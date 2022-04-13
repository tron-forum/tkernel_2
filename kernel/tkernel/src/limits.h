/*
 *----------------------------------------------------------------------
 *    T-Kernel 2.0 Software Package
 *
 *    Copyright 2011 by Ken Sakamura.
 *    This software is distributed under the latest version of T-License 2.x.
 *----------------------------------------------------------------------
 *
 *    Released by T-Engine Forum(http://www.t-engine.org/) at 2011/05/17.
 *    Modified by T-Engine Forum at 2013/01/18.
 *    Modified by TRON Forum(http://www.tron.org/) at 2015/06/01.
 *
 *----------------------------------------------------------------------
 */

/*
 *	limits.h
 *
 *	C language: integer size
 */

#ifndef _LIMITS_
#define _LIMITS_

#define CHAR_BIT	(8)
#define SCHAR_MIN	(-128)
#define SCHAR_MAX	(+127)
#define UCHAR_MAX	(255)
#define CHAR_MIN	SCHAR_MIN
#define CHAR_MAX	SCHAR_MAX
#define MB_LEN_MAX	(2)

#define SHRT_MIN	(-32767)		/* 0x8001 */
#define SHRT_MAX	(+32767)
#define USHRT_MAX	(65535)

#define LONG_MIN	(-2147483647L)		/* 0x80000001 */
#define LONG_MAX	(+2147483647L)
#define ULONG_MAX	(4294967295UL)

#define INT_MIN		LONG_MIN
#define INT_MAX		LONG_MAX
#define UINT_MAX	ULONG_MAX

#endif /* _LIMITS_ */
