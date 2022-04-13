/*
 *----------------------------------------------------------------------
 *    T-Kernel 2.0 Software Package
 *
 *    Copyright 2011 by Ken Sakamura.
 *    This software is distributed under the latest version of T-License 2.x.
 *----------------------------------------------------------------------
 *
 *    Released by T-Engine Forum(http://www.t-engine.org/) at 2011/05/17.
 *    Modified by T-Engine Forum at 2013/02/12.
 *    Modified by TRON Forum(http://www.tron.org/) at 2015/06/01.
 *
 *----------------------------------------------------------------------
 */

/*
 *	bittest.c (libsys)
 */

#include <sys/bitop.h>

EXPORT BOOL BitTest( const void *base, UW offset )
{
#if BIGENDIAN
	return (BOOL)((((const UB*)base)[offset >> 3] >> (UW)(7U - (offset & 7U))) & 1U);
#else
	return (BOOL)((((const UB*)base)[offset >> 3] >> (UW)(offset & 7U)) & 1U);
#endif
}
