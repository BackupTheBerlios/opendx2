//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxui/ImageLookCommand.C,v 1.1 1999/03/31 22:32:06 gda Exp $
 */



#include "defines.h"
#include "ImageLookCommand.h"
#include "ImageWindow.h"

ImageLookCommand::ImageLookCommand(const char   *name,
						 CommandScope *scope,
						 boolean       active,
						 ImageWindow  *w,
						 LookDirection dir):
    NoUndoCommand(name, scope, active)
{
    this->imageWindow = w;
    this->direction = dir;
}

boolean ImageLookCommand::doIt(CommandInterface *ci)
{
    return this->imageWindow->setLook(this->direction);
}
