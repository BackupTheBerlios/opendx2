/*  Open Visualization Data Explorer Source File */

#include <dxconfig.h>




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


