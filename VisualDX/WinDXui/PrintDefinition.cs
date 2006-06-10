using System;
using System.Collections.Generic;
using System.Text;

namespace WinDX.UI
{
    class PrintDefinition : NodeDefinition
    {
        protected override Node newNode(Network net, int inst)
        {
            PrintNode n = new PrintNode(this, net, inst);
            return n;
        }

        public PrintDefinition() { }

        public new static NodeDefinition AllocateDefinition()
        {
            return new PrintDefinition();
        }
    }
}
