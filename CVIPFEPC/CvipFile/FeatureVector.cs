/*''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' ======================================================================
' Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
' ======================================================================
'
'             File Name: FeatureVector.cs
'           Description: Contains the code for
'                        for FeatureVector class
'         Related Files: FeatureHeader.cs
'   Initial Coding Date: January 2012
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
    public class FeatureVector
    {
        static public readonly Point ptEmpty = new Point(-1, -1);
        static public readonly Size szEmpty = new Size(-1, -1);

        private double fArea = double.NaN;
        private double fAspect = double.NaN;
        private double fEuler = double.NaN;
        private double fOrientation = double.NaN;
        private double fPerimeter = double.NaN;
        private double fThinness = double.NaN;
        private double[] fHist = null;
        private double[] fRst = null;
        private double[,] fLaw = null;
        private PointF ptCentroid = FeatureVector.ptEmpty;

        private Dictionary<string, double[]> fProjections = new Dictionary<string, double[]>();
        private Dictionary<string, double[]> fSpectral = new Dictionary<string, double[]>();
        private Dictionary<string, double[]> fTexture = new Dictionary<string, double[]>();

        private bool bFeatureSetExpanded = false;
        private string sClassName = null;
        private FeatureHeader hdrFeatures = null;

        public FeatureVector() { }
        public FeatureVector(FeatureHeader fh) { this.FeatureHeader = fh; }
        public FeatureVector(FeatureHeader fh, string classname)
            : this(fh)
        {
            this.ClassName = classname;
        }
        public void ClearTex()
        {


            this.fTexture.Clear();
        }
        public static FeatureVector FromArray(FeatureHeader fh, double[] fData)
        {
            int idx = 0;
            FeatureVector fv = new FeatureVector(fh);

            // Binary object features
            if (fh.UseArea) fv.Area = fData[idx++];
            if (fh.UseCentroid)
            {
                float y = (float)fData[idx++];
                float x = (float)fData[idx++];
                fv.Centroid = new PointF(x, y);
            }
            if (fh.UseOrientation) fv.Orientation = fData[idx++];
            if (fh.UsePerimeter) fv.Perimeter = fData[idx++];
            if (fh.UseEuler) fv.Euler = fData[idx++];
            if (fh.UseProjections)
            {
                int height = fh.ProjectionsHeight;
                int width = fh.ProjectionsWidth;
                double[] projections = fv.Projections = new double[height + width];
                for (int i = 0; i < (height + width); i++)
                    projections[i] = fData[idx++];
            }
            if (fh.UseThinness) fv.Thinness = fData[idx++];
            if (fh.UseAspectRatio) fv.AspectRatio = fData[idx++];

            // RST-Invariant Moment-Based features
            for (int i = 0; i < 7; i++)
            {
                if (fh.UseRst[i])
                {
                    double[] rst = fv.Rst = new double[7];
                    for (int j = 0; j < 7; j++)
                        rst[j] = fData[idx++];
                    break;
                }
            }

            // Histogram features
            for (int i = 0; i < 5; i++)
            {
                if (fh.UseHist[i])
                {
                    double[] hist = fv.Hist = new double[fh.Bands * 5];
                    for (int j = 0; j < (fh.Bands * 5); j++)
                        hist[j] = fData[idx++];
                    break;
                }
            }
            // Law Features
            for (int i = 0; i < 15; i++)
            {
                if (fh.UseLaw[i])
                {
                    double[,] law = fv.Law = new double[15, fh.Bands * 5];
                    for (int j = 0; j < 15; j++)
                    {
                        if (fh.UseLaw[j])
                        {
                            for (int k = 0; k < (fh.Bands * 5); k++)
                                law[j, k] = fData[idx++];
                        }

                    }
                    break;
                }
            }
            // Texture features
            for (int i = 0; i < 5; i++)
            {
                if (fh.UseTexture[i])
                {
                    double[] texture = fv.Texture = new double[10];
                    for (int j = 0; j < 10; j++)
                        texture[j] = fData[idx++];
                    break;
                }
            }
            
            // Spectral features
            if (fh.UseSpectral)
            {
                int rings = fh.SpectralRings;
                int sectors = fh.SpectralSectors;
                double[] spectral = fv.Spectral = new double[(1 + rings + sectors) * fh.Bands];
                for (int j = 0; j < ((1 + rings + sectors) * fh.Bands); j++)
                    spectral[j] = fData[idx++];
            }
            return fv;
        }
        public double[] ToArray()
        {
            double[] vals = null;
            if (this.FeatureHeader != null)
            {
                List<double> lstVals = new List<double>();
                // Binary object features
                if (this.FeatureHeader.UseArea) lstVals.Add(this.Area);
                if (this.FeatureHeader.UseCentroid)
                {
                    lstVals.Add(this.Centroid.Y);
                    lstVals.Add(this.Centroid.X);
                }
                if (this.FeatureHeader.UseOrientation) lstVals.Add(this.Orientation);
                if (this.FeatureHeader.UsePerimeter) lstVals.Add(this.Perimeter);
                if (this.FeatureHeader.UseEuler) lstVals.Add(this.Euler);
                if (this.FeatureHeader.UseProjections) lstVals.AddRange(this.Projections);
                if (this.FeatureHeader.UseThinness) lstVals.Add(this.Thinness);
                if (this.FeatureHeader.UseAspectRatio) lstVals.Add(this.AspectRatio);

                // RST-Invariant Moment-Based features
                for (int i = 0; i < 7; i++)
                {
                    if (this.FeatureHeader.UseRst[i])
                    {
                        lstVals.AddRange(this.Rst);
                        break;
                    }
                }

                // Histogram features
                for (int i = 0; i < 5; i++)
                {
                    if (this.FeatureHeader.UseHist[i])
                    {
                        lstVals.AddRange(this.Hist);
                        break;
                    }
                }

                // Law Features
                for (int i = 0; i < 15; i++)
                {
                    if (this.FeatureHeader.UseLaw[i])
                    { ////////change to accomodate 2d array
                        double[] row = new double[this.FeatureHeader.Bands * 5];
                        for (int j = 0; j < (this.FeatureHeader.Bands * 5); j++)
                        {
                            row[j] = this.Law[i, j];

                        }
                        lstVals.AddRange(row);

                    }

                }

                // Texture features
                for (int i = 0; i < 5; i++)
                {
                    if (this.FeatureHeader.UseTexture[i])
                    {
                        lstVals.AddRange(this.Texture);
                        break;
                    }
                }

                // Spectral features
                if (this.FeatureHeader.UseSpectral) lstVals.AddRange(this.Spectral);
                vals = lstVals.ToArray();
            }
            return vals;
        }
        public virtual void ResetValues()
        {
            // Binary object features
            this.fArea = double.NaN;
            this.fAspect = double.NaN;
            this.fEuler = double.NaN;
            this.fOrientation = double.NaN;
            this.fPerimeter = double.NaN;
            this.fProjections.Clear();
            this.fThinness = double.NaN;
            this.ptCentroid = FeatureVector.ptEmpty;

            // RST-Invariant Moment-Based features
            this.fRst = null;
            // Histogram features
            this.fHist = null;
            // Texture features
            this.fTexture.Clear();
            // Spectral features
            this.fSpectral.Clear();
        }

        public virtual string ClassName
        {
            get { return this.sClassName; }
            set { this.sClassName = value; }
        }
        public virtual FeatureHeader FeatureHeader
        {
            get { return this.hdrFeatures; }
            set { this.hdrFeatures = value; }
        }
        public bool FeatureSetExpanded
        {
            get { return this.bFeatureSetExpanded; }
            set { this.bFeatureSetExpanded = value; }
        }

        // Binary object features
        public virtual double Area
        {
            get
            {
                this.bFeatureSetExpanded = double.IsNaN(this.fArea);
                return this.fArea;
            }
            set { this.fArea = value; }
        }
        public virtual double AspectRatio
        {
            get
            {
                this.bFeatureSetExpanded = double.IsNaN(this.fAspect);
                return this.fAspect;
            }
            set { this.fAspect = value; }
        }
        public virtual PointF Centroid
        {
            get
            {
                this.bFeatureSetExpanded = (this.ptCentroid == FeatureVector.ptEmpty);
                return this.ptCentroid;
            }
            set { this.ptCentroid = value; }
        }
        public virtual double Euler
        {
            get
            {
                this.bFeatureSetExpanded = double.IsNaN(this.fEuler);
                return this.fEuler;
            }
            set { this.fEuler = value; }
        }
        public virtual double Orientation
        {
            get
            {
                this.bFeatureSetExpanded = double.IsNaN(this.fOrientation);
                return this.fOrientation;
            }
            set { this.fOrientation = value; }
        }
        public virtual double Perimeter
        {
            get
            {
                this.bFeatureSetExpanded = double.IsNaN(this.fPerimeter);
                return this.fPerimeter;
            }
            set { this.fPerimeter = value; }
        }
        public virtual double[] Projections
        {
            get
            {
                double[] projections = null;
                if (this.FeatureHeader != null)
                {
                    int height = this.FeatureHeader.ProjectionsHeight;
                    int width = this.FeatureHeader.ProjectionsWidth;
                    string idx = height + "x" + width;
                    this.fProjections.TryGetValue(idx, out projections);
                }
                this.bFeatureSetExpanded = (projections == null);
                return projections;
            }
            set
            {
                if (this.FeatureHeader == null)
                    throw new ArgumentNullException("FeatureVector.FeatureHeader == null", "FeatureVector.Projections.set");
                int height = this.FeatureHeader.ProjectionsHeight;
                int width = this.FeatureHeader.ProjectionsWidth;
                string idx = height + "x" + width;
                if (value != null)
                    this.fProjections[idx] = value;
                else
                    this.fProjections.Remove(idx);
            }
        }
        public virtual double Thinness
        {
            get
            {
                this.bFeatureSetExpanded = double.IsNaN(this.fThinness);
                return this.fThinness;
            }
            set { this.fThinness = value; }
        }
        // RST-Invariant Moment-Based features
        public virtual double[] Rst
        {
            get
            {
                this.bFeatureSetExpanded = (this.fRst == null);
                return this.fRst;
            }
            set { this.fRst = value; }
        }
        // Histogram features
        public virtual double[] Hist
        {
            get
            {
                this.bFeatureSetExpanded = (this.fHist == null);
                return this.fHist;
            }
            set { this.fHist = value; }
        }
        public double HistMean
        {
            get { return this.Hist[0]; }
            set { this.Hist[0] = value; }
        }
        public double HistStdDev
        {
            get { return this.Hist[1]; }
            set { this.Hist[1] = value; }
        }
        public double HistSkew
        {
            get { return this.Hist[2]; }
            set { this.Hist[2] = value; }
        }
        public double HistEnergy
        {
            get { return this.Hist[3]; }
            set { this.Hist[3] = value; }
        }
        public double HistEntropy
        {
            get { return this.Hist[4]; }
            set { this.Hist[4] = value; }
        }
        public virtual double[,] Law
        {
            get
            {
                this.bFeatureSetExpanded = (this.fLaw == null);
                return this.fLaw;
            }
            set { this.fLaw = value; }
        }
       
        // Texture features
        public virtual double[] Texture
        {
            get
            { 
                double[] texture = null;
                if (this.FeatureHeader != null)
                {
                    string idx;
                    if (FeatureHeader.UseCombTex)
                    {
                      //  int inc = FeatureHeader.TextureDistanceLower;
                        idx = this.FeatureHeader.TextureDistanceCalc.ToString();
                       // inc = inc + FeatureHeader.TextureDistanceIncrement;
                       // FeatureHeader.TextureDistanceLower = inc ;
                    }
                    else
                        idx = this.FeatureHeader.TextureDistance.ToString();
                    if (this.FeatureHeader.TextureUseTexture2)
                        idx += "t2";
                    this.fTexture.TryGetValue(idx, out texture);
                }
                this.bFeatureSetExpanded = (texture == null);
                return texture;
            }
            set
            {
                if (this.FeatureHeader == null)
                throw new ArgumentNullException("FeatureVector.FeatureHeader == null", "FeatureVector.Texture.set");
                string idx;
                if (FeatureHeader.UseCombTex)
                    idx = this.FeatureHeader.TextureDistanceCalc.ToString();
                else
                    idx = this.FeatureHeader.TextureDistance.ToString();
                if (this.FeatureHeader.TextureUseTexture2)
                    idx += "t2";
                if (value != null)
                    this.fTexture[idx] = value;
               else
                   this.fTexture.Remove(idx);
            }
        }
        // Spectral features
        public virtual double[] Spectral
        {
            get
            {
                double[] spectral = null;
                if (this.FeatureHeader != null)
                {
                    int rings = this.FeatureHeader.SpectralRings;
                    int sectors = this.FeatureHeader.SpectralSectors;
                    string idx = rings + "x" + sectors;
                    this.fSpectral.TryGetValue(idx, out spectral);
                }
                this.bFeatureSetExpanded = (spectral == null);
                return spectral;
            }
            set
            {
                if (this.FeatureHeader == null)
                    throw new ArgumentNullException("FeatureVector.FeatureHeader == null", "FeatureVector.Spectral.set");
                int rings = this.FeatureHeader.SpectralRings;
                int sectors = this.FeatureHeader.SpectralSectors;
                string idx = rings + "x" + sectors;
                if (value != null)
                    this.fSpectral[idx] = value;
                else
                    this.fSpectral.Remove(idx);
            }
        }
    }
}
