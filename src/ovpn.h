/*
 * OpenVPN Configuration Files Converter
 * Copyright © 2020 Anton Kikin <a.kikin@tano-systems.com>
 *
 * This work is free. You can redistribute it and/or modify it under the
 * terms of the Do What The Fuck You Want To Public License, Version 2,
 * as published by Sam Hocevar. See the COPYING file for more details.
 */

#ifndef OVPN_H
#define OVPN_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>
#include <assert.h>

#include <libintl.h>
#include <locale.h>

#define _(STRING) gettext(STRING) /* NOLINT(bugprone-reserved-identifier) */

#include <json-c/json.h>
#include <ovpn-options.h>

/* ----------------------------------------------------------------------- */

/**
 * @brief OpenVPN configuration file data
 */
typedef struct ovpn
{
	/** Flags */
	unsigned int flags;

	/** Count of errors */
	unsigned int errors;

	/** Count of warnings */
	unsigned int warnings;

	/** Root JSON object */
	json_object *json;

	/** JSON object for options data */
	json_object *json_options;

	/** JSON object for inlines data */
	json_object *json_inlines;

	/** JSON object for status */
	json_object *json_status;

} ovpn_t;

/** Include status object in main JSON */
#define OVPN_FLAG_INCLUDE_STATUS  0x01u

ovpn_t *ovpn_new(unsigned int flags);
void ovpn_delete(ovpn_t *ovpn);

int ovpn_parse(ovpn_t *ovpn, FILE *input);

#define OVPN_DUMP_FLAG_PRETTY  0x01u

int ovpn_dump_json(
	ovpn_t *ovpn, unsigned int flags, FILE *stream);

int ovpn_dump_json_status(
	ovpn_t *ovpn, unsigned int flags, FILE *stream);

/* ----------------------------------------------------------------------- */

typedef enum
{
	OVPN_MSG_TYPE_ERROR,
	OVPN_MSG_TYPE_WARNING,

} ovpn_msg_type_t;

__attribute__((format(printf, 4, 5)))
int ovpn_status_msg(
	ovpn_t *ovpn,
	ovpn_msg_type_t msg,
	unsigned int line,
	const char *format, ...
);

/* ----------------------------------------------------------------------- */

#endif /* OVPN_H */
