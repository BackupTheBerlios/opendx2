// Completed 2/24/2006

using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;
using System.Diagnostics;

namespace WinDX.UI
{
    abstract class PreActionCommand : NoUndoCommand
    {
        private String dialogQuestion;
        private String dialogTitle;

        private CommandInterface ci = null;

        protected Form parent = null;

        protected PreActionCommand(String name, CommandScope scope, bool active,
            String dialogTitle, String dialogQuestion, Form parent)
            : base (name, scope, active)
        {
            Debug.Assert(dialogTitle != null);
            Debug.Assert(dialogQuestion != null);

            this.dialogTitle = dialogTitle;
            this.dialogQuestion = dialogQuestion;
            this.parent = parent;
        }
        protected PreActionCommand(String name, CommandScope scope, bool active,
            String dialogTitle, String dialogQuestion)
            : base (name, scope, active)
        {
            Debug.Assert(dialogTitle != null);
            Debug.Assert(dialogQuestion != null);

            this.dialogTitle = dialogTitle;
            this.dialogQuestion = dialogQuestion;
        }

        protected virtual void doPreAction() { }
 
        /// <summary>
        /// Overrides the supperclass execute() function:
        /// First posts a dialog to ask for user confirmation before
        /// actually executing the command.
        /// </summary>
        /// <param name="ci"></param>
        /// <returns></returns>
        public override bool execute(CommandInterface ci)
        {
            this.ci = ci;

            Form fp = parent;
            if (fp == null)
                fp = MainProgram.theApplication.getRootForm();

            QuestionDialog qd = new QuestionDialog();
            qd.modalPost(parent, dialogQuestion, dialogTitle, this,
                yes_Click, no_Click, cancel_Click, "Yes", "No", "Cancel", 3);

            return false;
        }
        public override bool execute() 
        {
            return this.execute(null);
        }

        public bool baseExecute(CommandInterface ci)
        {
            return base.execute(ci);
        }

        public void yes_Click(Object sender, System.EventArgs e)
        {
            this.doPreAction();
        }

        public void no_Click(Object sender, System.EventArgs e)
        {
            base.execute(this.ci);
        }

        public void cancel_Click(Object sender, System.EventArgs e)
        {
            Button b = (Button)sender;
            Form tlf = (Form)b.TopLevelControl;
            tlf.Close();
        }

    }
}
