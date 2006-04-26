// Complete 4/24/2006

using System;
using System.Collections.Generic;
using System.Text;

namespace WinDX.UI
{
    class DisconnectFromServerCommand : ConfirmedCommand
    {
        public DisconnectFromServerCommand(String name,
            CommandScope scope, bool active)
            :
            base(name, scope, active,
            "Disconnect from Server",
            "Do you really want to disconnect from the server?") { }

        public override bool doIt(CommandInterface ci)
        {
            return DXApplication.theDXApplication.disconnectFromServer();
        }

    }
}
