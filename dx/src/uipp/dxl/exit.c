/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>


#include <stdio.h>
#include <ctype.h>
#include <sys/types.h>
#if  !defined(OS2) && !defined(DXD_WIN)
#include <sys/param.h>
#endif
#ifdef DXD_HAS_WINSOCKETS
#include <winsock.h>
#else
#include <sys/socket.h>
#endif
#ifdef DXD_WIN
#include <sys/timeb.h>
#else
#include <sys/time.h>
#endif
#ifndef DXD_HAS_WINSOCKETS
#include <netdb.h>
#endif
#include <errno.h>
#include <malloc.h>
#if defined(ibm6000) || defined(pgcc) || defined(__METAWARE_HC) || defined(OS2)
#include <sys/select.h>
#endif

#include "../base/UIConfig.h"
#include "../base/defines.h"
#include "dxlP.h"

DXLError
uiDXLDisconnect(DXLConnection *conn)
{
    int sts;

    sts = DXLSend(conn, "disconnect");
    DXLCloseConnection(conn);

    return sts;
}
DXLError
DXLExitDX(DXLConnection *conn)
{
    int retval;  
    int sts;
    fd_set fds;
#ifdef hp700
    int width = MAXFUPLIM;
#else
#ifdef aviion
    int width = NOFILE;
#else
#ifdef solaris
    int width = FD_SETSIZE;
#else
#ifdef  DXD_HAS_WINSOCKETS
    int width = FD_SETSIZE;
#else
#ifndef OS2
    int width = getdtablesize();
#endif
#endif
#endif
#endif
#endif
    struct timeval to;
    const char *cmd;

    if (conn->fd <= 0 )
	return ERROR;

    if (conn->dxuiConnected)
	cmd = "exit";
    else
	cmd = "quit;\n";

    /*
    // Don't need to syncrhonize after sending the quit/exit commands
    */
    DXLSetSynchronization(conn,0);

    sts = DXLSend(conn, cmd);

    FD_ZERO(&fds);
    FD_SET(conn->fd, &fds);
    to.tv_sec = 0;
    to.tv_usec = 0;
#ifdef DXD_HAS_WINSOCKETS
    select(width, &fds, NULL, NULL, NULL);
#else
#ifndef OS2
    /* this will set retval even though we don't need it here */
    SELECT_INTR(width, (SELECT_ARG_TYPE)&fds, NULL, NULL, NULL, retval);
#else
    select(&conn->fd, 1, 0, 0, -1);
#endif
#endif

    DXLCloseConnection(conn);

    return sts;
}

