using System;
using System.Collections.Generic;
using System.Text;

namespace WinDX.UI
{
    class Ark
    {
        private Node from;
        private int fromParameter;
        private Node to;
        private int toParameter;
        private ArkStandIn arcStandIn;

        public Ark(Node fromNode, int fp, Node toNode, int tp)
        {
            arcStandIn = null;

            from = fromNode;
            fromParameter = fp;
            to = toNode;
            toParameter = tp;
            throw new Exception("Not fully implemented.");
        }

        public Node getSourceNode(ref int param)
        {
            param = fromParameter;
            return from;
        }

        public Node getDestinationNode(ref int param)
        {
            param = toParameter;
            return to;
        }

        public void setArkStandIn(ArkStandIn asi)
        {
            arcStandIn = asi;
        }

        ArkStandIn getArkStandIn()
        {
            return arcStandIn;
        }
    }
}
