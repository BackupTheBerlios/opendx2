/*  Open Visualization Data Explorer Source File */

#include <dxconfig.h>




#include "NoOpCommand.h"


NoOpCommand::NoOpCommand(const char*   name,
			 CommandScope* scope,
			 boolean       active) : Command(name, scope, active)
{
    //
    // No op.
    //
}

boolean NoOpCommand::doIt(CommandInterface *ci)
{
    return TRUE;
}

boolean NoOpCommand::undoIt()
{
    return TRUE;
}
