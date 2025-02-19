/***************************************************************************
* =========================================================================
*
*			 CVIP_ATAT - Dr. Scott Umbaugh SIUE
* 
* =========================================================================
*
*             File Name: CVIPATATForm.cs 
*           Description: GUI for algorithm test and analysis.
*   Initial Coding Date: June 6, 2006
*Last Modification Made: June 18, 2021
*  Programming Language: Visual Studio C#.NET 2008, 2017, 2019 
*             Credit(s): Wenjun(Evan) Bian, Pelin Guvenc, Charles Stacey
*                        Southern Illinois University at Edwardsville
*
*		  Copyright (c): 2010-2021 SIUE - Scott Umbaugh
****************************************************************************/

using System;
using System.Drawing;
using System.Windows.Forms;
using System.IO;
using SERVERLib;
using CVIP_ATAT.Files;
using System.Diagnostics;
using System.Threading;

namespace CVIP_ATAT
{
    public partial class CVIPATATForm : Form
    {
        public CVIPTools CVIPTool = new CVIPTools();
        MDIMainForm MDIMainFormRef;
        Images algorithmImage;
        Processes algorithmProcess;
        Test algorithmTest;
        imageView viewImage, idealImage;
        ManualResetEvent threadCTL;

        public int btPauseClickSign = 0;
        public int saveDateToListViewSignTest = 0;
        public int saveDateToListViewSignCompare = 0;

        public int btRunStopClickSign = 0;
        public int btCompareStopClickSign = 0;

        public string CVIP_projectPath;

        public string imageNamePath;
        public string idealNamePath;


        public CVIPATATForm(MDIMainForm reference, string projectPath) //Get MDIMainForm's reference
        {
            InitializeComponent();
            MDIMainFormRef = reference;
            CVIP_projectPath = projectPath;
            threadCTL = new ManualResetEvent(true);
        }

        private void CVIPATATForm_Load(object sender, EventArgs e)
        {
            MDIMainFormRef.runTestFinishSign = 0;
            algorithmImage = new Images(this);
            algorithmProcess = new Processes(this, MDIMainFormRef);
            //algorithmTest = new Test(this, MDIMainFormRef, algorithmProcess, CVIPTool, threadCTL);
            this.Text = CVIP_projectPath;
        }

        private void CVIPATATForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (MDIMainFormRef.mnuAskBeforeExit.Enabled == true)
            {
                DialogResult MessageBoxReturn = 0;

                MessageBoxReturn = MessageBox.Show("Do you want to save this Project?", "CVIPATAT Project Confirm Exit",
                    MessageBoxButtons.YesNoCancel, MessageBoxIcon.Question);

                switch (MessageBoxReturn)
                {
                    case DialogResult.No:  //do not save project but close
                        //close CVIPATAT Project and testRunThread if it is on running.
                        e.Cancel = false;
                        MDIMainFormRef.CVIPATATFormCloseSign = 0;
                        if (btTestRun.Enabled == false) //if we start a thread, abort it
                            algorithmTest.testRunThread.Abort();

                        this.Dispose();

                        MDIMainFormRef.mnuSaveProject.Enabled = false;
                        MDIMainFormRef.mnuCloseProject.Enabled = false;
                        MDIMainFormRef.mnuOpenProject.Enabled = true;
                        MDIMainFormRef.mnuNewProject.Enabled = true;

                        MDIMainFormRef.CVIPATA_Open_Sign = 0;
                        MDIMainFormRef.CVIPATA_New_Sign = 0;
                        MDIMainFormRef.newProjectPath = "0";
                        break;
                    case DialogResult.Yes:  //save project and close

                        MDIMainFormRef.savenow();

                        //close CVIPATTA Project and testRunThread if it is on running
                        e.Cancel = false;
                        MDIMainFormRef.CVIPATATFormCloseSign = 0;
                        if (btTestRun.Enabled == false) //if we start a thread, abort it
                            algorithmTest.testRunThread.Abort();

                        this.Dispose();

                        MDIMainFormRef.mnuSaveProject.Enabled = false;
                        MDIMainFormRef.mnuCloseProject.Enabled = false;
                        MDIMainFormRef.mnuOpenProject.Enabled = true;
                        MDIMainFormRef.mnuNewProject.Enabled = true;

                        MDIMainFormRef.CVIPATA_Open_Sign = 0;
                        MDIMainFormRef.CVIPATA_New_Sign = 0;
                        MDIMainFormRef.newProjectPath = "0";

                        break;
                    case DialogResult.Cancel:
                        //donot close CVIPATTAForm.
                        e.Cancel = true;
                        MDIMainFormRef.CVIPATATFormCloseSign = 1;
                        MDIMainFormRef.mnuSaveProject.Enabled = true;
                        MDIMainFormRef.mnuCloseProject.Enabled = true;
                        MDIMainFormRef.mnuOpenProject.Enabled = false;
                        MDIMainFormRef.mnuNewProject.Enabled = false;
                        break;
                    default:
                        //donot close CVIPATTAForm.
                        e.Cancel = true;
                        MDIMainFormRef.CVIPATATFormCloseSign = 1;
                        MDIMainFormRef.mnuSaveProject.Enabled = true;
                        MDIMainFormRef.mnuCloseProject.Enabled = true;
                        MDIMainFormRef.mnuOpenProject.Enabled = false;
                        MDIMainFormRef.mnuNewProject.Enabled = false;
                        break;
                }
            }
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            if (btTestRun.Enabled == false && btPauseClickSign == 0)  //it means Run Button is press down
            {
                float percent;
                if (algorithmTest.testComp == 0)
                {
                    tbFOption.Text = algorithmTest.finishedOptionCount.ToString();
                    TestTypeLabel.Text = "Testing Algorithms";
                }
                else
                {
                    tbFOption.Text = (Convert.ToInt32(tbTotalOptionsImage.Text) * Convert.ToInt32(tbImageCount.Text)).ToString();
                    TestTypeLabel.Text = "Running Comparisons";
                }
                if (algorithmTest.typeOfTest == 0) //Full Test
                {
                    pBarTest.Maximum = (Convert.ToInt32(tbTotalOptionsImage.Text) * Convert.ToInt32(tbImageCount.Text)) * 2;
                    pBarTest.Minimum = 0;
                    pBarTest.Value = algorithmTest.finishedOptionCount;
                    percent = 100 * algorithmTest.finishedOptionCount / pBarTest.Maximum;
                }
                else if (algorithmTest.typeOfTest == 1) //Only Test
                {
                    pBarTest.Maximum = (Convert.ToInt32(tbTotalOptionsImage.Text) * Convert.ToInt32(tbImageCount.Text));
                    pBarTest.Minimum = 0;
                    pBarTest.Value = algorithmTest.finishedOptionCount;
                    percent = 100 * algorithmTest.finishedOptionCount / pBarTest.Maximum;
                }
                else //Only Compare
                {
                    pBarTest.Maximum = 200;
                    pBarTest.Minimum = 100;
                    pBarTest.Value = algorithmTest.finishedOptionCount;
                    percent = algorithmTest.finishedOptionCount - 100;
                }
                labelShowProgress.Text = "Progress: " + percent.ToString() + "%";
            }

            if (MDIMainFormRef.runTestFinishSign == 1) //If experiment is finished
            {
                if (btRunStopClickSign == 0) //Thread finished without stop button
                {
                    if (saveDateToListViewSignTest == 0 && algorithmTest.typeOfTest != 2 && algorithmTest.ranTest == 0)
                    {
                        algorithmTest.saveDateToListViewTest();
                        saveDateToListViewSignTest = 1;
                    }
                }
                else
                { }
                TestTypeLabel.Text = "No Test Running";
                btTestRun.Enabled = true;
                btRunPause.Enabled = false;
                btRunPause.Text = "Pause";
                btRunStop.Enabled = false;
                MDIMainFormRef.runTestFinishSign = 0;
            }
        }

        private void btAddImage_Click(object sender, EventArgs e)
        {
            algorithmImage.image_btAddImage_Click();
        }

        private void btDeleteAllImage_Click(object sender, EventArgs e)
        {
            algorithmImage.image_btDeleteAllImage_Click();
        }

        private void cbBoxSeclectProcess_SelectedIndexChanged(object sender, EventArgs e)
        {
            algorithmProcess.process_cbBoxSeclectProcess_SelectedIndexChanged();
        }

        private void cbBoxSeclectProcess_KeyUp(object sender, KeyEventArgs e)
        {
            cbBoxSeclectProcess.Text = "Select Process Here";
            MessageBox.Show("Please select the process from the list only", "Select a process",
                       MessageBoxButtons.OK, MessageBoxIcon.Warning);
        }

        private void cbSelectStage_KeyUp(object sender, KeyEventArgs e)
        {
            cbBoxSelectStage.Text = "Select Stage Here";
            MessageBox.Show("Please select the stage from the list only", "Select a stage",
                       MessageBoxButtons.OK, MessageBoxIcon.Warning);
        }

        private void btAddProcess_Click(object sender, EventArgs e)
        {
            algorithmProcess.process_btAddProcess_Click();
        }

        private void btDeleteAllProcesses_Click(object sender, EventArgs e)
        {
            algorithmProcess.Process_btDeleteAllProcesses_Click();
            cbBoxSelectStage.Text = "1";
        }

        private void btUp_Click(object sender, EventArgs e)
        {
            algorithmProcess.process_btUp_Click();
        }

        private void btDown_Click(object sender, EventArgs e)
        {
            algorithmProcess.process_btDown_Click();
        }

        private void labelHelp_MouseLeave(object sender, EventArgs e)
        {
            toolTiplvTestResult.Active = false;
        }

        private void labelHelp_Click(object sender, EventArgs e)
        {
            toolTiplvTestResult.Active = true;
            toolTiplvTestResult.SetToolTip(labelHelp, "We use x1.x2.x3 to represent stage and option." +
                "x1 means first stage, x2 means second stage. x1=1 means the first option of stage 1," +
                "x3=2 means the second option of stage 3");
        }

        private void cbBoxSelectStage_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (lvProcess.Items.Count == 0)
            {
                if (Convert.ToInt32(cbBoxSelectStage.Text) > 1)
                {
                    MessageBox.Show("Please select stage '1'. This is the first process.", "Please re-select the stage",
                                           MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    cbBoxSelectStage.Text = "1";
                }
            }
            else
            {
                if (Convert.ToInt32(cbBoxSelectStage.Text) - Convert.ToInt32(lvProcess.Items[lvProcess.Items.Count - 1].SubItems[0].Text) > 1)
                {
                    MessageBox.Show("You can select several process for the same stage; however, you can not miss a stage. For example, you can not "
                    + "select stage that is larger than '5', if the largest stage in the listview is '3'. Please check the stage and fix the problem before run the test.", "Please re-select the stage",
                     MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    cbBoxSelectStage.Text = "1";
                }
            }
        }

        private void tabTest_Enter(object sender, EventArgs e)
        {
            tbTOption.Text = Convert.ToString(Convert.ToInt32(tbTotalOptionsImage.Text) * Convert.ToInt32(tbImageCount.Text));
        }

        private void tabProcesses_Enter(object sender, EventArgs e)
        {
            tbTOption.Text = Convert.ToString(Convert.ToInt32(tbTotalOptionsImage.Text) * Convert.ToInt32(tbImageCount.Text));
        }

        private void btDeleteCheckedTest_Click(object sender, EventArgs e)
        {
            int checkedTestCount = lvTestResult.CheckedItems.Count;
            if (checkedTestCount == 0)
                MessageBox.Show("No Test Result is checked now.", "Delete check items",MessageBoxButtons.OK, MessageBoxIcon.Question);
            else
            {
                for (int i = checkedTestCount - 1; i >= 0; i--)
                    lvTestResult.Items.Remove(lvTestResult.CheckedItems[i]);
            }
        }

        private void btDeleteAllTest_Click(object sender, EventArgs e)
        {
            if (lvTestResult.Items.Count == 0)
                MessageBox.Show("No Test Result can be deleted now.", "Delete all items",MessageBoxButtons.OK, MessageBoxIcon.Question);
            else
            {
                if (MessageBox.Show("Do you really want to delete all the Test Result in ListView?",
                        "Delete all items", MessageBoxButtons.OKCancel, MessageBoxIcon.Exclamation)
                         == DialogResult.OK)
                {
                    lvTestResult.Items.Clear();
                }
            }
        }

        private void btTestRun_Click(object sender, EventArgs e)
        {
            threadCTL.Set();
            algorithmTest = new Test(this, MDIMainFormRef, algorithmProcess, CVIPTool, threadCTL);
            algorithmTest.test_btTestRun_Click();
            btRunStopClickSign = 0;
        }

        private void btRunPause_Click_1(object sender, EventArgs e)
        {
            btTestRun.Enabled = false;
            btRunStop.Enabled = true;
            if (btPauseClickSign == 0)
            {
                //algorithmTest.testRunThread.Suspend();
                threadCTL.Reset();
                btRunPause.Text = "Resume";
                btPauseClickSign = 1;
            }
            else
            {
                //algorithmTest.testRunThread.Resume();
                threadCTL.Set();
                btRunPause.Text = "Pause";
                btPauseClickSign = 0;
            }
        }

        public void btRunStop_Click_1(object sender, EventArgs e)
        {
            //if (btPauseClickSign == 1)
            //    threadCTL.Set();
            threadCTL.Reset();

            btPauseClickSign = 0;

            algorithmTest.testRunThread.Abort();

            btRunStopClickSign = 1;
            MDIMainFormRef.runTestFinishSign = 1;

            if(algorithmTest.testCon != null)
                algorithmTest.testCon.Close();//close database when we stop the thread       
        }

        private void btDeleteCheckedProcess_Click_1(object sender, EventArgs e)
        {
            algorithmProcess.process_btDeleteCheckedProcess_Click();
            cbBoxSelectStage.Text = "1";
        }

        private void btDelAllIdealImage_Click(object sender, EventArgs e)
        {
            algorithmImage.btDelAllIdealImage_Click();
        }

        private void btDelSelectedIdImage_Click(object sender, EventArgs e)
        {
            algorithmImage.btDelSelectedIdImage_Click();
        }

        private void btDeleteSelectedImage_Click(object sender, EventArgs e)
        {
            algorithmImage.image_btDeleteSelectedImage_Click();
        }

        private void btAddIdealImage_Click(object sender, EventArgs e)
        {
            algorithmImage.image_btAddIdealImage_Click();
        }

        //Works for the Results link, actual object is called resultLink
        private void linkLabel1_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
        {
            Process.Start("explorer.exe", CVIP_projectPath);
        }

        private void rb_FullTest_CheckedChanged(object sender, EventArgs e)
        {
            if (rb_FullTest.Checked == true)
            {
                //Uncheck other test options
                rb_Compare.Checked = false;
                rb_Test.Checked = false;

                //Remove file options for compare
                tb_TestDir.Visible = tb_IdealDir.Visible = tbAlg.Visible = false;
                bt_TestDir.Visible = bt_IdealDir.Visible = bt_Alg.Visible = false;
                lb_TestDir.Visible = lb_IdealDir.Visible = lblAlg.Visible = false;
                btnAddCTable.Visible = false;

                //Activate compare options
                cb_RMS.Enabled = cb_SNR.Enabled = cb_SubtractEnergy.Enabled = true;
                cb_DICE.Enabled = cb_Jaccard.Enabled = cb_Over.Enabled = cb_XOR.Enabled = true;
                cb_XOR.Enabled = cb_Average.Enabled = cb_StdDev.Enabled = cbSelectAll.Enabled = true;
                cb_CheckedChanged(sender, e);
            }
        }

        private void rb_Test_CheckedChanged(object sender, EventArgs e)
        {
            if (rb_Test.Checked == true)
            {
                //Uncheck other test options
                rb_Compare.Checked = false;
                rb_FullTest.Checked = false;

                //Remove file options for compare
                tb_TestDir.Visible = tb_IdealDir.Visible = tbAlg.Visible = false;
                bt_TestDir.Visible = bt_IdealDir.Visible = bt_Alg.Visible = false;
                lb_TestDir.Visible = lb_IdealDir.Visible = lblAlg.Visible = false;
                btnAddCTable.Visible = false;

                //Grey out compare parameters
                cb_RMS.Enabled = cb_SNR.Enabled = cb_SubtractEnergy.Enabled = false;
                cb_DICE.Enabled = cb_Jaccard.Enabled = cb_Over.Enabled = cb_XOR.Enabled = false;
                tb_RMSR.Enabled = tb_RMSG.Enabled = tb_RMSB.Enabled = false;
                tb_RMSR.BackColor = tb_RMSG.BackColor = tb_RMSB.BackColor = Color.DarkGray;
                tb_SNRR.Enabled = tb_SNRG.Enabled = tb_SNRB.Enabled = false;
                tb_SNRR.BackColor = tb_SNRG.BackColor = tb_SNRB.BackColor = Color.DarkGray;
                tb_SUBR.Enabled = tb_SUBG.Enabled = tb_SUBB.Enabled = false;
                tb_SUBR.BackColor = tb_SUBG.BackColor = tb_SUBB.BackColor = Color.DarkGray;
                tb_DICER.Enabled = tb_DICEG.Enabled = tb_DICEB.Enabled = false;
                tb_DICER.BackColor = tb_DICEG.BackColor = tb_DICEB.BackColor = Color.DarkGray;
                tb_JaccR.Enabled = tb_JaccG.Enabled = tb_JaccB.Enabled = false;
                tb_JaccR.BackColor = tb_JaccG.BackColor = tb_JaccB.BackColor = Color.DarkGray;
                tb_OverR.Enabled = tb_OverG.Enabled = tb_OverB.Enabled = false;
                tb_OverR.BackColor = tb_OverG.BackColor = tb_OverB.BackColor = Color.DarkGray;
                tb_XORR.Enabled = tb_XORG.Enabled = tb_XORB.Enabled = false;
                tb_XORR.BackColor = tb_XORG.BackColor = tb_XORB.BackColor = Color.DarkGray;
                tb_Thresh.Enabled = false;
                tb_Thresh.BackColor = Color.DarkGray;
                cb_Average.Enabled = cb_StdDev.Enabled = cbSelectAll.Enabled = false;
            }
        }

        private void rb_Compare_CheckedChanged(object sender, EventArgs e)
        {
            if (rb_Compare.Checked == true)
            {
                rb_FullTest.Checked = false;
                rb_Test.Checked = false;

                //Remove file options for compare
                tb_TestDir.Visible = tb_IdealDir.Visible = tbAlg.Visible = true;
                bt_TestDir.Visible = bt_IdealDir.Visible = bt_Alg.Visible = true;
                lb_TestDir.Visible = lb_IdealDir.Visible = lblAlg.Visible = true;
                btnAddCTable.Visible = true;

                //Activate compare options
                cb_RMS.Enabled = cb_SNR.Enabled = cb_SubtractEnergy.Enabled = true;
                cb_DICE.Enabled = cb_Jaccard.Enabled = cb_Over.Enabled = cb_XOR.Enabled = true;
                cb_XOR.Enabled = cb_Average.Enabled = cb_StdDev.Enabled = cbSelectAll.Enabled = true;
                cb_CheckedChanged(sender, e);
            }
        }

        private void bt_TestDir_Click(object sender, EventArgs e)
        {
            if (folderBrowser.ShowDialog() == DialogResult.OK)
            {
                tb_TestDir.Text = folderBrowser.SelectedPath;
            }
        }

        private void bt_IdealDir_Click(object sender, EventArgs e)
        {
            if (folderBrowser.ShowDialog() == DialogResult.OK)
            {
                tb_IdealDir.Text = folderBrowser.SelectedPath;
            }
        }

        private void updatelistViewWithCompareMain()
        {
            ListViewItem objListView;
            FileInfo myFile;
            string justFile, fileName, stage, line = "";
            string[] testFiles = null, idealFiles = null;
            string[] extensions = { ".vip", ".jpeg", ".jpg", ".gif", ".bmp", ".pbm", ".pgm", ".ppm", ".tif" };
            bool imageFile, idealExists;
            int i, e, t, error = 0, split;
            //Get Test Directory
            if (Directory.Exists(tb_TestDir.Text))
                testFiles = Directory.GetFiles(tb_TestDir.Text, "*", SearchOption.AllDirectories);
            else
                error = 1;

            //Get Ideal Directory
            if (Directory.Exists(tb_IdealDir.Text))
                idealFiles = Directory.GetFiles(tb_IdealDir.Text, "*", SearchOption.AllDirectories);
            else
                error = 2;

            if (error == 0)
            {
                deleteListView();
                for (t = 0; t < testFiles.Length; t++)
                {
                    //Check Extension
                    imageFile = false;
                    for (e = 0; e < extensions.Length; e++)
                    {
                        if (Path.GetExtension(testFiles[t]) == extensions[e])
                        {
                            imageFile = true;
                            break;
                        }
                    }                    

                    //Check Ideal Folder for Test Match
                    idealExists = false;
                    for (i = 0; i < idealFiles.Length; i++)
                    {
                        myFile = new FileInfo(testFiles[t]);
                        justFile = Path.GetFileName(myFile.Name);
                        split = justFile.IndexOf(".");
                        fileName = justFile.Substring(0, split);
                        if (fileName == Path.GetFileNameWithoutExtension(idealFiles[i]))
                        {
                            idealExists = true;
                            break;
                        }
                    }

                    //Create new row if criteria is met.
                    if (imageFile == true && idealExists == true)
                    {
                        myFile = new FileInfo(testFiles[t]);
                        justFile = Path.GetFileName(myFile.Name);
                        split = justFile.IndexOf(".");
                        fileName = justFile.Substring(0, split + 4);
                        try
                        {
                            justFile = justFile.Substring(split + 1, justFile.Length - split - 1);
                            split = justFile.IndexOf("_");
                            stage = justFile.Substring(split + 1, justFile.Length - split - 1);
                            split = stage.IndexOf("_");
                            stage = stage.Substring(0, split);

                            using (StreamReader sr = new StreamReader(tbAlg.Text))
                            {
                                while (!sr.EndOfStream)
                                {
                                    line = sr.ReadLine();
                                    if (String.IsNullOrEmpty(line)) continue;
                                    if (line.Contains(stage))
                                    {
                                        line = line.Remove(0, stage.Length + 3);
                                        break;
                                    }
                                }
                            }
                        }
                        catch
                        {
                            stage = "Unknown";
                            line = "Algorithm Not Found";
                        }

                        objListView = lvTestResult.Items.Add(stage);
                        objListView.SubItems.Add(line);
                        objListView.SubItems.Add(myFile.Name);
                        objListView.SubItems.Add(myFile.DirectoryName);
                        objListView.SubItems.Add(fileName);
                        objListView.SubItems.Add(tb_IdealDir.Text);
                        objListView.SubItems.Add("null");
                    }
                }
            }
            else
            {
                if (error == 1 && tb_TestDir.Text != "No Folder Selected")
                    MessageBox.Show("Directory does not exist.", "Choose another directory.", MessageBoxButtons.OK, MessageBoxIcon.Question);
                else if (error == 2 && tb_IdealDir.Text != "No Folder Selected")
                    MessageBox.Show("Mask directory not included.", "Include a mask directory.", MessageBoxButtons.OK, MessageBoxIcon.Question);
            }
        }

        //Changes parameter permissions for each checkbox.
        private void cb_CheckedChanged(object sender, EventArgs e)
        {
            tb_RMSR.Enabled = tb_RMSG.Enabled = tb_RMSB.Enabled = cb_RMS.Checked;
            tb_RMSR.BackColor = tb_RMSG.BackColor = tb_RMSB.BackColor = cb_RMS.Checked ? Color.White : Color.DarkGray;
            tb_SNRR.Enabled = tb_SNRG.Enabled = tb_SNRB.Enabled = cb_SNR.Checked;
            tb_SNRR.BackColor = tb_SNRG.BackColor = tb_SNRB.BackColor = cb_SNR.Checked ? Color.White : Color.DarkGray;
            tb_SUBR.Enabled = tb_SUBG.Enabled = tb_SUBB.Enabled = cb_SubtractEnergy.Checked;
            tb_SUBR.BackColor = tb_SUBG.BackColor = tb_SUBB.BackColor = cb_SubtractEnergy.Checked ? Color.White : Color.DarkGray;
            tb_DICER.Enabled = tb_DICEG.Enabled = tb_DICEB.Enabled = cb_DICE.Checked;
            tb_DICER.BackColor = tb_DICEG.BackColor = tb_DICEB.BackColor = cb_DICE.Checked ? Color.White : Color.DarkGray;
            tb_JaccR.Enabled = tb_JaccG.Enabled = tb_JaccB.Enabled = cb_Jaccard.Checked;
            tb_JaccR.BackColor = tb_JaccG.BackColor = tb_JaccB.BackColor = cb_Jaccard.Checked ? Color.White : Color.DarkGray;
            tb_OverR.Enabled = tb_OverG.Enabled = tb_OverB.Enabled = cb_Over.Checked;
            tb_OverR.BackColor = tb_OverG.BackColor = tb_OverB.BackColor = cb_Over.Checked ? Color.White : Color.DarkGray;
            tb_XORR.Enabled = tb_XORG.Enabled = tb_XORB.Enabled = tb_Thresh.Enabled = tb_Thresh.Visible = lb_Thresh.Visible = cb_XOR.Checked;
            tb_XORR.BackColor = tb_XORG.BackColor = tb_XORB.BackColor = tb_Thresh.BackColor = cb_XOR.Checked ? Color.White : Color.DarkGray;
        }

        private void cbSelectAll_CheckedChanged(object sender, EventArgs e)
        {
            cb_RMS.Checked = cb_SNR.Checked = cb_SubtractEnergy.Checked = cb_DICE.Checked = cb_Jaccard.Checked = cbSelectAll.Checked;
            cb_Over.Checked = cb_XOR.Checked = cb_Average.Checked = cb_StdDev.Checked = cbSelectAll.Checked;
        }

        private void bt_Alg_Click(object sender, EventArgs e)
        {
            if (fileBrowser.ShowDialog() == DialogResult.OK)
            {
                using (StreamReader sr = new StreamReader(fileBrowser.FileName))
                {
                    string firstLine = sr.ReadLine();
                    if (firstLine.Contains("ID") && firstLine.Contains("Algorithm"))
                        tbAlg.Text = fileBrowser.FileName;
                    else
                    {
                        tbAlg.Text = "Invalid File Format.";
                        MessageBox.Show("Algorithm file selected has invalid formatting", "Invalid algorithm file.", MessageBoxButtons.OK, MessageBoxIcon.Question);
                    }
                }
            }
        }
     
        private void bt_AddFolder_Click(object sender, EventArgs e)
        {
            algorithmImage.image_btAddFolder_Click();
        }

        private void bt_DecreaseStage_Click(object sender, EventArgs e)
        {
            algorithmProcess.process_bt_DecreaseStage_Click();
        }

        private void bt_IncreaseStage_Click(object sender, EventArgs e)
        {
            algorithmProcess.process_bt_IncreaseStage_Click();
        }

        private void btnAddCTable_Click(object sender, EventArgs e)
        {
            string[] testFiles = null;
            if (Directory.Exists(tb_TestDir.Text))
            {
                testFiles = Directory.GetFiles(tb_TestDir.Text, "*", SearchOption.AllDirectories);
                if (testFiles.Length > 5000)
                {
                    DialogResult dResult = MessageBox.Show("The image set was found to be greater than 5000 images. This " +
                        "could cause decreased performance and will take a while. Continue?", "Large Image Set", MessageBoxButtons.YesNo);
                    if (dResult == DialogResult.Yes)
                        updatelistViewWithCompareMain();
                }
                else
                    updatelistViewWithCompareMain();
            }
            else
                MessageBox.Show("Test folder does not exist.", "No Test Folder", MessageBoxButtons.OK);
        }

        private void abortTimer_Tick(object sender, EventArgs e)
        {
            if (btTestRun.Enabled == false)  //it means Run Button is press down
            {
                if (algorithmTest.aborted == 1)
                {
                    algorithmTest.aborted = 0;
                    btRunStop_Click_1(null, null);
                }
                else if (algorithmTest.aborted == 3)
                {
                    btRunStop_Click_1(null, null);
                    MDIMainFormRef.endProgram();
                    this.Dispose();
                }
            }
        }

        private void listView_MouseDoubleClick(object sender, MouseEventArgs e)
        {
            ListView lv = sender as ListView;
            if (lv.SelectedItems.Count == 0)
            {
                MessageBox.Show("No Images In Table.", "Please add an image.", MessageBoxButtons.OK, MessageBoxIcon.Warning);
            }
            else
            {
                ListView.SelectedIndexCollection indexes = lv.SelectedIndices;
                foreach (int index in indexes)
                {
                    if (lv.Name == "lvImage")
                    {
                        imageNamePath = lv.Items[index].SubItems[1].Text;
                        idealNamePath = lv.Items[index].SubItems[3].Text;
                    }
                    else
                    {
                        imageNamePath = lv.Items[index].SubItems[3].Text + "\\" + lv.Items[index].SubItems[2].Text;
                        idealNamePath = lv.Items[index].SubItems[5].Text + "\\" + lv.Items[index].SubItems[4].Text;
                    }
                }
                if (File.Exists(imageNamePath))
                {
                    viewImage = new imageView(MDIMainFormRef, imageNamePath);
                    viewImage.MdiParent = MDIMainFormRef;
                    viewImage.Show();
                }
                else
                {
                    MessageBox.Show("Test Image File Not Found.", "File Not Found.", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                }
                if (File.Exists(idealNamePath))
                {
                    idealImage = new imageView(MDIMainFormRef, idealNamePath);
                    idealImage.MdiParent = MDIMainFormRef;
                    idealImage.Show();
                }
                else
                {
                    MessageBox.Show("Ideal Image File Not Found.", "File Not Found.", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                }
            }
        }

        public void deleteListView()
        {
            if (lvTestResult.Items.Count == 0)
            { }
            else
            {
                lvTestResult.Items.Clear();
            }
        }

        public void repairCompare()
        {
            if (tb_RMSR.Text == "") tb_RMSR.Text = "10";
            if (tb_RMSG.Text == "") tb_RMSG.Text = "10";
            if (tb_RMSB.Text == "") tb_RMSB.Text = "10";
            if (tb_SNRR.Text == "") tb_SNRR.Text = "15";
            if (tb_SNRG.Text == "") tb_SNRG.Text = "15";
            if (tb_SNRB.Text == "") tb_SNRB.Text = "15";
            if (tb_SUBR.Text == "") tb_SUBR.Text = "0.5";
            if (tb_SUBG.Text == "") tb_SUBG.Text = "0.5";
            if (tb_SUBB.Text == "") tb_SUBB.Text = "0.5";
            if (tb_DICER.Text == "") tb_DICER.Text = "0.8";
            if (tb_DICEG.Text == "") tb_DICEG.Text = "0.8";
            if (tb_DICEB.Text == "") tb_DICEB.Text = "0.8";
            if (tb_JaccR.Text == "") tb_JaccR.Text = "0.8";
            if (tb_JaccG.Text == "") tb_JaccG.Text = "0.8";
            if (tb_JaccB.Text == "") tb_JaccB.Text = "0.8";
            if (tb_OverR.Text == "") tb_OverR.Text = "0.8";
            if (tb_OverG.Text == "") tb_OverG.Text = "0.8";
            if (tb_OverB.Text == "") tb_OverB.Text = "0.8";
            if (tb_XORR.Text == "") tb_XORR.Text = "0.2";
            if (tb_XORG.Text == "") tb_XORG.Text = "0.2";
            if (tb_XORB.Text == "") tb_XORB.Text = "0.2";
            if (tb_Thresh.Text == "") tb_Thresh.Text = "128";
            if (rb_FullTest.Checked == false && rb_Test.Checked == false && rb_Compare.Checked == false) rb_FullTest.Checked = true;
            if (tb_TestDir.Text == "") tb_TestDir.Text = "No Folder Selected";
            if (tb_IdealDir.Text == "") tb_IdealDir.Text = "No Folder Selected";
            if (tbAlg.Text == "") tbAlg.Text = "No File Selected";
        }
    }
}



