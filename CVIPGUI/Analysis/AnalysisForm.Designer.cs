namespace CVIPGUI
{
    partial class AnalysisForm
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(AnalysisForm));
            this.tabAnalysis = new System.Windows.Forms.TabControl();
            this.tabPreprocessing = new System.Windows.Forms.TabPage();
            this.pagePreprocessing = new CVIPGUI.Analysis.Preprocessing();
            this.tabGeometry = new System.Windows.Forms.TabPage();
            this.pageGeometry = new CVIPGUI.Analysis.Geometry();
            this.tabEdgeDetect = new System.Windows.Forms.TabPage();
            this.pageEdgeDetect = new CVIPGUI.Analysis.EdgeDetection();
            this.tabSegmentation = new System.Windows.Forms.TabPage();
            this.pageSegmentation = new CVIPGUI.Analysis.Segmentation();
            this.tabTransforms = new System.Windows.Forms.TabPage();
            this.pageTransforms = new CVIPGUI.Analysis.Transforms();
            this.tabFeatures = new System.Windows.Forms.TabPage();
            this.pageFeatures = new CVIPGUI.Analysis.Features();
            this.tabClassification = new System.Windows.Forms.TabPage();
            this.pageClassification = new CVIPGUI.Analysis.Classification();
            this.tabAnalysis.SuspendLayout();
            this.tabPreprocessing.SuspendLayout();
            this.tabGeometry.SuspendLayout();
            this.tabEdgeDetect.SuspendLayout();
            this.tabSegmentation.SuspendLayout();
            this.tabTransforms.SuspendLayout();
            this.tabFeatures.SuspendLayout();
            this.tabClassification.SuspendLayout();
            this.SuspendLayout();
            // 
            // tabAnalysis
            // 
            this.tabAnalysis.Controls.Add(this.tabPreprocessing);
            this.tabAnalysis.Controls.Add(this.tabGeometry);
            this.tabAnalysis.Controls.Add(this.tabEdgeDetect);
            this.tabAnalysis.Controls.Add(this.tabSegmentation);
            this.tabAnalysis.Controls.Add(this.tabTransforms);
            this.tabAnalysis.Controls.Add(this.tabFeatures);
            this.tabAnalysis.Controls.Add(this.tabClassification);
            this.tabAnalysis.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tabAnalysis.Location = new System.Drawing.Point(0, 0);
            this.tabAnalysis.Name = "tabAnalysis";
            this.tabAnalysis.SelectedIndex = 0;
            this.tabAnalysis.Size = new System.Drawing.Size(693, 567);
            this.tabAnalysis.TabIndex = 0;
            // 
            // tabPreprocessing
            // 
            this.tabPreprocessing.Controls.Add(this.pagePreprocessing);
            this.tabPreprocessing.Location = new System.Drawing.Point(4, 22);
            this.tabPreprocessing.Name = "tabPreprocessing";
            this.tabPreprocessing.Size = new System.Drawing.Size(685, 541);
            this.tabPreprocessing.TabIndex = 0;
            this.tabPreprocessing.Text = "Preprocessing";
            this.tabPreprocessing.UseVisualStyleBackColor = true;
            // 
            // pagePreprocessing
            // 
            this.pagePreprocessing.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.pagePreprocessing.CausesValidation = false;
            this.pagePreprocessing.Cursor = System.Windows.Forms.Cursors.Default;
            this.pagePreprocessing.Dock = System.Windows.Forms.DockStyle.Fill;
            this.pagePreprocessing.Location = new System.Drawing.Point(0, 0);
            this.pagePreprocessing.Name = "pagePreprocessing";
            this.pagePreprocessing.Size = new System.Drawing.Size(685, 541);
            this.pagePreprocessing.TabIndex = 0;
            // 
            // tabGeometry
            // 
            this.tabGeometry.Controls.Add(this.pageGeometry);
            this.tabGeometry.Location = new System.Drawing.Point(4, 22);
            this.tabGeometry.Name = "tabGeometry";
            this.tabGeometry.Size = new System.Drawing.Size(685, 541);
            this.tabGeometry.TabIndex = 1;
            this.tabGeometry.Text = "Geometry";
            this.tabGeometry.UseVisualStyleBackColor = true;
            // 
            // pageGeometry
            // 
            this.pageGeometry.CausesValidation = false;
            this.pageGeometry.Cursor = System.Windows.Forms.Cursors.Default;
            this.pageGeometry.Dock = System.Windows.Forms.DockStyle.Fill;
            this.pageGeometry.Location = new System.Drawing.Point(0, 0);
            this.pageGeometry.Name = "pageGeometry";
            this.pageGeometry.Size = new System.Drawing.Size(685, 541);
            this.pageGeometry.TabIndex = 0;
            this.pageGeometry.Load += new System.EventHandler(this.pageGeometry_Load);
            // 
            // tabEdgeDetect
            // 
            this.tabEdgeDetect.Controls.Add(this.pageEdgeDetect);
            this.tabEdgeDetect.Location = new System.Drawing.Point(4, 22);
            this.tabEdgeDetect.Name = "tabEdgeDetect";
            this.tabEdgeDetect.Size = new System.Drawing.Size(685, 541);
            this.tabEdgeDetect.TabIndex = 2;
            this.tabEdgeDetect.Text = "Edge/Line Detection";
            this.tabEdgeDetect.UseVisualStyleBackColor = true;
            // 
            // pageEdgeDetect
            // 
            this.pageEdgeDetect.CausesValidation = false;
            this.pageEdgeDetect.Cursor = System.Windows.Forms.Cursors.Default;
            this.pageEdgeDetect.Dock = System.Windows.Forms.DockStyle.Fill;
            this.pageEdgeDetect.Location = new System.Drawing.Point(0, 0);
            this.pageEdgeDetect.Name = "pageEdgeDetect";
            this.pageEdgeDetect.Size = new System.Drawing.Size(192, 74);
            this.pageEdgeDetect.TabIndex = 0;
            // 
            // tabSegmentation
            // 
            this.tabSegmentation.Controls.Add(this.pageSegmentation);
            this.tabSegmentation.Location = new System.Drawing.Point(4, 22);
            this.tabSegmentation.Name = "tabSegmentation";
            this.tabSegmentation.Size = new System.Drawing.Size(685, 541);
            this.tabSegmentation.TabIndex = 3;
            this.tabSegmentation.Text = "Segmentation";
            this.tabSegmentation.UseVisualStyleBackColor = true;
            // 
            // pageSegmentation
            // 
            this.pageSegmentation.CausesValidation = false;
            this.pageSegmentation.Cursor = System.Windows.Forms.Cursors.Default;
            this.pageSegmentation.Dock = System.Windows.Forms.DockStyle.Fill;
            this.pageSegmentation.Location = new System.Drawing.Point(0, 0);
            this.pageSegmentation.Name = "pageSegmentation";
            this.pageSegmentation.Size = new System.Drawing.Size(685, 541);
            this.pageSegmentation.TabIndex = 0;
            // 
            // tabTransforms
            // 
            this.tabTransforms.Controls.Add(this.pageTransforms);
            this.tabTransforms.Location = new System.Drawing.Point(4, 22);
            this.tabTransforms.Name = "tabTransforms";
            this.tabTransforms.Size = new System.Drawing.Size(685, 541);
            this.tabTransforms.TabIndex = 4;
            this.tabTransforms.Text = "Transforms";
            this.tabTransforms.UseVisualStyleBackColor = true;
            // 
            // pageTransforms
            // 
            this.pageTransforms.CausesValidation = false;
            this.pageTransforms.Cursor = System.Windows.Forms.Cursors.Default;
            this.pageTransforms.Dock = System.Windows.Forms.DockStyle.Fill;
            this.pageTransforms.Location = new System.Drawing.Point(0, 0);
            this.pageTransforms.Name = "pageTransforms";
            this.pageTransforms.Size = new System.Drawing.Size(685, 541);
            this.pageTransforms.TabIndex = 0;
            // 
            // tabFeatures
            // 
            this.tabFeatures.Controls.Add(this.pageFeatures);
            this.tabFeatures.Location = new System.Drawing.Point(4, 22);
            this.tabFeatures.Name = "tabFeatures";
            this.tabFeatures.Size = new System.Drawing.Size(685, 541);
            this.tabFeatures.TabIndex = 5;
            this.tabFeatures.Text = "Features";
            this.tabFeatures.UseVisualStyleBackColor = true;
            // 
            // pageFeatures
            // 
            this.pageFeatures.CausesValidation = false;
            this.pageFeatures.Cursor = System.Windows.Forms.Cursors.Default;
            this.pageFeatures.Dock = System.Windows.Forms.DockStyle.Top;
            this.pageFeatures.Location = new System.Drawing.Point(0, 0);
            this.pageFeatures.Name = "pageFeatures";
            this.pageFeatures.Size = new System.Drawing.Size(685, 600);
            this.pageFeatures.TabIndex = 0;
            this.pageFeatures.Load += new System.EventHandler(this.pageFeatures_Load);
            // 
            // tabClassification
            // 
            this.tabClassification.Controls.Add(this.pageClassification);
            this.tabClassification.Location = new System.Drawing.Point(4, 22);
            this.tabClassification.Name = "tabClassification";
            this.tabClassification.Size = new System.Drawing.Size(685, 541);
            this.tabClassification.TabIndex = 6;
            this.tabClassification.Text = "Pattern Classification";
            this.tabClassification.UseVisualStyleBackColor = true;
            // 
            // pageClassification
            // 
            this.pageClassification.CausesValidation = false;
            this.pageClassification.Cursor = System.Windows.Forms.Cursors.Default;
            this.pageClassification.Dock = System.Windows.Forms.DockStyle.Fill;
            this.pageClassification.Location = new System.Drawing.Point(0, 0);
            this.pageClassification.Name = "pageClassification";
            this.pageClassification.Size = new System.Drawing.Size(685, 541);
            this.pageClassification.TabIndex = 0;
            this.pageClassification.Load += new System.EventHandler(this.pageClassification_Load);
            // 
            // AnalysisForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.CausesValidation = false;
            this.ClientSize = new System.Drawing.Size(693, 567);
            this.Controls.Add(this.tabAnalysis);
            this.DoubleBuffered = true;
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "AnalysisForm";
            this.Text = "Analysis";
            this.Load += new System.EventHandler(this.AnalysisForm_Load);
            this.tabAnalysis.ResumeLayout(false);
            this.tabPreprocessing.ResumeLayout(false);
            this.tabGeometry.ResumeLayout(false);
            this.tabEdgeDetect.ResumeLayout(false);
            this.tabSegmentation.ResumeLayout(false);
            this.tabTransforms.ResumeLayout(false);
            this.tabFeatures.ResumeLayout(false);
            this.tabClassification.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        public System.Windows.Forms.TabControl tabAnalysis;
        private System.Windows.Forms.TabPage tabPreprocessing;
        private Analysis.Preprocessing pagePreprocessing;
        private System.Windows.Forms.TabPage tabGeometry;
        private Analysis.Geometry pageGeometry;
        private System.Windows.Forms.TabPage tabEdgeDetect;
        private Analysis.EdgeDetection pageEdgeDetect;
        private System.Windows.Forms.TabPage tabSegmentation;
        private Analysis.Segmentation pageSegmentation;
        private System.Windows.Forms.TabPage tabTransforms;
        private Analysis.Transforms pageTransforms;
        private System.Windows.Forms.TabPage tabFeatures;
        private System.Windows.Forms.TabPage tabClassification;
        private Analysis.Classification pageClassification;
        public Analysis.Features pageFeatures;
    }
}