/*  Open Visualization Data Explorer Source File */




#include "defines.h"
#include "HelpMenuCommand.h"
#include "IBMApplication.h"
#include "CommandInterface.h"
#include "InfoDialogManager.h"


HelpMenuCommand::HelpMenuCommand(const char*   name,
				       CommandScope* scope,
				       boolean       active,
				       HelpMenuCommandType comType ) :
	NoUndoCommand(name, scope, active)
{
	this->commandType = comType;
}


boolean HelpMenuCommand::doIt(CommandInterface *ci)
{
    boolean ret = FALSE;

    switch (this->commandType) {

    case HelpMenuCommand::GenericHelp:
	ASSERT(ci);
	//
	// This is a bit bogus, in that the following normally implies
	// asking help on the option itself, but we use the option name
	// to drive help on specific topics as defined by the name of
	// the CommandInterface referencing this command. 
	//
	ci->componentHelp();
	ret = TRUE;
	break;

    case HelpMenuCommand::HelpTutorial:
	
	InfoMessage("Starting the tutorial...");
	ret = theApplication->startTutorial();

	break;

    case HelpMenuCommand::AboutApp:
	
	InfoMessage(theIBMApplication->getAboutAppString());
	ret = TRUE;

	break;

    case HelpMenuCommand::TechSupport:
	
	InfoMessage(theIBMApplication->getTechSupportString());
	ret = TRUE;

	break;

    default:
	ASSERT(0);
    }

    return ret;
}

