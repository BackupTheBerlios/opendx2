using System;
using System.Collections.Generic;
using System.Text;

namespace WinDX.UI
{
    class SequencerDefinition : ShadowedOutputDefinition
    {
        protected override Node newNode(Network net, int instance)
        {
            String node_name = NameString;
            if (net.findNode(SymbolManager.theSymbolManager.registerSymbol(node_name), 0) != null)
            {
                ErrorDialog ed = new ErrorDialog();
                ed.post("Only one {0} is allowed in a network.", node_name);
                return null;
            }
            SequencerNode d = new SequencerNode(this, net, instance);
            return d;
        }

        public SequencerDefinition() { }

        public new static NodeDefinition AllocateDefinition()
        {
            return new SequencerDefinition();
        }

    }
}
