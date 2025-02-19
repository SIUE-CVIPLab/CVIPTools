namespace CVIPGUI.Compression
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
            this.rbBinToGray = new System.Windows.Forms.RadioButton();
            this.rbGrayToBin = new System.Windows.Forms.RadioButton();
            this.rbSpatialQuant = new System.Windows.Forms.RadioButton();
            this.rbGraylevelQuant = new System.Windows.Forms.RadioButton();
            this.grpPreprocessing = new System.Windows.Forms.GroupBox();
            this.grpQuant = new System.Windows.Forms.GroupBox();
            this.grpConvert = new System.Windows.Forms.GroupBox();
            this.grpParameters = new System.Windows.Forms.GroupBox();
            this.lblGrayLevels = new System.Windows.Forms.Label();
            this.cboGrayLevels = new System.Windows.Forms.ComboBox();
            this.lblType = new System.Windows.Forms.Label();
            this.rbIGS = new System.Windows.Forms.RadioButton();
            this.rbStandard = new System.Windows.Forms.RadioButton();
            this.lblMethod = new System.Windows.Forms.Label();
            this.cboMethod = new System.Windows.Forms.ComboBox();
            this.lblWidth = new System.Windows.Forms.Label();
            this.cboWidth = new System.Windows.Forms.ComboBox();
            this.lblHeight = new System.Windows.Forms.Label();
            this.cboHeight = new System.Windows.Forms.ComboBox();
            this.btnHelp = new System.Windows.Forms.Button();
            this.btnCancel = new System.Windows.Forms.Button();
            this.btnReset = new System.Windows.Forms.Button();
            this.btnApply = new System.Windows.Forms.Button();
            this.grpPreprocessing.SuspendLayout();
            this.grpParameters.SuspendLayout();
            this.SuspendLayout();
            // 
            // rbBinToGray
            // 
            this.rbBinToGray.AutoSize = true;
            this.rbBinToGray.Checked = true;
            this.rbBinToGray.Location = new System.Drawing.Point(26, 25);
            this.rbBinToGray.Name = "rbBinToGray";
            this.rbBinToGray.Size = new System.Drawing.Size(163, 17);
            this.rbBinToGray.TabIndex = 0;
            this.rbBinToGray.TabStop = true;
            this.rbBinToGray.Text = "Convert Binary To Gray Code";
            this.rbBinToGray.UseVisualStyleBackColor = true;
            this.rbBinToGray.Click += new System.EventHandler(this.rbPreprocessing_Click);
            // 
            // rbGrayToBin
            // 
            this.rbGrayToBin.AutoSize = true;
            this.rbGrayToBin.Location = new System.Drawing.Point(26, 49);
            this.rbGrayToBin.Name = "rbGrayToBin";
            this.rbGrayToBin.Size = new System.Drawing.Size(163, 17);
            this.rbGrayToBin.TabIndex = 1;
            this.rbGrayToBin.Text = "Convert Gray Code To Binary";
            this.rbGrayToBin.UseVisualStyleBackColor = true;
            this.rbGrayToBin.Click += new System.EventHandler(this.rbPreprocessing_Click);
            // 
            // rbSpatialQuant
            // 
            this.rbSpatialQuant.AutoSize = true;
            this.rbSpatialQuant.Location = new System.Drawing.Point(26, 90);
            this.rbSpatialQuant.Name = "rbSpatialQuant";
            this.rbSpatialQuant.Size = new System.Drawing.Size(119, 17);
            this.rbSpatialQuant.TabIndex = 2;
            this.rbSpatialQuant.Text = "Spatial Quantization";
            this.rbSpatialQuant.UseVisualStyleBackColor = true;
            this.rbSpatialQuant.Click += new System.EventHandler(this.rbPreprocessing_Click);
            // 
            // rbGraylevelQuant
            // 
            this.rbGraylevelQuant.AllowDrop = true;
            this.rbGraylevelQuant.AutoSize = true;
            this.rbGraylevelQuant.Location = new System.Drawing.Point(26, 114);
            this.rbGraylevelQuant.Name = "rbGraylevelQuant";
            this.rbGraylevelQuant.Size = new System.Drawing.Size(131, 17);
            this.rbGraylevelQuant.TabIndex = 3;
            this.rbGraylevelQuant.Text = "Graylevel Quantization";
            this.rbGraylevelQuant.UseVisualStyleBackColor = true;
            this.rbGraylevelQuant.Click += new System.EventHandler(this.rbPreprocessing_Click);
            // 
            // grpPreprocessing
            // 
            this.grpPreprocessing.Controls.Add(this.grpQuant);
            this.grpPreprocessing.Controls.Add(this.grpConvert);
            this.grpPreprocessing.Location = new System.Drawing.Point(5, 1);
            this.grpPreprocessing.Name = "grpPreprocessing";
            this.grpPreprocessing.Size = new System.Drawing.Size(263, 317);
            this.grpPreprocessing.TabIndex = 4;
            this.grpPreprocessing.TabStop = false;
            // 
            // grpQuant
            // 
            this.grpQuant.Location = new System.Drawing.Point(10, 75);
            this.grpQuant.Name = "grpQuant";
            this.grpQuant.Size = new System.Drawing.Size(243, 63);
            this.grpQuant.TabIndex = 1;
            this.grpQuant.TabStop = false;
            // 
            // grpConvert
            // 
            this.grpConvert.Location = new System.Drawing.Point(10, 10);
            this.grpConvert.Name = "grpConvert";
            this.grpConvert.Size = new System.Drawing.Size(243, 63);
            this.grpConvert.TabIndex = 0;
            this.grpConvert.TabStop = false;
            // 
            // grpParameters
            // 
            this.grpParameters.Controls.Add(this.lblGrayLevels);
            this.grpParameters.Controls.Add(this.cboGrayLevels);
            this.grpParameters.Controls.Add(this.lblType);
            this.grpParameters.Controls.Add(this.rbIGS);
            this.grpParameters.Controls.Add(this.rbStandard);
            this.grpParameters.Controls.Add(this.lblMethod);
            this.grpParameters.Controls.Add(this.cboMethod);
            this.grpParameters.Controls.Add(this.lblWidth);
            this.grpParameters.Controls.Add(this.cboWidth);
            this.grpParameters.Controls.Add(this.lblHeight);
            this.grpParameters.Controls.Add(this.cboHeight);
            this.grpParameters.Location = new System.Drawing.Point(275, 1);
            this.grpParameters.Name = "grpParameters";
            this.grpParameters.Size = new System.Drawing.Size(317, 317);
            this.grpParameters.TabIndex = 5;
            this.grpParameters.TabStop = false;
            this.grpParameters.Text = "Parameters";
            // 
            // lblGrayLevels
            // 
            this.lblGrayLevels.AutoSize = true;
            this.lblGrayLevels.Location = new System.Drawing.Point(15, 175);
            this.lblGrayLevels.Name = "lblGrayLevels";
            this.lblGrayLevels.Size = new System.Drawing.Size(89, 13);
            this.lblGrayLevels.TabIndex = 10;
            this.lblGrayLevels.Text = "No. of graylevels:";
            // 
            // cboGrayLevels
            // 
            this.cboGrayLevels.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cboGrayLevels.FormattingEnabled = true;
            this.cboGrayLevels.Items.AddRange(new object[] {
            "2",
            "4",
            "8",
            "16",
            "32",
            "64",
            "128"});
            this.cboGrayLevels.Location = new System.Drawing.Point(110, 171);
            this.cboGrayLevels.Name = "cboGrayLevels";
            this.cboGrayLevels.Size = new System.Drawing.Size(100, 21);
            this.cboGrayLevels.TabIndex = 9;
            this.cboGrayLevels.Text = "2";
            this.cboGrayLevels.Validating += new System.ComponentModel.CancelEventHandler(this.cboGrayLevels_Validating);
            // 
            // lblType
            // 
            this.lblType.AutoSize = true;
            this.lblType.Location = new System.Drawing.Point(70, 149);
            this.lblType.Name = "lblType";
            this.lblType.Size = new System.Drawing.Size(34, 13);
            this.lblType.TabIndex = 8;
            this.lblType.Text = "Type:";
            // 
            // rbIGS
            // 
            this.rbIGS.AutoSize = true;
            this.rbIGS.Location = new System.Drawing.Point(195, 147);
            this.rbIGS.Name = "rbIGS";
            this.rbIGS.Size = new System.Drawing.Size(43, 17);
            this.rbIGS.TabIndex = 7;
            this.rbIGS.Text = "IGS";
            this.rbIGS.UseVisualStyleBackColor = true;
            // 
            // rbStandard
            // 
            this.rbStandard.AutoSize = true;
            this.rbStandard.Checked = true;
            this.rbStandard.Location = new System.Drawing.Point(111, 147);
            this.rbStandard.Name = "rbStandard";
            this.rbStandard.Size = new System.Drawing.Size(68, 17);
            this.rbStandard.TabIndex = 6;
            this.rbStandard.TabStop = true;
            this.rbStandard.Text = "Standard";
            this.rbStandard.UseVisualStyleBackColor = true;
            // 
            // lblMethod
            // 
            this.lblMethod.AutoSize = true;
            this.lblMethod.Location = new System.Drawing.Point(58, 107);
            this.lblMethod.Name = "lblMethod";
            this.lblMethod.Size = new System.Drawing.Size(46, 13);
            this.lblMethod.TabIndex = 5;
            this.lblMethod.Text = "Method:";
            // 
            // cboMethod
            // 
            this.cboMethod.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cboMethod.FormattingEnabled = true;
            this.cboMethod.Items.AddRange(new object[] {
            "Average",
            "Median",
            "Decimation"});
            this.cboMethod.Location = new System.Drawing.Point(110, 103);
            this.cboMethod.Name = "cboMethod";
            this.cboMethod.SelectedIndex = 1;
            this.cboMethod.Size = new System.Drawing.Size(100, 21);
            this.cboMethod.TabIndex = 4;
            // 
            // lblWidth
            // 
            this.lblWidth.AutoSize = true;
            this.lblWidth.Location = new System.Drawing.Point(66, 79);
            this.lblWidth.Name = "lblWidth";
            this.lblWidth.Size = new System.Drawing.Size(38, 13);
            this.lblWidth.TabIndex = 3;
            this.lblWidth.Text = "Width:";
            // 
            // cboWidth
            // 
            this.cboWidth.FormattingEnabled = true;
            this.cboWidth.Items.AddRange(new object[] {
            "32",
            "64",
            "128",
            "256"});
            this.cboWidth.Location = new System.Drawing.Point(110, 75);
            this.cboWidth.Name = "cboWidth";
            this.cboWidth.Size = new System.Drawing.Size(100, 21);
            this.cboWidth.TabIndex = 2;
            this.cboWidth.Text = "32";
            this.cboWidth.Validating += new System.ComponentModel.CancelEventHandler(this.cboUIntVal_Validating);
            // 
            // lblHeight
            // 
            this.lblHeight.AutoSize = true;
            this.lblHeight.Location = new System.Drawing.Point(63, 51);
            this.lblHeight.Name = "lblHeight";
            this.lblHeight.Size = new System.Drawing.Size(41, 13);
            this.lblHeight.TabIndex = 1;
            this.lblHeight.Text = "Height:";
            // 
            // cboHeight
            // 
            this.cboHeight.FormattingEnabled = true;
            this.cboHeight.Items.AddRange(new object[] {
            "32",
            "64",
            "128",
            "256"});
            this.cboHeight.Location = new System.Drawing.Point(110, 47);
            this.cboHeight.Name = "cboHeight";
            this.cboHeight.Size = new System.Drawing.Size(100, 21);
            this.cboHeight.TabIndex = 0;
            this.cboHeight.Text = "32";
            this.cboHeight.Validating += new System.ComponentModel.CancelEventHandler(this.cboUIntVal_Validating);
            // 
            // btnHelp
            // 
            this.btnHelp.BackColor = System.Drawing.Color.Yellow;
            this.btnHelp.Location = new System.Drawing.Point(12, 325);
            this.btnHelp.Name = "btnHelp";
            this.btnHelp.Size = new System.Drawing.Size(60, 26);
            this.btnHelp.TabIndex = 6;
            this.btnHelp.Text = "Help";
            this.btnHelp.UseVisualStyleBackColor = false;
            this.btnHelp.Click += new System.EventHandler(this.btnHelp_Click);
            // 
            // btnCancel
            // 
            this.btnCancel.BackColor = System.Drawing.Color.OrangeRed;
            this.btnCancel.Location = new System.Drawing.Point(400, 325);
            this.btnCancel.Name = "btnCancel";
            this.btnCancel.Size = new System.Drawing.Size(60, 26);
            this.btnCancel.TabIndex = 7;
            this.btnCancel.Text = "Cancel";
            this.btnCancel.UseVisualStyleBackColor = false;
            this.btnCancel.Click += new System.EventHandler(this.btnCancel_Click);
            // 
            // btnReset
            // 
            this.btnReset.BackColor = System.Drawing.Color.CornflowerBlue;
            this.btnReset.Location = new System.Drawing.Point(466, 325);
            this.btnReset.Name = "btnReset";
            this.btnReset.Size = new System.Drawing.Size(60, 26);
            this.btnReset.TabIndex = 8;
            this.btnReset.Text = "Reset";
            this.btnReset.UseVisualStyleBackColor = false;
            this.btnReset.Click += new System.EventHandler(this.btnReset_Click);
            // 
            // btnApply
            // 
            this.btnApply.BackColor = System.Drawing.Color.LimeGreen;
            this.btnApply.ForeColor = System.Drawing.Color.White;
            this.btnApply.Location = new System.Drawing.Point(532, 325);
            this.btnApply.Name = "btnApply";
            this.btnApply.Size = new System.Drawing.Size(60, 26);
            this.btnApply.TabIndex = 9;
            this.btnApply.Text = "Apply";
            this.btnApply.UseVisualStyleBackColor = false;
            this.btnApply.Click += new System.EventHandler(this.btnApply_Click);
            // 
            // Preprocessing
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.rbBinToGray);
            this.Controls.Add(this.rbGrayToBin);
            this.Controls.Add(this.rbSpatialQuant);
            this.Controls.Add(this.rbGraylevelQuant);
            this.Controls.Add(this.grpPreprocessing);
            this.Controls.Add(this.grpParameters);
            this.Controls.Add(this.btnHelp);
            this.Controls.Add(this.btnCancel);
            this.Controls.Add(this.btnReset);
            this.Controls.Add(this.btnApply);
            this.Name = "Preprocessing";
            this.Size = new System.Drawing.Size(601, 354);
            this.grpPreprocessing.ResumeLayout(false);
            this.grpParameters.ResumeLayout(false);
            this.grpParameters.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.RadioButton rbBinToGray;
        private System.Windows.Forms.RadioButton rbGrayToBin;
        private System.Windows.Forms.RadioButton rbSpatialQuant;
        private System.Windows.Forms.RadioButton rbGraylevelQuant;
        private System.Windows.Forms.GroupBox grpPreprocessing;
        private System.Windows.Forms.GroupBox grpQuant;
        private System.Windows.Forms.GroupBox grpConvert;
        private System.Windows.Forms.GroupBox grpParameters;
        private System.Windows.Forms.Label lblGrayLevels;
        private System.Windows.Forms.ComboBox cboGrayLevels;
        private System.Windows.Forms.Label lblType;
        private System.Windows.Forms.RadioButton rbIGS;
        private System.Windows.Forms.RadioButton rbStandard;
        private System.Windows.Forms.Label lblMethod;
        private System.Windows.Forms.ComboBox cboMethod;
        private System.Windows.Forms.Label lblWidth;
        private System.Windows.Forms.ComboBox cboWidth;
        private System.Windows.Forms.Label lblHeight;
        private System.Windows.Forms.ComboBox cboHeight;
        private System.Windows.Forms.Button btnHelp;
        private System.Windows.Forms.Button btnCancel;
        private System.Windows.Forms.Button btnReset;
        private System.Windows.Forms.Button btnApply;
    }
}
