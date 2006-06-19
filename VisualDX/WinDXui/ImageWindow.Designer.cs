using System.Windows.Forms;
using System.ComponentModel;
using System.Drawing;

namespace WinDX.UI
{
    partial class ImageWindow
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.Text = "ImageWindow";
            pictureBox = new PictureBox();
            ((ISupportInitialize)(pictureBox)).BeginInit();
            this.SuspendLayout();

            pictureBox.Anchor = ((AnchorStyles)((((AnchorStyles.Top | AnchorStyles.Bottom)
                | AnchorStyles.Left) | AnchorStyles.Right)));
            pictureBox.BackColor = Color.White;
            pictureBox.Location = new Point(0, 27);
            pictureBox.Name = "pictureBox";
            pictureBox.Size = new Size(640, 480);
            pictureBox.SizeMode = PictureBoxSizeMode.StretchImage;
            pictureBox.TabIndex = 0;
            pictureBox.TabStop = false;

            // Will probably need to add the code for callbacks when the picture box
            // changes.

            //this.AutoSizeMode = AutoSizeMode.GrowAndShrink;
            this.ClientSize = new Size(640, 480);
            this.Controls.Add(pictureBox);
            this.DoubleBuffered = true;
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox)).EndInit();
            this.ResumeLayout();
            if (!IsAnchor)
                this.ShowIcon = false;
            //this.ResumeLayout(false);
            //this.PerformLayout();

        }

        #endregion
    }
}