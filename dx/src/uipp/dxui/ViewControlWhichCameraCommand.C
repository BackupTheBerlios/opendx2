/*  Open Visualization Data Explorer Source File */



#include "defines.h"
#include "ViewControlWhichCameraCommand.h"
#include "ViewControlDialog.h"

ViewControlWhichCameraCommand::ViewControlWhichCameraCommand(const char   *name,
						 CommandScope *scope,
						 boolean       active,
						 ViewControlDialog  *d):
    NoUndoCommand(name, scope, active)
{
    this->viewControlDialog = d;
}

boolean ViewControlWhichCameraCommand::doIt(CommandInterface *ci)
{
    this->viewControlDialog->setWhichCameraVector();
    return TRUE;
}
