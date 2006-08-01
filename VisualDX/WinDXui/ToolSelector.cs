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

        // Below are not implemented yet.
        public static bool AddTool(Symbol cat, Symbol tool, Object ptr)
        {
            return true;
        }
        public static bool RemoveTool(Symbol cat, Symbol tool)
        {
            return true;
        }

        public static bool UpdateCategoryList()
        {
            return true;
        }
    }
}
