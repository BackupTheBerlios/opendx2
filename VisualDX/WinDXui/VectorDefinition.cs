// Completed 7/27/2006

using System;
using System.Collections.Generic;
using System.Text;

namespace WinDX.UI
{
    class VectorDefinition : ScalarDefinition
    {
        protected override Node newNode(Network net, int inst)
        {
            ScalarNode n = new ScalarNode(this, net, inst, true, 3);
            return n;
        }

        public VectorDefinition() { }

        public static new NodeDefinition AllocateDefinition()
        {
            return new VectorDefinition();
        }
    }
}
