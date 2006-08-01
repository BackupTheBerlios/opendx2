using System;
using System.Collections.Generic;
using System.Text;

namespace WinDX.UI
{
    class StreaklineDefinition : NodeDefinition
    {
        protected override Node newNode(Network net, int instance)
        {
            StreaklineNode n = new StreaklineNode(this, net, instance);
            return n;
        }

        public static new NodeDefinition AllocateDefinition()
        {
            return new StreaklineDefinition();
        }

    }
}
