/*''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' ======================================================================
' Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
' ======================================================================
'
'             File Name: Classifier.cs
'           Description: Contains the code for
'                        Classifier class
'         Related Files: FeatureChooser.cs
'                        FeatureHeader.cs
'                        FeatureFile.cs
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

using SERVERLib;
using System;
using System.Collections.Generic;
using System.IO;
using System.Text;
using System.Xml.Serialization;

namespace CVIPFEPC.CvipFile
{
    public enum Algorithm
    {
        K_NearestNeighbor,
        NearestCentroid,
        NearestNeighbor
    }
    public enum Normalization
    {
        None,
        Range,
        UnitVector,
        StdNormal,
        MinMax,
        Softmax
    }
    public enum Distance
    {
        Euclidean,
        CityBlock,
        MaxValue,
        Minkowski,
        VectorInnerProduct,
        Tanimoto
    }
    public class Classifier : FeatureChooser
    {
        private static CVIPTools CvipOp = new CVIPTools();

        private Algorithm currentAlgorithm = Algorithm.NearestNeighbor;
        private Distance currentDistance = Distance.Euclidean;
        private Normalization currentNormalization = Normalization.None;

        private float m_fMinkowski = 3.0f;
        private float m_fSMax = 1.0f;
        private float m_fSMin = 0.0f;
        private float m_fSoftmax = 1.0f;
        private int m_nNeighbors = 3;

		public string tmpclass1 = null;
        public string tmpclass2 = null;
        public string tmpclass3 = null ;
        public string tmpclass4 ,tmpclass5 ,tmpclass6 ,tmpclass7 ,tmpclass8 ,tmpclass9 ,tmpclass10 ;
        public string tmpheader;
        public int abc = 0;

        private Dictionary<Algorithm, string> sAlgorithmAbbreviations = null;
        private Dictionary<Distance, string> sDistanceAbbreviations = null;
        private Dictionary<Normalization, string> sNormalizationAbbreviations = null;

        public Classifier() { }
        public Classifier(Classifier classifier)
            : base((FeatureChooser)classifier)
        {
            this.currentAlgorithm = classifier.currentAlgorithm;
            this.currentDistance = classifier.currentDistance;
            this.currentNormalization = classifier.currentNormalization;
            this.m_fMinkowski = classifier.m_fMinkowski;
            this.m_fSMax = classifier.m_fSMax;
            this.m_fSMin = classifier.m_fSMin;
            this.m_fSoftmax = classifier.m_fSoftmax;
            this.m_nNeighbors = classifier.m_nNeighbors;
        }
        public override bool Equals(object obj)
        {
            return (Equals(obj as Classifier));
        }
        public bool Equals(Classifier classifier)
        {
            return base.Equals(classifier) &&
                (this.currentAlgorithm == classifier.currentAlgorithm) &&
                (this.currentDistance == classifier.currentDistance) &&
                (this.currentNormalization == classifier.currentNormalization) &&
                (this.m_fMinkowski == classifier.m_fMinkowski) &&
                (this.m_fSMax == classifier.m_fSMax) &&
                (this.m_fSMin == classifier.m_fSMin) &&
                (this.m_fSoftmax == classifier.m_fSoftmax) &&
                (this.m_nNeighbors == classifier.m_nNeighbors);
        }
        public override int GetHashCode()
        {
            return base.GetHashCode();
        }
        public override void AllOn()
        {
            if (this.FeatureHeader != null)
                this.FeatureHeader.AllOn();
        }
        public override void Append(FeatureChooser fc)
        {
            ClassifierChooser cc = fc as ClassifierChooser;
            if (cc != null)
            {
                base.Append(fc);
                cc.Classifier = this;
            }
            else if ((fc != null) && (this.FeatureHeader != null))
            {
                this.FeatureHeader.Append(fc);
            }
        }
        public void Classify(string sTest, string sTrain, string sResult)
        {
            int errcode = 7;
            if (this.Algorithm == Algorithm.K_NearestNeighbor)
            {
                errcode = CvipOp.K_Nearest_Neighbor(ref sTest,
                                    ref sTrain,
                                    ref sResult,
                                    (int)Normalization.None,
                                    (int)this.Distance,
                                    this.Neighbors,
                                    this.SMin,
                                    this.SMax,
                                    this.Softmax,
                                    this.Minkowski);
            }
            else
            {
                errcode = CvipOp.Nearest_Neighbor(ref sTest,
                                    ref sTrain,
                                    ref sResult,
                                    (int)Normalization.None,
                                    (int)this.Distance,
                                    this.SMin,
                                    this.SMax,
                                    this.Softmax,
                                    this.Minkowski);
            }
            if (errcode != 0)
            {
                switch (errcode)
                {
                    case 1: throw new Exception("The headers in the training and test files don't match");
                    case 2: throw new Exception("K is greater than the number of entries in the training set or K<=0");
                    case 3: throw new Exception("s_min is greater than or equal to s_max");
                    case 4: throw new Exception("Data range is 0 and so the data can't be normalized");
                    case 5: throw new Exception("Divisor is 0 in Tanimoto similarity measure");
                    case 7: throw new Exception("Can't open, read or create file");
                    case 9: throw new Exception("Memory allocation error");
                    case 10: throw new Exception("Every entry in training set should have a class name");
                    case 12: throw new Exception("r in minkowski should be a positive integer");
                    case 13: throw new Exception("There is more than one header in the training or test feature file");
                    default: throw new Exception("An unknown error occured");
                }
            }
        }
        public int ClassifyLeaveOneOut(FeatureFileSet ffs, MultiStepJobEventArgs e)
        {
            int successes = -1;
            string[] sResults = RunLeaveOneOutExperiment(ffs, e);
            if ((e.ErrorMsg != null) || e.WorkCancelled)
            {
                return successes;
            }
            using (StreamWriter sw = File.CreateText(ffs.ResultsFile))
            {
                WriteResultHeader(ffs, sw);
                List<string>[] statistics = ParseResults(ffs, sResults, sw, e);
                if ((e.ErrorMsg != null) || e.WorkCancelled)
                {
                    return successes;
                }
                successes = e.StepsFinished;
                WriteStatistics(ffs, statistics, sw);
            }
            return successes;
        }
        public int ClassifyTrainingTest(FeatureFileSet ffs, MultiStepJobEventArgs e)
        {
            int successes = -1;
            string[] sResults = RunTrainingTestExperiment(ffs, e);
            if ((e.ErrorMsg != null) || e.WorkCancelled)
            {
                return successes;
            }
            using (StreamWriter sw = File.CreateText(ffs.ResultsFile))
            {
                WriteResultHeader(ffs, sw);
                List<string>[] statistics = ParseResults(ffs, sResults, sw, e);
                if ((e.ErrorMsg != null) || e.WorkCancelled)
                {
                    return successes;
                }
                successes = e.StepsFinished;
                WriteStatistics(ffs, statistics, sw);
            }
            return successes;
        }
        private List<string>[] ParseResults(FeatureFileSet ffs, string[] sResults, StreamWriter sw, MultiStepJobEventArgs e)
        {
            int successes = 0;
            FeatureFile ff = ffs.UsingLeaveOneOut ? ffs.TrainingSet : ffs.TestSet;
            List<string> lstClasses = new List<string>();
            List<string> lstActualClass = new List<string>();
            List<string> lstPredictedClass = new List<string>();
            List<string>[] statistics = new List<string>[] { lstClasses, lstActualClass, lstPredictedClass };

            e.NewJob(ff.Count, RunTestState.ParseResults);
            e.ReportProgress();
            for (int i = 0; i < ff.Count; i++)
            {
                string s = sResults[i];
                sw.WriteLine(s);
                s = s.Trim();

                int idx = s.IndexOf(' ');
                string tempName = ff[i].Name.Replace(" ", "_");
                if (s.Substring(0, idx) != tempName)
                {
                    e.ErrorMsg = "Classifier.ParseResults(): Object.Name doesn't match name in results file. Object.Name = " + ff[i].Name;
                    return null;
                }
                s = s.Substring(idx).Trim();
                s = s.Substring(s.IndexOf(' ')).Trim();
                s = s.Substring(s.IndexOf(' ')).Trim();

                idx = s.IndexOf(' ');
                string sClass = s.Substring(0, idx);
                lstActualClass.Add(sClass);

                if (sClass != ff[i].ClassName)
                {
                    e.ErrorMsg = "Classifier.ParseResults(): Object.ClassName doesn't match class name in results file. Object.ClassName = " + ff[i].ClassName;
                    return null;
                }
                if (!lstClasses.Contains(sClass))
                    lstClasses.Add(sClass);

                s = s.Substring(idx).Trim();
                idx = s.IndexOf(' ');
                sClass = s.Substring(0, idx);
                lstPredictedClass.Add(sClass);

                if (sClass == ff[i].ClassName)
                    successes++;

                e.StepComplete();
                e.ReportProgress();
            }
            e.JobComplete(successes);
            sw.WriteLine();
            sw.WriteLine();
            return statistics;
        }
        private string[] RunLeaveOneOutExperiment(FeatureFileSet ffs, MultiStepJobEventArgs e)
        {
            //System.Diagnostics.Debugger.Break();
            bool bDeleteTmpFiles = false;
            string[] sResults = new string[ffs.TrainingSet.Count];
            if (ffs.TmpTrainingSetFile == null)
            {
                ffs.TmpResultFile = Path.Combine(Path.GetTempPath(), Path.GetRandomFileName());
                ffs.TmpTrainingSetFile = Path.Combine(Path.GetTempPath(), Path.GetRandomFileName());
                ffs.TmpTestSetFile = Path.Combine(Path.GetTempPath(), Path.GetRandomFileName());
                bDeleteTmpFiles = true;
            }
            try
            {
                MultiStepJobEventArgs ffArgs = new MultiStepJobEventArgs(ffs.TrainingSet.Count, RunTestState.ExtractFeatures, e.WorkerThread);
                ffArgs.WorkerReportsProgress = false;
                e.NewJob(ffs.TrainingSet.Count, RunTestState.ClassifyLeaveOneOut);
                e.ReportProgress();
                for (int i = 0; i < ffs.TrainingSet.Count; i++)
                {
                    ffArgs.NewJob();
                    ffs.WriteTmpLeaveOneOutFiles(i, ffArgs);
                    if ((ffArgs.ErrorMsg != null) || ffArgs.WorkCancelled)
                    {
                        e.ErrorMsg = ffArgs.ErrorMsg;
                        e.WorkCancelled = ffArgs.WorkCancelled;
                        break;
                    }
                    Classify(ffs.TmpTestSetFile, ffs.TmpTrainingSetFile, ffs.TmpResultFile);
                    if (e.CancellationRequested)
                    {
                        e.WorkCancelled = true;
                        break;
                    }
                    using (StreamReader sr = File.OpenText(ffs.TmpResultFile))
                    {
                        string s = null;
                        while ((s = sr.ReadLine()) != null)
                        {
                            if (s.Contains("END OF PATTERN CLASSIFICATION HEADER"))
                                break;
                        }
                        while ((s = sr.ReadLine()) != null)
                        {
                            if (string.IsNullOrEmpty(s.Trim()))
                                continue;
                            break;
                        }
                        sResults[i] = s;
                    }
                    e.StepComplete();
                    e.ReportProgress();
                }
            }
            finally
            {
                if (bDeleteTmpFiles)
                {
                    if (File.Exists(ffs.TmpResultFile))
                    {
                        try { File.Delete(ffs.TmpResultFile); }
                        catch { }
                    }
                    if (File.Exists(ffs.TmpTrainingSetFile))
                    {
                        try { File.Delete(ffs.TmpTrainingSetFile); }
                        catch { }
                    }
                    if (File.Exists(ffs.TmpTestSetFile))
                    {
                        try { File.Delete(ffs.TmpTestSetFile); }
                        catch { }
                    }
                    ffs.TmpResultFile = null;
                    ffs.TmpTrainingSetFile = null;
                    ffs.TmpTestSetFile = null;
                }
            }
            return sResults;
        }
        private string[] RunTrainingTestExperiment(FeatureFileSet ffs, MultiStepJobEventArgs e)
        {
            bool bDeleteTmpFiles = false;
            string[] sResults = new string[ffs.TestSet.Count];
            if (ffs.TmpTrainingSetFile == null)
            {
                ffs.TmpResultFile = Path.Combine(Path.GetTempPath(), Path.GetRandomFileName());
                ffs.TmpTrainingSetFile = Path.Combine(Path.GetTempPath(), Path.GetRandomFileName());
                ffs.TmpTestSetFile = Path.Combine(Path.GetTempPath(), Path.GetRandomFileName());
                bDeleteTmpFiles = true;
            }
            try
            {
                ffs.WriteTmpTrainingTestFiles(e);
                if ((e.ErrorMsg != null) || e.WorkCancelled)
                {
                    return null;
                }
                Classify(ffs.TmpTestSetFile, ffs.TmpTrainingSetFile, ffs.TmpResultFile);
                if (e.CancellationRequested)
                {
                    e.WorkCancelled = true;
                    return null;
                }
                using (StreamReader sr = File.OpenText(ffs.TmpResultFile))
                {
                    int idx = 0;
                    string s = null;
                    while ((s = sr.ReadLine()) != null)
                    {
                        if (s.Contains("END OF PATTERN CLASSIFICATION HEADER"))
                            break;
                    }
                    while ((s = sr.ReadLine()) != null)
                    {
                        if (string.IsNullOrEmpty(s.Trim()))
                            continue;
                        break;
                    }
                    do
                    {
                        if (string.IsNullOrEmpty(s.Trim()))
                            break;
                        sResults[idx++] = s;
                    }
                    while ((s = sr.ReadLine()) != null);
                }
            }
            finally
            {
                if (bDeleteTmpFiles)
                {
                    if (File.Exists(ffs.TmpResultFile))
                    {
                        try { File.Delete(ffs.TmpResultFile); }
                        catch { }
                    }
                    if (File.Exists(ffs.TmpTrainingSetFile))
                    {
                        try { File.Delete(ffs.TmpTrainingSetFile); }
                        catch { }
                    }
                    if (File.Exists(ffs.TmpTestSetFile))
                    {
                        try { File.Delete(ffs.TmpTestSetFile); }
                        catch { }
                    }
                    ffs.TmpResultFile = null;
                    ffs.TmpTrainingSetFile = null;
                    ffs.TmpTestSetFile = null;
                }
            }
            return sResults;
        }
        private void WriteResultHeader(FeatureFileSet ffs, StreamWriter sw)
        {
            sw.Write(this.FeatureHeader.ToString());
            sw.WriteLine("*** PATTERN CLASSIFICATION HEADER ***");
            if (ffs.UsingLeaveOneOut)
                sw.WriteLine("Test Type: Leave-One-Out");
            else
                sw.WriteLine("Test Type: TrainingSet/TestSet");
            switch (ffs.Algorithm)
            {
                case Algorithm.NearestNeighbor:
                    sw.WriteLine("Classification Algorithm: Nearest Neighbor");
                    break;
                case Algorithm.K_NearestNeighbor:
                    sw.WriteLine("Classification Algorithm: K-nearest Neighbor\tk = " + ffs.Classifier.Neighbors);
                    break;
                case Algorithm.NearestCentroid:
                    sw.WriteLine("Classification Algorithm: Nearest Centroid");
                    break;
            }
            switch (ffs.Normalization)
            {
                case Normalization.None:
                    sw.WriteLine("Data Normalization: None");
                    break;
                case Normalization.Range:
                    sw.WriteLine("Data Normalization: Range-normalization");
                    break;
                case Normalization.UnitVector:
                    sw.WriteLine("Data Normalization: Unit Vector Normalization");
                    break;
                case Normalization.StdNormal:
                    sw.WriteLine("Data Normalization: Standard Normal Density Normalization");
                    break;
                case Normalization.MinMax:
                    sw.WriteLine("Data Normalization: Min-max Normalization\tSmin = " + ffs.Classifier.SMin + "; Smax = " + ffs.Classifier.SMax);
                    break;
                case Normalization.Softmax:
                    sw.WriteLine("Data Normalization: Softmax Normalization\tr = " + ffs.Classifier.Softmax);
                    break;
            }
            switch (ffs.Classifier.Distance)
            {
                case Distance.Euclidean:
                    sw.WriteLine("Distance Measure: Euclidean Distance");
                    break;
                case Distance.CityBlock:
                    sw.WriteLine("Distance Measure: City Block Value Metric");
                    break;
                case Distance.MaxValue:
                    sw.WriteLine("Distance Measure: Maximum Value Metric");
                    break;
                case Distance.Minkowski:
                    sw.WriteLine("Distance Measure: Minkowski Distance\tr = " + ffs.Classifier.Minkowski);
                    break;
                case Distance.VectorInnerProduct:
                    sw.WriteLine("Similarity Measure: Vector Inner Product");
                    break;
                case Distance.Tanimoto:
                    sw.WriteLine("Similarity Measure: Tanimoto Metric");
                    break;
            }
            if (ffs.UsingLeaveOneOut)
                sw.WriteLine("Feature File: " + ffs.LooTrainingSetFile);
            else
            {
                sw.WriteLine("Training Set File: " + ffs.TrainingSetFile);
                sw.WriteLine("Test Set File: " + ffs.TestSetFile);
            }
            if (ffs.Algorithm == Algorithm.NearestCentroid)
                sw.WriteLine("Centroid Training Set File: " + ffs.CentroidSetFile);
            if (ffs.Normalization != Normalization.None)
            {
                string fname = (ffs.Algorithm == Algorithm.NearestCentroid) ? ffs.CentroidSetFile : ffs.TrainingSetFile;
                sw.WriteLine("Normalized Training Set File: " + ffs.NormalizedFileName(fname, ffs.Normalization));
                sw.WriteLine("Normalized Test Set File: " + ffs.NormalizedFileName(ffs.TestSetFile, ffs.Normalization));
            }
            sw.WriteLine("Output File: " + ffs.ResultsFile);
            sw.WriteLine();
            sw.WriteLine("1. Image Name in Test Set");
            sw.WriteLine("2. Object's row coordinate in Test Set");
            sw.WriteLine("3. Object's column coordinate in Test Set");
            sw.WriteLine("4. Class in Test Set");
            sw.WriteLine("5. Class in Training Set");
            sw.WriteLine("6. Value of Distance or Similarity Measure");
            sw.WriteLine("*** END OF PATTERN CLASSIFICATION HEADER ***");
            sw.WriteLine();
            sw.WriteLine();
        }
        private void WriteStatistics(FeatureFileSet ffs, List<string>[] statistics, StreamWriter sw)
        {
            FeatureFile fff = ffs.UsingLeaveOneOut ? ffs.TrainingSet : ffs.TestSet;
            List<string> lstClasses = statistics[0];
            List<string> lstActualClass = statistics[1];
            List<string> lstPredictedClass = statistics[2];

            sw.WriteLine("*** STATISTICS ***");
            sw.WriteLine("#: Class in the Test File");
            sw.WriteLine("@: Class identified");
            sw.WriteLine();

            for (int i = 0; i < lstClasses.Count; i++)
            {
                int totalCorrect = 0;
                sw.Write("#" + (i + 1) + " |\t");
                for (int j = 0; j < lstClasses.Count; j++)
                {
                    //Added 9/6/2019 to have total class number at top of excel sheet
                    int nCount = 0;
                    for (int k = 0; k < fff.Count; k++)
                    {
                        if ((lstActualClass[k] == lstClasses[i]) && (lstPredictedClass[k] == lstClasses[j]))
                        {
                            nCount++;
                        }
                    }
                    totalCorrect += nCount;
                }
                sw.WriteLine("#" + (i + 1) + ". " + lstClasses[i]);
                if (abc == 0)
                    tmpheader = tmpheader + "%Success " + lstClasses[i] + "(Out of " + totalCorrect.ToString() + "),";
            }
            abc = 1;
            sw.WriteLine();
            for (int i = 0; i < lstClasses.Count; i++)
                sw.WriteLine("@" + (i + 1) + ". " + lstClasses[i]);
            sw.WriteLine();

            sw.Write("   |    ");
            for (int i = 0; i < lstClasses.Count; i++)
                sw.Write("@" + (i + 1) + "\t");
            sw.WriteLine("% Correct");

            sw.Write("---+----");
            for (int i = 0; i < lstClasses.Count; i++)
                sw.Write("--------");
            sw.WriteLine("----------");

            for (int i = 0; i < lstClasses.Count; i++)
            {
                int nSum = 0;
                int correct;
                double fPercentage = 0.0;
                sw.Write("#" + (i + 1) + " |\t");
                for (int j = 0; j < lstClasses.Count; j++)
                {
                    int nCount = 0;
                    for (int k = 0; k < fff.Count; k++)
                    {
                        if ((lstActualClass[k] == lstClasses[i]) && (lstPredictedClass[k] == lstClasses[j]))
                        {
                            nCount++;
                        }
                    }
                    if (j == i)
                        fPercentage = nCount;
                    sw.Write(nCount + "\t");
                    nSum += nCount;
                }
                correct = (int)fPercentage;
                fPercentage = (fPercentage / nSum) * 100.0;
                    if ((i + 1) == 1)
                        tmpclass1 = fPercentage.ToString("0.00") + "% (" + correct.ToString() + "/" + nSum.ToString() + ")";
                    if ((i + 1) == 2)
                        tmpclass2 = fPercentage.ToString("0.00") + "% (" + correct.ToString() + "/" + nSum.ToString() + ")";
                    if ((i + 1) == 3)
                        tmpclass3 = fPercentage.ToString("0.00") + "% (" + correct.ToString() + "/" + nSum.ToString() + ")";
                    if ((i + 1) == 4)
                        tmpclass4 = fPercentage.ToString("0.00") + "% (" + correct.ToString() + "/" + nSum.ToString() + ")";
                    if ((i + 1) == 5)
                        tmpclass5 = fPercentage.ToString("0.00") + "% (" + correct.ToString() + "/" + nSum.ToString() + ")";
                    if ((i + 1) == 6)
                        tmpclass6 = fPercentage.ToString("0.00") + "% (" + correct.ToString() + "/" + nSum.ToString() + ")";
                    if ((i + 1) == 7)
                        tmpclass7 = fPercentage.ToString("0.00") + "% (" + correct.ToString() + "/" + nSum.ToString() + ")";
                    if ((i + 1) == 8)
                        tmpclass8 = fPercentage.ToString("0.00") + "% (" + correct.ToString() + "/" + nSum.ToString() + ")";
                    if ((i + 1) == 9)
                        tmpclass9 = fPercentage.ToString("0.00") + "% (" + correct.ToString() + "/" + nSum.ToString() + ")";
                    if ((i + 1) == 10)
                        tmpclass10 = fPercentage.ToString("0.00") + "% (" + correct.ToString() + "/" + nSum.ToString() + ")";
                sw.WriteLine(fPercentage.ToString("0.00") + "%");
            }
        }

        public override string SelectionHeader
        {
            get
            {
                string hdr = base.SelectionHeader.TrimStart(' ', ',');
                if (this.FeatureHeader != null)
                    hdr += ", NumFeatures" + this.FeatureHeader.SelectionHeader;
                return hdr;
            }
        }
        public override string SelectionValue
        {
            get
            {
                string val = base.SelectionValue.TrimStart(' ', ',');
                if (this.FeatureHeader != null)
                    val += ", " + this.FeatureHeader.NumFeatures + this.FeatureHeader.SelectionValue;
                return val;
            }

        }
        [XmlIgnore]
        public Dictionary<Algorithm, string> AlgorithmAbbreviation
        {
            get
            {
                if (this.sAlgorithmAbbreviations == null)
                {
                    this.sAlgorithmAbbreviations = new Dictionary<Algorithm, string>();
                    this.sAlgorithmAbbreviations[Algorithm.K_NearestNeighbor] = "KNN" + this.Neighbors;
                    this.sAlgorithmAbbreviations[Algorithm.NearestCentroid] = "NC";
                    this.sAlgorithmAbbreviations[Algorithm.NearestNeighbor] = "NN";
                }
                return this.sAlgorithmAbbreviations;
            }
        }
        [XmlIgnore]
        public Dictionary<Distance, string> DistanceAbbreviation
        {
            get
            {
                if (this.sDistanceAbbreviations == null)
                {
                    this.sDistanceAbbreviations = new Dictionary<Distance, string>();
                    this.sDistanceAbbreviations[Distance.CityBlock] = "CB";
                    this.sDistanceAbbreviations[Distance.Euclidean] = "Euc";
                    this.sDistanceAbbreviations[Distance.MaxValue] = "MV";
                    this.sDistanceAbbreviations[Distance.Minkowski] = "Mink" + this.Minkowski;
                    this.sDistanceAbbreviations[Distance.Tanimoto] = "Tan";
                    this.sDistanceAbbreviations[Distance.VectorInnerProduct] = "VIP";
                }
                return this.sDistanceAbbreviations;
            }
        }
        [XmlIgnore]
        public Dictionary<Normalization, string> NormalizationAbbreviation
        {
            get
            {
                if (this.sNormalizationAbbreviations == null)
                {
                    this.sNormalizationAbbreviations = new Dictionary<Normalization, string>();
                    this.sNormalizationAbbreviations[Normalization.MinMax] = "MM" + this.SMin + "x" + this.SMax;
                    this.sNormalizationAbbreviations[Normalization.None] = "None";
                    this.sNormalizationAbbreviations[Normalization.Range] = "Rng";
                    this.sNormalizationAbbreviations[Normalization.Softmax] = "SMax" + this.Softmax;
                    this.sNormalizationAbbreviations[Normalization.StdNormal] = "StdNor";
                    this.sNormalizationAbbreviations[Normalization.UnitVector] = "UVec";
                }
                return this.sNormalizationAbbreviations;
            }
        }

        public Algorithm Algorithm
        {
            get { return this.currentAlgorithm; }
            set { this.currentAlgorithm = value; }
        }
        public Distance Distance
        {
            get { return this.currentDistance; }
            set { this.currentDistance = value; }
        }
        public Normalization Normalization
        {
            get { return this.currentNormalization; }
            set { this.currentNormalization = value; }
        }
        public float Minkowski
        {
            get { return this.m_fMinkowski; }
            set
            {
                this.m_fMinkowski = value;
                this.DistanceAbbreviation[Distance.Minkowski] = "Mink" + this.Minkowski;
            }
        }
        public float SMax
        {
            get { return this.m_fSMax; }
            set
            {
                this.m_fSMax = value;
                this.NormalizationAbbreviation[Normalization.MinMax] = "MM" + this.SMin + "x" + this.SMax;
            }
        }
        public float SMin
        {
            get { return this.m_fSMin; }
            set
            {
                this.m_fSMin = value;
                this.NormalizationAbbreviation[Normalization.MinMax] = "MM" + this.SMin + "x" + this.SMax;
            }
        }
        public float Softmax
        {
            get { return this.m_fSoftmax; }
            set
            {
                this.m_fSoftmax = value;
                this.NormalizationAbbreviation[Normalization.Softmax] = "SMax" + this.Softmax;
            }
        }
        public int Neighbors
        {
            get { return this.m_nNeighbors; }
            set
            {
                this.m_nNeighbors = value;
                this.AlgorithmAbbreviation[Algorithm.K_NearestNeighbor] = "KNN" + this.Neighbors;
            }
        }

    }
}
