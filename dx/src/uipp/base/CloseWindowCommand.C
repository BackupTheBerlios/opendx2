//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/base/CloseWindowCommand.C,v 1.1 1999/03/24 15:17:22 gda Exp $
 */


#include "MainWindow.h"
#include "CloseWindowCommand.h"


CloseWindowCommand::CloseWindowCommand(const char*   name,
				       CommandScope* scope,
				       boolean       active,
				       MainWindow*   window):
	NoUndoCommand(name, scope, active)
{
    ASSERT(window);

    //
    // Save the associated window.
    //
    this->window = window;
}


boolean CloseWindowCommand::doIt(CommandInterface *ci)
{
    this->window->closeWindow();

    return TRUE;
}


