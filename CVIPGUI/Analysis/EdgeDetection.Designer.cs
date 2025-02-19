namespace CVIPGUI.Analysis
{
    partial class EdgeDetection
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
            this.rbRoberts = new System.Windows.Forms.RadioButton();
            this.rbSobel = new System.Windows.Forms.RadioButton();
            this.rbPrewitt = new System.Windows.Forms.RadioButton();
            this.rbLaplacian = new System.Windows.Forms.RadioButton();
            this.rbKirsch = new System.Windows.Forms.RadioButton();
            this.rbRobinson = new System.Windows.Forms.RadioButton();
            this.rbPyramid = new System.Windows.Forms.RadioButton();
            this.rbCerchar = new System.Windows.Forms.RadioButton();
            this.rbMarrHildreth = new System.Windows.Forms.RadioButton();
            this.rbCanny = new System.Windows.Forms.RadioButton();
            this.rbBoieCox = new System.Windows.Forms.RadioButton();
            this.rbShenCastan = new System.Windows.Forms.RadioButton();
            this.rbFreiChen = new System.Windows.Forms.RadioButton();
            this.rbMoravec = new System.Windows.Forms.RadioButton();
            this.rbHarris = new System.Windows.Forms.RadioButton();
            this.rbHough = new System.Windows.Forms.RadioButton();
            this.rbEdgeLink = new System.Windows.Forms.RadioButton();
            this.rbPratt = new System.Windows.Forms.RadioButton();
            this.grpRoberts = new System.Windows.Forms.GroupBox();
            this.chkNotImage = new System.Windows.Forms.CheckBox();
            this.cboThreshold = new System.Windows.Forms.ComboBox();
            this.btnThreshold = new System.Windows.Forms.Button();
            this.pnlRoberts = new System.Windows.Forms.Panel();
            this.chkKeepDC = new System.Windows.Forms.CheckBox();
            this.btnShowMask = new System.Windows.Forms.Button();
            this.cboLaplacianMask = new System.Windows.Forms.ComboBox();
            this.lblLaplacianMask = new System.Windows.Forms.Label();
            this.btnShowType = new System.Windows.Forms.Button();
            this.cboRobertsType = new System.Windows.Forms.ComboBox();
            this.lblRobertsType = new System.Windows.Forms.Label();
            this.cboKernelSize = new System.Windows.Forms.ComboBox();
            this.lblKernelSize = new System.Windows.Forms.Label();
            this.cboPostThreshold = new System.Windows.Forms.ComboBox();
            this.lblPostThreshold = new System.Windows.Forms.Label();
            this.cboPreFilter = new System.Windows.Forms.ComboBox();
            this.lblPreFilter = new System.Windows.Forms.Label();
            this.grpMarr = new System.Windows.Forms.GroupBox();
            this.lblThresholdVal = new System.Windows.Forms.Label();
            this.cboThresholdValue = new System.Windows.Forms.ComboBox();
            this.pnlMarr = new System.Windows.Forms.Panel();
            this.chkShowImages = new System.Windows.Forms.CheckBox();
            this.pnlFrieChen = new System.Windows.Forms.Panel();
            this.cboFreiChenPostThresh = new System.Windows.Forms.ComboBox();
            this.lblFreiChenPostThresh = new System.Windows.Forms.Label();
            this.cboThresholdAngle = new System.Windows.Forms.ComboBox();
            this.lblThresholdAngle = new System.Windows.Forms.Label();
            this.cboProjectionMethod = new System.Windows.Forms.ComboBox();
            this.lblProjectionMethod = new System.Windows.Forms.Label();
            this.cboFreiChenPreFilter = new System.Windows.Forms.ComboBox();
            this.lblFreiChenPreFilter = new System.Windows.Forms.Label();
            this.chkThresholdAngle = new System.Windows.Forms.CheckBox();
            this.chkFrieKeepDC = new System.Windows.Forms.CheckBox();
            this.pnlMarrHildreth = new System.Windows.Forms.Panel();
            this.chkCombineBands = new System.Windows.Forms.CheckBox();
            this.cboMarrDelta = new System.Windows.Forms.ComboBox();
            this.lblMarrDelta = new System.Windows.Forms.Label();
            this.cboMarrSigma = new System.Windows.Forms.ComboBox();
            this.lblMarrSigma = new System.Windows.Forms.Label();
            this.rbDualVariance = new System.Windows.Forms.RadioButton();
            this.rbSingleVariance = new System.Windows.Forms.RadioButton();
            this.pnlCanny = new System.Windows.Forms.Panel();
            this.cboCannyVariance = new System.Windows.Forms.ComboBox();
            this.lblCannyVariance = new System.Windows.Forms.Label();
            this.cboCannyHiThresh = new System.Windows.Forms.ComboBox();
            this.lblCannyHiThresh = new System.Windows.Forms.Label();
            this.cboCannyLoThresh = new System.Windows.Forms.ComboBox();
            this.lblCannyLoThresh = new System.Windows.Forms.Label();
            this.pnlBoieCox = new System.Windows.Forms.Panel();
            this.chkThinEdge = new System.Windows.Forms.CheckBox();
            this.cboBoieVariance = new System.Windows.Forms.ComboBox();
            this.lblBoieVariance = new System.Windows.Forms.Label();
            this.cboBoieHiThresh = new System.Windows.Forms.ComboBox();
            this.lblBoieHiThresh = new System.Windows.Forms.Label();
            this.cboBoieLoThresh = new System.Windows.Forms.ComboBox();
            this.lblBoieLoThresh = new System.Windows.Forms.Label();
            this.rbHysteresisThreshold = new System.Windows.Forms.RadioButton();
            this.rbOrdinaryThreshold = new System.Windows.Forms.RadioButton();
            this.pnlShenCastan = new System.Windows.Forms.Panel();
            this.cboThinFactor = new System.Windows.Forms.ComboBox();
            this.lblThinFactor = new System.Windows.Forms.Label();
            this.cboWindowSize = new System.Windows.Forms.ComboBox();
            this.lblWindowSize = new System.Windows.Forms.Label();
            this.cboSmoothingFactor = new System.Windows.Forms.ComboBox();
            this.lblSmoothingFactor = new System.Windows.Forms.Label();
            this.cboShenHiThresh = new System.Windows.Forms.ComboBox();
            this.lblShenHiThresh = new System.Windows.Forms.Label();
            this.cboShenLoThresh = new System.Windows.Forms.ComboBox();
            this.lblShenLoThresh = new System.Windows.Forms.Label();
            this.grpMoravec = new System.Windows.Forms.GroupBox();
            this.pnlMoravec = new System.Windows.Forms.Panel();
            this.pnlMoravecDetector = new System.Windows.Forms.Panel();
            this.cboMoravecThreshold = new System.Windows.Forms.ComboBox();
            this.lblMoravecThreshold = new System.Windows.Forms.Label();
            this.pnlEdgeLink = new System.Windows.Forms.Panel();
            this.cboEdgeLinkConnectDistance = new System.Windows.Forms.ComboBox();
            this.lblEdgeLinkConnectDistance = new System.Windows.Forms.Label();
            this.pnlPratt = new System.Windows.Forms.Panel();
            this.txtCurrentImg = new System.Windows.Forms.Label();
            this.cboSecondImg = new System.Windows.Forms.ComboBox();
            this.txtPrattResultGS = new System.Windows.Forms.Label();
            this.pnlPrattResultRGB = new System.Windows.Forms.Panel();
            this.txtPrattResultB = new System.Windows.Forms.Label();
            this.txtPrattResultG = new System.Windows.Forms.Label();
            this.txtPrattResultR = new System.Windows.Forms.Label();
            this.lblPrattResult = new System.Windows.Forms.Label();
            this.cboScaleFactor = new System.Windows.Forms.ComboBox();
            this.lblScaleFactor = new System.Windows.Forms.Label();
            this.lblEdgeDetectImage = new System.Windows.Forms.Label();
            this.lblIdealImage = new System.Windows.Forms.Label();
            this.pnlHarris = new System.Windows.Forms.Panel();
            this.cboHarrisMinDistance = new System.Windows.Forms.ComboBox();
            this.lblHarrisMinDistance = new System.Windows.Forms.Label();
            this.cboHarrisAlpha = new System.Windows.Forms.ComboBox();
            this.lblHarrisAlpha = new System.Windows.Forms.Label();
            this.cboHarrisBorder = new System.Windows.Forms.ComboBox();
            this.lblHarrisBorder = new System.Windows.Forms.Label();
            this.cboHarrisThreshold = new System.Windows.Forms.ComboBox();
            this.lblHarrisThreshold = new System.Windows.Forms.Label();
            this.pnlHough = new System.Windows.Forms.Panel();
            this.cboIntermediateResult = new System.Windows.Forms.ComboBox();
            this.lblIntermediateResult = new System.Windows.Forms.Label();
            this.cboSegmentPixels = new System.Windows.Forms.ComboBox();
            this.lblSegmentPixels = new System.Windows.Forms.Label();
            this.cboLinePixels = new System.Windows.Forms.ComboBox();
            this.lblLinePixels = new System.Windows.Forms.Label();
            this.cboHoughConnectDistance = new System.Windows.Forms.ComboBox();
            this.lblHoughConnectDistance = new System.Windows.Forms.Label();
            this.cboDeltaLength = new System.Windows.Forms.ComboBox();
            this.lblDeltaLength = new System.Windows.Forms.Label();
            this.cboLineAngles = new System.Windows.Forms.ComboBox();
            this.lblLineAngles = new System.Windows.Forms.Label();
            this.btnHelp = new System.Windows.Forms.Button();
            this.btnCancel = new System.Windows.Forms.Button();
            this.btnReset = new System.Windows.Forms.Button();
            this.btnApply = new System.Windows.Forms.Button();
            this.toolTipImage2 = new System.Windows.Forms.ToolTip(this.components);
            this.grpRoberts.SuspendLayout();
            this.pnlRoberts.SuspendLayout();
            this.grpMarr.SuspendLayout();
            this.pnlMarr.SuspendLayout();
            this.pnlFrieChen.SuspendLayout();
            this.pnlMarrHildreth.SuspendLayout();
            this.pnlCanny.SuspendLayout();
            this.pnlBoieCox.SuspendLayout();
            this.pnlShenCastan.SuspendLayout();
            this.grpMoravec.SuspendLayout();
            this.pnlMoravec.SuspendLayout();
            this.pnlMoravecDetector.SuspendLayout();
            this.pnlEdgeLink.SuspendLayout();
            this.pnlPratt.SuspendLayout();
            this.pnlPrattResultRGB.SuspendLayout();
            this.pnlHarris.SuspendLayout();
            this.pnlHough.SuspendLayout();
            this.SuspendLayout();
            // 
            // rbRoberts
            // 
            this.rbRoberts.AutoSize = true;
            this.rbRoberts.Checked = true;
            this.rbRoberts.Location = new System.Drawing.Point(20, 17);
            this.rbRoberts.Name = "rbRoberts";
            this.rbRoberts.Size = new System.Drawing.Size(62, 17);
            this.rbRoberts.TabIndex = 0;
            this.rbRoberts.TabStop = true;
            this.rbRoberts.Text = "Roberts";
            this.rbRoberts.UseVisualStyleBackColor = true;
            this.rbRoberts.CheckedChanged += new System.EventHandler(this.rbEdgeDetection_CheckedChanged);
            // 
            // rbSobel
            // 
            this.rbSobel.AutoSize = true;
            this.rbSobel.Location = new System.Drawing.Point(20, 39);
            this.rbSobel.Name = "rbSobel";
            this.rbSobel.Size = new System.Drawing.Size(52, 17);
            this.rbSobel.TabIndex = 1;
            this.rbSobel.Text = "Sobel";
            this.rbSobel.UseVisualStyleBackColor = true;
            this.rbSobel.CheckedChanged += new System.EventHandler(this.rbEdgeDetection_CheckedChanged);
            // 
            // rbPrewitt
            // 
            this.rbPrewitt.AutoSize = true;
            this.rbPrewitt.Location = new System.Drawing.Point(20, 61);
            this.rbPrewitt.Name = "rbPrewitt";
            this.rbPrewitt.Size = new System.Drawing.Size(57, 17);
            this.rbPrewitt.TabIndex = 2;
            this.rbPrewitt.Text = "Prewitt";
            this.rbPrewitt.UseVisualStyleBackColor = true;
            this.rbPrewitt.CheckedChanged += new System.EventHandler(this.rbEdgeDetection_CheckedChanged);
            // 
            // rbLaplacian
            // 
            this.rbLaplacian.AutoSize = true;
            this.rbLaplacian.Location = new System.Drawing.Point(20, 83);
            this.rbLaplacian.Name = "rbLaplacian";
            this.rbLaplacian.Size = new System.Drawing.Size(71, 17);
            this.rbLaplacian.TabIndex = 3;
            this.rbLaplacian.Text = "Laplacian";
            this.rbLaplacian.UseVisualStyleBackColor = true;
            this.rbLaplacian.CheckedChanged += new System.EventHandler(this.rbEdgeDetection_CheckedChanged);
            // 
            // rbKirsch
            // 
            this.rbKirsch.AutoSize = true;
            this.rbKirsch.Location = new System.Drawing.Point(20, 105);
            this.rbKirsch.Name = "rbKirsch";
            this.rbKirsch.Size = new System.Drawing.Size(54, 17);
            this.rbKirsch.TabIndex = 4;
            this.rbKirsch.Text = "Kirsch";
            this.rbKirsch.UseVisualStyleBackColor = true;
            this.rbKirsch.CheckedChanged += new System.EventHandler(this.rbEdgeDetection_CheckedChanged);
            // 
            // rbRobinson
            // 
            this.rbRobinson.AutoSize = true;
            this.rbRobinson.Location = new System.Drawing.Point(20, 127);
            this.rbRobinson.Name = "rbRobinson";
            this.rbRobinson.Size = new System.Drawing.Size(70, 17);
            this.rbRobinson.TabIndex = 5;
            this.rbRobinson.Text = "Robinson";
            this.rbRobinson.UseVisualStyleBackColor = true;
            this.rbRobinson.CheckedChanged += new System.EventHandler(this.rbEdgeDetection_CheckedChanged);
            // 
            // rbPyramid
            // 
            this.rbPyramid.AutoSize = true;
            this.rbPyramid.Location = new System.Drawing.Point(20, 149);
            this.rbPyramid.Name = "rbPyramid";
            this.rbPyramid.Size = new System.Drawing.Size(62, 17);
            this.rbPyramid.TabIndex = 6;
            this.rbPyramid.Text = "Pyramid";
            this.rbPyramid.UseVisualStyleBackColor = true;
            this.rbPyramid.CheckedChanged += new System.EventHandler(this.rbEdgeDetection_CheckedChanged);
            // 
            // rbCerchar
            // 
            this.rbCerchar.AutoSize = true;
            this.rbCerchar.Location = new System.Drawing.Point(20, 171);
            this.rbCerchar.Name = "rbCerchar";
            this.rbCerchar.Size = new System.Drawing.Size(62, 17);
            this.rbCerchar.TabIndex = 7;
            this.rbCerchar.Text = "Cerchar";
            this.rbCerchar.UseVisualStyleBackColor = true;
            this.rbCerchar.CheckedChanged += new System.EventHandler(this.rbEdgeDetection_CheckedChanged);
            // 
            // rbMarrHildreth
            // 
            this.rbMarrHildreth.AutoSize = true;
            this.rbMarrHildreth.Location = new System.Drawing.Point(20, 210);
            this.rbMarrHildreth.Name = "rbMarrHildreth";
            this.rbMarrHildreth.Size = new System.Drawing.Size(85, 17);
            this.rbMarrHildreth.TabIndex = 8;
            this.rbMarrHildreth.Text = "Marr Hildreth";
            this.rbMarrHildreth.UseVisualStyleBackColor = true;
            this.rbMarrHildreth.CheckedChanged += new System.EventHandler(this.rbEdgeDetection_CheckedChanged);
            // 
            // rbCanny
            // 
            this.rbCanny.AutoSize = true;
            this.rbCanny.Location = new System.Drawing.Point(20, 232);
            this.rbCanny.Name = "rbCanny";
            this.rbCanny.Size = new System.Drawing.Size(55, 17);
            this.rbCanny.TabIndex = 9;
            this.rbCanny.Text = "Canny";
            this.rbCanny.UseVisualStyleBackColor = true;
            this.rbCanny.CheckedChanged += new System.EventHandler(this.rbEdgeDetection_CheckedChanged);
            // 
            // rbBoieCox
            // 
            this.rbBoieCox.AutoSize = true;
            this.rbBoieCox.Location = new System.Drawing.Point(20, 254);
            this.rbBoieCox.Name = "rbBoieCox";
            this.rbBoieCox.Size = new System.Drawing.Size(67, 17);
            this.rbBoieCox.TabIndex = 10;
            this.rbBoieCox.Text = "Boie-Cox";
            this.rbBoieCox.UseVisualStyleBackColor = true;
            this.rbBoieCox.CheckedChanged += new System.EventHandler(this.rbEdgeDetection_CheckedChanged);
            // 
            // rbShenCastan
            // 
            this.rbShenCastan.AutoSize = true;
            this.rbShenCastan.Location = new System.Drawing.Point(20, 276);
            this.rbShenCastan.Name = "rbShenCastan";
            this.rbShenCastan.Size = new System.Drawing.Size(86, 17);
            this.rbShenCastan.TabIndex = 11;
            this.rbShenCastan.Text = "Shen-Castan";
            this.rbShenCastan.UseVisualStyleBackColor = true;
            this.rbShenCastan.CheckedChanged += new System.EventHandler(this.rbEdgeDetection_CheckedChanged);
            // 
            // rbFreiChen
            // 
            this.rbFreiChen.AutoSize = true;
            this.rbFreiChen.Location = new System.Drawing.Point(20, 298);
            this.rbFreiChen.Name = "rbFreiChen";
            this.rbFreiChen.Size = new System.Drawing.Size(70, 17);
            this.rbFreiChen.TabIndex = 12;
            this.rbFreiChen.Text = "Frei-Chen";
            this.rbFreiChen.UseVisualStyleBackColor = true;
            this.rbFreiChen.CheckedChanged += new System.EventHandler(this.rbEdgeDetection_CheckedChanged);
            // 
            // rbMoravec
            // 
            this.rbMoravec.AutoSize = true;
            this.rbMoravec.Location = new System.Drawing.Point(20, 338);
            this.rbMoravec.Name = "rbMoravec";
            this.rbMoravec.Size = new System.Drawing.Size(67, 17);
            this.rbMoravec.TabIndex = 13;
            this.rbMoravec.Text = "Moravec";
            this.rbMoravec.UseVisualStyleBackColor = true;
            this.rbMoravec.CheckedChanged += new System.EventHandler(this.rbEdgeDetection_CheckedChanged);
            // 
            // rbHarris
            // 
            this.rbHarris.AutoSize = true;
            this.rbHarris.Location = new System.Drawing.Point(20, 361);
            this.rbHarris.Name = "rbHarris";
            this.rbHarris.Size = new System.Drawing.Size(86, 17);
            this.rbHarris.TabIndex = 14;
            this.rbHarris.Text = "Harris Corner";
            this.rbHarris.UseVisualStyleBackColor = true;
            this.rbHarris.CheckedChanged += new System.EventHandler(this.rbEdgeDetection_CheckedChanged);
            // 
            // rbHough
            // 
            this.rbHough.AutoSize = true;
            this.rbHough.Location = new System.Drawing.Point(20, 384);
            this.rbHough.Name = "rbHough";
            this.rbHough.Size = new System.Drawing.Size(57, 17);
            this.rbHough.TabIndex = 15;
            this.rbHough.Text = "Hough";
            this.rbHough.UseVisualStyleBackColor = true;
            this.rbHough.CheckedChanged += new System.EventHandler(this.rbEdgeDetection_CheckedChanged);
            // 
            // rbEdgeLink
            // 
            this.rbEdgeLink.AutoSize = true;
            this.rbEdgeLink.Location = new System.Drawing.Point(20, 407);
            this.rbEdgeLink.Name = "rbEdgeLink";
            this.rbEdgeLink.Size = new System.Drawing.Size(73, 17);
            this.rbEdgeLink.TabIndex = 16;
            this.rbEdgeLink.Text = "Edge Link";
            this.rbEdgeLink.UseVisualStyleBackColor = true;
            this.rbEdgeLink.CheckedChanged += new System.EventHandler(this.rbEdgeDetection_CheckedChanged);
            // 
            // rbPratt
            // 
            this.rbPratt.AutoSize = true;
            this.rbPratt.Location = new System.Drawing.Point(20, 430);
            this.rbPratt.Name = "rbPratt";
            this.rbPratt.Size = new System.Drawing.Size(73, 17);
            this.rbPratt.TabIndex = 17;
            this.rbPratt.Text = "Pratt Merit";
            this.rbPratt.UseVisualStyleBackColor = true;
            this.rbPratt.CheckedChanged += new System.EventHandler(this.rbEdgeDetection_CheckedChanged);
            // 
            // grpRoberts
            // 
            this.grpRoberts.Controls.Add(this.chkNotImage);
            this.grpRoberts.Controls.Add(this.cboThreshold);
            this.grpRoberts.Controls.Add(this.btnThreshold);
            this.grpRoberts.Controls.Add(this.pnlRoberts);
            this.grpRoberts.Location = new System.Drawing.Point(8, 4);
            this.grpRoberts.Name = "grpRoberts";
            this.grpRoberts.Size = new System.Drawing.Size(628, 190);
            this.grpRoberts.TabIndex = 18;
            this.grpRoberts.TabStop = false;
            // 
            // chkNotImage
            // 
            this.chkNotImage.AutoSize = true;
            this.chkNotImage.Checked = true;
            this.chkNotImage.CheckState = System.Windows.Forms.CheckState.Checked;
            this.chkNotImage.Location = new System.Drawing.Point(382, 167);
            this.chkNotImage.Name = "chkNotImage";
            this.chkNotImage.Size = new System.Drawing.Size(81, 17);
            this.chkNotImage.TabIndex = 3;
            this.chkNotImage.Text = "NOT Image";
            this.chkNotImage.UseVisualStyleBackColor = true;
            // 
            // cboThreshold
            // 
            this.cboThreshold.FormattingEnabled = true;
            this.cboThreshold.Items.AddRange(new object[] {
            "0",
            "32",
            "64",
            "128",
            "196"});
            this.cboThreshold.Location = new System.Drawing.Point(469, 97);
            this.cboThreshold.Name = "cboThreshold";
            this.cboThreshold.Size = new System.Drawing.Size(49, 21);
            this.cboThreshold.TabIndex = 2;
            this.cboThreshold.Text = "128";
            // 
            // btnThreshold
            // 
            this.btnThreshold.BackColor = System.Drawing.Color.Lime;
            this.btnThreshold.Location = new System.Drawing.Point(384, 95);
            this.btnThreshold.Name = "btnThreshold";
            this.btnThreshold.Size = new System.Drawing.Size(82, 26);
            this.btnThreshold.TabIndex = 1;
            this.btnThreshold.Text = "Threshold at";
            this.btnThreshold.UseVisualStyleBackColor = false;
            this.btnThreshold.Click += new System.EventHandler(this.btnThreshold_Click);
            // 
            // pnlRoberts
            // 
            this.pnlRoberts.Controls.Add(this.chkKeepDC);
            this.pnlRoberts.Controls.Add(this.btnShowMask);
            this.pnlRoberts.Controls.Add(this.cboLaplacianMask);
            this.pnlRoberts.Controls.Add(this.lblLaplacianMask);
            this.pnlRoberts.Controls.Add(this.btnShowType);
            this.pnlRoberts.Controls.Add(this.cboRobertsType);
            this.pnlRoberts.Controls.Add(this.lblRobertsType);
            this.pnlRoberts.Controls.Add(this.cboKernelSize);
            this.pnlRoberts.Controls.Add(this.lblKernelSize);
            this.pnlRoberts.Controls.Add(this.cboPostThreshold);
            this.pnlRoberts.Controls.Add(this.lblPostThreshold);
            this.pnlRoberts.Controls.Add(this.cboPreFilter);
            this.pnlRoberts.Controls.Add(this.lblPreFilter);
            this.pnlRoberts.Location = new System.Drawing.Point(117, 13);
            this.pnlRoberts.Name = "pnlRoberts";
            this.pnlRoberts.Size = new System.Drawing.Size(354, 134);
            this.pnlRoberts.TabIndex = 0;
            // 
            // chkKeepDC
            // 
            this.chkKeepDC.AutoSize = true;
            this.chkKeepDC.Location = new System.Drawing.Point(265, 2);
            this.chkKeepDC.Name = "chkKeepDC";
            this.chkKeepDC.Size = new System.Drawing.Size(95, 17);
            this.chkKeepDC.TabIndex = 12;
            this.chkKeepDC.Text = "Add to Original";
            this.chkKeepDC.UseVisualStyleBackColor = true;
            // 
            // btnShowMask
            // 
            this.btnShowMask.Location = new System.Drawing.Point(166, 112);
            this.btnShowMask.Name = "btnShowMask";
            this.btnShowMask.Size = new System.Drawing.Size(73, 22);
            this.btnShowMask.TabIndex = 11;
            this.btnShowMask.Text = "Show Mask";
            this.btnShowMask.UseVisualStyleBackColor = true;
            this.btnShowMask.Click += new System.EventHandler(this.btnShowMask_Click);
            // 
            // cboLaplacianMask
            // 
            this.cboLaplacianMask.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cboLaplacianMask.FormattingEnabled = true;
            this.cboLaplacianMask.Items.AddRange(new object[] {
            "Mask1",
            "Mask2",
            "Mask3"});
            this.cboLaplacianMask.Location = new System.Drawing.Point(89, 112);
            this.cboLaplacianMask.Name = "cboLaplacianMask";
            this.cboLaplacianMask.Size = new System.Drawing.Size(65, 21);
            this.cboLaplacianMask.TabIndex = 10;
            // 
            // lblLaplacianMask
            // 
            this.lblLaplacianMask.AutoSize = true;
            this.lblLaplacianMask.Location = new System.Drawing.Point(0, 113);
            this.lblLaplacianMask.Name = "lblLaplacianMask";
            this.lblLaplacianMask.Size = new System.Drawing.Size(33, 13);
            this.lblLaplacianMask.TabIndex = 9;
            this.lblLaplacianMask.Text = "Mask";
            // 
            // btnShowType
            // 
            this.btnShowType.Location = new System.Drawing.Point(166, 84);
            this.btnShowType.Name = "btnShowType";
            this.btnShowType.Size = new System.Drawing.Size(73, 22);
            this.btnShowType.TabIndex = 8;
            this.btnShowType.Text = "Show Type";
            this.btnShowType.UseVisualStyleBackColor = true;
            this.btnShowType.Click += new System.EventHandler(this.btnShowType_Click);
            // 
            // cboRobertsType
            // 
            this.cboRobertsType.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cboRobertsType.FormattingEnabled = true;
            this.cboRobertsType.Items.AddRange(new object[] {
            "Type1",
            "Type2"});
            this.cboRobertsType.Location = new System.Drawing.Point(89, 84);
            this.cboRobertsType.Name = "cboRobertsType";
            this.cboRobertsType.Size = new System.Drawing.Size(65, 21);
            this.cboRobertsType.TabIndex = 7;
            // 
            // lblRobertsType
            // 
            this.lblRobertsType.AutoSize = true;
            this.lblRobertsType.Location = new System.Drawing.Point(0, 86);
            this.lblRobertsType.Name = "lblRobertsType";
            this.lblRobertsType.Size = new System.Drawing.Size(31, 13);
            this.lblRobertsType.TabIndex = 6;
            this.lblRobertsType.Text = "Type";
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
            "13",
            "15",
            "17",
            "19",
            "21"});
            this.cboKernelSize.Location = new System.Drawing.Point(89, 56);
            this.cboKernelSize.Name = "cboKernelSize";
            this.cboKernelSize.Size = new System.Drawing.Size(65, 21);
            this.cboKernelSize.TabIndex = 5;
            this.cboKernelSize.Text = "3";
            this.cboKernelSize.Validating += new System.ComponentModel.CancelEventHandler(this.cboUIntVal_Validating);
            // 
            // lblKernelSize
            // 
            this.lblKernelSize.AutoSize = true;
            this.lblKernelSize.Location = new System.Drawing.Point(0, 59);
            this.lblKernelSize.Name = "lblKernelSize";
            this.lblKernelSize.Size = new System.Drawing.Size(60, 13);
            this.lblKernelSize.TabIndex = 4;
            this.lblKernelSize.Text = "Kernel Size";
            // 
            // cboPostThreshold
            // 
            this.cboPostThreshold.FormattingEnabled = true;
            this.cboPostThreshold.Items.AddRange(new object[] {
            "No post threshold",
            "32",
            "64",
            "128",
            "196"});
            this.cboPostThreshold.Location = new System.Drawing.Point(89, 28);
            this.cboPostThreshold.Name = "cboPostThreshold";
            this.cboPostThreshold.Size = new System.Drawing.Size(150, 21);
            this.cboPostThreshold.TabIndex = 3;
            this.cboPostThreshold.Validating += new System.ComponentModel.CancelEventHandler(this.cboPostThreshold_Validating);
            // 
            // lblPostThreshold
            // 
            this.lblPostThreshold.AutoSize = true;
            this.lblPostThreshold.Location = new System.Drawing.Point(0, 32);
            this.lblPostThreshold.Name = "lblPostThreshold";
            this.lblPostThreshold.Size = new System.Drawing.Size(78, 13);
            this.lblPostThreshold.TabIndex = 2;
            this.lblPostThreshold.Text = "Post Threshold";
            // 
            // cboPreFilter
            // 
            this.cboPreFilter.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cboPreFilter.FormattingEnabled = true;
            this.cboPreFilter.Items.AddRange(new object[] {
            "none",
            "average",
            "center-weighted average",
            "gaussian1",
            "gaussian2"});
            this.cboPreFilter.Location = new System.Drawing.Point(89, 0);
            this.cboPreFilter.Name = "cboPreFilter";
            this.cboPreFilter.Size = new System.Drawing.Size(150, 21);
            this.cboPreFilter.TabIndex = 1;
            // 
            // lblPreFilter
            // 
            this.lblPreFilter.AutoSize = true;
            this.lblPreFilter.Location = new System.Drawing.Point(0, 4);
            this.lblPreFilter.Name = "lblPreFilter";
            this.lblPreFilter.Size = new System.Drawing.Size(45, 13);
            this.lblPreFilter.TabIndex = 0;
            this.lblPreFilter.Text = "PreFilter";
            // 
            // grpMarr
            // 
            this.grpMarr.Controls.Add(this.lblThresholdVal);
            this.grpMarr.Controls.Add(this.cboThresholdValue);
            this.grpMarr.Controls.Add(this.pnlMarr);
            this.grpMarr.Location = new System.Drawing.Point(8, 197);
            this.grpMarr.Name = "grpMarr";
            this.grpMarr.Size = new System.Drawing.Size(628, 124);
            this.grpMarr.TabIndex = 19;
            this.grpMarr.TabStop = false;
            // 
            // lblThresholdVal
            // 
            this.lblThresholdVal.AutoSize = true;
            this.lblThresholdVal.Location = new System.Drawing.Point(280, 97);
            this.lblThresholdVal.Name = "lblThresholdVal";
            this.lblThresholdVal.Size = new System.Drawing.Size(84, 13);
            this.lblThresholdVal.TabIndex = 2;
            this.lblThresholdVal.Text = "Theshold Value:";
            // 
            // cboThresholdValue
            // 
            this.cboThresholdValue.FormattingEnabled = true;
            this.cboThresholdValue.Items.AddRange(new object[] {
            "0",
            "10",
            "25",
            "50",
            "75",
            "100",
            "150",
            "200"});
            this.cboThresholdValue.Location = new System.Drawing.Point(374, 94);
            this.cboThresholdValue.Margin = new System.Windows.Forms.Padding(2);
            this.cboThresholdValue.Name = "cboThresholdValue";
            this.cboThresholdValue.Size = new System.Drawing.Size(92, 21);
            this.cboThresholdValue.TabIndex = 1;
            // 
            // pnlMarr
            // 
            this.pnlMarr.Controls.Add(this.chkShowImages);
            this.pnlMarr.Controls.Add(this.pnlFrieChen);
            this.pnlMarr.Controls.Add(this.pnlMarrHildreth);
            this.pnlMarr.Controls.Add(this.pnlCanny);
            this.pnlMarr.Controls.Add(this.pnlBoieCox);
            this.pnlMarr.Controls.Add(this.pnlShenCastan);
            this.pnlMarr.Location = new System.Drawing.Point(117, 13);
            this.pnlMarr.Name = "pnlMarr";
            this.pnlMarr.Size = new System.Drawing.Size(386, 77);
            this.pnlMarr.TabIndex = 0;
            // 
            // chkShowImages
            // 
            this.chkShowImages.AutoSize = true;
            this.chkShowImages.Location = new System.Drawing.Point(0, 59);
            this.chkShowImages.Name = "chkShowImages";
            this.chkShowImages.Size = new System.Drawing.Size(151, 17);
            this.chkShowImages.TabIndex = 5;
            this.chkShowImages.Text = "Show Intermediate Images";
            this.chkShowImages.UseVisualStyleBackColor = true;
            // 
            // pnlFrieChen
            // 
            this.pnlFrieChen.Controls.Add(this.cboFreiChenPostThresh);
            this.pnlFrieChen.Controls.Add(this.lblFreiChenPostThresh);
            this.pnlFrieChen.Controls.Add(this.cboThresholdAngle);
            this.pnlFrieChen.Controls.Add(this.lblThresholdAngle);
            this.pnlFrieChen.Controls.Add(this.cboProjectionMethod);
            this.pnlFrieChen.Controls.Add(this.lblProjectionMethod);
            this.pnlFrieChen.Controls.Add(this.cboFreiChenPreFilter);
            this.pnlFrieChen.Controls.Add(this.lblFreiChenPreFilter);
            this.pnlFrieChen.Controls.Add(this.chkThresholdAngle);
            this.pnlFrieChen.Controls.Add(this.chkFrieKeepDC);
            this.pnlFrieChen.Location = new System.Drawing.Point(0, 0);
            this.pnlFrieChen.Name = "pnlFrieChen";
            this.pnlFrieChen.Size = new System.Drawing.Size(365, 74);
            this.pnlFrieChen.TabIndex = 4;
            // 
            // cboFreiChenPostThresh
            // 
            this.cboFreiChenPostThresh.FormattingEnabled = true;
            this.cboFreiChenPostThresh.Items.AddRange(new object[] {
            "No post threshold",
            "32",
            "64",
            "128",
            "196"});
            this.cboFreiChenPostThresh.Location = new System.Drawing.Point(258, 53);
            this.cboFreiChenPostThresh.Name = "cboFreiChenPostThresh";
            this.cboFreiChenPostThresh.Size = new System.Drawing.Size(107, 21);
            this.cboFreiChenPostThresh.TabIndex = 9;
            // 
            // lblFreiChenPostThresh
            // 
            this.lblFreiChenPostThresh.AutoSize = true;
            this.lblFreiChenPostThresh.Location = new System.Drawing.Point(177, 58);
            this.lblFreiChenPostThresh.Name = "lblFreiChenPostThresh";
            this.lblFreiChenPostThresh.Size = new System.Drawing.Size(78, 13);
            this.lblFreiChenPostThresh.TabIndex = 8;
            this.lblFreiChenPostThresh.Text = "Post Threshold";
            // 
            // cboThresholdAngle
            // 
            this.cboThresholdAngle.FormattingEnabled = true;
            this.cboThresholdAngle.Items.AddRange(new object[] {
            "45",
            "50",
            "55",
            "60",
            "65",
            "70",
            "75",
            "80"});
            this.cboThresholdAngle.Location = new System.Drawing.Point(215, 28);
            this.cboThresholdAngle.Name = "cboThresholdAngle";
            this.cboThresholdAngle.Size = new System.Drawing.Size(65, 21);
            this.cboThresholdAngle.TabIndex = 7;
            this.cboThresholdAngle.Text = "45";
            this.cboThresholdAngle.Validating += new System.ComponentModel.CancelEventHandler(this.cboIntVal_Validating);
            // 
            // lblThresholdAngle
            // 
            this.lblThresholdAngle.AutoSize = true;
            this.lblThresholdAngle.Location = new System.Drawing.Point(126, 32);
            this.lblThresholdAngle.Name = "lblThresholdAngle";
            this.lblThresholdAngle.Size = new System.Drawing.Size(80, 13);
            this.lblThresholdAngle.TabIndex = 6;
            this.lblThresholdAngle.Text = "Value(Degrees)";
            // 
            // cboProjectionMethod
            // 
            this.cboProjectionMethod.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cboProjectionMethod.FormattingEnabled = true;
            this.cboProjectionMethod.Items.AddRange(new object[] {
            "edge subspace",
            "line subspace",
            "max(edge,line)",
            "min angle(edge,line)"});
            this.cboProjectionMethod.Location = new System.Drawing.Point(215, 0);
            this.cboProjectionMethod.Name = "cboProjectionMethod";
            this.cboProjectionMethod.Size = new System.Drawing.Size(150, 21);
            this.cboProjectionMethod.TabIndex = 5;
            this.cboProjectionMethod.SelectedIndexChanged += new System.EventHandler(this.cboProjectionMethod_SelectedIndexChanged);
            // 
            // lblProjectionMethod
            // 
            this.lblProjectionMethod.AutoSize = true;
            this.lblProjectionMethod.Location = new System.Drawing.Point(126, 4);
            this.lblProjectionMethod.Name = "lblProjectionMethod";
            this.lblProjectionMethod.Size = new System.Drawing.Size(54, 13);
            this.lblProjectionMethod.TabIndex = 4;
            this.lblProjectionMethod.Text = "Projection";
            // 
            // cboFreiChenPreFilter
            // 
            this.cboFreiChenPreFilter.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cboFreiChenPreFilter.FormattingEnabled = true;
            this.cboFreiChenPreFilter.Items.AddRange(new object[] {
            "none",
            "average",
            "center-weighted average",
            "gaussian1",
            "gaussian2"});
            this.cboFreiChenPreFilter.Location = new System.Drawing.Point(41, 53);
            this.cboFreiChenPreFilter.Name = "cboFreiChenPreFilter";
            this.cboFreiChenPreFilter.Size = new System.Drawing.Size(133, 21);
            this.cboFreiChenPreFilter.TabIndex = 3;
            // 
            // lblFreiChenPreFilter
            // 
            this.lblFreiChenPreFilter.AutoSize = true;
            this.lblFreiChenPreFilter.Location = new System.Drawing.Point(-4, 58);
            this.lblFreiChenPreFilter.Name = "lblFreiChenPreFilter";
            this.lblFreiChenPreFilter.Size = new System.Drawing.Size(45, 13);
            this.lblFreiChenPreFilter.TabIndex = 2;
            this.lblFreiChenPreFilter.Text = "PreFilter";
            // 
            // chkThresholdAngle
            // 
            this.chkThresholdAngle.AutoSize = true;
            this.chkThresholdAngle.Checked = true;
            this.chkThresholdAngle.CheckState = System.Windows.Forms.CheckState.Checked;
            this.chkThresholdAngle.Location = new System.Drawing.Point(0, 30);
            this.chkThresholdAngle.Name = "chkThresholdAngle";
            this.chkThresholdAngle.Size = new System.Drawing.Size(103, 17);
            this.chkThresholdAngle.TabIndex = 1;
            this.chkThresholdAngle.Text = "Threshold Angle";
            this.chkThresholdAngle.UseVisualStyleBackColor = true;
            this.chkThresholdAngle.CheckedChanged += new System.EventHandler(this.chkThresholdAngle_CheckedChanged);
            // 
            // chkFrieKeepDC
            // 
            this.chkFrieKeepDC.AutoSize = true;
            this.chkFrieKeepDC.Location = new System.Drawing.Point(0, 2);
            this.chkFrieKeepDC.Name = "chkFrieKeepDC";
            this.chkFrieKeepDC.Size = new System.Drawing.Size(69, 17);
            this.chkFrieKeepDC.TabIndex = 0;
            this.chkFrieKeepDC.Text = "Keep DC";
            this.chkFrieKeepDC.UseVisualStyleBackColor = true;
            // 
            // pnlMarrHildreth
            // 
            this.pnlMarrHildreth.Controls.Add(this.chkCombineBands);
            this.pnlMarrHildreth.Controls.Add(this.cboMarrDelta);
            this.pnlMarrHildreth.Controls.Add(this.lblMarrDelta);
            this.pnlMarrHildreth.Controls.Add(this.cboMarrSigma);
            this.pnlMarrHildreth.Controls.Add(this.lblMarrSigma);
            this.pnlMarrHildreth.Controls.Add(this.rbDualVariance);
            this.pnlMarrHildreth.Controls.Add(this.rbSingleVariance);
            this.pnlMarrHildreth.Location = new System.Drawing.Point(0, 0);
            this.pnlMarrHildreth.Name = "pnlMarrHildreth";
            this.pnlMarrHildreth.Size = new System.Drawing.Size(354, 49);
            this.pnlMarrHildreth.TabIndex = 3;
            // 
            // chkCombineBands
            // 
            this.chkCombineBands.AutoSize = true;
            this.chkCombineBands.Location = new System.Drawing.Point(132, 32);
            this.chkCombineBands.Name = "chkCombineBands";
            this.chkCombineBands.Size = new System.Drawing.Size(187, 17);
            this.chkCombineBands.TabIndex = 6;
            this.chkCombineBands.Text = "Post-Process by Combining Bands";
            this.chkCombineBands.UseVisualStyleBackColor = true;
            // 
            // cboMarrDelta
            // 
            this.cboMarrDelta.FormattingEnabled = true;
            this.cboMarrDelta.Items.AddRange(new object[] {
            "0.2",
            "0.4",
            "0.6",
            "0.8",
            "1.0"});
            this.cboMarrDelta.Location = new System.Drawing.Point(301, 0);
            this.cboMarrDelta.Name = "cboMarrDelta";
            this.cboMarrDelta.Size = new System.Drawing.Size(53, 21);
            this.cboMarrDelta.TabIndex = 5;
            this.cboMarrDelta.Text = "0.8";
            this.cboMarrDelta.Validating += new System.ComponentModel.CancelEventHandler(this.cboMarrDelta_Validating);
            // 
            // lblMarrDelta
            // 
            this.lblMarrDelta.AutoSize = true;
            this.lblMarrDelta.Location = new System.Drawing.Point(258, 4);
            this.lblMarrDelta.Name = "lblMarrDelta";
            this.lblMarrDelta.Size = new System.Drawing.Size(32, 13);
            this.lblMarrDelta.TabIndex = 4;
            this.lblMarrDelta.Text = "Delta";
            // 
            // cboMarrSigma
            // 
            this.cboMarrSigma.FormattingEnabled = true;
            this.cboMarrSigma.Items.AddRange(new object[] {
            "1.0",
            "1.2",
            "1.5",
            "2.0",
            "2.2",
            "2.5",
            "3.0",
            "3.2",
            "3.5",
            "4.0"});
            this.cboMarrSigma.Location = new System.Drawing.Point(174, 0);
            this.cboMarrSigma.Name = "cboMarrSigma";
            this.cboMarrSigma.Size = new System.Drawing.Size(53, 21);
            this.cboMarrSigma.TabIndex = 3;
            this.cboMarrSigma.Text = "2.0";
            this.cboMarrSigma.Validating += new System.ComponentModel.CancelEventHandler(this.cboFloatVal_Validating);
            // 
            // lblMarrSigma
            // 
            this.lblMarrSigma.AutoSize = true;
            this.lblMarrSigma.Location = new System.Drawing.Point(129, 4);
            this.lblMarrSigma.Name = "lblMarrSigma";
            this.lblMarrSigma.Size = new System.Drawing.Size(36, 13);
            this.lblMarrSigma.TabIndex = 2;
            this.lblMarrSigma.Text = "Sigma";
            // 
            // rbDualVariance
            // 
            this.rbDualVariance.AutoSize = true;
            this.rbDualVariance.Location = new System.Drawing.Point(0, 32);
            this.rbDualVariance.Name = "rbDualVariance";
            this.rbDualVariance.Size = new System.Drawing.Size(92, 17);
            this.rbDualVariance.TabIndex = 1;
            this.rbDualVariance.Text = "Dual Variance";
            this.rbDualVariance.UseVisualStyleBackColor = true;
            this.rbDualVariance.CheckedChanged += new System.EventHandler(this.rbMarrVariance_CheckedChanged);
            // 
            // rbSingleVariance
            // 
            this.rbSingleVariance.AutoSize = true;
            this.rbSingleVariance.Checked = true;
            this.rbSingleVariance.Location = new System.Drawing.Point(0, 4);
            this.rbSingleVariance.Name = "rbSingleVariance";
            this.rbSingleVariance.Size = new System.Drawing.Size(99, 17);
            this.rbSingleVariance.TabIndex = 0;
            this.rbSingleVariance.TabStop = true;
            this.rbSingleVariance.Text = "Single Variance";
            this.rbSingleVariance.UseVisualStyleBackColor = true;
            this.rbSingleVariance.CheckedChanged += new System.EventHandler(this.rbMarrVariance_CheckedChanged);
            // 
            // pnlCanny
            // 
            this.pnlCanny.Controls.Add(this.cboCannyVariance);
            this.pnlCanny.Controls.Add(this.lblCannyVariance);
            this.pnlCanny.Controls.Add(this.cboCannyHiThresh);
            this.pnlCanny.Controls.Add(this.lblCannyHiThresh);
            this.pnlCanny.Controls.Add(this.cboCannyLoThresh);
            this.pnlCanny.Controls.Add(this.lblCannyLoThresh);
            this.pnlCanny.Location = new System.Drawing.Point(0, 0);
            this.pnlCanny.Name = "pnlCanny";
            this.pnlCanny.Size = new System.Drawing.Size(350, 49);
            this.pnlCanny.TabIndex = 2;
            // 
            // cboCannyVariance
            // 
            this.cboCannyVariance.FormattingEnabled = true;
            this.cboCannyVariance.Items.AddRange(new object[] {
            "0.5",
            "1.0",
            "1.5",
            "2.0",
            "2.5",
            "3.0",
            "3.5",
            "4.0",
            "4.5",
            "5.0"});
            this.cboCannyVariance.Location = new System.Drawing.Point(290, 0);
            this.cboCannyVariance.Name = "cboCannyVariance";
            this.cboCannyVariance.Size = new System.Drawing.Size(43, 21);
            this.cboCannyVariance.TabIndex = 5;
            this.cboCannyVariance.Text = "0.5";
            this.cboCannyVariance.Validating += new System.ComponentModel.CancelEventHandler(this.cboVarianceValue_Validating);
            // 
            // lblCannyVariance
            // 
            this.lblCannyVariance.AutoSize = true;
            this.lblCannyVariance.Location = new System.Drawing.Point(180, 4);
            this.lblCannyVariance.Name = "lblCannyVariance";
            this.lblCannyVariance.Size = new System.Drawing.Size(98, 13);
            this.lblCannyVariance.TabIndex = 4;
            this.lblCannyVariance.Text = "Standard Deviation";
            // 
            // cboCannyHiThresh
            // 
            this.cboCannyHiThresh.FormattingEnabled = true;
            this.cboCannyHiThresh.Items.AddRange(new object[] {
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
            this.cboCannyHiThresh.Location = new System.Drawing.Point(114, 28);
            this.cboCannyHiThresh.Name = "cboCannyHiThresh";
            this.cboCannyHiThresh.Size = new System.Drawing.Size(48, 21);
            this.cboCannyHiThresh.TabIndex = 3;
            this.cboCannyHiThresh.Text = "1.0";
            this.cboCannyHiThresh.Validating += new System.ComponentModel.CancelEventHandler(this.cboThresholdValue_Validating);
            // 
            // lblCannyHiThresh
            // 
            this.lblCannyHiThresh.AutoSize = true;
            this.lblCannyHiThresh.Location = new System.Drawing.Point(0, 32);
            this.lblCannyHiThresh.Name = "lblCannyHiThresh";
            this.lblCannyHiThresh.Size = new System.Drawing.Size(105, 13);
            this.lblCannyHiThresh.TabIndex = 2;
            this.lblCannyHiThresh.Text = "High threshold factor";
            // 
            // cboCannyLoThresh
            // 
            this.cboCannyLoThresh.FormattingEnabled = true;
            this.cboCannyLoThresh.Items.AddRange(new object[] {
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
            this.cboCannyLoThresh.Location = new System.Drawing.Point(114, 0);
            this.cboCannyLoThresh.Name = "cboCannyLoThresh";
            this.cboCannyLoThresh.Size = new System.Drawing.Size(48, 21);
            this.cboCannyLoThresh.TabIndex = 1;
            this.cboCannyLoThresh.Text = "1.0";
            this.cboCannyLoThresh.Validating += new System.ComponentModel.CancelEventHandler(this.cboThresholdValue_Validating);
            // 
            // lblCannyLoThresh
            // 
            this.lblCannyLoThresh.AutoSize = true;
            this.lblCannyLoThresh.Location = new System.Drawing.Point(0, 4);
            this.lblCannyLoThresh.Name = "lblCannyLoThresh";
            this.lblCannyLoThresh.Size = new System.Drawing.Size(103, 13);
            this.lblCannyLoThresh.TabIndex = 0;
            this.lblCannyLoThresh.Text = "Low threshold factor";
            // 
            // pnlBoieCox
            // 
            this.pnlBoieCox.Controls.Add(this.chkThinEdge);
            this.pnlBoieCox.Controls.Add(this.cboBoieVariance);
            this.pnlBoieCox.Controls.Add(this.lblBoieVariance);
            this.pnlBoieCox.Controls.Add(this.cboBoieHiThresh);
            this.pnlBoieCox.Controls.Add(this.lblBoieHiThresh);
            this.pnlBoieCox.Controls.Add(this.cboBoieLoThresh);
            this.pnlBoieCox.Controls.Add(this.lblBoieLoThresh);
            this.pnlBoieCox.Controls.Add(this.rbHysteresisThreshold);
            this.pnlBoieCox.Controls.Add(this.rbOrdinaryThreshold);
            this.pnlBoieCox.Location = new System.Drawing.Point(0, 0);
            this.pnlBoieCox.Name = "pnlBoieCox";
            this.pnlBoieCox.Size = new System.Drawing.Size(470, 49);
            this.pnlBoieCox.TabIndex = 1;
            // 
            // chkThinEdge
            // 
            this.chkThinEdge.AutoSize = true;
            this.chkThinEdge.Location = new System.Drawing.Point(292, 30);
            this.chkThinEdge.Name = "chkThinEdge";
            this.chkThinEdge.RightToLeft = System.Windows.Forms.RightToLeft.Yes;
            this.chkThinEdge.Size = new System.Drawing.Size(94, 17);
            this.chkThinEdge.TabIndex = 8;
            this.chkThinEdge.Text = "Thinning edge";
            this.chkThinEdge.UseVisualStyleBackColor = true;
            // 
            // cboBoieVariance
            // 
            this.cboBoieVariance.FormattingEnabled = true;
            this.cboBoieVariance.Items.AddRange(new object[] {
            "0.5",
            "1.0",
            "2.0",
            "3.0",
            "4.0",
            "5.0"});
            this.cboBoieVariance.Location = new System.Drawing.Point(232, 0);
            this.cboBoieVariance.Name = "cboBoieVariance";
            this.cboBoieVariance.Size = new System.Drawing.Size(43, 21);
            this.cboBoieVariance.TabIndex = 7;
            this.cboBoieVariance.Text = "1.0";
            this.cboBoieVariance.Validating += new System.ComponentModel.CancelEventHandler(this.cboVarianceValue_Validating);
            // 
            // lblBoieVariance
            // 
            this.lblBoieVariance.AutoSize = true;
            this.lblBoieVariance.Location = new System.Drawing.Point(123, 0);
            this.lblBoieVariance.Name = "lblBoieVariance";
            this.lblBoieVariance.Size = new System.Drawing.Size(98, 13);
            this.lblBoieVariance.TabIndex = 6;
            this.lblBoieVariance.Text = "Standard Deviation";
            // 
            // cboBoieHiThresh
            // 
            this.cboBoieHiThresh.FormattingEnabled = true;
            this.cboBoieHiThresh.Items.AddRange(new object[] {
            "0.5",
            "1.0",
            "2.0",
            "3.0",
            "4.0",
            "5.0",
            "6.0",
            "7.0",
            "8.0",
            "9.0"});
            this.cboBoieHiThresh.Location = new System.Drawing.Point(232, 28);
            this.cboBoieHiThresh.Name = "cboBoieHiThresh";
            this.cboBoieHiThresh.Size = new System.Drawing.Size(48, 21);
            this.cboBoieHiThresh.TabIndex = 5;
            this.cboBoieHiThresh.Text = "1.0";
            this.cboBoieHiThresh.Validating += new System.ComponentModel.CancelEventHandler(this.cboThresholdValue_Validating);
            // 
            // lblBoieHiThresh
            // 
            this.lblBoieHiThresh.AutoSize = true;
            this.lblBoieHiThresh.Location = new System.Drawing.Point(123, 32);
            this.lblBoieHiThresh.Name = "lblBoieHiThresh";
            this.lblBoieHiThresh.Size = new System.Drawing.Size(105, 13);
            this.lblBoieHiThresh.TabIndex = 4;
            this.lblBoieHiThresh.Text = "High threshold factor";
            // 
            // cboBoieLoThresh
            // 
            this.cboBoieLoThresh.FormattingEnabled = true;
            this.cboBoieLoThresh.Items.AddRange(new object[] {
            "0.1",
            "0.2",
            "0.3",
            "0.4",
            "0.5",
            "0.6",
            "0.7",
            "0.8",
            "0.9",
            "1.0"});
            this.cboBoieLoThresh.Location = new System.Drawing.Point(232, 0);
            this.cboBoieLoThresh.Name = "cboBoieLoThresh";
            this.cboBoieLoThresh.Size = new System.Drawing.Size(48, 21);
            this.cboBoieLoThresh.TabIndex = 3;
            this.cboBoieLoThresh.Text = "0.2";
            this.cboBoieLoThresh.Validating += new System.ComponentModel.CancelEventHandler(this.cboThresholdValue_Validating);
            // 
            // lblBoieLoThresh
            // 
            this.lblBoieLoThresh.AutoSize = true;
            this.lblBoieLoThresh.Location = new System.Drawing.Point(123, 4);
            this.lblBoieLoThresh.Name = "lblBoieLoThresh";
            this.lblBoieLoThresh.Size = new System.Drawing.Size(103, 13);
            this.lblBoieLoThresh.TabIndex = 2;
            this.lblBoieLoThresh.Text = "Low threshold factor";
            // 
            // rbHysteresisThreshold
            // 
            this.rbHysteresisThreshold.AutoSize = true;
            this.rbHysteresisThreshold.Location = new System.Drawing.Point(0, 32);
            this.rbHysteresisThreshold.Name = "rbHysteresisThreshold";
            this.rbHysteresisThreshold.Size = new System.Drawing.Size(115, 17);
            this.rbHysteresisThreshold.TabIndex = 1;
            this.rbHysteresisThreshold.Text = "Hysterisis threshold";
            this.rbHysteresisThreshold.UseVisualStyleBackColor = true;
            this.rbHysteresisThreshold.CheckedChanged += new System.EventHandler(this.rbBoieThreshold_CheckedChanged);
            // 
            // rbOrdinaryThreshold
            // 
            this.rbOrdinaryThreshold.AutoSize = true;
            this.rbOrdinaryThreshold.Checked = true;
            this.rbOrdinaryThreshold.Location = new System.Drawing.Point(0, 2);
            this.rbOrdinaryThreshold.Name = "rbOrdinaryThreshold";
            this.rbOrdinaryThreshold.Size = new System.Drawing.Size(110, 17);
            this.rbOrdinaryThreshold.TabIndex = 0;
            this.rbOrdinaryThreshold.TabStop = true;
            this.rbOrdinaryThreshold.Text = "Ordinary threshold";
            this.rbOrdinaryThreshold.UseVisualStyleBackColor = true;
            this.rbOrdinaryThreshold.CheckedChanged += new System.EventHandler(this.rbBoieThreshold_CheckedChanged);
            // 
            // pnlShenCastan
            // 
            this.pnlShenCastan.Controls.Add(this.cboThinFactor);
            this.pnlShenCastan.Controls.Add(this.lblThinFactor);
            this.pnlShenCastan.Controls.Add(this.cboWindowSize);
            this.pnlShenCastan.Controls.Add(this.lblWindowSize);
            this.pnlShenCastan.Controls.Add(this.cboSmoothingFactor);
            this.pnlShenCastan.Controls.Add(this.lblSmoothingFactor);
            this.pnlShenCastan.Controls.Add(this.cboShenHiThresh);
            this.pnlShenCastan.Controls.Add(this.lblShenHiThresh);
            this.pnlShenCastan.Controls.Add(this.cboShenLoThresh);
            this.pnlShenCastan.Controls.Add(this.lblShenLoThresh);
            this.pnlShenCastan.Location = new System.Drawing.Point(0, 0);
            this.pnlShenCastan.Name = "pnlShenCastan";
            this.pnlShenCastan.Size = new System.Drawing.Size(347, 77);
            this.pnlShenCastan.TabIndex = 0;
            // 
            // cboThinFactor
            // 
            this.cboThinFactor.FormattingEnabled = true;
            this.cboThinFactor.Items.AddRange(new object[] {
            "1",
            "2",
            "3",
            "4",
            "5",
            "6"});
            this.cboThinFactor.Location = new System.Drawing.Point(304, 56);
            this.cboThinFactor.Name = "cboThinFactor";
            this.cboThinFactor.Size = new System.Drawing.Size(43, 21);
            this.cboThinFactor.TabIndex = 9;
            this.cboThinFactor.Text = "1";
            this.cboThinFactor.Validating += new System.ComponentModel.CancelEventHandler(this.cboIntVal_Validating);
            // 
            // lblThinFactor
            // 
            this.lblThinFactor.AutoSize = true;
            this.lblThinFactor.Location = new System.Drawing.Point(200, 60);
            this.lblThinFactor.Name = "lblThinFactor";
            this.lblThinFactor.Size = new System.Drawing.Size(58, 13);
            this.lblThinFactor.TabIndex = 8;
            this.lblThinFactor.Text = "Thin factor";
            // 
            // cboWindowSize
            // 
            this.cboWindowSize.FormattingEnabled = true;
            this.cboWindowSize.Items.AddRange(new object[] {
            "3",
            "5",
            "7"});
            this.cboWindowSize.Location = new System.Drawing.Point(304, 28);
            this.cboWindowSize.Name = "cboWindowSize";
            this.cboWindowSize.Size = new System.Drawing.Size(43, 21);
            this.cboWindowSize.TabIndex = 7;
            this.cboWindowSize.Text = "5";
            this.cboWindowSize.Validating += new System.ComponentModel.CancelEventHandler(this.cboIntVal_Validating);
            // 
            // lblWindowSize
            // 
            this.lblWindowSize.AutoSize = true;
            this.lblWindowSize.Location = new System.Drawing.Point(200, 32);
            this.lblWindowSize.Name = "lblWindowSize";
            this.lblWindowSize.Size = new System.Drawing.Size(67, 13);
            this.lblWindowSize.TabIndex = 6;
            this.lblWindowSize.Text = "Window size";
            // 
            // cboSmoothingFactor
            // 
            this.cboSmoothingFactor.FormattingEnabled = true;
            this.cboSmoothingFactor.Items.AddRange(new object[] {
            "0.5",
            "0.6",
            "0.7",
            "0.8",
            "0.9"});
            this.cboSmoothingFactor.Location = new System.Drawing.Point(304, 0);
            this.cboSmoothingFactor.Name = "cboSmoothingFactor";
            this.cboSmoothingFactor.Size = new System.Drawing.Size(43, 21);
            this.cboSmoothingFactor.TabIndex = 5;
            this.cboSmoothingFactor.Text = "0.9";
            this.cboSmoothingFactor.Validating += new System.ComponentModel.CancelEventHandler(this.cboSmoothingFactor_Validating);
            // 
            // lblSmoothingFactor
            // 
            this.lblSmoothingFactor.AutoSize = true;
            this.lblSmoothingFactor.Location = new System.Drawing.Point(200, 4);
            this.lblSmoothingFactor.Name = "lblSmoothingFactor";
            this.lblSmoothingFactor.Size = new System.Drawing.Size(87, 13);
            this.lblSmoothingFactor.TabIndex = 4;
            this.lblSmoothingFactor.Text = "Smoothing factor";
            // 
            // cboShenHiThresh
            // 
            this.cboShenHiThresh.FormattingEnabled = true;
            this.cboShenHiThresh.Items.AddRange(new object[] {
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
            this.cboShenHiThresh.Location = new System.Drawing.Point(114, 28);
            this.cboShenHiThresh.Name = "cboShenHiThresh";
            this.cboShenHiThresh.Size = new System.Drawing.Size(48, 21);
            this.cboShenHiThresh.TabIndex = 3;
            this.cboShenHiThresh.Text = "1.0";
            this.cboShenHiThresh.Validating += new System.ComponentModel.CancelEventHandler(this.cboThresholdValue_Validating);
            // 
            // lblShenHiThresh
            // 
            this.lblShenHiThresh.AutoSize = true;
            this.lblShenHiThresh.Location = new System.Drawing.Point(0, 32);
            this.lblShenHiThresh.Name = "lblShenHiThresh";
            this.lblShenHiThresh.Size = new System.Drawing.Size(105, 13);
            this.lblShenHiThresh.TabIndex = 2;
            this.lblShenHiThresh.Text = "High threshold factor";
            // 
            // cboShenLoThresh
            // 
            this.cboShenLoThresh.FormattingEnabled = true;
            this.cboShenLoThresh.Items.AddRange(new object[] {
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
            this.cboShenLoThresh.Location = new System.Drawing.Point(114, 0);
            this.cboShenLoThresh.Name = "cboShenLoThresh";
            this.cboShenLoThresh.Size = new System.Drawing.Size(48, 21);
            this.cboShenLoThresh.TabIndex = 1;
            this.cboShenLoThresh.Text = "1.0";
            this.cboShenLoThresh.Validating += new System.ComponentModel.CancelEventHandler(this.cboThresholdValue_Validating);
            // 
            // lblShenLoThresh
            // 
            this.lblShenLoThresh.AutoSize = true;
            this.lblShenLoThresh.Location = new System.Drawing.Point(0, 4);
            this.lblShenLoThresh.Name = "lblShenLoThresh";
            this.lblShenLoThresh.Size = new System.Drawing.Size(103, 13);
            this.lblShenLoThresh.TabIndex = 0;
            this.lblShenLoThresh.Text = "Low threshold factor";
            // 
            // grpMoravec
            // 
            this.grpMoravec.Controls.Add(this.pnlMoravec);
            this.grpMoravec.Location = new System.Drawing.Point(8, 324);
            this.grpMoravec.Name = "grpMoravec";
            this.grpMoravec.Size = new System.Drawing.Size(628, 132);
            this.grpMoravec.TabIndex = 20;
            this.grpMoravec.TabStop = false;
            // 
            // pnlMoravec
            // 
            this.pnlMoravec.Controls.Add(this.pnlMoravecDetector);
            this.pnlMoravec.Controls.Add(this.pnlEdgeLink);
            this.pnlMoravec.Controls.Add(this.pnlPratt);
            this.pnlMoravec.Controls.Add(this.pnlHarris);
            this.pnlMoravec.Controls.Add(this.pnlHough);
            this.pnlMoravec.Location = new System.Drawing.Point(117, 15);
            this.pnlMoravec.Name = "pnlMoravec";
            this.pnlMoravec.Size = new System.Drawing.Size(377, 107);
            this.pnlMoravec.TabIndex = 0;
            // 
            // pnlMoravecDetector
            // 
            this.pnlMoravecDetector.Controls.Add(this.cboMoravecThreshold);
            this.pnlMoravecDetector.Controls.Add(this.lblMoravecThreshold);
            this.pnlMoravecDetector.Location = new System.Drawing.Point(0, 0);
            this.pnlMoravecDetector.Name = "pnlMoravecDetector";
            this.pnlMoravecDetector.Size = new System.Drawing.Size(144, 21);
            this.pnlMoravecDetector.TabIndex = 4;
            // 
            // cboMoravecThreshold
            // 
            this.cboMoravecThreshold.FormattingEnabled = true;
            this.cboMoravecThreshold.Items.AddRange(new object[] {
            "32.0",
            "64.0",
            "128.0",
            "196.0"});
            this.cboMoravecThreshold.Location = new System.Drawing.Point(72, 0);
            this.cboMoravecThreshold.Name = "cboMoravecThreshold";
            this.cboMoravecThreshold.Size = new System.Drawing.Size(72, 21);
            this.cboMoravecThreshold.TabIndex = 1;
            this.cboMoravecThreshold.Text = "32.0";
            this.cboMoravecThreshold.Validating += new System.ComponentModel.CancelEventHandler(this.cboFloatVal_Validating);
            // 
            // lblMoravecThreshold
            // 
            this.lblMoravecThreshold.AutoSize = true;
            this.lblMoravecThreshold.Location = new System.Drawing.Point(0, 4);
            this.lblMoravecThreshold.Name = "lblMoravecThreshold";
            this.lblMoravecThreshold.Size = new System.Drawing.Size(54, 13);
            this.lblMoravecThreshold.TabIndex = 0;
            this.lblMoravecThreshold.Text = "Threshold";
            // 
            // pnlEdgeLink
            // 
            this.pnlEdgeLink.Controls.Add(this.cboEdgeLinkConnectDistance);
            this.pnlEdgeLink.Controls.Add(this.lblEdgeLinkConnectDistance);
            this.pnlEdgeLink.Location = new System.Drawing.Point(0, 0);
            this.pnlEdgeLink.Name = "pnlEdgeLink";
            this.pnlEdgeLink.Size = new System.Drawing.Size(174, 21);
            this.pnlEdgeLink.TabIndex = 3;
            // 
            // cboEdgeLinkConnectDistance
            // 
            this.cboEdgeLinkConnectDistance.FormattingEnabled = true;
            this.cboEdgeLinkConnectDistance.Items.AddRange(new object[] {
            "1",
            "2",
            "5",
            "10",
            "15",
            "20"});
            this.cboEdgeLinkConnectDistance.Location = new System.Drawing.Point(126, 0);
            this.cboEdgeLinkConnectDistance.Name = "cboEdgeLinkConnectDistance";
            this.cboEdgeLinkConnectDistance.Size = new System.Drawing.Size(48, 21);
            this.cboEdgeLinkConnectDistance.TabIndex = 1;
            this.cboEdgeLinkConnectDistance.Text = "2";
            this.cboEdgeLinkConnectDistance.Validating += new System.ComponentModel.CancelEventHandler(this.cboUIntVal_Validating);
            // 
            // lblEdgeLinkConnectDistance
            // 
            this.lblEdgeLinkConnectDistance.AutoSize = true;
            this.lblEdgeLinkConnectDistance.Location = new System.Drawing.Point(0, 4);
            this.lblEdgeLinkConnectDistance.Name = "lblEdgeLinkConnectDistance";
            this.lblEdgeLinkConnectDistance.Size = new System.Drawing.Size(120, 13);
            this.lblEdgeLinkConnectDistance.TabIndex = 0;
            this.lblEdgeLinkConnectDistance.Text = "Connect Distance (max)";
            // 
            // pnlPratt
            // 
            this.pnlPratt.Controls.Add(this.txtCurrentImg);
            this.pnlPratt.Controls.Add(this.cboSecondImg);
            this.pnlPratt.Controls.Add(this.txtPrattResultGS);
            this.pnlPratt.Controls.Add(this.pnlPrattResultRGB);
            this.pnlPratt.Controls.Add(this.lblPrattResult);
            this.pnlPratt.Controls.Add(this.cboScaleFactor);
            this.pnlPratt.Controls.Add(this.lblScaleFactor);
            this.pnlPratt.Controls.Add(this.lblEdgeDetectImage);
            this.pnlPratt.Controls.Add(this.lblIdealImage);
            this.pnlPratt.Location = new System.Drawing.Point(0, 0);
            this.pnlPratt.Name = "pnlPratt";
            this.pnlPratt.Size = new System.Drawing.Size(377, 107);
            this.pnlPratt.TabIndex = 2;
            // 
            // txtCurrentImg
            // 
            this.txtCurrentImg.AutoSize = true;
            this.txtCurrentImg.ForeColor = System.Drawing.Color.Blue;
            this.txtCurrentImg.Location = new System.Drawing.Point(116, 4);
            this.txtCurrentImg.Name = "txtCurrentImg";
            this.txtCurrentImg.Size = new System.Drawing.Size(82, 13);
            this.txtCurrentImg.TabIndex = 10;
            this.txtCurrentImg.Text = "Current Image...";
            // 
            // cboSecondImg
            // 
            this.cboSecondImg.DisplayMember = "Text";
            this.cboSecondImg.DrawMode = System.Windows.Forms.DrawMode.OwnerDrawFixed;
            this.cboSecondImg.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cboSecondImg.FormattingEnabled = true;
            this.cboSecondImg.Location = new System.Drawing.Point(120, 25);
            this.cboSecondImg.Name = "cboSecondImg";
            this.cboSecondImg.Size = new System.Drawing.Size(245, 21);
            this.cboSecondImg.TabIndex = 9;
            this.cboSecondImg.DrawItem += new System.Windows.Forms.DrawItemEventHandler(this.cboSecondImage_DrawItem);
            this.cboSecondImg.SelectedIndexChanged += new System.EventHandler(this.cboSecondImage_SelectedIndexChanged);
            // 
            // txtPrattResultGS
            // 
            this.txtPrattResultGS.BackColor = System.Drawing.Color.White;
            this.txtPrattResultGS.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.txtPrattResultGS.Location = new System.Drawing.Point(203, 71);
            this.txtPrattResultGS.Name = "txtPrattResultGS";
            this.txtPrattResultGS.Size = new System.Drawing.Size(63, 21);
            this.txtPrattResultGS.TabIndex = 8;
            this.txtPrattResultGS.Text = "Working...";
            this.txtPrattResultGS.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // pnlPrattResultRGB
            // 
            this.pnlPrattResultRGB.BackColor = System.Drawing.Color.White;
            this.pnlPrattResultRGB.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.pnlPrattResultRGB.Controls.Add(this.txtPrattResultB);
            this.pnlPrattResultRGB.Controls.Add(this.txtPrattResultG);
            this.pnlPrattResultRGB.Controls.Add(this.txtPrattResultR);
            this.pnlPrattResultRGB.Location = new System.Drawing.Point(203, 56);
            this.pnlPrattResultRGB.Name = "pnlPrattResultRGB";
            this.pnlPrattResultRGB.Size = new System.Drawing.Size(63, 51);
            this.pnlPrattResultRGB.TabIndex = 7;
            // 
            // txtPrattResultB
            // 
            this.txtPrattResultB.AutoSize = true;
            this.txtPrattResultB.ForeColor = System.Drawing.Color.Blue;
            this.txtPrattResultB.Location = new System.Drawing.Point(3, 34);
            this.txtPrattResultB.Name = "txtPrattResultB";
            this.txtPrattResultB.Size = new System.Drawing.Size(52, 13);
            this.txtPrattResultB.TabIndex = 2;
            this.txtPrattResultB.Text = "0.000000";
            // 
            // txtPrattResultG
            // 
            this.txtPrattResultG.AutoSize = true;
            this.txtPrattResultG.ForeColor = System.Drawing.Color.Green;
            this.txtPrattResultG.Location = new System.Drawing.Point(3, 18);
            this.txtPrattResultG.Name = "txtPrattResultG";
            this.txtPrattResultG.Size = new System.Drawing.Size(52, 13);
            this.txtPrattResultG.TabIndex = 1;
            this.txtPrattResultG.Text = "0.000000";
            // 
            // txtPrattResultR
            // 
            this.txtPrattResultR.AutoSize = true;
            this.txtPrattResultR.ForeColor = System.Drawing.Color.Red;
            this.txtPrattResultR.Location = new System.Drawing.Point(3, 2);
            this.txtPrattResultR.Name = "txtPrattResultR";
            this.txtPrattResultR.Size = new System.Drawing.Size(52, 13);
            this.txtPrattResultR.TabIndex = 0;
            this.txtPrattResultR.Text = "0.000000";
            // 
            // lblPrattResult
            // 
            this.lblPrattResult.AutoSize = true;
            this.lblPrattResult.Location = new System.Drawing.Point(161, 75);
            this.lblPrattResult.Name = "lblPrattResult";
            this.lblPrattResult.Size = new System.Drawing.Size(37, 13);
            this.lblPrattResult.TabIndex = 6;
            this.lblPrattResult.Text = "Result";
            // 
            // cboScaleFactor
            // 
            this.cboScaleFactor.FormattingEnabled = true;
            this.cboScaleFactor.Items.AddRange(new object[] {
            "1/9",
            "1/7",
            "1/5",
            "1/3",
            "1/2",
            "1"});
            this.cboScaleFactor.Location = new System.Drawing.Point(72, 56);
            this.cboScaleFactor.Name = "cboScaleFactor";
            this.cboScaleFactor.Size = new System.Drawing.Size(67, 21);
            this.cboScaleFactor.TabIndex = 5;
            // 
            // lblScaleFactor
            // 
            this.lblScaleFactor.AutoSize = true;
            this.lblScaleFactor.Location = new System.Drawing.Point(0, 60);
            this.lblScaleFactor.Name = "lblScaleFactor";
            this.lblScaleFactor.Size = new System.Drawing.Size(67, 13);
            this.lblScaleFactor.TabIndex = 4;
            this.lblScaleFactor.Text = "Scale Factor";
            // 
            // lblEdgeDetectImage
            // 
            this.lblEdgeDetectImage.AutoSize = true;
            this.lblEdgeDetectImage.Location = new System.Drawing.Point(0, 32);
            this.lblEdgeDetectImage.Name = "lblEdgeDetectImage";
            this.lblEdgeDetectImage.Size = new System.Drawing.Size(113, 13);
            this.lblEdgeDetectImage.TabIndex = 2;
            this.lblEdgeDetectImage.Text = "Edge Detection Image";
            // 
            // lblIdealImage
            // 
            this.lblIdealImage.AutoSize = true;
            this.lblIdealImage.Location = new System.Drawing.Point(0, 4);
            this.lblIdealImage.Name = "lblIdealImage";
            this.lblIdealImage.Size = new System.Drawing.Size(90, 13);
            this.lblIdealImage.TabIndex = 0;
            this.lblIdealImage.Text = "Ideal Edge Image";
            // 
            // pnlHarris
            // 
            this.pnlHarris.Controls.Add(this.cboHarrisMinDistance);
            this.pnlHarris.Controls.Add(this.lblHarrisMinDistance);
            this.pnlHarris.Controls.Add(this.cboHarrisAlpha);
            this.pnlHarris.Controls.Add(this.lblHarrisAlpha);
            this.pnlHarris.Controls.Add(this.cboHarrisBorder);
            this.pnlHarris.Controls.Add(this.lblHarrisBorder);
            this.pnlHarris.Controls.Add(this.cboHarrisThreshold);
            this.pnlHarris.Controls.Add(this.lblHarrisThreshold);
            this.pnlHarris.Location = new System.Drawing.Point(0, 0);
            this.pnlHarris.Name = "pnlHarris";
            this.pnlHarris.Size = new System.Drawing.Size(331, 49);
            this.pnlHarris.TabIndex = 1;
            // 
            // cboHarrisMinDistance
            // 
            this.cboHarrisMinDistance.FormattingEnabled = true;
            this.cboHarrisMinDistance.Items.AddRange(new object[] {
            "20.0",
            "15.0",
            "10.0",
            "9.0",
            "8.0",
            "7.0",
            "6.0",
            "5.0",
            "4.0",
            "3.0",
            "2.0",
            "1.0"});
            this.cboHarrisMinDistance.Location = new System.Drawing.Point(259, 28);
            this.cboHarrisMinDistance.Name = "cboHarrisMinDistance";
            this.cboHarrisMinDistance.Size = new System.Drawing.Size(72, 21);
            this.cboHarrisMinDistance.TabIndex = 7;
            this.cboHarrisMinDistance.Text = "10.0";
            this.cboHarrisMinDistance.Validating += new System.ComponentModel.CancelEventHandler(this.cboFloatVal_Validating);
            // 
            // lblHarrisMinDistance
            // 
            this.lblHarrisMinDistance.AutoSize = true;
            this.lblHarrisMinDistance.Location = new System.Drawing.Point(155, 32);
            this.lblHarrisMinDistance.Name = "lblHarrisMinDistance";
            this.lblHarrisMinDistance.Size = new System.Drawing.Size(93, 13);
            this.lblHarrisMinDistance.TabIndex = 6;
            this.lblHarrisMinDistance.Text = "Minimum Distance";
            // 
            // cboHarrisAlpha
            // 
            this.cboHarrisAlpha.FormattingEnabled = true;
            this.cboHarrisAlpha.Items.AddRange(new object[] {
            "0.5",
            "0.4",
            "0.3",
            "0.2",
            "0.1",
            "0.05",
            "0.04",
            "0.03",
            "0.02",
            "0.01"});
            this.cboHarrisAlpha.Location = new System.Drawing.Point(259, 0);
            this.cboHarrisAlpha.Name = "cboHarrisAlpha";
            this.cboHarrisAlpha.Size = new System.Drawing.Size(72, 21);
            this.cboHarrisAlpha.TabIndex = 5;
            this.cboHarrisAlpha.Text = "0.05";
            this.cboHarrisAlpha.Validating += new System.ComponentModel.CancelEventHandler(this.cboFloatVal_Validating);
            // 
            // lblHarrisAlpha
            // 
            this.lblHarrisAlpha.AutoSize = true;
            this.lblHarrisAlpha.Location = new System.Drawing.Point(214, 4);
            this.lblHarrisAlpha.Name = "lblHarrisAlpha";
            this.lblHarrisAlpha.Size = new System.Drawing.Size(34, 13);
            this.lblHarrisAlpha.TabIndex = 4;
            this.lblHarrisAlpha.Text = "Alpha";
            // 
            // cboHarrisBorder
            // 
            this.cboHarrisBorder.FormattingEnabled = true;
            this.cboHarrisBorder.Items.AddRange(new object[] {
            "50",
            "40",
            "35",
            "30",
            "25",
            "20",
            "15",
            "10",
            "5"});
            this.cboHarrisBorder.Location = new System.Drawing.Point(65, 28);
            this.cboHarrisBorder.Name = "cboHarrisBorder";
            this.cboHarrisBorder.Size = new System.Drawing.Size(72, 21);
            this.cboHarrisBorder.TabIndex = 3;
            this.cboHarrisBorder.Text = "20";
            this.cboHarrisBorder.Validating += new System.ComponentModel.CancelEventHandler(this.cboUIntVal_Validating);
            // 
            // lblHarrisBorder
            // 
            this.lblHarrisBorder.AutoSize = true;
            this.lblHarrisBorder.Location = new System.Drawing.Point(16, 32);
            this.lblHarrisBorder.Name = "lblHarrisBorder";
            this.lblHarrisBorder.Size = new System.Drawing.Size(38, 13);
            this.lblHarrisBorder.TabIndex = 2;
            this.lblHarrisBorder.Text = "Border";
            // 
            // cboHarrisThreshold
            // 
            this.cboHarrisThreshold.FormattingEnabled = true;
            this.cboHarrisThreshold.Items.AddRange(new object[] {
            "40000",
            "35000",
            "30000",
            "25000",
            "20000",
            "15000",
            "10000",
            "5000",
            "2500"});
            this.cboHarrisThreshold.Location = new System.Drawing.Point(65, 0);
            this.cboHarrisThreshold.Name = "cboHarrisThreshold";
            this.cboHarrisThreshold.Size = new System.Drawing.Size(72, 21);
            this.cboHarrisThreshold.TabIndex = 1;
            this.cboHarrisThreshold.Text = "20000";
            this.cboHarrisThreshold.Validating += new System.ComponentModel.CancelEventHandler(this.cboIntVal_Validating);
            // 
            // lblHarrisThreshold
            // 
            this.lblHarrisThreshold.AutoSize = true;
            this.lblHarrisThreshold.Location = new System.Drawing.Point(0, 4);
            this.lblHarrisThreshold.Name = "lblHarrisThreshold";
            this.lblHarrisThreshold.Size = new System.Drawing.Size(54, 13);
            this.lblHarrisThreshold.TabIndex = 0;
            this.lblHarrisThreshold.Text = "Threshold";
            // 
            // pnlHough
            // 
            this.pnlHough.Controls.Add(this.cboIntermediateResult);
            this.pnlHough.Controls.Add(this.lblIntermediateResult);
            this.pnlHough.Controls.Add(this.cboSegmentPixels);
            this.pnlHough.Controls.Add(this.lblSegmentPixels);
            this.pnlHough.Controls.Add(this.cboLinePixels);
            this.pnlHough.Controls.Add(this.lblLinePixels);
            this.pnlHough.Controls.Add(this.cboHoughConnectDistance);
            this.pnlHough.Controls.Add(this.lblHoughConnectDistance);
            this.pnlHough.Controls.Add(this.cboDeltaLength);
            this.pnlHough.Controls.Add(this.lblDeltaLength);
            this.pnlHough.Controls.Add(this.cboLineAngles);
            this.pnlHough.Controls.Add(this.lblLineAngles);
            this.pnlHough.Location = new System.Drawing.Point(0, 0);
            this.pnlHough.Name = "pnlHough";
            this.pnlHough.Size = new System.Drawing.Size(358, 105);
            this.pnlHough.TabIndex = 0;
            // 
            // cboIntermediateResult
            // 
            this.cboIntermediateResult.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cboIntermediateResult.FormattingEnabled = true;
            this.cboIntermediateResult.Items.AddRange(new object[] {
            "Hough image",
            "Inverse Hough",
            "After ANDing",
            "After connection",
            "Final result (after extinction)"});
            this.cboIntermediateResult.Location = new System.Drawing.Point(126, 84);
            this.cboIntermediateResult.Name = "cboIntermediateResult";
            this.cboIntermediateResult.Size = new System.Drawing.Size(232, 21);
            this.cboIntermediateResult.TabIndex = 11;
            // 
            // lblIntermediateResult
            // 
            this.lblIntermediateResult.AutoSize = true;
            this.lblIntermediateResult.Location = new System.Drawing.Point(0, 88);
            this.lblIntermediateResult.Name = "lblIntermediateResult";
            this.lblIntermediateResult.Size = new System.Drawing.Size(85, 13);
            this.lblIntermediateResult.TabIndex = 10;
            this.lblIntermediateResult.Text = "Displayed Image";
            // 
            // cboSegmentPixels
            // 
            this.cboSegmentPixels.FormattingEnabled = true;
            this.cboSegmentPixels.Items.AddRange(new object[] {
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
            this.cboSegmentPixels.Location = new System.Drawing.Point(310, 28);
            this.cboSegmentPixels.Name = "cboSegmentPixels";
            this.cboSegmentPixels.Size = new System.Drawing.Size(48, 21);
            this.cboSegmentPixels.TabIndex = 9;
            this.cboSegmentPixels.Text = "10";
            this.cboSegmentPixels.Validating += new System.ComponentModel.CancelEventHandler(this.cboUIntVal_Validating);
            // 
            // lblSegmentPixels
            // 
            this.lblSegmentPixels.AutoSize = true;
            this.lblSegmentPixels.Location = new System.Drawing.Point(200, 32);
            this.lblSegmentPixels.Name = "lblSegmentPixels";
            this.lblSegmentPixels.Size = new System.Drawing.Size(104, 13);
            this.lblSegmentPixels.TabIndex = 8;
            this.lblSegmentPixels.Text = "Segment Pixels (min)";
            // 
            // cboLinePixels
            // 
            this.cboLinePixels.FormattingEnabled = true;
            this.cboLinePixels.Items.AddRange(new object[] {
            "10",
            "20",
            "50",
            "100"});
            this.cboLinePixels.Location = new System.Drawing.Point(310, 0);
            this.cboLinePixels.Name = "cboLinePixels";
            this.cboLinePixels.Size = new System.Drawing.Size(48, 21);
            this.cboLinePixels.TabIndex = 7;
            this.cboLinePixels.Text = "20";
            this.cboLinePixels.Validating += new System.ComponentModel.CancelEventHandler(this.cboUIntVal_Validating);
            // 
            // lblLinePixels
            // 
            this.lblLinePixels.AutoSize = true;
            this.lblLinePixels.Location = new System.Drawing.Point(200, 4);
            this.lblLinePixels.Name = "lblLinePixels";
            this.lblLinePixels.Size = new System.Drawing.Size(82, 13);
            this.lblLinePixels.TabIndex = 6;
            this.lblLinePixels.Text = "Line Pixels (min)";
            // 
            // cboHoughConnectDistance
            // 
            this.cboHoughConnectDistance.FormattingEnabled = true;
            this.cboHoughConnectDistance.Items.AddRange(new object[] {
            "1",
            "2",
            "5",
            "10",
            "15",
            "20"});
            this.cboHoughConnectDistance.Location = new System.Drawing.Point(126, 56);
            this.cboHoughConnectDistance.Name = "cboHoughConnectDistance";
            this.cboHoughConnectDistance.Size = new System.Drawing.Size(48, 21);
            this.cboHoughConnectDistance.TabIndex = 5;
            this.cboHoughConnectDistance.Text = "2";
            this.cboHoughConnectDistance.Validating += new System.ComponentModel.CancelEventHandler(this.cboUIntVal_Validating);
            // 
            // lblHoughConnectDistance
            // 
            this.lblHoughConnectDistance.AutoSize = true;
            this.lblHoughConnectDistance.Location = new System.Drawing.Point(0, 60);
            this.lblHoughConnectDistance.Name = "lblHoughConnectDistance";
            this.lblHoughConnectDistance.Size = new System.Drawing.Size(120, 13);
            this.lblHoughConnectDistance.TabIndex = 4;
            this.lblHoughConnectDistance.Text = "Connect Distance (max)";
            // 
            // cboDeltaLength
            // 
            this.cboDeltaLength.FormattingEnabled = true;
            this.cboDeltaLength.Items.AddRange(new object[] {
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
            this.cboDeltaLength.Location = new System.Drawing.Point(126, 28);
            this.cboDeltaLength.Name = "cboDeltaLength";
            this.cboDeltaLength.Size = new System.Drawing.Size(48, 21);
            this.cboDeltaLength.TabIndex = 3;
            this.cboDeltaLength.Text = "1";
            this.cboDeltaLength.Validating += new System.ComponentModel.CancelEventHandler(this.cboUIntVal_Validating);
            // 
            // lblDeltaLength
            // 
            this.lblDeltaLength.AutoSize = true;
            this.lblDeltaLength.Location = new System.Drawing.Point(0, 32);
            this.lblDeltaLength.Name = "lblDeltaLength";
            this.lblDeltaLength.Size = new System.Drawing.Size(97, 13);
            this.lblDeltaLength.TabIndex = 2;
            this.lblDeltaLength.Text = "Delta Length (Rho)";
            // 
            // cboLineAngles
            // 
            this.cboLineAngles.DropDownStyle = System.Windows.Forms.ComboBoxStyle.Simple;
            this.cboLineAngles.FormattingEnabled = true;
            this.cboLineAngles.Location = new System.Drawing.Point(126, 0);
            this.cboLineAngles.Name = "cboLineAngles";
            this.cboLineAngles.Size = new System.Drawing.Size(48, 21);
            this.cboLineAngles.TabIndex = 1;
            this.cboLineAngles.Text = "0";
            this.cboLineAngles.Validating += new System.ComponentModel.CancelEventHandler(this.cboLineAngles_Validating);
            // 
            // lblLineAngles
            // 
            this.lblLineAngles.AutoSize = true;
            this.lblLineAngles.Location = new System.Drawing.Point(0, 4);
            this.lblLineAngles.Name = "lblLineAngles";
            this.lblLineAngles.Size = new System.Drawing.Size(62, 13);
            this.lblLineAngles.TabIndex = 0;
            this.lblLineAngles.Text = "Line Angles";
            // 
            // btnHelp
            // 
            this.btnHelp.BackColor = System.Drawing.Color.Yellow;
            this.btnHelp.Location = new System.Drawing.Point(12, 513);
            this.btnHelp.Name = "btnHelp";
            this.btnHelp.Size = new System.Drawing.Size(60, 26);
            this.btnHelp.TabIndex = 21;
            this.btnHelp.Text = "Help";
            this.btnHelp.UseVisualStyleBackColor = false;
            this.btnHelp.Click += new System.EventHandler(this.btnHelp_Click);
            // 
            // btnCancel
            // 
            this.btnCancel.BackColor = System.Drawing.Color.OrangeRed;
            this.btnCancel.CausesValidation = false;
            this.btnCancel.Location = new System.Drawing.Point(390, 513);
            this.btnCancel.Name = "btnCancel";
            this.btnCancel.Size = new System.Drawing.Size(60, 26);
            this.btnCancel.TabIndex = 22;
            this.btnCancel.Text = "Cancel";
            this.btnCancel.UseVisualStyleBackColor = false;
            this.btnCancel.Click += new System.EventHandler(this.btnCancel_Click);
            // 
            // btnReset
            // 
            this.btnReset.BackColor = System.Drawing.Color.CornflowerBlue;
            this.btnReset.CausesValidation = false;
            this.btnReset.Location = new System.Drawing.Point(487, 513);
            this.btnReset.Name = "btnReset";
            this.btnReset.Size = new System.Drawing.Size(60, 26);
            this.btnReset.TabIndex = 23;
            this.btnReset.Text = "Reset";
            this.btnReset.UseVisualStyleBackColor = false;
            this.btnReset.Click += new System.EventHandler(this.btnReset_Click);
            // 
            // btnApply
            // 
            this.btnApply.BackColor = System.Drawing.Color.LimeGreen;
            this.btnApply.ForeColor = System.Drawing.Color.White;
            this.btnApply.Location = new System.Drawing.Point(576, 513);
            this.btnApply.Name = "btnApply";
            this.btnApply.Size = new System.Drawing.Size(60, 26);
            this.btnApply.TabIndex = 24;
            this.btnApply.Text = "Apply";
            this.btnApply.UseVisualStyleBackColor = false;
            this.btnApply.Click += new System.EventHandler(this.btnApply_Click);
            // 
            // EdgeDetection
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.btnApply);
            this.Controls.Add(this.btnReset);
            this.Controls.Add(this.btnCancel);
            this.Controls.Add(this.btnHelp);
            this.Controls.Add(this.rbPratt);
            this.Controls.Add(this.rbEdgeLink);
            this.Controls.Add(this.rbHough);
            this.Controls.Add(this.rbHarris);
            this.Controls.Add(this.rbMoravec);
            this.Controls.Add(this.rbFreiChen);
            this.Controls.Add(this.rbShenCastan);
            this.Controls.Add(this.rbBoieCox);
            this.Controls.Add(this.rbCanny);
            this.Controls.Add(this.rbMarrHildreth);
            this.Controls.Add(this.rbCerchar);
            this.Controls.Add(this.rbPyramid);
            this.Controls.Add(this.rbRobinson);
            this.Controls.Add(this.rbKirsch);
            this.Controls.Add(this.rbLaplacian);
            this.Controls.Add(this.rbPrewitt);
            this.Controls.Add(this.rbSobel);
            this.Controls.Add(this.rbRoberts);
            this.Controls.Add(this.grpMoravec);
            this.Controls.Add(this.grpMarr);
            this.Controls.Add(this.grpRoberts);
            this.Name = "EdgeDetection";
            this.Size = new System.Drawing.Size(679, 555);
            this.grpRoberts.ResumeLayout(false);
            this.grpRoberts.PerformLayout();
            this.pnlRoberts.ResumeLayout(false);
            this.pnlRoberts.PerformLayout();
            this.grpMarr.ResumeLayout(false);
            this.grpMarr.PerformLayout();
            this.pnlMarr.ResumeLayout(false);
            this.pnlMarr.PerformLayout();
            this.pnlFrieChen.ResumeLayout(false);
            this.pnlFrieChen.PerformLayout();
            this.pnlMarrHildreth.ResumeLayout(false);
            this.pnlMarrHildreth.PerformLayout();
            this.pnlCanny.ResumeLayout(false);
            this.pnlCanny.PerformLayout();
            this.pnlBoieCox.ResumeLayout(false);
            this.pnlBoieCox.PerformLayout();
            this.pnlShenCastan.ResumeLayout(false);
            this.pnlShenCastan.PerformLayout();
            this.grpMoravec.ResumeLayout(false);
            this.pnlMoravec.ResumeLayout(false);
            this.pnlMoravecDetector.ResumeLayout(false);
            this.pnlMoravecDetector.PerformLayout();
            this.pnlEdgeLink.ResumeLayout(false);
            this.pnlEdgeLink.PerformLayout();
            this.pnlPratt.ResumeLayout(false);
            this.pnlPratt.PerformLayout();
            this.pnlPrattResultRGB.ResumeLayout(false);
            this.pnlPrattResultRGB.PerformLayout();
            this.pnlHarris.ResumeLayout(false);
            this.pnlHarris.PerformLayout();
            this.pnlHough.ResumeLayout(false);
            this.pnlHough.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.RadioButton rbRoberts;
        private System.Windows.Forms.RadioButton rbSobel;
        private System.Windows.Forms.RadioButton rbPrewitt;
        private System.Windows.Forms.RadioButton rbLaplacian;
        private System.Windows.Forms.RadioButton rbKirsch;
        private System.Windows.Forms.RadioButton rbRobinson;
        private System.Windows.Forms.RadioButton rbPyramid;
        private System.Windows.Forms.RadioButton rbCerchar;
        private System.Windows.Forms.RadioButton rbMarrHildreth;
        private System.Windows.Forms.RadioButton rbCanny;
        private System.Windows.Forms.RadioButton rbBoieCox;
        private System.Windows.Forms.RadioButton rbShenCastan;
        private System.Windows.Forms.RadioButton rbFreiChen;
        private System.Windows.Forms.RadioButton rbMoravec;
        private System.Windows.Forms.RadioButton rbHarris;
        private System.Windows.Forms.RadioButton rbHough;
        private System.Windows.Forms.RadioButton rbEdgeLink;
        private System.Windows.Forms.RadioButton rbPratt;
        private System.Windows.Forms.GroupBox grpRoberts;
        private System.Windows.Forms.CheckBox chkNotImage;
        private System.Windows.Forms.ComboBox cboThreshold;
        private System.Windows.Forms.Button btnThreshold;
        private System.Windows.Forms.Panel pnlRoberts;
        private System.Windows.Forms.CheckBox chkKeepDC;
        private System.Windows.Forms.Button btnShowMask;
        private System.Windows.Forms.ComboBox cboLaplacianMask;
        private System.Windows.Forms.Label lblLaplacianMask;
        private System.Windows.Forms.Button btnShowType;
        private System.Windows.Forms.ComboBox cboRobertsType;
        private System.Windows.Forms.Label lblRobertsType;
        private System.Windows.Forms.ComboBox cboKernelSize;
        private System.Windows.Forms.Label lblKernelSize;
        private System.Windows.Forms.ComboBox cboPostThreshold;
        private System.Windows.Forms.Label lblPostThreshold;
        private System.Windows.Forms.ComboBox cboPreFilter;
        private System.Windows.Forms.Label lblPreFilter;
        private System.Windows.Forms.GroupBox grpMarr;
        private System.Windows.Forms.Panel pnlMarr;
        private System.Windows.Forms.CheckBox chkShowImages;
        private System.Windows.Forms.Panel pnlFrieChen;
        private System.Windows.Forms.ComboBox cboFreiChenPostThresh;
        private System.Windows.Forms.Label lblFreiChenPostThresh;
        private System.Windows.Forms.ComboBox cboThresholdAngle;
        private System.Windows.Forms.Label lblThresholdAngle;
        private System.Windows.Forms.ComboBox cboProjectionMethod;
        private System.Windows.Forms.Label lblProjectionMethod;
        private System.Windows.Forms.ComboBox cboFreiChenPreFilter;
        private System.Windows.Forms.Label lblFreiChenPreFilter;
        private System.Windows.Forms.CheckBox chkThresholdAngle;
        private System.Windows.Forms.CheckBox chkFrieKeepDC;
        private System.Windows.Forms.Panel pnlMarrHildreth;
        private System.Windows.Forms.CheckBox chkCombineBands;
        private System.Windows.Forms.ComboBox cboMarrDelta;
        private System.Windows.Forms.Label lblMarrDelta;
        private System.Windows.Forms.ComboBox cboMarrSigma;
        private System.Windows.Forms.Label lblMarrSigma;
        private System.Windows.Forms.RadioButton rbDualVariance;
        private System.Windows.Forms.RadioButton rbSingleVariance;
        private System.Windows.Forms.Panel pnlCanny;
        private System.Windows.Forms.ComboBox cboCannyVariance;
        private System.Windows.Forms.Label lblCannyVariance;
        private System.Windows.Forms.ComboBox cboCannyHiThresh;
        private System.Windows.Forms.Label lblCannyHiThresh;
        private System.Windows.Forms.ComboBox cboCannyLoThresh;
        private System.Windows.Forms.Label lblCannyLoThresh;
        private System.Windows.Forms.Panel pnlBoieCox;
        private System.Windows.Forms.CheckBox chkThinEdge;
        private System.Windows.Forms.ComboBox cboBoieVariance;
        private System.Windows.Forms.Label lblBoieVariance;
        private System.Windows.Forms.ComboBox cboBoieHiThresh;
        private System.Windows.Forms.Label lblBoieHiThresh;
        private System.Windows.Forms.ComboBox cboBoieLoThresh;
        private System.Windows.Forms.Label lblBoieLoThresh;
        private System.Windows.Forms.RadioButton rbHysteresisThreshold;
        private System.Windows.Forms.RadioButton rbOrdinaryThreshold;
        private System.Windows.Forms.Panel pnlShenCastan;
        private System.Windows.Forms.ComboBox cboThinFactor;
        private System.Windows.Forms.Label lblThinFactor;
        private System.Windows.Forms.ComboBox cboWindowSize;
        private System.Windows.Forms.Label lblWindowSize;
        private System.Windows.Forms.ComboBox cboSmoothingFactor;
        private System.Windows.Forms.Label lblSmoothingFactor;
        private System.Windows.Forms.ComboBox cboShenHiThresh;
        private System.Windows.Forms.Label lblShenHiThresh;
        private System.Windows.Forms.ComboBox cboShenLoThresh;
        private System.Windows.Forms.Label lblShenLoThresh;
        private System.Windows.Forms.GroupBox grpMoravec;
        private System.Windows.Forms.Panel pnlMoravec;
        private System.Windows.Forms.Panel pnlMoravecDetector;
        private System.Windows.Forms.ComboBox cboMoravecThreshold;
        private System.Windows.Forms.Label lblMoravecThreshold;
        private System.Windows.Forms.Panel pnlEdgeLink;
        private System.Windows.Forms.ComboBox cboEdgeLinkConnectDistance;
        private System.Windows.Forms.Label lblEdgeLinkConnectDistance;
        private System.Windows.Forms.Panel pnlPratt;
        private System.Windows.Forms.Label txtPrattResultGS;
        private System.Windows.Forms.Panel pnlPrattResultRGB;
        private System.Windows.Forms.Label txtPrattResultB;
        private System.Windows.Forms.Label txtPrattResultG;
        private System.Windows.Forms.Label txtPrattResultR;
        private System.Windows.Forms.Label lblPrattResult;
        private System.Windows.Forms.ComboBox cboScaleFactor;
        private System.Windows.Forms.Label lblScaleFactor;
        //private System.Windows.Forms.ComboBox cboEdgeDetectImage;
        private System.Windows.Forms.Label lblEdgeDetectImage;
        //private System.Windows.Forms.ComboBox cboIdealImage;
        private System.Windows.Forms.Label lblIdealImage;
        private System.Windows.Forms.Panel pnlHarris;
        private System.Windows.Forms.ComboBox cboHarrisMinDistance;
        private System.Windows.Forms.Label lblHarrisMinDistance;
        private System.Windows.Forms.ComboBox cboHarrisAlpha;
        private System.Windows.Forms.Label lblHarrisAlpha;
        private System.Windows.Forms.ComboBox cboHarrisBorder;
        private System.Windows.Forms.Label lblHarrisBorder;
        private System.Windows.Forms.ComboBox cboHarrisThreshold;
        private System.Windows.Forms.Label lblHarrisThreshold;
        private System.Windows.Forms.Panel pnlHough;
        private System.Windows.Forms.ComboBox cboIntermediateResult;
        private System.Windows.Forms.Label lblIntermediateResult;
        private System.Windows.Forms.ComboBox cboSegmentPixels;
        private System.Windows.Forms.Label lblSegmentPixels;
        private System.Windows.Forms.ComboBox cboLinePixels;
        private System.Windows.Forms.Label lblLinePixels;
        private System.Windows.Forms.ComboBox cboHoughConnectDistance;
        private System.Windows.Forms.Label lblHoughConnectDistance;
        private System.Windows.Forms.ComboBox cboDeltaLength;
        private System.Windows.Forms.Label lblDeltaLength;
        private System.Windows.Forms.ComboBox cboLineAngles;
        private System.Windows.Forms.Label lblLineAngles;
        private System.Windows.Forms.Button btnHelp;
        private System.Windows.Forms.Button btnCancel;
        private System.Windows.Forms.Button btnReset;
        private System.Windows.Forms.Button btnApply;

        private System.Windows.Forms.ComboBox cboSecondImg;
        private System.Windows.Forms.Label txtCurrentImg;
        private System.Windows.Forms.ToolTip toolTipImage2;
        private System.Windows.Forms.ComboBox cboThresholdValue;
        private System.Windows.Forms.Label lblThresholdVal;
    }
}

