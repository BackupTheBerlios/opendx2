//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxuilib/Attic/ViewControlWhichCameraCommand.C,v 1.1 1999/03/24 15:17:49 gda Exp $
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
