namespace CVIP_ATAT
{
    partial class AboutCVIPATAT
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(AboutCVIPATAT));
            this.AboutCVIPATATExit = new System.Windows.Forms.Button();
            this.title = new System.Windows.Forms.Label();
            this.copyright = new System.Windows.Forms.Label();
            this.version = new System.Windows.Forms.Label();
            this.author = new System.Windows.Forms.Label();
            this.linktoUmbaugh = new System.Windows.Forms.LinkLabel();
            this.permission = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // AboutCVIPATATExit
            // 
            this.AboutCVIPATATExit.Location = new System.Drawing.Point(342, 316);
            this.AboutCVIPATATExit.Name = "AboutCVIPATATExit";
            this.AboutCVIPATATExit.Size = new System.Drawing.Size(83, 28);
            this.AboutCVIPATATExit.TabIndex = 0;
            this.AboutCVIPATATExit.Text = "OK";
            this.AboutCVIPATATExit.UseVisualStyleBackColor = true;
            this.AboutCVIPATATExit.Click += new System.EventHandler(this.AboutCVIPATATExit_Click);
            // 
            // title
            // 
            this.title.AutoSize = true;
            this.title.Font = new System.Drawing.Font("Microsoft Sans Serif", 18F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.title.Location = new System.Drawing.Point(82, 25);
            this.title.Name = "title";
            this.title.Size = new System.Drawing.Size(585, 29);
            this.title.TabIndex = 1;
            this.title.Text = "Automatic CVIP Algorithm Test And Analysis Tool";
            // 
            // copyright
            // 
            this.copyright.AutoSize = true;
            this.copyright.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.copyright.Location = new System.Drawing.Point(125, 246);
            this.copyright.Name = "copyright";
            this.copyright.Size = new System.Drawing.Size(503, 13);
            this.copyright.TabIndex = 2;
            this.copyright.Text = "     Copyright© 2010-2023 Scott E Umbaugh @ Southern Illinois University Edwardsv" +
    "ille";
            // 
            // version
            // 
            this.version.AutoSize = true;
            this.version.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.version.Location = new System.Drawing.Point(339, 76);
            this.version.Name = "version";
            this.version.Size = new System.Drawing.Size(79, 13);
            this.version.TabIndex = 2;
            this.version.Text = "Version: 5.9h";
            // 
            // author
            // 
            this.author.AutoSize = true;
            this.author.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.author.Location = new System.Drawing.Point(179, 98);
            this.author.Name = "author";
            this.author.Size = new System.Drawing.Size(453, 39);
            this.author.TabIndex = 0;
            this.author.Text = resources.GetString("author.Text");
            // 
            // linktoUmbaugh
            // 
            this.linktoUmbaugh.AutoSize = true;
            this.linktoUmbaugh.Location = new System.Drawing.Point(340, 281);
            this.linktoUmbaugh.Name = "linktoUmbaugh";
            this.linktoUmbaugh.Size = new System.Drawing.Size(95, 13);
            this.linktoUmbaugh.TabIndex = 3;
            this.linktoUmbaugh.TabStop = true;
            this.linktoUmbaugh.Text = "CVIPtools Website";
            this.linktoUmbaugh.LinkClicked += new System.Windows.Forms.LinkLabelLinkClickedEventHandler(this.linkLabel1_LinkClicked);
            // 
            // permission
            // 
            this.permission.Location = new System.Drawing.Point(145, 146);
            this.permission.Name = "permission";
            this.permission.Size = new System.Drawing.Size(477, 78);
            this.permission.TabIndex = 4;
            this.permission.Text = resources.GetString("permission.Text");
            // 
            // AboutCVIPATAT
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(767, 381);
            this.Controls.Add(this.permission);
            this.Controls.Add(this.linktoUmbaugh);
            this.Controls.Add(this.author);
            this.Controls.Add(this.version);
            this.Controls.Add(this.copyright);
            this.Controls.Add(this.title);
            this.Controls.Add(this.AboutCVIPATATExit);
            this.Name = "AboutCVIPATAT";
            this.Text = "About CVIPATAT";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button AboutCVIPATATExit;
        private System.Windows.Forms.Label title;
        private System.Windows.Forms.Label copyright;
        private System.Windows.Forms.Label version;
        private System.Windows.Forms.Label author;
        private System.Windows.Forms.LinkLabel linktoUmbaugh;
        private System.Windows.Forms.Label permission;
    }
}