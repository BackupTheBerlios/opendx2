using System;
using System.Collections.Generic;
using System.Text;
using System.IO;

namespace WinDX.UI
{
    class ParseMDF
    {
        private Dictionary<String, NodeDefinition> theDynamicPackageDictionary =
            new Dictionary<String, NodeDefinition>();

        public static bool ParsePackageLine(String line, int lineNumber, int start)
        {
            throw new Exception("Not Yet Implemented");
        }

        public static NodeDefinition ParseModuleLine(Dictionary<Symbol, NodeDefinition> mdf,
            String line, int lineNumber, int start)
        {
            throw new Exception("Not Yet Implemented");
        }

        public static bool ParseMDFTypes(ref ParameterDefinition param, String p, int lineNumber)
        {
            throw new Exception("Not Yet Implemented");
        }

        public static bool GetIntegerAttribute(String line, String attr, int val)
        {
            throw new Exception("Not Yet Implemented");
        }

        public static bool ParseParameterAttributes(ref ParameterDefinition pd,
            String attr)
        {
            throw new Exception("Not Yet Implemented");
        }

        public static bool ParseOutboardLine(ref NodeDefinition module, String line,
            int lineNumber, int start)
        {
            throw new Exception("Not Yet Implemented");
        }

        public static bool ParseLoadableLine(ref NodeDefinition module, String line,
            int lineNumber, int start)
        {
            throw new Exception("Not Yet Implemented");
        }

        public static bool ParseInputLine(Dictionary<Symbol, NodeDefinition> mdf,
            ref NodeDefinition module, String line, int lineNumber, int start)
        {
            throw new Exception("Not Yet Implemented");
        }

        public static bool ParseOutputLine(Dictionary<Symbol, NodeDefinition> mdf,
            ref NodeDefinition module, String line, int lineNumber, int start)
        {
            throw new Exception("Not Yet Implemented");
        }

        public static bool ParseOptionsLine(Dictionary<Symbol, NodeDefinition> mdf,
            ref NodeDefinition module, String line, int lineNumber, int start)
        {
            throw new Exception("Not Yet Implemented");
        }

        public static bool ParseMDFOptions(ref ParameterDefinition pd, String p)
        {
            throw new Exception("Not Yet Implemented");
        }

        public static bool ParseRepeatLine(Dictionary<Symbol, NodeDefinition> mdf,
            ref NodeDefinition module, String line, int lineNumber, int start,
            int io_state)
        {
            throw new Exception("Not Yet Implemented");
        }

        public static bool FinishNodeDefinition(ref Dictionary<Symbol, NodeDefinition> mdf,
            ref NodeDefinition module)
        {
            throw new Exception("Not Yet Implemented");
        }

        public static bool ReadMDF(ref Dictionary<Symbol, NodeDefinition> mdf, 
            Stream s, bool uionly)
        {
            throw new Exception("Not Yet Implemented");
        }

        public static bool LoadMDFFile(String file, String mdftype,
            ref Dictionary<Symbol, NodeDefinition> mdf, bool uionly)
        {
            throw new Exception("Not Yet Implemented");
        }

    }
}
