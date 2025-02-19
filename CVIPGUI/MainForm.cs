/*''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' ======================================================================
' Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
' ======================================================================
'
'             File Name: MainForm.cs
'           Description: Contains controls and code
'                        for MainForm class
'         Related Files: ViewerForm.cs
'                        ImageQueue.cs
'                        InfoPanel.cs
'                        AnlysisForm.cs
'                        EnhancementForm.cs
'                        RestorationForm.cs
'                        CompressionForm.cs
'                        UtilitiesForm.cs
'                        CvipOp.cs
'                        CvipConstant.cs
'   Initial Coding Date: February 2007
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

using Microsoft.Win32;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Drawing.Printing;
using System.IO;
using System.Text;
using System.Windows.Forms;

namespace CVIPGUI
{
    public partial class MainForm : Form
    {
        static private MainForm frmMain = null;

        static private AnalysisForm frmAnalysis = null;
        static private CompressionForm frmCompression = null;
        static private CustomRemapForm frmCustomRemap = null;
        static private EnhancementForm frmEnhancement = null;
        static private LaunchCameraForm frmLaunchCamera = null;
        static private RestorationForm frmRestoration = null;
        static private UtilitiesForm frmUtilities = null;
        string TempOpenPath;

        public MainForm()
        {
            MainForm.frmMain = this;
            InitializeComponent();
            TempOpenPath = MainForm.CVIPtoolsHOME + @"images";

        }
        private void mnuAnalysis_Click(object sender, EventArgs e)
        {
            if (MainForm.frmAnalysis == null)
            {
                MainForm.frmAnalysis = new AnalysisForm();
                MainForm.frmAnalysis.Show();
            }
            int tab = int.Parse((sender as ToolStripMenuItem).Tag.ToString());
            MainForm.frmAnalysis.tabAnalysis.SelectTab(tab);
            MainForm.frmAnalysis.BringToFront();
        }
        private void mnuCompression_Click(object sender, EventArgs e)
        {
            if (MainForm.frmCompression == null)
            {
                MainForm.frmCompression = new CompressionForm();
                MainForm.frmCompression.Show();
            }
            int tab = int.Parse((sender as ToolStripMenuItem).Tag.ToString());
            MainForm.frmCompression.tabCompression.SelectTab(tab);
            MainForm.frmCompression.BringToFront();
        }
        private void mnuEnhancement_Click(object sender, EventArgs e)
        {
            if (MainForm.frmEnhancement == null)
            {
                MainForm.frmEnhancement = new EnhancementForm();
                MainForm.frmEnhancement.Show();
            }
            int tab = int.Parse((sender as ToolStripMenuItem).Tag.ToString());
            MainForm.frmEnhancement.tabEnhancement.SelectTab(tab);
            MainForm.frmEnhancement.BringToFront();
        }
        private void mnuRestoration_Click(object sender, EventArgs e)
        {
            if (MainForm.frmRestoration == null)
            {
                MainForm.frmRestoration = new RestorationForm();
                MainForm.frmRestoration.Show();
            }
            int tab = int.Parse((sender as ToolStripMenuItem).Tag.ToString());
            MainForm.frmRestoration.tabRestoration.SelectTab(tab);
            MainForm.frmRestoration.BringToFront();
        }
        private void mnuShowUtilities_Click(object sender, EventArgs e)
        {
            this.mnuUtilArithLogic.Visible = this.mnuShowUtilities.Checked;
            this.mnuUtilCompare.Visible = this.mnuShowUtilities.Checked;
            this.mnuUtilConvert.Visible = this.mnuShowUtilities.Checked;
            this.mnuUtilCreate.Visible = this.mnuShowUtilities.Checked;
            this.mnuUtilEnhance.Visible = this.mnuShowUtilities.Checked;
            this.mnuUtilFilter.Visible = this.mnuShowUtilities.Checked;
            this.mnuUtilSize.Visible = this.mnuShowUtilities.Checked;
            this.mnuUtilStats.Visible = this.mnuShowUtilities.Checked;
            this.mnuShowUtilities.BackColor = this.mnuShowUtilities.Checked
                ? System.Drawing.SystemColors.Info
                : System.Drawing.SystemColors.Control;
        }
        private void mnuUtilities_Click(object sender, EventArgs e)
        {
            ToolStripMenuItem itm = sender as ToolStripMenuItem;
            string op = itm.Text;
            if (op == "Fast Double Size")
            {
                ViewerForm viewer = MainForm.Viewers.SelectedViewer;
                if (viewer == null)
                {
                    MessageBox.Show("Please give an input image!", "No input image!",
                    MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    return;
                }
                this.Cursor = Cursors.WaitCursor;
                int inputImage = viewer.SelectedArea == null ? viewer.CVIPimage : viewer.SelectedImage;
                int outputImage = CvipOp.Local_Adaptive_Zoom(inputImage);
                if (outputImage != 0)
                {
                    string newImageName = viewer.Text;
                    newImageName += "_DoubleSize";
                    newImageName += CvipConstant.imageNameCount++.ToString();
                    MainForm.Viewers.Add(outputImage, newImageName);
                }
                this.Cursor = Cursors.Default;
            }
            else
            {
                if (MainForm.frmUtilities == null)
                {
                    MainForm.frmUtilities = new UtilitiesForm();
                    MainForm.frmUtilities.Show();
                }
                string util = itm.OwnerItem.Text;
                MainForm.frmUtilities.OpName = op;
                MainForm.frmUtilities.UtilName = util;
                MainForm.frmUtilities.Text = "Utility->" + util + "->" + op;
                MainForm.frmUtilities.Init();
                MainForm.frmUtilities.BringToFront();
            }
        }

        private void mnuCVIPtoolsWeblink_MouseMove(object sender, MouseEventArgs e)
        {
            this.mnuCVIP.Cursor = Cursors.Hand;
        }
        private void mnuCVIPtoolsWeblink_MouseLeave(object sender, EventArgs e)
        {
            this.mnuCVIP.Cursor = Cursors.Default;
        }
        private void mnuCVIPtoolsWeblink_Click(object sender, EventArgs e)
        {
            try { System.Diagnostics.Process.Start("http://cviptools.siue.edu"); }
            catch { }
        }

        private void mnuFileExit_Click(object sender, EventArgs e)
        {
            if (this.pnlQueue.RemoveAll())
                Application.Exit();
        }
        private void mnuFileHistogram_Click(object sender, EventArgs e)
        {
            // get the image that will be operated on
            ViewerForm viewer = this.pnlQueue.SelectedViewer;
            if (viewer == null)
            {
                MessageBox.Show("Please give an input image!", "No input image!",
                    MessageBoxButtons.OK, MessageBoxIcon.Warning);
                return;
            }
            int inputImage = viewer.CVIPimage;
            int outputImage = CvipOp.get_hist_real(inputImage);
            if (outputImage != 0)
            {
                // create a name for the new image
                string newImageName = viewer.Text + "_Hist";
                newImageName += CvipConstant.imageNameCount++.ToString();

                // Save image name and path into image queue and create an instance
                // of ImageViewer for holding image and doing other operations
                this.pnlQueue.Add(outputImage, newImageName);
            }
        }
        private void mnuFileOpen_Click(object sender, EventArgs e)
        {
            dlgFileOpen.InitialDirectory = TempOpenPath;
            if (dlgFileOpen.ShowDialog() == DialogResult.OK)
            {
                this.Cursor = Cursors.WaitCursor;
                this.pnlQueue.AddFiles(dlgFileOpen.FileNames);
                this.Cursor = Cursors.Default;
                TempOpenPath = Path.GetDirectoryName(dlgFileOpen.FileName);

            }
        }
        private void mnuFilePrint_Click(object sender, EventArgs e)
        {
            if (this.pnlQueue.SelectedViewer == null)
            {
                MessageBox.Show("This operation must have an input image!", "Input an image.",
                    MessageBoxButtons.OK, MessageBoxIcon.Warning);
                return;
            }
            PrintDialog dlg = new PrintDialog();
            dlg.Document = new PrintDocument();
            dlg.Document.PrintPage += this.OnPrintPage;
            if (dlg.ShowDialog() == DialogResult.OK)
            {
                dlg.Document.Print();
            }
        }
        private void OnPrintPage(object sender, PrintPageEventArgs e)
        {
            ViewerForm viewer = this.pnlQueue.SelectedViewer;
            int tmp = viewer.CVIPimage;
            int img = CvipOp.CondRemap_Image(tmp, dataType.CVIP_BYTE, 0, 255);
            CvipOp.Delete_Image(ref tmp);
            Bitmap bmp = CvipOp.CvipToBitmap(img);
            CvipOp.Delete_Image(ref img);
            e.Graphics.DrawImage(bmp, e.MarginBounds.Location);
        }
        private void mnuFileSave_Click(object sender, EventArgs e)
        {
            ViewerForm viewer = this.pnlQueue.SelectedViewer;
            if (viewer == null)
            {
                MessageBox.Show("This operation must have an input image!", "Input an image.",
                    MessageBoxButtons.OK, MessageBoxIcon.Warning);
                return;
            }
            imageFormat format = viewer.ImageFormat;
            switch (format)
            {
            case imageFormat.VIP: this.dlgFileSave.FilterIndex = 1; break;
            case imageFormat.EPS: this.dlgFileSave.FilterIndex = 2; break;
            case imageFormat.GIF: this.dlgFileSave.FilterIndex = 3; break;
            case imageFormat.ITX: this.dlgFileSave.FilterIndex = 4; break;
            case imageFormat.JPG: this.dlgFileSave.FilterIndex = 5; break;
            case imageFormat.JP2: this.dlgFileSave.FilterIndex = 6; break;
            case imageFormat.PNG: this.dlgFileSave.FilterIndex = 7; break;
            case imageFormat.PPM: this.dlgFileSave.FilterIndex = 8; break;
            case imageFormat.IRIS: this.dlgFileSave.FilterIndex = 9; break;
            case imageFormat.RAS: this.dlgFileSave.FilterIndex = 10; break;
            case imageFormat.TIF: this.dlgFileSave.FilterIndex = 11; break;
            case imageFormat.BMP: this.dlgFileSave.FilterIndex = 12; break;
            }
            string fname = viewer.Text;
            if (fname.Contains("."))
            {
                int idx = fname.LastIndexOf('.');
                string ext = fname.Substring(idx + 1).Trim().ToUpper();
                idx = -1;
                switch (ext)
                {
                case "VIP": idx = 1; break;
                case "EPS": idx = 2; break;
                case "GIF": idx = 3; break;
                case "ITX": idx = 4; break;
                case "JPG": idx = 5; break;
                case "JP2": idx = 6; break;
                case "PNG": idx = 7; break;
                case "PPM": idx = 8; break;
                case "IRIX": idx = 9; break;
                case "RAS": idx = 10; break;
                case "TIF": idx = 11; break;
                case "BMP": idx = 12; break;
                }
                if (idx > 0)
                {
                    this.dlgFileSave.FilterIndex = idx;
                    fname = fname.Substring(0, fname.Length - ext.Length - 1);
                }
            }
            this.dlgFileSave.FileName = fname;
            this.dlgFileSave.ShowDialog();
        }
        private void dlgFileSave_FileOk(object sender, CancelEventArgs e)
        {
            this.dlgFileSave.InitialDirectory = new FileInfo(this.dlgFileSave.FileName).DirectoryName;

            string ext = null;
            imageFormat format = imageFormat.VIP;
            switch (this.dlgFileSave.FilterIndex)
            {
            case 1:
                ext = ".vip";
                format = imageFormat.VIP;
                break;
            case 2:
                ext = ".eps";
                format = imageFormat.EPS;
                break;
            case 3:
                ext = ".gif";
                format = imageFormat.GIF;
                break;
            case 4:
                ext = ".itx";
                format = imageFormat.ITX;
                break;
            case 5:
                ext = ".jpg";
                format = imageFormat.JPG;
                break;
            case 6:
                ext = ".jp2";
                format = imageFormat.JP2;
                break;
            case 7:
                ext = ".png";
                format = imageFormat.PNG;
                break;
            case 8:
                ext = ".ppm";
                format = imageFormat.PPM;
                break;
            case 9:
                ext = ".irix";
                format = imageFormat.IRIS;
                break;
            case 10:
                ext = ".ras";
                format = imageFormat.RAS;
                break;
            case 11:
                ext = ".tif";
                format = imageFormat.TIF;
                break;
            case 12:
                ext = ".bmp";
                format = imageFormat.BMP;
                break;
            }
            string fname = this.dlgFileSave.FileName.Trim();
            if (!fname.ToLower().EndsWith(ext))
                fname += ext;
            if (File.Exists(fname))
            {
                string title = "Save as";
                string msg = "File " + this.dlgFileSave.FileName + " already exists.\n";
                msg += "Do you want to replace it?";
                if (MessageBox.Show(msg, title, MessageBoxButtons.YesNo, MessageBoxIcon.Warning) == DialogResult.No)
                {
                    e.Cancel = true;
                    return;
                }
                File.Delete(fname);
            }
            ViewerForm viewer = this.pnlQueue.SelectedViewer;
            int image = viewer.CVIPimage;
            if ((format != imageFormat.VIP) &&
                (viewer.DataType != dataType.CVIP_BYTE))
            {
                image = CvipOp.CondRemap_Image(image, dataType.CVIP_BYTE, 0, 255);
            }
            if ((format == imageFormat.JPG) || (format == imageFormat.JP2))
            {
                GetIntDialog dlg = new GetIntDialog();
                if (format == imageFormat.JPG)
                {
                    dlg.Prompt = "Enter compression quality for JPEG Compression:";
                    dlg.Text = "Compression Quality";
                    dlg.Value = 70;
                }
                else
                {
                    dlg.Prompt = "Enter compression ratio for JPEG2000 Compression:";
                    dlg.Text = "Compression Ratio";
                    dlg.Value = 50;
                }
                if (dlg.ShowDialog() == DialogResult.OK)
                {
                    CvipOp.Write_JPEG_Image(image, fname, 0, 0, format, 0, dlg.Value);
                }
            }
            else
            {
                CvipOp.Write_Image(image, fname, 0, 0, format, 0);
            }
        }

        private void mnuFFTMagnitude_Click(object sender, EventArgs e)
        {
            // get the image that will be operated on
            ViewerForm viewer = this.pnlQueue.SelectedViewer;
            if (viewer == null)
            {
                MessageBox.Show("Please give an input image!", "No input image!",
                    MessageBoxButtons.OK, MessageBoxIcon.Warning);
                return;
            }
            int inputImage = viewer.CVIPimage;
            if (CvipOp.History_Check(inputImage, 41) == 0)
            {
                MessageBox.Show("There is no transform history.", "FFT Magnitude",
                    MessageBoxButtons.OK, MessageBoxIcon.Warning);
                return;
            }
            int outputImage = CvipOp.Fft_Mag(inputImage);

            // create a name for the new image
            string newImageName = viewer.Text + "_fftmag";
            newImageName += CvipConstant.imageNameCount++.ToString();

            // Save image name and path into image queue and create an instance
            // of ImageViewer for holding image and doing other operations
            this.pnlQueue.Add(outputImage, newImageName);
        }
        private void mnuFFTPhase_Click(object sender, EventArgs e)
        {
            // get the image that will be operated on
            ViewerForm viewer = this.pnlQueue.SelectedViewer;
            if (viewer == null)
            {
                MessageBox.Show("Please give an input image!", "No input image!",
                    MessageBoxButtons.OK, MessageBoxIcon.Warning);
                return;
            }
            int inputImage = viewer.CVIPimage;
            if (CvipOp.History_Check(inputImage, 41) == 0)
            {
                MessageBox.Show("There is no transform history.", "FFT Phase",
                    MessageBoxButtons.OK, MessageBoxIcon.Warning);
                return;
            }
            int outputImage = CvipOp.Fft_Phase(inputImage, 0, -1);

            // create a name for the new image
            string newImageName = viewer.Text + "_fftphase";
            newImageName += CvipConstant.imageNameCount++.ToString();

            // Save image name and path into image queue and create an instance
            // of ImageViewer for holding image and doing other operations
            this.pnlQueue.Add(outputImage, newImageName);
        }

        private void mnuHelpAbout_Click(object sender, EventArgs e)
        {
            new AboutForm().ShowDialog();
        }
        private void mnuHelpContents_Click(object sender, EventArgs e)
        {
            MainForm.ShowHelp();
        }
        static public void ShowHelp()
        {
            string cvipHome = MainForm.CVIPtoolsHOME;
            if (string.IsNullOrEmpty(cvipHome))
            {
                MessageBox.Show("Can't find the CVIPtools help file. The CVIPtoolsHOME environment variable is not set.",
                    "CVIPtoolsHELP Not Found", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                return;
            }
            FileInfo fi = new FileInfo(cvipHome + @"HELP\CVIPtoolsHELP.CHM");
            if (!fi.Exists)
            {
                MessageBox.Show("The file: " + fi.FullName + " is missing.", "CVIPtoolsHELP Not Found",
                    MessageBoxButtons.OK, MessageBoxIcon.Warning);
                return;
            }
            System.Diagnostics.Process.Start(fi.FullName);
        }

        private void mnuLogRemap_Click(object sender, EventArgs e)
        {
            // get the image that will be operated on
            ViewerForm viewer = this.pnlQueue.SelectedViewer;
            if (viewer == null)
            {
                MessageBox.Show("Please give an input image!", "No input image!",
                    MessageBoxButtons.OK, MessageBoxIcon.Warning);
                return;
            }
            int inputImage = viewer.CVIPimage;
         /*   int xform = CvipOp.Check_xform_history(inputImage, 0);
            if (CvipOp.History_Check(inputImage, xform) == 0)
            {
                MessageBox.Show("There is no transform history.", "Log Remap",
                    MessageBoxButtons.OK, MessageBoxIcon.Warning);
                return;
            }*/
            LogRemap band = (LogRemap)(sender as ToolStripItem).Tag;
            // create a name for the new image
            string newImageName = viewer.Text + "_logremap_" + band.ToString();
            newImageName += CvipConstant.imageNameCount++.ToString();

            // Save image name and path into image queue and create an instance
            // of ImageViewer for holding image and doing other operations
            this.pnlQueue.Add(inputImage, newImageName, band);
        }

        private void mnuLongFileNames_CheckedChanged(object sender, EventArgs e)
        {
            if (mnuLongFileNames.Checked == true)
                CvipFunctionNames.longFileNamesChecked = 0;
            else
                CvipFunctionNames.longFileNamesChecked = 1;
        }
        private void mnuLongFileNames_Click(object sender, EventArgs e)
        {
            if (mnuLongFileNames.Checked == true)
                CvipFunctionNames.longFileNamesChecked = 0;
            else
                CvipFunctionNames.longFileNamesChecked = 1;
        }

        private void mnuViewBand_Click(object sender, EventArgs e)
        {
            ViewerForm viewer = this.pnlQueue.SelectedViewer;
            if (viewer == null) return;

            int imgInput = viewer.CVIPimage, imgOutput;
            int band = int.Parse((sender as ToolStripItem).Tag.ToString());
            int[] bands = new int[3];

            for (int i = 0; i < 3; i++)
            {
                if (i == band)
                    bands[i] = CvipOp.Extract_Band(imgInput, i + 1);
                else
                    bands[i] = CvipOp.New_Image(imageFormat.PGM,
                                                    colorFormat.GRAY,
                                                    1,
                                                    viewer.ImageHeight,
                                                    viewer.ImageWidth,
                                                    viewer.DataType,
                                                    dataFormat.REAL);
            }
            if ((imgOutput = CvipOp.Assemble_Bands(bands)) != 0)
            {
                string name = viewer.Text;
                switch (band)
                {
                case 0: name += "_red"; break;
                case 1: name += "_green"; break;
                case 2: name += "_blue"; break;
                }
                name += CvipConstant.imageNameCount++.ToString();
                this.pnlQueue.Add(imgOutput, name);
            }
        }
        private void mnuViewImageQueue_CheckedChanged(object sender, EventArgs e)
        {
            this.pnlQueue.Visible = this.mnuViewImageQueue.Checked;
        }
        private void ImageQueue_VisibleChanged(object sender, EventArgs e)
        {
            this.mnuViewImageQueue.Checked = this.pnlQueue.Visible;
        }
        private void mnuViewInfoPanel_CheckedChanged(object sender, EventArgs e)
        {
            this.pnlInfo.Visible = this.mnuViewInfoPanel.Checked;
        }
        private void InfoPanel_VisibleChanged(object sender, EventArgs e)
        {
            this.mnuViewInfoPanel.Checked = this.pnlInfo.Visible;
        }
        private void mnuViewStatusBar_CheckedChanged(object sender, EventArgs e)
        {
            this.statbarCVIP.Visible = this.mnuViewStatusBar.Checked;
        }
        private void mnuViewToolbar_CheckedChanged(object sender, EventArgs e)
        {
            this.toolbarCVIP.Visible = this.mnuViewToolbar.Checked;
        }

        protected override void OnLoad(EventArgs e)
        {
            base.OnLoad(e);
            this.mnuViewImageQueue.Checked = true;
            this.mnuViewInfoPanel.Checked = false;

            string cvipHome = MainForm.CVIPtoolsHOME;
            if (!string.IsNullOrEmpty(cvipHome))
            {
                this.dlgFileOpen.InitialDirectory = cvipHome + @"images";
                this.dlgFileSave.InitialDirectory = cvipHome + @"images";
            }
        }
        private void OnFocusedViewerChanged(ViewerForm viewer)
        {
            if (viewer != null)
            {
                this.statbarFileName.Text = viewer.Name;
                this.statbarColorFormat.Text = viewer.ColorFormat.ToString();
                this.statbarImageFormat.Text = viewer.ImageFormat.ToString();
                this.statbarDataFormat.Text = viewer.DataFormat.ToString();
                this.statbarDataType.Text = viewer.DataType.ToString().Substring(5);
                this.statbarDataRMin.Text = viewer.DataMin.ToString("0.##");
                this.statbarDataRMax.Text = viewer.DataMax.ToString("0.##");
                this.statbarBands.Text = viewer.Bands.ToString();
                this.statbarWidth.Text = viewer.ImageWidth.ToString();
                this.statbarHeight.Text = viewer.ImageHeight.ToString();
            }
            else
            {
                this.statbarFileName.Text = "";
                this.statbarColorFormat.Text = "";
                this.statbarImageFormat.Text = "";
                this.statbarDataFormat.Text = "";
                this.statbarDataType.Text = "";
                this.statbarDataRMin.Text = "";
                this.statbarDataRMax.Text = "";
                this.statbarBands.Text = "";
                this.statbarWidth.Text = "";
                this.statbarHeight.Text = "";
            }
        }
        private void OnSelectedViewerChanged(ViewerForm viewer)
        {
            bool bViewBandEnabled = (viewer != null) && (viewer.Bands == 3);

            this.mnuFileHistogram.Enabled = (viewer != null);
            this.mnuFileFFTPhase.Enabled = (viewer != null);
            this.mnuFileFFTMagnitude.Enabled = (viewer != null);
            this.mnuFileLogRemapAll.Enabled = (viewer != null);
            this.mnuFileLogRemapRed.Enabled = bViewBandEnabled;
            this.mnuFileLogRemapGreen.Enabled = bViewBandEnabled;
            this.mnuFileLogRemapBlue.Enabled = bViewBandEnabled;
            this.mnuFileViewRedBand.Enabled = bViewBandEnabled;
            this.mnuFileViewGreenBand.Enabled = bViewBandEnabled;
            this.mnuFileViewBlueBand.Enabled = bViewBandEnabled;
            this.mnuFileSave.Enabled = (viewer != null);
            this.mnuFilePrint.Enabled = (viewer != null);

            this.mnuViewHistogram.Enabled = (viewer != null);
            this.mnuViewFFTPhase.Enabled = (viewer != null);
            this.mnuViewFFTMagnitude.Enabled = (viewer != null);
            this.mnuViewLogRemapAll.Enabled = (viewer != null);
            this.mnuViewLogRemapRed.Enabled = bViewBandEnabled;
            this.mnuViewLogRemapGreen.Enabled = bViewBandEnabled;
            this.mnuViewLogRemapBlue.Enabled = bViewBandEnabled;
            this.mnuViewBandRed.Enabled = bViewBandEnabled;
            this.mnuViewBandGreen.Enabled = bViewBandEnabled;
            this.mnuViewBandBlue.Enabled = bViewBandEnabled;

            this.tbSave.Enabled = (viewer != null);
            this.tbPrint.Enabled = (viewer != null);
            this.tbHistogram.Enabled = (viewer != null);
            this.tbRedBand.Enabled = bViewBandEnabled;
            this.tbGreenBand.Enabled = bViewBandEnabled;
            this.tbBlueBand.Enabled = bViewBandEnabled;

            if (viewer == null)
                this.OnFocusedViewerChanged(null);
        }
        private void OnViewerMouseMoved(Point ptImage, ViewerForm viewer)
        {
            string[] rgb;
            if ((rgb = viewer.GetRGBString(ptImage)) != null)
            {
                this.tbColValue.Text = ptImage.X.ToString();
                this.tbRowValue.Text = ptImage.Y.ToString();
                this.tbRValue.Text = rgb[0];
                this.tbGValue.Text = rgb[1];
                this.tbBValue.Text = rgb[2];
            }
            else
            {
                this.tbColValue.Text = "";
                this.tbRowValue.Text = "";
                this.tbRValue.Text = "";
                this.tbGValue.Text = "";
                this.tbBValue.Text = "";
            }
        }

        static public CustomRemapForm ShowCustomRemapForm()
        {
            CustomRemapForm frm = null;
            if (MainForm.frmCustomRemap == null)
            {
                frm = MainForm.frmCustomRemap = new CustomRemapForm();
                MainForm.frmCustomRemap.Show();
            }
            MainForm.frmCustomRemap.BringToFront();
            return frm;
        }

        private void tbATAT_Click(object sender, EventArgs e)
        {
            string cvipHome = MainForm.CVIPtoolsHOME;
            if (string.IsNullOrEmpty(cvipHome))
            {
                MessageBox.Show("Can't find the CVIPATAT executable. The CVIPtoolsHOME environment variable is not set.",
                    "CVIPATAT Not Found", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                return;
            }
            FileInfo fi = new FileInfo(cvipHome + @"bin\CVIPATAT.exe");
            if (!fi.Exists)
            {
                MessageBox.Show("The file: " + fi.FullName + " is missing.", "CVIPATAT Not Found",
                    MessageBoxButtons.OK, MessageBoxIcon.Warning);
                return;
            }
            System.Diagnostics.Process.Start(fi.FullName);
        }
        private void tbATATFEPC_MouseEnter(object sender, EventArgs e)
        {
            (sender as ToolStripButton).ForeColor = Color.Black;
        }
        private void tbATATFEPC_MouseLeave(object sender, EventArgs e)
        {
            (sender as ToolStripButton).ForeColor = Color.White;
        }
        private void tbCamera_Click(object sender, EventArgs e)
        {
            if (MainForm.frmLaunchCamera == null)
            {
                MainForm.frmLaunchCamera = new LaunchCameraForm();
                MainForm.frmLaunchCamera.Show();
            }
            MainForm.frmLaunchCamera.BringToFront();
        }
        private void tbFEPC_Click(object sender, EventArgs e)
        {
            string cvipHome = MainForm.CVIPtoolsHOME;
            if (string.IsNullOrEmpty(cvipHome))
            {
                MessageBox.Show("Can't find the CVIPFEPC executable. The CVIPtoolsHOME environment variable is not set.",
                    "CVIPFEPC Not Found", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                return;
            }
            FileInfo fi = new FileInfo(cvipHome + @"bin\CVIPFEPC.exe");
            if (!fi.Exists)
            {
                MessageBox.Show("The file: " + fi.FullName + " is missing.", "CVIPFEPC Not Found",
                    MessageBoxButtons.OK, MessageBoxIcon.Warning);
                return;
            }
            System.Diagnostics.Process.Start(fi.FullName);
        }

        protected override void WndProc(ref Message m)
        {
            switch ((WM)m.Msg)
            {
            case WM.CLOSE:
            case WM.ENDSESSION:
            case WM.QUERYENDSESSION:
                if (!this.pnlQueue.RemoveAll())
                    m.Msg = (int)WM.NULL;
                break;
            
            case WM.CREATE:
                this.pnlQueue.SelectedViewerChanged += this.OnSelectedViewerChanged;
                ViewerForm.FocusedViewerChanged += this.OnFocusedViewerChanged;
                ViewerForm.MouseMoved += this.OnViewerMouseMoved;
                break;
            

            case WM.DESTROY:
                this.pnlQueue.SelectedViewerChanged -= this.OnSelectedViewerChanged;
                ViewerForm.FocusedViewerChanged -= this.OnFocusedViewerChanged;
                ViewerForm.MouseMoved -= this.OnViewerMouseMoved;
                break;
            }
            base.WndProc(ref m);
        }

        static public MainForm TheMainForm { get { return (MainForm.frmMain); } }
        static public string CVIPtoolsHOME
        {
            get
            {
                string envKey = @"HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Control\Session Manager\Environment";
                return (string)Registry.GetValue(envKey, "CVIPtoolsHOME", null);
            }
        }
        static public AnalysisForm AnalysisForm
        {
            get { return MainForm.frmAnalysis; }
            set
            {
                if (value != null) throw new ArgumentException("Value must be null");
                if (MainForm.frmAnalysis != null)
                {
                    AnalysisForm frm = MainForm.frmAnalysis;
                    MainForm.frmAnalysis = null;
                    frm.Close();
                }
            }
        }
        static public CompressionForm CompressionForm
        {
            get { return MainForm.frmCompression; }
            set
            {
                if (value != null) throw new ArgumentException("Value must be null");
                if (MainForm.frmCompression != null)
                {
                    CompressionForm frm = MainForm.frmCompression;
                    MainForm.frmCompression = null;
                    frm.Close();
                }
            }
        }
        static public CustomRemapForm CustomRemapForm
        {
            get { return MainForm.frmCustomRemap; }
            set
            {
                if (value != null) throw new ArgumentException("Value must be null");
                if (MainForm.frmCustomRemap != null)
                {
                    CustomRemapForm frm = MainForm.frmCustomRemap;
                    MainForm.frmCustomRemap = null;
                    frm.Close();
                }
            }
        }
        static public EnhancementForm EnhancementForm
        {
            get { return MainForm.frmEnhancement; }
            set
            {
                if (value != null) throw new ArgumentException("Value must be null");
                if (MainForm.frmEnhancement != null)
                {
                    EnhancementForm frm = MainForm.frmEnhancement;
                    MainForm.frmEnhancement = null;
                    frm.Close();
                }
            }
        }
        static public LaunchCameraForm LaunchCameraForm
        {
            get { return MainForm.frmLaunchCamera; }
            set
            {
                if (value != null) throw new ArgumentException("Value must be null");
                if (MainForm.frmLaunchCamera != null)
                {
                    LaunchCameraForm frm = MainForm.frmLaunchCamera;
                    MainForm.frmLaunchCamera = null;
                    frm.Close();
                }
            }
        }
        static public RestorationForm RestorationForm
        {
            get { return MainForm.frmRestoration; }
            set
            {
                if (value != null) throw new ArgumentException("Value must be null");
                if (MainForm.frmRestoration != null)
                {
                    RestorationForm frm = MainForm.frmRestoration;
                    MainForm.frmRestoration = null;
                    frm.Close();
                }
            }
        }
        static public UtilitiesForm UtilitiesForm
        {
            get { return MainForm.frmUtilities; }
            set
            {
                if (value != null) throw new ArgumentException("Value must be null");
                if (MainForm.frmUtilities != null)
                {
                    UtilitiesForm frm = MainForm.frmUtilities;
                    MainForm.frmUtilities = null;
                    frm.Close();
                }
            }
        }
        static public ImageQueue Viewers
        {
            get
            {
                ImageQueue viewers = null;
                if (MainForm.TheMainForm != null)
                    viewers = MainForm.TheMainForm.pnlQueue;
                return viewers;
            }
        }

        private void MainForm_Load(object sender, EventArgs e)
        {

        }

        private void mnuView_Click(object sender, EventArgs e)
        {

        }

        private void statbarDataFormat_Click(object sender, EventArgs e)
        {

        }

       

       

        
    }
}
