
//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxuilib/Attic/ImageApproxCommand.C,v 1.1 1999/03/24 15:17:40 gda Exp $
 */


#include "defines.h"
#include "ImageApproxCommand.h"
#include "ImageWindow.h"

ImageApproxCommand::ImageApproxCommand(const char   *name,
						 CommandScope *scope,
						 boolean       active,
						 ImageWindow  *w,
						 boolean    up,
						 ApproxMode mode):
    NoUndoCommand(name, scope, active)
{
    this->imageWindow = w;
    this->up = up;
    this->mode = mode;
}

boolean ImageApproxCommand::doIt(CommandInterface *ci)
{
    this->imageWindow->setApproximation(this->up, this->mode);
    return TRUE;
}
