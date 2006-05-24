using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;

namespace WinDX.UI
{
    public class DXToolStripMenuItem : ToolStripMenuItem
    {
        private CommandInterface ci;
        public DXToolStripMenuItem(String name, Command cmd)
            :
            base()
        {
            ci = new CommandInterface(name, cmd, this);

            this.Click += new EventHandler(cmd.executeEvent);
        }

        public DXToolStripMenuItem(String name, Command cmd,
            String bubbleHelp)
            : base()
        {
            ci = new CommandInterface(name, cmd, this);

            this.Click += new EventHandler(cmd.executeEvent);

            if (bubbleHelp != null)
            {
                // set bubble help
            }
        }
    }
}
