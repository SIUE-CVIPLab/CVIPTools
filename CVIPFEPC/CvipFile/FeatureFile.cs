/*''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' ======================================================================
' Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
' ======================================================================
'
'             File Name: FeatureFile.cs
'           Description: Contains the code for
'                        for FeatureFile class
'         Related Files: FeatureHeader.cs
'                        CvipObject.cs
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
using System.Collections;
using System.Collections.Generic;
using System.IO;
using System.Text;
using System.Threading.Tasks;

namespace CVIPFEPC.CvipFile
{
    public class FeatureFileSet : IEnumerable<FeatureFile>
    {
        protected Classifier classifier = null;
        protected FeatureFile[] ffSet = new FeatureFile[3];
        protected FeatureHeader hdrFeatures = null;
        protected int idxCombinatoricTest = -1;
        protected int idxLooTest = -1;
        protected int idxWorkingDir = -1;
        protected string sResultFileSuffix = null;
        protected string sTmpResultFile = null;
        protected string sTmpTrainingSetFile = null;
        protected string sTmpTestSetFile = null;
        protected string sWorkingDir = null;

        protected Dictionary<Normalization, FeatureVector[][]> trainingFeatureVectorsByNorm = new Dictionary<Normalization, FeatureVector[][]>();
        protected Dictionary<Normalization, FeatureVector[][]> centroidFeatureVectorsByNorm = new Dictionary<Normalization, FeatureVector[][]>();
        protected Dictionary<Normalization, FeatureVector[][]> trainingLLOFeatureVectorsByNorm = new Dictionary<Normalization, FeatureVector[][]>();
        protected Dictionary<Normalization, FeatureVector[][]> centroidLLOFeatureVectorsByNorm = new Dictionary<Normalization, FeatureVector[][]>();

        public void ResetFeatureVectors()
        {
            trainingFeatureVectorsByNorm = new Dictionary<Normalization, FeatureVector[][]>();
            centroidFeatureVectorsByNorm = new Dictionary<Normalization, FeatureVector[][]>();
            trainingLLOFeatureVectorsByNorm = new Dictionary<Normalization, FeatureVector[][]>();
            centroidLLOFeatureVectorsByNorm = new Dictionary<Normalization, FeatureVector[][]>();
        }

        FeatureVector[] tempfeatureVetors = null;

        public FeatureFileSet(bool bLeave1Out)
        {
            this.ffSet[0] = new FeatureFile(this);
            if (!bLeave1Out)
                this.ffSet[1] = new FeatureFile(this);
        }
        public void Add(CvipObject obj)
        {
            this.TrainingSet.Add(obj);
        }
        public void Clear()
        {
            foreach (FeatureFile ff in this.ffSet)
            {
                if (ff == null) continue;
                ff.Clear();

            }
        }
        IEnumerator IEnumerable.GetEnumerator()
        {
            return this.GetEnumerator();
        }
        public IEnumerator<FeatureFile> GetEnumerator()
        {
            return ((IEnumerable<FeatureFile>)this.ffSet).GetEnumerator();
        }
        protected string AppendToFileName(string fname, string text)
        {
            if (!string.IsNullOrEmpty(fname))
            {
                FileInfo fi = new FileInfo(fname);
                int lenExt = fi.Extension.Length;
                int lenName = fi.FullName.Length;
                fname = fi.FullName.Substring(0, lenName - lenExt) + text + ".txt";
            }
            return fname;
        }
        protected string GetFullFileName(string fname)
        {
            string fullname = null;
            if (!string.IsNullOrEmpty(this.WorkingDirectory))
                fullname = this.WorkingDirectory + @"\" + fname + this.idxWorkingDir + ".txt";
            return fullname;
        }
        public string NormalizedFileName(string fname, Normalization norm)
        {
            if (norm != Normalization.None)
                fname = AppendToFileName(fname, "-" + this.Classifier.NormalizationAbbreviation[norm]);
            return fname;
        }
        public void BeginCombinatoricTest()
        {
            this.Classifier.Reset();
            this.TmpResultFile = Path.Combine(Path.GetTempPath(), Path.GetRandomFileName());
            this.TmpTrainingSetFile = Path.Combine(Path.GetTempPath(), Path.GetRandomFileName());
            this.TmpTestSetFile = Path.Combine(Path.GetTempPath(), Path.GetRandomFileName());
        }
        public void ResetCombinatoricIndex()
        {
            this.FeatureHeader.Reset();
            this.idxCombinatoricTest = 1;
            this.sResultFileSuffix = null;
        }
        public bool IncrementCombinatoricIndex()
        {
            this.idxCombinatoricTest++;
            return this.FeatureHeader.Increment();
        }
        public void EndCombinatoricTest()
        {
            this.idxCombinatoricTest = -1;
            this.sResultFileSuffix = null;
            if (File.Exists(this.TmpResultFile))
            {
                try { File.Delete(this.TmpResultFile); }
                catch { }
            }
            if (File.Exists(this.TmpTrainingSetFile))
            {
                try { File.Delete(this.TmpTrainingSetFile); }
                catch { }
            }
            if (File.Exists(this.TmpTestSetFile))
            {
                try { File.Delete(this.TmpTestSetFile); }
                catch { }
            }
            this.TmpResultFile = null;
            this.TmpTrainingSetFile = null;
            this.TmpTestSetFile = null;
        }
        public void WriteFeatureFileSet(MultiStepJobEventArgs e)
        {
            this.FeatureHeader.AllOn();
            if (this.Normalization != Normalization.None)
                WriteFeatureFileSet(Normalization.None, e);
            WriteFeatureFileSet(this.Normalization, e);
        }
        protected void WriteFeatureFileSet(Normalization norm, MultiStepJobEventArgs e)
        {
            if (this.UsingTrainingTest)
                WriteTrainingTestFileSet(norm, e);
            else
                WriteLeaveOneOutFileSet(norm, e);
        }
        protected void WriteLeaveOneOutFileSet(Normalization norm, MultiStepJobEventArgs e)
        {
            int count = this.TrainingSet.Count;
            if (this.CentroidSet != null)
                count += this.TrainingSet.Count * this.CentroidSet.Count;
            else
            {
                if (norm != Normalization.None)
                    count += this.TrainingSet.Count * (this.TrainingSet.Count - 1);
            }
            MultiStepJobEventArgs args = new MultiStepJobEventArgs(e.WorkerThread);
            e.NewJob(count, RunTestState.CreateFeatureFiles);
            e.ReportProgress();

            if (norm == Normalization.None)
            {
                if (this.tempfeatureVetors == null)
                {
                    this.tempfeatureVetors = this.TrainingSet.FeatureVectors.GetFeatureVectors(args);
                }
                FeatureVector[] fv1D = this.tempfeatureVetors;
                if (e.CancellationRequested || args.WorkCancelled)
                {
                    e.WorkCancelled = true;
                    return;
                }
                this.TrainingSet.WriteToFile(this.LooTrainingSetFile, fv1D, e);
                if ((e.ErrorMsg != null) || e.WorkCancelled)
                    return;
            }

            if ((norm != Normalization.None) || (this.CentroidSet != null))
            {
                FeatureVector[][] fv2D = null;
                if (this.CentroidSet != null)
                {
                    // Check if the dictionary already contains the FeatureVector for the given normalization
                    if (!this.centroidLLOFeatureVectorsByNorm.TryGetValue(norm, out fv2D))
                    {
                        // If not, generate it and store it in the dictionary
                        fv2D = this.CentroidSet.FeatureVectors.GetLeaveOneOutVectors(norm, args);
                        if (e.CancellationRequested || args.WorkCancelled)
                        {
                            e.WorkCancelled = true;
                            return;
                        }
                        this.centroidLLOFeatureVectorsByNorm[norm] = fv2D;
                    }

                    for (this.idxLooTest = 0; this.idxLooTest < this.TrainingSet.Count; this.idxLooTest++)
                    {
                        this.CentroidSet.WriteToFile(NormalizedFileName(this.CentroidSetFile, norm), fv2D[this.idxLooTest], e);
                        if ((e.ErrorMsg != null) || e.WorkCancelled)
                            return;
                    }
                }
                else
                {
                    // Check if the dictionary already contains the FeatureVector for the given normalization
                    if (!this.trainingLLOFeatureVectorsByNorm.TryGetValue(norm, out fv2D))
                    {
                        // If not, generate it and store it in the dictionary
                        fv2D = this.TrainingSet.FeatureVectors.GetLeaveOneOutVectors(norm, args);
                        if (e.CancellationRequested || args.WorkCancelled)
                        {
                            e.WorkCancelled = true;
                            return;
                        }
                        this.trainingLLOFeatureVectorsByNorm[norm] = fv2D;
                    }

                    for (this.idxLooTest = 0; this.idxLooTest < this.TrainingSet.Count; this.idxLooTest++)
                    {
                        this.TrainingSet.WriteLooFile(NormalizedFileName(this.TrainingSetFile, norm), fv2D[this.idxLooTest], true, this.idxLooTest, e);
                        if ((e.ErrorMsg != null) || e.WorkCancelled)
                            return;
                    }
                }

                if (norm != Normalization.None)
                {
                    this.TrainingSet.WriteToFile(NormalizedFileName(this.TestSetFile, norm), fv2D[this.idxLooTest], e);
                    if ((e.ErrorMsg != null) || e.WorkCancelled)
                        return;
                }
                this.idxLooTest = -1;
            }
        }

        protected void WriteTrainingTestFileSet(Normalization norm, MultiStepJobEventArgs e)
        {
            FeatureVector[][] fv;

            // Check if the dictionary already contains the FeatureVector for the given normalization
            if (!this.trainingFeatureVectorsByNorm.TryGetValue(norm, out fv))
            {
                // If not, generate it and store it in the dictionary
                fv = this.TrainingSet.FeatureVectors.GetTrainingTestVectors(norm, e);
                if (e.CancellationRequested || e.WorkCancelled)
                {
                    e.WorkCancelled = true;
                    return;
                }
                this.trainingFeatureVectorsByNorm[norm] = fv;
            }

            int count = 0;
            for (int i = 0; i < 3; i++)
            {
                if (fv[i] == null)
                    continue;
                count += fv[i].Length;
                // if (FeatureHeader.UseCombTex)
                //count = count * ((FeatureHeader.TextureDistanceUpper - FeatureHeader.TextureDistanceLower) / FeatureHeader.TextureDistanceIncrement) + 1;
            }

            e.NewJob(count, RunTestState.CreateFeatureFiles);
            e.ReportProgress();
            for (int i = 0; i < 3; i++)
            {
                if (fv[i] == null)
                    continue;
                this[i].WriteToFile(NormalizedFileName(this.FileNames[i], norm), fv[i], e);
                if ((e.ErrorMsg != null) || e.WorkCancelled)
                    return;
            }
        }
        public void WriteTmpLeaveOneOutFiles(int idxTest, MultiStepJobEventArgs e)
        {
            FeatureVector[] fvTrainingSet = null;
            FeatureVector[] fvTestSet = null;

            if (this.Normalization == Normalization.None)
            {
                if (this.tempfeatureVetors == null)
                {
                    this.tempfeatureVetors = this.TrainingSet.FeatureVectors.GetFeatureVectors(e);
                }
                fvTrainingSet = fvTestSet = this.tempfeatureVetors;
            }
            else
            {
                // Check if the dictionary already contains the FeatureVector for the given normalization
                if (!this.trainingLLOFeatureVectorsByNorm.TryGetValue(this.Normalization, out FeatureVector[][] trainingVectors))
                {
                    // If not, generate it and store it in the dictionary
                    trainingVectors = this.TrainingSet.FeatureVectors.GetLeaveOneOutVectors(this.Normalization, e);
                    if (e.CancellationRequested || e.WorkCancelled)
                    {
                        e.WorkCancelled = true;
                        return;
                    }
                    this.trainingLLOFeatureVectorsByNorm[this.Normalization] = trainingVectors;
                }
                fvTrainingSet = fvTestSet = trainingVectors[idxTest];
            }

            if (e.CancellationRequested || e.WorkCancelled)
            {
                e.WorkCancelled = true;
                return;
            }

            if (this.CentroidSet == null)
            {
                e.NewJob(this.TrainingSet.Count, RunTestState.CreateFeatureFiles);
                e.ReportProgress();
                this.TrainingSet.WriteLooFile(this.TmpTrainingSetFile, fvTrainingSet, true, idxTest, e);
                if ((e.ErrorMsg != null) || e.WorkCancelled)
                    return;
            }
            else
            {
                // Check if the dictionary already contains the FeatureVector for the given normalization
                if (!this.centroidLLOFeatureVectorsByNorm.TryGetValue(this.Normalization, out FeatureVector[][] centroidVectors))
                {
                    // If not, generate it and store it in the dictionary
                    centroidVectors = this.CentroidSet.FeatureVectors.GetLeaveOneOutVectors(this.Normalization, e);
                    if (e.CancellationRequested || e.WorkCancelled)
                    {
                        e.WorkCancelled = true;
                        return;
                    }
                    this.centroidLLOFeatureVectorsByNorm[this.Normalization] = centroidVectors;
                }

                e.NewJob(this.CentroidSet.Count + 1, RunTestState.CreateFeatureFiles);
                e.ReportProgress();
                this.CentroidSet.WriteToFile(this.TmpTrainingSetFile, centroidVectors[idxTest], e);
                if ((e.ErrorMsg != null) || e.WorkCancelled)
                    return;

                if (this.Normalization != Normalization.None)
                    fvTestSet = centroidVectors[this.TrainingSet.Count];
            }

            this.TrainingSet.WriteLooFile(this.TmpTestSetFile, fvTestSet, false, idxTest, e);
        }
        public void WriteTmpTrainingTestFiles(MultiStepJobEventArgs e)
        {
            FeatureVector[][] fv;

            // Check if the dictionary already contains the FeatureVector for the given normalization
            if (!this.trainingFeatureVectorsByNorm.TryGetValue(this.Normalization, out fv))
            {
                // If not, generate it and store it in the dictionary
                fv = this.TrainingSet.FeatureVectors.GetTrainingTestVectors(this.Normalization, e);
                if (e.CancellationRequested || e.WorkCancelled)
                {
                    e.WorkCancelled = true;
                    return;
                }
                this.trainingFeatureVectorsByNorm[this.Normalization] = fv;
            }

            int idxTraining = (this.CentroidSet != null) ? 2 : 0;
            e.NewJob(fv[idxTraining].Length + fv[1].Length, RunTestState.CreateFeatureFiles);
            e.ReportProgress();

            this[idxTraining].WriteToFile(this.TmpTrainingSetFile, fv[idxTraining], e);
            if ((e.ErrorMsg != null) || e.WorkCancelled)
                return;
            this[1].WriteToFile(this.TmpTestSetFile, fv[1], e);
        }

        public Algorithm Algorithm
        {
            get { return (this.classifier != null) ? this.classifier.Algorithm : Algorithm.NearestNeighbor; }
        }
        public Distance Distance
        {
            get { return (this.classifier != null) ? this.classifier.Distance : Distance.Euclidean; }
        }
        public Normalization Normalization
        {
            get { return (this.classifier != null) ? this.classifier.Normalization : Normalization.None; }
        }
        public Classifier Classifier
        {
            get { return this.classifier; }
            set
            {
                this.classifier = value;
                if (value != null)
                    value.FeatureHeader = this.FeatureHeader;
            }
        }
        public FeatureHeader FeatureHeader
        {
            get { return this.hdrFeatures; }
            set
            {
                this.hdrFeatures = value;
                if (this.Classifier != null)
                    this.Classifier.FeatureHeader = value;
                foreach (ImageObject obj in this.TrainingSet)
                    obj.FeatureHeader = value;
                if (this.TestSet != null)
                {
                    foreach (ImageObject obj in this.TestSet)
                        obj.FeatureHeader = value;
                }
            }
        }
        public FeatureFile TrainingSet { get { return this[0]; } }
        public FeatureFile TestSet { get { return this[1]; } }
        public CentroidSet CentroidSet { get { return this[2] as CentroidSet; } }
        public FeatureFile this[int idx]
        {
            get
            {
                FeatureFile ff = null;
                switch (idx)
                {
                    case 0:
                    case 1:
                        ff = this.ffSet[idx];
                        break;
                    case 2:
                        if (this.Algorithm == Algorithm.NearestCentroid)
                        {
                            if (this.ffSet[2] == null)
                                this.ffSet[2] = new CentroidSet(this);
                            ff = this.ffSet[2];
                        }
                        break;
                }
                return ff;
            }
        }
        public string[] FileNames
        {
            get { return new string[] { this.TrainingSetFile, this.TestSetFile, this.CentroidSetFile }; }
        }
        public string CentroidSetFile
        {
            get { return AppendToFileName(this.TrainingSetFile, "-centroid"); }
        }
        public string TrainingSetFile
        {
            get
            {
                string fname = GetFullFileName("TrainSet");
                if (this.idxLooTest >= 0)
                    fname = AppendToFileName(fname, "." + (this.idxLooTest + 1).ToString());
                return fname;
            }
        }
        public string ResultsFile
        {
            get
            {
                string fname = GetFullFileName("Results"), suffix = null;
                if (this.idxCombinatoricTest >= 0)
                    suffix = "." + this.idxCombinatoricTest;
                suffix += this.ResultFileSuffix;
                return AppendToFileName(fname, suffix);
            }
        }
        protected string ResultFileSuffix
        {
            get
            {
                if (this.sResultFileSuffix == null)
                {
                    this.sResultFileSuffix = "-" + this.Classifier.AlgorithmAbbreviation[this.Algorithm] +
                                                        "-" + this.Classifier.DistanceAbbreviation[this.Distance] +
                                                        "-" + this.Classifier.NormalizationAbbreviation[this.Normalization];
                }
                return this.sResultFileSuffix;
            }
        }
        public string TmpResultFile
        {
            get { return this.sTmpResultFile; }
            set { this.sTmpResultFile = value; }
        }
        public string TmpTrainingSetFile
        {
            get { return this.sTmpTrainingSetFile; }
            set { this.sTmpTrainingSetFile = value; }
        }
        public string TmpTestSetFile
        {
            get { return this.sTmpTestSetFile; }
            set { this.sTmpTestSetFile = value; }
        }
        public string WorkingDirectory
        {
            get { return this.sWorkingDir; }
            set
            {
                this.idxWorkingDir = -1;
                this.sWorkingDir = value;
                if (!string.IsNullOrEmpty(value))
                {
                    int idx = value.Length - 1;
                    while ((idx >= 0) && char.IsDigit(value[idx])) idx--;
                    if (idx >= 0) this.idxWorkingDir = int.Parse(value.Substring(idx + 1));
                }
            }
        }
        public bool UsingLeaveOneOut { get { return this.TestSet == null; } }
        public bool UsingTrainingTest { get { return this.TestSet != null; } }
        public int CombinatoricTestIndex { get { return this.idxCombinatoricTest; } }
        public string LooTrainingSetFile { get { return GetFullFileName("FeatureFile"); } }
        public string TestSetFile { get { return GetFullFileName("TestSet"); } }
    }
    public class FeatureFile : ICollection<CvipObject>
    {
        protected FeatureFileSet ffsOwner = null;
        protected FeatureVectorCollection collectionVectors = null;
        protected SortedList<string, CvipObject> lstObjects = new SortedList<string, CvipObject>();

        public FeatureFile(FeatureFileSet ffs)
        {
            this.ffsOwner = ffs;
            this.collectionVectors = new FeatureVectorCollection(this);
        }
        public virtual void Add(CvipObject obj)
        {
            Add(obj.Name, obj);
        }
        protected void Add(string key, CvipObject obj)
        {
            if (!string.IsNullOrEmpty(key))
            {
                obj.FeatureFile = this;
                this.lstObjects.Add(key, obj);
                this.ClearVectorCache();
            }
        }
        public void Clear()
        {
            this.lstObjects.Clear();
            this.ClearVectorCache();






        }
        public void ClearVectorCache()
        {
            if (!this.IsCentroidSet)
            {
                foreach (FeatureFile ff in this.ffsOwner)
                {
                    if (ff == null) continue;
                    ff.FeatureVectors.Clear();


                }
            }
        }
        public virtual bool Contains(CvipObject obj)
        {
            return ContainsKey(obj.Name);
        }
        protected bool ContainsKey(string key)
        {
            bool contains = false;
            if (!string.IsNullOrEmpty(key))
                contains = this.lstObjects.ContainsKey(key);
            return contains;
        }
        public void CopyTo(CvipObject[] dest, int idx)
        {
            this.lstObjects.Values.CopyTo(dest, idx);
        }
        IEnumerator IEnumerable.GetEnumerator()
        {
            return this.GetEnumerator();
        }
        public IEnumerator<CvipObject> GetEnumerator()
        {
            return this.lstObjects.Values.GetEnumerator();
        }
        public virtual bool Remove(CvipObject obj)
        {
            return RemoveKey(obj.Name);
        }
        protected bool RemoveKey(string key)
        {
            bool success = false;
            if (!string.IsNullOrEmpty(key) && this.lstObjects.ContainsKey(key))
            {
                success = this.lstObjects.Remove(key);
                this.ClearVectorCache();
            }
            return success;
        }
        public void WriteToFile(string fname, FeatureVector[] featurevalues, MultiStepJobEventArgs e)
        {
            if ((featurevalues == null) || (this.FeatureHeader == null) || string.IsNullOrEmpty(fname))
            {
                if (featurevalues == null)
                    e.ErrorMsg = "FeatureFile.WriteToFile(): FeatureVectors not available.";
                if (this.FeatureHeader == null)
                    e.ErrorMsg = "FeatureFile.WriteToFile(): FeatureHeader not set.";
                if (string.IsNullOrEmpty(fname))
                    e.ErrorMsg = "FeatureFile.WriteToFile(): FileName not set.";
                return;
            }
            FileInfo fi = new FileInfo(fname);
            if (!Directory.Exists(fi.DirectoryName))
                Directory.CreateDirectory(fi.DirectoryName);
            using (StreamWriter sw = File.CreateText(fi.FullName))
            {
                sw.AutoFlush = true;
                sw.Write(this.FeatureHeader.ToString());
                for (int i = 0; i < this.Count; i++)
                {
                    sw.WriteLine(this[i].ToString(featurevalues[i]));
                    sw.WriteLine();
                    if (e.CancellationRequested)
                    {
                        e.WorkCancelled = true;
                        return;
                    }
                    e.StepComplete();
                    e.ReportProgress();
                }
            }
        }
        public void WriteLooFile(string fname, FeatureVector[] featurevalues, bool bWriteTrainingSet, int idxTest, MultiStepJobEventArgs e)
        {
            if ((featurevalues == null) || (this.FeatureHeader == null) || string.IsNullOrEmpty(fname))
            {
                if (featurevalues == null)
                    e.ErrorMsg = "FeatureFile.WriteLooFile(): FeatureVectors not available.";
                if (this.FeatureHeader == null)
                    e.ErrorMsg = "FeatureFile.WriteLooFile(): FeatureHeader not set.";
                if (string.IsNullOrEmpty(fname))
                    e.ErrorMsg = "FeatureFile.WriteLooFile(): FileName not set.";
                return;
            }
            FileInfo fi = new FileInfo(fname);
            if (!Directory.Exists(fi.DirectoryName))
                Directory.CreateDirectory(fi.DirectoryName);
            using (StreamWriter sw = File.CreateText(fi.FullName))
            {
                sw.AutoFlush = true;
                sw.Write(this.FeatureHeader.ToString());
                if (bWriteTrainingSet)
                {
                    for (int i = 0; i < this.Count; i++)
                    {
                        if (i == idxTest) continue;
                        sw.WriteLine(this[i].ToString(featurevalues[i]));
                        sw.WriteLine();
                        if (e.CancellationRequested)
                        {
                            e.WorkCancelled = true;
                            return;
                        }
                        e.StepComplete();
                        e.ReportProgress();
                    }
                }
                else
                {
                    sw.WriteLine(this[idxTest].ToString(featurevalues[idxTest]));
                    sw.WriteLine();
                    e.StepComplete();
                    e.ReportProgress();
                }
            }
        }
        public class FeatureVectorCollection
        {
            private FeatureFile ffOwner = null;
            private FeatureVector[] fvNonNormalized = null;
            private Dictionary<Normalization, FeatureVector[]> dictionaryTrainingTest = new Dictionary<Normalization, FeatureVector[]>();
            private Dictionary<Normalization, FeatureVector[][]> dictionaryLeave1Out = new Dictionary<Normalization, FeatureVector[][]>();

            public FeatureVectorCollection(FeatureFile ff) { this.ffOwner = ff; }
            public void Clear()
            {
                FeatureHeader fd = new FeatureHeader();
                if (this.IsCentroidSet)
                    this.CentroidSet.ResetVectors();

                this.dictionaryLeave1Out.Clear();
                this.dictionaryTrainingTest.Clear();




            }
            public void ClearAll()
            {
                if (this.IsCentroidSet)
                    this.CentroidSet.ResetVectors();
                this.dictionaryLeave1Out.Clear();
                this.dictionaryTrainingTest.Clear();
                this.fvNonNormalized = null;


            }
            public FeatureVector[] GetFeatureVectors(MultiStepJobEventArgs e)
            {
                RefreshNonNormalizedVectors(e);
                if (e.WorkCancelled)
                    return null;
                return this.fvNonNormalized;
            }
            public FeatureVector[][] GetLeaveOneOutVectors(Normalization norm, MultiStepJobEventArgs e)
            {
                FeatureVector[][] vectors = null;
                FeatureVector[][] vectorsTest = null;
                if ((this.TrainingSet.Count > 0) && (this.FeatureHeader != null))
                {
                    RefreshNonNormalizedVectors(e);
                    if (e.WorkCancelled)
                        return null;

                    if (this.CentroidSet == null)
                    {
                        if (norm == Normalization.None)
                        {
                            vectors = new FeatureVector[3][];
                            vectors[0] = this.TrainingSet.FeatureVectors.fvNonNormalized;
                        }
                        else
                        {
                            if (!this.TrainingSet.FeatureVectors.dictionaryLeave1Out.ContainsKey(norm) &&
                                (this.Classifier != null))
                            {
                                e.NewJob(this.TrainingSet.Count + 1, RunTestState.NormalizeFeatures);
                                e.ReportProgress();

                                FeatureVector[] fvTmp1D = this.TrainingSet.FeatureVectors.fvNonNormalized;
                                FeatureVector[][] fvTmp2D = new FeatureVector[this.TrainingSet.Count + 1][];
                                double[][] fNonNormalized = new double[this.TrainingSet.Count][];
                                double[][] fNormalized = new double[this.TrainingSet.Count][];
                                for (int i = 0; i < this.TrainingSet.Count; i++)
                                {
                                    fNonNormalized[i] = fvTmp1D[i].ToArray();
                                    fNormalized[i] = new double[fNonNormalized[0].Length];
                                }
                                for (int i = 0; i < this.TrainingSet.Count; i++)
                                {
                                    Normalizer.NormalizeLeaveOneOut(norm, i, fNonNormalized, fNormalized, this.Classifier);
                                    if (e.CancellationRequested)
                                    {
                                        e.WorkCancelled = true;
                                        return null;
                                    }
                                    fvTmp1D = new FeatureVector[this.TrainingSet.Count];
                                    for (int j = 0; j < this.TrainingSet.Count; j++)
                                        fvTmp1D[j] = FeatureVector.FromArray(this.FeatureHeader, fNormalized[j]);
                                    fvTmp2D[i] = fvTmp1D;
                                    e.StepComplete();
                                    e.ReportProgress();
                                }
                                fvTmp1D = new FeatureVector[this.TrainingSet.Count];
                                for (int i = 0; i < this.TrainingSet.Count; i++)
                                    fvTmp1D[i] = fvTmp2D[i][i];
                                fvTmp2D[this.TrainingSet.Count] = fvTmp1D;
                                e.StepComplete();
                                e.ReportProgress();
                                this.TrainingSet.FeatureVectors.dictionaryLeave1Out.Add(norm, fvTmp2D);
                            }
                            if (this.TrainingSet.FeatureVectors.dictionaryLeave1Out.ContainsKey(norm))
                            {
                                vectorsTest = this.TrainingSet.FeatureVectors.dictionaryLeave1Out[norm];
                                if (vectorsTest[0][0].Texture == null)
                                {
                                    e.NewJob(this.TrainingSet.Count + 1, RunTestState.NormalizeFeatures);
                                    e.ReportProgress();

                                    FeatureVector[] fvTmp1D = this.TrainingSet.FeatureVectors.fvNonNormalized;
                                    FeatureVector[][] fvTmp2D = new FeatureVector[this.TrainingSet.Count + 1][];
                                    double[][] fNonNormalized = new double[this.TrainingSet.Count][];
                                    double[][] fNormalized = new double[this.TrainingSet.Count][];
                                    for (int i = 0; i < this.TrainingSet.Count; i++)
                                    {
                                        fNonNormalized[i] = fvTmp1D[i].ToArray();
                                        fNormalized[i] = new double[fNonNormalized[0].Length];
                                    }
                                    for (int i = 0; i < this.TrainingSet.Count; i++)
                                    {
                                        Normalizer.NormalizeLeaveOneOut(norm, i, fNonNormalized, fNormalized, this.Classifier);
                                        if (e.CancellationRequested)
                                        {
                                            e.WorkCancelled = true;
                                            return null;
                                        }
                                        fvTmp1D = new FeatureVector[this.TrainingSet.Count];
                                        for (int j = 0; j < this.TrainingSet.Count; j++)
                                            fvTmp1D[j] = FeatureVector.FromArray(this.FeatureHeader, fNormalized[j]);
                                        fvTmp2D[i] = fvTmp1D;
                                        e.StepComplete();
                                        e.ReportProgress();
                                    }
                                    fvTmp1D = new FeatureVector[this.TrainingSet.Count];
                                    for (int i = 0; i < this.TrainingSet.Count; i++)
                                        fvTmp1D[i] = fvTmp2D[i][i];
                                    fvTmp2D[this.TrainingSet.Count] = fvTmp1D;
                                    e.StepComplete();
                                    e.ReportProgress();
                                    this.TrainingSet.FeatureVectors.dictionaryLeave1Out.Clear();
                                    this.TrainingSet.FeatureVectors.dictionaryLeave1Out.Add(norm, fvTmp2D);
                                }
                                vectors = this.TrainingSet.FeatureVectors.dictionaryLeave1Out[norm];
                            }

                        }
                    }
                    else
                    {
                        if (!this.CentroidSet.FeatureVectors.dictionaryLeave1Out.ContainsKey(Normalization.None))
                        {
                            FeatureVector[][] fvTmp = new FeatureVector[this.TrainingSet.Count][];
                            for (int i = 0; i < this.TrainingSet.Count; i++)
                            {
                                fvTmp[i] = new FeatureVector[this.CentroidSet.Count];
                                for (int j = 0; j < this.CentroidSet.Count; j++)
                                {
                                    CentroidObject obj = this.CentroidSet[j] as CentroidObject;
                                    fvTmp[i][j] = obj.LeaveOneOutVectors[i];
                                }
                            }
                            this.CentroidSet.FeatureVectors.dictionaryLeave1Out.Add(Normalization.None, fvTmp);
                        }
                        if (!this.CentroidSet.FeatureVectors.dictionaryLeave1Out.ContainsKey(norm) &&
                            (norm != Normalization.None) && (this.Classifier != null))
                        {
                            e.NewJob(this.TrainingSet.Count + 1, RunTestState.NormalizeFeatures);
                            e.ReportProgress();

                            FeatureVector[] fvTmp1D = null;
                            FeatureVector[] fvTraining = this.TrainingSet.FeatureVectors.fvNonNormalized;
                            FeatureVector[][] fvTmp2D = new FeatureVector[this.TrainingSet.Count + 1][];
                            FeatureVector[][] fvCentroids = this.CentroidSet.FeatureVectors.dictionaryLeave1Out[Normalization.None];
                            double[][] fCentroid = new double[this.CentroidSet.Count + 1][];
                            for (int i = 0; i < this.TrainingSet.Count; i++)
                            {
                                for (int j = 0; j < this.CentroidSet.Count; j++)
                                {
                                    if (fvCentroids[i][j] == null)
                                        continue;
                                    fCentroid[j] = fvCentroids[i][j].ToArray();
                                }
                                fCentroid[this.CentroidSet.Count] = fvTraining[i].ToArray();

                                Normalizer.NormalizeLeaveOneOut(norm, this.CentroidSet.Count, fCentroid, this.Classifier);
                                if (e.CancellationRequested)
                                {
                                    e.WorkCancelled = true;
                                    return null;
                                }
                                fvTmp1D = new FeatureVector[this.CentroidSet.Count + 1];
                                for (int j = 0; j < this.CentroidSet.Count + 1; j++)
                                {
                                    if (fCentroid[j] == null)
                                        continue;
                                    fvTmp1D[j] = FeatureVector.FromArray(this.FeatureHeader, fCentroid[j]);
                                }
                                fvTmp2D[i] = fvTmp1D;
                                e.StepComplete();
                                e.ReportProgress();
                            }
                            fvTmp1D = new FeatureVector[this.TrainingSet.Count];
                            for (int i = 0; i < this.TrainingSet.Count; i++)
                                fvTmp1D[i] = fvTmp2D[i][this.CentroidSet.Count];
                            fvTmp2D[this.TrainingSet.Count] = fvTmp1D;
                            e.StepComplete();
                            e.ReportProgress();
                            this.CentroidSet.FeatureVectors.dictionaryLeave1Out.Add(norm, fvTmp2D);
                        }
                        if (this.CentroidSet.FeatureVectors.dictionaryLeave1Out.ContainsKey(norm))
                        {
                            vectorsTest = this.CentroidSet.FeatureVectors.dictionaryLeave1Out[norm];
                            if (vectorsTest[0][0].Texture == null)
                            {
                                e.NewJob(this.TrainingSet.Count + 1, RunTestState.NormalizeFeatures);
                                e.ReportProgress();

                                FeatureVector[] fvTmp1D = null;
                                FeatureVector[] fvTraining = this.TrainingSet.FeatureVectors.fvNonNormalized;
                                FeatureVector[][] fvTmp2D = new FeatureVector[this.TrainingSet.Count + 1][];
                                FeatureVector[][] fvCentroids = this.CentroidSet.FeatureVectors.dictionaryLeave1Out[Normalization.None];
                                double[][] fCentroid = new double[this.CentroidSet.Count + 1][];
                                for (int i = 0; i < this.TrainingSet.Count; i++)
                                {
                                    for (int j = 0; j < this.CentroidSet.Count; j++)
                                    {
                                        if (fvCentroids[i][j] == null)
                                            continue;
                                        fCentroid[j] = fvCentroids[i][j].ToArray();
                                    }
                                    fCentroid[this.CentroidSet.Count] = fvTraining[i].ToArray();

                                    Normalizer.NormalizeLeaveOneOut(norm, this.CentroidSet.Count, fCentroid, this.Classifier);
                                    if (e.CancellationRequested)
                                    {
                                        e.WorkCancelled = true;
                                        return null;
                                    }
                                    fvTmp1D = new FeatureVector[this.CentroidSet.Count + 1];
                                    for (int j = 0; j < this.CentroidSet.Count + 1; j++)
                                    {
                                        if (fCentroid[j] == null)
                                            continue;
                                        fvTmp1D[j] = FeatureVector.FromArray(this.FeatureHeader, fCentroid[j]);
                                    }
                                    fvTmp2D[i] = fvTmp1D;
                                    e.StepComplete();
                                    e.ReportProgress();
                                }
                                fvTmp1D = new FeatureVector[this.TrainingSet.Count];
                                for (int i = 0; i < this.TrainingSet.Count; i++)
                                    fvTmp1D[i] = fvTmp2D[i][this.CentroidSet.Count];
                                fvTmp2D[this.TrainingSet.Count] = fvTmp1D;
                                e.StepComplete();
                                e.ReportProgress();
                                this.CentroidSet.FeatureVectors.dictionaryLeave1Out.Clear();
                                this.CentroidSet.FeatureVectors.dictionaryLeave1Out.Add(norm, fvTmp2D);
                            }
                            vectors = this.CentroidSet.FeatureVectors.dictionaryLeave1Out[norm];
                        }

                    }
                }
                return vectors;
            }
            public FeatureVector[][] GetTrainingTestVectors(Normalization norm, MultiStepJobEventArgs e)
            {
                FeatureVector[][] vectors = new FeatureVector[3][];
                FeatureVector[][] vectorsTest = new FeatureVector[3][];
                if (this.IsUsingTrainingTest && (this.FeatureHeader != null) &&
                    (this.TrainingSet.Count > 0) && (this.TestSet.Count > 0))
                {
                    RefreshNonNormalizedVectors(e);
                    if (e.WorkCancelled)
                        return null;

                    if (norm == Normalization.None)
                    {
                        vectors[0] = this.TrainingSet.FeatureVectors.fvNonNormalized;
                        vectors[1] = this.TestSet.FeatureVectors.fvNonNormalized;
                        if (this.CentroidSet != null)
                            vectors[2] = this.CentroidSet.FeatureVectors.fvNonNormalized;
                    }
                    else
                    {
                        FeatureFile ffTrainingSet = (this.CentroidSet != null) ? this.CentroidSet : this.TrainingSet;
                        FeatureFile ffTestSet = this.TestSet;
                        if ((!ffTrainingSet.FeatureVectors.dictionaryTrainingTest.ContainsKey(norm) ||
                             !ffTestSet.FeatureVectors.dictionaryTrainingTest.ContainsKey(norm))
                             &&
                             (this.Classifier != null))
                        {
                            e.ReportProgress(WorkerThread.LookupString(RunTestState.NormalizeFeatures));
                            FeatureVector[] fvTmp = ffTrainingSet.FeatureVectors.fvNonNormalized;
                            double[][] fTraining = new double[ffTrainingSet.Count][];
                            for (int i = 0; i < ffTrainingSet.Count; i++)
                                fTraining[i] = fvTmp[i].ToArray();

                            fvTmp = ffTestSet.FeatureVectors.fvNonNormalized;
                            double[][] fTest = new double[ffTestSet.Count][];
                            for (int i = 0; i < ffTestSet.Count; i++)
                                fTest[i] = fvTmp[i].ToArray();

                            Normalizer.NormalizeTrainingTest(norm, fTraining, fTest, this.Classifier);
                            if (e.CancellationRequested)
                            {
                                e.WorkCancelled = true;
                                return null;
                            }
                            fvTmp = new FeatureVector[ffTrainingSet.Count];
                            for (int i = 0; i < ffTrainingSet.Count; i++)
                                fvTmp[i] = FeatureVector.FromArray(this.FeatureHeader, fTraining[i]);
                            ffTrainingSet.FeatureVectors.dictionaryTrainingTest[norm] = fvTmp;

                            fvTmp = new FeatureVector[ffTestSet.Count];
                            for (int i = 0; i < ffTestSet.Count; i++)
                                fvTmp[i] = FeatureVector.FromArray(this.FeatureHeader, fTest[i]);
                            ffTestSet.FeatureVectors.dictionaryTrainingTest[norm] = fvTmp;
                        }
                        if (ffTrainingSet.FeatureVectors.dictionaryTrainingTest.ContainsKey(norm) &&
                            ffTestSet.FeatureVectors.dictionaryTrainingTest.ContainsKey(norm))
                        {
                            vectorsTest[0] = ffTrainingSet.FeatureVectors.dictionaryTrainingTest[norm];
                            vectorsTest[1] = ffTestSet.FeatureVectors.dictionaryTrainingTest[norm];

                            if (vectorsTest[0][0].Texture == null)
                            {

                                ffTrainingSet.FeatureVectors.dictionaryTrainingTest[norm] = null;
                                ffTestSet.FeatureVectors.dictionaryTrainingTest[norm] = null;
                                e.ReportProgress(WorkerThread.LookupString(RunTestState.NormalizeFeatures));
                                FeatureVector[] fvTmp = ffTrainingSet.FeatureVectors.fvNonNormalized;
                                double[][] fTraining = new double[ffTrainingSet.Count][];
                                for (int i = 0; i < ffTrainingSet.Count; i++)
                                    fTraining[i] = fvTmp[i].ToArray();

                                fvTmp = ffTestSet.FeatureVectors.fvNonNormalized;
                                double[][] fTest = new double[ffTestSet.Count][];
                                for (int i = 0; i < ffTestSet.Count; i++)
                                    fTest[i] = fvTmp[i].ToArray();

                                Normalizer.NormalizeTrainingTest(norm, fTraining, fTest, this.Classifier);
                                if (e.CancellationRequested)
                                {
                                    e.WorkCancelled = true;
                                    return null;
                                }
                                fvTmp = new FeatureVector[ffTrainingSet.Count];
                                for (int i = 0; i < ffTrainingSet.Count; i++)
                                    fvTmp[i] = FeatureVector.FromArray(this.FeatureHeader, fTraining[i]);
                                ffTrainingSet.FeatureVectors.dictionaryTrainingTest[norm] = fvTmp;

                                fvTmp = new FeatureVector[ffTestSet.Count];
                                for (int i = 0; i < ffTestSet.Count; i++)
                                    fvTmp[i] = FeatureVector.FromArray(this.FeatureHeader, fTest[i]);
                                ffTestSet.FeatureVectors.dictionaryTrainingTest[norm] = fvTmp;

                            }
                            int idx = (ffTrainingSet == this.TrainingSet) ? 0 : 2;
                            vectors[idx] = ffTrainingSet.FeatureVectors.dictionaryTrainingTest[norm];
                            vectors[1] = ffTestSet.FeatureVectors.dictionaryTrainingTest[norm];
                        }
                    }
                }
                return vectors;
            }
            private void RefreshNonNormalizedVectors(MultiStepJobEventArgs e)
            {
                int count = this.TrainingSet.Count;
                if (this.IsUsingTrainingTest) count += this.TestSet.Count;
                e.NewJob(count, RunTestState.ExtractFeatures);
                e.ReportProgress();

                for (int i = 0; i < 3; i++)
                {
                    FeatureFile ff = this.FeatureFileSet[i];
                    if ((ff == null) || ((count = ff.Count) == 0))
                        continue;
                    if (ff.IsCentroidSet)
                    {
                        e.NewJob(count, RunTestState.CalculateCentroid);
                        e.ReportProgress();
                    }
                    if ((ff.FeatureVectors.fvNonNormalized == null) ||
                         (ff.FeatureVectors.fvNonNormalized.Length != count))
                    {
                        ff.FeatureVectors.fvNonNormalized = new FeatureVector[count];
                        ff.ClearVectorCache();
                        for (int k = 0; k < count; k++)
                        {

                          //  ff[k].FeatureVector.ClearTex();
                        }

                    }
                    Parallel.For(0, count, j =>
                    {
                        var startTime = DateTime.Now;
                        Console.WriteLine($"Start Time for index {j}: {startTime:HH:mm:ss.fff}");

                        ff.FeatureVectors.fvNonNormalized[j] = ff[j].FeatureVector;
                        
                        if (e.CancellationRequested)
                        {
                            e.WorkCancelled = true;
                            return;
                        }

                        e.StepComplete();
                        e.ReportProgress();

                        var endTime = DateTime.Now;
                        Console.WriteLine($"End Time for index {j}: {endTime:HH:mm:ss.fff}");
                    });

                }
            }

            public Classifier Classifier { get { return this.ffOwner.Classifier; } }
            public CentroidSet CentroidSet { get { return this.ffOwner.CentroidSet; } }
            public FeatureFile TrainingSet { get { return this.ffOwner.TrainingSet; } }
            public FeatureFile TestSet { get { return this.ffOwner.TestSet; } }
            public FeatureFileSet FeatureFileSet { get { return this.ffOwner.FeatureFileSet; } }
            public FeatureHeader FeatureHeader { get { return this.ffOwner.FeatureHeader; } }
            public bool IsCentroidSet { get { return this.ffOwner.IsCentroidSet; } }
            public bool IsTrainingSet { get { return this.ffOwner.IsTrainingSet; } }
            public bool IsTestSet { get { return this.ffOwner.IsTestSet; } }
            public bool IsUsingLeaveOneOut { get { return this.ffOwner.IsUsingLeaveOneOut; } }
            public bool IsUsingTrainingTest { get { return this.ffOwner.IsUsingTrainingTest; } }
        }
        public virtual CvipObject this[int idx]
        {
            get
            {
                CvipObject obj = null;
                if ((idx >= 0) && (idx < this.lstObjects.Count))
                    obj = this.lstObjects.Values[idx];
                return obj;
            }
        }
        public CvipObject this[string key]
        {
            get
            {
                CvipObject obj = null;
                if (!string.IsNullOrEmpty(key))
                {
                    int idx = this.lstObjects.IndexOfKey(key);
                    if (idx != -1)
                        obj = this.lstObjects.Values[idx];
                }
                return obj;
            }
        }
        public Algorithm Algorithm { get { return this.ffsOwner.Algorithm; } }
        public Classifier Classifier { get { return this.ffsOwner.Classifier; } }
        public CentroidSet CentroidSet { get { return this.ffsOwner.CentroidSet; } }
        public FeatureFile TrainingSet { get { return this.ffsOwner.TrainingSet; } }
        public FeatureFile TestSet { get { return this.ffsOwner.TestSet; } }
        public FeatureFileSet FeatureFileSet { get { return this.ffsOwner; } }
        public FeatureHeader FeatureHeader { get { return this.ffsOwner.FeatureHeader; } }
        public FeatureVectorCollection FeatureVectors { get { return this.collectionVectors; } }
        public Normalization Normalization { get { return this.ffsOwner.Normalization; } }
        public bool IsCentroidSet { get { return this.CentroidSet == this; } }
        public bool IsTrainingSet { get { return this.TrainingSet == this; } }
        public bool IsTestSet { get { return this.TestSet == this; } }
        public bool IsReadOnly { get { return false; } }
        public bool IsUsingLeaveOneOut { get { return this.ffsOwner.UsingLeaveOneOut; } }
        public bool IsUsingTrainingTest { get { return this.ffsOwner.UsingTrainingTest; } }
        public virtual int Count { get { return this.lstObjects.Count; } }
    }
}
