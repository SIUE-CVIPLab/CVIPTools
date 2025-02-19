/*''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' ======================================================================
' Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
' ======================================================================
'
'             File Name: UtilSize.cs
'           Description: Contains the controls and code
'                        for Utilities->UtilSize page
'         Related Files: CvipOp.cs
'                        CvipConstant.cs
'   Initial Coding Date: April 2007
'              Modified: August 2009
'       Delevoping tool: Visual Studio 2010-C#
'             Credit(s): Wenjun(Evan) Bian
'                        Patrick Solt
Hari Siva Kumar Reddy Bhogala
'                        Southern Illinois University Edwardsville
'
'  Copyright (C) 2013 Scott Umbaugh and SIUE
'
'  Permission to use, copy, modify, and distribute this software and its
'  documentation for any non-commercial purpose and without fee is hereby
'  granted, provided that the above copyright notice appear in all copies
'  and that both that copyright notice and this permission notice appear
'  in supporting documentation.  This software is provided "as is"
'  without express or implied warranty.
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
    public partial class UtilSize : UserControl
    {
        private string strOpName;

        public UtilSize()
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

            this.btnApply.Enabled = false;
            this.Cursor = Cursors.WaitCursor;

            int inputImage = viewer.CVIPimage, outputImage = 0;
            string appendix = "";

            switch (this.strOpName)
            {
            case "Crop":
                if (this.CropCol < 0 || this.CropRow < 0 )
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

            case "Double Size":
                if (viewer.SelectedArea != null)
                {
                    CvipOp.Delete_Image(ref inputImage);
                    inputImage = viewer.SelectedImage;
                }
                outputImage = CvipOp.Local_Adaptive_Zoom(inputImage);
                appendix = "SzeFstDublSze";
                break;

            case "Resize":
                if (viewer.SelectedArea != null)
                {
                    CvipOp.Delete_Image(ref inputImage);
                    inputImage = viewer.SelectedImage;
                }
                int imageHeight = CvipOp.GetNoOfRows_Image(inputImage);
                int imageWidth = CvipOp.GetNoOfCols_Image(inputImage);

                if ((this.HeightParameter < 2) || (this.WidthParameter < 2))
                {
                    MessageBox.Show("Check Height/Width Values(Must be > 1)", "Positive Value Required",
                        MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    break;
                }
                if ((imageHeight == this.HeightParameter) && (imageWidth == this.WidthParameter))
                {
                    MessageBox.Show("The new size is the same as before, no action performed", "Resize Parameters",
                        MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    break;
                }
                float heightFactor = (float)this.HeightParameter / (float)imageHeight;
                float widthFactor = (float)this.WidthParameter / (float)imageWidth;
                float maxFactor = Math.Max(heightFactor, widthFactor);
                if (this.rbZeroOrderHold.Checked)
                {
                    if (maxFactor > 1.0f)
                    {
                        outputImage = CvipOp.Enlarge(inputImage, (int)((float)imageHeight * maxFactor), (int)((float)imageWidth * maxFactor));
                        if ((outputImage != 0) && (heightFactor != widthFactor))
                        {
                            CvipOp.Delete_Image(ref inputImage);
                            inputImage = outputImage;
                            outputImage = CvipOp.Spatial_Quant(inputImage, this.HeightParameter, this.WidthParameter, 1);
                        }
                    }
                    else
                        outputImage = CvipOp.Spatial_Quant(inputImage, this.HeightParameter, this.WidthParameter, 1);
                }
                else // linear interpolation
                    outputImage = CvipOp.Bilinear_Interp1(inputImage, widthFactor, heightFactor);
                appendix = "SzeReSze";
                break;

            case "Spatial Quant":
                if (viewer.SelectedArea != null)
                {
                    CvipOp.Delete_Image(ref inputImage);
                    inputImage = viewer.SelectedImage;
                }
                if ((this.HeightParameter <1) || (this.WidthParameter < 1))
                {
                    MessageBox.Show("Check Height/Width Values", "Positive Value Required",
                        MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    break;
                }
                if (this.SpatialQuantMethod == 2 &&((this.HeightParameter <1) || (this.WidthParameter < 1)) )
                {
                    MessageBox.Show("Check Height/Width Values (Must be > 1)", "Positive Value Required",
                        MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    break;
                }
                //MessageBox.Show(this.SpatialQuantMethod.ToString());


                outputImage = CvipOp.Spatial_Quant(inputImage, this.HeightParameter, this.WidthParameter, this.SpatialQuantMethod);
                appendix = "SzeSptialQuant";
                break;
            }

            if (outputImage != 0)
            {
                string newImageName = viewer.Text;
                //newImageName += "_" + appendix;
                //newImageName += CvipConstant.imageNameCount++.ToString();
                //MainForm.Viewers.Add(outputImage, newImageName);

                newImageName += "_" + CvipFunctionNames.getFncName(appendix);
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

        private void btnHelp_Click(object sender, EventArgs e)
        {
            MainForm.ShowHelp();
        }

        private void btnReset_Click(object sender, EventArgs e)
        {
            ResetControls();
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

        public void Init(string op)
        {
            this.strOpName = op;
            this.pnlCrop.Visible = (this.strOpName == "Crop");
            this.pnlResize.Visible = (this.strOpName == "Resize");
            this.pnlSpatialQuant.Visible = (this.strOpName == "Spatial Quant");
        }

        protected override void OnLoad(EventArgs e)
        {
            base.OnLoad(e);

            this.pnlCrop.Location = new Point(4, 20);
            this.pnlResize.Location = new Point(4, 20);
            this.pnlSpatialQuant.Location = new Point(4, 20);
          // this.Size = new Size(436, 140);

            if (MainForm.Viewers != null)
                OnSelectedViewerChanged(MainForm.Viewers.SelectedViewer);
            ResetControls();
        }

        private void OnBoundingRectangleChanged(Rectangle rect, ViewerForm viewer)
        {
            if ((viewer == MainForm.Viewers.SelectedViewer) &&
                (this.strOpName == "Crop"))
            {
                this.cboCropRow.Text = rect.Y.ToString();
                this.cboCropCol.Text = rect.X.ToString();
                this.cboCropHeight.Text = rect.Height.ToString();
                this.cboCropWidth.Text = rect.Width.ToString();
            }
        }

        private void OnSelectedViewerChanged(ViewerForm viewer)
        {
            this.txtCurrentImage.Text = (viewer == null) ? null : viewer.Text;
        }

        private void ResetControls()
        {
            switch (this.strOpName)
            {
            case "Crop":
                this.cboCropCol.Text = "0";
                this.cboCropRow.Text = "0";
                this.cboCropWidth.Text = "100";
                this.cboCropHeight.Text = "100";
                break;

            case "Resize":
                this.cboResizeWidth.Text = "256";
                this.cboResizeHeight.Text = "256";
                this.rbZeroOrderHold.Checked = true;
                break;

            case "Spatial Quant":
                this.cboSpatialQuantWidth.Text = "32";
                this.cboSpatialQuantHeight.Text = "32";
                this.cboSpatialQuantMethod.SelectedIndex = 1;
                break;
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
                    ViewerForm.BoundingRectangleChanged += this.OnBoundingRectangleChanged;
                    break;

                case WM.DESTROY:
                    MainForm.Viewers.SelectedViewerChanged -= this.OnSelectedViewerChanged;
                    ViewerForm.BoundingRectangleChanged -= this.OnBoundingRectangleChanged;
                    break;
                }
            }
        }

        private int CropCol { get { return int.Parse(this.cboCropCol.Text); } }
        private int CropRow { get { return int.Parse(this.cboCropRow.Text); } }
        private int SpatialQuantMethod { get { return this.cboSpatialQuantMethod.SelectedIndex + 1; } }

        private int HeightParameter
        {
            get
            {
                int height = 0;
                switch (this.strOpName)
                {
                case "Crop":
                    height = int.Parse(this.cboCropHeight.Text);
                    break;

                case "Resize":
                    height = int.Parse(this.cboResizeHeight.Text);
                    break;

                case "Spatial Quant":
                    height = int.Parse(this.cboSpatialQuantHeight.Text);
                    break;
                }
                return height;
            }
        }
        private int WidthParameter
        {
            get
            {
                int width = 0;
                switch (this.strOpName)
                {
                case "Crop":
                    width = int.Parse(this.cboCropWidth.Text);
                    break;

                case "Resize":
                    width = int.Parse(this.cboResizeWidth.Text);
                    break;

                case "Spatial Quant":
                    width = int.Parse(this.cboSpatialQuantWidth.Text);
                    break;
                }
                return width;
            }
        }

        private void grpSize_Enter(object sender, EventArgs e)
        {

        }
    }
}
