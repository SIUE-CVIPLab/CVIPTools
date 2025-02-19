namespace CVIPGUI.Restoration
{
    partial class FrequencyFilter
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(FrequencyFilter));
            this.rbInverse = new System.Windows.Forms.RadioButton();
            this.rbGeometricMean = new System.Windows.Forms.RadioButton();
            this.rbPowerSpectrumEQ = new System.Windows.Forms.RadioButton();
            this.rbConstrLeastSqu = new System.Windows.Forms.RadioButton();
            this.rbWiener = new System.Windows.Forms.RadioButton();
            this.rbPractWiener = new System.Windows.Forms.RadioButton();
            this.rbParaWiener = new System.Windows.Forms.RadioButton();
            this.rbNotch = new System.Windows.Forms.RadioButton();
            this.grpFilters = new System.Windows.Forms.GroupBox();
            this.lblWienerCoefficient = new System.Windows.Forms.Label();
            this.picWienerCoefficient = new System.Windows.Forms.PictureBox();
            this.lblDegradedImage = new System.Windows.Forms.Label();
            this.txtDegradedImage = new System.Windows.Forms.TextBox();
            this.grpDegradationFunction = new System.Windows.Forms.GroupBox();
            this.pnlDegradationFunction = new System.Windows.Forms.Panel();
            this.lblLimitGain2 = new System.Windows.Forms.Label();
            this.lblLimitGain1 = new System.Windows.Forms.Label();
            this.cboLimitGain = new System.Windows.Forms.ComboBox();
            this.lblCutoffFreq = new System.Windows.Forms.Label();
            this.cboCutoffFreq = new System.Windows.Forms.ComboBox();
            this.grpBlurMask = new System.Windows.Forms.GroupBox();
            this.lblBlurWeight = new System.Windows.Forms.Label();
            this.cboBlurWeight = new System.Windows.Forms.ComboBox();
            this.lblBlurMethod = new System.Windows.Forms.Label();
            this.cboBlurMethod = new System.Windows.Forms.ComboBox();
            this.lblBlurShape = new System.Windows.Forms.Label();
            this.cboBlurShape = new System.Windows.Forms.ComboBox();
            this.btnEditMask = new System.Windows.Forms.Button();
            this.lblMaskHeight = new System.Windows.Forms.Label();
            this.cboMaskHeight = new System.Windows.Forms.ComboBox();
            this.lblMaskWidth = new System.Windows.Forms.Label();
            this.cboMaskWidth = new System.Windows.Forms.ComboBox();
            this.cboDegradationImage = new System.Windows.Forms.ComboBox();
            this.rbUseImage = new System.Windows.Forms.RadioButton();
            this.rbSpecifyFunc = new System.Windows.Forms.RadioButton();
            this.pnlParameters = new System.Windows.Forms.Panel();
            this.lblK = new System.Windows.Forms.Label();
            this.cboK = new System.Windows.Forms.ComboBox();
            this.lblAlpha = new System.Windows.Forms.Label();
            this.cboAlpha = new System.Windows.Forms.ComboBox();
            this.lblSmoothFunc = new System.Windows.Forms.Label();
            this.cboSmoothFunc = new System.Windows.Forms.ComboBox();
            this.lblGamma = new System.Windows.Forms.Label();
            this.cboGamma = new System.Windows.Forms.ComboBox();
            this.lblOriginalImage = new System.Windows.Forms.Label();
            this.cboOriginalImage = new System.Windows.Forms.ComboBox();
            this.lblNoiseImage = new System.Windows.Forms.Label();
            this.cboNoiseImage = new System.Windows.Forms.ComboBox();
            this.lblRestorationEqu = new System.Windows.Forms.Label();
            this.picRestorationEqu = new System.Windows.Forms.PictureBox();
            this.grpNotchFilter = new System.Windows.Forms.GroupBox();
            this.pnlNotch = new System.Windows.Forms.Panel();
            this.btnAddNotch = new System.Windows.Forms.Button();
            this.btnRedoNotch = new System.Windows.Forms.Button();
            this.lblNotchSize = new System.Windows.Forms.Label();
            this.cboNotchSize = new System.Windows.Forms.ComboBox();
            this.lblNotchRow = new System.Windows.Forms.Label();
            this.txtNotchRow = new System.Windows.Forms.TextBox();
            this.lblNotchCol = new System.Windows.Forms.Label();
            this.txtNotchCol = new System.Windows.Forms.TextBox();
            this.lblPoint = new System.Windows.Forms.Label();
            this.cboPoint = new System.Windows.Forms.ComboBox();
            this.lblInfo = new System.Windows.Forms.Label();
            this.lblTransformType = new System.Windows.Forms.Label();
            this.cboTransformType = new System.Windows.Forms.ComboBox();
            this.btnHelp = new System.Windows.Forms.Button();
            this.btnCancel = new System.Windows.Forms.Button();
            this.btnReset = new System.Windows.Forms.Button();
            this.btnApply = new System.Windows.Forms.Button();
            this.toolTipImageCombo = new System.Windows.Forms.ToolTip(this.components);
            this.grpFilters.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.picWienerCoefficient)).BeginInit();
            this.grpDegradationFunction.SuspendLayout();
            this.pnlDegradationFunction.SuspendLayout();
            this.grpBlurMask.SuspendLayout();
            this.pnlParameters.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.picRestorationEqu)).BeginInit();
            this.grpNotchFilter.SuspendLayout();
            this.pnlNotch.SuspendLayout();
            this.SuspendLayout();
            // 
            // rbInverse
            // 
            this.rbInverse.AutoSize = true;
            this.rbInverse.Checked = true;
            this.rbInverse.Location = new System.Drawing.Point(18, 23);
            this.rbInverse.Name = "rbInverse";
            this.rbInverse.Size = new System.Drawing.Size(60, 17);
            this.rbInverse.TabIndex = 0;
            this.rbInverse.TabStop = true;
            this.rbInverse.Text = "Inverse";
            this.rbInverse.UseVisualStyleBackColor = true;
            this.rbInverse.CheckedChanged += new System.EventHandler(this.rbInverse_CheckedChanged);
            this.rbInverse.Click += new System.EventHandler(this.rbFreqFilter_Click);
            // 
            // rbGeometricMean
            // 
            this.rbGeometricMean.AutoSize = true;
            this.rbGeometricMean.Location = new System.Drawing.Point(18, 48);
            this.rbGeometricMean.Name = "rbGeometricMean";
            this.rbGeometricMean.Size = new System.Drawing.Size(103, 17);
            this.rbGeometricMean.TabIndex = 1;
            this.rbGeometricMean.Text = "Geometric Mean";
            this.rbGeometricMean.UseVisualStyleBackColor = true;
            this.rbGeometricMean.Click += new System.EventHandler(this.rbFreqFilter_Click);
            // 
            // rbPowerSpectrumEQ
            // 
            this.rbPowerSpectrumEQ.AutoSize = true;
            this.rbPowerSpectrumEQ.Location = new System.Drawing.Point(18, 73);
            this.rbPowerSpectrumEQ.Name = "rbPowerSpectrumEQ";
            this.rbPowerSpectrumEQ.Size = new System.Drawing.Size(163, 17);
            this.rbPowerSpectrumEQ.TabIndex = 2;
            this.rbPowerSpectrumEQ.Text = "Power Spectrum Equalization";
            this.rbPowerSpectrumEQ.UseVisualStyleBackColor = true;
            this.rbPowerSpectrumEQ.Click += new System.EventHandler(this.rbFreqFilter_Click);
            // 
            // rbConstrLeastSqu
            // 
            this.rbConstrLeastSqu.AutoSize = true;
            this.rbConstrLeastSqu.Location = new System.Drawing.Point(18, 98);
            this.rbConstrLeastSqu.Name = "rbConstrLeastSqu";
            this.rbConstrLeastSqu.Size = new System.Drawing.Size(152, 17);
            this.rbConstrLeastSqu.TabIndex = 3;
            this.rbConstrLeastSqu.Text = "Constrained Least Squares";
            this.rbConstrLeastSqu.UseVisualStyleBackColor = true;
            this.rbConstrLeastSqu.Click += new System.EventHandler(this.rbFreqFilter_Click);
            // 
            // rbWiener
            // 
            this.rbWiener.AutoSize = true;
            this.rbWiener.Location = new System.Drawing.Point(18, 123);
            this.rbWiener.Name = "rbWiener";
            this.rbWiener.Size = new System.Drawing.Size(59, 17);
            this.rbWiener.TabIndex = 4;
            this.rbWiener.Text = "Wiener";
            this.rbWiener.UseVisualStyleBackColor = true;
            this.rbWiener.Click += new System.EventHandler(this.rbFreqFilter_Click);
            // 
            // rbPractWiener
            // 
            this.rbPractWiener.AutoSize = true;
            this.rbPractWiener.Location = new System.Drawing.Point(18, 148);
            this.rbPractWiener.Name = "rbPractWiener";
            this.rbPractWiener.Size = new System.Drawing.Size(103, 17);
            this.rbPractWiener.TabIndex = 5;
            this.rbPractWiener.Text = "Practical Wiener";
            this.rbPractWiener.UseVisualStyleBackColor = true;
            this.rbPractWiener.Click += new System.EventHandler(this.rbFreqFilter_Click);
            // 
            // rbParaWiener
            // 
            this.rbParaWiener.AutoSize = true;
            this.rbParaWiener.Location = new System.Drawing.Point(18, 173);
            this.rbParaWiener.Name = "rbParaWiener";
            this.rbParaWiener.Size = new System.Drawing.Size(112, 17);
            this.rbParaWiener.TabIndex = 6;
            this.rbParaWiener.Text = "Parametric Wiener";
            this.rbParaWiener.UseVisualStyleBackColor = true;
            this.rbParaWiener.Click += new System.EventHandler(this.rbFreqFilter_Click);
            // 
            // rbNotch
            // 
            this.rbNotch.AutoSize = true;
            this.rbNotch.Location = new System.Drawing.Point(18, 390);
            this.rbNotch.Name = "rbNotch";
            this.rbNotch.Size = new System.Drawing.Size(79, 17);
            this.rbNotch.TabIndex = 7;
            this.rbNotch.Text = "Notch Filter";
            this.rbNotch.UseVisualStyleBackColor = true;
            this.rbNotch.Click += new System.EventHandler(this.rbFreqFilter_Click);
            // 
            // grpFilters
            // 
            this.grpFilters.Controls.Add(this.lblWienerCoefficient);
            this.grpFilters.Controls.Add(this.picWienerCoefficient);
            this.grpFilters.Location = new System.Drawing.Point(6, 6);
            this.grpFilters.Name = "grpFilters";
            this.grpFilters.Size = new System.Drawing.Size(181, 270);
            this.grpFilters.TabIndex = 8;
            this.grpFilters.TabStop = false;
            this.grpFilters.Text = "Restoration Filters";
            // 
            // lblWienerCoefficient
            // 
            this.lblWienerCoefficient.AutoSize = true;
            this.lblWienerCoefficient.ForeColor = System.Drawing.SystemColors.HotTrack;
            this.lblWienerCoefficient.Location = new System.Drawing.Point(10, 218);
            this.lblWienerCoefficient.Name = "lblWienerCoefficient";
            this.lblWienerCoefficient.Size = new System.Drawing.Size(100, 13);
            this.lblWienerCoefficient.TabIndex = 1;
            this.lblWienerCoefficient.Text = "Alpha=0, Gamma=0";
            // 
            // picWienerCoefficient
            // 
            this.picWienerCoefficient.Image = ((System.Drawing.Image)(resources.GetObject("picWienerCoefficient.Image")));
            this.picWienerCoefficient.Location = new System.Drawing.Point(80, 201);
            this.picWienerCoefficient.Name = "picWienerCoefficient";
            this.picWienerCoefficient.Size = new System.Drawing.Size(81, 53);
            this.picWienerCoefficient.TabIndex = 0;
            this.picWienerCoefficient.TabStop = false;
            // 
            // lblDegradedImage
            // 
            this.lblDegradedImage.AutoSize = true;
            this.lblDegradedImage.Location = new System.Drawing.Point(199, 7);
            this.lblDegradedImage.Name = "lblDegradedImage";
            this.lblDegradedImage.Size = new System.Drawing.Size(149, 13);
            this.lblDegradedImage.TabIndex = 9;
            this.lblDegradedImage.Text = "Degraded Image or Spectrum:";
            // 
            // txtDegradedImage
            // 
            this.txtDegradedImage.BackColor = System.Drawing.SystemColors.Menu;
            this.txtDegradedImage.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.txtDegradedImage.ForeColor = System.Drawing.Color.Blue;
            this.txtDegradedImage.Location = new System.Drawing.Point(352, 7);
            this.txtDegradedImage.Name = "txtDegradedImage";
            this.txtDegradedImage.ReadOnly = true;
            this.txtDegradedImage.Size = new System.Drawing.Size(238, 13);
            this.txtDegradedImage.TabIndex = 10;
            this.txtDegradedImage.MouseEnter += new System.EventHandler(this.cboImage_MouseEnter);
            // 
            // grpDegradationFunction
            // 
            this.grpDegradationFunction.Controls.Add(this.pnlDegradationFunction);
            this.grpDegradationFunction.Location = new System.Drawing.Point(193, 25);
            this.grpDegradationFunction.Name = "grpDegradationFunction";
            this.grpDegradationFunction.Size = new System.Drawing.Size(401, 165);
            this.grpDegradationFunction.TabIndex = 11;
            this.grpDegradationFunction.TabStop = false;
            this.grpDegradationFunction.Text = "Degradation Function";
            // 
            // pnlDegradationFunction
            // 
            this.pnlDegradationFunction.Controls.Add(this.lblLimitGain2);
            this.pnlDegradationFunction.Controls.Add(this.lblLimitGain1);
            this.pnlDegradationFunction.Controls.Add(this.cboLimitGain);
            this.pnlDegradationFunction.Controls.Add(this.lblCutoffFreq);
            this.pnlDegradationFunction.Controls.Add(this.cboCutoffFreq);
            this.pnlDegradationFunction.Controls.Add(this.grpBlurMask);
            this.pnlDegradationFunction.Controls.Add(this.cboDegradationImage);
            this.pnlDegradationFunction.Controls.Add(this.rbUseImage);
            this.pnlDegradationFunction.Controls.Add(this.rbSpecifyFunc);
            this.pnlDegradationFunction.Location = new System.Drawing.Point(5, 17);
            this.pnlDegradationFunction.Name = "pnlDegradationFunction";
            this.pnlDegradationFunction.Size = new System.Drawing.Size(393, 142);
            this.pnlDegradationFunction.TabIndex = 9;
            // 
            // lblLimitGain2
            // 
            this.lblLimitGain2.AutoSize = true;
            this.lblLimitGain2.Location = new System.Drawing.Point(318, 125);
            this.lblLimitGain2.Name = "lblLimitGain2";
            this.lblLimitGain2.Size = new System.Drawing.Size(75, 13);
            this.lblLimitGain2.TabIndex = 8;
            this.lblLimitGain2.Text = "times DC gain.";
            // 
            // lblLimitGain1
            // 
            this.lblLimitGain1.AutoSize = true;
            this.lblLimitGain1.Location = new System.Drawing.Point(154, 125);
            this.lblLimitGain1.Name = "lblLimitGain1";
            this.lblLimitGain1.Size = new System.Drawing.Size(107, 13);
            this.lblLimitGain1.TabIndex = 7;
            this.lblLimitGain1.Text = "Limit gain of R(u,v) to";
            this.lblLimitGain1.TextAlign = System.Drawing.ContentAlignment.TopRight;
            // 
            // cboLimitGain
            // 
            this.cboLimitGain.FormattingEnabled = true;
            this.cboLimitGain.Items.AddRange(new object[] {
            "None",
            "1",
            "10",
            "50",
            "100",
            "1000"});
            this.cboLimitGain.Location = new System.Drawing.Point(262, 121);
            this.cboLimitGain.Name = "cboLimitGain";
            this.cboLimitGain.Size = new System.Drawing.Size(55, 21);
            this.cboLimitGain.TabIndex = 6;
            this.cboLimitGain.Text = "100";
            this.cboLimitGain.Validating += new System.ComponentModel.CancelEventHandler(this.cboLimitGain_Validating);
            // 
            // lblCutoffFreq
            // 
            this.lblCutoffFreq.AutoSize = true;
            this.lblCutoffFreq.Location = new System.Drawing.Point(0, 125);
            this.lblCutoffFreq.Name = "lblCutoffFreq";
            this.lblCutoffFreq.Size = new System.Drawing.Size(88, 13);
            this.lblCutoffFreq.TabIndex = 5;
            this.lblCutoffFreq.Text = "Cutoff Frequency";
            // 
            // cboCutoffFreq
            // 
            this.cboCutoffFreq.FormattingEnabled = true;
            this.cboCutoffFreq.Items.AddRange(new object[] {
            "0",
            "4",
            "8",
            "16",
            "32",
            "64",
            "128"});
            this.cboCutoffFreq.Location = new System.Drawing.Point(89, 121);
            this.cboCutoffFreq.Name = "cboCutoffFreq";
            this.cboCutoffFreq.Size = new System.Drawing.Size(55, 21);
            this.cboCutoffFreq.TabIndex = 4;
            this.cboCutoffFreq.Text = "32";
            this.cboCutoffFreq.Validating += new System.ComponentModel.CancelEventHandler(this.cboDoubleVal_Validating);
            // 
            // grpBlurMask
            // 
            this.grpBlurMask.Controls.Add(this.lblBlurWeight);
            this.grpBlurMask.Controls.Add(this.cboBlurWeight);
            this.grpBlurMask.Controls.Add(this.lblBlurMethod);
            this.grpBlurMask.Controls.Add(this.cboBlurMethod);
            this.grpBlurMask.Controls.Add(this.lblBlurShape);
            this.grpBlurMask.Controls.Add(this.cboBlurShape);
            this.grpBlurMask.Controls.Add(this.btnEditMask);
            this.grpBlurMask.Controls.Add(this.lblMaskHeight);
            this.grpBlurMask.Controls.Add(this.cboMaskHeight);
            this.grpBlurMask.Controls.Add(this.lblMaskWidth);
            this.grpBlurMask.Controls.Add(this.cboMaskWidth);
            this.grpBlurMask.Location = new System.Drawing.Point(3, 21);
            this.grpBlurMask.Name = "grpBlurMask";
            this.grpBlurMask.Size = new System.Drawing.Size(385, 94);
            this.grpBlurMask.TabIndex = 3;
            this.grpBlurMask.TabStop = false;
            // 
            // lblBlurWeight
            // 
            this.lblBlurWeight.AutoSize = true;
            this.lblBlurWeight.Location = new System.Drawing.Point(249, 70);
            this.lblBlurWeight.Name = "lblBlurWeight";
            this.lblBlurWeight.Size = new System.Drawing.Size(44, 13);
            this.lblBlurWeight.TabIndex = 14;
            this.lblBlurWeight.Text = "Weight:";
            this.lblBlurWeight.TextAlign = System.Drawing.ContentAlignment.TopRight;
            // 
            // cboBlurWeight
            // 
            this.cboBlurWeight.FormattingEnabled = true;
            this.cboBlurWeight.Items.AddRange(new object[] {
            "100.0",
            "10.0",
            "1.0",
            "0.1",
            "0.01",
            "0.001"});
            this.cboBlurWeight.Location = new System.Drawing.Point(294, 66);
            this.cboBlurWeight.Name = "cboBlurWeight";
            this.cboBlurWeight.Size = new System.Drawing.Size(50, 21);
            this.cboBlurWeight.TabIndex = 13;
            this.cboBlurWeight.Text = "1.0";
            this.cboBlurWeight.SelectedIndexChanged += new System.EventHandler(this.cboBlurParameter_Changed);
            this.cboBlurWeight.Validating += new System.ComponentModel.CancelEventHandler(this.cboFloatVal_Validating);
            this.cboBlurWeight.Validated += new System.EventHandler(this.cboBlurParameter_Changed);
            // 
            // lblBlurMethod
            // 
            this.lblBlurMethod.AutoSize = true;
            this.lblBlurMethod.Location = new System.Drawing.Point(9, 70);
            this.lblBlurMethod.Name = "lblBlurMethod";
            this.lblBlurMethod.Size = new System.Drawing.Size(67, 13);
            this.lblBlurMethod.TabIndex = 12;
            this.lblBlurMethod.Text = "Blur Method:";
            this.lblBlurMethod.TextAlign = System.Drawing.ContentAlignment.TopRight;
            // 
            // cboBlurMethod
            // 
            this.cboBlurMethod.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cboBlurMethod.FormattingEnabled = true;
            this.cboBlurMethod.Items.AddRange(new object[] {
            "Constant",
            "Center-Weighted Constant",
            "Gaussian"});
            this.cboBlurMethod.Location = new System.Drawing.Point(77, 66);
            this.cboBlurMethod.Name = "cboBlurMethod";
            this.cboBlurMethod.Size = new System.Drawing.Size(157, 21);
            this.cboBlurMethod.TabIndex = 11;
            this.cboBlurMethod.SelectedIndexChanged += new System.EventHandler(this.cboBlurParameter_Changed);
            // 
            // lblBlurShape
            // 
            this.lblBlurShape.AutoSize = true;
            this.lblBlurShape.Location = new System.Drawing.Point(14, 44);
            this.lblBlurShape.Name = "lblBlurShape";
            this.lblBlurShape.Size = new System.Drawing.Size(62, 13);
            this.lblBlurShape.TabIndex = 6;
            this.lblBlurShape.Text = "Blur Shape:";
            this.lblBlurShape.TextAlign = System.Drawing.ContentAlignment.TopRight;
            // 
            // cboBlurShape
            // 
            this.cboBlurShape.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cboBlurShape.FormattingEnabled = true;
            this.cboBlurShape.Items.AddRange(new object[] {
            "Circle",
            "Rectangle",
            "Horizontal line",
            "Vertical line",
            "Slash",
            "Backslash"});
            this.cboBlurShape.Location = new System.Drawing.Point(77, 40);
            this.cboBlurShape.Name = "cboBlurShape";
            this.cboBlurShape.Size = new System.Drawing.Size(97, 21);
            this.cboBlurShape.TabIndex = 5;
            this.cboBlurShape.SelectedIndexChanged += new System.EventHandler(this.cboBlurShape_SelectedIndexChanged);
            // 
            // btnEditMask
            // 
            this.btnEditMask.Location = new System.Drawing.Point(293, 12);
            this.btnEditMask.Name = "btnEditMask";
            this.btnEditMask.Size = new System.Drawing.Size(75, 24);
            this.btnEditMask.TabIndex = 4;
            this.btnEditMask.Text = "Edit Mask";
            this.btnEditMask.UseVisualStyleBackColor = true;
            this.btnEditMask.Click += new System.EventHandler(this.btnEditMask_Click);
            // 
            // lblMaskHeight
            // 
            this.lblMaskHeight.AutoSize = true;
            this.lblMaskHeight.Location = new System.Drawing.Point(148, 18);
            this.lblMaskHeight.Name = "lblMaskHeight";
            this.lblMaskHeight.Size = new System.Drawing.Size(70, 13);
            this.lblMaskHeight.TabIndex = 3;
            this.lblMaskHeight.Text = "Mask Height:";
            this.lblMaskHeight.TextAlign = System.Drawing.ContentAlignment.TopRight;
            // 
            // cboMaskHeight
            // 
            this.cboMaskHeight.FormattingEnabled = true;
            this.cboMaskHeight.Items.AddRange(new object[] {
            "3",
            "5",
            "7",
            "9",
            "11",
            "13"});
            this.cboMaskHeight.Location = new System.Drawing.Point(219, 14);
            this.cboMaskHeight.Name = "cboMaskHeight";
            this.cboMaskHeight.Size = new System.Drawing.Size(50, 21);
            this.cboMaskHeight.TabIndex = 2;
            this.cboMaskHeight.Text = "9";
            this.cboMaskHeight.SelectedIndexChanged += new System.EventHandler(this.cboMaskSize_Validated);
            this.cboMaskHeight.Validating += new System.ComponentModel.CancelEventHandler(this.cboMaskSize_Validating);
            this.cboMaskHeight.Validated += new System.EventHandler(this.cboMaskSize_Validated);
            // 
            // lblMaskWidth
            // 
            this.lblMaskWidth.AutoSize = true;
            this.lblMaskWidth.Location = new System.Drawing.Point(9, 18);
            this.lblMaskWidth.Name = "lblMaskWidth";
            this.lblMaskWidth.Size = new System.Drawing.Size(67, 13);
            this.lblMaskWidth.TabIndex = 1;
            this.lblMaskWidth.Text = "Mask Width:";
            this.lblMaskWidth.TextAlign = System.Drawing.ContentAlignment.TopRight;
            // 
            // cboMaskWidth
            // 
            this.cboMaskWidth.FormattingEnabled = true;
            this.cboMaskWidth.Items.AddRange(new object[] {
            "3",
            "5",
            "7",
            "9",
            "11",
            "13"});
            this.cboMaskWidth.Location = new System.Drawing.Point(77, 14);
            this.cboMaskWidth.Name = "cboMaskWidth";
            this.cboMaskWidth.Size = new System.Drawing.Size(50, 21);
            this.cboMaskWidth.TabIndex = 0;
            this.cboMaskWidth.Text = "9";
            this.cboMaskWidth.SelectedIndexChanged += new System.EventHandler(this.cboMaskSize_Validated);
            this.cboMaskWidth.Validating += new System.ComponentModel.CancelEventHandler(this.cboMaskSize_Validating);
            this.cboMaskWidth.Validated += new System.EventHandler(this.cboMaskSize_Validated);
            // 
            // cboDegradationImage
            // 
            this.cboDegradationImage.DisplayMember = "Text";
            this.cboDegradationImage.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cboDegradationImage.DropDownWidth = 300;
            this.cboDegradationImage.FormattingEnabled = true;
            this.cboDegradationImage.Location = new System.Drawing.Point(210, 0);
            this.cboDegradationImage.Name = "cboDegradationImage";
            this.cboDegradationImage.Size = new System.Drawing.Size(178, 21);
            this.cboDegradationImage.TabIndex = 2;
            this.cboDegradationImage.SelectedIndexChanged += new System.EventHandler(this.cboImage_SelectedIndexChanged);
            this.cboDegradationImage.MouseEnter += new System.EventHandler(this.cboImage_MouseEnter);
            // 
            // rbUseImage
            // 
            this.rbUseImage.AutoSize = true;
            this.rbUseImage.Location = new System.Drawing.Point(121, 2);
            this.rbUseImage.Name = "rbUseImage";
            this.rbUseImage.Size = new System.Drawing.Size(90, 17);
            this.rbUseImage.TabIndex = 1;
            this.rbUseImage.Text = "Use an image";
            this.rbUseImage.UseVisualStyleBackColor = true;
            this.rbUseImage.Click += new System.EventHandler(this.rbDegradationFunction_Click);
            // 
            // rbSpecifyFunc
            // 
            this.rbSpecifyFunc.AutoSize = true;
            this.rbSpecifyFunc.Checked = true;
            this.rbSpecifyFunc.Location = new System.Drawing.Point(7, 2);
            this.rbSpecifyFunc.Name = "rbSpecifyFunc";
            this.rbSpecifyFunc.Size = new System.Drawing.Size(110, 17);
            this.rbSpecifyFunc.TabIndex = 0;
            this.rbSpecifyFunc.TabStop = true;
            this.rbSpecifyFunc.Text = "Specify a function";
            this.rbSpecifyFunc.UseVisualStyleBackColor = true;
            this.rbSpecifyFunc.Click += new System.EventHandler(this.rbDegradationFunction_Click);
            // 
            // pnlParameters
            // 
            this.pnlParameters.Controls.Add(this.lblK);
            this.pnlParameters.Controls.Add(this.cboK);
            this.pnlParameters.Controls.Add(this.lblAlpha);
            this.pnlParameters.Controls.Add(this.cboAlpha);
            this.pnlParameters.Controls.Add(this.lblSmoothFunc);
            this.pnlParameters.Controls.Add(this.cboSmoothFunc);
            this.pnlParameters.Controls.Add(this.lblGamma);
            this.pnlParameters.Controls.Add(this.cboGamma);
            this.pnlParameters.Controls.Add(this.lblOriginalImage);
            this.pnlParameters.Controls.Add(this.cboOriginalImage);
            this.pnlParameters.Controls.Add(this.lblNoiseImage);
            this.pnlParameters.Controls.Add(this.cboNoiseImage);
            this.pnlParameters.Location = new System.Drawing.Point(193, 186);
            this.pnlParameters.Name = "pnlParameters";
            this.pnlParameters.Size = new System.Drawing.Size(401, 91);
            this.pnlParameters.TabIndex = 12;
            // 
            // lblK
            // 
            this.lblK.AutoSize = true;
            this.lblK.Location = new System.Drawing.Point(150, 68);
            this.lblK.Name = "lblK";
            this.lblK.Size = new System.Drawing.Size(17, 13);
            this.lblK.TabIndex = 11;
            this.lblK.Text = "K:";
            // 
            // cboK
            // 
            this.cboK.FormattingEnabled = true;
            this.cboK.Items.AddRange(new object[] {
            "0.0",
            "0.01",
            "0.05",
            "0.1",
            "0.3",
            "0.5",
            "0.8",
            "1.0"});
            this.cboK.Location = new System.Drawing.Point(168, 64);
            this.cboK.Name = "cboK";
            this.cboK.Size = new System.Drawing.Size(55, 21);
            this.cboK.TabIndex = 10;
            this.cboK.Text = "1.0";
            this.cboK.SelectedIndexChanged += new System.EventHandler(this.cboK_SelectedIndexChanged);
            this.cboK.Validating += new System.ComponentModel.CancelEventHandler(this.cboDoubleVal_Validating);
            // 
            // lblAlpha
            // 
            this.lblAlpha.AutoSize = true;
            this.lblAlpha.Location = new System.Drawing.Point(36, 68);
            this.lblAlpha.Name = "lblAlpha";
            this.lblAlpha.Size = new System.Drawing.Size(37, 13);
            this.lblAlpha.TabIndex = 9;
            this.lblAlpha.Text = "Alpha:";
            // 
            // cboAlpha
            // 
            this.cboAlpha.FormattingEnabled = true;
            this.cboAlpha.Items.AddRange(new object[] {
            "0.0",
            "0.111",
            "0.125",
            "0.167",
            "0.25",
            "0.333",
            "0.5",
            "0.667"});
            this.cboAlpha.Location = new System.Drawing.Point(73, 64);
            this.cboAlpha.Name = "cboAlpha";
            this.cboAlpha.Size = new System.Drawing.Size(55, 21);
            this.cboAlpha.TabIndex = 8;
            this.cboAlpha.Text = "0.0";
            this.cboAlpha.Validating += new System.ComponentModel.CancelEventHandler(this.cboDoubleVal_Validating);
            // 
            // lblSmoothFunc
            // 
            this.lblSmoothFunc.AutoSize = true;
            this.lblSmoothFunc.Location = new System.Drawing.Point(148, 42);
            this.lblSmoothFunc.Name = "lblSmoothFunc";
            this.lblSmoothFunc.Size = new System.Drawing.Size(162, 13);
            this.lblSmoothFunc.TabIndex = 7;
            this.lblSmoothFunc.Text = "Smoothness Constraint Function:";
            // 
            // cboSmoothFunc
            // 
            this.cboSmoothFunc.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cboSmoothFunc.FormattingEnabled = true;
            this.cboSmoothFunc.Items.AddRange(new object[] {
            "Laplacian1",
            "Laplacian2",
            "Laplacian3",
            "Laplacian4"});
            this.cboSmoothFunc.Location = new System.Drawing.Point(311, 38);
            this.cboSmoothFunc.Name = "cboSmoothFunc";
            this.cboSmoothFunc.Size = new System.Drawing.Size(83, 21);
            this.cboSmoothFunc.TabIndex = 6;
            // 
            // lblGamma
            // 
            this.lblGamma.AutoSize = true;
            this.lblGamma.Location = new System.Drawing.Point(27, 42);
            this.lblGamma.Name = "lblGamma";
            this.lblGamma.Size = new System.Drawing.Size(46, 13);
            this.lblGamma.TabIndex = 5;
            this.lblGamma.Text = "Gamma:";
            // 
            // cboGamma
            // 
            this.cboGamma.FormattingEnabled = true;
            this.cboGamma.Items.AddRange(new object[] {
            "0.0",
            "0.5",
            "0.8",
            "1.0"});
            this.cboGamma.Location = new System.Drawing.Point(73, 38);
            this.cboGamma.Name = "cboGamma";
            this.cboGamma.Size = new System.Drawing.Size(55, 21);
            this.cboGamma.TabIndex = 4;
            this.cboGamma.Text = "0.5";
            this.cboGamma.Validating += new System.ComponentModel.CancelEventHandler(this.cboDoubleVal_Validating);
            // 
            // lblOriginalImage
            // 
            this.lblOriginalImage.AutoSize = true;
            this.lblOriginalImage.Location = new System.Drawing.Point(198, 16);
            this.lblOriginalImage.Name = "lblOriginalImage";
            this.lblOriginalImage.Size = new System.Drawing.Size(76, 13);
            this.lblOriginalImage.TabIndex = 3;
            this.lblOriginalImage.Text = "Original image:";
            // 
            // cboOriginalImage
            // 
            this.cboOriginalImage.DisplayMember = "Text";
            this.cboOriginalImage.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cboOriginalImage.DropDownWidth = 300;
            this.cboOriginalImage.FormattingEnabled = true;
            this.cboOriginalImage.Location = new System.Drawing.Point(274, 12);
            this.cboOriginalImage.Name = "cboOriginalImage";
            this.cboOriginalImage.Size = new System.Drawing.Size(120, 21);
            this.cboOriginalImage.TabIndex = 2;
            this.cboOriginalImage.SelectedIndexChanged += new System.EventHandler(this.cboImage_SelectedIndexChanged);
            this.cboOriginalImage.MouseEnter += new System.EventHandler(this.cboImage_MouseEnter);
            // 
            // lblNoiseImage
            // 
            this.lblNoiseImage.AutoSize = true;
            this.lblNoiseImage.Location = new System.Drawing.Point(5, 16);
            this.lblNoiseImage.Name = "lblNoiseImage";
            this.lblNoiseImage.Size = new System.Drawing.Size(68, 13);
            this.lblNoiseImage.TabIndex = 1;
            this.lblNoiseImage.Text = "Noise image:";
            // 
            // cboNoiseImage
            // 
            this.cboNoiseImage.DisplayMember = "Text";
            this.cboNoiseImage.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cboNoiseImage.DropDownWidth = 300;
            this.cboNoiseImage.FormattingEnabled = true;
            this.cboNoiseImage.Location = new System.Drawing.Point(73, 12);
            this.cboNoiseImage.Name = "cboNoiseImage";
            this.cboNoiseImage.Size = new System.Drawing.Size(120, 21);
            this.cboNoiseImage.TabIndex = 0;
            this.cboNoiseImage.SelectedIndexChanged += new System.EventHandler(this.cboImage_SelectedIndexChanged);
            this.cboNoiseImage.MouseEnter += new System.EventHandler(this.cboImage_MouseEnter);
            // 
            // lblRestorationEqu
            // 
            this.lblRestorationEqu.AutoSize = true;
            this.lblRestorationEqu.ForeColor = System.Drawing.SystemColors.HotTrack;
            this.lblRestorationEqu.Location = new System.Drawing.Point(30, 317);
            this.lblRestorationEqu.Name = "lblRestorationEqu";
            this.lblRestorationEqu.Size = new System.Drawing.Size(185, 13);
            this.lblRestorationEqu.TabIndex = 13;
            this.lblRestorationEqu.Text = "The generalized  restoration equation:";
            // 
            // picRestorationEqu
            // 
            this.picRestorationEqu.Image = ((System.Drawing.Image)(resources.GetObject("picRestorationEqu.Image")));
            this.picRestorationEqu.InitialImage = null;
            this.picRestorationEqu.Location = new System.Drawing.Point(221, 274);
            this.picRestorationEqu.Name = "picRestorationEqu";
            this.picRestorationEqu.Size = new System.Drawing.Size(322, 98);
            this.picRestorationEqu.TabIndex = 14;
            this.picRestorationEqu.TabStop = false;
            // 
            // grpNotchFilter
            // 
            this.grpNotchFilter.Controls.Add(this.pnlNotch);
            this.grpNotchFilter.Location = new System.Drawing.Point(6, 373);
            this.grpNotchFilter.Name = "grpNotchFilter";
            this.grpNotchFilter.Size = new System.Drawing.Size(588, 80);
            this.grpNotchFilter.TabIndex = 15;
            this.grpNotchFilter.TabStop = false;
            this.grpNotchFilter.Text = "Notch Filter";
            // 
            // pnlNotch
            // 
            this.pnlNotch.Controls.Add(this.btnAddNotch);
            this.pnlNotch.Controls.Add(this.btnRedoNotch);
            this.pnlNotch.Controls.Add(this.lblNotchSize);
            this.pnlNotch.Controls.Add(this.cboNotchSize);
            this.pnlNotch.Controls.Add(this.lblNotchRow);
            this.pnlNotch.Controls.Add(this.txtNotchRow);
            this.pnlNotch.Controls.Add(this.lblNotchCol);
            this.pnlNotch.Controls.Add(this.txtNotchCol);
            this.pnlNotch.Controls.Add(this.lblPoint);
            this.pnlNotch.Controls.Add(this.cboPoint);
            this.pnlNotch.Controls.Add(this.lblInfo);
            this.pnlNotch.Controls.Add(this.lblTransformType);
            this.pnlNotch.Controls.Add(this.cboTransformType);
            this.pnlNotch.Location = new System.Drawing.Point(21, 16);
            this.pnlNotch.Name = "pnlNotch";
            this.pnlNotch.Size = new System.Drawing.Size(560, 52);
            this.pnlNotch.TabIndex = 2;
            // 
            // btnAddNotch
            // 
            this.btnAddNotch.Location = new System.Drawing.Point(500, 29);
            this.btnAddNotch.Name = "btnAddNotch";
            this.btnAddNotch.Size = new System.Drawing.Size(60, 23);
            this.btnAddNotch.TabIndex = 13;
            this.btnAddNotch.Text = "Add";
            this.btnAddNotch.UseVisualStyleBackColor = true;
            this.btnAddNotch.Click += new System.EventHandler(this.btnNotchAdd_Click);
            // 
            // btnRedoNotch
            // 
            this.btnRedoNotch.Location = new System.Drawing.Point(500, 0);
            this.btnRedoNotch.Name = "btnRedoNotch";
            this.btnRedoNotch.Size = new System.Drawing.Size(60, 23);
            this.btnRedoNotch.TabIndex = 12;
            this.btnRedoNotch.Text = "Redo";
            this.btnRedoNotch.UseVisualStyleBackColor = true;
            this.btnRedoNotch.Click += new System.EventHandler(this.btnNotchRedo_Click);
            // 
            // lblNotchSize
            // 
            this.lblNotchSize.AutoSize = true;
            this.lblNotchSize.Location = new System.Drawing.Point(405, 28);
            this.lblNotchSize.Name = "lblNotchSize";
            this.lblNotchSize.Size = new System.Drawing.Size(30, 13);
            this.lblNotchSize.TabIndex = 11;
            this.lblNotchSize.Text = "Size:";
            this.lblNotchSize.TextAlign = System.Drawing.ContentAlignment.TopRight;
            // 
            // cboNotchSize
            // 
            this.cboNotchSize.FormattingEnabled = true;
            this.cboNotchSize.Items.AddRange(new object[] {
            "1",
            "2",
            "3",
            "4",
            "5",
            "10",
            "50",
            "100"});
            this.cboNotchSize.Location = new System.Drawing.Point(435, 24);
            this.cboNotchSize.Name = "cboNotchSize";
            this.cboNotchSize.Size = new System.Drawing.Size(50, 21);
            this.cboNotchSize.TabIndex = 10;
            this.cboNotchSize.Text = "10";
            this.cboNotchSize.Validating += new System.ComponentModel.CancelEventHandler(this.cboIntVal_Validating);
            this.cboNotchSize.Validated += new System.EventHandler(this.cboNotchVal_Validated);
            // 
            // lblNotchRow
            // 
            this.lblNotchRow.AutoSize = true;
            this.lblNotchRow.Location = new System.Drawing.Point(335, 28);
            this.lblNotchRow.Name = "lblNotchRow";
            this.lblNotchRow.Size = new System.Drawing.Size(32, 13);
            this.lblNotchRow.TabIndex = 9;
            this.lblNotchRow.Text = "Row:";
            this.lblNotchRow.TextAlign = System.Drawing.ContentAlignment.TopRight;
            // 
            // txtNotchRow
            // 
            this.txtNotchRow.Location = new System.Drawing.Point(367, 24);
            this.txtNotchRow.Name = "txtNotchRow";
            this.txtNotchRow.Size = new System.Drawing.Size(30, 20);
            this.txtNotchRow.TabIndex = 8;
            this.txtNotchRow.Text = "0";
            this.txtNotchRow.Validating += new System.ComponentModel.CancelEventHandler(this.txtIntVal_Validating);
            this.txtNotchRow.Validated += new System.EventHandler(this.cboNotchVal_Validated);
            // 
            // lblNotchCol
            // 
            this.lblNotchCol.AutoSize = true;
            this.lblNotchCol.Location = new System.Drawing.Point(272, 28);
            this.lblNotchCol.Name = "lblNotchCol";
            this.lblNotchCol.Size = new System.Drawing.Size(25, 13);
            this.lblNotchCol.TabIndex = 7;
            this.lblNotchCol.Text = "Col:";
            this.lblNotchCol.TextAlign = System.Drawing.ContentAlignment.TopRight;
            // 
            // txtNotchCol
            // 
            this.txtNotchCol.Location = new System.Drawing.Point(297, 24);
            this.txtNotchCol.Name = "txtNotchCol";
            this.txtNotchCol.Size = new System.Drawing.Size(30, 20);
            this.txtNotchCol.TabIndex = 6;
            this.txtNotchCol.Text = "0";
            this.txtNotchCol.Validating += new System.ComponentModel.CancelEventHandler(this.txtIntVal_Validating);
            this.txtNotchCol.Validated += new System.EventHandler(this.cboNotchVal_Validated);
            // 
            // lblPoint
            // 
            this.lblPoint.AutoSize = true;
            this.lblPoint.Location = new System.Drawing.Point(180, 28);
            this.lblPoint.Name = "lblPoint";
            this.lblPoint.Size = new System.Drawing.Size(34, 13);
            this.lblPoint.TabIndex = 5;
            this.lblPoint.Text = "Point:";
            this.lblPoint.TextAlign = System.Drawing.ContentAlignment.TopRight;
            // 
            // cboPoint
            // 
            this.cboPoint.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cboPoint.FormattingEnabled = true;
            this.cboPoint.Items.AddRange(new object[] {
            "(new)"});
            this.cboPoint.Location = new System.Drawing.Point(214, 24);
            this.cboPoint.Name = "cboPoint";
            this.cboPoint.Size = new System.Drawing.Size(50, 21);
            this.cboPoint.TabIndex = 4;
            this.cboPoint.SelectedIndexChanged += new System.EventHandler(this.cboPoint_SelectedIndexChanged);
            // 
            // lblInfo
            // 
            this.lblInfo.AutoSize = true;
            this.lblInfo.ForeColor = System.Drawing.SystemColors.HotTrack;
            this.lblInfo.Location = new System.Drawing.Point(81, 3);
            this.lblInfo.Name = "lblInfo";
            this.lblInfo.Size = new System.Drawing.Size(412, 13);
            this.lblInfo.TabIndex = 2;
            this.lblInfo.Text = "Please select a \'Transform Type\' first. Then perform Notch Filter on transformed " +
                "image.";
            // 
            // lblTransformType
            // 
            this.lblTransformType.AutoSize = true;
            this.lblTransformType.Location = new System.Drawing.Point(0, 28);
            this.lblTransformType.Name = "lblTransformType";
            this.lblTransformType.Size = new System.Drawing.Size(84, 13);
            this.lblTransformType.TabIndex = 1;
            this.lblTransformType.Text = "Transform Type:";
            // 
            // cboTransformType
            // 
            this.cboTransformType.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cboTransformType.FormattingEnabled = true;
            this.cboTransformType.Items.AddRange(new object[] {
            "FFT",
            "DCT",
            "Haar",
            "Walsh",
            "Hadamard"});
            this.cboTransformType.Location = new System.Drawing.Point(84, 24);
            this.cboTransformType.Name = "cboTransformType";
            this.cboTransformType.Size = new System.Drawing.Size(88, 21);
            this.cboTransformType.TabIndex = 0;
            this.cboTransformType.SelectedIndexChanged += new System.EventHandler(this.cboTransformType_SelectedIndexChanged);
            // 
            // btnHelp
            // 
            this.btnHelp.BackColor = System.Drawing.Color.Yellow;
            this.btnHelp.Location = new System.Drawing.Point(12, 466);
            this.btnHelp.Name = "btnHelp";
            this.btnHelp.Size = new System.Drawing.Size(60, 26);
            this.btnHelp.TabIndex = 16;
            this.btnHelp.Text = "Help";
            this.btnHelp.UseVisualStyleBackColor = false;
            this.btnHelp.Click += new System.EventHandler(this.btnHelp_Click);
            // 
            // btnCancel
            // 
            this.btnCancel.BackColor = System.Drawing.Color.OrangeRed;
            this.btnCancel.CausesValidation = false;
            this.btnCancel.Location = new System.Drawing.Point(402, 466);
            this.btnCancel.Name = "btnCancel";
            this.btnCancel.Size = new System.Drawing.Size(60, 26);
            this.btnCancel.TabIndex = 17;
            this.btnCancel.Text = "Cancel";
            this.btnCancel.UseVisualStyleBackColor = false;
            this.btnCancel.Click += new System.EventHandler(this.btnCancel_Click);
            // 
            // btnReset
            // 
            this.btnReset.BackColor = System.Drawing.Color.CornflowerBlue;
            this.btnReset.CausesValidation = false;
            this.btnReset.Location = new System.Drawing.Point(468, 466);
            this.btnReset.Name = "btnReset";
            this.btnReset.Size = new System.Drawing.Size(60, 26);
            this.btnReset.TabIndex = 18;
            this.btnReset.Text = "Reset";
            this.btnReset.UseVisualStyleBackColor = false;
            this.btnReset.Click += new System.EventHandler(this.btnReset_Click);
            // 
            // btnApply
            // 
            this.btnApply.BackColor = System.Drawing.Color.LimeGreen;
            this.btnApply.ForeColor = System.Drawing.Color.White;
            this.btnApply.Location = new System.Drawing.Point(534, 466);
            this.btnApply.Name = "btnApply";
            this.btnApply.Size = new System.Drawing.Size(60, 26);
            this.btnApply.TabIndex = 19;
            this.btnApply.Text = "Apply";
            this.btnApply.UseVisualStyleBackColor = false;
            this.btnApply.Click += new System.EventHandler(this.btnApply_Click);
            // 
            // toolTipImageCombo
            // 
            this.toolTipImageCombo.AutomaticDelay = 0;
            this.toolTipImageCombo.ShowAlways = true;
            // 
            // FrequencyFilter
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.CausesValidation = false;
            this.Controls.Add(this.rbInverse);
            this.Controls.Add(this.rbGeometricMean);
            this.Controls.Add(this.rbPowerSpectrumEQ);
            this.Controls.Add(this.rbConstrLeastSqu);
            this.Controls.Add(this.rbWiener);
            this.Controls.Add(this.rbPractWiener);
            this.Controls.Add(this.rbParaWiener);
            this.Controls.Add(this.rbNotch);
            this.Controls.Add(this.grpFilters);
            this.Controls.Add(this.lblDegradedImage);
            this.Controls.Add(this.txtDegradedImage);
            this.Controls.Add(this.grpDegradationFunction);
            this.Controls.Add(this.pnlParameters);
            this.Controls.Add(this.lblRestorationEqu);
            this.Controls.Add(this.picRestorationEqu);
            this.Controls.Add(this.grpNotchFilter);
            this.Controls.Add(this.btnHelp);
            this.Controls.Add(this.btnCancel);
            this.Controls.Add(this.btnReset);
            this.Controls.Add(this.btnApply);
            this.Name = "FrequencyFilter";
            this.Size = new System.Drawing.Size(600, 495);
            this.grpFilters.ResumeLayout(false);
            this.grpFilters.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.picWienerCoefficient)).EndInit();
            this.grpDegradationFunction.ResumeLayout(false);
            this.pnlDegradationFunction.ResumeLayout(false);
            this.pnlDegradationFunction.PerformLayout();
            this.grpBlurMask.ResumeLayout(false);
            this.grpBlurMask.PerformLayout();
            this.pnlParameters.ResumeLayout(false);
            this.pnlParameters.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.picRestorationEqu)).EndInit();
            this.grpNotchFilter.ResumeLayout(false);
            this.pnlNotch.ResumeLayout(false);
            this.pnlNotch.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.RadioButton rbInverse;
        private System.Windows.Forms.RadioButton rbGeometricMean;
        private System.Windows.Forms.RadioButton rbPowerSpectrumEQ;
        private System.Windows.Forms.RadioButton rbConstrLeastSqu;
        private System.Windows.Forms.RadioButton rbWiener;
        private System.Windows.Forms.RadioButton rbPractWiener;
        private System.Windows.Forms.RadioButton rbParaWiener;
        private System.Windows.Forms.RadioButton rbNotch;
        private System.Windows.Forms.GroupBox grpFilters;
        private System.Windows.Forms.Label lblWienerCoefficient;
        private System.Windows.Forms.PictureBox picWienerCoefficient;
        private System.Windows.Forms.Label lblDegradedImage;
        private System.Windows.Forms.TextBox txtDegradedImage;
        private System.Windows.Forms.GroupBox grpDegradationFunction;
        private System.Windows.Forms.Panel pnlDegradationFunction;
        private System.Windows.Forms.Label lblLimitGain2;
        private System.Windows.Forms.Label lblLimitGain1;
        private System.Windows.Forms.ComboBox cboLimitGain;
        private System.Windows.Forms.Label lblCutoffFreq;
        private System.Windows.Forms.ComboBox cboCutoffFreq;
        private System.Windows.Forms.GroupBox grpBlurMask;
        private System.Windows.Forms.Label lblBlurWeight;
        private System.Windows.Forms.ComboBox cboBlurWeight;
        private System.Windows.Forms.Label lblBlurMethod;
        private System.Windows.Forms.ComboBox cboBlurMethod;
        private System.Windows.Forms.Label lblBlurShape;
        private System.Windows.Forms.ComboBox cboBlurShape;
        private System.Windows.Forms.Button btnEditMask;
        private System.Windows.Forms.Label lblMaskHeight;
        private System.Windows.Forms.ComboBox cboMaskHeight;
        private System.Windows.Forms.Label lblMaskWidth;
        private System.Windows.Forms.ComboBox cboMaskWidth;
        private System.Windows.Forms.ComboBox cboDegradationImage;
        private System.Windows.Forms.RadioButton rbUseImage;
        private System.Windows.Forms.RadioButton rbSpecifyFunc;
        private System.Windows.Forms.Panel pnlParameters;
        private System.Windows.Forms.Label lblK;
        private System.Windows.Forms.ComboBox cboK;
        private System.Windows.Forms.Label lblAlpha;
        private System.Windows.Forms.ComboBox cboAlpha;
        private System.Windows.Forms.Label lblSmoothFunc;
        private System.Windows.Forms.ComboBox cboSmoothFunc;
        private System.Windows.Forms.Label lblGamma;
        private System.Windows.Forms.ComboBox cboGamma;
        private System.Windows.Forms.Label lblOriginalImage;
        private System.Windows.Forms.ComboBox cboOriginalImage;
        private System.Windows.Forms.Label lblNoiseImage;
        private System.Windows.Forms.ComboBox cboNoiseImage;
        private System.Windows.Forms.Label lblRestorationEqu;
        private System.Windows.Forms.PictureBox picRestorationEqu;
        private System.Windows.Forms.GroupBox grpNotchFilter;
        private System.Windows.Forms.Panel pnlNotch;
        private System.Windows.Forms.Button btnAddNotch;
        private System.Windows.Forms.Button btnRedoNotch;
        private System.Windows.Forms.Label lblNotchSize;
        private System.Windows.Forms.ComboBox cboNotchSize;
        private System.Windows.Forms.Label lblNotchRow;
        private System.Windows.Forms.TextBox txtNotchRow;
        private System.Windows.Forms.Label lblNotchCol;
        private System.Windows.Forms.TextBox txtNotchCol;
        private System.Windows.Forms.Label lblPoint;
        private System.Windows.Forms.ComboBox cboPoint;
        private System.Windows.Forms.Label lblInfo;
        private System.Windows.Forms.Label lblTransformType;
        private System.Windows.Forms.ComboBox cboTransformType;
        private System.Windows.Forms.Button btnHelp;
        private System.Windows.Forms.Button btnCancel;
        private System.Windows.Forms.Button btnReset;
        private System.Windows.Forms.Button btnApply;
        private System.Windows.Forms.ToolTip toolTipImageCombo;
    }
}
