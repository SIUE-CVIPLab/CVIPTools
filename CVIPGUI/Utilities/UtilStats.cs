/*''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' ======================================================================
' Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
' ======================================================================
'
'             File Name: UtilStats.cs
'           Description: Contains the controls and code
'                        for Utilities->UtilStats page
'         Related Files: CvipOp.cs
'                        CvipConstant.cs
'   Initial Coding Date: April 2007
'              Modified: March 2010
'       Delevoping tool: Visual Studio 2008-C#
'             Credit(s): Wenjun(Evan) Bian
'                        Patrick Solt
'                        Southern Illinois University Edwardsville
'
' Copyright (C) 2010 Scott Umbaugh and SIUE
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
    public partial class UtilStats : UserControl
    {
        ViewerForm SelectedViewer;
        private string mOpName;

        public UtilStats()
        {
            InitializeComponent();
        }

        private void btnApply_Click(object sender, EventArgs e)
        {
            int inputImage = 0, bands = 0;
            try
            {
                // disable Apply button
                this.btnApply.Enabled = false;
                this.Cursor = Cursors.WaitCursor;

                if (SelectedViewer == null)
                    throw new Exception("No input image!");
                else
                {
                    // get the image that will be operated on
                    inputImage = SelectedViewer.CVIPimage;
                }

                switch (mOpName)
                {
                case "Image Data Range":
                    double[] DataRangeResult;

                    DataRangeResult = CvipOp.Get_max_min_value(inputImage);
                    bands = CvipOp.GetNoOfBands_Image(inputImage);

                    lblMinReal0.Text = DataRangeResult[0].ToString("0.000");
                    lblMaxReal0.Text = DataRangeResult[1].ToString("0.000");

                    if (CvipOp.GetDataFormat_Image(inputImage) == dataFormat.COMPLEX)
                    {
                        lblMinImag0.Text = DataRangeResult[2].ToString("0.000");
                        lblMaxImag0.Text = DataRangeResult[3].ToString("0.000");
                    }

                    if (bands > 1)
                    {
                        lblMinReal1.Text = DataRangeResult[4].ToString("0.000");
                        lblMaxReal1.Text = DataRangeResult[5].ToString("0.000");
                        lblMinReal2.Text = DataRangeResult[8].ToString("0.000");
                        lblMaxReal2.Text = DataRangeResult[9].ToString("0.000");

                        if (CvipOp.GetDataFormat_Image(inputImage) == dataFormat.COMPLEX)
                        {
                            lblMinImag1.Text = DataRangeResult[6].ToString("0.000");
                            lblMaxImag1.Text = DataRangeResult[7].ToString("0.000");
                            lblMinImag2.Text = DataRangeResult[10].ToString("0.000");
                            lblMaxImag2.Text = DataRangeResult[11].ToString("0.000");
                        }
                    }
                    break;

                case "Image Statistics":
                    int tempImage = 0, labledImage = 0;
                    int imageWidth = 0, imageHeight = 0;
                    double[] features;

                    bands = CvipOp.GetNoOfBands_Image(inputImage);
                    imageWidth = CvipOp.GetNoOfCols_Image(inputImage);
                    imageHeight = CvipOp.GetNoOfRows_Image(inputImage);

                    if (chkUtilStatsConvert.Checked)
                    {
                        tempImage = CvipOp.Remap_Image(inputImage, dataType.CVIP_BYTE, 0, 255);
                        CvipOp.Delete_Image(ref inputImage);
                        inputImage = tempImage;
                    }

                    labledImage = CvipOp.Create_Rectangle(imageWidth, imageHeight, 0, 0, imageWidth, imageHeight);

                    features = CvipOp.Hist_Feature(inputImage, labledImage, 0, 0);
                    CvipOp.Delete_Image(ref labledImage);

                    lblUtilStatsMean0.Text = features[0].ToString("0.000");
                    lblUtilStatsSTD0.Text = features[1].ToString("0.000");
                    lblUtilStatsSkew0.Text = features[2].ToString("0.000");
                    lblUtilStatsEnergy0.Text = features[3].ToString("0.000");
                    lblUtilStatsEntropy0.Text = features[4].ToString("0.000");
                    if (bands == 3)
                    {
                        lblUtilStatsMean1.Text = features[5].ToString("0.000");
                        lblUtilStatsSTD1.Text = features[6].ToString("0.000");
                        lblUtilStatsSkew1.Text = features[7].ToString("0.000");
                        lblUtilStatsEnergy1.Text = features[8].ToString("0.000");
                        lblUtilStatsEntropy1.Text = features[9].ToString("0.000");

                        lblUtilStatsMean2.Text = features[10].ToString("0.000");
                        lblUtilStatsSTD2.Text = features[11].ToString("0.000");
                        lblUtilStatsSkew2.Text = features[12].ToString("0.000");
                        lblUtilStatsEnergy2.Text = features[13].ToString("0.000");
                        lblUtilStatsEntropy2.Text = features[14].ToString("0.000");
                    }
                    break;
                }

                // delete input image
                CvipOp.Delete_Image(ref inputImage);

                // enable Apply button
                this.btnApply.Enabled = true;
                this.Cursor = Cursors.Default;
            }
            catch (Exception e1)
            {
                // enable Apply button
                this.btnApply.Enabled = true;
                this.Cursor = Cursors.Default;
                MessageBox.Show(e1.Message);
            }
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
            Clear();
            if (mOpName == "Image Statistics")
                chkUtilStatsConvert.Checked = true;
        }

        private void Clear()
        {
            lblMaxImag0.Text = "";
            lblMaxImag1.Text = "";
            lblMaxImag2.Text = "";
            lblMinImag0.Text = "";
            lblMinImag1.Text = "";
            lblMinImag2.Text = "";
            lblMaxReal0.Text = "";
            lblMaxReal1.Text = "";
            lblMaxReal2.Text = "";
            lblMinReal0.Text = "";
            lblMinReal1.Text = "";
            lblMinReal2.Text = "";

            lblUtilStatsEnergy0.Text = "";
            lblUtilStatsEnergy1.Text = "";
            lblUtilStatsEnergy2.Text = "";
            lblUtilStatsEntropy0.Text = "";
            lblUtilStatsEntropy1.Text = "";
            lblUtilStatsEntropy2.Text = "";
            lblUtilStatsSkew0.Text = "";
            lblUtilStatsSkew1.Text = "";
            lblUtilStatsSkew2.Text = "";
            lblUtilStatsSTD0.Text = "";
            lblUtilStatsSTD1.Text = "";
            lblUtilStatsSTD2.Text = "";
            lblUtilStatsMean0.Text = "";
            lblUtilStatsMean1.Text = "";
            lblUtilStatsMean2.Text = "";
        }

        public void Init(string op)
        {
            this.mOpName = op;
            switch (mOpName)
            {
            case "Image Data Range":
                pnlUtilStatsDataRange.Visible = true;
                this.pnlUtilImageStats.Visible = false;
                break;

            case "Image Statistics":
                pnlUtilStatsDataRange.Visible = false;
                this.pnlUtilImageStats.Visible = true;
                break;
            }
            UpdateImageList();
        }

        protected override void OnLoad(EventArgs e)
        {
            base.OnLoad(e);

            this.pnlUtilImageStats.Location = new Point(7, 3);
            this.pnlUtilStatsDataRange.Location = new Point(7, 3);
            //this.Size = new Size(436, 140);

            chkUtilStatsConvert.Checked = true;
            UpdateImageList();
        }

        public void UpdateImageList()
        {
            if (MainForm.Viewers != null)
            {
                try
                {
                    lblUtilStatsCurrentImage.Text = "";
                    SelectedViewer = MainForm.Viewers.SelectedViewer;
                    if (SelectedViewer != null)
                    {
                        lblUtilStatsDataRangeCurrentImage.Text = SelectedViewer.Text;
                        lblUtilStatsCurrentImage.Text = SelectedViewer.Text;
                    }

                    Clear();
                }
                catch (Exception e1)
                {
                    MessageBox.Show(e1.Message);
                }
            }
        }
    }
}
