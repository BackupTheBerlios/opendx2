/*  Open Visualization Data Explorer Source File */

#include <dxconfig.h>




#include "defines.h"
#include "ImageSoftwareCommand.h"
#include "ImageWindow.h"

ImageSoftwareCommand::ImageSoftwareCommand(const char   *name,
						 CommandScope *scope,
						 boolean       active,
						 ImageWindow  *w):
    NoUndoCommand(name, scope, active)
{
    this->imageWindow = w;
}

boolean ImageSoftwareCommand::doIt(CommandInterface *ci)
{
    Boolean set;
    XtVaGetValues(ci->getRootWidget(), XmNset, &set, NULL);
    this->imageWindow->setSoftware(set);
    return TRUE;
}
