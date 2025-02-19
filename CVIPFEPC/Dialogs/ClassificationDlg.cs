/*''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' ======================================================================
' Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
' ======================================================================
'
'             File Name: ClassificationDlg.cs
'           Description: Contains the code for
'                        ClassificationDlg dialog
'         Related Files: MainForm.cs
'                        AppConfiguration.cs
'                        Classifier.cs
'   Initial Coding Date: November 2006
'              Modified: January 2012
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

using CVIPFEPC.Configuration;
using CVIPFEPC.CvipFile;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace CVIPFEPC.Dialogs
{
    public partial class ClassificationDlg : Form
    {
        private bool bMultiSelect = false;
        private Algorithm currentAlgorithm;
        private Distance currentDistance;
        private Normalization currentNormalization;

        private Classifier defaultClassifier = null;
        private Classifier internalClassifier = null;
        private AlgorithmChooser defaultAlgorithmChooser = null;
        private AlgorithmChooser internalAlgorithmChooser = null;
        private DistanceChooser defaultDistanceChooser = null;
        private DistanceChooser internalDistanceChooser = null;
        private NormalizationChooser defaultNormalizationChooser = null;
        private NormalizationChooser internalNormalizationChooser = null;

        public ClassificationDlg()
            : this(false) { }
        public ClassificationDlg(bool multiselect)
        {
            InitializeComponent();
            this.bMultiSelect = multiselect;
        }
        private void btnSelectionMode_Click(object sender, EventArgs e)
        {
            SetSelectionMode((sender as Button) == this.btnSwitchToMultiSelect);
        }
        private void btnOK_Click(object sender, EventArgs e)
        {
            if (!this.ClassifierInternal.Equals(AppConfiguration.Classifier))
                AppConfiguration.Classifier = this.Classifier;
            if (!this.AlgorithmChooserInternal.Equals(AppConfiguration.AlgorithmChooser))
                AppConfiguration.AlgorithmChooser = this.AlgorithmChooser;
            if (!this.DistanceChooserInternal.Equals(AppConfiguration.DistanceChooser))
                AppConfiguration.DistanceChooser = this.DistanceChooser;
            if (!this.NormalizationChooserInternal.Equals(AppConfiguration.NormalizationChooser))
                AppConfiguration.NormalizationChooser = this.NormalizationChooser;
        }
        private void btnReset_Click(object sender, EventArgs e)
        {
            this.ClassifierInternal = this.defaultClassifier;
            this.AlgorithmChooserInternal = this.defaultAlgorithmChooser;
            this.DistanceChooserInternal = this.defaultDistanceChooser;
            this.NormalizationChooserInternal = this.defaultNormalizationChooser;
        }
        private void cboIntVal_Validating(object sender, CancelEventArgs e)
        {
            ComboBox cbo = sender as ComboBox;
            int val;
            if (!int.TryParse(cbo.Text, out val))
            {
                MessageBox.Show("Please check the input value. Only integers are accepted.",
                   "Integer Required", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                cbo.SelectAll();
                e.Cancel = true;
            }
        }
        protected override void OnLoad(EventArgs e)
        {
            base.OnLoad(e);

            this.rbAlgorithmNearestNeighbor.Tag = Algorithm.NearestNeighbor;
            this.rbAlgorithmKNearestNeighbor.Tag = Algorithm.K_NearestNeighbor;
            this.rbAlgorithmNearestCentroid.Tag = Algorithm.NearestCentroid;

            this.rbDistanceEuclidean.Tag = Distance.Euclidean;
            this.rbDistanceAbsValue.Tag = Distance.CityBlock;
            this.rbDistanceMaxValue.Tag = Distance.MaxValue;
            this.rbDistanceMinkowski.Tag = Distance.Minkowski;
            this.rbDistanceVIP.Tag = Distance.VectorInnerProduct;
            this.rbDistanceTanimoto.Tag = Distance.Tanimoto;

            this.rbNormalizeNone.Tag = Normalization.None;
            this.rbNormalizeRange.Tag = Normalization.Range;
            this.rbNormalizeUnitVector.Tag = Normalization.UnitVector;
            this.rbNormalizeStdNorm.Tag = Normalization.StdNormal;
            this.rbNormalizeMinMax.Tag = Normalization.MinMax;
            this.rbNormalizeSoftmax.Tag = Normalization.Softmax;

            this.Classifier = AppConfiguration.Classifier;
            this.AlgorithmChooser = AppConfiguration.AlgorithmChooser;
            this.DistanceChooser = AppConfiguration.DistanceChooser;
            this.NormalizationChooser = AppConfiguration.NormalizationChooser;

            SetSelectionMode(this.bMultiSelect);
        }
        private void OnValueChanged(object sender, EventArgs e)
        {
            RefreshGUI();
        }
        private void rbAlgorithm_Click(object sender, EventArgs e)
        {
            RadioButton rb = sender as RadioButton;
            if ((rb != null) && rb.Checked && (rb.Tag != null))
            {
                this.currentAlgorithm = (Algorithm)rb.Tag;
                RefreshGUI();
            }
        }
        private void rbDistance_Click(object sender, EventArgs e)
        {
            RadioButton rb = sender as RadioButton;
            if ((rb != null) && rb.Checked && (rb.Tag != null))
            {
                this.currentDistance = (Distance)rb.Tag;
                RefreshGUI();
            }
        }
        private void rbNormalization_Click(object sender, EventArgs e)
        {
            RadioButton rb = sender as RadioButton;
            if ((rb != null) && rb.Checked && (rb.Tag != null))
            {
                this.currentNormalization = (Normalization)rb.Tag;
                RefreshGUI();
            }
        }
        private void RefreshGUI()
        {
            bool visible = (this.bMultiSelect && this.chkAlgorithmKNearestNeighbor.Checked) ||
                                (!this.bMultiSelect && this.Algorithm == Algorithm.K_NearestNeighbor);
            this.cboK.Visible = visible;
            this.lblK.Visible = visible;

            visible = (this.bMultiSelect && this.chkDistanceMinkowski.Checked) ||
                                (!this.bMultiSelect && this.Distance == Distance.Minkowski);
            this.cboMinkowski.Visible = visible;
            this.lblMinkowski.Visible = visible;

            visible = (this.bMultiSelect && this.chkNormalizeSoftmax.Checked) ||
                                (!this.bMultiSelect && this.Normalization == Normalization.Softmax);
            this.txtSoftmax.Visible = visible;
            this.lblSoftmax.Visible = visible;

            visible = (this.bMultiSelect && this.chkNormalizeMinMax.Checked) ||
                                (!this.bMultiSelect && this.Normalization == Normalization.MinMax);
            this.txtSMin.Visible = visible;
            this.lblSMin.Visible = visible;
            this.txtSMax.Visible = visible;
            this.lblSMax.Visible = visible;

            this.btnReset.Enabled = this.IsDirty;
        }
        private void SaveChanges()
        {
            if (!this.ClassifierInternal.Equals(AppConfiguration.Classifier))
            {
                AppConfiguration.Classifier = this.Classifier;
                this.defaultClassifier = this.Classifier;
            }
            if (!this.AlgorithmChooserInternal.Equals(AppConfiguration.AlgorithmChooser))
            {
                AppConfiguration.AlgorithmChooser = this.AlgorithmChooser;
                this.defaultAlgorithmChooser = this.AlgorithmChooser;
            }
            if (!this.DistanceChooserInternal.Equals(AppConfiguration.DistanceChooser))
            {
                AppConfiguration.DistanceChooser = this.DistanceChooser;
                this.defaultDistanceChooser = this.DistanceChooser;
            }
            if (!this.NormalizationChooserInternal.Equals(AppConfiguration.NormalizationChooser))
            {
                AppConfiguration.NormalizationChooser = this.NormalizationChooser;
                this.defaultNormalizationChooser = this.NormalizationChooser;
            }
            RefreshGUI();
        }
        private void SetSelectionMode(bool multiselect)
        {
            if (this.IsDirty)
            {
                string msg = "There are unsaved changes on this page. Would you like to save them?";
                string caption = "Unsaved Items";
                switch (MessageBox.Show(msg, caption, MessageBoxButtons.YesNoCancel))
                {
                case DialogResult.Cancel:
                    return;
                case DialogResult.Yes:
                    SaveChanges();
                    break;
                }
            }
            this.bMultiSelect = multiselect;

            this.btnSwitchToSingleSelect.Visible = this.bMultiSelect;
            this.pnlAlgorithmMultiSelect.Visible = this.bMultiSelect;
            this.pnlDistanceMultiSelect.Visible = this.bMultiSelect;
            this.pnlNormMultiSelect.Visible = this.bMultiSelect;

            this.btnSwitchToMultiSelect.Visible = !this.bMultiSelect;
            this.pnlAlgorithmSingleSelect.Visible = !this.bMultiSelect;
            this.pnlDistanceSingleSelect.Visible = !this.bMultiSelect;
            this.pnlNormSingleSelect.Visible = !this.bMultiSelect;

            if (this.bMultiSelect)
                this.Text = "Pattern Classification - Combinatoric Selection";
            else
                this.Text = "Pattern Classification - Single Selection";

            RefreshGUI();
        }
        private void txtIntVal_Validating(object sender, CancelEventArgs e)
        {
            TextBox txt = sender as TextBox;
            int val;
            if (!int.TryParse(txt.Text, out val))
            {
                MessageBox.Show("Please check the input value. Only integers are accepted.",
                   "Integer Required", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                txt.SelectAll();
                e.Cancel = true;
            }
        }
        private void txtMinMax_Validating(object sender, CancelEventArgs e)
        {
            TextBox txt = sender as TextBox;
            int val;
            if (!int.TryParse(txt.Text, out val))
            {
                MessageBox.Show("Please check the input value. Only integers are accepted.",
                   "Integer Required", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                txt.SelectAll();
                e.Cancel = true;
                return;
            }
            if ((txt == this.txtSMin) && (val > this.SMax))
            {
                MessageBox.Show("s_min must be less than s_max",
                   "Min-Max Normalization", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                txt.SelectAll();
                e.Cancel = true;
                return;
            }
            if ((txt == this.txtSMax) && (val < this.SMin))
            {
                MessageBox.Show("s_max must be greater than s_min",
                   "Min-Max Normalization", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                txt.SelectAll();
                e.Cancel = true;
                return;
            }
        }

        private bool IsDirty
        {
            get
            {
                return !this.ClassifierInternal.Equals(this.defaultClassifier) ||
                            !this.AlgorithmChooserInternal.Equals(this.defaultAlgorithmChooser) ||
                            !this.DistanceChooserInternal.Equals(this.defaultDistanceChooser) ||
                            !this.NormalizationChooserInternal.Equals(this.defaultNormalizationChooser);
            }
        }
        private Classifier ClassifierInternal
        {
            get
            {
                if (this.internalClassifier == null) this.internalClassifier = new Classifier();
                this.internalClassifier.Algorithm = this.Algorithm;
                this.internalClassifier.Distance = this.Distance;
                this.internalClassifier.Normalization = this.Normalization;
                this.internalClassifier.Minkowski = this.Minkowski;
                this.internalClassifier.Neighbors = this.K;
                this.internalClassifier.Softmax = this.Softmax;
                this.internalClassifier.SMin = this.SMin;
                this.internalClassifier.SMax = this.SMax;
                return this.internalClassifier;
            }
            set
            {
                Classifier classifier = (value != null) ? value : new Classifier();
                this.Algorithm = classifier.Algorithm;
                this.Distance = classifier.Distance;
                this.Normalization = classifier.Normalization;
                this.Minkowski = classifier.Minkowski;
                this.K = classifier.Neighbors;
                this.Softmax = classifier.Softmax;
                this.SMin = classifier.SMin;
                this.SMax = classifier.SMax;
            }
        }
        public Classifier Classifier
        {
            get { return new Classifier(this.ClassifierInternal); }
            set
            {
                this.ClassifierInternal = value;
                this.defaultClassifier = new Classifier(this.ClassifierInternal);
                RefreshGUI();
            }
        }
        private AlgorithmChooser AlgorithmChooserInternal
        {
            get
            {
                if (this.internalAlgorithmChooser == null) this.internalAlgorithmChooser = new AlgorithmChooser();
                this.internalAlgorithmChooser.MinNeighbors = this.K;
                this.internalAlgorithmChooser.MaxNeighbors = this.K;
                this.internalAlgorithmChooser.IncludeNearestNeighbor = this.IncludeAlgorithmNearestNeighbor;
                this.internalAlgorithmChooser.IncludeKNearestNeighbor = this.IncludeAlgorithmKNearestNeighbor;
                this.internalAlgorithmChooser.IncludeNearestCentroid = this.IncludeAlgorithmNearestCentroid;
                return this.internalAlgorithmChooser;
            }
            set
            {
                AlgorithmChooser chooser = (value != null) ? value : new AlgorithmChooser();
                this.IncludeAlgorithmNearestNeighbor = chooser.IncludeNearestNeighbor;
                this.IncludeAlgorithmKNearestNeighbor = chooser.IncludeKNearestNeighbor;
                this.IncludeAlgorithmNearestCentroid = chooser.IncludeNearestCentroid;
            }
        }
        public AlgorithmChooser AlgorithmChooser
        {
            get { return new AlgorithmChooser(this.AlgorithmChooserInternal); }
            set
            {
                this.AlgorithmChooserInternal = value;
                this.defaultAlgorithmChooser = new AlgorithmChooser(this.AlgorithmChooserInternal);
                RefreshGUI();
            }
        }
        private DistanceChooser DistanceChooserInternal
        {
            get
            {
                if (this.internalDistanceChooser == null) this.internalDistanceChooser = new DistanceChooser();
                this.internalDistanceChooser.MinkowskiMin = this.Minkowski;
                this.internalDistanceChooser.MinkowskiMax = this.Minkowski;
                this.internalDistanceChooser.IncludeCityBlock = this.IncludeDistanceCityBlock;
                this.internalDistanceChooser.IncludeEuclidean = this.IncludeDistanceEuclidean;
                this.internalDistanceChooser.IncludeMaxValue = this.IncludeDistanceMaxValue;
                this.internalDistanceChooser.IncludeMinkowski = this.IncludeDistanceMinkowski;
                this.internalDistanceChooser.IncludeTanimoto = this.IncludeDistanceTanimoto;
                this.internalDistanceChooser.IncludeVIP = this.IncludeDistanceVIP;
                return this.internalDistanceChooser;
            }
            set
            {
                DistanceChooser chooser = (value != null) ? value : new DistanceChooser();
                this.IncludeDistanceCityBlock = chooser.IncludeCityBlock;
                this.IncludeDistanceEuclidean = chooser.IncludeEuclidean;
                this.IncludeDistanceMaxValue = chooser.IncludeMaxValue;
                this.IncludeDistanceMinkowski = chooser.IncludeMinkowski;
                this.IncludeDistanceTanimoto = chooser.IncludeTanimoto;
                this.IncludeDistanceVIP = chooser.IncludeVIP;
            }
        }
        public DistanceChooser DistanceChooser
        {
            get { return new DistanceChooser(this.DistanceChooserInternal); }
            set
            {
                this.DistanceChooserInternal = value;
                this.defaultDistanceChooser = new DistanceChooser(this.DistanceChooserInternal);
                RefreshGUI();
            }
        }
        private NormalizationChooser NormalizationChooserInternal
        {
            get
            {
                if (this.internalNormalizationChooser == null) this.internalNormalizationChooser = new NormalizationChooser();
                this.internalNormalizationChooser.SMaxMin = this.SMax;
                this.internalNormalizationChooser.SMaxMax = this.SMax;
                this.internalNormalizationChooser.SMinMin = this.SMin;
                this.internalNormalizationChooser.SMinMax = this.SMin;
                this.internalNormalizationChooser.SoftmaxMin = this.Softmax;
                this.internalNormalizationChooser.SoftmaxMax = this.Softmax;
                this.internalNormalizationChooser.IncludeNone = this.IncludeNormalizationNone;
                this.internalNormalizationChooser.IncludeMinMax = this.IncludeNormalizationMinMax;
                this.internalNormalizationChooser.IncludeRange = this.IncludeNormalizationRange;
                this.internalNormalizationChooser.IncludeSoftmax = this.IncludeNormalizationSoftmax;
                this.internalNormalizationChooser.IncludeStdNorm = this.IncludeNormalizationStdNorm;
                this.internalNormalizationChooser.IncludeUnitVec = this.IncludeNormalizationUnitVec;
                return this.internalNormalizationChooser;
            }
            set
            {
                NormalizationChooser chooser = (value != null) ? value : new NormalizationChooser();
                this.IncludeNormalizationNone = chooser.IncludeNone;
                this.IncludeNormalizationMinMax = chooser.IncludeMinMax;
                this.IncludeNormalizationRange = chooser.IncludeRange;
                this.IncludeNormalizationSoftmax = chooser.IncludeSoftmax;
                this.IncludeNormalizationStdNorm = chooser.IncludeStdNorm;
                this.IncludeNormalizationUnitVec = chooser.IncludeUnitVec;
            }
        }
        public NormalizationChooser NormalizationChooser
        {
            get { return new NormalizationChooser(this.NormalizationChooserInternal); }
            set
            {
                this.NormalizationChooserInternal = value;
                this.defaultNormalizationChooser = new NormalizationChooser(this.NormalizationChooserInternal);
                RefreshGUI();
            }
        }
        [DefaultValue(Algorithm.NearestNeighbor)]
        public Algorithm Algorithm
        {
            get { return this.currentAlgorithm; }
            set
            {
                switch (value)
                {
                case Algorithm.K_NearestNeighbor:
                    this.rbAlgorithmKNearestNeighbor.PerformClick();
                    break;
                case Algorithm.NearestCentroid:
                    this.rbAlgorithmNearestCentroid.PerformClick();
                    break;
                default:
                    this.rbAlgorithmNearestNeighbor.PerformClick();
                    break;
                }
            }
        }
        [DefaultValue(Distance.Euclidean)]
        public Distance Distance
        {
            get { return this.currentDistance; }
            set
            {
                switch (value)
                {
                case Distance.CityBlock:
                    this.rbDistanceAbsValue.PerformClick();
                    break;
                case Distance.MaxValue:
                    this.rbDistanceMaxValue.PerformClick();
                    break;
                case Distance.Minkowski:
                    this.rbDistanceMinkowski.PerformClick();
                    break;
                case Distance.Tanimoto:
                    this.rbDistanceTanimoto.PerformClick();
                    break;
                case Distance.VectorInnerProduct:
                    this.rbDistanceVIP.PerformClick();
                    break;
                default:
                    this.rbDistanceEuclidean.PerformClick();
                    break;
                }
            }
        }
        [DefaultValue(Normalization.None)]
        public Normalization Normalization
        {
            get { return this.currentNormalization; }
            set
            {
                switch (value)
                {
                case Normalization.None:
                    this.rbNormalizeNone.PerformClick();
                    break;
                case Normalization.MinMax:
                    this.rbNormalizeMinMax.PerformClick();
                    break;
                case Normalization.Range:
                    this.rbNormalizeRange.PerformClick();
                    break;
                case Normalization.Softmax:
                    this.rbNormalizeSoftmax.PerformClick();
                    break;
                case Normalization.UnitVector:
                    this.rbNormalizeUnitVector.PerformClick();
                    break;
                default:
                    this.rbNormalizeStdNorm.PerformClick();
                    break;
                }
            }
        }
        [DefaultValue(3.0F)]
        public float Minkowski
        {
            get { return float.Parse(this.cboMinkowski.Text); }
            set { this.cboMinkowski.Text = ((int)value).ToString(); }
        }
        [DefaultValue(3)]
        public int K
        {
            get { return int.Parse(this.cboK.Text); }
            set { this.cboK.Text = value.ToString(); }
        }
        [DefaultValue(1.0F)]
        public float Softmax
        {
            get { return float.Parse(this.txtSoftmax.Text); }
            set { this.txtSoftmax.Text = ((int)value).ToString(); }
        }
        [DefaultValue(0.0F)]
        public float SMin
        {
            get { return float.Parse(this.txtSMin.Text); }
            set { this.txtSMin.Text = ((int)value).ToString(); }
        }
        [DefaultValue(1.0F)]
        public float SMax
        {
            get { return float.Parse(this.txtSMax.Text); }
            set { this.txtSMax.Text = ((int)value).ToString(); }
        }
        [DefaultValue(true)]
        public bool IncludeAlgorithmNearestNeighbor
        {
            get { return this.chkAlgorithmNearestNeighbor.Checked; }
            set { this.chkAlgorithmNearestNeighbor.Checked = value; }
        }
        [DefaultValue(false)]
        public bool IncludeAlgorithmKNearestNeighbor
        {
            get { return this.chkAlgorithmKNearestNeighbor.Checked; }
            set { this.chkAlgorithmKNearestNeighbor.Checked = value; }
        }
        [DefaultValue(false)]
        public bool IncludeAlgorithmNearestCentroid
        {
            get { return this.chkAlgorithmNearestCentroid.Checked; }
            set { this.chkAlgorithmNearestCentroid.Checked = value; }
        }
        [DefaultValue(false)]
        public bool IncludeDistanceCityBlock
        {
            get { return this.chkDistanceAbsValue.Checked; }
            set { this.chkDistanceAbsValue.Checked = value; }
        }
        [DefaultValue(true)]
        public bool IncludeDistanceEuclidean
        {
            get { return this.chkDistanceEuclidean.Checked; }
            set { this.chkDistanceEuclidean.Checked = value; }
        }
        [DefaultValue(false)]
        public bool IncludeDistanceMaxValue
        {
            get { return this.chkDistanceMaxValue.Checked; }
            set { this.chkDistanceMaxValue.Checked = value; }
        }
        [DefaultValue(false)]
        public bool IncludeDistanceMinkowski
        {
            get { return this.chkDistanceMinkowski.Checked; }
            set { this.chkDistanceMinkowski.Checked = value; }
        }
        [DefaultValue(false)]
        public bool IncludeDistanceTanimoto
        {
            get { return this.chkDistanceTanimoto.Checked; }
            set { this.chkDistanceTanimoto.Checked = value; }
        }
        [DefaultValue(false)]
        public bool IncludeDistanceVIP
        {
            get { return this.chkDistanceVIP.Checked; }
            set { this.chkDistanceVIP.Checked = value; }
        }
        [DefaultValue(true)]
        public bool IncludeNormalizationNone
        {
            get { return this.chkNormalizeNone.Checked; }
            set { this.chkNormalizeNone.Checked = value; }
        }
        [DefaultValue(false)]
        public bool IncludeNormalizationMinMax
        {
            get { return this.chkNormalizeMinMax.Checked; }
            set { this.chkNormalizeMinMax.Checked = value; }
        }
        [DefaultValue(false)]
        public bool IncludeNormalizationRange
        {
            get { return this.chkNormalizeRange.Checked; }
            set { this.chkNormalizeRange.Checked = value; }
        }
        [DefaultValue(false)]
        public bool IncludeNormalizationSoftmax
        {
            get { return this.chkNormalizeSoftmax.Checked; }
            set { this.chkNormalizeSoftmax.Checked = value; }
        }
        [DefaultValue(false)]
        public bool IncludeNormalizationStdNorm
        {
            get { return this.chkNormalizeStdNorm.Checked; }
            set { this.chkNormalizeStdNorm.Checked = value; }
        }
        [DefaultValue(false)]
        public bool IncludeNormalizationUnitVec
        {
            get { return this.chkNormalizeUnitVector.Checked; }
            set { this.chkNormalizeUnitVector.Checked = value; }
        }

        private void chkDistanceVIP_CheckedChanged(object sender, EventArgs e)
        {

        }

        private void grpDistance_Enter(object sender, EventArgs e)
        {

        }

        private void pnlDistanceMultiSelect_Paint(object sender, PaintEventArgs e)
        {

        }

        private void chkDistanceEuclidean_CheckedChanged(object sender, EventArgs e)
        {

        }
    }
}
