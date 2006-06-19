using System;
using System.Collections.Generic;
using System.Text;
using System.Diagnostics;
using System.Windows.Forms;
using System.Drawing;
using System.IO;
using System.Text.RegularExpressions;

namespace WinDX.UI
{
    public class DXApplication : BaseApplication
    {
        #region structs and enums    
        
        public enum Restriction
        {
            FULLY_RESTRICTED = 1,
            SOMEWHAT_RESTRICTED = 2,
            MINIMALLY_RESTRICTED = 3
        };

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
            public bool executeProgram;
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

            genericHelpCmd = new HelpMenuCommand("genericAppHelp",
                null, true, HelpMenuCommand.HelpType.GenericHelp);
            helpTutorialCmd = new HelpMenuCommand("helpTutorial",
                null, true, HelpMenuCommand.HelpType.HelpTutorial);

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
            connectToServerCmd = new NoUndoDXAppCommand("Start Server",
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

            NDAllocatorDictionary.theNDAllocatorDictionary = new NDAllocatorDictionary();

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
        public List<Network> macroList = new List<Network>();
        /// <summary>
        /// DX application commands
        /// </summary>
        /// 
        public Command genericHelpCmd;
        public Command helpTutorialCmd;

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

        protected DXWindow anchor = null;
        protected CommandScope commandScope = null;
        protected DXServerInfo serverInfo;
        protected DXExecCtl execCtl = new DXExecCtl();

        protected ApplicIF applicationPacket;

        protected MsgWin messageWindow;

        protected List<String> errorList = new List<string>();
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
        private bool isRestrictionLevel(Restriction level)
        {
            Debug.Assert(level > 0);
            String rlev = "";
            XmlPreferences.theXmlPreferences.GetPref("restrictionLevel", out rlev);
            if (rlev == null)
                return false;
            switch (level)
            {
                case Restriction.MINIMALLY_RESTRICTED:
                    if (rlev == "minimum")
                        return true;
                    break;
                case Restriction.SOMEWHAT_RESTRICTED:
                    if (rlev == "intermediate")
                        return true;
                    break;
                case Restriction.FULLY_RESTRICTED:
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

        private static void QueuedPacketAccept(Object sender, System.EventArgs e)
        {
            Control c = (Control)sender;
            if (c.Tag is DXPacketIF)
            {
                DXPacketIF p = (DXPacketIF)c.Tag;
                theDXApplication.packetIFAccept(p);
            } else 
                throw new Exception("Something went wrong, c.Tag not correct.");
        }

        private static void QueuedPacketCancel(Object sender, System.EventArgs e)
        {
            Control c = (Control)sender;
            if (c.Tag is DXPacketIF)
            {
                DXPacketIF p = (DXPacketIF)c.Tag;
                theDXApplication.packetIFCancel(p);
            } else
                throw new Exception("Something went wrong, c.Tag not correct.");
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
                this.network.getGroupManagers()[ProcessGroupManager.ProcessGroup];
        }

        #endregion

        #region Protected Methods

        /// <summary>
        /// If we're using an anchor window with its own copyright then be satisfied
        /// with that.  Otherwise use the superclass method.
        /// </summary>
        protected override void postCopyrightNotice()
        {
            if (anchor != null && anchor is DXAnchorWindow)
            {
                DXAnchorWindow dxa = (DXAnchorWindow) anchor;
                dxa.postCopyrightNotice();
            }
            else
                base.postCopyrightNotice();
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

        public virtual void clearErrorList()
        {
            foreach (String s in errorList)
            {
                highlightNodes(s, HighlightType.REMOVEHIGHLIGHT);
            }
            errorList.Clear();
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
            Debug.Assert(pif != null);
            pif.send(PacketIF.PacketType.FOREGROUND, "Executive(\"flush dictionary\");\n");
        }

        /// <summary>
        /// Handle acceptance of (connection to) a packet interface.
        /// </summary>
        /// <param name="p"></param>
        protected virtual void packetIFAccept(DXPacketIF p)
        {
            serverInfo.queuedPackets.Remove(p);
            if (serverInfo.packet != null)
            {
                serverInfo.packet = null;
                disconnectedFromServerCmd.execute();
            }
            serverInfo.packet = p;

            p.initializePacketIO();

            connectedToServerCmd.execute();
            sendNewMDFToServer(NodeDefinition.theNodeDefinitionDictionary);

            getExecCtl().newConnection();
        }

        /// <summary>
        /// Install the default resources for this class and then call the
        /// same super class method to get the default resources from the
        /// super classes.
        /// </summary>
        protected virtual void installDefaultResources()
        {
            String val;
            bool bval;
            int ival;

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
            XmlPreferences.theXmlPreferences.GetPref("foreground", out val);
            resource.foreground = Utils.ColorFromPoundString(val);
            XmlPreferences.theXmlPreferences.GetPref("background", out val);
            resource.background = Utils.ColorFromPoundString(val);
            XmlPreferences.theXmlPreferences.GetPref("anchorMode", out val);
            resource.anchorMode = val;
            XmlPreferences.theXmlPreferences.GetPref("DXVersion", out bval);
            resource.echoVersion = bval;
            XmlPreferences.theXmlPreferences.GetPref("debugMode", out bval);
            resource.debugMode = bval;
            XmlPreferences.theXmlPreferences.GetPref("showInstanceNumbers", out bval);
            resource.showInstanceNumbers = bval;
            XmlPreferences.theXmlPreferences.GetPref("directory", out val);
            resource.workingDirectory = val;
            XmlPreferences.theXmlPreferences.GetPref("executive", out val);
            resource.executive = val;
            XmlPreferences.theXmlPreferences.GetPref("executeProgram", out bval);
            resource.executeProgram = bval;
            XmlPreferences.theXmlPreferences.GetPref("executeOnChange", out bval);
            resource.executeOnChange = bval;
            XmlPreferences.theXmlPreferences.GetPref("printHelpMessage", out bval);
            resource.showHelpMessage = bval;
            XmlPreferences.theXmlPreferences.GetPref("host", out val);
            resource.server = val;
            XmlPreferences.theXmlPreferences.GetPref("noAnchorAtStartup", out bval);
            resource.noAnchorAtStartup = bval;
            XmlPreferences.theXmlPreferences.GetPref("noConfirmedQuit", out bval);
            resource.noConfirmedQuit = bval;
            XmlPreferences.theXmlPreferences.GetPref("macros", out val);
            resource.macros = val;
            XmlPreferences.theXmlPreferences.GetPref("memory", out ival);
            resource.memorySize = ival;
            XmlPreferences.theXmlPreferences.GetPref("metric", out bval);
            resource.isMetric = bval;
            XmlPreferences.theXmlPreferences.GetPref("messages", out val);
            resource.errorPath = val;
            XmlPreferences.theXmlPreferences.GetPref("port", out ival);
            resource.port = ival;
            XmlPreferences.theXmlPreferences.GetPref("printImageCommand", out val);
            resource.printImageCommand = val;
            XmlPreferences.theXmlPreferences.GetPref("printImageFormat", out val);
            resource.printImageFormat = val;
            XmlPreferences.theXmlPreferences.GetPref("printImagePageSize", out val);
            resource.printImagePageSize = val;
            XmlPreferences.theXmlPreferences.GetPref("printImageSize", out val);
            resource.printImageSize = val;
            XmlPreferences.theXmlPreferences.GetPref("printImageResolution", out ival);
            resource.printImageResolution = ival;
            XmlPreferences.theXmlPreferences.GetPref("program", out val);
            resource.program = val;
            XmlPreferences.theXmlPreferences.GetPref("cfg", out val);
            resource.cfgfile = val;
            XmlPreferences.theXmlPreferences.GetPref("runLocally", out bval);
            resource.runLocally = bval;
            XmlPreferences.theXmlPreferences.GetPref("runUIOnly", out bval);
            resource.runUIOnly = bval;
            XmlPreferences.theXmlPreferences.GetPref("saveImageFormat", out val);
            resource.saveImageFormat = val;
            XmlPreferences.theXmlPreferences.GetPref("saveImagePageSize", out val);
            resource.saveImagePageSize = val;
            XmlPreferences.theXmlPreferences.GetPref("saveImageSize", out val);
            resource.saveImageSize = val;
            XmlPreferences.theXmlPreferences.GetPref("saveImageResolution", out ival);
            resource.saveImageResolution = ival;
            XmlPreferences.theXmlPreferences.GetPref("suppressStartupWindows", out bval);
            resource.suppressStartupWindows = bval;
            XmlPreferences.theXmlPreferences.GetPref("userModuleDescriptionFile", out val);
            resource.userModules = val;
            XmlPreferences.theXmlPreferences.GetPref("executiveModuleDescriptionFile", out val);
            resource.executiveModule = val;
            XmlPreferences.theXmlPreferences.GetPref("uiModuleDescriptionFile", out val);
            resource.uiModule = val;
            XmlPreferences.theXmlPreferences.GetPref("noWindowPlacement", out bval);
            resource.noWindowPlacement = bval;
            XmlPreferences.theXmlPreferences.GetPref("restrictionLevel", out val);
            resource.restrictionLevel = val;
            XmlPreferences.theXmlPreferences.GetPref("noRWConfig", out bval);
            resource.noRWConfig = bval;
            XmlPreferences.theXmlPreferences.GetPref("noPanelEdit", out bval);
            resource.noPanelEdit = bval;
            XmlPreferences.theXmlPreferences.GetPref("noInteractorEdits", out bval);
            resource.noInteractorEdits = bval;
            XmlPreferences.theXmlPreferences.GetPref("noInteractorAttributes", out bval);
            resource.noInteractorAttributes = bval;
            XmlPreferences.theXmlPreferences.GetPref("noInteractorMovement", out bval);
            resource.noInteractorMovement = bval;
            XmlPreferences.theXmlPreferences.GetPref("noOpenAllPanels", out bval);
            resource.noOpenAllPanels = bval;
            XmlPreferences.theXmlPreferences.GetPref("noPanelAccess", out bval);
            resource.noPanelAccess = bval;
            XmlPreferences.theXmlPreferences.GetPref("noPanelOptions", out bval);
            resource.noPanelOptions = bval;
            XmlPreferences.theXmlPreferences.GetPref("noMessageInfoOption", out bval);
            resource.noMessageInfoOption = bval;
            XmlPreferences.theXmlPreferences.GetPref("noMessageWarningOption", out bval);
            resource.noMessageWarningOption = bval;
            XmlPreferences.theXmlPreferences.GetPref("noEditorOnError", out bval);
            resource.noEditorOnError = bval;
            XmlPreferences.theXmlPreferences.GetPref("noScriptCommands", out bval);
            resource.noScriptCommands = bval;
            XmlPreferences.theXmlPreferences.GetPref("noPGroupAssignment", out bval);
            resource.noPGroupAssignment = bval;
            XmlPreferences.theXmlPreferences.GetPref("noImageRWNetFile", out bval);
            resource.noImageRWNetFile = bval;
            XmlPreferences.theXmlPreferences.GetPref("limitedNetFileSelection", out bval);
            resource.limitedNetFileSelection = bval;
            XmlPreferences.theXmlPreferences.GetPref("netPath", out val);
            resource.netPath = val;
            XmlPreferences.theXmlPreferences.GetPref("noImageLoad", out bval);
            resource.noImageLoad = bval;
            XmlPreferences.theXmlPreferences.GetPref("noImageSaving", out bval);
            resource.noImageSaving = bval;
            XmlPreferences.theXmlPreferences.GetPref("noImagePrinting", out bval);
            resource.noImagePrinting = bval;
            XmlPreferences.theXmlPreferences.GetPref("limitImageOptions", out bval);
            resource.limitImageOptions = bval;
            XmlPreferences.theXmlPreferences.GetPref("notifySaveNet", out bval);
            resource.notifySaveNet = bval;
            XmlPreferences.theXmlPreferences.GetPref("noNetworkExecute", out bval);
            resource.noNetworkExecute = bval;
            XmlPreferences.theXmlPreferences.GetPref("noEditorAccess", out bval);
            resource.noEditorAccess = bval;
            XmlPreferences.theXmlPreferences.GetPref("noDXHelp", out bval);
            resource.noDXHelp = bval;
            XmlPreferences.theXmlPreferences.GetPref("noCMapSetNameOption", out bval);
            resource.noCMapSetNameOption = bval;
            XmlPreferences.theXmlPreferences.GetPref("noCMapOpenMap", out bval);
            resource.noCMapOpenMap = bval;
            XmlPreferences.theXmlPreferences.GetPref("noCMapSaveMap", out bval);
            resource.noCMapSaveMap = bval;
            XmlPreferences.theXmlPreferences.GetPref("applicationPort", out ival);
            resource.applicationPort = ival;
            XmlPreferences.theXmlPreferences.GetPref("applicationHost", out val);
            resource.applicationHost = val;
            XmlPreferences.theXmlPreferences.GetPref("infoEnabled", out bval);
            resource.infoEnabled = bval;
            XmlPreferences.theXmlPreferences.GetPref("warningEnabled", out bval);
            resource.warningEnabled = bval;
            XmlPreferences.theXmlPreferences.GetPref("errorEnabled", out bval);
            resource.errorEnabled = bval;
            XmlPreferences.theXmlPreferences.GetPref("moduleInfoOpensMessage", out bval);
            resource.moduleInfoOpensMessage = bval;
            XmlPreferences.theXmlPreferences.GetPref("infoOpensMessage", out bval);
            resource.infoOpensMessage = bval;
            XmlPreferences.theXmlPreferences.GetPref("warningOpensMessage", out bval);
            resource.warningOpensMessage = bval;
            XmlPreferences.theXmlPreferences.GetPref("errorOpensMessage", out bval);
            resource.errorOpensMessage = bval;
            XmlPreferences.theXmlPreferences.GetPref("useWindowSpecs", out bval);
            resource.useWindowSpecs = bval;
            XmlPreferences.theXmlPreferences.GetPref("forceNetFileEncryption", out bval);
            resource.forceNetFileEncryption = bval;
            XmlPreferences.theXmlPreferences.GetPref("cryptKey", out val);
            resource.cryptKey = val;
            XmlPreferences.theXmlPreferences.GetPref("exitAfter", out bval);
            resource.exitAfter = bval;
            XmlPreferences.theXmlPreferences.GetPref("noExecuteMenus", out bval);
            resource.noExecuteMenus = bval;
            XmlPreferences.theXmlPreferences.GetPref("noConnectionMenus", out bval);
            resource.noConnectionMenus = bval;
            XmlPreferences.theXmlPreferences.GetPref("noWindowsMenus", out bval);
            resource.noWindowsMenus = bval;
            XmlPreferences.theXmlPreferences.GetPref("noExitOptions", out bval);
            resource.noExitOptions = bval;
            XmlPreferences.theXmlPreferences.GetPref("noImageMenus", out bval);
            resource.noImageMenus = bval;
            XmlPreferences.theXmlPreferences.GetPref("oemApplicationName", out val);
            resource.oemApplicationName = val;
            XmlPreferences.theXmlPreferences.GetPref("oemApplicationNameCode", out val);
            resource.oemApplicationNameCode = val;
            XmlPreferences.theXmlPreferences.GetPref("viewDataFile", out val);
            resource.viewDataFile = val;
            XmlPreferences.theXmlPreferences.GetPref("autoScrollVPE", out bval);
            resource.autoScrollVPEInitVal = bval;
            XmlPreferences.theXmlPreferences.GetPref("autoLayoutHeight", out ival);
            resource.autoLayoutHeight = ival;
            XmlPreferences.theXmlPreferences.GetPref("autoLayoutGroupSpacing", out ival);
            resource.autoLayoutGroupSpacing = ival;
            XmlPreferences.theXmlPreferences.GetPref("autoLayoutNodeSpacing", out ival);
            resource.autoLayoutNodeSpacing = ival;
            XmlPreferences.theXmlPreferences.GetPref("cosmoDir", out val);
            resource.cosmoDir = val;
            XmlPreferences.theXmlPreferences.GetPref("jdkDir", out val);
            resource.jdkDir = val;
            XmlPreferences.theXmlPreferences.GetPref("htmlDir", out val);
            resource.htmlDir = val;
            XmlPreferences.theXmlPreferences.GetPref("serverDir", out val);
            resource.serverDir = val;
            XmlPreferences.theXmlPreferences.GetPref("dxJarFile", out val);
            resource.dxJarFile = val;
            XmlPreferences.theXmlPreferences.GetPref("userHtmlDir", out val);
            resource.userHtmlDir = val;
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
            runApplication = false;

            if (InEditMode && appAllowsSavingNetFile())
            {
                String defFile = "";
                getApplicationDefaultsFileName(ref defFile);

                XmlPreferences.theXmlPreferences.WritePrefs(defFile);
            }
            Application.Exit();
        }


        public override bool initialize(ref string[] argv)
        {
            bool wasSetBusy = false;

            base.initialize(ref argv);

            if (!DXApplication.DXApplicationClassInitialized)
            {
                installDefaultResources();
                DXApplicationClassInitialized = true;
            }

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
            if (resource.debugMode)
            {
                if (resource.port != 0)
                    Console.WriteLine("port        = {0}", resource.port);
                if (resource.memorySize != 0)
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
                    Console.WriteLine("application port = {0}", resource.applicationPort);
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
                Console.WriteLine("print image resolution = {0}",
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
                Console.WriteLine("save image resolution = {0}",
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
                    Console.WriteLine("automatic graph layout height = {0}",
                    resource.autoLayoutHeight);
                if (resource.autoLayoutGroupSpacing > 0)
                    Console.WriteLine("automatic graph layout group spacing = {0}",
                    resource.autoLayoutGroupSpacing);
                if (resource.autoLayoutNodeSpacing > 0)
                    Console.WriteLine("automatic graph layout node spacing = {0}",
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

            // Post the copyright message if the anchor window came up.
            if (!resource.noAnchorAtStartup)
                postCopyrightNotice();

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
            serverInfo.children = new List<DXChild>();
            serverInfo.queuedPackets = new List<DXPacketIF>();

            if (argv != null)
            {
                foreach (String arg in argv)
                {
                    serverInfo.executiveFlags += arg + " ";
                }
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
            }
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
                // Initialize the anchor window so it can handle reading in the network
                // before being managed.
                if (applyWindowPlacements() ||
                    resource.noAnchorAtStartup)
                {
                    anchor.Show();
                    anchor.Visible = true;
                }
                else
                {
                    anchor.Show();
                    anchor.Visible = true;
                    setBusyCursor(true);
                    wasSetBusy = true;
                }
            }
            else
            {
                anchor = newNetworkEditor(network);
                if (anchor == null)
                    return false;

                anchor.Show();
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
            {
                anchor.Show();
            }
            else if (!anchor.Visible)
            {
                anchor.Show();
                setBusyCursor(true);
                wasSetBusy = true;
            }

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

        public void highlightNodes(String path, HighlightType highlightType)
        {
            String name;
            int instance;

            path = GetErrorNode(path, out name, out instance);

            EditorWindow editor = network.getEditor();
            if (editor != null)
            {
                editor.highlightNode(name, instance, highlightType);
            }

            while (path != null && path.Length > 0)
            {
                String netname = name;
                path = GetErrorNode(path, out name, out instance);
                foreach (Network n in macroList)
                {
                    if (n.NameString == netname &&
                        n.getEditor() != null)
                    {
                        n.getEditor().highlightNode(name, instance, highlightType);
                        break;
                    }
                }
            }
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
            bool wasQueued = false;
            String server;

            if (c != null)
            {
                server = c.getServer();
                if (!c.IsQueued)
                {
                    serverInfo.children.Remove(c);
                    c.unQueue();
                }
            }
            else
            {
                server = serverInfo.server;
            }
            DXPacketIF p = new DXPacketIF(server, port, DXChild.HostIsLocal(server));
            if (DXApplication.resource.debugMode)
                p.setEchoCallback(DXApplication.DebugEchoCallback, "need to get stderr");

            if (p.Error)
            {
                ErrorDialog ed = new ErrorDialog();
                ed.post("Connection to {0} failed.", server);
                p = null;
                return 0;
            }

            clearErrorList();
            if (serverInfo.packet == null)
            {
                if (wasQueued)
                {
                    InfoDialog id = new InfoDialog();
                    id.post("Your connection to {0} has been accepted.", server);
                }
                packetIFAccept(p);
            }
            else
            {
                serverInfo.queuedPackets.Insert(0, p);
                QuestionDialog qd = new QuestionDialog();
                String s = String.Format("Your connection to server {0} has been accepted. Do you want to disconnect from {0} and connect to it?",
                    server, serverInfo.server);
                qd.modalPost(this.getAnchorForm(), s, null, p, DXApplication.QueuedPacketAccept, 
                    DXApplication.QueuedPacketCancel, null, "Yes", "No", null, 2);
                    
            }
            return 1;
        }

        public void closeConnection(DXChild c)
        {
            throw new Exception("Not Yet Implemented");
        }

        public void completeConnection(DXChild c)
        {
            if (c != null)
            {
                switch (c.waitForConnection())
                {
                    case -1:
                        ErrorDialog ed = new ErrorDialog();
                        ed.post("Connection to server {0} failed: {1}",
                            c.getServer(), c.failed());
                        closeConnection(c);
                        break;
                    case 0:
                        if (resource.executeProgram)
                            getExecCtl().executeOnce();
                        break;
                    case 1:
                        InfoDialog id = new InfoDialog();
                        id.post("Connection to server {0} has been queued", c.getServer());
                        break;
                }
            }
            else if (!serverInfo.autoStart)
            {
                connectToServer(serverInfo.port, null);
            }

            // Let the application packet know that a new connection to
            // the server has been created. 
            if (applicationPacket != null)
                applicationPacket.handleServerConnection();

            if (resource.executeOnChange)
                getExecCtl().enableExecOnChange();
        }

        public DXChild startServer()
        {
            List<String> args = new List<String>();
            int i = 0;

            args.Add("dx");

            if (serverInfo.autoStart)
            {
                args.Add("-exonly");
                args.Add("-local");

                if (serverInfo.memorySize > 0)
                {
                    args.Add("-memory");
                    args.Add(serverInfo.memorySize.ToString());
                }

                if (serverInfo.executive != null)
                {
                    serverInfo.executive.Trim();
                    if (serverInfo.executive.Length > 0)
                    {
                        args.Add("-exec");
                        args.Add(serverInfo.executive);
                    }
                }

                if (serverInfo.workingDirectory != null)
                {
                    serverInfo.workingDirectory.Trim();
                    if (serverInfo.workingDirectory.Length > 0)
                    {
                        args.Add("-directory");
                        if (serverInfo.workingDirectory.Contains(" ") &&
                            !serverInfo.workingDirectory.Contains("\""))
                            args.Add("\"" + serverInfo.workingDirectory + "\"");
                        else
                            args.Add(serverInfo.workingDirectory);
                    }
                }
                
                if (serverInfo.userModules != null && 
                    serverInfo.userModules.Length > 0)
                {
                    args.Add("-mdf");
                    args.Add(serverInfo.userModules);
                }

                if (serverInfo.executiveFlags != null)
                {
                    serverInfo.executiveFlags.Trim();
                    if (serverInfo.executiveFlags.Length > 0)
                        args.Add(serverInfo.executiveFlags);
                }

                String[] argArr = new String[args.Count];
                for (int j = 0; j < args.Count; j++)
                    argArr[j] = args[j];

                DXChild c = new DXChild(serverInfo.server, argArr, false);
                if (c.failed() != null)
                {
                    argArr[0] = this.getUIRoot() + "/bin/dx";
                    c = new DXChild(serverInfo.server, argArr, false);
                }

                serverInfo.children.Insert(0, c);
                return c;
            }
            else
                return null;
        }

        public void setServer(String server)
        {
            throw new Exception("Not Yet Implemented");
        }

        public DXPacketIF getPacketIF() { return this.serverInfo.packet; }
        public DXExecCtl getExecCtl() { return this.execCtl; }


        public virtual bool openFile(String netfile)
        {
            return openFile(netfile, null);
        }
        public virtual bool openFile(String netfile,
            String cfgfile)
        {
            return openFile(netfile, cfgfile, true);
        }
        public virtual bool openFile(String netfile,
            String cfgfile, bool resetTheServer)
        {
            Network net = this.network;
            bool execOnChange = getExecCtl().inExecOnChange();
            bool result;

            if (execOnChange)
                getExecCtl().suspendExecOnChange();

            if (resetTheServer)
                resetServer();

            // We can't do this until after resetting the server, because
            // it has to clean up its windows too.
            net.clear();

            if ((result = net.readNetwork(netfile, cfgfile)) == false)
            {
                if (execOnChange)
                {
                    getExecCtl().updateMacros();
                    getExecCtl().resumeExecOnChange();
                }
                appendReferencedFile(netfile);
            }
            readFirstNetwork = true;
            return result;
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
            getExecCtl().terminateExecution();

            clearErrorList();

            markNetworksDirty();
            thisServer.notifyClients(MsgServerDisconnected);

            DXPacketIF pif = getPacketIF();
            if (pif != null)
            {
                flushExecutiveDictionaries(pif);

                pif.send(PacketIF.PacketType.FOREGROUND, "Trace(\"memory\", 0);\n");

                String message = String.Format("Executive(\"version {0} {1} {2}\");\n",
                global::WinDX.UI.Resources.PIF_MAJOR_VERSION,
                global::WinDX.UI.Resources.PIF_MINOR_VERSION,
                global::WinDX.UI.Resources.PIF_MICRO_VERSION);

                pif.send(PacketIF.PacketType.FOREGROUND, message);
            }

            return true;
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
            OpenFileDialog openNetworkDialog = new OpenFileDialog();
            openNetworkDialog.Filter = "Network Files (*.net)|*.NET";
            openNetworkDialog.FilterIndex = 0;

            openNetworkDialog.FileOk += new System.ComponentModel.CancelEventHandler(OpenNetworkDialog_FileOk);
            openNetworkDialog.ShowDialog(this.anchor);

        }
        void OpenNetworkDialog_FileOk(object sender, System.ComponentModel.CancelEventArgs e)
        {
            OpenFileDialog ofd = (OpenFileDialog)sender;
            DXApplication.theDXApplication.getExecCtl().terminateExecution();
            DXApplication.theDXApplication.openFile(ofd.FileName);
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
        public String ServerName { get { return serverInfo.server; } }

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
            String msg = "";
            Debug.Assert(n != null);

            if (!this.appAllowsEditorAccess())
            {
                msg = "This invocation of Data Explorer does not allow editor " +
                    "access (-edit). \n" +
                    "Try image mode (-image).";
                InfoDialog id = new InfoDialog();
                id.post(msg);
                return null;
            }
            bool is_anchor;
            if (anchor == null)
                is_anchor = true;
            else
                is_anchor = false;

            return new EditorWindow(is_anchor, n);
        }

        public virtual Network newNetwork()
        {
            return newNetwork(false);
        }
        public virtual Network newNetwork(bool nonJava)
        {
            Network n;
            if (nonJava)
                n = new Network();
            else
                n = new JavaNet();
            return n;
        }
        public virtual MsgWin newMsgWin()
        {
            return new MsgWin();
        }
        public virtual ImageWindow newImageWindow(Network n)
        {
            bool is_anchor;

            Debug.Assert(n != null);

            if (this.anchor == null)
                is_anchor = true;
            else
                is_anchor = false;

            return new ImageWindow(is_anchor, n);
        }
        public virtual ControlPanel newControlPanel(Network n)
        {
            throw new Exception("Not Yet Implemented");
        }

        public virtual void addErrorList(String line)
        {
            int chr = line.IndexOf('/');
            int second_slash = -1;
            String newline = null;
            if(chr >= 0)
                newline = line.Substring(chr);

            if (newline != null && (second_slash = newline.IndexOf('/')) >= 0)
            {
                String name = network.getNameString();
                if (!newline.StartsWith(name))
                    return;

                String node_id = newline.Substring(second_slash);
                errorList.Add(node_id);

                // Don't highlight until after execution.
                // Highlighting is now done in DXExecCtl::endLastExecution() by
                // calling this->refreshErrorIndicators().
                if (!getExecCtl().isExecuting())
                    highlightNodes(node_id, HighlightType.ERRORHIGHLIGHT);
            }
            else if (line.Contains("PEER ABORT - "))
            {
                // One of the distributed peers aborted abnormally.
                // Unhighlight all the modules.
                // FIXME: If we don't unhighlight, the aborted module is still
                // highlighted green, so we could go through the process group
                // and mark the greens modules as error modules.
                Network n = this.network;
                EditorWindow e = n.getEditor();
                if (e != null)
                    e.highlightNodes(HighlightType.REMOVEHIGHLIGHT);

                foreach (Network mn in macroList)
                {
                    e = mn.getEditor();
                    if (e != null)
                        e.highlightNodes(HighlightType.REMOVEHIGHLIGHT);
                }

                // This is similar to a disconnect, so make sure the user knows.
                ErrorDialog ed = new ErrorDialog();
                ed.post(line.Substring(line.IndexOf("PEER ABORT - ") + 13));
            }
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
            // This also effectively marks the parameters as dirty.
            getExecCtl().forceFullResend();
        }

        public bool DoesInfoOpenMessage
        {
            get
            {
                return doesInfoOpenMessage(false);
            }
        }
        public bool doesInfoOpenMessage(bool fromModule)
        {
            return (resource.infoOpensMessage ||
                (fromModule && resource.moduleInfoOpensMessage)) &&
                IsInfoEnabled;
        }
        public bool DoesWarningOpenMessage
        {
            get { return resource.warningOpensMessage && IsWarningEnabled; }
        }
        public bool DoesErrorOpenMessage
        {
            get { return resource.errorOpensMessage && IsErrorEnabled; }
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

        public DXWindow getAnchor()
        {
            return this.anchor;
        }
        public bool appAllowsConfirmedQuit()
        {
            return !resource.noConfirmedQuit;
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
            String buf;
            bool sent_stuff = false;
            DXPacketIF pif = getPacketIF();

            if (pif == null)
                return;

            Debug.Assert(newdefs != null);
            foreach (KeyValuePair<Symbol, NodeDefinition> kvp in newdefs)
            {
                NodeDefinition nd = kvp.Value;
                bool outboard = nd.IsOutboard;
                bool dynamic = nd.IsDynamicallyLoaded;

                // The following requires that the exec sees the -mdf options
                // that the UI sees.
                bool send = (outboard || dynamic) && nd.UILoadedOnly;

                // See if a definition already existed and if the outboardness or 
                // the dynamicity changes (e.g. outboard -> inboard) we must resend
                // the new definition.
                if (!send && current != null)
                {
                    Symbol s = nd.NameSymbol;
                    NodeDefinition olddef;
                    if (current.TryGetValue(s, out olddef))
                    {
                        send = (olddef.IsOutboard != outboard ||
                            olddef.IsDynamicallyLoaded != dynamic);
                    }
                }

                // If we're supposed to send this definition and the node has one,
                // then lets send it.
                String mdf = nd.getMDFString();
                if (send && mdf != null)
                {
                    Regex regex = new Regex(@"""");
                    mdf = regex.Replace(mdf, @"\\""");
                    regex = new Regex(@"\n");
                    mdf = regex.Replace(mdf, @"\\\n");
                    buf = "Executive(\"mdf string\",\"" + mdf + "\");\n";
                    pif.send(PacketIF.PacketType.FOREGROUND, buf);
                    sent_stuff = true;
                }
            }


        }

        //
        // Define a set of methods that indicate a level of UI capability. 
        //
        public virtual bool appAllowsDXHelp()
        {
            return (!resource.noDXHelp &&
                getOEMApplicationName() == null);
        }
        public virtual bool appSuppressesStartupWindows()
        {
            return resource.suppressStartupWindows;
        }
        public virtual bool appLimitsNetFileSelection()
        {
            return resource.limitedNetFileSelection;
        }

        public virtual bool appAllowsPanelEdit()
        {
            throw new Exception("Not Yet Implemented");
        }
        public virtual bool appAllowsRWConfig()
        {
            return !isRestrictionLevel(Restriction.FULLY_RESTRICTED) &&
                !resource.noRWConfig;
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
            return !isRestrictionLevel(Restriction.SOMEWHAT_RESTRICTED) &&
                !resource.noImageRWNetFile;
        }
        public virtual bool appAllowsSavingNetFile()
        {
            return appAllowsSavingNetFile(null);
        }
        public virtual bool appAllowsSavingNetFile(Network net)
        {
            return appAllowsSavingCfgFile() &&
                (net == null || !net.WasNetFileEncoded);
        }
        public virtual bool appAllowsSavingCfgFile()
        {
            return (InEditMode || appAllowsImageRWNetFile());
        }
        public virtual bool appAllowsImageLoad()
        {
            return !isRestrictionLevel(Restriction.SOMEWHAT_RESTRICTED) &&
                !resource.noImageLoad;
        }
        public virtual bool appAllowsImageSaving()
        {
            return !isRestrictionLevel(Restriction.FULLY_RESTRICTED) &&
                !resource.noImageSaving;
        }
        public virtual bool appAllowsImagePrinting()
        {
            return !resource.noImagePrinting;
        }
        public virtual bool appLimitsImageOptions()
        {
            return isRestrictionLevel(Restriction.MINIMALLY_RESTRICTED) ||
                resource.limitImageOptions;
        }

        public virtual bool appAllowsEditorAccess()
        {
            return !isRestrictionLevel(Restriction.MINIMALLY_RESTRICTED) &&
                !resource.noEditorAccess;
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
            return !resource.noExitOptions;
        }
        public bool appAllowsExecuteMenus()
        {
            throw new Exception("Not Yet Implemented");
        }
        public bool appAllowsConnectionMenus()
        {
            return !resource.noConnectionMenus;
        }
        public bool appAllowsWindowsMenus()
        {
            throw new Exception("Not Yet Implemented");
        }
        public bool appAllowsImageMenus()
        {
            return !resource.noImageMenus;
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
            String s = getOEMApplicationName();
            if (s == null)
                s = "Data Explorer";
            return s;
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
            String s = getOEMApplicationName();
            if (s == null || s.Length == 0)
                return global::WinDX.UI.Resources.CopyrightString;
            else
                return null;
        }

        /// <summary>
        /// Go through the error list and highlight all nodes that got errors.
        /// </summary>
        public void refreshErrorIndicators()
        {
            if (errorList.Count == 0)
                return;

            foreach (String s in errorList)
            {
                highlightNodes(s, HighlightType.ERRORHIGHLIGHT);
            }
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
            return !resource.noWindowPlacement;
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
            // Don't include files that go in /tmp.  These are files
            // that are created as a result of Cut,Copy,Paste and 
            // Drag-n-Drop and shouldn't be recorded here.
            String tmpdir = getTmpDirectory();
            if (file.StartsWith(tmpdir))
            {
                return;
            }

            String cp = Utils.GetFullFilePath(file);
            XmlPreferences.theXmlPreferences.AddListPref("recentNets", cp);
        }
        public void removeReferencedFile(String file)
        {
            throw new Exception("Not Yet Implemented");
        }
        public void getRecentNets(out List<String> result)
        {
            XmlPreferences.theXmlPreferences.GetPref("recentNets", out result);
        }

        public static String GetErrorNode(String path, out String name, out int instance)
        {
            String namep;
            Regex regex = new Regex(@"(.*):(\d+)");
            Match m = regex.Match(path);
            if (!m.Success)
            {
                name = "";
                instance = 0;
                return null;
            }
            name = m.Groups[1].Value;
            instance = int.Parse(m.Groups[2].Value);

            int loc = name.IndexOf('_') - 1;
            if (loc >= 0)
            {
                namep = name.Substring(loc);
                if (namep.StartsWith("_Image"))
                    name = "Image";
            }

            loc = path.IndexOf('/');
            if (loc >= 0)
                path = path.Substring(loc+1);
            else
                path = null;

            return path;
        }

        #endregion
    }
}
