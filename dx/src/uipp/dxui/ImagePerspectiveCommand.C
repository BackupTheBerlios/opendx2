//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxui/ImagePerspectiveCommand.C,v 1.1 1999/03/31 22:32:11 gda Exp $
 */


#include "defines.h"
#include "ImagePerspectiveCommand.h"
#include "ImageWindow.h"

ImagePerspectiveCommand::ImagePerspectiveCommand(const char   *name,
				   CommandScope *scope,
				   boolean       active,
				   ImageWindow  *w,
				   boolean       enable):
    NoUndoCommand(name, scope, active)
{
    this->imageWindow = w;
    this->enablePerspective = enable;
}

boolean
ImagePerspectiveCommand::doIt(CommandInterface *ci)
{
    return this->imageWindow->enablePerspective(this->enablePerspective);
}
