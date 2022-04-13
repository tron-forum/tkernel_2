/*
 *----------------------------------------------------------------------
 *    T-Kernel 2.0 Software Package
 *
 *    Copyright 2011 by Ken Sakamura.
 *    This software is distributed under the latest version of T-License 2.x.
 *----------------------------------------------------------------------
 *
 *    Released by T-Engine Forum(http://www.t-engine.org/) at 2011/05/17.
 *    Modified by T-Engine Forum at 2014/09/10.
 *    Modified by TRON Forum(http://www.tron.org/) at 2015/06/01.
 *
 *----------------------------------------------------------------------
 */

/*
 *	bitsset.c (libsys)
 */

#include <sys/bitop.h>
#include <libstr.h>

/*
 * Set the bit string.
 *	Set the width bits from the position of specified bit.
 */
EXPORT void BitsSet( void *base, W offset, W width )
{
	UB	*bp;
	INT	n;

	n = offset / 8;
	bp = (UB*)base + n;

	n = (W)((UW)offset & 7U);
	if ( n > 0 ) {
		for ( ; n < 8; ++n ) {
			if ( --width < 0 ) {
				return;
			}
			BitSet(bp, (UW)n);
		}
		bp++;
	}

	n = width / 8;
	if ( n > 0 ) {
		MEMSET(bp, 0xffU, (size_t)n);
	}
	bp += n;
	width -= n * 8;

	for ( n = 0; n < width; ++n ) {
		BitSet(bp, (UW)n);
	}
}
