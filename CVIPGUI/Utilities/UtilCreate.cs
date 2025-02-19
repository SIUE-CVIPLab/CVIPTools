/*''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' ======================================================================
' Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
' ======================================================================
'
'             File Name: UtilCreate.cs
'           Description: Contains the controls and code
'                        for Utilities->UtilCreate page
'         Related Files: CvipOp.cs
'                        CvipConstant.cs
'   Initial Coding Date: April 2007
'              Modified: December 2009
'       Delevoping tool: Visual Studio 2008-C#
'             Credit(s): Patrick Solt
Hari Siva Kumar Reddy Bhogala
'                        Southern Illinois University Edwardsville
'
' Copyright (C) 2011 Scott Umbaugh and SIUE
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
    enum CreateSelection
    {
        Add_Noise,
        Assemble_Bands,
        Black_Image,
        Border_Image,
        Border_Mask,
        Checkerboard,
        Circle,
        Cosine_Wave,
        Ellipse,
        Extract_Band,
        Line,
        Rectangle,
        Sine_Wave,
        Square_Wave
    }

    public partial class UtilCreate : UserControl
    {
        private CreateSelection currentSelection;

        public UtilCreate()
        {
            InitializeComponent();

            this.pnlAssembleBands.Location = new Point(4, 20);
            this.pnlBlack.Location = new Point(4, 20);
            this.pnlBorder.Location = new Point(4, 20);
            this.pnlCheckerboard.Location = new Point(4, 20);
            this.pnlCircle.Location = new Point(4, 20);
            this.pnlEllipse.Location = new Point(4, 20);
            this.pnlExtractBand.Location = new Point(4, 20);
            this.pnlLine.Location = new Point(4, 20);
            this.pnlNoise.Location = new Point(4, 20);
            this.pnlRectangle.Location = new Point(4, 20);
            this.pnlWave.Location = new Point(4, 20);
          //  if ((this.Height / 4 > 185))
            //    this.Size = new Size(this.Width / 2, this.Height / 4);
           // else
           // this.Size = new Size(436, 140);
        }

        private void btnApply_Click(object sender, EventArgs e)
        {
            ViewerForm viewer = null, viewerR = null, viewerG = null, viewerB = null;
            if (((this.currentSelection == CreateSelection.Add_Noise) && this.rbUseCurrentImage.Checked) ||
                (this.currentSelection == CreateSelection.Border_Image) ||
                (this.currentSelection == CreateSelection.Border_Mask) ||
                (this.currentSelection == CreateSelection.Extract_Band))
            {
                viewer = (ViewerForm)this.txtCurrentImage.Tag;
                if (viewer == null)
                {
                    MessageBox.Show("Please give an input image!", "No input image!",
                        MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    return;
                }
            }
            else if (this.currentSelection == CreateSelection.Assemble_Bands)
            {
                viewerR = this.cboRedBand.SelectedItem as ViewerForm;
                viewerG = this.cboGreenBand.SelectedItem as ViewerForm;
                viewerB = this.cboBlueBand.SelectedItem as ViewerForm;
                if ((viewerR == null) || (viewerG == null) || (viewerB == null))
                {
                    MessageBox.Show("Please make sure that you select images for all the bands.",
                        "Missing input image!", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    return;
                }
            }

            // disable Apply button
            this.btnApply.Enabled = false;
            this.Cursor = Cursors.WaitCursor;

            try
            {
                int[] area = null, bands = null;
                int band = -1, width = -1, height = -1;
                int inputImage = 0, outputImage = 0;
                string appendix = this.currentSelection.ToString();

                switch (this.currentSelection)
                {
                    case CreateSelection.Add_Noise:
                        if (this.rbUseCurrentImage.Checked)
                            inputImage = viewer.CVIPimage;
                        else
                            inputImage = CvipOp.Create_Black(this.ImageWidth, this.ImageHeight);

                        switch (this.cboNoiseType.Text)
                        {
                            case "Gamma":
                                outputImage = CvipOp.Gamma_Noise(inputImage, this.Variance, this.Alpha);
                                appendix = "Gamma_Noise";
                                break;

                            case "Gaussian":
                                outputImage = CvipOp.Gaussian_Noise(inputImage, this.Variance, this.Mean);
                                appendix = "Gaussian_Noise";
                                break;

                            case "Negtive exponential":
                                outputImage = CvipOp.Neg_Exp_Noise(inputImage, this.Variance);
                                appendix = "Neg_Exp_Noise";
                                break;

                            case "Rayleigh":
                                outputImage = CvipOp.Rayleigh_Noise(inputImage, this.Variance);
                                appendix = "Rayleigh_Noise";
                                break;

                            case "Salt and Pepper":
                                outputImage = CvipOp.Speckle_Noise(inputImage, this.Salt, this.Pepper);
                                appendix = "Salt_Pepper_Noise";
                                break;

                            case "Uniform":
                                outputImage = CvipOp.Uniform_Noise(inputImage, this.Variance, this.Mean);
                                appendix = "Uniform_Noise";
                                break;
                        }
                        CvipOp.Delete_Image(ref inputImage);
                        break;

                    case CreateSelection.Assemble_Bands:
                        bands = new int[3];
                        bands[0] = viewerR.CVIPimage;
                        bands[1] = viewerG.CVIPimage;
                        bands[2] = viewerB.CVIPimage;
                        outputImage = CvipOp.Assemble_Bands(bands);
                        for (int i = 0; i < 3; i++)
                            CvipOp.Delete_Image(ref bands[i]);
                        break;

                    case CreateSelection.Black_Image:
                        if (this.ImageWidth < 1 || this.ImageHeight < 1)
                        {
                            MessageBox.Show("ImageWidth and ImageHeight must be > 0 ", "Positive Value Required",
                            MessageBoxButtons.OK, MessageBoxIcon.Warning);
                            break;
                        }
                        outputImage = CvipOp.Create_Black(this.ImageWidth, this.ImageHeight);
                        break;

                    case CreateSelection.Border_Image:
                        if (viewer.SelectionState != SelectionState.BorderSelected)
                        {
                            MessageBox.Show("You must draw Border first!", "No Border",
                                MessageBoxButtons.OK, MessageBoxIcon.Warning);
                            break;
                        }
                        inputImage = viewer.CVIPimage;
                        if (viewer.DataType != dataType.CVIP_BYTE)
                            inputImage = CvipOp.CondRemap_Image(inputImage, dataType.CVIP_BYTE, 0, 255);
                        area = viewer.SelectedArea;
                        ColorDialog cd = new ColorDialog();
                        cd.ShowDialog();
                        outputImage = CvipOp.Object_Crop(inputImage, area, 3, (int)cd.Color.R, (int)cd.Color.G, (int)cd.Color.B);
                        break;

                    case CreateSelection.Border_Mask:
                        if (viewer.SelectionState != SelectionState.BorderSelected)
                        {
                            MessageBox.Show("You must draw Border first!", "No Border",
                                MessageBoxButtons.OK, MessageBoxIcon.Warning);
                            break;
                        }
                        area = viewer.SelectedArea;
                        outputImage = CvipOp.Object_Crop(viewer.CVIPimage, area, 2, 0, 0, 0);
                        break;

                    case CreateSelection.Checkerboard:
                        if (this.CellWidth < 1 || this.CellHeight < 1)
                        {
                            MessageBox.Show("CellWidth and CellHeight must be > 0 ", "Positive Value Required",
                           MessageBoxButtons.OK, MessageBoxIcon.Warning);
                            break;
                        }


                        if (this.ImageWidth < 1 || this.ImageHeight < 1)
                        {
                            MessageBox.Show("ImageWidth and ImageHeight must be > 0 ", "Positive Value Required",
                            MessageBoxButtons.OK, MessageBoxIcon.Warning);
                            break;
                        }
                        outputImage = CvipOp.Create_Checkboard(this.ImageWidth, this.ImageHeight,
                                                                this.StartCol, this.StartRow,
                                                                this.CellWidth, this.CellHeight);
                        break;

                    case CreateSelection.Circle:
                        if (this.ImageWidth < 1 || this.ImageHeight < 1)
                        {
                            MessageBox.Show("ImageWidth and ImageHeight must be > 0 ", "Positive Value Required",
                            MessageBoxButtons.OK, MessageBoxIcon.Warning);
                            break;
                        }
                        if (this.chkBlurRadiusCircle.Checked)
                            outputImage = CvipOp.Create_Degenerate_Circle(this.ImageWidth, this.ImageHeight,
                                                                            this.CenterCol, this.CenterRow,
                                                                            this.Radius, this.BlurRadius);
                        else
                            outputImage = CvipOp.Create_Circle(this.ImageWidth, this.ImageHeight,
                                                                this.CenterCol, this.CenterRow,
                                                                this.Radius);
                        break;

                    case CreateSelection.Cosine_Wave:
                    case CreateSelection.Sine_Wave:
                    case CreateSelection.Square_Wave:
                        if (this.ImageWidth < 1 || this.ImageHeight < 1)
                        {
                            MessageBox.Show("ImageWidth and ImageHeight must be > 0 ", "Positive Value Required",
                            MessageBoxButtons.OK, MessageBoxIcon.Warning);
                            break;
                        }
                        width = this.ImageWidth;
                        height = this.ImageHeight;
                        if (width == height)
                        {
                            if (this.Frequency < 0)
                            {
                                MessageBox.Show("Frequency can't be negative. ", "Positive Value required",
                               MessageBoxButtons.OK, MessageBoxIcon.Warning);
                                break;
                            }
                            switch (this.currentSelection)
                            {
                                case CreateSelection.Cosine_Wave:
                                    outputImage = CvipOp.Create_Cosine(width, this.Frequency, this.Direction);
                                    break;
                                case CreateSelection.Sine_Wave:
                                    outputImage = CvipOp.Create_Sine(width, this.Frequency, this.Direction);
                                    break;
                                case CreateSelection.Square_Wave:
                                    outputImage = CvipOp.Create_Squarewave(width, this.Frequency, this.Direction);
                                    break;
                            }
                        }
                        else
                        {
                            int max = Math.Max(width, height), tmp = 0;
                            if (((max == width) && (this.Direction == 1)) ||
                                ((max == height) && (this.Direction == 2)))
                            {
                                switch (this.currentSelection)
                                {
                                    case CreateSelection.Cosine_Wave:
                                        tmp = CvipOp.Create_Cosine(max, this.Frequency, this.Direction);
                                        break;
                                    case CreateSelection.Sine_Wave:
                                        tmp = CvipOp.Create_Sine(max, this.Frequency, this.Direction);
                                        break;
                                    case CreateSelection.Square_Wave:
                                        tmp = CvipOp.Create_Squarewave(max, this.Frequency, this.Direction);
                                        break;
                                }
                            }
                            else
                            {
                                int min = Math.Min(width, height);
                                int factor = (int)((double)this.Frequency * ((double)max / (double)min));
                                switch (this.currentSelection)
                                {
                                    case CreateSelection.Cosine_Wave:
                                        tmp = CvipOp.Create_Cosine(max, factor, this.Direction);
                                        break;
                                    case CreateSelection.Sine_Wave:
                                        tmp = CvipOp.Create_Sine(max, factor, this.Direction);
                                        break;
                                    case CreateSelection.Square_Wave:
                                        tmp = CvipOp.Create_Squarewave(max, factor, this.Direction);
                                        break;
                                }
                            }
                            outputImage = CvipOp.Crop(tmp, 0, 0, height, width);
                            CvipOp.Delete_Image(ref tmp);
                        }
                        break;

                    case CreateSelection.Ellipse:
                        if (this.ImageWidth < 1 || this.ImageHeight < 1)
                        {
                            MessageBox.Show("ImageWidth and ImageHeight must be > 0 ", "Positive Value Required",
                            MessageBoxButtons.OK, MessageBoxIcon.Warning);
                            break;
                        }
                        outputImage = CvipOp.Create_Ellipse(this.ImageWidth, this.ImageHeight,
                                                            this.CenterCol, this.CenterRow,
                                                            this.ShapeWidth, this.ShapeHeight);
                        break;

                    case CreateSelection.Extract_Band:
                        band = 0;
                        inputImage = viewer.CVIPimage;
                        if (this.rbExtractBand1.Checked)
                        {
                            appendix = "bandR";
                            band = 1;
                        }
                        else if (this.rbExtractBand2.Checked)
                        {
                            appendix = "bandG";
                            band = 2;
                        }
                        else
                        {
                            appendix = "bandB";
                            band = 3;
                        }
                        outputImage = CvipOp.Extract_Band(inputImage, band);
                        CvipOp.Delete_Image(ref inputImage);
                        break;

                    case CreateSelection.Line:
                        if (this.ImageWidth < 1 || this.ImageHeight < 1)
                        {
                            MessageBox.Show("ImageWidth and ImageHeight must be > 0 ", "Positive Value Required",
                            MessageBoxButtons.OK, MessageBoxIcon.Warning);
                            break;
                        }
                        outputImage = CvipOp.Create_Line(this.ImageWidth, this.ImageHeight,
                                                            this.StartCol, this.StartRow,
                                                            this.EndCol, this.EndRow);
                        break;

                    case CreateSelection.Rectangle:
                        if (this.ImageWidth < 1 || this.ImageHeight < 1)
                        {
                            MessageBox.Show("ImageWidth and ImageHeight must be > 0 ", "Positive Value Required",
                            MessageBoxButtons.OK, MessageBoxIcon.Warning);
                            break;
                        }
                        outputImage = CvipOp.Create_Rectangle(this.ImageWidth, this.ImageHeight,
                                                                this.StartCol, this.StartRow,
                                                                this.ShapeWidth, this.ShapeHeight);
                        break;
                }
                if (outputImage != 0)
                {
                    string newImageName = "";
                    if (((this.currentSelection == CreateSelection.Add_Noise) && this.rbUseCurrentImage.Checked) ||
                        (this.currentSelection == CreateSelection.Border_Image) ||
                        (this.currentSelection == CreateSelection.Border_Mask) ||
                        (this.currentSelection == CreateSelection.Extract_Band))
                    {
                        newImageName += viewer.Text + "_";
                    }
                    newImageName += CvipFunctionNames.getFncName(appendix);
                    newImageName += CvipConstant.imageNameCount++.ToString();
                    MainForm.Viewers.Add(outputImage, newImageName);
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }

            // enable Apply button
            this.btnApply.Enabled = true;
            this.Cursor = Cursors.Default;
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
            ResetControls();
        }

        private void cboBand_DrawItem(object sender, DrawItemEventArgs e)
        {
            ComboBox cbo = sender as ComboBox;
            this.toolTipImage2.RemoveAll();
            if (cbo.Items.Count != 0 && e.Index != -1)
            {
                string text = cbo.GetItemText(cbo.Items[e.Index]);
                e.DrawBackground();
                using (SolidBrush br = new SolidBrush(e.ForeColor))
                {
                    e.Graphics.DrawString(text, e.Font, br, e.Bounds);
                }
                if ((e.State & DrawItemState.Selected) == DrawItemState.Selected)
                {
                    this.toolTipImage2.Show(text, cbo, e.Bounds.Right, e.Bounds.Bottom);
                }
                else
                {
                    this.toolTipImage2.Hide(cbo);
                }
                e.DrawFocusRectangle();
            }
        }

        private void cboBand_SelectedIndexChanged(object sender, EventArgs e)
        {
            ComboBox cbo = sender as ComboBox;
            this.toolTipImage2.RemoveAll();
            this.toolTipImage2.Hide(cbo);
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

        private void cboNoiseType_SelectedIndexChanged(object sender, EventArgs e)
        {
            switch (this.cboNoiseType.Text)
            {
                case "Negtive exponential":
                case "Rayleigh":
                    this.cboAlpha.Visible = false;
                    this.cboMean.Visible = false;
                    this.lblAlpha_Mean.Visible = false;

                    this.cboPepper.Visible = false;
                    this.cboSalt.Visible = false;
                    this.lblPepper.Visible = false;
                    this.lblSalt.Visible = false;

                    this.cboVariance.Visible = true;
                    this.lblVariance.Visible = true;
                    break;

                case "Gaussian":
                case "Uniform":
                    this.cboAlpha.Visible = false;
                    this.cboMean.Visible = true;
                    this.lblAlpha_Mean.Text = "Mean";
                    this.lblAlpha_Mean.Visible = true;

                    this.cboPepper.Visible = false;
                    this.cboSalt.Visible = false;
                    this.lblPepper.Visible = false;
                    this.lblSalt.Visible = false;

                    this.cboVariance.Visible = true;
                    this.lblVariance.Visible = true;
                    break;

                case "Gamma":
                    this.cboAlpha.Visible = true;
                    this.cboMean.Visible = false;
                    this.lblAlpha_Mean.Text = "Alpha";
                    this.lblAlpha_Mean.Visible = true;

                    this.cboPepper.Visible = false;
                    this.cboSalt.Visible = false;
                    this.lblPepper.Visible = false;
                    this.lblSalt.Visible = false;

                    this.cboVariance.Visible = true;
                    this.lblVariance.Visible = true;
                    break;

                case "Salt and Pepper":
                    this.cboAlpha.Visible = false;
                    this.cboMean.Visible = false;
                    this.lblAlpha_Mean.Visible = false;

                    this.cboPepper.Visible = true;
                    this.cboSalt.Visible = true;
                    this.lblPepper.Visible = true;
                    this.lblSalt.Visible = true;

                    this.cboVariance.Visible = false;
                    this.lblVariance.Visible = false;
                    break;
            }
        }

        public void Init(string op)
        {
            switch (op)
            {
                case "Add Noise":
                    this.currentSelection = CreateSelection.Add_Noise;
                    break;
                case "Assemble Bands":
                    this.currentSelection = CreateSelection.Assemble_Bands;
                    break;
                case "Black Image":
                    this.currentSelection = CreateSelection.Black_Image;
                    break;
                case "Border Image":
                    this.currentSelection = CreateSelection.Border_Image;
                    break;
                case "Border Mask":
                    this.currentSelection = CreateSelection.Border_Mask;
                    break;
                case "Cosine Wave":
                    this.currentSelection = CreateSelection.Cosine_Wave;
                    break;
                case "Extract Band":
                    this.currentSelection = CreateSelection.Extract_Band;
                    break;
                case "Sine Wave":
                    this.currentSelection = CreateSelection.Sine_Wave;
                    break;
                case "Square Wave":
                    this.currentSelection = CreateSelection.Square_Wave;
                    break;
                default:
                    this.currentSelection = (CreateSelection)Enum.Parse(typeof(CreateSelection), op);
                    break;
            }

            this.lblCurrentImage.Visible = (this.currentSelection == CreateSelection.Add_Noise) ||
                                            (this.currentSelection == CreateSelection.Extract_Band);
            this.txtCurrentImage.Visible = (this.currentSelection == CreateSelection.Add_Noise) ||
                                            (this.currentSelection == CreateSelection.Extract_Band);
            this.pnlAssembleBands.Visible = (this.currentSelection == CreateSelection.Assemble_Bands);
            this.pnlBlack.Visible = (this.currentSelection == CreateSelection.Black_Image);
            this.pnlBorder.Visible = (this.currentSelection == CreateSelection.Border_Image) ||
                                        (this.currentSelection == CreateSelection.Border_Mask);
            this.pnlCheckerboard.Visible = (this.currentSelection == CreateSelection.Checkerboard);
            this.pnlCircle.Visible = (this.currentSelection == CreateSelection.Circle);
            this.pnlEllipse.Visible = (this.currentSelection == CreateSelection.Ellipse);
            this.pnlExtractBand.Visible = (this.currentSelection == CreateSelection.Extract_Band);
            this.pnlLine.Visible = (this.currentSelection == CreateSelection.Line);
            this.pnlNoise.Visible = (this.currentSelection == CreateSelection.Add_Noise);
            this.pnlRectangle.Visible = (this.currentSelection == CreateSelection.Rectangle);
            this.pnlWave.Visible = (this.currentSelection == CreateSelection.Cosine_Wave) ||
                                    (this.currentSelection == CreateSelection.Sine_Wave) ||
                                    (this.currentSelection == CreateSelection.Square_Wave);

            switch (this.currentSelection)
            {
                case CreateSelection.Assemble_Bands:
                case CreateSelection.Border_Image:
                case CreateSelection.Border_Mask:
                    this.btnReset.Enabled = false;
                    break;

                default:
                    this.btnReset.Enabled = true;
                    break;
            }

            ResetControls();
        }

        //private void OnSelectedViewerChanged(ViewerForm viewer)
        //{
        //    if (MainForm.Viewers != null)
        //    {
        //        this.txtCurrentImage.Tag = viewer;
        //        this.txtCurrentImage.Text = "";
        //        if (viewer != null)
        //            this.txtCurrentImage.Text = viewer.Text;
        //        this.txtCurrentImageBorder.Text = this.txtCurrentImage.Text;
        //    }
        //}

        private void OnViewerCollectionChanged()
        {
            if (MainForm.Viewers != null)
            {
                ViewerForm r = this.cboRedBand.SelectedItem as ViewerForm;
                ViewerForm g = this.cboGreenBand.SelectedItem as ViewerForm;
                ViewerForm b = this.cboBlueBand.SelectedItem as ViewerForm;

                if (r == null) r = MainForm.Viewers.SelectedViewer;
                if (g == null) g = MainForm.Viewers.SelectedViewer;
                if (b == null) b = MainForm.Viewers.SelectedViewer;

                this.cboRedBand.Items.Clear();
                this.cboGreenBand.Items.Clear();
                this.cboBlueBand.Items.Clear();

                foreach (ViewerForm viewer in MainForm.Viewers)
                {
                    this.cboRedBand.Items.Add(viewer);
                    this.cboGreenBand.Items.Add(viewer);
                    this.cboBlueBand.Items.Add(viewer);
                }

                this.cboRedBand.SelectedItem = r;
                this.cboGreenBand.SelectedItem = g;
                this.cboBlueBand.SelectedItem = b;
            }
        }

        private void rbUseImage_Click(object sender, EventArgs e)
        {
            this.cboImageHeightNoise.Visible = this.rbUseBlackImage.Checked;
            this.cboImageWidthNoise.Visible = this.rbUseBlackImage.Checked;
            this.lblImageHeightNoise.Visible = this.rbUseBlackImage.Checked;
            this.lblImageWidthNoise.Visible = this.rbUseBlackImage.Checked;
        }

        private void ResetControls()
        {
            switch (this.currentSelection)
            {
                case CreateSelection.Add_Noise:
                    this.cboAlpha.Text = "1";
                    this.cboAlpha.Visible = false;
                    this.cboMean.Text = "0";
                    this.cboMean.Visible = false;
                    this.lblAlpha_Mean.Visible = false;

                    this.cboPepper.Text = "0.03";
                    this.cboPepper.Visible = false;
                    this.cboSalt.Text = "0.03";
                    this.cboSalt.Visible = false;
                    this.lblPepper.Visible = false;
                    this.lblSalt.Visible = false;

                    this.cboVariance.Text = "100.0";
                    this.cboVariance.Visible = true;
                    this.lblVariance.Visible = true;

                    this.cboImageHeightNoise.Text = "256";
                    this.cboImageHeightNoise.Visible = false;
                    this.cboImageWidthNoise.Text = "256";
                    this.cboImageWidthNoise.Visible = false;
                    this.lblImageHeightNoise.Visible = false;
                    this.lblImageWidthNoise.Visible = false;

                    this.cboNoiseType.SelectedIndex = 1;
                    this.rbUseCurrentImage.PerformClick();
                    break;

                case CreateSelection.Black_Image:
                    this.cboImageHeightBlack.Text = "256";
                    this.cboImageWidthBlack.Text = "256";
                    break;

                case CreateSelection.Checkerboard:
                    this.cboStartColCheckerboard.Text = "0";
                    this.cboStartRowCheckerboard.Text = "0";
                    this.cboCellHeightCheckerboard.Text = "32";
                    this.cboCellWidthCheckerboard.Text = "32";
                    this.cboImageHeightCheckerboard.Text = "256";
                    this.cboImageWidthCheckerboard.Text = "256";
                    break;

                case CreateSelection.Circle:
                    this.cboCenterColCircle.Text = "128";
                    this.cboCenterRowCircle.Text = "128";
                    this.cboRadiusCircle.Text = "32";
                    this.cboBlurRadiusCircle.Text = "64";
                    this.chkBlurRadiusCircle.Checked = false;
                    this.cboImageHeightCircle.Text = "256";
                    this.cboImageWidthCircle.Text = "256";
                    break;

                case CreateSelection.Cosine_Wave:
                case CreateSelection.Sine_Wave:
                    this.cboDirection.SelectedIndex = 0;
                    this.cboFrequency.Text = "32";
                    this.cboImageHeightWave.Text = "256";
                    this.cboImageWidthWave.Text = "256";
                    break;

                case CreateSelection.Ellipse:
                    this.cboCenterColEllipse.Text = "128";
                    this.cboCenterRowEllipse.Text = "128";
                    this.cboHeightEllipse.Text = "64";
                    this.cboWidthEllipse.Text = "128";
                    this.cboImageHeightEllipse.Text = "256";
                    this.cboImageWidthEllipse.Text = "256";
                    break;

                case CreateSelection.Extract_Band:
                    this.rbExtractBand1.Checked = true;
                    break;

                case CreateSelection.Line:
                    this.cboStartColLine.Text = "0";
                    this.cboStartRowLine.Text = "0";
                    this.cboEndColLine.Text = "256";
                    this.cboEndRowLine.Text = "256";
                    this.cboImageHeightLine.Text = "256";
                    this.cboImageWidthLine.Text = "256";
                    break;

                case CreateSelection.Rectangle:
                    this.cboStartColRectangle.Text = "96";
                    this.cboStartRowRectangle.Text = "96";
                    this.cboHeightRectangle.Text = "64";
                    this.cboWidthRectangle.Text = "64";
                    this.cboImageHeightRectangle.Text = "256";
                    this.cboImageWidthRectangle.Text = "256";
                    break;

                case CreateSelection.Square_Wave:
                    this.cboDirection.SelectedIndex = 1;
                    this.cboFrequency.Text = "32";
                    this.cboImageHeightWave.Text = "256";
                    this.cboImageWidthWave.Text = "256";
                    break;
            }

            // enable Apply button
            this.btnApply.Enabled = true;
            this.Cursor = Cursors.Default;
        }


        private void OnSelectedViewerChanged(ViewerForm viewer)
        {
            if (MainForm.Viewers != null)
            {
                if ((ModifierKeys & Keys.Alt) == Keys.Alt)
                {
                    this.cboGreenBand.SelectedItem = viewer;
                }
                else
                {
                    if ((ModifierKeys & Keys.Shift) == Keys.Shift)
                    {
                        this.cboBlueBand.SelectedItem = viewer;
                    }
                    else
                    {
                        this.txtCurrentImage.Tag = viewer;
                        this.txtCurrentImage.Text = "";
                        if (viewer != null)
                            this.txtCurrentImage.Text = viewer.Text;
                        this.cboRedBand.Tag = viewer;
                        this.cboRedBand.Text = "";
                        if (viewer != null)
                            this.cboRedBand.Text = viewer.Text;

                    }
                }
            }
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
                        OnSelectedViewerChanged(MainForm.Viewers.SelectedViewer);
                        OnViewerCollectionChanged();
                        break;

                    case WM.DESTROY:
                        MainForm.Viewers.SelectedViewerChanged -= this.OnSelectedViewerChanged;
                        MainForm.Viewers.ViewerCollectionChanged -= this.OnViewerCollectionChanged;
                        break;
                }
            }
        }

        public double Mean { get { return double.Parse(this.cboMean.Text); } }
        public double Pepper { get { return double.Parse(this.cboPepper.Text); } }
        public double Salt { get { return double.Parse(this.cboSalt.Text); } }
        public double Variance { get { return double.Parse(this.cboVariance.Text); } }

        public int Alpha { get { return int.Parse(this.cboAlpha.Text); } }
        public int BlurRadius { get { return int.Parse(this.cboBlurRadiusCircle.Text); } }
        public int CellHeight { get { return int.Parse(this.cboCellHeightCheckerboard.Text); } }
        public int CellWidth { get { return int.Parse(this.cboCellWidthCheckerboard.Text); } }
        public int Direction { get { return this.cboDirection.SelectedIndex + 1; } }
        public int EndCol { get { return int.Parse(this.cboEndColLine.Text); } }
        public int EndRow { get { return int.Parse(this.cboEndRowLine.Text); } }
        public int Frequency { get { return int.Parse(this.cboFrequency.Text); } }
        public int Radius { get { return int.Parse(this.cboRadiusCircle.Text); } }
        public int CenterCol
        {
            get
            {
                int col = -1;
                switch (this.currentSelection)
                {
                    case CreateSelection.Circle:
                        col = int.Parse(this.cboCenterColCircle.Text);
                        break;
                    case CreateSelection.Ellipse:
                        col = int.Parse(this.cboCenterColEllipse.Text);
                        break;
                }
                return col;
            }
        }
        public int CenterRow
        {
            get
            {
                int row = -1;
                switch (this.currentSelection)
                {
                    case CreateSelection.Circle:
                        row = int.Parse(this.cboCenterRowCircle.Text);
                        break;
                    case CreateSelection.Ellipse:
                        row = int.Parse(this.cboCenterRowEllipse.Text);
                        break;
                }
                return row;
            }
        }
        public int ImageHeight
        {
            get
            {
                int height = -1;
                switch (this.currentSelection)
                {
                    case CreateSelection.Add_Noise:
                        height = int.Parse(this.cboImageHeightNoise.Text);
                        break;
                    case CreateSelection.Black_Image:
                        height = int.Parse(this.cboImageHeightBlack.Text);
                        break;
                    case CreateSelection.Checkerboard:
                        height = int.Parse(this.cboImageHeightCheckerboard.Text);
                        break;
                    case CreateSelection.Circle:
                        height = int.Parse(this.cboImageHeightCircle.Text);
                        break;
                    case CreateSelection.Cosine_Wave:
                    case CreateSelection.Sine_Wave:
                    case CreateSelection.Square_Wave:
                        height = int.Parse(this.cboImageHeightWave.Text);
                        break;
                    case CreateSelection.Ellipse:
                        height = int.Parse(this.cboImageHeightEllipse.Text);
                        break;
                    case CreateSelection.Line:
                        height = int.Parse(this.cboImageHeightLine.Text);
                        break;
                    case CreateSelection.Rectangle:
                        height = int.Parse(this.cboImageHeightRectangle.Text);
                        break;
                }
                return height;
            }
        }
        public int ImageWidth
        {
            get
            {
                int width = -1;
                switch (this.currentSelection)
                {
                    case CreateSelection.Add_Noise:
                        width = int.Parse(this.cboImageWidthNoise.Text);
                        break;
                    case CreateSelection.Black_Image:
                        width = int.Parse(this.cboImageWidthBlack.Text);
                        break;
                    case CreateSelection.Checkerboard:
                        width = int.Parse(this.cboImageWidthCheckerboard.Text);
                        break;
                    case CreateSelection.Circle:
                        width = int.Parse(this.cboImageWidthCircle.Text);
                        break;
                    case CreateSelection.Cosine_Wave:
                    case CreateSelection.Sine_Wave:
                    case CreateSelection.Square_Wave:
                        width = int.Parse(this.cboImageWidthWave.Text);
                        break;
                    case CreateSelection.Ellipse:
                        width = int.Parse(this.cboImageWidthEllipse.Text);
                        break;
                    case CreateSelection.Line:
                        width = int.Parse(this.cboImageWidthLine.Text);
                        break;
                    case CreateSelection.Rectangle:
                        width = int.Parse(this.cboImageWidthRectangle.Text);
                        break;
                }
                return width;
            }
        }
        public int ShapeHeight
        {
            get
            {
                int height = -1;
                switch (this.currentSelection)
                {
                    case CreateSelection.Ellipse:
                        height = int.Parse(this.cboHeightEllipse.Text);
                        break;
                    case CreateSelection.Rectangle:
                        height = int.Parse(this.cboHeightRectangle.Text);
                        break;
                }
                return height;
            }
        }
        public int ShapeWidth
        {
            get
            {
                int width = -1;
                switch (this.currentSelection)
                {
                    case CreateSelection.Ellipse:
                        width = int.Parse(this.cboWidthEllipse.Text);
                        break;
                    case CreateSelection.Rectangle:
                        width = int.Parse(this.cboWidthRectangle.Text);
                        break;
                }
                return width;
            }
        }
        public int StartCol
        {
            get
            {
                int col = -1;
                switch (this.currentSelection)
                {
                    case CreateSelection.Checkerboard:
                        col = int.Parse(this.cboStartColCheckerboard.Text);
                        break;
                    case CreateSelection.Line:
                        col = int.Parse(this.cboStartColLine.Text);
                        break;
                    case CreateSelection.Rectangle:
                        col = int.Parse(this.cboStartColRectangle.Text);
                        break;
                }
                return col;
            }
        }
        public int StartRow
        {
            get
            {
                int row = -1;
                switch (this.currentSelection)
                {
                    case CreateSelection.Checkerboard:
                        row = int.Parse(this.cboStartRowCheckerboard.Text);
                        break;
                    case CreateSelection.Line:
                        row = int.Parse(this.cboStartRowLine.Text);
                        break;
                    case CreateSelection.Rectangle:
                        row = int.Parse(this.cboStartRowRectangle.Text);
                        break;
                }
                return row;
            }
        }
    }
}
