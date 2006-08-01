// Completed 7/27/2006

using System;
using System.Collections.Generic;
using System.Text;

namespace WinDX.UI
{
    class VectorListDefinition : ScalarListDefinition
    {
        protected override Node newNode(Network net, int instance)
        {
            ScalarListNode n = new ScalarListNode(this, net, instance, true, 3);
            return n;
        }

        public VectorListDefinition() { }

        public static new NodeDefinition AllocateDefinition()
        {
            return new VectorListDefinition();
        }
    }
}
