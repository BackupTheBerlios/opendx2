/*  Open Visualization Data Explorer Source File */



#include "defines.h"
#include "ImageRedoCommand.h"
#include "ImageWindow.h"

ImageRedoCommand::ImageRedoCommand(const char   *name,
						 CommandScope *scope,
						 boolean       active,
						 ImageWindow  *w):
    NoUndoCommand(name, scope, active)
{
    this->imageWindow = w;
}

boolean ImageRedoCommand::doIt(CommandInterface *ci)
{
    this->imageWindow->redoCamera();
    return TRUE;
}
