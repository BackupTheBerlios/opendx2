using System;
using System.Collections.Generic;
using System.Text;
using System.Diagnostics;

namespace WinDX.UI
{
    public class DXExecCtl
    {
        #region Private member data
        static void BGBeginMessage(Object clientData, int id, Object p)
        { throw new Exception("Not implemented"); }
        static void BGEndMessage(Object clientData, int id, Object p)
        { throw new Exception("Not implemented"); }
        static void HWBeginMessage(Object clientData, int id, Object p)
        { throw new Exception("Not implemented"); }
        static void HWEndMessage(Object clientData, int id, Object p)
        { throw new Exception("Not implemented"); }
        static void ExecComplete(Object clientData, int id, String p)
        {
            DXExecCtl ctl = DXApplication.theDXApplication.getExecCtl();
            SequencerNode sequencer = DXApplication.theDXApplication.network.sequencer;

            // During VCR executing we turn off green lights and pop up
            // the Play button ONLY when we receive "stop" command.
            if (ctl.vcrIsExecuting && p != "stop")
                return;

            ctl.endLastExecution(true);

            if (ctl.vcrIsExecuting)
            {
                if (sequencer != null)
                    sequencer.setPlayDirection(SequencerDirection.Directionless);
                ctl.vcrIsExecuting = false;
            }

            if (!ctl.inExecOnChange() && ctl.hwExecuting <= 0)
                DXApplication.theDXApplication.thisServer.notifyClients(DXApplication.MsgExecuteDone);
        }
        static void ResumeExecOnChange(Object clientData, int id, Object p)
        { throw new Exception("Not implemented"); }
        static void ResetVcrNextFrame(Object clientData, int id, Object p)
        { throw new Exception("Not implemented"); }

        void beginSingleExecution(bool update_macros)
        {
            DXApplication.theDXApplication.thisServer.notifyClients(DXApplication.MsgExecute);
            if (update_macros && inExecOnChange() && !isExecOnChangeSuspended())
                suspendExecOnChange();

            DXApplication.theDXApplication.clearErrorList();

            if (update_macros)
                updateMacros();

            isCurrentlyExecuting = true;

            DXApplication.theDXApplication.executingCmd.execute();
        }
        void endLastExecution(bool resume)
        {
            isCurrentlyExecuting = false;
            SequencerNode sequencer = DXApplication.theDXApplication.network.sequencer;
            Symbol msg = Symbol.zero;

            if (vcrIsExecuting)
            {
                if (sequencer.isStepMode())
                    vcrIsExecuting = false;
            }

            if ((resume || resumeExecOnChangeAfterExecution) &&
                (isExecOnChangeSuspended()))
            {
                resumeExecOnChange();
            }
            else if (inExecOnChange() && !isExecOnChangeSuspended())
            {
                if (hwExecuting <= 0)
                    msg = DXApplication.MsgStandBy;
            }

            // If a request to exit ExecOnChange mode was requested during an
            // execution, then do it now.
            if (endExecOnChangePending)
            {
                endExecOnChangePending = false;
                endExecOnChange();
                msg = Symbol.zero;
            }

            resumeExecOnChangeAfterExecution = false;

            // Set activation of execution dependent commands.
            DXApplication.theDXApplication.notExecutingCmd.execute();

            // Indicate the nodes that had errors.
            // FIXME: only do this if there are errors.
            DXApplication.theDXApplication.refreshErrorIndicators();

            if (msg != Symbol.zero)
                DXApplication.theDXApplication.thisServer.notifyClients(msg);
        }

        bool endExecOnChangePending;
        #endregion

        #region Protected member data
        //
        // Execution flag.
        //
        protected bool isCurrentlyExecuting;
        protected bool vcrIsExecuting;
        protected bool execOnChange;
        protected int execOnChangeSuspensions;
        protected int hwExecuting;  	// counter for HW rendering messages
        protected bool hwBusy;  		// setting of busy cursor for HW rendering 
        protected bool forceNetworkResend;
        protected bool forceParameterResend;
        protected bool resumeExecOnChangeAfterExecution;
        protected bool isExecOnChangeSuspended()
        { return this.execOnChangeSuspensions > 0; }
        #endregion

        #region Public Methods

        //
        // Constructor:
        //
        public DXExecCtl()
        {
            forceNetworkResend = true;
            forceParameterResend = true;
            execOnChange = false;
            execOnChangeSuspensions = 0;
            isCurrentlyExecuting = false;
            vcrIsExecuting = false;
            resumeExecOnChangeAfterExecution = false;
            endExecOnChangePending = false;
        }


        //
        // Enter/leave execute on change mode.
        //
        public void newConnection()
        {
            DXPacketIF p = DXApplication.theDXApplication.getPacketIF();
            Debug.Assert(p != null);
            p.setHandler(PacketIF.PacketType.INTERRUPT,
                DXExecCtl.ExecComplete,
                DXApplication.theDXApplication.getExecCtl(),
                "stop");

            // highlighting handlers for HW rendering
            hwExecuting = 0;
            hwBusy = false;
            p.setHandler(PacketIF.PacketType.INFORMATION,
                DXExecCtl.HWBeginMessage,
                this, "HW:  begin");

            p.setHandler(PacketIF.PacketType.INFORMATION,
                DXExecCtl.HWEndMessage,
                this, "HW:  end");

            p.setHandler(PacketIF.PacketType.INFORMATION,
                DXExecCtl.BGBeginMessage,
                this, "BG:  begin");

            p.setHandler(PacketIF.PacketType.INFORMATION,
                DXExecCtl.BGEndMessage,
                this, "BG:  end");

            SequencerNode sequencer = DXApplication.theDXApplication.network.sequencer;
            if (sequencer != null)
                sequencer.Transmitted = false;

            if (inExecOnChange())
            {
                updateMacros(true);
                resumeExecOnChange();
            }
            execOnChange = false;
            endLastExecution(false);

            forceNetworkResend = true;
            forceParameterResend = true;
            execOnChangeSuspensions = 0;
            isCurrentlyExecuting = false;
            vcrIsExecuting = false;
        }
        public void suspendExecOnChange()
        { throw new Exception("Not implemented"); }

        public void resumeExecOnChange()
        { throw new Exception("Not implemented"); }


        //
        // Go out of execution on change mode without terminating the current
        // graph execution.  If not current executing, then we go ahead and
        // go out of eoc mode, otherwise schedule the exit from eoc mode for
        // the end of the current graph execution (see endLastExecution()).
        // We return TRUE if we were able to go out of eoc mode now, FALSE if
        // we won't be going out until the end of the current execution.
        //
        public bool endExecOnChange()
        { throw new Exception("Not implemented"); }


        public void enableExecOnChange()
        { throw new Exception("Not implemented"); }

        public void updateMacros()
        { updateMacros(false); }
        public void updateMacros(bool force)
        {
            DXPacketIF p = DXApplication.theDXApplication.getPacketIF();
            if (p == null)
                return;

            bool forcenet = force || forceNetworkResend;
            bool forceparam = force || forceParameterResend;

            bool resume = false;

            if (inExecOnChange() && !isExecOnChangeSuspended())
            {
                suspendExecOnChange();
                resume = true;
            }

            forceNetworkResend = false;
            forceParameterResend = false;

            ProcessGroupManager pmgr = (ProcessGroupManager)
                DXApplication.theDXApplication.network.getGroupManagers()[ProcessGroupManager.ProcessGroup];

            if (pmgr != null && pmgr.IsDirty)
                pmgr.sendAssignment(ProcessGroupManager.Function.ATTACH);

            List<Network> macros = DXApplication.theDXApplication.macroList;
            foreach (Network n in macros.ToArray())
            {
                bool dirty = n.IsDirty;
                if (forcenet || dirty)
                    n.sendNetwork();
                if (forceparam || dirty)
                    n.sendValues(forceparam);
            }

            Network n1 = DXApplication.theDXApplication.network;
            if (forcenet || n1.IsDirty)
                n1.sendNetwork();
            if (forceparam || n1.IsDirty)
                n1.sendValues(forceparam);

            SequencerNode sequencer = n1.sequencer;
            if (sequencer != null && (force || !sequencer.Transmitted))
                vcrTransmit();

            if (resume)
                resumeExecOnChange();
        }

        public void executeOnce()
        {
            DXPacketIF p = DXApplication.theDXApplication.getPacketIF();
            if (p == null)
                return;

            beginSingleExecution(true);
            String s = DXApplication.theDXApplication.network.NameString;
            s += "();\n";
            p.send(PacketIF.PacketType.FOREGROUND, s, DXExecCtl.ExecComplete, null);
        }


        public bool inExecOnChange()
        { return this.execOnChange; }
        public bool isExecuting()
        { return this.isCurrentlyExecuting; }
        public bool isVcrExecuting()
        { return this.vcrIsExecuting; }
        public bool assignmentRequiresExecution()
        { return !this.isVcrExecuting() && !this.inExecOnChange(); }

        //
        // Functions called by the Sequencer.
        //
        public void vcrFrameSet(String command)
        { throw new Exception("Not implemented"); }
        public void vcrTransmit()
        { throw new Exception("Not implemented"); }
        public void vcrExecute(int action)
        { throw new Exception("Not implemented"); }
        public void vcrCommand(SequencerDirection action, bool state)
        { throw new Exception("Not implemented"); }


        //
        // Will take you out of execute on change if in it, and
        // terminate the current execution.
        public void terminateExecution()
        {
            if (!isCurrentlyExecuting && !execOnChange)
                return;

            if (vcrIsExecuting)
            {
                vcrIsExecuting = false;
                vcrCommand(SequencerDirection.Pause, false);
            }

            Symbol msg;
            DXPacketIF p = DXApplication.theDXApplication.getPacketIF();
            if (p == null)
            {
                msg = DXApplication.MsgExecuteDone;
                DXApplication.theDXApplication.notExecutingCmd.execute();
            }
            else
            {
                msg = Symbol.zero;
                p.send(PacketIF.PacketType.INTERRUPT);
                p.send(PacketIF.PacketType.FOREGROUND, "Executive(\"nop\");",
                    DXExecCtl.ExecComplete, null);
                p.sendImmediate("sync");
                DXApplication.theDXApplication.executeOnChangeCmd.activate();
            }
            execOnChange = false;
            isCurrentlyExecuting = false;
            if (msg != Symbol.zero)
                DXApplication.theDXApplication.thisServer.notifyClients(msg);
        }
        public void updateMacro(Network n)
        { throw new Exception("Not implemented"); }

        //
        // This is used to force networks and parameters to be resent
        // after a reset.
        //
        public void forceFullResend()
        {
            forceNetworkResend = true;
            forceParameterResend = true;
            GroupManager pmgr =
                DXApplication.theDXApplication.network.getGroupManagers()[ProcessGroupManager.ProcessGroup];
            if (pmgr != null) pmgr.setDirty();

            SequencerNode sequencer = DXApplication.theDXApplication.network.sequencer;
            if (sequencer != null)
                sequencer.Transmitted = false;
        }


        #endregion
    }
}
