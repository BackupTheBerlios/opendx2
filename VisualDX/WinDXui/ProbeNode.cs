using System;
using System.Collections.Generic;
using System.Text;

namespace WinDX.UI
{
    public class ProbeNode : Node
    {
        protected override string netNodeString(string prefix)
        {
            return "";
        }
        protected override string valuesString(string prefix)
        {
            String outputParam = outputParameterNamesString(prefix);

            String str = outputParam + " = " + getOutputValueString(1) + ";\n";
            return str;
        }

        public ProbeNode(NodeDefinition nd, Network net, int instnc) 
            : base(nd, net, instnc)
        { }

        ~ProbeNode()
        {
            foreach (ImageWindow iw in getNetwork().getImageList())
            {
                iw.deleteProbe(this);
            }
        }

        public override bool initialize()
        {
            String str = NameString + "_" + InstanceNumber;
            setLabelString(str);
            return true;
        }

        public override void initializeAfterNetworkMember()
        {
            foreach (ImageWindow iw in getNetwork().getImageList())
            {
                iw.addProbe(this);
            }
        }

        public override bool setLabelString(string label)
        {
            bool result = base.setLabelString(label);
            foreach (ImageWindow iw in getNetwork().getImageList())
            {
                iw.changeProbe(this);
            }
            return result;
        }

        public Parameter getOutput() { return getOutputParameter(1); }

        public virtual void setCursorValue(int cursor, double x, double y, double z)
        {
            if (NameString == "Probe")
            {
                String str = String.Format("[{0}, {1}, {2}]", x, y, z);
                setOutputValue(1, str, DXTypeVals.VectorType, cursor == -1 ? false : true);
            }
            else
                resetValueList(cursor, false, x, y, z);
        }

        public virtual void deleteCursor(int cursor) {
            if (NameString == "Probe")
                clearOutputValue(1);
            else
                resetValueList(cursor, true, 0.0, 0.0, 0.0);
        }

        public virtual void resetValueList(int cursor, bool toDelete,
            double x, double y, double z)
        {
            String oldList = getOutputValueString(1);
            String pl, newlist;

            if (oldList == "NULL")
                pl = "{ }";
            else
                pl = oldList;

            if (toDelete)
            {
                if (pl == "{ }")
                    newlist = null;
                else if (cursor == -1)
                    newlist = DXValue.DeleteListItem(pl,
                        DXTypeVals.VectorListType, cursor);
                else
                    newlist = DXValue.DeleteListItem(pl,
                        DXTypeVals.VectorListType, cursor + 1);
            }
            else
            {
                String value = String.Format("[{0}, {1}, {2}]", x, y, z);
                if (cursor == -1)
                {
                    newlist = DXValue.AppendListItem(pl, value);
                }
                else
                {
                    newlist = DXValue.ReplaceListItem(pl, value, 
                        DXTypeVals.VectorListType, cursor + 1);
                }
            }

            if (newlist == null || newlist.Length < 4)
                setOutputValue(1, "NULL", DXTypeVals.VectorListType);
            else
                setOutputValue(1, newlist, DXTypeVals.VectorListType,
                    cursor == -1 ? false : true);
        }

        public override void switchNetwork(Network from, Network to, bool silently)
        {
            bool change_label = false;
            String name = LabelString.Substring(0, LabelString.IndexOf('_')-1);
            int instance = Int32.Parse(LabelString.Substring(LabelString.IndexOf('_')));

            if (name != null && name == NameString && instance != InstanceNumber)
            {
                change_label = true;
            }

            String new_name = "";
            
            List<Node> rnl = to.makeClassifiedNodeList(typeof(ProbeNode), false);
            if (rnl != null && !change_label)
            {
                foreach (Node n in rnl)
                {
                    if (!change_label)
                    {
                        if (n.LabelString == LabelString)
                        {
                            change_label = true;
                            break;
                        }
                    }
                }
            }

            if (change_label)
            {
                String new_label = NameString + "_" + InstanceNumber;
                if (!silently)
                {
                    InfoDialog id = new InfoDialog();
                    id.post("{0} {1} has been relabled {2}", NameString, LabelString, new_label);
                }
                setLabelString(new_label);
            }
            base.switchNetwork(from, to, silently);
        }

        public override bool isA(Symbol classname)
        {
            Symbol s = SymbolManager.theSymbolManager.registerSymbol("ProbeNode");
            if (s == classname)
                return true;
            else
                return base.isA(classname);
        }
    }
}
