/*
 *----------------------------------------------------------------------
 *    T-Kernel 2.0 Software Package
 *
 *    Copyright 2011 by Ken Sakamura.
 *    This software is distributed under the latest version of T-License 2.x.
 *----------------------------------------------------------------------
 *
 *    Released by T-Engine Forum(http://www.t-engine.org/) at 2011/05/17.
 *    Modified by T-Engine Forum at 2013/02/26.
 *    Modified by TRON Forum(http://www.tron.org/) at 2015/06/01.
 *
 *----------------------------------------------------------------------
 */

/*
 *      gdevcnf.c (sysinit)
 *      DEVCONF access utilities
 */

#include "sysinit.h"
#include <device/devconf.h>
#include <sys/sysinfo.h>
#include <libstr.h>
#define DevConfPtr	(SCInfo.devconf)

/* Defined in T-Kernel/SM as internal functions */
IMPORT INT getcfn( CONST UB *conf, CONST UB *name, INT *val, INT max );
IMPORT INT getcfs( CONST UB *conf, CONST UB *name, UB *bp, INT max );


EXPORT	W	GetDevConf(UB *name, W *val)
{
	return getcfn(DevConfPtr, name, (INT*)val, L_DEVCONF_VAL);
}

EXPORT	W	GetDevConfStr(UB *name, UB *str)
{
	return getcfs(DevConfPtr, name, str, L_DEVCONF_STR);
}
