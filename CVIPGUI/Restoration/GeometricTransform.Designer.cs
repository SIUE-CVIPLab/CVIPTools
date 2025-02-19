namespace CVIPGUI.Restoration
{
    partial class GeometricTransform
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(GeometricTransform));
            this.rbNewMesh = new System.Windows.Forms.RadioButton();
            this.rbOpenMesh = new System.Windows.Forms.RadioButton();
            this.rbSineMesh = new System.Windows.Forms.RadioButton();
            this.grpSelections = new System.Windows.Forms.GroupBox();
            this.lblNotes = new System.Windows.Forms.Label();
            this.grpParameters = new System.Windows.Forms.GroupBox();
            this.lblInterpMethod = new System.Windows.Forms.Label();
            this.cboInterpMethod = new System.Windows.Forms.ComboBox();
            this.lblDirection = new System.Windows.Forms.Label();
            this.cboDirection = new System.Windows.Forms.ComboBox();
            this.grpOpenMesh = new System.Windows.Forms.GroupBox();
            this.btnMeshFile = new System.Windows.Forms.Button();
            this.lblMeshFile = new System.Windows.Forms.Label();
            this.grpNewMesh = new System.Windows.Forms.GroupBox();
            this.picMeshExample = new System.Windows.Forms.PictureBox();
            this.lblExample = new System.Windows.Forms.Label();
            this.lblMeshStatus = new System.Windows.Forms.Label();
            this.btnSaveMesh = new System.Windows.Forms.Button();
            this.btnRedoMesh = new System.Windows.Forms.Button();
            this.lblMeshRow = new System.Windows.Forms.Label();
            this.txtMeshRow = new System.Windows.Forms.TextBox();
            this.lblMeshCol = new System.Windows.Forms.Label();
            this.txtMeshCol = new System.Windows.Forms.TextBox();
            this.lblMeshPoint = new System.Windows.Forms.Label();
            this.cboMeshPoint = new System.Windows.Forms.ComboBox();
            this.lblNumPoints1 = new System.Windows.Forms.Label();
            this.lblNumPoints = new System.Windows.Forms.Label();
            this.txtNumPoints = new System.Windows.Forms.Label();
            this.lblMeshPoints = new System.Windows.Forms.Label();
            this.lblMeshRows = new System.Windows.Forms.Label();
            this.cboMeshRows = new System.Windows.Forms.ComboBox();
            this.lblMeshCols = new System.Windows.Forms.Label();
            this.cboMeshCols = new System.Windows.Forms.ComboBox();
            this.btnHelp = new System.Windows.Forms.Button();
            this.btnCancel = new System.Windows.Forms.Button();
            this.btnReset = new System.Windows.Forms.Button();
            this.btnApply = new System.Windows.Forms.Button();
            this.grpSelections.SuspendLayout();
            this.grpParameters.SuspendLayout();
            this.grpOpenMesh.SuspendLayout();
            this.grpNewMesh.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.picMeshExample)).BeginInit();
            this.SuspendLayout();
            // 
            // rbNewMesh
            // 
            this.rbNewMesh.AutoSize = true;
            this.rbNewMesh.Checked = true;
            this.rbNewMesh.Location = new System.Drawing.Point(24, 28);
            this.rbNewMesh.Name = "rbNewMesh";
            this.rbNewMesh.Size = new System.Drawing.Size(126, 17);
            this.rbNewMesh.TabIndex = 0;
            this.rbNewMesh.TabStop = true;
            this.rbNewMesh.Text = "Enter a new mesh file";
            this.rbNewMesh.UseVisualStyleBackColor = true;
            this.rbNewMesh.Click += new System.EventHandler(this.rbGeoTransforms_Click);
            // 
            // rbOpenMesh
            // 
            this.rbOpenMesh.AutoSize = true;
            this.rbOpenMesh.Location = new System.Drawing.Point(24, 57);
            this.rbOpenMesh.Name = "rbOpenMesh";
            this.rbOpenMesh.Size = new System.Drawing.Size(141, 17);
            this.rbOpenMesh.TabIndex = 1;
            this.rbOpenMesh.Text = "Use an existing mesh file";
            this.rbOpenMesh.UseVisualStyleBackColor = true;
            this.rbOpenMesh.Click += new System.EventHandler(this.rbGeoTransforms_Click);
            // 
            // rbSineMesh
            // 
            this.rbSineMesh.AutoSize = true;
            this.rbSineMesh.Location = new System.Drawing.Point(24, 86);
            this.rbSineMesh.Name = "rbSineMesh";
            this.rbSineMesh.Size = new System.Drawing.Size(115, 17);
            this.rbSineMesh.TabIndex = 2;
            this.rbSineMesh.Text = "Create a sine mesh";
            this.rbSineMesh.UseVisualStyleBackColor = true;
            this.rbSineMesh.Click += new System.EventHandler(this.rbGeoTransforms_Click);
            // 
            // grpSelections
            // 
            this.grpSelections.Controls.Add(this.lblNotes);
            this.grpSelections.Location = new System.Drawing.Point(8, 8);
            this.grpSelections.Name = "grpSelections";
            this.grpSelections.Size = new System.Drawing.Size(193, 449);
            this.grpSelections.TabIndex = 3;
            this.grpSelections.TabStop = false;
            // 
            // lblNotes
            // 
            this.lblNotes.AutoSize = true;
            this.lblNotes.ForeColor = System.Drawing.Color.Blue;
            this.lblNotes.Location = new System.Drawing.Point(8, 312);
            this.lblNotes.Name = "lblNotes";
            this.lblNotes.Size = new System.Drawing.Size(174, 91);
            this.lblNotes.TabIndex = 0;
            this.lblNotes.Text = "Notes:\n\n1) Right click on the image to show\nselect box to turn on/off the mesh\ndi" +
    "splay, then left-click to do it.\n\n2) Only NxN meshes are supported.";
            // 
            // grpParameters
            // 
            this.grpParameters.Controls.Add(this.lblInterpMethod);
            this.grpParameters.Controls.Add(this.cboInterpMethod);
            this.grpParameters.Controls.Add(this.lblDirection);
            this.grpParameters.Controls.Add(this.cboDirection);
            this.grpParameters.Location = new System.Drawing.Point(208, 8);
            this.grpParameters.Name = "grpParameters";
            this.grpParameters.Size = new System.Drawing.Size(385, 65);
            this.grpParameters.TabIndex = 4;
            this.grpParameters.TabStop = false;
            // 
            // lblInterpMethod
            // 
            this.lblInterpMethod.AutoSize = true;
            this.lblInterpMethod.Location = new System.Drawing.Point(191, 18);
            this.lblInterpMethod.Name = "lblInterpMethod";
            this.lblInterpMethod.Size = new System.Drawing.Size(156, 13);
            this.lblInterpMethod.TabIndex = 3;
            this.lblInterpMethod.Text = "Gray value interpolation method";
            // 
            // cboInterpMethod
            // 
            this.cboInterpMethod.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cboInterpMethod.FormattingEnabled = true;
            this.cboInterpMethod.Items.AddRange(new object[] {
            "Nearest neighbor (quick)",
            "Neighborhood average (medium)",
            "Bilinear interpolation (slow)"});
            this.cboInterpMethod.Location = new System.Drawing.Point(191, 34);
            this.cboInterpMethod.Name = "cboInterpMethod";
            this.cboInterpMethod.SelectedIndex = 0;
            this.cboInterpMethod.Size = new System.Drawing.Size(175, 21);
            this.cboInterpMethod.TabIndex = 2;
            // 
            // lblDirection
            // 
            this.lblDirection.AutoSize = true;
            this.lblDirection.Location = new System.Drawing.Point(11, 18);
            this.lblDirection.Name = "lblDirection";
            this.lblDirection.Size = new System.Drawing.Size(49, 13);
            this.lblDirection.TabIndex = 1;
            this.lblDirection.Text = "Direction";
            // 
            // cboDirection
            // 
            this.cboDirection.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cboDirection.FormattingEnabled = true;
            this.cboDirection.Items.AddRange(new object[] {
            "Regular -> Irregular",
            "Irregular -> Regular"});
            this.cboDirection.Location = new System.Drawing.Point(11, 34);
            this.cboDirection.Name = "cboDirection";
            this.cboDirection.SelectedIndex = 0;
            this.cboDirection.Size = new System.Drawing.Size(150, 21);
            this.cboDirection.TabIndex = 0;
            // 
            // grpOpenMesh
            // 
            this.grpOpenMesh.Controls.Add(this.btnMeshFile);
            this.grpOpenMesh.Controls.Add(this.lblMeshFile);
            this.grpOpenMesh.Location = new System.Drawing.Point(208, 80);
            this.grpOpenMesh.Name = "grpOpenMesh";
            this.grpOpenMesh.Size = new System.Drawing.Size(385, 49);
            this.grpOpenMesh.TabIndex = 5;
            this.grpOpenMesh.TabStop = false;
            this.grpOpenMesh.Text = "Mesh File";
            // 
            // btnMeshFile
            // 
            this.btnMeshFile.Location = new System.Drawing.Point(301, 17);
            this.btnMeshFile.Name = "btnMeshFile";
            this.btnMeshFile.Size = new System.Drawing.Size(75, 23);
            this.btnMeshFile.TabIndex = 1;
            this.btnMeshFile.Text = "Select";
            this.btnMeshFile.UseVisualStyleBackColor = true;
            this.btnMeshFile.Click += new System.EventHandler(this.btnMeshFile_Click);
            // 
            // lblMeshFile
            // 
            this.lblMeshFile.BackColor = System.Drawing.Color.White;
            this.lblMeshFile.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.lblMeshFile.Location = new System.Drawing.Point(10, 18);
            this.lblMeshFile.Name = "lblMeshFile";
            this.lblMeshFile.Size = new System.Drawing.Size(280, 21);
            this.lblMeshFile.TabIndex = 0;
            this.lblMeshFile.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // grpNewMesh
            // 
            this.grpNewMesh.Controls.Add(this.picMeshExample);
            this.grpNewMesh.Controls.Add(this.lblExample);
            this.grpNewMesh.Controls.Add(this.lblMeshStatus);
            this.grpNewMesh.Controls.Add(this.btnSaveMesh);
            this.grpNewMesh.Controls.Add(this.btnRedoMesh);
            this.grpNewMesh.Controls.Add(this.lblMeshRow);
            this.grpNewMesh.Controls.Add(this.txtMeshRow);
            this.grpNewMesh.Controls.Add(this.lblMeshCol);
            this.grpNewMesh.Controls.Add(this.txtMeshCol);
            this.grpNewMesh.Controls.Add(this.lblMeshPoint);
            this.grpNewMesh.Controls.Add(this.cboMeshPoint);
            this.grpNewMesh.Controls.Add(this.lblNumPoints1);
            this.grpNewMesh.Controls.Add(this.lblNumPoints);
            this.grpNewMesh.Controls.Add(this.txtNumPoints);
            this.grpNewMesh.Controls.Add(this.lblMeshPoints);
            this.grpNewMesh.Controls.Add(this.lblMeshRows);
            this.grpNewMesh.Controls.Add(this.cboMeshRows);
            this.grpNewMesh.Controls.Add(this.lblMeshCols);
            this.grpNewMesh.Controls.Add(this.cboMeshCols);
            this.grpNewMesh.Location = new System.Drawing.Point(208, 136);
            this.grpNewMesh.Name = "grpNewMesh";
            this.grpNewMesh.Size = new System.Drawing.Size(385, 321);
            this.grpNewMesh.TabIndex = 6;
            this.grpNewMesh.TabStop = false;
            this.grpNewMesh.Text = "New Mesh";
            // 
            // picMeshExample
            // 
            this.picMeshExample.Image = ((System.Drawing.Image)(resources.GetObject("picMeshExample.Image")));
            this.picMeshExample.Location = new System.Drawing.Point(192, 192);
            this.picMeshExample.Name = "picMeshExample";
            this.picMeshExample.Size = new System.Drawing.Size(121, 73);
            this.picMeshExample.TabIndex = 18;
            this.picMeshExample.TabStop = false;
            // 
            // lblExample
            // 
            this.lblExample.AutoSize = true;
            this.lblExample.ForeColor = System.Drawing.Color.Blue;
            this.lblExample.Location = new System.Drawing.Point(12, 184);
            this.lblExample.Name = "lblExample";
            this.lblExample.Size = new System.Drawing.Size(169, 65);
            this.lblExample.TabIndex = 17;
            this.lblExample.Text = "Example:\n\nPress \'Alt-key + Left-mouse-button\'\nto enter the 3x3 mesh points in\nord" +
    "er as shown.";
            // 
            // lblMeshStatus
            // 
            this.lblMeshStatus.ForeColor = System.Drawing.Color.Red;
            this.lblMeshStatus.Location = new System.Drawing.Point(12, 130);
            this.lblMeshStatus.Name = "lblMeshStatus";
            this.lblMeshStatus.Size = new System.Drawing.Size(282, 13);
            this.lblMeshStatus.TabIndex = 16;
            this.lblMeshStatus.Text = "New mesh has been created. Please Apply it to the image.";
            // 
            // btnSaveMesh
            // 
            this.btnSaveMesh.Location = new System.Drawing.Point(301, 105);
            this.btnSaveMesh.Name = "btnSaveMesh";
            this.btnSaveMesh.Size = new System.Drawing.Size(75, 23);
            this.btnSaveMesh.TabIndex = 15;
            this.btnSaveMesh.Text = "Save Mesh";
            this.btnSaveMesh.UseVisualStyleBackColor = true;
            this.btnSaveMesh.Click += new System.EventHandler(this.btnSaveMesh_Click);
            // 
            // btnRedoMesh
            // 
            this.btnRedoMesh.Location = new System.Drawing.Point(301, 74);
            this.btnRedoMesh.Name = "btnRedoMesh";
            this.btnRedoMesh.Size = new System.Drawing.Size(75, 23);
            this.btnRedoMesh.TabIndex = 14;
            this.btnRedoMesh.Text = "Redo";
            this.btnRedoMesh.UseVisualStyleBackColor = true;
            this.btnRedoMesh.Click += new System.EventHandler(this.btnRedoMesh_Click);
            // 
            // lblMeshRow
            // 
            this.lblMeshRow.AutoSize = true;
            this.lblMeshRow.Location = new System.Drawing.Point(195, 89);
            this.lblMeshRow.Name = "lblMeshRow";
            this.lblMeshRow.Size = new System.Drawing.Size(45, 13);
            this.lblMeshRow.TabIndex = 13;
            this.lblMeshRow.Text = "and row";
            // 
            // txtMeshRow
            // 
            this.txtMeshRow.Location = new System.Drawing.Point(241, 85);
            this.txtMeshRow.Name = "txtMeshRow";
            this.txtMeshRow.Size = new System.Drawing.Size(45, 20);
            this.txtMeshRow.TabIndex = 12;
            this.txtMeshRow.Validated += new System.EventHandler(this.txtMeshPoint_Validated);
            // 
            // lblMeshCol
            // 
            this.lblMeshCol.AutoSize = true;
            this.lblMeshCol.Location = new System.Drawing.Point(107, 89);
            this.lblMeshCol.Name = "lblMeshCol";
            this.lblMeshCol.Size = new System.Drawing.Size(41, 13);
            this.lblMeshCol.TabIndex = 11;
            this.lblMeshCol.Text = "column";
            // 
            // txtMeshCol
            // 
            this.txtMeshCol.Location = new System.Drawing.Point(149, 85);
            this.txtMeshCol.Name = "txtMeshCol";
            this.txtMeshCol.Size = new System.Drawing.Size(45, 20);
            this.txtMeshCol.TabIndex = 10;
            this.txtMeshCol.Validated += new System.EventHandler(this.txtMeshPoint_Validated);
            // 
            // lblMeshPoint
            // 
            this.lblMeshPoint.AutoSize = true;
            this.lblMeshPoint.Location = new System.Drawing.Point(12, 89);
            this.lblMeshPoint.Name = "lblMeshPoint";
            this.lblMeshPoint.Size = new System.Drawing.Size(48, 13);
            this.lblMeshPoint.TabIndex = 9;
            this.lblMeshPoint.Text = "For point";
            // 
            // cboMeshPoint
            // 
            this.cboMeshPoint.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cboMeshPoint.FormattingEnabled = true;
            this.cboMeshPoint.Location = new System.Drawing.Point(61, 85);
            this.cboMeshPoint.Name = "cboMeshPoint";
            this.cboMeshPoint.Size = new System.Drawing.Size(45, 21);
            this.cboMeshPoint.TabIndex = 8;
            this.cboMeshPoint.SelectedIndexChanged += new System.EventHandler(this.cboMeshPoint_SelectedIndexChanged);
            // 
            // lblNumPoints1
            // 
            this.lblNumPoints1.AutoSize = true;
            this.lblNumPoints1.Location = new System.Drawing.Point(146, 58);
            this.lblNumPoints1.Name = "lblNumPoints1";
            this.lblNumPoints1.Size = new System.Drawing.Size(38, 13);
            this.lblNumPoints1.TabIndex = 7;
            this.lblNumPoints1.Text = "points.";
            // 
            // lblNumPoints
            // 
            this.lblNumPoints.AutoSize = true;
            this.lblNumPoints.Location = new System.Drawing.Point(12, 58);
            this.lblNumPoints.Name = "lblNumPoints";
            this.lblNumPoints.Size = new System.Drawing.Size(98, 13);
            this.lblNumPoints.TabIndex = 6;
            this.lblNumPoints.Text = "This mesh requires ";
            // 
            // txtNumPoints
            // 
            this.txtNumPoints.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.txtNumPoints.Location = new System.Drawing.Point(110, 54);
            this.txtNumPoints.Name = "txtNumPoints";
            this.txtNumPoints.Size = new System.Drawing.Size(35, 20);
            this.txtNumPoints.TabIndex = 5;
            this.txtNumPoints.Text = "9";
            this.txtNumPoints.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // lblMeshPoints
            // 
            this.lblMeshPoints.AutoSize = true;
            this.lblMeshPoints.Location = new System.Drawing.Point(288, 27);
            this.lblMeshPoints.Name = "lblMeshPoints";
            this.lblMeshPoints.Size = new System.Drawing.Size(78, 13);
            this.lblMeshPoints.TabIndex = 4;
            this.lblMeshPoints.Text = "of mesh points.";
            // 
            // lblMeshRows
            // 
            this.lblMeshRows.AutoSize = true;
            this.lblMeshRows.Location = new System.Drawing.Point(188, 27);
            this.lblMeshRows.Name = "lblMeshRows";
            this.lblMeshRows.Size = new System.Drawing.Size(50, 13);
            this.lblMeshRows.TabIndex = 3;
            this.lblMeshRows.Text = "and rows";
            // 
            // cboMeshRows
            // 
            this.cboMeshRows.FormattingEnabled = true;
            this.cboMeshRows.Items.AddRange(new object[] {
            "2",
            "3",
            "4",
            "5",
            "6",
            "7",
            "8",
            "9",
            "10",
            "11",
            "12",
            "13",
            "14",
            "15",
            "16"});
            this.cboMeshRows.Location = new System.Drawing.Point(241, 23);
            this.cboMeshRows.Name = "cboMeshRows";
            this.cboMeshRows.Size = new System.Drawing.Size(45, 21);
            this.cboMeshRows.TabIndex = 2;
            this.cboMeshRows.Text = "5";
            this.cboMeshRows.SelectedIndexChanged += new System.EventHandler(this.cboMeshSize_Validated);
            this.cboMeshRows.Validating += new System.ComponentModel.CancelEventHandler(this.cboUIntVal_Validating);
            this.cboMeshRows.Validated += new System.EventHandler(this.cboMeshSize_Validated);
            // 
            // lblMeshCols
            // 
            this.lblMeshCols.AutoSize = true;
            this.lblMeshCols.Location = new System.Drawing.Point(12, 27);
            this.lblMeshCols.Name = "lblMeshCols";
            this.lblMeshCols.Size = new System.Drawing.Size(129, 13);
            this.lblMeshCols.TabIndex = 1;
            this.lblMeshCols.Text = "Select number of columns";
            // 
            // cboMeshCols
            // 
            this.cboMeshCols.FormattingEnabled = true;
            this.cboMeshCols.Items.AddRange(new object[] {
            "2",
            "3",
            "4",
            "5",
            "6",
            "7",
            "8",
            "9",
            "10",
            "11",
            "12",
            "13",
            "14",
            "15",
            "16"});
            this.cboMeshCols.Location = new System.Drawing.Point(143, 23);
            this.cboMeshCols.Name = "cboMeshCols";
            this.cboMeshCols.Size = new System.Drawing.Size(45, 21);
            this.cboMeshCols.TabIndex = 0;
            this.cboMeshCols.Text = "5";
            this.cboMeshCols.SelectedIndexChanged += new System.EventHandler(this.cboMeshSize_Validated);
            this.cboMeshCols.Validating += new System.ComponentModel.CancelEventHandler(this.cboUIntVal_Validating);
            this.cboMeshCols.Validated += new System.EventHandler(this.cboMeshSize_Validated);
            // 
            // btnHelp
            // 
            this.btnHelp.BackColor = System.Drawing.Color.Yellow;
            this.btnHelp.Location = new System.Drawing.Point(12, 466);
            this.btnHelp.Name = "btnHelp";
            this.btnHelp.Size = new System.Drawing.Size(60, 26);
            this.btnHelp.TabIndex = 7;
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
            this.btnCancel.TabIndex = 8;
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
            this.btnReset.TabIndex = 9;
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
            this.btnApply.TabIndex = 10;
            this.btnApply.Text = "Apply";
            this.btnApply.UseVisualStyleBackColor = false;
            this.btnApply.Click += new System.EventHandler(this.btnApply_Click);
            // 
            // GeometricTransform
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.rbNewMesh);
            this.Controls.Add(this.rbOpenMesh);
            this.Controls.Add(this.rbSineMesh);
            this.Controls.Add(this.grpSelections);
            this.Controls.Add(this.grpParameters);
            this.Controls.Add(this.grpOpenMesh);
            this.Controls.Add(this.grpNewMesh);
            this.Controls.Add(this.btnHelp);
            this.Controls.Add(this.btnCancel);
            this.Controls.Add(this.btnReset);
            this.Controls.Add(this.btnApply);
            this.Name = "GeometricTransform";
            this.Size = new System.Drawing.Size(600, 495);
            this.grpSelections.ResumeLayout(false);
            this.grpSelections.PerformLayout();
            this.grpParameters.ResumeLayout(false);
            this.grpParameters.PerformLayout();
            this.grpOpenMesh.ResumeLayout(false);
            this.grpNewMesh.ResumeLayout(false);
            this.grpNewMesh.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.picMeshExample)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.RadioButton rbNewMesh;
        private System.Windows.Forms.RadioButton rbOpenMesh;
        private System.Windows.Forms.RadioButton rbSineMesh;
        private System.Windows.Forms.GroupBox grpSelections;
        private System.Windows.Forms.Label lblNotes;
        private System.Windows.Forms.GroupBox grpParameters;
        private System.Windows.Forms.Label lblInterpMethod;
        private System.Windows.Forms.ComboBox cboInterpMethod;
        private System.Windows.Forms.Label lblDirection;
        private System.Windows.Forms.ComboBox cboDirection;
        private System.Windows.Forms.GroupBox grpOpenMesh;
        private System.Windows.Forms.Button btnMeshFile;
        private System.Windows.Forms.Label lblMeshFile;
        private System.Windows.Forms.GroupBox grpNewMesh;
        private System.Windows.Forms.PictureBox picMeshExample;
        private System.Windows.Forms.Label lblExample;
        private System.Windows.Forms.Label lblMeshStatus;
        private System.Windows.Forms.Button btnSaveMesh;
        private System.Windows.Forms.Button btnRedoMesh;
        private System.Windows.Forms.Label lblMeshRow;
        private System.Windows.Forms.TextBox txtMeshRow;
        private System.Windows.Forms.Label lblMeshCol;
        private System.Windows.Forms.TextBox txtMeshCol;
        private System.Windows.Forms.Label lblMeshPoint;
        private System.Windows.Forms.ComboBox cboMeshPoint;
        private System.Windows.Forms.Label lblNumPoints1;
        private System.Windows.Forms.Label lblNumPoints;
        private System.Windows.Forms.Label txtNumPoints;
        private System.Windows.Forms.Label lblMeshPoints;
        private System.Windows.Forms.Label lblMeshRows;
        private System.Windows.Forms.ComboBox cboMeshRows;
        private System.Windows.Forms.Label lblMeshCols;
        private System.Windows.Forms.ComboBox cboMeshCols;
        private System.Windows.Forms.Button btnHelp;
        private System.Windows.Forms.Button btnCancel;
        private System.Windows.Forms.Button btnReset;
        private System.Windows.Forms.Button btnApply;
    }
}
