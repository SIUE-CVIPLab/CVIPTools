namespace CVIPGUI.Enhancement
{
    partial class Sharpening
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
            this.groupBoxHistogramParameter = new System.Windows.Forms.GroupBox();
            this.checkBoxSharpening1 = new System.Windows.Forms.CheckBox();
            this.checkBoxSharpening2 = new System.Windows.Forms.CheckBox();
            this.cbSharpening4 = new System.Windows.Forms.ComboBox();
            this.lbSharpening4 = new System.Windows.Forms.Label();
            this.cbSharpening3 = new System.Windows.Forms.ComboBox();
            this.lbSharpening3 = new System.Windows.Forms.Label();
            this.cbSharpening2 = new System.Windows.Forms.ComboBox();
            this.lbSharpening2 = new System.Windows.Forms.Label();
            this.cbSharpening1 = new System.Windows.Forms.ComboBox();
            this.lbSharpening1 = new System.Windows.Forms.Label();
            this.lbLaplacian = new System.Windows.Forms.Label();
            this.rbMaskII = new System.Windows.Forms.RadioButton();
            this.rbMaskI = new System.Windows.Forms.RadioButton();
            this.btSharpeningHelp = new System.Windows.Forms.Button();
            this.btSharpeningCancel = new System.Windows.Forms.Button();
            this.btSharpeningReset = new System.Windows.Forms.Button();
            this.btSharpeningApply = new System.Windows.Forms.Button();
            this.groupBoxHistogram1 = new System.Windows.Forms.GroupBox();
            this.rbSharpIII = new System.Windows.Forms.RadioButton();
            this.rbSharpingI = new System.Windows.Forms.RadioButton();
            this.rbUnsharpMasking = new System.Windows.Forms.RadioButton();
            this.rbFFTSharpening = new System.Windows.Forms.RadioButton();
            this.rbHomomorphic = new System.Windows.Forms.RadioButton();
            this.rbHighFreqEmphasis = new System.Windows.Forms.RadioButton();
            this.rbDCTSharpening = new System.Windows.Forms.RadioButton();
            this.rbHighBoost = new System.Windows.Forms.RadioButton();
            this.rbHighpassSpatial = new System.Windows.Forms.RadioButton();
            this.rbSharpingII = new System.Windows.Forms.RadioButton();
            this.groupBoxHistogram2 = new System.Windows.Forms.GroupBox();
            this.groupBoxHistogram3 = new System.Windows.Forms.GroupBox();
            this.lblLowPercent = new System.Windows.Forms.Label();
            this.lblHighPercent = new System.Windows.Forms.Label();
            this.groupBoxHistogramParameter.SuspendLayout();
            this.groupBoxHistogram1.SuspendLayout();
            this.SuspendLayout();
            // 
            // groupBoxHistogramParameter
            // 
            this.groupBoxHistogramParameter.Controls.Add(this.lblHighPercent);
            this.groupBoxHistogramParameter.Controls.Add(this.lblLowPercent);
            this.groupBoxHistogramParameter.Controls.Add(this.checkBoxSharpening1);
            this.groupBoxHistogramParameter.Controls.Add(this.checkBoxSharpening2);
            this.groupBoxHistogramParameter.Controls.Add(this.cbSharpening4);
            this.groupBoxHistogramParameter.Controls.Add(this.lbSharpening4);
            this.groupBoxHistogramParameter.Controls.Add(this.cbSharpening3);
            this.groupBoxHistogramParameter.Controls.Add(this.lbSharpening3);
            this.groupBoxHistogramParameter.Controls.Add(this.cbSharpening2);
            this.groupBoxHistogramParameter.Controls.Add(this.lbSharpening2);
            this.groupBoxHistogramParameter.Controls.Add(this.cbSharpening1);
            this.groupBoxHistogramParameter.Controls.Add(this.lbSharpening1);
            this.groupBoxHistogramParameter.Controls.Add(this.lbLaplacian);
            this.groupBoxHistogramParameter.Controls.Add(this.rbMaskII);
            this.groupBoxHistogramParameter.Controls.Add(this.rbMaskI);
            this.groupBoxHistogramParameter.Location = new System.Drawing.Point(175, 1);
            this.groupBoxHistogramParameter.Name = "groupBoxHistogramParameter";
            this.groupBoxHistogramParameter.Size = new System.Drawing.Size(392, 254);
            this.groupBoxHistogramParameter.TabIndex = 21;
            this.groupBoxHistogramParameter.TabStop = false;
            this.groupBoxHistogramParameter.Text = "Parameters";
            // 
            // checkBoxSharpening1
            // 
            this.checkBoxSharpening1.AutoSize = true;
            this.checkBoxSharpening1.Checked = true;
            this.checkBoxSharpening1.CheckState = System.Windows.Forms.CheckState.Checked;
            this.checkBoxSharpening1.Location = new System.Drawing.Point(18, 192);
            this.checkBoxSharpening1.Name = "checkBoxSharpening1";
            this.checkBoxSharpening1.Size = new System.Drawing.Size(173, 17);
            this.checkBoxSharpening1.TabIndex = 3;
            this.checkBoxSharpening1.Text = "Intermediate Image Remapping";
            this.checkBoxSharpening1.UseVisualStyleBackColor = true;
            // 
            // checkBoxSharpening2
            // 
            this.checkBoxSharpening2.AutoSize = true;
            this.checkBoxSharpening2.Checked = true;
            this.checkBoxSharpening2.CheckState = System.Windows.Forms.CheckState.Checked;
            this.checkBoxSharpening2.Location = new System.Drawing.Point(18, 215);
            this.checkBoxSharpening2.Name = "checkBoxSharpening2";
            this.checkBoxSharpening2.Size = new System.Drawing.Size(127, 17);
            this.checkBoxSharpening2.TabIndex = 3;
            this.checkBoxSharpening2.Text = "Add to Original Image";
            this.checkBoxSharpening2.UseVisualStyleBackColor = true;
            // 
            // cbSharpening4
            // 
            this.cbSharpening4.FormattingEnabled = true;
            this.cbSharpening4.Location = new System.Drawing.Point(150, 145);
            this.cbSharpening4.Name = "cbSharpening4";
            this.cbSharpening4.Size = new System.Drawing.Size(110, 21);
            this.cbSharpening4.TabIndex = 2;
            this.cbSharpening4.Visible = false;
            this.cbSharpening4.TextChanged += new System.EventHandler(this.Percent_TextChanged);
            this.cbSharpening4.Leave += new System.EventHandler(this.cbSharpening4_Leave);
            // 
            // lbSharpening4
            // 
            this.lbSharpening4.AutoSize = true;
            this.lbSharpening4.Location = new System.Drawing.Point(15, 149);
            this.lbSharpening4.Name = "lbSharpening4";
            this.lbSharpening4.Size = new System.Drawing.Size(106, 13);
            this.lbSharpening4.TabIndex = 1;
            this.lbSharpening4.Text = "Low clip percentage ";
            this.lbSharpening4.Visible = false;
            // 
            // cbSharpening3
            // 
            this.cbSharpening3.FormattingEnabled = true;
            this.cbSharpening3.Location = new System.Drawing.Point(150, 118);
            this.cbSharpening3.Name = "cbSharpening3";
            this.cbSharpening3.Size = new System.Drawing.Size(110, 21);
            this.cbSharpening3.TabIndex = 2;
            this.cbSharpening3.TextChanged += new System.EventHandler(this.Percent_TextChanged);
            this.cbSharpening3.Leave += new System.EventHandler(this.cbSharpening3_Leave);
            // 
            // lbSharpening3
            // 
            this.lbSharpening3.AutoSize = true;
            this.lbSharpening3.Location = new System.Drawing.Point(15, 122);
            this.lbSharpening3.Name = "lbSharpening3";
            this.lbSharpening3.Size = new System.Drawing.Size(106, 13);
            this.lbSharpening3.TabIndex = 1;
            this.lbSharpening3.Text = "Low clip percentage ";
            // 
            // cbSharpening2
            // 
            this.cbSharpening2.FormattingEnabled = true;
            this.cbSharpening2.Location = new System.Drawing.Point(150, 91);
            this.cbSharpening2.Name = "cbSharpening2";
            this.cbSharpening2.Size = new System.Drawing.Size(110, 21);
            this.cbSharpening2.TabIndex = 2;
            this.cbSharpening2.TextChanged += new System.EventHandler(this.Percent_TextChanged);
            this.cbSharpening2.Leave += new System.EventHandler(this.cbSharpening2_Leave);
            // 
            // lbSharpening2
            // 
            this.lbSharpening2.AutoSize = true;
            this.lbSharpening2.Location = new System.Drawing.Point(15, 95);
            this.lbSharpening2.Name = "lbSharpening2";
            this.lbSharpening2.Size = new System.Drawing.Size(106, 13);
            this.lbSharpening2.TabIndex = 1;
            this.lbSharpening2.Text = "Low clip percentage ";
            // 
            // cbSharpening1
            // 
            this.cbSharpening1.FormattingEnabled = true;
            this.cbSharpening1.Location = new System.Drawing.Point(150, 64);
            this.cbSharpening1.Name = "cbSharpening1";
            this.cbSharpening1.Size = new System.Drawing.Size(110, 21);
            this.cbSharpening1.TabIndex = 2;
            this.cbSharpening1.Leave += new System.EventHandler(this.cbSharpening1_Leave);
            // 
            // lbSharpening1
            // 
            this.lbSharpening1.AutoSize = true;
            this.lbSharpening1.Location = new System.Drawing.Point(15, 68);
            this.lbSharpening1.Name = "lbSharpening1";
            this.lbSharpening1.Size = new System.Drawing.Size(106, 13);
            this.lbSharpening1.TabIndex = 1;
            this.lbSharpening1.Text = "Low clip percentage ";
            // 
            // lbLaplacian
            // 
            this.lbLaplacian.AutoSize = true;
            this.lbLaplacian.Location = new System.Drawing.Point(15, 31);
            this.lbLaplacian.Name = "lbLaplacian";
            this.lbLaplacian.Size = new System.Drawing.Size(53, 13);
            this.lbLaplacian.TabIndex = 1;
            this.lbLaplacian.Text = "Laplacian";
            // 
            // rbMaskII
            // 
            this.rbMaskII.AutoSize = true;
            this.rbMaskII.Location = new System.Drawing.Point(250, 29);
            this.rbMaskII.Name = "rbMaskII";
            this.rbMaskII.Size = new System.Drawing.Size(60, 17);
            this.rbMaskII.TabIndex = 0;
            this.rbMaskII.Text = "Mask II";
            this.rbMaskII.UseVisualStyleBackColor = true;
            // 
            // rbMaskI
            // 
            this.rbMaskI.AutoSize = true;
            this.rbMaskI.Checked = true;
            this.rbMaskI.Location = new System.Drawing.Point(150, 29);
            this.rbMaskI.Name = "rbMaskI";
            this.rbMaskI.Size = new System.Drawing.Size(54, 17);
            this.rbMaskI.TabIndex = 0;
            this.rbMaskI.TabStop = true;
            this.rbMaskI.Text = "MaskI";
            this.rbMaskI.UseVisualStyleBackColor = true;
            // 
            // btSharpeningHelp
            // 
            this.btSharpeningHelp.BackColor = System.Drawing.Color.Yellow;
            this.btSharpeningHelp.Location = new System.Drawing.Point(11, 273);
            this.btSharpeningHelp.Name = "btSharpeningHelp";
            this.btSharpeningHelp.Size = new System.Drawing.Size(60, 26);
            this.btSharpeningHelp.TabIndex = 19;
            this.btSharpeningHelp.Text = "Help";
            this.btSharpeningHelp.UseVisualStyleBackColor = false;
            this.btSharpeningHelp.Click += new System.EventHandler(this.btSharpeningHelp_Click);
            // 
            // btSharpeningCancel
            // 
            this.btSharpeningCancel.BackColor = System.Drawing.Color.OrangeRed;
            this.btSharpeningCancel.Location = new System.Drawing.Point(373, 273);
            this.btSharpeningCancel.Name = "btSharpeningCancel";
            this.btSharpeningCancel.Size = new System.Drawing.Size(60, 26);
            this.btSharpeningCancel.TabIndex = 20;
            this.btSharpeningCancel.Text = "Cancel";
            this.btSharpeningCancel.UseVisualStyleBackColor = false;
            this.btSharpeningCancel.Click += new System.EventHandler(this.btSharpeningCancel_Click);
            // 
            // btSharpeningReset
            // 
            this.btSharpeningReset.BackColor = System.Drawing.Color.CornflowerBlue;
            this.btSharpeningReset.Location = new System.Drawing.Point(439, 273);
            this.btSharpeningReset.Name = "btSharpeningReset";
            this.btSharpeningReset.Size = new System.Drawing.Size(60, 26);
            this.btSharpeningReset.TabIndex = 17;
            this.btSharpeningReset.Text = "Reset";
            this.btSharpeningReset.UseVisualStyleBackColor = false;
            this.btSharpeningReset.Click += new System.EventHandler(this.btSharpeningReset_Click);
            // 
            // btSharpeningApply
            // 
            this.btSharpeningApply.BackColor = System.Drawing.Color.LimeGreen;
            this.btSharpeningApply.ForeColor = System.Drawing.Color.White;
            this.btSharpeningApply.Location = new System.Drawing.Point(505, 273);
            this.btSharpeningApply.Name = "btSharpeningApply";
            this.btSharpeningApply.Size = new System.Drawing.Size(60, 26);
            this.btSharpeningApply.TabIndex = 18;
            this.btSharpeningApply.Text = "Apply";
            this.btSharpeningApply.UseVisualStyleBackColor = false;
            this.btSharpeningApply.Click += new System.EventHandler(this.btSharpeningApply_Click);
            // 
            // groupBoxHistogram1
            // 
            this.groupBoxHistogram1.Controls.Add(this.rbSharpIII);
            this.groupBoxHistogram1.Controls.Add(this.rbSharpingI);
            this.groupBoxHistogram1.Controls.Add(this.rbUnsharpMasking);
            this.groupBoxHistogram1.Controls.Add(this.rbFFTSharpening);
            this.groupBoxHistogram1.Controls.Add(this.rbHomomorphic);
            this.groupBoxHistogram1.Controls.Add(this.rbHighFreqEmphasis);
            this.groupBoxHistogram1.Controls.Add(this.rbDCTSharpening);
            this.groupBoxHistogram1.Controls.Add(this.rbHighBoost);
            this.groupBoxHistogram1.Controls.Add(this.rbHighpassSpatial);
            this.groupBoxHistogram1.Controls.Add(this.rbSharpingII);
            this.groupBoxHistogram1.Controls.Add(this.groupBoxHistogram2);
            this.groupBoxHistogram1.Controls.Add(this.groupBoxHistogram3);
            this.groupBoxHistogram1.Location = new System.Drawing.Point(6, 1);
            this.groupBoxHistogram1.Name = "groupBoxHistogram1";
            this.groupBoxHistogram1.Size = new System.Drawing.Size(166, 255);
            this.groupBoxHistogram1.TabIndex = 16;
            this.groupBoxHistogram1.TabStop = false;
            this.groupBoxHistogram1.Text = "Spatial Domain Sharpening";
            // 
            // rbSharpIII
            // 
            this.rbSharpIII.AutoSize = true;
            this.rbSharpIII.Location = new System.Drawing.Point(5, 58);
            this.rbSharpIII.Name = "rbSharpIII";
            this.rbSharpIII.Size = new System.Drawing.Size(137, 17);
            this.rbSharpIII.TabIndex = 1;
            this.rbSharpIII.Text = "Sharpening Algorithm III";
            this.rbSharpIII.UseVisualStyleBackColor = true;
            this.rbSharpIII.Click += new System.EventHandler(this.rbSharpIII_Click);
            // 
            // rbSharpingI
            // 
            this.rbSharpingI.AutoSize = true;
            this.rbSharpingI.Checked = true;
            this.rbSharpingI.Location = new System.Drawing.Point(5, 20);
            this.rbSharpingI.Name = "rbSharpingI";
            this.rbSharpingI.Size = new System.Drawing.Size(131, 17);
            this.rbSharpingI.TabIndex = 0;
            this.rbSharpingI.TabStop = true;
            this.rbSharpingI.Text = "Sharpening Algorithm I";
            this.rbSharpingI.UseVisualStyleBackColor = true;
            this.rbSharpingI.Click += new System.EventHandler(this.rbSharpingI_Click);
            // 
            // rbUnsharpMasking
            // 
            this.rbUnsharpMasking.AutoSize = true;
            this.rbUnsharpMasking.Location = new System.Drawing.Point(5, 115);
            this.rbUnsharpMasking.Name = "rbUnsharpMasking";
            this.rbUnsharpMasking.Size = new System.Drawing.Size(108, 17);
            this.rbUnsharpMasking.TabIndex = 0;
            this.rbUnsharpMasking.Text = "Unsharp Masking";
            this.rbUnsharpMasking.UseVisualStyleBackColor = true;
            this.rbUnsharpMasking.Click += new System.EventHandler(this.rbUnsharpMasking_Click);
            // 
            // rbFFTSharpening
            // 
            this.rbFFTSharpening.AutoSize = true;
            this.rbFFTSharpening.Location = new System.Drawing.Point(5, 164);
            this.rbFFTSharpening.Name = "rbFFTSharpening";
            this.rbFFTSharpening.Size = new System.Drawing.Size(101, 17);
            this.rbFFTSharpening.TabIndex = 0;
            this.rbFFTSharpening.Text = "FFT Sharpening";
            this.rbFFTSharpening.UseVisualStyleBackColor = true;
            this.rbFFTSharpening.Click += new System.EventHandler(this.rbFFTSharpening_Click);
            // 
            // rbHomomorphic
            // 
            this.rbHomomorphic.AutoSize = true;
            this.rbHomomorphic.Location = new System.Drawing.Point(5, 224);
            this.rbHomomorphic.Name = "rbHomomorphic";
            this.rbHomomorphic.Size = new System.Drawing.Size(147, 17);
            this.rbHomomorphic.TabIndex = 0;
            this.rbHomomorphic.Text = "Homomorphic Sharpening";
            this.rbHomomorphic.UseVisualStyleBackColor = true;
            this.rbHomomorphic.Click += new System.EventHandler(this.rbHomomorphic_Click);
            // 
            // rbHighFreqEmphasis
            // 
            this.rbHighFreqEmphasis.AutoSize = true;
            this.rbHighFreqEmphasis.Location = new System.Drawing.Point(5, 204);
            this.rbHighFreqEmphasis.Name = "rbHighFreqEmphasis";
            this.rbHighFreqEmphasis.Size = new System.Drawing.Size(148, 17);
            this.rbHighFreqEmphasis.TabIndex = 0;
            this.rbHighFreqEmphasis.Text = "High Frequency Emphasis";
            this.rbHighFreqEmphasis.UseVisualStyleBackColor = true;
            this.rbHighFreqEmphasis.Click += new System.EventHandler(this.rbHighFreqEmphasis_Click);
            // 
            // rbDCTSharpening
            // 
            this.rbDCTSharpening.AutoSize = true;
            this.rbDCTSharpening.Location = new System.Drawing.Point(5, 184);
            this.rbDCTSharpening.Name = "rbDCTSharpening";
            this.rbDCTSharpening.Size = new System.Drawing.Size(104, 17);
            this.rbDCTSharpening.TabIndex = 0;
            this.rbDCTSharpening.Text = "DCT Sharpening";
            this.rbDCTSharpening.UseVisualStyleBackColor = true;
            this.rbDCTSharpening.Click += new System.EventHandler(this.rbDCTSharpening_Click);
            // 
            // rbHighBoost
            // 
            this.rbHighBoost.AutoSize = true;
            this.rbHighBoost.Location = new System.Drawing.Point(5, 96);
            this.rbHighBoost.Name = "rbHighBoost";
            this.rbHighBoost.Size = new System.Drawing.Size(77, 17);
            this.rbHighBoost.TabIndex = 0;
            this.rbHighBoost.Text = "High Boost";
            this.rbHighBoost.UseVisualStyleBackColor = true;
            this.rbHighBoost.Click += new System.EventHandler(this.rbHighBoost_Click);
            // 
            // rbHighpassSpatial
            // 
            this.rbHighpassSpatial.AutoSize = true;
            this.rbHighpassSpatial.Location = new System.Drawing.Point(5, 77);
            this.rbHighpassSpatial.Name = "rbHighpassSpatial";
            this.rbHighpassSpatial.Size = new System.Drawing.Size(129, 17);
            this.rbHighpassSpatial.TabIndex = 0;
            this.rbHighpassSpatial.Text = "Highpass Spatial Filter";
            this.rbHighpassSpatial.UseVisualStyleBackColor = true;
            this.rbHighpassSpatial.Click += new System.EventHandler(this.rbHighpassSpatial_Click);
            // 
            // rbSharpingII
            // 
            this.rbSharpingII.AutoSize = true;
            this.rbSharpingII.Location = new System.Drawing.Point(5, 39);
            this.rbSharpingII.Name = "rbSharpingII";
            this.rbSharpingII.Size = new System.Drawing.Size(134, 17);
            this.rbSharpingII.TabIndex = 0;
            this.rbSharpingII.Text = "Sharpening Algorithm II";
            this.rbSharpingII.UseVisualStyleBackColor = true;
            this.rbSharpingII.Click += new System.EventHandler(this.rbSharpingII_Click);
            // 
            // groupBoxHistogram2
            // 
            this.groupBoxHistogram2.Location = new System.Drawing.Point(0, 0);
            this.groupBoxHistogram2.Name = "groupBoxHistogram2";
            this.groupBoxHistogram2.Size = new System.Drawing.Size(166, 144);
            this.groupBoxHistogram2.TabIndex = 0;
            this.groupBoxHistogram2.TabStop = false;
            this.groupBoxHistogram2.Text = "Spatial Domain Sharpening";
            // 
            // groupBoxHistogram3
            // 
            this.groupBoxHistogram3.Location = new System.Drawing.Point(0, 146);
            this.groupBoxHistogram3.Name = "groupBoxHistogram3";
            this.groupBoxHistogram3.Size = new System.Drawing.Size(166, 109);
            this.groupBoxHistogram3.TabIndex = 0;
            this.groupBoxHistogram3.TabStop = false;
            this.groupBoxHistogram3.Text = "Frequency Domain Sharpen";
            // 
            // lblLowPercent
            // 
            this.lblLowPercent.AutoSize = true;
            this.lblLowPercent.ForeColor = System.Drawing.Color.Blue;
            this.lblLowPercent.Location = new System.Drawing.Point(266, 95);
            this.lblLowPercent.Name = "lblLowPercent";
            this.lblLowPercent.Size = new System.Drawing.Size(30, 13);
            this.lblLowPercent.TabIndex = 43;
            this.lblLowPercent.Text = "2.5%";
            // 
            // lblHighPercent
            // 
            this.lblHighPercent.AutoSize = true;
            this.lblHighPercent.ForeColor = System.Drawing.Color.Blue;
            this.lblHighPercent.Location = new System.Drawing.Point(266, 122);
            this.lblHighPercent.Name = "lblHighPercent";
            this.lblHighPercent.Size = new System.Drawing.Size(30, 13);
            this.lblHighPercent.TabIndex = 44;
            this.lblHighPercent.Text = "2.5%";
            // 
            // Sharpening
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.groupBoxHistogramParameter);
            this.Controls.Add(this.btSharpeningHelp);
            this.Controls.Add(this.btSharpeningCancel);
            this.Controls.Add(this.btSharpeningReset);
            this.Controls.Add(this.btSharpeningApply);
            this.Controls.Add(this.groupBoxHistogram1);
            this.Name = "Sharpening";
            this.Size = new System.Drawing.Size(573, 305);
            this.groupBoxHistogramParameter.ResumeLayout(false);
            this.groupBoxHistogramParameter.PerformLayout();
            this.groupBoxHistogram1.ResumeLayout(false);
            this.groupBoxHistogram1.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox groupBoxHistogramParameter;
        private System.Windows.Forms.CheckBox checkBoxSharpening2;
        private System.Windows.Forms.ComboBox cbSharpening4;
        private System.Windows.Forms.Label lbSharpening4;
        private System.Windows.Forms.ComboBox cbSharpening3;
        private System.Windows.Forms.Label lbSharpening3;
        private System.Windows.Forms.ComboBox cbSharpening2;
        private System.Windows.Forms.Label lbSharpening2;
        private System.Windows.Forms.ComboBox cbSharpening1;
        private System.Windows.Forms.Label lbSharpening1;
        private System.Windows.Forms.Label lbLaplacian;
        private System.Windows.Forms.RadioButton rbMaskII;
        private System.Windows.Forms.RadioButton rbMaskI;
        private System.Windows.Forms.Button btSharpeningHelp;
        private System.Windows.Forms.Button btSharpeningCancel;
        private System.Windows.Forms.Button btSharpeningReset;
        private System.Windows.Forms.Button btSharpeningApply;
        private System.Windows.Forms.GroupBox groupBoxHistogram1;
        private System.Windows.Forms.RadioButton rbFFTSharpening;
        private System.Windows.Forms.RadioButton rbHomomorphic;
        private System.Windows.Forms.RadioButton rbHighFreqEmphasis;
        private System.Windows.Forms.RadioButton rbDCTSharpening;
        private System.Windows.Forms.RadioButton rbUnsharpMasking;
        private System.Windows.Forms.RadioButton rbHighBoost;
        private System.Windows.Forms.RadioButton rbHighpassSpatial;
        private System.Windows.Forms.RadioButton rbSharpingII;
        public System.Windows.Forms.RadioButton rbSharpingI;
        private System.Windows.Forms.GroupBox groupBoxHistogram2;
        private System.Windows.Forms.GroupBox groupBoxHistogram3;
        private System.Windows.Forms.CheckBox checkBoxSharpening1;
        private System.Windows.Forms.RadioButton rbSharpIII;
        private System.Windows.Forms.Label lblLowPercent;
        private System.Windows.Forms.Label lblHighPercent;
    }
}
