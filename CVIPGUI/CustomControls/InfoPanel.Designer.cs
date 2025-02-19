namespace CVIPGUI
{
    partial class InfoPanel
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
            this.components = new System.ComponentModel.Container();
            this.pnlBorderOuter = new System.Windows.Forms.Panel();
            this.pnlBorderInner = new System.Windows.Forms.Panel();
            this.richTextInfo = new System.Windows.Forms.RichTextBox();
            this.mnuInfoPanel = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.mnuInfoCopy = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuInfoSep1 = new System.Windows.Forms.ToolStripSeparator();
            this.mnuInfoClear = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuInfoSep2 = new System.Windows.Forms.ToolStripSeparator();
            this.mnuInfoHide = new System.Windows.Forms.ToolStripMenuItem();
            this.splitter = new System.Windows.Forms.Splitter();
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.pnlBorderOuter.SuspendLayout();
            this.pnlBorderInner.SuspendLayout();
            this.mnuInfoPanel.SuspendLayout();
            this.SuspendLayout();
            // 
            // pnlBorderOuter
            // 
            this.pnlBorderOuter.BackColor = System.Drawing.SystemColors.Control;
            this.pnlBorderOuter.Controls.Add(this.pnlBorderInner);
            this.pnlBorderOuter.Dock = System.Windows.Forms.DockStyle.Fill;
            this.pnlBorderOuter.Location = new System.Drawing.Point(1, 1);
            this.pnlBorderOuter.Name = "pnlBorderOuter";
            this.pnlBorderOuter.Padding = new System.Windows.Forms.Padding(6, 6, 7, 7);
            this.pnlBorderOuter.Size = new System.Drawing.Size(515, 121);
            this.pnlBorderOuter.TabIndex = 0;
            // 
            // pnlBorderInner
            // 
            this.pnlBorderInner.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(127)))), ((int)(((byte)(157)))), ((int)(((byte)(185)))));
            this.pnlBorderInner.Controls.Add(this.richTextInfo);
            this.pnlBorderInner.Dock = System.Windows.Forms.DockStyle.Fill;
            this.pnlBorderInner.Location = new System.Drawing.Point(6, 6);
            this.pnlBorderInner.Name = "pnlBorderInner";
            this.pnlBorderInner.Padding = new System.Windows.Forms.Padding(1);
            this.pnlBorderInner.Size = new System.Drawing.Size(502, 108);
            this.pnlBorderInner.TabIndex = 0;
            // 
            // richTextInfo
            // 
            this.richTextInfo.BackColor = System.Drawing.SystemColors.Window;
            this.richTextInfo.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.richTextInfo.ContextMenuStrip = this.mnuInfoPanel;
            this.richTextInfo.Dock = System.Windows.Forms.DockStyle.Fill;
            this.richTextInfo.Location = new System.Drawing.Point(1, 1);
            this.richTextInfo.Name = "richTextInfo";
            this.richTextInfo.ReadOnly = true;
            this.richTextInfo.Size = new System.Drawing.Size(500, 106);
            this.richTextInfo.TabIndex = 0;
            this.richTextInfo.TabStop = false;
            this.richTextInfo.Text = "";
            this.richTextInfo.SelectionChanged += new System.EventHandler(this.richTextInfo_SelectionChanged);
            // 
            // mnuInfoPanel
            // 
            this.mnuInfoPanel.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.mnuInfoCopy,
            this.mnuInfoSep1,
            this.mnuInfoClear,
            this.mnuInfoSep2,
            this.mnuInfoHide});
            this.mnuInfoPanel.Name = "mnuInfoPanel";
            this.mnuInfoPanel.Size = new System.Drawing.Size(103, 82);
            // 
            // mnuInfoCopy
            // 
            this.mnuInfoCopy.Enabled = false;
            this.mnuInfoCopy.Name = "mnuInfoCopy";
            this.mnuInfoCopy.Size = new System.Drawing.Size(102, 22);
            this.mnuInfoCopy.Text = "&Copy";
            this.mnuInfoCopy.Click += new System.EventHandler(this.mnuInfoCopy_Click);
            // 
            // mnuInfoSep1
            // 
            this.mnuInfoSep1.Name = "mnuInfoSep1";
            this.mnuInfoSep1.Size = new System.Drawing.Size(99, 6);
            // 
            // mnuInfoClear
            // 
            this.mnuInfoClear.Name = "mnuInfoClear";
            this.mnuInfoClear.Size = new System.Drawing.Size(102, 22);
            this.mnuInfoClear.Text = "Clea&r";
            this.mnuInfoClear.Click += new System.EventHandler(this.mnuInfoClear_Click);
            // 
            // mnuInfoSep2
            // 
            this.mnuInfoSep2.Name = "mnuInfoSep2";
            this.mnuInfoSep2.Size = new System.Drawing.Size(99, 6);
            // 
            // mnuInfoHide
            // 
            this.mnuInfoHide.Name = "mnuInfoHide";
            this.mnuInfoHide.Size = new System.Drawing.Size(102, 22);
            this.mnuInfoHide.Text = "&Hide";
            this.mnuInfoHide.Click += new System.EventHandler(this.mnuInfoHide_Click);
            // 
            // splitter
            // 
            this.splitter.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.splitter.Location = new System.Drawing.Point(0, 0);
            this.splitter.Name = "splitter";
            this.splitter.Size = new System.Drawing.Size(515, 4);
            this.splitter.TabIndex = 0;
            this.splitter.TabStop = false;
            // 
            // timer1
            // 
            this.timer1.Enabled = true;
            this.timer1.Interval = 1000;
            this.timer1.Tick += new System.EventHandler(this.timer1_Tick);
            // 
            // InfoPanel
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.ButtonShadow;
            this.Controls.Add(this.pnlBorderOuter);
            this.Name = "InfoPanel";
            this.Padding = new System.Windows.Forms.Padding(1, 1, 0, 1);
            this.Size = new System.Drawing.Size(516, 123);
            this.pnlBorderOuter.ResumeLayout(false);
            this.pnlBorderInner.ResumeLayout(false);
            this.mnuInfoPanel.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Panel pnlBorderOuter;
        private System.Windows.Forms.Panel pnlBorderInner;
        private System.Windows.Forms.RichTextBox richTextInfo;
        private System.Windows.Forms.Splitter splitter;
        private System.Windows.Forms.ContextMenuStrip mnuInfoPanel;
        private System.Windows.Forms.ToolStripMenuItem mnuInfoCopy;
        private System.Windows.Forms.ToolStripSeparator mnuInfoSep1;
        private System.Windows.Forms.ToolStripMenuItem mnuInfoClear;
        private System.Windows.Forms.ToolStripSeparator mnuInfoSep2;
        private System.Windows.Forms.ToolStripMenuItem mnuInfoHide;
        private System.Windows.Forms.Timer timer1;
    }
}
