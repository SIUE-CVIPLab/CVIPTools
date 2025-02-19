namespace CVIPGUI.Utilities
{
    partial class UtilFilter
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
            this.grpFilter = new System.Windows.Forms.GroupBox();
            this.lblCurrentImage = new System.Windows.Forms.Label();
            this.txtCurrentImage = new System.Windows.Forms.Label();
            this.pnlMean = new System.Windows.Forms.Panel();
            this.lblMaskSizeMean = new System.Windows.Forms.Label();
            this.cboMaskSizeMean = new System.Windows.Forms.ComboBox();
            this.pnlMedian = new System.Windows.Forms.Panel();
            this.lblMaskSizeMedian = new System.Windows.Forms.Label();
            this.cboMaskSizeMedian = new System.Windows.Forms.ComboBox();
            this.rbAdaptiveMedian = new System.Windows.Forms.RadioButton();
            this.rbStandardMedian = new System.Windows.Forms.RadioButton();
            this.pnlLaplacian = new System.Windows.Forms.Panel();
            this.lblFilterType = new System.Windows.Forms.Label();
            this.rbLaplacianType3 = new System.Windows.Forms.RadioButton();
            this.rbLaplacianType2 = new System.Windows.Forms.RadioButton();
            this.rbLaplacianType1 = new System.Windows.Forms.RadioButton();
            this.pnlDifference = new System.Windows.Forms.Panel();
            this.lblDifferenceSize = new System.Windows.Forms.Label();
            this.rbDifference11x11 = new System.Windows.Forms.RadioButton();
            this.rbDifference9x9 = new System.Windows.Forms.RadioButton();
            this.rbDifference7x7 = new System.Windows.Forms.RadioButton();
            this.rbDifference5x5 = new System.Windows.Forms.RadioButton();
            this.rbDifference3x3 = new System.Windows.Forms.RadioButton();
            this.pnlSpecifyFilter = new System.Windows.Forms.Panel();
            this.lblSpecifyFilterSize = new System.Windows.Forms.Label();
            this.rbSpecifyFilter11x11 = new System.Windows.Forms.RadioButton();
            this.rbSpecifyFilter9x9 = new System.Windows.Forms.RadioButton();
            this.rbSpecifyFilter7x7 = new System.Windows.Forms.RadioButton();
            this.rbSpecifyFilter5x5 = new System.Windows.Forms.RadioButton();
            this.rbSpecifyFilter3x3 = new System.Windows.Forms.RadioButton();
            this.chkNormalized = new System.Windows.Forms.CheckBox();
            this.lblSpecifyFilter = new System.Windows.Forms.Label();
            this.cboSpecifyFilter = new System.Windows.Forms.ComboBox();
            this.pnlSpecifyBlur = new System.Windows.Forms.Panel();
            this.lblBlurWeight = new System.Windows.Forms.Label();
            this.cboBlurWeight = new System.Windows.Forms.ComboBox();
            this.lblBlurMethod = new System.Windows.Forms.Label();
            this.cboBlurMethod = new System.Windows.Forms.ComboBox();
            //this.lblShapeHeight = new System.Windows.Forms.Label();
            //this.cboShapeHeight = new System.Windows.Forms.ComboBox();
            //this.lblShapeWidth = new System.Windows.Forms.Label();
            //this.cboShapeWidth = new System.Windows.Forms.ComboBox();
            this.lblBlurShape = new System.Windows.Forms.Label();
            this.cboBlurShape = new System.Windows.Forms.ComboBox();
            this.lblMaskHeight = new System.Windows.Forms.Label();
            this.cboMaskHeight = new System.Windows.Forms.ComboBox();
            this.lblMaskWidth = new System.Windows.Forms.Label();
            this.cboMaskWidth = new System.Windows.Forms.ComboBox();
            this.btnEditMask = new System.Windows.Forms.Button();
            this.btnHelp = new System.Windows.Forms.Button();
            this.btnCancel = new System.Windows.Forms.Button();
            this.btnReset = new System.Windows.Forms.Button();
            this.btnApply = new System.Windows.Forms.Button();
            this.grpFilter.SuspendLayout();
            this.pnlMean.SuspendLayout();
            this.pnlMedian.SuspendLayout();
            this.pnlLaplacian.SuspendLayout();
            this.pnlDifference.SuspendLayout();
            this.pnlSpecifyFilter.SuspendLayout();
            this.pnlSpecifyBlur.SuspendLayout();
            this.SuspendLayout();
            // 
            // grpFilter
            // 
            this.grpFilter.Controls.Add(this.lblCurrentImage);
            this.grpFilter.Controls.Add(this.txtCurrentImage);
            this.grpFilter.Location = new System.Drawing.Point(1, -4);
            this.grpFilter.Name = "grpFilter";
            this.grpFilter.Size = new System.Drawing.Size(430, 107);
            this.grpFilter.TabIndex = 0;
            this.grpFilter.TabStop = false;
            // 
            // lblCurrentImage
            // 
            this.lblCurrentImage.AutoSize = true;
            this.lblCurrentImage.Location = new System.Drawing.Point(7, 8);
            this.lblCurrentImage.Name = "lblCurrentImage";
            this.lblCurrentImage.Size = new System.Drawing.Size(76, 13);
            this.lblCurrentImage.TabIndex = 1;
            this.lblCurrentImage.Text = "Current Image:";
            // 
            // txtCurrentImage
            // 
            this.txtCurrentImage.AutoSize = true;
            this.txtCurrentImage.ForeColor = System.Drawing.Color.Blue;
            this.txtCurrentImage.Location = new System.Drawing.Point(84, 8);
            this.txtCurrentImage.Name = "txtCurrentImage";
            this.txtCurrentImage.Size = new System.Drawing.Size(81, 13);
            this.txtCurrentImage.TabIndex = 0;
            this.txtCurrentImage.Text = "txtCurrentImage";
            // 
            // pnlMean
            // 
            this.pnlMean.Controls.Add(this.lblMaskSizeMean);
            this.pnlMean.Controls.Add(this.cboMaskSizeMean);
            this.pnlMean.Location = new System.Drawing.Point(11, 153);
            this.pnlMean.Name = "pnlMean";
            this.pnlMean.Size = new System.Drawing.Size(420, 75);
            this.pnlMean.TabIndex = 1;
            // 
            // lblMaskSizeMean
            // 
            this.lblMaskSizeMean.AutoSize = true;
            this.lblMaskSizeMean.Location = new System.Drawing.Point(3, 6);
            this.lblMaskSizeMean.Name = "lblMaskSizeMean";
            this.lblMaskSizeMean.Size = new System.Drawing.Size(56, 13);
            this.lblMaskSizeMean.TabIndex = 1;
            this.lblMaskSizeMean.Text = "Mask Size";
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
            this.cboMaskSizeMean.Location = new System.Drawing.Point(64, 3);
            this.cboMaskSizeMean.Name = "cboMaskSizeMean";
            this.cboMaskSizeMean.Size = new System.Drawing.Size(73, 21);
            this.cboMaskSizeMean.TabIndex = 0;
            this.cboMaskSizeMean.Validating += new System.ComponentModel.CancelEventHandler(this.cboMaskSize_Validating);
            // 
            // pnlMedian
            // 
            this.pnlMedian.Controls.Add(this.lblMaskSizeMedian);
            this.pnlMedian.Controls.Add(this.cboMaskSizeMedian);
            this.pnlMedian.Controls.Add(this.rbAdaptiveMedian);
            this.pnlMedian.Controls.Add(this.rbStandardMedian);
            this.pnlMedian.Location = new System.Drawing.Point(11, 234);
            this.pnlMedian.Name = "pnlMedian";
            this.pnlMedian.Size = new System.Drawing.Size(420, 75);
            this.pnlMedian.TabIndex = 2;
            // 
            // lblMaskSizeMedian
            // 
            this.lblMaskSizeMedian.AutoSize = true;
            this.lblMaskSizeMedian.Location = new System.Drawing.Point(4, 33);
            this.lblMaskSizeMedian.Name = "lblMaskSizeMedian";
            this.lblMaskSizeMedian.Size = new System.Drawing.Size(56, 13);
            this.lblMaskSizeMedian.TabIndex = 3;
            this.lblMaskSizeMedian.Text = "Mask Size";
            // 
            // cboMaskSizeMedian
            // 
            this.cboMaskSizeMedian.FormattingEnabled = true;
            this.cboMaskSizeMedian.Items.AddRange(new object[] {
            "3",
            "5",
            "7",
            "9",
            "11"});
            this.cboMaskSizeMedian.Location = new System.Drawing.Point(65, 29);
            this.cboMaskSizeMedian.Name = "cboMaskSizeMedian";
            this.cboMaskSizeMedian.Size = new System.Drawing.Size(73, 21);
            this.cboMaskSizeMedian.TabIndex = 2;
            this.cboMaskSizeMedian.Validating += new System.ComponentModel.CancelEventHandler(this.cboMaskSize_Validating);
            // 
            // rbAdaptiveMedian
            // 
            this.rbAdaptiveMedian.AutoSize = true;
            this.rbAdaptiveMedian.Location = new System.Drawing.Point(80, 6);
            this.rbAdaptiveMedian.Name = "rbAdaptiveMedian";
            this.rbAdaptiveMedian.Size = new System.Drawing.Size(67, 17);
            this.rbAdaptiveMedian.TabIndex = 1;
            this.rbAdaptiveMedian.Text = "Adaptive";
            this.rbAdaptiveMedian.UseVisualStyleBackColor = true;
            // 
            // rbStandardMedian
            // 
            this.rbStandardMedian.AutoSize = true;
            this.rbStandardMedian.Checked = true;
            this.rbStandardMedian.Location = new System.Drawing.Point(6, 6);
            this.rbStandardMedian.Name = "rbStandardMedian";
            this.rbStandardMedian.Size = new System.Drawing.Size(68, 17);
            this.rbStandardMedian.TabIndex = 0;
            this.rbStandardMedian.TabStop = true;
            this.rbStandardMedian.Text = "Standard";
            this.rbStandardMedian.UseVisualStyleBackColor = true;
            // 
            // pnlLaplacian
            // 
            this.pnlLaplacian.Controls.Add(this.lblFilterType);
            this.pnlLaplacian.Controls.Add(this.rbLaplacianType3);
            this.pnlLaplacian.Controls.Add(this.rbLaplacianType2);
            this.pnlLaplacian.Controls.Add(this.rbLaplacianType1);
            this.pnlLaplacian.Location = new System.Drawing.Point(11, 315);
            this.pnlLaplacian.Name = "pnlLaplacian";
            this.pnlLaplacian.Size = new System.Drawing.Size(420, 75);
            this.pnlLaplacian.TabIndex = 3;
            // 
            // lblFilterType
            // 
            this.lblFilterType.AutoSize = true;
            this.lblFilterType.Location = new System.Drawing.Point(3, 9);
            this.lblFilterType.Name = "lblFilterType";
            this.lblFilterType.Size = new System.Drawing.Size(105, 13);
            this.lblFilterType.TabIndex = 3;
            this.lblFilterType.Text = "Specify the filter type";
            // 
            // rbLaplacianType3
            // 
            this.rbLaplacianType3.AutoSize = true;
            this.rbLaplacianType3.Location = new System.Drawing.Point(134, 32);
            this.rbLaplacianType3.Name = "rbLaplacianType3";
            this.rbLaplacianType3.Size = new System.Drawing.Size(58, 17);
            this.rbLaplacianType3.TabIndex = 2;
            this.rbLaplacianType3.Text = "Type 3";
            this.rbLaplacianType3.UseVisualStyleBackColor = true;
            this.rbLaplacianType3.CheckedChanged += new System.EventHandler(this.rbLaplacianType_CheckedChanged);
            // 
            // rbLaplacianType2
            // 
            this.rbLaplacianType2.AutoSize = true;
            this.rbLaplacianType2.Location = new System.Drawing.Point(70, 32);
            this.rbLaplacianType2.Name = "rbLaplacianType2";
            this.rbLaplacianType2.Size = new System.Drawing.Size(58, 17);
            this.rbLaplacianType2.TabIndex = 1;
            this.rbLaplacianType2.Text = "Type 2";
            this.rbLaplacianType2.UseVisualStyleBackColor = true;
            this.rbLaplacianType2.CheckedChanged += new System.EventHandler(this.rbLaplacianType_CheckedChanged);
            // 
            // rbLaplacianType1
            // 
            this.rbLaplacianType1.AutoSize = true;
            this.rbLaplacianType1.Checked = true;
            this.rbLaplacianType1.Location = new System.Drawing.Point(6, 32);
            this.rbLaplacianType1.Name = "rbLaplacianType1";
            this.rbLaplacianType1.Size = new System.Drawing.Size(58, 17);
            this.rbLaplacianType1.TabIndex = 0;
            this.rbLaplacianType1.TabStop = true;
            this.rbLaplacianType1.Text = "Type 1";
            this.rbLaplacianType1.UseVisualStyleBackColor = true;
            this.rbLaplacianType1.CheckedChanged += new System.EventHandler(this.rbLaplacianType_CheckedChanged);
            // 
            // pnlDifference
            // 
            this.pnlDifference.Controls.Add(this.lblDifferenceSize);
            this.pnlDifference.Controls.Add(this.rbDifference11x11);
            this.pnlDifference.Controls.Add(this.rbDifference9x9);
            this.pnlDifference.Controls.Add(this.rbDifference7x7);
            this.pnlDifference.Controls.Add(this.rbDifference5x5);
            this.pnlDifference.Controls.Add(this.rbDifference3x3);
            this.pnlDifference.Location = new System.Drawing.Point(11, 396);
            this.pnlDifference.Name = "pnlDifference";
            this.pnlDifference.Size = new System.Drawing.Size(420, 75);
            this.pnlDifference.TabIndex = 4;
            // 
            // lblDifferenceSize
            // 
            this.lblDifferenceSize.AutoSize = true;
            this.lblDifferenceSize.Location = new System.Drawing.Point(3, 9);
            this.lblDifferenceSize.Name = "lblDifferenceSize";
            this.lblDifferenceSize.Size = new System.Drawing.Size(133, 13);
            this.lblDifferenceSize.TabIndex = 5;
            this.lblDifferenceSize.Text = "Specify the size of the filter";
            // 
            // rbDifference11x11
            // 
            this.rbDifference11x11.AutoSize = true;
            this.rbDifference11x11.Location = new System.Drawing.Point(258, 32);
            this.rbDifference11x11.Name = "rbDifference11x11";
            this.rbDifference11x11.Size = new System.Drawing.Size(54, 17);
            this.rbDifference11x11.TabIndex = 4;
            this.rbDifference11x11.Text = "11x11";
            this.rbDifference11x11.UseVisualStyleBackColor = true;
            this.rbDifference11x11.CheckedChanged += new System.EventHandler(this.rbDifference_CheckedChanged);
            // 
            // rbDifference9x9
            // 
            this.rbDifference9x9.AutoSize = true;
            this.rbDifference9x9.Location = new System.Drawing.Point(195, 32);
            this.rbDifference9x9.Name = "rbDifference9x9";
            this.rbDifference9x9.Size = new System.Drawing.Size(42, 17);
            this.rbDifference9x9.TabIndex = 3;
            this.rbDifference9x9.Text = "9x9";
            this.rbDifference9x9.UseVisualStyleBackColor = true;
            this.rbDifference9x9.CheckedChanged += new System.EventHandler(this.rbDifference_CheckedChanged);
            // 
            // rbDifference7x7
            // 
            this.rbDifference7x7.AutoSize = true;
            this.rbDifference7x7.Location = new System.Drawing.Point(132, 32);
            this.rbDifference7x7.Name = "rbDifference7x7";
            this.rbDifference7x7.Size = new System.Drawing.Size(42, 17);
            this.rbDifference7x7.TabIndex = 2;
            this.rbDifference7x7.Text = "7x7";
            this.rbDifference7x7.UseVisualStyleBackColor = true;
            this.rbDifference7x7.CheckedChanged += new System.EventHandler(this.rbDifference_CheckedChanged);
            // 
            // rbDifference5x5
            // 
            this.rbDifference5x5.AutoSize = true;
            this.rbDifference5x5.Location = new System.Drawing.Point(69, 32);
            this.rbDifference5x5.Name = "rbDifference5x5";
            this.rbDifference5x5.Size = new System.Drawing.Size(42, 17);
            this.rbDifference5x5.TabIndex = 1;
            this.rbDifference5x5.Text = "5x5";
            this.rbDifference5x5.UseVisualStyleBackColor = true;
            this.rbDifference5x5.CheckedChanged += new System.EventHandler(this.rbDifference_CheckedChanged);
            // 
            // rbDifference3x3
            // 
            this.rbDifference3x3.AutoSize = true;
            this.rbDifference3x3.Checked = true;
            this.rbDifference3x3.Location = new System.Drawing.Point(6, 32);
            this.rbDifference3x3.Name = "rbDifference3x3";
            this.rbDifference3x3.Size = new System.Drawing.Size(42, 17);
            this.rbDifference3x3.TabIndex = 0;
            this.rbDifference3x3.TabStop = true;
            this.rbDifference3x3.Text = "3x3";
            this.rbDifference3x3.UseVisualStyleBackColor = true;
            this.rbDifference3x3.CheckedChanged += new System.EventHandler(this.rbDifference_CheckedChanged);
            // 
            // pnlSpecifyFilter
            // 
            this.pnlSpecifyFilter.Controls.Add(this.lblSpecifyFilterSize);
            this.pnlSpecifyFilter.Controls.Add(this.rbSpecifyFilter11x11);
            this.pnlSpecifyFilter.Controls.Add(this.rbSpecifyFilter9x9);
            this.pnlSpecifyFilter.Controls.Add(this.rbSpecifyFilter7x7);
            this.pnlSpecifyFilter.Controls.Add(this.rbSpecifyFilter5x5);
            this.pnlSpecifyFilter.Controls.Add(this.rbSpecifyFilter3x3);
            this.pnlSpecifyFilter.Controls.Add(this.chkNormalized);
            this.pnlSpecifyFilter.Controls.Add(this.lblSpecifyFilter);
            this.pnlSpecifyFilter.Controls.Add(this.cboSpecifyFilter);
            this.pnlSpecifyFilter.Location = new System.Drawing.Point(11, 477);
            this.pnlSpecifyFilter.Name = "pnlSpecifyFilter";
            this.pnlSpecifyFilter.Size = new System.Drawing.Size(420, 75);
            this.pnlSpecifyFilter.TabIndex = 5;
            // 
            // lblSpecifyFilterSize
            // 
            this.lblSpecifyFilterSize.AutoSize = true;
            this.lblSpecifyFilterSize.Location = new System.Drawing.Point(4, 43);
            this.lblSpecifyFilterSize.Name = "lblSpecifyFilterSize";
            this.lblSpecifyFilterSize.Size = new System.Drawing.Size(97, 13);
            this.lblSpecifyFilterSize.TabIndex = 8;
            this.lblSpecifyFilterSize.Text = "Spatial filter of size:";
            // 
            // rbSpecifyFilter11x11
            // 
            this.rbSpecifyFilter11x11.AutoSize = true;
            this.rbSpecifyFilter11x11.Location = new System.Drawing.Point(330, 41);
            this.rbSpecifyFilter11x11.Name = "rbSpecifyFilter11x11";
            this.rbSpecifyFilter11x11.Size = new System.Drawing.Size(54, 17);
            this.rbSpecifyFilter11x11.TabIndex = 7;
            this.rbSpecifyFilter11x11.Text = "11x11";
            this.rbSpecifyFilter11x11.UseVisualStyleBackColor = true;
            this.rbSpecifyFilter11x11.CheckedChanged += new System.EventHandler(this.rbcboSpecifyFilter_ParameterChanged);
            // 
            // rbSpecifyFilter9x9
            // 
            this.rbSpecifyFilter9x9.AutoSize = true;
            this.rbSpecifyFilter9x9.Location = new System.Drawing.Point(276, 41);
            this.rbSpecifyFilter9x9.Name = "rbSpecifyFilter9x9";
            this.rbSpecifyFilter9x9.Size = new System.Drawing.Size(42, 17);
            this.rbSpecifyFilter9x9.TabIndex = 6;
            this.rbSpecifyFilter9x9.Text = "9x9";
            this.rbSpecifyFilter9x9.UseVisualStyleBackColor = true;
            this.rbSpecifyFilter9x9.CheckedChanged += new System.EventHandler(this.rbcboSpecifyFilter_ParameterChanged);
            // 
            // rbSpecifyFilter7x7
            // 
            this.rbSpecifyFilter7x7.AutoSize = true;
            this.rbSpecifyFilter7x7.Location = new System.Drawing.Point(222, 41);
            this.rbSpecifyFilter7x7.Name = "rbSpecifyFilter7x7";
            this.rbSpecifyFilter7x7.Size = new System.Drawing.Size(42, 17);
            this.rbSpecifyFilter7x7.TabIndex = 5;
            this.rbSpecifyFilter7x7.Text = "7x7";
            this.rbSpecifyFilter7x7.UseVisualStyleBackColor = true;
            this.rbSpecifyFilter7x7.CheckedChanged += new System.EventHandler(this.rbcboSpecifyFilter_ParameterChanged);
            // 
            // rbSpecifyFilter5x5
            // 
            this.rbSpecifyFilter5x5.AutoSize = true;
            this.rbSpecifyFilter5x5.Location = new System.Drawing.Point(168, 41);
            this.rbSpecifyFilter5x5.Name = "rbSpecifyFilter5x5";
            this.rbSpecifyFilter5x5.Size = new System.Drawing.Size(42, 17);
            this.rbSpecifyFilter5x5.TabIndex = 4;
            this.rbSpecifyFilter5x5.Text = "5x5";
            this.rbSpecifyFilter5x5.UseVisualStyleBackColor = true;
            this.rbSpecifyFilter5x5.CheckedChanged += new System.EventHandler(this.rbcboSpecifyFilter_ParameterChanged);
            // 
            // rbSpecifyFilter3x3
            // 
            this.rbSpecifyFilter3x3.AutoSize = true;
            this.rbSpecifyFilter3x3.Checked = true;
            this.rbSpecifyFilter3x3.Location = new System.Drawing.Point(114, 41);
            this.rbSpecifyFilter3x3.Name = "rbSpecifyFilter3x3";
            this.rbSpecifyFilter3x3.Size = new System.Drawing.Size(42, 17);
            this.rbSpecifyFilter3x3.TabIndex = 3;
            this.rbSpecifyFilter3x3.TabStop = true;
            this.rbSpecifyFilter3x3.Text = "3x3";
            this.rbSpecifyFilter3x3.UseVisualStyleBackColor = true;
            this.rbSpecifyFilter3x3.CheckedChanged += new System.EventHandler(this.rbcboSpecifyFilter_ParameterChanged);
            // 
            // chkNormalized
            // 
            this.chkNormalized.AutoSize = true;
            this.chkNormalized.Checked = true;
            this.chkNormalized.CheckState = System.Windows.Forms.CheckState.Checked;
            this.chkNormalized.Location = new System.Drawing.Point(228, 8);
            this.chkNormalized.Name = "chkNormalized";
            this.chkNormalized.Size = new System.Drawing.Size(72, 17);
            this.chkNormalized.TabIndex = 2;
            this.chkNormalized.Text = "Normalize";
            this.chkNormalized.UseVisualStyleBackColor = true;
            // 
            // lblSpecifyFilter
            // 
            this.lblSpecifyFilter.AutoSize = true;
            this.lblSpecifyFilter.Location = new System.Drawing.Point(4, 10);
            this.lblSpecifyFilter.Name = "lblSpecifyFilter";
            this.lblSpecifyFilter.Size = new System.Drawing.Size(51, 13);
            this.lblSpecifyFilter.TabIndex = 1;
            this.lblSpecifyFilter.Text = "Specify a";
            // 
            // cboSpecifyFilter
            // 
            this.cboSpecifyFilter.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cboSpecifyFilter.FormattingEnabled = true;
            this.cboSpecifyFilter.Items.AddRange(new object[] {
            "Low pass",
            "High pass",
            "Center weighted constant",
            "Gaussian"});
            this.cboSpecifyFilter.Location = new System.Drawing.Point(59, 6);
            this.cboSpecifyFilter.Name = "cboSpecifyFilter";
            this.cboSpecifyFilter.SelectedIndex = 0;
            this.cboSpecifyFilter.Size = new System.Drawing.Size(150, 21);
            this.cboSpecifyFilter.TabIndex = 0;
            this.cboSpecifyFilter.SelectedIndexChanged += new System.EventHandler(this.rbcboSpecifyFilter_ParameterChanged);
            // 
            // pnlSpecifyBlur
            // 
            this.pnlSpecifyBlur.Controls.Add(this.lblBlurWeight);
            this.pnlSpecifyBlur.Controls.Add(this.cboBlurWeight);
            this.pnlSpecifyBlur.Controls.Add(this.lblBlurMethod);
            this.pnlSpecifyBlur.Controls.Add(this.cboBlurMethod);
            //this.pnlSpecifyBlur.Controls.Add(this.lblShapeHeight);
            //this.pnlSpecifyBlur.Controls.Add(this.cboShapeHeight);
            //this.pnlSpecifyBlur.Controls.Add(this.lblShapeWidth);
            //this.pnlSpecifyBlur.Controls.Add(this.cboShapeWidth);
            this.pnlSpecifyBlur.Controls.Add(this.lblBlurShape);
            this.pnlSpecifyBlur.Controls.Add(this.cboBlurShape);
            this.pnlSpecifyBlur.Controls.Add(this.lblMaskHeight);
            this.pnlSpecifyBlur.Controls.Add(this.cboMaskHeight);
            this.pnlSpecifyBlur.Controls.Add(this.lblMaskWidth);
            this.pnlSpecifyBlur.Controls.Add(this.cboMaskWidth);
            this.pnlSpecifyBlur.Location = new System.Drawing.Point(11, 558);
            this.pnlSpecifyBlur.Name = "pnlSpecifyBlur";
            this.pnlSpecifyBlur.Size = new System.Drawing.Size(420, 86);
            this.pnlSpecifyBlur.TabIndex = 6;
            // 
            // lblBlurWeight
            // 
            this.lblBlurWeight.AutoSize = true;
            this.lblBlurWeight.Location = new System.Drawing.Point(249, 62);
            this.lblBlurWeight.Name = "lblBlurWeight";
            this.lblBlurWeight.Size = new System.Drawing.Size(44, 13);
            this.lblBlurWeight.TabIndex = 13;
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
            this.cboBlurWeight.Location = new System.Drawing.Point(294, 58);
            this.cboBlurWeight.Name = "cboBlurWeight";
            this.cboBlurWeight.Size = new System.Drawing.Size(50, 21);
            this.cboBlurWeight.TabIndex = 12;
            this.cboBlurWeight.Text = "1.0";
            this.cboBlurWeight.Validating += new System.ComponentModel.CancelEventHandler(this.cboFloatVal_Validating);
            this.cboBlurWeight.SelectedIndexChanged += new System.EventHandler(this.cboBlurParameter_Changed);
            this.cboBlurWeight.Validated += new System.EventHandler(this.cboBlurParameter_Changed);
            // 
            // lblBlurMethod
            // 
            this.lblBlurMethod.AutoSize = true;
            this.lblBlurMethod.Location = new System.Drawing.Point(9, 62);
            this.lblBlurMethod.Name = "lblBlurMethod";
            this.lblBlurMethod.Size = new System.Drawing.Size(67, 13);
            this.lblBlurMethod.TabIndex = 11;
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
            this.cboBlurMethod.Location = new System.Drawing.Point(77, 58);
            this.cboBlurMethod.Name = "cboBlurMethod";
            this.cboBlurMethod.SelectedIndex = 1;
            this.cboBlurMethod.Size = new System.Drawing.Size(157, 21);
            this.cboBlurMethod.TabIndex = 10;
            this.cboBlurMethod.SelectedIndexChanged += new System.EventHandler(this.cboBlurParameter_Changed);
            // 
            // lblShapeHeight
            // 
            //this.lblShapeHeight.AutoSize = true;
            //this.lblShapeHeight.Location = new System.Drawing.Point(289, 36);
            //this.lblShapeHeight.Name = "lblShapeHeight";
            //this.lblShapeHeight.Size = new System.Drawing.Size(41, 13);
            //this.lblShapeHeight.TabIndex = 9;
            //this.lblShapeHeight.Text = "Height:";
            //this.lblShapeHeight.TextAlign = System.Drawing.ContentAlignment.TopRight;
            // 
            // cboShapeHeight
            // 
            //this.cboShapeHeight.FormattingEnabled = true;
            //this.cboShapeHeight.Items.AddRange(new object[] {
            //"3",
            //"5",
            //"7",
            //"9",
            //"11"});
            //this.cboShapeHeight.Location = new System.Drawing.Point(330, 32);
            //this.cboShapeHeight.Name = "cboShapeHeight";
            //this.cboShapeHeight.Size = new System.Drawing.Size(50, 21);
            //this.cboShapeHeight.TabIndex = 8;
            //this.cboShapeHeight.Text = "7";
            //this.cboShapeHeight.Validating += new System.ComponentModel.CancelEventHandler(this.cboIntVal_Validating);
            //this.cboShapeHeight.SelectedIndexChanged += new System.EventHandler(this.cboShapeSize_Validated);
            //this.cboShapeHeight.Validated += new System.EventHandler(this.cboShapeSize_Validated);
            // 
            // lblShapeWidth
            // 
            //this.lblShapeWidth.AutoSize = true;
            //this.lblShapeWidth.Location = new System.Drawing.Point(180, 36);
            //this.lblShapeWidth.Name = "lblShapeWidth";
            //this.lblShapeWidth.Size = new System.Drawing.Size(38, 13);
            //this.lblShapeWidth.TabIndex = 7;
            //this.lblShapeWidth.Text = "Width:";
            //this.lblShapeWidth.TextAlign = System.Drawing.ContentAlignment.TopRight;
            // 
            // cboShapeWidth
            // 
            //this.cboShapeWidth.FormattingEnabled = true;
            //this.cboShapeWidth.Items.AddRange(new object[] {
            //"3",
            //"5",
            //"7",
            //"9",
            //"11"});
            //this.cboShapeWidth.Location = new System.Drawing.Point(233, 32);
            //this.cboShapeWidth.Name = "cboShapeWidth";
            //this.cboShapeWidth.Size = new System.Drawing.Size(50, 21);
            //this.cboShapeWidth.TabIndex = 6;
            //this.cboShapeWidth.Text = "7";
            //this.cboShapeWidth.Validating += new System.ComponentModel.CancelEventHandler(this.cboIntVal_Validating);
            //this.cboShapeWidth.SelectedIndexChanged += new System.EventHandler(this.cboShapeSize_Validated);
            //this.cboShapeWidth.Validated += new System.EventHandler(this.cboShapeSize_Validated);
            // 
            // lblBlurShape
            // 
            this.lblBlurShape.AutoSize = true;
            this.lblBlurShape.Location = new System.Drawing.Point(14, 36);
            this.lblBlurShape.Name = "lblBlurShape";
            this.lblBlurShape.Size = new System.Drawing.Size(62, 13);
            this.lblBlurShape.TabIndex = 5;
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
            this.cboBlurShape.Location = new System.Drawing.Point(77, 32);
            this.cboBlurShape.Name = "cboBlurShape";
            this.cboBlurShape.SelectedIndex = 1;
            this.cboBlurShape.Size = new System.Drawing.Size(97, 21);
            this.cboBlurShape.TabIndex = 4;
            this.cboBlurShape.SelectedIndexChanged += new System.EventHandler(this.cboBlurShape_SelectedIndexChanged);
            // 
            // lblMaskHeight
            // 
            this.lblMaskHeight.AutoSize = true;
            this.lblMaskHeight.Location = new System.Drawing.Point(148, 10);
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
            this.cboMaskHeight.Location = new System.Drawing.Point(219, 6);
            this.cboMaskHeight.Name = "cboMaskHeight";
            this.cboMaskHeight.Size = new System.Drawing.Size(50, 21);
            this.cboMaskHeight.TabIndex = 2;
            this.cboMaskHeight.Text = "9";
            this.cboMaskHeight.Validating += new System.ComponentModel.CancelEventHandler(this.cboMaskSize_Validating);
            this.cboMaskHeight.SelectedIndexChanged += new System.EventHandler(this.cboMaskSize_Validated);
            this.cboMaskHeight.Validated += new System.EventHandler(this.cboMaskSize_Validated);
            // 
            // lblMaskWidth
            // 
            this.lblMaskWidth.AutoSize = true;
            this.lblMaskWidth.Location = new System.Drawing.Point(9, 10);
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
            this.cboMaskWidth.Location = new System.Drawing.Point(77, 6);
            this.cboMaskWidth.Name = "cboMaskWidth";
            this.cboMaskWidth.Size = new System.Drawing.Size(50, 21);
            this.cboMaskWidth.TabIndex = 0;
            this.cboMaskWidth.Text = "9";
            this.cboMaskWidth.Validating += new System.ComponentModel.CancelEventHandler(this.cboMaskSize_Validating);
            this.cboMaskWidth.SelectedIndexChanged += new System.EventHandler(this.cboMaskSize_Validated);
            this.cboMaskWidth.Validated += new System.EventHandler(this.cboMaskSize_Validated);
            // 
            // btnEditMask
            // 
            this.btnEditMask.Location = new System.Drawing.Point(348, 10);
            this.btnEditMask.Name = "btnEditMask";
            this.btnEditMask.Size = new System.Drawing.Size(75, 24);
            this.btnEditMask.TabIndex = 7;
            this.btnEditMask.Text = "Edit Mask";
            this.btnEditMask.UseVisualStyleBackColor = true;
            this.btnEditMask.Click += new System.EventHandler(this.btnEditMask_Click);
            // 
            // btnHelp
            // 
            this.btnHelp.BackColor = System.Drawing.Color.Yellow;
            this.btnHelp.Location = new System.Drawing.Point(2, 109);
            this.btnHelp.Name = "btnHelp";
            this.btnHelp.Size = new System.Drawing.Size(60, 26);
            this.btnHelp.TabIndex = 8;
            this.btnHelp.Text = "Help";
            this.btnHelp.UseVisualStyleBackColor = false;
            this.btnHelp.Click += new System.EventHandler(this.btnHelp_Click);
            // 
            // btnCancel
            // 
            this.btnCancel.BackColor = System.Drawing.Color.OrangeRed;
            this.btnCancel.CausesValidation = false;
            this.btnCancel.Location = new System.Drawing.Point(238, 109);
            this.btnCancel.Name = "btnCancel";
            this.btnCancel.Size = new System.Drawing.Size(60, 26);
            this.btnCancel.TabIndex = 9;
            this.btnCancel.Text = "Cancel";
            this.btnCancel.UseVisualStyleBackColor = false;
            this.btnCancel.Click += new System.EventHandler(this.btnCancel_Click);
            // 
            // btnReset
            // 
            this.btnReset.BackColor = System.Drawing.Color.CornflowerBlue;
            this.btnReset.CausesValidation = false;
            this.btnReset.Location = new System.Drawing.Point(304, 109);
            this.btnReset.Name = "btnReset";
            this.btnReset.Size = new System.Drawing.Size(60, 26);
            this.btnReset.TabIndex = 10;
            this.btnReset.Text = "Reset";
            this.btnReset.UseVisualStyleBackColor = false;
            this.btnReset.Click += new System.EventHandler(this.btnReset_Click);
            // 
            // btnApply
            // 
            this.btnApply.BackColor = System.Drawing.Color.LimeGreen;
            this.btnApply.ForeColor = System.Drawing.Color.White;
            this.btnApply.Location = new System.Drawing.Point(370, 109);
            this.btnApply.Name = "btnApply";
            this.btnApply.Size = new System.Drawing.Size(60, 26);
            this.btnApply.TabIndex = 11;
            this.btnApply.Text = "Apply";
            this.btnApply.UseVisualStyleBackColor = false;
            this.btnApply.Click += new System.EventHandler(this.btnApply_Click);
            // 
            // UtilFilter
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.CausesValidation = false;
            this.Controls.Add(this.btnApply);
            this.Controls.Add(this.btnReset);
            this.Controls.Add(this.btnCancel);
            this.Controls.Add(this.btnHelp);
            this.Controls.Add(this.btnEditMask);
            this.Controls.Add(this.pnlSpecifyBlur);
            this.Controls.Add(this.pnlSpecifyFilter);
            this.Controls.Add(this.pnlDifference);
            this.Controls.Add(this.pnlLaplacian);
            this.Controls.Add(this.pnlMedian);
            this.Controls.Add(this.pnlMean);
            this.Controls.Add(this.grpFilter);
            this.Name = "UtilFilter";
            this.Size = new System.Drawing.Size(456, 677);
            this.grpFilter.ResumeLayout(false);
            this.grpFilter.PerformLayout();
            this.pnlMean.ResumeLayout(false);
            this.pnlMean.PerformLayout();
            this.pnlMedian.ResumeLayout(false);
            this.pnlMedian.PerformLayout();
            this.pnlLaplacian.ResumeLayout(false);
            this.pnlLaplacian.PerformLayout();
            this.pnlDifference.ResumeLayout(false);
            this.pnlDifference.PerformLayout();
            this.pnlSpecifyFilter.ResumeLayout(false);
            this.pnlSpecifyFilter.PerformLayout();
            this.pnlSpecifyBlur.ResumeLayout(false);
            this.pnlSpecifyBlur.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox grpFilter;
        private System.Windows.Forms.Label lblCurrentImage;
        private System.Windows.Forms.Label txtCurrentImage;
        private System.Windows.Forms.Panel pnlMean;
        private System.Windows.Forms.Label lblMaskSizeMean;
        private System.Windows.Forms.ComboBox cboMaskSizeMean;
        private System.Windows.Forms.Panel pnlMedian;
        private System.Windows.Forms.Label lblMaskSizeMedian;
        private System.Windows.Forms.ComboBox cboMaskSizeMedian;
        private System.Windows.Forms.RadioButton rbAdaptiveMedian;
        private System.Windows.Forms.RadioButton rbStandardMedian;
        private System.Windows.Forms.Panel pnlLaplacian;
        private System.Windows.Forms.Label lblFilterType;
        private System.Windows.Forms.RadioButton rbLaplacianType3;
        private System.Windows.Forms.RadioButton rbLaplacianType2;
        private System.Windows.Forms.RadioButton rbLaplacianType1;
        private System.Windows.Forms.Panel pnlDifference;
        private System.Windows.Forms.Label lblDifferenceSize;
        private System.Windows.Forms.RadioButton rbDifference11x11;
        private System.Windows.Forms.RadioButton rbDifference9x9;
        private System.Windows.Forms.RadioButton rbDifference7x7;
        private System.Windows.Forms.RadioButton rbDifference5x5;
        private System.Windows.Forms.RadioButton rbDifference3x3;
        private System.Windows.Forms.Panel pnlSpecifyFilter;
        private System.Windows.Forms.Label lblSpecifyFilterSize;
        private System.Windows.Forms.RadioButton rbSpecifyFilter11x11;
        private System.Windows.Forms.RadioButton rbSpecifyFilter9x9;
        private System.Windows.Forms.RadioButton rbSpecifyFilter7x7;
        private System.Windows.Forms.RadioButton rbSpecifyFilter5x5;
        private System.Windows.Forms.RadioButton rbSpecifyFilter3x3;
        private System.Windows.Forms.CheckBox chkNormalized;
        private System.Windows.Forms.Label lblSpecifyFilter;
        private System.Windows.Forms.ComboBox cboSpecifyFilter;
        private System.Windows.Forms.Panel pnlSpecifyBlur;
        private System.Windows.Forms.Label lblBlurWeight;
        private System.Windows.Forms.ComboBox cboBlurWeight;
        private System.Windows.Forms.Label lblBlurMethod;
        private System.Windows.Forms.ComboBox cboBlurMethod;
        //private System.Windows.Forms.Label lblShapeHeight;
        //private System.Windows.Forms.ComboBox cboShapeHeight;
        //private System.Windows.Forms.Label lblShapeWidth;
        //private System.Windows.Forms.ComboBox cboShapeWidth;
        private System.Windows.Forms.Label lblBlurShape;
        private System.Windows.Forms.ComboBox cboBlurShape;
        private System.Windows.Forms.Label lblMaskHeight;
        private System.Windows.Forms.ComboBox cboMaskHeight;
        private System.Windows.Forms.Label lblMaskWidth;
        private System.Windows.Forms.ComboBox cboMaskWidth;
        private System.Windows.Forms.Button btnEditMask;
        private System.Windows.Forms.Button btnHelp;
        private System.Windows.Forms.Button btnCancel;
        private System.Windows.Forms.Button btnReset;
        private System.Windows.Forms.Button btnApply;
    }
}
