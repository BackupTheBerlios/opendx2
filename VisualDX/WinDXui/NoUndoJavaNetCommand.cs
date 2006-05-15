// Completed 5/8/2006

using System;
using System.Collections.Generic;
using System.Text;
using System.Diagnostics;

namespace WinDX.UI
{
    class NoUndoJavaNetCommand : NoUndoCommand
    {
        public enum JavaNetCommandType
        {
            SaveWebPage,
            SaveApplet,
            SaveBean
        };

        protected JavaNet network;
        protected JavaNetCommandType commandType;

        public override bool doIt(CommandInterface ci)
        {
            Debug.Assert(network != null);

            switch (commandType)
            {
                case JavaNetCommandType.SaveBean:
                    network.saveBean();
                    break;
                case JavaNetCommandType.SaveApplet:
                    network.saveApplet();
                    break;
                case JavaNetCommandType.SaveWebPage:
                    network.saveWebPage();
                    break;
                default:
                    Debug.Assert(false);
                    break;
            }
            return true;
        }

        public NoUndoJavaNetCommand(String name,
            CommandScope scope, bool active, JavaNet n,
            JavaNetCommandType comType)
            :
            base(name, scope, active)
        {
            commandType = comType;
            network = n;
        }
    }
}
