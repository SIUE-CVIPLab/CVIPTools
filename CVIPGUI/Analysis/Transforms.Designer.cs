namespace CVIPGUI.Analysis
{
    partial class Transforms
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
            this.rbDCT = new System.Windows.Forms.RadioButton();
            this.rbFFT = new System.Windows.Forms.RadioButton();
            this.rbHaar = new System.Windows.Forms.RadioButton();
            this.rbWalsh = new System.Windows.Forms.RadioButton();
            this.rbHadamard = new System.Windows.Forms.RadioButton();
            this.rbWavelet = new System.Windows.Forms.RadioButton();
            this.rbLowPass = new System.Windows.Forms.RadioButton();
            this.rbHighPass = new System.Windows.Forms.RadioButton();
            this.rbBandPass = new System.Windows.Forms.RadioButton();
            this.rbBandReject = new System.Windows.Forms.RadioButton();
            this.rbHighFreqEmphasis = new System.Windows.Forms.RadioButton();
            this.rbNotch = new System.Windows.Forms.RadioButton();
            this.rbFFTPhase = new System.Windows.Forms.RadioButton();
            this.rbFFTMagnitude = new System.Windows.Forms.RadioButton();
            this.grpTransforms = new System.Windows.Forms.GroupBox();
            this.pnlTransforms = new System.Windows.Forms.Panel();
            this.pnlForward = new System.Windows.Forms.Panel();
            this.cboDecomposition = new System.Windows.Forms.ComboBox();
            this.lblDecomposition = new System.Windows.Forms.Label();
            this.cboBasis = new System.Windows.Forms.ComboBox();
            this.lblBasis = new System.Windows.Forms.Label();
            this.cboBlockSize = new System.Windows.Forms.ComboBox();
            this.lblBlockSize = new System.Windows.Forms.Label();
            this.rbInverse = new System.Windows.Forms.RadioButton();
            this.rbForward = new System.Windows.Forms.RadioButton();
            this.grpFilters = new System.Windows.Forms.GroupBox();
            this.pnlNotch = new System.Windows.Forms.Panel();
            this.btnAddNotch = new System.Windows.Forms.Button();
            this.btnRedoNotch = new System.Windows.Forms.Button();
            this.cboNotchSize = new System.Windows.Forms.ComboBox();
            this.lblNotchSize = new System.Windows.Forms.Label();
            this.txtNotchRow = new System.Windows.Forms.TextBox();
            this.lblNotchRow = new System.Windows.Forms.Label();
            this.txtNotchCol = new System.Windows.Forms.TextBox();
            this.lblNotchCol = new System.Windows.Forms.Label();
            this.cboPoint = new System.Windows.Forms.ComboBox();
            this.lblPoint = new System.Windows.Forms.Label();
            this.pnlFilters = new System.Windows.Forms.Panel();
            this.cboEmphasisOffset = new System.Windows.Forms.ComboBox();
            this.lblEmphasisOffset = new System.Windows.Forms.Label();
            this.cboCutoffHigh = new System.Windows.Forms.ComboBox();
            this.lblCutoffHigh = new System.Windows.Forms.Label();
            this.cboCutoffLow = new System.Windows.Forms.ComboBox();
            this.lblCutoffLow = new System.Windows.Forms.Label();
            this.cboFilterOrder = new System.Windows.Forms.ComboBox();
            this.lblFilterOrder = new System.Windows.Forms.Label();
            this.cboFilterType = new System.Windows.Forms.ComboBox();
            this.lblFilterType = new System.Windows.Forms.Label();
            this.chkKeepDC = new System.Windows.Forms.CheckBox();
            this.cboCutoff = new System.Windows.Forms.ComboBox();
            this.lblCutoff = new System.Windows.Forms.Label();
            this.pnlFFTMagnitude = new System.Windows.Forms.Panel();
            this.rbNoTranslate = new System.Windows.Forms.RadioButton();
            this.rbTranslate = new System.Windows.Forms.RadioButton();
            this.btnHelp = new System.Windows.Forms.Button();
            this.btnCancel = new System.Windows.Forms.Button();
            this.btnReset = new System.Windows.Forms.Button();
            this.btnApply = new System.Windows.Forms.Button();
            this.Note1 = new System.Windows.Forms.Label();
            this.Note2 = new System.Windows.Forms.Label();
            this.grpTransforms.SuspendLayout();
            this.pnlTransforms.SuspendLayout();
            this.pnlForward.SuspendLayout();
            this.grpFilters.SuspendLayout();
            this.pnlNotch.SuspendLayout();
            this.pnlFilters.SuspendLayout();
            this.pnlFFTMagnitude.SuspendLayout();
            this.SuspendLayout();
            // 
            // rbDCT
            // 
            this.rbDCT.AutoSize = true;
            this.rbDCT.Location = new System.Drawing.Point(20, 26);
            this.rbDCT.Name = "rbDCT";
            this.rbDCT.Size = new System.Drawing.Size(47, 17);
            this.rbDCT.TabIndex = 0;
            this.rbDCT.Text = "DCT";
            this.rbDCT.UseVisualStyleBackColor = true;
            this.rbDCT.CheckedChanged += new System.EventHandler(this.rbTransforms_CheckedChanged);
            // 
            // rbFFT
            // 
            this.rbFFT.AutoSize = true;
            this.rbFFT.Checked = true;
            this.rbFFT.Location = new System.Drawing.Point(20, 49);
            this.rbFFT.Name = "rbFFT";
            this.rbFFT.Size = new System.Drawing.Size(44, 17);
            this.rbFFT.TabIndex = 1;
            this.rbFFT.TabStop = true;
            this.rbFFT.Text = "FFT";
            this.rbFFT.UseVisualStyleBackColor = true;
            this.rbFFT.CheckedChanged += new System.EventHandler(this.rbTransforms_CheckedChanged);
            // 
            // rbHaar
            // 
            this.rbHaar.AutoSize = true;
            this.rbHaar.Location = new System.Drawing.Point(20, 72);
            this.rbHaar.Name = "rbHaar";
            this.rbHaar.Size = new System.Drawing.Size(48, 17);
            this.rbHaar.TabIndex = 2;
            this.rbHaar.Text = "Haar";
            this.rbHaar.UseVisualStyleBackColor = true;
            this.rbHaar.CheckedChanged += new System.EventHandler(this.rbTransforms_CheckedChanged);
            // 
            // rbWalsh
            // 
            this.rbWalsh.AutoSize = true;
            this.rbWalsh.Location = new System.Drawing.Point(20, 95);
            this.rbWalsh.Name = "rbWalsh";
            this.rbWalsh.Size = new System.Drawing.Size(55, 17);
            this.rbWalsh.TabIndex = 3;
            this.rbWalsh.Text = "Walsh";
            this.rbWalsh.UseVisualStyleBackColor = true;
            this.rbWalsh.CheckedChanged += new System.EventHandler(this.rbTransforms_CheckedChanged);
            // 
            // rbHadamard
            // 
            this.rbHadamard.AutoSize = true;
            this.rbHadamard.Location = new System.Drawing.Point(20, 118);
            this.rbHadamard.Name = "rbHadamard";
            this.rbHadamard.Size = new System.Drawing.Size(74, 17);
            this.rbHadamard.TabIndex = 4;
            this.rbHadamard.Text = "Hadamard";
            this.rbHadamard.UseVisualStyleBackColor = true;
            this.rbHadamard.CheckedChanged += new System.EventHandler(this.rbTransforms_CheckedChanged);
            // 
            // rbWavelet
            // 
            this.rbWavelet.AutoSize = true;
            this.rbWavelet.Location = new System.Drawing.Point(20, 141);
            this.rbWavelet.Name = "rbWavelet";
            this.rbWavelet.Size = new System.Drawing.Size(65, 17);
            this.rbWavelet.TabIndex = 5;
            this.rbWavelet.Text = "Wavelet";
            this.rbWavelet.UseVisualStyleBackColor = true;
            this.rbWavelet.CheckedChanged += new System.EventHandler(this.rbTransforms_CheckedChanged);
            // 
            // rbLowPass
            // 
            this.rbLowPass.AutoSize = true;
            this.rbLowPass.Location = new System.Drawing.Point(20, 201);
            this.rbLowPass.Name = "rbLowPass";
            this.rbLowPass.Size = new System.Drawing.Size(71, 17);
            this.rbLowPass.TabIndex = 6;
            this.rbLowPass.Text = "Low Pass";
            this.rbLowPass.UseVisualStyleBackColor = true;
            this.rbLowPass.CheckedChanged += new System.EventHandler(this.rbTransforms_CheckedChanged);
            // 
            // rbHighPass
            // 
            this.rbHighPass.AutoSize = true;
            this.rbHighPass.Location = new System.Drawing.Point(20, 224);
            this.rbHighPass.Name = "rbHighPass";
            this.rbHighPass.Size = new System.Drawing.Size(73, 17);
            this.rbHighPass.TabIndex = 7;
            this.rbHighPass.Text = "High Pass";
            this.rbHighPass.UseVisualStyleBackColor = true;
            this.rbHighPass.CheckedChanged += new System.EventHandler(this.rbTransforms_CheckedChanged);
            // 
            // rbBandPass
            // 
            this.rbBandPass.AutoSize = true;
            this.rbBandPass.Location = new System.Drawing.Point(20, 247);
            this.rbBandPass.Name = "rbBandPass";
            this.rbBandPass.Size = new System.Drawing.Size(76, 17);
            this.rbBandPass.TabIndex = 8;
            this.rbBandPass.Text = "Band Pass";
            this.rbBandPass.UseVisualStyleBackColor = true;
            this.rbBandPass.CheckedChanged += new System.EventHandler(this.rbTransforms_CheckedChanged);
            // 
            // rbBandReject
            // 
            this.rbBandReject.AutoSize = true;
            this.rbBandReject.Location = new System.Drawing.Point(20, 270);
            this.rbBandReject.Name = "rbBandReject";
            this.rbBandReject.Size = new System.Drawing.Size(84, 17);
            this.rbBandReject.TabIndex = 9;
            this.rbBandReject.Text = "Band Reject";
            this.rbBandReject.UseVisualStyleBackColor = true;
            this.rbBandReject.CheckedChanged += new System.EventHandler(this.rbTransforms_CheckedChanged);
            // 
            // rbHighFreqEmphasis
            // 
            this.rbHighFreqEmphasis.AutoSize = true;
            this.rbHighFreqEmphasis.Location = new System.Drawing.Point(20, 293);
            this.rbHighFreqEmphasis.Name = "rbHighFreqEmphasis";
            this.rbHighFreqEmphasis.Size = new System.Drawing.Size(115, 17);
            this.rbHighFreqEmphasis.TabIndex = 10;
            this.rbHighFreqEmphasis.Text = "High freq emphasis";
            this.rbHighFreqEmphasis.UseVisualStyleBackColor = true;
            this.rbHighFreqEmphasis.CheckedChanged += new System.EventHandler(this.rbTransforms_CheckedChanged);
            // 
            // rbNotch
            // 
            this.rbNotch.AutoSize = true;
            this.rbNotch.Location = new System.Drawing.Point(20, 316);
            this.rbNotch.Name = "rbNotch";
            this.rbNotch.Size = new System.Drawing.Size(54, 17);
            this.rbNotch.TabIndex = 11;
            this.rbNotch.Text = "Notch";
            this.rbNotch.UseVisualStyleBackColor = true;
            this.rbNotch.CheckedChanged += new System.EventHandler(this.rbTransforms_CheckedChanged);
            // 
            // rbFFTPhase
            // 
            this.rbFFTPhase.AutoSize = true;
            this.rbFFTPhase.Location = new System.Drawing.Point(20, 364);
            this.rbFFTPhase.Name = "rbFFTPhase";
            this.rbFFTPhase.Size = new System.Drawing.Size(169, 17);
            this.rbFFTPhase.TabIndex = 12;
            this.rbFFTPhase.Text = "Extract FFT Phase Only Image";
            this.rbFFTPhase.UseVisualStyleBackColor = true;
            this.rbFFTPhase.CheckedChanged += new System.EventHandler(this.rbTransforms_CheckedChanged);
            // 
            // rbFFTMagnitude
            // 
            this.rbFFTMagnitude.AutoSize = true;
            this.rbFFTMagnitude.Location = new System.Drawing.Point(20, 404);
            this.rbFFTMagnitude.Name = "rbFFTMagnitude";
            this.rbFFTMagnitude.Size = new System.Drawing.Size(189, 17);
            this.rbFFTMagnitude.TabIndex = 13;
            this.rbFFTMagnitude.Text = "Extract FFT Magnitude Only Image";
            this.rbFFTMagnitude.UseVisualStyleBackColor = true;
            this.rbFFTMagnitude.CheckedChanged += new System.EventHandler(this.rbTransforms_CheckedChanged);
            // 
            // grpTransforms
            // 
            this.grpTransforms.Controls.Add(this.pnlTransforms);
            this.grpTransforms.Location = new System.Drawing.Point(8, 8);
            this.grpTransforms.Name = "grpTransforms";
            this.grpTransforms.Size = new System.Drawing.Size(628, 165);
            this.grpTransforms.TabIndex = 14;
            this.grpTransforms.TabStop = false;
            this.grpTransforms.Text = "Transform";
            // 
            // pnlTransforms
            // 
            this.pnlTransforms.Controls.Add(this.pnlForward);
            this.pnlTransforms.Controls.Add(this.rbInverse);
            this.pnlTransforms.Controls.Add(this.rbForward);
            this.pnlTransforms.Location = new System.Drawing.Point(152, 16);
            this.pnlTransforms.Name = "pnlTransforms";
            this.pnlTransforms.Size = new System.Drawing.Size(306, 105);
            this.pnlTransforms.TabIndex = 0;
            // 
            // pnlForward
            // 
            this.pnlForward.Controls.Add(this.cboDecomposition);
            this.pnlForward.Controls.Add(this.lblDecomposition);
            this.pnlForward.Controls.Add(this.cboBasis);
            this.pnlForward.Controls.Add(this.lblBasis);
            this.pnlForward.Controls.Add(this.cboBlockSize);
            this.pnlForward.Controls.Add(this.lblBlockSize);
            this.pnlForward.Location = new System.Drawing.Point(16, 23);
            this.pnlForward.Name = "pnlForward";
            this.pnlForward.Size = new System.Drawing.Size(290, 47);
            this.pnlForward.TabIndex = 2;
            // 
            // cboDecomposition
            // 
            this.cboDecomposition.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cboDecomposition.FormattingEnabled = true;
            this.cboDecomposition.Items.AddRange(new object[] {
            "1",
            "2",
            "3",
            "4",
            "5",
            "6",
            "7",
            "8",
            "9"});
            this.cboDecomposition.Location = new System.Drawing.Point(241, 26);
            this.cboDecomposition.Name = "cboDecomposition";
            this.cboDecomposition.Size = new System.Drawing.Size(49, 21);
            this.cboDecomposition.TabIndex = 5;
            // 
            // lblDecomposition
            // 
            this.lblDecomposition.AutoSize = true;
            this.lblDecomposition.Location = new System.Drawing.Point(139, 30);
            this.lblDecomposition.Name = "lblDecomposition";
            this.lblDecomposition.Size = new System.Drawing.Size(101, 13);
            this.lblDecomposition.TabIndex = 4;
            this.lblDecomposition.Text = "Decomposition(1-9):";
            // 
            // cboBasis
            // 
            this.cboBasis.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cboBasis.FormattingEnabled = true;
            this.cboBasis.Items.AddRange(new object[] {
            "haar",
            "daub4"});
            this.cboBasis.Location = new System.Drawing.Point(59, 26);
            this.cboBasis.Name = "cboBasis";
            this.cboBasis.Size = new System.Drawing.Size(73, 21);
            this.cboBasis.TabIndex = 3;
            // 
            // lblBasis
            // 
            this.lblBasis.AutoSize = true;
            this.lblBasis.Location = new System.Drawing.Point(0, 30);
            this.lblBasis.Name = "lblBasis";
            this.lblBasis.Size = new System.Drawing.Size(35, 13);
            this.lblBasis.TabIndex = 2;
            this.lblBasis.Text = "Basis:";
            // 
            // cboBlockSize
            // 
            this.cboBlockSize.FormattingEnabled = true;
            this.cboBlockSize.Items.AddRange(new object[] {
            "2",
            "4",
            "8",
            "16",
            "32",
            "64",
            "128",
            "256",
            "512",
            "1024",
            "2048"});
            this.cboBlockSize.Location = new System.Drawing.Point(59, 0);
            this.cboBlockSize.Name = "cboBlockSize";
            this.cboBlockSize.Size = new System.Drawing.Size(73, 21);
            this.cboBlockSize.TabIndex = 1;
            this.cboBlockSize.Text = "256";
            this.cboBlockSize.Validating += new System.ComponentModel.CancelEventHandler(this.cboBlockSize_Validating);
            // 
            // lblBlockSize
            // 
            this.lblBlockSize.AutoSize = true;
            this.lblBlockSize.Location = new System.Drawing.Point(0, 4);
            this.lblBlockSize.Name = "lblBlockSize";
            this.lblBlockSize.Size = new System.Drawing.Size(58, 13);
            this.lblBlockSize.TabIndex = 0;
            this.lblBlockSize.Text = "Block size:";
            // 
            // rbInverse
            // 
            this.rbInverse.AutoSize = true;
            this.rbInverse.Location = new System.Drawing.Point(0, 88);
            this.rbInverse.Name = "rbInverse";
            this.rbInverse.Size = new System.Drawing.Size(60, 17);
            this.rbInverse.TabIndex = 1;
            this.rbInverse.Text = "Inverse";
            this.rbInverse.UseVisualStyleBackColor = true;
            this.rbInverse.CheckedChanged += new System.EventHandler(this.rbTransformDirection_CheckedChanged);
            // 
            // rbForward
            // 
            this.rbForward.AutoSize = true;
            this.rbForward.Checked = true;
            this.rbForward.Location = new System.Drawing.Point(0, 0);
            this.rbForward.Name = "rbForward";
            this.rbForward.Size = new System.Drawing.Size(63, 17);
            this.rbForward.TabIndex = 0;
            this.rbForward.TabStop = true;
            this.rbForward.Text = "Forward";
            this.rbForward.UseVisualStyleBackColor = true;
            this.rbForward.CheckedChanged += new System.EventHandler(this.rbTransformDirection_CheckedChanged);
            // 
            // grpFilters
            // 
            this.grpFilters.Controls.Add(this.pnlNotch);
            this.grpFilters.Controls.Add(this.pnlFilters);
            this.grpFilters.Location = new System.Drawing.Point(8, 183);
            this.grpFilters.Name = "grpFilters";
            this.grpFilters.Size = new System.Drawing.Size(628, 162);
            this.grpFilters.TabIndex = 15;
            this.grpFilters.TabStop = false;
            this.grpFilters.Text = "Transform Filters";
            // 
            // pnlNotch
            // 
            this.pnlNotch.Controls.Add(this.btnAddNotch);
            this.pnlNotch.Controls.Add(this.btnRedoNotch);
            this.pnlNotch.Controls.Add(this.cboNotchSize);
            this.pnlNotch.Controls.Add(this.lblNotchSize);
            this.pnlNotch.Controls.Add(this.txtNotchRow);
            this.pnlNotch.Controls.Add(this.lblNotchRow);
            this.pnlNotch.Controls.Add(this.txtNotchCol);
            this.pnlNotch.Controls.Add(this.lblNotchCol);
            this.pnlNotch.Controls.Add(this.cboPoint);
            this.pnlNotch.Controls.Add(this.lblPoint);
            this.pnlNotch.Location = new System.Drawing.Point(151, 101);
            this.pnlNotch.Name = "pnlNotch";
            this.pnlNotch.Size = new System.Drawing.Size(346, 52);
            this.pnlNotch.TabIndex = 1;
            // 
            // btnAddNotch
            // 
            this.btnAddNotch.Location = new System.Drawing.Point(286, 29);
            this.btnAddNotch.Name = "btnAddNotch";
            this.btnAddNotch.Size = new System.Drawing.Size(60, 23);
            this.btnAddNotch.TabIndex = 9;
            this.btnAddNotch.Text = "Add";
            this.btnAddNotch.UseVisualStyleBackColor = true;
            this.btnAddNotch.Click += new System.EventHandler(this.btnNotchAdd_Click);
            // 
            // btnRedoNotch
            // 
            this.btnRedoNotch.Location = new System.Drawing.Point(286, 0);
            this.btnRedoNotch.Name = "btnRedoNotch";
            this.btnRedoNotch.Size = new System.Drawing.Size(60, 23);
            this.btnRedoNotch.TabIndex = 8;
            this.btnRedoNotch.Text = "Redo";
            this.btnRedoNotch.UseVisualStyleBackColor = true;
            this.btnRedoNotch.Click += new System.EventHandler(this.btnNotchRedo_Click);
            // 
            // cboNotchSize
            // 
            this.cboNotchSize.FormattingEnabled = true;
            this.cboNotchSize.Items.AddRange(new object[] {
            "1",
            "2",
            "3",
            "4",
            "5",
            "10",
            "50",
            "100"});
            this.cboNotchSize.Location = new System.Drawing.Point(223, 29);
            this.cboNotchSize.Name = "cboNotchSize";
            this.cboNotchSize.Size = new System.Drawing.Size(50, 21);
            this.cboNotchSize.TabIndex = 7;
            this.cboNotchSize.Text = "10";
            this.cboNotchSize.Validating += new System.ComponentModel.CancelEventHandler(this.cboIntVal_Validating);
            this.cboNotchSize.Validated += new System.EventHandler(this.cboNotchVal_Validated);
            // 
            // lblNotchSize
            // 
            this.lblNotchSize.AutoSize = true;
            this.lblNotchSize.Location = new System.Drawing.Point(193, 33);
            this.lblNotchSize.Name = "lblNotchSize";
            this.lblNotchSize.Size = new System.Drawing.Size(30, 13);
            this.lblNotchSize.TabIndex = 6;
            this.lblNotchSize.Text = "Size:";
            // 
            // txtNotchRow
            // 
            this.txtNotchRow.Location = new System.Drawing.Point(160, 29);
            this.txtNotchRow.Name = "txtNotchRow";
            this.txtNotchRow.Size = new System.Drawing.Size(30, 20);
            this.txtNotchRow.TabIndex = 5;
            this.txtNotchRow.Text = "0";
            this.txtNotchRow.Validating += new System.ComponentModel.CancelEventHandler(this.txtIntVal_Validating);
            this.txtNotchRow.Validated += new System.EventHandler(this.cboNotchVal_Validated);
            // 
            // lblNotchRow
            // 
            this.lblNotchRow.AutoSize = true;
            this.lblNotchRow.Location = new System.Drawing.Point(128, 33);
            this.lblNotchRow.Name = "lblNotchRow";
            this.lblNotchRow.Size = new System.Drawing.Size(32, 13);
            this.lblNotchRow.TabIndex = 4;
            this.lblNotchRow.Text = "Row:";
            // 
            // txtNotchCol
            // 
            this.txtNotchCol.Location = new System.Drawing.Point(95, 29);
            this.txtNotchCol.Name = "txtNotchCol";
            this.txtNotchCol.Size = new System.Drawing.Size(30, 20);
            this.txtNotchCol.TabIndex = 3;
            this.txtNotchCol.Text = "0";
            this.txtNotchCol.Validating += new System.ComponentModel.CancelEventHandler(this.txtIntVal_Validating);
            this.txtNotchCol.Validated += new System.EventHandler(this.cboNotchVal_Validated);
            // 
            // lblNotchCol
            // 
            this.lblNotchCol.AutoSize = true;
            this.lblNotchCol.Location = new System.Drawing.Point(70, 33);
            this.lblNotchCol.Name = "lblNotchCol";
            this.lblNotchCol.Size = new System.Drawing.Size(25, 13);
            this.lblNotchCol.TabIndex = 2;
            this.lblNotchCol.Text = "Col:";
            // 
            // cboPoint
            // 
            this.cboPoint.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cboPoint.FormattingEnabled = true;
            this.cboPoint.Items.AddRange(new object[] {
            "(new)"});
            this.cboPoint.Location = new System.Drawing.Point(0, 29);
            this.cboPoint.Name = "cboPoint";
            this.cboPoint.Size = new System.Drawing.Size(60, 21);
            this.cboPoint.TabIndex = 1;
            this.cboPoint.SelectedIndexChanged += new System.EventHandler(this.cboPoint_SelectedIndexChanged);
            // 
            // lblPoint
            // 
            this.lblPoint.AutoSize = true;
            this.lblPoint.Location = new System.Drawing.Point(0, 13);
            this.lblPoint.Name = "lblPoint";
            this.lblPoint.Size = new System.Drawing.Size(34, 13);
            this.lblPoint.TabIndex = 0;
            this.lblPoint.Text = "Point:";
            // 
            // pnlFilters
            // 
            this.pnlFilters.Controls.Add(this.cboEmphasisOffset);
            this.pnlFilters.Controls.Add(this.lblEmphasisOffset);
            this.pnlFilters.Controls.Add(this.cboCutoffHigh);
            this.pnlFilters.Controls.Add(this.lblCutoffHigh);
            this.pnlFilters.Controls.Add(this.cboCutoffLow);
            this.pnlFilters.Controls.Add(this.lblCutoffLow);
            this.pnlFilters.Controls.Add(this.cboFilterOrder);
            this.pnlFilters.Controls.Add(this.lblFilterOrder);
            this.pnlFilters.Controls.Add(this.cboFilterType);
            this.pnlFilters.Controls.Add(this.lblFilterType);
            this.pnlFilters.Controls.Add(this.chkKeepDC);
            this.pnlFilters.Controls.Add(this.cboCutoff);
            this.pnlFilters.Controls.Add(this.lblCutoff);
            this.pnlFilters.Location = new System.Drawing.Point(151, 17);
            this.pnlFilters.Name = "pnlFilters";
            this.pnlFilters.Size = new System.Drawing.Size(343, 102);
            this.pnlFilters.TabIndex = 0;
            // 
            // cboEmphasisOffset
            // 
            this.cboEmphasisOffset.FormattingEnabled = true;
            this.cboEmphasisOffset.Items.AddRange(new object[] {
            "1.2",
            "1.3",
            "1.5",
            "1.7",
            "1.9",
            "2.5"});
            this.cboEmphasisOffset.Location = new System.Drawing.Point(87, 81);
            this.cboEmphasisOffset.Name = "cboEmphasisOffset";
            this.cboEmphasisOffset.Size = new System.Drawing.Size(100, 21);
            this.cboEmphasisOffset.TabIndex = 12;
            this.cboEmphasisOffset.Text = "1.2";
            this.cboEmphasisOffset.Validating += new System.ComponentModel.CancelEventHandler(this.cboDoubleVal_Validating);
            // 
            // lblEmphasisOffset
            // 
            this.lblEmphasisOffset.AutoSize = true;
            this.lblEmphasisOffset.Location = new System.Drawing.Point(0, 85);
            this.lblEmphasisOffset.Name = "lblEmphasisOffset";
            this.lblEmphasisOffset.Size = new System.Drawing.Size(84, 13);
            this.lblEmphasisOffset.TabIndex = 11;
            this.lblEmphasisOffset.Text = "Emphasis offset:";
            // 
            // cboCutoffHigh
            // 
            this.cboCutoffHigh.FormattingEnabled = true;
            this.cboCutoffHigh.Items.AddRange(new object[] {
            "64",
            "128",
            "256",
            "512"});
            this.cboCutoffHigh.Location = new System.Drawing.Point(293, 54);
            this.cboCutoffHigh.Name = "cboCutoffHigh";
            this.cboCutoffHigh.Size = new System.Drawing.Size(50, 21);
            this.cboCutoffHigh.TabIndex = 10;
            this.cboCutoffHigh.Text = "128";
            this.cboCutoffHigh.Validating += new System.ComponentModel.CancelEventHandler(this.cboIntVal_Validating);
            // 
            // lblCutoffHigh
            // 
            this.lblCutoffHigh.AutoSize = true;
            this.lblCutoffHigh.Location = new System.Drawing.Point(204, 58);
            this.lblCutoffHigh.Name = "lblCutoffHigh";
            this.lblCutoffHigh.Size = new System.Drawing.Size(87, 13);
            this.lblCutoffHigh.TabIndex = 9;
            this.lblCutoffHigh.Text = "High Cutoff Freq:";
            // 
            // cboCutoffLow
            // 
            this.cboCutoffLow.FormattingEnabled = true;
            this.cboCutoffLow.Items.AddRange(new object[] {
            "8",
            "16",
            "32",
            "64",
            "128"});
            this.cboCutoffLow.Location = new System.Drawing.Point(87, 54);
            this.cboCutoffLow.Name = "cboCutoffLow";
            this.cboCutoffLow.Size = new System.Drawing.Size(100, 21);
            this.cboCutoffLow.TabIndex = 8;
            this.cboCutoffLow.Text = "32";
            this.cboCutoffLow.Validating += new System.ComponentModel.CancelEventHandler(this.cboIntVal_Validating);
            // 
            // lblCutoffLow
            // 
            this.lblCutoffLow.AutoSize = true;
            this.lblCutoffLow.Location = new System.Drawing.Point(0, 58);
            this.lblCutoffLow.Name = "lblCutoffLow";
            this.lblCutoffLow.Size = new System.Drawing.Size(85, 13);
            this.lblCutoffLow.TabIndex = 7;
            this.lblCutoffLow.Text = "Low Cutoff Freq:";
            // 
            // cboFilterOrder
            // 
            this.cboFilterOrder.FormattingEnabled = true;
            this.cboFilterOrder.Items.AddRange(new object[] {
            "1",
            "2",
            "3",
            "4",
            "5",
            "6",
            "7",
            "8"});
            this.cboFilterOrder.Location = new System.Drawing.Point(293, 27);
            this.cboFilterOrder.Name = "cboFilterOrder";
            this.cboFilterOrder.Size = new System.Drawing.Size(50, 21);
            this.cboFilterOrder.TabIndex = 6;
            this.cboFilterOrder.Text = "1";
            this.cboFilterOrder.Validating += new System.ComponentModel.CancelEventHandler(this.cboIntVal_Validating);
            // 
            // lblFilterOrder
            // 
            this.lblFilterOrder.AutoSize = true;
            this.lblFilterOrder.Location = new System.Drawing.Point(204, 31);
            this.lblFilterOrder.Name = "lblFilterOrder";
            this.lblFilterOrder.Size = new System.Drawing.Size(61, 13);
            this.lblFilterOrder.TabIndex = 5;
            this.lblFilterOrder.Text = "Filter Order:";
            // 
            // cboFilterType
            // 
            this.cboFilterType.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cboFilterType.FormattingEnabled = true;
            this.cboFilterType.Items.AddRange(new object[] {
            "Ideal",
            "Butterworth"});
            this.cboFilterType.Location = new System.Drawing.Point(87, 27);
            this.cboFilterType.Name = "cboFilterType";
            this.cboFilterType.Size = new System.Drawing.Size(100, 21);
            this.cboFilterType.TabIndex = 4;
            this.cboFilterType.SelectedIndexChanged += new System.EventHandler(this.cboFilterType_SelectedIndexChanged);
            // 
            // lblFilterType
            // 
            this.lblFilterType.AutoSize = true;
            this.lblFilterType.Location = new System.Drawing.Point(0, 31);
            this.lblFilterType.Name = "lblFilterType";
            this.lblFilterType.Size = new System.Drawing.Size(59, 13);
            this.lblFilterType.TabIndex = 3;
            this.lblFilterType.Text = "Filter Type:";
            // 
            // chkKeepDC
            // 
            this.chkKeepDC.AutoSize = true;
            this.chkKeepDC.Location = new System.Drawing.Point(206, 0);
            this.chkKeepDC.Name = "chkKeepDC";
            this.chkKeepDC.Size = new System.Drawing.Size(69, 17);
            this.chkKeepDC.TabIndex = 2;
            this.chkKeepDC.Text = "Keep DC";
            this.chkKeepDC.UseVisualStyleBackColor = true;
            this.chkKeepDC.CheckedChanged += new System.EventHandler(this.chkKeepDC_CheckedChanged);
            // 
            // cboCutoff
            // 
            this.cboCutoff.FormattingEnabled = true;
            this.cboCutoff.Items.AddRange(new object[] {
            "8",
            "16",
            "32",
            "64",
            "128"});
            this.cboCutoff.Location = new System.Drawing.Point(87, 0);
            this.cboCutoff.Name = "cboCutoff";
            this.cboCutoff.Size = new System.Drawing.Size(100, 21);
            this.cboCutoff.TabIndex = 1;
            this.cboCutoff.Text = "32";
            this.cboCutoff.Validating += new System.ComponentModel.CancelEventHandler(this.cboIntVal_Validating);
            // 
            // lblCutoff
            // 
            this.lblCutoff.AutoSize = true;
            this.lblCutoff.Location = new System.Drawing.Point(0, 4);
            this.lblCutoff.Name = "lblCutoff";
            this.lblCutoff.Size = new System.Drawing.Size(62, 13);
            this.lblCutoff.TabIndex = 0;
            this.lblCutoff.Text = "Cutoff Freq:";
            // 
            // pnlFFTMagnitude
            // 
            this.pnlFFTMagnitude.Controls.Add(this.rbNoTranslate);
            this.pnlFFTMagnitude.Controls.Add(this.rbTranslate);
            this.pnlFFTMagnitude.Location = new System.Drawing.Point(251, 403);
            this.pnlFFTMagnitude.Name = "pnlFFTMagnitude";
            this.pnlFFTMagnitude.Size = new System.Drawing.Size(216, 17);
            this.pnlFFTMagnitude.TabIndex = 16;
            // 
            // rbNoTranslate
            // 
            this.rbNoTranslate.AutoSize = true;
            this.rbNoTranslate.Location = new System.Drawing.Point(119, 0);
            this.rbNoTranslate.Name = "rbNoTranslate";
            this.rbNoTranslate.Size = new System.Drawing.Size(94, 17);
            this.rbNoTranslate.TabIndex = 1;
            this.rbNoTranslate.Text = "No Translation";
            this.rbNoTranslate.UseVisualStyleBackColor = true;
            // 
            // rbTranslate
            // 
            this.rbTranslate.AutoSize = true;
            this.rbTranslate.Checked = true;
            this.rbTranslate.Location = new System.Drawing.Point(4, 0);
            this.rbTranslate.Name = "rbTranslate";
            this.rbTranslate.Size = new System.Drawing.Size(102, 17);
            this.rbTranslate.TabIndex = 0;
            this.rbTranslate.TabStop = true;
            this.rbTranslate.Text = "With Translation";
            this.rbTranslate.UseVisualStyleBackColor = true;
            // 
            // btnHelp
            // 
            this.btnHelp.BackColor = System.Drawing.Color.Yellow;
            this.btnHelp.Location = new System.Drawing.Point(17, 515);
            this.btnHelp.Name = "btnHelp";
            this.btnHelp.Size = new System.Drawing.Size(60, 26);
            this.btnHelp.TabIndex = 17;
            this.btnHelp.Text = "Help";
            this.btnHelp.UseVisualStyleBackColor = false;
            this.btnHelp.Click += new System.EventHandler(this.btnHelp_Click);
            // 
            // btnCancel
            // 
            this.btnCancel.BackColor = System.Drawing.Color.OrangeRed;
            this.btnCancel.CausesValidation = false;
            this.btnCancel.Location = new System.Drawing.Point(389, 515);
            this.btnCancel.Name = "btnCancel";
            this.btnCancel.Size = new System.Drawing.Size(60, 26);
            this.btnCancel.TabIndex = 18;
            this.btnCancel.Text = "Cancel";
            this.btnCancel.UseVisualStyleBackColor = false;
            this.btnCancel.Click += new System.EventHandler(this.btnCancel_Click);
            // 
            // btnReset
            // 
            this.btnReset.BackColor = System.Drawing.Color.CornflowerBlue;
            this.btnReset.CausesValidation = false;
            this.btnReset.Location = new System.Drawing.Point(488, 515);
            this.btnReset.Name = "btnReset";
            this.btnReset.Size = new System.Drawing.Size(60, 26);
            this.btnReset.TabIndex = 19;
            this.btnReset.Text = "Reset";
            this.btnReset.UseVisualStyleBackColor = false;
            this.btnReset.Click += new System.EventHandler(this.btnReset_Click);
            // 
            // btnApply
            // 
            this.btnApply.BackColor = System.Drawing.Color.LimeGreen;
            this.btnApply.ForeColor = System.Drawing.Color.White;
            this.btnApply.Location = new System.Drawing.Point(574, 514);
            this.btnApply.Name = "btnApply";
            this.btnApply.Size = new System.Drawing.Size(60, 26);
            this.btnApply.TabIndex = 20;
            this.btnApply.Text = "Apply";
            this.btnApply.UseVisualStyleBackColor = false;
            this.btnApply.Click += new System.EventHandler(this.btnApply_Click);
            // 
            // Note1
            // 
            this.Note1.AutoSize = true;
            this.Note1.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Note1.Location = new System.Drawing.Point(40, 388);
            this.Note1.Name = "Note1";
            this.Note1.Size = new System.Drawing.Size(338, 13);
            this.Note1.TabIndex = 21;
            this.Note1.Text = "Note: Normalizes the spectral magnitude and performs the inverse FFT";
            // 
            // Note2
            // 
            this.Note2.AutoSize = true;
            this.Note2.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Note2.Location = new System.Drawing.Point(43, 428);
            this.Note2.Name = "Note2";
            this.Note2.Size = new System.Drawing.Size(314, 13);
            this.Note2.TabIndex = 22;
            this.Note2.Text = "note: normalizes the spectral phase and performs the inverse FFT";
            // 
            // Transforms
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.Note2);
            this.Controls.Add(this.Note1);
            this.Controls.Add(this.btnApply);
            this.Controls.Add(this.btnReset);
            this.Controls.Add(this.btnCancel);
            this.Controls.Add(this.btnHelp);
            this.Controls.Add(this.rbFFTMagnitude);
            this.Controls.Add(this.rbFFTPhase);
            this.Controls.Add(this.rbNotch);
            this.Controls.Add(this.rbHighFreqEmphasis);
            this.Controls.Add(this.rbBandReject);
            this.Controls.Add(this.rbBandPass);
            this.Controls.Add(this.rbHighPass);
            this.Controls.Add(this.rbLowPass);
            this.Controls.Add(this.rbWavelet);
            this.Controls.Add(this.rbHadamard);
            this.Controls.Add(this.rbWalsh);
            this.Controls.Add(this.rbHaar);
            this.Controls.Add(this.rbFFT);
            this.Controls.Add(this.rbDCT);
            this.Controls.Add(this.pnlFFTMagnitude);
            this.Controls.Add(this.grpFilters);
            this.Controls.Add(this.grpTransforms);
            this.Name = "Transforms";
            this.Size = new System.Drawing.Size(679, 555);
            this.grpTransforms.ResumeLayout(false);
            this.pnlTransforms.ResumeLayout(false);
            this.pnlTransforms.PerformLayout();
            this.pnlForward.ResumeLayout(false);
            this.pnlForward.PerformLayout();
            this.grpFilters.ResumeLayout(false);
            this.pnlNotch.ResumeLayout(false);
            this.pnlNotch.PerformLayout();
            this.pnlFilters.ResumeLayout(false);
            this.pnlFilters.PerformLayout();
            this.pnlFFTMagnitude.ResumeLayout(false);
            this.pnlFFTMagnitude.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.RadioButton rbDCT;
        private System.Windows.Forms.RadioButton rbFFT;
        private System.Windows.Forms.RadioButton rbHaar;
        private System.Windows.Forms.RadioButton rbWalsh;
        private System.Windows.Forms.RadioButton rbHadamard;
        private System.Windows.Forms.RadioButton rbWavelet;
        private System.Windows.Forms.RadioButton rbLowPass;
        private System.Windows.Forms.RadioButton rbHighPass;
        private System.Windows.Forms.RadioButton rbBandPass;
        private System.Windows.Forms.RadioButton rbBandReject;
        private System.Windows.Forms.RadioButton rbHighFreqEmphasis;
        private System.Windows.Forms.RadioButton rbNotch;
        private System.Windows.Forms.RadioButton rbFFTPhase;
        private System.Windows.Forms.RadioButton rbFFTMagnitude;
        private System.Windows.Forms.GroupBox grpTransforms;
        private System.Windows.Forms.Panel pnlTransforms;
        private System.Windows.Forms.Panel pnlForward;
        private System.Windows.Forms.ComboBox cboDecomposition;
        private System.Windows.Forms.Label lblDecomposition;
        private System.Windows.Forms.ComboBox cboBasis;
        private System.Windows.Forms.Label lblBasis;
        private System.Windows.Forms.ComboBox cboBlockSize;
        private System.Windows.Forms.Label lblBlockSize;
        private System.Windows.Forms.RadioButton rbInverse;
        private System.Windows.Forms.RadioButton rbForward;
        private System.Windows.Forms.GroupBox grpFilters;
        private System.Windows.Forms.Panel pnlNotch;
        private System.Windows.Forms.Button btnAddNotch;
        private System.Windows.Forms.Button btnRedoNotch;
        private System.Windows.Forms.ComboBox cboNotchSize;
        private System.Windows.Forms.Label lblNotchSize;
        private System.Windows.Forms.TextBox txtNotchRow;
        private System.Windows.Forms.Label lblNotchRow;
        private System.Windows.Forms.TextBox txtNotchCol;
        private System.Windows.Forms.Label lblNotchCol;
        private System.Windows.Forms.ComboBox cboPoint;
        private System.Windows.Forms.Label lblPoint;
        private System.Windows.Forms.Panel pnlFilters;
        private System.Windows.Forms.ComboBox cboEmphasisOffset;
        private System.Windows.Forms.Label lblEmphasisOffset;
        private System.Windows.Forms.ComboBox cboCutoffHigh;
        private System.Windows.Forms.Label lblCutoffHigh;
        private System.Windows.Forms.ComboBox cboCutoffLow;
        private System.Windows.Forms.Label lblCutoffLow;
        private System.Windows.Forms.ComboBox cboFilterOrder;
        private System.Windows.Forms.Label lblFilterOrder;
        private System.Windows.Forms.ComboBox cboFilterType;
        private System.Windows.Forms.Label lblFilterType;
        private System.Windows.Forms.CheckBox chkKeepDC;
        private System.Windows.Forms.ComboBox cboCutoff;
        private System.Windows.Forms.Label lblCutoff;
        private System.Windows.Forms.Panel pnlFFTMagnitude;
        private System.Windows.Forms.RadioButton rbNoTranslate;
        private System.Windows.Forms.RadioButton rbTranslate;
        private System.Windows.Forms.Button btnHelp;
        private System.Windows.Forms.Button btnCancel;
        private System.Windows.Forms.Button btnReset;
        private System.Windows.Forms.Button btnApply;
        private System.Windows.Forms.Label Note1;
        private System.Windows.Forms.Label Note2;
    }
}
