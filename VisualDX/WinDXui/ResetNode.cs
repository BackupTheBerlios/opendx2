// Completed 7/27/2006

using System;
using System.Collections.Generic;
using System.Text;

namespace WinDX.UI
{
    class ResetNode : ToggleNode
    {
        protected override int handleInteractorMsgInfo(string line)
        {
            int vals = 0;

            if (line.Contains("Resetting oneshot"))
            {
                this.reset(false);
                clearOutputDirty(1);
                vals++;
            }
            return vals;
        }

        protected override bool expectingModuleMessage()
        {
            return true;
        }


        protected override string strcatParameterNameLvalue(Parameter p, string prefix, int index)
        {
            String s = base.strcatParameterNameLvalue(p, prefix, index);

            if (index == 1 && !p.IsInput && IsSet)
            {
                String reset = getResetValue();
                s += String.Format("[oneshot:{0}]", reset);
            }
            return s;
        }

        protected override string getModuleMessageIdString()
        {
            if (moduleMessageId == null || moduleMessageId.Length == 0)
                moduleMessageId = getNetworkOutputNameString(1);
            return moduleMessageId;
        }

        public ResetNode(NodeDefinition nd, Network net, int instnc) :
            base(nd, net, instnc)
        { }

        public override bool initialize()
        {
            return base.initialize();
        }

        public override string getJavaNodeName()
        {
            return "ResetNode";
        }
    }
}
