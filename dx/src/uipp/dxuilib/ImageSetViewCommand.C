//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxuilib/Attic/ImageSetViewCommand.C,v 1.1 1999/03/24 15:17:42 gda Exp $
 */


#include "defines.h"
#include "ImageSetViewCommand.h"
#include "ImageWindow.h"

ImageSetViewCommand::ImageSetViewCommand(const char   *name,
						 CommandScope *scope,
						 boolean       active,
						 ImageWindow  *w,
						 ViewDirection dir):
    NoUndoCommand(name, scope, active)
{
    this->imageWindow = w;
    this->direction = dir;
}

boolean ImageSetViewCommand::doIt(CommandInterface *ci)
{
    return this->imageWindow->setView(this->direction);
}
