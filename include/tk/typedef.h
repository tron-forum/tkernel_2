/*
 *----------------------------------------------------------------------
 *    T-Kernel 2.0 Software Package
 *
 *    Copyright 2011 by Ken Sakamura.
 *    This software is distributed under the latest version of T-License 2.x.
 *----------------------------------------------------------------------
 *
 *    Released by T-Engine Forum(http://www.t-engine.org/) at 2011/05/17.
 *    Modified by TRON Forum(http://www.tron.org/) at 2015/06/01.
 *
 *----------------------------------------------------------------------
 */

/*
 *	@(#)typedef.h (T-Kernel)
 *
 *	T-Kernel Standard Data Type Definition
 */

#ifndef	__TK_TYPEDEF_H__
#define __TK_TYPEDEF_H__

#include <basic.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Data type in which meaning is defined in T-Kernel/OS specification
 */
typedef INT		FN;		/* Function code */
typedef INT		RNO;		/* Rendezvous number */
typedef UW		ATR;		/* Object/handler attribute */
typedef INT		ER;		/* Error code */
typedef INT		PRI;		/* Priority */
typedef W		TMO;		/* Time out setting (ms) */
typedef D		TMO_U;		/* Time out setting (us) */
typedef UW		RELTIM;		/* Relative time (ms) */
typedef UD		RELTIM_U;	/* Relative time (us) */

typedef struct systim {			/* System time (ms) */
	W	hi;			/* Upper 32 bits */
	UW	lo;			/* Lower 32 bits */
} SYSTIM;

typedef	D	SYSTIM_U;		/* System time (us) */

/*
 * Common constant
 */
#define NULL		0		/* Invalid address */
#define TA_NULL		0U		/* No special attributes indicated */
#define TMO_POL		0		/* Polling */
#define TMO_FEVR	(-1)		/* Permanent wait */

/* ------------------------------------------------------------------------ */

/*
 * 64 bits value
 */
typedef struct dw {
#if BIGENDIAN
	W	hi;	/* Upper 32 bits */
	UW	lo;	/* Lower 32 bits */
#else
	UW	lo;	/* Lower 32 bits */
	W	hi;	/* Upper 32 bits */
#endif
} DW;

#ifdef __cplusplus
}
#endif
#endif /* __TK_TYPEDEF_H__ */
