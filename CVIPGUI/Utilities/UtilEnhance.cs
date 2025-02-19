/*''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' ======================================================================
' Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
' ======================================================================
'
'             File Name: UtilEnhance.cs
'           Description: Contains the controls and code
'                        for Utilities->UtilEnhance page
'         Related Files: CvipOp.cs
'                        CvipConstant.cs
'   Initial Coding Date: April 2007
'              Modified: March 2010
'       Delevoping tool: Visual Studio 2008-C#
'             Credit(s): Wenjun(Evan) Bian
'                        Patrick Solt
Hari Siva Kumar Reddy Bhogala
'                        Southern Illinois University Edwardsville
'
' Copyright (C) 2010 Scott Umbaugh and SIUE
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

namespace CVIPGUI.Utilities
{
    public partial class UtilEnhance : UserControl
    {
        ViewerForm SelectedViewer;
        private string mOpName;

        public UtilEnhance()
        {
            InitializeComponent();
        }

        private void AddImageToQueue(string OpName, int outputImage)
        {
            string newImageName = "";
            try
            {
                // create a name for the new image
                newImageName = SelectedViewer.Text + "_" + OpName + Convert.ToString(CvipConstant.imageNameCount);
                CvipConstant.imageNameCount++;

                //Save image name and path into image queue and
                //create an instance of imageViewer From for holding image and doing other operations
                MainForm.Viewers.Add(outputImage, newImageName);
            }
            catch (Exception e)
            {
                MessageBox.Show(e.Message);
            }
        }

        private void btnApply_Click(object sender, EventArgs e)
        {
            int inputImage = 0, outputImage = 0;
            string appendix = "";
            try
            {
                // disable Apply button
                this.btnApply.Enabled = false;
                this.Cursor = Cursors.WaitCursor;

                if (SelectedViewer == null)
                    throw new Exception("No input image!");
                else
                    // get the image that will be operated on
                    inputImage = SelectedViewer.CVIPimage;

                switch (mOpName)
                {
                case "Brighten/Darken":
                    outputImage = CvipOp.Gray_Multiply(inputImage, Convert.ToSingle(cmbUtilEnhanceBDFactor.Text));
                    appendix = "x" + cmbUtilEnhanceBDFactor.Text.ToString() + "_";
                    break;

                case "Edge Enhancement":
                    int imageWidth = 0, imageHeight = 0, imageSize = 0, cutoff = 0;

                    imageWidth = CvipOp.GetNoOfCols_Image(inputImage);
                    imageHeight = CvipOp.GetNoOfRows_Image(inputImage);
                    if (imageHeight > imageWidth)
                        imageSize = imageHeight;
                    else
                        imageSize = imageWidth;

                    if (imageSize < 2)
                        imageSize = 2;

                    //raise to next number of 2's power
                    imageSize = Convert.ToInt32(Math.Pow(2.0, Math.Round(Math.Log(imageSize - 1.0) / Math.Log(2.0)) + 0.5));

                    if (imageSize >= 16)
                        cutoff = imageSize / 16;
                    else
                        cutoff = 1;

                    if (rdbUtilEnhanceHighFreqEmphasis.Checked)
                    {
                        outputImage = CvipOp.HighFreq_Emphasize(inputImage, cmbUtilEnhanceTransform.SelectedIndex, cutoff, 1, 0.5, 1);
                        appendix = "Hfe";
                    }
                    else if (rdbUtilEnhanceUnsharp.Checked)
                    {
                        double[] rangeArray;
                        int maxVal;

                        rangeArray = CvipOp.Get_max_min_value(inputImage);
                        maxVal = Convert.ToInt32(rangeArray[1]);
                        if (Convert.ToDouble(cmbUnsharp2.Text) < 0 ||  Convert.ToDouble(cmbUnsharp4.Text) < 0)
                        {
                            MessageBox.Show("Clip Percentage can't be negative. ", "Positive Value Required",
                           MessageBoxButtons.OK, MessageBoxIcon.Warning);
                            break;
                        }
                        outputImage = CvipOp.Unsharp_Masking(inputImage, Convert.ToInt32(cmbUnsharp1.Text), Convert.ToInt32(cmbUnsharp3.Text), Convert.ToDouble(cmbUnsharp2.Text), Convert.ToDouble(cmbUnsharp4.Text));
                        appendix = "Unsharp";
                    }
                    else if (rdbUtilEnhanceFFT.Checked)
                    {
                        outputImage = CvipOp.FFTSharpening(inputImage, cutoff, 1, 1);
                        appendix = "FFTSharp";
                    }
                    else if (rdbUtilEnhanceDCT.Checked)
                    {
                        outputImage = CvipOp.DCTSharpening(inputImage, cutoff, 1, 1);
                        appendix = "DCTSharp";
                    }
                    break;

                case "Histogram Equalization":
                    if (rdbUtilEnhanceValue.Checked)
                        outputImage = CvipOp.Histogram_Equalization(inputImage, 0);
                    else if (rdbUtilEnhanceRed.Checked)
                        outputImage = CvipOp.Histogram_Equalization(inputImage, 1);
                    else if (rdbUtilEnhanceGreen.Checked)
                        outputImage = CvipOp.Histogram_Equalization(inputImage, 2);
                    else if (rdbUtilEnhanceBlue.Checked)
                        outputImage = CvipOp.Histogram_Equalization(inputImage, 3);

                    appendix = "Heq";
                    break;

                case "Histogram Stretch":
                    if ( Convert.ToSingle(cmbUtilEnhanceHistoStretchLowClipPercent.Text) < 0 || Convert.ToSingle(cmbUtilEnhanceHistoStretchHighClipPercent.Text) < 0)
                    {
                        MessageBox.Show("Clip Percentage can't be negative. ", "Positive Value Required",
                       MessageBoxButtons.OK, MessageBoxIcon.Warning);
                        break;
                    }
                    outputImage = CvipOp.Histogram_Stretch(inputImage, Convert.ToInt32(cmbUtilEnhanceHistoStretchLowerLimit.Text), Convert.ToInt32(cmbUtilEnhanceHistoStretchHigherLimit.Text), Convert.ToSingle(cmbUtilEnhanceHistoStretchLowClipPercent.Text), Convert.ToSingle(cmbUtilEnhanceHistoStretchHighClipPercent.Text));

                    appendix = "HistStretch";
                    break;

                case "Pseudocolor":
                    if (rdbUtilEnhanceFreqMapping.Checked)
                        outputImage = CvipOp.Pseudocol_Freq(inputImage, Convert.ToInt32(cmbUtilEnhanceLowCutoffFreq.Text), Convert.ToInt32(cmbUtilEnhanceHighCutoffFreq.Text), Convert.ToInt32(cmbUtilEnhanceLowPassColor.SelectedIndex), Convert.ToInt32(cmbUtilEnhanceBandPassColor.SelectedIndex), Convert.ToInt32(cmbUtilEnhanceHighPassColor.SelectedIndex));
                    else if (rdbUtilEnhanceGLMapping.Checked)
                        outputImage = CvipOp.Graylevel_Remap(inputImage, Convert.ToInt32(cmbUtilEnhanceRed.SelectedIndex), Convert.ToInt32(cmbUtilEnhanceGreen.SelectedIndex), Convert.ToInt32(cmbUtilEnhanceBlue.SelectedIndex));

                    appendix = "Pseudo";
                    break;

                case "Sharpening":
                    int mask = 1;
                    if (rdbUtilEnhanceSharpeningMakeI.Checked)
                        mask = 1;
                    else if (rdbUtilEnhanceSharpeningMakeII.Checked)
                        mask = 2;

                    if ( Convert.ToSingle(cmbUtilEnhanceSharpeningLowClipPercent.Text) < 0 || Convert.ToSingle(cmbUtilEnhanceSharpeningHighClipPercent.Text) < 0)
                    {
                        
                        MessageBox.Show("Clip Percentage can't be negative. ", "Positive Value Required",
                       MessageBoxButtons.OK, MessageBoxIcon.Warning);
                        break;
                    }
                        if ( Convert.ToInt32(cmbUtilEnhanceSharpeningKernelSize.Text)  < 0 )
                    {
                        MessageBox.Show("Kernel Size can't be negative. ", "Positive Value Required",
                       MessageBoxButtons.OK, MessageBoxIcon.Warning);
                        break;
                    }
                    outputImage = CvipOp.Sharpening_AlgorithmI(inputImage, Convert.ToInt32(chkUtilEnhanceSharpeningRemap.Checked), mask, Convert.ToInt32(cmbUtilEnhanceSharpeningKernelSize.Text), Convert.ToSingle(cmbUtilEnhanceSharpeningLowClipPercent.Text), Convert.ToSingle(cmbUtilEnhanceSharpeningHighClipPercent.Text), Convert.ToInt32(chkUtilEnhanceSharpeningAddOrigImage.Checked));
                    appendix = "Sharpening";
                    break;
                }

                if (outputImage != 0) AddImageToQueue(appendix, outputImage);

                // delete input image
                CvipOp.Delete_Image(ref inputImage);

                // enable Apply button
                this.btnApply.Enabled = true;
                this.Cursor = Cursors.Default;
            }
            catch (Exception e1)
            {
                // enable Apply button
                this.btnApply.Enabled = true;
                this.Cursor = Cursors.Default;
                MessageBox.Show(e1.Message);
            }
        }

        private void btnCancel_Click(object sender, EventArgs e)
        {
            MainForm.UtilitiesForm.Close();
        }

        private void btnHelp_Click(object sender, EventArgs e)
        {
            MainForm.ShowHelp();
        }

        private void btnReset_Click(object sender, EventArgs e)
        {
            switch (mOpName)
            {
            case "Brighten/Darken":
                cmbUtilEnhanceBDFactor.SelectedIndex = 3;
                break;

            case "Edge Enhancement":
                lblUtilEnhanceTransform.Visible = true;
                cmbUtilEnhanceTransform.Visible = true;
                cmbUtilEnhanceTransform.Visible = false;
                lblUtilEnhanceTransform.Visible = false;
                rdbUtilEnhanceUnsharp.Checked = true;
                cmbUtilEnhanceTransform.SelectedIndex = 0;
                break;

            case "Histogram Equalization":
                rdbUtilEnhanceValue.Checked = true;
                break;

            case "Histogram Stretch":
                cmbUtilEnhanceHistoStretchLowerLimit.SelectedIndex = 0;
                cmbUtilEnhanceHistoStretchHigherLimit.SelectedIndex = 9;
                cmbUtilEnhanceHistoStretchLowClipPercent.SelectedIndex = 3;
                cmbUtilEnhanceHistoStretchHighClipPercent.SelectedIndex = 3;
                break;

            case "Pseudocolor":
                this.rdbUtilEnhanceFreqMapping.Checked = true;
                this.cmbUtilEnhanceLowCutoffFreq.SelectedIndex = 1;
                this.cmbUtilEnhanceHighCutoffFreq.SelectedIndex = 0;
                this.cmbUtilEnhanceLowPassColor.SelectedIndex = 0;
                this.cmbUtilEnhanceBandPassColor.SelectedIndex = 1;
                this.cmbUtilEnhanceHighPassColor.SelectedIndex = 2;

                this.cmbUtilEnhanceRed.SelectedIndex = 0;
                this.cmbUtilEnhanceGreen.SelectedIndex = 1;
                this.cmbUtilEnhanceBlue.SelectedIndex = 2;
                break;

            case "Sharpening":
                chkUtilEnhanceSharpeningRemap.Checked = true;
                chkUtilEnhanceSharpeningAddOrigImage.Checked = true;
                cmbUtilEnhanceSharpeningKernelSize.SelectedIndex = 0;
                cmbUtilEnhanceSharpeningLowClipPercent.SelectedIndex = 2;
                cmbUtilEnhanceSharpeningHighClipPercent.SelectedIndex = 2;
                break;
            }
        }

        private void cmbUtilEnhanceRed_DrawItem(object sender, DrawItemEventArgs e)
        {
            if (e.Index != -1)
                e.Graphics.DrawImage(UtilPseudoColorImageList.Images[e.Index], e.Bounds.Left, e.Bounds.Top);
        }

        private void cmbUtilEnhanceGreen_DrawItem(object sender, DrawItemEventArgs e)
        {
            if (e.Index != -1)
                e.Graphics.DrawImage(UtilPseudoColorImageList.Images[e.Index], e.Bounds.Left, e.Bounds.Top);
        }

        private void cmbUtilEnhanceBlue_DrawItem(object sender, DrawItemEventArgs e)
        {
            if (e.Index != -1)
                e.Graphics.DrawImage(UtilPseudoColorImageList.Images[e.Index], e.Bounds.Left, e.Bounds.Top);
        }

        public void Init(string op)
        {
            this.mOpName = op;
            pnlUtilEnhanceBD.Visible = false;
            pnlUtilEnhanceEdgeEnhance.Visible = false;
            pnlUtilEnhanceHistoEqual.Visible = false;
            pnlUtilEnhanceHistoStretch.Visible = false;
            pnlUtilEnhancePseudocolor.Visible = false;
            pnlUtilEnhanceSharpening.Visible = false;

            switch (mOpName)
            {
            case "Brighten/Darken":
                pnlUtilEnhanceBD.Visible = true;
                break;

            case "Edge Enhancement":
                pnlUtilEnhanceEdgeEnhance.Visible = true;
                break;

            case "Histogram Equalization":
                pnlUtilEnhanceHistoEqual.Visible = true;
                break;

            case "Histogram Stretch":
                pnlUtilEnhanceHistoStretch.Visible = true;
                break;

            case "Pseudocolor":
                pnlUtilEnhancePseudocolor.Visible = true;
                break;

            case "Sharpening":
                pnlUtilEnhanceSharpening.Visible = true;
                break;
            }
            UpdateImageList();
        }

        protected override void OnLoad(EventArgs e)
        {
            base.OnLoad(e);

            this.pnlUtilEnhancePseudocolor.Location = new Point(4, 20);
            this.pnlUtilEnhanceBD.Location = new Point(4, 20);
            this.pnlUtilEnhanceEdgeEnhance.Location = new Point(4, 20);
            this.pnlUtilEnhanceHistoEqual.Location = new Point(4, 20);
            this.pnlUtilEnhanceHistoStretch.Location = new Point(4, 20);
            this.pnlUtilEnhanceSharpening.Location = new Point(4, 20);
           // if ((this.Height / 4 > 150))
            //    this.Size = new Size(this.Width / 2, this.Height / 4);
           // else
           // this.Size = new Size(581, 172);

            //Brightening/Darkening
            cmbUtilEnhanceBDFactor.SelectedIndex = 3;

            //Edge Enhancement
            cmbUtilEnhanceTransform.SelectedIndex = 0;

            //Histogram Stretch
            cmbUtilEnhanceHistoStretchLowerLimit.SelectedIndex = 0;
            cmbUtilEnhanceHistoStretchHigherLimit.SelectedIndex = 9;
            cmbUtilEnhanceHistoStretchLowClipPercent.SelectedIndex = 3;
            cmbUtilEnhanceHistoStretchHighClipPercent.SelectedIndex = 3;

            //Pseudocolor
            this.cmbUtilEnhanceLowCutoffFreq.SelectedIndex = 1;
            this.cmbUtilEnhanceHighCutoffFreq.SelectedIndex = 0;
            this.cmbUtilEnhanceLowPassColor.SelectedIndex = 0;
            this.cmbUtilEnhanceBandPassColor.SelectedIndex = 1;
            this.cmbUtilEnhanceHighPassColor.SelectedIndex = 2;

            this.cmbUtilEnhanceRed.SelectedIndex = 0;
            this.cmbUtilEnhanceGreen.SelectedIndex = 1;
            this.cmbUtilEnhanceBlue.SelectedIndex = 2;

            //Sharpening
            cmbUtilEnhanceSharpeningKernelSize.SelectedIndex = 0;
            cmbUtilEnhanceSharpeningLowClipPercent.SelectedIndex = 2;
            cmbUtilEnhanceSharpeningHighClipPercent.SelectedIndex = 2;

            UpdateImageList();
        }

        private void rdbUtilEnhanceDCT_CheckedChanged(object sender, EventArgs e)
        {
            lblUtilEnhanceTransform.Visible = false;
            cmbUtilEnhanceTransform.Visible = false;
            lblUnsharp1.Visible = false;
            lblUnsharp2.Visible = false;
            lblUnsharp3.Visible = false;
            lblUnsharp4.Visible = false;
            cmbUnsharp1.Visible = false;
            cmbUnsharp2.Visible = false;
            cmbUnsharp3.Visible = false;
            cmbUnsharp4.Visible = false;
        }

        private void rdbUtilEnhanceFFT_CheckedChanged(object sender, EventArgs e)
        {
            lblUtilEnhanceTransform.Visible = false;
            cmbUtilEnhanceTransform.Visible = false;
            lblUnsharp1.Visible = false;
            lblUnsharp2.Visible = false;
            lblUnsharp3.Visible = false;
            lblUnsharp4.Visible = false;
            cmbUnsharp1.Visible = false;
            cmbUnsharp2.Visible = false;
            cmbUnsharp3.Visible = false;
            cmbUnsharp4.Visible = false;
        }

        private void rdbUtilEnhanceFreqMapping_CheckedChanged(object sender, EventArgs e)
        {
            this.pnlUtilEnhanceGLMapping.Visible = false;
            this.pnlUtilEnhanceFreqMapping.Visible = true;
            lblUnsharp1.Visible = false;
            lblUnsharp2.Visible = false;
            lblUnsharp3.Visible = false;
            lblUnsharp4.Visible = false;
            cmbUnsharp1.Visible = false;
            cmbUnsharp2.Visible = false;
            cmbUnsharp3.Visible = false;
            cmbUnsharp4.Visible = false;
        }

        private void rdbUtilEnhanceGLMapping_CheckedChanged(object sender, EventArgs e)
        {
            this.pnlUtilEnhanceGLMapping.Visible = true;
            this.pnlUtilEnhanceFreqMapping.Visible = false;
            lblUnsharp1.Visible = false;
            lblUnsharp2.Visible = false;
            lblUnsharp3.Visible = false;
            lblUnsharp4.Visible = false;
            cmbUnsharp1.Visible = false;
            cmbUnsharp2.Visible = false;
            cmbUnsharp3.Visible = false;
            cmbUnsharp4.Visible = false;
        }

        private void rdbUtilEnhanceHighFreqEmphasis_CheckedChanged(object sender, EventArgs e)
        {
            lblUtilEnhanceTransform.Visible = true;
            cmbUtilEnhanceTransform.Visible = true;
            lblUnsharp1.Visible = false;
            lblUnsharp2.Visible = false;
            lblUnsharp3.Visible = false;
            lblUnsharp4.Visible = false;
            cmbUnsharp1.Visible = false;
            cmbUnsharp2.Visible = false;
            cmbUnsharp3.Visible = false;
            cmbUnsharp4.Visible = false;
        }

        private void rdbUtilEnhanceUnsharp_CheckedChanged(object sender, EventArgs e)
        {
            lblUtilEnhanceTransform.Visible = false;
            cmbUtilEnhanceTransform.Visible = false;
            lblUnsharp1.Visible = true;
            lblUnsharp2.Visible = true;
            lblUnsharp3.Visible = true;
            lblUnsharp4.Visible = true;
            cmbUnsharp1.Visible = true;
            cmbUnsharp2.Visible = true;
            cmbUnsharp3.Visible = true;
            cmbUnsharp4.Visible = true;
        }

        public void UpdateImageList()
        {
            if (MainForm.Viewers != null)
            {
                try
                {
                    lblUtilEnhanceCurrentImage.Text = "";
                    SelectedViewer = MainForm.Viewers.SelectedViewer;
                    if (SelectedViewer != null)
                    {
                        lblUtilEnhanceCurrentImage.Text = SelectedViewer.Text;

                        if (CvipOp.GetNoOfBands_Image(SelectedViewer.CVIPimage) == 1)
                        {
                            rdbUtilEnhanceRed.Enabled = false;
                            rdbUtilEnhanceGreen.Enabled = false;
                            rdbUtilEnhanceBlue.Enabled = false;
                        }
                        else
                        {
                            rdbUtilEnhanceRed.Enabled = true;
                            rdbUtilEnhanceGreen.Enabled = true;
                            rdbUtilEnhanceBlue.Enabled = true;
                        }
                    }
                }
                catch (Exception e1)
                {
                    MessageBox.Show(e1.Message);
                }
            }
        }

        private void label2_Click(object sender, EventArgs e)
        {

        }
    }
}
