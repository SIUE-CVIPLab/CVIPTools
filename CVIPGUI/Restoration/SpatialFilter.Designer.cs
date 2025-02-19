namespace CVIPGUI.Restoration
{
    partial class SpatialFilter
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
            this.rbMedian = new System.Windows.Forms.RadioButton();
            this.rbMinimum = new System.Windows.Forms.RadioButton();
            this.rbMidpoint = new System.Windows.Forms.RadioButton();
            this.rbMaximum = new System.Windows.Forms.RadioButton();
            this.rbAlphaTrim = new System.Windows.Forms.RadioButton();
            this.rbArithmetic = new System.Windows.Forms.RadioButton();
            this.rbGeometric = new System.Windows.Forms.RadioButton();
            this.rbHarmonic = new System.Windows.Forms.RadioButton();
            this.rbContraHarmonic = new System.Windows.Forms.RadioButton();
            this.rbYpMean = new System.Windows.Forms.RadioButton();
            this.rbMMSE = new System.Windows.Forms.RadioButton();
            this.rbAdaptiveMedian = new System.Windows.Forms.RadioButton();
            this.rbKuwahara = new System.Windows.Forms.RadioButton();
            this.rbAdaptiveContrast = new System.Windows.Forms.RadioButton();
            this.rbAnisotropic = new System.Windows.Forms.RadioButton();
            this.grpOrderFilters = new System.Windows.Forms.GroupBox();
            this.pnlOrderFilters = new System.Windows.Forms.Panel();
            this.lblTrimSize = new System.Windows.Forms.Label();
            this.txtTrimSize = new System.Windows.Forms.TextBox();
            this.lblMaskSizeOrder = new System.Windows.Forms.Label();
            this.cboMaskSizeOrder = new System.Windows.Forms.ComboBox();
            this.grpMeanFilters = new System.Windows.Forms.GroupBox();
            this.pnlMeanFilters = new System.Windows.Forms.Panel();
            this.lblFilterOrder = new System.Windows.Forms.Label();
            this.cboFilterOrder = new System.Windows.Forms.ComboBox();
            this.lblMaskSizeMean = new System.Windows.Forms.Label();
            this.cboMaskSizeMean = new System.Windows.Forms.ComboBox();
            this.grpAdaptiveFilters = new System.Windows.Forms.GroupBox();
            this.pnlAdaptiveFilters = new System.Windows.Forms.Panel();
            this.lblMaskSizeAdaptive = new System.Windows.Forms.Label();
            this.cboMaskSizeAdaptive = new System.Windows.Forms.ComboBox();
            this.pnlMMSE = new System.Windows.Forms.Panel();
            this.lblThreshold = new System.Windows.Forms.Label();
            this.cboThreshold = new System.Windows.Forms.ComboBox();
            this.lblKernelSizeMMSE = new System.Windows.Forms.Label();
            this.cboKernelSizeMMSE = new System.Windows.Forms.ComboBox();
            this.lblNoiseVar = new System.Windows.Forms.Label();
            this.cboNoiseVar = new System.Windows.Forms.ComboBox();
            this.pnlAdaptiveContrast = new System.Windows.Forms.Panel();
            this.lblKernelSizeAC = new System.Windows.Forms.Label();
            this.cboKernelSizeAC = new System.Windows.Forms.ComboBox();
            this.lblLocalGainMax = new System.Windows.Forms.Label();
            this.cboLocalGainMax = new System.Windows.Forms.ComboBox();
            this.lblLocalMean = new System.Windows.Forms.Label();
            this.cboLocalMean = new System.Windows.Forms.ComboBox();
            this.lblLocalGainMin = new System.Windows.Forms.Label();
            this.cboLocalGainMin = new System.Windows.Forms.ComboBox();
            this.lblLocalGain = new System.Windows.Forms.Label();
            this.cboLocalGain = new System.Windows.Forms.ComboBox();
            this.pnlAnisotropic = new System.Windows.Forms.Panel();
            this.lblBlockSize = new System.Windows.Forms.Label();
            this.cboBlockSize = new System.Windows.Forms.ComboBox();
            this.lblSmoothing = new System.Windows.Forms.Label();
            this.cboSmoothing = new System.Windows.Forms.ComboBox();
            this.lblEdgeThreshold = new System.Windows.Forms.Label();
            this.cboEdgeThreshold = new System.Windows.Forms.ComboBox();
            this.lblIterations = new System.Windows.Forms.Label();
            this.cboIterations = new System.Windows.Forms.ComboBox();
            this.rbImproved = new System.Windows.Forms.RadioButton();
            this.rbStandard = new System.Windows.Forms.RadioButton();
            this.btnHelp = new System.Windows.Forms.Button();
            this.btnCancel = new System.Windows.Forms.Button();
            this.btnReset = new System.Windows.Forms.Button();
            this.btnApply = new System.Windows.Forms.Button();
            this.grpOrderFilters.SuspendLayout();
            this.pnlOrderFilters.SuspendLayout();
            this.grpMeanFilters.SuspendLayout();
            this.pnlMeanFilters.SuspendLayout();
            this.grpAdaptiveFilters.SuspendLayout();
            this.pnlAdaptiveFilters.SuspendLayout();
            this.pnlMMSE.SuspendLayout();
            this.pnlAdaptiveContrast.SuspendLayout();
            this.pnlAnisotropic.SuspendLayout();
            this.SuspendLayout();
            // 
            // rbMedian
            // 
            this.rbMedian.AutoSize = true;
            this.rbMedian.Checked = true;
            this.rbMedian.Location = new System.Drawing.Point(15, 22);
            this.rbMedian.Name = "rbMedian";
            this.rbMedian.Size = new System.Drawing.Size(60, 17);
            this.rbMedian.TabIndex = 0;
            this.rbMedian.TabStop = true;
            this.rbMedian.Text = "Median";
            this.rbMedian.UseVisualStyleBackColor = true;
            this.rbMedian.Click += new System.EventHandler(this.rbSpatial_Click);
            // 
            // rbMinimum
            // 
            this.rbMinimum.AutoSize = true;
            this.rbMinimum.Location = new System.Drawing.Point(15, 46);
            this.rbMinimum.Name = "rbMinimum";
            this.rbMinimum.Size = new System.Drawing.Size(66, 17);
            this.rbMinimum.TabIndex = 1;
            this.rbMinimum.Text = "Minimum";
            this.rbMinimum.UseVisualStyleBackColor = true;
            this.rbMinimum.Click += new System.EventHandler(this.rbSpatial_Click);
            // 
            // rbMidpoint
            // 
            this.rbMidpoint.AutoSize = true;
            this.rbMidpoint.Location = new System.Drawing.Point(15, 70);
            this.rbMidpoint.Name = "rbMidpoint";
            this.rbMidpoint.Size = new System.Drawing.Size(65, 17);
            this.rbMidpoint.TabIndex = 2;
            this.rbMidpoint.Text = "Midpoint";
            this.rbMidpoint.UseVisualStyleBackColor = true;
            this.rbMidpoint.Click += new System.EventHandler(this.rbSpatial_Click);
            // 
            // rbMaximum
            // 
            this.rbMaximum.AutoSize = true;
            this.rbMaximum.Location = new System.Drawing.Point(15, 94);
            this.rbMaximum.Name = "rbMaximum";
            this.rbMaximum.Size = new System.Drawing.Size(69, 17);
            this.rbMaximum.TabIndex = 3;
            this.rbMaximum.Text = "Maximum";
            this.rbMaximum.UseVisualStyleBackColor = true;
            this.rbMaximum.Click += new System.EventHandler(this.rbSpatial_Click);
            // 
            // rbAlphaTrim
            // 
            this.rbAlphaTrim.AutoSize = true;
            this.rbAlphaTrim.Location = new System.Drawing.Point(15, 118);
            this.rbAlphaTrim.Name = "rbAlphaTrim";
            this.rbAlphaTrim.Size = new System.Drawing.Size(125, 17);
            this.rbAlphaTrim.TabIndex = 4;
            this.rbAlphaTrim.Text = "Alpha Trimmed Mean";
            this.rbAlphaTrim.UseVisualStyleBackColor = true;
            this.rbAlphaTrim.Click += new System.EventHandler(this.rbSpatial_Click);
            // 
            // rbArithmetic
            // 
            this.rbArithmetic.AutoSize = true;
            this.rbArithmetic.Location = new System.Drawing.Point(15, 173);
            this.rbArithmetic.Name = "rbArithmetic";
            this.rbArithmetic.Size = new System.Drawing.Size(71, 17);
            this.rbArithmetic.TabIndex = 5;
            this.rbArithmetic.Text = "Arithmetic";
            this.rbArithmetic.UseVisualStyleBackColor = true;
            this.rbArithmetic.Click += new System.EventHandler(this.rbSpatial_Click);
            // 
            // rbGeometric
            // 
            this.rbGeometric.AutoSize = true;
            this.rbGeometric.Location = new System.Drawing.Point(15, 197);
            this.rbGeometric.Name = "rbGeometric";
            this.rbGeometric.Size = new System.Drawing.Size(73, 17);
            this.rbGeometric.TabIndex = 6;
            this.rbGeometric.Text = "Geometric";
            this.rbGeometric.UseVisualStyleBackColor = true;
            this.rbGeometric.Click += new System.EventHandler(this.rbSpatial_Click);
            // 
            // rbHarmonic
            // 
            this.rbHarmonic.AutoSize = true;
            this.rbHarmonic.Location = new System.Drawing.Point(15, 221);
            this.rbHarmonic.Name = "rbHarmonic";
            this.rbHarmonic.Size = new System.Drawing.Size(70, 17);
            this.rbHarmonic.TabIndex = 7;
            this.rbHarmonic.Text = "Harmonic";
            this.rbHarmonic.UseVisualStyleBackColor = true;
            this.rbHarmonic.Click += new System.EventHandler(this.rbSpatial_Click);
            // 
            // rbContraHarmonic
            // 
            this.rbContraHarmonic.AutoSize = true;
            this.rbContraHarmonic.Location = new System.Drawing.Point(15, 245);
            this.rbContraHarmonic.Name = "rbContraHarmonic";
            this.rbContraHarmonic.Size = new System.Drawing.Size(104, 17);
            this.rbContraHarmonic.TabIndex = 8;
            this.rbContraHarmonic.Text = "Contra-Harmonic";
            this.rbContraHarmonic.UseVisualStyleBackColor = true;
            this.rbContraHarmonic.Click += new System.EventHandler(this.rbSpatial_Click);
            // 
            // rbYpMean
            // 
            this.rbYpMean.AutoSize = true;
            this.rbYpMean.Location = new System.Drawing.Point(15, 269);
            this.rbYpMean.Name = "rbYpMean";
            this.rbYpMean.Size = new System.Drawing.Size(38, 17);
            this.rbYpMean.TabIndex = 9;
            this.rbYpMean.Text = "Yp";
            this.rbYpMean.UseVisualStyleBackColor = true;
            this.rbYpMean.Click += new System.EventHandler(this.rbSpatial_Click);
            // 
            // rbMMSE
            // 
            this.rbMMSE.AutoSize = true;
            this.rbMMSE.Location = new System.Drawing.Point(15, 324);
            this.rbMMSE.Name = "rbMMSE";
            this.rbMMSE.Size = new System.Drawing.Size(57, 17);
            this.rbMMSE.TabIndex = 10;
            this.rbMMSE.Text = "MMSE";
            this.rbMMSE.UseVisualStyleBackColor = true;
            this.rbMMSE.Click += new System.EventHandler(this.rbSpatial_Click);
            // 
            // rbAdaptiveMedian
            // 
            this.rbAdaptiveMedian.AutoSize = true;
            this.rbAdaptiveMedian.Location = new System.Drawing.Point(15, 348);
            this.rbAdaptiveMedian.Name = "rbAdaptiveMedian";
            this.rbAdaptiveMedian.Size = new System.Drawing.Size(105, 17);
            this.rbAdaptiveMedian.TabIndex = 11;
            this.rbAdaptiveMedian.Text = "Adaptive Median";
            this.rbAdaptiveMedian.UseVisualStyleBackColor = true;
            this.rbAdaptiveMedian.Click += new System.EventHandler(this.rbSpatial_Click);
            // 
            // rbKuwahara
            // 
            this.rbKuwahara.AutoSize = true;
            this.rbKuwahara.Location = new System.Drawing.Point(15, 372);
            this.rbKuwahara.Name = "rbKuwahara";
            this.rbKuwahara.Size = new System.Drawing.Size(98, 17);
            this.rbKuwahara.TabIndex = 12;
            this.rbKuwahara.Text = "Kuwahara Filter";
            this.rbKuwahara.UseVisualStyleBackColor = true;
            this.rbKuwahara.Click += new System.EventHandler(this.rbSpatial_Click);
            // 
            // rbAdaptiveContrast
            // 
            this.rbAdaptiveContrast.AutoSize = true;
            this.rbAdaptiveContrast.Location = new System.Drawing.Point(15, 396);
            this.rbAdaptiveContrast.Name = "rbAdaptiveContrast";
            this.rbAdaptiveContrast.Size = new System.Drawing.Size(109, 17);
            this.rbAdaptiveContrast.TabIndex = 13;
            this.rbAdaptiveContrast.Text = "Adaptive Contrast";
            this.rbAdaptiveContrast.UseVisualStyleBackColor = true;
            this.rbAdaptiveContrast.Click += new System.EventHandler(this.rbSpatial_Click);
            // 
            // rbAnisotropic
            // 
            this.rbAnisotropic.AutoSize = true;
            this.rbAnisotropic.Location = new System.Drawing.Point(15, 420);
            this.rbAnisotropic.Name = "rbAnisotropic";
            this.rbAnisotropic.Size = new System.Drawing.Size(121, 17);
            this.rbAnisotropic.TabIndex = 14;
            this.rbAnisotropic.Text = "Anisotropic Diffusion";
            this.rbAnisotropic.UseVisualStyleBackColor = true;
            this.rbAnisotropic.Click += new System.EventHandler(this.rbSpatial_Click);
            // 
            // grpOrderFilters
            // 
            this.grpOrderFilters.Controls.Add(this.pnlOrderFilters);
            this.grpOrderFilters.Location = new System.Drawing.Point(3, 3);
            this.grpOrderFilters.Name = "grpOrderFilters";
            this.grpOrderFilters.Size = new System.Drawing.Size(590, 141);
            this.grpOrderFilters.TabIndex = 15;
            this.grpOrderFilters.TabStop = false;
            this.grpOrderFilters.Text = "Order Filters";
            // 
            // pnlOrderFilters
            // 
            this.pnlOrderFilters.Controls.Add(this.lblTrimSize);
            this.pnlOrderFilters.Controls.Add(this.txtTrimSize);
            this.pnlOrderFilters.Controls.Add(this.lblMaskSizeOrder);
            this.pnlOrderFilters.Controls.Add(this.cboMaskSizeOrder);
            this.pnlOrderFilters.Location = new System.Drawing.Point(136, 22);
            this.pnlOrderFilters.Name = "pnlOrderFilters";
            this.pnlOrderFilters.Size = new System.Drawing.Size(221, 48);
            this.pnlOrderFilters.TabIndex = 0;
            // 
            // lblTrimSize
            // 
            this.lblTrimSize.AutoSize = true;
            this.lblTrimSize.Location = new System.Drawing.Point(0, 32);
            this.lblTrimSize.Name = "lblTrimSize";
            this.lblTrimSize.Size = new System.Drawing.Size(119, 13);
            this.lblTrimSize.TabIndex = 3;
            this.lblTrimSize.Text = "Trim size [0~(N*N-1)/2]:";
            // 
            // txtTrimSize
            // 
            this.txtTrimSize.Location = new System.Drawing.Point(121, 28);
            this.txtTrimSize.Name = "txtTrimSize";
            this.txtTrimSize.Size = new System.Drawing.Size(100, 20);
            this.txtTrimSize.TabIndex = 2;
            this.txtTrimSize.Text = "0";
            this.txtTrimSize.Validating += new System.ComponentModel.CancelEventHandler(this.txtIntVal_Validating);
            // 
            // lblMaskSizeOrder
            // 
            this.lblMaskSizeOrder.AutoSize = true;
            this.lblMaskSizeOrder.Location = new System.Drawing.Point(60, 4);
            this.lblMaskSizeOrder.Name = "lblMaskSizeOrder";
            this.lblMaskSizeOrder.Size = new System.Drawing.Size(59, 13);
            this.lblMaskSizeOrder.TabIndex = 1;
            this.lblMaskSizeOrder.Text = "Mask Size:";
            // 
            // cboMaskSizeOrder
            // 
            this.cboMaskSizeOrder.FormattingEnabled = true;
            this.cboMaskSizeOrder.Items.AddRange(new object[] {
            "3",
            "5",
            "7",
            "9",
            "11"});
            this.cboMaskSizeOrder.Location = new System.Drawing.Point(121, 0);
            this.cboMaskSizeOrder.Name = "cboMaskSizeOrder";
            this.cboMaskSizeOrder.Size = new System.Drawing.Size(100, 21);
            this.cboMaskSizeOrder.TabIndex = 0;
            this.cboMaskSizeOrder.Text = "3";
            this.cboMaskSizeOrder.Validating += new System.ComponentModel.CancelEventHandler(this.cboMaskSize_Validating);
            // 
            // grpMeanFilters
            // 
            this.grpMeanFilters.Controls.Add(this.pnlMeanFilters);
            this.grpMeanFilters.Location = new System.Drawing.Point(3, 154);
            this.grpMeanFilters.Name = "grpMeanFilters";
            this.grpMeanFilters.Size = new System.Drawing.Size(590, 141);
            this.grpMeanFilters.TabIndex = 16;
            this.grpMeanFilters.TabStop = false;
            this.grpMeanFilters.Text = "Mean Filters";
            // 
            // pnlMeanFilters
            // 
            this.pnlMeanFilters.Controls.Add(this.lblFilterOrder);
            this.pnlMeanFilters.Controls.Add(this.cboFilterOrder);
            this.pnlMeanFilters.Controls.Add(this.lblMaskSizeMean);
            this.pnlMeanFilters.Controls.Add(this.cboMaskSizeMean);
            this.pnlMeanFilters.Location = new System.Drawing.Point(194, 22);
            this.pnlMeanFilters.Name = "pnlMeanFilters";
            this.pnlMeanFilters.Size = new System.Drawing.Size(163, 49);
            this.pnlMeanFilters.TabIndex = 0;
            // 
            // lblFilterOrder
            // 
            this.lblFilterOrder.AutoSize = true;
            this.lblFilterOrder.Location = new System.Drawing.Point(0, 32);
            this.lblFilterOrder.Name = "lblFilterOrder";
            this.lblFilterOrder.Size = new System.Drawing.Size(61, 13);
            this.lblFilterOrder.TabIndex = 3;
            this.lblFilterOrder.Text = "Filter Order:";
            // 
            // cboFilterOrder
            // 
            this.cboFilterOrder.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cboFilterOrder.FormattingEnabled = true;
            this.cboFilterOrder.Items.AddRange(new object[] {
            "-5",
            "-4",
            "-3",
            "-2",
            "-1",
            "0",
            "1",
            "2",
            "3",
            "4",
            "5"});
            this.cboFilterOrder.Location = new System.Drawing.Point(63, 28);
            this.cboFilterOrder.Name = "cboFilterOrder";
            this.cboFilterOrder.Size = new System.Drawing.Size(100, 21);
            this.cboFilterOrder.TabIndex = 2;
            // 
            // lblMaskSizeMean
            // 
            this.lblMaskSizeMean.AutoSize = true;
            this.lblMaskSizeMean.Location = new System.Drawing.Point(2, 4);
            this.lblMaskSizeMean.Name = "lblMaskSizeMean";
            this.lblMaskSizeMean.Size = new System.Drawing.Size(59, 13);
            this.lblMaskSizeMean.TabIndex = 1;
            this.lblMaskSizeMean.Text = "Mask Size:";
            // 
            // cboMaskSizeMean
            // 
            this.cboMaskSizeMean.FormattingEnabled = true;
            this.cboMaskSizeMean.Items.AddRange(new object[] {
            "3",
            "5",
            "7",
            "9",
            "11"});
            this.cboMaskSizeMean.Location = new System.Drawing.Point(63, 0);
            this.cboMaskSizeMean.Name = "cboMaskSizeMean";
            this.cboMaskSizeMean.Size = new System.Drawing.Size(100, 21);
            this.cboMaskSizeMean.TabIndex = 0;
            this.cboMaskSizeMean.Text = "3";
            this.cboMaskSizeMean.Validating += new System.ComponentModel.CancelEventHandler(this.cboMaskSize_Validating);
            // 
            // grpAdaptiveFilters
            // 
            this.grpAdaptiveFilters.Controls.Add(this.pnlAdaptiveFilters);
            this.grpAdaptiveFilters.Location = new System.Drawing.Point(3, 305);
            this.grpAdaptiveFilters.Name = "grpAdaptiveFilters";
            this.grpAdaptiveFilters.Size = new System.Drawing.Size(590, 141);
            this.grpAdaptiveFilters.TabIndex = 17;
            this.grpAdaptiveFilters.TabStop = false;
            this.grpAdaptiveFilters.Text = "Adaptive Filters";
            // 
            // pnlAdaptiveFilters
            // 
            this.pnlAdaptiveFilters.Controls.Add(this.lblMaskSizeAdaptive);
            this.pnlAdaptiveFilters.Controls.Add(this.cboMaskSizeAdaptive);
            this.pnlAdaptiveFilters.Controls.Add(this.pnlMMSE);
            this.pnlAdaptiveFilters.Controls.Add(this.pnlAdaptiveContrast);
            this.pnlAdaptiveFilters.Controls.Add(this.pnlAnisotropic);
            this.pnlAdaptiveFilters.Controls.Add(this.rbImproved);
            this.pnlAdaptiveFilters.Controls.Add(this.rbStandard);
            this.pnlAdaptiveFilters.Location = new System.Drawing.Point(152, 22);
            this.pnlAdaptiveFilters.Name = "pnlAdaptiveFilters";
            this.pnlAdaptiveFilters.Size = new System.Drawing.Size(404, 106);
            this.pnlAdaptiveFilters.TabIndex = 0;
            // 
            // lblMaskSizeAdaptive
            // 
            this.lblMaskSizeAdaptive.AutoSize = true;
            this.lblMaskSizeAdaptive.Location = new System.Drawing.Point(44, 33);
            this.lblMaskSizeAdaptive.Name = "lblMaskSizeAdaptive";
            this.lblMaskSizeAdaptive.Size = new System.Drawing.Size(59, 13);
            this.lblMaskSizeAdaptive.TabIndex = 0;
            this.lblMaskSizeAdaptive.Text = "Mask Size:";
            // 
            // cboMaskSizeAdaptive
            // 
            this.cboMaskSizeAdaptive.FormattingEnabled = true;
            this.cboMaskSizeAdaptive.Items.AddRange(new object[] {
            "3",
            "5",
            "7",
            "9",
            "11"});
            this.cboMaskSizeAdaptive.Location = new System.Drawing.Point(105, 29);
            this.cboMaskSizeAdaptive.Name = "cboMaskSizeAdaptive";
            this.cboMaskSizeAdaptive.Size = new System.Drawing.Size(100, 21);
            this.cboMaskSizeAdaptive.TabIndex = 1;
            this.cboMaskSizeAdaptive.Text = "3";
            this.cboMaskSizeAdaptive.Validating += new System.ComponentModel.CancelEventHandler(this.cboMaskSize_Validating);
            // 
            // pnlMMSE
            // 
            this.pnlMMSE.Controls.Add(this.lblThreshold);
            this.pnlMMSE.Controls.Add(this.cboThreshold);
            this.pnlMMSE.Controls.Add(this.lblKernelSizeMMSE);
            this.pnlMMSE.Controls.Add(this.cboKernelSizeMMSE);
            this.pnlMMSE.Controls.Add(this.lblNoiseVar);
            this.pnlMMSE.Controls.Add(this.cboNoiseVar);
            this.pnlMMSE.Location = new System.Drawing.Point(21, 29);
            this.pnlMMSE.Name = "pnlMMSE";
            this.pnlMMSE.Size = new System.Drawing.Size(184, 77);
            this.pnlMMSE.TabIndex = 43;
            // 
            // lblThreshold
            // 
            this.lblThreshold.AutoSize = true;
            this.lblThreshold.Location = new System.Drawing.Point(25, 60);
            this.lblThreshold.Name = "lblThreshold";
            this.lblThreshold.Size = new System.Drawing.Size(57, 13);
            this.lblThreshold.TabIndex = 5;
            this.lblThreshold.Text = "Threshold:";
            // 
            // cboThreshold
            // 
            this.cboThreshold.FormattingEnabled = true;
            this.cboThreshold.Items.AddRange(new object[] {
            "0.2",
            "0.3",
            "0.4",
            "0.5",
            "0.6",
            "0.7",
            "0.8",
            "0.9",
            "1.0"});
            this.cboThreshold.Location = new System.Drawing.Point(84, 56);
            this.cboThreshold.Name = "cboThreshold";
            this.cboThreshold.Size = new System.Drawing.Size(100, 21);
            this.cboThreshold.TabIndex = 4;
            this.cboThreshold.Text = "0.6";
            this.cboThreshold.Validating += new System.ComponentModel.CancelEventHandler(this.cboFloatVal_Validating);
            // 
            // lblKernelSizeMMSE
            // 
            this.lblKernelSizeMMSE.AutoSize = true;
            this.lblKernelSizeMMSE.Location = new System.Drawing.Point(19, 32);
            this.lblKernelSizeMMSE.Name = "lblKernelSizeMMSE";
            this.lblKernelSizeMMSE.Size = new System.Drawing.Size(63, 13);
            this.lblKernelSizeMMSE.TabIndex = 3;
            this.lblKernelSizeMMSE.Text = "Kernel Size:";
            // 
            // cboKernelSizeMMSE
            // 
            this.cboKernelSizeMMSE.FormattingEnabled = true;
            this.cboKernelSizeMMSE.Items.AddRange(new object[] {
            "3",
            "5",
            "7",
            "9",
            "11",
            "13",
            "15"});
            this.cboKernelSizeMMSE.Location = new System.Drawing.Point(84, 28);
            this.cboKernelSizeMMSE.Name = "cboKernelSizeMMSE";
            this.cboKernelSizeMMSE.Size = new System.Drawing.Size(100, 21);
            this.cboKernelSizeMMSE.TabIndex = 2;
            this.cboKernelSizeMMSE.Text = "9";
            this.cboKernelSizeMMSE.Validating += new System.ComponentModel.CancelEventHandler(this.cboUIntVal_Validating);
            // 
            // lblNoiseVar
            // 
            this.lblNoiseVar.AutoSize = true;
            this.lblNoiseVar.Location = new System.Drawing.Point(0, 4);
            this.lblNoiseVar.Name = "lblNoiseVar";
            this.lblNoiseVar.Size = new System.Drawing.Size(82, 13);
            this.lblNoiseVar.TabIndex = 1;
            this.lblNoiseVar.Text = "Noise Variance:";
            // 
            // cboNoiseVar
            // 
            this.cboNoiseVar.FormattingEnabled = true;
            this.cboNoiseVar.Items.AddRange(new object[] {
            "100.0",
            "200.0",
            "300.0",
            "400.0",
            "500.0",
            "600.0",
            "700.0",
            "800.0"});
            this.cboNoiseVar.Location = new System.Drawing.Point(84, 0);
            this.cboNoiseVar.Name = "cboNoiseVar";
            this.cboNoiseVar.Size = new System.Drawing.Size(100, 21);
            this.cboNoiseVar.TabIndex = 0;
            this.cboNoiseVar.Text = "100.0";
            this.cboNoiseVar.Validating += new System.ComponentModel.CancelEventHandler(this.cboDoubleVal_Validating);
            // 
            // pnlAdaptiveContrast
            // 
            this.pnlAdaptiveContrast.Controls.Add(this.lblKernelSizeAC);
            this.pnlAdaptiveContrast.Controls.Add(this.cboKernelSizeAC);
            this.pnlAdaptiveContrast.Controls.Add(this.lblLocalGainMax);
            this.pnlAdaptiveContrast.Controls.Add(this.cboLocalGainMax);
            this.pnlAdaptiveContrast.Controls.Add(this.lblLocalMean);
            this.pnlAdaptiveContrast.Controls.Add(this.cboLocalMean);
            this.pnlAdaptiveContrast.Controls.Add(this.lblLocalGainMin);
            this.pnlAdaptiveContrast.Controls.Add(this.cboLocalGainMin);
            this.pnlAdaptiveContrast.Controls.Add(this.lblLocalGain);
            this.pnlAdaptiveContrast.Controls.Add(this.cboLocalGain);
            this.pnlAdaptiveContrast.Location = new System.Drawing.Point(4, 29);
            this.pnlAdaptiveContrast.Name = "pnlAdaptiveContrast";
            this.pnlAdaptiveContrast.Size = new System.Drawing.Size(400, 77);
            this.pnlAdaptiveContrast.TabIndex = 44;
            // 
            // lblKernelSizeAC
            // 
            this.lblKernelSizeAC.AutoSize = true;
            this.lblKernelSizeAC.Location = new System.Drawing.Point(36, 60);
            this.lblKernelSizeAC.Name = "lblKernelSizeAC";
            this.lblKernelSizeAC.Size = new System.Drawing.Size(63, 13);
            this.lblKernelSizeAC.TabIndex = 9;
            this.lblKernelSizeAC.Text = "Kernel Size:";
            // 
            // cboKernelSizeAC
            // 
            this.cboKernelSizeAC.FormattingEnabled = true;
            this.cboKernelSizeAC.Items.AddRange(new object[] {
            "7",
            "9",
            "11",
            "13",
            "15",
            "21"});
            this.cboKernelSizeAC.Location = new System.Drawing.Point(101, 56);
            this.cboKernelSizeAC.Name = "cboKernelSizeAC";
            this.cboKernelSizeAC.Size = new System.Drawing.Size(100, 21);
            this.cboKernelSizeAC.TabIndex = 8;
            this.cboKernelSizeAC.Text = "11";
            this.cboKernelSizeAC.Validating += new System.ComponentModel.CancelEventHandler(this.cboUIntVal_Validating);
            // 
            // lblLocalGainMax
            // 
            this.lblLocalGainMax.AutoSize = true;
            this.lblLocalGainMax.Location = new System.Drawing.Point(214, 32);
            this.lblLocalGainMax.Name = "lblLocalGainMax";
            this.lblLocalGainMax.Size = new System.Drawing.Size(84, 13);
            this.lblLocalGainMax.TabIndex = 7;
            this.lblLocalGainMax.Text = "Local Gain Max:";
            // 
            // cboLocalGainMax
            // 
            this.cboLocalGainMax.FormattingEnabled = true;
            this.cboLocalGainMax.Items.AddRange(new object[] {
            "5.0",
            "10.0",
            "15.0",
            "20.0",
            "25.0",
            "30.0",
            "100.0"});
            this.cboLocalGainMax.Location = new System.Drawing.Point(300, 28);
            this.cboLocalGainMax.Name = "cboLocalGainMax";
            this.cboLocalGainMax.Size = new System.Drawing.Size(100, 21);
            this.cboLocalGainMax.TabIndex = 6;
            this.cboLocalGainMax.Text = "10.0";
            this.cboLocalGainMax.Validating += new System.ComponentModel.CancelEventHandler(this.cboDoubleVal_Validating);
            // 
            // lblLocalMean
            // 
            this.lblLocalMean.AutoSize = true;
            this.lblLocalMean.Location = new System.Drawing.Point(0, 32);
            this.lblLocalMean.Name = "lblLocalMean";
            this.lblLocalMean.Size = new System.Drawing.Size(99, 13);
            this.lblLocalMean.TabIndex = 5;
            this.lblLocalMean.Text = "Local Mean Factor:";
            // 
            // cboLocalMean
            // 
            this.cboLocalMean.FormattingEnabled = true;
            this.cboLocalMean.Items.AddRange(new object[] {
            "0.5",
            "0.6",
            "0.7",
            "0.8",
            "0.9",
            "1.0"});
            this.cboLocalMean.Location = new System.Drawing.Point(101, 28);
            this.cboLocalMean.Name = "cboLocalMean";
            this.cboLocalMean.Size = new System.Drawing.Size(100, 21);
            this.cboLocalMean.TabIndex = 4;
            this.cboLocalMean.Text = "1.0";
            this.cboLocalMean.Validating += new System.ComponentModel.CancelEventHandler(this.cboDoubleVal_Validating);
            // 
            // lblLocalGainMin
            // 
            this.lblLocalGainMin.AutoSize = true;
            this.lblLocalGainMin.Location = new System.Drawing.Point(217, 4);
            this.lblLocalGainMin.Name = "lblLocalGainMin";
            this.lblLocalGainMin.Size = new System.Drawing.Size(81, 13);
            this.lblLocalGainMin.TabIndex = 3;
            this.lblLocalGainMin.Text = "Local Gain Min:";
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
            this.cboLocalGainMin.Location = new System.Drawing.Point(300, 0);
            this.cboLocalGainMin.Name = "cboLocalGainMin";
            this.cboLocalGainMin.Size = new System.Drawing.Size(100, 21);
            this.cboLocalGainMin.TabIndex = 2;
            this.cboLocalGainMin.Text = "5.0";
            this.cboLocalGainMin.Validating += new System.ComponentModel.CancelEventHandler(this.cboDoubleVal_Validating);
            // 
            // lblLocalGain
            // 
            this.lblLocalGain.AutoSize = true;
            this.lblLocalGain.Location = new System.Drawing.Point(5, 4);
            this.lblLocalGain.Name = "lblLocalGain";
            this.lblLocalGain.Size = new System.Drawing.Size(94, 13);
            this.lblLocalGain.TabIndex = 1;
            this.lblLocalGain.Text = "Local Gain Factor:";
            // 
            // cboLocalGain
            // 
            this.cboLocalGain.FormattingEnabled = true;
            this.cboLocalGain.Items.AddRange(new object[] {
            "0.2",
            "0.5",
            "0.6",
            "0.8",
            "0.9"});
            this.cboLocalGain.Location = new System.Drawing.Point(101, 0);
            this.cboLocalGain.Name = "cboLocalGain";
            this.cboLocalGain.Size = new System.Drawing.Size(100, 21);
            this.cboLocalGain.TabIndex = 0;
            this.cboLocalGain.Text = "0.8";
            this.cboLocalGain.Validating += new System.ComponentModel.CancelEventHandler(this.cboDoubleVal_Validating);
            // 
            // pnlAnisotropic
            // 
            this.pnlAnisotropic.Controls.Add(this.lblBlockSize);
            this.pnlAnisotropic.Controls.Add(this.cboBlockSize);
            this.pnlAnisotropic.Controls.Add(this.lblSmoothing);
            this.pnlAnisotropic.Controls.Add(this.cboSmoothing);
            this.pnlAnisotropic.Controls.Add(this.lblEdgeThreshold);
            this.pnlAnisotropic.Controls.Add(this.cboEdgeThreshold);
            this.pnlAnisotropic.Controls.Add(this.lblIterations);
            this.pnlAnisotropic.Controls.Add(this.cboIterations);
            this.pnlAnisotropic.Location = new System.Drawing.Point(0, 29);
            this.pnlAnisotropic.Name = "pnlAnisotropic";
            this.pnlAnisotropic.Size = new System.Drawing.Size(404, 49);
            this.pnlAnisotropic.TabIndex = 45;
            // 
            // lblBlockSize
            // 
            this.lblBlockSize.AutoSize = true;
            this.lblBlockSize.Location = new System.Drawing.Point(242, 32);
            this.lblBlockSize.Name = "lblBlockSize";
            this.lblBlockSize.Size = new System.Drawing.Size(60, 13);
            this.lblBlockSize.TabIndex = 7;
            this.lblBlockSize.Text = "Block Size:";
            // 
            // cboBlockSize
            // 
            this.cboBlockSize.FormattingEnabled = true;
            this.cboBlockSize.Items.AddRange(new object[] {
            "8",
            "16",
            "32",
            "64",
            "128"});
            this.cboBlockSize.Location = new System.Drawing.Point(304, 28);
            this.cboBlockSize.Name = "cboBlockSize";
            this.cboBlockSize.Size = new System.Drawing.Size(100, 21);
            this.cboBlockSize.TabIndex = 6;
            this.cboBlockSize.Text = "64";
            this.cboBlockSize.Validating += new System.ComponentModel.CancelEventHandler(this.cboUIntVal_Validating);
            // 
            // lblSmoothing
            // 
            this.lblSmoothing.AutoSize = true;
            this.lblSmoothing.Location = new System.Drawing.Point(0, 32);
            this.lblSmoothing.Name = "lblSmoothing";
            this.lblSmoothing.Size = new System.Drawing.Size(103, 13);
            this.lblSmoothing.TabIndex = 5;
            this.lblSmoothing.Text = "Smoothing/Iteration:";
            // 
            // cboSmoothing
            // 
            this.cboSmoothing.FormattingEnabled = true;
            this.cboSmoothing.Items.AddRange(new object[] {
            "1",
            "2",
            "3",
            "4",
            "5"});
            this.cboSmoothing.Location = new System.Drawing.Point(105, 28);
            this.cboSmoothing.Name = "cboSmoothing";
            this.cboSmoothing.Size = new System.Drawing.Size(100, 21);
            this.cboSmoothing.TabIndex = 4;
            this.cboSmoothing.Text = "1";
            this.cboSmoothing.Validating += new System.ComponentModel.CancelEventHandler(this.cboUIntVal_Validating);
            // 
            // lblEdgeThreshold
            // 
            this.lblEdgeThreshold.AutoSize = true;
            this.lblEdgeThreshold.Location = new System.Drawing.Point(217, 4);
            this.lblEdgeThreshold.Name = "lblEdgeThreshold";
            this.lblEdgeThreshold.Size = new System.Drawing.Size(85, 13);
            this.lblEdgeThreshold.TabIndex = 3;
            this.lblEdgeThreshold.Text = "Edge Threshold:";
            // 
            // cboEdgeThreshold
            // 
            this.cboEdgeThreshold.FormattingEnabled = true;
            this.cboEdgeThreshold.Items.AddRange(new object[] {
            "1",
            "5",
            "10",
            "15",
            "20"});
            this.cboEdgeThreshold.Location = new System.Drawing.Point(304, 0);
            this.cboEdgeThreshold.Name = "cboEdgeThreshold";
            this.cboEdgeThreshold.Size = new System.Drawing.Size(100, 21);
            this.cboEdgeThreshold.TabIndex = 2;
            this.cboEdgeThreshold.Text = "5";
            this.cboEdgeThreshold.Validating += new System.ComponentModel.CancelEventHandler(this.cboUIntVal_Validating);
            // 
            // lblIterations
            // 
            this.lblIterations.AutoSize = true;
            this.lblIterations.Location = new System.Drawing.Point(28, 4);
            this.lblIterations.Name = "lblIterations";
            this.lblIterations.Size = new System.Drawing.Size(75, 13);
            this.lblIterations.TabIndex = 1;
            this.lblIterations.Text = "# of Iterations:";
            // 
            // cboIterations
            // 
            this.cboIterations.FormattingEnabled = true;
            this.cboIterations.Items.AddRange(new object[] {
            "10",
            "20",
            "50",
            "100",
            "200"});
            this.cboIterations.Location = new System.Drawing.Point(105, 0);
            this.cboIterations.Name = "cboIterations";
            this.cboIterations.Size = new System.Drawing.Size(100, 21);
            this.cboIterations.TabIndex = 0;
            this.cboIterations.Text = "20";
            this.cboIterations.Validating += new System.ComponentModel.CancelEventHandler(this.cboUIntVal_Validating);
            // 
            // rbImproved
            // 
            this.rbImproved.AutoSize = true;
            this.rbImproved.Location = new System.Drawing.Point(199, 0);
            this.rbImproved.Name = "rbImproved";
            this.rbImproved.Size = new System.Drawing.Size(69, 17);
            this.rbImproved.TabIndex = 2;
            this.rbImproved.TabStop = true;
            this.rbImproved.Text = "Improved";
            this.rbImproved.UseVisualStyleBackColor = true;
            this.rbImproved.Click += new System.EventHandler(this.rbSpatial_Click);
            // 
            // rbStandard
            // 
            this.rbStandard.AutoSize = true;
            this.rbStandard.Location = new System.Drawing.Point(104, 0);
            this.rbStandard.Name = "rbStandard";
            this.rbStandard.Size = new System.Drawing.Size(68, 17);
            this.rbStandard.TabIndex = 1;
            this.rbStandard.TabStop = true;
            this.rbStandard.Text = "Standard";
            this.rbStandard.UseVisualStyleBackColor = true;
            this.rbStandard.Click += new System.EventHandler(this.rbSpatial_Click);
            // 
            // btnHelp
            // 
            this.btnHelp.BackColor = System.Drawing.Color.Yellow;
            this.btnHelp.Location = new System.Drawing.Point(12, 466);
            this.btnHelp.Name = "btnHelp";
            this.btnHelp.Size = new System.Drawing.Size(60, 26);
            this.btnHelp.TabIndex = 41;
            this.btnHelp.Text = "Help";
            this.btnHelp.UseVisualStyleBackColor = false;
            this.btnHelp.Click += new System.EventHandler(this.btnHelp_Click);
            // 
            // btnCancel
            // 
            this.btnCancel.BackColor = System.Drawing.Color.OrangeRed;
            this.btnCancel.Location = new System.Drawing.Point(402, 466);
            this.btnCancel.Name = "btnCancel";
            this.btnCancel.Size = new System.Drawing.Size(60, 26);
            this.btnCancel.TabIndex = 42;
            this.btnCancel.Text = "Cancel";
            this.btnCancel.UseVisualStyleBackColor = false;
            this.btnCancel.Click += new System.EventHandler(this.btnCancel_Click);
            // 
            // btnReset
            // 
            this.btnReset.BackColor = System.Drawing.Color.CornflowerBlue;
            this.btnReset.Location = new System.Drawing.Point(468, 466);
            this.btnReset.Name = "btnReset";
            this.btnReset.Size = new System.Drawing.Size(60, 26);
            this.btnReset.TabIndex = 39;
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
            this.btnApply.TabIndex = 40;
            this.btnApply.Text = "Apply";
            this.btnApply.UseVisualStyleBackColor = false;
            this.btnApply.Click += new System.EventHandler(this.btnApply_Click);
            // 
            // SpatialFilter
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.rbMedian);
            this.Controls.Add(this.rbMinimum);
            this.Controls.Add(this.rbMidpoint);
            this.Controls.Add(this.rbMaximum);
            this.Controls.Add(this.rbAlphaTrim);
            this.Controls.Add(this.rbArithmetic);
            this.Controls.Add(this.rbGeometric);
            this.Controls.Add(this.rbHarmonic);
            this.Controls.Add(this.rbContraHarmonic);
            this.Controls.Add(this.rbYpMean);
            this.Controls.Add(this.rbMMSE);
            this.Controls.Add(this.rbAdaptiveMedian);
            this.Controls.Add(this.rbKuwahara);
            this.Controls.Add(this.rbAdaptiveContrast);
            this.Controls.Add(this.rbAnisotropic);
            this.Controls.Add(this.grpOrderFilters);
            this.Controls.Add(this.grpMeanFilters);
            this.Controls.Add(this.grpAdaptiveFilters);
            this.Controls.Add(this.btnHelp);
            this.Controls.Add(this.btnCancel);
            this.Controls.Add(this.btnReset);
            this.Controls.Add(this.btnApply);
            this.Name = "SpatialFilter";
            this.Size = new System.Drawing.Size(600, 495);
            this.grpOrderFilters.ResumeLayout(false);
            this.pnlOrderFilters.ResumeLayout(false);
            this.pnlOrderFilters.PerformLayout();
            this.grpMeanFilters.ResumeLayout(false);
            this.pnlMeanFilters.ResumeLayout(false);
            this.pnlMeanFilters.PerformLayout();
            this.grpAdaptiveFilters.ResumeLayout(false);
            this.pnlAdaptiveFilters.ResumeLayout(false);
            this.pnlAdaptiveFilters.PerformLayout();
            this.pnlMMSE.ResumeLayout(false);
            this.pnlMMSE.PerformLayout();
            this.pnlAdaptiveContrast.ResumeLayout(false);
            this.pnlAdaptiveContrast.PerformLayout();
            this.pnlAnisotropic.ResumeLayout(false);
            this.pnlAnisotropic.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.RadioButton rbMedian;
        private System.Windows.Forms.RadioButton rbMinimum;
        private System.Windows.Forms.RadioButton rbMidpoint;
        private System.Windows.Forms.RadioButton rbMaximum;
        private System.Windows.Forms.RadioButton rbAlphaTrim;
        private System.Windows.Forms.RadioButton rbArithmetic;
        private System.Windows.Forms.RadioButton rbGeometric;
        private System.Windows.Forms.RadioButton rbHarmonic;
        private System.Windows.Forms.RadioButton rbContraHarmonic;
        private System.Windows.Forms.RadioButton rbYpMean;
        private System.Windows.Forms.RadioButton rbMMSE;
        private System.Windows.Forms.RadioButton rbAdaptiveMedian;
        private System.Windows.Forms.RadioButton rbKuwahara;
        private System.Windows.Forms.RadioButton rbAdaptiveContrast;
        private System.Windows.Forms.RadioButton rbAnisotropic;
        private System.Windows.Forms.GroupBox grpOrderFilters;
        private System.Windows.Forms.Panel pnlOrderFilters;
        private System.Windows.Forms.Label lblTrimSize;
        private System.Windows.Forms.TextBox txtTrimSize;
        private System.Windows.Forms.Label lblMaskSizeOrder;
        private System.Windows.Forms.ComboBox cboMaskSizeOrder;
        private System.Windows.Forms.GroupBox grpMeanFilters;
        private System.Windows.Forms.Panel pnlMeanFilters;
        private System.Windows.Forms.Label lblFilterOrder;
        private System.Windows.Forms.ComboBox cboFilterOrder;
        private System.Windows.Forms.Label lblMaskSizeMean;
        private System.Windows.Forms.ComboBox cboMaskSizeMean;
        private System.Windows.Forms.GroupBox grpAdaptiveFilters;
        private System.Windows.Forms.Panel pnlAdaptiveFilters;
        private System.Windows.Forms.Label lblMaskSizeAdaptive;
        private System.Windows.Forms.ComboBox cboMaskSizeAdaptive;
        private System.Windows.Forms.Panel pnlMMSE;
        private System.Windows.Forms.Label lblThreshold;
        private System.Windows.Forms.ComboBox cboThreshold;
        private System.Windows.Forms.Label lblKernelSizeMMSE;
        private System.Windows.Forms.ComboBox cboKernelSizeMMSE;
        private System.Windows.Forms.Label lblNoiseVar;
        private System.Windows.Forms.ComboBox cboNoiseVar;
        private System.Windows.Forms.Panel pnlAdaptiveContrast;
        private System.Windows.Forms.Label lblKernelSizeAC;
        private System.Windows.Forms.ComboBox cboKernelSizeAC;
        private System.Windows.Forms.Label lblLocalGainMax;
        private System.Windows.Forms.ComboBox cboLocalGainMax;
        private System.Windows.Forms.Label lblLocalMean;
        private System.Windows.Forms.ComboBox cboLocalMean;
        private System.Windows.Forms.Label lblLocalGainMin;
        private System.Windows.Forms.ComboBox cboLocalGainMin;
        private System.Windows.Forms.Label lblLocalGain;
        private System.Windows.Forms.ComboBox cboLocalGain;
        private System.Windows.Forms.Panel pnlAnisotropic;
        private System.Windows.Forms.Label lblBlockSize;
        private System.Windows.Forms.ComboBox cboBlockSize;
        private System.Windows.Forms.Label lblSmoothing;
        private System.Windows.Forms.ComboBox cboSmoothing;
        private System.Windows.Forms.Label lblEdgeThreshold;
        private System.Windows.Forms.ComboBox cboEdgeThreshold;
        private System.Windows.Forms.Label lblIterations;
        private System.Windows.Forms.ComboBox cboIterations;
        private System.Windows.Forms.RadioButton rbImproved;
        private System.Windows.Forms.RadioButton rbStandard;
        private System.Windows.Forms.Button btnHelp;
        private System.Windows.Forms.Button btnCancel;
        private System.Windows.Forms.Button btnReset;
        private System.Windows.Forms.Button btnApply;
    }
}
