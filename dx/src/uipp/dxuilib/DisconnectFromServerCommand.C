//////////////////////////////////////////////////////////////////////////////
//                            DX  SOURCEFILE                                //
//                                                                          //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

/*
 * $Header: /home/xubuntu/berlios_backup/github/tmp-cvs/opendx2/Repository/dx/src/uipp/dxuilib/Attic/DisconnectFromServerCommand.C,v 1.1 1999/03/24 15:17:39 gda Exp $
 */

#include "defines.h"
#include "DisconnectFromServerCommand.h"
#include "DXApplication.h"


DisconnectFromServerCommand::DisconnectFromServerCommand(const char*   name,
                CommandScope* scope,
                boolean       active):
     ConfirmedCommand(name, scope, active,
		      "Disconnect from Server...",
		      "Do you really want to disconnect from the server?")
{
}

DisconnectFromServerCommand::~DisconnectFromServerCommand()
{
}

boolean DisconnectFromServerCommand::doIt(CommandInterface *ci)
{
    return theDXApplication->disconnectFromServer();
}
