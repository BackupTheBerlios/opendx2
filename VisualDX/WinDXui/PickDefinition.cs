using System;
using System.Collections.Generic;
using System.Text;

namespace WinDX.UI
{
    class PickDefinition : ProbeDefinition
    {
        protected override Node newNode(Network net)
        {
            // instance = -1
            return new PickNode(this, net, -1);
        }
        protected override Node newNode(Network net, int instance)
        {
            return new PickNode(this, net, instance);
        }

        public PickDefinition() : base() { }

        public new static NodeDefinition AllocateDefinition()
        {
            return new PickDefinition();
        }

        public override bool IsAllowedInMacro()
        {
            return false;
        }

    }
}
