/*''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' ======================================================================
' Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
' ======================================================================
'
'             File Name: FeatureFile.cs
'           Description: Contains the controls and code
'                        for Analysis->FeatureFile class
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
using System.Collections;
using System.Collections.Generic;
using System.Text;
using System.IO;
using System.Windows.Forms;

namespace CVIPGUI.Analysis
{
    public class FeatureFile : ICollection<CvipObject>
    {
        FeatureHeader m_hdrFeatures = null;
        List<CvipObject> m_lstObjects = new List<CvipObject>();
        bool LTFAIL=true;
        public FeatureFile()
        {
        }
        public FeatureFile(FeatureHeader fh)
        {
            this.m_hdrFeatures = fh;
        }
        public void Add(CvipObject obj)
        {
            if (this.m_hdrFeatures == null)
                this.m_hdrFeatures = obj.FeatureHeader;
            if (obj == null) { LTFAIL = false; return; }
            if (!this.m_hdrFeatures.Equals(obj.FeatureHeader))
            {
                MessageBox.Show("Feature Selection has been changed. Please choose another feature file.",
                    "FeatureFile.Add()", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                return;
            }
            this.m_lstObjects.Add(obj);
        }
        public bool Add(int imgOrig, int imgLabeled, int row, int col, string name,string seg, string classname, FeatureHeader fh)
        {
            if (this.m_lstObjects.Count == 0)
                this.m_hdrFeatures = new FeatureHeader(fh);
            if (!this.m_hdrFeatures.Equals(fh))
            {
                MessageBox.Show("Feature Selection has been changed. Please choose another feature file.",
                    "FeatureFile.Add()", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                return false;
            }
            int bands = CvipOp.GetNoOfBands_Image(imgOrig);
            if (this.m_hdrFeatures.Bands == -1)
                this.m_hdrFeatures.Bands = bands;
            if (this.m_hdrFeatures.Bands != bands)
            {
                MessageBox.Show("Number of bands has changed. Please choose another feature file.",
                    "FeatureFile.Add()", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                return false;
            }
            Add(CvipObject.Create(name,seg, imgOrig, imgLabeled, row, col, m_hdrFeatures, classname));
            if (LTFAIL == false) { return false; }
            return true;
        }
        public void Clear()
        {
            this.m_lstObjects.Clear();
            this.m_hdrFeatures = null;
        }
        public bool Contains(CvipObject obj)
        {
            return this.m_lstObjects.Contains(obj);
        }
        public void CopyTo(CvipObject[] array, int arrayIndex)
        {
            this.m_lstObjects.CopyTo(array, arrayIndex);
        }
        IEnumerator IEnumerable.GetEnumerator()
        {
            return this.GetEnumerator();
        }
        public IEnumerator<CvipObject> GetEnumerator()
        {
            return this.m_lstObjects.GetEnumerator();
        }
        static public FeatureFile Open(string fname)
        {
            if (!File.Exists(fname))
            {
                MessageBox.Show(fname + " does not exist.", "FeatureFile.Open()",
                    MessageBoxButtons.OK, MessageBoxIcon.Warning);
                return null;
            }
            FeatureFile ff = null;
            using (StreamReader sr = File.OpenText(fname))
            {
                FeatureHeader fh = FeatureHeader.Parse(sr);
                if (fh != null)
                {
                    ff = new FeatureFile(fh);
                    string s;
                    while ((s = sr.ReadLine()) != null)
                    {
                        if (!string.IsNullOrEmpty(s))
                            ff.Add(CvipObject.Parse(fh, s));
                    }
                }
            }
            return ff;
        }
        public bool Remove(CvipObject obj)
        {
            bool success = this.m_lstObjects.Remove(obj);
            if (this.m_lstObjects.Count == 0)
                this.m_hdrFeatures = null;
            return success;
        }
        public override string ToString()
        {
            StringBuilder bldr = new StringBuilder();
            if (this.m_hdrFeatures != null)
            {
                bldr.Append(this.m_hdrFeatures.ToString());
                foreach (CvipObject obj in this.m_lstObjects)
                {
                    bldr.AppendLine(obj.ToString());
                    bldr.AppendLine();
                }
            }
            return bldr.ToString();
        }
        public void Write(string fname)
        {
            if (string.IsNullOrEmpty(fname))
            {
                MessageBox.Show("FileName is Required.", "FeatureFile.Write()",
                    MessageBoxButtons.OK, MessageBoxIcon.Warning);
                return;
            }
            using (StreamWriter sw = File.CreateText(fname))
            {
                sw.Write(this.ToString());
            }
        }
        public void WriteLooTestSet(string fname, int idxTest)
        {
            if (string.IsNullOrEmpty(fname))
            {
                MessageBox.Show("FileName is Required.", "FeatureFile.WriteLooTestSet()",
                    MessageBoxButtons.OK, MessageBoxIcon.Warning);
                return;
            }
            if ((idxTest < 0) || (idxTest >= this.m_lstObjects.Count))
            {
                MessageBox.Show("Test object index is out of range.", "FeatureFile.WriteLooTestSet()",
                    MessageBoxButtons.OK, MessageBoxIcon.Warning);
                return;
            }
            if (this.m_hdrFeatures != null)
            {
                using (StreamWriter sw = File.CreateText(fname))
                {
                    sw.Write(this.m_hdrFeatures.ToString());
                    sw.WriteLine(this.m_lstObjects[idxTest].ToString());
                    sw.WriteLine();
                }
            }
        }
        public void WriteLooTrainingSet(string fname, int idxTest)
        {
            if (string.IsNullOrEmpty(fname))
            {
                MessageBox.Show("FileName is Required.", "FeatureFile.WriteLooTrainingSet()",
                    MessageBoxButtons.OK, MessageBoxIcon.Warning);
                return;
            }
            if ((idxTest < 0) || (idxTest >= this.m_lstObjects.Count))
            {
                MessageBox.Show("Test object index is out of range.", "FeatureFile.WriteLooTrainingSet()",
                    MessageBoxButtons.OK, MessageBoxIcon.Warning);
                return;
            }
            if (this.m_hdrFeatures != null)
            {
                using (StreamWriter sw = File.CreateText(fname))
                {
                    sw.Write(this.m_hdrFeatures.ToString());
                    for (int i = 0; i < this.m_lstObjects.Count; i++)
                    {
                        if (i != idxTest)
                        {
                            sw.WriteLine(this.m_lstObjects[i].ToString());
                            sw.WriteLine();
                        }
                    }
                }
            }
        }

        public CvipObject this[int idx]
        {
            get
            {
                CvipObject obj = null;
                if ((idx >= 0) && (idx < this.m_lstObjects.Count))
                    obj = this.m_lstObjects[idx];
                return obj;
            }
        }
        public int Bands
        {
            get
            {
                int bands = -1;
                if (this.m_hdrFeatures != null)
                    bands = this.m_hdrFeatures.Bands;
                return bands;
            }
        }
        public bool IsReadOnly { get { return false; } }
        public int Count { get { return this.m_lstObjects.Count; } }
        public FeatureHeader FeatureHeader { get { return this.m_hdrFeatures; } }
    }
}
