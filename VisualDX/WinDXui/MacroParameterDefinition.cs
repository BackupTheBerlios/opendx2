using System;
using System.Collections.Generic;
using System.Text;

namespace WinDX.UI
{
    class MacroParameterDefinition : NodeDefinition
    {
        protected override CDBAllocator getCDBAllocator()
        {
            return ParameterCDB.AllocateConfigurationDialog;
        }
        protected override Node newNode(Network net, int instance)
        {
            if (!net.CanBeMacro)
            {
                ErrorDialog ed = new ErrorDialog();
                ed.post("The {0} tool, which converts this network to a macro, is not " +
                    "allowed in the current network. It is likely that one or more " +
                    "of the tools in the current network is not allowed in a macro.",
                    NameString);
                return null;
            }
            MacroParameterNode d = new MacroParameterNode(this, net, instance);
            return d;
        }

        public MacroParameterDefinition()
            : base()
        { }

        public static new NodeDefinition AllocateDefinition()
        {
            return new MacroParameterDefinition();
        }

        public override void finishDefinition()
        {
            base.finishDefinition();
            foreach (ParameterDefinition pd in outputDefs)
            {
                pd.setWriteableCacheability(false);
                pd.setDefaultCacheability(Cacheability.OutputFullyCached);
            }
        }
    }
}
