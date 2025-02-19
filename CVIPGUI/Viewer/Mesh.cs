/*''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' ======================================================================
' Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
' ======================================================================
'
'             File Name: Mesh.cs
'           Description: Contains the controls and code
'                        for ViewerForm->Mesh class
'         Related Files: ViewerForm.cs
'   Initial Coding Date: December 2009
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
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Text;
using System.Windows.Forms;

namespace CVIPGUI
{
    [Serializable]
    public class Mesh
    {
        private Point ptSelected = CvipConstant.ptEmpty;
        private Point[,] ptsMesh = null;

        [NonSerialized]
        private bool bMouseDragging = false;
        [NonSerialized]
        private ViewerForm frmViewer = null;

        static public event ViewerChanged MeshChanged;

        public Mesh(ViewerForm viewer)
        {
            this.frmViewer = viewer;
        }
        public Mesh(ViewerForm viewer, Mesh mesh)
        {
            this.frmViewer = viewer;
            if (mesh.Points != null)
            {
                this.ptsMesh = new Point[mesh.Rows, mesh.Cols];
                this.ptSelected = mesh.SelectedPoint;
                for (int r = 0; r < mesh.Rows; r++)
                {
                    for (int c = 0; c < mesh.Cols; c++)
                    {
                        this.Points[r, c] = mesh.Points[r, c];
                    }
                }
            }
            this.frmViewer.ShowMesh = (this.Points != null);
        }
        public void AddPoint(Point pt)
        {
            if (this.Points != null)
            {
                for (int r = 0; r < this.Rows; r++)
                {
                    for (int c = 0; c < this.Cols; c++)
                    {
                        if (this.Points[r, c] == CvipConstant.ptEmpty)
                        {
                            this.Points[r, c] = pt;
                            this.ptSelected = new Point(c, r);
                            this.frmViewer.Refresh();
                            if (Mesh.MeshChanged != null)
                                Mesh.MeshChanged(this.frmViewer);
                            return;
                        }
                    }
                }
            }
        }
        public void Clear()
        {
            if (this.Points != null)
            {
                this.ptsMesh = null;
                this.ptSelected = CvipConstant.ptEmpty;
                this.frmViewer.Refresh();
                if (Mesh.MeshChanged != null)
                    Mesh.MeshChanged(this.frmViewer);
            }
        }
        public void CreateMesh(int rows, int cols)
        {
            this.ptsMesh = new Point[rows, cols];
            this.ptSelected = CvipConstant.ptEmpty;
            for (int r = 0; r < rows; r++)
            {
                for (int c = 0; c < cols; c++)
                {
                    this.Points[r, c] = CvipConstant.ptEmpty;
                }
            }
            this.frmViewer.ShowMesh = (this.Points != null);
            if (Mesh.MeshChanged != null)
                Mesh.MeshChanged(this.frmViewer);
        }
        public void CreateSineMesh(int rows, int cols)
        {
            this.ptsMesh = CvipOp.Create_Mesh_Sine(rows, cols);
            this.ptSelected = new Point(0, 0);
            this.frmViewer.ShowMesh = (this.Points != null);
            if (Mesh.MeshChanged != null)
                Mesh.MeshChanged(this.frmViewer);
        }
        public void Draw(Graphics g)
        {
            if (this.Points != null)
            {
                try
                {
                    GraphicsPath gp = new GraphicsPath();
                    for (int r = 0; r < this.Rows; r++)
                    {
                        for (int c = 0; c < this.Cols; c++)
                        {
                            Point p1 = this.Points[r, c];
                            if (p1 == CvipConstant.ptEmpty)
                                continue;
                            gp.AddEllipse(p1.X - 2, p1.Y - 2, 4, 4);
                            if ((c + 1) < this.Cols)
                            {
                                Point p2 = this.Points[r, c + 1];
                                if (p2 != CvipConstant.ptEmpty)
                                {
                                    gp.AddLine(p1, p2);
                                    gp.StartFigure();
                                }
                            }
                            if ((r + 1) < this.Rows)
                            {
                                Point p2 = this.Points[r + 1, c];
                                if (p2 != CvipConstant.ptEmpty)
                                {
                                    gp.AddLine(p1, p2);
                                    gp.StartFigure();
                                }
                            }
                        }
                    }
                    float fScaleX = (float)this.frmViewer.ClientSize.Width / this.frmViewer.ImageWidth;
                    float fScaleY = (float)this.frmViewer.ClientSize.Height / this.frmViewer.ImageHeight;
                    Matrix m = new Matrix();
                    m.Scale(fScaleX, fScaleY);
                    gp.Transform(m);
                    g.FillPath(Brushes.Red, gp);
                    g.DrawPath(Pens.Red, gp);
                    if (this.SelectedPoint != CvipConstant.ptEmpty)
                    {
                        Point pt = this.SelectedValue;
                        gp.Reset();
                        gp.AddEllipse(pt.X - 2, pt.Y - 2, 4, 4);
                        gp.Transform(m);
                        g.FillPath(Brushes.Blue, gp);
                    }
                }
                catch { }
            }
        }
        public Point HitTest(Point pt)
        {
            Point ptClosest = CvipConstant.ptEmpty;
            if (this.Points != null)
            {
                int border = 5, mindist = int.MaxValue;
                for (int r = 0; r < this.Rows; r++)
                {
                    for (int c = 0; c < this.Cols; c++)
                    {
                        if (this.Points[r, c] != CvipConstant.ptEmpty)
                        {
                            int xdist = Math.Abs(this.Points[r, c].X - pt.X);
                            int ydist = Math.Abs(this.Points[r, c].Y - pt.Y);
                            if ((xdist <= border) && (ydist <= border))
                            {
                                int dist = xdist * xdist + ydist * ydist;
                                if (dist < mindist)
                                {
                                    ptClosest = new Point(c, r);
                                    mindist = dist;
                                }
                            }
                        }
                    }
                }
            }
            return ptClosest;
        }
        public string OpenFile()
        {
            string meshFile = null;
            string meshHome = MainForm.CVIPtoolsHOME;
            if (!string.IsNullOrEmpty(meshHome))
                meshHome += @"bin\mesh";

            OpenFileDialog dlgOpenFile = new OpenFileDialog();
            dlgOpenFile.CheckFileExists = true;
            dlgOpenFile.Filter = "All Files(*.*)|*.*";
            dlgOpenFile.FilterIndex = 1;
            dlgOpenFile.InitialDirectory = meshHome;
            dlgOpenFile.Multiselect = false;
            dlgOpenFile.Title = "Load Mesh";
            if (dlgOpenFile.ShowDialog() != DialogResult.Cancel)
            {
                try
                {
                    Point[,] pts = CvipOp.File_To_Mesh(dlgOpenFile.FileName);
                    if (pts != null)
                    {
                        this.ptsMesh = pts;
                        this.ptSelected = new Point(0, 0);
                        this.frmViewer.ShowMesh = (this.Points != null);
                        if (Mesh.MeshChanged != null)
                            Mesh.MeshChanged(this.frmViewer);
                        meshFile = dlgOpenFile.FileName;
                    }
                }
                catch { }
            }
            return meshFile;
        }
        public string SaveToFile()
        {
            if (!this.Complete)
            {
                MessageBox.Show("There are no mesh points to save!", "No Mesh Points",
                    MessageBoxButtons.OK, MessageBoxIcon.Warning);
                return null;
            }
            string meshFile = null;
            string meshHome = MainForm.CVIPtoolsHOME;
            if (!string.IsNullOrEmpty(meshHome))
                meshHome += @"bin\mesh";

            SaveFileDialog dlgSaveFile = new SaveFileDialog();
            dlgSaveFile.Filter = "All Files(*.*)|*.*";
            dlgSaveFile.FilterIndex = 1;
            dlgSaveFile.InitialDirectory = meshHome;
            dlgSaveFile.Title = "Save Mesh";
            if (dlgSaveFile.ShowDialog() != DialogResult.Cancel)
            {
                CvipOp.Mesh_To_File(dlgSaveFile.FileName, this.Points);
                meshFile = dlgSaveFile.FileName;
            }
            return meshFile;
        }

        public bool MouseDragging
        {
            get { return this.bMouseDragging; }
            set { this.bMouseDragging = value; }
        }
        public int Cols { get { return (this.Points == null) ? -1 : this.Points.GetLength(1); } }
        public int Rows { get { return (this.Points == null) ? -1 : this.Points.GetLength(0); } }
        public int NumPoints { get { return (this.Points == null) ? -1 : (this.Cols * this.Rows); } }
        public Point[,] Points { get { return this.ptsMesh; } }
        public bool Complete
        {
            get
            {
                bool complete = false;
                if (this.Points != null)
                    complete = (this.PointsCompleted == this.NumPoints);
                return complete;
            }
        }
        public int PointsCompleted
        {
            get
            {
                int completed = -1;
                if (this.Points != null)
                {
                    completed = 0;
                    for (int r = 0; r < this.Rows; r++)
                    {
                        for (int c = 0; c < this.Cols; c++)
                        {
                            if (this.Points[r, c] != CvipConstant.ptEmpty)
                                completed++;
                        }
                    }
                }
                return completed;
            }
        }
        public int SelectedIndex
        {
            get
            {
                int idx = -1;
                if (this.SelectedPoint != CvipConstant.ptEmpty)
                    idx = (this.SelectedPoint.Y * this.Cols) + this.SelectedPoint.X;
                return idx;
            }
            set
            {
                Point selected = CvipConstant.ptEmpty;
                if ((value >= 0) && (value < this.NumPoints))
                    selected = new Point(value % this.Cols, value / this.Cols);
                this.SelectedPoint = selected;
            }
        }
        public Point SelectedPoint
        {
            get { return this.ptSelected; }
            set
            {
                this.ptSelected = value;
                this.frmViewer.Refresh();
                if (Mesh.MeshChanged != null)
                    Mesh.MeshChanged(this.frmViewer);
            }
        }
        public Point SelectedValue
        {
            get
            {
                Point val = CvipConstant.ptEmpty;
                if (this.SelectedPoint != CvipConstant.ptEmpty)
                    val = this.Points[this.SelectedPoint.Y, this.SelectedPoint.X];
                return val;
            }
            set
            {
                if (this.SelectedPoint != CvipConstant.ptEmpty)
                {
                    this.Points[this.SelectedPoint.Y, this.SelectedPoint.X] = value;
                    this.frmViewer.Refresh();
                    if (Mesh.MeshChanged != null)
                        Mesh.MeshChanged(this.frmViewer);
                }
            }
        }
        public string Status
        {
            get
            {
                string status = "";
                if (this.Points != null)
                {
                    int completed = this.PointsCompleted;
                    int needed = this.NumPoints;
                    if (completed == needed)
                        status = "Ready";
                    else
                        status = completed + " of " + needed + " points completed";
                }
                return (status);
            }
        }
    }
}
