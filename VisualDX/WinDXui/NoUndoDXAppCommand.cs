using System;
using System.Collections.Generic;
using System.Text;
using System.Diagnostics;

namespace WinDX.UI
{
    class NoUndoDXAppCommand : NoUndoCommand
    {
        protected DXApplication application;
        protected DXApplication.CommandType commandType;

        public NoUndoDXAppCommand(String name, CommandScope scope,
            bool active, DXApplication app, DXApplication.CommandType comType)
            : base(name, scope, active)
        {
            this.commandType = comType;
            this.application = app;
        }

        public override bool doIt(CommandInterface ci)
        {
            bool ret=false;
            SequencerNode seq_node = null;

            Debug.Assert(application != null);

            switch (commandType)
            {
                case DXApplication.CommandType.StartServer:
                    ret = application.postStartServerDialog();
                    break;
                case DXApplication.CommandType.ResetServer:
                    ret = application.resetServer();
                    break;
                case DXApplication.CommandType.ExecuteOnce:
                    application.getExecCtl().executeOnce();
                    break;
                case DXApplication.CommandType.ExecuteOnChange:
                    application.getExecCtl().enableExecOnChange();
                    break;
                case DXApplication.CommandType.EndExecution:
                    application.getExecCtl().terminateExecution();
                    break;
                case DXApplication.CommandType.OpenNetwork:
                    application.postOpenNetworkDialog();
                    break;
                case DXApplication.CommandType.LoadMacro:
                    application.postLoadMacroDialog();
                    break;
                case DXApplication.CommandType.AssignProcessGroup:
                    application.postProcessGroupAssignDialog();
                    break;
                case DXApplication.CommandType.OpenAllColormaps:
                    if (application.network == null)
                        ret = false;
                    else
                        application.network.openColormap(true);
                    break;
                case DXApplication.CommandType.OpenSequencer:
                    Debug.Assert(application.network != null);
                    seq_node = application.network.sequencer;
                    if (seq_node == null)
                        ret = false;
                    else
                    {
                        seq_node.openDefaultWindow(application.getRootForm());
                        ret = true;
                    }
                    break;
                case DXApplication.CommandType.OpenMessageWindow:
                    application.MessageWindow.Show();
                    ret = true;
                    break;
                case DXApplication.CommandType.ToggleInfoEnabled:
                    application.enableInfo(application.isInfoEnabled());
                    break;
                case DXApplication.CommandType.ToggleWarningEnabled:
                    application.enableWarning(application.isWarningEnabled());
                    break;
                case DXApplication.CommandType.ToggleErrorEnabled:
                    application.enableError(application.isErrorEnabled());
                    break;
                case DXApplication.CommandType.LoadUserMDF:
                    application.postLoadMDFDialog();
                    ret = true;
                    break;
                case DXApplication.CommandType.HelpOnManual:
                    application.helpOn("OnManual");
                    ret = true;
                    break;
                case DXApplication.CommandType.HelpOnHelp:
                    application.helpOn("OnHelp");
                    ret = true;
                    break;
                default:
                    Debug.Assert(false);
                    break;
            }
            return ret;
        }

        public override void activate()
        {
            bool connected = (application.getPacketIF() != null);

            Debug.Assert(application != null);
            bool enabled = true;

            switch (commandType)
            {
                case DXApplication.CommandType.ExecuteOnce:
                case DXApplication.CommandType.ExecuteOnChange:
                case DXApplication.CommandType.EndExecution:
                    if (!connected) enabled = false;
                    break;
            }
            if (enabled)
                base.activate();
        }

    }
}
