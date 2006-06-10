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

        private void initInstanceData(Node node) { throw new Exception("Not Yet Implemented"); }
        private String HelpText;

        protected Node node;
        protected String initialNotation;

        //protected DescrDialog descriptionDialog;

        protected Form createDialog(Form parent) { throw new Exception("Not Yet Implemented"); }
        protected int typeWidth;
        protected virtual Control createBody(Form parent) { throw new Exception("Not Yet Implemented"); }
        protected virtual Control createInputs(Form parent) { throw new Exception("Not Yet Implemented"); }
        protected virtual Control createOutputs(Form parent) { throw new Exception("Not Yet Implemented"); }

        // Constructor (for derived classes):
        protected ConfigurationDialog(String name, Form parent, Node node)
        {
            throw new Exception("Not Yet Implemented");
        }

        //....

        public static ConfigurationDialog AllocateConfigurationDialog(Form parent, Node node)
        {
            throw new Exception("Not Yet Implemented");
        }

        public ConfigurationDialog(Form parent, Node node)
        {
            throw new Exception("Not Yet Implemented");
        }

        ~ConfigurationDialog() { throw new Exception("Not Yet Implemented"); }

        public virtual String getHelpSyntaxString()
        {
            throw new Exception("Not Yet Implemented");
        }

        // These functions are called by anyone when the Node gets reconfigured.
        // changeIn/Output are called when parameter i has changed status or
        // value or connection.  newIn/Output are called whenever a parameter
        // is added, and deleteIn/Output are called whenever a parameter is
        // deleted.  "i" in these is 1-based.
        public virtual void changeInput(int i) { throw new Exception("Not Yet Implemented"); }
        public virtual void changeOutput(int i) { throw new Exception("Not Yet Implemented"); }
        public virtual void newInput(int i) { throw new Exception("Not Yet Implemented"); }
        public virtual void newOutput(int i) { throw new Exception("Not Yet Implemented"); }
        public virtual void deleteInput(int i) { throw new Exception("Not Yet Implemented"); }
        public virtual void deleteOutput(int i) { throw new Exception("Not Yet Implemented"); }

        public virtual void changeLabel() { throw new Exception("Not Yet Implemented"); }

    }
}