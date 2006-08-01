// Completed 7/27/2006

using System;
using System.Collections.Generic;
using System.Text;

namespace WinDX.UI
{
    class FileSelectorDefinition : ValueDefinition
    {
        protected override Node newNode(Network net, int instance)
        {
            InteractorNode n = new FileSelectorNode(this, net, instance);
            return n;
        }

        public FileSelectorDefinition() { }

        public static new NodeDefinition AllocateDefinition()
        {
            return new FileSelectorDefinition();
        }
    }
}
