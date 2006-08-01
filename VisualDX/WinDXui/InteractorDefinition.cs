// Completed 7/26/2006

using System;
using System.Collections.Generic;
using System.Text;

namespace WinDX.UI
{
    class InteractorDefinition : ShadowedOutputDefinition
    {
        protected override SIAllocator getSIAllocator()
        {
            return InteractorStandIn.AllocateStandIn;
        }

        public InteractorDefinition() { }

    }
}
