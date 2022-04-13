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
 *	pccard.c	System disk driver
 *
 *	PCMCIA card event processing
 */

#include "sdisk.h"
#include "ata.h"

/*
 *	no PCMCIA support
 */
EXPORT	ER	sdPowerOn(DrvTab *drv, UW req)
		{return E_OK;}

EXPORT	void	sdPowerOff(DrvTab *drv, UW req)
		{return;}

EXPORT	INT	sdCardEvent(INT evttyp, CardReq *req, GDI gdi)
		{return E_NOSPT;}

EXPORT	ER	sdInitCard(DrvTab *drv)
		{return E_NOSPT;}
