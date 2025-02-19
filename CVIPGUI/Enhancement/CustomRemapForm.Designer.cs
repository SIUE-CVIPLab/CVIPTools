namespace CVIPGUI
{
    partial class CustomRemapForm
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

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(CustomRemapForm));
            this.lblCurrentX = new System.Windows.Forms.Label();
            this.txtCurrentX = new System.Windows.Forms.Label();
            this.lblCurrentY = new System.Windows.Forms.Label();
            this.txtCurrentY = new System.Windows.Forms.Label();
            this.lblRemappedValue = new System.Windows.Forms.Label();
            this.lblYAxis255 = new System.Windows.Forms.Label();
            this.lblYAxis224 = new System.Windows.Forms.Label();
            this.lblYAxis192 = new System.Windows.Forms.Label();
            this.lblYAxis160 = new System.Windows.Forms.Label();
            this.lblYAxis128 = new System.Windows.Forms.Label();
            this.lblYAxis96 = new System.Windows.Forms.Label();
            this.lblYAxis64 = new System.Windows.Forms.Label();
            this.lblYAxis32 = new System.Windows.Forms.Label();
            this.lblYAxis0 = new System.Windows.Forms.Label();
            this.lblXAxis0 = new System.Windows.Forms.Label();
            this.lblXAxis32 = new System.Windows.Forms.Label();
            this.lblXAxis64 = new System.Windows.Forms.Label();
            this.lblXAxis96 = new System.Windows.Forms.Label();
            this.lblXAxis128 = new System.Windows.Forms.Label();
            this.lblXAxis160 = new System.Windows.Forms.Label();
            this.lblXAxis192 = new System.Windows.Forms.Label();
            this.lblXAxis224 = new System.Windows.Forms.Label();
            this.lblXAxis255 = new System.Windows.Forms.Label();
            this.lblOriginalValue = new System.Windows.Forms.Label();
            this.grpInterpolation = new System.Windows.Forms.GroupBox();
            this.rbLagrange = new System.Windows.Forms.RadioButton();
            this.rbLinear = new System.Windows.Forms.RadioButton();
            this.grpBand = new System.Windows.Forms.GroupBox();
            this.rbBlue = new System.Windows.Forms.RadioButton();
            this.rbGreen = new System.Windows.Forms.RadioButton();
            this.rbRed = new System.Windows.Forms.RadioButton();
            this.rbAll = new System.Windows.Forms.RadioButton();
            this.grpAddPoints = new System.Windows.Forms.GroupBox();
            this.btnAdd = new System.Windows.Forms.Button();
            this.cboAddY = new System.Windows.Forms.ComboBox();
            this.lblAddY = new System.Windows.Forms.Label();
            this.cboAddX = new System.Windows.Forms.ComboBox();
            this.lblAddX = new System.Windows.Forms.Label();
            this.btnOpenMapFile = new System.Windows.Forms.Button();
            this.btnSave = new System.Windows.Forms.Button();
            this.btnClose = new System.Windows.Forms.Button();
            this.btnApply = new System.Windows.Forms.Button();
            this.grpInterpolation.SuspendLayout();
            this.grpBand.SuspendLayout();
            this.grpAddPoints.SuspendLayout();
            this.SuspendLayout();
            // 
            // lblCurrentX
            // 
            this.lblCurrentX.AutoSize = true;
            this.lblCurrentX.Location = new System.Drawing.Point(206, 15);
            this.lblCurrentX.Name = "lblCurrentX";
            this.lblCurrentX.Size = new System.Drawing.Size(20, 13);
            this.lblCurrentX.TabIndex = 0;
            this.lblCurrentX.Text = "X :";
            // 
            // txtCurrentX
            // 
            this.txtCurrentX.Location = new System.Drawing.Point(226, 15);
            this.txtCurrentX.Name = "txtCurrentX";
            this.txtCurrentX.Size = new System.Drawing.Size(30, 13);
            this.txtCurrentX.TabIndex = 1;
            this.txtCurrentX.Text = "0";
            // 
            // lblCurrentY
            // 
            this.lblCurrentY.AutoSize = true;
            this.lblCurrentY.Location = new System.Drawing.Point(263, 15);
            this.lblCurrentY.Name = "lblCurrentY";
            this.lblCurrentY.Size = new System.Drawing.Size(20, 13);
            this.lblCurrentY.TabIndex = 2;
            this.lblCurrentY.Text = "Y :";
            // 
            // txtCurrentY
            // 
            this.txtCurrentY.Location = new System.Drawing.Point(284, 15);
            this.txtCurrentY.Name = "txtCurrentY";
            this.txtCurrentY.Size = new System.Drawing.Size(30, 13);
            this.txtCurrentY.TabIndex = 3;
            this.txtCurrentY.Text = "0";
            // 
            // lblRemappedValue
            // 
            this.lblRemappedValue.AutoSize = true;
            this.lblRemappedValue.Location = new System.Drawing.Point(12, 62);
            this.lblRemappedValue.Name = "lblRemappedValue";
            this.lblRemappedValue.Size = new System.Drawing.Size(16, 208);
            this.lblRemappedValue.TabIndex = 4;
            this.lblRemappedValue.Text = "R\r\ne\r\nm\r\na\r\np\r\np\r\ne\r\nd\r\n\r\nV\r\na\r\nl\r\nu\r\ne \r\n\r\nY";
            // 
            // lblYAxis255
            // 
            this.lblYAxis255.AutoSize = true;
            this.lblYAxis255.Location = new System.Drawing.Point(32, 34);
            this.lblYAxis255.Name = "lblYAxis255";
            this.lblYAxis255.Size = new System.Drawing.Size(25, 13);
            this.lblYAxis255.TabIndex = 5;
            this.lblYAxis255.Text = "255";
            this.lblYAxis255.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // lblYAxis224
            // 
            this.lblYAxis224.AutoSize = true;
            this.lblYAxis224.Location = new System.Drawing.Point(32, 65);
            this.lblYAxis224.Name = "lblYAxis224";
            this.lblYAxis224.Size = new System.Drawing.Size(25, 13);
            this.lblYAxis224.TabIndex = 6;
            this.lblYAxis224.Text = "224";
            this.lblYAxis224.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // lblYAxis192
            // 
            this.lblYAxis192.AutoSize = true;
            this.lblYAxis192.Location = new System.Drawing.Point(32, 97);
            this.lblYAxis192.Name = "lblYAxis192";
            this.lblYAxis192.Size = new System.Drawing.Size(25, 13);
            this.lblYAxis192.TabIndex = 7;
            this.lblYAxis192.Text = "192";
            this.lblYAxis192.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // lblYAxis160
            // 
            this.lblYAxis160.AutoSize = true;
            this.lblYAxis160.Location = new System.Drawing.Point(32, 129);
            this.lblYAxis160.Name = "lblYAxis160";
            this.lblYAxis160.Size = new System.Drawing.Size(25, 13);
            this.lblYAxis160.TabIndex = 8;
            this.lblYAxis160.Text = "160";
            this.lblYAxis160.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // lblYAxis128
            // 
            this.lblYAxis128.AutoSize = true;
            this.lblYAxis128.Location = new System.Drawing.Point(32, 161);
            this.lblYAxis128.Name = "lblYAxis128";
            this.lblYAxis128.Size = new System.Drawing.Size(25, 13);
            this.lblYAxis128.TabIndex = 9;
            this.lblYAxis128.Text = "128";
            this.lblYAxis128.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // lblYAxis96
            // 
            this.lblYAxis96.AutoSize = true;
            this.lblYAxis96.Location = new System.Drawing.Point(38, 193);
            this.lblYAxis96.Name = "lblYAxis96";
            this.lblYAxis96.Size = new System.Drawing.Size(19, 13);
            this.lblYAxis96.TabIndex = 10;
            this.lblYAxis96.Text = "96";
            this.lblYAxis96.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // lblYAxis64
            // 
            this.lblYAxis64.AutoSize = true;
            this.lblYAxis64.Location = new System.Drawing.Point(38, 225);
            this.lblYAxis64.Name = "lblYAxis64";
            this.lblYAxis64.Size = new System.Drawing.Size(19, 13);
            this.lblYAxis64.TabIndex = 11;
            this.lblYAxis64.Text = "64";
            this.lblYAxis64.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // lblYAxis32
            // 
            this.lblYAxis32.AutoSize = true;
            this.lblYAxis32.Location = new System.Drawing.Point(38, 257);
            this.lblYAxis32.Name = "lblYAxis32";
            this.lblYAxis32.Size = new System.Drawing.Size(19, 13);
            this.lblYAxis32.TabIndex = 12;
            this.lblYAxis32.Text = "32";
            this.lblYAxis32.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // lblYAxis0
            // 
            this.lblYAxis0.AutoSize = true;
            this.lblYAxis0.Location = new System.Drawing.Point(44, 289);
            this.lblYAxis0.Name = "lblYAxis0";
            this.lblYAxis0.Size = new System.Drawing.Size(13, 13);
            this.lblYAxis0.TabIndex = 13;
            this.lblYAxis0.Text = "0";
            this.lblYAxis0.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // lblXAxis0
            // 
            this.lblXAxis0.AutoSize = true;
            this.lblXAxis0.Location = new System.Drawing.Point(54, 302);
            this.lblXAxis0.Name = "lblXAxis0";
            this.lblXAxis0.Size = new System.Drawing.Size(13, 13);
            this.lblXAxis0.TabIndex = 14;
            this.lblXAxis0.Text = "0";
            this.lblXAxis0.TextAlign = System.Drawing.ContentAlignment.TopCenter;
            // 
            // lblXAxis32
            // 
            this.lblXAxis32.AutoSize = true;
            this.lblXAxis32.Location = new System.Drawing.Point(83, 302);
            this.lblXAxis32.Name = "lblXAxis32";
            this.lblXAxis32.Size = new System.Drawing.Size(19, 13);
            this.lblXAxis32.TabIndex = 15;
            this.lblXAxis32.Text = "32";
            this.lblXAxis32.TextAlign = System.Drawing.ContentAlignment.TopCenter;
            // 
            // lblXAxis64
            // 
            this.lblXAxis64.AutoSize = true;
            this.lblXAxis64.Location = new System.Drawing.Point(115, 302);
            this.lblXAxis64.Name = "lblXAxis64";
            this.lblXAxis64.Size = new System.Drawing.Size(19, 13);
            this.lblXAxis64.TabIndex = 16;
            this.lblXAxis64.Text = "64";
            this.lblXAxis64.TextAlign = System.Drawing.ContentAlignment.TopCenter;
            // 
            // lblXAxis96
            // 
            this.lblXAxis96.AutoSize = true;
            this.lblXAxis96.Location = new System.Drawing.Point(147, 302);
            this.lblXAxis96.Name = "lblXAxis96";
            this.lblXAxis96.Size = new System.Drawing.Size(19, 13);
            this.lblXAxis96.TabIndex = 17;
            this.lblXAxis96.Text = "96";
            this.lblXAxis96.TextAlign = System.Drawing.ContentAlignment.TopCenter;
            // 
            // lblXAxis128
            // 
            this.lblXAxis128.AutoSize = true;
            this.lblXAxis128.Location = new System.Drawing.Point(176, 302);
            this.lblXAxis128.Name = "lblXAxis128";
            this.lblXAxis128.Size = new System.Drawing.Size(25, 13);
            this.lblXAxis128.TabIndex = 18;
            this.lblXAxis128.Text = "128";
            this.lblXAxis128.TextAlign = System.Drawing.ContentAlignment.TopCenter;
            // 
            // lblXAxis160
            // 
            this.lblXAxis160.AutoSize = true;
            this.lblXAxis160.Location = new System.Drawing.Point(208, 302);
            this.lblXAxis160.Name = "lblXAxis160";
            this.lblXAxis160.Size = new System.Drawing.Size(25, 13);
            this.lblXAxis160.TabIndex = 19;
            this.lblXAxis160.Text = "160";
            this.lblXAxis160.TextAlign = System.Drawing.ContentAlignment.TopCenter;
            // 
            // lblXAxis192
            // 
            this.lblXAxis192.AutoSize = true;
            this.lblXAxis192.Location = new System.Drawing.Point(240, 302);
            this.lblXAxis192.Name = "lblXAxis192";
            this.lblXAxis192.Size = new System.Drawing.Size(25, 13);
            this.lblXAxis192.TabIndex = 20;
            this.lblXAxis192.Text = "192";
            this.lblXAxis192.TextAlign = System.Drawing.ContentAlignment.TopCenter;
            // 
            // lblXAxis224
            // 
            this.lblXAxis224.AutoSize = true;
            this.lblXAxis224.Location = new System.Drawing.Point(272, 302);
            this.lblXAxis224.Name = "lblXAxis224";
            this.lblXAxis224.Size = new System.Drawing.Size(25, 13);
            this.lblXAxis224.TabIndex = 21;
            this.lblXAxis224.Text = "224";
            this.lblXAxis224.TextAlign = System.Drawing.ContentAlignment.TopCenter;
            // 
            // lblXAxis255
            // 
            this.lblXAxis255.AutoSize = true;
            this.lblXAxis255.Location = new System.Drawing.Point(303, 302);
            this.lblXAxis255.Name = "lblXAxis255";
            this.lblXAxis255.Size = new System.Drawing.Size(25, 13);
            this.lblXAxis255.TabIndex = 22;
            this.lblXAxis255.Text = "255";
            this.lblXAxis255.TextAlign = System.Drawing.ContentAlignment.TopCenter;
            // 
            // lblOriginalValue
            // 
            this.lblOriginalValue.AutoSize = true;
            this.lblOriginalValue.Location = new System.Drawing.Point(139, 326);
            this.lblOriginalValue.Name = "lblOriginalValue";
            this.lblOriginalValue.Size = new System.Drawing.Size(82, 13);
            this.lblOriginalValue.TabIndex = 23;
            this.lblOriginalValue.Text = "Original Value X";
            // 
            // grpInterpolation
            // 
            this.grpInterpolation.Controls.Add(this.rbLagrange);
            this.grpInterpolation.Controls.Add(this.rbLinear);
            this.grpInterpolation.Location = new System.Drawing.Point(331, 14);
            this.grpInterpolation.Name = "grpInterpolation";
            this.grpInterpolation.Size = new System.Drawing.Size(169, 77);
            this.grpInterpolation.TabIndex = 24;
            this.grpInterpolation.TabStop = false;
            this.grpInterpolation.Text = "Interpolation Method";
            // 
            // rbLagrange
            // 
            this.rbLagrange.AutoSize = true;
            this.rbLagrange.Location = new System.Drawing.Point(18, 41);
            this.rbLagrange.Name = "rbLagrange";
            this.rbLagrange.Size = new System.Drawing.Size(131, 17);
            this.rbLagrange.TabIndex = 1;
            this.rbLagrange.Text = "Lagrange Interpolation";
            this.rbLagrange.UseVisualStyleBackColor = true;
            this.rbLagrange.CheckedChanged += new System.EventHandler(this.rbInterpolationMethod_CheckedChanged);
            // 
            // rbLinear
            // 
            this.rbLinear.AutoSize = true;
            this.rbLinear.Checked = true;
            this.rbLinear.Location = new System.Drawing.Point(18, 18);
            this.rbLinear.Name = "rbLinear";
            this.rbLinear.Size = new System.Drawing.Size(54, 17);
            this.rbLinear.TabIndex = 0;
            this.rbLinear.TabStop = true;
            this.rbLinear.Text = "Linear";
            this.rbLinear.UseVisualStyleBackColor = true;
            this.rbLinear.CheckedChanged += new System.EventHandler(this.rbInterpolationMethod_CheckedChanged);
            // 
            // grpBand
            // 
            this.grpBand.Controls.Add(this.rbBlue);
            this.grpBand.Controls.Add(this.rbGreen);
            this.grpBand.Controls.Add(this.rbRed);
            this.grpBand.Controls.Add(this.rbAll);
            this.grpBand.Location = new System.Drawing.Point(331, 97);
            this.grpBand.Name = "grpBand";
            this.grpBand.Size = new System.Drawing.Size(169, 77);
            this.grpBand.TabIndex = 25;
            this.grpBand.TabStop = false;
            this.grpBand.Text = "Band";
            // 
            // rbBlue
            // 
            this.rbBlue.AutoSize = true;
            this.rbBlue.Location = new System.Drawing.Point(118, 38);
            this.rbBlue.Name = "rbBlue";
            this.rbBlue.Size = new System.Drawing.Size(46, 17);
            this.rbBlue.TabIndex = 3;
            this.rbBlue.Text = "Blue";
            this.rbBlue.UseVisualStyleBackColor = true;
            this.rbBlue.CheckedChanged += new System.EventHandler(this.rbRGB_CheckedChanged);
            // 
            // rbGreen
            // 
            this.rbGreen.AutoSize = true;
            this.rbGreen.Location = new System.Drawing.Point(61, 38);
            this.rbGreen.Name = "rbGreen";
            this.rbGreen.Size = new System.Drawing.Size(54, 17);
            this.rbGreen.TabIndex = 2;
            this.rbGreen.Text = "Green";
            this.rbGreen.UseVisualStyleBackColor = true;
            this.rbGreen.CheckedChanged += new System.EventHandler(this.rbRGB_CheckedChanged);
            // 
            // rbRed
            // 
            this.rbRed.AutoSize = true;
            this.rbRed.Location = new System.Drawing.Point(10, 38);
            this.rbRed.Name = "rbRed";
            this.rbRed.Size = new System.Drawing.Size(45, 17);
            this.rbRed.TabIndex = 1;
            this.rbRed.Text = "Red";
            this.rbRed.UseVisualStyleBackColor = true;
            this.rbRed.CheckedChanged += new System.EventHandler(this.rbRGB_CheckedChanged);
            // 
            // rbAll
            // 
            this.rbAll.AutoSize = true;
            this.rbAll.Checked = true;
            this.rbAll.Location = new System.Drawing.Point(10, 19);
            this.rbAll.Name = "rbAll";
            this.rbAll.Size = new System.Drawing.Size(36, 17);
            this.rbAll.TabIndex = 0;
            this.rbAll.TabStop = true;
            this.rbAll.Text = "All";
            this.rbAll.UseVisualStyleBackColor = true;
            this.rbAll.CheckedChanged += new System.EventHandler(this.rbRGB_CheckedChanged);
            // 
            // grpAddPoints
            // 
            this.grpAddPoints.Controls.Add(this.btnAdd);
            this.grpAddPoints.Controls.Add(this.cboAddY);
            this.grpAddPoints.Controls.Add(this.lblAddY);
            this.grpAddPoints.Controls.Add(this.cboAddX);
            this.grpAddPoints.Controls.Add(this.lblAddX);
            this.grpAddPoints.Location = new System.Drawing.Point(331, 180);
            this.grpAddPoints.Name = "grpAddPoints";
            this.grpAddPoints.Size = new System.Drawing.Size(169, 77);
            this.grpAddPoints.TabIndex = 26;
            this.grpAddPoints.TabStop = false;
            this.grpAddPoints.Text = "Add points";
            // 
            // btnAdd
            // 
            this.btnAdd.Location = new System.Drawing.Point(120, 37);
            this.btnAdd.Name = "btnAdd";
            this.btnAdd.Size = new System.Drawing.Size(36, 21);
            this.btnAdd.TabIndex = 4;
            this.btnAdd.Text = "Add";
            this.btnAdd.UseVisualStyleBackColor = true;
            this.btnAdd.Click += new System.EventHandler(this.btnAdd_Click);
            // 
            // cboAddY
            // 
            this.cboAddY.FormattingEnabled = true;
            this.cboAddY.Items.AddRange(new object[] {
            "0",
            "32",
            "64",
            "96",
            "128",
            "160",
            "192",
            "224",
            "255"});
            this.cboAddY.Location = new System.Drawing.Point(49, 49);
            this.cboAddY.Name = "cboAddY";
            this.cboAddY.Size = new System.Drawing.Size(58, 21);
            this.cboAddY.TabIndex = 3;
            this.cboAddY.Text = "128";
            this.cboAddY.Validating += new System.ComponentModel.CancelEventHandler(this.cboUIntVal_Validating);
            // 
            // lblAddY
            // 
            this.lblAddY.AutoSize = true;
            this.lblAddY.Location = new System.Drawing.Point(7, 53);
            this.lblAddY.Name = "lblAddY";
            this.lblAddY.Size = new System.Drawing.Size(20, 13);
            this.lblAddY.TabIndex = 2;
            this.lblAddY.Text = "Y :";
            // 
            // cboAddX
            // 
            this.cboAddX.FormattingEnabled = true;
            this.cboAddX.Items.AddRange(new object[] {
            "0",
            "32",
            "64",
            "96",
            "128",
            "160",
            "192",
            "224",
            "255"});
            this.cboAddX.Location = new System.Drawing.Point(49, 21);
            this.cboAddX.Name = "cboAddX";
            this.cboAddX.Size = new System.Drawing.Size(58, 21);
            this.cboAddX.TabIndex = 1;
            this.cboAddX.Text = "128";
            this.cboAddX.Validating += new System.ComponentModel.CancelEventHandler(this.cboUIntVal_Validating);
            // 
            // lblAddX
            // 
            this.lblAddX.AutoSize = true;
            this.lblAddX.Location = new System.Drawing.Point(7, 25);
            this.lblAddX.Name = "lblAddX";
            this.lblAddX.Size = new System.Drawing.Size(20, 13);
            this.lblAddX.TabIndex = 0;
            this.lblAddX.Text = "X :";
            // 
            // btnOpenMapFile
            // 
            this.btnOpenMapFile.Location = new System.Drawing.Point(349, 263);
            this.btnOpenMapFile.Name = "btnOpenMapFile";
            this.btnOpenMapFile.Size = new System.Drawing.Size(101, 21);
            this.btnOpenMapFile.TabIndex = 27;
            this.btnOpenMapFile.Text = "Open a map file";
            this.btnOpenMapFile.UseVisualStyleBackColor = true;
            this.btnOpenMapFile.Click += new System.EventHandler(this.btnOpenMapFile_Click);
            // 
            // btnSave
            // 
            this.btnSave.Location = new System.Drawing.Point(349, 295);
            this.btnSave.Name = "btnSave";
            this.btnSave.Size = new System.Drawing.Size(51, 21);
            this.btnSave.TabIndex = 28;
            this.btnSave.Text = "Save";
            this.btnSave.UseVisualStyleBackColor = true;
            this.btnSave.Click += new System.EventHandler(this.btnSave_Click);
            // 
            // btnClose
            // 
            this.btnClose.BackColor = System.Drawing.Color.OrangeRed;
            this.btnClose.CausesValidation = false;
            this.btnClose.Location = new System.Drawing.Point(366, 326);
            this.btnClose.Name = "btnClose";
            this.btnClose.Size = new System.Drawing.Size(60, 26);
            this.btnClose.TabIndex = 29;
            this.btnClose.Text = "Close";
            this.btnClose.UseVisualStyleBackColor = false;
            this.btnClose.Click += new System.EventHandler(this.btnClose_Click);
            // 
            // btnApply
            // 
            this.btnApply.BackColor = System.Drawing.Color.LimeGreen;
            this.btnApply.ForeColor = System.Drawing.Color.White;
            this.btnApply.Location = new System.Drawing.Point(440, 326);
            this.btnApply.Name = "btnApply";
            this.btnApply.Size = new System.Drawing.Size(60, 26);
            this.btnApply.TabIndex = 30;
            this.btnApply.Text = "Apply";
            this.btnApply.UseVisualStyleBackColor = false;
            this.btnApply.Click += new System.EventHandler(this.btnApply_Click);
            // 
            // CustomRemapForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.CausesValidation = false;
            this.ClientSize = new System.Drawing.Size(510, 359);
            this.Controls.Add(this.btnApply);
            this.Controls.Add(this.btnClose);
            this.Controls.Add(this.btnSave);
            this.Controls.Add(this.btnOpenMapFile);
            this.Controls.Add(this.grpAddPoints);
            this.Controls.Add(this.grpBand);
            this.Controls.Add(this.grpInterpolation);
            this.Controls.Add(this.lblOriginalValue);
            this.Controls.Add(this.lblXAxis255);
            this.Controls.Add(this.lblXAxis224);
            this.Controls.Add(this.lblXAxis192);
            this.Controls.Add(this.lblXAxis160);
            this.Controls.Add(this.lblXAxis128);
            this.Controls.Add(this.lblXAxis96);
            this.Controls.Add(this.lblXAxis64);
            this.Controls.Add(this.lblXAxis32);
            this.Controls.Add(this.lblXAxis0);
            this.Controls.Add(this.lblYAxis0);
            this.Controls.Add(this.lblYAxis32);
            this.Controls.Add(this.lblYAxis64);
            this.Controls.Add(this.lblYAxis96);
            this.Controls.Add(this.lblYAxis128);
            this.Controls.Add(this.lblYAxis160);
            this.Controls.Add(this.lblYAxis192);
            this.Controls.Add(this.lblYAxis224);
            this.Controls.Add(this.lblYAxis255);
            this.Controls.Add(this.lblRemappedValue);
            this.Controls.Add(this.txtCurrentY);
            this.Controls.Add(this.lblCurrentY);
            this.Controls.Add(this.txtCurrentX);
            this.Controls.Add(this.lblCurrentX);
            this.DoubleBuffered = true;
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.Fixed3D;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "CustomRemapForm";
            this.ShowInTaskbar = false;
            this.Text = "Pseudocolor";
            this.grpInterpolation.ResumeLayout(false);
            this.grpInterpolation.PerformLayout();
            this.grpBand.ResumeLayout(false);
            this.grpBand.PerformLayout();
            this.grpAddPoints.ResumeLayout(false);
            this.grpAddPoints.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label lblCurrentX;
        private System.Windows.Forms.Label txtCurrentX;
        private System.Windows.Forms.Label lblCurrentY;
        private System.Windows.Forms.Label txtCurrentY;
        private System.Windows.Forms.Label lblRemappedValue;
        private System.Windows.Forms.Label lblYAxis255;
        private System.Windows.Forms.Label lblYAxis224;
        private System.Windows.Forms.Label lblYAxis192;
        private System.Windows.Forms.Label lblYAxis160;
        private System.Windows.Forms.Label lblYAxis128;
        private System.Windows.Forms.Label lblYAxis96;
        private System.Windows.Forms.Label lblYAxis64;
        private System.Windows.Forms.Label lblYAxis32;
        private System.Windows.Forms.Label lblYAxis0;
        private System.Windows.Forms.Label lblXAxis0;
        private System.Windows.Forms.Label lblXAxis32;
        private System.Windows.Forms.Label lblXAxis64;
        private System.Windows.Forms.Label lblXAxis96;
        private System.Windows.Forms.Label lblXAxis128;
        private System.Windows.Forms.Label lblXAxis160;
        private System.Windows.Forms.Label lblXAxis192;
        private System.Windows.Forms.Label lblXAxis224;
        private System.Windows.Forms.Label lblXAxis255;
        private System.Windows.Forms.Label lblOriginalValue;
        private System.Windows.Forms.GroupBox grpInterpolation;
        private System.Windows.Forms.RadioButton rbLagrange;
        private System.Windows.Forms.RadioButton rbLinear;
        private System.Windows.Forms.GroupBox grpBand;
        private System.Windows.Forms.RadioButton rbBlue;
        private System.Windows.Forms.RadioButton rbGreen;
        private System.Windows.Forms.RadioButton rbRed;
        private System.Windows.Forms.RadioButton rbAll;
        private System.Windows.Forms.GroupBox grpAddPoints;
        private System.Windows.Forms.Button btnAdd;
        private System.Windows.Forms.ComboBox cboAddY;
        private System.Windows.Forms.Label lblAddY;
        private System.Windows.Forms.ComboBox cboAddX;
        private System.Windows.Forms.Label lblAddX;
        private System.Windows.Forms.Button btnOpenMapFile;
        private System.Windows.Forms.Button btnSave;
        private System.Windows.Forms.Button btnClose;
        private System.Windows.Forms.Button btnApply;
    }
}
