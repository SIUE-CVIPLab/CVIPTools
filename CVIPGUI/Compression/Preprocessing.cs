/*''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' ======================================================================
' Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
' ======================================================================
'
'             File Name: Preprocessing.cs
'           Description: Contains the controls and code
'                        for Compression->Preprocessing page
'         Related Files: CvipOp.cs
'                        CvipConstant.cs
'   Initial Coding Date: August 2007
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
'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''*/

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace CVIPGUI.Compression
{
    enum PreprocessingSelection
    {
        bin2gray,
        gray2bin,
        spatialquant,
        grayquant
    }

    public partial class Preprocessing : UserControl
    {
        private PreprocessingSelection currentSelection;

        public Preprocessing()
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
            case PreprocessingSelection.bin2gray:
                outputImage = CvipOp.BinaryToGray(inputImage);
                break;

            case PreprocessingSelection.gray2bin:
                outputImage = CvipOp.GrayToBinary(inputImage);
                break;

            case PreprocessingSelection.spatialquant:
                outputImage = CvipOp.Spatial_Quant(inputImage, this.NumRows, this.NumCols, this.Method);
                break;

            case PreprocessingSelection.grayquant:
                outputImage = CvipOp.Graylevel_Quant(inputImage, this.NumGrayLevels, this.Choice);
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
        private void cboGrayLevels_Validating(object sender, CancelEventArgs e)
        {
            int size;
            if (!int.TryParse(this.cboGrayLevels.Text, out size))
            {
                MessageBox.Show("Please check the input value. Only integers are accepted.",
                   "Integer Required", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                this.cboGrayLevels.SelectAll();
                e.Cancel = true;
                return;
            }
            int n = 1;
            while (n < size) n *= 2;
            if ((n != size) || (n == 1))
            {
                MessageBox.Show("Number of gray levels should be a power of 2.",
                    "Number of Gray Levels", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                this.cboGrayLevels.SelectAll();
                e.Cancel = true;
                return;
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

            this.rbBinToGray.Tag = PreprocessingSelection.bin2gray;
            this.rbGrayToBin.Tag = PreprocessingSelection.gray2bin;
            this.rbSpatialQuant.Tag = PreprocessingSelection.spatialquant;
            this.rbGraylevelQuant.Tag = PreprocessingSelection.grayquant;

            ResetControls();
        }
        private void rbPreprocessing_Click(object sender, EventArgs e)
        {
            RadioButton rb = sender as RadioButton;
            if ((rb != null) && rb.Checked && (rb.Tag != null))
                this.currentSelection = (PreprocessingSelection)rb.Tag;
            UpdateControls();
        }
        private void ResetControls()
        {
            // Parameters group
            this.cboHeight.Text = "32";
            this.cboWidth.Text = "32";
            this.cboMethod.SelectedIndex = 1;
            this.rbStandard.PerformClick();
            this.cboGrayLevels.Text = "2";

            // Default current selection
            this.rbBinToGray.PerformClick();

            // enable Apply button
            this.btnApply.Enabled = true;
            this.Cursor = Cursors.Default;
        }
        private void UpdateControls()
        {
            this.lblHeight.Visible = this.currentSelection == PreprocessingSelection.spatialquant;
            this.cboHeight.Visible = this.currentSelection == PreprocessingSelection.spatialquant;
            this.lblWidth.Visible = this.currentSelection == PreprocessingSelection.spatialquant;
            this.cboWidth.Visible = this.currentSelection == PreprocessingSelection.spatialquant;
            this.lblMethod.Visible = this.currentSelection == PreprocessingSelection.spatialquant;
            this.cboMethod.Visible = this.currentSelection == PreprocessingSelection.spatialquant;
            this.lblType.Visible = this.currentSelection == PreprocessingSelection.grayquant;
            this.rbStandard.Visible = this.currentSelection == PreprocessingSelection.grayquant;
            this.rbIGS.Visible = this.currentSelection == PreprocessingSelection.grayquant;
            this.lblGrayLevels.Visible = this.currentSelection == PreprocessingSelection.grayquant;
            this.cboGrayLevels.Visible = this.currentSelection == PreprocessingSelection.grayquant;

            // enable Apply button
            this.btnApply.Enabled = true;
            this.Cursor = Cursors.Default;
        }

        private int Choice { get { return this.rbStandard.Checked ? 0 : 1; } }
        private int NumGrayLevels { get { return int.Parse(this.cboGrayLevels.Text); } }
        private int NumCols { get { return int.Parse(this.cboWidth.Text); } }
        private int NumRows { get { return int.Parse(this.cboHeight.Text); } }
        private int Method { get { return this.cboMethod.SelectedIndex + 1; } }
    }
}
