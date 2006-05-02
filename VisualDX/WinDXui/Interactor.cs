using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Text;
using System.Windows.Forms;

namespace WinDX.UI
{
    public partial class Interactor : UserControl
    {
        public Interactor()
        {
            InitializeComponent();

        }
        public virtual void initialize()
        {
            throw new Exception("Not Yet Implemented");
        }
        public virtual void createInteractor()
        {
            throw new Exception("Not Yet Implemented");
        }
    }
}
