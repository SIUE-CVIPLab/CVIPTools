namespace CVIPFEPC.Dialogs
{
    partial class TestCompleteDlg
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
            this.pnlLayout = new System.Windows.Forms.TableLayoutPanel();
            this.pnlMessageLayout = new System.Windows.Forms.TableLayoutPanel();
            this.picIcon = new System.Windows.Forms.PictureBox();
            this.pnlMessage = new System.Windows.Forms.Panel();
            this.lblLargeResult = new System.Windows.Forms.LinkLabel();
            this.lblSmallResult = new System.Windows.Forms.LinkLabel();
            this.lblDoneMessage = new System.Windows.Forms.Label();
            this.btnOK = new System.Windows.Forms.Button();
            this.pnlLayout.SuspendLayout();
            this.pnlMessageLayout.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.picIcon)).BeginInit();
            this.pnlMessage.SuspendLayout();
            this.SuspendLayout();
            // 
            // pnlLayout
            // 
            this.pnlLayout.AutoSize = true;
            this.pnlLayout.ColumnCount = 1;
            this.pnlLayout.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.pnlLayout.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Absolute, 20F));
            this.pnlLayout.Controls.Add(this.pnlMessageLayout, 0, 0);
            this.pnlLayout.Location = new System.Drawing.Point(0, 0);
            this.pnlLayout.Margin = new System.Windows.Forms.Padding(0);
            this.pnlLayout.Name = "pnlLayout";
            this.pnlLayout.RowCount = 2;
            this.pnlLayout.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.pnlLayout.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 49F));
            this.pnlLayout.Size = new System.Drawing.Size(263, 133);
            this.pnlLayout.TabIndex = 0;
            // 
            // pnlMessageLayout
            // 
            this.pnlMessageLayout.AutoSize = true;
            this.pnlMessageLayout.BackColor = System.Drawing.SystemColors.Window;
            this.pnlMessageLayout.ColumnCount = 3;
            this.pnlMessageLayout.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Absolute, 59F));
            this.pnlMessageLayout.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.pnlMessageLayout.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Absolute, 30F));
            this.pnlMessageLayout.Controls.Add(this.picIcon, 0, 1);
            this.pnlMessageLayout.Controls.Add(this.pnlMessage, 1, 1);
            this.pnlMessageLayout.Location = new System.Drawing.Point(0, 0);
            this.pnlMessageLayout.Margin = new System.Windows.Forms.Padding(0);
            this.pnlMessageLayout.Name = "pnlMessageLayout";
            this.pnlMessageLayout.RowCount = 3;
            this.pnlMessageLayout.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 25F));
            this.pnlMessageLayout.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.pnlMessageLayout.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 25F));
            this.pnlMessageLayout.Size = new System.Drawing.Size(263, 84);
            this.pnlMessageLayout.TabIndex = 0;
            // 
            // picIcon
            // 
            this.picIcon.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.picIcon.Location = new System.Drawing.Point(25, 26);
            this.picIcon.Margin = new System.Windows.Forms.Padding(0, 1, 2, 1);
            this.picIcon.Name = "picIcon";
            this.picIcon.Size = new System.Drawing.Size(32, 32);
            this.picIcon.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.picIcon.TabIndex = 0;
            this.picIcon.TabStop = false;
            // 
            // pnlMessage
            // 
            this.pnlMessage.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.pnlMessage.Controls.Add(this.lblLargeResult);
            this.pnlMessage.Controls.Add(this.lblSmallResult);
            this.pnlMessage.Controls.Add(this.lblDoneMessage);
            this.pnlMessage.Location = new System.Drawing.Point(62, 34);
            this.pnlMessage.Margin = new System.Windows.Forms.Padding(3, 1, 0, 1);
            this.pnlMessage.Name = "pnlMessage";
            this.pnlMessage.Size = new System.Drawing.Size(171, 15);
            this.pnlMessage.TabIndex = 1;
            // 
            // lblLargeResult
            // 
            this.lblLargeResult.Location = new System.Drawing.Point(0, 15);
            this.lblLargeResult.Margin = new System.Windows.Forms.Padding(0);
            this.lblLargeResult.Name = "lblLargeResult";
            this.lblLargeResult.Size = new System.Drawing.Size(390, 15);
            this.lblLargeResult.TabIndex = 2;
            this.lblLargeResult.LinkClicked += new System.Windows.Forms.LinkLabelLinkClickedEventHandler(this.lblResult_LinkClicked);
            // 
            // lblSmallResult
            // 
            this.lblSmallResult.Location = new System.Drawing.Point(167, 0);
            this.lblSmallResult.Margin = new System.Windows.Forms.Padding(0);
            this.lblSmallResult.Name = "lblSmallResult";
            this.lblSmallResult.Size = new System.Drawing.Size(220, 15);
            this.lblSmallResult.TabIndex = 1;
            this.lblSmallResult.TextAlign = System.Drawing.ContentAlignment.BottomLeft;
            this.lblSmallResult.LinkClicked += new System.Windows.Forms.LinkLabelLinkClickedEventHandler(this.lblResult_LinkClicked);
            // 
            // lblDoneMessage
            // 
            this.lblDoneMessage.Location = new System.Drawing.Point(0, 0);
            this.lblDoneMessage.Margin = new System.Windows.Forms.Padding(0);
            this.lblDoneMessage.Name = "lblDoneMessage";
            this.lblDoneMessage.Size = new System.Drawing.Size(167, 15);
            this.lblDoneMessage.TabIndex = 0;
            this.lblDoneMessage.Text = "Done. Results can be found in:";
            this.lblDoneMessage.TextAlign = System.Drawing.ContentAlignment.BottomLeft;
            // 
            // btnOK
            // 
            this.btnOK.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.btnOK.DialogResult = System.Windows.Forms.DialogResult.OK;
            this.btnOK.Location = new System.Drawing.Point(166, 96);
            this.btnOK.Margin = new System.Windows.Forms.Padding(0, 0, 9, 11);
            this.btnOK.Name = "btnOK";
            this.btnOK.Size = new System.Drawing.Size(88, 26);
            this.btnOK.TabIndex = 1;
            this.btnOK.Text = "OK";
            this.btnOK.UseVisualStyleBackColor = true;
            // 
            // TestCompleteDlg
            // 
            this.AcceptButton = this.btnOK;
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.None;
            this.AutoSize = true;
            this.ClientSize = new System.Drawing.Size(263, 133);
            this.Controls.Add(this.btnOK);
            this.Controls.Add(this.pnlLayout);
            this.Font = new System.Drawing.Font("Segoe UI", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.ForeColor = System.Drawing.SystemColors.WindowText;
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "TestCompleteDlg";
            this.ShowIcon = false;
            this.ShowInTaskbar = false;
            this.SizeGripStyle = System.Windows.Forms.SizeGripStyle.Hide;
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
            this.Text = "Test Complete";
            this.pnlLayout.ResumeLayout(false);
            this.pnlLayout.PerformLayout();
            this.pnlMessageLayout.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.picIcon)).EndInit();
            this.pnlMessage.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TableLayoutPanel pnlLayout;
        private System.Windows.Forms.TableLayoutPanel pnlMessageLayout;
        private System.Windows.Forms.PictureBox picIcon;
        private System.Windows.Forms.Panel pnlMessage;
        private System.Windows.Forms.LinkLabel lblLargeResult;
        private System.Windows.Forms.LinkLabel lblSmallResult;
        private System.Windows.Forms.Label lblDoneMessage;
        private System.Windows.Forms.Button btnOK;
    }
}
