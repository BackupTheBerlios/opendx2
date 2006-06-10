using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;
using System.Diagnostics;

namespace WinDX.UI
{
    class UIComponentHelpCommand : NoUndoCommand
    {
        protected Control control = null;

        public UIComponentHelpCommand(String name, CommandScope scope,
            bool active, Control control)
            :
            base(name, scope, active)
        {
            Debug.Assert(control != null);
            this.control = control;
        }

        public override bool doIt(CommandInterface ci)
        {
            // This will automatically get called by WinForms--no need 
            // to actually do it here. Make sure that all Components have
            // a componentHelp function then register a delegate for 
            // HelpRequested.
            return true;
        }
    }
}
