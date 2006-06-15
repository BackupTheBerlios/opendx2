using System;
using System.Collections.Generic;
using System.Text;

namespace WinDX.UI
{
    class MWClearCmd : NoUndoCommand
    {
        protected MsgWin messageWindow;

        public override bool doIt(CommandInterface ci)
        {
            messageWindow.clear();
            return true;
        }

        public MWClearCmd(String name, CommandScope scope, bool active, MsgWin win)
            :
            base(name, scope, active)
        {
            messageWindow = win;
        }

    }
}
