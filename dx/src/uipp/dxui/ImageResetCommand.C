/*  Open Visualization Data Explorer Source File */



#include "defines.h"
#include "ImageResetCommand.h"
#include "ImageWindow.h"

ImageResetCommand::ImageResetCommand(const char   *name,
						 CommandScope *scope,
						 boolean       active,
						 ImageWindow  *w):
    NoUndoCommand(name, scope, active)
{
    this->imageWindow = w;
}

boolean ImageResetCommand::doIt(CommandInterface *ci)
{
    this->imageWindow->resetCamera();
    return TRUE;
}
