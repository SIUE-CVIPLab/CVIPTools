namespace CVIPGUI.Utilities
{
    partial class UtilSize
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
            this.grpSize = new System.Windows.Forms.GroupBox();
            this.lblCurrentImage = new System.Windows.Forms.Label();
            this.txtCurrentImage = new System.Windows.Forms.Label();
            this.pnlCrop = new System.Windows.Forms.Panel();
            this.lblCropHeight = new System.Windows.Forms.Label();
            this.cboCropHeight = new System.Windows.Forms.ComboBox();
            this.lblCropWidth = new System.Windows.Forms.Label();
            this.cboCropWidth = new System.Windows.Forms.ComboBox();
            this.lblCropRow = new System.Windows.Forms.Label();
            this.cboCropRow = new System.Windows.Forms.ComboBox();
            this.lblCropCol = new System.Windows.Forms.Label();
            this.cboCropCol = new System.Windows.Forms.ComboBox();
            this.pnlResize = new System.Windows.Forms.Panel();
            this.rbLinearInterp = new System.Windows.Forms.RadioButton();
            this.rbZeroOrderHold = new System.Windows.Forms.RadioButton();
            this.lblResizeMethod = new System.Windows.Forms.Label();
            this.lblResizeHeight = new System.Windows.Forms.Label();
            this.cboResizeHeight = new System.Windows.Forms.ComboBox();
            this.lblResizeWidth = new System.Windows.Forms.Label();
            this.cboResizeWidth = new System.Windows.Forms.ComboBox();
            this.pnlSpatialQuant = new System.Windows.Forms.Panel();
            this.lblSpatialQuantMethod = new System.Windows.Forms.Label();
            this.cboSpatialQuantMethod = new System.Windows.Forms.ComboBox();
            this.lblSpatialQuantHeight = new System.Windows.Forms.Label();
            this.cboSpatialQuantHeight = new System.Windows.Forms.ComboBox();
            this.lblSpatialQuantWidth = new System.Windows.Forms.Label();
            this.cboSpatialQuantWidth = new System.Windows.Forms.ComboBox();
            this.btnHelp = new System.Windows.Forms.Button();
            this.btnCancel = new System.Windows.Forms.Button();
            this.btnReset = new System.Windows.Forms.Button();
            this.btnApply = new System.Windows.Forms.Button();
            this.grpSize.SuspendLayout();
            this.pnlCrop.SuspendLayout();
            this.pnlResize.SuspendLayout();
            this.pnlSpatialQuant.SuspendLayout();
            this.SuspendLayout();
            // 
            // grpSize
            // 
            this.grpSize.Controls.Add(this.lblCurrentImage);
            this.grpSize.Controls.Add(this.txtCurrentImage);
            this.grpSize.Location = new System.Drawing.Point(1, -12);
            this.grpSize.Margin = new System.Windows.Forms.Padding(4);
            this.grpSize.Name = "grpSize";
            this.grpSize.Padding = new System.Windows.Forms.Padding(4);
            this.grpSize.Size = new System.Drawing.Size(573, 132);
            this.grpSize.TabIndex = 0;
            this.grpSize.TabStop = false;
            this.grpSize.Enter += new System.EventHandler(this.grpSize_Enter);
            // 
            // lblCurrentImage
            // 
            this.lblCurrentImage.AutoSize = true;
            this.lblCurrentImage.Location = new System.Drawing.Point(7, 14);
            this.lblCurrentImage.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lblCurrentImage.Name = "lblCurrentImage";
            this.lblCurrentImage.Size = new System.Drawing.Size(97, 17);
            this.lblCurrentImage.TabIndex = 1;
            this.lblCurrentImage.Text = "Current Image";
            // 
            // txtCurrentImage
            // 
            this.txtCurrentImage.AutoSize = true;
            this.txtCurrentImage.ForeColor = System.Drawing.Color.Purple;
            this.txtCurrentImage.Location = new System.Drawing.Point(107, 14);
            this.txtCurrentImage.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.txtCurrentImage.Name = "txtCurrentImage";
            this.txtCurrentImage.Size = new System.Drawing.Size(0, 17);
            this.txtCurrentImage.TabIndex = 0;
            // 
            // pnlCrop
            // 
            this.pnlCrop.Controls.Add(this.lblCropHeight);
            this.pnlCrop.Controls.Add(this.cboCropHeight);
            this.pnlCrop.Controls.Add(this.lblCropWidth);
            this.pnlCrop.Controls.Add(this.cboCropWidth);
            this.pnlCrop.Controls.Add(this.lblCropRow);
            this.pnlCrop.Controls.Add(this.cboCropRow);
            this.pnlCrop.Controls.Add(this.lblCropCol);
            this.pnlCrop.Controls.Add(this.cboCropCol);
            this.pnlCrop.Location = new System.Drawing.Point(15, 174);
            this.pnlCrop.Margin = new System.Windows.Forms.Padding(4);
            this.pnlCrop.Name = "pnlCrop";
            this.pnlCrop.Size = new System.Drawing.Size(560, 92);
            this.pnlCrop.TabIndex = 1;
            // 
            // lblCropHeight
            // 
            this.lblCropHeight.AutoSize = true;
            this.lblCropHeight.Location = new System.Drawing.Point(332, 47);
            this.lblCropHeight.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lblCropHeight.Name = "lblCropHeight";
            this.lblCropHeight.Size = new System.Drawing.Size(75, 17);
            this.lblCropHeight.TabIndex = 7;
            this.lblCropHeight.Text = "and height";
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
            this.cboCropHeight.Location = new System.Drawing.Point(411, 42);
            this.cboCropHeight.Margin = new System.Windows.Forms.Padding(4);
            this.cboCropHeight.Name = "cboCropHeight";
            this.cboCropHeight.Size = new System.Drawing.Size(64, 24);
            this.cboCropHeight.TabIndex = 6;
            this.cboCropHeight.Text = "100";
            this.cboCropHeight.Validating += new System.ComponentModel.CancelEventHandler(this.cboIntVal_Validating);
            // 
            // lblCropWidth
            // 
            this.lblCropWidth.AutoSize = true;
            this.lblCropWidth.Location = new System.Drawing.Point(184, 47);
            this.lblCropWidth.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lblCropWidth.Name = "lblCropWidth";
            this.lblCropWidth.Size = new System.Drawing.Size(68, 17);
            this.lblCropWidth.TabIndex = 5;
            this.lblCropWidth.Text = "with width";
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
            this.cboCropWidth.Location = new System.Drawing.Point(259, 42);
            this.cboCropWidth.Margin = new System.Windows.Forms.Padding(4);
            this.cboCropWidth.Name = "cboCropWidth";
            this.cboCropWidth.Size = new System.Drawing.Size(64, 24);
            this.cboCropWidth.TabIndex = 4;
            this.cboCropWidth.Text = "100";
            this.cboCropWidth.Validating += new System.ComponentModel.CancelEventHandler(this.cboIntVal_Validating);
            // 
            // lblCropRow
            // 
            this.lblCropRow.AutoSize = true;
            this.lblCropRow.Location = new System.Drawing.Point(332, 11);
            this.lblCropRow.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lblCropRow.Name = "lblCropRow";
            this.lblCropRow.Size = new System.Drawing.Size(58, 17);
            this.lblCropRow.TabIndex = 3;
            this.lblCropRow.Text = "and row";
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
            this.cboCropRow.Location = new System.Drawing.Point(411, 6);
            this.cboCropRow.Margin = new System.Windows.Forms.Padding(4);
            this.cboCropRow.Name = "cboCropRow";
            this.cboCropRow.Size = new System.Drawing.Size(64, 24);
            this.cboCropRow.TabIndex = 2;
            this.cboCropRow.Text = "0";
            this.cboCropRow.Validating += new System.ComponentModel.CancelEventHandler(this.cboIntVal_Validating);
            // 
            // lblCropCol
            // 
            this.lblCropCol.AutoSize = true;
            this.lblCropCol.Location = new System.Drawing.Point(4, 11);
            this.lblCropCol.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lblCropCol.Name = "lblCropCol";
            this.lblCropCol.Size = new System.Drawing.Size(252, 17);
            this.lblCropCol.TabIndex = 1;
            this.lblCropCol.Text = "Crop from Upper-Left corner at column";
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
            this.cboCropCol.Location = new System.Drawing.Point(259, 6);
            this.cboCropCol.Margin = new System.Windows.Forms.Padding(4);
            this.cboCropCol.Name = "cboCropCol";
            this.cboCropCol.Size = new System.Drawing.Size(64, 24);
            this.cboCropCol.TabIndex = 0;
            this.cboCropCol.Text = "0";
            this.cboCropCol.Validating += new System.ComponentModel.CancelEventHandler(this.cboIntVal_Validating);
            // 
            // pnlResize
            // 
            this.pnlResize.Controls.Add(this.rbLinearInterp);
            this.pnlResize.Controls.Add(this.rbZeroOrderHold);
            this.pnlResize.Controls.Add(this.lblResizeMethod);
            this.pnlResize.Controls.Add(this.lblResizeHeight);
            this.pnlResize.Controls.Add(this.cboResizeHeight);
            this.pnlResize.Controls.Add(this.lblResizeWidth);
            this.pnlResize.Controls.Add(this.cboResizeWidth);
            this.pnlResize.Location = new System.Drawing.Point(15, 273);
            this.pnlResize.Margin = new System.Windows.Forms.Padding(4);
            this.pnlResize.Name = "pnlResize";
            this.pnlResize.Size = new System.Drawing.Size(560, 92);
            this.pnlResize.TabIndex = 2;
            // 
            // rbLinearInterp
            // 
            this.rbLinearInterp.AutoSize = true;
            this.rbLinearInterp.Location = new System.Drawing.Point(205, 44);
            this.rbLinearInterp.Margin = new System.Windows.Forms.Padding(4);
            this.rbLinearInterp.Name = "rbLinearInterp";
            this.rbLinearInterp.Size = new System.Drawing.Size(151, 21);
            this.rbLinearInterp.TabIndex = 6;
            this.rbLinearInterp.Text = "Linear interpolation";
            this.rbLinearInterp.UseVisualStyleBackColor = true;
            // 
            // rbZeroOrderHold
            // 
            this.rbZeroOrderHold.AutoSize = true;
            this.rbZeroOrderHold.Checked = true;
            this.rbZeroOrderHold.Location = new System.Drawing.Point(65, 44);
            this.rbZeroOrderHold.Margin = new System.Windows.Forms.Padding(4);
            this.rbZeroOrderHold.Name = "rbZeroOrderHold";
            this.rbZeroOrderHold.Size = new System.Drawing.Size(128, 21);
            this.rbZeroOrderHold.TabIndex = 5;
            this.rbZeroOrderHold.TabStop = true;
            this.rbZeroOrderHold.Text = "Zero order hold";
            this.rbZeroOrderHold.UseVisualStyleBackColor = true;
            // 
            // lblResizeMethod
            // 
            this.lblResizeMethod.AutoSize = true;
            this.lblResizeMethod.Location = new System.Drawing.Point(12, 47);
            this.lblResizeMethod.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lblResizeMethod.Name = "lblResizeMethod";
            this.lblResizeMethod.Size = new System.Drawing.Size(44, 17);
            this.lblResizeMethod.TabIndex = 4;
            this.lblResizeMethod.Text = "Using";
            // 
            // lblResizeHeight
            // 
            this.lblResizeHeight.AutoSize = true;
            this.lblResizeHeight.Location = new System.Drawing.Point(248, 12);
            this.lblResizeHeight.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lblResizeHeight.Name = "lblResizeHeight";
            this.lblResizeHeight.Size = new System.Drawing.Size(75, 17);
            this.lblResizeHeight.TabIndex = 3;
            this.lblResizeHeight.Text = "and height";
            // 
            // cboResizeHeight
            // 
            this.cboResizeHeight.FormattingEnabled = true;
            this.cboResizeHeight.Items.AddRange(new object[] {
            "8",
            "16",
            "32",
            "64",
            "128",
            "256",
            "512",
            "1024"});
            this.cboResizeHeight.Location = new System.Drawing.Point(325, 7);
            this.cboResizeHeight.Margin = new System.Windows.Forms.Padding(4);
            this.cboResizeHeight.Name = "cboResizeHeight";
            this.cboResizeHeight.Size = new System.Drawing.Size(64, 24);
            this.cboResizeHeight.TabIndex = 2;
            this.cboResizeHeight.Text = "256";
            this.cboResizeHeight.Validating += new System.ComponentModel.CancelEventHandler(this.cboIntVal_Validating);
            // 
            // lblResizeWidth
            // 
            this.lblResizeWidth.AutoSize = true;
            this.lblResizeWidth.Location = new System.Drawing.Point(4, 12);
            this.lblResizeWidth.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lblResizeWidth.Name = "lblResizeWidth";
            this.lblResizeWidth.Size = new System.Drawing.Size(169, 17);
            this.lblResizeWidth.TabIndex = 1;
            this.lblResizeWidth.Text = "Resize the image to width";
            // 
            // cboResizeWidth
            // 
            this.cboResizeWidth.FormattingEnabled = true;
            this.cboResizeWidth.Items.AddRange(new object[] {
            "8",
            "16",
            "32",
            "64",
            "128",
            "256",
            "512",
            "1024"});
            this.cboResizeWidth.Location = new System.Drawing.Point(177, 7);
            this.cboResizeWidth.Margin = new System.Windows.Forms.Padding(4);
            this.cboResizeWidth.Name = "cboResizeWidth";
            this.cboResizeWidth.Size = new System.Drawing.Size(64, 24);
            this.cboResizeWidth.TabIndex = 0;
            this.cboResizeWidth.Text = "256";
            this.cboResizeWidth.Validating += new System.ComponentModel.CancelEventHandler(this.cboIntVal_Validating);
            // 
            // pnlSpatialQuant
            // 
            this.pnlSpatialQuant.Controls.Add(this.lblSpatialQuantMethod);
            this.pnlSpatialQuant.Controls.Add(this.cboSpatialQuantMethod);
            this.pnlSpatialQuant.Controls.Add(this.lblSpatialQuantHeight);
            this.pnlSpatialQuant.Controls.Add(this.cboSpatialQuantHeight);
            this.pnlSpatialQuant.Controls.Add(this.lblSpatialQuantWidth);
            this.pnlSpatialQuant.Controls.Add(this.cboSpatialQuantWidth);
            this.pnlSpatialQuant.Location = new System.Drawing.Point(15, 373);
            this.pnlSpatialQuant.Margin = new System.Windows.Forms.Padding(4);
            this.pnlSpatialQuant.Name = "pnlSpatialQuant";
            this.pnlSpatialQuant.Size = new System.Drawing.Size(560, 92);
            this.pnlSpatialQuant.TabIndex = 3;
            // 
            // lblSpatialQuantMethod
            // 
            this.lblSpatialQuantMethod.AutoSize = true;
            this.lblSpatialQuantMethod.Location = new System.Drawing.Point(4, 48);
            this.lblSpatialQuantMethod.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lblSpatialQuantMethod.Name = "lblSpatialQuantMethod";
            this.lblSpatialQuantMethod.Size = new System.Drawing.Size(95, 17);
            this.lblSpatialQuantMethod.TabIndex = 5;
            this.lblSpatialQuantMethod.Text = "Using method";
            // 
            // cboSpatialQuantMethod
            // 
            this.cboSpatialQuantMethod.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cboSpatialQuantMethod.FormattingEnabled = true;
            this.cboSpatialQuantMethod.Items.AddRange(new object[] {
            "Average value",
            "Median value",
            "Decimation"});
            this.cboSpatialQuantMethod.SelectedIndex = 1;
            this.cboSpatialQuantMethod.Location = new System.Drawing.Point(104, 43);
            this.cboSpatialQuantMethod.Margin = new System.Windows.Forms.Padding(4);
            this.cboSpatialQuantMethod.Name = "cboSpatialQuantMethod";
            this.cboSpatialQuantMethod.Size = new System.Drawing.Size(175, 24);
            this.cboSpatialQuantMethod.TabIndex = 4;
            // 
            // lblSpatialQuantHeight
            // 
            this.lblSpatialQuantHeight.AutoSize = true;
            this.lblSpatialQuantHeight.Location = new System.Drawing.Point(144, 12);
            this.lblSpatialQuantHeight.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lblSpatialQuantHeight.Name = "lblSpatialQuantHeight";
            this.lblSpatialQuantHeight.Size = new System.Drawing.Size(75, 17);
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
            this.cboSpatialQuantHeight.Location = new System.Drawing.Point(221, 7);
            this.cboSpatialQuantHeight.Margin = new System.Windows.Forms.Padding(4);
            this.cboSpatialQuantHeight.Name = "cboSpatialQuantHeight";
            this.cboSpatialQuantHeight.Size = new System.Drawing.Size(64, 24);
            this.cboSpatialQuantHeight.TabIndex = 2;
            this.cboSpatialQuantHeight.Text = "32";
            this.cboSpatialQuantHeight.Validating += new System.ComponentModel.CancelEventHandler(this.cboIntVal_Validating);
            // 
            // lblSpatialQuantWidth
            // 
            this.lblSpatialQuantWidth.AutoSize = true;
            this.lblSpatialQuantWidth.Location = new System.Drawing.Point(4, 12);
            this.lblSpatialQuantWidth.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lblSpatialQuantWidth.Name = "lblSpatialQuantWidth";
            this.lblSpatialQuantWidth.Size = new System.Drawing.Size(61, 17);
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
            this.cboSpatialQuantWidth.Location = new System.Drawing.Point(71, 7);
            this.cboSpatialQuantWidth.Margin = new System.Windows.Forms.Padding(4);
            this.cboSpatialQuantWidth.Name = "cboSpatialQuantWidth";
            this.cboSpatialQuantWidth.Size = new System.Drawing.Size(64, 24);
            this.cboSpatialQuantWidth.TabIndex = 0;
            this.cboSpatialQuantWidth.Text = "32";
            this.cboSpatialQuantWidth.Validating += new System.ComponentModel.CancelEventHandler(this.cboIntVal_Validating);
            // 
            // btnHelp
            // 
            this.btnHelp.BackColor = System.Drawing.Color.Yellow;
            this.btnHelp.Location = new System.Drawing.Point(3, 134);
            this.btnHelp.Margin = new System.Windows.Forms.Padding(4);
            this.btnHelp.Name = "btnHelp";
            this.btnHelp.Size = new System.Drawing.Size(80, 32);
            this.btnHelp.TabIndex = 4;
            this.btnHelp.Text = "Help";
            this.btnHelp.UseVisualStyleBackColor = false;
            this.btnHelp.Click += new System.EventHandler(this.btnHelp_Click);
            // 
            // btnCancel
            // 
            this.btnCancel.BackColor = System.Drawing.Color.OrangeRed;
            this.btnCancel.CausesValidation = false;
            this.btnCancel.Location = new System.Drawing.Point(317, 134);
            this.btnCancel.Margin = new System.Windows.Forms.Padding(4);
            this.btnCancel.Name = "btnCancel";
            this.btnCancel.Size = new System.Drawing.Size(80, 32);
            this.btnCancel.TabIndex = 5;
            this.btnCancel.Text = "Cancel";
            this.btnCancel.UseVisualStyleBackColor = false;
            this.btnCancel.Click += new System.EventHandler(this.btnCancel_Click);
            // 
            // btnReset
            // 
            this.btnReset.BackColor = System.Drawing.Color.CornflowerBlue;
            this.btnReset.CausesValidation = false;
            this.btnReset.Location = new System.Drawing.Point(405, 134);
            this.btnReset.Margin = new System.Windows.Forms.Padding(4);
            this.btnReset.Name = "btnReset";
            this.btnReset.Size = new System.Drawing.Size(80, 32);
            this.btnReset.TabIndex = 6;
            this.btnReset.Text = "Reset";
            this.btnReset.UseVisualStyleBackColor = false;
            this.btnReset.Click += new System.EventHandler(this.btnReset_Click);
            // 
            // btnApply
            // 
            this.btnApply.BackColor = System.Drawing.Color.LimeGreen;
            this.btnApply.ForeColor = System.Drawing.Color.White;
            this.btnApply.Location = new System.Drawing.Point(493, 134);
            this.btnApply.Margin = new System.Windows.Forms.Padding(4);
            this.btnApply.Name = "btnApply";
            this.btnApply.Size = new System.Drawing.Size(80, 32);
            this.btnApply.TabIndex = 7;
            this.btnApply.Text = "Apply";
            this.btnApply.UseVisualStyleBackColor = false;
            this.btnApply.Click += new System.EventHandler(this.btnApply_Click);
            // 
            // UtilSize
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.CausesValidation = false;
            this.Controls.Add(this.pnlSpatialQuant);
            this.Controls.Add(this.pnlResize);
            this.Controls.Add(this.pnlCrop);
            this.Controls.Add(this.grpSize);
            this.Controls.Add(this.btnHelp);
            this.Controls.Add(this.btnCancel);
            this.Controls.Add(this.btnReset);
            this.Controls.Add(this.btnApply);
            this.Margin = new System.Windows.Forms.Padding(4);
            this.Name = "UtilSize";
            this.Size = new System.Drawing.Size(588, 482);
            this.grpSize.ResumeLayout(false);
            this.grpSize.PerformLayout();
            this.pnlCrop.ResumeLayout(false);
            this.pnlCrop.PerformLayout();
            this.pnlResize.ResumeLayout(false);
            this.pnlResize.PerformLayout();
            this.pnlSpatialQuant.ResumeLayout(false);
            this.pnlSpatialQuant.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox grpSize;
        private System.Windows.Forms.Label lblCurrentImage;
        private System.Windows.Forms.Label txtCurrentImage;
        private System.Windows.Forms.Panel pnlCrop;
        private System.Windows.Forms.Label lblCropHeight;
        private System.Windows.Forms.ComboBox cboCropHeight;
        private System.Windows.Forms.Label lblCropWidth;
        private System.Windows.Forms.ComboBox cboCropWidth;
        private System.Windows.Forms.Label lblCropRow;
        private System.Windows.Forms.ComboBox cboCropRow;
        private System.Windows.Forms.Label lblCropCol;
        private System.Windows.Forms.ComboBox cboCropCol;
        private System.Windows.Forms.Panel pnlResize;
        private System.Windows.Forms.RadioButton rbLinearInterp;
        private System.Windows.Forms.RadioButton rbZeroOrderHold;
        private System.Windows.Forms.Label lblResizeMethod;
        private System.Windows.Forms.Label lblResizeHeight;
        private System.Windows.Forms.ComboBox cboResizeHeight;
        private System.Windows.Forms.Label lblResizeWidth;
        private System.Windows.Forms.ComboBox cboResizeWidth;
        private System.Windows.Forms.Panel pnlSpatialQuant;
        private System.Windows.Forms.Label lblSpatialQuantMethod;
        private System.Windows.Forms.ComboBox cboSpatialQuantMethod;
        private System.Windows.Forms.Label lblSpatialQuantHeight;
        private System.Windows.Forms.ComboBox cboSpatialQuantHeight;
        private System.Windows.Forms.Label lblSpatialQuantWidth;
        private System.Windows.Forms.ComboBox cboSpatialQuantWidth;
        private System.Windows.Forms.Button btnHelp;
        private System.Windows.Forms.Button btnCancel;
        private System.Windows.Forms.Button btnReset;
        private System.Windows.Forms.Button btnApply;
    }
}
