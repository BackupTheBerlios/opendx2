// Completed 7/26/2006

using System;
using System.Collections.Generic;
using System.Text;

namespace WinDX.UI
{
    class ScalarListDefinition : ScalarDefinition
    {
        protected override Node newNode(Network net, int instance)
        {
            ScalarListNode n = new ScalarListNode(this, net, instance, false, 1);
            return n;
        }

        public ScalarListDefinition() { }

        public static new NodeDefinition AllocateDefinition()
        {
            return new ScalarListDefinition();
        }
    }
}
