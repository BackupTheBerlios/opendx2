using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;
using System.Diagnostics;

namespace WinDX.UI
{
    abstract class ConfirmedCommand : NoUndoCommand
    {
        private String dialogQuestion;
        private String dialogTitle;

        protected Form parent;

        protected ConfirmedCommand(String name,
            CommandScope scope,
            bool active,
            String dialogTitle,
            String dialogQuestion,
            Form parent)
            : base (name, scope, active)
        {
            Debug.Assert(dialogTitle != null);
            Debug.Assert(dialogQuestion != null);

            this.dialogTitle = dialogTitle;
            this.dialogQuestion = dialogQuestion;
            this.parent = parent;
        }
        protected ConfirmedCommand(String name,
            CommandScope scope,
            bool active,
            String dialogTitle,
            String dialogQuestion)
            : base (name, scope, active)
        {
            Debug.Assert(dialogTitle != null);
            Debug.Assert(dialogQuestion != null);

            this.dialogTitle = dialogTitle;
            this.dialogQuestion = dialogQuestion;
            parent = null;
        }

        public override bool execute(CommandInterface ci)
        {
            Form pf = parent;
            if (parent == null)
                pf = MainProgram.theApplication.getAnchorForm();

            QuestionDialog qd = new QuestionDialog();
            qd.modalPost(pf, dialogQuestion, dialogTitle,
                this, ok_Click, null, null, null, null,
                null, 2);

            return false;
        }
        public override bool execute()
        {
            return this.execute(null);
        }

        public void ok_Click(Object sender, System.EventArgs e) 
        {
            // This should be an instance. So I should be able
            // to just access. If not, what I'm going to have to 
            // do is something like:

            // Button button = (Button)sender;
            // DialogManager dm = (DialogManager) button.TopLevelControl;
            // ConfirmedCommand cc = (ConfirmedCommand) dm.data;
            // cc.base.execute(null);

            base.execute(null);
        }
    }
}
