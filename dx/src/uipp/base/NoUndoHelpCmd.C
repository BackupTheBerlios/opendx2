//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
// NoUndoHelpCmd.C 						    //
//                                                                          //
// NoUndoHelpCmd Class methods and other related functions.            //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/base/NoUndoHelpCmd.C,v 1.1 1999/03/24 15:17:24 gda Exp $
 */


#include "defines.h"
#include "NoUndoHelpCmd.h"
#include "HelpWin.h"


NoUndoHelpCmd::NoUndoHelpCmd(const char   *name,
			 CommandScope* scope,
			 boolean       active,
			 HelpWin      *helpWin,
			 HelpCmdType     comType):
    NoUndoCommand(name, scope, active)
{
    this->commandType = comType;
    this->helpWin = helpWin;
}


boolean NoUndoHelpCmd::doIt(CommandInterface *ci)
{
    HelpWin *helpWin = this->helpWin;
    boolean     ret = TRUE;

    ASSERT(helpWin);

    switch (this->commandType) {
    case NoUndoHelpCmd::Close:
        helpWin->unmanage();
        break;
    default:
	ASSERT(0);
    }

    return ret;
}
