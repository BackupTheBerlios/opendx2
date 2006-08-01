using System;
using System.Collections.Generic;
using System.Text;

namespace WinDX.UI
{
    class ValueListNode : ValueNode
    {
        protected override InteractorInstance newInteractorInstance()
        {
            ValueListInstance ii;
            ii = new ValueListInstance(this);
            return ii;
        }

        public ValueListNode(NodeDefinition nd, Network net, int instnc)
            : base(nd, net, instnc)
        { }

    }
}
