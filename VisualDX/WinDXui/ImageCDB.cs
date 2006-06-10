using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;

namespace WinDX.UI
{
    class ImageCDB : ConfigurationDialog
    {
        protected override Control createOutputs(Form parent)
        {
            throw new Exception("Not Yet Implemented");
            return base.createOutputs(parent);
        }

        public static ConfigurationDialog AllocatedConfigurationDialog(Form parent,
            Node node)
        {
            return new ImageCDB(parent, node);
        }

        public override void changeOutput(int i)
        {
            throw new Exception("Not Yet Implemented");
            base.changeOutput(i);
        }

        public ImageCDB(Form parent, Node node) :
            base("imageConfigurationDialog", parent, node)
        {
            
        }

        ~ImageCDB() { throw new Exception("Not Yet Implemented"); }

    }
}
