using System;
using System.Collections.Generic;
using System.Text;

namespace WinDX.UI
{
    public class ShadowedOutputNode : DrivenNode
    {
        public ShadowedOutputNode(NodeDefinition nd, Network net, int instc)
            : base(nd, net, instc)
        {
        }

        protected override int handleNodeMsgInfo(string line)
        {
            throw new Exception("The method or operation is not implemented.");
        }
        protected override void reflectStateChange(bool unmanage)
        {
            throw new Exception("The method or operation is not implemented.");
        }
    }
}
