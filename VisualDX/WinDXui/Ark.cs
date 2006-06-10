using System;
using System.Collections.Generic;
using System.Text;

namespace WinDX.UI
{
    public class Ark
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
            from.addOutputArk(this, fp);
            to.addInputArk(this, tp);
        }

        public Node getSourceNode(out int param)
        {
            param = fromParameter;
            return from;
        }

        public Node getDestinationNode(out int param)
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
