using System;
using System.Collections.Generic;
using System.Text;

namespace WinDX.UI
{
    class EchoDefinition : NodeDefinition
    {
        protected override Node newNode(Network net, int inst)
        {
            EchoNode n = new EchoNode(this, net, inst);
            return n;
        }

        public EchoDefinition() { }

        public new static NodeDefinition AllocateDefinition()
        {
            return new EchoDefinition();
        }
    }
}
