using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;

namespace WinDX.UI
{
    class QuestionDialog : DialogManager
    {
        public QuestionDialog(String name)
            : base(name)
        {
        }

        public QuestionDialog()
            : base("")
        {
        }

        protected override void createDialog()
        {
            this.iconBox.Image = global::WinDX.UI.Resources.question;
            this.Text = "Question";
            this.okButton.Click += new EventHandler(okButton_Click);
        }

        private void okButton_Click(object sender, EventArgs e)
        {
            Form f = (Form)((Button)sender).TopLevelControl;
            f.Close();
        }

    }
}
