/*
 * OpenVPN Configuration Files Converter
 * Copyright © 2020 Anton Kikin <a.kikin@tano-systems.com>
 *
 * This work is free. You can redistribute it and/or modify it under the
 * terms of the Do What The Fuck You Want To Public License, Version 2,
 * as published by Sam Hocevar. See the COPYING file for more details.
 */

/**
 * @file
 * @brief Main source file
 *
 * @author Anton Kikin <a.kikin@tano-systems.com>
 */

#include <getopt.h>
#include <limits.h> /* PATH_MAX */
#include <ovpn.h>

/* ----------------------------------------------------------------------- */

/**
 * @brief Configuration data structure
 */
typedef struct config
{
	/** Read data from stdin */
	int is_stdin;

	/** Output formatted JSON */
	int is_pretty;

	/** Include status information into main JSON object
	 *  By default, status information dumper separately in stderr */
	int include_status;

	/** Input file name */
	const char *input_filename;

	/** Base path for locale files */
	char locale_path[PATH_MAX];

	/** Language */
	char language[32];

} config_t;

/**
 * @brief Global configuration structure and default values
 */
static config_t config =
{
	.is_stdin       =  0,
	.is_pretty      =  0,
	.include_status =  0,
	.input_filename =  NULL,
	.locale_path    =  GETTEXT_LOCALEDIR,
	.language       = "",
};

/* ----------------------------------------------------------------------- */

/**
 * @brief Short command line options list
 */
static const char *opts_str = "hspil:L:";

/**
 * @brief Long command line options list
 */
static const struct option opts[] =
{
	{ .name = "help",           .has_arg = no_argument,       .val = 'h' },
	{ .name = "stdin",          .has_arg = no_argument,       .val = 's' },
	{ .name = "pretty",         .has_arg = no_argument,       .val = 'p' },
	{ .name = "include-status", .has_arg = no_argument,       .val = 'i' },
	{ .name = "locale-path",    .has_arg = required_argument, .val = 'l' },
	{ .name = "language",       .has_arg = required_argument, .val = 'L' },
	{ 0 }
};

/**
 * Display program usage help
 */
static void display_usage(void)
{
	fprintf(stdout,
		"\n"
		"OpenVPN Configuration Files Converter version " OVPN_CONVERT_VERSION "\n"
		"Copyright (c) 2020 Anton Kikin <a.kikin@tano-systems.com>\n"
		"\n"
		"Usage: ovpn-convert [options] <input-file>\n"
		"\n"
		"Options:\n"
		"  -h, --help\n"
		"        Show this help text.\n"
		"\n"
		"  -s, --stdin\n"
		"        Read data from stdin instead of file.\n"
		"\n"
		"  -p, --pretty\n"
		"        Output formatted JSON.\n"
		"\n"
		"  -i, --include-status\n"
		"        Include parse status information to main JSON.\n"
		"        By default status information is dumped separately\n"
		"        to stderr stream.\n"
		"\n"
		"  -l, --locale-path <path>\n"
		"        Path to directory with locale (mo) files\n"
		"        (default: %s).\n"
		"\n"
		"  -L, --language <language>\n"
		"        Manually specify language\n"
		"        (default: <from environment>).\n"
		"\n",
		config.locale_path
	);
}

/**
 * Parse command line arguments into @ref config global structure
 *
 * @param[in] argc  Number of arguments
 * @param[in] argv  Array of the pointers to the arguments
 *
 * @return 0 on success
 * @return <0 on error
 */
static int parse_cli_args(int argc, char *argv[])
{
	int opt;

	while((opt = getopt_long(argc, argv, opts_str, opts, NULL)) != EOF)
	{
		switch(opt)
		{
			case '?':
			{
				/* Invalid option */
				return -EINVAL;
			}

			case 'h': /* --help */
			{
				display_usage();
				exit(0);
			}

			case 's': /* --stdin */
			{
				config.is_stdin = 1;
				break;
			}

			case 'p': /* --pretty */
			{
				config.is_pretty = 1;
				break;
			}

			case 'i': /* --include-status */
			{
				config.include_status = 1;
				break;
			}

			case 'l': /* --locale-path */
			{
				strncpy(config.locale_path, optarg, PATH_MAX);
				config.locale_path[PATH_MAX - 1] = '\0';
				break;
			}

			case 'L': /* --language */
			{
				strncpy(config.language, optarg, sizeof(config.language));
				config.language[sizeof(config.language) - 1] = '\0';
				break;
			}

			default:
				break;
		}
	}

	if ((argc == optind) && !config.is_stdin)
	{
		fprintf(stderr, "Input file is not specified\n");
		return -EINVAL;
	}
	else
	{
		if (!config.is_stdin)
		{
			config.input_filename = argv[optind];
		}
		else if (argc > optind)
		{
			fprintf(stderr,
				"Can't specify both stdin and input file\n");

			return -EINVAL;
		}
	}

	return 0;
}

/* ----------------------------------------------------------------------- */

static int setup_i18n(void)
{
#ifndef NDEBUG
	char locale_dir[PATH_MAX];
	strcpy(locale_dir, getenv("PWD"));
	strcat(locale_dir, "/po");
#else
	char *locale_dir = config.locale_path;
#endif

	if (config.language[0])
	{
		setenv("LANGUAGE", config.language, 1);
		setenv("LANG", config.language, 1);
	}

	/* Setting the i18n environment */
	setlocale(LC_ALL, "");

	bindtextdomain(GETTEXT_PACKAGE, locale_dir);
	textdomain(GETTEXT_PACKAGE);

	return 0;
}

/* ----------------------------------------------------------------------- */

int ovpn_parse_and_dump(FILE *input)
{
	int ret;
	ovpn_t *ovpn;

	ovpn = ovpn_new(
		config.include_status ? OVPN_FLAG_INCLUDE_STATUS : 0
	);

	if (!ovpn)
	{
		fprintf(stderr,
			"Failed to allocate memory for OVPN object\n");

		return -ENOMEM;
	}

	ret = ovpn_parse(ovpn, input);
	if (!ret)
	{
		ovpn_dump_json(
			ovpn,
			config.is_pretty ? OVPN_DUMP_FLAG_PRETTY : 0,
			stdout
		);

		if (!config.include_status)
		{
			/* If include_status is enabled, status object included in main JSON
			 * and dumped by ovpn_dump_json() function */
			ovpn_dump_json_status(
				ovpn,
				config.is_pretty ? OVPN_DUMP_FLAG_PRETTY : 0,
				stderr
			);
		}
	}

	ovpn_delete(ovpn);
	return ret;
}

/**
 * Program start point
 *
 * @param[in] argc  Number of arguments
 * @param[in] argv  Array of the pointers to the arguments
 *
 * @return 0 on success
 * @return <0 on error
 */
int main(int argc, char *argv[])
{
	int ret;
	FILE *input;

	ret = parse_cli_args(argc, argv);
	if (ret)
	{
		display_usage();
		return ret;
	}

	ret = setup_i18n();
	if (ret)
		return ret;

	if (config.is_stdin)
		input = stdin;
	else
	{
		input = fopen(config.input_filename, "rb");
		if (!input)
		{
			fprintf(stderr,
				"Could not open file '%s'\n",
				config.input_filename);

			return -ENODEV;
		}
	}

	ret = ovpn_parse_and_dump(input);
	if (!config.is_stdin)
		fclose(input);

	return ret;
}

/* ----------------------------------------------------------------------- */
