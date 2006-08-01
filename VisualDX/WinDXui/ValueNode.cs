// Completed 7/27/2006

using System;
using System.Collections.Generic;
using System.Text;

namespace WinDX.UI
{
    class ValueNode : NondrivenInteractorNode
    {
        protected override InteractorInstance newInteractorInstance()
        {
            ValueInstance ii;
            ii = new ValueInstance(this);

            return ii;
        }

        public ValueNode(NodeDefinition nd, Network net, int instnc)
            :
            base(nd, net, instnc)
        { }

        public override bool initialize()
        {
            DXTypeVals t = setOutputValue(1, "NULL", DXTypeVals.UndefinedType, false);
            return t == DXTypeVals.UndefinedType ? false : true;
        }
    }
}
