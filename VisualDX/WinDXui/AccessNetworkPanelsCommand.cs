// Completed
// Last edited 4/03/2006

using System;
using System.Collections.Generic;
using System.Text;
using System.Diagnostics;

namespace WinDX.UI
{
    class AccessNetworkPanelsCommand : NoUndoCommand
    {
        public enum AccessPanelType
        {
            OpenAllPanels,
            CloseAllPanels,
            OpenPanelByInstance,
            OpenPanelGroupByIndex
        }

        protected Network network;
        protected AccessPanelType accessType;

        AccessNetworkPanelsCommand(String name,
            CommandScope scope, bool active, Network network,
            AccessPanelType how)
            : base(name, scope, active)
        {
            Debug.Assert(network != null);

            this.network = network;
            this.accessType = how;
        }

        public override bool doIt(CommandInterface ci)
        {
            switch (accessType)
            {
                case AccessPanelType.OpenAllPanels:
                    network.openControlPanel(0);
                    break;
                case AccessPanelType.CloseAllPanels:
                    network.closeControlPanel(0);
                    break;
                case AccessPanelType.OpenPanelByInstance:
                    if (ci != null)
                        network.openControlPanel((int) ci.LocalData);
                    break;
                case AccessPanelType.OpenPanelGroupByIndex:
                    if (ci != null)
                        network.openControlPanelGroup((int) ci.LocalData);
                    break;
            }
            return true;
        }

    }
}
