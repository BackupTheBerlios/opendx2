/*  Open Visualization Data Explorer Source File */

#include <dxconfig.h>




#include "defines.h"
#include "NoUndoGARAppCommand.h"
#include "GARApplication.h"


NoUndoGARAppCommand::NoUndoGARAppCommand(const char*   name,
				       CommandScope* scope,
				       boolean       active,
				       GARApplication *app,
				       GARAppCommandType comType ) :
	NoUndoCommand(name, scope, active)
{
	this->commandType = comType;
	this->application = app;
}


boolean NoUndoGARAppCommand::doIt(CommandInterface *)
{
    GARApplication *app = this->application;
    boolean ret;

    ASSERT(app);

    ret = TRUE;
    switch (this->commandType) {

    case NoUndoGARAppCommand::HelpOnManual:
	theGARApplication->helpOn("OnManual");
	ret = TRUE;
	break;

    case NoUndoGARAppCommand::HelpOnHelp:
	theGARApplication->helpOn("OnHelp");
	ret = TRUE;
	break;

    default:
	ASSERT(0);
    }

    return ret;
}
