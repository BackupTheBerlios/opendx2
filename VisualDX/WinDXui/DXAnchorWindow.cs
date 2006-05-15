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
        protected ToolStripMenuItem openOption;
        protected ToolStripMenuItem loadMacroOption;
        protected ToolStripMenuItem loadMDFOption;
        protected ToolStripMenuItem saveOption;
        protected ToolStripMenuItem saveAsOption;
        protected ToolStripMenuItem closeOption;
        protected ToolStripMenuItem settingsOption;
        protected ToolStripMenuItem saveCfgOption;
        protected ToolStripMenuItem openCfgOption;
        protected Command closeCmd;

        // Window menu options
        protected ToolStripMenuItem openAllControlPanelsOption;
        protected ToolStripMenuItem openControlPanelByNameOption;
        protected ToolStripMenuItem openAllColormapEditorsOption;
        protected ToolStripMenuItem messageWindowOption;
        protected ToolStripMenuItem openVPEOption;
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
            base.createMenus(menu);
            throw new Exception("Not Yet Implemented");
        }
        protected virtual void createFileMenu(MenuStrip menubar)
        {
            throw new Exception("Not Yet Implemented");
        }
        protected virtual void createWindowsMenu(MenuStrip menubar)
        {
            throw new Exception("Not Yet Implemented");
        }
        protected override void createHelpMenu(MenuStrip menu)
        {
            base.createHelpMenu(menu);
            throw new Exception("Not Yet Implemented");
        }
        protected override void createFileHistoryMenu(ToolStripMenuItem menuItem)
        {
            base.createFileHistoryMenu(menuItem);
            throw new Exception("Not Yet Implemented");
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
            String file = DXApplication.theDXApplication.network.getFileName();
            String title = "";


            if (file != null && file.Length > 0)
            {
                title = vpe_name + " " + file;
            }
            else
                title = vpe_name;

            this.Text = title;
        }
    }
}
