/*****************************************************************************/
/*                            DX  SOURCEFILE                                 */
/*****************************************************************************/

/*****************************************************************************/
/* Main.C -								     */
/* main program								     */
/*****************************************************************************/

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/tutor/Main.C,v 1.1 1999/03/24 15:17:34 gda Exp $
 */

#include "defines.h"
#include "TutorApplication.h"
#ifdef DXD_WINSOCK_SOCKETS          //SMH must initialize Win Sockets
#define _WINSPOOL_      //SMH prevent name clash from uneeded included inlcudes
#include <winsock.h>
#endif
#ifdef DXD_IBM_OS2_SOCKETS
#include <sys/socket.h>
#endif

#ifdef	DXD_WIN

#include <stdio.h>
#include <Xm/Xm.h>          /* Motif Toolkit */
#include <Mrm/MrmPubli.h>    /* Mrm */
#ifdef _X86_
#include <stdlib.h>        /* HCL - exit prototype               */
#include <X11/XlibXtra.h>          /* HCL - HCLXmInit prototype          */
#endif

#endif


//
// Used by the assert macro.
//
const char *AssertMsgString = "Internal error detected at \"%s\":%d.\n";
 
void main(unsigned int argc,
	  char**       argv)
{
#ifdef	DXD_WIN
#ifdef _X86_
    HCLXmInit();
#endif
#endif

#ifdef DXD_WINSOCK_SOCKETS    //SMH initialize Win Sockets
    {
        WSADATA *wsadata = new WSADATA;
        WSAStartup(0x0100,wsadata);
        delete wsadata;
    }
#endif
#ifdef DXD_IBM_OS2_SOCKETS
    sock_init();
#endif
    //
    // Initialize Xt Intrinsics, build all the windows, and enter event loop.
    // Note that all the windows are created elsewhere (<Application>App.C),
    // and managed in the application initialization routine.
    //
    if (NOT theApplication)
    {
	theApplication = new TutorApplication("DXTutor");
    }

    if (!theApplication->initialize(&argc, argv))
	exit(1);

    theApplication->handleEvents();

    delete theApplication;

#ifdef DXD_WINSOCK_SOCKETS    //SMH cleanup Win Sockets
    WSACleanup();
#endif

    exit(0);
}
