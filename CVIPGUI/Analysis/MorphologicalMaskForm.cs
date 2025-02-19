/*''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' ======================================================================
' Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
' ======================================================================
'
'             File Name: MorphologicalMaskForm.cs
'           Description: Contains the controls and code
'                        for Analysis->MorphologicalMaskForm page
'         Related Files: Segmentation.cs
'                        CvipOp.cs
'   Initial Coding Date: November 2011
'              Modified: March 2013
'       Delevoping tool: Visual Studio 2010-C#
'             Credit(s): Patrick Solt
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

namespace CVIPGUI.Analysis
{
    public enum Direction : int
    {
        ArrowDown = 1,
        ArrowDownLeft = 5,
        ArrowDownRight = 8,
        ArrowLeft = 2,
        ArrowRight = 4,
        ArrowUp = 3,
        ArrowUpLeft = 6,
        ArrowUpRight = 7,
        DirectionNotSet = 9
    }
    public partial class MorphologicalMaskForm : Form
    {
        const int BorderX = 11;
        const int BorderY = 11;
        const int ColumnWidth = 35;
        const int RowHeight = 25;

        private Direction dirCurrent = Direction.DirectionNotSet;
        private MorphologicalMasks masks = new MorphologicalMasks();
        private Segmentation frmOwner = null;
        

        public MorphologicalMaskForm(Segmentation owner)
        {
            InitializeComponent();
            this.frmOwner = owner;
            this.MdiParent = MainForm.TheMainForm;
            
        }
        private void btnArrow_Click(object sender, EventArgs e)
        {
            Button arrow = sender as Button;
            if (arrow == this.btnArrowDown)
                this.CurrentDirection = Direction.ArrowDown;
            else if (arrow == this.btnArrowDownLeft)
                this.CurrentDirection = Direction.ArrowDownLeft;
            else if (arrow == this.btnArrowDownRight)
                this.CurrentDirection = Direction.ArrowDownRight;
            else if (arrow == this.btnArrowLeft)
                this.CurrentDirection = Direction.ArrowLeft;
            else if (arrow == this.btnArrowRight)
                this.CurrentDirection = Direction.ArrowRight;
            else if (arrow == this.btnArrowUp)
                this.CurrentDirection = Direction.ArrowUp;
            else if (arrow == this.btnArrowUpLeft)
                this.CurrentDirection = Direction.ArrowUpLeft;
            else if (arrow == this.btnArrowUpRight)
                this.CurrentDirection = Direction.ArrowUpRight;
            
            LoadCurrentValues();
        }
        private void btnClose_Click(object sender, EventArgs e)
        {
            EndEdit();
            this.Hide();
        }
        private void btnReset_Click(object sender, EventArgs e)
        {
            ResetValues();
        }
        private void ClearValues()
        {
            EndEdit();
            this.masks.Clear();
        }
        public void EndEdit()
        {
           // this.gridData.CancelEdit();
            this.gridData.EndEdit();
        }
        private void gridData_CellValidating(object sender, DataGridViewCellValidatingEventArgs e)
        {
            string text = ((string)e.FormattedValue).ToLower();
            if ((text != "0") && (text != "1") && (text != "x"))
            {
                MessageBox.Show("Please check the input value. Must be '0', '1', or 'x'.",
                   "Invalid Mask Value", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                DataGridViewTextBoxEditingControl textbox = this.gridData.EditingControl as DataGridViewTextBoxEditingControl;
                if (textbox != null)
                    textbox.SelectAll();
                e.Cancel = true;
            }
        }
        private void gridData_CellValidated(object sender, DataGridViewCellEventArgs e)
        {
            switch (this.frmOwner.CurrentSelection)
            {
            case SegmentationSelection.morphHit:
                this.masks.HitOrMissMask[(int)this.dirCurrent, this.MaskSize] = this.GridValues;
                break;
            case SegmentationSelection.morphSkel:

                this.masks.SkeletonizationMask[(int)this.dirCurrent, this.MaskSize] = this.GridValues;
                break;
            case SegmentationSelection.morphThin:
                this.masks.ThinningMask[(int)this.dirCurrent, this.MaskSize] = this.GridValues;
                break;
            }
        }
        private void gridData_Leave(object sender, EventArgs e)
        {
            EndEdit();
        }
        public void LoadCurrentValues()
        {
            if ((this.frmOwner.CurrentSelection != SegmentationSelection.morphHit) &&
                (this.frmOwner.CurrentSelection != SegmentationSelection.morphSkel) &&
                (this.frmOwner.CurrentSelection != SegmentationSelection.morphThin))
            {
                return;
            }
            EndEdit();
            this.MaskSize = this.frmOwner.MaskSize;
            switch (this.frmOwner.CurrentSelection)
            {
            case SegmentationSelection.morphHit:
            if ((this.CurrentDirection == Direction.DirectionNotSet)) //||
            //    (this.CurrentDirection == Direction.ArrowDown) ||
            //    (this.CurrentDirection == Direction.ArrowLeft) ||
            //    (this.CurrentDirection == Direction.ArrowRight) ||
            //    (this.CurrentDirection == Direction.ArrowUp))
                {
                    this.CurrentDirection = Direction.ArrowUpRight;//.ArrowDown;
                }
                this.GridValues = this.masks.HitOrMissMask[(int)this.dirCurrent, this.MaskSize];
                this.Text = "Hit or Miss Mask";
                break;

            case SegmentationSelection.morphSkel:                                    
                if (this.CurrentDirection == Direction.DirectionNotSet)
                    this.CurrentDirection = Direction.ArrowDown;
                
                this.GridValues = this.masks.SkeletonizationMask[(int)this.dirCurrent, this.MaskSize];
                 
                this.Text = "Skeletonization Mask";
               
                this.btnArrowDown.Visible = false;  // Changes done in 5.7 version
                this.btnArrowDownLeft.Visible = false;
                this.btnArrowDownRight.Visible = false;
                this.btnArrowLeft.Visible = false;
                this.btnArrowRight.Visible = false;
                this.btnArrowUp.Visible = false;
                this.btnArrowUpLeft.Visible = false;
                this.btnArrowUpRight.Visible = false;
              
               
                break;

            case SegmentationSelection.morphThin:
                if (this.CurrentDirection == Direction.DirectionNotSet)
                    this.CurrentDirection = Direction.ArrowDown;
                this.GridValues = this.masks.ThinningMask[(int)this.dirCurrent, this.MaskSize];
                this.Text = "Thinning Mask";
                break;
            }
        }
        private void RecalcLayout()
        {
            bool bShowArrows = true;
            bool bShowNSEWArrows = true;//(this.frmOwner.CurrentSelection != SegmentationSelection.morphHit);
            this.btnArrowDown.Visible = bShowNSEWArrows;
            this.btnArrowDownLeft.Visible = bShowArrows;
            this.btnArrowDownRight.Visible = bShowArrows;
            this.btnArrowLeft.Visible = bShowNSEWArrows;
            this.btnArrowRight.Visible = bShowNSEWArrows;
            this.btnArrowUp.Visible = bShowNSEWArrows;
            this.btnArrowUpLeft.Visible = bShowArrows;
            this.btnArrowUpRight.Visible = bShowArrows;
            if (bShowArrows)
            {
                this.btnArrowUpLeft.Location = new Point(BorderX, BorderY);
                this.pnlGrid.Location = new Point(this.btnArrowUpLeft.Right, this.btnArrowUpLeft.Bottom);
                this.btnArrowUpRight.Location = new Point(this.pnlGrid.Right, BorderY);
                this.btnArrowDownLeft.Location = new Point(BorderX, this.pnlGrid.Bottom);
                this.btnArrowDownRight.Location = new Point(this.pnlGrid.Right, this.pnlGrid.Bottom);

                int center = this.pnlGrid.Right - (((this.Cols * ColumnWidth) + this.btnArrowUp.Width) / 2);
                this.btnArrowUp.Location = new Point(center, BorderY);
                this.btnArrowDown.Location = new Point(center, this.pnlGrid.Bottom);

                center = this.pnlGrid.Bottom - (((this.Rows * RowHeight) + this.btnArrowLeft.Height) / 2);
                this.btnArrowLeft.Location = new Point(BorderX, center);
                this.btnArrowRight.Location = new Point(this.pnlGrid.Right, center);

                int top = this.btnArrowDown.Bottom + 16;
                int left = this.btnArrowRight.Right - this.btnApply.Width;
                this.btnApply.Location = new Point(left, top);

                left = this.btnApply.Left - 2 - this.btnReset.Width;
                this.btnReset.Location = new Point(left, top);

                left = this.btnReset.Left - 2 - this.btnClose.Width;
                this.btnClose.Location = new Point(left, top);

                this.ClientSize = new System.Drawing.Size(this.btnApply.Right + BorderX, this.btnApply.Bottom + BorderY);
            }
            else if (this.Cols > 3)
            {
                this.pnlGrid.Location = new Point(BorderX, BorderY);

                int top = this.pnlGrid.Bottom + 16;
                int left = this.pnlGrid.Right - this.btnApply.Width;
                this.btnApply.Location = new Point(left, top);

                left = this.btnApply.Left - 2 - this.btnReset.Width;
                this.btnReset.Location = new Point(left, top);

                left = this.btnReset.Left - 2 - this.btnClose.Width;
                this.btnClose.Location = new Point(left, top);

                this.ClientSize = new System.Drawing.Size(this.btnApply.Right + BorderX, this.btnApply.Bottom + BorderY);
            }
            else
            {
                int width = (2 * (BorderX + 2)) + this.btnClose.Width + this.btnReset.Width + this.btnApply.Width;
                int left = (width - this.pnlGrid.Width) / 2;
                this.pnlGrid.Location = new Point(left, BorderY);

                int top = this.pnlGrid.Bottom + 16;
                this.btnClose.Location = new Point(BorderX, top);
                this.btnReset.Location = new Point(this.btnClose.Right + 2, top);
                this.btnApply.Location = new Point(this.btnReset.Right + 2, top);
                this.ClientSize = new System.Drawing.Size(width, this.btnApply.Bottom + BorderY);
            }
        }
        private void ResetValues()
        {
            this.CurrentDirection = Direction.DirectionNotSet;
            ClearValues();
            LoadCurrentValues();
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

        public int Cols { get { return this.MaskSize; } }
        public int Rows { get { return this.MaskSize; } }
        public int MaskSize
        {
            get { return this.gridData.Rows.Count; }
            set
            {
                if (this.MaskSize != value)
                {
                    ClearValues();
                    this.gridData.Rows.Clear();
                    this.gridData.Columns.Clear();
                    for (int col = 0; col < value; col++)
                    {
                        this.gridData.Columns.Add((col + 1).ToString(), (col + 1).ToString());
                        this.gridData.Columns[col].SortMode = DataGridViewColumnSortMode.NotSortable;
                        this.gridData.Columns[col].Width = ColumnWidth;
                    }
                    for (int row = 0; row < value; row++)
                    {
                        this.gridData.Rows.Add();
                        this.gridData.Rows[row].HeaderCell.Value = (row + 1).ToString();
                        this.gridData.Rows[row].Height = RowHeight;
                        for (int col = 0; col < value; col++)
                        {
                            this.gridData.Rows[row].Cells[col].ValueType = typeof(char);
                        }
                    }
                    int width = this.gridData.RowHeadersWidth + (this.Cols * ColumnWidth);
                    int height = this.gridData.ColumnHeadersHeight + (this.Rows * RowHeight);
                    this.gridData.Size = new Size(width, height);
                    this.pnlGrid.Size = new Size(width - 15, height - 1);
                }
                RecalcLayout();
            }
        }
        public double[] CurrentValues
        {
            get
            {
                double[] values = new double[this.MaskSize * this.MaskSize];
                double[,] mask = this.GridValues;
                for (int r = 0; r < this.MaskSize; r++)
                {
                    for (int c = 0; c < this.MaskSize; c++)
                    {
                        values[(r * this.MaskSize) + c] = mask[r, c];
                    }
                }
                return values;
            }
        }
        public double[,] GridValues
        {
            get
            {
                double[,] mask = new double[this.MaskSize, this.MaskSize];
                for (int r = 0; r < this.MaskSize; r++)
                {
                    for (int c = 0; c < this.MaskSize; c++)
                    {
                        char ch = (char)this.gridData.Rows[r].Cells[c].Value;
                        double val = -1.0;
                        if (ch == '0')
                            val = 0.0;
                        else if (ch == '1')
                            val = 1.0;
                        mask[r, c] = val;
                    }
                }
                return mask;
            }
            set
            {
                for (int r = 0; r < this.MaskSize; r++)
                {
                    for (int c = 0; c < this.MaskSize; c++)
                    {
                        char val = 'x';
                        if (value[r, c] == 0.0)
                            val = '0';
                        else if (value[r, c] == 1.0)
                            val = '1';
                        this.gridData.Rows[r].Cells[c].Value = val;
                    }
                }
            }
        }
        public Direction CurrentDirection
        {
            get { return this.dirCurrent; }
            set
            {
                this.dirCurrent = value;
                this.btnArrowDown.BackColor = SystemColors.Control;
                this.btnArrowDownLeft.BackColor = SystemColors.Control;
                this.btnArrowDownRight.BackColor = SystemColors.Control;
                this.btnArrowLeft.BackColor = SystemColors.Control;
                this.btnArrowRight.BackColor = SystemColors.Control;
                this.btnArrowUp.BackColor = SystemColors.Control;
                this.btnArrowUpLeft.BackColor = SystemColors.Control;
                this.btnArrowUpRight.BackColor = SystemColors.Control;
                switch (value)
                {
                case Direction.ArrowDown:
                    this.btnArrowDown.BackColor = Color.GreenYellow;
                    break;
                case Direction.ArrowDownLeft:
                    this.btnArrowDownLeft.BackColor = Color.GreenYellow;
                    break;
                case Direction.ArrowDownRight:
                    this.btnArrowDownRight.BackColor = Color.GreenYellow;
                    break;
                case Direction.ArrowLeft:
                    this.btnArrowLeft.BackColor = Color.GreenYellow;
                    break;
                case Direction.ArrowRight:
                    this.btnArrowRight.BackColor = Color.GreenYellow;
                    break;
                case Direction.ArrowUp:
                    this.btnArrowUp.BackColor = Color.GreenYellow;
                    break;
                case Direction.ArrowUpLeft:
                    this.btnArrowUpLeft.BackColor = Color.GreenYellow;
                    break;
                case Direction.ArrowUpRight:
                    this.btnArrowUpRight.BackColor = Color.GreenYellow;
                    break;
                }
            }
        }
    }
}
