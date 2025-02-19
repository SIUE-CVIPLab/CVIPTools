/*''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' ======================================================================
' Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
' ======================================================================
'
'             File Name: CentroidObject.cs
'           Description: Contains the code for
'                        for CentroidObject class
'         Related Files: CvipObject.cs
'                        CentroidSet.cs
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
using System.IO;
using System.Text;

namespace CVIPFEPC.CvipFile
{
    public class CentroidObject : CvipObject
    {
        protected Dictionary<int, FeatureVector> lstVectorSet = null;
        protected FeatureVector[] fvLeave1OutVectors = null;

        public CentroidObject(CentroidSet ff, string classname)
            : base(ff, classname)
        {
            if (string.IsNullOrEmpty(this.ClassName))
                throw new ArgumentNullException("classname", "A CentroidObject must have a unique class name.");
        }
        public override void ResetValues()
        {
            base.ResetValues();
            this.fvLeave1OutVectors = null;
            this.lstVectorSet = null;
        }

        public override string Name
        {
            get { return new FileInfo(this.FeatureFile.FeatureFileSet.CentroidSetFile).Name; }
        }
        protected Dictionary<int, FeatureVector> VectorSet
        {
            get
            {
                Dictionary<int, FeatureVector> lstRetVal = null;
                if (this.FeatureFile.TrainingSet.Count > 0)
                {
                    if (this.lstVectorSet == null)
                    {
                        this.lstVectorSet = new Dictionary<int, FeatureVector>();
                        for (int i = 0; i < this.FeatureFile.TrainingSet.Count; i++)
                        {
                            FeatureVector fv = this.FeatureFile.TrainingSet[i];
                            if (fv.ClassName == this.ClassName)
                                this.lstVectorSet.Add(i, fv);
                        }
                    }
                    if (this.lstVectorSet.Count > 0)
                        lstRetVal = this.lstVectorSet;
                }
                return lstRetVal;
            }
        }
        public FeatureVector[] LeaveOneOutVectors
        {
            get
            {
                FeatureVector[] vectors = null;
                if (this.FeatureHeader != null)
                {
                    if ((this.fvLeave1OutVectors == null) && (this.VectorSet != null))
                    {
                        this.fvLeave1OutVectors = new FeatureVector[this.FeatureFile.TrainingSet.Count];
                        for (int i = 0; i < this.FeatureFile.TrainingSet.Count; i++)
                        {
                            int count = this.VectorSet.Count;
                            if (this.VectorSet.ContainsKey(i)) count--;
                            if (count < 1) continue;

                            FeatureVector[] fvTmp = new FeatureVector[count];
                            count = 0;
                            foreach (KeyValuePair<int, FeatureVector> kvp in this.VectorSet)
                            {
                                if (kvp.Key == i) continue;
                                fvTmp[count++] = kvp.Value;
                            }
                            this.fvLeave1OutVectors[i] = new CentroidVector(fvTmp, this.FeatureHeader, this.ClassName);
                        }
                    }
                    vectors = this.fvLeave1OutVectors;
                }
                return vectors;
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
                    foreach (FeatureVector fv in this.VectorSet.Values)
                        sum += fv.Area;
                    area = base.Area = sum / this.VectorSet.Count;
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
                    foreach (FeatureVector fv in this.VectorSet.Values)
                        sum += fv.AspectRatio;
                    aspect = base.AspectRatio = sum / this.VectorSet.Count;
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
                    foreach (FeatureVector fv in this.VectorSet.Values)
                    {
                        sumX += fv.Centroid.X;
                        sumY += fv.Centroid.Y;
                    }
                    sumX /= this.VectorSet.Count;
                    sumY /= this.VectorSet.Count;
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
                    foreach (FeatureVector fv in this.VectorSet.Values)
                        sum += fv.Euler;
                    euler = base.Euler = sum / this.VectorSet.Count;
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
                    foreach (FeatureVector fv in this.VectorSet.Values)
                        sum += fv.Orientation;
                    orientation = base.Orientation = sum / this.VectorSet.Count;
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
                    foreach (FeatureVector fv in this.VectorSet.Values)
                        sum += fv.Perimeter;
                    perimeter = base.Perimeter = sum / this.VectorSet.Count;
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
                    foreach (FeatureVector fv in this.VectorSet.Values)
                    {
                        for (int i = 0; i < (height + width); i++)
                            projections[i] += fv.Projections[i];
                    }
                    for (int i = 0; i < (height + width); i++)
                        projections[i] /= this.VectorSet.Count;
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
                    foreach (FeatureVector fv in this.VectorSet.Values)
                        sum += fv.Thinness;
                    thinness = base.Thinness = sum / this.VectorSet.Count;
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
                    foreach (FeatureVector fv in this.VectorSet.Values)
                    {
                        for (int i = 0; i < 7; i++)
                            rst[i] += fv.Rst[i];
                    }
                    for (int i = 0; i < 7; i++)
                        rst[i] /= this.VectorSet.Count;
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
                    foreach (FeatureVector fv in this.VectorSet.Values)
                    {
                        for (int i = 0; i < (this.FeatureHeader.Bands * 5); i++)
                            hist[i] += fv.Hist[i];
                    }
                    for (int i = 0; i < (this.FeatureHeader.Bands * 5); i++)
                        hist[i] /= this.VectorSet.Count;
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
                    foreach (FeatureVector fv in this.VectorSet.Values)
                    {
                        for (int i = 0; i < 10; i++)
                            texture[i] += fv.Texture[i];
                    }
                    for (int i = 0; i < 10; i++)
                        texture[i] /= this.VectorSet.Count;
                }
                return texture;
            }
            set { throw new NotSupportedException(); }
        }
        // Law Features
        public override double[,] Law
        {
            get
            {
                double[,] law = base.Law;
                if ((law == null) && (this.FeatureHeader != null) && (this.VectorSet != null))
                {
                    law = base.Law = new double[15, this.FeatureHeader.Bands * 5];
                    foreach (FeatureVector fv in this.VectorSet.Values)
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
                            law[i, j] /= this.VectorSet.Count;
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
                    foreach (FeatureVector fv in this.VectorSet.Values)
                    {
                        for (int i = 0; i < ((1 + rings + sectors) * this.FeatureHeader.Bands); i++)
                            spectral[i] += fv.Spectral[i];
                    }
                    for (int i = 0; i < ((1 + rings + sectors) * this.FeatureHeader.Bands); i++)
                        spectral[i] /= this.VectorSet.Count;
                }
                return spectral;
            }
            set { throw new NotSupportedException(); }
        }
    }
}
