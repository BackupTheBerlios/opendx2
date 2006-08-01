using System;
using System.Collections.Generic;
using System.Text;

namespace WinDX.UI
{
    class DisplayDefinition : DrivenDefinition
    {
        public override Node createNewNode(Network net)
        {
            return createNewNode(net, -1);
        }
        protected override Node newNode(Network net, int instance)
        {
            DisplayNode d = new DisplayNode(this, net, instance);
            return d;
        }

        public DisplayDefinition()
            : base()
        { }

        public new static NodeDefinition AllocateDefinition()
        {
            return new DisplayDefinition();
        }

        public override bool IsAllowedInMacro()
        {
            return true;
        }
    }
}
