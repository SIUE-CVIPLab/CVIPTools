/*''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' ======================================================================
' Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
' ======================================================================
'
'             File Name: UtilCompare.cs
'           Description: Contains the controls and code
'                        for Utilities->UtilCompare page
'         Related Files: CvipOp.cs
'                        CvipConstant.cs
'   Initial Coding Date: April 2007
'              Modified: October 2010
'       Delevoping tool: Visual Studio 2008-C#
'             Credit(s): Wenjun(Evan) Bian
'                        Patrick Solt
'                        Jhansi Lakshmi Akkineni
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
    public partial class UtilCompare : UserControl
    {
        private string currentSelection;

        public UtilCompare()
        {
            InitializeComponent();
        }

        private void btnApply_Click(object sender, EventArgs e)
        {
            ViewerForm viewer = (ViewerForm)this.txtCurrentImage.Tag;
            ViewerForm viewer2 = (ViewerForm)this.cboSecondImage.SelectedItem;
            if (viewer == null)
            {
                MessageBox.Show("Please give an input image!", "No input image!",
                    MessageBoxButtons.OK, MessageBoxIcon.Warning);
                return;
            }
            if (viewer2 == null)
            {
                MessageBox.Show("Please give a second image!", "No second image!",
                    MessageBoxButtons.OK, MessageBoxIcon.Warning);
                return;
            }

            // disable Apply button
            this.btnApply.Enabled = false;
            this.Cursor = Cursors.WaitCursor;

            try
            {
                // get the image(s) that will be operated on
                int inputImage1 = viewer.CVIPimage, outputImage = 0;
                int inputImage2 = viewer2.CVIPimage;
                string appendix = "";

                switch (this.currentSelection)
                {
                    case "Compare Two Images":
                    case "Objective Error Metrics":
                        if (this.rbCompareRMS_SUB.Checked)
                        {
                            if (this.rbCompareRMS_SUB.Text == "RMS Error")
                            {
                                float[] result = CvipOp.Rms_Error(inputImage1, inputImage2);
                                //double[] result = CvipOp.Dice_Coef(inputImage1, inputImage2);
                                if (result != null)
                                {
                                    string rmsMessage = "";
                                    for (int i = 0; i < viewer.Bands; i++)
                                        rmsMessage += "Band " + (i + 1).ToString() + ": " + result[i].ToString("0.00") + "       ";
                                    this.lblResult.Visible = true;
                                    this.txtResult.Visible = true;
                                    this.txtResult.Text = rmsMessage;
                                    //  MessageBox.Show(rmsMessage, "Root-Mean-Square Error", MessageBoxButtons.OK);
                                }
                                appendix = "RMS";
                            }
                            else
                            {
                                outputImage = CvipOp.Subtract_Image(inputImage1, inputImage2);
                                appendix = "Sub";
                            }
                        }
                        else if (this.rbCompareSNR_XOR.Checked)
                        {
                            if (this.rbCompareSNR_XOR.Text == "Peak SNR")
                            {
                                int bands = viewer.Bands;
                                int bands2 = viewer2.Bands;
                                if (bands != bands2)
                                {
                                    string msg = "The bands of two images are not equal. In order to compare the images, do you want to equalize the bands?";
                                    string caption = "SNR";
                                    MessageBoxButtons btns = MessageBoxButtons.YesNo;
                                    if (MessageBox.Show(msg, caption, btns) != DialogResult.Yes)
                                    {
                                        break;
                                    }
                                    if (bands == 1)
                                    {
                                        int[] tmp = new int[3];
                                        for (int i = 0; i < 3; i++)
                                            tmp[i] = inputImage1;
                                        int img = CvipOp.Assemble_Bands(tmp);
                                        CvipOp.Delete_Image(ref inputImage1);
                                        inputImage1 = img;
                                    }
                                    else
                                    {
                                        int[] tmp = new int[3];
                                        for (int i = 0; i < 3; i++)
                                            tmp[i] = inputImage2;
                                        int img = CvipOp.Assemble_Bands(tmp);
                                        CvipOp.Delete_Image(ref inputImage2);
                                        inputImage2 = img;
                                    }
                                }
                                float[] result = CvipOp.Snr(inputImage1, inputImage2);
                                if (result != null)
                                {
                                    string snrMessage = "";
                                    bands = CvipOp.GetNoOfBands_Image(inputImage1);
                                    for (int i = 0; i < bands; i++)
                                    {
                                        if (result[i] < 0)
                                            snrMessage += "Band " + (i + 1).ToString() + ": Infinity (no error)    ";
                                        else
                                            snrMessage += "Band " + (i + 1).ToString() + ": " + result[i].ToString("0.000") + "      ";
                                    }
                                    this.lblResult.Visible = true;
                                    this.txtResult.Visible = true;
                                    this.txtResult.Text = snrMessage;
                                    //    MessageBox.Show(snrMessage, "Signal-To-Noise Ratio", MessageBoxButtons.OK);
                                }
                                appendix = "SNR";
                            }
                            else
                            {
                                outputImage = CvipOp.Xor_Image(inputImage1, inputImage2);
                                appendix = "XOR";
                            }
                        }
                        else if (this.rbCompareXORe.Checked || this.rbCompareDice.Checked || this.rbCompareJaccard.Checked || this.rbCompareOverlap.Checked)
                        {
                            int bands = viewer.Bands;
                            int bands2 = viewer2.Bands;
                            if (bands != bands2)
                            {
                                string msg = "The bands of two images are not equal. In order to compare the images, do you want to equalize the bands?";
                                string caption = "Error Metric";
                                MessageBoxButtons btns = MessageBoxButtons.YesNo;
                                if (MessageBox.Show(msg, caption, btns) != DialogResult.Yes)
                                {
                                    break;
                                }
                            }
                            double[] result = null;
                            if (this.rbCompareXORe.Checked)
                            {
                                result = CvipOp.XOR_Error(inputImage1, inputImage2);
                                appendix = "XORe";
                            }
                            else if (this.rbCompareDice.Checked)
                            {
                                result = CvipOp.Dice_Coef(inputImage1, inputImage2);
                                appendix = "Dice";
                            }
                            else if (this.rbCompareJaccard.Checked)
                            {
                                result = CvipOp.Jaccard_Index(inputImage1, inputImage2);
                                appendix = "Jaccard";
                            }
                            else if (this.rbCompareOverlap.Checked)
                            {
                                result = CvipOp.Overlap_Coef(inputImage1, inputImage2);
                                appendix = "Overlap";
                            }
                            if (result != null)
                            {
                                string areaMessage = "";
                                bands = CvipOp.GetNoOfBands_Image(inputImage1);
                                for (int i = 0; i < bands; i++)
                                {
                                    areaMessage += "Band " + (i + 1).ToString() + ": " + result[i].ToString("0.000") + "      ";
                                }
                                this.lblResult.Visible = true;
                                this.txtResult.Visible = true;
                                this.txtResult.Text = areaMessage;
                            }
                        }
                        this.toolTipImage2.RemoveAll();
                        break;

                    case "Pratt Figure of Merit":
                        double ScaleFactor = 0.0;
                        string[] splitresult = this.cboScaleFactor.Text.Split(new char[] { '/' }, 2);
                        if (splitresult.Length == 2)
                            ScaleFactor = Convert.ToDouble(splitresult[0]) / Convert.ToDouble(splitresult[1]);
                        else
                            ScaleFactor = Convert.ToDouble(this.cboScaleFactor.Text);
                        this.pnlPrattResultRGB.Visible = false;
                        this.txtPrattResultGS.Text = "Working...";
                        this.txtPrattResultGS.Visible = true;
                        Update();
                        double[] PNRresult = CvipOp.Pratt_Merit(inputImage1, inputImage2, ScaleFactor);
                        if (PNRresult.Length == 1)
                            this.txtPrattResultGS.Text = PNRresult[0].ToString("0.000000");
                        else
                        {
                            this.txtPrattResultGS.Visible = false;
                            this.txtPrattResultR.Text = PNRresult[0].ToString("0.000000");
                            this.txtPrattResultG.Text = PNRresult[1].ToString("0.000000");
                            this.txtPrattResultB.Text = PNRresult[2].ToString("0.000000");
                            this.pnlPrattResultRGB.Visible = true;
                        }
                        break;
                }
                if (outputImage != 0)
                {
                    string newImageName = viewer.Text;
                    newImageName += "_" + CvipFunctionNames.getFncName(appendix);
                    newImageName += CvipConstant.imageNameCount++.ToString();
                    MainForm.Viewers.Add(outputImage, newImageName);
                }

                // delete input images
                CvipOp.Delete_Image(ref inputImage1);
                CvipOp.Delete_Image(ref inputImage2);
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }

            // enable Apply button
            this.btnApply.Enabled = true;
            this.Cursor = Cursors.Default;
            this.toolTipImage2.RemoveAll();
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
            switch (this.currentSelection)
            {
                case "Compare Two Images":
                    this.lblCurrentImage.Text = "Ideal Image (Ground Truth)";
                    this.lblSecondImage.Text = "Test Image";
                    this.lblResult.Visible = false;
                    this.txtResult.Text = "";
                    this.txtResult.Visible = false;
                    this.rbCompareRMS_SUB.Checked = true;
                    this.pnlCompareImages.Visible = true;
                    this.compareImagesChange();
                    this.pnlComparePratt.Visible = false;
                    this.toolTipImage2.RemoveAll();
                    break;

                case "Objective Error Metrics":
                    this.lblCurrentImage.Text = "Ideal Image (Ground Truth)";
                    this.lblSecondImage.Text = "Test Image";
                    this.lblResult.Visible = false;
                    this.txtResult.Text = "";
                    this.txtResult.Visible = false;
                    this.rbCompareRMS_SUB.Checked = true;
                    this.pnlCompareImages.Visible = true;
                    this.compareErrorChange();
                    this.pnlComparePratt.Visible = false;
                    this.toolTipImage2.RemoveAll();
                    break;

                case "Pratt Figure of Merit":
                    this.lblCurrentImage.Text = "Ideal Edge Image";
                    this.lblSecondImage.Text = "Edge Detection Image";
                    this.pnlCompareImages.Visible = false;
                    this.pnlComparePratt.Visible = true;
                    this.cboScaleFactor.SelectedIndex = 0;
                    this.toolTipImage2.RemoveAll();
                    break;
            }
        }

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

        public void Init(string op)
        {
            this.currentSelection = op;
            switch (currentSelection)
            {
                case "Compare Two Images":
                    this.lblCurrentImage.Text = "Ideal Image (Ground Truth)";
                    this.lblSecondImage.Text = "Test Image";
                    this.pnlCompareImages.Visible = true;
                    this.compareImagesChange();
                    this.lblResult.Visible = false;
                    this.txtResult.Text = "";
                    this.txtResult.Visible = false;
                    this.rbCompareRMS_SUB.Checked = true;
                    this.pnlComparePratt.Visible = false;
                    this.toolTipImage2.RemoveAll();
                    break;

                case "Objective Error Metrics":
                    this.lblCurrentImage.Text = "Ideal Image (Ground Truth)";
                    this.lblSecondImage.Text = "Test Image";
                    this.pnlCompareImages.Visible = true;
                    this.compareErrorChange();
                    this.lblResult.Visible = false;
                    this.txtResult.Text = "";
                    this.txtResult.Visible = false;
                    this.rbCompareRMS_SUB.Checked = true;
                    this.pnlComparePratt.Visible = false;
                    this.toolTipImage2.RemoveAll();
                    break;

                case "Pratt Figure of Merit":
                    this.lblCurrentImage.Text = "Ideal Edge Image"; 
                    this.lblSecondImage.Text = "Edge Detection Image";
                    this.pnlCompareImages.Visible = false;
                    this.pnlComparePratt.Visible = true;
                    this.toolTipImage2.RemoveAll();
                    if (string.IsNullOrEmpty(this.cboScaleFactor.Text)) this.cboScaleFactor.SelectedIndex = 0;
                    break;
            }
            if (MainForm.Viewers != null)
            {
                OnSelectedViewerChanged(MainForm.Viewers.SelectedViewer);
                OnViewerCollectionChanged();
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
        }

        private void OnSelectedViewerChanged(ViewerForm viewer)
        {
            if (MainForm.Viewers != null)
            {
                if ((ModifierKeys & Keys.Alt) == Keys.Alt)
                {
                    this.cboSecondImage.SelectedItem = viewer;
                }
                else
                {
                    this.txtCurrentImage.Tag = viewer;
                    this.txtCurrentImage.Text = "";
                    if (viewer != null)
                        this.txtCurrentImage.Text = viewer.Text;
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
                        break;

                    case WM.DESTROY:
                        MainForm.Viewers.SelectedViewerChanged -= this.OnSelectedViewerChanged;
                        MainForm.Viewers.ViewerCollectionChanged -= this.OnViewerCollectionChanged;
                        break;
                }
            }
        }

        private void compareImagesChange()
        {
            this.rbCompareRMS_SUB.Text = "Subtraction";
            this.rbCompareSNR_XOR.Text = "XOR";
            this.rbCompareSNR_XOR.Location = new System.Drawing.Point(90, 3);
            this.rbCompareRMS_SUB.Visible = true;
            this.rbCompareSNR_XOR.Visible = true;
            this.rbCompareXORe.Visible = false;
            this.rbCompareDice.Visible = false;
            this.rbCompareJaccard.Visible = false;
            this.rbCompareOverlap.Visible = false;
        }

        private void compareErrorChange()
        {
            this.rbCompareRMS_SUB.Text = "RMS Error";
            this.rbCompareSNR_XOR.Text = "Peak SNR";
            this.rbCompareSNR_XOR.Location = new System.Drawing.Point(80, 3);
            this.rbCompareRMS_SUB.Visible = true;
            this.rbCompareSNR_XOR.Visible = true;
            this.rbCompareXORe.Visible = true;
            this.rbCompareDice.Visible = true;
            this.rbCompareJaccard.Visible = true;
            this.rbCompareOverlap.Visible = true;
        }

        private void compareCheckChanged(object sender, EventArgs e)
        {
            this.lblResult.Visible = false;
            this.txtResult.Text = "";
            this.txtResult.Visible = false;
        }
    }
}
