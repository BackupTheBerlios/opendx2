using System;
using System.Collections.Generic;
using System.Text;
using System.Diagnostics;

namespace WinDX.UI
{
    public class PickNode : ProbeNode
    {
        private const int PICKNAME = 1;
        private const int PICKFROM = 2;
        private const int PICKPTS = 3;
        private const int PICKINDEX = 4;

        protected override string netNodeString(string prefix)
        {
            return nodeNetNodeString(prefix);
        }
        protected override string valuesString(string prefix)
        {
            return nodeValuesString(prefix);
        }
        protected void incrementIndex()
        {
            if (isInputDefaulting(PICKINDEX))
                setInputValue(PICKINDEX, "0");
            else
            {
                String s = getInputValueString(PICKINDEX);
                int i = Int32.Parse(s);
                i++;
                setInputValueQuietly(PICKINDEX, i.ToString(), DXTypeVals.UndefinedType);
            }
        }

        public PickNode(NodeDefinition nd, Network net, int instnc)
            :
            base(nd, net, instnc)
        { }

        ~PickNode()
        {
            foreach (ImageWindow iw in getNetwork().getImageList())
                iw.deletePick(this);
        }

        public override bool initialize()
        {
            String str = NameString + "_" + InstanceNumber;
            setLabelString(str);

            setInputValue(PICKNAME, LabelString, DXTypeVals.UndefinedType, false);
            return true;
        }
        public override void initializeAfterNetworkMember()
        {
            foreach (ImageWindow iw in getNetwork().getImageList())
                iw.addPick(this);
        }

        public override bool setLabelString(string label)
        {
            bool result = nodeSetLabelString(label);
            foreach (ImageWindow iw in getNetwork().getImageList())
            {
                iw.changePick(this);
            }
            return result;
        }

        public override void setCursorValue(int cursor, double x, double y, double z)
        {
            String value = getInputValueString(PICKPTS);

            this.incrementIndex();

            String s = String.Format("[{0}, {1}]", x, y);
            if (isInputDefaulting(PICKPTS) ||
                value == null || value == "NULL" || value.Length == 0)
            {
                String newVal = "{" + s + "}";
                setInputValue(PICKPTS, newVal);
            }
            else if (cursor == -1)
            {
                String newVal = value.Substring(0, value.IndexOf('}'));
                newVal += "," + s + "}";
                setInputValue(PICKPTS, newVal);
            }
            else
            {
                // There was code here in the C++ version, but I don't
                // believe it would ever get here.
                Debug.Assert(false);
            }
        }

        public void resetCursor() {
            if (isInputDefaulting(PICKPTS))
                return;
            String v = getInputValueString(PICKPTS);
            if (v.Length == 0 || v == "NULL")
                return;
            incrementIndex();
            setInputValueQuietly(PICKPTS, "NULL");
        }

        public void pickFrom(Node n)
        {
            if (n != null)
            {
                ImageNode imn = (ImageNode)n;
                setInputValueQuietly(PICKFROM, imn.getPickIdentifier());
            }
            else
            {
                setInputValueQuietly(PICKFROM, "NULL");
                setInputValueQuietly(PICKPTS, "NULL");
            }
        }

        public override bool isA(Symbol classname)
        {
            Symbol s = SymbolManager.theSymbolManager.registerSymbol("PickNode");
            if (s == classname)
                return true;
            else
                return base.isA(classname);
        }

        public override bool hasJavaRepresentation() { return true; }
        public override string getJavaNodeName() { return "PickNode"; }
    }
}
