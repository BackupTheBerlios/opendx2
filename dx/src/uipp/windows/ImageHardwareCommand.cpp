/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>
#include "defines.h"




#include "ImageHardwareCommand.h"
#include "ImageWindow.h"

ImageHardwareCommand::ImageHardwareCommand(const char   *name,
						 CommandScope *scope,
						 bool       active,
						 ImageWindow  *w):
    NoUndoCommand(name, scope, active)
{
    this->imageWindow = w;
}

bool ImageHardwareCommand::doIt(CommandInterface *ci)
{
    //Boolean set;
    //XtVaGetValues(ci->getRootWidget(), XmNset, &set, NULL);
    //this->imageWindow->setSoftware(!set);
    return true;
}
