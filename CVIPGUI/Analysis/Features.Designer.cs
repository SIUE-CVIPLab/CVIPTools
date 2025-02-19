namespace CVIPGUI.Analysis
{
    partial class Features
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
            this.cboOriginalImage = new System.Windows.Forms.ComboBox();
            this.lblOriginalImage = new System.Windows.Forms.Label();
            this.cboSegmentedImage = new System.Windows.Forms.ComboBox();
            this.lblSegmentedImage = new System.Windows.Forms.Label();
            this.cboFeatureFile = new System.Windows.Forms.ComboBox();
            this.lblFeatureFile = new System.Windows.Forms.Label();
            this.btnSaveAs = new System.Windows.Forms.Button();
            this.txtClassName = new System.Windows.Forms.TextBox();
            this.lblClassName = new System.Windows.Forms.Label();
            this.txtFeatureCol = new System.Windows.Forms.TextBox();
            this.lblFeatureCol = new System.Windows.Forms.Label();
            this.txtFeatureRow = new System.Windows.Forms.TextBox();
            this.lblFeatureRow = new System.Windows.Forms.Label();
            this.btnViewFeatureFile = new System.Windows.Forms.Button();
            this.btnViewLabeledImage = new System.Windows.Forms.Button();
            this.grpBinary = new System.Windows.Forms.GroupBox();
            this.btnSelectAllBin = new System.Windows.Forms.Button();
            this.lblProjHeight = new System.Windows.Forms.Label();
            this.txtProjHeight = new System.Windows.Forms.TextBox();
            this.lblProjWidth = new System.Windows.Forms.Label();
            this.txtProjWidth = new System.Windows.Forms.TextBox();
            this.chkAspect = new System.Windows.Forms.CheckBox();
            this.chkThinness = new System.Windows.Forms.CheckBox();
            this.chkProjections = new System.Windows.Forms.CheckBox();
            this.chkEuler = new System.Windows.Forms.CheckBox();
            this.chkPerimeter = new System.Windows.Forms.CheckBox();
            this.chkOrientation = new System.Windows.Forms.CheckBox();
            this.chkCentroid = new System.Windows.Forms.CheckBox();
            this.chkArea = new System.Windows.Forms.CheckBox();
            this.grpRST = new System.Windows.Forms.GroupBox();
            this.btnSelectAllRst = new System.Windows.Forms.Button();
            this.chkRst7 = new System.Windows.Forms.CheckBox();
            this.chkRst6 = new System.Windows.Forms.CheckBox();
            this.chkRst5 = new System.Windows.Forms.CheckBox();
            this.chkRst4 = new System.Windows.Forms.CheckBox();
            this.chkRst3 = new System.Windows.Forms.CheckBox();
            this.chkRst2 = new System.Windows.Forms.CheckBox();
            this.chkRst1 = new System.Windows.Forms.CheckBox();
            this.grpHistogram = new System.Windows.Forms.GroupBox();
            this.btnSelectAllHist = new System.Windows.Forms.Button();
            this.chkHistEntropy = new System.Windows.Forms.CheckBox();
            this.chkHistEnergy = new System.Windows.Forms.CheckBox();
            this.chkHistSkew = new System.Windows.Forms.CheckBox();
            this.chkHistStdDev = new System.Windows.Forms.CheckBox();
            this.chkHistMean = new System.Windows.Forms.CheckBox();
            this.grpTexture = new System.Windows.Forms.GroupBox();
            this.btnSelectAllTex = new System.Windows.Forms.Button();
            this.chkIncludeZero = new System.Windows.Forms.CheckBox();
            this.lblTexDistance = new System.Windows.Forms.Label();
            this.cboTexDistance = new System.Windows.Forms.ComboBox();
            this.chkTexEntropy = new System.Windows.Forms.CheckBox();
            this.chkTexInvDiff = new System.Windows.Forms.CheckBox();
            this.chkTexCorrelation = new System.Windows.Forms.CheckBox();
            this.chkTexInertia = new System.Windows.Forms.CheckBox();
            this.chkTexEnergy = new System.Windows.Forms.CheckBox();
            this.grpSpectral = new System.Windows.Forms.GroupBox();
            this.btnSpectral = new System.Windows.Forms.Button();
            this.lblNumSectors = new System.Windows.Forms.Label();
            this.txtNumSectors = new System.Windows.Forms.TextBox();
            this.lblNumRings = new System.Windows.Forms.Label();
            this.txtNumRings = new System.Windows.Forms.TextBox();
            this.chkSpectral = new System.Windows.Forms.CheckBox();
            this.btnHelp = new System.Windows.Forms.Button();
            this.btnCancel = new System.Windows.Forms.Button();
            this.btnReset = new System.Windows.Forms.Button();
            this.btnApply = new System.Windows.Forms.Button();
            this.dlgFileOpen = new System.Windows.Forms.OpenFileDialog();
            this.grplaw = new System.Windows.Forms.GroupBox();
            this.button2 = new System.Windows.Forms.Button();
            this.chklaw15 = new System.Windows.Forms.CheckBox();
            this.chklaw14 = new System.Windows.Forms.CheckBox();
            this.chklaw13 = new System.Windows.Forms.CheckBox();
            this.chklaw12 = new System.Windows.Forms.CheckBox();
            this.chklaw11 = new System.Windows.Forms.CheckBox();
            this.chklaw10 = new System.Windows.Forms.CheckBox();
            this.chklaw9 = new System.Windows.Forms.CheckBox();
            this.chklaw7 = new System.Windows.Forms.CheckBox();
            this.chklaw8 = new System.Windows.Forms.CheckBox();
            this.chklaw6 = new System.Windows.Forms.CheckBox();
            this.chklaw5 = new System.Windows.Forms.CheckBox();
            this.chklaw4 = new System.Windows.Forms.CheckBox();
            this.chklaw3 = new System.Windows.Forms.CheckBox();
            this.button1 = new System.Windows.Forms.Button();
            this.chklaw2 = new System.Windows.Forms.CheckBox();
            this.chklaw1 = new System.Windows.Forms.CheckBox();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.btnExceltoText = new System.Windows.Forms.Button();
            this.grpBinary.SuspendLayout();
            this.grpRST.SuspendLayout();
            this.grpHistogram.SuspendLayout();
            this.grpTexture.SuspendLayout();
            this.grpSpectral.SuspendLayout();
            this.grplaw.SuspendLayout();
            this.groupBox1.SuspendLayout();
            this.SuspendLayout();
            // 
            // cboOriginalImage
            // 
            this.cboOriginalImage.DisplayMember = "Text";
            this.cboOriginalImage.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cboOriginalImage.FormattingEnabled = true;
            this.cboOriginalImage.Location = new System.Drawing.Point(102, 16);
            this.cboOriginalImage.Name = "cboOriginalImage";
            this.cboOriginalImage.Size = new System.Drawing.Size(512, 21);
            this.cboOriginalImage.TabIndex = 0;
            // 
            // lblOriginalImage
            // 
            this.lblOriginalImage.AutoSize = true;
            this.lblOriginalImage.Location = new System.Drawing.Point(6, 19);
            this.lblOriginalImage.Name = "lblOriginalImage";
            this.lblOriginalImage.Size = new System.Drawing.Size(74, 26);
            this.lblOriginalImage.TabIndex = 1;
            this.lblOriginalImage.Text = "Original Image\r\n  (Ctrl + Click)";
            // 
            // cboSegmentedImage
            // 
            this.cboSegmentedImage.DisplayMember = "Text";
            this.cboSegmentedImage.FormattingEnabled = true;
            this.cboSegmentedImage.Location = new System.Drawing.Point(102, 51);
            this.cboSegmentedImage.Name = "cboSegmentedImage";
            this.cboSegmentedImage.Size = new System.Drawing.Size(512, 21);
            this.cboSegmentedImage.TabIndex = 2;
            // 
            // lblSegmentedImage
            // 
            this.lblSegmentedImage.AutoSize = true;
            this.lblSegmentedImage.Location = new System.Drawing.Point(6, 51);
            this.lblSegmentedImage.Name = "lblSegmentedImage";
            this.lblSegmentedImage.Size = new System.Drawing.Size(93, 26);
            this.lblSegmentedImage.TabIndex = 3;
            this.lblSegmentedImage.Text = "Segmented Image\r\n  ( Alt + Click )";
            // 
            // cboFeatureFile
            // 
            this.cboFeatureFile.DisplayMember = "Name";
            this.cboFeatureFile.FormattingEnabled = true;
            this.cboFeatureFile.Location = new System.Drawing.Point(102, 83);
            this.cboFeatureFile.Name = "cboFeatureFile";
            this.cboFeatureFile.Size = new System.Drawing.Size(241, 21);
            this.cboFeatureFile.TabIndex = 4;
            this.cboFeatureFile.SelectedIndexChanged += new System.EventHandler(this.cboFeatureFile_SelectedIndexChanged);
            // 
            // lblFeatureFile
            // 
            this.lblFeatureFile.AutoSize = true;
            this.lblFeatureFile.Location = new System.Drawing.Point(3, 88);
            this.lblFeatureFile.Name = "lblFeatureFile";
            this.lblFeatureFile.Size = new System.Drawing.Size(93, 13);
            this.lblFeatureFile.TabIndex = 5;
            this.lblFeatureFile.Text = "Feature File Name";
            this.lblFeatureFile.Click += new System.EventHandler(this.lblFeatureFile_Click);
            // 
            // btnSaveAs
            // 
            this.btnSaveAs.Location = new System.Drawing.Point(349, 82);
            this.btnSaveAs.Name = "btnSaveAs";
            this.btnSaveAs.Size = new System.Drawing.Size(65, 22);
            this.btnSaveAs.TabIndex = 6;
            this.btnSaveAs.Text = "Save As ...";
            this.btnSaveAs.UseVisualStyleBackColor = true;
            this.btnSaveAs.Click += new System.EventHandler(this.btnSaveAs_Click);
            // 
            // txtClassName
            // 
            this.txtClassName.Location = new System.Drawing.Point(496, 81);
            this.txtClassName.Name = "txtClassName";
            this.txtClassName.Size = new System.Drawing.Size(118, 20);
            this.txtClassName.TabIndex = 7;
            // 
            // lblClassName
            // 
            this.lblClassName.AutoSize = true;
            this.lblClassName.Location = new System.Drawing.Point(420, 87);
            this.lblClassName.Name = "lblClassName";
            this.lblClassName.Size = new System.Drawing.Size(77, 13);
            this.lblClassName.TabIndex = 8;
            this.lblClassName.Text = "Class(Optional)";
            // 
            // txtFeatureCol
            // 
            this.txtFeatureCol.Location = new System.Drawing.Point(185, 110);
            this.txtFeatureCol.Name = "txtFeatureCol";
            this.txtFeatureCol.Size = new System.Drawing.Size(57, 20);
            this.txtFeatureCol.TabIndex = 9;
            this.txtFeatureCol.Text = "1";
            // 
            // lblFeatureCol
            // 
            this.lblFeatureCol.AutoSize = true;
            this.lblFeatureCol.Location = new System.Drawing.Point(6, 117);
            this.lblFeatureCol.Name = "lblFeatureCol";
            this.lblFeatureCol.Size = new System.Drawing.Size(162, 13);
            this.lblFeatureCol.TabIndex = 10;
            this.lblFeatureCol.Text = "The coordinate of the object, Col";
            // 
            // txtFeatureRow
            // 
            this.txtFeatureRow.Location = new System.Drawing.Point(292, 110);
            this.txtFeatureRow.Name = "txtFeatureRow";
            this.txtFeatureRow.Size = new System.Drawing.Size(56, 20);
            this.txtFeatureRow.TabIndex = 11;
            this.txtFeatureRow.Text = "1";
            // 
            // lblFeatureRow
            // 
            this.lblFeatureRow.AutoSize = true;
            this.lblFeatureRow.Location = new System.Drawing.Point(257, 113);
            this.lblFeatureRow.Name = "lblFeatureRow";
            this.lblFeatureRow.Size = new System.Drawing.Size(29, 13);
            this.lblFeatureRow.TabIndex = 12;
            this.lblFeatureRow.Text = "Row";
            // 
            // btnViewFeatureFile
            // 
            this.btnViewFeatureFile.Location = new System.Drawing.Point(354, 107);
            this.btnViewFeatureFile.Name = "btnViewFeatureFile";
            this.btnViewFeatureFile.Size = new System.Drawing.Size(120, 23);
            this.btnViewFeatureFile.TabIndex = 13;
            this.btnViewFeatureFile.Text = "View Feature File";
            this.btnViewFeatureFile.UseVisualStyleBackColor = true;
            this.btnViewFeatureFile.Click += new System.EventHandler(this.btnViewFeatureFile_Click);
            // 
            // btnViewLabeledImage
            // 
            this.btnViewLabeledImage.Location = new System.Drawing.Point(480, 107);
            this.btnViewLabeledImage.Name = "btnViewLabeledImage";
            this.btnViewLabeledImage.Size = new System.Drawing.Size(134, 23);
            this.btnViewLabeledImage.TabIndex = 14;
            this.btnViewLabeledImage.Text = "View Labeled Image";
            this.btnViewLabeledImage.UseVisualStyleBackColor = true;
            this.btnViewLabeledImage.Click += new System.EventHandler(this.btnViewLabeledImage_Click);
            // 
            // grpBinary
            // 
            this.grpBinary.Controls.Add(this.btnSelectAllBin);
            this.grpBinary.Controls.Add(this.lblProjHeight);
            this.grpBinary.Controls.Add(this.txtProjHeight);
            this.grpBinary.Controls.Add(this.lblProjWidth);
            this.grpBinary.Controls.Add(this.txtProjWidth);
            this.grpBinary.Controls.Add(this.chkAspect);
            this.grpBinary.Controls.Add(this.chkThinness);
            this.grpBinary.Controls.Add(this.chkProjections);
            this.grpBinary.Controls.Add(this.chkEuler);
            this.grpBinary.Controls.Add(this.chkPerimeter);
            this.grpBinary.Controls.Add(this.chkOrientation);
            this.grpBinary.Controls.Add(this.chkCentroid);
            this.grpBinary.Controls.Add(this.chkArea);
            this.grpBinary.Location = new System.Drawing.Point(8, 152);
            this.grpBinary.Name = "grpBinary";
            this.grpBinary.Size = new System.Drawing.Size(519, 99);
            this.grpBinary.TabIndex = 15;
            this.grpBinary.TabStop = false;
            this.grpBinary.Text = "Binary Features";
            // 
            // btnSelectAllBin
            // 
            this.btnSelectAllBin.Location = new System.Drawing.Point(430, 67);
            this.btnSelectAllBin.Name = "btnSelectAllBin";
            this.btnSelectAllBin.Size = new System.Drawing.Size(75, 23);
            this.btnSelectAllBin.TabIndex = 12;
            this.btnSelectAllBin.Text = "Select All";
            this.btnSelectAllBin.UseVisualStyleBackColor = true;
            this.btnSelectAllBin.Click += new System.EventHandler(this.btnSelectAllBin_Click);
            // 
            // lblProjHeight
            // 
            this.lblProjHeight.AutoSize = true;
            this.lblProjHeight.Location = new System.Drawing.Point(280, 72);
            this.lblProjHeight.Name = "lblProjHeight";
            this.lblProjHeight.Size = new System.Drawing.Size(39, 13);
            this.lblProjHeight.TabIndex = 11;
            this.lblProjHeight.Text = "height:";
            // 
            // txtProjHeight
            // 
            this.txtProjHeight.Location = new System.Drawing.Point(324, 68);
            this.txtProjHeight.Name = "txtProjHeight";
            this.txtProjHeight.Size = new System.Drawing.Size(43, 20);
            this.txtProjHeight.TabIndex = 10;
            this.txtProjHeight.Text = "10";
            // 
            // lblProjWidth
            // 
            this.lblProjWidth.AutoSize = true;
            this.lblProjWidth.Location = new System.Drawing.Point(13, 72);
            this.lblProjWidth.Name = "lblProjWidth";
            this.lblProjWidth.Size = new System.Drawing.Size(210, 13);
            this.lblProjWidth.TabIndex = 9;
            this.lblProjWidth.Text = "For projections, enter the normalizing width:";
            // 
            // txtProjWidth
            // 
            this.txtProjWidth.Location = new System.Drawing.Point(228, 68);
            this.txtProjWidth.Name = "txtProjWidth";
            this.txtProjWidth.Size = new System.Drawing.Size(44, 20);
            this.txtProjWidth.TabIndex = 8;
            this.txtProjWidth.Text = "10";
            // 
            // chkAspect
            // 
            this.chkAspect.AutoSize = true;
            this.chkAspect.Location = new System.Drawing.Point(310, 43);
            this.chkAspect.Name = "chkAspect";
            this.chkAspect.Size = new System.Drawing.Size(87, 17);
            this.chkAspect.TabIndex = 7;
            this.chkAspect.Text = "Aspect Ratio";
            this.chkAspect.UseVisualStyleBackColor = true;
            // 
            // chkThinness
            // 
            this.chkThinness.AutoSize = true;
            this.chkThinness.Location = new System.Drawing.Point(221, 43);
            this.chkThinness.Name = "chkThinness";
            this.chkThinness.Size = new System.Drawing.Size(69, 17);
            this.chkThinness.TabIndex = 6;
            this.chkThinness.Text = "Thinness";
            this.chkThinness.UseVisualStyleBackColor = true;
            // 
            // chkProjections
            // 
            this.chkProjections.AutoSize = true;
            this.chkProjections.Location = new System.Drawing.Point(124, 43);
            this.chkProjections.Name = "chkProjections";
            this.chkProjections.Size = new System.Drawing.Size(78, 17);
            this.chkProjections.TabIndex = 5;
            this.chkProjections.Text = "Projections";
            this.chkProjections.UseVisualStyleBackColor = true;
            // 
            // chkEuler
            // 
            this.chkEuler.AutoSize = true;
            this.chkEuler.Location = new System.Drawing.Point(15, 43);
            this.chkEuler.Name = "chkEuler";
            this.chkEuler.Size = new System.Drawing.Size(90, 17);
            this.chkEuler.TabIndex = 4;
            this.chkEuler.Text = "Euler Number";
            this.chkEuler.UseVisualStyleBackColor = true;
            // 
            // chkPerimeter
            // 
            this.chkPerimeter.AutoSize = true;
            this.chkPerimeter.Location = new System.Drawing.Point(310, 20);
            this.chkPerimeter.Name = "chkPerimeter";
            this.chkPerimeter.Size = new System.Drawing.Size(70, 17);
            this.chkPerimeter.TabIndex = 3;
            this.chkPerimeter.Text = "Perimeter";
            this.chkPerimeter.UseVisualStyleBackColor = true;
            // 
            // chkOrientation
            // 
            this.chkOrientation.AutoSize = true;
            this.chkOrientation.Location = new System.Drawing.Point(221, 20);
            this.chkOrientation.Name = "chkOrientation";
            this.chkOrientation.Size = new System.Drawing.Size(77, 17);
            this.chkOrientation.TabIndex = 2;
            this.chkOrientation.Text = "Orientation";
            this.chkOrientation.UseVisualStyleBackColor = true;
            // 
            // chkCentroid
            // 
            this.chkCentroid.AutoSize = true;
            this.chkCentroid.Location = new System.Drawing.Point(124, 20);
            this.chkCentroid.Name = "chkCentroid";
            this.chkCentroid.Size = new System.Drawing.Size(65, 17);
            this.chkCentroid.TabIndex = 1;
            this.chkCentroid.Text = "Centroid";
            this.chkCentroid.UseVisualStyleBackColor = true;
            // 
            // chkArea
            // 
            this.chkArea.AutoSize = true;
            this.chkArea.Location = new System.Drawing.Point(15, 20);
            this.chkArea.Name = "chkArea";
            this.chkArea.Size = new System.Drawing.Size(48, 17);
            this.chkArea.TabIndex = 0;
            this.chkArea.Text = "Area";
            this.chkArea.UseVisualStyleBackColor = true;
            // 
            // grpRST
            // 
            this.grpRST.Controls.Add(this.btnSelectAllRst);
            this.grpRST.Controls.Add(this.chkRst7);
            this.grpRST.Controls.Add(this.chkRst6);
            this.grpRST.Controls.Add(this.chkRst5);
            this.grpRST.Controls.Add(this.chkRst4);
            this.grpRST.Controls.Add(this.chkRst3);
            this.grpRST.Controls.Add(this.chkRst2);
            this.grpRST.Controls.Add(this.chkRst1);
            this.grpRST.Location = new System.Drawing.Point(8, 263);
            this.grpRST.Name = "grpRST";
            this.grpRST.Size = new System.Drawing.Size(519, 45);
            this.grpRST.TabIndex = 16;
            this.grpRST.TabStop = false;
            this.grpRST.Text = "RST- Invariant Features";
            // 
            // btnSelectAllRst
            // 
            this.btnSelectAllRst.Location = new System.Drawing.Point(430, 14);
            this.btnSelectAllRst.Name = "btnSelectAllRst";
            this.btnSelectAllRst.Size = new System.Drawing.Size(75, 23);
            this.btnSelectAllRst.TabIndex = 7;
            this.btnSelectAllRst.Text = "Select All";
            this.btnSelectAllRst.UseVisualStyleBackColor = true;
            this.btnSelectAllRst.Click += new System.EventHandler(this.btnSelectAllRst_Click);
            // 
            // chkRst7
            // 
            this.chkRst7.AutoSize = true;
            this.chkRst7.Location = new System.Drawing.Point(357, 20);
            this.chkRst7.Name = "chkRst7";
            this.chkRst7.Size = new System.Drawing.Size(43, 17);
            this.chkRst7.TabIndex = 6;
            this.chkRst7.Text = "rst7";
            this.chkRst7.UseVisualStyleBackColor = true;
            // 
            // chkRst6
            // 
            this.chkRst6.AutoSize = true;
            this.chkRst6.Location = new System.Drawing.Point(300, 20);
            this.chkRst6.Name = "chkRst6";
            this.chkRst6.Size = new System.Drawing.Size(43, 17);
            this.chkRst6.TabIndex = 5;
            this.chkRst6.Text = "rst6";
            this.chkRst6.UseVisualStyleBackColor = true;
            // 
            // chkRst5
            // 
            this.chkRst5.AutoSize = true;
            this.chkRst5.Location = new System.Drawing.Point(243, 20);
            this.chkRst5.Name = "chkRst5";
            this.chkRst5.Size = new System.Drawing.Size(43, 17);
            this.chkRst5.TabIndex = 4;
            this.chkRst5.Text = "rst5";
            this.chkRst5.UseVisualStyleBackColor = true;
            // 
            // chkRst4
            // 
            this.chkRst4.AutoSize = true;
            this.chkRst4.Location = new System.Drawing.Point(186, 20);
            this.chkRst4.Name = "chkRst4";
            this.chkRst4.Size = new System.Drawing.Size(43, 17);
            this.chkRst4.TabIndex = 3;
            this.chkRst4.Text = "rst4";
            this.chkRst4.UseVisualStyleBackColor = true;
            // 
            // chkRst3
            // 
            this.chkRst3.AutoSize = true;
            this.chkRst3.Location = new System.Drawing.Point(129, 20);
            this.chkRst3.Name = "chkRst3";
            this.chkRst3.Size = new System.Drawing.Size(43, 17);
            this.chkRst3.TabIndex = 2;
            this.chkRst3.Text = "rst3";
            this.chkRst3.UseVisualStyleBackColor = true;
            // 
            // chkRst2
            // 
            this.chkRst2.AutoSize = true;
            this.chkRst2.Location = new System.Drawing.Point(72, 20);
            this.chkRst2.Name = "chkRst2";
            this.chkRst2.Size = new System.Drawing.Size(43, 17);
            this.chkRst2.TabIndex = 1;
            this.chkRst2.Text = "rst2";
            this.chkRst2.UseVisualStyleBackColor = true;
            // 
            // chkRst1
            // 
            this.chkRst1.AutoSize = true;
            this.chkRst1.Location = new System.Drawing.Point(15, 20);
            this.chkRst1.Name = "chkRst1";
            this.chkRst1.Size = new System.Drawing.Size(43, 17);
            this.chkRst1.TabIndex = 0;
            this.chkRst1.Text = "rst1";
            this.chkRst1.UseVisualStyleBackColor = true;
            // 
            // grpHistogram
            // 
            this.grpHistogram.Controls.Add(this.btnSelectAllHist);
            this.grpHistogram.Controls.Add(this.chkHistEntropy);
            this.grpHistogram.Controls.Add(this.chkHistEnergy);
            this.grpHistogram.Controls.Add(this.chkHistSkew);
            this.grpHistogram.Controls.Add(this.chkHistStdDev);
            this.grpHistogram.Controls.Add(this.chkHistMean);
            this.grpHistogram.Location = new System.Drawing.Point(8, 317);
            this.grpHistogram.Name = "grpHistogram";
            this.grpHistogram.Size = new System.Drawing.Size(519, 56);
            this.grpHistogram.TabIndex = 17;
            this.grpHistogram.TabStop = false;
            this.grpHistogram.Text = "Histogram Features";
            // 
            // btnSelectAllHist
            // 
            this.btnSelectAllHist.Location = new System.Drawing.Point(430, 14);
            this.btnSelectAllHist.Name = "btnSelectAllHist";
            this.btnSelectAllHist.Size = new System.Drawing.Size(75, 23);
            this.btnSelectAllHist.TabIndex = 5;
            this.btnSelectAllHist.Text = "Select All";
            this.btnSelectAllHist.UseVisualStyleBackColor = true;
            this.btnSelectAllHist.Click += new System.EventHandler(this.btnSelectAllHist_Click);
            // 
            // chkHistEntropy
            // 
            this.chkHistEntropy.AutoSize = true;
            this.chkHistEntropy.Location = new System.Drawing.Point(349, 20);
            this.chkHistEntropy.Name = "chkHistEntropy";
            this.chkHistEntropy.Size = new System.Drawing.Size(62, 17);
            this.chkHistEntropy.TabIndex = 4;
            this.chkHistEntropy.Text = "Entropy";
            this.chkHistEntropy.UseVisualStyleBackColor = true;
            // 
            // chkHistEnergy
            // 
            this.chkHistEnergy.AutoSize = true;
            this.chkHistEnergy.Location = new System.Drawing.Point(264, 20);
            this.chkHistEnergy.Name = "chkHistEnergy";
            this.chkHistEnergy.Size = new System.Drawing.Size(59, 17);
            this.chkHistEnergy.TabIndex = 3;
            this.chkHistEnergy.Text = "Energy";
            this.chkHistEnergy.UseVisualStyleBackColor = true;
            // 
            // chkHistSkew
            // 
            this.chkHistSkew.AutoSize = true;
            this.chkHistSkew.Location = new System.Drawing.Point(185, 20);
            this.chkHistSkew.Name = "chkHistSkew";
            this.chkHistSkew.Size = new System.Drawing.Size(53, 17);
            this.chkHistSkew.TabIndex = 2;
            this.chkHistSkew.Text = "Skew";
            this.chkHistSkew.UseVisualStyleBackColor = true;
            // 
            // chkHistStdDev
            // 
            this.chkHistStdDev.AutoSize = true;
            this.chkHistStdDev.Location = new System.Drawing.Point(94, 20);
            this.chkHistStdDev.Name = "chkHistStdDev";
            this.chkHistStdDev.Size = new System.Drawing.Size(65, 17);
            this.chkHistStdDev.TabIndex = 1;
            this.chkHistStdDev.Text = "Std Dev";
            this.chkHistStdDev.UseVisualStyleBackColor = true;
            // 
            // chkHistMean
            // 
            this.chkHistMean.AutoSize = true;
            this.chkHistMean.Location = new System.Drawing.Point(15, 20);
            this.chkHistMean.Name = "chkHistMean";
            this.chkHistMean.Size = new System.Drawing.Size(53, 17);
            this.chkHistMean.TabIndex = 0;
            this.chkHistMean.Text = "Mean";
            this.chkHistMean.UseVisualStyleBackColor = true;
            // 
            // grpTexture
            // 
            this.grpTexture.Controls.Add(this.btnSelectAllTex);
            this.grpTexture.Controls.Add(this.chkIncludeZero);
            this.grpTexture.Controls.Add(this.lblTexDistance);
            this.grpTexture.Controls.Add(this.cboTexDistance);
            this.grpTexture.Controls.Add(this.chkTexEntropy);
            this.grpTexture.Controls.Add(this.chkTexInvDiff);
            this.grpTexture.Controls.Add(this.chkTexCorrelation);
            this.grpTexture.Controls.Add(this.chkTexInertia);
            this.grpTexture.Controls.Add(this.chkTexEnergy);
            this.grpTexture.Location = new System.Drawing.Point(8, 379);
            this.grpTexture.Name = "grpTexture";
            this.grpTexture.Size = new System.Drawing.Size(519, 84);
            this.grpTexture.TabIndex = 18;
            this.grpTexture.TabStop = false;
            this.grpTexture.Text = "Texture Features";
            // 
            // btnSelectAllTex
            // 
            this.btnSelectAllTex.Location = new System.Drawing.Point(430, 46);
            this.btnSelectAllTex.Name = "btnSelectAllTex";
            this.btnSelectAllTex.Size = new System.Drawing.Size(75, 23);
            this.btnSelectAllTex.TabIndex = 8;
            this.btnSelectAllTex.Text = "Select All";
            this.btnSelectAllTex.UseVisualStyleBackColor = true;
            this.btnSelectAllTex.Click += new System.EventHandler(this.btnSelectAllTex_Click);
            // 
            // chkIncludeZero
            // 
            this.chkIncludeZero.AutoSize = true;
            this.chkIncludeZero.Location = new System.Drawing.Point(215, 50);
            this.chkIncludeZero.Name = "chkIncludeZero";
            this.chkIncludeZero.Size = new System.Drawing.Size(112, 17);
            this.chkIncludeZero.TabIndex = 7;
            this.chkIncludeZero.Text = "Include Zero Pairs";
            this.chkIncludeZero.UseVisualStyleBackColor = true;
            // 
            // lblTexDistance
            // 
            this.lblTexDistance.AutoSize = true;
            this.lblTexDistance.Location = new System.Drawing.Point(13, 51);
            this.lblTexDistance.Name = "lblTexDistance";
            this.lblTexDistance.Size = new System.Drawing.Size(121, 13);
            this.lblTexDistance.TabIndex = 6;
            this.lblTexDistance.Text = "Texture distance (pixels)";
            // 
            // cboTexDistance
            // 
            this.cboTexDistance.FormattingEnabled = true;
            this.cboTexDistance.Items.AddRange(new object[] {
            "1",
            "2",
            "3",
            "4",
            "5",
            "6"});
            this.cboTexDistance.Location = new System.Drawing.Point(142, 47);
            this.cboTexDistance.Name = "cboTexDistance";
            this.cboTexDistance.Size = new System.Drawing.Size(48, 21);
            this.cboTexDistance.TabIndex = 5;
            this.cboTexDistance.Text = "2";
            // 
            // chkTexEntropy
            // 
            this.chkTexEntropy.AutoSize = true;
            this.chkTexEntropy.Location = new System.Drawing.Point(349, 20);
            this.chkTexEntropy.Name = "chkTexEntropy";
            this.chkTexEntropy.Size = new System.Drawing.Size(62, 17);
            this.chkTexEntropy.TabIndex = 4;
            this.chkTexEntropy.Text = "Entropy";
            this.chkTexEntropy.UseVisualStyleBackColor = true;
            // 
            // chkTexInvDiff
            // 
            this.chkTexInvDiff.AutoSize = true;
            this.chkTexInvDiff.Location = new System.Drawing.Point(253, 20);
            this.chkTexInvDiff.Name = "chkTexInvDiff";
            this.chkTexInvDiff.Size = new System.Drawing.Size(80, 17);
            this.chkTexInvDiff.TabIndex = 3;
            this.chkTexInvDiff.Text = "Inverse Diff";
            this.chkTexInvDiff.UseVisualStyleBackColor = true;
            // 
            // chkTexCorrelation
            // 
            this.chkTexCorrelation.AutoSize = true;
            this.chkTexCorrelation.Location = new System.Drawing.Point(161, 20);
            this.chkTexCorrelation.Name = "chkTexCorrelation";
            this.chkTexCorrelation.Size = new System.Drawing.Size(76, 17);
            this.chkTexCorrelation.TabIndex = 2;
            this.chkTexCorrelation.Text = "Correlation";
            this.chkTexCorrelation.UseVisualStyleBackColor = true;
            // 
            // chkTexInertia
            // 
            this.chkTexInertia.AutoSize = true;
            this.chkTexInertia.Location = new System.Drawing.Point(90, 20);
            this.chkTexInertia.Name = "chkTexInertia";
            this.chkTexInertia.Size = new System.Drawing.Size(55, 17);
            this.chkTexInertia.TabIndex = 1;
            this.chkTexInertia.Text = "Inertia";
            this.chkTexInertia.UseVisualStyleBackColor = true;
            // 
            // chkTexEnergy
            // 
            this.chkTexEnergy.AutoSize = true;
            this.chkTexEnergy.Location = new System.Drawing.Point(15, 20);
            this.chkTexEnergy.Name = "chkTexEnergy";
            this.chkTexEnergy.Size = new System.Drawing.Size(59, 17);
            this.chkTexEnergy.TabIndex = 0;
            this.chkTexEnergy.Text = "Energy";
            this.chkTexEnergy.UseVisualStyleBackColor = true;
            // 
            // grpSpectral
            // 
            this.grpSpectral.Controls.Add(this.btnSpectral);
            this.grpSpectral.Controls.Add(this.lblNumSectors);
            this.grpSpectral.Controls.Add(this.txtNumSectors);
            this.grpSpectral.Controls.Add(this.lblNumRings);
            this.grpSpectral.Controls.Add(this.txtNumRings);
            this.grpSpectral.Controls.Add(this.chkSpectral);
            this.grpSpectral.Location = new System.Drawing.Point(8, 469);
            this.grpSpectral.Name = "grpSpectral";
            this.grpSpectral.Size = new System.Drawing.Size(519, 45);
            this.grpSpectral.TabIndex = 19;
            this.grpSpectral.TabStop = false;
            this.grpSpectral.Text = "Spectral Features";
            // 
            // btnSpectral
            // 
            this.btnSpectral.Location = new System.Drawing.Point(430, 14);
            this.btnSpectral.Name = "btnSpectral";
            this.btnSpectral.Size = new System.Drawing.Size(75, 23);
            this.btnSpectral.TabIndex = 5;
            this.btnSpectral.Text = "Select";
            this.btnSpectral.UseVisualStyleBackColor = true;
            this.btnSpectral.Click += new System.EventHandler(this.btnSpectral_Click);
            // 
            // lblNumSectors
            // 
            this.lblNumSectors.AutoSize = true;
            this.lblNumSectors.Location = new System.Drawing.Point(284, 20);
            this.lblNumSectors.Name = "lblNumSectors";
            this.lblNumSectors.Size = new System.Drawing.Size(95, 13);
            this.lblNumSectors.TabIndex = 4;
            this.lblNumSectors.Text = "Number of Sectors";
            // 
            // txtNumSectors
            // 
            this.txtNumSectors.Location = new System.Drawing.Point(381, 16);
            this.txtNumSectors.Name = "txtNumSectors";
            this.txtNumSectors.Size = new System.Drawing.Size(38, 20);
            this.txtNumSectors.TabIndex = 3;
            this.txtNumSectors.Text = "3";
            // 
            // lblNumRings
            // 
            this.lblNumRings.AutoSize = true;
            this.lblNumRings.Location = new System.Drawing.Point(151, 20);
            this.lblNumRings.Name = "lblNumRings";
            this.lblNumRings.Size = new System.Drawing.Size(81, 13);
            this.lblNumRings.TabIndex = 2;
            this.lblNumRings.Text = "Number of rings";
            // 
            // txtNumRings
            // 
            this.txtNumRings.Location = new System.Drawing.Point(234, 16);
            this.txtNumRings.Name = "txtNumRings";
            this.txtNumRings.Size = new System.Drawing.Size(38, 20);
            this.txtNumRings.TabIndex = 1;
            this.txtNumRings.Text = "3";
            // 
            // chkSpectral
            // 
            this.chkSpectral.AutoSize = true;
            this.chkSpectral.Location = new System.Drawing.Point(15, 20);
            this.chkSpectral.Name = "chkSpectral";
            this.chkSpectral.Size = new System.Drawing.Size(129, 17);
            this.chkSpectral.TabIndex = 0;
            this.chkSpectral.Text = "Get Spectral Features";
            this.chkSpectral.UseVisualStyleBackColor = true;
            // 
            // btnHelp
            // 
            this.btnHelp.BackColor = System.Drawing.Color.Yellow;
            this.btnHelp.Location = new System.Drawing.Point(17, 515);
            this.btnHelp.Name = "btnHelp";
            this.btnHelp.Size = new System.Drawing.Size(60, 26);
            this.btnHelp.TabIndex = 20;
            this.btnHelp.Text = "Help";
            this.btnHelp.UseVisualStyleBackColor = false;
            this.btnHelp.Click += new System.EventHandler(this.btnHelp_Click);
            // 
            // btnCancel
            // 
            this.btnCancel.BackColor = System.Drawing.Color.OrangeRed;
            this.btnCancel.CausesValidation = false;
            this.btnCancel.Location = new System.Drawing.Point(389, 515);
            this.btnCancel.Name = "btnCancel";
            this.btnCancel.Size = new System.Drawing.Size(60, 26);
            this.btnCancel.TabIndex = 21;
            this.btnCancel.Text = "Cancel";
            this.btnCancel.UseVisualStyleBackColor = false;
            this.btnCancel.Click += new System.EventHandler(this.btnCancel_Click);
            // 
            // btnReset
            // 
            this.btnReset.BackColor = System.Drawing.Color.CornflowerBlue;
            this.btnReset.CausesValidation = false;
            this.btnReset.Location = new System.Drawing.Point(488, 515);
            this.btnReset.Name = "btnReset";
            this.btnReset.Size = new System.Drawing.Size(60, 26);
            this.btnReset.TabIndex = 22;
            this.btnReset.Text = "Reset";
            this.btnReset.UseVisualStyleBackColor = false;
            this.btnReset.Click += new System.EventHandler(this.btnReset_Click);
            // 
            // btnApply
            // 
            this.btnApply.BackColor = System.Drawing.Color.LimeGreen;
            this.btnApply.ForeColor = System.Drawing.Color.White;
            this.btnApply.Location = new System.Drawing.Point(574, 515);
            this.btnApply.Name = "btnApply";
            this.btnApply.Size = new System.Drawing.Size(60, 26);
            this.btnApply.TabIndex = 23;
            this.btnApply.Text = "Apply";
            this.btnApply.UseVisualStyleBackColor = false;
            this.btnApply.Click += new System.EventHandler(this.btnApply_Click);
            // 
            // dlgFileOpen
            // 
            this.dlgFileOpen.CheckFileExists = false;
            this.dlgFileOpen.Filter = "All Files(*.*)|*.*\" + \"Text Documents (*.txt)|*.txt|";
            this.dlgFileOpen.FilterIndex = 2;
            this.dlgFileOpen.Title = "Choose Feature Filename";
            // 
            // grplaw
            // 
            this.grplaw.Controls.Add(this.button2);
            this.grplaw.Controls.Add(this.chklaw15);
            this.grplaw.Controls.Add(this.chklaw14);
            this.grplaw.Controls.Add(this.chklaw13);
            this.grplaw.Controls.Add(this.chklaw12);
            this.grplaw.Controls.Add(this.chklaw11);
            this.grplaw.Controls.Add(this.chklaw10);
            this.grplaw.Controls.Add(this.chklaw9);
            this.grplaw.Controls.Add(this.chklaw7);
            this.grplaw.Controls.Add(this.chklaw8);
            this.grplaw.Controls.Add(this.chklaw6);
            this.grplaw.Controls.Add(this.chklaw5);
            this.grplaw.Controls.Add(this.chklaw4);
            this.grplaw.Controls.Add(this.chklaw3);
            this.grplaw.Controls.Add(this.button1);
            this.grplaw.Controls.Add(this.chklaw2);
            this.grplaw.Controls.Add(this.chklaw1);
            this.grplaw.Location = new System.Drawing.Point(545, 152);
            this.grplaw.Name = "grplaw";
            this.grplaw.Size = new System.Drawing.Size(131, 362);
            this.grplaw.TabIndex = 19;
            this.grplaw.TabStop = false;
            this.grplaw.Text = "LawsTextureFeatures";
            this.grplaw.Enter += new System.EventHandler(this.grplaw_Enter);
            // 
            // button2
            // 
            this.button2.Location = new System.Drawing.Point(29, 306);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(74, 25);
            this.button2.TabIndex = 22;
            this.button2.Text = "Select All";
            this.button2.UseVisualStyleBackColor = true;
            this.button2.Click += new System.EventHandler(this.button2_Click);
            // 
            // chklaw15
            // 
            this.chklaw15.AutoSize = true;
            this.chklaw15.Location = new System.Drawing.Point(73, 247);
            this.chklaw15.Name = "chklaw15";
            this.chklaw15.Size = new System.Drawing.Size(42, 17);
            this.chklaw15.TabIndex = 21;
            this.chklaw15.Text = "RR";
            this.chklaw15.UseVisualStyleBackColor = true;
            // 
            // chklaw14
            // 
            this.chklaw14.AutoSize = true;
            this.chklaw14.Location = new System.Drawing.Point(73, 204);
            this.chklaw14.Name = "chklaw14";
            this.chklaw14.Size = new System.Drawing.Size(48, 17);
            this.chklaw14.TabIndex = 20;
            this.chklaw14.Text = "WW";
            this.chklaw14.UseVisualStyleBackColor = true;
            // 
            // chklaw13
            // 
            this.chklaw13.AutoSize = true;
            this.chklaw13.Location = new System.Drawing.Point(73, 165);
            this.chklaw13.Name = "chklaw13";
            this.chklaw13.Size = new System.Drawing.Size(45, 17);
            this.chklaw13.TabIndex = 19;
            this.chklaw13.Text = "WR";
            this.chklaw13.UseVisualStyleBackColor = true;
            // 
            // chklaw12
            // 
            this.chklaw12.AutoSize = true;
            this.chklaw12.Location = new System.Drawing.Point(73, 129);
            this.chklaw12.Name = "chklaw12";
            this.chklaw12.Size = new System.Drawing.Size(44, 17);
            this.chklaw12.TabIndex = 18;
            this.chklaw12.Text = "SW";
            this.chklaw12.UseVisualStyleBackColor = true;
            // 
            // chklaw11
            // 
            this.chklaw11.AutoSize = true;
            this.chklaw11.Location = new System.Drawing.Point(73, 97);
            this.chklaw11.Name = "chklaw11";
            this.chklaw11.Size = new System.Drawing.Size(41, 17);
            this.chklaw11.TabIndex = 17;
            this.chklaw11.Text = "SR";
            this.chklaw11.UseVisualStyleBackColor = true;
            // 
            // chklaw10
            // 
            this.chklaw10.AutoSize = true;
            this.chklaw10.Location = new System.Drawing.Point(73, 56);
            this.chklaw10.Name = "chklaw10";
            this.chklaw10.Size = new System.Drawing.Size(40, 17);
            this.chklaw10.TabIndex = 16;
            this.chklaw10.Text = "SS";
            this.chklaw10.UseVisualStyleBackColor = true;
            // 
            // chklaw9
            // 
            this.chklaw9.AutoSize = true;
            this.chklaw9.Location = new System.Drawing.Point(73, 20);
            this.chklaw9.Name = "chklaw9";
            this.chklaw9.Size = new System.Drawing.Size(44, 17);
            this.chklaw9.TabIndex = 15;
            this.chklaw9.Text = "EW";
            this.chklaw9.UseVisualStyleBackColor = true;
            // 
            // chklaw7
            // 
            this.chklaw7.AutoSize = true;
            this.chklaw7.Location = new System.Drawing.Point(16, 247);
            this.chklaw7.Name = "chklaw7";
            this.chklaw7.Size = new System.Drawing.Size(40, 17);
            this.chklaw7.TabIndex = 14;
            this.chklaw7.Text = "ES";
            this.chklaw7.UseVisualStyleBackColor = true;
            // 
            // chklaw8
            // 
            this.chklaw8.AutoSize = true;
            this.chklaw8.Location = new System.Drawing.Point(16, 279);
            this.chklaw8.Name = "chklaw8";
            this.chklaw8.Size = new System.Drawing.Size(41, 17);
            this.chklaw8.TabIndex = 13;
            this.chklaw8.Text = "ER";
            this.chklaw8.UseVisualStyleBackColor = true;
            // 
            // chklaw6
            // 
            this.chklaw6.AutoSize = true;
            this.chklaw6.Location = new System.Drawing.Point(15, 208);
            this.chklaw6.Name = "chklaw6";
            this.chklaw6.Size = new System.Drawing.Size(40, 17);
            this.chklaw6.TabIndex = 12;
            this.chklaw6.Text = "EE";
            this.chklaw6.UseVisualStyleBackColor = true;
            // 
            // chklaw5
            // 
            this.chklaw5.AutoSize = true;
            this.chklaw5.Location = new System.Drawing.Point(16, 165);
            this.chklaw5.Name = "chklaw5";
            this.chklaw5.Size = new System.Drawing.Size(43, 17);
            this.chklaw5.TabIndex = 11;
            this.chklaw5.Text = "LW";
            this.chklaw5.UseVisualStyleBackColor = true;
            // 
            // chklaw4
            // 
            this.chklaw4.AutoSize = true;
            this.chklaw4.Location = new System.Drawing.Point(13, 129);
            this.chklaw4.Name = "chklaw4";
            this.chklaw4.Size = new System.Drawing.Size(40, 17);
            this.chklaw4.TabIndex = 10;
            this.chklaw4.Text = "LR";
            this.chklaw4.UseVisualStyleBackColor = true;
            // 
            // chklaw3
            // 
            this.chklaw3.AutoSize = true;
            this.chklaw3.Location = new System.Drawing.Point(13, 97);
            this.chklaw3.Name = "chklaw3";
            this.chklaw3.Size = new System.Drawing.Size(39, 17);
            this.chklaw3.TabIndex = 9;
            this.chklaw3.Text = "LS";
            this.chklaw3.UseVisualStyleBackColor = true;
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(16, 400);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(75, 23);
            this.button1.TabIndex = 8;
            this.button1.Text = "Select All";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // chklaw2
            // 
            this.chklaw2.AutoSize = true;
            this.chklaw2.Location = new System.Drawing.Point(13, 56);
            this.chklaw2.Name = "chklaw2";
            this.chklaw2.Size = new System.Drawing.Size(39, 17);
            this.chklaw2.TabIndex = 1;
            this.chklaw2.Text = "LE";
            this.chklaw2.UseVisualStyleBackColor = true;
            // 
            // chklaw1
            // 
            this.chklaw1.AutoSize = true;
            this.chklaw1.Location = new System.Drawing.Point(13, 20);
            this.chklaw1.Name = "chklaw1";
            this.chklaw1.Size = new System.Drawing.Size(38, 17);
            this.chklaw1.TabIndex = 0;
            this.chklaw1.Text = "LL";
            this.chklaw1.UseVisualStyleBackColor = true;
            this.chklaw1.CheckedChanged += new System.EventHandler(this.chklaw1_CheckedChanged);
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.lblOriginalImage);
            this.groupBox1.Controls.Add(this.cboOriginalImage);
            this.groupBox1.Controls.Add(this.lblSegmentedImage);
            this.groupBox1.Controls.Add(this.cboSegmentedImage);
            this.groupBox1.Controls.Add(this.lblFeatureFile);
            this.groupBox1.Controls.Add(this.cboFeatureFile);
            this.groupBox1.Controls.Add(this.btnSaveAs);
            this.groupBox1.Controls.Add(this.lblClassName);
            this.groupBox1.Controls.Add(this.txtClassName);
            this.groupBox1.Controls.Add(this.lblFeatureCol);
            this.groupBox1.Controls.Add(this.txtFeatureCol);
            this.groupBox1.Controls.Add(this.btnViewLabeledImage);
            this.groupBox1.Controls.Add(this.lblFeatureRow);
            this.groupBox1.Controls.Add(this.btnViewFeatureFile);
            this.groupBox1.Controls.Add(this.txtFeatureRow);
            this.groupBox1.Location = new System.Drawing.Point(8, 2);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(668, 144);
            this.groupBox1.TabIndex = 24;
            this.groupBox1.TabStop = false;
            // 
            // btnExceltoText
            // 
            this.btnExceltoText.BackColor = System.Drawing.SystemColors.Control;
            this.btnExceltoText.BackgroundImageLayout = System.Windows.Forms.ImageLayout.None;
            this.btnExceltoText.Location = new System.Drawing.Point(102, 517);
            this.btnExceltoText.Name = "btnExceltoText";
            this.btnExceltoText.Size = new System.Drawing.Size(103, 23);
            this.btnExceltoText.TabIndex = 25;
            this.btnExceltoText.Text = "Excel to Text";
            this.btnExceltoText.UseVisualStyleBackColor = false;
            this.btnExceltoText.Click += new System.EventHandler(this.btnExceltoText_Click);
            // 
            // Features
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.btnExceltoText);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.grplaw);
            this.Controls.Add(this.btnApply);
            this.Controls.Add(this.btnReset);
            this.Controls.Add(this.btnCancel);
            this.Controls.Add(this.btnHelp);
            this.Controls.Add(this.grpSpectral);
            this.Controls.Add(this.grpTexture);
            this.Controls.Add(this.grpHistogram);
            this.Controls.Add(this.grpRST);
            this.Controls.Add(this.grpBinary);
            this.DoubleBuffered = true;
            this.Name = "Features";
            this.Size = new System.Drawing.Size(679, 555);
            this.grpBinary.ResumeLayout(false);
            this.grpBinary.PerformLayout();
            this.grpRST.ResumeLayout(false);
            this.grpRST.PerformLayout();
            this.grpHistogram.ResumeLayout(false);
            this.grpHistogram.PerformLayout();
            this.grpTexture.ResumeLayout(false);
            this.grpTexture.PerformLayout();
            this.grpSpectral.ResumeLayout(false);
            this.grpSpectral.PerformLayout();
            this.grplaw.ResumeLayout(false);
            this.grplaw.PerformLayout();
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.ComboBox cboOriginalImage;
        private System.Windows.Forms.Label lblOriginalImage;
        private System.Windows.Forms.ComboBox cboSegmentedImage;
        private System.Windows.Forms.Label lblSegmentedImage;
        private System.Windows.Forms.ComboBox cboFeatureFile;
        private System.Windows.Forms.Label lblFeatureFile;
        private System.Windows.Forms.Button btnSaveAs;
        private System.Windows.Forms.TextBox txtClassName;
        private System.Windows.Forms.Label lblClassName;
        private System.Windows.Forms.TextBox txtFeatureCol;
        private System.Windows.Forms.Label lblFeatureCol;
        private System.Windows.Forms.TextBox txtFeatureRow;
        private System.Windows.Forms.Label lblFeatureRow;
        private System.Windows.Forms.Button btnViewFeatureFile;
        private System.Windows.Forms.Button btnViewLabeledImage;
        private System.Windows.Forms.GroupBox grpBinary;
        private System.Windows.Forms.Button btnSelectAllBin;
        private System.Windows.Forms.Label lblProjHeight;
        private System.Windows.Forms.TextBox txtProjHeight;
        private System.Windows.Forms.Label lblProjWidth;
        private System.Windows.Forms.TextBox txtProjWidth;
        private System.Windows.Forms.CheckBox chkAspect;
        private System.Windows.Forms.CheckBox chkThinness;
        private System.Windows.Forms.CheckBox chkProjections;
        private System.Windows.Forms.CheckBox chkEuler;
        private System.Windows.Forms.CheckBox chkPerimeter;
        private System.Windows.Forms.CheckBox chkOrientation;
        private System.Windows.Forms.CheckBox chkCentroid;
        private System.Windows.Forms.CheckBox chkArea;
        private System.Windows.Forms.GroupBox grpRST;
        private System.Windows.Forms.Button btnSelectAllRst;
        private System.Windows.Forms.CheckBox chkRst7;
        private System.Windows.Forms.CheckBox chkRst6;
        private System.Windows.Forms.CheckBox chkRst5;
        private System.Windows.Forms.CheckBox chkRst4;
        private System.Windows.Forms.CheckBox chkRst3;
        private System.Windows.Forms.CheckBox chkRst2;
        private System.Windows.Forms.CheckBox chkRst1;
        private System.Windows.Forms.GroupBox grpHistogram;
        private System.Windows.Forms.Button btnSelectAllHist;
        private System.Windows.Forms.CheckBox chkHistEntropy;
        private System.Windows.Forms.CheckBox chkHistEnergy;
        private System.Windows.Forms.CheckBox chkHistSkew;
        private System.Windows.Forms.CheckBox chkHistStdDev;
        private System.Windows.Forms.CheckBox chkHistMean;
        private System.Windows.Forms.GroupBox grpTexture;
        private System.Windows.Forms.Button btnSelectAllTex;
        private System.Windows.Forms.CheckBox chkIncludeZero;
        private System.Windows.Forms.Label lblTexDistance;
        private System.Windows.Forms.ComboBox cboTexDistance;
        private System.Windows.Forms.CheckBox chkTexEntropy;
        private System.Windows.Forms.CheckBox chkTexInvDiff;
        private System.Windows.Forms.CheckBox chkTexCorrelation;
        private System.Windows.Forms.CheckBox chkTexInertia;
        private System.Windows.Forms.CheckBox chkTexEnergy;
        private System.Windows.Forms.GroupBox grpSpectral;
        private System.Windows.Forms.Button btnSpectral;
        private System.Windows.Forms.Label lblNumSectors;
        private System.Windows.Forms.TextBox txtNumSectors;
        private System.Windows.Forms.Label lblNumRings;
        private System.Windows.Forms.TextBox txtNumRings;
        private System.Windows.Forms.CheckBox chkSpectral;
        private System.Windows.Forms.Button btnHelp;
        private System.Windows.Forms.Button btnCancel;
        private System.Windows.Forms.Button btnReset;
        private System.Windows.Forms.Button btnApply;
        private System.Windows.Forms.OpenFileDialog dlgFileOpen;
        private System.Windows.Forms.GroupBox grplaw;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.CheckBox chklaw2;
        private System.Windows.Forms.CheckBox chklaw1;
        private System.Windows.Forms.CheckBox chklaw4;
        private System.Windows.Forms.CheckBox chklaw3;
        private System.Windows.Forms.CheckBox chklaw5;
        private System.Windows.Forms.CheckBox chklaw6;
        private System.Windows.Forms.CheckBox chklaw9;
        private System.Windows.Forms.CheckBox chklaw7;
        private System.Windows.Forms.CheckBox chklaw8;
        private System.Windows.Forms.CheckBox chklaw12;
        private System.Windows.Forms.CheckBox chklaw11;
        private System.Windows.Forms.CheckBox chklaw10;
        private System.Windows.Forms.CheckBox chklaw13;
        private System.Windows.Forms.CheckBox chklaw15;
        private System.Windows.Forms.CheckBox chklaw14;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.Button btnExceltoText;
    }
}
