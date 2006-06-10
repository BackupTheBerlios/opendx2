using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Diagnostics;
using System.Resources;

namespace WinDX.UI
{
    public abstract partial class MainWindow : Form, IClient
    {
        public Control CommandArea
        {
            get { return commandArea; }
        }
        public Control WorkArea
        {
            get { return workArea; }
        }
        public MenuStrip MenuBar
        {
            get { return menuBar; }
        }
        public bool IsInitialized
        {
            get { return isInitialized; }
        }

        private Control commandArea = null;
        private Control workArea = null;
        private MenuStrip menuBar = null;
        private WizardDialog wizardDialog = null;
        private bool hasMenuBar;
        private bool isInitialized = false;

        protected CommandScope commandScope;

        public Command helpOnWindowCmd = null;
        public Command helpAboutAppCmd = null;
        public Command helpTechSupportCmd = null;

        #region Help Menu Items
        protected ToolStripMenuItem helpToolStripMenuItem = null;
        private DXToolStripMenuItem onWindowOption = null;
        private DXToolStripMenuItem onManualOption = null;
        private DXToolStripMenuItem onHelpOption = null;
        private DXToolStripMenuItem aboutAppOption = null;
        private ToolStripSeparator sep1 = null;
        private DXToolStripMenuItem techSupportOption = null;

        #endregion

        /// <summary>
        /// Create the window-specific work area.
        /// </summary>
        /// <param name="parent"></param>
        /// <returns></returns>
        protected abstract Control createWorkArea(Form parent);

        /// <summary>
        /// Most derived classes will no want this. It provides a look like a
        /// dialog box. The purpose is to accomodate ControlPanels which need
        /// to alter their appearance in a major way without changing class
        /// hierarchy.
        /// </summary>
        /// <param name="parent"></param>
        /// <returns></returns>
        protected virtual Control createCommandArea(Form parent)
        {
            return null;
        }

        /// <summary>
        /// This routine is called by initialize() function to create
        /// the menus for the menubar in the window.
        /// This function is defined here for windows that do not have
        /// menu bars (i.e. hasMenuBar == FALSE), so should never be called.
        /// </summary>
        /// <param name="parent"></param>
        protected virtual void createMenus(MenuStrip menu)
        {
            Debug.Assert(!hasMenuBar);
        }

        // Overridden by DXWindow
        protected virtual void createMenuBar(Form parent)
        {

            menuBar = new MenuStrip();
            parent.SuspendLayout();

            parent.Controls.Add(menuBar);
            parent.MainMenuStrip = menuBar;
            parent.ResumeLayout(false);
            parent.PerformLayout();
        }

        /// <summary>
        /// Provides context help.
        /// </summary>
        /// <param name="parent"></param>
        protected virtual void provideContextHelp(Form parent)
        {
            // No implementation at this level
        }

        /// <summary>
        /// Window close callback.
        /// </summary>
        public virtual void closeCallback(Object sender, CancelEventArgs e)
        {
            closeWindow();
        }

        protected override void OnClosing(CancelEventArgs e)
        {
            e.Cancel = true;
            base.OnClosing(e);
            closeWindow();
        }

        private void CommonConstructor()
        {
            InitializeComponent();

            workArea = null;
            commandArea = null;
            Text = "";

            Visible = false;
            if (hasMenuBar)
            {
                commandScope = new CommandScope();
                helpOnWindowCmd = new UIComponentHelpCommand("helpOnWindow", null,
                    true, this);
            }
            else
                commandScope = null;

            Debug.Assert(MainProgram.theApplication != null);
            MainProgram.theApplication.thisServer.registerClient(this);

            Load += new EventHandler(MainWindow_Load);
        }

        private void MainWindow_Load(object sender, EventArgs e)
        {
            if (!isInitialized)
                initialize();

            if (DXApplication.theDXApplication.inWizardMode())
                postWizard();
        }

        public MainWindow(String name)
        {
            hasMenuBar = true;

            CommonConstructor();


        }
        public MainWindow(String name, bool usesMenuBar)
        {
            hasMenuBar = usesMenuBar;

            CommonConstructor();
        }

        ~MainWindow()
        {
            MainProgram.theApplication.thisServer.unregisterClient(this);
        }

        /// <summary>
        /// Creates and intializes the window.
        /// </summary>
        public virtual void initialize()
        {
            //FormClosing += new FormClosingEventHandler(closeCallback);
            this.HelpRequested += new System.Windows.Forms.HelpEventHandler(Help.helpOn);


            workArea = createWorkArea(this);
            Debug.Assert(workArea != null);

            commandArea = createCommandArea(this);

            this.Controls.Add(commandArea);

            if (hasMenuBar)
            {
                createMenuBar(this);
                createMenus(menuBar);
            }

            Size = new Size(1000, 800);

            MainProgram.theApplication.setRootForm(this);

            if (global::WinDX.UI.Resources.startup != null)
                Icon = global::WinDX.UI.Resources.startup;
        }

        public virtual void notify(Symbol message)
        {
            notify(message, null, null);
        }
        public virtual void notify(Symbol message, String data)
        {
            notify(message, data, null);
        }
        public virtual void notify(Symbol message, String data, String msg)
        {
            if (message == BaseApplication.MsgManage)
            {
                Debug.Assert(IsInitialized);
                this.Show();
            }
            else if (message == BaseApplication.MsgUnmanage)
            {
                this.Hide();
            }
            else if (message == BaseApplication.MsgSetBusyCursor)
            {
                Cursor = Cursors.WaitCursor;
            }
            else if (message == BaseApplication.MsgResetCursor)
            {
                Cursor = Cursors.Default;
            }
            else if (message == BaseApplication.MsgManageByLeafClassName)
            {
                if (data == null || data == GetType().ToString())
                    this.Show();
            }
            else if (message == BaseApplication.MsgUnmanageByLeafClassName)
            {
                if (data == null || data == GetType().ToString())
                    this.Hide();
            }
            else if (message == BaseApplication.MsgCreate)
            {
                if (!Visible)
                {
                    if (IsInitialized)
                        initialize();
                    this.Show();
                }
            }
        }

        protected virtual void createBaseHelpMenu(MenuStrip menu)
        {
            createBaseHelpMenu(menu, true, false);
        }
        protected virtual void createBaseHelpMenu(MenuStrip menu,
            bool add_standard_options)
        {
            createBaseHelpMenu(menu, add_standard_options, false);
        }
        protected virtual void createBaseHelpMenu(MenuStrip menu,
            bool add_standard_options, bool addAboutApp)
        {
            Debug.Assert(menu != null);

            Debug.Assert(menuBar != null);

            ComponentResourceManager resources = new ComponentResourceManager(typeof(MainWindow));

            this.helpAboutAppCmd = new HelpMenuCommand("helpAboutApp", null, true, HelpMenuCommand.HelpType.AboutApp);
            this.helpTechSupportCmd = new HelpMenuCommand("helpTechSupport", null, true,
                HelpMenuCommand.HelpType.TechSupport);

            helpToolStripMenuItem = new ToolStripMenuItem();
            onWindowOption = new DXToolStripMenuItem("onWindowOption", this.helpOnWindowCmd);
            onManualOption = new DXToolStripMenuItem("onManualOption", DXApplication.theDXApplication.genericHelpCmd);
            onHelpOption = new DXToolStripMenuItem("onHelpOption", DXApplication.theDXApplication.genericHelpCmd);
            aboutAppOption = new DXToolStripMenuItem("aboutAppOption", this.helpAboutAppCmd);
            sep1 = new ToolStripSeparator();
            techSupportOption = new DXToolStripMenuItem("techSupportOption", this.helpTechSupportCmd);

            menuBar.SuspendLayout();
            SuspendLayout();
            menuBar.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            helpToolStripMenuItem});

            helpToolStripMenuItem.DropDownItems.AddRange(new ToolStripItem[] {
            onWindowOption,
            onManualOption,
            onHelpOption });

            helpToolStripMenuItem.Name = "helpToolStripMenuItem";
            resources.ApplyResources(this.helpToolStripMenuItem, "helpToolStripMenuItem");

            // 
            // onWindowOption
            // 
            onWindowOption.Name = "onWindowOption";
            //onWindowOption.Click += new EventHandler(Help.helpOn);
            resources.ApplyResources(this.onWindowOption, "onWindowOption");

            // 
            // onManualOption
            // 
            onManualOption.Name = "onManualOption";
            //onManualOption.Click += new EventHandler(Help.helpOn);
            resources.ApplyResources(this.onManualOption, "onManualOption");

            // 
            // onHelpOption
            // 
            onHelpOption.Name = "onHelpOption";
            //onHelpOption.Click += new EventHandler(Help.helpOn);
            resources.ApplyResources(this.onHelpOption, "onHelpOption");

            if (addAboutApp)
            {
                helpToolStripMenuItem.DropDownItems.AddRange(new ToolStripItem[] {
                    sep1, aboutAppOption, techSupportOption });
                // 
                // sep1
                // 
                sep1.Name = "sep1";
                // 
                // aboutAppOption
                // 
                aboutAppOption.Name = "aboutAppOption";
                //aboutAppOption.Click += new EventHandler(Help.helpOn);
                resources.ApplyResources(this.aboutAppOption, "aboutAppOption");

                // 
                // techSupportOption
                // 
                techSupportOption.Name = "techSupportOption";
                //techSupportOption.Click += new EventHandler(Help.helpOn);
                resources.ApplyResources(this.techSupportOption, "techSupportOption");

            }
            menuBar.ResumeLayout();
            menuBar.PerformLayout();
            ResumeLayout();
            PerformLayout();
        }

        protected virtual void postWizard()
        {
            if (!DXApplication.theDXApplication.inWizardMode())
                return;
            if (wizardDialog != null && wizardDialog.Visible) 
                return;
            if (DXApplication.theDXApplication.isWizardWindow(base.Name))
            {
                if (wizardDialog == null)
                    wizardDialog = new WizardDialog(this);
                if (wizardDialog.getText() != null && wizardDialog.getText().Length > 0)
                    wizardDialog.Show();
            }
        }

        private void helpNeeded(object sender, HelpEventArgs hlpevent)
        {

        }

        public virtual void closeWindow()
        {
            this.Close();
        }
    }
}