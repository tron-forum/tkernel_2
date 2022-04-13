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
 *	power.c (EM1-D512)
 *	Power-Saving Function
 */

#include "sysmgr.h"

/*
 * Switch to power-saving mode
 */
EXPORT void low_pow( void )
{
	Asm("mcr p15, 0, %0, cr7, c0, 4":: "r"(0));
}

/*
 * Move to suspend mode
 */
EXPORT void off_pow( void )
{
	Asm("mcr p15, 0, %0, cr7, c0, 4":: "r"(0));
}
