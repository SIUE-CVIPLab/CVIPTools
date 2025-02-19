/*''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' ======================================================================
' Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
' ======================================================================
'
'             File Name: GeometricTransform.cs
'           Description: Contains the controls and code
'                        for Restoration->GeometricTransform page
'         Related Files: CvipOp.cs
'                        CvipConstant.cs
'   Initial Coding Date: November 2007
'              Modified: November 2009
'       Delevoping tool: Visual Studio 2010-C#
'             Credit(s): Wenjun(Evan) Bian
'                        Jhansi Lakshmi Akkineni
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
using System.IO;
using System.Text;
using System.Windows.Forms;

namespace CVIPGUI.Restoration
{
    enum GeoTransformSelection
    {
        newmesh,
        openmesh,
        sinemesh
    }

    public partial class GeometricTransform : UserControl
    {
        private GeoTransformSelection currentSelection;

        public GeometricTransform()
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
            this.btnApply.Tag = true;
            this.btnApply.Enabled = false;
            this.Cursor = Cursors.WaitCursor;

            // get the image that will be operated on
            int inputImage = viewer.CVIPimage;

            switch (this.currentSelection)
            {
            case GeoTransformSelection.sinemesh:
                viewer.CreateSineMesh(this.MeshRows, this.MeshCols);
                break;
            }
            if (viewer.MeshComplete)
            {
                int outputImage = 0;
                if (this.cboDirection.SelectedIndex == 0)
                    outputImage = CvipOp.Mesh_WarpingRI(inputImage, viewer.MeshPoints, this.InterpMethod, 1);
                else
                    outputImage = CvipOp.Mesh_Warping(inputImage, viewer.MeshPoints, this.InterpMethod);
                if (outputImage != 0)
                {
                    string newImageName = viewer.Text;
                    newImageName += "_" + CvipFunctionNames.getFncName(this.currentSelection.ToString());
                    newImageName += CvipConstant.imageNameCount++.ToString();
                    ViewerForm newViewer = MainForm.Viewers.Add(outputImage, newImageName);
                    newViewer.Mesh = viewer.Mesh;
                }
            }
            else
            {
                MessageBox.Show("Please select a mesh first!", "No Mesh!",
                    MessageBoxButtons.OK, MessageBoxIcon.Warning);
            }
            // enable Apply button
            this.btnApply.Enabled = true;
            this.btnApply.Tag = null;
            this.Cursor = Cursors.Default;
        }
        private void btnCancel_Click(object sender, EventArgs e)
        {
            MainForm.RestorationForm.Close();
        }
        private void btnHelp_Click(object sender, EventArgs e)
        {
            MainForm.ShowHelp();
        }
        private void btnMeshFile_Click(object sender, EventArgs e)
        {
            ViewerForm viewer = MainForm.Viewers.SelectedViewer;
            if (viewer == null)
            {
                MessageBox.Show("This operation requires an input image!", "No input image!",
                    MessageBoxButtons.OK, MessageBoxIcon.Warning);
                return;
            }
            string meshFile = viewer.OpenMesh();
            if (!string.IsNullOrEmpty(meshFile))
                this.lblMeshFile.Text = new FileInfo(meshFile).Name;
        }
        private void btnRedoMesh_Click(object sender, EventArgs e)
        {
            ViewerForm viewer = MainForm.Viewers.SelectedViewer;
            if (viewer != null)
                viewer.ClearMesh();
        }
        private void btnReset_Click(object sender, EventArgs e)
        {
            ResetControls();
        }
        private void btnSaveMesh_Click(object sender, EventArgs e)
        {
            ViewerForm viewer = MainForm.Viewers.SelectedViewer;
            if (viewer == null)
            {
                MessageBox.Show("Please give an input image!", "No input image!",
                    MessageBoxButtons.OK, MessageBoxIcon.Warning);
                return;
            }
            if (!viewer.MeshComplete)
            {
                MessageBox.Show("There are no mesh points to save!", "No Mesh Points",
                    MessageBoxButtons.OK, MessageBoxIcon.Warning);
                return;
            }
            viewer.SaveMesh();
        }
        private void cboMeshSize_Validated(object sender, EventArgs e)
        {
            ComboBox cbo = sender as ComboBox;
            if (this.cboMeshCols.Text != cbo.Text)
                this.cboMeshCols.Text = cbo.Text;
            if (this.cboMeshRows.Text != cbo.Text)
                this.cboMeshRows.Text = cbo.Text;
            this.txtNumPoints.Text = this.NumPoints.ToString();
        }
        private void cboMeshPoint_SelectedIndexChanged(object sender, EventArgs e)
        {
            // only run if not already in an update
            if (this.cboMeshPoint.Tag == null)
            {
                ViewerForm viewer = MainForm.Viewers.SelectedViewer;
                if (viewer != null)
                    viewer.MeshSelectedIndex = this.cboMeshPoint.SelectedIndex;
            }
        }
        private void cboUIntVal_Validating(object sender, CancelEventArgs e)
        {
            ComboBox cbo = sender as ComboBox;
            int val;
            if (!int.TryParse(cbo.Text, out val) || (val < 0))
            {
                MessageBox.Show("Please check the input value. Only unsigned integers are accepted.",
                   "Unsigned Integer Required", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                cbo.SelectAll();
                e.Cancel = true;
            }
        }
        protected override void OnLoad(EventArgs e)
        {
            base.OnLoad(e);

            this.rbNewMesh.Tag = GeoTransformSelection.newmesh;
            this.rbOpenMesh.Tag = GeoTransformSelection.openmesh;
            this.rbSineMesh.Tag = GeoTransformSelection.sinemesh;

            if (MainForm.Viewers != null)
            {
                OnSelectedViewerChanged(MainForm.Viewers.SelectedViewer);
                ResetControls();
            }
        }
        private void OnSelectedViewerChanged(ViewerForm viewer)
        {
            // set .Tag to flag that update in progress
            this.cboMeshPoint.Tag = true;
            this.btnMeshFile.Enabled = viewer != null;
            if ((viewer != null) && (viewer.MeshPoints != null))
            {
                this.btnRedoMesh.Enabled = true;
                this.btnSaveMesh.Enabled = viewer.MeshComplete;
                this.lblMeshStatus.Text = viewer.MeshStatus;

                int ptsComplete = viewer.MeshPointsCompleted;
                while (this.cboMeshPoint.Items.Count > ptsComplete)
                    this.cboMeshPoint.Items.RemoveAt(this.cboMeshPoint.Items.Count - 1);
                while (this.cboMeshPoint.Items.Count < ptsComplete)
                    this.cboMeshPoint.Items.Add(this.cboMeshPoint.Items.Count + 1);

                if (viewer.MeshSelectedIndex >= 0)
                {
                    this.cboMeshPoint.SelectedIndex = viewer.MeshSelectedIndex;
                    Point selected = viewer.MeshSelectedValue;
                    this.txtMeshCol.Text = selected.X.ToString();
                    this.txtMeshRow.Text = selected.Y.ToString();
                    this.txtMeshCol.Refresh();
                    this.txtMeshRow.Refresh();
                }
                else
                {
                    this.txtMeshCol.Text = "";
                    this.txtMeshRow.Text = "";
                }
            }
            else
            {
                this.btnRedoMesh.Enabled = false;
                this.btnSaveMesh.Enabled = false;
                this.cboMeshPoint.Items.Clear();
                this.txtMeshCol.Text = "";
                this.txtMeshRow.Text = "";
                this.lblMeshStatus.Text = "";
            }
            this.cboMeshPoint.Tag = null;
        }
        private void OnViewerAltMouseClicked(Point ptImage, ViewerForm viewer)
        {
            if (viewer.MeshPoints == null)
                viewer.CreateMesh(this.MeshRows, this.MeshCols);
        }
        private void rbGeoTransforms_Click(object sender, EventArgs e)
        {
            if (this.btnApply.Tag == null)
            {
                RadioButton rb = sender as RadioButton;
                if ((rb != null) && rb.Checked && (rb.Tag != null))
                    this.currentSelection = (GeoTransformSelection)rb.Tag;
                UpdateControls();
            }
        }
        private void ResetControls()
        {
            // Parameters group
            this.cboDirection.SelectedIndex = 0;
            this.cboInterpMethod.SelectedIndex = 0;

            // OpenMesh group
            this.lblMeshFile.Text = "";

            // NewMesh group
            this.cboMeshCols.Text = "5";
            this.cboMeshRows.Text = "5";
            this.txtNumPoints.Text = this.NumPoints.ToString();

            // Default current selection
            this.rbNewMesh.PerformClick();

            // enable Apply button
            this.btnApply.Enabled = true;
            this.Cursor = Cursors.Default;
        }
        private void txtMeshPoint_Validated(object sender, EventArgs e)
        {
            ViewerForm viewer = MainForm.Viewers.SelectedViewer;
            if (viewer != null)
            {
                int col, row;
                if (int.TryParse(this.txtMeshCol.Text, out col) &&
                    int.TryParse(this.txtMeshRow.Text, out row))
                {
                    viewer.MeshSelectedValue = new Point(col, row);
                }
            }
        }
        private void UpdateControls()
        {
            switch (this.currentSelection)
            {
            case GeoTransformSelection.newmesh:
                this.cboMeshCols.Text = "5";
                this.cboMeshRows.Text = "5";
                this.lblNotes.Visible = true;
                this.grpOpenMesh.Visible = false;
                this.lblMeshCols.Visible = true;
                this.cboMeshCols.Visible = true;
                this.lblMeshRows.Visible = true;
                this.cboMeshRows.Visible = true;
                this.lblMeshPoints.Visible = true;
                this.lblNumPoints.Visible = true;
                this.lblNumPoints1.Visible = true;
                this.txtNumPoints.Visible = true;
                this.btnRedoMesh.Visible = true;
                this.lblMeshStatus.Visible = true;
                this.lblExample.Visible = true;
                this.picMeshExample.Visible = true;
                this.btnRedoMesh.PerformClick();
                break;

            case GeoTransformSelection.openmesh:
                this.lblNotes.Visible = false;
                this.grpOpenMesh.Visible = true;
                this.lblMeshCols.Visible = false;
                this.cboMeshCols.Visible = false;
                this.lblMeshRows.Visible = false;
                this.cboMeshRows.Visible = false;
                this.lblMeshPoints.Visible = false;
                this.lblNumPoints.Visible = false;
                this.lblNumPoints1.Visible = false;
                this.txtNumPoints.Visible = false;
                this.btnRedoMesh.Visible = false;
                this.lblMeshStatus.Visible = false;
                this.lblExample.Visible = false;
                this.picMeshExample.Visible = false;
                break;

            case GeoTransformSelection.sinemesh:
                this.cboMeshCols.Text = "16";
                this.cboMeshRows.Text = "16";
                this.lblNotes.Visible = false;
                this.grpOpenMesh.Visible = false;
                this.lblMeshCols.Visible = true;
                this.cboMeshCols.Visible = true;
                this.lblMeshRows.Visible = true;
                this.cboMeshRows.Visible = true;
                this.lblMeshPoints.Visible = true;
                this.lblNumPoints.Visible = false;
                this.lblNumPoints1.Visible = false;
                this.txtNumPoints.Visible = false;
                this.btnRedoMesh.Visible = false;
                this.lblMeshStatus.Visible = false;
                this.lblExample.Visible = false;
                this.picMeshExample.Visible = false;
                break;
            }
            // enable Apply button
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
                    ViewerForm.AltMouseClicked += this.OnViewerAltMouseClicked;
                    ViewerForm.MeshChanged += this.OnSelectedViewerChanged;
                    break;

                case WM.DESTROY:
                    MainForm.Viewers.SelectedViewerChanged -= this.OnSelectedViewerChanged;
                    ViewerForm.AltMouseClicked -= this.OnViewerAltMouseClicked;
                    ViewerForm.MeshChanged -= this.OnSelectedViewerChanged;
                    break;
                }
            }
        }

        private int InterpMethod
        {
            get
            {
                int method = -1;
                switch (this.cboInterpMethod.SelectedIndex)
                {
                case 0: method = 1; break;
                case 1: method = 3; break;
                case 2: method = 2; break;
                }
                return method;
            }
        }
        private int MeshCols { get { return int.Parse(this.cboMeshCols.Text); } }
        private int MeshRows { get { return int.Parse(this.cboMeshRows.Text); } }
        private int NumPoints { get { return this.MeshCols * this.MeshRows; } }
    }
}
