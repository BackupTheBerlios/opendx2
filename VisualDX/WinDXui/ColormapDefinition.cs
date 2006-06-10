using System;
using System.Collections.Generic;
using System.Text;

namespace WinDX.UI
{
    class ColormapDefinition : DrivenDefinition
    {
        protected override Node newNode(Network net, int instance)
        {
            ColormapNode n = new ColormapNode(this, net, instance);
            return n;
        }

        public ColormapDefinition()
            : base()
        { }

        public static NodeDefinition AllocateDefinition()
        {
            return new ColormapDefinition();
        }

    }
}
