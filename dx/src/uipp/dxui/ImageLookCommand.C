/*  Open Visualization Data Explorer Source File */

#include <dxconfig.h>





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
