namespace CVIPFEPC
{
    partial class MainForm
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
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(MainForm));
            this.mnuFEPC = new System.Windows.Forms.MenuStrip();
            this.mnuFile = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuFileLoadConfig = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuFileSaveConfig = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuFileSeparator = new System.Windows.Forms.ToolStripSeparator();
            this.mnuFileExit = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuSettings = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuSettingsClasses = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuSettingsClassification = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuSettingsFeatures = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem1 = new System.Windows.Forms.ToolStripMenuItem();
            this.contentsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.aboutFEPCToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.btnRandomize = new System.Windows.Forms.Button();
            this.btnInvert = new System.Windows.Forms.Button();
            this.grpView = new System.Windows.Forms.GroupBox();
            this.rbViewMasked = new System.Windows.Forms.RadioButton();
            this.rbViewMask = new System.Windows.Forms.RadioButton();
            this.rbViewOriginal = new System.Windows.Forms.RadioButton();
            this.btnFeatures = new System.Windows.Forms.Button();
            this.btnClassification = new System.Windows.Forms.Button();
            this.btnAddFiles = new System.Windows.Forms.Button();
            this.btnDelete = new System.Windows.Forms.Button();
            this.btnAbortTest = new System.Windows.Forms.Button();
            this.btnRunTest = new System.Windows.Forms.Button();
            this.cboClasses = new System.Windows.Forms.ComboBox();
            this.lblClasses = new System.Windows.Forms.Label();
            this.txtOutputFolder = new System.Windows.Forms.LinkLabel();
            this.lblOutputFolder = new System.Windows.Forms.Label();
            this.btnOutputFolder = new System.Windows.Forms.Button();
            this.grpTestType = new System.Windows.Forms.GroupBox();
            this.pnlSingleCombinatoric = new System.Windows.Forms.Panel();
            this.rbCombinatoric = new System.Windows.Forms.RadioButton();
            this.rbSingle = new System.Windows.Forms.RadioButton();
            this.pnlTestTrainingLeave1Out = new System.Windows.Forms.Panel();
            this.rbLeave1Out = new System.Windows.Forms.RadioButton();
            this.rbTestTraining = new System.Windows.Forms.RadioButton();
            this.statFEPC = new System.Windows.Forms.StatusStrip();
            this.lblStatus = new System.Windows.Forms.ToolStripStatusLabel();
            this.pbStatus = new System.Windows.Forms.ToolStripProgressBar();
            this.dlgAddFiles = new System.Windows.Forms.OpenFileDialog();
            this.dlgAddFilesLaw = new System.Windows.Forms.OpenFileDialog();
            this.lstImages = new CVIPFEPC.CustomControls.FepcListView();
            this.udImages = new CVIPFEPC.CustomControls.UpDown();
            this.pictCurrentImage = new CVIPFEPC.CustomControls.FepcPictureBox();
            this.mnuFEPC.SuspendLayout();
            this.grpView.SuspendLayout();
            this.grpTestType.SuspendLayout();
            this.pnlSingleCombinatoric.SuspendLayout();
            this.pnlTestTrainingLeave1Out.SuspendLayout();
            this.statFEPC.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictCurrentImage)).BeginInit();
            this.SuspendLayout();
            // 
            // mnuFEPC
            // 
            this.mnuFEPC.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.mnuFile,
            this.mnuSettings,
            this.toolStripMenuItem1});
            this.mnuFEPC.Location = new System.Drawing.Point(0, 0);
            this.mnuFEPC.Name = "mnuFEPC";
            this.mnuFEPC.Size = new System.Drawing.Size(702, 24);
            this.mnuFEPC.TabIndex = 0;
            // 
            // mnuFile
            // 
            this.mnuFile.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.mnuFileLoadConfig,
            this.mnuFileSaveConfig,
            this.mnuFileSeparator,
            this.mnuFileExit});
            this.mnuFile.Name = "mnuFile";
            this.mnuFile.Size = new System.Drawing.Size(37, 20);
            this.mnuFile.Text = "&File";
            // 
            // mnuFileLoadConfig
            // 
            this.mnuFileLoadConfig.Name = "mnuFileLoadConfig";
            this.mnuFileLoadConfig.Size = new System.Drawing.Size(177, 22);
            this.mnuFileLoadConfig.Text = "&Load Configuration";
            this.mnuFileLoadConfig.Click += new System.EventHandler(this.mnuFileLoadConfig_Click);
            // 
            // mnuFileSaveConfig
            // 
            this.mnuFileSaveConfig.Name = "mnuFileSaveConfig";
            this.mnuFileSaveConfig.Size = new System.Drawing.Size(177, 22);
            this.mnuFileSaveConfig.Text = "&Save Configuration";
            this.mnuFileSaveConfig.Click += new System.EventHandler(this.mnuFileSaveConfig_Click);
            // 
            // mnuFileSeparator
            // 
            this.mnuFileSeparator.Name = "mnuFileSeparator";
            this.mnuFileSeparator.Size = new System.Drawing.Size(174, 6);
            // 
            // mnuFileExit
            // 
            this.mnuFileExit.Name = "mnuFileExit";
            this.mnuFileExit.Size = new System.Drawing.Size(177, 22);
            this.mnuFileExit.Text = "E&xit";
            this.mnuFileExit.Click += new System.EventHandler(this.mnuFileExit_Click);
            // 
            // mnuSettings
            // 
            this.mnuSettings.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.mnuSettingsClasses,
            this.mnuSettingsClassification,
            this.mnuSettingsFeatures});
            this.mnuSettings.Name = "mnuSettings";
            this.mnuSettings.Size = new System.Drawing.Size(61, 20);
            this.mnuSettings.Text = "&Settings";
            // 
            // mnuSettingsClasses
            // 
            this.mnuSettingsClasses.Name = "mnuSettingsClasses";
            this.mnuSettingsClasses.Size = new System.Drawing.Size(144, 22);
            this.mnuSettingsClasses.Text = "Class &List";
            this.mnuSettingsClasses.Click += new System.EventHandler(this.mnuSettingsClasses_Click);
            // 
            // mnuSettingsClassification
            // 
            this.mnuSettingsClassification.Name = "mnuSettingsClassification";
            this.mnuSettingsClassification.Size = new System.Drawing.Size(144, 22);
            this.mnuSettingsClassification.Text = "&Classification";
            this.mnuSettingsClassification.Click += new System.EventHandler(this.mnuSettingsClassification_Click);
            // 
            // mnuSettingsFeatures
            // 
            this.mnuSettingsFeatures.Name = "mnuSettingsFeatures";
            this.mnuSettingsFeatures.Size = new System.Drawing.Size(144, 22);
            this.mnuSettingsFeatures.Text = "&Features";
            this.mnuSettingsFeatures.Click += new System.EventHandler(this.mnuSettingsFeatures_Click);
            // 
            // toolStripMenuItem1
            // 
            this.toolStripMenuItem1.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(255)))), ((int)(((byte)(128)))));
            this.toolStripMenuItem1.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.contentsToolStripMenuItem,
            this.aboutFEPCToolStripMenuItem});
            this.toolStripMenuItem1.Name = "toolStripMenuItem1";
            this.toolStripMenuItem1.Size = new System.Drawing.Size(44, 20);
            this.toolStripMenuItem1.Text = "Help";
            this.toolStripMenuItem1.Click += new System.EventHandler(this.toolStripMenuItem1_Click);
            // 
            // contentsToolStripMenuItem
            // 
            this.contentsToolStripMenuItem.Name = "contentsToolStripMenuItem";
            this.contentsToolStripMenuItem.Size = new System.Drawing.Size(137, 22);
            this.contentsToolStripMenuItem.Text = "Contents";
            this.contentsToolStripMenuItem.Click += new System.EventHandler(this.contentsToolStripMenuItem_Click);
            // 
            // aboutFEPCToolStripMenuItem
            // 
            this.aboutFEPCToolStripMenuItem.Name = "aboutFEPCToolStripMenuItem";
            this.aboutFEPCToolStripMenuItem.Size = new System.Drawing.Size(137, 22);
            this.aboutFEPCToolStripMenuItem.Text = "About FEPC";
            this.aboutFEPCToolStripMenuItem.Click += new System.EventHandler(this.aboutFEPCToolStripMenuItem_Click);
            // 
            // btnRandomize
            // 
            this.btnRandomize.Enabled = false;
            this.btnRandomize.Location = new System.Drawing.Point(401, 38);
            this.btnRandomize.Name = "btnRandomize";
            this.btnRandomize.Size = new System.Drawing.Size(110, 25);
            this.btnRandomize.TabIndex = 3;
            this.btnRandomize.Text = "Random Selection";
            this.btnRandomize.UseVisualStyleBackColor = true;
            this.btnRandomize.Click += new System.EventHandler(this.btnRandomize_Click);
            // 
            // btnInvert
            // 
            this.btnInvert.Enabled = false;
            this.btnInvert.Location = new System.Drawing.Point(517, 38);
            this.btnInvert.Name = "btnInvert";
            this.btnInvert.Size = new System.Drawing.Size(100, 25);
            this.btnInvert.TabIndex = 4;
            this.btnInvert.Text = "Invert Selection";
            this.btnInvert.UseVisualStyleBackColor = true;
            this.btnInvert.Click += new System.EventHandler(this.btnInvert_Click);
            // 
            // grpView
            // 
            this.grpView.Controls.Add(this.rbViewMasked);
            this.grpView.Controls.Add(this.rbViewMask);
            this.grpView.Controls.Add(this.rbViewOriginal);
            this.grpView.Location = new System.Drawing.Point(21, 289);
            this.grpView.Name = "grpView";
            this.grpView.Size = new System.Drawing.Size(125, 96);
            this.grpView.TabIndex = 6;
            this.grpView.TabStop = false;
            this.grpView.Text = "View";
            // 
            // rbViewMasked
            // 
            this.rbViewMasked.AutoSize = true;
            this.rbViewMasked.Location = new System.Drawing.Point(13, 67);
            this.rbViewMasked.Name = "rbViewMasked";
            this.rbViewMasked.Size = new System.Drawing.Size(95, 17);
            this.rbViewMasked.TabIndex = 2;
            this.rbViewMasked.Text = "Masked Image";
            this.rbViewMasked.UseVisualStyleBackColor = true;
            this.rbViewMasked.CheckedChanged += new System.EventHandler(this.rbView_CheckedChanged);
            // 
            // rbViewMask
            // 
            this.rbViewMask.AutoSize = true;
            this.rbViewMask.Location = new System.Drawing.Point(13, 44);
            this.rbViewMask.Name = "rbViewMask";
            this.rbViewMask.Size = new System.Drawing.Size(51, 17);
            this.rbViewMask.TabIndex = 1;
            this.rbViewMask.Text = "Mask";
            this.rbViewMask.UseVisualStyleBackColor = true;
            this.rbViewMask.CheckedChanged += new System.EventHandler(this.rbView_CheckedChanged);
            // 
            // rbViewOriginal
            // 
            this.rbViewOriginal.AutoSize = true;
            this.rbViewOriginal.Checked = true;
            this.rbViewOriginal.Location = new System.Drawing.Point(13, 21);
            this.rbViewOriginal.Name = "rbViewOriginal";
            this.rbViewOriginal.Size = new System.Drawing.Size(92, 17);
            this.rbViewOriginal.TabIndex = 0;
            this.rbViewOriginal.TabStop = true;
            this.rbViewOriginal.Text = "Original Image";
            this.rbViewOriginal.UseVisualStyleBackColor = true;
            this.rbViewOriginal.CheckedChanged += new System.EventHandler(this.rbView_CheckedChanged);
            // 
            // btnFeatures
            // 
            this.btnFeatures.Location = new System.Drawing.Point(161, 292);
            this.btnFeatures.Name = "btnFeatures";
            this.btnFeatures.Size = new System.Drawing.Size(65, 27);
            this.btnFeatures.TabIndex = 7;
            this.btnFeatures.Text = "Features";
            this.btnFeatures.UseVisualStyleBackColor = true;
            this.btnFeatures.Click += new System.EventHandler(this.mnuSettingsFeatures_Click);
            // 
            // btnClassification
            // 
            this.btnClassification.Location = new System.Drawing.Point(231, 292);
            this.btnClassification.Name = "btnClassification";
            this.btnClassification.Size = new System.Drawing.Size(80, 27);
            this.btnClassification.TabIndex = 8;
            this.btnClassification.Text = "Classification";
            this.btnClassification.UseVisualStyleBackColor = true;
            this.btnClassification.Click += new System.EventHandler(this.mnuSettingsClassification_Click);
            // 
            // btnAddFiles
            // 
            this.btnAddFiles.Location = new System.Drawing.Point(316, 292);
            this.btnAddFiles.Name = "btnAddFiles";
            this.btnAddFiles.Size = new System.Drawing.Size(70, 27);
            this.btnAddFiles.TabIndex = 9;
            this.btnAddFiles.Text = "Add Files";
            this.btnAddFiles.UseVisualStyleBackColor = true;
            this.btnAddFiles.Click += new System.EventHandler(this.btnAddFiles_Click);
            // 
            // btnDelete
            // 
            this.btnDelete.Enabled = false;
            this.btnDelete.Location = new System.Drawing.Point(316, 325);
            this.btnDelete.Name = "btnDelete";
            this.btnDelete.Size = new System.Drawing.Size(70, 27);
            this.btnDelete.TabIndex = 10;
            this.btnDelete.Text = "Delete";
            this.btnDelete.UseVisualStyleBackColor = true;
            this.btnDelete.Click += new System.EventHandler(this.btnDelete_Click);
            // 
            // btnAbortTest
            // 
            this.btnAbortTest.Location = new System.Drawing.Point(316, 358);
            this.btnAbortTest.Name = "btnAbortTest";
            this.btnAbortTest.Size = new System.Drawing.Size(70, 27);
            this.btnAbortTest.TabIndex = 11;
            this.btnAbortTest.Text = "Abort Test";
            this.btnAbortTest.UseVisualStyleBackColor = true;
            this.btnAbortTest.Click += new System.EventHandler(this.btnAbortTest_Click);
            // 
            // btnRunTest
            // 
            this.btnRunTest.Location = new System.Drawing.Point(316, 358);
            this.btnRunTest.Name = "btnRunTest";
            this.btnRunTest.Size = new System.Drawing.Size(70, 27);
            this.btnRunTest.TabIndex = 12;
            this.btnRunTest.Text = "Run Test";
            this.btnRunTest.UseVisualStyleBackColor = true;
            this.btnRunTest.Click += new System.EventHandler(this.btnRunTest_Click);
            // 
            // cboClasses
            // 
            this.cboClasses.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cboClasses.FormattingEnabled = true;
            this.cboClasses.Location = new System.Drawing.Point(161, 364);
            this.cboClasses.Name = "cboClasses";
            this.cboClasses.Size = new System.Drawing.Size(148, 21);
            this.cboClasses.Sorted = true;
            this.cboClasses.TabIndex = 13;
            this.cboClasses.SelectedIndexChanged += new System.EventHandler(this.cboClasses_SelectedIndexChanged);
            // 
            // lblClasses
            // 
            this.lblClasses.AutoSize = true;
            this.lblClasses.Location = new System.Drawing.Point(161, 347);
            this.lblClasses.Name = "lblClasses";
            this.lblClasses.Size = new System.Drawing.Size(35, 13);
            this.lblClasses.TabIndex = 14;
            this.lblClasses.Text = "Class:";
            // 
            // txtOutputFolder
            // 
            this.txtOutputFolder.LinkColor = System.Drawing.Color.Blue;
            this.txtOutputFolder.Location = new System.Drawing.Point(21, 441);
            this.txtOutputFolder.Name = "txtOutputFolder";
            this.txtOutputFolder.Size = new System.Drawing.Size(287, 20);
            this.txtOutputFolder.TabIndex = 15;
            this.txtOutputFolder.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.txtOutputFolder.VisitedLinkColor = System.Drawing.Color.Blue;
            this.txtOutputFolder.LinkClicked += new System.Windows.Forms.LinkLabelLinkClickedEventHandler(this.txtOutputFolder_LinkClicked);
            // 
            // lblOutputFolder
            // 
            this.lblOutputFolder.AutoSize = true;
            this.lblOutputFolder.Location = new System.Drawing.Point(21, 423);
            this.lblOutputFolder.Name = "lblOutputFolder";
            this.lblOutputFolder.Size = new System.Drawing.Size(116, 13);
            this.lblOutputFolder.TabIndex = 16;
            this.lblOutputFolder.Text = "Result Output Location";
            this.lblOutputFolder.Click += new System.EventHandler(this.lblOutputFolder_Click);
            // 
            // btnOutputFolder
            // 
            this.btnOutputFolder.Location = new System.Drawing.Point(316, 439);
            this.btnOutputFolder.Name = "btnOutputFolder";
            this.btnOutputFolder.Size = new System.Drawing.Size(70, 25);
            this.btnOutputFolder.TabIndex = 17;
            this.btnOutputFolder.Text = "Browse";
            this.btnOutputFolder.UseVisualStyleBackColor = true;
            this.btnOutputFolder.Click += new System.EventHandler(this.btnOutputFolder_Click);
            // 
            // grpTestType
            // 
            this.grpTestType.Controls.Add(this.pnlSingleCombinatoric);
            this.grpTestType.Controls.Add(this.pnlTestTrainingLeave1Out);
            this.grpTestType.Location = new System.Drawing.Point(401, 392);
            this.grpTestType.Name = "grpTestType";
            this.grpTestType.Size = new System.Drawing.Size(280, 72);
            this.grpTestType.TabIndex = 18;
            this.grpTestType.TabStop = false;
            this.grpTestType.Text = "Test Type";
            this.grpTestType.Enter += new System.EventHandler(this.grpTestType_Enter);
            // 
            // pnlSingleCombinatoric
            // 
            this.pnlSingleCombinatoric.Controls.Add(this.rbCombinatoric);
            this.pnlSingleCombinatoric.Controls.Add(this.rbSingle);
            this.pnlSingleCombinatoric.Location = new System.Drawing.Point(171, 21);
            this.pnlSingleCombinatoric.Name = "pnlSingleCombinatoric";
            this.pnlSingleCombinatoric.Size = new System.Drawing.Size(86, 39);
            this.pnlSingleCombinatoric.TabIndex = 1;
            // 
            // rbCombinatoric
            // 
            this.rbCombinatoric.AutoSize = true;
            this.rbCombinatoric.Location = new System.Drawing.Point(0, 22);
            this.rbCombinatoric.Name = "rbCombinatoric";
            this.rbCombinatoric.Size = new System.Drawing.Size(86, 17);
            this.rbCombinatoric.TabIndex = 1;
            this.rbCombinatoric.Text = "Combinatoric";
            this.rbCombinatoric.UseVisualStyleBackColor = true;
            this.rbCombinatoric.CheckedChanged += new System.EventHandler(this.rbCombinatoric_CheckedChanged);
            // 
            // rbSingle
            // 
            this.rbSingle.AutoSize = true;
            this.rbSingle.Checked = true;
            this.rbSingle.Location = new System.Drawing.Point(0, 0);
            this.rbSingle.Name = "rbSingle";
            this.rbSingle.Size = new System.Drawing.Size(78, 17);
            this.rbSingle.TabIndex = 0;
            this.rbSingle.TabStop = true;
            this.rbSingle.Text = "Single Test";
            this.rbSingle.UseVisualStyleBackColor = true;
            // 
            // pnlTestTrainingLeave1Out
            // 
            this.pnlTestTrainingLeave1Out.Controls.Add(this.rbLeave1Out);
            this.pnlTestTrainingLeave1Out.Controls.Add(this.rbTestTraining);
            this.pnlTestTrainingLeave1Out.Location = new System.Drawing.Point(13, 21);
            this.pnlTestTrainingLeave1Out.Name = "pnlTestTrainingLeave1Out";
            this.pnlTestTrainingLeave1Out.Size = new System.Drawing.Size(108, 39);
            this.pnlTestTrainingLeave1Out.TabIndex = 0;
            // 
            // rbLeave1Out
            // 
            this.rbLeave1Out.AutoSize = true;
            this.rbLeave1Out.Location = new System.Drawing.Point(0, 22);
            this.rbLeave1Out.Name = "rbLeave1Out";
            this.rbLeave1Out.Size = new System.Drawing.Size(98, 17);
            this.rbLeave1Out.TabIndex = 1;
            this.rbLeave1Out.Text = "Leave One Out";
            this.rbLeave1Out.UseVisualStyleBackColor = true;
            this.rbLeave1Out.CheckedChanged += new System.EventHandler(this.rbTestTrainingLeave1Out_CheckedChanged);
            // 
            // rbTestTraining
            // 
            this.rbTestTraining.AutoSize = true;
            this.rbTestTraining.Checked = true;
            this.rbTestTraining.Location = new System.Drawing.Point(0, 0);
            this.rbTestTraining.Name = "rbTestTraining";
            this.rbTestTraining.Size = new System.Drawing.Size(108, 17);
            this.rbTestTraining.TabIndex = 0;
            this.rbTestTraining.TabStop = true;
            this.rbTestTraining.Text = "Test/Training Set";
            this.rbTestTraining.UseVisualStyleBackColor = true;
            this.rbTestTraining.CheckedChanged += new System.EventHandler(this.rbTestTrainingLeave1Out_CheckedChanged);
            // 
            // statFEPC
            // 
            this.statFEPC.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.lblStatus,
            this.pbStatus});
            this.statFEPC.Location = new System.Drawing.Point(0, 485);
            this.statFEPC.Name = "statFEPC";
            this.statFEPC.ShowItemToolTips = true;
            this.statFEPC.Size = new System.Drawing.Size(702, 22);
            this.statFEPC.TabIndex = 19;
            // 
            // lblStatus
            // 
            this.lblStatus.Name = "lblStatus";
            this.lblStatus.Size = new System.Drawing.Size(39, 17);
            this.lblStatus.Text = "Ready";
            // 
            // pbStatus
            // 
            this.pbStatus.Name = "pbStatus";
            this.pbStatus.Size = new System.Drawing.Size(100, 16);
            // 
            // dlgAddFiles
            // 
            this.dlgAddFiles.Filter = resources.GetString("dlgAddFiles.Filter");
            this.dlgAddFiles.Multiselect = true;
            this.dlgAddFiles.Title = "Select files to add";
            this.dlgAddFiles.FileOk += new System.ComponentModel.CancelEventHandler(this.dlgAddFiles_FileOk);
            // 
            // dlgAddFilesLaw
            // 
            this.dlgAddFilesLaw.FileName = "dlgAddFilesLaw";
            this.dlgAddFilesLaw.Filter = resources.GetString("dlgAddFilesLaw.Filter");
            this.dlgAddFilesLaw.Multiselect = true;
            this.dlgAddFilesLaw.Title = "Select files to add";
            // 
            // lstImages
            // 
            this.lstImages.CheckBoxes = true;
            this.lstImages.FullRowSelect = true;
            this.lstImages.HideSelection = false;
            this.lstImages.LabelWrap = false;
            this.lstImages.Location = new System.Drawing.Point(401, 69);
            this.lstImages.Name = "lstImages";
            this.lstImages.Size = new System.Drawing.Size(280, 316);
            this.lstImages.TabIndex = 5;
            this.lstImages.UseCompatibleStateImageBehavior = false;
            this.lstImages.View = System.Windows.Forms.View.Details;
            this.lstImages.ColumnClick += new System.Windows.Forms.ColumnClickEventHandler(this.lstImages_ColumnClick);
            this.lstImages.ItemSelectionChanged += new System.Windows.Forms.ListViewItemSelectionChangedEventHandler(this.lstImages_ItemSelectionChanged);
            this.lstImages.SelectedIndexChanged += new System.EventHandler(this.lstImages_SelectedIndexChanged);
            // 
            // udImages
            // 
            this.udImages.Increment = -1;
            this.udImages.Location = new System.Drawing.Point(359, 191);
            this.udImages.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.udImages.Max = 0;
            this.udImages.Min = 0;
            this.udImages.Name = "udImages";
            this.udImages.Size = new System.Drawing.Size(20, 64);
            this.udImages.TabIndex = 2;
            this.udImages.Value = 0;
            this.udImages.Wrap = true;
            this.udImages.UpClick += new System.Action(this.udImages_Click);
            this.udImages.DownClick += new System.Action(this.udImages_Click);
            // 
            // pictCurrentImage
            // 
            this.pictCurrentImage.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.pictCurrentImage.Location = new System.Drawing.Point(21, 43);
            this.pictCurrentImage.Name = "pictCurrentImage";
            this.pictCurrentImage.Size = new System.Drawing.Size(316, 236);
            this.pictCurrentImage.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.pictCurrentImage.TabIndex = 1;
            this.pictCurrentImage.TabStop = false;
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(702, 507);
            this.Controls.Add(this.statFEPC);
            this.Controls.Add(this.grpTestType);
            this.Controls.Add(this.btnOutputFolder);
            this.Controls.Add(this.lblOutputFolder);
            this.Controls.Add(this.txtOutputFolder);
            this.Controls.Add(this.lblClasses);
            this.Controls.Add(this.cboClasses);
            this.Controls.Add(this.btnRunTest);
            this.Controls.Add(this.btnAbortTest);
            this.Controls.Add(this.btnDelete);
            this.Controls.Add(this.btnAddFiles);
            this.Controls.Add(this.btnClassification);
            this.Controls.Add(this.btnFeatures);
            this.Controls.Add(this.grpView);
            this.Controls.Add(this.lstImages);
            this.Controls.Add(this.btnInvert);
            this.Controls.Add(this.btnRandomize);
            this.Controls.Add(this.udImages);
            this.Controls.Add(this.pictCurrentImage);
            this.Controls.Add(this.mnuFEPC);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MainMenuStrip = this.mnuFEPC;
            this.MaximizeBox = false;
            this.Name = "MainForm";
            this.SizeGripStyle = System.Windows.Forms.SizeGripStyle.Hide;
            this.Text = "Feature Extraction and Pattern Classification Test";
            this.mnuFEPC.ResumeLayout(false);
            this.mnuFEPC.PerformLayout();
            this.grpView.ResumeLayout(false);
            this.grpView.PerformLayout();
            this.grpTestType.ResumeLayout(false);
            this.pnlSingleCombinatoric.ResumeLayout(false);
            this.pnlSingleCombinatoric.PerformLayout();
            this.pnlTestTrainingLeave1Out.ResumeLayout(false);
            this.pnlTestTrainingLeave1Out.PerformLayout();
            this.statFEPC.ResumeLayout(false);
            this.statFEPC.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictCurrentImage)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.MenuStrip mnuFEPC;
        private System.Windows.Forms.ToolStripMenuItem mnuFile;
        private System.Windows.Forms.ToolStripMenuItem mnuFileLoadConfig;
        private System.Windows.Forms.ToolStripMenuItem mnuFileSaveConfig;
        private System.Windows.Forms.ToolStripSeparator mnuFileSeparator;
        private System.Windows.Forms.ToolStripMenuItem mnuFileExit;
        private System.Windows.Forms.ToolStripMenuItem mnuSettings;
        private System.Windows.Forms.ToolStripMenuItem mnuSettingsClasses;
        private System.Windows.Forms.ToolStripMenuItem mnuSettingsClassification;
        private System.Windows.Forms.ToolStripMenuItem mnuSettingsFeatures;
        private CustomControls.FepcPictureBox pictCurrentImage;
        private CustomControls.UpDown udImages;
        private System.Windows.Forms.Button btnRandomize;
        private System.Windows.Forms.Button btnInvert;
        private CustomControls.FepcListView lstImages;
        private System.Windows.Forms.GroupBox grpView;
        private System.Windows.Forms.RadioButton rbViewMasked;
        private System.Windows.Forms.RadioButton rbViewMask;
        private System.Windows.Forms.RadioButton rbViewOriginal;
        private System.Windows.Forms.Button btnFeatures;
        private System.Windows.Forms.Button btnClassification;
        private System.Windows.Forms.Button btnAddFiles;
        private System.Windows.Forms.Button btnDelete;
        private System.Windows.Forms.Button btnAbortTest;
        private System.Windows.Forms.Button btnRunTest;
        private System.Windows.Forms.ComboBox cboClasses;
        private System.Windows.Forms.Label lblClasses;
        private System.Windows.Forms.LinkLabel txtOutputFolder;
        private System.Windows.Forms.Label lblOutputFolder;
        private System.Windows.Forms.Button btnOutputFolder;
        private System.Windows.Forms.GroupBox grpTestType;
        private System.Windows.Forms.Panel pnlSingleCombinatoric;
        private System.Windows.Forms.RadioButton rbCombinatoric;
        private System.Windows.Forms.RadioButton rbSingle;
        private System.Windows.Forms.Panel pnlTestTrainingLeave1Out;
        private System.Windows.Forms.RadioButton rbLeave1Out;
        private System.Windows.Forms.RadioButton rbTestTraining;
        private System.Windows.Forms.StatusStrip statFEPC;
        private System.Windows.Forms.ToolStripStatusLabel lblStatus;
        private System.Windows.Forms.ToolStripProgressBar pbStatus;
        private System.Windows.Forms.OpenFileDialog dlgAddFiles;
        private System.Windows.Forms.ToolStripMenuItem toolStripMenuItem1;
        private System.Windows.Forms.ToolStripMenuItem contentsToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem aboutFEPCToolStripMenuItem;
        private System.Windows.Forms.OpenFileDialog dlgAddFilesLaw;
    }
}
