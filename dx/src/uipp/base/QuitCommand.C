//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
// QuitCommand.C -							    //
//                                                                          //
// QuitCommand Class methods and other related functions/procedures.	    //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/base/QuitCommand.C,v 1.1 1999/03/24 15:17:24 gda Exp $
 */


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


