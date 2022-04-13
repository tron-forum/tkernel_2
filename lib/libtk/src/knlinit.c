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
 *	@(#)knlinit.c (libtk)
 *
 *	KnlInit() is always linked as it is called from the
 *	manager startup part.
 *	Note that adding too many processing can make the
 *	program quite large.
 */

#include <basic.h>
#include <sys/commarea.h>
#include <tk/sysmgr.h>

/*
 * Kernel utility initialization
 */
EXPORT void KnlInit( void )
{
	if ( __CommArea == NULL ) {
		/* Get kernel common data area */
		_GetKernelCommonArea(&__CommArea);
	}
}
