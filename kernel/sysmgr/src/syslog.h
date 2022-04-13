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
 *	syslog.h (T-Kernel/SM)
 *	System Log Task Definition
 */

#ifndef _SYSLOG_
#define _SYSLOG_

#define USE_SYSLOG_CONSIO 0		/* Use console IO for system log
					   (useful for system analysis and for debug because this makes
					    syslog() to work without waits, unlike tm_printf() and the like
					    which affect the timing of system execution) */

#define MBF_LOG_BUFSZ	(1024*6)	/* Size of message buffer for log */
#define MBF_LOG_MAXMSZ	256		/* Maximum length of log message */

#endif /* _SYSLOG_ */
