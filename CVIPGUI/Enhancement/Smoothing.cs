/*''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' ======================================================================
' Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
' ======================================================================
'
'             File Name: Smoothing.cs
'           Description: Contains the controls and code
'                        for Enhancement->Smoothing tab
'         Related Files: CvipOp.cs
'                        CvipConstant.cs
'   Initial Coding Date: June 2007
'              Modified: October 2009
'       Delevoping tool: Visual Studio 2010-C#
'             Credit(s): Wenjun(Evan) Bian
'                        Patrick Solt,Hari Siva Kumar Reddy Bhogala
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
using CVIPGUI.Utilities;

namespace CVIPGUI.Enhancement
{
    enum SmoothingSelection
    {
        mean,
        gaussian,
        midpoint,
        contra,
        ypmean,
        median,
        adapmedian,
        kuwahara,
        anisotropic,
        adapanisotropic,
        fftsmooth,
        dctsmooth
    }

    public partial class Smoothing : UserControl
    {
        private SmoothingSelection currentSelection;
        //private UtilFilterMask filterMask = null;
        private double[,] defaultMatrix = null;
        public Smoothing()
        {
            InitializeComponent();
        }
        private void btnApply_Click(object sender, EventArgs e)
        {
            ViewerForm viewer = MainForm.Viewers.SelectedViewer;
            if (viewer == null)
            {
                MessageBox.Show("Please give an input image!", "No input image!",
                    MessageBoxButtons.OK, MessageBoxIcon.Warning);
                return;
            }
            // disable Apply button
            this.btnApply.Enabled = false;
            this.Cursor = Cursors.WaitCursor;

            // get the image that will be operated on
            int inputImage = viewer.CVIPimage, outputImage = 0;

            switch (this.currentSelection)
            {
                case SmoothingSelection.mean:
                    if (this.MaskSize > 11)
                    {
                        MessageBox.Show("Currently the maximum mask size is limited to 11.",
                            "Range error!", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                        break;
                    }
                    outputImage = CvipOp.Mean_Filter(inputImage, this.MaskSize);
                    break;

                case SmoothingSelection.gaussian:
                    double[,] filter = null;
                    if (this.MaskSize < 3)
                    {
                        MessageBox.Show("The mask size should be equal or greater than 3.",
                            "Range error!", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                        break;
                    }
                    else if (this.MaskSize > 31)
                    {
                        MessageBox.Show("Currently the maximum mask size is limited to 31.",
                            "Range error!", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                        break;
                    }

                    filter = SpecifyFilterGaussian();
                    this.defaultMatrix = filter;
                   
                    outputImage = CvipOp.Specify_Filter(inputImage, this.MaskSize, this.MaskSize,this.CurrentValues(), 1);

                    // outputImage = CvipOp.Gaussian_Blur_Filter(inputImage, this.MaskSize);
                    break;

                case SmoothingSelection.midpoint:
                    if (this.MaskSize > 11)
                    {
                        MessageBox.Show("Currently the maximum mask size is limited to 11.",
                            "Range error!", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                        break;
                    }
                    outputImage = CvipOp.Midpoint_Filter(inputImage, this.MaskSize);
                    break;

                case SmoothingSelection.contra:
                    if (this.MaskSize > 11)
                    {
                        MessageBox.Show("Currently the maximum mask size is limited to 11.",
                            "Range error!", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                        break;
                    }
                    outputImage = CvipOp.Contra_Filter(inputImage, this.MaskSize, this.Order);
                    break;

                case SmoothingSelection.ypmean:
                    if (this.MaskSize > 11)
                    {
                        MessageBox.Show("Currently the maximum mask size is limited to 11.",
                            "Range error!", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                        break;
                    }
                    outputImage = CvipOp.Ypmean_Filter(inputImage, this.MaskSize, this.Order);
                    break;

                case SmoothingSelection.median:
                    if (this.MaskSize < 3)
                    {
                        MessageBox.Show("The mask size should be equal or greater than 3.",
                            "Range error!", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                        break;
                    }
                    outputImage = CvipOp.Median_Filter(inputImage, this.MaskSize);
                    break;

                case SmoothingSelection.adapmedian:
                    if (this.MaskSize < 3)
                    {
                        MessageBox.Show("The mask size should be equal or greater than 3.",
                            "Range error!", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                        break;
                    }
                    else if (this.MaskSize > 31)
                    {
                        MessageBox.Show("Currently the maximum mask size is limited to 31.",
                            "Range error!", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                        break;
                    }
                    outputImage = CvipOp.Adapt_Median_Filter(inputImage, this.MaskSize);
                    break;

                case SmoothingSelection.kuwahara:
                    if (this.MaskSize < 3)
                    {
                        MessageBox.Show("The mask size should be equal or greater than 3.",
                            "Range error!", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                        break;
                    }
                    else if (this.MaskSize > 128)
                    {
                        MessageBox.Show("Currently the maximum mask size is limited to 128.",
                            "Range error!", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                        break;
                    }
                    outputImage = CvipOp.Kuwahara_Filter(inputImage, this.MaskSize);
                    break;

                case SmoothingSelection.anisotropic:
                    outputImage = CvipOp.AD_Filter(inputImage, this.Iterations, this.SmoothPerIter, this.EdgeThreshold);
                    break;

                case SmoothingSelection.adapanisotropic:
                    outputImage = CvipOp.Param_AD_Filter(inputImage, this.Iterations, this.SmoothPerIter, this.EdgeThreshold, this.BlockSize);
                    break;

                case SmoothingSelection.fftsmooth:
                    outputImage = CvipOp.FFTSmoothing(inputImage, this.Cutoff, 1);
                    break;

                case SmoothingSelection.dctsmooth:
                    outputImage = CvipOp.DCTSmoothing(inputImage, this.Cutoff, 1);
                    break;
            }
            if (outputImage != 0)
            {
                string newImageName = viewer.Text;
                newImageName += "_" + CvipFunctionNames.getFncName(this.currentSelection.ToString());
                newImageName += CvipConstant.imageNameCount++.ToString();
                MainForm.Viewers.Add(outputImage, newImageName);
            }
            // delete input image
            CvipOp.Delete_Image(ref inputImage);

            // enable Apply button
            this.btnApply.Enabled = true;
            this.Cursor = Cursors.Default;
        }
        private void btnCancel_Click(object sender, EventArgs e)
        {
            MainForm.EnhancementForm.Close();
        }
        private void btnHelp_Click(object sender, EventArgs e)
        {
            MainForm.ShowHelp();
        }
        private void btnReset_Click(object sender, EventArgs e)
        {
            ResetControls();
        }
        private void cboSmoothing_Validating(object sender, CancelEventArgs e)
        {
            int val;
            if (!int.TryParse(this.cboSmoothing.Text, out val))
            {
                MessageBox.Show("Please check the input value. Only unsigned integers are accepted.",
                   "Unsigned Integer Required", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                this.cboSmoothing.SelectAll();
                e.Cancel = true;
            }
            if (val < 1)
            {
                MessageBox.Show("Currently the minimum smoothing per iteration is limited to 1.",
                   "Range error!", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                this.cboSmoothing.SelectAll();
                e.Cancel = true;
            }
        }
        private void cboUIntVal_Validating(object sender, CancelEventArgs e)
        {
            ComboBox cbo = sender as ComboBox;
            int val;
            if (!int.TryParse(cbo.Text, out val) || (val < 0))
            {
                MessageBox.Show("Please check the input value. Only unsigned integers are accepted.",
                   "Unsigned Integer Required", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                cbo.SelectAll();
                e.Cancel = true;
            }
        }
        protected override void OnLoad(EventArgs e)
        {
            base.OnLoad(e);

            this.rbMean.Tag = SmoothingSelection.mean;
            this.rbGaussian.Tag = SmoothingSelection.gaussian;
            this.rbMidpoint.Tag = SmoothingSelection.midpoint;
            this.rbContraHarmonic.Tag = SmoothingSelection.contra;
            this.rbYpMean.Tag = SmoothingSelection.ypmean;
            this.rbMedian.Tag = SmoothingSelection.median;
            this.rbKuwahara.Tag = SmoothingSelection.kuwahara;
            this.rbADFilter.Tag = SmoothingSelection.anisotropic;
            this.rbFFTSmoothing.Tag = SmoothingSelection.fftsmooth;
            this.rbDCTSmoothing.Tag = SmoothingSelection.dctsmooth;

            ResetControls();
        }
        private void rbAdaptive_Click(object sender, EventArgs e)
        {
            if (this.rbADFilter.Checked)
            {
                if (this.rbAdaptive.Checked)
                    this.currentSelection = SmoothingSelection.adapanisotropic;
                else
                    this.currentSelection = SmoothingSelection.anisotropic;
            }
            else if (this.rbMedian.Checked)
            {
                if (this.rbAdaptive.Checked)
                    this.currentSelection = SmoothingSelection.adapmedian;
                else
                    this.currentSelection = SmoothingSelection.median;
            }
            UpdateControls();
        }
        private void rbSmoothing_Click(object sender, EventArgs e)
        {
            RadioButton rb = sender as RadioButton;
            if ((rb != null) && rb.Checked && (rb.Tag != null))
            {
                this.currentSelection = (SmoothingSelection)rb.Tag;
                if (this.rbAdaptive.Checked)
                {
                    if (this.currentSelection == SmoothingSelection.anisotropic)
                        this.currentSelection = SmoothingSelection.adapanisotropic;
                    else if (this.currentSelection == SmoothingSelection.median)
                        this.currentSelection = SmoothingSelection.adapmedian;
                }
                UpdateControls();
            }
        }

        private double[] CurrentValues()
        {

            double[] matrix = new double[this.MaskSize * this.MaskSize];
            for (int i = 0; i < this.MaskSize; i++)
            {
                for (int j = 0; j < this.MaskSize; j++)
                {
                    matrix[(i * this.MaskSize) + j] = this.defaultMatrix[i, j];

                }
            }
            return matrix;

        }

        private double[,] SpecifyFilterGaussian()
        {
            double[,] mask = new double[this.MaskSize, this.MaskSize];
            int center = this.MaskSize / 2;
            double weight = this.MaskSize * this.MaskSize;
            double sigma = Math.Sqrt(center * center / (2 * Math.Log(2) + (this.MaskSize - 3) * Math.Log(3)));
            sigma = 1.0 / 2.0 / sigma / sigma;
            for (int i = 0; i < this.MaskSize; i++)
            {
                for (int j = 0; j < this.MaskSize; j++)
                {
                    double tmp1 = (i - center) * (i - center);
                    double tmp2 = (j - center) * (j - center);
                    mask[i, j] = weight * Math.Exp(-(tmp1 + tmp2) * sigma);
                }
            }
            mask[center, center] = weight;
            return mask;
        }



        private void ResetControls()
        {
            this.cboMaskSize.Text = "3";
            this.cboOrder.SelectedIndex = 6;
            this.cboIterations.Text = "20";
            this.cboSmoothing.Text = "1";
            this.cboEdgeThreshold.Text = "5";
            this.cboBlockSize.Text = "64";
            this.cboCutoff.Text = "32";

            // Default current selection
            this.rbStandard.PerformClick();
            this.rbMean.PerformClick();

            // enable Apply button
            this.btnApply.Enabled = true;
            this.Cursor = Cursors.Default;
        }
        private void UpdateControls()
        {
            switch (this.currentSelection)
            {
                case SmoothingSelection.mean:
                case SmoothingSelection.gaussian:
                case SmoothingSelection.midpoint:
                case SmoothingSelection.contra:
                case SmoothingSelection.ypmean:
                case SmoothingSelection.kuwahara:
                    this.rbStandard.Visible = false;
                    this.rbAdaptive.Visible = false;
                    this.lblType.Visible = false;

                    this.pnlMask.Visible = true;
                    this.cboMaskSize.Items.Clear();
                    //if (this.currentSelection == SmoothingSelection.gaussian)
                    //{
                    //    this.cboMaskSize.Items.AddRange(new object[] {
                    //    "3",
                    //    "5",
                    //    "7"});
                    //}
                    //else
                    //{
                    this.cboMaskSize.Items.AddRange(new object[] {
                    "3",
                    "5",
                    "7",
                    "9",
                    "11"});
                    //}

                    this.cboOrder.Visible = (this.currentSelection == SmoothingSelection.contra) ||
                                                (this.currentSelection == SmoothingSelection.ypmean);
                    this.lblOrder.Visible = (this.currentSelection == SmoothingSelection.contra) ||
                                                (this.currentSelection == SmoothingSelection.ypmean);

                    this.pnlAnisotropic.Visible = false;
                    this.cboCutoff.Visible = false;
                    this.lblCutoff.Visible = false;
                    break;

                case SmoothingSelection.median:
                case SmoothingSelection.adapmedian:
                    this.rbStandard.Visible = true;
                    this.rbAdaptive.Text = "Adaptive";
                    this.rbAdaptive.Visible = true;
                    this.lblType.Visible = true;

                    this.pnlMask.Visible = true;
                    this.cboMaskSize.Items.Clear();
                    this.cboMaskSize.Items.AddRange(new object[] {
                "3",
                "5",
                "7",
                "9",
                "11"});
                    this.cboOrder.Visible = false;
                    this.lblOrder.Visible = false;

                    this.pnlAnisotropic.Visible = false;
                    this.cboCutoff.Visible = false;
                    this.lblCutoff.Visible = false;
                    break;

                case SmoothingSelection.anisotropic:
                case SmoothingSelection.adapanisotropic:
                    this.rbStandard.Visible = true;
                    this.rbAdaptive.Text = "Parametric";
                    this.rbAdaptive.Visible = true;
                    this.lblType.Visible = true;

                    this.pnlMask.Visible = false;

                    this.pnlAnisotropic.Visible = true;
                    this.cboBlockSize.Visible = this.currentSelection == SmoothingSelection.adapanisotropic;
                    this.lblBlockSize.Visible = this.currentSelection == SmoothingSelection.adapanisotropic;
                    this.cboCutoff.Visible = false;
                    this.lblCutoff.Visible = false;
                    break;

                case SmoothingSelection.fftsmooth:
                case SmoothingSelection.dctsmooth:
                    this.rbStandard.Visible = false;
                    this.rbAdaptive.Visible = false;
                    this.lblType.Visible = false;

                    this.pnlMask.Visible = false;
                    this.pnlAnisotropic.Visible = false;

                    this.cboCutoff.Visible = true;
                    this.lblCutoff.Visible = true;
                    break;
            }
            // enable Apply button
            this.btnApply.Enabled = true;
            this.Cursor = Cursors.Default;
        }

        private int BlockSize { get { return int.Parse(this.cboBlockSize.Text); } }
        private int Cutoff { get { return int.Parse(this.cboCutoff.Text); } }
         private int Order { get { return int.Parse(this.cboOrder.Text); } }
        private int MaskSize { get { return int.Parse(this.cboMaskSize.Text); } }
        private int SmoothPerIter { get { return int.Parse(this.cboSmoothing.Text); } }
        private int EdgeThreshold { get { return int.Parse(this.cboEdgeThreshold.Text); } }
        private int Iterations { get { return int.Parse(this.cboIterations.Text); } }
       
    }
}
