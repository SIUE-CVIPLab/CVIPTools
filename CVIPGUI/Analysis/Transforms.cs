/*''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' ======================================================================
' Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
' ======================================================================
'
'             File Name: Transforms.cs
'           Description: Contains the controls and code
'                        for Analysis->Transforms page
'         Related Files: CvipOp.cs
'                        CvipConstant.cs
'   Initial Coding Date: April 2007
'              Modified: April 2013
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
    enum TransformSelection : int
    {
        dct = 39,
        fft = 41,
        walhad = 43,
        hadamard = 45,
        haar = 47,
        wavelet = 49,
        low_pass = 51,
        high_pass = 53,
        band_pass = 55,
        band_reject = 57,
        high_freq_emphasis = 59,
        notch = 61,
        fft_phase = 63,
        fft_magnitude = 65
    }
    public partial class Transforms : UserControl
    {
        private bool bKeepDCBandPass = false;
        private bool bKeepDCBandReject = true;
        private bool bKeepDCLowPass = true;
        private bool bKeepDCHighPass = false;
        private bool bKeepDCHighFreqEmphasis = false;

        private TransformSelection currentSelection = TransformSelection.fft;
        private List<NotchZone> lstNotches = new List<NotchZone>();

        public Transforms()
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
            int basis = 0, blocksize = 0, decomp = 0, dupImage = 0;
            int hist = 0, param2 = 0, xform = 0;

            switch (this.currentSelection)
            {
            case TransformSelection.dct:
            case TransformSelection.fft:
            case TransformSelection.haar:
            case TransformSelection.walhad:
            case TransformSelection.hadamard:
                xform = (int)this.currentSelection;
                if (this.rbForward.Checked)
                {
                    int limit = this.BlockSizeLimit;
                    if (this.BlockSize > limit)
                    {
                        MessageBox.Show("Block size should not exceed " + limit + ".",
                            "Block Size", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                        break;
                    }
                    switch (this.currentSelection)
                    {
                    case TransformSelection.dct:
                        outputImage = CvipOp.Dct_Transform(inputImage, this.BlockSize);
                        break;
                    case TransformSelection.fft:
                        outputImage = CvipOp.Fft_Transform(inputImage, this.BlockSize);
                        break;
                    case TransformSelection.haar:
                        outputImage = CvipOp.Haar_Transform(inputImage, 1, this.BlockSize);
                        break;
                    case TransformSelection.walhad:
                        outputImage = CvipOp.Walhad_Transform(inputImage, 1, this.BlockSize);
                        break;
                    case TransformSelection.hadamard:
                        outputImage = CvipOp.Walhad_Transform(inputImage, 3, this.BlockSize);
                        break;
                    }
                    if (outputImage != 0)
                    {
                        hist = CvipOp.history_create(xform, 2, this.BlockSize);
                        CvipOp.History_Add(outputImage, hist);
                    }
                }
                else
                {
                    if (CvipOp.History_Check(inputImage, xform) == 1)
                    {
                        hist = CvipOp.History_Get(inputImage, xform);
                        blocksize = CvipOp.History_get_data(hist, xform);
                        switch (this.currentSelection)
                        {
                        case TransformSelection.dct:
                            outputImage = CvipOp.Idct_Transform(inputImage, blocksize);
                            break;
                        case TransformSelection.fft:
                            outputImage = CvipOp.Ifft_Transform(inputImage, blocksize);
                            break;
                        case TransformSelection.haar:
                            outputImage = CvipOp.Haar_Transform(inputImage, 0, blocksize);
                            break;
                        case TransformSelection.walhad:
                            outputImage = CvipOp.Walhad_Transform(inputImage, 0, blocksize);
                            break;
                        case TransformSelection.hadamard:
                            outputImage = CvipOp.Walhad_Transform(inputImage, 2, blocksize);
                            break;
                        }
                        CvipOp.History_Delete_Program(inputImage, xform);
                    }
                    else
                    {
                        MessageBox.Show("Transform history information not found. Cannot perform the operation.",
                            "Transform History", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    }
                }
                break;

            case TransformSelection.low_pass:
            case TransformSelection.high_pass:
            case TransformSelection.band_pass:
            case TransformSelection.band_reject:
            case TransformSelection.high_freq_emphasis:
            case TransformSelection.notch:
                xform = CvipOp.Check_xform_history(inputImage, 2);
                if (CvipOp.History_Check(inputImage, xform) == 0)
                {
                    MessageBox.Show("Transform history information not found. Cannot perform the operation.",
                        "Transform History", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    break;
                }
                hist = CvipOp.History_Get(inputImage, xform);
                blocksize = (xform == (int)TransformSelection.wavelet) ? viewer.ImageHeight : CvipOp.History_get_data(hist, 0);
                if ((this.currentSelection != TransformSelection.notch) &&
                    (xform == (int)TransformSelection.fft))
                {
                    if ((this.currentSelection == TransformSelection.high_freq_emphasis) ||
                        (this.cboFilterType.SelectedIndex == 0)) // Ideal
                    {
                        switch (this.currentSelection)
                        {
                        case TransformSelection.low_pass:
                            outputImage = CvipOp.Ideal_Low(inputImage, blocksize, this.KeepDC, this.CutoffFreq);
                            break;
                        case TransformSelection.high_pass:
                            outputImage = CvipOp.Ideal_High(inputImage, blocksize, this.KeepDC, this.CutoffFreq);
                            break;
                        case TransformSelection.band_pass:
                            outputImage = CvipOp.Ideal_Band_Pass(inputImage, blocksize, this.KeepDC, this.CutoffFreqLow, this.CutoffFreqHigh);
                            break;
                        case TransformSelection.band_reject:
                            outputImage = CvipOp.Ideal_Band_Reject(inputImage, blocksize, this.KeepDC, this.CutoffFreqLow, this.CutoffFreqHigh);
                            break;
                        case TransformSelection.high_freq_emphasis:
                            outputImage = CvipOp.High_Freq_Emphasis(inputImage, blocksize, this.KeepDC, this.CutoffFreqHigh, this.EmphasisOffset, this.FilterOrder);
                            break;
                        }
                    }
                    else // Butterworth
                    {
                        switch (this.currentSelection)
                        {
                        case TransformSelection.low_pass:
                            outputImage = CvipOp.Butterworth_Low(inputImage, blocksize, this.KeepDC, this.CutoffFreq, this.FilterOrder);
                            break;
                        case TransformSelection.high_pass:
                            outputImage = CvipOp.Butterworth_High(inputImage, blocksize, this.KeepDC, this.CutoffFreq, this.FilterOrder);
                            break;
                        case TransformSelection.band_pass:
                            outputImage = CvipOp.Butterworth_Band_Pass(inputImage, blocksize, this.KeepDC, this.CutoffFreqLow, this.CutoffFreqHigh, this.FilterOrder);
                            break;
                        case TransformSelection.band_reject:
                            outputImage = CvipOp.Butterworth_Band_Reject(inputImage, blocksize, this.KeepDC, this.CutoffFreqLow, this.CutoffFreqHigh, this.FilterOrder);
                            break;
                        }
                    }
                    if (outputImage != 0)
                    {
                        dupImage = CvipOp.Duplicate_Image(outputImage);
                        outputImage = CvipOp.Ifft_Transform(outputImage, blocksize);
                        CvipOp.History_Delete_Program(outputImage, xform);
                    }
                }
                else
                {
                    switch (this.currentSelection)
                    {
                    case TransformSelection.low_pass:
                        outputImage = CvipOp.Nonfft_Xformfilter(inputImage, blocksize, this.KeepDC, this.cboFilterType.SelectedIndex + 1, this.CutoffFreq, 0, this.FilterOrder);
                        break;
                    case TransformSelection.high_pass:
                        outputImage = CvipOp.Nonfft_Xformfilter(inputImage, blocksize, this.KeepDC, this.cboFilterType.SelectedIndex + 3, this.CutoffFreq, 0, this.FilterOrder);
                        break;
                    case TransformSelection.band_pass:
                        outputImage = CvipOp.Nonfft_Xformfilter(inputImage, blocksize, this.KeepDC, this.cboFilterType.SelectedIndex + 5, this.CutoffFreqLow, this.CutoffFreqHigh, this.FilterOrder);
                        break;
                    case TransformSelection.band_reject:
                        outputImage = CvipOp.Nonfft_Xformfilter(inputImage, blocksize, this.KeepDC, this.cboFilterType.SelectedIndex + 7, this.CutoffFreqLow, this.CutoffFreqHigh, this.FilterOrder);
                        break;
                    case TransformSelection.high_freq_emphasis:
                        outputImage = CvipOp.Nonfft_Xformfilter(inputImage, blocksize, this.KeepDC, 9, this.CutoffFreqHigh, this.EmphasisOffset, this.FilterOrder);
                        break;
                    case TransformSelection.notch:
                        if (this.lstNotches.Count == 0)
                        {
                            MessageBox.Show("No notches are defined. Cannot perform the operation.",
                                "Notch Filter", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                            break;
                        }
                        outputImage = CvipOp.Notch(inputImage, this.lstNotches.ToArray());
                        break;
                    }
                    if (outputImage != 0)
                    {
                        dupImage = CvipOp.Duplicate_Image(outputImage);
                        switch ((TransformSelection)xform)
                        {
                        case TransformSelection.dct:
                            outputImage = CvipOp.Idct_Transform(outputImage, blocksize);
                            break;
                        case TransformSelection.haar:
                            outputImage = CvipOp.Haar_Transform(outputImage, 0, blocksize);
                            break;
                        case TransformSelection.walhad:
                            outputImage = CvipOp.Walhad_Transform(outputImage, 0, blocksize);
                            break;
                        case TransformSelection.hadamard:
                            outputImage = CvipOp.Walhad_Transform(outputImage, 2, blocksize);
                            break;
                        case TransformSelection.fft:
                            outputImage = CvipOp.Ifft_Transform(outputImage, blocksize);
                            break;
                        case TransformSelection.wavelet:
                            basis = CvipOp.History_get_data2(hist, xform, 0);
                            decomp = CvipOp.History_get_data2(hist, xform, 1);
                           // param2 = viewer.ImageHeight / (int)Math.Exp(Math.Log(2) * (decomp - 1));
                            param2 = viewer.ImageHeight / (int)Math.Pow(2, (decomp - 1));//(int)Math.Exp(Math.Log(2) * (decomp - 1));
                        
                            if (basis == 1) // haar
                            {
                                outputImage = CvipOp.Wavhaar_Transform(outputImage, -1, param2);
                            }
                            else // daub4
                            {
                                outputImage = CvipOp.Wavdaub4_Transform(outputImage, -1, param2);
                            }
                            //CvipOp.History_Delete_Program(outputImage, xform);
                            break;
                        }
                            CvipOp.History_Delete_Program(outputImage, xform);
                        }
                }
                break;

            case TransformSelection.wavelet:
                xform = (int)this.currentSelection;
                if (this.rbForward.Checked)
                {
                    CvipOp.Cast_Image(inputImage, dataType.CVIP_FLOAT);
                    basis = this.cboBasis.SelectedIndex + 1;
                    decomp = this.Decomposition;
                    param2 = viewer.ImageHeight / (int)Math.Pow(2, (decomp - 1));//(int)Math.Exp(Math.Log(2) * (decomp - 1));
                    if (basis == 1) // haar
                    {
                        outputImage = CvipOp.Wavhaar_Transform(inputImage, 1, param2);
                    }
                    else // daub4
                    {
                        outputImage = CvipOp.Wavdaub4_Transform(inputImage, 1, param2);
                    }
                    if (outputImage != 0)
                    {
                        hist = CvipOp.history_create2(xform, 2, basis, decomp);
                        CvipOp.History_Add(outputImage, hist);
                    }
                }
                else
                {
                    if (CvipOp.History_Check(inputImage, xform) == 1)
                    {
                        hist = CvipOp.History_Get(inputImage, xform);
                        basis = CvipOp.History_get_data2(hist, xform, 0);
                        decomp = CvipOp.History_get_data2(hist, xform, 1);
                        param2 = viewer.ImageHeight / (int)Math.Pow(2, (decomp - 1));//(int)Math.Exp(Math.Log(2) * (decomp - 1));
                        if (basis == 1) // haar
                        {
                            outputImage = CvipOp.Wavhaar_Transform(inputImage, -1, param2);
                        }
                        else // daub4
                        {
                            outputImage = CvipOp.Wavdaub4_Transform(inputImage, -1, param2);
                        }
                        CvipOp.History_Delete_Program(inputImage, xform);
                    }
                    else
                    {
                        MessageBox.Show("Transform history information not found. Cannot perform the operation.",
                            "Transform History", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    }
                }
                break;

            case TransformSelection.fft_phase:
                if (CvipOp.History_Check(inputImage, 41) == 1)
                {
                    //MessageBox.Show();
                    if (CvipOp.GetDataFormat_Image(inputImage).ToString() == "COMPLEX")
                    {
                        outputImage = CvipOp.Fft_Phase(inputImage, 1, -1);
                        hist = CvipOp.History_Get(outputImage, 41);
                        blocksize = CvipOp.History_get_data(hist, 0);
                        outputImage = CvipOp.Ifft_Transform(outputImage, blocksize);
                        outputImage = CvipOp.Remap_Image(outputImage, dataType.CVIP_BYTE, 0, 255);
                       
                    }
                    else
                    {
                        MessageBox.Show("Transform history information not found. Cannot perform the operation.",
                        "Transform History", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                
                    }
                    }

                else
                {
                    MessageBox.Show("Non-FFT transform image. Cannot perform the operation.",
                        "Transform History", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                }
                break;

            case TransformSelection.fft_magnitude:
                if (CvipOp.History_Check(inputImage, 41) == 1)
                {
                    outputImage = CvipOp.Fft_Mag(inputImage);
                    hist = CvipOp.History_Get(outputImage, 41);
                    blocksize = CvipOp.History_get_data(hist, 0);
                    outputImage = CvipOp.Ifft_Transform(outputImage, blocksize);
                    if (this.rbTranslate.Checked)
                        outputImage = CvipOp.Translate(outputImage, 1, 0, 0, CvipOp.GetNoOfRows_Image(outputImage), CvipOp.GetNoOfCols_Image(outputImage), 128, 128, 128);
                    outputImage = CvipOp.Remap_Image(outputImage, dataType.CVIP_BYTE, 0, 255);
                }
                else
                {
                    MessageBox.Show("Transform history information not found. Cannot perform the operation.",
                        "Transform History", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                }
                break;
            }
            if (outputImage != 0)
            {
                string newImageName;
                if ((this.currentSelection == TransformSelection.low_pass) ||
                    (this.currentSelection == TransformSelection.high_pass) ||
                    (this.currentSelection == TransformSelection.band_pass) ||
                    (this.currentSelection == TransformSelection.band_reject) ||
                    (this.currentSelection == TransformSelection.notch))
                {
                    newImageName = viewer.Text + "_" + CvipFunctionNames.getFncName(this.currentSelection.ToString());
                    newImageName += CvipConstant.imageNameCount++.ToString();
                    MainForm.Viewers.Add(dupImage, newImageName, LogRemap.All);
                }
                newImageName = viewer.Text + "_" + CvipFunctionNames.getFncName(this.currentSelection.ToString());
                newImageName += CvipConstant.imageNameCount++.ToString();
                if (this.rbForward.Checked && ((this.currentSelection == TransformSelection.dct) ||
                                                (this.currentSelection == TransformSelection.fft) ||
                                                (this.currentSelection == TransformSelection.haar) ||
                                                (this.currentSelection == TransformSelection.walhad) ||
                                                (this.currentSelection == TransformSelection.hadamard) ||
                                                (this.currentSelection == TransformSelection.wavelet)))
                {
                    MainForm.Viewers.Add(outputImage, newImageName, LogRemap.All);
                }
                else
                {
                    MainForm.Viewers.Add(outputImage, newImageName);
                }
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
        private void btnNotchAdd_Click(object sender, EventArgs e)
        {
            this.lstNotches.Add(new NotchZone(this.NotchRow, this.NotchCol, this.NotchSize));
            this.cboPoint.Items.Insert(this.cboPoint.Items.Count - 1, this.cboPoint.Items.Count);
            this.cboPoint.SelectedIndex = this.cboPoint.Items.Count - 2;
            this.btnAddNotch.Enabled = false;
        }
        private void btnNotchRedo_Click(object sender, EventArgs e)
        {
            ResetNotch();
        }
        private void btnReset_Click(object sender, EventArgs e)
        {
            ResetControls();
        }
        private void cboBlockSize_Validating(object sender, CancelEventArgs e)
        {
            int size;
            if (!int.TryParse(this.cboBlockSize.Text, out size))
            {
                MessageBox.Show("Please check the input value. Only integers are accepted.",
                   "Integer Required", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                this.cboBlockSize.SelectAll();
                e.Cancel = true;
                return;
            }
            if ((Math.Log(size, 2) % 1) != 0.0)
            {
                MessageBox.Show("Block size should be a power of 2.",
                    "Block Size", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                this.cboBlockSize.SelectAll();
                e.Cancel = true;
                return;
            }
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
        private void cboFilterType_SelectedIndexChanged(object sender, EventArgs e)
        {
            this.cboFilterOrder.Visible = this.lblFilterOrder.Visible = (this.cboFilterType.SelectedIndex == 1);
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
        private void cboNotchVal_Validated(object sender, EventArgs e)
        {
            if ((this.cboPoint.SelectedIndex >= 0) &&
                (this.cboPoint.SelectedIndex < this.cboPoint.Items.Count - 1))
            {
                NotchZone nz = this.lstNotches[this.cboPoint.SelectedIndex];
                nz.Col = this.NotchCol;
                nz.Row = this.NotchRow;
                nz.Radius = this.NotchSize;
                this.lstNotches[this.cboPoint.SelectedIndex] = nz;
            }
        }
        private void cboPoint_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (this.cboPoint.SelectedIndex < this.cboPoint.Items.Count - 1)
            {
                this.NotchCol = this.lstNotches[this.cboPoint.SelectedIndex].Col;
                this.NotchRow = this.lstNotches[this.cboPoint.SelectedIndex].Row;
                this.NotchSize = this.lstNotches[this.cboPoint.SelectedIndex].Radius;
            }
            else
                this.btnAddNotch.Enabled = true;
        }
        private void chkKeepDC_CheckedChanged(object sender, EventArgs e)
        {
            switch (this.currentSelection)
            {
            case TransformSelection.low_pass:
                this.bKeepDCLowPass = this.chkKeepDC.Checked;
                break;
            case TransformSelection.high_pass:
                this.bKeepDCHighPass = this.chkKeepDC.Checked;
                break;
            case TransformSelection.band_pass:
                this.bKeepDCBandPass = this.chkKeepDC.Checked;
                break;
            case TransformSelection.band_reject:
                this.bKeepDCBandReject = this.chkKeepDC.Checked;
                break;
            case TransformSelection.high_freq_emphasis:
                this.bKeepDCHighFreqEmphasis = this.chkKeepDC.Checked;
                break;
            }
        }
        protected override void OnLoad(EventArgs e)
        {
            base.OnLoad(e);

            this.rbDCT.Tag = TransformSelection.dct;
            this.rbFFT.Tag = TransformSelection.fft;
            this.rbHaar.Tag = TransformSelection.haar;
            this.rbWalsh.Tag = TransformSelection.walhad;
            this.rbHadamard.Tag = TransformSelection.hadamard;
            this.rbWavelet.Tag = TransformSelection.wavelet;
            this.rbLowPass.Tag = TransformSelection.low_pass;
            this.rbHighPass.Tag = TransformSelection.high_pass;
            this.rbBandPass.Tag = TransformSelection.band_pass;
            this.rbBandReject.Tag = TransformSelection.band_reject;
            this.rbHighFreqEmphasis.Tag = TransformSelection.high_freq_emphasis;
            this.rbNotch.Tag = TransformSelection.notch;
            this.rbFFTPhase.Tag = TransformSelection.fft_phase;
            this.rbFFTMagnitude.Tag = TransformSelection.fft_magnitude;

            ResetControls();
        }
        private void OnSelectedViewerChanged(ViewerForm viewer)
        {
            int limit = this.BlockSizeLimit;
           // if (this.BlockSize < limit)
                this.BlockSize = limit;
           // int x= Math.Max(viewer.Height, viewer.Width);
           // if(viewer !=null)
           // this.cboBlockSize.Text = (Math.Log(Math.Max(viewer.Height, viewer.Width)) / Math.Log(2)).ToString();
            //viewer.Width

        }
        private void OnViewerMouseClick(Point pos, ViewerForm viewer)
        {
            this.cboPoint.SelectedIndex = this.cboPoint.Items.Count - 1;
            this.NotchCol = pos.X;
            this.NotchRow = pos.Y;
            this.btnAddNotch.Enabled = true;
        }
        private void rbTransformDirection_CheckedChanged(object sender, EventArgs e)
        {
            if ((this.pnlForward.Visible = this.rbForward.Checked) == true)
            {
                this.cboBlockSize.Visible = this.lblBlockSize.Visible = (this.currentSelection != TransformSelection.wavelet);
                this.cboBasis.Visible = this.lblBasis.Visible = (this.currentSelection == TransformSelection.wavelet);
                this.cboDecomposition.Visible = this.lblDecomposition.Visible = (this.currentSelection == TransformSelection.wavelet);
            }
        }
        private void rbTransforms_CheckedChanged(object sender, EventArgs e)
        {
            RadioButton rb = sender as RadioButton;
            if ((rb != null) && rb.Checked && (rb.Tag != null))
            {
                this.currentSelection = (TransformSelection)rb.Tag;
                UpdateControls();
            }
        }
        private void ResetControls()
        {
            // Transforms group
            this.rbForward.Checked = true;

            // Forward-Transform panel
            int limit = this.BlockSizeLimit;
            this.BlockSize = (limit < 256) ? limit : 256;
            this.cboBasis.SelectedIndex = 0;
            this.cboDecomposition.SelectedIndex = 0;

            // Transform-Filters panel
            this.bKeepDCBandPass = false;
            this.bKeepDCBandReject = true;
            this.bKeepDCLowPass = true;
            this.bKeepDCHighPass = false;
            this.bKeepDCHighFreqEmphasis = false;

            this.cboCutoff.Text = "32";
            this.cboCutoffHigh.Text = "128";
            this.cboCutoffLow.Text = "32";
            this.cboEmphasisOffset.Text = "1.2";
            this.cboFilterOrder.Text = "1";
            this.cboFilterType.SelectedIndex = 0;
            this.chkKeepDC.Checked = false;

            // Notch-Filter panel
            ResetNotch();

            // FFT-Magnitude panel
            this.rbTranslate.Checked = true;

            // Default current selection
            this.currentSelection = TransformSelection.fft;
            this.rbFFT.Checked = true;
            UpdateControls();
        }
        private void ResetNotch()
        {
            this.lstNotches.Clear();
            object newitem = this.cboPoint.Items[this.cboPoint.Items.Count - 1];
            this.cboPoint.Items.Clear();
            this.cboPoint.Items.Add(newitem);
            this.cboPoint.SelectedIndex = 0;
            this.NotchCol = 0;
            this.NotchRow = 0;
            this.NotchSize = 10;
        }
        private void txtIntVal_Validating(object sender, CancelEventArgs e)
        {
            TextBox txt = sender as TextBox;
            int val;
            if (!int.TryParse(txt.Text, out val))
            {
                MessageBox.Show("Please check the input value. Only integers are accepted.",
                   "Integer Required", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                txt.SelectAll();
                e.Cancel = true;
            }
        }
        private void UpdateControls()
        {
            switch (this.currentSelection)
            {
            case TransformSelection.dct:
            case TransformSelection.fft:
            case TransformSelection.haar:
            case TransformSelection.walhad:
            case TransformSelection.hadamard:
            case TransformSelection.wavelet:
                this.pnlTransforms.Visible = true;
                if ((this.pnlForward.Visible = this.rbForward.Checked) == true)
                {
                    this.cboBlockSize.Visible = this.lblBlockSize.Visible = (this.currentSelection != TransformSelection.wavelet);
                    this.cboBasis.Visible = this.lblBasis.Visible = (this.currentSelection == TransformSelection.wavelet);
                    this.cboDecomposition.Visible = this.lblDecomposition.Visible = (this.currentSelection == TransformSelection.wavelet);
                }
                this.pnlFilters.Visible = false;
                this.pnlNotch.Visible = false;
                this.pnlFFTMagnitude.Visible = false;
                break;

            case TransformSelection.low_pass:
            case TransformSelection.high_pass:
                this.pnlFilters.Visible = true;
                this.cboCutoff.Visible = this.lblCutoff.Visible = true;
                this.cboFilterType.Visible = this.lblFilterType.Visible = true;
                this.cboFilterOrder.Visible = this.lblFilterOrder.Visible = (this.cboFilterType.SelectedIndex == 1);
                this.cboCutoffLow.Visible = this.lblCutoffLow.Visible = false;
                this.cboCutoffHigh.Visible = this.lblCutoffHigh.Visible = false;
                this.cboEmphasisOffset.Visible = this.lblEmphasisOffset.Visible = false;
                this.chkKeepDC.Checked = (this.currentSelection == TransformSelection.low_pass) ? this.bKeepDCLowPass : this.bKeepDCHighPass;
                this.chkKeepDC.Visible = true;

                this.pnlTransforms.Visible = false;
                this.pnlNotch.Visible = false;
                this.pnlFFTMagnitude.Visible = false;
                break;

            case TransformSelection.band_pass:
            case TransformSelection.band_reject:
                this.pnlFilters.Visible = true;
                this.cboCutoff.Visible = this.lblCutoff.Visible = false;
                this.cboFilterType.Visible = this.lblFilterType.Visible = true;
                this.cboFilterOrder.Visible = this.lblFilterOrder.Visible = (this.cboFilterType.SelectedIndex == 1);
                this.cboCutoffLow.Visible = this.lblCutoffLow.Visible = true;
                this.cboCutoffHigh.Visible = this.lblCutoffHigh.Visible = true;
                this.cboEmphasisOffset.Visible = this.lblEmphasisOffset.Visible = false;
                this.chkKeepDC.Checked = (this.currentSelection == TransformSelection.band_pass) ? this.bKeepDCBandPass : this.bKeepDCBandReject;
                this.chkKeepDC.Visible = true;

                this.pnlTransforms.Visible = false;
                this.pnlNotch.Visible = false;
                this.pnlFFTMagnitude.Visible = false;
                break;

            case TransformSelection.high_freq_emphasis:
                this.pnlFilters.Visible = true;
                this.cboCutoff.Visible = this.lblCutoff.Visible = false;
                this.cboFilterType.Visible = this.lblFilterType.Visible = false;
                this.cboFilterOrder.Visible = this.lblFilterOrder.Visible = true;
                this.cboCutoffLow.Visible = this.lblCutoffLow.Visible = false;
                this.cboCutoffHigh.Visible = this.lblCutoffHigh.Visible = true;
                this.cboEmphasisOffset.Visible = this.lblEmphasisOffset.Visible = true;
                this.chkKeepDC.Checked = this.bKeepDCHighFreqEmphasis;
                this.chkKeepDC.Visible = true;

                this.pnlTransforms.Visible = false;
                this.pnlNotch.Visible = false;
                this.pnlFFTMagnitude.Visible = false;
                break;

            case TransformSelection.notch:
                this.pnlTransforms.Visible = false;
                this.pnlFilters.Visible = false;
                this.pnlNotch.Visible = true;
                this.pnlFFTMagnitude.Visible = false;
                break;

            case TransformSelection.fft_phase:
                this.pnlTransforms.Visible = false;
                this.pnlFilters.Visible = false;
                this.pnlNotch.Visible = false;
                this.pnlFFTMagnitude.Visible = false;
                break;

            case TransformSelection.fft_magnitude:
                this.pnlTransforms.Visible = false;
                this.pnlFilters.Visible = false;
                this.pnlNotch.Visible = false;
                this.pnlFFTMagnitude.Visible = true;
                break;
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
                    ViewerForm.MouseClicked += this.OnViewerMouseClick;
                    OnSelectedViewerChanged(MainForm.Viewers.SelectedViewer);
                    break;

                case WM.DESTROY:
                    MainForm.Viewers.SelectedViewerChanged -= this.OnSelectedViewerChanged;
                    ViewerForm.MouseClicked -= this.OnViewerMouseClick;
                    break;
                }
            }
        }

        private double EmphasisOffset { get { return double.Parse(this.cboEmphasisOffset.Text); } }

        private int CutoffFreq { get { return int.Parse(this.cboCutoff.Text); } }
        private int CutoffFreqHigh { get { return int.Parse(this.cboCutoffHigh.Text); } }
        private int CutoffFreqLow { get { return int.Parse(this.cboCutoffLow.Text); } }
        private int Decomposition { get { return int.Parse(this.cboDecomposition.Text); } }
        private int KeepDC { get { return this.chkKeepDC.Checked ? 1 : 0; } }

        private int BlockSize
        {
            get { return int.Parse(this.cboBlockSize.Text); }
            set { this.cboBlockSize.Text = value.ToString(); }
        }
        private int BlockSizeLimit
        {
            get
            {
                int limit = int.MaxValue;
                ViewerForm viewer = null;
                if ((MainForm.Viewers != null) &&
                    ((viewer = MainForm.Viewers.SelectedViewer) != null))
                {
                    int maxside = Math.Max(viewer.ImageHeight, viewer.ImageWidth);
                    double power = Math.Log(maxside, 2);
                    if ((power % 1) != 0.0)
                        power += 1.0;
                    limit = (int)Math.Pow(2.0, (double)((int)power));
                }
                else return 256;
                return limit;
            }
        }
        private int FilterOrder
        {
            get
            {
                int order = 0;
                if ((this.cboFilterType.SelectedIndex != 0) ||
                    (this.currentSelection == TransformSelection.high_freq_emphasis))
                {
                    order = int.Parse(this.cboFilterOrder.Text);
                }
                return order;
            }
        }
        private int NotchCol
        {
            get { return int.Parse(this.txtNotchCol.Text); }
            set { this.txtNotchCol.Text = value.ToString(); }
        }
        private int NotchRow
        {
            get { return int.Parse(this.txtNotchRow.Text); }
            set { this.txtNotchRow.Text = value.ToString(); }
        }
        private int NotchSize
        {
            get { return int.Parse(this.cboNotchSize.Text); }
            set { this.cboNotchSize.Text = value.ToString(); }
        }
    }
}
