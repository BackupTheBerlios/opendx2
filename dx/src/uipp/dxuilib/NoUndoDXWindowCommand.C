//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxuilib/Attic/NoUndoDXWindowCommand.C,v 1.1 1999/03/24 15:17:43 gda Exp $
 */


#include "UIConfig.h"

#include "defines.h"
#include "NoUndoDXWindowCommand.h"
#include "ToggleButtonInterface.h"
#include "DXWindow.h"

NoUndoDXWindowCommand::NoUndoDXWindowCommand(const char*   name,
				       CommandScope* scope,
				       boolean       active,
				       DXWindow  *window,
				       DXWindowCommandType comType ) :
	NoUndoCommand(name, scope, active)
{
	this->commandType = comType;
	this->dxWindow = window;
}


boolean NoUndoDXWindowCommand::doIt(CommandInterface *ci)
{
    DXWindow *window = this->dxWindow;

    ASSERT(window);

    switch (this->commandType) {
	case NoUndoDXWindowCommand::ToggleWindowStartup:
	    window->toggleWindowStartup();
	    if (window->isStartup())
		this->notifyClients(ToggleButtonInterface::MsgToggleOn);
	    else
		this->notifyClients(ToggleButtonInterface::MsgToggleOff);
	    break;
	default:
	    ASSERT(0);
    }

    return TRUE;
}


