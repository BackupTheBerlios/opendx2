//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxui/ImageResetCommand.C,v 1.1 1999/03/31 22:32:17 gda Exp $
 */


#include "defines.h"
#include "ImageResetCommand.h"
#include "ImageWindow.h"

ImageResetCommand::ImageResetCommand(const char   *name,
						 CommandScope *scope,
						 boolean       active,
						 ImageWindow  *w):
    NoUndoCommand(name, scope, active)
{
    this->imageWindow = w;
}

boolean ImageResetCommand::doIt(CommandInterface *ci)
{
    this->imageWindow->resetCamera();
    return TRUE;
}
