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
 *	quesearch.c (libsys)
 */

#include "quetemplate.h"

/*EXPORT QUESEARCH(, W, ==)*/
QUEUE* QueSearch( QUEUE *start, QUEUE *end, W val, W offset )
{
	QUEUE	*que;
	for ( que = start->next; que != end; que = que->next ) {
		if ( *(W*)((VB*)que + offset) == val ) {
			break;
		}
	}
	return que;
}
