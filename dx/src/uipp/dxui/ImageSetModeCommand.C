//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxui/ImageSetModeCommand.C,v 1.1 1999/03/31 22:32:20 gda Exp $
 */


#include "defines.h"
#include "ImageSetModeCommand.h"
#include "ImageWindow.h"

ImageSetModeCommand::ImageSetModeCommand(const char   *name,
						 CommandScope *scope,
						 boolean       active,
						 ImageWindow  *w,
						 DirectInteractionMode mode):
    NoUndoCommand(name, scope, active)
{
    this->imageWindow = w;
    this->mode = mode;
}

boolean ImageSetModeCommand::doIt(CommandInterface *ci)
{
    return this->imageWindow->setInteractionMode(mode);
}
