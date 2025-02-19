/*''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' ======================================================================
' Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
' ======================================================================
'
'             File Name: FrequencyFilter.cs
'           Description: Contains the controls and code
'                        for Restoration->FrequencyFilter page
'         Related Files: CvipOp.cs
'                        CvipConstant.cs
'   Initial Coding Date: November 2007
'              Modified: November 2011
'       Delevoping tool: Visual Studio 2010-C#
'             Credit(s): Wenjun(Evan) Bian
'                        Patrick Solt
'                        Jhansi Lakshmi Akkineni
Hari Siva Kumar Reddy Bhogala
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
    enum FreqFilterSelection
    {
        inverse,
        geoMean,
        powerSpectEq,
        constLeastSqu,
        wiener,
        practWiener,
        paraWiener,
        notch
    }
    enum Shape : int
    {
        circle = 0,
        rectangle = 1,
        horzLine = 2,
        vertLine = 3,
        slash = 4,
        backSlash = 5
    }
    enum TransformType : int
    {
        fft = 0,
        dct = 1,
        haar = 2,
        walsh = 3,
        hadamard = 4
    }

    public partial class FrequencyFilter : UserControl
    {
        private FreqFilterSelection currentSelection;
        private double[,] currentMatrix = null;
        private List<NotchZone> lstNotches = new List<NotchZone>();

        public FrequencyFilter()
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
            int degradedImage = viewer.CVIPimage, outputImage = 0;
            int degradationFunc = 0, noiseImage = 0, origImage = 0;
            int blocksize = 0, dupImage = 0, hist = 0, xform = 0;

            switch (this.currentSelection)
            {
            case FreqFilterSelection.inverse:
                if ((degradationFunc = GetDegradationFunctionImage()) == 0)
                    break;
                if (CvipOp.GetNoOfBands_Image(degradationFunc) != viewer.Bands)
                {
                    MessageBox.Show("The bands of images are different.", "Input image error",
                        MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    CvipOp.Delete_Image(ref degradationFunc);
                    break;
                }
                outputImage = CvipOp.Inverse_Xformfilter(degradedImage, degradationFunc, this.FreqGainLimit, this.CutoffFreq);
                if (CvipOp.History_Check(outputImage, 41) == 0) //FFT
                {
                    MessageBox.Show("No FFT Transform found. Cannot perform the operation.",
                           "FFT error", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    CvipOp.Delete_Image(ref outputImage);
                    break;
                }
                hist = CvipOp.History_Get(outputImage, 41);
                blocksize = CvipOp.History_get_data(hist, 0);
                outputImage = CvipOp.Ifft_Transform(outputImage, blocksize);
                hist = CvipOp.history_create(42, 2, (float)blocksize);   //I_FFT=42
                CvipOp.History_Add(outputImage, hist);
                break;

            case FreqFilterSelection.geoMean:
                if (this.cboNoiseImage.SelectedItem as ViewerForm == null)
                {
                    MessageBox.Show("Please input noise image.", "Noise image error",
                        MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    break;
                }
                if (this.cboOriginalImage.SelectedItem as ViewerForm == null)
                {
                    MessageBox.Show("Please input Original image.", "Original image error",
                        MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    break;
                }
                if ((degradationFunc = GetDegradationFunctionImage()) == 0)
                    break;
                noiseImage = (this.cboNoiseImage.SelectedItem as ViewerForm).CVIPimage;
                origImage = (this.cboOriginalImage.SelectedItem as ViewerForm).CVIPimage;
                if ((CvipOp.GetNoOfBands_Image(degradationFunc) != viewer.Bands) ||
                    (CvipOp.GetNoOfBands_Image(noiseImage) != viewer.Bands) ||
                    (CvipOp.GetNoOfBands_Image(origImage) != viewer.Bands))
                {
                    MessageBox.Show("The bands of images are different.", "Image band error",
                        MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    CvipOp.Delete_Image(ref degradationFunc);
                    CvipOp.Delete_Image(ref noiseImage);
                    CvipOp.Delete_Image(ref origImage);
                    break;
                }
                outputImage = CvipOp.Geometric_Mean(degradedImage, degradationFunc, noiseImage, origImage, this.Gamma, this.Alpha, this.FreqGainLimit, (int)this.CutoffFreq);
                if (CvipOp.History_Check(outputImage, 41) == 0) //FFT
                {
                    MessageBox.Show("No FFT Transform found. Cannot perform the operation.",
                           "FFT error", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    CvipOp.Delete_Image(ref outputImage);
                    break;
                }
                hist = CvipOp.History_Get(outputImage, 41);
                blocksize = CvipOp.History_get_data(hist, 0);
                outputImage = CvipOp.Ifft_Transform(outputImage, blocksize);
                hist = CvipOp.history_create(42, 2, (float)blocksize);   //I_FFT=42
                CvipOp.History_Add(outputImage, hist);
                break;

            case FreqFilterSelection.powerSpectEq:
                if (this.cboNoiseImage.SelectedItem as ViewerForm == null)
                {
                    MessageBox.Show("Please input noise image.", "Noise image error",
                        MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    break;
                }
                if (this.cboOriginalImage.SelectedItem as ViewerForm == null)
                {
                    MessageBox.Show("Please input Original image.", "Original image error",
                        MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    break;
                }
                if ((degradationFunc = GetDegradationFunctionImage()) == 0)
                    break;
                noiseImage = (this.cboNoiseImage.SelectedItem as ViewerForm).CVIPimage;
                origImage = (this.cboOriginalImage.SelectedItem as ViewerForm).CVIPimage;
                if ((CvipOp.GetNoOfBands_Image(degradationFunc) != viewer.Bands) ||
                    (CvipOp.GetNoOfBands_Image(noiseImage) != viewer.Bands) ||
                    (CvipOp.GetNoOfBands_Image(origImage) != viewer.Bands))
                {
                    MessageBox.Show("The bands of images are different.", "Image band error",
                        MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    CvipOp.Delete_Image(ref degradationFunc);
                    CvipOp.Delete_Image(ref noiseImage);
                    CvipOp.Delete_Image(ref origImage);
                    break;
                }
                outputImage = CvipOp.Power_Spect_Eq(degradedImage, degradationFunc, noiseImage, origImage, this.FreqGainLimit, (int)this.CutoffFreq);
                if (CvipOp.History_Check(outputImage, 41) == 0) //FFT
                {
                    MessageBox.Show("No FFT Transform found. Cannot perform the operation.",
                           "FFT error", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    CvipOp.Delete_Image(ref outputImage);
                    break;
                }
                hist = CvipOp.History_Get(outputImage, 41);
                blocksize = CvipOp.History_get_data(hist, 0);
                outputImage = CvipOp.Ifft_Transform(outputImage, blocksize);
                hist = CvipOp.history_create(42, 2, (float)blocksize);   //I_FFT=42
                CvipOp.History_Add(outputImage, hist);
                break;

            case FreqFilterSelection.constLeastSqu:
                if ((degradationFunc = GetDegradationFunctionImage()) == 0)
                    break;
                if (CvipOp.GetNoOfBands_Image(degradationFunc) != viewer.Bands)
                {
                    MessageBox.Show("The bands of images are different.", "Image band error",
                        MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    CvipOp.Delete_Image(ref degradationFunc);
                    break;
                }
                outputImage = CvipOp.Least_Squares(degradedImage, degradationFunc, this.SmoothnessConstraintFunction, this.Gamma, this.FreqGainLimit, (int)this.CutoffFreq);
                if (CvipOp.History_Check(outputImage, 41) == 0) //FFT
                {
                    MessageBox.Show("No FFT Transform found. Cannot perform the operation.",
                           "FFT error", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    CvipOp.Delete_Image(ref outputImage);
                    break;
                }
                hist = CvipOp.History_Get(outputImage, 41);
                blocksize = CvipOp.History_get_data(hist, 0);
                outputImage = CvipOp.Ifft_Transform(outputImage, blocksize);
                hist = CvipOp.history_create(42, 2, (float)blocksize);   //I_FFT=42
                CvipOp.History_Add(outputImage, hist);
                break;

            case FreqFilterSelection.wiener:
                if (this.cboNoiseImage.SelectedItem as ViewerForm == null)
                {
                    MessageBox.Show("Please input noise image.", "Noise image error",
                        MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    break;
                }
                if (this.cboOriginalImage.SelectedItem as ViewerForm == null)
                {
                    MessageBox.Show("Please input Original image.", "Original image error",
                        MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    break;
                }
                if ((degradationFunc = GetDegradationFunctionImage()) == 0)
                    break;
                noiseImage = (this.cboNoiseImage.SelectedItem as ViewerForm).CVIPimage;
                origImage = (this.cboOriginalImage.SelectedItem as ViewerForm).CVIPimage;
                if ((CvipOp.GetNoOfBands_Image(degradationFunc) != viewer.Bands) ||
                    (CvipOp.GetNoOfBands_Image(noiseImage) != viewer.Bands) ||
                    (CvipOp.GetNoOfBands_Image(origImage) != viewer.Bands))
                {
                    MessageBox.Show("The bands of images are different.", "Image band error",
                        MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    CvipOp.Delete_Image(ref degradationFunc);
                    CvipOp.Delete_Image(ref noiseImage);
                    CvipOp.Delete_Image(ref origImage);
                    break;
                }
                outputImage = CvipOp.Wiener(degradedImage, degradationFunc, noiseImage, origImage, this.FreqGainLimit, (int)this.CutoffFreq);
                if (CvipOp.History_Check(outputImage, 41) == 0) //FFT
                {
                    MessageBox.Show("No FFT Transform found. Cannot perform the operation.",
                           "FFT error", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    CvipOp.Delete_Image(ref outputImage);
                    break;
                }
                hist = CvipOp.History_Get(outputImage, 41);
                blocksize = CvipOp.History_get_data(hist, 0);
                outputImage = CvipOp.Ifft_Transform(outputImage, blocksize);
                hist = CvipOp.history_create(42, 2, (float)blocksize);   //I_FFT=42
                CvipOp.History_Add(outputImage, hist);
                break;

            case FreqFilterSelection.practWiener:
                if ((degradationFunc = GetDegradationFunctionImage()) == 0)
                    break;
                if (CvipOp.GetNoOfBands_Image(degradationFunc) != viewer.Bands)
                {
                    MessageBox.Show("The bands of images are different.", "Input image error",
                        MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    CvipOp.Delete_Image(ref degradationFunc);
                    break;
                }
                outputImage = CvipOp.Simple_Wiener(degradedImage, degradationFunc, this.K);
                if (CvipOp.History_Check(outputImage, 41) == 0) //FFT
                {
                    MessageBox.Show("No FFT Transform found. Cannot perform the operation.",
                           "FFT error", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    CvipOp.Delete_Image(ref outputImage);
                    break;
                }
                hist = CvipOp.History_Get(outputImage, 41);
                blocksize = CvipOp.History_get_data(hist, 0);
                outputImage = CvipOp.Ifft_Transform(outputImage, blocksize);
                hist = CvipOp.history_create(42, 2, (float)blocksize);   //I_FFT=42
                CvipOp.History_Add(outputImage, hist);
                break;

            case FreqFilterSelection.paraWiener:
                if (!this.rbUseImage.Checked &&
                    (((int)this.CutoffFreq < 0) || (this.Gamma < 0)))
                {
                    MessageBox.Show("Positive integer required for the cutoff frequency and Gamma.",
                       "Input error", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    break;
                }
                if (this.cboNoiseImage.SelectedItem as ViewerForm == null)
                {
                    MessageBox.Show("Please input noise image.", "Noise image error",
                        MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    break;
                }
                if (this.cboOriginalImage.SelectedItem as ViewerForm == null)
                {
                    MessageBox.Show("Please input Original image.", "Original image error",
                        MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    break;
                }
                if ((degradationFunc = GetDegradationFunctionImage()) == 0)
                    break;
                noiseImage = (this.cboNoiseImage.SelectedItem as ViewerForm).CVIPimage;
                origImage = (this.cboOriginalImage.SelectedItem as ViewerForm).CVIPimage;
                if ((CvipOp.GetNoOfBands_Image(degradationFunc) != viewer.Bands) ||
                    (CvipOp.GetNoOfBands_Image(noiseImage) != viewer.Bands) ||
                    (CvipOp.GetNoOfBands_Image(origImage) != viewer.Bands))
                {
                    MessageBox.Show("The bands of images are different.", "Image band error",
                        MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    CvipOp.Delete_Image(ref degradationFunc);
                    CvipOp.Delete_Image(ref noiseImage);
                    CvipOp.Delete_Image(ref origImage);
                    break;
                }
                outputImage = CvipOp.Parametric_Wiener(degradedImage, degradationFunc, noiseImage, origImage, this.Gamma, this.FreqGainLimit, (int)this.CutoffFreq);
                if (CvipOp.History_Check(outputImage, 41) == 0) //FFT
                {
                    MessageBox.Show("No FFT Transform found. Cannot perform the operation.",
                           "FFT error", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    CvipOp.Delete_Image(ref outputImage);
                    break;
                }
                hist = CvipOp.History_Get(outputImage, 41);
                blocksize = CvipOp.History_get_data(hist, 0);
                outputImage = CvipOp.Ifft_Transform(outputImage, blocksize);
                hist = CvipOp.history_create(42, 2, (float)blocksize);   //I_FFT=42
                CvipOp.History_Add(outputImage, hist);
                break;

            case FreqFilterSelection.notch:
                if (this.lstNotches.Count == 0)
                {
                    MessageBox.Show("No notches are defined. Cannot perform the operation.",
                        "Notch Filter", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    break;
                }
                xform = CvipOp.Check_xform_history(degradedImage, 2);
                if (CvipOp.History_Check(degradedImage, xform) == 0)
                {
                    MessageBox.Show("Transform history information not found. Cannot perform the operation.",
                        "Transform History", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    break;
                }
                hist = CvipOp.History_Get(degradedImage, xform);
                blocksize = CvipOp.History_get_data(hist, 0);
                outputImage = CvipOp.Notch(degradedImage, this.lstNotches.ToArray());
                if ((dupImage = CvipOp.Duplicate_Image(outputImage)) != 0)
                {
                    string newImageName = viewer.Text;
                    newImageName += "_" + this.currentSelection.ToString();
                    newImageName += CvipConstant.imageNameCount++.ToString();
                    MainForm.Viewers.Add(dupImage, newImageName, LogRemap.All);
                }
                switch (xform)
                {
                case 39: // dct
                    outputImage = CvipOp.Idct_Transform(outputImage, blocksize);
                    break;
                case 41: // fft
                    outputImage = CvipOp.Ifft_Transform(outputImage, blocksize);
                    break;
                case 43: // walsh
                    outputImage = CvipOp.Walhad_Transform(outputImage, 0, blocksize);
                    break;
                case 45: // hadamard
                    outputImage = CvipOp.Walhad_Transform(outputImage, 2, blocksize);
                    break;
                case 47: // haar
                    outputImage = CvipOp.Haar_Transform(outputImage, 0, blocksize);
                    break;
                }
                break;
            }
            if (outputImage != 0)
            {
                string newImageName = viewer.Text;
                newImageName += "_" + CvipFunctionNames.getFncName(this.currentSelection.ToString());
                newImageName += CvipConstant.imageNameCount++.ToString();
                MainForm.Viewers.Add(outputImage, newImageName);
            }
            // enable Apply button
            this.btnApply.Enabled = true;
            this.Cursor = Cursors.Default;
        }
        private void btnCancel_Click(object sender, EventArgs e)
        {
            MainForm.RestorationForm.Close();
        }
        private void btnEditMask_Click(object sender, EventArgs e)
        {
            double[,] dflt = this.DefaultMatrix;
            if (dflt == null)
                return;

            FrequencyFilterMask mask = new FrequencyFilterMask(dflt, this.currentMatrix);
            if (mask.ShowDialog() == DialogResult.OK)
                this.currentMatrix = mask.CurrentValues;
        }
        private void btnHelp_Click(object sender, EventArgs e)
        {
            MainForm.ShowHelp();
        }
        private void btnNotchAdd_Click(object sender, EventArgs e)
        {
            this.lstNotches.Add(new NotchZone(this.NotchRow, this.NotchCol, this.NotchSize));
            this.cboPoint.Items.Insert(this.cboPoint.Items.Count - 1, this.cboPoint.Items.Count);
            this.cboPoint.SelectedIndex = this.cboPoint.Items.Count - 2;
            this.btnAddNotch.Enabled = false;
        }
        private void btnNotchRedo_Click(object sender, EventArgs e)
        {
            ResetNotch();
        }
        private void btnReset_Click(object sender, EventArgs e)
        {
            ResetControls();
        }
        private void cboBlurParameter_Changed(object sender, EventArgs e)
        {
            this.currentMatrix = null;
        }
        private void cboBlurShape_SelectedIndexChanged(object sender, EventArgs e)
        {
            switch (this.BlurShape)
            {
            case Shape.circle:
                //this.lblShapeWidth.Text = "Diameter:";
                //this.lblShapeWidth.Visible = true;
                //this.cboShapeWidth.Visible = true;
                //this.lblShapeHeight.Visible = false;
                //this.cboShapeHeight.Visible = false;
                //this.ShapeWidth = Math.Min(this.MaskHeight, this.MaskWidth);
                break;
            case Shape.rectangle:
                //this.lblShapeWidth.Text = "Width:";
                //this.lblShapeWidth.Visible = true;
                //this.cboShapeWidth.Visible = true;
                //this.lblShapeHeight.Visible = true;
                //this.cboShapeHeight.Visible = true;
                //this.ShapeHeight = this.MaskHeight;
                //this.ShapeWidth = this.MaskWidth;
                break;
            default:
                //this.lblShapeWidth.Visible = false;
                //this.cboShapeWidth.Visible = false;
                //this.lblShapeHeight.Visible = false;
                //this.cboShapeHeight.Visible = false;
                break;
            }
            this.currentMatrix = null;
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
        private void cboImage_MouseEnter(object sender, EventArgs e)
        {
            Control ctrl = sender as Control;
            toolTipImageCombo.SetToolTip(ctrl, ctrl.Text);
        }

        private void cboImage_SelectedIndexChanged(object sender, EventArgs e)
        {
            ComboBox cbo = sender as ComboBox;
            ViewerForm selected = cbo.SelectedItem as ViewerForm;
            if (selected != null) selected.Activate();
        }
        private void cboIntVal_Validating(object sender, CancelEventArgs e)
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
        }
        private void cboLimitGain_Validating(object sender, CancelEventArgs e)
        {
            if (this.cboLimitGain.SelectedIndex != 0)
            {
                int val;
                if (!int.TryParse(this.cboLimitGain.Text, out val))
                {
                    MessageBox.Show("Please check the input value. Only integers are accepted.",
                       "Integer Required", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    this.cboLimitGain.SelectAll();
                    e.Cancel = true;
                }
            }
        }
        private void cboMaskSize_Validated(object sender, EventArgs e)
        {
            if ((sender as ComboBox).Tag == null) // only run if this is response to user selection
            {
                //if (this.BlurShape == Shape.circle)
                //{
                //    int maxrad = Math.Min(this.MaskHeight, this.MaskWidth);
                //    if (this.ShapeWidth > maxrad)
                //        this.ShapeWidth = maxrad;
                //}
                //else if (this.BlurShape == Shape.rectangle)
                //{
                //    if (this.ShapeHeight > this.MaskHeight)
                //        this.ShapeHeight = this.MaskHeight;
                //    if (this.ShapeWidth > this.MaskWidth)
                //        this.ShapeWidth = this.MaskWidth;
                //}
            }
            this.currentMatrix = null;
        }
        private void cboMaskSize_Validating(object sender, CancelEventArgs e)
        {
            ComboBox cbo = sender as ComboBox;
            int val;
            if (!int.TryParse(cbo.Text, out val) || (val < 3) || (val > 31))
            {
                MessageBox.Show("Please check the input value. Mask size should be an integer between 3 and 31.",
                   "Unsupported Mask Size", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                cbo.SelectAll();
                e.Cancel = true;
            }
        }
        private void cboNotchVal_Validated(object sender, EventArgs e)
        {
            if ((this.cboPoint.SelectedIndex >= 0) &&
                (this.cboPoint.SelectedIndex < this.cboPoint.Items.Count - 1))
            {
                NotchZone nz = this.lstNotches[this.cboPoint.SelectedIndex];
                nz.Col = this.NotchCol;
                nz.Row = this.NotchRow;
                nz.Radius = this.NotchSize;
                this.lstNotches[this.cboPoint.SelectedIndex] = nz;
            }
        }
        private void cboPoint_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (this.cboPoint.SelectedIndex < this.cboPoint.Items.Count - 1)
            {
                this.NotchCol = this.lstNotches[this.cboPoint.SelectedIndex].Col;
                this.NotchRow = this.lstNotches[this.cboPoint.SelectedIndex].Row;
                this.NotchSize = this.lstNotches[this.cboPoint.SelectedIndex].Radius;
            }
            else
                this.btnAddNotch.Enabled = true;
        }
        private void cboShapeSize_Validated(object sender, EventArgs e)
        {
            if ((sender as ComboBox).Tag == null) // only run if this is response to user selection
            {
                if (this.BlurShape == Shape.circle)
                {
                    //if (this.MaskHeight < this.ShapeWidth)
                    //    this.MaskHeight = this.ShapeWidth;
                    //if (this.MaskWidth < this.ShapeWidth)
                    //    this.MaskWidth = this.ShapeWidth;
                }
                else if (this.BlurShape == Shape.rectangle)
                {
                    //if (this.MaskHeight < this.ShapeHeight)
                    //    this.MaskHeight = this.ShapeHeight;
                    //if (this.MaskWidth < this.ShapeWidth)
                    //    this.MaskWidth = this.ShapeWidth;
                }
            }
            this.currentMatrix = null;
        }
        private void cboTransformType_SelectedIndexChanged(object sender, EventArgs e)
        {
            this.lstNotches.Clear();
            object newitem = this.cboPoint.Items[this.cboPoint.Items.Count - 1];
            this.cboPoint.Items.Clear();
            this.cboPoint.Items.Add(newitem);
            this.cboPoint.SelectedIndex = 0;
            this.NotchCol = 0;
            this.NotchRow = 0;
            this.NotchSize = 10;

            ViewerForm viewer = MainForm.Viewers.SelectedViewer;
            if (viewer == null)
                return;
            if (this.cboTransformType.SelectedIndex >= 0)
            {
                int inputImage = viewer.CVIPimage, outputImage = 0;
                int minedge = Math.Min(viewer.ImageWidth, viewer.ImageHeight);
                int blocksize = 1, hist = 0;
                while (blocksize < minedge)
                    blocksize *= 2;
                if (blocksize > minedge)
                    blocksize /= 2;

                switch (this.TransformType)
                {
                case TransformType.fft:
                    outputImage = CvipOp.Fft_Transform(inputImage, blocksize);
                    hist = CvipOp.history_create(41, 2, (float)blocksize);
                    CvipOp.History_Add(outputImage, hist);
                    break;
                case TransformType.dct:
                    outputImage = CvipOp.Dct_Transform(inputImage, blocksize);
                    hist = CvipOp.history_create(39, 2, (float)blocksize);
                    CvipOp.History_Add(outputImage, hist);
                    break;
                case TransformType.haar:
                    outputImage = CvipOp.Haar_Transform(inputImage, 1, blocksize);
                    hist = CvipOp.history_create(47, 2, (float)blocksize);
                    CvipOp.History_Add(outputImage, hist);
                    break;
                case TransformType.walsh:
                    outputImage = CvipOp.Walhad_Transform(inputImage, 1, blocksize);
                    hist = CvipOp.history_create(43, 2, (float)blocksize);
                    CvipOp.History_Add(outputImage, hist);
                    break;
                case TransformType.hadamard:
                    outputImage = CvipOp.Walhad_Transform(inputImage, 3, blocksize);
                    hist = CvipOp.history_create(45, 2, (float)blocksize);
                    CvipOp.History_Add(outputImage, hist);
                    break;
                }
                if (outputImage != 0)
                {
                    string newImageName = viewer.Text;
                    newImageName += "_" + this.TransformType.ToString();
                    newImageName += CvipConstant.imageNameCount++.ToString();
                    MainForm.Viewers.Add(outputImage, newImageName, LogRemap.All);
                }
            }
        }
        private int GetDegradationFunctionImage()
        {
            int degradation = 0;
            if (this.rbUseImage.Checked)
            {
                ViewerForm viewer = this.cboDegradationImage.SelectedItem as ViewerForm;
                if (viewer == null)
                {
                    MessageBox.Show("Please choose the degradation function image.",
                        "Degradation Function Image Error",
                        MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    return 0;
                }
                degradation = viewer.CVIPimage;
            }
            else if (this.currentMatrix == null)
            {
                degradation = this.BlurImage;
            }
            else
            {
                degradation = CvipOp.Create_Mask(this.currentMatrix);
            }
            int bands = CvipOp.GetNoOfBands_Image(degradation);
            if ((bands == 1) && (MainForm.Viewers.SelectedViewer.Bands == 3))
            {
                int[] tmpArray = new int[3];
                tmpArray[0] = degradation;
                tmpArray[1] = degradation;
                tmpArray[2] = degradation;
                degradation = CvipOp.Assemble_Bands(tmpArray);
            }
            return degradation;
        }
        protected override void OnLoad(EventArgs e)
        {
            base.OnLoad(e);

            this.rbInverse.Tag = FreqFilterSelection.inverse;
            this.rbGeometricMean.Tag = FreqFilterSelection.geoMean;
            this.rbPowerSpectrumEQ.Tag = FreqFilterSelection.powerSpectEq;
            this.rbConstrLeastSqu.Tag = FreqFilterSelection.constLeastSqu;
            this.rbWiener.Tag = FreqFilterSelection.wiener;
            this.rbPractWiener.Tag = FreqFilterSelection.practWiener;
            this.rbParaWiener.Tag = FreqFilterSelection.paraWiener;
            this.rbNotch.Tag = FreqFilterSelection.notch;

            ResetControls();
        }
        private void OnSelectedViewerChanged(ViewerForm viewer)
        {
            this.txtDegradedImage.Text = "";
            if (viewer != null)
                this.txtDegradedImage.Text = viewer.Text;
        }
        private void OnViewerCollectionChanged()
        {
            if (MainForm.Viewers != null)
            {
                ViewerForm degraded = this.cboDegradationImage.SelectedItem as ViewerForm;
                ViewerForm noise = this.cboNoiseImage.SelectedItem as ViewerForm;
                ViewerForm orig = this.cboOriginalImage.SelectedItem as ViewerForm;

                if (degraded == null) degraded = MainForm.Viewers.SelectedViewer;
                if (noise == null) noise = MainForm.Viewers.SelectedViewer;
                if (orig == null) orig = MainForm.Viewers.SelectedViewer;

                this.cboDegradationImage.Items.Clear();
                this.cboNoiseImage.Items.Clear();
                this.cboOriginalImage.Items.Clear();

                foreach (ViewerForm viewer in MainForm.Viewers)
                {
                    this.cboDegradationImage.Items.Add(viewer);
                    this.cboNoiseImage.Items.Add(viewer);
                    this.cboOriginalImage.Items.Add(viewer);
                }
                this.cboDegradationImage.SelectedItem = degraded;
                this.cboNoiseImage.SelectedItem = noise;
                this.cboOriginalImage.SelectedItem = orig;
            }
        }
        private void OnViewerMouseClick(Point pos, ViewerForm viewer)
        {
            this.cboPoint.SelectedIndex = this.cboPoint.Items.Count - 1;
            this.NotchCol = pos.X;
            this.NotchRow = pos.Y;
            this.btnAddNotch.Enabled = true;
        }
        private void rbDegradationFunction_Click(object sender, EventArgs e)
        {
            this.cboDegradationImage.Visible = this.rbUseImage.Checked;
            this.grpBlurMask.Visible = !this.rbUseImage.Checked;
        }
        private void rbFreqFilter_Click(object sender, EventArgs e)
        {
            RadioButton rb = sender as RadioButton;
            if ((rb != null) && rb.Checked && (rb.Tag != null))
            {
                this.currentSelection = (FreqFilterSelection)rb.Tag;
                UpdateControls();
            }
        }
        private void ResetControls()
        {
            // Blur Mask Panel
            this.cboMaskWidth.Text = "9";
            this.cboMaskHeight.Text = "9";
            this.cboBlurShape.SelectedIndex = 1;
            //this.cboShapeWidth.Text = "7";
            //this.cboShapeHeight.Text = "7";
            this.cboBlurMethod.SelectedIndex = 2;
            this.cboBlurWeight.Text = "1.0";

            // Degradation Function Group
            this.cboCutoffFreq.Text = "32";
            this.cboLimitGain.Text = "100";
            this.rbSpecifyFunc.PerformClick();

            // Parameters Group
            this.cboGamma.Text = "0.5";
            this.cboSmoothFunc.SelectedIndex = 0;
            this.cboAlpha.Text = "0.0";
            this.cboK.Text = "1.0";

            // Notch Filter Group
            ResetNotch();

            // Default current selection
            this.rbInverse.PerformClick();

            // enable Apply button
            this.btnApply.Enabled = true;
            this.Cursor = Cursors.Default;
        }
        private void ResetNotch()
        {
            this.lstNotches.Clear();
            object newitem = this.cboPoint.Items[this.cboPoint.Items.Count - 1];
            this.cboPoint.Items.Clear();
            this.cboPoint.Items.Add(newitem);
            this.cboPoint.SelectedIndex = 0;
            this.NotchCol = 0;
            this.NotchRow = 0;
            this.NotchSize = 10;
            this.cboTransformType.SelectedIndex = -1;
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
            case FreqFilterSelection.inverse:
                this.lblWienerCoefficient.Text = "Alpha=0, Gamma=0";
                this.lblWienerCoefficient.Visible = true;
                this.picWienerCoefficient.Visible = false;
                this.pnlDegradationFunction.Visible = true;
                this.lblCutoffFreq.Visible = true;
                this.cboCutoffFreq.Visible = true;
                this.lblLimitGain1.Visible = true;
                this.lblLimitGain2.Visible = true;
                this.cboLimitGain.Visible = true;
                this.pnlParameters.Visible = false;
                this.pnlNotch.Visible = false;
                break;

            case FreqFilterSelection.geoMean:
                this.lblWienerCoefficient.Visible = false;
                this.picWienerCoefficient.Visible = false;
                this.pnlDegradationFunction.Visible = true;
                this.lblCutoffFreq.Visible = true;
                this.cboCutoffFreq.Visible = true;
                this.lblLimitGain1.Visible = true;
                this.lblLimitGain2.Visible = true;
                this.cboLimitGain.Visible = true;
                this.pnlParameters.Visible = true;
                this.lblNoiseImage.Visible = true;
                this.cboNoiseImage.Visible = true;
                this.lblOriginalImage.Visible = true;
                this.cboOriginalImage.Visible = true;
                this.lblGamma.Visible = true;
                this.cboGamma.Visible = true;
                this.lblSmoothFunc.Visible = false;
                this.cboSmoothFunc.Visible = false;
                this.lblAlpha.Visible = true;
                this.cboAlpha.Visible = true;
                this.lblK.Visible = false;
                this.cboK.Visible = false;
                this.pnlNotch.Visible = false;
                break;

            case FreqFilterSelection.powerSpectEq:
                this.lblWienerCoefficient.Text = "Alpha=0.5, Gamma=1";
                this.lblWienerCoefficient.Visible = true;
                this.picWienerCoefficient.Visible = false;
                this.pnlDegradationFunction.Visible = true;
                this.lblCutoffFreq.Visible = true;
                this.cboCutoffFreq.Visible = true;
                this.lblLimitGain1.Visible = true;
                this.lblLimitGain2.Visible = true;
                this.cboLimitGain.Visible = true;
                this.pnlParameters.Visible = true;
                this.lblNoiseImage.Visible = true;
                this.cboNoiseImage.Visible = true;
                this.lblOriginalImage.Visible = true;
                this.cboOriginalImage.Visible = true;
                this.lblGamma.Visible = false;
                this.cboGamma.Visible = false;
                this.lblSmoothFunc.Visible = false;
                this.cboSmoothFunc.Visible = false;
                this.lblAlpha.Visible = false;
                this.cboAlpha.Visible = false;
                this.lblK.Visible = false;
                this.cboK.Visible = false;
                this.pnlNotch.Visible = false;
                break;

            case FreqFilterSelection.constLeastSqu:
                this.lblWienerCoefficient.Text = "Alpha=0";
                this.lblWienerCoefficient.Visible = true;
                this.picWienerCoefficient.Visible = false;
                this.pnlDegradationFunction.Visible = true;
                this.lblCutoffFreq.Visible = true;
                this.cboCutoffFreq.Visible = true;
                this.lblLimitGain1.Visible = true;
                this.lblLimitGain2.Visible = true;
                this.cboLimitGain.Visible = true;
                this.pnlParameters.Visible = true;
                this.lblNoiseImage.Visible = false;
                this.cboNoiseImage.Visible = false;
                this.lblOriginalImage.Visible = false;
                this.cboOriginalImage.Visible = false;
                this.lblGamma.Visible = true;
                this.cboGamma.Visible = true;
                this.lblSmoothFunc.Visible = true;
                this.cboSmoothFunc.Visible = true;
                this.lblAlpha.Visible = false;
                this.cboAlpha.Visible = false;
                this.lblK.Visible = false;
                this.cboK.Visible = false;
                this.pnlNotch.Visible = false;
                break;

            case FreqFilterSelection.wiener:
                this.lblWienerCoefficient.Text = "Alpha=0, Gamma=1";
                this.lblWienerCoefficient.Visible = true;
                this.picWienerCoefficient.Visible = false;
                this.pnlDegradationFunction.Visible = true;
                this.lblCutoffFreq.Visible = true;
                this.cboCutoffFreq.Visible = true;
                this.lblLimitGain1.Visible = true;
                this.lblLimitGain2.Visible = true;
                this.cboLimitGain.Visible = true;
                this.pnlParameters.Visible = true;
                this.lblNoiseImage.Visible = true;
                this.cboNoiseImage.Visible = true;
                this.lblOriginalImage.Visible = true;
                this.cboOriginalImage.Visible = true;
                this.lblGamma.Visible = false;
                this.cboGamma.Visible = false;
                this.lblSmoothFunc.Visible = false;
                this.cboSmoothFunc.Visible = false;
                this.lblAlpha.Visible = false;
                this.cboAlpha.Visible = false;
                this.lblK.Visible = false;
                this.cboK.Visible = false;
                this.pnlNotch.Visible = false;
                break;

            case FreqFilterSelection.practWiener:
                this.lblWienerCoefficient.Text = "Alpha=0,   K=";
                this.lblWienerCoefficient.Visible = true;
                this.picWienerCoefficient.Visible = true;
                this.pnlDegradationFunction.Visible = true;
                this.lblCutoffFreq.Visible = false;
                this.cboCutoffFreq.Visible = false;
                this.lblLimitGain1.Visible = false;
                this.lblLimitGain2.Visible = false;
                this.cboLimitGain.Visible = false;
                this.pnlParameters.Visible = true;
                this.lblNoiseImage.Visible = false;
                this.cboNoiseImage.Visible = false;
                this.lblOriginalImage.Visible = false;
                this.cboOriginalImage.Visible = false;
                this.lblGamma.Visible = false;
                this.cboGamma.Visible = false;
                this.lblSmoothFunc.Visible = false;
                this.cboSmoothFunc.Visible = false;
                this.lblAlpha.Visible = false;
                this.cboAlpha.Visible = false;
                this.lblK.Visible = true;
                this.cboK.Visible = true;
                this.pnlNotch.Visible = false;
                break;

            case FreqFilterSelection.paraWiener:
                this.lblWienerCoefficient.Text = "Alpha=0";
                this.lblWienerCoefficient.Visible = true;
                this.picWienerCoefficient.Visible = false;
                this.pnlDegradationFunction.Visible = true;
                this.lblCutoffFreq.Visible = true;
                this.cboCutoffFreq.Visible = true;
                this.lblLimitGain1.Visible = true;
                this.lblLimitGain2.Visible = true;
                this.cboLimitGain.Visible = true;
                this.pnlParameters.Visible = true;
                this.lblNoiseImage.Visible = true;
                this.cboNoiseImage.Visible = true;
                this.lblOriginalImage.Visible = true;
                this.cboOriginalImage.Visible = true;
                this.lblGamma.Visible = true;
                this.cboGamma.Visible = true;
                this.lblSmoothFunc.Visible = false;
                this.cboSmoothFunc.Visible = false;
                this.lblAlpha.Visible = false;
                this.cboAlpha.Visible = false;
                this.lblK.Visible = false;
                this.cboK.Visible = false;
                this.pnlNotch.Visible = false;
                break;

            case FreqFilterSelection.notch:
                this.lblWienerCoefficient.Visible = false;
                this.picWienerCoefficient.Visible = false;
                this.pnlDegradationFunction.Visible = false;
                this.pnlParameters.Visible = false;
                this.pnlNotch.Visible = true;
                break;
            }
            // enable Apply button
            this.btnApply.Enabled = true;
            this.Cursor = Cursors.Default;
        }
        protected override void WndProc(ref Message m)
        {
            base.WndProc(ref m);
            if (MainForm.Viewers != null)
            {
                switch ((WM)m.Msg)
                {
                case WM.CREATE:
                    MainForm.Viewers.SelectedViewerChanged += this.OnSelectedViewerChanged;
                    MainForm.Viewers.ViewerCollectionChanged += this.OnViewerCollectionChanged;
                    ViewerForm.MouseClicked += this.OnViewerMouseClick;
                    OnViewerCollectionChanged();
                    break;

                case WM.DESTROY:
                    MainForm.Viewers.SelectedViewerChanged -= this.OnSelectedViewerChanged;
                    MainForm.Viewers.ViewerCollectionChanged -= this.OnViewerCollectionChanged;
                    ViewerForm.MouseClicked -= this.OnViewerMouseClick;
                    break;
                }
            }
        }

        private double Alpha { get { return double.Parse(this.cboAlpha.Text); } }
        private double CutoffFreq { get { return double.Parse(this.cboCutoffFreq.Text); } }
        private double Gamma { get { return double.Parse(this.cboGamma.Text); } }
        private double K { get { return double.Parse(this.cboK.Text); } }
        private float BlurWeight { get { return float.Parse(this.cboBlurWeight.Text); } }
        private int BlurMethod { get { return this.cboBlurMethod.SelectedIndex + 1; } }
        private Shape BlurShape { get { return (Shape)this.cboBlurShape.SelectedIndex; } }
        private TransformType TransformType { get { return (TransformType)this.cboTransformType.SelectedIndex; } }

        private double[,] DefaultMatrix
        {
            get
            {
                int blur = this.BlurImage;
                double[] pixelVal = null;
                double[,] matrix = new double[this.MaskHeight, this.MaskWidth];

                for (int i = 0; i < this.MaskHeight; i++)
                {
                    for (int j = 0; j < this.MaskWidth; j++)
                    {
                        pixelVal = (double[])CvipOp.GetPixel_Image(blur, i, j);
                        matrix[i, j] = pixelVal[0];
                    }
                }
                return matrix;
            }
        }
        private int BlurImage
        {
            get
            {
                int blur = 0, mask = 0;
                switch (this.BlurShape)
                {
                case Shape.circle:
                    mask = CvipOp.Create_Circle(this.MaskWidth, this.MaskHeight, this.MaskWidth / 2, this.MaskHeight / 2, this.MaskWidth / 2 );//this.ShapeWidth / 2);
                    break;
                case Shape.rectangle:
                    mask = CvipOp.Create_Rectangle(this.MaskWidth, this.MaskHeight, 0, 0, this.MaskWidth, this.MaskHeight);
                        //(this.MaskWidth - this.ShapeWidth) / 2, (this.MaskHeight - this.ShapeHeight) / 2, this.ShapeWidth, this.ShapeHeight);
                    break;
                case Shape.horzLine:
                    mask = CvipOp.Create_Line(this.MaskWidth, this.MaskHeight, 0, this.MaskHeight / 2, this.MaskWidth - 1, this.MaskHeight / 2);
                    break;
                case Shape.vertLine:
                    mask = CvipOp.Create_Line(this.MaskWidth, this.MaskHeight, this.MaskWidth / 2, 0, this.MaskWidth / 2, this.MaskHeight - 1);
                    break;
                case Shape.slash:
                    mask = CvipOp.Create_Line(this.MaskWidth, this.MaskHeight, 0, this.MaskHeight - 1, this.MaskWidth - 1, 0);
                    break;
                case Shape.backSlash:
                    mask = CvipOp.Create_Line(this.MaskWidth, this.MaskHeight, 0, 0, this.MaskWidth - 1, this.MaskHeight - 1);
                    break;
                }
                mask = CvipOp.Gray_Multiply2(mask, 0.003922f);
                blur = CvipOp.H_image(this.BlurMethod, this.MaskHeight, this.MaskWidth);
                mask = CvipOp.Multiply_Image(mask, blur);
                mask = CvipOp.Gray_Multiply2(mask, this.BlurWeight);
                return mask;
            }
        }
        private int FreqGainLimit
        {
            get
            {
                int val = 0;
                if (this.cboLimitGain.SelectedIndex != 0)
                    val = int.Parse(this.cboLimitGain.Text);
                return val;
            }
        }
        private int MaskHeight
        {
            get { return int.Parse(this.cboMaskHeight.Text); }
            set
            {
                // set .Tag to flag that this value is being set by code, not user.
                this.cboMaskHeight.Tag = true;
                this.cboMaskHeight.Text = value.ToString();
                this.cboMaskHeight.Tag = null;
            }
        }
        private int MaskWidth
        {
            get { return int.Parse(this.cboMaskWidth.Text); }
            set
            {
                // set .Tag to flag that this value is being set by code, not user.
                this.cboMaskWidth.Tag = true;
                this.cboMaskWidth.Text = value.ToString();
                this.cboMaskWidth.Tag = null;
            }
        }
        private int NotchCol
        {
            get { return int.Parse(this.txtNotchCol.Text); }
            set { this.txtNotchCol.Text = value.ToString(); }
        }
        private int NotchRow
        {
            get { return int.Parse(this.txtNotchRow.Text); }
            set { this.txtNotchRow.Text = value.ToString(); }
        }
        private int NotchSize
        {
            get { return int.Parse(this.cboNotchSize.Text); }
            set { this.cboNotchSize.Text = value.ToString(); }
        }
        //private int ShapeHeight
        //{
        //    get { return int.Parse(this.cboShapeHeight.Text); }
        //    set
        //    {
        //        // set .Tag to flag that this value is being set by code, not user.
        //        this.cboShapeHeight.Tag = true;
        //        this.cboShapeHeight.Text = value.ToString();
        //        this.cboShapeHeight.Tag = null;
        //    }
        //}
        //private int ShapeWidth
        //{
        //    get { return int.Parse(this.cboShapeWidth.Text); }
        //    set
        //    {
        //        // set .Tag to flag that this value is being set by code, not user.
        //        this.cboShapeWidth.Tag = true;
        //        this.cboShapeWidth.Text = value.ToString();
        //        this.cboShapeWidth.Tag = null;
        //    }
        //}
        private int SmoothnessConstraintFunction
        {
            get
            {
                double[,] mask = new double[3, 3];
                switch (this.cboSmoothFunc.SelectedIndex)
                {
                case 0:
                    mask[0, 0] = 0; mask[0, 1] = -1; mask[0, 2] = 0;
                    mask[1, 0] = -1; mask[1, 1] = 4; mask[1, 2] = -1;
                    mask[2, 0] = 0; mask[2, 1] = -1; mask[2, 2] = 0;
                    break;
                case 1:
                    mask[0, 0] = 1; mask[0, 1] = -2; mask[0, 2] = 1;
                    mask[1, 0] = -2; mask[1, 1] = 4; mask[1, 2] = -2;
                    mask[2, 0] = 1; mask[2, 1] = -2; mask[2, 2] = 1;
                    break;
                case 2:
                    mask[0, 0] = -1; mask[0, 1] = -1; mask[0, 2] = -1;
                    mask[1, 0] = -1; mask[1, 1] = 8; mask[1, 2] = -1;
                    mask[2, 0] = -1; mask[2, 1] = -1; mask[2, 2] = -1;
                    break;
                case 3:
                    mask[0, 0] = -2; mask[0, 1] = 1; mask[0, 2] = -2;
                    mask[1, 0] = 1; mask[1, 1] = 4; mask[1, 2] = 1;
                    mask[2, 0] = -2; mask[2, 1] = 1; mask[2, 2] = -2;
                    break;
                }
                int smoothImage = CvipOp.Create_Mask(mask);
                if (MainForm.Viewers.SelectedViewer.Bands == 3)
                {
                    int[] tmpArray = new int[3];
                    tmpArray[0] = smoothImage;
                    tmpArray[1] = smoothImage;
                    tmpArray[2] = smoothImage;
                    smoothImage = CvipOp.Assemble_Bands(tmpArray);
                }
                return smoothImage;
            }
        }

        private void rbInverse_CheckedChanged(object sender, EventArgs e)
        {

        }

        private void cboK_SelectedIndexChanged(object sender, EventArgs e)
        {

        }
    }
}
