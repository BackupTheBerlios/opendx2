/*  Open Visualization Data Explorer Source File */



#include "defines.h"
#include "ImageUndoCommand.h"
#include "ImageWindow.h"

ImageUndoCommand::ImageUndoCommand(const char   *name,
						 CommandScope *scope,
						 boolean       active,
						 ImageWindow  *w):
    NoUndoCommand(name, scope, active)
{
    this->imageWindow = w;
}

boolean ImageUndoCommand::doIt(CommandInterface *ci)
{
    this->imageWindow->undoCamera();
    return TRUE;
}
