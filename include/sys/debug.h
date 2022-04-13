/*
 *----------------------------------------------------------------------
 *    T-Kernel 2.0 Software Package
 *
 *    Copyright 2011 by Ken Sakamura.
 *    This software is distributed under the latest version of T-License 2.x.
 *----------------------------------------------------------------------
 *
 *    Released by T-Engine Forum(http://www.t-engine.org/) at 2011/05/17.
 *    Modified by T-Engine Forum at 2013/03/07.
 *    Modified by TRON Forum(http://www.tron.org/) at 2015/06/01.
 *
 *----------------------------------------------------------------------
 */

/*
 *	@(#)debug.h (sys)
 *
 *	Debug support
 */

#ifndef	__SYS_DEBUG_H__
#define __SYS_DEBUG_H__

#include <basic.h>

#ifdef DEBUG
#include <tm/tmonitor.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Example
 *	DEBUG_PRINT(("error = %d\n", ercd));
 *
 *	DO_DEBUG( if ( ercd < ER_OK ) DEBUG_PRINT(("error = %d\n", ercd)); )
 */
#ifdef DEBUG

#ifndef DEBUG_MODULE
#define DEBUG_MODULE	""	/* Normally define like "(module name)" */
#endif

#define DEBUG_PRINT(arg)						\
	(								\
		tm_printf("%s#%d%s:", __FILE__, __LINE__, DEBUG_MODULE),	\
		tm_printf arg						\
	)
#define TM_DEBUG_PRINT(arg)						\
	(								\
		tm_printf("%s#%d%s:", __FILE__, __LINE__, DEBUG_MODULE), \
		tm_printf arg						\
	)

#define DO_DEBUG(exp)	{ exp }

#else /* DEBUG */

#define DEBUG_PRINT(arg)	/* arg */
#define TM_DEBUG_PRINT(arg)	/* arg */
#define DO_DEBUG(exp)		/* exp */

#endif /* DEBUG */

#ifdef __cplusplus
}
#endif
#endif /* __SYS_DEBUG_H__ */
