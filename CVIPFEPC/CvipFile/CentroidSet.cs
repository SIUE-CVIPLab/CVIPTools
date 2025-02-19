/*''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' ======================================================================
' Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
' ======================================================================
'
'             File Name: CentroidSet.cs
'           Description: Contains the code for
'                        for CentroidSet class
'         Related Files: FeatureFile.cs
'                        FeatureHeader.cs
'                        CvipObject.cs
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
using System.IO;
using System.Text;

namespace CVIPFEPC.CvipFile
{
    public class CentroidSet : FeatureFile
    {
        protected string[] sClassList = null;

        public CentroidSet(FeatureFileSet ffs)
            : base(ffs) { }
        public override void Add(CvipObject obj)
        {
            Add(obj.ClassName, obj);
        }
        public override bool Contains(CvipObject obj)
        {
            return ContainsKey(obj.ClassName);
        }
        public override bool Remove(CvipObject obj)
        {
            return RemoveKey(obj.ClassName);
        }
        public void ResetVectors()
        {
            for (int i = 0; i < this.lstObjects.Count; i++)
                this.lstObjects.Values[i].ResetValues();
            this.sClassList = null;
        }

        public override int Count { get { return this.ClassList.Length; } }
        public override CvipObject this[int idx]
        {
            get
            {
                CvipObject obj = null;
                if ((idx >= 0) && (idx < this.ClassList.Length))
                {
                    string classname = this.ClassList[idx];
                    if (!this.ContainsKey(classname))
                        this.Add(new CentroidObject(this, classname));
                    idx = this.lstObjects.IndexOfKey(classname);
                    obj = this.lstObjects.Values[idx];
                }
                return obj;
            }
        }
        protected string[] ClassList
        {
            get
            {
                string[] classes = null;
                if (this.TrainingSet.Count > 0)
                {
                    if (this.sClassList == null)
                    {
                        List<string> lstClasses = new List<string>();
                        for (int i = 0; i < this.TrainingSet.Count; i++)
                        {
                            string classname = this.TrainingSet[i].ClassName;
                            if (string.IsNullOrEmpty(classname))
                                continue;
                            if (!lstClasses.Contains(classname))
                                lstClasses.Add(classname);
                        }
                        if (lstClasses.Count > 0)
                        {
                            lstClasses.Sort();
                            this.sClassList = lstClasses.ToArray();
                        }
                    }
                    classes = this.sClassList;
                }
                return classes;
            }
        }
    }
}
