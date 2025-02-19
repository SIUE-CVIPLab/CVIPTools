/*''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' ======================================================================
' Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
' ======================================================================
'
'             File Name: Sharpening.cs
'           Description: Contains the controls and code
'                        for Enhancement->Sharpening tab
'         Related Files: CvipOp.cs
'                        CvipConstant.cs
'   Initial Coding Date: June 2007
'              Modified: October 2009
'       Delevoping tool: Visual Studio 2010-C#
'             Credit(s): Wenjun(Evan) Bian
'                        Patrick Solt
'                        Southern Illinois University Edwardsville
'
' Copyright (C) 2013 Scott Umbaugh and SIUE
'
' Permission to use, copy, modify, and distribute this software and its
' documentation for any non-commercial purpose and without fee is hereby
' granted, provided that the above copyright notice appear in all copies
' and that both that copyright notice and this permission notice appear
' in supporting documentation.  This software is provided "as is"
' without express or implied warranty.
'
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''*/

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace CVIPGUI.Enhancement
{
    public partial class Sharpening : UserControl
    {
        private string sharpeningSelected;

        public Sharpening()
        {
            InitializeComponent();
        }
        protected override void OnLoad(EventArgs e)
        {
            base.OnLoad(e);
            this.rbSharpingI.PerformClick();
        }
        public void rbSharpingI_Click(object sender, EventArgs e)
        {
            string[] items;
            sharpeningSelected = "SharpeningI";

            lbLaplacian.Visible = true;
            rbMaskI.Visible = true;
            rbMaskI.Checked = true;
            rbMaskII.Visible = true;

            lbSharpening1.Visible = true;
            lbSharpening1.Text = "Kernel Size of Sobel";
            cbSharpening1.Visible = true;
            items = new string[] { "3", "5", "7" };
            cbSharpening1.DataSource = items;
            cbSharpening1.Text = "3";

            lbSharpening2.Visible = true;
            lbSharpening2.Text = "Low Clip Percent";
            cbSharpening2.Visible = true;
            items = new string[] { "0.0", "0.005", "0.01", "0.015", "0.02" };
            cbSharpening2.DataSource = items;
            cbSharpening2.Text = "0.005";
            lblLowPercent.Text = "0.5%";
            lblLowPercent.Visible = true;
            lblLowPercent.Location = new System.Drawing.Point(266, 95);

            lbSharpening3.Visible = true;
            lbSharpening3.Text = "High Clip Percent";
            cbSharpening3.Visible = true;
            items = new string[] { "0.0", "0.005", "0.01", "0.015", "0.02" };
            cbSharpening3.DataSource = items;
            cbSharpening3.Text = "0.005";
            lblHighPercent.Text = "0.5%";
            lblHighPercent.Visible = true;
            lblHighPercent.Location = new System.Drawing.Point(266, 122);

            lbSharpening4.Visible = false;
            lbSharpening4.Text = "Kernel Size of Sobel";
            cbSharpening4.Visible = false;
            items = new string[] { "3", "5", "7" };
            cbSharpening4.DataSource = items;
            cbSharpening4.Text = "3";

            checkBoxSharpening1.Visible = true;
            checkBoxSharpening1.Checked = true;
            checkBoxSharpening1.Text = "Intermediate Image Remapping";

            checkBoxSharpening2.Visible = true;
            checkBoxSharpening2.Checked = true;
            checkBoxSharpening2.Text = "Add to Original Image";
        }
        private void rbSharpingII_Click(object sender, EventArgs e)
        {
            string[] items;
            sharpeningSelected = "SharpeningII";

            lbLaplacian.Visible = false;
            rbMaskI.Visible = false;
            rbMaskII.Visible = false;

            lblLowPercent.Visible = false;
            lblHighPercent.Visible = false;

            lbSharpening1.Visible = false;
            lbSharpening1.Text = "Kernel Size of Sobel";
            cbSharpening1.Visible = false;
            items = new string[] { "3", "5", "7" };
            cbSharpening1.DataSource = items;
            cbSharpening1.Text = "3";

            lbSharpening2.Visible = false;
            lbSharpening2.Text = "Low Clip Percent";
            cbSharpening2.Visible = false;
            items = new string[] { "0.0", "0.005", "0.01", "0.015", "0.02" };
            cbSharpening2.DataSource = items;
            cbSharpening2.Text = "0.005";

            lbSharpening3.Visible = false;
            lbSharpening3.Text = "High Clip Percent";
            cbSharpening3.Visible = false;
            items = new string[] { "0.0", "0.005", "0.01", "0.015", "0.02" };
            cbSharpening3.DataSource = items;
            cbSharpening3.Text = "0.005";

            lbSharpening4.Visible = false;
            lbSharpening4.Text = "Kernel Size of Sobel";
            cbSharpening4.Visible = false;
            items = new string[] { "3", "5", "7" };
            cbSharpening4.DataSource = items;
            cbSharpening4.Text = "3";

            checkBoxSharpening1.Visible = false;
            checkBoxSharpening1.Checked = false;
            checkBoxSharpening1.Text = "Intermediate Image Remapping";

            checkBoxSharpening2.Visible = true;
            checkBoxSharpening2.Checked = true;
            checkBoxSharpening2.Text = "Add to Original Image";
        }
        private void rbHighpassSpatial_Click(object sender, EventArgs e)
        {
            string[] items;
            sharpeningSelected = "HighpassSpatial";

            lbLaplacian.Visible = false;
            rbMaskI.Visible = false;
            rbMaskII.Visible = false;

            lblLowPercent.Visible = false;
            lblHighPercent.Visible = false;

            lbSharpening1.Visible = false;
            lbSharpening1.Text = "Kernel Size of Sobel";
            cbSharpening1.Visible = false;
            items = new string[] { "3", "5", "7" };
            cbSharpening1.DataSource = items;
            cbSharpening1.Text = "3";

            lbSharpening2.Visible = false;
            lbSharpening2.Text = "Low Clip Percent";
            cbSharpening2.Visible = false;
            items = new string[] { "0.0", "0.005", "0.01", "0.015", "0.02" };
            cbSharpening2.DataSource = items;
            cbSharpening2.Text = "0.005";

            lbSharpening3.Visible = false;
            lbSharpening3.Text = "High Clip Percent";
            cbSharpening3.Visible = false;
            items = new string[] { "0.0", "0.005", "0.01", "0.015", "0.02" };
            cbSharpening3.DataSource = items;
            cbSharpening3.Text = "0.005";

            lbSharpening4.Visible = false;
            lbSharpening4.Text = "Kernel Size of Sobel";
            cbSharpening4.Visible = false;
            items = new string[] { "3", "5", "7" };
            cbSharpening4.DataSource = items;
            cbSharpening4.Text = "3";

            checkBoxSharpening1.Visible = false;
            checkBoxSharpening1.Checked = false;
            checkBoxSharpening1.Text = "Intermediate Image Remapping";

            checkBoxSharpening2.Visible = true;
            checkBoxSharpening2.Checked = true;
            checkBoxSharpening2.Text = "Add to Original Image";
        }
        private void rbHighBoost_Click(object sender, EventArgs e)
        {
            string[] items;
            sharpeningSelected = "HighBoost";

            lbLaplacian.Visible = false;
            rbMaskI.Visible = false;
            rbMaskII.Visible = false;

            lblLowPercent.Visible = false;
            lblHighPercent.Visible = false;

            lbSharpening1.Visible = true;
            lbSharpening1.Text = "Mask Size";
            cbSharpening1.Visible = true;
            items = new string[] { "3", "5", "7", "9" ,"11","13"};
            cbSharpening1.DataSource = items;
            cbSharpening1.Text = "3";

            lbSharpening2.Visible = true;
            lbSharpening2.Text = "Center Value";
            cbSharpening2.Visible = true;
            items = new string[] { "5", "7", "8", "9", "25", "49", "81","121","169" };
            cbSharpening2.DataSource = items;
            cbSharpening2.Text = "9";

            lbSharpening3.Visible = false;
            lbSharpening3.Text = "High Clip Percent";
            cbSharpening3.Visible = false;
            items = new string[] { "0.0", "0.005", "0.01", "0.015", "0.02" };
            cbSharpening3.DataSource = items;
            cbSharpening3.Text = "0.005";

            lbSharpening4.Visible = false;
            lbSharpening4.Text = "Kernel Size of Sobel";
            cbSharpening4.Visible = false;
            items = new string[] { "3", "5", "7" };
            cbSharpening4.DataSource = items;
            cbSharpening4.Text = "3";

            checkBoxSharpening1.Visible = false;
            checkBoxSharpening1.Checked = false;
            checkBoxSharpening1.Text = "Intermediate Image Remapping";

            checkBoxSharpening2.Visible = true;
            checkBoxSharpening2.Checked = true;
            checkBoxSharpening2.Text = "Add to Original Image";
        }
        private void rbUnsharpMasking_Click(object sender, EventArgs e)
        {
            string[] items;
            sharpeningSelected = "UnsharpMasking";

            lbLaplacian.Visible = false;
            rbMaskI.Visible = false;
            rbMaskII.Visible = false;

            lbSharpening1.Visible = true;
            lbSharpening1.Text = "Low Limit";
            cbSharpening1.Visible = true;
            items = new string[] { "0", "10", "30", "50", "70", "80", "100" };
            cbSharpening1.DataSource = items;
            cbSharpening1.Text = "0";

            lbSharpening2.Visible = true;
            lbSharpening2.Text = "Upper Limit";
            cbSharpening2.Visible = true;
            items = new string[] { "100", "120", "150", "170", "200", "220", "255" };
            cbSharpening2.DataSource = items;
            cbSharpening2.Text = "100";

            lbSharpening3.Visible = true;
            lbSharpening3.Text = "Low Clip Percent";
            cbSharpening3.Visible = true;
            items = new string[] { "0.01", "0.02", "0.03", "0.04", "0.05", "0.075", "0.1", "0.15" };
            cbSharpening3.DataSource = items;
            cbSharpening3.Text = "0.01";
            lblLowPercent.Text = "1%";
            lblLowPercent.Visible = true;
            lblLowPercent.Location = new System.Drawing.Point(266, 122);

            lbSharpening4.Visible = true;
            lbSharpening4.Text = "High Clip Percent";
            cbSharpening4.Visible = true;
            items = new string[] { "0.01", "0.02", "0.03", "0.04", "0.05", "0.075", "0.1", "0.15" };
            cbSharpening4.DataSource = items;
            cbSharpening4.Text = "0.01";
            lblHighPercent.Text = "1%";
            lblHighPercent.Visible = true;
            lblHighPercent.Location = new System.Drawing.Point(266, 149);

            checkBoxSharpening1.Visible = false;
            checkBoxSharpening1.Checked = false;
            checkBoxSharpening1.Text = "Intermediate Image Remapping";

            checkBoxSharpening2.Visible = false;
            checkBoxSharpening2.Checked = false;
            checkBoxSharpening2.Text = "Add to Original Image";
        }
        private void rbFFTSharpening_Click(object sender, EventArgs e)
        {
            string[] items;
            sharpeningSelected = "FFTSharpening";

            lbLaplacian.Visible = false;
            rbMaskI.Visible = false;
            rbMaskII.Visible = false;

            lblLowPercent.Visible = false;
            lblHighPercent.Visible = false;

            lbSharpening1.Visible = true;
            lbSharpening1.Text = "Cutoff Frequency";
            cbSharpening1.Visible = true;
            items = new string[] { "16", "24", "32", "40", "48", "56", "64" };
            cbSharpening1.DataSource = items;
            cbSharpening1.Text = "64";

            lbSharpening2.Visible = true;
            lbSharpening2.Text = "Butterworth Order";
            cbSharpening2.Visible = true;
            items = new string[] { "1", "2", "3", "4", "5", "6", "7", "8" };
            cbSharpening2.DataSource = items;
            cbSharpening2.Text = "3";

            lbSharpening3.Visible = false;
            lbSharpening3.Text = "High Clip Percent";
            cbSharpening3.Visible = false;
            items = new string[] { "0.0", "0.005", "0.01", "0.015", "0.02" };
            cbSharpening3.DataSource = items;
            cbSharpening3.Text = "0.005";

            lbSharpening4.Visible = false;
            lbSharpening4.Text = "Kernel Size of Sobel";
            cbSharpening4.Visible = false;
            items = new string[] { "3", "5", "7" };
            cbSharpening4.DataSource = items;
            cbSharpening4.Text = "3";

            checkBoxSharpening1.Visible = false;
            checkBoxSharpening1.Checked = false;
            checkBoxSharpening1.Text = "Intermediate Image Remapping";

            checkBoxSharpening2.Visible = true;
            checkBoxSharpening2.Checked = true;
            checkBoxSharpening2.Text = "Add to Original Image";
        }
        private void rbDCTSharpening_Click(object sender, EventArgs e)
        {
            string[] items;
            sharpeningSelected = "DCTSharpening";

            lbLaplacian.Visible = false;
            rbMaskI.Visible = false;
            rbMaskII.Visible = false;

            lblLowPercent.Visible = false;
            lblHighPercent.Visible = false;

            lbSharpening1.Visible = true;
            lbSharpening1.Text = "Cutoff Frequency";
            cbSharpening1.Visible = true;
            items = new string[] { "16", "24", "32", "40", "48", "56", "64" };
            cbSharpening1.DataSource = items;
            cbSharpening1.Text = "64";

            lbSharpening2.Visible = true;
            lbSharpening2.Text = "Butterworth Order";
            cbSharpening2.Visible = true;
            items = new string[] { "1", "2", "3", "4", "5", "6", "7", "8" };
            cbSharpening2.DataSource = items;
            cbSharpening2.Text = "3";

            lbSharpening3.Visible = false;
            lbSharpening3.Text = "High Clip Percent";
            cbSharpening3.Visible = false;
            items = new string[] { "0.0", "0.005", "0.01", "0.015", "0.02" };
            cbSharpening3.DataSource = items;
            cbSharpening3.Text = "0.005";

            lbSharpening4.Visible = false;
            lbSharpening4.Text = "Kernel Size of Sobel";
            cbSharpening4.Visible = false;
            items = new string[] { "3", "5", "7" };
            cbSharpening4.DataSource = items;
            cbSharpening4.Text = "3";

            checkBoxSharpening1.Visible = false;
            checkBoxSharpening1.Checked = false;
            checkBoxSharpening1.Text = "Intermediate Image Remapping";

            checkBoxSharpening2.Visible = true;
            checkBoxSharpening2.Checked = true;
            checkBoxSharpening2.Text = "Add to Original Image";
        }
        private void rbHighFreqEmphasis_Click(object sender, EventArgs e)
        {
            string[] items;
            sharpeningSelected = "HighFreqEmphasis";

            lbLaplacian.Visible = false;
            rbMaskI.Visible = false;
            rbMaskII.Visible = false;

            lblLowPercent.Visible = false;
            lblHighPercent.Visible = false;

            if (rbHighFreqEmphasis.Checked)
            {
                cbSharpening1.DropDownStyle = ComboBoxStyle.DropDownList;
            }
            else
            {
                cbSharpening1.DropDownStyle = ComboBoxStyle.DropDown;
            }
            lbSharpening1.Visible = true;
            lbSharpening1.Text = "Transform";
            cbSharpening1.Visible = true;
            items = new string[] { "FFT", "DCT", "Haar", "Walsh", "Hadamard" };
            cbSharpening1.DataSource = items;
            cbSharpening1.Text = "FFT";

            lbSharpening2.Visible = true;
            lbSharpening2.Text = "Cutoff Frequency";
            cbSharpening2.Visible = true;
            items = new string[] { "16", "24", "32", "40", "48", "56", "64" };
            cbSharpening2.DataSource = items;
            cbSharpening2.Text = "32";

            lbSharpening3.Visible = true;
            lbSharpening3.Text = "Filter Order";
            cbSharpening3.Visible = true;
            items = new string[] { "1", "2", "3", "4", "5", "6", "7", "8" };
            cbSharpening3.DataSource = items;
            cbSharpening3.Text = "3";

            lbSharpening4.Visible = true;
            lbSharpening4.Text = "Emphasis Offset";
            cbSharpening4.Visible = true;
            items = new string[] { "0.5", "1.2", "1.3", "1.5", "1.7", "1.9", "2.0", "2.5" };
            cbSharpening4.DataSource = items;
            cbSharpening4.Text = "0.5";

            checkBoxSharpening1.Visible = false;
            checkBoxSharpening1.Checked = false;
            checkBoxSharpening1.Text = "Intermediate Image Remapping";

            checkBoxSharpening2.Visible = true;
            checkBoxSharpening2.Checked = false;
            checkBoxSharpening2.Text = "Keep DC";
        }
        private void rbHomomorphic_Click(object sender, EventArgs e)
        {
            string[] items;
            sharpeningSelected = "Homomorphic";

            lbLaplacian.Visible = false;
            rbMaskI.Visible = false;
            rbMaskII.Visible = false;

            lblLowPercent.Visible = false;
            lblHighPercent.Visible = false;

            lbSharpening1.Visible = true;
            lbSharpening1.Text = "Cutoff Frequency";
            cbSharpening1.Visible = true;
            items = new string[] { "0", "16", "24", "32", "40", "48", "56", "64", "80", "128" };
            cbSharpening1.DataSource = items;
            cbSharpening1.Text = "64";

            lbSharpening2.Visible = true;
            lbSharpening2.Text = "Lower Frequency Gain";
            cbSharpening2.Visible = true;
            items = new string[] { "0.2", "0.4", "0.6", "0.7", "0.8", "0.85", "0.9", "0.95" };
            cbSharpening2.DataSource = items;
            cbSharpening2.Text = "0.9";

            lbSharpening3.Visible = true;
            lbSharpening3.Text = "Higher Frequency Gain";
            cbSharpening3.Visible = true;
            items = new string[] { "1.1", "1.2", "1.3", "1.4", "1.5", "1.8", "2.0", "2.5" };
            cbSharpening3.DataSource = items;
            cbSharpening3.Text = "1.3";

            lbSharpening4.Visible = false;
            lbSharpening4.Text = "Emphasis Offset";
            cbSharpening4.Visible = false;
            items = new string[] { "0.5", "1.2", "1.3", "1.5", "1.7", "1.9", "2.0", "2.5" };
            cbSharpening4.DataSource = items;
            cbSharpening4.Text = "0.5";

            checkBoxSharpening1.Visible = false;
            checkBoxSharpening1.Checked = false;
            checkBoxSharpening1.Text = "Intermediate Image Remapping";

            checkBoxSharpening2.Visible = true;
            checkBoxSharpening2.Checked = true;
            checkBoxSharpening2.Text = "Add to Original Image";
        }
        private void cbSharpening1_Leave(object sender, EventArgs e)
        {
            try
            {
                if (rbHighFreqEmphasis.Checked)
                { }
                else
                {
                    Convert.ToDouble(cbSharpening1.Text);
                }
            }
            catch
            {
                if (rbSharpingI.Checked)
                    cbSharpening1.Text = "3";
                else if (rbHighBoost.Checked)
                    cbSharpening1.Text = "3";
                else if (rbUnsharpMasking.Checked)
                    cbSharpening1.Text = "0";
                else if (rbFFTSharpening.Checked)
                    cbSharpening1.Text = "64";
                else if (rbDCTSharpening.Checked)
                    cbSharpening1.Text = "64";
                else if (rbHighFreqEmphasis.Checked)
                    cbSharpening1.Text = "FFT";
                else if (rbHomomorphic.Checked)
                    cbSharpening1.Text = "64";
                else
                { }
                MessageBox.Show("Please check the input value. Only digit numbers are accepted.",
                   "Digit number input error", MessageBoxButtons.OK, MessageBoxIcon.Warning);
            }
        }
        private void cbSharpening2_Leave(object sender, EventArgs e)
        {
            try
            {
                Convert.ToDouble(cbSharpening2.Text);
            }
            catch
            {
                if (rbSharpingI.Checked)
                    cbSharpening2.Text = "0.005";
                else if (rbHighBoost.Checked)
                    cbSharpening2.Text = "9";
                else if (rbUnsharpMasking.Checked)
                    cbSharpening2.Text = "100";
                else if (rbFFTSharpening.Checked)
                    cbSharpening2.Text = "3";
                else if (rbDCTSharpening.Checked)
                    cbSharpening2.Text = "3";
                else if (rbHighFreqEmphasis.Checked)
                    cbSharpening2.Text = "32";
                else if (rbHomomorphic.Checked)
                    cbSharpening2.Text = "0.9";
                else
                { }

                MessageBox.Show("Please check the input value. Only digit numbers are accepted.",
                   "Digit number input error", MessageBoxButtons.OK, MessageBoxIcon.Warning);
            }
        }
        private void cbSharpening3_Leave(object sender, EventArgs e)
        {
            try
            {
                Convert.ToDouble(cbSharpening3.Text);
            }
            catch
            {
                if (rbSharpingI.Checked)
                    cbSharpening3.Text = "0.005";
                else if (rbUnsharpMasking.Checked)
                    cbSharpening3.Text = "0.01";
                else if (rbHighFreqEmphasis.Checked)
                    cbSharpening3.Text = "3";
                else if (rbHomomorphic.Checked)
                    cbSharpening3.Text = "1.3";
                else
                { }
                MessageBox.Show("Please check the input value. Only digit numbers are accepted.",
                   "Digit number input error", MessageBoxButtons.OK, MessageBoxIcon.Warning);
            }
        }
        private void cbSharpening4_Leave(object sender, EventArgs e)
        {
            try
            {
                Convert.ToDouble(cbSharpening4.Text);
            }
            catch
            {
                if (rbUnsharpMasking.Checked)
                    cbSharpening4.Text = "0.01";
                else if (rbHighFreqEmphasis.Checked)
                    cbSharpening4.Text = "0.5";
                else
                { }
                MessageBox.Show("Please check the input value. Only digit numbers are accepted.",
                   "Digit number input error", MessageBoxButtons.OK, MessageBoxIcon.Warning);
            }
        }
        private void btSharpeningHelp_Click(object sender, EventArgs e)
        {
            MainForm.ShowHelp();
        }
        private void btSharpeningCancel_Click(object sender, EventArgs e)
        {
            MainForm.EnhancementForm.Close();
        }
        private void btSharpeningReset_Click(object sender, EventArgs e)
        {
            if (this.rbSharpingI.Checked)
                this.rbSharpingI.PerformClick();
            else if (this.rbSharpingII.Checked)
                this.rbSharpingII.PerformClick();
            else if (this.rbSharpIII.Checked)
                this.rbSharpIII.PerformClick();
            else if (this.rbHighpassSpatial.Checked)
                this.rbHighpassSpatial.PerformClick();
            else if (this.rbHighBoost.Checked)
                this.rbHighBoost.PerformClick();
            else if (this.rbUnsharpMasking.Checked)
                this.rbUnsharpMasking.PerformClick();
            else if (this.rbFFTSharpening.Checked)
                this.rbFFTSharpening.PerformClick();
            else if (this.rbDCTSharpening.Checked)
                this.rbDCTSharpening.PerformClick();
            else if (this.rbHighFreqEmphasis.Checked)
                this.rbHighFreqEmphasis.PerformClick();
            else if (this.rbHomomorphic.Checked)
                this.rbHomomorphic.PerformClick();

            // enable Apply button
            this.btSharpeningApply.Enabled = true;
            this.Cursor = Cursors.Default;
        }
        private void btSharpeningApply_Click(object sender, EventArgs e)
        {
            ViewerForm viewer = MainForm.Viewers.SelectedViewer;
            if (viewer == null)
            {
                MessageBox.Show("Please give an input image!", "No input image!",
                    MessageBoxButtons.OK, MessageBoxIcon.Warning);
                return;
            }
            string newImageName = "";
            int SelectBoxValue = 0;

            // disable Apply button
            this.btSharpeningApply.Enabled = false;
            this.Cursor = Cursors.WaitCursor;

            // get the image that will be operated on
            int inputImage = viewer.CVIPimage, outputImage = 0;

            switch (sharpeningSelected)
            {
            case "SharpeningI":
                if (rbMaskI.Checked)
                    SelectBoxValue = 1;
                else if (rbMaskII.Checked)
                    SelectBoxValue = 2;
                else
                { }
                outputImage = CvipOp.Sharpening_AlgorithmI(inputImage, Convert.ToInt16(checkBoxSharpening1.Checked), SelectBoxValue, Convert.ToInt16(Convert.ToDouble(cbSharpening1.Text)), Convert.ToSingle(cbSharpening2.Text), Convert.ToSingle(cbSharpening3.Text), Convert.ToInt16(checkBoxSharpening2.Checked));

                // create a name for the new image
                newImageName = viewer.Text;
                newImageName = newImageName + "_" + CvipFunctionNames.getFncName("SharpI") + Convert.ToString(CvipConstant.imageNameCount);
                CvipConstant.imageNameCount++;

                //Save image name and path into image queue and
                //create an instance of imageViewer From for holding image and doing other operations
                if (outputImage != 0) MainForm.Viewers.Add(outputImage, newImageName);
                break;

            case "SharpeningII":
                outputImage = CvipOp.Sharpening_AlgorithmII(inputImage, Convert.ToInt16(checkBoxSharpening2.Checked));

                // create a name for the new image
                newImageName = viewer.Text;
                newImageName = newImageName + "_" + CvipFunctionNames.getFncName("SharpII") + Convert.ToString(CvipConstant.imageNameCount);
                CvipConstant.imageNameCount++;

                //Save image name and path into image queue and
                //create an instance of imageViewer From for holding image and doing other operations
                if (outputImage != 0) MainForm.Viewers.Add(outputImage, newImageName);
                break;

             case "SharpeningIII":
                    outputImage = CvipOp.Sharpening_AlgorithmIII(inputImage, Convert.ToInt16(checkBoxSharpening2.Checked));

                    // create a name for the new image
                    newImageName = viewer.Text;
                    newImageName = newImageName + "_" + CvipFunctionNames.getFncName("SharpII") + Convert.ToString(CvipConstant.imageNameCount);
                    CvipConstant.imageNameCount++;

                    //Save image name and path into image queue and
                    //create an instance of imageViewer From for holding image and doing other operations
                    if (outputImage != 0) MainForm.Viewers.Add(outputImage, newImageName);
                break;

                case "HighpassSpatial":
                outputImage = CvipOp.Highpass_Spatial_Filter(inputImage, Convert.ToInt16(checkBoxSharpening2.Checked));

                // create a name for the new image
                newImageName = viewer.Text;
                newImageName = newImageName + "_" + CvipFunctionNames.getFncName("Highpass") + Convert.ToString(CvipConstant.imageNameCount);
                CvipConstant.imageNameCount++;

                //Save image name and path into image queue and
                //create an instance of imageViewer From for holding image and doing other operations
                if (outputImage != 0) MainForm.Viewers.Add(outputImage, newImageName);
                break;

            case "HighBoost":
                outputImage = CvipOp.HighBoost(inputImage, Convert.ToInt16(Convert.ToDouble(cbSharpening1.Text)), Convert.ToInt16(Convert.ToDouble(cbSharpening2.Text)), Convert.ToInt16(checkBoxSharpening2.Checked));

                // create a name for the new image
                newImageName = viewer.Text;
                newImageName = newImageName + "_" + CvipFunctionNames.getFncName("HighBoost") + Convert.ToString(CvipConstant.imageNameCount);
                CvipConstant.imageNameCount++;

                //Save image name and path into image queue and
                //create an instance of imageViewer From for holding image and doing other operations
                if (outputImage != 0) MainForm.Viewers.Add(outputImage, newImageName);
                break;

            case "UnsharpMasking":
                outputImage = CvipOp.Unsharp_Masking(inputImage, Convert.ToInt16(Convert.ToDouble(cbSharpening1.Text)), Convert.ToInt16(Convert.ToDouble(cbSharpening2.Text)), Convert.ToDouble(cbSharpening3.Text), Convert.ToDouble(cbSharpening4.Text));

                // create a name for the new image
                newImageName = viewer.Text;
                newImageName = newImageName + "_" + CvipFunctionNames.getFncName("Unsharp") + Convert.ToString(CvipConstant.imageNameCount);
                CvipConstant.imageNameCount++;

                //Save image name and path into image queue and
                //create an instance of imageViewer From for holding image and doing other operations
                if (outputImage != 0) MainForm.Viewers.Add(outputImage, newImageName);
                break;

            case "FFTSharpening":
                outputImage = CvipOp.FFTSharpening(inputImage, Convert.ToInt16(Convert.ToDouble(cbSharpening1.Text)), Convert.ToInt16(Convert.ToDouble(cbSharpening2.Text)), Convert.ToInt16(checkBoxSharpening2.Checked));

                // create a name for the new image
                newImageName = viewer.Text;
                newImageName = newImageName + "_" + CvipFunctionNames.getFncName("FFTSharpen") + Convert.ToString(CvipConstant.imageNameCount);
                CvipConstant.imageNameCount++;

                //Save image name and path into image queue and
                //create an instance of imageViewer From for holding image and doing other operations
                if (outputImage != 0) MainForm.Viewers.Add(outputImage, newImageName);
                break;

            case "DCTSharpening":
                outputImage = CvipOp.DCTSharpening(inputImage, Convert.ToInt16(Convert.ToDouble(cbSharpening1.Text)), Convert.ToInt16(Convert.ToDouble(cbSharpening2.Text)), Convert.ToInt16(checkBoxSharpening2.Checked));

                // create a name for the new image
                newImageName = viewer.Text;
                newImageName = newImageName + "_" + CvipFunctionNames.getFncName("DCTSharpen") + Convert.ToString(CvipConstant.imageNameCount);
                CvipConstant.imageNameCount++;

                //Save image name and path into image queue and
                //create an instance of imageViewer From for holding image and doing other operations
                if (outputImage != 0) MainForm.Viewers.Add(outputImage, newImageName);
                break;

            case "HighFreqEmphasis":
                outputImage = CvipOp.HighFreq_Emphasize(inputImage, Convert.ToInt16(cbSharpening1.SelectedIndex), Convert.ToInt16(Convert.ToDouble(cbSharpening2.Text)), Convert.ToInt16(Convert.ToDouble(cbSharpening3.Text)), Convert.ToDouble(cbSharpening4.Text), Convert.ToInt16(checkBoxSharpening2.Checked));

                // create a name for the new image
                newImageName = viewer.Text;
                newImageName = newImageName + "_" + CvipFunctionNames.getFncName("HighFreqEmph") + Convert.ToString(CvipConstant.imageNameCount);
                CvipConstant.imageNameCount++;

                //Save image name and path into image queue and
                //create an instance of imageViewer From for holding image and doing other operations
                if (outputImage != 0) MainForm.Viewers.Add(outputImage, newImageName);
                break;

            case "Homomorphic":
                int row, col;
                int cutoff_limit, cutoff;
                double high_freq_gain, low_freq_gain;

                row = CvipOp.GetNoOfRows_Image(inputImage);
                col = CvipOp.GetNoOfCols_Image(inputImage);

                if (row < col)
                {
                    cutoff_limit = row / 2;
                }
                else
                {
                    cutoff_limit = col / 2;
                }
                cutoff = Convert.ToInt16(Convert.ToDouble(cbSharpening1.Text));
                low_freq_gain = Convert.ToDouble(cbSharpening2.Text);
                high_freq_gain = Convert.ToDouble(cbSharpening3.Text);

                if (cutoff < 0 || cutoff > cutoff_limit)
                {
                    MessageBox.Show("The cutooff frequency should be within [0," + Convert.ToString(cutoff_limit) + "]",
                        "Range error!", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                }
                else
                {
                    outputImage = CvipOp.Homomorphic_Sharpen(inputImage, cutoff, low_freq_gain, high_freq_gain, Convert.ToInt16(checkBoxSharpening2.Checked));

                    // create a name for the new image
                    newImageName = viewer.Text;
                    newImageName = newImageName + "_" + CvipFunctionNames.getFncName("Homomorphic") + Convert.ToString(CvipConstant.imageNameCount);
                    CvipConstant.imageNameCount++;

                    //Save image name and path into image queue and
                    //create an instance of imageViewer From for holding image and doing other operations
                    if (outputImage != 0) MainForm.Viewers.Add(outputImage, newImageName);
                }
                break;
            }//End: switch()

            // delete input image
            CvipOp.Delete_Image(ref inputImage);

            // enable Apply button
            this.btSharpeningApply.Enabled = true;
            this.Cursor = Cursors.Default;
        }

        private void rbSharpIII_Click(object sender, EventArgs e)
        {
            string[] items;
            sharpeningSelected = "SharpeningIII";

            lbLaplacian.Visible = false;
            rbMaskI.Visible = false;
            rbMaskII.Visible = false;

            lblLowPercent.Visible = false;
            lblHighPercent.Visible = false;

            lbSharpening1.Visible = false;
            lbSharpening1.Text = "Kernel Size of Sobel";
            cbSharpening1.Visible = false;
            items = new string[] { "3", "5", "7" };
            cbSharpening1.DataSource = items;
            cbSharpening1.Text = "3";

            lbSharpening2.Visible = false;
            lbSharpening2.Text = "Low Clip Percent";
            cbSharpening2.Visible = false;
            items = new string[] { "0.0", "0.005", "0.01", "0.015", "0.02" };
            cbSharpening2.DataSource = items;
            cbSharpening2.Text = "0.005";

            lbSharpening3.Visible = false;
            lbSharpening3.Text = "High Clip Percent";
            cbSharpening3.Visible = false;
            items = new string[] { "0.0", "0.005", "0.01", "0.015", "0.02" };
            cbSharpening3.DataSource = items;
            cbSharpening3.Text = "0.005";

            lbSharpening4.Visible = false;
            lbSharpening4.Text = "Kernel Size of Sobel";
            cbSharpening4.Visible = false;
            items = new string[] { "3", "5", "7" };
            cbSharpening4.DataSource = items;
            cbSharpening4.Text = "3";

            checkBoxSharpening1.Visible = false;
            checkBoxSharpening1.Checked = false;
            checkBoxSharpening1.Text = "Intermediate Image Remapping";

            checkBoxSharpening2.Visible = true;
            checkBoxSharpening2.Checked = true;
            checkBoxSharpening2.Text = "Add to Original Image";
        }

        private void Percent_TextChanged(object sender, EventArgs e)
        {
            ComboBox cbo = sender as ComboBox;
            if (cbo.Name == "cbSharpening2" && sharpeningSelected == "SharpeningI")
            {
                float percent = float.Parse(this.cbSharpening2.Text) * 100;
                lblLowPercent.Text = percent.ToString() + "%";
            }
            else if (cbo.Name == "cbSharpening3" && sharpeningSelected == "SharpeningI")
            {
                float percent = float.Parse(this.cbSharpening3.Text) * 100;
                lblHighPercent.Text = percent.ToString() + "%";
            }
            else if (cbo.Name == "cbSharpening3" && sharpeningSelected == "UnsharpMasking")
            {
                float percent = float.Parse(this.cbSharpening3.Text) * 100;
                lblLowPercent.Text = percent.ToString() + "%";
            }
            else if (cbo.Name == "cbSharpening4" && sharpeningSelected == "UnsharpMasking")
            {
                float percent = float.Parse(this.cbSharpening4.Text) * 100;
                lblHighPercent.Text = percent.ToString() + "%";
            }
        }
    }
}
