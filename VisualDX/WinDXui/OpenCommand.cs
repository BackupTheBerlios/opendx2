//Completed 4/24/2006

using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;

namespace WinDX.UI
{
    class OpenCommand : OptionalPreActionCommand
    {
        private DXApplication application;

        public OpenCommand(String name, CommandScope scope, bool active,
            DXApplication app, Form parent)
            : base(name, scope, active,
            "Save Confirmation", "Do you want to save the program?",
            parent)
        {
            this.application = app;
        }

        public OpenCommand(String name, CommandScope scope, bool active,
            DXApplication app)
            : base(name, scope, active,
            "Save Confirmation", "Do you want to save the program?")
        {
            this.application = app;
        }

        protected override bool needsConfirmation()
        {
            return this.application.network.SaveToFileRequired;
        }

        protected override void doPreAction()
        {
            Network net = application.network;
            String fname = net.FileName;

            if (fname != null)
            {
                if (net.saveNetwork(fname))
                {
                    this.doIt(null);
                }
            }
            else
            {
                if (parent != null)
                    net.postSaveAsDialog(parent, this);
                else
                    net.postSaveAsDialog(application.getAnchor(), this);
            }

        }

        public override bool doIt(CommandInterface ci)
        {
            this.application.postOpenNetworkDialog();
            return true;
        }
    }
}
