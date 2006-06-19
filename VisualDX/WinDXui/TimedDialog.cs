using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Diagnostics;
using System.Text.RegularExpressions;

namespace WinDX.UI
{
    public partial class TimedDialog : Form
    {
        static System.Windows.Forms.Timer popDownTimer = new System.Windows.Forms.Timer();
        static Form dialog = null;

        protected TimedDialog()
        {
            InitializeComponent();

            Bitmap buttonimg = global::WinDX.UI.Resources.OpenDX_Splash;
            this.ImageButton.Image = buttonimg;
        }

        public TimedDialog(String name, Form parent,
            String message, String title, int timeout)
        {
            Regex regex = new Regex(@"\\n");
            message = regex.Replace(message, Environment.NewLine);
            dialog = this;
            InitializeComponent();

            Bitmap buttonimg = global::WinDX.UI.Resources.OpenDX_Splash;
            this.ImageButton.Image = buttonimg;

            if (parent == null)
                this.Parent = MainProgram.theApplication.getAnchorForm();
            else
                this.Parent = parent;

            this.StartPosition = FormStartPosition.CenterScreen;

            this.messageLabel.Text = message;
            this.Text = title;

            popDownTimer.Tick += new EventHandler(Popdown);
            popDownTimer.Interval = timeout;
            popDownTimer.Start();

            this.Show();
            this.Refresh();
        }

        public static void Popdown(Object myObject, EventArgs myEventArgs)
        {
//            Debug.Assert(dialog != null);

            popDownTimer.Stop();
            dialog.Dispose();
        }

        private void ImageButton_Click(object sender, EventArgs e)
        {
            Popdown(sender, e);
        }
    }
}