/*  Open Visualization Data Explorer Source File */

#include <dxconfig.h>




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
