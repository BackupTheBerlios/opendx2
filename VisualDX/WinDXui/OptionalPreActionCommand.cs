using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;

namespace WinDX.UI
{
    abstract class OptionalPreActionCommand : PreActionCommand
    {
        protected OptionalPreActionCommand(String name,
            CommandScope scope, bool active, String dialogTitle,
            String dialogQuestion, Form parent)
            : base(name, scope, active, dialogTitle, dialogQuestion, parent)
        { }

        protected OptionalPreActionCommand(String name,
            CommandScope scope, bool active, String dialogTitle,
            String dialogQuestion)
            : base(
            name, scope, active, dialogTitle, dialogQuestion)
        { }

        protected abstract bool needsConfirmation();

        public override bool execute(CommandInterface ci)
        {
            if (needsConfirmation())
            {
                base.execute(ci);
            }
            else
            {
                base.baseExecute(ci);
            }

            return false;
        }
    }
}
