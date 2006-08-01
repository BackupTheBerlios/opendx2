// Completed 7/27/2006

using System;
using System.Collections.Generic;
using System.Text;

namespace WinDX.UI
{
    class ResetDefinition : ToggleDefinition
    {
        protected override Node newNode(Network net, int instance)
        {
            ResetNode n = new ResetNode(this, net, instance);
            return n;
        }

        public ResetDefinition() { }

        public static new NodeDefinition AllocateDefinition()
        {
            return new ResetDefinition();
        }
    }
}
