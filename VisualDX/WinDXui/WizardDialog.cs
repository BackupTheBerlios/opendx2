// Complete 5/5/2006

using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;
using System.Diagnostics;
using System.IO;

namespace WinDX.UI
{
    class WizardDialog : TextEditDialog
    {
        private static bool ClassInitialized = false;

        private String text;
        private bool file_read;

        private static List<String> AlreadyWizzered = null;

        public WizardDialog(Form parent)
            : base("wizard", parent, true, true)
        {
            Parent = parent;
            cancelButton.Visible = false;
            restoreButton.Visible = false;
            applyButton.Visible = false;
            checkBox.Visible = true;
            text = "";
            file_read = false;
            ClassInitialized = true;
            okButton.Click += new EventHandler(okCallback);
            this.Text = MainProgram.theResources.GetString("WizardDialog_title");
            nameLabel.Text = MainProgram.theResources.GetString("WizardDialog_label");
            checkBox.Text = MainProgram.theResources.GetString("WizardDialog_checkbox");
        }

        public override void okCallback(object sender, EventArgs e)
        {
            if (checkBox.Enabled)
                DXApplication.theDXApplication.appendNoWizardName(Parent.Name);
            base.okCallback(sender, e);
        }

        public override string  getText()
        {
            if (text != null && text.Length > 0) return text;

            if (file_read) return null;

            file_read = true;

            String uiroot = MainProgram.theApplication.getUIRoot();
            Debug.Assert(uiroot != null);

            if (uiroot.ToCharArray()[uiroot.Length-1] != '/')
                uiroot += "/";
            
            if (Parent == null || Parent.Name == null)
                return null;

            uiroot += "/ui/" + Parent.Name;

            try
            {
                TextReader tr = new StringReader(uiroot);
                text = tr.ReadToEnd();
            }
            catch (Exception e)
            {
                return null;
            }

            return text;
        }



    }
}
