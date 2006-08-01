using System;
using System.Collections.Generic;
using System.Text;

namespace WinDX.UI
{
    class SelectorNode : SelectionNode
    {
        protected override InteractorInstance newInteractorInstance()
        {
            throw new Exception("Not Yet Implemented");
        }
        protected override string getInitialValueList()
        {
            throw new Exception("The method or operation is not implemented.");
        }
        protected override string getInitialStringList()
        {
            throw new Exception("The method or operation is not implemented.");
        }

        public SelectorNode(NodeDefinition nd, Network net, int instnc) : 
            base(nd, net, instnc)
        { }

        /// <summary>
        /// Deselect all current selections and make the given index
        /// the current selection.
        /// </summary>
        /// <param name="index"></param>
        /// <param name="send"></param>
        public void setSelectedOptionIndex(int index) { setSelectedOptionIndex(index, true); }
        public void setSelectedOptionIndex(int index, bool send)
        {
            throw new Exception("Not Yet Implemented");
        }

        /// <summary>
        /// If there is only one item selected, then return its index,
        /// otherwise return 0.
        /// </summary>
        /// <returns></returns>
        public int getSelectedOptionIndex() { throw new Exception("Not Yet Implemented"); }

        public override bool isA(Symbol classname)
        {
            throw new Exception("Not Yet Implemented");
            return base.isA(classname);
        }
    }
}
