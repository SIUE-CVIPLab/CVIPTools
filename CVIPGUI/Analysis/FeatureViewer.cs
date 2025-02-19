/*''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' ======================================================================
' Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
' ======================================================================
'
'             File Name: FeatureViewer.cs
'           Description: Contains the controls and code
'                        for Analysis->FeatureViewer page
'         Related Files: Features.cs
'                        Classification.cs
'                        CvipOp.cs
'   Initial Coding Date: August 2009
'              Modified: June 2010
'       Delevoping tool: Visual Studio 2010-C#
'             Credit(s): Patrick Solt
'                        Jhansi Lakshmi Akkineni
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
    public partial class FeatureViewer : Form
    {
        FeatureFile ffFeatures = null;
        ListViewItem[] lvDest;
        ListView lvUndo;

        public FeatureViewer()
        {
            InitializeComponent();
            this.MdiParent = MainForm.TheMainForm;
        }

        private void btnClose_Click(object sender, EventArgs e)
        {
            this.Hide();
        }

        private void btnSaveAsExcel_Click(object sender, EventArgs e)
        {
            String dirFeatures = MainForm.CVIPtoolsHOME;
            if (!string.IsNullOrEmpty(dirFeatures))
                dirFeatures += @"bin\feature";

            SaveFileDialog dlgFileSave = new SaveFileDialog();
            dlgFileSave.Filter = "All Files(*.*)|*.*" + "Excel Workbook (*.xlsx)|*.xlsx|";
            dlgFileSave.FilterIndex = 2;
            dlgFileSave.InitialDirectory = dirFeatures;
            dlgFileSave.OverwritePrompt = false;
            dlgFileSave.Title = "Choose Excel Filename";
            if (dlgFileSave.ShowDialog() == DialogResult.OK)
            {
                if (File.Exists(dlgFileSave.FileName))
                {
                    string title = "Save as";
                    string msg = "File " + dlgFileSave.FileName + " already exists.\n";
                    msg += "Do you want to replace it?";
                    MessageBoxButtons buttons = MessageBoxButtons.YesNo;
                    MessageBoxIcon icon = MessageBoxIcon.Warning;
                    if (MessageBox.Show(msg, title, buttons, icon) == DialogResult.No)
                        return;
                    File.Delete(dlgFileSave.FileName);
                }

                Excel.ApplicationClass app = new Microsoft.Office.Interop.Excel.ApplicationClass();
                Excel.Worksheet sheet = new Microsoft.Office.Interop.Excel.Worksheet();
                Excel.Workbook book = null;
                try
                {
                    book = app.Workbooks.Add(Type.Missing);
                    sheet = (Excel.Worksheet)book.ActiveSheet;
                    sheet = (Excel.Worksheet)book.Sheets[1];
                    sheet.Name = "Features";

                    for (int i = 0; i < this.lvFeatures.Columns.Count; i++)
                    {
                        sheet.Cells[1, i + 1] = this.lvFeatures.Columns[i].Text;
                        ((Excel.Range)sheet.Cells[1, i + 1]).EntireRow.Font.Bold = true;
                    }
                    for (int i = 0; i < this.lvFeatures.Items.Count; i++)
                    {
                        ListViewItem item = this.lvFeatures.Items[i];
                        for (int j = 0; j < item.SubItems.Count; j++)
                        {
                            sheet.Cells[i + 2, j + 1] = item.SubItems[j].Text;
                        }
                    }
                    sheet.Columns.Font.Name = "Arial";
                    sheet.Columns.AutoFit();
                    book.SaveAs(dlgFileSave.FileName, Type.Missing, Type.Missing, Type.Missing, false, Type.Missing, Microsoft.Office.Interop.Excel.XlSaveAsAccessMode.xlExclusive, Type.Missing, Type.Missing, Type.Missing, Type.Missing, Type.Missing);
                    string ext = (dlgFileSave.FilterIndex == 2) ? ".xlsx" : "";
                    MessageBox.Show("Features Successfully saved to " + dlgFileSave.FileName + ext,
                        "Information", MessageBoxButtons.OK, MessageBoxIcon.Information);
                    app.Quit();
                }
                catch (Exception ex)
                {
                    MessageBox.Show(ex.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                }
            }
        }

        private void grpButtons_Resize(object sender, EventArgs e)
        {
            Point pt = new Point(0, 0);
            pt.X = this.grpButtons.Size.Width - 105;
            pt.Y = this.grpButtons.Size.Height - 25;
            this.btnSaveAsExcel.Location = pt;
        }

        private void mnuCopy_Click(object sender, EventArgs e)
        {
            this.lvUndo = new ListView();
            for (int i = 0; i < this.lvFeatures.Items.Count; i++)
            {
                ListViewItem item = (ListViewItem)this.lvFeatures.Items[i].Clone();
                this.lvUndo.Items.Add(item);
            }
            this.lvDest = new ListViewItem[this.lvFeatures.SelectedItems.Count];
            this.lvFeatures.SelectedItems.CopyTo(this.lvDest, 0);
            this.mnuPaste.Enabled = true;
            this.mnuUndo.Enabled = true;
        }

        private void mnuCut_Click(object sender, EventArgs e)
        {
            this.lvUndo = new ListView();
            for (int i = 0; i < this.lvFeatures.Items.Count; i++)
            {
                ListViewItem item = (ListViewItem)this.lvFeatures.Items[i].Clone();
                this.lvUndo.Items.Add(item);
            }
            this.lvDest = new ListViewItem[this.lvFeatures.SelectedItems.Count];
            this.lvFeatures.SelectedItems.CopyTo(this.lvDest, 0);
            for (int i = this.lvFeatures.SelectedItems.Count; i > 0; i--)
                this.lvFeatures.SelectedItems[i - 1].Remove();
            this.mnuPaste.Enabled = true;
            this.mnuUndo.Enabled = true;
        }

        private void mnuDelete_Click(object sender, EventArgs e)
        {
            this.lvUndo = new ListView();
            for (int i = 0; i < this.lvFeatures.Items.Count; i++)
            {
                ListViewItem item = (ListViewItem)this.lvFeatures.Items[i].Clone();
                this.lvUndo.Items.Add(item);
            }
            for (int i = this.lvFeatures.SelectedItems.Count; i > 0; i--)
                this.lvFeatures.SelectedItems[i - 1].Remove();
            this.mnuUndo.Enabled = true;
            this.mnuPaste.Enabled = false;
        }

        private void mnuPaste_Click(object sender, EventArgs e)
        {
            this.lvUndo = new ListView();
            for (int i = 0; i < this.lvFeatures.Items.Count; i++)
            {
                ListViewItem item = (ListViewItem)this.lvFeatures.Items[i].Clone();
                this.lvUndo.Items.Add(item);
            }
            for (int i = 0; i < this.lvDest.Length; i++)
            {
                ListViewItem temp = (ListViewItem)this.lvDest[i].Clone();
                this.lvFeatures.Items.Add(temp);
            }
            this.mnuPaste.Enabled = false;
            this.mnuUndo.Enabled = true;
        }

        private void mnuSelectAll_Click(object sender, EventArgs e)
        {
            for (int i = 0; i < this.lvFeatures.Items.Count; i++)
                this.lvFeatures.Items[i].Selected = true;
        }

        private void mnuUndo_Click(object sender, EventArgs e)
        {
            ListViewItem[] items = new ListViewItem[this.lvUndo.Items.Count];
            this.lvUndo.Items.CopyTo(items, 0);
            this.lvUndo.Clear();
            this.lvUndo = new ListView();
            for (int i = 0; i < this.lvFeatures.Items.Count; i++)
            {
                ListViewItem item = (ListViewItem)this.lvFeatures.Items[i].Clone();
                this.lvUndo.Items.Add(item);
            }
            this.lvFeatures.Items.Clear();
            this.lvFeatures.Items.AddRange(items);
        }

        public void Show(FeatureFile ff)
        {
            this.FeatureFile = ff;
            this.Show();
            this.BringToFront();
        }

        public FeatureFile FeatureFile
        {
            get { return this.ffFeatures; }
            set
            {
                this.ffFeatures = value;
                try
                {
                    int idx = 0;
                    FeatureHeader fh = this.ffFeatures.FeatureHeader;

                    this.lvFeatures.Items.Clear();
                    this.lvFeatures.Columns.Clear();
                    this.lvFeatures.Columns.Add("S.No");
                    this.lvFeatures.Columns[idx++].Width = 50;
                    this.lvFeatures.Columns.Add("Name");
                    this.lvFeatures.Columns[idx++].Width = 70;
                    this.lvFeatures.Columns.Add("Bands");
                    this.lvFeatures.Columns[idx++].Width = 70;
                    this.lvFeatures.Columns.Add("Row");
                    this.lvFeatures.Columns[idx++].Width = 50;
                    this.lvFeatures.Columns.Add("Column");
                    this.lvFeatures.Columns[idx++].Width = 60;

                    // Binary object features
                    if (fh.UseArea)
                    {
                        this.lvFeatures.Columns.Add("Area");
                        this.lvFeatures.Columns[idx++].Width = 70;
                    }
                    if (fh.UseCentroid)
                    {
                        this.lvFeatures.Columns.Add("Centroid_Row");
                        this.lvFeatures.Columns[idx++].Width = 100;
                        this.lvFeatures.Columns.Add("Centroid_Col");
                        this.lvFeatures.Columns[idx++].Width = 100;
                    }
                    if (fh.UseOrientation)
                    {
                        this.lvFeatures.Columns.Add("Orientation");
                        this.lvFeatures.Columns[idx++].Width = 90;
                    }
                    if (fh.UsePerimeter)
                    {
                        this.lvFeatures.Columns.Add("Perimeter");
                        this.lvFeatures.Columns[idx++].Width = 90;
                    }
                    if (fh.UseEuler)
                    {
                        this.lvFeatures.Columns.Add("Euler Number");
                        this.lvFeatures.Columns[idx++].Width = 90;
                    }
                    if (fh.UseProjections)
                    {
                        for (int i = 0; i < (fh.ProjectionsHeight + fh.ProjectionsWidth); i++)
                        {
                            this.lvFeatures.Columns.Add("Projections_" + "(" + fh.ProjectionsHeight + "," + fh.ProjectionsWidth + ")" + (i + 1));
                            this.lvFeatures.Columns[idx++].Width = 100;
                        }
                    }
                    if (fh.UseThinness)
                    {
                        this.lvFeatures.Columns.Add("Thinness");
                        this.lvFeatures.Columns[idx++].Width = 90;
                    }
                    if (fh.UseAspectRatio)
                    {
                        this.lvFeatures.Columns.Add("Aspect Ratio");
                        this.lvFeatures.Columns[idx++].Width = 90;
                    }
                    // RST-Invariant Moment-Based features
                    for (int i = 0; i < 7; i++)
                    {
                        if (fh.UseRst[i])
                        {
                            this.lvFeatures.Columns.Add("RST" + (i + 1).ToString());
                            this.lvFeatures.Columns[idx++].Width = 70;
                        }
                    }
                   
                    // Histogram features
                    for (int i = 0; i < 5; i++)
                    {
                        if (fh.UseHist[i])
                        {
                            string s = null;
                            switch (i)
                            {
                            case 0: s = "Histo_Mean"; break;
                            case 1: s = "Histo_Standard_Deviation"; break;
                            case 2: s = "Histo_Skew"; break;
                            case 3: s = "Histo_Energy"; break;
                            case 4: s = "Histo_Entropy"; break;
                            }
                            switch (fh.Bands)
                            {
                            case 1:
                                this.lvFeatures.Columns.Add(s);
                                this.lvFeatures.Columns[idx++].Width = 100;
                                break;
                            case 3:
                                this.lvFeatures.Columns.Add(s + "_R");
                                this.lvFeatures.Columns[idx++].Width = 100;
                                this.lvFeatures.Columns.Add(s + "_G");
                                this.lvFeatures.Columns[idx++].Width = 100;
                                this.lvFeatures.Columns.Add(s + "_B");
                                this.lvFeatures.Columns[idx++].Width = 100;
                                break;
                            }
                        }
                    }
                    // Texture features
                    for (int i = 0; i < 5; i++)
                    {
                        if (fh.UseTexture[i])
                        {
                            string s = null;
                            switch (i)
                            {
                            case 0: s = "Texture Energy"; break;
                            case 1: s = "Inertia"; break;
                            case 2: s = "Correlation"; break;
                            case 3: s = "Inverse Diff"; break;
                            case 4: s = "Texture Entropy"; break;
                            }
                            this.lvFeatures.Columns.Add(s + " Average (" + fh.TextureDistance + "," + fh.TextureUseZeros.ToString() + ")");
                            this.lvFeatures.Columns[idx++].Width = 120;
                            this.lvFeatures.Columns.Add(s + " Range");
                            this.lvFeatures.Columns[idx++].Width = 120;
                        }
                    }
                    //law texture
                    for (int i = 0; i < 15; i++)
                    {
                        if (fh.UseLaw[i])
                        {
                            string s = null;
                            string s1 = null;
                            if (i == 0) s = "LevelLevel";
                            else if (i == 1) s = "LevelEdge";
                            else if (i == 2) s = "LevelSpot";
                            else if (i == 3) s = "LevelRipple";
                            else if (i == 4) s = "LevelWave";
                            else if (i == 5) s = "EdgeEdge";
                            else if (i == 6) s = "Edgespot";
                            else if (i == 7) s = "EdgeRipple";
                            else if (i == 8) s = "EdgeWave";
                            else if (i == 9) s = "SpotSpot";
                            else if (i == 10) s = "SpotRipple";
                            else if (i == 11) s = "SpotWave";
                            else if (i == 12) s = "WaveRipple";
                            else if (i == 13) s = "WaveWave";
                            else if (i == 14) s = "RippleRipple";
                            for (int j = 0; j < 5; j++)
                            {
                                s1 = "";
                                switch (j)
                                {
                                    case 0: s1 = s1 + "_Mean"; break;
                                    case 1: s1 = s1 + "_Standard_Deviation"; break;
                                    case 2: s1 = s1 + "_Skew"; break;
                                    case 3: s1 = s1 + "_Energy"; break;
                                    case 4: s1 = s1 + "_Entropy"; break;
                                }
                                switch (fh.Bands)
                                {
                                    case 1:
                                        this.lvFeatures.Columns.Add(s+s1);
                                        this.lvFeatures.Columns[idx++].Width = 100;
                                        break;
                                    case 3:
                                        this.lvFeatures.Columns.Add(s+s1 + "_R");
                                        this.lvFeatures.Columns[idx++].Width = 100;
                                        this.lvFeatures.Columns.Add(s +s1+ "_G");
                                        this.lvFeatures.Columns[idx++].Width = 100;
                                        this.lvFeatures.Columns.Add(s +s1+ "_B");
                                        this.lvFeatures.Columns[idx++].Width = 100;
                                        break;
                                }
                            }
                        }
                    }
                    // Spectral features
                    if (fh.UseSpectral)
                    {
                        switch (fh.Bands)
                        {
                        case 1:
                            this.lvFeatures.Columns.Add("Spectral_DC");
                            this.lvFeatures.Columns[idx++].Width = 100;
                            for (int i = 1; i <= fh.SpectralRings; i++)
                            {
                                this.lvFeatures.Columns.Add("Ring" + i);
                                this.lvFeatures.Columns[idx++].Width = 70;
                            }
                            for (int i = 1; i <= fh.SpectralSectors; i++)
                            {
                                this.lvFeatures.Columns.Add("Sector" + i);
                                this.lvFeatures.Columns[idx++].Width = 70;
                            }
                            break;
                        case 3:
                            this.lvFeatures.Columns.Add("Spectral_DC_R");
                            this.lvFeatures.Columns[idx++].Width = 100;
                            for (int i = 1; i <= fh.SpectralRings; i++)
                            {
                                this.lvFeatures.Columns.Add("Ring" + i + "_R");
                                this.lvFeatures.Columns[idx++].Width = 70;
                            }
                            for (int i = 1; i <= fh.SpectralSectors; i++)
                            {
                                this.lvFeatures.Columns.Add("Sector" + i + "_R");
                                this.lvFeatures.Columns[idx++].Width = 70;
                            }
                            this.lvFeatures.Columns.Add("Spectral_DC_G");
                            this.lvFeatures.Columns[idx++].Width = 100;
                            for (int i = 1; i <= fh.SpectralRings; i++)
                            {
                                this.lvFeatures.Columns.Add("Ring" + i + "_G");
                                this.lvFeatures.Columns[idx++].Width = 70;
                            }
                            for (int i = 1; i <= fh.SpectralSectors; i++)
                            {
                                this.lvFeatures.Columns.Add("Sector" + i + "_G");
                                this.lvFeatures.Columns[idx++].Width = 70;
                            }
                            this.lvFeatures.Columns.Add("Spectral_DC_B");
                            this.lvFeatures.Columns[idx++].Width = 100;
                            for (int i = 1; i <= fh.SpectralRings; i++)
                            {
                                this.lvFeatures.Columns.Add("Ring" + i + "_B");
                                this.lvFeatures.Columns[idx++].Width = 70;
                            }
                            for (int i = 1; i <= fh.SpectralSectors; i++)
                            {
                                this.lvFeatures.Columns.Add("Sector" + i + "_B");
                                this.lvFeatures.Columns[idx++].Width = 70;
                            }
                            break;
                        }
                    }
                    this.lvFeatures.Columns.Add("ClassName");
                    this.lvFeatures.Columns[idx++].Width = 90;

                    idx = 1;
                    foreach (CvipObject obj in this.ffFeatures)
                    {
                        ListViewItem item = new ListViewItem(idx++.ToString());
                        item.SubItems.Add(obj.Name);
                        item.SubItems.Add(fh.Bands.ToString());
                        item.SubItems.Add(obj.Row);
                        item.SubItems.Add(obj.Col);

                        // Binary object features
                        if (fh.UseArea)
                            item.SubItems.Add(obj.Area);
                        if (fh.UseCentroid)
                        {
                            item.SubItems.Add(obj.CentroidRow);
                            item.SubItems.Add(obj.CentroidCol);
                        }
                        if (fh.UseOrientation)
                            item.SubItems.Add(obj.Orientation);
                        if (fh.UsePerimeter)
                            item.SubItems.Add(obj.Perimeter);
                        if (fh.UseEuler)
                            item.SubItems.Add(obj.Euler);
                        if (fh.UseProjections)
                        {
                            for (int i = 0; i < (fh.ProjectionsHeight + fh.ProjectionsWidth); i++)
                                item.SubItems.Add(obj.Projections[i]);
                        }
                        if (fh.UseThinness)
                            item.SubItems.Add(obj.Thinness);
                        if (fh.UseAspectRatio)
                            item.SubItems.Add(obj.AspectRatio);

                        // RST-Invariant Moment-Based features
                        for (int i = 0; i < 7; i++)
                        {
                            if (fh.UseRst[i])
                                item.SubItems.Add(obj.Rst[i]);
                        }
                       
                        // Histogram features
                        for (int i = 0; i < 5; i++)
                        {
                            if (fh.UseHist[i])
                            {
                                for (int j = 0; j < fh.Bands; j++)
                                    item.SubItems.Add(obj.Hist[i, j]);
                            }
                        }
                       
                        // Texture features
                        for (int i = 0; i < 5; i++)
                        {
                            if (fh.UseTexture[i])
                            {
                                item.SubItems.Add(obj.Texture[i, 0]);
                                item.SubItems.Add(obj.Texture[i, 1]);
                            }
                        }
                        //law textures
                        for (int i = 0; i < 15; i++)
                        {
                            if (fh.UseLaw[i])
                            {
                                for (int j = 0; j < 5; j++)
                                    for (int k = 0; k < fh.Bands; k++)
                                    {
                                        item.SubItems.Add(obj.law[i, j, k]);


                                    }
                            }
                        }
                        // Spectral features
                        if (fh.UseSpectral)
                        {
                            for (int i = 0; i < fh.Bands; i++)
                            {
                                item.SubItems.Add(obj.SpectralDC[i]);
                                for (int j = 0; j < fh.SpectralRings; j++)
                                    item.SubItems.Add(obj.SpectralRings[i, j]);
                                for (int j = 0; j < fh.SpectralSectors; j++)
                                    item.SubItems.Add(obj.SpectralSectors[i, j]);
                            }
                        }
                        // Class Name
                        item.SubItems.Add(obj.ClassName);
                        this.lvFeatures.Items.Add(item);
                    }
                }
                catch (Exception ex)
                {
                    MessageBox.Show("Unhandled exception: " + ex.Message,
                        "FeatureViewer.FeatureFile", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                }
            }
        }

       
    }
}
