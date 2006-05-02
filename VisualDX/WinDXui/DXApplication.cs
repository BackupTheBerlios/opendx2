using System;
using System.Collections.Generic;
using System.Text;
using System.Diagnostics;
using System.Windows.Forms;
using System.Drawing;
using System.IO;

namespace WinDX.UI
{
    public class DXApplication : BaseApplication
    {
        #region structs and enums             

        protected struct DXResource
        {
            public String server;
            public String executive;
            public String workingDirectory;

            public String program;
            public String cfgfile;
            public String userModules;
            public String macros;
            public String errorPath;

            public String executiveModule;
            public String uiModule;

            public bool noWindowPlacement;

            public int port;
            public int memorySize;

            public bool echoVersion;
            public String anchorMode;
            public bool noAnchorAtStartup;
            public bool noConfirmedQuit;
            public bool debugMode;
            public bool showInstanceNumbers;
            public bool runUIOnly;
            public bool runLocally;
            public bool showHelpMessage;
            public bool executiveProgram;
            public bool executeOnChange;
            public bool suppressStartupWindows;
            public bool isMetric;
            public bool exitAfter;
            public bool noExitOptions;
            public bool noExecuteMenus;
            public bool noConnectionMenus;
            public bool noWindowsMenus;


            // Image Window saving/printing control
            public String printImageFormat;
            public String printImagePageSize;
            public int printImageResolution;
            public String printImageSize;
            public String printImageCommand;

            public String saveImageFormat;
            public String saveImagePageSize;
            public int saveImageResolution;
            public String saveImageSize;

            // Message Window control
            public bool infoEnabled;
            public bool warningEnabled;
            public bool errorEnabled;
            public bool moduleInfoOpensMessage;
            public bool infoOpensMessage;
            public bool warningOpensMessage;
            public bool errorOpensMessage;

            // Configurability Level
            public String restrictionLevel;
            public bool useWindowSpecs;
            public bool noRWConfig;

            // Panel configurability
            public bool noOpenAllPanels;
            public bool noPanelEdit;
            public bool noPanelAccess;
            public bool noPanelOptions;

            // Interactor/panel configurability
            public bool noInteractorEdits;
            public bool noInteractorAttributes;
            public bool noInteractorMovement;

            // Image/Editor window configurability
            public bool noImageMenus;
            public bool noImageRWNetFile;
            public bool limitedNetFileSelection;
            public String netPath;
            public bool noImageLoad;
            public bool noEditorAccess;
            public bool limitImageOptions;
            public bool noImageSaving;
            public bool noImagePrinting;
            public bool notifySaveNet;
            public bool noNetworkExecute;

            // Message window configurability
            public bool noScriptCommands;
            public bool noMessageInfoOption;
            public bool noMessageWarningOption;
            public bool noEditorOnError;

            // ColormapEditor window configurability
            public bool noCMapSetNameOption;
            public bool noCMapOpenMap;
            public bool noCMapSaveMap;

            // Process group defining and host assignments.
            public bool noPGroupAssignment;

            // Global configurability
            public bool noDXHelp;

            public String cryptKey;
            public bool forceNetFileEncryption;
            public String forceFunctionalLicense;

            public int applicationPort;
            public String applicationHost;

            public String oemApplicationName;
            public String oemApplicationNameCode;
            public String oemLicenseCode;

            public String viewDataFile;

            // set to false by default, provides an initial value to 
            // EditorWorkSpace for repositioning scrollbars during page
            // changes.
            public bool autoScrollVPEInitVal;

            // On behalf of Java generation
            public String cosmoDir;
            public String jdkDir;
            public String htmlDir;
            public String dxJarFile;
            public String userHtmlDir;
            public String serverDir;

            // Automatic graph layout
            public int autoLayoutHeight;
            public int autoLayoutGroupSpacing;
            public int autoLayoutNodeSpacing;

            // Colors
            public Color errorNodeForeground;
            public Color executionHighlightForeground;
            public Color backgroundExecutionForeground;
            public Color foreground;
            public Color background;
            public Color insensitiveColor;
            public Color accentColor;
            public Color standInBackground;
        }

        protected struct DXServerInfo
        {
            public bool autoStart;
            public String server;
            public String executive;
            public String workingDirectory;
            public String userModules; // -mdf option
            public String executiveFlags; // Other flags, as required, for dxexec.
            public int port;
            public int memorySize;

            public List<DXChild> children;
            public List<DXPacketIF> queuedPackets;
            public DXPacketIF packet;
        }

        public enum AppType { Image, Editor, Menubar };
        public enum OpenVpe { DontOpenVpe, MayOpenVpe, MustOpenVpe };
        public enum CommandType
        {
            StartServer, ResetServer, ExecuteOnce,
            ExecuteOnChange, EndExecution, LoadMacro, OpenAllColormaps,
            OpenMessageWindow, OpenNetwork, OpenSequencer, ToggleInfoEnabled,
            ToggleWarningEnabled, ToggleErrorEnabled, LoadUserMDF,
            AssignProcessGroup, HelpOnManual, HelpOnHelp
        };

        public enum HighlightType
        {
            ERRORHIGHLIGHT,
            EXECUTEHIGHLIGHT,
            REMOVEHIGHLIGHT
        };

        #endregion 

        #region Public Contructors
        static DXApplication()
        {
            if (SymbolManager.theSymbolManager == null)
                SymbolManager.theSymbolManager = new SymbolManager();

            MsgExecute = SymbolManager.theSymbolManager.registerSymbol("Execute");
            MsgStandBy = SymbolManager.theSymbolManager.registerSymbol("StandBy");
            MsgExecuteDone = SymbolManager.theSymbolManager.registerSymbol("ExecuteDone");
            MsgServerDisconnected = SymbolManager.theSymbolManager.registerSymbol("ServerDisconnected");
            MsgPanelChanged = SymbolManager.theSymbolManager.registerSymbol("PanelChanged");
        }

        public DXApplication(String s)
            : base(s)
        {
            theDXApplication = this;
            anchor = null;
            serverDisconnectScheduled = false;
            network = null;

            // Create the local command scope.
            commandScope = new CommandScope();

            // Initialize the packet interface.
            serverInfo.packet = null;
            applicationPacket = null;
            messageWindow = null;

            quitCmd = new ConfirmedQuitCommand("quit", commandScope,
                true, this);
            exitCmd = new ConfirmedExitCommand("exit", commandScope,
                true, this);
            openFileCmd = new OpenCommand("open", commandScope,
                true, this);
            messageWindowCmd = new NoUndoDXAppCommand("messageWindowCmd",
                commandScope, true, this, CommandType.OpenMessageWindow);

            openSequencerCmd = new NoUndoDXAppCommand("openSequencerCmd",
                commandScope, false, this, CommandType.OpenSequencer);
            openAllColormapCmd = new NoUndoDXAppCommand("openAllColormapCmd",
                commandScope, false, this, CommandType.OpenAllColormaps);
            loadMacroCmd = new NoUndoDXAppCommand("Load Macro Command",
                commandScope, true, this, CommandType.LoadMacro);
            executeOnceCmd = new NoUndoDXAppCommand("Execute Once",
                commandScope, false, this, CommandType.ExecuteOnce);
            executeOnChangeCmd = new NoUndoDXAppCommand("Execute On Change",
                commandScope, false, this, CommandType.ExecuteOnChange);
            endExecutionCmd = new NoUndoDXAppCommand("End Execution",
                commandScope, false, this, CommandType.EndExecution);
            connectedToServerCmd = new NoOpCommand("Connected To Server",
                commandScope, true);
            disconnectedFromServerCmd = new NoOpCommand("Disconnected From Server",
                commandScope, true);
            executingCmd = new NoOpCommand("executingCmd", commandScope, true);
            notExecutingCmd = new NoOpCommand("notExecutingCmd", commandScope, true);
            connectedToServerCmd = new NoUndoDXAppCommand("Start Server",
                commandScope, true, this, CommandType.StartServer);
            resetServerCmd = new NoUndoDXAppCommand("Reset Server",
                commandScope, false, this, CommandType.ResetServer);
            disconnectFromServerCmd = new DisconnectFromServerCommand("disconnectFromServer",
                commandScope, false);
            loadMDFCmd = new NoUndoDXAppCommand("Load MDF...",
                commandScope, true, this, CommandType.LoadUserMDF);
            toggleInfoEnable = new NoUndoDXAppCommand("Enable Information",
                commandScope, true, this, CommandType.ToggleInfoEnabled);
            toggleWarningEnable = new NoUndoDXAppCommand("Enable Warnings",
                commandScope, true, this, CommandType.ToggleWarningEnabled);
            toggleErrorEnable = new NoUndoDXAppCommand("Enable Errors",
                commandScope, true, this, CommandType.ToggleErrorEnabled);
            assignProcessGroupCmd = new NoUndoDXAppCommand("assignProcessGroup",
                commandScope, true, this, CommandType.AssignProcessGroup);

            connectedToServerCmd.autoActivate(executeOnceCmd);
            connectedToServerCmd.autoActivate(executeOnChangeCmd);
            connectedToServerCmd.autoActivate(endExecutionCmd);
            connectedToServerCmd.autoActivate(disconnectedFromServerCmd);
            connectedToServerCmd.autoActivate(resetServerCmd);
            connectedToServerCmd.autoActivate(connectedToServerCmd);

            disconnectedFromServerCmd.autoActivate(connectedToServerCmd);
            disconnectedFromServerCmd.autoActivate(executeOnceCmd);
            disconnectedFromServerCmd.autoActivate(executeOnChangeCmd);
            disconnectedFromServerCmd.autoActivate(endExecutionCmd);
            disconnectedFromServerCmd.autoActivate(disconnectedFromServerCmd);
            disconnectedFromServerCmd.autoActivate(resetServerCmd);

            //
            // Once in execute on change don't allow it again until the user
            // does an endExecutionCmd
            //
            executeOnChangeCmd.autoDeactivate(executeOnChangeCmd);
            endExecutionCmd.autoActivate(executeOnChangeCmd);
            openFileCmd.autoActivate(executeOnChangeCmd);


            //
            // Set the automatic activation of any commands that depend on whether 
            // or not we are currently executing. 
            //
            executingCmd.autoDeactivate(openFileCmd);
            notExecutingCmd.autoActivate(openFileCmd);
            executingCmd.autoDeactivate(executeOnceCmd);
            notExecutingCmd.autoActivate(executeOnceCmd);

            //
            // Don't allow execute on change during an execute once.
            //
            executeOnceCmd.autoDeactivate(executeOnChangeCmd);
            notExecutingCmd.autoActivate(executeOnChangeCmd);

            readFirstNetwork = false;

        }

        ~DXApplication()
        {
            runApplication = false;
            theDXApplication = null;
        }

        #endregion

        #region Public Static Properties/Variables
        public static readonly Symbol MsgExecute = Symbol.zero;
        public static readonly Symbol MsgStandBy = Symbol.zero;
        public static readonly Symbol MsgExecuteDone = Symbol.zero;
        public static readonly Symbol MsgServerDisconnected = Symbol.zero;
        public static readonly Symbol MsgPanelChanged = Symbol.zero;
        public static DXApplication theDXApplication = null;
        public static readonly String EDIT_ANCHOR_MODE = "EDIT";
        public static readonly String IMAGE_ANCHOR_MODE = "IMAGE";
        public static readonly String MENUBAR_ANCHOR_MODE = "MENUBAR";
        #endregion

        #region Public Instance Properties/Variables
        /// <summary>
        /// Main Network
        /// </summary>
        public Network network;
        /// <summary>
        /// List of User Macros
        /// </summary>
        public List<Network> macroList;
        /// <summary>
        /// DX application commands
        /// </summary>
        public Command quitCmd;
        public Command exitCmd;
        public Command openFileCmd;
        public Command loadMacroCmd;
        public Command executeOnceCmd;
        public Command executeOnChangeCmd;
        public Command endExecutionCmd;
        public Command connectedToServerCmd;
        public Command disconnectedFromServerCmd;
        public Command connectToServerCmd;
        public Command resetServerCmd;
        public Command disconnectFromServerCmd;
        public Command messageWindowCmd;
        public Command openSequencerCmd;
        public Command openAllColormapCmd;
        public Command assignProcessGroupCmd;

        /// <summary>
        /// Used to do autoactiviation/deactivation of commands that
        /// register themselves with this command.
        /// </summary>
        public Command executingCmd;
        public Command notExecutingCmd;
        public Command loadMDFCmd;
        public Command toggleInfoEnable;
        public Command toggleWarningEnable;
        public Command toggleErrorEnable;


        public Color AccentColor
        {
            get { return resource.accentColor; }
        }
        public Color StandInBackground
        {
            get { return resource.standInBackground; }
        }
        public Color ErrorNodeForeground
        {
            get { return resource.errorNodeForeground; }
        }
        public Color ExecutionHighlightForeground
        {
            get { return resource.executionHighlightForeground; }
        }
        public Color BackgroundExecutionForeground
        {
            get { return resource.backgroundExecutionForeground; }
        }
        public Color Foreground
        {
            get { return resource.foreground; }
        }
        public Color InsensitiveColor
        {
            get { return resource.insensitiveColor; }
        }
        public bool InDebugMode
        {
            get { return resource.debugMode; }
        }

        public bool ShowInstanceNumber
        {
            get { return (resource.debugMode || resource.showInstanceNumbers); }
        }

        public bool InEditMode
        {
            get { return (resource.anchorMode == EDIT_ANCHOR_MODE); }
        }
        public bool InImageMode
        {
            get { return (resource.anchorMode == IMAGE_ANCHOR_MODE); }
        }
        public bool InMenuBarMode
        {
            get { return (resource.anchorMode == MENUBAR_ANCHOR_MODE); }
        }
        public bool InDataViewerMode
        {
            get { return (resource.viewDataFile != null); }
        }
        public String DataViewerImportFile
        {
            get { return resource.viewDataFile; }
        }
        public bool IsMetricUnits
        {
            get { return resource.isMetric; }
        }

        public MsgWin MessageWindow
        {
            get { return messageWindow; }
        }

        public String LimitedNetPath
        {
            get { return resource.netPath; }
        }

        // Get the default image printing/saving options specified through
        // command line options or resources.
        public String PrintImageFormat
        {
            get { return resource.printImageFormat; }
        }
        public String PrintImagePageSize
        {
            get { return resource.printImagePageSize; }
        }
        public String PrintImageSize
        {
            get { return resource.printImageSize; }
        }
        public int PrintImageResolution
        {
            get { return resource.printImageResolution; }
        }
        public String PrintImageCommand
        {
            get { return resource.printImageCommand; }
        }
        public String SaveImageFormat
        {
            get { return resource.saveImageFormat; }
        }
        public String SaveImagePageSize
        {
            get { return resource.saveImagePageSize; }
        }
        public String SaveImageSize
        {
            get { return resource.saveImageSize; }
        }
        public int SaveImageResolution
        {
            get { return resource.saveImageResolution; }
        }

        public bool IsInfoEnabled
        {
            get { return resource.infoEnabled; }
        }
        public bool IsWarningEnabled
        {
            get { return resource.warningEnabled; }
        }
        public bool IsErrorEnabled
        {
            get { return resource.errorEnabled; }
        }
        public bool DoesWarningOpenMessage
        {
            get { return resource.warningOpensMessage && IsWarningEnabled; }
        }
        public bool DoesErrorOpenMessage
        {
            get { return resource.errorOpensMessage && IsErrorEnabled; }
        }

        String CosmoDir
        {
            get { return resource.cosmoDir; }
        }
        String JdkDir
        {
            get { return resource.jdkDir; }
        }
        String HtmlDir
        {
            get { return resource.htmlDir; }
        }
        String ServerDir
        {
            get { return resource.serverDir; }
        }
        String DxJarFile
        {
            get { return resource.dxJarFile; }
        }
        String UserHtmlDir
        {
            get { return resource.userHtmlDir; }
        }
        bool AutoScrollInitialValue
        {
            get { return resource.autoScrollVPEInitVal; }
        }

        #endregion

        #region Protected Static Properties/Variables
        protected static DXResource resource;
        protected static String [] ListValuedSettings;
        #endregion

        #region Protected Instance Properties/Variables

        protected Form anchor = null;
        protected CommandScope commandScope = null;
        protected DXServerInfo serverInfo;
        protected DXExecCtl execCtl;

        protected ApplicIF applicationPacket;

        protected MsgWin messageWindow;

        protected List<String> errorList;
        #endregion

        #region Private Static Properties/Variables
        private static bool DXApplicationClassInitialized = false;
        #endregion

        #region Private Instance Properties/Variables
        /// <summary>
        /// Should we do a disconnect from the executive next time through
        /// the handleEvents.
        /// </summary>
        private bool serverDisconnectScheduled = false;
        /// <summary>
        /// Continue to run the application
        /// </summary>
        private bool runApplication = false;
        /// <summary>
        /// Have we read the first network yet
        /// </summary>
        private bool readFirstNetwork = false;




        #endregion

        #region Private Methods
        /// <summary>
        /// Define a mapping of integer levels and the restriction level names 
        /// and determine if the current restriction level is at the given
        /// level. The highest level of restriction is 1 the lowest and
        /// +infinity
        /// </summary>
        /// <param name="level"></param>
        /// <returns></returns>
        private bool isRestrictionLevel(int level)
        {
            Debug.Assert(level > 0);
            String rlev = "";
            XmlPreferences.theXmlPreferences.GetPref("restrictionLevel", out rlev);
            if (rlev == null)
                return false;
            switch (level)
            {
                case 3:
                    if (rlev == "minimum")
                        return true;
                    break;
                case 2:
                    if (rlev == "intermediate")
                        return true;
                    break;
                case 1:
                    if (rlev == "maximum")
                        return true;
                    break;
            }
            return false;
        }

        /// <summary>
        /// Save all dirty files and return a message string
        /// </summary>
        /// <param name="msg"></param>
        private void emergencySave(out String msg)
        {
            String introMsg = "The following files have been written...";
            bool introMsgUsed = false;
            msg = introMsg;

            // Still need to complete this function.
        }

        /// <summary>
        /// Need to work on oem stuff.
        /// </summary>
        /// <returns></returns>
        private String getOEMApplicationName()
        {
            String name;
            XmlPreferences.theXmlPreferences.GetPref("oemApplicationName", out name);
            return name;
        }


        private static void DebugEchoCallback(Object clientData, String echoString)
        {
            Console.WriteLine("DXLink::" + echoString);
        }

        private static void QueuedPacketAccept(Object data)
        {
            DXPacketIF p = (DXPacketIF)data;
            theDXApplication.packetIFAccept(p);
        }

        private static void QueuedPacketCancel(Object data)
        {
            DXPacketIF p = (DXPacketIF)data;
            theDXApplication.packetIFCancel(p);
        }

        private bool getAutoScrollInitialValue()
        {
            bool asv;
            XmlPreferences.theXmlPreferences.GetPref("autoScrollVPEInitVal", out asv);
            return asv;
        }

        private ProcessGroupManager getProcessGroupManager()
        {
            return (ProcessGroupManager)
                this.network.groupManagers[ProcessGroupManager.ProcessGroup];
        }

        #endregion

        #region Protected Methods

        /// <summary>
        /// If we're using an anchor window with its own copyright then be satisfied
        /// with that.  Otherwise use the superclass method.
        /// </summary>
        protected override void postCopyrightNotice()
        {
            throw new Exception("Not Yet Implemented");
        }


        /// <summary>
        /// Read the module description file into the Node Definition Dictionary.
        /// </summary>
        protected virtual void loadMDF()
        {
            String str = "";
            char fc = resource.executiveModule.ToCharArray()[0];
            if (fc == '/' || fc == '.')
                str = resource.executiveModule;
            else
                str = getUIRoot() + "/" + resource.executiveModule;

            Dictionary<Symbol, NodeDefinition> newdefs = new Dictionary<Symbol, NodeDefinition>();
            if (!ParseMDF.LoadMDFFile(str, "executive", ref newdefs, false))
                return;

            // Mark all of these as system-tools.
            foreach (NodeDefinition nd in newdefs.Values)
            {
                Symbol s = nd.NameSymbol;
                NodeDefinition.theNodeDefinitionDictionary.Add(s, nd);
                nd.setUserTool(false);
            }
        }

        /// <summary>
        /// Read the interactor description file into the Node Definition Dictionary.
        /// </summary>
        protected virtual void loadIDF()
        {
            InteractorStyle.BuildtheInteractorStyleDictionary();
            String str = "";
            if (resource.uiModule.ToCharArray()[0] == '/' ||
                resource.uiModule.ToCharArray()[0] == '.')
                str = resource.uiModule;
            else
            {
                str = getUIRoot();
                str += "/" + resource.uiModule;
            }

            Dictionary<Symbol, NodeDefinition> newdefs = new Dictionary<Symbol,NodeDefinition>();
            if (!ParseMDF.LoadMDFFile(str, "user interface", ref newdefs, false))
                return;

            // Mark all of these as system-tools.
            foreach (NodeDefinition nd in newdefs.Values)
            {
                Symbol s = nd.NameSymbol;
                NodeDefinition.theNodeDefinitionDictionary.Add(s, nd);
                nd.setUserTool(false);
            }
        }

        protected virtual void clearErrorList()
        {
            throw new Exception("Not Yet Implemented");
        }

        /// <summary>
        /// Disconnect from Exec next time through the main loop
        /// </summary>
        protected void scheduleServerDisconnect()
        {
            throw new Exception("Not Yet Implemented");
        }

        /// <summary>
        /// Send the command to the flush the dictionaries.
        /// </summary>
        /// <param name="pif"></param>
        protected virtual void flushExecutiveDictionaries(DXPacketIF pif)
        {
            throw new Exception("Not Yet Implemented");
        }

        /// <summary>
        /// Handle acceptance of (connection to) a packet interface.
        /// </summary>
        /// <param name="p"></param>
        protected virtual void packetIFAccept(DXPacketIF p)
        {
            throw new Exception("Not Yet Implemented");
        }

        /// <summary>
        /// Install the default resources for this class and then call the
        /// same super class method to get the default resources from the
        /// super classes.
        /// </summary>
        protected virtual void installDefaultResources()
        {
            setDefaultResources();
            String val;
            XmlPreferences.theXmlPreferences.GetPref("standInBackground", out val);
            resource.standInBackground = Utils.ColorFromPoundString(val);
            XmlPreferences.theXmlPreferences.GetPref("executionHighlightForeground", out val);
            resource.executionHighlightForeground = Utils.ColorFromPoundString(val);
            XmlPreferences.theXmlPreferences.GetPref("backgroundExecutionForeground", out val);
            resource.backgroundExecutionForeground = Utils.ColorFromPoundString(val);
            XmlPreferences.theXmlPreferences.GetPref("errorHighlightForeground", out val);
            resource.errorNodeForeground = Utils.ColorFromPoundString(val);
            XmlPreferences.theXmlPreferences.GetPref("InsensitiveColor", out val);
            resource.insensitiveColor = Utils.ColorFromPoundString(val);

            // Need to get the rest of the XmlPrefs out and set them into DXResource.

        }

        protected void setDefaultResources()
        {
            XmlPreferences.theXmlPreferences.SetDefault("standInBackground", XmlPreferences.PrefType.TypeString, "#5F9EA0");
            XmlPreferences.theXmlPreferences.SetDefault("executionHighlightForeground", XmlPreferences.PrefType.TypeString, "#00FF7E");
            XmlPreferences.theXmlPreferences.SetDefault("backgroundExecutionForeground", XmlPreferences.PrefType.TypeString, "#7E7EB4");
            XmlPreferences.theXmlPreferences.SetDefault("errorHighlightForeground", XmlPreferences.PrefType.TypeString, "#FF9B00");
            XmlPreferences.theXmlPreferences.SetDefault("InsensitiveColor", XmlPreferences.PrefType.TypeString, "#888888");
        }

        #endregion


        #region Public Methods

        /// <summary>
        /// Do an emergencySave() on abort
        /// </summary>
        public override void abortApplication()
        {
            if (theDXApplication != null)
            {
                String msg;
                emergencySave(out msg);
                MessageBox.Show(msg);
            }
            base.abortApplication();
        }

        public override void shutdownApplication()
        {
            throw new Exception("The method or operation is not implemented.");
        }


        protected override bool initialize(ref string[] argv)
        {
            bool wasSetBusy = false;

            base.initialize(ref argv);

            if (resource.executiveModule == null)
                resource.executiveModule = "lib/dx.mdf";
            if (resource.uiModule == null)
                resource.uiModule = "ui/ui.mdf";
            if (resource.userModules == null)
                resource.userModules = Environment.GetEnvironmentVariable("DXMDF");
            if (resource.macros == null)
                resource.macros = Environment.GetEnvironmentVariable("DXMACROS");
            if (resource.server == null)
                resource.server = Environment.GetEnvironmentVariable("DXHOST");
            if (resource.server == null)
                resource.server = "localhost";
            if (resource.server.Contains(","))
            {
                // Remove the port number if it exists (i.e DXHOST=slope,1920)
                resource.server = resource.server.Substring(0, resource.server.IndexOf(','));
            }
            if (resource.netPath == null)
                resource.netPath = Environment.GetEnvironmentVariable("DXNETPATH");
            if (resource.cryptKey == null)
                resource.cryptKey = Environment.GetEnvironmentVariable("DXCRYPTKEY");

            // If the app does not allow editor access or we are starting up without
            // displaying the anchor window, force one of (image or menubar) mode.
            if ((InEditMode && !appAllowsEditorAccess()) ||
                resource.noAnchorAtStartup)
            {
                if (InMenuBarMode)
                    resource.anchorMode = MENUBAR_ANCHOR_MODE;
                else
                    resource.anchorMode = IMAGE_ANCHOR_MODE;
            }

            // Echo the resources.
            if(resource.debugMode)
            {
                if(resource.port != 0)
                    Console.WriteLine("port        = {0}", resource.port);
                if(resource.memorySize != 0)
                    Console.WriteLine("memory size = {0}", resource.memorySize);
                if (resource.server != null)
                    Console.WriteLine("server = {0}", resource.server);
                if (resource.executive != null)
                    Console.WriteLine("executive = {0}", resource.executive);
                if (resource.workingDirectory != null)
                    Console.WriteLine("working directory = {0}",
                     resource.workingDirectory);
                if (resource.netPath != null)
                    Console.WriteLine("net path = {0}", resource.netPath);
                if (resource.program != null)
                    Console.WriteLine("program = {0}", resource.program);
                if (resource.cfgfile != null)
                    Console.WriteLine("cfgfile = {0}", resource.cfgfile);
                if (getUIRoot() != null)
                    Console.WriteLine("root = {0}", getUIRoot());
                if (resource.macros != null)
                    Console.WriteLine("macros = {0}", resource.macros);
                if (resource.errorPath != null)
                    Console.WriteLine("error path = {0}", resource.errorPath);
                if (resource.echoVersion)
                    Console.WriteLine("echo version");
                if (resource.anchorMode != null)
                    Console.WriteLine("anchor mode = {0}", resource.anchorMode);
                if (resource.noAnchorAtStartup)
                    Console.WriteLine("hiding anchor at startup");
                if (resource.debugMode)
                    Console.WriteLine("debug mode");
                if (resource.runUIOnly)
                    Console.WriteLine("run UI only");
                if (resource.showHelpMessage)
                    Console.WriteLine("show help message");
                if (resource.userModules != null)
                    Console.WriteLine("user mdf = {0}", resource.userModules);
                if (resource.executiveModule != null)
                    Console.WriteLine("executive mdf = {0}", resource.executiveModule);
                if (resource.uiModule != null)
                    Console.WriteLine("ui mdf = {0}", resource.uiModule);
                if (resource.suppressStartupWindows)
                    Console.WriteLine("suppress startup windows");

                if (resource.applicationPort != 0)
                    Console.WriteLine("application port = %d", resource.applicationPort);
                if (resource.applicationHost != null)
                    Console.WriteLine("application host = {0}", resource.applicationHost);

                //
                // Image printing resources.
                //
                if (resource.printImageCommand != null)
                    Console.WriteLine("print image command = '{0}'",
                        resource.printImageCommand);
                if (resource.printImageFormat != null)
                    Console.WriteLine("print image format = '{0}'",
                        resource.printImageFormat);
                if (resource.printImagePageSize != null)
                    Console.WriteLine("print image page size = '{0}'",
                        resource.printImagePageSize);
                Console.WriteLine("print image resolution = %d",
                        resource.printImageResolution);

                //
                // Image saving resources.
                //
                if (resource.saveImageFormat != null)
                    Console.WriteLine("save image format = '{0}'",
                        resource.saveImageFormat);
                if (resource.saveImagePageSize != null)
                    Console.WriteLine("save image page size = '{0}'",
                        resource.saveImagePageSize);
                Console.WriteLine("save image resolution = %d",
                        resource.saveImageResolution);

                //
                // UI restrictions 
                //
                if (resource.restrictionLevel != null)
                    Console.WriteLine("restriction level {0}",
                            resource.restrictionLevel);
                if (resource.noEditorAccess)
                    Console.WriteLine("no editor access");
                if (resource.limitedNetFileSelection)
                    Console.WriteLine("limited network file selection");
                if (resource.noImageRWNetFile)
                    Console.WriteLine("no net file read/write");
                if (resource.noImageSaving)
                    Console.WriteLine("no image saving");
                if (resource.noImagePrinting)
                    Console.WriteLine("no image printing");
                if (resource.noImageLoad)
                    Console.WriteLine("no image load ");
                if (resource.limitImageOptions)
                    Console.WriteLine("limit image options");
                if (resource.noRWConfig)
                    Console.WriteLine("no cfg save");
                if (resource.noPanelEdit)
                    Console.WriteLine("no panel edit");
                if (resource.noInteractorEdits)
                    Console.WriteLine("no interactor style");
                if (resource.noInteractorAttributes)
                    Console.WriteLine("no interactor attributes");
                if (resource.noInteractorMovement)
                    Console.WriteLine("no interactor movement");
                if (resource.noOpenAllPanels)
                    Console.WriteLine("no open all panels");
                if (resource.noPanelAccess)
                    Console.WriteLine("no panel access");
                if (resource.noPanelOptions)
                    Console.WriteLine("no panel options");
                if (resource.noMessageInfoOption)
                    Console.WriteLine("no message info option");
                if (resource.noMessageWarningOption)
                    Console.WriteLine("no message warning option");
                if (resource.noDXHelp)
                    Console.WriteLine("no DX help");

                //
                // automatic graph layout
                //
                if (resource.autoLayoutHeight > 0)
                    Console.WriteLine("automatic graph layout height = %d",
                    resource.autoLayoutHeight);
                if (resource.autoLayoutGroupSpacing > 0)
                    Console.WriteLine("automatic graph layout group spacing = %d",
                    resource.autoLayoutGroupSpacing);
                if (resource.autoLayoutNodeSpacing > 0)
                    Console.WriteLine("automatic graph layout node spacing = %d",
                    resource.autoLayoutNodeSpacing);
            }

            if (resource.echoVersion)
            {
                String vers = String.Format("{0} User Interface, version {1}.{2}.{3} ({4})",
                    getFormalName(), global::WinDX.UI.Resources.MAJOR_VERSION,
                global::WinDX.UI.Resources.MINOR_VERSION,
                global::WinDX.UI.Resources.MICRO_VERSION,
                File.GetLastWriteTime(Application.ExecutablePath));

                MessageBox.Show(vers, "Version");
                Application.Exit();
            }

            // Fix me! May need to turn off help here.

            // Validate and set automatic graph layout values
            if (resource.autoLayoutHeight > 0)
            {
                String errmsg = GraphLayout.SetHeightPerLevel(resource.autoLayoutHeight);
                if (errmsg != null)
                {
                    MessageBox.Show(errmsg, "Startup Error");
                    return false;
                }
            }
            if (resource.autoLayoutGroupSpacing > 0)
            {
                String errmsg = GraphLayout.SetGroupSpacing(resource.autoLayoutGroupSpacing);
                if (errmsg != null)
                {
                    MessageBox.Show(errmsg, "Startup Error");
                    return false;
                }
            }
            if (resource.autoLayoutNodeSpacing > 0)
            {
                String errmsg = GraphLayout.SetNodeSpacing(resource.autoLayoutNodeSpacing);
                if (errmsg != null)
                {
                    MessageBox.Show(errmsg, "Startup Error");
                    return false;
                }
            }

            // Validate the resources and options
            if (InEditMode && !appAllowsEditorAccess())
            {
                MessageBox.Show("-edit and -noEditorAccess options are incompatible.", "Startup Error");
                return false;
            }

            if (appAllowsImageRWNetFile() && appLimitsNetFileSelection() &&
                resource.netPath == null)
            {
                MessageBox.Show("The \"limitedNetFileSelection\" or \"noImageRWNetFile\" " +
                    "option requires\na directory pathname specified by " +
                    "the \"DXNETPATH\" environment variable, \n" +
                    "the -netPath command line option, or\n" +
                    "the *netPath resource.", "Startup Error");
                return false;
            }

            // Setup Server Information
            serverInfo.autoStart = (resource.port <= 0);
            serverInfo.server = resource.server;
            serverInfo.executive = resource.executive;
            serverInfo.workingDirectory = resource.workingDirectory;
            serverInfo.userModules = resource.userModules;
            serverInfo.port = (resource.port == 0 ? 1900 : resource.port);
            serverInfo.memorySize = resource.memorySize;
            serverInfo.executiveFlags = "";

            foreach (String arg in argv)
            {
                serverInfo.executiveFlags += arg + " ";
            }

            if (InDataViewerMode)
            {
                resource.executeOnChange = true;
                resource.noImageRWNetFile = true;
                resource.noRWConfig = true;
                resource.noImageLoad = true;
                resource.noDXHelp = true;
                resource.noPGroupAssignment = true;
                resource.limitImageOptions = true;
                resource.noScriptCommands = true;
                resource.noConnectionMenus = true;
                resource.noWindowsMenus = true;
                resource.anchorMode = IMAGE_ANCHOR_MODE;
                resource.noAnchorAtStartup = true;
                resource.suppressStartupWindows = true;
                resource.noConfirmedQuit = true;
            }

            // Create the first/root/anchor network and place it in the
            // network list.
            network = newNetwork();

            if (appAllowsEditorAccess())
            {
                // Initialize the ConfigurationDialog allocator for the editor
                CDBAllocatorDictionary.theCDBAllocatorDictionary = new CDBAllocatorDictionary();

                // Initialize the StandIn allocator for the editor.
                SIAllocatorDictionary.theSIAllocatorDictionary = new SIAllocatorDictionary();

                // Move to the indicated directory
                if (serverInfo.workingDirectory != null)
                {
                    try
                    {
                        Directory.SetCurrentDirectory(serverInfo.workingDirectory);
                    }
                    catch (Exception e)
                    {
                        MessageBox.Show(e.Message, "Unable to set Working Directory");
                    }
                }

                loadMDF();
                loadIDF();
                if (resource.userModules != null)
                    loadUDF(resource.userModules, null, false);

                // Decorator Styles
                DecoratorStyle.BuildtheDecoratorStyleDictionary();

                // load the initial set of user macros.
                MacroDefinition.LoadMacroDirectories(resource.macros);

                // Create the anchor window
                if (!InEditMode)
                {
                    if (InImageMode)
                        anchor = newImageWindow(network);
                    else if (InMenuBarMode)
                        anchor = new DXAnchorWindow("dxAnchor", true, true);
                    else
                    {
                        MessageBox.Show("Unrecognized anchor mode.", "Startup Error");
                        Application.Exit();
                    }
                }

                // Initialize the anchor window so it can handle reading in the network
                // before being managed.
                if (applyWindowPlacements() ||
                    resource.noAnchorAtStartup)
                { }
                else
                {
                    anchor.Visible = true;
                    setBusyCursor(true);
                    wasSetBusy = true;
                }

                // Create the message and debug windows
                messageWindow = newMsgWin();

                // If quested, read in the network.  This is after opening the anchor
                // window because image nodes may wish to bind with the initial image
                // window, etc.
                if (resource.program != null)
                    openFile(resource.program, resource.cfgfile);

                if (InDataViewerMode)
                {
                    Node n = network.findNode("Import");
                    if (n == null)
                    {
                        ErrorDialog ed = new ErrorDialog();
                        ed.post("Can not find Import tool in viewing program.");
                    }
                    else
                    {
                        String s = resource.viewDataFile;
                        Debug.Assert(s != null);
                        n.setInputValue(1, s);
                    }
                }

                if (resource.noAnchorAtStartup)
                    anchor.Visible = true;
                else if (anchor.Visible)
                {
                    anchor.Visible = false;
                    setBusyCursor(true);
                    wasSetBusy = true;
                }

                // Post the copyright message if the anchor window came up.
                if (!resource.noAnchorAtStartup)
                    postCopyrightNotice();

                if (!resource.runUIOnly)
                {
                    // Connect to exec first
                    DXChild c = startServer();

                    completeConnection(c);
                }

                // If there is an application to talk to, connect to it.
                if (resource.applicationPort != 0)
                    connectToApplication(resource.applicationHost,
                        resource.applicationPort);

                if (wasSetBusy)
                    setBusyCursor(false);

                return true;
            }
        }

        public void highlightNodes(String path, HighlightType highlightType)
        {
            throw new Exception("Not Yet Implemented");
        }

        public void notifyPanelChanged()
        {
            throw new Exception("Not Yet Implemented");
        }


        public int connectToServer(int port)
        {
            return connectToServer(port, null);
        }
        public int connectToServer(int port, DXChild c)
        {
            throw new Exception("Not Yet Implemented");
        }

        public void closeConnection(DXChild c)
        {
            throw new Exception("Not Yet Implemented");
        }

        public void completeConnection(DXChild c)
        {
            throw new Exception("Not Yet Implemented");
        }

        public DXChild startServer()
        {
            throw new Exception("Not Yet Implemented");
        }

        public void setServer(String server)
        {
            throw new Exception("Not Yet Implemented");
        }

        public DXPacketIF getPacketIF() { return this.serverInfo.packet; }
        public DXExecCtl getExecCtl() { return this.execCtl; }


        public virtual bool openFile(String netfile,
            String cfgfile)
        {
            return openFile(netfile, cfgfile, true);
        }
        public virtual bool openFile(String netfile,
            String cfgfile, bool resetTheServer)
        {
            throw new Exception("Not Yet Implemented");
        }

        public virtual bool saveFile(String netfile)
        {
            return saveFile(netfile, false);
        }
        public virtual bool saveFile(String netfile,
            bool force)
        {
            throw new Exception("Not Yet Implemented");
        }


        public virtual bool resetServer()
        {
            throw new Exception("Not Yet Implemented");
        }
        public bool postStartServerDialog()
        {
            throw new Exception("Not Yet Implemented");
        }
        public void postProcessGroupAssignDialog()
        {
            throw new Exception("Not Yet Implemented");
        }
        public void postOpenNetworkDialog()
        {
            throw new Exception("Not Yet Implemented");
        }
        public void postLoadMDFDialog()
        {
            throw new Exception("Not Yet Implemented");
        }
        public void postLoadMacroDialog()
        {
            throw new Exception("Not Yet Implemented");
        }
        public void getServerParameters(int autoStart, ref String server,
            ref String executive, ref String workingDirectory,
            ref String executiveFlags, int port, int memorySize)
        {
            throw new Exception("Not Yet Implemented");
        }
        public void setServerParameters(int autoStart, String server,
            String executive, String workingDirectory,
            String executiveFlags, int port, int memorySize)
        {
            throw new Exception("Not Yet Implemented");
        }

        public virtual void connectToApplication(String host, int port)
        {
            throw new Exception("Not Yet Implemented");
        }

        public void showInstanceNumbers(bool on_or_off)
        {
            throw new Exception("Not Yet Implemented");
        }

        /// <summary>
        /// Create a new network editor.  
        /// This particular implementation makes the returned editor an anchor
        /// if this->anchor is NULL.
        /// This may return NULL in which case a message dialog is posted. 
        /// </summary>
        /// <param name="n"></param>
        /// <returns></returns>
        public virtual EditorWindow newNetworkEditor(Network n)
        {
            throw new Exception("Not Yet Implemented");
        }

        public virtual Network newNetwork()
        {
            return newNetwork(false);
        }
        public virtual Network newNetwork(bool nonJava)
        {
            throw new Exception("Not Yet Implemented");
        }
        public virtual MsgWin newMsgWin()
        {
            throw new Exception("Not Yet Implemented");
        }
        public virtual ImageWindow newImageWindow(Network n)
        {
            throw new Exception("Not Yet Implemented");
        }
        public virtual ControlPanel newControlPanel(Network n)
        {
            throw new Exception("Not Yet Implemented");
        }

        public virtual void addErrorList(String line)
        {
            throw new Exception("Not Yet Implemented");
        }

        /// <summary>
        /// Handle cancelation of (disconnection from) a packet interface.
        /// </summary>
        /// <param name="p"></param>
        public virtual void packetIFCancel(DXPacketIF p)
        {
            throw new Exception("Not Yet Implemented");
        }


        public override void helpOn(String topic)
        {

        }

        //
        // Mark all the networks owned by this application as dirty.
        //
        public void markNetworksDirty()
        {
            throw new Exception("The method or operation is not implemented.");
        }

        public bool doesInfoOpenMessage()
        {
            return doesInfoOpenMessage(false);
        }
        public bool doesInfoOpenMessage(bool fromModule)
        {
            throw new Exception("The method or operation is not implemented.");
        }
        public bool doesWarningOpenMessage()
        {
            throw new Exception("The method or operation is not implemented.");
        }
        public bool doesErrorOpenMessage
        {
            get { throw new Exception("Not yet implemented."); }
        }
        public int doesErrorOpenVpe(Network n)
        {
            throw new Exception("The method or operation is not implemented.");
        }
        public void enableInfo(bool enable)
        {
            throw new Exception("The method or operation is not implemented.");
        }
        public void enableWarning(bool enable)
        {
            throw new Exception("The method or operation is not implemented.");
        }
        public void enableError(bool enable)
        {
            throw new Exception("The method or operation is not implemented.");
        }

        public Form getAnchor()
        {
            return this.anchor;
        }
        public bool appAllowsConfirmedQuit()
        {
            throw new Exception("The method or operation is not implemented.");
        }
        public bool disconnectFromServer()
        {
            if (serverInfo.packet != null)
                packetIFCancel(serverInfo.packet);

            //
            // Only clear the error list when we ask to be disconnected
            // (i.e. don't do it in packetIFCancel() which gets called when
            // unexpectedly disconnected from the server). 
            //
            clearErrorList();

            //
            // Make sure we don't disconnect on the next connection.
            //
            serverDisconnectScheduled = true;

            return true;
        }

        public void disconnectFromApplication(bool terminate)
        {
            if (applicationPacket != null)
            {
                applicationPacket = null;
            }
            if (terminate)
                shutdownApplication();
        }

        public CommandScope getCommandScope()
        {
            return commandScope;
        }

        /// <summary>
        /// Read the user's description file into the Node Definition Dictionary.
        /// If dict is not null then fill the given dictionary with the 
        /// NodeDefintions found in the given MDF. 
        /// If uiLoadedOnly is TRUE, then the user has asked to have these loaded
        /// from somewhere other than the command line (in which case the 
        /// exec does not know about them yet).
        /// </summary>
        /// <param name="fileName"></param>
        public virtual void loadUDF(String fileName)
        {
            Dictionary<Symbol, NodeDefinition> dict = null;
            loadUDF(fileName, ref dict, false);
        }
        public virtual void loadUDF(String fileName, Dictionary<Symbol, NodeDefinition> dict,
            bool uiLoadedOnly)
        {
            Dictionary<Symbol, NodeDefinition> dict2 = null;
            if(dict != null)
                dict2 = new Dictionary<Symbol, NodeDefinition>(dict);
            loadUDF(fileName, ref dict2, false);
        }
        public virtual void loadUDF(String fileName, ref Dictionary<Symbol, NodeDefinition> dict)
        {
            loadUDF(fileName, ref dict, false);
        }
        public virtual void loadUDF(String fileName, ref Dictionary<Symbol, NodeDefinition> dict,
            bool uiLoadedOnly)
        {
            Dictionary<Symbol, NodeDefinition> local_dict = new Dictionary<Symbol,NodeDefinition>();
            if (dict == null)
                dict = local_dict;
            if (ParseMDF.LoadMDFFile(fileName, "user's", ref dict, uiLoadedOnly) &&
                dict.Count > 0)
            {
                Dictionary<Symbol, NodeDefinition> olddefs = new Dictionary<Symbol, NodeDefinition>(dict);
                // Send any new definitions to the server.
                sendNewMDFToServer(dict, ref olddefs);
                
                // Make sure the tool selectors get updated.
                ToolSelector.MergeNewTools(dict);


                // Now ask all the networks to update the node that are contained
                // within the network.
                network.redefineNodes(dict, ref olddefs);
                foreach (Network net in macroList)
                {
                    net.redefineNodes(dict, ref olddefs);
                }
            }
        }

        /// <summary>
        /// Get selected NodeDefinitoins from the newdefs dictionary and send 
        /// their representative MDF specs to the server if they are
        /// 	1) outboard 
        /// 	2) dynamically loaded 
        /// 	3) outboardness or dynmacity changes compared to the possibly 
        ///	    existing definition in the current dictionary if provided.
        /// </summary>
        /// <param name="newdefs"></param>
        public void sendNewMDFToServer(Dictionary<Symbol, NodeDefinition> newdefs)
        {
            Dictionary<Symbol, NodeDefinition> dict = null;
            sendNewMDFToServer(newdefs, ref dict);
        }
        public void sendNewMDFToServer(Dictionary<Symbol, NodeDefinition> newdefs,
            ref Dictionary<Symbol, NodeDefinition> current)
        {
            throw new Exception("Not Yet Implemented");
        }

        //
        // Define a set of methods that indicate a level of UI capability. 
        //
        public virtual bool appAllowsDXHelp()
        {
            throw new Exception("Not Yet Implemented");
        }
        public virtual bool appSuppressesStartupWindows()
        {
            throw new Exception("Not Yet Implemented");
        }
        public virtual bool appLimitsNetFileSelection()
        {
            throw new Exception("Not Yet Implemented");
        }

        public virtual bool appAllowsPanelEdit()
        {
            throw new Exception("Not Yet Implemented");
        }
        public virtual bool appAllowsRWConfig()
        {
            throw new Exception("Not Yet Implemented");
        }
        public virtual bool appAllowsPanelAccess()
        {
            throw new Exception("Not Yet Implemented");
        }
        public virtual bool appAllowsOpenAllPanels()
        {
            throw new Exception("Not Yet Implemented");
        }
        public virtual bool appAllowsPanelOptions()
        {
            throw new Exception("Not Yet Implemented");
        }

        public virtual bool appAllowsInteractorEdits()
        {
            throw new Exception("Not Yet Implemented");
        }
        public virtual bool appAllowsInteractorSelection()
        {
            throw new Exception("Not Yet Implemented");
        }
        public virtual bool appAllowsInteractorMovement()
        {
            throw new Exception("Not Yet Implemented");
        }
        public virtual bool appAllowsInteractorAttributeChange()
        {
            throw new Exception("Not Yet Implemented");
        }

        public virtual bool appAllowsImageRWNetFile()
        {
            throw new Exception("Not Yet Implemented");
        }
        public virtual bool appAllowsSavingNetFile()
        {
            return appAllowsSavingNetFile(null);
        }
        public virtual bool appAllowsSavingNetFile(Network net)
        {
            throw new Exception("Not Yet Implemented");
        }
        public virtual bool appAllowsSavingCfgFile()
        {
            throw new Exception("Not Yet Implemented");
        }
        public virtual bool appAllowsImageLoad()
        {
            throw new Exception("Not Yet Implemented");
        }
        public virtual bool appAllowsImageSaving()
        {
            throw new Exception("Not Yet Implemented");
        }
        public virtual bool appAllowsImagePrinting()
        {
            throw new Exception("Not Yet Implemented");
        }
        public virtual bool appLimitsImageOptions()
        {
            throw new Exception("Not Yet Implemented");
        }

        public virtual bool appAllowsEditorAccess()
        {
            throw new Exception("Not Yet Implemented");
        }
        public virtual bool appAllowsPGroupAssignmentChange()
        {
            throw new Exception("Not Yet Implemented");
        }

        public virtual bool appAllowsMessageInfoOption()
        {
            throw new Exception("Not Yet Implemented");
        }
        public virtual bool appAllowsMessageWarningOption()
        {
            throw new Exception("Not Yet Implemented");
        }
        public virtual bool appAllowsScriptCommands()
        {
            throw new Exception("Not Yet Implemented");
        }

        public virtual bool appAllowsCMapSetName()
        {
            throw new Exception("Not Yet Implemented");
        }
        public virtual bool appAllowsCMapOpenMap()
        {
            throw new Exception("Not Yet Implemented");
        }
        public virtual bool appAllowsCMapSaveMap()
        {
            throw new Exception("Not Yet Implemented");
        }
        public virtual bool appForcesNetFileEncryption()
        {
            throw new Exception("Not Yet Implemented");
        }
        public bool appAllowsExitOptions()
        {
            throw new Exception("Not Yet Implemented");
        }
        public bool appAllowsExecuteMenus()
        {
            throw new Exception("Not Yet Implemented");
        }
        public bool appAllowsConnectionMenus()
        {
            throw new Exception("Not Yet Implemented");
        }
        public bool appAllowsWindowsMenus()
        {
            throw new Exception("Not Yet Implemented");
        }
        public bool appAllowsImageMenus()
        {
            throw new Exception("Not Yet Implemented");
        }

        public bool dxlAppNotifySaveNet()
        {
            return resource.notifySaveNet;
        }

        public bool dxlAppNoNetworkExecute()
        {
            return resource.noNetworkExecute;
        }

        /// <summary>
        /// Return the name of the application (i.e. 'Data Explorer',
        /// 'Data Prompter', 'Medical Visualizer'...).
        /// </summary>
        /// <returns></returns>
        public override String getInformalName()
        {
            throw new Exception("Not Yet Implemented");
        }

        /// <summary>
        /// Return the formal name of the application (i.e. 
        /// 'Open Visualization Data Explorer', 'Open Visualization Data Prompter'...)
        /// </summary>
        /// <returns></returns>
        public override String getFormalName()
        {
            return global::WinDX.UI.Resources.PRODUCT_NAME;
        }

        /// <summary>
        /// Get the applications copyright notice, for example...
        /// "Copyright International Business Machines Corporation 1991-1993
        /// All rights reserved"
        /// </summary>
        /// <returns></returns>
        public override String getCopyrightNotice()
        {
            throw new Exception("Not Yet Implemented");
        }

        /// <summary>
        /// Go through the error list and highlight all nodes that got errors.
        /// </summary>
        public void refreshErrorIndicators()
        {
            throw new Exception("Not Yet Implemented");
        }

        public virtual bool printComment(Stream s)
        {
            throw new Exception("Not Yet Implemented");
        }
        public virtual bool parseComment(String line, String filename, int lineno)
        {
            throw new Exception("Not Yet Implemented");
        }

        /// <summary>
        /// 
        /// </summary>
        /// <returns>true if the DXWindows are supposed to use the window placement
        /// information saved in the .net or .cfg files. </returns>
        public virtual bool applyWindowPlacements()
        {
            throw new Exception("Not Yet Implemented");
        }

        public virtual String getCryptKey()
        {
            return resource.cryptKey;
        }

        ApplicIF getAppConnection()
        {
            return applicationPacket;
        }

        public void appendReferencedFile(String file)
        {
            throw new Exception("Not Yet Implemented");
        }
        public void removeReferencedFile(String file)
        {
            throw new Exception("Not Yet Implemented");
        }
        public void getRecentNets(out List<String> result)
        {
            throw new Exception("Not Yet Implemented");
        }


        #endregion
    }
}
