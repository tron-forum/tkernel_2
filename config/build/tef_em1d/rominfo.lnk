/*
 *----------------------------------------------------------------------
 *    T-Kernel 2.0 Software Package
 *
 *    Copyright 2011 by Ken Sakamura.
 *    This software is distributed under the latest version of T-License 2.x.
 *----------------------------------------------------------------------
 *
 *    Released by T-Engine Forum(http://www.t-engine.org/) at 2011/05/17.
 *    Modified by T-Engine Forum at 2013/03/02.
 *    Modified by TRON Forum(http://www.tron.org/) at 2015/06/01.
 *
 *----------------------------------------------------------------------
 */

/*
 *	rominfo.lnk (config, EM1D-512)
 *	ROM information linker script
 */

OUTPUT_FORMAT("elf32-larm-tkernel", "elf32-barm-tkernel", "elf32-larm-tkernel")
OUTPUT_ARCH(arm)

PHDRS {
	data	PT_LOAD;
}

SECTIONS {
	/* start address of data section = ROMInfo */
	.data 0x70020000 : {
		*(.data)
		*(.text)
	} :data
}
