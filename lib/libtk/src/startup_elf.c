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
 *	@(#)startup_elf.c (libtk)
 *
 *	Compiler dependent startup sequence (for ELF)
 */

#include <basic.h>

EXPORT void _init_compiler( void )
{
IMPORT	void	_init( void );
	_init();
}

EXPORT void _fini_compiler( void )
{
IMPORT	void	_fini( void );
	_fini();
}
