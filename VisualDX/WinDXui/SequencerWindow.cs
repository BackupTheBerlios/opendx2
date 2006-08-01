using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;

namespace WinDX.UI
{
    class SequencerWindow : DXWindow
    {
        private SequencerNode node;
        private bool handlingStateChange;

        protected override Control createWorkArea(Form parent)
        {
            throw new Exception("The method or operation is not implemented.");
        }

        protected void disableFrameControl()
        {
            throw new Exception("Not Yet Implemented");
        }
        protected void enableFrameControl()
        {
            throw new Exception("Not Yet Implemented");
        }

        protected virtual void handleStateChange(bool unmanage)
        {
            throw new Exception("Not Yet Implemented");
        }

        protected override void beginExecution()
        {
            throw new Exception("Not Yet Implemented");
            base.beginExecution();
        }

        protected override void standBy()
        {
            throw new Exception("Not Yet Implemented");
            base.standBy();
        }

        protected override void endExecution()
        {
            throw new Exception("Not Yet Implemented");
            base.endExecution();
        }

        public SequencerWindow(SequencerNode node)
            :
            base("sequencerWindow", false, false)
        {
            throw new Exception("Not Yet Implemented");
        }

        public void mapRaise()
        {
            throw new Exception("Not Yet Implemented");
        }
        public void reset()
        {
            throw new Exception("Not Yet Implemented");
        }

        public override void setStartup()
        {
            throw new Exception("Not Yet Implemented");
            base.setStartup();
        }

        /// <summary>
        /// Set the buttons that indicate which way the sequencer is playing.
        /// </summary>
        /// <param name="dir"></param>
        public void setPlayDirection(SequencerDirection dir)
        {
            throw new Exception("Not Yet Implemented");
        }


    }
}
