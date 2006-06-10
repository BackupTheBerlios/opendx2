using System;
using System.Collections.Generic;
using System.Text;

namespace WinDX.UI
{
    public class TransmitterNode : UniqueNameNode
    {
        public const String ClassTransmitterNode = "TransmitterNode";

        private static bool initializing = false;

        protected override string netNodeString(string prefix)
        {
            String source = inputParameterNamesString(prefix);
            String str = String.Format("{0} = {1};\n", this.LabelString, source);

            return str;
        }

        public TransmitterNode(NodeDefinition nd, Network net, int instnc)
            :
            base(nd, net, instnc)
        {
        }

        public override bool initialize()
        {
            String s = String.Format("wireless_{0}", InstanceNumber);
            initializing = true;
            setLabelString(s);
            initializing = false;
            return true;
        }

        public override bool setLabelString(String label)
        {
            if (label == LabelString)
                return true;

            List<Node> rnl = this.getNetwork().makeClassifiedNodeList(typeof(ReceiverNode), false);

            if (initializing || getNetwork().IsReadingNetwork)
            {
                if (!initializing)
                {
                    //
                    // Because of an old bug (hopefully fixed in 3.1.4), we need to scan
                    // for existing receivers with the same name.  These receivers are supposed
                    // to be placed later in the .net file than the transmitter.  Network::
                    // mergeNetworks() was not connecting up transmitters and receivers properly
                    // until 3.1.4.  So this check will work around a bug.
                    //
                    Network net = this.getNetwork();
                    int net_major = net.getNetMajorVersion();
                    int net_minor = net.getNetMinorVersion();
                    int net_micro = net.getNetMicroVersion();
                    int net_version = Utils.VersionNumber(net_major, net_minor, net_micro);
                    int fixed_version = Utils.VersionNumber(3, 1, 1);
                    if (net_version < fixed_version)
                    {
                        // grab up any receivers that already have this name
                        if (rnl != null)
                        {
                            foreach (Node node in rnl)
                            {
                                ReceiverNode rn = (ReceiverNode)node;
                                if (!rn.IsTransmitterConnected &&
                                    node.LabelString == label)
                                {
                                    Network lnet = getNetwork();
                                    if (!lnet.checkForCycle(this, node))
                                    {
                                        new Ark(this, 0, node, 0);
                                    }
                                    else
                                    {
                                        WarningDialog wd = new WarningDialog();
                                        String msg = "This network contains Transmitter/Receiver " +
                                            "pair \"{0}\" which would cause a cyclic " +
                                            "connection. Executing this network will yield " +
                                            "unpredictable results until this is fixed.";
                                        wd.post(msg, LabelString);
                                        break;
                                    }
                                }
                            }
                        }
                    }
                }
                return base.setLabelString(label);
            }
            if (!verifyRestrictedLabel(label))
                return false;

            String conflict = getNetwork().nameConflictExists(this, label);
            if (conflict != null)
            {
                ErrorDialog ed = new ErrorDialog();
                ed.post("A {0} with name \"{1}\" already exists.", conflict, label);
                return false;
            }

            if (!getNetwork().IsReadingNetwork)
            {
                if (rnl != null)
                {
                    foreach (Node nd in rnl)
                    {
                        ReceiverNode rn = (ReceiverNode)nd;
                        if (!rn.IsTransmitterConnected &&
                            rn.LabelString == label)
                        {
                            if (getNetwork().checkForCycle(this, rn))
                            {
                                ErrorDialog ed = new ErrorDialog();
                                ed.post("Unable to rename Transmitter \"{0}\" to \"{1}\" because it would create a cyclic connection.",
                                    LabelString, label);
                                return false;
                            }
                        }
                    }
                }
            }

            if (!base.setLabelString(label))
                return false;

            // Rename receivers
            List<Ark> reclist = getOutputArks(0);
            foreach (Ark a in reclist)
            {
                int dummy;
                Node rcvr = a.getDestinationNode(out dummy);
                rcvr.setLabelString(label);
            }

            // grab up any receivers that already have this name
            // We've already done the check for cyclic connections.
            if (rnl != null)
            {
                foreach (Node nd in rnl)
                {
                    ReceiverNode rn = (ReceiverNode)nd;
                    if (!rn.IsTransmitterConnected &&
                        LabelString == label)
                    {
                        new Ark(this, 0, rn, 0);
                    }
                }
            }
            return true;
        }
     

        public override bool isA(Symbol classname)
        {
            Symbol s = SymbolManager.theSymbolManager.registerSymbol(ClassTransmitterNode);
            if (s == classname)
                return true;
            else
                return base.isA(classname);
        }

        public void switchNetwork(Network from, Network to) { switchNetwork(from, to, false); }
        public void switchNetwork(Network from, Network to, bool silently)
        {
            String conflict = to.nameConflictExists(this, LabelString);
            String new_name = "";
            bool name_change_required = false;
            if (conflict != null)
            {
                new_name = String.Format("wireless_{0}", InstanceNumber);
                name_change_required = true;
            }

            List<Node> rnl = to.makeClassifiedNodeList(typeof(TransmitterNode), false);
            String cp = (name_change_required ? new_name : LabelString);
            if (rnl != null)
            {
                foreach (Node n in rnl)
                {
                    ReceiverNode rn = (ReceiverNode)n;
                    if (!rn.IsTransmitterConnected &&
                        rn.LabelString == cp)
                    {
                        if (to.checkForCycle(this, rn))
                        {
                            new_name = String.Format("cyclic_connection_{0}", InstanceNumber);
                            name_change_required = true;
                            break;
                        }
                    }
                }
            }

            if (name_change_required)
            {
                if (!silently)
                {
                    InfoDialog id = new InfoDialog();
                    id.post("Transmitter {0} has been relabled {1}", LabelString, new_name);
                }
                setLabelString(new_name);
            }
            rnl = to.makeClassifiedNodeList(typeof(ReceiverNode), false);
            if (rnl != null)
            {
                foreach (Node n in rnl)
                {
                    ReceiverNode rn = (ReceiverNode)n;
                    if (!rn.IsTransmitterConnected &&
                        rn.LabelString == LabelString)
                    {
                        new Ark(this, 0, rn, 0);
                    }
                }
            }
            base.switchNetwork(from, to, silently);
        }

        public override bool namesConflict(string his_label, string my_label, string his_classname)
        {
            if (his_classname == ReceiverNode.ClassReceiverNode) return false;

            return base.namesConflict(his_label, my_label, his_classname);
        }
    }
}
