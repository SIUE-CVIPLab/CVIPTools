namespace CVIPGUI.Utilities
{
    partial class UtilArithLogic
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
            this.grpArithLogic = new System.Windows.Forms.GroupBox();
            this.pnlMultConstant = new System.Windows.Forms.Panel();
            this.chkByteClipping = new System.Windows.Forms.CheckBox();
            this.lblMultConstant = new System.Windows.Forms.Label();
            this.cboMultConstant = new System.Windows.Forms.ComboBox();
            this.pnlSecondImage = new System.Windows.Forms.Panel();
            this.lblSecondImage = new System.Windows.Forms.Label();
            this.cboSecondImage = new System.Windows.Forms.ComboBox();
            this.lblCurrentImage = new System.Windows.Forms.Label();
            this.txtCurrentImage = new System.Windows.Forms.Label();
            this.rbConstant = new System.Windows.Forms.RadioButton();
            this.rbImage = new System.Windows.Forms.RadioButton();
            this.lblCurrentOperation = new System.Windows.Forms.Label();
            this.txtCurrentOperation = new System.Windows.Forms.Label();
            this.btnHelp = new System.Windows.Forms.Button();
            this.btnCancel = new System.Windows.Forms.Button();
            this.btnReset = new System.Windows.Forms.Button();
            this.btnApply = new System.Windows.Forms.Button();
            this.toolTipImage2 = new System.Windows.Forms.ToolTip(this.components);
            this.grpArithLogic.SuspendLayout();
            this.pnlMultConstant.SuspendLayout();
            this.pnlSecondImage.SuspendLayout();
            this.SuspendLayout();
            // 
            // grpArithLogic
            // 
            this.grpArithLogic.Controls.Add(this.pnlMultConstant);
            this.grpArithLogic.Controls.Add(this.pnlSecondImage);
            this.grpArithLogic.Controls.Add(this.lblCurrentImage);
            this.grpArithLogic.Controls.Add(this.txtCurrentImage);
            this.grpArithLogic.Controls.Add(this.rbConstant);
            this.grpArithLogic.Controls.Add(this.rbImage);
            this.grpArithLogic.Controls.Add(this.lblCurrentOperation);
            this.grpArithLogic.Controls.Add(this.txtCurrentOperation);
            this.grpArithLogic.Location = new System.Drawing.Point(3, -5);
            this.grpArithLogic.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.grpArithLogic.Name = "grpArithLogic";
            this.grpArithLogic.Padding = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.grpArithLogic.Size = new System.Drawing.Size(573, 132);
            this.grpArithLogic.TabIndex = 0;
            this.grpArithLogic.TabStop = false;
            this.grpArithLogic.Enter += new System.EventHandler(this.grpArithLogic_Enter);
            // 
            // pnlMultConstant
            // 
            this.pnlMultConstant.Controls.Add(this.chkByteClipping);
            this.pnlMultConstant.Controls.Add(this.lblMultConstant);
            this.pnlMultConstant.Controls.Add(this.cboMultConstant);
            this.pnlMultConstant.Location = new System.Drawing.Point(3, 68);
            this.pnlMultConstant.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.pnlMultConstant.Name = "pnlMultConstant";
            this.pnlMultConstant.Size = new System.Drawing.Size(557, 44);
            this.pnlMultConstant.TabIndex = 7;
            // 
            // chkByteClipping
            // 
            this.chkByteClipping.AutoSize = true;
            this.chkByteClipping.Checked = true;
            this.chkByteClipping.CheckState = System.Windows.Forms.CheckState.Checked;
            this.chkByteClipping.Location = new System.Drawing.Point(256, 10);
            this.chkByteClipping.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.chkByteClipping.Name = "chkByteClipping";
            this.chkByteClipping.Size = new System.Drawing.Size(120, 21);
            this.chkByteClipping.TabIndex = 2;
            this.chkByteClipping.Text = "BYTE Clipping";
            this.chkByteClipping.UseVisualStyleBackColor = true;
            // 
            // lblMultConstant
            // 
            this.lblMultConstant.AutoSize = true;
            this.lblMultConstant.Location = new System.Drawing.Point(8, 15);
            this.lblMultConstant.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lblMultConstant.Name = "lblMultConstant";
            this.lblMultConstant.Size = new System.Drawing.Size(94, 17);
            this.lblMultConstant.TabIndex = 1;
            this.lblMultConstant.Text = "By a constant";
            // 
            // cboMultConstant
            // 
            this.cboMultConstant.FormattingEnabled = true;
            this.cboMultConstant.Items.AddRange(new object[] {
            "0.2",
            "0.5",
            "0.8",
            "1.2",
            "1.5",
            "1.8",
            "2.0",
            "2.5",
            "3.0"});
            this.cboMultConstant.Location = new System.Drawing.Point(112, 10);
            this.cboMultConstant.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.cboMultConstant.Name = "cboMultConstant";
            this.cboMultConstant.Size = new System.Drawing.Size(96, 24);
            this.cboMultConstant.TabIndex = 0;
            this.cboMultConstant.Validating += new System.ComponentModel.CancelEventHandler(this.cboMultConstant_Validating);
            // 
            // pnlSecondImage
            // 
            this.pnlSecondImage.Controls.Add(this.lblSecondImage);
            this.pnlSecondImage.Controls.Add(this.cboSecondImage);
            this.pnlSecondImage.Location = new System.Drawing.Point(3, 68);
            this.pnlSecondImage.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.pnlSecondImage.Name = "pnlSecondImage";
            this.pnlSecondImage.Size = new System.Drawing.Size(557, 44);
            this.pnlSecondImage.TabIndex = 6;
            // 
            // lblSecondImage
            // 
            this.lblSecondImage.AutoSize = true;
            this.lblSecondImage.Location = new System.Drawing.Point(7, 14);
            this.lblSecondImage.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lblSecondImage.Name = "lblSecondImage";
            this.lblSecondImage.Size = new System.Drawing.Size(98, 17);
            this.lblSecondImage.TabIndex = 1;
            this.lblSecondImage.Text = "Second Image";
            // 
            // cboSecondImage
            // 
            this.cboSecondImage.DisplayMember = "Text";
            this.cboSecondImage.DrawMode = System.Windows.Forms.DrawMode.OwnerDrawFixed;
            this.cboSecondImage.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cboSecondImage.FormattingEnabled = true;
            this.cboSecondImage.Location = new System.Drawing.Point(113, 10);
            this.cboSecondImage.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.cboSecondImage.Name = "cboSecondImage";
            this.cboSecondImage.Size = new System.Drawing.Size(387, 23);
            this.cboSecondImage.TabIndex = 0;
            this.cboSecondImage.DrawItem += new System.Windows.Forms.DrawItemEventHandler(this.cboSecondImage_DrawItem);
            this.cboSecondImage.SelectedIndexChanged += new System.EventHandler(this.cboSecondImage_SelectedIndexChanged);
            // 
            // lblCurrentImage
            // 
            this.lblCurrentImage.AutoSize = true;
            this.lblCurrentImage.Location = new System.Drawing.Point(9, 48);
            this.lblCurrentImage.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lblCurrentImage.Name = "lblCurrentImage";
            this.lblCurrentImage.Size = new System.Drawing.Size(97, 17);
            this.lblCurrentImage.TabIndex = 5;
            this.lblCurrentImage.Text = "Current Image";
            // 
            // txtCurrentImage
            // 
            this.txtCurrentImage.AutoSize = true;
            this.txtCurrentImage.Location = new System.Drawing.Point(111, 48);
            this.txtCurrentImage.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.txtCurrentImage.Name = "txtCurrentImage";
            this.txtCurrentImage.Size = new System.Drawing.Size(0, 17);
            this.txtCurrentImage.TabIndex = 4;
            // 
            // rbConstant
            // 
            this.rbConstant.AutoSize = true;
            this.rbConstant.Location = new System.Drawing.Point(285, 12);
            this.rbConstant.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.rbConstant.Name = "rbConstant";
            this.rbConstant.Size = new System.Drawing.Size(85, 21);
            this.rbConstant.TabIndex = 3;
            this.rbConstant.Text = "Constant";
            this.rbConstant.UseVisualStyleBackColor = true;
            this.rbConstant.Click += new System.EventHandler(this.rbMultOp_Click);
            // 
            // rbImage
            // 
            this.rbImage.AutoSize = true;
            this.rbImage.Checked = true;
            this.rbImage.Location = new System.Drawing.Point(205, 12);
            this.rbImage.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.rbImage.Name = "rbImage";
            this.rbImage.Size = new System.Drawing.Size(67, 21);
            this.rbImage.TabIndex = 2;
            this.rbImage.TabStop = true;
            this.rbImage.Text = "Image";
            this.rbImage.UseVisualStyleBackColor = true;
            this.rbImage.Click += new System.EventHandler(this.rbMultOp_Click);
            // 
            // lblCurrentOperation
            // 
            this.lblCurrentOperation.AutoSize = true;
            this.lblCurrentOperation.Location = new System.Drawing.Point(7, 15);
            this.lblCurrentOperation.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lblCurrentOperation.Name = "lblCurrentOperation";
            this.lblCurrentOperation.Size = new System.Drawing.Size(122, 17);
            this.lblCurrentOperation.TabIndex = 1;
            this.lblCurrentOperation.Text = "Current Operation";
            // 
            // txtCurrentOperation
            // 
            this.txtCurrentOperation.AutoSize = true;
            this.txtCurrentOperation.ForeColor = System.Drawing.Color.Purple;
            this.txtCurrentOperation.Location = new System.Drawing.Point(135, 15);
            this.txtCurrentOperation.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.txtCurrentOperation.Name = "txtCurrentOperation";
            this.txtCurrentOperation.Size = new System.Drawing.Size(33, 17);
            this.txtCurrentOperation.TabIndex = 0;
            this.txtCurrentOperation.Text = "Add";
            // 
            // btnHelp
            // 
            this.btnHelp.BackColor = System.Drawing.Color.Yellow;
            this.btnHelp.Location = new System.Drawing.Point(4, 135);
            this.btnHelp.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.btnHelp.Name = "btnHelp";
            this.btnHelp.Size = new System.Drawing.Size(80, 32);
            this.btnHelp.TabIndex = 1;
            this.btnHelp.Text = "Help";
            this.btnHelp.UseVisualStyleBackColor = false;
            this.btnHelp.Click += new System.EventHandler(this.btnHelp_Click);
            // 
            // btnCancel
            // 
            this.btnCancel.BackColor = System.Drawing.Color.OrangeRed;
            this.btnCancel.CausesValidation = false;
            this.btnCancel.Location = new System.Drawing.Point(319, 135);
            this.btnCancel.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.btnCancel.Name = "btnCancel";
            this.btnCancel.Size = new System.Drawing.Size(80, 32);
            this.btnCancel.TabIndex = 2;
            this.btnCancel.Text = "Cancel";
            this.btnCancel.UseVisualStyleBackColor = false;
            this.btnCancel.Click += new System.EventHandler(this.btnCancel_Click);
            // 
            // btnReset
            // 
            this.btnReset.BackColor = System.Drawing.Color.CornflowerBlue;
            this.btnReset.CausesValidation = false;
            this.btnReset.Location = new System.Drawing.Point(407, 135);
            this.btnReset.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.btnReset.Name = "btnReset";
            this.btnReset.Size = new System.Drawing.Size(80, 32);
            this.btnReset.TabIndex = 3;
            this.btnReset.Text = "Reset";
            this.btnReset.UseVisualStyleBackColor = false;
            this.btnReset.Click += new System.EventHandler(this.btnReset_Click);
            // 
            // btnApply
            // 
            this.btnApply.BackColor = System.Drawing.Color.LimeGreen;
            this.btnApply.ForeColor = System.Drawing.Color.White;
            this.btnApply.Location = new System.Drawing.Point(495, 135);
            this.btnApply.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.btnApply.Name = "btnApply";
            this.btnApply.Size = new System.Drawing.Size(80, 32);
            this.btnApply.TabIndex = 4;
            this.btnApply.Text = "Apply";
            this.btnApply.UseVisualStyleBackColor = false;
            this.btnApply.Click += new System.EventHandler(this.btnApply_Click);
            // 
            // UtilArithLogic
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.btnApply);
            this.Controls.Add(this.btnReset);
            this.Controls.Add(this.btnCancel);
            this.Controls.Add(this.btnHelp);
            this.Controls.Add(this.grpArithLogic);
            this.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.Name = "UtilArithLogic";
            this.Size = new System.Drawing.Size(581, 172);
            this.grpArithLogic.ResumeLayout(false);
            this.grpArithLogic.PerformLayout();
            this.pnlMultConstant.ResumeLayout(false);
            this.pnlMultConstant.PerformLayout();
            this.pnlSecondImage.ResumeLayout(false);
            this.pnlSecondImage.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox grpArithLogic;
        private System.Windows.Forms.Panel pnlMultConstant;
        private System.Windows.Forms.CheckBox chkByteClipping;
        private System.Windows.Forms.Label lblMultConstant;
        private System.Windows.Forms.ComboBox cboMultConstant;
        private System.Windows.Forms.Panel pnlSecondImage;
        private System.Windows.Forms.Label lblSecondImage;
        private System.Windows.Forms.ComboBox cboSecondImage;
        private System.Windows.Forms.Label lblCurrentImage;
        private System.Windows.Forms.Label txtCurrentImage;
        private System.Windows.Forms.RadioButton rbConstant;
        private System.Windows.Forms.RadioButton rbImage;
        private System.Windows.Forms.Label lblCurrentOperation;
        private System.Windows.Forms.Label txtCurrentOperation;
        private System.Windows.Forms.Button btnHelp;
        private System.Windows.Forms.Button btnCancel;
        private System.Windows.Forms.Button btnReset;
        private System.Windows.Forms.Button btnApply;
        private System.Windows.Forms.ToolTip toolTipImage2;
    }
}
