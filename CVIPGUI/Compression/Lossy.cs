/*''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' ======================================================================
' Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
' ======================================================================
'
'             File Name: Lossy.cs
'           Description: Contains the controls and code
'                        for Compression->Lossy page
'         Related Files: CvipOp.cs
'                        CvipConstant.cs
'   Initial Coding Date: October 2007
'              Modified: November 2011
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
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''*/

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Text;
using System.Windows.Forms;

namespace CVIPGUI.Compression
{
    enum LossySelection
    {
        BTC,
        MBTC,
        PMBTC,
        BitplaneRLC,
        DyRLC,
        JPEG,
        JPEG2_,
        DPC,
        Zonal,
        Fractal,
        VQ,
        XVQ,
        XfrmCmpr
    }

    public partial class Lossy : UserControl
    {
        TextBox[] arrText;
        public viewTable tableChrom = null, tableLumi = null;

        public string[] tableChrominanceSave = new string[64];
        public string[] tableLuminanceSave = new string[64];
        public string[] tableChrominanceNoneQuantSave = new string[64];
        public string[] tableLuminanceNoneQuantSave = new string[64];

        public bool bChrominanceTableSaved = false;
        public bool bLuminanceTableSaved = false;

        private LossySelection currentSelection;
        private string vq_codebook;

        string[] tableChrominanceDefault = new string[] {
                                                    "17", "18", "24", "47", "99", "99", "99", "99",
                                                    "18", "21", "26", "66", "99", "99", "99", "99",
                                                    "24", "26", "56", "99", "99", "99", "99", "99",
                                                    "47", "66", "99", "99", "99", "99", "99", "99",
                                                    "99", "99", "99", "99", "99", "99", "99", "99",
                                                    "99", "99", "99", "99", "99", "99", "99", "99",
                                                    "99", "99", "99", "99", "99", "99", "99", "99",
                                                    "99", "99", "99", "99", "99", "99", "99", "99" };

        string[] tableLuminanceDefault = new string[]   {
                                                    "16", "11", "10", "16", "24",  "15",  "1",   "61",
                                                    "12", "12", "14", "19", "26",  "58",  "60",  "55",
                                                    "14", "13", "16", "24", "40",  "57",  "69",  "56",
                                                    "14", "17", "22", "29", "51",  "81",  "80",  "62",
                                                    "18", "22", "37", "56", "68",  "109", "103", "77",
                                                    "24", "35", "55", "64", "81",  "104", "113", "92",
                                                    "49", "64", "78", "87", "103", "121", "120", "101",
                                                    "72", "92", "95", "98", "112", "100", "103", "99" };

        public Lossy()
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
            // create a new temp file for compression file
            string dname = Environment.GetEnvironmentVariable("TEMP") + @"\compression";
            if (!Directory.Exists(dname)) Directory.CreateDirectory(dname);

            string codefile, compression_file;
            double deviation, ratio;
            int bits, cdbook_in_file, check1, check2, clipping, coding;
            int color_space, dir, dtype, fixed_cdbook, idx, jpegquant;
            int keepdc, mask, max, origin, remap, scheme, xform;
            CheckBox[] arrCheck = new CheckBox[] {
                checkBox15, checkBox14, checkBox13, checkBox12,
                checkBox11, checkBox10, checkBox9, checkBox8 };

            for (idx = 1; true; idx++)
            {
                compression_file = dname + @"\" + idx.ToString() + ".tmp__";
                if (!File.Exists(compression_file)) break;
            }
            // disable Apply button
            this.btnApply.Enabled = false;
            this.Cursor = Cursors.WaitCursor;

            // get the image that will be operated on
            int inputImage = viewer.CVIPimage, outputImage = 0;

            switch (this.currentSelection)
            {
            case LossySelection.BTC:
                if (Convert.ToInt16(comboBox1.Text) <= 2)
                {
                    MessageBox.Show("Please enter a block size greater than 2!", "Inappropriate Block Size",
                        MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    break;
                }
                outputImage = CvipOp.BTC_Compression_Image(inputImage, compression_file, Convert.ToInt16(comboBox1.Text));
                break;

            case LossySelection.MBTC:
                if (Convert.ToInt16(comboBox1.Text) <= 0)
                {
                    MessageBox.Show("Please enter a block size greater than 0!", "Inappropriate Block Size",
                        MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    break;
                }
                outputImage = CvipOp.MBTC_Compression_Image(inputImage, compression_file, Convert.ToInt16(comboBox1.Text));
                break;

            case LossySelection.PMBTC:
                if (Convert.ToInt16(comboBox1.Text) <= 0)
                {
                    MessageBox.Show("Please enter a block size greater than 0!", "Inappropriate Block Size",
                        MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    break;
                }
                outputImage = CvipOp.PMBTC_Compression_Image(inputImage, compression_file, Convert.ToInt16(comboBox1.Text));
                break;

            case LossySelection.BitplaneRLC:
                mask = 0;
                for (int i = 0; i < 8; i++)
                {
                    if (arrCheck[i].Checked)
                        mask += (int)Math.Pow(2, i);
                }
                outputImage = CvipOp.BRLC_Compression_Image(inputImage, compression_file, mask);
                break;

            case LossySelection.DyRLC:
                outputImage = CvipOp.DynRLC_Compression_Image(inputImage, compression_file, Convert.ToInt16(Convert.ToDecimal(comboBox1.Text)));
                break;

            case LossySelection.JPEG:
                // inputImage, quality, grayscale, optimize, smooth
                // default optimized is 1 since tcl does set that parameters
                outputImage = CvipOp.JPEG_Compression_Image(inputImage, compression_file, Convert.ToInt16(Convert.ToDecimal(comboBox1.Text)), Convert.ToInt16(checkBoxGrayScale.Checked), 1, Convert.ToInt16(checkBoxSmooth.Checked));
                break;

            case LossySelection.JPEG2_:
                // inputImage, quality, grayscale, optimize, smooth
                // default optimized is 1 since tcl does set that parameters
                int rate = -1, quality = -1;
                if (cbRatio.Enabled)
                    rate = Convert.ToInt16(cbRatio.Text);
                if (cbQuality.Enabled)
                    quality = Convert.ToInt16(cbQuality.Text);
                outputImage = CvipOp.JPEG2000_Compression_Image(inputImage, compression_file, rate, quality, Convert.ToInt16(cbNumResolution.Text), Convert.ToInt16(cbCodeBlockSize.Text));
                break;

            case LossySelection.DPC:
                bits = Convert.ToInt16(comboBox7.Text);
                if (bits < 1 || bits > 7)
                {
                    MessageBox.Show("The number of bits' input range is [1,7].!",
                        "input error!", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    break;
                }
                // ratio, bits, clipping, dir, origin, deviation
                // set clipping to 1
                // if you select Lloyd-Max, for coding it uses the reconstruted value in the predictor;
                // If you select "Original value", it uses Truncaiton coding and the original value in the predictor;
                // if you select "Reconsrtruted value" it does Truncaiton for the coding and uses the reconstruted value in the predictor.
                if (comboBox3.Text == "Original Value")
                    origin = 1;       //Original value
                else
                {
                    if (comboBox4.Text == "Lloyd-Max Quant")
                        origin = 3;   //Lloyd-Max
                    else
                        origin = 2;   //Reconsrtruted value
                }
                clipping = 1;
                deviation = (origin == 3) ? Convert.ToDouble(comboBox8.Text) : -1;
                dir = comboBox6.SelectedIndex;
                ratio = Convert.ToDouble(comboBox5.Text);
                outputImage = CvipOp.DPC_Compression_Image(inputImage, compression_file, Convert.ToSingle(ratio), bits, clipping, dir, origin, Convert.ToSingle(deviation));
                break;

            case LossySelection.Zonal:
                if (Convert.ToInt16(comboBox3.Text) <= 0)
                {
                    MessageBox.Show("Please enter a block size greater than 0!", "Inappropriate Block Size",
                        MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    break;
                }

                if (Convert.ToDouble(comboBox5.Text) < 2)
                {
                    MessageBox.Show("Please enter Compression ration greater than or equal to 2 !", "Inappropriate Compression Ratio",
                        MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    break;
                }
                
                
                outputImage = CvipOp.Zonal_Compression_Image(inputImage, compression_file, Convert.ToInt16(comboBox3.Text), comboBox4.SelectedIndex + 1, comboBox6.SelectedIndex + 1, Convert.ToDouble(comboBox5.Text), Convert.ToInt16(checkBox16.Checked));
                break;

            case LossySelection.Fractal:
                max = -2;
                for (int size = 1; size < Math.Max(viewer.ImageHeight, viewer.ImageWidth); max++)
                {
                    size *= 2;
                }
                if (Convert.ToInt16(comboBox5.Text) > max)
                {
                    MessageBox.Show("'Recursion size max' should be no greater than " + max.ToString() + ".",
                        "Size error!", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    comboBox5.Text = max.ToString();
                    break;
                }
                if (Convert.ToInt16(comboBox4.Text) <= 0 || Convert.ToInt16(comboBox5.Text) <= 0)
                {
                    MessageBox.Show("Please enter a recursion size greater than 0!",
                        "Inappropriate Recursion Size", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    break;
                }
                outputImage = CvipOp.Fractal_Compression_Image(inputImage, compression_file, Convert.ToInt16(comboBox3.Text), Convert.ToInt16(comboBox4.Text), Convert.ToInt16(comboBox5.Text), Convert.ToInt16(comboBox6.Text), Convert.ToInt16(checkBox16.Checked));
                break;

            case LossySelection.VQ:
                cdbook_in_file = 0;
                fixed_cdbook = 1;
                // Read codebook from file; don't save codebook              cdbook_in_file : 0 fixed_cdbook : 1
                // Read codebook from file; save codebook with coding result cdbook_in_file : 1 fixed_cdbook : 1
                // Generate codebook; save codebook with coding result       cdbook_in_file : 1 fixed_cdbook : 0
                // Generate codebook; save codebook into separate file       cdbook_in_file : 0 fixed_cdbook : 0
                if (radioButton1.Checked)
                {
                    cdbook_in_file = 0;
                    fixed_cdbook = 1;
                }
                else if (radioButton2.Checked)
                {
                    cdbook_in_file = 1;
                    fixed_cdbook = 1;
                }
                else if (radioButton3.Checked)
                {
                    cdbook_in_file = 1;
                    fixed_cdbook = 0;
                }
                else if (radioButton4.Checked)
                {
                    cdbook_in_file = 0;
                    fixed_cdbook = 0;
                    if (vq_codebook == null)
                    {
                        MessageBox.Show("Please give a codebook file name first.!",
                            "Codebook name error!", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                        break;
                    }
                    if (File.Exists(MainForm.CVIPtoolsHOME + @"bin\codebook\" + textBoxCodeName.Text))
                    {
                        string msg = "Current file already exists. Do you want to overwrite it?";
                        string title = "Codebook name error!";
                        MessageBoxButtons btns = MessageBoxButtons.OKCancel;
                        MessageBoxIcon icon = MessageBoxIcon.Warning;
                        if (MessageBox.Show(msg, title, btns, icon) != DialogResult.Yes)
                            break;
                    }
                }
                outputImage = CvipOp.Vq_Compression_Image(inputImage, compression_file, Convert.ToInt16(comboBoxHeight.Text), Convert.ToInt16(comboBoxWidth.Text), Convert.ToInt16(comboBoxSize.Text), Convert.ToDouble(comboBoxErrorThresh.Text), vq_codebook, cdbook_in_file, fixed_cdbook);
                break;

            case LossySelection.XVQ:
                // if the image is not color, it can't be preprocessed by PCT
                xform = comboBox4.SelectedIndex + 1;
                if ((xform == 2 || xform == 4) && (viewer.Bands != 3))
                {
                    MessageBox.Show("This is not a color image. So it can't be pre-processed by PCT.",
                        "Image input error!", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    break;
                }
                dtype = comboBox5.SelectedIndex + 1;
                keepdc = checkBox16.Checked ? 0 : 1;
                remap = comboBox6.SelectedIndex + 1;
                scheme = (comboBox3.SelectedIndex + 1) * 2;
                if ((xform == 1) || (xform == 3)) scheme--; // Without PCT preprocessing
                outputImage = CvipOp.XVQ_Compression(inputImage, xform, scheme, compression_file, dtype, remap, keepdc);
                break;

            case LossySelection.XfrmCmpr:
                check1 = checkBoxQuanTable.Checked ? 1 : 0;
                check2 = checkBoxJPEGQTable.Checked ? 1 : 0;
                coding = (comboBoxCoding.Text == "Huffman") ? 2 : 1;

                if (rbRGB.Checked)
                    color_space = 0;
                else if (rbPCT.Checked)
                    color_space = 1;
                else
                    color_space = 2;

                if (comboBoxTransform.Text == "Wavelet(haar)")
                    xform = 1;
                else if (comboBoxTransform.Text == "Wavelet(daub4)")
                    xform = 2;
                else
                    xform = 0;

                codefile = dname + @"\quattable.txt";
                using (StreamWriter sw = File.CreateText(codefile))
                {
                    for (int i = 0; i < 30; i++)
                        sw.WriteLine(arrText[i].Text);
                }

                if ((comboBoxTransform.Text == "DCT") &&
                    (comboBoxBlocksize.Text == "8") &&
                    checkBoxJPEGQTable.Checked)
                    jpegquant = 1;
                else
                    jpegquant = 0;
                //'combobox1---blocksize ???
                outputImage = CvipOp.Transform_compression(inputImage, compression_file, codefile, color_space, xform, Convert.ToInt16(comboBoxBlocksize.Text), check1, jpegquant, coding, 0, 4, check2);
                break;
            }
            if (outputImage != 0)
            {
                // create a name for the new image
                string newImageName = viewer.Text + "_" + CvipFunctionNames.getFncName(currentSelection.ToString());
                newImageName += CvipConstant.imageNameCount++.ToString();
                MainForm.Viewers.Add(outputImage, newImageName, idx, compression_file);
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
        private void btnChrominance_Click(object sender, EventArgs e)
        {
            if (this.tableChrom == null)
            {
                this.tableChrom = new viewTable();
                this.tableChrom.Text = "JPEG Chrominance Table";
                this.tableChrom.Show();
            }
            this.tableChrom.BringToFront();
        }
        private void btnLuminance_Click(object sender, EventArgs e)
        {
            if (this.tableLumi == null)
            {
                this.tableLumi = new viewTable();
                this.tableLumi.Text = "JPEG Luminance Table";
                this.tableLumi.Show();
            }
            this.tableLumi.BringToFront();
        }
        private void btnOpenOrSave_Click(object sender, EventArgs e)
        {
            if (radioButton1.Checked || radioButton2.Checked)
            {
                // open codebook
                if (string.IsNullOrEmpty(dlgOpenCodebook.InitialDirectory))
                {
                    string home = MainForm.CVIPtoolsHOME;
                    if (!string.IsNullOrEmpty(home))
                    {
                        dlgOpenCodebook.InitialDirectory = home + @"bin\codebook";
                        dlgOpenCodebook.Title = "Open codebook";
                        dlgOpenCodebook.FileName = "";
                        dlgOpenCodebook.Filter = "All Files (*.*)|*.*";
                    }
                }
                if (dlgOpenCodebook.ShowDialog() == DialogResult.OK)
                {
                    vq_codebook = dlgOpenCodebook.FileName;
                    FileInfo imageinfo = new FileInfo(dlgOpenCodebook.FileName);
                    textBoxCodeName.Text = imageinfo.Name;
                }
            }
            else if (radioButton4.Checked)
            {
                // save codebook
                string home = MainForm.CVIPtoolsHOME;
                SaveFileDialog dlgSave = new SaveFileDialog();
                dlgSave.InitialDirectory = home + @"bin\codebook";
                dlgSave.FileName = textBoxCodeName.Text;
                dlgSave.Title = "Save Codebook";
                dlgSave.Filter = "All Files(*.*)|*.*";
                if (dlgSave.ShowDialog() == DialogResult.OK)
                {
                    if (File.Exists(dlgSave.FileName)) File.Delete(dlgSave.FileName);
                    vq_codebook = dlgSave.FileName;
                    FileInfo imageinfo = new FileInfo(dlgSave.FileName);
                    textBoxCodeName.Text = imageinfo.Name;
                }
            }
        }
        private void btnReset_Click(object sender, EventArgs e)
        {
            if (rbBTC.Checked)
                rbBTC_CheckedChanged(sender, e);
            else if (rbMBTC.Checked)
                rbMBTC_CheckedChanged(sender, e);
            else if (rbPMBTC.Checked)
                rbPMBTC_CheckedChanged(sender, e);
            else if (rbJPEG.Checked)
                rbJPEG_CheckedChanged(sender, e);
            else if (rbDynamicRLC.Checked)
                rbDynamicRLC_CheckedChanged(sender, e);
            else if (rbBitplaneRLC.Checked)
                rbBitplaneRLC_CheckedChanged(sender, e);
            else if (rbDPC.Checked)
                rbDPC_CheckedChanged(sender, e);
            else if (rbZonal.Checked)
                rbZonal_CheckedChanged(sender, e);
            else if (rbFractal.Checked)
                rbFractal_CheckedChanged(sender, e);
            else if (rbXVQ.Checked)
                rbXVQ_CheckedChanged(sender, e);
            else if (rbVectorQuan.Checked)
                rbVectorQuan_CheckedChanged(sender, e);
            else if (rbJPEG2000.Checked)
                rbJPEG2000_CheckedChanged(sender, e);
            else if (rbTransformCompression.Checked)
            {
                rbTransformCompression_CheckedChanged(sender, e);
                textBox2.Text = "16";
                textBox3.Text = "32";
                textBox4.Text = "32";
                textBox5.Text = "48";
                textBox6.Text = "48";
                textBox7.Text = "48";
                textBox8.Text = "64";
                textBox9.Text = "64";
                textBox10.Text = "64";
                textBox11.Text = "64";
                textBox12.Text = "32";
                textBox13.Text = "48";
                textBox14.Text = "48";
                textBox16.Text = "64";
                textBox15.Text = "64";
                textBox17.Text = "64";
                textBox18.Text = "128";
                textBox19.Text = "128";
                textBox20.Text = "128";
                textBox21.Text = "128";
                textBox22.Text = "32";
                textBox23.Text = "48";
                textBox24.Text = "48";
                textBox24.Text = "64";
                textBox26.Text = "64";
                textBox27.Text = "64";
                textBox28.Text = "128";
                textBox29.Text = "128";
                textBox30.Text = "128";
                textBox31.Text = "128";
            }
        }
        private void btnSaveCompressedData_Click(object sender, EventArgs e)
        {
            ViewerForm viewer = MainForm.Viewers.SelectedViewer;
            if (viewer == null)
            {
                MessageBox.Show("This operation must have an input image!",
                    "Input an image.", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                return;
            }
            if (rbTransformCompression.Checked)
            {
                MessageBox.Show("Saving Transform compressed image is currently unsupported.",
                    "Current unsupported format!", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                return;
            }
            // viewer.CompressionIndex = 0, then normal image
            // viewer.CompressionIndex > 0, then compressed image
            if (viewer.CompressionIndex <= 0)
            {
                MessageBox.Show("Unsupported format!", "Input an compressed image.",
                    MessageBoxButtons.OK, MessageBoxIcon.Warning);
                return;
            }
            SaveFileDialog dlgSave = new SaveFileDialog();
            dlgSave.InitialDirectory = MainForm.CVIPtoolsHOME + @"bin\compression";
            dlgSave.Title = "Save Compressed File";
            if (viewer.ImageFormat == imageFormat.JPG)
            {
                dlgSave.Filter = "JPEG Format (*.jpg)|*.jpg";
                dlgSave.FileName = viewer.Text + ".jpg";
            }
            else if (viewer.ImageFormat == imageFormat.JP2)
            {
                dlgSave.Filter = "JPEG2000 Format (*.jp2)|*.jp2";
                dlgSave.FileName = viewer.Text + ".jp2";
            }
            else
            {
                dlgSave.Filter = "CVIPtools VIP Format (*.vip)|*.vip";
                dlgSave.FileName = viewer.Text + ".vip";
            }
            if (dlgSave.ShowDialog() == DialogResult.OK)
            {
                if (File.Exists(dlgSave.FileName)) File.Delete(dlgSave.FileName);

                // fname is different from viewer.CompressedFileName
                // viewer.CompressedFileName is the temporary compressed image
                // it should be ended with  ".tmp__", such as ...".tmp__"
                // fname is the filename that is almost same as viewer.CompressedFileName
                // except without "__".  I do not know the actual reason.
                string dname = Environment.GetEnvironmentVariable("TEMP") + @"\compression\";
                string fname = dname + viewer.CompressionIndex.ToString() + ".tmp";
                CvipOp.Save_Compressed_Data(viewer.CVIPimage, fname);
                File.Copy(fname, dlgSave.FileName);
            }
        }
        private void checkBoxQuanTable_CheckedChanged(object sender, EventArgs e)
        {
            if (rbRGB.Checked)
                rbRGB_CheckedChanged(sender, e);
            else
                rbYCbCrPCT_CheckedChanged(sender, e);
        }
        private void comboBox1_Leave(object sender, EventArgs e)
        {
            try
            {
                Convert.ToDouble(comboBox1.Text);
            }
            catch
            {
                comboBox1.Text = "8";
                MessageBox.Show("Please check the input value. Only digit numbers are accepted.",
                    "Digit number input error", MessageBoxButtons.OK, MessageBoxIcon.Warning);
            }
        }
        private void comboBox3_Leave(object sender, EventArgs e)
        {
            if (rbZonal.Checked || rbFractal.Checked)
            {
                try
                {
                    Convert.ToDouble(comboBox3.Text);
                }
                catch
                {
                    if (rbZonal.Checked)
                        comboBox3.Text = "16";
                    else
                        comboBox3.Text = "10";
                    MessageBox.Show("Please check the input value. Only digit numbers are accepted.",
                        "Digit number input error", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                }
            }
        }
        private void comboBox4_Leave(object sender, EventArgs e)
        {
            if (rbFractal.Checked)
            {
                try
                {
                    Convert.ToDouble(comboBox4.Text);
                }
                catch
                {
                    comboBox4.Text = "3";
                    MessageBox.Show("Please check the input value. Only digit numbers are accepted.",
                        "Digit number input error", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                }
            }
        }
        private void comboBox5_Leave(object sender, EventArgs e)
        {
            if (rbDPC.Checked || rbZonal.Checked || rbFractal.Checked)
            {
                try
                {
                    Convert.ToDouble(comboBox5.Text);
                }
                catch
                {
                    if (rbDPC.Checked)
                        comboBox5.Text = "0.9";
                    else if (rbZonal.Checked)
                        comboBox5.Text = "2";
                    else
                        comboBox5.Text = "6";
                    MessageBox.Show("Please check the input value. Only digit numbers are accepted.",
                        "Digit number input error", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                }
            }
        }
        private void comboBox6_Leave(object sender, EventArgs e)
        {
            if (rbFractal.Checked)
            {
                try
                {
                    Convert.ToDouble(comboBox6.Text);
                }
                catch
                {
                    comboBox6.Text = "0";
                    MessageBox.Show("Please check the input value. Only digit numbers are accepted.",
                        "Digit number input error", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                }
            }
        }
        private void comboBox7_Leave(object sender, EventArgs e)
        {
            try
            {
                Convert.ToDouble(comboBox7.Text);
            }
            catch
            {
                comboBox7.Text = "4";
                MessageBox.Show("Please check the input value. Only digit numbers are accepted.",
                    "Digit number input error", MessageBoxButtons.OK, MessageBoxIcon.Warning);
            }
        }
        private void comboBox8_Leave(object sender, EventArgs e)
        {
            try
            {
                Convert.ToDouble(comboBox8.Text);
            }
            catch
            {
                comboBox8.Text = "10";
                MessageBox.Show("Please check the input value. Only digit numbers are accepted.",
                    "Digit number input error", MessageBoxButtons.OK, MessageBoxIcon.Warning);
            }
        }
        private void comboBoxBlocksize_Leave(object sender, EventArgs e)
        {
            try
            {
                Convert.ToDouble(comboBoxBlocksize.Text);
            }
            catch
            {
                comboBoxBlocksize.Text = "8";
                MessageBox.Show("Please check the input value. Only digit numbers are accepted.",
                    "Digit number input error", MessageBoxButtons.OK, MessageBoxIcon.Warning);
            }
        }
        private void comboBoxQuanTable_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (this.tableChrom != null)
                this.tableChrom.LoadJPEGQuantTable();
            if (this.tableLumi != null)
                this.tableLumi.LoadJPEGQuantTable();
        }
        protected override void OnLoad(EventArgs e)
        {
            base.OnLoad(e);
            currentSelection = LossySelection.BTC;

            groupBoxLossyPara1.Enabled = true;
            groupBoxLossyPara2.Enabled = false;
            groupBoxLossyPara3.Enabled = false;
            groupBoxLossyPara4.Enabled = false;
            groupBoxLossyPara5.Enabled = false;
            groupBoxLossyPara1.BringToFront();

            groupBoxLossyPara1.Visible = true;
            groupBoxLossyPara2.Visible = false;
            groupBoxLossyPara3.Visible = false;
            groupBoxLossyPara4.Visible = false;
            groupBoxLossyPara5.Visible = false;

            groupBoxLossyPara2.Location = new Point(0, 0);
            groupBoxLossyPara3.Location = new Point(0, 0);
            groupBoxLossyPara4.Location = new Point(0, 0);
            groupBoxLossyPara5.Location = new Point(0, 0);

            comboBoxQuanTable.Text = "Default";
            arrText = new TextBox[] {
                textBox2,  textBox3,  textBox4,  textBox5,  textBox6,  textBox7,  textBox8,  textBox9,  textBox10, textBox11,
                textBox12, textBox13, textBox14, textBox15, textBox16, textBox17, textBox18, textBox19, textBox20, textBox21,
                textBox22, textBox23, textBox24, textBox25, textBox26, textBox27, textBox28, textBox29, textBox30, textBox31};

            saveDefaultJPEGQuantTable();
        }
        public void rbBTC_CheckedChanged(object sender, EventArgs e)
        {
            if (rbBTC.Checked)
            {
                currentSelection = LossySelection.BTC;

                groupBoxLossyPara1.Enabled = true;
                groupBoxLossyPara2.Enabled = false;
                groupBoxLossyPara3.Enabled = false;
                groupBoxLossyPara4.Enabled = false;
                groupBoxLossyPara5.Enabled = false;
                groupBoxLossyPara1.BringToFront();

                groupBoxLossyPara1.Visible = true;
                groupBoxLossyPara2.Visible = false;
                groupBoxLossyPara3.Visible = false;
                groupBoxLossyPara4.Visible = false;
                groupBoxLossyPara5.Visible = false;

                label1.Text = "Block size";
                comboBox1.DataSource = new string[] { "3", "4", "8", "16", "32" };
                comboBox1.Text = "8";

                label2.Visible = false;
                comboBoxQuanTable.Visible = false;
                groupBox3.Visible = false;
                checkBoxSmooth.Visible = false;
                checkBoxGrayScale.Visible = false;
                btChrominance.Visible = false;
                btLuminance.Visible = false;
            }
        }
        private void rbMBTC_CheckedChanged(object sender, EventArgs e)
        {
            if (rbMBTC.Checked)
            {
                currentSelection = LossySelection.MBTC;

                groupBoxLossyPara1.Enabled = true;
                groupBoxLossyPara2.Enabled = false;
                groupBoxLossyPara3.Enabled = false;
                groupBoxLossyPara4.Enabled = false;
                groupBoxLossyPara5.Enabled = false;
                groupBoxLossyPara1.BringToFront();

                groupBoxLossyPara1.Visible = true;
                groupBoxLossyPara2.Visible = false;
                groupBoxLossyPara3.Visible = false;
                groupBoxLossyPara4.Visible = false;
                groupBoxLossyPara5.Visible = false;

                label1.Text = "Block size";
                comboBox1.DataSource = new string[] { "2", "4", "8", "16", "32" };
                comboBox1.Text = "8";

                label2.Visible = false;
                comboBoxQuanTable.Visible = false;
                groupBox3.Visible = false;
                checkBoxSmooth.Visible = false;
                checkBoxGrayScale.Visible = false;
                btChrominance.Visible = false;
                btLuminance.Visible = false;
            }
        }
        private void rbPMBTC_CheckedChanged(object sender, EventArgs e)
        {
            if (rbPMBTC.Checked)
            {
                currentSelection = LossySelection.PMBTC;

                groupBoxLossyPara1.Enabled = true;
                groupBoxLossyPara2.Enabled = false;
                groupBoxLossyPara3.Enabled = false;
                groupBoxLossyPara4.Enabled = false;
                groupBoxLossyPara5.Enabled = false;
                groupBoxLossyPara1.BringToFront();

                groupBoxLossyPara1.Visible = true;
                groupBoxLossyPara2.Visible = false;
                groupBoxLossyPara3.Visible = false;
                groupBoxLossyPara4.Visible = false;
                groupBoxLossyPara5.Visible = false;

                label1.Text = "Block size";
                comboBox1.DataSource = new string[] { "3", "4", "8", "16", "32" };
                comboBox1.Text = "8";

                label2.Visible = false;
                comboBoxQuanTable.Visible = false;
                groupBox3.Visible = false;
                checkBoxSmooth.Visible = false;
                checkBoxGrayScale.Visible = false;
                btChrominance.Visible = false;
                btLuminance.Visible = false;
            }
        }
        private void rbJPEG_CheckedChanged(object sender, EventArgs e)
        {
            if (rbJPEG.Checked)
            {
                currentSelection = LossySelection.JPEG;

                groupBoxLossyPara1.Enabled = true;
                groupBoxLossyPara2.Enabled = false;
                groupBoxLossyPara3.Enabled = false;
                groupBoxLossyPara4.Enabled = false;
                groupBoxLossyPara5.Enabled = false;
                groupBoxLossyPara1.BringToFront();

                groupBoxLossyPara1.Visible = true;
                groupBoxLossyPara2.Visible = false;
                groupBoxLossyPara3.Visible = false;
                groupBoxLossyPara4.Visible = false;
                groupBoxLossyPara5.Visible = false;

                label1.Text = "Quality";
                comboBox1.DataSource = new string[] { "10", "20", "30", "40", "50", "60", "70", "80", "90", "95" };
                comboBox1.Text = "70";

                label2.Visible = true;
                comboBoxQuanTable.Visible = true;
                groupBox3.Visible = false;
                checkBoxSmooth.Visible = true;
                checkBoxGrayScale.Visible = true;
                btChrominance.Visible = true;
                btLuminance.Visible = true;

                checkBoxSmooth.Checked = true;
                checkBoxGrayScale.Checked = false;
                comboBoxQuanTable.Text = "Default";
            }
        }
        private void rbDynamicRLC_CheckedChanged(object sender, EventArgs e)
        {
            if (rbDynamicRLC.Checked)
            {
                currentSelection = LossySelection.DyRLC;

                groupBoxLossyPara1.Enabled = true;
                groupBoxLossyPara2.Enabled = false;
                groupBoxLossyPara3.Enabled = false;
                groupBoxLossyPara4.Enabled = false;
                groupBoxLossyPara5.Enabled = false;
                groupBoxLossyPara1.BringToFront();

                groupBoxLossyPara1.Visible = true;
                groupBoxLossyPara2.Visible = false;
                groupBoxLossyPara3.Visible = false;
                groupBoxLossyPara4.Visible = false;
                groupBoxLossyPara5.Visible = false;

                label1.Text = "Window size";
                comboBox1.DataSource = new string[] { "2", "5", "10", "20", "50" };
                comboBox1.Text = "10";

                label2.Visible = false;
                comboBoxQuanTable.Visible = false;
                groupBox3.Visible = false;
                checkBoxSmooth.Visible = false;
                checkBoxGrayScale.Visible = false;
                btChrominance.Visible = false;
                btLuminance.Visible = false;
            }
        }
        private void rbBitplaneRLC_CheckedChanged(object sender, EventArgs e)
        {
            if (rbBitplaneRLC.Checked)
            {
                currentSelection = LossySelection.BitplaneRLC;

                groupBoxLossyPara1.Enabled = true;
                groupBoxLossyPara2.Enabled = false;
                groupBoxLossyPara3.Enabled = false;
                groupBoxLossyPara4.Enabled = false;
                groupBoxLossyPara5.Enabled = false;
                groupBoxLossyPara1.BringToFront();

                groupBoxLossyPara1.Visible = true;
                groupBoxLossyPara2.Visible = false;
                groupBoxLossyPara3.Visible = false;
                groupBoxLossyPara4.Visible = false;
                groupBoxLossyPara5.Visible = false;

                label1.Visible = false;
                comboBox1.Visible = false;
                label1.Text = "Block size";
                comboBox1.DataSource = new string[] { "3", "4", "8", "16", "32" };
                comboBox1.Text = "8";

                label2.Visible = false;
                comboBoxQuanTable.Visible = false;
                groupBox3.Visible = true;
                checkBoxSmooth.Visible = false;
                checkBoxGrayScale.Visible = false;
                btChrominance.Visible = false;
                btLuminance.Visible = false;

                checkBox8.Checked = true;
                checkBox9.Checked = true;
                checkBox10.Checked = true;
                checkBox11.Checked = true;
                checkBox12.Checked = true;
                checkBox13.Checked = false;
                checkBox14.Checked = false;
                checkBox15.Checked = false;
            }
            else
            {
                label1.Visible = true;
                comboBox1.Visible = true;
            }
        }
        private void rbDPC_CheckedChanged(object sender, EventArgs e)
        {
            if (rbDPC.Checked)
            {
                currentSelection = LossySelection.DPC;

                groupBoxLossyPara1.Enabled = true;
                groupBoxLossyPara2.Enabled = true;
                groupBoxLossyPara3.Enabled = false;
                groupBoxLossyPara4.Enabled = false;
                groupBoxLossyPara5.Enabled = false;
                groupBoxLossyPara2.BringToFront();

                groupBoxLossyPara1.Visible = true;
                groupBoxLossyPara2.Visible = true;
                groupBoxLossyPara3.Visible = false;
                groupBoxLossyPara4.Visible = false;
                groupBoxLossyPara5.Visible = false;

                label3.Text = "Predictor";
                label4.Text = "Quantizer";
                label5.Text = "Correlation";
                label6.Text = "Scan direction";
                label7.Visible = true;
                label7.Text = "Number of bits";
                label8.Visible = true;
                label8.Text = "Std. dev";

                string[] items = new string[] { "Original Value", "Reconstructed Value" };
                comboBox3.Items.Clear();
                comboBox3.DropDownStyle = ComboBoxStyle.DropDownList;
                comboBox3.DrawMode = DrawMode.Normal;
                comboBox3.Items.AddRange(items);
                comboBox3.SelectedIndex = 1;

                items = new string[] { "Lloyd-Max Quant", "Truncation (clip)" };
                comboBox4.Items.Clear();
                comboBox4.DropDownStyle = ComboBoxStyle.DropDownList;
                comboBox4.DrawMode = DrawMode.Normal;
                comboBox4.Items.AddRange(items);
                comboBox4.SelectedIndex = 0;

                items = new string[] { "0.75", "0.8", "0.85","0.9", "0.95", "0.98" };
                comboBox5.Items.Clear();
                comboBox5.DropDownStyle = ComboBoxStyle.DropDown;
                comboBox5.DrawMode = DrawMode.Normal;
                comboBox5.Items.AddRange(items);
                comboBox5.SelectedIndex = 0;
                comboBox5.Text = "0.9";

                items = new string[] { "horizontal", "vertical" };
                comboBox6.Items.Clear();
                comboBox6.DropDownStyle = ComboBoxStyle.DropDownList;
                comboBox6.DrawMode = DrawMode.Normal;
                comboBox6.Items.AddRange(items);
                comboBox6.SelectedIndex = 0;

                comboBox7.Visible = true;
                items = new string[] { "1", "2", "3", "4", "5", "6", "7" };
                comboBox7.DataSource = items;
                comboBox7.Text = "4";

                comboBox8.Visible = true;
                items = new string[] { "5","10", "20", "30", "40", "50" };
                comboBox8.DataSource = items;
                comboBox8.Text = "10";
                checkBox16.Visible = false;
            }
        }
        private void rbZonal_CheckedChanged(object sender, EventArgs e)
        {
            if (rbZonal.Checked)
            {
                currentSelection = LossySelection.Zonal;

                groupBoxLossyPara1.Enabled = true;
                groupBoxLossyPara2.Enabled = true;
                groupBoxLossyPara3.Enabled = false;
                groupBoxLossyPara4.Enabled = false;
                groupBoxLossyPara5.Enabled = false;
                groupBoxLossyPara2.BringToFront();

                groupBoxLossyPara1.Visible = true;
                groupBoxLossyPara2.Visible = true;
                groupBoxLossyPara3.Visible = false;
                groupBoxLossyPara4.Visible = false;
                groupBoxLossyPara5.Visible = false;

                label3.Text = "Block size";
                label4.Text = "Transform";
                if(this.Height>430)
               label5.Location = new Point(36, 84);
                else
                    label5.Location = new Point(26, 77);
                label5.Text = "Apprx. Compress Ratio \n";
                label5.Text += "(Block size dependent)";
                label6.Text = "Mask shape";
                label7.Visible = false;
                label8.Visible = false;

                string[] items = new string[] { "8", "16", "32", "64", "128", "256", "512" };
                comboBox3.Items.Clear();
                comboBox3.DropDownStyle = ComboBoxStyle.DropDownList;
                comboBox3.DrawMode = DrawMode.Normal;
                comboBox3.Items.AddRange(items);
                comboBox3.SelectedIndex = 1;

                items = new string[] { "FFT", "DCT", "Walsh", "Hadamard" };
                comboBox4.Items.Clear();
                comboBox4.DropDownStyle = ComboBoxStyle.DropDownList;
                comboBox4.DrawMode = DrawMode.Normal;
                comboBox4.Items.AddRange(items);
                comboBox4.SelectedIndex = 1;

                items = new string[] { "2", "2.5", "3", "3.5", "4", "4.5", "5" };
                comboBox5.Items.Clear();
                comboBox5.DropDownStyle = ComboBoxStyle.DropDown;
                comboBox5.DrawMode = DrawMode.Normal;
                comboBox5.Items.AddRange(items);
                comboBox5.SelectedIndex = 0;

                items = new string[] { "Triangle", "Square", "Circle" };
                comboBox6.Items.Clear();
                comboBox6.DropDownStyle = ComboBoxStyle.DropDownList;
                comboBox6.DrawMode = DrawMode.Normal;
                comboBox6.Items.AddRange(items);
                comboBox6.SelectedIndex = 0;

                comboBox7.Visible = false;
                comboBox8.Visible = false;

                checkBox16.Visible = true;
                checkBox16.Text = "DC Quantization";
                checkBox16.Checked = false;
            }
            else
            {
                if (this.Height > 430)
                    label5.Location = new Point(36, 94);
                else
               label5.Location = new Point(26, 77);
            }
        }
        private void rbFractal_CheckedChanged(object sender, EventArgs e)
        {
            if (rbFractal.Checked)
            {
                currentSelection = LossySelection.Fractal;

                groupBoxLossyPara1.Enabled = true;
                groupBoxLossyPara2.Enabled = true;
                groupBoxLossyPara3.Enabled = false;
                groupBoxLossyPara4.Enabled = false;
                groupBoxLossyPara5.Enabled = false;
                groupBoxLossyPara2.BringToFront();

                groupBoxLossyPara1.Visible = true;
                groupBoxLossyPara2.Visible = true;
                groupBoxLossyPara3.Visible = false;
                groupBoxLossyPara4.Visible = false;
                groupBoxLossyPara5.Visible = false;

                label3.Text = "Tolerance";
                label4.Text = "Recursion size min.";
                label5.Text = "Recursion size max.";
                label6.Text = "Domain pool type";
                label7.Visible = false;
                label8.Visible = false;

                string[] items = new string[] { "4", "8", "10", "12", "32", "64", "128", "256" };
                comboBox3.Items.Clear();
                comboBox3.DropDownStyle = ComboBoxStyle.DropDown;
                comboBox3.DrawMode = DrawMode.Normal;
                comboBox3.Items.AddRange(items);
                comboBox3.SelectedIndex = 2;

                items = new string[] { "2", "3", "4", "5", "6" };
                comboBox4.Items.Clear();
                comboBox4.DropDownStyle = ComboBoxStyle.DropDown;
                comboBox4.DrawMode = DrawMode.Normal;
                comboBox4.Items.AddRange(items);
                comboBox4.SelectedIndex = 1;

                items = new string[] { "3", "4", "5", "6", "7", "8" };
                comboBox5.Items.Clear();
                comboBox5.DropDownStyle = ComboBoxStyle.DropDown;
                comboBox5.DrawMode = DrawMode.Normal;
                comboBox5.Items.AddRange(items);
                comboBox5.SelectedIndex = 3;

                items = new string[] { "0", "1", "2" };
                comboBox6.Items.Clear();
                comboBox6.DropDownStyle = ComboBoxStyle.DropDown;
                comboBox6.DrawMode = DrawMode.Normal;
                comboBox6.Items.AddRange(items);
                comboBox6.SelectedIndex = 0;

                comboBox7.Visible = false;
                comboBox8.Visible = false;

                checkBox16.Visible = true;
                checkBox16.Text = "Slower encoding";
                checkBox16.Checked = false;
            }
        }
        private void rbXVQ_CheckedChanged(object sender, EventArgs e)
        {
            if (rbXVQ.Checked)
            {
                currentSelection = LossySelection.XVQ;

                groupBoxLossyPara1.Enabled = true;
                groupBoxLossyPara2.Enabled = true;
                groupBoxLossyPara3.Enabled = false;
                groupBoxLossyPara4.Enabled = false;
                groupBoxLossyPara5.Enabled = false;
                groupBoxLossyPara2.BringToFront();

                groupBoxLossyPara1.Visible = true;
                groupBoxLossyPara2.Visible = true;
                groupBoxLossyPara3.Visible = false;
                groupBoxLossyPara4.Visible = false;
                groupBoxLossyPara5.Visible = false;

                label3.Text = "Compression Algorithm";
                label4.Text = "Transform";
                label5.Text = "Data Type";
                label6.Text = "Remap Type";
                label7.Visible = false;
                label8.Visible = false;

                string[] items = new string[] { "VQ1", "VQ2", "VQ3", "VQ4" };
                comboBox3.Items.Clear();
                comboBox3.DropDownStyle = ComboBoxStyle.DropDownList;
                comboBox3.DrawMode = DrawMode.Normal;
                comboBox3.Items.AddRange(items);
                comboBox3.SelectedIndex = 0;

                items = new string[] { "DCT", "PCT_DCT", "WAVELET", "PCT_WAVELET" };
                comboBox4.Items.Clear();
                comboBox4.DropDownStyle = ComboBoxStyle.DropDownList;
                comboBox4.DrawMode = DrawMode.Normal;
                comboBox4.Items.AddRange(items);
                comboBox4.SelectedIndex = 0;

                items = new string[] { "FLOAT", "BYTE", "SHORT" };
                comboBox5.Items.Clear();
                comboBox5.DropDownStyle = ComboBoxStyle.DropDownList;
                comboBox5.DrawMode = DrawMode.Normal;
                comboBox5.Items.AddRange(items);
                comboBox5.SelectedIndex = 1;

                items = new string[] { "LINEAR", "LOG" };
                comboBox6.Items.Clear();
                comboBox6.DropDownStyle = ComboBoxStyle.DropDownList;
                comboBox6.DrawMode = DrawMode.Normal;
                comboBox6.Items.AddRange(items);
                comboBox6.SelectedIndex = 0;

                comboBox7.Visible = false;
                comboBox8.Visible = false;

                checkBox16.Visible = true;
                checkBox16.Text = "DC Quantization";
                checkBox16.Checked = false;
            }
        }
        private void rbVectorQuan_CheckedChanged(object sender, EventArgs e)
        {
            if (rbVectorQuan.Checked)
            {
                currentSelection = LossySelection.VQ;

                groupBoxLossyPara1.Enabled = true;
                groupBoxLossyPara2.Enabled = true;
                groupBoxLossyPara3.Enabled = true;
                groupBoxLossyPara4.Enabled = false;
                groupBoxLossyPara5.Enabled = false;
                groupBoxLossyPara3.BringToFront();

                groupBoxLossyPara1.Visible = true;
                groupBoxLossyPara2.Visible = true;
                groupBoxLossyPara3.Visible = true;
                groupBoxLossyPara4.Visible = false;
                groupBoxLossyPara5.Visible = false;

                string[] items = new string[] { "2", "3", "4", "5", "6", "7", "8", "9" };
                comboBoxHeight.DataSource = items;
                comboBoxHeight.Text = "4";

                items = new string[] { "2", "3", "4", "5", "6", "7", "8", "9" };
                comboBoxWidth.DataSource = items;
                comboBoxWidth.Text = "4";

                items = new string[] { "32", "64", "128", "256", "512" };
                comboBoxSize.DataSource = items;
                comboBoxSize.Text = "128";

                items = new string[] { "5", "10", "15", "20", "25" };
                comboBoxErrorThresh.DataSource = items;
                comboBoxErrorThresh.Text = "20";

                radioButton3.Checked = true;
            }
        }
        private void rbTransformCompression_CheckedChanged(object sender, EventArgs e)
        {
            if (rbTransformCompression.Checked)
            {
                currentSelection = LossySelection.XfrmCmpr;

                groupBoxLossyPara1.Enabled = true;
                groupBoxLossyPara2.Enabled = true;
                groupBoxLossyPara3.Enabled = true;
                groupBoxLossyPara4.Enabled = true;
                groupBoxLossyPara5.Enabled = false;
                groupBoxLossyPara4.BringToFront();

                groupBoxLossyPara1.Visible = true;
                groupBoxLossyPara2.Visible = true;
                groupBoxLossyPara3.Visible = true;
                groupBoxLossyPara4.Visible = true;
                groupBoxLossyPara5.Visible = false;

                string[] items = new string[] { "DCT", "Wavelet(haar)", "Wavelet(daub4)" };
                comboBoxTransform.Items.Clear();
                comboBoxTransform.DropDownStyle = ComboBoxStyle.DropDownList;
                comboBoxTransform.DrawMode = DrawMode.Normal;
                comboBoxTransform.Items.AddRange(items);
                comboBoxTransform.SelectedIndex = 0;

                items = new string[] { "8", "16", "32", "64", "128", "256", "512" };
                comboBoxBlocksize.Items.Clear();
                comboBoxBlocksize.DropDownStyle = ComboBoxStyle.DropDownList;
                comboBoxBlocksize.DrawMode = DrawMode.Normal;
                comboBoxBlocksize.Items.AddRange(items);
                comboBoxBlocksize.SelectedIndex = 0;

                items = new string[] { "Huffman" };
                comboBoxCoding.Items.Clear();
                comboBoxCoding.DropDownStyle = ComboBoxStyle.DropDownList;
                comboBoxCoding.DrawMode = DrawMode.Normal;
                comboBoxCoding.Items.AddRange(items);
                comboBoxCoding.SelectedIndex = 0;

                comboBoxDatatype.Visible = false;
                items = new string[] { "FLOAT", "BYTE", "SHORT" };
                comboBoxDatatype.Items.Clear();
                comboBoxDatatype.DropDownStyle = ComboBoxStyle.DropDownList;
                comboBoxDatatype.DrawMode = DrawMode.Normal;
                comboBoxDatatype.Items.AddRange(items);
                comboBoxDatatype.SelectedIndex = 1;

                comboBoxRemapType.Visible = false;
                items = new string[] { "LINEAR", "LOG" };
                comboBoxRemapType.Items.Clear();
                comboBoxRemapType.DropDownStyle = ComboBoxStyle.DropDownList;
                comboBoxRemapType.DrawMode = DrawMode.Normal;
                comboBoxRemapType.Items.AddRange(items);
                comboBoxRemapType.SelectedIndex = 0;

                rbRGB.Checked = true;
                checkBoxQuanTable.Checked = false;
                checkBoxJPEGQTable.Checked = false;
            }
        }
        private void rbRGB_CheckedChanged(object sender, EventArgs e)
        {
            label17.Visible = false;
            label18.Visible = false;
            for (int i = 0; i < 10; i++)
            {
                arrText[i].ReadOnly = !checkBoxQuanTable.Checked;
                arrText[i].Visible = true;
            }
            for (int i = 10; i < 30; i++)
                arrText[i].Visible = false;
        }
        private void rbYCbCrPCT_CheckedChanged(object sender, EventArgs e)
        {
            label17.Visible = true;
            label18.Visible = false;
            for (int i = 0; i < 30; i++)
            {
                arrText[i].ReadOnly = !checkBoxQuanTable.Checked;
                arrText[i].Visible = true;
            }
        }
        private void radioButton1_CheckedChanged(object sender, EventArgs e)
        {
            label14.Visible = true;
            label10.Visible = false;
            label11.Visible = false;
            label12.Visible = false;
            label13.Visible = false;
            label19.Visible = false;
            comboBoxHeight.Visible = false;
            comboBoxWidth.Visible = false;
            comboBoxSize.Visible = false;
            comboBoxErrorThresh.Visible = false;

            label9.Visible = true;
            textBoxCodeName.Visible = true;
            buttonOpenOrSave.Visible = true;
            buttonOpenOrSave.Text = "Open";
        }
        private void radioButton2_CheckedChanged(object sender, EventArgs e)
        {
            label14.Visible = true;
            label10.Visible = false;
            label11.Visible = false;
            label12.Visible = false;
            label13.Visible = false;
            label19.Visible = false;
            comboBoxHeight.Visible = false;
            comboBoxWidth.Visible = false;
            comboBoxSize.Visible = false;
            comboBoxErrorThresh.Visible = false;

            label9.Visible = true;
            textBoxCodeName.Visible = true;
            buttonOpenOrSave.Visible = true;
            buttonOpenOrSave.Text = "Open";
        }
        private void radioButton3_CheckedChanged(object sender, EventArgs e)
        {
            label14.Visible = false;
            label10.Visible = true;
            label11.Visible = true;
            label12.Visible = true;
            label13.Visible = true;
            label19.Visible = true;
            comboBoxHeight.Visible = true;
            comboBoxWidth.Visible = true;
            comboBoxSize.Visible = true;
            comboBoxErrorThresh.Visible = true;

            label9.Visible = false;
            textBoxCodeName.Visible = false;
            buttonOpenOrSave.Visible = false;
            buttonOpenOrSave.Text = "Open";
        }
        private void radioButton4_CheckedChanged(object sender, EventArgs e)
        {
            label14.Visible = false;
            label10.Visible = true;
            label11.Visible = true;
            label12.Visible = true;
            label13.Visible = true;
            label19.Visible = true;
            comboBoxHeight.Visible = true;
            comboBoxWidth.Visible = true;
            comboBoxSize.Visible = true;
            comboBoxErrorThresh.Visible = true;

            label9.Visible = true;
            textBoxCodeName.Visible = true;
            buttonOpenOrSave.Visible = true;
            buttonOpenOrSave.Text = "Save as...";
        }
        public void saveDefaultJPEGQuantTable()
        {
            string fname = Environment.GetEnvironmentVariable("TEMP") + @"\quant1.txt";
            if (File.Exists(fname)) File.Delete(fname);
            using (StreamWriter sw = File.CreateText(fname))
            {
                for (int i = 0; i < 64; i++) sw.Write(tableLuminanceDefault[i] + " ");
                sw.WriteLine("\n");
                for (int i = 0; i < 64; i++) sw.Write(tableChrominanceDefault[i] + " ");
            }
        }
        private void rbRatio_CheckedChanged(object sender, EventArgs e)
        {
            if (rbRatio.Checked)
            {
                cbRatio.Enabled = true;
                cbQuality.Enabled = false;
            }
        }
        private void rbQuality_CheckedChanged(object sender, EventArgs e)
        {
            if (rbQuality.Checked)
            {
                cbQuality.Enabled = true;
                cbRatio.Enabled = false;
            }
        }
        private void rbJPEG2000_CheckedChanged(object sender, EventArgs e)
        {
            if (rbJPEG2000.Checked)
            {
                currentSelection = LossySelection.JPEG2_;

                groupBoxLossyPara1.Enabled = true;
                groupBoxLossyPara2.Enabled = true;
                groupBoxLossyPara3.Enabled = true;
                groupBoxLossyPara4.Enabled = true;
                groupBoxLossyPara5.Enabled = true;
                groupBoxLossyPara5.BringToFront();

                groupBoxLossyPara1.Visible = true;
                groupBoxLossyPara2.Visible = true;
                groupBoxLossyPara3.Visible = true;
                groupBoxLossyPara4.Visible = true;
                groupBoxLossyPara5.Visible = true;

                if (rbRatio.Checked)
                    cbQuality.Enabled = false;

                lblCodeBlockSize.Visible = true;
                cbCodeBlockSize.Visible = true;
                cbCodeBlockSize.Enabled = true;

                string[] items = new string[] { "5", "10", "15", "20", "30", "40", "50", "100" };
                cbRatio.Items.Clear();
                //         comboBox3.DropDownStyle = ComboBoxStyle.DropDownList;
                //         comboBox3.DrawMode = DrawMode.Normal;
                cbRatio.Items.AddRange(items);
                cbRatio.SelectedIndex = 0;

                items = new string[] { "70", "60", "50", "40", "30", "20", "10", "5" };
                cbQuality.Items.Clear();
                //        comboBox4.DropDownStyle = ComboBoxStyle.DropDownList;
                //        comboBox4.DrawMode = DrawMode.Normal;
                cbQuality.Items.AddRange(items);
                cbQuality.SelectedIndex = 0;

                items = new string[] { "1", "2", "3", "4", "5", "6" };
                cbNumResolution.Items.Clear();
                cbNumResolution.DropDownStyle = ComboBoxStyle.DropDownList;
                cbNumResolution.DrawMode = DrawMode.Normal;
                cbNumResolution.Items.AddRange(items);
                cbNumResolution.Text = "1";

                items = new string[] { "8", "16", "32", "64" };
                cbCodeBlockSize.Items.Clear();
                cbCodeBlockSize.DropDownStyle = ComboBoxStyle.DropDownList;
                cbCodeBlockSize.DrawMode = DrawMode.Normal;
                cbCodeBlockSize.Items.AddRange(items);
                cbCodeBlockSize.Text = "64";
            }
        }

        private void groupBoxLossyPara3_Enter(object sender, EventArgs e)
        {

        }
    }
}
