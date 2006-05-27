using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;
using System.IO;
using System.Diagnostics;

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

            ParseState() { }
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

        private ParseState parseState;
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
        public bool saveToFileRequired { get { throw new Exception("Not Yet Implemented"); } }

        #endregion

        #region Public Static Methods
        internal static void GenerateModuleMessage(
            Dictionary<String, Definition> nodes, String msg, bool error) { }

        #endregion

        #region Public Instance Methods

        public String getFileName() { return ""; }

        #endregion

        #region Protected Methods

        protected bool parse(String filename) { return false;  }
        protected bool cfgParseComment(String name, String file, int lineno) 
        { return false; }
        protected void resetImageCount() { throw new Exception("Not Yet Implemented"); }

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

        // Methods for extern "C" functions reference by yacc.
        private void parseComment(String comment)
        {
            throw new Exception("Not Yet Implemented");
        }
        private void parseFunctionID(String name)
        {
            throw new Exception("Not Yet Implemented");
        }
        private void parseArgument(String name, bool isVarname)
        {
            throw new Exception("Not Yet Implemented");
        }
        private void parseLValue(String name)
        {
            throw new Exception("Not Yet Implemented");
        }
        private void parseRValue(String name)
        {
            throw new Exception("Not Yet Implemented");
        }
        private void parseStringAttribute(String name, String value)
        {
            throw new Exception("Not Yet Implemented");
        }
        private void parseIntAttribute(String name, String value)
        {
            throw new Exception("Not Yet Implemented");
        }
        private void parseEndOfMacroDefinition()
        {
            throw new Exception("Not Yet Implemented");
        }

        // Parse all .net file comments.
        private void parseVersionComment(String comment, bool netfile)
        {
            throw new Exception("Not Yet Implemented");
        }
        private bool netParseComments(String comment, String file, int lineno)
        {
            throw new Exception("Not Yet Implemented");
        }
        private void netParseMacroComment(String comment)
        {
            throw new Exception("Not Yet Implemented");
        }
        private void netParseMODULEComment(String comment)
        {
            throw new Exception("Not Yet Implemented");
        }
        private void netParseVersionComment(String comment)
        {
            throw new Exception("Not Yet Implemented");
        }
        private void netParseCATEGORYComment(String comment)
        {
            throw new Exception("Not Yet Implemented");
        }
        private void netParseDESCRIPTIONComment(String comment)
        {
            throw new Exception("Not Yet Implemented");
        }
        private void netParseCommentComment(String comment)
        {
            throw new Exception("Not Yet Implemented");
        }
        private void netParseNodeComment(String comment)
        {
            throw new Exception("Not Yet Implemented");
        }

        // Parse all .cfg file comments.
        private bool cfgParseComments(String comment, String file, int lineno)
        {
            throw new Exception("Not Yet Implemented");
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
            throw new Exception("Not Yet Implemented");
        }

        private int visitNodes(Node n)
        {
            throw new Exception("Not Yet Implemented");
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
            throw new Exception("Not Yet Implemented");
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
            throw new Exception("Not Yet Implemented");
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
            throw new Exception("Not Yet Implemented");
        }

        public virtual bool printBody(StreamWriter sw, PrintType dest)
        { return printBody(sw, dest, null, null); }
        public virtual bool printBody(StreamWriter sw, PrintType dest,
            PacketIF.PacketIFCallback echoCallback) { return printBody(sw, dest, echoCallback, null); }
        public virtual bool printBody(StreamWriter sw, PrintType dest,
            PacketIF.PacketIFCallback echoCallback, Object echoClientData)
        {
            throw new Exception("Not Yet Implemented");
        }


        public virtual bool printTrailer(StreamWriter sw, PrintType dest)
        { return printTrailer(sw, dest, null, null); }
        public virtual bool printTrailer(StreamWriter sw, PrintType dest,
            PacketIF.PacketIFCallback echoCallback) { return printTrailer(sw, dest, echoCallback, null); }
        public virtual bool printTrailer(StreamWriter sw, PrintType dest,
            PacketIF.PacketIFCallback echoCallback, Object echoClientData)
        {
            throw new Exception("Not Yet Implemented");
        }

        public virtual bool printValues(StreamWriter sw, PrintType dest)
        {
            throw new Exception("Not Yet Implemented");
        }
        public virtual bool sendNetwork()
        {
            throw new Exception("Not Yet Implemented");
        }
        public virtual bool sendValues() { return sendValues(false); }
        public virtual bool sendValues(bool force)
        {
            throw new Exception("Not Yet Implemented");
        }


        /// <summary>
        /// Convert a filename (with or without corresponding extensions)
        /// to a filename with the correct extension.
        /// </summary>
        /// <param name="filename"></param>
        /// <returns></returns>
        public static String FilenameToNetname(String filename)
        {
            throw new Exception("Not Yet Implemented");
        }
        public static String FilenameToCfgname(String filename)
        {
            throw new Exception("Not Yet Implemented");
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
            throw new Exception("Not Yet Implemented");
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
            throw new Exception("Not Yet Implemented");
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
            throw new Exception("Not Yet Implemented");
        }

        public static FileStream OpenNetworkFile(String netfile, out bool wasEncoded)
        {
            String errmsg = null;
            return OpenNetworkFile(netfile, out wasEncoded, ref errmsg);
        }
        public static FileStream OpenNetworkFile(String netfile, out bool wasEncoded, ref String errmsg)
        {
            throw new Exception("Not Yet Implemented");
        }

        public FileStream openNetworkFile(String netfile)
        {
            String errmsg = null;
            return openNetworkFile(netfile, ref errmsg);
        }
        public FileStream openNetworkFile(String netfile, ref String errmsg)
        {
            throw new Exception("Not Yet Implemented");
        }


        public static void CloseNetworkFile(FileStream sw, bool wasEncoded)
        {
            throw new Exception("Not Yet Implemented");
        }
        public void closeNetworkFile(FileStream sw)
        {
            throw new Exception("Not Yet Implemented");
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

        public void setDirty() { throw new Exception("Not Yet Implemented"); }
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
            throw new Exception("Not Yet Implemented");
        }
        public void deleteNode(Node node) { deleteNode(node, true); }
        public void deleteNode(Node node, bool undefer)
        {
            throw new Exception("Not Yet Implemented");
        }
        public Node findNode(Symbol name, int instance)
        {
            throw new Exception("Not Yet Implemented");
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

        public int getNodeCount()
        {
            throw new Exception("Not Yet Implemented");
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
            throw new Exception("Not Yet Implemented");
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
                dn = (DisplayNode) nodeList[nodeList.Count - 1];
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

        #endregion
    }
}
