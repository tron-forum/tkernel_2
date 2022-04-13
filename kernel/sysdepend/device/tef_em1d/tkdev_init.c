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
 *	tkdev_init.c (EM1-D512)
 *	T-Kernel Device-Dependent Initialization/Finalization
 */

#include "kernel.h"
#include <tk/sysdef.h>
#include <tk/syslib.h>
#include <tm/tmonitor.h>
#include "tkdev_conf.h"

/*
 * Target system-dependent initialization
 */
EXPORT ER tkdev_initialize( void )
{
static	UINT	giob[4] = { _L, _H, _HH, _HHH };
	UINT	gb;
	INT	i;

	/* initialize GPIO interrupt */
	for ( i = 0; i < 4; ++i ) {
		gb = giob[i];
		out_w(GIO_IDS(gb), 0xffffffff); /* disable interrupt */
		out_w(GIO_IIA(gb), 0x00000000); /* disassert interrupt pin */
		out_w(GIO_GSW(gb), 0x00000000); /* disassert FIQ pin */
	}

	/* initialize interrupt controller (AINT) */
	out_w(IT0_IDSS0,    0xffffffff);	/* disassert interrupt pin  */
	out_w(IT0_IDSS1,    0xffffffff);
	out_w(IT0_IDSS2,    0xffffffff);
	out_w(IT0_IDS0,	    0xffffffff);	/* disable interrupt */
	out_w(IT0_IDS1,	    0xffffffff);
	out_w(IT0_IDS2,	    0xffffffff);
	out_w(IT_PINV_CLR0, 0xffffffff);	/* reset inverted logic */
	out_w(IT_PINV_CLR1, 0xffffffff);
	out_w(IT_PINV_CLR2, 0xffffffff);
	out_w(IT_LIIR,	    0xffffffff);	/* clear interrupt */
	out_w(IT0_IIR,	    0xffffffff);
	out_w(IT0_FIE,	    0x00000001);	/* enable FIQ */

	/* enable GPIO interrupt on AINT */
	out_w(IT0_IENS0, IRQM(26)|IRQM(27));	/* assert interrupt pin */
	out_w(IT0_IENS1, IRQM(50)|IRQM(51)|IRQM(52)|IRQM(53));
	out_w(IT0_IENS2, IRQM(79)|IRQM(80));
	out_w(IT0_IEN0,	 IRQM(26)|IRQM(27));	/* enable interrupt */
	out_w(IT0_IEN1,	 IRQM(50)|IRQM(51)|IRQM(52)|IRQM(53));
	out_w(IT0_IEN2,	 IRQM(79)|IRQM(80));

	/* enable abort switch(SW1) */
	SetIntMode(IV_GPIO(8), IM_ENA|IM_LEVEL|IM_HI);
	EnableInt(IV_GPIO(8));

	return E_OK;
}

/*
 * Target system-dependent finalization
 *	Normally jump to ROM monitor.
 *	No return from this function.
 */
EXPORT void tkdev_exit( void )
{
	disint();
	tm_exit(0);	/* Turn off power and exit */

	/* Not suppose to return from 'tm_exit,' but just in case */
	for ( ;; ) {
		tm_monitor();  /* To T-Monitor */
	}
}
