namespace CVIPGUI.Utilities
{
    partial class UtilCompare
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
            this.grpCompare = new System.Windows.Forms.GroupBox();
            this.pnlCompareImages = new System.Windows.Forms.Panel();
            this.rbCompareOverlap = new System.Windows.Forms.RadioButton();
            this.rbCompareJaccard = new System.Windows.Forms.RadioButton();
            this.lblResult = new System.Windows.Forms.Label();
            this.txtResult = new System.Windows.Forms.Label();
            this.rbCompareRMS_SUB = new System.Windows.Forms.RadioButton();
            this.rbCompareSNR_XOR = new System.Windows.Forms.RadioButton();
            this.rbCompareXORe = new System.Windows.Forms.RadioButton();
            this.rbCompareDice = new System.Windows.Forms.RadioButton();
            this.pnlPrattResultRGB = new System.Windows.Forms.Panel();
            this.txtPrattResultB = new System.Windows.Forms.Label();
            this.txtPrattResultG = new System.Windows.Forms.Label();
            this.txtPrattResultR = new System.Windows.Forms.Label();
            this.lblSecondImage = new System.Windows.Forms.Label();
            this.cboSecondImage = new System.Windows.Forms.ComboBox();
            this.lblCurrentImage = new System.Windows.Forms.Label();
            this.txtCurrentImage = new System.Windows.Forms.Label();
            this.pnlComparePratt = new System.Windows.Forms.Panel();
            this.txtPrattResultGS = new System.Windows.Forms.Label();
            this.lblPrattResult = new System.Windows.Forms.Label();
            this.txtPrattResult = new System.Windows.Forms.Label();
            this.lblScaleFactor = new System.Windows.Forms.Label();
            this.cboScaleFactor = new System.Windows.Forms.ComboBox();
            this.btnHelp = new System.Windows.Forms.Button();
            this.btnCancel = new System.Windows.Forms.Button();
            this.btnReset = new System.Windows.Forms.Button();
            this.btnApply = new System.Windows.Forms.Button();
            this.toolTipImage2 = new System.Windows.Forms.ToolTip(this.components);
            this.grpCompare.SuspendLayout();
            this.pnlCompareImages.SuspendLayout();
            this.pnlPrattResultRGB.SuspendLayout();
            this.pnlComparePratt.SuspendLayout();
            this.SuspendLayout();
            // 
            // grpCompare
            // 
            this.grpCompare.Controls.Add(this.pnlCompareImages);
            this.grpCompare.Controls.Add(this.pnlPrattResultRGB);
            this.grpCompare.Controls.Add(this.lblSecondImage);
            this.grpCompare.Controls.Add(this.cboSecondImage);
            this.grpCompare.Controls.Add(this.lblCurrentImage);
            this.grpCompare.Controls.Add(this.txtCurrentImage);
            this.grpCompare.Controls.Add(this.pnlComparePratt);
            this.grpCompare.Location = new System.Drawing.Point(2, -4);
            this.grpCompare.Name = "grpCompare";
            this.grpCompare.Size = new System.Drawing.Size(427, 104);
            this.grpCompare.TabIndex = 0;
            this.grpCompare.TabStop = false;
            // 
            // pnlCompareImages
            // 
            this.pnlCompareImages.Controls.Add(this.rbCompareOverlap);
            this.pnlCompareImages.Controls.Add(this.rbCompareJaccard);
            this.pnlCompareImages.Controls.Add(this.lblResult);
            this.pnlCompareImages.Controls.Add(this.txtResult);
            this.pnlCompareImages.Controls.Add(this.rbCompareRMS_SUB);
            this.pnlCompareImages.Controls.Add(this.rbCompareSNR_XOR);
            this.pnlCompareImages.Controls.Add(this.rbCompareXORe);
            this.pnlCompareImages.Controls.Add(this.rbCompareDice);
            this.pnlCompareImages.Location = new System.Drawing.Point(3, 57);
            this.pnlCompareImages.Name = "pnlCompareImages";
            this.pnlCompareImages.Size = new System.Drawing.Size(415, 47);
            this.pnlCompareImages.TabIndex = 5;
            // 
            // rbCompareOverlap
            // 
            this.rbCompareOverlap.AutoSize = true;
            this.rbCompareOverlap.Location = new System.Drawing.Point(350, 4);
            this.rbCompareOverlap.Name = "rbCompareOverlap";
            this.rbCompareOverlap.Size = new System.Drawing.Size(62, 17);
            this.rbCompareOverlap.TabIndex = 5;
            this.rbCompareOverlap.Text = "Overlap";
            this.rbCompareOverlap.UseVisualStyleBackColor = true;
            this.rbCompareOverlap.CheckedChanged += new System.EventHandler(this.compareCheckChanged);
            // 
            // rbCompareJaccard
            // 
            this.rbCompareJaccard.AutoSize = true;
            this.rbCompareJaccard.Location = new System.Drawing.Point(285, 4);
            this.rbCompareJaccard.Name = "rbCompareJaccard";
            this.rbCompareJaccard.Size = new System.Drawing.Size(63, 17);
            this.rbCompareJaccard.TabIndex = 4;
            this.rbCompareJaccard.Text = "Jaccard";
            this.rbCompareJaccard.UseVisualStyleBackColor = true;
            this.rbCompareJaccard.CheckedChanged += new System.EventHandler(this.compareCheckChanged);
            // 
            // lblResult
            // 
            this.lblResult.AutoSize = true;
            this.lblResult.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lblResult.ForeColor = System.Drawing.Color.Purple;
            this.lblResult.Location = new System.Drawing.Point(1, 26);
            this.lblResult.Name = "lblResult";
            this.lblResult.Size = new System.Drawing.Size(47, 13);
            this.lblResult.TabIndex = 5;
            this.lblResult.Text = "Result:";
            this.lblResult.Visible = false;
            // 
            // txtResult
            // 
            this.txtResult.AutoSize = true;
            this.txtResult.BackColor = System.Drawing.SystemColors.HighlightText;
            this.txtResult.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.txtResult.Location = new System.Drawing.Point(48, 26);
            this.txtResult.Name = "txtResult";
            this.txtResult.Size = new System.Drawing.Size(2, 15);
            this.txtResult.TabIndex = 4;
            this.txtResult.Visible = false;
            // 
            // rbCompareRMS_SUB
            // 
            this.rbCompareRMS_SUB.AutoSize = true;
            this.rbCompareRMS_SUB.Location = new System.Drawing.Point(4, 3);
            this.rbCompareRMS_SUB.Name = "rbCompareRMS_SUB";
            this.rbCompareRMS_SUB.Size = new System.Drawing.Size(73, 17);
            this.rbCompareRMS_SUB.TabIndex = 0;
            this.rbCompareRMS_SUB.Text = "RMS error";
            this.rbCompareRMS_SUB.UseVisualStyleBackColor = true;
            this.rbCompareRMS_SUB.CheckedChanged += new System.EventHandler(this.compareCheckChanged);
            // 
            // rbCompareSNR_XOR
            // 
            this.rbCompareSNR_XOR.AutoSize = true;
            this.rbCompareSNR_XOR.Location = new System.Drawing.Point(80, 3);
            this.rbCompareSNR_XOR.Name = "rbCompareSNR_XOR";
            this.rbCompareSNR_XOR.Size = new System.Drawing.Size(76, 17);
            this.rbCompareSNR_XOR.TabIndex = 1;
            this.rbCompareSNR_XOR.Text = "Peak SNR";
            this.rbCompareSNR_XOR.UseVisualStyleBackColor = true;
            this.rbCompareSNR_XOR.CheckedChanged += new System.EventHandler(this.compareCheckChanged);
            // 
            // rbCompareXORe
            // 
            this.rbCompareXORe.AutoSize = true;
            this.rbCompareXORe.Location = new System.Drawing.Point(160, 4);
            this.rbCompareXORe.Name = "rbCompareXORe";
            this.rbCompareXORe.Size = new System.Drawing.Size(72, 17);
            this.rbCompareXORe.TabIndex = 2;
            this.rbCompareXORe.Text = "XOR error";
            this.rbCompareXORe.UseVisualStyleBackColor = true;
            this.rbCompareXORe.CheckedChanged += new System.EventHandler(this.compareCheckChanged);
            // 
            // rbCompareDice
            // 
            this.rbCompareDice.AutoSize = true;
            this.rbCompareDice.Location = new System.Drawing.Point(235, 4);
            this.rbCompareDice.Name = "rbCompareDice";
            this.rbCompareDice.Size = new System.Drawing.Size(47, 17);
            this.rbCompareDice.TabIndex = 3;
            this.rbCompareDice.Text = "Dice";
            this.rbCompareDice.UseVisualStyleBackColor = true;
            this.rbCompareDice.CheckedChanged += new System.EventHandler(this.compareCheckChanged);
            // 
            // pnlPrattResultRGB
            // 
            this.pnlPrattResultRGB.BackColor = System.Drawing.Color.White;
            this.pnlPrattResultRGB.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.pnlPrattResultRGB.Controls.Add(this.txtPrattResultB);
            this.pnlPrattResultRGB.Controls.Add(this.txtPrattResultG);
            this.pnlPrattResultRGB.Controls.Add(this.txtPrattResultR);
            this.pnlPrattResultRGB.Location = new System.Drawing.Point(237, 68);
            this.pnlPrattResultRGB.Name = "pnlPrattResultRGB";
            this.pnlPrattResultRGB.Size = new System.Drawing.Size(178, 20);
            this.pnlPrattResultRGB.TabIndex = 8;
            this.pnlPrattResultRGB.Visible = false;
            // 
            // txtPrattResultB
            // 
            this.txtPrattResultB.AutoSize = true;
            this.txtPrattResultB.ForeColor = System.Drawing.Color.Blue;
            this.txtPrattResultB.Location = new System.Drawing.Point(119, 2);
            this.txtPrattResultB.Name = "txtPrattResultB";
            this.txtPrattResultB.Size = new System.Drawing.Size(52, 13);
            this.txtPrattResultB.TabIndex = 2;
            this.txtPrattResultB.Text = "0.000000";
            // 
            // txtPrattResultG
            // 
            this.txtPrattResultG.AutoSize = true;
            this.txtPrattResultG.ForeColor = System.Drawing.Color.Green;
            this.txtPrattResultG.Location = new System.Drawing.Point(61, 2);
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
            // lblSecondImage
            // 
            this.lblSecondImage.AutoSize = true;
            this.lblSecondImage.Location = new System.Drawing.Point(9, 38);
            this.lblSecondImage.Name = "lblSecondImage";
            this.lblSecondImage.Size = new System.Drawing.Size(101, 13);
            this.lblSecondImage.TabIndex = 3;
            this.lblSecondImage.Text = "With Second Image";
            // 
            // cboSecondImage
            // 
            this.cboSecondImage.DisplayMember = "Text";
            this.cboSecondImage.DrawMode = System.Windows.Forms.DrawMode.OwnerDrawFixed;
            this.cboSecondImage.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cboSecondImage.FormattingEnabled = true;
            this.cboSecondImage.Location = new System.Drawing.Point(134, 35);
            this.cboSecondImage.Name = "cboSecondImage";
            this.cboSecondImage.Size = new System.Drawing.Size(282, 21);
            this.cboSecondImage.TabIndex = 2;
            this.cboSecondImage.DrawItem += new System.Windows.Forms.DrawItemEventHandler(this.cboSecondImage_DrawItem);
            this.cboSecondImage.SelectedIndexChanged += new System.EventHandler(this.cboSecondImage_SelectedIndexChanged);
            // 
            // lblCurrentImage
            // 
            this.lblCurrentImage.AutoSize = true;
            this.lblCurrentImage.Location = new System.Drawing.Point(9, 16);
            this.lblCurrentImage.Name = "lblCurrentImage";
            this.lblCurrentImage.Size = new System.Drawing.Size(90, 13);
            this.lblCurrentImage.TabIndex = 1;
            this.lblCurrentImage.Text = "Ideal Edge Image";
            // 
            // txtCurrentImage
            // 
            this.txtCurrentImage.AutoSize = true;
            this.txtCurrentImage.ForeColor = System.Drawing.Color.Purple;
            this.txtCurrentImage.Location = new System.Drawing.Point(150, 16);
            this.txtCurrentImage.Name = "txtCurrentImage";
            this.txtCurrentImage.Size = new System.Drawing.Size(0, 13);
            this.txtCurrentImage.TabIndex = 0;
            // 
            // pnlComparePratt
            // 
            this.pnlComparePratt.Controls.Add(this.txtPrattResultGS);
            this.pnlComparePratt.Controls.Add(this.lblPrattResult);
            this.pnlComparePratt.Controls.Add(this.txtPrattResult);
            this.pnlComparePratt.Controls.Add(this.lblScaleFactor);
            this.pnlComparePratt.Controls.Add(this.cboScaleFactor);
            this.pnlComparePratt.Location = new System.Drawing.Point(3, 57);
            this.pnlComparePratt.Name = "pnlComparePratt";
            this.pnlComparePratt.Size = new System.Drawing.Size(415, 51);
            this.pnlComparePratt.TabIndex = 4;
            // 
            // txtPrattResultGS
            // 
            this.txtPrattResultGS.AutoSize = true;
            this.txtPrattResultGS.BackColor = System.Drawing.Color.White;
            this.txtPrattResultGS.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.txtPrattResultGS.Location = new System.Drawing.Point(231, 12);
            this.txtPrattResultGS.Name = "txtPrattResultGS";
            this.txtPrattResultGS.Size = new System.Drawing.Size(65, 13);
            this.txtPrattResultGS.TabIndex = 4;
            this.txtPrattResultGS.Text = "   Working...";
            this.txtPrattResultGS.Visible = false;
            // 
            // lblPrattResult
            // 
            this.lblPrattResult.AutoSize = true;
            this.lblPrattResult.ForeColor = System.Drawing.Color.Purple;
            this.lblPrattResult.Location = new System.Drawing.Point(181, 13);
            this.lblPrattResult.Name = "lblPrattResult";
            this.lblPrattResult.Size = new System.Drawing.Size(37, 13);
            this.lblPrattResult.TabIndex = 3;
            this.lblPrattResult.Text = "Result";
            // 
            // txtPrattResult
            // 
            this.txtPrattResult.AutoSize = true;
            this.txtPrattResult.BackColor = System.Drawing.SystemColors.HighlightText;
            this.txtPrattResult.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.txtPrattResult.Location = new System.Drawing.Point(224, 13);
            this.txtPrattResult.Name = "txtPrattResult";
            this.txtPrattResult.Size = new System.Drawing.Size(2, 15);
            this.txtPrattResult.TabIndex = 2;
            // 
            // lblScaleFactor
            // 
            this.lblScaleFactor.AutoSize = true;
            this.lblScaleFactor.Location = new System.Drawing.Point(6, 13);
            this.lblScaleFactor.Name = "lblScaleFactor";
            this.lblScaleFactor.Size = new System.Drawing.Size(67, 13);
            this.lblScaleFactor.TabIndex = 1;
            this.lblScaleFactor.Text = "Scale Factor";
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
            this.cboScaleFactor.Location = new System.Drawing.Point(79, 10);
            this.cboScaleFactor.Name = "cboScaleFactor";
            this.cboScaleFactor.Size = new System.Drawing.Size(67, 21);
            this.cboScaleFactor.TabIndex = 0;
            // 
            // btnHelp
            // 
            this.btnHelp.BackColor = System.Drawing.Color.Yellow;
            this.btnHelp.Location = new System.Drawing.Point(5, 110);
            this.btnHelp.Name = "btnHelp";
            this.btnHelp.Size = new System.Drawing.Size(60, 26);
            this.btnHelp.TabIndex = 1;
            this.btnHelp.Text = "Help";
            this.btnHelp.UseVisualStyleBackColor = false;
            this.btnHelp.Click += new System.EventHandler(this.btnHelp_Click);
            // 
            // btnCancel
            // 
            this.btnCancel.BackColor = System.Drawing.Color.OrangeRed;
            this.btnCancel.CausesValidation = false;
            this.btnCancel.Location = new System.Drawing.Point(239, 110);
            this.btnCancel.Name = "btnCancel";
            this.btnCancel.Size = new System.Drawing.Size(60, 26);
            this.btnCancel.TabIndex = 2;
            this.btnCancel.Text = "Cancel";
            this.btnCancel.UseVisualStyleBackColor = false;
            this.btnCancel.Click += new System.EventHandler(this.btnCancel_Click);
            // 
            // btnReset
            // 
            this.btnReset.BackColor = System.Drawing.Color.CornflowerBlue;
            this.btnReset.CausesValidation = false;
            this.btnReset.Location = new System.Drawing.Point(305, 110);
            this.btnReset.Name = "btnReset";
            this.btnReset.Size = new System.Drawing.Size(60, 26);
            this.btnReset.TabIndex = 3;
            this.btnReset.Text = "Reset";
            this.btnReset.UseVisualStyleBackColor = false;
            this.btnReset.Click += new System.EventHandler(this.btnReset_Click);
            // 
            // btnApply
            // 
            this.btnApply.BackColor = System.Drawing.Color.LimeGreen;
            this.btnApply.ForeColor = System.Drawing.Color.White;
            this.btnApply.Location = new System.Drawing.Point(371, 110);
            this.btnApply.Name = "btnApply";
            this.btnApply.Size = new System.Drawing.Size(60, 26);
            this.btnApply.TabIndex = 4;
            this.btnApply.Text = "Apply";
            this.btnApply.UseVisualStyleBackColor = false;
            this.btnApply.Click += new System.EventHandler(this.btnApply_Click);
            // 
            // UtilCompare
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.btnApply);
            this.Controls.Add(this.btnReset);
            this.Controls.Add(this.btnCancel);
            this.Controls.Add(this.btnHelp);
            this.Controls.Add(this.grpCompare);
            this.Name = "UtilCompare";
            this.Size = new System.Drawing.Size(433, 158);
            this.grpCompare.ResumeLayout(false);
            this.grpCompare.PerformLayout();
            this.pnlCompareImages.ResumeLayout(false);
            this.pnlCompareImages.PerformLayout();
            this.pnlPrattResultRGB.ResumeLayout(false);
            this.pnlPrattResultRGB.PerformLayout();
            this.pnlComparePratt.ResumeLayout(false);
            this.pnlComparePratt.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox grpCompare;
        private System.Windows.Forms.Panel pnlCompareImages;
        private System.Windows.Forms.Label lblResult;
        private System.Windows.Forms.Label txtResult;
        private System.Windows.Forms.RadioButton rbCompareRMS_SUB;
        private System.Windows.Forms.RadioButton rbCompareSNR_XOR;
        private System.Windows.Forms.RadioButton rbCompareXORe;
        private System.Windows.Forms.RadioButton rbCompareDice;
        private System.Windows.Forms.Panel pnlComparePratt;
        private System.Windows.Forms.Label lblPrattResult;
        private System.Windows.Forms.Label txtPrattResult;
        private System.Windows.Forms.Label lblScaleFactor;
        private System.Windows.Forms.ComboBox cboScaleFactor;
        private System.Windows.Forms.Label lblSecondImage;
        private System.Windows.Forms.ComboBox cboSecondImage;
        private System.Windows.Forms.Label lblCurrentImage;
        private System.Windows.Forms.Label txtCurrentImage;
        private System.Windows.Forms.Button btnHelp;
        private System.Windows.Forms.Button btnCancel;
        private System.Windows.Forms.Button btnReset;
        private System.Windows.Forms.Button btnApply;
        private System.Windows.Forms.ToolTip toolTipImage2;
        private System.Windows.Forms.Panel pnlPrattResultRGB;
        private System.Windows.Forms.Label txtPrattResultB;
        private System.Windows.Forms.Label txtPrattResultR;
        private System.Windows.Forms.Label txtPrattResultG;
        private System.Windows.Forms.Label txtPrattResultGS;
        private System.Windows.Forms.RadioButton rbCompareOverlap;
        private System.Windows.Forms.RadioButton rbCompareJaccard;
    }
}
