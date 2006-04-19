namespace WinDX.UI
{
        partial class DialogManager
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

            #region Windows Form Designer generated code

            /// <summary>
            /// Required method for Designer support - do not modify
            /// the contents of this method with the code editor.
            /// </summary>
            private void InitializeComponent()
            {
                this.tableLayoutPanel1 = new System.Windows.Forms.TableLayoutPanel();
                this.iconBox = new System.Windows.Forms.PictureBox();
                this.tableLayoutPanel2 = new System.Windows.Forms.TableLayoutPanel();
                this.flowLayoutPanel1 = new System.Windows.Forms.FlowLayoutPanel();
                this.okButton = new System.Windows.Forms.Button();
                this.cancelButton = new System.Windows.Forms.Button();
                this.helpButton = new System.Windows.Forms.Button();
                this.messageLabel = new System.Windows.Forms.Label();
                this.tableLayoutPanel1.SuspendLayout();
                ((System.ComponentModel.ISupportInitialize)(this.iconBox)).BeginInit();
                this.tableLayoutPanel2.SuspendLayout();
                this.flowLayoutPanel1.SuspendLayout();
                this.SuspendLayout();
                // 
                // tableLayoutPanel1
                // 
                this.tableLayoutPanel1.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                            | System.Windows.Forms.AnchorStyles.Left)
                            | System.Windows.Forms.AnchorStyles.Right)));
                this.tableLayoutPanel1.AutoSize = true;
                this.tableLayoutPanel1.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
                this.tableLayoutPanel1.ColumnCount = 2;
                this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle());
                this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle());
                this.tableLayoutPanel1.Controls.Add(this.iconBox, 0, 0);
                this.tableLayoutPanel1.Controls.Add(this.tableLayoutPanel2, 0, 2);
                this.tableLayoutPanel1.Controls.Add(this.messageLabel, 1, 0);
                this.tableLayoutPanel1.Location = new System.Drawing.Point(12, 12);
                this.tableLayoutPanel1.Name = "tableLayoutPanel1";
                this.tableLayoutPanel1.RowCount = 3;
                this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle());
                this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle());
                this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle());
                this.tableLayoutPanel1.Size = new System.Drawing.Size(255, 102);
                this.tableLayoutPanel1.TabIndex = 0;
                // 
                // iconBox
                // 
                this.iconBox.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                            | System.Windows.Forms.AnchorStyles.Right)));
                this.iconBox.Location = new System.Drawing.Point(3, 3);
                this.iconBox.Name = "iconBox";
                this.tableLayoutPanel1.SetRowSpan(this.iconBox, 2);
                this.iconBox.Size = new System.Drawing.Size(48, 48);
                this.iconBox.TabIndex = 2;
                this.iconBox.TabStop = false;
                // 
                // tableLayoutPanel2
                // 
                this.tableLayoutPanel2.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                            | System.Windows.Forms.AnchorStyles.Left)
                            | System.Windows.Forms.AnchorStyles.Right)));
                this.tableLayoutPanel2.AutoSize = true;
                this.tableLayoutPanel2.ColumnCount = 3;
                this.tableLayoutPanel1.SetColumnSpan(this.tableLayoutPanel2, 2);
                this.tableLayoutPanel2.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50F));
                this.tableLayoutPanel2.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle());
                this.tableLayoutPanel2.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50F));
                this.tableLayoutPanel2.Controls.Add(this.flowLayoutPanel1, 1, 0);
                this.tableLayoutPanel2.Location = new System.Drawing.Point(3, 57);
                this.tableLayoutPanel2.Name = "tableLayoutPanel2";
                this.tableLayoutPanel2.RowCount = 1;
                this.tableLayoutPanel2.RowStyles.Add(new System.Windows.Forms.RowStyle());
                this.tableLayoutPanel2.Size = new System.Drawing.Size(249, 42);
                this.tableLayoutPanel2.TabIndex = 1;
                // 
                // flowLayoutPanel1
                // 
                this.flowLayoutPanel1.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                            | System.Windows.Forms.AnchorStyles.Left)
                            | System.Windows.Forms.AnchorStyles.Right)));
                this.flowLayoutPanel1.AutoSize = true;
                this.flowLayoutPanel1.Controls.Add(this.okButton);
                this.flowLayoutPanel1.Controls.Add(this.cancelButton);
                this.flowLayoutPanel1.Controls.Add(this.helpButton);
                this.flowLayoutPanel1.Location = new System.Drawing.Point(3, 10);
                this.flowLayoutPanel1.Margin = new System.Windows.Forms.Padding(3, 10, 3, 3);
                this.flowLayoutPanel1.Name = "flowLayoutPanel1";
                this.flowLayoutPanel1.Size = new System.Drawing.Size(243, 29);
                this.flowLayoutPanel1.TabIndex = 1;
                this.flowLayoutPanel1.WrapContents = false;
                // 
                // okButton
                // 
                this.okButton.Location = new System.Drawing.Point(3, 3);
                this.okButton.Name = "okButton";
                this.okButton.Size = new System.Drawing.Size(75, 23);
                this.okButton.TabIndex = 0;
                this.okButton.Text = "OK";
                this.okButton.UseVisualStyleBackColor = true;
                // 
                // cancelButton
                // 
                this.cancelButton.DialogResult = System.Windows.Forms.DialogResult.Cancel;
                this.cancelButton.Location = new System.Drawing.Point(84, 3);
                this.cancelButton.Name = "cancelButton";
                this.cancelButton.Size = new System.Drawing.Size(75, 23);
                this.cancelButton.TabIndex = 1;
                this.cancelButton.Text = "Cancel";
                this.cancelButton.UseVisualStyleBackColor = true;
                // 
                // helpButton
                // 
                this.helpButton.Location = new System.Drawing.Point(165, 3);
                this.helpButton.Name = "helpButton";
                this.helpButton.Size = new System.Drawing.Size(75, 23);
                this.helpButton.TabIndex = 2;
                this.helpButton.Text = "Help";
                this.helpButton.UseVisualStyleBackColor = true;
                this.helpButton.Visible = false;
                // 
                // messageLabel
                // 
                this.messageLabel.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                            | System.Windows.Forms.AnchorStyles.Left)
                            | System.Windows.Forms.AnchorStyles.Right)));
                this.messageLabel.AutoSize = true;
                this.messageLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
                this.messageLabel.Location = new System.Drawing.Point(57, 8);
                this.messageLabel.Margin = new System.Windows.Forms.Padding(3, 8, 3, 0);
                this.messageLabel.Name = "messageLabel";
                this.messageLabel.Size = new System.Drawing.Size(195, 26);
                this.messageLabel.TabIndex = 0;
                this.messageLabel.Text = "This is the warning \ntext for the text dialog.";
                // 
                // DialogManager
                // 
                this.AcceptButton = this.okButton;
                this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
                this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
                this.AutoSize = true;
                this.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
                this.CancelButton = this.cancelButton;
                this.ClientSize = new System.Drawing.Size(278, 121);
                this.Controls.Add(this.tableLayoutPanel1);
                this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
                this.MaximizeBox = false;
                this.MinimizeBox = false;
                this.Name = "DialogManager";
                this.ShowIcon = false;
                this.Text = "Dialog";
                this.TopMost = true;
                this.tableLayoutPanel1.ResumeLayout(false);
                this.tableLayoutPanel1.PerformLayout();
                ((System.ComponentModel.ISupportInitialize)(this.iconBox)).EndInit();
                this.tableLayoutPanel2.ResumeLayout(false);
                this.tableLayoutPanel2.PerformLayout();
                this.flowLayoutPanel1.ResumeLayout(false);
                this.ResumeLayout(false);
                this.PerformLayout();

            }

            #endregion

            private System.Windows.Forms.TableLayoutPanel tableLayoutPanel1;
            private System.Windows.Forms.Label messageLabel;
            private System.Windows.Forms.FlowLayoutPanel flowLayoutPanel1;
            protected System.Windows.Forms.Button okButton;
            protected System.Windows.Forms.Button cancelButton;
            private System.Windows.Forms.TableLayoutPanel tableLayoutPanel2;
            protected System.Windows.Forms.Button helpButton;
            protected System.Windows.Forms.PictureBox iconBox;
        }
}