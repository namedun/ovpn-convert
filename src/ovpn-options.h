/*
 * OpenVPN Configuration Files Converter
 * Copyright © 2020 Anton Kikin <a.kikin@tano-systems.com>
 *
 * This work is free. You can redistribute it and/or modify it under the
 * terms of the Do What The Fuck You Want To Public License, Version 2,
 * as published by Sam Hocevar. See the COPYING file for more details.
 */

#ifndef OVPN_OPTIONS_H
#define OVPN_OPTIONS_H

/* ----------------------------------------------------------------------- */

/** Maximum size for inline tag name */
#define OVPN_OPT_INLINE_TAG_SIZE  32

/* ----------------------------------------------------------------------- */

/**
 * OpenVPN configuration option inline types
 */
typedef enum
{
	/** Invalid (unspecified) type */
	OVPN_OPT_INLINE_TYPE_INVALID = 0,

	/** Plain */
	OVPN_OPT_INLINE_TYPE_PLAIN,

	/** Options */
	OVPN_OPT_INLINE_TYPE_OPTIONS,

} ovpn_opt_inline_type_t;

static inline const char *ovpn_opt_inline_type_asciiz(
	const ovpn_opt_inline_type_t type)
{
	switch (type)
	{
		case OVPN_OPT_INLINE_TYPE_PLAIN:   return "plain";
		case OVPN_OPT_INLINE_TYPE_OPTIONS: return "options";
		case OVPN_OPT_INLINE_TYPE_INVALID: /* fallthrough */
		default:
			return "invalid";
	}
}

/**
 * @def OVPN_OPT_FLAG_MULTIPLE
 *      Option can be specified multiple times
 * @def OVPN_OPT_FLAG_CONNECTION
 *      Option can be used in connection profile
 * @def OVPN_OPT_FLAG_DEPRECATED
 *      Option is deprecated and will be removed in OpenVPN 2.5+
 * @def OVPN_OPT_FLAG_WINDOWS
 *      Windows specific option
 * @def OVPN_OPT_FLAG_IPV6
 *      IPv6 related option
 * @def OVPN_OPT_FLAG_INLINE
 *      Option can be in 'inline' form
 * @def OVPN_OPT_FLAG_DEBUG
 *      Debug related option
 * @def OVPN_OPT_FLAG_STANDALONE
 *      Option can be used only in standalone mode
 * @def OVPN_OPT_FLAG_PUSHABLE
 *      Option can be used in "push" option
 * @def OVPN_OPT_FLAG_NORMAL
 *      Option can be used in normal context
 */

#define OVPN_OPT_FLAG_MULTIPLE    (0x001u)
#define OVPN_OPT_FLAG_CONNECTION  (0x002u)
#define OVPN_OPT_FLAG_DEPRECATED  (0x004u)
#define OVPN_OPT_FLAG_WINDOWS     (0x008u)
#define OVPN_OPT_FLAG_IPV6        (0x010u)
#define OVPN_OPT_FLAG_INLINE      (0x020u)
#define OVPN_OPT_FLAG_DEBUG       (0x040u)
#define OVPN_OPT_FLAG_STANDALONE  (0x080u)
#define OVPN_OPT_FLAG_PUSHABLE    (0x100u)
#define OVPN_OPT_FLAG_NORMAL      (0x200u)

/** The value that defines that the option number
  * of arguments is not limited. */
#define OVPN_OPT_ARGS_NOT_LIMITED (-1)

/**
 * OpenVPN option argument types
 */
typedef enum
{
	OVPN_OPT_ARG_TYPE_LISTVALUE = 1,
	OVPN_OPT_ARG_TYPE_ADDRESS,
	OVPN_OPT_ARG_TYPE_PORT,
	OVPN_OPT_ARG_TYPE_NUMBER,
	OVPN_OPT_ARG_TYPE_UNUMBER,
	OVPN_OPT_ARG_TYPE_INTERFACE,
	OVPN_OPT_ARG_TYPE_FILEPATH,
	OVPN_OPT_ARG_TYPE_STRING,
	OVPN_OPT_ARG_TYPE_COMMAND,
	OVPN_OPT_ARG_TYPE_DIR,
	OVPN_OPT_ARG_TYPE_NETWORK,
	OVPN_OPT_ARG_TYPE_NETMASK,
	OVPN_OPT_ARG_TYPE_TUNTAP_DEVICE,
	OVPN_OPT_ARG_TYPE_LIST,
	OVPN_OPT_ARG_TYPE_IPV6ADDR,
	OVPN_OPT_ARG_TYPE_IPADDR,
	OVPN_OPT_ARG_TYPE_MACADDRESS,

} ovpn_opt_arg_type_t;

/**
 * OpenVPN option argument information
 */
typedef struct
{
	const char *name;
	const ovpn_opt_arg_type_t *types;
	int optional;
	int range_min;
	int range_max;
	const char *listvalues[];

} ovpn_opt_arg_info_t;

/**
 * OpenVPN configuration option
 */
typedef struct
{
	/** Option name */
	const char *name;

	/** Option flags */
	unsigned int flags;

	/** Option inline type
	  * Actual only with OVPN_OPT_FLAG_INLINE flag */
	ovpn_opt_inline_type_t inline_type;

	struct
	{
		/** Minimal number of arguments */
		int min;

		/** Maximal number of arguments (-1 - not limited) */
		int max;

		/** Arguments information */
		const ovpn_opt_arg_info_t **info;

	} args;

} ovpn_opt_info_t;

/* ----------------------------------------------------------------------- */

/**
 * Find option information by option name
 *
 * @param[in] name  Option name
 * @param[in] flags Find only options with specified flags
 * @param[in] num   Maximum count of characters in @p name to find
 *
 * @return Pointer to option information structure
 *         (@ref ovpn_opt_t) or NULL
 */
const ovpn_opt_info_t *ovpn_opt_find(
	const char *name,
	unsigned int flags,
	size_t num
);

/* ----------------------------------------------------------------------- */

#endif /* OVPN_OPTIONS_H */
