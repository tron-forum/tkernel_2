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
 *	Extended SVC parameter packet
 *
 *	   (generated automatically)
 */

#include <basic.h>
#include <device/em1d512_iic.h>
#include <sys/str_align.h>
#include "fnem1d512.h"

typedef struct {
	W ch;	_align64
	UH *cmddat;	_align64
	W words;	_align64
} H8IO_EM1D512_IICXFER_PARA;

typedef struct {
	W cs;	_align64
	UB *xmit;	_align64
	UB *recv;	_align64
	W len;	_align64
} H8IO_EM1D512_SPIXFER_PARA;

