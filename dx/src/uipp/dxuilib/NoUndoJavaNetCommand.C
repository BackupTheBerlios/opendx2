/////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxuilib/Attic/NoUndoJavaNetCommand.C,v 1.1 1999/03/24 15:17:43 gda Exp $
 */


#include "UIConfig.h"
#include "defines.h"
#include "NoUndoJavaNetCommand.h"
#include "JavaNet.h"

NoUndoJavaNetCommand::NoUndoJavaNetCommand(const char*   name,
				       CommandScope* scope,
				       boolean       active,
				       JavaNet	*net,
				       JavaNetCommandType comType ) :
	NoUndoCommand(name, scope, active)
{
	this->commandType = comType;
	this->network = net;
}


boolean NoUndoJavaNetCommand::doIt(CommandInterface *ci)
{
    JavaNet *net = this->network;

    ASSERT(net);

    switch (this->commandType) {
	case NoUndoJavaNetCommand::SaveBean:
	    net->saveBean();
	    break;
	case NoUndoJavaNetCommand::SaveApplet:
	    net->saveApplet();
	    break;
	case NoUndoJavaNetCommand::SaveWebPage:
            net->saveWebPage();
	    break;
	default:
	    ASSERT(0);
    }

    return TRUE;
}


