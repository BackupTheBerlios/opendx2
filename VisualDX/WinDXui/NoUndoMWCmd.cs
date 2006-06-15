using System;
using System.Collections.Generic;
using System.Text;

namespace WinDX.UI
{
    class NoUndoMWCmd : NoUndoCommand
    {
        public enum CmdType
        {
            Log,
            Save,
            Close,
            NextError,
            PrevError,
            ExecScript,
            Tracing,
            Memory
        }
        private MsgWin messageWindow;
        private CmdType commandType;

        public NoUndoMWCmd(String name, CommandScope scope, bool active,
            MsgWin win, CmdType comType)
            :
            base(name, scope, active)
        {
            messageWindow = win;
            commandType = comType;
        }

        public override bool doIt(CommandInterface ci)
        {
            switch (commandType)
            {
                case CmdType.Log:
                    if (messageWindow.LogFile != null)
                        messageWindow.log(null);
                    else
                        messageWindow.postLogDialog();
                    break;
                case CmdType.Save:
                    messageWindow.postSaveDialog();
                    break;
                case CmdType.Close:
                    messageWindow.Close();
                    break;
                case CmdType.NextError:
                    messageWindow.findNextError();
                    break;
                case CmdType.PrevError:
                    messageWindow.findPrevError();
                    break;
                case CmdType.Tracing:
                    messageWindow.toggleTracing();
                    break;
                case CmdType.Memory:
                    messageWindow.memoryUse();
                    break;
                default:
                    System.Diagnostics.Debug.Assert(false);
                    break;
            }
            return true;
        }
    }
}
