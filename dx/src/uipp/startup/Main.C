/*****************************************************************************/
/*                            DX  SOURCEFILE                                 */
/*****************************************************************************/

/*****************************************************************************/
/* Main.C -								     */
/* main program								     */
/*****************************************************************************/

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/startup/Main.C,v 1.1 1999/03/24 15:17:34 gda Exp $
 */

#include "../base/UIConfig.h"

#ifdef	DXD_WIN

#include <stdio.h>
#include <Xm/Xm.h>          /* Motif Toolkit */
#include <Mrm/MrmPubli.h>    /* Mrm */
#ifdef _X86_
#include <stdlib.h>        /* HCL - exit prototype               */
#include <X11/XlibXtra.h>          /* HCL - HCLXmInit prototype          */
#endif

#endif

#include "../base/defines.h"
#include "StartupApplication.h"

void main(unsigned int argc,
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
	theApplication = new StartupApplication("Startup");
    }

    theApplication->initialize(&argc, argv);
    theApplication->handleEvents();

    delete theApplication;
}
