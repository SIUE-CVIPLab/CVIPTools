/*''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' ======================================================================
' Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
' ======================================================================
'
'             File Name: Features.cs
'           Description: Contains the controls and code
'                        for Analysis->Features page
'         Related Files: CvipOp.cs
'                        FeatureFile.cs
'                        FeatureHeader.cs
'                        CvipConstant.cs
'                        CvipObject.cs
'                        FeatureViewer.cs
'   Initial Coding Date: April 2007
'              Modified: May 2010
'       Delevoping tool: Visual Studio 2010-C#
'             Credit(s): Wenjun(Evan) Bian
'                        Patrick Solt
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
using System.IO;
using System.Text;
using System.Windows.Forms;
using Excel = Microsoft.Office.Interop.Excel;


namespace CVIPGUI.Analysis
{
    public partial class Features : UserControl
    {
        FeatureViewer m_vwrFeatures = new FeatureViewer();

        public Features()
        {
            InitializeComponent();
        }
        private void btnApply_Click(object sender, EventArgs e)
        {
            ViewerForm viewerOrig = this.cboOriginalImage.SelectedItem as ViewerForm;
            ViewerForm viewerSeg = this.cboSegmentedImage.SelectedItem as ViewerForm;
            if ((viewerOrig == null) || (viewerSeg == null))
            {
                MessageBox.Show("This operation must have an original and a segmented image.",
                    "No input image!", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                return;
            }
            FileInfo fi = this.FeatureFileInfo;

            if (fi == null)
            {
                MessageBox.Show("Please give a feature file name by clicking 'Save as' button.",
                    "No Feature File Name!", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                return;
            }
            if (this.ClassName.Contains(" "))
            {
                MessageBox.Show("Spaces are not allowed in Class Names",
                    "Error", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                // this.txtClassName.Text = " ";
                return;
            }

            this.btnApply.Enabled = false;
            this.Cursor = Cursors.WaitCursor;

            int imgOrig = viewerOrig.CVIPimage;
            int imgLabeled = viewerSeg.CVIPimage;
            if (viewerSeg.Bands != 1)
                imgLabeled = CvipOp.Luminance_Image(imgLabeled);
            imgLabeled = CvipOp.Label(imgLabeled);

            FeatureFile ff = null;
            if (fi.Exists)
                ff = FeatureFile.Open(fi.FullName);
            if (ff == null)
                ff = new FeatureFile();
            string tempName;
            if (this.ObjectName.Contains(" "))
            {
                tempName = this.ObjectName.Replace(" ", "_");
                MessageBox.Show("Filenames with spaces will be replaced with underscores in results files.",
                    "Spaces in File Name!", MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
            else
            { tempName = this.ObjectName; }
            if (ff.Add(imgOrig, imgLabeled, this.Row, this.Col, tempName, viewerSeg.Text, this.ClassName, this.FeatureHeader))
            {
                ff.Write(fi.FullName);
                this.m_vwrFeatures.FeatureFile = ff;

                if (this.cboFeatureFile.SelectedItem as FileInfo != fi)
                {
                    this.cboFeatureFile.SelectedItem = null;
                    foreach (FileInfo fiPresent in this.cboFeatureFile.Items)
                    {
                        if (fiPresent.FullName.ToLower() == fi.FullName.ToLower())
                        {
                            this.cboFeatureFile.SelectedItem = fiPresent;
                            break;
                        }
                    }
                    if (this.cboFeatureFile.SelectedItem == null)
                    {
                        this.cboFeatureFile.Items.Add(fi);
                        this.cboFeatureFile.SelectedItem = fi;
                    }
                    this.m_vwrFeatures.Text = fi.Name;
                    this.m_vwrFeatures.Show();
                    this.m_vwrFeatures.BringToFront();
                }
            }
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
        private void btnSaveAs_Click(object sender, EventArgs e)
        {
            FileInfo fi = this.FeatureFileInfo;
            if (fi != null)
            {
                this.dlgFileOpen.InitialDirectory = fi.Directory.FullName;
                this.dlgFileOpen.FileName = fi.Name;
            }
            if (this.dlgFileOpen.ShowDialog() == DialogResult.OK)
            {
                fi = new FileInfo(this.dlgFileOpen.FileName.Trim());
                if (string.IsNullOrEmpty(fi.Extension))
                    fi = new FileInfo(fi.FullName + ".txt");
                this.cboFeatureFile.SelectedItem = null;
                foreach (FileInfo fiPresent in this.cboFeatureFile.Items)
                {
                    if (fiPresent.FullName.ToLower() == fi.FullName.ToLower())
                    {
                        this.cboFeatureFile.SelectedItem = fiPresent;
                        break;
                    }
                }
                if (this.cboFeatureFile.SelectedItem == null)
                {
                    this.cboFeatureFile.Items.Add(fi);
                    this.cboFeatureFile.SelectedItem = fi;
                }
                if (fi.Exists)
                {
                    FeatureFile ff = FeatureFile.Open(fi.FullName);
                    if (ff != null)
                    {
                        this.FeatureHeader = new FeatureHeader(ff.FeatureHeader);
                        this.m_vwrFeatures.Text = fi.Name;
                        this.m_vwrFeatures.Show(ff);
                    }
                }
            }
        }
        private void btnSelectAllBin_Click(object sender, EventArgs e)
        {
            bool bChecked = this.btnSelectAllBin.Text == "Select All";
            if (bChecked)
                this.btnSelectAllBin.Text = "Deselect All";
            else
                this.btnSelectAllBin.Text = "Select All";

            this.chkArea.Checked = bChecked;
            this.chkCentroid.Checked = bChecked;
            this.chkOrientation.Checked = bChecked;
            this.chkPerimeter.Checked = bChecked;
            this.chkEuler.Checked = bChecked;
            this.chkProjections.Checked = bChecked;
            this.chkThinness.Checked = bChecked;
            this.chkAspect.Checked = bChecked;
        }
        private void btnSelectAllHist_Click(object sender, EventArgs e)
        {
            bool bChecked = this.btnSelectAllHist.Text == "Select All";
            if (bChecked)
                this.btnSelectAllHist.Text = "Deselect All";
            else
                this.btnSelectAllHist.Text = "Select All";

            this.chkHistMean.Checked = bChecked;
            this.chkHistStdDev.Checked = bChecked;
            this.chkHistSkew.Checked = bChecked;
            this.chkHistEnergy.Checked = bChecked;
            this.chkHistEntropy.Checked = bChecked;
        }
        private void btnSelectAllRst_Click(object sender, EventArgs e)
        {
            bool bChecked = this.btnSelectAllRst.Text == "Select All";
            if (bChecked)
                this.btnSelectAllRst.Text = "Deselect All";
            else
                this.btnSelectAllRst.Text = "Select All";

            this.chkRst1.Checked = bChecked;
            this.chkRst2.Checked = bChecked;
            this.chkRst3.Checked = bChecked;
            this.chkRst4.Checked = bChecked;
            this.chkRst5.Checked = bChecked;
            this.chkRst6.Checked = bChecked;
            this.chkRst7.Checked = bChecked;
        }
        private void btnSelectAllTex_Click(object sender, EventArgs e)
        {
            bool bChecked = this.btnSelectAllTex.Text == "Select All";
            if (bChecked)
                this.btnSelectAllTex.Text = "Deselect All";
            else
                this.btnSelectAllTex.Text = "Select All";

            this.chkTexEnergy.Checked = bChecked;
            this.chkTexInertia.Checked = bChecked;
            this.chkTexCorrelation.Checked = bChecked;
            this.chkTexInvDiff.Checked = bChecked;
            this.chkTexEntropy.Checked = bChecked;
        }
        private void btnSpectral_Click(object sender, EventArgs e)
        {
            this.chkSpectral.Checked = (this.btnSpectral.Text == "Select");
            if (this.chkSpectral.Checked)
                this.btnSpectral.Text = "Deselect";
            else
                this.btnSpectral.Text = "Select";
        }
        private void button1_Click(object sender, EventArgs e)
        {
            bool bChecked = this.button1.Text == "Select All";
            if (bChecked)
                this.button1.Text = "Deselect All";
            else
                this.button1.Text = "Select All";
            this.chklaw1.Checked = bChecked;
            this.chklaw2.Checked = bChecked;
            this.chklaw3.Checked = bChecked;
            this.chklaw4.Checked = bChecked;
            this.chklaw5.Checked = bChecked;
            this.chklaw6.Checked = bChecked;
            this.chklaw7.Checked = bChecked;
            this.chklaw8.Checked = bChecked;
            this.chklaw9.Checked = bChecked;
            this.chklaw10.Checked = bChecked;
            this.chklaw11.Checked = bChecked;
            this.chklaw12.Checked = bChecked;
            this.chklaw13.Checked = bChecked;
            this.chklaw14.Checked = bChecked;
            this.chklaw15.Checked = bChecked;
        }
        private void btnViewFeatureFile_Click(object sender, EventArgs e)
        {

            FileInfo fi = this.FeatureFileInfo;
            FeatureFile ff = null;

            if ((fi != null) && fi.Exists)
            {
                ff = FeatureFile.Open(fi.FullName);

                if ((ff != null) && (this.cboFeatureFile.SelectedItem as FileInfo != fi))
                {

                    this.cboFeatureFile.SelectedItem = null;
                    foreach (FileInfo fiPresent in this.cboFeatureFile.Items)
                    {
                        if (fiPresent.FullName.ToLower() == fi.FullName.ToLower())
                        {
                            this.cboFeatureFile.SelectedItem = fiPresent;
                            break;
                        }
                    }
                    if (this.cboFeatureFile.SelectedItem == null)
                    {

                        this.cboFeatureFile.Items.Add(fi);
                        this.cboFeatureFile.SelectedItem = fi;
                    }
                }
            }
            if (ff != null)
            {
                this.FeatureHeader = new FeatureHeader(ff.FeatureHeader);
                this.m_vwrFeatures.Text = fi.Name;
            }
            else
                ff = new FeatureFile(this.FeatureHeader);

            this.m_vwrFeatures.Show(ff);
        }
        private void btnViewLabeledImage_Click(object sender, EventArgs e)
        {
            ViewerForm viewerSeg = this.cboSegmentedImage.SelectedItem as ViewerForm;
            if (viewerSeg == null)
            {
                MessageBox.Show("This Operation must have a Segmented image",
                    "No input image!", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                return;
            }
            int imgLabeled = viewerSeg.CVIPimage;
            if (viewerSeg.Bands != 1)
                imgLabeled = CvipOp.Luminance_Image(imgLabeled);
            imgLabeled = CvipOp.Label(imgLabeled);
            if (imgLabeled != 0)
            {
                string newImageName = viewerSeg.Text;
                newImageName += CvipFunctionNames.getFncName("_Label");
                newImageName += CvipConstant.imageNameCount++.ToString();
                MainForm.Viewers.Add(imgLabeled, newImageName);
            }
        }




        private void OnSelectedViewerChanged(ViewerForm viewer)
        {
            if (MainForm.Viewers != null)
            {
                if ((ModifierKeys & Keys.Alt) == Keys.Alt)
                {
                    this.cboSegmentedImage.SelectedItem = viewer;
                }
                else
                {
                    if ((ModifierKeys & Keys.Control) == Keys.Control)
                    {
                        this.cboOriginalImage.SelectedItem = viewer;
                    }
                }
            }
        }


        private void cboFeatureFile_SelectedIndexChanged(object sender, EventArgs e)
        {
            FileInfo fi = this.FeatureFileInfo;
            if ((fi != null) && fi.Exists)
            {
                FeatureFile ff = FeatureFile.Open(fi.FullName);
                if (ff != null)
                {
                    if (this.cboFeatureFile.SelectedItem as FileInfo != fi)
                    {
                        this.cboFeatureFile.SelectedItem = null;
                        foreach (FileInfo fiPresent in this.cboFeatureFile.Items)
                        {
                            if (fiPresent.FullName.ToLower() == fi.FullName.ToLower())
                            {
                                this.cboFeatureFile.SelectedItem = fiPresent;
                                break;
                            }
                        }
                        if (this.cboFeatureFile.SelectedItem == null)
                        {
                            this.cboFeatureFile.Items.Add(fi);
                            this.cboFeatureFile.SelectedItem = fi;
                        }
                    }
                    this.FeatureHeader = new FeatureHeader(ff.FeatureHeader);
                    this.m_vwrFeatures.Text = fi.Name;
                    this.m_vwrFeatures.Show(ff);
                }
            }
        }
        protected override void OnLoad(EventArgs e)
        {
            base.OnLoad(e);

            if (MainForm.Viewers != null)
            {
                // Populate Feature File List
                string cvipHome = MainForm.CVIPtoolsHOME;
                if (!string.IsNullOrEmpty(cvipHome))
                {
                    string dirFeatures = cvipHome + @"bin\feature";
                    this.dlgFileOpen.InitialDirectory = dirFeatures;
                    this.cboFeatureFile.Items.Clear();
                    foreach (FileInfo fi in new DirectoryInfo(dirFeatures).GetFiles("*.txt"))
                        this.cboFeatureFile.Items.Add(fi);
                }
                OnSelectedViewerChanged(MainForm.Viewers.SelectedViewer);

                OnViewerCollectionChanged();
            }
        }
        private void OnViewerCollectionChanged()
        {
            if (MainForm.Viewers != null)
            {
                ViewerForm viewerOriginal = this.cboOriginalImage.SelectedItem as ViewerForm;
                ViewerForm viewerSegmented = this.cboSegmentedImage.SelectedItem as ViewerForm;
                if (viewerOriginal == null) viewerOriginal = MainForm.Viewers.SelectedViewer;
                if (viewerSegmented == null) viewerSegmented = MainForm.Viewers.SelectedViewer;
                this.cboOriginalImage.Items.Clear();
                this.cboSegmentedImage.Items.Clear();
                foreach (ViewerForm viewer in MainForm.Viewers)
                {
                    this.cboOriginalImage.Items.Add(viewer);
                    this.cboSegmentedImage.Items.Add(viewer);
                }
                this.cboOriginalImage.SelectedItem = viewerOriginal;
                this.cboSegmentedImage.SelectedItem = viewerSegmented;
            }
        }
        private void OnViewerMouseClick(Point pos, ViewerForm viewer)
        {
            if ((ModifierKeys & (Keys.Control)) == Keys.Control)
                this.cboOriginalImage.SelectedItem = viewer;
            else if ((ModifierKeys & Keys.Alt) == Keys.Alt)
                this.cboSegmentedImage.SelectedItem = viewer;
            this.Col = pos.X;
            this.Row = pos.Y;
        }
        private void ResetControls()
        {
            // Populate Feature File List
            string cvipHome = MainForm.CVIPtoolsHOME;
            if (!string.IsNullOrEmpty(cvipHome))
            {
                string dirFeatures = cvipHome + @"bin\feature";
                this.dlgFileOpen.InitialDirectory = dirFeatures;
                this.cboFeatureFile.Items.Clear();
                foreach (FileInfo fi in new DirectoryInfo(dirFeatures).GetFiles("*.txt"))
                    this.cboFeatureFile.Items.Add(fi);
            }
            this.btnSelectAllBin.Text = "Select All";
            this.btnSelectAllRst.Text = "Select All";
            this.btnSelectAllHist.Text = "Select All";
            this.btnSelectAllTex.Text = "Select All";
            this.btnSpectral.Text = "Select";
            this.button1.Text = "Select All";

            this.txtClassName.Clear();
            this.txtFeatureCol.Text = "1";
            this.txtFeatureRow.Text = "1";

            this.FeatureHeader = new FeatureHeader();

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
                        ViewerForm.MouseClicked += this.OnViewerMouseClick;
                        OnViewerCollectionChanged();
                        break;

                    case WM.DESTROY:
                        MainForm.Viewers.SelectedViewerChanged -= this.OnSelectedViewerChanged;
                        MainForm.Viewers.ViewerCollectionChanged -= this.OnViewerCollectionChanged;
                        ViewerForm.MouseClicked -= this.OnViewerMouseClick;
                        break;
                }
            }
        }

        int Col
        {
            get
            {
                int col = -1;
                int.TryParse(this.txtFeatureCol.Text, out col);
                return col;
            }
            set { this.txtFeatureCol.Text = value.ToString(); }
        }
        int Row
        {
            get
            {
                int row = -1;
                int.TryParse(this.txtFeatureRow.Text, out row);
                return row;
            }
            set { this.txtFeatureRow.Text = value.ToString(); }
        }
        int ProjectionsHeight
        {
            get
            {
                int height = -1;
                int.TryParse(this.txtProjHeight.Text, out height);
                return height;
            }
            set { this.txtProjHeight.Text = value.ToString(); }
        }
        int ProjectionsWidth
        {
            get
            {
                int width = -1;
                int.TryParse(this.txtProjWidth.Text, out width);
                return width;
            }
            set { this.txtProjWidth.Text = value.ToString(); }
        }
        int SpectralRings
        {
            get
            {
                int rings = -1;
                int.TryParse(this.txtNumRings.Text, out rings);
                return rings;
            }
            set { this.txtNumRings.Text = value.ToString(); }
        }
        int SpectralSectors
        {
            get
            {
                int sectors = -1;
                int.TryParse(this.txtNumSectors.Text, out sectors);
                return sectors;
            }
            set { this.txtNumSectors.Text = value.ToString(); }
        }
        int TextureDistance
        {
            get
            {
                int distance = -1;
                int.TryParse(this.cboTexDistance.Text, out distance);
                return distance;
            }
            set { this.cboTexDistance.Text = value.ToString(); }
        }
        FileInfo FeatureFileInfo
        {
            get
            {
                FileInfo fi = this.cboFeatureFile.SelectedItem as FileInfo;
                if ((fi == null) && !string.IsNullOrEmpty(this.cboFeatureFile.Text.Trim()))
                {
                    string fname = this.cboFeatureFile.Text.Trim();
                    if (fname.IndexOfAny(new char[] { '\\', '/' }) < 0)
                    {
                        string cvipHome = MainForm.CVIPtoolsHOME;
                        if (!string.IsNullOrEmpty(cvipHome))
                            fname = cvipHome + @"bin\feature\" + fname;
                    }
                    fi = new FileInfo(fname);
                }
                if ((fi != null) && string.IsNullOrEmpty(fi.Extension))
                    fi = new FileInfo(fi.FullName + ".txt");
                if (fi != null)
                    fi.Refresh();
                return fi;
            }
        }
        FeatureHeader FeatureHeader
        {
            get
            {
                FeatureHeader fh = new FeatureHeader();
                fh.ProjectionsHeight = this.ProjectionsHeight;
                fh.ProjectionsWidth = this.ProjectionsWidth;
                fh.SpectralRings = this.SpectralRings;
                fh.SpectralSectors = this.SpectralSectors;
                fh.TextureDistance = this.TextureDistance;
                fh.TextureUseZeros = this.chkIncludeZero.Checked;
                fh.UseArea = this.chkArea.Checked;
                fh.UseAspectRatio = this.chkAspect.Checked;
                fh.UseCentroid = this.chkCentroid.Checked;
                fh.UseEuler = this.chkEuler.Checked;
                fh.UseHistMean = this.chkHistMean.Checked;
                fh.UseHistStdDev = this.chkHistStdDev.Checked;
                fh.UseHistSkew = this.chkHistSkew.Checked;
                fh.UseHistEnergy = this.chkHistEnergy.Checked;
                fh.UseHistEntropy = this.chkHistEntropy.Checked;
                fh.UseOrientation = this.chkOrientation.Checked;
                fh.UsePerimeter = this.chkPerimeter.Checked;
                fh.UseProjections = this.chkProjections.Checked;
                fh.UseRst[0] = this.chkRst1.Checked;
                fh.UseRst[1] = this.chkRst2.Checked;
                fh.UseRst[2] = this.chkRst3.Checked;
                fh.UseRst[3] = this.chkRst4.Checked;
                fh.UseRst[4] = this.chkRst5.Checked;
                fh.UseRst[5] = this.chkRst6.Checked;
                fh.UseRst[6] = this.chkRst7.Checked;
                fh.UseSpectral = this.chkSpectral.Checked;
                fh.UseTexEnergy = this.chkTexEnergy.Checked;
                fh.UseTexInertia = this.chkTexInertia.Checked;
                fh.UseTexCorrelation = this.chkTexCorrelation.Checked;
                fh.UseTexInvDiff = this.chkTexInvDiff.Checked;
                fh.UseTexEntropy = this.chkTexEntropy.Checked;
                fh.UseThinness = this.chkThinness.Checked;
                fh.UseMask1 = this.chklaw1.Checked;
                fh.UseMask2 = this.chklaw2.Checked;
                fh.UseMask3 = this.chklaw3.Checked;
                fh.UseMask4 = this.chklaw4.Checked;
                fh.UseMask5 = this.chklaw5.Checked;
                fh.UseMask6 = this.chklaw6.Checked;
                fh.UseMask7 = this.chklaw7.Checked;
                fh.UseMask8 = this.chklaw8.Checked;
                fh.UseMask9 = this.chklaw9.Checked;
                fh.UseMask10 = this.chklaw10.Checked;
                fh.UseMask11 = this.chklaw11.Checked;
                fh.UseMask12 = this.chklaw12.Checked;
                fh.UseMask13 = this.chklaw13.Checked;
                fh.UseMask14 = this.chklaw14.Checked;
                fh.UseMask15 = this.chklaw15.Checked;
                return fh;
            }
            set
            {
                if (value == null)
                    value = new FeatureHeader();
                this.ProjectionsHeight = value.ProjectionsHeight;
                this.ProjectionsWidth = value.ProjectionsWidth;
                this.SpectralRings = value.SpectralRings;
                this.SpectralSectors = value.SpectralSectors;
                this.TextureDistance = value.TextureDistance;
                this.chkIncludeZero.Checked = value.TextureUseZeros;
                this.chkArea.Checked = value.UseArea;
                this.chkAspect.Checked = value.UseAspectRatio;
                this.chkCentroid.Checked = value.UseCentroid;
                this.chkEuler.Checked = value.UseEuler;
                this.chkHistMean.Checked = value.UseHistMean;
                this.chkHistStdDev.Checked = value.UseHistStdDev;
                this.chkHistSkew.Checked = value.UseHistSkew;
                this.chkHistEnergy.Checked = value.UseHistEnergy;
                this.chkHistEntropy.Checked = value.UseHistEntropy;
                this.chkOrientation.Checked = value.UseOrientation;
                this.chkPerimeter.Checked = value.UsePerimeter;
                this.chkProjections.Checked = value.UseProjections;
                this.chkRst1.Checked = value.UseRst[0];
                this.chkRst2.Checked = value.UseRst[1];
                this.chkRst3.Checked = value.UseRst[2];
                this.chkRst4.Checked = value.UseRst[3];
                this.chkRst5.Checked = value.UseRst[4];
                this.chkRst6.Checked = value.UseRst[5];
                this.chkRst7.Checked = value.UseRst[6];
                this.chkSpectral.Checked = value.UseSpectral;
                this.chkTexEnergy.Checked = value.UseTexEnergy;
                this.chkTexInertia.Checked = value.UseTexInertia;
                this.chkTexCorrelation.Checked = value.UseTexCorrelation;
                this.chkTexInvDiff.Checked = value.UseTexInvDiff;
                this.chkTexEntropy.Checked = value.UseTexEntropy;
                this.chkThinness.Checked = value.UseThinness;
                this.chklaw1.Checked = value.UseMask1;
                this.chklaw2.Checked = value.UseMask2;
                this.chklaw3.Checked = value.UseMask3;
                this.chklaw4.Checked = value.UseMask4;
                this.chklaw5.Checked = value.UseMask5;
                this.chklaw6.Checked = value.UseMask6;
                this.chklaw7.Checked = value.UseMask7;
                this.chklaw8.Checked = value.UseMask8;
                this.chklaw9.Checked = value.UseMask9;
                this.chklaw10.Checked = value.UseMask10;
                this.chklaw11.Checked = value.UseMask11;
                this.chklaw12.Checked = value.UseMask12;
                this.chklaw13.Checked = value.UseMask13;
                this.chklaw14.Checked = value.UseMask14;
                this.chklaw15.Checked = value.UseMask15;

            }
        }
        string ClassName { get { return this.txtClassName.Text; } }
        string ObjectName { get { return this.cboOriginalImage.Text; } }

        private void chklaw1_CheckedChanged(object sender, EventArgs e)
        {

        }

        private void grplaw_Enter(object sender, EventArgs e)
        {

        }

        private void lblFeatureFile_Click(object sender, EventArgs e)
        {

        }

        private void button2_Click(object sender, EventArgs e)
        {
            bool bChecked = this.button2.Text == "Select All";
            if (bChecked)
                this.button2.Text = "Deselect All";
            else
                this.button2.Text = "Select All";
            this.chklaw1.Checked = bChecked;
            this.chklaw2.Checked = bChecked;
            this.chklaw3.Checked = bChecked;
            this.chklaw4.Checked = bChecked;
            this.chklaw5.Checked = bChecked;
            this.chklaw6.Checked = bChecked;
            this.chklaw7.Checked = bChecked;
            this.chklaw8.Checked = bChecked;
            this.chklaw9.Checked = bChecked;
            this.chklaw10.Checked = bChecked;
            this.chklaw11.Checked = bChecked;
            this.chklaw12.Checked = bChecked;
            this.chklaw13.Checked = bChecked;
            this.chklaw14.Checked = bChecked;
            this.chklaw15.Checked = bChecked;
        }

        private void btnExceltoText_Click(object sender, EventArgs e)
        {
            String dirFeatures = MainForm.CVIPtoolsHOME;
            if (!string.IsNullOrEmpty(dirFeatures))
                dirFeatures += @"bin\feature";

            OpenFileDialog dlgFileOpen = new OpenFileDialog();
            dlgFileOpen.Filter = "All Files(*.*)|*.*" + "Excel Workbook (*.xlsx)|*.xlsx|";
            dlgFileOpen.FilterIndex = 2;
            dlgFileOpen.InitialDirectory = dirFeatures;
            dlgFileOpen.Title = "Choose Excel File";
            SaveFileDialog dlgFileSave = new SaveFileDialog();
            dlgFileSave.Filter = "All Files(*.*)|*.*" + "Text Documents (*.txt|*.txt|";
            dlgFileSave.FilterIndex = 2;
            dlgFileSave.InitialDirectory = dirFeatures;
            dlgFileSave.Title = "Save Text File";
            
            if (dlgFileOpen.ShowDialog() == DialogResult.OK && dlgFileSave.ShowDialog() == DialogResult.OK)
            {
                ExceltoText(dlgFileOpen.FileName, dlgFileSave.FileName);
            }
        }

        private void ExceltoText(string excelSheet, string textSheet)
        {
            int colCount, rowCount, num;
            string itemPartNumber, txtTitle;
            if (File.Exists(textSheet))
            {
                string title = "Save as";
                string msg = "File " + textSheet + " already exists.\n";
                msg += "Do you want to replace it?";
                MessageBoxButtons buttons = MessageBoxButtons.YesNo;
                MessageBoxIcon icon = MessageBoxIcon.Warning;
                if (MessageBox.Show(msg, title, buttons, icon) == DialogResult.No)
                    return;
                File.Delete(textSheet);
            }
            Excel.ApplicationClass app = new Microsoft.Office.Interop.Excel.ApplicationClass();
            Excel.Workbook book = app.Workbooks.Open(excelSheet, 0, true, 5, "", "", true, Microsoft.Office.Interop.Excel.XlPlatform.xlWindows, "\t", false, false, 0, true, 1, 0); ;
            Excel.Worksheet sheet = (Excel.Worksheet)book.Worksheets.get_Item(1);
            try
            {
                using (StreamWriter sr = File.CreateText(textSheet))
                {

                    //Create Header
                    itemPartNumber = Convert.ToString(((Excel.Range)sheet.Cells[2, 3]).Value2);
                    sr.WriteLine("CVIPtools feature file for image with " + itemPartNumber + " band");
                    colCount = 2;
                    num = 1;
                    while (!string.IsNullOrEmpty(itemPartNumber = Convert.ToString(((Excel.Range)sheet.Cells[1, colCount]).Value2)))
                    {
                        if (itemPartNumber != "ClassName" && itemPartNumber != "Bands")
                        {
                            sr.Write(num.ToString());
                            sr.Write(". ");
                            txtTitle = determineName(itemPartNumber, ref colCount);
                            sr.Write(txtTitle);
                            sr.WriteLine();
                            num++;
                        }
                        colCount++;
                    }
                    sr.WriteLine("*** END OF HEADER; CLASS (optional) SHOWN AT THE END OF DATA ***");
                    sr.WriteLine();

                    //Write Data
                    rowCount = 2;
                    while (!string.IsNullOrEmpty(itemPartNumber = Convert.ToString(((Excel.Range)sheet.Cells[rowCount, 1]).Value2)))
                    {
                        for (int i = 2; i < colCount + 1; i++)
                        {
                            if (i != 3)
                            {
                                itemPartNumber = Convert.ToString(((Excel.Range)sheet.Cells[rowCount, i]).Value2);
                                sr.Write(itemPartNumber);
                                sr.Write(" ");
                            }
                        }
                        sr.WriteLine();
                        sr.WriteLine();
                        rowCount++;
                    }

                }
                MessageBox.Show("Features Successfully saved to " + textSheet, "Information", MessageBoxButtons.OK, MessageBoxIcon.Information);
                app.Quit();
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private string determineName(string excelTitle, ref int colCount)
        {
            string textTitle, tempTitle;
            int pFrom, pTo;
            //Check Projection
            if (excelTitle.Contains("Projection"))
                tempTitle = "Projection";
            else if (excelTitle.Contains("Average"))
                tempTitle = "Texture";
            else if (excelTitle.Substring(excelTitle.Length - 1, 1) == "R")
                tempTitle = excelTitle.Replace("_R", "_Band0");
            else if (excelTitle.Substring(excelTitle.Length - 1, 1) == "G")
                tempTitle = excelTitle.Replace("_G", "_Band1");
            else if (excelTitle.Substring(excelTitle.Length - 1, 1) == "B")
                tempTitle = excelTitle.Replace("_B", "_Band2");
            else
                tempTitle = excelTitle;

            switch (tempTitle)
            {
                case "Name":
                    textTitle = "Image Name";
                    break;
                case "Row":
                    textTitle = "Object's Row Coordinate";
                    break;
                case "Column":
                    textTitle = "Object's Column Coordinate";
                    break;
                case "Centroid_Row":
                    textTitle = "Centroid (Row, Column)";
                    colCount++;
                    break;
                case "Orientation":
                    textTitle = "Orientation (Axis of Least Second Moment)";
                    break;
                case "Projection":
                    pFrom = excelTitle.IndexOf("(") + "(".Length;
                    pTo = excelTitle.LastIndexOf(",");
                    String height = excelTitle.Substring(pFrom, pTo - pFrom);
                    pFrom = excelTitle.IndexOf(",") + ",".Length;
                    pTo = excelTitle.LastIndexOf(")");
                    String width = excelTitle.Substring(pFrom, pTo - pFrom);
                    textTitle = "Projection (Height: " + height + "  Width:" + width + ")";
                    colCount = colCount + int.Parse(height) + int.Parse(width) - 1;
                    break;
                case "Texture":
                    pFrom = excelTitle.IndexOf("(") + "(".Length;
                    pTo = excelTitle.LastIndexOf(",");
                    String distance = excelTitle.Substring(pFrom, pTo - pFrom);
                    pFrom = excelTitle.IndexOf(",") + ",".Length;
                    pTo = excelTitle.LastIndexOf(")");
                    String includeZero = excelTitle.Substring(pFrom, pTo - pFrom);
                    textTitle = excelTitle.Substring(0, excelTitle.IndexOf("(")) + "(Texture Distance: " + distance + "  IncludeZeroPairs: " + includeZero + ")";
                    break;
                default:
                    textTitle = tempTitle;
                    break;
            }
            return textTitle;
        }
    }
}
