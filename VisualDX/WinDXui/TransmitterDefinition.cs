using System;
using System.Collections.Generic;
using System.Text;

namespace WinDX.UI
{
    class TransmitterDefinition : NodeDefinition
    {
        protected override SIAllocator getSIAllocator()
        {
            return ItalicLabeledStandIn.AllocateStandIn;
        }

        protected override Node newNode(Network net, int instance)
        {
            TransmitterNode d = new TransmitterNode(this, net, instance);
            return d;
        }

        public static new NodeDefinition AllocateDefinition()
        {
            return new TransmitterDefinition();
        }
    }
}
