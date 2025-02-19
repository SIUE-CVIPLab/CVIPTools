/*''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' ======================================================================
' Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
' ======================================================================
'
'             File Name: SpatialFilter.cs
'           Description: UserControl contains the controls and code
'                        for Restoration->SpatialFilter tab
'         Related Files: CvipOp.cs
'                        CvipConstant.cs
'   Initial Coding Date: November 2007
'              Modified: December 2009
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

namespace CVIPGUI.Restoration
{
    enum SpatialSelection
    {
        median,
        minimum,
        midpoint,
        maximum,
        alphamean,
        arithmetic,
        geometric,
        harmonic,
        contra,
        ypmean,
        mmse,
        adaptmedian,
        kuwahara,
        adaptcontrast,
        anisotropic
    }

    public partial class SpatialFilter : UserControl
    {
        private SpatialSelection currentSelection;

        public SpatialFilter()
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
            case SpatialSelection.median:
                    if (this.MaskSize > 31)
                    {
                        MessageBox.Show("Currently the maximum mask size is limited to 31.",
                           "Range error!", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                        break;
                    }
                outputImage = CvipOp.Median_Filter(inputImage, this.MaskSize);
                break;

            case SpatialSelection.minimum:
                if (this.MaskSize > 11)
                {
                    MessageBox.Show("Currently the maximum mask size is limited to 11.",
                       "Range error!", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    break;
                }
                outputImage = CvipOp.Minimum_Filter(inputImage, this.MaskSize);
                break;

            case SpatialSelection.midpoint:
                if (this.MaskSize > 11)
                {
                    MessageBox.Show("Currently the maximum mask size is limited to 11.",
                       "Range error!", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    break;
                }
                outputImage = CvipOp.Midpoint_Filter(inputImage, this.MaskSize);
                break;

            case SpatialSelection.maximum:
                if (this.MaskSize > 11)
                {
                    MessageBox.Show("Currently the maximum mask size is limited to 11.",
                       "Range error!", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    break;
                }
                outputImage = CvipOp.Maximum_Filter(inputImage, this.MaskSize);
                break;

            case SpatialSelection.alphamean:
                if ((this.TrimSize > (Math.Pow(this.MaskSize, 2) - 1) / 2) ||
                    (this.TrimSize < 0))
                {
                    MessageBox.Show("'Trim Size' is beyond the range.",
                        "Range error!", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    break;
                }
                if (this.MaskSize > 11)
                {
                    MessageBox.Show("Currently the maximum mask size is limited to 11.",
                       "Range error!", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    break;
                }
                outputImage = CvipOp.Alpha_Filter(inputImage, this.MaskSize, this.TrimSize);
                break;

            case SpatialSelection.arithmetic:
                if (this.MaskSize > 11)
                {
                    MessageBox.Show("Currently the maximum mask size is limited to 11.",
                       "Range error!", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    break;
                }
                outputImage = CvipOp.Mean_Filter(inputImage, this.MaskSize);
                break;

            case SpatialSelection.geometric:
                if (this.MaskSize > 11)
                {
                    MessageBox.Show("Currently the maximum mask size is limited to 11.",
                       "Range error!", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    break;
                }
                outputImage = CvipOp.Geometric_Filter(inputImage, this.MaskSize);
                break;

            case SpatialSelection.harmonic:
                if (this.MaskSize > 31)
                {
                    MessageBox.Show("Currently the maximum mask size is limited to 31.",
                       "Range error!", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    break;
                }
                outputImage = CvipOp.Harmonic_Filter(inputImage, this.MaskSize);
                break;

            case SpatialSelection.contra:
                if (this.MaskSize > 11)
                {
                    MessageBox.Show("Currently the maximum mask size is limited to 11.",
                       "Range error!", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    break;
                }
                outputImage = CvipOp.Contra_Filter(inputImage, this.MaskSize, this.FilterOrder);
                break;

            case SpatialSelection.ypmean:
                if (this.FilterOrder == 0)
                {
                    MessageBox.Show("Zero is not allowed as filter order due to division by 0.",
                        "Range error!", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    break;
                }
                if (this.MaskSize > 31)
                {
                    MessageBox.Show("Currently the maximum mask size is limited to 31.",
                       "Range error!", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    break;
                }
                outputImage = CvipOp.Ypmean_Filter(inputImage, this.MaskSize, this.FilterOrder);
                break;

            case SpatialSelection.mmse:
                if (this.rbStandard.Checked)
                    outputImage = CvipOp.Mmse_Filter(inputImage, this.NoiseVariance, this.KernelSize);
                else
                    outputImage = CvipOp.Improved_Mmse_Filter(inputImage, this.Threshold, this.KernelSize, (float)this.NoiseVariance);
                break;

            case SpatialSelection.adaptmedian:
                if (this.MaskSize > 11)
                {
                    MessageBox.Show("Currently the maximum mask size is limited to 11.",
                       "Range error!", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    break;
                }
                outputImage = CvipOp.Adapt_Median_Filter(inputImage, this.MaskSize);
                break;

            case SpatialSelection.kuwahara:

                outputImage = CvipOp.Kuwahara_Filter(inputImage, this.MaskSize);
                break;

            case SpatialSelection.adaptcontrast:
                outputImage = CvipOp.Adaptive_Contrast_Filter(inputImage, this.LocalGainFactor, this.LocalMeanFactor, this.KernelSize, this.LocalGainMin, this.LocalGainMax);
                break;

            case SpatialSelection.anisotropic:
                if (this.rbStandard.Checked)
                    outputImage = CvipOp.AD_Filter(inputImage, this.NumIterations, this.SmoothPerIteration, this.EdgeThreshold);
                else
                    outputImage = CvipOp.Param_AD_Filter(inputImage, this.NumIterations, this.SmoothPerIteration, this.EdgeThreshold, this.BlockSize);
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
            MainForm.RestorationForm.Close();
        }
        private void btnHelp_Click(object sender, EventArgs e)
        {
            MainForm.ShowHelp();
        }
        private void btnReset_Click(object sender, EventArgs e)
        {
            ResetControls();
        }
        private void cboDoubleVal_Validating(object sender, CancelEventArgs e)
        {
            ComboBox cbo = sender as ComboBox;
            double val;
            if (!double.TryParse(cbo.Text, out val))
            {
                MessageBox.Show("Please check the input value. Only doubles are accepted.",
                   "Double Required", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                cbo.SelectAll();
                e.Cancel = true;
            }
        }
        private void cboFloatVal_Validating(object sender, CancelEventArgs e)
        {
            ComboBox cbo = sender as ComboBox;
            float val;
            if (!float.TryParse(cbo.Text, out val))
            {
                MessageBox.Show("Please check the input value. Only floats are accepted.",
                   "Float Required", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                cbo.SelectAll();
                e.Cancel = true;
            }
        }
        private void cboMaskSize_Validating(object sender, CancelEventArgs e)
        {
            ComboBox cbo = sender as ComboBox;
            int val;
            if (!int.TryParse(cbo.Text, out val))
            {
                MessageBox.Show("Please check the input value. Only integers are accepted.",
                   "Integer Required", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                cbo.SelectAll();
                e.Cancel = true;
            }
            //else if (val < 3)
            //{
            //    MessageBox.Show("The mask size should not be less than 3.",
            //        "Range error!", MessageBoxButtons.OK, MessageBoxIcon.Warning);
            //    cbo.SelectAll();
            //    e.Cancel = true;
            //}
            //else if (val > 11)
            //{
            //    MessageBox.Show("Currently the maximum mask size is limited to 11.",
            //        "Range error!", MessageBoxButtons.OK, MessageBoxIcon.Warning);
            //    cbo.SelectAll();
            //    e.Cancel = true;
            //}
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

            this.rbMedian.Tag = SpatialSelection.median;
            this.rbMinimum.Tag = SpatialSelection.minimum;
            this.rbMidpoint.Tag = SpatialSelection.midpoint;
            this.rbMaximum.Tag = SpatialSelection.maximum;
            this.rbAlphaTrim.Tag = SpatialSelection.alphamean;
            this.rbArithmetic.Tag = SpatialSelection.arithmetic;
            this.rbGeometric.Tag = SpatialSelection.geometric;
            this.rbHarmonic.Tag = SpatialSelection.harmonic;
            this.rbContraHarmonic.Tag = SpatialSelection.contra;
            this.rbYpMean.Tag = SpatialSelection.ypmean;
            this.rbMMSE.Tag = SpatialSelection.mmse;
            this.rbAdaptiveMedian.Tag = SpatialSelection.adaptmedian;
            this.rbKuwahara.Tag = SpatialSelection.kuwahara;
            this.rbAdaptiveContrast.Tag = SpatialSelection.adaptcontrast;
            this.rbAnisotropic.Tag = SpatialSelection.anisotropic;

            ResetControls();
        }
        private void rbSpatial_Click(object sender, EventArgs e)
        {
            RadioButton rb = sender as RadioButton;
            if ((rb != null) && rb.Checked && (rb.Tag != null))
                this.currentSelection = (SpatialSelection)rb.Tag;
            UpdateControls();
        }
        private void ResetControls()
        {
            // Order Filters group
            this.cboMaskSizeOrder.Text = "3";
            this.txtTrimSize.Text = "0";

            // Mean Filters group
            this.cboMaskSizeMean.Text = "3";
            this.cboFilterOrder.SelectedIndex = 6;

            // Adaptive Filters group
            this.cboMaskSizeAdaptive.Text = "3";

            // MMSE	panel
            this.cboNoiseVar.Text = "100.0";
            this.cboKernelSizeMMSE.Text = "9";
            this.cboThreshold.Text = "0.6";

            // Adaptive contrast panel
            this.cboLocalGain.Text = "0.8";
            this.cboLocalGainMin.Text = "5.0";
            this.cboLocalGainMax.Text = "10.0";
            this.cboLocalMean.Text = "1.0";
            this.cboKernelSizeAC.Text = "11";

            // Anisotropic panel
            this.cboIterations.Text = "20";
            this.cboEdgeThreshold.Text = "5";
            this.cboSmoothing.Text = "1";
            this.cboBlockSize.Text = "64";

            // Default current selection
            this.rbStandard.PerformClick();
            this.rbMedian.PerformClick();

            // enable Apply button
            this.btnApply.Enabled = true;
            this.Cursor = Cursors.Default;
        }
        private void txtIntVal_Validating(object sender, CancelEventArgs e)
        {
            TextBox txt = sender as TextBox;
            int val;
            if (!int.TryParse(txt.Text, out val))
            {
                MessageBox.Show("Please check the input value. Only integers are accepted.",
                   "Integer Required", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                txt.SelectAll();
                e.Cancel = true;
            }
        }
        private void UpdateControls()
        {
            switch (this.currentSelection)
            {
            case SpatialSelection.median:
            case SpatialSelection.minimum:
            case SpatialSelection.midpoint:
            case SpatialSelection.maximum:
            case SpatialSelection.alphamean:
                this.pnlOrderFilters.Visible = true;
                this.txtTrimSize.Visible = this.currentSelection == SpatialSelection.alphamean;
                this.lblTrimSize.Visible = this.currentSelection == SpatialSelection.alphamean;

                this.pnlMeanFilters.Visible = false;
                this.pnlAdaptiveFilters.Visible = false;
                break;

            case SpatialSelection.arithmetic:
            case SpatialSelection.geometric:
            case SpatialSelection.harmonic:
            case SpatialSelection.contra:
            case SpatialSelection.ypmean:
                this.pnlMeanFilters.Visible = true;
                this.cboFilterOrder.Visible = (this.currentSelection == SpatialSelection.contra) ||
                                                (this.currentSelection == SpatialSelection.ypmean);
                this.lblFilterOrder.Visible = (this.currentSelection == SpatialSelection.contra) ||
                                                (this.currentSelection == SpatialSelection.ypmean);

                this.pnlOrderFilters.Visible = false;
                this.pnlAdaptiveFilters.Visible = false;
                break;

            case SpatialSelection.mmse:
                this.pnlAdaptiveFilters.Visible = true;
                this.rbStandard.Visible = true;
                this.rbImproved.Text = "Improved";
                this.rbImproved.Visible = true;
                this.pnlMMSE.Visible = true;
                this.cboThreshold.Visible = this.rbImproved.Checked;
                this.lblThreshold.Visible = this.rbImproved.Checked;

                this.cboMaskSizeAdaptive.Visible = false;
                this.lblMaskSizeAdaptive.Visible = false;
                this.pnlAdaptiveContrast.Visible = false;
                this.pnlAnisotropic.Visible = false;
                this.pnlOrderFilters.Visible = false;
                this.pnlMeanFilters.Visible = false;
                break;

            case SpatialSelection.adaptmedian:
            case SpatialSelection.kuwahara:
                this.pnlAdaptiveFilters.Visible = true;
                this.cboMaskSizeAdaptive.Visible = true;
                this.lblMaskSizeAdaptive.Visible = true;

                this.rbStandard.Visible = false;
                this.rbImproved.Visible = false;
                this.pnlMMSE.Visible = false;
                this.pnlAdaptiveContrast.Visible = false;
                this.pnlAnisotropic.Visible = false;
                this.pnlOrderFilters.Visible = false;
                this.pnlMeanFilters.Visible = false;
                break;

            case SpatialSelection.adaptcontrast:
                this.pnlAdaptiveFilters.Visible = true;
                this.pnlAdaptiveContrast.Visible = true;

                this.rbStandard.Visible = false;
                this.rbImproved.Visible = false;
                this.cboMaskSizeAdaptive.Visible = false;
                this.lblMaskSizeAdaptive.Visible = false;
                this.pnlMMSE.Visible = false;
                this.pnlAnisotropic.Visible = false;
                this.pnlOrderFilters.Visible = false;
                this.pnlMeanFilters.Visible = false;
                break;

            case SpatialSelection.anisotropic:
                this.pnlAdaptiveFilters.Visible = true;
                this.rbStandard.Visible = true;
                this.rbImproved.Text = "Parametric";
                this.rbImproved.Visible = true;
                this.pnlAnisotropic.Visible = true;
                this.cboBlockSize.Visible = this.rbImproved.Checked;
                this.lblBlockSize.Visible = this.rbImproved.Checked;

                this.cboMaskSizeAdaptive.Visible = false;
                this.lblMaskSizeAdaptive.Visible = false;
                this.pnlMMSE.Visible = false;
                this.pnlAdaptiveContrast.Visible = false;
                this.pnlOrderFilters.Visible = false;
                this.pnlMeanFilters.Visible = false;
                break;
            }
            // enable Apply button
            this.btnApply.Enabled = true;
            this.Cursor = Cursors.Default;
        }

        private double LocalGainFactor { get { return double.Parse(this.cboLocalGain.Text); } }
        private double LocalGainMax { get { return double.Parse(this.cboLocalGainMax.Text); } }
        private double LocalGainMin { get { return double.Parse(this.cboLocalGainMin.Text); } }
        private double LocalMeanFactor { get { return double.Parse(this.cboLocalMean.Text); } }
        private double NoiseVariance { get { return double.Parse(this.cboNoiseVar.Text); } }

        private float Threshold { get { return float.Parse(this.cboThreshold.Text); } }

        private int BlockSize { get { return int.Parse(this.cboBlockSize.Text); } }
        private int EdgeThreshold { get { return int.Parse(this.cboEdgeThreshold.Text); } }
        private int FilterOrder { get { return int.Parse(this.cboFilterOrder.Text); } }
        private int NumIterations { get { return int.Parse(this.cboIterations.Text); } }
        private int SmoothPerIteration { get { return int.Parse(this.cboSmoothing.Text); } }
        private int TrimSize { get { return int.Parse(this.txtTrimSize.Text); } }

        private int KernelSize
        {
            get
            {
                int kernel = -1;
                switch (this.currentSelection)
                {
                case SpatialSelection.adaptcontrast:
                    kernel = int.Parse(this.cboKernelSizeAC.Text);
                    break;
                case SpatialSelection.mmse:
                    kernel = int.Parse(this.cboKernelSizeMMSE.Text);
                    break;
                }

                return kernel;
            }
        }
        private int MaskSize
        {
            get
            {
                int mask = -1;
                switch (this.currentSelection)
                {
                case SpatialSelection.median:
                case SpatialSelection.minimum:
                case SpatialSelection.midpoint:
                case SpatialSelection.maximum:
                case SpatialSelection.alphamean:
                    mask = int.Parse(this.cboMaskSizeOrder.Text);
                    break;
                case SpatialSelection.arithmetic:
                case SpatialSelection.geometric:
                case SpatialSelection.harmonic:
                case SpatialSelection.contra:
                case SpatialSelection.ypmean:
                    mask = int.Parse(this.cboMaskSizeMean.Text);
                    break;
                case SpatialSelection.adaptmedian:
                case SpatialSelection.kuwahara:
                    mask = int.Parse(this.cboMaskSizeAdaptive.Text);
                    break;
                }
                return mask;
            }
        }
    }
}
