// Completed 5/5/2006

using System;
using System.Collections.Generic;
using System.Text;
using System.Diagnostics;

namespace WinDX.UI
{
    class NoUndoAnchorCommand : NoUndoCommand
    {
        public enum AnchorCommandType
        {
            OpenVPE
        };

        protected DXAnchorWindow anchorWindow;
        protected AnchorCommandType commandType;

        public override bool doIt(CommandInterface ci)
        {
            Debug.Assert(anchorWindow != null);
            switch (commandType)
            {
                case AnchorCommandType.OpenVPE:
                    anchorWindow.postVPE();
                    break;
                default:
                    Debug.Assert(false);
                    break;
            }
            return true;
        }

        public NoUndoAnchorCommand(String name, CommandScope scope,
            bool active, DXAnchorWindow aw,
            AnchorCommandType comType) :
            base(name, scope, active)
        {
            commandType = comType;
            anchorWindow = aw;
        }
    }
}
