/*''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' ======================================================================
' Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
' ======================================================================
'
'             File Name: CustomRemapForm.cs
'           Description: Contains the controls and code
'                        for Enhancement->CustomRemapForm page
'         Related Files: CvipOp.cs
'                        CvipConstant.cs
'   Initial Coding Date: November 2011
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
using System.IO;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace CVIPGUI
{
    public partial class CustomRemapForm : Form
    {
        public event GenericStateChange MapFileCollectionChanged;

        readonly Point ptOrigin = new Point(60, 295); // Screen coordinates of the point (0, 0)

        // Saves the previous mouse point
        Point ptPrev = CvipConstant.ptEmpty;

        // Saves input points. -1 means need interpolate
        int[] nPtsEnteredRed = null;
        int[] nPtsEnteredGreen = null;
        int[] nPtsEnteredBlue = null;

        // Saves the input points and interpolated points
        byte[] bPtsInterpolatedRed = null;
        byte[] bPtsInterpolatedGreen = null;
        byte[] bPtsInterpolatedBlue = null;

        public CustomRemapForm()
        {
            InitializeComponent();
            this.MdiParent = MainForm.TheMainForm;

            // Saves input points. -1 means need interpolate
            this.nPtsEnteredRed = Enumerable.Repeat(-1, 256).ToArray();
            this.nPtsEnteredGreen = Enumerable.Repeat(-1, 256).ToArray();
            this.nPtsEnteredBlue = Enumerable.Repeat(-1, 256).ToArray();

            this.nPtsEnteredRed[0] = this.nPtsEnteredGreen[0] = this.nPtsEnteredBlue[0] = 0;
            this.nPtsEnteredRed[255] = this.nPtsEnteredGreen[255] = this.nPtsEnteredBlue[255] = 255;
        }
        private void btnAdd_Click(object sender, EventArgs e)
        {
            Point pt = this.PointToAdd;
            if (this.rbAll.Checked || this.rbRed.Checked)
            {
                this.nPtsEnteredRed[pt.X] = pt.Y;
                this.bPtsInterpolatedRed = null;
            }
            if (this.rbAll.Checked || this.rbGreen.Checked)
            {
                this.nPtsEnteredGreen[pt.X] = pt.Y;
                this.bPtsInterpolatedGreen = null;
            }
            if (this.rbAll.Checked || this.rbBlue.Checked)
            {
                this.nPtsEnteredBlue[pt.X] = pt.Y;
                this.bPtsInterpolatedBlue = null;
            }
            Refresh();
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

            int i, j = 0;
            int[] nMapData = new int[768];
            for (i = 0; i < 256; i++) nMapData[j++] = this.PointsInterpolatedRed[i];
            for (i = 0; i < 256; i++) nMapData[j++] = this.PointsInterpolatedGreen[i];
            for (i = 0; i < 256; i++) nMapData[j++] = this.PointsInterpolatedBlue[i];

            // get the image that will be operated on
            int inputImage = viewer.CVIPimage;
            int outputImage = CvipOp.P_Remap(inputImage, nMapData);

            if (outputImage != 0)
            {
                string newImageName = viewer.Text + "_" + CvipFunctionNames.getFncName("Pseudo_Remap");
                newImageName += CvipConstant.imageNameCount++.ToString();
                MainForm.Viewers.Add(outputImage, newImageName);
            }
            // delete input image
            CvipOp.Delete_Image(ref inputImage);

            // enable Apply button
            this.btnApply.Enabled = true;
            this.Cursor = Cursors.Default;
        }
        private void btnClose_Click(object sender, EventArgs e)
        {
            Close();
        }
        private void btnOpenMapFile_Click(object sender, EventArgs e)
        {
            string cvipHome = MainForm.CVIPtoolsHOME, sMapDirectory = null;
            if (!string.IsNullOrEmpty(cvipHome))
                sMapDirectory = cvipHome + @"bin\remap";

            OpenFileDialog dlg = new OpenFileDialog();
            dlg.Filter = "Color Map File(*.map)|*.map";
            dlg.FilterIndex = 1;
            dlg.InitialDirectory = sMapDirectory;
            dlg.Title = "Load Pseudocolor Map";
            if (dlg.ShowDialog() == DialogResult.OK)
            {
                FileInfo fi = new FileInfo(dlg.FileName);
                if (fi.Length < 3840)
                {
                    MessageBox.Show(fi.FullName + " is in the old map format. We cannot display its curve. Please try another one.",
                        "File format error", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    return;
                }
                using (BinaryReader br = new BinaryReader(fi.OpenRead()))
                {
                    br.BaseStream.Seek(768, SeekOrigin.Begin);
                    for (int i = 0; i < 256; i++) this.nPtsEnteredRed[i] = br.ReadInt32();
                    for (int i = 0; i < 256; i++) this.nPtsEnteredGreen[i] = br.ReadInt32();
                    for (int i = 0; i < 256; i++) this.nPtsEnteredBlue[i] = br.ReadInt32();
                }
                this.bPtsInterpolatedRed = null;
                this.bPtsInterpolatedGreen = null;
                this.bPtsInterpolatedBlue = null;
                Refresh();
            }
        }
        private void btnSave_Click(object sender, EventArgs e)
        {
            string cvipHome = MainForm.CVIPtoolsHOME, sMapDirectory = null;
            if (!string.IsNullOrEmpty(cvipHome))
                sMapDirectory = cvipHome + @"bin\remap";

            SaveFileDialog dlg = new SaveFileDialog();
            dlg.Filter = "Color map file(*.map)|*.map";
            dlg.FilterIndex = 1;
            dlg.InitialDirectory = sMapDirectory;
            dlg.Title = "Save Pseudocolor Map";
            if (dlg.ShowDialog() == DialogResult.OK)
            {
                FileInfo fi = new FileInfo(dlg.FileName);
                if (fi.Exists) fi.Delete();
                using (BinaryWriter bw = new BinaryWriter(fi.Create()))
                {
                    for (int i = 0; i < 256; i++) bw.Write(this.PointsInterpolatedRed[i]);
                    for (int i = 0; i < 256; i++) bw.Write(this.PointsInterpolatedGreen[i]);
                    for (int i = 0; i < 256; i++) bw.Write(this.PointsInterpolatedBlue[i]);
                    for (int i = 0; i < 256; i++) bw.Write(this.nPtsEnteredRed[i]);
                    for (int i = 0; i < 256; i++) bw.Write(this.nPtsEnteredGreen[i]);
                    for (int i = 0; i < 256; i++) bw.Write(this.nPtsEnteredBlue[i]);
                }
                if ((fi.DirectoryName.ToLower().TrimEnd('\\') == sMapDirectory.ToLower()) &&
                    (this.MapFileCollectionChanged != null))
                {
                    this.MapFileCollectionChanged();
                }
            }
        }
        protected void cboUIntVal_Validating(object sender, CancelEventArgs e)
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
        private void DrawAxis(Graphics g)
        {
            // x, y axis
            g.DrawRectangle(Pens.Black, new Rectangle(this.ptOrigin.X, this.ptOrigin.Y - 255, 255, 255));

            // tick marks
            const int numticks = 16;
            const int step = 16;

            int x = this.ptOrigin.X;
            int y = this.ptOrigin.Y;
            for (int i = 0; i < numticks; i++)
            {
                if ((i % 2) == 0)
                {
                    g.DrawLine(Pens.Red, x, this.ptOrigin.Y, x, this.ptOrigin.Y - 6);
                    g.DrawLine(Pens.Red, this.ptOrigin.X, y, this.ptOrigin.X + 6, y);
                }
                else
                {
                    g.DrawLine(Pens.Red, x, this.ptOrigin.Y, x, this.ptOrigin.Y - 3);
                    g.DrawLine(Pens.Red, this.ptOrigin.X, y, this.ptOrigin.X + 3, y);
                }

                x += step;
                y -= step;
            }
        }
        private Point FindClosestPoint(Point pt)
        {
            Point ptClosest = CvipConstant.ptEmpty;
            int border = 5, dist, mindist = int.MaxValue, x;

            if (this.rbAll.Checked || this.rbRed.Checked)
            {
                for (x = pt.X - border; x <= pt.X + border; x++)
                {
                    if ((x >= 0) && (x < 256) &&
                        (this.nPtsEnteredRed[x] != -1) &&
                        (Math.Abs(this.nPtsEnteredRed[x] - pt.Y) <= border))
                    {
                        dist = Math.Abs(x - pt.X) + Math.Abs(this.nPtsEnteredRed[x] - pt.Y);
                        if (dist < mindist)
                        {
                            ptClosest.X = x;
                            ptClosest.Y = this.nPtsEnteredRed[x];
                            mindist = dist;
                        }
                    }
                }
            }
            if (this.rbAll.Checked || this.rbGreen.Checked)
            {
                for (x = pt.X - border; x <= pt.X + border; x++)
                {
                    if ((x >= 0) && (x < 256) &&
                        (this.nPtsEnteredGreen[x] != -1) &&
                        (Math.Abs(this.nPtsEnteredGreen[x] - pt.Y) <= border))
                    {
                        dist = Math.Abs(x - pt.X) + Math.Abs(this.nPtsEnteredGreen[x] - pt.Y);
                        if (dist < mindist)
                        {
                            ptClosest.X = x;
                            ptClosest.Y = this.nPtsEnteredGreen[x];
                            mindist = dist;
                        }
                    }
                }
            }
            if (this.rbAll.Checked || this.rbBlue.Checked)
            {
                for (x = pt.X - border; x <= pt.X + border; x++)
                {
                    if ((x >= 0) && (x < 256) &&
                        (this.nPtsEnteredBlue[x] != -1) &&
                        (Math.Abs(this.nPtsEnteredBlue[x] - pt.Y) <= border))
                    {
                        dist = Math.Abs(x - pt.X) + Math.Abs(this.nPtsEnteredBlue[x] - pt.Y);
                        if (dist < mindist)
                        {
                            ptClosest.X = x;
                            ptClosest.Y = this.nPtsEnteredBlue[x];
                            mindist = dist;
                        }
                    }
                }
            }
            return ptClosest;
        }
        private void GetRidOf(Point pt)
        {
            if ((pt.X > 0) && (pt.X < 255))
            {
                if ((this.rbAll.Checked || this.rbRed.Checked) &&
                    (this.nPtsEnteredRed[pt.X] == pt.Y))
                {
                    this.nPtsEnteredRed[pt.X] = -1;
                    this.bPtsInterpolatedRed = null;
                }
                if ((this.rbAll.Checked || this.rbGreen.Checked) &&
                    (this.nPtsEnteredGreen[pt.X] == pt.Y))
                {
                    this.nPtsEnteredGreen[pt.X] = -1;
                    this.bPtsInterpolatedGreen = null;
                }
                if ((this.rbAll.Checked || this.rbBlue.Checked) &&
                    (this.nPtsEnteredBlue[pt.X] == pt.Y))
                {
                    this.nPtsEnteredBlue[pt.X] = -1;
                    this.bPtsInterpolatedBlue = null;
                }
                Refresh();
            }
        }
        private Point GraphToWindow(int nGraphX, int nGraphY)
        {
            Point ptWindow = CvipConstant.ptEmpty;
            if ((nGraphX >= 0) && (nGraphX <= 255) &&
                (nGraphY >= 0) && (nGraphY <= 255))
            {
                ptWindow = new Point(this.ptOrigin.X + nGraphX, this.ptOrigin.Y - nGraphY);
            }
            return ptWindow;
        }
        private Point GraphToWindow(Point ptGraph)
        {
            return GraphToWindow(ptGraph.X, ptGraph.Y);
        }
        private byte[] Interpolate(int[] nPtsEntered)
        {
            byte[] bPtsInterpolated = null;
            if (this.rbLinear.Checked)
            {
                bPtsInterpolated = LinearInterpolate(nPtsEntered);
            }
            else
            {
                bPtsInterpolated = LagrangeInterpolate(nPtsEntered);
            }
            return bPtsInterpolated;
        }
        private byte[] LagrangeInterpolate(int[] nPtsEntered)
        {
            List<Point> pts = new List<Point>();
            for (int x = 0; x < 256; x++)
            {
                if (nPtsEntered[x] != -1)
                    pts.Add(new Point(x, nPtsEntered[x]));
            }
            byte[] bPtsInterpolated = new byte[256];
            for (int x = 0; x < 256; x++)
            {
                if (nPtsEntered[x] != -1)
                {
                    bPtsInterpolated[x] = (byte)nPtsEntered[x];
                }
                else
                {
                    double sum = 0.0;
                    for (int i = 0; i < pts.Count; i++)
                        sum += LagrangePolynomial(x, i, pts) * (double)pts[i].Y;
                    int y = (int)(sum + 0.5);
                    y = Math.Max(0, y);
                    y = Math.Min(y, 255);
                    bPtsInterpolated[x] = (byte)y;
                }
            }
            return bPtsInterpolated;
        }
        private double LagrangePolynomial(int x, int j, List<Point> pts)
        {
            double poly = 1.0;
            for (int i = 0; i < pts.Count; i++)
            {
                if (i != j)
                {
                    poly *= (double)(x - pts[i].X) / (double)(pts[j].X - pts[i].X);
                }
            }
            return poly;
        }
        private byte[] LinearInterpolate(int[] nPtsEntered)
        {
            byte[] bPtsInterpolated = new byte[256];
            int x1 = -1, y = 0;
            double slope = 0.0;
            for (int x = 0; x < 256; x++)
            {
                if (nPtsEntered[x] != -1)
                {
                    bPtsInterpolated[x] = (byte)nPtsEntered[x];
                    if (x1 == -1)
                    {
                        x1 = x;
                        continue;
                    }
                    slope = (double)(nPtsEntered[x] - nPtsEntered[x1]) / (double)(x - x1);
                    for (int i = x1 + 1; i < x; i++)
                    {
                        y = (int)((slope * (double)(i - x1)) + nPtsEntered[x1] + 0.5);
                        y = Math.Max(0, y);
                        y = Math.Min(y, 255);
                        bPtsInterpolated[i] = (byte)y;
                    }
                    x1 = x;
                }
            }
            return bPtsInterpolated;
        }
        protected override void OnFormClosing(FormClosingEventArgs e)
        {
            base.OnFormClosing(e);
            MainForm.CustomRemapForm = null;
        }
        protected override void OnMouseDown(MouseEventArgs e)
        {
            base.OnMouseDown(e);

            Point pt = WindowToGraph(e.Location);
            if (pt != CvipConstant.ptEmpty)
            {
                this.PointToAdd = this.CurrentPoint = pt;
                this.ptPrev = FindClosestPoint(pt);
            }
        }
        protected override void OnMouseMove(MouseEventArgs e)
        {
            base.OnMouseMove(e);

            Point pt = WindowToGraph(e.Location);
            if (pt != CvipConstant.ptEmpty)
            {
                this.CurrentPoint = pt;

                if (this.ptPrev != CvipConstant.ptEmpty)
                {
                    Reposition(this.ptPrev, pt);
                    this.ptPrev = pt;
                }
            }
        }
        protected override void OnMouseUp(MouseEventArgs e)
        {
            base.OnMouseUp(e);

            Point pt = WindowToGraph(e.Location);
            if (pt != CvipConstant.ptEmpty)
            {
                this.PointToAdd = this.CurrentPoint = pt;
                if ((this.ptPrev == CvipConstant.ptEmpty) &&
                    (e.Button == MouseButtons.Left))
                {
                    btnAdd.PerformClick();
                }
            }
            if (this.ptPrev != CvipConstant.ptEmpty)
            {
                if (e.Button == MouseButtons.Left)
                {
                    Reposition(this.ptPrev, this.CurrentPoint);
                }
                else
                {
                    GetRidOf(this.ptPrev);
                }
                this.ptPrev = CvipConstant.ptEmpty;
            }
        }
        protected override void OnPaint(PaintEventArgs e)
        {
            base.OnPaint(e);

            DrawAxis(e.Graphics);

            if (this.rbAll.Checked || this.rbRed.Checked)
            {
                byte[] pts = this.PointsInterpolatedRed;
                for (int x = 0; x < 256; x++)
                {
                    // draw input points in red band (red circle)
                    if (this.nPtsEnteredRed[x] != -1)
                    {
                        Rectangle rct = new Rectangle(GraphToWindow(x, this.nPtsEnteredRed[x]), new Size(10, 10));
                        rct.Offset(-5, -5);
                        e.Graphics.FillEllipse(Brushes.Red, rct);
                    }
                    // draw curve in red band
                    if (x == 0) continue;
                    Point p1 = GraphToWindow(x - 1, pts[x - 1]);
                    Point p2 = GraphToWindow(x, pts[x]);
                    p1.Offset(0, -1);
                    p2.Offset(0, -1);
                    e.Graphics.DrawLine(Pens.Red, p1, p2);
                }
            }
            if (this.rbAll.Checked || this.rbGreen.Checked)
            {
                byte[] pts = this.PointsInterpolatedGreen;
                for (int x = 0; x < 256; x++)
                {
                    // draw input points in green band (green vertical line)
                    if (this.nPtsEnteredGreen[x] != -1)
                    {
                        Rectangle rct = new Rectangle(GraphToWindow(x, this.nPtsEnteredGreen[x]), new Size(4, 10));
                        rct.Offset(-2, -5);
                        e.Graphics.FillRectangle(Brushes.Green, rct);
                    }
                    // draw curve in green band
                    if (x == 0) continue;
                    Point p1 = GraphToWindow(x - 1, pts[x - 1]);
                    Point p2 = GraphToWindow(x, pts[x]);
                    e.Graphics.DrawLine(Pens.Green, p1, p2);
                }
            }
            if (this.rbAll.Checked || this.rbBlue.Checked)
            {
                byte[] pts = this.PointsInterpolatedBlue;
                for (int x = 0; x < 256; x++)
                {
                    // draw input points in blue band (blue horizontal line)
                    if (this.nPtsEnteredBlue[x] != -1)
                    {
                        Rectangle rct = new Rectangle(GraphToWindow(x, this.nPtsEnteredBlue[x]), new Size(10, 4));
                        rct.Offset(-5, -2);
                        e.Graphics.FillRectangle(Brushes.Blue, rct);
                    }
                    // draw curve in blue band
                    if (x == 0) continue;
                    Point p1 = GraphToWindow(x - 1, pts[x - 1]);
                    Point p2 = GraphToWindow(x, pts[x]);
                    p1.Offset(0, 1);
                    p2.Offset(0, 1);
                    e.Graphics.DrawLine(Pens.Blue, p1, p2);
                }
            }
        }
        private void rbInterpolationMethod_CheckedChanged(object sender, EventArgs e)
        {
            this.bPtsInterpolatedRed = null;
            this.bPtsInterpolatedGreen = null;
            this.bPtsInterpolatedBlue = null;
            Refresh();
        }
        private void rbRGB_CheckedChanged(object sender, EventArgs e)
        {
            Refresh();
        }
        private void Reposition(Point ptOld, Point ptNew)
        {
            if ((ptOld.X != -1) && (ptOld.Y != -1))
            {
                if (ptOld.X == 0) ptNew.X = 0;
                if (ptOld.X == 255) ptNew.X = 255;

                if ((this.rbAll.Checked || this.rbRed.Checked) &&
                    (this.nPtsEnteredRed[ptOld.X] == ptOld.Y))
                {
                    this.nPtsEnteredRed[ptOld.X] = -1;
                    this.nPtsEnteredRed[ptNew.X] = ptNew.Y;
                    this.bPtsInterpolatedRed = null;
                }
                if ((this.rbAll.Checked || this.rbGreen.Checked) &&
                    (this.nPtsEnteredGreen[ptOld.X] == ptOld.Y))
                {
                    this.nPtsEnteredGreen[ptOld.X] = -1;
                    this.nPtsEnteredGreen[ptNew.X] = ptNew.Y;
                    this.bPtsInterpolatedGreen = null;
                }
                if ((this.rbAll.Checked || this.rbBlue.Checked) &&
                    (this.nPtsEnteredBlue[ptOld.X] == ptOld.Y))
                {
                    this.nPtsEnteredBlue[ptOld.X] = -1;
                    this.nPtsEnteredBlue[ptNew.X] = ptNew.Y;
                    this.bPtsInterpolatedBlue = null;
                }
                Refresh();
            }
        }
        private Point WindowToGraph(Point ptWindow)
        {
            Point ptGraph = CvipConstant.ptEmpty;
            int nGraphX = ptWindow.X - this.ptOrigin.X;
            int nGraphY = this.ptOrigin.Y - ptWindow.Y;
            if ((nGraphX >= 0) && (nGraphX <= 255) &&
                (nGraphY >= 0) && (nGraphY <= 255))
            {
                ptGraph = new Point(nGraphX, nGraphY);
            }
            return ptGraph;
        }

        byte[] PointsInterpolatedRed
        {
            get
            {
                if (this.bPtsInterpolatedRed == null)
                {
                    this.bPtsInterpolatedRed = Interpolate(this.nPtsEnteredRed);
                }
                return this.bPtsInterpolatedRed;
            }
        }
        byte[] PointsInterpolatedGreen
        {
            get
            {
                if (this.bPtsInterpolatedGreen == null)
                {
                    this.bPtsInterpolatedGreen = Interpolate(this.nPtsEnteredGreen);
                }
                return this.bPtsInterpolatedGreen;
            }
        }
        byte[] PointsInterpolatedBlue
        {
            get
            {
                if (this.bPtsInterpolatedBlue == null)
                {
                    this.bPtsInterpolatedBlue = Interpolate(this.nPtsEnteredBlue);
                }
                return this.bPtsInterpolatedBlue;
            }
        }
        private Point PointToAdd
        {
            get
            {
                int x = int.Parse(this.cboAddX.Text);
                int y = int.Parse(this.cboAddY.Text);
                return new Point(x, y);
            }
            set
            {
                this.cboAddX.Text = value.X.ToString();
                this.cboAddY.Text = value.Y.ToString();
            }
        }
        private Point CurrentPoint
        {
            get
            {
                int x = int.Parse(this.txtCurrentX.Text);
                int y = int.Parse(this.txtCurrentY.Text);
                return new Point(x, y);
            }
            set
            {
                this.txtCurrentX.Text = value.X.ToString();
                this.txtCurrentY.Text = value.Y.ToString();
            }
        }
    }
}
