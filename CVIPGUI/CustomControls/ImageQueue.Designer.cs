namespace CVIPGUI
{
    partial class ImageQueue
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
            this.pnlBorder = new System.Windows.Forms.Panel();
            this.pnlLower = new System.Windows.Forms.Panel();
            this.lvViewers = new CVIPGUI.ImageQueueListView();
            this.colImageName = new System.Windows.Forms.ColumnHeader();
            this.pnlUpper = new System.Windows.Forms.Panel();
            this.chkLockInput = new System.Windows.Forms.CheckBox();
            this.btnDeleteAll = new System.Windows.Forms.Button();
            this.btnDelete = new System.Windows.Forms.Button();
            this.splitter = new CVIPGUI.ImageQueueSplitter();
            this.pnlSplitterBottom = new System.Windows.Forms.Panel();
            this.pnlSplitterTop = new System.Windows.Forms.Panel();
            this.pnlBorder.SuspendLayout();
            this.pnlLower.SuspendLayout();
            this.pnlUpper.SuspendLayout();
            this.splitter.SuspendLayout();
            this.SuspendLayout();
            // 
            // pnlBorder
            // 
            this.pnlBorder.BackColor = System.Drawing.SystemColors.Control;
            this.pnlBorder.Controls.Add(this.pnlLower);
            this.pnlBorder.Controls.Add(this.pnlUpper);
            this.pnlBorder.Dock = System.Windows.Forms.DockStyle.Fill;
            this.pnlBorder.Location = new System.Drawing.Point(0, 1);
            this.pnlBorder.Name = "pnlBorder";
            this.pnlBorder.Size = new System.Drawing.Size(135, 329);
            this.pnlBorder.TabIndex = 0;
            // 
            // pnlLower
            // 
            this.pnlLower.Controls.Add(this.lvViewers);
            this.pnlLower.Dock = System.Windows.Forms.DockStyle.Fill;
            this.pnlLower.Location = new System.Drawing.Point(0, 60);
            this.pnlLower.Name = "pnlLower";
            this.pnlLower.Padding = new System.Windows.Forms.Padding(5, 0, 6, 7);
            this.pnlLower.Size = new System.Drawing.Size(135, 269);
            this.pnlLower.TabIndex = 1;
            // 
            // lvViewers
            // 
            this.lvViewers.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.colImageName});
            this.lvViewers.Dock = System.Windows.Forms.DockStyle.Fill;
            this.lvViewers.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lvViewers.FullRowSelect = true;
            this.lvViewers.GridLines = true;
            this.lvViewers.HeaderStyle = System.Windows.Forms.ColumnHeaderStyle.None;
            this.lvViewers.Location = new System.Drawing.Point(5, 0);
            this.lvViewers.Name = "lvViewers";
            this.lvViewers.ShowItemToolTips = true;
            this.lvViewers.Size = new System.Drawing.Size(124, 262);
            this.lvViewers.TabIndex = 0;
            this.lvViewers.UseCompatibleStateImageBehavior = false;
            this.lvViewers.View = System.Windows.Forms.View.Details;
            // 
            // colImageName
            // 
            this.colImageName.Text = "Image Name";
            this.colImageName.Width = 120;
            // 
            // pnlUpper
            // 
            this.pnlUpper.Controls.Add(this.chkLockInput);
            this.pnlUpper.Controls.Add(this.btnDeleteAll);
            this.pnlUpper.Controls.Add(this.btnDelete);
            this.pnlUpper.Dock = System.Windows.Forms.DockStyle.Top;
            this.pnlUpper.Location = new System.Drawing.Point(0, 0);
            this.pnlUpper.Name = "pnlUpper";
            this.pnlUpper.Size = new System.Drawing.Size(135, 60);
            this.pnlUpper.TabIndex = 0;
            // 
            // chkLockInput
            // 
            this.chkLockInput.AutoSize = true;
            this.chkLockInput.Checked = true;
            this.chkLockInput.CheckState = System.Windows.Forms.CheckState.Checked;
            this.chkLockInput.Location = new System.Drawing.Point(25, 37);
            this.chkLockInput.Name = "chkLockInput";
            this.chkLockInput.RightToLeft = System.Windows.Forms.RightToLeft.Yes;
            this.chkLockInput.Size = new System.Drawing.Size(77, 17);
            this.chkLockInput.TabIndex = 2;
            this.chkLockInput.Text = "Lock Input";
            this.chkLockInput.UseVisualStyleBackColor = true;
            // 
            // btnDeleteAll
            // 
            this.btnDeleteAll.Enabled = false;
            this.btnDeleteAll.Location = new System.Drawing.Point(3, 7);
            this.btnDeleteAll.Name = "btnDeleteAll";
            this.btnDeleteAll.Size = new System.Drawing.Size(60, 24);
            this.btnDeleteAll.TabIndex = 0;
            this.btnDeleteAll.Text = "Delete All";
            this.btnDeleteAll.UseVisualStyleBackColor = true;
            this.btnDeleteAll.Click += new System.EventHandler(this.btnDeleteAll_Click);
            // 
            // btnDelete
            // 
            this.btnDelete.Enabled = false;
            this.btnDelete.Location = new System.Drawing.Point(68, 7);
            this.btnDelete.Name = "btnDelete";
            this.btnDelete.Size = new System.Drawing.Size(60, 24);
            this.btnDelete.TabIndex = 1;
            this.btnDelete.Text = "Delete";
            this.btnDelete.UseVisualStyleBackColor = true;
            this.btnDelete.Click += new System.EventHandler(this.btnDelete_Click);
            // 
            // splitter
            // 
            this.splitter.Controls.Add(this.pnlSplitterBottom);
            this.splitter.Controls.Add(this.pnlSplitterTop);
            this.splitter.Location = new System.Drawing.Point(0, 0);
            this.splitter.Name = "splitter";
            this.splitter.Size = new System.Drawing.Size(5, 60);
            this.splitter.TabIndex = 0;
            this.splitter.TabStop = false;
            // 
            // pnlSplitterBottom
            // 
            this.pnlSplitterBottom.BackColor = System.Drawing.SystemColors.ButtonShadow;
            this.pnlSplitterBottom.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.pnlSplitterBottom.Location = new System.Drawing.Point(0, 59);
            this.pnlSplitterBottom.Name = "pnlSplitterBottom";
            this.pnlSplitterBottom.Size = new System.Drawing.Size(5, 1);
            this.pnlSplitterBottom.TabIndex = 0;
            // 
            // pnlSplitterTop
            // 
            this.pnlSplitterTop.BackColor = System.Drawing.SystemColors.ButtonShadow;
            this.pnlSplitterTop.Dock = System.Windows.Forms.DockStyle.Top;
            this.pnlSplitterTop.Location = new System.Drawing.Point(0, 0);
            this.pnlSplitterTop.Name = "pnlSplitterTop";
            this.pnlSplitterTop.Size = new System.Drawing.Size(5, 0);
            this.pnlSplitterTop.TabIndex = 1;
            // 
            // ImageQueue
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.ButtonShadow;
            this.Controls.Add(this.pnlBorder);
            this.Name = "ImageQueue";
            this.Padding = new System.Windows.Forms.Padding(0, 1, 1, 1);
            this.Size = new System.Drawing.Size(136, 331);
            this.pnlBorder.ResumeLayout(false);
            this.pnlLower.ResumeLayout(false);
            this.pnlUpper.ResumeLayout(false);
            this.pnlUpper.PerformLayout();
            this.splitter.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Panel pnlBorder;
        private System.Windows.Forms.Panel pnlUpper;
        private System.Windows.Forms.Button btnDelete;
        private System.Windows.Forms.Button btnDeleteAll;
        private System.Windows.Forms.CheckBox chkLockInput;
        private System.Windows.Forms.Panel pnlLower;
        private CVIPGUI.ImageQueueListView lvViewers;
        private System.Windows.Forms.ColumnHeader colImageName;
        private ImageQueueSplitter splitter;
        private System.Windows.Forms.Panel pnlSplitterBottom;
        private System.Windows.Forms.Panel pnlSplitterTop;
    }
}
