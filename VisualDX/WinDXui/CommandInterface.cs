using System;
using System.Collections.Generic;
using System.Text;
using System.Diagnostics;
using System.Reflection;
using System.Windows.Forms;

namespace WinDX.UI
{
    /// <summary>
    /// Class completed
    /// The Interface to commands.
    /// </summary>
    class CommandInterface : IClient
    {
        protected Command command;
        private Object localData;

        public Object LocalData
        {
            get { return localData; }
            set { localData = value; }
        }

        protected CommandInterface(String name)
        {
            throw new Exception("CommandInteface requires a command.");
        }

        protected CommandInterface(String name, Command command)
        {
            if (command == null)
            {
                StackFrame stackFrame = new StackFrame();
                MethodBase methodBase = stackFrame.GetMethod();
                throw new Exception(string.Format("{0}: invalid arg", methodBase));
            }

            this.name = name;
            this.command = command;
            command.registerClient(this);
        }

        private bool active;
        private String name;

        public bool Active
        {
            get { return active; }
            set { active = value; }
        }
	

        public virtual void notify(Symbol message)
        {
            notify(message, null, null);
        }

        public virtual void notify(Symbol message, Object msgdata)
        {
            notify(message, msgdata, null);
        }

        public virtual void notify(Symbol message, Object msgdata, String msg)
        {
            if (message == Command.MsgActivate)
                this.Active = true;
            else if (message == Command.MsgDeactivate)
                this.Active = false;
            else if (message == Command.MsgDisassociate)
                this.command = null;
        }

        protected void executeCommand()
        {
            if (this.command != null)
            {
                MainProgram.theApplication.startCommandInterfaceExecution();
                this.command.execute(this);
                MainProgram.theApplication.endCommandInterfaceExecution();
            }
        }

        public void componentHelp()
        {
            //This should probably be written using 
            // HelpRequested
        }

    }
}
