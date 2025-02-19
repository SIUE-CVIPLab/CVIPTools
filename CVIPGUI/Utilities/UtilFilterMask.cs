/*''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' ======================================================================
' Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
' ======================================================================
'
'             File Name: UtilFilterMask.cs
'           Description: Contains the controls and code
'                        for Utilities->UtilFilterMask page
'         Related Files: CvipOp.cs
'                        CvipConstant.cs
'   Initial Coding Date: July 2010
'              Modified: November 2011
'       Delevoping tool: Visual Studio 2010-C#
'             Credit(s): Patrick Solt
'                        Southern Illinois University Edwardsville
'
' Copyright (C) 2012 Scott Umbaugh and SIUE
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
    public partial class UtilFilterMask : Form
    {
        const int BorderX = 11;
        const int BorderY = 11;
        const int ColumnWidth = 50;
        const int RowHeight = 25;

        private bool bShowArrows = false;
        private double[,] defaultMatrix = null;
        public GenericStateChange currentArrowClick = null;

        public UtilFilterMask()
        {
            InitializeComponent();
            this.MdiParent = MainForm.TheMainForm;
        }
        public void ArrowDownClick()
        {
            this.btnArrowDown.BackColor = Color.GreenYellow;
            this.btnArrowDownLeft.BackColor = SystemColors.Control;
            this.btnArrowDownRight.BackColor = SystemColors.Control;
            this.btnArrowLeft.BackColor = SystemColors.Control;
            this.btnArrowRight.BackColor = SystemColors.Control;
            this.btnArrowUp.BackColor = SystemColors.Control;
            this.btnArrowUpLeft.BackColor = SystemColors.Control;
            this.btnArrowUpRight.BackColor = SystemColors.Control;
            this.currentArrowClick = this.ArrowDownClick;

            int size = this.MaskSize.Width;
            int center = size / 2;
            double[,] vals = new double[size, size];
            for (int i = 0; i < size; i++)
            {
                if (i < center)
                    vals[i, center] = -1.0;
                else if (i > center)
                    vals[i, center] = 1.0;
            }
            this.DefaultValues = vals;
        }
        public void ArrowDownLeftClick()
        {
            this.btnArrowDown.BackColor = SystemColors.Control;
            this.btnArrowDownLeft.BackColor = Color.GreenYellow;
            this.btnArrowDownRight.BackColor = SystemColors.Control;
            this.btnArrowLeft.BackColor = SystemColors.Control;
            this.btnArrowRight.BackColor = SystemColors.Control;
            this.btnArrowUp.BackColor = SystemColors.Control;
            this.btnArrowUpLeft.BackColor = SystemColors.Control;
            this.btnArrowUpRight.BackColor = SystemColors.Control;
            this.currentArrowClick = this.ArrowDownLeftClick;

            int size = this.MaskSize.Width;
            int center = size / 2;
            double[,] vals = new double[size, size];
            for (int i = 0; i < size; i++)
            {
                if (i < center)
                    vals[i, size - i - 1] = -1.0;
                else if (i > center)
                    vals[i, size - i - 1] = 1.0;
            }
            this.DefaultValues = vals;
        }
        public void ArrowDownRightClick()
        {
            this.btnArrowDown.BackColor = SystemColors.Control;
            this.btnArrowDownLeft.BackColor = SystemColors.Control;
            this.btnArrowDownRight.BackColor = Color.GreenYellow;
            this.btnArrowLeft.BackColor = SystemColors.Control;
            this.btnArrowRight.BackColor = SystemColors.Control;
            this.btnArrowUp.BackColor = SystemColors.Control;
            this.btnArrowUpLeft.BackColor = SystemColors.Control;
            this.btnArrowUpRight.BackColor = SystemColors.Control;
            this.currentArrowClick = this.ArrowDownRightClick;

            int size = this.MaskSize.Width;
            int center = size / 2;
            double[,] vals = new double[size, size];
            for (int i = 0; i < size; i++)
            {
                if (i < center)
                    vals[i, i] = -1.0;
                else if (i > center)
                    vals[i, i] = 1.0;
            }
            this.DefaultValues = vals;
        }
        public void ArrowLeftClick()
        {
            this.btnArrowDown.BackColor = SystemColors.Control;
            this.btnArrowDownLeft.BackColor = SystemColors.Control;
            this.btnArrowDownRight.BackColor = SystemColors.Control;
            this.btnArrowLeft.BackColor = Color.GreenYellow;
            this.btnArrowRight.BackColor = SystemColors.Control;
            this.btnArrowUp.BackColor = SystemColors.Control;
            this.btnArrowUpLeft.BackColor = SystemColors.Control;
            this.btnArrowUpRight.BackColor = SystemColors.Control;
            this.currentArrowClick = this.ArrowLeftClick;

            int size = this.MaskSize.Width;
            int center = size / 2;
            double[,] vals = new double[size, size];
            for (int i = 0; i < size; i++)
            {
                if (i < center)
                    vals[center, i] = 1.0;
                else if (i > center)
                    vals[center, i] = -1.0;
            }
            this.DefaultValues = vals;
        }
        public void ArrowRightClick()
        {
            this.btnArrowDown.BackColor = SystemColors.Control;
            this.btnArrowDownLeft.BackColor = SystemColors.Control;
            this.btnArrowDownRight.BackColor = SystemColors.Control;
            this.btnArrowLeft.BackColor = SystemColors.Control;
            this.btnArrowRight.BackColor = Color.GreenYellow;
            this.btnArrowUp.BackColor = SystemColors.Control;
            this.btnArrowUpLeft.BackColor = SystemColors.Control;
            this.btnArrowUpRight.BackColor = SystemColors.Control;
            this.currentArrowClick = this.ArrowRightClick;

            int size = this.MaskSize.Width;
            int center = size / 2;
            double[,] vals = new double[size, size];
            for (int i = 0; i < size; i++)
            {
                if (i < center)
                    vals[center, i] = -1.0;
                else if (i > center)
                    vals[center, i] = 1.0;
            }
            this.DefaultValues = vals;
        }
        public void ArrowUpClick()
        {
            this.btnArrowDown.BackColor = SystemColors.Control;
            this.btnArrowDownLeft.BackColor = SystemColors.Control;
            this.btnArrowDownRight.BackColor = SystemColors.Control;
            this.btnArrowLeft.BackColor = SystemColors.Control;
            this.btnArrowRight.BackColor = SystemColors.Control;
            this.btnArrowUp.BackColor = Color.GreenYellow;
            this.btnArrowUpLeft.BackColor = SystemColors.Control;
            this.btnArrowUpRight.BackColor = SystemColors.Control;
            this.currentArrowClick = this.ArrowUpClick;

            int size = this.MaskSize.Width;
            int center = size / 2;
            double[,] vals = new double[size, size];
            for (int i = 0; i < size; i++)
            {
                if (i < center)
                    vals[i, center] = 1.0;
                else if (i > center)
                    vals[i, center] = -1.0;
            }
            this.DefaultValues = vals;
        }
        public void ArrowUpLeftClick()
        {
            this.btnArrowDown.BackColor = SystemColors.Control;
            this.btnArrowDownLeft.BackColor = SystemColors.Control;
            this.btnArrowDownRight.BackColor = SystemColors.Control;
            this.btnArrowLeft.BackColor = SystemColors.Control;
            this.btnArrowRight.BackColor = SystemColors.Control;
            this.btnArrowUp.BackColor = SystemColors.Control;
            this.btnArrowUpLeft.BackColor = Color.GreenYellow;
            this.btnArrowUpRight.BackColor = SystemColors.Control;
            this.currentArrowClick = this.ArrowUpLeftClick;

            int size = this.MaskSize.Width;
            int center = size / 2;
            double[,] vals = new double[size, size];
            for (int i = 0; i < size; i++)
            {
                if (i < center)
                    vals[i, i] = 1.0;
                else if (i > center)
                    vals[i, i] = -1.0;
            }
            this.DefaultValues = vals;
        }
        public void ArrowUpRightClick()
        {
            this.btnArrowDown.BackColor = SystemColors.Control;
            this.btnArrowDownLeft.BackColor = SystemColors.Control;
            this.btnArrowDownRight.BackColor = SystemColors.Control;
            this.btnArrowLeft.BackColor = SystemColors.Control;
            this.btnArrowRight.BackColor = SystemColors.Control;
            this.btnArrowUp.BackColor = SystemColors.Control;
            this.btnArrowUpLeft.BackColor = SystemColors.Control;
            this.btnArrowUpRight.BackColor = Color.GreenYellow;
            this.currentArrowClick = this.ArrowUpRightClick;

            int size = this.MaskSize.Width;
            int center = size / 2;
            double[,] vals = new double[size, size];
            for (int i = 0; i < size; i++)
            {
                if (i < center)
                    vals[i, size - i - 1] = 1.0;
                else if (i > center)
                    vals[i, size - i - 1] = -1.0;
            }
            this.DefaultValues = vals;
        }
        private void btnArrowDown_Click(object sender, EventArgs e)
        {
            ArrowDownClick();
        }
        private void btnArrowDownLeft_Click(object sender, EventArgs e)
        {
            ArrowDownLeftClick();
        }
        private void btnArrowDownRight_Click(object sender, EventArgs e)
        {
            ArrowDownRightClick();
        }
        private void btnArrowLeft_Click(object sender, EventArgs e)
        {
            ArrowLeftClick();
        }
        private void btnArrowRight_Click(object sender, EventArgs e)
        {
            ArrowRightClick();
        }
        private void btnArrowUp_Click(object sender, EventArgs e)
        {
            ArrowUpClick();
        }
        private void btnArrowUpLeft_Click(object sender, EventArgs e)
        {
            ArrowUpLeftClick();
        }
        private void btnArrowUpRight_Click(object sender, EventArgs e)
        {
            ArrowUpRightClick();
        }
        private void btnCancel_Click(object sender, EventArgs e)
        {
            EndEdit();
            this.Hide();
        }
        private void btnReset_Click(object sender, EventArgs e)
        {
            EndEdit();
            LoadDefaultValues();
        }
        private void chkKeepOriginal_CheckedChanged(object sender, EventArgs e)
        {
            int r = this.Rows / 2;
            int c = this.Cols / 2;
            double val = this.chkKeepOriginal.Checked ? 1.0 : -1.0;
            val += (double)this.gridData.Rows[r].Cells[c].Value;
            this.gridData.Rows[r].Cells[c].Value = val;
        }
        public void EndEdit()
        {
            //this.gridData.CancelEdit();
            this.gridData.EndEdit();
        }
        private void gridData_CellValidating(object sender, DataGridViewCellValidatingEventArgs e)
        {
            double val;
            string text = (string)e.FormattedValue;
            if (!double.TryParse(text, out val))
            {
                MessageBox.Show("Please check the input value. Only doubles are accepted.",
                   "Double Required", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                DataGridViewTextBoxEditingControl textbox = this.gridData.EditingControl as DataGridViewTextBoxEditingControl;
                if (textbox != null)
                    textbox.SelectAll();
                e.Cancel = true;
            }
        }
        private void gridData_Leave(object sender, EventArgs e)
        {
            EndEdit();
        }
        private void LoadDefaultValues()
        {
            if (this.defaultMatrix != null)
            {
                for (int i = 0; i < this.Rows; i++)
                {
                    for (int j = 0; j < this.Cols; j++)
                    {
                        this.gridData.Rows[i].Cells[j].Value = this.defaultMatrix[i, j];
                    }
                }
                if (this.chkKeepOriginal.Checked)
                {
                    int r = this.Rows / 2;
                    int c = this.Cols / 2;
                    double val = (double)this.gridData.Rows[r].Cells[c].Value + 1.0;
                    this.gridData.Rows[r].Cells[c].Value = val;
                }
            }
        }
        private void RecalcLayout()
        {
            this.btnArrowDown.Visible = this.ShowArrows;
            this.btnArrowDownLeft.Visible = this.ShowArrows;
            this.btnArrowDownRight.Visible = this.ShowArrows;
            this.btnArrowLeft.Visible = this.ShowArrows;
            this.btnArrowRight.Visible = this.ShowArrows;
            this.btnArrowUp.Visible = this.ShowArrows;
            this.btnArrowUpLeft.Visible = this.ShowArrows;
            this.btnArrowUpRight.Visible = this.ShowArrows;

            if (this.ShowArrows)
            {
                int left = BorderX;
                int right = left + this.btnArrowUpLeft.Width + this.pnlGrid.Width;
                int middle = right - (((this.Cols * ColumnWidth) + this.btnArrowUp.Width) / 2);

                int top = BorderY;
                int bottom = top + this.btnArrowUpLeft.Height + this.pnlGrid.Height;
                int center = bottom - (((this.Rows * RowHeight) + this.btnArrowLeft.Height) / 2);

                this.btnArrowUpLeft.Location = new Point(left, top);
                this.btnArrowUp.Location = new Point(middle, top);
                this.btnArrowUpRight.Location = new Point(right, top);

                this.btnArrowLeft.Location = new Point(left, center);
                this.btnArrowRight.Location = new Point(right, center);

                this.btnArrowDownLeft.Location = new Point(left, bottom);
                this.btnArrowDown.Location = new Point(middle, bottom);
                this.btnArrowDownRight.Location = new Point(right, bottom);

                this.pnlGrid.Location = new Point(left + this.btnArrowUpLeft.Width, top + this.btnArrowUpLeft.Height);

                right += (this.btnArrowUpRight.Width + BorderX);
                bottom += this.btnArrowDownLeft.Height;
                bottom = (this.Cols < 5) ? (bottom + 74) : (bottom + 49);
                this.ClientSize = new System.Drawing.Size(right, bottom);

                left = right - 65;
                top = bottom - 32;

                this.btnApply.Location = new Point(left, top);
                this.btnReset.Location = new Point(left - 60, top);
                this.btnCancel.Location = new Point(left - 120, top);

                left = BorderX;
                top = (this.Cols < 5) ? (bottom - 58) : (bottom - 29);
                this.chkKeepOriginal.Location = new Point(left + 1, top);
            }
            else
            {
                this.pnlGrid.Location = new Point(BorderX, BorderY);

                int right = (2 * BorderX) + this.pnlGrid.Width;
                int bottom = BorderY + this.pnlGrid.Height;
                bottom = (this.Cols < 7) ? (bottom + 74) : (bottom + 49);
                this.ClientSize = new System.Drawing.Size(right, bottom);

                int left = right - 65;
                int top = bottom - 32;

                this.btnApply.Location = new Point(left, top);
                this.btnReset.Location = new Point(left - 60, top);
                this.btnCancel.Location = new Point(left - 120, top);

                left = BorderX;
                top = (this.Cols < 7) ? (bottom - 58) : (bottom - 29);
                this.chkKeepOriginal.Location = new Point(left + 1, top);
            }
        }
        protected override void WndProc(ref Message m)
        {
            if (m.Msg == (int)WM.MOUSEACTIVATE)
            {
                int hittest = (int)m.LParam & 0xffff;
                if ((hittest == (int)HT.CLOSE))
                {
                    EndEdit();
                    this.Hide();
                    m.Msg = (int)WM.NULL;
                }
            }
            base.WndProc(ref m);
        }

        public int Cols { get { return this.MaskSize.Width; } }
        public int Rows { get { return this.MaskSize.Height; } }
        public double[] CurrentValues
        {
            get
            {
                double[] matrix = new double[this.Rows * this.Cols];
                for (int i = 0; i < this.Rows; i++)
                {
                    for (int j = 0; j < this.Cols; j++)
                    {
                        matrix[(i * this.Cols) + j] = (double)this.gridData.Rows[i].Cells[j].Value;
                    }
                }
                return matrix;
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
                LoadDefaultValues();
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
                    RecalcLayout();
                }
            }
        }
        public bool ShowArrows
        {
            get { return this.bShowArrows; }
            set
            {
                if (this.bShowArrows != value)
                {
                    this.bShowArrows = value;
                    RecalcLayout();
                }
            }
        }
    }
}
