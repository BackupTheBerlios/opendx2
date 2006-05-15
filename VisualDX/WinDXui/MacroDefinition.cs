using System;
using System.Collections.Generic;
using System.Text;
using System.IO;

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
        
        protected List<Node> referencingNodes;

        protected bool initialRead;
        protected bool updatingServer; // Are we calling DXExecCtl.updateMacros()

        #endregion

        #region Public Instance Variables

        public String FileName
        {
            get { return fileName; }
        }

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
            throw new Exception("Not yet implemented.");
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
            String errmsg = null;
            return LoadMacroDirectories(path, false, ref errmsg, false);
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
                StreamReader sw = Network.OpenNetworkFile(file, out wasEncoded);
                if (sw == null)
                {
                    ErrorDialog ed = new ErrorDialog();
                    ed.post("Failed to load macro file {0}.", file);
                    return_code = false;
                }
                else
                {
                    bool asMacro;
                    MacroDefinition.LoadMacroFile(sw, file, replace, out asMacro, asSystemMacro);
                    Network.CloseNetworkFile(sw, wasEncoded);
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
                body.setDefinition(null);
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

        public bool printNetworkBody(Stream s, PrintType ptype)
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
                body.setDefinition(this);
                initialRead = true;
                bool r = body.readNetwork(fileName);
                initialRead = false;
                if (!r)
                {
                    body.setDefinition(null);
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
            if (DXApplication.theDXApplication.InDebugMode)
                Console.WriteLine("read macro from {0}\n", filename);

            SymbolManager symbolManager = SymbolManager.theSymbolManager;

            throw new Exception("Not yet implemented.");

        }

        protected virtual bool removeIODef(List<ParameterDefinition> l, 
            ParameterDefinition pd)
        {
            throw new Exception("Not yet implemented.");
        }

        protected override bool addIODef(List<ParameterDefinition> l,
            ParameterDefinition pd)
        {
            throw new Exception("Not yet implemented.");
        }

        protected virtual bool replaceIODef(List<ParameterDefinition> l,
            ParameterDefinition newPd,
            ParameterDefinition pd)
        {
            throw new Exception("Not yet implemented.");
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
        protected override Node newNode(Network net)
        {
            return newNode(net, -1);
        }
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
