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
 *	quetemplate.c (libsys)
 */

#include <sys/queue.h>

#define	QUESEARCH(NAME, TYPE, COND)					\
QUEUE* QueSearch##NAME( QUEUE *start, QUEUE *end, TYPE val, W offset )	\
{									\
	QUEUE	*que;							\
	for ( que = start->next; que != end; que = que->next ) {	\
		if ( *(TYPE*)((VB*)que + offset) COND val ) {	\
			break;	\
		}	\
	}								\
	return que;							\
}

#define	QUESEARCHREV(NAME, TYPE, COND)					\
QUEUE* QueSearchRev##NAME( QUEUE *start, QUEUE *end, TYPE val, W offset )\
{									\
	QUEUE	*que;							\
	for ( que = start->prev; que != end; que = que->prev ) {	\
		if ( *(TYPE*)((VB*)que + offset) COND val ) {	\
			break;	\
		}	\
	}								\
	return que;							\
}
