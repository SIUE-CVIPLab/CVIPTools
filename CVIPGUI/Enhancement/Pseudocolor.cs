/*''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' ======================================================================
' Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
' ======================================================================
'
'             File Name: Pseudocolor.cs
'           Description: Contains the controls and code
'                        for Enhancement->Pseudocolor tab
'         Related Files: CvipOp.cs
'                        CvipConstant.cs
'   Initial Coding Date: June 2007
'              Modified: November 2011
'       Delevoping tool: Visual Studio 2010-C#
'             Credit(s): Wenjun(Evan) Bian
'                        Patrick Solt,Hari Siva Kumar Reddy Bhogala
							
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

namespace CVIPGUI.Enhancement
{
    enum PseudoSelection
    {
        GrayLevelMap,
        FreqMap,
        IntensitySlice,
        Pseudo_Remap
    }

    public partial class Pseudocolor : UserControl
    {
        private PseudoSelection currentSelection;

        public Pseudocolor()
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
            case PseudoSelection.GrayLevelMap:
                if (viewer.Bands != 1)
                {
                    MessageBox.Show("The input image must be a gray scale image.",
                        "Input image error", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    break;
                }
                outputImage = CvipOp.Graylevel_Remap(inputImage, this.cboRed.SelectedIndex, this.cboGreen.SelectedIndex, this.cboBlue.SelectedIndex);
                break;

            case PseudoSelection.FreqMap:
                if (viewer.Bands != 1)
                {
                    MessageBox.Show("The input image must be a gray scale image.",
                        "Input image error", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    break;
                }
                if ((this.cboLowpassColor.Text == this.cboBandpassColor.Text) ||
                    (this.cboLowpassColor.Text == this.cboHighpassColor.Text) ||
                    (this.cboBandpassColor.Text == this.cboHighpassColor.Text))
                {
                    MessageBox.Show("Please use different colors for different bands.",
                        "Image band error", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    break;
                }
                outputImage = CvipOp.Pseudocol_Freq(inputImage, this.LowCutoff, this.HighCutoff, this.cboLowpassColor.SelectedIndex, this.cboBandpassColor.SelectedIndex, this.cboHighpassColor.SelectedIndex);
                break;

            case PseudoSelection.IntensitySlice:
                if (viewer.Bands != 1)
                {
                    MessageBox.Show("The input image must be a gray scale image.",
                        "Input image error", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    break;
                }
                int[] table = this.LookupTable;
                outputImage = CvipOp.Intensity_Slicing(inputImage, ref table[0], this.chkZeroDataOOR.Checked ? 1 : 0);
                break;

            case PseudoSelection.Pseudo_Remap:
                FileInfo fiMapFile = this.cboMappingFile.SelectedItem as FileInfo;
                if (fiMapFile == null)
                {
                    MessageBox.Show("Please select a map file first.",
                        "Map File", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    break;
                }
                fiMapFile.Refresh();
                if (!fiMapFile.Exists)
                {
                    MessageBox.Show("The file: " + fiMapFile.FullName + " is missing.",
                        "File Not Found", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    RefreshMapfileList();
                    break;
                }
                using (FileStream fs = fiMapFile.OpenRead())
                {
                    int[] nMapData = new int[768];
                    for (int i = 0; i < 768; i++)
                    {
                        nMapData[i] = (int)fs.ReadByte();
                    }
                    outputImage = CvipOp.P_Remap(inputImage, nMapData);
                }
                break;
            }
            if (outputImage != 0)
            {
                string newImageName = viewer.Text + "_" + CvipFunctionNames.getFncName(this.currentSelection.ToString());
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
            MainForm.EnhancementForm.Close();
        }
        private void btnCustomRemapCurve_Click(object sender, EventArgs e)
        {
            CustomRemapForm frm = MainForm.ShowCustomRemapForm();
            if (frm != null)
                frm.MapFileCollectionChanged += this.RefreshMapfileList;
        }
        private void btnHelp_Click(object sender, EventArgs e)
        {
            MainForm.ShowHelp();
        }
        private void btnLoadMappingFile_Click(object sender, EventArgs e)
        {
            string cvipHome = MainForm.CVIPtoolsHOME;
            if (string.IsNullOrEmpty(cvipHome))
            {
                MessageBox.Show("This operation cannot be completed. The CVIPtoolsHOME environment variable is not set.",
                    "CVIPtoolsHOME", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                return;
            }
            DirectoryInfo diMapDirectory = new DirectoryInfo(cvipHome + @"bin\remap");
            if (!diMapDirectory.Exists)
                diMapDirectory.Create();

            OpenFileDialog dlg = new OpenFileDialog();
            dlg.Title = "Load Pseudo Color Map";
            dlg.Filter = "Color Map File(*.map)|*.map";
            dlg.FilterIndex = 1;
            dlg.InitialDirectory = diMapDirectory.FullName;

            if (dlg.ShowDialog() == DialogResult.OK)
            {
                FileInfo fi = new FileInfo(dlg.FileName);
                if (fi.DirectoryName.ToLower().TrimEnd('\\') != diMapDirectory.FullName.ToLower().TrimEnd('\\'))
                {
                    FileInfo fiMap = new FileInfo(diMapDirectory.FullName.TrimEnd('\\') + @"\" + fi.Name);
                    if (fiMap.Exists)
                    {
                        string title = "Load Map File";
                        string msg = "File " + fiMap.FullName + " already exists.\n";
                        msg += "Do you want to replace it?";
                        if (MessageBox.Show(msg, title, MessageBoxButtons.YesNo, MessageBoxIcon.Warning) == DialogResult.No)
                        {
                            return;
                        }
                        fiMap.Delete();
                    }
                    fi.CopyTo(fiMap.FullName);
                }
                RefreshMapfileList();
                for (int i = 0; i < this.cboMappingFile.Items.Count; i++)
                {
                    if ((this.cboMappingFile.Items[i] as FileInfo).Name.ToLower() == fi.Name.ToLower())
                    {
                        this.cboMappingFile.SelectedIndex = i;
                        break;
                    }
                }
            }
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
        private void cboRemap_DrawItem(object sender, DrawItemEventArgs e)
        {
            if (e.Index != -1)
            {
                e.Graphics.DrawImage(ilRemapCurves.Images[e.Index], e.Bounds.Location);
            }
        }
        protected override void OnLoad(EventArgs e)
        {
            base.OnLoad(e);

            this.rbGrayLevelMap.Tag = PseudoSelection.GrayLevelMap;
            this.rbFreqDomainMap.Tag = PseudoSelection.FreqMap;
            this.rbIntensitySlice.Tag = PseudoSelection.IntensitySlice;
            this.rbGrayLevelMapII.Tag = PseudoSelection.Pseudo_Remap;

            ResetControls();
        }
        private void rbPseudocolor_Click(object sender, EventArgs e)
        {
            RadioButton rb = sender as RadioButton;
            if ((rb != null) && rb.Checked && (rb.Tag != null))
                this.currentSelection = (PseudoSelection)rb.Tag;
            UpdateControls();
        }
        private void RefreshMapfileList()
        {
            this.cboMappingFile.Items.Clear();

            string cvipHome = MainForm.CVIPtoolsHOME;
            DirectoryInfo diMapDirectory = new DirectoryInfo(cvipHome + @"bin\remap");
            if (!string.IsNullOrEmpty(cvipHome) && diMapDirectory.Exists)
            {
                foreach (FileInfo fiMap in diMapDirectory.GetFiles("*.map"))
                {
                    this.cboMappingFile.Items.Add(fiMap);
                }
            }
            if (this.cboMappingFile.Items.Count > 0)
                this.cboMappingFile.SelectedIndex = 0;
        }
        private void ResetControls()
        {
            // GrayLevelMap panel
            this.cboRed.SelectedIndex = 0;
            this.cboGreen.SelectedIndex = 1;
            this.cboBlue.SelectedIndex = 2;

            // FreqDomain panel
            this.cboLowpassColor.SelectedIndex = 0;
            this.cboBandpassColor.SelectedIndex = 1;
            this.cboHighpassColor.SelectedIndex = 2;
            this.cboLowCutoff.Text = "10";
            this.cboHighCutoff.Text = "100";

            // IntensitySlice panel
            this.chkZeroDataOOR.Checked = false;

            this.cboRange1From.Text = "0";
            this.cboRange1To.Text = "63";
            this.cboRange1Red.Text = "255";
            this.cboRange1Green.Text = "0";
            this.cboRange1Blue.Text = "0";

            this.cboRange2From.Text = "64";
            this.cboRange2To.Text = "127";
            this.cboRange2Red.Text = "0";
            this.cboRange2Green.Text = "255";
            this.cboRange2Blue.Text = "0";

            this.cboRange3From.Text = "128";
            this.cboRange3To.Text = "191";
            this.cboRange3Red.Text = "0";
            this.cboRange3Green.Text = "0";
            this.cboRange3Blue.Text = "255";

            this.cboRange4From.Text = "192";
            this.cboRange4To.Text = "255";
            this.cboRange4Red.Text = "255";
            this.cboRange4Green.Text = "255";
            this.cboRange4Blue.Text = "255";

            // GrayLevelMapII panel
            RefreshMapfileList();

            // Default current selection
            this.rbGrayLevelMap.PerformClick();

            // enable Apply button
            this.btnApply.Enabled = true;
            this.Cursor = Cursors.Default;
        }
        private void UpdateControls()
        {
            switch (this.currentSelection)
            {
            case PseudoSelection.GrayLevelMap:
                this.pnlGrayLevelMap.Visible = true;
                this.pnlFreqDomainMap.Visible = false;
                this.pnlIntensitySlice.Visible = false;
                this.pnlGrayLevelMapII.Visible = false;
                this.btnCustomRemapCurve.Visible = false;
                break;

            case PseudoSelection.FreqMap:
                this.pnlGrayLevelMap.Visible = false;
                this.pnlFreqDomainMap.Visible = true;
                this.pnlIntensitySlice.Visible = false;
                this.pnlGrayLevelMapII.Visible = false;
                this.btnCustomRemapCurve.Visible = false;
                break;

            case PseudoSelection.IntensitySlice:
                this.pnlGrayLevelMap.Visible = false;
                this.pnlFreqDomainMap.Visible = false;
                this.pnlIntensitySlice.Visible = true;
                this.pnlGrayLevelMapII.Visible = false;
                this.btnCustomRemapCurve.Visible = false;
                break;

            case PseudoSelection.Pseudo_Remap:
                this.pnlGrayLevelMap.Visible = false;
                this.pnlFreqDomainMap.Visible = false;
                this.pnlIntensitySlice.Visible = false;
                this.pnlGrayLevelMapII.Visible = true;
                this.btnCustomRemapCurve.Visible = true;
                break;
            }
            // enable Apply button
            this.btnApply.Enabled = true;
            this.Cursor = Cursors.Default;
        }
        protected override void WndProc(ref Message m)
        {
            switch ((WM)m.Msg)
            {
            case WM.DESTROY:
                if (MainForm.CustomRemapForm != null)
                    MainForm.CustomRemapForm.MapFileCollectionChanged -= this.RefreshMapfileList;
                break;
            }
            base.WndProc(ref m);
        }

        private int LowCutoff { get { return int.Parse(this.cboLowCutoff.Text); } }
        private int HighCutoff { get { return int.Parse(this.cboHighCutoff.Text); } }
        private int[] LookupTable
        {
            get
            {
                int[] table = new int[20];

                table[0] = int.Parse(this.cboRange1From.Text);
                table[1] = int.Parse(this.cboRange1To.Text);
                table[2] = int.Parse(this.cboRange2From.Text);
                table[3] = int.Parse(this.cboRange2To.Text);
                table[4] = int.Parse(this.cboRange3From.Text);
                table[5] = int.Parse(this.cboRange3To.Text);
                table[6] = int.Parse(this.cboRange4From.Text);
                table[7] = int.Parse(this.cboRange4To.Text);
                table[8] = int.Parse(this.cboRange1Red.Text);
                table[9] = int.Parse(this.cboRange1Green.Text);
                table[10] = int.Parse(this.cboRange1Blue.Text);
                table[11] = int.Parse(this.cboRange2Red.Text);
                table[12] = int.Parse(this.cboRange2Green.Text);
                table[13] = int.Parse(this.cboRange2Blue.Text);
                table[14] = int.Parse(this.cboRange3Red.Text);
                table[15] = int.Parse(this.cboRange3Green.Text);
                table[16] = int.Parse(this.cboRange3Blue.Text);
                table[17] = int.Parse(this.cboRange4Red.Text);
                table[18] = int.Parse(this.cboRange4Green.Text);
                table[19] = int.Parse(this.cboRange4Blue.Text);

                return table;
            }
        }

      
    }
}
