//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/base/NoOpCommand.C,v 1.1 1999/03/24 15:17:24 gda Exp $
 */


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
