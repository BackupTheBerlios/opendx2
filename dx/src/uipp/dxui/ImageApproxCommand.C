/*  Open Visualization Data Explorer Source File */



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
