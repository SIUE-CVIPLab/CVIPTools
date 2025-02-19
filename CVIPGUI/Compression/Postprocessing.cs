/*''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' ======================================================================
' Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
' ======================================================================
'
'             File Name: Postprocessing.cs
'           Description: Contains the controls and code
'                        for Compression->Postprocessing page
'         Related Files: CvipOp.cs
'                        CvipConstant.cs
'   Initial Coding Date: September 2020
'              Modified: October 2020
'       Delevoping tool: Visual Studio 2019
'             Credit(s): Charles Stacey
'                        Southern Illinois University Edwardsville
'
' Copyright (C) 2020 Scott Umbaugh and SIUE
'
' Permission to use, copy, modify, and distribute this software and its
' documentation for any non-commercial purpose and without fee is hereby
' granted, provided that the above copyright notice appear in all copies
' and that both that copyright notice and this permission notice appear
' in supporting documentation.  This software is provided "as is"
' without express or implied warranty.
'
'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''*/
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace CVIPGUI.Compression
{
    enum PostprocessingSelection
    {
        HistEQ,
        HistStretch,
        mean,
        gaussian
    }

    public partial class Postprocessing : UserControl
    {
        private PostprocessingSelection currentSelection;
        private double[,] defaultMatrix = null;

        public Postprocessing()
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
                case PostprocessingSelection.HistEQ:
                    outputImage = CvipOp.Histogram_Equalization(inputImage, this.EqBand);
                    break;

                case PostprocessingSelection.HistStretch:
                    outputImage = CvipOp.Histogram_Stretch(inputImage, this.LowLimit, this.HighLimit, this.LowClip, this.HighClip);
                    break;

                case PostprocessingSelection.mean:
                    if (this.MaskSize > 11)
                    {
                        MessageBox.Show("Currently the maximum mask size is limited to 11.",
                            "Range error!", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                        break;
                    }
                    outputImage = CvipOp.Mean_Filter(inputImage, this.MaskSize);
                    break;

                case PostprocessingSelection.gaussian:
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

                    outputImage = CvipOp.Specify_Filter(inputImage, this.MaskSize, this.MaskSize, this.CurrentValues(), 1);
                    break;
            }
            if (outputImage != 0)
            {
                // create a name for the new image
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
            MainForm.CompressionForm.Close();
        }

        private void btnHelp_Click(object sender, EventArgs e)
        {
            MainForm.ShowHelp();
        }

        private void btnReset_Click(object sender, EventArgs e)
        {
            ResetControls();
        }

        protected override void OnLoad(EventArgs e)
        {
            base.OnLoad(e);

            this.rbHistEq.Tag = PostprocessingSelection.HistEQ;
            this.rbHistSt.Tag = PostprocessingSelection.HistStretch;
            this.rbMean.Tag = PostprocessingSelection.mean;
            this.rbGauss.Tag = PostprocessingSelection.gaussian;

            ResetControls();
        }

        private void rbPostprocessing_Click(object sender, EventArgs e)
        {
            RadioButton rb = sender as RadioButton;
            if ((rb != null) && rb.Checked && (rb.Tag != null))
                this.currentSelection = (PostprocessingSelection)rb.Tag;
            this.rbHistEq.Checked = (PostprocessingSelection)this.rbHistEq.Tag == this.currentSelection;
            this.rbHistSt.Checked = (PostprocessingSelection)this.rbHistSt.Tag == this.currentSelection;
            this.rbMean.Checked = (PostprocessingSelection)this.rbMean.Tag == this.currentSelection;
            this.rbGauss.Checked = (PostprocessingSelection)this.rbGauss.Tag == this.currentSelection;
            UpdateControls();
        }

        private void ResetControls()
        {
            // Parameters group
            this.rbLight.Checked = true;
            this.cbLowLimit.Text = "0";
            this.cbHighLimit.Text = "255";
            this.cbLowClip.Text = "0.025";
            this.cbHighClip.Text = "0.025";
            this.cbMaskSize.Text = "3";

            // Default current selection
            this.rbHistEq.PerformClick();

            // enable Apply button
            this.btnApply.Enabled = true;
            this.Cursor = Cursors.Default;
        }

        private void UpdateControls()
        {
            this.HistEqPanel.Visible = this.currentSelection == PostprocessingSelection.HistEQ;
            this.HistStPanel.Visible = this.currentSelection == PostprocessingSelection.HistStretch;
            this.maskPanel.Visible = (this.currentSelection == PostprocessingSelection.mean || this.currentSelection == PostprocessingSelection.gaussian);

            // enable Apply button
            this.btnApply.Enabled = true;
            this.Cursor = Cursors.Default;
        }

        private void OnSelectedViewerChanged(ViewerForm viewer)
        {
            this.rbRed.Enabled = (viewer != null) && (viewer.Bands == 3);
            this.rbGreen.Enabled = (viewer != null) && (viewer.Bands == 3);
            this.rbBlue.Enabled = (viewer != null) && (viewer.Bands == 3);
            this.rbLight.Enabled = (viewer != null);
            //if (viewer.Bands == 1)
            //    this.rbLight.PerformClick();
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

        private int MaskSize { get { return int.Parse(this.cbMaskSize.Text); } }
        private int LowLimit { get { return int.Parse(this.cbLowLimit.Text); } }
        private int HighLimit { get { return int.Parse(this.cbHighLimit.Text); } }
        private float LowClip { get { return float.Parse(this.cbLowClip.Text); } }
        private float HighClip { get { return float.Parse(this.cbHighClip.Text); } }
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

        private void Percent_TextChanged(object sender, EventArgs e)
        {
            ComboBox cbo = sender as ComboBox;
            if (cbo.Name == "cbLowClip")
            {
                float percent = float.Parse(this.cbLowClip.Text) * 100;
                lblLowPercent.Text = percent.ToString() + "%";
            }
            else
            {
                float percent = float.Parse(this.cbHighClip.Text) * 100;
                lblHighPercent.Text = percent.ToString() + "%";
            }
        }
    }
}
