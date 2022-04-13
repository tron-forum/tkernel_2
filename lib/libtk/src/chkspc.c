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
 *	@(#)chkspc.c (libtk)
 *
 *	Address check
 */

#include <basic.h>
#include <tk/syslib.h>
#include <sys/segment.h>

#if VIRTUAL_ADDRESS

#include "getsvcenv.h"

/*
 * Check address space
 *	Checks to see that the memory space from address to the
 *	len byte is valid.
 */
EXPORT ER ChkSpaceR( CONST void *addr, INT len )
{
	return ChkSpace(addr, len, MA_READ, getsvcenv());
}
EXPORT ER ChkSpaceRW( CONST void *addr, INT len )
{
	return ChkSpace(addr, len, MA_READ|MA_WRITE, getsvcenv());
}
EXPORT ER ChkSpaceRE( CONST void *addr, INT len )
{
	return ChkSpace(addr, len, MA_READ|MA_EXECUTE, getsvcenv());
}

#else /* VIRTUAL_ADDRESS */

EXPORT ER ChkSpaceR( CONST void *addr, INT len )
{
	return E_OK;
}
EXPORT ER ChkSpaceRW( CONST void *addr, INT len )
{
	return E_OK;
}
EXPORT ER ChkSpaceRE( CONST void *addr, INT len )
{
	return E_OK;
}

#endif /* VIRTUAL_ADDRESS */
