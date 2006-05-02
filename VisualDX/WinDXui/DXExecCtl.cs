using System;
using System.Collections.Generic;
using System.Text;

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
        static void ExecComplete(Object clientData, int id, Object p)
        { throw new Exception("Not implemented"); }
        static void ResumeExecOnChange(Object clientData, int id, Object p)
        { throw new Exception("Not implemented"); }
        static void ResetVcrNextFrame(Object clientData, int id, Object p)
        { throw new Exception("Not implemented"); }

        void beginSingleExecution(bool update_macros)
        { throw new Exception("Not implemented"); }
        void endLastExecution(bool resume)
        { throw new Exception("Not implemented"); }

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
        DXExecCtl() { throw new Exception("Not implemented"); }


        //
        // Enter/leave execute on change mode.
        //
        public void newConnection()
        { throw new Exception("Not implemented"); }
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

        public void updateMacros(bool force)
        { throw new Exception("Not implemented"); }

        public void executeOnce()
        { throw new Exception("Not implemented"); }


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
        { throw new Exception("Not implemented"); }
        public void updateMacro(Network n)
        { throw new Exception("Not implemented"); }

        //
        // This is used to force networks and parameters to be resent
        // after a reset.
        //
        public void forceFullResend()
        { throw new Exception("Not implemented"); }


        #endregion
    }
}
