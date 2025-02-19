/*''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' ======================================================================
' Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
' ======================================================================
'
'             File Name: UtilFilter.cs
'           Description: Contains the controls and code
'                        for Utilities->UtilFilter page
'         Related Files: CvipOp.cs
'                        CvipConstant.cs
'   Initial Coding Date: April 2007
'              Modified: November 2011
'       Delevoping tool: Visual Studio 2010-C#
'             Credit(s): Wenjun(Evan) Bian
'                        Patrick Solt
Hari Siva Kumar Reddy Bhogala
'                        Southern Illinois University Edwardsville
'
' Copyright (C) 2012 Scott Umbaugh and SIUE
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
    enum FilterSelection
    {
        mean,
        median,
        laplacian,
        difference,
        specifyfilter,
        specifyblur
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

    public partial class UtilFilter : UserControl
    {
        static readonly double[,] laplacianType1 = new double[,] { { 0, -1, 0 }, { -1, 4, -1 }, { 0, -1, 0 } };
        static readonly double[,] laplacianType2 = new double[,] { { -1, -1, -1 }, { -1, 8, -1 }, { -1, -1, -1 } };
        static readonly double[,] laplacianType3 = new double[,] { { -2, 1, -2 }, { 1, 4, 1 }, { -2, 1, -2 } };
        private FilterSelection currentSelection;
        private UtilFilterMask filterMask = null;

        public UtilFilter()
        {
            InitializeComponent();

            this.pnlMean.Location = new Point(4, 20);
            this.pnlMedian.Location = new Point(4, 20);
            this.pnlLaplacian.Location = new Point(4, 20);
            this.pnlDifference.Location = new Point(4, 20);
            this.pnlSpecifyFilter.Location = new Point(4, 20);
            this.pnlSpecifyBlur.Location = new Point(4, 20);

            this.Size = new Size(436, 140);
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
            string appendix = "";

            switch (this.currentSelection)
            {
            case FilterSelection.mean:
                outputImage = CvipOp.Mean_Filter(inputImage, this.MaskSize);
                appendix = "Mean" + this.MaskSize.ToString() + "_";
                break;

            case FilterSelection.median:
                if (this.rbStandardMedian.Checked)
                {
                    if (this.MaskSize > 31)
                    {
                        MessageBox.Show("Currently the maximum mask size is limited to 31.",
                           "Range error!", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                        break;
                    }
                    outputImage = CvipOp.Median_Filter(inputImage, this.MaskSize);
                }
                else
                {
                    if (this.MaskSize > 11)
                    {
                        MessageBox.Show("Currently the maximum mask size is limited to 11.",
                           "Range error!", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                        break;
                    }
                    outputImage = CvipOp.Adapt_Median_Filter(inputImage, this.MaskSize);

                }
                appendix = "Median" + this.MaskSize.ToString() + "_";
                break;

            case FilterSelection.laplacian:
                outputImage = CvipOp.Specify_Filter(inputImage, this.filterMask.Rows, this.filterMask.Cols, this.filterMask.CurrentValues, 1);
                appendix = "Lapl3x3_";
                break;

            case FilterSelection.difference:
                outputImage = CvipOp.Specify_Filter(inputImage, this.filterMask.Rows, this.filterMask.Cols, this.filterMask.CurrentValues, 1);
                appendix = "Diff" + this.filterMask.Cols.ToString() + "x" + this.filterMask.Rows.ToString() + "_";
                break;

            case FilterSelection.specifyfilter:
                int normalize = this.chkNormalized.Checked ? 1 : 0;
                outputImage = CvipOp.Specify_Filter(inputImage, this.filterMask.Rows, this.filterMask.Cols, this.filterMask.CurrentValues, normalize);
                appendix = "Filter" + this.filterMask.Cols.ToString() + "x" + this.filterMask.Rows.ToString() + "_";
                break;

            case FilterSelection.specifyblur:
                outputImage = CvipOp.Specify_Filter(inputImage, this.filterMask.Rows, this.filterMask.Cols, this.filterMask.CurrentValues, 1);
                appendix = "Blur" + this.filterMask.Cols.ToString() + "x" + this.filterMask.Rows.ToString() + "_";
                break;
            }
            if (outputImage != 0)
            {
                string newImageName = viewer.Text;
                newImageName += "_" + appendix;
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
            MainForm.UtilitiesForm.Close();
        }

        private void btnEditMask_Click(object sender, EventArgs e)
        {
            this.filterMask.Show();
            this.filterMask.Focus();
        }

        private void btnHelp_Click(object sender, EventArgs e)
        {
            MainForm.ShowHelp();
        }

        private void btnReset_Click(object sender, EventArgs e)
        {
            ResetControls();
        }

        private void cboBlurParameter_Changed(object sender, EventArgs e)
        {
            this.filterMask.DefaultValues = SpecifyBlur();
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
            this.filterMask.DefaultValues = SpecifyBlur();
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
            this.filterMask.DefaultValues = SpecifyBlur();
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
            else
            {
                int max = (this.currentSelection == FilterSelection.mean) ? 11 : 31;
                if (val < 3)
                {
                    MessageBox.Show("The mask size should not be less than 3.",
                        "Range error!", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    cbo.SelectAll();
                    e.Cancel = true;
                }
                else if (val > max)
                {
                    MessageBox.Show("Currently the maximum mask size is limited to " + max.ToString() + ".",
                        "Range error!", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    cbo.SelectAll();
                    e.Cancel = true;
                }
            }
        }

        private void cboShapeSize_Validated(object sender, EventArgs e)
        {
            if ((sender as ComboBox).Tag == null) // only run if this is response to user selection
            {
                //if (this.BlurShape == Shape.circle)
                //{
                //    if (this.MaskHeight < this.ShapeWidth)
                //        this.MaskHeight = this.ShapeWidth;
                //    if (this.MaskWidth < this.ShapeWidth)
                //        this.MaskWidth = this.ShapeWidth;
                //}
                //else if (this.BlurShape == Shape.rectangle)
                //{
                //    if (this.MaskHeight < this.ShapeHeight)
                //        this.MaskHeight = this.ShapeHeight;
                //    if (this.MaskWidth < this.ShapeWidth)
                //        this.MaskWidth = this.ShapeWidth;
                //}
            }
            this.filterMask.DefaultValues = SpecifyBlur();
        }

        public void Init(string selection)
        {
            switch (selection)
            {
            case "Mean":
                this.currentSelection = FilterSelection.mean;
                break;
            case "Median":
                this.currentSelection = FilterSelection.median;
                break;
            case "Laplacian Filter":
                this.currentSelection = FilterSelection.laplacian;
                break;
            case "Difference Filter":
                this.currentSelection = FilterSelection.difference;
                break;
            case "Specify a Filter":
                this.currentSelection = FilterSelection.specifyfilter;
                break;
            case "Specify a Blur":
                this.currentSelection = FilterSelection.specifyblur;
                break;
            }

            this.pnlMean.Visible = this.currentSelection == FilterSelection.mean;
            this.pnlMedian.Visible = this.currentSelection == FilterSelection.median;
            this.pnlLaplacian.Visible = this.currentSelection == FilterSelection.laplacian;
            this.pnlDifference.Visible = this.currentSelection == FilterSelection.difference;
            this.pnlSpecifyFilter.Visible = this.currentSelection == FilterSelection.specifyfilter;
            this.pnlSpecifyBlur.Visible = this.currentSelection == FilterSelection.specifyblur;

            this.btnEditMask.Visible = (this.currentSelection != FilterSelection.mean) &&
                (this.currentSelection != FilterSelection.median);

            ResetControls();
        }

        private void OnSelectedViewerChanged(ViewerForm viewer)
        {
            this.txtCurrentImage.Text = "";
            if (viewer != null)
                this.txtCurrentImage.Text = viewer.Text;
        }

        private void rbcboSpecifyFilter_ParameterChanged(object sender, EventArgs e)
        {
            double[,] filter = null;
            string dimensions = " " + this.MaskSize.ToString() + "x" + this.MaskSize.ToString();
            switch (this.cboSpecifyFilter.SelectedIndex)
            {
            case 0: // Low-Pass
                filter = SpecifyFilterLowPass();
                break;
            case 1: // High-Pass
                filter = SpecifyFilterHighPass();
                break;
            case 2: // Center-Weighted constant
                filter = SpecifyFilterCenterWeightedConstant();
                break;
            case 3: // Gaussian
                filter = SpecifyFilterGaussian();
                break;
            }
            this.filterMask.DefaultValues = filter;
            this.filterMask.Text = this.cboSpecifyFilter.Text + dimensions;
        }

        private void rbDifference_CheckedChanged(object sender, EventArgs e)
        {
            this.filterMask.MaskSize = new Size(this.MaskSize, this.MaskSize);
            if (this.filterMask.currentArrowClick != null)
                this.filterMask.currentArrowClick();
        }

        private void rbLaplacianType_CheckedChanged(object sender, EventArgs e)
        {
            double[,] laplacian = null;
            string text = null;
            if (this.rbLaplacianType1.Checked)
            {
                laplacian = laplacianType1;
                text = "Laplacian Filter Type 1";
            }
            else if (this.rbLaplacianType2.Checked)
            {
                laplacian = laplacianType2;
                text = "Laplacian Filter Type 2";
            }
            else
            {
                laplacian = laplacianType3;
                text = "Laplacian Filter Type 3";
            }
            this.filterMask.DefaultValues = laplacian;
            this.filterMask.Text = text;
        }

        private void ResetControls()
        {
            switch (this.currentSelection)
            {
            case FilterSelection.mean:
                this.cboMaskSizeMean.SelectedIndex = 0;
                break;

            case FilterSelection.median:
                this.cboMaskSizeMedian.SelectedIndex = 0;
                this.rbStandardMedian.Checked = true;
                break;

            case FilterSelection.laplacian:
                this.rbLaplacianType1.Checked = true;
                this.filterMask.chkKeepOriginal.Checked = false;
                this.filterMask.DefaultValues = laplacianType1;
                this.filterMask.ShowArrows = false;
                this.filterMask.Text = "Laplacian Filter Type 1";
                break;

            case FilterSelection.difference:
                this.rbDifference3x3.Checked = true;
                this.filterMask.chkKeepOriginal.Checked = false;
                this.filterMask.MaskSize = new Size(3, 3);
                this.filterMask.ShowArrows = true;
                this.filterMask.Text = "Difference Filter";
                this.filterMask.ArrowUpClick();
                break;

            case FilterSelection.specifyfilter:
                this.cboSpecifyFilter.SelectedIndex = 0;
                this.chkNormalized.Checked = true;
                this.rbSpecifyFilter3x3.Checked = true;
                this.filterMask.chkKeepOriginal.Checked = false;
                this.filterMask.DefaultValues = SpecifyFilterLowPass();
                this.filterMask.ShowArrows = false;
                this.filterMask.Text = this.cboSpecifyFilter.Text + " 3x3";
                break;

            case FilterSelection.specifyblur:
                this.cboMaskHeight.Text = "9";
                this.cboMaskWidth.Text = "9";
                this.cboBlurShape.SelectedIndex = 1;
                //this.cboShapeHeight.Text = "7";
                //this.cboShapeWidth.Text = "7";
                this.cboBlurMethod.SelectedIndex = 2;
                this.cboBlurWeight.Text = "1.0";
                this.filterMask.chkKeepOriginal.Checked = false;
                this.filterMask.DefaultValues = SpecifyBlur();
                this.filterMask.ShowArrows = false;
                this.filterMask.Text = "Specify Blur";
                break;
            }

            // enable Apply button
            this.btnApply.Enabled = true;
            this.Cursor = Cursors.Default;
        }

        private double[,] SpecifyBlur()
        {
            int blur = 0, mask = 0 ;
            
            switch (this.BlurShape)
            {
            case Shape.circle:
                    mask = CvipOp.Create_Circle(this.MaskWidth, this.MaskHeight, this.MaskWidth / 2, this.MaskHeight / 2, this.MaskWidth / 2);
                    //(this.MaskWidth, this.MaskHeight, this.MaskWidth / 2, this.MaskHeight / 2, this.ShapeWidth / 2);
                break;
            case Shape.rectangle:
                mask = CvipOp.Create_Rectangle(this.MaskWidth, this.MaskHeight, 0, 0, this.MaskWidth, this.MaskHeight);
                    //(this.MaskWidth, this.MaskHeight, (this.MaskWidth - this.ShapeWidth) / 2, (this.MaskHeight - this.ShapeHeight) / 2, this.ShapeWidth, this.ShapeHeight);
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

            double sum = 0;
           
            int center = this.MaskHeight / 2;
            int center1 = this.MaskWidth / 2;

            double[] pixelVal = null;
            double[,] matrix = new double[this.MaskHeight, this.MaskWidth];

            for (int i = 0; i < this.MaskHeight; i++)
            {
                for (int j = 0; j < this.MaskWidth; j++)
                {
                    pixelVal = (double[])CvipOp.GetPixel_Image(mask, i, j);
                    matrix[i, j] = pixelVal[0];

                    if (this.cboBlurMethod.Text == "Center-Weighted Constant" && (this.cboBlurShape.Text == "Rectangle"))
                    {
                        matrix[i, j] = (int)pixelVal[0];
                    }

                    if (this.cboBlurMethod.Text == "Center-Weighted Constant" && (this.cboBlurShape.Text == "Horizontal line" ||
            this.cboBlurShape.Text == "Vertical line" || this.cboBlurShape.Text ==    "Slash" ||  
            this.cboBlurShape.Text == "Backslash"))
                    {
                        sum = sum + pixelVal[0];
                       
                        matrix[center, center1] = (int)sum / this.MaskHeight;
                    }

                   
                }
            }
            return matrix;
            

            ////int sum = 0;
            ////int center = this.MaskHeight / 2;
            //for (int a = 0; a < this.MaskHeight; a++)
            //{
            //    for (int b = 0; b < this.MaskWidth; b++)
            //    {
            // matrix[center, center] =sum;
            ////         matrix1[a,b] = sum + matrix[i,j];

            //    }
            //}                     
            //     return matrix;
          
        }

        private double[,] SpecifyFilterCenterWeightedConstant()
        {
            double[,] mask = new double[this.MaskSize, this.MaskSize];
            for (int i = 0; i < this.MaskSize; i++)
            {
                for (int j = 0; j < this.MaskSize; j++)
                {
                    mask[i, j] = 1.0;
                }
            }
            int center = this.MaskSize / 2;
            mask[center, center] = this.MaskSize * this.MaskSize;
            return mask;
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

        private double[,] SpecifyFilterHighPass()
        {
            double[,] mask = new double[this.MaskSize, this.MaskSize];
            for (int i = 0; i < this.MaskSize; i++)
            {
                for (int j = 0; j < this.MaskSize; j++)
                {
                    mask[i, j] = -1.0;
                }
            }
            int center = this.MaskSize / 2;
            mask[center, center] = this.MaskSize * this.MaskSize;
            return mask;
        }

        private double[,] SpecifyFilterLowPass()
        {
            double[,] mask = new double[this.MaskSize, this.MaskSize];
            for (int i = 0; i < this.MaskSize; i++)
            {
                for (int j = 0; j < this.MaskSize; j++)
                {
                    mask[i, j] = 1.0;
                }
            }
            return mask;
        }

        protected override void WndProc(ref Message m)
        {
            base.WndProc(ref m);
            if (MainForm.Viewers != null)
            {
                switch ((WM)m.Msg)
                {
                case WM.CREATE:
                    this.filterMask = new UtilFilterMask();
                    this.filterMask.btnApply.Click += new System.EventHandler(this.btnApply_Click);
                    MainForm.Viewers.SelectedViewerChanged += this.OnSelectedViewerChanged;
                    OnSelectedViewerChanged(MainForm.Viewers.SelectedViewer);
                    break;

                case WM.DESTROY:
                    this.filterMask.EndEdit();
                    this.filterMask.Close();
                    MainForm.Viewers.SelectedViewerChanged -= this.OnSelectedViewerChanged;
                    break;
                }
            }
        }

        private float BlurWeight { get { return float.Parse(this.cboBlurWeight.Text); } }
        private int BlurMethod { get { return this.cboBlurMethod.SelectedIndex + 1; } }
        private Shape BlurShape { get { return (Shape)this.cboBlurShape.SelectedIndex; } }

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
        private int MaskSize
        {
            get
            {
                int mask = -1;
                switch (this.currentSelection)
                {
                case FilterSelection.mean:
                    mask = int.Parse(this.cboMaskSizeMean.Text);
                    break;
                case FilterSelection.median:
                    mask = int.Parse(this.cboMaskSizeMedian.Text);
                    break;
                case FilterSelection.difference:
                    if (this.rbDifference3x3.Checked)
                        mask = 3;
                    else if (this.rbDifference5x5.Checked)
                        mask = 5;
                    else if (this.rbDifference7x7.Checked)
                        mask = 7;
                    else if (this.rbDifference9x9.Checked)
                        mask = 9;
                    else
                        mask = 11;
                    break;
                case FilterSelection.specifyfilter:
                    if (this.rbSpecifyFilter3x3.Checked)
                        mask = 3;
                    else if (this.rbSpecifyFilter5x5.Checked)
                        mask = 5;
                    else if (this.rbSpecifyFilter7x7.Checked)
                        mask = 7;
                    else if (this.rbSpecifyFilter9x9.Checked)
                        mask = 9;
                    else
                        mask = 11;
                    break;                
                }
                return mask;
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
    }
}
