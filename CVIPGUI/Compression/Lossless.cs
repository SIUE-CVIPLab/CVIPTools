/*''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' ======================================================================
' Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
' ======================================================================
'
'             File Name: Lossless.cs
'           Description: Contains the controls and code
'                        for Compression->Lossless page
'         Related Files: CvipOp.cs
'                        CvipConstant.cs
'   Initial Coding Date: September 2007
'              Modified: May 2010
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
    enum LosslessSelection
    {
        Huffman,
        ZivLempel,
        DPC,
        Bitplane,
        JPEG2_
    }

    public partial class Lossless : UserControl
    {
        private LosslessSelection currentSelection;

        public Lossless()
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
            string fname, dname = Environment.GetEnvironmentVariable("TEMP") + @"\compression";
            if (!Directory.Exists(dname)) Directory.CreateDirectory(dname);

            int idx = 1;
            for (idx = 1; true; idx++)
            {
                fname = dname + @"\" + idx.ToString() + ".tmp__";
                if (!File.Exists(fname)) break;
            }
            // disable Apply button
            this.btnApply.Enabled = false;
            this.Cursor = Cursors.WaitCursor;

            // get the image that will be operated on
            int inputImage = viewer.CVIPimage, outputImage = 0;

            switch (this.currentSelection)
            {
            case LosslessSelection.Huffman:
                outputImage = CvipOp.Huffman_Compression_Image(inputImage, fname);
                break;

            case LosslessSelection.ZivLempel:
                outputImage = CvipOp.ZVL_Compression_Image(inputImage, fname);
                break;

            case LosslessSelection.DPC:
                if (Convert.ToInt16(Convert.ToDouble(comboBox3.Text)) < 3)
                {
                    MessageBox.Show("The number of bits should be greater than 2!", "Input error!",
                        MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    break;
                }
                outputImage = CvipOp.DPC_Compression_Image(inputImage, fname, Convert.ToSingle(comboBox1.Text), Convert.ToInt16(Convert.ToDouble(comboBox3.Text)) - 1, 0, Convert.ToInt16(comboBox2.SelectedIndex), 1, 1);
                break;

            case LosslessSelection.Bitplane:
                outputImage = CvipOp.BRLC_Compression_Image(inputImage, fname, 255);
                break;

            case LosslessSelection.JPEG2_:
                //inputImage, Quality, grayscale, optimize, smooth
                //default optimized is 1 since tcl does set that parameters
                int rate = 1;
                int quality = -1;
                int blocksize = 64;
                outputImage = CvipOp.JPEG2000_Compression_Image(inputImage, fname, rate, quality, Convert.ToInt16(comboBox3.Text), blocksize);
                break;
            }
            if (outputImage != 0)
            {
                // create a name for the new image
                string newImageName = viewer.Text + "_" + CvipFunctionNames.getFncName(currentSelection.ToString());
                newImageName += CvipConstant.imageNameCount++.ToString();
                MainForm.Viewers.Add(outputImage, newImageName, idx, fname);
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
        private void btnReset_Click(object sender, EventArgs e)
        {
            ResetControls();
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
            // viewer.CompressionIndex = 0, then normal image
            // viewer.CompressionIndex > 0, then compressed image
            if (viewer.CompressionIndex <= 0)
            {
                MessageBox.Show("Unsupported format!", "Input compressed image.",
                    MessageBoxButtons.OK, MessageBoxIcon.Warning);
                return;
            }
            SaveFileDialog dlgSave = new SaveFileDialog();
            dlgSave.InitialDirectory = MainForm.CVIPtoolsHOME + @"bin\compression";
            dlgSave.Title = "Save Compressed File";

            //jpeg is not supported at the moment
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
                string tmp = Environment.GetEnvironmentVariable("TEMP") + @"\compression\";
                string fname = tmp + viewer.CompressionIndex.ToString() + ".tmp";
                if (viewer.ImageFormat == imageFormat.JPG)
                {
                    CvipOp.Save_Compressed_Data(viewer.CVIPimage, fname);
                    File.Copy(viewer.CompressedFileName, dlgSave.FileName);
                }
                else if (viewer.ImageFormat == imageFormat.JP2)
                {
                    CvipOp.Save_Compressed_Data(viewer.CVIPimage, fname);
                    File.Copy(fname, dlgSave.FileName);
                }
                else
                {
                    CvipOp.Save_Compressed_Data(viewer.CVIPimage, fname);
                    File.Copy(fname, dlgSave.FileName);
                }
            }
        }
        private void comboBox1_Leave(object sender, EventArgs e)
        {
            try
            {
                Convert.ToDouble(comboBox1.Text);
            }
            catch
            {
                comboBox1.Text = "0.9";
                MessageBox.Show("Please check the input value. Only digit numbers are accepted.",
                   "Digit number input error", MessageBoxButtons.OK, MessageBoxIcon.Warning);
            }
        }
        private void comboBox3_Leave(object sender, EventArgs e)
        {
            try
            {
                Convert.ToDouble(comboBox3.Text);
            }
            catch
            {
                comboBox3.Text = "5";
                MessageBox.Show("Please check the input value. Only digit numbers are accepted.",
                   "Digit number input error", MessageBoxButtons.OK, MessageBoxIcon.Warning);
            }
        }
        protected override void OnLoad(EventArgs e)
        {
            base.OnLoad(e);

            this.rbHuffman.Tag = LosslessSelection.Huffman;
            this.rbZivLempel.Tag = LosslessSelection.ZivLempel;
            this.rbDPC.Tag = LosslessSelection.DPC;
            this.rbBitplaneRLC.Tag = LosslessSelection.Bitplane;
            this.rbJPEG2000.Tag = LosslessSelection.JPEG2_;

            ResetControls();
        }
        private void rbLossless_Click(object sender, EventArgs e)
        {
            RadioButton rb = sender as RadioButton;
            if ((rb != null) && rb.Checked && (rb.Tag != null))
                this.currentSelection = (LosslessSelection)rb.Tag;
            UpdateControls();
        }
        private void ResetControls()
        {
            label1.Text = "Correlation";
            comboBox1.DataSource = new string[] { "0.75", "0.8", "0.85", "0.9", "0.95", "0.98" };
            comboBox1.Text = "0.9";

            label2.Text = "Scan Direction";
            comboBox2.Items.Clear();
            comboBox2.DropDownStyle = ComboBoxStyle.DropDownList;
            comboBox2.DrawMode = DrawMode.Normal;
            comboBox2.Items.AddRange(new string[] { "Horizontal", "Vertical" });
            comboBox2.SelectedIndex = 0;

            label3.Text = "Number of Bits";
            comboBox3.DataSource = new string[] { "3", "4", "5", "6", "7" };
            comboBox3.Text = "5";

            // Default current selection
            this.rbHuffman.PerformClick();

            // enable Apply button
            this.btnApply.Enabled = true;
            this.Cursor = Cursors.Default;
        }
        private void UpdateControls()
        {
            switch (this.currentSelection)
            {
            case LosslessSelection.Huffman:
            case LosslessSelection.ZivLempel:
            case LosslessSelection.Bitplane:
            case LosslessSelection.JPEG2_:
                label1.Visible = false;
                comboBox1.Visible = false;
                label2.Visible = false;
                comboBox2.Visible = false;
                label3.Visible = false;
                comboBox3.Visible = false;
                label4.Visible = false;
                comboBox4.Visible = false;
                break;

            case LosslessSelection.DPC:
                label1.Visible = true;
                comboBox1.Visible = true;
                label2.Visible = true;
                comboBox2.Visible = true;
                label3.Visible = true;
                comboBox3.Visible = true;
                label4.Visible = false;
                comboBox4.Visible = false;
                break;

            //case LosslessSelection.JPEG2_:
            //    label1.Text = "Ratio";
            //    label1.Visible = false;
            //    comboBox1.DataSource = new string[] { "5", "10", "15", "20", "50" };
            //    comboBox1.Text = "1";
            //    comboBox1.Visible = false;

            //    label2.Text = "Quality";
            //    label2.Visible = false;
            //    comboBox2.Items.Clear();
            //    // comboBox2.DropDownStyle = ComboBoxStyle.DropDownList;
            //    // comboBox2.DrawMode = DrawMode.Normal;
            //    comboBox2.Items.AddRange(new string[] { "50", "40", "30", "20", "10" });
            //    comboBox2.SelectedIndex = 0;
            //    comboBox2.Visible = false;

            //    label3.Text = "Number of Resolutions";
            //    label3.Visible = false;
            //    comboBox3.DataSource = new string[] { "1", "2", "3", "4", "5", "6" };
            //    comboBox3.Text = "1";
            //    comboBox3.Visible = false;

            //    label4.Visible = false;
            //    comboBox4.Items.Clear();
            //    comboBox4.DropDownStyle = ComboBoxStyle.DropDownList;
            //    comboBox4.DrawMode = DrawMode.Normal;
            //    comboBox4.Items.AddRange(new string[] { "8", "16", "32", "64", "128" });
            //    comboBox4.Text = "64";
            //    comboBox4.Visible = false;
            //    break;
            }
            // enable Apply button
            this.btnApply.Enabled = true;
            this.Cursor = Cursors.Default;
        }
    }
}
