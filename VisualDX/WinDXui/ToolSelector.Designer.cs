namespace WinDX.UI
{
    partial class ToolSelector
    {
        /// <summary> 
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary> 
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Component Designer generated code

        /// <summary> 
        /// Required method for Designer support - do not modify 
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.Windows.Forms.TreeNode treeNode2 = new System.Windows.Forms.TreeNode("All");
            this.ToolTab = new System.Windows.Forms.TabControl();
            this.tabPage1 = new System.Windows.Forms.TabPage();
            this.ToolTree = new System.Windows.Forms.TreeView();
            this.ToolTab.SuspendLayout();
            this.tabPage1.SuspendLayout();
            this.SuspendLayout();
            // 
            // ToolTab
            // 
            this.ToolTab.Controls.Add(this.tabPage1);
            this.ToolTab.Location = new System.Drawing.Point(3, 3);
            this.ToolTab.Name = "ToolTab";
            this.ToolTab.SelectedIndex = 0;
            this.ToolTab.Size = new System.Drawing.Size(244, 589);
            this.ToolTab.TabIndex = 0;
            // 
            // tabPage1
            // 
            this.tabPage1.Controls.Add(this.ToolTree);
            this.tabPage1.Location = new System.Drawing.Point(4, 22);
            this.tabPage1.Name = "tabPage1";
            this.tabPage1.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage1.Size = new System.Drawing.Size(236, 563);
            this.tabPage1.TabIndex = 0;
            this.tabPage1.Text = "Tools";
            this.tabPage1.UseVisualStyleBackColor = true;
            // 
            // ToolTree
            // 
            this.ToolTree.BackColor = System.Drawing.SystemColors.MenuBar;
            this.ToolTree.FullRowSelect = true;
            this.ToolTree.Location = new System.Drawing.Point(3, 6);
            this.ToolTree.Name = "ToolTree";
            treeNode2.Name = "All";
            treeNode2.Text = "All";
            this.ToolTree.Nodes.AddRange(new System.Windows.Forms.TreeNode[] {
            treeNode2});
            this.ToolTree.Size = new System.Drawing.Size(227, 551);
            this.ToolTree.TabIndex = 0;
            // 
            // ToolSelector
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.ToolTab);
            this.Name = "ToolSelector";
            this.Size = new System.Drawing.Size(250, 595);
            this.ToolTab.ResumeLayout(false);
            this.tabPage1.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.TabControl ToolTab;
        private System.Windows.Forms.TabPage tabPage1;
        private System.Windows.Forms.TreeView ToolTree;
    }
}
