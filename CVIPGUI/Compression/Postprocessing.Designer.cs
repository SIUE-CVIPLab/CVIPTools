namespace CVIPGUI.Compression
{
    partial class Postprocessing
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
            this.btnApply = new System.Windows.Forms.Button();
            this.btnCancel = new System.Windows.Forms.Button();
            this.btnHelp = new System.Windows.Forms.Button();
            this.btnReset = new System.Windows.Forms.Button();
            this.grpParameters = new System.Windows.Forms.GroupBox();
            this.maskPanel = new System.Windows.Forms.Panel();
            this.cbMaskSize = new System.Windows.Forms.ComboBox();
            this.lblMaskSize = new System.Windows.Forms.Label();
            this.HistStPanel = new System.Windows.Forms.Panel();
            this.cbHighClip = new System.Windows.Forms.ComboBox();
            this.cbLowClip = new System.Windows.Forms.ComboBox();
            this.cbHighLimit = new System.Windows.Forms.ComboBox();
            this.cbLowLimit = new System.Windows.Forms.ComboBox();
            this.lblhighClip = new System.Windows.Forms.Label();
            this.lblLowClip = new System.Windows.Forms.Label();
            this.lblHighLimit = new System.Windows.Forms.Label();
            this.lblLowLimit = new System.Windows.Forms.Label();
            this.HistEqPanel = new System.Windows.Forms.Panel();
            this.rbBlue = new System.Windows.Forms.RadioButton();
            this.rbGreen = new System.Windows.Forms.RadioButton();
            this.rbRed = new System.Windows.Forms.RadioButton();
            this.rbLight = new System.Windows.Forms.RadioButton();
            this.lblOnBand = new System.Windows.Forms.Label();
            this.grpPostprocessing = new System.Windows.Forms.GroupBox();
            this.grpSpatial = new System.Windows.Forms.GroupBox();
            this.rbGauss = new System.Windows.Forms.RadioButton();
            this.rbMean = new System.Windows.Forms.RadioButton();
            this.grpHist = new System.Windows.Forms.GroupBox();
            this.rbHistSt = new System.Windows.Forms.RadioButton();
            this.rbHistEq = new System.Windows.Forms.RadioButton();
            this.lblLowPercent = new System.Windows.Forms.Label();
            this.lblHighPercent = new System.Windows.Forms.Label();
            this.grpParameters.SuspendLayout();
            this.maskPanel.SuspendLayout();
            this.HistStPanel.SuspendLayout();
            this.HistEqPanel.SuspendLayout();
            this.grpPostprocessing.SuspendLayout();
            this.grpSpatial.SuspendLayout();
            this.grpHist.SuspendLayout();
            this.SuspendLayout();
            // 
            // btnApply
            // 
            this.btnApply.BackColor = System.Drawing.Color.LimeGreen;
            this.btnApply.ForeColor = System.Drawing.Color.White;
            this.btnApply.Location = new System.Drawing.Point(532, 325);
            this.btnApply.Name = "btnApply";
            this.btnApply.Size = new System.Drawing.Size(60, 26);
            this.btnApply.TabIndex = 10;
            this.btnApply.Text = "Apply";
            this.btnApply.UseVisualStyleBackColor = false;
            this.btnApply.Click += new System.EventHandler(this.btnApply_Click);
            // 
            // btnCancel
            // 
            this.btnCancel.BackColor = System.Drawing.Color.OrangeRed;
            this.btnCancel.Location = new System.Drawing.Point(400, 325);
            this.btnCancel.Name = "btnCancel";
            this.btnCancel.Size = new System.Drawing.Size(60, 26);
            this.btnCancel.TabIndex = 11;
            this.btnCancel.Text = "Cancel";
            this.btnCancel.UseVisualStyleBackColor = false;
            this.btnCancel.Click += new System.EventHandler(this.btnCancel_Click);
            // 
            // btnHelp
            // 
            this.btnHelp.BackColor = System.Drawing.Color.Yellow;
            this.btnHelp.Location = new System.Drawing.Point(12, 325);
            this.btnHelp.Name = "btnHelp";
            this.btnHelp.Size = new System.Drawing.Size(60, 26);
            this.btnHelp.TabIndex = 12;
            this.btnHelp.Text = "Help";
            this.btnHelp.UseVisualStyleBackColor = false;
            this.btnHelp.Click += new System.EventHandler(this.btnHelp_Click);
            // 
            // btnReset
            // 
            this.btnReset.BackColor = System.Drawing.Color.CornflowerBlue;
            this.btnReset.Location = new System.Drawing.Point(466, 325);
            this.btnReset.Name = "btnReset";
            this.btnReset.Size = new System.Drawing.Size(60, 26);
            this.btnReset.TabIndex = 13;
            this.btnReset.Text = "Reset";
            this.btnReset.UseVisualStyleBackColor = false;
            this.btnReset.Click += new System.EventHandler(this.btnReset_Click);
            // 
            // grpParameters
            // 
            this.grpParameters.Controls.Add(this.maskPanel);
            this.grpParameters.Controls.Add(this.HistStPanel);
            this.grpParameters.Controls.Add(this.HistEqPanel);
            this.grpParameters.Location = new System.Drawing.Point(275, 1);
            this.grpParameters.Name = "grpParameters";
            this.grpParameters.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.grpParameters.Size = new System.Drawing.Size(317, 317);
            this.grpParameters.TabIndex = 14;
            this.grpParameters.TabStop = false;
            this.grpParameters.Text = "Parameters";
            // 
            // maskPanel
            // 
            this.maskPanel.Controls.Add(this.cbMaskSize);
            this.maskPanel.Controls.Add(this.lblMaskSize);
            this.maskPanel.Location = new System.Drawing.Point(7, 179);
            this.maskPanel.Name = "maskPanel";
            this.maskPanel.Size = new System.Drawing.Size(200, 45);
            this.maskPanel.TabIndex = 2;
            // 
            // cbMaskSize
            // 
            this.cbMaskSize.FormattingEnabled = true;
            this.cbMaskSize.Items.AddRange(new object[] {
            "3",
            "5",
            "7",
            "9",
            "11"});
            this.cbMaskSize.Location = new System.Drawing.Point(73, 12);
            this.cbMaskSize.Name = "cbMaskSize";
            this.cbMaskSize.Size = new System.Drawing.Size(54, 21);
            this.cbMaskSize.TabIndex = 1;
            this.cbMaskSize.Text = "3";
            this.cbMaskSize.Validating += new System.ComponentModel.CancelEventHandler(this.cboIntVal_Validating);
            // 
            // lblMaskSize
            // 
            this.lblMaskSize.AutoSize = true;
            this.lblMaskSize.Location = new System.Drawing.Point(8, 15);
            this.lblMaskSize.Name = "lblMaskSize";
            this.lblMaskSize.Size = new System.Drawing.Size(59, 13);
            this.lblMaskSize.TabIndex = 0;
            this.lblMaskSize.Text = "Mask Size:";
            // 
            // HistStPanel
            // 
            this.HistStPanel.Controls.Add(this.lblHighPercent);
            this.HistStPanel.Controls.Add(this.lblLowPercent);
            this.HistStPanel.Controls.Add(this.cbHighClip);
            this.HistStPanel.Controls.Add(this.cbLowClip);
            this.HistStPanel.Controls.Add(this.cbHighLimit);
            this.HistStPanel.Controls.Add(this.cbLowLimit);
            this.HistStPanel.Controls.Add(this.lblhighClip);
            this.HistStPanel.Controls.Add(this.lblLowClip);
            this.HistStPanel.Controls.Add(this.lblHighLimit);
            this.HistStPanel.Controls.Add(this.lblLowLimit);
            this.HistStPanel.Location = new System.Drawing.Point(7, 61);
            this.HistStPanel.Name = "HistStPanel";
            this.HistStPanel.Size = new System.Drawing.Size(264, 111);
            this.HistStPanel.TabIndex = 1;
            // 
            // cbHighClip
            // 
            this.cbHighClip.FormattingEnabled = true;
            this.cbHighClip.Items.AddRange(new object[] {
            "0.01",
            "0.02",
            "0.025",
            "0.03",
            "0.04",
            "0.05",
            "0.075",
            "0.1",
            "0.15"});
            this.cbHighClip.Location = new System.Drawing.Point(132, 80);
            this.cbHighClip.Name = "cbHighClip";
            this.cbHighClip.Size = new System.Drawing.Size(74, 21);
            this.cbHighClip.TabIndex = 7;
            this.cbHighClip.Text = "0.025";
            this.cbHighClip.TextChanged += new System.EventHandler(this.Percent_TextChanged);
            this.cbHighClip.Validating += new System.ComponentModel.CancelEventHandler(this.cboFloatVal_Validating);
            // 
            // cbLowClip
            // 
            this.cbLowClip.FormattingEnabled = true;
            this.cbLowClip.Items.AddRange(new object[] {
            "0.01",
            "0.02",
            "0.025",
            "0.03",
            "0.04",
            "0.05",
            "0.075",
            "0.1",
            "0.15"});
            this.cbLowClip.Location = new System.Drawing.Point(132, 55);
            this.cbLowClip.Name = "cbLowClip";
            this.cbLowClip.Size = new System.Drawing.Size(74, 21);
            this.cbLowClip.TabIndex = 6;
            this.cbLowClip.Text = "0.025";
            this.cbLowClip.TextChanged += new System.EventHandler(this.Percent_TextChanged);
            this.cbLowClip.Validating += new System.ComponentModel.CancelEventHandler(this.cboFloatVal_Validating);
            // 
            // cbHighLimit
            // 
            this.cbHighLimit.FormattingEnabled = true;
            this.cbHighLimit.Items.AddRange(new object[] {
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
            this.cbHighLimit.Location = new System.Drawing.Point(132, 30);
            this.cbHighLimit.Name = "cbHighLimit";
            this.cbHighLimit.Size = new System.Drawing.Size(74, 21);
            this.cbHighLimit.TabIndex = 5;
            this.cbHighLimit.Text = "255";
            this.cbHighLimit.Validating += new System.ComponentModel.CancelEventHandler(this.cboIntVal_Validating);
            // 
            // cbLowLimit
            // 
            this.cbLowLimit.FormattingEnabled = true;
            this.cbLowLimit.Items.AddRange(new object[] {
            "0",
            "1",
            "10",
            "20",
            "30",
            "40",
            "50",
            "75",
            "100"});
            this.cbLowLimit.Location = new System.Drawing.Point(132, 5);
            this.cbLowLimit.Name = "cbLowLimit";
            this.cbLowLimit.Size = new System.Drawing.Size(74, 21);
            this.cbLowLimit.TabIndex = 4;
            this.cbLowLimit.Text = "0";
            this.cbLowLimit.Validating += new System.ComponentModel.CancelEventHandler(this.cboIntVal_Validating);
            // 
            // lblhighClip
            // 
            this.lblhighClip.AutoSize = true;
            this.lblhighClip.Location = new System.Drawing.Point(5, 85);
            this.lblhighClip.Name = "lblhighClip";
            this.lblhighClip.Size = new System.Drawing.Size(92, 13);
            this.lblhighClip.TabIndex = 3;
            this.lblhighClip.Text = "High Clip Percent:";
            // 
            // lblLowClip
            // 
            this.lblLowClip.AutoSize = true;
            this.lblLowClip.Location = new System.Drawing.Point(5, 60);
            this.lblLowClip.Name = "lblLowClip";
            this.lblLowClip.Size = new System.Drawing.Size(90, 13);
            this.lblLowClip.TabIndex = 2;
            this.lblLowClip.Text = "Low Clip Percent:";
            // 
            // lblHighLimit
            // 
            this.lblHighLimit.AutoSize = true;
            this.lblHighLimit.Location = new System.Drawing.Point(5, 35);
            this.lblHighLimit.Name = "lblHighLimit";
            this.lblHighLimit.Size = new System.Drawing.Size(53, 13);
            this.lblHighLimit.TabIndex = 1;
            this.lblHighLimit.Text = "HighLimit:";
            // 
            // lblLowLimit
            // 
            this.lblLowLimit.AutoSize = true;
            this.lblLowLimit.Location = new System.Drawing.Point(5, 10);
            this.lblLowLimit.Name = "lblLowLimit";
            this.lblLowLimit.Size = new System.Drawing.Size(54, 13);
            this.lblLowLimit.TabIndex = 0;
            this.lblLowLimit.Text = "Low Limit:";
            // 
            // HistEqPanel
            // 
            this.HistEqPanel.Controls.Add(this.rbBlue);
            this.HistEqPanel.Controls.Add(this.rbGreen);
            this.HistEqPanel.Controls.Add(this.rbRed);
            this.HistEqPanel.Controls.Add(this.rbLight);
            this.HistEqPanel.Controls.Add(this.lblOnBand);
            this.HistEqPanel.Location = new System.Drawing.Point(7, 20);
            this.HistEqPanel.Name = "HistEqPanel";
            this.HistEqPanel.Size = new System.Drawing.Size(304, 34);
            this.HistEqPanel.TabIndex = 0;
            // 
            // rbBlue
            // 
            this.rbBlue.AutoSize = true;
            this.rbBlue.Location = new System.Drawing.Point(242, 10);
            this.rbBlue.Name = "rbBlue";
            this.rbBlue.Size = new System.Drawing.Size(46, 17);
            this.rbBlue.TabIndex = 3;
            this.rbBlue.TabStop = true;
            this.rbBlue.Text = "Blue";
            this.rbBlue.UseVisualStyleBackColor = true;
            // 
            // rbGreen
            // 
            this.rbGreen.AutoSize = true;
            this.rbGreen.Location = new System.Drawing.Point(182, 10);
            this.rbGreen.Name = "rbGreen";
            this.rbGreen.Size = new System.Drawing.Size(54, 17);
            this.rbGreen.TabIndex = 2;
            this.rbGreen.TabStop = true;
            this.rbGreen.Text = "Green";
            this.rbGreen.UseVisualStyleBackColor = true;
            // 
            // rbRed
            // 
            this.rbRed.AutoSize = true;
            this.rbRed.Location = new System.Drawing.Point(132, 10);
            this.rbRed.Name = "rbRed";
            this.rbRed.Size = new System.Drawing.Size(45, 17);
            this.rbRed.TabIndex = 1;
            this.rbRed.TabStop = true;
            this.rbRed.Text = "Red";
            this.rbRed.UseVisualStyleBackColor = true;
            // 
            // rbLight
            // 
            this.rbLight.AutoSize = true;
            this.rbLight.Location = new System.Drawing.Point(60, 10);
            this.rbLight.Name = "rbLight";
            this.rbLight.Size = new System.Drawing.Size(70, 17);
            this.rbLight.TabIndex = 0;
            this.rbLight.TabStop = true;
            this.rbLight.Text = "Lightness";
            this.rbLight.UseVisualStyleBackColor = true;
            // 
            // lblOnBand
            // 
            this.lblOnBand.AutoSize = true;
            this.lblOnBand.Location = new System.Drawing.Point(2, 12);
            this.lblOnBand.Name = "lblOnBand";
            this.lblOnBand.Size = new System.Drawing.Size(52, 13);
            this.lblOnBand.TabIndex = 0;
            this.lblOnBand.Text = "On Band:";
            // 
            // grpPostprocessing
            // 
            this.grpPostprocessing.Controls.Add(this.grpSpatial);
            this.grpPostprocessing.Controls.Add(this.grpHist);
            this.grpPostprocessing.Location = new System.Drawing.Point(5, 1);
            this.grpPostprocessing.Name = "grpPostprocessing";
            this.grpPostprocessing.Size = new System.Drawing.Size(263, 317);
            this.grpPostprocessing.TabIndex = 0;
            this.grpPostprocessing.TabStop = false;
            // 
            // grpSpatial
            // 
            this.grpSpatial.Controls.Add(this.rbGauss);
            this.grpSpatial.Controls.Add(this.rbMean);
            this.grpSpatial.Location = new System.Drawing.Point(10, 75);
            this.grpSpatial.Name = "grpSpatial";
            this.grpSpatial.Size = new System.Drawing.Size(243, 63);
            this.grpSpatial.TabIndex = 1;
            this.grpSpatial.TabStop = false;
            // 
            // rbGauss
            // 
            this.rbGauss.AutoSize = true;
            this.rbGauss.Location = new System.Drawing.Point(6, 40);
            this.rbGauss.Name = "rbGauss";
            this.rbGauss.Size = new System.Drawing.Size(94, 17);
            this.rbGauss.TabIndex = 3;
            this.rbGauss.Text = "Gaussian Filter";
            this.rbGauss.UseVisualStyleBackColor = true;
            this.rbGauss.Click += new System.EventHandler(this.rbPostprocessing_Click);
            // 
            // rbMean
            // 
            this.rbMean.AutoSize = true;
            this.rbMean.Location = new System.Drawing.Point(6, 19);
            this.rbMean.Name = "rbMean";
            this.rbMean.Size = new System.Drawing.Size(77, 17);
            this.rbMean.TabIndex = 2;
            this.rbMean.Text = "Mean Filter";
            this.rbMean.UseVisualStyleBackColor = true;
            this.rbMean.Click += new System.EventHandler(this.rbPostprocessing_Click);
            // 
            // grpHist
            // 
            this.grpHist.Controls.Add(this.rbHistSt);
            this.grpHist.Controls.Add(this.rbHistEq);
            this.grpHist.Location = new System.Drawing.Point(10, 10);
            this.grpHist.Name = "grpHist";
            this.grpHist.Size = new System.Drawing.Size(243, 63);
            this.grpHist.TabIndex = 0;
            this.grpHist.TabStop = false;
            // 
            // rbHistSt
            // 
            this.rbHistSt.AutoSize = true;
            this.rbHistSt.Location = new System.Drawing.Point(6, 40);
            this.rbHistSt.Name = "rbHistSt";
            this.rbHistSt.Size = new System.Drawing.Size(109, 17);
            this.rbHistSt.TabIndex = 1;
            this.rbHistSt.Text = "Histogram Stretch";
            this.rbHistSt.UseVisualStyleBackColor = true;
            this.rbHistSt.Click += new System.EventHandler(this.rbPostprocessing_Click);
            // 
            // rbHistEq
            // 
            this.rbHistEq.AutoSize = true;
            this.rbHistEq.Checked = true;
            this.rbHistEq.Location = new System.Drawing.Point(6, 19);
            this.rbHistEq.Name = "rbHistEq";
            this.rbHistEq.Size = new System.Drawing.Size(132, 17);
            this.rbHistEq.TabIndex = 0;
            this.rbHistEq.TabStop = true;
            this.rbHistEq.Text = "Histogram Equalization";
            this.rbHistEq.UseVisualStyleBackColor = true;
            this.rbHistEq.Click += new System.EventHandler(this.rbPostprocessing_Click);
            // 
            // lblLowPercent
            // 
            this.lblLowPercent.AutoSize = true;
            this.lblLowPercent.ForeColor = System.Drawing.Color.Blue;
            this.lblLowPercent.Location = new System.Drawing.Point(212, 60);
            this.lblLowPercent.Name = "lblLowPercent";
            this.lblLowPercent.Size = new System.Drawing.Size(30, 13);
            this.lblLowPercent.TabIndex = 43;
            this.lblLowPercent.Text = "2.5%";
            // 
            // lblHighPercent
            // 
            this.lblHighPercent.AutoSize = true;
            this.lblHighPercent.ForeColor = System.Drawing.Color.Blue;
            this.lblHighPercent.Location = new System.Drawing.Point(212, 83);
            this.lblHighPercent.Name = "lblHighPercent";
            this.lblHighPercent.Size = new System.Drawing.Size(30, 13);
            this.lblHighPercent.TabIndex = 44;
            this.lblHighPercent.Text = "2.5%";
            // 
            // Postprocessing
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.grpPostprocessing);
            this.Controls.Add(this.grpParameters);
            this.Controls.Add(this.btnReset);
            this.Controls.Add(this.btnHelp);
            this.Controls.Add(this.btnCancel);
            this.Controls.Add(this.btnApply);
            this.Name = "Postprocessing";
            this.Size = new System.Drawing.Size(601, 354);
            this.grpParameters.ResumeLayout(false);
            this.maskPanel.ResumeLayout(false);
            this.maskPanel.PerformLayout();
            this.HistStPanel.ResumeLayout(false);
            this.HistStPanel.PerformLayout();
            this.HistEqPanel.ResumeLayout(false);
            this.HistEqPanel.PerformLayout();
            this.grpPostprocessing.ResumeLayout(false);
            this.grpSpatial.ResumeLayout(false);
            this.grpSpatial.PerformLayout();
            this.grpHist.ResumeLayout(false);
            this.grpHist.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button btnApply;
        private System.Windows.Forms.Button btnCancel;
        private System.Windows.Forms.Button btnHelp;
        private System.Windows.Forms.Button btnReset;
        private System.Windows.Forms.GroupBox grpParameters;
        private System.Windows.Forms.GroupBox grpPostprocessing;
        private System.Windows.Forms.GroupBox grpHist;
        private System.Windows.Forms.GroupBox grpSpatial;
        private System.Windows.Forms.RadioButton rbHistEq;
        private System.Windows.Forms.RadioButton rbGauss;
        private System.Windows.Forms.RadioButton rbMean;
        private System.Windows.Forms.RadioButton rbHistSt;
        private System.Windows.Forms.Panel HistStPanel;
        private System.Windows.Forms.Label lblhighClip;
        private System.Windows.Forms.Label lblLowClip;
        private System.Windows.Forms.Label lblHighLimit;
        private System.Windows.Forms.Label lblLowLimit;
        private System.Windows.Forms.Panel HistEqPanel;
        private System.Windows.Forms.RadioButton rbBlue;
        private System.Windows.Forms.RadioButton rbGreen;
        private System.Windows.Forms.RadioButton rbRed;
        private System.Windows.Forms.RadioButton rbLight;
        private System.Windows.Forms.Label lblOnBand;
        private System.Windows.Forms.Panel maskPanel;
        private System.Windows.Forms.ComboBox cbMaskSize;
        private System.Windows.Forms.Label lblMaskSize;
        private System.Windows.Forms.ComboBox cbHighClip;
        private System.Windows.Forms.ComboBox cbLowClip;
        private System.Windows.Forms.ComboBox cbHighLimit;
        private System.Windows.Forms.ComboBox cbLowLimit;
        private System.Windows.Forms.Label lblHighPercent;
        private System.Windows.Forms.Label lblLowPercent;
    }
}
