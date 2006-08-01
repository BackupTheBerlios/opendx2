// Completed 7/26/2006

using System;
using System.Collections.Generic;
using System.Text;

namespace WinDX.UI
{
    class InteractorStandIn : StandIn
    {
        protected InteractorStandIn(WorkSpace w, Node n) : base(w, n) { }

        public static new StandIn AllocateStandIn(WorkSpace w, Node n)
        {
            StandIn si = new InteractorStandIn(w, n);
            si.createStandIn();
            return si;
        }

        protected override void handleSelectionChange(bool select)
        {
            Network net = node.getNetwork();
            for (int i = 0; i<net.getPanelCount(); i++)
            {
                ControlPanel cp = net.getPanelByIndex(i);
                cp.handleNodeStatusChange(node, select ?
                    Node.NodeStatusChange.NodeSelected :
                    Node.NodeStatusChange.NodeDeselected);
            }
            base.handleSelectionChange(select);
        }
    }
}
