using System;
using System.Collections.Generic;
using System.Text;

namespace WinDX.UI
{
    class StreaklineNode : Node
    {
        public StreaklineNode(NodeDefinition nd, Network net, int instnc)
            : base(nd, net, instnc)
        {
            setInputValue(1, getModuleMessageIdString(), DXTypeVals.StringType, false);
        }

        public override int assignNewInstanceNumber()
        {
            bool isConnected = isInputConnected(1);
            int instance_number = base.assignNewInstanceNumber();

            if (!isConnected)
                setInputValue(1, getModuleMessageIdString(), DXTypeVals.StringType, false);

            return instance_number;
        }

        public override bool isA(Symbol classname)
        {
            Symbol s = SymbolManager.theSymbolManager.registerSymbol("StreaklineNode");
            if (s == classname)
                return true;
            else
                return base.isA(classname);
        }
    }
}
