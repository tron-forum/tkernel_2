/*
 *----------------------------------------------------------------------
 *    T-Kernel 2.0 Software Package
 *
 *    Copyright 2011 by Ken Sakamura.
 *    This software is distributed under the latest version of T-License 2.x.
 *----------------------------------------------------------------------
 *
 *    Released by T-Engine Forum(http://www.t-engine.org/) at 2011/05/17.
 *    Modified by T-Engine Forum at 2014/09/10.
 *    Modified by TRON Forum(http://www.tron.org/) at 2015/06/01.
 *
 *----------------------------------------------------------------------
 */

/*
 *	usermain.c (usermain)
 *	User Main for debug with device drivers
 */

#include <basic.h>
#include <tk/tkernel.h>
#include <tm/tmonitor.h>
#include <libstr.h>

/* Device drivers */
IMPORT ER ConsoleIO( INT ac, UB *av[] );
IMPORT ER ClockDrv( INT ac, UB *av[] );
IMPORT ER SysDiskDrv( INT ac, UB *av[] );
IMPORT ER ScreenDrv( INT ac, UB *av[] );
IMPORT ER KbPdDrv( INT ac, UB *av[] );
IMPORT ER LowKbPdDrv( INT ac, UB *av[] );

#ifdef DEBUG_SAMPLE
/*-----------------------------------------------------------------------------
	debug sample
-----------------------------------------------------------------------------*/
/*
 *  debug sample - task
 */
LOCAL void test_tsk( INT stacd, void *exinf )
{
	INT	i;

	tm_printf("3 - Sample task started (tid=%d).\n", tk_get_tid());

	for (i = 0; i < 3; i++) {
		tk_dly_tsk(1000);
		tm_printf("%d - Delay 1000 msec.\n", 4 + i);
	}

	tm_printf("7 - Wakeup main task.\n");

	/* Wake up calling task */
	tk_wup_tsk(stacd);

	tm_printf("9 - Sample task finished.\n");

	/* Exit and delete myself */
	tk_exd_tsk();
}
/*
 *  debug sample - main
 */
LOCAL	void	debug_sample(void)
{
	ER	er;
	ID	ttskid;
	T_CTSK	ctsk;
	T_RTSK	rtsk;

	tm_printf("1 - Debug sample started.\n");

	/* Create task */
	MEMSET(&ctsk, 0, sizeof(ctsk));

	ctsk.tskatr = TA_HLNG | TA_RNG0;/* Task attribute		*/
	ctsk.task = test_tsk;		/* Task startup address		*/
	ctsk.itskpri = 140;		/* Priority at task startup	*/
	ctsk.stksz = 2 * 1024;		/* User stack size (byte)	*/

	ttskid = tk_cre_tsk(&ctsk);
	if ( ttskid < E_OK ) {
		tm_printf("ERROR: tk_cre_tsk [%#x].\n", ttskid);
		goto err_ret;
	}

	/* Start task */
	er = tk_sta_tsk(ttskid, tk_get_tid());
	if ( er < E_OK ) {
		tk_del_tsk(ttskid);
		tm_printf("ERROR: tk_sta_tsk [%#x].\n", er);
		goto err_ret;
	}

	tm_printf("2 - Start sample task (tid=%d) and wait.\n", ttskid);

	/* Wait for wake-up */
	tk_slp_tsk(TMO_FEVR);

	tm_printf("8 - Wakeup from sample task.\n");

	/* Confirm deletion of task */
	while(1) {
		er = tk_ref_tsk(ttskid, &rtsk);
		if ( er == E_NOEXS ) break;
		tk_slp_tsk(50);
	}
	tm_printf("10 - Debug sample finished.\n");

err_ret:
	return;
}
#endif	/* DEBUG_SAMPLE */

/*
 * Entry routine for the user application.
 * At this point, Initialize and start the user application.
 *
 * Entry routine is called from the initial task for Kernel,
 * so system call for stopping the task should not be issued
 * from the contexts of entry routine.
 * We recommend that:
 * (1)'usermain()' only generates the user initial task.
 * (2)initialize and start the user application by the user
 * initial task.
 */
EXPORT	INT	usermain( void )
{
	ER	ercd;

	/* Start the device drivers */
#ifdef DRV_CONSOLE
	ercd = ConsoleIO(0, NULL);
	tm_putstring(ercd >= E_OK ? "ConsoleIO - OK\n" : "ConsoleIO - ERR\n");
#endif
#ifdef DRV_CLOCK
	ercd = ClockDrv(0, NULL);
	tm_putstring(ercd >= E_OK ? "ClockDrv - OK\n" : "ClockDrv - ERR\n");
#endif
#ifdef DRV_SYSDISK
	ercd = SysDiskDrv(0, NULL);
	tm_putstring(ercd >= E_OK ? "SysDiskDrv - OK\n" : "SysDiskDrv - ERR\n");
#endif
#ifdef DRV_SCREEN
	ercd = ScreenDrv(0, NULL);
	tm_putstring(ercd >= E_OK ? "ScreenDrv - OK\n" : "ScreenDrv - ERR\n");
#endif
#ifdef DRV_KBPD
	ercd = KbPdDrv(0, NULL);
	tm_putstring(ercd >= E_OK ? "KbPdDrv - OK\n" : "KbPdDrv - ERR\n");
#endif
#ifdef DRV_LOWKBPD
	ercd = LowKbPdDrv(0, NULL);
	tm_putstring(ercd >= E_OK ? "LowKbPdDrv - OK\n" : "LowKbPdDrv - ERR\n");
#endif

#ifdef DEBUG_SAMPLE
	/* Debug sample */
	debug_sample();
#endif

	/* System shutdown */
	tm_putstring((UB*)"Push any key to shutdown the T-Kernel.\n");
	tm_getchar(-1);

	/* Stop the device drivers */
#ifdef DRV_LOWKBPD
	LowKbPdDrv(-1, NULL);
#endif
#ifdef DRV_KBPD
	KbPdDrv(-1, NULL);
#endif
#ifdef DRV_SCREEN
	ScreenDrv(-1, NULL);
#endif
#ifdef DRV_SYSDISK
	SysDiskDrv(-1, NULL);
#endif
#ifdef DRV_CLOCK
	ClockDrv(-1, NULL);
#endif
#ifdef DRV_CONSOLE
	ConsoleIO(-1, NULL);
#endif

	return 0;
}
