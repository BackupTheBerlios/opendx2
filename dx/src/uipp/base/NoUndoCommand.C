/*  Open Visualization Data Explorer Source File */

#include <dxconfig.h>




#include "NoUndoCommand.h"


NoUndoCommand::NoUndoCommand(const char*   name,
			     CommandScope* scope,
			     boolean       active): Command(name, scope, active)
{
    this->hasUndo = FALSE;
}


