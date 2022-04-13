/*
 *----------------------------------------------------------------------
 *    T-Kernel 2.0 Software Package
 *
 *    Copyright 2011 by Ken Sakamura.
 *    This software is distributed under the latest version of T-License 2.x.
 *----------------------------------------------------------------------
 *
 *    Released by T-Engine Forum(http://www.t-engine.org/) at 2011/05/17.
 *    Modified by T-Engine Forum at 2013/02/28.
 *    Modified by TRON Forum(http://www.tron.org/) at 2015/06/01.
 *
 *----------------------------------------------------------------------
 */

/*
 *	syslog.c (libsys)
 */

#include <stdarg.h>
#include <sys/syslog.h>

extern int tm_vsprintf(char *str, const char *format, va_list ap);
extern int __logmask;

void syslog( int priority, const char *format, ... )
{
	va_list	ap;
	char	buf[256];
	int	len;

	if ( (LOG_MASK(priority & LOG_PRIMASK) & __logmask) != 0 ) {
		va_start(ap, format);
		len = tm_vsprintf(buf, format, ap);
		va_end(ap);
		if ( len >= sizeof(buf) ) len = sizeof(buf) - 1;
		if ( len > 0 ) _syslog_send(buf, len);
	}
}
