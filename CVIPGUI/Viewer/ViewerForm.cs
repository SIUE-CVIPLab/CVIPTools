/*''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' ======================================================================
' Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
' ======================================================================
'
'             File Name: ViewerForm.cs
'           Description: Contains the controls and code
'                        for ViewerForm class
'         Related Files: ImageQueue.cs
'                        Win32Msgs.cs
'   Initial Coding Date: March 2007
'              Modified: February 2010
'       Delevoping tool: Visual Studio 2010-C#
'             Credit(s): Wenjun(Evan) Bian
'                        Patrick Solt
'                        Jhansi Lakshmi Akkineni
Hari Siva Kumar Reddy Bhogala
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

namespace CVIPGUI
{
    public delegate void MouseEvent(Point ptImage, ViewerForm viewer);
   
    public partial class ViewerForm : Form
    {
       
        private double fDataMin;
        private double fDataMax;
        private int nBands = -1;
        private int nHeight = -1;
        private int nWidth = -1;
        private int pDisplayImage = 0;
        private int pOriginalImage = 0;
        private int pMemoryDC = 0;
        private colorFormat enumColorFormat;
        private dataFormat enumDataFormat;
        private dataType enumDataType;
        private imageFormat enumImageFormat;
        private int nCompressionIndex = 0;
        private string strCompressedFileName = "";
        private AreaSelection areaSelection = null;
        private Mesh ptsMesh = null;
        private bool bShowMesh = false;

        static public event MouseEvent AltMouseClicked;
        static public event MouseEvent MouseClicked;
        static public event MouseEvent MouseMoved;
        static public event ViewerChanged FocusedViewerChanged;

        public ViewerForm(int img, string name)
        {
            InitializeComponent();

            if (img == 0)
                throw new ArgumentException(name + ": CVIPimage pointer not initialized.");

            this.Name = this.Text = name;
            this.pDisplayImage = CvipOp.Duplicate_Image(img);
            this.pOriginalImage = CvipOp.Duplicate_Image(img);
            CvipOp.Delete_Image(ref img);

            double[] info = CvipOp.GetImageInfo(this.pOriginalImage);
            this.enumColorFormat = (colorFormat)info[0];
            this.enumImageFormat = (imageFormat)info[1];
            this.enumDataFormat = (dataFormat)info[2];
            this.enumDataType = (dataType)info[3];
            this.nBands = (int)info[4];
            this.nHeight = (int)info[5];
            this.nWidth = (int)info[6];
            
            this.nCompressionIndex = 0;

            double[] range = CvipOp.Get_max_min_value(this.pOriginalImage);
            for (int i = 0; i < (this.Bands * 4); i += 4)
            {
                if (range[i] < range[0]) range[0] = range[i];
                if (range[i + 1] > range[1]) range[1] = range[i + 1];
                if (this.DataFormat == dataFormat.COMPLEX)
                {
                    if (range[i + 2] < range[0]) range[0] = range[i + 2];
                    if (range[i + 3] > range[1]) range[1] = range[i + 3];
                }
            }
            this.fDataMin = range[0];
            this.fDataMax = range[1];
        }
        public ViewerForm(int img, string name, LogRemap remap)
            : this(img, name)
        {
            img = this.pDisplayImage;
            this.pDisplayImage = CvipOp.Log_Remap(img, remap);
        }
        public ViewerForm(int img, string name, int compressionIndex, string compressedFileName)
            : this(img, name)
        {
            this.nCompressionIndex = compressionIndex;
            this.strCompressedFileName = compressedFileName;
        }
        public void ClearMesh()
        {
            if (this.Mesh != null)
                this.Mesh.Clear();
        }
        public void CreateMesh(int rows, int cols)
        {
            if (this.ptsMesh == null)
                this.ptsMesh = new Mesh(this);
            this.Mesh.CreateMesh(rows, cols);
        }
        public void CreateSineMesh(int rows, int cols)
        {
            if (this.ptsMesh == null)
                this.ptsMesh = new Mesh(this);
            this.Mesh.CreateSineMesh(rows, cols);
        }
        public void FlipImage(bool direction)
        {
            if (direction)
                this.pDisplayImage = CvipOp.Vertical_Flip(this.pDisplayImage);
            else
                this.pDisplayImage = CvipOp.Horizontal_Flip(this.pDisplayImage);
            this.RenderDisplayImage();
            this.Refresh();
        }
        public string[] GetRGBString(Point ptImage)
        {
            string[] rgb = null; 
            if ((ptImage.X >= 0) && (ptImage.X < this.ImageWidth) &&
                (ptImage.Y >= 0) && (ptImage.Y < this.ImageHeight))
            {
                double[] pixel = (double[])CvipOp.GetPixel_Image(this.pOriginalImage, ptImage.Y, ptImage.X);
                string format = "";
                if ((this.DataType == dataType.CVIP_DOUBLE) ||
                    (this.DataType == dataType.CVIP_FLOAT))
                {
                    format = "0.00000";
                }
                rgb = new string[3];
                rgb[0] = pixel[0].ToString(format);
                if (this.Bands == 1)
                {
                    rgb[1] = rgb[0];
                    rgb[2] = rgb[0];
                }
                else
                {
                    rgb[1] = pixel[1].ToString(format);
                    rgb[2] = pixel[2].ToString(format);
                }
            }
            return rgb;
        }
        public void HistEQImage()
        {
            this.pDisplayImage = CvipOp.Histogram_Equalization(this.pDisplayImage, 0);
            this.RenderDisplayImage();
            this.Refresh();
        }
        protected override void OnClosing(CancelEventArgs e)
        {
            if (this.areaSelection != null)
                this.areaSelection.Reset();

            if (this.ListItem != null)
                MainForm.Viewers.Remove(this);

            if (this.pMemoryDC != 0)
            {
                CvipOp.Delete_DisplayImage(this.pMemoryDC);
                this.pMemoryDC = 0;
            }
            if (this.pDisplayImage != 0)
                CvipOp.Delete_Image(ref this.pDisplayImage);

            if (this.pOriginalImage != 0)
                CvipOp.Delete_Image(ref this.pOriginalImage);

            base.OnClosing(e);
        }
        protected override void OnGotFocus(EventArgs e)
        {
            if (ViewerForm.FocusedViewerChanged != null)
                ViewerForm.FocusedViewerChanged(this);
            base.OnGotFocus(e);
        }
        protected override void OnKeyDown(KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Delete)
            {
                MainForm.Viewers.RemoveSelected();
                e.Handled = true;
            }
            else if (e.Control)
            {
                if (e.KeyCode == Keys.A)
                {
                    SelectRect(new Rectangle(0, 0, this.ImageWidth, this.ImageHeight));
                    e.Handled = true;
                }
                else if (e.KeyCode == Keys.C)
                {
                    if (this.SelectedArea != null)
                    {
                        int selection = this.SelectedImage;
                        Bitmap bmp = CvipOp.CvipToBitmap(selection);
                        CvipOp.Delete_Image(ref selection);
                        Clipboard.SetImage(bmp);
                        e.Handled = true;
                    }
                    else if (this.MeshComplete)
                    {
                        Clipboard.SetData("CVIPtoolsMesh", this.ptsMesh);
                        e.Handled = true;
                    }
                }
                else if (e.KeyCode == Keys.V)
                {
                    if (Clipboard.ContainsData("CVIPtoolsMesh"))
                    {
                        Mesh mesh = Clipboard.GetData("CVIPtoolsMesh") as Mesh;
                        this.ptsMesh = new Mesh(this, mesh);
                        this.Refresh();
                        e.Handled = true;
                    }
                }
            }
            base.OnKeyDown(e);
        }
        protected override void OnKeyPress(KeyPressEventArgs e)
        {
            MainForm.Viewers.OnKeyboardCommand(e);
            base.OnKeyPress(e);
        }
        protected override void OnKeyUp(KeyEventArgs e)
        {
            base.OnKeyUp(e);
            if ((ModifierKeys & Keys.Alt) != Keys.Alt)
                this.Cursor = Cursors.Default;
        }
        protected override void OnLoad(EventArgs e)
        {
            this.ClientSize = new Size(this.ImageWidth, this.ImageHeight);
            if (this.ImageHeight > 745)
            {
                this.ClientSize = new Size((int)(this.ImageWidth * (745 / (double)this.ImageHeight)), 745);
            }
            this.RenderDisplayImage();
            base.OnLoad(e);
        }
        protected override void OnMouseClick(MouseEventArgs e)
        {
            base.OnMouseClick(e);
            Point pt = ScalePointWindowToImage(e.Location);
            if ((ModifierKeys & Keys.Alt) == Keys.Alt)
            {
                if (ViewerForm.AltMouseClicked != null)
                    ViewerForm.AltMouseClicked(pt, this);
                if ((this.MeshPoints != null) && !this.MeshComplete)
                    this.Mesh.AddPoint(pt);
            }
            if (ViewerForm.MouseClicked != null)
                ViewerForm.MouseClicked(pt, this);

            
        }
        protected override void OnMouseDown(MouseEventArgs e)
        {
            base.OnMouseDown(e);
            Point pt = ScalePointWindowToImage(e.Location);
            if ((e.Button == MouseButtons.Middle) && (this.areaSelection != null))
                this.areaSelection.Reset();
            else if ((ModifierKeys & (Keys.Shift | Keys.Control)) != Keys.None)
            {
                if (this.areaSelection == null)
                    this.areaSelection = new AreaSelection(this);
                if ((ModifierKeys & Keys.Shift) == Keys.Shift)
                    this.areaSelection.BeginRectangle(pt);
                else if ((ModifierKeys & Keys.Control) == Keys.Control)
                    this.areaSelection.BeginBorder(pt);
            }
            else if (((ModifierKeys & Keys.Alt) == Keys.Alt) && this.MeshComplete)
            {
                Point ptHit = this.Mesh.HitTest(pt);
                if (ptHit != CvipConstant.ptEmpty)
                {
                    this.Mesh.SelectedPoint = ptHit;
                    this.Mesh.MouseDragging = true;
                }
            }
        }
        protected override void OnMouseLeave(EventArgs e)
        {
            base.OnMouseLeave(e);
            if (ViewerForm.MouseMoved != null)
                ViewerForm.MouseMoved(CvipConstant.ptEmpty, this);
        }
        protected override void OnMouseMove(MouseEventArgs e)
        {
            base.OnMouseMove(e);
            Point pt = ScalePointWindowToImage(e.Location);
            if ((this.SelectionState == SelectionState.SelectingBorder) ||
                (this.SelectionState == SelectionState.SelectingRectangle))
            {
                this.areaSelection.AddPoint(pt);
            }
            if (((ModifierKeys & Keys.Alt) == Keys.Alt) && this.MeshComplete)
            {
                if (this.Mesh.MouseDragging)
                    this.Mesh.SelectedValue = pt;
                if (this.Mesh.HitTest(pt) != CvipConstant.ptEmpty)
                    this.Cursor = Cursors.Cross;
                else
                    this.Cursor = Cursors.Default;
            }
            if (ViewerForm.MouseMoved != null)
                ViewerForm.MouseMoved(pt, this);
        }
        protected override void OnMouseUp(MouseEventArgs e)
        {
            base.OnMouseUp(e);
            if ((this.SelectionState == SelectionState.SelectingBorder) ||
                (this.SelectionState == SelectionState.SelectingRectangle))
            {
                this.areaSelection.FinishSelection();
            }
            if (this.Mesh != null)
                this.Mesh.MouseDragging = false;
        }
        protected override void OnPaint(PaintEventArgs e)
        {
            base.OnPaint(e);
            IntPtr hdc = e.Graphics.GetHdc();
            CvipOp.Show_DisplayImage(hdc.ToInt32(), pMemoryDC, this.ClientSize.Width, this.ClientSize.Height, this.ImageWidth, this.ImageHeight);
            e.Graphics.ReleaseHdc();
            if (this.areaSelection != null) this.areaSelection.Draw(e.Graphics);
            if (this.bShowMesh && (this.Mesh != null)) this.Mesh.Draw(e.Graphics);
        }
        public string OpenMesh()
        {
            if (this.ptsMesh == null)
                this.ptsMesh = new Mesh(this);
            return this.Mesh.OpenFile();
        }
        private void popmnuCopyMesh_Click(object sender, EventArgs e)
        {
            if (this.MeshComplete)
                Clipboard.SetData("CVIPtoolsMesh", this.ptsMesh);
        }
        private void popmnuPasteMesh_Click(object sender, EventArgs e)
        {
            if (Clipboard.ContainsData("CVIPtoolsMesh"))
            {
                Mesh mesh = Clipboard.GetData("CVIPtoolsMesh") as Mesh;
                this.ptsMesh = new Mesh(this, mesh);
                this.Refresh();
            }
        }
        private void popmnuShowMesh_Click(object sender, EventArgs e)
        {
            this.ShowMesh = this.popmnuShowMesh.Checked;
        }
        private void RenderDisplayImage()
        {
            if (this.pMemoryDC != 0)
            {
                CvipOp.Delete_DisplayImage(this.pMemoryDC);
                this.pMemoryDC = 0;
            }
            int img = this.pDisplayImage;
            this.pDisplayImage = CvipOp.CondRemap_Image(img, dataType.CVIP_BYTE, 0, 255);
            CvipOp.Delete_Image(ref img);
            Bitmap bmp = new Bitmap(this.ImageWidth, this.ImageHeight);
            Graphics g = Graphics.FromImage(bmp);
            g.Clear(Color.Black);
            IntPtr hdc = g.GetHdc();
            pMemoryDC = CvipOp.Render_DisplayImage(hdc.ToInt32(), this.pDisplayImage);
            g.ReleaseHdc(hdc);
            g.Dispose();
        }
        public void RestoreImage()
        {
            this.pDisplayImage = CvipOp.Duplicate_Image(this.pOriginalImage);
            this.nWidth = CvipOp.GetNoOfCols_Image(this.pDisplayImage);
            this.nHeight = CvipOp.GetNoOfRows_Image(this.pDisplayImage);
            this.RenderDisplayImage();
            this.Refresh();
        }
        public void RestoreResizeImage()
        {
            this.pDisplayImage = CvipOp.Duplicate_Image(this.pOriginalImage);
            this.nWidth = CvipOp.GetNoOfCols_Image(this.pDisplayImage);
            this.nHeight = CvipOp.GetNoOfRows_Image(this.pDisplayImage);
            this.ClientSize = new Size(this.ImageWidth, this.ImageHeight);
            this.RenderDisplayImage();
            this.Refresh();

            if (ViewerForm.FocusedViewerChanged != null)
                ViewerForm.FocusedViewerChanged(this);
        }
        public void RotateImage(bool direction)
        {
            float degrees = direction ? -90.0f : 90.0f;
            this.pDisplayImage = CvipOp.Rotate(this.pDisplayImage, degrees);
            this.nWidth = CvipOp.GetNoOfCols_Image(this.pDisplayImage);
            this.nHeight = CvipOp.GetNoOfRows_Image(this.pDisplayImage);
            this.ClientSize = new Size(this.ImageWidth, this.ImageHeight);
            this.RenderDisplayImage();
            this.Refresh();

            if (ViewerForm.FocusedViewerChanged != null)
                ViewerForm.FocusedViewerChanged(this);
        }
        public string SaveMesh()
        {
            if (!this.MeshComplete)
            {
                MessageBox.Show("There are no mesh points to save!", "No Mesh Points",
                    MessageBoxButtons.OK, MessageBoxIcon.Warning);
                return null;
            }
            return this.Mesh.SaveToFile();
        }
        Point ScalePointWindowToImage(Point ptWindow)
        {
           

            double scaleX = (double)this.ImageWidth / this.ClientSize.Width;
            double scaleY = (double)this.ImageHeight / this.ClientSize.Height;
            int X = (int)((double)ptWindow.X * scaleX);
            int Y = (int)((double)ptWindow.Y * scaleY);
            return new Point(X, Y);
        }
        public void SelectRect(Rectangle rect)
        {
            if (this.areaSelection == null)
                this.areaSelection = new AreaSelection(this);
            this.areaSelection.SelectRect(rect);
        }
        protected override void WndProc(ref Message m)
        {
            base.WndProc(ref m);
            
            if (m.Msg == (int)WM.MOUSEACTIVATE)
            {
                int hittest = (int)m.LParam & 0xffff;
                if ((hittest != (int)HT.CLOSE) && (this.ListItem != null))
                {
                    if (System.Windows.Forms.Control.ModifierKeys == Keys.Control)
                    {
                        if ((MainForm.Viewers.SelectedViewers.Count > 1) ||
                            !this.ListItem.Selected)
                        {
                            this.ListItem.Selected = !this.ListItem.Selected;
                        }
                    }
                    else
                        MainForm.Viewers.SelectedViewer = this;
                }
            }
        }
        static public event RectangleChanged BoundingRectangleChanged
        {
            add { AreaSelection.BoundingRectangleChanged += value; }
            remove { AreaSelection.BoundingRectangleChanged -= value; }
        }
        static public event ViewerChanged MeshChanged
        {
            add { Mesh.MeshChanged += value; }
            remove { Mesh.MeshChanged -= value; }
        }

        public int Bands { get { return this.nBands; } }
        public int CompressionIndex { get { return (this.nCompressionIndex); } }
        public int CVIPimage { get { return CvipOp.Duplicate_Image(this.pOriginalImage); } }
        public int ImageHeight { get { return (this.nHeight); } }
        public int ImageWidth { get { return (this.nWidth); } }

        public double DataMax { get { return this.fDataMax; } }
        public double DataMin { get { return this.fDataMin; } }

        public colorFormat ColorFormat { get { return this.enumColorFormat; } }
        public dataFormat DataFormat { get { return this.enumDataFormat; } }
        public dataType DataType { get { return this.enumDataType; } }
        public imageFormat ImageFormat { get { return this.enumImageFormat; } }
        public string CompressedFileName { get { return (this.strCompressedFileName); } }

        public Rectangle BoundingRectangle
        {
            get
            {
                Rectangle rect = Rectangle.Empty;
                if (this.areaSelection != null)
                    rect = this.areaSelection.BoundingRectangle;
                return rect;
            }
        }
        public ImageQueueListItem ListItem
        {
            get { return (ImageQueueListItem)this.Tag; }
            set
            {
                if ((this.ListItem != value) && ((this.Tag = value) != null))
                    this.ListItem.Viewer = this;
            }
        }
        public Mesh Mesh
        {
            get { return this.ptsMesh; }
            set
            {
                this.ptsMesh = null;
                if (value != null)
                    this.ptsMesh = new Mesh(this, value);
                this.Refresh();
            }
        }
        public bool MeshComplete
        {
            get
            {
                bool complete = false;
                if (this.Mesh != null)
                    complete = this.Mesh.Complete;
                return complete;
            }
        }
        public Point[,] MeshPoints
        {
            get
            {
                Point[,] points = null;
                if (this.Mesh != null)
                    points = this.Mesh.Points;
                return points;
            }
        }
        public int MeshPointsCompleted
        {
            get
            {
                int completed = -1;
                if (this.Mesh != null)
                    completed = this.Mesh.PointsCompleted;
                return completed;
            }
        }
        public int MeshSelectedIndex
        {
            get
            {
                int idx = -1;
                if (this.Mesh != null)
                    idx = this.Mesh.SelectedIndex;
                return idx;
            }
            set
            {
                if (this.Mesh != null)
                    this.Mesh.SelectedIndex = value;
            }
        }
        public Point MeshSelectedValue
        {
            get
            {
                Point val = CvipConstant.ptEmpty;
                if (this.Mesh != null)
                    val = this.Mesh.SelectedValue;
                return val;
            }
            set
            {
                if (this.Mesh != null)
                    this.Mesh.SelectedValue = value;
            }
        }
        public string MeshStatus
        {
            get
            {
                string status = "";
                if (this.Mesh != null)
                    status = this.Mesh.Status;
                return status;
            }
        }
        public int[] SelectedArea
        {
            get
            {
                int[] area = null;
                if (this.areaSelection != null)
                    area = this.areaSelection.Area;
                return area;
            }
        }
        public int SelectedImage
        {
            get
            {
                int copy = 0;
                int[] selectedArea = this.SelectedArea;
                if (selectedArea != null)
                {
                    if (this.areaSelection.State == SelectionState.BorderSelected)
                        copy = CvipOp.Object_Crop(this.CVIPimage, selectedArea, 1, 0, 0, 0);
                    else
                        copy = CvipOp.Crop(this.CVIPimage, selectedArea[0], selectedArea[1], selectedArea[2], selectedArea[3]);
                }
                return copy;
            }
        }
        public SelectionState SelectionState
        {
            get
            {
                SelectionState ss = SelectionState.Idle;
                if (this.areaSelection != null)
                    ss = this.areaSelection.State;
                return ss;
            }
            set
            {
                if (value != SelectionState.Idle)
                    throw new ArgumentException("SelectionState can only be set to 'Idle' externally");
                if (this.areaSelection != null)
                    this.areaSelection.Reset();
            }
        }
        public bool ShowMesh
        {
            get { return this.bShowMesh; }
            set
            {
                this.bShowMesh = value;
                if (this.popmnuShowMesh.Checked != this.bShowMesh)
                    this.popmnuShowMesh.Checked = this.bShowMesh;
                this.Refresh();
            }
        }

       
    }
}
