//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxui/ImageConstraintCommand.C,v 1.1 1999/03/31 22:31:54 gda Exp $
 */


#include "defines.h"
#include "ImageConstraintCommand.h"
#include "ImageWindow.h"

ImageConstraintCommand::ImageConstraintCommand(const char   *name,
						 CommandScope *scope,
						 boolean       active,
						 ImageWindow  *w,
						 ConstraintDirection dir):
    NoUndoCommand(name, scope, active)
{
    this->imageWindow = w;
    this->direction = dir;
}

boolean ImageConstraintCommand::doIt(CommandInterface *ci)
{
    return this->imageWindow->setConstraint(this->direction);
}
