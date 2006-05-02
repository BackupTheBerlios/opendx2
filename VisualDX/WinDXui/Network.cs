using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;
using System.IO;

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

        public struct netVersion
        {
            public Int16 major;
            public Int16 minor;
            public Int16 micro;
        }

        public struct dxVersion
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

        private bool fileHadGetOrSetNodes;
        private static List<TransmitterNode> RenameTransmitterList;

        #endregion

        #region Public Constructors
        Network() 
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

        }
        #endregion

        #region Protected Properties/Variables

        protected EditorWindow editor;
        protected List<ImageWindow> imageList;
        protected List<ControlPanel> panelList;
        protected NodeList nodeList;
        protected List<Decorator> decoratorList;

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

        protected int lastPanelInstanceNumber;
        protected PanelGroupManager panelGroupManager;
        protected PanelAccessManager panelAccessManager;

        protected int imageCount;

        protected WorkSpaceInfo workSpaceInfo;


        #endregion

        #region Public Properties/Variables
        public const String NetExtension = ".net";
        public const String CfgExtension = ".cfg";

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

        public Dictionary<String, GroupManager> groupManagers;
        public SequencerNode sequencer;

        #endregion

        #region Public Static Methods
        internal static void GenerateModuleMessage(
            Dictionary<String, Definition> nodes, String msg, bool error) { }

        #endregion

        #region Public Instance Methods

        public void closeControlPanel(int a) { }
        public void openControlPanel(int a) { }
        public void openControlPanelGroup(int a) { }
        public String getFileName() { return ""; }
        public bool saveNetwork(String fname) { return false; }

        #endregion

        #region Protected Methods

        protected bool parse(String filename) { return false;  }
        protected bool cfgParseComment(String name, String file, int lineno) 
        { return false; }
        protected void resetImageCount() { }

        #endregion

        #region Public Methods

        //
        // isMacro returns true if this network can be considered a macro.
        // canBeMacro returns true if there is nothing in the net that prevents
        // it from being a macro.
        // makeMacro makes this network a macro if do is true, else it makes it
        // be a "normal" net.
        public bool isMacro()
        {
            throw new Exception("Not yet implemented");
        }
        public bool canBeMacro()
        {
            throw new Exception("Not yet implemented");
        }
        public bool makeMacro(bool make)
        {
            throw new Exception("Not yet implemented");
        }

        //
        // Return true if the network is different from that on disk, and the
        // application allows saving of .net and .cfg files.
        //
        public bool saveToFileRequired()
        {
            throw new Exception("Not yet implemented");
        }

        public void setDefinition(MacroDefinition md) { throw new Exception("Not yet implemented"); }
        public MacroDefinition getDefinition() { throw new Exception("Not yet implemented"); }

        //
        // Colormap Management functions
        //
        public void openColormap(bool openAll) { throw new Exception("Not yet implemented"); }

        /// <summary>
        /// Name of the Network
        /// </summary>
        public String NameString
        {
            get { return SymbolManager.theSymbolManager.getSymbolString(name); }
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

        public bool IsDeleted
        {
            get { return deleting; }
        }

        public bool printNetwork(Stream s, PrintType pt)
        {
            throw new Exception("Not Yet Implemented");
        }
        public bool readNetwork(String filename)
        {
            throw new Exception("Not Yet Implemented");
        }

        public bool redefineNodes(Dictionary<Symbol, NodeDefinition> newdefs,
            ref Dictionary<Symbol, NodeDefinition> olddefs)
        {
            throw new Exception("Not Yet Implemented");
        }

        public Node findNode(String name)
        {
            int a = 0;
            return findNode(name, ref a, false);
        }
        public Node findNode(String name, ref int startpos)
        {
            return findNode(name, ref startpos, false);
        }
        public Node findNode(String name, ref int startpos, bool byLabel)
        {
            throw new Exception("Not Yet Implemented");
        }
        public Node findNode(Symbol name, int instance)
        {
            throw new Exception("Not Yet Implemented");
        }


        #endregion
    }
}
