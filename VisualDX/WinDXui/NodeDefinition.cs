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
        protected Symbol category;
        protected long mdf_flags;  // bits representing FLAGS statment in mdf.
        protected String description;  // A short description
        protected int input_repeats;  // the last n inputs are repeatable 
        protected int output_repeats;  // the last n outputs are repeatable
        protected String loadFile;  // Name of the file containing loadable object
        protected String outboardCommand;  // Name of executable file.
        protected String outboardHost;

        protected bool userTool; // true if defined by a user .mdf file and defaults to true.

        protected bool writeableCacheability; // Is the cacheability of this type of node modifyable

        protected Cacheability defaultCacheability; // Is the module cached by default

        /// <summary>
        /// Increment this number to generate numbers for instances
        /// of the type that is being defined.
        /// </summary>
        protected int nodeInstanceNumbers;

        protected virtual bool addIODef(List<ParameterDefinition> l, ParameterDefinition pd)
        {
            if (l == null)
                return false;
            l.Add(pd);
            return true;
        }

        public static Dictionary<Symbol, NodeDefinition> theNodeDefinitionDictionary;
    }
}
