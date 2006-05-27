using System;
using System.Collections.Generic;
using System.Text;
using System.IO;
using System.Diagnostics;
using System.Text.RegularExpressions;

namespace WinDX.UI
{
    class ParseMDF
    {
        private static Dictionary<String, NodeDefinition> theDynamicPackageDictionary =
            new Dictionary<String, NodeDefinition>();

        public static NodeDefinition ParseModuleLine(Dictionary<Symbol, NodeDefinition> mdf,
            String line, int lineNumber)
        {
            int current;
            int temp;
            String function;
            NodeDefinition module = null;

            Debug.Assert(mdf != null);
            Debug.Assert(line != null);
            Debug.Assert(lineNumber > 0);

            line = line.Trim();

            Regex rx = new Regex(@"^MODULE\s+([a-zA-Z_]\w*)$");
            Match m = rx.Match(line);
            if (!m.Success)
            {
                ErrorDialog ed = new ErrorDialog();
                ed.post("Invalid module name: {0} must start with a letter and contain only letters and numbers (line {1})",
                    line, lineNumber);
                return null;
            }
            function = m.Groups[1].Value;
            Symbol s = SymbolManager.theSymbolManager.registerSymbol(function);
            if (mdf.ContainsKey(s))
            {
                ErrorDialog ed = new ErrorDialog();
                ed.post("Encountered another definition of module \"{0}\" on line {1}",
                    function, lineNumber);
                return null;
            }

            // Get a new NodeDefinition by name
            module = NDAllocatorDictionary.theNDAllocatorDictionary.allocate(function);
            if (module == null)
            {
                ErrorDialog ed = new ErrorDialog();
                ed.post("Can not find NodeDefinition allocator for module '{0}'",
                    function);
                return null;
            }
            module.setName(function);
            return module;
        }

        public static bool ParseMDFTypes(ref ParameterDefinition param, String p, int lineNumber)
        {
            DXType input_type;
            Regex reg = new Regex(" or ");
            p = reg.Replace(p, " | ");

            List<String> types = Utils.StringTokenizer(p, "|", new String[] { "" });
            DXTypeVals type;
            foreach (String str in types)
            {
                String sstr = str.Trim();
                type = DXType.StringToType(sstr);
                if (type == DXTypeVals.UndefinedType)
                {
                    ErrorDialog ed = new ErrorDialog();
                    ed.post("Erroneous parameter type encountered in line {0}.", lineNumber);
                    return false;
                }

                input_type = new DXType(type);
                bool r = param.addType(input_type);
                Debug.Assert(r);
            }
            return true;
        }

        public static bool GetIntegerAttribute(String line, String attr, ref int val)
        {
            String ms = attr + @"\s*:\s*([0-9]+)";
            Regex rx = new Regex(ms);
            Match m = rx.Match(line);
            if (!m.Success)
                return false;
            val = Int32.Parse(m.Groups[1].Value);
            return true;
        }

        public static bool ParseParameterAttributes(ref ParameterDefinition pd,
            String attr)
        {
            int val = 0;
            bool v;

            if (GetIntegerAttribute(attr, "private", ref val))
            {
                v = (val == 1 ? false : true);
                pd.setViewability(v);
                if (v) pd.setDefaultVisibility(false);
            }
            else if (GetIntegerAttribute(attr, "hidden", ref val))
            {
                v = (val == 1 ? false : true);
                pd.setDefaultVisibility(v);
            }

            if (GetIntegerAttribute(attr, "visible", ref val))
            {
                bool visible = false, viewable = false;
                if (val == 0)
                {
                    viewable = true;
                    visible = false;
                }
                else if (val == 1)
                {
                    viewable = true;
                    visible = true;
                }
                else if (val == 2)
                {
                    viewable = false;
                    visible = false;
                }
                pd.setViewability(viewable);
                pd.setDefaultVisibility(visible);
            }

            if (GetIntegerAttribute(attr, "cache", ref val))
                pd.setDefaultCacheability((Cacheability)val);
            if (pd.IsInput && GetIntegerAttribute(attr, "reroute", ref val) &&
                (val >= 0))
                pd.setRerouteOutput(val + 1);

            return true;
        }

        public static bool ParseOutboardLine(ref NodeDefinition module, String line,
            int lineNumber)
        {
            Debug.Assert(module != null);
            Debug.Assert(line != null);
            Debug.Assert(lineNumber > 0);

            line = line.Trim();
            List<String> toks = Utils.StringTokenizer(line, ";", null);
            if (toks.Count < 1)
            {
                ErrorDialog ed = new ErrorDialog();
                ed.post("Encountered an erroneous OUTBOARD specification on line {0}", lineNumber);
                return false;
            }
            module.OutboardCommand = toks[0];
            if (toks.Count > 1)
                module.DefaultOutboardHost = toks[1];

            return true;
        }

        public static bool ParseLoadableLine(ref NodeDefinition module, String line,
            int lineNumber)
        {
            Debug.Assert(module != null);
            Debug.Assert(line != null);
            Debug.Assert(lineNumber > 0);

            line = line.Trim();
            int sem = line.IndexOf(';');
            if (sem >= 0)
                line = line.Substring(0, sem);

            if (line.Length == 0)
            {
                ErrorDialog ed = new ErrorDialog();
                ed.post("Encountered an erroneous LOADABLE specification on line {0}.", lineNumber);
                return false;
            }
            module.DynamicLoadFile = line;
            return true;
        }

        public static bool ParseInputLine(Dictionary<Symbol, NodeDefinition> mdf,
            ref NodeDefinition module, String line, int lineNumber)
        {
            Debug.Assert(mdf != null);
            Debug.Assert(module != null);
            Debug.Assert(line != null);
            Debug.Assert(lineNumber > 0);
            ParameterDefinition input = null;
            Symbol symbol;

            List<String> toks = Utils.StringTokenizer(line, ";", new String[] { "" });

            if (toks.Count < 3)
            {
                ErrorDialog ed = new ErrorDialog();
                ed.post("Encountered an erroneous INPUT specification on line {0}.", lineNumber);
                return false;
            }

            // Parse the first substring: NAME and optional attributes
            String iname;
            int bracketStart = toks[0].IndexOf('[');
            if (bracketStart >= 0)
                iname = toks[0].Substring(0, bracketStart);
            else
                iname = toks[0];

            iname = iname.Trim();
            Regex rx = new Regex(@"^([a-zA-Z_]\w*)$");
            Match m = rx.Match(iname);
            if (!m.Success)
            {
                ErrorDialog ed = new ErrorDialog();
                ed.post("Invalid input name: {0} line {1}",
                    iname, lineNumber);
                return false;
            }

            symbol = SymbolManager.theSymbolManager.registerSymbol(iname);
            input = new ParameterDefinition(symbol);
            input.markAsInput();
            input.setDefaultVisibility();

            if (toks[0].Contains("["))
            {
                int begin_att = toks[0].IndexOf('[');
                int end_att = toks[0].Substring(begin_att).IndexOf(']');
                String atts = null;
                if (end_att > 0)
                    atts = toks[0].Substring(begin_att, end_att);
                if (atts != null)
                    if (!ParseParameterAttributes(ref input, atts))
                    {
                        ErrorDialog ed = new ErrorDialog();
                        ed.post("Unrecognized input attribute(s) ({0}) in MDF line {1}",
                            atts, lineNumber);
                        return false;
                    }
            }

            // Parse the second substring: TYPE.
            if (!ParseMDFTypes(ref input, toks[1], lineNumber))
                return false;

            // Parse the third substring:  DEFAULT VALUE.

            // If the value is equal to "(none)", then mark this parameter
            // as a required parameter.

            toks[2] = toks[2].Trim();
            if (toks[2].StartsWith("("))
            { // A descriptive value
                if (toks[2] == "(none)")
                    input.setRequired();
                else
                    input.setNotRequired();
                input.setDescriptiveValue(toks[2]);
            }
            else if (!input.setDefaultValue(toks[2]))
            {
                ErrorDialog ed = new ErrorDialog();
                ed.post("Default value given on line {0} not one of given types.", lineNumber);
                return false;
            }

            // Add the fourth substring:  DESCRIPTION
            // Description can be blank
            if (toks.Count == 3)
                input.setDescription("");
            else
                input.setDescription(toks[3]);

            module.addInput(input);
            return true;
        }

        public static bool ParseOutputLine(Dictionary<Symbol, NodeDefinition> mdf,
            ref NodeDefinition module, String line, int lineNumber)
        {
            Debug.Assert(mdf != null);
            Debug.Assert(module != null);
            Debug.Assert(line != null);
            Debug.Assert(lineNumber > 0);

            Symbol symbol;
            ParameterDefinition output;

            List<String> toks = Utils.StringTokenizer(line, ";", new String[] { "" });

            if (toks.Count < 3)
            {
                ErrorDialog ed = new ErrorDialog();
                ed.post("Encountered an erroneous OUTPUT specification on line {0}.", lineNumber);
                return false;
            }

            // Parse the first substring: NAME and optional attributes
            String iname;
            int bracketStart = toks[0].IndexOf('[');
            if (bracketStart >= 0)
                iname = toks[0].Substring(0, bracketStart);
            else
                iname = toks[0];

            iname = iname.Trim();
            Regex rx = new Regex(@"^([a-zA-Z_][0-9a-zA-Z_]*)$");
            Match m = rx.Match(iname);
            if (!m.Success)
            {
                ErrorDialog ed = new ErrorDialog();
                ed.post("Invalid output name: {0} line {1}",
                    iname, lineNumber);
                return false;
            }

            symbol = SymbolManager.theSymbolManager.registerSymbol(iname);
            output = new ParameterDefinition(symbol);
            output.markAsOutput();
            output.setDefaultVisibility();

            if (toks[0].Contains("["))
            {
                int begin_att = toks[0].IndexOf('[');
                int end_att = toks[0].Substring(begin_att).IndexOf(']');
                String atts = null;
                if (end_att > 0)
                    atts = toks[0].Substring(begin_att, end_att);
                if (atts != null)
                    if (!ParseParameterAttributes(ref output, atts))
                    {
                        ErrorDialog ed = new ErrorDialog();
                        ed.post("Unrecognized input attribute(s) ({0}) in MDF line {1}",
                            atts, lineNumber);
                        return false;
                    }
            }

            // Parse the second substring: TYPE.
            if (!ParseMDFTypes(ref output, toks[1], lineNumber))
                return false;

            // Parse the third substring:  DESCRIPTION

            output.setDescription(toks[2]);

            module.addOutput(output);
            return true;

        }

        public static bool ParseOptionsLine(Dictionary<Symbol, NodeDefinition> mdf,
            ref NodeDefinition module, String line, int lineNumber)
        {
            Debug.Assert(mdf != null);
            Debug.Assert(module != null);
            Debug.Assert(line != null);
            Debug.Assert(lineNumber > 0);

            int inum = module.InputCount;

            // assumes we're working on the most recently added param.
            ParameterDefinition pd = module.getInputDefinition(inum);

            List<String> toks = Utils.StringTokenizer(line, ";", new string[] { "" });
            foreach (string tok in toks)
            {
                String tokt = tok.Trim();
                if (tokt.Length > 0)
                    pd.addValueOption(tokt);
            }
            return true;
        }

        private static bool ParseRepeatLine(Dictionary<Symbol, NodeDefinition> mdf,
            ref NodeDefinition module, String line, int lineNumber, StateConstants io_state)
        {
            Debug.Assert(mdf != null);
            Debug.Assert(module != null);
            Debug.Assert(line != null);
            Debug.Assert(lineNumber > 0);
            Debug.Assert(io_state == StateConstants.Input || io_state == StateConstants.Output);

            line = line.Trim();
            Regex rx = new Regex(@"^([0-9]+)$");
            Match m = rx.Match(line);
            if (!m.Success)
            {
                ErrorDialog ed = new ErrorDialog();
                ed.post("Encountered error when expecting a repeat value on line {0}.",
                    lineNumber);
                return false;
            }

            int value = Int32.Parse(line);

            int cnt;
            String ioname;

            if (io_state == StateConstants.Input)
            {
                cnt = module.InputCount;
                ioname = "input";
                module.InputRepeatCount = value;
            }
            else
            {
                cnt = module.OutputCount;
                ioname = "output";
                module.OutputRepeatCount = value;
            }

            if (value > cnt)
            {
                ErrorDialog ed = new ErrorDialog();
                ed.post("The repeat value on line {0} is greater than the number of prior {1} paramaters.",
                    lineNumber, ioname);
                if (io_state == StateConstants.Input)
                    module.InputRepeatCount = 0;
                else
                    module.OutputRepeatCount = 0;
                return false;
            }
            return true;
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="mdf"></param>
        /// <param name="module"></param>
        /// <returns>true if the module was added to the mdf dictionary</returns>
        public static bool FinishNodeDefinition(ref Dictionary<Symbol, NodeDefinition> mdf,
            ref NodeDefinition module)
        {
            Debug.Assert(mdf != null);
            Debug.Assert(module != null);

            Symbol nameSym = module.NameSymbol;

            if (module.Category != Symbol.zero ||
            (nameSym == NDAllocatorDictionary.GetNodeNameSymbol) ||
            (nameSym == NDAllocatorDictionary.SetNodeNameSymbol))
            {
                module.completeDefinition();
                mdf.Add(nameSym, module);
                return true;
            }
            else
                return false;
        }

        private enum StateConstants : long
        {
            None = 0,
            Module = 1,
            Category = 2,
            Description = 4,
            Input = 8,
            Repeat = 16,
            Output = 32,
            Error = 64,
            SawRepeat = 128,
            Flags = 256,
            Outboard = 512,
            Loadable = 1024,
            Package = 2048,
            Options = 4096
        };

        public static bool ReadMDF(ref Dictionary<Symbol, NodeDefinition> mdf, 
            StreamReader input, bool uionly)
        {
            NodeDefinition module;
            Symbol category;
            StateConstants state, last_iostate;
            bool parsed_flags, checked_flags, finished, parsed_category,
                parsed_description, parsed_outboard, checked_category,
                checked_description, checked_outboard, parsed_loadable,
                checked_loadable, checked_repeat, get_another_line;
            int line_number;
            String p = null;

            Debug.Assert(mdf != null);
            Debug.Assert(input != null);

            module = null;
            line_number = 0;
            state = StateConstants.Package;
            last_iostate = StateConstants.None;

            finished = false;
            get_another_line = true;
            parsed_description = false;
            parsed_outboard = false;
            parsed_loadable = false;
            parsed_category = false;
            parsed_flags = false;

            checked_category = false;
            checked_description = false;
            checked_outboard = false;
            checked_flags = false;
            checked_loadable = false;
            checked_repeat = false;

            for (; ; )
            {
                if (get_another_line)
                {
                    checked_description = parsed_description;
                    checked_repeat = false;
                    checked_loadable = parsed_loadable;
                    checked_outboard = parsed_outboard;
                    checked_category = parsed_category;
                    checked_flags = parsed_flags;

                    for (; ; )
                    {
                        // Get a line to parse
                        p = input.ReadLine();
                        line_number++;

                        if (p == null)
                        {
                            finished = true;
                            break;
                        }

                        p = p.Trim();

                        if (p.Length > 0 && p.ToCharArray()[0] != '#')
                            break;
                    }
                }
                else
                {
                    get_another_line = true;
                }

                // If no more input, i.e. finished, then exit loop.
                if (finished)
                    break;

                // Otherwise, parse according to the current state.
                switch (state)
                {
                    case StateConstants.Package:
                        // Parse the standalone "PACKAGE" keyword
                        if (p.StartsWith("PACKAGE"))
                        {
                            p = p.Substring(7);
                            p = p.TrimStart();
                            theDynamicPackageDictionary[p] = null;
                        }
                        else
                        {
                            // Don't get another line yet
                            get_another_line = false;
                            state = StateConstants.Module;
                        }
                        break;
                    case StateConstants.Module:
                        // Parse MODULE keyword
                        if (!p.StartsWith("MODULE"))
                        {
                            ErrorDialog ed = new ErrorDialog();
                            ed.post("Encountered error when expecting \"MODULE\" keyword on line {0}.",
                                line_number);
                            return false;
                        }

                        if (module != null)
                        {
                            if(!FinishNodeDefinition(ref mdf, ref module))
                                module = null;
                        }

                        checked_description = parsed_description = false;
                        checked_outboard = parsed_outboard = false;
                        checked_loadable = parsed_loadable = false;
                        checked_category = parsed_category = false;
                        checked_flags = parsed_flags = false;
                        checked_repeat = false;

                        // Add the module index to the module index list.

                        module = ParseModuleLine(mdf, p, line_number);
                        if (module != null)
                        {
                            state = StateConstants.Category;
                            if (uionly)
                                module.UILoadedOnly = true;
                        }
                        else
                            return false;
                        break;
                    case StateConstants.Category:
                        checked_category = true;
                        if (p.StartsWith("CATEGORY"))
                        {
                            String cat = p.Substring(8);
                            cat = cat.TrimStart();
                            category = SymbolManager.theSymbolManager.registerSymbol(cat);
                            if (module == null)
                            {
                                ErrorDialog ed = new ErrorDialog();
                                ed.post("Encountered unexpected \"CATEGORY\" on line {0}.",
                                    line_number);
                                return false;
                            }
                            module.Category = category;
                            parsed_category = true;
                            if (!parsed_description)
                                state = StateConstants.Description;
                            else if (!parsed_outboard)
                                state = StateConstants.Outboard;
                            else if (!parsed_flags)
                                state = StateConstants.Flags;
                            else
                                state = StateConstants.Input;
                        }
                        else
                        {
                            module.Category = Symbol.zero;

                            get_another_line = false;
                            if (!checked_description)
                                state = StateConstants.Description;
                            else if (!checked_outboard)
                                state = StateConstants.Outboard;
                            else if (!checked_flags)
                                state = StateConstants.Flags;
                            else
                                state = StateConstants.Input;
                        }
                        break;
                    case StateConstants.Description:
                        checked_description = true;

                        if (p.StartsWith("DESCRIPTION"))
                        {
                            String desc = p.Substring(11);
                            desc = desc.TrimStart();

                            module.Description = desc;
                            parsed_description = true;
                            if (!parsed_category)
                                state = StateConstants.Category;
                            else if (!parsed_outboard)
                                state = StateConstants.Outboard;
                            else if (!parsed_flags)
                                state = StateConstants.Flags;
                            else
                                state = StateConstants.Input;
                        }
                        else
                        {
                            get_another_line = false;
                            if (!checked_category)
                                state = StateConstants.Category;
                            else if (!checked_outboard)
                                state = StateConstants.Outboard;
                            else if (!checked_flags)
                                state = StateConstants.Flags;
                            else
                                state = StateConstants.Input;
                        }
                        break;
                    case StateConstants.Loadable:
                        checked_loadable = true;
                        if (p.StartsWith("LOADABLE"))
                        {
                            String load = p.Substring(8);
                            load = load.TrimStart();

                            if (!ParseLoadableLine(ref module, load, line_number))
                                return false;
                            parsed_loadable = true;

                            if (!parsed_category)
                                state = StateConstants.Category;
                            else if (!parsed_description)
                                state = StateConstants.Description;
                            else if (!parsed_flags)
                                state = StateConstants.Flags;
                            else
                                state = StateConstants.Input;
                        }
                        else
                        {
                            get_another_line = false;

                            if (!checked_category)
                                state = StateConstants.Category;
                            else if (!checked_description)
                                state = StateConstants.Description;
                            else if (!checked_flags)
                                state = StateConstants.Flags;
                            else if (!checked_outboard)
                                state = StateConstants.Outboard;
                            else
                                state = StateConstants.Input;
                        }
                        break;
                    case StateConstants.Outboard:
                        checked_outboard = true;
                        if (p.StartsWith("OUTBOARD"))
                        {
                            String outb = p.Substring(8);
                            outb = outb.TrimStart();
                            if (!ParseOutboardLine(ref module, outb, line_number))
                                return false;
                            parsed_outboard = true;

                            if (!parsed_category)
                                state = StateConstants.Category;
                            else if (!parsed_description)
                                state = StateConstants.Description;
                            else if (!parsed_flags)
                                state = StateConstants.Flags;
                            else
                                state = StateConstants.Input;
                        }
                        else
                        {
                            get_another_line = false;

                            if (!checked_loadable)
                                state = StateConstants.Loadable;
                            else if (!checked_category)
                                state = StateConstants.Category;
                            else if (!checked_description)
                                state = StateConstants.Description;
                            else if (!checked_flags)
                                state = StateConstants.Flags;
                            else
                                state = StateConstants.Input;
                        }
                        break;
                    case StateConstants.Flags:
                        checked_flags = true;
                        if (p.StartsWith("FLAGS"))
                        {
                            parsed_flags = true;

                            if (p.Contains("SWITCH")) module.setMDFFlagSWITCH();
                            if (p.Contains("ERR_CONT")) module.setMDFFlagERR_CONT();
                            if (p.Contains("PIN")) module.setMDFFlagPIN();
                            if (p.Contains("SIDE_EFFECT")) module.setMDFFlagSIDE_EFFECT();
                            if (p.Contains("PERSISTENT")) module.setMDFFlagPERSISTENT();
                            if (p.Contains("ASYNC")) module.setMDFFlagASYNCHRONOUS();
                            if (p.Contains("REROUTABLE")) module.setMDFFlagREROUTABLE();
                            if (p.Contains("REACH")) module.setMDFFlagREACH();
                            if (p.Contains("LOOP")) module.setMDFFlagLOOP();

                            if (!parsed_category)
                                state = StateConstants.Category;
                            else if (!parsed_description)
                                state = StateConstants.Description;
                            else if (!parsed_outboard)
                                state = StateConstants.Outboard;
                            else
                                state = StateConstants.Input;
                        }
                        else
                        {
                            get_another_line = false;

                            if (!parsed_category)
                                state = StateConstants.Category;
                            else if (!parsed_description)
                                state = StateConstants.Description;
                            else if (!parsed_outboard)
                                state = StateConstants.Outboard;
                            else
                                state = StateConstants.Input;
                        }
                        break;
                    case StateConstants.Input:
                        last_iostate = StateConstants.Input;
                        if (p.StartsWith("INPUT"))
                        {
                            String inp = p.Substring(5);
                            inp = inp.TrimStart();
                            if (ParseInputLine(mdf, ref module, inp, line_number))
                                state = StateConstants.Input;
                            else
                                return false;
                        }
                        else
                        {
                            get_another_line = false;

                            if (checked_repeat)
                                state = StateConstants.Output;
                            else
                                state = StateConstants.Options;
                        }
                        break;
                    case StateConstants.Output:
                        last_iostate = StateConstants.Output;
                        if (p.StartsWith("OUTPUT"))
                        {
                            String outp = p.Substring(6);
                            outp = outp.TrimStart();
                            if (ParseOutputLine(mdf, ref module, outp, line_number))
                                state = StateConstants.Output;
                            else
                                return false;
                        }
                        else
                        {
                            get_another_line = false;
                            state = StateConstants.Repeat;
                        }
                        break;
                    case StateConstants.Repeat:
                        checked_repeat = true;
                        if (p.StartsWith("REPEAT"))
                        {
                            String rep = p.Substring(6);
                            rep = rep.TrimStart();
                            if (ParseRepeatLine(mdf, ref module, rep, line_number, last_iostate))
                            {
                                // Next, parse output or module line.
                                if (last_iostate == StateConstants.Input)
                                    state = StateConstants.Output;
                                else if (last_iostate == StateConstants.Output)
                                    state = StateConstants.Package;
                                else
                                    Debug.Assert(false);
                                get_another_line = true;
                            }
                            else
                                return false;
                        }
                        else
                        {
                            get_another_line = false;
                            // If not successful, try parsing output or module line.
                            if (last_iostate == StateConstants.Input)
                                state = StateConstants.Input;
                            else if (last_iostate == StateConstants.Output)
                                state = StateConstants.Package;
                            else
                                Debug.Assert(false);
                        }
                        break;
                    case StateConstants.Options:
                        Debug.Assert(last_iostate == StateConstants.Input);
                        if (p.StartsWith("OPTIONS"))
                        {
                            String opts = p.Substring(7);
                            opts = opts.TrimStart();
                            if (ParseOptionsLine(mdf, ref module, opts, line_number))
                            {
                                state = StateConstants.Options;
                                get_another_line = true;
                            }
                            else
                                return false;
                        }
                        else
                        {
                            get_another_line = false;
                            // If not successful, try parsing output or module line.
                            if (!checked_repeat)
                                state = StateConstants.Repeat;
                            else
                                state = StateConstants.Input;
                        }
                        break;

                    default:
                        Debug.Assert(false);
                        break;
                }
            }

            if (module != null)
                FinishNodeDefinition(ref mdf, ref module);

            return true;
        }

        public static bool LoadMDFFile(String file, String mdftype,
            ref Dictionary<Symbol, NodeDefinition> mdf, bool uionly)
        {
            StreamReader input;
            bool parsed;

            if (file == null || file.Length == 0)
                return true;

            try
            {
                input = new StreamReader(file);
                parsed = ReadMDF(ref mdf, input, uionly);
                input.Close();

                if (!parsed)
                {
                    ErrorDialog ed = new ErrorDialog();
                    ed.post("Error found in {0} module definition file \"{1}\".",
                        mdftype, file);
                    return false;
                }
            }
            catch (System.IO.IOException e)
            {
                ErrorDialog ed = new ErrorDialog();
                ed.post("Cannot open {0} module description file \"{1}\".", 
                    mdftype, file);
                return false;
            }
            return true;
        }

    }
}
