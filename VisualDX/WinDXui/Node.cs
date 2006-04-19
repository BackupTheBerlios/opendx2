using System;
using System.Collections.Generic;
using System.Text;

namespace WinDX.UI
{
    class Node
    {
        public enum NodeParameterStatusChange {
            ParameterValueChanged = 0x100000,
            PatemeterSetValueChanged = 0x000001 | 0x100000,
            ParameterSetValueToDefaulting = 0x000002 | 0x100000,
            ParameterVisibilityChanged = 0x200000,
            ParameterBecomesVisible = 0x000003 | 0x200000,
            ParameterBecomesInvisible = 0x000004 | 0x200000,
            ParameterArkChanged = 0x400000,
            ParameterArkRemoved = 0x000008 | 0x400000,
            ParameterArkAdded = 0x000010 | 0x400000
        };
    }
}
