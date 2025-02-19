/*''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' ======================================================================
' Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
' ======================================================================
'
'             File Name: UtilConvert.cs
'           Description: Contains the controls and code
'                        for Utilities->UtilConvert page
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
    public partial class UtilConvert : UserControl
    {
        ViewerForm SelectedViewer;
        private string mOpName;

        public UtilConvert()
        {
            InitializeComponent();
        }

        private void AddImageToQueue(string OpName, int outputImage)
        {
            string newImageName = "";
            try
            {
                // create a name for the new image
                newImageName = SelectedViewer.Text + "_" + CvipFunctionNames.getFncName(OpName) + Convert.ToString(CvipConstant.imageNameCount);
                CvipConstant.imageNameCount++;

                //Save image name and path into image queue and
                //create an instance of imageViewer From for holding image and doing other operations
                MainForm.Viewers.Add(outputImage, newImageName);
            }
            catch (Exception e)
            {
                MessageBox.Show(e.Message);
            }
        }

        private void btnApply_Click(object sender, EventArgs e)
        {
            int inputImage1 = 0, tmp = 0, outputImage = 0;
            string appendix = "";
            try
            {
                // disable Apply button
                this.btnApply.Enabled = false;
                this.Cursor = Cursors.WaitCursor;

                if (SelectedViewer == null)
                {
                    throw new Exception("No input image!");
                }
                else
                {
                    // get the image that will be operated on
                    inputImage1 = SelectedViewer.CVIPimage;
                }

                switch (mOpName)
                {
                case "Binary Threshold":
                    outputImage = CvipOp.Threshold_Segment(inputImage1, Convert.ToInt32(cmbUtilBinaryThreshold.Text), this.chkUtilBinaryThreshold.Checked);
                    appendix = "Thresh";
                    break;

                case "Data Type":
                    dataType data_type_in, data_type_out = 0;
                    string[] appendixNames = new string[] { "BYTE", "SHORT", "INTEGER", "FLOAT" };

                    if (this.rdbUtilConvertBYTE.Checked)
                        data_type_out = dataType.CVIP_BYTE;
                    else if (this.rdbUtilConvertSHORT.Checked)
                        data_type_out = dataType.CVIP_SHORT;
                    else if (this.rdbUtilConvertINTEGER.Checked)
                        data_type_out = dataType.CVIP_INTEGER;
                    else if (this.rdbUtilConvertFLOAT.Checked)
                        data_type_out = dataType.CVIP_FLOAT;

                    data_type_in = CvipOp.GetDataType_Image(inputImage1);
                    if (data_type_in < data_type_out)
                    {
                        outputImage = CvipOp.Duplicate_Image(inputImage1);
                        CvipOp.Cast_Image(outputImage, data_type_out);
                    }
                    else if (data_type_in > data_type_out)
                    {
                        switch (data_type_out)
                        {
                        case dataType.CVIP_BYTE:
                            outputImage = CvipOp.Remap_Image(inputImage1, data_type_out, byte.MinValue, byte.MaxValue);
                            break;
                        case dataType.CVIP_SHORT:
                            outputImage = CvipOp.Remap_Image(inputImage1, data_type_out, short.MinValue, short.MaxValue);
                            break;
                        case dataType.CVIP_INTEGER:
                            outputImage = CvipOp.Remap_Image(inputImage1, data_type_out, int.MinValue, int.MaxValue);
                            break;
                        }
                    }
                    else
                        MessageBox.Show("The data type was unchanged.");

                    appendix = appendixNames[(int)data_type_out];
                    break;

                case "Halftone":
                    int half_tone = 1;

                    if (rdbUtilConvertHTFS.Checked)
                        half_tone = 1;
                    else if (rdbUtilConvertHTThreshold.Checked)
                        half_tone = 2;
                    else if (rdbUtilConvertHTDither.Checked)
                        half_tone = 3;
                    else if (rdbUtilConvertHTCluster3.Checked)
                        half_tone = 4;
                    else if (rdbUtilConvertHTCluster4.Checked)
                        half_tone = 5;
                    else if (rdbUtilConvertHTCluster8.Checked)
                        half_tone = 6;

                    string thresh;
                    if (half_tone == 1)
                        thresh = FS_Box.Text;
                    else
                        thresh = cmbUtilConvertHTThreshold.Text;

                    if (CvipOp.GetNoOfBands_Image(inputImage1) == 1)
                    {
                        tmp = CvipOp.Remap_Image(inputImage1, dataType.CVIP_BYTE, 0, 255);
                        outputImage = CvipOp.CVIPhalftone(tmp, half_tone, 255, Convert.ToSingle(thresh), 1, 1);
                        outputImage = CvipOp.REMAPP(outputImage, dataType.CVIP_BYTE, 0, 255);
                    }
                    else
                    {
                        int band0 = 0, band1 = 0, band2 = 0;
                        int dupli = CvipOp.Duplicate_Image(inputImage1);
                        int[] imageArray = new int[3];
                        tmp = CvipOp.Extract_Band(dupli, 1);
                        band0 = CvipOp.Remap_Image(tmp, dataType.CVIP_BYTE, 0, 255);
                        dupli = CvipOp.Duplicate_Image(inputImage1);
                        tmp = CvipOp.Extract_Band(dupli, 2);
                        band1 = CvipOp.Remap_Image(tmp, dataType.CVIP_BYTE, 0, 255);
                        dupli = CvipOp.Duplicate_Image(inputImage1);
                        tmp = CvipOp.Extract_Band(dupli, 3);
                        band2 = CvipOp.Remap_Image(tmp, dataType.CVIP_BYTE, 0, 255);

                        tmp = CvipOp.CVIPhalftone(band0, half_tone, 255, Convert.ToSingle(thresh), 1, 1);
                        imageArray[0] = CvipOp.REMAPP(tmp, dataType.CVIP_BYTE, 0, 255);
                        tmp = CvipOp.CVIPhalftone(band1, half_tone, 255, Convert.ToSingle(thresh), 1, 1);
                        imageArray[1] = CvipOp.REMAPP(tmp, dataType.CVIP_BYTE, 0, 255);
                        tmp = CvipOp.CVIPhalftone(band2, half_tone, 255, Convert.ToSingle(thresh), 1, 1);
                        imageArray[2] = CvipOp.REMAPP(tmp, dataType.CVIP_BYTE, 0, 255);

                        outputImage = CvipOp.Assemble_Bands(imageArray);
                        for (int i = 0; i < 3; i++)
                            CvipOp.Delete_Image(ref imageArray[i]);
                    }
                    appendix = "Halftone";
                    break;

                case "Gray Level Quantization":
                    if (rdbUtilConvertStandard.Checked)
                        outputImage = CvipOp.Gray_Quant_Segment(inputImage1, Convert.ToInt32(cmbUtilConvertNumOfBits.Text));
                    else if (rdbUtilConvertIGS.Checked)
                        outputImage = CvipOp.Igs_Segment(inputImage1, Convert.ToInt32(cmbUtilConvertNumOfBits.Text));

                    appendix = "GLQ";
                    break;

                case "Gray Code-Natural Binary":
                    //direction -- 1 or 0. 1 means from binary to Gray
                    if (rdbUtilConvertGCtoNBC.Checked)
                        outputImage = CvipOp.Gray_Binary(inputImage1, 0);
                    else if (rdbUtilConvertNBCtoGC.Checked)
                        outputImage = CvipOp.Gray_Binary(inputImage1, 1);

                    appendix = "GrayCode";
                    break;

                case "Gray to Color":
                    if (rdbUtilConvertFreqMapping.Checked)
                        outputImage = CvipOp.Pseudocol_Freq(inputImage1, Convert.ToInt32(cmbUtilConvertLowCutoffFreq.Text), Convert.ToInt32(cmbUtilConvertHighCutoffFreq.Text), Convert.ToInt32(cmbUtilConvertLowPassColor.SelectedIndex), Convert.ToInt32(cmbUtilConvertBandPassColor.SelectedIndex), Convert.ToInt32(cmbUtilConvertHighPassColor.SelectedIndex));
                    else if (rdbUtilConvertGLMapping.Checked)
                        outputImage = CvipOp.Graylevel_Remap(inputImage1, Convert.ToInt32(cmbUtilConvertRed.SelectedIndex), Convert.ToInt32(cmbUtilConvertGreen.SelectedIndex), Convert.ToInt32(cmbUtilConvertBlue.SelectedIndex));

                    appendix = "Pseudo";
                    break;

                case "Color to Gray":
                    if (rdbUtilConvertLum.Checked)
                    {
                        outputImage = CvipOp.Luminance_Image(inputImage1);
                        appendix = "Lum";
                    }
                    else if (rdbUtilConvertAvg.Checked)
                    {
                        outputImage = CvipOp.Lum_Average(inputImage1);
                        appendix = "LumAvg";
                    }
                    break;

                case "Color Space":
                    double[] NormVector = { 0.0, 0.0, 0.0 };
                    double[] RefWhite = { 0.0, 0.0, 0.0 };
                    int forward_backward_choice = 0;
                    int tempImage = 0;

                    if (chkUtilConvertNormalize.Checked)
                        for (int i = 0; i < 3; i++) NormVector[i] = 255.0;

                    if (cmbUtilConvertColorSpace.SelectedIndex == 6) //PCT
                    {
                        if (chkUtilConvertForward.Checked)
                        {
                            forward_backward_choice = 1;
                            appendix = "";
                        }
                        else
                        {
                            forward_backward_choice = 2;
                            appendix = "Inv";
                        }
                    }
                    else  //Not PCT
                    {
                        if (chkUtilConvertForward.Checked)
                        {
                            forward_backward_choice = 1;
                            appendix = "";
                        }
                        else
                        {
                            forward_backward_choice = -1;
                            appendix = "Inv";
                        }
                    }

                    switch (cmbUtilConvertColorSpace.SelectedIndex)
                    {
                    case 0: //XYZ
                        outputImage = CvipOp.ColorXform(inputImage1, colorFormat.XYZ, ref NormVector[0], ref RefWhite[0], forward_backward_choice);
                        appendix += "XYZ";
                        break;
                    case 1: //LAB
                        for (int i = 0; i < 3; i++) RefWhite[i] = 1.0;
                        outputImage = CvipOp.ColorXform(inputImage1, colorFormat.LAB, ref NormVector[0], ref RefWhite[0], forward_backward_choice);
                        appendix += "LAB";
                        break;
                    case 2: //LUV
                        for (int i = 0; i < 3; i++) RefWhite[i] = 1.0;
                        outputImage = CvipOp.ColorXform(inputImage1, colorFormat.LUV, ref NormVector[0], ref RefWhite[0], forward_backward_choice);
                        appendix += "LUV";
                        break;
                    case 3: //CCT
                        outputImage = CvipOp.ColorXform(inputImage1, colorFormat.CCT, ref NormVector[0], ref RefWhite[0], forward_backward_choice);
                        appendix += "CCT";
                        break;
                    case 4: //HSL
                        for (int i = 0; i < 3; i++) RefWhite[i] = 0.0;
                        tempImage = CvipOp.Remap_Image(inputImage1, dataType.CVIP_BYTE, 0, 255);
                        outputImage = CvipOp.ColorXform(tempImage, colorFormat.HSL, ref NormVector[0], ref RefWhite[0], forward_backward_choice);
                        appendix += "HSL";
                        break;
                    case 5: //HSV
                        tempImage = CvipOp.Remap_Image(inputImage1, dataType.CVIP_BYTE, 0, 255);
                        outputImage = CvipOp.ColorXform(tempImage, colorFormat.HSV, ref NormVector[0], ref RefWhite[0], forward_backward_choice);
                        appendix += "HSV";
                        break;
                    case 6: //PCT
                        double[] MaskP = { 0 };
                        outputImage = CvipOp.Pct_Color(inputImage1, false, ref MaskP[0], forward_backward_choice);
                        appendix += "PCT";
                        break;
                    case 7: //SCT
                        outputImage = CvipOp.ColorXform(inputImage1, colorFormat.SCT, ref NormVector[0], ref RefWhite[0], forward_backward_choice);
                        appendix += "SCT";
                        break;
                    }

                    if (cmbUtilConvertColorSpace.SelectedIndex != 6) // Not PCT
                        if (chkUtilConvertRemap.Checked)
                            outputImage = CvipOp.Remap_Image(outputImage, dataType.CVIP_BYTE, 0, 255);
                    break;

                case "Label Image":
                    if (CvipOp.GetNoOfBands_Image(inputImage1) == 1)
                        outputImage = CvipOp.Label(inputImage1);
                    else
                    {
                        tmp = CvipOp.Luminance_Image(inputImage1);
                        outputImage = CvipOp.Label(tmp);
                        CvipOp.Delete_Image(ref tmp);
                    }
                    appendix = "Label";
                    break;
                }

                if (outputImage != 0) AddImageToQueue(appendix, outputImage);

                // delete input image
                CvipOp.Delete_Image(ref inputImage1);

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
            switch (mOpName)
            {
            case "Binary Threshold":
                cmbUtilBinaryThreshold.SelectedIndex = 5;
                chkUtilBinaryThreshold.Checked = true;
                break;

            case "Data Type":
                this.rdbUtilConvertBYTE.Checked = true;
                break;

            case "Halftone":
                this.rdbUtilConvertHTFS.Checked = true;
                break;

            case "Gray Level Quantization":
                this.rdbUtilConvertStandard.Checked = true;
                cmbUtilConvertNumOfBits.SelectedIndex = 3;
                break;

            case "Gray Code-Natural Binary":
                this.rdbUtilConvertNBCtoGC.Checked = true;
                break;

            case "Gray to Color":
                this.rdbUtilConvertFreqMapping.Checked = true;
                this.cmbUtilConvertLowCutoffFreq.SelectedIndex = 1;
                this.cmbUtilConvertHighCutoffFreq.SelectedIndex = 0;
                this.cmbUtilConvertLowPassColor.SelectedIndex = 0;
                this.cmbUtilConvertBandPassColor.SelectedIndex = 1;
                this.cmbUtilConvertHighPassColor.SelectedIndex = 2;

                this.cmbUtilConvertRed.SelectedIndex = 0;
                this.cmbUtilConvertGreen.SelectedIndex = 1;
                this.cmbUtilConvertBlue.SelectedIndex = 2;
                break;

            case "Color to Gray":
                this.rdbUtilConvertLum.Checked = true;
                break;

            case "Color Space":
                cmbUtilConvertColorSpace.SelectedIndex = 6;

                this.chkUtilConvertForward.Checked = true;
                this.chkUtilConvertNormalize.Checked = true;
                this.chkUtilConvertRemap.Checked = false;
                this.chkUtilConvertNormalize.Enabled = false;
                this.chkUtilConvertRemap.Enabled = false;
                break;
            }
        }

        private void cmbUtilConvertColorSpace_SelectedIndexChanged(object sender, EventArgs e)
        {
            try
            {
                switch (cmbUtilConvertColorSpace.SelectedIndex)
                {
                case 0:
                case 1:
                    
                case 3:
                case 4:
                case 5:
                case 7:
                    chkUtilConvertNormalize.Checked = true;
                    chkUtilConvertNormalize.Enabled = true;
                    chkUtilConvertRemap.Enabled = true;
                    break;

                case 2:
                    chkUtilConvertNormalize.Checked = false;
                   
                    chkUtilConvertNormalize.Enabled = true;
                    chkUtilConvertRemap.Enabled = true;
                    break;
                case 6:
                    chkUtilConvertNormalize.Enabled = false;
                    chkUtilConvertRemap.Enabled = false;
                    break;
                }
            }
            catch (Exception e1)
            {
                MessageBox.Show(e1.Message);
            }
        }

        private void cmbUtilConvertRed_DrawItem(object sender, DrawItemEventArgs e)
        {
            if (e.Index != -1)
                e.Graphics.DrawImage(UtilGrayToColorImageList.Images[e.Index], e.Bounds.Left, e.Bounds.Top);
        }

        private void cmbUtilConvertGreen_DrawItem(object sender, DrawItemEventArgs e)
        {
            if (e.Index != -1)
                e.Graphics.DrawImage(UtilGrayToColorImageList.Images[e.Index], e.Bounds.Left, e.Bounds.Top);
        }

        private void cmbUtilConvertBlue_DrawItem(object sender, DrawItemEventArgs e)
        {
            if (e.Index != -1)
                e.Graphics.DrawImage(UtilGrayToColorImageList.Images[e.Index], e.Bounds.Left, e.Bounds.Top);
        }

        public void Init(string op)
        {
            this.mOpName = op;
            this.pnlUtilConvertBinaryThreshold.Visible = false;
            this.pnlUtilConvertDataType.Visible = false;
            this.pnlUtilConvertHalftone.Visible = false;
            this.pnlUtilConvertLabelImage.Visible = false;
            this.pnlUtilConvertGrayLevelQuant.Visible = false;
            this.pnlUtilConvertGCNBC.Visible = false;
            this.pnlUtilConvertGrayToColor.Visible = false;
            this.pnlUtilConvertColorToGray.Visible = false;
            this.pnlUtilConvertColorSpace.Visible = false;

            switch (mOpName)
            {
            case "Binary Threshold":
                this.pnlUtilConvertBinaryThreshold.Visible = true;
                btnReset.Enabled = true;
                break;

            case "Data Type":
                this.pnlUtilConvertDataType.Visible = true;
                btnReset.Enabled = true;
                break;

            case "Halftone":
                this.pnlUtilConvertHalftone.Visible = true;
                btnReset.Enabled = true;
                break;

            case "Gray Level Quantization":
                this.pnlUtilConvertGrayLevelQuant.Visible = true;
                btnReset.Enabled = true;
                break;

            case "Gray Code-Natural Binary":
                this.pnlUtilConvertGCNBC.Visible = true;
                btnReset.Enabled = true;
                break;

            case "Gray to Color":
                this.pnlUtilConvertGrayToColor.Visible = true;
                btnReset.Enabled = true;
                break;

            case "Color to Gray":
                this.pnlUtilConvertColorToGray.Visible = true;
                btnReset.Enabled = true;
                break;

            case "Color Space":
                this.pnlUtilConvertColorSpace.Visible = true;
                btnReset.Enabled = true;
                break;

            case "Label Image":
                lblUtilLableImage.Text = "This function creates a labeled image from a current image:\n" +
                                         "1) For color images, it first converts the image to a grayscale image by performing \n     luminance transform. And then it labels the grayscale image.\n" +
                                         "2) Typically used with the images that have been segmented.";
                pnlUtilConvertLabelImage.Visible = true;
                btnReset.Enabled = false;
                break;
            }

            UpdateImageList();
        }

        protected override void OnEnter(EventArgs e)
        {
            base.OnEnter(e);
            try
            {
                SelectedViewer = MainForm.Viewers.SelectedViewer;
                if (SelectedViewer != null)
                {
                    //Data Type
                    switch (SelectedViewer.DataType)
                    {
                    case dataType.CVIP_BYTE:
                        lblUtilConvertDataType.Text = "BYTE";
                        break;
                    case dataType.CVIP_SHORT:
                        lblUtilConvertDataType.Text = "SHORT";
                        break;
                    case dataType.CVIP_INTEGER:
                        lblUtilConvertDataType.Text = "INTEGER";
                        break;
                    case dataType.CVIP_FLOAT:
                        lblUtilConvertDataType.Text = "FLOAT";
                        break;
                    }
                }

                //Halftone
                //cmbUtilConvertHTThreshold.SelectedIndex = 2;

                //Gray Level Quantization
                //cmbUtilConvertNumOfBits.SelectedIndex = 3;
            }
            catch (Exception e1)
            {
                MessageBox.Show(e1.Message);
            }
        }

        protected override void OnLoad(EventArgs e)
        {
            base.OnLoad(e);

            this.pnlUtilConvertBinaryThreshold.Location = new Point(4, 20);
            this.pnlUtilConvertDataType.Location = new Point(4, 20);
            this.pnlUtilConvertHalftone.Location = new Point(4, 20);
            this.pnlUtilConvertLabelImage.Location = new Point(4, 20);
            this.pnlUtilConvertGrayLevelQuant.Location = new Point(4, 20);
            this.pnlUtilConvertGCNBC.Location = new Point(4, 20);
            this.pnlUtilConvertGrayToColor.Location = new Point(4, 20);
            this.pnlUtilConvertColorToGray.Location = new Point(4, 20);
            this.pnlUtilConvertColorSpace.Location = new Point(4, 20);
          //  this.Size = new Size(436, 140);

            this.btnReset.PerformClick();

            this.cmbUtilConvertRed.SelectedIndex = 0;
            this.cmbUtilConvertGreen.SelectedIndex = 1;
            this.cmbUtilConvertBlue.SelectedIndex = 2;

            //Color Space
            cmbUtilConvertColorSpace.SelectedIndex = 6;
            chkUtilConvertNormalize.Enabled = false;
            chkUtilConvertRemap.Enabled = false;

            UpdateImageList();
        }

        private void rdbUtilConvertHTThreshold_CheckedChanged(object sender, EventArgs e)
        {
            if (rdbUtilConvertHTThreshold.Checked)
                cmbUtilConvertHTThreshold.Visible = true;
            else
                cmbUtilConvertHTThreshold.Visible = false;
        }

        private void rdbUtilConvertFreqMapping_CheckedChanged(object sender, EventArgs e)
        {
            this.pnlUtilConvertGLMapping.Visible = false;
            this.pnlUtilConvertFreqMapping.Visible = true;
        }

        private void rdbUtilConvertGLMapping_CheckedChanged(object sender, EventArgs e)
        {
            this.pnlUtilConvertGLMapping.Visible = true;
            this.pnlUtilConvertFreqMapping.Visible = false;
        }

        public void UpdateImageList()
        {
            if (MainForm.Viewers != null)
            {
                try
                {
                    lblUtilConvertCurrentImage.Text = "";
                    SelectedViewer = MainForm.Viewers.SelectedViewer;
                    if (SelectedViewer != null)
                        lblUtilConvertCurrentImage.Text = SelectedViewer.Text;
                }
                catch (Exception e1)
                {
                    MessageBox.Show(e1.Message);
                }
            }
        }

        private void rdbUtilConvertHTFS_CheckedChanged(object sender, EventArgs e)
        {
            if (rdbUtilConvertHTFS.Checked)
                FS_Box.Visible = true;
            else
                FS_Box.Visible = false;
        }
        /*
private void cmbUtilConvertHTThreshold_SelectedIndexChanged(object sender, EventArgs e)
{

}*/
    }
}
