/*''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' ======================================================================
' Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
' ======================================================================
'
'             File Name: FrequencyFilterMask.cs
'           Description: Contains the controls and code
'                        for Restoration->FrequencyFilterMask page
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
using System.Text;
using System.Windows.Forms;

namespace CVIPGUI.Restoration
{
    public partial class FrequencyFilterMask : Form
    {
        const int BorderX = 11;
        const int BorderY = 11;
        const int ColumnWidth = 50;
        const int RowHeight = 25;

        private double[,] defaultMatrix = null;

        public FrequencyFilterMask(double[,] dflt, double[,] current)
        {
            InitializeComponent();

            this.DefaultValues = dflt;
            if (current != null)
                this.CurrentValues = current;
        }
        private void btnReset_Click(object sender, EventArgs e)
        {
            this.gridData.CancelEdit();
            this.CurrentValues = this.DefaultValues;
        }
        private void gridData_DataError(object sender, DataGridViewDataErrorEventArgs e)
        {
            MessageBox.Show("Please check the input value. Only doubles are accepted.",
               "Double Required", MessageBoxButtons.OK, MessageBoxIcon.Warning);
            ((DataGridViewTextBoxEditingControl)this.gridData.EditingControl).SelectAll();
        }

        public int Cols { get { return this.MaskSize.Width; } }
        public int Rows { get { return this.MaskSize.Height; } }
        public double[,] CurrentValues
        {
            get
            {
                double[,] matrix = new double[this.Rows, this.Cols];
                for (int i = 0; i < this.Rows; i++)
                {
                    for (int j = 0; j < this.Cols; j++)
                    {
                        matrix[i, j] = (double)this.gridData.Rows[i].Cells[j].Value;
                    }
                }
                return matrix;
            }
            set
            {
                for (int i = 0; i < this.Rows; i++)
                {
                    for (int j = 0; j < this.Cols; j++)
                    {
                        this.gridData.Rows[i].Cells[j].Value = value[i, j];
                    }
                }
            }
        }
        public double[,] DefaultValues
        {
            get { return this.defaultMatrix; }
            set
            {
                int cols = value.GetLength(1);
                int rows = value.GetLength(0);
                this.MaskSize = new Size(cols, rows);
                this.defaultMatrix = value;
                this.CurrentValues = this.DefaultValues;
            }
        }
        public Size MaskSize
        {
            get { return new Size(this.gridData.Columns.Count, this.gridData.Rows.Count); }
            set
            {
                if (this.MaskSize != value)
                {
                    this.defaultMatrix = null;
                    this.gridData.Rows.Clear();
                    this.gridData.Columns.Clear();
                    for (int i = 0; i < value.Width; i++)
                    {
                        this.gridData.Columns.Add((i + 1).ToString(), (i + 1).ToString());
                        this.gridData.Columns[i].SortMode = DataGridViewColumnSortMode.NotSortable;
                        this.gridData.Columns[i].Width = ColumnWidth;
                    }
                    for (int i = 0; i < value.Height; i++)
                    {
                        this.gridData.Rows.Add();
                        this.gridData.Rows[i].HeaderCell.Value = (i + 1).ToString();
                        this.gridData.Rows[i].Height = RowHeight;
                        for (int j = 0; j < value.Width; j++)
                        {
                            this.gridData.Rows[i].Cells[j].ValueType = typeof(double);
                        }
                    }
                    int width = this.gridData.RowHeadersWidth + (this.Cols * ColumnWidth);
                    int height = this.gridData.ColumnHeadersHeight + (this.Rows * RowHeight);
                    this.gridData.Size = new Size(width, height);
                    this.pnlGrid.Size = new Size(width - 15, height - 1);

                    this.pnlGrid.Location = new Point(BorderX, BorderY);
                    int right = (2 * BorderX) + this.pnlGrid.Width;
                    int bottom = BorderY + this.pnlGrid.Height + 49;
                    this.ClientSize = new System.Drawing.Size(right, bottom);

                    int left = right - 65;
                    int top = bottom - 32;

                    this.btnOK.Location = new Point(left, top);
                    this.btnReset.Location = new Point(left - 60, top);
                    this.btnCancel.Location = new Point(left - 120, top);
                }
            }
        }
    }
}
