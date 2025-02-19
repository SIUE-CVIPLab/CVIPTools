namespace CVIPGUI.Analysis
{
    partial class Preprocessing
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
            this.btnApply = new System.Windows.Forms.Button();
            this.btnReset = new System.Windows.Forms.Button();
            this.btnCancel = new System.Windows.Forms.Button();
            this.btnHelp = new System.Windows.Forms.Button();
            this.grp_Arithmetic = new System.Windows.Forms.GroupBox();
            this.lblSecondImage = new System.Windows.Forms.Label();
            this.CurrentImageLabel = new System.Windows.Forms.Label();
            this.txtCurrentImage = new System.Windows.Forms.TextBox();
            this.cboSecondImage = new System.Windows.Forms.ComboBox();
            this.rbXor = new System.Windows.Forms.RadioButton();
            this.rbOr = new System.Windows.Forms.RadioButton();
            this.rbNot = new System.Windows.Forms.RadioButton();
            this.rbAnd = new System.Windows.Forms.RadioButton();
            this.rbDivide = new System.Windows.Forms.RadioButton();
            this.rbMultiply = new System.Windows.Forms.RadioButton();
            this.rbSubtract = new System.Windows.Forms.RadioButton();
            this.rbAdd = new System.Windows.Forms.RadioButton();
            this.rbGaussian11x11 = new System.Windows.Forms.RadioButton();
            this.rbGaussian9x9 = new System.Windows.Forms.RadioButton();
            this.rbGaussianz7x7 = new System.Windows.Forms.RadioButton();
            this.rbGaussian5x5 = new System.Windows.Forms.RadioButton();
            this.rbGaussian3x3 = new System.Windows.Forms.RadioButton();
            this.chkNormalize = new System.Windows.Forms.CheckBox();
            this.rb11x11 = new System.Windows.Forms.RadioButton();
            this.rb9x9 = new System.Windows.Forms.RadioButton();
            this.rb7x7 = new System.Windows.Forms.RadioButton();
            this.rb5x5 = new System.Windows.Forms.RadioButton();
            this.rb3x3 = new System.Windows.Forms.RadioButton();
            this.rbAdaptive = new System.Windows.Forms.RadioButton();
            this.rbStandard = new System.Windows.Forms.RadioButton();
            this.rbType3 = new System.Windows.Forms.RadioButton();
            this.rbType2 = new System.Windows.Forms.RadioButton();
            this.rbType1 = new System.Windows.Forms.RadioButton();
            this.toolTipImage2 = new System.Windows.Forms.ToolTip(this.components);
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.pnlGaussian = new System.Windows.Forms.Panel();
            this.lblGaussMask = new System.Windows.Forms.Label();
            this.pnlDifference = new System.Windows.Forms.Panel();
            this.label1 = new System.Windows.Forms.Label();
            this.pnlLaplacian = new System.Windows.Forms.Panel();
            this.lblLaplacianType = new System.Windows.Forms.Label();
            this.pnlMedian = new System.Windows.Forms.Panel();
            this.lblMedianType = new System.Windows.Forms.Label();
            this.btnEditMask = new System.Windows.Forms.Button();
            this.cboMaskSize = new System.Windows.Forms.ComboBox();
            this.lblMaskSize = new System.Windows.Forms.Label();
            this.rbDifference = new System.Windows.Forms.RadioButton();
            this.rbLaplacian = new System.Windows.Forms.RadioButton();
            this.rbMedian = new System.Windows.Forms.RadioButton();
            this.rbGaussian = new System.Windows.Forms.RadioButton();
            this.rbMeanFilter = new System.Windows.Forms.RadioButton();
            this.grpZoomLocation = new System.Windows.Forms.GroupBox();
            this.lblZoompt1 = new System.Windows.Forms.Label();
            this.lblZoomPixels = new System.Windows.Forms.Label();
            this.cboZoomHeight = new System.Windows.Forms.ComboBox();
            this.cboZoomFactor = new System.Windows.Forms.ComboBox();
            this.cboZoomMethod = new System.Windows.Forms.ComboBox();
            this.lblZoomFactor = new System.Windows.Forms.Label();
            this.lblZoomHeight = new System.Windows.Forms.Label();
            this.lblZoomMethod = new System.Windows.Forms.Label();
            this.cboZoomWidth = new System.Windows.Forms.ComboBox();
            this.lblZoomWidth = new System.Windows.Forms.Label();
            this.cboZoomRow = new System.Windows.Forms.ComboBox();
            this.lblZoomRow = new System.Windows.Forms.Label();
            this.cboZoomCol = new System.Windows.Forms.ComboBox();
            this.pnlCropp = new System.Windows.Forms.Panel();
            this.cboCropHeight = new System.Windows.Forms.ComboBox();
            this.cboCropRow = new System.Windows.Forms.ComboBox();
            this.cboCropCol = new System.Windows.Forms.ComboBox();
            this.cboCropWidth = new System.Windows.Forms.ComboBox();
            this.lblCropHeight = new System.Windows.Forms.Label();
            this.lblCropWidth = new System.Windows.Forms.Label();
            this.lblCropRow = new System.Windows.Forms.Label();
            this.lblCropCol = new System.Windows.Forms.Label();
            this.rbZoom = new System.Windows.Forms.RadioButton();
            this.rbCrop = new System.Windows.Forms.RadioButton();
            this.grpZoom = new System.Windows.Forms.GroupBox();
            this.rbGrayLevelQ = new System.Windows.Forms.RadioButton();
            this.grpQuantization = new System.Windows.Forms.GroupBox();
            this.pnlGrayLevelQ = new System.Windows.Forms.Panel();
            this.rdbUtilConvertStandard = new System.Windows.Forms.RadioButton();
            this.label5 = new System.Windows.Forms.Label();
            this.cmbUtilConvertNumOfBits = new System.Windows.Forms.ComboBox();
            this.rdbUtilConvertIGS = new System.Windows.Forms.RadioButton();
            this.pnlSpatialQuant = new System.Windows.Forms.Panel();
            this.lblSpatialQuantMethod = new System.Windows.Forms.Label();
            this.cboSpatialQuantMethod = new System.Windows.Forms.ComboBox();
            this.lblSpatialQuantHeight = new System.Windows.Forms.Label();
            this.cboSpatialQuantHeight = new System.Windows.Forms.ComboBox();
            this.lblSpatialQuantWidth = new System.Windows.Forms.Label();
            this.cboSpatialQuantWidth = new System.Windows.Forms.ComboBox();
            this.rbSpatialQuant = new System.Windows.Forms.RadioButton();
            this.grpHistogram = new System.Windows.Forms.GroupBox();
            this.pnlHistStretch = new System.Windows.Forms.Panel();
            this.lblHighPercent = new System.Windows.Forms.Label();
            this.lblLowPercent = new System.Windows.Forms.Label();
            this.lblLowLimit = new System.Windows.Forms.Label();
            this.cboHighClip = new System.Windows.Forms.ComboBox();
            this.cboLowLimit = new System.Windows.Forms.ComboBox();
            this.lblHighLimit = new System.Windows.Forms.Label();
            this.cboHighLimit = new System.Windows.Forms.ComboBox();
            this.lblHighClip = new System.Windows.Forms.Label();
            this.lblLowClip = new System.Windows.Forms.Label();
            this.cboLowClip = new System.Windows.Forms.ComboBox();
            this.pnlHistogramEQ = new System.Windows.Forms.Panel();
            this.rbBlue = new System.Windows.Forms.RadioButton();
            this.lblBand = new System.Windows.Forms.Label();
            this.rbGreen = new System.Windows.Forms.RadioButton();
            this.rbRed = new System.Windows.Forms.RadioButton();
            this.rbValue = new System.Windows.Forms.RadioButton();
            this.rbHistStretch = new System.Windows.Forms.RadioButton();
            this.rbHistEQ = new System.Windows.Forms.RadioButton();
            this.grp_Arithmetic.SuspendLayout();
            this.groupBox1.SuspendLayout();
            this.pnlGaussian.SuspendLayout();
            this.pnlDifference.SuspendLayout();
            this.pnlLaplacian.SuspendLayout();
            this.pnlMedian.SuspendLayout();
            this.grpZoomLocation.SuspendLayout();
            this.pnlCropp.SuspendLayout();
            this.grpZoom.SuspendLayout();
            this.grpQuantization.SuspendLayout();
            this.pnlGrayLevelQ.SuspendLayout();
            this.pnlSpatialQuant.SuspendLayout();
            this.grpHistogram.SuspendLayout();
            this.pnlHistStretch.SuspendLayout();
            this.pnlHistogramEQ.SuspendLayout();
            this.SuspendLayout();
            // 
            // btnApply
            // 
            this.btnApply.BackColor = System.Drawing.Color.LimeGreen;
            this.btnApply.ForeColor = System.Drawing.Color.White;
            this.btnApply.Location = new System.Drawing.Point(576, 513);
            this.btnApply.Name = "btnApply";
            this.btnApply.Size = new System.Drawing.Size(60, 26);
            this.btnApply.TabIndex = 25;
            this.btnApply.Text = "Apply";
            this.btnApply.UseVisualStyleBackColor = false;
            this.btnApply.Click += new System.EventHandler(this.btnApply_Click);
            // 
            // btnReset
            // 
            this.btnReset.BackColor = System.Drawing.Color.CornflowerBlue;
            this.btnReset.CausesValidation = false;
            this.btnReset.Location = new System.Drawing.Point(487, 513);
            this.btnReset.Name = "btnReset";
            this.btnReset.Size = new System.Drawing.Size(60, 26);
            this.btnReset.TabIndex = 26;
            this.btnReset.Text = "Reset";
            this.btnReset.UseVisualStyleBackColor = false;
            this.btnReset.Click += new System.EventHandler(this.btnReset_Click);
            // 
            // btnCancel
            // 
            this.btnCancel.BackColor = System.Drawing.Color.OrangeRed;
            this.btnCancel.CausesValidation = false;
            this.btnCancel.Location = new System.Drawing.Point(390, 513);
            this.btnCancel.Name = "btnCancel";
            this.btnCancel.Size = new System.Drawing.Size(60, 26);
            this.btnCancel.TabIndex = 27;
            this.btnCancel.Text = "Cancel";
            this.btnCancel.UseVisualStyleBackColor = false;
            this.btnCancel.Click += new System.EventHandler(this.btnCancel_Click);
            // 
            // btnHelp
            // 
            this.btnHelp.BackColor = System.Drawing.Color.Yellow;
            this.btnHelp.Location = new System.Drawing.Point(12, 513);
            this.btnHelp.Name = "btnHelp";
            this.btnHelp.Size = new System.Drawing.Size(60, 26);
            this.btnHelp.TabIndex = 28;
            this.btnHelp.Text = "Help";
            this.btnHelp.UseVisualStyleBackColor = false;
            this.btnHelp.Click += new System.EventHandler(this.btnHelp_Click);
            // 
            // grp_Arithmetic
            // 
            this.grp_Arithmetic.Controls.Add(this.lblSecondImage);
            this.grp_Arithmetic.Controls.Add(this.CurrentImageLabel);
            this.grp_Arithmetic.Controls.Add(this.txtCurrentImage);
            this.grp_Arithmetic.Controls.Add(this.cboSecondImage);
            this.grp_Arithmetic.Location = new System.Drawing.Point(5, 0);
            this.grp_Arithmetic.Name = "grp_Arithmetic";
            this.grp_Arithmetic.Size = new System.Drawing.Size(670, 175);
            this.grp_Arithmetic.TabIndex = 29;
            this.grp_Arithmetic.TabStop = false;
            this.grp_Arithmetic.Text = "Arithmetic/Logic";
            // 
            // lblSecondImage
            // 
            this.lblSecondImage.AutoSize = true;
            this.lblSecondImage.Location = new System.Drawing.Point(210, 60);
            this.lblSecondImage.Name = "lblSecondImage";
            this.lblSecondImage.Size = new System.Drawing.Size(79, 13);
            this.lblSecondImage.TabIndex = 39;
            this.lblSecondImage.Text = "Second Image:";
            // 
            // CurrentImageLabel
            // 
            this.CurrentImageLabel.AutoSize = true;
            this.CurrentImageLabel.Location = new System.Drawing.Point(210, 25);
            this.CurrentImageLabel.Name = "CurrentImageLabel";
            this.CurrentImageLabel.Size = new System.Drawing.Size(76, 13);
            this.CurrentImageLabel.TabIndex = 38;
            this.CurrentImageLabel.Text = "Current Image:";
            // 
            // txtCurrentImage
            // 
            this.txtCurrentImage.BackColor = System.Drawing.SystemColors.ControlLightLight;
            this.txtCurrentImage.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.txtCurrentImage.ForeColor = System.Drawing.Color.Blue;
            this.txtCurrentImage.Location = new System.Drawing.Point(290, 25);
            this.txtCurrentImage.Name = "txtCurrentImage";
            this.txtCurrentImage.ReadOnly = true;
            this.txtCurrentImage.Size = new System.Drawing.Size(200, 13);
            this.txtCurrentImage.TabIndex = 31;
            // 
            // cboSecondImage
            // 
            this.cboSecondImage.DisplayMember = "Text";
            this.cboSecondImage.DrawMode = System.Windows.Forms.DrawMode.OwnerDrawFixed;
            this.cboSecondImage.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cboSecondImage.FormattingEnabled = true;
            this.cboSecondImage.Location = new System.Drawing.Point(290, 55);
            this.cboSecondImage.Name = "cboSecondImage";
            this.cboSecondImage.Size = new System.Drawing.Size(121, 21);
            this.cboSecondImage.TabIndex = 30;
            this.cboSecondImage.DrawItem += new System.Windows.Forms.DrawItemEventHandler(this.cboSecondImage_DrawItem);
            this.cboSecondImage.SelectedIndexChanged += new System.EventHandler(this.cboSecondImage_SelectedIndexChanged);
            // 
            // rbXor
            // 
            this.rbXor.AutoSize = true;
            this.rbXor.Location = new System.Drawing.Point(20, 155);
            this.rbXor.Name = "rbXor";
            this.rbXor.Size = new System.Drawing.Size(48, 17);
            this.rbXor.TabIndex = 37;
            this.rbXor.TabStop = true;
            this.rbXor.Text = "XOR";
            this.rbXor.UseVisualStyleBackColor = true;
            this.rbXor.CheckedChanged += new System.EventHandler(this.rbPreProcessing_CheckedChanged);
            // 
            // rbOr
            // 
            this.rbOr.AutoSize = true;
            this.rbOr.Location = new System.Drawing.Point(20, 135);
            this.rbOr.Name = "rbOr";
            this.rbOr.Size = new System.Drawing.Size(41, 17);
            this.rbOr.TabIndex = 36;
            this.rbOr.TabStop = true;
            this.rbOr.Text = "OR";
            this.rbOr.UseVisualStyleBackColor = true;
            this.rbOr.CheckedChanged += new System.EventHandler(this.rbPreProcessing_CheckedChanged);
            // 
            // rbNot
            // 
            this.rbNot.AutoSize = true;
            this.rbNot.Location = new System.Drawing.Point(20, 115);
            this.rbNot.Name = "rbNot";
            this.rbNot.Size = new System.Drawing.Size(48, 17);
            this.rbNot.TabIndex = 35;
            this.rbNot.TabStop = true;
            this.rbNot.Text = "NOT";
            this.rbNot.UseVisualStyleBackColor = true;
            this.rbNot.CheckedChanged += new System.EventHandler(this.rbPreProcessing_CheckedChanged);
            // 
            // rbAnd
            // 
            this.rbAnd.AutoSize = true;
            this.rbAnd.Location = new System.Drawing.Point(20, 95);
            this.rbAnd.Name = "rbAnd";
            this.rbAnd.Size = new System.Drawing.Size(48, 17);
            this.rbAnd.TabIndex = 34;
            this.rbAnd.TabStop = true;
            this.rbAnd.Text = "AND";
            this.rbAnd.UseVisualStyleBackColor = true;
            this.rbAnd.CheckedChanged += new System.EventHandler(this.rbPreProcessing_CheckedChanged);
            // 
            // rbDivide
            // 
            this.rbDivide.AutoSize = true;
            this.rbDivide.Location = new System.Drawing.Point(20, 75);
            this.rbDivide.Name = "rbDivide";
            this.rbDivide.Size = new System.Drawing.Size(55, 17);
            this.rbDivide.TabIndex = 33;
            this.rbDivide.TabStop = true;
            this.rbDivide.Text = "Divide";
            this.rbDivide.UseVisualStyleBackColor = true;
            this.rbDivide.CheckedChanged += new System.EventHandler(this.rbPreProcessing_CheckedChanged);
            // 
            // rbMultiply
            // 
            this.rbMultiply.AutoSize = true;
            this.rbMultiply.Location = new System.Drawing.Point(20, 55);
            this.rbMultiply.Name = "rbMultiply";
            this.rbMultiply.Size = new System.Drawing.Size(60, 17);
            this.rbMultiply.TabIndex = 32;
            this.rbMultiply.TabStop = true;
            this.rbMultiply.Text = "Multiply";
            this.rbMultiply.UseVisualStyleBackColor = true;
            this.rbMultiply.CheckedChanged += new System.EventHandler(this.rbPreProcessing_CheckedChanged);
            // 
            // rbSubtract
            // 
            this.rbSubtract.AutoSize = true;
            this.rbSubtract.Location = new System.Drawing.Point(20, 35);
            this.rbSubtract.Name = "rbSubtract";
            this.rbSubtract.Size = new System.Drawing.Size(65, 17);
            this.rbSubtract.TabIndex = 30;
            this.rbSubtract.TabStop = true;
            this.rbSubtract.Text = "Subtract";
            this.rbSubtract.UseVisualStyleBackColor = true;
            this.rbSubtract.CheckedChanged += new System.EventHandler(this.rbPreProcessing_CheckedChanged);
            // 
            // rbAdd
            // 
            this.rbAdd.AutoSize = true;
            this.rbAdd.Location = new System.Drawing.Point(20, 15);
            this.rbAdd.Name = "rbAdd";
            this.rbAdd.Size = new System.Drawing.Size(44, 17);
            this.rbAdd.TabIndex = 0;
            this.rbAdd.TabStop = true;
            this.rbAdd.Text = "Add";
            this.rbAdd.UseVisualStyleBackColor = true;
            this.rbAdd.CheckedChanged += new System.EventHandler(this.rbPreProcessing_CheckedChanged);
            // 
            // rbGaussian11x11
            // 
            this.rbGaussian11x11.AutoSize = true;
            this.rbGaussian11x11.Location = new System.Drawing.Point(265, 3);
            this.rbGaussian11x11.Name = "rbGaussian11x11";
            this.rbGaussian11x11.Size = new System.Drawing.Size(56, 17);
            this.rbGaussian11x11.TabIndex = 45;
            this.rbGaussian11x11.TabStop = true;
            this.rbGaussian11x11.Text = "11X11";
            this.rbGaussian11x11.UseVisualStyleBackColor = true;
            this.rbGaussian11x11.CheckedChanged += new System.EventHandler(this.rbcboSpecifyFilter_ParameterChanged);
            // 
            // rbGaussian9x9
            // 
            this.rbGaussian9x9.AutoSize = true;
            this.rbGaussian9x9.Location = new System.Drawing.Point(215, 3);
            this.rbGaussian9x9.Name = "rbGaussian9x9";
            this.rbGaussian9x9.Size = new System.Drawing.Size(44, 17);
            this.rbGaussian9x9.TabIndex = 44;
            this.rbGaussian9x9.TabStop = true;
            this.rbGaussian9x9.Text = "9X9";
            this.rbGaussian9x9.UseVisualStyleBackColor = true;
            this.rbGaussian9x9.CheckedChanged += new System.EventHandler(this.rbcboSpecifyFilter_ParameterChanged);
            // 
            // rbGaussianz7x7
            // 
            this.rbGaussianz7x7.AutoSize = true;
            this.rbGaussianz7x7.Location = new System.Drawing.Point(165, 3);
            this.rbGaussianz7x7.Name = "rbGaussianz7x7";
            this.rbGaussianz7x7.Size = new System.Drawing.Size(44, 17);
            this.rbGaussianz7x7.TabIndex = 43;
            this.rbGaussianz7x7.TabStop = true;
            this.rbGaussianz7x7.Text = "7X7";
            this.rbGaussianz7x7.UseVisualStyleBackColor = true;
            this.rbGaussianz7x7.CheckedChanged += new System.EventHandler(this.rbcboSpecifyFilter_ParameterChanged);
            // 
            // rbGaussian5x5
            // 
            this.rbGaussian5x5.AutoSize = true;
            this.rbGaussian5x5.Location = new System.Drawing.Point(115, 3);
            this.rbGaussian5x5.Name = "rbGaussian5x5";
            this.rbGaussian5x5.Size = new System.Drawing.Size(44, 17);
            this.rbGaussian5x5.TabIndex = 42;
            this.rbGaussian5x5.TabStop = true;
            this.rbGaussian5x5.Text = "5X5";
            this.rbGaussian5x5.UseVisualStyleBackColor = true;
            this.rbGaussian5x5.CheckedChanged += new System.EventHandler(this.rbcboSpecifyFilter_ParameterChanged);
            // 
            // rbGaussian3x3
            // 
            this.rbGaussian3x3.AutoSize = true;
            this.rbGaussian3x3.Checked = true;
            this.rbGaussian3x3.Location = new System.Drawing.Point(65, 3);
            this.rbGaussian3x3.Name = "rbGaussian3x3";
            this.rbGaussian3x3.Size = new System.Drawing.Size(44, 17);
            this.rbGaussian3x3.TabIndex = 41;
            this.rbGaussian3x3.TabStop = true;
            this.rbGaussian3x3.Text = "3X3";
            this.rbGaussian3x3.UseVisualStyleBackColor = true;
            this.rbGaussian3x3.CheckedChanged += new System.EventHandler(this.rbcboSpecifyFilter_ParameterChanged);
            // 
            // chkNormalize
            // 
            this.chkNormalize.AutoSize = true;
            this.chkNormalize.Checked = true;
            this.chkNormalize.CheckState = System.Windows.Forms.CheckState.Checked;
            this.chkNormalize.Location = new System.Drawing.Point(330, 4);
            this.chkNormalize.Name = "chkNormalize";
            this.chkNormalize.Size = new System.Drawing.Size(72, 17);
            this.chkNormalize.TabIndex = 40;
            this.chkNormalize.Text = "Normalize";
            this.chkNormalize.UseVisualStyleBackColor = true;
            // 
            // rb11x11
            // 
            this.rb11x11.AutoSize = true;
            this.rb11x11.Location = new System.Drawing.Point(265, 3);
            this.rb11x11.Name = "rb11x11";
            this.rb11x11.Size = new System.Drawing.Size(56, 17);
            this.rb11x11.TabIndex = 16;
            this.rb11x11.TabStop = true;
            this.rb11x11.Text = "11X11";
            this.rb11x11.UseVisualStyleBackColor = true;
            this.rb11x11.CheckedChanged += new System.EventHandler(this.rbDifference_CheckedChanged);
            // 
            // rb9x9
            // 
            this.rb9x9.AutoSize = true;
            this.rb9x9.Location = new System.Drawing.Point(215, 3);
            this.rb9x9.Name = "rb9x9";
            this.rb9x9.Size = new System.Drawing.Size(44, 17);
            this.rb9x9.TabIndex = 15;
            this.rb9x9.TabStop = true;
            this.rb9x9.Text = "9X9";
            this.rb9x9.UseVisualStyleBackColor = true;
            this.rb9x9.CheckedChanged += new System.EventHandler(this.rbDifference_CheckedChanged);
            // 
            // rb7x7
            // 
            this.rb7x7.AutoSize = true;
            this.rb7x7.Location = new System.Drawing.Point(165, 3);
            this.rb7x7.Name = "rb7x7";
            this.rb7x7.Size = new System.Drawing.Size(44, 17);
            this.rb7x7.TabIndex = 14;
            this.rb7x7.TabStop = true;
            this.rb7x7.Text = "7X7";
            this.rb7x7.UseVisualStyleBackColor = true;
            this.rb7x7.CheckedChanged += new System.EventHandler(this.rbDifference_CheckedChanged);
            // 
            // rb5x5
            // 
            this.rb5x5.AutoSize = true;
            this.rb5x5.Location = new System.Drawing.Point(115, 3);
            this.rb5x5.Name = "rb5x5";
            this.rb5x5.Size = new System.Drawing.Size(44, 17);
            this.rb5x5.TabIndex = 13;
            this.rb5x5.TabStop = true;
            this.rb5x5.Text = "5X5";
            this.rb5x5.UseVisualStyleBackColor = true;
            this.rb5x5.CheckedChanged += new System.EventHandler(this.rbDifference_CheckedChanged);
            // 
            // rb3x3
            // 
            this.rb3x3.AutoSize = true;
            this.rb3x3.Checked = true;
            this.rb3x3.Location = new System.Drawing.Point(65, 3);
            this.rb3x3.Name = "rb3x3";
            this.rb3x3.Size = new System.Drawing.Size(44, 17);
            this.rb3x3.TabIndex = 12;
            this.rb3x3.TabStop = true;
            this.rb3x3.Text = "3X3";
            this.rb3x3.UseVisualStyleBackColor = true;
            this.rb3x3.CheckedChanged += new System.EventHandler(this.rbDifference_CheckedChanged);
            // 
            // rbAdaptive
            // 
            this.rbAdaptive.AutoSize = true;
            this.rbAdaptive.Location = new System.Drawing.Point(170, 3);
            this.rbAdaptive.Name = "rbAdaptive";
            this.rbAdaptive.Size = new System.Drawing.Size(67, 17);
            this.rbAdaptive.TabIndex = 8;
            this.rbAdaptive.TabStop = true;
            this.rbAdaptive.Text = "Adaptive";
            this.rbAdaptive.UseVisualStyleBackColor = true;
            // 
            // rbStandard
            // 
            this.rbStandard.AutoSize = true;
            this.rbStandard.Checked = true;
            this.rbStandard.Location = new System.Drawing.Point(90, 3);
            this.rbStandard.Name = "rbStandard";
            this.rbStandard.Size = new System.Drawing.Size(68, 17);
            this.rbStandard.TabIndex = 7;
            this.rbStandard.TabStop = true;
            this.rbStandard.Text = "Standard";
            this.rbStandard.UseVisualStyleBackColor = true;
            // 
            // rbType3
            // 
            this.rbType3.AutoSize = true;
            this.rbType3.Location = new System.Drawing.Point(220, 4);
            this.rbType3.Name = "rbType3";
            this.rbType3.Size = new System.Drawing.Size(58, 17);
            this.rbType3.TabIndex = 11;
            this.rbType3.TabStop = true;
            this.rbType3.Text = "Type 3";
            this.rbType3.UseVisualStyleBackColor = true;
            this.rbType3.CheckedChanged += new System.EventHandler(this.rbLaplacianType_CheckedChanged);
            // 
            // rbType2
            // 
            this.rbType2.AutoSize = true;
            this.rbType2.Location = new System.Drawing.Point(155, 4);
            this.rbType2.Name = "rbType2";
            this.rbType2.Size = new System.Drawing.Size(55, 17);
            this.rbType2.TabIndex = 10;
            this.rbType2.TabStop = true;
            this.rbType2.Text = "Type2";
            this.rbType2.UseVisualStyleBackColor = true;
            this.rbType2.CheckedChanged += new System.EventHandler(this.rbLaplacianType_CheckedChanged);
            // 
            // rbType1
            // 
            this.rbType1.AutoSize = true;
            this.rbType1.Checked = true;
            this.rbType1.Location = new System.Drawing.Point(90, 3);
            this.rbType1.Name = "rbType1";
            this.rbType1.Size = new System.Drawing.Size(58, 17);
            this.rbType1.TabIndex = 9;
            this.rbType1.TabStop = true;
            this.rbType1.Text = "Type 1";
            this.rbType1.UseVisualStyleBackColor = true;
            this.rbType1.CheckedChanged += new System.EventHandler(this.rbLaplacianType_CheckedChanged);
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.pnlGaussian);
            this.groupBox1.Controls.Add(this.pnlDifference);
            this.groupBox1.Controls.Add(this.pnlLaplacian);
            this.groupBox1.Controls.Add(this.pnlMedian);
            this.groupBox1.Controls.Add(this.btnEditMask);
            this.groupBox1.Controls.Add(this.cboMaskSize);
            this.groupBox1.Controls.Add(this.lblMaskSize);
            this.groupBox1.Location = new System.Drawing.Point(6, 178);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(670, 118);
            this.groupBox1.TabIndex = 30;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Spatial Filters";
            // 
            // pnlGaussian
            // 
            this.pnlGaussian.Controls.Add(this.lblGaussMask);
            this.pnlGaussian.Controls.Add(this.rbGaussian3x3);
            this.pnlGaussian.Controls.Add(this.chkNormalize);
            this.pnlGaussian.Controls.Add(this.rbGaussian11x11);
            this.pnlGaussian.Controls.Add(this.rbGaussian5x5);
            this.pnlGaussian.Controls.Add(this.rbGaussian9x9);
            this.pnlGaussian.Controls.Add(this.rbGaussianz7x7);
            this.pnlGaussian.Location = new System.Drawing.Point(170, 55);
            this.pnlGaussian.Name = "pnlGaussian";
            this.pnlGaussian.Size = new System.Drawing.Size(410, 27);
            this.pnlGaussian.TabIndex = 46;
            // 
            // lblGaussMask
            // 
            this.lblGaussMask.AutoSize = true;
            this.lblGaussMask.Location = new System.Drawing.Point(3, 7);
            this.lblGaussMask.Name = "lblGaussMask";
            this.lblGaussMask.Size = new System.Drawing.Size(62, 13);
            this.lblGaussMask.TabIndex = 48;
            this.lblGaussMask.Text = "Mask Size: ";
            // 
            // pnlDifference
            // 
            this.pnlDifference.Controls.Add(this.label1);
            this.pnlDifference.Controls.Add(this.rb3x3);
            this.pnlDifference.Controls.Add(this.rb5x5);
            this.pnlDifference.Controls.Add(this.rb7x7);
            this.pnlDifference.Controls.Add(this.rb9x9);
            this.pnlDifference.Controls.Add(this.rb11x11);
            this.pnlDifference.Location = new System.Drawing.Point(170, 90);
            this.pnlDifference.Name = "pnlDifference";
            this.pnlDifference.Size = new System.Drawing.Size(330, 24);
            this.pnlDifference.TabIndex = 46;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(3, 5);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(62, 13);
            this.label1.TabIndex = 49;
            this.label1.Text = "Mask Size: ";
            // 
            // pnlLaplacian
            // 
            this.pnlLaplacian.Controls.Add(this.lblLaplacianType);
            this.pnlLaplacian.Controls.Add(this.rbType1);
            this.pnlLaplacian.Controls.Add(this.rbType2);
            this.pnlLaplacian.Controls.Add(this.rbType3);
            this.pnlLaplacian.Location = new System.Drawing.Point(170, 70);
            this.pnlLaplacian.Name = "pnlLaplacian";
            this.pnlLaplacian.Size = new System.Drawing.Size(300, 29);
            this.pnlLaplacian.TabIndex = 47;
            // 
            // lblLaplacianType
            // 
            this.lblLaplacianType.AutoSize = true;
            this.lblLaplacianType.Location = new System.Drawing.Point(3, 5);
            this.lblLaplacianType.Name = "lblLaplacianType";
            this.lblLaplacianType.Size = new System.Drawing.Size(83, 13);
            this.lblLaplacianType.TabIndex = 12;
            this.lblLaplacianType.Text = "Laplacian Type:";
            // 
            // pnlMedian
            // 
            this.pnlMedian.Controls.Add(this.lblMedianType);
            this.pnlMedian.Controls.Add(this.rbStandard);
            this.pnlMedian.Controls.Add(this.rbAdaptive);
            this.pnlMedian.Location = new System.Drawing.Point(170, 40);
            this.pnlMedian.Name = "pnlMedian";
            this.pnlMedian.Size = new System.Drawing.Size(245, 24);
            this.pnlMedian.TabIndex = 46;
            // 
            // lblMedianType
            // 
            this.lblMedianType.AutoSize = true;
            this.lblMedianType.Location = new System.Drawing.Point(3, 5);
            this.lblMedianType.Name = "lblMedianType";
            this.lblMedianType.Size = new System.Drawing.Size(72, 13);
            this.lblMedianType.TabIndex = 13;
            this.lblMedianType.Text = "Median Type:";
            // 
            // btnEditMask
            // 
            this.btnEditMask.Location = new System.Drawing.Point(505, 89);
            this.btnEditMask.Name = "btnEditMask";
            this.btnEditMask.Size = new System.Drawing.Size(75, 24);
            this.btnEditMask.TabIndex = 18;
            this.btnEditMask.Text = "Edit Mask";
            this.btnEditMask.UseVisualStyleBackColor = true;
            this.btnEditMask.Click += new System.EventHandler(this.btnEditMask_Click);
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
            this.cboMaskSize.Location = new System.Drawing.Point(239, 16);
            this.cboMaskSize.Name = "cboMaskSize";
            this.cboMaskSize.Size = new System.Drawing.Size(50, 21);
            this.cboMaskSize.TabIndex = 6;
            this.cboMaskSize.Text = "3";
            this.cboMaskSize.Validating += new System.ComponentModel.CancelEventHandler(this.cboMaskSize_Validating);
            // 
            // lblMaskSize
            // 
            this.lblMaskSize.AutoSize = true;
            this.lblMaskSize.Location = new System.Drawing.Point(173, 19);
            this.lblMaskSize.Name = "lblMaskSize";
            this.lblMaskSize.Size = new System.Drawing.Size(62, 13);
            this.lblMaskSize.TabIndex = 5;
            this.lblMaskSize.Text = "Mask Size: ";
            // 
            // rbDifference
            // 
            this.rbDifference.AutoSize = true;
            this.rbDifference.Location = new System.Drawing.Point(20, 270);
            this.rbDifference.Name = "rbDifference";
            this.rbDifference.Size = new System.Drawing.Size(74, 17);
            this.rbDifference.TabIndex = 4;
            this.rbDifference.TabStop = true;
            this.rbDifference.Text = "Difference";
            this.rbDifference.UseVisualStyleBackColor = true;
            this.rbDifference.CheckedChanged += new System.EventHandler(this.rbPreProcessing_CheckedChanged);
            // 
            // rbLaplacian
            // 
            this.rbLaplacian.AutoSize = true;
            this.rbLaplacian.Location = new System.Drawing.Point(20, 250);
            this.rbLaplacian.Name = "rbLaplacian";
            this.rbLaplacian.Size = new System.Drawing.Size(71, 17);
            this.rbLaplacian.TabIndex = 3;
            this.rbLaplacian.TabStop = true;
            this.rbLaplacian.Text = "Laplacian";
            this.rbLaplacian.UseVisualStyleBackColor = true;
            this.rbLaplacian.CheckedChanged += new System.EventHandler(this.rbPreProcessing_CheckedChanged);
            // 
            // rbMedian
            // 
            this.rbMedian.AutoSize = true;
            this.rbMedian.Location = new System.Drawing.Point(20, 210);
            this.rbMedian.Name = "rbMedian";
            this.rbMedian.Size = new System.Drawing.Size(60, 17);
            this.rbMedian.TabIndex = 2;
            this.rbMedian.TabStop = true;
            this.rbMedian.Text = "Median";
            this.rbMedian.UseVisualStyleBackColor = true;
            this.rbMedian.CheckedChanged += new System.EventHandler(this.rbPreProcessing_CheckedChanged);
            // 
            // rbGaussian
            // 
            this.rbGaussian.AutoSize = true;
            this.rbGaussian.Location = new System.Drawing.Point(20, 230);
            this.rbGaussian.Name = "rbGaussian";
            this.rbGaussian.Size = new System.Drawing.Size(69, 17);
            this.rbGaussian.TabIndex = 1;
            this.rbGaussian.TabStop = true;
            this.rbGaussian.Text = "Gaussian";
            this.rbGaussian.UseVisualStyleBackColor = true;
            this.rbGaussian.CheckedChanged += new System.EventHandler(this.rbPreProcessing_CheckedChanged);
            // 
            // rbMeanFilter
            // 
            this.rbMeanFilter.AutoSize = true;
            this.rbMeanFilter.Location = new System.Drawing.Point(20, 190);
            this.rbMeanFilter.Name = "rbMeanFilter";
            this.rbMeanFilter.Size = new System.Drawing.Size(52, 17);
            this.rbMeanFilter.TabIndex = 0;
            this.rbMeanFilter.TabStop = true;
            this.rbMeanFilter.Text = "Mean";
            this.rbMeanFilter.UseVisualStyleBackColor = true;
            this.rbMeanFilter.CheckedChanged += new System.EventHandler(this.rbPreProcessing_CheckedChanged);
            // 
            // grpZoomLocation
            // 
            this.grpZoomLocation.Controls.Add(this.lblZoompt1);
            this.grpZoomLocation.Controls.Add(this.lblZoomPixels);
            this.grpZoomLocation.Controls.Add(this.cboZoomHeight);
            this.grpZoomLocation.Controls.Add(this.cboZoomFactor);
            this.grpZoomLocation.Controls.Add(this.cboZoomMethod);
            this.grpZoomLocation.Controls.Add(this.lblZoomFactor);
            this.grpZoomLocation.Controls.Add(this.lblZoomHeight);
            this.grpZoomLocation.Controls.Add(this.lblZoomMethod);
            this.grpZoomLocation.Controls.Add(this.cboZoomWidth);
            this.grpZoomLocation.Controls.Add(this.lblZoomWidth);
            this.grpZoomLocation.Controls.Add(this.cboZoomRow);
            this.grpZoomLocation.Controls.Add(this.lblZoomRow);
            this.grpZoomLocation.Controls.Add(this.cboZoomCol);
            this.grpZoomLocation.Location = new System.Drawing.Point(88, 14);
            this.grpZoomLocation.Name = "grpZoomLocation";
            this.grpZoomLocation.Size = new System.Drawing.Size(570, 60);
            this.grpZoomLocation.TabIndex = 4;
            this.grpZoomLocation.TabStop = false;
            // 
            // lblZoompt1
            // 
            this.lblZoompt1.AutoSize = true;
            this.lblZoompt1.Location = new System.Drawing.Point(16, 12);
            this.lblZoompt1.Name = "lblZoompt1";
            this.lblZoompt1.Size = new System.Drawing.Size(127, 13);
            this.lblZoompt1.TabIndex = 13;
            this.lblZoompt1.Text = "Area beginning at column";
            // 
            // lblZoomPixels
            // 
            this.lblZoomPixels.AutoSize = true;
            this.lblZoomPixels.Location = new System.Drawing.Point(365, 37);
            this.lblZoomPixels.Name = "lblZoomPixels";
            this.lblZoomPixels.Size = new System.Drawing.Size(36, 13);
            this.lblZoomPixels.TabIndex = 12;
            this.lblZoomPixels.Text = "pixels.";
            // 
            // cboZoomHeight
            // 
            this.cboZoomHeight.FormattingEnabled = true;
            this.cboZoomHeight.Items.AddRange(new object[] {
            "0",
            "8",
            "16",
            "32",
            "64",
            "128",
            "256",
            "512"});
            this.cboZoomHeight.Location = new System.Drawing.Point(299, 32);
            this.cboZoomHeight.Name = "cboZoomHeight";
            this.cboZoomHeight.Size = new System.Drawing.Size(60, 21);
            this.cboZoomHeight.TabIndex = 11;
            this.cboZoomHeight.Text = "64";
            this.cboZoomHeight.Validating += new System.ComponentModel.CancelEventHandler(this.cboPositiveIntVal_Validating);
            this.cboZoomHeight.Validated += new System.EventHandler(this.cboCropZoom_Validated);
            // 
            // cboZoomFactor
            // 
            this.cboZoomFactor.FormattingEnabled = true;
            this.cboZoomFactor.Items.AddRange(new object[] {
            "0.5",
            "0.8",
            "1.2",
            "1.5",
            "2.0",
            "3.0",
            "4.0",
            "5.0"});
            this.cboZoomFactor.Location = new System.Drawing.Point(400, 10);
            this.cboZoomFactor.Name = "cboZoomFactor";
            this.cboZoomFactor.Size = new System.Drawing.Size(57, 21);
            this.cboZoomFactor.TabIndex = 1;
            this.cboZoomFactor.Text = "2.0";
            this.cboZoomFactor.Validating += new System.ComponentModel.CancelEventHandler(this.cboZoomFactor_Validating);
            // 
            // cboZoomMethod
            // 
            this.cboZoomMethod.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cboZoomMethod.FormattingEnabled = true;
            this.cboZoomMethod.Items.AddRange(new object[] {
            "Zero Order Hold",
            "Bilinear Interpolation"});
            this.cboZoomMethod.Location = new System.Drawing.Point(440, 34);
            this.cboZoomMethod.Name = "cboZoomMethod";
            this.cboZoomMethod.Size = new System.Drawing.Size(120, 21);
            this.cboZoomMethod.TabIndex = 3;
            // 
            // lblZoomFactor
            // 
            this.lblZoomFactor.AutoSize = true;
            this.lblZoomFactor.Location = new System.Drawing.Point(371, 15);
            this.lblZoomFactor.Name = "lblZoomFactor";
            this.lblZoomFactor.Size = new System.Drawing.Size(19, 13);
            this.lblZoomFactor.TabIndex = 0;
            this.lblZoomFactor.Text = "By";
            // 
            // lblZoomHeight
            // 
            this.lblZoomHeight.AutoSize = true;
            this.lblZoomHeight.Location = new System.Drawing.Point(224, 37);
            this.lblZoomHeight.Name = "lblZoomHeight";
            this.lblZoomHeight.Size = new System.Drawing.Size(69, 13);
            this.lblZoomHeight.TabIndex = 10;
            this.lblZoomHeight.Text = "and height of";
            // 
            // lblZoomMethod
            // 
            this.lblZoomMethod.AutoSize = true;
            this.lblZoomMethod.Location = new System.Drawing.Point(410, 37);
            this.lblZoomMethod.Name = "lblZoomMethod";
            this.lblZoomMethod.Size = new System.Drawing.Size(26, 13);
            this.lblZoomMethod.TabIndex = 2;
            this.lblZoomMethod.Text = "Use";
            // 
            // cboZoomWidth
            // 
            this.cboZoomWidth.FormattingEnabled = true;
            this.cboZoomWidth.Items.AddRange(new object[] {
            "0",
            "8",
            "16",
            "32",
            "64",
            "128",
            "256",
            "512"});
            this.cboZoomWidth.Location = new System.Drawing.Point(149, 34);
            this.cboZoomWidth.Name = "cboZoomWidth";
            this.cboZoomWidth.Size = new System.Drawing.Size(60, 21);
            this.cboZoomWidth.TabIndex = 9;
            this.cboZoomWidth.Text = "64";
            this.cboZoomWidth.Validating += new System.ComponentModel.CancelEventHandler(this.cboPositiveIntVal_Validating);
            this.cboZoomWidth.Validated += new System.EventHandler(this.cboCropZoom_Validated);
            // 
            // lblZoomWidth
            // 
            this.lblZoomWidth.AutoSize = true;
            this.lblZoomWidth.Location = new System.Drawing.Point(64, 40);
            this.lblZoomWidth.Name = "lblZoomWidth";
            this.lblZoomWidth.Size = new System.Drawing.Size(78, 13);
            this.lblZoomWidth.TabIndex = 8;
            this.lblZoomWidth.Text = "with a width of ";
            // 
            // cboZoomRow
            // 
            this.cboZoomRow.FormattingEnabled = true;
            this.cboZoomRow.Items.AddRange(new object[] {
            "0",
            "8",
            "16",
            "32",
            "64",
            "128",
            "256",
            "512"});
            this.cboZoomRow.Location = new System.Drawing.Point(275, 9);
            this.cboZoomRow.Name = "cboZoomRow";
            this.cboZoomRow.Size = new System.Drawing.Size(60, 21);
            this.cboZoomRow.TabIndex = 7;
            this.cboZoomRow.Text = "0";
            this.cboZoomRow.Validating += new System.ComponentModel.CancelEventHandler(this.cboUIntVal_Validating);
            this.cboZoomRow.Validated += new System.EventHandler(this.cboCropZoom_Validated);
            // 
            // lblZoomRow
            // 
            this.lblZoomRow.AutoSize = true;
            this.lblZoomRow.Location = new System.Drawing.Point(224, 12);
            this.lblZoomRow.Name = "lblZoomRow";
            this.lblZoomRow.Size = new System.Drawing.Size(45, 13);
            this.lblZoomRow.TabIndex = 6;
            this.lblZoomRow.Text = "and row";
            // 
            // cboZoomCol
            // 
            this.cboZoomCol.FormattingEnabled = true;
            this.cboZoomCol.Items.AddRange(new object[] {
            "0",
            "8",
            "16",
            "32",
            "64",
            "128",
            "256",
            "512"});
            this.cboZoomCol.Location = new System.Drawing.Point(149, 7);
            this.cboZoomCol.Name = "cboZoomCol";
            this.cboZoomCol.Size = new System.Drawing.Size(60, 21);
            this.cboZoomCol.TabIndex = 5;
            this.cboZoomCol.Text = "0";
            this.cboZoomCol.Validating += new System.ComponentModel.CancelEventHandler(this.cboUIntVal_Validating);
            this.cboZoomCol.Validated += new System.EventHandler(this.cboCropZoom_Validated);
            // 
            // pnlCropp
            // 
            this.pnlCropp.Controls.Add(this.cboCropHeight);
            this.pnlCropp.Controls.Add(this.cboCropRow);
            this.pnlCropp.Controls.Add(this.cboCropCol);
            this.pnlCropp.Controls.Add(this.cboCropWidth);
            this.pnlCropp.Controls.Add(this.lblCropHeight);
            this.pnlCropp.Controls.Add(this.lblCropWidth);
            this.pnlCropp.Controls.Add(this.lblCropRow);
            this.pnlCropp.Controls.Add(this.lblCropCol);
            this.pnlCropp.Location = new System.Drawing.Point(73, 15);
            this.pnlCropp.Name = "pnlCropp";
            this.pnlCropp.Size = new System.Drawing.Size(590, 38);
            this.pnlCropp.TabIndex = 2;
            // 
            // cboCropHeight
            // 
            this.cboCropHeight.FormattingEnabled = true;
            this.cboCropHeight.Items.AddRange(new object[] {
            "8",
            "16",
            "32",
            "64",
            "100",
            "128",
            "256",
            "512"});
            this.cboCropHeight.Location = new System.Drawing.Point(515, 6);
            this.cboCropHeight.Name = "cboCropHeight";
            this.cboCropHeight.Size = new System.Drawing.Size(60, 21);
            this.cboCropHeight.TabIndex = 6;
            this.cboCropHeight.Text = "100";
            this.cboCropHeight.Validating += new System.ComponentModel.CancelEventHandler(this.cboIntVal_Validating);
            // 
            // cboCropRow
            // 
            this.cboCropRow.FormattingEnabled = true;
            this.cboCropRow.Items.AddRange(new object[] {
            "0",
            "8",
            "16",
            "32",
            "64",
            "128",
            "256",
            "512"});
            this.cboCropRow.Location = new System.Drawing.Point(265, 6);
            this.cboCropRow.Name = "cboCropRow";
            this.cboCropRow.Size = new System.Drawing.Size(60, 21);
            this.cboCropRow.TabIndex = 2;
            this.cboCropRow.Text = "0";
            this.cboCropRow.Validating += new System.ComponentModel.CancelEventHandler(this.cboIntVal_Validating);
            // 
            // cboCropCol
            // 
            this.cboCropCol.FormattingEnabled = true;
            this.cboCropCol.Items.AddRange(new object[] {
            "0",
            "8",
            "16",
            "32",
            "64",
            "128",
            "256",
            "512"});
            this.cboCropCol.Location = new System.Drawing.Point(145, 6);
            this.cboCropCol.Name = "cboCropCol";
            this.cboCropCol.Size = new System.Drawing.Size(64, 21);
            this.cboCropCol.TabIndex = 0;
            this.cboCropCol.Text = "0";
            this.cboCropCol.Validating += new System.ComponentModel.CancelEventHandler(this.cboIntVal_Validating);
            // 
            // cboCropWidth
            // 
            this.cboCropWidth.FormattingEnabled = true;
            this.cboCropWidth.Items.AddRange(new object[] {
            "8",
            "16",
            "32",
            "64",
            "100",
            "128",
            "256",
            "512"});
            this.cboCropWidth.Location = new System.Drawing.Point(390, 6);
            this.cboCropWidth.Name = "cboCropWidth";
            this.cboCropWidth.Size = new System.Drawing.Size(61, 21);
            this.cboCropWidth.TabIndex = 4;
            this.cboCropWidth.Text = "100";
            this.cboCropWidth.Validating += new System.ComponentModel.CancelEventHandler(this.cboIntVal_Validating);
            // 
            // lblCropHeight
            // 
            this.lblCropHeight.AutoSize = true;
            this.lblCropHeight.Location = new System.Drawing.Point(455, 9);
            this.lblCropHeight.Name = "lblCropHeight";
            this.lblCropHeight.Size = new System.Drawing.Size(57, 13);
            this.lblCropHeight.TabIndex = 7;
            this.lblCropHeight.Text = "and height";
            // 
            // lblCropWidth
            // 
            this.lblCropWidth.AutoSize = true;
            this.lblCropWidth.Location = new System.Drawing.Point(330, 9);
            this.lblCropWidth.Name = "lblCropWidth";
            this.lblCropWidth.Size = new System.Drawing.Size(54, 13);
            this.lblCropWidth.TabIndex = 5;
            this.lblCropWidth.Text = "with width";
            // 
            // lblCropRow
            // 
            this.lblCropRow.AutoSize = true;
            this.lblCropRow.Location = new System.Drawing.Point(215, 9);
            this.lblCropRow.Name = "lblCropRow";
            this.lblCropRow.Size = new System.Drawing.Size(45, 13);
            this.lblCropRow.TabIndex = 3;
            this.lblCropRow.Text = "and row";
            // 
            // lblCropCol
            // 
            this.lblCropCol.AutoSize = true;
            this.lblCropCol.Location = new System.Drawing.Point(3, 9);
            this.lblCropCol.Name = "lblCropCol";
            this.lblCropCol.Size = new System.Drawing.Size(139, 13);
            this.lblCropCol.TabIndex = 1;
            this.lblCropCol.Text = "Upper-Left corner at column";
            // 
            // rbZoom
            // 
            this.rbZoom.AutoSize = true;
            this.rbZoom.Location = new System.Drawing.Point(20, 340);
            this.rbZoom.Name = "rbZoom";
            this.rbZoom.Size = new System.Drawing.Size(52, 17);
            this.rbZoom.TabIndex = 5;
            this.rbZoom.TabStop = true;
            this.rbZoom.Text = "Zoom";
            this.rbZoom.UseVisualStyleBackColor = true;
            this.rbZoom.CheckedChanged += new System.EventHandler(this.rbPreProcessing_CheckedChanged);
            // 
            // rbCrop
            // 
            this.rbCrop.AutoSize = true;
            this.rbCrop.Location = new System.Drawing.Point(20, 315);
            this.rbCrop.Name = "rbCrop";
            this.rbCrop.Size = new System.Drawing.Size(47, 17);
            this.rbCrop.TabIndex = 3;
            this.rbCrop.TabStop = true;
            this.rbCrop.Text = "Crop";
            this.rbCrop.UseVisualStyleBackColor = true;
            this.rbCrop.CheckedChanged += new System.EventHandler(this.rbPreProcessing_CheckedChanged);
            // 
            // grpZoom
            // 
            this.grpZoom.Controls.Add(this.grpZoomLocation);
            this.grpZoom.Controls.Add(this.pnlCropp);
            this.grpZoom.Location = new System.Drawing.Point(5, 295);
            this.grpZoom.Name = "grpZoom";
            this.grpZoom.Size = new System.Drawing.Size(670, 80);
            this.grpZoom.TabIndex = 32;
            this.grpZoom.TabStop = false;
            this.grpZoom.Text = "Geometry";
            // 
            // rbGrayLevelQ
            // 
            this.rbGrayLevelQ.AutoSize = true;
            this.rbGrayLevelQ.Location = new System.Drawing.Point(20, 395);
            this.rbGrayLevelQ.Name = "rbGrayLevelQ";
            this.rbGrayLevelQ.Size = new System.Drawing.Size(108, 17);
            this.rbGrayLevelQ.TabIndex = 7;
            this.rbGrayLevelQ.TabStop = true;
            this.rbGrayLevelQ.Text = "Gray Level Quant";
            this.rbGrayLevelQ.UseVisualStyleBackColor = true;
            this.rbGrayLevelQ.CheckedChanged += new System.EventHandler(this.rbPreProcessing_CheckedChanged);
            // 
            // grpQuantization
            // 
            this.grpQuantization.Controls.Add(this.pnlGrayLevelQ);
            this.grpQuantization.Controls.Add(this.pnlSpatialQuant);
            this.grpQuantization.Location = new System.Drawing.Point(6, 375);
            this.grpQuantization.Name = "grpQuantization";
            this.grpQuantization.Size = new System.Drawing.Size(670, 65);
            this.grpQuantization.TabIndex = 9;
            this.grpQuantization.TabStop = false;
            this.grpQuantization.Text = "Quantization";
            // 
            // pnlGrayLevelQ
            // 
            this.pnlGrayLevelQ.Controls.Add(this.rdbUtilConvertStandard);
            this.pnlGrayLevelQ.Controls.Add(this.label5);
            this.pnlGrayLevelQ.Controls.Add(this.cmbUtilConvertNumOfBits);
            this.pnlGrayLevelQ.Controls.Add(this.rdbUtilConvertIGS);
            this.pnlGrayLevelQ.Location = new System.Drawing.Point(170, 16);
            this.pnlGrayLevelQ.Name = "pnlGrayLevelQ";
            this.pnlGrayLevelQ.Size = new System.Drawing.Size(320, 35);
            this.pnlGrayLevelQ.TabIndex = 41;
            // 
            // rdbUtilConvertStandard
            // 
            this.rdbUtilConvertStandard.AutoSize = true;
            this.rdbUtilConvertStandard.Checked = true;
            this.rdbUtilConvertStandard.Location = new System.Drawing.Point(6, 3);
            this.rdbUtilConvertStandard.Name = "rdbUtilConvertStandard";
            this.rdbUtilConvertStandard.Size = new System.Drawing.Size(68, 17);
            this.rdbUtilConvertStandard.TabIndex = 5;
            this.rdbUtilConvertStandard.TabStop = true;
            this.rdbUtilConvertStandard.Text = "Standard";
            this.rdbUtilConvertStandard.UseVisualStyleBackColor = true;
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(130, 5);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(109, 13);
            this.label5.TabIndex = 0;
            this.label5.Text = "Number of gray levels";
            // 
            // cmbUtilConvertNumOfBits
            // 
            this.cmbUtilConvertNumOfBits.FormattingEnabled = true;
            this.cmbUtilConvertNumOfBits.Items.AddRange(new object[] {
            "2",
            "4",
            "8",
            "16",
            "32",
            "64",
            "128"});
            this.cmbUtilConvertNumOfBits.Location = new System.Drawing.Point(240, 2);
            this.cmbUtilConvertNumOfBits.Name = "cmbUtilConvertNumOfBits";
            this.cmbUtilConvertNumOfBits.Size = new System.Drawing.Size(66, 21);
            this.cmbUtilConvertNumOfBits.TabIndex = 2;
            this.cmbUtilConvertNumOfBits.Text = "16";
            // 
            // rdbUtilConvertIGS
            // 
            this.rdbUtilConvertIGS.AutoSize = true;
            this.rdbUtilConvertIGS.Location = new System.Drawing.Point(85, 3);
            this.rdbUtilConvertIGS.Name = "rdbUtilConvertIGS";
            this.rdbUtilConvertIGS.Size = new System.Drawing.Size(43, 17);
            this.rdbUtilConvertIGS.TabIndex = 6;
            this.rdbUtilConvertIGS.Text = "IGS";
            this.rdbUtilConvertIGS.UseVisualStyleBackColor = true;
            // 
            // pnlSpatialQuant
            // 
            this.pnlSpatialQuant.Controls.Add(this.lblSpatialQuantMethod);
            this.pnlSpatialQuant.Controls.Add(this.cboSpatialQuantMethod);
            this.pnlSpatialQuant.Controls.Add(this.lblSpatialQuantHeight);
            this.pnlSpatialQuant.Controls.Add(this.cboSpatialQuantHeight);
            this.pnlSpatialQuant.Controls.Add(this.lblSpatialQuantWidth);
            this.pnlSpatialQuant.Controls.Add(this.cboSpatialQuantWidth);
            this.pnlSpatialQuant.Location = new System.Drawing.Point(159, 16);
            this.pnlSpatialQuant.Name = "pnlSpatialQuant";
            this.pnlSpatialQuant.Size = new System.Drawing.Size(460, 40);
            this.pnlSpatialQuant.TabIndex = 40;
            // 
            // lblSpatialQuantMethod
            // 
            this.lblSpatialQuantMethod.AutoSize = true;
            this.lblSpatialQuantMethod.Location = new System.Drawing.Point(226, 10);
            this.lblSpatialQuantMethod.Name = "lblSpatialQuantMethod";
            this.lblSpatialQuantMethod.Size = new System.Drawing.Size(72, 13);
            this.lblSpatialQuantMethod.TabIndex = 5;
            this.lblSpatialQuantMethod.Text = "Using method";
            // 
            // cboSpatialQuantMethod
            // 
            this.cboSpatialQuantMethod.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cboSpatialQuantMethod.FormattingEnabled = true;
            this.cboSpatialQuantMethod.Items.AddRange(new object[] {
            "Average Value",
            "Median Value",
            "Decimation"});
            this.cboSpatialQuantMethod.Location = new System.Drawing.Point(298, 7);
            this.cboSpatialQuantMethod.Name = "cboSpatialQuantMethod";
            this.cboSpatialQuantMethod.Size = new System.Drawing.Size(132, 21);
            this.cboSpatialQuantMethod.TabIndex = 4;
            // 
            // lblSpatialQuantHeight
            // 
            this.lblSpatialQuantHeight.AutoSize = true;
            this.lblSpatialQuantHeight.Location = new System.Drawing.Point(108, 10);
            this.lblSpatialQuantHeight.Name = "lblSpatialQuantHeight";
            this.lblSpatialQuantHeight.Size = new System.Drawing.Size(57, 13);
            this.lblSpatialQuantHeight.TabIndex = 3;
            this.lblSpatialQuantHeight.Text = "and height";
            // 
            // cboSpatialQuantHeight
            // 
            this.cboSpatialQuantHeight.FormattingEnabled = true;
            this.cboSpatialQuantHeight.Items.AddRange(new object[] {
            "32",
            "64",
            "128",
            "256"});
            this.cboSpatialQuantHeight.Location = new System.Drawing.Point(166, 6);
            this.cboSpatialQuantHeight.Name = "cboSpatialQuantHeight";
            this.cboSpatialQuantHeight.Size = new System.Drawing.Size(49, 21);
            this.cboSpatialQuantHeight.TabIndex = 2;
            this.cboSpatialQuantHeight.Text = "32";
            this.cboSpatialQuantHeight.Validating += new System.ComponentModel.CancelEventHandler(this.cboIntVal_Validating);
            // 
            // lblSpatialQuantWidth
            // 
            this.lblSpatialQuantWidth.AutoSize = true;
            this.lblSpatialQuantWidth.Location = new System.Drawing.Point(3, 10);
            this.lblSpatialQuantWidth.Name = "lblSpatialQuantWidth";
            this.lblSpatialQuantWidth.Size = new System.Drawing.Size(48, 13);
            this.lblSpatialQuantWidth.TabIndex = 1;
            this.lblSpatialQuantWidth.Text = "To width";
            // 
            // cboSpatialQuantWidth
            // 
            this.cboSpatialQuantWidth.FormattingEnabled = true;
            this.cboSpatialQuantWidth.Items.AddRange(new object[] {
            "32",
            "64",
            "128",
            "256"});
            this.cboSpatialQuantWidth.Location = new System.Drawing.Point(53, 6);
            this.cboSpatialQuantWidth.Name = "cboSpatialQuantWidth";
            this.cboSpatialQuantWidth.Size = new System.Drawing.Size(49, 21);
            this.cboSpatialQuantWidth.TabIndex = 0;
            this.cboSpatialQuantWidth.Text = "32";
            this.cboSpatialQuantWidth.Validating += new System.ComponentModel.CancelEventHandler(this.cboIntVal_Validating);
            // 
            // rbSpatialQuant
            // 
            this.rbSpatialQuant.AutoSize = true;
            this.rbSpatialQuant.Location = new System.Drawing.Point(20, 415);
            this.rbSpatialQuant.Name = "rbSpatialQuant";
            this.rbSpatialQuant.Size = new System.Drawing.Size(119, 17);
            this.rbSpatialQuant.TabIndex = 41;
            this.rbSpatialQuant.TabStop = true;
            this.rbSpatialQuant.Text = "Spatial Quantization";
            this.rbSpatialQuant.UseVisualStyleBackColor = true;
            this.rbSpatialQuant.CheckedChanged += new System.EventHandler(this.rbPreProcessing_CheckedChanged);
            // 
            // grpHistogram
            // 
            this.grpHistogram.Controls.Add(this.pnlHistStretch);
            this.grpHistogram.Controls.Add(this.pnlHistogramEQ);
            this.grpHistogram.Location = new System.Drawing.Point(5, 438);
            this.grpHistogram.Name = "grpHistogram";
            this.grpHistogram.Size = new System.Drawing.Size(670, 70);
            this.grpHistogram.TabIndex = 33;
            this.grpHistogram.TabStop = false;
            this.grpHistogram.Text = "Histogram";
            // 
            // pnlHistStretch
            // 
            this.pnlHistStretch.Controls.Add(this.lblHighPercent);
            this.pnlHistStretch.Controls.Add(this.lblLowPercent);
            this.pnlHistStretch.Controls.Add(this.lblLowLimit);
            this.pnlHistStretch.Controls.Add(this.cboHighClip);
            this.pnlHistStretch.Controls.Add(this.cboLowLimit);
            this.pnlHistStretch.Controls.Add(this.lblHighLimit);
            this.pnlHistStretch.Controls.Add(this.cboHighLimit);
            this.pnlHistStretch.Controls.Add(this.lblHighClip);
            this.pnlHistStretch.Controls.Add(this.lblLowClip);
            this.pnlHistStretch.Controls.Add(this.cboLowClip);
            this.pnlHistStretch.Location = new System.Drawing.Point(170, 13);
            this.pnlHistStretch.Name = "pnlHistStretch";
            this.pnlHistStretch.Size = new System.Drawing.Size(494, 54);
            this.pnlHistStretch.TabIndex = 34;
            // 
            // lblHighPercent
            // 
            this.lblHighPercent.AutoSize = true;
            this.lblHighPercent.ForeColor = System.Drawing.Color.Blue;
            this.lblHighPercent.Location = new System.Drawing.Point(306, 32);
            this.lblHighPercent.Name = "lblHighPercent";
            this.lblHighPercent.Size = new System.Drawing.Size(30, 13);
            this.lblHighPercent.TabIndex = 43;
            this.lblHighPercent.Text = "2.5%";
            // 
            // lblLowPercent
            // 
            this.lblLowPercent.AutoSize = true;
            this.lblLowPercent.ForeColor = System.Drawing.Color.Blue;
            this.lblLowPercent.Location = new System.Drawing.Point(306, 8);
            this.lblLowPercent.Name = "lblLowPercent";
            this.lblLowPercent.Size = new System.Drawing.Size(30, 13);
            this.lblLowPercent.TabIndex = 42;
            this.lblLowPercent.Text = "2.5%";
            // 
            // lblLowLimit
            // 
            this.lblLowLimit.AutoSize = true;
            this.lblLowLimit.Location = new System.Drawing.Point(30, 7);
            this.lblLowLimit.Name = "lblLowLimit";
            this.lblLowLimit.Size = new System.Drawing.Size(50, 13);
            this.lblLowLimit.TabIndex = 34;
            this.lblLowLimit.Text = "Low limit:";
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
            this.cboHighClip.Location = new System.Drawing.Point(236, 29);
            this.cboHighClip.Name = "cboHighClip";
            this.cboHighClip.Size = new System.Drawing.Size(64, 21);
            this.cboHighClip.TabIndex = 41;
            this.cboHighClip.Text = "0.025";
            this.cboHighClip.TextChanged += new System.EventHandler(this.Percent_TextChanged);
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
            this.cboLowLimit.Location = new System.Drawing.Point(83, 4);
            this.cboLowLimit.Name = "cboLowLimit";
            this.cboLowLimit.Size = new System.Drawing.Size(44, 21);
            this.cboLowLimit.TabIndex = 35;
            this.cboLowLimit.Text = "0";
            this.cboLowLimit.Validating += new System.ComponentModel.CancelEventHandler(this.cboIntVal_Validating);
            // 
            // lblHighLimit
            // 
            this.lblHighLimit.AutoSize = true;
            this.lblHighLimit.Location = new System.Drawing.Point(29, 32);
            this.lblHighLimit.Name = "lblHighLimit";
            this.lblHighLimit.Size = new System.Drawing.Size(52, 13);
            this.lblHighLimit.TabIndex = 36;
            this.lblHighLimit.Text = "High limit:";
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
            this.cboHighLimit.Location = new System.Drawing.Point(83, 30);
            this.cboHighLimit.Name = "cboHighLimit";
            this.cboHighLimit.Size = new System.Drawing.Size(44, 21);
            this.cboHighLimit.TabIndex = 37;
            this.cboHighLimit.Text = "255";
            this.cboHighLimit.Validating += new System.ComponentModel.CancelEventHandler(this.cboIntVal_Validating);
            // 
            // lblHighClip
            // 
            this.lblHighClip.AutoSize = true;
            this.lblHighClip.Location = new System.Drawing.Point(140, 32);
            this.lblHighClip.Name = "lblHighClip";
            this.lblHighClip.Size = new System.Drawing.Size(90, 13);
            this.lblHighClip.TabIndex = 40;
            this.lblHighClip.Text = "High clip percent:";
            // 
            // lblLowClip
            // 
            this.lblLowClip.AutoSize = true;
            this.lblLowClip.Location = new System.Drawing.Point(140, 7);
            this.lblLowClip.Name = "lblLowClip";
            this.lblLowClip.Size = new System.Drawing.Size(88, 13);
            this.lblLowClip.TabIndex = 38;
            this.lblLowClip.Text = "Low clip percent:";
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
            this.cboLowClip.Location = new System.Drawing.Point(236, 4);
            this.cboLowClip.Name = "cboLowClip";
            this.cboLowClip.Size = new System.Drawing.Size(64, 21);
            this.cboLowClip.TabIndex = 39;
            this.cboLowClip.Text = "0.025";
            this.cboLowClip.TextChanged += new System.EventHandler(this.Percent_TextChanged);
            // 
            // pnlHistogramEQ
            // 
            this.pnlHistogramEQ.Controls.Add(this.rbBlue);
            this.pnlHistogramEQ.Controls.Add(this.lblBand);
            this.pnlHistogramEQ.Controls.Add(this.rbGreen);
            this.pnlHistogramEQ.Controls.Add(this.rbRed);
            this.pnlHistogramEQ.Controls.Add(this.rbValue);
            this.pnlHistogramEQ.Location = new System.Drawing.Point(170, 15);
            this.pnlHistogramEQ.Name = "pnlHistogramEQ";
            this.pnlHistogramEQ.Size = new System.Drawing.Size(449, 37);
            this.pnlHistogramEQ.TabIndex = 4;
            // 
            // rbBlue
            // 
            this.rbBlue.AutoSize = true;
            this.rbBlue.Location = new System.Drawing.Point(302, 4);
            this.rbBlue.Name = "rbBlue";
            this.rbBlue.Size = new System.Drawing.Size(46, 17);
            this.rbBlue.TabIndex = 8;
            this.rbBlue.Text = "Blue";
            this.rbBlue.UseVisualStyleBackColor = true;
            // 
            // lblBand
            // 
            this.lblBand.AutoSize = true;
            this.lblBand.Location = new System.Drawing.Point(13, 6);
            this.lblBand.Name = "lblBand";
            this.lblBand.Size = new System.Drawing.Size(52, 13);
            this.lblBand.TabIndex = 9;
            this.lblBand.Text = "On Band:";
            // 
            // rbGreen
            // 
            this.rbGreen.AutoSize = true;
            this.rbGreen.Location = new System.Drawing.Point(230, 4);
            this.rbGreen.Name = "rbGreen";
            this.rbGreen.Size = new System.Drawing.Size(54, 17);
            this.rbGreen.TabIndex = 7;
            this.rbGreen.Text = "Green";
            this.rbGreen.UseVisualStyleBackColor = true;
            // 
            // rbRed
            // 
            this.rbRed.AutoSize = true;
            this.rbRed.Location = new System.Drawing.Point(168, 5);
            this.rbRed.Name = "rbRed";
            this.rbRed.Size = new System.Drawing.Size(45, 17);
            this.rbRed.TabIndex = 6;
            this.rbRed.Text = "Red";
            this.rbRed.UseVisualStyleBackColor = true;
            // 
            // rbValue
            // 
            this.rbValue.AutoSize = true;
            this.rbValue.Checked = true;
            this.rbValue.Location = new System.Drawing.Point(85, 4);
            this.rbValue.Name = "rbValue";
            this.rbValue.Size = new System.Drawing.Size(70, 17);
            this.rbValue.TabIndex = 5;
            this.rbValue.TabStop = true;
            this.rbValue.Text = "Lightness";
            this.rbValue.UseVisualStyleBackColor = true;
            // 
            // rbHistStretch
            // 
            this.rbHistStretch.AutoSize = true;
            this.rbHistStretch.Location = new System.Drawing.Point(20, 480);
            this.rbHistStretch.Name = "rbHistStretch";
            this.rbHistStretch.Size = new System.Drawing.Size(109, 17);
            this.rbHistStretch.TabIndex = 3;
            this.rbHistStretch.Text = "Histogram Stretch";
            this.rbHistStretch.UseVisualStyleBackColor = true;
            this.rbHistStretch.CheckedChanged += new System.EventHandler(this.rbPreProcessing_CheckedChanged);
            // 
            // rbHistEQ
            // 
            this.rbHistEQ.AutoSize = true;
            this.rbHistEQ.Checked = true;
            this.rbHistEQ.Location = new System.Drawing.Point(20, 460);
            this.rbHistEQ.Name = "rbHistEQ";
            this.rbHistEQ.Size = new System.Drawing.Size(132, 17);
            this.rbHistEQ.TabIndex = 1;
            this.rbHistEQ.TabStop = true;
            this.rbHistEQ.Text = "Histogram Equalization";
            this.rbHistEQ.UseVisualStyleBackColor = true;
            this.rbHistEQ.CheckedChanged += new System.EventHandler(this.rbPreProcessing_CheckedChanged);
            // 
            // Preprocessing
            // 
            this.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.Controls.Add(this.rbAdd);
            this.Controls.Add(this.rbSubtract);
            this.Controls.Add(this.rbMultiply);
            this.Controls.Add(this.rbDivide);
            this.Controls.Add(this.rbAnd);
            this.Controls.Add(this.rbNot);
            this.Controls.Add(this.rbOr);
            this.Controls.Add(this.rbXor);
            this.Controls.Add(this.rbMeanFilter);
            this.Controls.Add(this.rbGaussian);
            this.Controls.Add(this.rbMedian);
            this.Controls.Add(this.rbLaplacian);
            this.Controls.Add(this.rbDifference);
            this.Controls.Add(this.rbCrop);
            this.Controls.Add(this.rbZoom);
            this.Controls.Add(this.rbGrayLevelQ);
            this.Controls.Add(this.rbSpatialQuant);
            this.Controls.Add(this.rbHistEQ);
            this.Controls.Add(this.rbHistStretch);
            this.Controls.Add(this.grpHistogram);
            this.Controls.Add(this.grpQuantization);
            this.Controls.Add(this.grpZoom);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.grp_Arithmetic);
            this.Controls.Add(this.btnHelp);
            this.Controls.Add(this.btnCancel);
            this.Controls.Add(this.btnReset);
            this.Controls.Add(this.btnApply);
            this.Name = "Preprocessing";
            this.Size = new System.Drawing.Size(679, 555);
            this.grp_Arithmetic.ResumeLayout(false);
            this.grp_Arithmetic.PerformLayout();
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.pnlGaussian.ResumeLayout(false);
            this.pnlGaussian.PerformLayout();
            this.pnlDifference.ResumeLayout(false);
            this.pnlDifference.PerformLayout();
            this.pnlLaplacian.ResumeLayout(false);
            this.pnlLaplacian.PerformLayout();
            this.pnlMedian.ResumeLayout(false);
            this.pnlMedian.PerformLayout();
            this.grpZoomLocation.ResumeLayout(false);
            this.grpZoomLocation.PerformLayout();
            this.pnlCropp.ResumeLayout(false);
            this.pnlCropp.PerformLayout();
            this.grpZoom.ResumeLayout(false);
            this.grpQuantization.ResumeLayout(false);
            this.pnlGrayLevelQ.ResumeLayout(false);
            this.pnlGrayLevelQ.PerformLayout();
            this.pnlSpatialQuant.ResumeLayout(false);
            this.pnlSpatialQuant.PerformLayout();
            this.grpHistogram.ResumeLayout(false);
            this.pnlHistStretch.ResumeLayout(false);
            this.pnlHistStretch.PerformLayout();
            this.pnlHistogramEQ.ResumeLayout(false);
            this.pnlHistogramEQ.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button btnApply;
        private System.Windows.Forms.Button btnReset;
        private System.Windows.Forms.Button btnCancel;
        private System.Windows.Forms.Button btnHelp;
        private System.Windows.Forms.GroupBox grp_Arithmetic;
        private System.Windows.Forms.RadioButton rbAdd;
        private System.Windows.Forms.RadioButton rbSubtract;
        private System.Windows.Forms.ComboBox cboSecondImage;
        private System.Windows.Forms.ToolTip toolTipImage2;
        private System.Windows.Forms.TextBox txtCurrentImage;
        private System.Windows.Forms.RadioButton rbDivide;
        private System.Windows.Forms.RadioButton rbMultiply;
        private System.Windows.Forms.RadioButton rbXor;
        private System.Windows.Forms.RadioButton rbOr;
        private System.Windows.Forms.RadioButton rbNot;
        private System.Windows.Forms.RadioButton rbAnd;
        private System.Windows.Forms.Label lblSecondImage;
        private System.Windows.Forms.Label CurrentImageLabel;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.RadioButton rbMeanFilter;
        private System.Windows.Forms.RadioButton rbAdaptive;
        private System.Windows.Forms.RadioButton rbStandard;
        private System.Windows.Forms.ComboBox cboMaskSize;
        private System.Windows.Forms.Label lblMaskSize;
        private System.Windows.Forms.RadioButton rbDifference;
        private System.Windows.Forms.RadioButton rbLaplacian;
        private System.Windows.Forms.RadioButton rbMedian;
        private System.Windows.Forms.RadioButton rbGaussian;
        private System.Windows.Forms.RadioButton rb11x11;
        private System.Windows.Forms.RadioButton rb9x9;
        private System.Windows.Forms.RadioButton rb7x7;
        private System.Windows.Forms.RadioButton rb5x5;
        private System.Windows.Forms.RadioButton rb3x3;
        private System.Windows.Forms.RadioButton rbType3;
        private System.Windows.Forms.RadioButton rbType2;
        private System.Windows.Forms.RadioButton rbType1;
        private System.Windows.Forms.Button btnEditMask;
        private System.Windows.Forms.CheckBox chkNormalize;
        private System.Windows.Forms.RadioButton rbGaussian11x11;
        private System.Windows.Forms.RadioButton rbGaussian9x9;
        private System.Windows.Forms.RadioButton rbGaussianz7x7;
        private System.Windows.Forms.RadioButton rbGaussian5x5;
        private System.Windows.Forms.RadioButton rbGaussian3x3;
        private System.Windows.Forms.Panel pnlCropp;
        private System.Windows.Forms.Label lblCropHeight;
        private System.Windows.Forms.ComboBox cboCropHeight;
        private System.Windows.Forms.Label lblCropWidth;
        private System.Windows.Forms.ComboBox cboCropWidth;
        private System.Windows.Forms.Label lblCropRow;
        private System.Windows.Forms.ComboBox cboCropRow;
        private System.Windows.Forms.Label lblCropCol;
        private System.Windows.Forms.ComboBox cboCropCol;
        private System.Windows.Forms.RadioButton rbCrop;
        private System.Windows.Forms.GroupBox grpZoom;
        private System.Windows.Forms.GroupBox grpZoomLocation;
        private System.Windows.Forms.Label lblZoomPixels;
        private System.Windows.Forms.ComboBox cboZoomHeight;
        private System.Windows.Forms.Label lblZoomHeight;
        private System.Windows.Forms.ComboBox cboZoomWidth;
        private System.Windows.Forms.Label lblZoomWidth;
        private System.Windows.Forms.ComboBox cboZoomRow;
        private System.Windows.Forms.Label lblZoomRow;
        private System.Windows.Forms.ComboBox cboZoomCol;
        private System.Windows.Forms.ComboBox cboZoomMethod;
        private System.Windows.Forms.Label lblZoomMethod;
        private System.Windows.Forms.ComboBox cboZoomFactor;
        private System.Windows.Forms.Label lblZoomFactor;
        private System.Windows.Forms.RadioButton rbZoom;
        private System.Windows.Forms.RadioButton rbGrayLevelQ;
        private System.Windows.Forms.Panel pnlMedian;
        private System.Windows.Forms.Panel pnlGaussian;
        private System.Windows.Forms.Panel pnlDifference;
        private System.Windows.Forms.Panel pnlLaplacian;
        private System.Windows.Forms.GroupBox grpQuantization;
        private System.Windows.Forms.RadioButton rbSpatialQuant;
        private System.Windows.Forms.Panel pnlSpatialQuant;
        private System.Windows.Forms.Label lblSpatialQuantMethod;
        private System.Windows.Forms.ComboBox cboSpatialQuantMethod;
        private System.Windows.Forms.Label lblSpatialQuantHeight;
        private System.Windows.Forms.ComboBox cboSpatialQuantHeight;
        private System.Windows.Forms.Label lblSpatialQuantWidth;
        private System.Windows.Forms.ComboBox cboSpatialQuantWidth;
        private System.Windows.Forms.Label lblZoompt1;
        private System.Windows.Forms.GroupBox grpHistogram;
        private System.Windows.Forms.RadioButton rbHistEQ;
        private System.Windows.Forms.RadioButton rbHistStretch;
        private System.Windows.Forms.Panel pnlHistogramEQ;
        private System.Windows.Forms.RadioButton rbBlue;
        private System.Windows.Forms.Label lblBand;
        private System.Windows.Forms.RadioButton rbGreen;
        private System.Windows.Forms.RadioButton rbRed;
        private System.Windows.Forms.RadioButton rbValue;
        private System.Windows.Forms.ComboBox cboHighClip;
        private System.Windows.Forms.Label lblHighClip;
        private System.Windows.Forms.Label lblLowLimit;
        private System.Windows.Forms.ComboBox cboLowLimit;
        private System.Windows.Forms.Label lblHighLimit;
        private System.Windows.Forms.ComboBox cboLowClip;
        private System.Windows.Forms.ComboBox cboHighLimit;
        private System.Windows.Forms.Label lblLowClip;
        private System.Windows.Forms.Panel pnlHistStretch;
        private System.Windows.Forms.Panel pnlGrayLevelQ;
        private System.Windows.Forms.RadioButton rdbUtilConvertStandard;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.ComboBox cmbUtilConvertNumOfBits;
        private System.Windows.Forms.RadioButton rdbUtilConvertIGS;
        private System.Windows.Forms.Label lblLaplacianType;
        private System.Windows.Forms.Label lblMedianType;
        private System.Windows.Forms.Label lblGaussMask;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label lblHighPercent;
        private System.Windows.Forms.Label lblLowPercent;
    }
}
