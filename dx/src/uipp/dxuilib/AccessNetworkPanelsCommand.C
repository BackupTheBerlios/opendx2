//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxuilib/Attic/AccessNetworkPanelsCommand.C,v 1.1 1999/03/24 15:17:38 gda Exp $
 */


#include "UIConfig.h"
#include "defines.h"
#include "AccessNetworkPanelsCommand.h"
#include "Network.h"
#include "CommandInterface.h"

AccessNetworkPanelsCommand::
    AccessNetworkPanelsCommand(const char*   name,
				CommandScope* scope,
				boolean       active,
				Network*      network,
				AccessPanelType	how) :
	NoUndoCommand(name, scope, active)
{
    ASSERT(network);
    //
    // Save the associated network.
    //
    this->network 	= network;
    this->accessType	= how;
}


boolean AccessNetworkPanelsCommand::doIt(CommandInterface *ci)
{
    Network *network = this->network;
   

    switch (this->accessType) {
	case AccessNetworkPanelsCommand::OpenAllPanels:
	    network->openControlPanel(0);
	    break;
	case AccessNetworkPanelsCommand::CloseAllPanels:
	    network->closeControlPanel(0);
	    break;
	case AccessNetworkPanelsCommand::OpenPanelByInstance:
	    if (ci)
		network->openControlPanel((int)ci->getLocalData());
	    break;
	case AccessNetworkPanelsCommand::OpenPanelGroupByIndex:
	    if (ci)
		network->openControlPanelGroup((int)ci->getLocalData());
	    break;
    }

    //
    // Return the result.
    //
    return TRUE;
}


