using System;
using System.Collections.Generic;
using System.Text;

namespace WinDX.UI
{
    class ColormapNode : DrivenNode
    {
        public ColormapNode(NodeDefinition nd, Network net, int instnc)
            :
            base(nd, net, instnc)
        {
            throw new Exception("Not Yet Implemented");
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
