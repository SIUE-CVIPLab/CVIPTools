/*''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' ======================================================================
' Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
' ======================================================================
'
'             File Name: AreaSelection.cs
'           Description: Contains the controls and code
'                        for ViewerForm->AreaSelection class
'         Related Files: ViewerForm.cs
'   Initial Coding Date: December 2009
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
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Text;
using System.Threading;

namespace CVIPGUI
{
    public delegate void RectangleChanged(Rectangle rect, ViewerForm viewer);

    public enum SelectionState
    {
        Idle,
        SelectingBorder,
        SelectingRectangle,
        BorderSelected,
        RectangleSelected
    }
    public class AreaSelection
    {
        static private int nAntOffset = 0;
        static private Timer AntTimer = new Timer(AreaSelection.OnAntTmer, null, Timeout.Infinite, Timeout.Infinite);
        static private GenericStateChange AntTimerTick;
        static public event RectangleChanged BoundingRectangleChanged;

        private Point ptP1 = CvipConstant.ptEmpty;
        private GraphicsPath gpSelectedArea = new GraphicsPath();
        private SelectionState ssCurrent = SelectionState.Idle;
        private ViewerForm frmViewer = null;

        public AreaSelection(ViewerForm viewer)
        {
            this.frmViewer = viewer;
        }
        public void AddPoint(Point pt)
        {
            switch (this.ssCurrent)
            {
            case SelectionState.Idle:
            case SelectionState.BorderSelected:
            case SelectionState.RectangleSelected:
                return;
            case SelectionState.SelectingBorder:
                this.gpSelectedArea.AddLine(this.ptP1, pt);
                this.ptP1 = pt;
                break;
            case SelectionState.SelectingRectangle:
                Rectangle rect = NormalizedRectangle(this.ptP1, pt);
                this.gpSelectedArea.Reset();
                this.gpSelectedArea.AddRectangle(rect);
                break;
            }
            if (AreaSelection.BoundingRectangleChanged != null)
                AreaSelection.BoundingRectangleChanged(this.BoundingRectangle, this.frmViewer);
            this.frmViewer.Invalidate();
        }
        public void BeginBorder(Point pt)
        {
            AreaSelection.AntTimerTick -= this.OnAntTimerTick;
            this.ssCurrent = SelectionState.SelectingBorder;
            this.gpSelectedArea.Reset();
            this.ptP1 = pt;
            this.frmViewer.Invalidate();
        }
        public void BeginRectangle(Point pt)
        {
            AreaSelection.AntTimerTick -= this.OnAntTimerTick;
            this.ssCurrent = SelectionState.SelectingRectangle;
            this.gpSelectedArea.Reset();
            this.ptP1 = pt;
            this.frmViewer.Invalidate();
        }
        public void Draw(Graphics g)
        {
            if (this.gpSelectedArea.PointCount > 0)
            {
                try
                {
                    GraphicsPath gp = this.gpSelectedArea.Clone() as GraphicsPath;
                    float fScaleX = (float)this.frmViewer.ClientSize.Width / this.frmViewer.ImageWidth;
                    float fScaleY = (float)this.frmViewer.ClientSize.Height / this.frmViewer.ImageHeight;
                    Matrix m = new Matrix();
                    m.Scale(fScaleX, fScaleY);
                    gp.Transform(m);
                    g.DrawPath(Pens.Black, gp);
                    Pen p = new Pen(Color.White, 1);
                    p.DashStyle = System.Drawing.Drawing2D.DashStyle.Dash;
                    p.DashPattern = new float[2] { 3, 3 };
                    p.DashOffset = AreaSelection.nAntOffset;
                    g.DrawPath(p, gp);
                }
                catch { }
            }
        }
        public void FinishSelection()
        {
            switch (this.ssCurrent)
            {
            case SelectionState.Idle:
            case SelectionState.BorderSelected:
            case SelectionState.RectangleSelected:
                return;
            case SelectionState.SelectingBorder:
                this.gpSelectedArea.CloseFigure();
                this.ssCurrent = SelectionState.BorderSelected;
                break;
            case SelectionState.SelectingRectangle:
                this.ssCurrent = SelectionState.RectangleSelected;
                break;
            }
            RectangleF bounds = this.gpSelectedArea.GetBounds();
            if ((bounds.Width == 0.0f) || (bounds.Height == 0.0f))
            {
                Reset();
            }
            if (this.ssCurrent != SelectionState.Idle)
            {
                AreaSelection.AntTimerTick += this.OnAntTimerTick;
                AreaSelection.AntTimer.Change(25, 25);
            }
            this.frmViewer.Invalidate();
        }
        private Rectangle NormalizedRectangle(Point p1, Point p2)
        {
            Rectangle rect = new Rectangle();
            // Normalize the rectangle.
            rect.X = Math.Min(p1.X, p2.X);
            rect.Y = Math.Min(p1.Y, p2.Y);
            rect.Width = Math.Abs(p2.X - p1.X);
            rect.Height = Math.Abs(p2.Y - p1.Y);
            if (rect.X < 0)
            {
                rect.Width += rect.X;
                rect.X = 0;
            }
            if (rect.Y < 0)
            {
                rect.Height += rect.Y;
                rect.Y = 0;
            }
            if (rect.Right > this.frmViewer.ImageWidth)
                rect.Width = this.frmViewer.ImageWidth - rect.X;
            if (rect.Bottom > this.frmViewer.ImageHeight)
                rect.Height = this.frmViewer.ImageHeight - rect.Y;
            return rect;
        }
        static private void OnAntTmer(object state)
        {
            if (AreaSelection.AntTimerTick != null)
            {
                AreaSelection.nAntOffset++;
                AreaSelection.nAntOffset %= 6;
                AreaSelection.AntTimerTick();
            }
            else
                AreaSelection.AntTimer.Change(Timeout.Infinite, Timeout.Infinite);
        }
        private void OnAntTimerTick()
        {
            this.frmViewer.Invalidate();
        }
        public void Reset()
        {
            AreaSelection.AntTimerTick -= this.OnAntTimerTick;
            this.ssCurrent = SelectionState.Idle;
            this.gpSelectedArea.Reset();
            this.ptP1 = CvipConstant.ptEmpty;
            this.frmViewer.Invalidate();
        }
        public void SelectRect(Rectangle rect)
        {
            if ((rect.Width <= 0) || (rect.Height <= 0))
            {
                Reset();
                return;
            }
            Point p2 = new Point(rect.Size);
            p2.Offset(rect.Location);
            rect = NormalizedRectangle(rect.Location, p2);
            this.gpSelectedArea.Reset();
            this.gpSelectedArea.AddRectangle(rect);
            this.ssCurrent = SelectionState.RectangleSelected;
            AreaSelection.AntTimerTick += this.OnAntTimerTick;
            AreaSelection.AntTimer.Change(25, 25);
            if (AreaSelection.BoundingRectangleChanged != null)
                AreaSelection.BoundingRectangleChanged(rect, this.frmViewer);
            this.frmViewer.Invalidate();
        }

        public int[] Area
        {
            get
            {
                int[] area = null;
                if (this.ssCurrent == SelectionState.BorderSelected)
                {
                    int numPoints = this.gpSelectedArea.PathPoints.Length;
                    int numXYVals = 2 * (numPoints + 1);
                    int x, y;

                    area = new int[numXYVals + 1];
                    area[0] = numXYVals;

                    for (int i = 0; i < numPoints; i++)
                    {
                        x = Math.Max(0, (int)this.gpSelectedArea.PathPoints[i].X);
                        x = Math.Min(x, this.frmViewer.ImageWidth - 1);
                        y = Math.Max(0, (int)this.gpSelectedArea.PathPoints[i].Y);
                        y = Math.Min(y, this.frmViewer.ImageHeight - 1);
                        area[(2 * i) + 1] = y;
                        area[(2 * i) + 2] = x;
                    }
                    area[numXYVals - 1] = area[1];
                    area[numXYVals] = area[2];
                }
                else if ((this.ssCurrent == SelectionState.RectangleSelected) ||
                    (this.ssCurrent == SelectionState.SelectingRectangle))
                {
                    area = new int[4];
                    area[0] = (int)gpSelectedArea.PathPoints[0].Y;
                    area[1] = (int)gpSelectedArea.PathPoints[0].X;
                    area[2] = (int)gpSelectedArea.PathPoints[2].Y - area[0];
                    area[3] = (int)gpSelectedArea.PathPoints[2].X - area[1];
                }
                return area;
            }
        }
        public Rectangle BoundingRectangle
        {
            get
            {
                Rectangle rect = Rectangle.Empty;
                if (this.ssCurrent != SelectionState.Idle)
                {
                    rect = Rectangle.Round(this.gpSelectedArea.GetBounds());
                    Point p2 = new Point(rect.Size);
                    p2.Offset(rect.Location);
                    rect = NormalizedRectangle(rect.Location, p2);
                }
                return rect;
            }
        }
        public SelectionState State
        {
            get { return this.ssCurrent; }
            set
            {
                if (value != SelectionState.Idle)
                    throw new ArgumentException("SelectionState can only be set to 'Idle' externally");
                Reset();
            }
        }
    }
}
