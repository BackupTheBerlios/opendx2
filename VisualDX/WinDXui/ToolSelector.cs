using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Text;
using System.Windows.Forms;

namespace WinDX.UI
{
    public partial class ToolSelector : UserControl
    {
        
        public ToolSelector()
        {
            InitializeComponent();
        }

        public static void MergeNewTools(Dictionary<Symbol, NodeDefinition> dict)
        {
            throw new Exception("Not Yet Implemented");
        }
    }
}
