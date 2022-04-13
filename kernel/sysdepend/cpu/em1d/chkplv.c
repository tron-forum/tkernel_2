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
 *	chkplv.c (EM1-D512)
 *	Check Call Protected Level
 */

#include "sysmgr.h"
#include <sys/sysinfo.h>

IMPORT INT	svc_call_limit;	/* SVC protected level (T-Kernel/OS) */

Inline INT PPL( void )
{
	return (SCInfo.taskmode >> 16) & 3;
}

/*
 * Check protected level of extended SVC caller
 */
EXPORT ER ChkCallPLevel( void )
{
	return ( PPL() > svc_call_limit )? E_OACV: E_OK;
}
