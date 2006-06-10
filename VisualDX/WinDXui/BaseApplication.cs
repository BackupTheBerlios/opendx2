using System;
using System.Collections.Generic;
using System.Text;
using System.Diagnostics;
using System.Reflection;
using System.IO;
using System.Windows.Forms;

namespace WinDX.UI
{
    public enum PrintType
    {
        PrintExec = 0,     // Destination: exec
        PrintFile,         // Destination: file
        PrintCut,          // Destination: cut/paste
        PrintCPBuffer      // Destination: cut/paste
    };

    public enum DirectInteractionMode
    {
        NONE,
        CAMERA,
        CURSORS,
        PICK,
        NAVIGATE,
        PANZOOM,
        ROAM,
        ROTATE,
        ZOOM
    };

    public enum Cacheability
    {
        //
        // Define constants that indicate the module level cacheability. 
        // NOTE: The number assignments used here should match those used by the
        // server to determine cacheability.
        //
        ModuleNotCached = 0,
        ModuleFullyCached = 1,
        ModuleCacheOnce = 2,

        //
        // This used to define the cacheability of various entities in the server.
        // For now those entities include the Nodes outputs (cached based on all
        // the input values) and individual inputs and outputs.
        // NOTE: The number assignments used here should match those used by the
        // server to determine cacheability.
        // Further, note that the code may assume the these values map 1 to 1 ont
        // the Module* cache enumated values.
        //
        OutputNotCached = 0,
        OutputFullyCached = 1,
        OutputCacheOnce = 2,

        // 
        // Used to define cacheability internal to a system macro (in
        // particular, the Image macro)
        InternalsNotCached = 0,
        InternalsFullyCached = 1,
        InternalsCacheOnce = 2,

        // 
        // Used to map cache attributes on INPUT statemtents in the mdf files.
        // 'cache:0' means that the input is not used to derived the output cache
        // tag, where 'cache:1' means the opposite.
        // NOTE: The number assignments used here should match those used by the
        // mdf file. 
        //
        InputDoesNotDeriveOutputCacheTag = 0,	// 'cache:0'
        InputDerivesOutputCacheTag = 1 		// 'cache:1'
    };

    public enum Alignment
    {
        None,
        Beginning,
        Center,
        End
    }

    public abstract class BaseApplication
    {
        #region Application
        private static bool ApplicationClassInitialized = false;
        private int busyCursors = 0;
        private String name = null;
        public Server thisServer = null;

        private bool tooltip = false;
        private Form root = null;

        public bool ToolTips
        {
            get { return tooltip; }
            set { tooltip = value; }
        }

        public static readonly Symbol MsgCreate = Symbol.zero;
        public static readonly Symbol MsgManage = Symbol.zero;
        public static readonly Symbol MsgUnmanage = Symbol.zero;
        public static readonly Symbol MsgSetBusyCursor = Symbol.zero;
        public static readonly Symbol MsgResetCursor = Symbol.zero;
        public static readonly Symbol MsgManageByLeafClassName = Symbol.zero;
        public static readonly Symbol MsgUnmanageByLeafClassName = Symbol.zero;
        public static readonly Symbol MsgManageByTitle = Symbol.zero;
        public static readonly Symbol MsgUnmanageByTitle = Symbol.zero;

        protected String applicationClass = null;

        static BaseApplication()
        {
            if (!ApplicationClassInitialized)
            {
                if (SymbolManager.theSymbolManager == null)
                {
                    StackFrame stackFrame = new StackFrame();
                    MethodBase methodBase = stackFrame.GetMethod();
                    throw new Exception(string.Format("{0}: symbolManager not init'd", methodBase));
                }

                MsgCreate = SymbolManager.theSymbolManager.registerSymbol("Create");
                MsgManage = SymbolManager.theSymbolManager.registerSymbol("Manage");
                MsgUnmanage = SymbolManager.theSymbolManager.registerSymbol("Unmanage");
                MsgSetBusyCursor = SymbolManager.theSymbolManager.registerSymbol("SetBusyCursor");
                MsgResetCursor = SymbolManager.theSymbolManager.registerSymbol("ResetCursor");
                MsgManageByLeafClassName = SymbolManager.theSymbolManager.registerSymbol("ManageByLeafClassName");
                MsgUnmanageByLeafClassName = SymbolManager.theSymbolManager.registerSymbol("UnmanageByLeafClassName");
                MsgManageByTitle = SymbolManager.theSymbolManager.registerSymbol("ManageByTitle");
                MsgUnmanageByTitle = SymbolManager.theSymbolManager.registerSymbol("UnmanageByTitle");

                ApplicationClassInitialized = true;
            }
        }
        public BaseApplication(String className)
        {
            Debug.Assert(className != null);
            
            name = className;
            aboutAppString = null;
            thisServer = new Server();
        }

        /// <summary>
        /// Given the command line args, parse them and set up
        /// theXmlPreferences.
        /// </summary>
        /// <param name="argv"></param>
        protected virtual String[] parseCommand(String[] argv)
        {
            String res_file = null;
            List<String> newargv = new List<String>();

            if (getApplicationDefaultsFileName(ref res_file, false))
            {
                if (!XmlPreferences.theXmlPreferences.ReadPrefs(res_file))
                {
                    throw new Exception("Preference File Corrupted. Please delete it and restart!");
                }
            }
            else
                XmlPreferences.theXmlPreferences.CreatePrefs();

            for (int i = 0; i < argv.Length; i++)
            {
                char nafc = '\0';
                String arg = argv[i];
                if (i < argv.Length - 1)
                {
                    String arg1 = argv[i + 1];
                    char[] ca = arg1.ToCharArray();
                    nafc = ca[0];
                }
                if (NOARGtrue(arg, "-wizard", "wizard")) { }
                else if (ARGStr(arg, "-edit", "anchorMode", "EDIT")) { }
                else if (NOARGtrue(arg, "-execute", "executeProgram")) { }
                else if (NOARGtrue(arg, "-execute_on_change", "executeOnChange")) { }
                else if (NOARGtrue(arg, "-help", "printHelpMessage")) { }
                else if (ARGStr(arg, "-image", "anchorMode", "IMAGE")) { }
                else if (ARGStr(arg, "-kiosk", "anchorMode", "MENUBAR")) { }
                else if (ARGStr(arg, "-menubar", "anchorMode", "MENUBAR")) { }
                else if (NOARGtrue(arg, "-noAnchorAtStartup", "noAnchorAtStartup")) { }
                else if (NOARGtrue(arg, "-noConfirmedQuit", "noConfirmedQuit")) { }
                else if (NOARGtrue(arg, "-local", "runLocally")) { }
                else if (NOARGtrue(arg, "-metric", "metric")) { }
                else if (NOARGtrue(arg, "-suppress", "suppressStartupWindows")) { }
                else if (NOARGtrue(arg, "-uidebug", "debugMode")) { }
                else if (NOARGtrue(arg, "-showInstanceNumbers", "showInstanceNumbers")) { }
                else if (NOARGtrue(arg, "-uionly", "runUIOnly")) { }
                else if (NOARGtrue(arg, "-version", "DXVersion")) { }
                //Backdoor Switches
                else if (NOARGtrue(arg, "-noDXHelp", "noDXHelp")) { }
                else if (NOARGtrue(arg, "-noEditorAccess", "noEditorAccess")) { }
                else if (NOARGtrue(arg, "-notifySaveNet", "notifySaveNet")) { }
                else if (NOARGtrue(arg, "-noNetworkExecute", "noNetworkExecute")) { }
                else if (NOARGtrue(arg, "-noImageRWNetFile", "noImageRWNetFile")) { }
                else if (NOARGtrue(arg, "-noImageLoad", "noImageLoad")) { }
                else if (NOARGtrue(arg, "-limitImageOptions", "limitImageOptions")) { }
                else if (NOARGtrue(arg, "-limitedNetFileSelection", "limitedNetFileSelection")) { }
                else if (NOARGtrue(arg, "-noNetFileSelection", "noNetFileSelection")) { }
                else if (NOARGtrue(arg, "-noImageSaving", "noImageSaving")) { }
                else if (NOARGtrue(arg, "-noImagePrinting", "noImagePrinting")) { }
                else if (NOARGtrue(arg, "-noInteractorMovement", "noInteractorMovement")) { }
                else if (NOARGtrue(arg, "-noOpenAllPanels", "noOpenAllPanels")) { }
                else if (NOARGtrue(arg, "-noPanelAccess", "noPanelAccess")) { }
                else if (NOARGtrue(arg, "-noPanelOptions", "noPanelOptions")) { }
                else if (NOARGtrue(arg, "-noPanelEdit", "noPanelEdit")) { }
                else if (NOARGtrue(arg, "-noRWConfig", "noRWConfig")) { }
                else if (NOARGtrue(arg, "-noScriptCommands", "noScriptCommands")) { }
                else if (NOARGtrue(arg, "-noMessageInfoOption", "noMessageInfoOption")) { }
                else if (NOARGtrue(arg, "-noEditorOnError", "noEditorOnError")) { }
                else if (NOARGtrue(arg, "-noCMapSetNameOption", "noCMapSetNameOption")) { }
                else if (NOARGtrue(arg, "-noCMapSaveMap", "noCMapSaveMap")) { }
                else if (NOARGtrue(arg, "-noWindowPlacement", "noWindowPlacement")) { }
                else if (NOARGtrue(arg, "-noCMapOpenMap", "noCmapOpenMap")) { }
                else if (NOARGtrue(arg, "-noPGroupAssignment", "noPGroupAssignement")) { }
                else if (NOARGtrue(arg, "-warning", "warningEnabled")) { }
                else if (NOARGtrue(arg, "-info", "infoEnabled")) { }
                else if (NOARGtrue(arg, "-error", "errorEnabled")) { }
                else if (NOARGtrue(arg, "-exitAfter", "exitAfter")) { }
                else if (NOARGtrue(arg, "-noExecuteMenus", "noExecuteMenus")) { }
                else if (NOARGtrue(arg, "-noConnectionMenus", "noConnectionMenus")) { }
                else if (NOARGtrue(arg, "-noWindowsMenus", "noWindowsMenus")) { }
                else if (NOARGtrue(arg, "-noExitOptions", "noExitOptions")) { }
                else if (NOARGtrue(arg, "-noImageMenus", "noImageMenus")) { }
                else if (NOARGfalse(arg, "-noAutoScrollVPE", "noAutoScrollVPE")) { }

                else if (argv.Length == i + 1 || nafc == '-')
                {
                    Console.WriteLine("Missing argument for {0}", argv[i]);
                    Environment.Exit(1);
                }
                else if (ARGStr(arg, "-uiroot", "UIRoot", argv[i + 1])) { i++; }
                else if (ARGStr(arg, "-dismissedWizards", "dismissedWizards", argv[i + 1])) { i++; }
                else if (ARGStr(arg, "-exec", "executive", argv[i + 1])) { i++; }
                else if (ARGStr(arg, "-directory", "directory", argv[i + 1])) { i++; }
                else if (ARGStr(arg, "-memory", "memory", argv[i + 1])) { i++; }
                else if (ARGStr(arg, "-host", "host", argv[i + 1])) { i++; }
                else if (ARGStr(arg, "-macros", "macros", argv[i + 1])) { i++; }
                else if (ARGStr(arg, "-mdf", "userModuleDescriptionFile", argv[i + 1])) { i++; }
                else if (ARGStr(arg, "-dxmdf", "executiveModuleDescriptionFile", argv[i + 1])) { i++; }
                else if (ARGStr(arg, "-uimdf", "uiModuleDescriptionFile", argv[i + 1])) { i++; }
                else if (ARGStr(arg, "-port", "port", argv[i + 1])) { i++; }
                else if (ARGStr(arg, "-printImageFormat", "printImageFormat", argv[i + 1])) { i++; }
                else if (ARGStr(arg, "-printImagePageSize", "printImagePageSize", argv[i + 1])) { i++; }
                else if (ARGStr(arg, "-printImageSize", "printImageSize", argv[i + 1])) { i++; }
                else if (ARGStr(arg, "-printImageResolution", "printImageResolution", argv[i + 1])) { i++; }
                else if (ARGStr(arg, "-program", "program", argv[i + 1])) { i++; }
                else if (ARGStr(arg, "-cfg", "cfg", argv[i + 1])) { i++; }
                else if (ARGStr(arg, "-saveImageFormat", "saveImageFormat", argv[i + 1])) { i++; }
                else if (ARGStr(arg, "-saveImagePageSize", "saveImagePageSize", argv[i + 1])) { i++; }
                else if (ARGStr(arg, "-saveImageSize", "saveImageSize", argv[i + 1])) { i++; }
                else if (ARGStr(arg, "-saveImageResolution", "saveImageResolution", argv[i + 1])) { i++; }
                else if (ARGStr(arg, "-uimessages", "messages", argv[i + 1])) { i++; }
                // Backdoor Switches
                else if (ARGStr(arg, "-restrictionLevel", "restrictionLevel", argv[i + 1])) { i++; }
                else if (ARGStr(arg, "-appHost", "applicationHost", argv[i + 1])) { i++; }
                else if (ARGStr(arg, "-appPort", "applicationPort", argv[i + 1])) { i++; }
                else if (ARGStr(arg, "-netPath", "netPath", argv[i + 1])) { i++; }
                else if (ARGStr(arg, "-forceNetFileEncryption", "forceNetFileEncryption", argv[i + 1])) { i++; }
                else if (ARGStr(arg, "-cryptKey", "cryptKey", argv[i + 1])) { i++; }
                else if (ARGStr(arg, "-forceLicense", "forceLicense", argv[i + 1])) { i++; }
                else if (ARGStr(arg, "-view", "viewDataFile", argv[i + 1])) { i++; }
                else if (ARGStr(arg, "-autoLayoutHeight", "autoLayoutHeight", argv[i + 1])) { i++; }
                else if (ARGStr(arg, "-autoLayoutGroupSpacing", "autoLayoutGroupSpacing", argv[i + 1])) { i++; }
                else if (ARGStr(arg, "-autoLayoutNodeSpacing", "autoLayoutNodeSpacing", argv[i + 1])) { i++; }
                else
                {
                    newargv.Add(arg);
                }
            }

            XmlPreferences.theXmlPreferences.SetDefault("standInBackground", XmlPreferences.PrefType.TypeString, "#5F9EA0");
            XmlPreferences.theXmlPreferences.SetDefault("executionHighlightForeground", XmlPreferences.PrefType.TypeString, "#00ff7e");
            XmlPreferences.theXmlPreferences.SetDefault("backgroundExecutionForeground", XmlPreferences.PrefType.TypeString, "#7e7eb4");
            XmlPreferences.theXmlPreferences.SetDefault("errorHighlightForeground", XmlPreferences.PrefType.TypeString, "#ff9b00");
            XmlPreferences.theXmlPreferences.SetDefault("foreground", XmlPreferences.PrefType.TypeString, "Black");
            XmlPreferences.theXmlPreferences.SetDefault("background", XmlPreferences.PrefType.TypeString, "#b4b4b4");
            XmlPreferences.theXmlPreferences.SetDefault("InsensitiveColor", XmlPreferences.PrefType.TypeString, "#888888");
            XmlPreferences.theXmlPreferences.SetDefault("anchorMode", XmlPreferences.PrefType.TypeString, "EDIT");
            XmlPreferences.theXmlPreferences.SetDefault("DXVersion", XmlPreferences.PrefType.TypeBool, "false");
            XmlPreferences.theXmlPreferences.SetDefault("debugMode", XmlPreferences.PrefType.TypeBool, "false");
            XmlPreferences.theXmlPreferences.SetDefault("showInstanceNumbers", XmlPreferences.PrefType.TypeBool, "false");
            XmlPreferences.theXmlPreferences.SetDefault("directory", XmlPreferences.PrefType.TypeString, "");
            XmlPreferences.theXmlPreferences.SetDefault("executive", XmlPreferences.PrefType.TypeString, "");
            XmlPreferences.theXmlPreferences.SetDefault("executeProgram", XmlPreferences.PrefType.TypeBool, "false");
            XmlPreferences.theXmlPreferences.SetDefault("executeOnChange", XmlPreferences.PrefType.TypeBool, "false");
            XmlPreferences.theXmlPreferences.SetDefault("printHelpMessage", XmlPreferences.PrefType.TypeBool, "false");
            XmlPreferences.theXmlPreferences.SetDefault("host", XmlPreferences.PrefType.TypeString, "");
            XmlPreferences.theXmlPreferences.SetDefault("noAnchorAtStartup", XmlPreferences.PrefType.TypeBool, "false");
            XmlPreferences.theXmlPreferences.SetDefault("noConfirmedQuit", XmlPreferences.PrefType.TypeBool, "false");


            XmlPreferences.theXmlPreferences.SetDefault("memory", XmlPreferences.PrefType.TypeInt, "0");
            XmlPreferences.theXmlPreferences.SetDefault("metric", XmlPreferences.PrefType.TypeBool, "false");
            XmlPreferences.theXmlPreferences.SetDefault("messages", XmlPreferences.PrefType.TypeString, "");
            XmlPreferences.theXmlPreferences.SetDefault("port", XmlPreferences.PrefType.TypeInt, "0");
            XmlPreferences.theXmlPreferences.SetDefault("printImageCommand", XmlPreferences.PrefType.TypeString, "lpr");
            XmlPreferences.theXmlPreferences.SetDefault("printImageFormat", XmlPreferences.PrefType.TypeString, "TIFF");
            XmlPreferences.theXmlPreferences.SetDefault("printImagePageSize", XmlPreferences.PrefType.TypeString, "");
            XmlPreferences.theXmlPreferences.SetDefault("printImageSize", XmlPreferences.PrefType.TypeString, "");
            XmlPreferences.theXmlPreferences.SetDefault("printImageResolution", XmlPreferences.PrefType.TypeInt, "0");
            XmlPreferences.theXmlPreferences.SetDefault("program", XmlPreferences.PrefType.TypeString, "");
            XmlPreferences.theXmlPreferences.SetDefault("cfg", XmlPreferences.PrefType.TypeString, "");
            XmlPreferences.theXmlPreferences.SetDefault("runLocally", XmlPreferences.PrefType.TypeBool, "false");
            XmlPreferences.theXmlPreferences.SetDefault("runUIOnly", XmlPreferences.PrefType.TypeBool, "false");
            XmlPreferences.theXmlPreferences.SetDefault("saveImageFormat", XmlPreferences.PrefType.TypeString, "");
            XmlPreferences.theXmlPreferences.SetDefault("saveImagePageSize", XmlPreferences.PrefType.TypeString, "");
            XmlPreferences.theXmlPreferences.SetDefault("saveImageSize", XmlPreferences.PrefType.TypeString, "");
            XmlPreferences.theXmlPreferences.SetDefault("saveImageResolution", XmlPreferences.PrefType.TypeInt, "0");
            XmlPreferences.theXmlPreferences.SetDefault("suppressStartupWindows", XmlPreferences.PrefType.TypeBool, "false");
            XmlPreferences.theXmlPreferences.SetDefault("userModuleDescriptionFile", XmlPreferences.PrefType.TypeString, "");
            XmlPreferences.theXmlPreferences.SetDefault("executiveModuleDescriptionFile", XmlPreferences.PrefType.TypeString, "");
            XmlPreferences.theXmlPreferences.SetDefault("uiModuleDescriptionFile", XmlPreferences.PrefType.TypeString, "");
            XmlPreferences.theXmlPreferences.SetDefault("noWindowPlacement", XmlPreferences.PrefType.TypeBool, "false");
            XmlPreferences.theXmlPreferences.SetDefault("restrictionLevel", XmlPreferences.PrefType.TypeString, "");
            XmlPreferences.theXmlPreferences.SetDefault("noRWConfig", XmlPreferences.PrefType.TypeBool, "false");
            XmlPreferences.theXmlPreferences.SetDefault("noPanelEdit", XmlPreferences.PrefType.TypeBool, "false");
            XmlPreferences.theXmlPreferences.SetDefault("noInteractorEdits", XmlPreferences.PrefType.TypeBool, "false");
            XmlPreferences.theXmlPreferences.SetDefault("noInteractorAttributes", XmlPreferences.PrefType.TypeBool, "false");
            XmlPreferences.theXmlPreferences.SetDefault("noInteractorMovement", XmlPreferences.PrefType.TypeBool, "false");
            XmlPreferences.theXmlPreferences.SetDefault("noOpenAllPanels", XmlPreferences.PrefType.TypeBool, "false");
            XmlPreferences.theXmlPreferences.SetDefault("noPanelAccess", XmlPreferences.PrefType.TypeBool, "false");
            XmlPreferences.theXmlPreferences.SetDefault("noPanelOptions", XmlPreferences.PrefType.TypeBool, "false");
            XmlPreferences.theXmlPreferences.SetDefault("noMessageInfoOption", XmlPreferences.PrefType.TypeBool, "false");
            XmlPreferences.theXmlPreferences.SetDefault("noMessageWarningOption", XmlPreferences.PrefType.TypeBool, "false");
            XmlPreferences.theXmlPreferences.SetDefault("noEditorOnError", XmlPreferences.PrefType.TypeBool, "false");
            XmlPreferences.theXmlPreferences.SetDefault("noScriptCommands", XmlPreferences.PrefType.TypeBool, "false");
            XmlPreferences.theXmlPreferences.SetDefault("noPGroupAssignment", XmlPreferences.PrefType.TypeBool, "false");
            XmlPreferences.theXmlPreferences.SetDefault("noImageRWNetFile", XmlPreferences.PrefType.TypeBool, "false");
            XmlPreferences.theXmlPreferences.SetDefault("limitedNetFileSelection", XmlPreferences.PrefType.TypeBool, "false");
            XmlPreferences.theXmlPreferences.SetDefault("netPath", XmlPreferences.PrefType.TypeString, "");
            XmlPreferences.theXmlPreferences.SetDefault("noImageLoad", XmlPreferences.PrefType.TypeBool, "false");
            XmlPreferences.theXmlPreferences.SetDefault("noImageSaving", XmlPreferences.PrefType.TypeBool, "false");
            XmlPreferences.theXmlPreferences.SetDefault("noImagePrinting", XmlPreferences.PrefType.TypeBool, "false");
            XmlPreferences.theXmlPreferences.SetDefault("limitImageOptions", XmlPreferences.PrefType.TypeBool, "false");
            XmlPreferences.theXmlPreferences.SetDefault("notifySaveNet", XmlPreferences.PrefType.TypeBool, "false");
            XmlPreferences.theXmlPreferences.SetDefault("noNetworkExecute", XmlPreferences.PrefType.TypeBool, "false");
            XmlPreferences.theXmlPreferences.SetDefault("noEditorAccess", XmlPreferences.PrefType.TypeBool, "false");
            XmlPreferences.theXmlPreferences.SetDefault("noDXHelp", XmlPreferences.PrefType.TypeBool, "false");
            XmlPreferences.theXmlPreferences.SetDefault("noCMapSetNameOption", XmlPreferences.PrefType.TypeBool, "false");
            XmlPreferences.theXmlPreferences.SetDefault("noCMapOpenMap", XmlPreferences.PrefType.TypeBool, "false");
            XmlPreferences.theXmlPreferences.SetDefault("noCMapSaveMap", XmlPreferences.PrefType.TypeBool, "false");
            XmlPreferences.theXmlPreferences.SetDefault("applicationPort", XmlPreferences.PrefType.TypeInt, "0");
            XmlPreferences.theXmlPreferences.SetDefault("applicationHost", XmlPreferences.PrefType.TypeString, "");
            XmlPreferences.theXmlPreferences.SetDefault("infoEnabled", XmlPreferences.PrefType.TypeBool, "true");
            XmlPreferences.theXmlPreferences.SetDefault("warningEnabled", XmlPreferences.PrefType.TypeBool, "true");
            XmlPreferences.theXmlPreferences.SetDefault("errorEnabled", XmlPreferences.PrefType.TypeBool, "true");
            XmlPreferences.theXmlPreferences.SetDefault("moduleInfoOpensMessage", XmlPreferences.PrefType.TypeBool, "true");
            XmlPreferences.theXmlPreferences.SetDefault("infoOpenMessage", XmlPreferences.PrefType.TypeBool, "false");
            XmlPreferences.theXmlPreferences.SetDefault("warningOpenMessage", XmlPreferences.PrefType.TypeBool, "false");
            XmlPreferences.theXmlPreferences.SetDefault("errorOpenMessage", XmlPreferences.PrefType.TypeBool, "true");
            XmlPreferences.theXmlPreferences.SetDefault("useWindowSpecs", XmlPreferences.PrefType.TypeBool, "false");
            XmlPreferences.theXmlPreferences.SetDefault("forceNetFileEncryption", XmlPreferences.PrefType.TypeBool, "false");
            XmlPreferences.theXmlPreferences.SetDefault("cryptKey", XmlPreferences.PrefType.TypeString, "");
            XmlPreferences.theXmlPreferences.SetDefault("exitAfter", XmlPreferences.PrefType.TypeBool, "false");
            XmlPreferences.theXmlPreferences.SetDefault("forceLicense", XmlPreferences.PrefType.TypeString, "");
            XmlPreferences.theXmlPreferences.SetDefault("noExecuteMenus", XmlPreferences.PrefType.TypeBool, "false");
            XmlPreferences.theXmlPreferences.SetDefault("noConnectionMenus", XmlPreferences.PrefType.TypeBool, "false");
            XmlPreferences.theXmlPreferences.SetDefault("noWindowsMenus", XmlPreferences.PrefType.TypeBool, "false");
            XmlPreferences.theXmlPreferences.SetDefault("noExitOptions", XmlPreferences.PrefType.TypeBool, "false");
            XmlPreferences.theXmlPreferences.SetDefault("noImageMenus", XmlPreferences.PrefType.TypeBool, "false");
            XmlPreferences.theXmlPreferences.SetDefault("oemApplicationName", XmlPreferences.PrefType.TypeString, "");
            XmlPreferences.theXmlPreferences.SetDefault("oemApplicationNameCode", XmlPreferences.PrefType.TypeString, "");
            XmlPreferences.theXmlPreferences.SetDefault("oemLicenseCode", XmlPreferences.PrefType.TypeString, "");
            XmlPreferences.theXmlPreferences.SetDefault("viewDataFile", XmlPreferences.PrefType.TypeString, "");
            XmlPreferences.theXmlPreferences.SetDefault("autoScrollVPE", XmlPreferences.PrefType.TypeBool, "true");
            XmlPreferences.theXmlPreferences.SetDefault("autoLayoutHeight", XmlPreferences.PrefType.TypeInt, "90", true);
            XmlPreferences.theXmlPreferences.SetDefault("autoLayoutGroupSpacing", XmlPreferences.PrefType.TypeInt, "30", true);
            XmlPreferences.theXmlPreferences.SetDefault("autoLayoutNodeSpacing", XmlPreferences.PrefType.TypeInt, "15", true);
            XmlPreferences.theXmlPreferences.SetDefault("cosmoDir", XmlPreferences.PrefType.TypeString, "");
            XmlPreferences.theXmlPreferences.SetDefault("jdkDir", XmlPreferences.PrefType.TypeString, "");
            XmlPreferences.theXmlPreferences.SetDefault("htmlDir", XmlPreferences.PrefType.TypeString, "");
            XmlPreferences.theXmlPreferences.SetDefault("serverDir", XmlPreferences.PrefType.TypeString, "");
            XmlPreferences.theXmlPreferences.SetDefault("dxJarFile", XmlPreferences.PrefType.TypeString, "");
            XmlPreferences.theXmlPreferences.SetDefault("userHtmlDir", XmlPreferences.PrefType.TypeString, "");

            // The following is a little different. The default should actually be dxroot/samples/macros
            // Set it in DXApplication if null.
            XmlPreferences.theXmlPreferences.SetDefault("macros", XmlPreferences.PrefType.TypeString, "");

            if (newargv.Count > 0)
            {
                String[] retargs = new String[newargv.Count];
                for (int i = 0; i < newargv.Count; i++)
                {
                    retargs[i] = newargv[i];
                }
                return retargs;

            }
            else 
                return null;
        }

        #region Command Line Parsing Helpers
        /// <summary>
        /// Private functions for helping parse command line.
        /// </summary>
        /// <param name="arg"></param>
        /// <param name="cla"></param>
        /// <param name="pn"></param>
        /// <param name="val"></param>
        /// <returns></returns>
        private bool ARGStr(String arg, String cla, String pn, String val)
        {
            if (cla == arg)
            {
                XmlPreferences.theXmlPreferences.SetPref(
                    pn, XmlPreferences.PrefType.TypeString, val, false);
                arg = "";
                val = "";
                return true;
            }
            return false;
        }
        private bool NOARGtrue(String arg, String cla, String pn)
        {
            if (cla == arg)
            {
                XmlPreferences.theXmlPreferences.SetPref(
                    pn, XmlPreferences.PrefType.TypeBool, "true", false);
                arg = "";
                return true;
            }
            return false;
        }
        private bool NOARGfalse(String arg, String cla, String pn)
        {
            if (cla == arg)
            {
                XmlPreferences.theXmlPreferences.SetPref(
                    pn, XmlPreferences.PrefType.TypeBool, "false", false);
                arg = "";
                return true;
            }
            return false;
        }
        #endregion


        public virtual bool initialize(ref String[] argv)
        {
            name = argv[0];
            thisServer.notifyClients(MsgCreate);

            String[] argsn = new String[argv.Length - 1];
            for (int i = 1; i < argv.Length; i++)
                argsn[i - 1] = argv[i];
 
            argv = parseCommand(argsn);

            String pref;
            XmlPreferences.theXmlPreferences.GetPref("UIRoot", out pref);
            if (pref == null || pref.Length == 0)
            {
                String tmp = System.Environment.GetEnvironmentVariable("DXROOT");
                if (tmp != null)
                {
                    pref = tmp;
                }
                else
                {
                    pref = Application.StartupPath;
                }
            }

            XmlPreferences.theXmlPreferences.SetPref("UIRoot", pref, false);
            parseNoWizardNames();

            return true;
        }

        protected virtual void postCopyrightNotice()
        {
            String c = getCopyrightNotice();

            if (c != null)
            {
                TimedDialog copyright = new TimedDialog("copyrightMessage",
                    MainProgram.theApplication.getRootForm(), 
                    c, "Welcome", 5000);
            }
        }

        /// <summary>
        /// Notify all client windows to manage themselves
        /// </summary>
        public void manage()
        {
            thisServer.notifyClients(MsgManage);
        }

        /// <summary>
        /// Notify all client windows to unmanage themselves
        /// </summary>
        public void unmanage()
        {
            thisServer.notifyClients(MsgUnmanage);
        }

        /// <summary>
        /// Calls to this routine can be 'stacked' so that the first call
        /// sets the cursor and the last call resets the cursor
        /// </summary>
        /// <param name="setting"></param>
        public void setBusyCursor(bool setting)
        {
            if (setting)
                busyCursors++;
            else
                busyCursors--;

            switch (busyCursors)
            {
                case 0:
                    thisServer.notifyClients(MsgResetCursor);
                    break;
                case 1:
                    if (setting)
                        thisServer.notifyClients(MsgSetBusyCursor);
                    break;
            }
        }

        public abstract void shutdownApplication();

        public virtual String getFormalName()
        {
            return "'Your Application's Formal Name Here'";
        }

        public virtual String getInformalName()
        {
            return "'Your Application's Informal Name Here'";
        }

        public virtual String getCopyrightNotice()
        {
            return "'Your Application's Copyright Notice Here'";
        }

        public virtual void helpOn(String topic)
        {
            Console.WriteLine("Your Application specific help on {0} here", topic);
        }

        public virtual String getHelpDirFileName()
        {
            return "HelpDir";
        }

        public virtual String getHTMLDirFileName()
        {
            return "Help.idx";
        }

        /// <summary>
        /// Start a tutorial on behalf of the application.
        /// Return true if successful. Should be overridden.
        /// </summary>
        /// <returns></returns>
        public virtual bool startTutorial()
        {
            return false;
        }

        public virtual void abortApplication()
        {
            // Used to do the following:
            // raise signal SIGABRT
            // executes all functions registered with _atexit()
            // flushes all open output streams
            // closes all open files
            // removes all temporary files

            Environment.Exit(1);
        }

        /// <summary>
        /// The application prefs file lies in the users 
        /// local application data folder. Get it and make
        /// sure its writable.
        /// </summary>
        /// <param name="res_file"></param>
        /// <param name="create"></param>
        /// <returns></returns>
        public bool getApplicationDefaultsFileName(ref String res_file, bool create)
        {
            String class_name = applicationClass;
            String lad = Environment.GetFolderPath(Environment.SpecialFolder.LocalApplicationData);
            lad += "\\OpenDX";

            if (!Directory.Exists(lad))
            {
                try
                {
                    Directory.CreateDirectory(lad);
                }
                catch (Exception e)
                {
                    Console.WriteLine("Unable to create OpenDX Application Pref Directory");
                    return false;
                }
            }

            lad += "\\prefs.xml";
            res_file = lad;
            return isUsableDefaultsFile(res_file, create);
        }
        public bool getApplicationDefaultsFileName(ref String res_file)
        {
            return getApplicationDefaultsFileName(ref res_file, false);
        }

        /// <summary>
        /// Check to see if a file exists and is writable
        /// </summary>
        /// <param name="res_file"></param>
        /// <param name="create"></param>
        /// <returns></returns>
        public bool isUsableDefaultsFile(String res_file, bool create)
        {
            if (File.Exists(res_file))
            {
                FileAttributes fa = File.GetAttributes(res_file);

                if ((fa & FileAttributes.Normal) == FileAttributes.Normal)
                {
                    try
                    {
                        FileStream fs = File.OpenWrite(res_file);
                        fs.Close();
                    }
                    catch (Exception e)
                    {
                        return false;
                    }
                }
            }
            else
            {
                // Try and create the file since it doesn't exist if
                // create is true
                if (create)
                {
                    try
                    {
                        FileStream fs = File.Create(res_file);
                        fs.Close();
                    }
                    catch (Exception e)
                    {
                        return false;
                    }
                }
                else
                    return false;
            }

            return true;
        }

        public void handleEvents()
        {
            // Run Application 
            // Loop forever... 
            // handling events

            // Could be System.Windows.Forms.Application.Run(this.applicationContext);
            // Or perhaps drop this function and just put it in MainProgram.
        }

        /// <summary>
        /// Virtual methods that are called by ExecuteCommandCallback()
        /// before and after Command.execute()
        /// </summary>
        public virtual void startCommandInterfaceExecution()
        {
            thisServer.notifyClients(Command.MsgBeginExecuting);

        }

        public virtual void endCommandInterfaceExecution()
        {
            thisServer.notifyClients(Command.MsgEndExecuting);
        }
        #endregion

        #region IBMApplication

        public Form getRootForm()
        {
            return root;
        }

        public virtual void setRootForm(Form root)
        {
            this.root = root;
        }

        private String aboutAppString = null;
        protected String techSupportString = null;
        private List<String> noWizards = null;

        public String getUIRoot()
        {
            // Let's just get this by finding the location of the UI path.
            String uiroot = "";
            if(!XmlPreferences.theXmlPreferences.GetPref("UIRoot", out uiroot))
                uiroot = Application.StartupPath;
            return uiroot;
        }

        public String getAboutAppString()
        {
            if (aboutAppString == null)
            {
                aboutAppString = "Product : " + getFormalName() + "\n";
                aboutAppString += String.Format("Version : Version {0}.{1}.{2}\n",
                global::WinDX.UI.Resources.MAJOR_VERSION,
                global::WinDX.UI.Resources.MINOR_VERSION,
                global::WinDX.UI.Resources.MICRO_VERSION);
                DateTime __DATE__ = File.GetLastWriteTime(Application.ExecutablePath);
                aboutAppString += String.Format("Dated   : {0}", __DATE__);
            }
            return aboutAppString;
        }

        public String getTechSupportString()
        {
            if (techSupportString == null)
            {
                String dxroot = getUIRoot();
                String nosup = "No Technical Support Available";
                if (dxroot == null)
                    return nosup;

                String supfile = dxroot + "/ui/support.txt";
                try
                {
                    using (StreamReader sr = new StreamReader(supfile))
                    {
                        String line;
                        while ((line = sr.ReadLine()) != null)
                        {
                            techSupportString += line + "\n";
                        }
                    }
                }
                catch (Exception e)
                {
                    techSupportString = nosup;
                }
            }
            return techSupportString;
        }

        public String getHelpDirectory()
        {
            String helpDir = getUIRoot() + "/help";
            return helpDir;
        }

        public String getTmpDirectory()
        {
            String tmp = System.IO.Path.GetTempPath();
            if (tmp != null && tmp.Length > 0)
                return tmp;

            tmp = System.Environment.GetEnvironmentVariable("TMP");
            if (tmp != null && tmp.Length > 0)
                return tmp;

            tmp = System.Environment.GetEnvironmentVariable("TEMP");
            if (tmp != null && tmp.Length > 0)
                return tmp;

            throw new Exception("Cannot get Temporary Directory, please consult developers.");
            return null;
        }

        public String getHTMLDirectory()
        {
            String htmlDir = getUIRoot() + "/html";
            return htmlDir;
        }

        public void printResource(String resource, String value)
        {
            XmlPreferences.theXmlPreferences.SetPref(resource, value, true);
        }

        public void parseNoWizardNames()
        {
            String wizNames;
            XmlPreferences.theXmlPreferences.GetPref("noWizardNames", out wizNames);
            if (wizNames == null)
                return;

            if(noWizards == null)
                noWizards = new List<string>();

            String[] allWiz = wizNames.Split(':');
            foreach (String s in allWiz)
            {
                noWizards.Add(s);
            }
        }

        public void appendNoWizardName(String nowiz)
        {
            if (noWizards == null)
                noWizards = new List<string>();

            noWizards.Add(nowiz);
            printNoWizardNames();
        }

        public void printNoWizardNames()
        {
            String allWiz = "";
            for (int i = 0; i < noWizards.Count - 1; i++)
                allWiz += noWizards[i] + ":";
            allWiz += noWizards[noWizards.Count - 1];

            XmlPreferences.theXmlPreferences.SetPref("dismissedWizards", allWiz, true);
        }

        public bool inWizardMode()
        {
            bool wizmode;
            XmlPreferences.theXmlPreferences.GetPref("wizard", out wizmode);
            return wizmode;
        }

        public bool isWizardWindow(String name)
        {
            if (inWizardMode() == false) return false;
            if (noWizards == null) return true;

            if (noWizards.Contains(name))
                return false;

            return true;
        }

        #endregion
    }
}
