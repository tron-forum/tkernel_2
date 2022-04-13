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
 *	@(#)getdembf.c (libtk)
 */

#include <basic.h>
#include <sys/util.h>
#include <tk/tkernel.h>

/*
	Get message buffer for device event notice
*/
EXPORT	ID	GetDevEvtMbf( void )
{
	T_IDEV	idev;
	tk_ref_idv(&idev);
	return idev.evtmbfid;
}
