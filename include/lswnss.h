/*
 * NSS boilerplate stuff, for libreswan.
 *
 * Copyright (C) 2016, Andrew Cagney <cagney@gnu.org>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.  See <https://www.gnu.org/licenses/gpl2.txt>.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 */

#ifndef _LSWNSS_H_
#define _LSWNSS_H_

#include <prerror.h>		/* for PRErrorCode, for PR_GetError() */
#include <pk11pub.h>

#include "lswcdefs.h"		/* for PRINTF_LIKE() */
#include "lset.h"
#include "lswalloc.h"
#include "secrets.h"

enum lsw_nss_flags {
	LSW_NSS_READONLY = 1,
	/*
	 * Should shutdown call PR_CLEANUP.
	 */
	LSW_NSS_SKIP_PR_CLEANUP = 2,
};

/*
 * If something goes wrong, the error gets dumped into this null
 * terminated buffer.
 */
typedef char lsw_nss_buf_t[100];

bool lsw_nss_setup(const char *config_dir, unsigned flags,
		   PK11PasswordFunc get_nss_password, lsw_nss_buf_t err);
void lsw_nss_shutdown(void);

/*
 * Just in case, at some point passing a parameter becomes somehow
 * useful.
 */
#define lsw_return_nss_password_file_info() NULL

char *lsw_nss_get_password(PK11SlotInfo *slot, PRBool retry, void *arg);

PK11SlotInfo *lsw_nss_get_authenticated_slot(lsw_nss_buf_t err);

/* _(SECERR: N (0xX): <error-string>) */
void log_nss_error(lset_t rc_log, struct logger *logger, PRErrorCode pr_error,
		   const char *message, ...) PRINTF_LIKE(4);

size_t jam_nss_error(struct jambuf *log);
size_t jam_nss_ckm(struct jambuf *buf, CK_MECHANISM_TYPE mechanism);
size_t jam_nss_ckf(struct jambuf *buf, CK_FLAGS flags);
size_t jam_nss_cka(struct jambuf *buf, CK_ATTRIBUTE_TYPE attribute);
size_t jam_nss_secitem(struct jambuf *buf, const SECItem *secitem);

#endif
