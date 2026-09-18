/*
 * Copyright (c) 2001
 *	The Tcpdump Group and contributors.  All rights reserved.
 * Copyright (c) 1997
 *	The Regents of the University of California.  All rights reserved.
 *
 * SPDX-License-Identifier: BSD-4-Clause-Shortened
 */

#include <config.h>

#include <sys/types.h>
#include <sys/time.h>

#include <stdio.h>
#include <time.h>

#ifdef HAVE_OS_PROTO_H
#include "os-proto.h"
#endif

#include "tcpslice.h"

/*
 * Returns the difference between gmt and local time in seconds.
 * Use gmtime() and localtime() to keep things simple.
 */
int32_t
gmt2local(time_t t)
{
	int dt, dir;
	struct tm *gmt, *loc;
	struct tm sgmt;

	if (t == 0)
		t = time(NULL);
	gmt = &sgmt;
	*gmt = *gmtime(&t);
	loc = localtime(&t);
	dt = (loc->tm_hour - gmt->tm_hour) * 60 * 60 +
	    (loc->tm_min - gmt->tm_min) * 60;

	/*
	 * If the year or Julian day is different, we span 00:00 GMT
	 * and must add or subtract a day. Check the year first to
	 * avoid problems when the Julian day wraps.
	 */
	dir = loc->tm_year - gmt->tm_year;
	if (dir == 0)
		dir = loc->tm_yday - gmt->tm_yday;
	dt += dir * 24 * 60 * 60;

	return (dt);
}
