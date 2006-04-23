using System;
using System.Collections.Generic;
using System.Text;

namespace WinDX.UI
{
    class SaveMacroCommand : NoUndoCommand
    {
        private MacroDefinition md;
        private Command next;

        public SaveMacroCommand(String name, CommandScope scope,
            bool active, MacroDefinition md)
            : base(name, scope, active)
        {
            this.md = md;
            this.next = null;
        }

        public override bool doIt(CommandInterface ci)
        {
            String message = "Do you want to save macro " + md.body.NameString;
            message += " as file: " + md.fileName;

            QuestionDialog qd = new QuestionDialog();
            qd.modalPost(
                DXApplication.theDXApplication.getAnchor(),
                message, "Save Confirmation",
                this,
                SaveMacro,
                DiscardMacro,
                null, "Yes", "No", null, 2);

            return true;
        }

        private void SaveMacro(Object sender, System.EventArgs e)
        {
            this.md.body.saveNetwork(this.md.fileName);
            if (this.next != null)
                this.next.execute();
        }

        private void DiscardMacro(Object sender, System.EventArgs e)
        {
            if (this.next != null)
                this.next.execute();
        }

        public void setNext(Command next)
        {
            this.next = next;
        }

    }
}
