// Complete 5/5/2006

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace WinDX.UI
{
    public abstract partial class TextEditDialog : Form
    {
        bool readOnly;
        bool wizard;

        private void CommonConstructor()
        {
            InitializeComponent();
            checkBox.Visible = false;
            okButton.Text = MainProgram.theResources.GetString("TextEditDialog_okButton");
            cancelButton.Text = MainProgram.theResources.GetString("TextEditDialog_cancelButton");
            applyButton.Text = MainProgram.theResources.GetString("TextEditDialog_applyButton");
            restoreButton.Text = MainProgram.theResources.GetString("TextEditDialog_restoreButton");
            checkBox.Text = MainProgram.theResources.GetString("TextEditDialog_checkBox");

            okButton.Click += new EventHandler(okCallback);
            applyButton.Click += new EventHandler(applyCallback);
            restoreButton.Click += new EventHandler(restoreCallback);
            cancelButton.Click += new EventHandler(cancelCallback);
            Load += new EventHandler(updateInfo);
        }

        private void updateInfo(Object sender, EventArgs e)
        {
            textBox.Text = getText();
        }


        public TextEditDialog(String name, Form parent) 
        {
            CommonConstructor();
            readOnly = false;
            wizard = false;
        }
        public TextEditDialog(String name, Form parent, bool readOnly)
        {
            CommonConstructor();
            this.readOnly = readOnly;
            this.wizard = false;
        }
        public TextEditDialog(String name, Form parent, bool readOnly, bool wizard)
        {
            CommonConstructor();

            this.readOnly = readOnly;
            this.wizard = wizard;
        }

        public virtual void okCallback(Object sender, EventArgs e)
        {
            if (readOnly)
                saveEditorText();
        }

        public virtual void applyCallback(Object sender, EventArgs e)
        {
            saveEditorText();
        }

        public virtual void restoreCallback(Object sender, EventArgs e)
        {
            installEditorText("");
        }

        public virtual void cancelCallback(Object sender, EventArgs e)
        {
            // No implementation
        }

        public void installEditorText(String text)
        {
            if (text == null)
            {
                String s = getText();
                if (s == null)
                    s = "";
                textBox.Text = s;
            }
        }

        public bool saveEditorText()
        {
            return saveText(textBox.Text);
        }

        /// <summary>
        /// Get the the text that is to be edited. 
        /// At this level we return NULL; the subclass may redefine this.
        /// </summary>
        /// <returns></returns>
        public virtual String getText()
        {
            return null;
        }

        /// <summary>
        /// Save the given text. 
        /// At this level we do nothing; the subclass may redefine this.
        /// If there is no error then return TRUE. 
        /// </summary>
        /// <param name="s"></param>
        /// <returns></returns>
        public virtual bool saveText(String s)
        {
            return true;
        }

        public virtual String getDialogTitle()
        {
            return "";
        }
    }
}