//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxui/ImageUndoCommand.C,v 1.1 1999/03/31 22:32:28 gda Exp $
 */


#include "defines.h"
#include "ImageUndoCommand.h"
#include "ImageWindow.h"

ImageUndoCommand::ImageUndoCommand(const char   *name,
						 CommandScope *scope,
						 boolean       active,
						 ImageWindow  *w):
    NoUndoCommand(name, scope, active)
{
    this->imageWindow = w;
}

boolean ImageUndoCommand::doIt(CommandInterface *ci)
{
    this->imageWindow->undoCamera();
    return TRUE;
}
