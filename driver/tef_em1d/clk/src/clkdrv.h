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
 *	clkdrv.h	Clock driver : common definition
 */

#define	DEBUG_MODULE	"(clkdrv)"

#include <tk/tkernel.h>
#include <device/sdrvif.h>
#include <device/clk.h>
#include <sys/debug.h>

#define	InvalidID	(0)		/* Invalid ID */
#define	InvalidDevID	(-1)		/* Invalid device ID */

/*
 *	Clock driver entry
 */
IMPORT	ER	ClockDrv(INT ac, UB *av[]);

/*
 *	System types (hardware-dependent) routine
 */

/*
 *	Hardware initialization configuration
 */
IMPORT	ER	cdInitHardware(void);
IMPORT	ER	cdFinishHardware(void);

/*
 *	Set/Get the current time
 */
IMPORT	ER	cdSetDateTime(void *date_tim);
IMPORT	ER	cdGetDateTime(void *date_tim);

/*
 *	Set/Get the automatic power-supply ON time
 */
IMPORT	ER	cdSetAutoPwOn(void *date_tim);
IMPORT	ER	cdGetAutoPwOn(void *date_tim);

/*
 *	Access of nonvolatile register
 */
IMPORT	INT	cdSetRegister(void *buf, INT size);
IMPORT	INT	cdGetRegister(void *buf, INT size);
