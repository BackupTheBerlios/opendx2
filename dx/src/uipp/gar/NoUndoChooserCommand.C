//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
// NoUndoChooserCommand.C 						    //
//                                                                          //
// NoUndoChooserCommand Class methods and other related functions.        //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/gar/Attic/NoUndoChooserCommand.C,v 1.1 1999/03/24 15:17:28 gda Exp $
 */


#include "defines.h"
#include "NoUndoChooserCommand.h"
#include "GARChooserWindow.h"

NoUndoChooserCommand::NoUndoChooserCommand(const char*   name,
				       CommandScope* scope,
				       boolean       active,
				       GARChooserWindow *chooser,
				       ChooserCommandType comType) :
	NoUndoCommand(name, scope, active)
{
	this->commandType = comType;
	this->chooser = chooser;
}


boolean NoUndoChooserCommand::doIt(CommandInterface *)
{
    GARChooserWindow *chooser = this->chooser;
    boolean ret;

    ASSERT(chooser);

    ret = TRUE;
    switch (this->commandType) {

    case NoUndoChooserCommand::ShowMessages:
	ret = chooser->showMessages();
	break;

    case NoUndoChooserCommand::SelectDataFile:
	ret = chooser->postDataFileSelector();
	break;

    case NoUndoChooserCommand::OpenPrompter:
	ret = chooser->openExistingPrompter();
	break;

    case NoUndoChooserCommand::NoOp:
	ret = TRUE;
	break;

    default:
	ASSERT(0);
    }

    return ret;
}
