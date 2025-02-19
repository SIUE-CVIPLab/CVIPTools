/*''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' ======================================================================
' Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
' ======================================================================
'
'             File Name: Normalizer.cs
'           Description: Contains the code for
'                        for Normalizer class
'         Related Files: FeatureFile.cs
'                        FeatureVector.cs
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
using System.Text;

namespace CVIPFEPC.CvipFile
{
    public static class Normalizer
    {
        public static void NormalizeLeaveOneOut(Normalization norm, int idx, double[][] fFeatureVals, Classifier classifier)
        {
            double[] euclidean = null;
            Tuple<double, double>[] stats = null;
            switch (norm)
            {
            case Normalization.MinMax:
                stats = FindMinMax(fFeatureVals, idx);
                MinMaxNormalize(fFeatureVals, stats, classifier.SMin, classifier.SMax);
                break;
            case Normalization.Range:
                stats = FindMinMax(fFeatureVals, idx);
                RangeNormalize(fFeatureVals, stats);
                break;
            case Normalization.Softmax:
                stats = FindMeanSigma(fFeatureVals, idx);
                SoftmaxNormalize(fFeatureVals, stats, classifier.Softmax);
                break;
            case Normalization.StdNormal:
                stats = FindMeanSigma(fFeatureVals, idx);
                StdNormNormalize(fFeatureVals, stats);
                break;
            case Normalization.UnitVector:
                euclidean = FindEuclideans(fFeatureVals, idx);
                UnitVectorNormalize(fFeatureVals, euclidean);
                break;
            }
        }
        public static void NormalizeLeaveOneOut(Normalization norm, int idx, double[][] fNonNormalized, double[][] fNormalized, Classifier classifier)
        {
            double[] euclidean = null;
            Tuple<double, double>[] stats = null;
            switch (norm)
            {
            case Normalization.MinMax:
                stats = FindMinMax(fNonNormalized, idx);
                MinMaxNormalize(fNonNormalized, fNormalized, stats, classifier.SMin, classifier.SMax);
                break;
            case Normalization.Range:
                stats = FindMinMax(fNonNormalized, idx);
                RangeNormalize(fNonNormalized, fNormalized, stats);
                break;
            case Normalization.Softmax:
                stats = FindMeanSigma(fNonNormalized, idx);
                SoftmaxNormalize(fNonNormalized, fNormalized, stats, classifier.Softmax);
                break;
            case Normalization.StdNormal:
                stats = FindMeanSigma(fNonNormalized, idx);
                StdNormNormalize(fNonNormalized, fNormalized, stats);
                break;
            case Normalization.UnitVector:
                euclidean = FindEuclideans(fNonNormalized, idx);
                UnitVectorNormalize(fNonNormalized, fNormalized, euclidean);
                break;
            }
        }
        public static void NormalizeTrainingTest(Normalization norm, double[][] fTraining, double[][] fTest, Classifier classifier)
        {
            double[] euclidean = null;
            Tuple<double, double>[] stats = null;
            switch (norm)
            {
            case Normalization.MinMax:
                stats = FindMinMax(fTraining);
                MinMaxNormalize(fTraining, stats, classifier.SMin, classifier.SMax);
                MinMaxNormalize(fTest, stats, classifier.SMin, classifier.SMax);
                break;
            case Normalization.Range:
                stats = FindMinMax(fTraining);
                RangeNormalize(fTraining, stats);
                RangeNormalize(fTest, stats);
                break;
            case Normalization.Softmax:
                stats = FindMeanSigma(fTraining);
                SoftmaxNormalize(fTraining, stats, classifier.Softmax);
                SoftmaxNormalize(fTest, stats, classifier.Softmax);
                break;
            case Normalization.StdNormal:
                stats = FindMeanSigma(fTraining);
                StdNormNormalize(fTraining, stats);
                StdNormNormalize(fTest, stats);
                break;
            case Normalization.UnitVector:
                euclidean = FindEuclideans(fTraining);
                UnitVectorNormalize(fTraining, euclidean);
                UnitVectorNormalize(fTest, euclidean);
                break;
            }
        }
        private static double[] FindEuclideans(double[][] data, int idx)
        {
            double[] tmp = data[idx];
            data[idx] = null;
            double[] euclideans = FindEuclideans(data);
            data[idx] = tmp;
            return euclideans;
        }
        public static double[] FindEuclideans(double[][] data)
        {
            int cols = 0, rows = data.Length;
            for (int r = 0; r < rows; r++)
            {
                if (data[r] == null) continue;
                cols = data[r].Length;
                break;
            }
            double[] euclideans = new double[cols];
            for (int c = 0; c < cols; c++)
            {
                euclideans[c] = 0.0;
                for (int r = 0; r < rows; r++)
                {
                    if (data[r] == null) continue;
                    euclideans[c] += data[r][c] * data[r][c];
                }
                euclideans[c] = Math.Sqrt(euclideans[c]);
            }
            return euclideans;
        }
        private static Tuple<double, double>[] FindMeanSigma(double[][] data, int idx)
        {
            double[] tmp = data[idx];
            data[idx] = null;
            Tuple<double, double>[] meansigma = FindMeanSigma(data);
            data[idx] = tmp;
            return meansigma;
        }
        public static Tuple<double, double>[] FindMeanSigma(double[][] data)
        {
            int cols = 0, rows = data.Length;
            for (int r = 0; r < rows; r++)
            {
                if (data[r] == null) continue;
                cols = data[r].Length;
                break;
            }
            Tuple<double, double>[] meansigma = new Tuple<double, double>[cols];
            for (int c = 0; c < cols; c++)
            {
                int count = 0;
                double mean = 0.0;
                double sigma = 0.0;
                for (int r = 0; r < rows; r++)
                {
                    if (data[r] == null) continue;
                    mean += data[r][c];
                    count++;
                }
                mean /= count;
                for (int r = 0; r < rows; r++)
                {
                    if (data[r] == null) continue;
                    sigma += ((data[r][c] - mean) * (data[r][c] - mean));
                }
                sigma = Math.Sqrt(sigma / count);
                meansigma[c] = new Tuple<double, double>(mean, sigma);
            }
            return meansigma;
        }
        private static Tuple<double, double>[] FindMinMax(double[][] data, int idx)
        {
            double[] tmp = data[idx];
            data[idx] = null;
            Tuple<double, double>[] minmax = FindMinMax(data);
            data[idx] = tmp;
            return minmax;
        }
        public static Tuple<double, double>[] FindMinMax(double[][] data)
        {
            int cols = 0, rows = data.Length;
            for (int r = 0; r < rows; r++)
            {
                if (data[r] == null) continue;
                cols = data[r].Length;
                break;
            }
            Tuple<double, double>[] minmax = new Tuple<double, double>[cols];
            for (int c = 0; c < cols; c++)
            {
                double min = double.MaxValue;
                double max = double.MinValue;
                for (int r = 0; r < rows; r++)
                {
                    if (data[r] == null) continue;
                    if (data[r][c] < min)
                        min = data[r][c];
                    if (data[r][c] > max)
                        max = data[r][c];
                }
                minmax[c] = new Tuple<double, double>(min, max);
            }
            return minmax;
        }
        private static void MinMaxNormalize(double[][] data, Tuple<double, double>[] minmax, float s_min, float s_max)
        {
            MinMaxNormalize(data, null, minmax, s_min, s_max);
        }
        private static void MinMaxNormalize(double[][] fNonNormalized, double[][] fNormalized, Tuple<double, double>[] minmax, float s_min, float s_max)
        {
            double[][] normalized = (fNormalized != null) ? fNormalized : fNonNormalized;
            int rows = fNonNormalized.Length;
            int cols = fNonNormalized[0].Length;
            for (int c = 0; c < cols; c++)
            {
                double min = minmax[c].Item1;
                double max = minmax[c].Item2;
                double scaler = (max - min) * (s_max - s_min);
                if (scaler == 0.0)
                {
                    for (int r = 0; r < rows; r++)
                        normalized[r][c] = 0.0;
                }
                else
                {
                    for (int r = 0; r < rows; r++)
                    {
                        normalized[r][c] = ((fNonNormalized[r][c] - min) / scaler) + s_min;
                        normalized[r][c] = Math.Max(normalized[r][c], s_min);
                        normalized[r][c] = Math.Min(normalized[r][c], s_max);
                    }
                }
            }
        }
        private static void RangeNormalize(double[][] data, Tuple<double, double>[] minmax)
        {
            RangeNormalize(data, null, minmax);
        }
        private static void RangeNormalize(double[][] fNonNormalized, double[][] fNormalized, Tuple<double, double>[] minmax)
        {
            double[][] normalized = (fNormalized != null) ? fNormalized : fNonNormalized;
            int rows = fNonNormalized.Length;
            int cols = fNonNormalized[0].Length;
            for (int c = 0; c < cols; c++)
            {
                double min = minmax[c].Item1;
                double max = minmax[c].Item2;
                double range = max - min;
                if (range == 0.0)
                {
                    for (int r = 0; r < rows; r++)
                        normalized[r][c] = 0.0;
                }
                else
                {
                    for (int r = 0; r < rows; r++)
                    {
                        normalized[r][c] = Math.Max(fNonNormalized[r][c], min);
                        normalized[r][c] = Math.Min(normalized[r][c], max);
                        normalized[r][c] = normalized[r][c] / range;
                    }
                }
            }
        }
        private static void SoftmaxNormalize(double[][] data, Tuple<double, double>[] meansigma, float r_softmax)
        {
            SoftmaxNormalize(data, null, meansigma, r_softmax);
        }
        private static void SoftmaxNormalize(double[][] fNonNormalized, double[][] fNormalized, Tuple<double, double>[] meansigma, float r_softmax)
        {
            double[][] normalized = (fNormalized != null) ? fNormalized : fNonNormalized;
            int rows = fNonNormalized.Length;
            int cols = fNonNormalized[0].Length;
            for (int c = 0; c < cols; c++)
            {
                double mean = meansigma[c].Item1;
                double sigma = meansigma[c].Item2;
                double scaler = sigma * r_softmax;
                if (scaler == 0.0)
                {
                    for (int r = 0; r < rows; r++)
                        normalized[r][c] = 0.0;
                }
                else
                {
                    for (int r = 0; r < rows; r++)
                    {
                        normalized[r][c] = (fNonNormalized[r][c] - mean) / scaler;
                        normalized[r][c] = 1 / (1 + Math.Exp(-normalized[r][c]));
                    }
                }
            }
        }
        private static void StdNormNormalize(double[][] data, Tuple<double, double>[] meansigma)
        {
            StdNormNormalize(data, null, meansigma);
        }
        private static void StdNormNormalize(double[][] fNonNormalized, double[][] fNormalized, Tuple<double, double>[] meansigma)
        {
            double[][] normalized = (fNormalized != null) ? fNormalized : fNonNormalized;
            int rows = fNonNormalized.Length;
            int cols = fNonNormalized[0].Length;
            for (int c = 0; c < cols; c++)
            {
                double mean = meansigma[c].Item1;
                double sigma = meansigma[c].Item2;
                if (sigma == 0.0)
                {
                    for (int r = 0; r < rows; r++)
                        normalized[r][c] = 0.0;
                }
                else
                {
                    for (int r = 0; r < rows; r++)
                        normalized[r][c] = (fNonNormalized[r][c] - mean) / sigma;
                }
            }
        }
        private static void UnitVectorNormalize(double[][] data, double[] euclidean)
        {
            UnitVectorNormalize(data, null, euclidean);
        }
        private static void UnitVectorNormalize(double[][] fNonNormalized, double[][] fNormalized, double[] euclidean)
        {
            double[][] normalized = (fNormalized != null) ? fNormalized : fNonNormalized;
            int rows = fNonNormalized.Length;
            int cols = fNonNormalized[0].Length;
            for (int c = 0; c < cols; c++)
            {
                if (euclidean[c] == 0.0)
                {
                    for (int r = 0; r < rows; r++)
                        normalized[r][c] = 0.0;
                }
                else
                {
                    for (int r = 0; r < rows; r++)
                    {
                        normalized[r][c] = fNonNormalized[r][c] / euclidean[c];
                        normalized[r][c] = Math.Max(normalized[r][c], -1);
                        normalized[r][c] = Math.Min(normalized[r][c], 1);
                    }
                }
            }
        }
    }
}
