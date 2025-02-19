namespace CVIPGUI
{
    partial class UtilitiesForm
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(UtilitiesForm));
            this.utilStats1 = new CVIPGUI.Utilities.UtilStats();
            this.utilSize1 = new CVIPGUI.Utilities.UtilSize();
            this.utilFilter1 = new CVIPGUI.Utilities.UtilFilter();
            this.utilEnhance1 = new CVIPGUI.Utilities.UtilEnhance();
            this.utilCreate1 = new CVIPGUI.Utilities.UtilCreate();
            this.utilConvert1 = new CVIPGUI.Utilities.UtilConvert();
            this.utilCompare1 = new CVIPGUI.Utilities.UtilCompare();
            this.utilArithLogic1 = new CVIPGUI.Utilities.UtilArithLogic();
            this.SuspendLayout();
            // 
            // utilStats1
            // 
            this.utilStats1.Location = new System.Drawing.Point(442, 438);
            this.utilStats1.Margin = new System.Windows.Forms.Padding(4);
            this.utilStats1.Name = "utilStats1";
            this.utilStats1.Size = new System.Drawing.Size(436, 140);
            this.utilStats1.TabIndex = 7;
            // 
            // utilSize1
            // 
            this.utilSize1.CausesValidation = false;
            this.utilSize1.Location = new System.Drawing.Point(442, 295);
            this.utilSize1.Margin = new System.Windows.Forms.Padding(4);
            this.utilSize1.Name = "utilSize1";
            this.utilSize1.Size = new System.Drawing.Size(436, 140);
            this.utilSize1.TabIndex = 6;
            // 
            // utilFilter1
            // 
            this.utilFilter1.CausesValidation = false;
            this.utilFilter1.Location = new System.Drawing.Point(444, 151);
            this.utilFilter1.Margin = new System.Windows.Forms.Padding(4);
            this.utilFilter1.Name = "utilFilter1";
            this.utilFilter1.Size = new System.Drawing.Size(436, 140);
            this.utilFilter1.TabIndex = 5;
            this.utilFilter1.Load += new System.EventHandler(this.utilFilter1_Load);
            // 
            // utilEnhance1
            // 
            this.utilEnhance1.Location = new System.Drawing.Point(445, 0);
            this.utilEnhance1.Margin = new System.Windows.Forms.Padding(4);
            this.utilEnhance1.Name = "utilEnhance1";
            this.utilEnhance1.Size = new System.Drawing.Size(436, 140);
            this.utilEnhance1.TabIndex = 4;
            this.utilEnhance1.Load += new System.EventHandler(this.utilEnhance1_Load);
            // 
            // utilCreate1
            // 
            this.utilCreate1.CausesValidation = false;
            this.utilCreate1.Location = new System.Drawing.Point(3, 437);
            this.utilCreate1.Margin = new System.Windows.Forms.Padding(4);
            this.utilCreate1.Name = "utilCreate1";
            this.utilCreate1.Size = new System.Drawing.Size(436, 140);
            this.utilCreate1.TabIndex = 3;
            // 
            // utilConvert1
            // 
            this.utilConvert1.Location = new System.Drawing.Point(2, 295);
            this.utilConvert1.Margin = new System.Windows.Forms.Padding(4);
            this.utilConvert1.Name = "utilConvert1";
            this.utilConvert1.Size = new System.Drawing.Size(436, 140);
            this.utilConvert1.TabIndex = 2;
            this.utilConvert1.Load += new System.EventHandler(this.utilConvert1_Load);
            // 
            // utilCompare1
            // 
            this.utilCompare1.CausesValidation = false;
            this.utilCompare1.Location = new System.Drawing.Point(0, 149);
            this.utilCompare1.Margin = new System.Windows.Forms.Padding(4);
            this.utilCompare1.Name = "utilCompare1";
            this.utilCompare1.Size = new System.Drawing.Size(438, 140);
            this.utilCompare1.TabIndex = 1;
            // 
            // utilArithLogic1
            // 
            this.utilArithLogic1.CausesValidation = false;
            this.utilArithLogic1.Location = new System.Drawing.Point(0, 0);
            this.utilArithLogic1.Margin = new System.Windows.Forms.Padding(4);
            this.utilArithLogic1.Name = "utilArithLogic1";
            this.utilArithLogic1.Size = new System.Drawing.Size(439, 143);
            this.utilArithLogic1.TabIndex = 0;
            // 
            // UtilitiesForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.CausesValidation = false;
            this.ClientSize = new System.Drawing.Size(894, 628);
            this.Controls.Add(this.utilStats1);
            this.Controls.Add(this.utilSize1);
            this.Controls.Add(this.utilFilter1);
            this.Controls.Add(this.utilEnhance1);
            this.Controls.Add(this.utilCreate1);
            this.Controls.Add(this.utilConvert1);
            this.Controls.Add(this.utilCompare1);
            this.Controls.Add(this.utilArithLogic1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "UtilitiesForm";
            this.Text = "UtilitiesForm";
            this.Load += new System.EventHandler(this.UtilitiesForm_Load);
            this.ResumeLayout(false);

        }

        #endregion

        private CVIPGUI.Utilities.UtilArithLogic utilArithLogic1;
        private CVIPGUI.Utilities.UtilCompare utilCompare1;
        private CVIPGUI.Utilities.UtilConvert utilConvert1;
        private CVIPGUI.Utilities.UtilCreate utilCreate1;
        private CVIPGUI.Utilities.UtilEnhance utilEnhance1;
        private CVIPGUI.Utilities.UtilFilter utilFilter1;
        private CVIPGUI.Utilities.UtilSize utilSize1;
        private CVIPGUI.Utilities.UtilStats utilStats1;
    }
}