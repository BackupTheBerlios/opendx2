/*  Open Visualization Data Explorer Source File */



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
    application->shutdownApplication();

    return TRUE;
}


