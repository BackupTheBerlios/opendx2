//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxui/NoUndoAnchorCommand.C,v 1.1 1999/03/31 22:32:57 gda Exp $
 */


#include "defines.h"
#include "NoUndoAnchorCommand.h"
#include "DXAnchorWindow.h"
#include "DXApplication.h"
#include "Network.h"

NoUndoAnchorCommand::NoUndoAnchorCommand(const char*   name,
				       CommandScope* scope,
				       boolean       active,
				       DXAnchorWindow  *aw,
				       AnchorCommandType comType ) :
	NoUndoCommand(name, scope, active)
{
	this->commandType = comType;
	this->anchorWindow = aw;
}


boolean NoUndoAnchorCommand::doIt(CommandInterface *ci)
{
    Command *cmd;
    DXAnchorWindow *aw = this->anchorWindow;

    ASSERT(aw);

    switch (this->commandType) {
	case NoUndoAnchorCommand::OpenVPE:
            aw->postVPE();
	    break;
	default:
	    ASSERT(0);
    }

    return TRUE;
}


