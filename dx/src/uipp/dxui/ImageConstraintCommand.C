/*  Open Visualization Data Explorer Source File */



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
