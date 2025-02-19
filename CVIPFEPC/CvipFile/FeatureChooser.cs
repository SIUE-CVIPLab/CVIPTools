/*''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' ======================================================================
' Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
' ======================================================================
'
'             File Name: FeatureChooser.cs
'           Description: Contains the code for
'                        FeatureChooser class
'         Related Files: FeatureHeader.cs
'   Initial Coding Date: August 2007
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
    public abstract class FeatureChooser
    {
        protected bool m_bLocked = false;
        protected FeatureChooser m_chooserNext = null;
        protected FeatureHeader m_hdrFeatures = null;

        protected FeatureChooser() { }
        protected FeatureChooser(FeatureChooser fc) { this.m_bLocked = fc.m_bLocked; }
        public virtual void AllOn()
        {
            if (this.m_chooserNext != null) this.m_chooserNext.AllOn();
        }
        public virtual void Append(FeatureChooser fc)
        {
            if (fc != null)
            {
                FeatureChooser current = this;
                while (current.m_chooserNext != null) current = current.m_chooserNext;
                current.m_chooserNext = fc;
                fc.FeatureHeader = this.FeatureHeader;
            }
        }
        public override bool Equals(object obj)
        {
            return (Equals(obj as FeatureChooser));
        }
        public bool Equals(FeatureChooser fc)
        {
            return ((object)fc != null) &&
                (this.m_bLocked == fc.m_bLocked);
        }
        public override int GetHashCode()
        {
            return base.GetHashCode();
        }
        public virtual bool Increment()
        {
            return (this.m_chooserNext != null) ? this.m_chooserNext.Increment() : true;
        }
        public virtual void Reset()
        {
            if (this.m_chooserNext != null) this.m_chooserNext.Reset();
        }

        public bool Locked
        {
            get { return this.m_bLocked; }
            set { this.m_bLocked = value; }
        }
        [XmlIgnore]
        public virtual FeatureHeader FeatureHeader
        {
            get { return this.m_hdrFeatures; }
            set { this.m_hdrFeatures = value; }
        }
        public virtual ulong NumCombinations
        {
            get { return (this.m_chooserNext != null) ? this.m_chooserNext.NumCombinations : 1; }
        }
        public virtual string SelectionHeader
        {
            get { return (this.m_chooserNext != null) ? this.m_chooserNext.SelectionHeader : null; }
           
        }
        public virtual string SelectionValue
        {
            get { return (this.m_chooserNext != null) ? this.m_chooserNext.SelectionValue : null; } 
        }
    }
    public class BinaryChooser : FeatureChooser
    {
        bool m_bUseAreaLocked = false;
        bool m_bUseAspectLocked = false;
        bool m_bUseCentroidLocked = false;
        bool m_bUseEulerLocked = false;
        bool m_bUseOrientationLocked = false;
        bool m_bUsePerimeterLocked = false;
        bool m_bUseProjectionsLocked = false;
        bool m_bUseThinnessLocked = false;
        int com ;

        public BinaryChooser() { }
        public BinaryChooser(BinaryChooser bc)
            : base((FeatureChooser)bc)
        {
            this.m_bUseAreaLocked = bc.m_bUseAreaLocked;
            this.m_bUseAspectLocked = bc.m_bUseAspectLocked;
            this.m_bUseCentroidLocked = bc.m_bUseCentroidLocked;
            this.m_bUseEulerLocked = bc.m_bUseEulerLocked;
            this.m_bUseOrientationLocked = bc.m_bUseOrientationLocked;
            this.m_bUsePerimeterLocked = bc.m_bUsePerimeterLocked;
            this.m_bUseProjectionsLocked = bc.m_bUseProjectionsLocked;
            this.m_bUseThinnessLocked = bc.m_bUseThinnessLocked;
        }
        public override void AllOn()
        {
            base.AllOn();
            if (!this.Locked)
            {
                if (!this.UseAreaLocked) this.UseArea = true;
                if (!this.UseCentroidLocked) this.UseCentroid = true;
                if (!this.UseOrientationLocked) this.UseOrientation = true;
                if (!this.UsePerimeterLocked) this.UsePerimeter = true;
                if (!this.UseEulerLocked) this.UseEuler = true;
                if (!this.UseProjectionsLocked) this.UseProjections = true;
                if (!this.UseThinnessLocked) this.UseThinness = true;
                if (!this.UseAspectRatioLocked) this.UseAspectRatio = true;
            }
        }
        public override bool Equals(object obj)
        {
            return (Equals(obj as BinaryChooser));
        }
        public bool Equals(BinaryChooser bc)
        {
            return base.Equals(bc) &&
                (this.m_bUseAreaLocked == bc.m_bUseAreaLocked) &&
                (this.m_bUseAspectLocked == bc.m_bUseAspectLocked) &&
                (this.m_bUseCentroidLocked == bc.m_bUseCentroidLocked) &&
                (this.m_bUseEulerLocked == bc.m_bUseEulerLocked) &&
                (this.m_bUseOrientationLocked == bc.m_bUseOrientationLocked) &&
                (this.m_bUsePerimeterLocked == bc.m_bUsePerimeterLocked) &&
                (this.m_bUseProjectionsLocked == bc.m_bUseProjectionsLocked) &&
                (this.m_bUseThinnessLocked == bc.m_bUseThinnessLocked);
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
                if (carry && !this.UseAspectRatioLocked)
                {
                    this.UseAspectRatio = !this.UseAspectRatio;
                    carry = !this.UseAspectRatio;
                }
                if (carry && !this.UseThinnessLocked)
                {
                    this.UseThinness = !this.UseThinness;
                    carry = !this.UseThinness;
                }
                if (carry && !this.UseProjectionsLocked)
                {
                    this.UseProjections = !this.UseProjections;
                    carry = !this.UseProjections;
                }
                if (carry && !this.UseEulerLocked)
                {
                    this.UseEuler = !this.UseEuler;
                    carry = !this.UseEuler;
                }
                if (carry && !this.UsePerimeterLocked)
                {
                    this.UsePerimeter = !this.UsePerimeter;
                    carry = !this.UsePerimeter;
                }
                if (carry && !this.UseOrientationLocked)
                {
                    this.UseOrientation = !this.UseOrientation;
                    carry = !this.UseOrientation;
                }
                if (carry && !this.UseCentroidLocked)
                {
                    this.UseCentroid = !this.UseCentroid;
                    carry = !this.UseCentroid;
                }
                if (carry && !this.UseAreaLocked)
                {
                    this.UseArea = !this.UseArea;
                    carry = !this.UseArea;
                }
            }
            return carry;
        }
        public override void Reset()
        {
            base.Reset();
            if (!this.Locked)
            {
                if (!this.UseAreaLocked) this.UseArea = false;
                if (!this.UseCentroidLocked) this.UseCentroid = false;
                if (!this.UseOrientationLocked) this.UseOrientation = false;
                if (!this.UsePerimeterLocked) this.UsePerimeter = false;
                if (!this.UseEulerLocked) this.UseEuler = false;
                if (!this.UseProjectionsLocked) this.UseProjections = false;
                if (!this.UseThinnessLocked) this.UseThinness = false;
                if (!this.UseAspectRatioLocked) this.UseAspectRatio = false;
            }
        }

        public override FeatureHeader FeatureHeader
        {
            get { return base.FeatureHeader; }
            set
            {
                base.FeatureHeader = value;
                if (value != null)
                {
                    this.UseAreaLocked = !value.UseArea;
                    this.UseAspectRatioLocked = !value.UseAspectRatio;
                    this.UseCentroidLocked = !value.UseCentroid;
                    this.UseEulerLocked = !value.UseEuler;
                    this.UseOrientationLocked = !value.UseOrientation;
                    this.UsePerimeterLocked = !value.UsePerimeter;
                    this.UseProjectionsLocked = !value.UseProjections;
                    this.UseThinnessLocked = !value.UseThinness;
                }
            }
        }
        public override ulong NumCombinations
        {
            get
            {
                ulong combinations = base.NumCombinations;
                if (!this.UseAreaLocked) combinations *= 2;
                if (!this.UseCentroidLocked) combinations *= 2;
                if (!this.UseOrientationLocked) combinations *= 2;
                if (!this.UsePerimeterLocked) combinations *= 2;
                if (!this.UseEulerLocked) combinations *= 2;
                if (!this.UseProjectionsLocked) combinations *= 2;
                if (!this.UseThinnessLocked) combinations *= 2;
                if (!this.UseAspectRatioLocked) combinations *= 2;
                return combinations;
            }
        }
        public override string SelectionHeader
        {
            get
            {
                string hdr = "";
                if (this.UseArea || !this.UseAreaLocked) hdr += ", Area";
                if (this.UseCentroid || !this.UseCentroidLocked) hdr += ", Centroid";
                if (this.UseOrientation || !this.UseOrientationLocked) hdr += ", Orientation";
                if (this.UsePerimeter || !this.UsePerimeterLocked) hdr += ", Perimeter";
                if (this.UseEuler || !this.UseEulerLocked) hdr += ", Euler";
                if (this.UseProjections || !this.UseProjectionsLocked) hdr += ", Projections";
                if (this.UseThinness || !this.UseThinnessLocked) hdr += ", Thinness";
                if (this.UseAspectRatio || !this.UseAspectRatioLocked) hdr += ", AspectRatio";
                return hdr + base.SelectionHeader;
            }
          
        }
        public override string SelectionValue
        {
            get
            {
                string val = "";
                if (this.UseArea || !this.UseAreaLocked)
                {
                    val += ", ";
                    if (this.UseArea) val += "X";
                }
                if (this.UseCentroid || !this.UseCentroidLocked)
                {
                    val += ", ";
                    if (this.UseCentroid) val += "X";
                }
                if (this.UseOrientation || !this.UseOrientationLocked)
                {
                    val += ", ";
                    if (this.UseOrientation) val += "X";
                }
                if (this.UsePerimeter || !this.UsePerimeterLocked)
                {
                    val += ", ";
                    if (this.UsePerimeter) val += "X";
                }
                if (this.UseEuler || !this.UseEulerLocked)
                {
                    val += ", ";
                    if (this.UseEuler) val += "X";
                }
                if (this.UseProjections || !this.UseProjectionsLocked)
                {
                    val += ", ";
                    if (this.UseProjections) val += "X";
                }
                if (this.UseThinness || !this.UseThinnessLocked)
                {
                    val += ", ";
                    if (this.UseThinness) val += "X";
                }
                if (this.UseAspectRatio || !this.UseAspectRatioLocked)
                {
                    val += ", ";
                    if (this.UseAspectRatio) val += "X";
                }
                return val + base.SelectionValue;
            }
        
        }

        [XmlIgnore]
        public bool UseArea
        {
            get { return this.m_hdrFeatures.UseArea; }
            set { this.m_hdrFeatures.UseArea = value; }
        }
        public bool UseAreaLocked
        {
            get { return (this.m_bUseAreaLocked || this.Locked); }
            set { this.m_bUseAreaLocked = value; }
        }
        [XmlIgnore]
        public bool UseAspectRatio
        {
            get { return this.m_hdrFeatures.UseAspectRatio; }
            set { this.m_hdrFeatures.UseAspectRatio = value; }
        }
        public bool UseAspectRatioLocked
        {
            get { return (this.m_bUseAspectLocked || this.Locked); }
            set { this.m_bUseAspectLocked = value; }
        }
        [XmlIgnore]
        public bool UseCentroid
        {
            get { return this.m_hdrFeatures.UseCentroid; }
            set { this.m_hdrFeatures.UseCentroid = value; }
        }
        public bool UseCentroidLocked
        {
            get { return (this.m_bUseCentroidLocked || this.Locked); }
            set { this.m_bUseCentroidLocked = value; }
        }
        [XmlIgnore]
        public bool UseEuler
        {
            get { return this.m_hdrFeatures.UseEuler; }
            set { this.m_hdrFeatures.UseEuler = value; }
        }
        public bool UseEulerLocked
        {
            get { return (this.m_bUseEulerLocked || this.Locked); }
            set { this.m_bUseEulerLocked = value; }
        }
        [XmlIgnore]
        public bool UseOrientation
        {
            get { return this.m_hdrFeatures.UseOrientation; }
            set { this.m_hdrFeatures.UseOrientation = value; }
        }
        public bool UseOrientationLocked
        {
            get { return (this.m_bUseOrientationLocked || this.Locked); }
            set { this.m_bUseOrientationLocked = value; }
        }
        [XmlIgnore]
        public bool UsePerimeter
        {
            get { return this.m_hdrFeatures.UsePerimeter; }
            set { this.m_hdrFeatures.UsePerimeter = value; }
        }
        public bool UsePerimeterLocked
        {
            get { return (this.m_bUsePerimeterLocked || this.Locked); }
            set { this.m_bUsePerimeterLocked = value; }
        }
        [XmlIgnore]
        public bool UseProjections
        {
            get { return this.m_hdrFeatures.UseProjections; }
            set { this.m_hdrFeatures.UseProjections = value; }
        }
        public bool UseProjectionsLocked
        {
            get { return (this.m_bUseProjectionsLocked || this.Locked); }
            set { this.m_bUseProjectionsLocked = value; }
        }
        [XmlIgnore]
        public bool UseThinness
        {
            get { return this.m_hdrFeatures.UseThinness; }
            set { this.m_hdrFeatures.UseThinness = value; }
        }
        public bool UseThinnessLocked
        {
            get { return (this.m_bUseThinnessLocked || this.Locked); }
            set { this.m_bUseThinnessLocked = value; }
        }
    }
    public class HistogramChooser : FeatureChooser
    {
        bool m_bUseEnergyLocked = false;
        bool m_bUseEntropyLocked = false;
        bool m_bUseMeanLocked = false;
        bool m_bUseSkewLocked = false;
        bool m_bUseStdDevLocked = false;

        public HistogramChooser() { }
        public HistogramChooser(HistogramChooser hc)
            : base((FeatureChooser)hc)
        {
            this.m_bUseEnergyLocked = hc.m_bUseEnergyLocked;
            this.m_bUseEntropyLocked = hc.m_bUseEntropyLocked;
            this.m_bUseMeanLocked = hc.m_bUseMeanLocked;
            this.m_bUseSkewLocked = hc.m_bUseSkewLocked;
            this.m_bUseStdDevLocked = hc.m_bUseStdDevLocked;
        }
        public override void AllOn()
        {
            base.AllOn();
            if (!this.Locked)
            {
                if (!this.UseMeanLocked) this.UseMean = true;
                if (!this.UseStdDevLocked) this.UseStdDev = true;
                if (!this.UseSkewLocked) this.UseSkew = true;
                if (!this.UseEnergyLocked) this.UseEnergy = true;
                if (!this.UseEntropyLocked) this.UseEntropy = true;
            }
        }
        public override bool Equals(object obj)
        {
            return (Equals(obj as HistogramChooser));
        }
        public bool Equals(HistogramChooser hc)
        {
            return base.Equals(hc) &&
                (this.m_bUseEnergyLocked == hc.m_bUseEnergyLocked) &&
                (this.m_bUseEntropyLocked == hc.m_bUseEntropyLocked) &&
                (this.m_bUseMeanLocked == hc.m_bUseMeanLocked) &&
                (this.m_bUseSkewLocked == hc.m_bUseSkewLocked) &&
                (this.m_bUseStdDevLocked == hc.m_bUseStdDevLocked);
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
                if (carry && !this.UseEntropyLocked)
                {
                    this.UseEntropy = !this.UseEntropy;
                    carry = !this.UseEntropy;
                }
                if (carry && !this.UseEnergyLocked)
                {
                    this.UseEnergy = !this.UseEnergy;
                    carry = !this.UseEnergy;
                }
                if (carry && !this.UseSkewLocked)
                {
                    this.UseSkew = !this.UseSkew;
                    carry = !this.UseSkew;
                }
                if (carry && !this.UseStdDevLocked)
                {
                    this.UseStdDev = !this.UseStdDev;
                    carry = !this.UseStdDev;
                }
                if (carry && !this.UseMeanLocked)
                {
                    this.UseMean = !this.UseMean;
                    carry = !this.UseMean;
                }
            }
            return carry;
        }
        public override void Reset()
        {
            base.Reset();
            if (!this.Locked)
            {
                if (!this.UseMeanLocked) this.UseMean = false;
                if (!this.UseStdDevLocked) this.UseStdDev = false;
                if (!this.UseSkewLocked) this.UseSkew = false;
                if (!this.UseEnergyLocked) this.UseEnergy = false;
                if (!this.UseEntropyLocked) this.UseEntropy = false;
            }
        }

        public override FeatureHeader FeatureHeader
        {
            get { return base.FeatureHeader; }
            set
            {
                base.FeatureHeader = value;
                if (value != null)
                {
                    this.UseEnergyLocked = !value.UseHistEnergy;
                    this.UseEntropyLocked = !value.UseHistEntropy;
                    this.UseMeanLocked = !value.UseHistMean;
                    this.UseSkewLocked = !value.UseHistSkew;
                    this.UseStdDevLocked = !value.UseHistStdDev;
                }
            }
        }
        public override ulong NumCombinations
        {
            get
            {
                ulong combinations = base.NumCombinations;
                if (!this.UseMeanLocked) combinations *= 2;
                if (!this.UseStdDevLocked) combinations *= 2;
                if (!this.UseSkewLocked) combinations *= 2;
                if (!this.UseEnergyLocked) combinations *= 2;
                if (!this.UseEntropyLocked) combinations *= 2;
                return combinations;
            }
        }
        public override string SelectionHeader
        {
            get
            {
                string hdr = "";
                if (this.UseMean || !this.UseMeanLocked) hdr += ", HistMean";
                if (this.UseStdDev || !this.UseStdDevLocked) hdr += ", HistStdDev";
                if (this.UseSkew || !this.UseSkewLocked) hdr += ", HistSkew";
                if (this.UseEnergy || !this.UseEnergyLocked) hdr += ", HistEnergy";
                if (this.UseEntropy || !this.UseEntropyLocked) hdr += ", HistEntropy";
                return hdr + base.SelectionHeader;
            }
           
        }
        public override string SelectionValue
        {
            get
            {
                string val = "";
                if (this.UseMean || !this.UseMeanLocked)
                {
                    val += ", ";
                    if (this.UseMean) val += "X";
                }
                if (this.UseStdDev || !this.UseStdDevLocked)
                {
                    val += ", ";
                    if (this.UseStdDev) val += "X";
                }
                if (this.UseSkew || !this.UseSkewLocked)
                {
                    val += ", ";
                    if (this.UseSkew) val += "X";
                }
                if (this.UseEnergy || !this.UseEnergyLocked)
                {
                    val += ", ";
                    if (this.UseEnergy) val += "X";
                }
                if (this.UseEntropy || !this.UseEntropyLocked)
                {
                    val += ", ";
                    if (this.UseEntropy) val += "X";
                }
                return val + base.SelectionValue;
            }
          
        }

        [XmlIgnore]
        public bool UseEnergy
        {
            get { return this.m_hdrFeatures.UseHistEnergy; }
            set { this.m_hdrFeatures.UseHistEnergy = value; }
        }
        public bool UseEnergyLocked
        {
            get { return (this.m_bUseEnergyLocked || this.Locked); }
            set { this.m_bUseEnergyLocked = value; }
        }
        [XmlIgnore]
        public bool UseEntropy
        {
            get { return this.m_hdrFeatures.UseHistEntropy; }
            set { this.m_hdrFeatures.UseHistEntropy = value; }
        }
        public bool UseEntropyLocked
        {
            get { return (this.m_bUseEntropyLocked || this.Locked); }
            set { this.m_bUseEntropyLocked = value; }
        }
        [XmlIgnore]
        public bool UseMean
        {
            get { return this.m_hdrFeatures.UseHistMean; }
            set { this.m_hdrFeatures.UseHistMean = value; }
        }
        public bool UseMeanLocked
        {
            get { return (this.m_bUseMeanLocked || this.Locked); }
            set { this.m_bUseMeanLocked = value; }
        }
        [XmlIgnore]
        public bool UseSkew
        {
            get { return this.m_hdrFeatures.UseHistSkew; }
            set { this.m_hdrFeatures.UseHistSkew = value; }
        }
        public bool UseSkewLocked
        {
            get { return (this.m_bUseSkewLocked || this.Locked); }
            set { this.m_bUseSkewLocked = value; }
        }
        [XmlIgnore]
        public bool UseStdDev
        {
            get { return this.m_hdrFeatures.UseHistStdDev; }
            set { this.m_hdrFeatures.UseHistStdDev = value; }
        }
        public bool UseStdDevLocked
        {
            get { return (this.m_bUseStdDevLocked || this.Locked); }
            set { this.m_bUseStdDevLocked = value; }
        }
    }
    public class RstChooser : FeatureChooser
    {
        bool[] m_bUseRstLocked = new bool[7];

        public RstChooser() { }
        public RstChooser(RstChooser rc)
            : base((FeatureChooser)rc)
        {
            for (int i = 0; i < 7; i++)
                this.m_bUseRstLocked[i] = rc.m_bUseRstLocked[i];
        }
        public override void AllOn()
        {
            base.AllOn();
            if (!this.Locked)
            {
                for (int i = 0; i < 7; i++)
                    if (!this.UseRstLocked[i]) this.UseRst[i] = true;
            }
        }
        public override bool Equals(object obj)
        {
            return (Equals(obj as RstChooser));
        }
        public bool Equals(RstChooser rc)
        {
            return base.Equals(rc) &&
                (this.m_bUseRstLocked[0] == rc.m_bUseRstLocked[0]) &&
                (this.m_bUseRstLocked[1] == rc.m_bUseRstLocked[1]) &&
                (this.m_bUseRstLocked[2] == rc.m_bUseRstLocked[2]) &&
                (this.m_bUseRstLocked[3] == rc.m_bUseRstLocked[3]) &&
                (this.m_bUseRstLocked[4] == rc.m_bUseRstLocked[4]) &&
                (this.m_bUseRstLocked[5] == rc.m_bUseRstLocked[5]) &&
                (this.m_bUseRstLocked[6] == rc.m_bUseRstLocked[6]);
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
                for (int i = 6; i >= 0; i--)
                {
                    if (carry && !this.UseRstLocked[i])
                    {
                        this.UseRst[i] = !this.UseRst[i];
                        carry = !this.UseRst[i];
                    }
                }
            }
            return carry;
        }
        public override void Reset()
        {
            base.Reset();
            if (!this.Locked)
            {
                for (int i = 0; i < 7; i++)
                    if (!this.UseRstLocked[i]) this.UseRst[i] = false;
            }
        }

        public override FeatureHeader FeatureHeader
        {
            get { return base.FeatureHeader; }
            set
            {
                base.FeatureHeader = value;
                if (value != null)
                {
                    for (int i = 0; i < 7; i++)
                        this.UseRstLocked[i] = !value.UseRst[i];
                }
            }
        }
        public override ulong NumCombinations
        {
            get
            {
                ulong combinations = base.NumCombinations;
                for (int i = 0; i < 7; i++)
                    if (!this.UseRstLocked[i]) combinations *= 2;
                return combinations;
            }
        }
        public override string SelectionHeader
        {
            get
            {
                string hdr = "";
                for (int i = 0; i < 7; i++)
                    if (this.UseRst[i] || !(this.UseRstLocked[i] || this.Locked)) hdr += ", Rst" + (i + 1).ToString();
                return hdr + base.SelectionHeader;
            }
           
        }
        public override string SelectionValue
        {
            get
            {
                string val = "";
                for (int i = 0; i < 7; i++)
                {
                    if (this.UseRst[i] || !(this.UseRstLocked[i] || this.Locked))
                    {
                        val += ", ";
                        if (this.UseRst[i]) val += "X";
                    }
                }
                return val + base.SelectionValue;
            }
           
        }

        public bool[] UseRst { get { return this.m_hdrFeatures.UseRst; } }
        public bool[] UseRstLocked { get { return this.m_bUseRstLocked; } }
        [XmlIgnore]
        public bool UseRst1
        {
            get { return this.m_hdrFeatures.UseRst1; }
            set { this.m_hdrFeatures.UseRst1 = value; }
        }
        public bool UseRst1Locked
        {
            get { return (this.m_bUseRstLocked[0] || this.Locked); }
            set { this.m_bUseRstLocked[0] = value; }
        }
        [XmlIgnore]
        public bool UseRst2
        {
            get { return this.m_hdrFeatures.UseRst2; }
            set { this.m_hdrFeatures.UseRst2 = value; }
        }
        public bool UseRst2Locked
        {
            get { return (this.m_bUseRstLocked[1] || this.Locked); }
            set { this.m_bUseRstLocked[1] = value; }
        }
        [XmlIgnore]
        public bool UseRst3
        {
            get { return this.m_hdrFeatures.UseRst3; }
            set { this.m_hdrFeatures.UseRst3 = value; }
        }
        public bool UseRst3Locked
        {
            get { return (this.m_bUseRstLocked[2] || this.Locked); }
            set { this.m_bUseRstLocked[2] = value; }
        }
        [XmlIgnore]
        public bool UseRst4
        {
            get { return this.m_hdrFeatures.UseRst4; }
            set { this.m_hdrFeatures.UseRst4 = value; }
        }
        public bool UseRst4Locked
        {
            get { return (this.m_bUseRstLocked[3] || this.Locked); }
            set { this.m_bUseRstLocked[3] = value; }
        }
        [XmlIgnore]
        public bool UseRst5
        {
            get { return this.m_hdrFeatures.UseRst5; }
            set { this.m_hdrFeatures.UseRst5 = value; }
        }
        public bool UseRst5Locked
        {
            get { return (this.m_bUseRstLocked[4] || this.Locked); }
            set { this.m_bUseRstLocked[4] = value; }
        }
        [XmlIgnore]
        public bool UseRst6
        {
            get { return this.m_hdrFeatures.UseRst6; }
            set { this.m_hdrFeatures.UseRst6 = value; }
        }
        public bool UseRst6Locked
        {
            get { return (this.m_bUseRstLocked[5] || this.Locked); }
            set { this.m_bUseRstLocked[5] = value; }
        }
        [XmlIgnore]
        public bool UseRst7
        {
            get { return this.m_hdrFeatures.UseRst7; }
            set { this.m_hdrFeatures.UseRst7 = value; }
        }
        public bool UseRst7Locked
        {
            get { return (this.m_bUseRstLocked[6] || this.Locked); }
            set { this.m_bUseRstLocked[6] = value; }
        }
    }
    public class LawChooser : FeatureChooser
    {
        bool[] m_bUseLawLocked = new bool[15];

        public LawChooser() { }
        public LawChooser(LawChooser lc)
            : base((FeatureChooser)lc)
        {
            for (int i = 0; i < 15; i++)
                this.m_bUseLawLocked[i] = lc.m_bUseLawLocked[i];
        }
        public override void AllOn()
        {
            base.AllOn();
            if (!this.Locked)
            {
                for (int i = 0; i < 15; i++)
                    if (!this.UseLawLocked[i]) this.UseLaw[i] = true;
            }
        }
        public override bool Equals(object obj)
        {
            return (Equals(obj as LawChooser));
        }
        public bool Equals(LawChooser lc)
        {
            return base.Equals(lc) &&
                (this.m_bUseLawLocked[0] == lc.m_bUseLawLocked[0]) &&
                (this.m_bUseLawLocked[1] == lc.m_bUseLawLocked[1]) &&
                (this.m_bUseLawLocked[2] == lc.m_bUseLawLocked[2]) &&
                (this.m_bUseLawLocked[3] == lc.m_bUseLawLocked[3]) &&
                (this.m_bUseLawLocked[4] == lc.m_bUseLawLocked[4]) &&
                (this.m_bUseLawLocked[5] == lc.m_bUseLawLocked[5]) &&
                (this.m_bUseLawLocked[6] == lc.m_bUseLawLocked[6]) &&
                (this.m_bUseLawLocked[7] == lc.m_bUseLawLocked[7]) &&
                (this.m_bUseLawLocked[8] == lc.m_bUseLawLocked[8]) &&
                (this.m_bUseLawLocked[9] == lc.m_bUseLawLocked[9]) &&
                (this.m_bUseLawLocked[10] == lc.m_bUseLawLocked[10]) &&
                (this.m_bUseLawLocked[11] == lc.m_bUseLawLocked[11]) &&
                   (this.m_bUseLawLocked[12] == lc.m_bUseLawLocked[12]) &&
                (this.m_bUseLawLocked[13] == lc.m_bUseLawLocked[13]) &&
                (this.m_bUseLawLocked[14] == lc.m_bUseLawLocked[14]) &&
                (this.m_bUseLawLocked[15] == lc.m_bUseLawLocked[15]);
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
                for (int i = 14; i >= 0; i--)
                {
                    if (carry && !this.UseLawLocked[i])
                    {
                        this.UseLaw[i] = !this.UseLaw[i];
                        carry = !this.UseLaw[i];
                    }
                }
            }
            return carry;
        }
        public override void Reset()
        {
            base.Reset();
            if (!this.Locked)
            {
                for (int i = 0; i < 15; i++)
                    if (!this.UseLawLocked[i]) this.UseLaw[i] = false;
            }
        }

        public override FeatureHeader FeatureHeader
        {
            get { return base.FeatureHeader; }
            set
            {
                base.FeatureHeader = value;
                if (value != null)
                {
                    for (int i = 0; i < 15; i++)
                        this.UseLawLocked[i] = !value.UseLaw[i];
                }
            }
        }
        public override ulong NumCombinations
        {
            get
            {
                ulong combinations = base.NumCombinations;
                for (int i = 0; i < 15; i++)
                    if (!this.UseLawLocked[i]) combinations *= 2;
                return combinations;
            }
        }
        public override string SelectionHeader
        {
            get
            {
                string hdr = "";
                for (int i = 0; i < 15; i++)
                    if (this.UseLaw[i] || !(this.UseLawLocked[i] || this.Locked)) hdr += ", Law" + (i + 1).ToString();
                return hdr + base.SelectionHeader;
            }

        }
        public override string SelectionValue
        {
            get
            {
                string val = "";
                for (int i = 0; i < 15; i++)
                {
                    if (this.UseLaw[i] || !(this.UseLawLocked[i] || this.Locked))
                    {
                        val += ", ";
                        if (this.UseLaw[i]) val += "X";
                    }
                }
                return val + base.SelectionValue;
            }

        }

        public bool[] UseLaw { get { return this.m_hdrFeatures.UseLaw; } }
        public bool[] UseLawLocked { get { return this.m_bUseLawLocked; } }
        [XmlIgnore]
        public bool UseLaw1
        {
            get { return this.m_hdrFeatures.UseMask1; }
            set { this.m_hdrFeatures.UseMask1 = value; }
        }
        public bool UseLaw1Locked
        {
            get { return (this.m_bUseLawLocked[0] || this.Locked); }
            set { this.m_bUseLawLocked[0] = value; }
        }
        [XmlIgnore]
        public bool UseLaw2
        {
            get { return this.m_hdrFeatures.UseMask2; }
            set { this.m_hdrFeatures.UseMask2 = value; }
        }
        public bool UseLaw2Locked
        {
            get { return (this.m_bUseLawLocked[1] || this.Locked); }
            set { this.m_bUseLawLocked[1] = value; }
        }
        [XmlIgnore]
        public bool UseLaw3
        {
            get { return this.m_hdrFeatures.UseMask3; }
            set { this.m_hdrFeatures.UseMask3 = value; }
        }
        public bool UseLaw3Locked
        {
            get { return (this.m_bUseLawLocked[2] || this.Locked); }
            set { this.m_bUseLawLocked[2] = value; }
        }
        [XmlIgnore]
        public bool UseLaw4
        {
            get { return this.m_hdrFeatures.UseMask4; }
            set { this.m_hdrFeatures.UseMask4 = value; }
        }
        public bool UseLaw4Locked
        {
            get { return (this.m_bUseLawLocked[3] || this.Locked); }
            set { this.m_bUseLawLocked[3] = value; }
        }
        [XmlIgnore]
        public bool UseLaw5
        {
            get { return this.m_hdrFeatures.UseMask5; }
            set { this.m_hdrFeatures.UseMask5 = value; }
        }
        public bool UseLaw5Locked
        {
            get { return (this.m_bUseLawLocked[4] || this.Locked); }
            set { this.m_bUseLawLocked[4] = value; }
        }
        [XmlIgnore]
        public bool UseLaw6
        {
            get { return this.m_hdrFeatures.UseMask6; }
            set { this.m_hdrFeatures.UseMask6 = value; }
        }
        public bool UseLaw6Locked
        {
            get { return (this.m_bUseLawLocked[5] || this.Locked); }
            set { this.m_bUseLawLocked[5] = value; }
        }
        [XmlIgnore]
        public bool UseLaw7
        {
            get { return this.m_hdrFeatures.UseMask7; }
            set { this.m_hdrFeatures.UseMask7 = value; }
        }
        public bool UseLaw7Locked
        {
            get { return (this.m_bUseLawLocked[6] || this.Locked); }
            set { this.m_bUseLawLocked[6] = value; }
        }
        [XmlIgnore]
        public bool UseLaw8
        {
            get { return this.m_hdrFeatures.UseMask8; }
            set { this.m_hdrFeatures.UseMask8 = value; }
        }
        public bool UseLaw8Locked
        {
            get { return (this.m_bUseLawLocked[7] || this.Locked); }
            set { this.m_bUseLawLocked[7] = value; }
        }
        [XmlIgnore]
        public bool UseLaw9
        {
            get { return this.m_hdrFeatures.UseMask9; }
            set { this.m_hdrFeatures.UseMask9 = value; }
        }
        public bool UseLaw9Locked
        {
            get { return (this.m_bUseLawLocked[8] || this.Locked); }
            set { this.m_bUseLawLocked[8] = value; }
        }
        [XmlIgnore]
        public bool UseLaw10
        {
            get { return this.m_hdrFeatures.UseMask10; }
            set { this.m_hdrFeatures.UseMask10 = value; }
        }
        public bool UseLaw10Locked
        {
            get { return (this.m_bUseLawLocked[9] || this.Locked); }
            set { this.m_bUseLawLocked[9] = value; }
        }
        [XmlIgnore]
        public bool UseLaw11
        {
            get { return this.m_hdrFeatures.UseMask11; }
            set { this.m_hdrFeatures.UseMask11 = value; }
        }
        public bool UseLaw11Locked
        {
            get { return (this.m_bUseLawLocked[10] || this.Locked); }
            set { this.m_bUseLawLocked[10] = value; }
        }
        [XmlIgnore]
        public bool UseLaw12
        {
            get { return this.m_hdrFeatures.UseMask12; }
            set { this.m_hdrFeatures.UseMask12 = value; }
        }
        public bool UseLaw12Locked
        {
            get { return (this.m_bUseLawLocked[11] || this.Locked); }
            set { this.m_bUseLawLocked[11] = value; }
        }
        [XmlIgnore]
        public bool UseLaw13
        {
            get { return this.m_hdrFeatures.UseMask13; }
            set { this.m_hdrFeatures.UseMask13 = value; }
        }
        public bool UseLaw13Locked
        {
            get { return (this.m_bUseLawLocked[12] || this.Locked); }
            set { this.m_bUseLawLocked[12] = value; }
        }
        [XmlIgnore]
        public bool UseLaw14
        {
            get { return this.m_hdrFeatures.UseMask14; }
            set { this.m_hdrFeatures.UseMask14 = value; }
        }
        public bool UseLaw14Locked
        {
            get { return (this.m_bUseLawLocked[13] || this.Locked); }
            set { this.m_bUseLawLocked[13] = value; }
        }
        [XmlIgnore]
        public bool UseLaw15
        {
            get { return this.m_hdrFeatures.UseMask15; }
            set { this.m_hdrFeatures.UseMask15 = value; }
        }
        public bool UseLaw15Locked
        {
            get { return (this.m_bUseLawLocked[14] || this.Locked); }
            set { this.m_bUseLawLocked[14] = value; }
        }
    }
    public class TextureChooser : FeatureChooser
    {
        bool m_bUseCorrelationLocked = false;
        bool m_bUseEnergyLocked = false;
        bool m_bUseEntropyLocked = false;
      //  bool m_bUseLawLocked = false;
        bool m_bUseInertiaLocked = false;
        bool m_bUseInvDiffLocked = false;
        bool m_buseCombTexture = false;
        bool m_buseCombLaw = false;
        int m_nMinDistance = 2;
        int m_nMaxDistance = 2;
        int m_nIncDistance = 2;

        public TextureChooser() { }
        public TextureChooser(TextureChooser tc)
            : base((FeatureChooser)tc)
        {
            this.m_bUseCorrelationLocked = tc.m_bUseCorrelationLocked;
            this.m_bUseEnergyLocked = tc.m_bUseEnergyLocked;
            this.m_bUseEntropyLocked = tc.m_bUseEntropyLocked;
            this.m_bUseInertiaLocked = tc.m_bUseInertiaLocked;
            this.m_bUseInvDiffLocked = tc.m_bUseInvDiffLocked;
            this.m_buseCombTexture = tc.m_buseCombTexture; 
            this.m_nMinDistance = tc.m_nMinDistance;
            this.m_nMaxDistance = tc.m_nMaxDistance;
        }
        public override void AllOn()
        {
            base.AllOn();
            if (!this.Locked)
            {
                if (!this.UseEnergyLocked) this.UseEnergy = true;
                if (!this.UseInertiaLocked) this.UseInertia = true;
                if (!this.UseCorrelationLocked) this.UseCorrelation = true;
                if (!this.UseInvDiffLocked) this.UseInvDiff = true;
                if (!this.UseEntropyLocked) this.UseEntropy = true;
            }
        }
        public override bool Equals(object obj)
        {
            return (Equals(obj as TextureChooser));
        }
        public bool Equals(TextureChooser tc)
        {
            return base.Equals(tc) &&
                (this.m_bUseCorrelationLocked == tc.m_bUseCorrelationLocked) &&
                (this.m_bUseEnergyLocked == tc.m_bUseEnergyLocked) &&
                (this.m_bUseEntropyLocked == tc.m_bUseEntropyLocked) &&
                (this.m_bUseInertiaLocked == tc.m_bUseInertiaLocked) &&
                (this.m_bUseInvDiffLocked == tc.m_bUseInvDiffLocked) &&
                (this.m_buseCombTexture == tc.m_buseCombTexture) &&
                (this.m_nMinDistance == tc.m_nMinDistance) &&
               
                (this.m_nMaxDistance == tc.m_nMaxDistance) ;
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
                if (carry && !this.UseEntropyLocked)
                {
                    this.UseEntropy = !this.UseEntropy;
                    carry = !this.UseEntropy;
                }
                if (carry && !this.UseInvDiffLocked)
                {
                    this.UseInvDiff = !this.UseInvDiff;
                    carry = !this.UseInvDiff;
                }
                if (carry && !this.UseCorrelationLocked)
                {
                    this.UseCorrelation = !this.UseCorrelation;
                    carry = !this.UseCorrelation;
                }
                if (carry && !this.UseInertiaLocked)
                {
                    this.UseInertia = !this.UseInertia;
                    carry = !this.UseInertia;
                }
                if (carry && !this.UseEnergyLocked)
                {
                    this.UseEnergy = !this.UseEnergy;
                    carry = !this.UseEnergy;
                }
                if (carry)
                {
                    if (!FeatureHeader.UseCombTex)
                    {
                        if (++this.Distance <= this.MinDistance)
                        {
                            FeatureChooser next = this.m_chooserNext;
                            this.m_chooserNext = null;
                            carry = Increment();
                            this.m_chooserNext = next;
                        }
                        else
                        {
                            this.Distance = this.Distance-1;
                        }
                    }
                    else
                    {
                        if (++FeatureHeader.TextureDistanceCalc <= this.FeatureHeader.TextureDistanceLower)
                        {
                            FeatureChooser next = this.m_chooserNext;
                            this.m_chooserNext = null;
                            carry = Increment();
                            this.m_chooserNext = next;
                        }
                        else
                        {
                            FeatureHeader.TextureDistanceCalc = FeatureHeader.TextureDistanceCalc-1;
                        }
                    }
                }
            }
            return carry;
        }
        public override void Reset()
        {
            base.Reset();
            if (!this.Locked)
            {
                this.Distance = this.MinDistance;

                if (!this.UseEnergyLocked) this.UseEnergy = false;
                if (!this.UseInertiaLocked) this.UseInertia = false;
                if (!this.UseCorrelationLocked) this.UseCorrelation = false;
                if (!this.UseInvDiffLocked) this.UseInvDiff = false;
                if (!this.UseEntropyLocked) this.UseEntropy = false;
            }
        }

        public override FeatureHeader FeatureHeader
        {
            get { return base.FeatureHeader; }
            set
            {
                base.FeatureHeader = value;
                if (value != null)
                {
                    this.UseEnergyLocked = !value.UseTexEnergy;
                    this.UseCorrelationLocked = !value.UseTexCorrelation;
                    this.UseEntropyLocked = !value.UseTexEntropy;
                    this.UseInertiaLocked = !value.UseTexInertia;
                    this.UseInvDiffLocked = !value.UseTexInvDiff;
                    this.UseCombTex = !value.UseCombTex;
                    this.MinDistance = value.TextureDistanceLower;
                    this.MaxDistance = value.TextureDistanceUpper;
                    this.IncDistance = value.TextureDistanceIncrement;

                }
            }
        }
        public override ulong NumCombinations
        { 

            get
            {
                ulong combinations = base.NumCombinations;
                if (!this.UseEnergyLocked) combinations *= 2;
                if (!this.UseInertiaLocked) combinations *= 2;
                if (!this.UseCorrelationLocked) combinations *= 2;
                if (!this.UseInvDiffLocked) combinations *= 2;
                if (!this.UseEntropyLocked) combinations *= 2;
               // combinations *= 2;//for Laws Texture

               // combinations *= (ulong)((this.MaxDistance - this.MinDistance) / this.IncDistance)+1; 
                return combinations;
            }
        }
        public override string SelectionHeader
        {
            get
            {
                string hdr = "";
                if (this.UseEnergy || !this.UseEnergyLocked ||
                    this.UseInertia || !this.UseInertiaLocked ||
                    this.UseCorrelation || !this.UseCorrelationLocked ||
                    this.UseInvDiff || !this.UseInvDiffLocked ||
                    this.UseEntropy || !this.UseEntropyLocked)
                {
                    hdr += ", Distance";
                    if (this.UseEnergy || !this.UseEnergyLocked) hdr += ", TexEnergy";
                    if (this.UseInertia || !this.UseInertiaLocked) hdr += ", TexInertia";
                    if (this.UseCorrelation || !this.UseCorrelationLocked) hdr += ", TexCorrelation";
                    if (this.UseInvDiff || !this.UseInvDiffLocked) hdr += ", TexInvDiff";
                    if (this.UseEntropy || !this.UseEntropyLocked) hdr += ", TexEntropy";
                  //  if (this.UseLaw || !this.UseLawLocked) hdr += ", LawTexture";
                  //  hdr += ", LawTexture";
                }
                return hdr + base.SelectionHeader;
            }
          
        }
        public override string SelectionValue
        {
            get
            {
                string val = "";
                if (this.UseEnergy || !this.UseEnergyLocked ||
                    this.UseInertia || !this.UseInertiaLocked ||
                    this.UseCorrelation || !this.UseCorrelationLocked ||
                    this.UseInvDiff || !this.UseInvDiffLocked ||
                    this.UseEntropy || !this.UseEntropyLocked)
                {
                    if (FeatureHeader.UseCombTex)
                        val += ", " + FeatureHeader.TextureDistanceCalc;
                    else val += this.Distance;
                    if (this.UseEnergy || !this.UseEnergyLocked)
                    {
                        val += ", ";
                        if (this.UseEnergy) val += "X";
                    }
                    if (this.UseInertia || !this.UseInertiaLocked)
                    {
                        val += ", ";
                        if (this.UseInertia) val += "X";
                    }
                    if (this.UseCorrelation || !this.UseCorrelationLocked)
                    {
                        val += ", ";
                        if (this.UseCorrelation) val += "X";
                    }
                    if (this.UseInvDiff || !this.UseInvDiffLocked)
                    {
                        val += ", ";
                        if (this.UseInvDiff) val += "X";
                    }
                    if (this.UseEntropy || !this.UseEntropyLocked)
                    {
                        val += ", ";
                        if (this.UseEntropy) val += "X";
                    }
                  
                }
                return val + base.SelectionValue;
            }
           
        }

        [XmlIgnore]
        public int Distance
        {
            get
            {
                int distance = -1;
                if (this.m_hdrFeatures != null)
                    distance = this.m_hdrFeatures.TextureDistance;
                return distance;
            }
            set
            {
                if (this.m_hdrFeatures != null)
                    this.m_hdrFeatures.TextureDistance = value;
            }
        }

        public int MinDistance
        {
            get { return this.m_nMinDistance; }
            set
            {
                this.m_nMinDistance = value;
                this.Distance = this.m_nMinDistance;
            }
        }
        public int MaxDistance
        {
            get { return this.m_nMaxDistance; }
            set
            {
                this.m_nMaxDistance = value;
                this.Distance = this.m_nMinDistance;
            }
        }

        public int IncDistance
        {
            get
            {
                int distance = -1;
                distance = this.m_hdrFeatures.TextureDistanceIncrement;
                return distance; ;
            }
            set
            {
                if (this.m_hdrFeatures != null)
                    this.m_hdrFeatures.TextureDistanceIncrement = value;
            }
        }
        [XmlIgnore]
        public bool UseCorrelation
        {
            get { return this.m_hdrFeatures.UseTexCorrelation; }
            set { this.m_hdrFeatures.UseTexCorrelation = value; }
        }
        public bool UseCorrelationLocked
        {
            get { return (this.m_bUseCorrelationLocked || this.Locked); }
            set { this.m_bUseCorrelationLocked = value; }
        }
        [XmlIgnore]
        public bool UseEnergy
        {
            get { return this.m_hdrFeatures.UseTexEnergy; }
            set { this.m_hdrFeatures.UseTexEnergy = value; }
        }
        public bool UseEnergyLocked
        {
            get { return (this.m_bUseEnergyLocked || this.Locked); }
            set { this.m_bUseEnergyLocked = value; }
        }
        [XmlIgnore]
        public bool UseEntropy
        {
            get { return this.m_hdrFeatures.UseTexEntropy; }
            set { this.m_hdrFeatures.UseTexEntropy = value; }
        }
        public bool UseEntropyLocked
        {
            get { return (this.m_bUseEntropyLocked || this.Locked); }
            set { this.m_bUseEntropyLocked = value; }
        }
       
        [XmlIgnore]
        public bool UseInertia
        {
            get { return this.m_hdrFeatures.UseTexInertia; }
            set { this.m_hdrFeatures.UseTexInertia = value; }
        }
        public bool UseInertiaLocked
        {
            get { return (this.m_bUseInertiaLocked || this.Locked); }
            set { this.m_bUseInertiaLocked = value; }
        }
        [XmlIgnore]
        public bool UseInvDiff
        {
            get { return this.m_hdrFeatures.UseTexInvDiff; }
            set { this.m_hdrFeatures.UseTexInvDiff = value; }
        }
        public bool UseInvDiffLocked
        {
            get { return (this.m_bUseInvDiffLocked || this.Locked); }
            set { this.m_bUseInvDiffLocked = value; }
        }

        public bool UseCombTex
        {
            get { return (this.m_bUseInvDiffLocked || this.Locked); }
            set { this.m_buseCombTexture = value; }
        }
      
       
       // public bool UseLawLocked
       // {
           // get { return (this.m_bUseLawLocked || this.Locked); }
           // set { this.m_bUseLawLocked = value; }
       // }
    }
    public class SpectralChooser : FeatureChooser
    {
        int m_nRingsMin = 3;
        int m_nRingsMax = 3;
        int m_nSectorsMin = 3;
        int m_nSectorsMax = 3;

        public SpectralChooser() { }
        public SpectralChooser(SpectralChooser sc)
            : base((FeatureChooser)sc)
        {
            this.m_nRingsMin = sc.m_nRingsMin;
            this.m_nRingsMax = sc.m_nRingsMax;
            this.m_nSectorsMin = sc.m_nSectorsMin;
            this.m_nSectorsMax = sc.m_nSectorsMax;
        }
        public override void AllOn()
        {
            base.AllOn();
            if (!this.Locked) this.UseSpectral = true;
        }
        public override bool Equals(object obj)
        {
            return (Equals(obj as SpectralChooser));
        }
        public bool Equals(SpectralChooser sc)
        {
            return base.Equals(sc) &&
                (this.m_nRingsMin == sc.m_nRingsMin) &&
                (this.m_nRingsMax == sc.m_nRingsMax) &&
                (this.m_nSectorsMin == sc.m_nSectorsMin) &&
                (this.m_nSectorsMax == sc.m_nSectorsMax);
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
                this.UseSpectral = !this.UseSpectral;
                carry = !this.UseSpectral;
                if (carry)
                {
                    if (++this.Rings <= this.RingsMax)
                    {
                        FeatureChooser next = this.m_chooserNext;
                        this.m_chooserNext = null;
                        carry = Increment();
                        this.m_chooserNext = next;
                    }
                    else
                    {
                        this.Rings = this.RingsMin;
                        if (++this.Sectors <= this.SectorsMax)
                        {
                            FeatureChooser next = this.m_chooserNext;
                            this.m_chooserNext = null;
                            carry = Increment();
                            this.m_chooserNext = next;
                        }
                        else
                        {
                            this.Sectors = this.SectorsMin;
                        }
                    }
                }
            }
            return carry;
        }
        public override void Reset()
        {
            base.Reset();
            if (!this.Locked)
            {
                this.Rings = this.RingsMin;
                this.Sectors = this.SectorsMin;
                this.UseSpectral = false;
            }
        }

        public override FeatureHeader FeatureHeader
        {
            get { return base.FeatureHeader; }
            set
            {
                base.FeatureHeader = value;
                if (value != null)
                {
                    this.Locked = !value.UseSpectral;
                    this.RingsMin = value.SpectralRings;
                    this.RingsMax = value.SpectralRings;
                    this.SectorsMin = value.SpectralSectors;
                    this.SectorsMax = value.SpectralSectors;
                }
            }
        }
        public override ulong NumCombinations
        {
            get
            {
                ulong combinations = base.NumCombinations;
                if (!this.Locked) combinations *= 2;
                return combinations;
            }
        }
        public override string SelectionHeader
        {
            get
            {
                string hdr = "";
                if (this.UseSpectral || !this.Locked) hdr += ", Spectral";
                return hdr + base.SelectionHeader;
            }
           
        }
      
        public override string SelectionValue
        {
            get
            {
                string val = "";
                if (this.UseSpectral || !this.Locked)
                {
                    val += ", ";
                    if (this.UseSpectral)
                        val += this.Rings + "x" + this.Sectors;
                }
                return val + base.SelectionValue;
            }
            
        }
      
        [XmlIgnore]
        public int Rings
        {
            get
            {
                int rings = -1;
                if (this.m_hdrFeatures != null)
                    rings = this.m_hdrFeatures.SpectralRings;
                return rings;
            }
            set
            {
                if (this.m_hdrFeatures != null)
                    this.m_hdrFeatures.SpectralRings = value;
            }
        }
        public int RingsMin
        {
            get { return this.m_nRingsMin; }
            set
            {
                this.m_nRingsMin = value;
                this.Rings = this.m_nRingsMin;
            }
        }
        public int RingsMax
        {
            get { return this.m_nRingsMax; }
            set
            {
                this.m_nRingsMax = value;
                this.Rings = this.m_nRingsMin;
            }
        }
        [XmlIgnore]
        public int Sectors
        {
            get
            {
                int sectors = -1;
                if (this.m_hdrFeatures != null)
                    sectors = this.m_hdrFeatures.SpectralSectors;
                return sectors;
            }
            set
            {
                if (this.m_hdrFeatures != null)
                    this.m_hdrFeatures.SpectralSectors = value;
            }
        }
        public int SectorsMin
        {
            get { return this.m_nSectorsMin; }
            set
            {
                this.m_nSectorsMin = value;
                this.Sectors = this.m_nSectorsMin;
            }
        }
        public int SectorsMax
        {
            get { return this.m_nSectorsMax; }
            set
            {
                this.m_nSectorsMax = value;
                this.Sectors = this.m_nSectorsMin;
            }
        }
        [XmlIgnore]
        public bool UseSpectral
        {
            get { return this.m_hdrFeatures.UseSpectral; }
            set { this.m_hdrFeatures.UseSpectral = value; }
        }
    }
}
