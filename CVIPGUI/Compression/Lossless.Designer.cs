namespace CVIPGUI.Compression
{
    partial class Lossless
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
            this.rbHuffman = new System.Windows.Forms.RadioButton();
            this.rbZivLempel = new System.Windows.Forms.RadioButton();
            this.rbDPC = new System.Windows.Forms.RadioButton();
            this.rbBitplaneRLC = new System.Windows.Forms.RadioButton();
            this.rbJPEG2000 = new System.Windows.Forms.RadioButton();
            this.grpHuffman = new System.Windows.Forms.GroupBox();
            this.grpBitplaneRLC = new System.Windows.Forms.GroupBox();
            this.grpParameters = new System.Windows.Forms.GroupBox();
            this.label4 = new System.Windows.Forms.Label();
            this.comboBox4 = new System.Windows.Forms.ComboBox();
            this.label3 = new System.Windows.Forms.Label();
            this.comboBox3 = new System.Windows.Forms.ComboBox();
            this.label2 = new System.Windows.Forms.Label();
            this.comboBox2 = new System.Windows.Forms.ComboBox();
            this.label1 = new System.Windows.Forms.Label();
            this.comboBox1 = new System.Windows.Forms.ComboBox();
            this.btnHelp = new System.Windows.Forms.Button();
            this.btnSaveCompressedData = new System.Windows.Forms.Button();
            this.btnCancel = new System.Windows.Forms.Button();
            this.btnReset = new System.Windows.Forms.Button();
            this.btnApply = new System.Windows.Forms.Button();
            this.grpParameters.SuspendLayout();
            this.SuspendLayout();
            // 
            // rbHuffman
            // 
            this.rbHuffman.AutoSize = true;
            this.rbHuffman.Checked = true;
            this.rbHuffman.Location = new System.Drawing.Point(21, 21);
            this.rbHuffman.Name = "rbHuffman";
            this.rbHuffman.Size = new System.Drawing.Size(65, 17);
            this.rbHuffman.TabIndex = 0;
            this.rbHuffman.TabStop = true;
            this.rbHuffman.Text = "Huffman";
            this.rbHuffman.UseVisualStyleBackColor = true;
            this.rbHuffman.Click += new System.EventHandler(this.rbLossless_Click);
            // 
            // rbZivLempel
            // 
            this.rbZivLempel.AutoSize = true;
            this.rbZivLempel.Location = new System.Drawing.Point(21, 50);
            this.rbZivLempel.Name = "rbZivLempel";
            this.rbZivLempel.Size = new System.Drawing.Size(77, 17);
            this.rbZivLempel.TabIndex = 1;
            this.rbZivLempel.Text = "Ziv-Lempel";
            this.rbZivLempel.UseVisualStyleBackColor = true;
            this.rbZivLempel.Click += new System.EventHandler(this.rbLossless_Click);
            // 
            // rbDPC
            // 
            this.rbDPC.AutoSize = true;
            this.rbDPC.Location = new System.Drawing.Point(21, 79);
            this.rbDPC.Name = "rbDPC";
            this.rbDPC.Size = new System.Drawing.Size(47, 17);
            this.rbDPC.TabIndex = 2;
            this.rbDPC.Text = "DPC";
            this.rbDPC.UseVisualStyleBackColor = true;
            this.rbDPC.Click += new System.EventHandler(this.rbLossless_Click);
            // 
            // rbBitplaneRLC
            // 
            this.rbBitplaneRLC.AutoSize = true;
            this.rbBitplaneRLC.Location = new System.Drawing.Point(21, 171);
            this.rbBitplaneRLC.Name = "rbBitplaneRLC";
            this.rbBitplaneRLC.Size = new System.Drawing.Size(87, 17);
            this.rbBitplaneRLC.TabIndex = 3;
            this.rbBitplaneRLC.Text = "Bitplane RLC";
            this.rbBitplaneRLC.UseVisualStyleBackColor = true;
            this.rbBitplaneRLC.Click += new System.EventHandler(this.rbLossless_Click);
            // 
            // rbJPEG2000
            // 
            this.rbJPEG2000.AutoSize = true;
            this.rbJPEG2000.Location = new System.Drawing.Point(21, 200);
            this.rbJPEG2000.Name = "rbJPEG2000";
            this.rbJPEG2000.Size = new System.Drawing.Size(235, 17);
            this.rbJPEG2000.TabIndex = 4;
            this.rbJPEG2000.Text = "Joint Photographic Expert Group(JPEG2000)";
            this.rbJPEG2000.UseVisualStyleBackColor = true;
            this.rbJPEG2000.Click += new System.EventHandler(this.rbLossless_Click);
            // 
            // grpHuffman
            // 
            this.grpHuffman.Location = new System.Drawing.Point(5, 2);
            this.grpHuffman.Name = "grpHuffman";
            this.grpHuffman.Size = new System.Drawing.Size(263, 146);
            this.grpHuffman.TabIndex = 5;
            this.grpHuffman.TabStop = false;
            // 
            // grpBitplaneRLC
            // 
            this.grpBitplaneRLC.Location = new System.Drawing.Point(5, 152);
            this.grpBitplaneRLC.Name = "grpBitplaneRLC";
            this.grpBitplaneRLC.Size = new System.Drawing.Size(263, 167);
            this.grpBitplaneRLC.TabIndex = 6;
            this.grpBitplaneRLC.TabStop = false;
            // 
            // grpParameters
            // 
            this.grpParameters.Controls.Add(this.label4);
            this.grpParameters.Controls.Add(this.comboBox4);
            this.grpParameters.Controls.Add(this.label3);
            this.grpParameters.Controls.Add(this.comboBox3);
            this.grpParameters.Controls.Add(this.label2);
            this.grpParameters.Controls.Add(this.comboBox2);
            this.grpParameters.Controls.Add(this.label1);
            this.grpParameters.Controls.Add(this.comboBox1);
            this.grpParameters.Location = new System.Drawing.Point(277, 2);
            this.grpParameters.Name = "grpParameters";
            this.grpParameters.Size = new System.Drawing.Size(316, 317);
            this.grpParameters.TabIndex = 7;
            this.grpParameters.TabStop = false;
            this.grpParameters.Text = "Parameters";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(14, 153);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(85, 13);
            this.label4.TabIndex = 7;
            this.label4.Text = "Code Block Size";
            this.label4.Visible = false;
            // 
            // comboBox4
            // 
            this.comboBox4.FormattingEnabled = true;
            this.comboBox4.Location = new System.Drawing.Point(124, 147);
            this.comboBox4.Name = "comboBox4";
            this.comboBox4.Size = new System.Drawing.Size(110, 21);
            this.comboBox4.TabIndex = 6;
            this.comboBox4.Visible = false;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(14, 117);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(75, 13);
            this.label3.TabIndex = 5;
            this.label3.Text = "Number of bits";
            this.label3.Visible = false;
            // 
            // comboBox3
            // 
            this.comboBox3.FormattingEnabled = true;
            this.comboBox3.Location = new System.Drawing.Point(124, 111);
            this.comboBox3.Name = "comboBox3";
            this.comboBox3.Size = new System.Drawing.Size(110, 21);
            this.comboBox3.TabIndex = 4;
            this.comboBox3.Visible = false;
            this.comboBox3.Leave += new System.EventHandler(this.comboBox3_Leave);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(14, 80);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(75, 13);
            this.label2.TabIndex = 3;
            this.label2.Text = "Scan direction";
            this.label2.Visible = false;
            // 
            // comboBox2
            // 
            this.comboBox2.FormattingEnabled = true;
            this.comboBox2.Location = new System.Drawing.Point(124, 74);
            this.comboBox2.Name = "comboBox2";
            this.comboBox2.Size = new System.Drawing.Size(110, 21);
            this.comboBox2.TabIndex = 2;
            this.comboBox2.Visible = false;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(14, 43);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(57, 13);
            this.label1.TabIndex = 1;
            this.label1.Text = "Correlation";
            this.label1.Visible = false;
            // 
            // comboBox1
            // 
            this.comboBox1.FormattingEnabled = true;
            this.comboBox1.Location = new System.Drawing.Point(124, 37);
            this.comboBox1.Name = "comboBox1";
            this.comboBox1.Size = new System.Drawing.Size(110, 21);
            this.comboBox1.TabIndex = 0;
            this.comboBox1.Visible = false;
            this.comboBox1.Leave += new System.EventHandler(this.comboBox1_Leave);
            // 
            // btnHelp
            // 
            this.btnHelp.BackColor = System.Drawing.Color.Yellow;
            this.btnHelp.Location = new System.Drawing.Point(12, 325);
            this.btnHelp.Name = "btnHelp";
            this.btnHelp.Size = new System.Drawing.Size(60, 26);
            this.btnHelp.TabIndex = 8;
            this.btnHelp.Text = "Help";
            this.btnHelp.UseVisualStyleBackColor = false;
            this.btnHelp.Click += new System.EventHandler(this.btnHelp_Click);
            // 
            // btnSaveCompressedData
            // 
            this.btnSaveCompressedData.Location = new System.Drawing.Point(134, 325);
            this.btnSaveCompressedData.Name = "btnSaveCompressedData";
            this.btnSaveCompressedData.Size = new System.Drawing.Size(134, 26);
            this.btnSaveCompressedData.TabIndex = 9;
            this.btnSaveCompressedData.Text = "Save Compressed Data";
            this.btnSaveCompressedData.UseVisualStyleBackColor = true;
            this.btnSaveCompressedData.Click += new System.EventHandler(this.btnSaveCompressedData_Click);
            // 
            // btnCancel
            // 
            this.btnCancel.BackColor = System.Drawing.Color.OrangeRed;
            this.btnCancel.Location = new System.Drawing.Point(400, 325);
            this.btnCancel.Name = "btnCancel";
            this.btnCancel.Size = new System.Drawing.Size(60, 26);
            this.btnCancel.TabIndex = 10;
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
            this.btnReset.TabIndex = 11;
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
            this.btnApply.TabIndex = 12;
            this.btnApply.Text = "Apply";
            this.btnApply.UseVisualStyleBackColor = false;
            this.btnApply.Click += new System.EventHandler(this.btnApply_Click);
            // 
            // Lossless
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.rbHuffman);
            this.Controls.Add(this.rbZivLempel);
            this.Controls.Add(this.rbDPC);
            this.Controls.Add(this.rbBitplaneRLC);
            this.Controls.Add(this.rbJPEG2000);
            this.Controls.Add(this.grpHuffman);
            this.Controls.Add(this.grpBitplaneRLC);
            this.Controls.Add(this.grpParameters);
            this.Controls.Add(this.btnHelp);
            this.Controls.Add(this.btnSaveCompressedData);
            this.Controls.Add(this.btnCancel);
            this.Controls.Add(this.btnReset);
            this.Controls.Add(this.btnApply);
            this.Name = "Lossless";
            this.Size = new System.Drawing.Size(601, 354);
            this.grpParameters.ResumeLayout(false);
            this.grpParameters.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.RadioButton rbHuffman;
        private System.Windows.Forms.RadioButton rbZivLempel;
        private System.Windows.Forms.RadioButton rbDPC;
        private System.Windows.Forms.RadioButton rbBitplaneRLC;
        private System.Windows.Forms.RadioButton rbJPEG2000;
        private System.Windows.Forms.GroupBox grpHuffman;
        private System.Windows.Forms.GroupBox grpBitplaneRLC;
        private System.Windows.Forms.GroupBox grpParameters;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.ComboBox comboBox4;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.ComboBox comboBox3;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.ComboBox comboBox2;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.ComboBox comboBox1;
        private System.Windows.Forms.Button btnHelp;
        private System.Windows.Forms.Button btnSaveCompressedData;
        private System.Windows.Forms.Button btnCancel;
        private System.Windows.Forms.Button btnReset;
        private System.Windows.Forms.Button btnApply;
    }
}
