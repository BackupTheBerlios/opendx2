using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Diagnostics;

namespace WinDX.UI
{
    public abstract partial class DialogManager : Form
    {
        public delegate void DialogCallback(Object sender, System.EventArgs e);

        protected Object data = null;
        protected Form lastParent = null;
        protected String name = null;

        public DialogManager()
        {
            InitializeComponent();
        }

        protected DialogManager(String name)
        {
            InitializeComponent();
            this.name = name;
        }

        protected abstract void createDialog();

        public void post(String fmt, params Object[] list)
        {
            String s = String.Format(fmt, list);
            post(MainProgram.theApplication.getRootForm(),
                s, null, null, null, null, null,
                null, null, null, 2);
        }

        public void modalPost(String fmt, params Object[] list)
        {
            String s = String.Format(fmt, list);
            modalPost(MainProgram.theApplication.getRootForm(),
                s, null, null, null, null, null,
                null, null, null, 2);
        }

        public void post(Form parent, String message,
    String title, Object clientData, DialogCallback okCallback,
    DialogCallback cancelCallback, DialogCallback helpCallback,
    String okLabel, String cancelLabel, String helpLabel, int cancelBtnNum)
        {
            if (parent == null)
                this.Parent = MainProgram.theApplication.getRootForm();
            else
                this.Parent = parent;

            createDialog();
            this.messageLabel.Text = message;
            if (title != null)
                this.Text = title;
            Debug.Assert((cancelBtnNum >= 1) && (cancelBtnNum <= 3));

            data = clientData;
            if (okLabel != null)
                this.okButton.Text = okLabel;
            if (cancelLabel != null)
                this.cancelButton.Text = cancelLabel;
            if (helpLabel != null)
                this.helpButton.Text = helpLabel;
            if (helpCallback == null)
            {
                this.helpButton.Visible = false;
            }
            else
                this.helpButton.Click += new EventHandler(helpCallback);

            if (okCallback != null)
                this.okButton.Click += new EventHandler(okCallback);
            if (cancelCallback != null)
                this.cancelButton.Click += new EventHandler(cancelCallback);

            this.Show();
        }

        public void modalPost(Form parent, String message,
            String title, Object clientData, DialogCallback okCallback,
            DialogCallback cancelCallback, DialogCallback helpCallback,
            String okLabel, String cancelLabel, String helpLabel, int cancelBtnNum)
        {
            if (parent == null)
                this.Parent = MainProgram.theApplication.getRootForm();
            else
                this.Parent = parent;

            createDialog();
            this.messageLabel.Text = message;
            if (title != null)
                this.Text = title;
            Debug.Assert((cancelBtnNum >= 1) && (cancelBtnNum <= 3));

            data = clientData;
            if (okLabel != null)
                this.okButton.Text = okLabel;
            if (cancelLabel != null)
                this.cancelButton.Text = cancelLabel;
            if (helpLabel != null)
                this.helpButton.Text = helpLabel;

            if (helpCallback == null)
            {
                this.helpButton.Visible = false;
            }
            else
                this.helpButton.Click += new EventHandler(helpCallback);

            if (okCallback != null)
                this.okButton.Click += new EventHandler(okCallback);
            if (cancelCallback != null)
                this.cancelButton.Click += new EventHandler(cancelCallback);

            this.ShowDialog();

        }
    }
}