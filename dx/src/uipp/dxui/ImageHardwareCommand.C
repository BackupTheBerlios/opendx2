/*  Open Visualization Data Explorer Source File */



#include "defines.h"
#include "ImageHardwareCommand.h"
#include "ImageWindow.h"

ImageHardwareCommand::ImageHardwareCommand(const char   *name,
						 CommandScope *scope,
						 boolean       active,
						 ImageWindow  *w):
    NoUndoCommand(name, scope, active)
{
    this->imageWindow = w;
}

boolean ImageHardwareCommand::doIt(CommandInterface *ci)
{
    Boolean set;
    XtVaGetValues(ci->getRootWidget(), XmNset, &set, NULL);
    this->imageWindow->setSoftware(!set);
    return TRUE;
}
