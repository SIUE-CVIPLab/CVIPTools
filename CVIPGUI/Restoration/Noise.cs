/*''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' ======================================================================
' Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
' ======================================================================
'
'             File Name: Noise.cs
'           Description: Contains the controls and code
'                        for Restoration->Noise page
'         Related Files: CvipOp.cs
'                        CvipConstant.cs
'   Initial Coding Date: October 2007
'              Modified: November 2009
'       Delevoping tool: Visual Studio 2010-C#
'             Credit(s): Wenjun(Evan) Bian
'                        Patrick Solt
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
    enum NoiseSelection
    {
        negexp,
        rayleigh,
        gaussian,
        uniform,
        gamma,
        saltpepper
    }

    public partial class Noise : UserControl
    {
        private NoiseSelection currentSelection;

        public Noise()
        {
            InitializeComponent();
        }
        private void btnApply_Click(object sender, EventArgs e)
        {
            ViewerForm viewer = MainForm.Viewers.SelectedViewer;
            if (viewer == null && !rbUseBlack.Checked)
            {
                MessageBox.Show("Please give an input image!", "No input image!",
                    MessageBoxButtons.OK, MessageBoxIcon.Warning);
                return;
            }
            if (this.ImageWidth <= 0 || this.ImageHeight <= 0)
            {
                MessageBox.Show("Please check Height and Width.", "Positive Value Expected!",
                    MessageBoxButtons.OK, MessageBoxIcon.Warning);
                return;
            }
            // disable Apply button
            this.btnApply.Enabled = false;
            this.Cursor = Cursors.WaitCursor;

            // get the image that will be operated on
            int inputImage = 0, outputImage = 0;
            if (rbUseBlack.Checked)
                inputImage = CvipOp.Create_Black(this.ImageWidth, this.ImageHeight);
            else
                inputImage = viewer.CVIPimage;
            
            switch (this.currentSelection)
            {
            case NoiseSelection.negexp:
                outputImage = CvipOp.Neg_Exp_Noise(inputImage, this.Variance);
                break;

            case NoiseSelection.rayleigh:
                outputImage = CvipOp.Rayleigh_Noise(inputImage, this.Variance);
                break;

            case NoiseSelection.gaussian:
                outputImage = CvipOp.Gaussian_Noise(inputImage, this.Variance, this.Mean);
                break;

            case NoiseSelection.uniform:
                outputImage = CvipOp.Uniform_Noise(inputImage, this.Variance, this.Mean);
                break;

            case NoiseSelection.gamma:
                outputImage = CvipOp.Gamma_Noise(inputImage, this.Variance, this.Alpha);
                break;

            case NoiseSelection.saltpepper:
                outputImage = CvipOp.Speckle_Noise(inputImage, this.Salt, this.Pepper);
                break;
            }
            if (outputImage != 0)
            {
                string newImageName = "";
                if (!rbUseBlack.Checked)
                    newImageName += viewer.Text + "_";
                newImageName += CvipFunctionNames.getFncName(this.currentSelection.ToString());
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
        protected override void OnLoad(EventArgs e)
        {
            base.OnLoad(e);

            this.rbNegExponent.Tag = NoiseSelection.negexp;
            this.rbRayleigh.Tag = NoiseSelection.rayleigh;
            this.rbGamma.Tag = NoiseSelection.gamma;
            this.rbGaussian.Tag = NoiseSelection.gaussian;
            this.rbUniform.Tag = NoiseSelection.uniform;
            this.rbSaltPepper.Tag = NoiseSelection.saltpepper;

            ResetControls();
        }
        private void rbNoise_Click(object sender, EventArgs e)
        {
            RadioButton rb = sender as RadioButton;
            if ((rb != null) && rb.Checked && (rb.Tag != null))
                this.currentSelection = (NoiseSelection)rb.Tag;
            UpdateControls();
        }
        private void rbUseCurrent_Click(object sender, EventArgs e)
        {
            this.lblHeight.Visible = this.rbUseBlack.Checked;
            this.cboHeight.Visible = this.rbUseBlack.Checked;
            this.lblWidth.Visible = this.rbUseBlack.Checked;
            this.cboWidth.Visible = this.rbUseBlack.Checked;
        }
        private void ResetControls()
        {
            this.cboVariance.Text = "100.0";
            this.cboMean.Text = "0.0";
            this.cboAlpha.Text = "3";
            this.cboPepper.Text = "0.03";
            this.cboSalt.Text = "0.03";
            this.cboHeight.Text = "256";
            this.cboWidth.Text = "256";

            this.rbUseCurrent.PerformClick();
            this.rbNegExponent.PerformClick();

            // enable Apply button
            this.btnApply.Enabled = true;
            this.Cursor = Cursors.Default;
        }
        private void UpdateControls()
        {
            switch (this.currentSelection)
            {
            case NoiseSelection.negexp:
            case NoiseSelection.rayleigh:
               // this.cboVariance.Text = "100.0";
                this.lblVariance.Visible = true;
                this.cboVariance.Visible = true;
                this.lblMean.Visible = false;
                this.cboMean.Visible = false;
                this.lblAlpha.Visible = false;
                this.cboAlpha.Visible = false;
                this.lblPepper.Visible = false;
                this.cboPepper.Visible = false;
                this.lblSalt.Visible = false;
                this.cboSalt.Visible = false;
                break;

            case NoiseSelection.gaussian:
            case NoiseSelection.uniform:
                //this.cboVariance.Text = "100.0";
                this.lblVariance.Visible = true;
                this.cboVariance.Visible = true;
                this.lblMean.Visible = true;
                this.cboMean.Visible = true;
                this.lblAlpha.Visible = false;
                this.cboAlpha.Visible = false;
                this.lblPepper.Visible = false;
                this.cboPepper.Visible = false;
                this.lblSalt.Visible = false;
                this.cboSalt.Visible = false;
                break;

            case NoiseSelection.gamma:
                //this.cboVariance.Text = "100.0";
                this.lblVariance.Visible = true;
                this.cboVariance.Visible = true;
                this.lblMean.Visible = false;
                this.cboMean.Visible = false;
                this.lblAlpha.Visible = true;
                this.cboAlpha.Visible = true;
                this.lblPepper.Visible = false;
                this.cboPepper.Visible = false;
                this.lblSalt.Visible = false;
                this.cboSalt.Visible = false;
                break;

            case NoiseSelection.saltpepper:
                this.lblVariance.Visible = false;
                this.cboVariance.Visible = false;
                this.lblMean.Visible = false;
                this.cboMean.Visible = false;
                this.lblAlpha.Visible = false;
                this.cboAlpha.Visible = false;
                this.lblPepper.Visible = true;
                this.cboPepper.Visible = true;
                this.lblSalt.Visible = true;
                this.cboSalt.Visible = true;
                break;
            }
            // enable Apply button
            this.btnApply.Enabled = true;
            this.Cursor = Cursors.Default;
        }

        private double Mean { get { return double.Parse(this.cboMean.Text); } }
        private double Pepper { get { return double.Parse(this.cboPepper.Text); } }
        private double Salt { get { return double.Parse(this.cboSalt.Text); } }
        private double Variance { get { return double.Parse(this.cboVariance.Text); } }

        private int Alpha { get { return int.Parse(this.cboAlpha.Text); } }
        private int ImageHeight { get { return int.Parse(this.cboHeight.Text); } }
        private int ImageWidth { get { return int.Parse(this.cboWidth.Text); } }
    }
}
