/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>
#include "defines.h"


#include "ImageFormatCommand.h"
#include "ImageFormatDialog.h"
#include "SaveImageDialog.h"

ImageFormatCommand::ImageFormatCommand(const char   *name,
						 CommandScope *scope,
						 bool       active,
						 ImageFormatDialog  *dialog,
						 int commandType):
    NoUndoCommand(name, scope, active)
{
    this->dialog = dialog;
    this->commandType = commandType;
}

bool ImageFormatCommand::doIt(CommandInterface *ci)
{
SaveImageDialog* sid = NUL(SaveImageDialog*);

    this->dialog->setBusyCursor(true);
    bool retval = false;
    switch (this->commandType) {
	case ImageFormatCommand::AllowRerender:
	    retval = this->dialog->allowRerender();
	    break;
	case ImageFormatCommand::DelayedColors:
	    retval = this->dialog->delayedColors();
	    break;
	case ImageFormatCommand::SelectFile:
	    retval = this->dialog->postFileSelectionDialog();
	    break;
	case ImageFormatCommand::SaveCurrent:
	    sid = (SaveImageDialog*)this->dialog;
	    retval = sid->dirtyCurrent();
	    break;
	case ImageFormatCommand::SaveContinuous:
	    sid = (SaveImageDialog*)this->dialog;
	    retval = sid->dirtyContinuous();
	    break;
	default:
	    ASSERT(0);
	    break;
    }
    this->dialog->setBusyCursor(false);
    return retval;
}
