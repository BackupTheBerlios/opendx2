
//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxui/ImageApproxCommand.C,v 1.1 1999/03/31 22:31:52 gda Exp $
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
