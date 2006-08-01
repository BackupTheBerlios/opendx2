using System;
using System.Collections.Generic;
using System.Text;

namespace WinDX.UI
{
    class DrivenDefinition : NodeDefinition
    {
        /// <summary>
        /// Driven nodes use AttributeParameters as input parameters.
        /// </summary>
        /// <param name="pd"></param>
        /// <param name="n"></param>
        /// <param name="index"></param>
        /// <returns></returns>
        public override Parameter newParameter(ParameterDefinition pd,
            Node n, int index)
        {
            if (pd.IsInput)
                return new AttributeParameter(pd, n, index);
            else
                return new Parameter(pd);
        }

        /// <summary>
        /// Mark all outputs as cache once with read-only cache attributes
        /// (as per the semantics of data-driven interactors).
        /// This helps to force an execution when inputs change that must have
        /// their values communicated back to the User Interface.
        /// </summary>
        public override void finishDefinition()
        {
            base.finishDefinition();
            foreach (ParameterDefinition pd in outputDefs)
            {
                pd.setWriteableCacheability(false);
                pd.setDefaultCacheability(Cacheability.OutputCacheOnce);
            }
        }

        public DrivenDefinition() { }

        public override bool IsAllowedInMacro()
        {
             return false;
        }

    }
}
