/*
 * OpenVPN Configuration Files Converter
 * Copyright © 2020 Anton Kikin <a.kikin@tano-systems.com>
 *
 * This work is free. You can redistribute it and/or modify it under the
 * terms of the Do What The Fuck You Want To Public License, Version 2,
 * as published by Sam Hocevar. See the COPYING file for more details.
 */

#include <stdarg.h>
#include <ovpn.h>

/* ----------------------------------------------------------------------- */

ovpn_t *ovpn_new(unsigned int flags)
{
	ovpn_t *ovpn = malloc(sizeof(ovpn_t));
	if (!ovpn)
		return NULL;

	memset(ovpn, 0, sizeof(ovpn_t));

	ovpn->flags = flags;

	/*
	 * Creates default JSON scheme:
	 * {
	 *     "inlines": {
	 *     },
	 *     "options": {
	 *     }
	 * }
	 */
	ovpn->json = json_object_new_object();
	if (!ovpn->json)
		goto out_error;

	ovpn->json_inlines = json_object_new_object();
	if (!ovpn->json_inlines)
		goto out_error;

	json_object_object_add(ovpn->json, "inlines",
		ovpn->json_inlines);

	ovpn->json_options = json_object_new_object();
	if (!ovpn->json_options)
		goto out_error;
	
	json_object_object_add(ovpn->json, "options",
		ovpn->json_options);

	/*
	 * JSON scheme for status object:
	 * {
	 *     "errors": 1,
	 *     "warning": 1
	 *     "messages": [
	 *         {
	 *             "type": "error",
	 *             "line": x,
	 *             "message": "xxxxxx"
	 *         }, {
	 *             "type": "warning",
	 *             "line": x,
	 *             "message": "xxxxxx"
	 *         }
	 *     ],
	 * }
	 */
	ovpn->json_status = json_object_new_object();
	if (!ovpn->json_status)
		goto out_error;

	json_object_object_add(ovpn->json_status, "errors", json_object_new_int(0));
	json_object_object_add(ovpn->json_status, "warnings", json_object_new_int(0));
	json_object_object_add(ovpn->json_status, "messages", json_object_new_array());

	if (ovpn->flags & OVPN_FLAG_INCLUDE_STATUS)
		json_object_object_add(ovpn->json, "status", ovpn->json_status);

	return ovpn;

out_error:
	if (ovpn->json)
		json_object_put(ovpn->json);

	if (ovpn->json_status)
		json_object_put(ovpn->json_status);

	free(ovpn);
	return NULL;
}

void ovpn_delete(ovpn_t *ovpn)
{
	if (!ovpn)
		return;

	if (ovpn->json)
		json_object_put(ovpn->json);

	if (ovpn->json_status && !(ovpn->flags & OVPN_FLAG_INCLUDE_STATUS))
		json_object_put(ovpn->json_status);

	free(ovpn);
}

int ovpn_dump_json(ovpn_t *ovpn, unsigned int flags, FILE *stream)
{
	if (!ovpn || !ovpn->json)
		return -1;

	fprintf(stream, "%s\n", json_object_to_json_string_ext(
		ovpn->json,
		(flags & OVPN_DUMP_FLAG_PRETTY)
		? (JSON_C_TO_STRING_PRETTY | JSON_C_TO_STRING_PRETTY_TAB) /* NOLINT(hicpp-signed-bitwise) */
		: 0
	));

	return 0;
}

int ovpn_dump_json_status(ovpn_t *ovpn, unsigned int flags, FILE *stream)
{
	if (!ovpn || !ovpn->json_status)
		return -1;

	if (ovpn->flags & OVPN_FLAG_INCLUDE_STATUS)
		return 0;

	fprintf(stream, "%s\n", json_object_to_json_string_ext(
		ovpn->json_status,
		(flags & OVPN_DUMP_FLAG_PRETTY)
		? (JSON_C_TO_STRING_PRETTY | JSON_C_TO_STRING_PRETTY_TAB) /* NOLINT(hicpp-signed-bitwise) */
		: 0
	));

	return 0;
}

/* ----------------------------------------------------------------------- */

int ovpn_status_msg(
	ovpn_t *ovpn,
	ovpn_msg_type_t msg,
	unsigned int line,
	const char *format, ...
)
{
	int res;
	char buf[256] = { 0 };

	json_object *obj;

	const char *type;

	switch (msg)
	{
		case OVPN_MSG_TYPE_ERROR: type = "error";
			ovpn->errors++;

			if (json_object_object_get_ex(ovpn->json_status, "errors", &obj))
				json_object_set_int(obj, (int) ovpn->errors);

			break;

		case OVPN_MSG_TYPE_WARNING: type = "warning";
			ovpn->warnings++;

			if (json_object_object_get_ex(ovpn->json_status, "warnings", &obj))
				json_object_set_int(obj, (int) ovpn->warnings);

			break;

		default: type = "unknown";
			break;
	}

	va_list va;
	va_start(va, format);

	res = vsnprintf(buf, sizeof(buf), format, va);
	if (res < 0)
		return -1;

	va_end(va);

	if (json_object_object_get_ex(ovpn->json_status, "messages", &obj))
	{
		json_object *json_message = json_object_new_object();

		if (!json_message)
			return -ENOMEM;

		json_object_object_add(json_message, "type",
			json_object_new_string(type));

		json_object_object_add(json_message, "message",
			json_object_new_string(buf));

		if (line > 0)
			json_object_object_add(json_message, "line",
				json_object_new_int((int)line));

		json_object_array_add(obj, json_message);
	}

	return 0;
}

/* ----------------------------------------------------------------------- */
