using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.IO;
using System.Text.RegularExpressions;

namespace WinDX.UI
{
    public partial class MsgWin : DXWindow
    {
        private class MsgWinListItem
        {
            public String _text;
            public Font _font;
            public Color _backColor;
            public Color _foreColor;

            public MsgWinListItem(String text, Color forecolor, Color backcolor, Font font)
            {
                _text = text;
                _font = font;
                _backColor = backcolor;
                _foreColor = forecolor;
            }
            public override string ToString()
            {
                return _text;
            }
        }
        private class MsgWinListItems
        {
            public MsgWinListItem[] items;
            public MsgWinListItems(MsgWinListItem[] items) { this.items = items; }
        }

        private TableLayoutPanel workArea;
        private ListBox errorBox;

        private bool firstMsg = true;
        private bool beenBeeped = false;
        private StreamWriter logFile = null;
        private bool executing = false;

        private Command nextErrorCmd;
        private Command prevErrorCmd;

        private Command clearCmd;
        private Command logCmd;
        private Command saveCmd;
        private Command closeCmd;

        private ToolStripMenuItem fileMenu;
        private DXToolStripMenuItem logOption;
        private DXToolStripMenuItem saveOption;
        private DXToolStripMenuItem closeOption;

        private String logFileName;
        

        public MsgWin()
            : base("messageWindow", false, true)
        {
            //InitializeComponent();

            clearCmd = new MWClearCmd("clear", commandScope, false, this);
            logCmd = new NoUndoMWCmd("log", commandScope, true, this, NoUndoMWCmd.CmdType.Log);
            saveCmd = new NoUndoMWCmd("save", commandScope, true, this, NoUndoMWCmd.CmdType.Save);
            closeCmd = new NoUndoMWCmd("close", commandScope, true, this, NoUndoMWCmd.CmdType.Close);

            initialize();
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.Sizable;
            //this.SizeGripStyle = System.Windows.Forms.SizeGripStyle.Show;
            this.ResumeLayout(false);
            this.PerformLayout();
        }
        protected override Control createWorkArea(Form parent)
        {
            this.workArea = new TableLayoutPanel();
            this.errorBox = new ListBox();
            this.workArea.SuspendLayout();
            this.SuspendLayout();
            // 
            // workArea
            // 
            this.workArea.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.workArea.ColumnCount = 1;
            this.workArea.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.workArea.Controls.Add(this.errorBox, 0, 0);
            this.workArea.Location = new System.Drawing.Point(0, 23);
            this.workArea.Name = "workArea";
            this.workArea.RowCount = 1;
            this.workArea.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.workArea.Size = new System.Drawing.Size(587, 314);
            this.workArea.TabIndex = 2;
            // 
            // errorList
            // 
            this.errorBox.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            //this.errorList.Location = new System.Drawing.Point(3, 3);
            this.errorBox.Name = "errorBox";
            //this.errorList.Size = new System.Drawing.Size(581, 308);
            this.errorBox.TabIndex = 1;
            this.errorBox.DrawMode = System.Windows.Forms.DrawMode.OwnerDrawVariable;
            this.errorBox.FormattingEnabled = true;
            this.errorBox.HorizontalScrollbar = true;
            this.errorBox.HorizontalExtent = 0;
            this.errorBox.IntegralHeight = false;
            this.errorBox.Name = "errorBox";
            this.errorBox.MeasureItem += new MeasureItemEventHandler(errorBox_MeasureItem);
            this.errorBox.DrawItem += new DrawItemEventHandler(errorBox_DrawItem);
            this.errorBox.BackColor = System.Drawing.SystemColors.Control;
            this.errorBox.FormattingEnabled = true;
            // 
            // MsgWin
            // 
            //this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            //this.AutoScaleMode = AutoScaleMode.Font;
            this.ClientSize = new Size(587, 341);
            parent.Controls.Add(this.workArea);
            this.Name = "MsgWin";
            this.ShowIcon = false;
            this.Text = "Message Window";
            this.workArea.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();
            return workArea;
        }

        void errorBox_DrawItem(object sender, DrawItemEventArgs e)
        {
            e.DrawBackground();
            e.DrawFocusRectangle();
            if (e.Index > 0 && errorBox.Items[e.Index] is MsgWinListItem)
            {
                MsgWinListItem mwli = (MsgWinListItem)errorBox.Items[e.Index];
                Color forecolor = e.ForeColor;
                if (mwli._foreColor != Color.Empty)
                    forecolor = mwli._foreColor;
                e.Graphics.DrawString(mwli._text,
                                      mwli._font,
                                      new SolidBrush(forecolor),
                                      e.Bounds);
            }
            else if (e.Index > 0 && errorBox.Items[e.Index] is MsgWinListItems)
            {
                MsgWinListItems mwlis = (MsgWinListItems)errorBox.Items[e.Index];
                Rectangle r = e.Bounds;
                Color forecolor;
                foreach (MsgWinListItem mwli in mwlis.items)
                {
                    if (mwli._foreColor == Color.Empty)
                        forecolor = e.ForeColor;
                    else
                        forecolor = mwli._foreColor;
                    SizeF sz = e.Graphics.MeasureString(mwli._text, mwli._font);
                    e.Graphics.DrawString(mwli._text,
                        mwli._font,
                        new SolidBrush(forecolor),
                        r);
                    r.X += (int)Math.Ceiling(sz.Width);
                }
            }
        }

        void errorBox_MeasureItem(object sender, MeasureItemEventArgs e)
        {
            MsgWinListItem msli;
            String text = "";
            if (errorBox.Items[e.Index] is MsgWinListItem)
            {
                msli = (MsgWinListItem)errorBox.Items[e.Index];
                text = msli._text;
            }
            else
            {
                msli = ((MsgWinListItems)errorBox.Items[e.Index]).items[0];
                foreach (MsgWinListItem mwli in ((MsgWinListItems)errorBox.Items[e.Index]).items)
                {
                    text += mwli._text;
                }
            }
            e.Graphics.PageUnit = GraphicsUnit.Point;
            SizeF sz = e.Graphics.MeasureString(text, msli._font);
            if (sz.Width > (float)errorBox.Width)
            {
                if (sz.Width > (float)errorBox.HorizontalExtent)
                    errorBox.HorizontalExtent = (int)Math.Ceiling(sz.Width);
            }
            else
                errorBox.HorizontalExtent = 0;
            e.ItemHeight = (int)Math.Ceiling(sz.Height) + 4;
        }


        protected override void createMenus(MenuStrip menu)
        {
            createFileMenu(menu);
            //createEditMenu(menu);
            //createExecuteMenu(menu);
            //if (DXApplication.theDXApplication.appAllowsScriptCommands())
            //    createCommandsMenu(menu);
            //createOptionsMenu(menu);
            //createHelpMenu(menu);
        }

        private void createFileMenu(MenuStrip menubar)
        {
            ComponentResourceManager resources = new ComponentResourceManager(typeof(DXWindow));

            SuspendLayout();
            menubar.SuspendLayout();

            fileMenu = new ToolStripMenuItem();
            fileMenu.Name = "fileMenu";
            menubar.Items.Add(fileMenu);

            logOption = new DXToolStripMenuItem("msgLogOption", logCmd);
            logOption.Name = "msgLogOption";
            saveOption = new DXToolStripMenuItem("msgSaveOption", saveCmd);
            saveOption.Name = "msgSaveOption";

            ToolStripSeparator sep2 = new ToolStripSeparator();

            closeOption = new DXToolStripMenuItem("msgCloseOption", closeCmd);
            closeOption.Name = "closeOption";
            fileMenu.DropDownItems.AddRange(new ToolStripItem[] {
                logOption, saveOption, sep2, closeOption});

            resources.ApplyResources(fileMenu, "fileMenu");
            resources.ApplyResources(logOption, "logOption");
            resources.ApplyResources(saveOption, "msgSaveOption");
            resources.ApplyResources(closeOption, "msgCloseOption");

            menubar.ResumeLayout();
            menubar.PerformLayout();

            ResumeLayout();
            PerformLayout();
        }

        // Check this
        public void addInformation(String line)
        {
            if (!DXApplication.theDXApplication.IsInfoEnabled)
                return;

            if (line == null || line.Length == 0)
                return;

            Regex regex = new Regex(@"\n");
            line = regex.Replace(line, Environment.NewLine);

            if (firstMsg)
            {
                firstMsg = false;
                if (logFile != null)
                {
                    logFile.Write("Begin Execution" + Environment.NewLine);
                }
                MsgWinListItem s = new MsgWinListItem("Begin Execution",
                    Color.Red, Color.Empty, new Font(FontFamily.GenericSansSerif, 9.0F,
                    FontStyle.Italic));
                errorBox.Items.Add(s);

                clearCmd.activate();
            }

            if (logFile != null)
            {
                logFile.Write(line + "\n");
            }
            MsgWinListItem s1 = new MsgWinListItem(line,
                    Color.Empty, Color.Empty, new Font(FontFamily.GenericSansSerif, 9.0F,
                    FontStyle.Regular));
            errorBox.Items.Add(s1);
            clearCmd.activate();

            if (DXApplication.theDXApplication.DoesInfoOpenMessage)
            {
                if (!Visible)
                    Visible = true;
            }
        }

        // Check this
        public void addError(String line)
        {
            if (!DXApplication.theDXApplication.IsErrorEnabled)
                return;
            if (line == null || line.Length == 0)
                return;

            if (firstMsg)
            {
                firstMsg = false;
                if (logFile != null)
                {
                    logFile.Write("Begin Execution" + Environment.NewLine);
                }
                MsgWinListItem s = new MsgWinListItem("Begin Execution", 
                    Color.Red, Color.Empty, new Font(FontFamily.GenericSansSerif, 9.0F,
                    FontStyle.Italic));
                errorBox.Items.Add(s);

                clearCmd.activate();
            }

            if (DXApplication.theDXApplication.DoesErrorOpenMessage && !Enabled)
                Enabled = true;

            // If this is a module error, change the format and report it.
            //  0:  ERROR:  2::/main:0/Compute:0: Bad parameter: expression must be a string
            String topNet = DXApplication.theDXApplication.network.NameString;
            Regex regex = new Regex(@" \d+:  ERROR:  \d+::/(.+):(\d+)/(.*)");
            Match m  = regex.Match(line);
            if (m.Success && m.Groups[1].Value == topNet)
            {
                String rep = "";
                String subline = m.Groups[3].Value;
                regex = new Regex(@"(.+):(\d+)/(.*)");
                m = regex.Match(subline);
                while (m.Success)
                {
                    rep += m.Groups[1].Value + ": ";

                    subline = m.Groups[3].Value;
                    m = regex.Match(subline);
                }
                regex = new Regex(@"(.+):(\d+)(.*)");
                m = regex.Match(subline);
                if (m.Success)
                {
                    rep += m.Groups[1].Value + ": ";
                    subline = m.Groups[3].Value;
                    subline = subline.TrimStart(new char[] { ':', ' ', '\t' });
                }


                MsgWinListItem s2 = new MsgWinListItem(rep, Color.Empty, Color.Empty,
                    new Font(FontFamily.GenericSansSerif, 9.0F, FontStyle.Bold));
                MsgWinListItem s3 = new MsgWinListItem(subline, Color.Empty, Color.Empty,
                    new Font(FontFamily.GenericSansSerif, 9.0F, FontStyle.Regular));

                MsgWinListItems fullLine = new MsgWinListItems(new MsgWinListItem[] { s2, s3 });
                errorBox.Items.Add(fullLine);
            }
            else
            {
                if (logFile != null)
                {
                    logFile.Write(line + Environment.NewLine);
                }
                MsgWinListItem s = new MsgWinListItem( line, Color.Empty, Color.Empty,
                    new Font(FontFamily.GenericSansSerif, 9.0F, FontStyle.Bold));
                errorBox.Items.Add(s);
                clearCmd.activate();
            }
            if (DXApplication.theDXApplication.DoesErrorOpenMessage)
            {
                if (!beenBeeped)
                {
                    System.Media.SystemSounds.Beep.Play();
                    beenBeeped = true;
                }
                if (!Visible)
                    Visible = true;
                else
                    BringToFront();
            }
        }

        // Check this
        public void addWarning(String line)
        {
            if (!DXApplication.theDXApplication.IsWarningEnabled)
                return;
            if (line == null || line.Length == 0)
                return;

            if (firstMsg)
            {
                firstMsg = false;
                if (logFile != null)
                {
                    logFile.Write("Begin Execution\n");
                }
                MsgWinListItem s = new MsgWinListItem("Begin Execution", Color.Red, Color.Empty,
                    new Font(FontFamily.GenericSansSerif, 9.0F, FontStyle.Italic));
                errorBox.Items.Add(s);
                clearCmd.activate();
            }

            if (logFile != null)
                logFile.Write(line + "\n");

            MsgWinListItem s1 = new MsgWinListItem(line, Color.Empty, Color.Empty,
                new Font(FontFamily.GenericSansSerif, 9.0F, FontStyle.Regular));

            errorBox.Items.Add(s1);

            if (DXApplication.theDXApplication.DoesWarningOpenMessage)
            {
                if (!this.Visible)
                    Visible = true;
                else
                    BringToFront();
            }
        }

        public void infoOpen()
        {
            throw new Exception("Not Yet Implemented");
        }

        public void clear()
        {
            errorBox.Items.Clear();
            clearCmd.deactivate();
        }

        protected override void beginExecution()
        {
            firstMsg = true;
            executing = true;
            beenBeeped = false;

            clearSelectableLines();
        }

        public void clearSelectedLines()
        {
            throw new Exception("Not Yet Implemented");
        }

        protected override void endExecution()
        {
            base.endExecution();

            executing = false;
            if (errorBox.SelectedItems.Count > 0)
            {
                findNextError(false);
                nextErrorCmd.activate();
                prevErrorCmd.activate();
            }
            else
            {
                nextErrorCmd.deactivate();
                prevErrorCmd.activate();
            }
        }

        public void clearSelectableLines()
        {
            throw new Exception("Not Yet Implemented");
        }

        public void findNextError() { findNextError(true); }
        public void findNextError(bool activateSameSelection)
        {
            throw new Exception("Not Yet Implemented");
        }

        public void findPrevError()
        {
            throw new Exception("Not Yet Implemented");
        }

        public bool log(String filename)
        {
            throw new Exception("Not Yet Implemented");
        }

        public bool save(String filename)
        {
            throw new Exception("Not Yet Implemented");
        }

        public void postLogDialog()
        {
            throw new Exception("Not Yet Implemented");
        }
        public void postSaveDialog()
        {
            throw new Exception("Not Yet Implemented");
        }
        public void postExecCommandDialog()
        {
            throw new Exception("Not Yet Implemented");
        }

        public String LogFile { get { return logFileName; } }

        public bool toggleTracing() { throw new Exception("Not Yet Implemented"); }
        public bool memoryUse() { throw new Exception("Not Yet Implemented"); }
    }
}