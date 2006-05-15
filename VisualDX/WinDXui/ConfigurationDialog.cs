using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace WinDX.UI
{
    public partial class ConfigurationDialog : Form
    {
        public ConfigurationDialog()
        {
            InitializeComponent();
        }

        public static ConfigurationDialog AllocateConfigurationDialog(Form parent, Node node)
        {
            throw new Exception("Not Yet Implemented");
        }
    }
}