/*
 *----------------------------------------------------------------------
 *    T-Kernel 2.0 Software Package
 *
 *    Copyright 2011 by Ken Sakamura.
 *    This software is distributed under the latest version of T-License 2.x.
 *----------------------------------------------------------------------
 *
 *    Released by T-Engine Forum(http://www.t-engine.org/) at 2011/05/17.
 *    Modified by T-Engine Forum at 2013/03/02. 
 *    Modified by TRON Forum(http://www.tron.org/) at 2015/06/01.
 *
 *----------------------------------------------------------------------
 */

/*
 *	inittask_def.c (extension)
 *	Initial task definition
 */

#include "inittask_def.h"

IMPORT void init_task(void);

/*
 * Initial task creation parameter
 */
EXPORT const T_CTSK c_init_task = {
	(void*)INITTASK_EXINF,	/* exinf */
	INITTASK_TSKATR,	/* tskatr */
	(FP)&init_task,		/* task */
	INITTASK_ITSKPRI,	/* itskpri */
	INITTASK_STKSZ,		/* stksz */
	INITTASK_SSTKSZ,	/* sstksz */
	(void*)INITTASK_STKPTR,	/* stkptr */
	(void*)INITTASK_UATB,	/* uatb */
	INITTASK_LSID,		/* lsid */
	INITTASK_RESID		/* resid */
};
