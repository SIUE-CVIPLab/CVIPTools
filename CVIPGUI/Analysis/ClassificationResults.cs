/*''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' ======================================================================
' Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
' ======================================================================
'
'             File Name: ClassificationResults.cs
'           Description: Contains the controls and code
'                        for Analysis->ClassificationResults page
'         Related Files: Classification.cs
'                        CvipOp.cs
'   Initial Coding Date: September 2009
'              Modified: March 2010
'       Delevoping tool: Visual Studio 2010-C#
'             Credit(s): Patrick Solt
'                        Jhansi Lakshmi Akkineni
'                        Southern Illinois University Edwardsville
'
' Copyright (C) 2014 Scott Umbaugh and SIUE
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

namespace CVIPGUI.Analysis
{
    public partial class ClassificationResults : Form
    {
        int tmpcount;
        public ClassificationResults()
        {
            InitializeComponent();
            this.MdiParent = MainForm.TheMainForm;
        }

        private void ok_Click(object sender, EventArgs e)
        {
            this.Hide();
        }

        public void open(string outputFile)
        {
            try
            {
                using (StreamReader sr = File.OpenText(outputFile))
                {
                    string txtoutput = "", tmpheader, tmpfield, features_text,output_file="";
                    dGVResults.Columns.Clear();
                    dGVResults1.Columns.Clear();
                    DataSet ds = new DataSet();
                    DataRow dtRow1;
                    DataTable dt1 = new DataTable("dt1");
                    DataTable dt2 = new DataTable("dt2");
                    DataTable dt3 = new DataTable("dt3");
                    txtoutput = sr.ReadToEnd();
                    int idx;
                    if (!string.IsNullOrEmpty(txtoutput))
                    {
                        idx = txtoutput.IndexOf("*** END OF HEADER; CLASS (optional) SHOWN AT THE END OF DATA ***");
                        features_text = txtoutput.Substring(0, idx);
                        txtoutput = txtoutput.Substring(idx).Trim();
                        dt1.Columns.Add("Classification Algorithm");
                        dt1.Columns.Add("Data Normalization");
                        dt1.Columns.Add("Distance Measure");
                        dt1.Columns.Add("Test Set File");
                        dt1.Columns.Add("Training Set File");
                        dt1.Columns.Add("Output File");
                        txtoutput = txtoutput.Trim();
                        if ((idx = txtoutput.IndexOf("Classification Algorithm:")) >= 0)
                        {
                            txtoutput = txtoutput.Substring(idx).Trim();
                        }
                        try
                        {
                            //Adding DataRow to the data table 1
                            dtRow1 = dt1.NewRow();
                            for (int i = 0; output_file != "Output File"||i<6; i++)    //if we use normalization then normalized files will be their in output to remove use if stmts in this blog
                            {
                                idx = txtoutput.IndexOf(':');
                                output_file = txtoutput.Substring(0, idx);
                                txtoutput = txtoutput.Substring(idx + 1).Trim();
                                idx = txtoutput.IndexOf("\r");
                                tmpfield = txtoutput.Substring(0, idx);
                                if (output_file == "Normalized Training Set File")         
                                { i--; }
                                else if(output_file == "Normalized Test Set File")
                                { i--; } 


                                else if (output_file == "Centroid Training Set File")
                                { i--; }
                                else
                                { dtRow1[i] = tmpfield; }
                                txtoutput = txtoutput.Substring(idx).Trim();
                            }
                            dt1.Rows.Add(dtRow1);
                            // Features Header
                            dtRow1 = dt1.NewRow();
                            dt1.Rows.Add(dtRow1);
                            tmpcount = 0;
                            while (idx > 0)
                            {
                                dtRow1 = dt1.NewRow();
                                for (int i = 0; i < 6; i++)
                                {
                                    if (idx == -1)
                                        break;
                                    idx = features_text.IndexOf('.');
                                    features_text = features_text.Substring(idx + 1).Trim();
                                    idx = features_text.IndexOf("\r");
                                    if (idx == -1)
                                        dtRow1[i] = features_text;
                                    else
                                    {
                                        dtRow1[i] = features_text.Substring(0, idx);
                                        features_text = features_text.Substring(idx).Trim();
                                    }
                                }
                                tmpcount++;
                                dt1.Rows.Add(dtRow1);
                            }
                            //DataTable 2 Columns
                            dtRow1 = dt1.NewRow();
                            dt1.Rows.Add(dtRow1);
                            dtRow1 = dt1.NewRow();
                            for (int i = 0; i < 6; i++)
                            {
                                idx = txtoutput.IndexOf('.');
                                txtoutput = txtoutput.Substring(idx + 1).Trim();
                                idx = txtoutput.IndexOf("\r");
                                tmpheader = txtoutput.Substring(0, idx);
                                dtRow1[i] = tmpheader;
                                txtoutput = txtoutput.Substring(idx).Trim();
                            }
                            dtRow1[4] = "Classification Results";
                            dt1.Rows.Add(dtRow1);
                            idx = txtoutput.IndexOf("\r\n\r\n\r\n");
                            txtoutput = txtoutput.Substring(idx + 6).Trim();
                            int count = 0;
                            while (idx > 0)
                            {
                                dtRow1 = dt1.NewRow();
                                for (int i = 0; i < 5; i++)
                                {
                                    idx = txtoutput.IndexOf(' ');
                                    tmpfield = txtoutput.Substring(0, idx);
                                    dtRow1[i] = tmpfield;
                                    txtoutput = txtoutput.Substring(idx).Trim();
                                }

                                idx = txtoutput.IndexOf("\r");    
                                if (txtoutput.IndexOf("\tNOTE") > 1)   //for k nearest neighbours their is note after result to ramove that this blog.
                                {
                                    idx = txtoutput.IndexOf("\t");
                                    tmpfield = txtoutput.Substring(0, idx);
                                    dtRow1[5] = tmpfield;
                                    txtoutput = txtoutput.Substring(idx).Trim();
                                    dt1.Rows.Add(dtRow1);
                                    count += 1;
                                    idx = txtoutput.IndexOf("\r\n");
                                    txtoutput = txtoutput.Substring(idx).Trim();
                                    if (txtoutput.IndexOf("*** STATISTICS ***") > 0)
                                        idx = 1;
                                    else
                                        idx = -1;
                                    continue;
                                }
                                tmpfield = txtoutput.Substring(0, idx);
                                dtRow1[5] = tmpfield;
                                txtoutput = txtoutput.Substring(idx).Trim();
                                dt1.Rows.Add(dtRow1);
                                count += 1;
                                if (txtoutput.IndexOf("*** STATISTICS ***") > 0)
                                    idx = 1;
                                else
                                    idx = -1;
                            }
                            string[] tmptestset = new string[count];
                            idx = txtoutput.IndexOf("\r\n\r\n");
                            txtoutput = txtoutput.Substring(idx + 4).Trim();
                            int n = 0;
                            count = 0;
                            while (idx > 0)
                            {
                                idx = txtoutput.IndexOf('.');
                                txtoutput = txtoutput.Substring(idx + 1).Trim();
                                idx = txtoutput.IndexOf("\r");
                                tmptestset[n] = txtoutput.Substring(0, idx);
                                txtoutput = txtoutput.Substring(idx).Trim();
                                if (txtoutput.IndexOf("@") > 0)
                                    idx = 1;
                                else
                                    idx = -1;
                                count += 1;
                                n++;
                            }
                            dGVResults1.Columns.Add("Class Identified", "Class Identified");
                            for (int i = 0; i < count; i++)
                            {
                                dGVResults1.Columns.Add(tmptestset[i], tmptestset[i]);
                            }
                            dGVResults1.Columns.Add("%Correct", "%Correct");
                            DataGridViewRow dgRow = new DataGridViewRow();
                            dgRow.CreateCells(dGVResults1);
                            DataGridViewCell dgcell = new DataGridViewTextBoxCell();
                            dgcell.Value = (object)(" ");
                            dgRow.Cells[0] = dgcell;
                            for (int i = 0; i < count; i++)
                            {
                                dgcell = new DataGridViewTextBoxCell();
                                dgcell.Value = (object)(tmptestset[i]);
                                dgRow.Cells[i + 1] = dgcell;
                            }
                            dgcell = new DataGridViewTextBoxCell();
                            dgcell.Value = (object)("% Correct");
                            dgRow.Cells[count + 1] = dgcell;
                            dGVResults1.Rows.Add(dgRow);
                            for (int i = 0; i < count; i++)
                            {
                                dgRow = new DataGridViewRow();
                                dgRow.CreateCells(dGVResults1);
                                dgcell = new DataGridViewTextBoxCell();
                                dgcell.Value = (object)(tmptestset[i]);
                                dgRow.Cells[0] = dgcell;
                                idx = txtoutput.IndexOf('#');
                                txtoutput = txtoutput.Substring(idx + 4).Trim();
                                for (int j = 1; j <= count; j++)
                                {
                                    idx = txtoutput.IndexOf("\t");
                                    tmpfield = txtoutput.Substring(0, idx);
                                    dgcell = new DataGridViewTextBoxCell();
                                    dgcell.Value = (object)(tmpfield);
                                    dgRow.Cells[j] = dgcell;
                                    txtoutput = txtoutput.Substring(idx).Trim();
                                }
                                idx = txtoutput.IndexOf("\r");
                                if (idx != -1)
                                    tmpfield = txtoutput.Substring(0, idx);
                                else
                                    tmpfield = txtoutput;
                                dgcell = new DataGridViewTextBoxCell();
                                dgcell.Value = (object)(tmpfield);
                                dgRow.Cells[count + 1] = dgcell;
                                dGVResults1.Rows.Add(dgRow);
                            }
                            dGVResults.DataSource = dt1;
                            for (int i = 0; i < dGVResults.Columns.Count; i++)
                                dGVResults.Columns[i].SortMode = DataGridViewColumnSortMode.NotSortable;
                            dGVResults.CellPainting += new DataGridViewCellPaintingEventHandler(dGVResults_CellPainting);
                            dGVResults1.CellPainting += new DataGridViewCellPaintingEventHandler(dGVResults1_CellPainting);
                            int tmpsize = 0;
                            for (int i = 0; i < dGVResults1.Rows.Count; i++)
                                tmpsize += dGVResults1.Rows[i].Height;
                            if (tmpsize < dGVResults1.Height)
                            {
                                for (int i = 0; i < dGVResults1.Rows.Count; i++)
                                    dGVResults1.Rows[i].Height = (dGVResults1.Height - 10) / dGVResults1.Rows.Count;
                            }
                        }
                        catch (Exception e1)
                        {
                            MessageBox.Show(e1.Message);
                        }
                    }
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        public void dGVResults_CellPainting(object sender, DataGridViewCellPaintingEventArgs e)
        {
            if (e.RowIndex == 1 && e.ColumnIndex != -1 && e.ColumnIndex < dGVResults.Columns.Count)
            {
                if (e.ColumnIndex != 2)
                {
                    e.PaintBackground(e.ClipBounds, true);
                    Rectangle r = e.CellBounds;
                    Rectangle r1 = dGVResults.GetCellDisplayRectangle(e.ColumnIndex, 1, true);
                    r.Width += r1.Width - 1;
                    r.Height -= 1;

                    using (SolidBrush brBk = new SolidBrush(SystemColors.Window))
                        e.Graphics.FillRectangle(brBk, r);

                    if (e.ColumnIndex == 1)
                    {
                        using (SolidBrush brFr = new SolidBrush(e.CellStyle.ForeColor))
                        {
                            StringFormat sf = new StringFormat();
                            sf.Alignment = StringAlignment.Near;
                            sf.LineAlignment = StringAlignment.Center;
                            Font ft = new Font("Courier New", 9, FontStyle.Bold);
                            e.Graphics.DrawString("FeatureFile Header", ft, brFr, r, sf);

                        }
                    }
                }
                e.Handled = true;
                dGVResults.Rows[1].ReadOnly = true;
                dGVResults.Rows[1].DefaultCellStyle.WrapMode = DataGridViewTriState.True;
            }
            if (e.RowIndex == (tmpcount + 2) && e.ColumnIndex != -1 && e.ColumnIndex < dGVResults.Columns.Count)
            {
                e.PaintBackground(e.ClipBounds, true);
                Rectangle r = e.CellBounds;
                Rectangle r1 = dGVResults.GetCellDisplayRectangle(e.ColumnIndex, (tmpcount + 2), true);
                r.Width += r1.Width - 1;
                r.Height -= 1;
                using (SolidBrush brBk = new SolidBrush(SystemColors.Window))
                    e.Graphics.FillRectangle(brBk, r);
                if (e.ColumnIndex == 1)
                {
                    using (SolidBrush brFr = new SolidBrush(e.CellStyle.ForeColor))
                    {
                        StringFormat sf = new StringFormat();
                        sf.Alignment = StringAlignment.Near;
                        sf.LineAlignment = StringAlignment.Center;
                        Font ft = new Font("Courier New", 9, FontStyle.Bold);
                        e.Graphics.DrawString("Test Set \nInformation", ft, brFr, r, sf);
                    }
                }
                e.Handled = true;
                dGVResults.Rows[e.RowIndex].ReadOnly = true;
                dGVResults.Rows[e.RowIndex].DefaultCellStyle.WrapMode = DataGridViewTriState.True;
                dGVResults.Rows[e.RowIndex].Height = 35;
            }
            if (e.RowIndex == (tmpcount + 3))
            {
                dGVResults.Rows[e.RowIndex].DefaultCellStyle.SelectionBackColor = SystemColors.Window;
                dGVResults.Rows[e.RowIndex].DefaultCellStyle.SelectionForeColor = SystemColors.WindowText;
                dGVResults.Rows[e.RowIndex].DefaultCellStyle.Font = new Font("Courier New", 9, FontStyle.Bold);
                dGVResults.Rows[e.RowIndex].DefaultCellStyle.WrapMode = DataGridViewTriState.True;
                dGVResults.Rows[e.RowIndex].ReadOnly = true;
            }
        }

        public void dGVResults1_CellPainting(object sender, DataGridViewCellPaintingEventArgs e)
        {
            if (e.ColumnIndex == 0)
            {
                dGVResults1.Columns[0].DefaultCellStyle.SelectionBackColor = SystemColors.Window;
                dGVResults1.Columns[0].DefaultCellStyle.SelectionForeColor = SystemColors.WindowText;
                dGVResults1.Columns[0].DefaultCellStyle.Font = new Font("Courier New", 9, FontStyle.Bold);
                dGVResults1.Columns[0].DefaultCellStyle.WrapMode = DataGridViewTriState.True;
                dGVResults1.Columns[0].ReadOnly = true;
            }
            if (e.RowIndex == 0)
            {
                dGVResults1.Rows[e.RowIndex].DefaultCellStyle.SelectionBackColor = SystemColors.Window;
                dGVResults1.Rows[e.RowIndex].DefaultCellStyle.SelectionForeColor = SystemColors.WindowText;
                dGVResults1.Rows[e.RowIndex].DefaultCellStyle.Font = new Font("Courier New", 9, FontStyle.Bold);
                dGVResults1.Rows[e.RowIndex].DefaultCellStyle.WrapMode = DataGridViewTriState.True;
                dGVResults1.Rows[e.RowIndex].ReadOnly = true;
            }
        }

        public void close()
        {
        }

        private void groupBox1_Resize(object sender, EventArgs e)
        {
            int size_height = groupBox1.Size.Height - this.dGVResults.Height - this.dGVResults1.Height - textBox1.Height;
            if (size_height > 0 && dGVResults.Rows.Count>0)
            {
                int dgvheight = 0, dgv1height = 0;
                for (int i = 0; i < dGVResults.Rows.Count; i++)
                    dgvheight += dGVResults.Rows[i].Height;
                dgvheight += dGVResults.ColumnHeadersHeight;
                for (int i = 0; i < dGVResults1.Rows.Count; i++)
                    dgv1height += dGVResults1.Rows[i].Height;
                if (dgvheight > dGVResults.Size.Height)
                {
                    if (size_height > (dgvheight - dGVResults.Size.Height))
                    {
                        dGVResults.Height = dgvheight;
                        size_height = size_height - (dgvheight - dGVResults.Height);
                    }
                    else
                    {
                        dGVResults.Height = dGVResults.Height + size_height;
                        size_height = 0;
                    }
                }
                if (size_height > 0)
                {
                    panel1.Height += (size_height - 10);
                    if (dgv1height < dGVResults1.Height)
                    {
                        for (int i = 0; i < dGVResults1.Rows.Count; i++)
                            dGVResults1.Rows[i].Height = (dGVResults1.Height) / dGVResults1.Rows.Count;
                    }
                }
            }
            else if (size_height < 0 && dGVResults1.Rows.Count>0)
            {
                int tmp = 39 * dGVResults1.Rows.Count;
                int htmp = dGVResults1.Height;
                if (dGVResults1.Height > tmp)
                {
                    for (int i = 0; i < dGVResults1.Rows.Count; i++)
                    {
                        dGVResults1.Rows[i].Height = 29;
                    }
                    panel1.Height = tmp + textBox1.Height + 10;
                    size_height += (htmp - tmp);
                }

                dGVResults.Height = dGVResults.Height + size_height;
            }
        }

        private void dGVResults_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {

        }

        private void dGVResults1_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {

        }
    }
}
