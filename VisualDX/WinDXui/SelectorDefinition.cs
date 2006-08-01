using System;
using System.Collections.Generic;
using System.Text;

namespace WinDX.UI
{
    class SelectorDefinition : SelectionDefinition
    {
        protected override Node newNode(Network net, int inst)
        {
            SelectorNode n = new SelectorNode(this, net, inst);
            return n;
        }

        public SelectorDefinition() { }

        public static NodeDefinition AllocateDefiniton()
        {
            return new SelectorDefinition();
        }
    }
}
