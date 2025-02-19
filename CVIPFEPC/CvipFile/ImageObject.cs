/*''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' ======================================================================
' Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
' ======================================================================
'
'             File Name: ImageObject.cs
'           Description: Contains the code for
'                        for ImageObject class
'         Related Files: CvipObject.cs
'                        FeatureHeader.cs
'   Initial Coding Date: March 2012
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

using SERVERLib;
using System;
using System.Collections.Generic;
using System.Drawing;
using System.Drawing.Imaging;
using System.IO;
using System.Runtime.InteropServices;
using System.Text;

namespace CVIPFEPC.CvipFile
{
    public class ImageObject : CvipObject
    {
        [ThreadStatic]
        static private CVIPTools cvip;
        static private object lockCvip = new object();

        private int nBands = -1;
        private int pImage = 0;
        private int pMask = 0;
        private int pLabeled = 0;

        private object lockCvipImage = new object();
        private object lockCvipMask = new object();
        private object lockLabeledImage = new object();
        private object lockLocation = new object();
        private object lockSize = new object();

        private FileInfo fiImage = null;
        private Point ptLocation = FeatureVector.ptEmpty;
        private Size szSize = FeatureVector.szEmpty;

        public ImageObject(FileInfo fi) { this.fiImage = fi; }
        public ImageObject(FileInfo fi, string classname)
            : this(fi)
        {
            this.ClassName = classname;
        }
        private Bitmap CvipImageToBitmap(int img)
        {
            int height = CvipOp.GetNoOfRows_Image(ref img);
            int width = CvipOp.GetNoOfCols_Image(ref img);
            Bitmap bmp = new Bitmap(width, height);
            Graphics g = Graphics.FromImage(bmp);
            g.Clear(Color.Black);
            IntPtr hdc = g.GetHdc();
            int pDC = CvipOp.Render_DisplayImage(hdc.ToInt32(), ref img);
            CvipOp.Show_DisplayImage(hdc.ToInt32(), pDC, width, height, width, height);
            CvipOp.Delete_DisplayImage(pDC);
            g.ReleaseHdc(hdc);
            g.Dispose();
            return bmp;
        }

        public string FileName { get { return (this.fiImage != null) ? this.fiImage.FullName : null; } }
        public override string Name { get { return (this.fiImage != null) ? this.fiImage.Name : null; } }
        public override int Col { get { return this.Location.X; } }
        public override int Row { get { return this.Location.Y; } }
        public int Height { get { return this.Size.Height; } }
        public int Width { get { return this.Size.Width; } }
        public int Image { get { return (this.CvipImage == 0) ? 0 : CvipOp.Duplicate_Image(ref this.pImage); } }
        public int Mask { get { return (this.CvipMask == 0) ? 0 : CvipOp.Duplicate_Image(ref this.pMask); } }

        public int Bands
        {
            get
            {
                if ((this.nBands == -1) && (this.CvipImage != 0))
                    this.nBands = CvipOp.GetNoOfBands_Image(ref this.pImage);
                return this.nBands;
            }
        }
        public override FeatureFile FeatureFile
        {
            get { return base.FeatureFile; }
            set
            {
                base.FeatureFile = value;
                if (value != null)
                    this.FeatureHeader = value.FeatureHeader;
            }
        }
        public override FeatureHeader FeatureHeader
        {
            get { return base.FeatureHeader; }
            set
            {
                if (value != null)
                {
                    if (value.Bands == -1)
                        value.Bands = this.Bands;
                    if (value.Bands != this.Bands)
                        throw new ArgumentException("FeatureHeader.Bands != ImageObject.Bands", "ImageObject.FeatureHeader.set");
                }
            }
        }

        static private CVIPTools CvipOp
        {
            get
            {
                lock (ImageObject.lockCvip)
                {
                    if (ImageObject.cvip == null)
                        ImageObject.cvip = new CVIPTools();
                }
                return ImageObject.cvip;
            }
        }
        private int CvipImage
        {
            get
            {
                lock (this.lockCvipImage)
                {
                    if ((this.pImage == 0) && (this.fiImage != null))
                    {
                        string fname = this.fiImage.FullName;
                        this.pImage = CvipOp.Read_Image(ref fname);
                    }
                }
                return this.pImage;
            }
        }
        private int CvipMask
        {
            get
            {
                lock (this.lockCvipMask)
                {
                    if ((this.pMask == 0) && (this.fiImage != null))
                    {
                        DirectoryInfo di = new DirectoryInfo(this.fiImage.DirectoryName + @"\masks");
                        string fname = this.fiImage.Name.Replace(this.fiImage.Extension, "*");
                        fname = di.GetFiles(fname)[0].FullName;
                        this.pMask = CvipOp.Read_Image(ref fname);
                    }
                }
                return this.pMask;
            }
        }
        private int Labeled
        {
            get
            {
                lock (this.lockLabeledImage)
                {
                    if ((this.pLabeled == 0) && (this.CvipMask != 0))
                    {
                        this.pLabeled = CvipOp.Duplicate_Image(ref this.pMask);
                        if (CvipOp.GetNoOfBands_Image(ref this.pLabeled) != 1)
                            this.pLabeled = CvipOp.Luminance_Image(ref this.pLabeled);
                        this.pLabeled = CvipOp.Label(ref this.pLabeled);
                    }
                }
                return this.pLabeled;
            }
        }
        public Point Location
        {
            get
            {
                lock (this.lockLocation)
                {
                    if ((this.ptLocation == FeatureVector.ptEmpty) && (this.CvipMask != 0))
                    {
                        Bitmap bmp = CvipImageToBitmap(this.pMask);
                        if (bmp.PixelFormat != PixelFormat.Format32bppPArgb)
                        {
                            Bitmap temp = new Bitmap(bmp.Width, bmp.Height, PixelFormat.Format32bppPArgb);
                            Graphics g = Graphics.FromImage(temp);
                            g.DrawImage(bmp, new Rectangle(0, 0, bmp.Width, bmp.Height), 0, 0, bmp.Width, bmp.Height, GraphicsUnit.Pixel);
                            bmp.Dispose();
                            g.Dispose();
                            bmp = temp;
                        }
                        BitmapData bmd = bmp.LockBits(new Rectangle(0, 0, bmp.Width, bmp.Height), ImageLockMode.ReadOnly, bmp.PixelFormat);
                        for (int row = 0; row < bmp.Height; row++)
                        {
                            int index = row * bmd.Stride;
                            for (int col = 0; col < bmp.Width; col++, index += 4)
                            {
                                if (Marshal.ReadByte(bmd.Scan0, index + 2) != 0)
                                {
                                    this.ptLocation.X = col;
                                    this.ptLocation.Y = row;
                                    col = bmp.Width;
                                    row = bmp.Height;
                                    break;
                                }
                            }
                        }
                        bmp.UnlockBits(bmd);
                    }
                }
                return this.ptLocation;
            }
        }
        public Size Size
        {
            get
            {
                lock (this.lockSize)
                {
                    if ((this.szSize == FeatureVector.szEmpty) && (this.CvipImage != 0))
                    {
                        this.szSize.Height = CvipOp.GetNoOfRows_Image(ref this.pImage);
                        this.szSize.Width = CvipOp.GetNoOfCols_Image(ref this.pImage);
                    }
                }
                return this.szSize;
            }
        }

        // Binary object features
        public override double Area
        {
            get
            {
                double area = base.Area;
                if (double.IsNaN(area) && (this.Labeled != 0))
                    area = base.Area = CvipOp.Area(ref this.pLabeled, this.Row, this.Col);
                return area;
            }
            set { throw new NotSupportedException(); }
        }
        public override double AspectRatio
        {
            get
            {
                double aspect = base.AspectRatio;
                if (double.IsNaN(aspect) && (this.Labeled != 0))
                    aspect = base.AspectRatio = CvipOp.Aspect(ref this.pLabeled, this.Row, this.Col);
                return aspect;
            }
            set { throw new NotSupportedException(); }
        }
        public override PointF Centroid
        {
            get
            {
                PointF centroid = base.Centroid;
                if ((centroid == FeatureVector.ptEmpty) && (this.Labeled != 0))
                {
                    int[] val = (int[])CvipOp.CentroID(ref this.pLabeled, this.Row, this.Col);
                    centroid = base.Centroid = new PointF(val[1], val[0]);
                }
                return centroid;
            }
            set { throw new NotSupportedException(); }
        }
        public override double Euler
        {
            get
            {
                double euler = base.Euler;
                if (double.IsNaN(euler) && (this.Labeled != 0))
                    euler = base.Euler = CvipOp.Euler(ref this.pLabeled, this.Row, this.Col);
                return euler;
            }
            set { throw new NotSupportedException(); }
        }
        public override double Orientation
        {
            get
            {
                double orientation = base.Orientation;
                if (double.IsNaN(orientation) && (this.Labeled != 0))
                    orientation = base.Orientation = CvipOp.Orientation(ref this.pLabeled, this.Row, this.Col);
                return orientation;
            }
            set { throw new NotSupportedException(); }
        }
        public override double Perimeter
        {
            get
            {
                double perimeter = base.Perimeter;
                if (double.IsNaN(perimeter) && (this.Labeled != 0))
                    perimeter = base.Perimeter = CvipOp.Perimeter(ref this.pLabeled, this.Row, this.Col);
                return perimeter;
            }
            set { throw new NotSupportedException(); }
        }
        public override double[] Projections
        {
            get
            {
                double[] projections = base.Projections;
                if ((projections == null) && (this.FeatureHeader != null) && (this.Labeled != 0))
                {
                    int height = this.FeatureHeader.ProjectionsHeight;
                    int width = this.FeatureHeader.ProjectionsWidth;
                    int[] vals = (int[])CvipOp.Projection(ref this.pLabeled, this.Row, this.Col, height, width);
                    projections = base.Projections = Array.ConvertAll(vals, x => (double)x);
                }
                return projections;
            }
            set { throw new NotSupportedException(); }
        }
        public override double Thinness
        {
            get
            {
                double thinness = base.Thinness;
                if (double.IsNaN(thinness) && (this.Labeled != 0))
                    thinness = base.Thinness = CvipOp.Thinness(ref this.pLabeled, this.Row, this.Col);
                return thinness;
            }
            set { throw new NotSupportedException(); }
        }
        // RST-Invariant Moment-Based features
        public override double[] Rst
        {
            get
            {
                double[] rst = base.Rst;
                if ((rst == null) && (this.Labeled != 0))
                    rst = base.Rst = (double[])CvipOp.Rst_invariant(ref this.pLabeled, this.Row, this.Col);
                return rst;
            }
            set { throw new NotSupportedException(); }
        }

        //Law Texture
        public override double[,] Law
        {
            get
            {
                double[,] law = null;
                double[] lawTemp; //Using this to get the values from CvipOp function, then copying them into 2d Law array
                if ((law == null) && (this.CvipImage != 0) && (this.Labeled != 0))
                {
                    law = base.Law = new double[15, this.FeatureHeader.Bands * 5];
                    //  law = base.Law = (double[])CvipOp.Rst_invariant(ref this.pLabeled, this.Row, this.Col);
                    if (this.FeatureHeader.UseMask1)
                    {
                        lawTemp = (double[])CvipOp.Laws_Texture_Feature(ref this.pImage, ref this.pLabeled, this.Row, this.Col, 15, 0, 0);
                        for (int i = 0; i < this.FeatureHeader.Bands * 5; i++) law[0,i] = lawTemp[i];
                    }
                    if (this.FeatureHeader.UseMask2)
                    {
                        lawTemp = (double[])CvipOp.Laws_Texture_Feature(ref this.pImage, ref this.pLabeled, this.Row, this.Col, 15, 0, 1);
                        for (int i = 0; i < this.FeatureHeader.Bands * 5; i++) law[1,i] = lawTemp[i];
                    }
                        if (this.FeatureHeader.UseMask3)
                        {
                            lawTemp = (double[])CvipOp.Laws_Texture_Feature(ref this.pImage, ref this.pLabeled, this.Row, this.Col, 15, 0, 2);
                            for (int i = 0; i < this.FeatureHeader.Bands * 5; i++) law[2, i] = lawTemp[i];
                        }
                        if (this.FeatureHeader.UseMask4)
                        {
                            lawTemp = (double[])CvipOp.Laws_Texture_Feature(ref this.pImage, ref this.pLabeled, this.Row, this.Col, 15, 0, 3);
                            for (int i = 0; i < this.FeatureHeader.Bands * 5; i++) law[3,i] = lawTemp[i];
                        }
                        if (this.FeatureHeader.UseMask5)
                        {
                            lawTemp = (double[])CvipOp.Laws_Texture_Feature(ref this.pImage, ref this.pLabeled, this.Row, this.Col, 15, 0, 4);
                            for (int i = 0; i < this.FeatureHeader.Bands * 5; i++) law[4,i] = lawTemp[i];
                        }
                        if (this.FeatureHeader.UseMask6)
                        {
                            lawTemp = (double[])CvipOp.Laws_Texture_Feature(ref this.pImage, ref this.pLabeled, this.Row, this.Col, 15, 1, 1);
                            for (int i = 0; i < this.FeatureHeader.Bands * 5; i++) law[5,i] = lawTemp[i];
                        }
                        if (this.FeatureHeader.UseMask7)
                        {
                            lawTemp = (double[])CvipOp.Laws_Texture_Feature(ref this.pImage, ref this.pLabeled, this.Row, this.Col, 15, 1, 2);
                            for (int i = 0; i < this.FeatureHeader.Bands * 5; i++) law[6,i] = lawTemp[i];
                        }
                        if (this.FeatureHeader.UseMask8)
                        {
                            lawTemp = (double[])CvipOp.Laws_Texture_Feature(ref this.pImage, ref this.pLabeled, this.Row, this.Col, 15, 1, 3);
                            for (int i = 0; i < this.FeatureHeader.Bands * 5; i++) law[7,i] = lawTemp[i];
                        }
                        if (this.FeatureHeader.UseMask9)
                        {
                            lawTemp = (double[])CvipOp.Laws_Texture_Feature(ref this.pImage, ref this.pLabeled, this.Row, this.Col, 15, 1, 4);
                            for (int i = 0; i < this.FeatureHeader.Bands * 5; i++) law[8,i] = lawTemp[i];
                        }
                        if (this.FeatureHeader.UseMask10)
                        {
                            lawTemp = (double[])CvipOp.Laws_Texture_Feature(ref this.pImage, ref this.pLabeled, this.Row, this.Col, 15, 2, 2);
                            for (int i = 0; i < this.FeatureHeader.Bands * 5; i++) law[9,i] = lawTemp[i];
                        }
                        if (this.FeatureHeader.UseMask11)
                        {
                            lawTemp = (double[])CvipOp.Laws_Texture_Feature(ref this.pImage, ref this.pLabeled, this.Row, this.Col, 15, 2, 3);
                            for (int i = 0; i < this.FeatureHeader.Bands * 5; i++) law[10,i] = lawTemp[i];
                        }
                        if (this.FeatureHeader.UseMask12)
                        {
                            lawTemp = (double[])CvipOp.Laws_Texture_Feature(ref this.pImage, ref this.pLabeled, this.Row, this.Col, 15, 2, 4);
                            for (int i = 0; i < this.FeatureHeader.Bands * 5; i++) law[11,i] = lawTemp[i];
                        }
                        if (this.FeatureHeader.UseMask13)
                        {
                            lawTemp = (double[])CvipOp.Laws_Texture_Feature(ref this.pImage, ref this.pLabeled, this.Row, this.Col, 15, 3, 3);
                            for (int i = 0; i < this.FeatureHeader.Bands * 5; i++) law[12,i] = lawTemp[i];
                        }
                        if (this.FeatureHeader.UseMask14)
                        {
                            lawTemp = (double[])CvipOp.Laws_Texture_Feature(ref this.pImage, ref this.pLabeled, this.Row, this.Col, 15, 3, 4);
                            for (int i = 0; i < this.FeatureHeader.Bands * 5; i++) law[13,i] = lawTemp[i];
                        }
                        if (this.FeatureHeader.UseMask15)
                        {
                            lawTemp = (double[])CvipOp.Laws_Texture_Feature(ref this.pImage, ref this.pLabeled, this.Row, this.Col, 15, 4, 3);
                            for (int i = 0; i < this.FeatureHeader.Bands * 5; i++) law[14,i] = lawTemp[i];
                        }

                    }
         
                    return law;
                
            }
            set { throw new NotSupportedException(); }
        }
        //
        // Histogram features
        public override double[] Hist
        {
            get
            {
                double[] hist = base.Hist;
                if ((hist == null) && (this.CvipImage != 0) && (this.Labeled != 0))
                {
                    double[] vals = (double[])CvipOp.Hist_Feature(ref this.pImage, ref this.pLabeled, this.Row, this.Col);
                    hist = base.Hist = new double[vals.Length];
                    for (int i = 0; i < 5; i++)
                    {
                        for (int j = 0; j < this.Bands; j++)
                        {
                            if ((i == 2) && double.IsNaN(vals[(j * 5) + i]))
                                vals[(j * 5) + i] = 256.0;
                            hist[(i * this.Bands) + j] = vals[(j * 5) + i];
                        }
                    }
                }
                return hist;
            }
            set { throw new NotSupportedException(); }
        }
        // Texture features
        public override double[] Texture
        {
            get
            {
                double[] texture = base.Texture;
                if ((texture == null) && (this.FeatureHeader != null) &&
                    (this.CvipImage != 0) && (this.Labeled != 0))
                {
                    int img = CvipOp.Duplicate_Image(ref this.pImage);
                    if (this.Bands != 1)
                        img = CvipOp.Luminance_Image(ref img);
                    texture = base.Texture = new double[10];
                    if (this.FeatureHeader.TextureUseTexture2)
                    {



                        if (this.FeatureHeader.UseCombTex)
                        {
                            double[] vals = (double[])CvipOp.TextureFeature2(ref img, ref this.pLabeled, 0,
                                this.Row, this.Col, this.FeatureHeader.TextureDistanceCalc, 1, 1, 1, 1, 1, 0);
                            for (int i = 0; i < 5; i++)
                            {
                                texture[(i * 2) + 0] = vals[(i * 6) + 4];

                                texture[(i * 2) + 1] = vals[(i * 6) + 5];
                            }
                        }

                        else
                        {
                            double[] vals = (double[])CvipOp.TextureFeature2(ref img, ref this.pLabeled, 0,
                                   this.Row, this.Col, this.FeatureHeader.TextureDistance, 1, 1, 1, 1, 1, 0);
                            for (int i = 0; i < 5; i++)
                            {
                                texture[(i * 2) + 0] = vals[(i * 6) + 4];
                                texture[(i * 2) + 1] = vals[(i * 6) + 5];
                            }
                        }
                    }
                    else
                    {
                        if (this.FeatureHeader.UseCombTex)
                        {
                            for (int i = 0; i < 5; i++)
                            {
                                int hexmask = 1;
                                switch (i)
                                {
                                    case 0: hexmask = 1; break;
                                    case 1: hexmask = 2; break;
                                    case 2: hexmask = 4; break;
                                    case 3: hexmask = 16; break;
                                    case 4: hexmask = 256; break;
                                }
                                double[] vals = (double[])CvipOp.TextureFeature(ref img, ref this.pLabeled,
                                    this.Row, this.Col, this.FeatureHeader.TextureDistanceCalc, hexmask);
                                texture[(i * 2) + 0] = vals[0];
                                texture[(i * 2) + 1] = vals[1];
                            }
                        }
                        else
                        {
                            for (int i = 0; i < 5; i++)
                            {
                                int hexmask = 1;
                                switch (i)
                                {
                                    case 0: hexmask = 1; break;
                                    case 1: hexmask = 2; break;
                                    case 2: hexmask = 4; break;
                                    case 3: hexmask = 16; break;
                                    case 4: hexmask = 256; break;
                                }
                                double[] vals = (double[])CvipOp.TextureFeature(ref img, ref this.pLabeled,
                                    this.Row, this.Col, this.FeatureHeader.TextureDistance, hexmask);
                                texture[(i * 2) + 0] = vals[0];
                                texture[(i * 2) + 1] = vals[1];
                            }
                        }
                    }

                    CvipOp.Delete_Image(ref img);
                }
                return texture;
            }
            set { throw new NotSupportedException(); }
        }
        // Spectral features
        public override double[] Spectral
        {
            get
            {
                double[] spectral = base.Spectral;
                if ((spectral == null) && (this.FeatureHeader != null) &&
                    (this.CvipImage != 0) && (this.Labeled != 0))
                {
                    int rings = this.FeatureHeader.SpectralRings;
                    int sectors = this.FeatureHeader.SpectralSectors;
                    double[] vals = (double[])CvipOp.Spectral_Feature(ref this.pImage, ref this.pLabeled, rings, sectors, this.Row, this.Col);
                    spectral = base.Spectral = new double[(1 + rings + sectors) * this.Bands];
                    for (int i = 0; i < this.Bands; i++)
                    {
                        spectral[(1 + rings + sectors) * i] = vals[3 + ((1 + rings + sectors) * i)];
                        for (int j = 1; j <= rings; j++)
                            spectral[j + ((1 + rings + sectors) * i)] = vals[3 + j + ((1 + rings + sectors) * i)];
                        for (int j = 1; j <= sectors; j++)
                            spectral[rings + j + ((1 + rings + sectors) * i)] = vals[3 + rings + j + ((1 + rings + sectors) * i)];
                    }
                }
                return spectral;
            }
            set { throw new NotSupportedException(); }
        }
    }
}
