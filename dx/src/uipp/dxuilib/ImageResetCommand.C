//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxuilib/Attic/ImageResetCommand.C,v 1.1 1999/03/24 15:17:42 gda Exp $
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
