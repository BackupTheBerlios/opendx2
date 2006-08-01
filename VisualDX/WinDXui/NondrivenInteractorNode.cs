using System;
using System.Collections.Generic;
using System.Text;
using System.Diagnostics;

namespace WinDX.UI
{
    class NondrivenInteractorNode : InteractorNode
    {
        protected override bool hasModuleMessageProtocol()
        {
            return false;
        }

        protected override bool expectingModuleMessage()
        {
            return false;
        }

        protected override int getShadowingInput(int output_index)
        {
            return 0;
        }

        protected override int handleNodeMsgInfo(String line)
        {
            Debug.Assert(false);
            return 0;
        }
        protected override int handleInteractorMsgInfo(String line)
        {
            Debug.Assert(false);
            return 0;
        }

        public NondrivenInteractorNode(NodeDefinition nd, Network net, int instnc)
            : base(nd, net, instnc)
        { }

        public int assignNewInstanceNumber()
        {
            return base.assignNewInstanceNumber();
        }

        public override bool IsDataDriven
        {
            get
            {
                return false;
            }
        }
    }
}
