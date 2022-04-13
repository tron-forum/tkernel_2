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
 *	bitsearch1.c (libsys)
 */

#include <machine.h>
#include <sys/bitop.h>

/*
 * Retrieve bit 1 in word-aligned array.
 *	A faster version of BitSearch1 available in case where base is word-aligned.
 *	This implementation uses binary search algorithm for efficiency.
 */
EXPORT W BitSearch1_w( const UW *base, W offset, W width )
{
	UW	*cp, v;
	W	position;

	cp = (UW*)base;
	cp += offset / 32;
	if ( offset & 31 ) {
#if BIGENDIAN
		v = *cp & (((UW)1U << (32 - (offset & 31))) - 1);
#else
		v = *cp & ~(((UW)1U << (offset & 31)) - 1);
#endif
	} else {
		v = *cp;
	}

	position = 0;
	while ( position < width ) {
		if ( v ) {            /* includes 1 --> search bit of 1 */
			if ( !position ) position -= (offset & 31);
#if BIGENDIAN
			if ( !(v & 0xffff0000U) ) {
				v <<= 16;
				position += 16;
			}
			if ( !(v & 0xff000000U) ) {
				v <<= 8;
				position += 8;
			}
			if ( !(v & 0xf0000000U) ) {
				v <<= 4;
				position += 4;
			}
			if ( !(v & 0xc0000000U) ) {
				v <<= 2;
				position += 2;
			}
			if ( !(v & 0x80000000U) ) {
				++position;
			}
#else
			if ( !(v & 0xffffU) ) {
				v >>= 16;
				position += 16;
			}
			if ( !(v & 0xffU) ) {
				v >>= 8;
				position += 8;
			}
			if ( !(v & 0xfU) ) {
				v >>= 4;
				position += 4;
			}
			if ( !(v & 0x3U) ) {
				v >>= 2;
				position += 2;
			}
			if ( !(v & 0x1U) ) {
				++position;
			}
#endif
			if ( position < width ) {
				return position;
			} else {
				return -1;
			}
		} else {              /* all bits are 0 --> 1 Word skip */
			if ( position ) {
				position += 32;
			} else {
				position = 32 - (offset & 31);
			}
			v = *++cp;
		}
	}

	return -1;
}

/*
 * Retrieve bit 1.
 *	Retrieve the width bits from the position of specified bit and return the position.
 *	If not found, return -1.
 *	The found position is returned in relative position from the retrieval start position.
 *	When found, the return value is between 0 and width-1.
 */
EXPORT W BitSearch1( const void *base, W offset, W width )
{
#if ALLOW_MISALIGN
	return BitSearch1_w((const UW*)base, offset, width);
#else
	/* Align base to the left word boundary, then use BitSearch1_w */
	UINT	wofs = ((UINT)base) & 3;
	return BitSearch1_w((const UW*)((const UB*)base - wofs), offset + wofs * 8, width);
#endif
}
