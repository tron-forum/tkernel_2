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
 *	@(#)tm_getline.S (libtm)
 *
 *	Input single line from console
 */
#define	_in_asm_source_

#include "tmon.h"

/*
 * INT tm_getline( UB *buff )
 */
TMCALL(tm_getline, TM_GETLINE)
