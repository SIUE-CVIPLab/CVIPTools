namespace CVIP_ATAT
{
    partial class MDIMainForm
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
            System.Windows.Forms.ToolStripMenuItem mnuFile;
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(MDIMainForm));
            this.mnuNewProject = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuOpenProject = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuCloseProject = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuSaveProject = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
            this.mnuExit = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator2 = new System.Windows.Forms.ToolStripSeparator();
            this.mnuAskBeforeExit = new System.Windows.Forms.ToolStripMenuItem();
            this.MainMenu = new System.Windows.Forms.MenuStrip();
            this.mnuHelp = new System.Windows.Forms.ToolStripMenuItem();
            this.contenToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.aboutCVIPATATToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.openProject = new System.Windows.Forms.OpenFileDialog();
            this.tbSep2 = new System.Windows.Forms.ToolStripLabel();
            this.tbColLabel = new System.Windows.Forms.ToolStripLabel();
            this.tbColValue = new System.Windows.Forms.ToolStripLabel();
            this.tbRowLabel = new System.Windows.Forms.ToolStripLabel();
            this.tbRowValue = new System.Windows.Forms.ToolStripLabel();
            this.tbSep4 = new System.Windows.Forms.ToolStripLabel();
            this.tbRLabel = new System.Windows.Forms.ToolStripLabel();
            this.tbRValue = new System.Windows.Forms.ToolStripLabel();
            this.tbGLabel = new System.Windows.Forms.ToolStripLabel();
            this.tbGValue = new System.Windows.Forms.ToolStripLabel();
            this.tbBLabel = new System.Windows.Forms.ToolStripLabel();
            this.toolbarCVIP = new System.Windows.Forms.ToolStrip();
            this.tbOpen = new System.Windows.Forms.ToolStripButton();
            this.tbBValue = new System.Windows.Forms.ToolStripLabel();
            this.fileDialog = new System.Windows.Forms.OpenFileDialog();
            mnuFile = new System.Windows.Forms.ToolStripMenuItem();
            this.MainMenu.SuspendLayout();
            this.toolbarCVIP.SuspendLayout();
            this.SuspendLayout();
            // 
            // mnuFile
            // 
            mnuFile.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.mnuNewProject,
            this.mnuOpenProject,
            this.mnuCloseProject,
            this.mnuSaveProject,
            this.toolStripSeparator1,
            this.mnuExit,
            this.toolStripSeparator2,
            this.mnuAskBeforeExit});
            mnuFile.Name = "mnuFile";
            mnuFile.Size = new System.Drawing.Size(37, 20);
            mnuFile.Text = "&File";
            // 
            // mnuNewProject
            // 
            this.mnuNewProject.Name = "mnuNewProject";
            this.mnuNewProject.Size = new System.Drawing.Size(152, 22);
            this.mnuNewProject.Text = "&New Project";
            this.mnuNewProject.Click += new System.EventHandler(this.mnuNewProject_Click);
            // 
            // mnuOpenProject
            // 
            this.mnuOpenProject.Name = "mnuOpenProject";
            this.mnuOpenProject.Size = new System.Drawing.Size(152, 22);
            this.mnuOpenProject.Text = "&Open Project";
            this.mnuOpenProject.Click += new System.EventHandler(this.mnuOpenProject_Click);
            // 
            // mnuCloseProject
            // 
            this.mnuCloseProject.Enabled = false;
            this.mnuCloseProject.Name = "mnuCloseProject";
            this.mnuCloseProject.Size = new System.Drawing.Size(152, 22);
            this.mnuCloseProject.Text = "&Close Project";
            this.mnuCloseProject.Click += new System.EventHandler(this.mnuClose_Click);
            // 
            // mnuSaveProject
            // 
            this.mnuSaveProject.Enabled = false;
            this.mnuSaveProject.Name = "mnuSaveProject";
            this.mnuSaveProject.Size = new System.Drawing.Size(152, 22);
            this.mnuSaveProject.Text = "&Save Project";
            this.mnuSaveProject.Click += new System.EventHandler(this.mnuSaveProject_Click);
            // 
            // toolStripSeparator1
            // 
            this.toolStripSeparator1.Name = "toolStripSeparator1";
            this.toolStripSeparator1.Size = new System.Drawing.Size(149, 6);
            // 
            // mnuExit
            // 
            this.mnuExit.Name = "mnuExit";
            this.mnuExit.Size = new System.Drawing.Size(152, 22);
            this.mnuExit.Text = "&Exit";
            this.mnuExit.Click += new System.EventHandler(this.exitToolStripMenuItem_Click);
            // 
            // toolStripSeparator2
            // 
            this.toolStripSeparator2.Name = "toolStripSeparator2";
            this.toolStripSeparator2.Size = new System.Drawing.Size(149, 6);
            // 
            // mnuAskBeforeExit
            // 
            this.mnuAskBeforeExit.Name = "mnuAskBeforeExit";
            this.mnuAskBeforeExit.Size = new System.Drawing.Size(152, 22);
            this.mnuAskBeforeExit.Text = "Ask Before Exit";
            this.mnuAskBeforeExit.Click += new System.EventHandler(this.mnuAskBeforeExit_Click);
            // 
            // MainMenu
            // 
            this.MainMenu.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            mnuFile,
            this.mnuHelp});
            this.MainMenu.Location = new System.Drawing.Point(0, 0);
            this.MainMenu.Name = "MainMenu";
            this.MainMenu.Size = new System.Drawing.Size(761, 24);
            this.MainMenu.TabIndex = 1;
            this.MainMenu.Text = "MainMenu";
            // 
            // mnuHelp
            // 
            this.mnuHelp.BackColor = System.Drawing.Color.Yellow;
            this.mnuHelp.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.contenToolStripMenuItem,
            this.aboutCVIPATATToolStripMenuItem});
            this.mnuHelp.Name = "mnuHelp";
            this.mnuHelp.Size = new System.Drawing.Size(44, 20);
            this.mnuHelp.Text = "&Help";
            // 
            // contenToolStripMenuItem
            // 
            this.contenToolStripMenuItem.Name = "contenToolStripMenuItem";
            this.contenToolStripMenuItem.Size = new System.Drawing.Size(171, 22);
            this.contenToolStripMenuItem.Text = "&Contents";
            this.contenToolStripMenuItem.Click += new System.EventHandler(this.contenToolStripMenuItem_Click);
            // 
            // aboutCVIPATATToolStripMenuItem
            // 
            this.aboutCVIPATATToolStripMenuItem.Name = "aboutCVIPATATToolStripMenuItem";
            this.aboutCVIPATATToolStripMenuItem.Size = new System.Drawing.Size(171, 22);
            this.aboutCVIPATATToolStripMenuItem.Text = "&About CVIP - ATAT";
            this.aboutCVIPATATToolStripMenuItem.Click += new System.EventHandler(this.aboutCVIPATATToolStripMenuItem_Click);
            // 
            // openProject
            // 
            this.openProject.FileName = "openProject";
            // 
            // tbSep2
            // 
            this.tbSep2.AutoSize = false;
            this.tbSep2.Name = "tbSep2";
            this.tbSep2.Size = new System.Drawing.Size(10, 28);
            // 
            // tbColLabel
            // 
            this.tbColLabel.Name = "tbColLabel";
            this.tbColLabel.Size = new System.Drawing.Size(53, 28);
            this.tbColLabel.Text = "Column:";
            this.tbColLabel.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            this.tbColLabel.ToolTipText = "Current column";
            // 
            // tbColValue
            // 
            this.tbColValue.AutoSize = false;
            this.tbColValue.Name = "tbColValue";
            this.tbColValue.Size = new System.Drawing.Size(40, 28);
            this.tbColValue.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.tbColValue.ToolTipText = "Current column";
            // 
            // tbRowLabel
            // 
            this.tbRowLabel.Name = "tbRowLabel";
            this.tbRowLabel.Size = new System.Drawing.Size(33, 28);
            this.tbRowLabel.Text = "Row:";
            this.tbRowLabel.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            this.tbRowLabel.ToolTipText = "Current row";
            // 
            // tbRowValue
            // 
            this.tbRowValue.AutoSize = false;
            this.tbRowValue.Name = "tbRowValue";
            this.tbRowValue.Size = new System.Drawing.Size(40, 28);
            this.tbRowValue.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.tbRowValue.ToolTipText = "Current row";
            // 
            // tbSep4
            // 
            this.tbSep4.AutoSize = false;
            this.tbSep4.Name = "tbSep4";
            this.tbSep4.Size = new System.Drawing.Size(30, 28);
            // 
            // tbRLabel
            // 
            this.tbRLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.tbRLabel.ForeColor = System.Drawing.Color.Red;
            this.tbRLabel.Name = "tbRLabel";
            this.tbRLabel.Size = new System.Drawing.Size(20, 28);
            this.tbRLabel.Text = "R:";
            this.tbRLabel.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            this.tbRLabel.ToolTipText = "Red pixel value";
            // 
            // tbRValue
            // 
            this.tbRValue.AutoSize = false;
            this.tbRValue.ForeColor = System.Drawing.Color.Red;
            this.tbRValue.Name = "tbRValue";
            this.tbRValue.Size = new System.Drawing.Size(85, 28);
            this.tbRValue.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.tbRValue.ToolTipText = "Red pixel value";
            // 
            // tbGLabel
            // 
            this.tbGLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.tbGLabel.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(192)))), ((int)(((byte)(0)))));
            this.tbGLabel.Name = "tbGLabel";
            this.tbGLabel.Size = new System.Drawing.Size(20, 28);
            this.tbGLabel.Text = "G:";
            this.tbGLabel.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            this.tbGLabel.ToolTipText = "Green pixel value";
            // 
            // tbGValue
            // 
            this.tbGValue.AutoSize = false;
            this.tbGValue.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(192)))), ((int)(((byte)(0)))));
            this.tbGValue.Name = "tbGValue";
            this.tbGValue.Size = new System.Drawing.Size(85, 28);
            this.tbGValue.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.tbGValue.ToolTipText = "Green pixel value";
            // 
            // tbBLabel
            // 
            this.tbBLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.tbBLabel.ForeColor = System.Drawing.Color.Blue;
            this.tbBLabel.Name = "tbBLabel";
            this.tbBLabel.Size = new System.Drawing.Size(19, 28);
            this.tbBLabel.Text = "B:";
            this.tbBLabel.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            this.tbBLabel.ToolTipText = "Blue pixel value";
            // 
            // toolbarCVIP
            // 
            this.toolbarCVIP.ImageScalingSize = new System.Drawing.Size(24, 24);
            this.toolbarCVIP.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.tbOpen,
            this.tbSep2,
            this.tbColLabel,
            this.tbColValue,
            this.tbRowLabel,
            this.tbRowValue,
            this.tbSep4,
            this.tbRLabel,
            this.tbRValue,
            this.tbGLabel,
            this.tbGValue,
            this.tbBLabel,
            this.tbBValue});
            this.toolbarCVIP.Location = new System.Drawing.Point(0, 24);
            this.toolbarCVIP.Name = "toolbarCVIP";
            this.toolbarCVIP.Size = new System.Drawing.Size(761, 31);
            this.toolbarCVIP.TabIndex = 6;
            // 
            // tbOpen
            // 
            this.tbOpen.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.tbOpen.Image = ((System.Drawing.Image)(resources.GetObject("tbOpen.Image")));
            this.tbOpen.ImageTransparentColor = System.Drawing.Color.Fuchsia;
            this.tbOpen.Name = "tbOpen";
            this.tbOpen.Size = new System.Drawing.Size(28, 28);
            this.tbOpen.Text = "Open";
            this.tbOpen.Click += new System.EventHandler(this.tbOpen_Click);
            // 
            // tbBValue
            // 
            this.tbBValue.AutoSize = false;
            this.tbBValue.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(192)))), ((int)(((byte)(0)))));
            this.tbBValue.Name = "tbBValue";
            this.tbBValue.Size = new System.Drawing.Size(85, 28);
            this.tbBValue.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.tbBValue.ToolTipText = "Blue pixel value";
            // 
            // fileDialog
            // 
            this.fileDialog.Title = "Select File";
            // 
            // MDIMainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.ControlDark;
            this.ClientSize = new System.Drawing.Size(761, 409);
            this.Controls.Add(this.toolbarCVIP);
            this.Controls.Add(this.MainMenu);
            this.IsMdiContainer = true;
            this.MainMenuStrip = this.MainMenu;
            this.Name = "MDIMainForm";
            this.Text = "Automatic CVIP Algorithm Test and Analysis Tool";
            this.WindowState = System.Windows.Forms.FormWindowState.Maximized;
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.MDIMainForm_FormClosing);
            this.Load += new System.EventHandler(this.MDIMainForm_Load);
            this.MainMenu.ResumeLayout(false);
            this.MainMenu.PerformLayout();
            this.toolbarCVIP.ResumeLayout(false);
            this.toolbarCVIP.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        public System.Windows.Forms.MenuStrip MainMenu;
        public System.Windows.Forms.OpenFileDialog openProject;
        public System.Windows.Forms.ToolStripMenuItem mnuNewProject;
        public System.Windows.Forms.ToolStripMenuItem mnuOpenProject;
        public System.Windows.Forms.ToolStripMenuItem mnuExit;
        public System.Windows.Forms.ToolStripMenuItem mnuHelp;
        public System.Windows.Forms.ToolStripMenuItem mnuAskBeforeExit;
        public System.Windows.Forms.ToolStripMenuItem contenToolStripMenuItem;
        public System.Windows.Forms.ToolStripMenuItem aboutCVIPATATToolStripMenuItem;
        public System.Windows.Forms.ToolStripMenuItem mnuSaveProject;
        public System.Windows.Forms.ToolStripMenuItem mnuCloseProject;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator2;
        private System.Windows.Forms.ToolStripLabel tbSep2;
        private System.Windows.Forms.ToolStripLabel tbColLabel;
        public System.Windows.Forms.ToolStripLabel tbColValue;
        private System.Windows.Forms.ToolStripLabel tbRowLabel;
        public System.Windows.Forms.ToolStripLabel tbRowValue;
        private System.Windows.Forms.ToolStripLabel tbSep4;
        private System.Windows.Forms.ToolStripLabel tbRLabel;
        public System.Windows.Forms.ToolStripLabel tbRValue;
        private System.Windows.Forms.ToolStripLabel tbGLabel;
        public System.Windows.Forms.ToolStripLabel tbGValue;
        private System.Windows.Forms.ToolStripLabel tbBLabel;
        private System.Windows.Forms.ToolStrip toolbarCVIP;
        public System.Windows.Forms.ToolStripLabel tbBValue;
        private System.Windows.Forms.ToolStripButton tbOpen;
        private System.Windows.Forms.OpenFileDialog fileDialog;
    }
}

