namespace CVIPGUI
{
    partial class CompressionForm
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(CompressionForm));
            this.tabCompression = new System.Windows.Forms.TabControl();
            this.tabPreprocessing = new System.Windows.Forms.TabPage();
            this.pagePreprocessing = new CVIPGUI.Compression.Preprocessing();
            this.tabLossless = new System.Windows.Forms.TabPage();
            this.pageLossless = new CVIPGUI.Compression.Lossless();
            this.tabLossy = new System.Windows.Forms.TabPage();
            this.pageLossy = new CVIPGUI.Compression.Lossy();
            this.tabPostprocessing = new System.Windows.Forms.TabPage();
            this.pagePostprocessing = new CVIPGUI.Compression.Postprocessing();
            this.tabCompression.SuspendLayout();
            this.tabPreprocessing.SuspendLayout();
            this.tabLossless.SuspendLayout();
            this.tabLossy.SuspendLayout();
            this.tabPostprocessing.SuspendLayout();
            this.SuspendLayout();
            // 
            // tabCompression
            // 
            this.tabCompression.Controls.Add(this.tabPreprocessing);
            this.tabCompression.Controls.Add(this.tabLossless);
            this.tabCompression.Controls.Add(this.tabLossy);
            this.tabCompression.Controls.Add(this.tabPostprocessing);
            this.tabCompression.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tabCompression.Location = new System.Drawing.Point(0, 0);
            this.tabCompression.Name = "tabCompression";
            this.tabCompression.SelectedIndex = 0;
            this.tabCompression.Size = new System.Drawing.Size(606, 380);
            this.tabCompression.TabIndex = 0;
            // 
            // tabPreprocessing
            // 
            this.tabPreprocessing.Controls.Add(this.pagePreprocessing);
            this.tabPreprocessing.Location = new System.Drawing.Point(4, 22);
            this.tabPreprocessing.Name = "tabPreprocessing";
            this.tabPreprocessing.Size = new System.Drawing.Size(598, 354);
            this.tabPreprocessing.TabIndex = 0;
            this.tabPreprocessing.Text = "Preprocessing";
            this.tabPreprocessing.UseVisualStyleBackColor = true;
            // 
            // pagePreprocessing
            // 
            this.pagePreprocessing.CausesValidation = false;
            this.pagePreprocessing.Cursor = System.Windows.Forms.Cursors.Default;
            this.pagePreprocessing.Dock = System.Windows.Forms.DockStyle.Fill;
            this.pagePreprocessing.Location = new System.Drawing.Point(0, 0);
            this.pagePreprocessing.Name = "pagePreprocessing";
            this.pagePreprocessing.Size = new System.Drawing.Size(598, 354);
            this.pagePreprocessing.TabIndex = 0;
            // 
            // tabLossless
            // 
            this.tabLossless.Controls.Add(this.pageLossless);
            this.tabLossless.Location = new System.Drawing.Point(4, 22);
            this.tabLossless.Name = "tabLossless";
            this.tabLossless.Size = new System.Drawing.Size(598, 354);
            this.tabLossless.TabIndex = 1;
            this.tabLossless.Text = "Lossless";
            this.tabLossless.UseVisualStyleBackColor = true;
            // 
            // pageLossless
            // 
            this.pageLossless.CausesValidation = false;
            this.pageLossless.Cursor = System.Windows.Forms.Cursors.Default;
            this.pageLossless.Dock = System.Windows.Forms.DockStyle.Fill;
            this.pageLossless.Location = new System.Drawing.Point(0, 0);
            this.pageLossless.Name = "pageLossless";
            this.pageLossless.Size = new System.Drawing.Size(598, 354);
            this.pageLossless.TabIndex = 0;
            // 
            // tabLossy
            // 
            this.tabLossy.Controls.Add(this.pageLossy);
            this.tabLossy.Location = new System.Drawing.Point(4, 22);
            this.tabLossy.Name = "tabLossy";
            this.tabLossy.Size = new System.Drawing.Size(598, 354);
            this.tabLossy.TabIndex = 2;
            this.tabLossy.Text = "Lossy";
            this.tabLossy.UseVisualStyleBackColor = true;
            // 
            // pageLossy
            // 
            this.pageLossy.CausesValidation = false;
            this.pageLossy.Cursor = System.Windows.Forms.Cursors.Default;
            this.pageLossy.Dock = System.Windows.Forms.DockStyle.Fill;
            this.pageLossy.Location = new System.Drawing.Point(0, 0);
            this.pageLossy.Name = "pageLossy";
            this.pageLossy.Size = new System.Drawing.Size(598, 354);
            this.pageLossy.TabIndex = 0;
            // 
            // tabPostprocessing
            // 
            this.tabPostprocessing.Controls.Add(this.pagePostprocessing);
            this.tabPostprocessing.Location = new System.Drawing.Point(4, 22);
            this.tabPostprocessing.Name = "tabPreprocessing";
            this.tabPostprocessing.Size = new System.Drawing.Size(598, 354);
            this.tabPostprocessing.TabIndex = 3;
            this.tabPostprocessing.Text = "Postprocessing";
            this.tabPostprocessing.UseVisualStyleBackColor = true;
            // 
            // pagePostprocessing
            // 
            this.pagePostprocessing.CausesValidation = false;
            this.pagePostprocessing.Cursor = System.Windows.Forms.Cursors.Default;
            this.pagePostprocessing.Dock = System.Windows.Forms.DockStyle.Fill;
            this.pagePostprocessing.Location = new System.Drawing.Point(0, 0);
            this.pagePostprocessing.Name = "pagePostprocessing";
            this.pagePostprocessing.Size = new System.Drawing.Size(598, 354);
            this.pagePostprocessing.TabIndex = 0;
            // 
            // CompressionForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(606, 380);
            this.Controls.Add(this.tabCompression);
            this.DoubleBuffered = true;
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "CompressionForm";
            this.Text = "Compression";
            this.tabCompression.ResumeLayout(false);
            this.tabPreprocessing.ResumeLayout(false);
            this.tabLossless.ResumeLayout(false);
            this.tabLossy.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        public System.Windows.Forms.TabControl tabCompression;
        private System.Windows.Forms.TabPage tabPreprocessing;
        private Compression.Preprocessing pagePreprocessing;
        private System.Windows.Forms.TabPage tabLossless;
        private Compression.Lossless pageLossless;
        private System.Windows.Forms.TabPage tabLossy;
        public Compression.Lossy pageLossy;
        private System.Windows.Forms.TabPage tabPostprocessing;
        private Compression.Postprocessing pagePostprocessing;
    }
}