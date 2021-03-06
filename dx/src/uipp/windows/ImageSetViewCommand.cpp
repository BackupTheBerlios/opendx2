/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>
#include "defines.h"




#include "ImageSetViewCommand.h"
#include "ImageWindow.h"

ImageSetViewCommand::ImageSetViewCommand(const char   *name,
						 CommandScope *scope,
						 bool       active,
						 ImageWindow  *w,
						 ViewDirection dir):
    NoUndoCommand(name, scope, active)
{
    this->imageWindow = w;
    this->direction = dir;
}

bool ImageSetViewCommand::doIt(CommandInterface *ci)
{
    return this->imageWindow->setView(this->direction);
}
