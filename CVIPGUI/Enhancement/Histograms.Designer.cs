namespace CVIPGUI.Enhancement
{
    partial class Histograms
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
            this.rbHistEQ = new System.Windows.Forms.RadioButton();
            this.rbHistSlide = new System.Windows.Forms.RadioButton();
            this.rbHistStretch = new System.Windows.Forms.RadioButton();
            this.rbHistShrink = new System.Windows.Forms.RadioButton();
            this.rbLocalEQ = new System.Windows.Forms.RadioButton();
            this.rbACE = new System.Windows.Forms.RadioButton();
            this.rbACEII = new System.Windows.Forms.RadioButton();
            this.rbLog = new System.Windows.Forms.RadioButton();
            this.rbEXP = new System.Windows.Forms.RadioButton();
            this.rbColorContrast = new System.Windows.Forms.RadioButton();
            this.rbHistSpecify = new System.Windows.Forms.RadioButton();
            this.rbLinearMod = new System.Windows.Forms.RadioButton();
            this.rbGrayLevelMult = new System.Windows.Forms.RadioButton();
            this.grpHistogram1 = new System.Windows.Forms.GroupBox();
            this.grpHistogram2 = new System.Windows.Forms.GroupBox();
            this.grpHistogram3 = new System.Windows.Forms.GroupBox();
            this.grpParameters = new System.Windows.Forms.GroupBox();
            this.pnlGrayLevelMult = new System.Windows.Forms.Panel();
            this.chkByteClipping = new System.Windows.Forms.CheckBox();
            this.cboFactor = new System.Windows.Forms.ComboBox();
            this.lblFactor = new System.Windows.Forms.Label();
            this.pnlLinearMod = new System.Windows.Forms.Panel();
            this.cboSlope = new System.Windows.Forms.ComboBox();
            this.lblSlope = new System.Windows.Forms.Label();
            this.cboInitialVal = new System.Windows.Forms.ComboBox();
            this.lblInitialVal = new System.Windows.Forms.Label();
            this.cboEndVal = new System.Windows.Forms.ComboBox();
            this.lblEndVal = new System.Windows.Forms.Label();
            this.cboStartVal = new System.Windows.Forms.ComboBox();
            this.lblStartVal = new System.Windows.Forms.Label();
            this.rbZeroDataOOR = new System.Windows.Forms.RadioButton();
            this.rbKeepDataOOR = new System.Windows.Forms.RadioButton();
            this.pnlHistSpec = new System.Windows.Forms.Panel();
            this.chkShowIntermediate = new System.Windows.Forms.CheckBox();
            this.cboFormulaBlue = new System.Windows.Forms.ComboBox();
            this.lblFormulaBlue = new System.Windows.Forms.Label();
            this.cboFormulaGreen = new System.Windows.Forms.ComboBox();
            this.lblFormulaGreen = new System.Windows.Forms.Label();
            this.cboFormulaRed = new System.Windows.Forms.ComboBox();
            this.lblFormulaRed = new System.Windows.Forms.Label();
            this.pnlACE = new System.Windows.Forms.Panel();
            this.cboLocalGainMax = new System.Windows.Forms.ComboBox();
            this.lblLocalGainMax = new System.Windows.Forms.Label();
            this.cboLocalGainMin = new System.Windows.Forms.ComboBox();
            this.lblLocalGainMin = new System.Windows.Forms.Label();
            this.cboKernelSize = new System.Windows.Forms.ComboBox();
            this.lblKernelSize = new System.Windows.Forms.Label();
            this.cboLocalGainFactor = new System.Windows.Forms.ComboBox();
            this.lblLocalGainFactor = new System.Windows.Forms.Label();
            this.cboLocalMeanFactor = new System.Windows.Forms.ComboBox();
            this.lblLocalMeanFactor = new System.Windows.Forms.Label();
            this.pnlStretch = new System.Windows.Forms.Panel();
            this.lblHighPercent = new System.Windows.Forms.Label();
            this.lblLowPercent = new System.Windows.Forms.Label();
            this.cboHighClip = new System.Windows.Forms.ComboBox();
            this.lblHighClip = new System.Windows.Forms.Label();
            this.cboLowClip = new System.Windows.Forms.ComboBox();
            this.lblLowClip = new System.Windows.Forms.Label();
            this.cboHighLimit = new System.Windows.Forms.ComboBox();
            this.lblHighLimit = new System.Windows.Forms.Label();
            this.cboLowLimit = new System.Windows.Forms.ComboBox();
            this.lblLowLimit = new System.Windows.Forms.Label();
            this.pnlSlide = new System.Windows.Forms.Panel();
            this.cboSlide = new System.Windows.Forms.ComboBox();
            this.lblSlide = new System.Windows.Forms.Label();
            this.rbSlideUp = new System.Windows.Forms.RadioButton();
            this.rbSlideDown = new System.Windows.Forms.RadioButton();
            this.pnlEQ = new System.Windows.Forms.Panel();
            this.lblCLAHEPercent = new System.Windows.Forms.Label();
            this.cboBlockSize = new System.Windows.Forms.ComboBox();
            this.lblBlockSize = new System.Windows.Forms.Label();
            this.lblBand = new System.Windows.Forms.Label();
            this.rbBlue = new System.Windows.Forms.RadioButton();
            this.rbGreen = new System.Windows.Forms.RadioButton();
            this.rbRed = new System.Windows.Forms.RadioButton();
            this.rbValue = new System.Windows.Forms.RadioButton();
            this.lblClahe = new System.Windows.Forms.Label();
            this.cboClahe = new System.Windows.Forms.ComboBox();
            this.CLAHECheckBox = new System.Windows.Forms.CheckBox();
            this.btnHelp = new System.Windows.Forms.Button();
            this.btnCancel = new System.Windows.Forms.Button();
            this.btnReset = new System.Windows.Forms.Button();
            this.btnApply = new System.Windows.Forms.Button();
            this.rbCLAHE = new System.Windows.Forms.RadioButton();
            this.grpParameters.SuspendLayout();
            this.pnlGrayLevelMult.SuspendLayout();
            this.pnlLinearMod.SuspendLayout();
            this.pnlHistSpec.SuspendLayout();
            this.pnlACE.SuspendLayout();
            this.pnlStretch.SuspendLayout();
            this.pnlSlide.SuspendLayout();
            this.pnlEQ.SuspendLayout();
            this.SuspendLayout();
            // 
            // rbHistEQ
            // 
            this.rbHistEQ.AutoSize = true;
            this.rbHistEQ.Checked = true;
            this.rbHistEQ.Location = new System.Drawing.Point(11, 12);
            this.rbHistEQ.Name = "rbHistEQ";
            this.rbHistEQ.Size = new System.Drawing.Size(132, 17);
            this.rbHistEQ.TabIndex = 0;
            this.rbHistEQ.TabStop = true;
            this.rbHistEQ.Text = "Histogram Equalization";
            this.rbHistEQ.UseVisualStyleBackColor = true;
            this.rbHistEQ.Click += new System.EventHandler(this.rbHistogram_Click);
            // 
            // rbHistSlide
            // 
            this.rbHistSlide.AutoSize = true;
            this.rbHistSlide.Location = new System.Drawing.Point(11, 28);
            this.rbHistSlide.Name = "rbHistSlide";
            this.rbHistSlide.Size = new System.Drawing.Size(98, 17);
            this.rbHistSlide.TabIndex = 1;
            this.rbHistSlide.Text = "Histogram Slide";
            this.rbHistSlide.UseVisualStyleBackColor = true;
            this.rbHistSlide.Click += new System.EventHandler(this.rbHistogram_Click);
            // 
            // rbHistStretch
            // 
            this.rbHistStretch.AutoSize = true;
            this.rbHistStretch.Location = new System.Drawing.Point(11, 44);
            this.rbHistStretch.Name = "rbHistStretch";
            this.rbHistStretch.Size = new System.Drawing.Size(109, 17);
            this.rbHistStretch.TabIndex = 2;
            this.rbHistStretch.Text = "Histogram Stretch";
            this.rbHistStretch.UseVisualStyleBackColor = true;
            this.rbHistStretch.Click += new System.EventHandler(this.rbHistogram_Click);
            // 
            // rbHistShrink
            // 
            this.rbHistShrink.AutoSize = true;
            this.rbHistShrink.Location = new System.Drawing.Point(11, 60);
            this.rbHistShrink.Name = "rbHistShrink";
            this.rbHistShrink.Size = new System.Drawing.Size(105, 17);
            this.rbHistShrink.TabIndex = 3;
            this.rbHistShrink.Text = "Histogram Shrink";
            this.rbHistShrink.UseVisualStyleBackColor = true;
            this.rbHistShrink.CheckedChanged += new System.EventHandler(this.rbHistShrink_CheckedChanged);
            this.rbHistShrink.Click += new System.EventHandler(this.rbHistogram_Click);
            // 
            // rbLocalEQ
            // 
            this.rbLocalEQ.AutoSize = true;
            this.rbLocalEQ.Location = new System.Drawing.Point(11, 82);
            this.rbLocalEQ.Name = "rbLocalEQ";
            this.rbLocalEQ.Size = new System.Drawing.Size(118, 17);
            this.rbLocalEQ.TabIndex = 4;
            this.rbLocalEQ.Text = "Local (Adaptive) Eq";
            this.rbLocalEQ.UseVisualStyleBackColor = true;
            this.rbLocalEQ.CheckedChanged += new System.EventHandler(this.rbLocalEQ_CheckedChanged);
            this.rbLocalEQ.Click += new System.EventHandler(this.rbHistogram_Click);
            // 
            // rbACE
            // 
            this.rbACE.AutoSize = true;
            this.rbACE.Location = new System.Drawing.Point(11, 116);
            this.rbACE.Name = "rbACE";
            this.rbACE.Size = new System.Drawing.Size(158, 17);
            this.rbACE.TabIndex = 5;
            this.rbACE.Text = "Adaptive Contrast Enh(ACE)";
            this.rbACE.UseVisualStyleBackColor = true;
            this.rbACE.Click += new System.EventHandler(this.rbHistogram_Click);
            // 
            // rbACEII
            // 
            this.rbACEII.AutoSize = true;
            this.rbACEII.Location = new System.Drawing.Point(11, 133);
            this.rbACEII.Name = "rbACEII";
            this.rbACEII.Size = new System.Drawing.Size(55, 17);
            this.rbACEII.TabIndex = 6;
            this.rbACEII.Text = "ACE II";
            this.rbACEII.UseVisualStyleBackColor = true;
            this.rbACEII.Click += new System.EventHandler(this.rbHistogram_Click);
            // 
            // rbLog
            // 
            this.rbLog.AutoSize = true;
            this.rbLog.Location = new System.Drawing.Point(11, 150);
            this.rbLog.Name = "rbLog";
            this.rbLog.Size = new System.Drawing.Size(63, 17);
            this.rbLog.TabIndex = 7;
            this.rbLog.Text = "log-ACE";
            this.rbLog.UseVisualStyleBackColor = true;
            this.rbLog.Click += new System.EventHandler(this.rbHistogram_Click);
            // 
            // rbEXP
            // 
            this.rbEXP.AutoSize = true;
            this.rbEXP.Location = new System.Drawing.Point(11, 167);
            this.rbEXP.Name = "rbEXP";
            this.rbEXP.Size = new System.Drawing.Size(66, 17);
            this.rbEXP.TabIndex = 8;
            this.rbEXP.Text = "exp-ACE";
            this.rbEXP.UseVisualStyleBackColor = true;
            this.rbEXP.Click += new System.EventHandler(this.rbHistogram_Click);
            // 
            // rbColorContrast
            // 
            this.rbColorContrast.AutoSize = true;
            this.rbColorContrast.Location = new System.Drawing.Point(11, 184);
            this.rbColorContrast.Name = "rbColorContrast";
            this.rbColorContrast.Size = new System.Drawing.Size(137, 17);
            this.rbColorContrast.TabIndex = 9;
            this.rbColorContrast.Text = "Color Contrast Algorithm";
            this.rbColorContrast.UseVisualStyleBackColor = true;
            this.rbColorContrast.Click += new System.EventHandler(this.rbHistogram_Click);
            // 
            // rbHistSpecify
            // 
            this.rbHistSpecify.AutoSize = true;
            this.rbHistSpecify.Location = new System.Drawing.Point(11, 212);
            this.rbHistSpecify.Name = "rbHistSpecify";
            this.rbHistSpecify.Size = new System.Drawing.Size(136, 17);
            this.rbHistSpecify.TabIndex = 10;
            this.rbHistSpecify.Text = "Histogram Specification";
            this.rbHistSpecify.UseVisualStyleBackColor = true;
            this.rbHistSpecify.Click += new System.EventHandler(this.rbHistogram_Click);
            // 
            // rbLinearMod
            // 
            this.rbLinearMod.AutoSize = true;
            this.rbLinearMod.Location = new System.Drawing.Point(11, 230);
            this.rbLinearMod.Name = "rbLinearMod";
            this.rbLinearMod.Size = new System.Drawing.Size(114, 17);
            this.rbLinearMod.TabIndex = 11;
            this.rbLinearMod.Text = "Linear Modification";
            this.rbLinearMod.UseVisualStyleBackColor = true;
            this.rbLinearMod.Click += new System.EventHandler(this.rbHistogram_Click);
            // 
            // rbGrayLevelMult
            // 
            this.rbGrayLevelMult.AutoSize = true;
            this.rbGrayLevelMult.Location = new System.Drawing.Point(11, 248);
            this.rbGrayLevelMult.Name = "rbGrayLevelMult";
            this.rbGrayLevelMult.Size = new System.Drawing.Size(140, 17);
            this.rbGrayLevelMult.TabIndex = 12;
            this.rbGrayLevelMult.Text = "Gray Level Multiplication";
            this.rbGrayLevelMult.UseVisualStyleBackColor = true;
            this.rbGrayLevelMult.Click += new System.EventHandler(this.rbHistogram_Click);
            // 
            // grpHistogram1
            // 
            this.grpHistogram1.Location = new System.Drawing.Point(6, 1);
            this.grpHistogram1.Name = "grpHistogram1";
            this.grpHistogram1.Size = new System.Drawing.Size(166, 80);
            this.grpHistogram1.TabIndex = 13;
            this.grpHistogram1.TabStop = false;
            // 
            // grpHistogram2
            // 
            this.grpHistogram2.Location = new System.Drawing.Point(6, 75);
            this.grpHistogram2.Name = "grpHistogram2";
            this.grpHistogram2.Size = new System.Drawing.Size(166, 128);
            this.grpHistogram2.TabIndex = 14;
            this.grpHistogram2.TabStop = false;
            // 
            // grpHistogram3
            // 
            this.grpHistogram3.Location = new System.Drawing.Point(6, 200);
            this.grpHistogram3.Name = "grpHistogram3";
            this.grpHistogram3.Size = new System.Drawing.Size(166, 70);
            this.grpHistogram3.TabIndex = 15;
            this.grpHistogram3.TabStop = false;
            // 
            // grpParameters
            // 
            this.grpParameters.Controls.Add(this.pnlGrayLevelMult);
            this.grpParameters.Controls.Add(this.pnlLinearMod);
            this.grpParameters.Controls.Add(this.pnlHistSpec);
            this.grpParameters.Controls.Add(this.pnlACE);
            this.grpParameters.Controls.Add(this.pnlStretch);
            this.grpParameters.Controls.Add(this.pnlSlide);
            this.grpParameters.Controls.Add(this.pnlEQ);
            this.grpParameters.Location = new System.Drawing.Point(175, 1);
            this.grpParameters.Name = "grpParameters";
            this.grpParameters.Size = new System.Drawing.Size(382, 269);
            this.grpParameters.TabIndex = 16;
            this.grpParameters.TabStop = false;
            this.grpParameters.Text = "Parameters";
            // 
            // pnlGrayLevelMult
            // 
            this.pnlGrayLevelMult.Controls.Add(this.chkByteClipping);
            this.pnlGrayLevelMult.Controls.Add(this.cboFactor);
            this.pnlGrayLevelMult.Controls.Add(this.lblFactor);
            this.pnlGrayLevelMult.Location = new System.Drawing.Point(15, 191);
            this.pnlGrayLevelMult.Name = "pnlGrayLevelMult";
            this.pnlGrayLevelMult.Size = new System.Drawing.Size(191, 49);
            this.pnlGrayLevelMult.TabIndex = 6;
            // 
            // chkByteClipping
            // 
            this.chkByteClipping.AutoSize = true;
            this.chkByteClipping.Checked = true;
            this.chkByteClipping.CheckState = System.Windows.Forms.CheckState.Checked;
            this.chkByteClipping.Location = new System.Drawing.Point(3, 32);
            this.chkByteClipping.Name = "chkByteClipping";
            this.chkByteClipping.Size = new System.Drawing.Size(86, 17);
            this.chkByteClipping.TabIndex = 2;
            this.chkByteClipping.Text = "Byte clipping";
            this.chkByteClipping.UseVisualStyleBackColor = true;
            // 
            // cboFactor
            // 
            this.cboFactor.FormattingEnabled = true;
            this.cboFactor.Items.AddRange(new object[] {
            "0.2",
            "0.5",
            "0.8",
            "1.2",
            "1.5",
            "1.8",
            "2.0",
            "2.5",
            "3.0"});
            this.cboFactor.Location = new System.Drawing.Point(81, 0);
            this.cboFactor.Name = "cboFactor";
            this.cboFactor.Size = new System.Drawing.Size(110, 21);
            this.cboFactor.TabIndex = 1;
            this.cboFactor.Text = "2.0";
            this.cboFactor.Validating += new System.ComponentModel.CancelEventHandler(this.cboFloatVal_Validating);
            // 
            // lblFactor
            // 
            this.lblFactor.AutoSize = true;
            this.lblFactor.Location = new System.Drawing.Point(0, 4);
            this.lblFactor.Name = "lblFactor";
            this.lblFactor.Size = new System.Drawing.Size(61, 13);
            this.lblFactor.TabIndex = 0;
            this.lblFactor.Text = "By a factor:";
            // 
            // pnlLinearMod
            // 
            this.pnlLinearMod.Controls.Add(this.cboSlope);
            this.pnlLinearMod.Controls.Add(this.lblSlope);
            this.pnlLinearMod.Controls.Add(this.cboInitialVal);
            this.pnlLinearMod.Controls.Add(this.lblInitialVal);
            this.pnlLinearMod.Controls.Add(this.cboEndVal);
            this.pnlLinearMod.Controls.Add(this.lblEndVal);
            this.pnlLinearMod.Controls.Add(this.cboStartVal);
            this.pnlLinearMod.Controls.Add(this.lblStartVal);
            this.pnlLinearMod.Controls.Add(this.rbZeroDataOOR);
            this.pnlLinearMod.Controls.Add(this.rbKeepDataOOR);
            this.pnlLinearMod.Location = new System.Drawing.Point(15, 107);
            this.pnlLinearMod.Name = "pnlLinearMod";
            this.pnlLinearMod.Size = new System.Drawing.Size(309, 137);
            this.pnlLinearMod.TabIndex = 5;
            this.pnlLinearMod.Paint += new System.Windows.Forms.PaintEventHandler(this.pnlLinearMod_Paint);
            // 
            // cboSlope
            // 
            this.cboSlope.FormattingEnabled = true;
            this.cboSlope.Items.AddRange(new object[] {
            "-4.0",
            "-3.0",
            "-1.0",
            "-0.5",
            "0.0",
            "0.5",
            "1.0",
            "1.2",
            "2.0",
            "3.0",
            "4.0"});
            this.cboSlope.Location = new System.Drawing.Point(81, 116);
            this.cboSlope.Name = "cboSlope";
            this.cboSlope.Size = new System.Drawing.Size(110, 21);
            this.cboSlope.TabIndex = 9;
            this.cboSlope.Text = "1.2";
            this.cboSlope.Validating += new System.ComponentModel.CancelEventHandler(this.cboDoubleVal_Validating);
            // 
            // lblSlope
            // 
            this.lblSlope.AutoSize = true;
            this.lblSlope.Location = new System.Drawing.Point(0, 120);
            this.lblSlope.Name = "lblSlope";
            this.lblSlope.Size = new System.Drawing.Size(34, 13);
            this.lblSlope.TabIndex = 8;
            this.lblSlope.Text = "Slope";
            // 
            // cboInitialVal
            // 
            this.cboInitialVal.FormattingEnabled = true;
            this.cboInitialVal.Items.AddRange(new object[] {
            "0",
            "32",
            "64",
            "96",
            "128"});
            this.cboInitialVal.Location = new System.Drawing.Point(81, 89);
            this.cboInitialVal.Name = "cboInitialVal";
            this.cboInitialVal.Size = new System.Drawing.Size(110, 21);
            this.cboInitialVal.TabIndex = 7;
            this.cboInitialVal.Text = "0";
            this.cboInitialVal.Validating += new System.ComponentModel.CancelEventHandler(this.cboDoubleVal_Validating);
            // 
            // lblInitialVal
            // 
            this.lblInitialVal.AutoSize = true;
            this.lblInitialVal.Location = new System.Drawing.Point(0, 93);
            this.lblInitialVal.Name = "lblInitialVal";
            this.lblInitialVal.Size = new System.Drawing.Size(63, 13);
            this.lblInitialVal.TabIndex = 6;
            this.lblInitialVal.Text = "Initial value:";
            // 
            // cboEndVal
            // 
            this.cboEndVal.FormattingEnabled = true;
            this.cboEndVal.Items.AddRange(new object[] {
            "32",
            "64",
            "96",
            "128",
            "160",
            "192",
            "224",
            "254"});
            this.cboEndVal.Location = new System.Drawing.Point(81, 62);
            this.cboEndVal.Name = "cboEndVal";
            this.cboEndVal.Size = new System.Drawing.Size(110, 21);
            this.cboEndVal.TabIndex = 5;
            this.cboEndVal.Text = "255";
            this.cboEndVal.Validating += new System.ComponentModel.CancelEventHandler(this.cboDoubleVal_Validating);
            // 
            // lblEndVal
            // 
            this.lblEndVal.AutoSize = true;
            this.lblEndVal.Location = new System.Drawing.Point(0, 66);
            this.lblEndVal.Name = "lblEndVal";
            this.lblEndVal.Size = new System.Drawing.Size(29, 13);
            this.lblEndVal.TabIndex = 4;
            this.lblEndVal.Text = "End:";
            // 
            // cboStartVal
            // 
            this.cboStartVal.FormattingEnabled = true;
            this.cboStartVal.Items.AddRange(new object[] {
            "0",
            "32",
            "64",
            "96",
            "128",
            "160",
            "192",
            "224"});
            this.cboStartVal.Location = new System.Drawing.Point(81, 35);
            this.cboStartVal.Name = "cboStartVal";
            this.cboStartVal.Size = new System.Drawing.Size(110, 21);
            this.cboStartVal.TabIndex = 3;
            this.cboStartVal.Text = "0";
            this.cboStartVal.Validating += new System.ComponentModel.CancelEventHandler(this.cboDoubleVal_Validating);
            // 
            // lblStartVal
            // 
            this.lblStartVal.AutoSize = true;
            this.lblStartVal.Location = new System.Drawing.Point(0, 39);
            this.lblStartVal.Name = "lblStartVal";
            this.lblStartVal.Size = new System.Drawing.Size(32, 13);
            this.lblStartVal.TabIndex = 2;
            this.lblStartVal.Text = "Start:";
            // 
            // rbZeroDataOOR
            // 
            this.rbZeroDataOOR.AutoSize = true;
            this.rbZeroDataOOR.Location = new System.Drawing.Point(163, 0);
            this.rbZeroDataOOR.Name = "rbZeroDataOOR";
            this.rbZeroDataOOR.Size = new System.Drawing.Size(146, 17);
            this.rbZeroDataOOR.TabIndex = 1;
            this.rbZeroDataOOR.Text = "Set out of range data to 0";
            this.rbZeroDataOOR.UseVisualStyleBackColor = true;
            // 
            // rbKeepDataOOR
            // 
            this.rbKeepDataOOR.AutoSize = true;
            this.rbKeepDataOOR.Checked = true;
            this.rbKeepDataOOR.Location = new System.Drawing.Point(3, 0);
            this.rbKeepDataOOR.Name = "rbKeepDataOOR";
            this.rbKeepDataOOR.Size = new System.Drawing.Size(134, 17);
            this.rbKeepDataOOR.TabIndex = 0;
            this.rbKeepDataOOR.TabStop = true;
            this.rbKeepDataOOR.Text = "Keep out of range data";
            this.rbKeepDataOOR.UseVisualStyleBackColor = true;
            // 
            // pnlHistSpec
            // 
            this.pnlHistSpec.Controls.Add(this.chkShowIntermediate);
            this.pnlHistSpec.Controls.Add(this.cboFormulaBlue);
            this.pnlHistSpec.Controls.Add(this.lblFormulaBlue);
            this.pnlHistSpec.Controls.Add(this.cboFormulaGreen);
            this.pnlHistSpec.Controls.Add(this.lblFormulaGreen);
            this.pnlHistSpec.Controls.Add(this.cboFormulaRed);
            this.pnlHistSpec.Controls.Add(this.lblFormulaRed);
            this.pnlHistSpec.Location = new System.Drawing.Point(15, 131);
            this.pnlHistSpec.Name = "pnlHistSpec";
            this.pnlHistSpec.Size = new System.Drawing.Size(245, 111);
            this.pnlHistSpec.TabIndex = 4;
            // 
            // chkShowIntermediate
            // 
            this.chkShowIntermediate.AutoSize = true;
            this.chkShowIntermediate.Checked = true;
            this.chkShowIntermediate.CheckState = System.Windows.Forms.CheckState.Checked;
            this.chkShowIntermediate.Location = new System.Drawing.Point(3, 94);
            this.chkShowIntermediate.Name = "chkShowIntermediate";
            this.chkShowIntermediate.Size = new System.Drawing.Size(197, 17);
            this.chkShowIntermediate.TabIndex = 6;
            this.chkShowIntermediate.Text = "Show intermediate histogram images";
            this.chkShowIntermediate.UseVisualStyleBackColor = true;
            // 
            // cboFormulaBlue
            // 
            this.cboFormulaBlue.FormattingEnabled = true;
            this.cboFormulaBlue.Items.AddRange(new object[] {
            "sin(0.025*x)",
            "x+25",
            "x*2.0",
            "ramp(2.0*x+5)",
            "exp(0.025*x)",
            "log(0.5*x+2)",
            "cos(0.025*x)",
            "sinh(0.025*x)",
            "tanh(0.025*x)",
            "cosh(0.025*x)"});
            this.cboFormulaBlue.Location = new System.Drawing.Point(135, 54);
            this.cboFormulaBlue.Name = "cboFormulaBlue";
            this.cboFormulaBlue.Size = new System.Drawing.Size(110, 21);
            this.cboFormulaBlue.TabIndex = 5;
            this.cboFormulaBlue.Text = "sin(0.025*x)";
            // 
            // lblFormulaBlue
            // 
            this.lblFormulaBlue.AutoSize = true;
            this.lblFormulaBlue.Location = new System.Drawing.Point(0, 58);
            this.lblFormulaBlue.Name = "lblFormulaBlue";
            this.lblFormulaBlue.Size = new System.Drawing.Size(99, 13);
            this.lblFormulaBlue.TabIndex = 4;
            this.lblFormulaBlue.Text = "Formula for B band:";
            // 
            // cboFormulaGreen
            // 
            this.cboFormulaGreen.FormattingEnabled = true;
            this.cboFormulaGreen.Items.AddRange(new object[] {
            "sin(0.025*x)",
            "x+25",
            "x*2.0",
            "ramp(2.0*x+5)",
            "exp(0.025*x)",
            "log(0.5*x+2)",
            "cos(0.025*x)",
            "sinh(0.025*x)",
            "tanh(0.025*x)",
            "cosh(0.025*x)"});
            this.cboFormulaGreen.Location = new System.Drawing.Point(135, 27);
            this.cboFormulaGreen.Name = "cboFormulaGreen";
            this.cboFormulaGreen.Size = new System.Drawing.Size(110, 21);
            this.cboFormulaGreen.TabIndex = 3;
            this.cboFormulaGreen.Text = "sin(0.025*x)";
            // 
            // lblFormulaGreen
            // 
            this.lblFormulaGreen.AutoSize = true;
            this.lblFormulaGreen.Location = new System.Drawing.Point(0, 31);
            this.lblFormulaGreen.Name = "lblFormulaGreen";
            this.lblFormulaGreen.Size = new System.Drawing.Size(100, 13);
            this.lblFormulaGreen.TabIndex = 2;
            this.lblFormulaGreen.Text = "Formula for G band:";
            // 
            // cboFormulaRed
            // 
            this.cboFormulaRed.FormattingEnabled = true;
            this.cboFormulaRed.Items.AddRange(new object[] {
            "sin(0.025*x)",
            "x+25",
            "x*2.0",
            "ramp(2.0*x+5)",
            "exp(0.025*x)",
            "log(0.5*x+2)",
            "cos(0.025*x)",
            "sinh(0.025*x)",
            "tanh(0.025*x)",
            "cosh(0.025*x)"});
            this.cboFormulaRed.Location = new System.Drawing.Point(135, 0);
            this.cboFormulaRed.Name = "cboFormulaRed";
            this.cboFormulaRed.Size = new System.Drawing.Size(110, 21);
            this.cboFormulaRed.TabIndex = 1;
            this.cboFormulaRed.Text = "sin(0.025*x)";
            // 
            // lblFormulaRed
            // 
            this.lblFormulaRed.AutoSize = true;
            this.lblFormulaRed.Location = new System.Drawing.Point(0, 4);
            this.lblFormulaRed.Name = "lblFormulaRed";
            this.lblFormulaRed.Size = new System.Drawing.Size(100, 13);
            this.lblFormulaRed.TabIndex = 0;
            this.lblFormulaRed.Text = "Formula for R band:";
            // 
            // pnlACE
            // 
            this.pnlACE.Controls.Add(this.cboLocalGainMax);
            this.pnlACE.Controls.Add(this.lblLocalGainMax);
            this.pnlACE.Controls.Add(this.cboLocalGainMin);
            this.pnlACE.Controls.Add(this.lblLocalGainMin);
            this.pnlACE.Controls.Add(this.cboKernelSize);
            this.pnlACE.Controls.Add(this.lblKernelSize);
            this.pnlACE.Controls.Add(this.cboLocalGainFactor);
            this.pnlACE.Controls.Add(this.lblLocalGainFactor);
            this.pnlACE.Controls.Add(this.cboLocalMeanFactor);
            this.pnlACE.Controls.Add(this.lblLocalMeanFactor);
            this.pnlACE.Location = new System.Drawing.Point(15, 113);
            this.pnlACE.Name = "pnlACE";
            this.pnlACE.Size = new System.Drawing.Size(245, 129);
            this.pnlACE.TabIndex = 3;
            // 
            // cboLocalGainMax
            // 
            this.cboLocalGainMax.FormattingEnabled = true;
            this.cboLocalGainMax.Items.AddRange(new object[] {
            "5.0",
            "10.0",
            "15.0",
            "20.0",
            "30.0",
            "100.0"});
            this.cboLocalGainMax.Location = new System.Drawing.Point(135, 108);
            this.cboLocalGainMax.Name = "cboLocalGainMax";
            this.cboLocalGainMax.Size = new System.Drawing.Size(110, 21);
            this.cboLocalGainMax.TabIndex = 9;
            this.cboLocalGainMax.Text = "10.0";
            this.cboLocalGainMax.Validating += new System.ComponentModel.CancelEventHandler(this.cboDoubleVal_Validating);
            // 
            // lblLocalGainMax
            // 
            this.lblLocalGainMax.AutoSize = true;
            this.lblLocalGainMax.Location = new System.Drawing.Point(0, 112);
            this.lblLocalGainMax.Name = "lblLocalGainMax";
            this.lblLocalGainMax.Size = new System.Drawing.Size(79, 13);
            this.lblLocalGainMax.TabIndex = 8;
            this.lblLocalGainMax.Text = "Local gain Max";
            // 
            // cboLocalGainMin
            // 
            this.cboLocalGainMin.FormattingEnabled = true;
            this.cboLocalGainMin.Items.AddRange(new object[] {
            "0.5",
            "1.0",
            "2.0",
            "5.0",
            "10.0",
            "15.0",
            "20.0"});
            this.cboLocalGainMin.Location = new System.Drawing.Point(135, 81);
            this.cboLocalGainMin.Name = "cboLocalGainMin";
            this.cboLocalGainMin.Size = new System.Drawing.Size(110, 21);
            this.cboLocalGainMin.TabIndex = 7;
            this.cboLocalGainMin.Text = "0.5";
            this.cboLocalGainMin.Validating += new System.ComponentModel.CancelEventHandler(this.cboDoubleVal_Validating);
            // 
            // lblLocalGainMin
            // 
            this.lblLocalGainMin.AutoSize = true;
            this.lblLocalGainMin.Location = new System.Drawing.Point(0, 85);
            this.lblLocalGainMin.Name = "lblLocalGainMin";
            this.lblLocalGainMin.Size = new System.Drawing.Size(79, 13);
            this.lblLocalGainMin.TabIndex = 6;
            this.lblLocalGainMin.Text = "Local gain Min:";
            // 
            // cboKernelSize
            // 
            this.cboKernelSize.FormattingEnabled = true;
            this.cboKernelSize.Items.AddRange(new object[] {
            "7",
            "9",
            "11",
            "13",
            "21"});
            this.cboKernelSize.Location = new System.Drawing.Point(135, 54);
            this.cboKernelSize.Name = "cboKernelSize";
            this.cboKernelSize.Size = new System.Drawing.Size(110, 21);
            this.cboKernelSize.TabIndex = 5;
            this.cboKernelSize.Text = "11";
            this.cboKernelSize.Validating += new System.ComponentModel.CancelEventHandler(this.cboUIntVal_Validating);
            // 
            // lblKernelSize
            // 
            this.lblKernelSize.AutoSize = true;
            this.lblKernelSize.Location = new System.Drawing.Point(0, 58);
            this.lblKernelSize.Name = "lblKernelSize";
            this.lblKernelSize.Size = new System.Drawing.Size(61, 13);
            this.lblKernelSize.TabIndex = 4;
            this.lblKernelSize.Text = "Kernel size:";
            // 
            // cboLocalGainFactor
            // 
            this.cboLocalGainFactor.FormattingEnabled = true;
            this.cboLocalGainFactor.Items.AddRange(new object[] {
            "0.4",
            "0.5",
            "0.6",
            "0.7",
            "0.8",
            "0.9",
            "1.0"});
            this.cboLocalGainFactor.Location = new System.Drawing.Point(135, 27);
            this.cboLocalGainFactor.Name = "cboLocalGainFactor";
            this.cboLocalGainFactor.Size = new System.Drawing.Size(110, 21);
            this.cboLocalGainFactor.TabIndex = 3;
            this.cboLocalGainFactor.Text = "1.0";
            this.cboLocalGainFactor.Validating += new System.ComponentModel.CancelEventHandler(this.cboDoubleVal_Validating);
            // 
            // lblLocalGainFactor
            // 
            this.lblLocalGainFactor.AutoSize = true;
            this.lblLocalGainFactor.Location = new System.Drawing.Point(0, 31);
            this.lblLocalGainFactor.Name = "lblLocalGainFactor";
            this.lblLocalGainFactor.Size = new System.Drawing.Size(89, 13);
            this.lblLocalGainFactor.TabIndex = 2;
            this.lblLocalGainFactor.Text = "Local gain factor:";
            // 
            // cboLocalMeanFactor
            // 
            this.cboLocalMeanFactor.FormattingEnabled = true;
            this.cboLocalMeanFactor.Items.AddRange(new object[] {
            "0.1",
            "0.2",
            "0.3",
            "0.4",
            "0.5"});
            this.cboLocalMeanFactor.Location = new System.Drawing.Point(135, 0);
            this.cboLocalMeanFactor.Name = "cboLocalMeanFactor";
            this.cboLocalMeanFactor.Size = new System.Drawing.Size(110, 21);
            this.cboLocalMeanFactor.TabIndex = 1;
            this.cboLocalMeanFactor.Text = "0.5";
            this.cboLocalMeanFactor.Validating += new System.ComponentModel.CancelEventHandler(this.cboDoubleVal_Validating);
            // 
            // lblLocalMeanFactor
            // 
            this.lblLocalMeanFactor.AutoSize = true;
            this.lblLocalMeanFactor.Location = new System.Drawing.Point(0, 4);
            this.lblLocalMeanFactor.Name = "lblLocalMeanFactor";
            this.lblLocalMeanFactor.Size = new System.Drawing.Size(95, 13);
            this.lblLocalMeanFactor.TabIndex = 0;
            this.lblLocalMeanFactor.Text = "Local mean factor:";
            // 
            // pnlStretch
            // 
            this.pnlStretch.Controls.Add(this.lblHighPercent);
            this.pnlStretch.Controls.Add(this.lblLowPercent);
            this.pnlStretch.Controls.Add(this.cboHighClip);
            this.pnlStretch.Controls.Add(this.lblHighClip);
            this.pnlStretch.Controls.Add(this.cboLowClip);
            this.pnlStretch.Controls.Add(this.lblLowClip);
            this.pnlStretch.Controls.Add(this.cboHighLimit);
            this.pnlStretch.Controls.Add(this.lblHighLimit);
            this.pnlStretch.Controls.Add(this.cboLowLimit);
            this.pnlStretch.Controls.Add(this.lblLowLimit);
            this.pnlStretch.Location = new System.Drawing.Point(15, 64);
            this.pnlStretch.Name = "pnlStretch";
            this.pnlStretch.Size = new System.Drawing.Size(345, 102);
            this.pnlStretch.TabIndex = 2;
            // 
            // lblHighPercent
            // 
            this.lblHighPercent.AutoSize = true;
            this.lblHighPercent.ForeColor = System.Drawing.Color.Blue;
            this.lblHighPercent.Location = new System.Drawing.Point(255, 85);
            this.lblHighPercent.Name = "lblHighPercent";
            this.lblHighPercent.Size = new System.Drawing.Size(30, 13);
            this.lblHighPercent.TabIndex = 44;
            this.lblHighPercent.Text = "2.5%";
            // 
            // lblLowPercent
            // 
            this.lblLowPercent.AutoSize = true;
            this.lblLowPercent.ForeColor = System.Drawing.Color.Blue;
            this.lblLowPercent.Location = new System.Drawing.Point(255, 60);
            this.lblLowPercent.Name = "lblLowPercent";
            this.lblLowPercent.Size = new System.Drawing.Size(30, 13);
            this.lblLowPercent.TabIndex = 43;
            this.lblLowPercent.Text = "2.5%";
            // 
            // cboHighClip
            // 
            this.cboHighClip.FormattingEnabled = true;
            this.cboHighClip.Items.AddRange(new object[] {
            "0.01",
            "0.02",
            "0.025",
            "0.03",
            "0.04",
            "0.05",
            "0.075",
            "0.1",
            "0.15"});
            this.cboHighClip.Location = new System.Drawing.Point(135, 81);
            this.cboHighClip.Name = "cboHighClip";
            this.cboHighClip.Size = new System.Drawing.Size(110, 21);
            this.cboHighClip.TabIndex = 7;
            this.cboHighClip.Text = "0.025";
            this.cboHighClip.TextChanged += new System.EventHandler(this.Percent_TextChanged);
            this.cboHighClip.Validating += new System.ComponentModel.CancelEventHandler(this.cboFloatVal_Validating);
            // 
            // lblHighClip
            // 
            this.lblHighClip.AutoSize = true;
            this.lblHighClip.Location = new System.Drawing.Point(0, 85);
            this.lblHighClip.Name = "lblHighClip";
            this.lblHighClip.Size = new System.Drawing.Size(90, 13);
            this.lblHighClip.TabIndex = 6;
            this.lblHighClip.Text = "High clip percent:";
            // 
            // cboLowClip
            // 
            this.cboLowClip.FormattingEnabled = true;
            this.cboLowClip.Items.AddRange(new object[] {
            "0.01",
            "0.02",
            "0.025",
            "0.03",
            "0.04",
            "0.05",
            "0.075",
            "0.1",
            "0.15"});
            this.cboLowClip.Location = new System.Drawing.Point(135, 54);
            this.cboLowClip.Name = "cboLowClip";
            this.cboLowClip.Size = new System.Drawing.Size(110, 21);
            this.cboLowClip.TabIndex = 5;
            this.cboLowClip.Text = "0.025";
            this.cboLowClip.TextChanged += new System.EventHandler(this.Percent_TextChanged);
            this.cboLowClip.Validating += new System.ComponentModel.CancelEventHandler(this.cboFloatVal_Validating);
            // 
            // lblLowClip
            // 
            this.lblLowClip.AutoSize = true;
            this.lblLowClip.Location = new System.Drawing.Point(0, 58);
            this.lblLowClip.Name = "lblLowClip";
            this.lblLowClip.Size = new System.Drawing.Size(88, 13);
            this.lblLowClip.TabIndex = 4;
            this.lblLowClip.Text = "Low clip percent:";
            // 
            // cboHighLimit
            // 
            this.cboHighLimit.FormattingEnabled = true;
            this.cboHighLimit.Items.AddRange(new object[] {
            "10",
            "20",
            "30",
            "40",
            "50",
            "75",
            "100",
            "200",
            "254",
            "255"});
            this.cboHighLimit.Location = new System.Drawing.Point(135, 27);
            this.cboHighLimit.Name = "cboHighLimit";
            this.cboHighLimit.Size = new System.Drawing.Size(110, 21);
            this.cboHighLimit.TabIndex = 3;
            this.cboHighLimit.Text = "255";
            this.cboHighLimit.Validating += new System.ComponentModel.CancelEventHandler(this.cboIntVal_Validating);
            // 
            // lblHighLimit
            // 
            this.lblHighLimit.AutoSize = true;
            this.lblHighLimit.Location = new System.Drawing.Point(0, 31);
            this.lblHighLimit.Name = "lblHighLimit";
            this.lblHighLimit.Size = new System.Drawing.Size(52, 13);
            this.lblHighLimit.TabIndex = 2;
            this.lblHighLimit.Text = "High limit:";
            // 
            // cboLowLimit
            // 
            this.cboLowLimit.FormattingEnabled = true;
            this.cboLowLimit.Items.AddRange(new object[] {
            "0",
            "1",
            "10",
            "20",
            "30",
            "40",
            "50",
            "75",
            "100"});
            this.cboLowLimit.Location = new System.Drawing.Point(135, 0);
            this.cboLowLimit.Name = "cboLowLimit";
            this.cboLowLimit.Size = new System.Drawing.Size(110, 21);
            this.cboLowLimit.TabIndex = 1;
            this.cboLowLimit.Text = "0";
            this.cboLowLimit.Validating += new System.ComponentModel.CancelEventHandler(this.cboIntVal_Validating);
            // 
            // lblLowLimit
            // 
            this.lblLowLimit.AutoSize = true;
            this.lblLowLimit.Location = new System.Drawing.Point(0, 4);
            this.lblLowLimit.Name = "lblLowLimit";
            this.lblLowLimit.Size = new System.Drawing.Size(50, 13);
            this.lblLowLimit.TabIndex = 0;
            this.lblLowLimit.Text = "Low limit:";
            // 
            // pnlSlide
            // 
            this.pnlSlide.Controls.Add(this.cboSlide);
            this.pnlSlide.Controls.Add(this.lblSlide);
            this.pnlSlide.Controls.Add(this.rbSlideUp);
            this.pnlSlide.Controls.Add(this.rbSlideDown);
            this.pnlSlide.Location = new System.Drawing.Point(15, 29);
            this.pnlSlide.Name = "pnlSlide";
            this.pnlSlide.Size = new System.Drawing.Size(197, 56);
            this.pnlSlide.TabIndex = 1;
            // 
            // cboSlide
            // 
            this.cboSlide.FormattingEnabled = true;
            this.cboSlide.Items.AddRange(new object[] {
            "10",
            "20",
            "30",
            "40",
            "50",
            "75",
            "100"});
            this.cboSlide.Location = new System.Drawing.Point(87, 35);
            this.cboSlide.Name = "cboSlide";
            this.cboSlide.Size = new System.Drawing.Size(110, 21);
            this.cboSlide.TabIndex = 3;
            this.cboSlide.Text = "20";
            this.cboSlide.Validating += new System.ComponentModel.CancelEventHandler(this.cboIntVal_Validating);
            // 
            // lblSlide
            // 
            this.lblSlide.AutoSize = true;
            this.lblSlide.Location = new System.Drawing.Point(0, 39);
            this.lblSlide.Name = "lblSlide";
            this.lblSlide.Size = new System.Drawing.Size(78, 13);
            this.lblSlide.TabIndex = 2;
            this.lblSlide.Text = "By the amount:";
            // 
            // rbSlideUp
            // 
            this.rbSlideUp.AutoSize = true;
            this.rbSlideUp.Checked = true;
            this.rbSlideUp.Location = new System.Drawing.Point(3, 0);
            this.rbSlideUp.Name = "rbSlideUp";
            this.rbSlideUp.Size = new System.Drawing.Size(39, 17);
            this.rbSlideUp.TabIndex = 0;
            this.rbSlideUp.TabStop = true;
            this.rbSlideUp.Text = "Up";
            this.rbSlideUp.UseVisualStyleBackColor = true;
            // 
            // rbSlideDown
            // 
            this.rbSlideDown.AutoSize = true;
            this.rbSlideDown.Location = new System.Drawing.Point(61, 0);
            this.rbSlideDown.Name = "rbSlideDown";
            this.rbSlideDown.Size = new System.Drawing.Size(53, 17);
            this.rbSlideDown.TabIndex = 1;
            this.rbSlideDown.Text = "Down";
            this.rbSlideDown.UseVisualStyleBackColor = true;
            // 
            // pnlEQ
            // 
            this.pnlEQ.Controls.Add(this.lblCLAHEPercent);
            this.pnlEQ.Controls.Add(this.cboBlockSize);
            this.pnlEQ.Controls.Add(this.lblBlockSize);
            this.pnlEQ.Controls.Add(this.lblBand);
            this.pnlEQ.Controls.Add(this.rbBlue);
            this.pnlEQ.Controls.Add(this.rbGreen);
            this.pnlEQ.Controls.Add(this.rbRed);
            this.pnlEQ.Controls.Add(this.rbValue);
            this.pnlEQ.Controls.Add(this.lblClahe);
            this.pnlEQ.Controls.Add(this.cboClahe);
            this.pnlEQ.Controls.Add(this.CLAHECheckBox);
            this.pnlEQ.Location = new System.Drawing.Point(15, 29);
            this.pnlEQ.Name = "pnlEQ";
            this.pnlEQ.Size = new System.Drawing.Size(335, 120);
            this.pnlEQ.TabIndex = 0;
            // 
            // lblCLAHEPercent
            // 
            this.lblCLAHEPercent.AutoSize = true;
            this.lblCLAHEPercent.ForeColor = System.Drawing.Color.Blue;
            this.lblCLAHEPercent.Location = new System.Drawing.Point(180, 70);
            this.lblCLAHEPercent.Name = "lblCLAHEPercent";
            this.lblCLAHEPercent.Size = new System.Drawing.Size(27, 13);
            this.lblCLAHEPercent.TabIndex = 43;
            this.lblCLAHEPercent.Text = "10%";
            // 
            // cboBlockSize
            // 
            this.cboBlockSize.FormattingEnabled = true;
            this.cboBlockSize.Items.AddRange(new object[] {
            "4",
            "8",
            "16",
            "32",
            "64",
            "128"});
            this.cboBlockSize.Location = new System.Drawing.Point(67, 35);
            this.cboBlockSize.Name = "cboBlockSize";
            this.cboBlockSize.Size = new System.Drawing.Size(110, 21);
            this.cboBlockSize.TabIndex = 6;
            this.cboBlockSize.Text = "4";
            this.cboBlockSize.Validating += new System.ComponentModel.CancelEventHandler(this.cboUIntVal_Validating);
            // 
            // lblBlockSize
            // 
            this.lblBlockSize.AutoSize = true;
            this.lblBlockSize.Location = new System.Drawing.Point(0, 39);
            this.lblBlockSize.Name = "lblBlockSize";
            this.lblBlockSize.Size = new System.Drawing.Size(58, 13);
            this.lblBlockSize.TabIndex = 5;
            this.lblBlockSize.Text = "Block size:";
            // 
            // lblBand
            // 
            this.lblBand.AutoSize = true;
            this.lblBand.Location = new System.Drawing.Point(0, 2);
            this.lblBand.Name = "lblBand";
            this.lblBand.Size = new System.Drawing.Size(52, 13);
            this.lblBand.TabIndex = 4;
            this.lblBand.Text = "On Band:";
            // 
            // rbBlue
            // 
            this.rbBlue.AutoSize = true;
            this.rbBlue.Location = new System.Drawing.Point(289, 0);
            this.rbBlue.Name = "rbBlue";
            this.rbBlue.Size = new System.Drawing.Size(46, 17);
            this.rbBlue.TabIndex = 3;
            this.rbBlue.Text = "Blue";
            this.rbBlue.UseVisualStyleBackColor = true;
            // 
            // rbGreen
            // 
            this.rbGreen.AutoSize = true;
            this.rbGreen.Location = new System.Drawing.Point(217, 0);
            this.rbGreen.Name = "rbGreen";
            this.rbGreen.Size = new System.Drawing.Size(54, 17);
            this.rbGreen.TabIndex = 2;
            this.rbGreen.Text = "Green";
            this.rbGreen.UseVisualStyleBackColor = true;
            // 
            // rbRed
            // 
            this.rbRed.AutoSize = true;
            this.rbRed.Location = new System.Drawing.Point(155, 1);
            this.rbRed.Name = "rbRed";
            this.rbRed.Size = new System.Drawing.Size(45, 17);
            this.rbRed.TabIndex = 1;
            this.rbRed.Text = "Red";
            this.rbRed.UseVisualStyleBackColor = true;
            // 
            // rbValue
            // 
            this.rbValue.AutoSize = true;
            this.rbValue.Checked = true;
            this.rbValue.Location = new System.Drawing.Point(72, 0);
            this.rbValue.Name = "rbValue";
            this.rbValue.Size = new System.Drawing.Size(70, 17);
            this.rbValue.TabIndex = 0;
            this.rbValue.TabStop = true;
            this.rbValue.Text = "Lightness";
            this.rbValue.UseVisualStyleBackColor = true;
            // 
            // lblClahe
            // 
            this.lblClahe.AutoSize = true;
            this.lblClahe.Location = new System.Drawing.Point(0, 70);
            this.lblClahe.Name = "lblClahe";
            this.lblClahe.Size = new System.Drawing.Size(67, 13);
            this.lblClahe.TabIndex = 8;
            this.lblClahe.Text = "Clip Percent:";
            // 
            // cboClahe
            // 
            this.cboClahe.FormattingEnabled = true;
            this.cboClahe.Items.AddRange(new object[] {
            "0",
            "0.01",
            "0.02",
            "0.05",
            "0.1",
            "0.25",
            "0.5",
            "0.75",
            "1"});
            this.cboClahe.Location = new System.Drawing.Point(67, 66);
            this.cboClahe.Name = "cboClahe";
            this.cboClahe.Size = new System.Drawing.Size(110, 21);
            this.cboClahe.TabIndex = 9;
            this.cboClahe.Text = "0.5";
            this.cboClahe.TextChanged += new System.EventHandler(this.Percent_TextChanged);
            this.cboClahe.Validating += new System.ComponentModel.CancelEventHandler(this.cboDoubleVal_Validating);
            // 
            // CLAHECheckBox
            // 
            this.CLAHECheckBox.AutoSize = true;
            this.CLAHECheckBox.Checked = true;
            this.CLAHECheckBox.CheckState = System.Windows.Forms.CheckState.Checked;
            this.CLAHECheckBox.Location = new System.Drawing.Point(3, 100);
            this.CLAHECheckBox.Name = "CLAHECheckBox";
            this.CLAHECheckBox.Size = new System.Drawing.Size(99, 17);
            this.CLAHECheckBox.TabIndex = 10;
            this.CLAHECheckBox.Text = "Sliding Window";
            this.CLAHECheckBox.UseVisualStyleBackColor = true;
            // 
            // btnHelp
            // 
            this.btnHelp.BackColor = System.Drawing.Color.Yellow;
            this.btnHelp.Location = new System.Drawing.Point(11, 273);
            this.btnHelp.Name = "btnHelp";
            this.btnHelp.Size = new System.Drawing.Size(60, 26);
            this.btnHelp.TabIndex = 17;
            this.btnHelp.Text = "Help";
            this.btnHelp.UseVisualStyleBackColor = false;
            this.btnHelp.Click += new System.EventHandler(this.btnHelp_Click);
            // 
            // btnCancel
            // 
            this.btnCancel.BackColor = System.Drawing.Color.OrangeRed;
            this.btnCancel.CausesValidation = false;
            this.btnCancel.Location = new System.Drawing.Point(373, 273);
            this.btnCancel.Name = "btnCancel";
            this.btnCancel.Size = new System.Drawing.Size(60, 26);
            this.btnCancel.TabIndex = 18;
            this.btnCancel.Text = "Cancel";
            this.btnCancel.UseVisualStyleBackColor = false;
            this.btnCancel.Click += new System.EventHandler(this.btnCancel_Click);
            // 
            // btnReset
            // 
            this.btnReset.BackColor = System.Drawing.Color.CornflowerBlue;
            this.btnReset.CausesValidation = false;
            this.btnReset.Location = new System.Drawing.Point(439, 273);
            this.btnReset.Name = "btnReset";
            this.btnReset.Size = new System.Drawing.Size(60, 26);
            this.btnReset.TabIndex = 19;
            this.btnReset.Text = "Reset";
            this.btnReset.UseVisualStyleBackColor = false;
            this.btnReset.Click += new System.EventHandler(this.btnReset_Click);
            // 
            // btnApply
            // 
            this.btnApply.BackColor = System.Drawing.Color.LimeGreen;
            this.btnApply.ForeColor = System.Drawing.Color.White;
            this.btnApply.Location = new System.Drawing.Point(505, 273);
            this.btnApply.Name = "btnApply";
            this.btnApply.Size = new System.Drawing.Size(60, 26);
            this.btnApply.TabIndex = 20;
            this.btnApply.Text = "Apply";
            this.btnApply.UseVisualStyleBackColor = false;
            this.btnApply.Click += new System.EventHandler(this.btnApply_Click);
            // 
            // rbCLAHE
            // 
            this.rbCLAHE.AutoSize = true;
            this.rbCLAHE.Location = new System.Drawing.Point(11, 99);
            this.rbCLAHE.Name = "rbCLAHE";
            this.rbCLAHE.Size = new System.Drawing.Size(147, 17);
            this.rbCLAHE.TabIndex = 21;
            this.rbCLAHE.Text = "Contrast Limited Adapt Eq";
            this.rbCLAHE.UseVisualStyleBackColor = true;
            this.rbCLAHE.Click += new System.EventHandler(this.rbHistogram_Click);
            // 
            // Histograms
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.grpParameters);
            this.Controls.Add(this.rbHistEQ);
            this.Controls.Add(this.rbHistSlide);
            this.Controls.Add(this.rbHistStretch);
            this.Controls.Add(this.rbHistShrink);
            this.Controls.Add(this.rbLocalEQ);
            this.Controls.Add(this.rbCLAHE);
            this.Controls.Add(this.rbACE);
            this.Controls.Add(this.rbACEII);
            this.Controls.Add(this.rbLog);
            this.Controls.Add(this.rbEXP);
            this.Controls.Add(this.rbColorContrast);
            this.Controls.Add(this.rbHistSpecify);
            this.Controls.Add(this.rbLinearMod);
            this.Controls.Add(this.rbGrayLevelMult);
            this.Controls.Add(this.grpHistogram1);
            this.Controls.Add(this.grpHistogram2);
            this.Controls.Add(this.grpHistogram3);
            this.Controls.Add(this.btnHelp);
            this.Controls.Add(this.btnCancel);
            this.Controls.Add(this.btnReset);
            this.Controls.Add(this.btnApply);
            this.Name = "Histograms";
            this.Size = new System.Drawing.Size(573, 305);
            this.grpParameters.ResumeLayout(false);
            this.pnlGrayLevelMult.ResumeLayout(false);
            this.pnlGrayLevelMult.PerformLayout();
            this.pnlLinearMod.ResumeLayout(false);
            this.pnlLinearMod.PerformLayout();
            this.pnlHistSpec.ResumeLayout(false);
            this.pnlHistSpec.PerformLayout();
            this.pnlACE.ResumeLayout(false);
            this.pnlACE.PerformLayout();
            this.pnlStretch.ResumeLayout(false);
            this.pnlStretch.PerformLayout();
            this.pnlSlide.ResumeLayout(false);
            this.pnlSlide.PerformLayout();
            this.pnlEQ.ResumeLayout(false);
            this.pnlEQ.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.RadioButton rbHistEQ;
        private System.Windows.Forms.RadioButton rbHistSlide;
        private System.Windows.Forms.RadioButton rbHistStretch;
        private System.Windows.Forms.RadioButton rbHistShrink;
        private System.Windows.Forms.RadioButton rbLocalEQ;
        private System.Windows.Forms.RadioButton rbACE;
        private System.Windows.Forms.RadioButton rbACEII;
        private System.Windows.Forms.RadioButton rbLog;
        private System.Windows.Forms.RadioButton rbEXP;
        private System.Windows.Forms.RadioButton rbColorContrast;
        private System.Windows.Forms.RadioButton rbHistSpecify;
        private System.Windows.Forms.RadioButton rbLinearMod;
        private System.Windows.Forms.RadioButton rbGrayLevelMult;
        private System.Windows.Forms.GroupBox grpHistogram1;
        private System.Windows.Forms.GroupBox grpHistogram2;
        private System.Windows.Forms.GroupBox grpHistogram3;
        private System.Windows.Forms.GroupBox grpParameters;
        private System.Windows.Forms.Panel pnlGrayLevelMult;
        private System.Windows.Forms.CheckBox chkByteClipping;
        private System.Windows.Forms.ComboBox cboFactor;
        private System.Windows.Forms.Label lblFactor;
        private System.Windows.Forms.Panel pnlLinearMod;
        private System.Windows.Forms.ComboBox cboSlope;
        private System.Windows.Forms.Label lblSlope;
        private System.Windows.Forms.ComboBox cboInitialVal;
        private System.Windows.Forms.Label lblInitialVal;
        private System.Windows.Forms.ComboBox cboEndVal;
        private System.Windows.Forms.Label lblEndVal;
        private System.Windows.Forms.ComboBox cboStartVal;
        private System.Windows.Forms.Label lblStartVal;
        private System.Windows.Forms.RadioButton rbZeroDataOOR;
        private System.Windows.Forms.RadioButton rbKeepDataOOR;
        private System.Windows.Forms.Panel pnlHistSpec;
        private System.Windows.Forms.CheckBox chkShowIntermediate;
        private System.Windows.Forms.ComboBox cboFormulaBlue;
        private System.Windows.Forms.Label lblFormulaBlue;
        private System.Windows.Forms.ComboBox cboFormulaGreen;
        private System.Windows.Forms.Label lblFormulaGreen;
        private System.Windows.Forms.ComboBox cboFormulaRed;
        private System.Windows.Forms.Label lblFormulaRed;
        private System.Windows.Forms.Panel pnlACE;
        private System.Windows.Forms.ComboBox cboLocalGainMax;
        private System.Windows.Forms.Label lblLocalGainMax;
        private System.Windows.Forms.ComboBox cboLocalGainMin;
        private System.Windows.Forms.Label lblLocalGainMin;
        private System.Windows.Forms.ComboBox cboKernelSize;
        private System.Windows.Forms.Label lblKernelSize;
        private System.Windows.Forms.ComboBox cboLocalGainFactor;
        private System.Windows.Forms.Label lblLocalGainFactor;
        private System.Windows.Forms.ComboBox cboLocalMeanFactor;
        private System.Windows.Forms.Label lblLocalMeanFactor;
        private System.Windows.Forms.Panel pnlStretch;
        private System.Windows.Forms.ComboBox cboHighClip;
        private System.Windows.Forms.Label lblHighClip;
        private System.Windows.Forms.ComboBox cboLowClip;
        private System.Windows.Forms.Label lblLowClip;
        private System.Windows.Forms.ComboBox cboHighLimit;
        private System.Windows.Forms.Label lblHighLimit;
        private System.Windows.Forms.ComboBox cboLowLimit;
        private System.Windows.Forms.Label lblLowLimit;
        private System.Windows.Forms.Panel pnlSlide;
        private System.Windows.Forms.ComboBox cboSlide;
        private System.Windows.Forms.Label lblSlide;
        private System.Windows.Forms.RadioButton rbSlideDown;
        private System.Windows.Forms.RadioButton rbSlideUp;
        private System.Windows.Forms.Panel pnlEQ;
        private System.Windows.Forms.ComboBox cboBlockSize;
        private System.Windows.Forms.Label lblBlockSize;
        private System.Windows.Forms.ComboBox cboClahe;
        private System.Windows.Forms.Label lblClahe;
        private System.Windows.Forms.Label lblBand;
        private System.Windows.Forms.RadioButton rbBlue;
        private System.Windows.Forms.RadioButton rbGreen;
        private System.Windows.Forms.RadioButton rbRed;
        private System.Windows.Forms.RadioButton rbValue;
        private System.Windows.Forms.Button btnHelp;
        private System.Windows.Forms.Button btnCancel;
        private System.Windows.Forms.Button btnReset;
        private System.Windows.Forms.Button btnApply;
        private System.Windows.Forms.RadioButton rbCLAHE;
        private System.Windows.Forms.CheckBox CLAHECheckBox;
        private System.Windows.Forms.Label lblLowPercent;
        private System.Windows.Forms.Label lblHighPercent;
        private System.Windows.Forms.Label lblCLAHEPercent;
    }
}
