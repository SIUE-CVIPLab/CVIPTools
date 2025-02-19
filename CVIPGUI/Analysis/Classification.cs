/*''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' ======================================================================
' Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
' ======================================================================
'
'             File Name: Classification.cs
'           Description: Contains the controls and code
'                        for Analysis->Classification page
'         Related Files: CvipOp.cs
'                        CvipConstant.cs
'   Initial Coding Date: July 2009
'              Modified: March 2010
'       Delevoping tool: Visual Studio 2010-C#
'             Credit(s): Patrick Solt
'                        Jhansi Lakshmi Akkineni
'                        Southern Illinois University Edwardsville
'
' Copyright (C) 2014 Scott Umbaugh and SIUE
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
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Text;
using System.Windows.Forms;
using Excel = Microsoft.Office.Interop.Excel;

namespace CVIPGUI.Analysis
{
    public partial class Classification : UserControl
    {
        string outputFile;
        string trainSetFile;
        string testSetFile;
        FeatureViewer myFeatureResults = new FeatureViewer();
        ClassificationResults myClassificationResults = new ClassificationResults();
        FeatureFile myFeatureFile = new FeatureFile();
        FeatureHeader myFeatureHeader = new FeatureHeader();

        public Classification()
        {
            InitializeComponent();
        }
        protected override void OnLoad(EventArgs e)
        {
            base.OnLoad(e);
            if (MainForm.Viewers != null)
            {
                string cvipHome = MainForm.CVIPtoolsHOME;
                if (!string.IsNullOrEmpty(cvipHome))
                {
                    string[] nameList = Directory.GetFiles(cvipHome + @"bin\feature");
                    for (int i = 0; i < nameList.Length; i++)
                        nameList[i] = new FileInfo(nameList[i]).Name;
                    cboTrainingSet.Items.Clear();
                    cboTestSet.Items.Clear();
                    cboOutput.Items.Clear();
                    cboTrainingSet.Items.AddRange(nameList);
                    cboTestSet.Items.AddRange(nameList);
                    cboOutput.Items.AddRange(nameList);
                }
            }
        }
        private void btnApply_Click(object sender, EventArgs e)
        {
            if (File.Exists(outputFile))
            {
                this.Cursor = Cursors.Default;
                string msg = "File " + outputFile + " already exists.\n";
                msg += "Do you want to Overwrite it?";
                if (MessageBox.Show(msg, "Information", MessageBoxButtons.YesNo, MessageBoxIcon.Information) == DialogResult.No)
                    return;
                else
                    File.Delete(outputFile);
            }
            if (rbLeaveOneOut.Checked)
                LeaveOneOutTest(myFeatureFile);
            else
                classify(testSetFile, trainSetFile, outputFile);
        }
        public void LeaveOneOutTest(FeatureFile ff)
        {
            int idx, i = 0;
            string s, tmptxt = trainSetFile;
            if (tmptxt.Contains(".txt"))
            {
                idx = tmptxt.IndexOf(".txt");
                tmptxt = tmptxt.Substring(0, idx).Trim();
            }
            string tmpOutput = "";
            int count = ff.Count;
            string[] testObjects = new string[count];
            string[] trainObjects = new string[count];
            string[] totalObjects = new string[count];
            string strTest = tmptxt + "_Test.txt";
            string strTrain = tmptxt + "_Train.txt";
            string featureFileHome = MainForm.CVIPtoolsHOME;
            featureFileHome = featureFileHome + @"bin\feature\";
            string strResult = featureFileHome + saveOutputFile.FileName;
            count = 0;
            for (int idxTest = 0; idxTest < ff.Count; idxTest++)
            {
                ff.WriteLooTrainingSet(strTrain, idxTest);
                ff.WriteLooTestSet(strTest, idxTest);
                this.classify(strTest, strTrain, strResult);
                using (StreamReader sr = File.OpenText(strResult))
                {
                    while ((s = sr.ReadLine()) != null)
                    {
                        if (i == 0)
                        {
                            tmpOutput += s;
                            tmpOutput += "\r\n";
                        }
                        if (s.Contains("*** END OF PATTERN CLASSIFICATION HEADER ***"))
                            break;
                    }
                    while ((s = sr.ReadLine()) != null)
                    {
                        s = s.Trim();
                        if (string.IsNullOrEmpty(s))
                            continue;
                        if (s.Contains("*** STATISTICS ***"))
                            break;
                        if (i == 0)
                            tmpOutput += "\r\n\r\n";
                        tmpOutput += s;
                        tmpOutput += "\r\n";
                        s = s.Substring(s.IndexOf(' ')).Trim();
                        s = s.Substring(s.IndexOf(' ')).Trim();
                        s = s.Substring(s.IndexOf(' ')).Trim();
                        idx = s.IndexOf(' ');
                        testObjects[i] = s.Substring(0, idx);
                        if (count == 0)
                        {
                            totalObjects[count] = testObjects[i];
                            count++;
                        }
                        else
                        {
                            bool flag = true;
                            for (int j = 0; j < count; j++)
                            {
                                if (totalObjects[j] == testObjects[i])
                                {
                                    flag = false;
                                    break;
                                }
                                else
                                    flag = true;
                            }
                            if (flag == true)
                            {
                                totalObjects[count] = testObjects[i];
                                count++;
                            }
                        }
                        s = s.Substring(idx).Trim();
                        idx = s.IndexOf(' ');
                        trainObjects[i] = s.Substring(0, idx);
                    }
                }
                i++;
            }
            tmpOutput += "\r\n\r\n";
            tmpOutput += "*** STATISTICS ***\r\n#: Class in the Test File\r\n@: Class identified\r\n\r\n";
            for (int j = 1; j <= count; j++)
                tmpOutput += "#" + j + ". " + totalObjects[j - 1] + "\r\n";
            tmpOutput += "\r\n";
            for (int j = 1; j <= count; j++)
                tmpOutput += "@" + j + ". " + totalObjects[j - 1] + "\r\n";
            tmpOutput += "\r\n";
            tmpOutput += "   |    ";
            for (int j = 1; j <= count; j++)
                tmpOutput += "@" + j + "\t";
            tmpOutput += "% Correct\r\n";
            tmpOutput += "---+----";
            for (int j = 0; j < count; j++)
                tmpOutput += "--------";
            tmpOutput += "----------\r\n";
            for (int j = 1; j <= count; j++)
            {
                float object_count = 0;
                float total_objects = 0;
                tmpOutput += "#" + j + " |\t";
                for (int k = 0; k < count; k++)
                {
                    int tmp = 0;
                    for (int n = 0; n < testObjects.Length; n++)
                    {
                        if (totalObjects[j - 1] == testObjects[n])
                        {
                            if (totalObjects[k] == trainObjects[n])
                                tmp += 1;
                            if (testObjects[n] == trainObjects[n])
                            {
                                object_count += 1;
                                total_objects += 1;
                            }
                            else
                                total_objects += 1;
                        }
                    }
                    tmpOutput += tmp + "\t";
                }
                object_count = (object_count / total_objects) * 100;
                tmpOutput += object_count.ToString() + "%\r\n";
                //if (flag == true)
                //    tmpOutput += "100.00%\r\n";
                //else
                //    tmpOutput += "0.00%\r\n";
            }
            if (File.Exists(strTest))
                File.Delete(strTest);
            if (File.Exists(strTrain))
                File.Delete(strTrain);
            using (StreamWriter sw = File.CreateText(outputFile))
            {
                sw.Write(tmpOutput);
                sw.Close();
            }
            myClassificationResults.open(outputFile);
            myClassificationResults.Show();
        }
        private void classify(string strTest, string strTrain, string strResult)
        {
            ViewerForm viewer = MainForm.Viewers.SelectedViewer;
            int s_min = 0;
            int s_max = 1;
            Int32 norm = 0;
            Int32 dist = 0;
            Int32 errcode = 0;
            int r_softmax = 1;
            int r_minkowski = 1;
            int k;
            this.Cursor = Cursors.Default;
            if (rbSoftMaxScaling.Checked)
            {
                if (string.IsNullOrEmpty(txtR.Text))
                    r_softmax = 1;
                else
                    r_softmax = int.Parse(txtR.Text);
            }
            if (rbSoftMaxScaling.Checked == false)
                r_softmax = -1;
            if (rbMinMaxNormalization.Checked)
            {
                if (string.IsNullOrEmpty(txtSmin.Text))
                    s_min = 0;
                else
                    s_min = int.Parse(txtSmin.Text);
                if (string.IsNullOrEmpty(txtSmax.Text))
                    s_max = 0;
                else
                    s_max = int.Parse(txtSmax.Text);
            }
            if (rbMinMaxNormalization.Checked == false)
            {
                s_min = -1;
                s_max = -1;
            }
            r_minkowski = int.Parse(cboMinkowskiR.Text);
            if (r_minkowski <= 0)
            {
                this.Cursor = Cursors.Default;
                MessageBox.Show("The r value in Minkowski Distance should be a positive integer.");
                return;
            }
            k = int.Parse(cboKNearest.Text);
            if (rbMinMaxNormalization.Checked && (s_min >= s_max))
            {
                s_min = int.Parse(txtSmin.Text);
                s_max = int.Parse(txtSmax.Text);
                errcode = 3;
            }
            else if (rbSoftMaxScaling.Checked && (r_minkowski <= 0))
            {
                errcode = 12;
            }
            else if (rbLeaveOneOut.Checked && (cboTrainingSet.Text == "" || cboOutput.Text == ""))
            {
                MessageBox.Show("Feature or Output Filename missing");
                return;
            }
            else if (rbTrainingTestSet.Checked && (cboTrainingSet.Text == "" || cboTestSet.Text == "" || cboOutput.Text == ""))
            {
                MessageBox.Show("Training, Test or Output Filename missing");
                return;
            }
            else
            {
                // Normalization selection
                if (rbNoNormalization.Checked)
                    norm = 0;
                else if (rbRangeNormalize.Checked)
                    norm = 1;
                else if (rbUnitVectorNormalization.Checked)
                    norm = 2;
                else if (rbStdNormalDensity.Checked)
                    norm = 3;
                else if (rbMinMaxNormalization.Checked)
                    norm = 4;
                else if (rbSoftMaxScaling.Checked)
                    norm = 5;
                //Distance measure selection
                if (rbEuclidean.Checked)
                    dist = 0;
                else if (rbCityBlock.Checked)
                    dist = 1;
                else if (rbMaxValue.Checked)
                    dist = 2;
                else if (rbMinkowski.Checked)
                    dist = 3;
                else if (rbVectorInner.Checked)
                    dist = 4;
                else if (rbTanimoto.Checked)
                    dist = 5;
                //Pattern Classification Algorithm
                if ((rbMinkowski.Checked) && (r_minkowski == 1))
                {
                    MessageBox.Show("The r value '1' in Minkowski Distance means that you perform 'City Block or Absolute Value Metric'.");
                    dist = 1;
                }
                if ((rbMinkowski.Checked) && (r_minkowski == 2))
                {
                    MessageBox.Show("The r value '2' in Minkowski Distance means that you perform 'Euclidean Distance'.");
                    dist = 0;
                }
                if (rbNearestNeighbor.Checked)
                    errcode = CvipOp.Nearest_Neighbor(strTest, strTrain, strResult, norm, dist, s_min, s_max, r_softmax, r_minkowski);
                else if (rbKNearest.Checked)
                    errcode = CvipOp.K_Nearest_Neighbor(strTest, strTrain, strResult, norm, dist, k, s_min, s_max, r_softmax, r_minkowski);
                else if (rbNearestCentroid.Checked)
                    errcode = CvipOp.Nearest_Centroid(strTest, strTrain, strResult, norm, dist, s_min, s_max, r_softmax, r_minkowski);
            }
            if (errcode > 0)
            {
                switch (errcode)
                {
                case 1:
                    MessageBox.Show("The headers in the training and test files don't match");
                    break;
                case 2:
                    MessageBox.Show("K is greater than the number of entries in the training set or K<=0");
                    break;
                case 3:
                    MessageBox.Show("s_min is greater than or equal to s_max");
                    break;
                case 4:
                    MessageBox.Show("Data range is 0 and so the data can't be normalized");
                    break;
                case 5:
                    MessageBox.Show("Divisor is 0 in Tanimoto similarity measure ");
                    break;
                case 7:
                    MessageBox.Show("Can't open, read or create file");
                    break;
                case 9:
                    MessageBox.Show("Memory allocation error");
                    break;
                case 10:
                    MessageBox.Show("Every entry in training set should have a class name");
                    break;
                case 12:
                    MessageBox.Show("r in minkowski should be a positive integer");
                    break;
                case 13:
                    MessageBox.Show("There is more than one header in the training or test feature file");
                    break;
                }
                return;
            }
            if (!rbLeaveOneOut.Checked)
            {
                myClassificationResults.open(outputFile);
                myClassificationResults.Show();
            }
        }
        private void btnTrainOpen_Click(object sender, EventArgs e)
        {
            string trainset = MainForm.CVIPtoolsHOME;
            trainset = trainset + @"bin\feature\";

            openTrainingSet.Title = "Open Training Set";
            openTrainingSet.Filter = "All Files(*.*)|*.*";
            openTrainingSet.FilterIndex = 1;
            openTrainingSet.InitialDirectory = trainset;
            if (openTrainingSet.ShowDialog() != DialogResult.Cancel)
            {
                FileInfo loadFullFile = null;
                if (openTrainingSet.FileName.Contains(".xlsx"))
                {
                    string textName = openTrainingSet.FileName;
                    textName = textName.Replace(".xlsx", ".txt");
                    ExceltoText(openTrainingSet.FileName, textName);
                    loadFullFile = new FileInfo(textName);
                }
                else
                    loadFullFile = new FileInfo(openTrainingSet.FileName);
                if (File.Exists(trainset + loadFullFile.Name) == false)
                {
                    File.Copy(loadFullFile.FullName, trainset + loadFullFile.Name);
                }
                cboTrainingSet.Items.Add(loadFullFile.Name);
                trainSetFile = openTrainingSet.FileName;
                cboTrainingSet.Text = loadFullFile.Name;
            }
            myFeatureFile = FeatureFile.Open(trainSetFile);
            if (File.Exists(trainSetFile))
                myFeatureResults.Show(myFeatureFile);
        }
        private void btnTestOpen_Click(object sender, EventArgs e)
        {
            string testsetfiles = MainForm.CVIPtoolsHOME;
            testsetfiles = testsetfiles + @"bin\feature\";
            openTestSet.Title = "Open Test Set";
            openTestSet.Filter = "All Files(*.*)|*.*";
            openTestSet.FilterIndex = 1;
            openTestSet.InitialDirectory = testsetfiles;
            if (openTestSet.ShowDialog() != DialogResult.Cancel)
            {
                FileInfo loadFullFile1 = null;
                if (openTestSet.FileName.Contains(".xlsx"))
                {
                    string textName = openTestSet.FileName;
                    textName = textName.Replace(".xlsx", ".txt");
                    ExceltoText(openTestSet.FileName, textName);
                    loadFullFile1 = new FileInfo(textName);
                }
                else
                    loadFullFile1 = new FileInfo(openTestSet.FileName);
                if (File.Exists(testsetfiles + loadFullFile1.Name) == false)
                {
                    File.Copy(loadFullFile1.FullName, testsetfiles + loadFullFile1.Name);
                }
                cboTestSet.Items.Add(loadFullFile1.Name);
                testSetFile = openTestSet.FileName;
                cboTestSet.Text = loadFullFile1.Name;
            }
            myFeatureFile = FeatureFile.Open(testSetFile);
            if (File.Exists(testSetFile))
                myFeatureResults.Show(myFeatureFile);
        }
        private void btnSaveas_Click(object sender, EventArgs e)
        {
            string featureFileHome = MainForm.CVIPtoolsHOME;
            featureFileHome = featureFileHome + @"bin\feature\";
            saveOutputFile.Title = "Save Output File";
            saveOutputFile.Filter = "All Files(*.*)|*.*" + "Text Documents (*.txt|*.txt|";
            saveOutputFile.FilterIndex = 2;
            saveOutputFile.InitialDirectory = featureFileHome;
            if (cboOutput.Text != "")
                saveOutputFile.FileName = cboOutput.Text;
            if (saveOutputFile.ShowDialog() != DialogResult.Cancel)
            {
                if (!saveOutputFile.FileName.Contains(".txt"))
                    saveOutputFile.FileName = saveOutputFile.FileName + ".txt";
                FileInfo loadFullFile2 = new FileInfo(saveOutputFile.FileName);
                cboOutput.Items.Add(loadFullFile2.Name);
                outputFile = saveOutputFile.FileName;
                cboOutput.Text = loadFullFile2.Name;
            }
            if (File.Exists(outputFile))
            {
                myClassificationResults.open(outputFile);
                myClassificationResults.Show();
            }
        }
        private void cboTrainingSet_SelectedIndexChanged(object sender, EventArgs e)
        {
            trainSetFile = MainForm.CVIPtoolsHOME;
            trainSetFile = trainSetFile + @"bin\feature\";
            trainSetFile = trainSetFile + cboTrainingSet.Text;
            if (trainSetFile.Contains(".xlsx"))
            {
                trainSetFile = trainSetFile.Replace(".xlsx", ".txt");
            }
            myFeatureFile = FeatureFile.Open(trainSetFile);
            myFeatureResults.Show(myFeatureFile);
        }
        private void cboTestSet_SelectedIndexChanged(object sender, EventArgs e)
        {
            testSetFile = MainForm.CVIPtoolsHOME;
            testSetFile = testSetFile + @"bin\feature\";
            testSetFile = testSetFile + cboTestSet.Text;
            if (testSetFile.Contains(".xlsx"))
            {
                testSetFile = testSetFile.Replace(".xlsx", ".txt");
            }
            myFeatureFile = FeatureFile.Open(testSetFile);
            myFeatureResults.Show(myFeatureFile);
        }
        private void cboOutput_SelectedIndexChanged(object sender, EventArgs e)
        {
            outputFile = MainForm.CVIPtoolsHOME;
            outputFile = outputFile + @"bin\feature\";
            outputFile = outputFile + cboOutput.Text;
            if (File.Exists(outputFile))
            {
                myClassificationResults.open(outputFile);
            }
            else
                myClassificationResults.close();
        }
        private void btnHelp_Click(object sender, EventArgs e)
        {
            MainForm.ShowHelp();
        }
        private void btnCancel_Click(object sender, EventArgs e)
        {
            MainForm.AnalysisForm.Close();
        }
        private void btnReset_Click(object sender, EventArgs e)
        {
            lbSmin.Visible = false;
            lbSmax.Visible = false;
            txtSmax.Visible = false;
            txtSmin.Visible = false;
            lbR.Visible = false;
            txtR.Visible = false;
            cboMinkowskiR.Visible = false;
            lbMinr.Visible = false;
            cboKNearest.Visible = false;
            lbK.Visible = false;
            cboTrainingSet.Text = "";
            cboTestSet.Text = "";
            cboOutput.Text = "";
            rbNoNormalization.Checked = true;
            rbEuclidean.Checked = true;
            rbNearestNeighbor.Checked = true;
            rbTrainingTestSet.Checked = true;
            string myfso = MainForm.CVIPtoolsHOME;
            myfso = myfso + @"bin\feature\";
            string[] nameList;
            nameList = Directory.GetFiles(myfso);
            string[] fileName = new string[nameList.Length];
            for (int i = 0; i < nameList.Length; i++)
            {
                FileInfo listFileInfo = new FileInfo(nameList[i]);
                fileName[i] = listFileInfo.Name;
            }
            cboTrainingSet.Items.Clear();
            cboTrainingSet.Items.AddRange(fileName);
            cboTestSet.Items.Clear();
            cboTestSet.Items.AddRange(fileName);
            cboOutput.Items.Clear();
            cboOutput.Items.AddRange(fileName);
        }
        private void rbMinMaxNormalization_CheckedChanged(object sender, EventArgs e)
        {
            this.lbSmin.Visible = this.rbMinMaxNormalization.Checked;
            this.lbSmax.Visible = this.rbMinMaxNormalization.Checked;
            this.txtSmax.Visible = this.rbMinMaxNormalization.Checked;
            this.txtSmin.Visible = this.rbMinMaxNormalization.Checked;
        }
        private void rbSoftMaxScaling_CheckedChanged(object sender, EventArgs e)
        {
            this.lbR.Visible = this.rbSoftMaxScaling.Checked;
            this.txtR.Visible = this.rbSoftMaxScaling.Checked;
        }
        private void rbMinkowski_CheckedChanged(object sender, EventArgs e)
        {
            this.cboMinkowskiR.Visible = this.rbMinkowski.Checked;
            this.lbMinr.Visible = this.rbMinkowski.Checked;
        }
        private void rbKNearest_CheckedChanged(object sender, EventArgs e)
        {
            this.cboKNearest.Visible = this.rbKNearest.Checked;
            this.lbK.Visible = this.rbKNearest.Checked;
        }
        private void cboOutput_TextChanged(object sender, EventArgs e)
        {
            if (cboOutput.Text != "")
            {
                outputFile = MainForm.CVIPtoolsHOME;
                outputFile = outputFile + @"bin\feature\";
                saveOutputFile.InitialDirectory = outputFile;
                outputFile = outputFile + cboOutput.Text;
                saveOutputFile.FileName = cboOutput.Text;
                if (!saveOutputFile.FileName.Contains(".txt"))
                {
                    saveOutputFile.FileName = saveOutputFile.FileName + ".txt";
                    outputFile += ".txt";
                }
            }
        }
        private void rbTrainingTestSet_CheckedChanged(object sender, EventArgs e)
        {
            lbTestSet.Visible = true;
            cboTestSet.Visible = true;
            lbTrainingSet.Text = "Training Set";
            btnTestOpen.Visible = true;
            if (this.Height < 669)
            {
                btnTrainOpen.Location = new Point(528, 12);
                btnSaveas.Location = new Point(528, 71);
                lbTrainingSet.Location = new Point(25, 20);
                cboTrainingSet.Location = new Point(96, 16);
                lbOutputFile.Location = new Point(25, 77);
                cboOutput.Location = new Point(96, 73);
            }
            else if (this.Height == 669)
            {
                btnTrainOpen.Location = new Point(704, 15);
                btnSaveas.Location = new Point(704, 87);
                lbTrainingSet.Location = new Point(15, 20);
                lbTestSet.Location = new Point(15,58);
                cboTrainingSet.Location = new Point(128, 16);
                lbOutputFile.Location = new Point(15, 87);
                cboOutput.Location = new Point(128, 87);
            }
        }
        private void rbLeaveOneOut_CheckedChanged(object sender, EventArgs e)
        {
            if (rbLeaveOneOut.Checked)
            {
                lbTestSet.Visible = false;
                cboTestSet.Visible = false;
                lbTrainingSet.Text = "Feature File";
                btnTestOpen.Visible = false;
                if (this.Height < 669)
                {
                    btnTrainOpen.Location = new Point(528, 22);
                    btnSaveas.Location = new Point(528, 61);
                    lbTrainingSet.Location = new Point(25, 30);
                    cboTrainingSet.Location = new Point(96, 26);
                    lbOutputFile.Location = new Point(25, 67);
                    cboOutput.Location = new Point(96, 63);
                }
                else if (this.Height == 669)
                {
                    btnTrainOpen.Location = new Point(700, 22);
                    btnSaveas.Location = new Point(700, 61);
                    lbTrainingSet.Location = new Point(25, 30);
                    cboTrainingSet.Location = new Point(128, 26);
                    lbOutputFile.Location = new Point(25, 67);
                    cboOutput.Location = new Point(128, 63);
                }
            }
        }
        private void cboTrainingSet_TextChanged(object sender, EventArgs e)
        {
            if (cboTrainingSet.Text != "")
            {
                trainSetFile = MainForm.CVIPtoolsHOME;
                trainSetFile = trainSetFile + @"bin\feature\";
                trainSetFile = trainSetFile + cboTrainingSet.Text;
                if (trainSetFile.Contains(".xlsx"))
                {
                    string textName = trainSetFile;
                    textName = textName.Replace(".xlsx", ".txt");
                    ExceltoText(trainSetFile, textName);
                    trainSetFile = textName;
                }
                if (!trainSetFile.Contains(".txt"))
                    trainSetFile += ".txt";
            }
        }
        private void cboTestSet_TextChanged(object sender, EventArgs e)
        {
            if (cboTestSet.Text != "")
            {
                testSetFile = MainForm.CVIPtoolsHOME;
                testSetFile = testSetFile + @"bin\feature\";
                testSetFile = testSetFile + cboTestSet.Text;
                if (testSetFile.Contains(".xlsx"))
                {
                    string textName = testSetFile;
                    textName = textName.Replace(".xlsx", ".txt");
                    ExceltoText(testSetFile, textName);
                    testSetFile = textName;
                }
                if (!testSetFile.Contains(".txt"))
                    testSetFile += ".txt";
            }
        }

        private void ExceltoText(string excelSheet, string textSheet)
        {
            int colCount, rowCount, num;
            string itemPartNumber, txtTitle;
            if (File.Exists(textSheet))
            {
                string title = "Save as";
                string msg = "File " + textSheet + " already exists.\n";
                msg += "Do you want to replace it?";
                MessageBoxButtons buttons = MessageBoxButtons.YesNo;
                MessageBoxIcon icon = MessageBoxIcon.Warning;
                if (MessageBox.Show(msg, title, buttons, icon) == DialogResult.No)
                    return;
                File.Delete(textSheet);
            }
            Excel.ApplicationClass app = new Microsoft.Office.Interop.Excel.ApplicationClass();
            Excel.Workbook book = app.Workbooks.Open(excelSheet, 0, true, 5, "", "", true, Microsoft.Office.Interop.Excel.XlPlatform.xlWindows, "\t", false, false, 0, true, 1, 0); ;
            Excel.Worksheet sheet = (Excel.Worksheet)book.Worksheets.get_Item(1);
            try
            {
                using (StreamWriter sr = File.CreateText(textSheet))
                {

                    //Create Header
                    itemPartNumber = Convert.ToString(((Excel.Range)sheet.Cells[2, 3]).Value2);
                    sr.WriteLine("CVIPtools feature file for image with " + itemPartNumber + " band");
                    colCount = 2;
                    num = 1;
                    while (!string.IsNullOrEmpty(itemPartNumber = Convert.ToString(((Excel.Range)sheet.Cells[1, colCount]).Value2)))
                    {
                        if (itemPartNumber != "ClassName" && itemPartNumber != "Bands")
                        {
                            sr.Write(num.ToString());
                            sr.Write(". ");
                            txtTitle = determineName(itemPartNumber, ref colCount);
                            sr.Write(txtTitle);
                            sr.WriteLine();
                            num++;
                        }
                        colCount++;
                    }
                    sr.WriteLine("*** END OF HEADER; CLASS (optional) SHOWN AT THE END OF DATA ***");
                    sr.WriteLine();

                    //Write Data
                    rowCount = 2;
                    while (!string.IsNullOrEmpty(itemPartNumber = Convert.ToString(((Excel.Range)sheet.Cells[rowCount, 1]).Value2)))
                    {
                        for (int i = 2; i < colCount + 1; i++)
                        {
                            if (i != 3)
                            {
                                itemPartNumber = Convert.ToString(((Excel.Range)sheet.Cells[rowCount, i]).Value2);
                                sr.Write(itemPartNumber);
                                sr.Write(" ");
                            }
                        }
                        sr.WriteLine();
                        sr.WriteLine();
                        rowCount++;
                    }

                }
                MessageBox.Show("Features Successfully saved to " + textSheet, "Information", MessageBoxButtons.OK, MessageBoxIcon.Information);
                app.Quit();
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private string determineName(string excelTitle, ref int colCount)
        {
            string textTitle, tempTitle;
            int pFrom, pTo;
            //Check Projection
            if (excelTitle.Contains("Projection"))
                tempTitle = "Projection";
            else if (excelTitle.Contains("Average"))
                tempTitle = "Texture";
            else if (excelTitle.Substring(excelTitle.Length - 1, 1) == "R")
                tempTitle = excelTitle.Replace("_R", "_Band0");
            else if (excelTitle.Substring(excelTitle.Length - 1, 1) == "G")
                tempTitle = excelTitle.Replace("_G", "_Band1");
            else if (excelTitle.Substring(excelTitle.Length - 1, 1) == "B")
                tempTitle = excelTitle.Replace("_B", "_Band2");
            else
                tempTitle = excelTitle;

            switch (tempTitle)
            {
                case "Name":
                    textTitle = "Image Name";
                    break;
                case "Row":
                    textTitle = "Object's Row Coordinate";
                    break;
                case "Column":
                    textTitle = "Object's Column Coordinate";
                    break;
                case "Centroid_Row":
                    textTitle = "Centroid (Row, Column)";
                    colCount++;
                    break;
                case "Orientation":
                    textTitle = "Orientation (Axis of Least Second Moment)";
                    break;
                case "Projection":
                    pFrom = excelTitle.IndexOf("(") + "(".Length;
                    pTo = excelTitle.LastIndexOf(",");
                    String height = excelTitle.Substring(pFrom, pTo - pFrom);
                    pFrom = excelTitle.IndexOf(",") + ",".Length;
                    pTo = excelTitle.LastIndexOf(")");
                    String width = excelTitle.Substring(pFrom, pTo - pFrom);
                    textTitle = "Projection (Height: " + height + "  Width:" + width + ")";
                    colCount = colCount + int.Parse(height) + int.Parse(width) - 1;
                    break;
                case "Texture":
                    pFrom = excelTitle.IndexOf("(") + "(".Length;
                    pTo = excelTitle.LastIndexOf(",");
                    String distance = excelTitle.Substring(pFrom, pTo - pFrom);
                    pFrom = excelTitle.IndexOf(",") + ",".Length;
                    pTo = excelTitle.LastIndexOf(")");
                    String includeZero = excelTitle.Substring(pFrom, pTo - pFrom);
                    textTitle = excelTitle.Substring(0, excelTitle.IndexOf("(")) + "(Texture Distance: " + distance + "  IncludeZeroPairs: " + includeZero + ")";
                    break;
                default:
                    textTitle = tempTitle;
                    break;
            }
            return textTitle;
        }
    }
}
