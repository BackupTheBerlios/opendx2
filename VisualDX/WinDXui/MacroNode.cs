using System;
using System.Collections.Generic;
using System.Text;

namespace WinDX.UI
{
    public class MacroNode : Node
    {
        public MacroNode(NodeDefinition nd, Network net, int instnc)
            : base(nd, net, instnc)
        {
            throw new Exception("Not yet implemented.");
        }

        public override void updateDefinition()
        {
            throw new Exception("Not yet implemented.");
        }

        public override bool initialize()
        {
            throw new Exception("Not yet implemented.");
        }
        public virtual bool sendValues()
        {
            return sendValues(true);
        }
        public virtual bool sendValues(bool ignoreDirty)
        {
            throw new Exception("Not yet implemented.");
        }

        public virtual void openMacro()
        {
            throw new Exception("Not yet implemented.");
        }

        /// <summary>
        /// Determine if this node is a node of the given class
        /// </summary>
        /// <param name="classname"></param>
        /// <returns></returns>
        public virtual bool IsA(Symbol classname)
        {
            throw new Exception("Not yet implemented.");
        }

        public virtual bool needsFastSort() { return true; }

        /// <summary>
        /// WebOptions is a macro.  I would like to represent it with its own
        /// Node subclass but that would require sending down the text of the
        /// macro the way the image macro is sent and it seems too cumbersome
        /// to include it in every .net file.  this->getJavaNodeName() will
        /// only be called from printAsJava and only in the case where the
        /// macro is WebOptions
        /// </summary>
        /// <returns></returns>
        public virtual bool hasJavaRepresentation()
        {
            throw new Exception("Not yet implemented.");
        }

        public virtual String getJavaNodeName() { return "WebOptionsNode"; }

        public virtual bool printInputAsJava(int input)
        {
            throw new Exception("Not yet implemented.");
        }
    }
}
