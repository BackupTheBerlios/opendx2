//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxuilib/Attic/ImageFormatCommand.C,v 1.1 1999/03/24 15:17:41 gda Exp $
 */


#include "defines.h"
#include "ImageFormatCommand.h"
#include "ImageFormatDialog.h"
#include "SaveImageDialog.h"

ImageFormatCommand::ImageFormatCommand(const char   *name,
						 CommandScope *scope,
						 boolean       active,
						 ImageFormatDialog  *dialog,
						 int commandType):
    NoUndoCommand(name, scope, active)
{
    this->dialog = dialog;
    this->commandType = commandType;
}

boolean ImageFormatCommand::doIt(CommandInterface *ci)
{
SaveImageDialog* sid = NUL(SaveImageDialog*);

    this->dialog->setBusyCursor(TRUE);
    boolean retval = FALSE;
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
    this->dialog->setBusyCursor(FALSE);
    return retval;
}
