/*''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' ======================================================================
' Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
' ======================================================================
'
'             File Name: MainForm.cs
'           Description: Contains the code for
'                        CVIPFEPC MainForm class
'         Related Files: FepcListView.cs
'                        FepcPictureBox.cs
'                        CvipObject.cs
'                        FeatureFile.cs
'   Initial Coding Date: November 2006
'              Modified: February 2012
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
using CVIPFEPC.CustomControls;
using CVIPFEPC.CvipFile;
using CVIPFEPC.Dialogs;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Text;
using System.Threading;
using System.Windows.Forms;
using Microsoft.Win32;
//using System.Collections.Generic;
using System.Linq;
//using System.IO;

namespace CVIPFEPC
{
    public partial class MainForm : Form
    {
        private List<ImageObject> lstNewObjects = new List<ImageObject>();
        private WorkEventArgs argsRunTest = null;
        private WorkerThread thrdBkGndWorker = null;
        private WorkerThread thrdRunTest = null;

        public MainForm()
        {
            InitializeComponent();
        }
        private void btnAbortTest_Click(object sender, EventArgs e)
        {
            if ((this.thrdRunTest != null) && this.thrdRunTest.IsBusy)
            {
                this.btnAbortTest.Enabled = false;
                this.thrdRunTest.RequestCancel();
            }
        }
        private void btnAddFiles_Click(object sender, EventArgs e)
        {
            this.dlgAddFiles.ShowDialog();
        }
        private void btnDelete_Click(object sender, EventArgs e)
        {
            OnDeleteKeyPressed();
        }
        private void btnInvert_Click(object sender, EventArgs e)
        {
            this.Cursor = Cursors.WaitCursor;
            this.lstImages.InvertChecked();
            this.Cursor = Cursors.Default;
        }
        private void btnOutputFolder_Click(object sender, EventArgs e)
        {
            FolderBrowserDialog dlg = new FolderBrowserDialog();
            dlg.SelectedPath = AppConfiguration.ResultsPath;
            if (dlg.ShowDialog() == DialogResult.OK)
            {
                AppConfiguration.ResultsPath = dlg.SelectedPath;
                this.txtOutputFolder.Text = AppConfiguration.ResultsPath;
            }
        }
        private void btnRandomize_Click(object sender, EventArgs e)
        {
            this.Cursor = Cursors.WaitCursor;
            this.lstImages.Randomize();
            this.Cursor = Cursors.Default;
        }
        private void btnRunTest_Click(object sender, EventArgs e)
        {
            if ((this.argsRunTest != null) && (this.thrdRunTest != null))
            {
                this.argsRunTest.NewJob();
                this.btnRunTest.Visible = false;
                this.btnAbortTest.Enabled = true;
                this.btnAbortTest.Visible = true;
                this.thrdRunTest.QueueWork(this.argsRunTest);
            }
        }
        private void cboClasses_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (this.cboClasses.Tag == null) // only run if this is response to user selection
            {
                for (int i = 0; i < this.lstImages.SelectedItems.Count; i++)
                {
                    this.lstImages.SelectedItems[i].SubItems[1].Text = this.cboClasses.Text;
                    this.lstImages.SelectedObjects[i].ClassName = this.cboClasses.Text;
                }
            }
        }
        private void ConfigurationLoad()
        {
            this.Cursor = Cursors.WaitCursor;
            this.btnDelete.Enabled = false;
            this.btnInvert.Enabled = false;
            this.btnRandomize.Enabled = false;
            this.cboClasses.Items.Clear();
            this.lstImages.Items.Clear();
            this.pictCurrentImage.CurrentObject = null;
            this.txtOutputFolder.Text = AppConfiguration.ResultsPath;
            this.udImages.Max = 0;
            if (AppConfiguration.ImageList.Count > 0)
            {
                List<ImageObject> newObjects = new List<ImageObject>();
                foreach (ImageObjectWrapper img in AppConfiguration.ImageList)
                {
                    FileInfo fi = new FileInfo(img.FileName);
                    if (!fi.Exists) continue;
                    ImageObject obj = new ImageObject(fi, img.ClassName);
                    this.lstImages.Add(obj, img.IsTestObject);
                    newObjects.Add(obj);
                }
                if (newObjects.Count > 0)
                    QueueBackgroundWork(newObjects);
            }
            OnClassListChanged();
            this.Cursor = Cursors.Default;
        }
        private void ConfigurationSave()
        {
            this.Cursor = Cursors.WaitCursor;
            List<ImageObjectWrapper> images = new List<ImageObjectWrapper>();
            for (int i = 0; i < this.lstImages.Items.Count; i++)
            {
                bool istestobject = this.lstImages.Items[i].Checked;
                string fname = this.lstImages.Items[i].Name;
                string classname = this.lstImages[i].ClassName;
                images.Add(new ImageObjectWrapper(fname, classname, istestobject));
            }
            AppConfiguration.ImageList = images;
            this.Cursor = Cursors.Default;
        }
        private void dlgAddFiles_FileOk(object sender, CancelEventArgs e)
        {
            this.Activate();
            this.Cursor = Cursors.WaitCursor;
            List<ImageObject> newObjects = new List<ImageObject>();
            try
            {
                foreach (string fname in this.dlgAddFiles.FileNames)
                {
                    FileInfo fi = new FileInfo(fname);
                    if (!fi.Exists) continue;
                    ImageObject obj = new ImageObject(fi);
                    this.lstImages.Add(obj);
                    newObjects.Add(obj);
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
            if (newObjects.Count > 0)
                QueueBackgroundWork(newObjects);
            this.Cursor = Cursors.Default;
        }

      
        private void lstImages_ColumnClick(object sender, ColumnClickEventArgs e)
        {
            this.lstImages.SortColumn = e.Column;
        }
        private void lstImages_ItemSelectionChanged(object sender, ListViewItemSelectionChangedEventArgs e)
        {
            string classname = null;
            this.btnDelete.Enabled = this.lstImages.SelectedItems.Count > 0;
            if (this.lstImages.SelectedItems.Count > 0)
            {
                classname = this.lstImages.SelectedObjects[0].ClassName;
                foreach (ImageObject obj in this.lstImages.SelectedObjects)
                {
                    if (obj.ClassName != classname)
                    {
                        classname = null;
                        break;
                    }
                }
                if (e.IsSelected && (this.lstImages.SelectedItems.Count == 1))
                {
                    this.pictCurrentImage.CurrentObject = this.lstImages[e.ItemIndex];
                    this.udImages.Value = e.ItemIndex;
                }
            }
            // set .Tag to flag that this value is being set by code, not user.
            this.cboClasses.Tag = true;
            this.cboClasses.Text = classname;
            this.cboClasses.Tag = null;
        }
        private void mnuFileExit_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }
        private void mnuFileLoadConfig_Click(object sender, EventArgs e)
        {
            OpenFileDialog dlgOpen = new OpenFileDialog();
            dlgOpen.CheckFileExists = true;
            dlgOpen.Filter = "All Files(*.*)|*.*|FEPC Config Files (*.config)|*.config";
            dlgOpen.FilterIndex = 2;
            dlgOpen.InitialDirectory = new FileInfo(AppConfiguration.ConfigFile).DirectoryName;
            dlgOpen.Multiselect = false;
            dlgOpen.Title = "Load Configuration";
            if (dlgOpen.ShowDialog() == DialogResult.OK)
            {
                AppConfiguration.LoadConfiguration(dlgOpen.FileName);
                ConfigurationLoad();
            }
        }
        private void mnuFileSaveConfig_Click(object sender, EventArgs e)
        {
            SaveFileDialog dlgSave = new SaveFileDialog();
            dlgSave.Filter = "All Files(*.*)|*.*|FEPC Config Files (*.config)|*.config";
            dlgSave.FilterIndex = 2;
            dlgSave.InitialDirectory = new FileInfo(AppConfiguration.ConfigFile).DirectoryName;
            dlgSave.Title = "Save Configuration";
            if (dlgSave.ShowDialog() == DialogResult.OK)
            {
                ConfigurationSave();
                AppConfiguration.SaveConfiguration(dlgSave.FileName);
            }
        }
        private void mnuSettingsClasses_Click(object sender, EventArgs e)
        {
            new ClassesDlg().ShowDialog();
        }
        private void mnuSettingsClassification_Click(object sender, EventArgs e)
        {
            new ClassificationDlg(this.rbCombinatoric.Checked).ShowDialog();
        }
        private void mnuSettingsFeatures_Click(object sender, EventArgs e)
        {
            new FeaturesDlg(this.rbCombinatoric.Checked).ShowDialog();
        }
        private void OnClassListChanged()
        {
            this.cboClasses.Items.Clear();
            this.cboClasses.Items.AddRange(AppConfiguration.ClassList.ToArray());
            for (int i = 0; i < this.lstImages.Items.Count; i++)
            {
                if (!AppConfiguration.ClassList.Contains(this.lstImages[i].ClassName))
                {
                    this.lstImages[i].ClassName = null;
                    this.lstImages.Items[i].SubItems[1].Text = null;
                }
            }
            string classname = null;
            if (this.lstImages.SelectedItems.Count > 0)
            {
                classname = this.lstImages.SelectedObjects[0].ClassName;
                foreach (ImageObject obj in this.lstImages.SelectedObjects)
                {
                    if (obj.ClassName != classname)
                    {
                        classname = null;
                        break;
                    }
                }
            }
            // set .Tag to flag that this value is being set by code, not user.
            this.cboClasses.Tag = true;
            this.cboClasses.Text = classname;
            this.cboClasses.Tag = null;
        }
        private void OnClassSelectionChanged(object sender, ToolStripItemClickedEventArgs e)
        {
            this.cboClasses.Text = e.ClickedItem.Text;
        }
        private void OnDeleteKeyPressed()
        {
            this.lstImages.RemoveSelected();
            if (this.lstImages.Items.Count > 0)
            {
                this.udImages.Max = this.lstImages.Items.Count - 1;
                this.lstImages.Items[this.udImages.Value].Selected = true;
            }
            else
            {
                this.btnInvert.Enabled = false;
                this.btnRandomize.Enabled = false;
                this.udImages.Max = 0;
                this.pictCurrentImage.CurrentObject = null;
            }
        }
        private void OnDoBkGndWork(WorkEventArgs e)
        {
            int tmp = 0;
            List<ImageObject> newObjects = new List<ImageObject>();
            while ((tmp = this.lstNewObjects.Count) > 0)
            {
                lock (this.lstNewObjects)
                {
                    newObjects.AddRange(this.lstNewObjects.GetRange(0, tmp));
                    this.lstNewObjects.RemoveRange(0, tmp);
                }
                while (newObjects.Count > 0)
                {
                    tmp = newObjects[newObjects.Count - 1].Row;
                    newObjects.RemoveAt(newObjects.Count - 1);
                }
            }
        }
        protected override void OnFormClosing(FormClosingEventArgs e)
        {
            if (this.thrdRunTest != null)
            {
                if (this.thrdRunTest.IsBusy)
                {
                    string msg = "The current test is still running. Would you like to abort it?";
                    string caption = "Test Running";
                    e.Cancel = (MessageBox.Show(msg, caption, MessageBoxButtons.YesNo) != DialogResult.Yes);
                }
                if (!e.Cancel)
                {
                    this.thrdRunTest.RequestAbort();
                    if (!this.thrdRunTest.Join(3000))
                        this.thrdRunTest.Abort();
                }
            }
            ConfigurationSave();
            base.OnFormClosing(e);
        }
        protected override void OnLoad(EventArgs e)
        {
            base.OnLoad(e);

            this.thrdBkGndWorker = new WorkerThread(this.OnDoBkGndWork);
            this.thrdBkGndWorker.SetApartmentState(ApartmentState.STA);
            this.thrdBkGndWorker.Priority = ThreadPriority.BelowNormal;
            this.thrdBkGndWorker.IsBackground = true;
            this.thrdBkGndWorker.Name = "BackgroundWorker";
            this.thrdBkGndWorker.StartThread();

            this.thrdRunTest = new WorkerThread(this.OnRunTest);
            this.thrdRunTest.SetApartmentState(ApartmentState.STA);
            this.thrdRunTest.Name = "TestRunner";
            this.thrdRunTest.ProgressChanged += this.OnProgressChanged;
            this.thrdRunTest.WorkCompleted += this.OnWorkCompleted;
            this.thrdRunTest.StartThread();
            this.argsRunTest = new MultiStepJobEventArgs(this.thrdRunTest);

            ConfigurationLoad();
        }
        private void OnRunTest(WorkEventArgs e)
        {
            e.ReportProgress(WorkerThread.LookupString(RunTestState.InitializingTest));
            FeatureFileGet delGetFF = new FeatureFileGet(this.lstImages.GetFeatureFile);
            Tuple<FeatureFileSet, string> result = e.InvokeDelegate(delGetFF) as Tuple<FeatureFileSet, string>;
            FeatureFileSet ffs = result.Item1;
            ffs.FeatureHeader.TextureDistanceCalc = ffs.FeatureHeader.TextureDistance;
            
            if (ffs == null)
            {
                e.ErrorMsg = result.Item2;
                return;
            }
            if (ffs.FeatureHeader.NumFeatures == 0)
            {
                e.ErrorMsg = "No features are selected. Please select some features.";
                return;
            }
            if (e.CancellationRequested)
            {
                e.WorkCancelled = true;
                return;
            }
            if (this.rbSingle.Checked)
                OnSingleTest(ffs, e as MultiStepJobEventArgs);
            else
                OnCombinatoricTest(ffs, e as MultiStepJobEventArgs);

            ffs.ResetFeatureVectors();
        }
        private void OnSingleTest(FeatureFileSet ffs, MultiStepJobEventArgs e)
        {
            int i = 0;
            string path = AppConfiguration.ResultsPath + "Experiment";
            for (i = 1; Directory.Exists(path + i); i++) ;
            ffs.WorkingDirectory = path + i;

            ffs.WriteFeatureFileSet(e);
            if ((e.ErrorMsg != null) || e.WorkCancelled)
            {
                return;
            }
            if (this.rbLeave1Out.Checked)
                ffs.Classifier.ClassifyLeaveOneOut(ffs, e);
            else
            {
                e.ReportProgress(WorkerThread.LookupString(RunTestState.ClassifyTestTraining));
                ffs.Classifier.ClassifyTrainingTest(ffs, e);
            }
            if (e.ErrorMsg != null)
            {
                return;
            }
            e.NewJob(RunTestState.TestComplete);
            e.ReportProgress();
            e.WorkResult = ffs.ResultsFile;
        }
        private void OnCombinatoricTest(FeatureFileSet ffs, MultiStepJobEventArgs e)
        {
            ffs.Classifier.Append(AppConfiguration.AlgorithmChooser);
            ffs.Classifier.Append(AppConfiguration.DistanceChooser);
            ffs.Classifier.Append(AppConfiguration.NormalizationChooser);
            ffs.Classifier.Append(new SpectralChooser());
            ffs.Classifier.Append(new TextureChooser());
            ffs.Classifier.Append(new HistogramChooser());
            ffs.Classifier.Append(new RstChooser());
            ffs.Classifier.Append(new LawChooser());
            ffs.Classifier.Append(new BinaryChooser());
            ffs.FeatureHeader.TextureDistanceCalc = ffs.FeatureHeader.TextureDistance;
           

            if (ffs.Classifier.NumCombinations == 0)
            {
                e.ErrorMsg = "Please check classification parameters. No experiments will run with current selection.";
                return;
            }
            if (ffs.FeatureHeader.NumCombinations == 1)
            {
                e.ErrorMsg = "No features are selected. Please select some features.";
                return;
            }
            if (this.rbLeave1Out.Checked)
            {
                if (!ffs.FeatureHeader.UseCombText || (!ffs.FeatureHeader.UseTexCorrelation &&
                                                       !ffs.FeatureHeader.UseTexEnergy &&
                                                       !ffs.FeatureHeader.UseTexEntropy &&
                                                       !ffs.FeatureHeader.UseTexInertia &&
                                                       !ffs.FeatureHeader.UseTexInvDiff))
                    OnCombinatoricLeaveOneOut(ffs, e);
                else
                {
                    int i = 0;
                    int noTesDistance;
                    noTesDistance = ((ffs.FeatureHeader.TextureDistanceUpper - ffs.FeatureHeader.TextureDistanceLower) / ffs.FeatureHeader.TextureDistanceIncrement)+1;
                    if (noTesDistance <= 0)
                    {
                        e.ErrorMsg = "Upper level should be greater than lower level texture distance";
                        return;
                    }
                    else
                    {
                        for (i = 0; i < noTesDistance; i++)
                        {
                            OnCombinatoricLeaveOneOut(ffs, e);
                            if (i < noTesDistance - 1)
                            ffs.FeatureHeader.TextureDistanceCalc = ffs.FeatureHeader.TextureDistanceCalc + ffs.FeatureHeader.TextureDistanceIncrement;
                        }
                    }
                }             
            }
               
            else{
                if (!ffs.FeatureHeader.UseCombText || (!ffs.FeatureHeader.UseTexCorrelation &&
                                                           !ffs.FeatureHeader.UseTexEnergy &&
                                                           !ffs.FeatureHeader.UseTexEntropy &&
                                                           !ffs.FeatureHeader.UseTexInertia &&
                                                           !ffs.FeatureHeader.UseTexInvDiff))
                    OnCombinatoricTrainingTest(ffs, e);
            else
            {
                int i = 0;
                int noTesDistance;
                noTesDistance=((ffs.FeatureHeader.TextureDistanceUpper - ffs.FeatureHeader.TextureDistanceLower) / ffs.FeatureHeader.TextureDistanceIncrement)+1 ;
                if (noTesDistance <= 0)
                {
                    e.ErrorMsg = "Upper level should be greater than lower level texture distance";
                    return;
                }
                else
                {
                    for (i = 0; i < noTesDistance; i++)
                    {
                        OnCombinatoricTrainingTest(ffs, e);
                        if (i < noTesDistance - 1)
                        ffs.FeatureHeader.TextureDistanceCalc = ffs.FeatureHeader.TextureDistanceCalc + ffs.FeatureHeader.TextureDistanceIncrement;
                    }
                }
                }               
            }
        }
        private void OnCombinatoricLeaveOneOut(FeatureFileSet ffs, MultiStepJobEventArgs e)
        {
            int i = 0;
            string path = AppConfiguration.ResultsPath + "Experiment";
            for (i = 1; Directory.Exists(path + i); i++) ;
            ffs.WorkingDirectory = path + i;
            Directory.CreateDirectory(ffs.WorkingDirectory);
            string sOverallResults = ffs.WorkingDirectory + @"\Overall Results" + i + ".csv";
            using (StreamWriter sw = File.CreateText(sOverallResults))
            {
                Classifier classifier = ffs.Classifier;
                FeatureHeader fh = ffs.FeatureHeader;
                MultiStepJobEventArgs args = new MultiStepJobEventArgs(e.WorkerThread);
                args.WorkerReportsProgress = false;

                ulong numcombinations = classifier.NumCombinations * (fh.NumCombinations - 1);
                e.NewJob((int)numcombinations, RunTestState.CombinatoricTest);
                e.ReportProgress();
                try
                {
                    ffs.BeginCombinatoricTest();

                    string headercolumn = classifier.SelectionValue + ", " + classifier.ClassifyLeaveOneOut(ffs, args) + "," + classifier.tmpclass1 + "," + classifier.tmpclass2 + "," + classifier.tmpclass3 + "," + classifier.tmpclass4 + "," + classifier.tmpclass5 + "," + classifier.tmpclass6 + "," + classifier.tmpclass7 + "," + classifier.tmpclass8 + "," + classifier.tmpclass9 + "," + classifier.tmpclass10;
                   
                    sw.WriteLine(classifier.SelectionHeader + ", # Correct (out of " + ffs.TrainingSet.Count + ")" + "," + classifier.tmpheader);
                    
                    do
                    {
                        ffs.WriteFeatureFileSet(args);
                        if ((args.ErrorMsg != null) || args.WorkCancelled)
                        {
                            e.ErrorMsg = args.ErrorMsg;
                            e.WorkCancelled = args.WorkCancelled;
                            return;                         
                        }
                        ffs.ResetCombinatoricIndex();
                        do
                        {
                            sw.WriteLine(classifier.SelectionValue + ", " + classifier.ClassifyLeaveOneOut(ffs, args) + "," + classifier.tmpclass1 + "," + classifier.tmpclass2 + "," + classifier.tmpclass3 + "," + classifier.tmpclass4+ "," + classifier.tmpclass5 + "," + classifier.tmpclass6 + "," + classifier.tmpclass7 + "," + classifier.tmpclass8+ "," + classifier.tmpclass9 + "," + classifier.tmpclass10);
                                                             
                            if ((args.ErrorMsg != null) || args.WorkCancelled)
                            {
                                e.ErrorMsg = args.ErrorMsg;
                                e.WorkCancelled = args.WorkCancelled;
                                return;
                            }
                            e.StepComplete();
                            e.ReportProgress();
                        }
                        while (!ffs.IncrementCombinatoricIndex());
                    }
                    while (!classifier.Increment());
                }
                finally
                {
                    ffs.EndCombinatoricTest();
                }
            }
            e.NewJob(RunTestState.TestComplete);
            e.ReportProgress();
            e.WorkResult = sOverallResults;
        }
        private void OnCombinatoricTrainingTest(FeatureFileSet ffs, MultiStepJobEventArgs e)
        {
            int i = 0;
            string path = AppConfiguration.ResultsPath + "Experiment";
            for (i = 1; Directory.Exists(path + i); i++) ;
            ffs.WorkingDirectory = path + i;
            Directory.CreateDirectory(ffs.WorkingDirectory);
            string sOverallResults = ffs.WorkingDirectory + @"\Overall Results" + i + ".csv";
            using (StreamWriter sw = File.CreateText(sOverallResults))
            {
                Classifier classifier = ffs.Classifier;   
                FeatureHeader fh = ffs.FeatureHeader;
                MultiStepJobEventArgs args = new MultiStepJobEventArgs(e.WorkerThread);
                args.WorkerReportsProgress = false;

                ulong numcombinations = classifier.NumCombinations * (fh.NumCombinations - 1);
                e.NewJob((int)numcombinations, RunTestState.CombinatoricTest);
                e.ReportProgress();
                try
                {
                    ffs.BeginCombinatoricTest();

                    string headercolumn = classifier.SelectionValue + ", " + classifier.ClassifyTrainingTest(ffs, args) + "," + classifier.tmpclass1 + "," + classifier.tmpclass2 + "," + classifier.tmpclass3 + "," + classifier.tmpclass4 + "," + classifier.tmpclass5 + "," + classifier.tmpclass6 + "," + classifier.tmpclass7 + "," + classifier.tmpclass8 + "," + classifier.tmpclass9 + "," + classifier.tmpclass10;

                    sw.WriteLine(classifier.SelectionHeader + ", # Correct (out of " + ffs.TestSet.Count + ")" + "," + classifier.tmpheader);
                    do
                    {
                        ffs.WriteFeatureFileSet(args);
                        if ((args.ErrorMsg != null) || args.WorkCancelled)
                        {
                            e.ErrorMsg = args.ErrorMsg;
                            e.WorkCancelled = args.WorkCancelled;
                            return;
                        }
                        ffs.ResetCombinatoricIndex();
                        do
                        {
                            sw.WriteLine(classifier.SelectionValue + ", " + classifier.ClassifyTrainingTest(ffs, args) + "," + classifier.tmpclass1 + "," + classifier.tmpclass2 + "," + classifier.tmpclass3 + "," + classifier.tmpclass4 + "," + classifier.tmpclass5 + "," + classifier.tmpclass6 + "," + classifier.tmpclass7 + "," + classifier.tmpclass8 + "," + classifier.tmpclass9 + "," + classifier.tmpclass10);
                            if ((args.ErrorMsg != null) || args.WorkCancelled)
                            {
                                e.ErrorMsg = args.ErrorMsg;
                                e.WorkCancelled = args.WorkCancelled;
                                return;
                            }
                            e.StepComplete();
                            e.ReportProgress();
                        }
                        while (!ffs.IncrementCombinatoricIndex());
                    }
                    while (!classifier.Increment());
                }
                finally
                {
                    ffs.EndCombinatoricTest();
                }
            }
            e.NewJob(RunTestState.TestComplete);
            e.ReportProgress();
            e.WorkResult = sOverallResults;
        }
        private void OnProgressChanged(ProgressChangedEventArgs e)
        
        {
            string status = e.StatusMessage;
            string tooltip = null;
            MultiStepJobProgressChangedArgs eMulti = e as MultiStepJobProgressChangedArgs;
            if (eMulti != null)
            {
                string workmsg = WorkerThread.LookupString(eMulti.WorkType);
                if (string.IsNullOrEmpty(status))
                    status = workmsg;
                if (eMulti.StepsTotal > 0)
                    tooltip = workmsg + ": " + eMulti.StepsFinished + " out of " + eMulti.StepsTotal + " steps complete.";
            }
            this.lblStatus.Text = status;
            this.pbStatus.ToolTipText = tooltip;
            this.pbStatus.Value = e.ProgressPercentage;
        }
        private void OnWorkCompleted(WorkCompletedEventArgs e)
        {
            if (e.Exception != null)
            {
					MessageBox.Show(e.Exception.ToString(), "Test Exception",
                    MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
            else if (e.ErrorMsg != null)
            {
					MessageBox.Show(e.ErrorMsg, "Test Error",
                    MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
            else if (e.WorkResult != null)
            {
                TestCompleteDlg dlg = new TestCompleteDlg((string)e.WorkResult);
                dlg.ShowDialog(this);
            }
            else if (e.WorkCancelled)
            {
                MessageBox.Show("Operation aborted by user.", "Test Aborted",
                    MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
            else
            {
                MessageBox.Show("Test thread has terminated prematurely. Result status is unknown.",
                    "Test Status Unknown", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
            }
            this.lblStatus.Text = WorkerThread.LookupString(RunTestState.Ready);
            this.pbStatus.ToolTipText = "";
            this.pbStatus.Value = 0;
            this.btnAbortTest.Visible = false;
            this.btnRunTest.Visible = true;
        }
        private void QueueBackgroundWork(List<ImageObject> newObjects)
        {
            if (newObjects.Count > 0)
            {
                this.btnInvert.Enabled = this.rbTestTraining.Checked;
                this.btnRandomize.Enabled = this.rbTestTraining.Checked;
                this.lstImages.ReSort();
                this.udImages.Max = this.lstImages.Items.Count - 1;
                if (this.lstImages.SelectedItems.Count == 0)
                    this.lstImages.Items[0].Selected = true;

                lock (this.lstNewObjects) this.lstNewObjects.AddRange(newObjects);
                this.thrdBkGndWorker.QueueWork();
            }
        }
        private void rbTestTrainingLeave1Out_CheckedChanged(object sender, EventArgs e)
        {
            this.lstImages.CheckBoxes = this.rbTestTraining.Checked;
            if (this.lstImages.Items.Count > 0)
            {
                this.btnInvert.Enabled = this.rbTestTraining.Checked;
                this.btnRandomize.Enabled = this.rbTestTraining.Checked;
            }
        }
        private void rbView_CheckedChanged(object sender, EventArgs e)
        {
            if (this.rbViewOriginal.Checked)
                this.pictCurrentImage.ShowImage();
            else if (this.rbViewMask.Checked)
                this.pictCurrentImage.ShowMask();
            else
                this.pictCurrentImage.ShowMaskedImage();
        }
        private void txtOutputFolder_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
        {
            try
            {
                FileInfo fi = new FileInfo(this.txtOutputFolder.Text);
                if (!Directory.Exists(fi.DirectoryName))
                    Directory.CreateDirectory(fi.DirectoryName);
                System.Diagnostics.Process.Start(fi.FullName);
            }
            catch { }
        }
        private void udImages_Click()
        {
            this.lstImages.SelectedItems.Clear();
            this.lstImages.Items[this.udImages.Value].Selected = true;
        }
        protected override void WndProc(ref Message m)
        {
            switch (m.Msg)
            {
            case 0x0001: // WM_CREATE
                AppConfiguration.ClassListChanged += this.OnClassListChanged;
                this.lstImages.ClassSelectionChanged += this.OnClassSelectionChanged;
                this.lstImages.DeleteKeyPressed += this.OnDeleteKeyPressed;
                break;
            case 0x0002: // WM_DESTROY
                AppConfiguration.ClassListChanged -= this.OnClassListChanged;
                this.lstImages.ClassSelectionChanged -= this.OnClassSelectionChanged;
                this.lstImages.DeleteKeyPressed -= this.OnDeleteKeyPressed;
                break;
            }
            base.WndProc(ref m);
        }

        private void lstImages_SelectedIndexChanged(object sender, EventArgs e)
        {

        }

        private void grpTestType_Enter(object sender, EventArgs e)
        {

        }

        private void label1_Click(object sender, EventArgs e)
        {
           
        }

        private void toolStripMenuItem1_Click(object sender, EventArgs e)
        {
            
        }

        private void rbCombinatoric_CheckedChanged(object sender, EventArgs e)
        {

        }

        private void lblOutputFolder_Click(object sender, EventArgs e)
        {

        }

        private void contentsToolStripMenuItem_Click(object sender, EventArgs e)
        {
           
            string cvipHome = @"HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Control\Session Manager\Environment";
            cvipHome = (string)Registry.GetValue(cvipHome, "CVIPtoolsHOME", null);
           // MessageBox.Show(cvipHome.ToString());
            if (string.IsNullOrEmpty(cvipHome))
            {
                MessageBox.Show("Can't find the FEPC help file. The CVIPtoolsHOME environment variable is not set.",
                    "FEPCHELP Not Found", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                return;
            }
            FileInfo fi = new FileInfo(cvipHome + @"HELP\FEPCHelp.CHM");
            if (!fi.Exists)
            {
                MessageBox.Show("The file: " + fi.FullName + " is missing.", "FEPCHELP Not Found",
                    MessageBoxButtons.OK, MessageBoxIcon.Warning);
                return;
            }
            System.Diagnostics.Process.Start(fi.FullName);
        
        }

        private void aboutFEPCToolStripMenuItem_Click(object sender, EventArgs e)
        {
            new AboutDlg().ShowDialog();
        }

        private void btnLaw_Click(object sender, EventArgs e)
        {
            OpenFileDialog fdlg = new OpenFileDialog();
            fdlg.Title = "C# Corner Open File Dialog";
            fdlg.InitialDirectory = @"c:\";
            fdlg.Filter = "All files (*.*)|*.*|All files (*.*)|*.*";
            fdlg.FilterIndex = 2;
            fdlg.RestoreDirectory = true;
            if (fdlg.ShowDialog() == DialogResult.OK)
            {
               
            }
        }
    }
}
