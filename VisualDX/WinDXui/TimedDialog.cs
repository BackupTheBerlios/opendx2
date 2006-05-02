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
    public partial class TimedDialog : Form
    {
        static Timer popDownTimer = new Timer();
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
            dialog = this;
            InitializeComponent();
            Bitmap buttonimg = global::WinDX.UI.Resources.OpenDX_Splash;
            this.ImageButton.Image = buttonimg;

            if (parent == null)
                this.Parent = MainProgram.theApplication.getRootForm();
            else
                this.Parent = parent;
            this.messageLabel.Text = message;
            this.Text = title;

            popDownTimer.Tick += new EventHandler(Popdown);
            popDownTimer.Interval = timeout;
            popDownTimer.Start();

            this.ShowDialog();
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