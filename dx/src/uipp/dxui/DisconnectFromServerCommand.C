/*  Open Visualization Data Explorer Source File */


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
