//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxui/ViewControlWhichCameraCommand.C,v 1.1 1999/03/31 22:36:04 gda Exp $
 */


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
