namespace CVIP_ATAT
{
    partial class NewProject
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
            this.gbNewProject = new System.Windows.Forms.GroupBox();
            this.labelPPath = new System.Windows.Forms.Label();
            this.btBrowse = new System.Windows.Forms.Button();
            this.tbLocation = new System.Windows.Forms.TextBox();
            this.tbPName = new System.Windows.Forms.TextBox();
            this.labelLocation = new System.Windows.Forms.Label();
            this.labelPName = new System.Windows.Forms.Label();
            this.folderBrowserDialog1 = new System.Windows.Forms.FolderBrowserDialog();
            this.btOk = new System.Windows.Forms.Button();
            this.btCancel = new System.Windows.Forms.Button();
            this.gbNewProject.SuspendLayout();
            this.SuspendLayout();
            // 
            // gbNewProject
            // 
            this.gbNewProject.Controls.Add(this.labelPPath);
            this.gbNewProject.Controls.Add(this.btBrowse);
            this.gbNewProject.Controls.Add(this.tbLocation);
            this.gbNewProject.Controls.Add(this.tbPName);
            this.gbNewProject.Controls.Add(this.labelLocation);
            this.gbNewProject.Controls.Add(this.labelPName);
            this.gbNewProject.Location = new System.Drawing.Point(23, 27);
            this.gbNewProject.Name = "gbNewProject";
            this.gbNewProject.Size = new System.Drawing.Size(505, 153);
            this.gbNewProject.TabIndex = 0;
            this.gbNewProject.TabStop = false;
            this.gbNewProject.Text = "Create a New Project";
            // 
            // labelPPath
            // 
            this.labelPPath.AutoSize = true;
            this.labelPPath.Location = new System.Drawing.Point(28, 116);
            this.labelPPath.Name = "labelPPath";
            this.labelPPath.Size = new System.Drawing.Size(223, 13);
            this.labelPPath.TabIndex = 3;
            this.labelPPath.Text = "Project will be created at location: C:\\Project1";
            // 
            // btBrowse
            // 
            this.btBrowse.Location = new System.Drawing.Point(394, 76);
            this.btBrowse.Name = "btBrowse";
            this.btBrowse.Size = new System.Drawing.Size(78, 27);
            this.btBrowse.TabIndex = 2;
            this.btBrowse.Text = "Browse";
            this.btBrowse.UseVisualStyleBackColor = true;
            this.btBrowse.Click += new System.EventHandler(this.btBrowse_Click);
            // 
            // tbLocation
            // 
            this.tbLocation.Location = new System.Drawing.Point(107, 75);
            this.tbLocation.Name = "tbLocation";
            this.tbLocation.Size = new System.Drawing.Size(269, 20);
            this.tbLocation.TabIndex = 1;
            this.tbLocation.Text = "C:\\";
            // 
            // tbPName
            // 
            this.tbPName.Location = new System.Drawing.Point(107, 38);
            this.tbPName.Name = "tbPName";
            this.tbPName.Size = new System.Drawing.Size(364, 20);
            this.tbPName.TabIndex = 1;
            this.tbPName.Text = "Project1";
            this.tbPName.KeyUp += new System.Windows.Forms.KeyEventHandler(this.tbPName_KeyUp);
            // 
            // labelLocation
            // 
            this.labelLocation.AutoSize = true;
            this.labelLocation.Location = new System.Drawing.Point(21, 78);
            this.labelLocation.Name = "labelLocation";
            this.labelLocation.Size = new System.Drawing.Size(51, 13);
            this.labelLocation.TabIndex = 0;
            this.labelLocation.Text = "Location:";
            // 
            // labelPName
            // 
            this.labelPName.AutoSize = true;
            this.labelPName.Location = new System.Drawing.Point(21, 37);
            this.labelPName.Name = "labelPName";
            this.labelPName.Size = new System.Drawing.Size(74, 13);
            this.labelPName.TabIndex = 0;
            this.labelPName.Text = "Project Name:";
            // 
            // btOk
            // 
            this.btOk.Location = new System.Drawing.Point(339, 196);
            this.btOk.Name = "btOk";
            this.btOk.Size = new System.Drawing.Size(78, 27);
            this.btOk.TabIndex = 1;
            this.btOk.Text = "OK";
            this.btOk.UseVisualStyleBackColor = true;
            this.btOk.Click += new System.EventHandler(this.btOk_Click);
            // 
            // btCancel
            // 
            this.btCancel.Location = new System.Drawing.Point(450, 196);
            this.btCancel.Name = "btCancel";
            this.btCancel.Size = new System.Drawing.Size(78, 27);
            this.btCancel.TabIndex = 1;
            this.btCancel.Text = "Cancel";
            this.btCancel.UseVisualStyleBackColor = true;
            this.btCancel.Click += new System.EventHandler(this.btCancel_Click);
            // 
            // NewProject
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(550, 238);
            this.Controls.Add(this.btCancel);
            this.Controls.Add(this.btOk);
            this.Controls.Add(this.gbNewProject);
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "NewProject";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "New Project";
            this.Load += new System.EventHandler(this.NewProject_Load);
            this.gbNewProject.ResumeLayout(false);
            this.gbNewProject.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox gbNewProject;
        private System.Windows.Forms.TextBox tbLocation;
        private System.Windows.Forms.TextBox tbPName;
        private System.Windows.Forms.Label labelLocation;
        private System.Windows.Forms.Label labelPName;
        private System.Windows.Forms.Label labelPPath;
        private System.Windows.Forms.Button btBrowse;
        private System.Windows.Forms.FolderBrowserDialog folderBrowserDialog1;
        private System.Windows.Forms.Button btOk;
        private System.Windows.Forms.Button btCancel;
    }
}