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
 *      conf.c          screen driver
 *
 *      initialization table that is tailored to the needs of video board and chip
 *
 */
#include	<basic.h>

/* EM1 LCD controller initialization processing */
IMPORT	W	EM1LCDCInit(void);

/*
        initialization table that is tailored to the needs of video board and chip
*/
EXPORT	FUNCP	VideoFunc[] = {
	(FUNCP)EM1LCDCInit,	/* internal */
	NULL,
};
