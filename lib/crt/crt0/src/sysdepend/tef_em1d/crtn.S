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
 *	crtn.S
 *
 *	C startup
 */

.macro FUNC_END
	.arm
	ldmdb	fp, {r4-r9, sl, fp, ip, lr}
	mov	sp, ip
	bx	lr
.endm

	.section	.init
	FUNC_END

	.section	.fini
	FUNC_END
