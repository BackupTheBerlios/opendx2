using System;
using System.Collections.Generic;
using System.Text;

namespace WinDX.UI
{
    class ReceiverNode : UniqueNameNode
    {
        public const String ClassReceiverNode = "ReceiverNode";

        public ReceiverNode(NodeDefinition nd, Network net, int instnc)
            :
            base(nd, net, instnc) { }

        public bool IsTransmitterConnected { get { throw new Exception("Not Yet Implemented"); } }
    }
}
