/*  Open Visualization Data Explorer Source File */



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
