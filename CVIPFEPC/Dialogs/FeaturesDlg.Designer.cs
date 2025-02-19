namespace CVIPFEPC.Dialogs
{
    partial class FeaturesDlg
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
            this.grpBinary = new System.Windows.Forms.GroupBox();
            this.btnBinSelectNone = new System.Windows.Forms.Button();
            this.btnBinSelectAll = new System.Windows.Forms.Button();
            this.lblProjHeight = new System.Windows.Forms.Label();
            this.txtProjHeight = new System.Windows.Forms.TextBox();
            this.lblProjWidth = new System.Windows.Forms.Label();
            this.txtProjWidth = new System.Windows.Forms.TextBox();
            this.chkBinThinness = new System.Windows.Forms.CheckBox();
            this.chkBinProjections = new System.Windows.Forms.CheckBox();
            this.chkBinPerimeter = new System.Windows.Forms.CheckBox();
            this.chkBinOrientation = new System.Windows.Forms.CheckBox();
            this.chkBinEuler = new System.Windows.Forms.CheckBox();
            this.chkBinCentroid = new System.Windows.Forms.CheckBox();
            this.chkBinAspect = new System.Windows.Forms.CheckBox();
            this.chkBinArea = new System.Windows.Forms.CheckBox();
            this.grpHistogram = new System.Windows.Forms.GroupBox();
            this.btnHistSelectNone = new System.Windows.Forms.Button();
            this.btnHistSelectAll = new System.Windows.Forms.Button();
            this.chkHistEntropy = new System.Windows.Forms.CheckBox();
            this.chkHistEnergy = new System.Windows.Forms.CheckBox();
            this.chkHistSkew = new System.Windows.Forms.CheckBox();
            this.chkHistStdDev = new System.Windows.Forms.CheckBox();
            this.chkHistMean = new System.Windows.Forms.CheckBox();
            this.grpRST = new System.Windows.Forms.GroupBox();
            this.btnRstSelectNone = new System.Windows.Forms.Button();
            this.btnRstSelectAll = new System.Windows.Forms.Button();
            this.chkRst7 = new System.Windows.Forms.CheckBox();
            this.chkRst6 = new System.Windows.Forms.CheckBox();
            this.chkRst5 = new System.Windows.Forms.CheckBox();
            this.chkRst4 = new System.Windows.Forms.CheckBox();
            this.chkRst3 = new System.Windows.Forms.CheckBox();
            this.chkRst2 = new System.Windows.Forms.CheckBox();
            this.chkRst1 = new System.Windows.Forms.CheckBox();
            this.grpTexture = new System.Windows.Forms.GroupBox();
            this.upperTD = new System.Windows.Forms.Label();
            this.incrementTD = new System.Windows.Forms.Label();
            this.lowerTD = new System.Windows.Forms.Label();
            this.textboxUpper = new System.Windows.Forms.TextBox();
            this.textboxIncrement = new System.Windows.Forms.TextBox();
            this.textboxLower = new System.Windows.Forms.TextBox();
            this.rbOldTexture = new System.Windows.Forms.RadioButton();
            this.rbTexture2 = new System.Windows.Forms.RadioButton();
            this.btnTextSelectNone = new System.Windows.Forms.Button();
            this.btnTextSelectAll = new System.Windows.Forms.Button();
            this.lblTextDistance = new System.Windows.Forms.Label();
            this.cboTextDistance = new System.Windows.Forms.ComboBox();
            this.chkTextEntropy = new System.Windows.Forms.CheckBox();
            this.chkTextInvDiff = new System.Windows.Forms.CheckBox();
            this.chkTextCorrelation = new System.Windows.Forms.CheckBox();
            this.chkTextInertia = new System.Windows.Forms.CheckBox();
            this.chkTextEnergy = new System.Windows.Forms.CheckBox();
            this.grpSpectral = new System.Windows.Forms.GroupBox();
            this.lblSpectralSectors = new System.Windows.Forms.Label();
            this.txtSpectralSectors = new System.Windows.Forms.TextBox();
            this.lblSpectralRings = new System.Windows.Forms.Label();
            this.txtSpectralRings = new System.Windows.Forms.TextBox();
            this.chkSpectral = new System.Windows.Forms.CheckBox();
            this.btnCancel = new System.Windows.Forms.Button();
            this.btnReset = new System.Windows.Forms.Button();
            this.btnOK = new System.Windows.Forms.Button();
            this.btnSwitchToSingleSelect = new System.Windows.Forms.Button();
            this.btnSwitchToMultiSelect = new System.Windows.Forms.Button();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.btnLawSelectNone = new System.Windows.Forms.Button();
            this.btnLawSelectAll = new System.Windows.Forms.Button();
            this.chklaw4 = new System.Windows.Forms.CheckBox();
            this.chklaw3 = new System.Windows.Forms.CheckBox();
            this.chklaw6 = new System.Windows.Forms.CheckBox();
            this.chklaw5 = new System.Windows.Forms.CheckBox();
            this.chklaw1 = new System.Windows.Forms.CheckBox();
            this.chklaw14 = new System.Windows.Forms.CheckBox();
            this.chklaw15 = new System.Windows.Forms.CheckBox();
            this.chklaw13 = new System.Windows.Forms.CheckBox();
            this.chklaw12 = new System.Windows.Forms.CheckBox();
            this.chklaw11 = new System.Windows.Forms.CheckBox();
            this.chklaw10 = new System.Windows.Forms.CheckBox();
            this.chklaw8 = new System.Windows.Forms.CheckBox();
            this.chklaw9 = new System.Windows.Forms.CheckBox();
            this.chklaw7 = new System.Windows.Forms.CheckBox();
            this.chklaw2 = new System.Windows.Forms.CheckBox();
            this.grpBinary.SuspendLayout();
            this.grpHistogram.SuspendLayout();
            this.grpRST.SuspendLayout();
            this.grpTexture.SuspendLayout();
            this.grpSpectral.SuspendLayout();
            this.groupBox1.SuspendLayout();
            this.SuspendLayout();
            // 
            // grpBinary
            // 
            this.grpBinary.Controls.Add(this.btnBinSelectNone);
            this.grpBinary.Controls.Add(this.btnBinSelectAll);
            this.grpBinary.Controls.Add(this.lblProjHeight);
            this.grpBinary.Controls.Add(this.txtProjHeight);
            this.grpBinary.Controls.Add(this.lblProjWidth);
            this.grpBinary.Controls.Add(this.txtProjWidth);
            this.grpBinary.Controls.Add(this.chkBinThinness);
            this.grpBinary.Controls.Add(this.chkBinProjections);
            this.grpBinary.Controls.Add(this.chkBinPerimeter);
            this.grpBinary.Controls.Add(this.chkBinOrientation);
            this.grpBinary.Controls.Add(this.chkBinEuler);
            this.grpBinary.Controls.Add(this.chkBinCentroid);
            this.grpBinary.Controls.Add(this.chkBinAspect);
            this.grpBinary.Controls.Add(this.chkBinArea);
            this.grpBinary.Location = new System.Drawing.Point(26, 20);
            this.grpBinary.Name = "grpBinary";
            this.grpBinary.Size = new System.Drawing.Size(447, 118);
            this.grpBinary.TabIndex = 0;
            this.grpBinary.TabStop = false;
            this.grpBinary.Text = "Binary Features";
            // 
            // btnBinSelectNone
            // 
            this.btnBinSelectNone.Location = new System.Drawing.Point(345, 62);
            this.btnBinSelectNone.Name = "btnBinSelectNone";
            this.btnBinSelectNone.Size = new System.Drawing.Size(75, 23);
            this.btnBinSelectNone.TabIndex = 13;
            this.btnBinSelectNone.Text = "Select None";
            this.btnBinSelectNone.UseVisualStyleBackColor = true;
            this.btnBinSelectNone.Click += new System.EventHandler(this.btnBinSelectNone_Click);
            // 
            // btnBinSelectAll
            // 
            this.btnBinSelectAll.Location = new System.Drawing.Point(345, 32);
            this.btnBinSelectAll.Name = "btnBinSelectAll";
            this.btnBinSelectAll.Size = new System.Drawing.Size(75, 23);
            this.btnBinSelectAll.TabIndex = 12;
            this.btnBinSelectAll.Text = "Select All";
            this.btnBinSelectAll.UseVisualStyleBackColor = true;
            this.btnBinSelectAll.Click += new System.EventHandler(this.btnBinSelectAll_Click);
            // 
            // lblProjHeight
            // 
            this.lblProjHeight.AutoSize = true;
            this.lblProjHeight.Location = new System.Drawing.Point(265, 84);
            this.lblProjHeight.Name = "lblProjHeight";
            this.lblProjHeight.Size = new System.Drawing.Size(39, 13);
            this.lblProjHeight.TabIndex = 11;
            this.lblProjHeight.Text = "height:";
            // 
            // txtProjHeight
            // 
            this.txtProjHeight.Location = new System.Drawing.Point(303, 81);
            this.txtProjHeight.Name = "txtProjHeight";
            this.txtProjHeight.Size = new System.Drawing.Size(30, 20);
            this.txtProjHeight.TabIndex = 10;
            this.txtProjHeight.Text = "10";
            this.txtProjHeight.Validating += new System.ComponentModel.CancelEventHandler(this.txtIntVal_Validating);
            this.txtProjHeight.Validated += new System.EventHandler(this.ValueChanged);
            // 
            // lblProjWidth
            // 
            this.lblProjWidth.AutoSize = true;
            this.lblProjWidth.Location = new System.Drawing.Point(20, 84);
            this.lblProjWidth.Name = "lblProjWidth";
            this.lblProjWidth.Size = new System.Drawing.Size(210, 13);
            this.lblProjWidth.TabIndex = 9;
            this.lblProjWidth.Text = "For projections, enter the normalizing width:";
            // 
            // txtProjWidth
            // 
            this.txtProjWidth.Location = new System.Drawing.Point(229, 81);
            this.txtProjWidth.Name = "txtProjWidth";
            this.txtProjWidth.Size = new System.Drawing.Size(30, 20);
            this.txtProjWidth.TabIndex = 8;
            this.txtProjWidth.Text = "10";
            this.txtProjWidth.Validating += new System.ComponentModel.CancelEventHandler(this.txtIntVal_Validating);
            this.txtProjWidth.Validated += new System.EventHandler(this.ValueChanged);
            // 
            // chkBinThinness
            // 
            this.chkBinThinness.AutoSize = true;
            this.chkBinThinness.Location = new System.Drawing.Point(270, 48);
            this.chkBinThinness.Name = "chkBinThinness";
            this.chkBinThinness.Size = new System.Drawing.Size(69, 17);
            this.chkBinThinness.TabIndex = 7;
            this.chkBinThinness.Text = "Thinness";
            this.chkBinThinness.UseVisualStyleBackColor = true;
            this.chkBinThinness.Click += new System.EventHandler(this.ValueChanged);
            // 
            // chkBinProjections
            // 
            this.chkBinProjections.AutoSize = true;
            this.chkBinProjections.Location = new System.Drawing.Point(187, 48);
            this.chkBinProjections.Name = "chkBinProjections";
            this.chkBinProjections.Size = new System.Drawing.Size(78, 17);
            this.chkBinProjections.TabIndex = 6;
            this.chkBinProjections.Text = "Projections";
            this.chkBinProjections.UseVisualStyleBackColor = true;
            this.chkBinProjections.Click += new System.EventHandler(this.ValueChanged);
            // 
            // chkBinPerimeter
            // 
            this.chkBinPerimeter.AutoSize = true;
            this.chkBinPerimeter.Location = new System.Drawing.Point(103, 48);
            this.chkBinPerimeter.Name = "chkBinPerimeter";
            this.chkBinPerimeter.Size = new System.Drawing.Size(70, 17);
            this.chkBinPerimeter.TabIndex = 5;
            this.chkBinPerimeter.Text = "Perimeter";
            this.chkBinPerimeter.UseVisualStyleBackColor = true;
            this.chkBinPerimeter.Click += new System.EventHandler(this.ValueChanged);
            // 
            // chkBinOrientation
            // 
            this.chkBinOrientation.AutoSize = true;
            this.chkBinOrientation.Location = new System.Drawing.Point(20, 48);
            this.chkBinOrientation.Name = "chkBinOrientation";
            this.chkBinOrientation.Size = new System.Drawing.Size(77, 17);
            this.chkBinOrientation.TabIndex = 4;
            this.chkBinOrientation.Text = "Orientation";
            this.chkBinOrientation.UseVisualStyleBackColor = true;
            this.chkBinOrientation.Click += new System.EventHandler(this.ValueChanged);
            // 
            // chkBinEuler
            // 
            this.chkBinEuler.AutoSize = true;
            this.chkBinEuler.Location = new System.Drawing.Point(270, 24);
            this.chkBinEuler.Name = "chkBinEuler";
            this.chkBinEuler.Size = new System.Drawing.Size(50, 17);
            this.chkBinEuler.TabIndex = 3;
            this.chkBinEuler.Text = "Euler";
            this.chkBinEuler.UseVisualStyleBackColor = true;
            this.chkBinEuler.Click += new System.EventHandler(this.ValueChanged);
            // 
            // chkBinCentroid
            // 
            this.chkBinCentroid.AutoSize = true;
            this.chkBinCentroid.Location = new System.Drawing.Point(187, 24);
            this.chkBinCentroid.Name = "chkBinCentroid";
            this.chkBinCentroid.Size = new System.Drawing.Size(65, 17);
            this.chkBinCentroid.TabIndex = 2;
            this.chkBinCentroid.Text = "Centroid";
            this.chkBinCentroid.UseVisualStyleBackColor = true;
            this.chkBinCentroid.Click += new System.EventHandler(this.ValueChanged);
            // 
            // chkBinAspect
            // 
            this.chkBinAspect.AutoSize = true;
            this.chkBinAspect.Location = new System.Drawing.Point(103, 24);
            this.chkBinAspect.Name = "chkBinAspect";
            this.chkBinAspect.Size = new System.Drawing.Size(59, 17);
            this.chkBinAspect.TabIndex = 1;
            this.chkBinAspect.Text = "Aspect";
            this.chkBinAspect.UseVisualStyleBackColor = true;
            this.chkBinAspect.Click += new System.EventHandler(this.ValueChanged);
            // 
            // chkBinArea
            // 
            this.chkBinArea.AutoSize = true;
            this.chkBinArea.Location = new System.Drawing.Point(20, 24);
            this.chkBinArea.Name = "chkBinArea";
            this.chkBinArea.Size = new System.Drawing.Size(48, 17);
            this.chkBinArea.TabIndex = 0;
            this.chkBinArea.Text = "Area";
            this.chkBinArea.UseVisualStyleBackColor = true;
            this.chkBinArea.Click += new System.EventHandler(this.ValueChanged);
            // 
            // grpHistogram
            // 
            this.grpHistogram.Controls.Add(this.btnHistSelectNone);
            this.grpHistogram.Controls.Add(this.btnHistSelectAll);
            this.grpHistogram.Controls.Add(this.chkHistEntropy);
            this.grpHistogram.Controls.Add(this.chkHistEnergy);
            this.grpHistogram.Controls.Add(this.chkHistSkew);
            this.grpHistogram.Controls.Add(this.chkHistStdDev);
            this.grpHistogram.Controls.Add(this.chkHistMean);
            this.grpHistogram.Location = new System.Drawing.Point(26, 147);
            this.grpHistogram.Name = "grpHistogram";
            this.grpHistogram.Size = new System.Drawing.Size(140, 220);
            this.grpHistogram.TabIndex = 1;
            this.grpHistogram.TabStop = false;
            this.grpHistogram.Text = "Histogram Features";
            // 
            // btnHistSelectNone
            // 
            this.btnHistSelectNone.Location = new System.Drawing.Point(33, 177);
            this.btnHistSelectNone.Name = "btnHistSelectNone";
            this.btnHistSelectNone.Size = new System.Drawing.Size(75, 23);
            this.btnHistSelectNone.TabIndex = 6;
            this.btnHistSelectNone.Text = "Select None";
            this.btnHistSelectNone.UseVisualStyleBackColor = true;
            this.btnHistSelectNone.Click += new System.EventHandler(this.btnHistSelectNone_Click);
            // 
            // btnHistSelectAll
            // 
            this.btnHistSelectAll.Location = new System.Drawing.Point(33, 147);
            this.btnHistSelectAll.Name = "btnHistSelectAll";
            this.btnHistSelectAll.Size = new System.Drawing.Size(75, 23);
            this.btnHistSelectAll.TabIndex = 5;
            this.btnHistSelectAll.Text = "SelectAll";
            this.btnHistSelectAll.UseVisualStyleBackColor = true;
            this.btnHistSelectAll.Click += new System.EventHandler(this.btnHistSelectAll_Click);
            // 
            // chkHistEntropy
            // 
            this.chkHistEntropy.AutoSize = true;
            this.chkHistEntropy.Location = new System.Drawing.Point(20, 115);
            this.chkHistEntropy.Name = "chkHistEntropy";
            this.chkHistEntropy.Size = new System.Drawing.Size(62, 17);
            this.chkHistEntropy.TabIndex = 4;
            this.chkHistEntropy.Text = "Entropy";
            this.chkHistEntropy.UseVisualStyleBackColor = true;
            this.chkHistEntropy.Click += new System.EventHandler(this.ValueChanged);
            // 
            // chkHistEnergy
            // 
            this.chkHistEnergy.AutoSize = true;
            this.chkHistEnergy.Location = new System.Drawing.Point(20, 92);
            this.chkHistEnergy.Name = "chkHistEnergy";
            this.chkHistEnergy.Size = new System.Drawing.Size(59, 17);
            this.chkHistEnergy.TabIndex = 3;
            this.chkHistEnergy.Text = "Energy";
            this.chkHistEnergy.UseVisualStyleBackColor = true;
            this.chkHistEnergy.Click += new System.EventHandler(this.ValueChanged);
            // 
            // chkHistSkew
            // 
            this.chkHistSkew.AutoSize = true;
            this.chkHistSkew.Location = new System.Drawing.Point(20, 69);
            this.chkHistSkew.Name = "chkHistSkew";
            this.chkHistSkew.Size = new System.Drawing.Size(53, 17);
            this.chkHistSkew.TabIndex = 2;
            this.chkHistSkew.Text = "Skew";
            this.chkHistSkew.UseVisualStyleBackColor = true;
            this.chkHistSkew.Click += new System.EventHandler(this.ValueChanged);
            // 
            // chkHistStdDev
            // 
            this.chkHistStdDev.AutoSize = true;
            this.chkHistStdDev.Location = new System.Drawing.Point(20, 47);
            this.chkHistStdDev.Name = "chkHistStdDev";
            this.chkHistStdDev.Size = new System.Drawing.Size(62, 17);
            this.chkHistStdDev.TabIndex = 1;
            this.chkHistStdDev.Text = "StdDev";
            this.chkHistStdDev.UseVisualStyleBackColor = true;
            this.chkHistStdDev.Click += new System.EventHandler(this.ValueChanged);
            // 
            // chkHistMean
            // 
            this.chkHistMean.AutoSize = true;
            this.chkHistMean.Location = new System.Drawing.Point(20, 24);
            this.chkHistMean.Name = "chkHistMean";
            this.chkHistMean.Size = new System.Drawing.Size(53, 17);
            this.chkHistMean.TabIndex = 0;
            this.chkHistMean.Text = "Mean";
            this.chkHistMean.UseVisualStyleBackColor = true;
            this.chkHistMean.Click += new System.EventHandler(this.ValueChanged);
            // 
            // grpRST
            // 
            this.grpRST.Controls.Add(this.btnRstSelectNone);
            this.grpRST.Controls.Add(this.btnRstSelectAll);
            this.grpRST.Controls.Add(this.chkRst7);
            this.grpRST.Controls.Add(this.chkRst6);
            this.grpRST.Controls.Add(this.chkRst5);
            this.grpRST.Controls.Add(this.chkRst4);
            this.grpRST.Controls.Add(this.chkRst3);
            this.grpRST.Controls.Add(this.chkRst2);
            this.grpRST.Controls.Add(this.chkRst1);
            this.grpRST.Location = new System.Drawing.Point(179, 147);
            this.grpRST.Name = "grpRST";
            this.grpRST.Size = new System.Drawing.Size(140, 220);
            this.grpRST.TabIndex = 2;
            this.grpRST.TabStop = false;
            this.grpRST.Text = "RST-Invariant Features";
            // 
            // btnRstSelectNone
            // 
            this.btnRstSelectNone.Location = new System.Drawing.Point(33, 177);
            this.btnRstSelectNone.Name = "btnRstSelectNone";
            this.btnRstSelectNone.Size = new System.Drawing.Size(75, 23);
            this.btnRstSelectNone.TabIndex = 8;
            this.btnRstSelectNone.Text = "Select None";
            this.btnRstSelectNone.UseVisualStyleBackColor = true;
            this.btnRstSelectNone.Click += new System.EventHandler(this.btnRstSelectNone_Click);
            // 
            // btnRstSelectAll
            // 
            this.btnRstSelectAll.Location = new System.Drawing.Point(33, 147);
            this.btnRstSelectAll.Name = "btnRstSelectAll";
            this.btnRstSelectAll.Size = new System.Drawing.Size(75, 23);
            this.btnRstSelectAll.TabIndex = 7;
            this.btnRstSelectAll.Text = "Select All";
            this.btnRstSelectAll.UseVisualStyleBackColor = true;
            this.btnRstSelectAll.Click += new System.EventHandler(this.btnRstSelectAll_Click);
            // 
            // chkRst7
            // 
            this.chkRst7.AutoSize = true;
            this.chkRst7.Location = new System.Drawing.Point(20, 115);
            this.chkRst7.Name = "chkRst7";
            this.chkRst7.Size = new System.Drawing.Size(43, 17);
            this.chkRst7.TabIndex = 6;
            this.chkRst7.Text = "rst7";
            this.chkRst7.UseVisualStyleBackColor = true;
            this.chkRst7.Click += new System.EventHandler(this.ValueChanged);
            // 
            // chkRst6
            // 
            this.chkRst6.AutoSize = true;
            this.chkRst6.Location = new System.Drawing.Point(77, 100);
            this.chkRst6.Name = "chkRst6";
            this.chkRst6.Size = new System.Drawing.Size(43, 17);
            this.chkRst6.TabIndex = 5;
            this.chkRst6.Text = "rst6";
            this.chkRst6.UseVisualStyleBackColor = true;
            this.chkRst6.Click += new System.EventHandler(this.ValueChanged);
            // 
            // chkRst5
            // 
            this.chkRst5.AutoSize = true;
            this.chkRst5.Location = new System.Drawing.Point(20, 85);
            this.chkRst5.Name = "chkRst5";
            this.chkRst5.Size = new System.Drawing.Size(43, 17);
            this.chkRst5.TabIndex = 4;
            this.chkRst5.Text = "rst5";
            this.chkRst5.UseVisualStyleBackColor = true;
            this.chkRst5.Click += new System.EventHandler(this.ValueChanged);
            // 
            // chkRst4
            // 
            this.chkRst4.AutoSize = true;
            this.chkRst4.Location = new System.Drawing.Point(77, 69);
            this.chkRst4.Name = "chkRst4";
            this.chkRst4.Size = new System.Drawing.Size(43, 17);
            this.chkRst4.TabIndex = 3;
            this.chkRst4.Text = "rst4";
            this.chkRst4.UseVisualStyleBackColor = true;
            this.chkRst4.Click += new System.EventHandler(this.ValueChanged);
            // 
            // chkRst3
            // 
            this.chkRst3.AutoSize = true;
            this.chkRst3.Location = new System.Drawing.Point(20, 54);
            this.chkRst3.Name = "chkRst3";
            this.chkRst3.Size = new System.Drawing.Size(43, 17);
            this.chkRst3.TabIndex = 2;
            this.chkRst3.Text = "rst3";
            this.chkRst3.UseVisualStyleBackColor = true;
            this.chkRst3.Click += new System.EventHandler(this.ValueChanged);
            // 
            // chkRst2
            // 
            this.chkRst2.AutoSize = true;
            this.chkRst2.Location = new System.Drawing.Point(77, 39);
            this.chkRst2.Name = "chkRst2";
            this.chkRst2.Size = new System.Drawing.Size(43, 17);
            this.chkRst2.TabIndex = 1;
            this.chkRst2.Text = "rst2";
            this.chkRst2.UseVisualStyleBackColor = true;
            this.chkRst2.Click += new System.EventHandler(this.ValueChanged);
            // 
            // chkRst1
            // 
            this.chkRst1.AutoSize = true;
            this.chkRst1.Location = new System.Drawing.Point(20, 24);
            this.chkRst1.Name = "chkRst1";
            this.chkRst1.Size = new System.Drawing.Size(43, 17);
            this.chkRst1.TabIndex = 0;
            this.chkRst1.Text = "rst1";
            this.chkRst1.UseVisualStyleBackColor = true;
            this.chkRst1.Click += new System.EventHandler(this.ValueChanged);
            // 
            // grpTexture
            // 
            this.grpTexture.Controls.Add(this.upperTD);
            this.grpTexture.Controls.Add(this.incrementTD);
            this.grpTexture.Controls.Add(this.lowerTD);
            this.grpTexture.Controls.Add(this.textboxUpper);
            this.grpTexture.Controls.Add(this.textboxIncrement);
            this.grpTexture.Controls.Add(this.textboxLower);
            this.grpTexture.Controls.Add(this.rbOldTexture);
            this.grpTexture.Controls.Add(this.rbTexture2);
            this.grpTexture.Controls.Add(this.btnTextSelectNone);
            this.grpTexture.Controls.Add(this.btnTextSelectAll);
            this.grpTexture.Controls.Add(this.lblTextDistance);
            this.grpTexture.Controls.Add(this.cboTextDistance);
            this.grpTexture.Controls.Add(this.chkTextEntropy);
            this.grpTexture.Controls.Add(this.chkTextInvDiff);
            this.grpTexture.Controls.Add(this.chkTextCorrelation);
            this.grpTexture.Controls.Add(this.chkTextInertia);
            this.grpTexture.Controls.Add(this.chkTextEnergy);
            this.grpTexture.Location = new System.Drawing.Point(332, 147);
            this.grpTexture.Name = "grpTexture";
            this.grpTexture.Size = new System.Drawing.Size(140, 308);
            this.grpTexture.TabIndex = 3;
            this.grpTexture.TabStop = false;
            this.grpTexture.Text = "Texture Features";
            this.grpTexture.Enter += new System.EventHandler(this.grpTexture_Enter);
            // 
            // upperTD
            // 
            this.upperTD.AutoSize = true;
            this.upperTD.Location = new System.Drawing.Point(100, 142);
            this.upperTD.Name = "upperTD";
            this.upperTD.Size = new System.Drawing.Size(34, 13);
            this.upperTD.TabIndex = 16;
            this.upperTD.Text = "upper";
            this.upperTD.Visible = false;
            // 
            // incrementTD
            // 
            this.incrementTD.AutoSize = true;
            this.incrementTD.Location = new System.Drawing.Point(48, 142);
            this.incrementTD.Name = "incrementTD";
            this.incrementTD.Size = new System.Drawing.Size(53, 13);
            this.incrementTD.TabIndex = 15;
            this.incrementTD.Text = "increment";
            this.incrementTD.Visible = false;
            this.incrementTD.Click += new System.EventHandler(this.label2_Click);
            // 
            // lowerTD
            // 
            this.lowerTD.AutoSize = true;
            this.lowerTD.Location = new System.Drawing.Point(17, 142);
            this.lowerTD.Name = "lowerTD";
            this.lowerTD.Size = new System.Drawing.Size(32, 13);
            this.lowerTD.TabIndex = 14;
            this.lowerTD.Text = "lower";
            this.lowerTD.Visible = false;
            this.lowerTD.Click += new System.EventHandler(this.label1_Click);
            // 
            // textboxUpper
            // 
            this.textboxUpper.Location = new System.Drawing.Point(101, 158);
            this.textboxUpper.Name = "textboxUpper";
            this.textboxUpper.Size = new System.Drawing.Size(39, 20);
            this.textboxUpper.TabIndex = 13;
            this.textboxUpper.Text = "6";
            this.textboxUpper.Visible = false;
            // 
            // textboxIncrement
            // 
            this.textboxIncrement.Location = new System.Drawing.Point(67, 158);
            this.textboxIncrement.Name = "textboxIncrement";
            this.textboxIncrement.Size = new System.Drawing.Size(35, 20);
            this.textboxIncrement.TabIndex = 12;
            this.textboxIncrement.Text = "2";
            this.textboxIncrement.Visible = false;
            // 
            // textboxLower
            // 
            this.textboxLower.Location = new System.Drawing.Point(24, 158);
            this.textboxLower.Name = "textboxLower";
            this.textboxLower.Size = new System.Drawing.Size(43, 20);
            this.textboxLower.TabIndex = 11;
            this.textboxLower.Text = "2";
            this.textboxLower.Visible = false;
            this.textboxLower.TextChanged += new System.EventHandler(this.textBox1_TextChanged);
            // 
            // rbOldTexture
            // 
            this.rbOldTexture.AutoSize = true;
            this.rbOldTexture.Location = new System.Drawing.Point(21, 270);
            this.rbOldTexture.Name = "rbOldTexture";
            this.rbOldTexture.Size = new System.Drawing.Size(102, 17);
            this.rbOldTexture.TabIndex = 10;
            this.rbOldTexture.Text = "Use Old Texture";
            this.rbOldTexture.UseVisualStyleBackColor = true;
            this.rbOldTexture.CheckedChanged += new System.EventHandler(this.ValueChanged);
            // 
            // rbTexture2
            // 
            this.rbTexture2.AutoSize = true;
            this.rbTexture2.Checked = true;
            this.rbTexture2.Location = new System.Drawing.Point(21, 253);
            this.rbTexture2.Name = "rbTexture2";
            this.rbTexture2.Size = new System.Drawing.Size(89, 17);
            this.rbTexture2.TabIndex = 9;
            this.rbTexture2.TabStop = true;
            this.rbTexture2.Text = "Use Texture2";
            this.rbTexture2.UseVisualStyleBackColor = true;
            this.rbTexture2.CheckedChanged += new System.EventHandler(this.ValueChanged);
            // 
            // btnTextSelectNone
            // 
            this.btnTextSelectNone.Location = new System.Drawing.Point(33, 223);
            this.btnTextSelectNone.Name = "btnTextSelectNone";
            this.btnTextSelectNone.Size = new System.Drawing.Size(75, 23);
            this.btnTextSelectNone.TabIndex = 8;
            this.btnTextSelectNone.Text = "Select None";
            this.btnTextSelectNone.UseVisualStyleBackColor = true;
            this.btnTextSelectNone.Click += new System.EventHandler(this.btnTextSelectNone_Click);
            // 
            // btnTextSelectAll
            // 
            this.btnTextSelectAll.Location = new System.Drawing.Point(33, 194);
            this.btnTextSelectAll.Name = "btnTextSelectAll";
            this.btnTextSelectAll.Size = new System.Drawing.Size(75, 23);
            this.btnTextSelectAll.TabIndex = 7;
            this.btnTextSelectAll.Text = "Select All";
            this.btnTextSelectAll.UseVisualStyleBackColor = true;
            this.btnTextSelectAll.Click += new System.EventHandler(this.btnTextSelectAll_Click);
            // 
            // lblTextDistance
            // 
            this.lblTextDistance.AutoSize = true;
            this.lblTextDistance.Location = new System.Drawing.Point(28, 142);
            this.lblTextDistance.Name = "lblTextDistance";
            this.lblTextDistance.Size = new System.Drawing.Size(89, 13);
            this.lblTextDistance.TabIndex = 6;
            this.lblTextDistance.Text = "Texture distance:";
            // 
            // cboTextDistance
            // 
            this.cboTextDistance.FormattingEnabled = true;
            this.cboTextDistance.Items.AddRange(new object[] {
            "1",
            "2",
            "3",
            "4",
            "5",
            "6"});
            this.cboTextDistance.Location = new System.Drawing.Point(33, 161);
            this.cboTextDistance.Name = "cboTextDistance";
            this.cboTextDistance.Size = new System.Drawing.Size(75, 21);
            this.cboTextDistance.TabIndex = 5;
            this.cboTextDistance.Text = "2";
            this.cboTextDistance.SelectedIndexChanged += new System.EventHandler(this.cboTextDistance_SelectedIndexChanged);
            this.cboTextDistance.Validating += new System.ComponentModel.CancelEventHandler(this.cboIntVal_Validating);
            this.cboTextDistance.Validated += new System.EventHandler(this.ValueChanged);
            // 
            // chkTextEntropy
            // 
            this.chkTextEntropy.AutoSize = true;
            this.chkTextEntropy.Location = new System.Drawing.Point(20, 115);
            this.chkTextEntropy.Name = "chkTextEntropy";
            this.chkTextEntropy.Size = new System.Drawing.Size(62, 17);
            this.chkTextEntropy.TabIndex = 4;
            this.chkTextEntropy.Text = "Entropy";
            this.chkTextEntropy.UseVisualStyleBackColor = true;
            this.chkTextEntropy.Click += new System.EventHandler(this.ValueChanged);
            // 
            // chkTextInvDiff
            // 
            this.chkTextInvDiff.AutoSize = true;
            this.chkTextInvDiff.Location = new System.Drawing.Point(20, 92);
            this.chkTextInvDiff.Name = "chkTextInvDiff";
            this.chkTextInvDiff.Size = new System.Drawing.Size(80, 17);
            this.chkTextInvDiff.TabIndex = 3;
            this.chkTextInvDiff.Text = "Inverse Diff";
            this.chkTextInvDiff.UseVisualStyleBackColor = true;
            this.chkTextInvDiff.CheckedChanged += new System.EventHandler(this.chkTextInvDiff_CheckedChanged);
            this.chkTextInvDiff.Click += new System.EventHandler(this.ValueChanged);
            // 
            // chkTextCorrelation
            // 
            this.chkTextCorrelation.AutoSize = true;
            this.chkTextCorrelation.Location = new System.Drawing.Point(20, 69);
            this.chkTextCorrelation.Name = "chkTextCorrelation";
            this.chkTextCorrelation.Size = new System.Drawing.Size(76, 17);
            this.chkTextCorrelation.TabIndex = 2;
            this.chkTextCorrelation.Text = "Correlation";
            this.chkTextCorrelation.UseVisualStyleBackColor = true;
            this.chkTextCorrelation.Click += new System.EventHandler(this.ValueChanged);
            // 
            // chkTextInertia
            // 
            this.chkTextInertia.AutoSize = true;
            this.chkTextInertia.Location = new System.Drawing.Point(20, 47);
            this.chkTextInertia.Name = "chkTextInertia";
            this.chkTextInertia.Size = new System.Drawing.Size(55, 17);
            this.chkTextInertia.TabIndex = 1;
            this.chkTextInertia.Text = "Inertia";
            this.chkTextInertia.UseVisualStyleBackColor = true;
            this.chkTextInertia.Click += new System.EventHandler(this.ValueChanged);
            // 
            // chkTextEnergy
            // 
            this.chkTextEnergy.AutoSize = true;
            this.chkTextEnergy.Location = new System.Drawing.Point(20, 24);
            this.chkTextEnergy.Name = "chkTextEnergy";
            this.chkTextEnergy.Size = new System.Drawing.Size(59, 17);
            this.chkTextEnergy.TabIndex = 0;
            this.chkTextEnergy.Text = "Energy";
            this.chkTextEnergy.UseVisualStyleBackColor = true;
            this.chkTextEnergy.Click += new System.EventHandler(this.ValueChanged);
            // 
            // grpSpectral
            // 
            this.grpSpectral.Controls.Add(this.lblSpectralSectors);
            this.grpSpectral.Controls.Add(this.txtSpectralSectors);
            this.grpSpectral.Controls.Add(this.lblSpectralRings);
            this.grpSpectral.Controls.Add(this.txtSpectralRings);
            this.grpSpectral.Controls.Add(this.chkSpectral);
            this.grpSpectral.Location = new System.Drawing.Point(26, 375);
            this.grpSpectral.Name = "grpSpectral";
            this.grpSpectral.Size = new System.Drawing.Size(293, 80);
            this.grpSpectral.TabIndex = 4;
            this.grpSpectral.TabStop = false;
            this.grpSpectral.Text = "Spectral Features";
            // 
            // lblSpectralSectors
            // 
            this.lblSpectralSectors.AutoSize = true;
            this.lblSpectralSectors.Location = new System.Drawing.Point(194, 52);
            this.lblSpectralSectors.Name = "lblSpectralSectors";
            this.lblSpectralSectors.Size = new System.Drawing.Size(46, 13);
            this.lblSpectralSectors.TabIndex = 4;
            this.lblSpectralSectors.Text = "Sectors:";
            this.lblSpectralSectors.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // txtSpectralSectors
            // 
            this.txtSpectralSectors.Location = new System.Drawing.Point(240, 48);
            this.txtSpectralSectors.Name = "txtSpectralSectors";
            this.txtSpectralSectors.Size = new System.Drawing.Size(33, 20);
            this.txtSpectralSectors.TabIndex = 3;
            this.txtSpectralSectors.Text = "3";
            this.txtSpectralSectors.Validating += new System.ComponentModel.CancelEventHandler(this.txtIntVal_Validating);
            this.txtSpectralSectors.Validated += new System.EventHandler(this.ValueChanged);
            // 
            // lblSpectralRings
            // 
            this.lblSpectralRings.AutoSize = true;
            this.lblSpectralRings.Location = new System.Drawing.Point(203, 24);
            this.lblSpectralRings.Name = "lblSpectralRings";
            this.lblSpectralRings.Size = new System.Drawing.Size(37, 13);
            this.lblSpectralRings.TabIndex = 2;
            this.lblSpectralRings.Text = "Rings:";
            this.lblSpectralRings.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // txtSpectralRings
            // 
            this.txtSpectralRings.Location = new System.Drawing.Point(240, 20);
            this.txtSpectralRings.Name = "txtSpectralRings";
            this.txtSpectralRings.Size = new System.Drawing.Size(33, 20);
            this.txtSpectralRings.TabIndex = 1;
            this.txtSpectralRings.Text = "3";
            this.txtSpectralRings.Validating += new System.ComponentModel.CancelEventHandler(this.txtIntVal_Validating);
            this.txtSpectralRings.Validated += new System.EventHandler(this.ValueChanged);
            // 
            // chkSpectral
            // 
            this.chkSpectral.AutoSize = true;
            this.chkSpectral.Location = new System.Drawing.Point(20, 24);
            this.chkSpectral.Name = "chkSpectral";
            this.chkSpectral.Size = new System.Drawing.Size(131, 17);
            this.chkSpectral.TabIndex = 0;
            this.chkSpectral.Text = "Use Spectral Features";
            this.chkSpectral.UseVisualStyleBackColor = true;
            this.chkSpectral.Click += new System.EventHandler(this.ValueChanged);
            // 
            // btnCancel
            // 
            this.btnCancel.BackColor = System.Drawing.Color.OrangeRed;
            this.btnCancel.CausesValidation = false;
            this.btnCancel.DialogResult = System.Windows.Forms.DialogResult.Cancel;
            this.btnCancel.Location = new System.Drawing.Point(240, 475);
            this.btnCancel.Name = "btnCancel";
            this.btnCancel.Size = new System.Drawing.Size(75, 25);
            this.btnCancel.TabIndex = 5;
            this.btnCancel.Text = "Cancel";
            this.btnCancel.UseVisualStyleBackColor = false;
            // 
            // btnReset
            // 
            this.btnReset.BackColor = System.Drawing.Color.CornflowerBlue;
            this.btnReset.CausesValidation = false;
            this.btnReset.Enabled = false;
            this.btnReset.Location = new System.Drawing.Point(320, 475);
            this.btnReset.Name = "btnReset";
            this.btnReset.Size = new System.Drawing.Size(75, 25);
            this.btnReset.TabIndex = 6;
            this.btnReset.Text = "Reset";
            this.btnReset.UseVisualStyleBackColor = false;
            this.btnReset.Click += new System.EventHandler(this.btnReset_Click);
            // 
            // btnOK
            // 
            this.btnOK.BackColor = System.Drawing.Color.LimeGreen;
            this.btnOK.DialogResult = System.Windows.Forms.DialogResult.OK;
            this.btnOK.ForeColor = System.Drawing.Color.White;
            this.btnOK.Location = new System.Drawing.Point(400, 475);
            this.btnOK.Name = "btnOK";
            this.btnOK.Size = new System.Drawing.Size(75, 25);
            this.btnOK.TabIndex = 7;
            this.btnOK.Text = "OK";
            this.btnOK.UseVisualStyleBackColor = false;
            this.btnOK.Click += new System.EventHandler(this.btnOK_Click);
            // 
            // btnSwitchToSingleSelect
            // 
            this.btnSwitchToSingleSelect.Location = new System.Drawing.Point(9, 475);
            this.btnSwitchToSingleSelect.Name = "btnSwitchToSingleSelect";
            this.btnSwitchToSingleSelect.Size = new System.Drawing.Size(179, 25);
            this.btnSwitchToSingleSelect.TabIndex = 8;
            this.btnSwitchToSingleSelect.Text = "Switch to Single Test Mode";
            this.btnSwitchToSingleSelect.UseVisualStyleBackColor = true;
            this.btnSwitchToSingleSelect.Click += new System.EventHandler(this.btnSelectionMode_Click);
            // 
            // btnSwitchToMultiSelect
            // 
            this.btnSwitchToMultiSelect.Location = new System.Drawing.Point(9, 475);
            this.btnSwitchToMultiSelect.Name = "btnSwitchToMultiSelect";
            this.btnSwitchToMultiSelect.Size = new System.Drawing.Size(179, 25);
            this.btnSwitchToMultiSelect.TabIndex = 9;
            this.btnSwitchToMultiSelect.Text = "Switch to Combinatoric Test Mode";
            this.btnSwitchToMultiSelect.UseVisualStyleBackColor = true;
            this.btnSwitchToMultiSelect.Click += new System.EventHandler(this.btnSelectionMode_Click);
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.btnLawSelectNone);
            this.groupBox1.Controls.Add(this.btnLawSelectAll);
            this.groupBox1.Controls.Add(this.chklaw4);
            this.groupBox1.Controls.Add(this.chklaw3);
            this.groupBox1.Controls.Add(this.chklaw6);
            this.groupBox1.Controls.Add(this.chklaw5);
            this.groupBox1.Controls.Add(this.chklaw1);
            this.groupBox1.Controls.Add(this.chklaw14);
            this.groupBox1.Controls.Add(this.chklaw15);
            this.groupBox1.Controls.Add(this.chklaw13);
            this.groupBox1.Controls.Add(this.chklaw12);
            this.groupBox1.Controls.Add(this.chklaw11);
            this.groupBox1.Controls.Add(this.chklaw10);
            this.groupBox1.Controls.Add(this.chklaw8);
            this.groupBox1.Controls.Add(this.chklaw9);
            this.groupBox1.Controls.Add(this.chklaw7);
            this.groupBox1.Controls.Add(this.chklaw2);
            this.groupBox1.Location = new System.Drawing.Point(478, 20);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(130, 490);
            this.groupBox1.TabIndex = 17;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Laws Texture Features";
            this.groupBox1.Enter += new System.EventHandler(this.groupBox1_Enter);
            // 
            // btnLawSelectNone
            // 
            this.btnLawSelectNone.Location = new System.Drawing.Point(25, 455);
            this.btnLawSelectNone.Name = "btnLawSelectNone";
            this.btnLawSelectNone.Size = new System.Drawing.Size(75, 23);
            this.btnLawSelectNone.TabIndex = 17;
            this.btnLawSelectNone.Text = "Select None";
            this.btnLawSelectNone.UseVisualStyleBackColor = true;
            this.btnLawSelectNone.Click += new System.EventHandler(this.button2_Click);
            // 
            // btnLawSelectAll
            // 
            this.btnLawSelectAll.Location = new System.Drawing.Point(24, 427);
            this.btnLawSelectAll.Name = "btnLawSelectAll";
            this.btnLawSelectAll.Size = new System.Drawing.Size(75, 23);
            this.btnLawSelectAll.TabIndex = 17;
            this.btnLawSelectAll.Text = "Select All";
            this.btnLawSelectAll.UseVisualStyleBackColor = true;
            this.btnLawSelectAll.Click += new System.EventHandler(this.button1_Click);
            // 
            // chklaw4
            // 
            this.chklaw4.AutoSize = true;
            this.chklaw4.Location = new System.Drawing.Point(19, 101);
            this.chklaw4.Name = "chklaw4";
            this.chklaw4.Size = new System.Drawing.Size(82, 17);
            this.chklaw4.TabIndex = 40;
            this.chklaw4.Text = "LevelRipple";
            this.chklaw4.UseVisualStyleBackColor = false;
            this.chklaw4.CheckedChanged += new System.EventHandler(this.ValueChanged);
            // 
            // chklaw3
            // 
            this.chklaw3.AutoSize = true;
            this.chklaw3.Location = new System.Drawing.Point(19, 70);
            this.chklaw3.Name = "chklaw3";
            this.chklaw3.Size = new System.Drawing.Size(74, 17);
            this.chklaw3.TabIndex = 39;
            this.chklaw3.Text = "LevelSpot";
            this.chklaw3.UseVisualStyleBackColor = false;
            this.chklaw3.CheckedChanged += new System.EventHandler(this.ValueChanged);
            // 
            // chklaw6
            // 
            this.chklaw6.AutoSize = true;
            this.chklaw6.Location = new System.Drawing.Point(19, 155);
            this.chklaw6.Name = "chklaw6";
            this.chklaw6.Size = new System.Drawing.Size(76, 17);
            this.chklaw6.TabIndex = 38;
            this.chklaw6.Text = "EdgeEdge";
            this.chklaw6.UseVisualStyleBackColor = false;
            this.chklaw6.CheckedChanged += new System.EventHandler(this.ValueChanged);
            // 
            // chklaw5
            // 
            this.chklaw5.AutoSize = true;
            this.chklaw5.Location = new System.Drawing.Point(19, 127);
            this.chklaw5.Name = "chklaw5";
            this.chklaw5.Size = new System.Drawing.Size(81, 17);
            this.chklaw5.TabIndex = 37;
            this.chklaw5.Text = "LevelWave";
            this.chklaw5.UseVisualStyleBackColor = false;
            this.chklaw5.CheckedChanged += new System.EventHandler(this.ValueChanged);
            // 
            // chklaw1
            // 
            this.chklaw1.AutoSize = true;
            this.chklaw1.Location = new System.Drawing.Point(19, 19);
            this.chklaw1.Name = "chklaw1";
            this.chklaw1.Size = new System.Drawing.Size(78, 17);
            this.chklaw1.TabIndex = 36;
            this.chklaw1.Text = "LevelLevel";
            this.chklaw1.UseVisualStyleBackColor = false;
            this.chklaw1.CheckedChanged += new System.EventHandler(this.ValueChanged);
            // 
            // chklaw14
            // 
            this.chklaw14.AutoSize = true;
            this.chklaw14.Location = new System.Drawing.Point(19, 381);
            this.chklaw14.Name = "chklaw14";
            this.chklaw14.Size = new System.Drawing.Size(84, 17);
            this.chklaw14.TabIndex = 35;
            this.chklaw14.Text = "WaveWave";
            this.chklaw14.UseVisualStyleBackColor = false;
            this.chklaw14.CheckedChanged += new System.EventHandler(this.ValueChanged);
            // 
            // chklaw15
            // 
            this.chklaw15.AutoSize = true;
            this.chklaw15.Location = new System.Drawing.Point(19, 408);
            this.chklaw15.Name = "chklaw15";
            this.chklaw15.Size = new System.Drawing.Size(86, 17);
            this.chklaw15.TabIndex = 34;
            this.chklaw15.Text = "RippleRipple";
            this.chklaw15.UseVisualStyleBackColor = false;
            this.chklaw15.CheckedChanged += new System.EventHandler(this.ValueChanged);
            // 
            // chklaw13
            // 
            this.chklaw13.AutoSize = true;
            this.chklaw13.Location = new System.Drawing.Point(19, 350);
            this.chklaw13.Name = "chklaw13";
            this.chklaw13.Size = new System.Drawing.Size(85, 17);
            this.chklaw13.TabIndex = 33;
            this.chklaw13.Text = "WaveRipple";
            this.chklaw13.UseVisualStyleBackColor = false;
            this.chklaw13.CheckedChanged += new System.EventHandler(this.ValueChanged);
            // 
            // chklaw12
            // 
            this.chklaw12.AutoSize = true;
            this.chklaw12.Location = new System.Drawing.Point(19, 321);
            this.chklaw12.Name = "chklaw12";
            this.chklaw12.Size = new System.Drawing.Size(77, 17);
            this.chklaw12.TabIndex = 32;
            this.chklaw12.Text = "SpotWave";
            this.chklaw12.UseVisualStyleBackColor = false;
            this.chklaw12.CheckedChanged += new System.EventHandler(this.ValueChanged);
            // 
            // chklaw11
            // 
            this.chklaw11.AutoSize = true;
            this.chklaw11.Location = new System.Drawing.Point(19, 292);
            this.chklaw11.Name = "chklaw11";
            this.chklaw11.Size = new System.Drawing.Size(78, 17);
            this.chklaw11.TabIndex = 30;
            this.chklaw11.Text = "SpotRipple";
            this.chklaw11.UseVisualStyleBackColor = false;
            this.chklaw11.CheckedChanged += new System.EventHandler(this.ValueChanged);
            // 
            // chklaw10
            // 
            this.chklaw10.AutoSize = true;
            this.chklaw10.Location = new System.Drawing.Point(19, 264);
            this.chklaw10.Name = "chklaw10";
            this.chklaw10.Size = new System.Drawing.Size(70, 17);
            this.chklaw10.TabIndex = 29;
            this.chklaw10.Text = "SpotSpot";
            this.chklaw10.UseVisualStyleBackColor = false;
            this.chklaw10.CheckedChanged += new System.EventHandler(this.ValueChanged);
            // 
            // chklaw8
            // 
            this.chklaw8.AutoSize = true;
            this.chklaw8.Location = new System.Drawing.Point(19, 212);
            this.chklaw8.Name = "chklaw8";
            this.chklaw8.Size = new System.Drawing.Size(81, 17);
            this.chklaw8.TabIndex = 28;
            this.chklaw8.Text = "EdgeRipple";
            this.chklaw8.UseVisualStyleBackColor = false;
            this.chklaw8.CheckedChanged += new System.EventHandler(this.ValueChanged);
            // 
            // chklaw9
            // 
            this.chklaw9.AutoSize = true;
            this.chklaw9.Location = new System.Drawing.Point(19, 238);
            this.chklaw9.Name = "chklaw9";
            this.chklaw9.Size = new System.Drawing.Size(80, 17);
            this.chklaw9.TabIndex = 27;
            this.chklaw9.Text = "EdgeWave";
            this.chklaw9.UseVisualStyleBackColor = false;
            this.chklaw9.CheckedChanged += new System.EventHandler(this.ValueChanged);
            // 
            // chklaw7
            // 
            this.chklaw7.AutoSize = true;
            this.chklaw7.Location = new System.Drawing.Point(19, 184);
            this.chklaw7.Name = "chklaw7";
            this.chklaw7.Size = new System.Drawing.Size(73, 17);
            this.chklaw7.TabIndex = 26;
            this.chklaw7.Text = "EdgeSpot";
            this.chklaw7.UseVisualStyleBackColor = false;
            this.chklaw7.CheckedChanged += new System.EventHandler(this.ValueChanged);
            // 
            // chklaw2
            // 
            this.chklaw2.AutoSize = true;
            this.chklaw2.Location = new System.Drawing.Point(19, 44);
            this.chklaw2.Name = "chklaw2";
            this.chklaw2.Size = new System.Drawing.Size(73, 17);
            this.chklaw2.TabIndex = 25;
            this.chklaw2.Text = "levelEdge";
            this.chklaw2.UseVisualStyleBackColor = false;
            this.chklaw2.CheckedChanged += new System.EventHandler(this.ValueChanged);
            // 
            // FeaturesDlg
            // 
            this.AcceptButton = this.btnOK;
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.CancelButton = this.btnCancel;
            this.CausesValidation = false;
           this.ClientSize = new System.Drawing.Size(623,540);//623, 522);
            this.ControlBox = false;
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.btnSwitchToMultiSelect);
            this.Controls.Add(this.btnSwitchToSingleSelect);
            this.Controls.Add(this.btnOK);
            this.Controls.Add(this.btnReset);
            this.Controls.Add(this.btnCancel);
            this.Controls.Add(this.grpSpectral);
            this.Controls.Add(this.grpTexture);
            this.Controls.Add(this.grpRST);
            this.Controls.Add(this.grpHistogram);
            this.Controls.Add(this.grpBinary);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "FeaturesDlg";
            this.ShowInTaskbar = false;
            this.SizeGripStyle = System.Windows.Forms.SizeGripStyle.Show;
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
            this.Text = "Feature Selection";
            this.grpBinary.ResumeLayout(false);
            this.grpBinary.PerformLayout();
            this.grpHistogram.ResumeLayout(false);
            this.grpHistogram.PerformLayout();
            this.grpRST.ResumeLayout(false);
            this.grpRST.PerformLayout();
            this.grpTexture.ResumeLayout(false);
            this.grpTexture.PerformLayout();
            this.grpSpectral.ResumeLayout(false);
            this.grpSpectral.PerformLayout();
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox grpBinary;
        private System.Windows.Forms.Button btnBinSelectNone;
        private System.Windows.Forms.Button btnBinSelectAll;
        private System.Windows.Forms.Label lblProjHeight;
        private System.Windows.Forms.TextBox txtProjHeight;
        private System.Windows.Forms.Label lblProjWidth;
        private System.Windows.Forms.TextBox txtProjWidth;
        private System.Windows.Forms.CheckBox chkBinThinness;
        private System.Windows.Forms.CheckBox chkBinProjections;
        private System.Windows.Forms.CheckBox chkBinPerimeter;
        private System.Windows.Forms.CheckBox chkBinOrientation;
        private System.Windows.Forms.CheckBox chkBinEuler;
        private System.Windows.Forms.CheckBox chkBinCentroid;
        private System.Windows.Forms.CheckBox chkBinAspect;
        private System.Windows.Forms.CheckBox chkBinArea;
        private System.Windows.Forms.GroupBox grpHistogram;
        private System.Windows.Forms.Button btnHistSelectNone;
        private System.Windows.Forms.Button btnHistSelectAll;
        private System.Windows.Forms.CheckBox chkHistEntropy;
        private System.Windows.Forms.CheckBox chkHistEnergy;
        private System.Windows.Forms.CheckBox chkHistSkew;
        private System.Windows.Forms.CheckBox chkHistStdDev;
        private System.Windows.Forms.CheckBox chkHistMean;
        private System.Windows.Forms.GroupBox grpRST;
        private System.Windows.Forms.Button btnRstSelectNone;
        private System.Windows.Forms.Button btnRstSelectAll;
        private System.Windows.Forms.CheckBox chkRst7;
        private System.Windows.Forms.CheckBox chkRst6;
        private System.Windows.Forms.CheckBox chkRst5;
        private System.Windows.Forms.CheckBox chkRst4;
        private System.Windows.Forms.CheckBox chkRst3;
        private System.Windows.Forms.CheckBox chkRst2;
        private System.Windows.Forms.CheckBox chkRst1;
        private System.Windows.Forms.GroupBox grpTexture;
        private System.Windows.Forms.RadioButton rbOldTexture;
        private System.Windows.Forms.RadioButton rbTexture2;
        private System.Windows.Forms.Button btnTextSelectNone;
        private System.Windows.Forms.Button btnTextSelectAll;
        private System.Windows.Forms.Label lblTextDistance;
        private System.Windows.Forms.ComboBox cboTextDistance;
        private System.Windows.Forms.CheckBox chkTextEntropy;
        private System.Windows.Forms.CheckBox chkTextInvDiff;
        private System.Windows.Forms.CheckBox chkTextCorrelation;
        private System.Windows.Forms.CheckBox chkTextInertia;
        private System.Windows.Forms.CheckBox chkTextEnergy;
        private System.Windows.Forms.GroupBox grpSpectral;
        private System.Windows.Forms.Label lblSpectralSectors;
        private System.Windows.Forms.TextBox txtSpectralSectors;
        private System.Windows.Forms.Label lblSpectralRings;
        private System.Windows.Forms.TextBox txtSpectralRings;
        private System.Windows.Forms.CheckBox chkSpectral;
        private System.Windows.Forms.Button btnCancel;
        private System.Windows.Forms.Button btnReset;
        private System.Windows.Forms.Button btnOK;
        private System.Windows.Forms.TextBox textboxUpper;
        private System.Windows.Forms.TextBox textboxIncrement;
        private System.Windows.Forms.TextBox textboxLower;
        private System.Windows.Forms.Label lowerTD;
        private System.Windows.Forms.Label incrementTD;
        private System.Windows.Forms.Label upperTD;
        private System.Windows.Forms.Button btnSwitchToSingleSelect;
        private System.Windows.Forms.Button btnSwitchToMultiSelect;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.CheckBox chklaw4;
        private System.Windows.Forms.CheckBox chklaw3;
        private System.Windows.Forms.CheckBox chklaw6;
        private System.Windows.Forms.CheckBox chklaw5;
        private System.Windows.Forms.CheckBox chklaw1;
        private System.Windows.Forms.CheckBox chklaw14;
        private System.Windows.Forms.CheckBox chklaw15;
        private System.Windows.Forms.CheckBox chklaw13;
        private System.Windows.Forms.CheckBox chklaw12;
        private System.Windows.Forms.CheckBox chklaw11;
        private System.Windows.Forms.CheckBox chklaw10;
        private System.Windows.Forms.CheckBox chklaw8;
        private System.Windows.Forms.CheckBox chklaw9;
        private System.Windows.Forms.CheckBox chklaw7;
        private System.Windows.Forms.CheckBox chklaw2;
        private System.Windows.Forms.Button btnLawSelectNone;
        private System.Windows.Forms.Button btnLawSelectAll;
    }
}
