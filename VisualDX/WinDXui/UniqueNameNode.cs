// Completed 5/27/2006

using System;
using System.Collections.Generic;
using System.Text;

namespace WinDX.UI
{
    public class UniqueNameNode : Node
    {
        public const String ClassUniqueNameNode = "UniqueNameNode";

        protected UniqueNameNode(NodeDefinition nd, Network net, int inst)
            :
            base(nd, net, inst) { }

        public override bool isA(Symbol classname)
        {
            Symbol s = SymbolManager.theSymbolManager.registerSymbol(ClassUniqueNameNode);
            if (s == classname)
                return true;
            else
                return base.isA(classname);
        }

        public String UniqueName
        {
            get
            {
                return LabelString;
            }
        }

        public virtual bool namesConflict(String his_label,
            String my_label, String his_classname)
        {
            return (his_label == my_label);
        }

        public override bool needsFastSort()
        {
            return true;
        }
    }
}
