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
 *	@(#)tm_writedisk.S (libtm)
 *
 *	Write to disk
 */
#define	_in_asm_source_

#include "tmon.h"

/*
 * INT tm_writedisk( UB *dev, INT sblk, INT nblks, void *addr )
 */
TMCALL(tm_writedisk, TM_WRITEDISK)
