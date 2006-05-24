// Completed 4/24/2006

using System;
using System.Collections.Generic;
using System.Text;

namespace WinDX.UI
{
    class ConfirmedExitCommand : OptionalPreActionCommand
    {
        private DXApplication application;

        public ConfirmedExitCommand(String name, CommandScope scope,
            bool active, DXApplication app)
            : base(name, scope, active,
        "Save Confirmation", "Do you want to save the macro(s)?")
        {
            application = app;
        }

        /// <summary>
        /// Return true if any macro has been modified.
        /// </summary>
        /// <returns></returns>
        protected override bool needsConfirmation()
        {
            foreach (Network net in application.macroList)
            {
                if (net.IsMacro && net.saveToFileRequired)
                    return true;
            }
            return false;
        }

        protected override void doPreAction()
        {
            SaveMacroCommand cmd = null, first = null, last = null;
            foreach (Network net in application.macroList)
            {
                if (net.IsMacro && net.saveToFileRequired)
                {
                    cmd = (SaveMacroCommand) net.getDefinition().getSaveCmd();
                    if (first == null)
                        first = cmd;
                    if (last != null)
                        last.setNext(cmd);
                    last = cmd;
                }
            }
            if (last != null)
            {
                last.setNext(this.application.quitCmd);
                first.execute();
            }
        }

        public override bool doIt(CommandInterface ci)
        {
            this.application.quitCmd.execute(ci);
            return true;
        }

        
    }
}
