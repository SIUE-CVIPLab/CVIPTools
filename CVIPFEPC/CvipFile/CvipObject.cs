/*''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' ======================================================================
' Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
' ======================================================================
'
'             File Name: CvipObject.cs
'           Description: Contains the code for
'                        for CvipObject class
'         Related Files: FeatureVector.cs
'                        FeatureFile.cs
'                        FeatureHeader.cs
'   Initial Coding Date: November 2006
'              Modified: March 2012
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
    public abstract class CvipObject : FeatureVector
    {
        protected FeatureFile ffFeatureFile = null;
        protected FeatureVector fvFeatures = null;

        protected CvipObject() { }
        protected CvipObject(FeatureFile ff) { this.FeatureFile = ff; }
        protected CvipObject(FeatureFile ff, string classname)
            : this(ff)
        {
            this.ClassName = classname;
        }
        public override void ResetValues()
        {
            base.ResetValues();
            if (this.fvFeatures != null) this.fvFeatures.ResetValues();
        }
        public string ToString(FeatureVector fv)
        {
            if (this.FeatureHeader == null)
                return "CvipObject.ToString: FeatureHeader not set.";

            string format = (this.FeatureFile.Normalization != Normalization.None) ? "0.000000" : null;
            StringBuilder bldr = new StringBuilder();

            string tempName = this.Name.Replace(" ", "_");
            bldr.Append(tempName + " " + this.Row + " " + this.Col);
            //bldr.Append(this.Name + " " + this.Row + " " + this.Col);

            // Binary object features
            if (this.FeatureHeader.UseArea) bldr.Append(" " + fv.Area.ToString(format));
            if (this.FeatureHeader.UseCentroid) bldr.Append(" " + fv.Centroid.Y.ToString(format) + " " + fv.Centroid.X.ToString(format));
            if (this.FeatureHeader.UseOrientation) bldr.Append(" " + fv.Orientation.ToString(format));
            if (this.FeatureHeader.UsePerimeter) bldr.Append(" " + fv.Perimeter.ToString(format));
            if (this.FeatureHeader.UseEuler) bldr.Append(" " + fv.Euler.ToString(format));
            if (this.FeatureHeader.UseProjections)
            {
                for (int i = 0; i < fv.Projections.Length; i++)
                    bldr.Append(" " + fv.Projections[i].ToString(format));
            }
            if (this.FeatureHeader.UseThinness) bldr.Append(" " + fv.Thinness.ToString("0.000000"));
            if (this.FeatureHeader.UseAspectRatio) bldr.Append(" " + fv.AspectRatio.ToString("0.000000"));

            // RST-Invariant Moment-Based features
            for (int i = 0; i < 7; i++)
            {
                if (this.FeatureHeader.UseRst[i])
                    bldr.Append(" " + fv.Rst[i].ToString("0.000000"));
            }
            // Histogram features
            for (int i = 0; i < 5; i++)
            {
                if (this.FeatureHeader.UseHist[i])
                {
                    for (int j = 0; j < this.FeatureHeader.Bands; j++)
                        bldr.Append(" " + fv.Hist[(i * this.FeatureHeader.Bands) + j].ToString("0.000000"));
                }
            }

            //Law features
            for (int i = 0; i < 15; i++)
            {
                if (this.FeatureHeader.UseLaw[i])
                {
                    double[,] tempLaw = fv.Law;
                    for (int j = 0; j < 15; j++)
                    {
                        if (this.FeatureHeader.UseLaw[j])
                            for (int k = 0; k < (this.FeatureHeader.Bands * 5); k++)
                                bldr.Append(" " + tempLaw[j, k].ToString("0.000000"));
                                //bldr.Append(" " + fv.Law[i,k].ToString("0.000000"));               
                    }
                    break;
                }
            }

            // Texture features
            for (int i = 0; i < 5; i++)
            {
                if (this.FeatureHeader.UseTexture[i])
                {
                    bldr.Append(" " + fv.Texture[(i * 2) + 0].ToString("0.000000"));
                    bldr.Append(" " + fv.Texture[(i * 2) + 1].ToString("0.000000"));
                }
            }
            
            // Spectral features
            if (this.FeatureHeader.UseSpectral)
            {
                int rings = this.FeatureHeader.SpectralRings;
                int sectors = this.FeatureHeader.SpectralSectors;
                for (int i = 0; i < this.FeatureHeader.Bands; i++)
                {
                    bldr.Append(" " + fv.Spectral[(1 + rings + sectors) * i].ToString("0.000000"));
                    for (int j = 1; j <= rings; j++)
                        bldr.Append(" " + fv.Spectral[j + ((1 + rings + sectors) * i)].ToString("0.000000"));
                    for (int j = 1; j <= sectors; j++)
                        bldr.Append(" " + fv.Spectral[rings + j + ((1 + rings + sectors) * i)].ToString("0.000000"));
                }
            }
            // Class Name
            bldr.Append(" " + this.ClassName);
            return bldr.ToString();
        }

        public virtual int Col { get { return 0; } }
        public virtual int Row { get { return 0; } }
        public abstract string Name { get; }

        public override string ClassName
        {
            get { return base.ClassName; }
            set
            {
                base.ClassName = value;
                if (this.FeatureFile != null)
                    this.FeatureFile.ClearVectorCache();
            }
        }
        public virtual FeatureFile FeatureFile
        {
            get { return this.ffFeatureFile; }
            set { this.ffFeatureFile = value; }
        }
        public override FeatureHeader FeatureHeader
        {
            get { return (this.FeatureFile != null) ? this.FeatureFile.FeatureHeader : null; }
            set { throw new NotSupportedException(); }
        }
        public FeatureVector FeatureVector
        {
            get
            {
                FeatureVector fv = null;
                if (this.FeatureHeader != null)
                {
                    if (this.fvFeatures == null)
                        this.fvFeatures = new FeatureVector(this.FeatureHeader, this.ClassName);
                    fv = this.fvFeatures;
                    fv.FeatureSetExpanded = false;

                    // Binary object features
                    if (this.FeatureHeader.UseArea) fv.Area = this.Area;
                    if (this.FeatureHeader.UseCentroid) fv.Centroid = this.Centroid;
                    if (this.FeatureHeader.UseOrientation) fv.Orientation = this.Orientation;
                    if (this.FeatureHeader.UsePerimeter) fv.Perimeter = this.Perimeter;
                    if (this.FeatureHeader.UseEuler) fv.Euler = this.Euler;
                    if (this.FeatureHeader.UseProjections) fv.Projections = this.Projections;
                    if (this.FeatureHeader.UseThinness) fv.Thinness = this.Thinness;
                    if (this.FeatureHeader.UseAspectRatio) fv.AspectRatio = this.AspectRatio;

                    // RST-Invariant Moment-Based features
                    for (int i = 0; i < 7; i++)
                    {
                        if (this.FeatureHeader.UseRst[i])
                        {
                            fv.Rst = this.Rst;
                            break;
                        }
                    }
                    // Histogram features
                    for (int i = 0; i < 5; i++)
                    {
                        if (this.FeatureHeader.UseHist[i])
                        {
                            fv.Hist = this.Hist;
                            break;
                        }
                    }
                    // Texture features
                    for (int i = 0; i < 5; i++)
                    {
                        if (this.FeatureHeader.UseTexture[i])
                        {
                            fv.Texture = this.Texture;
                            break;
                        }
                    }
                    for (int i = 0; i < 15; i++)
                    {
                        if (this.FeatureHeader.UseLaw[i])
                        {

                            fv.Law = this.Law;
                            break;
                        }

                    }
                    // Spectral features
                    if (this.FeatureHeader.UseSpectral) fv.Spectral = this.Spectral;

                    if (fv.FeatureSetExpanded)
                        this.FeatureFile.ClearVectorCache();
                }
                return fv;
            }
        }
    }
}
