/*  Open Visualization Data Explorer Source File */

#include <dxconfig.h>




#include "QuitCommand.h"
#include "Application.h"


QuitCommand::QuitCommand(Application*  app,
			 const char*   name,
			 CommandScope* scope,
			 boolean       active,
			 char*         dialogTitle,
			 char*         dialogQuestion) :
	ConfirmedCommand(name, scope, active, dialogTitle, dialogQuestion)
{
    //
    // No op.
    //
    this->application = app;
}


boolean QuitCommand::doIt(CommandInterface *ci)
{
    //
    // Terminate the application
    //
    exit(0);

    return TRUE;
}


