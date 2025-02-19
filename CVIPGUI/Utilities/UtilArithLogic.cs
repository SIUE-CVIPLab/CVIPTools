/*''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' ======================================================================
' Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
' ======================================================================
'
'             File Name: UtilArithLogic.cs
'           Description: Contains the controls and code
'                        for Utilities->UtilArithLogic page
'         Related Files: CvipOp.cs
'                        CvipConstant.cs
'   Initial Coding Date: April 2007
'              Modified: September 2012
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

namespace CVIPGUI.Utilities
{
    enum ArithLogicSelection
    {
        Add,
        Subtract,
        Multiply,
        Divide,
        AND,
        NOT,
        OR,
        XOR
    }

    public partial class UtilArithLogic : UserControl
    {
        private ArithLogicSelection currentSelection;

        public UtilArithLogic()
        {
            InitializeComponent();
        }
        private void btnApply_Click(object sender, EventArgs e)
        {
            ViewerForm viewer = (ViewerForm)this.txtCurrentImage.Tag, viewer2 = null;
            if (viewer == null)
            {
                MessageBox.Show("Please give an input image!", "No input image!",
                    MessageBoxButtons.OK, MessageBoxIcon.Warning);
                return;
            }
            if ((this.currentSelection != ArithLogicSelection.NOT) &&
                ((this.currentSelection != ArithLogicSelection.Multiply) || this.rbImage.Checked))
            {
                viewer2 = this.cboSecondImage.SelectedItem as ViewerForm;
                if (viewer2 == null)
                {
                    MessageBox.Show("Please give a second image!", "No second image!",
                        MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    return;
                }
            }
            // disable Apply button
            this.btnApply.Enabled = false;
            this.Cursor = Cursors.WaitCursor;

            try
            {
                // get the image(s) that will be operated on
                int inputImage1 = viewer.CVIPimage, outputImage = 0;
                int inputImage2 = (viewer2 == null) ? 0 : viewer2.CVIPimage;

                switch (this.currentSelection)
                {
                case ArithLogicSelection.Add:
                    outputImage = CvipOp.Add_Image(inputImage1, inputImage2);
                    break;

                case ArithLogicSelection.Subtract:
                    outputImage = CvipOp.Subtract_Image(inputImage1, inputImage2);
                    break;

                case ArithLogicSelection.Multiply:
                    if (this.rbImage.Checked)
                        outputImage = CvipOp.Multiply_Image(inputImage1, inputImage2);
                    else
                    {
                        if (this.chkByteClipping.Checked)
                        {
                            // with BYTE clipping
                            int tmp = CvipOp.Remap_Image(inputImage1, dataType.CVIP_BYTE, 0, 255);
                            outputImage = CvipOp.Gray_Multiply(tmp, this.MultConstant);
                        }
                        else
                        {
                            // without BYTE clipping
                            outputImage = CvipOp.Gray_Multiply2(inputImage1, this.MultConstant);
                        }
                    }
                    break;

                case ArithLogicSelection.Divide:
                    outputImage = CvipOp.Divide_Image(inputImage1, inputImage2, 1);
                    break;

                case ArithLogicSelection.AND:
                    outputImage = CvipOp.And_Image(inputImage1, inputImage2);
                    break;

                case ArithLogicSelection.NOT:
                    outputImage = CvipOp.Not_Image(inputImage1);
                    break;

                case ArithLogicSelection.OR:
                    outputImage = CvipOp.Or_Image(inputImage1, inputImage2);
                    break;

                case ArithLogicSelection.XOR:
                    outputImage = CvipOp.Xor_Image(inputImage1, inputImage2);
                    break;
                }
                if (outputImage != 0)
                {
                    string newImageName = viewer.Text;
                    newImageName += "_" + CvipFunctionNames.getFncName(this.currentSelection.ToString());
                    newImageName += CvipConstant.imageNameCount++.ToString();
                    MainForm.Viewers.Add(outputImage, newImageName);
                }
                // delete input images
                CvipOp.Delete_Image(ref inputImage1);
                if ((this.currentSelection != ArithLogicSelection.NOT) &&
                    ((this.currentSelection != ArithLogicSelection.Multiply) || this.rbImage.Checked))
                {
                    CvipOp.Delete_Image(ref inputImage2);
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
            // enable Apply button
            this.btnApply.Enabled = true;
            this.Cursor = Cursors.Default;
        }
        private void btnCancel_Click(object sender, EventArgs e)
        {
            MainForm.UtilitiesForm.Close();
        }
        private void btnHelp_Click(object sender, EventArgs e)
        {
            MainForm.ShowHelp();
        }
        private void btnReset_Click(object sender, EventArgs e)
        {
            //Multiply
            this.rbImage.Checked = true;
            this.pnlSecondImage.Visible = true;
            this.pnlMultConstant.Visible = false;
            this.toolTipImage2.RemoveAll();
        }
        private void cboMultConstant_Validating(object sender, CancelEventArgs e)
        {
            float val;
            if (!float.TryParse(this.cboMultConstant.Text, out val))
            {
                MessageBox.Show("Please check the input value. Only floats are accepted.",
                   "Float Required", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                this.cboMultConstant.SelectAll();
                e.Cancel = true;
            }
        }
        private void cboSecondImage_DrawItem(object sender, DrawItemEventArgs e)
        {
            this.toolTipImage2.RemoveAll();
            if (pnlSecondImage.Visible == true)
            {
                if (cboSecondImage.Items.Count != 0 && e.Index != -1)
                {
                    string text = this.cboSecondImage.GetItemText(cboSecondImage.Items[e.Index]);
                    e.DrawBackground();
                    using (SolidBrush br = new SolidBrush(e.ForeColor))
                    {
                        e.Graphics.DrawString(text, e.Font, br, e.Bounds);
                    }
                    if ((e.State & DrawItemState.Selected) == DrawItemState.Selected)
                    {
                        this.toolTipImage2.Show(text, cboSecondImage, e.Bounds.Right, e.Bounds.Bottom);
                    }
                    else
                    {
                        this.toolTipImage2.Hide(cboSecondImage);
                    }
                    e.DrawFocusRectangle();
                }
            }
        }
        private void cboSecondImage_SelectedIndexChanged(object sender, EventArgs e)
        {
            this.toolTipImage2.RemoveAll();
            this.toolTipImage2.Hide(this.cboSecondImage);
        }
        public void Init(string op)
        {
            this.currentSelection = (ArithLogicSelection)Enum.Parse(typeof(ArithLogicSelection), op);

            this.btnReset.Enabled = (this.currentSelection == ArithLogicSelection.Multiply);
            this.cboMultConstant.Text = "2.0";
            this.pnlMultConstant.Visible = (this.currentSelection == ArithLogicSelection.Multiply) && this.rbConstant.Checked;
            this.pnlSecondImage.Visible = (this.currentSelection != ArithLogicSelection.NOT);
            this.rbConstant.Visible = (this.currentSelection == ArithLogicSelection.Multiply);
            this.rbImage.Visible = (this.currentSelection == ArithLogicSelection.Multiply);
            this.txtCurrentOperation.Text = this.currentSelection.ToString();
            this.toolTipImage2.RemoveAll();

            if (MainForm.Viewers != null)
            {
                OnSelectedViewerChanged(MainForm.Viewers.SelectedViewer);
                OnViewerCollectionChanged();
            }
        }
        protected override void OnLoad(EventArgs e)
        {
            base.OnLoad(e);
            if (MainForm.Viewers != null)
            {
                OnSelectedViewerChanged(MainForm.Viewers.SelectedViewer);
                OnViewerCollectionChanged();
            }
        }
        private void OnSelectedViewerChanged(ViewerForm viewer)
        {
            if (MainForm.Viewers != null)
            {
                if ((ModifierKeys & Keys.Alt) == Keys.Alt)
                {
                    this.cboSecondImage.SelectedItem = viewer;
                }
                else
                {
                    this.txtCurrentImage.Tag = viewer;
                    this.txtCurrentImage.Text = "";
                    if (viewer != null)
                        this.txtCurrentImage.Text = viewer.Text;
                }
            }
        }
        private void OnViewerCollectionChanged()
        {
            if (MainForm.Viewers != null)
            {
                ViewerForm selected = this.cboSecondImage.SelectedItem as ViewerForm;
                if (selected == null) selected = MainForm.Viewers.SelectedViewer;
                this.cboSecondImage.Items.Clear();
                foreach (ViewerForm viewer in MainForm.Viewers)
                    this.cboSecondImage.Items.Add(viewer);
                this.cboSecondImage.SelectedItem = selected;
            }
        }
        private void rbMultOp_Click(object sender, EventArgs e)
        {
            this.pnlMultConstant.Visible = this.rbConstant.Checked;
            this.pnlSecondImage.Visible = this.rbImage.Checked;
            if (this.rbConstant.Checked)
            {
                this.toolTipImage2.RemoveAll();
                if (string.IsNullOrEmpty(this.cboMultConstant.Text))
                    this.cboMultConstant.Text = "2.0";
            }
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
                    break;

                case WM.DESTROY:
                    MainForm.Viewers.SelectedViewerChanged -= this.OnSelectedViewerChanged;
                    MainForm.Viewers.ViewerCollectionChanged -= this.OnViewerCollectionChanged;
                    break;
                }
            }
        }

        private float MultConstant { get { return float.Parse(this.cboMultConstant.Text); } }

        private void grpArithLogic_Enter(object sender, EventArgs e)
        {

        }
    }
}
