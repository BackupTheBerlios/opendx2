using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;
using System.Diagnostics;
using System.ComponentModel;

namespace WinDX.UI
{
    public class DXAnchorWindow : DXWindow
    {
        private static bool ClassInitialized = false;
        private TableLayoutPanel form;
        private Label label;
        private Label logoMessage;
        private Button logoButton;

        protected ToolStripMenuItem fileMenu;
        protected ToolStripMenuItem windowsMenu;

        // File menu options
        protected DXToolStripMenuItem openOption;
        protected CascadeAutoToolStripMenuItem recentOption;
        protected DXToolStripMenuItem loadMacroOption;
        protected DXToolStripMenuItem loadMDFOption;
        protected DXToolStripMenuItem saveOption;
        protected DXToolStripMenuItem saveAsOption;
        protected DXToolStripMenuItem closeOption;
        protected ToolStripMenuItem settingsOption;
        protected DXToolStripMenuItem saveCfgOption;
        protected DXToolStripMenuItem openCfgOption;
        protected Command closeCmd;

        // Window menu options
        protected DXToolStripMenuItem openAllControlPanelsOption;
        protected CascadeAutoToolStripMenuItem openControlPanelByNameOption;
        protected DXToolStripMenuItem openAllColormapEditorsOption;
        protected DXToolStripMenuItem messageWindowOption;
        protected DXToolStripMenuItem openVPEOption;
        Command openVPECmd;

        // Help menu options
        protected ToolStripMenuItem onVisualProgramOption;

        private void CommonConstructor()
        {
            closeCmd = new CloseWindowCommand("close", this.commandScope, true, this);
            if (DXApplication.theDXApplication.appAllowsEditorAccess())
            {
                openVPECmd = new NoUndoAnchorCommand("openVPE",
                    commandScope, true, this, NoUndoAnchorCommand.AnchorCommandType.OpenVPE);
            }
            else
                openVPECmd = null;

            if (!ClassInitialized)
            {
                Debug.Assert(MainProgram.theApplication != null);
                ClassInitialized = true;
            }
        }

        public DXAnchorWindow(String name, bool isAnchor)
            :
            base(name, isAnchor, true)
        {
            CommonConstructor();
        }
        public DXAnchorWindow(String name, bool isAnchor, bool usesMenuBar)
            :
            base(name, isAnchor, usesMenuBar)
        {
            CommonConstructor();
        }

        protected override Control createWorkArea(Form parent)
        {
            ComponentResourceManager resources = new ComponentResourceManager(typeof(DXAnchorWindow));

            form = new TableLayoutPanel();
            label = new Label();
            form.SuspendLayout();
            form.Name = "form";
            resources.ApplyResources(this.form, "form");

            form.Controls.Add(label);
            label.Name = "label";
            label.Text = "Delete me";
            resources.ApplyResources(label, "label");

            form.ResumeLayout();
            form.PerformLayout();

            resetWindowTitle();

            return form;
        }

        protected override void createMenus(MenuStrip menu)
        {
            createFileMenu(menu);
            createExecuteMenu(menu);
            createWindowsMenu(menu);
            createConnectionMenu(menu);
            createHelpMenu(menu);
        }
        protected virtual void createFileMenu(MenuStrip menubar)
        {
            ComponentResourceManager resources = new ComponentResourceManager(typeof(DXWindow));

            bool needSep = false;
            SuspendLayout();
            menubar.SuspendLayout();

            fileMenu = new ToolStripMenuItem();
            menubar.Items.Add(fileMenu);

            if (DXApplication.theDXApplication.appAllowsImageRWNetFile())
            {
                openOption = new DXToolStripMenuItem("fileOpenOption", DXApplication.theDXApplication.openFileCmd);
                recentOption = new CascadeAutoToolStripMenuItem(fileMenu);
                createFileHistoryMenu(ref recentOption, ref fileMenu);

                Network net = DXApplication.theDXApplication.network;
                saveOption = new DXToolStripMenuItem("fileSaveOption", net.getSaveCommand());
                saveAsOption = new DXToolStripMenuItem("fileSaveAsOption", net.getSaveAsCommand());
                fileMenu.DropDownItems.AddRange(new ToolStripItem[] {
                    openOption,
                    recentOption,
                    saveOption,
                    saveAsOption});
                fileMenu.Name = "fileMenu";
                saveOption.Name = "saveOption";
                saveAsOption.Name = "saveAsOption";

                resources.ApplyResources(fileMenu, "fileMenu");
                resources.ApplyResources(openOption, "openOption");
                resources.ApplyResources(recentOption, "recentOption");
                resources.ApplyResources(saveOption, "saveOption");
                resources.ApplyResources(saveAsOption, "saveAsOption");
                needSep = true;
            }
            if (DXApplication.theDXApplication.appAllowsRWConfig())
            {
                Command openCfgCmd = DXApplication.theDXApplication.network.getOpenCfgCommand();
                Command saveCfgCmd = DXApplication.theDXApplication.network.getSaveCfgCommand();
                if (openCfgCmd != null || saveCfgCmd != null)
                {
                    settingsOption = new ToolStripMenuItem();
                    settingsOption.Name = "settingsOption";
                    fileMenu.DropDownItems.Add(settingsOption);
                    resources.ApplyResources(settingsOption, "settingsOption");
                    needSep = true;
                }
                if (saveCfgCmd != null)
                {
                    saveCfgOption = new DXToolStripMenuItem("saveCfgOption", saveCfgCmd);
                    settingsOption.DropDownItems.Add(saveCfgOption);
                    saveCfgOption.Name = "saveCfgOption";
                    resources.ApplyResources(saveCfgOption, "saveCfgOption");
                }
                if (openCfgCmd != null)
                {
                    openCfgOption = new DXToolStripMenuItem("saveCfgOption", openCfgCmd);
                    settingsOption.DropDownItems.Add(openCfgOption);
                    openCfgOption.Name = "openCfgOption";
                    resources.ApplyResources(openCfgOption, "openCfgOption");
                }

            }
            if (DXApplication.theDXApplication.appAllowsImageLoad())
            {
                if (needSep)
                {
                    ToolStripSeparator sep1 = new ToolStripSeparator();
                    fileMenu.DropDownItems.Add(sep1);
                }
                loadMacroOption = new DXToolStripMenuItem("fileLoadMacroOption", 
                    DXApplication.theDXApplication.loadMacroCmd);
                loadMDFOption = new DXToolStripMenuItem("fileLoadMDFOption",
                    DXApplication.theDXApplication.loadMDFCmd);
                fileMenu.DropDownItems.AddRange(new ToolStripItem[] {
                    loadMacroOption,
                    loadMDFOption });
                needSep = true;
                loadMacroOption.Name = "loadMacroOption";
                resources.ApplyResources(loadMacroOption, "loadMacroOption");
                loadMDFOption.Name = "loadMDFOption";
                resources.ApplyResources(loadMDFOption, "loadMDFOption");
                
            }
            if (needSep)
            {
                ToolStripSeparator sep2 = new ToolStripSeparator();
                fileMenu.DropDownItems.Add(sep2);
            }
            closeOption = new DXToolStripMenuItem("fileCloseOption", closeCmd);
            fileMenu.DropDownItems.Add(closeOption);
            closeOption.Name = "closeOption";

            resources.ApplyResources(closeOption, "closeOption");

            menubar.ResumeLayout();
            menubar.PerformLayout();

            ResumeLayout();
            PerformLayout();
        }
        protected virtual void createWindowsMenu(MenuStrip menubar)
        {
            ComponentResourceManager resources = new ComponentResourceManager(typeof(DXWindow));

            ToolStripSeparator sep1 = new ToolStripSeparator();

            windowsMenu = new ToolStripMenuItem();
            openVPEOption = new DXToolStripMenuItem("openVPEOption", openVPECmd);
            openAllControlPanelsOption = new DXToolStripMenuItem("openAllControlPanelsOption",
                DXApplication.theDXApplication.network.getOpenAllPanelsCommand());
            openControlPanelByNameOption = new CascadeAutoToolStripMenuItem(windowsMenu);
            openAllColormapEditorsOption = new DXToolStripMenuItem("openAllColormapEditorsOptions",
                DXApplication.theDXApplication.openAllColormapCmd);
            messageWindowOption = new DXToolStripMenuItem("messageWindowOption",
                DXApplication.theDXApplication.messageWindowCmd);

            SuspendLayout();
            menubar.SuspendLayout();
            menubar.Items.Add(windowsMenu);
            windowsMenu.DropDownItems.AddRange(new ToolStripItem[] {
                openVPEOption,
                openAllControlPanelsOption,
                openControlPanelByNameOption,
                openAllColormapEditorsOption,
                messageWindowOption
                 });

            windowsMenu.Name = "windowsMenu";
            resources.ApplyResources(this.windowsMenu, "windowsMenu");

            openVPEOption.Name = "openVPEOption";
            resources.ApplyResources(this.openVPEOption, "openVPEOption");

            openAllControlPanelsOption.Name = "openAllControlPanelsOption";
            resources.ApplyResources(this.openAllControlPanelsOption, "openAllControlPanelsOption");

            openControlPanelByNameOption.Name = "openControlPanelByNameOption";
            resources.ApplyResources(this.openControlPanelByNameOption, "openControlPanelByNameOption");

            openAllColormapEditorsOption.Name = "openAllColormapEditorsOption";
            resources.ApplyResources(this.openAllColormapEditorsOption, "openAllColormapEditorsOption");

            messageWindowOption.Name = "messageWindowOption";
            resources.ApplyResources(this.messageWindowOption, "messageWindowOption");

            menubar.ResumeLayout();
            menubar.PerformLayout();

            ResumeLayout();
            PerformLayout();
        }
        protected override void createHelpMenu(MenuStrip menu)
        {
            ComponentResourceManager resources = new ComponentResourceManager(typeof(DXWindow));

            base.createHelpMenu(menu);
       
            ToolStripSeparator sep1 = new ToolStripSeparator();
            onVisualProgramOption = new ToolStripMenuItem();

            helpToolStripMenuItem.DropDownItems.AddRange(new ToolStripItem[] {
                sep1, onVisualProgramOption});

            onVisualProgramOption.Name = "onVisualProgramOption";
            resources.ApplyResources(this.onVisualProgramOption, "onVisualProgramOption");

        }
        protected override void createFileHistoryMenu(ref CascadeAutoToolStripMenuItem menuItem,
            ref ToolStripMenuItem parentMenuItem)
        {
            if(DXApplication.theDXApplication.appAllowsImageRWNetFile())
                base.createFileHistoryMenu(ref menuItem, ref parentMenuItem);
        }

        public bool postVPE()
        {
            throw new Exception("Not Yet Implemented");
        }

        /// <summary>
        /// This window will post a copyright notice inside itself as a substitute
        /// for the one supplied by {IBM}Application.
        /// </summary>
        public void postCopyrightNotice()
        {
            throw new Exception("Not Yet Implemented");
        }
        public void setKioskMessage(String msg)
        {
            throw new Exception("Not Yet Implemented");
        }

        /// <summary>
        /// Adjust the name of the editor window based on the current network name.
        /// </summary>
        public void resetWindowTitle()
        {
            String vpe_name = DXApplication.theDXApplication.getInformalName();
            String file = DXApplication.theDXApplication.network.FileName;
            String title = "";


            if (file != null && file.Length > 0)
            {
                title = vpe_name + " " + file;
            }
            else
                title = vpe_name;

            this.Text = title;
        }

        protected override void OnClosing(CancelEventArgs e)
        {
            throw new Exception("Not Yet Implemented");
            base.OnClosing(e);
        }
    }
}
