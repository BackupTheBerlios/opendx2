/////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxuilib/Attic/NoUndoNetworkCommand.C,v 1.1 1999/03/24 15:17:44 gda Exp $
 */


#include "UIConfig.h"
#include "defines.h"
#include "NoUndoNetworkCommand.h"
#include "Network.h"
#include "DXApplication.h"
#include "DXWindow.h"
#include "EditorWindow.h"

NoUndoNetworkCommand::NoUndoNetworkCommand(const char*   name,
				       CommandScope* scope,
				       boolean       active,
				       Network	*net,
				       NetworkCommandType comType ) :
	NoUndoCommand(name, scope, active)
{
	this->commandType = comType;
	this->network = net;
}


boolean NoUndoNetworkCommand::doIt(CommandInterface *ci)
{
    Network *net = this->network;

    ASSERT(net);

    switch (this->commandType) {
	case NoUndoNetworkCommand::HelpOnNetwork:
	    net->postHelpOnNetworkDialog();
	    break;
	case NoUndoNetworkCommand::SetNetworkName:
	    net->postNameDialog();
	    break;
	case NoUndoNetworkCommand::SaveNetwork:
	    net->saveNetwork(net->getFileName());
	    break;
	case NoUndoNetworkCommand::SaveNetworkAs:
	    if (net->isNetworkSavable())
		net->postSaveAsDialog(net->isMacro() ?
                        net->getEditor()->getRootWidget() :
                        theDXApplication->getAnchor()->getRootWidget());
	    break;
	case NoUndoNetworkCommand::SaveConfiguration:
            net->postSaveCfgDialog(net->isMacro() ?
                        net->getEditor()->getRootWidget() :
                        theDXApplication->getAnchor()->getRootWidget());
	    break;
	case NoUndoNetworkCommand::OpenConfiguration:
            net->postOpenCfgDialog(net->isMacro() ?
                        net->getEditor()->getRootWidget() :
                        theDXApplication->getAnchor()->getRootWidget());
	    break;
	default:
	    ASSERT(0);
    }

    return TRUE;
}


//
// Only activate the save and SaveAs commands when theDXApplication 
// allows saving networks as defined by appAllowsSavingNetFile()
//
void NoUndoNetworkCommand::activate()
{
    boolean doit;

    switch (this->commandType) {
	case NoUndoNetworkCommand::SaveNetwork:
	case NoUndoNetworkCommand::SaveNetworkAs:
	    doit = theDXApplication->appAllowsSavingNetFile(this->network);
	    break;
	default:
	    doit = TRUE;
	    break;
    }
    if (doit)
	this->NoUndoCommand::activate();

}
