using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;

namespace WinDX.UI
{
    public class CascadeAutoToolStripMenuItem : ToolStripMenuItem
    {
        public CascadeAutoToolStripMenuItem(ToolStripMenuItem parent)
        {
            parent.DropDownOpening += new EventHandler(this.OnParentPopup);
        }

        private void OnParentPopup(object sender, EventArgs e)
        {
            if (this.DropDownItems.Count == 0)
                this.Enabled = false;
            else
                this.Enabled = true;
        }
    }
}
