/***************************************************************************
* =========================================================================
*
*			 CVIPATAT - Dr. Scott Umbaugh SIUE
* 
* =========================================================================
*
*              File Name: CompareForm.cs 
*            Description: Used to compare images.
*    Initial Coding Date: June 6, 2006
*Last Modification Made: June 23, 2010
*  Programming Language: Visual Studio C#.NET 2008 
*             Credit(s): Wenjun(Evan) Bian, Pelin Guvenc
*                        Southern Illinois University at Edwardsville
*
*		  Copyright (c): 2010-2011 SIUE - Scott Umbaugh
****************************************************************************/


namespace CVIP_ATAT
{
    partial class CVIPATATForm
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
            this.tabProject = new System.Windows.Forms.TabControl();
            this.tabImages = new System.Windows.Forms.TabPage();
            this.gbInputImage = new System.Windows.Forms.GroupBox();
            this.bt_AddFolder = new System.Windows.Forms.Button();
            this.btAddIdealImage = new System.Windows.Forms.Button();
            this.tbImageCount = new System.Windows.Forms.TextBox();
            this.gblImage = new System.Windows.Forms.GroupBox();
            this.btDelAllIdealImage = new System.Windows.Forms.Button();
            this.lvImage = new System.Windows.Forms.ListView();
            this.columnImageName = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.columnImagePath = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.columnIdeaImageName = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.columnIdeaImagePath = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.btDelSelectedIdImage = new System.Windows.Forms.Button();
            this.btDeleteSelectedImage = new System.Windows.Forms.Button();
            this.btDeleteAllImage = new System.Windows.Forms.Button();
            this.btAddImage = new System.Windows.Forms.Button();
            this.lableTotalImage = new System.Windows.Forms.Label();
            this.tabProcesses = new System.Windows.Forms.TabPage();
            this.gbProcesses = new System.Windows.Forms.GroupBox();
            this.bt_IncreaseStage = new System.Windows.Forms.Button();
            this.bt_DecreaseStage = new System.Windows.Forms.Button();
            this.btDeleteCheckedProcess = new System.Windows.Forms.Button();
            this.btDown = new System.Windows.Forms.Button();
            this.btUp = new System.Windows.Forms.Button();
            this.tbTotalOptionsImage = new System.Windows.Forms.TextBox();
            this.labeltotalOptions = new System.Windows.Forms.Label();
            this.btDeleteAllProcesses = new System.Windows.Forms.Button();
            this.lvProcess = new System.Windows.Forms.ListView();
            this.columnStage = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.columnOption = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.columnProcess = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.columnP1 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.columnP2 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.columnP3 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.gbSetupProcess = new System.Windows.Forms.GroupBox();
            this.cbBoxSelectStage = new System.Windows.Forms.ComboBox();
            this.lbSelectStage = new System.Windows.Forms.Label();
            this.labelParameter33 = new System.Windows.Forms.Label();
            this.labelParameter23 = new System.Windows.Forms.Label();
            this.labelParameter13 = new System.Windows.Forms.Label();
            this.btAddProcess = new System.Windows.Forms.Button();
            this.labelParameter32 = new System.Windows.Forms.Label();
            this.labelParameter22 = new System.Windows.Forms.Label();
            this.labelParameter12 = new System.Windows.Forms.Label();
            this.labelParameter31 = new System.Windows.Forms.Label();
            this.tbParameter33 = new System.Windows.Forms.TextBox();
            this.tbParameter32 = new System.Windows.Forms.TextBox();
            this.tbParameter31 = new System.Windows.Forms.TextBox();
            this.labelParameter21 = new System.Windows.Forms.Label();
            this.tbParameter23 = new System.Windows.Forms.TextBox();
            this.tbParameter22 = new System.Windows.Forms.TextBox();
            this.tbParameter21 = new System.Windows.Forms.TextBox();
            this.labelParameter11 = new System.Windows.Forms.Label();
            this.tbParameter13 = new System.Windows.Forms.TextBox();
            this.tbParameter12 = new System.Windows.Forms.TextBox();
            this.tbParameter11 = new System.Windows.Forms.TextBox();
            this.labelSelectProcess = new System.Windows.Forms.Label();
            this.cbBoxSeclectProcess = new System.Windows.Forms.ComboBox();
            this.tabTest = new System.Windows.Forms.TabPage();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.btnAddCTable = new System.Windows.Forms.Button();
            this.bt_Alg = new System.Windows.Forms.Button();
            this.tbAlg = new System.Windows.Forms.TextBox();
            this.lblAlg = new System.Windows.Forms.Label();
            this.bt_IdealDir = new System.Windows.Forms.Button();
            this.bt_TestDir = new System.Windows.Forms.Button();
            this.tb_IdealDir = new System.Windows.Forms.TextBox();
            this.tb_TestDir = new System.Windows.Forms.TextBox();
            this.lb_IdealDir = new System.Windows.Forms.Label();
            this.lb_TestDir = new System.Windows.Forms.Label();
            this.rb_Compare = new System.Windows.Forms.RadioButton();
            this.rb_Test = new System.Windows.Forms.RadioButton();
            this.rb_FullTest = new System.Windows.Forms.RadioButton();
            this.resultLink = new System.Windows.Forms.LinkLabel();
            this.gbCompare = new System.Windows.Forms.GroupBox();
            this.cbSelectAll = new System.Windows.Forms.CheckBox();
            this.errorGroup = new System.Windows.Forms.GroupBox();
            this.tb_RMSR = new System.Windows.Forms.TextBox();
            this.tb_RMSG = new System.Windows.Forms.TextBox();
            this.tb_RMSB = new System.Windows.Forms.TextBox();
            this.tb_SNRB = new System.Windows.Forms.TextBox();
            this.tb_SNRR = new System.Windows.Forms.TextBox();
            this.tb_SNRG = new System.Windows.Forms.TextBox();
            this.cb_SNR = new System.Windows.Forms.CheckBox();
            this.cb_RMS = new System.Windows.Forms.CheckBox();
            this.CompareRGBLabel = new System.Windows.Forms.Label();
            this.diffGroup = new System.Windows.Forms.GroupBox();
            this.tb_SUBR = new System.Windows.Forms.TextBox();
            this.tb_SUBG = new System.Windows.Forms.TextBox();
            this.tb_SUBB = new System.Windows.Forms.TextBox();
            this.cb_SubtractEnergy = new System.Windows.Forms.CheckBox();
            this.shapeGroup = new System.Windows.Forms.GroupBox();
            this.tb_Thresh = new System.Windows.Forms.TextBox();
            this.tb_DICEG = new System.Windows.Forms.TextBox();
            this.tb_JaccG = new System.Windows.Forms.TextBox();
            this.tb_OverG = new System.Windows.Forms.TextBox();
            this.tb_OverB = new System.Windows.Forms.TextBox();
            this.tb_OverR = new System.Windows.Forms.TextBox();
            this.tb_JaccR = new System.Windows.Forms.TextBox();
            this.tb_DICER = new System.Windows.Forms.TextBox();
            this.lb_Thresh = new System.Windows.Forms.Label();
            this.tb_XORG = new System.Windows.Forms.TextBox();
            this.tb_JaccB = new System.Windows.Forms.TextBox();
            this.tb_XORB = new System.Windows.Forms.TextBox();
            this.tb_DICEB = new System.Windows.Forms.TextBox();
            this.cb_XOR = new System.Windows.Forms.CheckBox();
            this.cb_DICE = new System.Windows.Forms.CheckBox();
            this.cb_Jaccard = new System.Windows.Forms.CheckBox();
            this.cb_Over = new System.Windows.Forms.CheckBox();
            this.tb_XORR = new System.Windows.Forms.TextBox();
            this.averageGroup = new System.Windows.Forms.GroupBox();
            this.cb_StdDev = new System.Windows.Forms.CheckBox();
            this.cb_Average = new System.Windows.Forms.CheckBox();
            this.btDeleteAllTest = new System.Windows.Forms.Button();
            this.btDeleteCheckedTest = new System.Windows.Forms.Button();
            this.gbTestResult = new System.Windows.Forms.GroupBox();
            this.labelHelp = new System.Windows.Forms.Label();
            this.lvTestResult = new System.Windows.Forms.ListView();
            this.columnStageOption = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.columnAlgorithm = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.columnTRlImageName = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.columnTRImagePath = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.columnTRIdealImageName = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.columnTRIdealImagePath = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.columnTROriginalImage = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.gbRun = new System.Windows.Forms.GroupBox();
            this.TestTypeLabel = new System.Windows.Forms.Label();
            this.pBarTest = new System.Windows.Forms.ProgressBar();
            this.tbFOption = new System.Windows.Forms.TextBox();
            this.tbTOption = new System.Windows.Forms.TextBox();
            this.labelFOption = new System.Windows.Forms.Label();
            this.labelTOption = new System.Windows.Forms.Label();
            this.labelShowProgress = new System.Windows.Forms.Label();
            this.btTestRun = new System.Windows.Forms.Button();
            this.btRunStop = new System.Windows.Forms.Button();
            this.btRunPause = new System.Windows.Forms.Button();
            this.Empty3 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.AddImage = new System.Windows.Forms.OpenFileDialog();
            this.toolTiplvTestResult = new System.Windows.Forms.ToolTip(this.components);
            this.folderBrowser = new System.Windows.Forms.FolderBrowserDialog();
            this.fileBrowser = new System.Windows.Forms.OpenFileDialog();
            this.abortTimer = new System.Windows.Forms.Timer(this.components);
            this.tabProject.SuspendLayout();
            this.tabImages.SuspendLayout();
            this.gbInputImage.SuspendLayout();
            this.gblImage.SuspendLayout();
            this.tabProcesses.SuspendLayout();
            this.gbProcesses.SuspendLayout();
            this.gbSetupProcess.SuspendLayout();
            this.tabTest.SuspendLayout();
            this.groupBox1.SuspendLayout();
            this.gbCompare.SuspendLayout();
            this.errorGroup.SuspendLayout();
            this.diffGroup.SuspendLayout();
            this.shapeGroup.SuspendLayout();
            this.averageGroup.SuspendLayout();
            this.gbTestResult.SuspendLayout();
            this.gbRun.SuspendLayout();
            this.SuspendLayout();
            // 
            // tabProject
            // 
            this.tabProject.Controls.Add(this.tabImages);
            this.tabProject.Controls.Add(this.tabProcesses);
            this.tabProject.Controls.Add(this.tabTest);
            this.tabProject.Location = new System.Drawing.Point(3, -1);
            this.tabProject.Name = "tabProject";
            this.tabProject.SelectedIndex = 0;
            this.tabProject.Size = new System.Drawing.Size(870, 655);
            this.tabProject.TabIndex = 0;
            // 
            // tabImages
            // 
            this.tabImages.Controls.Add(this.gbInputImage);
            this.tabImages.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.tabImages.Location = new System.Drawing.Point(4, 22);
            this.tabImages.Name = "tabImages";
            this.tabImages.Padding = new System.Windows.Forms.Padding(3);
            this.tabImages.Size = new System.Drawing.Size(862, 629);
            this.tabImages.TabIndex = 0;
            this.tabImages.Text = "Images";
            this.tabImages.UseVisualStyleBackColor = true;
            // 
            // gbInputImage
            // 
            this.gbInputImage.Controls.Add(this.bt_AddFolder);
            this.gbInputImage.Controls.Add(this.btAddIdealImage);
            this.gbInputImage.Controls.Add(this.tbImageCount);
            this.gbInputImage.Controls.Add(this.gblImage);
            this.gbInputImage.Controls.Add(this.btAddImage);
            this.gbInputImage.Controls.Add(this.lableTotalImage);
            this.gbInputImage.Location = new System.Drawing.Point(6, 6);
            this.gbInputImage.Name = "gbInputImage";
            this.gbInputImage.Size = new System.Drawing.Size(846, 617);
            this.gbInputImage.TabIndex = 1;
            this.gbInputImage.TabStop = false;
            this.gbInputImage.Text = "Input Images";
            // 
            // bt_AddFolder
            // 
            this.bt_AddFolder.Location = new System.Drawing.Point(443, 15);
            this.bt_AddFolder.Name = "bt_AddFolder";
            this.bt_AddFolder.Size = new System.Drawing.Size(110, 28);
            this.bt_AddFolder.TabIndex = 11;
            this.bt_AddFolder.Text = "Add Batch Folder";
            this.bt_AddFolder.UseVisualStyleBackColor = true;
            this.bt_AddFolder.Click += new System.EventHandler(this.bt_AddFolder_Click);
            // 
            // btAddIdealImage
            // 
            this.btAddIdealImage.Location = new System.Drawing.Point(277, 15);
            this.btAddIdealImage.Name = "btAddIdealImage";
            this.btAddIdealImage.Size = new System.Drawing.Size(110, 28);
            this.btAddIdealImage.TabIndex = 10;
            this.btAddIdealImage.Text = "Add Ideal Image";
            this.btAddIdealImage.UseVisualStyleBackColor = true;
            this.btAddIdealImage.Click += new System.EventHandler(this.btAddIdealImage_Click);
            // 
            // tbImageCount
            // 
            this.tbImageCount.BackColor = System.Drawing.SystemColors.Control;
            this.tbImageCount.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.tbImageCount.Location = new System.Drawing.Point(707, 22);
            this.tbImageCount.Name = "tbImageCount";
            this.tbImageCount.ReadOnly = true;
            this.tbImageCount.Size = new System.Drawing.Size(60, 20);
            this.tbImageCount.TabIndex = 9;
            this.tbImageCount.Text = "0";
            this.tbImageCount.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            // 
            // gblImage
            // 
            this.gblImage.Controls.Add(this.btDelAllIdealImage);
            this.gblImage.Controls.Add(this.lvImage);
            this.gblImage.Controls.Add(this.btDelSelectedIdImage);
            this.gblImage.Controls.Add(this.btDeleteSelectedImage);
            this.gblImage.Controls.Add(this.btDeleteAllImage);
            this.gblImage.Location = new System.Drawing.Point(6, 48);
            this.gblImage.Name = "gblImage";
            this.gblImage.Size = new System.Drawing.Size(832, 563);
            this.gblImage.TabIndex = 7;
            this.gblImage.TabStop = false;
            this.gblImage.Text = "Images";
            // 
            // btDelAllIdealImage
            // 
            this.btDelAllIdealImage.Font = new System.Drawing.Font("Arial", 6.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btDelAllIdealImage.Location = new System.Drawing.Point(626, 15);
            this.btDelAllIdealImage.Name = "btDelAllIdealImage";
            this.btDelAllIdealImage.Size = new System.Drawing.Size(135, 25);
            this.btDelAllIdealImage.TabIndex = 11;
            this.btDelAllIdealImage.Text = "Delete ALL Ideal Images";
            this.btDelAllIdealImage.UseVisualStyleBackColor = true;
            this.btDelAllIdealImage.Click += new System.EventHandler(this.btDelAllIdealImage_Click);
            // 
            // lvImage
            // 
            this.lvImage.Alignment = System.Windows.Forms.ListViewAlignment.Default;
            this.lvImage.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.columnImageName,
            this.columnImagePath,
            this.columnIdeaImageName,
            this.columnIdeaImagePath});
            this.lvImage.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lvImage.FullRowSelect = true;
            this.lvImage.GridLines = true;
            this.lvImage.HeaderStyle = System.Windows.Forms.ColumnHeaderStyle.Nonclickable;
            this.lvImage.HideSelection = false;
            this.lvImage.Location = new System.Drawing.Point(6, 46);
            this.lvImage.Name = "lvImage";
            this.lvImage.ShowItemToolTips = true;
            this.lvImage.Size = new System.Drawing.Size(820, 510);
            this.lvImage.TabIndex = 2;
            this.lvImage.UseCompatibleStateImageBehavior = false;
            this.lvImage.View = System.Windows.Forms.View.Details;
            this.lvImage.MouseDoubleClick += new System.Windows.Forms.MouseEventHandler(this.listView_MouseDoubleClick);
            // 
            // columnImageName
            // 
            this.columnImageName.Text = "ImageName";
            this.columnImageName.Width = 175;
            // 
            // columnImagePath
            // 
            this.columnImagePath.Text = "ImagePath";
            this.columnImagePath.Width = 175;
            // 
            // columnIdeaImageName
            // 
            this.columnIdeaImageName.Text = "IdeaImageName";
            this.columnIdeaImageName.Width = 175;
            // 
            // columnIdeaImagePath
            // 
            this.columnIdeaImagePath.Text = "IdeaImagePath";
            this.columnIdeaImagePath.Width = 175;
            // 
            // btDelSelectedIdImage
            // 
            this.btDelSelectedIdImage.Font = new System.Drawing.Font("Arial", 6.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btDelSelectedIdImage.Location = new System.Drawing.Point(437, 15);
            this.btDelSelectedIdImage.Name = "btDelSelectedIdImage";
            this.btDelSelectedIdImage.Size = new System.Drawing.Size(135, 25);
            this.btDelSelectedIdImage.TabIndex = 11;
            this.btDelSelectedIdImage.Text = "Delete Selected Ideal Image";
            this.btDelSelectedIdImage.UseVisualStyleBackColor = true;
            this.btDelSelectedIdImage.Click += new System.EventHandler(this.btDelSelectedIdImage_Click);
            // 
            // btDeleteSelectedImage
            // 
            this.btDeleteSelectedImage.Font = new System.Drawing.Font("Arial", 6.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btDeleteSelectedImage.Location = new System.Drawing.Point(91, 15);
            this.btDeleteSelectedImage.Name = "btDeleteSelectedImage";
            this.btDeleteSelectedImage.Size = new System.Drawing.Size(135, 25);
            this.btDeleteSelectedImage.TabIndex = 3;
            this.btDeleteSelectedImage.Text = "Delete Selected Image";
            this.btDeleteSelectedImage.UseVisualStyleBackColor = true;
            this.btDeleteSelectedImage.Click += new System.EventHandler(this.btDeleteSelectedImage_Click);
            // 
            // btDeleteAllImage
            // 
            this.btDeleteAllImage.Font = new System.Drawing.Font("Arial", 6.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btDeleteAllImage.Location = new System.Drawing.Point(261, 15);
            this.btDeleteAllImage.Name = "btDeleteAllImage";
            this.btDeleteAllImage.Size = new System.Drawing.Size(135, 25);
            this.btDeleteAllImage.TabIndex = 4;
            this.btDeleteAllImage.Text = "Delete ALL Images";
            this.btDeleteAllImage.UseVisualStyleBackColor = true;
            this.btDeleteAllImage.Click += new System.EventHandler(this.btDeleteAllImage_Click);
            // 
            // btAddImage
            // 
            this.btAddImage.Location = new System.Drawing.Point(111, 15);
            this.btAddImage.Name = "btAddImage";
            this.btAddImage.Size = new System.Drawing.Size(110, 28);
            this.btAddImage.TabIndex = 2;
            this.btAddImage.Text = "Add Image";
            this.btAddImage.UseVisualStyleBackColor = true;
            this.btAddImage.Click += new System.EventHandler(this.btAddImage_Click);
            // 
            // lableTotalImage
            // 
            this.lableTotalImage.AutoSize = true;
            this.lableTotalImage.Location = new System.Drawing.Point(613, 23);
            this.lableTotalImage.Name = "lableTotalImage";
            this.lableTotalImage.Size = new System.Drawing.Size(81, 15);
            this.lableTotalImage.TabIndex = 8;
            this.lableTotalImage.Text = "Total Images:";
            // 
            // tabProcesses
            // 
            this.tabProcesses.Controls.Add(this.gbProcesses);
            this.tabProcesses.Controls.Add(this.gbSetupProcess);
            this.tabProcesses.Location = new System.Drawing.Point(4, 22);
            this.tabProcesses.Name = "tabProcesses";
            this.tabProcesses.Padding = new System.Windows.Forms.Padding(3);
            this.tabProcesses.Size = new System.Drawing.Size(862, 629);
            this.tabProcesses.TabIndex = 1;
            this.tabProcesses.Text = "Processes";
            this.tabProcesses.UseVisualStyleBackColor = true;
            this.tabProcesses.Enter += new System.EventHandler(this.tabProcesses_Enter);
            // 
            // gbProcesses
            // 
            this.gbProcesses.Controls.Add(this.bt_IncreaseStage);
            this.gbProcesses.Controls.Add(this.bt_DecreaseStage);
            this.gbProcesses.Controls.Add(this.btDeleteCheckedProcess);
            this.gbProcesses.Controls.Add(this.btDown);
            this.gbProcesses.Controls.Add(this.btUp);
            this.gbProcesses.Controls.Add(this.tbTotalOptionsImage);
            this.gbProcesses.Controls.Add(this.labeltotalOptions);
            this.gbProcesses.Controls.Add(this.btDeleteAllProcesses);
            this.gbProcesses.Controls.Add(this.lvProcess);
            this.gbProcesses.Location = new System.Drawing.Point(8, 184);
            this.gbProcesses.Name = "gbProcesses";
            this.gbProcesses.Size = new System.Drawing.Size(844, 432);
            this.gbProcesses.TabIndex = 8;
            this.gbProcesses.TabStop = false;
            this.gbProcesses.Text = "Processes";
            // 
            // bt_IncreaseStage
            // 
            this.bt_IncreaseStage.Font = new System.Drawing.Font("Microsoft Sans Serif", 6.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.bt_IncreaseStage.Location = new System.Drawing.Point(288, 395);
            this.bt_IncreaseStage.Name = "bt_IncreaseStage";
            this.bt_IncreaseStage.Size = new System.Drawing.Size(99, 25);
            this.bt_IncreaseStage.TabIndex = 12;
            this.bt_IncreaseStage.Text = "Increase Stage";
            this.bt_IncreaseStage.UseVisualStyleBackColor = true;
            this.bt_IncreaseStage.Click += new System.EventHandler(this.bt_IncreaseStage_Click);
            // 
            // bt_DecreaseStage
            // 
            this.bt_DecreaseStage.Font = new System.Drawing.Font("Microsoft Sans Serif", 6.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.bt_DecreaseStage.Location = new System.Drawing.Point(185, 395);
            this.bt_DecreaseStage.Name = "bt_DecreaseStage";
            this.bt_DecreaseStage.Size = new System.Drawing.Size(97, 25);
            this.bt_DecreaseStage.TabIndex = 11;
            this.bt_DecreaseStage.Text = "Decrease Stage";
            this.bt_DecreaseStage.UseVisualStyleBackColor = true;
            this.bt_DecreaseStage.Click += new System.EventHandler(this.bt_DecreaseStage_Click);
            // 
            // btDeleteCheckedProcess
            // 
            this.btDeleteCheckedProcess.Location = new System.Drawing.Point(538, 395);
            this.btDeleteCheckedProcess.Name = "btDeleteCheckedProcess";
            this.btDeleteCheckedProcess.Size = new System.Drawing.Size(149, 25);
            this.btDeleteCheckedProcess.TabIndex = 10;
            this.btDeleteCheckedProcess.Text = "Delete Checked Process";
            this.btDeleteCheckedProcess.UseVisualStyleBackColor = true;
            this.btDeleteCheckedProcess.Click += new System.EventHandler(this.btDeleteCheckedProcess_Click_1);
            // 
            // btDown
            // 
            this.btDown.Font = new System.Drawing.Font("Microsoft Sans Serif", 6.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btDown.Location = new System.Drawing.Point(441, 395);
            this.btDown.Name = "btDown";
            this.btDown.Size = new System.Drawing.Size(42, 25);
            this.btDown.TabIndex = 7;
            this.btDown.Text = "Down";
            this.btDown.UseVisualStyleBackColor = true;
            this.btDown.Click += new System.EventHandler(this.btDown_Click);
            // 
            // btUp
            // 
            this.btUp.Font = new System.Drawing.Font("Microsoft Sans Serif", 6.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btUp.Location = new System.Drawing.Point(393, 395);
            this.btUp.Name = "btUp";
            this.btUp.Size = new System.Drawing.Size(42, 25);
            this.btUp.TabIndex = 6;
            this.btUp.Text = "Up";
            this.btUp.UseVisualStyleBackColor = true;
            this.btUp.Click += new System.EventHandler(this.btUp_Click);
            // 
            // tbTotalOptionsImage
            // 
            this.tbTotalOptionsImage.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.tbTotalOptionsImage.Location = new System.Drawing.Point(90, 397);
            this.tbTotalOptionsImage.Name = "tbTotalOptionsImage";
            this.tbTotalOptionsImage.ReadOnly = true;
            this.tbTotalOptionsImage.Size = new System.Drawing.Size(42, 20);
            this.tbTotalOptionsImage.TabIndex = 5;
            this.tbTotalOptionsImage.Text = "0";
            this.tbTotalOptionsImage.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            // 
            // labeltotalOptions
            // 
            this.labeltotalOptions.Location = new System.Drawing.Point(6, 400);
            this.labeltotalOptions.Name = "labeltotalOptions";
            this.labeltotalOptions.Size = new System.Drawing.Size(110, 27);
            this.labeltotalOptions.TabIndex = 4;
            this.labeltotalOptions.Text = "Total Algorithms:";
            // 
            // btDeleteAllProcesses
            // 
            this.btDeleteAllProcesses.Location = new System.Drawing.Point(693, 395);
            this.btDeleteAllProcesses.Name = "btDeleteAllProcesses";
            this.btDeleteAllProcesses.Size = new System.Drawing.Size(120, 25);
            this.btDeleteAllProcesses.TabIndex = 3;
            this.btDeleteAllProcesses.Text = "Delete All Processes";
            this.btDeleteAllProcesses.UseVisualStyleBackColor = true;
            this.btDeleteAllProcesses.Click += new System.EventHandler(this.btDeleteAllProcesses_Click);
            // 
            // lvProcess
            // 
            this.lvProcess.AutoArrange = false;
            this.lvProcess.CheckBoxes = true;
            this.lvProcess.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.columnStage,
            this.columnOption,
            this.columnProcess,
            this.columnP1,
            this.columnP2,
            this.columnP3});
            this.lvProcess.FullRowSelect = true;
            this.lvProcess.GridLines = true;
            this.lvProcess.HideSelection = false;
            this.lvProcess.Location = new System.Drawing.Point(33, 19);
            this.lvProcess.MultiSelect = false;
            this.lvProcess.Name = "lvProcess";
            this.lvProcess.ShowItemToolTips = true;
            this.lvProcess.Size = new System.Drawing.Size(780, 367);
            this.lvProcess.Sorting = System.Windows.Forms.SortOrder.Ascending;
            this.lvProcess.TabIndex = 1;
            this.lvProcess.UseCompatibleStateImageBehavior = false;
            this.lvProcess.View = System.Windows.Forms.View.Details;
            // 
            // columnStage
            // 
            this.columnStage.Text = "Stage";
            this.columnStage.Width = 47;
            // 
            // columnOption
            // 
            this.columnOption.Text = "Option";
            this.columnOption.Width = 50;
            // 
            // columnProcess
            // 
            this.columnProcess.Text = "Process";
            this.columnProcess.Width = 470;
            // 
            // columnP1
            // 
            this.columnP1.Text = "P1";
            this.columnP1.Width = 70;
            // 
            // columnP2
            // 
            this.columnP2.Text = "P2";
            this.columnP2.Width = 70;
            // 
            // columnP3
            // 
            this.columnP3.Text = "P3";
            this.columnP3.Width = 70;
            // 
            // gbSetupProcess
            // 
            this.gbSetupProcess.Controls.Add(this.cbBoxSelectStage);
            this.gbSetupProcess.Controls.Add(this.lbSelectStage);
            this.gbSetupProcess.Controls.Add(this.labelParameter33);
            this.gbSetupProcess.Controls.Add(this.labelParameter23);
            this.gbSetupProcess.Controls.Add(this.labelParameter13);
            this.gbSetupProcess.Controls.Add(this.btAddProcess);
            this.gbSetupProcess.Controls.Add(this.labelParameter32);
            this.gbSetupProcess.Controls.Add(this.labelParameter22);
            this.gbSetupProcess.Controls.Add(this.labelParameter12);
            this.gbSetupProcess.Controls.Add(this.labelParameter31);
            this.gbSetupProcess.Controls.Add(this.tbParameter33);
            this.gbSetupProcess.Controls.Add(this.tbParameter32);
            this.gbSetupProcess.Controls.Add(this.tbParameter31);
            this.gbSetupProcess.Controls.Add(this.labelParameter21);
            this.gbSetupProcess.Controls.Add(this.tbParameter23);
            this.gbSetupProcess.Controls.Add(this.tbParameter22);
            this.gbSetupProcess.Controls.Add(this.tbParameter21);
            this.gbSetupProcess.Controls.Add(this.labelParameter11);
            this.gbSetupProcess.Controls.Add(this.tbParameter13);
            this.gbSetupProcess.Controls.Add(this.tbParameter12);
            this.gbSetupProcess.Controls.Add(this.tbParameter11);
            this.gbSetupProcess.Controls.Add(this.labelSelectProcess);
            this.gbSetupProcess.Controls.Add(this.cbBoxSeclectProcess);
            this.gbSetupProcess.Location = new System.Drawing.Point(8, 9);
            this.gbSetupProcess.Name = "gbSetupProcess";
            this.gbSetupProcess.Size = new System.Drawing.Size(844, 164);
            this.gbSetupProcess.TabIndex = 0;
            this.gbSetupProcess.TabStop = false;
            this.gbSetupProcess.Text = "Setup Process";
            // 
            // cbBoxSelectStage
            // 
            this.cbBoxSelectStage.DropDownHeight = 150;
            this.cbBoxSelectStage.FormattingEnabled = true;
            this.cbBoxSelectStage.IntegralHeight = false;
            this.cbBoxSelectStage.Items.AddRange(new object[] {
            "1",
            "2",
            "3",
            "4",
            "5",
            "6",
            "7",
            "8",
            "9",
            "10"});
            this.cbBoxSelectStage.Location = new System.Drawing.Point(419, 42);
            this.cbBoxSelectStage.Name = "cbBoxSelectStage";
            this.cbBoxSelectStage.Size = new System.Drawing.Size(180, 21);
            this.cbBoxSelectStage.TabIndex = 20;
            this.cbBoxSelectStage.Text = "Select Stage Here";
            this.cbBoxSelectStage.SelectedIndexChanged += new System.EventHandler(this.cbBoxSelectStage_SelectedIndexChanged);
            this.cbBoxSelectStage.KeyUp += new System.Windows.Forms.KeyEventHandler(this.cbSelectStage_KeyUp);
            // 
            // lbSelectStage
            // 
            this.lbSelectStage.AutoSize = true;
            this.lbSelectStage.Location = new System.Drawing.Point(415, 26);
            this.lbSelectStage.Name = "lbSelectStage";
            this.lbSelectStage.Size = new System.Drawing.Size(68, 13);
            this.lbSelectStage.TabIndex = 19;
            this.lbSelectStage.Text = "Select Stage";
            // 
            // labelParameter33
            // 
            this.labelParameter33.Location = new System.Drawing.Point(628, 126);
            this.labelParameter33.Name = "labelParameter33";
            this.labelParameter33.Size = new System.Drawing.Size(185, 35);
            this.labelParameter33.TabIndex = 18;
            this.labelParameter33.Text = "Parameter Range        ";
            // 
            // labelParameter23
            // 
            this.labelParameter23.Location = new System.Drawing.Point(382, 126);
            this.labelParameter23.Name = "labelParameter23";
            this.labelParameter23.Size = new System.Drawing.Size(158, 35);
            this.labelParameter23.TabIndex = 18;
            this.labelParameter23.Text = "Parameter Range        ";
            // 
            // labelParameter13
            // 
            this.labelParameter13.Location = new System.Drawing.Point(136, 126);
            this.labelParameter13.Name = "labelParameter13";
            this.labelParameter13.Size = new System.Drawing.Size(215, 46);
            this.labelParameter13.TabIndex = 18;
            this.labelParameter13.Text = "         Parameter Range        ";
            // 
            // btAddProcess
            // 
            this.btAddProcess.Location = new System.Drawing.Point(644, 37);
            this.btAddProcess.Name = "btAddProcess";
            this.btAddProcess.Size = new System.Drawing.Size(100, 28);
            this.btAddProcess.TabIndex = 17;
            this.btAddProcess.Text = "Add Process";
            this.btAddProcess.UseVisualStyleBackColor = true;
            this.btAddProcess.Click += new System.EventHandler(this.btAddProcess_Click);
            // 
            // labelParameter32
            // 
            this.labelParameter32.AutoSize = true;
            this.labelParameter32.Location = new System.Drawing.Point(628, 87);
            this.labelParameter32.Name = "labelParameter32";
            this.labelParameter32.Size = new System.Drawing.Size(111, 13);
            this.labelParameter32.TabIndex = 16;
            this.labelParameter32.Text = "lower increment upper";
            // 
            // labelParameter22
            // 
            this.labelParameter22.AutoSize = true;
            this.labelParameter22.Location = new System.Drawing.Point(382, 87);
            this.labelParameter22.Name = "labelParameter22";
            this.labelParameter22.Size = new System.Drawing.Size(111, 13);
            this.labelParameter22.TabIndex = 16;
            this.labelParameter22.Text = "lower increment upper";
            // 
            // labelParameter12
            // 
            this.labelParameter12.AutoSize = true;
            this.labelParameter12.Location = new System.Drawing.Point(133, 87);
            this.labelParameter12.Name = "labelParameter12";
            this.labelParameter12.Size = new System.Drawing.Size(111, 13);
            this.labelParameter12.TabIndex = 16;
            this.labelParameter12.Text = "lower increment upper";
            // 
            // labelParameter31
            // 
            this.labelParameter31.Location = new System.Drawing.Point(546, 81);
            this.labelParameter31.Name = "labelParameter31";
            this.labelParameter31.Size = new System.Drawing.Size(80, 74);
            this.labelParameter31.TabIndex = 15;
            this.labelParameter31.Text = "\r\n\r\nParameter3:";
            // 
            // tbParameter33
            // 
            this.tbParameter33.Enabled = false;
            this.tbParameter33.Location = new System.Drawing.Point(704, 103);
            this.tbParameter33.Name = "tbParameter33";
            this.tbParameter33.Size = new System.Drawing.Size(40, 20);
            this.tbParameter33.TabIndex = 14;
            // 
            // tbParameter32
            // 
            this.tbParameter32.Enabled = false;
            this.tbParameter32.Location = new System.Drawing.Point(668, 103);
            this.tbParameter32.Name = "tbParameter32";
            this.tbParameter32.Size = new System.Drawing.Size(40, 20);
            this.tbParameter32.TabIndex = 12;
            // 
            // tbParameter31
            // 
            this.tbParameter31.Enabled = false;
            this.tbParameter31.Location = new System.Drawing.Point(631, 103);
            this.tbParameter31.Name = "tbParameter31";
            this.tbParameter31.Size = new System.Drawing.Size(40, 20);
            this.tbParameter31.TabIndex = 13;
            // 
            // labelParameter21
            // 
            this.labelParameter21.Location = new System.Drawing.Point(297, 80);
            this.labelParameter21.Name = "labelParameter21";
            this.labelParameter21.Size = new System.Drawing.Size(84, 74);
            this.labelParameter21.TabIndex = 11;
            this.labelParameter21.Text = "\r\n\r\nParameter2:";
            // 
            // tbParameter23
            // 
            this.tbParameter23.Enabled = false;
            this.tbParameter23.Location = new System.Drawing.Point(458, 103);
            this.tbParameter23.Name = "tbParameter23";
            this.tbParameter23.Size = new System.Drawing.Size(40, 20);
            this.tbParameter23.TabIndex = 10;
            // 
            // tbParameter22
            // 
            this.tbParameter22.Enabled = false;
            this.tbParameter22.Location = new System.Drawing.Point(422, 103);
            this.tbParameter22.Name = "tbParameter22";
            this.tbParameter22.Size = new System.Drawing.Size(40, 20);
            this.tbParameter22.TabIndex = 8;
            // 
            // tbParameter21
            // 
            this.tbParameter21.Enabled = false;
            this.tbParameter21.Location = new System.Drawing.Point(385, 103);
            this.tbParameter21.Name = "tbParameter21";
            this.tbParameter21.Size = new System.Drawing.Size(40, 20);
            this.tbParameter21.TabIndex = 9;
            // 
            // labelParameter11
            // 
            this.labelParameter11.Location = new System.Drawing.Point(52, 81);
            this.labelParameter11.Name = "labelParameter11";
            this.labelParameter11.Size = new System.Drawing.Size(80, 80);
            this.labelParameter11.TabIndex = 7;
            this.labelParameter11.Text = "\r\n\r\nParameter1:";
            // 
            // tbParameter13
            // 
            this.tbParameter13.Enabled = false;
            this.tbParameter13.Location = new System.Drawing.Point(209, 103);
            this.tbParameter13.Name = "tbParameter13";
            this.tbParameter13.Size = new System.Drawing.Size(40, 20);
            this.tbParameter13.TabIndex = 6;
            // 
            // tbParameter12
            // 
            this.tbParameter12.Enabled = false;
            this.tbParameter12.Location = new System.Drawing.Point(173, 103);
            this.tbParameter12.Name = "tbParameter12";
            this.tbParameter12.Size = new System.Drawing.Size(40, 20);
            this.tbParameter12.TabIndex = 6;
            // 
            // tbParameter11
            // 
            this.tbParameter11.Enabled = false;
            this.tbParameter11.Location = new System.Drawing.Point(136, 103);
            this.tbParameter11.Name = "tbParameter11";
            this.tbParameter11.Size = new System.Drawing.Size(40, 20);
            this.tbParameter11.TabIndex = 6;
            // 
            // labelSelectProcess
            // 
            this.labelSelectProcess.AutoSize = true;
            this.labelSelectProcess.Location = new System.Drawing.Point(60, 26);
            this.labelSelectProcess.Name = "labelSelectProcess";
            this.labelSelectProcess.Size = new System.Drawing.Size(78, 13);
            this.labelSelectProcess.TabIndex = 3;
            this.labelSelectProcess.Text = "Select Process";
            // 
            // cbBoxSeclectProcess
            // 
            this.cbBoxSeclectProcess.DropDownHeight = 500;
            this.cbBoxSeclectProcess.DropDownWidth = 200;
            this.cbBoxSeclectProcess.FormattingEnabled = true;
            this.cbBoxSeclectProcess.IntegralHeight = false;
            this.cbBoxSeclectProcess.Items.AddRange(new object[] {
            "ACE II",
            "Adaptive Median Filtering",
            "Alpha Filtering",
            "Anisotropic Diffusion Filter",
            "Auto Single Threshold",
            "Binary Thresholding",
            "Boie-Cox-Hysterisis",
            "Boie-Cox Edge Detection",
            "Canny Edge Detection",
            "Color-to-Gray Conversion - Average",
            "Color-to-Gray Conversion - Luminance",
            "Color Transformation (RGB->HSL,HSV,SCT,CCT,LUV,LAB,XYZ)",
            "Contra-Harmonic Filtering",
            "Contrast-Limited Adaptive Hist Eq",
            "Direct Cosine Transform",
            "Edge-Linking",
            "Edge Enhancement with Unsharp Masking",
            "Extract Band",
            "Fast Fourier Transform",
            "Fuzzyc Segmentation",
            "Gaussian Filter",
            "Geometric Filtering",
            "Gray Level Quantization",
            "Haar Transform",
            "Harmonic Filtering",
            "High Boost",
            "High Freq. Emphasis (DC=>Off)",
            "High Freq. Emphasis (DC=>On)",
            "Highpass Spatial Filter",
            "Histogram Equalization",
            "Histogram Slide",
            "Histogram Stretch",
            "Histogram Thresholding Segmentation",
            "Hough Transform",
            "HSL -> RGB Transform",
            "HSV -> RGB Transform",
            "Inverse Direct Cosine Transform",
            "Inverse Fast Fourier Transform",
            "Kuwahara Filter",
            "Label Image",
            "Laplacian Edge Detection",
            "Maximum Filtering",
            "Mean Filtering",
            "Median Cut Segmentation",
            "Median Filtering",
            "Midpoint Filtering",
            "MMSE Filtering",
            "Morphological Closing-Circle Filtering",
            "Morphological Closing-Cross Filtering",
            "Morphological Closing-Rectangle Filtering",
            "Morphological Closing-Square Filtering",
            "Morphological Dilation-Circle Filtering",
            "Morphological Dilation-Cross Filtering",
            "Morphological Dilation-Rectangle Filtering",
            "Morphological Dilation-Square Filtering",
            "Morphological Erosion-Circle Filtering",
            "Morphological Erosion-Cross Filtering",
            "Morphological Erosion-Rectangle Filtering",
            "Morphological Erosion-Square Filtering",
            "Morphological Opening-Circle Filtering",
            "Morphological Opening-Cross Filtering",
            "Morphological Opening-Rectangle Filtering",
            "Morphological Opening-Square Filtering",
            "MorphSkel 4-mask,And",
            "MorphSkel 4-mask,Sequential",
            "MorphSkel 8-mask,And",
            "MorphSkel 8-mask,Sequential",
            "Not",
            "Otsu Thresholding",
            "Parametric AD Filter",
            "PCT Median Segmentation",
            "PCT Transform",
            "Prewitt Edge Detection",
            "Roberts Edge Detection",
            "SCT Center Segmentation",
            "Sharpening AlgorithmI ( Mask II )",
            "Sharpening AlgorithmII",
            "Shen-Castan Edge Detection",
            "Skip/Null",
            "Sobel Edge Detection",
            "Spatial Quantization",
            "Threshold(remapped) Segmentation",
            "Unsharp Masking",
            "Walsh-Hadamard Transform",
            "Watershed Segmentation",
            "Yp-Mean Filtering"});
            this.cbBoxSeclectProcess.Location = new System.Drawing.Point(63, 42);
            this.cbBoxSeclectProcess.Name = "cbBoxSeclectProcess";
            this.cbBoxSeclectProcess.Size = new System.Drawing.Size(312, 21);
            this.cbBoxSeclectProcess.Sorted = true;
            this.cbBoxSeclectProcess.TabIndex = 2;
            this.cbBoxSeclectProcess.Text = "Select Process Here";
            this.cbBoxSeclectProcess.SelectedIndexChanged += new System.EventHandler(this.cbBoxSeclectProcess_SelectedIndexChanged);
            this.cbBoxSeclectProcess.KeyUp += new System.Windows.Forms.KeyEventHandler(this.cbBoxSeclectProcess_KeyUp);
            // 
            // tabTest
            // 
            this.tabTest.Controls.Add(this.groupBox1);
            this.tabTest.Controls.Add(this.gbCompare);
            this.tabTest.Controls.Add(this.btDeleteAllTest);
            this.tabTest.Controls.Add(this.btDeleteCheckedTest);
            this.tabTest.Controls.Add(this.gbTestResult);
            this.tabTest.Controls.Add(this.gbRun);
            this.tabTest.Location = new System.Drawing.Point(4, 22);
            this.tabTest.Name = "tabTest";
            this.tabTest.Size = new System.Drawing.Size(862, 629);
            this.tabTest.TabIndex = 3;
            this.tabTest.Text = "Test and Compare";
            this.tabTest.UseVisualStyleBackColor = true;
            this.tabTest.Enter += new System.EventHandler(this.tabTest_Enter);
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.btnAddCTable);
            this.groupBox1.Controls.Add(this.bt_Alg);
            this.groupBox1.Controls.Add(this.tbAlg);
            this.groupBox1.Controls.Add(this.lblAlg);
            this.groupBox1.Controls.Add(this.bt_IdealDir);
            this.groupBox1.Controls.Add(this.bt_TestDir);
            this.groupBox1.Controls.Add(this.tb_IdealDir);
            this.groupBox1.Controls.Add(this.tb_TestDir);
            this.groupBox1.Controls.Add(this.lb_IdealDir);
            this.groupBox1.Controls.Add(this.lb_TestDir);
            this.groupBox1.Controls.Add(this.rb_Compare);
            this.groupBox1.Controls.Add(this.rb_Test);
            this.groupBox1.Controls.Add(this.rb_FullTest);
            this.groupBox1.Controls.Add(this.resultLink);
            this.groupBox1.Location = new System.Drawing.Point(450, 89);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(399, 244);
            this.groupBox1.TabIndex = 8;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Testing";
            // 
            // btnAddCTable
            // 
            this.btnAddCTable.Location = new System.Drawing.Point(101, 178);
            this.btnAddCTable.Name = "btnAddCTable";
            this.btnAddCTable.Size = new System.Drawing.Size(172, 23);
            this.btnAddCTable.TabIndex = 21;
            this.btnAddCTable.Text = "Add Compare Images to Table";
            this.btnAddCTable.UseVisualStyleBackColor = true;
            this.btnAddCTable.Visible = false;
            this.btnAddCTable.Click += new System.EventHandler(this.btnAddCTable_Click);
            // 
            // bt_Alg
            // 
            this.bt_Alg.Location = new System.Drawing.Point(85, 150);
            this.bt_Alg.Name = "bt_Alg";
            this.bt_Alg.Size = new System.Drawing.Size(53, 22);
            this.bt_Alg.TabIndex = 20;
            this.bt_Alg.Text = "Open";
            this.bt_Alg.UseVisualStyleBackColor = true;
            this.bt_Alg.Visible = false;
            this.bt_Alg.Click += new System.EventHandler(this.bt_Alg_Click);
            // 
            // tbAlg
            // 
            this.tbAlg.Location = new System.Drawing.Point(145, 151);
            this.tbAlg.Name = "tbAlg";
            this.tbAlg.Size = new System.Drawing.Size(247, 20);
            this.tbAlg.TabIndex = 19;
            this.tbAlg.Text = "No File Selected";
            this.tbAlg.Visible = false;
            this.tbAlg.WordWrap = false;
            // 
            // lblAlg
            // 
            this.lblAlg.AutoSize = true;
            this.lblAlg.Location = new System.Drawing.Point(0, 155);
            this.lblAlg.Name = "lblAlg";
            this.lblAlg.Size = new System.Drawing.Size(84, 13);
            this.lblAlg.TabIndex = 17;
            this.lblAlg.Text = "Algorithm Sheet:";
            this.lblAlg.Visible = false;
            // 
            // bt_IdealDir
            // 
            this.bt_IdealDir.Location = new System.Drawing.Point(85, 125);
            this.bt_IdealDir.Name = "bt_IdealDir";
            this.bt_IdealDir.Size = new System.Drawing.Size(53, 22);
            this.bt_IdealDir.TabIndex = 16;
            this.bt_IdealDir.Text = "Open";
            this.bt_IdealDir.UseVisualStyleBackColor = true;
            this.bt_IdealDir.Visible = false;
            this.bt_IdealDir.Click += new System.EventHandler(this.bt_IdealDir_Click);
            // 
            // bt_TestDir
            // 
            this.bt_TestDir.Location = new System.Drawing.Point(85, 100);
            this.bt_TestDir.Name = "bt_TestDir";
            this.bt_TestDir.Size = new System.Drawing.Size(53, 22);
            this.bt_TestDir.TabIndex = 15;
            this.bt_TestDir.Text = "Open";
            this.bt_TestDir.UseVisualStyleBackColor = true;
            this.bt_TestDir.Visible = false;
            this.bt_TestDir.Click += new System.EventHandler(this.bt_TestDir_Click);
            // 
            // tb_IdealDir
            // 
            this.tb_IdealDir.Location = new System.Drawing.Point(145, 126);
            this.tb_IdealDir.Name = "tb_IdealDir";
            this.tb_IdealDir.Size = new System.Drawing.Size(247, 20);
            this.tb_IdealDir.TabIndex = 14;
            this.tb_IdealDir.Text = "No Folder Selected";
            this.tb_IdealDir.Visible = false;
            this.tb_IdealDir.WordWrap = false;
            // 
            // tb_TestDir
            // 
            this.tb_TestDir.Location = new System.Drawing.Point(145, 101);
            this.tb_TestDir.Name = "tb_TestDir";
            this.tb_TestDir.Size = new System.Drawing.Size(247, 20);
            this.tb_TestDir.TabIndex = 13;
            this.tb_TestDir.Text = "No Folder Selected";
            this.tb_TestDir.Visible = false;
            this.tb_TestDir.WordWrap = false;
            // 
            // lb_IdealDir
            // 
            this.lb_IdealDir.AutoSize = true;
            this.lb_IdealDir.Location = new System.Drawing.Point(6, 130);
            this.lb_IdealDir.Name = "lb_IdealDir";
            this.lb_IdealDir.Size = new System.Drawing.Size(78, 13);
            this.lb_IdealDir.TabIndex = 12;
            this.lb_IdealDir.Text = "Ideal Directory:";
            this.lb_IdealDir.Visible = false;
            // 
            // lb_TestDir
            // 
            this.lb_TestDir.AutoSize = true;
            this.lb_TestDir.Location = new System.Drawing.Point(6, 105);
            this.lb_TestDir.Name = "lb_TestDir";
            this.lb_TestDir.Size = new System.Drawing.Size(76, 13);
            this.lb_TestDir.TabIndex = 11;
            this.lb_TestDir.Text = "Test Directory:";
            this.lb_TestDir.Visible = false;
            // 
            // rb_Compare
            // 
            this.rb_Compare.AutoSize = true;
            this.rb_Compare.Location = new System.Drawing.Point(25, 77);
            this.rb_Compare.Name = "rb_Compare";
            this.rb_Compare.Size = new System.Drawing.Size(91, 17);
            this.rb_Compare.TabIndex = 10;
            this.rb_Compare.Text = "Only Compare";
            this.rb_Compare.UseVisualStyleBackColor = true;
            this.rb_Compare.CheckedChanged += new System.EventHandler(this.rb_Compare_CheckedChanged);
            // 
            // rb_Test
            // 
            this.rb_Test.AutoSize = true;
            this.rb_Test.Location = new System.Drawing.Point(25, 54);
            this.rb_Test.Name = "rb_Test";
            this.rb_Test.Size = new System.Drawing.Size(70, 17);
            this.rb_Test.TabIndex = 9;
            this.rb_Test.Text = "Only Test";
            this.rb_Test.UseVisualStyleBackColor = true;
            this.rb_Test.CheckedChanged += new System.EventHandler(this.rb_Test_CheckedChanged);
            // 
            // rb_FullTest
            // 
            this.rb_FullTest.AutoSize = true;
            this.rb_FullTest.Checked = true;
            this.rb_FullTest.Location = new System.Drawing.Point(25, 31);
            this.rb_FullTest.Name = "rb_FullTest";
            this.rb_FullTest.Size = new System.Drawing.Size(161, 17);
            this.rb_FullTest.TabIndex = 8;
            this.rb_FullTest.TabStop = true;
            this.rb_FullTest.Text = "Full Test (Test and Compare)";
            this.rb_FullTest.UseVisualStyleBackColor = true;
            this.rb_FullTest.CheckedChanged += new System.EventHandler(this.rb_FullTest_CheckedChanged);
            // 
            // resultLink
            // 
            this.resultLink.AutoSize = true;
            this.resultLink.Location = new System.Drawing.Point(22, 215);
            this.resultLink.Name = "resultLink";
            this.resultLink.Size = new System.Drawing.Size(146, 13);
            this.resultLink.TabIndex = 7;
            this.resultLink.TabStop = true;
            this.resultLink.Text = "Link To Project/Result Folder";
            this.resultLink.LinkClicked += new System.Windows.Forms.LinkLabelLinkClickedEventHandler(this.linkLabel1_LinkClicked);
            // 
            // gbCompare
            // 
            this.gbCompare.Controls.Add(this.cbSelectAll);
            this.gbCompare.Controls.Add(this.errorGroup);
            this.gbCompare.Controls.Add(this.CompareRGBLabel);
            this.gbCompare.Controls.Add(this.diffGroup);
            this.gbCompare.Controls.Add(this.shapeGroup);
            this.gbCompare.Controls.Add(this.averageGroup);
            this.gbCompare.Location = new System.Drawing.Point(8, 90);
            this.gbCompare.Name = "gbCompare";
            this.gbCompare.Size = new System.Drawing.Size(427, 243);
            this.gbCompare.TabIndex = 6;
            this.gbCompare.TabStop = false;
            this.gbCompare.Text = "Compare";
            // 
            // cbSelectAll
            // 
            this.cbSelectAll.AutoSize = true;
            this.cbSelectAll.Location = new System.Drawing.Point(303, 98);
            this.cbSelectAll.Name = "cbSelectAll";
            this.cbSelectAll.Size = new System.Drawing.Size(117, 17);
            this.cbSelectAll.TabIndex = 37;
            this.cbSelectAll.Text = "Select/Deselect All";
            this.cbSelectAll.UseVisualStyleBackColor = true;
            this.cbSelectAll.CheckedChanged += new System.EventHandler(this.cbSelectAll_CheckedChanged);
            // 
            // errorGroup
            // 
            this.errorGroup.Controls.Add(this.tb_RMSR);
            this.errorGroup.Controls.Add(this.tb_RMSG);
            this.errorGroup.Controls.Add(this.tb_RMSB);
            this.errorGroup.Controls.Add(this.tb_SNRB);
            this.errorGroup.Controls.Add(this.tb_SNRR);
            this.errorGroup.Controls.Add(this.tb_SNRG);
            this.errorGroup.Controls.Add(this.cb_SNR);
            this.errorGroup.Controls.Add(this.cb_RMS);
            this.errorGroup.Location = new System.Drawing.Point(7, 27);
            this.errorGroup.Name = "errorGroup";
            this.errorGroup.Size = new System.Drawing.Size(277, 60);
            this.errorGroup.TabIndex = 33;
            this.errorGroup.TabStop = false;
            this.errorGroup.Text = "Error ";
            // 
            // tb_RMSR
            // 
            this.tb_RMSR.BackColor = System.Drawing.Color.DarkGray;
            this.tb_RMSR.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.tb_RMSR.Enabled = false;
            this.tb_RMSR.Location = new System.Drawing.Point(90, 11);
            this.tb_RMSR.Name = "tb_RMSR";
            this.tb_RMSR.Size = new System.Drawing.Size(50, 20);
            this.tb_RMSR.TabIndex = 1;
            this.tb_RMSR.Text = "10";
            this.tb_RMSR.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // tb_RMSG
            // 
            this.tb_RMSG.BackColor = System.Drawing.Color.DarkGray;
            this.tb_RMSG.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.tb_RMSG.Enabled = false;
            this.tb_RMSG.Location = new System.Drawing.Point(150, 11);
            this.tb_RMSG.Name = "tb_RMSG";
            this.tb_RMSG.Size = new System.Drawing.Size(50, 20);
            this.tb_RMSG.TabIndex = 2;
            this.tb_RMSG.Text = "10";
            this.tb_RMSG.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // tb_RMSB
            // 
            this.tb_RMSB.BackColor = System.Drawing.Color.DarkGray;
            this.tb_RMSB.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.tb_RMSB.Enabled = false;
            this.tb_RMSB.Location = new System.Drawing.Point(210, 11);
            this.tb_RMSB.Name = "tb_RMSB";
            this.tb_RMSB.Size = new System.Drawing.Size(50, 20);
            this.tb_RMSB.TabIndex = 3;
            this.tb_RMSB.Text = "10";
            this.tb_RMSB.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // tb_SNRB
            // 
            this.tb_SNRB.BackColor = System.Drawing.Color.DarkGray;
            this.tb_SNRB.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.tb_SNRB.Enabled = false;
            this.tb_SNRB.Location = new System.Drawing.Point(210, 33);
            this.tb_SNRB.Name = "tb_SNRB";
            this.tb_SNRB.Size = new System.Drawing.Size(50, 20);
            this.tb_SNRB.TabIndex = 10;
            this.tb_SNRB.Text = "15";
            this.tb_SNRB.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // tb_SNRR
            // 
            this.tb_SNRR.BackColor = System.Drawing.Color.DarkGray;
            this.tb_SNRR.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.tb_SNRR.Cursor = System.Windows.Forms.Cursors.IBeam;
            this.tb_SNRR.Enabled = false;
            this.tb_SNRR.Location = new System.Drawing.Point(90, 33);
            this.tb_SNRR.Name = "tb_SNRR";
            this.tb_SNRR.Size = new System.Drawing.Size(50, 20);
            this.tb_SNRR.TabIndex = 8;
            this.tb_SNRR.Text = "15";
            this.tb_SNRR.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // tb_SNRG
            // 
            this.tb_SNRG.BackColor = System.Drawing.Color.DarkGray;
            this.tb_SNRG.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.tb_SNRG.Enabled = false;
            this.tb_SNRG.Location = new System.Drawing.Point(150, 33);
            this.tb_SNRG.Name = "tb_SNRG";
            this.tb_SNRG.Size = new System.Drawing.Size(50, 20);
            this.tb_SNRG.TabIndex = 9;
            this.tb_SNRG.Text = "15";
            this.tb_SNRG.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // cb_SNR
            // 
            this.cb_SNR.AutoSize = true;
            this.cb_SNR.Location = new System.Drawing.Point(10, 34);
            this.cb_SNR.Name = "cb_SNR";
            this.cb_SNR.Size = new System.Drawing.Size(74, 17);
            this.cb_SNR.TabIndex = 5;
            this.cb_SNR.Text = "SNR Error";
            this.cb_SNR.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            this.cb_SNR.UseVisualStyleBackColor = true;
            this.cb_SNR.CheckedChanged += new System.EventHandler(this.cb_CheckedChanged);
            // 
            // cb_RMS
            // 
            this.cb_RMS.AutoSize = true;
            this.cb_RMS.BackColor = System.Drawing.Color.Transparent;
            this.cb_RMS.Location = new System.Drawing.Point(10, 14);
            this.cb_RMS.Name = "cb_RMS";
            this.cb_RMS.Size = new System.Drawing.Size(75, 17);
            this.cb_RMS.TabIndex = 0;
            this.cb_RMS.Text = "RMS Error";
            this.cb_RMS.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            this.cb_RMS.UseVisualStyleBackColor = false;
            this.cb_RMS.CheckedChanged += new System.EventHandler(this.cb_CheckedChanged);
            // 
            // CompareRGBLabel
            // 
            this.CompareRGBLabel.AutoSize = true;
            this.CompareRGBLabel.Location = new System.Drawing.Point(112, 14);
            this.CompareRGBLabel.Name = "CompareRGBLabel";
            this.CompareRGBLabel.Size = new System.Drawing.Size(137, 13);
            this.CompareRGBLabel.TabIndex = 4;
            this.CompareRGBLabel.Text = "R/M              G                 B";
            // 
            // diffGroup
            // 
            this.diffGroup.Controls.Add(this.tb_SUBR);
            this.diffGroup.Controls.Add(this.tb_SUBG);
            this.diffGroup.Controls.Add(this.tb_SUBB);
            this.diffGroup.Controls.Add(this.cb_SubtractEnergy);
            this.diffGroup.Location = new System.Drawing.Point(7, 87);
            this.diffGroup.Name = "diffGroup";
            this.diffGroup.Size = new System.Drawing.Size(277, 37);
            this.diffGroup.TabIndex = 34;
            this.diffGroup.TabStop = false;
            this.diffGroup.Text = "Difference";
            // 
            // tb_SUBR
            // 
            this.tb_SUBR.BackColor = System.Drawing.Color.DarkGray;
            this.tb_SUBR.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.tb_SUBR.Enabled = false;
            this.tb_SUBR.Location = new System.Drawing.Point(90, 11);
            this.tb_SUBR.Name = "tb_SUBR";
            this.tb_SUBR.Size = new System.Drawing.Size(50, 20);
            this.tb_SUBR.TabIndex = 11;
            this.tb_SUBR.Text = "0.5";
            this.tb_SUBR.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // tb_SUBG
            // 
            this.tb_SUBG.BackColor = System.Drawing.Color.DarkGray;
            this.tb_SUBG.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.tb_SUBG.Enabled = false;
            this.tb_SUBG.Location = new System.Drawing.Point(150, 11);
            this.tb_SUBG.Name = "tb_SUBG";
            this.tb_SUBG.Size = new System.Drawing.Size(50, 20);
            this.tb_SUBG.TabIndex = 12;
            this.tb_SUBG.Text = "0.5";
            this.tb_SUBG.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // tb_SUBB
            // 
            this.tb_SUBB.BackColor = System.Drawing.Color.DarkGray;
            this.tb_SUBB.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.tb_SUBB.Enabled = false;
            this.tb_SUBB.Location = new System.Drawing.Point(210, 11);
            this.tb_SUBB.Name = "tb_SUBB";
            this.tb_SUBB.Size = new System.Drawing.Size(50, 20);
            this.tb_SUBB.TabIndex = 13;
            this.tb_SUBB.Text = "0.5";
            this.tb_SUBB.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // cb_SubtractEnergy
            // 
            this.cb_SubtractEnergy.AutoSize = true;
            this.cb_SubtractEnergy.Location = new System.Drawing.Point(10, 12);
            this.cb_SubtractEnergy.Name = "cb_SubtractEnergy";
            this.cb_SubtractEnergy.Size = new System.Drawing.Size(78, 17);
            this.cb_SubtractEnergy.TabIndex = 6;
            this.cb_SubtractEnergy.Text = "Diff Energy";
            this.cb_SubtractEnergy.UseVisualStyleBackColor = true;
            this.cb_SubtractEnergy.CheckedChanged += new System.EventHandler(this.cb_CheckedChanged);
            // 
            // shapeGroup
            // 
            this.shapeGroup.Controls.Add(this.tb_Thresh);
            this.shapeGroup.Controls.Add(this.tb_DICEG);
            this.shapeGroup.Controls.Add(this.tb_JaccG);
            this.shapeGroup.Controls.Add(this.tb_OverG);
            this.shapeGroup.Controls.Add(this.tb_OverB);
            this.shapeGroup.Controls.Add(this.tb_OverR);
            this.shapeGroup.Controls.Add(this.tb_JaccR);
            this.shapeGroup.Controls.Add(this.tb_DICER);
            this.shapeGroup.Controls.Add(this.lb_Thresh);
            this.shapeGroup.Controls.Add(this.tb_XORG);
            this.shapeGroup.Controls.Add(this.tb_JaccB);
            this.shapeGroup.Controls.Add(this.tb_XORB);
            this.shapeGroup.Controls.Add(this.tb_DICEB);
            this.shapeGroup.Controls.Add(this.cb_XOR);
            this.shapeGroup.Controls.Add(this.cb_DICE);
            this.shapeGroup.Controls.Add(this.cb_Jaccard);
            this.shapeGroup.Controls.Add(this.cb_Over);
            this.shapeGroup.Controls.Add(this.tb_XORR);
            this.shapeGroup.Location = new System.Drawing.Point(7, 125);
            this.shapeGroup.Name = "shapeGroup";
            this.shapeGroup.Size = new System.Drawing.Size(327, 107);
            this.shapeGroup.TabIndex = 35;
            this.shapeGroup.TabStop = false;
            this.shapeGroup.Text = "Shape Error";
            // 
            // tb_Thresh
            // 
            this.tb_Thresh.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.tb_Thresh.Location = new System.Drawing.Point(270, 77);
            this.tb_Thresh.Name = "tb_Thresh";
            this.tb_Thresh.Size = new System.Drawing.Size(50, 20);
            this.tb_Thresh.TabIndex = 19;
            this.tb_Thresh.Text = "128";
            this.tb_Thresh.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.tb_Thresh.Visible = false;
            // 
            // tb_DICEG
            // 
            this.tb_DICEG.BackColor = System.Drawing.Color.DarkGray;
            this.tb_DICEG.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.tb_DICEG.Enabled = false;
            this.tb_DICEG.Location = new System.Drawing.Point(150, 11);
            this.tb_DICEG.Name = "tb_DICEG";
            this.tb_DICEG.Size = new System.Drawing.Size(50, 20);
            this.tb_DICEG.TabIndex = 25;
            this.tb_DICEG.Text = "0.8";
            this.tb_DICEG.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // tb_JaccG
            // 
            this.tb_JaccG.BackColor = System.Drawing.Color.DarkGray;
            this.tb_JaccG.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.tb_JaccG.Enabled = false;
            this.tb_JaccG.Location = new System.Drawing.Point(150, 33);
            this.tb_JaccG.Name = "tb_JaccG";
            this.tb_JaccG.Size = new System.Drawing.Size(50, 20);
            this.tb_JaccG.TabIndex = 28;
            this.tb_JaccG.Text = "0.8";
            this.tb_JaccG.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // tb_OverG
            // 
            this.tb_OverG.BackColor = System.Drawing.Color.DarkGray;
            this.tb_OverG.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.tb_OverG.Enabled = false;
            this.tb_OverG.Location = new System.Drawing.Point(150, 55);
            this.tb_OverG.Name = "tb_OverG";
            this.tb_OverG.Size = new System.Drawing.Size(50, 20);
            this.tb_OverG.TabIndex = 31;
            this.tb_OverG.Text = "0.8";
            this.tb_OverG.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // tb_OverB
            // 
            this.tb_OverB.BackColor = System.Drawing.Color.DarkGray;
            this.tb_OverB.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.tb_OverB.Enabled = false;
            this.tb_OverB.Location = new System.Drawing.Point(210, 55);
            this.tb_OverB.Name = "tb_OverB";
            this.tb_OverB.Size = new System.Drawing.Size(50, 20);
            this.tb_OverB.TabIndex = 32;
            this.tb_OverB.Text = "0.8";
            this.tb_OverB.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // tb_OverR
            // 
            this.tb_OverR.BackColor = System.Drawing.Color.DarkGray;
            this.tb_OverR.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.tb_OverR.Enabled = false;
            this.tb_OverR.Location = new System.Drawing.Point(90, 55);
            this.tb_OverR.Name = "tb_OverR";
            this.tb_OverR.Size = new System.Drawing.Size(50, 20);
            this.tb_OverR.TabIndex = 30;
            this.tb_OverR.Text = "0.8";
            this.tb_OverR.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // tb_JaccR
            // 
            this.tb_JaccR.BackColor = System.Drawing.Color.DarkGray;
            this.tb_JaccR.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.tb_JaccR.Enabled = false;
            this.tb_JaccR.Location = new System.Drawing.Point(90, 33);
            this.tb_JaccR.Name = "tb_JaccR";
            this.tb_JaccR.Size = new System.Drawing.Size(50, 20);
            this.tb_JaccR.TabIndex = 27;
            this.tb_JaccR.Text = "0.8";
            this.tb_JaccR.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // tb_DICER
            // 
            this.tb_DICER.BackColor = System.Drawing.Color.DarkGray;
            this.tb_DICER.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.tb_DICER.Enabled = false;
            this.tb_DICER.Location = new System.Drawing.Point(90, 11);
            this.tb_DICER.Name = "tb_DICER";
            this.tb_DICER.Size = new System.Drawing.Size(50, 20);
            this.tb_DICER.TabIndex = 24;
            this.tb_DICER.Text = "0.8";
            this.tb_DICER.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // lb_Thresh
            // 
            this.lb_Thresh.AutoSize = true;
            this.lb_Thresh.Location = new System.Drawing.Point(275, 60);
            this.lb_Thresh.Name = "lb_Thresh";
            this.lb_Thresh.Size = new System.Drawing.Size(40, 13);
            this.lb_Thresh.TabIndex = 20;
            this.lb_Thresh.Text = "Thresh";
            this.lb_Thresh.Visible = false;
            // 
            // tb_XORG
            // 
            this.tb_XORG.BackColor = System.Drawing.Color.DarkGray;
            this.tb_XORG.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.tb_XORG.Enabled = false;
            this.tb_XORG.Location = new System.Drawing.Point(150, 77);
            this.tb_XORG.Name = "tb_XORG";
            this.tb_XORG.Size = new System.Drawing.Size(50, 20);
            this.tb_XORG.TabIndex = 15;
            this.tb_XORG.Text = "0.2";
            this.tb_XORG.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // tb_JaccB
            // 
            this.tb_JaccB.BackColor = System.Drawing.Color.DarkGray;
            this.tb_JaccB.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.tb_JaccB.Enabled = false;
            this.tb_JaccB.Location = new System.Drawing.Point(210, 33);
            this.tb_JaccB.Name = "tb_JaccB";
            this.tb_JaccB.Size = new System.Drawing.Size(50, 20);
            this.tb_JaccB.TabIndex = 29;
            this.tb_JaccB.Text = "0.8";
            this.tb_JaccB.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // tb_XORB
            // 
            this.tb_XORB.BackColor = System.Drawing.Color.DarkGray;
            this.tb_XORB.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.tb_XORB.Enabled = false;
            this.tb_XORB.Location = new System.Drawing.Point(210, 77);
            this.tb_XORB.Name = "tb_XORB";
            this.tb_XORB.Size = new System.Drawing.Size(50, 20);
            this.tb_XORB.TabIndex = 16;
            this.tb_XORB.Text = "0.2";
            this.tb_XORB.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // tb_DICEB
            // 
            this.tb_DICEB.BackColor = System.Drawing.Color.DarkGray;
            this.tb_DICEB.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.tb_DICEB.Enabled = false;
            this.tb_DICEB.Location = new System.Drawing.Point(210, 11);
            this.tb_DICEB.Name = "tb_DICEB";
            this.tb_DICEB.Size = new System.Drawing.Size(50, 20);
            this.tb_DICEB.TabIndex = 26;
            this.tb_DICEB.Text = "0.8";
            this.tb_DICEB.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // cb_XOR
            // 
            this.cb_XOR.AutoSize = true;
            this.cb_XOR.Location = new System.Drawing.Point(10, 80);
            this.cb_XOR.Name = "cb_XOR";
            this.cb_XOR.Size = new System.Drawing.Size(74, 17);
            this.cb_XOR.TabIndex = 7;
            this.cb_XOR.Text = "XOR Error";
            this.cb_XOR.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            this.cb_XOR.UseVisualStyleBackColor = true;
            this.cb_XOR.CheckedChanged += new System.EventHandler(this.cb_CheckedChanged);
            // 
            // cb_DICE
            // 
            this.cb_DICE.AutoSize = true;
            this.cb_DICE.Location = new System.Drawing.Point(10, 14);
            this.cb_DICE.Name = "cb_DICE";
            this.cb_DICE.Size = new System.Drawing.Size(51, 17);
            this.cb_DICE.TabIndex = 21;
            this.cb_DICE.Text = "DICE";
            this.cb_DICE.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            this.cb_DICE.UseVisualStyleBackColor = true;
            this.cb_DICE.CheckedChanged += new System.EventHandler(this.cb_CheckedChanged);
            // 
            // cb_Jaccard
            // 
            this.cb_Jaccard.AutoSize = true;
            this.cb_Jaccard.Location = new System.Drawing.Point(10, 36);
            this.cb_Jaccard.Name = "cb_Jaccard";
            this.cb_Jaccard.Size = new System.Drawing.Size(64, 17);
            this.cb_Jaccard.TabIndex = 22;
            this.cb_Jaccard.Text = "Jaccard";
            this.cb_Jaccard.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            this.cb_Jaccard.UseVisualStyleBackColor = true;
            this.cb_Jaccard.CheckedChanged += new System.EventHandler(this.cb_CheckedChanged);
            // 
            // cb_Over
            // 
            this.cb_Over.AutoSize = true;
            this.cb_Over.Location = new System.Drawing.Point(10, 58);
            this.cb_Over.Name = "cb_Over";
            this.cb_Over.Size = new System.Drawing.Size(63, 17);
            this.cb_Over.TabIndex = 23;
            this.cb_Over.Text = "Overlap";
            this.cb_Over.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            this.cb_Over.UseVisualStyleBackColor = true;
            this.cb_Over.CheckedChanged += new System.EventHandler(this.cb_CheckedChanged);
            // 
            // tb_XORR
            // 
            this.tb_XORR.BackColor = System.Drawing.Color.DarkGray;
            this.tb_XORR.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.tb_XORR.Enabled = false;
            this.tb_XORR.Location = new System.Drawing.Point(90, 77);
            this.tb_XORR.Name = "tb_XORR";
            this.tb_XORR.Size = new System.Drawing.Size(50, 20);
            this.tb_XORR.TabIndex = 14;
            this.tb_XORR.Text = "0.2";
            this.tb_XORR.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // averageGroup
            // 
            this.averageGroup.Controls.Add(this.cb_StdDev);
            this.averageGroup.Controls.Add(this.cb_Average);
            this.averageGroup.Location = new System.Drawing.Point(290, 27);
            this.averageGroup.Name = "averageGroup";
            this.averageGroup.Size = new System.Drawing.Size(131, 60);
            this.averageGroup.TabIndex = 36;
            this.averageGroup.TabStop = false;
            this.averageGroup.Text = "Avg/StdDev";
            // 
            // cb_StdDev
            // 
            this.cb_StdDev.AutoSize = true;
            this.cb_StdDev.Location = new System.Drawing.Point(13, 33);
            this.cb_StdDev.Name = "cb_StdDev";
            this.cb_StdDev.Size = new System.Drawing.Size(109, 17);
            this.cb_StdDev.TabIndex = 18;
            this.cb_StdDev.Text = "Calculate StdDev";
            this.cb_StdDev.UseVisualStyleBackColor = true;
            // 
            // cb_Average
            // 
            this.cb_Average.AutoSize = true;
            this.cb_Average.Location = new System.Drawing.Point(13, 14);
            this.cb_Average.Name = "cb_Average";
            this.cb_Average.Size = new System.Drawing.Size(118, 17);
            this.cb_Average.TabIndex = 17;
            this.cb_Average.Text = "Calculate Averages";
            this.cb_Average.UseVisualStyleBackColor = true;
            // 
            // btDeleteAllTest
            // 
            this.btDeleteAllTest.Location = new System.Drawing.Point(690, 588);
            this.btDeleteAllTest.Name = "btDeleteAllTest";
            this.btDeleteAllTest.Size = new System.Drawing.Size(140, 32);
            this.btDeleteAllTest.TabIndex = 5;
            this.btDeleteAllTest.Text = "Delete All Result";
            this.btDeleteAllTest.UseVisualStyleBackColor = true;
            this.btDeleteAllTest.Click += new System.EventHandler(this.btDeleteAllTest_Click);
            // 
            // btDeleteCheckedTest
            // 
            this.btDeleteCheckedTest.Location = new System.Drawing.Point(529, 588);
            this.btDeleteCheckedTest.Name = "btDeleteCheckedTest";
            this.btDeleteCheckedTest.Size = new System.Drawing.Size(140, 32);
            this.btDeleteCheckedTest.TabIndex = 5;
            this.btDeleteCheckedTest.Text = "Delete checked Result";
            this.btDeleteCheckedTest.UseVisualStyleBackColor = true;
            this.btDeleteCheckedTest.Click += new System.EventHandler(this.btDeleteCheckedTest_Click);
            // 
            // gbTestResult
            // 
            this.gbTestResult.Controls.Add(this.labelHelp);
            this.gbTestResult.Controls.Add(this.lvTestResult);
            this.gbTestResult.Location = new System.Drawing.Point(8, 339);
            this.gbTestResult.Name = "gbTestResult";
            this.gbTestResult.Size = new System.Drawing.Size(841, 240);
            this.gbTestResult.TabIndex = 4;
            this.gbTestResult.TabStop = false;
            this.gbTestResult.Text = "Test Result---             ";
            // 
            // labelHelp
            // 
            this.labelHelp.AutoSize = true;
            this.labelHelp.FlatStyle = System.Windows.Forms.FlatStyle.System;
            this.labelHelp.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.labelHelp.Location = new System.Drawing.Point(80, 0);
            this.labelHelp.Name = "labelHelp";
            this.labelHelp.Size = new System.Drawing.Size(33, 13);
            this.labelHelp.TabIndex = 1;
            this.labelHelp.Text = "Help";
            this.labelHelp.Click += new System.EventHandler(this.labelHelp_Click);
            this.labelHelp.MouseLeave += new System.EventHandler(this.labelHelp_MouseLeave);
            // 
            // lvTestResult
            // 
            this.lvTestResult.Activation = System.Windows.Forms.ItemActivation.OneClick;
            this.lvTestResult.CheckBoxes = true;
            this.lvTestResult.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.columnStageOption,
            this.columnAlgorithm,
            this.columnTRlImageName,
            this.columnTRImagePath,
            this.columnTRIdealImageName,
            this.columnTRIdealImagePath,
            this.columnTROriginalImage});
            this.lvTestResult.FullRowSelect = true;
            this.lvTestResult.GridLines = true;
            this.lvTestResult.HideSelection = false;
            this.lvTestResult.Location = new System.Drawing.Point(6, 19);
            this.lvTestResult.MultiSelect = false;
            this.lvTestResult.Name = "lvTestResult";
            this.lvTestResult.ShowItemToolTips = true;
            this.lvTestResult.Size = new System.Drawing.Size(829, 215);
            this.lvTestResult.TabIndex = 0;
            this.lvTestResult.UseCompatibleStateImageBehavior = false;
            this.lvTestResult.View = System.Windows.Forms.View.Details;
            this.lvTestResult.MouseDoubleClick += new System.Windows.Forms.MouseEventHandler(this.listView_MouseDoubleClick);
            // 
            // columnStageOption
            // 
            this.columnStageOption.Text = "Stage&Option";
            this.columnStageOption.Width = 110;
            // 
            // columnAlgorithm
            // 
            this.columnAlgorithm.Text = "Algorithm";
            this.columnAlgorithm.Width = 110;
            // 
            // columnTRlImageName
            // 
            this.columnTRlImageName.Text = "ImageName";
            this.columnTRlImageName.Width = 110;
            // 
            // columnTRImagePath
            // 
            this.columnTRImagePath.Text = "ImagePath";
            this.columnTRImagePath.Width = 110;
            // 
            // columnTRIdealImageName
            // 
            this.columnTRIdealImageName.Text = "IdealImageName";
            this.columnTRIdealImageName.Width = 110;
            // 
            // columnTRIdealImagePath
            // 
            this.columnTRIdealImagePath.Text = "IdealImagePath";
            this.columnTRIdealImagePath.Width = 110;
            // 
            // columnTROriginalImage
            // 
            this.columnTROriginalImage.Text = "OriginalImage";
            this.columnTROriginalImage.Width = 110;
            // 
            // gbRun
            // 
            this.gbRun.Controls.Add(this.TestTypeLabel);
            this.gbRun.Controls.Add(this.pBarTest);
            this.gbRun.Controls.Add(this.tbFOption);
            this.gbRun.Controls.Add(this.tbTOption);
            this.gbRun.Controls.Add(this.labelFOption);
            this.gbRun.Controls.Add(this.labelTOption);
            this.gbRun.Controls.Add(this.labelShowProgress);
            this.gbRun.Controls.Add(this.btTestRun);
            this.gbRun.Controls.Add(this.btRunStop);
            this.gbRun.Controls.Add(this.btRunPause);
            this.gbRun.Location = new System.Drawing.Point(8, 3);
            this.gbRun.Name = "gbRun";
            this.gbRun.Size = new System.Drawing.Size(841, 80);
            this.gbRun.TabIndex = 3;
            this.gbRun.TabStop = false;
            this.gbRun.Text = "Run";
            // 
            // TestTypeLabel
            // 
            this.TestTypeLabel.AutoSize = true;
            this.TestTypeLabel.ForeColor = System.Drawing.Color.Red;
            this.TestTypeLabel.Location = new System.Drawing.Point(601, 49);
            this.TestTypeLabel.Name = "TestTypeLabel";
            this.TestTypeLabel.Size = new System.Drawing.Size(88, 13);
            this.TestTypeLabel.TabIndex = 8;
            this.TestTypeLabel.Text = "No Test Running";
            // 
            // pBarTest
            // 
            this.pBarTest.Location = new System.Drawing.Point(273, 16);
            this.pBarTest.Name = "pBarTest";
            this.pBarTest.Size = new System.Drawing.Size(534, 20);
            this.pBarTest.TabIndex = 7;
            // 
            // tbFOption
            // 
            this.tbFOption.Location = new System.Drawing.Point(508, 45);
            this.tbFOption.Name = "tbFOption";
            this.tbFOption.ReadOnly = true;
            this.tbFOption.Size = new System.Drawing.Size(64, 20);
            this.tbFOption.TabIndex = 6;
            // 
            // tbTOption
            // 
            this.tbTOption.Location = new System.Drawing.Point(347, 45);
            this.tbTOption.Name = "tbTOption";
            this.tbTOption.ReadOnly = true;
            this.tbTOption.Size = new System.Drawing.Size(61, 20);
            this.tbTOption.TabIndex = 6;
            // 
            // labelFOption
            // 
            this.labelFOption.AutoSize = true;
            this.labelFOption.Location = new System.Drawing.Point(414, 49);
            this.labelFOption.Name = "labelFOption";
            this.labelFOption.Size = new System.Drawing.Size(88, 13);
            this.labelFOption.TabIndex = 5;
            this.labelFOption.Text = "Finished Options:";
            // 
            // labelTOption
            // 
            this.labelTOption.AutoSize = true;
            this.labelTOption.Location = new System.Drawing.Point(270, 48);
            this.labelTOption.Name = "labelTOption";
            this.labelTOption.Size = new System.Drawing.Size(73, 13);
            this.labelTOption.TabIndex = 5;
            this.labelTOption.Text = "Total Options:";
            // 
            // labelShowProgress
            // 
            this.labelShowProgress.AutoSize = true;
            this.labelShowProgress.ForeColor = System.Drawing.Color.Red;
            this.labelShowProgress.Location = new System.Drawing.Point(713, 49);
            this.labelShowProgress.Name = "labelShowProgress";
            this.labelShowProgress.Size = new System.Drawing.Size(65, 13);
            this.labelShowProgress.TabIndex = 4;
            this.labelShowProgress.Text = " Progress  %";
            // 
            // btTestRun
            // 
            this.btTestRun.Location = new System.Drawing.Point(21, 28);
            this.btTestRun.Name = "btTestRun";
            this.btTestRun.Size = new System.Drawing.Size(70, 28);
            this.btTestRun.TabIndex = 0;
            this.btTestRun.Text = "Run";
            this.btTestRun.UseVisualStyleBackColor = true;
            this.btTestRun.Click += new System.EventHandler(this.btTestRun_Click);
            // 
            // btRunStop
            // 
            this.btRunStop.Enabled = false;
            this.btRunStop.Location = new System.Drawing.Point(174, 28);
            this.btRunStop.Name = "btRunStop";
            this.btRunStop.Size = new System.Drawing.Size(70, 28);
            this.btRunStop.TabIndex = 2;
            this.btRunStop.Text = "Stop";
            this.btRunStop.UseVisualStyleBackColor = true;
            this.btRunStop.Click += new System.EventHandler(this.btRunStop_Click_1);
            // 
            // btRunPause
            // 
            this.btRunPause.Enabled = false;
            this.btRunPause.Location = new System.Drawing.Point(98, 28);
            this.btRunPause.Name = "btRunPause";
            this.btRunPause.Size = new System.Drawing.Size(70, 28);
            this.btRunPause.TabIndex = 1;
            this.btRunPause.Text = "Pause";
            this.btRunPause.UseVisualStyleBackColor = true;
            this.btRunPause.Click += new System.EventHandler(this.btRunPause_Click_1);
            // 
            // Empty3
            // 
            this.Empty3.Text = "Empty3";
            // 
            // timer1
            // 
            this.timer1.Enabled = true;
            this.timer1.Interval = 3000;
            this.timer1.Tick += new System.EventHandler(this.timer1_Tick);
            // 
            // toolTiplvTestResult
            // 
            this.toolTiplvTestResult.AutomaticDelay = 0;
            this.toolTiplvTestResult.AutoPopDelay = 20000;
            this.toolTiplvTestResult.ForeColor = System.Drawing.SystemColors.ControlText;
            this.toolTiplvTestResult.InitialDelay = 0;
            this.toolTiplvTestResult.IsBalloon = true;
            this.toolTiplvTestResult.ReshowDelay = 0;
            this.toolTiplvTestResult.ShowAlways = true;
            // 
            // fileBrowser
            // 
            this.fileBrowser.FileName = "AlgFile";
            // 
            // abortTimer
            // 
            this.abortTimer.Enabled = true;
            this.abortTimer.Interval = 1;
            this.abortTimer.Tick += new System.EventHandler(this.abortTimer_Tick);
            // 
            // CVIPATATForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(874, 660);
            this.Controls.Add(this.tabProject);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "CVIPATATForm";
            this.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.StartPosition = System.Windows.Forms.FormStartPosition.Manual;
            this.Text = "CVIPATAT";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.CVIPATATForm_FormClosing);
            this.Load += new System.EventHandler(this.CVIPATATForm_Load);
            this.tabProject.ResumeLayout(false);
            this.tabImages.ResumeLayout(false);
            this.gbInputImage.ResumeLayout(false);
            this.gbInputImage.PerformLayout();
            this.gblImage.ResumeLayout(false);
            this.tabProcesses.ResumeLayout(false);
            this.gbProcesses.ResumeLayout(false);
            this.gbProcesses.PerformLayout();
            this.gbSetupProcess.ResumeLayout(false);
            this.gbSetupProcess.PerformLayout();
            this.tabTest.ResumeLayout(false);
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.gbCompare.ResumeLayout(false);
            this.gbCompare.PerformLayout();
            this.errorGroup.ResumeLayout(false);
            this.errorGroup.PerformLayout();
            this.diffGroup.ResumeLayout(false);
            this.diffGroup.PerformLayout();
            this.shapeGroup.ResumeLayout(false);
            this.shapeGroup.PerformLayout();
            this.averageGroup.ResumeLayout(false);
            this.averageGroup.PerformLayout();
            this.gbTestResult.ResumeLayout(false);
            this.gbTestResult.PerformLayout();
            this.gbRun.ResumeLayout(false);
            this.gbRun.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.TabControl tabProject;
        private System.Windows.Forms.TabPage tabImages;
        private System.Windows.Forms.TabPage tabProcesses;
        private System.Windows.Forms.TabPage tabTest;

        private System.Windows.Forms.GroupBox gbInputImage;
        public System.Windows.Forms.Button btTestRun;
        public System.Windows.Forms.Button btRunStop;
        public System.Windows.Forms.Button btRunPause;
        private System.Windows.Forms.ColumnHeader columnImageName;
        private System.Windows.Forms.ColumnHeader columnImagePath;
        private System.Windows.Forms.ColumnHeader columnIdeaImageName;
        private System.Windows.Forms.ColumnHeader columnIdeaImagePath;
        private System.Windows.Forms.Button btDeleteSelectedImage;
        private System.Windows.Forms.Button btDeleteAllImage;
        private System.Windows.Forms.GroupBox gbSetupProcess;
        private System.Windows.Forms.ColumnHeader columnStage;
        private System.Windows.Forms.ColumnHeader columnOption;
        private System.Windows.Forms.ColumnHeader columnProcess;
        private System.Windows.Forms.ColumnHeader columnP1;
        private System.Windows.Forms.Button btDeleteAllProcesses;
        private System.Windows.Forms.Label labelSelectProcess;
        private System.Windows.Forms.Button btAddProcess;

        private System.Windows.Forms.GroupBox gbRun;
        private System.Windows.Forms.Label labeltotalOptions;
        private System.Windows.Forms.ColumnHeader columnP2;
        private System.Windows.Forms.ColumnHeader columnP3;
        private System.Windows.Forms.Button btUp;
        public System.Windows.Forms.ListView lvProcess;
        public System.Windows.Forms.ListView lvImage;
        private System.Windows.Forms.GroupBox gbProcesses;
        private System.Windows.Forms.Button btDown;
        private System.Windows.Forms.GroupBox gbTestResult;
        private System.Windows.Forms.ColumnHeader columnTRlImageName;
        private System.Windows.Forms.ColumnHeader columnTRIdealImageName;
        private System.Windows.Forms.ColumnHeader columnStageOption;
        private System.Windows.Forms.Label labelHelp;
        private System.Windows.Forms.Label lbSelectStage;
        private System.Windows.Forms.ColumnHeader columnTRImagePath;
        private System.Windows.Forms.ColumnHeader columnTRIdealImagePath;
        public System.Windows.Forms.ComboBox cbBoxSeclectProcess;
        public System.Windows.Forms.ComboBox cbBoxSelectStage;
        public System.Windows.Forms.TextBox tbParameter13;
        public System.Windows.Forms.TextBox tbParameter12;
        public System.Windows.Forms.TextBox tbParameter11;
        public System.Windows.Forms.Label labelParameter31;
        public System.Windows.Forms.TextBox tbParameter33;
        public System.Windows.Forms.TextBox tbParameter32;
        public System.Windows.Forms.TextBox tbParameter31;
        public System.Windows.Forms.Label labelParameter21;
        public System.Windows.Forms.TextBox tbParameter23;
        public System.Windows.Forms.TextBox tbParameter22;
        public System.Windows.Forms.TextBox tbParameter21;
        public System.Windows.Forms.Label labelParameter11;
        public System.Windows.Forms.Label labelParameter12;
        public System.Windows.Forms.Label labelParameter32;
        public System.Windows.Forms.Label labelParameter22;
        public System.Windows.Forms.Label labelParameter33;
        public System.Windows.Forms.Label labelParameter23;
        public System.Windows.Forms.Label labelParameter13;
        public System.Windows.Forms.TextBox tbTotalOptionsImage;
        public System.Windows.Forms.Timer timer1;
        public System.Windows.Forms.Button btAddImage;
        public System.Windows.Forms.OpenFileDialog AddImage;
        public System.Windows.Forms.ToolTip toolTiplvTestResult;
        public System.Windows.Forms.ListView lvTestResult;
        private System.Windows.Forms.Label lableTotalImage;
        public System.Windows.Forms.TextBox tbImageCount;
        private System.Windows.Forms.Label labelFOption;
        private System.Windows.Forms.Label labelTOption;
        public System.Windows.Forms.TextBox tbFOption;
        public System.Windows.Forms.TextBox tbTOption;
        public System.Windows.Forms.Label labelShowProgress;
        public System.Windows.Forms.ProgressBar pBarTest;
        private System.Windows.Forms.Button btDeleteAllTest;
        private System.Windows.Forms.Button btDeleteCheckedTest;
        private System.Windows.Forms.ColumnHeader columnTROriginalImage;
        private System.Windows.Forms.Button btDeleteCheckedProcess;
        private System.Windows.Forms.Button btAddIdealImage;
        private System.Windows.Forms.Button btDelAllIdealImage;
        private System.Windows.Forms.Button btDelSelectedIdImage;
        private System.Windows.Forms.GroupBox gblImage;
        private System.Windows.Forms.ColumnHeader Empty3;
        private System.Windows.Forms.GroupBox gbCompare;
        public System.Windows.Forms.CheckBox cb_RMS;
        public System.Windows.Forms.TextBox tb_RMSB;
        public System.Windows.Forms.TextBox tb_RMSG;
        public System.Windows.Forms.TextBox tb_RMSR;
        public System.Windows.Forms.Label CompareRGBLabel;
        public System.Windows.Forms.CheckBox cb_SNR;
        public System.Windows.Forms.CheckBox cb_SubtractEnergy;
        public System.Windows.Forms.TextBox tb_SUBB;
        public System.Windows.Forms.TextBox tb_SUBG;
        public System.Windows.Forms.TextBox tb_SUBR;
        public System.Windows.Forms.TextBox tb_SNRB;
        public System.Windows.Forms.TextBox tb_SNRG;
        public System.Windows.Forms.TextBox tb_SNRR;
        public System.Windows.Forms.CheckBox cb_XOR;
        public System.Windows.Forms.TextBox tb_XORB;
        public System.Windows.Forms.TextBox tb_XORG;
        public System.Windows.Forms.TextBox tb_XORR;
        public System.Windows.Forms.CheckBox cb_Average;
        public System.Windows.Forms.CheckBox cb_StdDev;
        public System.Windows.Forms.Label lb_Thresh;
        public System.Windows.Forms.TextBox tb_Thresh;
        public System.Windows.Forms.LinkLabel resultLink;
        public System.Windows.Forms.Label TestTypeLabel;
        private System.Windows.Forms.GroupBox groupBox1;
        public System.Windows.Forms.RadioButton rb_Compare;
        public System.Windows.Forms.RadioButton rb_Test;
        public System.Windows.Forms.RadioButton rb_FullTest;
        private System.Windows.Forms.Label lb_IdealDir;
        private System.Windows.Forms.Label lb_TestDir;
        private System.Windows.Forms.Button bt_IdealDir;
        private System.Windows.Forms.Button bt_TestDir;
        public System.Windows.Forms.TextBox tb_IdealDir;
        public System.Windows.Forms.TextBox tb_TestDir;
        public System.Windows.Forms.TextBox tb_OverB;
        public System.Windows.Forms.TextBox tb_OverG;
        public System.Windows.Forms.TextBox tb_OverR;
        public System.Windows.Forms.TextBox tb_JaccB;
        public System.Windows.Forms.TextBox tb_JaccG;
        public System.Windows.Forms.TextBox tb_JaccR;
        public System.Windows.Forms.TextBox tb_DICEB;
        public System.Windows.Forms.TextBox tb_DICEG;
        public System.Windows.Forms.TextBox tb_DICER;
        public System.Windows.Forms.CheckBox cb_Over;
        public System.Windows.Forms.CheckBox cb_Jaccard;
        public System.Windows.Forms.CheckBox cb_DICE;
        private System.Windows.Forms.GroupBox errorGroup;
        private System.Windows.Forms.GroupBox diffGroup;
        private System.Windows.Forms.GroupBox shapeGroup;
        private System.Windows.Forms.GroupBox averageGroup;
        public System.Windows.Forms.TextBox tbAlg;
        private System.Windows.Forms.Label lblAlg;
        private System.Windows.Forms.Button bt_Alg;
        private System.Windows.Forms.OpenFileDialog fileBrowser;
        public System.Windows.Forms.CheckBox cbSelectAll;
        private System.Windows.Forms.ColumnHeader columnAlgorithm;
        public System.Windows.Forms.Button bt_AddFolder;
        public System.Windows.Forms.FolderBrowserDialog folderBrowser;
        private System.Windows.Forms.Button bt_IncreaseStage;
        private System.Windows.Forms.Button bt_DecreaseStage;
        private System.Windows.Forms.Button btnAddCTable;
        private System.Windows.Forms.Timer abortTimer;
        //private System.Windows.Forms.Button btCoordinate;

    }
}
