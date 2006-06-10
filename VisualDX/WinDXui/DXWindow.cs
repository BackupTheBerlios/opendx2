using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;
using System.IO;
using System.Resources;
using System.ComponentModel;
using System.Diagnostics;

namespace WinDX.UI
{
    public abstract class DXWindow : MainWindow
    {
        protected bool startup;  // Is this supposed to be opened at startup.
        protected bool anchor;   // Is this an anchor window?


        // Execute option pulldown support
        protected ToolStripMenuItem executeMenu;
        protected DXToolStripMenuItem executeOnceOption;
        protected DXToolStripMenuItem executeOnChangeOption;
        protected DXToolStripMenuItem endExecutionOption;
        protected DXToolStripMenuItem sequencerOption;

        // Connect option pulldown support
        protected ToolStripMenuItem connectionMenu;
        protected DXToolStripMenuItem startServerOption;
        protected DXToolStripMenuItem disconnectFromServerOption;
        protected DXToolStripMenuItem resetServerOption;
        protected DXToolStripMenuItem processGroupAssignmentOption;

        // Options menu
        protected Command toggleWindowStartupCmd;
        protected DXToolStripMenuItem toggleWindowStartupOption;

        // Adds help option pulldown support
        protected ToolStripMenuItem helpTutorialOption;

        // File history menus
        protected ToolStripMenuItem fileHistoryOption;
        protected CascadeAutoToolStripMenuItem recentMenu;
        List<ToolStripMenuItem> file_history_buttons;
        List<Command> file_history_commands;

        /// <summary>
        /// These routines provide the basic methods to build the execute
        /// and help menus, but can be overridden by the derived classes.
        /// </summary>
        /// <param name="menu"></param>
        protected virtual void createHelpMenu(MenuStrip menu)
        {
            bool addHelp = DXApplication.theDXApplication.appAllowsDXHelp();
            createBaseHelpMenu(menu);
            if (addHelp)
            {
                ComponentResourceManager resources = new ComponentResourceManager(typeof(DXWindow));

                ToolStripSeparator sep1 = new ToolStripSeparator();
                helpTutorialOption = new DXToolStripMenuItem("helpTutorialOption",
                    DXApplication.theDXApplication.helpTutorialCmd);

                helpToolStripMenuItem.DropDownItems.AddRange(new ToolStripItem[] {
                    sep1,
                    helpTutorialOption});
                helpTutorialOption.Name = "helpTutorialOption";
                resources.ApplyResources(this.helpTutorialOption, "helpTutorialOption");

            }
        }
        protected virtual void createExecuteMenu(MenuStrip menubar)
        {
            ComponentResourceManager resources = new ComponentResourceManager(typeof(DXWindow));

            ToolStripSeparator sep1 = new ToolStripSeparator();
            executeMenu = new ToolStripMenuItem();
            executeOnceOption = new DXToolStripMenuItem("executeOnceOption",
                DXApplication.theDXApplication.executeOnceCmd);
            executeOnChangeOption = new DXToolStripMenuItem("executeOnChangeOption",
                DXApplication.theDXApplication.executeOnChangeCmd);
            endExecutionOption = new DXToolStripMenuItem("endExecutionOption",
                DXApplication.theDXApplication.endExecutionCmd);
            sequencerOption = new DXToolStripMenuItem("sequencerOption",
                DXApplication.theDXApplication.openSequencerCmd);

            SuspendLayout();
            menubar.SuspendLayout();
            menubar.Items.Add(executeMenu);
            executeMenu.DropDownItems.AddRange(new ToolStripItem[] {
                executeOnceOption,
                executeOnChangeOption,
                endExecutionOption,
                sep1,
                sequencerOption });

            executeMenu.Name = "executeMenu";
            resources.ApplyResources(this.executeMenu, "executeMenu");
            

            //executeOnceOption
            executeOnceOption.Name = "executeOnceOption";
            resources.ApplyResources(this.executeOnceOption, "executeOnceOption");

            //executeOnChangeOption
            executeOnChangeOption.Name = "executeOnChangeOption";
            resources.ApplyResources(this.executeOnChangeOption, "executeOnChangeOption");

            // endExecutionOption
            endExecutionOption.Name = "endExecutionOption";
            resources.ApplyResources(this.endExecutionOption, "endExecutionOption");

            // sequencerOption
            sequencerOption.Name = "sequencerOption";
            resources.ApplyResources(this.sequencerOption, "sequencerOption");

            menubar.ResumeLayout();
            menubar.PerformLayout();

            ResumeLayout();
            PerformLayout();
        }
        protected virtual void createConnectionMenu(MenuStrip menubar)
        {
            if (!DXApplication.theDXApplication.appAllowsConnectionMenus())
                return;

            ComponentResourceManager resources = new ComponentResourceManager(typeof(DXWindow));

            ToolStripSeparator sep1 = new ToolStripSeparator();
            connectionMenu = new ToolStripMenuItem();
            startServerOption = new DXToolStripMenuItem("startServerOption",
                DXApplication.theDXApplication.connectedToServerCmd);
            disconnectFromServerOption = new DXToolStripMenuItem("disconnectFromServerOption",
                DXApplication.theDXApplication.disconnectedFromServerCmd);
            resetServerOption = new DXToolStripMenuItem("resetServerOption",
                DXApplication.theDXApplication.resetServerCmd);
            processGroupAssignmentOption = new DXToolStripMenuItem("processGroupAssignmentOption",
                DXApplication.theDXApplication.assignProcessGroupCmd);

            SuspendLayout();
            menubar.SuspendLayout();
            menubar.Items.Add(connectionMenu);
            connectionMenu.DropDownItems.AddRange(new ToolStripItem[] {
                startServerOption,
                disconnectFromServerOption,
                resetServerOption,
                sep1,
                processGroupAssignmentOption
                 });

            connectionMenu.Name = "connectionMenu";
            resources.ApplyResources(this.connectionMenu, "connectionMenu");

            startServerOption.Name = "startServerOption";
            resources.ApplyResources(this.startServerOption, "startServerOption");

            disconnectFromServerOption.Name = "disconnectFromServerOption";
            resources.ApplyResources(this.disconnectFromServerOption, "disconnectFromServerOption");

            resetServerOption.Name = "resetServerOption";
            resources.ApplyResources(this.resetServerOption, "resetServerOption");

            processGroupAssignmentOption.Name = "processGroupAssignmentOption";
            resources.ApplyResources(this.processGroupAssignmentOption, "processGroupAssignmentOption");

            menubar.ResumeLayout();
            menubar.PerformLayout();

            ResumeLayout();
            PerformLayout();
        }

        protected virtual void createFileHistoryMenu(ref CascadeAutoToolStripMenuItem menuItem, 
            ref ToolStripMenuItem parentMenuItem)
        {
            if (!IsAnchor)
                return;

            //List<String> recent_nets;
            //DXApplication.theDXApplication.getRecentNets(out recent_nets);
            recentMenu = menuItem;
            parentMenuItem.DropDownOpening += new EventHandler(buildFileHistoryMenu);
        }

        protected virtual void buildFileHistoryMenu(object sender, EventArgs e)
        {
            ToolStripMenuItem recentOptions = (ToolStripMenuItem) sender;
            List<String> recent_nets;
            DXApplication.theDXApplication.getRecentNets(out recent_nets);

            if (recentMenu == null)
                return;

            if (recent_nets == null || recent_nets.Count == 0)
            {
                recentMenu.DropDownItems.Clear();
                return;
            }
            else
            {

                ToolStripMenuItem[] files = new ToolStripMenuItem[recent_nets.Count];
                for (int i = 0; i < recent_nets.Count; i++)
                {
                    files[i] = new ToolStripMenuItem();
                    files[i].Name = String.Format("File_{0}", i);
                    files[i].Text = recent_nets[i];
                    // Need to add command to open here.
                }
                recentMenu.DropDownItems.Clear();
                recentMenu.DropDownItems.AddRange(files);
                recentMenu.Enabled = true;
            }
        }


        /// <summary>
        /// Children should implement these virtual functions to highlight their
        /// Execute menu pull down if they have one.
        /// </summary>
        protected virtual void beginExecution()
        {
            throw new Exception("Not Yet Implemented");
        }
        protected virtual void standBy()
        {
            throw new Exception("Not Yet Implemented");
        }
        protected virtual void endExecution()
        {
            throw new Exception("Not Yet Implemented");
        }
        protected virtual void serverDisconnect()
        {
            throw new Exception("Not Yet Implemented");
        }

        /// <summary>
        /// Virtual function called at the beggining/end of Command::execute
        /// </summary>
        protected virtual void beginCommandExecuting()
        {
            throw new Exception("Not Yet Implemented");
        }
        protected virtual void endCommandExecuting()
        {
            throw new Exception("Not Yet Implemented");
        }

        /// <summary>
        /// Remember the last message notified so that a new window can get
        /// notified at the creation time.
        /// </summary>
        protected Symbol lastMsg;
        protected static String lastMsgData;

        /// <summary>
        /// Not every window uses this, but enough do that we link it here.
        /// </summary>
        protected ControlPanelAccessDialog panelAccessDialog;

        protected ToolStripMenuItem addStartupToggleOption(ToolStripMenuItem menuItem)
        {
            throw new Exception("Not Yet Implemented");
        }

        /// <summary>
        ///Change whether or not this window is an anchor window.
        /// Update any visual state or anything else that is required. 
        /// </summary>
        /// <param name="isAnchor"></param>
        protected virtual void setAnchor(bool isAnchor)
        {
            throw new Exception("Not Yet Implemented");
        }

        protected virtual void buildFileHistoryMenu()
        {
            throw new Exception("Not Yet Implemented");
        }

        public DXWindow(String name, bool isAnchor, bool usesMenuBar)
            : base(name, usesMenuBar)
        {
            this.Load += new EventHandler(DXWindow_Load);
            anchor = isAnchor;
            startup = false;
            Debug.Assert(!usesMenuBar || commandScope != null);
        }

        private void DXWindow_Load(object sender, EventArgs e)
        {
            notify(lastMsg, lastMsgData);
        }

        public override void notify(Symbol message)
        {
            notify(message, null, null);
        }
        public override void notify(Symbol message, string data)
        {
            notify(message, data, null);
        }
        public override void notify(Symbol message, string data, string msg)
        {
            base.notify(message, data, msg);
        }

        public virtual bool IsAnchor
        {
            get { return anchor; }
        }

        /// <summary>
        /// Post the panel access dialog with this window PanelAccessManager info.
        /// If pam is not NULL, use it when creating the dialog otherwise use
        /// this->panelAccessManager.
        /// </summary>
        /// <param name="pam"></param>
        public void postPanelAccessDialog(PanelAccessManager pam)
        {
            throw new Exception("Not Yet Implemented");
        }

        public virtual bool printComment(Stream s)
        {
            throw new Exception("Not Yet Implemented");
        }

        public virtual bool parseComment(String line, String file, int lineno)
        {
            throw new Exception("Not Yet Implemented");
        }

        /// <summary>
        /// Reset the window to use the default settings for the state that is
        /// printed by the printComment() method.
        /// </summary>
        public virtual void useDefaultCommentState()
        {
            throw new Exception("Not Yet Implemented");
        }

        /// <summary>
        /// Determine if this window is a startup window.
        /// </summary>
        public bool IsStartup
        {
            get { return startup; }
        }

        /// <summary>
        /// Virtual because SequencerWindow must set a startup flag in his node
        /// at the same time.
        /// </summary>
        public virtual void setStartup()
        {
            setStartup(true);
        }
        public virtual void setStartup(bool set)
        {
            throw new Exception("Not Yet Implemented");
        }

        /// <summary>
        /// Called by the MainWindow CloseCallback
        /// </summary>
        public override void closeWindow()
        {
            if (DXApplication.theDXApplication.appAllowsExitOptions())
            {
                if (anchor)
                    DXApplication.theDXApplication.exitCmd.execute();
                else
                    Close();
            }
            else
            {
                WindowState = FormWindowState.Minimized;
            }
        }

        /// <summary>
        /// Changes whether or not this window is supposed to open up automatically 
        /// on startup.
        /// </summary>
        public virtual void toggleWindowStartup()
        {
            throw new Exception("Not Yet Implemented");
        }
    }
}
