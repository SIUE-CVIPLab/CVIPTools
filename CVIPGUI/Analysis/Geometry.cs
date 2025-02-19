/*''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' ======================================================================
' Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
' ======================================================================
'
'             File Name: Geometry.cs
'           Description: Contains the controls and code
'                        for Analysis->Geometry page
'         Related Files: CvipOp.cs
'                        CvipConstant.cs
'   Initial Coding Date: November 2007
'              Modified: March 2013
'       Delevoping tool: Visual Studio 2010-C#
'             Credit(s): Patrick Solt
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

namespace CVIPGUI.Analysis
{
    enum GeometrySelection
    {
        crop,
        paste,
        resize,
        rotate,
        translate,
        zoom
    }
    enum ResizeMethod : int
    {
        zero_order_hold = 0,
        linear_interpolation = 1
    }
    enum ZoomQuadrant : int
    {
        upperleft = 1,
        upperright = 2,
        lowerleft = 3,
        lowerright = 4,
        all = 5,
        area = 6
    }
    public partial class Geometry : UserControl
    {
        private GeometrySelection currentSelection = GeometrySelection.crop;

        public Geometry()
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
            case GeometrySelection.crop:
                if (viewer.SelectedArea == null)
                {
                    Rectangle rect = new Rectangle();
                    rect.X = this.CropCol;
                    rect.Y = this.CropRow;
                    rect.Width = this.CropWidth;
                    rect.Height = this.CropHeight;
                    viewer.SelectRect(rect);
                }
                outputImage = viewer.SelectedImage;
                break;

            case GeometrySelection.paste:
                ViewerForm copySrc = this.cboImages.SelectedItem as ViewerForm;
                if (copySrc == null)
                {
                    MessageBox.Show("You must select image to copy!", "No copy image!",
                        MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    break;
                }
                outputImage = CvipOp.Copy_Paste(copySrc.CVIPimage, inputImage, 0, 0, copySrc.ImageHeight, copySrc.ImageWidth, this.PasteRow, this.PasteCol, this.PasteTransparently);
                break;

            case GeometrySelection.resize:
                if (viewer.SelectedArea != null)
                {
                    CvipOp.Delete_Image(ref inputImage);
                    inputImage = viewer.SelectedImage;
                }
                int imageHeight = CvipOp.GetNoOfRows_Image(inputImage);
                int imageWidth = CvipOp.GetNoOfCols_Image(inputImage);
                if ((imageHeight == this.ResizeHeight) && (imageWidth == this.ResizeWidth))
                {
                    MessageBox.Show("The new size is the same as before, no action performed", "Resize Parameters",
                        MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    break;
                }
                float heightFactor = (float)this.ResizeHeight / (float)imageHeight;
                float widthFactor = (float)this.ResizeWidth / (float)imageWidth;
                float maxFactor = Math.Max(heightFactor, widthFactor);
                if (this.ResizeMethod == ResizeMethod.zero_order_hold)
                {
                    if (maxFactor > 1.0f)
                    {
                        outputImage = CvipOp.Enlarge(inputImage, (int)((float)imageHeight * maxFactor), (int)((float)imageWidth * maxFactor));
                        if ((outputImage != 0) && (heightFactor != widthFactor))
                        {
                            CvipOp.Delete_Image(ref inputImage);
                            inputImage = outputImage;
                            outputImage = CvipOp.Spatial_Quant(inputImage, this.ResizeHeight, this.ResizeWidth, 1);
                        }
                    }
                    else
                        outputImage = CvipOp.Spatial_Quant(inputImage, this.ResizeHeight, this.ResizeWidth, 1);
                }
                else // linear interpolation
                    outputImage = CvipOp.Bilinear_Interp1(inputImage, widthFactor, heightFactor);
                break;

            case GeometrySelection.rotate:
                outputImage = CvipOp.Rotate(inputImage, this.RotateDegrees);
                break;

            case GeometrySelection.translate:
                outputImage = CvipOp.Translate(inputImage, this.TranslateWrap, 0, 0, viewer.ImageHeight, viewer.ImageWidth, this.TranslateDown, this.TranslateRight, this.TranslateGrayLevel);
                break;

            case GeometrySelection.zoom:
                if (this.ZoomQuadrant == ZoomQuadrant.area)
                {
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
                    inputImage = viewer.SelectedImage;
                    if (this.ZoomMethod == ResizeMethod.zero_order_hold)
                        outputImage = CvipOp.Zoom(inputImage, (int)ZoomQuadrant.all, -1, -1, -1, -1, this.ZoomFactor);
                    else
                        outputImage = CvipOp.Bilinear_Interp1(inputImage, this.ZoomFactor, this.ZoomFactor);
                }
                else
                {
                    if (this.ZoomMethod == ResizeMethod.zero_order_hold)
                        outputImage = CvipOp.Zoom(inputImage, (int)this.ZoomQuadrant, -1, -1, -1, -1, this.ZoomFactor);
                    else
                    {
                        inputImage = CvipOp.Zoom(inputImage, (int)this.ZoomQuadrant, -1, -1, -1, -1, 1);
                        outputImage = CvipOp.Bilinear_Interp1(inputImage, this.ZoomFactor, this.ZoomFactor);
                    }
                }
                break;
            }
            if (outputImage != 0)
            {
                string newImageName = viewer.Text;
                newImageName += "_";
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
        private void cboCropZoom_Validated(object sender, EventArgs e)
        {
            ViewerForm viewer = MainForm.Viewers.SelectedViewer;
            if (viewer != null)
            {
                Rectangle rect = new Rectangle();
                switch (this.currentSelection)
                {
                case GeometrySelection.crop:
                    rect.X = this.CropCol;
                    rect.Y = this.CropRow;
                    rect.Width = this.CropWidth;
                    rect.Height = this.CropHeight;
                    break;

                case GeometrySelection.zoom:
                    rect.X = this.ZoomCol;
                    rect.Y = this.ZoomRow;
                    rect.Width = this.ZoomWidth;
                    rect.Height = this.ZoomHeight;
                    break;
                }
                viewer.SelectRect(rect);
            }
        }
        private void cboFloatVal_Validating(object sender, CancelEventArgs e)
        {
            ComboBox cbo = sender as ComboBox;
            float val;
            if (!float.TryParse(cbo.Text, out val))
            {
                MessageBox.Show("Please check the input value. Only float values are accepted.",
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
        private void chkTranslateWrap_CheckedChanged(object sender, EventArgs e)
        {
            this.cboTranslateGrayLevel.Enabled = this.chkTranslateWrap.Checked;
        }
        protected override void OnLoad(EventArgs e)
        {
            base.OnLoad(e);

            this.rbCrop.Tag = GeometrySelection.crop;
            this.rbPaste.Tag = GeometrySelection.paste;
            this.rbResize.Tag = GeometrySelection.resize;
            this.rbRotate.Tag = GeometrySelection.rotate;
            this.rbTranslate.Tag = GeometrySelection.translate;
            this.rbZoom.Tag = GeometrySelection.zoom;

            OnViewerCollectionChanged();
            ResetControls();
        }
        private void OnSelectedRectangleChanged(Rectangle rect, ViewerForm viewer)
        {
            if (viewer == MainForm.Viewers.SelectedViewer)
            {
                switch (this.currentSelection)
                {
                case GeometrySelection.crop:
                    this.cboCropCol.Text = rect.X.ToString();
                    this.cboCropRow.Text = rect.Y.ToString();
                    this.cboCropWidth.Text = rect.Width.ToString();
                    this.cboCropHeight.Text = rect.Height.ToString();
                    break;

                case GeometrySelection.zoom:
                    this.cboZoomCol.Text = rect.X.ToString();
                    this.cboZoomRow.Text = rect.Y.ToString();
                    this.cboZoomWidth.Text = rect.Width.ToString();
                    this.cboZoomHeight.Text = rect.Height.ToString();
                    break;
                }
            }
        }
        private void OnSelectedViewerChanged(ViewerForm viewer)
        {
            if ((this.currentSelection == GeometrySelection.paste) &&
                (((ModifierKeys & Keys.Shift) == Keys.Shift) || (this.cboImages.SelectedItem == null)))
            {
                this.cboImages.SelectedItem = viewer;
            }
            UpdateControls();
        }
        private void OnViewerCollectionChanged()
        {
            if (MainForm.Viewers != null)
            {
                ViewerForm selected = this.cboImages.SelectedItem as ViewerForm;
                if (selected == null) selected = MainForm.Viewers.SelectedViewer;
                this.cboImages.Items.Clear();
                foreach (ViewerForm viewer in MainForm.Viewers)
                    this.cboImages.Items.Add(viewer);
                this.cboImages.SelectedItem = selected;
            }
        }
        private void rbGeometry_CheckedChanged(object sender, EventArgs e)
        {
            RadioButton rb = sender as RadioButton;
            if ((rb != null) && rb.Checked && (rb.Tag != null))
            {
                this.currentSelection = (GeometrySelection)rb.Tag;
                UpdateControls();
            }
        }
        private void ResetControls()
        {
            this.cboCropCol.Text = "0";
            this.cboCropRow.Text = "0";
            this.cboCropWidth.Text = "100";
            this.cboCropHeight.Text = "100";
            this.cboPasteCol.Text = "128";
            this.cboPasteRow.Text = "128";
            this.chkTransparently.Checked = false;
            this.cboResizeWidth.Text = "256";
            this.cboResizeHeight.Text = "256";
            this.cboResizeMethod.SelectedIndex = 0;
            this.cboRotateDegrees.Text = "90";
            this.cboTranslateRight.Text = "128";
            this.cboTranslateDown.Text = "128";
            this.cboTranslateGrayLevel.Text = "128";
            this.chkTranslateWrap.Checked = false;
            this.cboZoomCol.Text = "0";
            this.cboZoomRow.Text = "0";
            this.cboZoomHeight.Text = "64";
            this.cboZoomWidth.Text = "64";
            this.cboZoomFactor.Text = "2.0";
            this.cboZoomMethod.SelectedIndex = 0;
            this.rbZoomArea.Checked = true;

            // Default current selection
            this.currentSelection = GeometrySelection.crop;
            this.rbCrop.Checked = true;
            UpdateControls();
        }
        private void UpdateControls()
        {
            if (MainForm.Viewers != null)
            {
                this.cboTranslateGrayLevel.Enabled = this.chkTranslateWrap.Checked;
                ViewerForm viewer = MainForm.Viewers.SelectedViewer;
                if ((viewer != null) &&
                    ((viewer.SelectionState == SelectionState.BorderSelected) ||
                    (viewer.SelectionState == SelectionState.RectangleSelected)))
                {
                    Rectangle rect = viewer.BoundingRectangle;
                    switch (this.currentSelection)
                    {
                    case GeometrySelection.crop:
                        this.cboCropCol.Text = rect.X.ToString();
                        this.cboCropRow.Text = rect.Y.ToString();
                        this.cboCropWidth.Text = rect.Width.ToString();
                        this.cboCropHeight.Text = rect.Height.ToString();
                        break;

                    case GeometrySelection.zoom:
                        this.cboZoomCol.Text = rect.X.ToString();
                        this.cboZoomRow.Text = rect.Y.ToString();
                        this.cboZoomWidth.Text = rect.Width.ToString();
                        this.cboZoomHeight.Text = rect.Height.ToString();
                        break;
                    }
                }
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
                    ViewerForm.BoundingRectangleChanged += this.OnSelectedRectangleChanged;
                    OnViewerCollectionChanged();
                    break;

                case WM.DESTROY:
                    MainForm.Viewers.SelectedViewerChanged -= this.OnSelectedViewerChanged;
                    MainForm.Viewers.ViewerCollectionChanged -= this.OnViewerCollectionChanged;
                    ViewerForm.BoundingRectangleChanged -= this.OnSelectedRectangleChanged;
                    break;
                }
            }
        }

        private float RotateDegrees { get { return float.Parse(this.cboRotateDegrees.Text); } }
        private float TranslateGrayLevel { get { return float.Parse(this.cboTranslateGrayLevel.Text); } }
        private float ZoomFactor { get { return float.Parse(this.cboZoomFactor.Text); } }

        private int CropCol { get { return int.Parse(this.cboCropCol.Text); } }
        private int CropRow { get { return int.Parse(this.cboCropRow.Text); } }
        private int CropHeight { get { return int.Parse(this.cboCropHeight.Text); } }
        private int CropWidth { get { return int.Parse(this.cboCropWidth.Text); } }
        private int PasteCol { get { return int.Parse(this.cboPasteCol.Text); } }
        private int PasteRow { get { return int.Parse(this.cboPasteRow.Text); } }
        private int PasteTransparently { get { return this.chkTransparently.Checked ? 1 : 0; } }
        private int ResizeHeight { get { return int.Parse(this.cboResizeHeight.Text); } }
        private int ResizeWidth { get { return int.Parse(this.cboResizeWidth.Text); } }
        private int TranslateDown { get { return int.Parse(this.cboTranslateDown.Text); } }
        private int TranslateRight { get { return int.Parse(this.cboTranslateRight.Text); } }
        private int TranslateWrap { get { return this.chkTranslateWrap.Checked ? 0 : 1; } }
        private int ZoomCol { get { return int.Parse(this.cboZoomCol.Text); } }
        private int ZoomRow { get { return int.Parse(this.cboZoomRow.Text); } }
        private int ZoomHeight { get { return int.Parse(this.cboZoomHeight.Text); } }
        private int ZoomWidth { get { return int.Parse(this.cboZoomWidth.Text); } }

        private ResizeMethod ResizeMethod { get { return (ResizeMethod)this.cboResizeMethod.SelectedIndex; } }
        private ResizeMethod ZoomMethod { get { return (ResizeMethod)this.cboZoomMethod.SelectedIndex; } }
        private ZoomQuadrant ZoomQuadrant
        {
            get
            {
                ZoomQuadrant zq = ZoomQuadrant.all;
                if (this.rbZoomArea.Checked)
                    zq = ZoomQuadrant.area;
                else if (this.rbZoomUpperLeft.Checked)
                    zq = ZoomQuadrant.upperleft;
                else if (this.rbZoomUpperRight.Checked)
                    zq = ZoomQuadrant.upperright;
                else if (this.rbZoomLowerLeft.Checked)
                    zq = ZoomQuadrant.lowerleft;
                else if (this.rbZoomLowerRight.Checked)
                    zq = ZoomQuadrant.lowerright;
                return zq;
            }
        }

        private void grpZoomLocation_Enter(object sender, EventArgs e)
        {

        }
    }
}
