//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxui/ImageRedoCommand.C,v 1.1 1999/03/31 22:32:14 gda Exp $
 */


#include "defines.h"
#include "ImageRedoCommand.h"
#include "ImageWindow.h"

ImageRedoCommand::ImageRedoCommand(const char   *name,
						 CommandScope *scope,
						 boolean       active,
						 ImageWindow  *w):
    NoUndoCommand(name, scope, active)
{
    this->imageWindow = w;
}

boolean ImageRedoCommand::doIt(CommandInterface *ci)
{
    this->imageWindow->redoCamera();
    return TRUE;
}
