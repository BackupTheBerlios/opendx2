/*  Open Visualization Data Explorer Source File */

#include <dxconfig.h>




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
