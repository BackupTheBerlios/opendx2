//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
// NoUndoMWCmd.C 						    //
//                                                                          //
// NoUndoMWCmd Class methods and other related functions.            //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxuilib/NoUndoMWCmd.C,v 1.1 1999/03/24 15:17:44 gda Exp $
 */


#include "defines.h"
#include "NoUndoMWCmd.h"
#include "MsgWin.h"


NoUndoMWCmd::NoUndoMWCmd(const char   *name,
			 CommandScope* scope,
			 boolean       active,
			 MsgWin       *messageWindow,
			 MWCmdType     comType):
    NoUndoCommand(name, scope, active)
{
    this->commandType = comType;
    this->messageWindow = messageWindow;
}


boolean NoUndoMWCmd::doIt(CommandInterface *ci)
{
    MsgWin *messageWindow = this->messageWindow;
    boolean     ret = TRUE;

    ASSERT(messageWindow);

    switch (this->commandType) {
    case NoUndoMWCmd::Log:
	if (messageWindow->getLogFile() != NULL)
	    messageWindow->log(NULL);
	else
	    messageWindow->postLogDialog();
	break;
    case NoUndoMWCmd::Save:
	messageWindow->postSaveDialog();
	break;
    case NoUndoMWCmd::Close:
        messageWindow->unmanage();
        break;
    case NoUndoMWCmd::NextError:
        messageWindow->findNextError();
        break;
    case NoUndoMWCmd::PrevError:
        messageWindow->findPrevError();
        break;
    case NoUndoMWCmd::ExecScript:
        messageWindow->postExecCommandDialog();
        break;
    case NoUndoMWCmd::Tracing:
	messageWindow->toggleTracing();
	break;
    case NoUndoMWCmd::Memory:
	messageWindow->memoryUse();
	break;
    default:
	ASSERT(0);
    }

    return ret;
}
