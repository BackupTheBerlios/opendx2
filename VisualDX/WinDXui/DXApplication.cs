using System;
using System.Collections.Generic;
using System.Text;
using System.Diagnostics;
using System.Windows.Forms;

namespace WinDX.UI
{
    class DXApplication : BaseApplication
    {
        #region structs and enums
        protected struct DXResource
        {
            String server;
            String executive;
            String workingDirectory;

            String program;
            String cfgfile;
            String userModules;
            String macros;
            String errorPath;

            String executiveModule;
            String uiModule;

            bool noWindowPlacement;

            int port;
            int memorySize;

            bool echoVersion;
            String anchorMode;
            bool noAnchorAtStartup;
            bool noConfirmedQuit;
            bool debugMode;
            bool showInstanceNumbers;
            bool runUIOnly;
            bool runLocally;
            bool showHelpMessage;
            bool executiveProgram;
            bool executeOnChange;
            bool suppressStartupWindows;
            bool isMetric;
            bool exitAfter;
            bool noExitOptions;
            bool noExecuteMenus;
            bool noConnectionMenus;
            bool noWindowsMenus;


            // Image Window saving/printing control
            String printImageFormat;
            String printImagePageSize;
            int printImageResolution;
            String printImageSize;
            String printImageCommand;

            String saveIamgeFormat;
            String saveImagePageSize;
            int saveImageResolution;
            String saveImageSize;

            // Message Window control
            bool infoEnabled;
            bool warningEnabled;
            bool errorEnabled;
            bool moduleInfoOpensMessage;
            bool infoOpensMessage;
            bool warningOpensMessage;
            bool errorOpensMessage;

            // Configurability Level
            String restrictionLevel;
            bool useWindowSpecs;
            bool noRWConfig;

            // Panel configurability
            bool noOpenAllPanels;
            bool noPanelEdit;
            bool noPanelAccess;
            bool noPanelOptions;

            // Interactor/panel configurability
            bool noInteractorEdits;
            bool noInteractorAttributes;
            bool noInteractorMovement;

            // Image/Editor window configurability
            bool noImageMenus;
            bool noImageRWNetFile;
            bool limitedNetFileSelection;
            String netPath;
            bool noImageLoad;
            bool noEditorAccess;
            bool limitImageOptions;
            bool noImageSaving;
            bool noImagePrinting;
            bool notifySaveNet;
            bool noNetworkExecute;

            // Message window configurability
            bool noScriptCommands;
            bool noMessageInfoOptions;
            bool noMessageWarningOption;
            bool noEditorOnError;

            // ColormapEditor window configurability
            bool noCMapSetNameOption;
            bool noCMapOpenMap;
            bool noCMapSaveMap;

            // Process group defining and host assignments.
            bool noPGroupAssignment;

            // Global configurability
            bool noDXHelp;

            String cryptKey;
            bool forceNetFileEncryption;
            String forceFunctionalLicense;

            int applicationPort;
            String applicationHost;

            String oemApplicationName;
            String oemApplicationNameCode;
            String oemLicenseCode;

            String viewDataFile;

            // set to false by default, provides an initial value to 
            // EditorWorkSpace for repositioning scrollbars during page
            // changes.
            bool autoScrollVPEInitVal;

            // On behalf of Java generation
            String cosmodir;
            String jdkDir;
            String htmlDir;
            String dxJarFile;
            String userHtmlDir;
            String serverDir;

            // Automatic graph layout
            int autoLayoutHeight;
            int autoLayoutGroupSpacing;
            int autoLayoutNodeSpacing;
        }

        protected struct DXServerInfo
        {
            public int autoStart;
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

        #endregion 

        #region Public Contructors
        static DXApplication()
        {
            // Initialize Symbols.
        }

        public DXApplication(String s)
            :
    base(s)
        {
            theDXApplication = this;
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

        #endregion

        #region Public Static Properties/Variables
        public static readonly Symbol MsgExecute = Symbol.zero;
        public static readonly Symbol MsgStandBy = Symbol.zero;
        public static readonly Symbol MsgExecuteDone = Symbol.zero;
        public static readonly Symbol MsgServerDisconnected = Symbol.zero;
        public static readonly Symbol MsgPanelChanged = Symbol.zero;
        public static DXApplication theDXApplication = null;
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


        public MsgWin MessageWindow
        {
            get { return messageWindow; }
        }


        #endregion

        #region Protected Static Properties/Variables
        protected static DXResource resource;
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
            MainProgram.theXmlPreferences.GetPref("restrictionLevel", out rlev);
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
            String introMsg = "The following files have been written...\n\n";
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
            MainProgram.theXmlPreferences.GetPref("oemApplicationName", out name);
            return name;
        }

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


        public override bool initialize(string[] argv)
        {
            return base.initialize(argv);
        }

        private static void DebugEchoCallback( Object clientData, String echoString)
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

        public override void helpOn(String topic)
        {

        }

        public override string getFormalName()
        {
            //String s = getOEMApplicationName();

            return global::WinDX.UI.Resources.PRODUCT_NAME;
        }

        private bool getAutoScrollInitialValue()
        {
            bool asv;
            MainProgram.theXmlPreferences.GetPref("autoScrollVPEInitVal", out asv);
            return asv;
        }

        private ProcessGroupManager getProcessGroupManager()
        {
            return (ProcessGroupManager)
                this.network.groupManagers[ProcessGroupManager.ProcessGroup];
        }

        public virtual void packetIFCancel(DXPacketIF p)
        {
            throw new Exception("The method or operation is not implemented.");
        }

        protected virtual void packetIFAccept(DXPacketIF p)
        {
            throw new Exception("The method or operation is not implemented.");
        }

        public DXPacketIF getPacketIF() { return this.serverInfo.packet; }
        public DXExecCtl getExecCtl() { return this.execCtl; }


        public virtual bool resetServer()
        {
            throw new Exception("The method or operation is not implemented.");
        }
        public bool postStartServerDialog()
        {
            throw new Exception("The method or operation is not implemented.");
        }
        public bool postProcessGroupAssignDialog()
        {
            throw new Exception("The method or operation is not implemented.");
        }
        public bool postOpenNetworkDialog()
        {
            throw new Exception("The method or operation is not implemented.");
        }
        public bool postLoadMDFDialog()
        {
            throw new Exception("The method or operation is not implemented.");
        }
        public bool postLoadMacroDialog()
        {
            throw new Exception("The method or operation is not implemented.");
        }

        public virtual void addErrorList(String line)
        {
            throw new Exception("Not yet implemented.");
        }

            //
    // Mark all the networks owned by this application as dirty.
    //
    public void markNetworksDirty()
        {
            throw new Exception("The method or operation is not implemented.");
        }

    public bool	isInfoEnabled()
        {
            throw new Exception("The method or operation is not implemented.");
        }
    public bool	isWarningEnabled()
        {
            throw new Exception("The method or operation is not implemented.");
        }
    public bool	isErrorEnabled()
        {
            throw new Exception("The method or operation is not implemented.");
        }
    public bool	doesInfoOpenMessage(bool fromModule)
        {
            throw new Exception("The method or operation is not implemented.");
        }
    public bool	doesWarningOpenMessage()
        {
            throw new Exception("The method or operation is not implemented.");
        }
    public bool	doesErrorOpenMessage
        {
            get { throw new Exception("Not yet implemented."); }
        }
    public int 	doesErrorOpenVpe(Network n)
        {
            throw new Exception("The method or operation is not implemented.");
        }
    public void	enableInfo(bool enable)
        {
            throw new Exception("The method or operation is not implemented.");
        }
    public void	enableWarning(bool enable)
        {
            throw new Exception("The method or operation is not implemented.");
        }
    public void	enableError(bool enable)
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

        public void clearErrorList()
        {
            throw new Exception("Not Yet Implemented");
            foreach (String s in errorList)
            {
               
            }
        }

        public enum HighlightType
        {
            ERRORHIGHLIGHT,
            EXECUTEHIGHLIGHT,
            REMOVEHIGHLIGHT
        };

        public void highlightNodes(String path, HighlightType highlightType)
        {
            throw new Exception("Not Yet Implemented");
        }

        public CommandScope getCommandScope()
        {
            throw new Exception("Not Yet Implemented");
        }
    }
}
