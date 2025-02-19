/*''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' ======================================================================
' Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
' ======================================================================
'
'             File Name: ClassifierChooser.cs
'           Description: Contains the code for
'                        ClassifierChooser class
'         Related Files: FeatureChooser.cs
'                        Classifier.cs
'                        FeatureHeader.cs
'   Initial Coding Date: December 2011
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
    public abstract class ClassifierChooser : FeatureChooser
    {
        protected Classifier m_Classifier = null;

        protected ClassifierChooser() { }
        protected ClassifierChooser(ClassifierChooser chooser)
            : base((FeatureChooser)chooser) { }

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
                cc.Classifier = this.Classifier;
            }
            else if ((fc != null) && (this.FeatureHeader != null))
            {
                this.FeatureHeader.Append(fc);
            }
        }

        [XmlIgnore]
        public Classifier Classifier
        {
            get { return this.m_Classifier; }
            set { this.m_Classifier = value; }
        }
        public override FeatureHeader FeatureHeader
        {
            get { return (this.m_Classifier != null) ? this.m_Classifier.FeatureHeader : null; }
            set { }
        }
    }
    public class AlgorithmChooser : ClassifierChooser
    {
        Queue<Algorithm> enabledAlgorithms = new Queue<Algorithm>();

        bool m_bUseNearestNeighbor = true;
        bool m_bUseKNearestNeighbor = false;
        bool m_bUseNearestCentroid = false;
        int m_nMinNeighbors = 3;
        int m_nMaxNeighbors = 3;

        public AlgorithmChooser() { }
        public AlgorithmChooser(AlgorithmChooser chooser)
            : base((ClassifierChooser)chooser)
        {
            this.m_bUseNearestNeighbor = chooser.m_bUseNearestNeighbor;
            this.m_bUseKNearestNeighbor = chooser.m_bUseKNearestNeighbor;
            this.m_bUseNearestCentroid = chooser.m_bUseNearestCentroid;
            this.m_nMinNeighbors = chooser.m_nMinNeighbors;
            this.m_nMaxNeighbors = chooser.m_nMaxNeighbors;
        }
        public override bool Equals(object obj)
        {
            return (Equals(obj as AlgorithmChooser));
        }
        public bool Equals(AlgorithmChooser chooser)
        {
            return base.Equals(chooser) &&
                (this.m_bUseNearestNeighbor == chooser.m_bUseNearestNeighbor) &&
                (this.m_bUseKNearestNeighbor == chooser.m_bUseKNearestNeighbor) &&
                (this.m_bUseNearestCentroid == chooser.m_bUseNearestCentroid) &&
                (this.m_nMinNeighbors == chooser.m_nMinNeighbors) &&
                (this.m_nMaxNeighbors == chooser.m_nMaxNeighbors);
        }
        public override int GetHashCode()
        {
            return base.GetHashCode();
        }
        public override bool Increment()
        {
            bool carry = base.Increment();
            if (carry && !this.Locked)
            {
                if (this.Algorithm == Algorithm.K_NearestNeighbor)
                {
                    if (carry = (++this.Neighbors > this.MaxNeighbors))
                        this.Neighbors = this.MinNeighbors;
                }
                if (carry)
                {
                    if (carry = (this.enabledAlgorithms.Count == 0))
                    {
                        if (this.m_bUseNearestNeighbor) this.enabledAlgorithms.Enqueue(Algorithm.NearestNeighbor);
                        if (this.m_bUseKNearestNeighbor) this.enabledAlgorithms.Enqueue(Algorithm.K_NearestNeighbor);
                        if (this.m_bUseNearestCentroid) this.enabledAlgorithms.Enqueue(Algorithm.NearestCentroid);
                    }
                    this.Algorithm = this.enabledAlgorithms.Dequeue();
                }
            }
            return carry;
        }
        public override void Reset()
        {
            base.Reset();
            if (!this.Locked)
            {
                this.enabledAlgorithms.Clear();
                if (this.m_bUseNearestNeighbor) this.enabledAlgorithms.Enqueue(Algorithm.NearestNeighbor);
                if (this.m_bUseKNearestNeighbor) this.enabledAlgorithms.Enqueue(Algorithm.K_NearestNeighbor);
                if (this.m_bUseNearestCentroid) this.enabledAlgorithms.Enqueue(Algorithm.NearestCentroid);
                this.Algorithm = this.enabledAlgorithms.Dequeue();
                this.Neighbors = this.MinNeighbors;
            }
        }

        public override ulong NumCombinations
        {
            get
            {
                ulong combinations = 0;
                if (this.m_bUseNearestNeighbor) combinations++;
                if (this.m_bUseKNearestNeighbor) combinations++;
                if (this.m_bUseNearestCentroid) combinations++;
                return combinations * base.NumCombinations;
            }
        }
        public override string SelectionHeader
        {
            get { return ", Algorithm" + base.SelectionHeader; }
        }
        public override string SelectionValue
        {
            get { return ", " + this.Classifier.AlgorithmAbbreviation[this.Algorithm] + base.SelectionValue; }
        }

        [XmlIgnore]
        public Algorithm Algorithm
        {
            get { return this.m_Classifier.Algorithm; }
            set { this.m_Classifier.Algorithm = value; }
        }
        [XmlIgnore]
        public int Neighbors
        {
            get { return this.m_Classifier.Neighbors; }
            set { this.m_Classifier.Neighbors = value; }
        }
        public int MinNeighbors
        {
            get { return this.m_nMinNeighbors; }
            set { this.m_nMinNeighbors = value; }
        }
        public int MaxNeighbors
        {
            get { return this.m_nMaxNeighbors; }
            set { this.m_nMaxNeighbors = value; }
        }
        public bool IncludeNearestNeighbor
        {
            get { return this.m_bUseNearestNeighbor; }
            set { this.m_bUseNearestNeighbor = value; }
        }
        public bool IncludeKNearestNeighbor
        {
            get { return this.m_bUseKNearestNeighbor; }
            set { this.m_bUseKNearestNeighbor = value; }
        }
        public bool IncludeNearestCentroid
        {
            get { return this.m_bUseNearestCentroid; }
            set { this.m_bUseNearestCentroid = value; }
        }
    }
    public class DistanceChooser : ClassifierChooser
    {
        Queue<Distance> enabledDistances = new Queue<Distance>();

        bool m_bUseCityBlock = false;
        bool m_bUseEuclidean = true;
        bool m_bUseMaxValue = false;
        bool m_bUseMinkowski = false;
        bool m_bUseTanimoto = false;
        bool m_bUseVIP = false;
        float m_fMinkowskiIncrement = 1.0f;
        float m_fMinkowskiMin = 3.0f;
        float m_fMinkowskiMax = 3.0f;

        public DistanceChooser() { }
        public DistanceChooser(DistanceChooser chooser)
            : base((ClassifierChooser)chooser)
        {
            this.m_bUseCityBlock = chooser.m_bUseCityBlock;
            this.m_bUseEuclidean = chooser.m_bUseEuclidean;
            this.m_bUseMaxValue = chooser.m_bUseMaxValue;
            this.m_bUseMinkowski = chooser.m_bUseMinkowski;
            this.m_bUseTanimoto = chooser.m_bUseTanimoto;
            this.m_bUseVIP = chooser.m_bUseVIP;
            this.m_fMinkowskiIncrement = chooser.m_fMinkowskiIncrement;
            this.m_fMinkowskiMin = chooser.m_fMinkowskiMin;
            this.m_fMinkowskiMax = chooser.m_fMinkowskiMax;
        }
        public override bool Equals(object obj)
        {
            return (Equals(obj as DistanceChooser));
        }
        public bool Equals(DistanceChooser chooser)
        {
            return base.Equals(chooser) &&
                (this.m_bUseCityBlock == chooser.m_bUseCityBlock) &&
                (this.m_bUseEuclidean == chooser.m_bUseEuclidean) &&
                (this.m_bUseMaxValue == chooser.m_bUseMaxValue) &&
                (this.m_bUseMinkowski == chooser.m_bUseMinkowski) &&
                (this.m_bUseTanimoto == chooser.m_bUseTanimoto) &&
                (this.m_bUseVIP == chooser.m_bUseVIP) &&
                (this.m_fMinkowskiIncrement == chooser.m_fMinkowskiIncrement) &&
                (this.m_fMinkowskiMin == chooser.m_fMinkowskiMin) &&
                (this.m_fMinkowskiMax == chooser.m_fMinkowskiMax);
        }
        public override int GetHashCode()
        {
            return base.GetHashCode();
        }
        public override bool Increment()
        {
            bool carry = base.Increment();
            if (carry && !this.Locked)
            {
                if (this.Distance == Distance.Minkowski)
                {
                    this.Minkowski += this.MinkowskiIncrement;
                    if (carry = (this.Minkowski > this.MinkowskiMax))
                        this.Minkowski = this.MinkowskiMin;
                }
                if (carry)
                {
                    if (carry = (this.enabledDistances.Count == 0))
                    {
                        if (this.m_bUseCityBlock) this.enabledDistances.Enqueue(Distance.CityBlock);
                        if (this.m_bUseEuclidean) this.enabledDistances.Enqueue(Distance.Euclidean);
                        if (this.m_bUseMaxValue) this.enabledDistances.Enqueue(Distance.MaxValue);
                        if (this.m_bUseMinkowski) this.enabledDistances.Enqueue(Distance.Minkowski);
                        if (this.m_bUseTanimoto) this.enabledDistances.Enqueue(Distance.Tanimoto);
                        if (this.m_bUseVIP) this.enabledDistances.Enqueue(Distance.VectorInnerProduct);
                    }
                    this.Distance = this.enabledDistances.Dequeue();
                }
            }
            return carry;
        }
        public override void Reset()
        {
            base.Reset();
            if (!this.Locked)
            {
                this.enabledDistances.Clear();
                if (this.m_bUseCityBlock) this.enabledDistances.Enqueue(Distance.CityBlock);
                if (this.m_bUseEuclidean) this.enabledDistances.Enqueue(Distance.Euclidean);
                if (this.m_bUseMaxValue) this.enabledDistances.Enqueue(Distance.MaxValue);
                if (this.m_bUseMinkowski) this.enabledDistances.Enqueue(Distance.Minkowski);
                if (this.m_bUseTanimoto) this.enabledDistances.Enqueue(Distance.Tanimoto);
                if (this.m_bUseVIP) this.enabledDistances.Enqueue(Distance.VectorInnerProduct);
                this.Distance = this.enabledDistances.Dequeue();
                this.Minkowski = this.MinkowskiMin;
            }
        }

        public override ulong NumCombinations
        {
            get
            {
                ulong combinations = 0;
                if (this.m_bUseCityBlock) combinations++;
                if (this.m_bUseEuclidean) combinations++;
                if (this.m_bUseMaxValue) combinations++;
                if (this.m_bUseMinkowski) combinations++;
                if (this.m_bUseTanimoto) combinations++;
                if (this.m_bUseVIP) combinations++;
                return combinations * base.NumCombinations;
            }
        }
        public override string SelectionHeader
        {
            get { return ", Distance" + base.SelectionHeader; }
        }
        public override string SelectionValue
        {
            get { return ", " + this.Classifier.DistanceAbbreviation[this.Distance] + base.SelectionValue; }
        }

        [XmlIgnore]
        public Distance Distance
        {
            get { return this.m_Classifier.Distance; }
            set { this.m_Classifier.Distance = value; }
        }
        [XmlIgnore]
        public float Minkowski
        {
            get { return this.m_Classifier.Minkowski; }
            set { this.m_Classifier.Minkowski = value; }
        }
        public float MinkowskiIncrement
        {
            get { return this.m_fMinkowskiIncrement; }
            set { this.m_fMinkowskiIncrement = value; }
        }
        public float MinkowskiMin
        {
            get { return this.m_fMinkowskiMin; }
            set { this.m_fMinkowskiMin = value; }
        }
        public float MinkowskiMax
        {
            get { return this.m_fMinkowskiMax; }
            set { this.m_fMinkowskiMax = value; }
        }
        public bool IncludeCityBlock
        {
            get { return this.m_bUseCityBlock; }
            set { this.m_bUseCityBlock = value; }
        }
        public bool IncludeEuclidean
        {
            get { return this.m_bUseEuclidean; }
            set { this.m_bUseEuclidean = value; }
        }
        public bool IncludeMaxValue
        {
            get { return this.m_bUseMaxValue; }
            set { this.m_bUseMaxValue = value; }
        }
        public bool IncludeMinkowski
        {
            get { return this.m_bUseMinkowski; }
            set { this.m_bUseMinkowski = value; }
        }
        public bool IncludeTanimoto
        {
            get { return this.m_bUseTanimoto; }
            set { this.m_bUseTanimoto = value; }
        }
        public bool IncludeVIP
        {
            get { return this.m_bUseVIP; }
            set { this.m_bUseVIP = value; }
        }
    }
    public class NormalizationChooser : ClassifierChooser
    {
        Queue<Normalization> enabledNormalizations = new Queue<Normalization>();

        bool m_bUseNone = true;
        bool m_bUseMinMax = false;
        bool m_bUseRange = false;
        bool m_bUseSoftmax = false;
        bool m_bUseStdNormal = false;
        bool m_bUseUnitVector = false;
        float m_fSMaxIncrement = 0.5f;
        float m_fSMaxMin = 1.0f;
        float m_fSMaxMax = 1.0f;
        float m_fSMinIncrement = 0.5f;
        float m_fSMinMin = 0.0f;
        float m_fSMinMax = 0.0f;
        float m_fSoftmaxIncrement = 0.5f;
        float m_fSoftmaxMin = 1.0f;
        float m_fSoftmaxMax = 1.0f;

        public NormalizationChooser() { }
        public NormalizationChooser(NormalizationChooser chooser)
            : base((ClassifierChooser)chooser)
        {
            this.m_bUseNone = chooser.m_bUseNone;
            this.m_bUseMinMax = chooser.m_bUseMinMax;
            this.m_bUseRange = chooser.m_bUseRange;
            this.m_bUseSoftmax = chooser.m_bUseSoftmax;
            this.m_bUseStdNormal = chooser.m_bUseStdNormal;
            this.m_bUseUnitVector = chooser.m_bUseUnitVector;
            this.m_fSMaxIncrement = chooser.m_fSMaxIncrement;
            this.m_fSMaxMin = chooser.m_fSMaxMin;
            this.m_fSMaxMax = chooser.m_fSMaxMax;
            this.m_fSMinIncrement = chooser.m_fSMinIncrement;
            this.m_fSMinMin = chooser.m_fSMinMin;
            this.m_fSMinMax = chooser.m_fSMinMax;
            this.m_fSoftmaxIncrement = chooser.m_fSoftmaxIncrement;
            this.m_fSoftmaxMin = chooser.m_fSoftmaxMin;
            this.m_fSoftmaxMax = chooser.m_fSoftmaxMax;
        }
        public override bool Equals(object obj)
        {
            return (Equals(obj as NormalizationChooser));
        }
        public bool Equals(NormalizationChooser chooser)
        {
            return base.Equals(chooser) &&
                (this.m_bUseNone == chooser.m_bUseNone) &&
                (this.m_bUseMinMax == chooser.m_bUseMinMax) &&
                (this.m_bUseRange == chooser.m_bUseRange) &&
                (this.m_bUseSoftmax == chooser.m_bUseSoftmax) &&
                (this.m_bUseStdNormal == chooser.m_bUseStdNormal) &&
                (this.m_bUseUnitVector == chooser.m_bUseUnitVector) &&
                (this.m_fSMaxIncrement == chooser.m_fSMaxIncrement) &&
                (this.m_fSMaxMin == chooser.m_fSMaxMin) &&
                (this.m_fSMaxMax == chooser.m_fSMaxMax) &&
                (this.m_fSMinIncrement == chooser.m_fSMinIncrement) &&
                (this.m_fSMinMin == chooser.m_fSMinMin) &&
                (this.m_fSMinMax == chooser.m_fSMinMax) &&
                (this.m_fSoftmaxIncrement == chooser.m_fSoftmaxIncrement) &&
                (this.m_fSoftmaxMin == chooser.m_fSoftmaxMin) &&
                (this.m_fSoftmaxMax == chooser.m_fSoftmaxMax);
        }
        public override int GetHashCode()
        {
            return base.GetHashCode();
        }
        public override bool Increment()
        {
            bool carry = base.Increment();
            if (carry && !this.Locked)
            {
                switch (this.Normalization)
                {
                case Normalization.MinMax:
                    this.SMax += this.SMaxIncrement;
                    if (carry = (this.SMax > this.SMaxMax))
                    {
                        this.SMin += this.SMinIncrement;
                        for (this.SMax = this.SMaxMin; this.SMax <= this.SMin; this.SMax += this.SMaxIncrement) ;
                        if (carry = ((this.SMin > this.SMinMax) || (this.SMax > this.SMaxMax)))
                        {
                            this.SMin = this.SMinMin;
                            this.SMax = this.SMaxMin;
                        }
                    }
                    break;
                case Normalization.Softmax:
                    this.Softmax += this.SoftmaxIncrement;
                    if (carry = (this.Softmax > this.SoftmaxMax))
                        this.Softmax = this.SoftmaxMin;
                    break;
                }
                if (carry)
                {
                    if (carry = (this.enabledNormalizations.Count == 0))
                    {
                        if (this.m_bUseNone) this.enabledNormalizations.Enqueue(Normalization.None);
                        if (this.m_bUseMinMax) this.enabledNormalizations.Enqueue(Normalization.MinMax);
                        if (this.m_bUseRange) this.enabledNormalizations.Enqueue(Normalization.Range);
                        if (this.m_bUseSoftmax) this.enabledNormalizations.Enqueue(Normalization.Softmax);
                        if (this.m_bUseStdNormal) this.enabledNormalizations.Enqueue(Normalization.StdNormal);
                        if (this.m_bUseUnitVector) this.enabledNormalizations.Enqueue(Normalization.UnitVector);
                    }
                    this.Normalization = this.enabledNormalizations.Dequeue();
                }
            }
            return carry;
        }
        public override void Reset()
        {
            base.Reset();
            if (!this.Locked)
            {
                this.enabledNormalizations.Clear();
                if (this.m_bUseNone) this.enabledNormalizations.Enqueue(Normalization.None);
                if (this.m_bUseMinMax) this.enabledNormalizations.Enqueue(Normalization.MinMax);
                if (this.m_bUseRange) this.enabledNormalizations.Enqueue(Normalization.Range);
                if (this.m_bUseSoftmax) this.enabledNormalizations.Enqueue(Normalization.Softmax);
                if (this.m_bUseStdNormal) this.enabledNormalizations.Enqueue(Normalization.StdNormal);
                if (this.m_bUseUnitVector) this.enabledNormalizations.Enqueue(Normalization.UnitVector);
                this.Normalization = this.enabledNormalizations.Dequeue();
                this.SMax = this.SMaxMin;
                this.SMin = this.SMinMin;
                this.Softmax = this.SoftmaxMin;
            }
        }

        public override ulong NumCombinations
        {
            get
            {
                ulong combinations = 0;
                if (this.m_bUseNone) combinations++;
                if (this.m_bUseMinMax) combinations++;
                if (this.m_bUseRange) combinations++;
                if (this.m_bUseSoftmax) combinations++;
                if (this.m_bUseStdNormal) combinations++;
                if (this.m_bUseUnitVector) combinations++;
                return combinations * base.NumCombinations;
            }
        }
        public override string SelectionHeader
        {
            get { return ", Normalization" + base.SelectionHeader; }
        }
        public override string SelectionValue
        {
            get { return ", " + this.Classifier.NormalizationAbbreviation[this.Normalization] + base.SelectionValue; }
        }

        [XmlIgnore]
        public Normalization Normalization
        {
            get { return this.m_Classifier.Normalization; }
            set { this.m_Classifier.Normalization = value; }
        }
        [XmlIgnore]
        public float SMax
        {
            get { return this.m_Classifier.SMax; }
            set { this.m_Classifier.SMax = value; }
        }
        public float SMaxIncrement
        {
            get { return this.m_fSMaxIncrement; }
            set { this.m_fSMaxIncrement = value; }
        }
        public float SMaxMin
        {
            get { return this.m_fSMaxMin; }
            set { this.m_fSMaxMin = value; }
        }
        public float SMaxMax
        {
            get { return this.m_fSMaxMax; }
            set { this.m_fSMaxMax = value; }
        }
        [XmlIgnore]
        public float SMin
        {
            get { return this.m_Classifier.SMin; }
            set { this.m_Classifier.SMin = value; }
        }
        public float SMinIncrement
        {
            get { return this.m_fSMinIncrement; }
            set { this.m_fSMinIncrement = value; }
        }
        public float SMinMin
        {
            get { return this.m_fSMinMin; }
            set { this.m_fSMinMin = value; }
        }
        public float SMinMax
        {
            get { return this.m_fSMinMax; }
            set { this.m_fSMinMax = value; }
        }
        [XmlIgnore]
        public float Softmax
        {
            get { return this.m_Classifier.Softmax; }
            set { this.m_Classifier.Softmax = value; }
        }
        public float SoftmaxIncrement
        {
            get { return this.m_fSoftmaxIncrement; }
            set { this.m_fSoftmaxIncrement = value; }
        }
        public float SoftmaxMin
        {
            get { return this.m_fSoftmaxMin; }
            set { this.m_fSoftmaxMin = value; }
        }
        public float SoftmaxMax
        {
            get { return this.m_fSoftmaxMax; }
            set { this.m_fSoftmaxMax = value; }
        }
        public bool IncludeNone
        {
            get { return this.m_bUseNone; }
            set { this.m_bUseNone = value; }
        }
        public bool IncludeMinMax
        {
            get { return this.m_bUseMinMax; }
            set { this.m_bUseMinMax = value; }
        }
        public bool IncludeRange
        {
            get { return this.m_bUseRange; }
            set { this.m_bUseRange = value; }
        }
        public bool IncludeSoftmax
        {
            get { return this.m_bUseSoftmax; }
            set { this.m_bUseSoftmax = value; }
        }
        public bool IncludeStdNorm
        {
            get { return this.m_bUseStdNormal; }
            set { this.m_bUseStdNormal = value; }
        }
        public bool IncludeUnitVec
        {
            get { return this.m_bUseUnitVector; }
            set { this.m_bUseUnitVector = value; }
        }
    }
}
