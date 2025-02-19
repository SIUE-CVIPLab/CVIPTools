namespace CVIPGUI.Analysis
{
    partial class Geometry
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
            this.rbCrop = new System.Windows.Forms.RadioButton();
            this.rbPaste = new System.Windows.Forms.RadioButton();
            this.rbResize = new System.Windows.Forms.RadioButton();
            this.rbRotate = new System.Windows.Forms.RadioButton();
            this.rbTranslate = new System.Windows.Forms.RadioButton();
            this.rbZoom = new System.Windows.Forms.RadioButton();
            this.grpCrop = new System.Windows.Forms.GroupBox();
            this.cboCropHeight = new System.Windows.Forms.ComboBox();
            this.lblCropHeight = new System.Windows.Forms.Label();
            this.cboCropWidth = new System.Windows.Forms.ComboBox();
            this.lblCropWidth = new System.Windows.Forms.Label();
            this.cboCropRow = new System.Windows.Forms.ComboBox();
            this.lblCropRow = new System.Windows.Forms.Label();
            this.cboCropCol = new System.Windows.Forms.ComboBox();
            this.grpPaste = new System.Windows.Forms.GroupBox();
            this.lblTransparently = new System.Windows.Forms.Label();
            this.cboPasteRow = new System.Windows.Forms.ComboBox();
            this.lblPasteRow = new System.Windows.Forms.Label();
            this.cboPasteCol = new System.Windows.Forms.ComboBox();
            this.lblPasteCol = new System.Windows.Forms.Label();
            this.chkTransparently = new System.Windows.Forms.CheckBox();
            this.cboImages = new System.Windows.Forms.ComboBox();
            this.grpResize = new System.Windows.Forms.GroupBox();
            this.cboResizeMethod = new System.Windows.Forms.ComboBox();
            this.lblResizeMethod = new System.Windows.Forms.Label();
            this.cboResizeHeight = new System.Windows.Forms.ComboBox();
            this.lblResizeHeight = new System.Windows.Forms.Label();
            this.cboResizeWidth = new System.Windows.Forms.ComboBox();
            this.grpRotate = new System.Windows.Forms.GroupBox();
            this.lblRotateDegrees = new System.Windows.Forms.Label();
            this.cboRotateDegrees = new System.Windows.Forms.ComboBox();
            this.grpTranslate = new System.Windows.Forms.GroupBox();
            this.lblWrapText = new System.Windows.Forms.Label();
            this.cboTranslateGrayLevel = new System.Windows.Forms.ComboBox();
            this.chkTranslateWrap = new System.Windows.Forms.CheckBox();
            this.lblTranslateDown = new System.Windows.Forms.Label();
            this.cboTranslateDown = new System.Windows.Forms.ComboBox();
            this.lblTranslateRight = new System.Windows.Forms.Label();
            this.cboTranslateRight = new System.Windows.Forms.ComboBox();
            this.grpZoom = new System.Windows.Forms.GroupBox();
            this.grpZoomLocation = new System.Windows.Forms.GroupBox();
            this.lblZoomPixels = new System.Windows.Forms.Label();
            this.cboZoomHeight = new System.Windows.Forms.ComboBox();
            this.lblZoomHeight = new System.Windows.Forms.Label();
            this.cboZoomWidth = new System.Windows.Forms.ComboBox();
            this.lblZoomWidth = new System.Windows.Forms.Label();
            this.cboZoomRow = new System.Windows.Forms.ComboBox();
            this.lblZoomRow = new System.Windows.Forms.Label();
            this.cboZoomCol = new System.Windows.Forms.ComboBox();
            this.rbZoomArea = new System.Windows.Forms.RadioButton();
            this.rbZoomLowerRight = new System.Windows.Forms.RadioButton();
            this.rbZoomLowerLeft = new System.Windows.Forms.RadioButton();
            this.rbZoomUpperRight = new System.Windows.Forms.RadioButton();
            this.rbZoomUpperLeft = new System.Windows.Forms.RadioButton();
            this.cboZoomMethod = new System.Windows.Forms.ComboBox();
            this.lblZoomMethod = new System.Windows.Forms.Label();
            this.cboZoomFactor = new System.Windows.Forms.ComboBox();
            this.lblZoomFactor = new System.Windows.Forms.Label();
            this.btnHelp = new System.Windows.Forms.Button();
            this.btnCancel = new System.Windows.Forms.Button();
            this.btnReset = new System.Windows.Forms.Button();
            this.btnApply = new System.Windows.Forms.Button();
            this.grpCrop.SuspendLayout();
            this.grpPaste.SuspendLayout();
            this.grpResize.SuspendLayout();
            this.grpRotate.SuspendLayout();
            this.grpTranslate.SuspendLayout();
            this.grpZoom.SuspendLayout();
            this.grpZoomLocation.SuspendLayout();
            this.SuspendLayout();
            // 
            // rbCrop
            // 
            this.rbCrop.AutoSize = true;
            this.rbCrop.Checked = true;
            this.rbCrop.Location = new System.Drawing.Point(16, 15);
            this.rbCrop.Name = "rbCrop";
            this.rbCrop.Size = new System.Drawing.Size(274, 17);
            this.rbCrop.TabIndex = 0;
            this.rbCrop.TabStop = true;
            this.rbCrop.Text = "Crop a subimage from the upper left corner at column";
            this.rbCrop.UseVisualStyleBackColor = true;
            this.rbCrop.CheckedChanged += new System.EventHandler(this.rbGeometry_CheckedChanged);
            // 
            // rbPaste
            // 
            this.rbPaste.AutoSize = true;
            this.rbPaste.Location = new System.Drawing.Point(16, 81);
            this.rbPaste.Name = "rbPaste";
            this.rbPaste.Size = new System.Drawing.Size(52, 17);
            this.rbPaste.TabIndex = 1;
            this.rbPaste.Text = "Paste";
            this.rbPaste.UseVisualStyleBackColor = true;
            this.rbPaste.CheckedChanged += new System.EventHandler(this.rbGeometry_CheckedChanged);
            // 
            // rbResize
            // 
            this.rbResize.AutoSize = true;
            this.rbResize.Location = new System.Drawing.Point(16, 153);
            this.rbResize.Name = "rbResize";
            this.rbResize.Size = new System.Drawing.Size(116, 17);
            this.rbResize.TabIndex = 2;
            this.rbResize.Text = "Resize image width";
            this.rbResize.UseVisualStyleBackColor = true;
            this.rbResize.CheckedChanged += new System.EventHandler(this.rbGeometry_CheckedChanged);
            // 
            // rbRotate
            // 
            this.rbRotate.AutoSize = true;
            this.rbRotate.Location = new System.Drawing.Point(16, 198);
            this.rbRotate.Name = "rbRotate";
            this.rbRotate.Size = new System.Drawing.Size(170, 17);
            this.rbRotate.TabIndex = 3;
            this.rbRotate.Text = "Rotate an image clockwise by ";
            this.rbRotate.UseVisualStyleBackColor = true;
            this.rbRotate.CheckedChanged += new System.EventHandler(this.rbGeometry_CheckedChanged);
            // 
            // rbTranslate
            // 
            this.rbTranslate.AutoSize = true;
            this.rbTranslate.Location = new System.Drawing.Point(16, 244);
            this.rbTranslate.Name = "rbTranslate";
            this.rbTranslate.Size = new System.Drawing.Size(138, 17);
            this.rbTranslate.TabIndex = 4;
            this.rbTranslate.Text = "Translate an image right";
            this.rbTranslate.UseVisualStyleBackColor = true;
            this.rbTranslate.CheckedChanged += new System.EventHandler(this.rbGeometry_CheckedChanged);
            // 
            // rbZoom
            // 
            this.rbZoom.AutoSize = true;
            this.rbZoom.Location = new System.Drawing.Point(16, 319);
            this.rbZoom.Name = "rbZoom";
            this.rbZoom.Size = new System.Drawing.Size(52, 17);
            this.rbZoom.TabIndex = 5;
            this.rbZoom.Text = "Zoom";
            this.rbZoom.UseVisualStyleBackColor = true;
            this.rbZoom.CheckedChanged += new System.EventHandler(this.rbGeometry_CheckedChanged);
            // 
            // grpCrop
            // 
            this.grpCrop.Controls.Add(this.cboCropHeight);
            this.grpCrop.Controls.Add(this.lblCropHeight);
            this.grpCrop.Controls.Add(this.cboCropWidth);
            this.grpCrop.Controls.Add(this.lblCropWidth);
            this.grpCrop.Controls.Add(this.cboCropRow);
            this.grpCrop.Controls.Add(this.lblCropRow);
            this.grpCrop.Controls.Add(this.cboCropCol);
            this.grpCrop.Location = new System.Drawing.Point(4, 0);
            this.grpCrop.Name = "grpCrop";
            this.grpCrop.Size = new System.Drawing.Size(632, 65);
            this.grpCrop.TabIndex = 6;
            this.grpCrop.TabStop = false;
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
            this.cboCropHeight.Location = new System.Drawing.Point(449, 38);
            this.cboCropHeight.Name = "cboCropHeight";
            this.cboCropHeight.Size = new System.Drawing.Size(75, 21);
            this.cboCropHeight.TabIndex = 6;
            this.cboCropHeight.Text = "100";
            this.cboCropHeight.Validating += new System.ComponentModel.CancelEventHandler(this.cboPositiveIntVal_Validating);
            this.cboCropHeight.Validated += new System.EventHandler(this.cboCropZoom_Validated);
            // 
            // lblCropHeight
            // 
            this.lblCropHeight.AutoSize = true;
            this.lblCropHeight.Location = new System.Drawing.Point(368, 42);
            this.lblCropHeight.Name = "lblCropHeight";
            this.lblCropHeight.Size = new System.Drawing.Size(69, 13);
            this.lblCropHeight.TabIndex = 5;
            this.lblCropHeight.Text = "and height of";
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
            this.cboCropWidth.Location = new System.Drawing.Point(288, 39);
            this.cboCropWidth.Name = "cboCropWidth";
            this.cboCropWidth.Size = new System.Drawing.Size(75, 21);
            this.cboCropWidth.TabIndex = 4;
            this.cboCropWidth.Text = "100";
            this.cboCropWidth.Validating += new System.ComponentModel.CancelEventHandler(this.cboPositiveIntVal_Validating);
            this.cboCropWidth.Validated += new System.EventHandler(this.cboCropZoom_Validated);
            // 
            // lblCropWidth
            // 
            this.lblCropWidth.AutoSize = true;
            this.lblCropWidth.Location = new System.Drawing.Point(195, 41);
            this.lblCropWidth.Name = "lblCropWidth";
            this.lblCropWidth.Size = new System.Drawing.Size(75, 13);
            this.lblCropWidth.TabIndex = 3;
            this.lblCropWidth.Text = "with a width of";
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
            "256"});
            this.cboCropRow.Location = new System.Drawing.Point(449, 11);
            this.cboCropRow.Name = "cboCropRow";
            this.cboCropRow.Size = new System.Drawing.Size(75, 21);
            this.cboCropRow.TabIndex = 2;
            this.cboCropRow.Text = "0";
            this.cboCropRow.Validating += new System.ComponentModel.CancelEventHandler(this.cboUIntVal_Validating);
            this.cboCropRow.Validated += new System.EventHandler(this.cboCropZoom_Validated);
            // 
            // lblCropRow
            // 
            this.lblCropRow.AutoSize = true;
            this.lblCropRow.Location = new System.Drawing.Point(392, 16);
            this.lblCropRow.Name = "lblCropRow";
            this.lblCropRow.Size = new System.Drawing.Size(45, 13);
            this.lblCropRow.TabIndex = 1;
            this.lblCropRow.Text = "and row";
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
            "256"});
            this.cboCropCol.Location = new System.Drawing.Point(288, 13);
            this.cboCropCol.Name = "cboCropCol";
            this.cboCropCol.Size = new System.Drawing.Size(75, 21);
            this.cboCropCol.TabIndex = 0;
            this.cboCropCol.Text = "0";
            this.cboCropCol.Validating += new System.ComponentModel.CancelEventHandler(this.cboUIntVal_Validating);
            this.cboCropCol.Validated += new System.EventHandler(this.cboCropZoom_Validated);
            // 
            // grpPaste
            // 
            this.grpPaste.Controls.Add(this.lblTransparently);
            this.grpPaste.Controls.Add(this.cboPasteRow);
            this.grpPaste.Controls.Add(this.lblPasteRow);
            this.grpPaste.Controls.Add(this.cboPasteCol);
            this.grpPaste.Controls.Add(this.lblPasteCol);
            this.grpPaste.Controls.Add(this.chkTransparently);
            this.grpPaste.Controls.Add(this.cboImages);
            this.grpPaste.Location = new System.Drawing.Point(4, 66);
            this.grpPaste.Name = "grpPaste";
            this.grpPaste.Size = new System.Drawing.Size(632, 70);
            this.grpPaste.TabIndex = 7;
            this.grpPaste.TabStop = false;
            // 
            // lblTransparently
            // 
            this.lblTransparently.AutoSize = true;
            this.lblTransparently.Location = new System.Drawing.Point(411, 45);
            this.lblTransparently.Name = "lblTransparently";
            this.lblTransparently.Size = new System.Drawing.Size(101, 13);
            this.lblTransparently.TabIndex = 6;
            this.lblTransparently.Text = "to the current image";
            // 
            // cboPasteRow
            // 
            this.cboPasteRow.FormattingEnabled = true;
            this.cboPasteRow.Items.AddRange(new object[] {
            "0",
            "8",
            "16",
            "32",
            "64",
            "128",
            "256"});
            this.cboPasteRow.Location = new System.Drawing.Point(330, 41);
            this.cboPasteRow.Name = "cboPasteRow";
            this.cboPasteRow.Size = new System.Drawing.Size(75, 21);
            this.cboPasteRow.TabIndex = 5;
            this.cboPasteRow.Text = "128";
            this.cboPasteRow.Validating += new System.ComponentModel.CancelEventHandler(this.cboUIntVal_Validating);
            // 
            // lblPasteRow
            // 
            this.lblPasteRow.AutoSize = true;
            this.lblPasteRow.Location = new System.Drawing.Point(279, 45);
            this.lblPasteRow.Name = "lblPasteRow";
            this.lblPasteRow.Size = new System.Drawing.Size(45, 13);
            this.lblPasteRow.TabIndex = 4;
            this.lblPasteRow.Text = "and row";
            // 
            // cboPasteCol
            // 
            this.cboPasteCol.FormattingEnabled = true;
            this.cboPasteCol.Items.AddRange(new object[] {
            "0",
            "8",
            "16",
            "32",
            "64",
            "128",
            "256"});
            this.cboPasteCol.Location = new System.Drawing.Point(200, 41);
            this.cboPasteCol.Name = "cboPasteCol";
            this.cboPasteCol.Size = new System.Drawing.Size(75, 21);
            this.cboPasteCol.TabIndex = 3;
            this.cboPasteCol.Text = "128";
            this.cboPasteCol.Validating += new System.ComponentModel.CancelEventHandler(this.cboUIntVal_Validating);
            // 
            // lblPasteCol
            // 
            this.lblPasteCol.AutoSize = true;
            this.lblPasteCol.Location = new System.Drawing.Point(28, 45);
            this.lblPasteCol.Name = "lblPasteCol";
            this.lblPasteCol.Size = new System.Drawing.Size(168, 13);
            this.lblPasteCol.TabIndex = 2;
            this.lblPasteCol.Text = "with its upper left corner at column";
            // 
            // chkTransparently
            // 
            this.chkTransparently.AutoSize = true;
            this.chkTransparently.Location = new System.Drawing.Point(438, 15);
            this.chkTransparently.Name = "chkTransparently";
            this.chkTransparently.Size = new System.Drawing.Size(86, 17);
            this.chkTransparently.TabIndex = 1;
            this.chkTransparently.Text = "transparently";
            this.chkTransparently.UseVisualStyleBackColor = true;
            // 
            // cboImages
            // 
            this.cboImages.DisplayMember = "Text";
            this.cboImages.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cboImages.FormattingEnabled = true;
            this.cboImages.Location = new System.Drawing.Point(64, 13);
            this.cboImages.Name = "cboImages";
            this.cboImages.Size = new System.Drawing.Size(365, 21);
            this.cboImages.TabIndex = 0;
            // 
            // grpResize
            // 
            this.grpResize.Controls.Add(this.cboResizeMethod);
            this.grpResize.Controls.Add(this.lblResizeMethod);
            this.grpResize.Controls.Add(this.cboResizeHeight);
            this.grpResize.Controls.Add(this.lblResizeHeight);
            this.grpResize.Controls.Add(this.cboResizeWidth);
            this.grpResize.Location = new System.Drawing.Point(4, 137);
            this.grpResize.Name = "grpResize";
            this.grpResize.Size = new System.Drawing.Size(632, 44);
            this.grpResize.TabIndex = 8;
            this.grpResize.TabStop = false;
            // 
            // cboResizeMethod
            // 
            this.cboResizeMethod.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cboResizeMethod.FormattingEnabled = true;
            this.cboResizeMethod.Items.AddRange(new object[] {
            "zero order hold",
            "linear interpolation"});
            this.cboResizeMethod.Location = new System.Drawing.Point(392, 15);
            this.cboResizeMethod.Name = "cboResizeMethod";
            this.cboResizeMethod.Size = new System.Drawing.Size(120, 21);
            this.cboResizeMethod.TabIndex = 4;
            // 
            // lblResizeMethod
            // 
            this.lblResizeMethod.AutoSize = true;
            this.lblResizeMethod.Location = new System.Drawing.Point(356, 19);
            this.lblResizeMethod.Name = "lblResizeMethod";
            this.lblResizeMethod.Size = new System.Drawing.Size(32, 13);
            this.lblResizeMethod.TabIndex = 3;
            this.lblResizeMethod.Text = "using";
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
            "512"});
            this.cboResizeHeight.Location = new System.Drawing.Point(277, 15);
            this.cboResizeHeight.Name = "cboResizeHeight";
            this.cboResizeHeight.Size = new System.Drawing.Size(75, 21);
            this.cboResizeHeight.TabIndex = 2;
            this.cboResizeHeight.Text = "256";
            this.cboResizeHeight.Validating += new System.ComponentModel.CancelEventHandler(this.cboPositiveIntVal_Validating);
            // 
            // lblResizeHeight
            // 
            this.lblResizeHeight.AutoSize = true;
            this.lblResizeHeight.Location = new System.Drawing.Point(213, 19);
            this.lblResizeHeight.Name = "lblResizeHeight";
            this.lblResizeHeight.Size = new System.Drawing.Size(57, 13);
            this.lblResizeHeight.TabIndex = 1;
            this.lblResizeHeight.Text = "and height";
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
            "512"});
            this.cboResizeWidth.Location = new System.Drawing.Point(133, 15);
            this.cboResizeWidth.Name = "cboResizeWidth";
            this.cboResizeWidth.Size = new System.Drawing.Size(75, 21);
            this.cboResizeWidth.TabIndex = 0;
            this.cboResizeWidth.Text = "256";
            this.cboResizeWidth.Validating += new System.ComponentModel.CancelEventHandler(this.cboPositiveIntVal_Validating);
            // 
            // grpRotate
            // 
            this.grpRotate.Controls.Add(this.lblRotateDegrees);
            this.grpRotate.Controls.Add(this.cboRotateDegrees);
            this.grpRotate.Location = new System.Drawing.Point(4, 182);
            this.grpRotate.Name = "grpRotate";
            this.grpRotate.Size = new System.Drawing.Size(632, 44);
            this.grpRotate.TabIndex = 9;
            this.grpRotate.TabStop = false;
            // 
            // lblRotateDegrees
            // 
            this.lblRotateDegrees.AutoSize = true;
            this.lblRotateDegrees.Location = new System.Drawing.Point(264, 18);
            this.lblRotateDegrees.Name = "lblRotateDegrees";
            this.lblRotateDegrees.Size = new System.Drawing.Size(45, 13);
            this.lblRotateDegrees.TabIndex = 1;
            this.lblRotateDegrees.Text = "degrees";
            // 
            // cboRotateDegrees
            // 
            this.cboRotateDegrees.FormattingEnabled = true;
            this.cboRotateDegrees.Items.AddRange(new object[] {
            "-180",
            "-150",
            "-135",
            "-120",
            "-90",
            "-60",
            "-45",
            "-30",
            "-20",
            "-10",
            "10",
            "20",
            "30",
            "45",
            "60",
            "90",
            "120",
            "135",
            "150",
            "180"});
            this.cboRotateDegrees.Location = new System.Drawing.Point(184, 14);
            this.cboRotateDegrees.Name = "cboRotateDegrees";
            this.cboRotateDegrees.Size = new System.Drawing.Size(75, 21);
            this.cboRotateDegrees.TabIndex = 0;
            this.cboRotateDegrees.Text = "90";
            this.cboRotateDegrees.Validating += new System.ComponentModel.CancelEventHandler(this.cboFloatVal_Validating);
            // 
            // grpTranslate
            // 
            this.grpTranslate.Controls.Add(this.lblWrapText);
            this.grpTranslate.Controls.Add(this.cboTranslateGrayLevel);
            this.grpTranslate.Controls.Add(this.chkTranslateWrap);
            this.grpTranslate.Controls.Add(this.lblTranslateDown);
            this.grpTranslate.Controls.Add(this.cboTranslateDown);
            this.grpTranslate.Controls.Add(this.lblTranslateRight);
            this.grpTranslate.Controls.Add(this.cboTranslateRight);
            this.grpTranslate.Location = new System.Drawing.Point(4, 227);
            this.grpTranslate.Name = "grpTranslate";
            this.grpTranslate.Size = new System.Drawing.Size(632, 75);
            this.grpTranslate.TabIndex = 10;
            this.grpTranslate.TabStop = false;
            // 
            // lblWrapText
            // 
            this.lblWrapText.AutoSize = true;
            this.lblWrapText.Location = new System.Drawing.Point(21, 48);
            this.lblWrapText.Name = "lblWrapText";
            this.lblWrapText.Size = new System.Drawing.Size(178, 13);
            this.lblWrapText.TabIndex = 6;
            this.lblWrapText.Text = "Wrap the image around the edge or ";
            // 
            // cboTranslateGrayLevel
            // 
            this.cboTranslateGrayLevel.FormattingEnabled = true;
            this.cboTranslateGrayLevel.Items.AddRange(new object[] {
            "0",
            "8",
            "16",
            "32",
            "64",
            "128",
            "256"});
            this.cboTranslateGrayLevel.Location = new System.Drawing.Point(327, 45);
            this.cboTranslateGrayLevel.Name = "cboTranslateGrayLevel";
            this.cboTranslateGrayLevel.Size = new System.Drawing.Size(75, 21);
            this.cboTranslateGrayLevel.TabIndex = 5;
            this.cboTranslateGrayLevel.Text = "128";
            this.cboTranslateGrayLevel.Validating += new System.ComponentModel.CancelEventHandler(this.cboFloatVal_Validating);
            // 
            // chkTranslateWrap
            // 
            this.chkTranslateWrap.AutoSize = true;
            this.chkTranslateWrap.Checked = true;
            this.chkTranslateWrap.CheckState = System.Windows.Forms.CheckState.Checked;
            this.chkTranslateWrap.Location = new System.Drawing.Point(200, 47);
            this.chkTranslateWrap.Name = "chkTranslateWrap";
            this.chkTranslateWrap.Size = new System.Drawing.Size(121, 17);
            this.chkTranslateWrap.TabIndex = 4;
            this.chkTranslateWrap.Text = "fill with gray value of";
            this.chkTranslateWrap.UseVisualStyleBackColor = true;
            this.chkTranslateWrap.CheckedChanged += new System.EventHandler(this.chkTranslateWrap_CheckedChanged);
            // 
            // lblTranslateDown
            // 
            this.lblTranslateDown.AutoSize = true;
            this.lblTranslateDown.Location = new System.Drawing.Point(409, 19);
            this.lblTranslateDown.Name = "lblTranslateDown";
            this.lblTranslateDown.Size = new System.Drawing.Size(33, 13);
            this.lblTranslateDown.TabIndex = 3;
            this.lblTranslateDown.Text = "pixels";
            // 
            // cboTranslateDown
            // 
            this.cboTranslateDown.FormattingEnabled = true;
            this.cboTranslateDown.Items.AddRange(new object[] {
            "0",
            "8",
            "16",
            "32",
            "64",
            "128",
            "256"});
            this.cboTranslateDown.Location = new System.Drawing.Point(327, 15);
            this.cboTranslateDown.Name = "cboTranslateDown";
            this.cboTranslateDown.Size = new System.Drawing.Size(75, 21);
            this.cboTranslateDown.TabIndex = 2;
            this.cboTranslateDown.Text = "128";
            this.cboTranslateDown.Validating += new System.ComponentModel.CancelEventHandler(this.cboIntVal_Validating);
            // 
            // lblTranslateRight
            // 
            this.lblTranslateRight.AutoSize = true;
            this.lblTranslateRight.Location = new System.Drawing.Point(236, 19);
            this.lblTranslateRight.Name = "lblTranslateRight";
            this.lblTranslateRight.Size = new System.Drawing.Size(83, 13);
            this.lblTranslateRight.TabIndex = 1;
            this.lblTranslateRight.Text = "pixels and down";
            // 
            // cboTranslateRight
            // 
            this.cboTranslateRight.FormattingEnabled = true;
            this.cboTranslateRight.Items.AddRange(new object[] {
            "0",
            "8",
            "16",
            "32",
            "64",
            "128",
            "256"});
            this.cboTranslateRight.Location = new System.Drawing.Point(154, 15);
            this.cboTranslateRight.Name = "cboTranslateRight";
            this.cboTranslateRight.Size = new System.Drawing.Size(75, 21);
            this.cboTranslateRight.TabIndex = 0;
            this.cboTranslateRight.Text = "128";
            this.cboTranslateRight.Validating += new System.ComponentModel.CancelEventHandler(this.cboIntVal_Validating);
            // 
            // grpZoom
            // 
            this.grpZoom.Controls.Add(this.grpZoomLocation);
            this.grpZoom.Controls.Add(this.cboZoomMethod);
            this.grpZoom.Controls.Add(this.lblZoomMethod);
            this.grpZoom.Controls.Add(this.cboZoomFactor);
            this.grpZoom.Controls.Add(this.lblZoomFactor);
            this.grpZoom.Location = new System.Drawing.Point(4, 303);
            this.grpZoom.Name = "grpZoom";
            this.grpZoom.Size = new System.Drawing.Size(632, 141);
            this.grpZoom.TabIndex = 11;
            this.grpZoom.TabStop = false;
            // 
            // grpZoomLocation
            // 
            this.grpZoomLocation.Controls.Add(this.lblZoomPixels);
            this.grpZoomLocation.Controls.Add(this.cboZoomHeight);
            this.grpZoomLocation.Controls.Add(this.lblZoomHeight);
            this.grpZoomLocation.Controls.Add(this.cboZoomWidth);
            this.grpZoomLocation.Controls.Add(this.lblZoomWidth);
            this.grpZoomLocation.Controls.Add(this.cboZoomRow);
            this.grpZoomLocation.Controls.Add(this.lblZoomRow);
            this.grpZoomLocation.Controls.Add(this.cboZoomCol);
            this.grpZoomLocation.Controls.Add(this.rbZoomArea);
            this.grpZoomLocation.Controls.Add(this.rbZoomLowerRight);
            this.grpZoomLocation.Controls.Add(this.rbZoomLowerLeft);
            this.grpZoomLocation.Controls.Add(this.rbZoomUpperRight);
            this.grpZoomLocation.Controls.Add(this.rbZoomUpperLeft);
            this.grpZoomLocation.Location = new System.Drawing.Point(24, 32);
            this.grpZoomLocation.Name = "grpZoomLocation";
            this.grpZoomLocation.Size = new System.Drawing.Size(393, 100);
            this.grpZoomLocation.TabIndex = 4;
            this.grpZoomLocation.TabStop = false;
            this.grpZoomLocation.Enter += new System.EventHandler(this.grpZoomLocation_Enter);
            // 
            // lblZoomPixels
            // 
            this.lblZoomPixels.AutoSize = true;
            this.lblZoomPixels.Location = new System.Drawing.Point(351, 73);
            this.lblZoomPixels.Name = "lblZoomPixels";
            this.lblZoomPixels.Size = new System.Drawing.Size(36, 13);
            this.lblZoomPixels.TabIndex = 12;
            this.lblZoomPixels.Text = "pixels.";
            // 
            // cboZoomHeight
            // 
            this.cboZoomHeight.FormattingEnabled = true;
            this.cboZoomHeight.Items.AddRange(new object[] {
            "0",
            "8",
            "16",
            "32",
            "64",
            "128",
            "256",
            "512"});
            this.cboZoomHeight.Location = new System.Drawing.Point(291, 68);
            this.cboZoomHeight.Name = "cboZoomHeight";
            this.cboZoomHeight.Size = new System.Drawing.Size(60, 21);
            this.cboZoomHeight.TabIndex = 11;
            this.cboZoomHeight.Text = "64";
            this.cboZoomHeight.Validating += new System.ComponentModel.CancelEventHandler(this.cboPositiveIntVal_Validating);
            this.cboZoomHeight.Validated += new System.EventHandler(this.cboCropZoom_Validated);
            // 
            // lblZoomHeight
            // 
            this.lblZoomHeight.AutoSize = true;
            this.lblZoomHeight.Location = new System.Drawing.Point(216, 73);
            this.lblZoomHeight.Name = "lblZoomHeight";
            this.lblZoomHeight.Size = new System.Drawing.Size(69, 13);
            this.lblZoomHeight.TabIndex = 10;
            this.lblZoomHeight.Text = "and height of";
            // 
            // cboZoomWidth
            // 
            this.cboZoomWidth.FormattingEnabled = true;
            this.cboZoomWidth.Items.AddRange(new object[] {
            "0",
            "8",
            "16",
            "32",
            "64",
            "128",
            "256",
            "512"});
            this.cboZoomWidth.Location = new System.Drawing.Point(154, 69);
            this.cboZoomWidth.Name = "cboZoomWidth";
            this.cboZoomWidth.Size = new System.Drawing.Size(60, 21);
            this.cboZoomWidth.TabIndex = 9;
            this.cboZoomWidth.Text = "64";
            this.cboZoomWidth.Validating += new System.ComponentModel.CancelEventHandler(this.cboPositiveIntVal_Validating);
            this.cboZoomWidth.Validated += new System.EventHandler(this.cboCropZoom_Validated);
            // 
            // lblZoomWidth
            // 
            this.lblZoomWidth.AutoSize = true;
            this.lblZoomWidth.Location = new System.Drawing.Point(70, 73);
            this.lblZoomWidth.Name = "lblZoomWidth";
            this.lblZoomWidth.Size = new System.Drawing.Size(78, 13);
            this.lblZoomWidth.TabIndex = 8;
            this.lblZoomWidth.Text = "with a width of ";
            // 
            // cboZoomRow
            // 
            this.cboZoomRow.FormattingEnabled = true;
            this.cboZoomRow.Items.AddRange(new object[] {
            "0",
            "8",
            "16",
            "32",
            "64",
            "128",
            "256",
            "512"});
            this.cboZoomRow.Location = new System.Drawing.Point(291, 41);
            this.cboZoomRow.Name = "cboZoomRow";
            this.cboZoomRow.Size = new System.Drawing.Size(60, 21);
            this.cboZoomRow.TabIndex = 7;
            this.cboZoomRow.Text = "0";
            this.cboZoomRow.Validating += new System.ComponentModel.CancelEventHandler(this.cboUIntVal_Validating);
            this.cboZoomRow.Validated += new System.EventHandler(this.cboCropZoom_Validated);
            // 
            // lblZoomRow
            // 
            this.lblZoomRow.AutoSize = true;
            this.lblZoomRow.Location = new System.Drawing.Point(219, 45);
            this.lblZoomRow.Name = "lblZoomRow";
            this.lblZoomRow.Size = new System.Drawing.Size(45, 13);
            this.lblZoomRow.TabIndex = 6;
            this.lblZoomRow.Text = "and row";
            // 
            // cboZoomCol
            // 
            this.cboZoomCol.FormattingEnabled = true;
            this.cboZoomCol.Items.AddRange(new object[] {
            "0",
            "8",
            "16",
            "32",
            "64",
            "128",
            "256",
            "512"});
            this.cboZoomCol.Location = new System.Drawing.Point(154, 41);
            this.cboZoomCol.Name = "cboZoomCol";
            this.cboZoomCol.Size = new System.Drawing.Size(60, 21);
            this.cboZoomCol.TabIndex = 5;
            this.cboZoomCol.Text = "0";
            this.cboZoomCol.Validating += new System.ComponentModel.CancelEventHandler(this.cboUIntVal_Validating);
            this.cboZoomCol.Validated += new System.EventHandler(this.cboCropZoom_Validated);
            // 
            // rbZoomArea
            // 
            this.rbZoomArea.AutoSize = true;
            this.rbZoomArea.Checked = true;
            this.rbZoomArea.Location = new System.Drawing.Point(8, 43);
            this.rbZoomArea.Name = "rbZoomArea";
            this.rbZoomArea.Size = new System.Drawing.Size(145, 17);
            this.rbZoomArea.TabIndex = 4;
            this.rbZoomArea.TabStop = true;
            this.rbZoomArea.Text = "Area beginning at column";
            this.rbZoomArea.UseVisualStyleBackColor = true;
            // 
            // rbZoomLowerRight
            // 
            this.rbZoomLowerRight.AutoSize = true;
            this.rbZoomLowerRight.Location = new System.Drawing.Point(256, 16);
            this.rbZoomLowerRight.Name = "rbZoomLowerRight";
            this.rbZoomLowerRight.Size = new System.Drawing.Size(82, 17);
            this.rbZoomLowerRight.TabIndex = 3;
            this.rbZoomLowerRight.Text = "Lower Right";
            this.rbZoomLowerRight.UseVisualStyleBackColor = true;
            // 
            // rbZoomLowerLeft
            // 
            this.rbZoomLowerLeft.AutoSize = true;
            this.rbZoomLowerLeft.Location = new System.Drawing.Point(176, 16);
            this.rbZoomLowerLeft.Name = "rbZoomLowerLeft";
            this.rbZoomLowerLeft.Size = new System.Drawing.Size(75, 17);
            this.rbZoomLowerLeft.TabIndex = 2;
            this.rbZoomLowerLeft.Text = "Lower Left";
            this.rbZoomLowerLeft.UseVisualStyleBackColor = true;
            // 
            // rbZoomUpperRight
            // 
            this.rbZoomUpperRight.AutoSize = true;
            this.rbZoomUpperRight.Location = new System.Drawing.Point(88, 16);
            this.rbZoomUpperRight.Name = "rbZoomUpperRight";
            this.rbZoomUpperRight.Size = new System.Drawing.Size(82, 17);
            this.rbZoomUpperRight.TabIndex = 1;
            this.rbZoomUpperRight.Text = "Upper Right";
            this.rbZoomUpperRight.UseVisualStyleBackColor = true;
            // 
            // rbZoomUpperLeft
            // 
            this.rbZoomUpperLeft.AutoSize = true;
            this.rbZoomUpperLeft.Location = new System.Drawing.Point(8, 16);
            this.rbZoomUpperLeft.Name = "rbZoomUpperLeft";
            this.rbZoomUpperLeft.Size = new System.Drawing.Size(75, 17);
            this.rbZoomUpperLeft.TabIndex = 0;
            this.rbZoomUpperLeft.Text = "Upper Left";
            this.rbZoomUpperLeft.UseVisualStyleBackColor = true;
            // 
            // cboZoomMethod
            // 
            this.cboZoomMethod.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cboZoomMethod.FormattingEnabled = true;
            this.cboZoomMethod.Items.AddRange(new object[] {
            "zero order hold",
            "linear interpolation"});
            this.cboZoomMethod.Location = new System.Drawing.Point(455, 101);
            this.cboZoomMethod.Name = "cboZoomMethod";
            this.cboZoomMethod.Size = new System.Drawing.Size(110, 21);
            this.cboZoomMethod.TabIndex = 3;
            // 
            // lblZoomMethod
            // 
            this.lblZoomMethod.AutoSize = true;
            this.lblZoomMethod.Location = new System.Drawing.Point(423, 105);
            this.lblZoomMethod.Name = "lblZoomMethod";
            this.lblZoomMethod.Size = new System.Drawing.Size(26, 13);
            this.lblZoomMethod.TabIndex = 2;
            this.lblZoomMethod.Text = "Use";
            // 
            // cboZoomFactor
            // 
            this.cboZoomFactor.FormattingEnabled = true;
            this.cboZoomFactor.Items.AddRange(new object[] {
            "0.5",
            "0.8",
            "1.2",
            "1.5",
            "2.0",
            "3.0",
            "4.0",
            "5.0"});
            this.cboZoomFactor.Location = new System.Drawing.Point(467, 69);
            this.cboZoomFactor.Name = "cboZoomFactor";
            this.cboZoomFactor.Size = new System.Drawing.Size(57, 21);
            this.cboZoomFactor.TabIndex = 1;
            this.cboZoomFactor.Text = "2.0";
            this.cboZoomFactor.Validating += new System.ComponentModel.CancelEventHandler(this.cboZoomFactor_Validating);
            // 
            // lblZoomFactor
            // 
            this.lblZoomFactor.AutoSize = true;
            this.lblZoomFactor.Location = new System.Drawing.Point(435, 73);
            this.lblZoomFactor.Name = "lblZoomFactor";
            this.lblZoomFactor.Size = new System.Drawing.Size(19, 13);
            this.lblZoomFactor.TabIndex = 0;
            this.lblZoomFactor.Text = "By";
            // 
            // btnHelp
            // 
            this.btnHelp.BackColor = System.Drawing.Color.Yellow;
            this.btnHelp.Location = new System.Drawing.Point(17, 515);
            this.btnHelp.Name = "btnHelp";
            this.btnHelp.Size = new System.Drawing.Size(60, 26);
            this.btnHelp.TabIndex = 12;
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
            this.btnCancel.TabIndex = 13;
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
            this.btnReset.TabIndex = 14;
            this.btnReset.Text = "Reset";
            this.btnReset.UseVisualStyleBackColor = false;
            this.btnReset.Click += new System.EventHandler(this.btnReset_Click);
            // 
            // btnApply
            // 
            this.btnApply.BackColor = System.Drawing.Color.LimeGreen;
            this.btnApply.ForeColor = System.Drawing.Color.White;
            this.btnApply.Location = new System.Drawing.Point(574, 515);
            this.btnApply.Name = "btnApply";
            this.btnApply.Size = new System.Drawing.Size(60, 26);
            this.btnApply.TabIndex = 15;
            this.btnApply.Text = "Apply";
            this.btnApply.UseVisualStyleBackColor = false;
            this.btnApply.Click += new System.EventHandler(this.btnApply_Click);
            // 
            // Geometry
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.btnApply);
            this.Controls.Add(this.btnReset);
            this.Controls.Add(this.btnCancel);
            this.Controls.Add(this.btnHelp);
            this.Controls.Add(this.rbZoom);
            this.Controls.Add(this.rbTranslate);
            this.Controls.Add(this.rbRotate);
            this.Controls.Add(this.rbResize);
            this.Controls.Add(this.rbPaste);
            this.Controls.Add(this.rbCrop);
            this.Controls.Add(this.grpZoom);
            this.Controls.Add(this.grpTranslate);
            this.Controls.Add(this.grpRotate);
            this.Controls.Add(this.grpResize);
            this.Controls.Add(this.grpPaste);
            this.Controls.Add(this.grpCrop);
            this.Name = "Geometry";
            this.Size = new System.Drawing.Size(679, 555);
            this.grpCrop.ResumeLayout(false);
            this.grpCrop.PerformLayout();
            this.grpPaste.ResumeLayout(false);
            this.grpPaste.PerformLayout();
            this.grpResize.ResumeLayout(false);
            this.grpResize.PerformLayout();
            this.grpRotate.ResumeLayout(false);
            this.grpRotate.PerformLayout();
            this.grpTranslate.ResumeLayout(false);
            this.grpTranslate.PerformLayout();
            this.grpZoom.ResumeLayout(false);
            this.grpZoom.PerformLayout();
            this.grpZoomLocation.ResumeLayout(false);
            this.grpZoomLocation.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.RadioButton rbCrop;
        private System.Windows.Forms.RadioButton rbPaste;
        private System.Windows.Forms.RadioButton rbResize;
        private System.Windows.Forms.RadioButton rbRotate;
        private System.Windows.Forms.RadioButton rbTranslate;
        private System.Windows.Forms.RadioButton rbZoom;
        private System.Windows.Forms.GroupBox grpCrop;
        private System.Windows.Forms.ComboBox cboCropHeight;
        private System.Windows.Forms.Label lblCropHeight;
        private System.Windows.Forms.ComboBox cboCropWidth;
        private System.Windows.Forms.Label lblCropWidth;
        private System.Windows.Forms.ComboBox cboCropRow;
        private System.Windows.Forms.Label lblCropRow;
        private System.Windows.Forms.ComboBox cboCropCol;
        private System.Windows.Forms.GroupBox grpPaste;
        private System.Windows.Forms.Label lblTransparently;
        private System.Windows.Forms.ComboBox cboPasteRow;
        private System.Windows.Forms.Label lblPasteRow;
        private System.Windows.Forms.ComboBox cboPasteCol;
        private System.Windows.Forms.Label lblPasteCol;
        private System.Windows.Forms.CheckBox chkTransparently;
        private System.Windows.Forms.ComboBox cboImages;
        private System.Windows.Forms.GroupBox grpResize;
        private System.Windows.Forms.ComboBox cboResizeMethod;
        private System.Windows.Forms.Label lblResizeMethod;
        private System.Windows.Forms.ComboBox cboResizeHeight;
        private System.Windows.Forms.Label lblResizeHeight;
        private System.Windows.Forms.ComboBox cboResizeWidth;
        private System.Windows.Forms.GroupBox grpRotate;
        private System.Windows.Forms.Label lblRotateDegrees;
        private System.Windows.Forms.ComboBox cboRotateDegrees;
        private System.Windows.Forms.GroupBox grpTranslate;
        private System.Windows.Forms.ComboBox cboTranslateGrayLevel;
        private System.Windows.Forms.CheckBox chkTranslateWrap;
        private System.Windows.Forms.Label lblTranslateDown;
        private System.Windows.Forms.ComboBox cboTranslateDown;
        private System.Windows.Forms.Label lblTranslateRight;
        private System.Windows.Forms.ComboBox cboTranslateRight;
        private System.Windows.Forms.GroupBox grpZoom;
        private System.Windows.Forms.GroupBox grpZoomLocation;
        private System.Windows.Forms.Label lblZoomPixels;
        private System.Windows.Forms.ComboBox cboZoomHeight;
        private System.Windows.Forms.Label lblZoomHeight;
        private System.Windows.Forms.ComboBox cboZoomWidth;
        private System.Windows.Forms.Label lblZoomWidth;
        private System.Windows.Forms.ComboBox cboZoomRow;
        private System.Windows.Forms.Label lblZoomRow;
        private System.Windows.Forms.ComboBox cboZoomCol;
        private System.Windows.Forms.RadioButton rbZoomArea;
        private System.Windows.Forms.RadioButton rbZoomLowerRight;
        private System.Windows.Forms.RadioButton rbZoomLowerLeft;
        private System.Windows.Forms.RadioButton rbZoomUpperRight;
        private System.Windows.Forms.RadioButton rbZoomUpperLeft;
        private System.Windows.Forms.ComboBox cboZoomMethod;
        private System.Windows.Forms.Label lblZoomMethod;
        private System.Windows.Forms.ComboBox cboZoomFactor;
        private System.Windows.Forms.Label lblZoomFactor;
        private System.Windows.Forms.Button btnHelp;
        private System.Windows.Forms.Button btnCancel;
        private System.Windows.Forms.Button btnReset;
        private System.Windows.Forms.Button btnApply;
        private System.Windows.Forms.Label lblWrapText;
    }
}
