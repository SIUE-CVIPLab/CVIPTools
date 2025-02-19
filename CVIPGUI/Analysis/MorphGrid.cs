using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace CVIPGUI.Analysis
{
    public partial class MorphGrid : Form
    {
        double[,] defaultMatrix = { {1, 0, 1 }, { 0, 1, 0 }, { 1, 0, 1 } };

        public MorphGrid()
        {
            InitializeComponent();
            this.MdiParent = MainForm.TheMainForm;
        }

        private void btnReset_Click(object sender, EventArgs e)
        {
            EndEdit();
            LoadDefaultValues();
        }
        private void btnCancel_Click(object sender, EventArgs e)
        {
            EndEdit();
            this.Hide();
        }
        public void EndEdit()
        {
            //this.gridData.CancelEdit();
            this.gridData.EndEdit();
        }

        private void LoadDefaultValues()
        {
            for (int i = 0; i < this.Rows; i++)
            {
                for (int j = 0; j < this.Cols; j++)
                {
                    this.gridData.Rows[i].Cells[j].Value = 0;
                }
            }
        }

        private void gridData_CellValidating(object sender, DataGridViewCellValidatingEventArgs e)
        {
            double val;
            string text = (string)e.FormattedValue;
            val = Convert.ToDouble(text);
            if (val != 0 && val != 1)
            {
                MessageBox.Show("Please check the input value. Only 0 and 1 are accepted.",
                   "Wrong Input!", MessageBoxButtons.OK, MessageBoxIcon.Warning);
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

        public int Cols { get { return this.MaskSize.Width; } }
        public int Rows { get { return this.MaskSize.Height; } }
        public int[] CurrentValues
        {
            get
            {
                int[] matrix = new int[this.Rows * this.Cols];
                int value;
                for (int i = 0; i < this.Rows; i++)
                {
                    for (int j = 0; j < this.Cols; j++)
                    {
                        value = Convert.ToInt32(this.gridData.Rows[i].Cells[j].Value);
                        if (value == 0)
                            matrix[(i * this.Cols) + j] = -1;
                        else
                            matrix[(i * this.Cols) + j] = 0;
                    }
                }
                return matrix;
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
                        this.gridData.Columns[i].Width = 50;
                    }
                    for (int i = 0; i < value.Height; i++)
                    {
                        this.gridData.Rows.Add();
                        this.gridData.Rows[i].HeaderCell.Value = (i + 1).ToString();
                        this.gridData.Rows[i].Height = 25;
                        for (int j = 0; j < value.Width; j++)
                        {
                            this.gridData.Rows[i].Cells[j].ValueType = typeof(double);
                            //Temporarily Fills Array With Zeros
                            this.gridData.Rows[i].Cells[j].Value = 0;
                        }
                    }
                    int width = this.gridData.RowHeadersWidth + (this.Cols * 50);
                    int height = this.gridData.ColumnHeadersHeight + (this.Rows * 25);
                    this.gridData.Size = new Size(width, height);
                    RecalcLayout();
                }
            }
        }

        private void RecalcLayout()
        {
            int right, left, top, bottom;
            right = (this.Cols*50) + 60;
            bottom = (this.Rows*25) + 35;
            this.ClientSize = new System.Drawing.Size(right + 10, bottom + 40);

            left = right - 55;
            top = bottom + 10;

            this.btnApply.Location = new Point(left, top);
            this.btnReset.Location = new Point(left - 60, top);
            this.btnCancel.Location = new Point(left - 120, top);
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
    }
}
