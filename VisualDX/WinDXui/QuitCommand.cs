using System;
using System.Collections.Generic;
using System.Text;

namespace WinDX.UI
{
    class QuitCommand : ConfirmedCommand
    {
        private BaseApplication application;

        public QuitCommand(BaseApplication app,
            String name, CommandScope scope, bool active,
            String dialogTitle, String dialogQuestion)
            :
        base(name, scope, active, dialogTitle, dialogQuestion)
        {
            application = app;
        }

        public override bool doIt(CommandInterface ci)
        {
            application.shutdownApplication();
            return true;
        }

    }
}
