/*''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' ======================================================================
' Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
' ======================================================================
'
'             File Name: EdgeDetection.cs
'           Description: Contains the controls and code
'                        for Analysis->EdgeDetection page
'         Related Files: CvipOp.cs
'                        CvipConstant.cs
'   Initial Coding Date: April 2007
'              Modified: March 2010
'       Delevoping tool: Visual Studio 2010-C#
'             Credit(s): Wenjun(Evan) Bian
'                        Patrick Solt
'                        Jhansi Lakshmi Akkineni
						Hari Siva Kumar Reddy Bhogala
'                        Southern Illinois University Edwardsville
'
' Copyright (C) 2014 Scott Umbaugh and SIUE
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
    enum EdgeDetectSelection : int
    {
        laplacian = 5,
        roberts = 6,
        sobel = 7,
        prewitt = 8,
        kirsch = 9,
        robinson = 10,
        pyramid = 11,
        freichen = 12,
        cerchar,
        marrhildreth,
        canny,
        boiecox,
        shencastan,
        moravec,
        harris,
        hough,
        edgelink,
        pratt
    }
    public partial class EdgeDetection : UserControl
    {
        private EdgeDetectSelection currentSelection = EdgeDetectSelection.roberts;

        public EdgeDetection()
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
            int dirImage = 0, magImage = 0, numbands = 0;

            switch (this.currentSelection)
            {
                case EdgeDetectSelection.roberts:
                    outputImage = CvipOp.Edge_Detect_Filter(inputImage, (int)this.currentSelection, this.PreFilter, this.RobertsType, this.KeepDC, this.PostThreshold, 0, 0, 0);
                    break;

                case EdgeDetectSelection.sobel:

                    outputImage = CvipOp.Sobel_Filter(inputImage, ref dirImage, this.PreFilter, this.KernelSize, this.KeepDC, this.PostThreshold);
                    if (this.KeepDC)
                    {
                        int tmp = outputImage;
                        outputImage = CvipOp.Add_Image(tmp, inputImage);
                        CvipOp.Delete_Image(ref tmp);
                    }
                    if (dirImage != 0)
                    {
                        // show dirImage
                        string dirImageName = viewer.Text + CvipFunctionNames.getFncName("sobel_direction");
                        dirImageName += CvipConstant.imageNameCount++.ToString();
                        MainForm.Viewers.Add(dirImage, dirImageName);
                    }
                    break;

                case EdgeDetectSelection.prewitt:

                    outputImage = CvipOp.Prewitt_Filter(inputImage, ref dirImage, this.PreFilter, this.KernelSize, this.KeepDC, this.PostThreshold);
                    if (this.KeepDC)
                    {
                        int tmp = outputImage;
                        outputImage = CvipOp.Add_Image(tmp, inputImage);
                        CvipOp.Delete_Image(ref tmp);
                    }
                    if (dirImage != 0)
                    {
                        // show dirImage
                        string dirImageName = viewer.Text + CvipFunctionNames.getFncName("prewitt_direction");
                        dirImageName += CvipConstant.imageNameCount++.ToString();
                        MainForm.Viewers.Add(dirImage, dirImageName);
                    }
                    break;

                case EdgeDetectSelection.laplacian:
                    outputImage = CvipOp.Edge_Detect_Filter(inputImage, (int)this.currentSelection, this.PreFilter, this.LaplacianMask, this.KeepDC, this.PostThreshold, 0, 0, 0);
                    break;

                case EdgeDetectSelection.kirsch:
                    outputImage = CvipOp.Kirsch_Filter(inputImage, ref dirImage, this.PreFilter, this.KernelSize, this.KeepDC, this.PostThreshold);
                    if (dirImage != 0)
                    {
                        // show dirImage
                        string dirImageName = viewer.Text + CvipFunctionNames.getFncName("kirsch_direction");
                        dirImageName += CvipConstant.imageNameCount++.ToString();
                        MainForm.Viewers.Add(dirImage, dirImageName);
                    }
                    break;

                case EdgeDetectSelection.robinson:
                    outputImage = CvipOp.Robinson_Filter(inputImage, ref dirImage, this.PreFilter, this.KernelSize, this.KeepDC, this.PostThreshold);
                    if (dirImage != 0)
                    {
                        // show dirImage
                        string dirImageName = viewer.Text + CvipFunctionNames.getFncName("robinson_direction");
                        dirImageName += CvipConstant.imageNameCount++.ToString();
                        MainForm.Viewers.Add(dirImage, dirImageName);
                    }
                    break;

                case EdgeDetectSelection.pyramid:
                    outputImage = CvipOp.Edge_Detect_Filter(inputImage, (int)this.currentSelection, this.PreFilter, 0, false, this.PostThreshold, 0, 0, 0);
                    break;

                case EdgeDetectSelection.cerchar:
                    if (viewer.Bands <= 1)
                    {
                        MessageBox.Show("This function requires a color image.", "Input Image Error",
                            MessageBoxButtons.OK, MessageBoxIcon.Warning);
                        break;
                    }
                    if (this.chkNotImage.Checked)
                    {
                        int tmp = CvipOp.Cerchar_Filter(inputImage);
                        outputImage = CvipOp.Not_Image(tmp);
                        CvipOp.Delete_Image(ref tmp);
                    }
                    else
                        outputImage = CvipOp.Cerchar_Filter(inputImage);
                    break;

                case EdgeDetectSelection.marrhildreth:
                    if (this.rbSingleVariance.Checked)
                        outputImage = CvipOp.Marr_Hildreth_Filter(inputImage, this.MarrSigma, thresholdVal);
                    else
                    {
                        int spdImage = CvipOp.Marr_Hildreth_Filter(inputImage, this.MarrSigma + this.MarrDelta, thresholdVal);
                        int smdImage = CvipOp.Marr_Hildreth_Filter(inputImage, this.MarrSigma - this.MarrDelta, thresholdVal);
                        if (this.ShowIntermediateImages)
                        {
                            if (spdImage != 0)
                            {
                                // show spdImage
                                string spdImageName = viewer.Text + CvipFunctionNames.getFncName("marrhildreth_sigma+delta");
                                spdImageName += CvipConstant.imageNameCount++.ToString();
                                MainForm.Viewers.Add(CvipOp.Duplicate_Image(spdImage), spdImageName);
                            }
                            if (smdImage != 0)
                            {
                                // show smdImage
                                string smdImageName = viewer.Text + CvipFunctionNames.getFncName("marrhildreth_sigma-delta");
                                smdImageName += CvipConstant.imageNameCount++.ToString();
                                MainForm.Viewers.Add(CvipOp.Duplicate_Image(smdImage), smdImageName);
                            }
                        }
                        outputImage = CvipOp.And_Image(spdImage, smdImage);
                        CvipOp.Delete_Image(ref spdImage);
                        CvipOp.Delete_Image(ref smdImage);
                    }
                    if ((outputImage != 0) && this.CombineBands &&
                        ((numbands = CvipOp.GetNoOfBands_Image(outputImage)) > 1))
                    {
                        int[] bands = new int[numbands];
                        for (int band = 0; band < numbands; band++)
                            bands[band] = CvipOp.Extract_Band(outputImage, band + 1);
                        CvipOp.Delete_Image(ref outputImage);

                        outputImage = bands[0];
                        for (int band = 1; band < numbands; band++)
                        {
                            int tmp = outputImage;
                            outputImage = CvipOp.And_Image(tmp, bands[band]);
                            CvipOp.Delete_Image(ref tmp);
                            CvipOp.Delete_Image(ref bands[band]);
                        }
                    }
                    break;

                case EdgeDetectSelection.canny:
                    outputImage = CvipOp.Canny_Filter(inputImage, this.LowThreshold, this.HighThreshold, this.Variance, ref magImage, ref dirImage);
                    if (this.ShowIntermediateImages)
                    {
                        if (magImage != 0)
                        {
                            // show magImage
                            string magImageName = viewer.Text + CvipFunctionNames.getFncName("canny_magnitude");
                            magImageName += CvipConstant.imageNameCount++.ToString();
                            MainForm.Viewers.Add(magImage, magImageName);
                        }
                        if (dirImage != 0)
                        {
                            // show dirImage
                            string dirImageName = viewer.Text + CvipFunctionNames.getFncName("canny_direction");
                            dirImageName += CvipConstant.imageNameCount++.ToString();
                            MainForm.Viewers.Add(dirImage, dirImageName);
                        }
                    }
                    break;

                case EdgeDetectSelection.boiecox:
                    int threshImage = 0, hystImage = 0;
                    outputImage = CvipOp.Boiecox_Filter(inputImage, this.Variance, this.DoThreshold, this.DoHyst, this.ThinningEdge, this.HighThreshold, this.LowThreshold, ref threshImage, ref hystImage);
                    if (this.ShowIntermediateImages)
                    {
                        if (threshImage != 0)
                        {
                            // show threshImage
                            string threshImageName = viewer.Text + CvipFunctionNames.getFncName("boiecox_threshold");
                            threshImageName += CvipConstant.imageNameCount++.ToString();
                            MainForm.Viewers.Add(threshImage, threshImageName);
                        }
                        if (this.DoHyst && (hystImage != 0))
                        {
                            // show hystImage
                            string hystImageName = viewer.Text + CvipFunctionNames.getFncName("boiecox_hyst");
                            hystImageName += CvipConstant.imageNameCount++.ToString();
                            MainForm.Viewers.Add(hystImage, hystImageName);
                        }
                    }
                    break;

                case EdgeDetectSelection.shencastan:
                    if (this.WindowSize > 21)
                    {
                        MessageBox.Show("Currently the maximum window size is limited to 21.",
                            "Range error!", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                        break;
                    }
                    int zeroImage = 0;
                    outputImage = CvipOp.Shen_Castan_Filter(inputImage, this.SmoothingFactor, this.WindowSize, this.LowThreshold, this.HighThreshold, this.ThinFactor, ref zeroImage);
                    if (this.ShowIntermediateImages && (zeroImage != 0))
                    {
                        // show zeroImage
                        string zeroImageName = viewer.Text + CvipFunctionNames.getFncName("shencastan_zerointer");
                        zeroImageName += CvipConstant.imageNameCount++.ToString();
                        MainForm.Viewers.Add(zeroImage, zeroImageName);
                    }
                    break;

                case EdgeDetectSelection.freichen:
                    outputImage = CvipOp.Edge_Detect_Filter(inputImage, (int)this.currentSelection, this.FreiChenPreFilter, 0, this.KeepDC, this.FreiChenPostThreshold, this.ProjectionMethod, this.ProjectionThreshold, this.ThresholdAngle);
                    break;

                case EdgeDetectSelection.moravec:
                    outputImage = CvipOp.Moravec_Corner_Filter(inputImage, this.MoravecThreshold);
                    break;

                case EdgeDetectSelection.harris:
                    outputImage = CvipOp.Harris_Corner_Filter(inputImage, this.HarrisAlpha, this.HarrisThreshold, this.HarrisBorder, this.HarrisMinDistance);
                    break;

                case EdgeDetectSelection.hough:
                    numbands = CvipOp.GetNoOfBands_Image(inputImage);
                    if (numbands != 1)
                    {
                        MessageBox.Show("One Band Binary Image Required!", "Incorrect Input!",
                            MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    }
                    else
                    {
                        outputImage = CvipOp.Hough_Filter(inputImage, "", this.cboLineAngles.Text, this.LinePixels, this.ConnectDistance, 0, this.DeltaLength, this.SegmentPixels, this.IntermediateResult);
                    }
                    break;

                case EdgeDetectSelection.edgelink:
                    outputImage = CvipOp.Edge_Link_Filter(inputImage, this.ConnectDistance);
                    break;

                case EdgeDetectSelection.pratt:
                    ViewerForm viewer1 = (ViewerForm)this.txtCurrentImg.Tag;
                    ViewerForm viewer2 = (ViewerForm)this.cboSecondImg.SelectedItem;



                    // get the image(s) that will be operated on
                    int idealImage = viewer1.CVIPimage;
                    int edgeDetectImage = viewer2.CVIPimage;

                    //ViewerForm viewerIdeal = this.cboIdealImage.SelectedItem as ViewerForm;
                    // ViewerForm viewerEdgeDetect = this.cboEdgeDetectImage.SelectedItem as ViewerForm;
                    if ((viewer1 == null) || (viewer2 == null))
                    {
                        MessageBox.Show("Please give an ideal and an edge-detected image!", "Missing input image!",
                            MessageBoxButtons.OK, MessageBoxIcon.Warning);
                        break;
                    }
                    //  int idealImage = viewerIdeal.CVIPimage;
                    // int edgeDetectImage = viewerEdgeDetect.CVIPimage;
                    if (!CvipOp.Check_Bin(idealImage) || !CvipOp.Check_Bin(edgeDetectImage))
                    {
                        CvipOp.Delete_Image(ref idealImage);
                        CvipOp.Delete_Image(ref edgeDetectImage);
                        MessageBox.Show("Please input an binary image. You can get a binary image by thresholding an image",
                            "Image input error", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                        break;
                    }
                    this.pnlPrattResultRGB.Visible = false;
                    this.txtPrattResultGS.Text = "Working...";
                    this.txtPrattResultGS.Visible = true;
                    Update();
                    string[] tokens = (this.cboScaleFactor.Text + "/1").Split(new char[] { '/' });
                    double num = double.Parse(tokens[0]);
                    double dem = double.Parse(tokens[1]);
                    double[] result = CvipOp.Pratt_Merit(idealImage, edgeDetectImage, num / dem);
                    if (result.Length == 1)
                        this.txtPrattResultGS.Text = result[0].ToString("0.000000");
                    else
                    {
                        this.txtPrattResultGS.Visible = false;
                        this.txtPrattResultR.Text = result[0].ToString("0.000000");
                        this.txtPrattResultG.Text = result[1].ToString("0.000000");
                        this.txtPrattResultB.Text = result[2].ToString("0.000000");
                        this.pnlPrattResultRGB.Visible = true;
                    }
                    CvipOp.Delete_Image(ref idealImage);
                    CvipOp.Delete_Image(ref edgeDetectImage);
                    break;
            }
            if (outputImage != 0)
            {
                string newImageName = viewer.Text + "_" + CvipFunctionNames.getFncName(this.currentSelection.ToString());
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
        private void btnShowMask_Click(object sender, EventArgs e)
        {
            StringBuilder bldr = new StringBuilder();
            bldr.AppendLine("  Mask 1:    Mask 2:    Mask 3:   (Without DC)");
            bldr.AppendLine("  0 -1  0     -1 -1 -1     -2  1 -2");
            bldr.AppendLine(" -1  4 -1     -1  8 -1      1  4  1");
            bldr.AppendLine("  0 -1  0     -1 -1 -1     -2  1 -2");
            bldr.AppendLine();
            bldr.AppendLine("  Mask 1:    Mask 2:    Mask 3:   (With DC)");
            bldr.AppendLine("  0 -1  0     -1 -1 -1     -2  1 -2");
            bldr.AppendLine(" -1  5 -1     -1  9 -1      1  5  1");
            bldr.AppendLine("  0 -1  0     -1 -1 -1     -2  1 -2");
            MessageBox.Show(bldr.ToString(), "Analysis: Edge/Line Detection: Laplacian",
                MessageBoxButtons.OK, MessageBoxIcon.None);
        }
        private void btnShowType_Click(object sender, EventArgs e)
        {
            StringBuilder bldr = new StringBuilder();
            bldr.AppendLine("Type 1: Regular gradient");
            bldr.AppendLine("G[I(r,c)] ={[I(r,c)-I(r+1,c+1)]^2 + [I(r+1,c)-I(r,c+1)]^2}^1/2");
            bldr.AppendLine();
            bldr.AppendLine("Type 2: Roberts gradient");
            bldr.AppendLine("G[I(r,c)] = |I(r,c)-I(r+1,c+1)| + |I(r+1,c)-I(r,c+1)|");
            MessageBox.Show(bldr.ToString(), "Analysis: Edge/Line Detection: Roberts",
                MessageBoxButtons.OK, MessageBoxIcon.None);
        }
        private void btnThreshold_Click(object sender, EventArgs e)
        {
            ViewerForm viewer = MainForm.Viewers.SelectedViewer;
            if (viewer == null)
            {
                MessageBox.Show("Please give an input image!", "No input image!",
                    MessageBoxButtons.OK, MessageBoxIcon.Warning);
                return;
            }
            this.btnThreshold.Enabled = false;
            this.Cursor = Cursors.WaitCursor;

            // get the image that will be operated on
            int inputImage = viewer.CVIPimage;
            int outputImage = CvipOp.Threshold_Segment(inputImage, this.ThresholdValue, false);
            if (outputImage != 0)
            {
                string newImageName = viewer.Text;
                newImageName += "_Threshold";
                newImageName += CvipConstant.imageNameCount++.ToString();
                MainForm.Viewers.Add(outputImage, newImageName);
            }
            // delete input image
            CvipOp.Delete_Image(ref inputImage);

            // enable Threshold button
            this.btnThreshold.Enabled = true;
            this.Cursor = Cursors.Default;
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
        private void cboLineAngles_Validating(object sender, CancelEventArgs e)
        {
            int val;
            foreach (string token in this.cboLineAngles.Text.Split(new char[] { ' ', '\t' }))
            {
                foreach (string subtoken in token.Split(new char[] { '-' }))
                {
                    if (!string.IsNullOrEmpty(subtoken) && !int.TryParse(subtoken, out val))
                    {
                        MessageBox.Show("You may specify ranges of angles with a dash, such as 45-55, and you must use a blank space as a separator, as in 0 45-50 90.",
                           "Line Angle Input Error", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                        this.cboLineAngles.SelectAll();
                        e.Cancel = true;
                        return;
                    }
                }
            }
        }
        private void cboMarrDelta_Validating(object sender, CancelEventArgs e)
        {
            float val;
            if (!float.TryParse(this.cboMarrDelta.Text, out val) || (val > 1.0))
            {
                MessageBox.Show("Please check the input value. Only floats <= 1.0 are accepted.",
                   "Float Required", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                this.cboMarrDelta.SelectAll();
                e.Cancel = true;
            }
        }
        private void cboPostThreshold_Validating(object sender, CancelEventArgs e)
        {
            if (this.cboPostThreshold.SelectedIndex != 0)
            {
                int val;
                if (!int.TryParse(this.cboPostThreshold.Text, out val))
                {
                    MessageBox.Show("Please check the input value. Only integers are accepted.",
                       "Integer Required", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    this.cboPostThreshold.SelectAll();
                    e.Cancel = true;
                }
            }
        }
        private void cboPrattImage_SelectedIndexChanged(object sender, EventArgs e)
        {
            ComboBox cbo = sender as ComboBox;
            ViewerForm selected = cbo.SelectedItem as ViewerForm;
            if (selected != null) selected.Activate();
        }
        private void cboProjectionMethod_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (this.cboProjectionMethod.SelectedIndex < 2)
            {
                this.chkThresholdAngle.Visible = true;
                if (this.chkThresholdAngle.Checked == true)
                {
                    this.cboThresholdAngle.Visible = true;
                    this.lblThresholdAngle.Visible = true;
                }
            }
            else
            {
                this.chkThresholdAngle.Visible
                    = this.cboThresholdAngle.Visible
                    = this.lblThresholdAngle.Visible
                    = false;
            }
        }
        private void cboSmoothingFactor_Validating(object sender, CancelEventArgs e)
        {
            double val;
            if (!double.TryParse(this.cboSmoothingFactor.Text, out val))
            {
                MessageBox.Show("Please check the input value. Only double values are accepted.",
                   "Double Required", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                this.cboSmoothingFactor.SelectAll();
                e.Cancel = true;
            }
            else if ((val <= 0.0) || (val >= 1.0))
            {
                MessageBox.Show("Please check the input value. Valid range is (0.0, 1.0).",
                   "Range Error", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                this.cboSmoothingFactor.SelectAll();
                e.Cancel = true;
            }
        }
        private void cboThresholdValue_Validating(object sender, CancelEventArgs e)
        {
            ComboBox cbo = sender as ComboBox;
            double val;
            if (!double.TryParse(cbo.Text, out val))
            {
                MessageBox.Show("Please check the input value. Only double values are accepted.",
                   "Double Required", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                cbo.SelectAll();
                e.Cancel = true;
            }
            else if (val < 0.0)
            {
                MessageBox.Show("Please check the input value. Valid range is positive numbers.",
                   "Range Error", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                cbo.SelectAll();
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
        private void cboVarianceValue_Validating(object sender, CancelEventArgs e)
        {
            ComboBox cbo = sender as ComboBox;
            double val;
            if (!double.TryParse(cbo.Text, out val))
            {
                MessageBox.Show("Please check the input value. Only double values are accepted.",
                   "Double Required", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                cbo.SelectAll();
                e.Cancel = true;
            }
            else if ((val < 0.5) || (val > 5.0))
            {
                MessageBox.Show("Please check the input value. Valid range is [0.5, 5.0].",
                   "Range Error", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                cbo.SelectAll();
                e.Cancel = true;
            }
        }
        private void chkThresholdAngle_CheckedChanged(object sender, EventArgs e)
        {
            this.cboThresholdAngle.Visible = this.lblThresholdAngle.Visible = this.chkThresholdAngle.Checked;
        }
        public void Init(string op)
        {


            if (MainForm.Viewers != null)
            {
                OnSelectedViewerChanged(MainForm.Viewers.SelectedViewer);
                OnViewerCollectionChanged();
            }
        }
        protected override void OnLoad(EventArgs e)
        {
            base.OnLoad(e);

            this.rbRoberts.Tag = EdgeDetectSelection.roberts;
            this.rbSobel.Tag = EdgeDetectSelection.sobel;
            this.rbPrewitt.Tag = EdgeDetectSelection.prewitt;
            this.rbLaplacian.Tag = EdgeDetectSelection.laplacian;
            this.rbKirsch.Tag = EdgeDetectSelection.kirsch;
            this.rbRobinson.Tag = EdgeDetectSelection.robinson;
            this.rbPyramid.Tag = EdgeDetectSelection.pyramid;
            this.rbCerchar.Tag = EdgeDetectSelection.cerchar;
            this.rbMarrHildreth.Tag = EdgeDetectSelection.marrhildreth;
            this.rbCanny.Tag = EdgeDetectSelection.canny;
            this.rbBoieCox.Tag = EdgeDetectSelection.boiecox;
            this.rbShenCastan.Tag = EdgeDetectSelection.shencastan;
            this.rbFreiChen.Tag = EdgeDetectSelection.freichen;
            this.rbMoravec.Tag = EdgeDetectSelection.moravec;
            this.rbHarris.Tag = EdgeDetectSelection.harris;
            this.rbHough.Tag = EdgeDetectSelection.hough;
            this.rbEdgeLink.Tag = EdgeDetectSelection.edgelink;
            this.rbPratt.Tag = EdgeDetectSelection.pratt;

            OnSelectedViewerChanged(MainForm.Viewers.SelectedViewer);
            OnViewerCollectionChanged();


            ResetControls();
        }
        private void OnSelectedViewerChanged(ViewerForm viewer)
        {
            if (MainForm.Viewers != null)
            {
                if ((ModifierKeys & Keys.Alt) == Keys.Alt)
                {
                    this.cboSecondImg.SelectedItem = viewer;
                }
                else
                {
                    this.txtCurrentImg.Tag = viewer;
                    this.txtCurrentImg.Text = "";
                    if (viewer != null)
                        this.txtCurrentImg.Text = viewer.Text;
                }
            }
        }
        private void cboSecondImage_DrawItem(object sender, DrawItemEventArgs e)
        {
            this.toolTipImage2.RemoveAll();
            // MessageBox.Show(cboSecondImg.Items.Count.ToString());
            if (cboSecondImg.Items.Count != 0 && e.Index != -1)
            {
                string text = this.cboSecondImg.GetItemText(cboSecondImg.Items[e.Index]);
                e.DrawBackground();
                using (SolidBrush br = new SolidBrush(e.ForeColor))
                {
                    e.Graphics.DrawString(text, e.Font, br, e.Bounds);
                }
                if ((e.State & DrawItemState.Selected) == DrawItemState.Selected)
                {
                    this.toolTipImage2.Show(text, cboSecondImg, e.Bounds.Right, e.Bounds.Bottom);
                }
                else
                {
                    this.toolTipImage2.Hide(cboSecondImg);
                }
                e.DrawFocusRectangle();
            }
        }
        private void cboSecondImage_SelectedIndexChanged(object sender, EventArgs e)
        {
            this.toolTipImage2.RemoveAll();
            this.toolTipImage2.Hide(this.cboSecondImg);
        }
        private void OnViewerCollectionChanged()
        {
            ViewerForm viewer1 = MainForm.Viewers.SelectedViewer;
            this.txtCurrentImg.Tag = viewer1;
            this.txtCurrentImg.Text = "";
            if (viewer1 != null)
                this.txtCurrentImg.Text = viewer1.Text;
            if (MainForm.Viewers != null)
            {
                ViewerForm selected = this.cboSecondImg.SelectedItem as ViewerForm;
                if (selected == null) selected = MainForm.Viewers.SelectedViewer;
                this.cboSecondImg.Items.Clear();
                foreach (ViewerForm viewer in MainForm.Viewers)
                    this.cboSecondImg.Items.Add(viewer);
                this.cboSecondImg.SelectedItem = selected;
            }
        }
        private void rbBoieThreshold_CheckedChanged(object sender, EventArgs e)
        {
            RadioButton rb = sender as RadioButton;
            if ((rb != null) && rb.Checked)
            {
                this.cboBoieLoThresh.Visible = this.lblBoieLoThresh.Visible = this.DoHyst;
                if (this.DoThreshold)
                    this.lblBoieHiThresh.Text = "Threshold factor";
                else
                    this.lblBoieHiThresh.Text = "High threshold factor";
            }
        }
        private void rbEdgeDetection_CheckedChanged(object sender, EventArgs e)
        {
            RadioButton rb = sender as RadioButton;
            if ((rb != null) && rb.Checked && (rb.Tag != null))
            {
                this.currentSelection = (EdgeDetectSelection)rb.Tag;
                UpdateControls();
            }
        }
        private void rbMarrVariance_CheckedChanged(object sender, EventArgs e)
        {
            RadioButton rb = sender as RadioButton;
            if ((rb != null) && rb.Checked)
                this.cboMarrDelta.Visible = this.lblMarrDelta.Visible = this.chkShowImages.Visible = this.rbDualVariance.Checked;
        }
        private void ResetControls()
        {
            // Roberts group
            this.chkNotImage.Checked = true;
            this.cboThreshold.Text = "128";

            // Roberts panel
            this.cboLaplacianMask.SelectedIndex = 0;
            this.cboRobertsType.SelectedIndex = 0;
            this.cboKernelSize.Text = "3";
            this.cboPostThreshold.SelectedIndex = 0;
            this.chkKeepDC.Checked = false;
            this.cboPreFilter.SelectedIndex = 0;

            // Marr-Hildreth group
            this.chkShowImages.Checked = false;

            // Frei-Chen panel
            this.cboFreiChenPostThresh.SelectedIndex = 0;
            this.cboThresholdAngle.Text = "45";
            this.cboProjectionMethod.SelectedIndex = 2;
            this.cboFreiChenPreFilter.SelectedIndex = 0;
            this.chkThresholdAngle.Checked = true;
            this.chkFrieKeepDC.Checked = false;

            // Marr-Hildreth panel
            this.chkCombineBands.Checked = false;
            this.cboMarrDelta.Text = "0.8";
            this.cboMarrSigma.Text = "2.0";
            this.rbSingleVariance.Checked = true;
            this.cboThresholdValue.Text = "0";

            // Canny panel
            this.cboCannyVariance.Text = "0.5";
            this.cboCannyHiThresh.Text = "1.0";
            this.cboCannyLoThresh.Text = "1.0";

            // Boie-Cox panel
            this.chkThinEdge.Checked = false;
            this.cboBoieVariance.Text = "1.0";
            this.cboBoieHiThresh.Text = "1.0";
            this.cboBoieLoThresh.Text = "0.2";
            this.rbOrdinaryThreshold.Checked = true;

            // Shen-Castan panel
            this.cboThinFactor.Text = "1";
            this.cboWindowSize.Text = "5";
            this.cboSmoothingFactor.Text = "0.9";
            this.cboShenHiThresh.Text = "1.0";
            this.cboShenLoThresh.Text = "1.0";

            // Moravec panel
            this.cboMoravecThreshold.Text = "32.0";

            // Edge-Link panel
            this.cboEdgeLinkConnectDistance.Text = "2";

            // Pratt Merit panel
            this.cboScaleFactor.SelectedIndex = 0;
            this.pnlPrattResultRGB.Visible = false;
            this.txtPrattResultGS.Text = "";
            this.txtPrattResultGS.Visible = true;

            // Harris panel
            this.cboHarrisMinDistance.Text = "10.0";
            this.cboHarrisAlpha.Text = "0.05";
            this.cboHarrisBorder.Text = "20";
            this.cboHarrisThreshold.Text = "20000";

            // Hough panel
            this.cboIntermediateResult.SelectedIndex = 4;
            this.cboSegmentPixels.Text = "10";
            this.cboLinePixels.Text = "20";
            this.cboHoughConnectDistance.Text = "2";
            this.cboDeltaLength.Text = "1";
            this.cboLineAngles.Text = "0";

            // Default current selection
            this.currentSelection = EdgeDetectSelection.roberts;
            this.rbRoberts.Checked = true;
            UpdateControls();
        }
        private void UpdateControls()
        {
            switch (this.currentSelection)
            {
                case EdgeDetectSelection.roberts:
                case EdgeDetectSelection.laplacian:
                    this.pnlRoberts.Visible = true;
                    this.cboPreFilter.Visible = this.lblPreFilter.Visible = true;
                    this.cboPostThreshold.Visible = this.lblPostThreshold.Visible = true;
                    this.cboKernelSize.Visible = this.lblKernelSize.Visible = false;
                    this.btnShowType.Visible = this.cboRobertsType.Visible = this.lblRobertsType.Visible = (this.currentSelection == EdgeDetectSelection.roberts);
                    this.btnShowMask.Visible = this.cboLaplacianMask.Visible = this.lblLaplacianMask.Visible = (this.currentSelection == EdgeDetectSelection.laplacian);
                    this.chkKeepDC.Visible = true;
                    this.chkNotImage.Visible = false;
                    this.pnlMarr.Visible = false;
                    this.pnlMoravec.Visible = false;
                    this.cboThresholdValue.Visible = false;
                    this.lblThresholdVal.Visible = false;
                    break;

                case EdgeDetectSelection.sobel:
                case EdgeDetectSelection.prewitt:
                    this.pnlRoberts.Visible = true;
                    this.cboPreFilter.Visible = this.lblPreFilter.Visible = true;
                    this.cboPostThreshold.Visible = this.lblPostThreshold.Visible = true;
                    this.cboKernelSize.Visible = this.lblKernelSize.Visible = true;
                    this.btnShowType.Visible = this.cboRobertsType.Visible = this.lblRobertsType.Visible = false;
                    this.btnShowMask.Visible = this.cboLaplacianMask.Visible = this.lblLaplacianMask.Visible = false;
                    this.chkKeepDC.Visible = true;
                    this.chkNotImage.Visible = false;
                    this.pnlMarr.Visible = false;
                    this.pnlMoravec.Visible = false;
                    this.cboThresholdValue.Visible = false;
                    this.lblThresholdVal.Visible = false;
                    break;

                case EdgeDetectSelection.kirsch:
                case EdgeDetectSelection.robinson:
                case EdgeDetectSelection.pyramid:
                    this.pnlRoberts.Visible = true;
                    this.cboPreFilter.Visible = this.lblPreFilter.Visible = true;
                    this.cboPostThreshold.Visible = this.lblPostThreshold.Visible = true;
                    this.cboKernelSize.Visible = this.lblKernelSize.Visible = false;
                    this.btnShowType.Visible = this.cboRobertsType.Visible = this.lblRobertsType.Visible = false;
                    this.btnShowMask.Visible = this.cboLaplacianMask.Visible = this.lblLaplacianMask.Visible = false;
                    this.chkKeepDC.Visible = false;
                    this.chkNotImage.Visible = false;
                    this.pnlMarr.Visible = false;
                    this.pnlMoravec.Visible = false;
                    this.cboThresholdValue.Visible = false;
                    this.lblThresholdVal.Visible = false;
                    break;

                case EdgeDetectSelection.cerchar:
                    this.pnlRoberts.Visible = false;
                    this.pnlMarr.Visible = false;
                    this.pnlMoravec.Visible = false;
                    this.chkNotImage.Visible = true;
                    this.cboThresholdValue.Visible = false;
                    this.lblThresholdVal.Visible = false;
                    break;

                case EdgeDetectSelection.marrhildreth:
                    this.cboThresholdValue.Visible = true;
                    this.lblThresholdVal.Visible = true;
                    this.pnlMarr.Visible = true;
                    this.chkShowImages.Visible = true;
                    this.pnlMarrHildreth.Visible = (this.currentSelection == EdgeDetectSelection.marrhildreth);
                    this.pnlCanny.Visible = (this.currentSelection == EdgeDetectSelection.canny);
                    this.pnlBoieCox.Visible = (this.currentSelection == EdgeDetectSelection.boiecox);
                    this.pnlShenCastan.Visible = (this.currentSelection == EdgeDetectSelection.shencastan);
                    if (this.pnlMarrHildreth.Visible)
                    {
                        this.cboMarrDelta.Visible
                            = this.lblMarrDelta.Visible
                            = this.chkShowImages.Visible
                            = this.rbDualVariance.Checked;
                    }
                    else if (this.pnlBoieCox.Visible)
                    {
                        this.cboBoieLoThresh.Visible = this.lblBoieLoThresh.Visible = this.DoHyst;
                        if (this.DoThreshold)
                            this.lblBoieHiThresh.Text = "Threshold factor";
                        else
                            this.lblBoieHiThresh.Text = "High threshold factor";
                    }
                    this.pnlFrieChen.Visible = false;
                    this.chkNotImage.Visible = false;
                    this.pnlRoberts.Visible = false;
                    this.pnlMoravec.Visible = false;
                    break;

                case EdgeDetectSelection.canny:
                case EdgeDetectSelection.boiecox:
                case EdgeDetectSelection.shencastan:
                    this.pnlMarr.Visible = true;
                    this.chkShowImages.Visible = true;
                    this.pnlMarrHildreth.Visible = (this.currentSelection == EdgeDetectSelection.marrhildreth);
                    this.pnlCanny.Visible = (this.currentSelection == EdgeDetectSelection.canny);
                    this.pnlBoieCox.Visible = (this.currentSelection == EdgeDetectSelection.boiecox);
                    this.pnlShenCastan.Visible = (this.currentSelection == EdgeDetectSelection.shencastan);
                    if (this.pnlMarrHildreth.Visible)
                    {
                        this.cboMarrDelta.Visible
                            = this.lblMarrDelta.Visible
                            = this.chkShowImages.Visible
                            = this.rbDualVariance.Checked;
                    }
                    else if (this.pnlBoieCox.Visible)
                    {
                        this.cboBoieLoThresh.Visible = this.lblBoieLoThresh.Visible = this.DoHyst;
                        if (this.DoThreshold)
                            this.lblBoieHiThresh.Text = "Threshold factor";
                        else
                            this.lblBoieHiThresh.Text = "High threshold factor";
                    }
                    this.pnlFrieChen.Visible = false;
                    this.chkNotImage.Visible = false;
                    this.pnlRoberts.Visible = false;
                    this.pnlMoravec.Visible = false;
                    this.cboThresholdValue.Visible = false;
                    this.lblThresholdVal.Visible = false;
                    break;

                case EdgeDetectSelection.freichen:
                    this.pnlRoberts.Visible = false;
                    this.cboPreFilter.Visible = this.lblPreFilter.Visible = false;
                    this.cboPostThreshold.Visible = this.lblPostThreshold.Visible = true;
                    this.cboKernelSize.Visible = this.lblKernelSize.Visible = false;
                    this.btnShowType.Visible = this.cboRobertsType.Visible = this.lblRobertsType.Visible = false;
                    this.btnShowMask.Visible = this.cboLaplacianMask.Visible = this.lblLaplacianMask.Visible = false;
                    this.chkKeepDC.Visible = false;
                    this.chkNotImage.Visible = false;
                    this.pnlMarr.Visible = true;
                    this.chkShowImages.Visible = false;
                    this.pnlMarrHildreth.Visible = false;
                    this.pnlCanny.Visible = false;
                    this.pnlBoieCox.Visible = false;
                    this.pnlShenCastan.Visible = false;
                    this.pnlFrieChen.Visible = true;
                    this.chkThresholdAngle.Visible = (this.cboProjectionMethod.SelectedIndex < 2);
                    this.cboThresholdAngle.Visible = this.lblThresholdAngle.Visible
                        = (this.chkThresholdAngle.Visible && this.chkThresholdAngle.Checked);
                    this.cboThresholdValue.Visible = false;
                    this.lblThresholdVal.Visible = false;
                    //this.btnThreshold.Visible = false;
                    //this.cboThreshold.Visible = false;

                    this.pnlMoravec.Visible = false;
                    break;

                case EdgeDetectSelection.moravec:
                case EdgeDetectSelection.harris:
                case EdgeDetectSelection.hough:
                case EdgeDetectSelection.edgelink:
                case EdgeDetectSelection.pratt:
                    this.pnlMoravec.Visible = true;
                    this.pnlMoravecDetector.Visible = (this.currentSelection == EdgeDetectSelection.moravec);
                    this.pnlHarris.Visible = (this.currentSelection == EdgeDetectSelection.harris);
                    this.pnlHough.Visible = (this.currentSelection == EdgeDetectSelection.hough);
                    this.pnlEdgeLink.Visible = (this.currentSelection == EdgeDetectSelection.edgelink);
                    this.pnlPratt.Visible = (this.currentSelection == EdgeDetectSelection.pratt);
                    this.chkNotImage.Visible = false;
                    this.pnlRoberts.Visible = false;
                    this.pnlMarr.Visible = false;
                    this.cboThresholdValue.Visible = false;
                    this.lblThresholdVal.Visible = false;
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
                        break;

                    case WM.DESTROY:
                        MainForm.Viewers.SelectedViewerChanged -= this.OnSelectedViewerChanged;
                        MainForm.Viewers.ViewerCollectionChanged -= this.OnViewerCollectionChanged;
                        break;
                }
            }
        }


        private int thresholdVal { get { return int.Parse(this.cboThresholdValue.Text); } }

        private bool CombineBands { get { return this.chkCombineBands.Checked; } }
        private bool DoHyst { get { return this.rbHysteresisThreshold.Checked; } }
        private bool DoThreshold { get { return this.rbOrdinaryThreshold.Checked; } }
        private bool ShowIntermediateImages { get { return this.chkShowImages.Checked; } }
        private bool ThinningEdge { get { return this.chkThinEdge.Checked; } }

        private double SmoothingFactor { get { return double.Parse(this.cboSmoothingFactor.Text); } }

        private float HarrisAlpha { get { return float.Parse(this.cboHarrisAlpha.Text); } }
        private float HarrisMinDistance { get { return float.Parse(this.cboHarrisMinDistance.Text); } }
        private float MarrDelta { get { return float.Parse(this.cboMarrDelta.Text); } }
        private float MarrSigma { get { return float.Parse(this.cboMarrSigma.Text); } }
        private float MoravecThreshold { get { return float.Parse(this.cboMoravecThreshold.Text); } }

        private int DeltaLength { get { return int.Parse(this.cboDeltaLength.Text); } }
        private int HarrisBorder { get { return int.Parse(this.cboHarrisBorder.Text); } }
        private int HarrisThreshold { get { return int.Parse(this.cboHarrisThreshold.Text); } }
        private int IntermediateResult { get { return this.cboIntermediateResult.SelectedIndex + 1; } }
        private int KernelSize { get { return int.Parse(this.cboKernelSize.Text); } }
        private int LaplacianMask { get { return this.cboLaplacianMask.SelectedIndex; } }
        private int LinePixels { get { return int.Parse(this.cboLinePixels.Text); } }
        private int PreFilter { get { return this.cboPreFilter.SelectedIndex; } }
        private int ProjectionMethod { get { return Math.Min(this.cboProjectionMethod.SelectedIndex + 1, 3); } }
        private int RobertsType { get { return this.cboRobertsType.SelectedIndex + 1; } }
        private int SegmentPixels { get { return int.Parse(this.cboSegmentPixels.Text); } }
        private int ThinFactor { get { return int.Parse(this.cboThinFactor.Text); } }
        private int ThresholdAngle { get { return int.Parse(this.cboThresholdAngle.Text); } }
        private int ThresholdValue { get { return int.Parse(this.cboThreshold.Text); } }
        private int WindowSize { get { return int.Parse(this.cboWindowSize.Text); } }
        private int FreiChenPreFilter { get { return this.cboFreiChenPreFilter.SelectedIndex; } }

        private int ConnectDistance
        {
            get
            {
                int val = 0;
                switch (this.currentSelection)
                {
                    case EdgeDetectSelection.edgelink:
                        val = int.Parse(this.cboEdgeLinkConnectDistance.Text);
                        break;
                    case EdgeDetectSelection.hough:
                        val = int.Parse(this.cboHoughConnectDistance.Text);
                        break;
                }
                return val;
            }
        }
        private int FreiChenPostThreshold
        {
            get
            {
                int val = -1;
                if (this.cboFreiChenPostThresh.SelectedIndex != 0)
                    val = int.Parse(this.cboFreiChenPostThresh.Text);
                return val;
            }
        }
        private double HighThreshold
        {
            get
            {
                double val = 0.0;
                switch (this.currentSelection)
                {
                    case EdgeDetectSelection.boiecox:
                        val = double.Parse(this.cboBoieHiThresh.Text);
                        break;
                    case EdgeDetectSelection.canny:
                        val = double.Parse(this.cboCannyHiThresh.Text);
                        break;
                    case EdgeDetectSelection.shencastan:
                        val = double.Parse(this.cboShenHiThresh.Text);
                        break;
                }
                return val;
            }
        }
        private bool KeepDC
        {
            get
            {
                if (this.currentSelection == EdgeDetectSelection.freichen)
                    return this.chkFrieKeepDC.Checked;
                return this.chkKeepDC.Checked;
            }
        }
        private double LowThreshold
        {
            get
            {
                double val = 0.0;
                switch (this.currentSelection)
                {
                    case EdgeDetectSelection.boiecox:
                        if (this.DoThreshold) val = double.Parse(this.cboBoieLoThresh.Text);
                        break;
                    case EdgeDetectSelection.canny:
                        val = double.Parse(this.cboCannyLoThresh.Text);
                        break;
                    case EdgeDetectSelection.shencastan:
                        val = double.Parse(this.cboShenLoThresh.Text);
                        break;
                }
                return val;
            }
        }
        private int PostThreshold
        {
            get
            {
                int val = -1;
                if (this.cboPostThreshold.SelectedIndex != 0)
                    val = int.Parse(this.cboPostThreshold.Text);
                return val;
            }
        }
        private int ProjectionThreshold
        {
            get
            {
                int val = 0;
                if (this.chkThresholdAngle.Checked &&
                    (this.cboProjectionMethod.SelectedIndex < 2))
                {
                    val = this.cboProjectionMethod.SelectedIndex + 1;
                }
                return val;
            }
        }
        private double Variance
        {
            get
            {
                double val = 0.0;
                switch (this.currentSelection)
                {
                    case EdgeDetectSelection.boiecox:
                        val = double.Parse(this.cboBoieVariance.Text);
                        break;
                    case EdgeDetectSelection.canny:
                        val = double.Parse(this.cboCannyVariance.Text);
                        break;
                }
                return val;
            }
        }
    }
}
