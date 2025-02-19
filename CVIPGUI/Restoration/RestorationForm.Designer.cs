namespace CVIPGUI
{
    partial class RestorationForm
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(RestorationForm));
            this.tabRestoration = new System.Windows.Forms.TabControl();
            this.tabNoise = new System.Windows.Forms.TabPage();
            this.pageNoise = new CVIPGUI.Restoration.Noise();
            this.tabSpatialFilter = new System.Windows.Forms.TabPage();
            this.pageSpatialFilter = new CVIPGUI.Restoration.SpatialFilter();
            this.tabFrequencyFilter = new System.Windows.Forms.TabPage();
            this.pageFreqFilter = new CVIPGUI.Restoration.FrequencyFilter();
            this.tabGeometricTransforms = new System.Windows.Forms.TabPage();
            this.pageGeometricTransforms = new CVIPGUI.Restoration.GeometricTransform();
            this.tabRestoration.SuspendLayout();
            this.tabNoise.SuspendLayout();
            this.tabSpatialFilter.SuspendLayout();
            this.tabFrequencyFilter.SuspendLayout();
            this.tabGeometricTransforms.SuspendLayout();
            this.SuspendLayout();
            // 
            // tabRestoration
            // 
            this.tabRestoration.Controls.Add(this.tabNoise);
            this.tabRestoration.Controls.Add(this.tabSpatialFilter);
            this.tabRestoration.Controls.Add(this.tabFrequencyFilter);
            this.tabRestoration.Controls.Add(this.tabGeometricTransforms);
            this.tabRestoration.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tabRestoration.Location = new System.Drawing.Point(0, 0);
            this.tabRestoration.Name = "tabRestoration";
            this.tabRestoration.SelectedIndex = 0;
            this.tabRestoration.Size = new System.Drawing.Size(605, 517);
            this.tabRestoration.TabIndex = 0;
            // 
            // tabNoise
            // 
            this.tabNoise.Controls.Add(this.pageNoise);
            this.tabNoise.Location = new System.Drawing.Point(4, 22);
            this.tabNoise.Name = "tabNoise";
            this.tabNoise.Size = new System.Drawing.Size(597, 491);
            this.tabNoise.TabIndex = 0;
            this.tabNoise.Text = "Noise";
            this.tabNoise.UseVisualStyleBackColor = true;
            // 
            // pageNoise
            // 
            this.pageNoise.CausesValidation = false;
            this.pageNoise.Cursor = System.Windows.Forms.Cursors.Default;
            this.pageNoise.Dock = System.Windows.Forms.DockStyle.Fill;
            this.pageNoise.Location = new System.Drawing.Point(0, 0);
            this.pageNoise.Name = "pageNoise";
            this.pageNoise.Size = new System.Drawing.Size(597, 491);
            this.pageNoise.TabIndex = 0;
            // 
            // tabSpatialFilter
            // 
            this.tabSpatialFilter.Controls.Add(this.pageSpatialFilter);
            this.tabSpatialFilter.Location = new System.Drawing.Point(4, 22);
            this.tabSpatialFilter.Name = "tabSpatialFilter";
            this.tabSpatialFilter.Size = new System.Drawing.Size(597, 491);
            this.tabSpatialFilter.TabIndex = 1;
            this.tabSpatialFilter.Text = "Spatial Filter";
            this.tabSpatialFilter.UseVisualStyleBackColor = true;
            // 
            // pageSpatialFilter
            // 
            this.pageSpatialFilter.CausesValidation = false;
            this.pageSpatialFilter.Cursor = System.Windows.Forms.Cursors.Default;
            this.pageSpatialFilter.Dock = System.Windows.Forms.DockStyle.Fill;
            this.pageSpatialFilter.Location = new System.Drawing.Point(0, 0);
            this.pageSpatialFilter.Name = "pageSpatialFilter";
            this.pageSpatialFilter.Size = new System.Drawing.Size(597, 491);
            this.pageSpatialFilter.TabIndex = 0;
            // 
            // tabFrequencyFilter
            // 
            this.tabFrequencyFilter.Controls.Add(this.pageFreqFilter);
            this.tabFrequencyFilter.Location = new System.Drawing.Point(4, 22);
            this.tabFrequencyFilter.Name = "tabFrequencyFilter";
            this.tabFrequencyFilter.Size = new System.Drawing.Size(597, 491);
            this.tabFrequencyFilter.TabIndex = 2;
            this.tabFrequencyFilter.Text = "Frequency Filter";
            this.tabFrequencyFilter.UseVisualStyleBackColor = true;
            // 
            // pageFreqFilter
            // 
            this.pageFreqFilter.CausesValidation = false;
            this.pageFreqFilter.Cursor = System.Windows.Forms.Cursors.Default;
            this.pageFreqFilter.Dock = System.Windows.Forms.DockStyle.Fill;
            this.pageFreqFilter.Location = new System.Drawing.Point(0, 0);
            this.pageFreqFilter.Name = "pageFreqFilter";
            this.pageFreqFilter.Size = new System.Drawing.Size(597, 491);
            this.pageFreqFilter.TabIndex = 0;
            // 
            // tabGeometricTransforms
            // 
            this.tabGeometricTransforms.Controls.Add(this.pageGeometricTransforms);
            this.tabGeometricTransforms.Location = new System.Drawing.Point(4, 22);
            this.tabGeometricTransforms.Name = "tabGeometricTransforms";
            this.tabGeometricTransforms.Size = new System.Drawing.Size(597, 491);
            this.tabGeometricTransforms.TabIndex = 3;
            this.tabGeometricTransforms.Text = "Geometric Transforms";
            this.tabGeometricTransforms.UseVisualStyleBackColor = true;
            // 
            // pageGeometricTransforms
            // 
            this.pageGeometricTransforms.CausesValidation = false;
            this.pageGeometricTransforms.Cursor = System.Windows.Forms.Cursors.Default;
            this.pageGeometricTransforms.Dock = System.Windows.Forms.DockStyle.Fill;
            this.pageGeometricTransforms.Location = new System.Drawing.Point(0, 0);
            this.pageGeometricTransforms.Name = "pageGeometricTransforms";
            this.pageGeometricTransforms.Size = new System.Drawing.Size(597, 491);
            this.pageGeometricTransforms.TabIndex = 0;
            // 
            // RestorationForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(605, 517);
            this.Controls.Add(this.tabRestoration);
            this.DoubleBuffered = true;
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "RestorationForm";
            this.Text = "Restoration";
            this.tabRestoration.ResumeLayout(false);
            this.tabNoise.ResumeLayout(false);
            this.tabSpatialFilter.ResumeLayout(false);
            this.tabFrequencyFilter.ResumeLayout(false);
            this.tabGeometricTransforms.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        public System.Windows.Forms.TabControl tabRestoration;
        private System.Windows.Forms.TabPage tabNoise;
        private Restoration.Noise pageNoise;
        private System.Windows.Forms.TabPage tabSpatialFilter;
        private Restoration.SpatialFilter pageSpatialFilter;
        private System.Windows.Forms.TabPage tabFrequencyFilter;
        private Restoration.FrequencyFilter pageFreqFilter;
        private System.Windows.Forms.TabPage tabGeometricTransforms;
        private Restoration.GeometricTransform pageGeometricTransforms;
    }
}