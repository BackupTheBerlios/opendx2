/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#ifndef _CCM_H
#define _CCM_H

#include <dxconfig.h>

int _dxfSetupServer(int pport, int *psock,
            struct sockaddr_in *pserver
#if DXD_SOCKET_UNIXDOMAIN_OK
            , int *pusock,
            struct sockaddr_un *puserver
#endif
);

int
_dxfCompleteServer(int sock,
    struct sockaddr_in server
#if DXD_SOCKET_UNIXDOMAIN_OK
    , int usock,
    struct sockaddr_un userver
#endif
    , int timeout
);

void _dxfPrintConnectTimeOut(char *execname, char *hostname);

#endif /* _CCM_H */
