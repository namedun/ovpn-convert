/*
 * OpenVPN Configuration Files Converter
 * Copyright © 2020 Anton Kikin <a.kikin@tano-systems.com>
 *
 * This work is free. You can redistribute it and/or modify it under the
 * terms of the Do What The Fuck You Want To Public License, Version 2,
 * as published by Sam Hocevar. See the COPYING file for more details.
 */

#include <ctype.h> /* isspace */

#include <ovpn.h>

/* ----------------------------------------------------------------------- */

/** @brief Maximum line size */
#define OVPN_PARSE_MAX_BUFFER_SIZE  1024

/** @brief Initial buffer size for reading */
#define OVPN_PARSE_BUFFER_SIZE  256

/* ----------------------------------------------------------------------- */

/** Default (initial) string data buffer size
 *  (must be power of two) */
#define DATA_BUFFER_SIZE  8192u

/**
 * Simple accumulative string buffer
 */
typedef struct
{
	/** String data */
	char *data;

	/** Current allocated size */
	size_t size;

	/** Current string length (without '\0') */
	size_t len;

} data_buffer_t;

static int data_buffer_init(data_buffer_t *b)
{
	assert(b);

	b->size = DATA_BUFFER_SIZE;
	b->len  = 0;
	b->data = calloc(1, b->size);

	if (!b->data)
		return -ENOMEM;

	return 0;
}

static void data_buffer_free(data_buffer_t *b)
{
	assert(b);
	assert(b->data);
	free(b->data);
}

static const char *data_buffer_get(data_buffer_t *b)
{
	assert(b);
	return b->data;
}

static int data_buffer_resize(data_buffer_t *b, const size_t size)
{
	char *new_data;
	size_t new_size;

	assert(b);

	/* Align to DATA_BUFFER_SIZE boundaries */
	new_size = (size + (DATA_BUFFER_SIZE - 1)) &
		(~(DATA_BUFFER_SIZE - 1));

	if (new_size <= b->size)
		return 0;

	new_data = realloc(b->data, new_size);
	if (!new_data)
		return -ENOMEM;

	b->data = new_data;
	b->size = new_size;
	return 0;
}

static int data_buffer_set(data_buffer_t *b, const char *data)
{
	size_t len;

	assert(b);
	assert(data);

	len = strlen(data);

	if ((len + 1) > b->size)
	{
		int ret = data_buffer_resize(b, (len + 1));
		if (ret)
			return ret;
	}

	b->len = len;
	strcpy(b->data, data);
	return 0;
}

static int data_buffer_append(data_buffer_t *b, const char *data)
{
	size_t new_len;

	assert(b);
	assert(data);

	new_len = b->len + strlen(data);

	if ((new_len + 1) > b->size)
	{
		int ret = data_buffer_resize(b, (new_len + 1));
		if (ret)
			return ret;
	}

	strcat(b->data + b->len, data);
	b->len = new_len;
	return 0;
}

/* ----------------------------------------------------------------------- */

#define OVPN_PARSE_FLAG_INLINE  0x01u

/**
 * @brief Parsing state structure
 */
typedef struct
{
	/** OpenVPN configuration data */
	ovpn_t *ovpn;

	/** Current line number */
	unsigned int line_n;

	/** Parsing state flags */
	unsigned int flags;

	/** Current tag name (inline option name or 'connection') */
	char inline_name[OVPN_OPT_INLINE_TAG_SIZE];

	/** Current inline tag option (only if tag is valid) */
	const ovpn_opt_info_t *inline_opt;

	/** JSON object that used to store options */
	json_object *json_options;

	/** JSON object that used to store inlines */
	json_object *json_inlines;

	/** JSON object for current inline data array */
	json_object *json_inline_data_array;

	/** Storage data buffer for inline data */
	data_buffer_t inline_data_buffer;

} ovpn_parse_state_t;

/* ----------------------------------------------------------------------- */

typedef struct
{
	const char *tag;
	size_t tag_len;
	int is_closing;

} ovpn_find_tag_data_t;

typedef enum
{
	OVPN_FIND_TAG_RES_OK,
	OVPN_FIND_TAG_RES_NONE,
	OVPN_FIND_TAG_RES_EMPTY_TAG,

} ovpn_find_tag_res_t;

static ovpn_find_tag_res_t ovpn_find_tag(
	const char *line,
	ovpn_find_tag_data_t *data
)
{
	const char *p = line;
	const char *start;
	const char *end;

	assert(line);
	assert(data);

	data->is_closing = 0;

	/* Trim leading spaces */
	while (isspace(*p))
		p++;

	/* No tag open bracket */
	if (!*p || (*p != '<'))
		return OVPN_FIND_TAG_RES_NONE;

	start = ++p;
	if (start[0] == '/')
	{
		start = ++p;
		data->is_closing = 1;
	}

	while (*p && (*p != '>'))
		p++;

	/* No tag close bracket */
	if (!*p)
		return OVPN_FIND_TAG_RES_NONE;

	end = p;

	/* Empty tag name */
	if (start == end)
		return OVPN_FIND_TAG_RES_EMPTY_TAG;

	data->tag = start;
	data->tag_len = (size_t)(end - start);

	return OVPN_FIND_TAG_RES_OK;
}

/* ----------------------------------------------------------------------- */

typedef enum
{
	OVPN_PARSE_TAG_RES_NONE,
	OVPN_PARSE_TAG_RES_OPENED,
	OVPN_PARSE_TAG_RES_CLOSED,
	OVPN_PARSE_TAG_RES_ERROR,

} ovpn_parse_tag_res_t;

static ovpn_parse_tag_res_t ovpn_parse_tag(
	ovpn_parse_state_t *state,
	const char *line
)
{
	int ret;
	ovpn_find_tag_data_t tag_data;

	ret = ovpn_find_tag(line, &tag_data);
	if (ret != OVPN_FIND_TAG_RES_OK)
		return OVPN_PARSE_TAG_RES_NONE;

	if (state->flags & OVPN_PARSE_FLAG_INLINE)
	{
		if (!tag_data.is_closing)
		{
			ovpn_status_msg(
				state->ovpn,
				OVPN_MSG_TYPE_ERROR,
				state->line_n,
				_("Unexpected start of inline option")
			);

			return OVPN_PARSE_TAG_RES_ERROR;
		}

		if (strncmp(state->inline_name, tag_data.tag, tag_data.tag_len) != 0)
		{
			ovpn_status_msg(
				state->ovpn,
				OVPN_MSG_TYPE_ERROR,
				state->line_n,
				_("Ending inline option is not match starting inline option")
			);

			return OVPN_PARSE_TAG_RES_ERROR;
		}

		state->flags &= (~OVPN_PARSE_FLAG_INLINE);
		return OVPN_PARSE_TAG_RES_CLOSED;
	}
	else
	{
		const ovpn_opt_info_t *tag_opt = ovpn_opt_find(
			tag_data.tag, 0, tag_data.tag_len);

		state->flags |= OVPN_PARSE_FLAG_INLINE;

		strncpy(state->inline_name, tag_data.tag, tag_data.tag_len);
		state->inline_name[tag_data.tag_len] = '\0';
		state->inline_opt = NULL;

		if (tag_data.is_closing)
		{
			ovpn_status_msg(
				state->ovpn,
				OVPN_MSG_TYPE_ERROR,
				state->line_n,
				_("Unexpected end of inline option '%s'"),
				state->inline_name
			);

			return OVPN_PARSE_TAG_RES_ERROR;
		}

		if (tag_opt)
		{
			if (tag_opt->flags & OVPN_OPT_FLAG_INLINE)
			{
				state->inline_opt = tag_opt;
			}
			else
			{
				ovpn_status_msg(
					state->ovpn,
					OVPN_MSG_TYPE_WARNING,
					state->line_n,
					_("Option '%s' can not be used in inline form"),
					state->inline_name
				);
			}
		}
		else
		{
 			ovpn_status_msg(
				state->ovpn,
				OVPN_MSG_TYPE_WARNING,
				state->line_n,
				_("Unknown inline option '%s'"),
				state->inline_name
			);
		}

		return OVPN_PARSE_TAG_RES_OPENED;
	}
}

/* ----------------------------------------------------------------------- */

/**
 * Line parser result code
 */
typedef enum
{
	/** Line successfully parsed */
	OVPN_LINE_PARSER_RES_PARSED,

	/** Line is not parsed. Try next parser */
	OVPN_LINE_PARSER_RES_NEXT,

	/** Parsing error */
	OVPN_LINE_PARSER_RES_ERROR,

	/** System error (no memory, etc...) */
	OVPN_LINE_PARSER_RES_SYS_ERROR

} ovpn_line_parser_res_t;

/* ----------------------------------------------------------------------- */

static ovpn_line_parser_res_t ovpn_line_parser_inline_tag(
	ovpn_parse_state_t *state,
	char *line
)
{
	ovpn_parse_tag_res_t tag_res;

	tag_res = ovpn_parse_tag(state, line);
	switch (tag_res)
	{
		case OVPN_PARSE_TAG_RES_OPENED:
		{
			json_object *inline_obj;

			if (!state->inline_opt)
				return OVPN_LINE_PARSER_RES_PARSED;

			if (!json_object_object_get_ex(
					state->json_inlines,
					state->inline_name,
					&inline_obj))
			{
				/* Create new JSON object for inline */
				inline_obj = json_object_new_object();

				json_object_object_add(
					state->json_inlines,
					state->inline_name,
					inline_obj
				);

				json_object_object_add(
					inline_obj,
					"type",
					json_object_new_string(
						ovpn_opt_inline_type_asciiz(
							state->inline_opt->inline_type
						)
					)
				);

				state->json_inline_data_array =
					json_object_new_array();

				json_object_object_add(
					 inline_obj,
					"data",
					 state->json_inline_data_array
				);
			}
			else
			{
				/* Use existing JSON object for inline */
				json_object_object_get_ex(
					inline_obj, "data", &state->json_inline_data_array);
			}

			if (state->inline_opt->inline_type == OVPN_OPT_INLINE_TYPE_OPTIONS)
			{
				state->json_options =
					json_object_new_object();

				json_object_array_add(
					state->json_inline_data_array,
					state->json_options
				);
			}

			/* Clear data buffer */
			data_buffer_set(&state->inline_data_buffer, "");

			return OVPN_LINE_PARSER_RES_PARSED;
		}

		case OVPN_PARSE_TAG_RES_CLOSED:
			if (state->inline_opt)
			{
				if (state->inline_opt->inline_type == OVPN_OPT_INLINE_TYPE_PLAIN)
				{
					/* Add plain inline data to data array */
					json_object_array_add(
						state->json_inline_data_array,
						json_object_new_string(
							data_buffer_get(&state->inline_data_buffer)
						)
					);
				}
				else if (state->inline_opt->inline_type == OVPN_OPT_INLINE_TYPE_OPTIONS)
				{
					/* Restore JSON options object to global */
					state->json_options = state->ovpn->json_options;
				}
			}

			return OVPN_LINE_PARSER_RES_PARSED;

		case OVPN_PARSE_TAG_RES_ERROR:
			return OVPN_LINE_PARSER_RES_ERROR;

		case OVPN_PARSE_TAG_RES_NONE:
			if (!(state->flags & OVPN_PARSE_FLAG_INLINE))
				return OVPN_LINE_PARSER_RES_NEXT;

			if (!state->inline_opt) /* ignore inline contents */
				return OVPN_LINE_PARSER_RES_PARSED;

			if (state->inline_opt->inline_type == OVPN_OPT_INLINE_TYPE_OPTIONS)
				return OVPN_LINE_PARSER_RES_NEXT;

			/* Collect plain inline data */
			if (data_buffer_append(&state->inline_data_buffer, line))
				return OVPN_LINE_PARSER_RES_SYS_ERROR;

			return OVPN_LINE_PARSER_RES_PARSED;

		default:
			break;
	}

	return OVPN_LINE_PARSER_RES_NEXT;
}

/* ----------------------------------------------------------------------- */

typedef struct
{
	char *curptr;
	int quotes;

} token_state_t;

static char *get_token(token_state_t *state, char *buffer, const char *delimeters)
{
	char ch;
	char *token = NULL;

	if (buffer)
	{
		/* Initializing */
		state->quotes = 0;
		state->curptr = buffer;
	}

	if (!delimeters || !state->curptr)
		return NULL;

	while((ch = *(state->curptr)))
	{
		if (!strchr(delimeters, ch))
		{
			token = state->curptr;
			break;
		}

		state->curptr++;
	}

	if (!token)
		return NULL;

	if (*token == '"')
	{
		++state->quotes;
		++token;
	}

	state->curptr = token;

	while((ch = *(state->curptr)))
	{
		if (( state->quotes && (ch == '"')) ||
			(!state->quotes && strchr(delimeters, ch)))
		{
			if (state->quotes)
				--state->quotes;

			*(state->curptr++) = '\0';
			break;
		}

		state->curptr++;
	}

	return token;
}

/* ----------------------------------------------------------------------- */

int ovpn_parse_validate_opt_basic(
	const ovpn_parse_state_t *state,
	const ovpn_opt_info_t *opt
)
{
	if (opt->flags & OVPN_OPT_FLAG_DEPRECATED)
	{
		ovpn_status_msg(
			state->ovpn, OVPN_MSG_TYPE_WARNING, state->line_n,
			_("Option '%s' is deprecated "
			  "and can be removed in future OpenVPN versions"),
			opt->name
		);
	}

	if (opt->flags & OVPN_OPT_FLAG_STANDALONE)
	{
		ovpn_status_msg(
			state->ovpn, OVPN_MSG_TYPE_WARNING, state->line_n,
			_("Option '%s' can be used only in standalone mode"),
			opt->name
		);
	}

	if (opt->flags & OVPN_OPT_FLAG_WINDOWS)
	{
		ovpn_status_msg(
			state->ovpn, OVPN_MSG_TYPE_WARNING, state->line_n,
			_("The '%s' option is specific for Windows"),
			opt->name
		);
	}

	return 0;
}

/* ----------------------------------------------------------------------- */

int ovpn_parse_validate_opt_arg(
	const ovpn_parse_state_t *state,
	const ovpn_opt_info_t *opt,
	int arg_idx,
	json_object *json_arg
)
{
	int i;
	int valid = false;

	const ovpn_opt_arg_info_t *arg_info;

	const char *arg_data = json_object_get_string(json_arg);

	if ((opt->args.max == OVPN_OPT_ARGS_NOT_LIMITED) && (arg_idx >= opt->args.max))
		arg_info = opt->args.info[opt->args.max - 1];
	else
		arg_info = opt->args.info[arg_idx];

	for (i = 0; arg_info->types[i]; i++)
	{
		if (valid)
			break;

		switch(arg_info->types[i])
		{
			case OVPN_OPT_ARG_TYPE_PORT:    /* fallthrough */
			case OVPN_OPT_ARG_TYPE_NUMBER:  /* fallthrough */
			case OVPN_OPT_ARG_TYPE_UNUMBER:
			{
				char *pEnd;
				long value = strtol(arg_data, &pEnd, 10);

				if (*pEnd != '\0')
					break;

				if (arg_info->types[i] == OVPN_OPT_ARG_TYPE_PORT)
				{
					if ((value >= 1) && (value <= 65536))
						valid = true;
				}
				else
				{
					if (arg_info->range_max != arg_info->range_min)
					{
						if ((value >= arg_info->range_min) && (value <= arg_info->range_max))
							valid = true;
					}
					else
					{
						if (arg_info->types[i] == OVPN_OPT_ARG_TYPE_UNUMBER)
						{
							if (value >= 0)
								valid = true;
						}
						else
							valid = true;
					}
				}

				break;
			}

			case OVPN_OPT_ARG_TYPE_LISTVALUE:
			{
				int j;

				for (j = 0; arg_info->listvalues[j]; j++)
				{
					if (strcmp(arg_data, arg_info->listvalues[j]) == 0)
					{
						valid = true;
						break;
					}
				}

				break;
			}

			case OVPN_OPT_ARG_TYPE_FILEPATH:      /* fallthrough */
			case OVPN_OPT_ARG_TYPE_DIR:           /* fallthrough */
			case OVPN_OPT_ARG_TYPE_ADDRESS:       /* fallthrough */
			case OVPN_OPT_ARG_TYPE_INTERFACE:     /* fallthrough */
			case OVPN_OPT_ARG_TYPE_STRING:        /* fallthrough */
			case OVPN_OPT_ARG_TYPE_COMMAND:       /* fallthrough */
			case OVPN_OPT_ARG_TYPE_NETWORK:       /* fallthrough */
			case OVPN_OPT_ARG_TYPE_NETMASK:       /* fallthrough */
			case OVPN_OPT_ARG_TYPE_TUNTAP_DEVICE: /* fallthrough */
			case OVPN_OPT_ARG_TYPE_LIST:          /* fallthrough */
			case OVPN_OPT_ARG_TYPE_IPV6ADDR:      /* fallthrough */
			case OVPN_OPT_ARG_TYPE_IPADDR:        /* fallthrough */
			case OVPN_OPT_ARG_TYPE_MACADDRESS:    /* fallthrough */
				valid = true;
				break;
		}
	}

	if (!valid)
	{
		ovpn_status_msg(
			state->ovpn, OVPN_MSG_TYPE_ERROR, state->line_n,
			_("Option '%s' has invalid argument #%d (%s) value '%s'"),
			opt->name, arg_idx + 1, arg_info->name, arg_data
		);
	}

	return 0;
}

int ovpn_parse_validate_opt_args(
	const ovpn_parse_state_t *state,
	const ovpn_opt_info_t *opt,
	const json_object *json_opt_args
)
{
	int arg_idx;
	int args_count = json_object_array_length(json_opt_args);

	/* Basic check for arguments count */
	if (args_count < opt->args.min)
	{
		ovpn_status_msg(
			state->ovpn, OVPN_MSG_TYPE_WARNING, state->line_n,
			_("Too few arguments (%d). "
			  "The minimum number of arguments for the '%s' option is %d"),
			args_count, opt->name, opt->args.min
		);
	}
	else if ((opt->args.max != OVPN_OPT_ARGS_NOT_LIMITED) &&
	         (args_count > opt->args.max))
	{
		ovpn_status_msg(
			state->ovpn, OVPN_MSG_TYPE_WARNING, state->line_n,
			_("Too many arguments (%d). "
			  "The maximum number of arguments for the '%s' option is %d"),
			args_count, opt->name, opt->args.max
		);
	}

	if (opt->args.info)
	{
		for (arg_idx = 0; arg_idx < args_count; arg_idx++)
		{
			if (opt->args.info[arg_idx])
			{
				ovpn_parse_validate_opt_arg(
					state, opt, arg_idx, json_object_array_get_idx(json_opt_args, arg_idx)
				);
			}
		}
	}

	return 0;
}

int ovpn_parse_validate_opt(
	const ovpn_parse_state_t *state,
	const ovpn_opt_info_t *opt,
	const json_object *json_opt
)
{
	json_object *json_opt_args;

	if (!json_object_object_get_ex(json_opt, "args", &json_opt_args))
		return -1;

	if (ovpn_parse_validate_opt_basic(state, opt))
		return -1;

	if (ovpn_parse_validate_opt_args(state, opt, json_opt_args))
		return -1;

	return 0;
}

/* ----------------------------------------------------------------------- */

static ovpn_line_parser_res_t ovpn_line_parser_option(
	ovpn_parse_state_t *state,
	char *line
)
{
	token_state_t token_state = { 0 };
	char *token = get_token(&token_state, line, " \t");

	if (token)
	{
		int args_count = 0;
		json_object *opt_array;
		json_object *args_array;
		json_object *opt_obj;

		const ovpn_opt_info_t *opt = ovpn_opt_find(
			token, OVPN_OPT_FLAG_NORMAL, SIZE_MAX
		);

		if (!opt)
		{
			ovpn_status_msg(
				state->ovpn,
				OVPN_MSG_TYPE_WARNING,
				state->line_n,
				_("Unknown option '%s'"), token
			);

			return OVPN_LINE_PARSER_RES_PARSED;
		}

		if (!json_object_object_get_ex(
			state->json_options,
			opt->name,
			&opt_array
		))
		{
			opt_array = json_object_new_array();

			json_object_object_add(
				state->json_options,
				opt->name,
				opt_array
			);
		}

		opt_obj = json_object_new_object();
		json_object_array_add(opt_array, opt_obj);

		args_array = json_object_new_array();

		while (token)
		{
			token = get_token(&token_state, NULL, " \t");
			if (token)
			{
				args_count++;

				json_object_array_add(
					args_array,
					json_object_new_string(token)
				);
			}
		}

		/* Add option */
		json_object_object_add(opt_obj, "args", args_array);

		if (ovpn_parse_validate_opt(state, opt, opt_obj))
			return OVPN_LINE_PARSER_RES_ERROR;

		return OVPN_LINE_PARSER_RES_PARSED;
	}

	return OVPN_LINE_PARSER_RES_NEXT;
}

/* ----------------------------------------------------------------------- */

static ovpn_line_parser_res_t (*ovpn_line_parsers[])(
	ovpn_parse_state_t *, char *
) =
{
	&ovpn_line_parser_inline_tag,
	&ovpn_line_parser_option,
	NULL
};

static int ovpn_line_parse(
	ovpn_parse_state_t *state,
	char *line
)
{
	int i;

	for (i = 0; ovpn_line_parsers[i]; i++)
	{
		ovpn_line_parser_res_t parser_res =
			ovpn_line_parsers[i](state, line);

		switch (parser_res)
		{
			case OVPN_LINE_PARSER_RES_PARSED:
				return 0;

			case OVPN_LINE_PARSER_RES_ERROR:
				/* fallthrough */

			case OVPN_LINE_PARSER_RES_SYS_ERROR:
				return -1;

			case OVPN_LINE_PARSER_RES_NEXT:
				/* fallthrough */

			default:
				break;
		}
	}

	/* Can't parse line */
	return 0;
}

/* ----------------------------------------------------------------------- */

int ovpn_parse(ovpn_t *ovpn, FILE *input)
{
	int ret;

	char *buffer = NULL;
	size_t buffer_size = OVPN_PARSE_BUFFER_SIZE;

	ovpn_parse_state_t state = {
		.ovpn = ovpn,
		.json_inlines = ovpn->json_inlines,
		.json_options = ovpn->json_options,
	};

	ret = data_buffer_init(&state.inline_data_buffer);
	if (ret)
	{
		fprintf(stderr,
			"Failed to initialize inline data buffer\n");

		return ret;
	}

	buffer = malloc(buffer_size);
	if (!buffer)
	{
		fprintf(stderr,
			"Failed to allocate memory for line buffer\n");

		data_buffer_free(&state.inline_data_buffer);
		return -ENOMEM;
	}

	while (1)
	{
		char *line = NULL;

		size_t buffer_offset = 0;
		size_t line_len = 0;

		state.line_n++;

		while (1)
		{
			char *new_buffer;

			line = fgets(buffer + buffer_offset,
				(int)(buffer_size - buffer_offset), input);

			if (!line)
				break;

			line_len += strnlen(line, buffer_size);

			if ((buffer[line_len - 1] == '\r') ||
			    (buffer[line_len - 1] == '\n'))
				break;

			/* Increase line buffer size */
			buffer_size += OVPN_PARSE_BUFFER_SIZE;
			if (buffer_size > OVPN_PARSE_MAX_BUFFER_SIZE)
			{
				fprintf(stderr,
					"line %u: Line buffer size limit (%zu) reached\n",
					state.line_n,
					(size_t)OVPN_PARSE_MAX_BUFFER_SIZE
				);

				free(buffer);
				data_buffer_free(&state.inline_data_buffer);
				return -EINVAL;
			}

			new_buffer = realloc(buffer, buffer_size);
			if (!new_buffer)
			{
				fprintf(stderr,
					"line %u: Failed to reallocate memory for line buffer (%zu -> %zu)\n",
					state.line_n,
					buffer_size - OVPN_PARSE_BUFFER_SIZE,
					buffer_size
				);

				free(buffer);
				data_buffer_free(&state.inline_data_buffer);
				return -ENOMEM;
			}

			buffer = new_buffer;
			buffer_offset = line_len;
		}

		if (!line_len) /* EOF */
			break;

		/* Do not trim spaces and comments in inlines */
		if (!(state.flags & OVPN_PARSE_FLAG_INLINE) ||
		    !strcmp(state.inline_name, "connection"))
		{
			/* Trim ending spaces */
			line = &buffer[line_len - 1];
			while ((line > buffer) && isspace(*line))
				*(line--) = '\0';

			line = buffer;

			/* Trim leading spaces */
			while (isspace(*line))
				line++;

			/* Trim comments ('#' and ';') */
			if (*line == '#' || *line == ';')
				*line = '\0';
		}
		else
			line = buffer;

		ret = ovpn_line_parse(&state, line);
		if (ret)
			break;
	}

	free(buffer);
	data_buffer_free(&state.inline_data_buffer);
	return ret;
}

/* ----------------------------------------------------------------------- */
