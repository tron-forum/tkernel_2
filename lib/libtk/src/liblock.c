/*
 *----------------------------------------------------------------------
 *    T-Kernel 2.0 Software Package
 *
 *    Copyright 2011 by Ken Sakamura.
 *    This software is distributed under the latest version of T-License 2.x.
 *----------------------------------------------------------------------
 *
 *    Released by T-Engine Forum(http://www.t-engine.org/) at 2011/05/17.
 *    Modified by T-Engine Forum at 2013/01/12.
 *    Modified by TRON Forum(http://www.tron.org/) at 2015/06/01.
 *
 *----------------------------------------------------------------------
 */

/*
 *	@(#)liblock.c (libtk)
 *
 *	Shared exclusive control lock in library
 */

#include "libtk.h"
#include <sys/util.h>
#include <tk/util.h>

LOCAL	FastMLock	LibLock;

/* Set Object Name in .exinf for DEBUG */
#define OBJNAME_LIBLOCK		"lltk"	/* multi-lock object name for liblock */

EXPORT ER _init_liblock( void )
{
	return CreateMLock(&LibLock, (UB*)OBJNAME_LIBLOCK);
}

EXPORT ER _lib_locktmo( W lockno, W tmo, BOOL ignore_mintr )
{
	return MLockTmo(&LibLock, lockno, tmo);
}

EXPORT ER _lib_lock( W lockno, BOOL ignore_mintr )
{
	return MLock(&LibLock, lockno);
}

EXPORT void _lib_unlock( W lockno )
{
	MUnlock(&LibLock, lockno);
}

EXPORT void _delete_liblock( void )
{
	DeleteMLock(&LibLock);
}
