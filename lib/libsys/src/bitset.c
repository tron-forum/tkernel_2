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
 *	bitset.c (libsys)
 */

#include <sys/bitop.h>

EXPORT void BitSet( void *base, UW offset )
{
#if BIGENDIAN
	((UB*)base)[offset >> 3] |= ((UB)0x80U  >>  (offset & 0x00000007U));
#else
	((UB*)base)[offset >> 3] |= ((UB)0x01U  <<  (offset & 0x00000007U));
#endif
}
