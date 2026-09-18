/*
 * Copyright (c) 2001
 *	The Tcpdump Group and contributors.  All rights reserved.
 * Copyright (c) 1993, 1995, 1996
 *	The Regents of the University of California.  All rights reserved.
 *
 * SPDX-License-Identifier: BSD-4-Clause-Shortened
 */

#include <config.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <time.h>

#ifdef HAVE_OS_PROTO_H
#include "os-proto.h"
#endif

#include "tcpslice.h"

static void
complain(const char *fmt, va_list ap)
{
	(void)fprintf(stderr, "tcpslice: ");
	(void)vfprintf(stderr, fmt, ap);
	if (*fmt) {
		fmt += strlen(fmt);
		if (fmt[-1] != '\n')
			(void)fputc('\n', stderr);
	}
}

/* VARARGS */
void
warning(const char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	complain(fmt, ap);
	va_end(ap);
}

/* VARARGS */
void
error(const char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	complain(fmt, ap);
	va_end(ap);
	exit(1);
	/* NOTREACHED */
}
