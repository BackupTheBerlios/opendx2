using System;
using System.Collections.Generic;
using System.Text;

namespace WinDX.UI
{
    abstract class NoUndoCommand : Command
    {
        public override bool undoIt()
        {
            return false;
        }

        protected NoUndoCommand(String name, CommandScope scope, bool active) 
            : base(name, scope, active)
        {
            hasUndo = false;
        }
    }
}
