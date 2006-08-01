using System;
using System.Collections.Generic;
using System.Text;
using System.Diagnostics;

namespace WinDX.UI
{
    class ReceiverNode : UniqueNameNode
    {
        public const String ClassReceiverNode = "ReceiverNode";
        public static bool initializing = false;

        protected override string netNodeString(string prefix)
        {
            String outputParam = outputParameterNamesString(prefix);
            return String.Format("{0} = {1};\n", outputParam, LabelString);
        }
        public override bool initialize()
        {
            String label = LabelString;
            Network net = getNetwork();
            EditorWindow editor = net.getEditor();
            if (!net.IsReadingNetwork && editor != null)
            {
                TransmitterNode tmtr = editor.getMostRecentTransmitterNode();
                if (tmtr != null)
                    label = tmtr.LabelString;
            }

            initializing = true;
            setLabelString(label);
            initializing = false;

            return true;
        }

        public ReceiverNode(NodeDefinition nd, Network net, int instnc)
            :
            base(nd, net, instnc) { }

        public override bool setLabelString(string label)
        {
            if (label == LabelString)
                return true;

            if (initializing && getNetwork().IsReadingNetwork)
                return base.setLabelString(label);

            if (!verifyRestrictedLabel(label))
                return false;

            // Skip the conflict check when reading in a newer style net since
            // there can't be any conflict in these nets.
            String conflict = null;
            if (getNetwork().IsReadingNetwork)
            {
                int net_major = getNetwork().getNetMajorVersion();
                int net_minor = getNetwork().getNetMinorVersion();
                int net_micro = getNetwork().getNetMicroVersion();

                int net_version = Utils.VersionNumber(net_major, net_minor, net_micro);
                if (net_version < Utils.VersionNumber(3, 1, 1))
                    conflict = getNetwork().nameConflictExists(this, label);
            }

            // If there is a name conflict while reading a network, it's important to try
            // to continue in spite of the conflict and fix things up later.  Reason: older
            // versions of dx allowed the name conflict and we would like to try and fix
            // things and report what happened rather than read the net incorrectly.
            if (conflict != null && getNetwork().IsReadingNetwork == false)
            {
                ErrorDialog ed = new ErrorDialog();
                ed.post("A {0} with name \"{1}\" already exists.", conflict, label);
                return false;
            }

            bool found = false;
            List<Ark> ia = getInputArks(1);
            if (ia != null && ia.Count > 0)
            {
                Ark a = ia[0];
                int dummy;
                if (a.getSourceNode(out dummy).LabelString == label)
                    found = true;
            }
            ia = null;

            if (!found)
            {
                List<Node> l = getNetwork().makeClassifiedNodeList(typeof(TransmitterNode), false);
                if (l != null && (getNetwork().IsReadingNetwork == false))
                {
                    // Before creating any Arks, check for cycles.
                    foreach (Node n in l)
                    {
                        if (n.LabelString == label)
                        {
                            Network net = getNetwork();
                            if (net.checkForCycle(n, this))
                            {
                                ErrorDialog ed = new ErrorDialog();
                                ed.post("Unable to rename Receiver \"{0}\" to \"{1}\" " +
                                    "because that would cause a cyclic connection.", LabelString,
                                    label);
                                return false;
                            }
                        }
                    }
                }
                if (l != null)
                {
                    foreach (Node n in l)
                    {
                        if (label == n.LabelString)
                        {
                            found = true;
                            new Ark(n, 1, this, 1);
                        }
                    }
                }
            }

            // There was a name conflict because earlier versions of dx were less restrictive.
            // Record the transmitter for later fixup.  When the transmitter is fixed up,
            // then we'll automatically get fixed up also.  Caveat:  if there is no transmitter
            // connected, then it's cool to refuse the name because then we're not breaking
            // anything.
            if (conflict != null)
            {
                Debug.Assert(getNetwork().IsReadingNetwork);
                if (IsTransmitterConnected == false)
                {
                    ErrorDialog ed = new ErrorDialog();
                    ed.post("A {0} with name \"{1}\" already exists.", conflict, label);
                    return false;
                }
                List<Ark> l = getInputArks(1);
                Debug.Assert(l.Count>0);
                Ark a = l[0];
                int dummy;
                TransmitterNode tn = (TransmitterNode) a.getSourceNode(out dummy);
                getNetwork().fixupTransmitter(tn);
            }
            return base.setLabelString(label);
        }

        /// <summary>
        /// Is this receiver connected to a Transmitter.
        /// </summary>
        public bool IsTransmitterConnected { get { throw new Exception("Not Yet Implemented"); } }

        /// <summary>
        /// Get the node that is connected to the Transmitter that this Receiver
        /// is receiving from.  IF there is no Transmitter for this Receiver, or 
        /// the Transmitter is not connected, return NULL, otherwise the Node.
        /// </summary>
        /// <param name="param_no"></param>
        /// <returns></returns>
        public Node getUltimateSourceNode(ref int param_no)
        {
            throw new Exception("Not Yet Implemented");
        }

        /// <summary>
        /// Switch the node from one net to another.  Look for a tranmitter to
        /// connect to.
        /// </summary>
        /// <param name="from"></param>
        /// <param name="to"></param>
        public override void switchNetwork(Network from, Network to)
        {
            throw new Exception("Not Yet Implemented");
            base.switchNetwork(from, to);
        }

        public override bool isA(Symbol classname)
        {
            throw new Exception("Not Yet Implemented");
            return base.isA(classname);
        }

        public override bool namesConflict(string his_label, string my_label, string his_classname)
        {
            throw new Exception("Not Yet Implemented");
            return base.namesConflict(his_label, my_label, his_classname);
        }
    }
}
