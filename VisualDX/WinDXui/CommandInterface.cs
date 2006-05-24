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
    public class CommandInterface : IClient
    {
        protected Command command;
        private Object localData;
        private ToolStripMenuItem menuItem;

        public Object LocalData
        {
            get { return localData; }
            set { localData = value; }
        }

        protected CommandInterface(String name)
        {
            throw new Exception("CommandInteface requires a command.");
        }

        public CommandInterface(String name, Command command, ToolStripMenuItem ctl)
        {
            if (command == null)
            {
                StackFrame stackFrame = new StackFrame();
                MethodBase methodBase = stackFrame.GetMethod();
                throw new Exception(string.Format("{0}: invalid arg", methodBase));
            }

            this.name = name;
            this.command = command;
            this.menuItem = ctl;
            command.registerClient(this);
        }

        private bool active;
        private String name;

        public bool Active
        {
            get
            {
                if (menuItem != null) return menuItem.Enabled;
                else return false;
            }
            set { if(menuItem != null) menuItem.Enabled = value; }
        }
	

        public virtual void notify(Symbol message)
        {
            notify(message, null, null);
        }

        public virtual void notify(Symbol message, String msgdata)
        {
            notify(message, msgdata, null);
        }

        public virtual void notify(Symbol message, String msgdata, String msg)
        {
            if (message == Command.MsgActivate)
                this.Active = true;
            else if (message == Command.MsgDeactivate)
                this.Active = false;
            else if (message == Command.MsgDisassociate)
            {
                if (menuItem != null)
                    menuItem.Click -= command.executeEvent;
                this.command = null;
            }
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
