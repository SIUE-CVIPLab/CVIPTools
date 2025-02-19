/*''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' ======================================================================
' Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
' ======================================================================
'
'             File Name: CvipObject.cs
'           Description: Contains the controls and code
'                        for Analysis->CvipObject class
'         Related Files: Classification.cs
'                        CvipOp.cs
'   Initial Coding Date: August 2009
'              Modified: March 2010
'       Delevoping tool: Visual Studio 2010-C#
'             Credit(s): Patrick Solt
'                        Jhansi Lakshmi Akkineni
'                        Southern Illinois University Edwardsville
'
' Copyright (C) 2014 Scott Umbaugh and SIUE
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
using System.Windows.Forms;

namespace CVIPGUI.Analysis
{
    public class CvipObject
    {
        FeatureHeader m_hdrFeatures = null;
        string m_strName = null;
        string m_strCol = null, m_strRow = null;// m_strBand = null;
              
        string m_strArea = null;
        string m_strAspect = null;
        string m_strCentroidCol = null;
        string m_strCentroidRow = null;
        string m_strClass = null;
        string m_strEuler = null;
        string[,] m_strHist = null;
        string m_strOrientation = null;
        string m_strPerimeter = null;
        string[,,] m_law = null;
        string[] m_strProjections = null;
        string[] m_strRst = null;
        string[] m_strSpectralDC = null;
        string[,] m_strSpectralRings = null;
        string[,] m_strSpectralSectors = null;
        string[,] m_strTexture = null;
        string m_strThinness = null;

        CvipObject(string name, FeatureHeader fh)
        {
            this.m_hdrFeatures = fh;
            this.m_strName = name;
        }
        static public CvipObject Create(string name, string seg,int imgOrig, int imgLabeled, int row, int col, FeatureHeader fh, string classname)
        {
            int bands = CvipOp.GetNoOfBands_Image(imgOrig);
            if (fh.Bands == -1)
                fh.Bands = bands;
            if (fh.Bands != bands)
            {

                MessageBox.Show("Image.Bands does not equal FeatureHeader.Bands.", "CvipObject.Create()",
                    MessageBoxButtons.OK, MessageBoxIcon.Warning);
                return null;
            }

            CvipObject obj = new CvipObject(name, fh);
            obj.m_strRow = row.ToString();
            obj.m_strCol = col.ToString();
            //obj.m_strBand = bands.ToString();

            // Binary object features
            if (fh.UseArea)
                obj.m_strArea = CvipOp.Area(imgLabeled, row, col).ToString();
            if (fh.UseCentroid)
            {
                int[] val = CvipOp.CentroID(imgLabeled, row, col);
                obj.m_strCentroidRow = val[0].ToString();
                obj.m_strCentroidCol = val[1].ToString();
            }
            if (fh.UseOrientation)
                obj.m_strOrientation = CvipOp.Orientation(imgLabeled, row, col).ToString();
            if (fh.UsePerimeter)
                obj.m_strPerimeter = CvipOp.Perimeter(imgLabeled, row, col).ToString();
            if (fh.UseEuler)
                obj.m_strEuler = CvipOp.Euler(imgLabeled, row, col).ToString();
            if (fh.UseProjections)
            {
                int height = fh.ProjectionsHeight;
                int width = fh.ProjectionsWidth;
                int count = height + width;
                obj.m_strProjections = new string[count];
                int[] vals = CvipOp.Projection(imgLabeled, row, col, height, width);
                for (int i = 0; i < count; i++)
                    obj.m_strProjections[i] = vals[i].ToString();
            }
            if (fh.UseThinness)
                obj.m_strThinness = CvipOp.Thinness(imgLabeled, row, col).ToString("0.000000");
            if (fh.UseAspectRatio)
                obj.m_strAspect = CvipOp.Aspect(imgLabeled, row, col).ToString("0.000000");

            // RST-Invariant Moment-Based features
            for (int i = 0; i < 7; i++)
            {
                if (fh.UseRst[i])
                {
                    obj.m_strRst = new string[7];
                    double[] vals = CvipOp.Rst_invariant(imgLabeled, row, col);
                    for (int j = 0; j < 7; j++)
                        obj.m_strRst[j] = vals[j].ToString("0.000000");
                    break;
                }
            }


            // histogram feature
            for (int i = 0; i < 5; i++)
            {
                if (fh.UseHist[i])
                {
                    obj.m_strHist = new string[5, fh.Bands];
                    double[] vals = CvipOp.Hist_Feature(imgOrig, imgLabeled, row, col);
                    for (int j = 0; j < 5; j++)
                    {
                        for (int k = 0; k < fh.Bands; k++)
                        {
                            if ((j == 2) && double.IsNaN(vals[j + (k * 5)]))
                                vals[j + (k * 5)] = 256.0;
                            obj.m_strHist[j, k] = vals[j + (k * 5)].ToString("0.000000");
                        }
                    }
                    break;
                }
            }
            // texture features
            for (int i = 0; i < 5; i++)
            {
                if (fh.UseTexture[i])
                {
                    obj.m_strTexture = new string[5, 2];
                    int img = CvipOp.Duplicate_Image(imgOrig);
                    if (fh.Bands != 1)
                        img = CvipOp.Luminance_Image(img);
                    double[] values = CvipOp.Texture2_Feature(img, imgLabeled, 0, row, col,
                        fh.TextureDistance, true, true, true, true, true, fh.TextureUseZeros);
                    CvipOp.Delete_Image(ref img);
                    for (int j = 0; j < 5; j++)
                    {
                        obj.m_strTexture[j, 0] = values[(j * 6) + 4].ToString("0.000000");
                        obj.m_strTexture[j, 1] = values[(j * 6) + 5].ToString("0.000000");
                    }
                    break;
                }
            }
            //law textures
           /* for (int i = 0; i < 15; i++)
            {
                if (fh.UseLaw[i]) ;
                for (int k = 0; k < 15; k++) ;

                        //bldr.Append(" " + fh.Law[k].ToString("0.000000"));
                //  bldr.Append(" " + fv.Law[i].ToString("0.000000"));

            }*/
            for (int i = 0; i < 15; i++)
            {
                


                    if (i == 0)
                        obj.m_law = new string[15, 5, fh.Bands];
                    if (fh.UseLaw[i])
                    {
                        if (name != seg)
                        {
                        double[] law = null;
                        //
                        try
                        {
                            if ((law == null) && (imgOrig != 0) && (imgLabeled != 0))
                            {
                                //  law = base.Law = (double[])CvipOp.Rst_invariant(ref this.pLabeled, this.Row, this.Col);
                                if (fh.UseMask1 && i == 0)
                                { law = (double[])CvipOp.Laws_Texture_Feature(imgOrig, imgLabeled, row, col, 15, 0, 0); }
                                if (fh.UseMask2 && i == 1)
                                    law = (double[])CvipOp.Laws_Texture_Feature(imgOrig, imgLabeled, row, col, 15, 0, 1);
                                if (fh.UseMask3 && i == 2)
                                    law = (double[])CvipOp.Laws_Texture_Feature(imgOrig, imgLabeled, row, col, 15, 0, 2);
                                if (fh.UseMask4 && i == 3)
                                    law = (double[])CvipOp.Laws_Texture_Feature(imgOrig, imgLabeled, row, col, 15, 0, 3);
                                if (fh.UseMask5 && i == 4)
                                    law = (double[])CvipOp.Laws_Texture_Feature(imgOrig, imgLabeled, row, col, 15, 0, 4);

                                if (fh.UseMask6 && i == 5)
                                    law = (double[])CvipOp.Laws_Texture_Feature(imgOrig, imgLabeled, row, col, 15, 1, 1);
                                if (fh.UseMask7 && i == 6)
                                    law = (double[])CvipOp.Laws_Texture_Feature(imgOrig, imgLabeled, row, col, 15, 1, 2);
                                if (fh.UseMask8 && i == 7)
                                    law = (double[])CvipOp.Laws_Texture_Feature(imgOrig, imgLabeled, row, col, 15, 1, 3);
                                if (fh.UseMask9 && i == 8)
                                    law = (double[])CvipOp.Laws_Texture_Feature(imgOrig, imgLabeled, row, col, 15, 1, 4);
                                if (fh.UseMask10 && i == 9)
                                    law = (double[])CvipOp.Laws_Texture_Feature(imgOrig, imgLabeled, row, col, 15, 2, 2);
                                if (fh.UseMask11 && i == 10)
                                    law = (double[])CvipOp.Laws_Texture_Feature(imgOrig, imgLabeled, row, col, 15, 2, 3);
                                if (fh.UseMask12 && i == 11)
                                    law = (double[])CvipOp.Laws_Texture_Feature(imgOrig, imgLabeled, row, col, 15, 2, 4);
                                if (fh.UseMask13 && i == 12)
                                    law = (double[])CvipOp.Laws_Texture_Feature(imgOrig, imgLabeled, row, col, 15, 3, 3);
                                if (fh.UseMask14 && i == 13)
                                    law = (double[])CvipOp.Laws_Texture_Feature(imgOrig, imgLabeled, row, col, 15, 3, 4);
                                if (fh.UseMask15 && i == 14)
                                    law = (double[])CvipOp.Laws_Texture_Feature(imgOrig, imgLabeled, row, col, 15, 4, 3);

                            }
                        }
                        catch { throw new NotSupportedException(); }
                        for (int k = 0; k < 5; k++)
                        {
                            for (int k1 = 0; k1 < fh.Bands; k1++)
                            {
                                obj.m_law[i, k, k1] = law[k + (k1 * 5)].ToString("0.000000");

                            }
                        }

                    }
                        else
                        {
                            MessageBox.Show("mask image is missing please give mask image and perform operation", "CvipObject.Parse()",
                             MessageBoxButtons.OK, MessageBoxIcon.Warning);
                            return null;
                        }
                }
               
            }
                
           
            // spectral features
            if (fh.UseSpectral)
            {
                int rings = fh.SpectralRings;
                int sectors = fh.SpectralSectors;
                obj.m_strSpectralDC = new string[fh.Bands];
                obj.m_strSpectralRings = new string[fh.Bands, rings];
                obj.m_strSpectralSectors = new string[fh.Bands, sectors];
                double[] val = CvipOp.Spectral_Feature(imgOrig, imgLabeled, rings, sectors, row, col);
                for (int i = 0; i < fh.Bands; i++)
                {
                    obj.m_strSpectralDC[i] = val[3 + ((1 + rings + sectors) * i)].ToString("0.000000");
                    for (int j = 1; j <= rings; j++)
                        obj.m_strSpectralRings[i, j - 1] = val[3 + j + ((1 + rings + sectors) * i)].ToString("0.000000");
                    for (int j = 1; j <= sectors; j++)
                        obj.m_strSpectralSectors[i, j - 1] = val[3 + rings + j + ((1 + rings + sectors) * i)].ToString("0.000000");
                }
            }
            //Class Name
            obj.m_strClass = classname;
            return obj;
        }
        static public CvipObject Parse(FeatureHeader fh, string s)
        {
            string[] tokens = s.Split(new char[] { ' ' });
            if (tokens.Length < 3)
            {
                MessageBox.Show("Couldn't find object name.", "CvipObject.Parse()",
                    MessageBoxButtons.OK, MessageBoxIcon.Warning);
                return null;
            }
            int idx = 0;
            CvipObject obj = new CvipObject(tokens[idx++], fh);
            obj.m_strRow = tokens[idx++];
            obj.m_strCol = tokens[idx++];
            
            try
            {
                // Binary object features
                if (fh.UseArea)
                    obj.m_strArea = tokens[idx++];
                if (fh.UseCentroid)
                {
                    obj.m_strCentroidRow = tokens[idx++];
                    obj.m_strCentroidCol = tokens[idx++];
                }
                if (fh.UseOrientation)
                    obj.m_strOrientation = tokens[idx++];
                if (fh.UsePerimeter)
                    obj.m_strPerimeter = tokens[idx++];
                if (fh.UseEuler)
                    obj.m_strEuler = tokens[idx++];
                if (fh.UseProjections)
                {
                    int count = fh.ProjectionsHeight + fh.ProjectionsWidth;
                    obj.m_strProjections = new string[count];
                    for (int i = 0; i < count; i++)
                        obj.m_strProjections[i] = tokens[idx++];
                }
                if (fh.UseThinness)
                    obj.m_strThinness = tokens[idx++];
                if (fh.UseAspectRatio)
                    obj.m_strAspect = tokens[idx++];

                // RST-Invariant Moment-Based features
                for (int i = 0; i < 7; i++)
                {
                    if (fh.UseRst[i])
                    {
                        obj.m_strRst = new string[7];
                        for (int j = 0; j < 7; j++)
                        {
                            if (fh.UseRst[j])
                                obj.m_strRst[j] = tokens[idx++];
                        }
                        break;
                    }
                }
                // histogram feature
                for (int i = 0; i < 5; i++)
                {
                    if (fh.UseHist[i])
                    {
                        obj.m_strHist = new string[5, fh.Bands];
                        for (int j = 0; j < 5; j++)
                        {
                            if (fh.UseHist[j])
                            {
                                for (int k = 0; k < fh.Bands; k++)
                                    obj.m_strHist[j, k] = tokens[idx++];
                            }
                        }
                        break;
                    }
                }
                // texture features
                for (int i = 0; i < 5; i++)
                {
                    if (fh.UseTexture[i])
                    {
                        obj.m_strTexture = new string[5, 2];
                        for (int j = 0; j < 5; j++)
                        {
                            if (fh.UseTexture[j])
                            {
                                obj.m_strTexture[j, 0] = tokens[idx++];
                                obj.m_strTexture[j, 1] = tokens[idx++];
                            }
                        }
                        break;
                    }
                }
                //law texture
                for (int i = 0; i < 15; i++)
                {
                    if(i==0)
                    obj.m_law = new string[15, 5, fh.Bands];
                    if (fh.UseLaw[i])
                    {
                        
                        for (int j = 0; j < 5; j++)
                        {
                            for (int k = 0; k < fh.Bands; k++)
                                { obj.m_law[i,j, k] = tokens[idx++];
                                                               
                                }
                                 }
                        
                    }
                }
                // spectral features
                if (fh.UseSpectral)
                {
                    obj.m_strSpectralDC = new string[fh.Bands];
                    obj.m_strSpectralRings = new string[fh.Bands, fh.SpectralRings];
                    obj.m_strSpectralSectors = new string[fh.Bands, fh.SpectralSectors];
                    for (int i = 0; i < fh.Bands; i++)
                    {
                        obj.m_strSpectralDC[i] = tokens[idx++];
                        for (int j = 0; j < fh.SpectralRings; j++)
                            obj.m_strSpectralRings[i, j] = tokens[idx++];
                        for (int j = 0; j < fh.SpectralSectors; j++)
                            obj.m_strSpectralSectors[i, j] = tokens[idx++];
                    }
                }
                // Class Name
                if (tokens.Length > idx)
                    obj.m_strClass = tokens[idx];
            }
            catch (Exception e)
            {
                MessageBox.Show(obj.m_strName + ": Unhandled exception: " + e.Message,
                    "CvipObject.Parse()", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                return null;
            }
            return (obj);
        }
        public override string ToString()
        {
            StringBuilder bldr = new StringBuilder();
            bldr.Append(this.m_strName + " " + this.m_strRow + " " + this.m_strCol);

            // Binary object features
            if (this.m_hdrFeatures.UseArea)
                bldr.Append(" " + this.m_strArea);
            if (this.m_hdrFeatures.UseCentroid)
                bldr.Append(" " + this.m_strCentroidRow + " " + this.m_strCentroidCol);
            if (this.m_hdrFeatures.UseOrientation)
                bldr.Append(" " + this.m_strOrientation);
            if (this.m_hdrFeatures.UsePerimeter)
                bldr.Append(" " + this.m_strPerimeter);
            if (this.m_hdrFeatures.UseEuler)
                bldr.Append(" " + this.m_strEuler);
            if (this.m_hdrFeatures.UseProjections)
            {
                int count = this.m_hdrFeatures.ProjectionsHeight + this.m_hdrFeatures.ProjectionsWidth;
                for (int i = 0; i < count; i++)
                    bldr.Append(" " + this.m_strProjections[i]);
            }
            if (this.m_hdrFeatures.UseThinness)
                bldr.Append(" " + this.m_strThinness);
            if (this.m_hdrFeatures.UseAspectRatio)
                bldr.Append(" " + this.m_strAspect);

            // RST-Invariant Moment-Based features
            for (int i = 0; i < 7; i++)
            {
                if (this.m_hdrFeatures.UseRst[i])
                    bldr.Append(" " + this.m_strRst[i]);
            }
            // histogram feature
            for (int i = 0; i < 5; i++)
            {
                if (this.m_hdrFeatures.UseHist[i])
                {
                    for (int j = 0; j < this.m_hdrFeatures.Bands; j++)
                        bldr.Append(" " + this.m_strHist[i, j]);
                }
            }
            

            // texture features
            for (int i = 0; i < 5; i++)
            {
                if (this.m_hdrFeatures.UseTexture[i])
                {
                    bldr.Append(" " + this.m_strTexture[i, 0]);
                    bldr.Append(" " + this.m_strTexture[i, 1]);
                }
            }
            //law texture
            for (int i = 0; i < 15; i++)
            {
                if (this.m_hdrFeatures.UseLaw[i])
                {
                    for (int j = 0; j < 5; j++)
                    {
                        for (int k = 0; k < this.m_hdrFeatures.Bands; k++)
                        {
                            bldr.Append(" " + this.m_law[i, j, k]);

                        }
                    }
                }
            }
            // spectral features
            if (this.m_hdrFeatures.UseSpectral)
            {
                for (int i = 0; i < this.m_hdrFeatures.Bands; i++)
                {
                    bldr.Append(" " + this.m_strSpectralDC[i]);
                    for (int j = 0; j < this.m_hdrFeatures.SpectralRings; j++)
                        bldr.Append(" " + this.m_strSpectralRings[i, j]);
                    for (int j = 0; j < this.m_hdrFeatures.SpectralSectors; j++)
                        bldr.Append(" " + this.m_strSpectralSectors[i, j]);
                }
            }
            // Class Name
            bldr.Append(" " + this.m_strClass);
            return bldr.ToString();
        }

        public string Name { get { return this.m_strName; } }
        public string Col { get { return this.m_strCol; } }
        public string Row { get { return this.m_strRow; } }
        //public string Band { get { return this.m_strBand; } }
        public string Area { get { return this.m_strArea; } }
        public string AspectRatio { get { return this.m_strAspect; } }
        public string CentroidCol { get { return this.m_strCentroidCol; } }
        public string CentroidRow { get { return this.m_strCentroidRow; } }
        public string ClassName { get { return this.m_strClass; } }
        public string Euler { get { return this.m_strEuler; } }
        public string[,] Hist { get { return this.m_strHist; } }
        public string Orientation { get { return this.m_strOrientation; } }
        public string Perimeter { get { return this.m_strPerimeter; } }
        public string[] Projections { get { return this.m_strProjections; } }
        public string[] Rst { get { return this.m_strRst; } }
        public string[] SpectralDC { get { return this.m_strSpectralDC; } }
        public string[,] SpectralRings { get { return this.m_strSpectralRings; } }
        public string[,] SpectralSectors { get { return this.m_strSpectralSectors; } }
        public string[,] Texture { get { return this.m_strTexture; } }
        public string Thinness { get { return this.m_strThinness; } }
        public string[,,] law { get { return this.m_law; } }
        public FeatureHeader FeatureHeader { get { return this.m_hdrFeatures; } }
    }
}
