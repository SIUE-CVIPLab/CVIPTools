/*''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' ======================================================================
' Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
' ======================================================================
'
'             File Name: FeatureHeader.cs
'           Description: Contains the code for
'                        FeatureHeader class
'         Related Files: FeatureChooser.cs
'                        CvipObject.cs
'                        FeatureFile.cs
'   Initial Coding Date: November 2006
'              Modified: December 2011
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
using System.Text;
using System.Xml.Serialization;

namespace CVIPFEPC.CvipFile
{
    public class FeatureHeader : FeatureChooser
    {
        private bool m_bTexUseTexture2 = true;
        private bool m_bTexUseZeroPairs = false;
        private bool m_bUseArea = false;
        private bool m_bUseAspect = false;
        private bool m_bUseCentroid = false;
        private bool m_bUseEuler = false;
        private bool m_bUseOrientation = false;
        private bool m_bUsePerimeter = false;
        private bool m_bUseProjections = false;
        private bool m_bUseSpectral = false;
        private bool m_bUseThinness = false;
        int inc = 0;

        private bool[] m_bUseHist = { true, false, false, false, false };
        private bool[] m_bUseRst = new bool[7];
        private bool[] m_bUseLaw = new bool[15];
        private bool[] m_bUseTexture = new bool[6];
      
        

        private int m_nBands = -1;
        private int m_nProjHeight = 10;
        private int m_nProjWidth = 10;
        private int m_nSpecRings = 3;
        private int m_nSpecSectors = 3;
        private int m_nTexDistance = 2;
        private int m_nTexDistancecalc ;
        private int m_nTexDistanceLower = 2;
        private int m_nTexDistanceIncrement = 1;
        private int m_nTexDistanceUpper = 6;
    
        private List<int> m_texDistance = new List<int>();

        public FeatureHeader() { }
        public FeatureHeader(FeatureHeader fh)
            : base((FeatureChooser)fh)
        {
            this.m_bTexUseTexture2 = fh.m_bTexUseTexture2;
            this.m_bTexUseZeroPairs = fh.m_bTexUseZeroPairs;
            this.m_bUseArea = fh.m_bUseArea;
            this.m_bUseAspect = fh.m_bUseAspect;
            this.m_bUseCentroid = fh.m_bUseCentroid;
            this.m_bUseEuler = fh.m_bUseEuler;
            this.m_bUseOrientation = fh.m_bUseOrientation;
            this.m_bUsePerimeter = fh.m_bUsePerimeter;
            this.m_bUseProjections = fh.m_bUseProjections;
            this.m_bUseSpectral = fh.m_bUseSpectral;
            this.m_bUseThinness = fh.m_bUseThinness;
          
            this.m_bUseHist[0] = fh.m_bUseHist[0];
            this.m_bUseHist[1] = fh.m_bUseHist[1];
            this.m_bUseHist[2] = fh.m_bUseHist[2];
            this.m_bUseHist[3] = fh.m_bUseHist[3];
            this.m_bUseHist[4] = fh.m_bUseHist[4];
            this.m_bUseRst[0] = fh.m_bUseRst[0];
            this.m_bUseRst[1] = fh.m_bUseRst[1];
            this.m_bUseRst[2] = fh.m_bUseRst[2];
            this.m_bUseRst[3] = fh.m_bUseRst[3];
            this.m_bUseRst[4] = fh.m_bUseRst[4];
            this.m_bUseRst[5] = fh.m_bUseRst[5];
            this.m_bUseRst[6] = fh.m_bUseRst[6];
            this.m_bUseLaw[0] = fh.m_bUseLaw[0];
            this.m_bUseLaw[1] = fh.m_bUseLaw[1];
            this.m_bUseLaw[2] = fh.m_bUseLaw[2];
            this.m_bUseLaw[3] = fh.m_bUseLaw[3];
            this.m_bUseLaw[4] = fh.m_bUseLaw[4];
            this.m_bUseLaw[5] = fh.m_bUseLaw[5];
            this.m_bUseLaw[6] = fh.m_bUseLaw[6];
            this.m_bUseLaw[7] = fh.m_bUseLaw[7];
            this.m_bUseLaw[8] = fh.m_bUseLaw[8];
            this.m_bUseLaw[9] = fh.m_bUseLaw[9];
            this.m_bUseLaw[10] = fh.m_bUseLaw[10];
            this.m_bUseLaw[11] = fh.m_bUseLaw[11];
            this.m_bUseLaw[12] = fh.m_bUseLaw[12];
            this.m_bUseLaw[13] = fh.m_bUseLaw[13];
            this.m_bUseLaw[14] = fh.m_bUseLaw[14];
            this.m_bUseTexture[0] = fh.m_bUseTexture[0];
            this.m_bUseTexture[1] = fh.m_bUseTexture[1];
            this.m_bUseTexture[2] = fh.m_bUseTexture[2];
            this.m_bUseTexture[3] = fh.m_bUseTexture[3];
            this.m_bUseTexture[4] = fh.m_bUseTexture[4];
            this.m_bUseTexture[5] = fh.m_bUseTexture[5];
            this.m_texDistance.Add(fh.m_nTexDistanceLower);
            this.m_texDistance.Add(fh.m_nTexDistanceLower + fh.m_nTexDistanceIncrement);
           

            this.m_nBands = fh.m_nBands;
            this.m_nProjHeight = fh.m_nProjHeight;
            this.m_nProjWidth = fh.m_nProjWidth;
            this.m_nSpecRings = fh.m_nSpecRings;
            this.m_nSpecSectors = fh.m_nSpecSectors;
            this.m_nTexDistance = fh.m_nTexDistance;
            this.m_nTexDistanceLower = fh.m_nTexDistanceLower;
            this.m_nTexDistanceIncrement = fh.m_nTexDistanceIncrement;
            this.m_nTexDistanceUpper = fh.m_nTexDistanceUpper;
        }
        public override void Append(FeatureChooser fc)
        {
            if (fc != null)
            {
                base.Append(fc);
                fc.FeatureHeader = this;
            }
        }
        public override bool Equals(object obj)
        {
            return (Equals(obj as FeatureHeader));
        }
        public bool Equals(FeatureHeader fh)
        {
            return base.Equals(fh) &&
                ((this.m_nBands == -1) || (fh.m_nBands == -1) || (this.m_nBands == fh.m_nBands)) &&
                (this.m_bTexUseTexture2 == fh.m_bTexUseTexture2) &&
                (this.m_bTexUseZeroPairs == fh.m_bTexUseZeroPairs) &&
                (this.m_bUseArea == fh.m_bUseArea) &&
                (this.m_bUseAspect == fh.m_bUseAspect) &&
                (this.m_bUseCentroid == fh.m_bUseCentroid) &&
                (this.m_bUseEuler == fh.m_bUseEuler) &&
                (this.m_bUseOrientation == fh.m_bUseOrientation) &&
                (this.m_bUsePerimeter == fh.m_bUsePerimeter) &&
                (this.m_bUseProjections == fh.m_bUseProjections) &&
                (this.m_bUseSpectral == fh.m_bUseSpectral) &&
                (this.m_bUseThinness == fh.m_bUseThinness) &&
                (this.m_bUseHist[0] == fh.m_bUseHist[0]) &&
                (this.m_bUseHist[1] == fh.m_bUseHist[1]) &&
                (this.m_bUseHist[2] == fh.m_bUseHist[2]) &&
                (this.m_bUseHist[3] == fh.m_bUseHist[3]) &&
                (this.m_bUseHist[4] == fh.m_bUseHist[4]) &&
                (this.m_bUseRst[0] == fh.m_bUseRst[0]) &&
                (this.m_bUseRst[1] == fh.m_bUseRst[1]) &&
                (this.m_bUseRst[2] == fh.m_bUseRst[2]) &&
                (this.m_bUseRst[3] == fh.m_bUseRst[3]) &&
                (this.m_bUseRst[4] == fh.m_bUseRst[4]) &&
                (this.m_bUseRst[5] == fh.m_bUseRst[5]) &&
                (this.m_bUseRst[6] == fh.m_bUseRst[6]) &&
                 (this.m_bUseLaw[0] == fh.m_bUseLaw[0]) &&
                (this.m_bUseLaw[1] == fh.m_bUseLaw[1]) &&
                (this.m_bUseLaw[2] == fh.m_bUseLaw[2]) &&
                (this.m_bUseLaw[3] == fh.m_bUseLaw[3]) &&
                (this.m_bUseLaw[4] == fh.m_bUseLaw[4]) &&
                (this.m_bUseLaw[5] == fh.m_bUseLaw[5]) &&
                (this.m_bUseLaw[6] == fh.m_bUseLaw[6]) &&
                 (this.m_bUseLaw[7] == fh.m_bUseLaw[7]) &&
                (this.m_bUseLaw[8] == fh.m_bUseLaw[8]) &&
                (this.m_bUseLaw[9] == fh.m_bUseLaw[9]) &&
                (this.m_bUseLaw[10] == fh.m_bUseLaw[10]) &&
                (this.m_bUseLaw[11] == fh.m_bUseLaw[11]) &&
                (this.m_bUseLaw[12] == fh.m_bUseLaw[12]) &&
                (this.m_bUseLaw[13] == fh.m_bUseLaw[13]) &&
                 (this.m_bUseLaw[14] == fh.m_bUseLaw[14]) &&
                (this.m_bUseTexture[0] == fh.m_bUseTexture[0]) &&
                (this.m_bUseTexture[1] == fh.m_bUseTexture[1]) &&
                (this.m_bUseTexture[2] == fh.m_bUseTexture[2]) &&
                (this.m_bUseTexture[3] == fh.m_bUseTexture[3]) &&
                (this.m_bUseTexture[4] == fh.m_bUseTexture[4]) &&
                (this.m_bUseTexture[5] == fh.m_bUseTexture[5]) &&
                (this.m_nProjHeight == fh.m_nProjHeight) &&
                (this.m_nProjWidth == fh.m_nProjWidth) &&
                (this.m_nSpecRings == fh.m_nSpecRings) &&
                (this.m_nSpecSectors == fh.m_nSpecSectors) &&
                (this.m_nTexDistance == fh.m_nTexDistance)&&
                (this.m_nTexDistanceLower == fh.m_nTexDistanceLower)&&
                (this.m_nTexDistanceIncrement == fh.m_nTexDistanceIncrement)&&
                (this.m_nTexDistanceIncrement == fh.m_nTexDistanceIncrement)
                ;
        }
        public override int GetHashCode()
        {
            return base.GetHashCode();
        }
        public override bool Increment()
        {
            bool carry = base.Increment();
            if ((this.NumFeatures == 0) && (this.NumCombinations > 1))
            {
                while (!carry && (this.NumFeatures == 0))
                    carry = base.Increment();
            }
            return carry;
        }
        public override void Reset()
        {
            base.Reset();
            if (this.NumFeatures == 0)
                Increment();
        }
        public override string ToString()
        {
            int i, j,k, lineno = 4;
            string s;
            StringBuilder bldr = new StringBuilder();

            bldr.AppendLine("CVIPtools feature file for image with " + this.m_nBands + " band");
            bldr.AppendLine("1. Image name    ");
            bldr.AppendLine("2. Object's row coordinate    ");
            bldr.AppendLine("3. Object's column coordinate    ");
            // Binary object features
            if (this.m_bUseArea)
            {
                s = lineno++.ToString() + ". Area   ";
                bldr.AppendLine(s);
            }
            if (this.m_bUseCentroid)
            {
                s = lineno++.ToString() + ". Centroid (row, column)   ";
                bldr.AppendLine(s);
            }
            if (this.m_bUseOrientation)
            {
                s = lineno++.ToString() + ". Orientation (Axis of least second moment)    ";
                bldr.AppendLine(s);
            }
            if (this.m_bUsePerimeter)
            {
                s = lineno++.ToString() + ". Perimeter    ";
                bldr.AppendLine(s);
            }
            if (this.m_bUseEuler)
            {
                s = lineno++.ToString() + ". Euler number    ";
                bldr.AppendLine(s);
            }
            if (this.m_bUseProjections)
            {
                s = lineno++.ToString() + ". Projection   (Height: ";
                s += this.m_nProjHeight.ToString();
                s += "  Width: ";
                s += this.m_nProjWidth.ToString();
                bldr.AppendLine(s + ")");
            }
            if (this.m_bUseThinness)
            {
                s = lineno++.ToString() + ". Thinness    ";
                bldr.AppendLine(s);
            }
            if (this.m_bUseAspect)
            {
                s = lineno++.ToString() + ". Aspect ratio    ";
                bldr.AppendLine(s);
            }
            // RST-Invariant Moment-Based features
            for (i = 0; i < 7; i++)
            {
                if (this.m_bUseRst[i])
                {
                    s = lineno++.ToString() + ". RST" + (i + 1).ToString() + "    ";
                    bldr.AppendLine(s);
                }
            }
            // Histogram features
            for (i = 0; i < 5; i++)
            {
                if (this.m_bUseHist[i])
                {
                    switch (i)
                    {
                    case 0: s = "Histo_Mean"; break;
                    case 1: s = "Histo_Standard_Deviation"; break;
                    case 2: s = "Histo_Skew"; break;
                    case 3: s = "Histo_Energy"; break;
                    case 4: s = "Histo_Entropy"; break;
                    default: s = ""; break;
                    }
                    if (this.m_nBands == 1)
                    {
                        bldr.AppendLine(lineno++.ToString() + ". " + s + "    ");
                    }
                    else
                    {
                        s += "_Band";
                        for (j = 0; j < this.m_nBands; j++)
                            bldr.AppendLine(lineno++.ToString() + ". " + s + j.ToString());
                    }
                }
            }

            // Laws Features
            for (i = 0; i < 15; i++)
            {
                if (this.m_bUseLaw[i])
                {
                    s = null;
                    string s1;
                    if (i == 0) s = "LevelLevel";
                    else if (i == 1) s = "LevelEdge";
                    else if (i == 2) s = "LevelSpot";
                    else if (i == 3) s = "LevelRipple";
                    else if (i == 4) s = "LevelWave";
                    else if (i == 5) s = "EdgeEdge";
                    else if (i == 6) s = "Edgespot";
                    else if (i == 7) s = "EdgeRipple";             
                    else if (i == 8) s = "EdgeWave";
                    else if (i == 9) s = "SpotSpot";
                    else if (i == 10) s = "SpotRipple";
                    else if (i == 11) s = "SpotWave";
                    else if (i == 12) s = "WaveRipple";
                    else if (i == 13) s = "WaveWave";
                    else if (i == 14) s = "RippleRipple";
                    for (k = 0; k < 5; k++)
                    {
                        s1 = "";
                        switch (k)
                        {
                            case 0: s1 = "_Mean"; break;
                            case 1: s1 = "_Standard_Deviation"; break;
                            case 2: s1 = "_Skew"; break;
                            case 3: s1 = "_Energy"; break;
                            case 4: s1 = "_Entropy"; break;
                            default: s = s1 = ""; break;
                        }                
                        if (this.m_nBands == 1)
                        {
                            bldr.AppendLine(lineno++.ToString() + ". " + s + s1 + " ");
                        }                   
                        else
                        {
                            s1 += "_Band";
                            for (j = 0; j < this.m_nBands; j++)
                                bldr.AppendLine(lineno++.ToString() + ". " + s + s1 + j.ToString());
                        }
                    }
                }
            }



            // Texture features
            for (i = 0; i < 5; i++)
            {
                if (this.m_bUseTexture[i])
                {
                    switch (i)
                    {
                    case 0: s = "Texture energy"; break;
                    case 1: s = "Inertia"; break;
                    case 2: s = "Correlation"; break;
                    case 3: s = "Inverse diff"; break;
                    case 4: s = "Texture entropy"; break;
                    default: s = ""; break;
                    }
                    bldr.Append(lineno++.ToString() + ". " + s);
                    bldr.Append(" average (Texture Distance: ");
                    //if (!this.m_bUseTexture[6])
                    bldr.Append(this.m_nTexDistancecalc.ToString());
                 //   else bldr.Append(this.m_nTexDistanceLower.ToString());
                   // bldr.Append(this.m_nTexDistanceLower.ToString());
                   // bldr.Append(this.m_nTexDistanceIncrement.ToString());
                   // bldr.Append(this.m_nTexDistanceUpper.ToString());
                    if (this.m_bTexUseTexture2)
                    {
                        bldr.Append("  IncludeZeroPairs: ");
                        bldr.Append(this.m_bTexUseZeroPairs.ToString());
                    }
                    bldr.AppendLine(")");
                    bldr.AppendLine(lineno++.ToString() + ". " + s + " range    ");
                   
                }

            }
            // Spectral features
            if (this.m_bUseSpectral)
            {
                for (i = 0; i < this.m_nBands; i++)
                {
                    s = lineno++.ToString() + ". Spectral_DC";
                    if (this.m_nBands > 1)
                        s += ("_Band" + i.ToString());
                    bldr.AppendLine(s);
                    for (j = 1; j <= this.m_nSpecRings; j++)
                    {
                        s = lineno++.ToString() + ". Ring" + j.ToString();
                        if (this.m_nBands > 1)
                            s += ("_Band" + i.ToString());
                        bldr.AppendLine(s);
                    }
                    for (j = 1; j <= this.m_nSpecSectors; j++)
                    {
                        s = lineno++.ToString() + ". Sector" + j.ToString();
                        if (this.m_nBands > 1)
                            s += ("_Band" + i.ToString());
                        bldr.AppendLine(s);
                    }
                }
            }
            bldr.AppendLine("*** END OF HEADER; CLASS (optional) SHOWN AT THE END OF DATA ***");
            bldr.AppendLine();
            return bldr.ToString();
        }

        [XmlIgnore]
        public int Bands
        {
            get { return this.m_nBands; }
            set
            {
                if (value == -1)
                    this.m_nBands = value;
                if (this.m_nBands != -1)
                    throw new ArgumentException("Bands is already set.", "FeatureHeader.Bands");
                this.m_nBands = value;
            }
        }
        public int NumFeatures
        {
            get
            {
                int count = 0, i;
                // Binary object features
                if (this.m_bUseArea) count++;
                if (this.m_bUseCentroid) count++;
                if (this.m_bUseOrientation) count++;
                if (this.m_bUsePerimeter) count++;
                if (this.m_bUseEuler) count++;
                if (this.m_bUseProjections) count++;
                if (this.m_bUseThinness) count++;
                if (this.m_bUseAspect) count++;

                // RST-Invariant Moment-Based features
                for (i = 0; i < 7; i++)
                    if (this.m_bUseRst[i]) count++;

                // Histogram features
                for (i = 0; i < 5; i++)
                    if (this.m_bUseHist[i]) count++;

                // Texture features
                for (i = 0; i < 5; i++)
                    if (this.m_bUseTexture[i]) count++;
               //for Laws Texture
                for (i = 0; i < 15; i++)
                    if (this.m_bUseLaw[i]) count++;
                //testure distance
               
               // count = count + ((this.m_nTexDistanceUpper - this.m_nTexDistanceLower) / this.m_nTexDistanceIncrement) +1;

                // Spectral features
                if (this.m_bUseSpectral) count++;

                return count;
            }
        }
        public int ProjectionsHeight
        {
            get { return this.m_nProjHeight; }
            set
            {
                if (value <= 0)
                    throw new ArgumentOutOfRangeException("ProjectionsHeight", "Must be > 0");
                this.m_nProjHeight = value;
            }
        }
        public int ProjectionsWidth
        {
            get { return this.m_nProjWidth; }
            set
            {
                if (value <= 0)
                    throw new ArgumentOutOfRangeException("ProjectionsWidth", "Must be > 0");
                this.m_nProjWidth = value;
            }
        }
        public int SpectralRings
        {
            get { return this.m_nSpecRings; }
            set
            {
                if (value <= 0)
                    throw new ArgumentOutOfRangeException("SpectralRings", "Must be > 0");
                this.m_nSpecRings = value;
            }
        }
        public int SpectralSectors
        {
            get { return this.m_nSpecSectors; }
            set
            {
                if (value <= 0)
                    throw new ArgumentOutOfRangeException("SpectralSectors", "Must be > 0");
                this.m_nSpecSectors = value;
            }
        }
        public int TextureDistance
        {
            get { return this.m_nTexDistance; }
            set
            {
                if (value <= 0)
                    throw new ArgumentOutOfRangeException("TextureDistance", "Must be > 0");
                this.m_nTexDistance =value;
            }
        }

        public int TextureDistanceLower
        { 
            get {return this.m_nTexDistanceLower; }
                
                //int distance = this.m_nTexDistanceLower;

               // if (distance <= this.m_nTexDistanceUpper)
                //{
                 //   distance = this.m_nTexDistanceLower + inc;
                 //   inc = this.m_nTexDistanceIncrement;
               // }
              //  return distance;
          //  }
            set
            {

                if (value <= 0)
                    throw new ArgumentOutOfRangeException("TextureDistanceLower", "Must be > 0");

            this.m_nTexDistanceLower = value;
            }
        }

        public int TextureDistanceCalc
        {
            get { return this.m_nTexDistancecalc; }
            set
            {
               // if (value <= 0)
                    //throw new ArgumentOutOfRangeException("TextureDistance", "Must be > 0");
                this.m_nTexDistancecalc = value;
            }
        }

        public int TextureDistanceIncrement
        {
            get { return this.m_nTexDistanceIncrement; }
            set
            {
                //if (value <= 0)
                   // throw new ArgumentOutOfRangeException("TextureDistanceIncrement", "Must be > 0");
                this.m_nTexDistanceIncrement = value;
            }
        }

        public int TextureDistanceUpper
        {
            get { return this.m_nTexDistanceUpper; }
            set
            {
              //  if (value <= 0)
                   // throw new ArgumentOutOfRangeException("TextureDistanceUpper", "Must be > 0");
               this.m_nTexDistanceUpper = value;
            }
        }

        public bool[] UseHist { get { return this.m_bUseHist; } }
        public bool[] UseRst { get { return this.m_bUseRst; } }
        public bool[] UseTexture { get { return this.m_bUseTexture; } }
        public bool[] UseLaw { get { return this.m_bUseLaw; } }
        public List<int> MultipleTex { get { return this.m_texDistance; } }
        public bool TextureUseTexture2
        {
            get { return this.m_bTexUseTexture2; }
            set { this.m_bTexUseTexture2 = value; }
        }
        public bool TextureUseZeros
        {
            get { return this.m_bTexUseZeroPairs; }
            set { this.m_bTexUseZeroPairs = value; }
        }
        public bool UseArea
        {
            get { return this.m_bUseArea; }
            set { this.m_bUseArea = value; }
        }
        public bool UseAspectRatio
        {
            get { return this.m_bUseAspect; }
            set { this.m_bUseAspect = value; }
        }
        public bool UseCentroid
        {
            get { return this.m_bUseCentroid; }
            set { this.m_bUseCentroid = value; }
        }
        public bool UseEuler
        {
            get { return this.m_bUseEuler; }
            set { this.m_bUseEuler = value; }
        }
        public bool UseOrientation
        {
            get { return this.m_bUseOrientation; }
            set { this.m_bUseOrientation = value; }
        }
        public bool UsePerimeter
        {
            get { return this.m_bUsePerimeter; }
            set { this.m_bUsePerimeter = value; }
        }
        public bool UseProjections
        {
            get { return this.m_bUseProjections; }
            set { this.m_bUseProjections = value; }
        }
        public bool UseThinness
        {
            get { return this.m_bUseThinness; }
            set { this.m_bUseThinness = value; }
        }
        public bool UseHistMean
        {
            get { return this.m_bUseHist[0]; }
            set { this.m_bUseHist[0] = value; }
        }
        public bool UseHistStdDev
        {
            get { return this.m_bUseHist[1]; }
            set { this.m_bUseHist[1] = value; }
        }
        public bool UseHistSkew
        {
            get { return this.m_bUseHist[2]; }
            set { this.m_bUseHist[2] = value; }
        }
        public bool UseHistEnergy
        {
            get { return this.m_bUseHist[3]; }
            set { this.m_bUseHist[3] = value; }
        }
        public bool UseHistEntropy
        {
            get { return this.m_bUseHist[4]; }
            set { this.m_bUseHist[4] = value; }
        }
        public bool UseRst1
        {
            get { return this.m_bUseRst[0]; }
            set { this.m_bUseRst[0] = value; }
        }
        public bool UseRst2
        {
            get { return this.m_bUseRst[1]; }
            set { this.m_bUseRst[1] = value; }
        }
        public bool UseRst3
        {
            get { return this.m_bUseRst[2]; }
            set { this.m_bUseRst[2] = value; }
        }
        public bool UseRst4
        {
            get { return this.m_bUseRst[3]; }
            set { this.m_bUseRst[3] = value; }
        }
        public bool UseRst5
        {
            get { return this.m_bUseRst[4]; }
            set { this.m_bUseRst[4] = value; }
        }
        public bool UseRst6
        {
            get { return this.m_bUseRst[5]; }
            set { this.m_bUseRst[5] = value; }
        }
        public bool UseRst7
        {
            get { return this.m_bUseRst[6]; }
            set { this.m_bUseRst[6] = value; }
        }
        public bool UseMask1
        {
            get { return this.m_bUseLaw[0]; }
            set { this.m_bUseLaw[0] = value; }
        }
        public bool UseMask2
        {
            get { return this.m_bUseLaw[1]; }
            set { this.m_bUseLaw[1] = value; }
        }
        public bool UseMask3
        {
            get { return this.m_bUseLaw[2]; }
            set { this.m_bUseLaw[2] = value; }
        }
        public bool UseMask4
        {
            get { return this.m_bUseLaw[3]; }
            set { this.m_bUseLaw[3] = value; }
        }
        public bool UseMask5
        {
            get { return this.m_bUseLaw[4]; }
            set { this.m_bUseLaw[4] = value; }
        }
        public bool UseMask6
        {
            get { return this.m_bUseLaw[5]; }
            set { this.m_bUseLaw[5] = value; }
        }
        public bool UseMask7
        {
            get { return this.m_bUseLaw[6]; }
            set { this.m_bUseLaw[6] = value; }
        }
        public bool UseMask8
        {
            get { return this.m_bUseLaw[7]; }
            set { this.m_bUseLaw[7] = value; }
        }
        public bool UseMask9
        {
            get { return this.m_bUseLaw[8]; }
            set { this.m_bUseLaw[8] = value; }
        }
        public bool UseMask10
        {
            get { return this.m_bUseLaw[9]; }
            set { this.m_bUseLaw[9] = value; }
        }
        public bool UseMask11
        {
            get { return this.m_bUseLaw[10]; }
            set { this.m_bUseLaw[10] = value; }
        }
        public bool UseMask12
        {
            get { return this.m_bUseLaw[11]; }
            set { this.m_bUseLaw[11] = value; }
        }
        public bool UseMask13
        {
            get { return this.m_bUseLaw[12]; }
            set { this.m_bUseLaw[12] = value; }
        }
        public bool UseMask14
        {
            get { return this.m_bUseLaw[13]; }
            set { this.m_bUseLaw[13] = value; }
        }
        public bool UseMask15
        {
            get { return this.m_bUseLaw[14]; }
            set { this.m_bUseLaw[14] = value; }
        }

        public bool UseSpectral
        {
            get { return this.m_bUseSpectral; }
            set { this.m_bUseSpectral = value; }
        }
        public bool UseTexEnergy
        {
            get { return this.m_bUseTexture[0]; }
            set { this.m_bUseTexture[0] = value; }
        }
        public bool UseTexInertia
        {
            get { return this.m_bUseTexture[1]; }
            set { this.m_bUseTexture[1] = value; }
        }
        public bool UseTexCorrelation
        {
            get { return this.m_bUseTexture[2]; }
            set { this.m_bUseTexture[2] = value; }
        }
        public bool UseTexInvDiff
        {
            get { return this.m_bUseTexture[3]; }
            set { this.m_bUseTexture[3] = value; }
        }
        public bool UseCombTex
        {
            get { return this.m_bUseTexture[5]; }
            set { this.m_bUseTexture[5] = value; }
        }
        public bool UseTexEntropy
        {
            get { return this.m_bUseTexture[4]; }
            set { this.m_bUseTexture[4] = value; }
        }
        public bool UseCombText
        {
            get { return this.m_bUseTexture[5]; }
            set { this.m_bUseTexture[5] = value; }
        }      
    }
}
