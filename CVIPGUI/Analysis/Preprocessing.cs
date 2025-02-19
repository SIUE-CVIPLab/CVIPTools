/*''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' ======================================================================
' Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
' ======================================================================
'
'             File Name: Preprocessing.cs
'           Description: Contains the controls and code
'                        for Analysis->Preprocessing page
'         Related Files: CvipOp.cs
'                        CvipConstant.cs
'   Initial Coding Date: 
'              Modified: 
'       Delevoping tool: Visual Studio 2019
'             Credit(s): comment to update
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
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''*/

using CVIPGUI.Utilities;
using System;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;

namespace CVIPGUI.Analysis
{    public enum PreProcessingSelection
    {
        Add,
        Subtract,
        Multiply,
        Divide,
        AND,
        NOT,
        OR,
        XOR,
        Mean,
        Gaussian,
        Median,
        Laplacian,
        Difference,
        Crop,
        Zoom,
        GrayLevelQuan,
        SpatialQuant,
        HistEQ,
        HistStretch
    } // end Enum



    public partial class Preprocessing : UserControl
    {
        private PreProcessingSelection currentSelection;
        static readonly double[,] laplacianType1 = new double[,] { { 0, -1, 0 }, { -1, 4, -1 }, { 0, -1, 0 } };
        static readonly double[,] laplacianType2 = new double[,] { { -1, -1, -1 }, { -1, 8, -1 }, { -1, -1, -1 } };
        static readonly double[,] laplacianType3 = new double[,] { { -2, 1, -2 }, { 1, 4, 1 }, { -2, 1, -2 } };
        private UtilFilterMask filterMask = null;
        ViewerForm current, alternate;
        //private CVIPGUI.Utilities.UtilFilterMask filterMask = null; 

        //private UtilFilterMask filterMask = null;

        public Preprocessing()
        {
            InitializeComponent();
        }

        private void btnApply_Click(object sender, EventArgs e)
        {
            ViewerForm viewer, viewer2 = null;

            //if(this.currentSelection == PreProcessingSelection.Add ||
            //   this.currentSelection == PreProcessingSelection.Subtract ||
            //   this.currentSelection == PreProcessingSelection.Multiply ||
            //   this.currentSelection == PreProcessingSelection.Divide ||
            //   this.currentSelection == PreProcessingSelection.AND ||
            //   this.currentSelection == PreProcessingSelection.OR ||
            //   this.currentSelection == PreProcessingSelection.XOR)
            //{
            //    viewer = (ViewerForm)this.txtCurrentImage.Tag;
            //    //MainForm.Viewers.SelectedViewer = viewer;
            //}
            //else
            //{
            //    viewer = MainForm.Viewers.SelectedViewer;
            //}

            viewer = current;

            if (viewer == null)
            {
                MessageBox.Show("Please give an input image!", "No input image!",
                    MessageBoxButtons.OK, MessageBoxIcon.Warning);
                return;
            }

            if (this.currentSelection != PreProcessingSelection.NOT)
            {
                viewer2 = (ViewerForm)this.cboSecondImage.SelectedItem;
            }

            this.btnApply.Enabled = false;
            this.Cursor = Cursors.WaitCursor;


            try
            {
                int inputImage1 = viewer.CVIPimage, outputImage = 0;
                int inputImage2 = (viewer2 == null) ? 0 : viewer2.CVIPimage;

                switch (this.currentSelection)
                {
                    case PreProcessingSelection.Add:
                        outputImage = CvipOp.Add_Image(inputImage1, inputImage2);
                        break;

                    case PreProcessingSelection.Subtract:
                        outputImage = CvipOp.Subtract_Image(inputImage1, inputImage2);
                        break;

                    case PreProcessingSelection.Multiply:
                        outputImage = CvipOp.Multiply_Image(inputImage1, inputImage2);
                        break;

                    case PreProcessingSelection.Divide:
                        outputImage = CvipOp.Divide_Image(inputImage1, inputImage2, 1);
                        break;

                    case PreProcessingSelection.AND:
                        outputImage = CvipOp.And_Image(inputImage1, inputImage2);
                        break;

                    case PreProcessingSelection.NOT:
                        outputImage = CvipOp.Not_Image(inputImage1);
                        break;

                    case PreProcessingSelection.OR:
                        outputImage = CvipOp.Or_Image(inputImage1, inputImage2);
                        break;

                    case PreProcessingSelection.XOR:
                        outputImage = CvipOp.Xor_Image(inputImage1, inputImage2);
                        break;


                }
                if (outputImage != 0)
                {
                    string newImageName = viewer.Text;
                    newImageName += "_" + CvipFunctionNames.getFncName(this.currentSelection.ToString());
                    newImageName += CvipConstant.imageNameCount++.ToString();
                    MainForm.Viewers.Add(outputImage, newImageName);
                }
                // delete input images
                CvipOp.Delete_Image(ref inputImage1);
                if (this.currentSelection != PreProcessingSelection.NOT)
                {
                    CvipOp.Delete_Image(ref inputImage2);
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
            // enable Apply button

            try
            {
                string appendix = "";
                int inputImage1 = viewer.CVIPimage, outputImage = 0;

                switch (this.currentSelection)
                {
                    case PreProcessingSelection.Mean:
                        outputImage = CvipOp.Mean_Filter(inputImage1, this.MaskSize);
                        appendix = "Mean" + this.MaskSize.ToString() + "_";
                        break;

                    case PreProcessingSelection.Median:
                        if (this.rbStandard.Checked)
                        {
                            if (this.MaskSize > 31)
                            {
                                MessageBox.Show("Currently the maximum mask size is limited to 31.",
                                    "Range error!", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                                break;
                            }
                            outputImage = CvipOp.Median_Filter(inputImage1, this.MaskSize);
                        }
                        else
                        {
                            if (this.MaskSize > 11)
                            {
                                MessageBox.Show("Currently the maximum mask size is limited to 11.",
                                    "Range error!", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                                break;
                            }
                            outputImage = CvipOp.Adapt_Median_Filter(inputImage1, this.MaskSize);

                        }
                        appendix = "Median" + this.MaskSize.ToString() + "_";
                        break;

                    case PreProcessingSelection.Laplacian:
                        outputImage = CvipOp.Specify_Filter(inputImage1, this.filterMask.Rows, this.filterMask.Cols, this.filterMask.CurrentValues, 1);
                        appendix = "Lapl3x3_";
                        break;
                    case PreProcessingSelection.Difference:
                        outputImage = CvipOp.Specify_Filter(inputImage1, this.filterMask.Rows, this.filterMask.Cols, this.filterMask.CurrentValues, 1);
                        appendix = "Diff" + this.filterMask.Cols.ToString() + "x" + this.filterMask.Rows.ToString() + "_";
                        break;

                    case PreProcessingSelection.Gaussian:
                        int normalize = this.chkNormalize.Checked ? 1 : 0;
                        outputImage = CvipOp.Specify_Filter(inputImage1, this.filterMask.Rows, this.filterMask.Cols, this.filterMask.CurrentValues, normalize);
                        appendix = "Filter" + this.filterMask.Cols.ToString() + "x" + this.filterMask.Rows.ToString() + "_";
                        break;

                    case PreProcessingSelection.Crop:
                        if (this.CropCol < 0 || this.CropRow < 0)
                        {
                            MessageBox.Show("Values must be >= 0. ", "Positive Value Required",
                            MessageBoxButtons.OK, MessageBoxIcon.Warning);
                            break;
                        }
                        if (this.WidthParameter < 0 || this.HeightParameter < 0)
                        {
                            MessageBox.Show("Width/Height must be > 0. ", "Positive Value Required",
                            MessageBoxButtons.OK, MessageBoxIcon.Warning);
                            break;
                        }
                        if (viewer.SelectedArea == null)
                        {
                            Rectangle rect = new Rectangle();
                            rect.X = this.CropCol;
                            rect.Y = this.CropRow;
                            rect.Width = this.WidthParameter;
                            rect.Height = this.HeightParameter;
                            viewer.SelectRect(rect);
                        }
                        outputImage = viewer.SelectedImage;
                        appendix = "SzeCrop";
                        break;

                    case PreProcessingSelection.GrayLevelQuan:

                        if (rdbUtilConvertStandard.Checked)
                            outputImage = CvipOp.Gray_Quant_Segment(inputImage1, Convert.ToInt32(cmbUtilConvertNumOfBits.Text));
                        else if (rdbUtilConvertIGS.Checked)
                            outputImage = CvipOp.Igs_Segment(inputImage1, Convert.ToInt32(cmbUtilConvertNumOfBits.Text));

                        appendix = "GLQ";
                        break;

                    case PreProcessingSelection.Zoom:
                        //if (this.ZoomQuadrant == ZoomQuadrant.area)
                        //{
                            if (viewer.SelectedArea == null)
                            {
                                if ((this.ZoomCol >= viewer.ImageWidth) ||
                                    (this.ZoomRow >= viewer.ImageHeight) ||
                                    ((this.ZoomCol + this.ZoomWidth) > viewer.ImageWidth) ||
                                    ((this.ZoomRow + this.ZoomHeight) > viewer.ImageHeight))
                                {
                                    MessageBox.Show("Check your input parameters!", "Zoom Parameters",
                                        MessageBoxButtons.OK, MessageBoxIcon.Warning);
                                    break;
                                }
                                Rectangle rect = new Rectangle();
                                rect.X = this.ZoomCol;
                                rect.Y = this.ZoomRow;
                                rect.Width = this.ZoomWidth;
                                rect.Height = this.ZoomHeight;
                                viewer.SelectRect(rect);
                            }
                            inputImage1 = viewer.SelectedImage;
                            if (this.ZoomMethod == ResizeMethod.zero_order_hold)
                                outputImage = CvipOp.Zoom(inputImage1, 5, -1, -1, -1, -1, this.ZoomFactor);
                            else
                                outputImage = CvipOp.Bilinear_Interp1(inputImage1, this.ZoomFactor, this.ZoomFactor);
                        //}
                        //else
                        //{
                        //    if (this.ZoomMethod == ResizeMethod.zero_order_hold)
                        //        outputImage = CvipOp.Zoom(inputImage1, (int)this.ZoomQuadrant, -1, -1, -1, -1, this.ZoomFactor);
                        //    else
                        //    {
                        //        inputImage1 = CvipOp.Zoom(inputImage1, (int)this.ZoomQuadrant, -1, -1, -1, -1, 1);
                        //        outputImage = CvipOp.Bilinear_Interp1(inputImage1, this.ZoomFactor, this.ZoomFactor);
                        //    }
                        //}
                        break;

                    case PreProcessingSelection.SpatialQuant:
                        if (viewer.SelectedArea != null)
                        {
                            CvipOp.Delete_Image(ref inputImage1);
                            inputImage1 = viewer.SelectedImage;
                        }
                        if ((this.HeightParameter < 1) || (this.WidthParameter < 1))
                        {
                            MessageBox.Show("Check Height/Width Values", "Positive Value Required",
                                MessageBoxButtons.OK, MessageBoxIcon.Warning);
                            break;
                        }
                        if (this.SpatialQuantMethod == 2 && ((this.HeightParameter < 1) || (this.WidthParameter < 1)))
                        {
                            MessageBox.Show("Check Height/Width Values (Must be > 1)", "Positive Value Required",
                                MessageBoxButtons.OK, MessageBoxIcon.Warning);
                            break;
                        }
                        //MessageBox.Show(this.SpatialQuantMethod.ToString());
                        outputImage = CvipOp.Spatial_Quant(inputImage1, this.HeightParameter, this.WidthParameter, this.SpatialQuantMethod);
                        appendix = "SzeSptialQuant";
                        break;

                    case PreProcessingSelection.HistEQ:
                        outputImage = CvipOp.Histogram_Equalization(inputImage1, this.EqBand);
                        break;

                    case PreProcessingSelection.HistStretch:
                        outputImage = CvipOp.Histogram_Stretch(inputImage1, this.LowLimit, this.HighLimit, this.LowClip, this.HighClip);
                        break;

                }
                if (outputImage != 0)
                {
                    string newImageName = viewer.Text;
                    newImageName += "_" + appendix;
                    newImageName += CvipConstant.imageNameCount++.ToString();
                    MainForm.Viewers.Add(outputImage, newImageName);
                }

                //End Code to apply spatial Filters... 

                this.btnApply.Enabled = true;
                this.Cursor = Cursors.Default;
                CvipOp.Delete_Image(ref inputImage1);
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        } // End Button Apply Click

        private void rbPreProcessing_CheckedChanged(object sender, EventArgs e)
        {
            RadioButton rb = sender as RadioButton;
            if ((rb != null) && rb.Checked && (rb.Tag != null))
            {
                this.currentSelection = (PreProcessingSelection)rb.Tag;
                UpdateControls();
            }
        }//End PreProcessing CheckChanged

        private void cboSecondImage_DrawItem(object sender, DrawItemEventArgs e)
        {
            this.toolTipImage2.RemoveAll();
            if (cboSecondImage.Items.Count != 0 && e.Index != -1)
            {
                string text = this.cboSecondImage.GetItemText(cboSecondImage.Items[e.Index]);
                e.DrawBackground();
                using (SolidBrush br = new SolidBrush(e.ForeColor))
                {
                    e.Graphics.DrawString(text, e.Font, br, e.Bounds);
                }
                if ((e.State & DrawItemState.Selected) == DrawItemState.Selected)
                {
                    this.toolTipImage2.Show(text, cboSecondImage, e.Bounds.Right, e.Bounds.Bottom);
                }
                else
                {
                    this.toolTipImage2.Hide(cboSecondImage);
                }
                e.DrawFocusRectangle();
            }
            this.toolTipImage2.RemoveAll();
        }

        private void cboSecondImage_SelectedIndexChanged(object sender, EventArgs e)
        {
            this.toolTipImage2.RemoveAll();
            this.toolTipImage2.Hide(this.cboSecondImage);
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
                        this.filterMask = new UtilFilterMask();
                        this.filterMask.btnApply.Click += new System.EventHandler(this.btnApply_Click);
                        //MainForm.Viewers.SelectedViewerChanged += this.OnSelectedViewerChanged;
                        OnSelectedViewerChanged(MainForm.Viewers.SelectedViewer);

                        //MainForm.Viewers.SelectedViewerChanged += this.OnSelectedViewerChanged;
                        //ViewerForm.BoundingRectangleChanged += this.OnBoundingRectangleChanged;
                        //MainForm.Viewers.SelectedViewerChanged += this.OnSelectedViewerChanged;
                        //MainForm.Viewers.ViewerCollectionChanged += this.OnViewerCollectionChanged;
                        ViewerForm.BoundingRectangleChanged += this.OnSelectedRectangleChanged;
                        OnViewerCollectionChanged();
                        break;

                    case WM.DESTROY:
                        MainForm.Viewers.SelectedViewerChanged -= this.OnSelectedViewerChanged;
                        MainForm.Viewers.ViewerCollectionChanged -= this.OnViewerCollectionChanged;
                        this.filterMask.EndEdit();
                        this.filterMask.Close();
                        //MainForm.Viewers.SelectedViewerChanged -= this.OnSelectedViewerChanged;

                        //MainForm.Viewers.SelectedViewerChanged -= this.OnSelectedViewerChanged;
                       //ViewerForm.BoundingRectangleChanged -= this.OnBoundingRectangleChanged;

                        //MainForm.Viewers.SelectedViewerChanged -= this.OnSelectedViewerChanged;
                        //MainForm.Viewers.ViewerCollectionChanged -= this.OnViewerCollectionChanged;
                        ViewerForm.BoundingRectangleChanged -= this.OnSelectedRectangleChanged;
                        break;
                }
            }
        }

        private void OnViewerCollectionChanged()
        {
            if (MainForm.Viewers != null)
            {
                ViewerForm selected = this.cboSecondImage.SelectedItem as ViewerForm;
                if (selected == null) selected = MainForm.Viewers.SelectedViewer;
                this.cboSecondImage.Items.Clear();
                foreach (ViewerForm viewer in MainForm.Viewers)
                    this.cboSecondImage.Items.Add(viewer);
                this.cboSecondImage.SelectedItem = selected;
            }
        }

        private void OnSelectedViewerChanged(ViewerForm viewer)
        {
            if (MainForm.Viewers != null)
            {
                if ((ModifierKeys & Keys.Alt) == Keys.Alt)
                {
                    if (this.currentSelection != PreProcessingSelection.Add &&
                       this.currentSelection != PreProcessingSelection.Subtract &&
                       this.currentSelection != PreProcessingSelection.Multiply &&
                       this.currentSelection != PreProcessingSelection.Divide &&
                       this.currentSelection != PreProcessingSelection.AND &&
                       this.currentSelection != PreProcessingSelection.OR &&
                       this.currentSelection != PreProcessingSelection.XOR)
                    {
                        this.txtCurrentImage.Tag = current = viewer;
                        this.txtCurrentImage.Text = "";
                        if (viewer != null)
                            this.txtCurrentImage.Text = viewer.Text;
                    }
                    else
                        this.cboSecondImage.SelectedItem = alternate = viewer;
                }
                else
                {
                    this.txtCurrentImage.Tag = current = viewer;
                    this.txtCurrentImage.Text = "";
                    if (viewer != null)
                        this.txtCurrentImage.Text = viewer.Text;
                }
            }
        }

        protected override void OnLoad(EventArgs e)
        {
            base.OnLoad(e);
            if (MainForm.Viewers != null)
            {
                OnSelectedViewerChanged(MainForm.Viewers.SelectedViewer);
                OnViewerCollectionChanged();
            }
            this.rbAdd.Tag = PreProcessingSelection.Add;
            this.rbSubtract.Tag = PreProcessingSelection.Subtract;
            this.rbMultiply.Tag = PreProcessingSelection.Multiply;
            this.rbDivide.Tag = PreProcessingSelection.Divide;
            this.rbAnd.Tag = PreProcessingSelection.AND;
            this.rbNot.Tag = PreProcessingSelection.NOT;
            this.rbOr.Tag = PreProcessingSelection.OR;
            this.rbXor.Tag = PreProcessingSelection.XOR;
            this.rbMeanFilter.Tag = PreProcessingSelection.Mean;
            this.rbGaussian.Tag = PreProcessingSelection.Gaussian;
            this.rbMedian.Tag = PreProcessingSelection.Median;
            this.rbLaplacian.Tag = PreProcessingSelection.Laplacian;
            this.rbDifference.Tag = PreProcessingSelection.Difference;
            this.rbCrop.Tag = PreProcessingSelection.Crop;
            this.rbZoom.Tag = PreProcessingSelection.Zoom;
            this.rbGrayLevelQ.Tag = PreProcessingSelection.GrayLevelQuan;
            this.rbSpatialQuant.Tag = PreProcessingSelection.SpatialQuant;
            this.rbHistEQ.Tag = PreProcessingSelection.HistEQ;
            this.rbHistStretch.Tag = PreProcessingSelection.HistStretch;

            OnViewerCollectionChanged();
            ResetControls();
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
                int max = (this.currentSelection == PreProcessingSelection.Mean) ? 11 : 31;
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

        private void btnCancel_Click(object sender, EventArgs e)
        {
            MainForm.AnalysisForm.Close();
        } // end Cancel Click

        private void btnHelp_Click(object sender, EventArgs e)
        {
            MainForm.ShowHelp();
        }// End Help Click 

        private void btnReset_Click(object sender, EventArgs e)
        {
            ResetControls();
        } // End Reset Click! 

        private void ResetControls()
        {
            //Mean
            this.cboMaskSize.Text = "3";
            //Median
            this.rbStandard.Checked = true;
            //Gaussian
            this.rbGaussian3x3.Checked = true;
            this.chkNormalize.Checked = true;
            //Laplacian
            this.rbType1.Checked = true;
            //Difference
            this.rb3x3.Checked = true;
            //Crop
            this.cboCropCol.Text = "0";
            this.cboCropRow.Text = "0";
            this.cboCropWidth.Text = "100";
            this.cboCropHeight.Text = "100";
            //Zoom
            this.cboZoomCol.Text = "0";
            this.cboZoomRow.Text = "0";
            this.cboZoomWidth.Text = "64";
            this.cboZoomHeight.Text = "64";
            this.cboZoomFactor.Text = "2.0";
            this.cboZoomMethod.Text = "Zero Order Hold";
            //GLQ
            this.rdbUtilConvertStandard.Checked = true;
            this.cmbUtilConvertNumOfBits.Text = "16";
            //Spatial Quantization
            this.cboSpatialQuantWidth.Text = "32";
            this.cboSpatialQuantHeight.Text = "32";
            this.cboSpatialQuantMethod.Text = "Average Value";
            //Histogram Eq
            this.rbValue.Checked = true;
            //Histogram Stretch
            this.cboLowLimit.Text = "0";
            this.cboHighLimit.Text = "255";
            this.cboLowClip.Text = "0.025";
            this.cboHighClip.Text = "0.025";
            this.lblLowPercent.Text = "2.5%";
            this.lblHighPercent.Text = "2.5%";

            this.currentSelection = PreProcessingSelection.Add;
            this.rbAdd.Checked = true;
            UpdateControls();
        }
        private void btnEditMask_Click(object sender, EventArgs e)
        {
            this.filterMask.Show();
            this.filterMask.Focus();
        }

        private void UpdateControls()
        {
            switch (this.currentSelection)
            {
                case PreProcessingSelection.Add:
                case PreProcessingSelection.Subtract:
                case PreProcessingSelection.Multiply:
                case PreProcessingSelection.Divide:
                case PreProcessingSelection.AND:              
                case PreProcessingSelection.OR:
                case PreProcessingSelection.XOR:
                    this.CurrentImageLabel.Visible = true;
                    this.txtCurrentImage.Visible = true;
                    this.lblSecondImage.Visible = true;
                    this.cboSecondImage.Visible = true;
                    this.pnlMedian.Visible = false;
                    this.pnlGaussian.Visible = false;
                    this.pnlLaplacian.Visible = false;
                    this.pnlDifference.Visible = false;
                    this.pnlCropp.Visible = false;
                    this.pnlGrayLevelQ.Visible = false;
                    this.pnlSpatialQuant.Visible = false;
                    this.pnlHistStretch.Visible = false;
                    this.pnlHistogramEQ.Visible = false;
                    this.grpZoomLocation.Visible = false;
                    this.btnEditMask.Visible = false;
                    this.lblMaskSize.Visible = false;
                    this.cboMaskSize.Visible = false;
                    this.lblMaskSize.Visible = false;
                    break;

                case PreProcessingSelection.NOT:
                    this.CurrentImageLabel.Visible = true;
                    this.txtCurrentImage.Visible = true;
                    this.lblSecondImage.Visible = false;
                    this.cboSecondImage.Visible = false;
                    this.pnlMedian.Visible = false;
                    this.pnlGaussian.Visible = false;
                    this.pnlLaplacian.Visible = false;
                    this.pnlDifference.Visible = false;
                    this.pnlCropp.Visible = false;
                    this.pnlGrayLevelQ.Visible = false;
                    this.pnlSpatialQuant.Visible = false;
                    this.pnlHistStretch.Visible = false;
                    this.pnlHistogramEQ.Visible = false;
                    this.grpZoomLocation.Visible = false;
                    this.btnEditMask.Visible = false;
                    this.lblMaskSize.Visible = false;
                    this.cboMaskSize.Visible = false;
                    this.lblMaskSize.Visible = false;
                    break;

                case PreProcessingSelection.Mean:
                    this.CurrentImageLabel.Visible = false;
                    this.txtCurrentImage.Visible = false;
                    this.lblSecondImage.Visible = false;
                    this.cboSecondImage.Visible = false;
                    this.pnlMedian.Visible = false;
                    this.pnlGaussian.Visible = false;
                    this.pnlLaplacian.Visible = false;
                    this.pnlDifference.Visible = false;
                    this.pnlCropp.Visible = false;
                    this.pnlGrayLevelQ.Visible = false;
                    this.pnlSpatialQuant.Visible = false;
                    this.pnlHistStretch.Visible = false;
                    this.pnlHistogramEQ.Visible = false;
                    this.grpZoomLocation.Visible = false;
                    this.btnEditMask.Visible = false;
                    this.lblMaskSize.Visible = false;
                    this.cboMaskSize.Visible = true;
                    this.lblMaskSize.Visible = true;
                    break;

                case PreProcessingSelection.Median:
                    this.CurrentImageLabel.Visible = false;
                    this.txtCurrentImage.Visible = false;
                    this.lblSecondImage.Visible = false;
                    this.cboSecondImage.Visible = false;
                    this.pnlMedian.Visible = true;
                    this.pnlGaussian.Visible = false;
                    this.pnlLaplacian.Visible = false;
                    this.pnlDifference.Visible = false;
                    this.pnlCropp.Visible = false;
                    this.pnlGrayLevelQ.Visible = false;
                    this.pnlSpatialQuant.Visible = false;
                    this.pnlHistStretch.Visible = false;
                    this.pnlHistogramEQ.Visible = false;
                    this.grpZoomLocation.Visible = false;
                    this.btnEditMask.Visible = false;
                    this.lblMaskSize.Visible = false;
                    this.cboMaskSize.Visible = true;
                    this.lblMaskSize.Visible = true;
                    break;

                case PreProcessingSelection.Laplacian:
                    this.rbType1.Checked = true;
                    double[,] laplacian = null;
                    string text = null;
                    laplacian = laplacianType1;
                    text = "Laplacian Filter Type 1";
                    this.filterMask.DefaultValues = laplacian;
                    this.filterMask.Text = text;

                    this.CurrentImageLabel.Visible = false;
                    this.txtCurrentImage.Visible = false;
                    this.lblSecondImage.Visible = false;
                    this.cboSecondImage.Visible = false;
                    this.pnlMedian.Visible = false;
                    this.pnlGaussian.Visible = false;
                    this.pnlLaplacian.Visible = true;
                    this.pnlDifference.Visible = false;
                    this.pnlCropp.Visible = false;
                    this.pnlGrayLevelQ.Visible = false;
                    this.pnlSpatialQuant.Visible = false;
                    this.pnlHistStretch.Visible = false;
                    this.pnlHistogramEQ.Visible = false;
                    this.grpZoomLocation.Visible = false;
                    this.btnEditMask.Visible = true;
                    this.lblMaskSize.Visible = true;
                    this.cboMaskSize.Visible = false;
                    this.lblMaskSize.Visible = false;
                    break;

                case PreProcessingSelection.GrayLevelQuan:
                    this.CurrentImageLabel.Visible = false;
                    this.txtCurrentImage.Visible = false;
                    this.lblSecondImage.Visible = false;
                    this.cboSecondImage.Visible = false;
                    this.pnlMedian.Visible = false;
                    this.pnlGaussian.Visible = false;
                    this.pnlLaplacian.Visible = false;
                    this.pnlDifference.Visible = false;
                    this.pnlCropp.Visible = false;
                    this.pnlGrayLevelQ.Visible = true;
                    this.pnlSpatialQuant.Visible = false;
                    this.pnlHistStretch.Visible = false;
                    this.pnlHistogramEQ.Visible = false;
                    this.grpZoomLocation.Visible = false;
                    this.btnEditMask.Visible = false;
                    this.lblMaskSize.Visible = false;
                    this.cboMaskSize.Visible = false;
                    this.lblMaskSize.Visible = false;
                    break;

                case PreProcessingSelection.Crop:
                    this.CurrentImageLabel.Visible = false;
                    this.txtCurrentImage.Visible = false;
                    this.lblSecondImage.Visible = false;
                    this.cboSecondImage.Visible = false;
                    this.pnlMedian.Visible = false;
                    this.pnlGaussian.Visible = false;
                    this.pnlLaplacian.Visible = false;
                    this.pnlDifference.Visible = false;
                    this.pnlCropp.Visible = true;
                    this.pnlGrayLevelQ.Visible = false;
                    this.pnlSpatialQuant.Visible = false;
                    this.pnlHistStretch.Visible = false;
                    this.pnlHistogramEQ.Visible = false;
                    this.grpZoomLocation.Visible = false;
                    this.btnEditMask.Visible = false;
                    this.lblMaskSize.Visible = false;
                    this.cboMaskSize.Visible = false;
                    this.lblMaskSize.Visible = false;
                    break;

                case PreProcessingSelection.Zoom:
                    this.CurrentImageLabel.Visible = false;
                    this.txtCurrentImage.Visible = false;
                    this.lblSecondImage.Visible = false;
                    this.cboSecondImage.Visible = false;
                    this.pnlMedian.Visible = false;
                    this.pnlGaussian.Visible = false;
                    this.pnlLaplacian.Visible = false;
                    this.pnlDifference.Visible = false;
                    this.pnlCropp.Visible = false;
                    this.pnlGrayLevelQ.Visible = false;
                    this.pnlSpatialQuant.Visible = false;
                    this.pnlHistStretch.Visible = false;
                    this.pnlHistogramEQ.Visible = false;
                    this.grpZoomLocation.Visible = true;
                    this.btnEditMask.Visible = false;
                    this.lblMaskSize.Visible = false;
                    this.cboMaskSize.Visible = false;
                    this.lblMaskSize.Visible = false;
                    break;

                case PreProcessingSelection.Gaussian:
                    double[,] filter = null;
                    string dimensions = " " + this.MaskSize.ToString() + "x" + this.MaskSize.ToString();
                    filter = SpecifyFilterGaussian();
                    this.filterMask.DefaultValues = filter;
                    this.filterMask.Text = "Gaussian " + dimensions;

                    this.CurrentImageLabel.Visible = false;
                    this.txtCurrentImage.Visible = false;
                    this.lblSecondImage.Visible = false;
                    this.cboSecondImage.Visible = false;
                    this.pnlMedian.Visible = false;
                    this.pnlGaussian.Visible = true;
                    this.pnlLaplacian.Visible = false;
                    this.pnlDifference.Visible = false;
                    this.pnlCropp.Visible = false;
                    this.pnlGrayLevelQ.Visible = false;
                    this.pnlSpatialQuant.Visible = false;
                    this.pnlHistStretch.Visible = false;
                    this.pnlHistogramEQ.Visible = false;
                    this.grpZoomLocation.Visible = false;
                    this.btnEditMask.Visible = true;
                    this.lblMaskSize.Visible = true;
                    this.cboMaskSize.Visible = false;
                    this.lblMaskSize.Visible = false;

                    break;
                case PreProcessingSelection.Difference:
                    this.rb3x3.Checked = true;
                    this.filterMask.chkKeepOriginal.Checked = false;
                    this.filterMask.MaskSize = new Size(3, 3);
                    this.filterMask.ShowArrows = true;
                    this.filterMask.Text = "Difference Filter";
                    this.filterMask.ArrowUpClick();

                    this.CurrentImageLabel.Visible = false;
                    this.txtCurrentImage.Visible = false;
                    this.lblSecondImage.Visible = false;
                    this.cboSecondImage.Visible = false;
                    this.pnlMedian.Visible = false;
                    this.pnlGaussian.Visible = false;
                    this.pnlLaplacian.Visible = false;
                    this.pnlDifference.Visible = true;
                    this.pnlCropp.Visible = false;
                    this.pnlGrayLevelQ.Visible = false;
                    this.pnlSpatialQuant.Visible = false;
                    this.pnlHistStretch.Visible = false;
                    this.pnlHistogramEQ.Visible = false;
                    this.grpZoomLocation.Visible = false;
                    this.btnEditMask.Visible = true;
                    this.lblMaskSize.Visible = true;
                    this.cboMaskSize.Visible = false;
                    this.lblMaskSize.Visible = false;
                    break;


                case PreProcessingSelection.SpatialQuant:
                    this.CurrentImageLabel.Visible = false;
                    this.txtCurrentImage.Visible = false;
                    this.lblSecondImage.Visible = false;
                    this.cboSecondImage.Visible = false;
                    this.pnlMedian.Visible = false;
                    this.pnlGaussian.Visible = false;
                    this.pnlLaplacian.Visible = false;
                    this.pnlDifference.Visible = false;
                    this.pnlCropp.Visible = false;
                    this.pnlGrayLevelQ.Visible = false;
                    this.pnlSpatialQuant.Visible = true;
                    this.pnlHistStretch.Visible = false;
                    this.pnlHistogramEQ.Visible = false;
                    this.grpZoomLocation.Visible = false;
                    this.btnEditMask.Visible = false;
                    this.lblMaskSize.Visible = false;
                    this.cboMaskSize.Visible = false;
                    this.lblMaskSize.Visible = false;
                    break;

                case PreProcessingSelection.HistEQ:
                    this.CurrentImageLabel.Visible = false;
                    this.txtCurrentImage.Visible = false;
                    this.lblSecondImage.Visible = false;
                    this.cboSecondImage.Visible = false;
                    this.pnlMedian.Visible = false;
                    this.pnlGaussian.Visible = false;
                    this.pnlLaplacian.Visible = false;
                    this.pnlDifference.Visible = false;
                    this.pnlCropp.Visible = false;
                    this.pnlGrayLevelQ.Visible = false;
                    this.pnlSpatialQuant.Visible = false;
                    this.pnlHistStretch.Visible = false;
                    this.pnlHistogramEQ.Visible = true;
                    this.grpZoomLocation.Visible = false;
                    this.btnEditMask.Visible = false;
                    this.lblMaskSize.Visible = false;
                    this.cboMaskSize.Visible = false;
                    this.lblMaskSize.Visible = false;
                    break;

                case PreProcessingSelection.HistStretch:
                    this.CurrentImageLabel.Visible = false;
                    this.txtCurrentImage.Visible = false;
                    this.lblSecondImage.Visible = false;
                    this.cboSecondImage.Visible = false;
                    this.pnlMedian.Visible = false;
                    this.pnlGaussian.Visible = false;
                    this.pnlLaplacian.Visible = false;
                    this.pnlDifference.Visible = false;
                    this.pnlCropp.Visible = false;
                    this.pnlGrayLevelQ.Visible = false;
                    this.pnlSpatialQuant.Visible = false;
                    this.pnlHistStretch.Visible = true;
                    this.pnlHistogramEQ.Visible = false;
                    this.grpZoomLocation.Visible = false;
                    this.btnEditMask.Visible = false;
                    this.lblMaskSize.Visible = false;
                    this.cboMaskSize.Visible = false;
                    this.lblMaskSize.Visible = false;
                    break;
            }
        }

        private void rbLaplacianType_CheckedChanged(object sender, EventArgs e)
        {
            double[,] laplacian = null;
            string text = null;
            if (this.rbType1.Checked)
            {
                laplacian = laplacianType1;
                text = "Laplacian Filter Type 1";


            }
            else if (this.rbType2.Checked)
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

        private void rbDifference_CheckedChanged(object sender, EventArgs e)
        {
            this.filterMask.MaskSize = new Size(this.MaskSize, this.MaskSize);
            if (this.filterMask.currentArrowClick != null)
            {
                this.filterMask.currentArrowClick();
            }

        }

        private void rbcboSpecifyFilter_ParameterChanged(object sender, EventArgs e)
        {
            double[,] filter = null;
            string dimensions = " " + this.MaskSize.ToString() + "x" + this.MaskSize.ToString();
            filter = SpecifyFilterGaussian();
            this.filterMask.DefaultValues = filter;
            this.filterMask.Text = "Gaussian " + dimensions;
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

        private int CropCol { get { return int.Parse(this.cboCropCol.Text); } }
        private int CropRow { get { return int.Parse(this.cboCropRow.Text); } }
        //private int SpatialQuantMethod { get { return this.cboSpatialQuantMethod.SelectedIndex + 1; } }

        private int HeightParameter
        {
            get
            {
                int Height = 0;
                switch (this.currentSelection)
                {
                    case PreProcessingSelection.Crop:
                        Height = int.Parse(this.cboCropHeight.Text);
                        break;
                    case PreProcessingSelection.SpatialQuant:
                        Height = int.Parse(this.cboSpatialQuantHeight.Text);
                        break;

                }
                return Height;
                /*
                int width = 0;
                width = int.Parse(this.cboCropWidth.Text);
                return width;
                */
            }
        }
        private int WidthParameter
        {
            get
            {
                int width = 0;
                switch (this.currentSelection)
                {
                    case PreProcessingSelection.Crop:
                        width = int.Parse(this.cboCropWidth.Text);
                        break;
                    case PreProcessingSelection.SpatialQuant:
                        width = int.Parse(this.cboSpatialQuantWidth.Text);
                        break;

                }
                return width;
                /*
                int width = 0;
                width = int.Parse(this.cboCropWidth.Text);
                return width;
                */
            }
        }

        private void OnBoundingRectangleChanged(Rectangle rect, ViewerForm viewer)
        {
            if ((viewer == MainForm.Viewers.SelectedViewer) &&
                (PreProcessingSelection.Crop == this.currentSelection))
            {
                this.cboCropRow.Text = rect.Y.ToString();
                this.cboCropCol.Text = rect.X.ToString();
                this.cboCropHeight.Text = rect.Height.ToString();
                this.cboCropWidth.Text = rect.Width.ToString();
            }
        }


        //private ZoomQuadrant ZoomQuadrant
        //{
        //    get
        //    {
        //        ZoomQuadrant zq = ZoomQuadrant.all;
        //        if (this.rbZoomArea.Checked)
        //            zq = ZoomQuadrant.area;
        //        else if (this.rbZoomUpperLeft.Checked)
        //            zq = ZoomQuadrant.upperleft;
        //        else if (this.rbZoomUpperRight.Checked)
        //            zq = ZoomQuadrant.upperright;
        //        else if (this.rbZoomLowerLeft.Checked)
        //            zq = ZoomQuadrant.lowerleft;
        //        else if (this.rbZoomLowerRight.Checked)
        //            zq = ZoomQuadrant.lowerright;
        //        return ZoomQuadrant.area;
        //    }
        //}
        private int ZoomCol { get { return int.Parse(this.cboZoomCol.Text); } }
        private int ZoomRow { get { return int.Parse(this.cboZoomRow.Text); } }
        private int ZoomHeight { get { return int.Parse(this.cboZoomHeight.Text); } }
        private int ZoomWidth { get { return int.Parse(this.cboZoomWidth.Text); } }
        private float ZoomFactor { get { return float.Parse(this.cboZoomFactor.Text); } }
        private int SpatialQuantMethod { get { return this.cboSpatialQuantMethod.SelectedIndex + 1; } }


        private ResizeMethod ZoomMethod { get { return (ResizeMethod)this.cboZoomMethod.SelectedIndex; } }
        private void OnSelectedRectangleChanged(Rectangle rect, ViewerForm viewer)
        {
            if (viewer == MainForm.Viewers.SelectedViewer)
            {
                this.cboZoomCol.Text = rect.X.ToString();
                this.cboZoomRow.Text = rect.Y.ToString();
                this.cboZoomWidth.Text = rect.Width.ToString();
                this.cboZoomHeight.Text = rect.Height.ToString();
            }
        }
        private void cboPositiveIntVal_Validating(object sender, CancelEventArgs e)
        {
            ComboBox cbo = sender as ComboBox;
            int val;
            if (!int.TryParse(cbo.Text, out val) || (val <= 0))
            {
                MessageBox.Show("Please check the input value. Only positive integers are accepted.",
                   "Positive Integer Required", MessageBoxButtons.OK, MessageBoxIcon.Warning);
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
        private void cboZoomFactor_Validating(object sender, CancelEventArgs e)
        {
            float val;
            if (!float.TryParse(this.cboZoomFactor.Text, out val) ||
                (val < 0.01f) || (val > 10.0f))
            {
                MessageBox.Show("Please check the input value. Only values in the range 0.01 to 10.0 are accepted.",
                   "Zoom Factor", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                this.cboZoomFactor.SelectAll();
                e.Cancel = true;
            }
        }

        private void cboCropZoom_Validated(object sender, EventArgs e)
        {
            ViewerForm viewer = MainForm.Viewers.SelectedViewer;
            if (viewer != null)
            {
                Rectangle rect = new Rectangle();
                rect.X = this.ZoomCol;
                rect.Y = this.ZoomRow;
                rect.Width = this.ZoomWidth;
                rect.Height = this.ZoomHeight;
                viewer.SelectRect(rect);
            }
        }

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

        private int LowLimit { get { return int.Parse(this.cboLowLimit.Text); } }
        private int HighLimit { get { return int.Parse(this.cboHighLimit.Text); } }
        private float LowClip { get { return float.Parse(this.cboLowClip.Text); } }
        private float HighClip { get { return float.Parse(this.cboHighClip.Text); } }

        private int MaskSize
        {
            get
            {
                int mask = -1;
                switch (this.currentSelection)
                {
                    case PreProcessingSelection.Mean:
                        mask = int.Parse(this.cboMaskSize.Text);
                        break;
                    case PreProcessingSelection.Median:
                        mask = int.Parse(this.cboMaskSize.Text);
                        break;
                    case PreProcessingSelection.Difference:
                        if (this.rb3x3.Checked)
                            mask = 3;
                        else if (this.rb5x5.Checked)
                            mask = 5;
                        else if (this.rb7x7.Checked)
                            mask = 7;
                        else if (this.rb9x9.Checked)
                            mask = 9;
                        else
                            mask = 11;
                        break;
                    case PreProcessingSelection.Gaussian:
                        if (this.rbGaussian3x3.Checked)
                            mask = 3;
                        else if (this.rbGaussian5x5.Checked)
                            mask = 5;
                        else if (this.rbGaussianz7x7.Checked)
                            mask = 7;
                        else if (this.rbGaussian9x9.Checked)
                            mask = 9;
                        else
                            mask = 11;
                        break;


                }
                return mask;
            }
        }

        private void Percent_TextChanged(object sender, EventArgs e)
        {
            ComboBox cbo = sender as ComboBox;
            if(cbo.Name == "cboLowClip")
            {
                float percent = float.Parse(this.cboLowClip.Text) * 100;
                lblLowPercent.Text = percent.ToString() + "%";
            }
            else
            {
                float percent = float.Parse(this.cboHighClip.Text) * 100;
                lblHighPercent.Text = percent.ToString() + "%";
            }
        }
    }
}
