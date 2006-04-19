using System;
using System.Collections.Generic;
using System.Text;

namespace WinDX.UI
{
    class NoOpCommand : Command
    {
        public NoOpCommand(String name, CommandScope scope,
            bool active)
            :
            base(name, scope, active) { }

        public override bool doIt(CommandInterface ci)
        {
            return true;
        }
        public override bool undoIt()
        {
            return true;
        }
    }
}
