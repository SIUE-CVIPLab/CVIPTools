/*''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' ======================================================================
' Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
' ======================================================================
'
'             File Name: FeaturesDlg.cs
'           Description: Contains the code for
'                        FeaturesDlg dialog
'         Related Files: MainForm.cs
'                        AppConfiguration.cs
'                        FeatureHeader.cs
'   Initial Coding Date: November 2006
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
    public partial class FeaturesDlg : Form
    {
        private FeatureHeader fhDefaults = null;
        private FeatureHeader fhInternal = null;
        private bool bMultiSelect = false;

        public FeaturesDlg()  : this(false) { }
        public FeaturesDlg(bool multiselect)
        {
            InitializeComponent();
            this.bMultiSelect = multiselect;
        }
        private void btnSelectionMode_Click(object sender, EventArgs e)
        {
            SetSelectionMode((sender as Button) == this.btnSwitchToMultiSelect);
        }
        private void SetSelectionMode(bool multiselect)
        {
            this.bMultiSelect = multiselect;

            this.btnSwitchToSingleSelect.Visible = this.bMultiSelect;
           

            this.btnSwitchToMultiSelect.Visible = !this.bMultiSelect;
            if (this.bMultiSelect)
            {
                this.textboxLower.Visible = true;
                this.textboxIncrement.Visible = true;
                this.textboxUpper.Visible = true;
                this.lowerTD.Visible = true;
                this.incrementTD.Visible = true;
                this.upperTD.Visible = true;
                this.lblTextDistance.Visible = false;
                this.cboTextDistance.Visible = false;

            }

            else
            {
                this.textboxLower.Visible = false;
                this.textboxIncrement.Visible = false;
                this.textboxUpper.Visible = false;
                this.lowerTD.Visible = false;
                this.incrementTD.Visible = false;
                this.upperTD.Visible = false;
                this.cboTextDistance.Visible = true;
                this.lblTextDistance.Visible = true;
            }
         

            if (this.bMultiSelect)
                this.Text = "Feature Selection - Combinatoric Selection";
            else
                this.Text = "Feature Selection - Single Selection";
            }
       
        private void btnBinSelectAll_Click(object sender, EventArgs e)
        {
            this.chkBinArea.CheckState = CheckState.Checked;
            this.chkBinAspect.CheckState = CheckState.Checked;
            this.chkBinCentroid.CheckState = CheckState.Checked;
            this.chkBinEuler.CheckState = CheckState.Checked;
            this.chkBinOrientation.CheckState = CheckState.Checked;
            this.chkBinPerimeter.CheckState = CheckState.Checked;
            this.chkBinProjections.CheckState = CheckState.Checked;
            this.chkBinThinness.CheckState = CheckState.Checked;

            CheckDirty();
        }
        private void btnBinSelectNone_Click(object sender, EventArgs e)
        {
            this.chkBinArea.CheckState = CheckState.Unchecked;
            this.chkBinAspect.CheckState = CheckState.Unchecked;
            this.chkBinCentroid.CheckState = CheckState.Unchecked;
            this.chkBinEuler.CheckState = CheckState.Unchecked;
            this.chkBinOrientation.CheckState = CheckState.Unchecked;
            this.chkBinPerimeter.CheckState = CheckState.Unchecked;
            this.chkBinProjections.CheckState = CheckState.Unchecked;
            this.chkBinThinness.CheckState = CheckState.Unchecked;

            CheckDirty();
        }
        private void btnHistSelectAll_Click(object sender, EventArgs e)
        {
            this.chkHistEnergy.CheckState = CheckState.Checked;
            this.chkHistEntropy.CheckState = CheckState.Checked;
            this.chkHistMean.CheckState = CheckState.Checked;
            this.chkHistSkew.CheckState = CheckState.Checked;
            this.chkHistStdDev.CheckState = CheckState.Checked;

            CheckDirty();
        }
        private void btnHistSelectNone_Click(object sender, EventArgs e)
        {
            this.chkHistEnergy.CheckState = CheckState.Unchecked;
            this.chkHistEntropy.CheckState = CheckState.Unchecked;
            this.chkHistMean.CheckState = CheckState.Unchecked;
            this.chkHistSkew.CheckState = CheckState.Unchecked;
            this.chkHistStdDev.CheckState = CheckState.Unchecked;

            CheckDirty();
        }
        private void btnOK_Click(object sender, EventArgs e)
        {
          //  if (!this.FeatureHeaderInternal.Equals(AppConfiguration.FeatureHeader))
                AppConfiguration.FeatureHeader = this.FeatureHeader;
        }
        private void btnReset_Click(object sender, EventArgs e)
        {
            this.FeatureHeaderInternal = this.fhDefaults;
        }
        private void btnRstSelectAll_Click(object sender, EventArgs e)
        {
            this.chkRst1.CheckState = CheckState.Checked;
            this.chkRst2.CheckState = CheckState.Checked;
            this.chkRst3.CheckState = CheckState.Checked;
            this.chkRst4.CheckState = CheckState.Checked;
            this.chkRst5.CheckState = CheckState.Checked;
            this.chkRst6.CheckState = CheckState.Checked;
            this.chkRst7.CheckState = CheckState.Checked;

            CheckDirty();
        }
        private void btnRstSelectNone_Click(object sender, EventArgs e)
        {
            this.chkRst1.CheckState = CheckState.Unchecked;
            this.chkRst2.CheckState = CheckState.Unchecked;
            this.chkRst3.CheckState = CheckState.Unchecked;
            this.chkRst4.CheckState = CheckState.Unchecked;
            this.chkRst5.CheckState = CheckState.Unchecked;
            this.chkRst6.CheckState = CheckState.Unchecked;
            this.chkRst7.CheckState = CheckState.Unchecked;

            CheckDirty();
        }
        private void btnTextSelectAll_Click(object sender, EventArgs e)
        {
            this.chkTextCorrelation.CheckState = CheckState.Checked;
            this.chkTextEnergy.CheckState = CheckState.Checked;
            this.chkTextEntropy.CheckState = CheckState.Checked;
            this.chkTextInertia.CheckState = CheckState.Checked;
            this.chkTextInvDiff.CheckState = CheckState.Checked;

            CheckDirty();
        }
        private void btnTextSelectNone_Click(object sender, EventArgs e)
        {
            this.chkTextCorrelation.CheckState = CheckState.Unchecked;
            this.chkTextEnergy.CheckState = CheckState.Unchecked;
            this.chkTextEntropy.CheckState = CheckState.Unchecked;
            this.chkTextInertia.CheckState = CheckState.Unchecked;
            this.chkTextInvDiff.CheckState = CheckState.Unchecked;

            CheckDirty();
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
        private void CheckDirty()
        {
            this.btnBinSelectAll.Enabled = (this.chkBinArea.CheckState != CheckState.Checked) ||
                                            (this.chkBinAspect.CheckState != CheckState.Checked) ||
                                            (this.chkBinCentroid.CheckState != CheckState.Checked) ||
                                            (this.chkBinEuler.CheckState != CheckState.Checked) ||
                                            (this.chkBinOrientation.CheckState != CheckState.Checked) ||
                                            (this.chkBinPerimeter.CheckState != CheckState.Checked) ||
                                            (this.chkBinProjections.CheckState != CheckState.Checked) ||
                                            (this.chkBinThinness.CheckState != CheckState.Checked);

            this.btnBinSelectNone.Enabled = (this.chkBinArea.CheckState != CheckState.Unchecked) ||
                                            (this.chkBinAspect.CheckState != CheckState.Unchecked) ||
                                            (this.chkBinCentroid.CheckState != CheckState.Unchecked) ||
                                            (this.chkBinEuler.CheckState != CheckState.Unchecked) ||
                                            (this.chkBinOrientation.CheckState != CheckState.Unchecked) ||
                                            (this.chkBinPerimeter.CheckState != CheckState.Unchecked) ||
                                            (this.chkBinProjections.CheckState != CheckState.Unchecked) ||
                                            (this.chkBinThinness.CheckState != CheckState.Unchecked);

            this.btnHistSelectAll.Enabled = (this.chkHistEnergy.CheckState != CheckState.Checked) ||
                                            (this.chkHistEntropy.CheckState != CheckState.Checked) ||
                                            (this.chkHistMean.CheckState != CheckState.Checked) ||
                                            (this.chkHistSkew.CheckState != CheckState.Checked) ||
                                            (this.chkHistStdDev.CheckState != CheckState.Checked);

            this.btnHistSelectNone.Enabled = (this.chkHistEnergy.CheckState != CheckState.Unchecked) ||
                                            (this.chkHistEntropy.CheckState != CheckState.Unchecked) ||
                                            (this.chkHistMean.CheckState != CheckState.Unchecked) ||
                                            (this.chkHistSkew.CheckState != CheckState.Unchecked) ||
                                            (this.chkHistStdDev.CheckState != CheckState.Unchecked);

            this.btnRstSelectAll.Enabled = (this.chkRst1.CheckState != CheckState.Checked) ||
                                            (this.chkRst2.CheckState != CheckState.Checked) ||
                                            (this.chkRst3.CheckState != CheckState.Checked) ||
                                            (this.chkRst4.CheckState != CheckState.Checked) ||
                                            (this.chkRst5.CheckState != CheckState.Checked) ||
                                            (this.chkRst6.CheckState != CheckState.Checked) ||
                                            (this.chkRst7.CheckState != CheckState.Checked);

           

              this.btnRstSelectNone.Enabled = (this.chkRst1.CheckState != CheckState.Unchecked) ||
                                            (this.chkRst2.CheckState != CheckState.Unchecked) ||
                                            (this.chkRst3.CheckState != CheckState.Unchecked) ||
                                            (this.chkRst4.CheckState != CheckState.Unchecked) ||
                                            (this.chkRst5.CheckState != CheckState.Unchecked) ||
                                            (this.chkRst6.CheckState != CheckState.Unchecked) ||
                                            (this.chkRst7.CheckState != CheckState.Unchecked);

            this.btnLawSelectAll.Enabled = (this.chklaw1.CheckState != CheckState.Checked) ||
                                           (this.chklaw2.CheckState != CheckState.Checked) ||
                                           (this.chklaw3.CheckState != CheckState.Checked) ||
                                           (this.chklaw4.CheckState != CheckState.Checked) ||
                                           (this.chklaw5.CheckState != CheckState.Checked) ||
                                           (this.chklaw6.CheckState != CheckState.Checked) ||
                                           (this.chklaw7.CheckState != CheckState.Checked) ||
                                           (this.chklaw8.CheckState != CheckState.Checked) ||
                                            (this.chklaw9.CheckState != CheckState.Checked) ||
                                           (this.chklaw10.CheckState != CheckState.Checked) ||
                                           (this.chklaw11.CheckState != CheckState.Checked) ||
                                           (this.chklaw12.CheckState != CheckState.Checked) ||
                                           (this.chklaw13.CheckState != CheckState.Checked) ||
                                           (this.chklaw14.CheckState != CheckState.Checked) ||
                                           (this.chklaw15.CheckState != CheckState.Checked);
            this.btnLawSelectNone.Enabled = (this.chklaw1.CheckState != CheckState.Unchecked) ||
                                           (this.chklaw2.CheckState != CheckState.Unchecked) ||
                                           (this.chklaw3.CheckState != CheckState.Unchecked) ||
                                           (this.chklaw4.CheckState != CheckState.Unchecked) ||
                                           (this.chklaw5.CheckState != CheckState.Unchecked) ||
                                           (this.chklaw6.CheckState != CheckState.Unchecked) ||
                                           (this.chklaw7.CheckState != CheckState.Unchecked) ||
                                           (this.chklaw8.CheckState != CheckState.Unchecked) ||
                                            (this.chklaw9.CheckState != CheckState.Unchecked) ||
                                           (this.chklaw10.CheckState != CheckState.Unchecked) ||
                                           (this.chklaw11.CheckState != CheckState.Unchecked) ||
                                           (this.chklaw12.CheckState != CheckState.Unchecked) ||
                                           (this.chklaw13.CheckState != CheckState.Unchecked) ||
                                           (this.chklaw14.CheckState != CheckState.Unchecked) ||
                                           (this.chklaw15.CheckState != CheckState.Unchecked);

            this.btnTextSelectAll.Enabled = (this.chkTextCorrelation.CheckState != CheckState.Checked) ||
                                            (this.chkTextEnergy.CheckState != CheckState.Checked) ||
                                            (this.chkTextEntropy.CheckState != CheckState.Checked) ||
                                            (this.chkTextInertia.CheckState != CheckState.Checked) ||
                                            (this.chkTextInvDiff.CheckState != CheckState.Checked);

            this.btnTextSelectNone.Enabled = (this.chkTextCorrelation.CheckState != CheckState.Unchecked) ||
                                            (this.chkTextEnergy.CheckState != CheckState.Unchecked) ||
                                            (this.chkTextEntropy.CheckState != CheckState.Unchecked) ||
                                            (this.chkTextInertia.CheckState != CheckState.Unchecked) ||
                                            (this.chkTextInvDiff.CheckState != CheckState.Unchecked);

            this.btnReset.Enabled = !this.FeatureHeaderInternal.Equals(this.fhDefaults);
        }
        protected override void OnLoad(EventArgs e)
        {
            base.OnLoad(e);
            this.FeatureHeader = AppConfiguration.FeatureHeader;
            SetSelectionMode(this.bMultiSelect);
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
        private void ValueChanged(object sender, EventArgs e)
        {
            CheckDirty();
        }

        private FeatureHeader FeatureHeaderInternal
        {
            get
            {
                if (this.fhInternal == null) this.fhInternal = new FeatureHeader();

                // Binary Features
                this.fhInternal.UseArea = this.chkBinArea.Checked;
                this.fhInternal.UseAspectRatio = this.chkBinAspect.Checked;
                this.fhInternal.UseCentroid = this.chkBinCentroid.Checked;
                this.fhInternal.UseEuler = this.chkBinEuler.Checked;
                this.fhInternal.UseOrientation = this.chkBinOrientation.Checked;
                this.fhInternal.UsePerimeter = this.chkBinPerimeter.Checked;
                this.fhInternal.UseProjections = this.chkBinProjections.Checked;
                this.fhInternal.UseThinness = this.chkBinThinness.Checked;
                this.fhInternal.ProjectionsHeight = this.ProjectionsHeight;
                this.fhInternal.ProjectionsWidth = this.ProjectionsWidth;

                // Histogram Features
                this.fhInternal.UseHistEnergy = this.chkHistEnergy.Checked;
                this.fhInternal.UseHistEntropy = this.chkHistEntropy.Checked;
                this.fhInternal.UseHistMean = this.chkHistMean.Checked;
                this.fhInternal.UseHistSkew = this.chkHistSkew.Checked;
                this.fhInternal.UseHistStdDev = this.chkHistStdDev.Checked;

                // RST-Invariant Features
                this.fhInternal.UseRst1 = this.chkRst1.Checked;
                this.fhInternal.UseRst2 = this.chkRst2.Checked;
                this.fhInternal.UseRst3 = this.chkRst3.Checked;
                this.fhInternal.UseRst4 = this.chkRst4.Checked;
                this.fhInternal.UseRst5 = this.chkRst5.Checked;
                this.fhInternal.UseRst6 = this.chkRst6.Checked;
                this.fhInternal.UseRst7 = this.chkRst7.Checked;

                // Texture Features
                this.fhInternal.UseTexEnergy = this.chkTextEnergy.Checked;
                this.fhInternal.UseTexInertia = this.chkTextInertia.Checked;
                this.fhInternal.UseTexCorrelation = this.chkTextCorrelation.Checked;
                this.fhInternal.UseTexInvDiff = this.chkTextInvDiff.Checked;
                this.fhInternal.UseTexEntropy = this.chkTextEntropy.Checked;
                this.fhInternal.UseCombTex = this.bMultiSelect;
                this.fhInternal.TextureDistance = this.TextureDistance;
               this.fhInternal.TextureDistanceLower = this.TextureDistanceLower;
                this.fhInternal.TextureDistanceUpper = this.TextureDistanceUpper;
                this.fhInternal.TextureDistanceIncrement = this.TextureDistanceIncrement;
                this.fhInternal.TextureUseTexture2 = this.TextureUseTexture2;


                // Spectral Features
                this.fhInternal.UseSpectral = this.chkSpectral.Checked;
                this.fhInternal.SpectralRings = this.SpectralRings;
                this.fhInternal.SpectralSectors = this.SpectralSectors;
                //Law Texture
                this.fhInternal.UseMask1 = this.chklaw1.Checked;
                this.fhInternal.UseMask2 = this.chklaw2.Checked;
                this.fhInternal.UseMask3 = this.chklaw3.Checked;
                this.fhInternal.UseMask4 = this.chklaw4.Checked;
                this.fhInternal.UseMask5 = this.chklaw5.Checked;
                this.fhInternal.UseMask6 = this.chklaw6.Checked;
                this.fhInternal.UseMask7 = this.chklaw7.Checked;
                this.fhInternal.UseMask8 = this.chklaw8.Checked;
                this.fhInternal.UseMask9 = this.chklaw9.Checked;
                this.fhInternal.UseMask10 = this.chklaw10.Checked;
                this.fhInternal.UseMask11 = this.chklaw11.Checked;
                this.fhInternal.UseMask12 = this.chklaw12.Checked;
                this.fhInternal.UseMask13 = this.chklaw13.Checked;
                this.fhInternal.UseMask14 = this.chklaw14.Checked;
                this.fhInternal.UseMask15 = this.chklaw15.Checked;


               

                return this.fhInternal;
            }
            set
            {
                FeatureHeader fh = (value != null) ? value : new FeatureHeader();

                // Binary Features
                this.chkBinArea.Checked = fh.UseArea;
                this.chkBinAspect.Checked = fh.UseAspectRatio;
                this.chkBinCentroid.Checked = fh.UseCentroid;
                this.chkBinEuler.Checked = fh.UseEuler;
                this.chkBinOrientation.Checked = fh.UseOrientation;
                this.chkBinPerimeter.Checked = fh.UsePerimeter;
                this.chkBinProjections.Checked = fh.UseProjections;
                this.chkBinThinness.Checked = fh.UseThinness;
                this.ProjectionsHeight = fh.ProjectionsHeight;
                this.ProjectionsWidth = fh.ProjectionsWidth;

                // Histogram Features
                this.chkHistEnergy.Checked = fh.UseHistEnergy;
                this.chkHistEntropy.Checked = fh.UseHistEntropy;
                this.chkHistMean.Checked = fh.UseHistMean;
                this.chkHistSkew.Checked = fh.UseHistSkew;
                this.chkHistStdDev.Checked = fh.UseHistStdDev;

                // RST-Invariant Features
                this.chkRst1.Checked = fh.UseRst1;
                this.chkRst2.Checked = fh.UseRst2;
                this.chkRst3.Checked = fh.UseRst3;
                this.chkRst4.Checked = fh.UseRst4;
                this.chkRst5.Checked = fh.UseRst5;
                this.chkRst6.Checked = fh.UseRst6;
                this.chkRst7.Checked = fh.UseRst7;
                //Law Texture
                this.chklaw1.Checked = fh.UseMask1;
                this.chklaw2.Checked = fh.UseMask2;
                this.chklaw3.Checked = fh.UseMask3;
                this.chklaw4.Checked = fh.UseMask4;
                this.chklaw5.Checked = fh.UseMask5;
                this.chklaw6.Checked = fh.UseMask6;
                this.chklaw7.Checked = fh.UseMask7;
                this.chklaw8.Checked = fh.UseMask8;
                this.chklaw9.Checked = fh.UseMask9;
                this.chklaw10.Checked = fh.UseMask10;
                this.chklaw11.Checked = fh.UseMask11;
                this.chklaw12.Checked = fh.UseMask12;
                this.chklaw13.Checked = fh.UseMask13;
                this.chklaw14.Checked = fh.UseMask14;
                this.chklaw15.Checked = fh.UseMask15;

                // Texture Features
                this.chkTextEnergy.Checked = fh.UseTexEnergy;
                this.chkTextInertia.Checked = fh.UseTexInertia;
                this.chkTextCorrelation.Checked = fh.UseTexCorrelation;
                this.chkTextInvDiff.Checked = fh.UseTexInvDiff;
                this.chkTextEntropy.Checked = fh.UseTexEntropy;
                this.TextureDistance = fh.TextureDistance;
               // this.UseCombTex = fh.UseCombText;
                this.TextureDistanceLower = fh.TextureDistanceLower;
                this.TextureDistanceIncrement = fh.TextureDistanceIncrement;
                this.TextureDistanceUpper = fh.TextureDistanceUpper;
                this.TextureUseTexture2 = fh.TextureUseTexture2;

                // Spectral Features
                this.chkSpectral.Checked = fh.UseSpectral;
                this.SpectralRings = fh.SpectralRings;
                this.SpectralSectors = fh.SpectralSectors;
            }
        }
        public FeatureHeader FeatureHeader
        {
            get { return new FeatureHeader(this.FeatureHeaderInternal); }
            set
            {
                this.FeatureHeaderInternal = value;
                this.fhDefaults = new FeatureHeader(this.FeatureHeaderInternal);
                CheckDirty();
            }
        }
        public int ProjectionsHeight
        {
            get { return int.Parse(this.txtProjHeight.Text); }
            set { this.txtProjHeight.Text = value.ToString(); }
        }
        public int ProjectionsWidth
        {
            get { return int.Parse(this.txtProjWidth.Text); }
            set { this.txtProjWidth.Text = value.ToString(); }
        }
        public int SpectralRings
        {
            get { return int.Parse(this.txtSpectralRings.Text); }
            set { this.txtSpectralRings.Text = value.ToString(); }
        }
        public int SpectralSectors
        {
            get { return int.Parse(this.txtSpectralSectors.Text); }
            set { this.txtSpectralSectors.Text = value.ToString(); }
        }
        public int TextureDistance
        {
            get { return int.Parse(this.cboTextDistance.Text); }
            set { this.cboTextDistance.Text = value.ToString(); }
        }
        public int TextureDistanceLower
        {
            get { return int.Parse(this.textboxLower.Text); }
            set { this.textboxLower.Text = value.ToString(); }
        }
        public int TextureDistanceIncrement
        {
            get { return int.Parse(this.textboxIncrement.Text); }
            set { this.textboxIncrement.Text = value.ToString(); }
        }
        public int TextureDistanceUpper
        {
            get { return int.Parse(this.textboxUpper.Text); }
            set { this.textboxUpper.Text = value.ToString(); }
        }
        public bool TextureUseTexture2
        {
            get { return this.rbTexture2.Checked; }
            set
            {
                this.rbTexture2.Checked = value;
                this.rbOldTexture.Checked = !value;
            }
        }
          
      

        private void cboTextDistance_SelectedIndexChanged(object sender, EventArgs e)
        {

        }

        private void grpTexture_Enter(object sender, EventArgs e)
        {

        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {

        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void label2_Click(object sender, EventArgs e)
        {

        }

        private void btnSwitchToSingleSelect_Click(object sender, EventArgs e)
        {
           

        }

        private void btnSwitchToMultiSelect_Click(object sender, EventArgs e)
        {

           
        }

        private void btnSwitchToMultiSelect_Click_1(object sender, EventArgs e)
        {
         
         

        }

        private void radioButton11_CheckedChanged(object sender, EventArgs e)
        {

        }

        private void chklaw4_CheckedChanged(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
            
            this.chklaw1.CheckState = CheckState.Checked;
            this.chklaw2.CheckState = CheckState.Checked;
            this.chklaw3.CheckState = CheckState.Checked;
            this.chklaw4.CheckState = CheckState.Checked;
            this.chklaw5.CheckState = CheckState.Checked;
            this.chklaw6.CheckState = CheckState.Checked;
            this.chklaw7.CheckState = CheckState.Checked;
            this.chklaw8.CheckState = CheckState.Checked;
            this.chklaw9.CheckState = CheckState.Checked;
            this.chklaw10.CheckState = CheckState.Checked;
            this.chklaw11.CheckState = CheckState.Checked;
            this.chklaw12.CheckState = CheckState.Checked;
            this.chklaw13.CheckState = CheckState.Checked;
            this.chklaw14.CheckState = CheckState.Checked;
            this.chklaw15.CheckState = CheckState.Checked;

            CheckDirty();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            this.chklaw1.CheckState = CheckState.Unchecked;
            this.chklaw2.CheckState = CheckState.Unchecked;
            this.chklaw3.CheckState = CheckState.Unchecked;
            this.chklaw4.CheckState = CheckState.Unchecked;
            this.chklaw5.CheckState = CheckState.Unchecked;
            this.chklaw6.CheckState = CheckState.Unchecked;
            this.chklaw7.CheckState = CheckState.Unchecked;
            this.chklaw8.CheckState = CheckState.Unchecked;
            this.chklaw9.CheckState = CheckState.Unchecked;
            this.chklaw10.CheckState = CheckState.Unchecked;
            this.chklaw11.CheckState = CheckState.Unchecked;
            this.chklaw12.CheckState = CheckState.Unchecked;
            this.chklaw13.CheckState = CheckState.Unchecked;
            this.chklaw14.CheckState = CheckState.Unchecked;
            this.chklaw15.CheckState = CheckState.Unchecked;

            CheckDirty();
        }

        private void groupBox1_Enter(object sender, EventArgs e)
        {

        }

        private void chklaw1_CheckedChanged(object sender, EventArgs e)
        {

        }

        private void chklaw2_CheckedChanged(object sender, EventArgs e)
        {

        }

        private void chkTextInvDiff_CheckedChanged(object sender, EventArgs e)
        {

        }
    }
}
