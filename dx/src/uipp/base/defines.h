/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/
#include <dxconfig.h>

#ifndef _DEFINES_H_
#define _DEFINES_H_

#include <stdio.h>
#include <stdlib.h>

#include <dx/arch.h>

#if defined(HAVE_WINDOWS_H) && defined(intelnt)
#include <windows.h>
#include <winsock.h>
#define S_IXUSR S_IEXEC
#define S_IXGRP S_IEXEC
#define S_IXOTH S_IEXEC
#define EADDRINUSE      WSAEADDRINUSE
#define USING_WINSOCKS
#endif

#if defined(HAVE_CYGWIN_SOCKET_H)
#include <cygwin/socket.h>
#elif defined(HAVE_SYS_SOCKET_H)
#include <sys/socket.h>
#elif defined(HAVE_SOCKET_H)
#include <socket.h>
#endif

#if defined(HAVE_SYS_PARAM_H)
#include <sys/param.h>
#endif

#if !defined(MIN)
#define MIN(a,b) ((a)<(b)?(a):(b))
#endif

#if !defined(MAX)
#define MAX(a,b) ((a)>(b)?(a):(b))
#endif

#if defined(HAVE_IOSTREAM_H)
#include <iostream.h>
#endif

#if defined(HAVE_STREAM_H)
#include <stream.h>
#endif

#ifdef intelnt
#define DXD_NON_UNIX_SOCKETS
#endif

#if !defined(HAVE_GETLOGIN)
#define GETLOGIN NULL
#else
#define GETLOGIN getlogin()
#endif

#if defined(HAVE_TYPES_H)
#include <types.h>
#endif

#if defined(HAVE_PROCESS_H)
#include <process.h>
#endif

#if defined(HAVE_STRINGS_H)
#include <strings.h>
#endif

#if !defined(HAVE_GETPID)
#if defined(HAVE__GETPID)
#define getpid  _getpid
#else
Got to have SOME getpid available
#endif
#endif

#if !defined(HAVE_UNLINK)
#if defined(HAVE__UNLINK)
#define unlink  _unlink
#else
Got to have SOME unlink available
#endif
#endif

#if !defined(HAVE_POPEN)
#if defined(HAVE__POPEN)
#define popen  _popen
#else
Got to have SOME popen available
#endif
#endif

#if !defined(HAVE_ISATTY)
#if defined(HAVE__ISATTY)
#define isatty  _isatty
#else
Got to have SOME isatty available
#endif
#endif

#if !defined(HAVE_PCLOSE)
#if defined(HAVE__PCLOSE)
#define pclose  _pclose
#else
Got to have SOME popen available
#endif
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

/*
// What type does malloc return
*/
#ifdef sun4
# define MALLOC_RETURNS malloc_t
#else
# define MALLOC_RETURNS void*
#endif

#define MALLOC(n)    ((void*)malloc(n))
#define CALLOC(n,s)  ((void*)calloc((n),(s)))
#define FREE(p)      (free((MALLOC_RETURNS)(p)))
#define REALLOC(p,n) ((p)? (void*)realloc((MALLOC_RETURNS)(p), (n)): 	\
			   (void*)malloc(n))

#ifndef MAXHOSTNAMELEN
#define MAXHOSTNAMELEN	128
#endif

#ifndef MAXPATHLEN
#define MAXPATHLEN	128
#endif

#define WORKSPACE_PAGES 1

#if defined(HAVE_LIBXMSTATIC)
#define XMSTATIC
#endif

#endif
