//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/base/ConfirmedCommand.C,v 1.1 1999/03/24 15:17:22 gda Exp $
 */


#include "UIConfig.h"

#include <Xm/MainW.h>

#include "defines.h"
#include "Application.h"
#include "ConfirmedCommand.h"
#include "QuestionDialogManager.h"
#include "CommandInterface.h"


void ConfirmedCommand::OkDCB(void* clientData)
{
    ConfirmedCommand* command;

    ASSERT(clientData);

    //
    // Call the superclass execute() function to do all the
    // normal command processing....
    //
    command = (ConfirmedCommand*)clientData;
    command->NoUndoCommand::execute(NULL);
}


ConfirmedCommand::ConfirmedCommand(const char*   name,
				   CommandScope* scope,
				   boolean       active,
				   char*         dialogTitle,
				   char*         dialogQuestion,
				   Widget	 parent):
	NoUndoCommand(name, scope, active)
{
    ASSERT(dialogTitle);
    ASSERT(dialogQuestion);

    this->dialogTitle    = dialogTitle;
    this->dialogQuestion = dialogQuestion;
    this->dialogParent	 = parent;
}


boolean ConfirmedCommand::execute(CommandInterface *ci)
{

    Widget parent = this->dialogParent;
    if (!parent)  {
	if (ci)
	    parent = ci->getDialogParent();
	else
	    parent = theApplication->getRootWidget();
    }
    //
    // First post the confirmation dialog.
    //
    theQuestionDialogManager->modalPost(parent,
				   this->dialogQuestion,
				   this->dialogTitle,
				   (void*)this,
				   ConfirmedCommand::OkDCB);
				   
    return FALSE;
}


