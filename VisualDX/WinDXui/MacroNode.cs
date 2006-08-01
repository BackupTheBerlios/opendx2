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
        }
        ~MacroNode()
        {
            MacroDefinition d = (MacroDefinition)Definition;
            d.dereference(this);
        }

        public override bool initialize()
        {
            MacroDefinition d = (MacroDefinition)Definition;
            d.reference(this);

            base.initialize();
            return true;
        }

        public override bool sendValues()
        {
            return sendValues(true);
        }
        public override bool sendValues(bool ignoreDirty)
        {
            MacroDefinition md = (MacroDefinition)Definition;
            md.updateServer();
            return base.sendValues(ignoreDirty);
        }

        public virtual void openMacro()
        {
            MacroDefinition md = (MacroDefinition)Definition;
            md.openMacro();
        }

        /// <summary>
        /// Determine if this node is a node of the given class
        /// </summary>
        /// <param name="classname"></param>
        /// <returns></returns>
        public virtual bool IsA(Symbol classname)
        {
            Symbol s = SymbolManager.theSymbolManager.registerSymbol("MacroNode");
            if (s == classname)
                return true;
            else
                return base.isA(classname);
        }

        public override bool needsFastSort() { return true; }

        /// <summary>
        /// WebOptions is a macro.  I would like to represent it with its own
        /// Node subclass but that would require sending down the text of the
        /// macro the way the image macro is sent and it seems too cumbersome
        /// to include it in every .net file.  this->getJavaNodeName() will
        /// only be called from printAsJava and only in the case where the
        /// macro is WebOptions
        /// </summary>
        /// <returns></returns>
        public override bool hasJavaRepresentation()
        {
            throw new Exception("Not yet implemented.");
        }

        public override String getJavaNodeName() { return "WebOptionsNode"; }

        public override bool printInputAsJava(int input)
        {
            throw new Exception("Not yet implemented.");
        }
    }
}
