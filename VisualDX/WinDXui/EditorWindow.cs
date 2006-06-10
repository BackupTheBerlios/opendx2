using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace WinDX.UI
{
    public partial class EditorWindow : DXWindow
    {
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel1;
        private System.Windows.Forms.TabControl PageSelector;
        private System.Windows.Forms.TabPage tabPage1;


        public EditorWindow() : base("editorWindow", false, true)
        {
            //InitializeComponent();

        }
        public EditorWindow(bool isAnchor, Network network) : base("editorWindow", isAnchor, true)
        {
            //InitializeComponent();
        }

        protected override Control createWorkArea(Form parent)
        {
            this.tableLayoutPanel1 = new System.Windows.Forms.TableLayoutPanel();
            this.PageSelector = new System.Windows.Forms.TabControl();
            this.tabPage1 = new System.Windows.Forms.TabPage();
            this.tableLayoutPanel1.SuspendLayout();
            this.PageSelector.SuspendLayout();
            this.SuspendLayout();
            // 
            // tableLayoutPanel1
            // 
            this.tableLayoutPanel1.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.tableLayoutPanel1.ColumnCount = 2;
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Absolute, 150F));
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutPanel1.Controls.Add(this.PageSelector, 1, 0);
            //this.tableLayoutPanel1.Location = new System.Drawing.Point(2, 4);
            this.tableLayoutPanel1.Name = "tableLayoutPanel1";
            this.tableLayoutPanel1.RowCount = 1;
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 100F));
            //this.tableLayoutPanel1.Size = new System.Drawing.Size(603, 408);
            this.tableLayoutPanel1.TabIndex = 0;
            // 
            // PageSelector
            // 
            this.PageSelector.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.PageSelector.Controls.Add(this.tabPage1);
            //this.PageSelector.Controls.Add(this.tabPage2);
            //this.PageSelector.Location = new System.Drawing.Point(153, 3);
            this.PageSelector.Name = "PageSelector";
            this.PageSelector.SelectedIndex = 0;
            //this.PageSelector.Size = new System.Drawing.Size(447, 402);
            this.PageSelector.TabIndex = 0;
            // 
            // tabPage1
            // 
            //this.tabPage1.Location = new System.Drawing.Point(4, 22);
            this.tabPage1.Name = "tabPage1";
            this.tabPage1.Padding = new System.Windows.Forms.Padding(3);
            //this.tabPage1.Size = new System.Drawing.Size(439, 376);
            this.tabPage1.TabIndex = 0;
            this.tabPage1.Text = "tabPage1";
            this.tabPage1.UseVisualStyleBackColor = true;
            // 
            // EditorWindow
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(607, 413);
            //this.Controls.Add(this.tableLayoutPanel1);
            this.Name = "EditorWindow";
            this.Text = "EditorWindow";
            this.tableLayoutPanel1.ResumeLayout(false);
            this.PageSelector.ResumeLayout(false);
            //this.ResumeLayout(false);
            return tableLayoutPanel1;
        }

        protected override void createMenus(MenuStrip menu)
        {
            //createFileMenu(menu);
            //createEditMenu(menu);
            createExecuteMenu(menu);
            //createWindowsMenu(menu);
            //createConnectionMenu(menu);
            //createOptionsMenu(menu);
            //createHelpMenu(menu);
        }

        // These aren't implemented yet.
        public void prepareForNewNetwork() { }
        public void installWorkSpaceInfo(ref WorkSpaceInfo info) {}
        public void completeNewNetwork() { }
        public void resetWindowTitle() { }
        public void beginPageChange() { }
        public void endPageChange() { }
        public void newDecorator(Decorator dec) { newDecorator(dec, null); }
        public void newDecorator(Decorator dec, EditorWorkSpace where) { }
        public void newNode(Node node, EditorWorkSpace where) { }

    }
}