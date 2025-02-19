namespace CVIP_ATAT
{
    partial class imageView
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
            this.label1 = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(52, 80);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(70, 13);
            this.label1.TabIndex = 2;
            this.label1.Text = "Row; Column";
            this.label1.Visible = false;
            // 
            // imageView
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoScroll = true;
            this.ClientSize = new System.Drawing.Size(518, 422);
            this.Controls.Add(this.label1);
            this.Name = "imageView";
            this.Text = "Image View";
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.imageView_FormClosed);
            this.Load += new System.EventHandler(this.imageView_Load);
            this.Paint += new System.Windows.Forms.PaintEventHandler(this.imageView_Paint);
            this.MouseLeave += new System.EventHandler(this.imageView_MouseLeave);
            this.MouseMove += new System.Windows.Forms.MouseEventHandler(this.imageView_MouseMove);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;


    }
}