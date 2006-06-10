using System;
using System.Collections.Generic;
using System.Text;

namespace WinDX.UI
{
    class LabeledStandIn : StandIn
    {
        //private static bool ClassInitialized = false;

        protected override string getButtonLabel()
        {
            return node.LabelString;
        }

        protected LabeledStandIn(WorkSpace w, Node node) 
        : base(w, node)
        { }

        public new static StandIn AllocateStandIn(WorkSpace w, Node node)
        {
            StandIn si = new LabeledStandIn(w, node);
            si.createStandIn();
            return si;
        }

        protected override void initialize()
        {
            base.initialize();
        }

    }
}
