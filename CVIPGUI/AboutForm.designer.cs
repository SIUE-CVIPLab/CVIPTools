namespace CVIPGUI
{
    partial class AboutForm
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(AboutForm));
            this.pnlAboutCvip = new System.Windows.Forms.Panel();
            this.lblPermission = new System.Windows.Forms.Label();
            this.lnkCvipWebSite = new System.Windows.Forms.LinkLabel();
            this.lblVersion = new System.Windows.Forms.Label();
            this.lblCopyright = new System.Windows.Forms.Label();
            this.lblTitle = new System.Windows.Forms.Label();
            this.txtAboutCvip = new System.Windows.Forms.RichTextBox();
            this.chkAboutCvip = new System.Windows.Forms.CheckBox();
            this.btnOK = new System.Windows.Forms.Button();
            this.pnlAboutCvip.SuspendLayout();
            this.SuspendLayout();
            // 
            // pnlAboutCvip
            // 
            this.pnlAboutCvip.Controls.Add(this.lblPermission);
            this.pnlAboutCvip.Controls.Add(this.lnkCvipWebSite);
            this.pnlAboutCvip.Controls.Add(this.lblVersion);
            this.pnlAboutCvip.Controls.Add(this.lblCopyright);
            this.pnlAboutCvip.Controls.Add(this.lblTitle);
            this.pnlAboutCvip.Location = new System.Drawing.Point(0, 0);
            this.pnlAboutCvip.Name = "pnlAboutCvip";
            this.pnlAboutCvip.Size = new System.Drawing.Size(473, 216);
            this.pnlAboutCvip.TabIndex = 0;
            // 
            // lblPermission
            // 
            this.lblPermission.Font = new System.Drawing.Font("Arial", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lblPermission.Location = new System.Drawing.Point(8, 155);
            this.lblPermission.Name = "lblPermission";
            this.lblPermission.Size = new System.Drawing.Size(461, 60);
            this.lblPermission.TabIndex = 4;
            this.lblPermission.Text = resources.GetString("lblPermission.Text");
            // 
            // lnkCvipWebSite
            // 
            this.lnkCvipWebSite.AutoSize = true;
            this.lnkCvipWebSite.Font = new System.Drawing.Font("Arial", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lnkCvipWebSite.Location = new System.Drawing.Point(168, 111);
            this.lnkCvipWebSite.Name = "lnkCvipWebSite";
            this.lnkCvipWebSite.Size = new System.Drawing.Size(109, 15);
            this.lnkCvipWebSite.TabIndex = 3;
            this.lnkCvipWebSite.TabStop = true;
            this.lnkCvipWebSite.Text = "CVIPtools Website";
            this.lnkCvipWebSite.LinkClicked += new System.Windows.Forms.LinkLabelLinkClickedEventHandler(this.lnkCvipWebSite_LinkClicked);
            // 
            // lblVersion
            // 
            this.lblVersion.Font = new System.Drawing.Font("Arial", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lblVersion.Location = new System.Drawing.Point(185, 75);
            this.lblVersion.Name = "lblVersion";
            this.lblVersion.Size = new System.Drawing.Size(100, 15);
            this.lblVersion.TabIndex = 2;
            this.lblVersion.Text = "Version: 5.9i";
            // 
            // lblCopyright
            // 
            this.lblCopyright.AutoSize = true;
            this.lblCopyright.Font = new System.Drawing.Font("Arial", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lblCopyright.Location = new System.Drawing.Point(3, 50);
            this.lblCopyright.Name = "lblCopyright";
            this.lblCopyright.Size = new System.Drawing.Size(469, 15);
            this.lblCopyright.TabIndex = 1;
            this.lblCopyright.Text = "Copyright © 1993-2025 Scott E Umbaugh @ Southern Illinois University Edwardsville" +
    "";
            // 
            // lblTitle
            // 
            this.lblTitle.AutoSize = true;
            this.lblTitle.Font = new System.Drawing.Font("Arial", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lblTitle.Location = new System.Drawing.Point(133, 23);
            this.lblTitle.Name = "lblTitle";
            this.lblTitle.Size = new System.Drawing.Size(185, 19);
            this.lblTitle.TabIndex = 0;
            this.lblTitle.Text = "CVIPtools for Windows";
            // 
            // txtAboutCvip
            // 
            this.txtAboutCvip.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.txtAboutCvip.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.txtAboutCvip.Location = new System.Drawing.Point(0, 0);
            this.txtAboutCvip.Name = "txtAboutCvip";
            this.txtAboutCvip.Size = new System.Drawing.Size(473, 216);
            this.txtAboutCvip.TabIndex = 1;
            this.txtAboutCvip.Text = resources.GetString("txtAboutCvip.Text");
            this.txtAboutCvip.Visible = false;
            // 
            // chkAboutCvip
            // 
            this.chkAboutCvip.Appearance = System.Windows.Forms.Appearance.Button;
            this.chkAboutCvip.Location = new System.Drawing.Point(63, 222);
            this.chkAboutCvip.Name = "chkAboutCvip";
            this.chkAboutCvip.Size = new System.Drawing.Size(110, 28);
            this.chkAboutCvip.TabIndex = 2;
            this.chkAboutCvip.Text = "About CVIPtools";
            this.chkAboutCvip.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            this.chkAboutCvip.UseVisualStyleBackColor = true;
            this.chkAboutCvip.Click += new System.EventHandler(this.chkAboutCvip_Click);
            // 
            // btnOK
            // 
            this.btnOK.DialogResult = System.Windows.Forms.DialogResult.OK;
            this.btnOK.Location = new System.Drawing.Point(303, 222);
            this.btnOK.Name = "btnOK";
            this.btnOK.Size = new System.Drawing.Size(110, 28);
            this.btnOK.TabIndex = 3;
            this.btnOK.Text = "OK";
            this.btnOK.UseVisualStyleBackColor = true;
            this.btnOK.Click += new System.EventHandler(this.btnOK_Click);
            // 
            // AboutForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(480, 259);
            this.Controls.Add(this.btnOK);
            this.Controls.Add(this.chkAboutCvip);
            this.Controls.Add(this.pnlAboutCvip);
            this.Controls.Add(this.txtAboutCvip);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "AboutForm";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "About CVIPtools";
            this.pnlAboutCvip.ResumeLayout(false);
            this.pnlAboutCvip.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Panel pnlAboutCvip;
        private System.Windows.Forms.Label lblPermission;
        private System.Windows.Forms.LinkLabel lnkCvipWebSite;
        private System.Windows.Forms.Label lblVersion;
        private System.Windows.Forms.Label lblCopyright;
        private System.Windows.Forms.Label lblTitle;
        private System.Windows.Forms.RichTextBox txtAboutCvip;
        private System.Windows.Forms.CheckBox chkAboutCvip;
        private System.Windows.Forms.Button btnOK;
    }
}