/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>



#include "defines.h"
#include "MBApplication.h"

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

int main(unsigned int argc,
	  char**       argv)
{
#ifdef	DXD_WIN
#ifdef _X86_
    HCLXmInit();
#endif
#endif
    //
    // Initialize Xt Intrinsics, build all the windows, and enter event loop.
    // Note that all the windows are created elsewhere (<Application>App.C),
    // and managed in the application initialization routine.
    //
    if (NOT theApplication)
    {
	theApplication = new MBApplication("MB");
    }

    theApplication->initialize(&argc, argv);
    theApplication->handleEvents();

    delete theApplication;

    return 0;
}
