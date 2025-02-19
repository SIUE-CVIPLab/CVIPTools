/*''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' ======================================================================
' Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
' ======================================================================
'
'             File Name: Segmentation.cs
'           Description: Contains the controls and code
'                        for Analysis->Segmentation page
'         Related Files: CvipOp.cs
'                        CvipConstant.cs
'   Initial Coding Date: April 2007
'              Modified: March 2013
'       Delevoping tool: Visual Studio 2010-C#
'             Credit(s): Wenjun(Evan) Bian
'                        Patrick Solt
'                        Mounika Mamidi
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

namespace CVIPGUI.Analysis
{
    public enum SegmentationSelection
    {
        median, 
        Kuwahara, 
        Anisotrophic,
        superPixel,
        grayQuant,
        autoThreshold,
        otsu,
        histThreshold,
        fuzzyc,
        medCut,
        pctMed,
        sct,
        multiRes,
        splitMerge,
        watershed,
        //gvfSnake,
        morphD,
        morphE,
        morphO,
        morphC,
        morphI,
        morphHit,
        morphThin,
        morphSkel
    }
    public partial class Segmentation : UserControl
    {
        private SegmentationSelection currentSelection = SegmentationSelection.grayQuant;
        private MorphologicalMaskForm filterMask = null;
        private MorphGrid morphGrid = null;

        public Segmentation()
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
                case SegmentationSelection.median:
                    if (this.rbStandard.Checked){
                        if (this.maskSizeMedian > 31)
                        {
                            MessageBox.Show("Currently the maximum mask size is limited to 31.",
                                   "Range error!", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                            break;
                        }
                        outputImage = CvipOp.Median_Filter(inputImage, this.maskSizeMedian); 
                    } else
                    {
                        if (this.maskSizeMedian > 11)
                        {
                            MessageBox.Show("Currently the maximum mask size is limited to 11.",
                                    "Range error!", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                            break;
                        }
                        outputImage = CvipOp.Adapt_Median_Filter(inputImage, this.maskSizeMedian); 
                    }
                    break;
                case SegmentationSelection.Kuwahara:
                    if (this.maskSizeMedian < 3)
                    {
                        MessageBox.Show("The mask size should be equal or greater than 3.",
                            "Range error!", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                        break;
                    }
                    else if (this.maskSizeMedian > 128)
                    {
                        MessageBox.Show("Currently the maximum mask size is limited to 128.",
                            "Range error!", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                        break;
                    }
                    outputImage = CvipOp.Kuwahara_Filter(inputImage, this.maskSizeMedian);
                    
                    break;
                case SegmentationSelection.Anisotrophic:
                    
                    if (this.rbStandard.Checked)
                    {
                        outputImage = CvipOp.AD_Filter(inputImage, this.Iterations, this.SmoothPerIter, this.EdgeThreshold);
                        break;
                    }
                    
                    if (this.rbParametric.Checked)
                    {
                        outputImage = CvipOp.Param_AD_Filter(inputImage, this.Iterations, this.SmoothPerIter, this.EdgeThreshold, this.BlockSize);
                        break;
                    }
                    
                    break;
                case SegmentationSelection.superPixel:
                    
                        outputImage = CvipOp.superPixel(inputImage);
                        
                    

                    break; 
                case SegmentationSelection.grayQuant:
                    if (this.cboQuantMethod.SelectedIndex == 0) // Standard
                        outputImage = CvipOp.Gray_Quant_Segment(inputImage, this.NumGrayLevels);
                    else
                        outputImage = CvipOp.Igs_Segment(inputImage, this.NumGrayLevels);
                    break;

                case SegmentationSelection.autoThreshold:
                    outputImage = CvipOp.Auto_Threshold_Segment(inputImage, this.AutoThreshLimit);
                    break;

                case SegmentationSelection.otsu:
                    outputImage = CvipOp.Otsu_Segment(inputImage);
                    break;

                case SegmentationSelection.histThreshold:
                    int tempImage = 0;
                    if (HistThreshTore < 0.2)
                    {
                        MessageBox.Show("The standard deviation must be greater than 0.2.",
                            "Invalid StdDev", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                        break;
                    }
                    if (viewer.Bands == 3)
                    {
                        if (rbHistThreshBands.Checked == true)
                        {
                            int[] eb = { 0, 0, 0 };
                            eb[0] = CvipOp.Extract_Band(inputImage, 1);
                            eb[1] = CvipOp.Extract_Band(inputImage, 2);
                            eb[2] = CvipOp.Extract_Band(inputImage, 3);
                            eb[0] = CvipOp.Hist_Thresh_Gray(eb[0], HistThreshTore);
                            eb[1] = CvipOp.Hist_Thresh_Gray(eb[1], HistThreshTore);
                            eb[2] = CvipOp.Hist_Thresh_Gray(eb[2], HistThreshTore);
                            outputImage = CvipOp.Assemble_Bands(eb);
                            CvipOp.Delete_Image(ref eb[0]);
                            CvipOp.Delete_Image(ref eb[1]);
                            CvipOp.Delete_Image(ref eb[2]);
                        }
                        else if(rbHistThreshPCT.Checked == true)
                        {
                            outputImage = CvipOp.Hist_Thresh_Segment(inputImage, HistThreshTore);
                        }
                        else
                        {
                            tempImage = CvipOp.Luminance_Image(inputImage);
                            outputImage = CvipOp.Hist_Thresh_Gray(tempImage, HistThreshTore);
                        }
                    }
                    else
                    {
                        outputImage = CvipOp.Hist_Thresh_Gray(inputImage, HistThreshTore);
                    }
                    break;

                case SegmentationSelection.fuzzyc:
                    outputImage = CvipOp.Fuzzyc_Segment(inputImage, this.Variance);
                    break;

                case SegmentationSelection.medCut:
                    outputImage = CvipOp.Median_Cut_Segment(inputImage, this.NumColors, 0, 0, 0, 0);
                    break;

                case SegmentationSelection.pctMed:
                    outputImage = CvipOp.Pct_Median_Segment(CvipOp.Remap_Image(inputImage, 0, 0, 255), this.NumColors);
                    break;

                case SegmentationSelection.sct:
                    outputImage = CvipOp.Sct_Split_Segment(CvipOp.Remap_Image(inputImage, 0, 0, 255), this.NumColorsAAxis, this.NumColorsBAxis);
                    break;

                case SegmentationSelection.multiRes:
                    outputImage = CvipOp.Multi_Resolution_Segment(inputImage, this.HomogeneityTest, this.Param1, this.Param2, this.RunPCT);
                    break;

                case SegmentationSelection.splitMerge:
                    outputImage = CvipOp.Split_Merge_Segment(inputImage, this.EntryLevel, this.HomogeneityTest, this.Param1, this.Param2, this.RunPCT);
                    break;

                case SegmentationSelection.watershed:
                    outputImage = CvipOp.Watershed_Segment(inputImage, this.MergeResult, this.WatershedThreshold);
                    break;

                //case SegmentationSelection.gvfSnake:
                //    if (viewer.SelectionState == SelectionState.Idle)
                //    {
                //        MessageBox.Show("Please draw an initial snake by holding CTRL button!", "No initial snake!",
                //        MessageBoxButtons.OK, MessageBoxIcon.Warning);
                //        break;
                //    }
                //    if (viewer.SelectionState != SelectionState.BorderSelected)
                //    {
                //        MessageBox.Show("Please draw the initial snake using CTRL button!", "Incompatible initial snake!",
                //        MessageBoxButtons.OK, MessageBoxIcon.Warning);
                //        break;
                //    }
                //    outputImage = CvipOp.GVFSnake_Segment(inputImage, viewer.SelectedArea, this.NumIterations, this.Alpha, this.Beta, this.Kappa);
                //    break;

                case SegmentationSelection.morphD:
                    if (this.KernelType < 5)
                        outputImage = CvipOp.MorphDilate(inputImage, this.KernelType, this.KernelSize, this.KernelHeight, this.KernelWidth);
                    else
                    {
                        int[] matrix = this.morphGrid.CurrentValues;
                        outputImage = CvipOp.MorphDilate_Image(inputImage,matrix, 0, 0, 0, this.morphGrid.Rows);
                    }
                    break;

                case SegmentationSelection.morphE:
                    if (this.KernelType < 5)
                        outputImage = CvipOp.MorphErode(inputImage, this.KernelType, this.KernelSize, this.KernelHeight, this.KernelWidth);
                    else
                    {
                        int[] matrix = this.morphGrid.CurrentValues;
                        outputImage = CvipOp.MorphErode_Image(inputImage, matrix, 0, 0, 0, this.morphGrid.Rows);
                    }
                    break;

                case SegmentationSelection.morphO:
                    if (this.KernelType < 5)
                        outputImage = CvipOp.MorphOpen(inputImage, this.KernelType, this.KernelSize, this.KernelHeight, this.KernelWidth);
                    else
                    {
                        int[] matrix = this.morphGrid.CurrentValues;
                        outputImage = CvipOp.MorphOpen_Image(inputImage, matrix, 0, 0, 0, this.morphGrid.Rows);
                    }
                    break;

                case SegmentationSelection.morphC:
                    if (this.KernelType < 5)
                        outputImage = CvipOp.MorphClose(inputImage, this.KernelType, this.KernelSize, this.KernelHeight, this.KernelWidth);
                    else
                    {
                        int[] matrix = this.morphGrid.CurrentValues;
                        outputImage = CvipOp.MorphClose_Image(inputImage, matrix, 0, 0, 0, this.morphGrid.Rows);
                    }
                    break;

                case SegmentationSelection.morphI:
                    if (!CvipOp.Check_Bin(inputImage))
                    {
                        MessageBox.Show("The input image must be a binary image. You can get a binary image by thresholding an image",
                            "Input image error", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                        break;
                    }
                    string surrounds = this.Surrounds;
                    if (string.IsNullOrEmpty(surrounds))
                    {
                        MessageBox.Show("Please select surrounding pattern(s).", "Surrounds error",
                            MessageBoxButtons.OK, MessageBoxIcon.Warning);
                        break;
                    }
                    outputImage = CvipOp.Morpho_com(inputImage, surrounds, this.Rotate, this.BoolFunc, this.NumIterations, this.SubFields);
                    break;

                case SegmentationSelection.morphHit:
                    outputImage = CvipOp.Morph_Hitmiss(inputImage, this.filterMask.Rows, this.filterMask.CurrentValues);
                    break;

                case SegmentationSelection.morphThin:
                    outputImage = CvipOp.Morph_Thinning(inputImage, this.filterMask.Rows, this.filterMask.CurrentValues);
                    break;

                case SegmentationSelection.morphSkel:
                    outputImage = CvipOp.Morph_Skeleton(inputImage, this.filterMask.Rows, this.filterMask.CurrentValues, this.NumIterations, this.Connectivity, this.SkeletonMethod);
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
            MainForm.AnalysisForm.Close();
        }
        private void btnHelp_Click(object sender, EventArgs e)
        {
            MainForm.ShowHelp();
        }
        private void btnReset_Click(object sender, EventArgs e)
        {
            ResetControls();
        }
        private void btnViewSurrounds_Click(object sender, EventArgs e)
        {
            StringBuilder bldr = new StringBuilder();
            bldr.AppendLine("         0                      0                      1                      1");
            bldr.AppendLine("    0        0            0        1            0        1            1        1");
            bldr.AppendLine("    0        0            0        0            0        0            0        0");
            bldr.AppendLine("         0                      0                      0                      0");
            bldr.AppendLine();
            bldr.AppendLine("  (1) E* = 1        (2) E* = 0       (3) E* = 0        (4) E* = 0");
            bldr.AppendLine();
            bldr.AppendLine();
            bldr.AppendLine();
            bldr.AppendLine("         1                      1                      1                      0");
            bldr.AppendLine("    1        1            1        1            1        1            1        1");
            bldr.AppendLine("    1        0            1        0            1        1            0        0");
            bldr.AppendLine("         0                      1                      1                      1");
            bldr.AppendLine();
            bldr.AppendLine("  (5) E* = 0        (6) E* = 0       (7) E* = 1        (8) E* = -2");
            bldr.AppendLine();
            bldr.AppendLine();
            bldr.AppendLine();
            bldr.AppendLine("         1                      1                      1                      0");
            bldr.AppendLine("    0        1            0        1            1        1            1        1");
            bldr.AppendLine("    1        0            0        0            0        0            0        0");
            bldr.AppendLine("         0                      1                      1                      0");
            bldr.AppendLine();
            bldr.AppendLine("  (9) E* = -1     (10) E* = -1    (11) E* = -1     (12) E* = -1");
            bldr.AppendLine();
            bldr.AppendLine();
            bldr.AppendLine();
            bldr.AppendLine("         0                        1");
            bldr.AppendLine("    0        1              0        1");
            bldr.AppendLine("    1        0              1        0");
            bldr.AppendLine("         0                        1");
            bldr.AppendLine();
            bldr.AppendLine("  (13) E* = -1     (14) E* = -1");
            MessageBox.Show(bldr.ToString(), "Surrounds for Iterative Morphological Filtering",
                MessageBoxButtons.OK, MessageBoxIcon.None);
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
        private void cboIterations_Validating(object sender, CancelEventArgs e)
        {
            if (this.cboMorphIterations.SelectedIndex != (this.cboMorphIterations.Items.Count - 1))
                this.cboUIntVal_Validating(sender, e);
        }

        private void cboSkeletonConnect_SelectedIndexChanged(object sender, EventArgs e)
        {
            switch (this.Connectivity)
            {
                case 0: // "4 horiz/vert mask"
                    this.filterMask.CurrentDirection = Direction.ArrowDown;
                    this.filterMask.LoadCurrentValues();
                    break;
                case 1: //  "4 diag mask"
                    this.filterMask.CurrentDirection = Direction.ArrowUpRight;
                    this.filterMask.LoadCurrentValues();
                    break;
            }
        }
        private void cboKernelType_SelectedIndexChanged(object sender, EventArgs e)
        {
            switch (this.KernelType)
            {
                case 1: // circle
                    this.cboKernelHeight.Visible = this.lblKernelHeight.Visible = false;
                    this.cboKernelWidth.Visible = this.lblKernelWidth.Visible = false;
                    this.morphGrid.Hide();
                    break;
                case 2: // square
                    this.cboKernelHeight.Visible = this.lblKernelHeight.Visible = false;
                    this.cboKernelWidth.Visible = this.lblKernelWidth.Visible = true;
                    this.lblKernelWidth.Text = "          Side:";
                    this.morphGrid.Hide();
                    break;
                case 3: // rectangle
                    this.cboKernelHeight.Visible = this.lblKernelHeight.Visible = true;
                    this.cboKernelWidth.Visible = this.lblKernelWidth.Visible = true;
                    this.lblKernelHeight.Text = "      Height:";
                    this.lblKernelWidth.Text = "       Width:";
                    this.morphGrid.Hide();
                    break;
                case 4: // cross
                    this.cboKernelHeight.Visible = this.lblKernelHeight.Visible = true;
                    this.cboKernelWidth.Visible = this.lblKernelWidth.Visible = true;
                    this.lblKernelHeight.Text = "Cross size:";
                    this.lblKernelWidth.Text = "Thickness:";
                    this.morphGrid.Hide();
                    break;
                case 5: // custom
                    this.cboKernelHeight.Visible = this.lblKernelHeight.Visible = false;
                    this.cboKernelWidth.Visible = this.lblKernelWidth.Visible = false;
                    this.morphGrid.Show();
                    this.morphGrid.Focus();
                    this.morphGrid.MaskSize = new Size(Int32.Parse(this.cboKernelSize.Text), Int32.Parse(this.cboKernelSize.Text));
                    break;
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
        private void chkMergeResult_CheckedChanged(object sender, EventArgs e)
        {
            this.cboWatershedThreshold.Visible = this.lblWatershedThreshold.Visible = this.MergeResult;
        }
        protected override void OnLoad(EventArgs e)
        {
            base.OnLoad(e);

            
            this.rbMedianFilter.Tag = SegmentationSelection.median;
            this.rbKurwaharaFilter.Tag = SegmentationSelection.Kuwahara;
            this.rbSuperPixel.Tag = SegmentationSelection.superPixel;
            this.rbAnatropicDiffusionFilter.Tag = SegmentationSelection.Anisotrophic;

            this.rbGrayLevelQuant.Tag = SegmentationSelection.grayQuant;
            this.rbAutoThresh.Tag = SegmentationSelection.autoThreshold;
            this.rbOtsu.Tag = SegmentationSelection.otsu;
            this.rbHistThreshold.Tag = SegmentationSelection.histThreshold;
            this.rbFuzzyCMean.Tag = SegmentationSelection.fuzzyc;
            this.rbMedianCut.Tag = SegmentationSelection.medCut;
            this.rbPCTMedian.Tag = SegmentationSelection.pctMed;
            this.rbSCTCenter.Tag = SegmentationSelection.sct;
            this.rbMultiResolution.Tag = SegmentationSelection.multiRes;
            this.rbSplitMerge.Tag = SegmentationSelection.splitMerge;
            this.rbWatershed.Tag = SegmentationSelection.watershed;
            //this.rbGVFSnake.Tag = SegmentationSelection.gvfSnake;
            this.rbMorphDilation.Tag = SegmentationSelection.morphD;
            this.rbMorphErosion.Tag = SegmentationSelection.morphE;
            this.rbMorphOpening.Tag = SegmentationSelection.morphO;
            this.rbMorphClosing.Tag = SegmentationSelection.morphC;
            this.rbMorphIterative.Tag = SegmentationSelection.morphI;
            this.rbHitOrMiss.Tag = SegmentationSelection.morphHit;
            this.rbThinning.Tag = SegmentationSelection.morphThin;
            this.rbSkeletonization.Tag = SegmentationSelection.morphSkel;

            ResetControls();
        }
        private void rbFilterSize_CheckedChanged(object sender, EventArgs e)
        {
            RadioButton rb = sender as RadioButton;
            if ((rb != null) && rb.Checked)
            {                
                this.filterMask.LoadCurrentValues();
               // this.filterMask.Show();
                this.filterMask.Focus();
                if (this.currentSelection == SegmentationSelection.morphHit || this.currentSelection == SegmentationSelection.morphThin)
                    this.filterMask.Visible = true;
            }
        }
        private void rbHomogeneityTest_CheckedChanged(object sender, EventArgs e)
        {
            RadioButton rb = sender as RadioButton;
            if ((rb != null) && rb.Checked)
            {
                this.cboPercentage.Visible = this.lblPercentage.Visible = (this.HomogeneityTest == 4);
                this.cboPixelDistance.Visible = this.lblPixelDistance.Visible
                    = this.cboSimilarity.Visible = this.lblSimilarity.Visible = (this.HomogeneityTest == 6);
                this.cboThreshold.Visible = this.lblThreshold.Visible = (this.HomogeneityTest == 4) || (this.HomogeneityTest == 5);
            }
        }
        private void rbSegmentation_CheckedChanged(object sender, EventArgs e)
        {
            RadioButton rb = sender as RadioButton;
            if ((rb != null) && rb.Checked && (rb.Tag != null))
            {
                this.currentSelection = (SegmentationSelection)rb.Tag;
                UpdateControls();
                
            }
        }
        private void ResetControls()
        {
            // Gray-Level Quant Panel
            this.cboFuzzyCVariance.Text = "3.0";
            this.cboLimit.Text = "10.0";
            this.cboNumColors.Text = "3";
            this.cboNumGrayLevels.Text = "8";
            this.cboQuantMethod.SelectedIndex = 0;
            this.cboSCTAAxis.Text = "2";
            this.cboSCTBAxis.Text = "2";
            this.cboWatershedThreshold.Text = "0.7";
            this.chkMergeResult.Checked = false;

            // Multi-Resolution Panel
            this.cboEntryLevel.Text = "3";
            this.cboPercentage.Text = "0.7";
            this.cboPixelDistance.Text = "2.0";
            this.cboSimilarity.Text = "50.0";
            this.cboThreshold.Text = "50.0";
            this.chkPCT.Checked = false;
            this.rbPureUniform.Checked = true;

            //// GVF Snake Panel
            //this.cboAlpha.Text = "0.01";
            //this.cboBeta.Text = "0.01";
            //this.cboKappa.Text = "0.01";
            //this.cboSnakeIterations.Text = "5";

            // Morphological Panel
            this.cboKernelHeight.Text = "3";
            this.cboKernelSize.Text = "3";
            this.cboKernelType.SelectedIndex = 2;
            this.cboKernelWidth.Text = "3";

            // Morph-Iterative Panel
            this.cboBoolFunc.SelectedIndex = 5;
            this.cboMorphIterations.Text = "3";
            this.cboSubFields.Text = "1";
            this.chkRotate.Checked = true;
            this.chkSurround1.Checked = true;
            this.chkSurround2.Checked = false;
            this.chkSurround3.Checked = false;
            this.chkSurround4.Checked = false;
            this.chkSurround5.Checked = false;
            this.chkSurround6.Checked = false;
            this.chkSurround7.Checked = true;
            this.chkSurround8.Checked = false;
            this.chkSurround9.Checked = false;
            this.chkSurround10.Checked = false;
            this.chkSurround11.Checked = false;
            this.chkSurround12.Checked = false;
            this.chkSurround13.Checked = false;
            this.chkSurround14.Checked = false;

            // Filter Size Panel
            this.cboSkeletonConnect.SelectedIndex = 2;
            this.cboSkeletonIterations.Text = "10";
            this.cboSkeletonMethod.SelectedIndex = 1;
            this.rbFilterSize3x3.Checked = true;

            //Histogram Thresh Panel
            this.rbHistThreshBands.Checked = true;
            this.cbHistThresh.Text = "2";

            //////////////////////////////////
            ///Modify below to auto-select the first one

            // Default current selection
            this.currentSelection = SegmentationSelection.median;
            this.rbMedianFilter.Checked = true;
            //this.rbGrayLevelQuant.Checked = true;
            this.rbKurwaharaFilter.Checked = false;
            this.rbAnatropicDiffusionFilter.Checked = false;
            this.rbGrayLevelQuant.Checked = false;
            this.rbAutoThresh.Checked = false;
            this.rbOtsu.Checked = false;
            this.rbHistThreshold.Checked = false;
            this.rbFuzzyCMean.Checked = false;
            this.rbMedianCut.Checked = false;
            this.rbPCTMedian.Checked = false;
            this.rbSCTCenter.Checked = false;
            this.rbMultiResolution.Checked = false;
            this.rbSplitMerge.Checked = false;
            this.rbWatershed.Checked = false;
            //is.rbGVFSnake.Checked = false;
            this.rbMorphDilation.Checked = false;
            this.rbMorphErosion.Checked = false;
            this.rbMorphOpening.Checked = false;
            this.rbMorphClosing.Checked = false;
            this.rbMorphIterative.Checked = false;
            this.rbHitOrMiss.Checked = false;
            this.rbThinning.Checked = false;
            this.rbSkeletonization.Checked = false;
            UpdateControls();








            ///////////////////////////////
            /// Sketchy Trial stuff
            /// implemented to fix the preprocessing tab on Analysis segmentation attempting to select AD filter the first 
            /// time you hit apply, then ku filter the second.

            this.currentSelection = SegmentationSelection.autoThreshold;
            UpdateControls();
            this.currentSelection = SegmentationSelection.fuzzyc;
            UpdateControls();
            this.currentSelection = SegmentationSelection.median;
            UpdateControls();
            this.currentSelection = SegmentationSelection.Anisotrophic;
            UpdateControls();
            this.currentSelection = SegmentationSelection.Kuwahara;


            this.rbMedianFilter.Checked = true;
            UpdateControls();
            this.rbKurwaharaFilter.Checked = true;
            this.rbMedianFilter.Checked = false;
            UpdateControls();
            this.rbAnatropicDiffusionFilter.Checked = true;
            this.rbKurwaharaFilter.Checked = false;
            UpdateControls();
            this.rbMedianFilter.Checked = true;
            this.rbAnatropicDiffusionFilter.Checked = false;
            UpdateControls();

            UpdateControls();





        }
        private void UpdateControls()
        {
            if (MainForm.Viewers != null)
            {
                // anagropic panel 
                if (this.currentSelection == SegmentationSelection.Anisotrophic)
                {
                    this.pnlAnisotropic.Visible = true;
                }
                else { this.pnlAnisotropic.Visible = false; }

                //mask size for preprocessing
                if ((this.currentSelection == SegmentationSelection.median) || (this.currentSelection == SegmentationSelection.Kuwahara))
                {
                    this.lblMaskSize.Visible = true;
                    this.cboMaskSize.Visible = true;
                }
                else
                {
                    this.lblMaskSize.Visible = false;
                    this.cboMaskSize.Visible = false;
                }
                if (this.currentSelection == SegmentationSelection.median || this.currentSelection == SegmentationSelection.Anisotrophic) { this.pnlMedian.Visible = true; }
                else { this.pnlMedian.Visible = false; }

                if (this.currentSelection == SegmentationSelection.Anisotrophic) { this.rbAdaptive.Visible = false; } else { this.rbAdaptive.Visible = true; }
                if (this.currentSelection == SegmentationSelection.median) { this.rbParametric.Visible = false; } else { this.rbParametric.Visible = true; }

                switch (this.currentSelection)
                {


                    case SegmentationSelection.median:

                        this.pnlFilterSize.Visible = false;
                        this.pnlGrayLevelQuant.Visible = false;
                        //this.pnlGVFSnake.Visible = false;
                        this.pnlMorphIterative.Visible = false;
                        this.pnlMorphological.Visible = false;
                        this.pnlMultiRes.Visible = false;
                        this.pnlHistThresh.Visible = false;
                        this.filterMask.Hide();
                        this.morphGrid.Hide();


                        break;

                    case SegmentationSelection.Kuwahara:

                        this.pnlFilterSize.Visible = false;
                        this.pnlGrayLevelQuant.Visible = false;
                        //this.pnlGVFSnake.Visible = false;
                        this.pnlMorphIterative.Visible = false;
                        this.pnlMorphological.Visible = false;
                        this.pnlMultiRes.Visible = false;
                        this.pnlHistThresh.Visible = false;
                        this.filterMask.Hide();
                        this.morphGrid.Hide();
                        break;
                    case SegmentationSelection.Anisotrophic:

                        this.pnlFilterSize.Visible = false;
                        this.pnlGrayLevelQuant.Visible = false;
                        //this.pnlGVFSnake.Visible = false;
                        this.pnlMorphIterative.Visible = false;
                        this.pnlMorphological.Visible = false;
                        this.pnlMultiRes.Visible = false;
                        this.pnlHistThresh.Visible = false;
                        this.filterMask.Hide();
                        this.morphGrid.Hide();
                        break;
                    case SegmentationSelection.superPixel:

                        this.pnlFilterSize.Visible = false;
                        this.pnlGrayLevelQuant.Visible = false;
                        //this.pnlGVFSnake.Visible = false;
                        this.pnlMorphIterative.Visible = false;
                        this.pnlMorphological.Visible = false;
                        this.pnlMultiRes.Visible = false;
                        this.pnlHistThresh.Visible = false;
                        this.filterMask.Hide();
                        this.morphGrid.Hide();
                        break;
                    case SegmentationSelection.grayQuant:

                        this.pnlGrayLevelQuant.Visible = true;
                        this.cboNumGrayLevels.Visible = this.lblNumGrayLevels.Visible = (this.currentSelection == SegmentationSelection.grayQuant);
                        this.cboQuantMethod.Visible = this.lblQuantMethod.Visible = (this.currentSelection == SegmentationSelection.grayQuant);
                        this.cboLimit.Visible = this.lblLimit.Visible = (this.currentSelection == SegmentationSelection.autoThreshold);
                        this.cboFuzzyCVariance.Visible = this.lblFuzzyCVariance.Visible = (this.currentSelection == SegmentationSelection.fuzzyc);
                        this.cboNumColors.Visible = this.lblNumColors.Visible = ((this.currentSelection == SegmentationSelection.medCut) || (this.currentSelection == SegmentationSelection.pctMed));
                        this.cboSCTAAxis.Visible = this.lblSCTAAxis.Visible = (this.currentSelection == SegmentationSelection.sct);
                        this.cboSCTBAxis.Visible = this.lblSCTBAxis.Visible = (this.currentSelection == SegmentationSelection.sct);
                        this.chkMergeResult.Visible = (this.currentSelection == SegmentationSelection.watershed);
                        this.cboWatershedThreshold.Visible = this.lblWatershedThreshold.Visible
                            = ((this.currentSelection == SegmentationSelection.watershed) && this.MergeResult);

                        this.pnlFilterSize.Visible = false;
                        //this.pnlGVFSnake.Visible = false;
                        this.pnlMorphIterative.Visible = false;
                        this.pnlMorphological.Visible = false;
                        this.pnlMultiRes.Visible = false;
                        this.pnlHistThresh.Visible = false;
                        this.filterMask.Hide();
                        this.morphGrid.Hide();
                        break;
                    case SegmentationSelection.autoThreshold:

                        this.pnlGrayLevelQuant.Visible = true;
                        this.cboNumGrayLevels.Visible = this.lblNumGrayLevels.Visible = (this.currentSelection == SegmentationSelection.grayQuant);
                        this.cboQuantMethod.Visible = this.lblQuantMethod.Visible = (this.currentSelection == SegmentationSelection.grayQuant);
                        this.cboLimit.Visible = this.lblLimit.Visible = (this.currentSelection == SegmentationSelection.autoThreshold);
                        this.cboFuzzyCVariance.Visible = this.lblFuzzyCVariance.Visible = (this.currentSelection == SegmentationSelection.fuzzyc);
                        this.cboNumColors.Visible = this.lblNumColors.Visible = ((this.currentSelection == SegmentationSelection.medCut) || (this.currentSelection == SegmentationSelection.pctMed));
                        this.cboSCTAAxis.Visible = this.lblSCTAAxis.Visible = (this.currentSelection == SegmentationSelection.sct);
                        this.cboSCTBAxis.Visible = this.lblSCTBAxis.Visible = (this.currentSelection == SegmentationSelection.sct);
                        this.chkMergeResult.Visible = (this.currentSelection == SegmentationSelection.watershed);
                        this.cboWatershedThreshold.Visible = this.lblWatershedThreshold.Visible
                            = ((this.currentSelection == SegmentationSelection.watershed) && this.MergeResult);

                        this.pnlFilterSize.Visible = false;
                        //this.pnlGVFSnake.Visible = false;
                        this.pnlMorphIterative.Visible = false;
                        this.pnlMorphological.Visible = false;
                        this.pnlMultiRes.Visible = false;
                        this.pnlHistThresh.Visible = false;
                        this.filterMask.Hide();
                        this.morphGrid.Hide();
                        break;
                    case SegmentationSelection.fuzzyc:


                        this.pnlGrayLevelQuant.Visible = true;
                        this.cboNumGrayLevels.Visible = this.lblNumGrayLevels.Visible = (this.currentSelection == SegmentationSelection.grayQuant);
                        this.cboQuantMethod.Visible = this.lblQuantMethod.Visible = (this.currentSelection == SegmentationSelection.grayQuant);
                        this.cboLimit.Visible = this.lblLimit.Visible = (this.currentSelection == SegmentationSelection.autoThreshold);
                        this.cboFuzzyCVariance.Visible = this.lblFuzzyCVariance.Visible = (this.currentSelection == SegmentationSelection.fuzzyc);
                        this.cboNumColors.Visible = this.lblNumColors.Visible = ((this.currentSelection == SegmentationSelection.medCut) || (this.currentSelection == SegmentationSelection.pctMed));
                        this.cboSCTAAxis.Visible = this.lblSCTAAxis.Visible = (this.currentSelection == SegmentationSelection.sct);
                        this.cboSCTBAxis.Visible = this.lblSCTBAxis.Visible = (this.currentSelection == SegmentationSelection.sct);
                        this.chkMergeResult.Visible = (this.currentSelection == SegmentationSelection.watershed);
                        this.cboWatershedThreshold.Visible = this.lblWatershedThreshold.Visible
                            = ((this.currentSelection == SegmentationSelection.watershed) && this.MergeResult);

                        this.pnlFilterSize.Visible = false;
                        //this.pnlGVFSnake.Visible = false;
                        this.pnlMorphIterative.Visible = false;
                        this.pnlMorphological.Visible = false;
                        this.pnlMultiRes.Visible = false;
                        this.pnlHistThresh.Visible = false;
                        this.filterMask.Hide();
                        this.morphGrid.Hide();
                        break;
                    case SegmentationSelection.medCut:


                        this.pnlGrayLevelQuant.Visible = true;
                        this.cboNumGrayLevels.Visible = this.lblNumGrayLevels.Visible = (this.currentSelection == SegmentationSelection.grayQuant);
                        this.cboQuantMethod.Visible = this.lblQuantMethod.Visible = (this.currentSelection == SegmentationSelection.grayQuant);
                        this.cboLimit.Visible = this.lblLimit.Visible = (this.currentSelection == SegmentationSelection.autoThreshold);
                        this.cboFuzzyCVariance.Visible = this.lblFuzzyCVariance.Visible = (this.currentSelection == SegmentationSelection.fuzzyc);
                        this.cboNumColors.Visible = this.lblNumColors.Visible = ((this.currentSelection == SegmentationSelection.medCut) || (this.currentSelection == SegmentationSelection.pctMed));
                        this.cboSCTAAxis.Visible = this.lblSCTAAxis.Visible = (this.currentSelection == SegmentationSelection.sct);
                        this.cboSCTBAxis.Visible = this.lblSCTBAxis.Visible = (this.currentSelection == SegmentationSelection.sct);
                        this.chkMergeResult.Visible = (this.currentSelection == SegmentationSelection.watershed);
                        this.cboWatershedThreshold.Visible = this.lblWatershedThreshold.Visible
                            = ((this.currentSelection == SegmentationSelection.watershed) && this.MergeResult);

                        this.pnlFilterSize.Visible = false;
                        //this.pnlGVFSnake.Visible = false;
                        this.pnlMorphIterative.Visible = false;
                        this.pnlMorphological.Visible = false;
                        this.pnlMultiRes.Visible = false;
                        this.pnlHistThresh.Visible = false;
                        this.filterMask.Hide();
                        this.morphGrid.Hide();
                        break;
                    case SegmentationSelection.pctMed:


                        this.pnlGrayLevelQuant.Visible = true;
                        this.cboNumGrayLevels.Visible = this.lblNumGrayLevels.Visible = (this.currentSelection == SegmentationSelection.grayQuant);
                        this.cboQuantMethod.Visible = this.lblQuantMethod.Visible = (this.currentSelection == SegmentationSelection.grayQuant);
                        this.cboLimit.Visible = this.lblLimit.Visible = (this.currentSelection == SegmentationSelection.autoThreshold);
                        this.cboFuzzyCVariance.Visible = this.lblFuzzyCVariance.Visible = (this.currentSelection == SegmentationSelection.fuzzyc);
                        this.cboNumColors.Visible = this.lblNumColors.Visible = ((this.currentSelection == SegmentationSelection.medCut) || (this.currentSelection == SegmentationSelection.pctMed));
                        this.cboSCTAAxis.Visible = this.lblSCTAAxis.Visible = (this.currentSelection == SegmentationSelection.sct);
                        this.cboSCTBAxis.Visible = this.lblSCTBAxis.Visible = (this.currentSelection == SegmentationSelection.sct);
                        this.chkMergeResult.Visible = (this.currentSelection == SegmentationSelection.watershed);
                        this.cboWatershedThreshold.Visible = this.lblWatershedThreshold.Visible
                            = ((this.currentSelection == SegmentationSelection.watershed) && this.MergeResult);

                        this.pnlFilterSize.Visible = false;
                        //this.pnlGVFSnake.Visible = false;
                        this.pnlMorphIterative.Visible = false;
                        this.pnlMorphological.Visible = false;
                        this.pnlMultiRes.Visible = false;
                        this.pnlHistThresh.Visible = false;
                        this.filterMask.Hide();
                        this.morphGrid.Hide();
                        break;
                    case SegmentationSelection.sct:


                        this.pnlGrayLevelQuant.Visible = true;
                        this.cboNumGrayLevels.Visible = this.lblNumGrayLevels.Visible = (this.currentSelection == SegmentationSelection.grayQuant);
                        this.cboQuantMethod.Visible = this.lblQuantMethod.Visible = (this.currentSelection == SegmentationSelection.grayQuant);
                        this.cboLimit.Visible = this.lblLimit.Visible = (this.currentSelection == SegmentationSelection.autoThreshold);
                        this.cboFuzzyCVariance.Visible = this.lblFuzzyCVariance.Visible = (this.currentSelection == SegmentationSelection.fuzzyc);
                        this.cboNumColors.Visible = this.lblNumColors.Visible = ((this.currentSelection == SegmentationSelection.medCut) || (this.currentSelection == SegmentationSelection.pctMed));
                        this.cboSCTAAxis.Visible = this.lblSCTAAxis.Visible = (this.currentSelection == SegmentationSelection.sct);
                        this.cboSCTBAxis.Visible = this.lblSCTBAxis.Visible = (this.currentSelection == SegmentationSelection.sct);
                        this.chkMergeResult.Visible = (this.currentSelection == SegmentationSelection.watershed);
                        this.cboWatershedThreshold.Visible = this.lblWatershedThreshold.Visible
                            = ((this.currentSelection == SegmentationSelection.watershed) && this.MergeResult);

                        this.pnlFilterSize.Visible = false;
                        //this.pnlGVFSnake.Visible = false;
                        this.pnlMorphIterative.Visible = false;
                        this.pnlMorphological.Visible = false;
                        this.pnlMultiRes.Visible = false;
                        this.pnlHistThresh.Visible = false;
                        this.filterMask.Hide();
                        this.morphGrid.Hide();
                        break;

                    case SegmentationSelection.watershed:



                        this.pnlFilterSize.Visible = false;
                        //this.pnlGVFSnake.Visible = false;
                        this.pnlMorphIterative.Visible = false;
                        this.pnlMorphological.Visible = false;
                        this.pnlMultiRes.Visible = false;
                        this.pnlHistThresh.Visible = false;
                        this.filterMask.Hide();
                        this.morphGrid.Hide();

                        this.pnlGrayLevelQuant.Visible = true;
                        this.cboNumGrayLevels.Visible = this.lblNumGrayLevels.Visible = (this.currentSelection == SegmentationSelection.grayQuant);
                        this.cboQuantMethod.Visible = this.lblQuantMethod.Visible = (this.currentSelection == SegmentationSelection.grayQuant);
                        this.cboLimit.Visible = this.lblLimit.Visible = (this.currentSelection == SegmentationSelection.autoThreshold);
                        this.cboFuzzyCVariance.Visible = this.lblFuzzyCVariance.Visible = (this.currentSelection == SegmentationSelection.fuzzyc);
                        this.cboNumColors.Visible = this.lblNumColors.Visible = ((this.currentSelection == SegmentationSelection.medCut) || (this.currentSelection == SegmentationSelection.pctMed));
                        this.cboSCTAAxis.Visible = this.lblSCTAAxis.Visible = (this.currentSelection == SegmentationSelection.sct);
                        this.cboSCTBAxis.Visible = this.lblSCTBAxis.Visible = (this.currentSelection == SegmentationSelection.sct);
                        this.chkMergeResult.Visible = (this.currentSelection == SegmentationSelection.watershed);
                        this.cboWatershedThreshold.Visible = this.lblWatershedThreshold.Visible
                            = ((this.currentSelection == SegmentationSelection.watershed) && this.MergeResult);

                        this.pnlFilterSize.Visible = false;
                        //this.pnlGVFSnake.Visible = false;
                        this.pnlMorphIterative.Visible = false;
                        this.pnlMorphological.Visible = false;
                        this.pnlMultiRes.Visible = false;
                        this.pnlHistThresh.Visible = false;
                        this.filterMask.Hide();
                        this.morphGrid.Hide();
                        break;

                    case SegmentationSelection.otsu:
                        this.rbMedianFilter.Checked = false;
                        this.rbKurwaharaFilter.Checked = false;
                        this.rbAnatropicDiffusionFilter.Checked = false;
                        this.rbSuperPixel.Checked = false;
                        this.rbMorphDilation.Checked = false;
                        this.rbMorphErosion.Checked = false;
                        this.rbMorphOpening.Checked = false;
                        this.rbMorphClosing.Checked = false;

                        this.rbMorphIterative.Checked = false;
                        this.rbHitOrMiss.Checked = false;
                        this.rbThinning.Checked = false;



                        this.rbSkeletonization.Checked = false;
                        this.pnlFilterSize.Visible = false;
                        this.pnlGrayLevelQuant.Visible = false;
                        //this.pnlGVFSnake.Visible = false;
                        this.pnlMorphIterative.Visible = false;
                        this.pnlMorphological.Visible = false;
                        this.pnlMultiRes.Visible = false;
                        this.pnlHistThresh.Visible = false;
                        this.filterMask.Hide();
                        this.morphGrid.Hide();
                        break;
                    case SegmentationSelection.histThreshold:
                        this.rbMedianFilter.Checked = false;
                        this.rbKurwaharaFilter.Checked = false;
                        this.rbAnatropicDiffusionFilter.Checked = false;
                        this.rbSuperPixel.Checked = false;
                        this.rbMorphDilation.Checked = false;
                        this.rbMorphErosion.Checked = false;
                        this.rbMorphOpening.Checked = false;
                        this.rbMorphClosing.Checked = false;

                        this.rbMorphIterative.Checked = false;
                        this.rbHitOrMiss.Checked = false;
                        this.rbThinning.Checked = false;
                        this.rbSkeletonization.Checked = false;
                        this.pnlHistThresh.Visible = true;

                        this.pnlFilterSize.Visible = false;
                        this.pnlGrayLevelQuant.Visible = false;
                        //this.pnlGVFSnake.Visible = false;
                        this.pnlMorphIterative.Visible = false;
                        this.pnlMorphological.Visible = false;
                        this.pnlMultiRes.Visible = false;
                        this.filterMask.Hide();
                        this.morphGrid.Hide();
                        break;

                    case SegmentationSelection.multiRes:

                    case SegmentationSelection.splitMerge:
                        this.rbMedianFilter.Checked = false;
                        this.rbKurwaharaFilter.Checked = false;
                        this.rbAnatropicDiffusionFilter.Checked = false;
                        this.rbSuperPixel.Checked = false;
                        this.rbMorphDilation.Checked = false;
                        this.rbMorphErosion.Checked = false;
                        this.rbMorphOpening.Checked = false;
                        this.rbMorphClosing.Checked = false;

                        this.rbMorphIterative.Checked = false;
                        this.rbHitOrMiss.Checked = false;
                        this.rbThinning.Checked = false;
                        this.rbSkeletonization.Checked = false;

                        this.pnlMultiRes.Visible = true;
                        this.cboEntryLevel.Visible = this.lblEntryLevel.Visible = (this.currentSelection == SegmentationSelection.splitMerge);
                        this.cboPercentage.Visible = this.lblPercentage.Visible = (this.HomogeneityTest == 4);
                        this.cboPixelDistance.Visible = this.lblPixelDistance.Visible = (this.HomogeneityTest == 6);
                        this.cboSimilarity.Visible = this.lblSimilarity.Visible = (this.HomogeneityTest == 6);
                        this.cboThreshold.Visible = this.lblThreshold.Visible = (this.HomogeneityTest == 4) || (this.HomogeneityTest == 5);

                        this.pnlFilterSize.Visible = false;
                        this.pnlGrayLevelQuant.Visible = false;
                        //this.pnlGVFSnake.Visible = false;
                        this.pnlMorphIterative.Visible = false;
                        this.pnlMorphological.Visible = false;
                        this.pnlHistThresh.Visible = false;
                        this.filterMask.Hide();
                        this.morphGrid.Hide();
                        break;

                    //case SegmentationSelection.gvfSnake:
                    //    this.pnlFilterSize.Visible = false;
                    //    this.pnlGrayLevelQuant.Visible = false;
                    //    this.pnlGVFSnake.Visible = true;
                    //    this.pnlMorphIterative.Visible = false;
                    //    this.pnlMorphological.Visible = false;
                    //    this.pnlMultiRes.Visible = false;
                    //    this.pnlHistThresh.Visible = false;
                    //    this.filterMask.Hide();
                    //    this.morphGrid.Hide();
                    //break;

                    case SegmentationSelection.morphD:
                    case SegmentationSelection.morphE:
                    case SegmentationSelection.morphO:
                    case SegmentationSelection.morphC:
                        this.rbMedianFilter.Checked = false;
                        this.rbKurwaharaFilter.Checked = false;
                        this.rbAnatropicDiffusionFilter.Checked = false;
                        this.rbSuperPixel.Checked = false;
                        //  this.rbMorphDilation.Checked = false;
                        //  this.rbMorphErosion.Checked = false;
                        //  this.rbMorphOpening.Checked = false;
                        //  this.rbMorphClosing.Checked = false;

                        this.rbMorphIterative.Checked = false;
                        this.rbHitOrMiss.Checked = false;
                        this.rbThinning.Checked = false;
                        this.rbSkeletonization.Checked = false;

                        this.pnlMorphological.Visible = true;
                        switch (this.KernelType)
                        {
                            case 1: // circle
                                this.cboKernelHeight.Visible = this.lblKernelHeight.Visible = false;
                                this.cboKernelWidth.Visible = this.lblKernelWidth.Visible = false;
                                this.morphGrid.Hide();
                                break;
                            case 2: // square
                                this.cboKernelHeight.Visible = this.lblKernelHeight.Visible = false;
                                this.cboKernelWidth.Visible = this.lblKernelWidth.Visible = true;
                                this.lblKernelWidth.Text = "          Side:";
                                this.morphGrid.Hide();
                                break;
                            case 3: // rectangle
                                this.cboKernelHeight.Visible = this.lblKernelHeight.Visible = true;
                                this.cboKernelWidth.Visible = this.lblKernelWidth.Visible = true;
                                this.lblKernelHeight.Text = "      Height:";
                                this.lblKernelWidth.Text = "       Width:";
                                this.morphGrid.Hide();
                                break;
                            case 4: // cross
                                this.cboKernelHeight.Visible = this.lblKernelHeight.Visible = true;
                                this.cboKernelWidth.Visible = this.lblKernelWidth.Visible = true;
                                this.lblKernelHeight.Text = "Cross size:";
                                this.lblKernelWidth.Text = "Thickness:";
                                this.morphGrid.Hide();
                                break;
                            case 5: // custom
                                this.cboKernelHeight.Visible = this.lblKernelHeight.Visible = false;
                                this.cboKernelWidth.Visible = this.lblKernelWidth.Visible = false;
                                this.morphGrid.Show();
                                this.morphGrid.Focus();
                                this.morphGrid.MaskSize = new Size(Int32.Parse(this.cboKernelSize.Text), Int32.Parse(this.cboKernelSize.Text));
                                break;
                        }
                        this.pnlFilterSize.Visible = false;
                        this.pnlGrayLevelQuant.Visible = false;
                        //this.pnlGVFSnake.Visible = false;
                        this.pnlMorphIterative.Visible = false;
                        this.pnlMultiRes.Visible = false;
                        this.pnlHistThresh.Visible = false;
                        this.filterMask.Hide();
                        break;

                    case SegmentationSelection.morphI:


                        this.pnlFilterSize.Visible = false;
                        this.pnlGrayLevelQuant.Visible = false;
                        //this.pnlGVFSnake.Visible = false;
                        this.pnlMorphIterative.Visible = true;
                        this.pnlMorphological.Visible = false;
                        this.pnlMultiRes.Visible = false;
                        this.pnlHistThresh.Visible = false;
                        this.filterMask.Hide();
                        this.morphGrid.Hide();
                        break;


                    case SegmentationSelection.morphHit:

                    case SegmentationSelection.morphThin:


                        // case SegmentationSelection.morphSkel:
                        this.pnlFilterSize.Visible = true;
                        this.cboSkeletonIterations.Visible = this.lblSkeletonIterations.Visible = (this.currentSelection == SegmentationSelection.morphSkel);
                        this.cboSkeletonConnect.Visible = this.lblSkeletonConnect.Visible = (this.currentSelection == SegmentationSelection.morphSkel);
                        this.cboSkeletonMethod.Visible = this.lblSkeletonMethod.Visible = (this.currentSelection == SegmentationSelection.morphSkel);

                        this.filterMask.CurrentDirection = Direction.DirectionNotSet;
                        if (this.Connectivity == 1)
                            this.filterMask.CurrentDirection = Direction.ArrowUpRight;
                        this.filterMask.LoadCurrentValues();
                        this.filterMask.Show();
                        this.filterMask.Focus();

                        this.pnlGrayLevelQuant.Visible = false;
                        //this.pnlGVFSnake.Visible = false;
                        this.pnlMorphIterative.Visible = false;
                        this.pnlMorphological.Visible = false;
                        this.pnlMultiRes.Visible = false;
                        this.pnlHistThresh.Visible = false;
                        this.morphGrid.Hide();
                        break;

                    case SegmentationSelection.morphSkel:


                        this.pnlFilterSize.Visible = true;
                        this.cboSkeletonIterations.Visible = this.lblSkeletonIterations.Visible = (this.currentSelection == SegmentationSelection.morphSkel);
                        this.cboSkeletonConnect.Visible = this.lblSkeletonConnect.Visible = (this.currentSelection == SegmentationSelection.morphSkel);
                        this.cboSkeletonMethod.Visible = this.lblSkeletonMethod.Visible = (this.currentSelection == SegmentationSelection.morphSkel);


                        this.filterMask.CurrentDirection = Direction.DirectionNotSet;
                        if (this.Connectivity == 1)
                            this.filterMask.CurrentDirection = Direction.ArrowUpRight;
                        this.filterMask.LoadCurrentValues();
                        //this.filterMask.Visible = false;
                        this.filterMask.Focus();

                        this.pnlGrayLevelQuant.Visible = false;
                        //this.pnlGVFSnake.Visible = false;
                        this.pnlMorphIterative.Visible = false;
                        this.pnlMorphological.Visible = false;
                        this.pnlMultiRes.Visible = false;
                        this.filterMask.Visible = false;
                        this.pnlHistThresh.Visible = false;
                        this.morphGrid.Hide();
                        break;


                }
            
                
                //Deslection Menu

                
                switch (this.currentSelection)
                {
                    case SegmentationSelection.median:
                        this.rbMedianFilter.Checked = true;
                        this.rbKurwaharaFilter.Checked = false;
                        this.rbAnatropicDiffusionFilter.Checked = false;
                        this.rbGrayLevelQuant.Checked = false;
                        this.rbAutoThresh.Checked = false;
                        this.rbOtsu.Checked = false;
                        this.rbHistThreshold.Checked = false;
                        this.rbFuzzyCMean.Checked = false;
                        this.rbMedianCut.Checked = false;
                        this.rbPCTMedian.Checked = false;
                        this.rbSCTCenter.Checked = false;
                        this.rbMultiResolution.Checked = false;
                        this.rbSplitMerge.Checked = false;
                        this.rbWatershed.Checked = false;
                        this.rbGVFSnake.Checked = false;
                        this.rbMorphDilation.Checked = false;
                        this.rbMorphErosion.Checked = false;
                        this.rbMorphOpening.Checked = false;
                        this.rbMorphClosing.Checked = false;
                        this.rbMorphIterative.Checked = false;
                        this.rbHitOrMiss.Checked = false;
                        this.rbThinning.Checked = false;
                        this.rbSkeletonization.Checked = false;
                        break;
                    case SegmentationSelection.Kuwahara:
                        this.rbMedianFilter.Checked = false;
                        
                        this.rbAnatropicDiffusionFilter.Checked = false;
                        //this.rbKurwaharaFilter.Checked = false;
                        this.rbKurwaharaFilter.Checked = true;
                        this.rbAnatropicDiffusionFilter.Checked = false;
                        this.rbGrayLevelQuant.Checked = false;
                        this.rbAutoThresh.Checked = false;
                        this.rbOtsu.Checked = false;
                        this.rbHistThreshold.Checked = false;
                        this.rbFuzzyCMean.Checked = false;
                        this.rbMedianCut.Checked = false;
                        this.rbPCTMedian.Checked = false;
                        this.rbSCTCenter.Checked = false;
                        this.rbMultiResolution.Checked = false;
                        this.rbSplitMerge.Checked = false;
                        this.rbWatershed.Checked = false;
                        this.rbGVFSnake.Checked = false;
                        this.rbMorphDilation.Checked = false;
                        this.rbMorphErosion.Checked = false;
                        this.rbMorphOpening.Checked = false;
                        this.rbMorphClosing.Checked = false;
                        this.rbMorphIterative.Checked = false;
                        this.rbHitOrMiss.Checked = false;
                        this.rbThinning.Checked = false;
                        this.rbSkeletonization.Checked = false;
                        break;
                    case SegmentationSelection.Anisotrophic:
                        this.rbMedianFilter.Checked = false;
                        this.rbKurwaharaFilter.Checked = false;
                        
                        this.rbAnatropicDiffusionFilter.Checked = true;
                        this.rbKurwaharaFilter.Checked = false;
                        this.rbAnatropicDiffusionFilter.Checked = true;
                        this.rbGrayLevelQuant.Checked = false;
                        this.rbAutoThresh.Checked = false;
                        this.rbOtsu.Checked = false;
                        this.rbHistThreshold.Checked = false;
                        this.rbFuzzyCMean.Checked = false;
                        this.rbMedianCut.Checked = false;
                        this.rbPCTMedian.Checked = false;
                        this.rbSCTCenter.Checked = false;
                        this.rbMultiResolution.Checked = false;
                        this.rbSplitMerge.Checked = false;
                        this.rbWatershed.Checked = false;
                        this.rbGVFSnake.Checked = false;
                        this.rbMorphDilation.Checked = false;
                        this.rbMorphErosion.Checked = false;
                        this.rbMorphOpening.Checked = false;
                        this.rbMorphClosing.Checked = false;
                        this.rbMorphIterative.Checked = false;
                        this.rbHitOrMiss.Checked = false;
                        this.rbThinning.Checked = false;
                        this.rbSkeletonization.Checked = false;
                        break;

                        
                    case SegmentationSelection.grayQuant:
                        this.rbMedianFilter.Checked = false;
                        this.rbKurwaharaFilter.Checked = false;
                        this.rbAnatropicDiffusionFilter.Checked = false;
                        this.rbGrayLevelQuant.Checked = true;
                        this.rbKurwaharaFilter.Checked = false;
                this.rbAnatropicDiffusionFilter.Checked = false;
                
                this.rbAutoThresh.Checked = false;
                this.rbOtsu.Checked = false;
                this.rbHistThreshold.Checked = false;
                this.rbFuzzyCMean.Checked = false;
                this.rbMedianCut.Checked = false;
                this.rbPCTMedian.Checked = false;
                this.rbSCTCenter.Checked = false;
                this.rbMultiResolution.Checked = false;
                this.rbSplitMerge.Checked = false;
                this.rbWatershed.Checked = false;
                this.rbGVFSnake.Checked = false;
                this.rbMorphDilation.Checked = false;
                this.rbMorphErosion.Checked = false;
                this.rbMorphOpening.Checked = false;
                this.rbMorphClosing.Checked = false;
                this.rbMorphIterative.Checked = false;
                this.rbHitOrMiss.Checked = false;
                this.rbThinning.Checked = false;
                this.rbSkeletonization.Checked = false;
                        break;
                    case SegmentationSelection.autoThreshold:
                        this.rbMedianFilter.Checked = false;
                        this.rbKurwaharaFilter.Checked = false;
                        this.rbAnatropicDiffusionFilter.Checked = false;
                        this.rbGrayLevelQuant.Checked = false;
                        this.rbKurwaharaFilter.Checked = false;
                        this.rbMedianFilter.Checked = false;
                        this.rbKurwaharaFilter.Checked = false;
                        this.rbAnatropicDiffusionFilter.Checked = false;
                        this.rbAutoThresh.Checked = true;
                        this.rbKurwaharaFilter.Checked = false;
                        this.rbAnatropicDiffusionFilter.Checked = false;
                        this.rbGrayLevelQuant.Checked = false;
                        this.rbAutoThresh.Checked = true;
                        this.rbOtsu.Checked = false;
                        this.rbHistThreshold.Checked = false;
                        this.rbFuzzyCMean.Checked = false;
                        this.rbMedianCut.Checked = false;
                        this.rbPCTMedian.Checked = false;
                        this.rbSCTCenter.Checked = false;
                        this.rbMultiResolution.Checked = false;
                        this.rbSplitMerge.Checked = false;
                        this.rbWatershed.Checked = false;
                        this.rbGVFSnake.Checked = false;
                        this.rbMorphDilation.Checked = false;
                        this.rbMorphErosion.Checked = false;
                        this.rbMorphOpening.Checked = false;
                        this.rbMorphClosing.Checked = false;
                        this.rbMorphIterative.Checked = false;
                        this.rbHitOrMiss.Checked = false;
                        this.rbThinning.Checked = false;
                        this.rbSkeletonization.Checked = false;
                        break;
                    case SegmentationSelection.otsu:
                        this.rbMedianFilter.Checked = false;
                        this.rbKurwaharaFilter.Checked = false;
                        this.rbAnatropicDiffusionFilter.Checked = false;
                        this.rbGrayLevelQuant.Checked = false;
                        this.rbKurwaharaFilter.Checked = false;
                        this.rbKurwaharaFilter.Checked = false;
                        this.rbAnatropicDiffusionFilter.Checked = false;
                        this.rbGrayLevelQuant.Checked = false;
                        this.rbAutoThresh.Checked = false;
                        this.rbOtsu.Checked = true;
                        this.rbHistThreshold.Checked = false;
                        this.rbFuzzyCMean.Checked = false;
                        this.rbMedianCut.Checked = false;
                        this.rbPCTMedian.Checked = false;
                        this.rbSCTCenter.Checked = false;
                        this.rbMultiResolution.Checked = false;
                        this.rbSplitMerge.Checked = false;
                        this.rbWatershed.Checked = false;
                        this.rbGVFSnake.Checked = false;
                        this.rbMorphDilation.Checked = false;
                        this.rbMorphErosion.Checked = false;
                        this.rbMorphOpening.Checked = false;
                        this.rbMorphClosing.Checked = false;
                        this.rbMorphIterative.Checked = false;
                        this.rbHitOrMiss.Checked = false;
                        this.rbThinning.Checked = false;
                        this.rbSkeletonization.Checked = false;
                        break;
                    case SegmentationSelection.histThreshold:
                        this.rbMedianFilter.Checked = false;
                        this.rbKurwaharaFilter.Checked = false;
                        this.rbAnatropicDiffusionFilter.Checked = false;
                        this.rbGrayLevelQuant.Checked = false;
                        this.rbKurwaharaFilter.Checked = false;
                        this.rbKurwaharaFilter.Checked = false;
                        this.rbAnatropicDiffusionFilter.Checked = false;
                        this.rbGrayLevelQuant.Checked = false;
                        this.rbAutoThresh.Checked = false;
                        this.rbOtsu.Checked = false;
                        this.rbHistThreshold.Checked = true;
                        this.rbFuzzyCMean.Checked = false;
                        this.rbMedianCut.Checked = false;
                        this.rbPCTMedian.Checked = false;
                        this.rbSCTCenter.Checked = false;
                        this.rbMultiResolution.Checked = false;
                        this.rbSplitMerge.Checked = false;
                        this.rbWatershed.Checked = false;
                        this.rbGVFSnake.Checked = false;
                        this.rbMorphDilation.Checked = false;
                        this.rbMorphErosion.Checked = false;
                        this.rbMorphOpening.Checked = false;
                        this.rbMorphClosing.Checked = false;
                        this.rbMorphIterative.Checked = false;
                        this.rbHitOrMiss.Checked = false;
                        this.rbThinning.Checked = false;
                        this.rbSkeletonization.Checked = false;
                        break;
                    case SegmentationSelection.fuzzyc:
                        this.rbMedianFilter.Checked = false;
                        this.rbKurwaharaFilter.Checked = false;
                        this.rbAnatropicDiffusionFilter.Checked = false;
                        this.rbGrayLevelQuant.Checked = false;
                        this.rbKurwaharaFilter.Checked = false;
                        this.rbKurwaharaFilter.Checked = false;
                        this.rbAnatropicDiffusionFilter.Checked = false;
                        this.rbGrayLevelQuant.Checked = false;
                        this.rbAutoThresh.Checked = false;
                        this.rbOtsu.Checked = false;
                        this.rbHistThreshold.Checked = false;
                        this.rbFuzzyCMean.Checked = true;
                        this.rbMedianCut.Checked = false;
                        this.rbPCTMedian.Checked = false;
                        this.rbSCTCenter.Checked = false;
                        this.rbMultiResolution.Checked = false;
                        this.rbSplitMerge.Checked = false;
                        this.rbWatershed.Checked = false;
                        this.rbGVFSnake.Checked = false;
                        this.rbMorphDilation.Checked = false;
                        this.rbMorphErosion.Checked = false;
                        this.rbMorphOpening.Checked = false;
                        this.rbMorphClosing.Checked = false;
                        this.rbMorphIterative.Checked = false;
                        this.rbHitOrMiss.Checked = false;
                        this.rbThinning.Checked = false;
                        this.rbSkeletonization.Checked = false;
                        break;
                    case SegmentationSelection.medCut:
                        this.rbMedianFilter.Checked = false;
                        this.rbKurwaharaFilter.Checked = false;
                        this.rbAnatropicDiffusionFilter.Checked = false;
                        this.rbGrayLevelQuant.Checked = false;
                        this.rbKurwaharaFilter.Checked = false;
                        this.rbKurwaharaFilter.Checked = false;
                        this.rbAnatropicDiffusionFilter.Checked = false;
                        this.rbGrayLevelQuant.Checked = false;
                        this.rbAutoThresh.Checked = false;
                        this.rbOtsu.Checked = false;
                        this.rbHistThreshold.Checked = false;
                        this.rbFuzzyCMean.Checked = false;
                        this.rbMedianCut.Checked = true;
                        this.rbPCTMedian.Checked = false;
                        this.rbSCTCenter.Checked = false;
                        this.rbMultiResolution.Checked = false;
                        this.rbSplitMerge.Checked = false;
                        this.rbWatershed.Checked = false;
                        this.rbGVFSnake.Checked = false;
                        this.rbMorphDilation.Checked = false;
                        this.rbMorphErosion.Checked = false;
                        this.rbMorphOpening.Checked = false;
                        this.rbMorphClosing.Checked = false;
                        this.rbMorphIterative.Checked = false;
                        this.rbHitOrMiss.Checked = false;
                        this.rbThinning.Checked = false;
                        this.rbSkeletonization.Checked = false;
                        break;
                    case SegmentationSelection.pctMed:
                        this.rbMedianFilter.Checked = false;
                        this.rbKurwaharaFilter.Checked = false;
                        this.rbAnatropicDiffusionFilter.Checked = false;
                        this.rbGrayLevelQuant.Checked = false;
                        this.rbKurwaharaFilter.Checked = false;
                        this.rbKurwaharaFilter.Checked = false;
                        this.rbAnatropicDiffusionFilter.Checked = false;
                        this.rbGrayLevelQuant.Checked = false;
                        this.rbAutoThresh.Checked = false;
                        this.rbOtsu.Checked = false;
                        this.rbHistThreshold.Checked = false;
                        this.rbFuzzyCMean.Checked = false;
                        this.rbMedianCut.Checked = false;
                        this.rbPCTMedian.Checked = true;
                        this.rbSCTCenter.Checked = false;
                        this.rbMultiResolution.Checked = false;
                        this.rbSplitMerge.Checked = false;
                        this.rbWatershed.Checked = false;
                        this.rbGVFSnake.Checked = false;
                        this.rbMorphDilation.Checked = false;
                        this.rbMorphErosion.Checked = false;
                        this.rbMorphOpening.Checked = false;
                        this.rbMorphClosing.Checked = false;
                        this.rbMorphIterative.Checked = false;
                        this.rbHitOrMiss.Checked = false;
                        this.rbThinning.Checked = false;
                        this.rbSkeletonization.Checked = false;
                        break;
                    case SegmentationSelection.sct:
                        this.rbMedianFilter.Checked = false;
                        this.rbKurwaharaFilter.Checked = false;
                        this.rbAnatropicDiffusionFilter.Checked = false;
                        this.rbGrayLevelQuant.Checked = false;
                        this.rbKurwaharaFilter.Checked = false;
                        this.rbKurwaharaFilter.Checked = false;
                        this.rbAnatropicDiffusionFilter.Checked = false;
                        this.rbGrayLevelQuant.Checked = false;
                        this.rbAutoThresh.Checked = false;
                        this.rbOtsu.Checked = false;
                        this.rbHistThreshold.Checked = false;
                        this.rbFuzzyCMean.Checked = false;
                        this.rbMedianCut.Checked = false;
                        this.rbPCTMedian.Checked = false;
                        this.rbSCTCenter.Checked = true;
                        this.rbMultiResolution.Checked = false;
                        this.rbSplitMerge.Checked = false;
                        this.rbWatershed.Checked = false;
                        this.rbGVFSnake.Checked = false;
                        this.rbMorphDilation.Checked = false;
                        this.rbMorphErosion.Checked = false;
                        this.rbMorphOpening.Checked = false;
                        this.rbMorphClosing.Checked = false;
                        this.rbMorphIterative.Checked = false;
                        this.rbHitOrMiss.Checked = false;
                        this.rbThinning.Checked = false;
                        this.rbSkeletonization.Checked = false;
                        break;
                    case SegmentationSelection.multiRes:
                        this.rbMedianFilter.Checked = false;
                        this.rbKurwaharaFilter.Checked = false;
                        this.rbAnatropicDiffusionFilter.Checked = false;
                        this.rbGrayLevelQuant.Checked = false;
                        this.rbKurwaharaFilter.Checked = false;
                        this.rbKurwaharaFilter.Checked = false;
                        this.rbAnatropicDiffusionFilter.Checked = false;
                        this.rbGrayLevelQuant.Checked = false;
                        this.rbAutoThresh.Checked = false;
                        this.rbOtsu.Checked = false;
                        this.rbHistThreshold.Checked = false;
                        this.rbFuzzyCMean.Checked = false;
                        this.rbMedianCut.Checked = false;
                        this.rbPCTMedian.Checked = false;
                        this.rbSCTCenter.Checked = false;
                        this.rbMultiResolution.Checked = true;
                        this.rbSplitMerge.Checked = false;
                        this.rbWatershed.Checked = false;
                        this.rbGVFSnake.Checked = false;
                        this.rbMorphDilation.Checked = false;
                        this.rbMorphErosion.Checked = false;
                        this.rbMorphOpening.Checked = false;
                        this.rbMorphClosing.Checked = false;
                        this.rbMorphIterative.Checked = false;
                        this.rbHitOrMiss.Checked = false;
                        this.rbThinning.Checked = false;
                        this.rbSkeletonization.Checked = false;
                        break;
                    case SegmentationSelection.splitMerge:
                        this.rbMedianFilter.Checked = false;
                        this.rbKurwaharaFilter.Checked = false;
                        this.rbAnatropicDiffusionFilter.Checked = false;
                        this.rbGrayLevelQuant.Checked = false;
                        this.rbKurwaharaFilter.Checked = false;
                        this.rbKurwaharaFilter.Checked = false;
                        this.rbAnatropicDiffusionFilter.Checked = false;
                        this.rbGrayLevelQuant.Checked = false;
                        this.rbAutoThresh.Checked = false;
                        this.rbOtsu.Checked = false;
                        this.rbHistThreshold.Checked = false;
                        this.rbFuzzyCMean.Checked = false;
                        this.rbMedianCut.Checked = false;
                        this.rbPCTMedian.Checked = false;
                        this.rbSCTCenter.Checked = false;
                        this.rbMultiResolution.Checked = false;
                        this.rbSplitMerge.Checked = true;
                        this.rbWatershed.Checked = false;
                        this.rbGVFSnake.Checked = false;
                        this.rbMorphDilation.Checked = false;
                        this.rbMorphErosion.Checked = false;
                        this.rbMorphOpening.Checked = false;
                        this.rbMorphClosing.Checked = false;
                        this.rbMorphIterative.Checked = false;
                        this.rbHitOrMiss.Checked = false;
                        this.rbThinning.Checked = false;
                        this.rbSkeletonization.Checked = false;
                        break;
                    case SegmentationSelection.watershed:
                        this.rbMedianFilter.Checked = false;
                        this.rbKurwaharaFilter.Checked = false;
                        this.rbAnatropicDiffusionFilter.Checked = false;
                        this.rbGrayLevelQuant.Checked = false;
                        this.rbKurwaharaFilter.Checked = false;
                        this.rbKurwaharaFilter.Checked = false;
                        this.rbAnatropicDiffusionFilter.Checked = false;
                        this.rbGrayLevelQuant.Checked = false;
                        this.rbAutoThresh.Checked = false;
                        this.rbOtsu.Checked = false;
                        this.rbHistThreshold.Checked = false;
                        this.rbFuzzyCMean.Checked = false;
                        this.rbMedianCut.Checked = false;
                        this.rbPCTMedian.Checked = false;
                        this.rbSCTCenter.Checked = false;
                        this.rbMultiResolution.Checked = false;
                        this.rbSplitMerge.Checked = false;
                        this.rbWatershed.Checked = true;
                        this.rbGVFSnake.Checked = false;
                        this.rbMorphDilation.Checked = false;
                        this.rbMorphErosion.Checked = false;
                        this.rbMorphOpening.Checked = false;
                        this.rbMorphClosing.Checked = false;
                        this.rbMorphIterative.Checked = false;
                        this.rbHitOrMiss.Checked = false;
                        this.rbThinning.Checked = false;
                        this.rbSkeletonization.Checked = false;
                        break;

                    //this.rbGVFSnake.Checked = false; break;
                    case SegmentationSelection.morphD:
                        this.rbMedianFilter.Checked = false;
                        this.rbKurwaharaFilter.Checked = false;
                        this.rbAnatropicDiffusionFilter.Checked = false;
                        this.rbGrayLevelQuant.Checked = false;
                        this.rbKurwaharaFilter.Checked = false;
                        this.rbKurwaharaFilter.Checked = false;
                        this.rbAnatropicDiffusionFilter.Checked = false;
                        this.rbGrayLevelQuant.Checked = false;
                        this.rbAutoThresh.Checked = false;
                        this.rbOtsu.Checked = false;
                        this.rbHistThreshold.Checked = false;
                        this.rbFuzzyCMean.Checked = false;
                        this.rbMedianCut.Checked = false;
                        this.rbPCTMedian.Checked = false;
                        this.rbSCTCenter.Checked = false;
                        this.rbMultiResolution.Checked = false;
                        this.rbSplitMerge.Checked = false;
                        this.rbWatershed.Checked = false;
                        this.rbGVFSnake.Checked = false;
                        this.rbMorphDilation.Checked = true;
                        this.rbMorphErosion.Checked = false;
                        this.rbMorphOpening.Checked = false;
                        this.rbMorphClosing.Checked = false;
                        this.rbMorphIterative.Checked = false;
                        this.rbHitOrMiss.Checked = false;
                        this.rbThinning.Checked = false;
                        this.rbSkeletonization.Checked = false;
                        break;
                    case SegmentationSelection.morphE:
                        this.rbMedianFilter.Checked = false;
                        this.rbKurwaharaFilter.Checked = false;
                        this.rbAnatropicDiffusionFilter.Checked = false;
                        this.rbGrayLevelQuant.Checked = false;
                        this.rbKurwaharaFilter.Checked = false;
                        this.rbKurwaharaFilter.Checked = false;
                        this.rbAnatropicDiffusionFilter.Checked = false;
                        this.rbGrayLevelQuant.Checked = false;
                        this.rbAutoThresh.Checked = false;
                        this.rbOtsu.Checked = false;
                        this.rbHistThreshold.Checked = false;
                        this.rbFuzzyCMean.Checked = false;
                        this.rbMedianCut.Checked = false;
                        this.rbPCTMedian.Checked = false;
                        this.rbSCTCenter.Checked = false;
                        this.rbMultiResolution.Checked = false;
                        this.rbSplitMerge.Checked = false;
                        this.rbWatershed.Checked = false;
                        this.rbGVFSnake.Checked = false;
                        this.rbMorphDilation.Checked = false;
                        this.rbMorphErosion.Checked = true;
                        this.rbMorphOpening.Checked = false;
                        this.rbMorphClosing.Checked = false;
                        this.rbMorphIterative.Checked = false;
                        this.rbHitOrMiss.Checked = false;
                        this.rbThinning.Checked = false;
                        this.rbSkeletonization.Checked = false;
                        break;
                    case SegmentationSelection.morphO:
                        this.rbMedianFilter.Checked = false;
                        this.rbKurwaharaFilter.Checked = false;
                        this.rbAnatropicDiffusionFilter.Checked = false;
                        this.rbGrayLevelQuant.Checked = false; 
                        
                        this.rbKurwaharaFilter.Checked = false;
                        this.rbAnatropicDiffusionFilter.Checked = false;
                        this.rbGrayLevelQuant.Checked = false;
                        this.rbAutoThresh.Checked = false;
                        this.rbOtsu.Checked = false;
                        this.rbHistThreshold.Checked = false;
                        this.rbFuzzyCMean.Checked = false;
                        this.rbMedianCut.Checked = false;
                        this.rbPCTMedian.Checked = false;
                        this.rbSCTCenter.Checked = false;
                        this.rbMultiResolution.Checked = false;
                        this.rbSplitMerge.Checked = false;
                        this.rbWatershed.Checked = false;
                        this.rbGVFSnake.Checked = false;
                        this.rbMorphDilation.Checked = false;
                        this.rbMorphErosion.Checked = false;
                        this.rbMorphOpening.Checked = true;
                        this.rbMorphClosing.Checked = false;
                        this.rbMorphIterative.Checked = false;
                        this.rbHitOrMiss.Checked = false;
                        this.rbThinning.Checked = false;
                        this.rbSkeletonization.Checked = false;
                        break;
                    case SegmentationSelection.morphC:
                        this.rbMedianFilter.Checked = false;
                        this.rbKurwaharaFilter.Checked = false;
                        this.rbAnatropicDiffusionFilter.Checked = false;
                        this.rbGrayLevelQuant.Checked = false;
                        this.rbKurwaharaFilter.Checked = false;
                        this.rbKurwaharaFilter.Checked = false;
                        this.rbAnatropicDiffusionFilter.Checked = false;
                        this.rbGrayLevelQuant.Checked = false;
                        this.rbAutoThresh.Checked = false;
                        this.rbOtsu.Checked = false;
                        this.rbHistThreshold.Checked = false;
                        this.rbFuzzyCMean.Checked = false;
                        this.rbMedianCut.Checked = false;
                        this.rbPCTMedian.Checked = false;
                        this.rbSCTCenter.Checked = false;
                        this.rbMultiResolution.Checked = false;
                        this.rbSplitMerge.Checked = false;
                        this.rbWatershed.Checked = false;
                        this.rbGVFSnake.Checked = false;
                        this.rbMorphDilation.Checked = false;
                        this.rbMorphErosion.Checked = false;
                        this.rbMorphOpening.Checked = false;
                        this.rbMorphClosing.Checked = true;
                        this.rbMorphIterative.Checked = false;
                        this.rbHitOrMiss.Checked = false;
                        this.rbThinning.Checked = false;
                        this.rbSkeletonization.Checked = false;
                        break;
                    case SegmentationSelection.morphI:
                        this.rbMedianFilter.Checked = false;
                        this.rbKurwaharaFilter.Checked = false;
                        this.rbAnatropicDiffusionFilter.Checked = false;
                        this.rbGrayLevelQuant.Checked = false;
                        this.rbKurwaharaFilter.Checked = false;
                        this.rbKurwaharaFilter.Checked = false;
                        this.rbAnatropicDiffusionFilter.Checked = false;
                        this.rbGrayLevelQuant.Checked = false;
                        this.rbAutoThresh.Checked = false;
                        this.rbOtsu.Checked = false;
                        this.rbHistThreshold.Checked = false;
                        this.rbFuzzyCMean.Checked = false;
                        this.rbMedianCut.Checked = false;
                        this.rbPCTMedian.Checked = false;
                        this.rbSCTCenter.Checked = false;
                        this.rbMultiResolution.Checked = false;
                        this.rbSplitMerge.Checked = false;
                        this.rbWatershed.Checked = false;
                        this.rbGVFSnake.Checked = false;
                        this.rbMorphDilation.Checked = false;
                        this.rbMorphErosion.Checked = false;
                        this.rbMorphOpening.Checked = false;
                        this.rbMorphClosing.Checked = false;
                        this.rbMorphIterative.Checked = true;
                        this.rbHitOrMiss.Checked = false;
                        this.rbThinning.Checked = false;
                        this.rbSkeletonization.Checked = false;
                        break;
                    case SegmentationSelection.morphHit:
                        this.rbMedianFilter.Checked = false;
                        this.rbKurwaharaFilter.Checked = false;
                        this.rbAnatropicDiffusionFilter.Checked = false;
                        this.rbGrayLevelQuant.Checked = false;
                        this.rbKurwaharaFilter.Checked = false;
                        this.rbKurwaharaFilter.Checked = false;
                        this.rbAnatropicDiffusionFilter.Checked = false;
                        this.rbGrayLevelQuant.Checked = false;
                        this.rbAutoThresh.Checked = false;
                        this.rbOtsu.Checked = false;
                        this.rbHistThreshold.Checked = false;
                        this.rbFuzzyCMean.Checked = false;
                        this.rbMedianCut.Checked = false;
                        this.rbPCTMedian.Checked = false;
                        this.rbSCTCenter.Checked = false;
                        this.rbMultiResolution.Checked = false;
                        this.rbSplitMerge.Checked = false;
                        this.rbWatershed.Checked = false;
                        this.rbGVFSnake.Checked = false;
                        this.rbMorphDilation.Checked = false;
                        this.rbMorphErosion.Checked = false;
                        this.rbMorphOpening.Checked = false;
                        this.rbMorphClosing.Checked = false;
                        this.rbMorphIterative.Checked = false;
                        this.rbHitOrMiss.Checked = true;
                        this.rbThinning.Checked = false;
                        this.rbSkeletonization.Checked = false;
                        break;
                    case SegmentationSelection.morphThin:
                        this.rbMedianFilter.Checked = false;
                        this.rbKurwaharaFilter.Checked = false;
                        this.rbAnatropicDiffusionFilter.Checked = false;
                        this.rbGrayLevelQuant.Checked = false;
                        this.rbKurwaharaFilter.Checked = false;
                        this.rbKurwaharaFilter.Checked = false;
                        this.rbAnatropicDiffusionFilter.Checked = false;
                        this.rbGrayLevelQuant.Checked = false;
                        this.rbAutoThresh.Checked = false;
                        this.rbOtsu.Checked = false;
                        this.rbHistThreshold.Checked = false;
                        this.rbFuzzyCMean.Checked = false;
                        this.rbMedianCut.Checked = false;
                        this.rbPCTMedian.Checked = false;
                        this.rbSCTCenter.Checked = false;
                        this.rbMultiResolution.Checked = false;
                        this.rbSplitMerge.Checked = false;
                        this.rbWatershed.Checked = false;
                        this.rbGVFSnake.Checked = false;
                        this.rbMorphDilation.Checked = false;
                        this.rbMorphErosion.Checked = false;
                        this.rbMorphOpening.Checked = false;
                        this.rbMorphClosing.Checked = false;
                        this.rbMorphIterative.Checked = false;
                        this.rbHitOrMiss.Checked = false;
                        this.rbThinning.Checked = true;
                        this.rbSkeletonization.Checked = false;
                        break;
                    case SegmentationSelection.morphSkel:
                        this.rbMedianCut.Checked = false;
                        this.rbMedianFilter.Checked = false;
                        this.rbKurwaharaFilter.Checked = false;
                        this.rbAnatropicDiffusionFilter.Checked = false;
                        this.rbGrayLevelQuant.Checked = false;
                        this.rbKurwaharaFilter.Checked = false;
                        this.rbKurwaharaFilter.Checked = false;
                        this.rbAnatropicDiffusionFilter.Checked = false;
                        this.rbGrayLevelQuant.Checked = false;
                        this.rbAutoThresh.Checked = false;
                        this.rbOtsu.Checked = false;
                        this.rbHistThreshold.Checked = false;
                        this.rbFuzzyCMean.Checked = false;
                        this.rbMedianCut.Checked = false;
                        this.rbPCTMedian.Checked = false;
                        this.rbSCTCenter.Checked = false;
                        this.rbMultiResolution.Checked = false;
                        this.rbSplitMerge.Checked = false;
                        this.rbWatershed.Checked = false;
                        this.rbGVFSnake.Checked = false;
                        this.rbMorphDilation.Checked = false;
                        this.rbMorphErosion.Checked = false;
                        this.rbMorphOpening.Checked = false;
                        this.rbMorphClosing.Checked = false;
                        this.rbMorphIterative.Checked = false;
                        this.rbHitOrMiss.Checked = false;
                        this.rbThinning.Checked = false;
                        this.rbSkeletonization.Checked = true;
                        break;

                        
                }



            }
            // enable Apply button
            this.btnApply.Enabled = true;
            this.Cursor = Cursors.Default;
        }

        private void OnSelectedViewerChanged(ViewerForm viewer)
        {
            this.lblHistThresh.Enabled = (viewer != null) && (viewer.Bands == 3);
            this.rbHistThreshBands.Enabled = (viewer != null) && (viewer.Bands == 3);
            this.rbHistThreshPCT.Enabled = (viewer != null) && (viewer.Bands == 3);
            this.rbHistThreshLum.Enabled = (viewer != null) && (viewer.Bands == 3);
        }

        protected override void WndProc(ref Message m)
        {
            base.WndProc(ref m);
            if (MainForm.Viewers != null)
            {
                switch ((WM)m.Msg)
                {
                    case WM.CREATE:
                        this.filterMask = new MorphologicalMaskForm(this);
                        this.filterMask.btnApply.Click += new System.EventHandler(this.btnApply_Click);
                        this.morphGrid = new MorphGrid();
                        this.morphGrid.btnApply.Click += new System.EventHandler(this.btnApply_Click);
                        MainForm.Viewers.SelectedViewerChanged += this.OnSelectedViewerChanged;
                        OnSelectedViewerChanged(MainForm.Viewers.SelectedViewer);
                        break;

                    case WM.DESTROY:
                        this.filterMask.EndEdit();
                        this.filterMask.Close();
                        this.morphGrid.EndEdit();
                        this.morphGrid.Close();
                        MainForm.Viewers.SelectedViewerChanged -= this.OnSelectedViewerChanged;
                        break;
                }
            }
        }

        public SegmentationSelection CurrentSelection { get { return this.currentSelection; } }
        private bool MergeResult { get { return this.chkMergeResult.Checked; } }
        private bool Rotate { get { return this.chkRotate.Checked; } }
        private bool RunPCT { get { return this.chkPCT.Checked; } }

        private double Alpha { get { return double.Parse(this.cboAlpha.Text); } }
        private double Beta { get { return double.Parse(this.cboBeta.Text); } }
        private double Kappa { get { return double.Parse(this.cboKappa.Text); } }
        private double Variance { get { return double.Parse(this.cboFuzzyCVariance.Text); } }
        private double WatershedThreshold { get { return double.Parse(this.cboWatershedThreshold.Text); } }
        private double Param1
        {
            get
            {
                double param1 = 0.0;
                if (this.rbVariance.Checked || this.rbWeightedGrayLevel.Checked)
                    param1 = double.Parse(this.cboThreshold.Text);
                else if (this.rbHomogeneity.Checked)
                    param1 = double.Parse(this.cboSimilarity.Text);
                return param1;
            }
        }
        private double Param2
        {
            get
            {
                double param = 0.0;
                if (this.rbVariance.Checked)
                    param = double.Parse(this.cboPercentage.Text);
                else if (this.rbHomogeneity.Checked)
                    param = double.Parse(this.cboPixelDistance.Text);
                return param;
            }
        }

        private float AutoThreshLimit { get { return float.Parse(this.cboLimit.Text); } }
        private float HistThreshTore { get { return float.Parse(this.cbHistThresh.Text); } }
        private int BoolFunc { get { return this.cboBoolFunc.SelectedIndex + 1; } }
        private int Connectivity { get { return this.cboSkeletonConnect.SelectedIndex; } }
        private int EntryLevel { get { return int.Parse(this.cboEntryLevel.Text); } }
        private int KernelHeight { get { return int.Parse(this.cboKernelHeight.Text); } }
        private int KernelSize { get { return int.Parse(this.cboKernelSize.Text); } }
        private int KernelType { get { return this.cboKernelType.SelectedIndex + 1; } }
        private int KernelWidth { get { return int.Parse(this.cboKernelWidth.Text); } }
        private int NumColors { get { return int.Parse(this.cboNumColors.Text); } }
        private int NumColorsAAxis { get { return int.Parse(this.cboSCTAAxis.Text); } }
        private int NumColorsBAxis { get { return int.Parse(this.cboSCTBAxis.Text); } }
        private int NumGrayLevels { get { return int.Parse(this.cboNumGrayLevels.Text); } }
        private int SkeletonMethod { get { return this.cboSkeletonMethod.SelectedIndex; } }
        private int SubFields { get { return int.Parse(this.cboSubFields.Text); } }
        private int SmoothPerIter { get { return int.Parse(this.cboSmoothing.Text); } }
        private int EdgeThreshold { get { return int.Parse(this.cboEdgeThreshold.Text); } }
        private int Iterations { get { return int.Parse(this.cboIterations.Text); } }
        private int BlockSize { get { return int.Parse(this.cboBlockSize.Text); } }

        private int HomogeneityTest
        {
            get
            {
                int choice = 0;
                if (this.rbPureUniform.Checked)
                    choice = 1;
                else if (this.rbLocalMean.Checked)
                    choice = 2;
                else if (this.rbLocalStd.Checked)
                    choice = 3;
                else if (this.rbVariance.Checked)
                    choice = 4;
                else if (this.rbWeightedGrayLevel.Checked)
                    choice = 5;
                else if (this.rbHomogeneity.Checked)
                    choice = 6;
                return choice;
            }
        }
        public int MaskSize
        {
            get
            {
                int size = 0;
                if (this.rbFilterSize3x3.Checked)
                    size = 3;
                else if (this.rbFilterSize5x5.Checked)
                    size = 5;
                else if (this.rbFilterSize7x7.Checked)
                    size = 7;
                else if (this.rbFilterSize9x9.Checked)
                    size = 9;
                return size;
            }
        }

        public int maskSizeMedian
        {
            get
            {
                int mask = -1; 
                mask = int.Parse(this.cboMaskSize.Text);
                return mask; 
            }
        }
        private int NumIterations
        {
            get
            {
                int iter = 0;
                switch (this.currentSelection)
                {
                    //case SegmentationSelection.gvfSnake:
                    //    iter = int.Parse(this.cboSnakeIterations.Text);
                    //    break;

                    case SegmentationSelection.morphI:
                        if (this.cboMorphIterations.SelectedIndex != (this.cboMorphIterations.Items.Count - 1))
                            iter = int.Parse(this.cboMorphIterations.Text);
                        break;

                    case SegmentationSelection.morphSkel:
                        iter = int.Parse(this.cboSkeletonIterations.Text);
                        break;
                }
                return iter;
            }
        }
        private string Surrounds
        {
            get
            {
                StringBuilder bldr = new StringBuilder();

                if (this.chkSurround1.Checked) bldr.Append(",1");
                if (this.chkSurround2.Checked) bldr.Append(",2");
                if (this.chkSurround3.Checked) bldr.Append(",3");
                if (this.chkSurround4.Checked) bldr.Append(",4");
                if (this.chkSurround5.Checked) bldr.Append(",5");
                if (this.chkSurround6.Checked) bldr.Append(",6");
                if (this.chkSurround7.Checked) bldr.Append(",7");
                if (this.chkSurround8.Checked) bldr.Append(",8");
                if (this.chkSurround9.Checked) bldr.Append(",9");
                if (this.chkSurround10.Checked) bldr.Append(",10");
                if (this.chkSurround11.Checked) bldr.Append(",11");
                if (this.chkSurround12.Checked) bldr.Append(",12");
                if (this.chkSurround13.Checked) bldr.Append(",13");
                if (this.chkSurround14.Checked) bldr.Append(",14");

                return bldr.ToString().TrimStart(',');
            }
        }

        private void Segmentation_Load(object sender, EventArgs e)
        {

        }


        private void cboKernelSize_TextChanged(object sender, EventArgs e)
        {
            this.morphGrid.MaskSize = new Size(Int32.Parse(this.cboKernelSize.Text), Int32.Parse(this.cboKernelSize.Text));
            if(this.currentSelection == SegmentationSelection.morphC
                || this.currentSelection == SegmentationSelection.morphD
                || this.currentSelection == SegmentationSelection.morphE
                || this.currentSelection == SegmentationSelection.morphO)
            {
                if(this.KernelType == 5)
                {
                    this.morphGrid.Show();
                    this.morphGrid.Focus();
                }
            }
        }
    }
}
