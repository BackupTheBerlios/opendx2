//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
// NoUndoTutorAppCommand.C 						    //
//                                                                          //
// NoUndoTutorAppCommand Class methods and other related functions.        //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/tutor/NoUndoTutorAppCommand.C,v 1.1 1999/03/24 15:17:34 gda Exp $
 */


#include "defines.h"
#include "NoUndoTutorAppCommand.h"
#include "TutorApplication.h"
#include "TutorWindow.h"
#include "CommandInterface.h"

NoUndoTutorAppCommand::NoUndoTutorAppCommand(const char*   name,
				       CommandScope* scope,
				       boolean       active,
				       TutorApplication *app,
				       TutorAppCommandType comType ) :
	NoUndoCommand(name, scope, active)
{
	this->commandType = comType;
	this->application = app;
}


boolean NoUndoTutorAppCommand::doIt(CommandInterface *ci)
{
    TutorApplication *app = this->application;
    boolean ret;

    ASSERT(app);

    ret = TRUE;
    switch (this->commandType) {

    case NoUndoTutorAppCommand::Quit:
	exit(0);
	break;

#if 0
    case NoUndoTutorAppCommand::GotoHelpText:
	if (ci) {
	    app->setBusyCursor(TRUE);
	    const char *file = (const char*)ci->getLocalData();
	    app->mainWindow->loadTutorText(file);
	    app->setBusyCursor(FALSE);
	}
	break;
#endif

    default:
	ASSERT(0);
    }

    return ret;
}

