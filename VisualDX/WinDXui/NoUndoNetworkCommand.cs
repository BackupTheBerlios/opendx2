// Completed 5/19/2006

using System;
using System.Collections.Generic;
using System.Text;
using System.Diagnostics;

namespace WinDX.UI
{
    class NoUndoNetworkCommand : NoUndoCommand
    {
        public enum NetworkCommandType
        {
            HelpOnNetwork,
            SetNetworkName,
            SaveNetwork,
            SaveNetworkAs,
            OpenConfiguration,
            SaveConfiguration
        };

        protected Network network;
        protected NetworkCommandType commandType;

        public override bool doIt(CommandInterface ci)
        {
            Debug.Assert(network != null);

            switch (commandType)
            {
                case NetworkCommandType.HelpOnNetwork:
                    network.postHelpOnNetworkDialog();
                    break;
                case NetworkCommandType.SetNetworkName:
                    network.postNameDialog();
                    break;
                case NetworkCommandType.SaveNetwork:
                    network.saveNetwork(network.FileName);
                    break;
                case NetworkCommandType.SaveNetworkAs:
                    if (network.IsNetworkSavable)
                        network.postSaveAsDialog(network.IsMacro ?
                            network.getEditor() : DXApplication.theDXApplication.getAnchor());
                    break;
                case NetworkCommandType.SaveConfiguration:
                    network.postSaveCfgDialog(network.IsMacro ?
                        network.getEditor() : DXApplication.theDXApplication.getAnchor());
                    break;
                case NetworkCommandType.OpenConfiguration:
                    network.postOpenCfgDialog(network.IsMacro ?
                        network.getEditor() : DXApplication.theDXApplication.getAnchor());
                    break;
                default:
                    Debug.Assert(false);
                    break;
            }
            return true;
        }

        public NoUndoNetworkCommand(String name, CommandScope scope, bool active,
            Network net, NetworkCommandType comType)
            : base(name, scope, active)
        {
            commandType = comType;
            network = net;
        }

        public override void activate()
        {
            bool doit;
            switch (commandType)
            {
                case NetworkCommandType.SaveNetwork:
                case NetworkCommandType.SaveNetworkAs:
                    doit = DXApplication.theDXApplication.appAllowsSavingNetFile(network);
                    break;
                default:
                    doit = true;
                    break;
            }
            if (doit)
                base.activate();
        }
    }
}
