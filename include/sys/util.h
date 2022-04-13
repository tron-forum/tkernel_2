/*
 *----------------------------------------------------------------------
 *    T-Kernel 2.0 Software Package
 *
 *    Copyright 2011 by Ken Sakamura.
 *    This software is distributed under the latest version of T-License 2.x.
 *----------------------------------------------------------------------
 *
 *    Released by T-Engine Forum(http://www.t-engine.org/) at 2011/05/17.
 *    Modified by T-Engine Forum at 2013/02/12.
 *    Modified by TRON Forum(http://www.tron.org/) at 2015/06/01.
 *
 *----------------------------------------------------------------------
 */

/*
 *	@(#)util.h (sys)
 *
 *	Manager utilities
 */

#ifndef __SYS_UTIL_H__
#define __SYS_UTIL_H__

#include <basic.h>
#include <tk/typedef.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * SYSCONF definition
 */
#define L_SYSCONF_VAL		16	/* Maximum number of elements */
#define L_SYSCONF_STR		256	/* Maximum string length */

/* Device related */
IMPORT ID	GetDevEvtMbf(void);

/* Memory allocation */
IMPORT void*	Smalloc(size_t size);
IMPORT void*	Scalloc(size_t nmemb, size_t size);
IMPORT void*	Srealloc(void *ptr, size_t size);
IMPORT void	Sfree(void *ptr);
IMPORT void	Smalloctest(int mode);
IMPORT BOOL	Smalloccheck(void *ptr);
IMPORT void	Kmalloctest(int mode);
IMPORT BOOL	Kmalloccheck(void *ptr);
IMPORT void	Vmalloctest(int mode);
IMPORT BOOL	Vmalloccheck(void *ptr);

/* Error code conversion */
IMPORT BOOL	_isDebugMode( void );
IMPORT BOOL	_isFsrcvMode( void );

/* Other */
IMPORT void _InitLibtk(void);
IMPORT void KnlInit(void);

#ifdef __cplusplus
}
#endif
#endif /*
 * Library (libtk) initialization
 *	The library is normally initialized automatically,
 *	so these functions do not need to be called explicitly.
 */
