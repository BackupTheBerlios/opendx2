using System;
using System.Collections.Generic;
using System.Text;

namespace WinDX.UI
{
    class ReceiverDefinition : NodeDefinition
    {
        protected override SIAllocator getSIAllocator()
        {
            return ItalicLabeledStandIn.AllocateStandIn;
        }

        protected override Node newNode(Network net, int instance)
        {
            ReceiverNode d = new ReceiverNode(this, net, instance);
            return d;
        }

        public override void finishDefinition()
        {
            base.finishDefinition();

            foreach (ParameterDefinition pd in outputDefs)
            {
                pd.setWriteableCacheability(false);
                pd.setDefaultCacheability(Cacheability.OutputNotCached);
            }
        }

        public static new NodeDefinition AllocateDefinition()
        {
            return new ReceiverDefinition();
        }

    }
}
