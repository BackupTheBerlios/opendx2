using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace WinDX.UI
{
    public partial class ImageWindow : DXWindow
    {
        public ImageWindow(bool isAnchor, Network network)
            : base("imageWindow", isAnchor, DXApplication.theDXApplication.appAllowsImageMenus())
        {
            InitializeComponent();
        }

        public override bool IsAnchor { get { return false; } }
        protected override Control createWorkArea(Form parent)
        {
            throw new Exception("The method or operation is not implemented.");
        }

        // Not implemented below this line
        public void resetWindowTitle() { }
    }
}