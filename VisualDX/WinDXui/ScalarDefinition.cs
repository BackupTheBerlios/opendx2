// Completed 7/26/2006

using System;
using System.Collections.Generic;
using System.Text;

namespace WinDX.UI
{
    class ScalarDefinition :InteractorDefinition
    {
        protected override Node newNode(Network net, int inst)
        {
            ScalarNode n = new ScalarNode(this, net, inst);
            return n;
        }

        public ScalarDefinition() { }

        public static new NodeDefinition AllocateDefinition()
        {
            return new ScalarDefinition();
        }

    }
}
