/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>
#include "defines.h"


#include "OptionalPreActionCommand.h"

OptionalPreActionCommand::OptionalPreActionCommand(const char*   name,
				   CommandScope* scope,
				   bool       active,
				   char*         dialogTitle,
				   char*         dialogQuestion):
	PreActionCommand(name, scope, active, 
			dialogTitle, dialogQuestion)
{
}


bool OptionalPreActionCommand::execute(CommandInterface *ci)
{
    //
    // First post the confirmation dialog.
    //
    if (this->needsConfirmation())
	this->PreActionCommand::execute(ci);
    else
	this->NoUndoCommand::execute(ci);
    return false;
}
