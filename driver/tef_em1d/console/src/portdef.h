/*
 *----------------------------------------------------------------------
 *    T-Kernel 2.0 Software Package
 *
 *    Copyright 2011 by Ken Sakamura.
 *    This software is distributed under the latest version of T-License 2.x.
 *----------------------------------------------------------------------
 *
 *    Released by T-Engine Forum(http://www.t-engine.org/) at 2011/05/17.
 *    Modified by T-Engine Forum at 2013/03/01.
 *    Modified by TRON Forum(http://www.tron.org/) at 2015/06/01.
 *
 *----------------------------------------------------------------------
 */

/*
 *	portdef.h	Console/Low-level serial I/O driver
 *
 *	Serial line low-level driver system-dependent port definition(EM1-D512)
 */

/* Port definition */
IMPORT	SC_FUNC	ScFuncNS16450;

#define	N_PORTS		1

LOCAL  SC_DEFS	PortDefs[N_PORTS] = {
	/* Port #0: UART0 */
	{
		&ScFuncNS16450,
		{	0x50000000,	/* I/O base address */
			4,		/* iostep */
			IV_IRQ(9)	/* Interrupt Vector */
		},
		0,			/* fctl register value */
		{0, 0, 0},		/* dt[3]: Not used */
		{0, 3, 0, 0, 38400},	/* default mode */
		{0, 0, 1, 1, 0, 0, 0},	/* default flow control */
		{0, 0, 0},		/* default flow status */
	}
};

#define	INIT_AUXPORT(sup)	/* Nothing */
#define	START_AUXPORT(sup)	/* Nothing */
