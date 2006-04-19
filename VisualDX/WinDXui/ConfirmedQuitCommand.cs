using System;
using System.Collections.Generic;
using System.Text;

namespace WinDX.UI
{
    class ConfirmedQuitCommand : OptionalPreActionCommand
    {
        private Command command;
        private DXApplication application;

        public ConfirmedQuitCommand(String name, CommandScope scope,
            bool active, DXApplication app)
            : base(name, scope, active,
            "Save Confirmation", "Do you want to save the program?")
        {
            application = app;
            command = null;
        }

        protected override bool needsConfirmation()
        {
            return application.network.saveToFileRequired();
        }

        protected override void doPreAction()
        {
            Network net = application.network;
            String fname = net.getFileName();

            if (fname != null)
            {
                if (net.saveNetwork(fname))
                    this.doIt(null);
            }
            else
                net.postSaveAsDialog(application.getAnchor(), this);
        }

        public override bool doIt(CommandInterface ci)
        {
            String dialogQuestion = "";
            if (!application.appAllowsConfirmedQuit())
            {
                application.shutdownApplication();
                return true;
            }

            if (this.command == null)
            {
                dialogQuestion = "Do you really want to quit " + application.getInformalName();

                CommandScope scope = scopeList[0];
                command = new QuitCommand(application, "quit", scope, true,
                    "Quit", dialogQuestion);
            }
            this.command.execute(ci);
            return true;
        }


    }
}
