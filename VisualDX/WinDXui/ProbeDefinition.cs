using System;
using System.Collections.Generic;
using System.Text;

namespace WinDX.UI
{
    class ProbeDefinition : NodeDefinition
    {
        protected override SIAllocator getSIAllocator()
        {
            return LabeledStandIn.AllocateStandIn;
        }

        protected override Node newNode(Network net, int instance)
        {
            return new ProbeNode(this, net, instance);
        }

        public ProbeDefinition() : base()
        { }

        public new static NodeDefinition AllocateDefinition()
        {
            return new ProbeDefinition();
        }

        public override bool IsAllowedInMacro()
        {
            return false;
        }
    }
}
