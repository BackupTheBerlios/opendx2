//Completed 7/27/2006

using System;
using System.Collections.Generic;
using System.Text;

namespace WinDX.UI
{
    class ValueDefinition : InteractorDefinition
    {
        protected override Node newNode(Network net, int instance)
        {
            InteractorNode n = new ValueNode(this, net, instance);
            return n;
        }

        public ValueDefinition() { }

        public static new NodeDefinition AllocateDefinition()
        {
            return new ValueDefinition();
        }
    }
}
