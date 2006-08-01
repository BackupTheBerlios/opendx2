using System;
using System.Collections.Generic;
using System.Text;

namespace WinDX.UI
{
    class ItalicLabeledStandIn : LabeledStandIn
    {
        protected ItalicLabeledStandIn(WorkSpace w, Node n)
            :
            base(w, n)
        { }

        public static new StandIn AllocateStandIn(WorkSpace w, Node n)
        {
            StandIn si = new ItalicLabeledStandIn(w, n);
            si.createStandIn();
            return si;
        }

        protected override void initialize()
        {
            // set up resources.
            base.initialize();
        }

        public override string getPostScriptLabelFont()
        {
            return "Helvetica-Oblique";
        }

        protected override string getButtonLabelFont()
        {
            return "big_oblique";
        }
    }
}
