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
 *	T-Kernel driver SVC interface library
 *
 *	   (generated automatically)
 */

#include <machine.h>
#include <tk/sysdef.h>
#include "fnem1d512.h"

	.text
	.balign	4
	.globl	Csym(em1d512_spixfer)
	.type	Csym(em1d512_spixfer), %function
Csym(em1d512_spixfer):
	stmfd	sp!, {r0-r3}
	mov	r0, sp
	stmfd	sp!, {lr}
	ldr	ip, =H8IO_EM1D512_SPIXFER_FN
	swi	SWI_SVC
	ldmfd	sp!, {lr}
	add	sp, sp, #4*4
	bx	lr

