using System;
using System.Collections.Generic;
using System.Text;

namespace WinDX.UI
{
    class ComputeDefinition : NodeDefinition
    {
        protected override CDBAllocator getCDBAllocator()
        {
            return ComputeCDB.AllocateConfigurationDialog;
        }

        protected override Node newNode(Network net, int instance)
        {
            ComputeNode c = new ComputeNode(this, net, instance);
            return c;
        }

        public ComputeDefinition()
            :
            base()
        { }

        public new static NodeDefinition AllocateDefinition()
        {
            return new ComputeDefinition();
        }

        public override void finishDefinition()
        {
            ParameterDefinition p = getInputDefinition(1);
            p.setDefaultVisibility(false);
        }
    }
}
