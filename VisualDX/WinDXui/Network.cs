using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;
using System.IO;
using System.Diagnostics;
using System.Globalization;
using System.Text.RegularExpressions;

namespace WinDX.UI
{
    public class Network
    {
        #region Support Classes/enums
        public class ParseState
        {
            public static Network network;
            public static String parse_file = null;
            public static bool error_occured;
            public static bool stop_parsing;
            public static bool issued_version_error;
            public static bool ignoreUndefinedModules;
            public static Dictionary<String, Definition> undefined_modules;
            public static Dictionary<String, Definition> redefined_modules;
            public static int parse_mode;
            public static bool main_macro_parsed;
            public static int lineno;

            internal ParseState() { }
            public void initializeForParse(Network n, int mode, 
                String filename) 
            {
                network = n;
                parse_mode = mode;
                parse_file = filename;
                node = null;
                parse_state = _PARSED_NONE;
                parse_sub_state = _SUB_PARSED_NONE;
                main_macro_parsed = false;
                error_occured = false;
                node_error_occured = false;
                stop_parsing = false;
                control_panel = null;
                lineno = 0;

                if (mode == _PARSE_NETWORK)
                {
                    issued_version_error = false;

                    if (undefined_modules != null)
                        undefined_modules.Clear();
                    else
                        undefined_modules = new Dictionary<string, Definition>();

                    if (redefined_modules != null)
                        redefined_modules.Clear();
                    else
                        redefined_modules = new Dictionary<string, Definition>();
                }
            }
            public void cleanupAfterParse() { parse_file = null; }
            public int parse_state;
            //
            // What did we just parse?  Was it a node or a decorator?  There are
            // stateful comments which could apply to either and we must know
            // wether to parseDecoratorComment or node->netParseComment.
            // group comments belong to either node or decorator.
            //
            public int parse_sub_state;
            public Node node;
            public int input_index;
            public int output_index;
            public bool node_error_occured;
            public ControlPanel control_panel;
        }

        public struct NetVersion
        {
            public Int16 major;
            public Int16 minor;
            public Int16 micro;
        }

        public struct DXVersion
        {
            public Int16 major;
            public Int16 minor;
            public Int16 micro;
        }


        #endregion

        #region Private Properties/Variables
        //
        // CommandInterfaces that use these two commands must arrange to set 
        // the instance number of the desired panel in the local data using
        // UIComponent::setLocalData().  Further, these are never de/activated()
        // and are created activated.  These are set up this way, because
        // anything that allows opening specific panels will have to be dynamic
        // (given an editor and the fact that the indices are kept in the
        // CommandInterface).  The CommandInterfaces that use these are created
        // in this->fillPanelCascade().
        private Command openPanelByInstanceCmd;
        private Command openPanelGroupByIndexCmd;

        //
        // Used by prepareFor/completeNewNetwork() and addNode() to defer
        // notifying the editor of the new nodes.  Instead we notify the editor
        // after the network is complete. 
        //
        private bool readingNetwork;

        //If the net came from a file and the file was encrypted, 
        // then this is set to TRUE.
        private bool netFileWasEncoded;

        private static Decorator lastObjectParsed;

        private ParseState parseState = new ParseState();
        private bool fileHadGetOrSetNodes;
        private static List<TransmitterNode> RenameTransmitterList;

        private Dictionary<String, GroupManager> groupManagers;

        private ControlPanel selectionOwner;

        #endregion

        #region Public Constructors
        /// <summary>
        /// THIS CONSTRUCTOR SHOULD NEVER BE CALLED FROM ANYWHERE BUT
        ///  DXApplication::newNetwork OR A SUBCLASS OF NETWORK.  ANY
        ///  SUBCLASSES CONSTRUCTOR SHOULD ONLY BE CALLED FROM A VIRTUAL
        ///  REPLACEMENT OF DXApplication::newNetwork.
        /// </summary>
        public Network() 
        {
            deleting = false;
            editor = null;
            prefix = null;
            description = null;
            comment = null;
            sequencer = null;
            fileName = null;
            readingNetwork = false;
            definition = null;
            remapInteractorOutputs = false;

            commandScope = new CommandScope();
            openAllPanelsCmd = new AccessNetworkPanelsCommand("openAllControlPanels",
                commandScope, false, this, AccessNetworkPanelsCommand.AccessPanelType.OpenAllPanels);

            // CommandInterfaces that use this must arrange to set the instance
            // number of the desired panel in the local data using 
            // UIComponent::setLocalData();

            openPanelByInstanceCmd = new AccessNetworkPanelsCommand("openPanelByInstance",
                commandScope, true, this, AccessNetworkPanelsCommand.AccessPanelType.OpenPanelByInstance);

            // CommandInterfaces that use this must arrange to set the instance
            // number of the desired panel in the local data using 
            // UIComponent::setLocalData();
            openPanelGroupByIndexCmd = new AccessNetworkPanelsCommand("openPanelGroupByIndex",
                commandScope, true, this, AccessNetworkPanelsCommand.AccessPanelType.OpenPanelGroupByIndex);

            closeAllPanelsCmd = new AccessNetworkPanelsCommand("closeAllControlPanels",
                commandScope, false, this, AccessNetworkPanelsCommand.AccessPanelType.CloseAllPanels);

            newCmd = new NewCommand("new", commandScope, false, this, null);

            saveAsCmd = new NoUndoNetworkCommand("saveCommand", commandScope,
                false, this, NoUndoNetworkCommand.NetworkCommandType.SaveNetworkAs);

            saveCmd = new NoUndoNetworkCommand("saveCommand", commandScope, false,
                this, NoUndoNetworkCommand.NetworkCommandType.SaveNetwork);

            saveCfgCmd = new NoUndoNetworkCommand("saveCfgCommand", commandScope, false,
                this, NoUndoNetworkCommand.NetworkCommandType.SaveConfiguration);

            openCfgCmd = new NoUndoNetworkCommand("openCfgCommand", commandScope, false,
                this, NoUndoNetworkCommand.NetworkCommandType.OpenConfiguration);

            setNameCmd = new NoUndoNetworkCommand("setNameCommand", commandScope, true,
                this, NoUndoNetworkCommand.NetworkCommandType.SetNetworkName);

            helpOnNetworkCmd = new NoUndoNetworkCommand("helpOnNetworkCommand", commandScope, false,
                this, NoUndoNetworkCommand.NetworkCommandType.HelpOnNetwork);

            panelGroupManager = new PanelGroupManager(this);
            panelAccessManager = new PanelAccessManager(this);

            // Set the activation of commands that depend on execution.
            // Remember to remove them in the destructor.

            DXApplication.theDXApplication.executingCmd.autoActivate(newCmd);
            DXApplication.theDXApplication.notExecutingCmd.autoActivate(newCmd);
            newCmd.autoActivate(DXApplication.theDXApplication.executeOnChangeCmd);

            deferrableRemoveNode = new DeferrableAction(Network.RemoveNodeWork, this);
            deferrableAddNode = new DeferrableAction(Network.AddNodeWork, this);
            deferrableSendNetwork = new DeferrableAction(Network.SendNetwork, this);

            selectionOwner = null;
            groupManagers = GroupManager.BuildTheGroupManagerDictionary(this);
            editorMessages = null;

            this.clear();
        }
        #endregion

        #region Protected Properties/Variables

        protected EditorWindow editor;
        protected List<ImageWindow> imageList = new List<ImageWindow>();
        protected List<ControlPanel> panelList = new List<ControlPanel>();
        protected NodeList nodeList = new NodeList();
        protected List<Decorator> decoratorList = new List<Decorator>();

        protected String description;
        protected String comment;
        protected Symbol category;
        protected Symbol name;
        protected String prefix;
        protected bool remapInteractorOutputs;

        protected DeferrableAction deferrableRemoveNode;
        protected DeferrableAction deferrableAddNode;
        protected DeferrableAction deferrableSendNetwork;

        protected CommandScope commandScope;
        protected Command openAllPanelsCmd;
        protected Command closeAllPanelsCmd;
        protected Command newCmd;
        protected Command saveAsCmd;
        protected Command saveCmd;
        protected Command saveCfgCmd;
        protected Command openCfgCmd;
        protected Command setNameCmd;
        protected Command helpOnNetworkCmd;

        protected bool dirty;
        protected bool fileDirty;
        protected String fileName;

        protected bool macro;
        protected MacroDefinition definition;
        protected bool deleting;

        protected Dialog setCommentDialog;
        protected Dialog helpOnNetworkDialog;

        protected int lastPanelInstanceNumber;
        protected PanelGroupManager panelGroupManager;
        protected PanelAccessManager panelAccessManager;

        protected int imageCount;
        protected DXVersion dxVersion;
        protected NetVersion netVersion;

        // the work space grid to be used by the editor.
        protected WorkSpaceInfo workSpaceInfo = new WorkSpaceInfo();


        #endregion

        #region Public Properties/Variables
        public const String NetExtension = ".net";
        public const String CfgExtension = ".cfg";
        public const String DEFAULT_MAIN_NAME = "main";

        public const int _PARSE_CONFIGURATION = 1;
        public const int _PARSE_NETWORK = 2;

        public const int _LEXER_RUNNING = 0;
        public const int _LEXER_INITIALIZE = 1;

        public const int _PARSED_NONE = 0;
        public const int _PARSED_NODE = 1;
        public const int _PARSED_PANEL = 2;
        public const int _PARSED_INTERACTOR = 3;
        public const int _PARSED_NETWORK_CFG = 4;
        public const int _PARSED_VCR = 5;
        public const int _PARSED_WORKSPACE = 6;
        public const int _PARSED_VERSION = 7;

        public const int _SUB_PARSED_NONE = 0;
        public const int _SUB_PARSED_NODE = 1;
        public const int _SUB_PARSED_DECORATOR = 2;

        public SequencerNode sequencer;

        public List<String> editorMessages;


        /// <summary>
        /// Determine if the network is in a state that can be saved to disk.
        /// If so, then return TRUE, otherwise return FALSE and issue an error.
        /// </summary>
        /// <returns></returns>
        public bool IsNetworkSavable
        {
            get { throw new Exception("Not Yet Implemented"); }
        }

        public bool IsDirty { get { return dirty; } }

        /// <summary>
        /// Is the network different than that on disk.  Before using this,
        /// be careful, to be sure you shouldn't be using saveToFileRequired() 
        /// instead.
        /// </summary>
        public bool IsFileDirty { get { return fileDirty; } }

        /// <summary>
        /// Return true if the network is different from that on disk, and the
        /// application allows saving of .net and .cfg files.
        /// </summary>
        public bool SaveToFileRequired
        {
            get
            {
                int count = NodeCount + decoratorList.Count;
                foreach (KeyValuePair<String, GroupManager> kvm in groupManagers)
                {
                    count += kvm.Value.GroupCount;
                }

                return IsFileDirty && (count > 0) &&
                    DXApplication.theDXApplication.appAllowsSavingNetFile(this) &&
                    DXApplication.theDXApplication.appAllowsSavingCfgFile() &&
                    !netFileWasEncoded;
            }
        }

        #endregion

        #region Public Static Methods
        internal static void GenerateModuleMessage(
            Dictionary<String, Definition> nodes, String msg, bool error) { }

        #endregion


        #region Protected Methods

        protected bool parse(StreamReader file) { return true;  }
        protected bool cfgParseComment(String name, String file, int lineno) 
        { return false; }
        protected void resetImageCount() { imageCount = 0; }

        /// <summary>
        /// Deletes a given panel from the panel list.
        /// Should you be using this->closeControlPanel(...).
        /// </summary>
        /// <param name="panel"></param>
        /// <returns></returns>
        protected bool deletePanel(ControlPanel panel) { return deletePanel(panel, false); }
        protected bool deletePanel(ControlPanel panel, bool destroyPanelsNow)
        {
            throw new Exception("Not Yet Implemented");
        }

        /// <summary>
        /// Do any work that is necessary to read in a new .cfg file and/or
        /// clear the network of any .cfg information.
        /// </summary>
        protected void clearCfgInformation() { clearCfgInformation(false); }
        protected void clearCfgInformation(bool destroyPanelsNow)
        {
            foreach (ControlPanel p in panelList)
                deletePanel(p, destroyPanelsNow);
            resetPanelInstanceNumber();
            panelGroupManager.clear();
            panelAccessManager.clear();

            foreach (Node node in nodeList)
                node.setDefaultCfgState();
        }


        /// <summary>
        /// Ask various windows to reset their titles.
        /// </summary>
        protected void resetWindowTitles()
        {
            DXWindow anchor = DXApplication.theDXApplication.getAnchor();
            bool anchor_reset = false;

            if (editor != null)
            {
                if (editor == anchor) anchor_reset = true;
                editor.resetWindowTitle();
            }

            foreach (ImageWindow iw in imageList)
            {
                if (iw == anchor)
                    anchor_reset = true;
                iw.resetWindowTitle();
            }

            if ((!anchor_reset) && (anchor != null))
            {
                if (anchor is DXAnchorWindow)
                {
                    DXAnchorWindow dxa = (DXAnchorWindow) anchor;
                    dxa.resetWindowTitle();
                }
            }
        }


        /// <summary>
        /// Do whatever is necessary to speed up the process of reading in a
        /// new network.  This includes letting the EditorWindow know by calling
        /// editor->prepareFor/completeNewNetwork().
        /// </summary>
        protected void prepareForNewNetwork()
        {
            if (Network.RenameTransmitterList != null)
                Network.RenameTransmitterList.Clear();

            deferrableAddNode.deferAction();
            deferrableRemoveNode.deferAction();

            if (editor != null)
                editor.prepareForNewNetwork();

            fileHadGetOrSetNodes = false;
        }
        protected void completeNewNetwork()
        {
            // This is to accomadate an optimization in addNode() in which nodes
            // are placed on the beginning of the list instead of the end.  This
            // should make finding connected nodes quicker, but leaves 
            // this->nodeList unsorted.
            if (readingNetwork)
                sortNetwork();

            // Let the editor know that the new network is done. 
            if (editor != null)
            {
                editor.installWorkSpaceInfo(ref workSpaceInfo);
                editor.completeNewNetwork();
            }

            resetWindowTitles();

            // Undefer the calls to changeNodeExistanceWork(), which may result in
            // a call to AddNodeWork().
            deferrableAddNode.undeferAction();
            deferrableRemoveNode.undeferAction();
        }


        /// <summary>
        /// Print comments and 'include' statements for the macros that are
        /// referenced in this network.  If nested is TRUE, then we don't print
        /// the 'include' statements.  Return TRUE on sucess or FALSE on failure.
        /// nested and processedMacros args are only really intended to be 
        /// used in the recursive calls (i.e. not by generic users).
        /// </summary>
        /// <param name="sw"></param>
        /// <param name="inline_define"></param>
        /// <param name="echoCallback"></param>
        /// <param name="echoClientData"></param>
        /// <returns></returns>
        protected virtual bool printMacroReferences(StreamWriter sw, bool inline_define,
            PacketIF.PacketIFCallback echoCallback, Object echoClientData)
        {
            throw new Exception("Not Yet Implemented");
        }

        /// <summary>
        /// THIS CONSTRUCTOR SHOULD NEVER BE CALLED FROM ANYWHERE BUT
        ///  DXApplication::newNetwork OR A SUBCLASS OF NETWORK.  ANY
        ///  SUBCLASSES CONSTRUCTOR SHOULD ONLY BE CALLED FROM A VIRTUAL
        ///  REPLACEMENT OF DXApplication::newNetwork.
        /// </summary>

        /// <summary>
        /// For editing operations which automatically chop arcs and replace
        /// them with transmitters/receivers.
        /// </summary>
        /// <param name="node"></param>
        /// <param name="pno"></param>
        /// <param name="trnsmtrs"></param>
        /// <param name="rcvrs"></param>
        /// <returns></returns>
        protected bool chopInputArk(Node node, int pno, Dictionary<String, NodeDefinition> trnsmtrs,
            Dictionary<String, NodeDefinition> rcvrs)
        {
            throw new Exception("Not Yet Implemented");
        }


        protected virtual bool parseDecoratorComment(String comment, String filename, int lineno)
        {
            throw new Exception("Not Yet Implemented");
        }

        #endregion

        #region Private Methods

        ~Network()
        {
            deleting = true;
            clear(true);

            DXApplication.theDXApplication.executingCmd.removeAutoCmd(newCmd);
            DXApplication.theDXApplication.notExecutingCmd.removeAutoCmd(newCmd);
        }

        // Parse all .net file comments.
        private void parseVersionComment(String comment, bool netfile)
        {
            int net_major = 0, net_minor = 0, net_micro = 0;
            Regex regex = new Regex(@" version: (\d+).(\d+).(\d+) \(format\), (\d+).(\d+).(\d+)");
            Match m = regex.Match(comment);

            if (netfile)
            {
                if (!m.Success)
                {
                    Regex regex2 = new Regex(@" version: (\d+).(\d+).(\d+)");
                    Match m2 = regex2.Match(comment);
                    if (!m2.Success)
                    {
                        ErrorDialog ed = new ErrorDialog();
                        ed.post("Invalid version comment at {0}:{1}", ParseState.parse_file,
                            ParseState.lineno);
                        ParseState.error_occured = true;
                        return;
                    }
                    net_major = Int32.Parse(m.Groups[1].ToString());
                    net_minor = Int32.Parse(m.Groups[2].ToString());
                    net_micro = Int32.Parse(m.Groups[3].ToString());
                }
                else
                {
                    net_major = Int32.Parse(m.Groups[1].ToString());
                    net_minor = Int32.Parse(m.Groups[2].ToString());
                    net_micro = Int32.Parse(m.Groups[3].ToString());
                    dxVersion.major = Int16.Parse(m.Groups[4].ToString());
                    dxVersion.minor = Int16.Parse(m.Groups[5].ToString());
                    dxVersion.micro = Int16.Parse(m.Groups[6].ToString());
                }
                netVersion.major = (short)net_major;
                netVersion.minor = (short)net_minor;
                netVersion.micro = (short)net_micro;
            }
            else
            {
                if (!m.Success)
                {
                    ErrorDialog ed = new ErrorDialog();
                    ed.post("Invalid version comment at {0}:{1}", ParseState.parse_file,
                        ParseState.lineno);
                    ParseState.error_occured = true;
                    return;
                }
            }

            if ((net_major > 2) && 
                (net_major > Int32.Parse(global::WinDX.UI.Resources.NETFILE_MAJOR_VERSION)))
            {
                String buf;
                if (netfile)
                {
                    if (IsMacro)
                    {
                        MacroDefinition md = getDefinition();
                        buf = "The macro " + md.NameString;
                    }
                    else
                        buf = "This visual program";
                }
                else
                    buf = "This configuration file";
                ErrorDialog ed = new ErrorDialog();
                buf += "was saved in an incompatible format by a release of " + 
                    DXApplication.theDXApplication.getInformalName() + " (version " +
                    dxVersion.major.ToString() + "." + dxVersion.minor.ToString() + "." +
                    dxVersion.micro.ToString() + ") that is more recent than this version (" + 
                    DXApplication.theDXApplication.getInformalName() +
                    global::WinDX.UI.Resources.MAJOR_VERSION + "." +
                    global ::WinDX.UI.Resources.MINOR_VERSION + "." +
                    global::WinDX.UI.Resources.MICRO_VERSION + ")" +
                    ". Contact your support center if you would like to obtain a version " +
                    "of " + DXApplication.theDXApplication.getInformalName() + "that can support" +
                    " this visual program.";

                ed.post(buf);
            }
        }

        private bool netParseComments(String comment, String file, int lineno)
        {
            // if .net node comment...
            // This signifies the beginning of the node comments
            if (comment.StartsWith(" node"))
            {
                netParseNodeComment(comment);
            }
            else if (comment.StartsWith(" version"))
            {
                netParseVersionComment(comment);
            }
            else if (comment.StartsWith(" MODULE"))
            {
                netParseMODULEComment(comment);
            }
            else if (comment.StartsWith(" CATEGORY"))
            {
                netParseCATEGORYComment(comment);
            }
            else if (comment.StartsWith(" pgroup assignment"))
            {
                Dictionary<String, GroupManager> dict = groupManagers;
                GroupManager gmgr;
                if (groupManagers.TryGetValue(ProcessGroupManager.ProcessGroup, out gmgr))
                    gmgr.parseComment(comment, ParseState.parse_file, ParseState.lineno, this);
            }
            else if (comment.StartsWith(" page assignment"))
            {
                GroupManager gmgr;
                if (groupManagers.TryGetValue(PageGroupManager.PageGroup, out gmgr))
                    gmgr.parseComment(comment, ParseState.parse_file, ParseState.lineno, this);
            }
            else if (comment.StartsWith(" DESCRIPTION"))
            {
                netParseDESCRIPTIONComment(comment);
            }
            else if (comment.StartsWith(" comment: "))
            {
                netParseCommentComment(comment);
            }
            else if (comment.StartsWith(" macro "))
            {
                netParseMacroComment(comment);
            }
            else if (comment == " network: end of macro body")
            {
                ParseState.main_macro_parsed = true;
                parseState.parse_state = _PARSED_NONE;
            }
            else if (comment.StartsWith(" decorator") ||
      comment.StartsWith(" annotation") ||
      comment.StartsWith(" resource"))
            {
                if (!parseDecoratorComment(comment, ParseState.parse_file,
                    ParseState.lineno))
                    ParseState.error_occured = true;
                else
                    this.parseState.parse_sub_state = _SUB_PARSED_DECORATOR;
            }
            else if (comment.Contains(" group:") &&
           this.parseState.parse_sub_state == _SUB_PARSED_DECORATOR)
            {
                if (!parseDecoratorComment(comment,
                    ParseState.parse_file, ParseState.lineno))
                    ParseState.error_occured = true;
            }
            else if (this.parseState.parse_state == _PARSED_NODE &&
                (parseState.parse_sub_state == _SUB_PARSED_NODE) &&
                comment.Contains(" group:") &&
                (parseState.node_error_occured == false))
            {
                if (!parseState.node.netParseComment(comment, ParseState.parse_file, ParseState.lineno))
                {
                    WarningDialog wd = new WarningDialog();
                    wd.post("Unrecognized comment at line {0} of file {1} (ignoring)",
                        lineno, file);
                }
            }
            else if (comment.StartsWith(" workspace"))
            {
                if (!workSpaceInfo.parseComment(comment, ParseState.parse_file,
                    ParseState.lineno))
                {
                    ParseState.error_occured = true;
                }
                parseState.parse_state = _PARSED_WORKSPACE;
            }
            else if (parseState.parse_state == _PARSED_NODE &&
           parseState.node_error_occured == false)
            {
                if (!parseState.node.netParseComment(comment,
                    ParseState.parse_file, ParseState.lineno))
                {
                    WarningDialog wd = new WarningDialog();
                    wd.post("Unrecognized comment at line {0} of file {1} (ignoring)",
                        lineno, file);
                }
                else
                {
                    parseState.parse_sub_state = _SUB_PARSED_NODE;
                }
            }
            else if (parseState.parse_state == _PARSED_WORKSPACE)
            {
                if (!workSpaceInfo.parseComment(comment, ParseState.parse_file, ParseState.lineno))
                {
                    WarningDialog wd = new WarningDialog();
                    wd.post("Unrecognized comment at line {0} of file {1} (ignoring)",
                        lineno, file);
                }
            }
            else if (parseState.parse_state == _PARSED_NODE)
            {
                WarningDialog wd = new WarningDialog();
                wd.post("Unrecognized comment at line {0} of file {1} (ignoring)",
                    lineno, file);
            }

            return ParseState.error_occured == false;
        }

        private void netParseMacroComment(String comment)
        {
            throw new Exception("Not Yet Implemented");
        }
        private void netParseMODULEComment(String comment)
        {
            Regex regex = new Regex(@" MODULE (.*)");
            Match m = regex.Match(comment);

            if (!m.Success)
            {
                ErrorDialog ed = new ErrorDialog();
                ed.post("Invalid MODULE comment at {0}:{1}",
                    ParseState.parse_file, ParseState.lineno);
                ParseState.error_occured = true;
                return;
            }

            name = SymbolManager.theSymbolManager.registerSymbol(m.Groups[1].ToString());
            if (prefix != null)
                prefix = null;
        }
        private void netParseVersionComment(String comment)
        {
            parseVersionComment(comment, true);
        }
        private void netParseCATEGORYComment(String comment)
        {
            Regex regex = new Regex(@" CATEGORY (.*)");
            Match m = regex.Match(comment);

            if (!m.Success)
            {
                ErrorDialog ed = new ErrorDialog();
                ed.post("Invalid CATEGORY comment at {0}:{1}",
                    ParseState.parse_file, ParseState.lineno);
                ParseState.error_occured = true;
                return;
            }
            setCategory(m.Groups[1].ToString(), false);
        }
        private void netParseDESCRIPTIONComment(String comment)
        {
            Regex regex = new Regex(@" DESCRIPTION (.*)");
            Match m = regex.Match(comment);

            if (!m.Success)
            {
                ErrorDialog ed = new ErrorDialog();
                ed.post("Invalid DESCRIPTION comment at {0}:{1}",
                    ParseState.parse_file, ParseState.lineno);
                ParseState.error_occured = true;
                return;
            }
            setDescription(m.Groups[1].ToString(), false);
        }
        private void netParseCommentComment(String comment)
        {
            if (ParseState.stop_parsing)
                return;

            this.comment = comment.Substring(10);
            setNetworkComment(this.comment);
        }
        private void netParseNodeComment(String comment)
        {
            if (!comment.StartsWith(" node "))
                return;

            if (parseState.node != null)
                addNode(parseState.node);

            parseState.node = null;
            parseState.node_error_occured = false;

            Regex regex = new Regex(@" node (.*)\[(\d+)\]:");
            Match m = regex.Match(comment);
            if (!m.Success)
            {
                ErrorDialog ed = new ErrorDialog();
                ed.post("Can't parse 'node' comment (file {0}, line {1})",
                    ParseState.parse_file, ParseState.lineno);
                parseState.node_error_occured = true;
                ParseState.error_occured = true;
                return;
            }

            NodeDefinition nd = null;
            Symbol s = SymbolManager.theSymbolManager.registerSymbol(m.Groups[1].ToString());
            if (!NodeDefinition.theNodeDefinitionDictionary.TryGetValue(s, out nd))
            {
                ParseState.undefined_modules.Add(m.Groups[1].ToString(), null);
                parseState.node_error_occured = true;
                ParseState.error_occured = true;
                return;
            }
            parseState.node = nd.createNewNode(this, Int32.Parse(m.Groups[2].ToString()));
            if (parseState.node == null)
            {
                ParseState.error_occured = true;
                parseState.node_error_occured = true;
                return;
            }

            // Determine if the node definition has changed.
            Regex r2 = new Regex(@"inputs = (\d+)");
            Match m2 = r2.Match(comment);
            if (m2.Success)
            {
                int inputs = Int32.Parse(m2.Groups[1].ToString());
                if (nd.IsUserTool && !nd.IsInputRepeatable && (inputs != nd.InputCount))
                {
                    ParseState.redefined_modules.Add(nd.NameString, null);
                }
            }
            r2 = new Regex(@"outputs = (\d+)");
            m2 = r2.Match(comment);
            if (m2.Success)
            {
                int outputs = Int32.Parse(m2.Groups[1].ToString());
                if (nd.IsUserTool && nd.IsOutputRepeatable && (outputs != nd.OutputCount))
                {
                    ParseState.redefined_modules.Add(nd.NameString, null);
                }
            }
            Symbol sym = nd.NameSymbol;
            if ((sym == NDAllocatorDictionary.GetNodeNameSymbol) ||
                (sym == NDAllocatorDictionary.SetNodeNameSymbol))
                fileHadGetOrSetNodes = true;

            parseState.input_index = 0;
            parseState.output_index = 0;

            // 'node' comment parsed successfully: set the parse state.
            parseState.parse_state = _PARSED_NODE;

            // Now ask the node to parse the rest of the information.
            if (!parseState.node.netParseComment(comment,
                ParseState.parse_file, ParseState.lineno))
            {
                WarningDialog wd = new WarningDialog();
                wd.post("Unrecognized comment at line {0} of file {1} (ignoring)",
                    ParseState.lineno, ParseState.parse_file);
            }
        }

        // Parse all .cfg file comments.
        private bool cfgParseComments(String comment, String file, int lineno)
        {
            if (comment.StartsWith(" interactor"))
                cfgParseInteractorComment(comment);
            else if (comment.StartsWith(" panel["))
                cfgParsePanelComment(comment);
            else if (comment.StartsWith(" version"))
                cfgParseVersionComment(comment);
            else if (getNetMajorVersion() < 3 && comment.StartsWith(" vcr"))
            {
                Node vcr = sequencer;
                if (vcr != null && vcr.cfgParseComment(comment, file, lineno))
                    parseState.parse_state = _PARSED_VCR;
                else
                    ParseState.error_occured = true;
            }
            else if (parseState.parse_state == _PARSED_NODE ||
       parseState.parse_state == _PARSED_INTERACTOR)
            {
                if (parseState.node_error_occured == false &&
                    !parseState.node.cfgParseComment(comment, file, lineno))
                {
                    WarningDialog wd = new WarningDialog();
                    wd.post("Unrecognized comment at line {0} of file {1} (ignoring)",
                        lineno, file);
                }
            }
            else if (parseState.parse_state == _PARSED_PANEL)
            {
                Debug.Assert(parseState.control_panel != null);
                if (!parseState.control_panel.cfgParseComment(comment, file, lineno))
                {
                    WarningDialog wd = new WarningDialog();
                    wd.post("Unrecognized comment at line {0} of file {1} (ignoring)",
                        lineno, file);
                }
            }
            else if (parseState.parse_state == _PARSED_NETWORK_CFG)
            {
                if (!cfgParseComment(comment, file, lineno))
                {
                    WarningDialog wd = new WarningDialog();
                    wd.post("Unrecognized comment at line {0} of file {1} (ignoring)",
                        lineno, file);
                }
            }
            // The 'time:' comment (in the .cfg file) signifies the beginning of the application's cfg comments.
            else if (comment.StartsWith(" time:"))
            {
                parseState.parse_state = _PARSED_NETWORK_CFG;
            }

            return (ParseState.error_occured == false);
        }
        private void cfgParsePanelComment(String comment)
        {
            throw new Exception("Not Yet Implemented");
        }
        private void cfgParseInteractorComment(String comment)
        {
            throw new Exception("Not Yet Implemented");
        }
        private void cfgParseNodeComment(String comment)
        {
            throw new Exception("Not Yet Implemented");
        }
        private void cfgParseVersionComment(String comment)
        {
            parseVersionComment(comment, false);
        }

        private int visitNodes(Node n)
        {
            for (int i = 1; i <= n.InputCount; i++)
            {
                if (n.isInputConnected(i))
                {
                    // Visit each upstream node. 
                    // Note, we don't need to sort the arcs to get a deterministic 
                    // sort, because we are going upstream instead of downstream
                    // (i.e. there is one arc per input).
                    foreach (Ark a in n.getInputArks(i))
                    {
                        int paramInd;
                        Node n2 = a.getSourceNode(out paramInd);
                        if (!n2.IsMarked)
                            visitNodes(n2);
                    }
                }
            }
            n.setMarked();
            nodeList.Add(n);

            return 0;
        }
        private bool markAndCheckForCycle(Node srcNode, Node dstNode)
        {
            throw new Exception("Not Yet Implemented");
        }

        // Static methods used by the DeferrableAction
        // class member below.
        private static void AddNodeWork(Network staticData, Node requestData)
        {
            staticData.changeExistanceWork(requestData, true);
        }

        private static void RemoveNodeWork(Network staticData, Node requestData)
        {
            staticData.changeExistanceWork(requestData, false);
        }

        // Static method used by the sendNetwork DeferrableAction
        // class member below.
        public static void SendNetwork(Network staticData, Node notUsed)
        {
            staticData.sendNetwork();
        }

        /// <summary>
        /// Add the given panel this network and if the instance number is 0
        /// then allocate a new instance number for the panel.
        /// </summary>
        /// <param name="p"></param>
        /// <returns></returns>
        private bool addPanel(ControlPanel p) { return addPanel(p, 0); }
        private bool addPanel(ControlPanel p, int instance)
        {
            throw new Exception("Not Yet Implemented");
        }

        /// <summary>
        /// Check version numbers using rules taken from ParseVersionComment
        /// If there is a problem post on Info Message
        /// </summary>
        /// <param name="netfile"></param>
        /// <param name="file"></param>
        /// <returns></returns>
        private bool versionMismatchQuery(bool netfile, String file)
        {
            throw new Exception("Not Yet Implemented");
        }

        /// <summary>
        /// Print decorator comments in the .net file.
        /// </summary>
        /// <param name="own"></param>
        private static void SetOwner(Object own)
        {
            throw new Exception("Not Yet Implemented");
        }
        private static void DeleteSelections(Object o)
        {
            throw new Exception("Not Yet Implemented");
        }
        private static void Select(Object o)
        {
            throw new Exception("Not Yet Implemented");
        }


        /// <summary>
        /// This is a helper function for optimizeNodeOutputCacheability() that
        /// returns a list of Nodes that are connected to the given output of the
        /// given node.  This would be trivial, except for Transmitters and 
        /// Receivers, In which case we need to traverse all Receivers for a 
        /// given Transmitter and all output arcs for each receiver.
        /// If destList is given, then we append the Nodes to that list, 
        /// otherwise we allocate one internally.  In either case, we return a 
        /// list.  In the latter case, the user should delete the returned list.
        /// </summary>
        /// <param name="src"></param>
        /// <param name="output_index"></param>
        /// <param name="destList"></param>
        /// <returns></returns>
        private static List<Node> GetDestinationNodes(Node src, int output_index,
            List<Node> destList) { return GetDestinationNodes(src, output_index, destList, false); }
        private static List<Node> GetDestinationNodes(Node src, int output_index,
            List<Node> destList, bool rcvrsOk)
        {
            throw new Exception("Not Yet Implemented");
        }


        /// <summary>
        /// Do a recursive depth-first search of this network for macro nodes.
        /// and append their MacroDefinitions to the given list.  The list will
        /// come back in depth-first order and will NOT contain duplicates.
        /// This has the side effect of loading the network bodies for all the
        /// returned MacroDefinitions.
        /// </summary>
        /// <param name="macros"></param>
        private void getReferencedMacros(ref List<Node> macros)
        {
            getReferencedMacros(ref macros, null);
        }
        private void getReferencedMacros(ref List<Node> macros, List<Node> visited)
        {
            throw new Exception("Not Yet Implemented");
        }

        #endregion

        #region Public Methods

        /// <summary>
        /// Adds a given image window to the image window list.
        /// Deletes a given image window from the image window list.
        /// </summary>
        /// <param name="image"></param>
        /// <returns></returns>
        public bool addImage(ImageWindow image)
        {
            throw new Exception("Not Yet Implemented");
        }
        public List<ImageWindow> getImageList() { return imageList; }
        public int getImageCount() { return imageList.Count; }
        public bool removeImage(ImageWindow image)
        {
            throw new Exception("Not Yet Implemented");
        }

        /// <summary>
        /// Posts the sequencer
        /// </summary>
        public void postSequencer()
        {
            throw new Exception("Not Yet Implemented");
        }

        public void setRemapInteractorOutputMode() { setRemapInteractorOutputMode(true); }
        public void setRemapInteractorOutputMode(bool val)
        {
            throw new Exception("Not Yet Implemented");
        }
        public bool isRemapInteractorOutputMode()
        {
            return remapInteractorOutputs;
        }

        /// <summary>
        /// Find a panel by index (was indexed from 1 in C++ vers.)
        /// </summary>
        /// <param name="index"></param>
        /// <returns></returns>
        public ControlPanel getPanelByIndex(int index)
        {
            Debug.Assert(index >= 0);
            return panelList[index];
        }
        public int getPanelCount() { return panelList.Count; }
        public ControlPanel getPanelByInstance(int instance)
        {
            throw new Exception("Not Yet Implemented");
        }
        public List<ControlPanel> getNonEmptyPanels()
        {
            throw new Exception("Not Yet Implemented");
        }

        /// <summary>
        /// Close the given panel indicated by panelInstance.
        /// If panelInstance is 0, unmanage all panels.
        /// If the given panel(s) contain 0 interactors, then also call 
        /// this->deletePanel() on the panel. 
        /// If do_unmanage is true, then unmanage the control panel(s).
        /// do_unmanage should be FALSE when call from the control panel's
        /// close callback.
        /// 
        /// May have to redo this to close all on -1 or something
        /// </summary>
        /// <param name="panelInstance"></param>
        public void closeControlPanel(int panelInstance) { closeControlPanel(panelInstance, true); }
        public void closeControlPanel(int panelInstance, bool do_unmanage)
        {
            throw new Exception("Not Yet Implemented");
        }


        /// <summary>
        /// Open the given panel indicated by panelInstance.
        /// If panelInstance is 0, manage all panels.
        /// 
        /// see close note
        /// </summary>
        /// <param name="panelInstance"></param>
        public void openControlPanel(int panelInstance)
        {
            if (panelInstance < 0)
            {
                foreach (ControlPanel panel in panelList)
                {
                    if (panel.IsStartup)
                        panel.Show();
                }
            }
            else if (panelInstance == 0)
            {
                foreach (ControlPanel panel in panelList)
                    panel.Show();
            }
            else
            {
                ControlPanel panel = getPanelByInstance(panelInstance);
                if (panel != null)
                    panel.Show();
            }
        }


        /// <summary>
        /// Open the given panel group indicated by groupIndex.
        /// Group indices are 1 based.
        /// </summary>
        /// <param name="groupIndex"></param>
        public void openControlPanelGroup(int groupIndex)
        {
            throw new Exception("Not Yet Implemented");
        }


        // Access routines:
        public EditorWindow getEditor()
        {
            return editor;
        }

        public Command getCloseAllPanelsCommand()
        {
            return closeAllPanelsCmd;
        }
        public Command getOpenAllPanelsCommand()
        {
            return openAllPanelsCmd;
        }
        public Command getNewCommand()
        {
            return newCmd;
        }
        public Command getSaveAsCommand()
        {
            return saveAsCmd;
        }
        public Command getSaveCommand()
        {
            return saveCmd;
        }

        public virtual Command getSaveWebPageCommand() { return null; }
        public virtual Command getSaveAppletCommand() { return null; }
        public virtual Command getSaveBeanCommand() { return null; }

        public Command getSaveCfgCommand()
        {
            return saveCfgCmd;
        }
        public Command getOpenCfgCommand()
        {
            return openCfgCmd;
        }
        public Command getSetNameCommand()
        {
            return setNameCmd;
        }
        public Command getHelpOnNetworkCommand()
        {
            return helpOnNetworkCmd;
        }
        public bool clear() { return clear(false); }
        public bool clear(bool destroyPanelsNow)
        {
            bool wasDeleting = deleting;
            deleting = true;

            prepareForNewNetwork();

            name = SymbolManager.theSymbolManager.registerSymbol(Network.DEFAULT_MAIN_NAME);

            if (description != null)
                description = null;

            if (fileName != null)
                fileName = null;

            setNetworkComment(null);
            if (prefix != null)
                prefix = null;

            // Delete the most basic elements first, since these may muck
            // around with some of the others (i.e. InteractorNodes access their
            // ControlPanels).  Delete each node from the network list before we
            // delete it so that there are not references to deleted nodes during
            // subsequent node deletions.

            nodeList.Clear();
            decoratorList.Clear();

            // Now clean up the control panels and other information in the .cfg .
            clearCfgInformation(destroyPanelsNow);

            // Delete all the image windows except the anchor.
            ImageWindow anchor = null;
            foreach (ImageWindow iw in imageList)
            {
                if (iw.IsAnchor)
                {
                    Debug.Assert(anchor == null);
                    anchor = iw;
                }
            }
            imageList.Clear();
            if (anchor != null)
                imageList.Add(anchor);

            if (helpOnNetworkDialog != null)
                helpOnNetworkDialog.Close();
            if (setCommentDialog != null)
                setCommentDialog.Close();

            foreach (KeyValuePair<String, GroupManager> gmgr in groupManagers)
                gmgr.Value.clear();

            if ((DXApplication.theDXApplication.network != null) &&
                (DXApplication.theDXApplication.macroList.Count == 0))
                NodeDefinition.ResetInstanceNumbers(NodeDefinition.theNodeDefinitionDictionary);

            category = Symbol.zero;
            macro = false;
            dirty = true;
            fileDirty = false;

            if ((definition != null) && (definition.IsReadingNet == false))
            {
                definition = null;
            }

            // Assume all networks are 0.0.0 unless the version comment in the
            // .net file indicates otherwise.  This assumes that when we write
            // out the .net file we use NETFILE_*_VERSION instead of these.
            netVersion.major = 0;
            netVersion.minor = 0;
            netVersion.micro = 0;

            // Assume all networks were written with dx version 1.0.0 unless the 
            // version comment in the .net file indicates otherwise.  This assumes 
            // that when we write out the .net file we use DX_*_VERSION instead of 
            // these.
            dxVersion.major = 0;
            dxVersion.minor = 0;
            dxVersion.micro = 0;

            completeNewNetwork();

            // Go back to the default work space configuration.  This must be done
            // AFTER the workspace widgets have been marked as being_destroyed in
            // order for the scrollbars to be removed.
            workSpaceInfo.setDefaultConfiguration();

            netFileWasEncoded = false;

            if (!wasDeleting)
                deleting = false;

            changeExistanceWork(null, false);
            return true;
        }


        // Net file format version access functions
        public int getDXMajorVersion() { return dxVersion.major; }
        public int getDXMinorVersion() { return dxVersion.minor; }
        public int getDXMicroVersion() { return dxVersion.micro; }

        // Net file format version access functions
        public int getNetMajorVersion() { return netVersion.major; }
        public int getNetMinorVersion() { return netVersion.minor; }
        public int getNetMicroVersion() { return netVersion.micro; }
        public void getVersion(out int maj, out int min, out int mic)
        {
            maj = netVersion.major;
            min = netVersion.minor;
            mic = netVersion.micro;
        }

        // Name and Category manipulations
        public void setDescription(String description) { setDescription(description, true); }
        public void setDescription(String description, bool markDirty)
        {
            throw new Exception("Not Yet Implemented");
        }
        public Symbol setCategory(String cat) { return setCategory(cat, true); }
        public Symbol setCategory(String cat, bool markDirty)
        {
            throw new Exception("Not Yet Implemented");
        }
        public Symbol setName(String n)
        {
            throw new Exception("Not Yet Implemented");
        }
        public String getDescriptionString()
        {
            throw new Exception("Not Yet Implemented");
        }
        public String getCategoryString()
        {
            return SymbolManager.theSymbolManager.getSymbolString(category);
        }
        public Symbol getCategorySymbol() { return category; }
        public String getNameString()
        {
            return SymbolManager.theSymbolManager.getSymbolString(name);
        }
        public Symbol getNameSymbol() { return name; }
        public String getPrefix()
        {
            if (prefix == null)
            {
                Debug.Assert(name != Symbol.zero);
                String s = SymbolManager.theSymbolManager.getSymbolString(name);
                Debug.Assert(s != null);
                prefix = s + "_";
            }
            return prefix;
        }
        public String getNetworkComment()
        {
            return comment;
        }
        public virtual void setNetworkComment(String s)
        {
            if (s != comment)
            {
                setDirty();
                if (s != null && s.Length > 0)
                    comment = s;
                else
                    comment = null;
            }
            if (comment != null && comment.Length > 0)
                helpOnNetworkCmd.activate();
            else
                helpOnNetworkCmd.deactivate(null);
        }

        // Printing/sending script representations of this network
        public virtual bool printNetwork(StreamWriter sw, PrintType dest)
        {
            throw new Exception("Not Yet Implemented");
        }

        public virtual bool printHeader(StreamWriter sw, PrintType dest)
        { return printHeader(sw, dest, null, null); }
        public virtual bool printHeader(StreamWriter sw, PrintType dest,
            PacketIF.PacketIFCallback echoCallback) { return printHeader(sw, dest, echoCallback, null); }
        public virtual bool printHeader(StreamWriter sw, PrintType dest,
            PacketIF.PacketIFCallback echoCallback, Object echoClientData)
        {
            DXPacketIF pif = DXApplication.theDXApplication.getPacketIF();
            String s;
            if (dest == PrintType.PrintFile || dest == PrintType.PrintCut || dest == PrintType.PrintCPBuffer)
            {
                s = "//\n";
                String datePatt = @"ddd MMM dd HH:mm:ss yyyy";
                s += "// time: " + System.DateTime.Now.ToString(datePatt);
                s += "//\n";
                s += String.Format("// version: {0}.{1}.{2} (format), {3}.{4}.{5} (DX)\n//\n",
                global::WinDX.UI.Resources.NETFILE_MAJOR_VERSION,
                global::WinDX.UI.Resources.NETFILE_MINOR_VERSION,
                global::WinDX.UI.Resources.NETFILE_MICRO_VERSION,
                global::WinDX.UI.Resources.MAJOR_VERSION,
                global::WinDX.UI.Resources.MINOR_VERSION,
                global::WinDX.UI.Resources.MICRO_VERSION);

                s += "//\n";
                sw.Write(s);
                if (echoCallback != null)
                    echoCallback(echoClientData, s);

                // Print the referenced
                bool inline_defined = false;

                if (dest == PrintType.PrintFile &&
                    !printMacroReferences(sw, false, echoCallback, echoClientData))
                    return false;

                s = "";

                if (IsMacro)
                    s += "// Begin MDF\n";

                s += "// MODULE " + SymbolManager.theSymbolManager.getSymbolString(name) + "\n";
                if (category != Symbol.zero)
                    s += "// CATEGORY " + (getCategoryString() == null ? " " : getCategoryString()) + "\n";
                if (description != null && description.Length > 0)
                    s += "// DESCRIPTION " + description + "\n";

                sw.Write(s);
                if (echoCallback != null)
                    echoCallback(echoClientData, s);

                s = "";

                if (IsMacro)
                {
                    for (int i = 1; i < getInputCount(); i++)
                    {
                        ParameterDefinition pd = getInputDefinition(i);
                        String[] strings = pd.getTypeStrings();
                        String types = "";
                        for (int j = 0; j < strings.Length; j++)
                        {
                            types += strings[j] + " or ";
                        }
                        types = types.Substring(0, types.Length - 4);

                        String visattr;
                        String dflt = pd.DefaultValue;
                        if (pd.IsRequired)
                            dflt = "(none)";
                        else if (dflt == null || dflt.Length == 0 || dflt == "NULL")
                            dflt = "(no default)";
                        if (!pd.IsViewable)
                            visattr = "[visible:2]";
                        else
                        {
                            if (pd.DefaultVisibility)
                                visattr = "";
                            else
                                visattr = "[visible:0]";
                        }
                        s += "// INPUT " + pd.NameString + visattr + "; " + types + "; " +
                            (dflt != null ? dflt : "(no default)") + "; " +
                            (pd.Description != null ? pd.Description : " ") + "\n";

                        String[] options = pd.getValueOptions();
                        if (options != null && options.Length > 0)
                        {
                            s += "// OPTIONS";
                            for (int k = 0; k < options.Length; k++)
                            {
                                s += " " + options[k] + " ;";
                            }
                            s = s.Substring(0, s.Length - 2);
                            s += "\n";
                        }
                    }
                    for (int i = 1; i < getOutputCount(); i++)
                    {
                        ParameterDefinition pd = getOutputDefinition(i);
                        {
                            String[] strings = pd.getTypeStrings();
                            String types = "";
                            for (int j = 0; j < strings.Length; j++)
                            {
                                types += strings[j] + " or ";
                            }
                            types = types.Substring(0, types.Length - 4);

                            String visattr = "";
                            if (!pd.IsViewable)
                                visattr = "[visible:2]";
                            else
                            {
                                if (pd.DefaultVisibility)
                                    visattr = "";
                                else
                                    visattr = "[visible:0]";
                            }

                            s += "// OUTPUT " + pd.NameString + visattr + "; " + types + "; " +
                                (pd.Description == null ? " " : pd.Description) + "\n";
                        }
                    }
                }
                s += "// End MDF\n";
                sw.Write(s);
                if (echoCallback != null)
                    echoCallback(echoClientData, s);

                s = "";

                // Print comments

                if (comment != null)
                {
                    String compcomment = comment;
                    if (compcomment.EndsWith("\n"))
                        compcomment = compcomment.Substring(0, compcomment.Length - 1);
                    Regex regex = new Regex(@"\n");
                    compcomment = regex.Replace(compcomment, "\n// comment: ");
                    s += "//\n// comment: ";
                    s += compcomment + "\n";
                }

                sw.Write(s);
                if (echoCallback != null)
                    echoCallback(echoClientData, s);

                s = "";

                Symbol psym = SymbolManager.theSymbolManager.getSymbol(ProcessGroupManager.ProcessGroup);
                foreach (KeyValuePair<String, GroupManager> kvp in this.groupManagers)
                {
                    if (psym == kvp.Value.getManagerSymbol())
                    {
                        if ((dest == PrintType.PrintExec) || (dest == PrintType.PrintFile))
                            if (!IsMacro)
                                if (!kvp.Value.printComment(sw))
                                    return false;
                    }
                    else
                    {
                        if (!kvp.Value.printComment(sw))
                            return false;
                    }
                }

                workSpaceInfo.printComments(sw);
                s = "//\n";
                sw.Write(s);
                if (echoCallback != null)
                    echoCallback(echoClientData, s);
            }

            s = "macro " + SymbolManager.theSymbolManager.getSymbolString(name) + "(\n";

            if (dest == PrintType.PrintFile || dest == PrintType.PrintCut || dest == PrintType.PrintCPBuffer)
            {
                sw.Write(s);
                if (echoCallback != null)
                    echoCallback(echoClientData, s);
            }
            else
            {
                pif.sendBytes(s);
            }
            s = "";

            for (int i = 1; IsMacro && i <= getInputCount(); i++)
            {
                ParameterDefinition pd = getInputDefinition(i);
                if (pd.NameSymbol == Symbol.zero)
                    s += (i == 1 ? " " : ",") + "dummy\n";
                else if (pd.DefaultDescriptive || pd.IsRequired || pd.DefaultValue == null ||
                    pd.DefaultValue == "NULL")
                    s += (i == 1 ? " " : ",") + pd.NameString + "\n";
                else
                    s += (i == 1 ? " " : ",") + pd.NameString + " = " + pd.DefaultValue + "\n";
            }
            s += ") -> (\n";

            if (dest == PrintType.PrintFile || dest == PrintType.PrintCut || dest == PrintType.PrintCPBuffer)
            {
                sw.Write(s);
                if (echoCallback != null)
                    echoCallback(echoClientData, s);
            }
            else
            {
                pif.sendBytes(s);
            }

            s = "";
            for (int i = 1; IsMacro && i <= getOutputCount(); i++)
            {
                ParameterDefinition pd = getOutputDefinition(i);
                if (pd.NameSymbol == Symbol.zero)
                    s += (i == 1 ? " " : ",") + "dummy\n";
                else
                    s += (i == 1 ? " " : ",") + pd.NameString + "\n";
            }

            s += ") {\n";
            if (dest == PrintType.PrintFile || dest == PrintType.PrintCut || dest == PrintType.PrintCPBuffer)
            {
                sw.Write(s);
                if (echoCallback != null)
                    echoCallback(echoClientData, s);
            }
            else
            {
                pif.sendBytes(s);
            }

            foreach (Node n in nodeList)
            {
                if (!n.netPrintBeginningOfMacroNode(sw, dest, prefix,
                    echoCallback, echoClientData))
                    return false;
            }
            return true;
        }

        public virtual bool printBody(StreamWriter sw, PrintType dest)
        { return printBody(sw, dest, null, null); }
        public virtual bool printBody(StreamWriter sw, PrintType dest,
            PacketIF.PacketIFCallback echoCallback) { return printBody(sw, dest, echoCallback, null); }
        public virtual bool printBody(StreamWriter sw, PrintType dest,
            PacketIF.PacketIFCallback echoCallback, Object echoClientData)
        {
            String prefix = getPrefix();

            if (editor != null && IsDirty)
                sortNetwork();

            resetImageCount();

            foreach (Node n in nodeList)
            {
                StandIn si = n.getStandIn();
                if (dest == PrintType.PrintFile ||
                    dest == PrintType.PrintExec ||
                    (dest == PrintType.PrintCPBuffer && selectionOwner.nodeIsInInstanceList(n)) ||
                    (dest == PrintType.PrintCut && si != null && si.IsSelected))
                {
                    if (!n.netPrintNode(sw, dest, prefix, echoCallback, echoClientData))
                        return false;
                }
            }

            if (!(dest == PrintType.PrintExec || dest == PrintType.PrintCPBuffer))
            {
                foreach (Decorator dec in decoratorList)
                {
                    if ((dest == PrintType.PrintFile) ||
                        (dest == PrintType.PrintCut && dec.IsSelected))
                    {
                        if (!dec.printComment(sw))
                            return false;
                    }
                }
            }

            return true;
        }


        public virtual bool printTrailer(StreamWriter sw, PrintType dest)
        { return printTrailer(sw, dest, null, null); }
        public virtual bool printTrailer(StreamWriter sw, PrintType dest,
            PacketIF.PacketIFCallback echoCallback) { return printTrailer(sw, dest, echoCallback, null); }
        public virtual bool printTrailer(StreamWriter sw, PrintType dest,
            PacketIF.PacketIFCallback echoCallback, Object echoClientData)
        {
            if (dest == PrintType.PrintFile || dest == PrintType.PrintCut || dest == PrintType.PrintCPBuffer)
            {
                sw.Write("// network: end of macro body\n");
            }

            foreach (Node n in nodeList)
            {
                if(!n.netPrintEndOfMacroNode(sw, dest, prefix, echoCallback, echoClientData))
                    return false;
            }

            String s = "}\n";
            DXPacketIF pif = DXApplication.theDXApplication.getPacketIF();
            if (dest == PrintType.PrintFile || dest == PrintType.PrintCut || dest == PrintType.PrintCPBuffer)
            {
                sw.Write(s);
                if (echoCallback == null)
                    echoCallback(echoClientData, s);
            }
            else
            {
                Debug.Assert(dest == PrintType.PrintExec);
                pif.sendBytes(s);
            }
            return true;
        }

        public virtual bool printValues(StreamWriter sw, PrintType dest)
        {
            throw new Exception("Not Yet Implemented");
        }
        public virtual bool sendNetwork()
        {
            if (deferrableSendNetwork.isActionDeferred())
            {
                deferrableSendNetwork.requestAction(null);
                return true;
            }

            DXPacketIF pi = DXApplication.theDXApplication.getPacketIF();
            if (pi == null)
                return true;

            PacketIF.PacketIFCallback cb = null;
            Object cbData = null;

            if (!netFileWasEncoded)
                cb = pi.getEchoCallback(ref cbData);

            pi.sendMacroStart();
            if (!printHeader(pi.getStreamWriter(), PrintType.PrintExec, cb, cbData))
                return false;
            if (!printBody(pi.getStreamWriter(), PrintType.PrintExec, cb, cbData))
                return false;
            if (!printTrailer(pi.getStreamWriter(), PrintType.PrintExec, cb, cbData))
                return false;
            pi.sendMacroEnd();

            clearDirty();
            return true;
        }
        public virtual bool sendValues() { return sendValues(false); }
        public virtual bool sendValues(bool force)
        {
            foreach (Node n in nodeList)
            {
                if (!n.sendValues(force))
                    return false;
            }
            return true;
        }


        /// <summary>
        /// Convert a filename (with or without corresponding extensions)
        /// to a filename with the correct extension.
        /// </summary>
        /// <param name="filename"></param>
        /// <returns></returns>
        public static String FilenameToNetname(String filename)
        {
            if (filename.EndsWith(".net", true, CultureInfo.InvariantCulture))
            {
                return filename;
            }
            else
                filename += ".net";
            return filename;
        }
        public static String FilenameToCfgname(String filename)
        {
            if (filename.EndsWith(".cfg", true, CultureInfo.InvariantCulture))
            {
                return filename;
            }
            else
                filename += ".cfg";
            return filename;
        }

        /// <summary>
        /// Save the network as a file in the .net and .cfg files
        /// </summary>
        /// <param name="name"></param>
        /// <returns></returns>
        public virtual bool saveNetwork(String name) { return saveNetwork(name, false); }
        public virtual bool saveNetwork(String name, bool force)
        {
            throw new Exception("Not Yet Implemented");
        }

        public bool openCfgFile(String name) { return openCfgFile(name, false, true); }
        public bool openCfgFile(String name, bool openStartup) { return openCfgFile(name, openStartup, true); }
        public bool openCfgFile(String name, bool openStartup, bool send)
        {
            bool ret = true;
            if (IsMacro)
                return true;

            String cfgfile = FilenameToCfgname(name);

            FileStream fs = null;
            try
            {
                fs = new FileStream(cfgfile, FileMode.Open);
            }
            catch (Exception)
            {

            }
            if (fs != null)
            {
                clearCfgInformation();
                parseState.initializeForParse(this, _PARSE_CONFIGURATION, cfgfile);
                readingNetwork = true;
                StreamReader sr = new StreamReader(fs);
                bool stopped_parsing = parse(sr);
                sr.Close();
                if (openStartup)
                    openControlPanel(-1);
                if (send)
                    sendValues(false);
                ret = !stopped_parsing;
                readingNetwork = false;
                parseState.cleanupAfterParse();
            }
            else
            {
                ret = false;
            }
            if (fs != null)
                fs.Close();

            return ret;
        }
        public bool saveCfgFile(String name)
        {
            throw new Exception("Not Yet Implemented");
        }

        /// <summary>
        /// markNetwork sets the flag marked[j] (0 based) if note j
        /// is connected to node i (0 based) in the d direction where d < 0
        /// means above (to its inputs), and d > 0 means below (to its outputs),
        /// and 0 means in both directions.
        /// </summary>
        /// <param name="marked"></param>
        /// <param name="i"></param>
        /// <param name="d"></param>
        /// <returns></returns>
        public int connectedNodes(bool marked, int i, int d)
        {
            throw new Exception("Not Yet Implemented");
        }
        public void sortNetwork()
        {
            if (nodeList.Count <= 1)
                return;

            List<Node> tmpNodeList = new List<Node>();
            // Sort the nodes so the visitation is deterministic.
            NodeNameComparer nnc = new NodeNameComparer();
            nodeList.Sort(nnc);
            for (int i = 0; i < nodeList.Count; i++)
            {
                tmpNodeList.Add(nodeList[i]);
                nodeList[i].clearMarked();
            }
            nodeList.Clear();

            // Now that we have a copy of the sorted list, visit all the nodes.
            foreach (Node n in tmpNodeList)
                if (!n.IsMarked)
                    visitNodes(n);
        }

        public class NodeNameComparer : IComparer<Node>
        {
            public int Compare(Node x, Node y)
            {
                int r = String.Compare(x.NameString, y.NameString);
                if (r == 0)
                    r = x.InstanceNumber - y.InstanceNumber;
                return r;
            }
        }

        public bool checkForCycle(Node srcNode, Node dstNode)
        {
            throw new Exception("Not Yet Implemented");
        }

        public virtual bool readNetwork(String netfile) { return readNetwork(netfile, null, false); }
        public virtual bool readNetwork(String netfile, String cfgfile)
        { return readNetwork(netfile, cfgfile, false); }
        public virtual bool readNetwork(String netfile, String cfgfile, bool ignoreUndefinedModules)
        {
            Decorator dec;
            bool enc;

            Network.ParseState.ignoreUndefinedModules = ignoreUndefinedModules;

            netfile = Network.FilenameToNetname(netfile);
            FileStream fs = OpenNetworkFile(netfile, out enc);
            StreamReader sr = new StreamReader(fs);

            // If there is an editor and this net file is encoded, then don't 
            // allow reading the .net.  Note, to catch all cases, we must also 
            // not allow creating of Editor's for encoded nets that have already
            // been read in (i.e. in image mode).  
            // See DXApplication::newNetworkEditor() and/or EditorWindow::manage().
            if (getEditor() != null && WasNetFileEncoded)
            {
                ErrorDialog ed = new ErrorDialog();
                ed.post("This visual program is encoded and is therefore not viewable with the VPE");
                if (sr != null)
                    sr.Close();
                sr = null;
            }

            if (sr == null)
            {
                clear();
                return false;
            }

            fileName = netfile;

            readingNetwork = true;
            prepareForNewNetwork();
            parseState.initializeForParse(this, _PARSE_NETWORK, netfile);
            bool parse_terminated = parseAntlr(sr);
            //bool parse_terminated = parse(sr);
            completeNewNetwork();
            readingNetwork = false;
            sr.Close();
            CloseNetworkFile(fs, enc);
            parseState.cleanupAfterParse();

            if (parse_terminated)
            {
                clear();
                return false;
            }

            // Parse the .cfg file if it exists.
            if (cfgfile == null || cfgfile == "")
            {
                cfgfile = netfile.Substring(0, netfile.LastIndexOf('.'));
                cfgfile += ".cfg";
            }
            openCfgFile(cfgfile, false, false);

            if (!DXApplication.theDXApplication.InEditMode &&
                !DXApplication.theDXApplication.appSuppressesStartupWindows())
            {
                openControlPanel(-1);

                if ((sequencer != null) && (sequencer.isStartup()))
                    postSequencer();
            }

            if (editor != null)
            {
                // turn line routing off before adding multiple vpe comments because
                // each one can cause a line reroute.
                bool hasdec = (decoratorList.Count > 0);
                if (hasdec)
                {
                    editor.beginPageChange();
                    foreach (Decorator decr in decoratorList)
                    {
                        editor.newDecorator(decr);
                    }
                    editor.endPageChange();
                }
            }
            setDirty();

            // Mark the network file dirty if there were redefined modules.
            if (Network.ParseState.redefined_modules.Count > 0)
                setFileDirty();
            else
                clearFileDirty();

            // Generate one collective error message for redefined modules.
            GenerateModuleMessage(Network.ParseState.redefined_modules,
                "The following tools have been redefined",
                false);

            String msg;
            // Generate one collective error message for undefined modules.
            if (getNameString() == "main")
                msg = "The main visual program contains undefined tools.\n" +
                    "Reload the visual program after loading the following tools";
            else
                msg = String.Format("Macro {0} contains undefined tools.\nReload macro {1} after loading the following tools",
                    getNameString(), getNameString());
            GenerateModuleMessage(Network.ParseState.undefined_modules, msg, true);

            // These three are 0.0.0 unless they were parsed out of the .net
            // which doesn't contain DX version numbers until DX 2.0.2
            int dx_major = getDXMajorVersion();
            int dx_minor = getDXMinorVersion();
            int dx_micro = getDXMicroVersion();
            int dx_version = Utils.VersionNumber(dx_major, dx_minor, dx_micro);

            // Version checking was added after version 2.0.2 of Data Explorer
            if (!ParseState.issued_version_error &&
                (dx_version > Utils.VersionNumber(2, 0, 2)))
            {
                int net_major = getNetMinorVersion();
                int net_minor = getNetMinorVersion();
                if (Utils.VersionNumber(net_major, net_minor, 0) >
                    Utils.VersionNumber(Int32.Parse(global::WinDX.UI.Resources.NETFILE_MAJOR_VERSION),
                Int32.Parse(global::WinDX.UI.Resources.NETFILE_MINOR_VERSION), 0))
                {
                    String name = DXApplication.theDXApplication.getInformalName();
                    WarningDialog wd = new WarningDialog();
                    wd.post("{0}{1} was saved in a format defined by a release of {2} (version {3}.{4}.{5}). Contact your support center if you would like to obtain a version of {6} that can fully support this visual program.",
                        (IsMacro ? "The macro " : "The visual program "),
                        (IsMacro ? getDefinition().NameString : ""),
                        name, dx_major, dx_minor, dx_micro,
                        global::WinDX.UI.Resources.MAJOR_VERSION,
                        global::WinDX.UI.Resources.MINOR_VERSION,
                        global::WinDX.UI.Resources.MICRO_VERSION,
                        name);
                }
            }
            renameTransmitters();
            return true;
        }

        public static FileStream OpenNetworkFile(String netfile, out bool wasEncoded)
        {
            String errmsg = null;
            return OpenNetworkFile(netfile, out wasEncoded, ref errmsg);
        }
        public static FileStream OpenNetworkFile(String netfile, out bool wasEncoded, ref String errmsg)
        {
            // No encoding included with this version yet.
            wasEncoded = false;
            FileStream fs;
            try
            {
                fs = new FileStream(netfile, FileMode.Open);
            }
            catch (Exception e)
            {
                errmsg = String.Format("Error opening file {0}: {1}", netfile, e.ToString());
                ErrorDialog ed = new ErrorDialog();
                ed.post(errmsg);
                return null;
            }

            return fs;
        }

        public FileStream openNetworkFile(String netfile)
        {
            String errmsg = null;
            return openNetworkFile(netfile, ref errmsg);
        }
        public FileStream openNetworkFile(String netfile, ref String errmsg)
        {
            return OpenNetworkFile(netfile, out netFileWasEncoded, ref errmsg);
        }


        public static void CloseNetworkFile(FileStream sw, bool wasEncoded)
        {
            if (wasEncoded)
            { throw new Exception("Encoded not handled yet."); }
            else
                sw.Close();
        }
        public void closeNetworkFile(FileStream sw)
        {
            CloseNetworkFile(sw, WasNetFileEncoded);
        }


        public bool netPrintNetwork(String name)
        {
            throw new Exception("Not Yet Implemented");
        }
        public bool cfgPrintNetwork(String name) { return cfgPrintNetwork(name, PrintType.PrintFile); }
        public bool cfgPrintNetwork(String name, PrintType dest)
        {
            throw new Exception("Not Yet Implemented");
        }

        public void setCPSelectionOwner(ControlPanel cp) { selectionOwner = cp; }
        public ControlPanel getSelectionOwner() { return selectionOwner; }
        public bool auxPrintNetwork()
        {
            throw new Exception("Not Yet Implemented");
        }

        public void setDirty()
        {
            dirty = true;
            fileDirty = true;

            DXApplication.theDXApplication.getExecCtl().terminateExecution();
        }
        public void clearDirty() { dirty = false; }
        public void setFileDirty() { fileDirty = true; }
        public void setFileDirty(bool val) { fileDirty = val; }
        public void clearFileDirty() { fileDirty = false; }


        /// <summary>
        /// Add a node to the network's node list.
        /// </summary>
        /// <param name="node"></param>
        /// <param name="where"></param>
        /// 
        public void addNode(Node node) { addNode(node, null); }
        public void addNode(Node node, EditorWorkSpace where)
        {
            setDirty();

            // This should make finding connected nodes quicker, but leaves 
            // this->nodeList unsorted (see this->completeNewNetwork()).

            if (readingNetwork)
                nodeList.Insert(0, node);
            else
                nodeList.Add(node);

            if (editor != null)
                editor.newNode(node, where);

            deferrableAddNode.requestAction(node);
        }
        public void deleteNode(Node node) { deleteNode(node, true); }
        public void deleteNode(Node node, bool undefer)
        {
            throw new Exception("Not Yet Implemented");
        }
        public Node findNode(Symbol name, int instance)
        {
            foreach (Node n in nodeList)
            {
                if ((n.getNameSymbol() == name) &&
                    ((n.InstanceNumber == instance) || (instance == 0)))
                    return n;
            }
            return null;
        }

        public Node findNode(String name) { int pos = 0; return findNode(name, ref pos, false); }
        public Node findNode(String name, ref int startpos) { return findNode(name, ref startpos, false); }
        public Node findNode(String name, ref int startpos, bool byLabel)
        {
            throw new Exception("Not Yet Implemented");
        }

        public void postSaveAsDialog(Form parent)
        {
            postSaveAsDialog(parent, null);
        }
        public void postSaveAsDialog(Form parent, Command cmd)
        {
            throw new Exception("Not yet implemented.");
        }
        public void postSaveCfgDialog(Form parent)
        {
            throw new Exception("Not yet implemented.");
        }

        public void postOpenCfgDialog(Form parent)
        {
            throw new Exception("Not yet implemented.");
        }
        public bool postNameDialog()
        {
            throw new Exception("Not Yet Implemented");
        }
        public void editNetworkComment()
        {
            throw new Exception("Not Yet Implemented");
        }
        public void postHelpOnNetworkDialog()
        {
            throw new Exception("Not Yet Implemented");
        }

        //
        // isMacro returns true if this network can be considered a macro.
        // canBeMacro returns true if there is nothing in the net that prevents
        // it from being a macro.
        // makeMacro makes this network a macro if do is true, else it makes it
        // be a "normal" net.
        public bool IsMacro
        {
            get
            {
                return definition != null;
            }
        }
        public bool CanBeMacro
        {
            get
            {
                throw new Exception("Not yet implemented");
            }
        }
        public bool makeMacro(bool make)
        {
            throw new Exception("Not yet implemented");
        }

        public ParameterDefinition getInputDefinition(int i)
        {
            throw new Exception("Not Yet Implemented");
        }
        public ParameterDefinition getOutputDefinition(int i)
        {
            throw new Exception("Not Yet Implemented");
        }
        public int getInputCount()
        {
            throw new Exception("Not Yet Implemented");
        }
        public int getOutputCount()
        {
            throw new Exception("Not Yet Implemented");
        }

        public bool moveInputPosition(MacroParameterNode n, int index)
        {
            throw new Exception("Not Yet Implemented");
        }
        public bool moveOutputPosition(MacroParameterNode n, int index)
        {
            throw new Exception("Not Yet Implemented");
        }

        public void setDefinition(MacroDefinition md) { throw new Exception("Not yet implemented"); }
        public MacroDefinition getDefinition() { throw new Exception("Not yet implemented"); }

        //
        // Colormap Management functions
        //
        public void openColormap(bool openAll) { throw new Exception("Not yet implemented"); }


        Node getNode(String name, int instance)
        {
            throw new Exception("Not Yet Implemented");
        }


        // Manipulate the panel instance numbers for panels in this network.
        public void resetPanelInstanceNumber()
        {
            lastPanelInstanceNumber = 0;
        }
        public int LastPanelInstanceNumber { get { return lastPanelInstanceNumber; }
            set { lastPanelInstanceNumber = value; }
        }
        public int NewPanelInstanceNumber { get { return ++lastPanelInstanceNumber; } }


        // Allocate a new control panel that belongs to this network.
        public ControlPanel newControlPanel() { return newControlPanel(0); }
        public ControlPanel newControlPanel(int instance)
        {
            throw new Exception("Not Yet Implemented");
        }

        public PanelAccessManager getPanelAccessManager()
        {
            return panelAccessManager;
        }
        public PanelGroupManager getPanelGroupManager()
        {
            return panelGroupManager;
        }
        public String FileName { get { return fileName; } }

        public WorkSpaceInfo getWorkSpaceInfo()
        {
            return workSpaceInfo;
        }

        /// <summary>
        /// Returns true if the caller is the last element of the image list.
        /// It is assumed that each member of this list will determine, during
        /// Node::prepareToSendNode, will call this to see if it's the last one.
        /// </summary>
        public bool IsLastImage
        {
            get { throw new Exception("Not Yet Implemented"); }
        }

        /// <summary>
        /// Given lists of old and new NodeDefinitions, redefine any nodes 
        /// in the current network.
        /// </summary>
        /// <param name="newdefs"></param>
        /// <param name="olddefs"></param>
        /// <returns></returns>
        public bool redefineNodes(Dictionary<Symbol, NodeDefinition> newdefs,
            ref Dictionary<Symbol, NodeDefinition> olddefs)
        {
            throw new Exception("Not Yet Implemented");
        }

        /// <summary>
        /// Find the first free index (indices start from 1) for nodes with the
        /// given name.
        /// Currently, this only works for Input/Output nodes.
        /// </summary>
        /// <param name="nodename"></param>
        /// <returns></returns>
        public int findFreeNodeIndex(String nodename)
        {
            throw new Exception("Not Yet Implemented");
        }

        public bool IsDeleted
        {
            get { return deleting; }
        }

        public int NodeCount
        {
            get
            {
                return nodeList.Count;
            }
        }

        /// <summary>
        /// Place menu items (ButtonInterfaces) in the CascadeMenu, that when 
        /// executed cause individually named panels and panel groups to be opened.
        /// If a PanelAccessManager, then only those ControlPanels defined to be 
        /// accessible are placed in the CascadeMenu.
        /// NOTE: to optimize this method, if the menu is returned deactivated()
        ///   it may not contain the correct contents and so should no be activated()
        ///   except through subsequent calls to this method.
        /// </summary>
        /// <param name="menu"></param>
        /// <param name="pam"></param>
        public void fillPanelCascade(ref ToolStripMenuItem menu, PanelAccessManager pam)
        {
            throw new Exception("Not Yet Implemented");
        }

        /// <summary>
        /// Merge two nets together, resolving instance collisions.  Delete the
        /// net being passed in.
        ///
        /// The stitch param (added 11/8/02) indicates what should be done when the
        /// incoming network has type/instance number conflicts with the existing
        /// network.  In the stitch case, the conflicts should be resolved by
        /// deleting the node in the incoming network and shifting its wires over
        /// to the conflicted node in the existing network.  The use of this is
        /// undoing a deletion of a set of nodes.
        /// </summary>
        /// <param name="network"></param>
        /// <param name="panels"></param>
        /// <param name="all"></param>
        /// <returns></returns>
        public bool mergeNetworks(Network network, List<Panel> panels, bool all)
        {
            return mergeNetworks(network, panels, all, false);
        }
        public bool mergeNetworks(Network network, List<Panel> panels, bool all, bool stitch)
        {
            throw new Exception("Not Yet Implemented");
        }

        public bool mergePanels(Network network)
        {
            throw new Exception("Not Yet Implemented");
        }

        // The decorators are held in this->decoratorList (no interactors in the list)
        public void addDecoratorToList(Decorator dec)
        {
            throw new Exception("Not Yet Implemented");
        }
        public void removeDecoratorFromList(Decorator dec)
        {
            throw new Exception("Not Yet Implemented");
        }
        public List<Decorator> getDecoratorList() { return decoratorList; }


        // get and set x,y,width,height of a net in the vpe
        public void setTopLeftPos(int x, int y)
        {
            throw new Exception("Not Yet Implemented");
        }
        public void getBoundingBox(out int x1, out int y1, out int x2, out int y2)
        {
            throw new Exception("Not Yet Implemented");
        }


        /// <summary>
        /// look through the network list and make a node list of the given class.  
        /// If classname == NULL, then all nodes are included in the list.
        /// If classname != NULL, and includeSubclasses = FALSE, then nodes must
        /// be of the given class and not derived from the given class.
        /// If no nodes were found then NULL is returned.
        /// The returned List must be deleted by the caller.
        /// </summary>
        /// <param name="classname"></param>
        /// <param name="includeSubclasses"></param>
        /// <returns></returns>
        /// 
        public List<Node> makeClassifiedNodeList(Type classtype)
        {
            return makeClassifiedNodeList(classtype, true);
        }
        public List<Node> makeClassifiedNodeList(Type classtype, bool includeSubclasses)
        {
            List<Node> nl = null;

            if (classtype != null && includeSubclasses == false)
                return nodeList.makeClassifiedNodeList(classtype);

            foreach (Node node in nodeList)
            {
                if (classtype == null ||
                    (includeSubclasses && node.GetType().ToString() == classtype.ToString()))
                {
                    if (nl == null) nl = new List<Node>();
                    nl.Add(node);
                }
            }
            return nl;
        }
        public List<ControlPanel> makeNamedControlPanelList(String name)
        {
            throw new Exception("Not Yet Implemented");
        }
        public List<Node> makeLabelledNodeList(String label)
        {
            throw new Exception("Not Yet Implemented");
        }


        /// <summary>
        /// Search the network for a node of the given class and return TRUE
        /// if found.
        /// </summary>
        /// <param name="classname"></param>
        /// <returns></returns>
        public bool containsClassOfNode(Type classname)
        {
            throw new Exception("Not Yet Implemented");
        }


        /// <summary>
        /// look through the network list and make a list of the nodes with
        /// the give name.
        /// If no nodes were found then NULL is returned.
        /// The returned List must be deleted by the caller.
        /// </summary>
        /// <param name="nodename"></param>
        /// <returns></returns>
        public List<Node> makeNamedNodeList(String nodename)
        {
            throw new Exception("Not Yet Implemented");
        }


        public bool IsReadingNetwork { get { return readingNetwork; } }

        /// <summary>
        /// Optimally set the output cacheability of all nodes within the network.
        /// We only operate on those that have writable cacheability.
        /// </summary>
        public void optimizeNodeOutputCacheability()
        {
            throw new Exception("Not Yet Implemented");
        }


        public bool WasNetFileEncoded { get { return netFileWasEncoded; } }

        /// <summary>
        /// See if the given label is unique among nodes requiring uniqueness.
        /// Return NUL(char*) if unique.  Otherwise return the node name of the
        /// guy with whom we have a conflict.
        /// </summary>
        /// <param name="passed_in"></param>
        /// <param name="label"></param>
        /// <returns></returns>
        public String nameConflictExists(UniqueNameNode passed_in, String label)
        {
            throw new Exception("Not Yet Implemented");
        }
        public String nameConflictExists(String label)
        {
            throw new Exception("Not Yet Implemented");
        }

        /// <summary>
        /// Maintain a list of transmitters which need fixing up after a network read.
        /// Older versions of dx weren't restrictive about name conflicts.  Now it
        /// you aren't allowed name conflicts among Transmitter,Receiver,Input,Output.
        /// So when reading a net with a name conflict, let it pass.  Just maintain a list
        /// of the conflicts and go back and fix them after the read.
        /// It's only necessary to fix the transmitters because changing them automatically
        /// fixes the receivers. (See renameTransmitters(), and RenameList.)
        /// If/when fixes are applied, we'll form a message string to show the user and
        /// store the string in a list.  EditorWindow can show the list if/when there
        /// is a vpe for the network.  No vpe/no display messages.
        /// </summary>
        /// <param name="tn"></param>
        public void fixupTransmitter(TransmitterNode tn)
        {
            throw new Exception("Not Yet Implemented");
        }
        public void renameTransmitters()
        {
            if (Network.RenameTransmitterList == null)
                return;
            int size = Network.RenameTransmitterList.Count;
            if (size == 0) return;

            String msg;
            if (size > 1)
            {
                if (IsMacro)
                    msg = String.Format("The following Transmitters in macro {0} were renamed due to name conflicts:",
                        getNameString());
                else
                    msg = "The following Transmitters were renamed due to name conflicts:";
            }

            foreach (TransmitterNode tn in Network.RenameTransmitterList)
            {
                String new_name;
                new_name = String.Format("{0}_xcvr", tn.LabelString);

            }
        }
        public void addEditorMessage(String msg)
        {
            throw new Exception("Not Yet Implemented");
        }
        public void showEditorMessages()
        {
            throw new Exception("Not Yet Implemented");
        }

        /// <summary>
        /// Called by Remove/AddNodeWork(), but can also be called directly.
        /// This had always been protected but is now public because we need to
        /// revisit command activation for reasons other than adding/removing nodes.
        /// </summary>
        /// <param name="n"></param>
        /// <param name="adding"></param>
        public virtual void changeExistanceWork(Node n, bool adding)
        {
            bool hasCfg = false;

            // If this isn't the 'main' network in dxui, then don't modify
            // the commands of DXApplication.  We arrive at this point in the
            // code whenever temporary networks are modified.  That shouldn't
            // change activation of application commands.  ...bug106

            bool modify_application_commands = (this == DXApplication.theDXApplication.network);

            List<Node> nl;

            if (adding)
            {
                if (n != null)
                {
                    nl = new List<Node>();
                    nl.Add(n);
                }
                else
                    nl = nodeList;

                foreach (Node node in nl)
                {
                    if (sequencer == null && node is SequencerNode)
                        sequencer = (SequencerNode) node;
                    node.initializeAfterNetworkMember();
                    if (modify_application_commands)
                    {
                        if (!DXApplication.theDXApplication.openAllColormapCmd.IsActive &&
                            node is ColormapNode)
                            DXApplication.theDXApplication.openAllColormapCmd.activate();
                    }
                    if (!hasCfg && node.hasCfgState())
                        hasCfg = true;
                }

                newCmd.activate();
                if (DXApplication.theDXApplication.appAllowsSavingNetFile(this))
                    this.saveAsCmd.activate();
                if (this.fileName != null)
                {
                    if (DXApplication.theDXApplication.appAllowsSavingNetFile(this))
                        this.saveCmd.activate();
                    if (hasCfg)
                    {
                        if (DXApplication.theDXApplication.appAllowsSavingCfgFile() &&
                            saveCfgCmd != null)
                            saveCfgCmd.activate();
                        if (openCfgCmd != null) openCfgCmd.activate();
                    }
                }
            }
            else
            {
                if (n != null)
                {
                    if (sequencer != null && n is SequencerNode)
                        sequencer = null;
                    if (DXApplication.theDXApplication.openAllColormapCmd.IsActive &&
                        n is ColormapNode)
                        if (modify_application_commands)
                        {
                            if (!containsClassOfNode(typeof(ColormapNode)))
                                DXApplication.theDXApplication.openAllColormapCmd.deactivate();
                        }
                }
                else
                {
                    if (modify_application_commands)
                    {
                        if (DXApplication.theDXApplication.openAllColormapCmd.IsActive &&
                            !containsClassOfNode(typeof(ColormapNode)))
                            DXApplication.theDXApplication.openAllColormapCmd.deactivate();
                    }
                    if (sequencer != null &&
                        !containsClassOfNode(typeof(SequencerNode)))
                        sequencer = null;
                }
                foreach (Node node in nodeList)
                {
                    if (!hasCfg)
                        break;
                    hasCfg = node.hasCfgState();
                }

                int count = nodeList.Count;
                int decorCount = decoratorList.Count;
                int groupCnt = 0;
                foreach (KeyValuePair<String, GroupManager> kvm in groupManagers)
                {
                    groupCnt += kvm.Value.GroupCount;
                }
                if ((count == 0) && (decorCount == 0) && (groupCnt == 0))
                {
                    newCmd.deactivate();
                    saveCmd.deactivate();
                    saveAsCmd.deactivate();
                }
                if ((count == 0) || !hasCfg)
                {
                    if (saveCfgCmd != null) saveCfgCmd.deactivate();
                    if (openCfgCmd != null) openCfgCmd.deactivate();
                }
            }

            nl = makeClassifiedNodeList(typeof(DisplayNode));
            if (nl != null)
            {
                DisplayNode dn;
                for(int i = 0; i< nl.Count-1; i++)
                {
                    dn = (DisplayNode) nodeList[i];
                    if (dn.isLastImage())
                        dn.setLastImage(false);
                }
                dn = (DisplayNode) nl[nl.Count - 1];
                if (dn.isLastImage())
                    dn.setLastImage(true);
            }
        }


        public Dictionary<String, GroupManager> getGroupManagers() { return groupManagers; }
        public void copyGroupInfo(Node node, List<Node> ln)
        {
            // Second param is a guess (need to figure out what it is a list of.)
            throw new Exception("Not Yet Implemented");
        }
        public void copyGroupInfo(Node node, Node dest)
        {
            // second param may need to be ref
            throw new Exception("Not Yet Implemented");
        }
        public bool chopArks(List<Node> selected, Dictionary<String, NodeDefinition> d1,
            Dictionary<String, NodeDefinition> d2)
        {
            throw new Exception("Not Yet Implemented");
        }
        public bool repleaceInputArks(List<Node> selected)
        {
            throw new Exception("Not Yet Implemented");
        }

        public virtual bool isJavified() { return false; }

        /// <summary>
        /// Name of the Network
        /// </summary>
        public String NameString
        {
            get { return SymbolManager.theSymbolManager.getSymbolString(name); }
        }

        public bool parseAntlr(StreamReader sr)
        {
            bool result;

            result = true;
            //try
            //{
                NetLexer lexer = new NetLexer(sr);
                NetParser parser = new NetParser(lexer);
                parser.start();
            //}
            //catch (Exception e)
            //{
            //    ErrorDialog ed = new ErrorDialog();
            //    ed.post("Unable to parse file {0}, reason: {1}", fileName, e.Message);
            //    result = false;
            //}

            if (ParseState.stop_parsing || ParseState.error_occured)
            {
                result = false;
            }

            // Only nodes found in the .net file are added to the network.
            if (result && ParseState.parse_mode == _PARSE_NETWORK &&
                parseState.node != null)
            {
                addNode(this.parseState.node);
                parseState.node = null;
            }
            else if ((parseState.node != null) && ParseState.parse_mode == _PARSE_NETWORK)
            {
                addNode(parseState.node);
                parseState.node = null;
            }

            return ParseState.stop_parsing;
        }

        public void ParseEndOfMacroDefinition()
        {
            if (ParseState.stop_parsing)
                return;
            ParseState.main_macro_parsed = true;
        }

        public void ParseFunctionID(String name)
        {
            if (ParseState.stop_parsing)
                return;

            // Suppress further processing if the first macro has already been parsed.
            if (ParseState.main_macro_parsed)
                return;

            this.parseState.output_index = 0;
        }

        public void ParseComment(String comment)
        {
            // Suppress further processing if first macro has already been parsed.
            if (ParseState.main_macro_parsed)
                return;

            // If black comment
            if (comment == null || comment.Trim().Length == 0)
                return;

            if (ParseState.parse_mode == _PARSE_NETWORK)
                this.netParseComments(comment, ParseState.parse_file, ParseState.lineno);
            else if (ParseState.parse_mode == _PARSE_CONFIGURATION)
                this.cfgParseComment(comment, ParseState.parse_file, ParseState.lineno);
        }

        public void ParseRValue(String name)
        {
            bool parse_error = false;
            String macro, str, type;
            int instance, parameter;

            if (this.parseState.node == null || ParseState.stop_parsing)
                return;

            if (ParseState.main_macro_parsed)
                return;

            List<String> toks = Utils.StringTokenizer(name, "_", new string[] { "" });
            if (toks.Count != 5)
                parse_error = true;

            macro = toks[0];
            str = toks[1];
            instance = Int32.Parse(toks[2]);
            type = toks[3];
            parameter = Int32.Parse(toks[4]);

            if (parse_error || type == "out")
                return;

            Node n;
            bool found = false;
            Symbol s_of_out = SymbolManager.theSymbolManager.registerSymbol(str);
            n = findNode(s_of_out, instance);
            if (n != null)
            {
                if (n.OutputCount < parameter)
                {
                    ErrorDialog ed = new ErrorDialog();
                    ed.post("Cannot connect output {0} of {1} to {2}, too many outputs (in {3}, line {4})",
                        parameter, str, this.parseState.node.NameString,
                        ParseState.parse_file, ParseState.lineno);
                }
                else if (this.parseState.node.InputCount < 1)
                {
                    ErrorDialog ed = new ErrorDialog();
                    ed.post("Cannot connect input {0} of {1} to {2}, too many inputs (in {3}, line {4})",
                        this.parseState.input_index, this.parseState.node.NameString, str,
                        ParseState.parse_file, ParseState.lineno);

                }
                else
                {
                    new Ark(n, parameter, this.parseState.node, 1);
                    this.parseState.node.setInputVisibility(1, true);
                    n.setOutputVisibility(parameter, true);
                }
                found = true;
            }
            if (!found && ParseState.ignoreUndefinedModules)
            {
                ParseState.undefined_modules.Add(str, null);
                ParseState.error_occured = true;
                return;
            }
        }

        public void ParseStringAttribute(String name, String value)
        {
            if (ParseState.stop_parsing)
                return;

            if (name != "pgroup")
                return;

            this.parseState.node.addToGroup(value, 
                SymbolManager.theSymbolManager.getSymbol(ProcessGroupManager.ProcessGroup));

        }

        public void ParseIntAttribute(String name, int value)
        {
            if (this.parseState.node == null || ParseState.stop_parsing)
                return;

            if (this.parseState.output_index > 0)
            {
                if (name == "cache")
                {
                    switch (value)
                    {
                        case 0:
                            parseState.node.setOutputCacheability(parseState.output_index,
                                Cacheability.ModuleNotCached);
                            break;
                        case 1:
                            parseState.node.setOutputCacheability(parseState.output_index,
                                Cacheability.ModuleFullyCached);
                            break;
                        case 2:
                            parseState.node.setOutputCacheability(parseState.output_index,
                                Cacheability.ModuleCacheOnce);
                            break;
                    }
                }
            }
            else if (parseState.parse_state == _PARSED_NODE)
            {
                if (name == "cache")
                {
                    switch (value)
                    {
                        case 0:
                            parseState.node.setNodeCacheability(Cacheability.ModuleNotCached);
                            break;
                        case 1:
                            parseState.node.setNodeCacheability(Cacheability.ModuleFullyCached);
                            break;
                        case 2:
                            parseState.node.setNodeCacheability(Cacheability.ModuleCacheOnce);
                            break;
                    }
                }
            }
        }

        public void ParseArgument(String name, bool isVarname)
        {
            String macro, module = "", type = "";
            int instance = 0, parameter = 0;

            bool parse_error = false;

            if (ParseState.stop_parsing || ParseState.main_macro_parsed)
                return;

            if (this.parseState.node == null)
                return;

            this.parseState.input_index++;

            if (!isVarname)
                return;

            List<String> toks = Utils.StringTokenizer(name, "_", new string[] { "" });
            if (toks.Count == 5)
            {
                macro = toks[0];
                module = toks[1];
                instance = Int32.Parse(toks[2]);
                type = toks[3];
                parameter = Int32.Parse(toks[4]);
            }
            else if (toks.Count == 4)
            {
                macro = "";
                module = toks[0];
                instance = Int32.Parse(toks[1]);
                type = toks[2];
                parameter = Int32.Parse(toks[3]);
            }
            else
                parse_error = true;

            if (parse_error && name != "NULL")
            {
                ErrorDialog ed = new ErrorDialog();
                ed.post("Error parsing tool input {0} (in {1}, line {2})",
                    name, ParseState.parse_file, ParseState.lineno);
                ParseState.error_occured = true;
                return;
            }

            if (type != "out")
            {
                if (type != "in")
                {
                    ErrorDialog ed = new ErrorDialog();
                    ed.post("Error parsing tool input {0} (in {1}, line {2})",
                        name, ParseState.parse_file, ParseState.lineno);
                    ParseState.error_occured = true;
                }
                return;
            }

            // If this node does not have enough inputs, and they were not added
            // earlier because this is a .net without the number of inputs in the 
            // comment, then add a set of input repeats.
            if (this.parseState.input_index >
                this.parseState.node.InputCount)
            {
                if (this.parseState.node.isInputRepeatable() &&
                    getNetMajorVersion() == 0)
                {
                    this.parseState.node.addInputRepeats();
                }
                else
                {
                    ErrorDialog ed = new ErrorDialog();
                    ed.post("Node {0} had unexpeceted number of inputs, file {1}, line {2}",
                        this.parseState.node.NameString,
                        ParseState.parse_file, ParseState.lineno);
                    ParseState.error_occured = true;
                    return;
                }
            }

            // The following is for 'out' input parameters ONLY!

            Symbol s_of_out = SymbolManager.theSymbolManager.registerSymbol(module);
            //  Skip any nodes that are 'connected to themselves' such as
            //  the Colormap module which does something like the following... 
            //    Colormap_1_out_1 = f(a);
            //    Colormap_1_out_1 = g(Colormap_1_out_1);
            //		....
            //  If the names and instances are the same then we assume we have
            //  the above situation.
            if ((this.parseState.node.getNameSymbol() == s_of_out) &&
                parseState.node.InstanceNumber == instance)
                return;

            Node n = null;
            bool found = false;

            n = this.findNode(s_of_out, instance);
            if (n != null)
            {
                if (n.OutputCount < parameter)
                {
                    ErrorDialog ed = new ErrorDialog();
                    ed.post("Cannot connect output {0} of {1} to {2}, too many outputs (in {3}, line {4}",
                        parameter, module, parseState.node.NameString,
                        ParseState.parse_file, ParseState.lineno);
                }
                else if (this.parseState.node.InputCount <
                    this.parseState.input_index)
                {
                    ErrorDialog ed = new ErrorDialog();
                    ed.post("Cannot connect input {0} of {1} to {2}, too many inputs (in {3}, line {4})",
                        parseState.input_index, parseState.node.NameString,
                        module, ParseState.parse_file, ParseState.lineno);
                }
                else
                {
                    // Connect output parameter to input of this.parseState.node
                    new Ark(n, parameter, this.parseState.node, this.parseState.input_index);
                    this.parseState.node.setInputVisibility(this.parseState.input_index, true);
                    n.setOutputVisibility(parameter, true);
                }
                found = true;
            }
            if (!found && ParseState.ignoreUndefinedModules)
            {
                ParseState.undefined_modules.Add(module, null);
                ParseState.error_occured = true;
                return;
            }
        }

        public void ParseLValue(String name)
        {
            if (ParseState.stop_parsing)
                return;

            if (ParseState.main_macro_parsed)
                return;

            if (name.Contains("_out_"))
                ++parseState.output_index;
        }
        #endregion
    }
}
