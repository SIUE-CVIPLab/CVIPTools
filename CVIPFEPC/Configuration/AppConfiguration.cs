/*''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' ======================================================================
' Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
' ======================================================================
'
'             File Name: AppConfiguration.cs
'           Description: Contains the code for
'                        AppConfiguration class
'         Related Files: MainForm.cs
'                        Classifier.cs
'                        FeatureHeader.cs
'   Initial Coding Date: September 2010
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

using CVIPFEPC.CvipFile;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.IO;
using System.Text;
using System.Windows.Forms;
using System.Xml.Serialization;

namespace CVIPFEPC.Configuration
{
    public class ConfigurationWrapper
    {
        public string ResultsPath = null;
        public Classifier Classifier = null;
        public AlgorithmChooser AlgorithmChooser = null;
        public DistanceChooser DistanceChooser = null;
        public NormalizationChooser NormalizationChooser = null;
        public FeatureHeader Features = null;
        public List<string> ClassList = null;
        public List<ImageObjectWrapper> ImageList = null;
    }
    public class ImageObjectWrapper
    {
        public ImageObjectWrapper() { }
        public ImageObjectWrapper(string fname, string classname, bool istest)
        {
            this.FileName = fname;
            this.ClassName = classname;
            this.IsTestObject = istest;
        }
        public bool IsTestObject = false;
        public string FileName = null;
        public string ClassName = null;
    }
    public static class AppConfiguration
    {
        private static string sConfigFile = Application.StartupPath + @"\FEPC.config";
        private static string sResultsPath = null;
        private static Classifier classifier = null;
        private static AlgorithmChooser chooserAlgorithm = null;
        private static DistanceChooser chooserDistance = null;
        private static NormalizationChooser chooserNormalization = null;
        private static FeatureHeader hdrFeatures = null;
        private static List<string> sClassList = null;
        private static List<ImageObjectWrapper> sImageList = null;

        [Category("Action")]
        [Description("Fires when the ClassList is modified.")]
        static public event Action ClassListChanged;

        static AppConfiguration()
        {
            LoadConfiguration();
        }
        public static void LoadConfiguration()
        {
            LoadConfiguration(AppConfiguration.sConfigFile);
        }
        public static void LoadConfiguration(string fname)
        {
            try
            {
                if (File.Exists(fname))
                {
                    using (StreamReader sr = File.OpenText(fname))
                    {
                        XmlSerializer xs = new XmlSerializer(typeof(ConfigurationWrapper));
                        ConfigurationWrapper config = (ConfigurationWrapper)xs.Deserialize(sr);
                        AppConfiguration.sClassList = config.ClassList;
                        AppConfiguration.sImageList = config.ImageList;
                        AppConfiguration.sResultsPath = config.ResultsPath;
                        AppConfiguration.ClassifierInternal = config.Classifier;
                        AppConfiguration.AlgorithmChooserInternal = config.AlgorithmChooser;
                        AppConfiguration.DistanceChooserInternal = config.DistanceChooser;
                        AppConfiguration.NormalizationChooserInternal = config.NormalizationChooser;
                        AppConfiguration.FeatureHeaderInternal = config.Features;
                    }
                    if (AppConfiguration.ClassListChanged != null)
                        AppConfiguration.ClassListChanged();
                }
            }
            catch { }
        }
        public static void SaveConfiguration()
        {
            SaveConfiguration(AppConfiguration.sConfigFile);
        }
        public static void SaveConfiguration(string fname)
        {
            try
            {
                if (File.Exists(fname))
                    File.Delete(fname);
                using (StreamWriter sw = File.CreateText(fname))
                {
                    ConfigurationWrapper config = new ConfigurationWrapper();
                    config.ClassList = AppConfiguration.ClassList;
                    config.ImageList = AppConfiguration.ImageList;
                    config.ResultsPath = AppConfiguration.ResultsPath;
                    config.Classifier = AppConfiguration.ClassifierInternal;
                    config.AlgorithmChooser = AppConfiguration.AlgorithmChooserInternal;
                    config.DistanceChooser = AppConfiguration.DistanceChooserInternal;
                    config.NormalizationChooser = AppConfiguration.NormalizationChooserInternal;
                    config.Features = AppConfiguration.FeatureHeaderInternal;
                    XmlSerializer xs = new XmlSerializer(typeof(ConfigurationWrapper));
                    xs.Serialize(sw, config);
                }
            }
            catch { }
        }

        public static string ConfigFile { get { return AppConfiguration.sConfigFile; } }
        public static List<string> ClassList
        {
            get
            {
                if (AppConfiguration.sClassList == null)
                    AppConfiguration.sClassList = new List<string>();
                return AppConfiguration.sClassList;
            }
            set
            {
                AppConfiguration.sClassList = value;
                AppConfiguration.ClassList.Sort();
                SaveConfiguration();

                if (AppConfiguration.ClassListChanged != null)
                    AppConfiguration.ClassListChanged();
            }
        }
        public static List<ImageObjectWrapper> ImageList
        {
            get
            {
                if (AppConfiguration.sImageList == null)
                    AppConfiguration.sImageList = new List<ImageObjectWrapper>();
                return AppConfiguration.sImageList;
            }
            set
            {
                AppConfiguration.sImageList = value;
                SaveConfiguration();
            }
        }
        public static string ResultsPath
        {
            get
            {
                if (string.IsNullOrEmpty(AppConfiguration.sResultsPath))
                {
                    AppConfiguration.sResultsPath = System.Environment.GetFolderPath(System.Environment.SpecialFolder.Desktop);
                    AppConfiguration.sResultsPath = AppConfiguration.sResultsPath.TrimEnd('\\') + @"\FEPC_Results\";
                }
                return AppConfiguration.sResultsPath;
            }
            set
            {
                AppConfiguration.sResultsPath = value;
                if (!string.IsNullOrEmpty(AppConfiguration.sResultsPath))
                    AppConfiguration.sResultsPath = AppConfiguration.sResultsPath.TrimEnd('\\') + @"\";
                SaveConfiguration();
            }
        }
        private static Classifier ClassifierInternal
        {
            get
            {
                if (AppConfiguration.classifier == null)
                    AppConfiguration.ClassifierInternal = new Classifier();
                return AppConfiguration.classifier;
            }
            set { AppConfiguration.classifier = value; }
        }
        public static Classifier Classifier
        {
            get { return new Classifier(AppConfiguration.ClassifierInternal); }
            set
            {
                AppConfiguration.ClassifierInternal = value;
                SaveConfiguration();
            }
        }
        private static AlgorithmChooser AlgorithmChooserInternal
        {
            get
            {
                if (AppConfiguration.chooserAlgorithm == null)
                    AppConfiguration.AlgorithmChooserInternal = new AlgorithmChooser();
                return AppConfiguration.chooserAlgorithm;
            }
            set { AppConfiguration.chooserAlgorithm = value; }
        }
        public static AlgorithmChooser AlgorithmChooser
        {
            get { return new AlgorithmChooser(AppConfiguration.AlgorithmChooserInternal); }
            set
            {
                AppConfiguration.AlgorithmChooserInternal = value;
                SaveConfiguration();
            }
        }
        private static DistanceChooser DistanceChooserInternal
        {
            get
            {
                if (AppConfiguration.chooserDistance == null)
                    AppConfiguration.DistanceChooserInternal = new DistanceChooser();
                return AppConfiguration.chooserDistance;
            }
            set { AppConfiguration.chooserDistance = value; }
        }
        public static DistanceChooser DistanceChooser
        {
            get { return new DistanceChooser(AppConfiguration.DistanceChooserInternal); }
            set
            {
                AppConfiguration.DistanceChooserInternal = value;
                SaveConfiguration();
            }
        }
        private static NormalizationChooser NormalizationChooserInternal
        {
            get
            {
                if (AppConfiguration.chooserNormalization == null)
                    AppConfiguration.NormalizationChooserInternal = new NormalizationChooser();
                return AppConfiguration.chooserNormalization;
            }
            set { AppConfiguration.chooserNormalization = value; }
        }
        public static NormalizationChooser NormalizationChooser
        {
            get { return new NormalizationChooser(AppConfiguration.NormalizationChooserInternal); }
            set
            {
                AppConfiguration.NormalizationChooserInternal = value;
                SaveConfiguration();
            }
        }
        private static FeatureHeader FeatureHeaderInternal
        {
            get
            {
                if (AppConfiguration.hdrFeatures == null)
                    AppConfiguration.FeatureHeaderInternal = new FeatureHeader();
                return AppConfiguration.hdrFeatures;
            }
            set { AppConfiguration.hdrFeatures = value; }
        }
        public static FeatureHeader FeatureHeader
        {
            get { return new FeatureHeader(AppConfiguration.FeatureHeaderInternal); }
            set
            {
                AppConfiguration.FeatureHeaderInternal = value;
                SaveConfiguration();
            }
        }
    }
}
