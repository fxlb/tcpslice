/*
 * Copyright (c) 2000
 *	The Tcpdump Group and contributors.  All rights reserved.
 * Copyright (c) 1992, 1993, 1995, 1996, 2000
 *	The Regents of the University of California.  All rights reserved.
 *
 * SPDX-License-Identifier: BSD-4-Clause-Shortened
 */

/*
 * gwtm2secs.c - convert "tm" structs for Greenwich time to Unix timestamp
 */

#include <config.h>

#include <sys/types.h>

#include <time.h>

#ifdef HAVE_OS_PROTO_H
#include "os-proto.h"
#endif

#include "tcpslice.h"

const int days_in_month[] =
	/* Jan Feb Mar Apr May Jun Jul Aug Sep Oct Nov Dec */
	{  31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

time_t
gwtm2secs( const struct tm *tm )
{
	int i, days, year;

	/* tm_year is either:
	 * a) the result from localtime()
	 * b) a 4-digit year specified on the command line minus 1900
	 * c) a 2-digit year specified on the command line
	 * in order to handle years from 2000 to 2069 specified as c), we
	 * check for years prior to 1970, which we can't handle anyway.
	 * (actually, for zones west of GMT, there are a few hours at
	 * the end of 1969, but we assume that nobody has traces taken
	 * during those hours.)
	 */
	year = tm->tm_year + 1900;
	if ( year < 1970 )
		year += 100;

	days = 0;
	for ( i = 1970; i < year; ++i )
	{
		days += 365;
		if ( IS_LEAP_YEAR(i) )
			++days;
	}

	for ( i = 0; i < tm->tm_mon; ++i )
		days += days_in_month[i];

	if ( IS_LEAP_YEAR(year) && tm->tm_mon > 1 ) /* 1 is February */
		++days;

	days += tm->tm_mday - 1; /* -1 since days are numbered starting at 1 */

	return days * 86400 + tm->tm_hour * 3600 + tm->tm_min * 60 + tm->tm_sec;
}
