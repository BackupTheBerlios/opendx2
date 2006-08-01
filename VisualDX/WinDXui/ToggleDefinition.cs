using System;
using System.Collections.Generic;
using System.Text;

namespace WinDX.UI
{
    class ToggleDefinition : InteractorDefinition
    {
        protected override Node newNode(Network net, int instance)
        {
            ToggleNode n = new ToggleNode(this, net, instance);
            return n;
        }

        public ToggleDefinition() { }

        public static new NodeDefinition AllocateDefinition()
        {
            return new ToggleDefinition();
        }
    }
}
