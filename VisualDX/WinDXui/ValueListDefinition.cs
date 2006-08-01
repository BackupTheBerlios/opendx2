// Completed 7/27/2006

using System;
using System.Collections.Generic;
using System.Text;

namespace WinDX.UI
{
    class ValueListDefinition : ValueDefinition
    {
        protected override Node newNode(Network net, int instance)
        {
            InteractorNode n = new ValueListNode(this, net, instance);
            return n;
        }

        public ValueListDefinition() { }

        public static new NodeDefinition AllocateDefinition()
        {
            return new ValueListDefinition();
        }
    }
}
