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
#include <sys/consio.h>
#include <sys/str_align.h>
#include <sys/svc/fnconsio.h>

typedef struct {
	W port;	_align64
	B *buf;	_align64
	UW len;	_align64
	W tmout;	_align64
} CONSIO_CONSOLE_GET_PARA;

typedef struct {
	W port;	_align64
	B *buf;	_align64
	UW len;	_align64
	W tmout;	_align64
} CONSIO_CONSOLE_PUT_PARA;

typedef struct {
	W req;	_align64
	UW *arg;	_align64
} CONSIO_CONSOLE_CONF_PARA;

typedef struct {
	W port;	_align64
	B *buf;	_align64
	UW len;	_align64
} CONSIO_CONSOLE_IN_PARA;

typedef struct {
	W port;	_align64
	B *buf;	_align64
	UW len;	_align64
} CONSIO_CONSOLE_OUT_PARA;

typedef struct {
	W port;	_align64
	W req;	_align64
	W arg;	_align64
} CONSIO_CONSOLE_CTL_PARA;

