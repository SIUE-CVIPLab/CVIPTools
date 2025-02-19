/*''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' ======================================================================
' Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
' ======================================================================
'
'             File Name: FeatureHeader.cs
'           Description: Contains the controls and code
'                        for Analysis->FeatureHeader class
'         Related Files: Classification.cs
'                        CvipOp.cs
'   Initial Coding Date: August 2009
'              Modified: March 2010
'       Delevoping tool: Visual Studio 2010-C#
'             Credit(s): Patrick Solt
'                        Jhansi Lakshmi Akkineni
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
using System.IO;
using System.Text;
using System.Windows.Forms;
using System.Text.RegularExpressions;

namespace CVIPGUI.Analysis
{
    public class FeatureHeader
    {
        bool m_bTexUseZeroPairs = false;
        bool m_bUseArea = false;
        bool m_bUseAspect = false;
        bool m_bUseCentroid = false;
        bool m_bUseEuler = false;
        bool m_bUseOrientation = false;
        bool m_bUsePerimeter = false;
        bool m_bUseProjections = false;
        bool m_bUseSpectral = false;
        bool m_bUseThinness = false;

        bool[] m_bUseHist = new bool[5];
        bool[] m_bUseRst = new bool[7];
        private bool[] m_bUseLaw = new bool[15];
        bool[] m_bUseTexture = new bool[5];

        int m_nBands = -1;
        int m_nProjHeight = 10;
        int m_nProjWidth = 10;
        int m_nSpecRings = 3;
        int m_nSpecSectors = 3;
        int m_nTexDistance = 2;

        public FeatureHeader()
        {
        }
        public FeatureHeader(int bands)
        {
            this.m_nBands = bands;
        }
        public FeatureHeader(FeatureHeader fh)
        {
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
            this.m_nBands = fh.m_nBands;
            this.m_nProjHeight = fh.m_nProjHeight;
            this.m_nProjWidth = fh.m_nProjWidth;
            this.m_nSpecRings = fh.m_nSpecRings;
            this.m_nSpecSectors = fh.m_nSpecSectors;
            this.m_nTexDistance = fh.m_nTexDistance;
        }
        public override bool Equals(object obj)
        {
            return (Equals(obj as FeatureHeader));
        }
        public bool Equals(FeatureHeader fh)
        {
            return ((object)fh != null) &&
                ((this.m_nBands == -1) || (fh.m_nBands == -1) || (this.m_nBands == fh.m_nBands)) &&
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
                (this.m_nProjHeight == fh.m_nProjHeight) &&
                (this.m_nProjWidth == fh.m_nProjWidth) &&
                (this.m_nSpecRings == fh.m_nSpecRings) &&
                (this.m_nSpecSectors == fh.m_nSpecSectors) &&
                (this.m_nTexDistance == fh.m_nTexDistance);
        }
        public override int GetHashCode()
        {
            return base.GetHashCode();
        }
        static public FeatureHeader Parse(StreamReader sr)
        {
            string s;
            int bands = -1, lineno = 0;
            FeatureHeader fh = null;
            while ((s = sr.ReadLine()) != null)
            {
                lineno++;
                s = s.Trim().ToLower();
                if (!string.IsNullOrEmpty(s) &&
                    s.Contains("feature file for image with"))
                {
                    s = s.Substring(s.IndexOf("with") + "with".Length).Trim();
                    s = s.Substring(0, s.IndexOf(' '));
                    if (int.TryParse(s, out bands) && ((bands == 1) || (bands == 3)))
                        fh = new FeatureHeader(bands);
                    break;
                }
            }
            if (fh == null)
            {
                MessageBox.Show("Couldn't find beginning of header.", "FeatureHeader.Parse()",
                    MessageBoxButtons.OK, MessageBoxIcon.Warning);
                return null;
            }
            try
            {
                int idx, nextcol = 1;
                while ((s = sr.ReadLine()) != null)
                {
                    lineno++;
                    s = s.Trim().ToLower();
                    if (string.IsNullOrEmpty(s))
                        continue;
                    if (s.Contains("***"))
                        break;
                    if (!char.IsDigit(s[0]))
                    {
                        MessageBox.Show("Line " + lineno.ToString() + ": Incorrect format.",
                            "FeatureHeader.Parse()", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                        fh = null;
                        return null;
                    }
                    idx = int.Parse(s.Substring(0, s.IndexOf('.')));
                    if (idx != nextcol++)
                    {
                        MessageBox.Show("Column " + idx.ToString() + " out of sequence.",
                            "FeatureHeader.Parse()", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                        fh = null;
                        return null;
                    }
                    if (s.Contains("area"))
                        fh.m_bUseArea = true;
                    else if (s.Contains("centroid"))
                        fh.m_bUseCentroid = true;
                    else if (s.Contains("orientation"))
                        fh.m_bUseOrientation = true;
                    else if (s.Contains("perimeter"))
                        fh.m_bUsePerimeter = true;
                    else if (s.Contains("euler"))
                        fh.m_bUseEuler = true;
                    else if (s.Contains("projection"))
                    {
                        fh.m_bUseProjections = true;
                        idx = s.IndexOf("height:") + "height:".Length;
                        s = s.Substring(idx).Trim();
                        idx = s.IndexOf(' ');
                        fh.m_nProjHeight = int.Parse(s.Substring(0, idx));
                        s = s.Substring(idx).Trim();
                        idx = s.IndexOf("width:") + "width:".Length;
                        s = s.Substring(idx).Trim();
                        fh.m_nProjWidth = int.Parse(s.Substring(0, s.IndexOf(')')));
                    }
                    else if (s.Contains("thinness"))
                        fh.m_bUseThinness = true;
                    else if (s.Contains("aspect ratio"))
                        fh.m_bUseAspect = true;
                    else if (s.Contains("rst"))
                    {
                        idx = s.IndexOf("rst") + "rst".Length;
                        s = s.Substring(idx).Trim();
                        fh.m_bUseRst[int.Parse(s) - 1] = true;
                    }
                    else if (s.Contains("histo"))
                    {
                        if (s.Contains("mean"))
                            fh.UseHistMean = true;
                        else if (s.Contains("standard_deviation"))
                            fh.UseHistStdDev = true;
                        else if (s.Contains("skew"))
                            fh.UseHistSkew = true;
                        else if (s.Contains("energy"))
                            fh.UseHistEnergy = true;
                        else if (s.Contains("entropy"))
                            fh.UseHistEntropy = true;
                    }
                   
                    else if (s.Contains("texture distance:"))
                    {
                        if (s.Contains("energy"))
                            fh.UseTexEnergy = true;
                        else if (s.Contains("inertia"))
                            fh.UseTexInertia = true;
                        else if (s.Contains("correlation"))
                            fh.UseTexCorrelation = true;
                        else if (s.Contains("inverse diff"))
                            fh.UseTexInvDiff = true;
                        else if (s.Contains("entropy"))
                            fh.UseTexEntropy = true;
                        idx = s.IndexOf("texture distance:") + "texture distance:".Length;
                        s = s.Substring(idx).Trim();
                        idx = s.IndexOfAny(new char[] { ' ', ')' });
                        fh.m_nTexDistance = int.Parse(s.Substring(0, idx));
                        s = s.Substring(idx).Trim();
                        if (s.Contains("includezeropairs:"))
                        {
                            idx = s.IndexOf("includezeropairs:") + "includezeropairs:".Length;
                            s = s.Substring(idx).Trim();
                            fh.m_bTexUseZeroPairs = bool.Parse(s.Substring(0, s.IndexOf(')')));
                        }
                    }
                    else if (s.Contains("level") || s.Contains("edge") || s.Contains("spot") || s.Contains("ripple") || s.Contains("wave"))
                    {
                        int s_val = -1;
                        if (s.Contains("levellevel")) s_val = 0;
                        else if (s.Contains("leveledge"))s_val=1;
                        else if (s.Contains("levelspot"))s_val=2;
                        else if (s.Contains("levelripple"))s_val=3;
                        else if (s.Contains("levelwave"))s_val=4;
                        else if (s.Contains("edgeedge"))s_val=5;
                        else if (s.Contains("edgespot"))s_val=6;
                        else if (s.Contains("edgeripple"))s_val=7;
                        else if (s.Contains("edgewave"))s_val=8;
                        else if (s.Contains("spotspot"))s_val=9;
                        else if (s.Contains("spotripple"))s_val= 10;
                        else if (s.Contains("spotwave"))s_val=11;
                        else if (s.Contains("waveripple"))s_val=12;
                        else if (s.Contains("wavewave"))s_val= 13;
                        else if (s.Contains("rippleripple"))s_val= 14;
                       
                        if (s.Contains("mean"))
                            fh.m_bUseLaw[s_val] = true;
                        else if (s.Contains("standard_deviation"))
                            fh.m_bUseLaw[s_val] = true;//fh.UseHistStdDev = true;
                        else if (s.Contains("skew"))
                            fh.m_bUseLaw[s_val] = true;//
                        else if (s.Contains("energy"))
                            fh.m_bUseLaw[s_val] = true;
                        else if (s.Contains("entropy"))
                            fh.m_bUseLaw[s_val] = true;
                        /* idx = s.IndexOf("LawTexture") + "LawTexture".Length;
                         s = s.Substring(idx).Trim();
                         fh.m_bUseLaw[int.Parse(s) - 1] = true;*/
                    }
                    else if (s.Contains("spectral"))
                        fh.m_bUseSpectral = true;
                    else if (s.Contains("ring"))
                    {
                        idx = s.IndexOf("ring") + "ring".Length;
                        s = s.Substring(idx).Trim();
                        for (idx = 0; (idx < s.Length) && char.IsDigit(s[idx]); idx++) ;
                        s = s.Substring(0, idx);
                        fh.m_nSpecRings = int.Parse(s);
                    }
                    else if (s.Contains("sector"))
                    {
                        idx = s.IndexOf("sector") + "sector".Length;
                        s = s.Substring(idx).Trim();
                        for (idx = 0; (idx < s.Length) && char.IsDigit(s[idx]); idx++) ;
                        s = s.Substring(0, idx);
                        fh.m_nSpecSectors = int.Parse(s);
                    }
                }
                if (!s.Contains("***"))
                {
                    MessageBox.Show("Couldn't find end of header.", "FeatureHeader.Parse()",
                        MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    fh = null;
                    return null;
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show("Line " + lineno.ToString() + " - Unhandled exception: " + ex.Message,
                    "FeatureHeader.Parse()", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                fh = null;
                return null;
            }
            return (fh);
        }
        public override string ToString()
        {
            StringBuilder bldr = new StringBuilder();
            try
            {
                string s;
                int i, j, lineno = 4;
                bldr.AppendLine("CVIPtools feature file for image with " + this.m_nBands + " band");
                bldr.AppendLine("1. Image Name    ");
                bldr.AppendLine("2. Object's Row Coordinate    ");
                bldr.AppendLine("3. Object's Column Coordinate    ");
                // Binary object features
                if (this.m_bUseArea)
                {
                    s = lineno++.ToString() + ". Area   ";
                    bldr.AppendLine(s);
                }
                if (this.m_bUseCentroid)
                {
                    s = lineno++.ToString() + ". Centroid (Row, Column)   ";
                    bldr.AppendLine(s);
                }
                if (this.m_bUseOrientation)
                {
                    s = lineno++.ToString() + ". Orientation (Axis of Least Second Moment)    ";
                    bldr.AppendLine(s);
                }
                if (this.m_bUsePerimeter)
                {
                    s = lineno++.ToString() + ". Perimeter    ";
                    bldr.AppendLine(s);
                }
                if (this.m_bUseEuler)
                {
                    s = lineno++.ToString() + ". Euler Number    ";
                    bldr.AppendLine(s);
                }
                if (this.m_bUseProjections)
                {
                    s = lineno++.ToString() + ". Projection (Height: ";
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
                    s = lineno++.ToString() + ". Aspect Ratio    ";
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
                // Texture features
                for (i = 0; i < 5; i++)
                {
                    if (this.m_bUseTexture[i])
                    {
                        switch (i)
                        {
                        case 0: s = "Texture Energy"; break;
                        case 1: s = "Inertia"; break;
                        case 2: s = "Correlation"; break;
                        case 3: s = "Inverse Diff"; break;
                        case 4: s = "Texture Entropy"; break;
                        default: s = ""; break;
                        }
                        bldr.Append(lineno++.ToString() + ". " + s);
                        bldr.Append(" Average (Texture Distance: ");
                        bldr.Append(this.m_nTexDistance.ToString());
                        bldr.Append("  IncludeZeroPairs: ");
                        bldr.AppendLine(this.m_bTexUseZeroPairs.ToString() + ")");
                        bldr.AppendLine(lineno++.ToString() + ". " + s + " Range    ");
                    }
                }

                //Laws Texture
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
                        else if (i ==7) s = "EdgeRipple";
                        else if (i == 8) s = "EdgeWave";
                        else if (i == 9) s = "SpotSpot";
                        else if (i == 10) s = "SpotRipple";
                        else if (i == 11) s = "SpotWave";
                        else if (i == 12) s = "WaveRipple";
                        else if (i == 13) s = "WaveWave";
                        else if (i == 14) s = "RippleRipple";
                        
                        for (int k = 0; k < 5; k++)
                        {
                            s1 = "";
                            switch (k)
                            {

                                case 0: s1 = "_Mean"; break;
                                case 1: s1 = "_Standard_Deviation"; break;
                                case 2: s1 = "_Skew"; break;
                                case 3: s1 =  "_Energy"; break;
                                case 4: s1 = "_Entropy"; break;
                                default: s=s1 = ""; break;
                            }
                            if (this.m_nBands == 1)
                            {
                                bldr.AppendLine(lineno++.ToString() + ". " + s +s1+ "    ");
                            }
                            else
                            {
                                s1 += "_Band";
                                for (j = 0; j < this.m_nBands; j++)
                                    bldr.AppendLine(lineno++.ToString() + ". " + s+s1 + j.ToString());
                            }
                        }
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
            }
            catch (Exception ex)
            {
                MessageBox.Show("Unhandled exception: " + ex.Message,
                    "FeatureHeader.ToString()", MessageBoxButtons.OK, MessageBoxIcon.Warning);
            }
            return bldr.ToString();
        }

        public int Bands
        {
            get { return this.m_nBands; }
            set
            {
                if (value == -1)
                    this.m_nBands = value;
                if (this.m_nBands != -1)
                {
                    MessageBox.Show("Bands is already set.", "FeatureHeader.Bands.set",
                        MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    return;
                }
                this.m_nBands = value;
            }
        }
        public int ProjectionsHeight
        {
            get { return this.m_nProjHeight; }
            set
            {
                if (value <= 0)
                {
                    MessageBox.Show("Invalid value.", "FeatureHeader.ProjectionsHeight.set",
                        MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    return;
                }
                this.m_nProjHeight = value;
            }
        }
        public int ProjectionsWidth
        {
            get { return this.m_nProjWidth; }
            set
            {
                if (value <= 0)
                {
                    MessageBox.Show("Invalid value.", "FeatureHeader.ProjectionsWidth.set",
                        MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    return;
                }
                this.m_nProjWidth = value;
            }
        }
        public int SpectralRings
        {
            get { return this.m_nSpecRings; }
            set
            {
                if (value <= 0)
                {
                    MessageBox.Show("Invalid value.", "FeatureHeader.SpectralRings.set",
                        MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    return;
                }
                this.m_nSpecRings = value;
            }
        }
        public int SpectralSectors
        {
            get { return this.m_nSpecSectors; }
            set
            {
                if (value <= 0)
                {
                    MessageBox.Show("Invalid value.", "FeatureHeader.SpectralSectors.set",
                        MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    return;
                }
                this.m_nSpecSectors = value;
            }
        }
        public int TextureDistance
        {
            get { return this.m_nTexDistance; }
            set
            {
                if (value <= 0)
                {
                    MessageBox.Show("Invalid value.", "FeatureHeader.TextureDistance.set",
                        MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    return;
                }
                this.m_nTexDistance = value;
            }
        }
        public bool[] UseHist { get { return this.m_bUseHist; } }
        public bool[] UseRst { get { return this.m_bUseRst; } }
        public bool[] UseLaw { get { return this.m_bUseLaw; } }
        public bool[] UseTexture { get { return this.m_bUseTexture; } }
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
        public bool UseTexEntropy
        {
            get { return this.m_bUseTexture[4]; }
            set { this.m_bUseTexture[4] = value; }
        }
        public bool UseThinness
        {
            get { return this.m_bUseThinness; }
            set { this.m_bUseThinness = value; }
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
    }
}
