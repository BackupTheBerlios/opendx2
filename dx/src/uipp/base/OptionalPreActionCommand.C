//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/base/OptionalPreActionCommand.C,v 1.1 1999/03/24 15:17:24 gda Exp $
 */


#include "OptionalPreActionCommand.h"

OptionalPreActionCommand::OptionalPreActionCommand(const char*   name,
				   CommandScope* scope,
				   boolean       active,
				   char*         dialogTitle,
				   char*         dialogQuestion,
				   Widget	 dialogParent):
	PreActionCommand(name, scope, active, 
			dialogTitle, dialogQuestion, dialogParent)
{
}


boolean OptionalPreActionCommand::execute(CommandInterface *ci)
{
    //
    // First post the confirmation dialog.
    //
    if (this->needsConfirmation())
	this->PreActionCommand::execute(ci);
    else
	this->NoUndoCommand::execute(ci);
    return FALSE;
}
