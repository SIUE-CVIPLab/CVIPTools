namespace CVIPGUI.Analysis
{
    partial class Segmentation
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
            this.rbGrayLevelQuant = new System.Windows.Forms.RadioButton();
            this.rbAutoThresh = new System.Windows.Forms.RadioButton();
            this.rbOtsu = new System.Windows.Forms.RadioButton();
            this.rbHistThreshold = new System.Windows.Forms.RadioButton();
            this.rbFuzzyCMean = new System.Windows.Forms.RadioButton();
            this.rbMedianCut = new System.Windows.Forms.RadioButton();
            this.rbPCTMedian = new System.Windows.Forms.RadioButton();
            this.rbSCTCenter = new System.Windows.Forms.RadioButton();
            this.rbMultiResolution = new System.Windows.Forms.RadioButton();
            this.rbSplitMerge = new System.Windows.Forms.RadioButton();
            this.rbWatershed = new System.Windows.Forms.RadioButton();
            this.rbGVFSnake = new System.Windows.Forms.RadioButton();
            this.grpSegmentation = new System.Windows.Forms.GroupBox();
            this.pnlGVFSnake = new System.Windows.Forms.Panel();
            this.cboKappa = new System.Windows.Forms.ComboBox();
            this.lblKappa = new System.Windows.Forms.Label();
            this.cboBeta = new System.Windows.Forms.ComboBox();
            this.lblBeta = new System.Windows.Forms.Label();
            this.cboAlpha = new System.Windows.Forms.ComboBox();
            this.lblAlpha = new System.Windows.Forms.Label();
            this.cboSnakeIterations = new System.Windows.Forms.ComboBox();
            this.lblSnakeIterations = new System.Windows.Forms.Label();
            this.pnlMultiRes = new System.Windows.Forms.Panel();
            this.cboPixelDistance = new System.Windows.Forms.ComboBox();
            this.lblPixelDistance = new System.Windows.Forms.Label();
            this.cboPercentage = new System.Windows.Forms.ComboBox();
            this.lblPercentage = new System.Windows.Forms.Label();
            this.chkPCT = new System.Windows.Forms.CheckBox();
            this.cboSimilarity = new System.Windows.Forms.ComboBox();
            this.lblSimilarity = new System.Windows.Forms.Label();
            this.cboThreshold = new System.Windows.Forms.ComboBox();
            this.lblThreshold = new System.Windows.Forms.Label();
            this.cboEntryLevel = new System.Windows.Forms.ComboBox();
            this.lblEntryLevel = new System.Windows.Forms.Label();
            this.rbWeightedGrayLevel = new System.Windows.Forms.RadioButton();
            this.rbLocalStd = new System.Windows.Forms.RadioButton();
            this.rbLocalMean = new System.Windows.Forms.RadioButton();
            this.rbHomogeneity = new System.Windows.Forms.RadioButton();
            this.rbVariance = new System.Windows.Forms.RadioButton();
            this.rbPureUniform = new System.Windows.Forms.RadioButton();
            this.pnlGrayLevelQuant = new System.Windows.Forms.Panel();
            this.cboWatershedThreshold = new System.Windows.Forms.ComboBox();
            this.lblWatershedThreshold = new System.Windows.Forms.Label();
            this.chkMergeResult = new System.Windows.Forms.CheckBox();
            this.cboSCTBAxis = new System.Windows.Forms.ComboBox();
            this.lblSCTBAxis = new System.Windows.Forms.Label();
            this.cboSCTAAxis = new System.Windows.Forms.ComboBox();
            this.lblSCTAAxis = new System.Windows.Forms.Label();
            this.cboNumColors = new System.Windows.Forms.ComboBox();
            this.lblNumColors = new System.Windows.Forms.Label();
            this.cboFuzzyCVariance = new System.Windows.Forms.ComboBox();
            this.lblFuzzyCVariance = new System.Windows.Forms.Label();
            this.cboLimit = new System.Windows.Forms.ComboBox();
            this.lblLimit = new System.Windows.Forms.Label();
            this.cboQuantMethod = new System.Windows.Forms.ComboBox();
            this.lblQuantMethod = new System.Windows.Forms.Label();
            this.cboNumGrayLevels = new System.Windows.Forms.ComboBox();
            this.lblNumGrayLevels = new System.Windows.Forms.Label();
            this.pnlHistThresh = new System.Windows.Forms.Panel();
            this.lblHistTore = new System.Windows.Forms.Label();
            this.cbHistThresh = new System.Windows.Forms.ComboBox();
            this.lblHistThresh = new System.Windows.Forms.Label();
            this.rbHistThreshBands = new System.Windows.Forms.RadioButton();
            this.rbHistThreshPCT = new System.Windows.Forms.RadioButton();
            this.rbHistThreshLum = new System.Windows.Forms.RadioButton();
            this.grpMorpho = new System.Windows.Forms.GroupBox();
            this.pnlFilterSize = new System.Windows.Forms.Panel();
            this.cboSkeletonMethod = new System.Windows.Forms.ComboBox();
            this.lblSkeletonMethod = new System.Windows.Forms.Label();
            this.cboSkeletonConnect = new System.Windows.Forms.ComboBox();
            this.lblSkeletonConnect = new System.Windows.Forms.Label();
            this.cboSkeletonIterations = new System.Windows.Forms.ComboBox();
            this.lblSkeletonIterations = new System.Windows.Forms.Label();
            this.rbFilterSize9x9 = new System.Windows.Forms.RadioButton();
            this.rbFilterSize7x7 = new System.Windows.Forms.RadioButton();
            this.rbFilterSize5x5 = new System.Windows.Forms.RadioButton();
            this.rbFilterSize3x3 = new System.Windows.Forms.RadioButton();
            this.lblFilterSize = new System.Windows.Forms.Label();
            this.pnlMorphological = new System.Windows.Forms.Panel();
            this.lblKernelType = new System.Windows.Forms.Label();
            this.cboKernelHeight = new System.Windows.Forms.ComboBox();
            this.lblKernelHeight = new System.Windows.Forms.Label();
            this.cboKernelWidth = new System.Windows.Forms.ComboBox();
            this.lblKernelWidth = new System.Windows.Forms.Label();
            this.cboKernelSize = new System.Windows.Forms.ComboBox();
            this.lblKernelSize = new System.Windows.Forms.Label();
            this.cboKernelType = new System.Windows.Forms.ComboBox();
            this.lblBinaryImages = new System.Windows.Forms.Label();
            this.lblAllImages = new System.Windows.Forms.Label();
            this.pnlMorphIterative = new System.Windows.Forms.Panel();
            this.chkSurround14 = new System.Windows.Forms.CheckBox();
            this.chkSurround13 = new System.Windows.Forms.CheckBox();
            this.chkSurround12 = new System.Windows.Forms.CheckBox();
            this.chkSurround11 = new System.Windows.Forms.CheckBox();
            this.chkSurround10 = new System.Windows.Forms.CheckBox();
            this.chkSurround9 = new System.Windows.Forms.CheckBox();
            this.chkSurround8 = new System.Windows.Forms.CheckBox();
            this.chkSurround7 = new System.Windows.Forms.CheckBox();
            this.chkSurround6 = new System.Windows.Forms.CheckBox();
            this.chkSurround5 = new System.Windows.Forms.CheckBox();
            this.chkSurround4 = new System.Windows.Forms.CheckBox();
            this.chkSurround3 = new System.Windows.Forms.CheckBox();
            this.chkSurround2 = new System.Windows.Forms.CheckBox();
            this.chkSurround1 = new System.Windows.Forms.CheckBox();
            this.btnViewSurrounds = new System.Windows.Forms.Button();
            this.cboSubFields = new System.Windows.Forms.ComboBox();
            this.lblSubFields = new System.Windows.Forms.Label();
            this.cboMorphIterations = new System.Windows.Forms.ComboBox();
            this.lblMorphIterations = new System.Windows.Forms.Label();
            this.cboBoolFunc = new System.Windows.Forms.ComboBox();
            this.lblBoolFunc = new System.Windows.Forms.Label();
            this.chkRotate = new System.Windows.Forms.CheckBox();
            this.btnHelp = new System.Windows.Forms.Button();
            this.btnCancel = new System.Windows.Forms.Button();
            this.btnReset = new System.Windows.Forms.Button();
            this.btnApply = new System.Windows.Forms.Button();
            this.grpPreProcessing = new System.Windows.Forms.GroupBox();
            this.pnlAnisotropic = new System.Windows.Forms.Panel();
            this.lblBlockSize = new System.Windows.Forms.Label();
            this.cboBlockSize = new System.Windows.Forms.ComboBox();
            this.lblEdgeThreshold = new System.Windows.Forms.Label();
            this.cboEdgeThreshold = new System.Windows.Forms.ComboBox();
            this.lblSmoothing = new System.Windows.Forms.Label();
            this.cboSmoothing = new System.Windows.Forms.ComboBox();
            this.lblIterations = new System.Windows.Forms.Label();
            this.cboIterations = new System.Windows.Forms.ComboBox();
            this.lblType = new System.Windows.Forms.Label();
            this.radioButton1 = new System.Windows.Forms.RadioButton();
            this.radioButton2 = new System.Windows.Forms.RadioButton();
            this.pnlMedian = new System.Windows.Forms.Panel();
            this.rbParametric = new System.Windows.Forms.RadioButton();
            this.lblMedianType = new System.Windows.Forms.Label();
            this.rbStandard = new System.Windows.Forms.RadioButton();
            this.rbAdaptive = new System.Windows.Forms.RadioButton();
            this.cboMaskSize = new System.Windows.Forms.ComboBox();
            this.lblMaskSize = new System.Windows.Forms.Label();
            this.rbSuperPixel = new System.Windows.Forms.RadioButton();
            this.rbAnatropicDiffusionFilter = new System.Windows.Forms.RadioButton();
            this.rbKurwaharaFilter = new System.Windows.Forms.RadioButton();
            this.rbMedianFilter = new System.Windows.Forms.RadioButton();
            this.rbSkeletonization = new System.Windows.Forms.RadioButton();
            this.rbThinning = new System.Windows.Forms.RadioButton();
            this.rbHitOrMiss = new System.Windows.Forms.RadioButton();
            this.rbMorphDilation = new System.Windows.Forms.RadioButton();
            this.rbMorphIterative = new System.Windows.Forms.RadioButton();
            this.rbMorphErosion = new System.Windows.Forms.RadioButton();
            this.rbMorphClosing = new System.Windows.Forms.RadioButton();
            this.rbMorphOpening = new System.Windows.Forms.RadioButton();
            this.grpSegmentation.SuspendLayout();
            this.pnlGVFSnake.SuspendLayout();
            this.pnlMultiRes.SuspendLayout();
            this.pnlGrayLevelQuant.SuspendLayout();
            this.pnlHistThresh.SuspendLayout();
            this.grpMorpho.SuspendLayout();
            this.pnlFilterSize.SuspendLayout();
            this.pnlMorphological.SuspendLayout();
            this.pnlMorphIterative.SuspendLayout();
            this.grpPreProcessing.SuspendLayout();
            this.pnlAnisotropic.SuspendLayout();
            this.pnlMedian.SuspendLayout();
            this.SuspendLayout();
            // 
            // rbGrayLevelQuant
            // 
            this.rbGrayLevelQuant.AutoSize = true;
            this.rbGrayLevelQuant.Checked = true;
            this.rbGrayLevelQuant.Location = new System.Drawing.Point(20, 134);
            this.rbGrayLevelQuant.Name = "rbGrayLevelQuant";
            this.rbGrayLevelQuant.Size = new System.Drawing.Size(138, 17);
            this.rbGrayLevelQuant.TabIndex = 0;
            this.rbGrayLevelQuant.TabStop = true;
            this.rbGrayLevelQuant.Text = "Gray Level Quantization";
            this.rbGrayLevelQuant.UseVisualStyleBackColor = true;
            this.rbGrayLevelQuant.CheckedChanged += new System.EventHandler(this.rbSegmentation_CheckedChanged);
            // 
            // rbAutoThresh
            // 
            this.rbAutoThresh.AutoSize = true;
            this.rbAutoThresh.Location = new System.Drawing.Point(20, 153);
            this.rbAutoThresh.Name = "rbAutoThresh";
            this.rbAutoThresh.Size = new System.Drawing.Size(179, 17);
            this.rbAutoThresh.TabIndex = 1;
            this.rbAutoThresh.Text = "Auto Single Threshold (K-means)";
            this.rbAutoThresh.UseVisualStyleBackColor = true;
            this.rbAutoThresh.CheckedChanged += new System.EventHandler(this.rbSegmentation_CheckedChanged);
            // 
            // rbOtsu
            // 
            this.rbOtsu.AutoSize = true;
            this.rbOtsu.Location = new System.Drawing.Point(20, 172);
            this.rbOtsu.Name = "rbOtsu";
            this.rbOtsu.Size = new System.Drawing.Size(111, 17);
            this.rbOtsu.TabIndex = 2;
            this.rbOtsu.Text = "Otsu Thresholding";
            this.rbOtsu.UseVisualStyleBackColor = true;
            this.rbOtsu.CheckedChanged += new System.EventHandler(this.rbSegmentation_CheckedChanged);
            // 
            // rbHistThreshold
            // 
            this.rbHistThreshold.AutoSize = true;
            this.rbHistThreshold.Location = new System.Drawing.Point(20, 191);
            this.rbHistThreshold.Name = "rbHistThreshold";
            this.rbHistThreshold.Size = new System.Drawing.Size(136, 17);
            this.rbHistThreshold.TabIndex = 3;
            this.rbHistThreshold.Text = "Histogram Thresholding";
            this.rbHistThreshold.UseVisualStyleBackColor = true;
            this.rbHistThreshold.CheckedChanged += new System.EventHandler(this.rbSegmentation_CheckedChanged);
            // 
            // rbFuzzyCMean
            // 
            this.rbFuzzyCMean.AutoSize = true;
            this.rbFuzzyCMean.Location = new System.Drawing.Point(20, 210);
            this.rbFuzzyCMean.Name = "rbFuzzyCMean";
            this.rbFuzzyCMean.Size = new System.Drawing.Size(92, 17);
            this.rbFuzzyCMean.TabIndex = 4;
            this.rbFuzzyCMean.Text = "Fuzzy C Mean";
            this.rbFuzzyCMean.UseVisualStyleBackColor = true;
            this.rbFuzzyCMean.CheckedChanged += new System.EventHandler(this.rbSegmentation_CheckedChanged);
            // 
            // rbMedianCut
            // 
            this.rbMedianCut.AutoSize = true;
            this.rbMedianCut.Location = new System.Drawing.Point(20, 229);
            this.rbMedianCut.Name = "rbMedianCut";
            this.rbMedianCut.Size = new System.Drawing.Size(79, 17);
            this.rbMedianCut.TabIndex = 5;
            this.rbMedianCut.Text = "Median Cut";
            this.rbMedianCut.UseVisualStyleBackColor = true;
            this.rbMedianCut.CheckedChanged += new System.EventHandler(this.rbSegmentation_CheckedChanged);
            // 
            // rbPCTMedian
            // 
            this.rbPCTMedian.AutoSize = true;
            this.rbPCTMedian.Location = new System.Drawing.Point(20, 248);
            this.rbPCTMedian.Name = "rbPCTMedian";
            this.rbPCTMedian.Size = new System.Drawing.Size(86, 17);
            this.rbPCTMedian.TabIndex = 6;
            this.rbPCTMedian.Text = "PCT/Median";
            this.rbPCTMedian.UseVisualStyleBackColor = true;
            this.rbPCTMedian.CheckedChanged += new System.EventHandler(this.rbSegmentation_CheckedChanged);
            // 
            // rbSCTCenter
            // 
            this.rbSCTCenter.AutoSize = true;
            this.rbSCTCenter.Location = new System.Drawing.Point(20, 267);
            this.rbSCTCenter.Name = "rbSCTCenter";
            this.rbSCTCenter.Size = new System.Drawing.Size(82, 17);
            this.rbSCTCenter.TabIndex = 7;
            this.rbSCTCenter.Text = "SCT/Center";
            this.rbSCTCenter.UseVisualStyleBackColor = true;
            this.rbSCTCenter.CheckedChanged += new System.EventHandler(this.rbSegmentation_CheckedChanged);
            // 
            // rbMultiResolution
            // 
            this.rbMultiResolution.AutoSize = true;
            this.rbMultiResolution.Location = new System.Drawing.Point(20, 286);
            this.rbMultiResolution.Name = "rbMultiResolution";
            this.rbMultiResolution.Size = new System.Drawing.Size(103, 17);
            this.rbMultiResolution.TabIndex = 8;
            this.rbMultiResolution.Text = "Multi_Resolution";
            this.rbMultiResolution.UseVisualStyleBackColor = true;
            this.rbMultiResolution.CheckedChanged += new System.EventHandler(this.rbSegmentation_CheckedChanged);
            // 
            // rbSplitMerge
            // 
            this.rbSplitMerge.AutoSize = true;
            this.rbSplitMerge.Location = new System.Drawing.Point(20, 305);
            this.rbSplitMerge.Name = "rbSplitMerge";
            this.rbSplitMerge.Size = new System.Drawing.Size(99, 17);
            this.rbSplitMerge.TabIndex = 9;
            this.rbSplitMerge.Text = "Split and Merge";
            this.rbSplitMerge.UseVisualStyleBackColor = true;
            this.rbSplitMerge.CheckedChanged += new System.EventHandler(this.rbSegmentation_CheckedChanged);
            // 
            // rbWatershed
            // 
            this.rbWatershed.AutoSize = true;
            this.rbWatershed.Location = new System.Drawing.Point(20, 324);
            this.rbWatershed.Name = "rbWatershed";
            this.rbWatershed.Size = new System.Drawing.Size(145, 17);
            this.rbWatershed.TabIndex = 10;
            this.rbWatershed.Text = "Watershed Segmentation";
            this.rbWatershed.UseVisualStyleBackColor = true;
            this.rbWatershed.CheckedChanged += new System.EventHandler(this.rbSegmentation_CheckedChanged);
            // 
            // rbGVFSnake
            // 
            this.rbGVFSnake.AutoSize = true;
            this.rbGVFSnake.Location = new System.Drawing.Point(20, 343);
            this.rbGVFSnake.Name = "rbGVFSnake";
            this.rbGVFSnake.Size = new System.Drawing.Size(158, 17);
            this.rbGVFSnake.TabIndex = 11;
            this.rbGVFSnake.Text = "Gradient Vector Flow Snake";
            this.rbGVFSnake.UseVisualStyleBackColor = true;
            this.rbGVFSnake.Visible = false;
            this.rbGVFSnake.CheckedChanged += new System.EventHandler(this.rbSegmentation_CheckedChanged);
            // 
            // grpSegmentation
            // 
            this.grpSegmentation.Controls.Add(this.pnlGVFSnake);
            this.grpSegmentation.Controls.Add(this.pnlMultiRes);
            this.grpSegmentation.Controls.Add(this.pnlGrayLevelQuant);
            this.grpSegmentation.Controls.Add(this.pnlHistThresh);
            this.grpSegmentation.Location = new System.Drawing.Point(12, 114);
            this.grpSegmentation.Name = "grpSegmentation";
            this.grpSegmentation.Size = new System.Drawing.Size(628, 257);
            this.grpSegmentation.TabIndex = 20;
            this.grpSegmentation.TabStop = false;
            this.grpSegmentation.Text = "Segmentation";
            // 
            // pnlGVFSnake
            // 
            this.pnlGVFSnake.Controls.Add(this.cboKappa);
            this.pnlGVFSnake.Controls.Add(this.lblKappa);
            this.pnlGVFSnake.Controls.Add(this.cboBeta);
            this.pnlGVFSnake.Controls.Add(this.lblBeta);
            this.pnlGVFSnake.Controls.Add(this.cboAlpha);
            this.pnlGVFSnake.Controls.Add(this.lblAlpha);
            this.pnlGVFSnake.Controls.Add(this.cboSnakeIterations);
            this.pnlGVFSnake.Controls.Add(this.lblSnakeIterations);
            this.pnlGVFSnake.Location = new System.Drawing.Point(178, 152);
            this.pnlGVFSnake.Name = "pnlGVFSnake";
            this.pnlGVFSnake.Size = new System.Drawing.Size(179, 105);
            this.pnlGVFSnake.TabIndex = 2;
            this.pnlGVFSnake.Visible = false;
            // 
            // cboKappa
            // 
            this.cboKappa.FormattingEnabled = true;
            this.cboKappa.Items.AddRange(new object[] {
            "0.05",
            "0.10",
            "0.25",
            "0.45",
            "0.85",
            "0.95",
            "0.155"});
            this.cboKappa.Location = new System.Drawing.Point(107, 84);
            this.cboKappa.Name = "cboKappa";
            this.cboKappa.Size = new System.Drawing.Size(72, 21);
            this.cboKappa.TabIndex = 7;
            this.cboKappa.Text = "0.01";
            this.cboKappa.Validating += new System.ComponentModel.CancelEventHandler(this.cboDoubleVal_Validating);
            // 
            // lblKappa
            // 
            this.lblKappa.AutoSize = true;
            this.lblKappa.Location = new System.Drawing.Point(63, 88);
            this.lblKappa.Name = "lblKappa";
            this.lblKappa.Size = new System.Drawing.Size(41, 13);
            this.lblKappa.TabIndex = 6;
            this.lblKappa.Text = "Kappa:";
            // 
            // cboBeta
            // 
            this.cboBeta.FormattingEnabled = true;
            this.cboBeta.Items.AddRange(new object[] {
            "0.05",
            "0.10",
            "0.25",
            "0.45",
            "0.85",
            "0.95",
            "0.155"});
            this.cboBeta.Location = new System.Drawing.Point(107, 56);
            this.cboBeta.Name = "cboBeta";
            this.cboBeta.Size = new System.Drawing.Size(72, 21);
            this.cboBeta.TabIndex = 5;
            this.cboBeta.Text = "0.01";
            this.cboBeta.Validating += new System.ComponentModel.CancelEventHandler(this.cboDoubleVal_Validating);
            // 
            // lblBeta
            // 
            this.lblBeta.AutoSize = true;
            this.lblBeta.Location = new System.Drawing.Point(72, 60);
            this.lblBeta.Name = "lblBeta";
            this.lblBeta.Size = new System.Drawing.Size(32, 13);
            this.lblBeta.TabIndex = 4;
            this.lblBeta.Text = "Beta:";
            // 
            // cboAlpha
            // 
            this.cboAlpha.FormattingEnabled = true;
            this.cboAlpha.Items.AddRange(new object[] {
            "0.05",
            "0.10",
            "0.25",
            "0.45",
            "0.85",
            "0.95",
            "0.155"});
            this.cboAlpha.Location = new System.Drawing.Point(107, 28);
            this.cboAlpha.Name = "cboAlpha";
            this.cboAlpha.Size = new System.Drawing.Size(72, 21);
            this.cboAlpha.TabIndex = 3;
            this.cboAlpha.Text = "0.01";
            this.cboAlpha.Validating += new System.ComponentModel.CancelEventHandler(this.cboDoubleVal_Validating);
            // 
            // lblAlpha
            // 
            this.lblAlpha.AutoSize = true;
            this.lblAlpha.Location = new System.Drawing.Point(67, 32);
            this.lblAlpha.Name = "lblAlpha";
            this.lblAlpha.Size = new System.Drawing.Size(37, 13);
            this.lblAlpha.TabIndex = 2;
            this.lblAlpha.Text = "Alpha:";
            // 
            // cboSnakeIterations
            // 
            this.cboSnakeIterations.FormattingEnabled = true;
            this.cboSnakeIterations.Items.AddRange(new object[] {
            "5",
            "10",
            "25",
            "45",
            "85",
            "100",
            "150"});
            this.cboSnakeIterations.Location = new System.Drawing.Point(107, 0);
            this.cboSnakeIterations.Name = "cboSnakeIterations";
            this.cboSnakeIterations.Size = new System.Drawing.Size(72, 21);
            this.cboSnakeIterations.TabIndex = 1;
            this.cboSnakeIterations.Text = "5";
            this.cboSnakeIterations.Validating += new System.ComponentModel.CancelEventHandler(this.cboUIntVal_Validating);
            // 
            // lblSnakeIterations
            // 
            this.lblSnakeIterations.AutoSize = true;
            this.lblSnakeIterations.Location = new System.Drawing.Point(0, 4);
            this.lblSnakeIterations.Name = "lblSnakeIterations";
            this.lblSnakeIterations.Size = new System.Drawing.Size(105, 13);
            this.lblSnakeIterations.TabIndex = 0;
            this.lblSnakeIterations.Text = "Number of Iterations:";
            // 
            // pnlMultiRes
            // 
            this.pnlMultiRes.Controls.Add(this.cboPixelDistance);
            this.pnlMultiRes.Controls.Add(this.lblPixelDistance);
            this.pnlMultiRes.Controls.Add(this.cboPercentage);
            this.pnlMultiRes.Controls.Add(this.lblPercentage);
            this.pnlMultiRes.Controls.Add(this.chkPCT);
            this.pnlMultiRes.Controls.Add(this.cboSimilarity);
            this.pnlMultiRes.Controls.Add(this.lblSimilarity);
            this.pnlMultiRes.Controls.Add(this.cboThreshold);
            this.pnlMultiRes.Controls.Add(this.lblThreshold);
            this.pnlMultiRes.Controls.Add(this.cboEntryLevel);
            this.pnlMultiRes.Controls.Add(this.lblEntryLevel);
            this.pnlMultiRes.Controls.Add(this.rbWeightedGrayLevel);
            this.pnlMultiRes.Controls.Add(this.rbLocalStd);
            this.pnlMultiRes.Controls.Add(this.rbLocalMean);
            this.pnlMultiRes.Controls.Add(this.rbHomogeneity);
            this.pnlMultiRes.Controls.Add(this.rbVariance);
            this.pnlMultiRes.Controls.Add(this.rbPureUniform);
            this.pnlMultiRes.Location = new System.Drawing.Point(178, 93);
            this.pnlMultiRes.Name = "pnlMultiRes";
            this.pnlMultiRes.Size = new System.Drawing.Size(310, 164);
            this.pnlMultiRes.TabIndex = 1;
            // 
            // cboPixelDistance
            // 
            this.cboPixelDistance.FormattingEnabled = true;
            this.cboPixelDistance.Items.AddRange(new object[] {
            "0.0",
            "1.0",
            "2.0",
            "3.0",
            "4.0",
            "5.0"});
            this.cboPixelDistance.Location = new System.Drawing.Point(224, 143);
            this.cboPixelDistance.Name = "cboPixelDistance";
            this.cboPixelDistance.Size = new System.Drawing.Size(69, 21);
            this.cboPixelDistance.TabIndex = 16;
            this.cboPixelDistance.Text = "2.0";
            this.cboPixelDistance.Validating += new System.ComponentModel.CancelEventHandler(this.cboDoubleVal_Validating);
            // 
            // lblPixelDistance
            // 
            this.lblPixelDistance.AutoSize = true;
            this.lblPixelDistance.Location = new System.Drawing.Point(148, 147);
            this.lblPixelDistance.Name = "lblPixelDistance";
            this.lblPixelDistance.Size = new System.Drawing.Size(72, 13);
            this.lblPixelDistance.TabIndex = 15;
            this.lblPixelDistance.Text = "Pixel distance";
            // 
            // cboPercentage
            // 
            this.cboPercentage.FormattingEnabled = true;
            this.cboPercentage.Items.AddRange(new object[] {
            "0.1",
            "0.2",
            "0.3",
            "0.4",
            "0.5",
            "0.6",
            "0.7",
            "0.8",
            "0.9",
            "1"});
            this.cboPercentage.Location = new System.Drawing.Point(224, 115);
            this.cboPercentage.Name = "cboPercentage";
            this.cboPercentage.Size = new System.Drawing.Size(69, 21);
            this.cboPercentage.TabIndex = 14;
            this.cboPercentage.Text = "0.7";
            this.cboPercentage.Validating += new System.ComponentModel.CancelEventHandler(this.cboDoubleVal_Validating);
            // 
            // lblPercentage
            // 
            this.lblPercentage.AutoSize = true;
            this.lblPercentage.Location = new System.Drawing.Point(148, 119);
            this.lblPercentage.Name = "lblPercentage";
            this.lblPercentage.Size = new System.Drawing.Size(62, 13);
            this.lblPercentage.TabIndex = 13;
            this.lblPercentage.Text = "Percentage";
            // 
            // chkPCT
            // 
            this.chkPCT.AutoSize = true;
            this.chkPCT.Location = new System.Drawing.Point(246, 89);
            this.chkPCT.Name = "chkPCT";
            this.chkPCT.RightToLeft = System.Windows.Forms.RightToLeft.Yes;
            this.chkPCT.Size = new System.Drawing.Size(47, 17);
            this.chkPCT.TabIndex = 12;
            this.chkPCT.Text = "PCT";
            this.chkPCT.UseVisualStyleBackColor = true;
            // 
            // cboSimilarity
            // 
            this.cboSimilarity.FormattingEnabled = true;
            this.cboSimilarity.Items.AddRange(new object[] {
            "10.0",
            "20.0",
            "30.0",
            "40.0",
            "50.0"});
            this.cboSimilarity.Location = new System.Drawing.Point(60, 143);
            this.cboSimilarity.Name = "cboSimilarity";
            this.cboSimilarity.Size = new System.Drawing.Size(69, 21);
            this.cboSimilarity.TabIndex = 11;
            this.cboSimilarity.Text = "50.0";
            this.cboSimilarity.Validating += new System.ComponentModel.CancelEventHandler(this.cboDoubleVal_Validating);
            // 
            // lblSimilarity
            // 
            this.lblSimilarity.AutoSize = true;
            this.lblSimilarity.Location = new System.Drawing.Point(0, 147);
            this.lblSimilarity.Name = "lblSimilarity";
            this.lblSimilarity.Size = new System.Drawing.Size(47, 13);
            this.lblSimilarity.TabIndex = 10;
            this.lblSimilarity.Text = "Similarity";
            // 
            // cboThreshold
            // 
            this.cboThreshold.FormattingEnabled = true;
            this.cboThreshold.Items.AddRange(new object[] {
            "10.0",
            "20.0",
            "30.0",
            "40.0",
            "50.0"});
            this.cboThreshold.Location = new System.Drawing.Point(60, 115);
            this.cboThreshold.Name = "cboThreshold";
            this.cboThreshold.Size = new System.Drawing.Size(69, 21);
            this.cboThreshold.TabIndex = 9;
            this.cboThreshold.Text = "50.0";
            this.cboThreshold.Validating += new System.ComponentModel.CancelEventHandler(this.cboDoubleVal_Validating);
            // 
            // lblThreshold
            // 
            this.lblThreshold.AutoSize = true;
            this.lblThreshold.Location = new System.Drawing.Point(0, 119);
            this.lblThreshold.Name = "lblThreshold";
            this.lblThreshold.Size = new System.Drawing.Size(54, 13);
            this.lblThreshold.TabIndex = 8;
            this.lblThreshold.Text = "Threshold";
            // 
            // cboEntryLevel
            // 
            this.cboEntryLevel.FormattingEnabled = true;
            this.cboEntryLevel.Items.AddRange(new object[] {
            "1",
            "2",
            "3",
            "4",
            "5",
            "6",
            "7",
            "8"});
            this.cboEntryLevel.Location = new System.Drawing.Point(60, 87);
            this.cboEntryLevel.Name = "cboEntryLevel";
            this.cboEntryLevel.Size = new System.Drawing.Size(69, 21);
            this.cboEntryLevel.TabIndex = 7;
            this.cboEntryLevel.Text = "3";
            this.cboEntryLevel.Validating += new System.ComponentModel.CancelEventHandler(this.cboUIntVal_Validating);
            // 
            // lblEntryLevel
            // 
            this.lblEntryLevel.AutoSize = true;
            this.lblEntryLevel.Location = new System.Drawing.Point(0, 91);
            this.lblEntryLevel.Name = "lblEntryLevel";
            this.lblEntryLevel.Size = new System.Drawing.Size(56, 13);
            this.lblEntryLevel.TabIndex = 6;
            this.lblEntryLevel.Text = "Entry level";
            // 
            // rbWeightedGrayLevel
            // 
            this.rbWeightedGrayLevel.AutoSize = true;
            this.rbWeightedGrayLevel.Location = new System.Drawing.Point(148, 44);
            this.rbWeightedGrayLevel.Name = "rbWeightedGrayLevel";
            this.rbWeightedGrayLevel.Size = new System.Drawing.Size(162, 17);
            this.rbWeightedGrayLevel.TabIndex = 5;
            this.rbWeightedGrayLevel.Text = "Weighted gray level distance";
            this.rbWeightedGrayLevel.UseVisualStyleBackColor = true;
            this.rbWeightedGrayLevel.CheckedChanged += new System.EventHandler(this.rbHomogeneityTest_CheckedChanged);
            // 
            // rbLocalStd
            // 
            this.rbLocalStd.AutoSize = true;
            this.rbLocalStd.Location = new System.Drawing.Point(148, 22);
            this.rbLocalStd.Name = "rbLocalStd";
            this.rbLocalStd.Size = new System.Drawing.Size(148, 17);
            this.rbLocalStd.TabIndex = 4;
            this.rbLocalStd.Text = "Local std. vs. global mean";
            this.rbLocalStd.UseVisualStyleBackColor = true;
            this.rbLocalStd.CheckedChanged += new System.EventHandler(this.rbHomogeneityTest_CheckedChanged);
            // 
            // rbLocalMean
            // 
            this.rbLocalMean.AutoSize = true;
            this.rbLocalMean.Location = new System.Drawing.Point(148, 0);
            this.rbLocalMean.Name = "rbLocalMean";
            this.rbLocalMean.Size = new System.Drawing.Size(157, 17);
            this.rbLocalMean.TabIndex = 3;
            this.rbLocalMean.Text = "Local mean vs. global mean";
            this.rbLocalMean.UseVisualStyleBackColor = true;
            this.rbLocalMean.CheckedChanged += new System.EventHandler(this.rbHomogeneityTest_CheckedChanged);
            // 
            // rbHomogeneity
            // 
            this.rbHomogeneity.AutoSize = true;
            this.rbHomogeneity.Location = new System.Drawing.Point(5, 44);
            this.rbHomogeneity.Name = "rbHomogeneity";
            this.rbHomogeneity.Size = new System.Drawing.Size(124, 17);
            this.rbHomogeneity.TabIndex = 2;
            this.rbHomogeneity.Text = "Texture homogeneity";
            this.rbHomogeneity.UseVisualStyleBackColor = true;
            this.rbHomogeneity.CheckedChanged += new System.EventHandler(this.rbHomogeneityTest_CheckedChanged);
            // 
            // rbVariance
            // 
            this.rbVariance.AutoSize = true;
            this.rbVariance.Location = new System.Drawing.Point(5, 22);
            this.rbVariance.Name = "rbVariance";
            this.rbVariance.Size = new System.Drawing.Size(67, 17);
            this.rbVariance.TabIndex = 1;
            this.rbVariance.Text = "Variance";
            this.rbVariance.UseVisualStyleBackColor = true;
            this.rbVariance.CheckedChanged += new System.EventHandler(this.rbHomogeneityTest_CheckedChanged);
            // 
            // rbPureUniform
            // 
            this.rbPureUniform.AutoSize = true;
            this.rbPureUniform.Checked = true;
            this.rbPureUniform.Location = new System.Drawing.Point(5, 0);
            this.rbPureUniform.Name = "rbPureUniform";
            this.rbPureUniform.Size = new System.Drawing.Size(94, 17);
            this.rbPureUniform.TabIndex = 0;
            this.rbPureUniform.TabStop = true;
            this.rbPureUniform.Text = "Pure uniformity";
            this.rbPureUniform.UseVisualStyleBackColor = true;
            this.rbPureUniform.CheckedChanged += new System.EventHandler(this.rbHomogeneityTest_CheckedChanged);
            // 
            // pnlGrayLevelQuant
            // 
            this.pnlGrayLevelQuant.Controls.Add(this.cboWatershedThreshold);
            this.pnlGrayLevelQuant.Controls.Add(this.lblWatershedThreshold);
            this.pnlGrayLevelQuant.Controls.Add(this.chkMergeResult);
            this.pnlGrayLevelQuant.Controls.Add(this.cboSCTBAxis);
            this.pnlGrayLevelQuant.Controls.Add(this.lblSCTBAxis);
            this.pnlGrayLevelQuant.Controls.Add(this.cboSCTAAxis);
            this.pnlGrayLevelQuant.Controls.Add(this.lblSCTAAxis);
            this.pnlGrayLevelQuant.Controls.Add(this.cboNumColors);
            this.pnlGrayLevelQuant.Controls.Add(this.lblNumColors);
            this.pnlGrayLevelQuant.Controls.Add(this.cboFuzzyCVariance);
            this.pnlGrayLevelQuant.Controls.Add(this.lblFuzzyCVariance);
            this.pnlGrayLevelQuant.Controls.Add(this.cboLimit);
            this.pnlGrayLevelQuant.Controls.Add(this.lblLimit);
            this.pnlGrayLevelQuant.Controls.Add(this.cboQuantMethod);
            this.pnlGrayLevelQuant.Controls.Add(this.lblQuantMethod);
            this.pnlGrayLevelQuant.Controls.Add(this.cboNumGrayLevels);
            this.pnlGrayLevelQuant.Controls.Add(this.lblNumGrayLevels);
            this.pnlGrayLevelQuant.Location = new System.Drawing.Point(178, 13);
            this.pnlGrayLevelQuant.Name = "pnlGrayLevelQuant";
            this.pnlGrayLevelQuant.Size = new System.Drawing.Size(294, 217);
            this.pnlGrayLevelQuant.TabIndex = 0;
            // 
            // cboWatershedThreshold
            // 
            this.cboWatershedThreshold.FormattingEnabled = true;
            this.cboWatershedThreshold.Items.AddRange(new object[] {
            "0.1",
            "0.2",
            "0.3",
            "0.4",
            "0.5",
            "0.6",
            "0.7",
            "0.8",
            "0.9"});
            this.cboWatershedThreshold.Location = new System.Drawing.Point(177, 196);
            this.cboWatershedThreshold.Name = "cboWatershedThreshold";
            this.cboWatershedThreshold.Size = new System.Drawing.Size(70, 21);
            this.cboWatershedThreshold.TabIndex = 16;
            this.cboWatershedThreshold.Text = "0.7";
            this.cboWatershedThreshold.Validating += new System.ComponentModel.CancelEventHandler(this.cboDoubleVal_Validating);
            // 
            // lblWatershedThreshold
            // 
            this.lblWatershedThreshold.AutoSize = true;
            this.lblWatershedThreshold.Location = new System.Drawing.Point(118, 200);
            this.lblWatershedThreshold.Name = "lblWatershedThreshold";
            this.lblWatershedThreshold.Size = new System.Drawing.Size(57, 13);
            this.lblWatershedThreshold.TabIndex = 15;
            this.lblWatershedThreshold.Text = "Threshold:";
            // 
            // chkMergeResult
            // 
            this.chkMergeResult.AutoSize = true;
            this.chkMergeResult.Location = new System.Drawing.Point(25, 198);
            this.chkMergeResult.Name = "chkMergeResult";
            this.chkMergeResult.Size = new System.Drawing.Size(84, 17);
            this.chkMergeResult.TabIndex = 14;
            this.chkMergeResult.Text = "Merge result";
            this.chkMergeResult.UseVisualStyleBackColor = true;
            this.chkMergeResult.CheckedChanged += new System.EventHandler(this.chkMergeResult_CheckedChanged);
            // 
            // cboSCTBAxis
            // 
            this.cboSCTBAxis.FormattingEnabled = true;
            this.cboSCTBAxis.Items.AddRange(new object[] {
            "2",
            "3",
            "4",
            "8",
            "16",
            "32",
            "64",
            "100"});
            this.cboSCTBAxis.Location = new System.Drawing.Point(177, 168);
            this.cboSCTBAxis.Name = "cboSCTBAxis";
            this.cboSCTBAxis.Size = new System.Drawing.Size(70, 21);
            this.cboSCTBAxis.TabIndex = 13;
            this.cboSCTBAxis.Text = "2";
            this.cboSCTBAxis.Validating += new System.ComponentModel.CancelEventHandler(this.cboUIntVal_Validating);
            // 
            // lblSCTBAxis
            // 
            this.lblSCTBAxis.AutoSize = true;
            this.lblSCTBAxis.Location = new System.Drawing.Point(137, 172);
            this.lblSCTBAxis.Name = "lblSCTBAxis";
            this.lblSCTBAxis.Size = new System.Drawing.Size(38, 13);
            this.lblSCTBAxis.TabIndex = 12;
            this.lblSCTBAxis.Text = "B axis:";
            // 
            // cboSCTAAxis
            // 
            this.cboSCTAAxis.FormattingEnabled = true;
            this.cboSCTAAxis.Items.AddRange(new object[] {
            "2",
            "3",
            "4",
            "8",
            "16",
            "32",
            "64",
            "100"});
            this.cboSCTAAxis.Location = new System.Drawing.Point(177, 140);
            this.cboSCTAAxis.Name = "cboSCTAAxis";
            this.cboSCTAAxis.Size = new System.Drawing.Size(70, 21);
            this.cboSCTAAxis.TabIndex = 11;
            this.cboSCTAAxis.Text = "2";
            this.cboSCTAAxis.Validating += new System.ComponentModel.CancelEventHandler(this.cboUIntVal_Validating);
            // 
            // lblSCTAAxis
            // 
            this.lblSCTAAxis.AutoSize = true;
            this.lblSCTAAxis.Location = new System.Drawing.Point(19, 144);
            this.lblSCTAAxis.Name = "lblSCTAAxis";
            this.lblSCTAAxis.Size = new System.Drawing.Size(156, 13);
            this.lblSCTAAxis.TabIndex = 10;
            this.lblSCTAAxis.Text = "Number of colors along   A axis:";
            // 
            // cboNumColors
            // 
            this.cboNumColors.FormattingEnabled = true;
            this.cboNumColors.Items.AddRange(new object[] {
            "2",
            "4",
            "8",
            "16",
            "32",
            "64",
            "128",
            "256",
            "512"});
            this.cboNumColors.Location = new System.Drawing.Point(177, 112);
            this.cboNumColors.Name = "cboNumColors";
            this.cboNumColors.Size = new System.Drawing.Size(117, 21);
            this.cboNumColors.TabIndex = 9;
            this.cboNumColors.Text = "32";
            this.cboNumColors.Validating += new System.ComponentModel.CancelEventHandler(this.cboUIntVal_Validating);
            // 
            // lblNumColors
            // 
            this.lblNumColors.AutoSize = true;
            this.lblNumColors.Location = new System.Drawing.Point(0, 116);
            this.lblNumColors.Name = "lblNumColors";
            this.lblNumColors.Size = new System.Drawing.Size(175, 13);
            this.lblNumColors.TabIndex = 8;
            this.lblNumColors.Text = "Number of desired colors (2 - 1000):";
            // 
            // cboFuzzyCVariance
            // 
            this.cboFuzzyCVariance.FormattingEnabled = true;
            this.cboFuzzyCVariance.Items.AddRange(new object[] {
            "0.2",
            "0.5",
            "1",
            "2.0",
            "3.0",
            "4.0",
            "6.0",
            "10.0",
            "12.0",
            "15.0",
            "20.0"});
            this.cboFuzzyCVariance.Location = new System.Drawing.Point(185, 84);
            this.cboFuzzyCVariance.Name = "cboFuzzyCVariance";
            this.cboFuzzyCVariance.Size = new System.Drawing.Size(90, 21);
            this.cboFuzzyCVariance.TabIndex = 7;
            this.cboFuzzyCVariance.Text = "3.0";
            this.cboFuzzyCVariance.Validating += new System.ComponentModel.CancelEventHandler(this.cboDoubleVal_Validating);
            // 
            // lblFuzzyCVariance
            // 
            this.lblFuzzyCVariance.AutoSize = true;
            this.lblFuzzyCVariance.Location = new System.Drawing.Point(0, 88);
            this.lblFuzzyCVariance.Name = "lblFuzzyCVariance";
            this.lblFuzzyCVariance.Size = new System.Drawing.Size(184, 13);
            this.lblFuzzyCVariance.TabIndex = 6;
            this.lblFuzzyCVariance.Text = "Gaussian kernel variance (0.1 - 20.0):";
            // 
            // cboLimit
            // 
            this.cboLimit.FormattingEnabled = true;
            this.cboLimit.Items.AddRange(new object[] {
            "1.0",
            "2.0",
            "3.0",
            "4.0",
            "5.0",
            "6.0",
            "7.0",
            "8.0",
            "9.0",
            "10.0"});
            this.cboLimit.Location = new System.Drawing.Point(177, 56);
            this.cboLimit.Name = "cboLimit";
            this.cboLimit.Size = new System.Drawing.Size(69, 21);
            this.cboLimit.TabIndex = 5;
            this.cboLimit.Text = "10.0";
            this.cboLimit.Validating += new System.ComponentModel.CancelEventHandler(this.cboFloatVal_Validating);
            // 
            // lblLimit
            // 
            this.lblLimit.AutoSize = true;
            this.lblLimit.Location = new System.Drawing.Point(144, 60);
            this.lblLimit.Name = "lblLimit";
            this.lblLimit.Size = new System.Drawing.Size(31, 13);
            this.lblLimit.TabIndex = 4;
            this.lblLimit.Text = "Limit:";
            // 
            // cboQuantMethod
            // 
            this.cboQuantMethod.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cboQuantMethod.FormattingEnabled = true;
            this.cboQuantMethod.Items.AddRange(new object[] {
            "Standard",
            "IGS"});
            this.cboQuantMethod.Location = new System.Drawing.Point(177, 28);
            this.cboQuantMethod.Name = "cboQuantMethod";
            this.cboQuantMethod.Size = new System.Drawing.Size(70, 21);
            this.cboQuantMethod.TabIndex = 3;
            // 
            // lblQuantMethod
            // 
            this.lblQuantMethod.AutoSize = true;
            this.lblQuantMethod.Location = new System.Drawing.Point(67, 32);
            this.lblQuantMethod.Name = "lblQuantMethod";
            this.lblQuantMethod.Size = new System.Drawing.Size(108, 13);
            this.lblQuantMethod.TabIndex = 2;
            this.lblQuantMethod.Text = "Quantization Method:";
            // 
            // cboNumGrayLevels
            // 
            this.cboNumGrayLevels.FormattingEnabled = true;
            this.cboNumGrayLevels.Items.AddRange(new object[] {
            "2",
            "4",
            "8",
            "16",
            "32",
            "64",
            "128"});
            this.cboNumGrayLevels.Location = new System.Drawing.Point(177, 0);
            this.cboNumGrayLevels.Name = "cboNumGrayLevels";
            this.cboNumGrayLevels.Size = new System.Drawing.Size(70, 21);
            this.cboNumGrayLevels.TabIndex = 1;
            this.cboNumGrayLevels.Text = "8";
            this.cboNumGrayLevels.Validating += new System.ComponentModel.CancelEventHandler(this.cboUIntVal_Validating);
            // 
            // lblNumGrayLevels
            // 
            this.lblNumGrayLevels.AutoSize = true;
            this.lblNumGrayLevels.Location = new System.Drawing.Point(63, 4);
            this.lblNumGrayLevels.Name = "lblNumGrayLevels";
            this.lblNumGrayLevels.Size = new System.Drawing.Size(112, 13);
            this.lblNumGrayLevels.TabIndex = 0;
            this.lblNumGrayLevels.Text = "Number of gray levels:";
            // 
            // pnlHistThresh
            // 
            this.pnlHistThresh.Controls.Add(this.lblHistTore);
            this.pnlHistThresh.Controls.Add(this.cbHistThresh);
            this.pnlHistThresh.Controls.Add(this.lblHistThresh);
            this.pnlHistThresh.Controls.Add(this.rbHistThreshBands);
            this.pnlHistThresh.Controls.Add(this.rbHistThreshPCT);
            this.pnlHistThresh.Controls.Add(this.rbHistThreshLum);
            this.pnlHistThresh.Location = new System.Drawing.Point(178, 70);
            this.pnlHistThresh.Name = "pnlHistThresh";
            this.pnlHistThresh.Size = new System.Drawing.Size(370, 100);
            this.pnlHistThresh.TabIndex = 17;
            // 
            // lblHistTore
            // 
            this.lblHistTore.AutoSize = true;
            this.lblHistTore.Location = new System.Drawing.Point(0, 26);
            this.lblHistTore.Name = "lblHistTore";
            this.lblHistTore.Size = new System.Drawing.Size(98, 13);
            this.lblHistTore.TabIndex = 30;
            this.lblHistTore.Text = "Standard Deviation";
            // 
            // cbHistThresh
            // 
            this.cbHistThresh.FormattingEnabled = true;
            this.cbHistThresh.Items.AddRange(new object[] {
            "0.25",
            "0.5",
            "0.75",
            "1",
            "1.5",
            "2",
            "3",
            "4",
            "5",
            "6"});
            this.cbHistThresh.Location = new System.Drawing.Point(100, 26);
            this.cbHistThresh.Name = "cbHistThresh";
            this.cbHistThresh.Size = new System.Drawing.Size(69, 21);
            this.cbHistThresh.Sorted = true;
            this.cbHistThresh.TabIndex = 29;
            this.cbHistThresh.Text = "2";
            // 
            // lblHistThresh
            // 
            this.lblHistThresh.AutoSize = true;
            this.lblHistThresh.Location = new System.Drawing.Point(0, 5);
            this.lblHistThresh.Name = "lblHistThresh";
            this.lblHistThresh.Size = new System.Drawing.Size(73, 13);
            this.lblHistThresh.TabIndex = 18;
            this.lblHistThresh.Text = "Color Method:";
            // 
            // rbHistThreshBands
            // 
            this.rbHistThreshBands.AutoSize = true;
            this.rbHistThreshBands.Location = new System.Drawing.Point(80, 3);
            this.rbHistThreshBands.Name = "rbHistThreshBands";
            this.rbHistThreshBands.Size = new System.Drawing.Size(69, 17);
            this.rbHistThreshBands.TabIndex = 26;
            this.rbHistThreshBands.TabStop = true;
            this.rbHistThreshBands.Text = "All Bands";
            this.rbHistThreshBands.UseVisualStyleBackColor = true;
            // 
            // rbHistThreshPCT
            // 
            this.rbHistThreshPCT.AutoSize = true;
            this.rbHistThreshPCT.Location = new System.Drawing.Point(160, 3);
            this.rbHistThreshPCT.Name = "rbHistThreshPCT";
            this.rbHistThreshPCT.Size = new System.Drawing.Size(96, 17);
            this.rbHistThreshPCT.TabIndex = 28;
            this.rbHistThreshPCT.TabStop = true;
            this.rbHistThreshPCT.Text = "PCT Transform";
            this.rbHistThreshPCT.UseVisualStyleBackColor = true;
            // 
            // rbHistThreshLum
            // 
            this.rbHistThreshLum.AutoSize = true;
            this.rbHistThreshLum.Location = new System.Drawing.Point(265, 3);
            this.rbHistThreshLum.Name = "rbHistThreshLum";
            this.rbHistThreshLum.Size = new System.Drawing.Size(77, 17);
            this.rbHistThreshLum.TabIndex = 27;
            this.rbHistThreshLum.TabStop = true;
            this.rbHistThreshLum.Text = "Luminance";
            this.rbHistThreshLum.UseVisualStyleBackColor = true;
            // 
            // grpMorpho
            // 
            this.grpMorpho.Controls.Add(this.pnlFilterSize);
            this.grpMorpho.Controls.Add(this.pnlMorphological);
            this.grpMorpho.Controls.Add(this.lblBinaryImages);
            this.grpMorpho.Controls.Add(this.lblAllImages);
            this.grpMorpho.Controls.Add(this.pnlMorphIterative);
            this.grpMorpho.Location = new System.Drawing.Point(12, 371);
            this.grpMorpho.Name = "grpMorpho";
            this.grpMorpho.Size = new System.Drawing.Size(628, 144);
            this.grpMorpho.TabIndex = 21;
            this.grpMorpho.TabStop = false;
            this.grpMorpho.Text = "Morphological Filters";
            // 
            // pnlFilterSize
            // 
            this.pnlFilterSize.Controls.Add(this.cboSkeletonMethod);
            this.pnlFilterSize.Controls.Add(this.lblSkeletonMethod);
            this.pnlFilterSize.Controls.Add(this.cboSkeletonConnect);
            this.pnlFilterSize.Controls.Add(this.lblSkeletonConnect);
            this.pnlFilterSize.Controls.Add(this.cboSkeletonIterations);
            this.pnlFilterSize.Controls.Add(this.lblSkeletonIterations);
            this.pnlFilterSize.Controls.Add(this.rbFilterSize9x9);
            this.pnlFilterSize.Controls.Add(this.rbFilterSize7x7);
            this.pnlFilterSize.Controls.Add(this.rbFilterSize5x5);
            this.pnlFilterSize.Controls.Add(this.rbFilterSize3x3);
            this.pnlFilterSize.Controls.Add(this.lblFilterSize);
            this.pnlFilterSize.Location = new System.Drawing.Point(26, 60);
            this.pnlFilterSize.Name = "pnlFilterSize";
            this.pnlFilterSize.Size = new System.Drawing.Size(500, 85);
            this.pnlFilterSize.TabIndex = 4;
            // 
            // cboSkeletonMethod
            // 
            this.cboSkeletonMethod.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cboSkeletonMethod.FormattingEnabled = true;
            this.cboSkeletonMethod.Items.AddRange(new object[] {
            "AND Method",
            "Sequential Method"});
            this.cboSkeletonMethod.Location = new System.Drawing.Point(98, 58);
            this.cboSkeletonMethod.Name = "cboSkeletonMethod";
            this.cboSkeletonMethod.Size = new System.Drawing.Size(119, 21);
            this.cboSkeletonMethod.TabIndex = 10;
            // 
            // lblSkeletonMethod
            // 
            this.lblSkeletonMethod.AutoSize = true;
            this.lblSkeletonMethod.Location = new System.Drawing.Point(3, 61);
            this.lblSkeletonMethod.Name = "lblSkeletonMethod";
            this.lblSkeletonMethod.Size = new System.Drawing.Size(43, 13);
            this.lblSkeletonMethod.TabIndex = 9;
            this.lblSkeletonMethod.Text = "Method";
            // 
            // cboSkeletonConnect
            // 
            this.cboSkeletonConnect.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cboSkeletonConnect.FormattingEnabled = true;
            this.cboSkeletonConnect.Items.AddRange(new object[] {
            "4-masks (horiz/vert)",
            "4 diag masks",
            "8-masks (horiz/vert/diag)"});
            this.cboSkeletonConnect.Location = new System.Drawing.Point(340, 30);
            this.cboSkeletonConnect.Name = "cboSkeletonConnect";
            this.cboSkeletonConnect.Size = new System.Drawing.Size(150, 21);
            this.cboSkeletonConnect.TabIndex = 8;
            this.cboSkeletonConnect.SelectedIndexChanged += new System.EventHandler(this.cboSkeletonConnect_SelectedIndexChanged);
            // 
            // lblSkeletonConnect
            // 
            this.lblSkeletonConnect.AutoSize = true;
            this.lblSkeletonConnect.Location = new System.Drawing.Point(264, 33);
            this.lblSkeletonConnect.Name = "lblSkeletonConnect";
            this.lblSkeletonConnect.Size = new System.Drawing.Size(65, 13);
            this.lblSkeletonConnect.TabIndex = 7;
            this.lblSkeletonConnect.Text = "Connectivity";
            // 
            // cboSkeletonIterations
            // 
            this.cboSkeletonIterations.FormattingEnabled = true;
            this.cboSkeletonIterations.Items.AddRange(new object[] {
            "1",
            "2",
            "5",
            "10",
            "20",
            "50",
            "80",
            "100",
            "200"});
            this.cboSkeletonIterations.Location = new System.Drawing.Point(98, 30);
            this.cboSkeletonIterations.Name = "cboSkeletonIterations";
            this.cboSkeletonIterations.Size = new System.Drawing.Size(119, 21);
            this.cboSkeletonIterations.TabIndex = 6;
            this.cboSkeletonIterations.Text = "2";
            this.cboSkeletonIterations.Validating += new System.ComponentModel.CancelEventHandler(this.cboUIntVal_Validating);
            // 
            // lblSkeletonIterations
            // 
            this.lblSkeletonIterations.AutoSize = true;
            this.lblSkeletonIterations.Location = new System.Drawing.Point(0, 25);
            this.lblSkeletonIterations.Name = "lblSkeletonIterations";
            this.lblSkeletonIterations.Size = new System.Drawing.Size(61, 26);
            this.lblSkeletonIterations.TabIndex = 5;
            this.lblSkeletonIterations.Text = "Number Of \r\nIterations";
            // 
            // rbFilterSize9x9
            // 
            this.rbFilterSize9x9.AutoSize = true;
            this.rbFilterSize9x9.Location = new System.Drawing.Point(385, 0);
            this.rbFilterSize9x9.Name = "rbFilterSize9x9";
            this.rbFilterSize9x9.Size = new System.Drawing.Size(42, 17);
            this.rbFilterSize9x9.TabIndex = 4;
            this.rbFilterSize9x9.Text = "9x9\r\n";
            this.rbFilterSize9x9.UseVisualStyleBackColor = true;
            this.rbFilterSize9x9.CheckedChanged += new System.EventHandler(this.rbFilterSize_CheckedChanged);
            // 
            // rbFilterSize7x7
            // 
            this.rbFilterSize7x7.AutoSize = true;
            this.rbFilterSize7x7.Location = new System.Drawing.Point(299, 0);
            this.rbFilterSize7x7.Name = "rbFilterSize7x7";
            this.rbFilterSize7x7.Size = new System.Drawing.Size(42, 17);
            this.rbFilterSize7x7.TabIndex = 3;
            this.rbFilterSize7x7.Text = "7x7";
            this.rbFilterSize7x7.UseVisualStyleBackColor = true;
            this.rbFilterSize7x7.CheckedChanged += new System.EventHandler(this.rbFilterSize_CheckedChanged);
            // 
            // rbFilterSize5x5
            // 
            this.rbFilterSize5x5.AutoSize = true;
            this.rbFilterSize5x5.Location = new System.Drawing.Point(205, 0);
            this.rbFilterSize5x5.Name = "rbFilterSize5x5";
            this.rbFilterSize5x5.Size = new System.Drawing.Size(42, 17);
            this.rbFilterSize5x5.TabIndex = 2;
            this.rbFilterSize5x5.Text = "5x5";
            this.rbFilterSize5x5.UseVisualStyleBackColor = true;
            this.rbFilterSize5x5.CheckedChanged += new System.EventHandler(this.rbFilterSize_CheckedChanged);
            // 
            // rbFilterSize3x3
            // 
            this.rbFilterSize3x3.AutoSize = true;
            this.rbFilterSize3x3.Checked = true;
            this.rbFilterSize3x3.Location = new System.Drawing.Point(98, 0);
            this.rbFilterSize3x3.Name = "rbFilterSize3x3";
            this.rbFilterSize3x3.Size = new System.Drawing.Size(42, 17);
            this.rbFilterSize3x3.TabIndex = 1;
            this.rbFilterSize3x3.TabStop = true;
            this.rbFilterSize3x3.Text = "3x3";
            this.rbFilterSize3x3.UseVisualStyleBackColor = true;
            this.rbFilterSize3x3.CheckedChanged += new System.EventHandler(this.rbFilterSize_CheckedChanged);
            // 
            // lblFilterSize
            // 
            this.lblFilterSize.AutoSize = true;
            this.lblFilterSize.Location = new System.Drawing.Point(0, 2);
            this.lblFilterSize.Name = "lblFilterSize";
            this.lblFilterSize.Size = new System.Drawing.Size(50, 13);
            this.lblFilterSize.TabIndex = 0;
            this.lblFilterSize.Text = "Filter size";
            // 
            // pnlMorphological
            // 
            this.pnlMorphological.Controls.Add(this.lblKernelType);
            this.pnlMorphological.Controls.Add(this.cboKernelHeight);
            this.pnlMorphological.Controls.Add(this.lblKernelHeight);
            this.pnlMorphological.Controls.Add(this.cboKernelWidth);
            this.pnlMorphological.Controls.Add(this.lblKernelWidth);
            this.pnlMorphological.Controls.Add(this.cboKernelSize);
            this.pnlMorphological.Controls.Add(this.lblKernelSize);
            this.pnlMorphological.Controls.Add(this.cboKernelType);
            this.pnlMorphological.Location = new System.Drawing.Point(26, 64);
            this.pnlMorphological.Name = "pnlMorphological";
            this.pnlMorphological.Size = new System.Drawing.Size(485, 26);
            this.pnlMorphological.TabIndex = 2;
            // 
            // lblKernelType
            // 
            this.lblKernelType.AutoSize = true;
            this.lblKernelType.Location = new System.Drawing.Point(0, 0);
            this.lblKernelType.Name = "lblKernelType";
            this.lblKernelType.Size = new System.Drawing.Size(58, 26);
            this.lblKernelType.TabIndex = 0;
            this.lblKernelType.Text = "Structuring\r\nElement";
            // 
            // cboKernelHeight
            // 
            this.cboKernelHeight.FormattingEnabled = true;
            this.cboKernelHeight.Items.AddRange(new object[] {
            "1",
            "3",
            "5",
            "7",
            "9",
            "11",
            "13"});
            this.cboKernelHeight.Location = new System.Drawing.Point(416, 3);
            this.cboKernelHeight.Name = "cboKernelHeight";
            this.cboKernelHeight.Size = new System.Drawing.Size(59, 21);
            this.cboKernelHeight.TabIndex = 7;
            this.cboKernelHeight.Text = "3";
            this.cboKernelHeight.Validating += new System.ComponentModel.CancelEventHandler(this.cboUIntVal_Validating);
            // 
            // lblKernelHeight
            // 
            this.lblKernelHeight.AutoSize = true;
            this.lblKernelHeight.Location = new System.Drawing.Point(360, 8);
            this.lblKernelHeight.Name = "lblKernelHeight";
            this.lblKernelHeight.Size = new System.Drawing.Size(41, 13);
            this.lblKernelHeight.TabIndex = 6;
            this.lblKernelHeight.Text = "Height:";
            // 
            // cboKernelWidth
            // 
            this.cboKernelWidth.FormattingEnabled = true;
            this.cboKernelWidth.Items.AddRange(new object[] {
            "1",
            "3",
            "5",
            "7",
            "9",
            "11",
            "13"});
            this.cboKernelWidth.Location = new System.Drawing.Point(300, 4);
            this.cboKernelWidth.Name = "cboKernelWidth";
            this.cboKernelWidth.Size = new System.Drawing.Size(59, 21);
            this.cboKernelWidth.TabIndex = 5;
            this.cboKernelWidth.Text = "3";
            this.cboKernelWidth.Validating += new System.ComponentModel.CancelEventHandler(this.cboUIntVal_Validating);
            // 
            // lblKernelWidth
            // 
            this.lblKernelWidth.AutoSize = true;
            this.lblKernelWidth.Location = new System.Drawing.Point(241, 7);
            this.lblKernelWidth.Name = "lblKernelWidth";
            this.lblKernelWidth.Size = new System.Drawing.Size(38, 13);
            this.lblKernelWidth.TabIndex = 4;
            this.lblKernelWidth.Text = "Width:";
            // 
            // cboKernelSize
            // 
            this.cboKernelSize.FormattingEnabled = true;
            this.cboKernelSize.Items.AddRange(new object[] {
            "3",
            "5",
            "7",
            "9",
            "11",
            "13"});
            this.cboKernelSize.Location = new System.Drawing.Point(170, 3);
            this.cboKernelSize.Name = "cboKernelSize";
            this.cboKernelSize.Size = new System.Drawing.Size(59, 21);
            this.cboKernelSize.TabIndex = 3;
            this.cboKernelSize.Text = "3";
            this.cboKernelSize.TextChanged += new System.EventHandler(this.cboKernelSize_TextChanged);
            this.cboKernelSize.Validating += new System.ComponentModel.CancelEventHandler(this.cboUIntVal_Validating);
            // 
            // lblKernelSize
            // 
            this.lblKernelSize.AutoSize = true;
            this.lblKernelSize.Location = new System.Drawing.Point(140, 7);
            this.lblKernelSize.Name = "lblKernelSize";
            this.lblKernelSize.Size = new System.Drawing.Size(30, 13);
            this.lblKernelSize.TabIndex = 2;
            this.lblKernelSize.Text = "Size:";
            // 
            // cboKernelType
            // 
            this.cboKernelType.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cboKernelType.FormattingEnabled = true;
            this.cboKernelType.Items.AddRange(new object[] {
            "circle",
            "square",
            "rectangle",
            "cross",
            "custom"});
            this.cboKernelType.Location = new System.Drawing.Point(61, 3);
            this.cboKernelType.Name = "cboKernelType";
            this.cboKernelType.Size = new System.Drawing.Size(69, 21);
            this.cboKernelType.TabIndex = 1;
            this.cboKernelType.SelectedIndexChanged += new System.EventHandler(this.cboKernelType_SelectedIndexChanged);
            // 
            // lblBinaryImages
            // 
            this.lblBinaryImages.AutoSize = true;
            this.lblBinaryImages.Location = new System.Drawing.Point(26, 39);
            this.lblBinaryImages.Name = "lblBinaryImages";
            this.lblBinaryImages.Size = new System.Drawing.Size(94, 13);
            this.lblBinaryImages.TabIndex = 1;
            this.lblBinaryImages.Text = "BINARY IMAGES:";
            // 
            // lblAllImages
            // 
            this.lblAllImages.AutoSize = true;
            this.lblAllImages.Location = new System.Drawing.Point(26, 20);
            this.lblAllImages.Name = "lblAllImages";
            this.lblAllImages.Size = new System.Drawing.Size(73, 13);
            this.lblAllImages.TabIndex = 0;
            this.lblAllImages.Text = "ALL IMAGES:";
            // 
            // pnlMorphIterative
            // 
            this.pnlMorphIterative.Controls.Add(this.chkSurround14);
            this.pnlMorphIterative.Controls.Add(this.chkSurround13);
            this.pnlMorphIterative.Controls.Add(this.chkSurround12);
            this.pnlMorphIterative.Controls.Add(this.chkSurround11);
            this.pnlMorphIterative.Controls.Add(this.chkSurround10);
            this.pnlMorphIterative.Controls.Add(this.chkSurround9);
            this.pnlMorphIterative.Controls.Add(this.chkSurround8);
            this.pnlMorphIterative.Controls.Add(this.chkSurround7);
            this.pnlMorphIterative.Controls.Add(this.chkSurround6);
            this.pnlMorphIterative.Controls.Add(this.chkSurround5);
            this.pnlMorphIterative.Controls.Add(this.chkSurround4);
            this.pnlMorphIterative.Controls.Add(this.chkSurround3);
            this.pnlMorphIterative.Controls.Add(this.chkSurround2);
            this.pnlMorphIterative.Controls.Add(this.chkSurround1);
            this.pnlMorphIterative.Controls.Add(this.btnViewSurrounds);
            this.pnlMorphIterative.Controls.Add(this.cboSubFields);
            this.pnlMorphIterative.Controls.Add(this.lblSubFields);
            this.pnlMorphIterative.Controls.Add(this.cboMorphIterations);
            this.pnlMorphIterative.Controls.Add(this.lblMorphIterations);
            this.pnlMorphIterative.Controls.Add(this.cboBoolFunc);
            this.pnlMorphIterative.Controls.Add(this.lblBoolFunc);
            this.pnlMorphIterative.Controls.Add(this.chkRotate);
            this.pnlMorphIterative.Location = new System.Drawing.Point(26, 64);
            this.pnlMorphIterative.Name = "pnlMorphIterative";
            this.pnlMorphIterative.Size = new System.Drawing.Size(472, 79);
            this.pnlMorphIterative.TabIndex = 3;
            // 
            // chkSurround14
            // 
            this.chkSurround14.AutoSize = true;
            this.chkSurround14.Location = new System.Drawing.Point(423, 62);
            this.chkSurround14.Name = "chkSurround14";
            this.chkSurround14.Size = new System.Drawing.Size(38, 17);
            this.chkSurround14.TabIndex = 21;
            this.chkSurround14.Text = "14";
            this.chkSurround14.UseVisualStyleBackColor = true;
            // 
            // chkSurround13
            // 
            this.chkSurround13.AutoSize = true;
            this.chkSurround13.Location = new System.Drawing.Point(369, 62);
            this.chkSurround13.Name = "chkSurround13";
            this.chkSurround13.Size = new System.Drawing.Size(38, 17);
            this.chkSurround13.TabIndex = 20;
            this.chkSurround13.Text = "13";
            this.chkSurround13.UseVisualStyleBackColor = true;
            // 
            // chkSurround12
            // 
            this.chkSurround12.AutoSize = true;
            this.chkSurround12.Location = new System.Drawing.Point(315, 62);
            this.chkSurround12.Name = "chkSurround12";
            this.chkSurround12.Size = new System.Drawing.Size(38, 17);
            this.chkSurround12.TabIndex = 19;
            this.chkSurround12.Text = "12";
            this.chkSurround12.UseVisualStyleBackColor = true;
            // 
            // chkSurround11
            // 
            this.chkSurround11.AutoSize = true;
            this.chkSurround11.Location = new System.Drawing.Point(261, 62);
            this.chkSurround11.Name = "chkSurround11";
            this.chkSurround11.Size = new System.Drawing.Size(38, 17);
            this.chkSurround11.TabIndex = 18;
            this.chkSurround11.Text = "11";
            this.chkSurround11.UseVisualStyleBackColor = true;
            // 
            // chkSurround10
            // 
            this.chkSurround10.AutoSize = true;
            this.chkSurround10.Location = new System.Drawing.Point(207, 62);
            this.chkSurround10.Name = "chkSurround10";
            this.chkSurround10.Size = new System.Drawing.Size(38, 17);
            this.chkSurround10.TabIndex = 17;
            this.chkSurround10.Text = "10";
            this.chkSurround10.UseVisualStyleBackColor = true;
            // 
            // chkSurround9
            // 
            this.chkSurround9.AutoSize = true;
            this.chkSurround9.Location = new System.Drawing.Point(159, 62);
            this.chkSurround9.Name = "chkSurround9";
            this.chkSurround9.Size = new System.Drawing.Size(32, 17);
            this.chkSurround9.TabIndex = 16;
            this.chkSurround9.Text = "9";
            this.chkSurround9.UseVisualStyleBackColor = true;
            // 
            // chkSurround8
            // 
            this.chkSurround8.AutoSize = true;
            this.chkSurround8.Location = new System.Drawing.Point(111, 62);
            this.chkSurround8.Name = "chkSurround8";
            this.chkSurround8.Size = new System.Drawing.Size(32, 17);
            this.chkSurround8.TabIndex = 15;
            this.chkSurround8.Text = "8";
            this.chkSurround8.UseVisualStyleBackColor = true;
            // 
            // chkSurround7
            // 
            this.chkSurround7.AutoSize = true;
            this.chkSurround7.Checked = true;
            this.chkSurround7.CheckState = System.Windows.Forms.CheckState.Checked;
            this.chkSurround7.Location = new System.Drawing.Point(423, 39);
            this.chkSurround7.Name = "chkSurround7";
            this.chkSurround7.Size = new System.Drawing.Size(32, 17);
            this.chkSurround7.TabIndex = 14;
            this.chkSurround7.Text = "7";
            this.chkSurround7.UseVisualStyleBackColor = true;
            // 
            // chkSurround6
            // 
            this.chkSurround6.AutoSize = true;
            this.chkSurround6.Location = new System.Drawing.Point(369, 39);
            this.chkSurround6.Name = "chkSurround6";
            this.chkSurround6.Size = new System.Drawing.Size(32, 17);
            this.chkSurround6.TabIndex = 13;
            this.chkSurround6.Text = "6";
            this.chkSurround6.UseVisualStyleBackColor = true;
            // 
            // chkSurround5
            // 
            this.chkSurround5.AutoSize = true;
            this.chkSurround5.Location = new System.Drawing.Point(315, 39);
            this.chkSurround5.Name = "chkSurround5";
            this.chkSurround5.Size = new System.Drawing.Size(32, 17);
            this.chkSurround5.TabIndex = 12;
            this.chkSurround5.Text = "5";
            this.chkSurround5.UseVisualStyleBackColor = true;
            // 
            // chkSurround4
            // 
            this.chkSurround4.AutoSize = true;
            this.chkSurround4.Location = new System.Drawing.Point(261, 39);
            this.chkSurround4.Name = "chkSurround4";
            this.chkSurround4.Size = new System.Drawing.Size(32, 17);
            this.chkSurround4.TabIndex = 11;
            this.chkSurround4.Text = "4";
            this.chkSurround4.UseVisualStyleBackColor = true;
            // 
            // chkSurround3
            // 
            this.chkSurround3.AutoSize = true;
            this.chkSurround3.Location = new System.Drawing.Point(207, 39);
            this.chkSurround3.Name = "chkSurround3";
            this.chkSurround3.Size = new System.Drawing.Size(32, 17);
            this.chkSurround3.TabIndex = 10;
            this.chkSurround3.Text = "3";
            this.chkSurround3.UseVisualStyleBackColor = true;
            // 
            // chkSurround2
            // 
            this.chkSurround2.AutoSize = true;
            this.chkSurround2.Location = new System.Drawing.Point(159, 39);
            this.chkSurround2.Name = "chkSurround2";
            this.chkSurround2.Size = new System.Drawing.Size(32, 17);
            this.chkSurround2.TabIndex = 9;
            this.chkSurround2.Text = "2";
            this.chkSurround2.UseVisualStyleBackColor = true;
            // 
            // chkSurround1
            // 
            this.chkSurround1.AutoSize = true;
            this.chkSurround1.Checked = true;
            this.chkSurround1.CheckState = System.Windows.Forms.CheckState.Checked;
            this.chkSurround1.Location = new System.Drawing.Point(111, 39);
            this.chkSurround1.Name = "chkSurround1";
            this.chkSurround1.Size = new System.Drawing.Size(32, 17);
            this.chkSurround1.TabIndex = 8;
            this.chkSurround1.Text = "1";
            this.chkSurround1.UseVisualStyleBackColor = true;
            // 
            // btnViewSurrounds
            // 
            this.btnViewSurrounds.Location = new System.Drawing.Point(0, 45);
            this.btnViewSurrounds.Name = "btnViewSurrounds";
            this.btnViewSurrounds.Size = new System.Drawing.Size(94, 26);
            this.btnViewSurrounds.TabIndex = 7;
            this.btnViewSurrounds.Text = "View surrounds";
            this.btnViewSurrounds.UseVisualStyleBackColor = true;
            this.btnViewSurrounds.Click += new System.EventHandler(this.btnViewSurrounds_Click);
            // 
            // cboSubFields
            // 
            this.cboSubFields.FormattingEnabled = true;
            this.cboSubFields.Items.AddRange(new object[] {
            "1",
            "2",
            "3"});
            this.cboSubFields.Location = new System.Drawing.Point(413, 0);
            this.cboSubFields.Name = "cboSubFields";
            this.cboSubFields.Size = new System.Drawing.Size(59, 21);
            this.cboSubFields.TabIndex = 6;
            this.cboSubFields.Text = "1";
            this.cboSubFields.Validating += new System.ComponentModel.CancelEventHandler(this.cboUIntVal_Validating);
            // 
            // lblSubFields
            // 
            this.lblSubFields.AutoSize = true;
            this.lblSubFields.Location = new System.Drawing.Point(357, 4);
            this.lblSubFields.Name = "lblSubFields";
            this.lblSubFields.Size = new System.Drawing.Size(56, 13);
            this.lblSubFields.TabIndex = 5;
            this.lblSubFields.Text = "SubFields:";
            // 
            // cboMorphIterations
            // 
            this.cboMorphIterations.FormattingEnabled = true;
            this.cboMorphIterations.Items.AddRange(new object[] {
            "3",
            "5",
            "10",
            "20",
            "50",
            "90",
            "infinite"});
            this.cboMorphIterations.Location = new System.Drawing.Point(290, 0);
            this.cboMorphIterations.Name = "cboMorphIterations";
            this.cboMorphIterations.Size = new System.Drawing.Size(59, 21);
            this.cboMorphIterations.TabIndex = 4;
            this.cboMorphIterations.Text = "3";
            this.cboMorphIterations.Validating += new System.ComponentModel.CancelEventHandler(this.cboIterations_Validating);
            // 
            // lblMorphIterations
            // 
            this.lblMorphIterations.AutoSize = true;
            this.lblMorphIterations.Location = new System.Drawing.Point(237, 4);
            this.lblMorphIterations.Name = "lblMorphIterations";
            this.lblMorphIterations.Size = new System.Drawing.Size(53, 13);
            this.lblMorphIterations.TabIndex = 3;
            this.lblMorphIterations.Text = "Iterations:";
            // 
            // cboBoolFunc
            // 
            this.cboBoolFunc.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cboBoolFunc.FormattingEnabled = true;
            this.cboBoolFunc.Items.AddRange(new object[] {
            "0",
            "!a",
            "ab",
            "a+b",
            "a^b",
            "(!a)b"});
            this.cboBoolFunc.Location = new System.Drawing.Point(170, 0);
            this.cboBoolFunc.Name = "cboBoolFunc";
            this.cboBoolFunc.Size = new System.Drawing.Size(59, 21);
            this.cboBoolFunc.TabIndex = 2;
            // 
            // lblBoolFunc
            // 
            this.lblBoolFunc.AutoSize = true;
            this.lblBoolFunc.Location = new System.Drawing.Point(121, 4);
            this.lblBoolFunc.Name = "lblBoolFunc";
            this.lblBoolFunc.Size = new System.Drawing.Size(49, 13);
            this.lblBoolFunc.TabIndex = 1;
            this.lblBoolFunc.Text = "Boolean:";
            // 
            // chkRotate
            // 
            this.chkRotate.AutoSize = true;
            this.chkRotate.Checked = true;
            this.chkRotate.CheckState = System.Windows.Forms.CheckState.Checked;
            this.chkRotate.Location = new System.Drawing.Point(50, 2);
            this.chkRotate.Name = "chkRotate";
            this.chkRotate.RightToLeft = System.Windows.Forms.RightToLeft.Yes;
            this.chkRotate.Size = new System.Drawing.Size(58, 17);
            this.chkRotate.TabIndex = 0;
            this.chkRotate.Text = "Rotate";
            this.chkRotate.UseVisualStyleBackColor = true;
            // 
            // btnHelp
            // 
            this.btnHelp.BackColor = System.Drawing.Color.Yellow;
            this.btnHelp.Location = new System.Drawing.Point(17, 515);
            this.btnHelp.Name = "btnHelp";
            this.btnHelp.Size = new System.Drawing.Size(60, 26);
            this.btnHelp.TabIndex = 22;
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
            this.btnCancel.TabIndex = 23;
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
            this.btnReset.TabIndex = 24;
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
            this.btnApply.TabIndex = 25;
            this.btnApply.Text = "Apply";
            this.btnApply.UseVisualStyleBackColor = false;
            this.btnApply.Click += new System.EventHandler(this.btnApply_Click);
            // 
            // grpPreProcessing
            // 
            this.grpPreProcessing.Controls.Add(this.pnlAnisotropic);
            this.grpPreProcessing.Controls.Add(this.lblType);
            this.grpPreProcessing.Controls.Add(this.radioButton1);
            this.grpPreProcessing.Controls.Add(this.radioButton2);
            this.grpPreProcessing.Controls.Add(this.pnlMedian);
            this.grpPreProcessing.Controls.Add(this.cboMaskSize);
            this.grpPreProcessing.Controls.Add(this.lblMaskSize);
            this.grpPreProcessing.Controls.Add(this.rbSuperPixel);
            this.grpPreProcessing.Controls.Add(this.rbAnatropicDiffusionFilter);
            this.grpPreProcessing.Controls.Add(this.rbKurwaharaFilter);
            this.grpPreProcessing.Controls.Add(this.rbMedianFilter);
            this.grpPreProcessing.Location = new System.Drawing.Point(12, 4);
            this.grpPreProcessing.Margin = new System.Windows.Forms.Padding(1);
            this.grpPreProcessing.Name = "grpPreProcessing";
            this.grpPreProcessing.Padding = new System.Windows.Forms.Padding(1);
            this.grpPreProcessing.Size = new System.Drawing.Size(628, 110);
            this.grpPreProcessing.TabIndex = 26;
            this.grpPreProcessing.TabStop = false;
            this.grpPreProcessing.Text = "PreProcessing";
            // 
            // pnlAnisotropic
            // 
            this.pnlAnisotropic.Controls.Add(this.lblBlockSize);
            this.pnlAnisotropic.Controls.Add(this.cboBlockSize);
            this.pnlAnisotropic.Controls.Add(this.lblEdgeThreshold);
            this.pnlAnisotropic.Controls.Add(this.cboEdgeThreshold);
            this.pnlAnisotropic.Controls.Add(this.lblSmoothing);
            this.pnlAnisotropic.Controls.Add(this.cboSmoothing);
            this.pnlAnisotropic.Controls.Add(this.lblIterations);
            this.pnlAnisotropic.Controls.Add(this.cboIterations);
            this.pnlAnisotropic.Location = new System.Drawing.Point(395, 10);
            this.pnlAnisotropic.Name = "pnlAnisotropic";
            this.pnlAnisotropic.Size = new System.Drawing.Size(243, 96);
            this.pnlAnisotropic.TabIndex = 55;
            // 
            // lblBlockSize
            // 
            this.lblBlockSize.AutoSize = true;
            this.lblBlockSize.Location = new System.Drawing.Point(59, 71);
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
            this.cboBlockSize.Location = new System.Drawing.Point(122, 68);
            this.cboBlockSize.Name = "cboBlockSize";
            this.cboBlockSize.Size = new System.Drawing.Size(99, 21);
            this.cboBlockSize.TabIndex = 6;
            this.cboBlockSize.Text = "64";
            // 
            // lblEdgeThreshold
            // 
            this.lblEdgeThreshold.AutoSize = true;
            this.lblEdgeThreshold.Location = new System.Drawing.Point(34, 52);
            this.lblEdgeThreshold.Name = "lblEdgeThreshold";
            this.lblEdgeThreshold.Size = new System.Drawing.Size(85, 13);
            this.lblEdgeThreshold.TabIndex = 5;
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
            this.cboEdgeThreshold.Location = new System.Drawing.Point(122, 47);
            this.cboEdgeThreshold.Name = "cboEdgeThreshold";
            this.cboEdgeThreshold.Size = new System.Drawing.Size(99, 21);
            this.cboEdgeThreshold.TabIndex = 4;
            this.cboEdgeThreshold.Text = "5";
            // 
            // lblSmoothing
            // 
            this.lblSmoothing.AutoSize = true;
            this.lblSmoothing.Location = new System.Drawing.Point(2, 29);
            this.lblSmoothing.Name = "lblSmoothing";
            this.lblSmoothing.Size = new System.Drawing.Size(119, 13);
            this.lblSmoothing.TabIndex = 3;
            this.lblSmoothing.Text = "Smoothing per Iteration:";
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
            this.cboSmoothing.Location = new System.Drawing.Point(122, 26);
            this.cboSmoothing.Name = "cboSmoothing";
            this.cboSmoothing.Size = new System.Drawing.Size(99, 21);
            this.cboSmoothing.TabIndex = 2;
            this.cboSmoothing.Text = "1";
            // 
            // lblIterations
            // 
            this.lblIterations.AutoSize = true;
            this.lblIterations.Location = new System.Drawing.Point(44, 8);
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
            "500"});
            this.cboIterations.Location = new System.Drawing.Point(122, 4);
            this.cboIterations.Name = "cboIterations";
            this.cboIterations.Size = new System.Drawing.Size(99, 21);
            this.cboIterations.TabIndex = 0;
            this.cboIterations.Text = "20";
            // 
            // lblType
            // 
            this.lblType.AutoSize = true;
            this.lblType.Location = new System.Drawing.Point(261, -20);
            this.lblType.Name = "lblType";
            this.lblType.Size = new System.Drawing.Size(34, 13);
            this.lblType.TabIndex = 54;
            this.lblType.Text = "Type:";
            // 
            // radioButton1
            // 
            this.radioButton1.AutoSize = true;
            this.radioButton1.Location = new System.Drawing.Point(378, -22);
            this.radioButton1.Name = "radioButton1";
            this.radioButton1.Size = new System.Drawing.Size(67, 17);
            this.radioButton1.TabIndex = 53;
            this.radioButton1.Text = "Adaptive";
            this.radioButton1.UseVisualStyleBackColor = true;
            // 
            // radioButton2
            // 
            this.radioButton2.AutoSize = true;
            this.radioButton2.Checked = true;
            this.radioButton2.Location = new System.Drawing.Point(303, -22);
            this.radioButton2.Name = "radioButton2";
            this.radioButton2.Size = new System.Drawing.Size(68, 17);
            this.radioButton2.TabIndex = 52;
            this.radioButton2.TabStop = true;
            this.radioButton2.Text = "Standard";
            this.radioButton2.UseVisualStyleBackColor = true;
            // 
            // pnlMedian
            // 
            this.pnlMedian.Controls.Add(this.rbParametric);
            this.pnlMedian.Controls.Add(this.lblMedianType);
            this.pnlMedian.Controls.Add(this.rbStandard);
            this.pnlMedian.Controls.Add(this.rbAdaptive);
            this.pnlMedian.Location = new System.Drawing.Point(168, 36);
            this.pnlMedian.Name = "pnlMedian";
            this.pnlMedian.Size = new System.Drawing.Size(194, 43);
            this.pnlMedian.TabIndex = 49;
            // 
            // rbParametric
            // 
            this.rbParametric.AutoSize = true;
            this.rbParametric.Location = new System.Drawing.Point(44, 21);
            this.rbParametric.Name = "rbParametric";
            this.rbParametric.Size = new System.Drawing.Size(75, 17);
            this.rbParametric.TabIndex = 14;
            this.rbParametric.TabStop = true;
            this.rbParametric.Text = "Parametric";
            this.rbParametric.UseVisualStyleBackColor = true;
            // 
            // lblMedianType
            // 
            this.lblMedianType.AutoSize = true;
            this.lblMedianType.Location = new System.Drawing.Point(3, 5);
            this.lblMedianType.Name = "lblMedianType";
            this.lblMedianType.Size = new System.Drawing.Size(34, 13);
            this.lblMedianType.TabIndex = 13;
            this.lblMedianType.Text = "Type:";
            // 
            // rbStandard
            // 
            this.rbStandard.AutoSize = true;
            this.rbStandard.Checked = true;
            this.rbStandard.Location = new System.Drawing.Point(44, 3);
            this.rbStandard.Name = "rbStandard";
            this.rbStandard.Size = new System.Drawing.Size(68, 17);
            this.rbStandard.TabIndex = 7;
            this.rbStandard.TabStop = true;
            this.rbStandard.Text = "Standard";
            this.rbStandard.UseVisualStyleBackColor = true;
            // 
            // rbAdaptive
            // 
            this.rbAdaptive.AutoSize = true;
            this.rbAdaptive.Location = new System.Drawing.Point(124, 3);
            this.rbAdaptive.Name = "rbAdaptive";
            this.rbAdaptive.Size = new System.Drawing.Size(67, 17);
            this.rbAdaptive.TabIndex = 8;
            this.rbAdaptive.TabStop = true;
            this.rbAdaptive.Text = "Adaptive";
            this.rbAdaptive.UseVisualStyleBackColor = true;
            // 
            // cboMaskSize
            // 
            this.cboMaskSize.FormattingEnabled = true;
            this.cboMaskSize.Items.AddRange(new object[] {
            "3",
            "5",
            "7",
            "9",
            "11"});
            this.cboMaskSize.Location = new System.Drawing.Point(230, 12);
            this.cboMaskSize.Name = "cboMaskSize";
            this.cboMaskSize.Size = new System.Drawing.Size(50, 21);
            this.cboMaskSize.TabIndex = 48;
            this.cboMaskSize.Text = "3";
            // 
            // lblMaskSize
            // 
            this.lblMaskSize.AutoSize = true;
            this.lblMaskSize.Location = new System.Drawing.Point(164, 15);
            this.lblMaskSize.Name = "lblMaskSize";
            this.lblMaskSize.Size = new System.Drawing.Size(62, 13);
            this.lblMaskSize.TabIndex = 47;
            this.lblMaskSize.Text = "Mask Size: ";
            // 
            // rbSuperPixel
            // 
            this.rbSuperPixel.AutoSize = true;
            this.rbSuperPixel.Location = new System.Drawing.Point(316, 80);
            this.rbSuperPixel.Margin = new System.Windows.Forms.Padding(1);
            this.rbSuperPixel.Name = "rbSuperPixel";
            this.rbSuperPixel.Size = new System.Drawing.Size(78, 17);
            this.rbSuperPixel.TabIndex = 1;
            this.rbSuperPixel.TabStop = true;
            this.rbSuperPixel.Text = "Super Pixel";
            this.rbSuperPixel.UseVisualStyleBackColor = true;
            this.rbSuperPixel.Visible = false;
            this.rbSuperPixel.CheckedChanged += new System.EventHandler(this.rbSegmentation_CheckedChanged);
            // 
            // rbAnatropicDiffusionFilter
            // 
            this.rbAnatropicDiffusionFilter.AutoSize = true;
            this.rbAnatropicDiffusionFilter.Location = new System.Drawing.Point(5, 70);
            this.rbAnatropicDiffusionFilter.Margin = new System.Windows.Forms.Padding(1);
            this.rbAnatropicDiffusionFilter.Name = "rbAnatropicDiffusionFilter";
            this.rbAnatropicDiffusionFilter.Size = new System.Drawing.Size(146, 17);
            this.rbAnatropicDiffusionFilter.TabIndex = 0;
            this.rbAnatropicDiffusionFilter.TabStop = true;
            this.rbAnatropicDiffusionFilter.Text = "Anisotropic Diffusion Filter";
            this.rbAnatropicDiffusionFilter.UseVisualStyleBackColor = true;
            this.rbAnatropicDiffusionFilter.CheckedChanged += new System.EventHandler(this.rbSegmentation_CheckedChanged);
            // 
            // rbKurwaharaFilter
            // 
            this.rbKurwaharaFilter.AutoSize = true;
            this.rbKurwaharaFilter.Location = new System.Drawing.Point(5, 47);
            this.rbKurwaharaFilter.Margin = new System.Windows.Forms.Padding(1);
            this.rbKurwaharaFilter.Name = "rbKurwaharaFilter";
            this.rbKurwaharaFilter.Size = new System.Drawing.Size(101, 17);
            this.rbKurwaharaFilter.TabIndex = 3;
            this.rbKurwaharaFilter.TabStop = true;
            this.rbKurwaharaFilter.Text = "Kurwahara Filter";
            this.rbKurwaharaFilter.UseVisualStyleBackColor = true;
            this.rbKurwaharaFilter.CheckedChanged += new System.EventHandler(this.rbSegmentation_CheckedChanged);
            // 
            // rbMedianFilter
            // 
            this.rbMedianFilter.AutoSize = true;
            this.rbMedianFilter.Location = new System.Drawing.Point(5, 24);
            this.rbMedianFilter.Margin = new System.Windows.Forms.Padding(1);
            this.rbMedianFilter.Name = "rbMedianFilter";
            this.rbMedianFilter.Size = new System.Drawing.Size(85, 17);
            this.rbMedianFilter.TabIndex = 2;
            this.rbMedianFilter.TabStop = true;
            this.rbMedianFilter.Text = "Median Filter";
            this.rbMedianFilter.UseVisualStyleBackColor = true;
            this.rbMedianFilter.CheckedChanged += new System.EventHandler(this.rbSegmentation_CheckedChanged);
            // 
            // rbSkeletonization
            // 
            this.rbSkeletonization.AutoSize = true;
            this.rbSkeletonization.Location = new System.Drawing.Point(431, 409);
            this.rbSkeletonization.Name = "rbSkeletonization";
            this.rbSkeletonization.Size = new System.Drawing.Size(97, 17);
            this.rbSkeletonization.TabIndex = 34;
            this.rbSkeletonization.Text = "Skeletonization";
            this.rbSkeletonization.UseVisualStyleBackColor = true;
            this.rbSkeletonization.CheckedChanged += new System.EventHandler(this.rbSegmentation_CheckedChanged);
            // 
            // rbThinning
            // 
            this.rbThinning.AutoSize = true;
            this.rbThinning.Location = new System.Drawing.Point(345, 409);
            this.rbThinning.Name = "rbThinning";
            this.rbThinning.Size = new System.Drawing.Size(66, 17);
            this.rbThinning.TabIndex = 33;
            this.rbThinning.Text = "Thinning";
            this.rbThinning.UseVisualStyleBackColor = true;
            this.rbThinning.CheckedChanged += new System.EventHandler(this.rbSegmentation_CheckedChanged);
            // 
            // rbHitOrMiss
            // 
            this.rbHitOrMiss.AutoSize = true;
            this.rbHitOrMiss.Location = new System.Drawing.Point(251, 409);
            this.rbHitOrMiss.Name = "rbHitOrMiss";
            this.rbHitOrMiss.Size = new System.Drawing.Size(74, 17);
            this.rbHitOrMiss.TabIndex = 32;
            this.rbHitOrMiss.Text = "Hit or Miss";
            this.rbHitOrMiss.UseVisualStyleBackColor = true;
            this.rbHitOrMiss.CheckedChanged += new System.EventHandler(this.rbSegmentation_CheckedChanged);
            // 
            // rbMorphDilation
            // 
            this.rbMorphDilation.AutoSize = true;
            this.rbMorphDilation.Location = new System.Drawing.Point(144, 388);
            this.rbMorphDilation.Name = "rbMorphDilation";
            this.rbMorphDilation.Size = new System.Drawing.Size(60, 17);
            this.rbMorphDilation.TabIndex = 27;
            this.rbMorphDilation.Text = "Dilation";
            this.rbMorphDilation.UseVisualStyleBackColor = true;
            this.rbMorphDilation.CheckedChanged += new System.EventHandler(this.rbSegmentation_CheckedChanged);
            // 
            // rbMorphIterative
            // 
            this.rbMorphIterative.AutoSize = true;
            this.rbMorphIterative.Location = new System.Drawing.Point(144, 409);
            this.rbMorphIterative.Name = "rbMorphIterative";
            this.rbMorphIterative.Size = new System.Drawing.Size(87, 17);
            this.rbMorphIterative.TabIndex = 31;
            this.rbMorphIterative.Text = "Iterative Mod";
            this.rbMorphIterative.UseVisualStyleBackColor = true;
            this.rbMorphIterative.CheckedChanged += new System.EventHandler(this.rbSegmentation_CheckedChanged);
            // 
            // rbMorphErosion
            // 
            this.rbMorphErosion.AutoSize = true;
            this.rbMorphErosion.Location = new System.Drawing.Point(251, 388);
            this.rbMorphErosion.Name = "rbMorphErosion";
            this.rbMorphErosion.Size = new System.Drawing.Size(60, 17);
            this.rbMorphErosion.TabIndex = 28;
            this.rbMorphErosion.Text = "Erosion";
            this.rbMorphErosion.UseVisualStyleBackColor = true;
            this.rbMorphErosion.CheckedChanged += new System.EventHandler(this.rbSegmentation_CheckedChanged);
            // 
            // rbMorphClosing
            // 
            this.rbMorphClosing.AutoSize = true;
            this.rbMorphClosing.Location = new System.Drawing.Point(431, 388);
            this.rbMorphClosing.Name = "rbMorphClosing";
            this.rbMorphClosing.Size = new System.Drawing.Size(59, 17);
            this.rbMorphClosing.TabIndex = 30;
            this.rbMorphClosing.Text = "Closing";
            this.rbMorphClosing.UseVisualStyleBackColor = true;
            this.rbMorphClosing.CheckedChanged += new System.EventHandler(this.rbSegmentation_CheckedChanged);
            // 
            // rbMorphOpening
            // 
            this.rbMorphOpening.AutoSize = true;
            this.rbMorphOpening.Location = new System.Drawing.Point(345, 388);
            this.rbMorphOpening.Name = "rbMorphOpening";
            this.rbMorphOpening.Size = new System.Drawing.Size(65, 17);
            this.rbMorphOpening.TabIndex = 29;
            this.rbMorphOpening.Text = "Opening";
            this.rbMorphOpening.UseVisualStyleBackColor = true;
            this.rbMorphOpening.CheckedChanged += new System.EventHandler(this.rbSegmentation_CheckedChanged);
            // 
            // Segmentation
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.CausesValidation = false;
            this.Controls.Add(this.btnApply);
            this.Controls.Add(this.btnReset);
            this.Controls.Add(this.btnCancel);
            this.Controls.Add(this.btnHelp);
            this.Controls.Add(this.rbSkeletonization);
            this.Controls.Add(this.rbGVFSnake);
            this.Controls.Add(this.rbThinning);
            this.Controls.Add(this.rbWatershed);
            this.Controls.Add(this.rbHitOrMiss);
            this.Controls.Add(this.rbSplitMerge);
            this.Controls.Add(this.rbMorphDilation);
            this.Controls.Add(this.rbMorphIterative);
            this.Controls.Add(this.rbMultiResolution);
            this.Controls.Add(this.rbMorphErosion);
            this.Controls.Add(this.rbMorphClosing);
            this.Controls.Add(this.rbMorphOpening);
            this.Controls.Add(this.rbSCTCenter);
            this.Controls.Add(this.rbPCTMedian);
            this.Controls.Add(this.rbMedianCut);
            this.Controls.Add(this.rbFuzzyCMean);
            this.Controls.Add(this.rbHistThreshold);
            this.Controls.Add(this.rbOtsu);
            this.Controls.Add(this.rbAutoThresh);
            this.Controls.Add(this.rbGrayLevelQuant);
            this.Controls.Add(this.grpSegmentation);
            this.Controls.Add(this.grpPreProcessing);
            this.Controls.Add(this.grpMorpho);
            this.Name = "Segmentation";
            this.Size = new System.Drawing.Size(679, 556);
            this.Load += new System.EventHandler(this.Segmentation_Load);
            this.grpSegmentation.ResumeLayout(false);
            this.pnlGVFSnake.ResumeLayout(false);
            this.pnlGVFSnake.PerformLayout();
            this.pnlMultiRes.ResumeLayout(false);
            this.pnlMultiRes.PerformLayout();
            this.pnlGrayLevelQuant.ResumeLayout(false);
            this.pnlGrayLevelQuant.PerformLayout();
            this.pnlHistThresh.ResumeLayout(false);
            this.pnlHistThresh.PerformLayout();
            this.grpMorpho.ResumeLayout(false);
            this.grpMorpho.PerformLayout();
            this.pnlFilterSize.ResumeLayout(false);
            this.pnlFilterSize.PerformLayout();
            this.pnlMorphological.ResumeLayout(false);
            this.pnlMorphological.PerformLayout();
            this.pnlMorphIterative.ResumeLayout(false);
            this.pnlMorphIterative.PerformLayout();
            this.grpPreProcessing.ResumeLayout(false);
            this.grpPreProcessing.PerformLayout();
            this.pnlAnisotropic.ResumeLayout(false);
            this.pnlAnisotropic.PerformLayout();
            this.pnlMedian.ResumeLayout(false);
            this.pnlMedian.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.RadioButton rbGrayLevelQuant;
        private System.Windows.Forms.RadioButton rbAutoThresh;
        private System.Windows.Forms.RadioButton rbOtsu;
        private System.Windows.Forms.RadioButton rbHistThreshold;
        private System.Windows.Forms.RadioButton rbFuzzyCMean;
        private System.Windows.Forms.RadioButton rbMedianCut;
        private System.Windows.Forms.RadioButton rbPCTMedian;
        private System.Windows.Forms.RadioButton rbSCTCenter;
        private System.Windows.Forms.RadioButton rbMultiResolution;
        private System.Windows.Forms.RadioButton rbSplitMerge;
        private System.Windows.Forms.RadioButton rbWatershed;
        private System.Windows.Forms.RadioButton rbGVFSnake;
        private System.Windows.Forms.GroupBox grpSegmentation;
        private System.Windows.Forms.Panel pnlGrayLevelQuant;
        private System.Windows.Forms.ComboBox cboWatershedThreshold;
        private System.Windows.Forms.Label lblWatershedThreshold;
        private System.Windows.Forms.CheckBox chkMergeResult;
        private System.Windows.Forms.ComboBox cboSCTBAxis;
        private System.Windows.Forms.Label lblSCTBAxis;
        private System.Windows.Forms.ComboBox cboSCTAAxis;
        private System.Windows.Forms.Label lblSCTAAxis;
        private System.Windows.Forms.ComboBox cboNumColors;
        private System.Windows.Forms.Label lblNumColors;
        private System.Windows.Forms.ComboBox cboFuzzyCVariance;
        private System.Windows.Forms.Label lblFuzzyCVariance;
        private System.Windows.Forms.ComboBox cboLimit;
        private System.Windows.Forms.Label lblLimit;
        private System.Windows.Forms.ComboBox cboQuantMethod;
        private System.Windows.Forms.Label lblQuantMethod;
        private System.Windows.Forms.ComboBox cboNumGrayLevels;
        private System.Windows.Forms.Label lblNumGrayLevels;
        private System.Windows.Forms.Panel pnlMultiRes;
        private System.Windows.Forms.ComboBox cboPixelDistance;
        private System.Windows.Forms.Label lblPixelDistance;
        private System.Windows.Forms.ComboBox cboPercentage;
        private System.Windows.Forms.Label lblPercentage;
        private System.Windows.Forms.CheckBox chkPCT;
        private System.Windows.Forms.ComboBox cboSimilarity;
        private System.Windows.Forms.Label lblSimilarity;
        private System.Windows.Forms.ComboBox cboThreshold;
        private System.Windows.Forms.Label lblThreshold;
        private System.Windows.Forms.ComboBox cboEntryLevel;
        private System.Windows.Forms.Label lblEntryLevel;
        private System.Windows.Forms.RadioButton rbWeightedGrayLevel;
        private System.Windows.Forms.RadioButton rbLocalStd;
        private System.Windows.Forms.RadioButton rbLocalMean;
        private System.Windows.Forms.RadioButton rbHomogeneity;
        private System.Windows.Forms.RadioButton rbVariance;
        private System.Windows.Forms.RadioButton rbPureUniform;
        private System.Windows.Forms.Panel pnlGVFSnake;
        private System.Windows.Forms.ComboBox cboKappa;
        private System.Windows.Forms.Label lblKappa;
        private System.Windows.Forms.ComboBox cboBeta;
        private System.Windows.Forms.Label lblBeta;
        private System.Windows.Forms.ComboBox cboAlpha;
        private System.Windows.Forms.Label lblAlpha;
        private System.Windows.Forms.ComboBox cboSnakeIterations;
        private System.Windows.Forms.Label lblSnakeIterations;
        private System.Windows.Forms.GroupBox grpMorpho;
        private System.Windows.Forms.Panel pnlMorphological;
        private System.Windows.Forms.ComboBox cboKernelHeight;
        private System.Windows.Forms.ComboBox cboKernelWidth;
        private System.Windows.Forms.Label lblKernelWidth;
        private System.Windows.Forms.ComboBox cboKernelSize;
        private System.Windows.Forms.Label lblKernelSize;
        private System.Windows.Forms.ComboBox cboKernelType;
        private System.Windows.Forms.Label lblKernelType;
        private System.Windows.Forms.Label lblBinaryImages;
        private System.Windows.Forms.Label lblAllImages;
        private System.Windows.Forms.Panel pnlMorphIterative;
        private System.Windows.Forms.CheckBox chkSurround14;
        private System.Windows.Forms.CheckBox chkSurround13;
        private System.Windows.Forms.CheckBox chkSurround12;
        private System.Windows.Forms.CheckBox chkSurround11;
        private System.Windows.Forms.CheckBox chkSurround10;
        private System.Windows.Forms.CheckBox chkSurround9;
        private System.Windows.Forms.CheckBox chkSurround8;
        private System.Windows.Forms.CheckBox chkSurround7;
        private System.Windows.Forms.CheckBox chkSurround6;
        private System.Windows.Forms.CheckBox chkSurround5;
        private System.Windows.Forms.CheckBox chkSurround4;
        private System.Windows.Forms.CheckBox chkSurround3;
        private System.Windows.Forms.CheckBox chkSurround2;
        private System.Windows.Forms.CheckBox chkSurround1;
        private System.Windows.Forms.Button btnViewSurrounds;
        private System.Windows.Forms.ComboBox cboSubFields;
        private System.Windows.Forms.Label lblSubFields;
        private System.Windows.Forms.ComboBox cboMorphIterations;
        private System.Windows.Forms.Label lblMorphIterations;
        private System.Windows.Forms.ComboBox cboBoolFunc;
        private System.Windows.Forms.Label lblBoolFunc;
        private System.Windows.Forms.CheckBox chkRotate;
        private System.Windows.Forms.Panel pnlFilterSize;
        private System.Windows.Forms.ComboBox cboSkeletonMethod;
        private System.Windows.Forms.Label lblSkeletonMethod;
        private System.Windows.Forms.ComboBox cboSkeletonConnect;
        private System.Windows.Forms.Label lblSkeletonConnect;
        private System.Windows.Forms.ComboBox cboSkeletonIterations;
        private System.Windows.Forms.Label lblSkeletonIterations;
        private System.Windows.Forms.RadioButton rbFilterSize9x9;
        private System.Windows.Forms.RadioButton rbFilterSize7x7;
        private System.Windows.Forms.RadioButton rbFilterSize5x5;
        private System.Windows.Forms.RadioButton rbFilterSize3x3;
        private System.Windows.Forms.Label lblFilterSize;
        private System.Windows.Forms.Button btnHelp;
        private System.Windows.Forms.Button btnCancel;
        private System.Windows.Forms.Button btnReset;
        private System.Windows.Forms.Button btnApply;
        private System.Windows.Forms.Label lblKernelHeight;
        private System.Windows.Forms.Panel pnlHistThresh;
        private System.Windows.Forms.Label lblHistThresh;
        private System.Windows.Forms.RadioButton rbHistThreshBands;
        private System.Windows.Forms.RadioButton rbHistThreshLum;
        private System.Windows.Forms.RadioButton rbHistThreshPCT;
        private System.Windows.Forms.ComboBox cbHistThresh;
        private System.Windows.Forms.Label lblHistTore;
        private System.Windows.Forms.GroupBox grpPreProcessing;
        private System.Windows.Forms.RadioButton rbKurwaharaFilter;
        private System.Windows.Forms.RadioButton rbMedianFilter;
        private System.Windows.Forms.RadioButton rbSuperPixel;
        private System.Windows.Forms.RadioButton rbAnatropicDiffusionFilter;
        private System.Windows.Forms.Panel pnlMedian;
        private System.Windows.Forms.Label lblMedianType;
        private System.Windows.Forms.RadioButton rbStandard;
        private System.Windows.Forms.RadioButton rbAdaptive;
        private System.Windows.Forms.ComboBox cboMaskSize;
        private System.Windows.Forms.Label lblMaskSize;
        private System.Windows.Forms.Panel pnlAnisotropic;
        private System.Windows.Forms.Label lblBlockSize;
        private System.Windows.Forms.ComboBox cboBlockSize;
        private System.Windows.Forms.Label lblEdgeThreshold;
        private System.Windows.Forms.ComboBox cboEdgeThreshold;
        private System.Windows.Forms.Label lblSmoothing;
        private System.Windows.Forms.ComboBox cboSmoothing;
        private System.Windows.Forms.Label lblIterations;
        private System.Windows.Forms.ComboBox cboIterations;
        private System.Windows.Forms.Label lblType;
        private System.Windows.Forms.RadioButton radioButton1;
        private System.Windows.Forms.RadioButton radioButton2;
        private System.Windows.Forms.RadioButton rbSkeletonization;
        private System.Windows.Forms.RadioButton rbThinning;
        private System.Windows.Forms.RadioButton rbHitOrMiss;
        private System.Windows.Forms.RadioButton rbMorphDilation;
        private System.Windows.Forms.RadioButton rbMorphIterative;
        private System.Windows.Forms.RadioButton rbMorphErosion;
        private System.Windows.Forms.RadioButton rbMorphClosing;
        private System.Windows.Forms.RadioButton rbMorphOpening;
        private System.Windows.Forms.RadioButton rbParametric;
    }
}
