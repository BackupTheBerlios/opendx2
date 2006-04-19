using System;
using System.Collections.Generic;
using System.Text;

namespace WinDX.UI
{
    class NodeDefinition : Definition
    {
        // Was this definition only loaded by the ui
        private bool uiLoadedOnly;

        protected List<ParameterDefinition> inputDefs;
        protected List<ParameterDefinition> outputDefs;
        Symbol category;

    }
}
