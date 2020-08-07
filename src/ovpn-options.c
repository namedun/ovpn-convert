/*
 * OpenVPN Configuration Files Converter
 * Copyright © 2020 Anton Kikin <a.kikin@tano-systems.com>
 *
 * This work is free. You can redistribute it and/or modify it under the
 * terms of the Do What The Fuck You Want To Public License, Version 2,
 * as published by Sam Hocevar. See the COPYING file for more details.
 */

#include <ovpn.h>

/* ----------------------------------------------------------------------- */

#define OVPN_OPT_DEF_ARG_TYPES(opt, opt_arg_num, ...) \
	static const ovpn_opt_arg_type_t \
		ovpn__ ## opt ## __args_ ## opt_arg_num ## _types[] = \
		{ \
			__VA_ARGS__, 0 \
		}

#define OVPN_OPT_DEF_ARG_LV(opt, opt_arg_num, opt_arg_name, \
                        opt_arg_optional, ...) \
	static const ovpn_opt_arg_info_t \
		ovpn__ ## opt ## __args_ ## opt_arg_num = \
		{ \
			.name = opt_arg_name, \
			.optional = opt_arg_optional, \
			.types = ovpn__ ## opt ## __args_ ## opt_arg_num ## _types, \
			.range_min = 0, \
			.range_max = 0, \
			.listvalues = { __VA_ARGS__, NULL } \
		}

#define OVPN_OPT_DEF_ARG_RANGE(opt, opt_arg_num, opt_arg_name, \
                        opt_arg_optional, opt_min, opt_max) \
	static const ovpn_opt_arg_info_t \
		ovpn__ ## opt ## __args_ ## opt_arg_num = \
		{ \
			.name = (opt_arg_name), \
			.optional = (opt_arg_optional), \
			.types = ovpn__ ## opt ## __args_ ## opt_arg_num ## _types, \
			.range_min = (opt_min), \
			.range_max = (opt_max), \
			.listvalues = { NULL } \
		}

#define OVPN_OPT_DEF_ARG(opt, opt_arg_num, opt_arg_name, \
                     opt_arg_optional) \
	static const ovpn_opt_arg_info_t \
		ovpn__ ## opt ## __args_ ## opt_arg_num = \
		{ \
			.name = (opt_arg_name), \
			.optional = (opt_arg_optional), \
			.types = ovpn__ ## opt ## __args_ ## opt_arg_num ## _types, \
			.range_min = 0, \
			.range_max = 0, \
			.listvalues = { NULL } \
		}

#define OVPN_OPT_DEF_ARGS_BEGIN(opt) \
	static const ovpn_opt_arg_info_t *ovpn__ ## opt ## __args[] = \
	{

#define OVPN_OPT_DEF_ARGS_ARG(opt, opt_arg_num) \
		&ovpn__ ## opt ## __args_ ## opt_arg_num,

#define OVPN_OPT_DEF_ARGS_END() \
		NULL \
	};

#define OVPN_OPT_REF_ARGS(opt) \
	ovpn__ ## opt ## __args

/* ----------------------------------------------------------------------- */

/*
 * Based on information from:
 * https://community.openvpn.net/openvpn/wiki/Openvpn24ManPage
 */

/* ----------------------------------------------------------------------- */

/*
 *     /\
 *    /  \
 *   / /\ \
 *  / ____ \
 * /_/    \_\
 */

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(allow_nonadmin, 1, OVPN_OPT_ARG_TYPE_INTERFACE);
OVPN_OPT_DEF_ARG(allow_nonadmin, 1, "TAP-Adapter", true);

OVPN_OPT_DEF_ARGS_BEGIN(allow_nonadmin)
OVPN_OPT_DEF_ARGS_ARG(allow_nonadmin, 1)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__allow_nonadmin =
{
	.name = "allow-nonadmin",
	.flags = OVPN_OPT_FLAG_NORMAL |
	         OVPN_OPT_FLAG_WINDOWS |
	         OVPN_OPT_FLAG_STANDALONE,
	.args = {
		/* [TAP-adapter] */
		.min = 0,
		.max = 1,
		.info = OVPN_OPT_REF_ARGS(allow_nonadmin)
	},
};

/* ----------------------------------------------------------------------- */

static const ovpn_opt_info_t ovpn__allow_pull_fqdn =
{
	.name = "allow-pull-fqdn",
	.flags = OVPN_OPT_FLAG_NORMAL,
};

/* ----------------------------------------------------------------------- */

static const ovpn_opt_info_t ovpn__allow_recursive_routing =
{
	.name = "allow-recursive-routing",
	.flags = OVPN_OPT_FLAG_NORMAL,
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(askpass, 1, OVPN_OPT_ARG_TYPE_FILEPATH);
OVPN_OPT_DEF_ARG(askpass, 1, "file", true);

OVPN_OPT_DEF_ARGS_BEGIN(askpass)
OVPN_OPT_DEF_ARGS_ARG(askpass, 1)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__askpass =
{
	.name = "askpass",
	.flags = OVPN_OPT_FLAG_NORMAL,
	.args = {
		/* [file] */
		.min = 0,
		.max = 1,
		.info = OVPN_OPT_REF_ARGS(askpass)
	},
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(auth, 1, OVPN_OPT_ARG_TYPE_STRING);
OVPN_OPT_DEF_ARG(auth, 1, "alg", false);

OVPN_OPT_DEF_ARGS_BEGIN(auth)
OVPN_OPT_DEF_ARGS_ARG(auth, 1)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__auth =
{
	.name = "auth",
	.flags = OVPN_OPT_FLAG_NORMAL,
	.args = {
		/* alg */
		.min = 1,
		.max = 1,
		.info = OVPN_OPT_REF_ARGS(auth)
	},
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(auth_gen_token, 1, OVPN_OPT_ARG_TYPE_UNUMBER);
OVPN_OPT_DEF_ARG(auth_gen_token, 1, "lifetime", true);

OVPN_OPT_DEF_ARGS_BEGIN(auth_gen_token)
OVPN_OPT_DEF_ARGS_ARG(auth_gen_token, 1)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__auth_gen_token =
{
	.name = "auth-gen-token",
	.args = {
		/* [lifetime] */
		.min = 0,
		.max = 1,
		.info = OVPN_OPT_REF_ARGS(auth_gen_token)
	},
	.flags = OVPN_OPT_FLAG_NORMAL
};

/* ----------------------------------------------------------------------- */

static const ovpn_opt_info_t ovpn__auth_nocache =
{
	.name = "auth-nocache",
	.flags = OVPN_OPT_FLAG_NORMAL
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(auth_retry, 1, OVPN_OPT_ARG_TYPE_LISTVALUE);
OVPN_OPT_DEF_ARG_LV(auth_retry, 1, "type", false,
	"none", "nointeract", "interact");

OVPN_OPT_DEF_ARGS_BEGIN(auth_retry)
OVPN_OPT_DEF_ARGS_ARG(auth_retry, 1)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__auth_retry =
{
	.name = "auth-retry",
	.flags = OVPN_OPT_FLAG_NORMAL,
	.args = {
		/* <none|nointeract|interact> */
		.min = 1,
		.max = 1,
		.info = OVPN_OPT_REF_ARGS(auth_retry)
	},
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(auth_token, 1, OVPN_OPT_ARG_TYPE_STRING);
OVPN_OPT_DEF_ARG(auth_token, 1, "token", false);

OVPN_OPT_DEF_ARGS_BEGIN(auth_token)
OVPN_OPT_DEF_ARGS_ARG(auth_token, 1)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__auth_token =
{
	.name = "auth-token",
	.flags = OVPN_OPT_FLAG_NORMAL |
	         OVPN_OPT_FLAG_PUSHABLE,
	.args = {
		/* token */
		.min = 1,
		.max = 1,
		.info = OVPN_OPT_REF_ARGS(auth_token)
	},
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(auth_user_pass, 1, OVPN_OPT_ARG_TYPE_FILEPATH);
OVPN_OPT_DEF_ARG(auth_user_pass, 1, "up", true);

OVPN_OPT_DEF_ARGS_BEGIN(auth_user_pass)
OVPN_OPT_DEF_ARGS_ARG(auth_user_pass, 1)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__auth_user_pass =
{
	.name = "auth-user-pass",
	.flags = OVPN_OPT_FLAG_NORMAL,
	.args = {
		/* [up] */
		.min = 0,
		.max = 1,
		.info = OVPN_OPT_REF_ARGS(auth_user_pass)
	},
};

/* ----------------------------------------------------------------------- */

static const ovpn_opt_info_t ovpn__auth_user_pass_optional =
{
	.name = "auth-user-pass-optional",
	.flags = OVPN_OPT_FLAG_NORMAL
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(auth_user_pass_verify, 1, OVPN_OPT_ARG_TYPE_COMMAND);
OVPN_OPT_DEF_ARG(auth_user_pass_verify, 1, "cmd", false);

OVPN_OPT_DEF_ARG_TYPES(auth_user_pass_verify, 2, OVPN_OPT_ARG_TYPE_LISTVALUE);
OVPN_OPT_DEF_ARG_LV(auth_user_pass_verify, 2, "method", false,
	"via-env", "via-file");

OVPN_OPT_DEF_ARGS_BEGIN(auth_user_pass_verify)
OVPN_OPT_DEF_ARGS_ARG(auth_user_pass_verify, 1)
OVPN_OPT_DEF_ARGS_ARG(auth_user_pass_verify, 2)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__auth_user_pass_verify =
{
	.name = "auth-user-pass-verify",
	.flags = OVPN_OPT_FLAG_NORMAL,
	.args = {
		/* cmd method */
		.min = 2,
		.max = 2,
		.info = OVPN_OPT_REF_ARGS(auth_user_pass_verify)
	},
};

/* ----------------------------------------------------------------------- */

/*
 *  ____
 * |  _ \
 * | |_) |
 * |  _ < 
 * | |_) |
 * |____/
 */

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(bcast_buffers, 1, OVPN_OPT_ARG_TYPE_UNUMBER);
OVPN_OPT_DEF_ARG(bcast_buffers, 1, "n", false);

OVPN_OPT_DEF_ARGS_BEGIN(bcast_buffers)
OVPN_OPT_DEF_ARGS_ARG(bcast_buffers, 1)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__bcast_buffers =
{
	.name = "bcast-buffers",
	.flags = OVPN_OPT_FLAG_NORMAL,
	.args = {
		/* n */
		.min = 1,
		.max = 1,
		.info = OVPN_OPT_REF_ARGS(bcast_buffers)
	},
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(bind, 1, OVPN_OPT_ARG_TYPE_LISTVALUE);
OVPN_OPT_DEF_ARG_LV(bind, 1, "ipv6only", true, "ipv6only");

OVPN_OPT_DEF_ARGS_BEGIN(bind)
OVPN_OPT_DEF_ARGS_ARG(bind, 1)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__bind =
{
	.name = "bind",
	.flags = OVPN_OPT_FLAG_NORMAL |
	         OVPN_OPT_FLAG_CONNECTION,
	.args = {
		/* [ipv6only] */
		.min = 0,
		.max = 1,
		.info = OVPN_OPT_REF_ARGS(bind)
	},
};

/* ----------------------------------------------------------------------- */

static const ovpn_opt_info_t ovpn__block_outside_dns =
{
	.name = "block-outside-dns",
	.flags = OVPN_OPT_FLAG_NORMAL |
	         OVPN_OPT_FLAG_WINDOWS,
};

/* ----------------------------------------------------------------------- */

/*
 *   _____
 *  / ____|
 * | |
 * | |
 * | |____
 *  \_____|
 *
 */

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(ca, 1, OVPN_OPT_ARG_TYPE_FILEPATH);
OVPN_OPT_DEF_ARG(ca, 1, "file", false);

OVPN_OPT_DEF_ARGS_BEGIN(ca)
OVPN_OPT_DEF_ARGS_ARG(ca, 1)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__ca =
{
	.name = "ca",
	.flags = OVPN_OPT_FLAG_NORMAL |
	         OVPN_OPT_FLAG_INLINE,
	.inline_type = OVPN_OPT_INLINE_TYPE_PLAIN,
	.args = {
		/* file */
		.min = 1,
		.max = 1,
		.info = OVPN_OPT_REF_ARGS(ca)
	},
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(capath, 1, OVPN_OPT_ARG_TYPE_DIR);
OVPN_OPT_DEF_ARG(capath, 1, "dir", false);

OVPN_OPT_DEF_ARGS_BEGIN(capath)
OVPN_OPT_DEF_ARGS_ARG(capath, 1)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__capath =
{
	.name = "capath",
	.flags = OVPN_OPT_FLAG_NORMAL,
	.args = {
		/* dir */
		.min = 1,
		.max = 1,
		.info = OVPN_OPT_REF_ARGS(capath)
	},
};

/* ----------------------------------------------------------------------- */

static const ovpn_opt_info_t ovpn__ccd_exclusive =
{
	.name = "ccd-exclusive",
	.flags = OVPN_OPT_FLAG_NORMAL
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(cd, 1, OVPN_OPT_ARG_TYPE_DIR);
OVPN_OPT_DEF_ARG(cd, 1, "dir", false);

OVPN_OPT_DEF_ARGS_BEGIN(cd)
OVPN_OPT_DEF_ARGS_ARG(cd, 1)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__cd =
{
	.name = "cd",
	.flags = OVPN_OPT_FLAG_NORMAL,
	.args = {
		/* dir */
		.min = 1,
		.max = 1,
		.info = OVPN_OPT_REF_ARGS(cd)
	},
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(cert, 1, OVPN_OPT_ARG_TYPE_FILEPATH);
OVPN_OPT_DEF_ARG(cert, 1, "file", false);

OVPN_OPT_DEF_ARGS_BEGIN(cert)
OVPN_OPT_DEF_ARGS_ARG(cert, 1)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__cert =
{
	.name = "cert",
	.flags = OVPN_OPT_FLAG_NORMAL |
	         OVPN_OPT_FLAG_INLINE,
	.inline_type = OVPN_OPT_INLINE_TYPE_PLAIN,
	.args = {
		/* file */
		.min = 1,
		.max = 1,
		.info = OVPN_OPT_REF_ARGS(cert)
	},
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(chroot, 1, OVPN_OPT_ARG_TYPE_DIR);
OVPN_OPT_DEF_ARG(chroot, 1, "dir", false);

OVPN_OPT_DEF_ARGS_BEGIN(chroot)
OVPN_OPT_DEF_ARGS_ARG(chroot, 1)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__chroot =
{
	.name = "chroot",
	.flags = OVPN_OPT_FLAG_NORMAL,
	.args = {
		/* dir */
		.min = 1,
		.max = 1,
		.info = OVPN_OPT_REF_ARGS(chroot)
	},
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(cipher, 1, OVPN_OPT_ARG_TYPE_STRING);
OVPN_OPT_DEF_ARG(cipher, 1, "alg", false);

OVPN_OPT_DEF_ARGS_BEGIN(cipher)
OVPN_OPT_DEF_ARGS_ARG(cipher, 1)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__cipher =
{
	.name = "cipher",
	.flags = OVPN_OPT_FLAG_NORMAL,
	.args = {
		/* alg */
		.min = 1,
		.max = 1,
		.info = OVPN_OPT_REF_ARGS(cipher)
	},
};

/* ----------------------------------------------------------------------- */

static const ovpn_opt_info_t ovpn__client =
{
	.name = "client",
	.flags = OVPN_OPT_FLAG_NORMAL
};

/* ----------------------------------------------------------------------- */

static const ovpn_opt_info_t ovpn__client_cert_not_required =
{
	.name = "client-cert-not-required",
	.flags = OVPN_OPT_FLAG_NORMAL |
	         OVPN_OPT_FLAG_DEPRECATED
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(client_config_dir, 1, OVPN_OPT_ARG_TYPE_DIR);
OVPN_OPT_DEF_ARG(client_config_dir, 1, "dir", false);

OVPN_OPT_DEF_ARGS_BEGIN(client_config_dir)
OVPN_OPT_DEF_ARGS_ARG(client_config_dir, 1)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__client_config_dir =
{
	.name = "client-config-dir",
	.flags = OVPN_OPT_FLAG_NORMAL,
	.args = {
		/* dir */
		.min = 1,
		.max = 1,
		.info = OVPN_OPT_REF_ARGS(client_config_dir)
	},
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(client_connect, 1, OVPN_OPT_ARG_TYPE_COMMAND);
OVPN_OPT_DEF_ARG(client_connect, 1, "cmd", false);

OVPN_OPT_DEF_ARGS_BEGIN(client_connect)
OVPN_OPT_DEF_ARGS_ARG(client_connect, 1)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__client_connect =
{
	.name = "client-connect",
	.flags = OVPN_OPT_FLAG_NORMAL,
	.args = {
		/* cmd */
		.min = 1,
		.max = 1,
		.info = OVPN_OPT_REF_ARGS(client_connect)
	},
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(client_disconnect, 1, OVPN_OPT_ARG_TYPE_COMMAND);
OVPN_OPT_DEF_ARG(client_disconnect, 1, "cmd", false);

OVPN_OPT_DEF_ARGS_BEGIN(client_disconnect)
OVPN_OPT_DEF_ARGS_ARG(client_disconnect, 1)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__client_disconnect =
{
	.name = "client-disconnect",
	.flags = OVPN_OPT_FLAG_NORMAL,
	.args = {
		/* cmd */
		.min = 1,
		.max = 1,
		.info = OVPN_OPT_REF_ARGS(client_disconnect)
	},
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(client_nat, 1, OVPN_OPT_ARG_TYPE_LISTVALUE);
OVPN_OPT_DEF_ARG_LV(client_nat, 1, "nat", false,
	"snat", "dnat");

OVPN_OPT_DEF_ARG_TYPES(client_nat, 2, OVPN_OPT_ARG_TYPE_NETWORK);
OVPN_OPT_DEF_ARG(client_nat, 2, "network", false);

OVPN_OPT_DEF_ARG_TYPES(client_nat, 3, OVPN_OPT_ARG_TYPE_NETMASK);
OVPN_OPT_DEF_ARG(client_nat, 3, "netmask", false);

OVPN_OPT_DEF_ARG_TYPES(client_nat, 4, OVPN_OPT_ARG_TYPE_NETWORK);
OVPN_OPT_DEF_ARG(client_nat, 4, "alias", false);

OVPN_OPT_DEF_ARGS_BEGIN(client_nat)
OVPN_OPT_DEF_ARGS_ARG(client_nat, 1)
OVPN_OPT_DEF_ARGS_ARG(client_nat, 2)
OVPN_OPT_DEF_ARGS_ARG(client_nat, 3)
OVPN_OPT_DEF_ARGS_ARG(client_nat, 4)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__client_nat =
{
	.name = "client-nat",
	.flags = OVPN_OPT_FLAG_NORMAL,
	.args = {
		/* snat|dnat network netmask alias */
		.min = 4,
		.max = 4,
		.info = OVPN_OPT_REF_ARGS(client_nat)
	},
};

/* ----------------------------------------------------------------------- */

static const ovpn_opt_info_t ovpn__client_to_client =
{
	.name = "client-to-client",
	.flags = OVPN_OPT_FLAG_NORMAL
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(compat_names, 1, OVPN_OPT_ARG_TYPE_STRING);
OVPN_OPT_DEF_ARG(compat_names, 1, "names", false);

OVPN_OPT_DEF_ARGS_BEGIN(compat_names)
OVPN_OPT_DEF_ARGS_ARG(compat_names, 1)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__compat_names =
{
	.name = "compat-names",
	.flags = OVPN_OPT_FLAG_NORMAL |
	         OVPN_OPT_FLAG_DEPRECATED,
	.args = {
		/* [no-remapping] */
		.min = 1,
		.max = OVPN_OPT_ARGS_NOT_LIMITED,
		.info = OVPN_OPT_REF_ARGS(compat_names)
	},
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(comp_lzo, 1, OVPN_OPT_ARG_TYPE_LISTVALUE);
OVPN_OPT_DEF_ARG_LV(comp_lzo, 1, "mode", true,
	"yes", "no", "adaptive");

OVPN_OPT_DEF_ARGS_BEGIN(comp_lzo)
OVPN_OPT_DEF_ARGS_ARG(comp_lzo, 1)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__comp_lzo =
{
	.name = "comp-lzo",
	.flags = OVPN_OPT_FLAG_NORMAL |
	         OVPN_OPT_FLAG_DEPRECATED |
	         OVPN_OPT_FLAG_PUSHABLE,
	.args = {
		/* [mode] */
		.min = 0,
		.max = 1,
		.info = OVPN_OPT_REF_ARGS(comp_lzo)
	},
};

/* ----------------------------------------------------------------------- */

static const ovpn_opt_info_t ovpn__comp_noadapt =
{
	.name = "comp-noadapt",
	.flags = OVPN_OPT_FLAG_NORMAL
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(compress, 1, OVPN_OPT_ARG_TYPE_LISTVALUE);
OVPN_OPT_DEF_ARG_LV(compress, 1, "algorithm", true,
	"lzo", "lz4");

OVPN_OPT_DEF_ARGS_BEGIN(compress)
OVPN_OPT_DEF_ARGS_ARG(compress, 1)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__compress =
{
	.name = "compress",
	.flags = OVPN_OPT_FLAG_NORMAL,
	.args = {
		/* [compress] */
		.min = 0,
		.max = 1,
		.info = OVPN_OPT_REF_ARGS(compress)
	},
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(connect_freq, 1, OVPN_OPT_ARG_TYPE_UNUMBER);
OVPN_OPT_DEF_ARG(connect_freq, 1, "n", false);

OVPN_OPT_DEF_ARG_TYPES(connect_freq, 2, OVPN_OPT_ARG_TYPE_UNUMBER);
OVPN_OPT_DEF_ARG(connect_freq, 2, "sec", false);

OVPN_OPT_DEF_ARGS_BEGIN(connect_freq)
OVPN_OPT_DEF_ARGS_ARG(connect_freq, 1)
OVPN_OPT_DEF_ARGS_ARG(connect_freq, 2)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__connect_freq =
{
	.name = "connect-freq",
	.flags = OVPN_OPT_FLAG_NORMAL,
	.args = {
		/* n sec */
		.min = 2,
		.max = 2,
		.info = OVPN_OPT_REF_ARGS(connect_freq)
	},
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(connect_retry, 1, OVPN_OPT_ARG_TYPE_UNUMBER);
OVPN_OPT_DEF_ARG(connect_retry, 1, "n", false);

OVPN_OPT_DEF_ARG_TYPES(connect_retry, 2, OVPN_OPT_ARG_TYPE_UNUMBER);
OVPN_OPT_DEF_ARG(connect_retry, 2, "max", true);

OVPN_OPT_DEF_ARGS_BEGIN(connect_retry)
OVPN_OPT_DEF_ARGS_ARG(connect_retry, 1)
OVPN_OPT_DEF_ARGS_ARG(connect_retry, 2)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__connect_retry =
{
	.name = "connect-retry",
	.flags = OVPN_OPT_FLAG_NORMAL |
	         OVPN_OPT_FLAG_CONNECTION,
	.args = {
		/* n [max] */
		.min = 1,
		.max = 2,
		.info = OVPN_OPT_REF_ARGS(connect_retry)
	},
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(connect_retry_max, 1, OVPN_OPT_ARG_TYPE_UNUMBER);
OVPN_OPT_DEF_ARG(connect_retry_max, 1, "n", false);

OVPN_OPT_DEF_ARGS_BEGIN(connect_retry_max)
OVPN_OPT_DEF_ARGS_ARG(connect_retry_max, 1)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__connect_retry_max =
{
	.name = "connect-retry-max",
	.flags = OVPN_OPT_FLAG_NORMAL |
	         OVPN_OPT_FLAG_CONNECTION,
	.args = {
		/* n */
		.min = 1,
		.max = 1,
		.info = OVPN_OPT_REF_ARGS(connect_retry_max)
	},
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(connect_timeout, 1, OVPN_OPT_ARG_TYPE_UNUMBER);
OVPN_OPT_DEF_ARG(connect_timeout, 1, "n", false);

OVPN_OPT_DEF_ARGS_BEGIN(connect_timeout)
OVPN_OPT_DEF_ARGS_ARG(connect_timeout, 1)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__connect_timeout =
{
	.name = "connect-timeout",
	.flags = OVPN_OPT_FLAG_NORMAL |
	         OVPN_OPT_FLAG_CONNECTION,
	.args = {
		/* n */
		.min = 1,
		.max = 1,
		.info = OVPN_OPT_REF_ARGS(connect_timeout)
	},
};

/* ----------------------------------------------------------------------- */

static const ovpn_opt_info_t ovpn__connection =
{
	.name = "connection",
	.flags = OVPN_OPT_FLAG_INLINE,
	.inline_type = OVPN_OPT_INLINE_TYPE_OPTIONS,
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(crl_verify, 1,
	OVPN_OPT_ARG_TYPE_FILEPATH, OVPN_OPT_ARG_TYPE_DIR);

OVPN_OPT_DEF_ARG(crl_verify, 1, "crl", false);

OVPN_OPT_DEF_ARG_TYPES(crl_verify, 2, OVPN_OPT_ARG_TYPE_LISTVALUE);
OVPN_OPT_DEF_ARG_LV(crl_verify, 2, "dir", true, "dir");

OVPN_OPT_DEF_ARGS_BEGIN(crl_verify)
OVPN_OPT_DEF_ARGS_ARG(crl_verify, 1)
OVPN_OPT_DEF_ARGS_ARG(crl_verify, 2)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__crl_verify =
{
	.name = "crl-verify",
	.flags = OVPN_OPT_FLAG_NORMAL |
	         OVPN_OPT_FLAG_INLINE,
	.inline_type = OVPN_OPT_INLINE_TYPE_PLAIN,
	.args = {
		/* crl ['dir'] */
		.min = 1,
		.max = 2,
		.info = OVPN_OPT_REF_ARGS(crl_verify)
	},
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(cryptoapicert, 1, OVPN_OPT_ARG_TYPE_STRING);
OVPN_OPT_DEF_ARG(cryptoapicert, 1, "select-string", false);

OVPN_OPT_DEF_ARGS_BEGIN(cryptoapicert)
OVPN_OPT_DEF_ARGS_ARG(cryptoapicert, 1)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__cryptoapicert =
{
	.name = "cryptoapicert",
	.flags = OVPN_OPT_FLAG_NORMAL,
	.args = {
		/* select-string */
		.min = 1,
		.max = 1,
		.info = OVPN_OPT_REF_ARGS(cryptoapicert)
	},
};

/* ----------------------------------------------------------------------- */

/*
 *  _____
 * |  __ \
 * | |  | |
 * | |  | |
 * | |__| |
 * |_____/
 *
 */

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(daemon, 1, OVPN_OPT_ARG_TYPE_STRING);
OVPN_OPT_DEF_ARG(daemon, 1, "progname", true);

OVPN_OPT_DEF_ARGS_BEGIN(daemon)
OVPN_OPT_DEF_ARGS_ARG(daemon, 1)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__daemon =
{
	.name = "daemon",
	.flags = OVPN_OPT_FLAG_NORMAL,
	.args = {
		/* [progname] */
		.min = 0,
		.max = 1,
		.info = OVPN_OPT_REF_ARGS(daemon)
	},
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(dev, 1, OVPN_OPT_ARG_TYPE_TUNTAP_DEVICE);
OVPN_OPT_DEF_ARG(dev, 1, "device", false);

OVPN_OPT_DEF_ARGS_BEGIN(dev)
OVPN_OPT_DEF_ARGS_ARG(dev, 1)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__dev =
{
	.name = "dev",
	.flags = OVPN_OPT_FLAG_NORMAL,
	.args = {
		/* tunX | tapX */
		.min = 1,
		.max = 1,
		.info = OVPN_OPT_REF_ARGS(dev)
	},
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(dev_node, 1, OVPN_OPT_ARG_TYPE_STRING);
OVPN_OPT_DEF_ARG(dev_node, 1, "node", false);

OVPN_OPT_DEF_ARGS_BEGIN(dev_node)
OVPN_OPT_DEF_ARGS_ARG(dev_node, 1)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__dev_node =
{
	.name = "dev-node",
	.flags = OVPN_OPT_FLAG_NORMAL,
	.args = {
		/* node */
		.min = 1,
		.max = 1,
		.info = OVPN_OPT_REF_ARGS(dev_node)
	},
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(dev_type, 1, OVPN_OPT_ARG_TYPE_LISTVALUE);
OVPN_OPT_DEF_ARG_LV(dev_type, 1, "device-type", false, "tun", "tap");

OVPN_OPT_DEF_ARGS_BEGIN(dev_type)
OVPN_OPT_DEF_ARGS_ARG(dev_type, 1)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__dev_type =
{
	.name = "dev-type",
	.flags = OVPN_OPT_FLAG_NORMAL,
	.args = {
		/* device-type */
		.min = 1,
		.max = 1,
		.info = OVPN_OPT_REF_ARGS(dev_type)
	},
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(dh, 1, OVPN_OPT_ARG_TYPE_FILEPATH);
OVPN_OPT_DEF_ARG(dh, 1, "file", false);

OVPN_OPT_DEF_ARGS_BEGIN(dh)
OVPN_OPT_DEF_ARGS_ARG(dh, 1)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__dh =
{
	.name = "dh",
	.flags = OVPN_OPT_FLAG_NORMAL |
	         OVPN_OPT_FLAG_INLINE,
	.inline_type = OVPN_OPT_INLINE_TYPE_PLAIN,
	.args = {
		/* file */
		.min = 1,
		.max = 1,
		.info = OVPN_OPT_REF_ARGS(dh)
	},
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(dhcp_option, 1, OVPN_OPT_ARG_TYPE_LISTVALUE);
OVPN_OPT_DEF_ARG_LV(dhcp_option, 1, "type", false,
	"DOMAIN", "DNS", "WINS", "NBDD", "NTP", "NBT", "NBS", "DISABLE-NTB");

OVPN_OPT_DEF_ARG_TYPES(dhcp_option, 2, OVPN_OPT_ARG_TYPE_STRING);
OVPN_OPT_DEF_ARG(dhcp_option, 2, "parm", true);

OVPN_OPT_DEF_ARGS_BEGIN(dhcp_option)
OVPN_OPT_DEF_ARGS_ARG(dhcp_option, 1)
OVPN_OPT_DEF_ARGS_ARG(dhcp_option, 2)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__dhcp_option =
{
	.name = "dhcp-option",
	.flags = OVPN_OPT_FLAG_NORMAL |
	         OVPN_OPT_FLAG_WINDOWS |
	         OVPN_OPT_FLAG_PUSHABLE |
	         OVPN_OPT_FLAG_MULTIPLE,
	.args = {
		/* type [parm] */
		.min = 1,
		.max = 2,
		.info = OVPN_OPT_REF_ARGS(dhcp_option)
	},
};

/* ----------------------------------------------------------------------- */

static const ovpn_opt_info_t ovpn__dhcp_release =
{
	.name = "dhcp-release",
	.flags = OVPN_OPT_FLAG_NORMAL |
	         OVPN_OPT_FLAG_WINDOWS
};

/* ----------------------------------------------------------------------- */

static const ovpn_opt_info_t ovpn__dhcp_renew =
{
	.name = "dhcp-renew",
	.flags = OVPN_OPT_FLAG_NORMAL |
	         OVPN_OPT_FLAG_WINDOWS
};

/* ----------------------------------------------------------------------- */

static const ovpn_opt_info_t ovpn__disable =
{
	.name = "disable",
	.flags = OVPN_OPT_FLAG_NORMAL
};

/* ----------------------------------------------------------------------- */

static const ovpn_opt_info_t ovpn__disable_occ =
{
	.name = "disable-occ",
	.flags = OVPN_OPT_FLAG_NORMAL
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(down, 1, OVPN_OPT_ARG_TYPE_COMMAND);
OVPN_OPT_DEF_ARG(down, 1, "type", false);

OVPN_OPT_DEF_ARGS_BEGIN(down)
OVPN_OPT_DEF_ARGS_ARG(down, 1)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__down =
{
	.name = "down",
	.flags = OVPN_OPT_FLAG_NORMAL,
	.args = {
		/* cmd */
		.min = 1,
		.max = 1,
		.info = OVPN_OPT_REF_ARGS(down)
	},
};

/* ----------------------------------------------------------------------- */

static const ovpn_opt_info_t ovpn__down_pre =
{
	.name = "down-pre",
	.flags = OVPN_OPT_FLAG_NORMAL
};

/* ----------------------------------------------------------------------- */

static const ovpn_opt_info_t ovpn__duplicate_cn =
{
	.name = "duplicate-cn",
	.flags = OVPN_OPT_FLAG_NORMAL
};

/* ----------------------------------------------------------------------- */

/*
 *  ______
 * |  ____|
 * | |__
 * |  __|
 * | |____
 * |______|
 *
 */

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(ecdh_curve, 1, OVPN_OPT_ARG_TYPE_STRING);
OVPN_OPT_DEF_ARG(ecdh_curve, 1, "name", false);

OVPN_OPT_DEF_ARGS_BEGIN(ecdh_curve)
OVPN_OPT_DEF_ARGS_ARG(ecdh_curve, 1)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__ecdh_curve =
{
	.name = "ecdh-curve",
	.flags = OVPN_OPT_FLAG_NORMAL,
	.args = {
		/* name */
		.min = 1,
		.max = 1,
		.info = OVPN_OPT_REF_ARGS(ecdh_curve)
	},
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(echo, 1, OVPN_OPT_ARG_TYPE_STRING);
OVPN_OPT_DEF_ARG(echo, 1, "parms", true);

OVPN_OPT_DEF_ARGS_BEGIN(echo)
OVPN_OPT_DEF_ARGS_ARG(echo, 1)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__echo =
{
	.name = "echo",
	.flags = OVPN_OPT_FLAG_NORMAL |
	         OVPN_OPT_FLAG_PUSHABLE,
	.args = {
		/* [parms...] */
		.min = 0,
		.max = OVPN_OPT_ARGS_NOT_LIMITED, /* not limited */
		.info = OVPN_OPT_REF_ARGS(echo)
	},
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(engine, 1, OVPN_OPT_ARG_TYPE_STRING);
OVPN_OPT_DEF_ARG(engine, 1, "engine-name", true);

OVPN_OPT_DEF_ARGS_BEGIN(engine)
OVPN_OPT_DEF_ARGS_ARG(engine, 1)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__engine =
{
	.name = "engine",
	.flags = OVPN_OPT_FLAG_NORMAL,
	.args = {
		/* [engine-name] */
		.min = 0,
		.max = 1,
		.info = OVPN_OPT_REF_ARGS(engine)
	},
};

/* ----------------------------------------------------------------------- */

static const ovpn_opt_info_t ovpn__errors_to_stderr =
{
	.name = "errors-to-stderr",
	.flags = OVPN_OPT_FLAG_NORMAL
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(explicit_exit_notify, 1, OVPN_OPT_ARG_TYPE_UNUMBER);
OVPN_OPT_DEF_ARG(explicit_exit_notify, 1, "n", true);

OVPN_OPT_DEF_ARGS_BEGIN(explicit_exit_notify)
OVPN_OPT_DEF_ARGS_ARG(explicit_exit_notify, 1)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__explicit_exit_notify =
{
	.name = "explicit-exit-notify",
	.flags = OVPN_OPT_FLAG_NORMAL |
	         OVPN_OPT_FLAG_CONNECTION,
	.args = {
		/* [n] */
		.min = 0,
		.max = 1,
		.info = OVPN_OPT_REF_ARGS(explicit_exit_notify)
	},
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(extra_certs, 1, OVPN_OPT_ARG_TYPE_FILEPATH);
OVPN_OPT_DEF_ARG(extra_certs, 1, "file", false);

OVPN_OPT_DEF_ARGS_BEGIN(extra_certs)
OVPN_OPT_DEF_ARGS_ARG(extra_certs, 1)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__extra_certs =
{
	.name = "extra-certs",
	.flags = OVPN_OPT_FLAG_NORMAL |
	         OVPN_OPT_FLAG_INLINE,
	.inline_type = OVPN_OPT_INLINE_TYPE_PLAIN,
	.args = {
		/* file */
		.min = 1,
		.max = 1,
		.info = OVPN_OPT_REF_ARGS(extra_certs)
	},
};

/* ----------------------------------------------------------------------- */

/*
 *  ______
 * |  ____|
 * | |__
 * |  __|
 * | |
 * |_|
 *
 */

/* ----------------------------------------------------------------------- */

static const ovpn_opt_info_t ovpn__fast_io =
{
	.name = "fast-io",
	.flags = OVPN_OPT_FLAG_NORMAL
};

/* ----------------------------------------------------------------------- */

static const ovpn_opt_info_t ovpn__float =
{
	.name = "float",
	.flags = OVPN_OPT_FLAG_NORMAL |
	         OVPN_OPT_FLAG_CONNECTION
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(fragment, 1, OVPN_OPT_ARG_TYPE_UNUMBER);
OVPN_OPT_DEF_ARG(fragment, 1, "max", false);

OVPN_OPT_DEF_ARGS_BEGIN(fragment)
OVPN_OPT_DEF_ARGS_ARG(fragment, 1)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__fragment =
{
	.name = "fragment",
	.flags = OVPN_OPT_FLAG_NORMAL |
	         OVPN_OPT_FLAG_CONNECTION,
	.args = {
		/* max */
		.min = 1,
		.max = 1,
		.info = OVPN_OPT_REF_ARGS(fragment)
	},
};

/* ----------------------------------------------------------------------- */

/*
 *   _____
 *  / ____|
 * | |  __
 * | | |_ |
 * | |__| |
 *  \_____|
 *
 */

/* ----------------------------------------------------------------------- */

static const ovpn_opt_info_t ovpn__genkey =
{
	.name = "genkey",
	.flags = OVPN_OPT_FLAG_NORMAL |
	         OVPN_OPT_FLAG_STANDALONE
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(group, 1, OVPN_OPT_ARG_TYPE_STRING);
OVPN_OPT_DEF_ARG(group, 1, "group", false);

OVPN_OPT_DEF_ARGS_BEGIN(group)
OVPN_OPT_DEF_ARGS_ARG(group, 1)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__group =
{
	.name = "group",
	.flags = OVPN_OPT_FLAG_NORMAL,
	.args = {
		/* group */
		.min = 1,
		.max = 1,
		.info = OVPN_OPT_REF_ARGS(group)
	},
};

/* ----------------------------------------------------------------------- */

/*
 *  _    _
 * | |  | |
 * | |__| |
 * |  __  |
 * | |  | |
 * |_|  |_|
 *
 */

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(hand_window, 1, OVPN_OPT_ARG_TYPE_UNUMBER);
OVPN_OPT_DEF_ARG(hand_window, 1, "n", false);

OVPN_OPT_DEF_ARGS_BEGIN(hand_window)
OVPN_OPT_DEF_ARGS_ARG(hand_window, 1)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__hand_window =
{
	.name = "hand-window",
	.flags = OVPN_OPT_FLAG_NORMAL,
	.args = {
		/* n */
		.min = 1,
		.max = 1,
		.info = OVPN_OPT_REF_ARGS(hand_window)
	},
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(hash_size, 1, OVPN_OPT_ARG_TYPE_UNUMBER);
OVPN_OPT_DEF_ARG(hash_size, 1, "r", false);

OVPN_OPT_DEF_ARG_TYPES(hash_size, 2, OVPN_OPT_ARG_TYPE_UNUMBER);
OVPN_OPT_DEF_ARG(hash_size, 2, "v", false);

OVPN_OPT_DEF_ARGS_BEGIN(hash_size)
OVPN_OPT_DEF_ARGS_ARG(hash_size, 1)
OVPN_OPT_DEF_ARGS_ARG(hash_size, 2)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__hash_size =
{
	.name = "hash-size",
	.flags = OVPN_OPT_FLAG_NORMAL,
	.args = {
		/* r v */
		.min = 2,
		.max = 2,
		.info = OVPN_OPT_REF_ARGS(hash_size)
	},
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(http_proxy, 1, OVPN_OPT_ARG_TYPE_ADDRESS);
OVPN_OPT_DEF_ARG(http_proxy, 1, "server", false);

OVPN_OPT_DEF_ARG_TYPES(http_proxy, 2, OVPN_OPT_ARG_TYPE_PORT);
OVPN_OPT_DEF_ARG(http_proxy, 2, "port", false);

OVPN_OPT_DEF_ARG_TYPES(http_proxy, 3,
	OVPN_OPT_ARG_TYPE_FILEPATH, OVPN_OPT_ARG_TYPE_LISTVALUE);
OVPN_OPT_DEF_ARG_LV(http_proxy, 3, "authfile", true,
	"auto", "auto-nct");

OVPN_OPT_DEF_ARG_TYPES(http_proxy, 4, OVPN_OPT_ARG_TYPE_LISTVALUE);
OVPN_OPT_DEF_ARG_LV(http_proxy, 4, "auth-method", true,
	"none", "basic", "ntlm");

OVPN_OPT_DEF_ARGS_BEGIN(http_proxy)
OVPN_OPT_DEF_ARGS_ARG(http_proxy, 1)
OVPN_OPT_DEF_ARGS_ARG(http_proxy, 2)
OVPN_OPT_DEF_ARGS_ARG(http_proxy, 3)
OVPN_OPT_DEF_ARGS_ARG(http_proxy, 4)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__http_proxy =
{
	.name = "http-proxy",
	.flags = OVPN_OPT_FLAG_NORMAL |
	         OVPN_OPT_FLAG_CONNECTION,
	.args = {
		/* server port [authfile|'auto'|'auto-nct'] [auth-method] */
		.min = 2,
		.max = 4,
		.info = OVPN_OPT_REF_ARGS(http_proxy)
	},
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(http_proxy_option, 1, OVPN_OPT_ARG_TYPE_LISTVALUE);
OVPN_OPT_DEF_ARG_LV(http_proxy_option, 1, "type", false,
	"VERSION", "AGENT", "CUSTOM-HEADER");

OVPN_OPT_DEF_ARG_TYPES(http_proxy_option, 2, OVPN_OPT_ARG_TYPE_STRING);
OVPN_OPT_DEF_ARG(http_proxy_option, 2, "parm", true);

OVPN_OPT_DEF_ARGS_BEGIN(http_proxy_option)
OVPN_OPT_DEF_ARGS_ARG(http_proxy_option, 1)
OVPN_OPT_DEF_ARGS_ARG(http_proxy_option, 2)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__http_proxy_option =
{
	.name = "http-proxy-option",
	.flags = OVPN_OPT_FLAG_NORMAL |
	         OVPN_OPT_FLAG_CONNECTION |
	         OVPN_OPT_FLAG_MULTIPLE,
	.args = {
		/* type [parm] */
		.min = 1,
		.max = 2,
		.info = OVPN_OPT_REF_ARGS(http_proxy_option)
	},
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(http_proxy_user_pass, 1, OVPN_OPT_ARG_TYPE_FILEPATH);
OVPN_OPT_DEF_ARG(http_proxy_user_pass, 1, "file", false);

OVPN_OPT_DEF_ARGS_BEGIN(http_proxy_user_pass)
OVPN_OPT_DEF_ARGS_ARG(http_proxy_user_pass, 1)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__http_proxy_user_pass =
{
	.name = "http-proxy-user-pass",
	.flags = OVPN_OPT_FLAG_NORMAL |
	         OVPN_OPT_FLAG_INLINE,
	.inline_type = OVPN_OPT_INLINE_TYPE_PLAIN,
	.args = {
		/* file */
		.min = 1,
		.max = 1,
		.info = OVPN_OPT_REF_ARGS(http_proxy_user_pass)
	},
};

/* ----------------------------------------------------------------------- */

/*
 *  _____
 * |_   _|
 *   | |
 *   | |
 *  _| |_
 * |_____|
 *
 */

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(ifconfig, 1, OVPN_OPT_ARG_TYPE_IPADDR);
OVPN_OPT_DEF_ARG(ifconfig, 1, "l", false);

OVPN_OPT_DEF_ARG_TYPES(ifconfig, 2, OVPN_OPT_ARG_TYPE_NETMASK);
OVPN_OPT_DEF_ARG(ifconfig, 2, "rn", false);

OVPN_OPT_DEF_ARGS_BEGIN(ifconfig)
OVPN_OPT_DEF_ARGS_ARG(ifconfig, 1)
OVPN_OPT_DEF_ARGS_ARG(ifconfig, 2)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__ifconfig =
{
	.name = "ifconfig",
	.flags = OVPN_OPT_FLAG_NORMAL,
	.args = {
		/* l rn */
		.min = 2,
		.max = 2,
		.info = OVPN_OPT_REF_ARGS(ifconfig)
	},
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(ifconfig_ipv6, 1, OVPN_OPT_ARG_TYPE_IPV6ADDR);
OVPN_OPT_DEF_ARG(ifconfig_ipv6, 1, "ipv6addr/bits", false);

OVPN_OPT_DEF_ARG_TYPES(ifconfig_ipv6, 2, OVPN_OPT_ARG_TYPE_IPV6ADDR);
OVPN_OPT_DEF_ARG(ifconfig_ipv6, 2, "ipv6remote", false);

OVPN_OPT_DEF_ARGS_BEGIN(ifconfig_ipv6)
OVPN_OPT_DEF_ARGS_ARG(ifconfig_ipv6, 1)
OVPN_OPT_DEF_ARGS_ARG(ifconfig_ipv6, 2)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__ifconfig_ipv6 =
{
	.name = "ifconfig-ipv6",
	.flags = OVPN_OPT_FLAG_NORMAL |
	         OVPN_OPT_FLAG_IPV6,
	.args = {
		/* ipv6addr/bits ipv6remote */
		.min = 2,
		.max = 2,
		.info = OVPN_OPT_REF_ARGS(ifconfig_ipv6)
	},
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(ifconfig_ipv6_pool, 1, OVPN_OPT_ARG_TYPE_IPV6ADDR);
OVPN_OPT_DEF_ARG(ifconfig_ipv6_pool, 1, "ipv6addr/bits", false);

OVPN_OPT_DEF_ARGS_BEGIN(ifconfig_ipv6_pool)
OVPN_OPT_DEF_ARGS_ARG(ifconfig_ipv6_pool, 1)
OVPN_OPT_DEF_ARGS_END()


static const ovpn_opt_info_t ovpn__ifconfig_ipv6_pool =
{
	.name = "ifconfig-ipv6-pool",
	.flags = OVPN_OPT_FLAG_NORMAL |
	         OVPN_OPT_FLAG_IPV6,
	.args = {
		/* ipv6addr/bits */
		.min = 1,
		.max = 1,
		.info = OVPN_OPT_REF_ARGS(ifconfig_ipv6_pool)
	},
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(ifconfig_ipv6_push, 1, OVPN_OPT_ARG_TYPE_IPV6ADDR);
OVPN_OPT_DEF_ARG(ifconfig_ipv6_push, 1, "ipv6addr/bits", false);

OVPN_OPT_DEF_ARG_TYPES(ifconfig_ipv6_push, 2, OVPN_OPT_ARG_TYPE_IPV6ADDR);
OVPN_OPT_DEF_ARG(ifconfig_ipv6_push, 2, "ipv6remote", false);

OVPN_OPT_DEF_ARGS_BEGIN(ifconfig_ipv6_push)
OVPN_OPT_DEF_ARGS_ARG(ifconfig_ipv6_push, 1)
OVPN_OPT_DEF_ARGS_ARG(ifconfig_ipv6_push, 2)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__ifconfig_ipv6_push =
{
	.name = "ifconfig-ipv6-push",
	.flags = OVPN_OPT_FLAG_NORMAL |
	         OVPN_OPT_FLAG_IPV6,
	.args = {
		/* ipv6addr/bits ipv6remote */
		.min = 2,
		.max = 2,
		.info = OVPN_OPT_REF_ARGS(ifconfig_ipv6_push)
	},
};

/* ----------------------------------------------------------------------- */

static const ovpn_opt_info_t ovpn__ifconfig_noexec =
{
	.name = "ifconfig-noexec",
	.flags = OVPN_OPT_FLAG_NORMAL
};

/* ----------------------------------------------------------------------- */

static const ovpn_opt_info_t ovpn__ifconfig_nowarn =
{
	.name = "ifconfig-nowarn",
	.flags = OVPN_OPT_FLAG_NORMAL
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(ifconfig_pool, 1, OVPN_OPT_ARG_TYPE_IPADDR);
OVPN_OPT_DEF_ARG(ifconfig_pool, 1, "start-IP", false);

OVPN_OPT_DEF_ARG_TYPES(ifconfig_pool, 2, OVPN_OPT_ARG_TYPE_IPADDR);
OVPN_OPT_DEF_ARG(ifconfig_pool, 2, "end-IP", false);

OVPN_OPT_DEF_ARG_TYPES(ifconfig_pool, 3, OVPN_OPT_ARG_TYPE_NETMASK);
OVPN_OPT_DEF_ARG(ifconfig_pool, 3, "netmask", true);

OVPN_OPT_DEF_ARGS_BEGIN(ifconfig_pool)
OVPN_OPT_DEF_ARGS_ARG(ifconfig_pool, 1)
OVPN_OPT_DEF_ARGS_ARG(ifconfig_pool, 2)
OVPN_OPT_DEF_ARGS_ARG(ifconfig_pool, 3)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__ifconfig_pool =
{
	.name = "ifconfig-pool",
	.flags = OVPN_OPT_FLAG_NORMAL,
	.args = {
		/* start-IP end-IP [netmask] */
		.min = 2,
		.max = 3,
		.info = OVPN_OPT_REF_ARGS(ifconfig_pool)
	},
};

/* ----------------------------------------------------------------------- */

static const ovpn_opt_info_t ovpn__ifconfig_pool_linear =
{
	.name = "ifconfig-pool-linear",
	.flags = OVPN_OPT_FLAG_NORMAL |
	         OVPN_OPT_FLAG_DEPRECATED
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(ifconfig_pool_persist, 1, OVPN_OPT_ARG_TYPE_FILEPATH);
OVPN_OPT_DEF_ARG(ifconfig_pool_persist, 1, "file", false);

OVPN_OPT_DEF_ARG_TYPES(ifconfig_pool_persist, 2, OVPN_OPT_ARG_TYPE_UNUMBER);
OVPN_OPT_DEF_ARG(ifconfig_pool_persist, 2, "seconds", true);

OVPN_OPT_DEF_ARGS_BEGIN(ifconfig_pool_persist)
OVPN_OPT_DEF_ARGS_ARG(ifconfig_pool_persist, 1)
OVPN_OPT_DEF_ARGS_ARG(ifconfig_pool_persist, 2)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__ifconfig_pool_persist =
{
	.name = "ifconfig-pool-persist",
	.flags = OVPN_OPT_FLAG_NORMAL,
	.args = {
		/* file [seconds] */
		.min = 1,
		.max = 2,
		.info = OVPN_OPT_REF_ARGS(ifconfig_pool_persist)
	},
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(ifconfig_push, 1, OVPN_OPT_ARG_TYPE_IPADDR);
OVPN_OPT_DEF_ARG(ifconfig_push, 1, "local", false);

OVPN_OPT_DEF_ARG_TYPES(ifconfig_push, 2, OVPN_OPT_ARG_TYPE_NETMASK);
OVPN_OPT_DEF_ARG(ifconfig_push, 2, "remote-netmask", false);

OVPN_OPT_DEF_ARG_TYPES(ifconfig_push, 3, OVPN_OPT_ARG_TYPE_STRING);
OVPN_OPT_DEF_ARG(ifconfig_push, 3, "alias", true);

OVPN_OPT_DEF_ARGS_BEGIN(ifconfig_push)
OVPN_OPT_DEF_ARGS_ARG(ifconfig_push, 1)
OVPN_OPT_DEF_ARGS_ARG(ifconfig_push, 2)
OVPN_OPT_DEF_ARGS_ARG(ifconfig_push, 3)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__ifconfig_push =
{
	.name = "ifconfig-push",
	.flags = OVPN_OPT_FLAG_NORMAL,
	.args = {
		/* local remote-netmask [alias] */
		.min = 2,
		.max = 3,
		.info = OVPN_OPT_REF_ARGS(ifconfig_push)
	},
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(ignore_unknown_option, 1, OVPN_OPT_ARG_TYPE_STRING);
OVPN_OPT_DEF_ARG(ignore_unknown_option, 1, "opt", false);

OVPN_OPT_DEF_ARGS_BEGIN(ignore_unknown_option)
OVPN_OPT_DEF_ARGS_ARG(ignore_unknown_option, 1)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__ignore_unknown_option =
{
	.name = "ignore-unknown-option",
	.flags = OVPN_OPT_FLAG_NORMAL |
	         OVPN_OPT_FLAG_MULTIPLE,
	.args = {
		/* opt1 opt2 opt3 ... optN */
		.min = 1,
		.max = OVPN_OPT_ARGS_NOT_LIMITED,
		.info = OVPN_OPT_REF_ARGS(ignore_unknown_option)
	},
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(inactive, 1, OVPN_OPT_ARG_TYPE_UNUMBER);
OVPN_OPT_DEF_ARG(inactive, 1, "n", false);

OVPN_OPT_DEF_ARG_TYPES(inactive, 2, OVPN_OPT_ARG_TYPE_UNUMBER);
OVPN_OPT_DEF_ARG(inactive, 2, "bytes", true);

OVPN_OPT_DEF_ARGS_BEGIN(inactive)
OVPN_OPT_DEF_ARGS_ARG(inactive, 1)
OVPN_OPT_DEF_ARGS_ARG(inactive, 2)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__inactive =
{
	.name = "inactive",
	.flags = OVPN_OPT_FLAG_NORMAL |
	         OVPN_OPT_FLAG_PUSHABLE,
	.args = {
		/* n [bytes] */
		.min = 1,
		.max = 2,
		.info = OVPN_OPT_REF_ARGS(inactive)
	},
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(ip_win32, 1, OVPN_OPT_ARG_TYPE_LISTVALUE);
OVPN_OPT_DEF_ARG_LV(ip_win32, 1, "method", false,
	"manual", "dynamic", "netsh", "ipapi", "adaptive");

OVPN_OPT_DEF_ARG_TYPES(ip_win32, 2, OVPN_OPT_ARG_TYPE_UNUMBER);
OVPN_OPT_DEF_ARG(ip_win32, 2, "offset", true);

OVPN_OPT_DEF_ARG_TYPES(ip_win32, 3, OVPN_OPT_ARG_TYPE_UNUMBER);
OVPN_OPT_DEF_ARG(ip_win32, 3, "lease-time", true);

OVPN_OPT_DEF_ARGS_BEGIN(ip_win32)
OVPN_OPT_DEF_ARGS_ARG(ip_win32, 1)
OVPN_OPT_DEF_ARGS_ARG(ip_win32, 2)
OVPN_OPT_DEF_ARGS_ARG(ip_win32, 3)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__ip_win32 =
{
	.name = "ip-win32",
	.flags = OVPN_OPT_FLAG_NORMAL |
	         OVPN_OPT_FLAG_WINDOWS |
	         OVPN_OPT_FLAG_PUSHABLE,
	.args = {
		/* method [offset] [lease-time] */
		.min = 1,
		.max = 3,
		.info = OVPN_OPT_REF_ARGS(ip_win32)
	},
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(ipchange, 1, OVPN_OPT_ARG_TYPE_COMMAND);
OVPN_OPT_DEF_ARG(ipchange, 1, "cmd", false);

OVPN_OPT_DEF_ARGS_BEGIN(ipchange)
OVPN_OPT_DEF_ARGS_ARG(ipchange, 1)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__ipchange =
{
	.name = "ipchange",
	.flags = OVPN_OPT_FLAG_NORMAL,
	.args = {
		/* cmd */
		.min = 1,
		.max = 1,
		.info = OVPN_OPT_REF_ARGS(ipchange)
	},
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(inetd, 1, OVPN_OPT_ARG_TYPE_LISTVALUE);
OVPN_OPT_DEF_ARG_LV(inetd, 1, "wait/nowait", true, "wait", "nowait");

OVPN_OPT_DEF_ARG_TYPES(inetd, 2, OVPN_OPT_ARG_TYPE_STRING);
OVPN_OPT_DEF_ARG(inetd, 2, "progname", true);

OVPN_OPT_DEF_ARGS_BEGIN(inetd)
OVPN_OPT_DEF_ARGS_ARG(inetd, 1)
OVPN_OPT_DEF_ARGS_ARG(inetd, 2)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__inetd =
{
	.name = "inetd",
	.flags = OVPN_OPT_FLAG_NORMAL,
	.args = {
		/* [wait|nowait] [progname] */
		.min = 0,
		.max = 2,
		.info = OVPN_OPT_REF_ARGS(inetd)
	},
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(iproute, 1, OVPN_OPT_ARG_TYPE_COMMAND);
OVPN_OPT_DEF_ARG(iproute, 1, "cmd", false);

OVPN_OPT_DEF_ARGS_BEGIN(iproute)
OVPN_OPT_DEF_ARGS_ARG(iproute, 1)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__iproute =
{
	.name = "iproute",
	.flags = OVPN_OPT_FLAG_NORMAL,
	.args = {
		/* cmd */
		.min = 1,
		.max = 1,
		.info = OVPN_OPT_REF_ARGS(iproute)
	},
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(iroute, 1, OVPN_OPT_ARG_TYPE_NETWORK);
OVPN_OPT_DEF_ARG(iroute, 1, "network", false);

OVPN_OPT_DEF_ARG_TYPES(iroute, 2, OVPN_OPT_ARG_TYPE_NETMASK);
OVPN_OPT_DEF_ARG(iroute, 2, "netmask", true);

OVPN_OPT_DEF_ARGS_BEGIN(iroute)
OVPN_OPT_DEF_ARGS_ARG(iroute, 1)
OVPN_OPT_DEF_ARGS_ARG(iroute, 2)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__iroute =
{
	.name = "iroute",
	.flags = OVPN_OPT_FLAG_NORMAL,
	.args = {
		/* network [netmask] */
		.min = 1,
		.max = 2,
		.info = OVPN_OPT_REF_ARGS(iroute)
	},
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(iroute_ipv6, 1, OVPN_OPT_ARG_TYPE_IPV6ADDR);
OVPN_OPT_DEF_ARG(iroute_ipv6, 1, "ipv6addr/bits", false);

OVPN_OPT_DEF_ARGS_BEGIN(iroute_ipv6)
OVPN_OPT_DEF_ARGS_ARG(iroute_ipv6, 1)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__iroute_ipv6 =
{
	.name = "iroute-ipv6",
	.flags = OVPN_OPT_FLAG_NORMAL |
	         OVPN_OPT_FLAG_IPV6,
	.args = {
		/* ipv6addr/bits */
		.min = 1,
		.max = 1,
		.info = OVPN_OPT_REF_ARGS(iroute_ipv6)
	},
};

/* ----------------------------------------------------------------------- */

/*
 *       _
 *      | |
 *      | |
 *  _   | |
 * | |__| |
 *  \____/
 *
 */

/* Nothing */

/*
 *  _  __
 * | |/ /
 * | ' /
 * |  <
 * | . \
 * |_|\_\
 *
 */

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(keepalive, 1, OVPN_OPT_ARG_TYPE_UNUMBER);
OVPN_OPT_DEF_ARG(keepalive, 1, "interval", false);

OVPN_OPT_DEF_ARG_TYPES(keepalive, 2, OVPN_OPT_ARG_TYPE_UNUMBER);
OVPN_OPT_DEF_ARG(keepalive, 2, "timeout", false);

OVPN_OPT_DEF_ARGS_BEGIN(keepalive)
OVPN_OPT_DEF_ARGS_ARG(keepalive, 1)
OVPN_OPT_DEF_ARGS_ARG(keepalive, 2)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__keepalive =
{
	.name = "keepalive",
	.flags = OVPN_OPT_FLAG_NORMAL,
	.args = {
		/* interval timeout */
		.min = 2,
		.max = 2,
		.info = OVPN_OPT_REF_ARGS(keepalive)
	},
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(key, 1, OVPN_OPT_ARG_TYPE_FILEPATH);
OVPN_OPT_DEF_ARG(key, 1, "file", false);

OVPN_OPT_DEF_ARGS_BEGIN(key)
OVPN_OPT_DEF_ARGS_ARG(key, 1)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__key =
{
	.name = "key",
	.inline_type = OVPN_OPT_INLINE_TYPE_PLAIN,
	.flags = OVPN_OPT_FLAG_NORMAL |
	         OVPN_OPT_FLAG_INLINE,
	.args = {
		/* file */
		.min = 1,
		.max = 1,
		.info = OVPN_OPT_REF_ARGS(key)
	},
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(key_direction, 1, OVPN_OPT_ARG_TYPE_STRING);
OVPN_OPT_DEF_ARG(key_direction, 1, "direction", false);

OVPN_OPT_DEF_ARGS_BEGIN(key_direction)
OVPN_OPT_DEF_ARGS_ARG(key_direction, 1)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__key_direction =
{
	.name = "key-direction",
	.flags = OVPN_OPT_FLAG_NORMAL,
	.args = {
		/* direction */
		.min = 1,
		.max = 1,
		.info = OVPN_OPT_REF_ARGS(key_direction)
	},
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(key_method, 1, OVPN_OPT_ARG_TYPE_STRING);
OVPN_OPT_DEF_ARG(key_method, 1, "m", false);

OVPN_OPT_DEF_ARGS_BEGIN(key_method)
OVPN_OPT_DEF_ARGS_ARG(key_method, 1)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__key_method =
{
	.name = "key-method",
	.flags = OVPN_OPT_FLAG_NORMAL |
	         OVPN_OPT_FLAG_DEPRECATED,
	.args = {
		/* m */
		.min = 1,
		.max = 1,
		.info = OVPN_OPT_REF_ARGS(key_method)
	},
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(keying_material_exporter, 1, OVPN_OPT_ARG_TYPE_STRING);
OVPN_OPT_DEF_ARG(keying_material_exporter, 1, "label", false);

OVPN_OPT_DEF_ARG_TYPES(keying_material_exporter, 2, OVPN_OPT_ARG_TYPE_UNUMBER);
OVPN_OPT_DEF_ARG_RANGE(keying_material_exporter, 2, "len", false, 16, 4095);

OVPN_OPT_DEF_ARGS_BEGIN(keying_material_exporter)
OVPN_OPT_DEF_ARGS_ARG(keying_material_exporter, 1)
OVPN_OPT_DEF_ARGS_ARG(keying_material_exporter, 2)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__keying_material_exporter =
{
	.name = "keying-material-exporter",
	.flags = OVPN_OPT_FLAG_NORMAL,
	.args = {
		/* label len */
		.min = 2,
		.max = 2,
		.info = OVPN_OPT_REF_ARGS(keying_material_exporter)
	},
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(keysize, 1, OVPN_OPT_ARG_TYPE_UNUMBER);
OVPN_OPT_DEF_ARG(keysize, 1, "n", false);

OVPN_OPT_DEF_ARGS_BEGIN(keysize)
OVPN_OPT_DEF_ARGS_ARG(keysize, 1)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__keysize =
{
	.name = "keysize",
	.flags = OVPN_OPT_FLAG_NORMAL |
	         OVPN_OPT_FLAG_DEPRECATED,
	.args = {
		/* n */
		.min = 1,
		.max = 1,
		.info = OVPN_OPT_REF_ARGS(keysize)
	},
};

/* ----------------------------------------------------------------------- */

/*
 *  _
 * | |
 * | |
 * | |
 * | |____
 * |______|
 *
 */

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(learn_address, 1, OVPN_OPT_ARG_TYPE_COMMAND);
OVPN_OPT_DEF_ARG(learn_address, 1, "cmd", false);

OVPN_OPT_DEF_ARGS_BEGIN(learn_address)
OVPN_OPT_DEF_ARGS_ARG(learn_address, 1)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__learn_address =
{
	.name = "learn-address",
	.flags = OVPN_OPT_FLAG_NORMAL,
	.args = {
		/* cmd */
		.min = 1,
		.max = 1,
		.info = OVPN_OPT_REF_ARGS(learn_address)
	},
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(link_mtu, 1, OVPN_OPT_ARG_TYPE_UNUMBER);
OVPN_OPT_DEF_ARG(link_mtu, 1, "n", false);

OVPN_OPT_DEF_ARGS_BEGIN(link_mtu)
OVPN_OPT_DEF_ARGS_ARG(link_mtu, 1)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__link_mtu =
{
	.name = "link-mtu",
	.flags = OVPN_OPT_FLAG_NORMAL |
	         OVPN_OPT_FLAG_CONNECTION,
	.args = {
		/* n */
		.min = 1,
		.max = 1,
		.info = OVPN_OPT_REF_ARGS(link_mtu)
	},
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(lladdr, 1, OVPN_OPT_ARG_TYPE_MACADDRESS);
OVPN_OPT_DEF_ARG(lladdr, 1, "address", false);

OVPN_OPT_DEF_ARGS_BEGIN(lladdr)
OVPN_OPT_DEF_ARGS_ARG(lladdr, 1)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__lladdr =
{
	.name = "lladdr",
	.flags = OVPN_OPT_FLAG_NORMAL,
	.args = {
		/* address */
		.min = 1,
		.max = 1,
		.info = OVPN_OPT_REF_ARGS(lladdr)
	},
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(local, 1, OVPN_OPT_ARG_TYPE_ADDRESS);
OVPN_OPT_DEF_ARG(local, 1, "host", false);

OVPN_OPT_DEF_ARGS_BEGIN(local)
OVPN_OPT_DEF_ARGS_ARG(local, 1)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__local =
{
	.name = "local",
	.flags = OVPN_OPT_FLAG_NORMAL |
	         OVPN_OPT_FLAG_CONNECTION,
	.args = {
		/* host */
		.min = 1,
		.max = 1,
		.info = OVPN_OPT_REF_ARGS(local)
	},
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(log, 1, OVPN_OPT_ARG_TYPE_FILEPATH);
OVPN_OPT_DEF_ARG(log, 1, "file", false);

OVPN_OPT_DEF_ARGS_BEGIN(log)
OVPN_OPT_DEF_ARGS_ARG(log, 1)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__log =
{
	.name = "log",
	.flags = OVPN_OPT_FLAG_NORMAL,
	.args = {
		/* file */
		.min = 1,
		.max = 1,
		.info = OVPN_OPT_REF_ARGS(log)
	},
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(log_append, 1, OVPN_OPT_ARG_TYPE_FILEPATH);
OVPN_OPT_DEF_ARG(log_append, 1, "file", false);

OVPN_OPT_DEF_ARGS_BEGIN(log_append)
OVPN_OPT_DEF_ARGS_ARG(log_append, 1)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__log_append =
{
	.name = "log-append",
	.flags = OVPN_OPT_FLAG_NORMAL,
	.args = {
		/* file */
		.min = 1,
		.max = 1,
		.info = OVPN_OPT_REF_ARGS(log_append)
	},
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(lport, 1, OVPN_OPT_ARG_TYPE_PORT);
OVPN_OPT_DEF_ARG(lport, 1, "port", false);

OVPN_OPT_DEF_ARGS_BEGIN(lport)
OVPN_OPT_DEF_ARGS_ARG(lport, 1)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__lport =
{
	.name = "lport",
	.flags = OVPN_OPT_FLAG_NORMAL |
	         OVPN_OPT_FLAG_CONNECTION,
	.args = {
		/* port */
		.min = 1,
		.max = 1,
		.info = OVPN_OPT_REF_ARGS(lport)
	},
};

/* ----------------------------------------------------------------------- */

/*
 *  __  __
 * |  \/  |
 * | \  / |
 * | |\/| |
 * | |  | |
 * |_|  |_|
 *
 */

/* ----------------------------------------------------------------------- */

static const ovpn_opt_info_t ovpn__machine_readable_output_client =
{
	.name = "machine-readable-output-client",
	.flags = OVPN_OPT_FLAG_NORMAL
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(management, 1,
	OVPN_OPT_ARG_TYPE_STRING, OVPN_OPT_ARG_TYPE_IPADDR);
OVPN_OPT_DEF_ARG(management, 1, "IP/socket-name", false);

OVPN_OPT_DEF_ARG_TYPES(management, 2,
	OVPN_OPT_ARG_TYPE_PORT, OVPN_OPT_ARG_TYPE_LISTVALUE);
OVPN_OPT_DEF_ARG_LV(management, 2, "port/unix", false, "unix");

OVPN_OPT_DEF_ARG_TYPES(management, 3,
	OVPN_OPT_ARG_TYPE_FILEPATH, OVPN_OPT_ARG_TYPE_LISTVALUE);
OVPN_OPT_DEF_ARG_LV(management, 3, "pw-file", true, "stdin");

OVPN_OPT_DEF_ARGS_BEGIN(management)
OVPN_OPT_DEF_ARGS_ARG(management, 1)
OVPN_OPT_DEF_ARGS_ARG(management, 2)
OVPN_OPT_DEF_ARGS_ARG(management, 3)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__management =
{
	.name = "management",
	.flags = OVPN_OPT_FLAG_NORMAL,
	.args = {
		/* socket-name unix [pw-file] */
		/* IP port [pw-file] */
		.min = 2,
		.max = 3,
		.info = OVPN_OPT_REF_ARGS(management)
	},
};

/* ----------------------------------------------------------------------- */

static const ovpn_opt_info_t ovpn__management_client =
{
	.name = "management-client",
	.flags = OVPN_OPT_FLAG_NORMAL
};

/* ----------------------------------------------------------------------- */

static const ovpn_opt_info_t ovpn__management_client_auth =
{
	.name = "management-client-auth",
	.flags = OVPN_OPT_FLAG_NORMAL
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(management_client_group, 1, OVPN_OPT_ARG_TYPE_STRING);
OVPN_OPT_DEF_ARG(management_client_group, 1, "g", false);

OVPN_OPT_DEF_ARGS_BEGIN(management_client_group)
OVPN_OPT_DEF_ARGS_ARG(management_client_group, 1)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__management_client_group =
{
	.name = "management-client-group",
	.flags = OVPN_OPT_FLAG_NORMAL,
	.args = {
		/* g */
		.min = 1,
		.max = 1,
		.info = OVPN_OPT_REF_ARGS(management_client_group)
	},
};

/* ----------------------------------------------------------------------- */

static const ovpn_opt_info_t ovpn__management_client_pf =
{
	.name = "management-client-pf",
	.flags = OVPN_OPT_FLAG_NORMAL
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(management_client_user, 1, OVPN_OPT_ARG_TYPE_STRING);
OVPN_OPT_DEF_ARG(management_client_user, 1, "u", false);

OVPN_OPT_DEF_ARGS_BEGIN(management_client_user)
OVPN_OPT_DEF_ARGS_ARG(management_client_user, 1)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__management_client_user =
{
	.name = "management-client-user",
	.flags = OVPN_OPT_FLAG_NORMAL,
	.args = {
		/* u */
		.min = 1,
		.max = 1,
		.info = OVPN_OPT_REF_ARGS(management_client_user)
	},
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(management_external_cert, 1, OVPN_OPT_ARG_TYPE_STRING);
OVPN_OPT_DEF_ARG(management_external_cert, 1, "certificate-hint", false);

OVPN_OPT_DEF_ARGS_BEGIN(management_external_cert)
OVPN_OPT_DEF_ARGS_ARG(management_external_cert, 1)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__management_external_cert =
{
	.name = "management-external-cert",
	.flags = OVPN_OPT_FLAG_NORMAL,
	.args = {
		/* certificate-hint */
		.min = 1,
		.max = 1,
		.info = OVPN_OPT_REF_ARGS(management_external_cert)
	},
};

/* ----------------------------------------------------------------------- */

static const ovpn_opt_info_t ovpn__management_external_key =
{
	.name = "management-external-key",
	.flags = OVPN_OPT_FLAG_NORMAL
};

/* ----------------------------------------------------------------------- */

static const ovpn_opt_info_t ovpn__management_forget_disconnect =
{
	.name = "management-forget-disconnect",
	.flags = OVPN_OPT_FLAG_NORMAL
};

/* ----------------------------------------------------------------------- */

static const ovpn_opt_info_t ovpn__management_hold =
{
	.name = "management-hold",
	.flags = OVPN_OPT_FLAG_NORMAL
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(management_log_cache, 1, OVPN_OPT_ARG_TYPE_UNUMBER);
OVPN_OPT_DEF_ARG(management_log_cache, 1, "n", false);

OVPN_OPT_DEF_ARGS_BEGIN(management_log_cache)
OVPN_OPT_DEF_ARGS_ARG(management_log_cache, 1)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__management_log_cache =
{
	.name = "management-log-cache",
	.flags = OVPN_OPT_FLAG_NORMAL,
	.args = {
		/* n */
		.min = 1,
		.max = 1,
		.info = OVPN_OPT_REF_ARGS(management_log_cache)
	},
};

/* ----------------------------------------------------------------------- */

static const ovpn_opt_info_t ovpn__management_query_passwords =
{
	.name = "management-query-passwords",
	.flags = OVPN_OPT_FLAG_NORMAL
};

/* ----------------------------------------------------------------------- */

static const ovpn_opt_info_t ovpn__management_query_proxy =
{
	.name = "management-query-proxy",
	.flags = OVPN_OPT_FLAG_NORMAL
};

/* ----------------------------------------------------------------------- */

static const ovpn_opt_info_t ovpn__management_query_remote =
{
	.name = "management-query-remote",
	.flags = OVPN_OPT_FLAG_NORMAL
};

/* ----------------------------------------------------------------------- */

static const ovpn_opt_info_t ovpn__management_signal =
{
	.name = "management-signal",
	.flags = OVPN_OPT_FLAG_NORMAL
};

/* ----------------------------------------------------------------------- */

static const ovpn_opt_info_t ovpn__management_up_down =
{
	.name = "management-up-down",
	.flags = OVPN_OPT_FLAG_NORMAL
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(mark, 1, OVPN_OPT_ARG_TYPE_STRING);
OVPN_OPT_DEF_ARG(mark, 1, "value", false);

OVPN_OPT_DEF_ARGS_BEGIN(mark)
OVPN_OPT_DEF_ARGS_ARG(mark, 1)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__mark =
{
	.name = "mark",
	.flags = OVPN_OPT_FLAG_NORMAL,
	.args = {
		/* value */
		.min = 1,
		.max = 1,
		.info = OVPN_OPT_REF_ARGS(mark)
	},
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(max_clients, 1, OVPN_OPT_ARG_TYPE_UNUMBER);
OVPN_OPT_DEF_ARG(max_clients, 1, "n", false);

OVPN_OPT_DEF_ARGS_BEGIN(max_clients)
OVPN_OPT_DEF_ARGS_ARG(max_clients, 1)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__max_clients =
{
	.name = "max-clients",
	.flags = OVPN_OPT_FLAG_NORMAL,
	.args = {
		/* n */
		.min = 1,
		.max = 1,
		.info = OVPN_OPT_REF_ARGS(max_clients)
	},
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(max_routes_per_client, 1, OVPN_OPT_ARG_TYPE_UNUMBER);
OVPN_OPT_DEF_ARG(max_routes_per_client, 1, "n", false);

OVPN_OPT_DEF_ARGS_BEGIN(max_routes_per_client)
OVPN_OPT_DEF_ARGS_ARG(max_routes_per_client, 1)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__max_routes_per_client =
{
	.name = "max-routes-per-client",
	.flags = OVPN_OPT_FLAG_NORMAL,
	.args = {
		/* n */
		.min = 1,
		.max = 1,
		.info = OVPN_OPT_REF_ARGS(max_routes_per_client)
	},
};

/* ----------------------------------------------------------------------- */

static const ovpn_opt_info_t ovpn__mktun =
{
	.name = "mktun",
	.flags = OVPN_OPT_FLAG_STANDALONE
};

/* ----------------------------------------------------------------------- */

static const ovpn_opt_info_t ovpn__mlock =
{
	.name = "mlock",
	.flags = OVPN_OPT_FLAG_NORMAL
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(mode, 1, OVPN_OPT_ARG_TYPE_LISTVALUE);
OVPN_OPT_DEF_ARG_LV(mode, 1, "m", false,
	"p2p", "server");

OVPN_OPT_DEF_ARGS_BEGIN(mode)
OVPN_OPT_DEF_ARGS_ARG(mode, 1)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__mode =
{
	.name = "mode",
	.flags = OVPN_OPT_FLAG_NORMAL,
	.args = {
		/* mode */
		.min = 1,
		.max = 1,
		.info = OVPN_OPT_REF_ARGS(mode),
	},
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(mssfix, 1, OVPN_OPT_ARG_TYPE_UNUMBER);
OVPN_OPT_DEF_ARG(mssfix, 1, "max", false);

OVPN_OPT_DEF_ARGS_BEGIN(mssfix)
OVPN_OPT_DEF_ARGS_ARG(mssfix, 1)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__mssfix =
{
	.name = "mssfix",
	.flags = OVPN_OPT_FLAG_NORMAL |
	         OVPN_OPT_FLAG_CONNECTION,
	.args = {
		/* max */
		.min = 1,
		.max = 1,
		.info = OVPN_OPT_REF_ARGS(mssfix)
	},
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(mtu_disc, 1, OVPN_OPT_ARG_TYPE_LISTVALUE);
OVPN_OPT_DEF_ARG_LV(mtu_disc, 1, "type", false,
	"no", "maybe", "yes");

OVPN_OPT_DEF_ARGS_BEGIN(mtu_disc)
OVPN_OPT_DEF_ARGS_ARG(mtu_disc, 1)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__mtu_disc =
{
	.name = "mtu-disc",
	.flags = OVPN_OPT_FLAG_NORMAL |
	         OVPN_OPT_FLAG_CONNECTION,
	.args = {
		/* type */
		.min = 1,
		.max = 1,
		.info = OVPN_OPT_REF_ARGS(mtu_disc)
	},
};

/* ----------------------------------------------------------------------- */

static const ovpn_opt_info_t ovpn__mtu_test =
{
	.name = "mtu-test",
	.flags = OVPN_OPT_FLAG_NORMAL
};

/* ----------------------------------------------------------------------- */

static const ovpn_opt_info_t ovpn__multihome =
{
	.name = "multihome",
	.flags = OVPN_OPT_FLAG_NORMAL
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(mute, 1, OVPN_OPT_ARG_TYPE_UNUMBER);
OVPN_OPT_DEF_ARG(mute, 1, "n", false);

OVPN_OPT_DEF_ARGS_BEGIN(mute)
OVPN_OPT_DEF_ARGS_ARG(mute, 1)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__mute =
{
	.name = "mute",
	.flags = OVPN_OPT_FLAG_NORMAL,
	.args = {
		/* n */
		.min = 1,
		.max = 1,
		.info = OVPN_OPT_REF_ARGS(mute)
	},
};

/* ----------------------------------------------------------------------- */

static const ovpn_opt_info_t ovpn__mute_replay_warnings =
{
	.name = "mute-replay-warnings",
	.flags = OVPN_OPT_FLAG_NORMAL
};

/* ----------------------------------------------------------------------- */

/*
 *  _   _
 * | \ | |
 * |  \| |
 * | . ` |
 * | |\  |
 * |_| \_|
 *
 */

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(ncp_ciphers, 1, OVPN_OPT_ARG_TYPE_LIST);
OVPN_OPT_DEF_ARG(ncp_ciphers, 1, "cipher_list", false);

OVPN_OPT_DEF_ARGS_BEGIN(ncp_ciphers)
OVPN_OPT_DEF_ARGS_ARG(ncp_ciphers, 1)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__ncp_ciphers =
{
	.name = "ncp-ciphers",
	.flags = OVPN_OPT_FLAG_NORMAL,
	.args = {
		/* cipher_list */
		.min = 1,
		.max = 1,
		.info = OVPN_OPT_REF_ARGS(ncp_ciphers)
	},
};

/* ----------------------------------------------------------------------- */

static const ovpn_opt_info_t ovpn__ncp_disable =
{
	.name = "ncp-disable",
	.flags = OVPN_OPT_FLAG_NORMAL
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(nice, 1, OVPN_OPT_ARG_TYPE_NUMBER);
OVPN_OPT_DEF_ARG(nice, 1, "n", false);

OVPN_OPT_DEF_ARGS_BEGIN(nice)
OVPN_OPT_DEF_ARGS_ARG(nice, 1)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__nice =
{
	.name = "nice",
	.flags = OVPN_OPT_FLAG_NORMAL,
	.args = {
		/* n */
		.min = 1,
		.max = 1,
		.info = OVPN_OPT_REF_ARGS(nice)
	},
};

/* ----------------------------------------------------------------------- */

static const ovpn_opt_info_t ovpn__no_iv =
{
	.name = "no-iv",
	.flags = OVPN_OPT_FLAG_NORMAL |
	         OVPN_OPT_FLAG_DEPRECATED
};

/* ----------------------------------------------------------------------- */

static const ovpn_opt_info_t ovpn__no_replay =
{
	.name = "no-replay",
	.flags = OVPN_OPT_FLAG_NORMAL |
	         OVPN_OPT_FLAG_DEPRECATED
};

/* ----------------------------------------------------------------------- */

static const ovpn_opt_info_t ovpn__no_name_remapping =
{
	.name = "no-name-remapping",
	.flags = OVPN_OPT_FLAG_NORMAL |
	         OVPN_OPT_FLAG_DEPRECATED
};

/* ----------------------------------------------------------------------- */

static const ovpn_opt_info_t ovpn__nobind =
{
	.name = "nobind",
	.flags = OVPN_OPT_FLAG_NORMAL |
	         OVPN_OPT_FLAG_CONNECTION
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(ns_cert_type, 1, OVPN_OPT_ARG_TYPE_LISTVALUE);
OVPN_OPT_DEF_ARG_LV(ns_cert_type, 1, "type", false,
	"client", "server");

OVPN_OPT_DEF_ARGS_BEGIN(ns_cert_type)
OVPN_OPT_DEF_ARGS_ARG(ns_cert_type, 1)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__ns_cert_type =
{
	.name = "ns-cert-type",
	.flags = OVPN_OPT_FLAG_NORMAL |
	         OVPN_OPT_FLAG_DEPRECATED,
	.args = {
		/* client|server */
		.min = 1,
		.max = 1,
		.info = OVPN_OPT_REF_ARGS(ns_cert_type)
	},
};

/* ----------------------------------------------------------------------- */

/*
 *   ____
 *  / __ \
 * | |  | |
 * | |  | |
 * | |__| |
 *  \____/
 *
 */

/* ----------------------------------------------------------------------- */

static const ovpn_opt_info_t ovpn__opt_verify =
{
	.name = "opt-verify",
	.flags = OVPN_OPT_FLAG_NORMAL
};

/* ----------------------------------------------------------------------- */

/*
 *  _____
 * |  __ \
 * | |__) |
 * |  ___/
 * | |
 * |_|
 *
 */

/* ----------------------------------------------------------------------- */

static const ovpn_opt_info_t ovpn__passtos =
{
	.name = "passtos",
	.flags = OVPN_OPT_FLAG_NORMAL
};

/* ----------------------------------------------------------------------- */

static const ovpn_opt_info_t ovpn__pause_exit =
{
	.name = "pause-exit",
	.flags = OVPN_OPT_FLAG_NORMAL |
	         OVPN_OPT_FLAG_WINDOWS
};

/* ----------------------------------------------------------------------- */

static const ovpn_opt_info_t ovpn__persist_key =
{
	.name = "persist-key",
	.flags = OVPN_OPT_FLAG_NORMAL |
	         OVPN_OPT_FLAG_PUSHABLE
};

/* ----------------------------------------------------------------------- */

static const ovpn_opt_info_t ovpn__persist_local_ip =
{
	.name = "persist-local-ip",
	.flags = OVPN_OPT_FLAG_NORMAL
};

/* ----------------------------------------------------------------------- */

static const ovpn_opt_info_t ovpn__persist_remote_ip =
{
	.name = "persist-remote-ip",
	.flags = OVPN_OPT_FLAG_NORMAL
};

/* ----------------------------------------------------------------------- */

static const ovpn_opt_info_t ovpn__persist_tun =
{
	.name = "persist-tun",
	.flags = OVPN_OPT_FLAG_NORMAL |
	         OVPN_OPT_FLAG_PUSHABLE
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(ping, 1, OVPN_OPT_ARG_TYPE_UNUMBER);
OVPN_OPT_DEF_ARG(ping, 1, "n", false);

OVPN_OPT_DEF_ARGS_BEGIN(ping)
OVPN_OPT_DEF_ARGS_ARG(ping, 1)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__ping =
{
	.name = "ping",
	.flags = OVPN_OPT_FLAG_NORMAL |
	         OVPN_OPT_FLAG_PUSHABLE,
	.args = {
		/* n */
		.min = 1,
		.max = 1,
		.info = OVPN_OPT_REF_ARGS(ping)
	},
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(ping_exit, 1, OVPN_OPT_ARG_TYPE_UNUMBER);
OVPN_OPT_DEF_ARG(ping_exit, 1, "n", false);

OVPN_OPT_DEF_ARGS_BEGIN(ping_exit)
OVPN_OPT_DEF_ARGS_ARG(ping_exit, 1)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__ping_exit =
{
	.name = "ping-exit",
	.flags = OVPN_OPT_FLAG_NORMAL |
	         OVPN_OPT_FLAG_PUSHABLE,
	.args = {
		/* n */
		.min = 1,
		.max = 1,
		.info = OVPN_OPT_REF_ARGS(ping_exit)
	},
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(ping_restart, 1, OVPN_OPT_ARG_TYPE_UNUMBER);
OVPN_OPT_DEF_ARG(ping_restart, 1, "n", false);

OVPN_OPT_DEF_ARGS_BEGIN(ping_restart)
OVPN_OPT_DEF_ARGS_ARG(ping_restart, 1)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__ping_restart =
{
	.name = "ping-restart",
	.flags = OVPN_OPT_FLAG_NORMAL |
	         OVPN_OPT_FLAG_PUSHABLE,
	.args = {
		/* n */
		.min = 1,
		.max = 1,
		.info = OVPN_OPT_REF_ARGS(ping_restart)
	},
};

/* ----------------------------------------------------------------------- */

static const ovpn_opt_info_t ovpn__ping_timer_rem =
{
	.name = "ping-timer-rem",
	.flags = OVPN_OPT_FLAG_NORMAL
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(pkcs11_cert_private, 1, OVPN_OPT_ARG_TYPE_UNUMBER);
OVPN_OPT_DEF_ARG_RANGE(pkcs11_cert_private, 1, "0/1", false, 0, 1);

OVPN_OPT_DEF_ARGS_BEGIN(pkcs11_cert_private)
OVPN_OPT_DEF_ARGS_ARG(pkcs11_cert_private, 1)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__pkcs11_cert_private =
{
	.name = "pkcs11-cert-private",
	.flags = OVPN_OPT_FLAG_NORMAL,
	.args = {
		/* [0|1]... */
		.min = 0,
		.max = OVPN_OPT_ARGS_NOT_LIMITED,
		.info = OVPN_OPT_REF_ARGS(pkcs11_cert_private)
	},
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(pkcs11_id, 1, OVPN_OPT_ARG_TYPE_STRING);
OVPN_OPT_DEF_ARG(pkcs11_id, 1, "name", false);

OVPN_OPT_DEF_ARGS_BEGIN(pkcs11_id)
OVPN_OPT_DEF_ARGS_ARG(pkcs11_id, 1)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__pkcs11_id =
{
	.name = "pkcs11-id",
	.flags = OVPN_OPT_FLAG_NORMAL,
	.args = {
		/* name */
		.min = 1,
		.max = 1,
		.info = OVPN_OPT_REF_ARGS(pkcs11_id)
	},
};

/* ----------------------------------------------------------------------- */

static const ovpn_opt_info_t ovpn__pkcs11_id_management =
{
	.name = "pkcs11-id-management",
	.flags = OVPN_OPT_FLAG_NORMAL
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(pkcs11_pin_cache, 1, OVPN_OPT_ARG_TYPE_UNUMBER);
OVPN_OPT_DEF_ARG(pkcs11_pin_cache, 1, "seconds", false);

OVPN_OPT_DEF_ARGS_BEGIN(pkcs11_pin_cache)
OVPN_OPT_DEF_ARGS_ARG(pkcs11_pin_cache, 1)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__pkcs11_pin_cache =
{
	.name = "pkcs11-pin-cache",
	.flags = OVPN_OPT_FLAG_NORMAL,
	.args = {
		/* seconds */
		.min = 1,
		.max = 1,
		.info = OVPN_OPT_REF_ARGS(pkcs11_pin_cache)
	},
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(pkcs11_protected_authentification, 1,
	OVPN_OPT_ARG_TYPE_UNUMBER);
OVPN_OPT_DEF_ARG_RANGE(pkcs11_protected_authentification, 1, "0/1", false, 0, 1);

OVPN_OPT_DEF_ARGS_BEGIN(pkcs11_protected_authentification)
OVPN_OPT_DEF_ARGS_ARG(pkcs11_protected_authentification, 1)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__pkcs11_protected_authentification =
{
	.name = "pkcs11-protected-authentification",
	.flags = OVPN_OPT_FLAG_NORMAL,
	.args = {
		/* [0|1]... */
		.min = 0,
		.max = 1,
		.info = OVPN_OPT_REF_ARGS(pkcs11_protected_authentification)
	},
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(pkcs11_providers, 1, OVPN_OPT_ARG_TYPE_STRING);
OVPN_OPT_DEF_ARG(pkcs11_providers, 1, "provider", false);

OVPN_OPT_DEF_ARGS_BEGIN(pkcs11_providers)
OVPN_OPT_DEF_ARGS_ARG(pkcs11_providers, 1)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__pkcs11_providers =
{
	.name = "pkcs11-providers",
	.flags = OVPN_OPT_FLAG_NORMAL,
	.args = {
		/* provider... */
		.min = 1,
		.max = OVPN_OPT_ARGS_NOT_LIMITED,
		.info = OVPN_OPT_REF_ARGS(pkcs11_providers)
	},
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(pkcs11_private_mode, 1, OVPN_OPT_ARG_TYPE_UNUMBER);
OVPN_OPT_DEF_ARG_RANGE(pkcs11_private_mode, 1, "provider", false, 0, 15);

OVPN_OPT_DEF_ARGS_BEGIN(pkcs11_private_mode)
OVPN_OPT_DEF_ARGS_ARG(pkcs11_private_mode, 1)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__pkcs11_private_mode =
{
	.name = "pkcs11-private-mode",
	.flags = OVPN_OPT_FLAG_NORMAL,
	.args = {
		/* mode... */
		.min = 1,
		.max = OVPN_OPT_ARGS_NOT_LIMITED,
		.info = OVPN_OPT_REF_ARGS(pkcs11_private_mode)
	},
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(pkcs12, 1, OVPN_OPT_ARG_TYPE_FILEPATH);
OVPN_OPT_DEF_ARG(pkcs12, 1, "file", false);

OVPN_OPT_DEF_ARGS_BEGIN(pkcs12)
OVPN_OPT_DEF_ARGS_ARG(pkcs12, 1)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__pkcs12 =
{
	.name = "pkcs12",
	.flags = OVPN_OPT_FLAG_NORMAL |
	         OVPN_OPT_FLAG_INLINE,
	.inline_type = OVPN_OPT_INLINE_TYPE_PLAIN,
	.args = {
		/* file */
		.min = 1,
		.max = 1,
		.info = OVPN_OPT_REF_ARGS(pkcs12)
	},
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(plugin, 1, OVPN_OPT_ARG_TYPE_FILEPATH);
OVPN_OPT_DEF_ARG(plugin, 1, "module-pathname", false);

OVPN_OPT_DEF_ARG_TYPES(plugin, 2, OVPN_OPT_ARG_TYPE_STRING);
OVPN_OPT_DEF_ARG(plugin, 2, "init-string", true);

OVPN_OPT_DEF_ARGS_BEGIN(plugin)
OVPN_OPT_DEF_ARGS_ARG(plugin, 1)
OVPN_OPT_DEF_ARGS_ARG(plugin, 2)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__plugin =
{
	.name = "plugin",
	.flags = OVPN_OPT_FLAG_NORMAL,
	.args = {
		/* module-pathname [init-string] */
		.min = 1,
		.max = 2,
		.info = OVPN_OPT_REF_ARGS(plugin)
	},
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(port, 1, OVPN_OPT_ARG_TYPE_PORT);
OVPN_OPT_DEF_ARG(port, 1, "port", false);

OVPN_OPT_DEF_ARGS_BEGIN(port)
OVPN_OPT_DEF_ARGS_ARG(port, 1)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__port =
{
	.name = "port",
	.flags = OVPN_OPT_FLAG_NORMAL |
	         OVPN_OPT_FLAG_CONNECTION,
	.args = {
		/* port */
		.min = 1,
		.max = 1,
		.info = OVPN_OPT_REF_ARGS(port)
	},
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(port_share, 1, OVPN_OPT_ARG_TYPE_ADDRESS);
OVPN_OPT_DEF_ARG(port_share, 1, "host", false);

OVPN_OPT_DEF_ARG_TYPES(port_share, 2, OVPN_OPT_ARG_TYPE_PORT);
OVPN_OPT_DEF_ARG(port_share, 2, "port", false);

OVPN_OPT_DEF_ARG_TYPES(port_share, 3, OVPN_OPT_ARG_TYPE_DIR);
OVPN_OPT_DEF_ARG(port_share, 3, "dir", true);

OVPN_OPT_DEF_ARGS_BEGIN(port_share)
OVPN_OPT_DEF_ARGS_ARG(port_share, 1)
OVPN_OPT_DEF_ARGS_ARG(port_share, 2)
OVPN_OPT_DEF_ARGS_ARG(port_share, 3)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__port_share =
{
	.name = "port-share",
	.flags = OVPN_OPT_FLAG_NORMAL,
	.args = {
		/* host port [dir] */
		.min = 2,
		.max = 3,
		.info = OVPN_OPT_REF_ARGS(port_share)
	},
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(prng, 1, OVPN_OPT_ARG_TYPE_STRING);
OVPN_OPT_DEF_ARG(prng, 1, "alg", false);

OVPN_OPT_DEF_ARG_TYPES(prng, 2, OVPN_OPT_ARG_TYPE_UNUMBER);
OVPN_OPT_DEF_ARG_RANGE(prng, 2, "nsl", true, 16, 64);

OVPN_OPT_DEF_ARGS_BEGIN(prng)
OVPN_OPT_DEF_ARGS_ARG(prng, 1)
OVPN_OPT_DEF_ARGS_ARG(prng, 2)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__prng =
{
	.name = "prng",
	.flags = OVPN_OPT_FLAG_NORMAL,
	.args = {
		/* alg [nsl] */
		.min = 1,
		.max = 2,
		.info = OVPN_OPT_REF_ARGS(prng)
	},
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(proto, 1, OVPN_OPT_ARG_TYPE_LISTVALUE);
OVPN_OPT_DEF_ARG_LV(proto, 1, "p", false,
	"udp", "tcp", "tcp-client", "tcp-server");

OVPN_OPT_DEF_ARGS_BEGIN(proto)
OVPN_OPT_DEF_ARGS_ARG(proto, 1)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__proto =
{
	.name = "proto",
	.flags = OVPN_OPT_FLAG_NORMAL |
	         OVPN_OPT_FLAG_CONNECTION,
	.args = {
		/* p */
		.min = 1,
		.max = 1,
		.info = OVPN_OPT_REF_ARGS(proto)
	},
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(proto_force, 1, OVPN_OPT_ARG_TYPE_LISTVALUE);
OVPN_OPT_DEF_ARG_LV(proto_force, 1, "p", false,
	"tcp", "udp");

OVPN_OPT_DEF_ARGS_BEGIN(proto_force)
OVPN_OPT_DEF_ARGS_ARG(proto_force, 1)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__proto_force =
{
	.name = "proto-force",
	.flags = OVPN_OPT_FLAG_NORMAL,
	.args = {
		/* tcp or udp */
		.min = 1,
		.max = 1,
		.info = OVPN_OPT_REF_ARGS(proto_force)
	},
};

/* ----------------------------------------------------------------------- */

static const ovpn_opt_info_t ovpn__pull =
{
	.name = "pull",
	.flags = OVPN_OPT_FLAG_NORMAL
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(pull_filter, 1, OVPN_OPT_ARG_TYPE_LISTVALUE);
OVPN_OPT_DEF_ARG_LV(pull_filter, 1, "action", false,
	"accept", "ignore", "reject");

OVPN_OPT_DEF_ARG_TYPES(pull_filter, 2, OVPN_OPT_ARG_TYPE_STRING);
OVPN_OPT_DEF_ARG(pull_filter, 2, "text", false);

OVPN_OPT_DEF_ARGS_BEGIN(pull_filter)
OVPN_OPT_DEF_ARGS_ARG(pull_filter, 1)
OVPN_OPT_DEF_ARGS_ARG(pull_filter, 2)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__pull_filter =
{
	.name = "pull-filter",
	.flags = OVPN_OPT_FLAG_NORMAL,
	.args = {
		/* accept|ignore|reject text */
		.min = 2,
		.max = 2,
		.info = OVPN_OPT_REF_ARGS(pull_filter)
	},
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(push, 1, OVPN_OPT_ARG_TYPE_STRING);
OVPN_OPT_DEF_ARG(push, 1, "option", false);

OVPN_OPT_DEF_ARGS_BEGIN(push)
OVPN_OPT_DEF_ARGS_ARG(push, 1)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__push =
{
	.name = "push",
	.flags = OVPN_OPT_FLAG_NORMAL |
	         OVPN_OPT_FLAG_MULTIPLE,
	.args = {
		/* option */
		.min = 1,
		.max = 1,
		.info = OVPN_OPT_REF_ARGS(push)
	},
};

/* ----------------------------------------------------------------------- */

static const ovpn_opt_info_t ovpn__push_peer_info =
{
	.name = "push-peer-info",
	.flags = OVPN_OPT_FLAG_NORMAL
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(push_remove, 1, OVPN_OPT_ARG_TYPE_STRING);
OVPN_OPT_DEF_ARG(push_remove, 1, "option", false);

OVPN_OPT_DEF_ARGS_BEGIN(push_remove)
OVPN_OPT_DEF_ARGS_ARG(push_remove, 1)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__push_remove =
{
	.name = "push-remove",
	.flags = OVPN_OPT_FLAG_NORMAL |
	         OVPN_OPT_FLAG_MULTIPLE,
	.args = {
		/* opt */
		.min = 1,
		.max = 1,
		.info = OVPN_OPT_REF_ARGS(push_remove)
	},
};

/* ----------------------------------------------------------------------- */

static const ovpn_opt_info_t ovpn__push_reset =
{
	.name = "push-reset",
	.flags = OVPN_OPT_FLAG_NORMAL
};

/* ----------------------------------------------------------------------- */

/*
 *   ____
 *  / __ \
 * | |  | |
 * | |  | |
 * | |__| |
 *  \___\_\
 *
 */

/* Nothing */

/*
 *  _____
 * |  __ \
 * | |__) |
 * |  _  /
 * | | \ \
 * |_|  \_\
 *
 */

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(rcvbuf, 1, OVPN_OPT_ARG_TYPE_UNUMBER);
OVPN_OPT_DEF_ARG(rcvbuf, 1, "size", false);

OVPN_OPT_DEF_ARGS_BEGIN(rcvbuf)
OVPN_OPT_DEF_ARGS_ARG(rcvbuf, 1)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__rcvbuf =
{
	.name = "rcvbuf",
	.flags = OVPN_OPT_FLAG_NORMAL |
	         OVPN_OPT_FLAG_PUSHABLE,
	.args = {
		/* size */
		.min = 1,
		.max = 1,
		.info = OVPN_OPT_REF_ARGS(rcvbuf)
	},
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(redirect_X, 1, OVPN_OPT_ARG_TYPE_LISTVALUE);
OVPN_OPT_DEF_ARG_LV(redirect_X, 1, "flags", false,
	"local", "autolocal", "def1", "bypass-dhcp", "bypass-dns",
	"block-local", "ipv6", "!ipv4");

OVPN_OPT_DEF_ARGS_BEGIN(redirect_X)
OVPN_OPT_DEF_ARGS_ARG(redirect_X, 1)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__redirect_gateway =
{
	.name = "redirect-gateway",
	.flags = OVPN_OPT_FLAG_NORMAL |
	         OVPN_OPT_FLAG_PUSHABLE,
	.args = {
		/* [flags...] */
		.min = 0,
		.max = OVPN_OPT_ARGS_NOT_LIMITED, /* not limited */
		.info = OVPN_OPT_REF_ARGS(redirect_X)
	},
};

static const ovpn_opt_info_t ovpn__redirect_private =
{
	.name = "redirect-private",
	.flags = OVPN_OPT_FLAG_NORMAL,
	.args = {
		/* [flags...] */
		.min = 0,
		.max = OVPN_OPT_ARGS_NOT_LIMITED, /* not limited */
		.info = OVPN_OPT_REF_ARGS(redirect_X)
	},
};

/* ----------------------------------------------------------------------- */

static const ovpn_opt_info_t ovpn__register_dns =
{
	.name = "register-dns",
	.flags = OVPN_OPT_FLAG_NORMAL |
	         OVPN_OPT_FLAG_WINDOWS
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(remap_usr1, 1, OVPN_OPT_ARG_TYPE_LISTVALUE);
OVPN_OPT_DEF_ARG_LV(remap_usr1, 1, "signal", false,
	"SIGHUP", "SIGTERM");

OVPN_OPT_DEF_ARGS_BEGIN(remap_usr1)
OVPN_OPT_DEF_ARGS_ARG(remap_usr1, 1)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__remap_usr1 =
{
	.name = "remap-usr1",
	.flags = OVPN_OPT_FLAG_NORMAL,
	.args = {
		/* signal */
		.min = 1,
		.max = 1,
		.info = OVPN_OPT_REF_ARGS(remap_usr1)
	},
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(remote, 1, OVPN_OPT_ARG_TYPE_ADDRESS);
OVPN_OPT_DEF_ARG(remote, 1, "host", false);

OVPN_OPT_DEF_ARG_TYPES(remote, 2, OVPN_OPT_ARG_TYPE_PORT);
OVPN_OPT_DEF_ARG(remote, 2, "port", true);

OVPN_OPT_DEF_ARG_TYPES(remote, 3, OVPN_OPT_ARG_TYPE_LISTVALUE);
OVPN_OPT_DEF_ARG_LV(remote, 3, "proto", true,
	"udp", "tcp", "udp4", "tcp4", "udp6", "tcp6",
	"tcp-client", "udp-client");

OVPN_OPT_DEF_ARGS_BEGIN(remote)
OVPN_OPT_DEF_ARGS_ARG(remote, 1)
OVPN_OPT_DEF_ARGS_ARG(remote, 2)
OVPN_OPT_DEF_ARGS_ARG(remote, 3)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__remote =
{
	.name = "remote",
	.flags = OVPN_OPT_FLAG_NORMAL |
	         OVPN_OPT_FLAG_CONNECTION |
	         OVPN_OPT_FLAG_MULTIPLE,
	.args = {
		/* host [port] [proto] */
		.min = 1,
		.max = 3,
		.info = OVPN_OPT_REF_ARGS(remote),
	},
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(remote_cert_eku, 1, OVPN_OPT_ARG_TYPE_STRING);
OVPN_OPT_DEF_ARG(remote_cert_eku, 1, "oid", false);

OVPN_OPT_DEF_ARGS_BEGIN(remote_cert_eku)
OVPN_OPT_DEF_ARGS_ARG(remote_cert_eku, 1)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__remote_cert_eku =
{
	.name = "remote-cert-eku",
	.flags = OVPN_OPT_FLAG_NORMAL,
	.args = {
		/* oid */
		.min = 1,
		.max = 1,
		.info = OVPN_OPT_REF_ARGS(remote_cert_eku)
	},
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(remote_cert_ku, 1, OVPN_OPT_ARG_TYPE_STRING);
OVPN_OPT_DEF_ARG(remote_cert_ku, 1, "v", false);

OVPN_OPT_DEF_ARGS_BEGIN(remote_cert_ku)
OVPN_OPT_DEF_ARGS_ARG(remote_cert_ku, 1)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__remote_cert_ku =
{
	.name = "remote-cert-ku",
	.flags = OVPN_OPT_FLAG_NORMAL,
	.args = {
		/* [v...] */
		.min = 0,
		.max = OVPN_OPT_ARGS_NOT_LIMITED,
		.info = OVPN_OPT_REF_ARGS(remote_cert_ku)
	},
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(remote_cert_tls, 1, OVPN_OPT_ARG_TYPE_LISTVALUE);
OVPN_OPT_DEF_ARG_LV(remote_cert_tls, 1, "mode", false,
	"client", "server");

OVPN_OPT_DEF_ARGS_BEGIN(remote_cert_tls)
OVPN_OPT_DEF_ARGS_ARG(remote_cert_tls, 1)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__remote_cert_tls =
{
	.name = "remote-cert-tls",
	.flags = OVPN_OPT_FLAG_NORMAL,
	.args = {
		/* client|server */
		.min = 1,
		.max = 1,
		.info = OVPN_OPT_REF_ARGS(remote_cert_tls)
	},
};

/* ----------------------------------------------------------------------- */

static const ovpn_opt_info_t ovpn__remote_random =
{
	.name = "remote-random",
	.flags = OVPN_OPT_FLAG_NORMAL
};

/* ----------------------------------------------------------------------- */

static const ovpn_opt_info_t ovpn__remote_random_hostname =
{
	.name = "remote-random-hostname",
	.flags = OVPN_OPT_FLAG_NORMAL
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(reneg_bytes, 1, OVPN_OPT_ARG_TYPE_UNUMBER);
OVPN_OPT_DEF_ARG(reneg_bytes, 1, "n", false);

OVPN_OPT_DEF_ARGS_BEGIN(reneg_bytes)
OVPN_OPT_DEF_ARGS_ARG(reneg_bytes, 1)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__reneg_bytes =
{
	.name = "reneg-bytes",
	.flags = OVPN_OPT_FLAG_NORMAL,
	.args = {
		/* n */
		.min = 1,
		.max = 1,
		.info = OVPN_OPT_REF_ARGS(reneg_bytes)
	},
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(reneg_pkts, 1, OVPN_OPT_ARG_TYPE_UNUMBER);
OVPN_OPT_DEF_ARG(reneg_pkts, 1, "n", false);

OVPN_OPT_DEF_ARGS_BEGIN(reneg_pkts)
OVPN_OPT_DEF_ARGS_ARG(reneg_pkts, 1)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__reneg_pkts =
{
	.name = "reneg-pkts",
	.flags = OVPN_OPT_FLAG_NORMAL,
	.args = {
		/* n */
		.min = 1,
		.max = 1,
		.info = OVPN_OPT_REF_ARGS(reneg_pkts)
	},
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(reneg_sec, 1, OVPN_OPT_ARG_TYPE_UNUMBER);
OVPN_OPT_DEF_ARG(reneg_sec, 1, "n", false);

OVPN_OPT_DEF_ARGS_BEGIN(reneg_sec)
OVPN_OPT_DEF_ARGS_ARG(reneg_sec, 1)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__reneg_sec =
{
	.name = "reneg-sec",
	.flags = OVPN_OPT_FLAG_NORMAL,
	.args = {
		/* n */
		.min = 1,
		.max = 1,
		.info = OVPN_OPT_REF_ARGS(reneg_sec)
	},
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(replay_persist, 1, OVPN_OPT_ARG_TYPE_FILEPATH);
OVPN_OPT_DEF_ARG(replay_persist, 1, "file", false);

OVPN_OPT_DEF_ARGS_BEGIN(replay_persist)
OVPN_OPT_DEF_ARGS_ARG(replay_persist, 1)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__replay_persist =
{
	.name = "replay-persist",
	.flags = OVPN_OPT_FLAG_NORMAL,
	.args = {
		/* file */
		.min = 1,
		.max = 1,
		.info = OVPN_OPT_REF_ARGS(replay_persist)
	},
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(replay_window, 1, OVPN_OPT_ARG_TYPE_UNUMBER);
OVPN_OPT_DEF_ARG(replay_window, 1, "n", false);

OVPN_OPT_DEF_ARG_TYPES(replay_window, 2, OVPN_OPT_ARG_TYPE_UNUMBER);
OVPN_OPT_DEF_ARG(replay_window, 2, "t", false);

OVPN_OPT_DEF_ARGS_BEGIN(replay_window)
OVPN_OPT_DEF_ARGS_ARG(replay_window, 1)
OVPN_OPT_DEF_ARGS_ARG(replay_window, 2)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__replay_window =
{
	.name = "replay-window",
	.flags = OVPN_OPT_FLAG_NORMAL,
	.args = {
		/* n [t] */
		.min = 1,
		.max = 2,
		.info = OVPN_OPT_REF_ARGS(replay_window)
	},
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(resolv_retry, 1,
	OVPN_OPT_ARG_TYPE_UNUMBER, OVPN_OPT_ARG_TYPE_LISTVALUE);
OVPN_OPT_DEF_ARG_LV(resolv_retry, 1, "n", false, "infinite");

OVPN_OPT_DEF_ARGS_BEGIN(resolv_retry)
OVPN_OPT_DEF_ARGS_ARG(resolv_retry, 1)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__resolv_retry =
{
	.name = "resolv-retry",
	.flags = OVPN_OPT_FLAG_NORMAL,
	.args = {
		/* n */
		.min = 1,
		.max = 1,
		.info = OVPN_OPT_REF_ARGS(resolv_retry)
	},
};

/* ----------------------------------------------------------------------- */

static const ovpn_opt_info_t ovpn__rmtun =
{
	.name = "rmtun",
	.flags = OVPN_OPT_FLAG_NORMAL |
	         OVPN_OPT_FLAG_STANDALONE
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(route, 1,
	OVPN_OPT_ARG_TYPE_NETWORK,
	OVPN_OPT_ARG_TYPE_ADDRESS,
	OVPN_OPT_ARG_TYPE_LISTVALUE);
OVPN_OPT_DEF_ARG_LV(route, 1, "network/IP", false,
	"vpn_gateway", "net_gateway", "remote_host");

OVPN_OPT_DEF_ARG_TYPES(route, 2, OVPN_OPT_ARG_TYPE_NETMASK);
OVPN_OPT_DEF_ARG(route, 2, "netmask", true);

OVPN_OPT_DEF_ARG_TYPES(route, 3,
	OVPN_OPT_ARG_TYPE_IPADDR, OVPN_OPT_ARG_TYPE_LISTVALUE);
OVPN_OPT_DEF_ARG_LV(route, 3, "gateway", true,
	"vpn_gateway", "net_gateway", "remote_host");

OVPN_OPT_DEF_ARG_TYPES(route, 4, OVPN_OPT_ARG_TYPE_UNUMBER);
OVPN_OPT_DEF_ARG(route, 4, "metric", true);

OVPN_OPT_DEF_ARGS_BEGIN(route)
OVPN_OPT_DEF_ARGS_ARG(route, 1)
OVPN_OPT_DEF_ARGS_ARG(route, 2)
OVPN_OPT_DEF_ARGS_ARG(route, 3)
OVPN_OPT_DEF_ARGS_ARG(route, 4)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__route =
{
	.name = "route",
	.flags = OVPN_OPT_FLAG_NORMAL |
	         OVPN_OPT_FLAG_PUSHABLE,
	.args = {
		/* network/IP [netmask] [gateway] [metric] */
		.min = 1,
		.max = 4,
		.info = OVPN_OPT_REF_ARGS(route)
	},
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(route_delay, 1, OVPN_OPT_ARG_TYPE_UNUMBER);
OVPN_OPT_DEF_ARG(route_delay, 1, "n", true);

OVPN_OPT_DEF_ARG_TYPES(route_delay, 2, OVPN_OPT_ARG_TYPE_UNUMBER);
OVPN_OPT_DEF_ARG(route_delay, 2, "w", true);

OVPN_OPT_DEF_ARGS_BEGIN(route_delay)
OVPN_OPT_DEF_ARGS_ARG(route_delay, 1)
OVPN_OPT_DEF_ARGS_ARG(route_delay, 2)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__route_delay =
{
	.name = "route-delay",
	.flags = OVPN_OPT_FLAG_NORMAL |
	         OVPN_OPT_FLAG_PUSHABLE,
	.args = {
		/* [n] [w] */
		.min = 0,
		.max = 2,
		.info = OVPN_OPT_REF_ARGS(route_delay)
	},
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(route_gateway, 1,
	OVPN_OPT_ARG_TYPE_IPADDR, OVPN_OPT_ARG_TYPE_LISTVALUE);
OVPN_OPT_DEF_ARG_LV(route_gateway, 1, "gw", false, "dhcp");

OVPN_OPT_DEF_ARGS_BEGIN(route_gateway)
OVPN_OPT_DEF_ARGS_ARG(route_gateway, 1)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__route_gateway =
{
	.name = "route-gateway",
	.flags = OVPN_OPT_FLAG_NORMAL |
	         OVPN_OPT_FLAG_PUSHABLE,
	.args = {
		/* gw|'dhcp' */
		.min = 1,
		.max = 1,
		.info = OVPN_OPT_REF_ARGS(route_gateway)
	},
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(route_ipv6, 1, OVPN_OPT_ARG_TYPE_IPV6ADDR);
OVPN_OPT_DEF_ARG(route_ipv6, 1, "ipv6addr/bits", false);

OVPN_OPT_DEF_ARG_TYPES(route_ipv6, 2, OVPN_OPT_ARG_TYPE_IPADDR);
OVPN_OPT_DEF_ARG(route_ipv6, 2, "gateway", true);

OVPN_OPT_DEF_ARG_TYPES(route_ipv6, 3, OVPN_OPT_ARG_TYPE_UNUMBER);
OVPN_OPT_DEF_ARG(route_ipv6, 3, "metric", true);

OVPN_OPT_DEF_ARGS_BEGIN(route_ipv6)
OVPN_OPT_DEF_ARGS_ARG(route_ipv6, 1)
OVPN_OPT_DEF_ARGS_ARG(route_ipv6, 2)
OVPN_OPT_DEF_ARGS_ARG(route_ipv6, 3)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__route_ipv6 =
{
	.name = "route-ipv6",
	.flags = OVPN_OPT_FLAG_NORMAL |
	         OVPN_OPT_FLAG_IPV6 |
	         OVPN_OPT_FLAG_PUSHABLE,
	.args = {
		/* ipv6addr/bits [gateway] [metric] */
		.min = 1,
		.max = 3,
		.info = OVPN_OPT_REF_ARGS(route_ipv6)
	},
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(route_method, 1, OVPN_OPT_ARG_TYPE_LISTVALUE);
OVPN_OPT_DEF_ARG_LV(route_method, 1, "m", false,
	"adaptive", "ipapi", "exe");

OVPN_OPT_DEF_ARGS_BEGIN(route_method)
OVPN_OPT_DEF_ARGS_ARG(route_method, 1)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__route_method =
{
	.name = "route-method",
	.flags = OVPN_OPT_FLAG_NORMAL |
	         OVPN_OPT_FLAG_WINDOWS,
	.args = {
		/* m */
		.min = 1,
		.max = 1,
		.info = OVPN_OPT_REF_ARGS(route_method)
	},
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(route_metric, 1, OVPN_OPT_ARG_TYPE_UNUMBER);
OVPN_OPT_DEF_ARG(route_metric, 1, "m", false);

OVPN_OPT_DEF_ARGS_BEGIN(route_metric)
OVPN_OPT_DEF_ARGS_ARG(route_metric, 1)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__route_metric =
{
	.name = "route-metric",
	.flags = OVPN_OPT_FLAG_NORMAL,
	.args = {
		/* m */
		.min = 1,
		.max = 1,
		.info = OVPN_OPT_REF_ARGS(route_metric)
	},
};

/* ----------------------------------------------------------------------- */

static const ovpn_opt_info_t ovpn__route_noexec =
{
	.name = "route-noexec",
	.flags = OVPN_OPT_FLAG_NORMAL
};

/* ----------------------------------------------------------------------- */

static const ovpn_opt_info_t ovpn__route_nopull =
{
	.name = "route-nopull",
	.flags = OVPN_OPT_FLAG_NORMAL
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(route_pre_down, 1, OVPN_OPT_ARG_TYPE_COMMAND);
OVPN_OPT_DEF_ARG(route_pre_down, 1, "cmd", false);

OVPN_OPT_DEF_ARGS_BEGIN(route_pre_down)
OVPN_OPT_DEF_ARGS_ARG(route_pre_down, 1)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__route_pre_down =
{
	.name = "route-pre-down",
	.flags = OVPN_OPT_FLAG_NORMAL,
	.args = {
		/* cmd */
		.min = 1,
		.max = 1,
		.info = OVPN_OPT_REF_ARGS(route_pre_down)
	},
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(route_up, 1, OVPN_OPT_ARG_TYPE_COMMAND);
OVPN_OPT_DEF_ARG(route_up, 1, "cmd", false);

OVPN_OPT_DEF_ARGS_BEGIN(route_up)
OVPN_OPT_DEF_ARGS_ARG(route_up, 1)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__route_up =
{
	.name = "route-up",
	.flags = OVPN_OPT_FLAG_NORMAL,
	.args = {
		/* cmd */
		.min = 1,
		.max = 1,
		.info = OVPN_OPT_REF_ARGS(route_up)
	},
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(rport, 1, OVPN_OPT_ARG_TYPE_PORT);
OVPN_OPT_DEF_ARG(rport, 1, "port", false);

OVPN_OPT_DEF_ARGS_BEGIN(rport)
OVPN_OPT_DEF_ARGS_ARG(rport, 1)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__rport =
{
	.name = "rport",
	.flags = OVPN_OPT_FLAG_NORMAL |
	         OVPN_OPT_FLAG_CONNECTION,
	.args = {
		/* port */
		.min = 1,
		.max = 1,
		.info = OVPN_OPT_REF_ARGS(rport)
	},
};

/* ----------------------------------------------------------------------- */

/*
 *   _____
 *  / ____|
 * | (___
 *  \___ \
 *  ____) |
 * |_____/
 *
 */

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(script_security, 1, OVPN_OPT_ARG_TYPE_UNUMBER);
OVPN_OPT_DEF_ARG_RANGE(script_security, 1, "level", false, 0, 3);

OVPN_OPT_DEF_ARGS_BEGIN(script_security)
OVPN_OPT_DEF_ARGS_ARG(script_security, 1)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__script_security =
{
	.name = "script-security",
	.flags = OVPN_OPT_FLAG_NORMAL,
	.args = {
		/* level */
		.min = 1,
		.max = 1,
		.info = OVPN_OPT_REF_ARGS(script_security)
	},
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(secret, 1, OVPN_OPT_ARG_TYPE_FILEPATH);
OVPN_OPT_DEF_ARG(secret, 1, "file", false);

OVPN_OPT_DEF_ARG_TYPES(secret, 2, OVPN_OPT_ARG_TYPE_STRING);
OVPN_OPT_DEF_ARG(secret, 2, "direction", true);

OVPN_OPT_DEF_ARGS_BEGIN(secret)
OVPN_OPT_DEF_ARGS_ARG(secret, 1)
OVPN_OPT_DEF_ARGS_ARG(secret, 2)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__secret =
{
	.name = "secret",
	.flags = OVPN_OPT_FLAG_NORMAL |
	         OVPN_OPT_FLAG_INLINE,
	.inline_type = OVPN_OPT_INLINE_TYPE_PLAIN,
	.args = {
		/* file [direction] */
		.min = 1,
		.max = 2,
		.info = OVPN_OPT_REF_ARGS(secret)
	},
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(server, 1, OVPN_OPT_ARG_TYPE_NETWORK);
OVPN_OPT_DEF_ARG(server, 1, "network", false);

OVPN_OPT_DEF_ARG_TYPES(server, 2, OVPN_OPT_ARG_TYPE_NETMASK);
OVPN_OPT_DEF_ARG(server, 2, "netmask", false);

OVPN_OPT_DEF_ARG_TYPES(server, 3, OVPN_OPT_ARG_TYPE_LISTVALUE);
OVPN_OPT_DEF_ARG_LV(server, 3, "metric", true, "nopool");

OVPN_OPT_DEF_ARGS_BEGIN(server)
OVPN_OPT_DEF_ARGS_ARG(server, 1)
OVPN_OPT_DEF_ARGS_ARG(server, 2)
OVPN_OPT_DEF_ARGS_ARG(server, 3)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__server =
{
	.name = "server",
	.flags = OVPN_OPT_FLAG_NORMAL,
	.args = {
		/* network netmask ['nopool'] */
		.min = 2,
		.max = 3,
		.info = OVPN_OPT_REF_ARGS(server)
	},
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(server_bridge, 1,
	OVPN_OPT_ARG_TYPE_IPADDR, OVPN_OPT_ARG_TYPE_LISTVALUE);
OVPN_OPT_DEF_ARG_LV(server_bridge, 1, "gateway", true, "nogw");

OVPN_OPT_DEF_ARG_TYPES(server_bridge, 2, OVPN_OPT_ARG_TYPE_NETMASK);
OVPN_OPT_DEF_ARG(server_bridge, 2, "netmask", false);

OVPN_OPT_DEF_ARG_TYPES(server_bridge, 3, OVPN_OPT_ARG_TYPE_IPADDR);
OVPN_OPT_DEF_ARG(server_bridge, 3, "pool-start-IP", true);

OVPN_OPT_DEF_ARG_TYPES(server_bridge, 4, OVPN_OPT_ARG_TYPE_IPADDR);
OVPN_OPT_DEF_ARG(server_bridge, 4, "pool-end-IP", true);

OVPN_OPT_DEF_ARGS_BEGIN(server_bridge)
OVPN_OPT_DEF_ARGS_ARG(server_bridge, 1)
OVPN_OPT_DEF_ARGS_ARG(server_bridge, 2)
OVPN_OPT_DEF_ARGS_ARG(server_bridge, 3)
OVPN_OPT_DEF_ARGS_ARG(server_bridge, 4)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__server_bridge =
{
	.name = "server-bridge",
	.flags = OVPN_OPT_FLAG_NORMAL,
	.args = {
		/* gateway netmask pool-start-IP pool-end-IP */
		/* ['nogw'] */
		.min = 0,
		.max = 4,
		.info = OVPN_OPT_REF_ARGS(server_bridge)
	},
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(server_ipv6, 1, OVPN_OPT_ARG_TYPE_IPV6ADDR);
OVPN_OPT_DEF_ARG(server_ipv6, 1, "ipv6addr/bits", false);

OVPN_OPT_DEF_ARGS_BEGIN(server_ipv6)
OVPN_OPT_DEF_ARGS_ARG(server_ipv6, 1)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__server_ipv6 =
{
	.name = "server-ipv6",
	.flags = OVPN_OPT_FLAG_NORMAL |
	         OVPN_OPT_FLAG_IPV6,
	.args = {
		/* ipv6addr/bits */
		.min = 1,
		.max = 1,
		.info = OVPN_OPT_REF_ARGS(server_ipv6)
	},
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(server_poll_timeout, 1, OVPN_OPT_ARG_TYPE_UNUMBER);
OVPN_OPT_DEF_ARG(server_poll_timeout, 1, "n", false);

OVPN_OPT_DEF_ARGS_BEGIN(server_poll_timeout)
OVPN_OPT_DEF_ARGS_ARG(server_poll_timeout, 1)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__server_poll_timeout =
{
	.name = "server-poll-timeout",
	.flags = OVPN_OPT_FLAG_NORMAL,
	.args = {
		/* n */
		.min = 1,
		.max = 1,
		.info = OVPN_OPT_REF_ARGS(server_poll_timeout)
	},
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(service, 1, OVPN_OPT_ARG_TYPE_STRING);
OVPN_OPT_DEF_ARG(service, 1, "exit-event", false);

OVPN_OPT_DEF_ARG_TYPES(service, 2, OVPN_OPT_ARG_TYPE_UNUMBER);
OVPN_OPT_DEF_ARG_RANGE(service, 2, "0/1", true, 0, 1);

OVPN_OPT_DEF_ARGS_BEGIN(service)
OVPN_OPT_DEF_ARGS_ARG(service, 1)
OVPN_OPT_DEF_ARGS_ARG(service, 2)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__service =
{
	.name = "service",
	.flags = OVPN_OPT_FLAG_NORMAL |
	         OVPN_OPT_FLAG_WINDOWS,
	.args = {
		/* exit-event [0|1] */
		.min = 1,
		.max = 2,
		.info = OVPN_OPT_REF_ARGS(service)
	},
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(setcon, 1, OVPN_OPT_ARG_TYPE_STRING);
OVPN_OPT_DEF_ARG(setcon, 1, "context", false);

OVPN_OPT_DEF_ARGS_BEGIN(setcon)
OVPN_OPT_DEF_ARGS_ARG(setcon, 1)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__setcon =
{
	.name = "setcon",
	.flags = OVPN_OPT_FLAG_NORMAL,
	.args = {
		/* context */
		.min = 1,
		.max = 1,
		.info = OVPN_OPT_REF_ARGS(setcon)
	},
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(setenv, 1, OVPN_OPT_ARG_TYPE_STRING);
OVPN_OPT_DEF_ARG(setenv, 1, "name", false);

OVPN_OPT_DEF_ARG_TYPES(setenv, 2, OVPN_OPT_ARG_TYPE_STRING);
OVPN_OPT_DEF_ARG(setenv, 2, "value", false);

OVPN_OPT_DEF_ARGS_BEGIN(setenv)
OVPN_OPT_DEF_ARGS_ARG(setenv, 1)
OVPN_OPT_DEF_ARGS_ARG(setenv, 2)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__setenv =
{
	.name = "setenv",
	.flags = OVPN_OPT_FLAG_NORMAL |
	         OVPN_OPT_FLAG_MULTIPLE |
	         OVPN_OPT_FLAG_PUSHABLE,
	.args = {
		/* name value */
		.min = 2,
		.max = 2,
		.info = OVPN_OPT_REF_ARGS(setenv)
	},
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(setenv_safe, 1, OVPN_OPT_ARG_TYPE_STRING);
OVPN_OPT_DEF_ARG(setenv_safe, 1, "name", false);

OVPN_OPT_DEF_ARG_TYPES(setenv_safe, 2, OVPN_OPT_ARG_TYPE_STRING);
OVPN_OPT_DEF_ARG(setenv_safe, 2, "value", false);

OVPN_OPT_DEF_ARGS_BEGIN(setenv_safe)
OVPN_OPT_DEF_ARGS_ARG(setenv_safe, 1)
OVPN_OPT_DEF_ARGS_ARG(setenv_safe, 2)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__setenv_safe =
{
	.name = "setenv-safe",
	.flags = OVPN_OPT_FLAG_NORMAL |
	         OVPN_OPT_FLAG_MULTIPLE,
	.args = {
		/* name value */
		.min = 2,
		.max = 2,
		.info = OVPN_OPT_REF_ARGS(setenv_safe)
	},
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(shaper, 1, OVPN_OPT_ARG_TYPE_UNUMBER);
OVPN_OPT_DEF_ARG(shaper, 1, "n", false);

OVPN_OPT_DEF_ARGS_BEGIN(shaper)
OVPN_OPT_DEF_ARGS_ARG(shaper, 1)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__shaper =
{
	.name = "shaper",
	.flags = OVPN_OPT_FLAG_NORMAL,
	.args = {
		/* n */
		.min = 1,
		.max = 1,
		.info = OVPN_OPT_REF_ARGS(shaper)
	},
};

/* ----------------------------------------------------------------------- */

static const ovpn_opt_info_t ovpn__show_adapters =
{
	.name = "show-adapters",
	.flags = OVPN_OPT_FLAG_NORMAL |
	         OVPN_OPT_FLAG_WINDOWS |
	         OVPN_OPT_FLAG_STANDALONE
};

/* ----------------------------------------------------------------------- */

static const ovpn_opt_info_t ovpn__show_ciphers =
{
	.name = "show-ciphers",
	.flags = OVPN_OPT_FLAG_NORMAL |
	         OVPN_OPT_FLAG_STANDALONE
};

/* ----------------------------------------------------------------------- */

static const ovpn_opt_info_t ovpn__show_curves =
{
	.name = "show-curves",
	.flags = OVPN_OPT_FLAG_NORMAL |
	         OVPN_OPT_FLAG_STANDALONE
};

/* ----------------------------------------------------------------------- */

static const ovpn_opt_info_t ovpn__show_digests =
{
	.name = "show-digests",
	.flags = OVPN_OPT_FLAG_NORMAL |
	         OVPN_OPT_FLAG_STANDALONE
};

/* ----------------------------------------------------------------------- */

static const ovpn_opt_info_t ovpn__show_engines =
{
	.name = "show-engines",
	.flags = OVPN_OPT_FLAG_NORMAL |
	         OVPN_OPT_FLAG_STANDALONE
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(show_gateway, 1, OVPN_OPT_ARG_TYPE_IPV6ADDR);
OVPN_OPT_DEF_ARG(show_gateway, 1, "v6target", true);

OVPN_OPT_DEF_ARGS_BEGIN(show_gateway)
OVPN_OPT_DEF_ARGS_ARG(show_gateway, 1)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__show_gateway =
{
	.name = "show-gateway",
	.flags = OVPN_OPT_FLAG_NORMAL |
	         OVPN_OPT_FLAG_DEBUG |
	         OVPN_OPT_FLAG_STANDALONE,
	.args = {
		/* [v6target] */
		.min = 0,
		.max = 1,
		.info = OVPN_OPT_REF_ARGS(show_gateway)
	},
};

/* ----------------------------------------------------------------------- */

static const ovpn_opt_info_t ovpn__show_net =
{
	.name = "show-net",
	.flags = OVPN_OPT_FLAG_NORMAL |
	         OVPN_OPT_FLAG_WINDOWS |
	         OVPN_OPT_FLAG_STANDALONE
};

/* ----------------------------------------------------------------------- */

static const ovpn_opt_info_t ovpn__show_net_up =
{
	.name = "show-net-up",
	.flags = OVPN_OPT_FLAG_NORMAL |
	         OVPN_OPT_FLAG_WINDOWS
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(show_pkcs11_ids, 1, OVPN_OPT_ARG_TYPE_STRING);
OVPN_OPT_DEF_ARG(show_pkcs11_ids, 1, "provider", true);

OVPN_OPT_DEF_ARG_TYPES(show_pkcs11_ids, 2, OVPN_OPT_ARG_TYPE_STRING);
OVPN_OPT_DEF_ARG(show_pkcs11_ids, 2, "cert_private", true);

OVPN_OPT_DEF_ARGS_BEGIN(show_pkcs11_ids)
OVPN_OPT_DEF_ARGS_ARG(show_pkcs11_ids, 1)
OVPN_OPT_DEF_ARGS_ARG(show_pkcs11_ids, 2)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__show_pkcs11_ids =
{
	.name = "show-pkcs11-ids",
	.flags = OVPN_OPT_FLAG_NORMAL |
	         OVPN_OPT_FLAG_STANDALONE,
	.args = {
		/* [provider] [cert_private] */
		.min = 0,
		.max = 2,
		.info = OVPN_OPT_REF_ARGS(show_pkcs11_ids)
	},
};

/* ----------------------------------------------------------------------- */

static const ovpn_opt_info_t ovpn__show_proxy_settings =
{
	.name = "show-proxy-settings",
	.flags = OVPN_OPT_FLAG_NORMAL |
	         OVPN_OPT_FLAG_WINDOWS
};

/* ----------------------------------------------------------------------- */

static const ovpn_opt_info_t ovpn__show_tls =
{
	.name = "show-tls",
	.flags = OVPN_OPT_FLAG_NORMAL |
	         OVPN_OPT_FLAG_STANDALONE
};

/* ----------------------------------------------------------------------- */

static const ovpn_opt_info_t ovpn__show_valid_subnets =
{
	.name = "show-valid-subnets",
	.flags = OVPN_OPT_FLAG_NORMAL |
	         OVPN_OPT_FLAG_WINDOWS |
	         OVPN_OPT_FLAG_STANDALONE
};

/* ----------------------------------------------------------------------- */

static const ovpn_opt_info_t ovpn__single_session =
{
	.name = "single-session",
	.flags = OVPN_OPT_FLAG_NORMAL
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(sndbuf, 1, OVPN_OPT_ARG_TYPE_UNUMBER);
OVPN_OPT_DEF_ARG(sndbuf, 1, "size", false);

OVPN_OPT_DEF_ARGS_BEGIN(sndbuf)
OVPN_OPT_DEF_ARGS_ARG(sndbuf, 1)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__sndbuf =
{
	.name = "sndbuf",
	.flags = OVPN_OPT_FLAG_NORMAL |
	         OVPN_OPT_FLAG_PUSHABLE,
	.args = {
		/* size */
		.min = 1,
		.max = 1,
		.info = OVPN_OPT_REF_ARGS(sndbuf)
	},
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(socket_flags, 1, OVPN_OPT_ARG_TYPE_STRING);
OVPN_OPT_DEF_ARG(socket_flags, 1, "flags", false);

OVPN_OPT_DEF_ARGS_BEGIN(socket_flags)
OVPN_OPT_DEF_ARGS_ARG(socket_flags, 1)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__socket_flags =
{
	.name = "socket-flags",
	.flags = OVPN_OPT_FLAG_NORMAL |
	         OVPN_OPT_FLAG_CONNECTION |
	         OVPN_OPT_FLAG_PUSHABLE,
	.args = {
		/* flags... */
		.min = 1,
		.max = OVPN_OPT_ARGS_NOT_LIMITED,
		.info = OVPN_OPT_REF_ARGS(socket_flags)
	},
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(socks_proxy, 1, OVPN_OPT_ARG_TYPE_ADDRESS);
OVPN_OPT_DEF_ARG(socks_proxy, 1, "server", false);

OVPN_OPT_DEF_ARG_TYPES(socks_proxy, 2, OVPN_OPT_ARG_TYPE_PORT);
OVPN_OPT_DEF_ARG(socks_proxy, 2, "port", true);

OVPN_OPT_DEF_ARG_TYPES(socks_proxy, 3, OVPN_OPT_ARG_TYPE_FILEPATH);
OVPN_OPT_DEF_ARG(socks_proxy, 3, "authfile", true);

OVPN_OPT_DEF_ARGS_BEGIN(socks_proxy)
OVPN_OPT_DEF_ARGS_ARG(socks_proxy, 1)
OVPN_OPT_DEF_ARGS_ARG(socks_proxy, 2)
OVPN_OPT_DEF_ARGS_ARG(socks_proxy, 3)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__socks_proxy =
{
	.name = "socks-proxy",
	.flags = OVPN_OPT_FLAG_NORMAL |
	         OVPN_OPT_FLAG_CONNECTION,
	.args = {
		/* server [port] [authfile] */
		.min = 1,
		.max = 3,
		.info = OVPN_OPT_REF_ARGS(socks_proxy)
	},
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(stale_routes_check, 1, OVPN_OPT_ARG_TYPE_UNUMBER);
OVPN_OPT_DEF_ARG(stale_routes_check, 1, "n", false);

OVPN_OPT_DEF_ARG_TYPES(stale_routes_check, 2, OVPN_OPT_ARG_TYPE_UNUMBER);
OVPN_OPT_DEF_ARG(stale_routes_check, 2, "t", true);

OVPN_OPT_DEF_ARGS_BEGIN(stale_routes_check)
OVPN_OPT_DEF_ARGS_ARG(stale_routes_check, 1)
OVPN_OPT_DEF_ARGS_ARG(stale_routes_check, 2)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__stale_routes_check =
{
	.name = "stale-routes-check",
	.flags = OVPN_OPT_FLAG_NORMAL,
	.args = {
		/* n [t] */
		.min = 1,
		.max = 2,
		.info = OVPN_OPT_REF_ARGS(stale_routes_check)
	},
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(static_challenge, 1, OVPN_OPT_ARG_TYPE_STRING);
OVPN_OPT_DEF_ARG(static_challenge, 1, "t", false);

OVPN_OPT_DEF_ARG_TYPES(static_challenge, 2, OVPN_OPT_ARG_TYPE_UNUMBER);
OVPN_OPT_DEF_ARG_RANGE(static_challenge, 2, "e", false, 0, 1);

OVPN_OPT_DEF_ARGS_BEGIN(static_challenge)
OVPN_OPT_DEF_ARGS_ARG(static_challenge, 1)
OVPN_OPT_DEF_ARGS_ARG(static_challenge, 2)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__static_challenge =
{
	.name = "static-challenge",
	.flags = OVPN_OPT_FLAG_NORMAL,
	.args = {
		/* t e */
		.min = 2,
		.max = 2,
		.info = OVPN_OPT_REF_ARGS(static_challenge)
	},
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(status, 1, OVPN_OPT_ARG_TYPE_FILEPATH);
OVPN_OPT_DEF_ARG(status, 1, "file", false);

OVPN_OPT_DEF_ARG_TYPES(status, 2, OVPN_OPT_ARG_TYPE_UNUMBER);
OVPN_OPT_DEF_ARG(status, 2, "n", true);

OVPN_OPT_DEF_ARGS_BEGIN(status)
OVPN_OPT_DEF_ARGS_ARG(status, 1)
OVPN_OPT_DEF_ARGS_ARG(status, 2)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__status =
{
	.name = "status",
	.flags = OVPN_OPT_FLAG_NORMAL,
	.args = {
		/* file [n] */
		.min = 1,
		.max = 2,
		.info = OVPN_OPT_REF_ARGS(status)
	},
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(status_version, 1, OVPN_OPT_ARG_TYPE_UNUMBER);
OVPN_OPT_DEF_ARG_RANGE(status_version, 1, "n", false, 1, 3);

OVPN_OPT_DEF_ARGS_BEGIN(status_version)
OVPN_OPT_DEF_ARGS_ARG(status_version, 1)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__status_version =
{
	.name = "status-version",
	.flags = OVPN_OPT_FLAG_NORMAL,
	.args = {
		/* [n] */
		.min = 0,
		.max = 1,
		.info = OVPN_OPT_REF_ARGS(status_version)
	},
};

/* ----------------------------------------------------------------------- */

static const ovpn_opt_info_t ovpn__suppress_timestamps =
{
	.name = "suppress-timestamps",
	.flags = OVPN_OPT_FLAG_NORMAL
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(syslog, 1, OVPN_OPT_ARG_TYPE_STRING);
OVPN_OPT_DEF_ARG(syslog, 1, "progname", true);

OVPN_OPT_DEF_ARGS_BEGIN(syslog)
OVPN_OPT_DEF_ARGS_ARG(syslog, 1)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__syslog =
{
	.name = "syslog",
	.flags = OVPN_OPT_FLAG_NORMAL,
	.args = {
		/* [progname] */
		.min = 0,
		.max = 1,
		.info = OVPN_OPT_REF_ARGS(syslog)
	},
};

/* ----------------------------------------------------------------------- */

/*
 *  _______
 * |__   __|
 *    | |
 *    | |
 *    | |
 *    |_|
 *
 */

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(tap_sleep, 1, OVPN_OPT_ARG_TYPE_UNUMBER);
OVPN_OPT_DEF_ARG(tap_sleep, 1, "n", false);

OVPN_OPT_DEF_ARGS_BEGIN(tap_sleep)
OVPN_OPT_DEF_ARGS_ARG(tap_sleep, 1)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__tap_sleep =
{
	.name = "tap-sleep",
	.flags = OVPN_OPT_FLAG_NORMAL |
	         OVPN_OPT_FLAG_WINDOWS,
	.args = {
		/* n */
		.min = 1,
		.max = 1,
		.info = OVPN_OPT_REF_ARGS(tap_sleep)
	},
};

/* ----------------------------------------------------------------------- */

static const ovpn_opt_info_t ovpn__tcp_nodelay =
{
	.name = "tcp-nodelay",
	.flags = OVPN_OPT_FLAG_NORMAL
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(tcp_queue_limit, 1, OVPN_OPT_ARG_TYPE_UNUMBER);
OVPN_OPT_DEF_ARG(tcp_queue_limit, 1, "n", false);

OVPN_OPT_DEF_ARGS_BEGIN(tcp_queue_limit)
OVPN_OPT_DEF_ARGS_ARG(tcp_queue_limit, 1)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__tcp_queue_limit =
{
	.name = "tcp-queue-limit",
	.flags = OVPN_OPT_FLAG_NORMAL,
	.args = {
		/* n */
		.min = 1,
		.max = 1,
		.info = OVPN_OPT_REF_ARGS(tcp_queue_limit)
	},
};

/* ----------------------------------------------------------------------- */

static const ovpn_opt_info_t ovpn__test_crypto =
{
	.name = "test-crypto",
	.flags = OVPN_OPT_FLAG_NORMAL
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(tls_auth, 1, OVPN_OPT_ARG_TYPE_FILEPATH);
OVPN_OPT_DEF_ARG(tls_auth, 1, "file", false);

OVPN_OPT_DEF_ARG_TYPES(tls_auth, 2, OVPN_OPT_ARG_TYPE_STRING);
OVPN_OPT_DEF_ARG(tls_auth, 2, "direction", true);

OVPN_OPT_DEF_ARGS_BEGIN(tls_auth)
OVPN_OPT_DEF_ARGS_ARG(tls_auth, 1)
OVPN_OPT_DEF_ARGS_ARG(tls_auth, 2)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__tls_auth =
{
	.name = "tls-auth",
	.flags = OVPN_OPT_FLAG_NORMAL |
	         OVPN_OPT_FLAG_INLINE,
	.inline_type = OVPN_OPT_INLINE_TYPE_PLAIN,
	.args = {
		/* file [direction] */
		.min = 1,
		.max = 2,
		.info = OVPN_OPT_REF_ARGS(tls_auth)
	},
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(tls_cert_profile, 1, OVPN_OPT_ARG_TYPE_LISTVALUE);
OVPN_OPT_DEF_ARG_LV(tls_cert_profile, 1, "file", false,
	"legacy", "preferred", "suiteb");

OVPN_OPT_DEF_ARGS_BEGIN(tls_cert_profile)
OVPN_OPT_DEF_ARGS_ARG(tls_cert_profile, 1)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__tls_cert_profile =
{
	.name = "tls-cert-profile",
	.flags = OVPN_OPT_FLAG_NORMAL,
	.args = {
		/* profile */
		.min = 1,
		.max = 1,
		.info = OVPN_OPT_REF_ARGS(tls_cert_profile)
	},
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(tls_cipher, 1, OVPN_OPT_ARG_TYPE_LIST);
OVPN_OPT_DEF_ARG(tls_cipher, 1, "l", false);

OVPN_OPT_DEF_ARGS_BEGIN(tls_cipher)
OVPN_OPT_DEF_ARGS_ARG(tls_cipher, 1)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__tls_cipher =
{
	.name = "tls-cipher",
	.flags = OVPN_OPT_FLAG_NORMAL,
	.args = {
		/* l */
		.min = 1,
		.max = 1,
		.info = OVPN_OPT_REF_ARGS(tls_cipher)
	},
};

static const ovpn_opt_info_t ovpn__tls_ciphersuites =
{
	.name = "tls-ciphersuites",
	.flags = OVPN_OPT_FLAG_NORMAL,
	.args = {
		/* l */
		.min = 1,
		.max = 1,
		.info = OVPN_OPT_REF_ARGS(tls_cipher)
	},
};

/* ----------------------------------------------------------------------- */

static const ovpn_opt_info_t ovpn__tls_client =
{
	.name = "tls-client",
	.flags = OVPN_OPT_FLAG_NORMAL
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(tls_crypt, 1, OVPN_OPT_ARG_TYPE_FILEPATH);
OVPN_OPT_DEF_ARG(tls_crypt, 1, "keyfile", false);

OVPN_OPT_DEF_ARGS_BEGIN(tls_crypt)
OVPN_OPT_DEF_ARGS_ARG(tls_crypt, 1)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__tls_crypt =
{
	.name = "tls-crypt",
	.flags = OVPN_OPT_FLAG_NORMAL |
	         OVPN_OPT_FLAG_INLINE,
	.inline_type = OVPN_OPT_INLINE_TYPE_PLAIN,
	.args = {
		/* keyfile */
		.min = 1,
		.max = 1,
		.info = OVPN_OPT_REF_ARGS(tls_crypt)
	},
};

/* ----------------------------------------------------------------------- */

static const ovpn_opt_info_t ovpn__tls_exit =
{
	.name = "tls-exit",
	.flags = OVPN_OPT_FLAG_NORMAL
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(tls_export_cert, 1, OVPN_OPT_ARG_TYPE_DIR);
OVPN_OPT_DEF_ARG(tls_export_cert, 1, "directory", false);

OVPN_OPT_DEF_ARGS_BEGIN(tls_export_cert)
OVPN_OPT_DEF_ARGS_ARG(tls_export_cert, 1)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__tls_export_cert =
{
	.name = "tls-export-cert",
	.flags = OVPN_OPT_FLAG_NORMAL,
	.args = {
		/* directory */
		.min = 1,
		.max = 1,
		.info = OVPN_OPT_REF_ARGS(tls_export_cert)
	},
};

/* ----------------------------------------------------------------------- */

static const ovpn_opt_info_t ovpn__tls_server =
{
	.name = "tls-server",
	.flags = OVPN_OPT_FLAG_NORMAL
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(tls_timeout, 1, OVPN_OPT_ARG_TYPE_UNUMBER);
OVPN_OPT_DEF_ARG(tls_timeout, 1, "n", false);

OVPN_OPT_DEF_ARGS_BEGIN(tls_timeout)
OVPN_OPT_DEF_ARGS_ARG(tls_timeout, 1)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__tls_timeout =
{
	.name = "tls-timeout",
	.flags = OVPN_OPT_FLAG_NORMAL,
	.args = {
		/* n */
		.min = 1,
		.max = 1,
		.info = OVPN_OPT_REF_ARGS(tls_timeout)
	},
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(tls_verify, 1, OVPN_OPT_ARG_TYPE_COMMAND);
OVPN_OPT_DEF_ARG(tls_verify, 1, "cmd", false);

OVPN_OPT_DEF_ARGS_BEGIN(tls_verify)
OVPN_OPT_DEF_ARGS_ARG(tls_verify, 1)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__tls_verify =
{
	.name = "tls-verify",
	.flags = OVPN_OPT_FLAG_NORMAL,
	.args = {
		/* cmd */
		.min = 1,
		.max = 1,
		.info = OVPN_OPT_REF_ARGS(tls_verify)
	},
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(tls_version_min, 1, OVPN_OPT_ARG_TYPE_STRING);
OVPN_OPT_DEF_ARG(tls_version_min, 1, "version", false);

OVPN_OPT_DEF_ARG_TYPES(tls_version_min, 2, OVPN_OPT_ARG_TYPE_LISTVALUE);
OVPN_OPT_DEF_ARG_LV(tls_version_min, 2, "or-highest", true, "or-highest");

OVPN_OPT_DEF_ARGS_BEGIN(tls_version_min)
OVPN_OPT_DEF_ARGS_ARG(tls_version_min, 1)
OVPN_OPT_DEF_ARGS_ARG(tls_version_min, 2)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__tls_version_min =
{
	.name = "tls-version-min",
	.flags = OVPN_OPT_FLAG_NORMAL,
	.args = {
		/* version ['or-highest'] */
		.min = 1,
		.max = 2,
		.info = OVPN_OPT_REF_ARGS(tls_version_min)
	},
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(tls_version_max, 1, OVPN_OPT_ARG_TYPE_STRING);
OVPN_OPT_DEF_ARG(tls_version_max, 1, "version", false);

OVPN_OPT_DEF_ARGS_BEGIN(tls_version_max)
OVPN_OPT_DEF_ARGS_ARG(tls_version_max, 1)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__tls_version_max =
{
	.name = "tls-version-max",
	.flags = OVPN_OPT_FLAG_NORMAL,
	.args = {
		/* version */
		.min = 1,
		.max = 1,
		.info = OVPN_OPT_REF_ARGS(tls_version_max)
	},
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(tmp_dir, 1, OVPN_OPT_ARG_TYPE_DIR);
OVPN_OPT_DEF_ARG(tmp_dir, 1, "dir", false);

OVPN_OPT_DEF_ARGS_BEGIN(tmp_dir)
OVPN_OPT_DEF_ARGS_ARG(tmp_dir, 1)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__tmp_dir =
{
	.name = "tmp-dir",
	.flags = OVPN_OPT_FLAG_NORMAL,
	.args = {
		/* dir */
		.min = 1,
		.max = 1,
		.info = OVPN_OPT_REF_ARGS(tmp_dir)
	},
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(topology, 1, OVPN_OPT_ARG_TYPE_LISTVALUE);
OVPN_OPT_DEF_ARG_LV(topology, 1, "mode", false,
	"net30", "p2p", "subnet");

OVPN_OPT_DEF_ARGS_BEGIN(topology)
OVPN_OPT_DEF_ARGS_ARG(topology, 1)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__topology =
{
	.name = "topology",
	.flags = OVPN_OPT_FLAG_NORMAL,
	.args = {
		/* mode */
		.min = 1,
		.max = 1,
		.info = OVPN_OPT_REF_ARGS(topology)
	},
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(tran_window, 1, OVPN_OPT_ARG_TYPE_UNUMBER);
OVPN_OPT_DEF_ARG(tran_window, 1, "n", false);

OVPN_OPT_DEF_ARGS_BEGIN(tran_window)
OVPN_OPT_DEF_ARGS_ARG(tran_window, 1)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__tran_window =
{
	.name = "tran-window",
	.flags = OVPN_OPT_FLAG_NORMAL,
	.args = {
		/* n */
		.min = 1,
		.max = 1,
		.info = OVPN_OPT_REF_ARGS(tran_window)
	},
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(tun_mtu, 1, OVPN_OPT_ARG_TYPE_UNUMBER);
OVPN_OPT_DEF_ARG(tun_mtu, 1, "n", false);

OVPN_OPT_DEF_ARGS_BEGIN(tun_mtu)
OVPN_OPT_DEF_ARGS_ARG(tun_mtu, 1)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__tun_mtu =
{
	.name = "tun-mtu",
	.flags = OVPN_OPT_FLAG_NORMAL |
	         OVPN_OPT_FLAG_CONNECTION,
	.args = {
		/* n */
		.min = 1,
		.max = 1,
		.info = OVPN_OPT_REF_ARGS(tun_mtu)
	},
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(tun_mtu_extra, 1, OVPN_OPT_ARG_TYPE_UNUMBER);
OVPN_OPT_DEF_ARG(tun_mtu_extra, 1, "n", false);

OVPN_OPT_DEF_ARGS_BEGIN(tun_mtu_extra)
OVPN_OPT_DEF_ARGS_ARG(tun_mtu_extra, 1)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__tun_mtu_extra =
{
	.name = "tun-mtu-extra",
	.flags = OVPN_OPT_FLAG_NORMAL |
	         OVPN_OPT_FLAG_CONNECTION,
	.args = {
		/* n */
		.min = 1,
		.max = 1,
		.info = OVPN_OPT_REF_ARGS(tun_mtu_extra)
	},
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(txqueuelen, 1, OVPN_OPT_ARG_TYPE_UNUMBER);
OVPN_OPT_DEF_ARG(txqueuelen, 1, "n", false);

OVPN_OPT_DEF_ARGS_BEGIN(txqueuelen)
OVPN_OPT_DEF_ARGS_ARG(txqueuelen, 1)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__txqueuelen =
{
	.name = "txqueuelen",
	.flags = OVPN_OPT_FLAG_NORMAL,
	.args = {
		/* n */
		.min = 1,
		.max = 1,
		.info = OVPN_OPT_REF_ARGS(txqueuelen)
	},
};

/* ----------------------------------------------------------------------- */

/*
 *  _    _
 * | |  | |
 * | |  | |
 * | |  | |
 * | |__| |
 *  \____/
 *
 */

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(up, 1, OVPN_OPT_ARG_TYPE_COMMAND);
OVPN_OPT_DEF_ARG(up, 1, "cmd", false);

OVPN_OPT_DEF_ARGS_BEGIN(up)
OVPN_OPT_DEF_ARGS_ARG(up, 1)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__up =
{
	.name = "up",
	.flags = OVPN_OPT_FLAG_NORMAL,
	.args = {
		/* cmd */
		.min = 1,
		.max = 1,
		.info = OVPN_OPT_REF_ARGS(up)
	},
};

/* ----------------------------------------------------------------------- */

static const ovpn_opt_info_t ovpn__up_delay =
{
	.name = "up-delay",
	.flags = OVPN_OPT_FLAG_NORMAL
};

/* ----------------------------------------------------------------------- */

static const ovpn_opt_info_t ovpn__up_restart =
{
	.name = "up-restart",
	.flags = OVPN_OPT_FLAG_NORMAL
};

/* ----------------------------------------------------------------------- */

static const ovpn_opt_info_t ovpn__use_prediction_resistance =
{
	.name = "use-prediction-resistance",
	.flags = OVPN_OPT_FLAG_NORMAL
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(user, 1, OVPN_OPT_ARG_TYPE_STRING);
OVPN_OPT_DEF_ARG(user, 1, "user", false);

OVPN_OPT_DEF_ARGS_BEGIN(user)
OVPN_OPT_DEF_ARGS_ARG(user, 1)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__user =
{
	.name = "user",
	.flags = OVPN_OPT_FLAG_NORMAL,
	.args = {
		/* user */
		.min = 1,
		.max = 1,
		.info = OVPN_OPT_REF_ARGS(user)
	},
};

/* ----------------------------------------------------------------------- */

static const ovpn_opt_info_t ovpn__username_as_common_name =
{
	.name = "username-as-common-name",
	.flags = OVPN_OPT_FLAG_NORMAL
};

/* ----------------------------------------------------------------------- */

/*
 * __      __
 * \ \    / /
 *  \ \  / /
 *   \ \/ /
 *    \  /
 *     \/
 *
 */

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(verb, 1, OVPN_OPT_ARG_TYPE_UNUMBER);
OVPN_OPT_DEF_ARG_RANGE(verb, 1, "n", false, 0, 11);

OVPN_OPT_DEF_ARGS_BEGIN(verb)
OVPN_OPT_DEF_ARGS_ARG(verb, 1)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__verb =
{
	.name = "verb",
	.flags = OVPN_OPT_FLAG_NORMAL,
	.args = {
		 /* n */
		.min = 1,
		.max = 1,
		.info = OVPN_OPT_REF_ARGS(verb)
	},
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(verify_client_cert, 1, OVPN_OPT_ARG_TYPE_LISTVALUE);
OVPN_OPT_DEF_ARG_LV(verify_client_cert, 1, "mode", false,
	"none", "optional", "require");

OVPN_OPT_DEF_ARGS_BEGIN(verify_client_cert)
OVPN_OPT_DEF_ARGS_ARG(verify_client_cert, 1)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__verify_client_cert =
{
	.name = "verify-client-cert",
	.flags = OVPN_OPT_FLAG_NORMAL,
	.args = {
		/* none|optional|require */
		.min = 1,
		.max = 1,
		.info = OVPN_OPT_REF_ARGS(verify_client_cert)
	},
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(verify_hash, 1, OVPN_OPT_ARG_TYPE_STRING);
OVPN_OPT_DEF_ARG(verify_hash, 1, "hash", false);

OVPN_OPT_DEF_ARG_TYPES(verify_hash, 2, OVPN_OPT_ARG_TYPE_LISTVALUE);
OVPN_OPT_DEF_ARG_LV(verify_hash, 2, "algo", true,
	"SHA1", "SHA256");

OVPN_OPT_DEF_ARGS_BEGIN(verify_hash)
OVPN_OPT_DEF_ARGS_ARG(verify_hash, 1)
OVPN_OPT_DEF_ARGS_ARG(verify_hash, 2)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__verify_hash =
{
	.name = "verify-hash",
	.flags = OVPN_OPT_FLAG_NORMAL,
	.args = {
		/* hash [algo] */
		.min = 1,
		.max = 2,
		.info = OVPN_OPT_REF_ARGS(verify_hash)
	},
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(verify_x509_name, 1, OVPN_OPT_ARG_TYPE_STRING);
OVPN_OPT_DEF_ARG(verify_x509_name, 1, "name", false);

OVPN_OPT_DEF_ARG_TYPES(verify_x509_name, 2, OVPN_OPT_ARG_TYPE_STRING);
OVPN_OPT_DEF_ARG(verify_x509_name, 2, "type", false);

OVPN_OPT_DEF_ARGS_BEGIN(verify_x509_name)
OVPN_OPT_DEF_ARGS_ARG(verify_x509_name, 1)
OVPN_OPT_DEF_ARGS_ARG(verify_x509_name, 2)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__verify_x509_name =
{
	.name = "verify-x509-name",
	.flags = OVPN_OPT_FLAG_NORMAL,
	.args = {
		/* name type */
		.min = 2,
		.max = 2,
		.info = OVPN_OPT_REF_ARGS(verify_x509_name)
	},
};

/* ----------------------------------------------------------------------- */

/*
 * __          __
 * \ \        / /
 *  \ \  /\  / /
 *   \ \/  \/ /
 *    \  /\  /
 *     \/  \/
 *
 */

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(win_sys, 1, OVPN_OPT_ARG_TYPE_DIR);
OVPN_OPT_DEF_ARG(win_sys, 1, "path", false);

OVPN_OPT_DEF_ARGS_BEGIN(win_sys)
OVPN_OPT_DEF_ARGS_ARG(win_sys, 1)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__win_sys =
{
	.name = "win-sys",
	.flags = OVPN_OPT_FLAG_NORMAL |
	         OVPN_OPT_FLAG_WINDOWS,
	.args = {
		/* path */
		.min = 1,
		.max = 1,
		.info = OVPN_OPT_REF_ARGS(win_sys)
	},
};

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(writepid, 1, OVPN_OPT_ARG_TYPE_FILEPATH);
OVPN_OPT_DEF_ARG(writepid, 1, "file", false);

OVPN_OPT_DEF_ARGS_BEGIN(writepid)
OVPN_OPT_DEF_ARGS_ARG(writepid, 1)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__writepid =
{
	.name = "writepid",
	.flags = OVPN_OPT_FLAG_NORMAL,
	.args = {
		/* file */
		.min = 1,
		.max = 1,
		.info = OVPN_OPT_REF_ARGS(writepid)
	},
};

/* ----------------------------------------------------------------------- */

/*
 * __   __
 * \ \ / /
 *  \ V /
 *   > <
 *  / . \
 * /_/ \_\
 *
 */

/* ----------------------------------------------------------------------- */

OVPN_OPT_DEF_ARG_TYPES(x509_username_field, 1, OVPN_OPT_ARG_TYPE_STRING);
OVPN_OPT_DEF_ARG(x509_username_field, 1, "fieldname", false);

OVPN_OPT_DEF_ARGS_BEGIN(x509_username_field)
OVPN_OPT_DEF_ARGS_ARG(x509_username_field, 1)
OVPN_OPT_DEF_ARGS_END()

static const ovpn_opt_info_t ovpn__x509_username_field =
{
	.name = "x509-username-field",
	.flags = OVPN_OPT_FLAG_NORMAL,
	.args = {
		/* [ext:]fieldname */
		.min = 1,
		.max = 1,
		.info = OVPN_OPT_REF_ARGS(x509_username_field)
	},
};

/* ----------------------------------------------------------------------- */

/*
 * __     __
 * \ \   / /
 *  \ \_/ /
 *   \   /
 *    | |
 *    |_|
 *
 */

/* Nothing */

/*
 *  ______
 * |___  /
 *    / /
 *   / /
 *  / /__
 * /_____|
 *
 */

/* Nothing */

/**
 * All supported OpenVPN configuration options and inlines
 */
static const ovpn_opt_info_t *ovpn_options[] =
{
	/* A */
	&ovpn__allow_nonadmin,
	&ovpn__allow_pull_fqdn,
	&ovpn__allow_recursive_routing,
	&ovpn__askpass,
	&ovpn__auth,
	&ovpn__auth_gen_token,
	&ovpn__auth_nocache,
	&ovpn__auth_retry,
	&ovpn__auth_token,
	&ovpn__auth_user_pass,
	&ovpn__auth_user_pass_optional,
	&ovpn__auth_user_pass_verify,

	/* B */
	&ovpn__bcast_buffers,
	&ovpn__bind,
	&ovpn__block_outside_dns,

	/* C */
	&ovpn__ca,
	&ovpn__capath,
	&ovpn__ccd_exclusive,
	&ovpn__cd,
	&ovpn__cert,
	&ovpn__chroot,
	&ovpn__cipher,
	&ovpn__client,
	&ovpn__client_cert_not_required,
	&ovpn__client_config_dir,
	&ovpn__client_connect,
	&ovpn__client_disconnect,
	&ovpn__client_nat,
	&ovpn__client_to_client,
	&ovpn__compat_names,
	&ovpn__comp_lzo,
	&ovpn__comp_noadapt,
	&ovpn__compress,
	&ovpn__connect_freq,
	&ovpn__connect_retry,
	&ovpn__connect_retry_max,
	&ovpn__connect_timeout,
	&ovpn__connection,
	&ovpn__crl_verify,
	&ovpn__cryptoapicert,

	/* D */
	&ovpn__daemon,
	&ovpn__dev,
	&ovpn__dev_node,
	&ovpn__dev_type,
	&ovpn__dh,
	&ovpn__dhcp_option,
	&ovpn__dhcp_release,
	&ovpn__dhcp_renew,
	&ovpn__disable,
	&ovpn__disable_occ,
	&ovpn__down,
	&ovpn__down_pre,
	&ovpn__duplicate_cn,

	/* E */
	&ovpn__ecdh_curve,
	&ovpn__echo,
	&ovpn__engine,
	&ovpn__errors_to_stderr,
	&ovpn__explicit_exit_notify,
	&ovpn__extra_certs,

	/* F */
	&ovpn__fast_io,
	&ovpn__float,
	&ovpn__fragment,

	/* G */
	&ovpn__genkey,
	&ovpn__group,

	/* H */
	&ovpn__hand_window,
	&ovpn__hash_size,
	&ovpn__http_proxy,
	&ovpn__http_proxy_option,
	&ovpn__http_proxy_user_pass,

	/* I */
	&ovpn__ifconfig,
	&ovpn__ifconfig_ipv6,
	&ovpn__ifconfig_ipv6_pool,
	&ovpn__ifconfig_ipv6_push,
	&ovpn__ifconfig_noexec,
	&ovpn__ifconfig_nowarn,
	&ovpn__ifconfig_pool,
	&ovpn__ifconfig_pool_linear,
	&ovpn__ifconfig_pool_persist,
	&ovpn__ifconfig_push,
	&ovpn__ignore_unknown_option,
	&ovpn__inactive,
	&ovpn__ip_win32,
	&ovpn__ipchange,
	&ovpn__inetd,
	&ovpn__iproute,
	&ovpn__iroute,
	&ovpn__iroute_ipv6,

	/* J - Nothing */

	/* K */
	&ovpn__keepalive,
	&ovpn__key,
	&ovpn__key_direction,
	&ovpn__key_method,
	&ovpn__keying_material_exporter,
	&ovpn__keysize,

	/* L */
	&ovpn__learn_address,
	&ovpn__link_mtu,
	&ovpn__lladdr,
	&ovpn__local,
	&ovpn__log,
	&ovpn__log_append,
	&ovpn__lport,

	/* M */
	&ovpn__machine_readable_output_client,
	&ovpn__management,
	&ovpn__management_client,
	&ovpn__management_client_auth,
	&ovpn__management_client_group,
	&ovpn__management_client_pf,
	&ovpn__management_client_user,
	&ovpn__management_external_cert,
	&ovpn__management_external_key,
	&ovpn__management_forget_disconnect,
	&ovpn__management_hold,
	&ovpn__management_log_cache,
	&ovpn__management_query_passwords,
	&ovpn__management_query_proxy,
	&ovpn__management_query_remote,
	&ovpn__management_signal,
	&ovpn__management_up_down,
	&ovpn__mark,
	&ovpn__max_clients,
	&ovpn__max_routes_per_client,
	&ovpn__mktun,
	&ovpn__mlock,
	&ovpn__mode,
	&ovpn__mssfix,
	&ovpn__mtu_disc,
	&ovpn__mtu_test,
	&ovpn__multihome,
	&ovpn__mute,
	&ovpn__mute_replay_warnings,

	/* N */
	&ovpn__ncp_ciphers,
	&ovpn__ncp_disable,
	&ovpn__nice,
	&ovpn__no_iv,
	&ovpn__no_replay,
	&ovpn__no_name_remapping,
	&ovpn__nobind,
	&ovpn__ns_cert_type,

	/* O */
	&ovpn__opt_verify,

	/* P */
	&ovpn__passtos,
	&ovpn__pause_exit,
	&ovpn__persist_key,
	&ovpn__persist_local_ip,
	&ovpn__persist_remote_ip,
	&ovpn__persist_tun,
	&ovpn__ping,
	&ovpn__ping_exit,
	&ovpn__ping_restart,
	&ovpn__ping_timer_rem,
	&ovpn__pkcs11_cert_private,
	&ovpn__pkcs11_id,
	&ovpn__pkcs11_id_management,
	&ovpn__pkcs11_pin_cache,
	&ovpn__pkcs11_protected_authentification,
	&ovpn__pkcs11_providers,
	&ovpn__pkcs11_private_mode,
	&ovpn__pkcs12,
	&ovpn__plugin,
	&ovpn__port,
	&ovpn__port_share,
	&ovpn__prng,
	&ovpn__proto,
	&ovpn__proto_force,
	&ovpn__pull,
	&ovpn__pull_filter,
	&ovpn__push,
	&ovpn__push_peer_info,
	&ovpn__push_remove,
	&ovpn__push_reset,

	/* Q - Nothing */

	/* R */
	&ovpn__rcvbuf,
	&ovpn__redirect_gateway,
	&ovpn__redirect_private,
	&ovpn__register_dns,
	&ovpn__remap_usr1,
	&ovpn__remote,
	&ovpn__remote_cert_eku,
	&ovpn__remote_cert_ku,
	&ovpn__remote_cert_tls,
	&ovpn__remote_random,
	&ovpn__remote_random_hostname,
	&ovpn__reneg_bytes,
	&ovpn__reneg_pkts,
	&ovpn__reneg_sec,
	&ovpn__replay_persist,
	&ovpn__replay_window,
	&ovpn__resolv_retry,
	&ovpn__rmtun,
	&ovpn__route,
	&ovpn__route_delay,
	&ovpn__route_gateway,
	&ovpn__route_ipv6,
	&ovpn__route_method,
	&ovpn__route_metric,
	&ovpn__route_noexec,
	&ovpn__route_nopull,
	&ovpn__route_pre_down,
	&ovpn__route_up,
	&ovpn__rport,

	/* S */
	&ovpn__script_security,
	&ovpn__secret,
	&ovpn__server,
	&ovpn__server_bridge,
	&ovpn__server_ipv6,
	&ovpn__server_poll_timeout,
	&ovpn__service,
	&ovpn__setcon,
	&ovpn__setenv,
	&ovpn__setenv_safe,
	&ovpn__shaper,
	&ovpn__show_adapters,
	&ovpn__show_ciphers,
	&ovpn__show_curves,
	&ovpn__show_digests,
	&ovpn__show_engines,
	&ovpn__show_gateway,
	&ovpn__show_net,
	&ovpn__show_net_up,
	&ovpn__show_pkcs11_ids,
	&ovpn__show_proxy_settings,
	&ovpn__show_tls,
	&ovpn__show_valid_subnets,
	&ovpn__single_session,
	&ovpn__sndbuf,
	&ovpn__socket_flags,
	&ovpn__socks_proxy,
	&ovpn__stale_routes_check,
	&ovpn__static_challenge,
	&ovpn__status,
	&ovpn__status_version,
	&ovpn__suppress_timestamps,
	&ovpn__syslog,

	/* T */
	&ovpn__tap_sleep,
	&ovpn__tcp_nodelay,
	&ovpn__tcp_queue_limit,
	&ovpn__test_crypto,
	&ovpn__tls_auth,
	&ovpn__tls_cert_profile,
	&ovpn__tls_cipher,
	&ovpn__tls_ciphersuites,
	&ovpn__tls_client,
	&ovpn__tls_crypt,
	&ovpn__tls_exit,
	&ovpn__tls_export_cert,
	&ovpn__tls_server,
	&ovpn__tls_timeout,
	&ovpn__tls_verify,
	&ovpn__tls_version_min,
	&ovpn__tls_version_max,
	&ovpn__tmp_dir,
	&ovpn__topology,
	&ovpn__tran_window,
	&ovpn__tun_mtu,
	&ovpn__tun_mtu_extra,
	&ovpn__txqueuelen,

	/* U */
	&ovpn__up,
	&ovpn__up_delay,
	&ovpn__up_restart,
	&ovpn__use_prediction_resistance,
	&ovpn__user,
	&ovpn__username_as_common_name,

	/* V */
	&ovpn__verb,
	&ovpn__verify_client_cert,
	&ovpn__verify_hash,
	&ovpn__verify_x509_name,

	/* W */
	&ovpn__win_sys,
	&ovpn__writepid,

	/* X */
	&ovpn__x509_username_field,

	/* Y - Nothing */

	/* Z - Nothing */

	NULL,
};

const ovpn_opt_info_t *ovpn_opt_find(const char *name, unsigned int flags, size_t num)
{
	int i;

	if (!name)
		return NULL;

	for (i = 0; ovpn_options[i]; i++)
	{
		if (strncmp(ovpn_options[i]->name, name, num) == 0)
		{
			if ((ovpn_options[i]->flags & flags) == flags)
				return ovpn_options[i];
		}
	}

	return NULL;
}
