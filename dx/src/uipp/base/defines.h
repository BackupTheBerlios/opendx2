/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>

#ifndef _defines_h
#define _defines_h

#include <stdio.h>
#include <stdlib.h>

#if defined(HAVE_SYS_PARAM_H)
#include <sys/param.h>
#endif

#if !defined(MIN)
#define MIN(a,b) ((a)<(b)?(a):(b))
#endif

#if !defined(MAX)
#define MAX(a,b) ((a)>(b)?(a):(b))
#endif

#if defined(__cplusplus) || defined(c_plusplus)
#ifdef DEBUG

#ifdef	DXD_WIN
#include <iostream.h>
#else
#include <stream.h>
#endif

#endif
#endif

#include "UIConfig.h"

#ifdef DXD_NEEDS_TYPES_H
#include <types.h>
#endif

#ifdef DXD_NEEDS_PROCESS_H
#include <process.h>
#endif

#ifdef DXD_WIN
#define getpid  _getpid
#define DELETE DX_DELETE
#endif

/***
 *** Constants:
 ***/

/*
 * This value HAS to match the value found in netlex.c so that ProbeList,
 * ScalarList, VectorList...can determine a limit to the number of list
 * item to allow in their parameter values.  If the limit is not enforced
 * yylex() will not be able to read in the whole value at once and then
 * the ui dumps core.
 */
#define UI_YYLMAX	4096

#ifndef TRUE
#define TRUE			((boolean)1)
#endif

#ifndef FALSE
#define FALSE			((boolean)0)
#endif

#ifndef UNDEFINED
#define UNDEFINED		((boolean)-1)
#endif

#define AND			&&
#define OR			||
#define NOT			!
#define MOD			%


/***
 *** Types:
 ***/
typedef unsigned char boolean;

/*****************************************************************************/
/* NUL -								     */
/*                                                                           */
/* Typecasts a zero (0) value to the specified type.			     */
/*                                                                           */
/*****************************************************************************/

#define	NUL(type)							\
	((type)0)


/*****************************************************************************/
/* ASSERT -								     */
/*                                                                           */
/* Returns if expression is true; otherwise, prints an error message         */
/* and dies.								     */
/*                                                                           */
/*****************************************************************************/

/*
#define ASSERT(expression)						\
(NOT (expression) ? 							\
	  (fprintf(stderr,						\
	     "Internal error detected at \"%s\":%d.\n",			\
	  __FILE__, __LINE__),						\
	  abort(), (int)FALSE) :					\
	  (int)TRUE)
*/
/*
 * Find this in Application.C
 */

#if defined(__cplusplus) || defined(c_plusplus)
extern "C"
#endif
void AssertionFailure(const char *file, int line);

#define ASSERT(expression)						\
do {									\
    if (NOT (expression))  						\
	  AssertionFailure(__FILE__,__LINE__); 				\
} while (0)

/*
 * Generic malloc routines which always return and take void*.
 */
#define MALLOC(n)    ((void*)malloc(n))
#define CALLOC(n,s)  ((void*)calloc((n),(s)))
#define FREE(p)      (free((MALLOC_RETURNS)(p)))
#define REALLOC(p,n) ((p)? (void*)realloc((MALLOC_RETURNS)(p), (n)): 	\
			   (void*)malloc(n))

#ifdef DXD_WIN

#ifndef MAXHOSTNAMELEN
#define MAXHOSTNAMELEN	128
#endif

#ifndef MAXPATHLEN
#define MAXPATHLEN	128
#endif

#endif

#endif /* _defines_h */
