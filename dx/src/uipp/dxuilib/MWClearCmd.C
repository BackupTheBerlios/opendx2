//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxuilib/MWClearCmd.C,v 1.1 1999/03/24 15:17:43 gda Exp $
 */


#include "defines.h"
#include "MWClearCmd.h"
#include "MsgWin.h"



//
// Constructor:
//
MWClearCmd::MWClearCmd(const char *name,
	   CommandScope *scope,
	   boolean active,
	   MsgWin *win):
    NoUndoCommand(name, scope, active)
{
    this->messageWindow = win;
}


boolean MWClearCmd::doIt(CommandInterface *ci)
{
    this->messageWindow->clear();

    return TRUE;
}
