/*  Open Visualization Data Explorer Source File */

#include <dxconfig.h>




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
