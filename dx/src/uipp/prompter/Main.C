/*****************************************************************************/
/*                            DX  SOURCEFILE                                 */
/*****************************************************************************/

/*****************************************************************************/
/* Main.C -								     */
/* main program								     */
/*****************************************************************************/

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/prompter/Main.C,v 1.1 1999/04/05 13:33:38 gda Exp $
 */

#include "../base/defines.h"
#include "GARApplication.h"
#ifdef	DXD_WIN

#include <stdio.h>
#include <Xm/Xm.h>          /* Motif Toolkit */
#include <Mrm/MrmPubli.h>    /* Mrm */
#ifdef _X86_
#include <stdlib.h>        /* HCL - exit prototype               */
#include <X11/XlibXtra.h>          /* HCL - HCLXmInit prototype          */
#endif

#endif

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
	theApplication = new GARApplication("GAR");
    }

    theApplication->initialize(&argc, argv);
    theApplication->handleEvents();

    delete theApplication;
}
