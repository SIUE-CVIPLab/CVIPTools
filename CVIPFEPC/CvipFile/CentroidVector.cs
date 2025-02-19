/*''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' ======================================================================
' Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
' ======================================================================
'
'             File Name: CentroidVector.cs
'           Description: Contains the code for
'                        for CentroidVector class
'         Related Files: FeatureVector.cs
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

using System;
using System.Collections.Generic;
using System.Drawing;
using System.Text;

namespace CVIPFEPC.CvipFile
{
    public class CentroidVector : FeatureVector
    {
        protected FeatureVector[] fvVectorSet = null;

        public CentroidVector(FeatureVector[] vectors, FeatureHeader fh, string classname)
            : base(fh, classname)
        {
            this.VectorSet = vectors;
        }

        public FeatureVector[] VectorSet
        {
            get { return this.fvVectorSet; }
            set
            {
                this.fvVectorSet = null;
                if ((value != null) && (value.Length > 0))
                    this.fvVectorSet = value;
                this.ResetValues();
            }
        }
        // Binary object features
        public override double Area
        {
            get
            {
                double area = base.Area;
                if (double.IsNaN(area) && (this.VectorSet != null))
                {
                    double sum = 0.0;
                    foreach (FeatureVector fv in this.VectorSet)
                        sum += fv.Area;
                    area = base.Area = sum / this.VectorSet.Length;
                }
                return area;
            }
            set { throw new NotSupportedException(); }
        }
        public override double AspectRatio
        {
            get
            {
                double aspect = base.AspectRatio;
                if (double.IsNaN(aspect) && (this.VectorSet != null))
                {
                    double sum = 0.0;
                    foreach (FeatureVector fv in this.VectorSet)
                        sum += fv.AspectRatio;
                    aspect = base.AspectRatio = sum / this.VectorSet.Length;
                }
                return aspect;
            }
            set { throw new NotSupportedException(); }
        }
        public override PointF Centroid
        {
            get
            {
                PointF centroid = base.Centroid;
                if ((centroid == FeatureVector.ptEmpty) && (this.VectorSet != null))
                {
                    double sumX = 0.0, sumY = 0.0;
                    foreach (FeatureVector fv in this.VectorSet)
                    {
                        sumX += fv.Centroid.X;
                        sumY += fv.Centroid.Y;
                    }
                    sumX /= this.VectorSet.Length;
                    sumY /= this.VectorSet.Length;
                    centroid = base.Centroid = new PointF((float)sumX, (float)sumY);
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
                if (double.IsNaN(euler) && (this.VectorSet != null))
                {
                    double sum = 0.0;
                    foreach (FeatureVector fv in this.VectorSet)
                        sum += fv.Euler;
                    euler = base.Euler = sum / this.VectorSet.Length;
                }
                return euler;
            }
            set { throw new NotSupportedException(); }
        }
        public override double Orientation
        {
            get
            {
                double orientation = base.Orientation;
                if (double.IsNaN(orientation) && (this.VectorSet != null))
                {
                    double sum = 0.0;
                    foreach (FeatureVector fv in this.VectorSet)
                        sum += fv.Orientation;
                    orientation = base.Orientation = sum / this.VectorSet.Length;
                }
                return orientation;
            }
            set { throw new NotSupportedException(); }
        }
        public override double Perimeter
        {
            get
            {
                double perimeter = base.Perimeter;
                if (double.IsNaN(perimeter) && (this.VectorSet != null))
                {
                    double sum = 0.0;
                    foreach (FeatureVector fv in this.VectorSet)
                        sum += fv.Perimeter;
                    perimeter = base.Perimeter = sum / this.VectorSet.Length;
                }
                return perimeter;
            }
            set { throw new NotSupportedException(); }
        }
        public override double[] Projections
        {
            get
            {
                double[] projections = base.Projections;
                if ((projections == null) && (this.FeatureHeader != null) && (this.VectorSet != null))
                {
                    int height = this.FeatureHeader.ProjectionsHeight;
                    int width = this.FeatureHeader.ProjectionsWidth;
                    projections = base.Projections = new double[height + width];
                    foreach (FeatureVector fv in this.VectorSet)
                    {
                        for (int i = 0; i < (height + width); i++)
                            projections[i] += fv.Projections[i];
                    }
                    for (int i = 0; i < (height + width); i++)
                        projections[i] /= this.VectorSet.Length;
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
                if (double.IsNaN(thinness) && (this.VectorSet != null))
                {
                    double sum = 0.0;
                    foreach (FeatureVector fv in this.VectorSet)
                        sum += fv.Thinness;
                    thinness = base.Thinness = sum / this.VectorSet.Length;
                }
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
                if ((rst == null) && (this.VectorSet != null))
                {
                    rst = base.Rst = new double[7];
                    foreach (FeatureVector fv in this.VectorSet)
                    {
                        for (int i = 0; i < 7; i++)
                            rst[i] += fv.Rst[i];
                    }
                    for (int i = 0; i < 7; i++)
                        rst[i] /= this.VectorSet.Length;
                }
                return rst;
            }
            set { throw new NotSupportedException(); }
        }
        // Histogram features
        public override double[] Hist
        {
            get
            {
                double[] hist = base.Hist;
                if ((hist == null) && (this.FeatureHeader != null) && (this.VectorSet != null))
                {
                    hist = base.Hist = new double[this.FeatureHeader.Bands * 5];
                    foreach (FeatureVector fv in this.VectorSet)
                    {
                        for (int i = 0; i < (this.FeatureHeader.Bands * 5); i++)
                            hist[i] += fv.Hist[i];
                    }
                    for (int i = 0; i < (this.FeatureHeader.Bands * 5); i++)
                        hist[i] /= this.VectorSet.Length;
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
                if ((texture == null) && (this.FeatureHeader != null) && (this.VectorSet != null))
                {
                    texture = base.Texture = new double[10];
                    foreach (FeatureVector fv in this.VectorSet)
                    {
                        for (int i = 0; i < 10; i++)
                            texture[i] += fv.Texture[i];
                    }
                    for (int i = 0; i < 10; i++)
                        texture[i] /= this.VectorSet.Length;
                }
                return texture;
            }
            set { throw new NotSupportedException(); }
        }
        public override double[,] Law
        {
            get
            {
                double[,] law = base.Law;
                if ((law == null) && (this.FeatureHeader != null) && (this.VectorSet != null))
                {
                    law = base.Law = new double[15, this.FeatureHeader.Bands * 5];
                    foreach (FeatureVector fv in this.VectorSet)
                    {
                        double[,] tempLaw = fv.Law;
                        for (int i = 0; i < 15; i++)
                        {
                            for (int j = 0; j < (this.FeatureHeader.Bands * 5); j++)
                            {
                                law[i, j] += tempLaw[i, j];
                                //law[i, j] += fv.Law[i, j];
                            }
                        }
                    }
                    for (int i = 0; i < 15; i++)
                    {
                        for (int j = 0; j < (this.FeatureHeader.Bands * 5); j++)
                        {
                            law[i, j] /= this.VectorSet.Length;
                        }
                    }
                }
                return law;
            }
            set { throw new NotSupportedException(); }
        }
        // Spectral features
        public override double[] Spectral
        {
            get
            {
                double[] spectral = base.Spectral;
                if ((spectral == null) && (this.FeatureHeader != null) && (this.VectorSet != null))
                {
                    int rings = this.FeatureHeader.SpectralRings;
                    int sectors = this.FeatureHeader.SpectralSectors;
                    spectral = base.Spectral = new double[(1 + rings + sectors) * this.FeatureHeader.Bands];
                    foreach (FeatureVector fv in this.VectorSet)
                    {
                        for (int i = 0; i < ((1 + rings + sectors) * this.FeatureHeader.Bands); i++)
                            spectral[i] += fv.Spectral[i];
                    }
                    for (int i = 0; i < ((1 + rings + sectors) * this.FeatureHeader.Bands); i++)
                        spectral[i] /= this.VectorSet.Length;
                }
                return spectral;
            }
            set { throw new NotSupportedException(); }
        }
    }
}
