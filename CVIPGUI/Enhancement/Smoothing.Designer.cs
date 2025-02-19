namespace CVIPGUI.Enhancement
{
    partial class Smoothing
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
            this.rbMean = new System.Windows.Forms.RadioButton();
            this.rbGaussian = new System.Windows.Forms.RadioButton();
            this.rbMidpoint = new System.Windows.Forms.RadioButton();
            this.rbContraHarmonic = new System.Windows.Forms.RadioButton();
            this.rbYpMean = new System.Windows.Forms.RadioButton();
            this.rbMedian = new System.Windows.Forms.RadioButton();
            this.rbKuwahara = new System.Windows.Forms.RadioButton();
            this.rbADFilter = new System.Windows.Forms.RadioButton();
            this.rbFFTSmoothing = new System.Windows.Forms.RadioButton();
            this.rbDCTSmoothing = new System.Windows.Forms.RadioButton();
            this.grpSpatialSmoothing = new System.Windows.Forms.GroupBox();
            this.grpFreqSmoothing = new System.Windows.Forms.GroupBox();
            this.grpParameters = new System.Windows.Forms.GroupBox();
            this.lblCutoff = new System.Windows.Forms.Label();
            this.cboCutoff = new System.Windows.Forms.ComboBox();
            this.pnlMask = new System.Windows.Forms.Panel();
            this.lblOrder = new System.Windows.Forms.Label();
            this.cboOrder = new System.Windows.Forms.ComboBox();
            this.lblMaskSize = new System.Windows.Forms.Label();
            this.cboMaskSize = new System.Windows.Forms.ComboBox();
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
            this.rbAdaptive = new System.Windows.Forms.RadioButton();
            this.rbStandard = new System.Windows.Forms.RadioButton();
            this.btnHelp = new System.Windows.Forms.Button();
            this.btnCancel = new System.Windows.Forms.Button();
            this.btnReset = new System.Windows.Forms.Button();
            this.btnApply = new System.Windows.Forms.Button();
            this.grpParameters.SuspendLayout();
            this.pnlMask.SuspendLayout();
            this.pnlAnisotropic.SuspendLayout();
            this.SuspendLayout();
            // 
            // rbMean
            // 
            this.rbMean.AutoSize = true;
            this.rbMean.Checked = true;
            this.rbMean.Location = new System.Drawing.Point(15, 17);
            this.rbMean.Name = "rbMean";
            this.rbMean.Size = new System.Drawing.Size(77, 17);
            this.rbMean.TabIndex = 0;
            this.rbMean.TabStop = true;
            this.rbMean.Text = "Mean Filter";
            this.rbMean.UseVisualStyleBackColor = true;
            this.rbMean.Click += new System.EventHandler(this.rbSmoothing_Click);
            // 
            // rbGaussian
            // 
            this.rbGaussian.AutoSize = true;
            this.rbGaussian.Location = new System.Drawing.Point(15, 38);
            this.rbGaussian.Name = "rbGaussian";
            this.rbGaussian.Size = new System.Drawing.Size(94, 17);
            this.rbGaussian.TabIndex = 1;
            this.rbGaussian.Text = "Gaussian Filter";
            this.rbGaussian.UseVisualStyleBackColor = true;
            this.rbGaussian.Click += new System.EventHandler(this.rbSmoothing_Click);
            // 
            // rbMidpoint
            // 
            this.rbMidpoint.AutoSize = true;
            this.rbMidpoint.Location = new System.Drawing.Point(15, 59);
            this.rbMidpoint.Name = "rbMidpoint";
            this.rbMidpoint.Size = new System.Drawing.Size(90, 17);
            this.rbMidpoint.TabIndex = 2;
            this.rbMidpoint.Text = "Midpoint Filter";
            this.rbMidpoint.UseVisualStyleBackColor = true;
            this.rbMidpoint.Click += new System.EventHandler(this.rbSmoothing_Click);
            // 
            // rbContraHarmonic
            // 
            this.rbContraHarmonic.AutoSize = true;
            this.rbContraHarmonic.Location = new System.Drawing.Point(15, 80);
            this.rbContraHarmonic.Name = "rbContraHarmonic";
            this.rbContraHarmonic.Size = new System.Drawing.Size(127, 17);
            this.rbContraHarmonic.TabIndex = 3;
            this.rbContraHarmonic.Text = "Contra-harmonic Filter";
            this.rbContraHarmonic.UseVisualStyleBackColor = true;
            this.rbContraHarmonic.Click += new System.EventHandler(this.rbSmoothing_Click);
            // 
            // rbYpMean
            // 
            this.rbYpMean.AutoSize = true;
            this.rbYpMean.Location = new System.Drawing.Point(15, 101);
            this.rbYpMean.Name = "rbYpMean";
            this.rbYpMean.Size = new System.Drawing.Size(93, 17);
            this.rbYpMean.TabIndex = 4;
            this.rbYpMean.Text = "Yp Mean Filter";
            this.rbYpMean.UseVisualStyleBackColor = true;
            this.rbYpMean.Click += new System.EventHandler(this.rbSmoothing_Click);
            // 
            // rbMedian
            // 
            this.rbMedian.AutoSize = true;
            this.rbMedian.Location = new System.Drawing.Point(15, 122);
            this.rbMedian.Name = "rbMedian";
            this.rbMedian.Size = new System.Drawing.Size(85, 17);
            this.rbMedian.TabIndex = 5;
            this.rbMedian.Text = "Median Filter";
            this.rbMedian.UseVisualStyleBackColor = true;
            this.rbMedian.Click += new System.EventHandler(this.rbSmoothing_Click);
            // 
            // rbKuwahara
            // 
            this.rbKuwahara.AutoSize = true;
            this.rbKuwahara.Location = new System.Drawing.Point(15, 143);
            this.rbKuwahara.Name = "rbKuwahara";
            this.rbKuwahara.Size = new System.Drawing.Size(98, 17);
            this.rbKuwahara.TabIndex = 6;
            this.rbKuwahara.Text = "Kuwahara Filter";
            this.rbKuwahara.UseVisualStyleBackColor = true;
            this.rbKuwahara.Click += new System.EventHandler(this.rbSmoothing_Click);
            // 
            // rbADFilter
            // 
            this.rbADFilter.AutoSize = true;
            this.rbADFilter.Location = new System.Drawing.Point(15, 164);
            this.rbADFilter.Name = "rbADFilter";
            this.rbADFilter.Size = new System.Drawing.Size(146, 17);
            this.rbADFilter.TabIndex = 7;
            this.rbADFilter.Text = "Anisotropic Diffusion Filter";
            this.rbADFilter.UseVisualStyleBackColor = true;
            this.rbADFilter.Click += new System.EventHandler(this.rbSmoothing_Click);
            // 
            // rbFFTSmoothing
            // 
            this.rbFFTSmoothing.AutoSize = true;
            this.rbFFTSmoothing.Location = new System.Drawing.Point(15, 211);
            this.rbFFTSmoothing.Name = "rbFFTSmoothing";
            this.rbFFTSmoothing.Size = new System.Drawing.Size(97, 17);
            this.rbFFTSmoothing.TabIndex = 8;
            this.rbFFTSmoothing.Text = "FFT Smoothing";
            this.rbFFTSmoothing.UseVisualStyleBackColor = true;
            this.rbFFTSmoothing.Click += new System.EventHandler(this.rbSmoothing_Click);
            // 
            // rbDCTSmoothing
            // 
            this.rbDCTSmoothing.AutoSize = true;
            this.rbDCTSmoothing.Location = new System.Drawing.Point(15, 232);
            this.rbDCTSmoothing.Name = "rbDCTSmoothing";
            this.rbDCTSmoothing.Size = new System.Drawing.Size(100, 17);
            this.rbDCTSmoothing.TabIndex = 9;
            this.rbDCTSmoothing.Text = "DCT Smoothing";
            this.rbDCTSmoothing.UseVisualStyleBackColor = true;
            this.rbDCTSmoothing.Click += new System.EventHandler(this.rbSmoothing_Click);
            // 
            // grpSpatialSmoothing
            // 
            this.grpSpatialSmoothing.Location = new System.Drawing.Point(6, 1);
            this.grpSpatialSmoothing.Name = "grpSpatialSmoothing";
            this.grpSpatialSmoothing.Size = new System.Drawing.Size(166, 188);
            this.grpSpatialSmoothing.TabIndex = 10;
            this.grpSpatialSmoothing.TabStop = false;
            this.grpSpatialSmoothing.Text = "Spatial Domain Smoothing";
            // 
            // grpFreqSmoothing
            // 
            this.grpFreqSmoothing.Location = new System.Drawing.Point(6, 195);
            this.grpFreqSmoothing.Name = "grpFreqSmoothing";
            this.grpFreqSmoothing.Size = new System.Drawing.Size(166, 60);
            this.grpFreqSmoothing.TabIndex = 11;
            this.grpFreqSmoothing.TabStop = false;
            this.grpFreqSmoothing.Text = "Frequency Domain Smoothing";
            // 
            // grpParameters
            // 
            this.grpParameters.Controls.Add(this.lblCutoff);
            this.grpParameters.Controls.Add(this.cboCutoff);
            this.grpParameters.Controls.Add(this.pnlMask);
            this.grpParameters.Controls.Add(this.pnlAnisotropic);
            this.grpParameters.Controls.Add(this.lblType);
            this.grpParameters.Controls.Add(this.rbAdaptive);
            this.grpParameters.Controls.Add(this.rbStandard);
            this.grpParameters.Location = new System.Drawing.Point(175, 1);
            this.grpParameters.Name = "grpParameters";
            this.grpParameters.Size = new System.Drawing.Size(392, 254);
            this.grpParameters.TabIndex = 12;
            this.grpParameters.TabStop = false;
            this.grpParameters.Text = "Parameters";
            // 
            // lblCutoff
            // 
            this.lblCutoff.AutoSize = true;
            this.lblCutoff.Location = new System.Drawing.Point(40, 211);
            this.lblCutoff.Name = "lblCutoff";
            this.lblCutoff.Size = new System.Drawing.Size(91, 13);
            this.lblCutoff.TabIndex = 6;
            this.lblCutoff.Text = "Cutoff Frequency:";
            // 
            // cboCutoff
            // 
            this.cboCutoff.FormattingEnabled = true;
            this.cboCutoff.Items.AddRange(new object[] {
            "16",
            "24",
            "32",
            "40",
            "48",
            "56",
            "64"});
            this.cboCutoff.Location = new System.Drawing.Point(134, 207);
            this.cboCutoff.Name = "cboCutoff";
            this.cboCutoff.Size = new System.Drawing.Size(121, 21);
            this.cboCutoff.TabIndex = 5;
            this.cboCutoff.Text = "32";
            this.cboCutoff.Validating += new System.ComponentModel.CancelEventHandler(this.cboUIntVal_Validating);
            // 
            // pnlMask
            // 
            this.pnlMask.Controls.Add(this.lblOrder);
            this.pnlMask.Controls.Add(this.cboOrder);
            this.pnlMask.Controls.Add(this.lblMaskSize);
            this.pnlMask.Controls.Add(this.cboMaskSize);
            this.pnlMask.Location = new System.Drawing.Point(198, 47);
            this.pnlMask.Name = "pnlMask";
            this.pnlMask.Size = new System.Drawing.Size(183, 49);
            this.pnlMask.TabIndex = 4;
            // 
            // lblOrder
            // 
            this.lblOrder.AutoSize = true;
            this.lblOrder.Location = new System.Drawing.Point(23, 32);
            this.lblOrder.Name = "lblOrder";
            this.lblOrder.Size = new System.Drawing.Size(36, 13);
            this.lblOrder.TabIndex = 3;
            this.lblOrder.Text = "Order:";
            // 
            // cboOrder
            // 
            this.cboOrder.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cboOrder.FormattingEnabled = true;
            this.cboOrder.Items.AddRange(new object[] {
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
            this.cboOrder.Location = new System.Drawing.Point(62, 28);
            this.cboOrder.Name = "cboOrder";
            this.cboOrder.Size = new System.Drawing.Size(121, 21);
            this.cboOrder.TabIndex = 2;
            // 
            // lblMaskSize
            // 
            this.lblMaskSize.AutoSize = true;
            this.lblMaskSize.Location = new System.Drawing.Point(3, 3);
            this.lblMaskSize.Name = "lblMaskSize";
            this.lblMaskSize.Size = new System.Drawing.Size(59, 13);
            this.lblMaskSize.TabIndex = 1;
            this.lblMaskSize.Text = "Mask Size:";
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
            this.cboMaskSize.Location = new System.Drawing.Point(62, 0);
            this.cboMaskSize.Name = "cboMaskSize";
            this.cboMaskSize.Size = new System.Drawing.Size(121, 21);
            this.cboMaskSize.TabIndex = 0;
            this.cboMaskSize.Text = "3";
            this.cboMaskSize.Validating += new System.ComponentModel.CancelEventHandler(this.cboUIntVal_Validating);
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
            this.pnlAnisotropic.Location = new System.Drawing.Point(59, 100);
            this.pnlAnisotropic.Name = "pnlAnisotropic";
            this.pnlAnisotropic.Size = new System.Drawing.Size(243, 105);
            this.pnlAnisotropic.TabIndex = 3;
            // 
            // lblBlockSize
            // 
            this.lblBlockSize.AutoSize = true;
            this.lblBlockSize.Location = new System.Drawing.Point(59, 88);
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
            this.cboBlockSize.Location = new System.Drawing.Point(122, 84);
            this.cboBlockSize.Name = "cboBlockSize";
            this.cboBlockSize.Size = new System.Drawing.Size(121, 21);
            this.cboBlockSize.TabIndex = 6;
            this.cboBlockSize.Text = "64";
            this.cboBlockSize.Validating += new System.ComponentModel.CancelEventHandler(this.cboUIntVal_Validating);
            // 
            // lblEdgeThreshold
            // 
            this.lblEdgeThreshold.AutoSize = true;
            this.lblEdgeThreshold.Location = new System.Drawing.Point(34, 60);
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
            this.cboEdgeThreshold.Location = new System.Drawing.Point(122, 56);
            this.cboEdgeThreshold.Name = "cboEdgeThreshold";
            this.cboEdgeThreshold.Size = new System.Drawing.Size(121, 21);
            this.cboEdgeThreshold.TabIndex = 4;
            this.cboEdgeThreshold.Text = "5";
            this.cboEdgeThreshold.Validating += new System.ComponentModel.CancelEventHandler(this.cboUIntVal_Validating);
            // 
            // lblSmoothing
            // 
            this.lblSmoothing.AutoSize = true;
            this.lblSmoothing.Location = new System.Drawing.Point(0, 32);
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
            this.cboSmoothing.Location = new System.Drawing.Point(122, 28);
            this.cboSmoothing.Name = "cboSmoothing";
            this.cboSmoothing.Size = new System.Drawing.Size(121, 21);
            this.cboSmoothing.TabIndex = 2;
            this.cboSmoothing.Text = "1";
            this.cboSmoothing.Validating += new System.ComponentModel.CancelEventHandler(this.cboSmoothing_Validating);
            // 
            // lblIterations
            // 
            this.lblIterations.AutoSize = true;
            this.lblIterations.Location = new System.Drawing.Point(44, 4);
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
            this.cboIterations.Location = new System.Drawing.Point(122, 0);
            this.cboIterations.Name = "cboIterations";
            this.cboIterations.Size = new System.Drawing.Size(121, 21);
            this.cboIterations.TabIndex = 0;
            this.cboIterations.Text = "20";
            this.cboIterations.Validating += new System.ComponentModel.CancelEventHandler(this.cboUIntVal_Validating);
            // 
            // lblType
            // 
            this.lblType.AutoSize = true;
            this.lblType.Location = new System.Drawing.Point(97, 31);
            this.lblType.Name = "lblType";
            this.lblType.Size = new System.Drawing.Size(34, 13);
            this.lblType.TabIndex = 2;
            this.lblType.Text = "Type:";
            // 
            // rbAdaptive
            // 
            this.rbAdaptive.AutoSize = true;
            this.rbAdaptive.Location = new System.Drawing.Point(214, 29);
            this.rbAdaptive.Name = "rbAdaptive";
            this.rbAdaptive.Size = new System.Drawing.Size(67, 17);
            this.rbAdaptive.TabIndex = 1;
            this.rbAdaptive.Text = "Adaptive";
            this.rbAdaptive.UseVisualStyleBackColor = true;
            this.rbAdaptive.Click += new System.EventHandler(this.rbAdaptive_Click);
            // 
            // rbStandard
            // 
            this.rbStandard.AutoSize = true;
            this.rbStandard.Checked = true;
            this.rbStandard.Location = new System.Drawing.Point(134, 29);
            this.rbStandard.Name = "rbStandard";
            this.rbStandard.Size = new System.Drawing.Size(68, 17);
            this.rbStandard.TabIndex = 0;
            this.rbStandard.TabStop = true;
            this.rbStandard.Text = "Standard";
            this.rbStandard.UseVisualStyleBackColor = true;
            this.rbStandard.Click += new System.EventHandler(this.rbAdaptive_Click);
            // 
            // btnHelp
            // 
            this.btnHelp.BackColor = System.Drawing.Color.Yellow;
            this.btnHelp.Location = new System.Drawing.Point(11, 273);
            this.btnHelp.Name = "btnHelp";
            this.btnHelp.Size = new System.Drawing.Size(60, 26);
            this.btnHelp.TabIndex = 13;
            this.btnHelp.Text = "Help";
            this.btnHelp.UseVisualStyleBackColor = false;
            this.btnHelp.Click += new System.EventHandler(this.btnHelp_Click);
            // 
            // btnCancel
            // 
            this.btnCancel.BackColor = System.Drawing.Color.OrangeRed;
            this.btnCancel.Location = new System.Drawing.Point(373, 273);
            this.btnCancel.Name = "btnCancel";
            this.btnCancel.Size = new System.Drawing.Size(60, 26);
            this.btnCancel.TabIndex = 14;
            this.btnCancel.Text = "Cancel";
            this.btnCancel.UseVisualStyleBackColor = false;
            this.btnCancel.Click += new System.EventHandler(this.btnCancel_Click);
            // 
            // btnReset
            // 
            this.btnReset.BackColor = System.Drawing.Color.CornflowerBlue;
            this.btnReset.Location = new System.Drawing.Point(439, 273);
            this.btnReset.Name = "btnReset";
            this.btnReset.Size = new System.Drawing.Size(60, 26);
            this.btnReset.TabIndex = 15;
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
            this.btnApply.TabIndex = 16;
            this.btnApply.Text = "Apply";
            this.btnApply.UseVisualStyleBackColor = false;
            this.btnApply.Click += new System.EventHandler(this.btnApply_Click);
            // 
            // Smoothing
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.rbMean);
            this.Controls.Add(this.rbGaussian);
            this.Controls.Add(this.rbMidpoint);
            this.Controls.Add(this.rbContraHarmonic);
            this.Controls.Add(this.rbYpMean);
            this.Controls.Add(this.rbMedian);
            this.Controls.Add(this.rbKuwahara);
            this.Controls.Add(this.rbADFilter);
            this.Controls.Add(this.rbFFTSmoothing);
            this.Controls.Add(this.rbDCTSmoothing);
            this.Controls.Add(this.grpSpatialSmoothing);
            this.Controls.Add(this.grpFreqSmoothing);
            this.Controls.Add(this.grpParameters);
            this.Controls.Add(this.btnHelp);
            this.Controls.Add(this.btnCancel);
            this.Controls.Add(this.btnReset);
            this.Controls.Add(this.btnApply);
            this.Name = "Smoothing";
            this.Size = new System.Drawing.Size(573, 305);
            this.grpParameters.ResumeLayout(false);
            this.grpParameters.PerformLayout();
            this.pnlMask.ResumeLayout(false);
            this.pnlMask.PerformLayout();
            this.pnlAnisotropic.ResumeLayout(false);
            this.pnlAnisotropic.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.RadioButton rbMean;
        private System.Windows.Forms.RadioButton rbGaussian;
        private System.Windows.Forms.RadioButton rbMidpoint;
        private System.Windows.Forms.RadioButton rbContraHarmonic;
        private System.Windows.Forms.RadioButton rbYpMean;
        private System.Windows.Forms.RadioButton rbMedian;
        private System.Windows.Forms.RadioButton rbKuwahara;
        private System.Windows.Forms.RadioButton rbADFilter;
        private System.Windows.Forms.RadioButton rbFFTSmoothing;
        private System.Windows.Forms.RadioButton rbDCTSmoothing;
        private System.Windows.Forms.GroupBox grpSpatialSmoothing;
        private System.Windows.Forms.GroupBox grpFreqSmoothing;
        private System.Windows.Forms.GroupBox grpParameters;
        private System.Windows.Forms.Label lblCutoff;
        private System.Windows.Forms.ComboBox cboCutoff;
        private System.Windows.Forms.Panel pnlMask;
        private System.Windows.Forms.Label lblOrder;
        private System.Windows.Forms.ComboBox cboOrder;
        private System.Windows.Forms.Label lblMaskSize;
        private System.Windows.Forms.ComboBox cboMaskSize;
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
        private System.Windows.Forms.RadioButton rbAdaptive;
        private System.Windows.Forms.RadioButton rbStandard;
        private System.Windows.Forms.Button btnHelp;
        private System.Windows.Forms.Button btnCancel;
        private System.Windows.Forms.Button btnReset;
        private System.Windows.Forms.Button btnApply;
    }
}
