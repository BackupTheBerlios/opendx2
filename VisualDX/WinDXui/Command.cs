using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Reflection;
using System.Text;

namespace WinDX.UI
{
    /// <summary>
    /// I've worked through this one.
    /// </summary>
    abstract class Command
    {
        private static readonly bool CommandClassInitialized;
        private String name;
        bool active = false;
        private Server thisServer = null;

        /// <summary>
        /// Set to true if command supports undo and implement functions.
        /// </summary>
        protected bool hasUndo = false;

        protected List<Command> activateCmds = new List<Command>();
        protected List<Command> deactivateCmds = new List<Command>();
        protected List<Command> autoActivators = new List<Command>();
        protected List<CommandScope> scopeList = new List<CommandScope>();


        /// <summary>
        /// Notification messages.
        /// </summary>
        public static readonly Symbol MsgActivate;
        public static readonly Symbol MsgDeactivate;
        public static readonly Symbol MsgDisassociate;
        public static readonly Symbol MsgBeginExecuting;
        public static readonly Symbol MsgEndExecuting;

        static Command()
        {

            if (!CommandClassInitialized)
            {
                if (MainProgram.theSymbolManager == null)
                {
                    throw new Exception("theSymbolManager not initialized");
                }

                MsgActivate = MainProgram.theSymbolManager.registerSymbol("Activate");
                MsgDeactivate = MainProgram.theSymbolManager.registerSymbol("Deactivate");
                MsgDisassociate = MainProgram.theSymbolManager.registerSymbol("Disassociate");
                MsgBeginExecuting = MainProgram.theSymbolManager.registerSymbol("BeginExecuting");
                MsgEndExecuting = MainProgram.theSymbolManager.registerSymbol("EndExecuting");

                CommandClassInitialized = true;
            }

        }

        public Command(String name, CommandScope scope, bool active)
        {
            if (name == null)
            {
                StackFrame stackFrame = new StackFrame();
                MethodBase methodBase = stackFrame.GetMethod();
                throw new Exception(string.Format("{0}: invalid arg", methodBase));
            }

            this.name = name;
            this.active = active;
            this.hasUndo = true;
            thisServer = new Server();

            if (scope != null)
            {
                scopeList.Add(scope);
            }

        }

        public virtual bool registerClient(IClient DXinterface)
        {
            if (DXinterface == null)
            {
                StackFrame stackFrame = new StackFrame();
                MethodBase methodBase = stackFrame.GetMethod();
                throw new Exception(string.Format("{0}: invalid arg", methodBase));
            }
            bool result = thisServer.registerClient(DXinterface);
            if (result)
            {
                if (active)
                {
                    DXinterface.notify(MsgActivate);
                }
                else
                {
                    DXinterface.notify(MsgDeactivate);
                }
            }
            return result;
        }

        public virtual void activate()
        {
            active = true;
            thisServer.notifyClients(MsgActivate);
        }

        public virtual void deactivate(String reason)
        {
            active = false;
            thisServer.notifyClients(MsgDeactivate, null, reason);
        }

        public bool registerScope(CommandScope scope)
        {
            if (scope == null)
            {
                StackFrame stackFrame = new StackFrame();
                MethodBase methodBase = stackFrame.GetMethod();
                throw new Exception(string.Format("{0}: invalid arg", methodBase));
            }

            if (scopeList.Contains(scope))
            {
                return false;
            }
            else
            {
                scopeList.Add(scope);
            }
            return true;
        }

        public bool unregisterScope(CommandScope scope)
        {
            if (!scopeList.Contains(scope))
            {
                return false;
            }

            return scopeList.Remove(scope);
        }

        public virtual bool execute(CommandInterface ci)
        {
            bool result;

            if (!active)
                return false;

            if (MainProgram.theApplication == null)
            {
                StackFrame stackFrame = new StackFrame();
                MethodBase methodBase = stackFrame.GetMethod();
                throw new Exception(string.Format("{0}: invalid arg", methodBase));
            }

            MainProgram.theApplication.setBusyCursor(true);
            if (doIt(ci))
            {
                foreach (CommandScope scope in scopeList)
                {
                    if (scope.getUndoCommand() != null)
                    {
                        if (hasUndo)
                        {
                            scope.setLastCommand(this);
                            scope.getUndoCommand().activate();
                        }
                        else
                        {
                            scope.setLastCommand(null);
                            scope.getUndoCommand().deactivate(null);
                        }
                    }
                }
                foreach (Command c in activateCmds)
                {
                    c.activate();
                }
                foreach (Command c in deactivateCmds)
                {
                    c.deactivate(null);
                }
                result = true;
            }
            else
                result = false;

            MainProgram.theApplication.setBusyCursor(false);

            return result;
        }

        public virtual bool execute()
        {
            return this.execute(null);
        }

        public bool undo()
        {
            if (undoIt())
            {
                foreach (CommandScope scope in scopeList)
                {
                    Command c = scope.getUndoCommand();
                    if (c != null)
                        c.deactivate(null);
                }
                return true;
            }
            return false;
        }

        public void autoActivate(Command c)
        {
            activateCmds.Add(c);
            if (deactivateCmds.Contains(c))
                deactivateCmds.Remove(c);
            c.addActivator(this);
        }

        public void autoDeactivate(Command c)
        {
            deactivateCmds.Add(c);
            if (activateCmds.Contains(c))
                activateCmds.Remove(c);
            c.removeActivator(this);
        }

        public void addActivator(Command c)
        {
            autoActivators.Add(c);
        }

        public void removeActivator(Command c)
        {
            autoActivators.Remove(c);
        }

        public bool isActive()
        {
            return active;
        }

        public bool canUndo()
        {
            return hasUndo;
        }

        public String getName()
        {
            return name;
        }

        public abstract bool doIt(CommandInterface ci);
        public abstract bool undoIt();

    }
}
