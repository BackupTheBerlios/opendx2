using System;
using System.Collections.Generic;
using System.Text;

namespace WinDX.UI
{
    /// <summary>
    /// Class complete
    /// Used store command list.
    /// </summary>
    class CommandScope
    {
        private Command lastCommand = null;
        private Command undoCommand = null;

        public virtual void setLastCommand(Command command)
        {
            lastCommand = command;
        }

        public virtual void setUndoCommand(Command command)
        {
            undoCommand = command;
        }

        public Command getLastCommand()
        {
            return lastCommand;
        }

        public Command getUndoCommand()
        {
            return undoCommand;
        }

    }
}
