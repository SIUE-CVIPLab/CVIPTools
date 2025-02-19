namespace CVIPGUI.Restoration
{
    partial class Noise
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
            this.rbNegExponent = new System.Windows.Forms.RadioButton();
            this.rbRayleigh = new System.Windows.Forms.RadioButton();
            this.rbGaussian = new System.Windows.Forms.RadioButton();
            this.rbUniform = new System.Windows.Forms.RadioButton();
            this.rbGamma = new System.Windows.Forms.RadioButton();
            this.rbSaltPepper = new System.Windows.Forms.RadioButton();
            this.grpNoise = new System.Windows.Forms.GroupBox();
            this.grpParameters = new System.Windows.Forms.GroupBox();
            this.lblWidth = new System.Windows.Forms.Label();
            this.cboWidth = new System.Windows.Forms.ComboBox();
            this.lblHeight = new System.Windows.Forms.Label();
            this.cboHeight = new System.Windows.Forms.ComboBox();
            this.rbUseBlack = new System.Windows.Forms.RadioButton();
            this.rbUseCurrent = new System.Windows.Forms.RadioButton();
            this.lblSalt = new System.Windows.Forms.Label();
            this.cboSalt = new System.Windows.Forms.ComboBox();
            this.lblPepper = new System.Windows.Forms.Label();
            this.cboPepper = new System.Windows.Forms.ComboBox();
            this.lblAlpha = new System.Windows.Forms.Label();
            this.cboAlpha = new System.Windows.Forms.ComboBox();
            this.lblMean = new System.Windows.Forms.Label();
            this.cboMean = new System.Windows.Forms.ComboBox();
            this.lblVariance = new System.Windows.Forms.Label();
            this.cboVariance = new System.Windows.Forms.ComboBox();
            this.btnHelp = new System.Windows.Forms.Button();
            this.btnCancel = new System.Windows.Forms.Button();
            this.btnReset = new System.Windows.Forms.Button();
            this.btnApply = new System.Windows.Forms.Button();
            this.grpParameters.SuspendLayout();
            this.SuspendLayout();
            // 
            // rbNegExponent
            // 
            this.rbNegExponent.AutoSize = true;
            this.rbNegExponent.Checked = true;
            this.rbNegExponent.Location = new System.Drawing.Point(19, 22);
            this.rbNegExponent.Name = "rbNegExponent";
            this.rbNegExponent.Size = new System.Drawing.Size(126, 17);
            this.rbNegExponent.TabIndex = 0;
            this.rbNegExponent.TabStop = true;
            this.rbNegExponent.Text = "Negative Exponential";
            this.rbNegExponent.UseVisualStyleBackColor = true;
            this.rbNegExponent.Click += new System.EventHandler(this.rbNoise_Click);
            // 
            // rbRayleigh
            // 
            this.rbRayleigh.AutoSize = true;
            this.rbRayleigh.Location = new System.Drawing.Point(19, 49);
            this.rbRayleigh.Name = "rbRayleigh";
            this.rbRayleigh.Size = new System.Drawing.Size(66, 17);
            this.rbRayleigh.TabIndex = 1;
            this.rbRayleigh.Text = "Rayleigh";
            this.rbRayleigh.UseVisualStyleBackColor = true;
            this.rbRayleigh.Click += new System.EventHandler(this.rbNoise_Click);
            // 
            // rbGaussian
            // 
            this.rbGaussian.AutoSize = true;
            this.rbGaussian.Location = new System.Drawing.Point(19, 76);
            this.rbGaussian.Name = "rbGaussian";
            this.rbGaussian.Size = new System.Drawing.Size(69, 17);
            this.rbGaussian.TabIndex = 2;
            this.rbGaussian.Text = "Gaussian";
            this.rbGaussian.UseVisualStyleBackColor = true;
            this.rbGaussian.Click += new System.EventHandler(this.rbNoise_Click);
            // 
            // rbUniform
            // 
            this.rbUniform.AutoSize = true;
            this.rbUniform.Location = new System.Drawing.Point(19, 103);
            this.rbUniform.Name = "rbUniform";
            this.rbUniform.Size = new System.Drawing.Size(61, 17);
            this.rbUniform.TabIndex = 3;
            this.rbUniform.Text = "Uniform";
            this.rbUniform.UseVisualStyleBackColor = true;
            this.rbUniform.Click += new System.EventHandler(this.rbNoise_Click);
            // 
            // rbGamma
            // 
            this.rbGamma.AutoSize = true;
            this.rbGamma.Location = new System.Drawing.Point(19, 130);
            this.rbGamma.Name = "rbGamma";
            this.rbGamma.Size = new System.Drawing.Size(61, 17);
            this.rbGamma.TabIndex = 4;
            this.rbGamma.Text = "Gamma";
            this.rbGamma.UseVisualStyleBackColor = true;
            this.rbGamma.Click += new System.EventHandler(this.rbNoise_Click);
            // 
            // rbSaltPepper
            // 
            this.rbSaltPepper.AutoSize = true;
            this.rbSaltPepper.Location = new System.Drawing.Point(19, 157);
            this.rbSaltPepper.Name = "rbSaltPepper";
            this.rbSaltPepper.Size = new System.Drawing.Size(101, 17);
            this.rbSaltPepper.TabIndex = 5;
            this.rbSaltPepper.Text = "Salt and Pepper";
            this.rbSaltPepper.UseVisualStyleBackColor = true;
            this.rbSaltPepper.Click += new System.EventHandler(this.rbNoise_Click);
            // 
            // grpNoise
            // 
            this.grpNoise.Location = new System.Drawing.Point(5, 2);
            this.grpNoise.Name = "grpNoise";
            this.grpNoise.Size = new System.Drawing.Size(215, 456);
            this.grpNoise.TabIndex = 6;
            this.grpNoise.TabStop = false;
            // 
            // grpParameters
            // 
            this.grpParameters.Controls.Add(this.lblWidth);
            this.grpParameters.Controls.Add(this.cboWidth);
            this.grpParameters.Controls.Add(this.lblHeight);
            this.grpParameters.Controls.Add(this.cboHeight);
            this.grpParameters.Controls.Add(this.rbUseBlack);
            this.grpParameters.Controls.Add(this.rbUseCurrent);
            this.grpParameters.Controls.Add(this.lblSalt);
            this.grpParameters.Controls.Add(this.cboSalt);
            this.grpParameters.Controls.Add(this.lblPepper);
            this.grpParameters.Controls.Add(this.cboPepper);
            this.grpParameters.Controls.Add(this.lblAlpha);
            this.grpParameters.Controls.Add(this.cboAlpha);
            this.grpParameters.Controls.Add(this.lblMean);
            this.grpParameters.Controls.Add(this.cboMean);
            this.grpParameters.Controls.Add(this.lblVariance);
            this.grpParameters.Controls.Add(this.cboVariance);
            this.grpParameters.Location = new System.Drawing.Point(226, 2);
            this.grpParameters.Name = "grpParameters";
            this.grpParameters.Size = new System.Drawing.Size(370, 456);
            this.grpParameters.TabIndex = 7;
            this.grpParameters.TabStop = false;
            this.grpParameters.Text = "Parameters";
            // 
            // lblWidth
            // 
            this.lblWidth.AutoSize = true;
            this.lblWidth.Location = new System.Drawing.Point(51, 325);
            this.lblWidth.Name = "lblWidth";
            this.lblWidth.Size = new System.Drawing.Size(35, 13);
            this.lblWidth.TabIndex = 15;
            this.lblWidth.Text = "Width";
            // 
            // cboWidth
            // 
            this.cboWidth.FormattingEnabled = true;
            this.cboWidth.Items.AddRange(new object[] {
            "32",
            "64",
            "128",
            "256",
            "512"});
            this.cboWidth.Location = new System.Drawing.Point(128, 321);
            this.cboWidth.Name = "cboWidth";
            this.cboWidth.Size = new System.Drawing.Size(123, 21);
            this.cboWidth.TabIndex = 14;
            this.cboWidth.Text = "256";
            this.cboWidth.Validating += new System.ComponentModel.CancelEventHandler(this.cboIntVal_Validating);
            // 
            // lblHeight
            // 
            this.lblHeight.AutoSize = true;
            this.lblHeight.Location = new System.Drawing.Point(51, 298);
            this.lblHeight.Name = "lblHeight";
            this.lblHeight.Size = new System.Drawing.Size(38, 13);
            this.lblHeight.TabIndex = 13;
            this.lblHeight.Text = "Height";
            // 
            // cboHeight
            // 
            this.cboHeight.FormattingEnabled = true;
            this.cboHeight.Items.AddRange(new object[] {
            "32",
            "64",
            "128",
            "256",
            "512"});
            this.cboHeight.Location = new System.Drawing.Point(128, 294);
            this.cboHeight.Name = "cboHeight";
            this.cboHeight.Size = new System.Drawing.Size(123, 21);
            this.cboHeight.TabIndex = 12;
            this.cboHeight.Text = "256";
            this.cboHeight.Validating += new System.ComponentModel.CancelEventHandler(this.cboIntVal_Validating);
            // 
            // rbUseBlack
            // 
            this.rbUseBlack.AutoSize = true;
            this.rbUseBlack.Location = new System.Drawing.Point(19, 266);
            this.rbUseBlack.Name = "rbUseBlack";
            this.rbUseBlack.Size = new System.Drawing.Size(104, 17);
            this.rbUseBlack.TabIndex = 11;
            this.rbUseBlack.Text = "Use black image";
            this.rbUseBlack.UseVisualStyleBackColor = true;
            this.rbUseBlack.Click += new System.EventHandler(this.rbUseCurrent_Click);
            // 
            // rbUseCurrent
            // 
            this.rbUseCurrent.AutoSize = true;
            this.rbUseCurrent.Checked = true;
            this.rbUseCurrent.Location = new System.Drawing.Point(19, 244);
            this.rbUseCurrent.Name = "rbUseCurrent";
            this.rbUseCurrent.Size = new System.Drawing.Size(111, 17);
            this.rbUseCurrent.TabIndex = 10;
            this.rbUseCurrent.TabStop = true;
            this.rbUseCurrent.Text = "Use current image";
            this.rbUseCurrent.UseVisualStyleBackColor = true;
            this.rbUseCurrent.Click += new System.EventHandler(this.rbUseCurrent_Click);
            // 
            // lblSalt
            // 
            this.lblSalt.AutoSize = true;
            this.lblSalt.Location = new System.Drawing.Point(15, 177);
            this.lblSalt.Name = "lblSalt";
            this.lblSalt.Size = new System.Drawing.Size(88, 13);
            this.lblSalt.TabIndex = 9;
            this.lblSalt.Text = "Probability of Salt";
            // 
            // cboSalt
            // 
            this.cboSalt.FormattingEnabled = true;
            this.cboSalt.Items.AddRange(new object[] {
            "0.02",
            "0.03",
            "0.05",
            "0.08",
            "0.10",
            "0.15",
            "0.20"});
            this.cboSalt.Location = new System.Drawing.Point(127, 173);
            this.cboSalt.Name = "cboSalt";
            this.cboSalt.Size = new System.Drawing.Size(123, 21);
            this.cboSalt.TabIndex = 8;
            this.cboSalt.Text = "0.03";
            this.cboSalt.Validating += new System.ComponentModel.CancelEventHandler(this.cboDoubleVal_Validating);
            // 
            // lblPepper
            // 
            this.lblPepper.AutoSize = true;
            this.lblPepper.Location = new System.Drawing.Point(15, 148);
            this.lblPepper.Name = "lblPepper";
            this.lblPepper.Size = new System.Drawing.Size(104, 13);
            this.lblPepper.TabIndex = 7;
            this.lblPepper.Text = "Probability of Pepper";
            // 
            // cboPepper
            // 
            this.cboPepper.FormattingEnabled = true;
            this.cboPepper.Items.AddRange(new object[] {
            "0.02",
            "0.03",
            "0.05",
            "0.08",
            "0.10",
            "0.15",
            "0.20"});
            this.cboPepper.Location = new System.Drawing.Point(127, 144);
            this.cboPepper.Name = "cboPepper";
            this.cboPepper.Size = new System.Drawing.Size(123, 21);
            this.cboPepper.TabIndex = 6;
            this.cboPepper.Text = "0.03";
            this.cboPepper.Validating += new System.ComponentModel.CancelEventHandler(this.cboDoubleVal_Validating);
            // 
            // lblAlpha
            // 
            this.lblAlpha.AutoSize = true;
            this.lblAlpha.Location = new System.Drawing.Point(15, 119);
            this.lblAlpha.Name = "lblAlpha";
            this.lblAlpha.Size = new System.Drawing.Size(34, 13);
            this.lblAlpha.TabIndex = 5;
            this.lblAlpha.Text = "Alpha";
            // 
            // cboAlpha
            // 
            this.cboAlpha.FormattingEnabled = true;
            this.cboAlpha.Items.AddRange(new object[] {
            "1",
            "2",
            "3",
            "4",
            "5"});
            this.cboAlpha.Location = new System.Drawing.Point(127, 115);
            this.cboAlpha.Name = "cboAlpha";
            this.cboAlpha.Size = new System.Drawing.Size(123, 21);
            this.cboAlpha.TabIndex = 4;
            this.cboAlpha.Text = "3";
            this.cboAlpha.Validating += new System.ComponentModel.CancelEventHandler(this.cboIntVal_Validating);
            // 
            // lblMean
            // 
            this.lblMean.AutoSize = true;
            this.lblMean.Location = new System.Drawing.Point(15, 90);
            this.lblMean.Name = "lblMean";
            this.lblMean.Size = new System.Drawing.Size(34, 13);
            this.lblMean.TabIndex = 3;
            this.lblMean.Text = "Mean";
            // 
            // cboMean
            // 
            this.cboMean.FormattingEnabled = true;
            this.cboMean.Items.AddRange(new object[] {
            "-20.0",
            "-10.0",
            "0.0",
            "10.0",
            "20.0"});
            this.cboMean.Location = new System.Drawing.Point(127, 86);
            this.cboMean.Name = "cboMean";
            this.cboMean.Size = new System.Drawing.Size(123, 21);
            this.cboMean.TabIndex = 2;
            this.cboMean.Text = "0.0";
            this.cboMean.Validating += new System.ComponentModel.CancelEventHandler(this.cboDoubleVal_Validating);
            // 
            // lblVariance
            // 
            this.lblVariance.AutoSize = true;
            this.lblVariance.Location = new System.Drawing.Point(15, 61);
            this.lblVariance.Name = "lblVariance";
            this.lblVariance.Size = new System.Drawing.Size(49, 13);
            this.lblVariance.TabIndex = 1;
            this.lblVariance.Text = "Variance";
            // 
            // cboVariance
            // 
            this.cboVariance.FormattingEnabled = true;
            this.cboVariance.Items.AddRange(new object[] {
            "100.0",
            "200.0",
            "300.0",
            "400.0",
            "500.0",
            "600.0",
            "700.0",
            "800.0"});
            this.cboVariance.Location = new System.Drawing.Point(127, 57);
            this.cboVariance.Name = "cboVariance";
            this.cboVariance.Size = new System.Drawing.Size(123, 21);
            this.cboVariance.TabIndex = 0;
            this.cboVariance.Text = "100.0";
            this.cboVariance.Validating += new System.ComponentModel.CancelEventHandler(this.cboDoubleVal_Validating);
            // 
            // btnHelp
            // 
            this.btnHelp.BackColor = System.Drawing.Color.Yellow;
            this.btnHelp.Location = new System.Drawing.Point(12, 466);
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
            this.btnCancel.Location = new System.Drawing.Point(402, 466);
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
            this.btnReset.Location = new System.Drawing.Point(468, 466);
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
            this.btnApply.Location = new System.Drawing.Point(534, 466);
            this.btnApply.Name = "btnApply";
            this.btnApply.Size = new System.Drawing.Size(60, 26);
            this.btnApply.TabIndex = 11;
            this.btnApply.Text = "Apply";
            this.btnApply.UseVisualStyleBackColor = false;
            this.btnApply.Click += new System.EventHandler(this.btnApply_Click);
            // 
            // Noise
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.rbNegExponent);
            this.Controls.Add(this.rbRayleigh);
            this.Controls.Add(this.rbGaussian);
            this.Controls.Add(this.rbUniform);
            this.Controls.Add(this.rbGamma);
            this.Controls.Add(this.rbSaltPepper);
            this.Controls.Add(this.grpNoise);
            this.Controls.Add(this.grpParameters);
            this.Controls.Add(this.btnHelp);
            this.Controls.Add(this.btnCancel);
            this.Controls.Add(this.btnReset);
            this.Controls.Add(this.btnApply);
            this.Name = "Noise";
            this.Size = new System.Drawing.Size(600, 495);
            this.grpParameters.ResumeLayout(false);
            this.grpParameters.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.RadioButton rbNegExponent;
        private System.Windows.Forms.RadioButton rbRayleigh;
        private System.Windows.Forms.RadioButton rbGaussian;
        private System.Windows.Forms.RadioButton rbUniform;
        private System.Windows.Forms.RadioButton rbGamma;
        private System.Windows.Forms.RadioButton rbSaltPepper;
        private System.Windows.Forms.GroupBox grpNoise;
        private System.Windows.Forms.GroupBox grpParameters;
        private System.Windows.Forms.Label lblWidth;
        private System.Windows.Forms.ComboBox cboWidth;
        private System.Windows.Forms.Label lblHeight;
        private System.Windows.Forms.ComboBox cboHeight;
        private System.Windows.Forms.RadioButton rbUseBlack;
        private System.Windows.Forms.RadioButton rbUseCurrent;
        private System.Windows.Forms.Label lblSalt;
        private System.Windows.Forms.ComboBox cboSalt;
        private System.Windows.Forms.Label lblPepper;
        private System.Windows.Forms.ComboBox cboPepper;
        private System.Windows.Forms.Label lblAlpha;
        private System.Windows.Forms.ComboBox cboAlpha;
        private System.Windows.Forms.Label lblMean;
        private System.Windows.Forms.ComboBox cboMean;
        private System.Windows.Forms.Label lblVariance;
        private System.Windows.Forms.ComboBox cboVariance;
        private System.Windows.Forms.Button btnHelp;
        private System.Windows.Forms.Button btnCancel;
        private System.Windows.Forms.Button btnReset;
        private System.Windows.Forms.Button btnApply;
    }
}
