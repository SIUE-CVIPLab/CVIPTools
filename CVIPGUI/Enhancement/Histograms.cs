/*''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' ======================================================================
' Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
' ======================================================================
'
'             File Name: Histograms.cs
'           Description: Contains the controls and code
'                        for Enhancement->Histograms tab
'         Related Files: CvipOp.cs
'                        CvipConstant.cs
'   Initial Coding Date: June 2007
'              Modified: November 2011
 *             Modified: August 2013 
'       Delevoping tool: Visual Studio 2010-C#
'             Credit(s): Wenjun(Evan) Bian
'                        Patrick Solt
 *                       Hari Siva Kumar Reddy Bhogala
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
    enum HistSelection
    {
        HistEQ,
        HistSlide,
        HistStretch,
        HistShrink,
        LocalEQ,
        CLAHE,
        ACE,
        ACEII,
        logACE,
        expACE,
        ColorEnhancement,
        HistSpec,
        LinearMod,
        GrayLevelMult
    }

    public partial class Histograms : UserControl
    {
        private HistSelection currentSelection;

        public Histograms()
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
           // this.btnApply.Enabled = false;
           
            this.Cursor = Cursors.WaitCursor;
            // get the image that will be operated on
           
            int inputImage = viewer.CVIPimage, outputImage = 0;
            
           
            switch (this.currentSelection)
            {
            case HistSelection.HistEQ:
                outputImage = CvipOp.Histogram_Equalization(inputImage, this.EqBand);
                break;

            case HistSelection.HistSlide:
                outputImage = CvipOp.Histogram_Slide(inputImage, this.Slide);
                break;

            case HistSelection.HistStretch:
                outputImage = CvipOp.Histogram_Stretch(inputImage,  this.LowLimit, this.HighLimit, this.LowClip, this.HighClip);
                break;

            case HistSelection.HistShrink:
                outputImage = CvipOp.Histogram_Stretch(inputImage, this.LowLimit, this.HighLimit, 0, 0);
                break;

            case HistSelection.LocalEQ:
                outputImage = CvipOp.Histogram_Local_Equalization(inputImage, this.BlockSize, this.EqBand);
                break;

             case HistSelection.CLAHE:
                    if(this.CLAHECheckBox.Checked == true)
                        outputImage = CvipOp.CLAHE(inputImage, this.BlockSize, this.CLAHEClip, this.EqBand);
                    else
                        outputImage = CvipOp.CLAHE_Grid(inputImage, this.BlockSize, this.CLAHEClip, this.EqBand);
                    break;

            case HistSelection.ACE:
                outputImage = CvipOp.Adaptive_Contrast_Filter(inputImage, this.LocalGainFactor, this.LocalMeanFactor, this.KernelSize, this.LocalGainMin, this.LocalGainMax);
                break;

            case HistSelection.ACEII:
                outputImage = CvipOp.Histogram_ACE2(inputImage, this.LocalMeanFactor, this.LocalGainFactor, this.KernelSize);
                break;

            case HistSelection.logACE:
                outputImage = CvipOp.Histogram_logACE(inputImage, this.LocalMeanFactor, this.LocalGainFactor, this.KernelSize);
                break;

            case HistSelection.expACE:
                outputImage = CvipOp.Histogram_expACE(inputImage, this.LocalMeanFactor, this.LocalGainFactor, this.KernelSize);
                break;

            case HistSelection.ColorEnhancement:
                if (viewer.Bands == 1)
                {
                    MessageBox.Show("The input image must be a color image.",
                        "Input image error", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    break;
                }
                outputImage = CvipOp.Color_Contrast_Enhance(inputImage, this.LowLimit, this.HighLimit, this.LowClip, this.HighClip);
                break;

            case HistSelection.HistSpec:
                outputImage = CvipOp.Histogram_Specification(inputImage, this.cboFormulaRed.Text, this.cboFormulaGreen.Text, this.cboFormulaBlue.Text);
                if ((outputImage != 0) && this.chkShowIntermediate.Checked)
                {
                    int tmpImage;
                    string tmpName;

                    // show histogram of input image
                    tmpImage = CvipOp.Get_Histogram_Image(inputImage);
                    if ((viewer.Bands == 1) || (viewer.Bands == 3))
                        tmpImage = CvipOp.Spatial_Quant(tmpImage, CvipOp.GetNoOfRows_Image(tmpImage) / 2, CvipOp.GetNoOfCols_Image(tmpImage) / 2, 3);
                    if (tmpImage != 0)
                    {
                        tmpName = viewer.Text + "_" + CvipFunctionNames.getFncName(currentSelection.ToString()) + CvipFunctionNames.getFncName("_histogram");
                        tmpName += CvipConstant.imageNameCount++.ToString();
                        MainForm.Viewers.Add(tmpImage, tmpName);
                    }

                    // show histogram specification
                    tmpImage = CvipOp.Spec_Hist_Image(inputImage, this.cboFormulaRed.Text, this.cboFormulaGreen.Text, this.cboFormulaBlue.Text);
                    if ((viewer.Bands == 1) || (viewer.Bands == 3))
                        tmpImage = CvipOp.Spatial_Quant(tmpImage, CvipOp.GetNoOfRows_Image(tmpImage) / 2, CvipOp.GetNoOfCols_Image(tmpImage) / 2, 3);
                    if (tmpImage != 0)
                    {
                        tmpName = viewer.Text + "_" + CvipFunctionNames.getFncName(currentSelection.ToString()) + CvipFunctionNames.getFncName("_spec");
                        tmpName += CvipConstant.imageNameCount++.ToString();
                        MainForm.Viewers.Add(tmpImage, tmpName);
                    }

                    // show histogram result
                    tmpImage = CvipOp.Get_Histogram_Image(CvipOp.Duplicate_Image(outputImage));
                    if ((viewer.Bands == 1) || (viewer.Bands == 3))
                        tmpImage = CvipOp.Spatial_Quant(tmpImage, CvipOp.GetNoOfRows_Image(tmpImage) / 2, CvipOp.GetNoOfCols_Image(tmpImage) / 2, 3);
                    if (tmpImage != 0)
                    {
                        tmpName = viewer.Text + "_" + CvipFunctionNames.getFncName(currentSelection.ToString()) + CvipFunctionNames.getFncName("_result");
                        tmpName += CvipConstant.imageNameCount++.ToString();
                        MainForm.Viewers.Add(tmpImage, tmpName);
                    }
                }
                break;

            case HistSelection.LinearMod:
                outputImage = CvipOp.Linear_Modify_Range(inputImage, this.StartVal, this.EndVal, this.InitialVal, this.Slope, this.KeepDataOOR, -1);
                break;

            case HistSelection.GrayLevelMult:
                outputImage = CvipOp.Gray_Level_Multiplication(inputImage, this.GrayLevelMultFactor, this.ByteClipping);
                break;
            }
            if (outputImage != 0)
            {
                string newImageName = viewer.Text + "_" + CvipFunctionNames.getFncName(currentSelection.ToString());
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

        private void cboUIntVal_Validating(object sender, CancelEventArgs e)
        {
            ComboBox cbo = sender as ComboBox;
            int val;
            if (!int.TryParse(cbo.Text, out val) || (val < 0))
            {
                MessageBox.Show("Please check the input value. Only positive integers are accepted.",
                   "Positive Integer Required", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                cbo.SelectAll();
                e.Cancel = true;
            }
        }

        protected override void OnLoad(EventArgs e)
        {
            base.OnLoad(e);

            this.rbHistEQ.Tag = HistSelection.HistEQ;
            this.rbHistSlide.Tag = HistSelection.HistSlide;
            this.rbHistStretch.Tag = HistSelection.HistStretch;
            this.rbHistShrink.Tag = HistSelection.HistShrink;
            this.rbLocalEQ.Tag = HistSelection.LocalEQ;
            this.rbCLAHE.Tag = HistSelection.CLAHE;
            this.rbACE.Tag = HistSelection.ACE;
            this.rbACEII.Tag = HistSelection.ACEII;
            this.rbLog.Tag = HistSelection.logACE;
            this.rbEXP.Tag = HistSelection.expACE;
            this.rbColorContrast.Tag = HistSelection.ColorEnhancement;
            this.rbHistSpecify.Tag = HistSelection.HistSpec;
            this.rbLinearMod.Tag = HistSelection.LinearMod;
            this.rbGrayLevelMult.Tag = HistSelection.GrayLevelMult;

            ResetControls();
        }

        private void OnSelectedViewerChanged(ViewerForm viewer)
        {
            this.rbRed.Enabled = (viewer != null) && (viewer.Bands == 3);
            this.rbGreen.Enabled = (viewer != null) && (viewer.Bands == 3);
            this.rbBlue.Enabled = (viewer != null) && (viewer.Bands == 3);
            this.rbValue.Enabled = (viewer != null);
        }

        private void rbHistogram_Click(object sender, EventArgs e)
        {
            RadioButton rb = sender as RadioButton;
            if ((rb != null) && rb.Checked && (rb.Tag != null))
                this.currentSelection = (HistSelection)rb.Tag;

            switch (this.currentSelection)
            {
            case HistSelection.HistShrink:
                 this.cboLowLimit.Text = "1";
                 this.cboHighLimit.Text = "100";
                 // this.cboLowLimit.Text = this.cboLowLimit.Text;
                 // this.cboHighLimit.Text = this.cboHighLimit.Text;
               
                break;

            case HistSelection.HistStretch:
            case HistSelection.ColorEnhancement:
                this.cboLowLimit.Text = "0";
                this.cboHighLimit.Text = "255";
                //this.cboLowLimit.Text = this.cboLowLimit.Text;
                //this.cboHighLimit.Text = this.cboHighLimit.Text;
                break;
            }

            UpdateControls();
        }

        private void ResetControls()
        {
            // Equalization panel
            this.cboBlockSize.Text = "16";
            this.cboClahe.Text = "0.1";
            this.rbValue.Checked = true;
            this.CLAHECheckBox.Checked = true;

            // Slide panel
            this.cboSlide.Text = "20";
            this.rbSlideUp.Checked = true;

            // Stretch panel
            this.cboLowLimit.Text = "0";
            this.cboHighLimit.Text = "255";
            this.cboLowClip.Text = "0.025";
            this.cboHighClip.Text = "0.025";

            // ACE panel
            this.cboKernelSize.Text = "11";
            this.cboLocalGainFactor.Text = "1.0";
            this.cboLocalGainMin.Text = "0.5";
            this.cboLocalGainMax.Text = "10.0";
            this.cboLocalMeanFactor.Text = "0.5";

            // HistSpec panel
            this.cboFormulaRed.Text = "sin(0.025*x)";
            this.cboFormulaGreen.Text = "sin(0.025*x)";
            this.cboFormulaBlue.Text = "sin(0.025*x)";
            this.chkShowIntermediate.Checked = true;

            // LinearMod panel
            this.cboStartVal.Text = "0";
            this.cboEndVal.Text = "255";
            this.cboInitialVal.Text = "0";
            this.cboSlope.Text = "1.2";
            this.rbKeepDataOOR.Checked = true;

            // GrayLevelMult panel
            this.cboFactor.Text = "2.0";
            this.chkByteClipping.Checked = true;

            // Default current selection
            this.rbHistEQ.PerformClick();

            // enable Apply button
            this.btnApply.Enabled = true;
            this.Cursor = Cursors.Default;
        }

        private void UpdateControls()
        {
            switch (this.currentSelection)
            {
            case HistSelection.HistEQ:
            case HistSelection.LocalEQ:
            case HistSelection.CLAHE:
                this.pnlEQ.Visible = true;
                this.cboBlockSize.Visible = (this.currentSelection == HistSelection.LocalEQ || this.currentSelection == HistSelection.CLAHE);
                this.lblBlockSize.Visible = (this.currentSelection == HistSelection.LocalEQ || this.currentSelection == HistSelection.CLAHE);
                this.cboClahe.Visible = this.lblClahe.Visible = this.lblCLAHEPercent.Visible = this.currentSelection == HistSelection.CLAHE;
                this.CLAHECheckBox.Visible = this.currentSelection == HistSelection.CLAHE;

                this.pnlACE.Visible = false;
                this.pnlGrayLevelMult.Visible = false;
                this.pnlHistSpec.Visible = false;
                this.pnlLinearMod.Visible = false;
                this.pnlSlide.Visible = false;
                this.pnlStretch.Visible = false;
                break;

            case HistSelection.HistSlide:
                this.pnlSlide.Visible = true;

                this.pnlACE.Visible = false;
                this.pnlEQ.Visible = false;
                this.pnlGrayLevelMult.Visible = false;
                this.pnlHistSpec.Visible = false;
                this.pnlLinearMod.Visible = false;
                this.pnlStretch.Visible = false;
                break;

            case HistSelection.HistStretch:
            case HistSelection.HistShrink:
            case HistSelection.ColorEnhancement:
                this.pnlStretch.Visible = true;
                this.cboLowClip.Visible = (this.currentSelection != HistSelection.HistShrink);
                this.lblLowClip.Visible = (this.currentSelection != HistSelection.HistShrink);
                this.cboHighClip.Visible = (this.currentSelection != HistSelection.HistShrink);
                this.lblHighClip.Visible = (this.currentSelection != HistSelection.HistShrink);
                this.lblLowPercent.Visible = (this.currentSelection != HistSelection.HistShrink);
                this.lblHighPercent.Visible = (this.currentSelection != HistSelection.HistShrink);

                this.pnlACE.Visible = false;
                this.pnlEQ.Visible = false;
                this.pnlGrayLevelMult.Visible = false;
                this.pnlHistSpec.Visible = false;
                this.pnlLinearMod.Visible = false;
                this.pnlSlide.Visible = false;
                break;

            case HistSelection.ACE:
            case HistSelection.ACEII:
            case HistSelection.logACE:
            case HistSelection.expACE:
                this.pnlACE.Visible = true;
                this.cboLocalGainMin.Visible = (this.currentSelection == HistSelection.ACE);
                this.lblLocalGainMin.Visible = (this.currentSelection == HistSelection.ACE);
                this.cboLocalGainMax.Visible = (this.currentSelection == HistSelection.ACE);
                this.lblLocalGainMax.Visible = (this.currentSelection == HistSelection.ACE);

                this.pnlEQ.Visible = false;
                this.pnlGrayLevelMult.Visible = false;
                this.pnlHistSpec.Visible = false;
                this.pnlLinearMod.Visible = false;
                this.pnlSlide.Visible = false;
                this.pnlStretch.Visible = false;
                break;

            case HistSelection.HistSpec:
                this.pnlHistSpec.Visible = true;

                this.pnlACE.Visible = false;
                this.pnlEQ.Visible = false;
                this.pnlGrayLevelMult.Visible = false;
                this.pnlLinearMod.Visible = false;
                this.pnlSlide.Visible = false;
                this.pnlStretch.Visible = false;
                break;

            case HistSelection.LinearMod:
                this.pnlLinearMod.Visible = true;

                this.pnlACE.Visible = false;
                this.pnlEQ.Visible = false;
                this.pnlGrayLevelMult.Visible = false;
                this.pnlHistSpec.Visible = false;
                this.pnlSlide.Visible = false;
                this.pnlStretch.Visible = false;
                break;

            case HistSelection.GrayLevelMult:
                this.pnlGrayLevelMult.Visible = true;

                this.pnlACE.Visible = false;
                this.pnlEQ.Visible = false;
                this.pnlHistSpec.Visible = false;
                this.pnlLinearMod.Visible = false;
                this.pnlSlide.Visible = false;
                this.pnlStretch.Visible = false;
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
                    OnSelectedViewerChanged(MainForm.Viewers.SelectedViewer);
                    break;

                case WM.DESTROY:
                    MainForm.Viewers.SelectedViewerChanged -= this.OnSelectedViewerChanged;
                    break;
                }
            }
        }

        private double StartVal { get { return double.Parse(this.cboStartVal.Text); } }
        private double EndVal { get { return double.Parse(this.cboEndVal.Text); } }
        private double InitialVal { get { return double.Parse(this.cboInitialVal.Text); } }
        private double Slope { get { return double.Parse(this.cboSlope.Text); } }
        private double LocalGainFactor { get { return double.Parse(this.cboLocalGainFactor.Text); } }
        private double LocalGainMin { get { return double.Parse(this.cboLocalGainMin.Text); } }
        private double LocalGainMax { get { return double.Parse(this.cboLocalGainMax.Text); } }
        private double LocalMeanFactor { get { return double.Parse(this.cboLocalMeanFactor.Text); } }
        private float GrayLevelMultFactor { get { return float.Parse(this.cboFactor.Text); } }
        private float LowClip { get { return float.Parse(this.cboLowClip.Text); } }
        private float HighClip { get { return float.Parse(this.cboHighClip.Text); } }
        private int BlockSize { get { return int.Parse(this.cboBlockSize.Text); } }
        private double CLAHEClip { get { return double.Parse(this.cboClahe.Text); } }
        private int ByteClipping { get { return this.chkByteClipping.Checked ? 1 : 0; } }
        private int KeepDataOOR { get { return this.rbKeepDataOOR.Checked ? 1 : 0; } }
        private int KernelSize { get { return int.Parse(this.cboKernelSize.Text); } }
        private int LowLimit { get { return int.Parse(this.cboLowLimit.Text); }}
        private int HighLimit { get { return int.Parse(this.cboHighLimit.Text); } }
        private int EqBand
        {
            get
            {
                int band = 0;
                if (this.rbRed.Checked)
                    band = 1;
                else if (this.rbGreen.Checked)
                    band = 2;
                else if (this.rbBlue.Checked)
                    band = 3;
                return band;
            }
        }
        private int Slide
        {
            get
            {
                int slide = int.Parse(this.cboSlide.Text);
                if (!this.rbSlideUp.Checked) slide = -slide;
                return slide;
            }
        }

        private void pnlLinearMod_Paint(object sender, PaintEventArgs e)
        {

        }

        private void rbHistShrink_CheckedChanged(object sender, EventArgs e)
        {

        }

        private void rbLocalEQ_CheckedChanged(object sender, EventArgs e)
        {

        }

        private void Percent_TextChanged(object sender, EventArgs e)
        {
            ComboBox cbo = sender as ComboBox;
            if (cbo.Name == "cboLowClip")
            {
                float percent = float.Parse(this.cboLowClip.Text) * 100;
                lblLowPercent.Text = percent.ToString() + "%";
            }
            else if(cbo.Name == "cboHighClip")
            {
                float percent = float.Parse(this.cboHighClip.Text) * 100;
                lblHighPercent.Text = percent.ToString() + "%";
            }
            else
            {
                float percent = float.Parse(this.cboClahe.Text) * 100;
                lblCLAHEPercent.Text = percent.ToString() + "%";
            }
        }
    }
}
