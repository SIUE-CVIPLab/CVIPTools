namespace CVIPFEPC.Dialogs
{
    partial class ClassificationDlg
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
            this.grpNormalization = new System.Windows.Forms.GroupBox();
            this.lblSoftmax = new System.Windows.Forms.Label();
            this.txtSoftmax = new System.Windows.Forms.TextBox();
            this.lblSMax = new System.Windows.Forms.Label();
            this.txtSMax = new System.Windows.Forms.TextBox();
            this.lblSMin = new System.Windows.Forms.Label();
            this.txtSMin = new System.Windows.Forms.TextBox();
            this.pnlNormMultiSelect = new System.Windows.Forms.Panel();
            this.chkNormalizeSoftmax = new System.Windows.Forms.CheckBox();
            this.chkNormalizeMinMax = new System.Windows.Forms.CheckBox();
            this.chkNormalizeStdNorm = new System.Windows.Forms.CheckBox();
            this.chkNormalizeUnitVector = new System.Windows.Forms.CheckBox();
            this.chkNormalizeRange = new System.Windows.Forms.CheckBox();
            this.chkNormalizeNone = new System.Windows.Forms.CheckBox();
            this.pnlNormSingleSelect = new System.Windows.Forms.Panel();
            this.rbNormalizeSoftmax = new System.Windows.Forms.RadioButton();
            this.rbNormalizeMinMax = new System.Windows.Forms.RadioButton();
            this.rbNormalizeStdNorm = new System.Windows.Forms.RadioButton();
            this.rbNormalizeUnitVector = new System.Windows.Forms.RadioButton();
            this.rbNormalizeRange = new System.Windows.Forms.RadioButton();
            this.rbNormalizeNone = new System.Windows.Forms.RadioButton();
            this.grpDistance = new System.Windows.Forms.GroupBox();
            this.lblMinkowski = new System.Windows.Forms.Label();
            this.cboMinkowski = new System.Windows.Forms.ComboBox();
            this.lblSimilarity = new System.Windows.Forms.Label();
            this.lblDistance = new System.Windows.Forms.Label();
            this.pnlDistanceMultiSelect = new System.Windows.Forms.Panel();
            this.chkDistanceTanimoto = new System.Windows.Forms.CheckBox();
            this.chkDistanceVIP = new System.Windows.Forms.CheckBox();
            this.chkDistanceMinkowski = new System.Windows.Forms.CheckBox();
            this.chkDistanceMaxValue = new System.Windows.Forms.CheckBox();
            this.chkDistanceAbsValue = new System.Windows.Forms.CheckBox();
            this.chkDistanceEuclidean = new System.Windows.Forms.CheckBox();
            this.pnlDistanceSingleSelect = new System.Windows.Forms.Panel();
            this.rbDistanceTanimoto = new System.Windows.Forms.RadioButton();
            this.rbDistanceVIP = new System.Windows.Forms.RadioButton();
            this.rbDistanceMinkowski = new System.Windows.Forms.RadioButton();
            this.rbDistanceMaxValue = new System.Windows.Forms.RadioButton();
            this.rbDistanceAbsValue = new System.Windows.Forms.RadioButton();
            this.rbDistanceEuclidean = new System.Windows.Forms.RadioButton();
            this.grpClassification = new System.Windows.Forms.GroupBox();
            this.lblK = new System.Windows.Forms.Label();
            this.cboK = new System.Windows.Forms.ComboBox();
            this.pnlAlgorithmMultiSelect = new System.Windows.Forms.Panel();
            this.chkAlgorithmNearestCentroid = new System.Windows.Forms.CheckBox();
            this.chkAlgorithmKNearestNeighbor = new System.Windows.Forms.CheckBox();
            this.chkAlgorithmNearestNeighbor = new System.Windows.Forms.CheckBox();
            this.pnlAlgorithmSingleSelect = new System.Windows.Forms.Panel();
            this.rbAlgorithmNearestCentroid = new System.Windows.Forms.RadioButton();
            this.rbAlgorithmKNearestNeighbor = new System.Windows.Forms.RadioButton();
            this.rbAlgorithmNearestNeighbor = new System.Windows.Forms.RadioButton();
            this.btnSwitchToMultiSelect = new System.Windows.Forms.Button();
            this.btnSwitchToSingleSelect = new System.Windows.Forms.Button();
            this.btnCancel = new System.Windows.Forms.Button();
            this.btnReset = new System.Windows.Forms.Button();
            this.btnOK = new System.Windows.Forms.Button();
            this.grpNormalization.SuspendLayout();
            this.pnlNormMultiSelect.SuspendLayout();
            this.pnlNormSingleSelect.SuspendLayout();
            this.grpDistance.SuspendLayout();
            this.pnlDistanceMultiSelect.SuspendLayout();
            this.pnlDistanceSingleSelect.SuspendLayout();
            this.grpClassification.SuspendLayout();
            this.pnlAlgorithmMultiSelect.SuspendLayout();
            this.pnlAlgorithmSingleSelect.SuspendLayout();
            this.SuspendLayout();
            // 
            // grpNormalization
            // 
            this.grpNormalization.Controls.Add(this.lblSoftmax);
            this.grpNormalization.Controls.Add(this.txtSoftmax);
            this.grpNormalization.Controls.Add(this.lblSMax);
            this.grpNormalization.Controls.Add(this.txtSMax);
            this.grpNormalization.Controls.Add(this.lblSMin);
            this.grpNormalization.Controls.Add(this.txtSMin);
            this.grpNormalization.Controls.Add(this.pnlNormMultiSelect);
            this.grpNormalization.Controls.Add(this.pnlNormSingleSelect);
            this.grpNormalization.Location = new System.Drawing.Point(36, 25);
            this.grpNormalization.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.grpNormalization.Name = "grpNormalization";
            this.grpNormalization.Padding = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.grpNormalization.Size = new System.Drawing.Size(727, 127);
            this.grpNormalization.TabIndex = 0;
            this.grpNormalization.TabStop = false;
            this.grpNormalization.Text = "Data Normalization";
            // 
            // lblSoftmax
            // 
            this.lblSoftmax.AutoSize = true;
            this.lblSoftmax.Location = new System.Drawing.Point(508, 91);
            this.lblSoftmax.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lblSoftmax.Name = "lblSoftmax";
            this.lblSoftmax.Size = new System.Drawing.Size(25, 17);
            this.lblSoftmax.TabIndex = 7;
            this.lblSoftmax.Text = "r =";
            // 
            // txtSoftmax
            // 
            this.txtSoftmax.Location = new System.Drawing.Point(535, 86);
            this.txtSoftmax.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.txtSoftmax.Name = "txtSoftmax";
            this.txtSoftmax.Size = new System.Drawing.Size(43, 22);
            this.txtSoftmax.TabIndex = 6;
            this.txtSoftmax.Text = "1";
            this.txtSoftmax.Validating += new System.ComponentModel.CancelEventHandler(this.txtIntVal_Validating);
            this.txtSoftmax.Validated += new System.EventHandler(this.OnValueChanged);
            // 
            // lblSMax
            // 
            this.lblSMax.AutoSize = true;
            this.lblSMax.Location = new System.Drawing.Point(593, 62);
            this.lblSMax.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lblSMax.Name = "lblSMax";
            this.lblSMax.Size = new System.Drawing.Size(60, 17);
            this.lblSMax.TabIndex = 5;
            this.lblSMax.Text = "s_max =";
            // 
            // txtSMax
            // 
            this.txtSMax.Location = new System.Drawing.Point(656, 57);
            this.txtSMax.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.txtSMax.Name = "txtSMax";
            this.txtSMax.Size = new System.Drawing.Size(43, 22);
            this.txtSMax.TabIndex = 4;
            this.txtSMax.Text = "1";
            this.txtSMax.Validating += new System.ComponentModel.CancelEventHandler(this.txtMinMax_Validating);
            this.txtSMax.Validated += new System.EventHandler(this.OnValueChanged);
            // 
            // lblSMin
            // 
            this.lblSMin.AutoSize = true;
            this.lblSMin.Location = new System.Drawing.Point(476, 62);
            this.lblSMin.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lblSMin.Name = "lblSMin";
            this.lblSMin.Size = new System.Drawing.Size(57, 17);
            this.lblSMin.TabIndex = 3;
            this.lblSMin.Text = "s_min =";
            // 
            // txtSMin
            // 
            this.txtSMin.Location = new System.Drawing.Point(535, 57);
            this.txtSMin.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.txtSMin.Name = "txtSMin";
            this.txtSMin.Size = new System.Drawing.Size(43, 22);
            this.txtSMin.TabIndex = 2;
            this.txtSMin.Text = "0";
            this.txtSMin.Validating += new System.ComponentModel.CancelEventHandler(this.txtMinMax_Validating);
            this.txtSMin.Validated += new System.EventHandler(this.OnValueChanged);
            // 
            // pnlNormMultiSelect
            // 
            this.pnlNormMultiSelect.Controls.Add(this.chkNormalizeSoftmax);
            this.pnlNormMultiSelect.Controls.Add(this.chkNormalizeMinMax);
            this.pnlNormMultiSelect.Controls.Add(this.chkNormalizeStdNorm);
            this.pnlNormMultiSelect.Controls.Add(this.chkNormalizeUnitVector);
            this.pnlNormMultiSelect.Controls.Add(this.chkNormalizeRange);
            this.pnlNormMultiSelect.Controls.Add(this.chkNormalizeNone);
            this.pnlNormMultiSelect.Location = new System.Drawing.Point(27, 31);
            this.pnlNormMultiSelect.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.pnlNormMultiSelect.Name = "pnlNormMultiSelect";
            this.pnlNormMultiSelect.Size = new System.Drawing.Size(536, 78);
            this.pnlNormMultiSelect.TabIndex = 1;
            // 
            // chkNormalizeSoftmax
            // 
            this.chkNormalizeSoftmax.AutoSize = true;
            this.chkNormalizeSoftmax.Location = new System.Drawing.Point(257, 57);
            this.chkNormalizeSoftmax.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.chkNormalizeSoftmax.Name = "chkNormalizeSoftmax";
            this.chkNormalizeSoftmax.Size = new System.Drawing.Size(130, 21);
            this.chkNormalizeSoftmax.TabIndex = 5;
            this.chkNormalizeSoftmax.Text = "Softmax Scaling";
            this.chkNormalizeSoftmax.UseVisualStyleBackColor = true;
            this.chkNormalizeSoftmax.Click += new System.EventHandler(this.OnValueChanged);
            // 
            // chkNormalizeMinMax
            // 
            this.chkNormalizeMinMax.AutoSize = true;
            this.chkNormalizeMinMax.Location = new System.Drawing.Point(257, 28);
            this.chkNormalizeMinMax.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.chkNormalizeMinMax.Name = "chkNormalizeMinMax";
            this.chkNormalizeMinMax.Size = new System.Drawing.Size(172, 21);
            this.chkNormalizeMinMax.TabIndex = 4;
            this.chkNormalizeMinMax.Text = "Min-max Normalization";
            this.chkNormalizeMinMax.UseVisualStyleBackColor = true;
            this.chkNormalizeMinMax.Click += new System.EventHandler(this.OnValueChanged);
            // 
            // chkNormalizeStdNorm
            // 
            this.chkNormalizeStdNorm.AutoSize = true;
            this.chkNormalizeStdNorm.Location = new System.Drawing.Point(257, 0);
            this.chkNormalizeStdNorm.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.chkNormalizeStdNorm.Name = "chkNormalizeStdNorm";
            this.chkNormalizeStdNorm.Size = new System.Drawing.Size(278, 21);
            this.chkNormalizeStdNorm.TabIndex = 3;
            this.chkNormalizeStdNorm.Text = "Standard Normal Density Normalization";
            this.chkNormalizeStdNorm.UseVisualStyleBackColor = true;
            this.chkNormalizeStdNorm.Click += new System.EventHandler(this.OnValueChanged);
            // 
            // chkNormalizeUnitVector
            // 
            this.chkNormalizeUnitVector.AutoSize = true;
            this.chkNormalizeUnitVector.Location = new System.Drawing.Point(0, 57);
            this.chkNormalizeUnitVector.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.chkNormalizeUnitVector.Name = "chkNormalizeUnitVector";
            this.chkNormalizeUnitVector.Size = new System.Drawing.Size(190, 21);
            this.chkNormalizeUnitVector.TabIndex = 2;
            this.chkNormalizeUnitVector.Text = "Unit Vector Normalization";
            this.chkNormalizeUnitVector.UseVisualStyleBackColor = true;
            this.chkNormalizeUnitVector.Click += new System.EventHandler(this.OnValueChanged);
            // 
            // chkNormalizeRange
            // 
            this.chkNormalizeRange.AutoSize = true;
            this.chkNormalizeRange.Location = new System.Drawing.Point(0, 28);
            this.chkNormalizeRange.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.chkNormalizeRange.Name = "chkNormalizeRange";
            this.chkNormalizeRange.Size = new System.Drawing.Size(140, 21);
            this.chkNormalizeRange.TabIndex = 1;
            this.chkNormalizeRange.Text = "Range-Normalize";
            this.chkNormalizeRange.UseVisualStyleBackColor = true;
            this.chkNormalizeRange.Click += new System.EventHandler(this.OnValueChanged);
            // 
            // chkNormalizeNone
            // 
            this.chkNormalizeNone.AutoSize = true;
            this.chkNormalizeNone.Checked = true;
            this.chkNormalizeNone.CheckState = System.Windows.Forms.CheckState.Checked;
            this.chkNormalizeNone.Location = new System.Drawing.Point(0, 0);
            this.chkNormalizeNone.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.chkNormalizeNone.Name = "chkNormalizeNone";
            this.chkNormalizeNone.Size = new System.Drawing.Size(64, 21);
            this.chkNormalizeNone.TabIndex = 0;
            this.chkNormalizeNone.Text = "None";
            this.chkNormalizeNone.UseVisualStyleBackColor = true;
            this.chkNormalizeNone.Click += new System.EventHandler(this.OnValueChanged);
            // 
            // pnlNormSingleSelect
            // 
            this.pnlNormSingleSelect.Controls.Add(this.rbNormalizeSoftmax);
            this.pnlNormSingleSelect.Controls.Add(this.rbNormalizeMinMax);
            this.pnlNormSingleSelect.Controls.Add(this.rbNormalizeStdNorm);
            this.pnlNormSingleSelect.Controls.Add(this.rbNormalizeUnitVector);
            this.pnlNormSingleSelect.Controls.Add(this.rbNormalizeRange);
            this.pnlNormSingleSelect.Controls.Add(this.rbNormalizeNone);
            this.pnlNormSingleSelect.Location = new System.Drawing.Point(27, 31);
            this.pnlNormSingleSelect.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.pnlNormSingleSelect.Name = "pnlNormSingleSelect";
            this.pnlNormSingleSelect.Size = new System.Drawing.Size(535, 78);
            this.pnlNormSingleSelect.TabIndex = 0;
            // 
            // rbNormalizeSoftmax
            // 
            this.rbNormalizeSoftmax.AutoSize = true;
            this.rbNormalizeSoftmax.Location = new System.Drawing.Point(257, 57);
            this.rbNormalizeSoftmax.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.rbNormalizeSoftmax.Name = "rbNormalizeSoftmax";
            this.rbNormalizeSoftmax.Size = new System.Drawing.Size(129, 21);
            this.rbNormalizeSoftmax.TabIndex = 5;
            this.rbNormalizeSoftmax.Text = "Softmax Scaling";
            this.rbNormalizeSoftmax.UseVisualStyleBackColor = true;
            this.rbNormalizeSoftmax.Click += new System.EventHandler(this.rbNormalization_Click);
            // 
            // rbNormalizeMinMax
            // 
            this.rbNormalizeMinMax.AutoSize = true;
            this.rbNormalizeMinMax.Location = new System.Drawing.Point(257, 28);
            this.rbNormalizeMinMax.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.rbNormalizeMinMax.Name = "rbNormalizeMinMax";
            this.rbNormalizeMinMax.Size = new System.Drawing.Size(171, 21);
            this.rbNormalizeMinMax.TabIndex = 4;
            this.rbNormalizeMinMax.Text = "Min-max Normalization";
            this.rbNormalizeMinMax.UseVisualStyleBackColor = true;
            this.rbNormalizeMinMax.Click += new System.EventHandler(this.rbNormalization_Click);
            // 
            // rbNormalizeStdNorm
            // 
            this.rbNormalizeStdNorm.AutoSize = true;
            this.rbNormalizeStdNorm.Location = new System.Drawing.Point(257, 0);
            this.rbNormalizeStdNorm.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.rbNormalizeStdNorm.Name = "rbNormalizeStdNorm";
            this.rbNormalizeStdNorm.Size = new System.Drawing.Size(277, 21);
            this.rbNormalizeStdNorm.TabIndex = 3;
            this.rbNormalizeStdNorm.Text = "Standard Normal Density Normalization";
            this.rbNormalizeStdNorm.UseVisualStyleBackColor = true;
            this.rbNormalizeStdNorm.Click += new System.EventHandler(this.rbNormalization_Click);
            // 
            // rbNormalizeUnitVector
            // 
            this.rbNormalizeUnitVector.AutoSize = true;
            this.rbNormalizeUnitVector.Location = new System.Drawing.Point(0, 57);
            this.rbNormalizeUnitVector.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.rbNormalizeUnitVector.Name = "rbNormalizeUnitVector";
            this.rbNormalizeUnitVector.Size = new System.Drawing.Size(189, 21);
            this.rbNormalizeUnitVector.TabIndex = 2;
            this.rbNormalizeUnitVector.Text = "Unit Vector Normalization";
            this.rbNormalizeUnitVector.UseVisualStyleBackColor = true;
            this.rbNormalizeUnitVector.Click += new System.EventHandler(this.rbNormalization_Click);
            // 
            // rbNormalizeRange
            // 
            this.rbNormalizeRange.AutoSize = true;
            this.rbNormalizeRange.Location = new System.Drawing.Point(0, 28);
            this.rbNormalizeRange.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.rbNormalizeRange.Name = "rbNormalizeRange";
            this.rbNormalizeRange.Size = new System.Drawing.Size(139, 21);
            this.rbNormalizeRange.TabIndex = 1;
            this.rbNormalizeRange.Text = "Range-Normalize";
            this.rbNormalizeRange.UseVisualStyleBackColor = true;
            this.rbNormalizeRange.Click += new System.EventHandler(this.rbNormalization_Click);
            // 
            // rbNormalizeNone
            // 
            this.rbNormalizeNone.AutoSize = true;
            this.rbNormalizeNone.Checked = true;
            this.rbNormalizeNone.Location = new System.Drawing.Point(0, 0);
            this.rbNormalizeNone.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.rbNormalizeNone.Name = "rbNormalizeNone";
            this.rbNormalizeNone.Size = new System.Drawing.Size(63, 21);
            this.rbNormalizeNone.TabIndex = 0;
            this.rbNormalizeNone.TabStop = true;
            this.rbNormalizeNone.Text = "None";
            this.rbNormalizeNone.UseVisualStyleBackColor = true;
            this.rbNormalizeNone.Click += new System.EventHandler(this.rbNormalization_Click);
            // 
            // grpDistance
            // 
            this.grpDistance.Controls.Add(this.lblMinkowski);
            this.grpDistance.Controls.Add(this.cboMinkowski);
            this.grpDistance.Controls.Add(this.lblSimilarity);
            this.grpDistance.Controls.Add(this.lblDistance);
            this.grpDistance.Controls.Add(this.pnlDistanceMultiSelect);
            this.grpDistance.Controls.Add(this.pnlDistanceSingleSelect);
            this.grpDistance.Location = new System.Drawing.Point(36, 162);
            this.grpDistance.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.grpDistance.Name = "grpDistance";
            this.grpDistance.Padding = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.grpDistance.Size = new System.Drawing.Size(727, 186);
            this.grpDistance.TabIndex = 1;
            this.grpDistance.TabStop = false;
            this.grpDistance.Text = "Distance and Similarity Measures";
            this.grpDistance.Enter += new System.EventHandler(this.grpDistance_Enter);
            // 
            // lblMinkowski
            // 
            this.lblMinkowski.AutoSize = true;
            this.lblMinkowski.Location = new System.Drawing.Point(267, 150);
            this.lblMinkowski.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lblMinkowski.Name = "lblMinkowski";
            this.lblMinkowski.Size = new System.Drawing.Size(25, 17);
            this.lblMinkowski.TabIndex = 5;
            this.lblMinkowski.Text = "r =";
            // 
            // cboMinkowski
            // 
            this.cboMinkowski.FormattingEnabled = true;
            this.cboMinkowski.Items.AddRange(new object[] {
            "3",
            "4",
            "5",
            "6",
            "7",
            "8",
            "9",
            "10"});
            this.cboMinkowski.Location = new System.Drawing.Point(293, 145);
            this.cboMinkowski.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.cboMinkowski.Name = "cboMinkowski";
            this.cboMinkowski.Size = new System.Drawing.Size(53, 24);
            this.cboMinkowski.TabIndex = 4;
            this.cboMinkowski.Text = "3";
            this.cboMinkowski.Validating += new System.ComponentModel.CancelEventHandler(this.cboIntVal_Validating);
            this.cboMinkowski.Validated += new System.EventHandler(this.OnValueChanged);
            // 
            // lblSimilarity
            // 
            this.lblSimilarity.AutoSize = true;
            this.lblSimilarity.Location = new System.Drawing.Point(411, 30);
            this.lblSimilarity.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lblSimilarity.Name = "lblSimilarity";
            this.lblSimilarity.Size = new System.Drawing.Size(130, 17);
            this.lblSimilarity.TabIndex = 3;
            this.lblSimilarity.Text = "Similarity Measures";
            // 
            // lblDistance
            // 
            this.lblDistance.AutoSize = true;
            this.lblDistance.Location = new System.Drawing.Point(52, 30);
            this.lblDistance.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lblDistance.Name = "lblDistance";
            this.lblDistance.Size = new System.Drawing.Size(129, 17);
            this.lblDistance.TabIndex = 2;
            this.lblDistance.Text = "Distance Measures";
            // 
            // pnlDistanceMultiSelect
            // 
            this.pnlDistanceMultiSelect.Controls.Add(this.chkDistanceTanimoto);
            this.pnlDistanceMultiSelect.Controls.Add(this.chkDistanceVIP);
            this.pnlDistanceMultiSelect.Controls.Add(this.chkDistanceMinkowski);
            this.pnlDistanceMultiSelect.Controls.Add(this.chkDistanceMaxValue);
            this.pnlDistanceMultiSelect.Controls.Add(this.chkDistanceAbsValue);
            this.pnlDistanceMultiSelect.Controls.Add(this.chkDistanceEuclidean);
            this.pnlDistanceMultiSelect.Location = new System.Drawing.Point(27, 59);
            this.pnlDistanceMultiSelect.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.pnlDistanceMultiSelect.Name = "pnlDistanceMultiSelect";
            this.pnlDistanceMultiSelect.Size = new System.Drawing.Size(600, 106);
            this.pnlDistanceMultiSelect.TabIndex = 1;
            this.pnlDistanceMultiSelect.Paint += new System.Windows.Forms.PaintEventHandler(this.pnlDistanceMultiSelect_Paint);
            // 
            // chkDistanceTanimoto
            // 
            this.chkDistanceTanimoto.AutoSize = true;
            this.chkDistanceTanimoto.Location = new System.Drawing.Point(357, 28);
            this.chkDistanceTanimoto.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.chkDistanceTanimoto.Name = "chkDistanceTanimoto";
            this.chkDistanceTanimoto.Size = new System.Drawing.Size(131, 21);
            this.chkDistanceTanimoto.TabIndex = 5;
            this.chkDistanceTanimoto.Text = "Tanimoto Metric";
            this.chkDistanceTanimoto.UseVisualStyleBackColor = true;
            this.chkDistanceTanimoto.Click += new System.EventHandler(this.OnValueChanged);
            // 
            // chkDistanceVIP
            // 
            this.chkDistanceVIP.AutoSize = true;
            this.chkDistanceVIP.Location = new System.Drawing.Point(357, 0);
            this.chkDistanceVIP.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.chkDistanceVIP.Name = "chkDistanceVIP";
            this.chkDistanceVIP.Size = new System.Drawing.Size(235, 21);
            this.chkDistanceVIP.TabIndex = 4;
            this.chkDistanceVIP.Text = "Normalized Vector Inner Product";
            this.chkDistanceVIP.UseVisualStyleBackColor = true;
            this.chkDistanceVIP.CheckedChanged += new System.EventHandler(this.chkDistanceVIP_CheckedChanged);
            this.chkDistanceVIP.Click += new System.EventHandler(this.OnValueChanged);
            // 
            // chkDistanceMinkowski
            // 
            this.chkDistanceMinkowski.AutoSize = true;
            this.chkDistanceMinkowski.Location = new System.Drawing.Point(0, 85);
            this.chkDistanceMinkowski.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.chkDistanceMinkowski.Name = "chkDistanceMinkowski";
            this.chkDistanceMinkowski.Size = new System.Drawing.Size(152, 21);
            this.chkDistanceMinkowski.TabIndex = 3;
            this.chkDistanceMinkowski.Text = "Minkowski Distance";
            this.chkDistanceMinkowski.UseVisualStyleBackColor = true;
            this.chkDistanceMinkowski.Click += new System.EventHandler(this.OnValueChanged);
            // 
            // chkDistanceMaxValue
            // 
            this.chkDistanceMaxValue.AutoSize = true;
            this.chkDistanceMaxValue.Location = new System.Drawing.Point(0, 57);
            this.chkDistanceMaxValue.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.chkDistanceMaxValue.Name = "chkDistanceMaxValue";
            this.chkDistanceMaxValue.Size = new System.Drawing.Size(170, 21);
            this.chkDistanceMaxValue.TabIndex = 2;
            this.chkDistanceMaxValue.Text = "Maximum Value Metric";
            this.chkDistanceMaxValue.UseVisualStyleBackColor = true;
            this.chkDistanceMaxValue.Click += new System.EventHandler(this.OnValueChanged);
            // 
            // chkDistanceAbsValue
            // 
            this.chkDistanceAbsValue.AutoSize = true;
            this.chkDistanceAbsValue.Location = new System.Drawing.Point(0, 28);
            this.chkDistanceAbsValue.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.chkDistanceAbsValue.Name = "chkDistanceAbsValue";
            this.chkDistanceAbsValue.Size = new System.Drawing.Size(249, 21);
            this.chkDistanceAbsValue.TabIndex = 1;
            this.chkDistanceAbsValue.Text = "City Block or Absolute Value Metric";
            this.chkDistanceAbsValue.UseVisualStyleBackColor = true;
            this.chkDistanceAbsValue.Click += new System.EventHandler(this.OnValueChanged);
            // 
            // chkDistanceEuclidean
            // 
            this.chkDistanceEuclidean.AutoSize = true;
            this.chkDistanceEuclidean.Checked = true;
            this.chkDistanceEuclidean.CheckState = System.Windows.Forms.CheckState.Checked;
            this.chkDistanceEuclidean.Location = new System.Drawing.Point(0, 0);
            this.chkDistanceEuclidean.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.chkDistanceEuclidean.Name = "chkDistanceEuclidean";
            this.chkDistanceEuclidean.Size = new System.Drawing.Size(151, 21);
            this.chkDistanceEuclidean.TabIndex = 0;
            this.chkDistanceEuclidean.Text = "Euclidean Distance";
            this.chkDistanceEuclidean.UseVisualStyleBackColor = true;
            this.chkDistanceEuclidean.CheckedChanged += new System.EventHandler(this.chkDistanceEuclidean_CheckedChanged);
            this.chkDistanceEuclidean.Click += new System.EventHandler(this.OnValueChanged);
            // 
            // pnlDistanceSingleSelect
            // 
            this.pnlDistanceSingleSelect.Controls.Add(this.rbDistanceTanimoto);
            this.pnlDistanceSingleSelect.Controls.Add(this.rbDistanceVIP);
            this.pnlDistanceSingleSelect.Controls.Add(this.rbDistanceMinkowski);
            this.pnlDistanceSingleSelect.Controls.Add(this.rbDistanceMaxValue);
            this.pnlDistanceSingleSelect.Controls.Add(this.rbDistanceAbsValue);
            this.pnlDistanceSingleSelect.Controls.Add(this.rbDistanceEuclidean);
            this.pnlDistanceSingleSelect.Location = new System.Drawing.Point(27, 59);
            this.pnlDistanceSingleSelect.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.pnlDistanceSingleSelect.Name = "pnlDistanceSingleSelect";
            this.pnlDistanceSingleSelect.Size = new System.Drawing.Size(600, 106);
            this.pnlDistanceSingleSelect.TabIndex = 0;
            // 
            // rbDistanceTanimoto
            // 
            this.rbDistanceTanimoto.AutoSize = true;
            this.rbDistanceTanimoto.Location = new System.Drawing.Point(357, 28);
            this.rbDistanceTanimoto.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.rbDistanceTanimoto.Name = "rbDistanceTanimoto";
            this.rbDistanceTanimoto.Size = new System.Drawing.Size(130, 21);
            this.rbDistanceTanimoto.TabIndex = 5;
            this.rbDistanceTanimoto.Text = "Tanimoto Metric";
            this.rbDistanceTanimoto.UseVisualStyleBackColor = true;
            this.rbDistanceTanimoto.Click += new System.EventHandler(this.rbDistance_Click);
            // 
            // rbDistanceVIP
            // 
            this.rbDistanceVIP.AutoSize = true;
            this.rbDistanceVIP.Location = new System.Drawing.Point(357, 0);
            this.rbDistanceVIP.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.rbDistanceVIP.Name = "rbDistanceVIP";
            this.rbDistanceVIP.Size = new System.Drawing.Size(234, 21);
            this.rbDistanceVIP.TabIndex = 4;
            this.rbDistanceVIP.Text = "Normalized Vector Inner Product";
            this.rbDistanceVIP.UseVisualStyleBackColor = true;
            this.rbDistanceVIP.Click += new System.EventHandler(this.rbDistance_Click);
            // 
            // rbDistanceMinkowski
            // 
            this.rbDistanceMinkowski.AutoSize = true;
            this.rbDistanceMinkowski.Location = new System.Drawing.Point(0, 85);
            this.rbDistanceMinkowski.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.rbDistanceMinkowski.Name = "rbDistanceMinkowski";
            this.rbDistanceMinkowski.Size = new System.Drawing.Size(151, 21);
            this.rbDistanceMinkowski.TabIndex = 3;
            this.rbDistanceMinkowski.Text = "Minkowski Distance";
            this.rbDistanceMinkowski.UseVisualStyleBackColor = true;
            this.rbDistanceMinkowski.Click += new System.EventHandler(this.rbDistance_Click);
            // 
            // rbDistanceMaxValue
            // 
            this.rbDistanceMaxValue.AutoSize = true;
            this.rbDistanceMaxValue.Location = new System.Drawing.Point(0, 57);
            this.rbDistanceMaxValue.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.rbDistanceMaxValue.Name = "rbDistanceMaxValue";
            this.rbDistanceMaxValue.Size = new System.Drawing.Size(169, 21);
            this.rbDistanceMaxValue.TabIndex = 2;
            this.rbDistanceMaxValue.Text = "Maximum Value Metric";
            this.rbDistanceMaxValue.UseVisualStyleBackColor = true;
            this.rbDistanceMaxValue.Click += new System.EventHandler(this.rbDistance_Click);
            // 
            // rbDistanceAbsValue
            // 
            this.rbDistanceAbsValue.AutoSize = true;
            this.rbDistanceAbsValue.Location = new System.Drawing.Point(0, 28);
            this.rbDistanceAbsValue.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.rbDistanceAbsValue.Name = "rbDistanceAbsValue";
            this.rbDistanceAbsValue.Size = new System.Drawing.Size(248, 21);
            this.rbDistanceAbsValue.TabIndex = 1;
            this.rbDistanceAbsValue.Text = "City Block or Absolute Value Metric";
            this.rbDistanceAbsValue.UseVisualStyleBackColor = true;
            this.rbDistanceAbsValue.Click += new System.EventHandler(this.rbDistance_Click);
            // 
            // rbDistanceEuclidean
            // 
            this.rbDistanceEuclidean.AutoSize = true;
            this.rbDistanceEuclidean.Checked = true;
            this.rbDistanceEuclidean.Location = new System.Drawing.Point(0, 0);
            this.rbDistanceEuclidean.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.rbDistanceEuclidean.Name = "rbDistanceEuclidean";
            this.rbDistanceEuclidean.Size = new System.Drawing.Size(150, 21);
            this.rbDistanceEuclidean.TabIndex = 0;
            this.rbDistanceEuclidean.TabStop = true;
            this.rbDistanceEuclidean.Text = "Euclidean Distance";
            this.rbDistanceEuclidean.UseVisualStyleBackColor = true;
            this.rbDistanceEuclidean.Click += new System.EventHandler(this.rbDistance_Click);
            // 
            // grpClassification
            // 
            this.grpClassification.Controls.Add(this.lblK);
            this.grpClassification.Controls.Add(this.cboK);
            this.grpClassification.Controls.Add(this.pnlAlgorithmMultiSelect);
            this.grpClassification.Controls.Add(this.pnlAlgorithmSingleSelect);
            this.grpClassification.Location = new System.Drawing.Point(36, 358);
            this.grpClassification.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.grpClassification.Name = "grpClassification";
            this.grpClassification.Padding = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.grpClassification.Size = new System.Drawing.Size(727, 123);
            this.grpClassification.TabIndex = 2;
            this.grpClassification.TabStop = false;
            this.grpClassification.Text = "Classification Algorithms";
            // 
            // lblK
            // 
            this.lblK.AutoSize = true;
            this.lblK.Location = new System.Drawing.Point(256, 62);
            this.lblK.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lblK.Name = "lblK";
            this.lblK.Size = new System.Drawing.Size(29, 17);
            this.lblK.TabIndex = 3;
            this.lblK.Text = "K =";
            // 
            // cboK
            // 
            this.cboK.FormattingEnabled = true;
            this.cboK.Items.AddRange(new object[] {
            "2",
            "3",
            "4",
            "5",
            "6",
            "7",
            "8",
            "9",
            "10"});
            this.cboK.Location = new System.Drawing.Point(288, 57);
            this.cboK.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.cboK.Name = "cboK";
            this.cboK.Size = new System.Drawing.Size(53, 24);
            this.cboK.TabIndex = 2;
            this.cboK.Text = "3";
            this.cboK.Validating += new System.ComponentModel.CancelEventHandler(this.cboIntVal_Validating);
            this.cboK.Validated += new System.EventHandler(this.OnValueChanged);
            // 
            // pnlAlgorithmMultiSelect
            // 
            this.pnlAlgorithmMultiSelect.Controls.Add(this.chkAlgorithmNearestCentroid);
            this.pnlAlgorithmMultiSelect.Controls.Add(this.chkAlgorithmKNearestNeighbor);
            this.pnlAlgorithmMultiSelect.Controls.Add(this.chkAlgorithmNearestNeighbor);
            this.pnlAlgorithmMultiSelect.Location = new System.Drawing.Point(27, 30);
            this.pnlAlgorithmMultiSelect.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.pnlAlgorithmMultiSelect.Name = "pnlAlgorithmMultiSelect";
            this.pnlAlgorithmMultiSelect.Size = new System.Drawing.Size(159, 78);
            this.pnlAlgorithmMultiSelect.TabIndex = 1;
            // 
            // chkAlgorithmNearestCentroid
            // 
            this.chkAlgorithmNearestCentroid.AutoSize = true;
            this.chkAlgorithmNearestCentroid.Location = new System.Drawing.Point(0, 57);
            this.chkAlgorithmNearestCentroid.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.chkAlgorithmNearestCentroid.Name = "chkAlgorithmNearestCentroid";
            this.chkAlgorithmNearestCentroid.Size = new System.Drawing.Size(137, 21);
            this.chkAlgorithmNearestCentroid.TabIndex = 2;
            this.chkAlgorithmNearestCentroid.Text = "Nearest Centroid";
            this.chkAlgorithmNearestCentroid.UseVisualStyleBackColor = true;
            this.chkAlgorithmNearestCentroid.Click += new System.EventHandler(this.OnValueChanged);
            // 
            // chkAlgorithmKNearestNeighbor
            // 
            this.chkAlgorithmKNearestNeighbor.AutoSize = true;
            this.chkAlgorithmKNearestNeighbor.Location = new System.Drawing.Point(0, 28);
            this.chkAlgorithmKNearestNeighbor.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.chkAlgorithmKNearestNeighbor.Name = "chkAlgorithmKNearestNeighbor";
            this.chkAlgorithmKNearestNeighbor.Size = new System.Drawing.Size(156, 21);
            this.chkAlgorithmKNearestNeighbor.TabIndex = 1;
            this.chkAlgorithmKNearestNeighbor.Text = "K-Nearest Neighbor";
            this.chkAlgorithmKNearestNeighbor.UseVisualStyleBackColor = true;
            this.chkAlgorithmKNearestNeighbor.Click += new System.EventHandler(this.OnValueChanged);
            // 
            // chkAlgorithmNearestNeighbor
            // 
            this.chkAlgorithmNearestNeighbor.AutoSize = true;
            this.chkAlgorithmNearestNeighbor.Checked = true;
            this.chkAlgorithmNearestNeighbor.CheckState = System.Windows.Forms.CheckState.Checked;
            this.chkAlgorithmNearestNeighbor.Location = new System.Drawing.Point(0, 0);
            this.chkAlgorithmNearestNeighbor.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.chkAlgorithmNearestNeighbor.Name = "chkAlgorithmNearestNeighbor";
            this.chkAlgorithmNearestNeighbor.Size = new System.Drawing.Size(142, 21);
            this.chkAlgorithmNearestNeighbor.TabIndex = 0;
            this.chkAlgorithmNearestNeighbor.Text = "Nearest Neighbor";
            this.chkAlgorithmNearestNeighbor.UseVisualStyleBackColor = true;
            this.chkAlgorithmNearestNeighbor.Click += new System.EventHandler(this.OnValueChanged);
            // 
            // pnlAlgorithmSingleSelect
            // 
            this.pnlAlgorithmSingleSelect.Controls.Add(this.rbAlgorithmNearestCentroid);
            this.pnlAlgorithmSingleSelect.Controls.Add(this.rbAlgorithmKNearestNeighbor);
            this.pnlAlgorithmSingleSelect.Controls.Add(this.rbAlgorithmNearestNeighbor);
            this.pnlAlgorithmSingleSelect.Location = new System.Drawing.Point(27, 30);
            this.pnlAlgorithmSingleSelect.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.pnlAlgorithmSingleSelect.Name = "pnlAlgorithmSingleSelect";
            this.pnlAlgorithmSingleSelect.Size = new System.Drawing.Size(157, 78);
            this.pnlAlgorithmSingleSelect.TabIndex = 0;
            // 
            // rbAlgorithmNearestCentroid
            // 
            this.rbAlgorithmNearestCentroid.AutoSize = true;
            this.rbAlgorithmNearestCentroid.Location = new System.Drawing.Point(0, 57);
            this.rbAlgorithmNearestCentroid.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.rbAlgorithmNearestCentroid.Name = "rbAlgorithmNearestCentroid";
            this.rbAlgorithmNearestCentroid.Size = new System.Drawing.Size(136, 21);
            this.rbAlgorithmNearestCentroid.TabIndex = 2;
            this.rbAlgorithmNearestCentroid.Text = "Nearest Centroid";
            this.rbAlgorithmNearestCentroid.UseVisualStyleBackColor = true;
            this.rbAlgorithmNearestCentroid.Click += new System.EventHandler(this.rbAlgorithm_Click);
            // 
            // rbAlgorithmKNearestNeighbor
            // 
            this.rbAlgorithmKNearestNeighbor.AutoSize = true;
            this.rbAlgorithmKNearestNeighbor.Location = new System.Drawing.Point(0, 28);
            this.rbAlgorithmKNearestNeighbor.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.rbAlgorithmKNearestNeighbor.Name = "rbAlgorithmKNearestNeighbor";
            this.rbAlgorithmKNearestNeighbor.Size = new System.Drawing.Size(155, 21);
            this.rbAlgorithmKNearestNeighbor.TabIndex = 1;
            this.rbAlgorithmKNearestNeighbor.Text = "K-Nearest Neighbor";
            this.rbAlgorithmKNearestNeighbor.UseVisualStyleBackColor = true;
            this.rbAlgorithmKNearestNeighbor.Click += new System.EventHandler(this.rbAlgorithm_Click);
            // 
            // rbAlgorithmNearestNeighbor
            // 
            this.rbAlgorithmNearestNeighbor.AutoSize = true;
            this.rbAlgorithmNearestNeighbor.Checked = true;
            this.rbAlgorithmNearestNeighbor.Location = new System.Drawing.Point(0, 0);
            this.rbAlgorithmNearestNeighbor.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.rbAlgorithmNearestNeighbor.Name = "rbAlgorithmNearestNeighbor";
            this.rbAlgorithmNearestNeighbor.Size = new System.Drawing.Size(141, 21);
            this.rbAlgorithmNearestNeighbor.TabIndex = 0;
            this.rbAlgorithmNearestNeighbor.TabStop = true;
            this.rbAlgorithmNearestNeighbor.Text = "Nearest Neighbor";
            this.rbAlgorithmNearestNeighbor.UseVisualStyleBackColor = true;
            this.rbAlgorithmNearestNeighbor.Click += new System.EventHandler(this.rbAlgorithm_Click);
            // 
            // btnSwitchToMultiSelect
            // 
            this.btnSwitchToMultiSelect.Location = new System.Drawing.Point(36, 510);
            this.btnSwitchToMultiSelect.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.btnSwitchToMultiSelect.Name = "btnSwitchToMultiSelect";
            this.btnSwitchToMultiSelect.Size = new System.Drawing.Size(239, 31);
            this.btnSwitchToMultiSelect.TabIndex = 3;
            this.btnSwitchToMultiSelect.Text = "Switch to Combinatoric Test Mode";
            this.btnSwitchToMultiSelect.UseVisualStyleBackColor = true;
            this.btnSwitchToMultiSelect.Click += new System.EventHandler(this.btnSelectionMode_Click);
            // 
            // btnSwitchToSingleSelect
            // 
            this.btnSwitchToSingleSelect.Location = new System.Drawing.Point(36, 510);
            this.btnSwitchToSingleSelect.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.btnSwitchToSingleSelect.Name = "btnSwitchToSingleSelect";
            this.btnSwitchToSingleSelect.Size = new System.Drawing.Size(239, 31);
            this.btnSwitchToSingleSelect.TabIndex = 4;
            this.btnSwitchToSingleSelect.Text = "Switch to Single Test Mode";
            this.btnSwitchToSingleSelect.UseVisualStyleBackColor = true;
            this.btnSwitchToSingleSelect.Click += new System.EventHandler(this.btnSelectionMode_Click);
            // 
            // btnCancel
            // 
            this.btnCancel.BackColor = System.Drawing.Color.OrangeRed;
            this.btnCancel.CausesValidation = false;
            this.btnCancel.DialogResult = System.Windows.Forms.DialogResult.Cancel;
            this.btnCancel.Location = new System.Drawing.Point(452, 510);
            this.btnCancel.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.btnCancel.Name = "btnCancel";
            this.btnCancel.Size = new System.Drawing.Size(100, 31);
            this.btnCancel.TabIndex = 5;
            this.btnCancel.Text = "Cancel";
            this.btnCancel.UseVisualStyleBackColor = false;
            // 
            // btnReset
            // 
            this.btnReset.BackColor = System.Drawing.Color.CornflowerBlue;
            this.btnReset.CausesValidation = false;
            this.btnReset.Enabled = false;
            this.btnReset.Location = new System.Drawing.Point(559, 510);
            this.btnReset.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.btnReset.Name = "btnReset";
            this.btnReset.Size = new System.Drawing.Size(100, 31);
            this.btnReset.TabIndex = 6;
            this.btnReset.Text = "Reset";
            this.btnReset.UseVisualStyleBackColor = false;
            this.btnReset.Click += new System.EventHandler(this.btnReset_Click);
            // 
            // btnOK
            // 
            this.btnOK.BackColor = System.Drawing.Color.LimeGreen;
            this.btnOK.DialogResult = System.Windows.Forms.DialogResult.OK;
            this.btnOK.ForeColor = System.Drawing.Color.White;
            this.btnOK.Location = new System.Drawing.Point(663, 510);
            this.btnOK.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.btnOK.Name = "btnOK";
            this.btnOK.Size = new System.Drawing.Size(100, 31);
            this.btnOK.TabIndex = 7;
            this.btnOK.Text = "OK";
            this.btnOK.UseVisualStyleBackColor = false;
            this.btnOK.Click += new System.EventHandler(this.btnOK_Click);
            // 
            // ClassificationDlg
            // 
            this.AcceptButton = this.btnOK;
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.CancelButton = this.btnCancel;
            this.CausesValidation = false;
            this.ClientSize = new System.Drawing.Size(799, 566);
            this.ControlBox = false;
            this.Controls.Add(this.btnOK);
            this.Controls.Add(this.btnReset);
            this.Controls.Add(this.btnCancel);
            this.Controls.Add(this.btnSwitchToSingleSelect);
            this.Controls.Add(this.btnSwitchToMultiSelect);
            this.Controls.Add(this.grpClassification);
            this.Controls.Add(this.grpDistance);
            this.Controls.Add(this.grpNormalization);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "ClassificationDlg";
            this.ShowInTaskbar = false;
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
            this.Text = "Pattern Classification";
            this.grpNormalization.ResumeLayout(false);
            this.grpNormalization.PerformLayout();
            this.pnlNormMultiSelect.ResumeLayout(false);
            this.pnlNormMultiSelect.PerformLayout();
            this.pnlNormSingleSelect.ResumeLayout(false);
            this.pnlNormSingleSelect.PerformLayout();
            this.grpDistance.ResumeLayout(false);
            this.grpDistance.PerformLayout();
            this.pnlDistanceMultiSelect.ResumeLayout(false);
            this.pnlDistanceMultiSelect.PerformLayout();
            this.pnlDistanceSingleSelect.ResumeLayout(false);
            this.pnlDistanceSingleSelect.PerformLayout();
            this.grpClassification.ResumeLayout(false);
            this.grpClassification.PerformLayout();
            this.pnlAlgorithmMultiSelect.ResumeLayout(false);
            this.pnlAlgorithmMultiSelect.PerformLayout();
            this.pnlAlgorithmSingleSelect.ResumeLayout(false);
            this.pnlAlgorithmSingleSelect.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox grpNormalization;
        private System.Windows.Forms.Label lblSoftmax;
        private System.Windows.Forms.TextBox txtSoftmax;
        private System.Windows.Forms.Label lblSMax;
        private System.Windows.Forms.TextBox txtSMax;
        private System.Windows.Forms.Label lblSMin;
        private System.Windows.Forms.TextBox txtSMin;
        private System.Windows.Forms.Panel pnlNormMultiSelect;
        private System.Windows.Forms.CheckBox chkNormalizeSoftmax;
        private System.Windows.Forms.CheckBox chkNormalizeMinMax;
        private System.Windows.Forms.CheckBox chkNormalizeStdNorm;
        private System.Windows.Forms.CheckBox chkNormalizeUnitVector;
        private System.Windows.Forms.CheckBox chkNormalizeRange;
        private System.Windows.Forms.CheckBox chkNormalizeNone;
        private System.Windows.Forms.Panel pnlNormSingleSelect;
        private System.Windows.Forms.RadioButton rbNormalizeSoftmax;
        private System.Windows.Forms.RadioButton rbNormalizeMinMax;
        private System.Windows.Forms.RadioButton rbNormalizeStdNorm;
        private System.Windows.Forms.RadioButton rbNormalizeUnitVector;
        private System.Windows.Forms.RadioButton rbNormalizeRange;
        private System.Windows.Forms.RadioButton rbNormalizeNone;
        private System.Windows.Forms.GroupBox grpDistance;
        private System.Windows.Forms.Label lblMinkowski;
        private System.Windows.Forms.ComboBox cboMinkowski;
        private System.Windows.Forms.Label lblSimilarity;
        private System.Windows.Forms.Label lblDistance;
        private System.Windows.Forms.Panel pnlDistanceMultiSelect;
        private System.Windows.Forms.CheckBox chkDistanceTanimoto;
        private System.Windows.Forms.CheckBox chkDistanceVIP;
        private System.Windows.Forms.CheckBox chkDistanceMinkowski;
        private System.Windows.Forms.CheckBox chkDistanceMaxValue;
        private System.Windows.Forms.CheckBox chkDistanceAbsValue;
        private System.Windows.Forms.CheckBox chkDistanceEuclidean;
        private System.Windows.Forms.Panel pnlDistanceSingleSelect;
        private System.Windows.Forms.RadioButton rbDistanceTanimoto;
        private System.Windows.Forms.RadioButton rbDistanceVIP;
        private System.Windows.Forms.RadioButton rbDistanceMinkowski;
        private System.Windows.Forms.RadioButton rbDistanceMaxValue;
        private System.Windows.Forms.RadioButton rbDistanceAbsValue;
        private System.Windows.Forms.RadioButton rbDistanceEuclidean;
        private System.Windows.Forms.GroupBox grpClassification;
        private System.Windows.Forms.Label lblK;
        private System.Windows.Forms.ComboBox cboK;
        private System.Windows.Forms.Panel pnlAlgorithmMultiSelect;
        private System.Windows.Forms.CheckBox chkAlgorithmNearestCentroid;
        private System.Windows.Forms.CheckBox chkAlgorithmKNearestNeighbor;
        private System.Windows.Forms.CheckBox chkAlgorithmNearestNeighbor;
        private System.Windows.Forms.Panel pnlAlgorithmSingleSelect;
        private System.Windows.Forms.RadioButton rbAlgorithmNearestCentroid;
        private System.Windows.Forms.RadioButton rbAlgorithmKNearestNeighbor;
        private System.Windows.Forms.RadioButton rbAlgorithmNearestNeighbor;
        private System.Windows.Forms.Button btnSwitchToMultiSelect;
        private System.Windows.Forms.Button btnSwitchToSingleSelect;
        private System.Windows.Forms.Button btnCancel;
        private System.Windows.Forms.Button btnReset;
        private System.Windows.Forms.Button btnOK;
    }
}
