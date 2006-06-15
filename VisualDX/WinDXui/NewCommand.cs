// Completed 5/19/2006

using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;

namespace WinDX.UI
{
    class NewCommand : OptionalPreActionCommand
    {
        private Network network;

        protected override bool needsConfirmation()
        {
            return network.SaveToFileRequired;
        }
        protected override void doPreAction()
        {
            Network net = DXApplication.theDXApplication.network;
            String fname = net.FileName;

            if (fname != null)
            {
                if (net.saveNetwork(fname))
                    this.doIt(null);
            }
            else
            {
                Form p = parent;
                if (p == null)
                    p = DXApplication.theDXApplication.getAnchorForm();
                net.postSaveAsDialog(p, this);
            }
        }
        public override bool doIt(CommandInterface ci)
        {
            DXApplication.theDXApplication.resetServer();
            return network.clear();
        }

        public NewCommand(String name, CommandScope scope, bool active,
            Network net, Form dialogParent)
            : base(name, scope, active,
            "Save Confirmation", "Do you want to save the program?",
            dialogParent)
        {
            network = net;
        }

    }
}
