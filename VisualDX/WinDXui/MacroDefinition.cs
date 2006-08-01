using System;
using System.Collections.Generic;
using System.Text;
using System.IO;
using System.Text.RegularExpressions;

namespace WinDX.UI
{
    public class MacroDefinition : NodeDefinition
    {
        #region Private Instance Variables
        private SaveMacroCommand saveCmd;
        private bool systemMacro; // Is this an internal only system macro
        #endregion

        #region Protected Instance Variables
        protected String fileName;
        protected Network body;
        
        protected List<Node> referencingNodes = new List<Node>();

        protected bool initialRead;
        protected bool updatingServer; // Are we calling DXExecCtl.updateMacros()

        #endregion

        #region Public Instance Variables

        public String FileName
        {
            get { return fileName; }
        }

        public static readonly String OLD_DUMMY_DESCRIPTION_STRING = "Generated dummy input";

        #endregion

        #region Public Methods
        /// <summary>
        /// Load a Macro
        /// </summary>
        /// <param name="fileName"></param>
        /// <param name="errmsg">
        /// If errmsg is not NULL and an error occurs then, no error messages are
        /// posted, and instead a string buffer is allocated to hold the error
        /// message that would have been posted and returned.
        /// </param>
        /// <returns></returns>
        public static bool LoadMacro(String fileName)
        {
            String errmsg = null;
            return LoadMacro(fileName, ref errmsg, false);
        }
        public static bool LoadMacro(String fileName, ref String errmsg)
        {
            return LoadMacro(fileName, ref errmsg, false);
        }
        public static bool LoadMacro(String fileName, ref String errmsg,
            bool asSystemMacro)
        {
            String netFile = Network.FilenameToNetname(fileName);
            bool return_code = true;
            bool wasEncoded;

            if (errmsg != null)
                errmsg = null;

            FileStream fs = Network.OpenNetworkFile(netFile, out wasEncoded, ref errmsg);

            if (fs == null)
            {
                return_code = false;
            }
            else
            {
                bool wasMacro;
                StreamReader sr = new StreamReader(fs);
                MacroDefinition.LoadMacroFile(sr, netFile, true, out wasMacro, asSystemMacro);
                Network.CloseNetworkFile(fs, wasEncoded);
                if (!wasMacro)
                {
                    String errtxt = "File {0} doesn't contain a macro and was not loaded";
                    if (errmsg != null)
                    {
                        errmsg = String.Format(errtxt, netFile);
                    }
                    else
                    {
                        ErrorDialog ed = new ErrorDialog();
                        ed.post(errtxt, netFile);
                    }
                    return_code = false;
                }
            }
            return return_code;
        }

        /// <summary>
        /// Load all .net files in the given directory that are macros.
        /// </summary>
        /// <param name="path"></param>
        /// <param name="replace">If true then replace current definitions with 
        /// the new one otherwise ignore the .net file.</param>
        /// <param name="errmsg">If errmsg is not NULL and an error occurs then, 
        /// no error messages are
        /// posted, and instead a string buffer is allocated to hold the error
        /// message that would have been posted and returned.</param>
        /// <param name="asSystemMacro"></param>
        /// <returns></returns>
        public static bool LoadMacroDirectories(String path)
        {
            TimedDialog.NotifyUser("Loading Macro Directories");
            String errmsg = null;
            return LoadMacroDirectories(path, false, ref errmsg, false);
            TimedDialog.NotifyUser("");

        }
        public static bool LoadMacroDirectories(String path,
            bool replace)
        {
            String errmsg = null;
            return LoadMacroDirectories(path, replace, ref errmsg, false);
        }
        public static bool LoadMacroDirectories(String path,
            bool replace, ref String errmsg)
        {
            return LoadMacroDirectories(path, replace, ref errmsg, false);
        }
        public static bool LoadMacroDirectories(String path,
            bool replace, ref String errmsg, bool asSystemMacro)
        {
            bool wasEncoded;
            bool return_code = true;

            if (path == null || path.Length == 0)
                return true;

            List<String> toks = Utils.StringTokenizer(path, ";", null);

            List<String> nets = new List<string>();
            // Enumerate over the paths
            foreach (String file in toks)
            {
                if (file.Length > 0)
                {
                    // for each path, locate all .net files and add them to nets.
                    String[] netfiles = null;
                    try
                    {
                        netfiles = Directory.GetFiles(file, "*.net");
                        if (netfiles.Length > 0)
                            nets.AddRange(netfiles);
                    }
                    catch (Exception)
                    { }   
                }
            }

            // At this point, we should have all the macros.
            foreach (String file in nets)
            {
                FileStream fs = Network.OpenNetworkFile(file, out wasEncoded);
                if (fs == null)
                {
                    ErrorDialog ed = new ErrorDialog();
                    ed.post("Failed to load macro file {0}.", file);
                    return_code = false;
                }
                else
                {
                    bool asMacro;
                    StreamReader sr = new StreamReader(fs);
                    MacroDefinition.LoadMacroFile(sr, file, replace, out asMacro, asSystemMacro);
                    sr.Close();
                    Network.CloseNetworkFile(fs, wasEncoded);
                }
            }
            return return_code;
        }

        public MacroDefinition()
        {
            throw new Exception("Not yet implemented.");
        }
        public MacroDefinition(bool systemMacro) : base()
        {
            this.systemMacro = systemMacro;
            fileName = null;
            body = null;
            initialRead = false;
            updatingServer = false;
            category = new Symbol(0);
            if (!systemMacro)
                saveCmd = new SaveMacroCommand("saveMacroCommand",
                    DXApplication.theDXApplication.getCommandScope(),
                    true, this);
        }

        ~MacroDefinition()
        {
            if (body != null)
            {
                body.Definition = null;
                DXApplication.theDXApplication.macroList.Remove(body);
                if (!body.IsDeleted)
                    body = null;
            }
        }

        public Command getSaveCmd() { return saveCmd; }

        public virtual bool isDerivedFromMacro()
        {
            return true;
        }

        public override void finishDefinition()
        {
            // No implementation
        }

        public virtual void reference(MacroNode n)
        {
            if (referencingNodes == null)
                return;
            if (referencingNodes.Contains(n))
                return;
            referencingNodes.Add(n);
            return;
        }

        public virtual void dereference(MacroNode n)
        {
            if (referencingNodes == null)
                return;
            referencingNodes.Remove(n);
        }

        public virtual bool updateServer()
        {
            if (!loadNetworkBody())
                return false;

            if (body != null && !updatingServer)
            {
                //
                // There is a recursive loop between DXExecCtl.updateMacros(),
                // Network.sendValues(), MacroNode.sendValues() and 
                // this->updateServer() that we try and avoid here.   
                //
                updatingServer = true;
                DXApplication.theDXApplication.getExecCtl().updateMacros(false);
                updatingServer = false;
            }
            return (body != null);
        }

        /// <summary>
        /// setNetwork should only be used when creating a new macro from a	
        /// network which exists (isn't in a file or already read in), and 
        /// isn't the main network.  It should really only be called by 
        /// Network::makeMacro()
        /// </summary>
        /// <param name="net"></param>
        /// <returns></returns>
        public virtual bool setNetwork(Network net)
        {
            throw new Exception("Not yet implemented.");
        }

        public virtual bool setNodeDefinitions(MacroDefinition newDef)
        {
            foreach (MacroNode n in referencingNodes)
            {
                n.setDefinition(newDef);
                n.updateDefinition();
                if (newDef != this)
                    newDef.reference(n);
            }
            return true;
        }

        public bool removeInput(ParameterDefinition pd)
        {
            return this.removeIODef(inputDefs, pd);
        }
        public bool removeOutput(ParameterDefinition pd)
        {
            return this.removeIODef(outputDefs, pd);
        }
        public bool replaceInput(ParameterDefinition newPd, ParameterDefinition pd)
        {
            return replaceIODef(inputDefs, newPd, pd);
        }
        public bool replaceOutput(ParameterDefinition newPd, ParameterDefinition pd)
        {
            return replaceIODef(outputDefs, newPd, pd);
        }

        public ParameterDefinition getNonDummyInputDefinition(int n)
        {
            return getNonDummyIODefinition(inputDefs, n);
        }
        public ParameterDefinition getNonDummyOutputDefinition(int n)
        {
            return getNonDummyIODefinition(outputDefs, n);
        }

        /// <summary>
        /// Find the first available spot to place a new parameter in the 
        /// input/ouput. If there are dummy parameters in the list, then the 
        /// index of the first dummy is returned.  If no dummies, then N+1 is 
        /// returned, where N is the current number of items in the list.
        /// </summary>
        /// <returns></returns>
        public int getFirstAvailableInputPosition()
        {
            return getFirstAvailableIOPosition(inputDefs);
        }
        public int getFirstAvailableOutputPosition()
        {
            return getFirstAvailableIOPosition(outputDefs);
        }

        public virtual void openMacro()
        {
            throw new Exception("Not yet implemented.");
        }

        public bool IsReadingNet
        {
            get { return initialRead; }
        }

        public bool printNetworkBody(StreamWriter s, PrintType ptype)
        {
            if (!loadNetworkBody())
                return false;
            return body.printNetwork(s, ptype);
        }

        public bool loadNetworkBody()
        {
            if (body == null)
            {
                body = DXApplication.theDXApplication.newNetwork();
                body.Definition = this;
                initialRead = true;
                bool r = body.readNetwork(fileName);
                initialRead = false;
                if (!r)
                {
                    body.Definition = null;
                    body = null;
                    return false;
                }
                else
                    DXApplication.theDXApplication.macroList.Add(body);
            }
            return true;
        }

        public Network getNetwork()
        {
            return body;
        }

        #endregion

        #region Protected Methods
        protected void setFileName(String name)
        {
            fileName = name;
        }

        protected static bool LoadMacroFile(StreamReader file, String filename, bool replace)
        {
            bool wasMacro;
            return LoadMacroFile(file, filename, replace, out wasMacro, false);
        }
        protected static bool LoadMacroFile(StreamReader file, String filename, bool replace,
            out bool wasMacro)
        {
            return LoadMacroFile(file, filename, replace, out wasMacro, false);
        }
        protected static bool LoadMacroFile(StreamReader file, String filename, 
            bool replace, out bool wasMacro, bool asSystemMacro)
        {
            bool inMDF = false;
            int lineNo = 0;
            NodeDefinition nd = null;
            MacroDefinition oldMd = null, md = null;
            ParameterDefinition most_recent_param = null;

            wasMacro = false;

            if (DXApplication.theDXApplication.InDebugMode)
                Console.WriteLine("read macro from {0}\n", filename);

            SymbolManager symbolManager = SymbolManager.theSymbolManager;

            String line;
            while ((line = file.ReadLine()) != null)
            {
                lineNo++;

                if (line.StartsWith("// Begin MDF"))
                {
                    inMDF = true;
                }
                else if (inMDF && line.StartsWith("// End MDF"))
                {
                    inMDF = false;
                    break;
                }
                else if (!inMDF && line.StartsWith("// MODULE"))
                {
                    if (DXApplication.theDXApplication.InDebugMode)
                        Console.WriteLine("Macro rejected");
                    wasMacro = false;
                    goto error;
                }
                else if (inMDF && line.StartsWith("// MODULE"))
                {
                    wasMacro = true;
                    Regex regex = new Regex(@"// MODULE (.+)");
                    Match match = regex.Match(line);
                    if (!match.Success)
                    {
                        ErrorDialog ed = new ErrorDialog();
                        ed.post("Invalid MODULE comment at line {0} of {1}.",
                            lineNo, filename);
                        goto error;
                    }
                    String name = match.Groups[1].Value.Trim();
                    int index = 0;
                    if (!Utils.IsRestrictedIdentifier(name))
                    {
                        ErrorDialog ed = new ErrorDialog();
                        ed.post("Invalid macro name: {0} must start with a letter " +
                            "and contain only letters and numbers at line {0} of {1}.",
                            name, lineNo, filename);
                        goto error;
                    }

                    if (name == "main")
                    {
                        ErrorDialog ed = new ErrorDialog();
                        ed.post("The macro name must not be \"main\" " +
                            "at line {0} of {1}.", lineNo, filename);
                        goto error;
                    }

                    Symbol s = SymbolManager.theSymbolManager.getSymbol(name);
                    if (theNodeDefinitionDictionary.TryGetValue(s, out nd))
                    {
                        if (!nd.IsDerivedFromMacro())
                        {
                            ErrorDialog ed = new ErrorDialog();
                            ed.post("Standard module \"{0}\" cannot be redefined. " +
                                "Macro file \"{1}\" not loaded.", name, filename);
                            goto error;
                        }
                        else if (!replace)
                        {
                            goto error;
                        }
                        oldMd = (MacroDefinition)nd;
                    }
                    md = new MacroDefinition(asSystemMacro);
                    md.setName(name);
                    md.setFileName(filename);
                    if (nd != null)
                        md.setNextInstance(nd.newInstanceNumber());
                }
                else if (inMDF && line.StartsWith("// CATEGORY"))
                {
                    Regex regex = new Regex(@"// CATEGORY (.*)");
                    Match match = regex.Match(line);
                    if (!match.Success)
                    {
                        ErrorDialog ed = new ErrorDialog();
                        ed.post("Invalid CATEGORY comment at line {0} of {1}.",
                            lineNo, filename);
                        goto error;
                    }
                    md.Category = symbolManager.registerSymbol(match.Groups[1].Value);
                }
                else if (inMDF && line.StartsWith("// DESCRIPTION"))
                {
                    Regex regex = new Regex(@"// DESCRIPTION (.*)");
                    Match match = regex.Match(line);
                    if (!match.Success)
                    {
                        ErrorDialog ed = new ErrorDialog();
                        ed.post("Invalid DESCRIPTION comment at line {0} of {1}.",
                            lineNo, filename);
                        goto error;
                    }
                    md.Description = match.Groups[1].Value;
                }
                else if (inMDF && line.StartsWith("// INPUT"))
                {
                    Regex regex = new Regex(@"// INPUT ([^;]+); ([^;]+); ([^;]+);(.*)");
                    Match match = regex.Match(line);

                    if (!match.Success)
                    {
                        ErrorDialog ed = new ErrorDialog();
                        ed.post("Invalid INPUT comment at line {0} of {1}.",
                            lineNo, filename);
                        goto error;
                    }

                    String name = match.Groups[1].Value.Trim();
                    String types = match.Groups[2].Value.Trim();
                    String deflt = match.Groups[3].Value.Trim();

                    String attr = "";
                    regex = new Regex(@"(.*)[(.*)]");
                    match = regex.Match(name);
                    if (match.Success)
                    {
                        name = match.Groups[1].Value;
                        attr = match.Groups[2].Value;
                    }

                    if (!Utils.IsIdentifier(name))
                    {
                        ErrorDialog ed = new ErrorDialog();
                        ed.post("Invalid parameter name at line {0} of {1}.",
                            lineNo, filename);
                        goto error;
                    }

                    int visattr = 1;
                    if (attr.Contains("visible:"))
                    {
                        regex = new Regex(@"visible:\s*(\d+)");
                        match = regex.Match(attr);
                        if (match.Success)
                            visattr = Int32.Parse(match.Groups[1].Value);
                    }

                    ParameterDefinition pd = new ParameterDefinition(symbolManager.registerSymbol(name));
                    String descr = "";
                    if (match.Groups.Count == 5)
                    {
                        descr = match.Groups[4].Value.Trim();
                    }
                    if (descr.Contains(OLD_DUMMY_DESCRIPTION_STRING) ||
                        descr.Contains(ParameterDefinition.DUMMY_DESCRIPTION_STRING))
                        pd.setDummy(true);
                    else
                        pd.setDescription(descr);

                    switch (visattr)
                    {
                        case 0: pd.setDefaultVisibility(false); break;
                        case 1: pd.setDefaultVisibility(true); break;
                        case 2: pd.setViewability(false); break;
                    }
                    pd.markAsInput();
                    if (!ParseMDF.ParseMDFTypes(ref pd, types, lineNo))
                    {
                        goto error;
                    }

                    if (deflt[0] == '(')
                    {
                        pd.setDescriptiveValue(deflt);
                        if (deflt == "(none)")
                            pd.setRequired();
                    }
                    else if (!pd.setDefaultValue(deflt))
                    {
                        ErrorDialog ed = new ErrorDialog();
                        ed.post("Invalid default parameter value at line {0} of {1}.",
                        lineNo, filename);
                        pd = null;
                        goto error;
                    }
                    md.addInput(pd);
                    most_recent_param = pd;
                }
                else if (most_recent_param != null && line.Contains("// OPTIONS"))
                {
                    // must convert trailing \n to whitespace becuase 
                    // ParseMDFOptions expects it that way.
                    List<String> toks = Utils.StringTokenizer(line.Substring(11), ";", null);
                    foreach (String tok in toks)
                    {
                        most_recent_param.addValueOption(tok.Trim());
                    }
                }
                else if (inMDF && line.StartsWith("// OUTPUT"))
                {
                    String name = "", types = "", descr = "", attr = "";
                    Regex regex = new Regex(@"// OUTPUT ([^;]+); ([^;]+);([^;]*)");
                    Match match = regex.Match(line);
                    if (match.Success)
                    {
                        name = match.Groups[1].Value;
                        types = match.Groups[2].Value;
                        if (match.Groups[3].Captures.Count > 0)
                            descr = match.Groups[3].Value.Trim();
                    }
                    else
                    {
                        ErrorDialog ed = new ErrorDialog();
                        ed.post("Invalid OUTPUT comment at line {0} of {1}.",
                        lineNo, filename);
                        goto error;
                    }
                    regex = new Regex(@"(.+)[(.*)]");
                    match = regex.Match(name);
                    if (match.Success)
                    {
                        name = match.Groups[1].Value;
                        attr = match.Groups[2].Value;
                    }
                    if (!Utils.IsIdentifier(name))
                    {
                        ErrorDialog ed = new ErrorDialog();
                        ed.post("Invalid parameter name at line {0} of {1}.",
                        lineNo, filename);
                        goto error;
                    }
                    int visattr = 1;
                    if (attr.Contains("visible:"))
                    {
                        regex = new Regex(@"visible:\s*(\d+)");
                        match = regex.Match(attr);
                        if (match.Success)
                            visattr = Int32.Parse(match.Groups[1].Value);
                    }

                    ParameterDefinition pd = new ParameterDefinition(symbolManager.registerSymbol(name));
                    if (descr.Contains(OLD_DUMMY_DESCRIPTION_STRING) ||
                        descr.Contains(ParameterDefinition.DUMMY_DESCRIPTION_STRING))
                        pd.setDummy(true);
                    else
                        pd.setDescription(descr);

                    switch (visattr)
                    {
                        case 0: pd.setDefaultVisibility(false); break;
                        case 1: pd.setDefaultVisibility(true); break;
                        case 2: pd.setViewability(false); break;
                    }
                    pd.markAsOutput();
                    if (!ParseMDF.ParseMDFTypes(ref pd, types, lineNo))
                    {
                        goto error;
                    }
                    md.addOutput(pd);
                }
                else if (inMDF)
                {
                    WarningDialog wd = new WarningDialog();
                    wd.post("Encountered unrecognized MDF line at line {0} of '{1}', ignored.",
                        lineNo, filename);
                }
                if (line.StartsWith("// INPUT"))
                {
                    most_recent_param = null;
                }
            }
            if (md == null)
                goto error;

            md.completeDefinition();
            if (!asSystemMacro)
            {
                if (oldMd != null)
                {
                    oldMd.setNodeDefinitions(md);
                    ToolSelector.RemoveTool(oldMd.Category, oldMd.NameSymbol);

                    // Check if the macro is changed.
                    if (oldMd.body != null && oldMd.saveCmd != null &&
                        oldMd.body.SaveToFileRequired)
                    {
                        oldMd.saveCmd.setNext(null);
                        oldMd.saveCmd.execute();
                    }
                    else
                        oldMd = null;
                }
            }
            theNodeDefinitionDictionary[md.NameSymbol] = md;

            if (!asSystemMacro)
            {
                ToolSelector.AddTool(md.Category, md.NameSymbol, md);
                ToolSelector.UpdateCategoryList();
            }

            if (DXApplication.theDXApplication.InDebugMode)
                Console.WriteLine("Macro {0} accepted", md.NameString);

            return true;

        error:
            if (md != null)
                md = null;
            return false;
        }

        protected virtual bool removeIODef(List<ParameterDefinition> l, 
            ParameterDefinition pd)
        {
            l.Remove(pd);
            if (!initialRead)
                setNodeDefinitions(this);
            return true;
        }

        protected override bool addIODef(List<ParameterDefinition> l,
            ParameterDefinition pd)
        {
            bool result = true;
            if (!initialRead)
            {
                result = base.addIODef(l, pd) && setNodeDefinitions(this);
            }
            return result;
        }

        protected virtual bool replaceIODef(List<ParameterDefinition> l,
            ParameterDefinition newPd,
            ParameterDefinition pd)
        {
            int position = l.IndexOf(pd);
            if (position < 0)
                return false;
            l.RemoveAt(position);
            l.Insert(position, newPd);

            for (int i = l.Count; i > 0; i--)
            {
                pd = l[i - 1];
                if (pd.IsDummy)
                {
                    l.RemoveAt(i);
                }
                else
                    break;
            }

            if (!initialRead)
                setNodeDefinitions(this);

            return true;
        }

        /// <summary>
        /// Get the Nth input that is not a dummy parameter definition.
        /// </summary>
        /// <param name="l"></param>
        /// <param name="n"></param>
        /// <returns></returns>
        protected ParameterDefinition getNonDummyIODefinition(List<ParameterDefinition> l,
            int n)
        {
            throw new Exception("Not yet implemented.");
        }

        /// <summary>
        /// Allocate a new Node of the corresponding type.
        /// </summary>
        /// <param name="net"></param>
        /// <returns></returns>
        protected override Node newNode(Network net, int instance)
        {
            MacroNode d = new MacroNode(this, net, instance);
            return d;
        }

        #endregion 

        #region Private Methods
        /// <summary>
        /// Find the first available spot to place a new parameter in the given
        /// list (expected to be either inputDefs or outputDefs). If there are dummy
        /// parameters in the list, then the index of the first dummy is returned.
        /// If no dummies, then N+1 is returned, where N is the current number of
        /// items in the list.
        /// </summary>
        /// <param name="l"></param>
        /// <returns></returns>
        private int getFirstAvailableIOPosition(List<ParameterDefinition> l)
        {
            throw new Exception("Not yet implemented.");
        }
        #endregion
    }
}
