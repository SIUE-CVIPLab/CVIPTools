namespace CVIPGUI
{
    partial class EnhancementForm
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(EnhancementForm));
            this.tabEnhancement = new System.Windows.Forms.TabControl();
            this.tabHistograms = new System.Windows.Forms.TabPage();
            this.pageHistograms = new CVIPGUI.Enhancement.Histograms();
            this.tabPseudocolor = new System.Windows.Forms.TabPage();
            this.pagePseudocolor = new CVIPGUI.Enhancement.Pseudocolor();
            this.tabSharpening = new System.Windows.Forms.TabPage();
            this.pageSharpening = new CVIPGUI.Enhancement.Sharpening();
            this.tabSmoothing = new System.Windows.Forms.TabPage();
            this.pageSmoothing = new CVIPGUI.Enhancement.Smoothing();
            this.tabEnhancement.SuspendLayout();
            this.tabHistograms.SuspendLayout();
            this.tabPseudocolor.SuspendLayout();
            this.tabSharpening.SuspendLayout();
            this.tabSmoothing.SuspendLayout();
            this.SuspendLayout();
            // 
            // tabEnhancement
            // 
            this.tabEnhancement.Controls.Add(this.tabHistograms);
            this.tabEnhancement.Controls.Add(this.tabPseudocolor);
            this.tabEnhancement.Controls.Add(this.tabSharpening);
            this.tabEnhancement.Controls.Add(this.tabSmoothing);
            this.tabEnhancement.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tabEnhancement.Location = new System.Drawing.Point(0, 0);
            this.tabEnhancement.Name = "tabEnhancement";
            this.tabEnhancement.SelectedIndex = 0;
            this.tabEnhancement.Size = new System.Drawing.Size(572, 329);
            this.tabEnhancement.TabIndex = 0;
            // 
            // tabHistograms
            // 
            this.tabHistograms.Controls.Add(this.pageHistograms);
            this.tabHistograms.Location = new System.Drawing.Point(4, 22);
            this.tabHistograms.Name = "tabHistograms";
            this.tabHistograms.Size = new System.Drawing.Size(564, 303);
            this.tabHistograms.TabIndex = 0;
            this.tabHistograms.Text = "Histogram/Contrast";
            this.tabHistograms.UseVisualStyleBackColor = true;
            // 
            // pageHistograms
            // 
            this.pageHistograms.CausesValidation = false;
            this.pageHistograms.Cursor = System.Windows.Forms.Cursors.Default;
            this.pageHistograms.Dock = System.Windows.Forms.DockStyle.Fill;
            this.pageHistograms.Location = new System.Drawing.Point(0, 0);
            this.pageHistograms.Name = "pageHistograms";
            this.pageHistograms.Size = new System.Drawing.Size(564, 303);
            this.pageHistograms.TabIndex = 0;
            this.pageHistograms.Load += new System.EventHandler(this.pageHistograms_Load);
            // 
            // tabPseudocolor
            // 
            this.tabPseudocolor.Controls.Add(this.pagePseudocolor);
            this.tabPseudocolor.Location = new System.Drawing.Point(4, 22);
            this.tabPseudocolor.Name = "tabPseudocolor";
            this.tabPseudocolor.Size = new System.Drawing.Size(564, 285);
            this.tabPseudocolor.TabIndex = 1;
            this.tabPseudocolor.Text = "Pseudocolor";
            this.tabPseudocolor.UseVisualStyleBackColor = true;
            // 
            // pagePseudocolor
            // 
            this.pagePseudocolor.CausesValidation = false;
            this.pagePseudocolor.Cursor = System.Windows.Forms.Cursors.Default;
            this.pagePseudocolor.Dock = System.Windows.Forms.DockStyle.Fill;
            this.pagePseudocolor.Location = new System.Drawing.Point(0, 0);
            this.pagePseudocolor.Name = "pagePseudocolor";
            this.pagePseudocolor.Size = new System.Drawing.Size(564, 285);
            this.pagePseudocolor.TabIndex = 0;
            // 
            // tabSharpening
            // 
            this.tabSharpening.Controls.Add(this.pageSharpening);
            this.tabSharpening.Location = new System.Drawing.Point(4, 22);
            this.tabSharpening.Name = "tabSharpening";
            this.tabSharpening.Size = new System.Drawing.Size(564, 285);
            this.tabSharpening.TabIndex = 2;
            this.tabSharpening.Text = "Sharpening";
            this.tabSharpening.UseVisualStyleBackColor = true;
            // 
            // pageSharpening
            // 
            this.pageSharpening.CausesValidation = false;
            this.pageSharpening.Cursor = System.Windows.Forms.Cursors.Default;
            this.pageSharpening.Dock = System.Windows.Forms.DockStyle.Fill;
            this.pageSharpening.Location = new System.Drawing.Point(0, 0);
            this.pageSharpening.Name = "pageSharpening";
            this.pageSharpening.Size = new System.Drawing.Size(564, 285);
            this.pageSharpening.TabIndex = 0;
            // 
            // tabSmoothing
            // 
            this.tabSmoothing.Controls.Add(this.pageSmoothing);
            this.tabSmoothing.Location = new System.Drawing.Point(4, 22);
            this.tabSmoothing.Name = "tabSmoothing";
            this.tabSmoothing.Size = new System.Drawing.Size(564, 285);
            this.tabSmoothing.TabIndex = 3;
            this.tabSmoothing.Text = "Smoothing";
            this.tabSmoothing.UseVisualStyleBackColor = true;
            // 
            // pageSmoothing
            // 
            this.pageSmoothing.CausesValidation = false;
            this.pageSmoothing.Cursor = System.Windows.Forms.Cursors.Default;
            this.pageSmoothing.Dock = System.Windows.Forms.DockStyle.Fill;
            this.pageSmoothing.Location = new System.Drawing.Point(0, 0);
            this.pageSmoothing.Name = "pageSmoothing";
            this.pageSmoothing.Size = new System.Drawing.Size(564, 285);
            this.pageSmoothing.TabIndex = 0;
            // 
            // EnhancementForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(572, 329);
            this.Controls.Add(this.tabEnhancement);
            this.DoubleBuffered = true;
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "EnhancementForm";
            this.Text = "Enhancement";
            this.tabEnhancement.ResumeLayout(false);
            this.tabHistograms.ResumeLayout(false);
            this.tabPseudocolor.ResumeLayout(false);
            this.tabSharpening.ResumeLayout(false);
            this.tabSmoothing.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        public System.Windows.Forms.TabControl tabEnhancement;
        private System.Windows.Forms.TabPage tabHistograms;
        private Enhancement.Histograms pageHistograms;
        private System.Windows.Forms.TabPage tabPseudocolor;
        private Enhancement.Pseudocolor pagePseudocolor;
        private System.Windows.Forms.TabPage tabSharpening;
        private Enhancement.Sharpening pageSharpening;
        private System.Windows.Forms.TabPage tabSmoothing;
        private Enhancement.Smoothing pageSmoothing;
    }
}