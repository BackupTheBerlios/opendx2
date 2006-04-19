using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;

namespace WinDX.UI
{
    class WarningDialog : DialogManager
    {
        public WarningDialog(String name)
            : base(name)
        {
        }
        public WarningDialog()
            : base("")
        {
        }

        protected override void createDialog()
        {
            this.iconBox.Image = global::WinDX.UI.Resources.warning;
            this.Text = "Warning";
            this.cancelButton.Hide();
            this.helpButton.Hide();
            this.okButton.Click += new EventHandler(okButton_Click);
        }

        private void okButton_Click(object sender, EventArgs e)
        {
            Form f = (Form)((Button)sender).TopLevelControl;
            f.Close();
        }
    }
}
