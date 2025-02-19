namespace CVIPGUI
{
    partial class ViewerForm
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
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(ViewerForm));
            this.popmnuMesh = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.popmnuShowMesh = new System.Windows.Forms.ToolStripMenuItem();
            this.popmnuCopyMesh = new System.Windows.Forms.ToolStripMenuItem();
            this.popmnuPasteMesh = new System.Windows.Forms.ToolStripMenuItem();
            this.popmnuMesh.SuspendLayout();
            this.SuspendLayout();
            // 
            // popmnuMesh
            // 
            this.popmnuMesh.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.popmnuShowMesh,
            this.popmnuCopyMesh,
            this.popmnuPasteMesh});
            this.popmnuMesh.Name = "popmnuMesh";
            this.popmnuMesh.Size = new System.Drawing.Size(168, 70);
            // 
            // popmnuShowMesh
            // 
            this.popmnuShowMesh.CheckOnClick = true;
            this.popmnuShowMesh.Name = "popmnuShowMesh";
            this.popmnuShowMesh.Size = new System.Drawing.Size(167, 22);
            this.popmnuShowMesh.Text = "Draw/Show Mesh";
            this.popmnuShowMesh.Click += new System.EventHandler(this.popmnuShowMesh_Click);
            // 
            // popmnuCopyMesh
            // 
            this.popmnuCopyMesh.Name = "popmnuCopyMesh";
            this.popmnuCopyMesh.Size = new System.Drawing.Size(167, 22);
            this.popmnuCopyMesh.Text = "Copy Mesh";
            this.popmnuCopyMesh.Click += new System.EventHandler(this.popmnuCopyMesh_Click);
            // 
            // popmnuPasteMesh
            // 
            this.popmnuPasteMesh.Name = "popmnuPasteMesh";
            this.popmnuPasteMesh.Size = new System.Drawing.Size(167, 22);
            this.popmnuPasteMesh.Text = "Paste Mesh";
            this.popmnuPasteMesh.Click += new System.EventHandler(this.popmnuPasteMesh_Click);
            // 
            // ViewerForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.ClientSize = new System.Drawing.Size(391, 352);
            this.ContextMenuStrip = this.popmnuMesh;
            this.DoubleBuffered = true;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            
            this.Name = "ViewerForm";
            this.Text = "ViewerForm";
            this.popmnuMesh.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.ContextMenuStrip popmnuMesh;
        private System.Windows.Forms.ToolStripMenuItem popmnuShowMesh;
        private System.Windows.Forms.ToolStripMenuItem popmnuCopyMesh;
        private System.Windows.Forms.ToolStripMenuItem popmnuPasteMesh;
    }
}