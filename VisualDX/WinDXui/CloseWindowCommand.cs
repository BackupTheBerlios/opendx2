// Completed 5/5/2006

using System;
using System.Collections.Generic;
using System.Text;
using System.Diagnostics;

namespace WinDX.UI
{
    class CloseWindowCommand : NoUndoCommand
    {
        protected MainWindow window;

        public override bool doIt(CommandInterface ci)
        {
            window.closeWindow();
            return true;
        }

        public CloseWindowCommand(String name, CommandScope scope,
            bool active, MainWindow window)
            :
            base(name, scope, active)
        {
            Debug.Assert(window != null);
            this.window = window;
        }


    }
}
