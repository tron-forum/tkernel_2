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
 *	wrkbuf.c
 *
 *       work buffer
 *
 *       this is in an independent separate file so that we can specify the layout at link-time.
 *       this is also used to store FlashROM writing program.
 *
 */

#include "cmdsvc.h"

EXPORT	UB	wrkBuf[WRKBUF_SZ];
