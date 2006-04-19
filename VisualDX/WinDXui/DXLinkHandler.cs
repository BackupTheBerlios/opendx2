using System;
using System.Collections.Generic;
using System.Text;

namespace WinDX.UI
{
    class DXLinkHandler : LinkHandler
    {
        #region private Methods

        private static bool SaveNetwork(String c, int id, Object va)
        {
            throw new Exception("Not Yet Implemented.");
        }
        private static bool OpenNetwork(String c, int id, Object va)
        {
            throw new Exception("Not Yet Implemented.");
        }
        private static bool OpenNetworkNoReset(String c, int id, Object va)
        {
            throw new Exception("Not Yet Implemented.");
        }
        private static bool OpenConfig(String c, int id, Object va)
        {
            throw new Exception("Not Yet Implemented.");
        }
        private static bool SaveConfig(String c, int id, Object va)
        {
            throw new Exception("Not Yet Implemented.");
        }
        private static bool ResetServer(String c, int id, Object va)
        {
            throw new Exception("Not Yet Implemented.");
        }
        private static bool Version(String c, int id, Object va)
        {
            throw new Exception("Not Yet Implemented.");
        }
        private static bool SetTabValue(String c, int id, Object va)
        {
            throw new Exception("Not Yet Implemented.");
        }
        private static bool SetGlobalValue(String c, int id, Object va)
        {
            throw new Exception("Not Yet Implemented.");
        }
        private static bool Terminate(String c, int id, Object va)
        {
            throw new Exception("Not Yet Implemented.");
        }
        private static bool Disconnect(String c, int id, Object va)
        {
            throw new Exception("Not Yet Implemented.");
        }
        private static bool QueryValue(String c, int id, Object va)
        {
            throw new Exception("Not Yet Implemented.");
        }
        private static bool QueryExecution(String c, int id, Object va)
        {
            throw new Exception("Not Yet Implemented.");
        }
        private static bool ConnectToServer(String c, int id, Object va)
        {
            throw new Exception("Not Yet Implemented.");
        }
        private static bool StartServer(String c, int id, Object va)
        {
            throw new Exception("Not Yet Implemented.");
        }
        private static void SyncCB(Object clientData, int id, Object line)
        {
            throw new Exception("Not Yet Implemented.");
        }
        private static bool Sync(String c, int id, Object va)
        {
            throw new Exception("Not Yet Implemented.");
        }
        private static bool SyncExec(String c, int id, Object va)
        {
            throw new Exception("Not Yet Implemented.");
        }
        private static bool OpenControlPanel(String c, int id, Object va)
        {
            throw new Exception("Not Yet Implemented.");
        }
        private static bool CloseControlPanel(String c, int id, Object va)
        {
            throw new Exception("Not Yet Implemented.");
        }
        private static bool ResendParameters(String c, int id, Object va)
        {
            throw new Exception("Not Yet Implemented.");
        }
        private static bool SetProbePoint(String c, int id, Object va)
        {
            throw new Exception("Not Yet Implemented.");
        }
        private static bool SetInteractionMode(String c, int id, Object va)
        {
            throw new Exception("Not Yet Implemented.");
        }
        private static bool LoadMacroFile(String c, int id, Object va)
        {
            throw new Exception("Not Yet Implemented.");
        }
        private static bool LoadMacroDirectory(String c, int id, Object va)
        {
            throw new Exception("Not Yet Implemented.");
        }
        private static bool ExecOnce(String c, int id, Object va)
        {
            throw new Exception("Not Yet Implemented.");
        }
        private static bool ExecOnChange(String c, int id, Object va)
        {
            throw new Exception("Not Yet Implemented.");
        }
        private static bool EndExecution(String c, int id, Object va)
        {
            throw new Exception("Not Yet Implemented.");
        }
        private static bool EndExecOnChange(String c, int id, Object va)
        {
            throw new Exception("Not Yet Implemented.");
        }
        private static bool PopupVCR(String c, int id, Object va)
        {
            throw new Exception("Not Yet Implemented.");
        }
        private static bool OpenVPE(String c, int id, Object va)
        {
            throw new Exception("Not Yet Implemented.");
        }
        private static bool CloseVPE(String c, int id, Object va)
        {
            throw new Exception("Not Yet Implemented.");
        }
        private static bool OpenSequencer(String c, int id, Object va)
        {
            throw new Exception("Not Yet Implemented.");
        }
        private static bool CloseSequencer(String c, int id, Object va)
        {
            throw new Exception("Not Yet Implemented.");
        }
        private static bool OpenColormapEditor(String c, int id, Object va)
        {
            throw new Exception("Not Yet Implemented.");
        }
        private static bool CloseColormapEditor(String c, int id, Object va)
        {
            throw new Exception("Not Yet Implemented.");
        }
        private static bool OpenImage(String c, int id, Object va)
        {
            throw new Exception("Not Yet Implemented.");
        }
        private static bool CloseImage(String c, int id, Object va)
        {
            throw new Exception("Not Yet Implemented.");
        }
        private static bool SelectProbe(String c, int id, Object va)
        {
            throw new Exception("Not Yet Implemented.");
        }
        private static bool SequencerPlay(String c, int id, Object va)
        {
            throw new Exception("Not Yet Implemented.");
        }
        private static bool SequencerPause(String c, int id, Object va)
        {
            throw new Exception("Not Yet Implemented.");
        }
        private static bool SequencerStep(String c, int id, Object va)
        {
            throw new Exception("Not Yet Implemented.");
        }
        private static bool SequencerStop(String c, int id, Object va)
        {
            throw new Exception("Not Yet Implemented.");
        }
        private static bool SequencerPalindrome(String c, int id, Object va)
        {
            throw new Exception("Not Yet Implemented.");
        }
        private static bool SequencerLoop(String c, int id, Object va)
        {
            SequencerNode s = DXApplication.theDXApplication.network.sequencer;
            if (s != null)
            {
                DXExecCtl ctl = DXApplication.theDXApplication.getExecCtl();
                DXLinkHandler a = (DXLinkHandler)va;
                bool set = c.Contains("off");
                ctl.vcrCommand(SequencerDirection.Loop, set);
                a.stallForExecutionIfRequired();
            }
            return true;
        }

        private static bool SetHWRendering(String c, int id, Object va)
        {
            throw new Exception("Not Yet Implemented.");
        }
        private static bool SetSWRendering(String c, int id, Object va)
        {
            throw new Exception("Not Yet Implemented.");
        }
        private bool setRenderMode(String msg, int id, bool swmode)
        {
            throw new Exception("Not Yet Implemented.");
        }


        private static bool StallNTimes(Object d)
        {
            throw new Exception("Not Yet Implemented.");
        }
        private static bool StallUntil(String c, int id, Object va)
        {
            throw new Exception("Not Yet Implemented.");
        }

        //
        // These two are used to delay the handling of messages
        // until the executive is done executing.  They also serve, to
        // interleave X events with the handling of messages which
        // keeps messages from being handled consecutively.
        //
        private static bool DestallOnNoExecution(Object d)
        {
            throw new Exception("Not Yet Implemented.");
        }
        private void stallForExecutionIfRequired()
        {
            throw new Exception("Not Yet Implemented.");
        }
        #endregion

        #region private Instance Variables
        private int stallCount;	// For implementing StallNTimes().

        #endregion

        #region Public Constructor

        public DXLinkHandler(PacketIF pif)
            : base(pif)
        {
            this.addCommand("set", (Command) null);
            this.addSubCommand("set", "tab", SetTabValue);
            this.addSubCommand("set", "value", SetGlobalValue);
            this.addSubCommand("set", "probevalue", SetProbePoint);
            this.addSubCommand("set", "activeprobe", SelectProbe);

            this.addCommand("execute", (Command) null);
            this.addSubCommand("execute", "once", DXLinkHandler.ExecOnce);
            this.addSubCommand("execute", "onchange", DXLinkHandler.ExecOnChange);
            this.addSubCommand("execute", "end", DXLinkHandler.EndExecution);
            this.addSubCommand("execute", "endEOC", DXLinkHandler.EndExecOnChange);

            this.addCommand("StartServer", DXLinkHandler.StartServer);
            this.addCommand("ConnectToServer", DXLinkHandler.ConnectToServer);
            this.addCommand("disconnect", DXLinkHandler.Disconnect);
            this.addCommand("exit", DXLinkHandler.Terminate);
            this.addCommand("quit", DXLinkHandler.Terminate);

            this.addCommand("save", (Command) null);
            this.addSubCommand("save", "network", DXLinkHandler.SaveNetwork);

            this.addCommand("open", (Command) null);
            this.addSubCommand("open", "networkNoReset",
                        DXLinkHandler.OpenNetworkNoReset);
            this.addSubCommand("open", "network",
                        DXLinkHandler.OpenNetwork);
            this.addSubCommand("open", "config",
                        DXLinkHandler.OpenConfig);
            this.addSubCommand("open", "controlpanel",
                        DXLinkHandler.OpenControlPanel);
            this.addSubCommand("open", "VPE",
                        DXLinkHandler.OpenVPE);
            this.addSubCommand("open", "sequencer",
                        DXLinkHandler.OpenSequencer);
            this.addSubCommand("open", "image",
                        DXLinkHandler.OpenImage);
            this.addSubCommand("open", "colormapEditor",
                        DXLinkHandler.OpenColormapEditor);

            this.addCommand("query", (Command) null);
            this.addSubCommand("query", "value", DXLinkHandler.QueryValue);
            this.addSubCommand("query", "sync", DXLinkHandler.Sync);
            this.addSubCommand("query", "sync-exec", DXLinkHandler.SyncExec);
            this.addSubCommand("query", "execution", DXLinkHandler.QueryExecution);

            this.addCommand("close", (Command) null);
            this.addSubCommand("close", "controlpanel",
                        DXLinkHandler.CloseControlPanel);
            this.addSubCommand("close", "VPE",
                        DXLinkHandler.CloseVPE);
            this.addSubCommand("close", "colormapEditor",
                        DXLinkHandler.CloseColormapEditor);
            this.addSubCommand("close", "image",
                        DXLinkHandler.CloseImage);
            this.addSubCommand("close", "sequencer",
                        DXLinkHandler.CloseSequencer);

            this.addCommand("sequencer", (Command) null);
            this.addSubCommand("sequencer", "play", DXLinkHandler.SequencerPlay);
            this.addSubCommand("sequencer", "pause", DXLinkHandler.SequencerPause);
            this.addSubCommand("sequencer", "step", DXLinkHandler.SequencerStep);
            this.addSubCommand("sequencer", "stop", DXLinkHandler.SequencerStop);
            this.addSubCommand("sequencer", "palindrome",
                        DXLinkHandler.SequencerPalindrome);
            this.addSubCommand("sequencer", "loop", DXLinkHandler.SequencerLoop);

            this.addCommand("load", (Command) null);
            this.addSubCommand("load", "macroFile",
                        DXLinkHandler.LoadMacroFile);
            this.addSubCommand("load", "macroDirectory",
                        DXLinkHandler.LoadMacroDirectory);

            this.addCommand("$version", DXLinkHandler.Version);
            this.addCommand("resend", DXLinkHandler.ResendParameters);
            this.addCommand("interactionMode", DXLinkHandler.SetInteractionMode);
            this.addCommand("reset", DXLinkHandler.ResetServer);

            this.addCommand("save", (Command) null);
            this.addSubCommand("save", "config", DXLinkHandler.SaveConfig);

            this.addCommand("render-mode", (Command) null);
            this.addSubCommand("render-mode", "hw", DXLinkHandler.SetHWRendering);
            this.addSubCommand("render-mode", "sw", DXLinkHandler.SetSWRendering);

            //
            // As of 6/12/95, we aren't using this in DXLink, but it may come in
            // handy for fixing bugs and may be of general utility.
            //
            this.addCommand("stall", (Command) null);
            this.addSubCommand("stall", "until", DXLinkHandler.StallUntil);
        }

        #endregion
    }
}
