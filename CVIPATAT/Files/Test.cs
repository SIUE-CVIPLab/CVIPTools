
/***************************************************************************
* =========================================================================
*
*			 CVIP_ATAT - Dr. Scott Umbaugh SIUE
*
* =========================================================================
*
*             File Name: Test.cs
*           Description: Used to create resultant images.
*   Initial Coding Date: June 6, 2006
*Last Modification Made: June 16, 2021
*  Programming Language: Visual Studio C#.NET 2019
*             Credit(s): Wenjun(Evan) Bian, Pelin Guvenc, Charles Stacey
*                        Southern Illinois University at Edwardsville
*
*		  Copyright (c): 2010-2021 SIUE - Scott Umbaugh
****************************************************************************/

using System;
using System.Threading;
using System.Windows.Forms;
using System.IO;
using System.Data.OleDb;
using System.Runtime.InteropServices;
using System.Data;
using SERVERLib;

namespace CVIP_ATAT.Files
{
    class Test
    {
        CVIPTools CVIPToolsTestRef;
        MDIMainForm MTestRef;
        CVIPATATForm CTestRef;
        Processes ProcessesTestRef;
        ManualResetEvent mainThreadCTL;

        public Thread testRunThread;

        string[,] processInputImageName; //[imageName][idealImageName]
        string[][] processAlgorithm; //[stage][option: algorithm]

        /*String*/
        string[][][] processParameter;//[stage][option: algorithm][Parameter: 1,2,3..]
        string[] parameterBackup;//[Parameter 1,2,3...]

        string stageOption, prevStageOption;
        int[] stageRepeatTimesCount;
        static string outputDirectory, outputTempDirectory;

        //for testRun input parameters
        string algorithmT, algorithmF, inputImagePathNameT, outputImagePathNameT; //Name+Algorithm
        string[] algorithms;

        int stageCount;

        //Error Markings for the compare stage
        bool[] avgStd = new bool[2]; //Tells if avg or stddev is used.
        public int testComp = 0; //Needed to tell what type of test if currently running.
        public int typeOfTest; //Determines the type of test.
        public int ranTest = 0;
        double[] errorValues = new double[21]; //Saves error metric values.
        bool isError; //Checks if an error is selected.
        public int aborted = 0;

        /*Used for obtaining the block size for the High_Freq_Emphasis*/
        int no_of_rows;
        int no_of_cols;
        int block_size;
        int fft_block_size;
        int dct_block_size;


        public int totalOption;
        public int finishedOptionCount;
        public int totalImageCount;

        //Saves Ideal String
        string idealFolder = null;

        public Test(CVIPATATForm reference, MDIMainForm reference1, Processes reference2, CVIPTools reference3, ManualResetEvent threadCTL)
        {
            CTestRef = reference;
            MTestRef = reference1;
            ProcessesTestRef = reference2;
            CVIPToolsTestRef = reference3;
            mainThreadCTL = threadCTL;            
        }


        //Starts the test
        public void test_btTestRun_Click()
        {
            try
            {
                //Get error data and save it to an array.
                getMetrics();

                MTestRef.savenow();

                //Fixed Save Data Error
                ranTest = 1;

                testComp = 0;
                int stageMissSign = 0;

                //Reset Progress Bar
                CTestRef.labelShowProgress.Text = "Progress  %";
                CTestRef.tbFOption.Text = "0";
                CTestRef.pBarTest.Maximum = 0;
                CTestRef.pBarTest.Minimum = 0;

                //Checks if the test portion is needed.
                if (typeOfTest == 0 || typeOfTest == 1)
                {
                    CTestRef.deleteListView();
                    //check whether we miss a stage. For example, we cannot have stages 3 and 5 without stage 4
                    for (int j = 0; j < CTestRef.lvProcess.Items.Count; j++)
                    {
                        if (j == 0)
                        {
                            if (Convert.ToInt16(CTestRef.lvProcess.Items[j].SubItems[0].Text) != 1)
                            {
                                stageMissSign = 1;
                            }
                        }
                        else
                        {
                            if (Convert.ToInt16(CTestRef.lvProcess.Items[j].SubItems[0].Text) - Convert.ToInt16(CTestRef.lvProcess.Items[j - 1].SubItems[0].Text) > 1)
                            {
                                stageMissSign = 1;
                            }
                        }

                    }

                    //judge wether image and process have been selected.
                    if (CTestRef.lvImage.Items.Count == 0 || CTestRef.lvProcess.Items.Count == 0)
                    {
                        MessageBox.Show("You must select a image or a process before run", "Select image and process",
                                    MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    }
                    else if (stageMissSign == 1)
                    {
                        MessageBox.Show("You can select several process for the same stage; however, you can not miss a stage. For example, you can not "
                          + "select stage that is larger than '5', if the largest stage in the listview is '3'. Please check the stage and fix the problem before run the test.", "Please re-select the stage",
                           MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    }
                    else
                    {
                        preTestRun();
                    }
                }
                else
                {
                    //updatelistViewWithCompare();
                    testComp = 1;
                    preCompareRun();
                }
            }
            catch
            {
                MessageBox.Show("Experiment aborted due to crash.", "Experiment Aborted!", MessageBoxButtons.OK, MessageBoxIcon.Error);
                CTestRef.labelShowProgress.Text = "Progress  %";
                CTestRef.tbFOption.Text = "0";
                CTestRef.pBarTest.Maximum = 0;
                CTestRef.pBarTest.Minimum = 0;
                CTestRef.btPauseClickSign = 0;
                CTestRef.btTestRun.Enabled = true;
                CTestRef.btRunPause.Enabled = false;
                CTestRef.btRunPause.Text = "Pause";
                CTestRef.btRunStop.Enabled = false;
                CTestRef.btRunStopClickSign = 1;
            }
            GC.Collect();
        }

        //Initializes test and Starts Thread
        public void preTestRun()
        {
            //get data form GUI( image , process, parameter, etc) for testing and analyzing.

            int indexForlvProcess = 0;

            //initiate data
            totalImageCount = CTestRef.lvImage.Items.Count;

            finishedOptionCount = 0;
            stageCount = 0;
            totalOption = 1;

            try
            {
                //store Name for all images and ideal images
                processInputImageName = new string[totalImageCount, 2];
                for (int i = 0; i < totalImageCount; i++)
                {
                    processInputImageName[i, 0] = CTestRef.lvImage.Items[i].SubItems[1].Text;
                    processInputImageName[i, 1] = CTestRef.lvImage.Items[i].SubItems[3].Text;
                }
            }
            catch
            {
                MessageBox.Show("Image Table Unsuccessfully Read.",
                         "Warning", MessageBoxButtons.OK, MessageBoxIcon.Warning);
            }

            try
            {
                //get the algorithm and parameter
                //Create a sub-directory for saving output image

                //public int[] optionInOneStageCount = new int[]{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
                //the number of elements that are not '0' means how many stage are.
                //the value of every element means how many options in that stage are.
                //the order of stage is the order of array, the first element means the first stage....

                //get the number of stage and total option
                for (int i = 0; i < Processes.optionInOneStageCount.Length; i++)
                {
                    if (Processes.optionInOneStageCount[i] != 0)
                    {
                        stageCount++;
                        totalOption = totalOption * Processes.optionInOneStageCount[i];
                    }
                }

                //define a jagged three dimensional array for saving stages, options and parameter.
                processParameter = new string[stageCount][][];
                for (int i = 0; i < stageCount; i++)
                {
                    processParameter[i] = new string[Processes.optionInOneStageCount[i]][];
                }
                for (int i = 0; i < stageCount; i++)
                {
                    for (int j = 0; j < Processes.optionInOneStageCount[i]; j++)
                    {
                        processParameter[i][j] = new string[3]; //current we just have 3 parameters
                    }
                }

                //define a jagged two dimensional array for saving stages and options(algorithms).
                processAlgorithm = new string[stageCount][];
                for (int i = 0; i < stageCount; i++)
                {
                    processAlgorithm[i] = new string[Processes.optionInOneStageCount[i]];
                }

                //initiate the jagged two dimension with stage and algorithm
                //and initiate the jagged three dimension with parameters
                for (int i = 0; i < stageCount; i++)
                {
                    if (i == 0)
                    {
                        indexForlvProcess = 0;
                    }
                    else
                    {
                        indexForlvProcess = indexForlvProcess + Processes.optionInOneStageCount[i - 1];
                    }

                    for (int j = 0; j < Processes.optionInOneStageCount[i]; j++)
                    {
                        processAlgorithm[i][j] = CTestRef.lvProcess.Items[j + indexForlvProcess].SubItems[2].Text;

                        /*String*/
                        processParameter[i][j][0] = CTestRef.lvProcess.Items[j + indexForlvProcess].SubItems[3].Text;
                        processParameter[i][j][1] = CTestRef.lvProcess.Items[j + indexForlvProcess].SubItems[4].Text;
                        processParameter[i][j][2] = CTestRef.lvProcess.Items[j + indexForlvProcess].SubItems[5].Text;
                    }
                }

                //Create a sub-directory in the project's directory for saving outputimage
                if (Directory.Exists(CTestRef.CVIP_projectPath + "\\Image Results\\") == true)
                {
                    DirectoryInfo createDirectory = new DirectoryInfo(CTestRef.CVIP_projectPath + "\\Image Results\\");
                    foreach (FileInfo file in createDirectory.GetFiles())
                    {
                        file.Delete();
                    }
                    foreach (DirectoryInfo deleteSub in createDirectory.GetDirectories())
                    {
                        deleteSub.Delete(true);
                    }
                }
                else
                {
                    DirectoryInfo createDirectory = new DirectoryInfo(CTestRef.CVIP_projectPath + "\\Image Results\\");
                    createDirectory.Create();
                }
                outputDirectory = CTestRef.CVIP_projectPath + "\\Image Results\\";


                if (Directory.Exists(CTestRef.CVIP_projectPath + "\\Temp\\") == true)
                {
                    DirectoryInfo createDirectory = new DirectoryInfo(CTestRef.CVIP_projectPath + "\\Temp\\");
                    foreach (FileInfo file in createDirectory.GetFiles())
                    {
                        file.Delete();
                    }
                }
                else
                {
                    DirectoryInfo createDirectory = new DirectoryInfo(CTestRef.CVIP_projectPath + "\\Temp\\");
                    createDirectory.Create();
                }
                outputTempDirectory = CTestRef.CVIP_projectPath + "\\Temp\\";

                //Multiple Ideal Folders Error Check
                if (typeOfTest == 0)
                {
                    string cFolder, pFolder;
                    pFolder = idealFolder = Path.GetDirectoryName(CTestRef.lvImage.Items[0].SubItems[3].Text);
                    for (int i = 0; i < totalImageCount; i++)
                    {
                        cFolder = Path.GetDirectoryName(CTestRef.lvImage.Items[i].SubItems[3].Text);
                        if(cFolder == "" || pFolder == "")
                        {
                            MessageBox.Show("All test files need ideal files.", "Ideal File Missing!", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                            return;
                        }
                        if (cFolder != pFolder)
                        {
                            MessageBox.Show("The experiment requires a single ideal folder.", "Multiple Ideal Folders Found!", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                            return;
                        }
                    }
                }

                //start thread
                if (typeOfTest == 0)
                {
                    ThreadStart testRunThreadStart = new ThreadStart(testRunThreadEntryPoint);
                    testRunThread = new Thread(testRunThreadStart);
                    testRunThread.IsBackground = true;
                    testRunThread.Name = "testRunThread";
                    testRunThread.Start();
                }
                else
                {
                    ThreadStart testRunThreadStart = new ThreadStart(OnlyTestThreadEntryPoint);
                    testRunThread = new Thread(testRunThreadStart);
                    testRunThread.IsBackground = true;
                    testRunThread.Name = "testRunThread";
                    testRunThread.Start();
                }

                //enable pause and stop thread button
                CTestRef.btTestRun.Enabled = false;
                CTestRef.btRunPause.Enabled = true;
                CTestRef.btRunStop.Enabled = true;
            }
            catch (COMException ce)
            {
                MessageBox.Show("Experiment Failed", "Experiment Crash", MessageBoxButtons.OK, MessageBoxIcon.Warning);
            }
            catch
            {
                MessageBox.Show("Experiment Failed", "Experiment Crash", MessageBoxButtons.OK, MessageBoxIcon.Warning);
            }

        }

        //Initializes Compare and Starts Thread
        public void preCompareRun()
        {
            finishedOptionCount = 100;

            try
            {
                CTestRef.resultLink.Visible = true;
                CTestRef.resultLink.Enabled = true;

                //start thread
                ThreadStart testRunThreadStart = new ThreadStart(OnlyCompareThreadEntryPoint);
                testRunThread = new Thread(testRunThreadStart);
                testRunThread.IsBackground = true;
                testRunThread.Name = "compareRunThread";
                testRunThread.Start();

                //enable pause and stop thread button
                CTestRef.btTestRun.Enabled = false;
                CTestRef.btRunPause.Enabled = true;
                CTestRef.btRunStop.Enabled = true;
            }
            catch (COMException ce)
            {
                // try something else 
                MessageBox.Show("Comparison Experiment Failed", "Experiment Crash", MessageBoxButtons.OK, MessageBoxIcon.Warning);

            }
        }

        public OleDbConnection testCon;
        DataSet myDataSet;
        DataTable myDataTable;
        OleDbDataAdapter myDataAdapter;
        OleDbCommandBuilder myCommandBuild;

        //Runs Full Test
        public void testRunThreadEntryPoint()
        {
            //connect to database for save data
            string strAccessConn = "Provider=Microsoft.JET.OLEDB.4.0;" +
                       "Data Source=" + CTestRef.CVIP_projectPath + "\\CVIPATAT_Database.mdb";
            string strAccessSelect = "Select * from TestResult"; //select the table

            testCon = new OleDbConnection(strAccessConn);
            myDataAdapter = new OleDbDataAdapter();
            myCommandBuild = new OleDbCommandBuilder(myDataAdapter);

            myDataAdapter.SelectCommand = new OleDbCommand(strAccessSelect, testCon);
            testCon.Open();

            //Create a DataTable with the name of the table in the database.
            //Create a DataSet including the DataTable.
            myDataSet = new DataSet();
            myDataTable = new DataTable();
            myDataSet.Tables.Add(myDataTable);

            //open the table ."TestResult" is the name of source table to map from;
            //                "DataTestResult" is the name of  is dataset table to map to
            myDataAdapter.TableMappings.Add("TestResult", "dataTestResult");

            //load current data in database into the local table copy
            myDataAdapter.Fill(myDataSet, "TestResult");

            //clear the virtual database
            myDataSet.Tables["DataTestResult"].Clear();

            ////close the true database
            testCon.Close();


            MTestRef.runTestFinishSign = 0;
            taskDistribute();
            try
            {
                Directory.Delete(outputTempDirectory, true);
            }
            catch
            {
                MessageBox.Show("Temporary folder not deleted.", "Temporary Folder Not Deleted", MessageBoxButtons.OK, MessageBoxIcon.Warning);
            }
            //MTestRef.runTestFinishSign = 1;

            //Check Comparison Metrics.
            if (!Directory.Exists(outputDirectory))
            {
                MessageBox.Show("outputDirectory not created.", "outputDirectory missing", MessageBoxButtons.OK, MessageBoxIcon.Warning);
            }
            else if (!Directory.Exists(idealFolder + "\\"))
            {
                MessageBox.Show("Ideal directory not found.", "Missing ideal directory", MessageBoxButtons.OK, MessageBoxIcon.Warning);
            }
            else if (!File.Exists(CTestRef.CVIP_projectPath + "\\AlgorithmData.txt"))
            {
                MessageBox.Show("Algorithm file not created.", "Missing algorithm file", MessageBoxButtons.OK, MessageBoxIcon.Warning);
            }
            else
            {
                //MTestRef.runTestFinishSign = 0;
                if (isError == true)
                {
                    testComp = 1;
                    Compare compareTest = new Compare(outputDirectory, idealFolder + "\\", CTestRef.CVIP_projectPath + "\\AlgorithmData.txt", errorValues, avgStd, Convert.ToUInt16(CTestRef.tb_Thresh.Text), CTestRef, mainThreadCTL);
                    compareTest.compareImages(ref finishedOptionCount);
                    compareTest = null;
                }
                else
                {
                    MessageBox.Show("No Error Metrics Chosen", "Choose Error Metric", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                }
            }
            //Directory.Delete(outputTempDirectory, true);
            ranTest = 0;
            MTestRef.runTestFinishSign = 1;
        }

        //Runs Test Thread
        public void OnlyTestThreadEntryPoint()
        {
            //connect to database for save data
            string strAccessConn = "Provider=Microsoft.JET.OLEDB.4.0;" +
                       "Data Source=" + CTestRef.CVIP_projectPath + "\\CVIPATAT_Database.mdb";
            string strAccessSelect = "Select * from TestResult"; //select the table

            testCon = new OleDbConnection(strAccessConn);
            myDataAdapter = new OleDbDataAdapter();
            myCommandBuild = new OleDbCommandBuilder(myDataAdapter);

            myDataAdapter.SelectCommand = new OleDbCommand(strAccessSelect, testCon);
            testCon.Open();

            //Create a DataTable with the name of the table in the database.
            //Create a DataSet including the DataTable.
            myDataSet = new DataSet();
            myDataTable = new DataTable();
            myDataSet.Tables.Add(myDataTable);

            //open the table ."TestResult" is the name of source table to map from;
            //                "DataTestResult" is the name of  is dataset table to map to
            myDataAdapter.TableMappings.Add("TestResult", "dataTestResult");

            //load current data in database into the local table copy
            myDataAdapter.Fill(myDataSet, "TestResult");

            //clear the virtual database
            myDataSet.Tables["DataTestResult"].Clear();

            ////close the true database
            testCon.Close();


            MTestRef.runTestFinishSign = 0;
            taskDistribute();
            try
            {
                Directory.Delete(outputTempDirectory, true);
            }
            catch
            {
                MessageBox.Show("Temporary folder not deleted.", "Temporary Folder Not Deleted", MessageBoxButtons.OK, MessageBoxIcon.Warning);
            }

            ranTest = 0;
            MTestRef.runTestFinishSign = 1;
        }

        //Runs Comparison Thread
        public void OnlyCompareThreadEntryPoint()
        {
            if (!Directory.Exists(CTestRef.tb_TestDir.Text))
            {
                MessageBox.Show("Test directory not found.", "Missing test directory", MessageBoxButtons.OK, MessageBoxIcon.Warning);
            }
            else if (!Directory.Exists(CTestRef.tb_IdealDir.Text))
            {
                MessageBox.Show("Ideal directory not found.", "Missing ideal directory", MessageBoxButtons.OK, MessageBoxIcon.Warning);
            }
            else if (!File.Exists(CTestRef.tbAlg.Text))
            {
                MessageBox.Show("Algorithm file not found.", "Missing algorithm file", MessageBoxButtons.OK, MessageBoxIcon.Warning);
            }
            else
            {
                MTestRef.runTestFinishSign = 0;
                if (isError == true)
                {
                    Compare compareTest = new Compare(CTestRef.tb_TestDir.Text + "\\", CTestRef.tb_IdealDir.Text + "\\", CTestRef.tbAlg.Text, errorValues, avgStd, Convert.ToUInt16(CTestRef.tb_Thresh.Text), CTestRef, mainThreadCTL);
                    compareTest.compareImages(ref finishedOptionCount);
                    compareTest = null;
                }
                else
                {
                    MessageBox.Show("No Error Metrics Chosen", "Choose Error Metric", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                }
            }
            MTestRef.runTestFinishSign = 1;
        }

        //Loops through all of the algorithm options
        private void taskDistribute()
        {
            int loopCount = 0;
            int[] optionIndexForStage; //index for option in each stage that stands for the current progress of process
            int[] optionIndexCarry;    //a variable for dealing with optionIndexForStage.
            int temp;
            int i, j, y, z, nameTemp, stageOptionTemp; //loop count
            int count = 0;
            int split;
            string justFile, algorithm, newPath;

            algorithms = new string[totalOption];

            optionIndexCarry = new int[stageCount];
            optionIndexForStage = new int[stageCount];
            parameterBackup = new string[3];

            FileInfo inputImageName, initiateFile, myFile;
            DataRow newRow;

            //initiate the optionIndexForStage
            for (i = 0; i < stageCount; i++) //now maximum stage is 20
            {
                optionIndexForStage[i] = 0;
            }

            //calculate the times of loop for every stage in order to avoid redundant work.
            stageRepeatTimesCount = new int[stageCount];
            for (i = 0; i < stageCount; i++)
            {
                stageRepeatTimesCount[i] = 1;
                temp = i;
                while (temp < stageCount - 1)
                {
                    stageRepeatTimesCount[i] = stageRepeatTimesCount[i] * Processes.optionInOneStageCount[temp + 1];
                    temp++;
                }
            }

            //distribute option for run
            for (z = 0; z < totalImageCount; z++)//image loop
            {
                inputImageName = new FileInfo(processInputImageName[z, 0]);
                for (y = 0; y < totalOption; y++) //option loop
                {
                    for (i = 0; i < stageCount; i++) //stage loop
                    {
                        mainThreadCTL.WaitOne();
                        if (loopCount % stageRepeatTimesCount[i] == 0)
                        {
                            //backup the parameter for the current stage and option
                            for (j = 0; j < parameterBackup.Length; j++)
                            {
                                parameterBackup[j] = processParameter[i][optionIndexForStage[i]][j];
                            }

                            //first stage
                            if (i == 0)
                            {
                                //use x.x.x(stage and option) to represent algorithm
                                stageOption = optionIndexForStage[i].ToString() + ".";

                                //algorithm
                                algorithmT = processAlgorithm[i][optionIndexForStage[i]];

                                //Fill in algorithm array for text
                                if (stageCount == 1)
                                {
                                    algorithmF = stageOption + "   " + algorithmT;
                                    for (int param = 0; param < 3; param++)
                                    {
                                        if (processParameter[i][optionIndexForStage[i]][param] != "-0")
                                        {
                                            algorithmF += processParameter[i][optionIndexForStage[i]][param];
                                            if (param < 2)
                                                if (processParameter[i][optionIndexForStage[i]][param + 1] != "-0")
                                                    algorithmF += ",";
                                        }
                                    }
                                    if (count < totalOption)
                                    {
                                        algorithms[count] = algorithmF;
                                        count++;
                                    }
                                    algorithmF = algorithmF.Substring(5, algorithmF.Length - 5);
                                }


                                //input Image's Path and Name
                                inputImagePathNameT = processInputImageName[z, 0];

                                //name the OutputImage's name and path
                                //save image in temporary directory
                                string extension;
                                extension = Path.GetExtension(inputImageName.Name);
                                if (outputTempDirectory != "null")
                                    if (stageCount != 1)
                                        outputImagePathNameT = outputTempDirectory + inputImageName.Name + stageOption;
                                    else
                                        outputImagePathNameT = outputTempDirectory + inputImageName.Name + "_" + stageOption + "_" + ".vip";
                                else
                                    outputImagePathNameT += stageOption;

                                //invoke testRun
                                TestRun(algorithmT, parameterBackup, inputImagePathNameT, outputImagePathNameT);
                            }
                            else if (i == stageCount - 1)//last stage
                            {
                                //use x.x.x(stage and option) to represent algorithm
                                stageOption = "";
                                prevStageOption = "";
                                algorithmF = "";
                                for (stageOptionTemp = 0; stageOptionTemp <= i; stageOptionTemp++)
                                {
                                    stageOption = stageOption + optionIndexForStage[stageOptionTemp].ToString() + ".";
                                    //Determine Algorithm String
                                    algorithmF += processAlgorithm[stageOptionTemp][optionIndexForStage[stageOptionTemp]];
                                    for (int param = 0; param < 3; param++)
                                    {
                                        if (processParameter[stageOptionTemp][optionIndexForStage[stageOptionTemp]][param] != "-0")
                                        {
                                            algorithmF += processParameter[stageOptionTemp][optionIndexForStage[stageOptionTemp]][param];
                                            if (param < 2)
                                                if (processParameter[stageOptionTemp][optionIndexForStage[stageOptionTemp]][param + 1] != "-0")
                                                    algorithmF += ",";
                                        }
                                    }
                                    algorithmF += "_";
                                    if (stageOptionTemp <= i - 1)
                                        prevStageOption = prevStageOption + optionIndexForStage[stageOptionTemp].ToString() + ".";
                                }

                                //Fill in algorithm array for text
                                if (count < totalOption)
                                {
                                    algorithms[count] = stageOption + "   " + algorithmF;
                                    count++;
                                }

                                //algorithm
                                algorithmT = processAlgorithm[i][optionIndexForStage[i]];

                                //input Image's Path and Name
                                //because of loop and avoiding redundant work, the image name should be renamed.
                                initiateFile = new FileInfo(processInputImageName[z, 0]);
                                inputImagePathNameT = outputTempDirectory + initiateFile.Name;
                                if (outputTempDirectory != "null")
                                    inputImagePathNameT = outputTempDirectory + inputImageName.Name + prevStageOption;
                                else
                                    inputImagePathNameT += prevStageOption;

                                //name the OutputImage's name and path
                                //save image in temporary directory
                                outputImagePathNameT = outputDirectory + initiateFile.Name + "_" + stageOption + "_" + ".vip";

                                //invoke testRun
                                TestRun(algorithmT, parameterBackup, inputImagePathNameT, outputImagePathNameT);
                            }
                            else //other stages
                            {
                                //use x.x.x(stage and option) to represent algorithm
                                stageOption = "";
                                prevStageOption = "";
                                for (stageOptionTemp = 0; stageOptionTemp <= i; stageOptionTemp++)
                                {
                                    stageOption = stageOption + optionIndexForStage[stageOptionTemp].ToString() + ".";
                                    if (stageOptionTemp <= i - 1)
                                        prevStageOption = prevStageOption + optionIndexForStage[stageOptionTemp].ToString() + ".";
                                }

                                //algorithm
                                algorithmT = processAlgorithm[i][optionIndexForStage[i]];

                                //input Image's Path and Name
                                //because of loop and avoiding redundant work, the image name should be renamed.
                                initiateFile = new FileInfo(processInputImageName[z, 0]);
                                inputImagePathNameT = outputTempDirectory + initiateFile.Name;
                                for (nameTemp = 0; nameTemp < i; nameTemp++)
                                {
                                    if (outputTempDirectory != "null")
                                        inputImagePathNameT = outputTempDirectory + inputImageName.Name + prevStageOption;
                                    else
                                        inputImagePathNameT += prevStageOption;
                                }

                                //name the OutputImage's name and path
                                //save image in temporary directory
                                outputImagePathNameT = outputTempDirectory + initiateFile.Name;
                                if (outputTempDirectory != "null")
                                    outputImagePathNameT = outputTempDirectory + inputImageName.Name + stageOption;
                                else
                                    outputImagePathNameT += stageOption;

                                //invoke testRun
                                TestRun(algorithmT, parameterBackup, inputImagePathNameT, outputImagePathNameT);
                            }
                        } // the end of "if"
                    }//stage loop

                    //count the times of loop
                    loopCount = y + 1;
                    finishedOptionCount = z * totalOption;
                    finishedOptionCount = finishedOptionCount + loopCount;//should think about images


                    //initiate optionIndexCarry to 0,
                    for (i = 0; i < stageCount; i++)
                    {
                        optionIndexCarry[i] = 0;
                    }
                    //we distribute option after having processed the first option.
                    optionIndexCarry[stageCount - 1] = 1;

                    // get the next option
                    for (i = stageCount - 1; i >= 0; i--)
                    {
                        optionIndexForStage[i] = optionIndexForStage[i] + optionIndexCarry[i];
                        if (optionIndexForStage[i] >= Processes.optionInOneStageCount[i])
                        {
                            if (i != 0)
                            {
                                optionIndexCarry[i - 1]++;
                                optionIndexForStage[i] = 0;
                            }

                        }
                    }

                    //write data into dataTestResult------store in computer memory first(virtual database)
                    //Added if statement to get correct image locations for viewing.
                    if (stageCount == 1)
                    {
                        string correctDir;
                        newRow = myDataSet.Tables["dataTestResult"].NewRow();

                        myFile = new FileInfo(outputImagePathNameT);
                        newRow["StageOption"] = stageOption;
                        newRow["Algorithm"] = algorithmF;
                        newRow["ImageName"] = myFile.Name;
                        correctDir = myFile.DirectoryName.Replace("Temp", "outputImage");
                        newRow["ImagePath"] = correctDir;
                        myFile = new FileInfo(processInputImageName[z, 1]);
                        newRow["IdealImageName"] = myFile.Name;
                        if (myFile.Name == "Null")
                        {
                            newRow["IdealImagePath"] = "Null";
                        }
                        else
                        {
                            newRow["IdealImagePath"] = myFile.DirectoryName;
                        }
                        myFile = new FileInfo(processInputImageName[z, 0]);
                        newRow["OriginalImage"] = myFile.FullName;

                        myDataSet.Tables["dataTestResult"].Rows.Add(newRow);
                    }
                    else
                    {
                        newRow = myDataSet.Tables["dataTestResult"].NewRow();

                        myFile = new FileInfo(outputImagePathNameT);
                        newRow["StageOption"] = stageOption;
                        newRow["Algorithm"] = algorithmF;
                        newRow["ImageName"] = myFile.Name;
                        newRow["ImagePath"] = myFile.DirectoryName;
                        myFile = new FileInfo(processInputImageName[z, 1]);
                        newRow["IdealImageName"] = myFile.Name;
                        if (myFile.Name == "Null")
                        {
                            newRow["IdealImagePath"] = "Null";
                        }
                        else
                        {
                            newRow["IdealImagePath"] = myFile.DirectoryName;
                        }
                        myFile = new FileInfo(processInputImageName[z, 0]);
                        newRow["OriginalImage"] = myFile.FullName;

                        myDataSet.Tables["dataTestResult"].Rows.Add(newRow);
                    }
                }//option loop

                //initiate variables for next image
                for (i = 0; i < stageCount; i++)
                {
                    optionIndexForStage[i] = 0;
                }
                loopCount = 0;

            }//image loop


            CTestRef.saveDateToListViewSignTest = 0;

            //if stagecount==1(just one stage) copy image in temp to outputimage
            if (stageCount == 1)
            {
                // Make a reference to a directory.
                DirectoryInfo myFolder = new DirectoryInfo(outputTempDirectory);

                // Get a reference to each file in that directory.
                FileInfo[] fileRef = myFolder.GetFiles();

                // copy image.
                foreach (FileInfo copyFile in fileRef)
                {
                    if (File.Exists(outputDirectory + copyFile.Name) == true)
                    { }
                    else
                    {
                        File.Copy(copyFile.FullName, outputDirectory + copyFile.Name);
                    }
                }
            }

            GC.Collect();

            //Creating Output Folders for each algorithm:
            string[] testFiles = Directory.GetFiles(outputDirectory);

            //Loop Through Each Resulting Image
            for (int fileNumber = 0; fileNumber < testFiles.Length; fileNumber++)
            {
                mainThreadCTL.WaitOne();
                try
                {
                    //Get Path Name For Seperate Algorithm Folder
                    justFile = Path.GetFileName(testFiles[fileNumber]);

                    //Get stage name:
                    split = justFile.IndexOf(".");
                    algorithm = justFile.Substring(split + 1, justFile.Length - split - 1);
                    split = algorithm.IndexOf("_");
                    algorithm = algorithm.Substring(split + 1, algorithm.Length - split - 1);
                    split = algorithm.IndexOf("_");
                    algorithm = algorithm.Substring(0, split);

                    newPath = outputDirectory + algorithm + "\\" + justFile;

                    //Change the Path Name in the Data Table
                    for (int r = 0; r < myDataSet.Tables["dataTestResult"].Rows.Count; r++)
                    {
                        newRow = myDataSet.Tables["dataTestResult"].Rows[r];
                        if ((string)newRow["ImageName"] == justFile)
                        {
                            newRow["ImagePath"] = Path.GetDirectoryName(newPath);
                            break;
                        }
                    }

                    //Move File to New Folder
                    if (Directory.Exists(Path.GetDirectoryName(newPath)))
                    {
                        File.Move(testFiles[fileNumber], newPath);
                    }
                    else
                    {
                        Directory.CreateDirectory(Path.GetDirectoryName(newPath));
                        File.Move(testFiles[fileNumber], newPath);
                    }
                }
                catch
                {

                }
            }

            //Create algorithms text file.
            if (File.Exists(CTestRef.CVIP_projectPath + "\\AlgorithmData.txt"))
            {
                File.Delete(CTestRef.CVIP_projectPath + "\\AlgorithmData.txt");
            }
            using (StreamWriter sw = new StreamWriter(CTestRef.CVIP_projectPath + "\\AlgorithmData.txt"))
            {
                sw.Write("ID");
                for (int stg = 0; stg < stageCount * 2 + 1; stg++)
                    sw.Write(" ");
                sw.WriteLine("Algorithm");
                for (int alg = 0; alg < algorithms.Length; alg++)
                    sw.WriteLine(algorithms[alg]);
            }
        }

        //Runs specified function on an image and saves the output
        private void TestRun(string algorithm, string[] parameter, string inputImagePathName, string outputImagePathName)
        {
            int inputImage;
            int[] imageTemp = new int[3];
            int NoOfRows, NoOfCols, NoOfBands, FilterDimension;
            /*Used for Color Transformation functions*/
            double[] norm = { 0.0, 0.0, 0.0 };
            double[] refWhite = { 0.0, 0.0, 0.0 };

            double[] arr3x3 = { 0, 0, 0, 255, 1, 255, 1, 1, 1 };
            double[] arr5x5 = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 1, 255, 255, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
            double[] arr7x7 = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 1, 255, 255, 255, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
            double[] arr9x9 = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 255, 255, 1, 255, 255, 255, 255, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };

            double[] arr = null;

            mainThreadCTL.WaitOne();

            try
            {
                //read image
                inputImage = CVIPToolsTestRef.Read_Image(ref inputImagePathName);

                //temp = inputImage;
                //if (inputImage == 0)
                //{
                //    MessageBox.Show("Image not correctly read. Process: " + algorithm, "Check the image",
                //                      MessageBoxButtons.OK, MessageBoxIcon.Warning);
                //}

                //process image
                switch (algorithm)
                {
                    case "ACEII":
                        imageTemp[0] = CVIPToolsTestRef.Ace2_Filter(ref inputImage, int.Parse(parameter[0]), double.Parse(parameter[1]), double.Parse(parameter[2]));
                        CVIPToolsTestRef.Delete_Image(inputImage);
                        inputImage = imageTemp[0];
                        break;

                    case "AdaptMed":
                        imageTemp[0] = CVIPToolsTestRef.Adapt_Median_Filter(ref inputImage, int.Parse(parameter[0]));
                        CVIPToolsTestRef.Delete_Image(inputImage);
                        inputImage = imageTemp[0];
                        break;

                    case "ADFilter":
                        imageTemp[0] = CVIPToolsTestRef.AD_Filter(ref inputImage, int.Parse(parameter[0]), int.Parse(parameter[1]), int.Parse(parameter[2]));
                        CVIPToolsTestRef.Delete_Image(inputImage);
                        inputImage = imageTemp[0];
                        break;

                    case "Alpha":
                        imageTemp[0] = CVIPToolsTestRef.Alpha_Filter(ref inputImage, int.Parse(parameter[0]), int.Parse(parameter[1]));
                        CVIPToolsTestRef.Delete_Image(inputImage);
                        inputImage = imageTemp[0];
                        break;

                    /*Boie-Cox Edge Detection*/
                    case "Boie-Cox":
                        imageTemp[0] = CVIPToolsTestRef.Boiecox_Filter(ref inputImage, double.Parse(parameter[2]), 1, 0, 0, double.Parse(parameter[1]), double.Parse(parameter[0]), ref inputImage, ref inputImage);
                        CVIPToolsTestRef.Delete_Image(inputImage);
                        inputImage = imageTemp[0];
                        break;

                    /*Boie-Cox-Hysterisis Edge Detection*/
                    case "Boie-Cox-Hysterisis":
                        imageTemp[0] = CVIPToolsTestRef.Boiecox_Filter(ref inputImage, double.Parse(parameter[2]), 0, 1, 0, double.Parse(parameter[1]), double.Parse(parameter[0]), ref inputImage, ref inputImage);
                        CVIPToolsTestRef.Delete_Image(inputImage);
                        inputImage = imageTemp[0];
                        break;

                    /*Binary Thresholding*/
                    case "BT":
                        imageTemp[0] = CVIPToolsTestRef.Threshold_Segment(ref inputImage, int.Parse(parameter[0]), (int)CVIPYesNo.CVIP_NO);
                        CVIPToolsTestRef.Delete_Image(inputImage);
                        inputImage = imageTemp[0];
                        break;

                    /*Canny Edge Detection*/
                    case "Canny":
                        imageTemp[0] = CVIPToolsTestRef.Canny_Filter(ref inputImage, double.Parse(parameter[0]), double.Parse(parameter[1]), double.Parse(parameter[2]), ref inputImage, ref inputImage);
                        CVIPToolsTestRef.Delete_Image(inputImage);
                        inputImage = imageTemp[0];
                        break;

                    /*Color-to-Gray Conversion - Average*/
                    case "C2GA":
                        imageTemp[0] = CVIPToolsTestRef.Lum_Average(ref inputImage);
                        CVIPToolsTestRef.Delete_Image(inputImage);
                        inputImage = imageTemp[0];
                        break;

                    /*Color-to-Gray Conversion - Luminance*/
                    case "C2GL":
                        imageTemp[0] = CVIPToolsTestRef.Luminance_Image(ref inputImage);
                        CVIPToolsTestRef.Delete_Image(inputImage);
                        inputImage = imageTemp[0];
                        break;

                    /*Color Transformation (RGB->HSL,HSV,SCT,CCT,LUV,LAB,XYZ)*/
                    /*Works only with colored images (3 band) - for now...*/
                    case "ColorXForm":
                        if (int.Parse(parameter[0]) == 7 || int.Parse(parameter[0]) == 8)
                        {
                            for (int i = 0; i < 3; i++) norm[i] = 255.0;
                            for (int i = 0; i < 3; i++) refWhite[i] = 1.0;
                            imageTemp[0] = ColorXform(inputImage, int.Parse(parameter[0]), ref norm[0], ref refWhite[0], 1);
                            CVIPToolsTestRef.Delete_Image(inputImage);
                            inputImage = imageTemp[0];
                        }
                        else
                        {
                            for (int i = 0; i < 3; i++) norm[i] = 255.0;
                            for (int i = 0; i < 3; i++) refWhite[i] = 0.0;
                            imageTemp[0] = ColorXform(inputImage, int.Parse(parameter[0]), ref norm[0], ref refWhite[0], 1);
                            CVIPToolsTestRef.Delete_Image(inputImage);
                            inputImage = imageTemp[0];
                        }
                        break;

                    case "ContraH":
                        imageTemp[0] = CVIPToolsTestRef.Contra_Filter(ref inputImage, int.Parse(parameter[0]), int.Parse(parameter[1]));
                        CVIPToolsTestRef.Delete_Image(inputImage);
                        inputImage = imageTemp[0];
                        break;

                    case "CLAHE":
                        imageTemp[0] = CVIPToolsTestRef.CLAHE(ref inputImage, int.Parse(parameter[0]), double.Parse(parameter[1]), int.Parse(parameter[2]));
                        CVIPToolsTestRef.Delete_Image(inputImage);
                        inputImage = imageTemp[0];
                        break;

                    /*Direct Cosine Transform*/
                    case "DCT":
                        imageTemp[0] = CVIPToolsTestRef.Dct_Transform(ref inputImage, int.Parse(parameter[0]));
                        CVIPToolsTestRef.Delete_Image(inputImage);
                        inputImage = imageTemp[0];
                        dct_block_size = int.Parse(parameter[0]);
                        block_size = int.Parse(parameter[0]);
                        break;

                    case "EB":
                        imageTemp[0] = CVIPToolsTestRef.Extract_Band(ref inputImage, int.Parse(parameter[0]));
                        CVIPToolsTestRef.Delete_Image(inputImage);
                        inputImage = imageTemp[0];
                        break;

                    /*Edge Linking*/
                    case "EdgeL":
                        imageTemp[0] = CVIPToolsTestRef.Edge_Link_Filter(ref inputImage, int.Parse(parameter[0]));
                        CVIPToolsTestRef.Delete_Image(inputImage);
                        inputImage = imageTemp[0];
                        break;

                    /*Fast Fourier Transform*/
                    case "FFT":
                        imageTemp[0] = CVIPToolsTestRef.Fft_Transform(ref inputImage, int.Parse(parameter[0]));
                        CVIPToolsTestRef.Delete_Image(inputImage);
                        inputImage = imageTemp[0];
                        fft_block_size = int.Parse(parameter[0]);
                        block_size = int.Parse(parameter[0]);
                        break;

                    case "Fuzzyc":
                        if (CVIPToolsTestRef.GetNoOfBands_Image(ref inputImage) == 1)
                        {
                            imageTemp[0] = CVIPToolsTestRef.Duplicate_Image(ref inputImage);
                            imageTemp[1] = CVIPToolsTestRef.Duplicate_Image(ref inputImage);
                            imageTemp[2] = CVIPToolsTestRef.Duplicate_Image(ref inputImage);

                            inputImage = CVIPToolsTestRef.Assemble_Bands(imageTemp);

                            inputImage = CVIPToolsTestRef.Fuzzyc_Segment(ref inputImage, float.Parse(parameter[0]));
                            inputImage = CVIPToolsTestRef.Extract_Band(ref inputImage, 1);

                            CVIPToolsTestRef.Delete_Image(ref imageTemp[0]);
                            CVIPToolsTestRef.Delete_Image(ref imageTemp[1]);
                            CVIPToolsTestRef.Delete_Image(ref imageTemp[2]);
                        }
                        else
                        {
                            imageTemp[0] = CVIPToolsTestRef.Fuzzyc_Segment(ref inputImage, float.Parse(parameter[0]));
                            CVIPToolsTestRef.Delete_Image(inputImage);
                            inputImage = imageTemp[0];
                        }
                        break;

                    case "GaussianFilter":
                        imageTemp[0] = CVIPToolsTestRef.Gaussian_Blur_Filter(ref inputImage, int.Parse(parameter[0]));
                        CVIPToolsTestRef.Delete_Image(inputImage);
                        inputImage = imageTemp[0];
                        break;

                    case "Geo":
                        imageTemp[0] = CVIPToolsTestRef.Geometric_Filter(ref inputImage, int.Parse(parameter[0]));
                        CVIPToolsTestRef.Delete_Image(inputImage);
                        inputImage = imageTemp[0];
                        break;

                    /*Gray Level Quantization*/
                    case "GLQ":
                        imageTemp[0] = CVIPToolsTestRef.Gray_Quant_Segment(ref inputImage, int.Parse(parameter[0]));
                        CVIPToolsTestRef.Delete_Image(ref inputImage);
                        inputImage = imageTemp[0];
                        break;

                    /*Haar Transform*/
                    case "HaarT":
                        imageTemp[0] = CVIPToolsTestRef.Haar_Transform(ref inputImage, int.Parse(parameter[0]), int.Parse(parameter[1]));
                        CVIPToolsTestRef.Delete_Image(inputImage);
                        inputImage = imageTemp[0];
                        block_size = int.Parse(parameter[1]);
                        break;

                    case "Harmon":
                        imageTemp[0] = CVIPToolsTestRef.Harmonic_Filter(ref inputImage, int.Parse(parameter[0]));
                        CVIPToolsTestRef.Delete_Image(inputImage);
                        inputImage = imageTemp[0];
                        break;

                    /*High Boost*/
                    case "High Boost":
                        imageTemp[0] = CVIPToolsTestRef.Highboost(ref inputImage, int.Parse(parameter[0]), int.Parse(parameter[1]), int.Parse(parameter[2]));
                        CVIPToolsTestRef.Delete_Image(inputImage);
                        inputImage = imageTemp[0];
                        break;

                    /*High Freq. Emphasis with DC*/
                    case "HighBoost-DC":
                        imageTemp[0] = CVIPToolsTestRef.High_Freq_Emphasis(ref inputImage, block_size, 1, int.Parse(parameter[0]), double.Parse(parameter[1]), int.Parse(parameter[2]));
                        CVIPToolsTestRef.Delete_Image(inputImage);
                        inputImage = imageTemp[0];
                        break;

                    /*High Freq. Emphasis without DC*/
                    case "HighBoost":
                        imageTemp[0] = CVIPToolsTestRef.High_Freq_Emphasis(ref inputImage, block_size, 0, int.Parse(parameter[0]), double.Parse(parameter[1]), int.Parse(parameter[2]));
                        CVIPToolsTestRef.Delete_Image(inputImage);
                        inputImage = imageTemp[0];
                        break;

                    /*Highpass Spatial Filter*/
                    case "Highpass Spatial Filter":
                        imageTemp[0] = CVIPToolsTestRef.Highpass_Spatial(ref inputImage, int.Parse(parameter[0]));
                        CVIPToolsTestRef.Delete_Image(inputImage);
                        inputImage = imageTemp[0];
                        break;

                    /*Histogram Equalization*/
                    case "HistEq":
                        imageTemp[0] = CVIPToolsTestRef.Histeq(ref inputImage, int.Parse(parameter[0]));
                        CVIPToolsTestRef.Delete_Image(inputImage);
                        inputImage = imageTemp[0];
                        break;

                    /*Histogram Slide*/
                    case "HistSlide":
                        imageTemp[0] = CVIPToolsTestRef.Hist_Slide(ref inputImage, int.Parse(parameter[0]));
                        CVIPToolsTestRef.Delete_Image(inputImage);
                        inputImage = imageTemp[0];
                        break;

                    /*Histogram Stretch*/
                    case "HistStr":
                        imageTemp[0] = CVIPToolsTestRef.Hist_Stretch(ref inputImage, int.Parse(parameter[0]), int.Parse(parameter[1]), float.Parse(parameter[2]), float.Parse(parameter[2]));
                        CVIPToolsTestRef.Delete_Image(inputImage);
                        inputImage = imageTemp[0];
                        break;

                    case "HistThresh":
                        imageTemp[0] = CVIPToolsTestRef.Hist_Thresh_Segment(ref inputImage, float.Parse(parameter[0]));
                        CVIPToolsTestRef.Delete_Image(inputImage);
                        inputImage = imageTemp[0];
                        break;

                    /*Hough Transform*/
                    case "HT":
                        string x = "test";
                        imageTemp[0] = CVIPToolsTestRef.Hough_Filter(ref inputImage, ref x, ref parameter[0], int.Parse(parameter[1]), int.Parse(parameter[2]), 0, 1, 1, 1);
                        CVIPToolsTestRef.Delete_Image(inputImage);
                        inputImage = imageTemp[0];
                        break;

                    /*HSL -> RGB Color Space Transform*/
                    case "HSL-RGB":
                        imageTemp[0] = CVIPToolsTestRef.ColorXform(ref inputImage, 3, ref norm[0], ref refWhite[0], 2);
                        CVIPToolsTestRef.Delete_Image(inputImage);
                        inputImage = imageTemp[0];
                        break;

                    /*HSV -> RGB Color Space Transform*/
                    case "HSV-RGB":
                        imageTemp[0] = CVIPToolsTestRef.ColorXform(ref inputImage, 4, ref norm[0], ref refWhite[0], 2);
                        CVIPToolsTestRef.Delete_Image(inputImage);
                        inputImage = imageTemp[0];
                        break;

                    case "IDCT":
                        imageTemp[0] = CVIPToolsTestRef.Idct_Transform(ref inputImage, dct_block_size);
                        CVIPToolsTestRef.Delete_Image(inputImage);
                        inputImage = imageTemp[0];
                        break;

                    case "IFFT":
                        imageTemp[0] = CVIPToolsTestRef.Ifft_Transform(ref inputImage, fft_block_size);
                        CVIPToolsTestRef.Delete_Image(inputImage);
                        inputImage = imageTemp[0];
                        break;

                    /*Kuwahara Filter*/
                    case "Kuwahara Filter":
                        imageTemp[0] = CVIPToolsTestRef.Kuwahara_Filter(ref inputImage, int.Parse(parameter[0]));
                        CVIPToolsTestRef.Delete_Image(inputImage);
                        inputImage = imageTemp[0];
                        break;

                    /*Laplacian Edge Detection*/
                    case "LapEDet":
                        imageTemp[0] = CVIPToolsTestRef.Edge_Detect_Filter(ref inputImage, 5 /*EDGE_LAPLACIAN*/ , int.Parse(parameter[0]), int.Parse(parameter[1]),
                                                                         int.Parse(parameter[2]), -1, -1, -1, -1);
                        CVIPToolsTestRef.Delete_Image(inputImage);
                        inputImage = imageTemp[0];
                        break;

                    /*Label Image*/
                    case "Lbl":
                        imageTemp[0] = CVIPToolsTestRef.Label(ref inputImage);
                        CVIPToolsTestRef.Delete_Image(inputImage);
                        inputImage = imageTemp[0];
                        break;

                    case "Maxi":
                        imageTemp[0] = CVIPToolsTestRef.Maximum_Filter(ref inputImage, int.Parse(parameter[0]));
                        CVIPToolsTestRef.Delete_Image(inputImage);
                        inputImage = imageTemp[0];
                        break;

                    case "Mean":
                        imageTemp[0] = CVIPToolsTestRef.Mean_Filter(ref inputImage, int.Parse(parameter[0]));
                        CVIPToolsTestRef.Delete_Image(inputImage);
                        inputImage = imageTemp[0];
                        break;

                    case "MedCut":
                        if (CVIPToolsTestRef.GetNoOfBands_Image(ref inputImage) == 1)
                        {
                            NoOfRows = CVIPToolsTestRef.GetNoOfRows_Image(ref inputImage);
                            NoOfCols = CVIPToolsTestRef.GetNoOfCols_Image(ref inputImage);

                            imageTemp[0] = CVIPToolsTestRef.Duplicate_Image(ref inputImage);
                            imageTemp[1] = CVIPToolsTestRef.Create_Black(NoOfCols, NoOfRows);
                            imageTemp[2] = CVIPToolsTestRef.Create_Black(NoOfCols, NoOfRows);

                            //inputImage = CVIPToolsTestRef.Assemble_Bands_CSharp(ref imageTemp[0], ref imageTemp[1], ref imageTemp[2]);
                            inputImage = CVIPToolsTestRef.Assemble_Bands(imageTemp);

                            inputImage = CVIPToolsTestRef.Median_Cut_Segment(ref inputImage, int.Parse(parameter[0]), (int)CVIPYesNo.CVIP_NO, 0, 0, 0);
                            inputImage = CVIPToolsTestRef.Extract_Band(ref inputImage, 1);

                            for (int i = 0; i < 3; i++)
                            {
                                CVIPToolsTestRef.Delete_Image(ref imageTemp[i]);
                            }
                        }
                        else
                        {
                            imageTemp[0] = CVIPToolsTestRef.Median_Cut_Segment(ref inputImage, int.Parse(parameter[0]), (int)CVIPYesNo.CVIP_NO, 0, 0, 0);
                            CVIPToolsTestRef.Delete_Image(ref inputImage);
                            inputImage = imageTemp[0];
                        }
                        break;

                    case "Med":
                        imageTemp[0] = CVIPToolsTestRef.Median_Filter(ref inputImage, int.Parse(parameter[0]));
                        CVIPToolsTestRef.Delete_Image(ref inputImage);
                        inputImage = imageTemp[0];
                        break;

                    case "MidP":
                        imageTemp[0] = CVIPToolsTestRef.Midpoint_Filter(ref inputImage, int.Parse(parameter[0]));
                        CVIPToolsTestRef.Delete_Image(ref inputImage);
                        inputImage = imageTemp[0];
                        break;

                    case "MMSE":
                        imageTemp[0] = CVIPToolsTestRef.Mmse_Filter(ref inputImage, float.Parse(parameter[1]), int.Parse(parameter[0]));
                        CVIPToolsTestRef.Delete_Image(ref inputImage);
                        inputImage = imageTemp[0];
                        break;

                    case "MorphCCir":
                        imageTemp[0] = CVIPToolsTestRef.MorphClose(ref inputImage, (int)kernelType.circle, int.Parse(parameter[0]), 1, 1);
                        CVIPToolsTestRef.Delete_Image(inputImage);
                        inputImage = imageTemp[0];
                        break;

                    case "MorphCCro":
                        imageTemp[0] = CVIPToolsTestRef.MorphClose(ref inputImage, (int)kernelType.cross, int.Parse(parameter[0]), int.Parse(parameter[1]), int.Parse(parameter[2]));
                        CVIPToolsTestRef.Delete_Image(inputImage);
                        inputImage = imageTemp[0];
                        break;

                    case "MorphCR":
                        imageTemp[0] = CVIPToolsTestRef.MorphClose(ref inputImage, (int)kernelType.rectangle, int.Parse(parameter[0]), int.Parse(parameter[1]), int.Parse(parameter[2]));
                        CVIPToolsTestRef.Delete_Image(inputImage);
                        inputImage = imageTemp[0];
                        break;

                    case "MorphCS":
                        imageTemp[0] = CVIPToolsTestRef.MorphClose(ref inputImage, (int)kernelType.square, int.Parse(parameter[0]), int.Parse(parameter[1]), 1);
                        CVIPToolsTestRef.Delete_Image(inputImage);
                        inputImage = imageTemp[0];
                        break;

                    case "MorphDCir":
                        imageTemp[0] = CVIPToolsTestRef.MorphDilate(ref inputImage, (int)kernelType.circle, int.Parse(parameter[0]), 1, 1);
                        CVIPToolsTestRef.Delete_Image(inputImage);
                        inputImage = imageTemp[0];
                        break;

                    case "MorphDCro":
                        imageTemp[0] = CVIPToolsTestRef.MorphDilate(ref inputImage, (int)kernelType.cross, int.Parse(parameter[0]), int.Parse(parameter[1]), int.Parse(parameter[2]));
                        CVIPToolsTestRef.Delete_Image(inputImage);
                        inputImage = imageTemp[0];
                        break;

                    case "MorphDR":
                        imageTemp[0] = CVIPToolsTestRef.MorphDilate(ref inputImage, (int)kernelType.rectangle, int.Parse(parameter[0]), int.Parse(parameter[1]), int.Parse(parameter[2]));
                        CVIPToolsTestRef.Delete_Image(inputImage);
                        inputImage = imageTemp[0];
                        break;

                    case "MorphDS":
                        imageTemp[0] = CVIPToolsTestRef.MorphDilate(ref inputImage, (int)kernelType.square, int.Parse(parameter[0]), int.Parse(parameter[1]), 1);
                        CVIPToolsTestRef.Delete_Image(inputImage);
                        inputImage = imageTemp[0];
                        break;

                    case "MorphECir":
                        imageTemp[0] = CVIPToolsTestRef.MorphErode(ref inputImage, (int)kernelType.circle, int.Parse(parameter[0]), 1, 1);
                        CVIPToolsTestRef.Delete_Image(inputImage);
                        inputImage = imageTemp[0];
                        break;

                    case "MorphECro":
                        imageTemp[0] = CVIPToolsTestRef.MorphErode(ref inputImage, (int)kernelType.cross, int.Parse(parameter[0]), int.Parse(parameter[1]), int.Parse(parameter[2]));
                        CVIPToolsTestRef.Delete_Image(inputImage);
                        inputImage = imageTemp[0];
                        break;

                    case "MorphER":
                        imageTemp[0] = CVIPToolsTestRef.MorphErode(ref inputImage, (int)kernelType.rectangle, int.Parse(parameter[0]), int.Parse(parameter[1]), int.Parse(parameter[2]));
                        CVIPToolsTestRef.Delete_Image(inputImage);
                        inputImage = imageTemp[0];
                        break;

                    case "MorphES":
                        imageTemp[0] = CVIPToolsTestRef.MorphErode(ref inputImage, (int)kernelType.square, int.Parse(parameter[0]), int.Parse(parameter[1]), 1);
                        CVIPToolsTestRef.Delete_Image(inputImage);
                        inputImage = imageTemp[0];
                        break;

                    case "MorphOCir":
                        imageTemp[0] = CVIPToolsTestRef.MorphOpen(ref inputImage, (int)kernelType.circle, int.Parse(parameter[0]), 1, 1);
                        CVIPToolsTestRef.Delete_Image(inputImage);
                        inputImage = imageTemp[0];
                        break;

                    case "MorphOCro":
                        imageTemp[0] = CVIPToolsTestRef.MorphOpen(ref inputImage, (int)kernelType.cross, int.Parse(parameter[0]), int.Parse(parameter[1]), int.Parse(parameter[2]));
                        CVIPToolsTestRef.Delete_Image(inputImage);
                        inputImage = imageTemp[0];
                        break;

                    case "MorphOR":
                        imageTemp[0] = CVIPToolsTestRef.MorphOpen(ref inputImage, (int)kernelType.rectangle, int.Parse(parameter[0]), int.Parse(parameter[1]), int.Parse(parameter[2]));
                        CVIPToolsTestRef.Delete_Image(inputImage);
                        inputImage = imageTemp[0];
                        break;

                    case "MorphOS":
                        imageTemp[0] = CVIPToolsTestRef.MorphOpen(ref inputImage, (int)kernelType.square, int.Parse(parameter[0]), int.Parse(parameter[1]), 1);
                        CVIPToolsTestRef.Delete_Image(inputImage);
                        inputImage = imageTemp[0];
                        break;

                    /*MorphSkel 4-mask,And*/
                    case "MorphSkel 4-mask,And":
                        FilterDimension = int.Parse(parameter[0]);
                        arr = null;
                        if (FilterDimension == 3)
                            arr = arr3x3;
                        else if (FilterDimension == 5)
                            arr = arr5x5;
                        else if (FilterDimension == 7)
                            arr = arr7x7;
                        else if (FilterDimension == 9)
                            arr = arr9x9;
                        imageTemp[0] = CVIPToolsTestRef.Morph_Skeleton(ref inputImage, FilterDimension, ref arr[0], int.Parse(parameter[1]), 0, 0);
                        CVIPToolsTestRef.Delete_Image(inputImage);
                        inputImage = imageTemp[0];
                        break;

                    /*MorphSkel 4-mask,Sequential*/
                    case "MorphSkel 4-mask,Sequential":
                        FilterDimension = int.Parse(parameter[0]);
                        arr = null;
                        if (FilterDimension == 3)
                            arr = arr3x3;
                        else if (FilterDimension == 5)
                            arr = arr5x5;
                        else if (FilterDimension == 7)
                            arr = arr7x7;
                        else if (FilterDimension == 9)
                            arr = arr9x9;
                        imageTemp[0] = CVIPToolsTestRef.Morph_Skeleton(ref inputImage, FilterDimension, ref arr[0], int.Parse(parameter[1]), 0, 1);
                        CVIPToolsTestRef.Delete_Image(inputImage);
                        inputImage = imageTemp[0];
                        break;

                    /*MorphSkel 8-mask,And*/
                    case "MorphSkel 8-mask,And":
                        FilterDimension = int.Parse(parameter[0]);
                        arr = null;
                        if (FilterDimension == 3)
                            arr = arr3x3;
                        else if (FilterDimension == 5)
                            arr = arr5x5;
                        else if (FilterDimension == 7)
                            arr = arr7x7;
                        else if (FilterDimension == 9)
                            arr = arr9x9;
                        imageTemp[0] = CVIPToolsTestRef.Morph_Skeleton(ref inputImage, FilterDimension, ref arr[0], int.Parse(parameter[1]), 1, 0);
                        CVIPToolsTestRef.Delete_Image(inputImage);
                        inputImage = imageTemp[0];
                        break;

                    /*MorphSkel 8-mask,Sequential*/
                    case "MorphSkel 8-mask,Sequential":
                        FilterDimension = int.Parse(parameter[0]);
                        arr = null;
                        if (FilterDimension == 3)
                            arr = arr3x3;
                        else if (FilterDimension == 5)
                            arr = arr5x5;
                        else if (FilterDimension == 7)
                            arr = arr7x7;
                        else if (FilterDimension == 9)
                            arr = arr9x9;
                        imageTemp[0] = CVIPToolsTestRef.Morph_Skeleton(ref inputImage, FilterDimension, ref arr[0], int.Parse(parameter[1]), 1, 1);
                        CVIPToolsTestRef.Delete_Image(inputImage);
                        inputImage = imageTemp[0];
                        break;

                    case "Not":
                        if (CVIPToolsTestRef.GetDataType_Image(ref inputImage) != (int)dataType.CVIP_BYTE)
                        {
                            imageTemp[0] = CVIPToolsTestRef.Remap_Image(ref inputImage, (int)dataType.CVIP_BYTE, 0, 255);
                            CVIPToolsTestRef.Delete_Image(inputImage);
                            inputImage = imageTemp[0];
                        }
                        imageTemp[0] = CVIPToolsTestRef.Not_Image(ref inputImage);
                        CVIPToolsTestRef.Delete_Image(inputImage);
                        inputImage = imageTemp[0];
                        break;

                    case "Otsu":
                        imageTemp[0] = CVIPToolsTestRef.Otsu_Segment(ref inputImage);
                        CVIPToolsTestRef.Delete_Image(inputImage);
                        inputImage = imageTemp[0];
                        break;

                    case "ParamADFilter":
                        imageTemp[0] = CVIPToolsTestRef.Param_AD_Filter(ref inputImage, int.Parse(parameter[0]), 1, int.Parse(parameter[1]), int.Parse(parameter[2]));
                        CVIPToolsTestRef.Delete_Image(inputImage);
                        inputImage = imageTemp[0];
                        break;

                    case "PCT":
                        double[] maskP = { 0 };
                        imageTemp[0] = CVIPToolsTestRef.Pct(ref inputImage, 0, ref maskP[0]);
                        CVIPToolsTestRef.Delete_Image(inputImage);
                        inputImage = imageTemp[0];
                        break;

                    case "PCTM":
                        if (CVIPToolsTestRef.GetNoOfBands_Image(ref inputImage) == 1)
                        {
                            NoOfRows = CVIPToolsTestRef.GetNoOfRows_Image(ref inputImage);
                            NoOfCols = CVIPToolsTestRef.GetNoOfCols_Image(ref inputImage);

                            imageTemp[0] = CVIPToolsTestRef.Duplicate_Image(ref inputImage);
                            imageTemp[1] = CVIPToolsTestRef.Create_Black(NoOfCols, NoOfRows);
                            imageTemp[2] = CVIPToolsTestRef.Create_Black(NoOfCols, NoOfRows);

                            inputImage = CVIPToolsTestRef.Assemble_Bands(imageTemp);
                            for (int i = 0; i < 3; i++)
                            {
                                CVIPToolsTestRef.Delete_Image(ref imageTemp[i]);
                            }

                            imageTemp[0] = CVIPToolsTestRef.Pct_Median_Segment(ref inputImage, int.Parse(parameter[0]));
                            CVIPToolsTestRef.Delete_Image(inputImage);
                            inputImage = imageTemp[0];

                            imageTemp[0] = CVIPToolsTestRef.Label(ref inputImage);
                            CVIPToolsTestRef.Delete_Image(inputImage);
                            inputImage = imageTemp[0];

                            imageTemp[0] = CVIPToolsTestRef.Extract_Band(ref inputImage, 1);
                            CVIPToolsTestRef.Delete_Image(inputImage);
                            inputImage = imageTemp[0];
                        }
                        else
                        {
                            imageTemp[0] = CVIPToolsTestRef.Pct_Median_Segment(ref inputImage, int.Parse(parameter[0]));
                            CVIPToolsTestRef.Delete_Image(inputImage);
                            inputImage = imageTemp[0];
                        }
                        break;

                    /*Prewitt Edge Detection*/
                    /*EDGE_PREWITT = 8*/
                    case "Prewitt":
                        imageTemp[0] = CVIPToolsTestRef.Edge_Detect_Filter(ref inputImage, 8/*EDGE_PREWITT*/, int.Parse(parameter[0]), int.Parse(parameter[1]),
                                                                         int.Parse(parameter[2]), -1, -1, -1, -1);
                        CVIPToolsTestRef.Delete_Image(inputImage);
                        inputImage = imageTemp[0];
                        break;

                    /*Roberts Edge Detection*/
                    /*EDGE_ROBERTS = 6*/
                    case "Roberts":
                        imageTemp[0] = CVIPToolsTestRef.Edge_Detect_Filter(ref inputImage, 6/*EDGE_ROBERTS*/, int.Parse(parameter[0]), int.Parse(parameter[1]),
                                                                         int.Parse(parameter[2]), -1, -1, -1, -1);
                        CVIPToolsTestRef.Delete_Image(inputImage);
                        inputImage = imageTemp[0];
                        break;
                    case "SingleThresh":
                        imageTemp[0] = CVIPToolsTestRef.Auto_Threshold_Segment(ref inputImage, float.Parse(parameter[0]));
                        CVIPToolsTestRef.Delete_Image(inputImage);
                        inputImage = imageTemp[0];
                        break;

                    case "SCT":
                        if (CVIPToolsTestRef.GetNoOfBands_Image(ref inputImage) == 1)
                        {
                            imageTemp[0] = CVIPToolsTestRef.Duplicate_Image(ref inputImage);
                            imageTemp[1] = CVIPToolsTestRef.Duplicate_Image(ref inputImage);
                            imageTemp[2] = CVIPToolsTestRef.Duplicate_Image(ref inputImage);

                            inputImage = CVIPToolsTestRef.Assemble_Bands(imageTemp);

                            inputImage = CVIPToolsTestRef.Sct_Split_Segment(ref inputImage, int.Parse(parameter[0]), int.Parse(parameter[1]));
                            inputImage = CVIPToolsTestRef.Extract_Band(ref inputImage, 1);

                            for (int i = 0; i < 3; i++)
                            {
                                CVIPToolsTestRef.Delete_Image(ref imageTemp[i]);
                            }
                        }
                        else
                        {
                            inputImage = CVIPToolsTestRef.Sct_Split_Segment(ref inputImage, int.Parse(parameter[0]), int.Parse(parameter[1]));
                        }
                        break;

                    /*Sharpening AlgorithmI*/
                    case "SharpeningI":
                        imageTemp[0] = CVIPToolsTestRef.Sharpen_I(ref inputImage, 1, 2, int.Parse(parameter[0]), float.Parse(parameter[1]), float.Parse(parameter[2]), 1);
                        CVIPToolsTestRef.Delete_Image(inputImage);
                        inputImage = imageTemp[0];
                        break;

                    /*Sharpening AlgorithmII*/
                    case "SharpeningII":
                        imageTemp[0] = CVIPToolsTestRef.Sharpen_II(ref inputImage, int.Parse(parameter[0]));
                        CVIPToolsTestRef.Delete_Image(inputImage);
                        inputImage = imageTemp[0];
                        break;

                    /*Shen-Castan Edge Detection*/
                    case "Shen-Castan":
                        imageTemp[0] = CVIPToolsTestRef.Shen_Castan_Filter(ref inputImage, double.Parse(parameter[2]), 5, double.Parse(parameter[0]), double.Parse(parameter[1]), 1, ref inputImage);
                        CVIPToolsTestRef.Delete_Image(inputImage);
                        inputImage = imageTemp[0];
                        break;

                    /*Skip/Null*/
                    case "Skip":
                        break;

                    /*Sobel Edge Detection*/
                    /*EDGE_SOBEL = 7*/
                    case "Sobel":
                        imageTemp[0] = CVIPToolsTestRef.Edge_Detect_Filter(ref inputImage, 7/*EDGE_SOBEL*/, int.Parse(parameter[0]), int.Parse(parameter[1]),
                                                                         int.Parse(parameter[2]), -1, -1, -1, -1);
                        CVIPToolsTestRef.Delete_Image(inputImage);
                        inputImage = imageTemp[0];
                        break;

                    /*Spatial Quantization*/
                    case "SQuant":
                        imageTemp[0] = CVIPToolsTestRef.Spatial_Quant(ref inputImage, int.Parse(parameter[0]), int.Parse(parameter[1]), int.Parse(parameter[2]));
                        CVIPToolsTestRef.Delete_Image(inputImage);
                        inputImage = imageTemp[0];
                        break;

                    case "Thresh":
                        //cvip_yes:1, remapped to 0~255, cvip_no:0, applied directly to the image data.
                        imageTemp[0] = CVIPToolsTestRef.Threshold_Segment(ref inputImage, int.Parse(parameter[0]), (int)CVIPYesNo.CVIP_YES);
                        CVIPToolsTestRef.Delete_Image(inputImage);
                        inputImage = imageTemp[0];
                        break;

                    /*Unsharp Masking*/
                    case "Unsharp Masking":
                        imageTemp[0] = CVIPToolsTestRef.Unsharp_Filter(ref inputImage, int.Parse(parameter[0]), int.Parse(parameter[1]), double.Parse(parameter[2]), 0);
                        CVIPToolsTestRef.Delete_Image(inputImage);
                        inputImage = imageTemp[0];
                        System.Console.WriteLine("\nUnsharp Masking");
                        break;

                    /*Walsh-Hadamard Transform*/
                    case "WHTrans":
                        imageTemp[0] = CVIPToolsTestRef.Walhad_Transform(ref inputImage, int.Parse(parameter[0]), int.Parse(parameter[1]));
                        CVIPToolsTestRef.Delete_Image(inputImage);
                        inputImage = imageTemp[0];
                        block_size = int.Parse(parameter[1]);
                        break;

                    /*Watershed Segmentation*/
                    case "Watershed":
                        imageTemp[0] = CVIPToolsTestRef.Watershed_Segment(ref inputImage, int.Parse(parameter[0]), float.Parse(parameter[1]));
                        CVIPToolsTestRef.Delete_Image(inputImage);
                        inputImage = imageTemp[0];
                        break;

                    case "Yp":
                        imageTemp[0] = CVIPToolsTestRef.Ypmean_Filter(ref inputImage, int.Parse(parameter[0]), int.Parse(parameter[1]));
                        CVIPToolsTestRef.Delete_Image(inputImage);
                        inputImage = imageTemp[0];
                        break;

                    /***********************************************************************************************************/
                    /***********************************************************************************************************/
                    /***********************************************************************************************************/

                    default:
                        break;
                }

                // Write Image
                if (inputImage == 0)
                {
                    if (aborted != 2 && aborted != 3)
                    {
                        DialogResult dlg = MessageBox.Show("Process Crashed!\n\nCurrent Process: " + algorithm + "\n\nInput Image Path: " + inputImagePathName
                            + "\n\nOutput Image Path: " + outputImagePathName + "\n\nCrashed results will be missing from output folder but will show up on the results table. Continue Experiment?"
                            , "Process Crash!", MessageBoxButtons.YesNo, MessageBoxIcon.Warning);
                        if (dlg == DialogResult.Yes)
                        {
                            aborted = 2;
                        }
                        else
                        {
                            aborted = 1;
                            Thread.Sleep(5000);
                        }
                    }
                }
                else
                {
                    try
                    {
                        CVIPToolsTestRef.Write_Image(ref inputImage, ref outputImagePathName, (int)CVIPYesNo.CVIP_NO, (int)CVIPYesNo.CVIP_NO, (int)imageFormat.VIP, 0);
                    }
                    catch
                    {
                        if (aborted != 3)
                        {
                            DialogResult dlg = MessageBox.Show("Image Write Corrupted!\n\nCurrent Process: " + algorithm + "\n\nInput Image Path: " + inputImagePathName
                                + "\n\nOutput Image Path: " + outputImagePathName + "\n\nWrite corruption means the image file was not released correctly. \nCVIPtools ATAT" +
                                " must be restarted.", "RESTARTING ATAT - Image Write Corruption!", MessageBoxButtons.OK, MessageBoxIcon.Error);
                            aborted = 3;
                        }
                    }
                    CVIPToolsTestRef.Delete_Image(ref inputImage);
                }
            }
            catch
            {
                if (aborted != 2 && aborted != 3)
                {
                    DialogResult dlg = MessageBox.Show("Process Crashed!\n\nCurrent Process: " + algorithm + "\n\nInput Image Path: " + inputImagePathName
                        + "\n\nOutput Image Path: " + outputImagePathName + "\n\nCrashed results will be missing from output folder but will show up on the results table. Continue Experiment?"
                        , "Process Crash!", MessageBoxButtons.YesNo, MessageBoxIcon.Warning);
                    if (dlg == DialogResult.Yes)
                    {
                        aborted = 2;
                    }
                    else
                    {
                        aborted = 1;
                        Thread.Sleep(5000);
                    }
                }
            }
        }

        //Used for Color Transforms
        public int ColorXform(int image, int cf, ref double norm_vector, ref double white_reference, int direction)
        {
            int dup = 0, ret = 0;

            dup = CVIPToolsTestRef.Duplicate_Image(ref image);
            ret = CVIPToolsTestRef.ColorXform(ref dup, cf, ref norm_vector, ref white_reference, direction);

            CVIPToolsTestRef.Delete_Image(ref dup); // Added as potential memory solution.

            return ret;
        }

        //Saves Database information to List View.
        public void saveDateToListViewTest()
        {
            ListViewItem objListView;

            //empty testResult listView first
            CTestRef.lvTestResult.Items.Clear();

            // all of the data are in the computer memory, so we just deal with virtual table.
            //Count the row's number.
            int rowCount = myDataSet.Tables["dataTestResult"].Rows.Count;
            //read data from certain row and certain column. the first row is marked as 0.
            for (int i = 0; i < rowCount; i++)
            {
                objListView = CTestRef.lvTestResult.Items.Add(myDataSet.Tables["DataTestResult"].Rows[i]["StageOption"].ToString());
                objListView.SubItems.Add(myDataSet.Tables["dataTestResult"].Rows[i]["Algorithm"].ToString());
                objListView.SubItems.Add(myDataSet.Tables["dataTestResult"].Rows[i]["ImageName"].ToString());
                objListView.SubItems.Add(myDataSet.Tables["dataTestResult"].Rows[i]["ImagePath"].ToString());
                objListView.SubItems.Add(myDataSet.Tables["dataTestResult"].Rows[i]["IdealImageName"].ToString());
                objListView.SubItems.Add(myDataSet.Tables["dataTestResult"].Rows[i]["IdealImagePath"].ToString());
                objListView.SubItems.Add(myDataSet.Tables["dataTestResult"].Rows[i]["OriginalImage"].ToString());
            }

            //dispose virtual database and other resource related to database
            myDataSet.Dispose();
            testCon.Dispose();
            myDataTable.Dispose();
            myDataAdapter.Dispose();
            myCommandBuild.Dispose();
        }

        //Allows the Compare to have saved values at the beginning of the test.
        //This avoids the values being changed midway.
        private void getMetrics()
        {
            //Get Error Values
            if (CTestRef.cb_RMS.Checked == true)
            {
                errorValues[0] = Convert.ToDouble(CTestRef.tb_RMSR.Text);
                errorValues[1] = Convert.ToDouble(CTestRef.tb_RMSG.Text);
                errorValues[2] = Convert.ToDouble(CTestRef.tb_RMSB.Text);
            }
            else
            {
                errorValues[0] = -1000;
                errorValues[1] = -1000;
                errorValues[2] = -1000;
            }
            if (CTestRef.cb_SNR.Checked == true)
            {
                errorValues[3] = Convert.ToDouble(CTestRef.tb_SNRR.Text);
                errorValues[4] = Convert.ToDouble(CTestRef.tb_SNRG.Text);
                errorValues[5] = Convert.ToDouble(CTestRef.tb_SNRB.Text);
            }
            else
            {
                errorValues[3] = -1000;
                errorValues[4] = -1000;
                errorValues[5] = -1000;
            }
            if (CTestRef.cb_SubtractEnergy.Checked == true)
            {
                errorValues[6] = Convert.ToDouble(CTestRef.tb_SUBR.Text);
                errorValues[7] = Convert.ToDouble(CTestRef.tb_SUBG.Text);
                errorValues[8] = Convert.ToDouble(CTestRef.tb_SUBB.Text);
            }
            else
            {
                errorValues[6] = -1000;
                errorValues[7] = -1000;
                errorValues[8] = -1000;
            }
            if (CTestRef.cb_DICE.Checked == true)
            {
                errorValues[9] = Convert.ToDouble(CTestRef.tb_DICER.Text);
                errorValues[10] = Convert.ToDouble(CTestRef.tb_DICEG.Text);
                errorValues[11] = Convert.ToDouble(CTestRef.tb_DICEB.Text);
            }
            else
            {
                errorValues[9] = -1000;
                errorValues[10] = -1000;
                errorValues[11] = -1000;
            }
            if (CTestRef.cb_Jaccard.Checked == true)
            {
                errorValues[12] = Convert.ToDouble(CTestRef.tb_JaccR.Text);
                errorValues[13] = Convert.ToDouble(CTestRef.tb_JaccG.Text);
                errorValues[14] = Convert.ToDouble(CTestRef.tb_JaccB.Text);
            }
            else
            {
                errorValues[12] = -1000;
                errorValues[13] = -1000;
                errorValues[14] = -1000;
            }
            if (CTestRef.cb_Over.Checked == true)
            {
                errorValues[15] = Convert.ToDouble(CTestRef.tb_OverR.Text);
                errorValues[16] = Convert.ToDouble(CTestRef.tb_OverG.Text);
                errorValues[17] = Convert.ToDouble(CTestRef.tb_OverB.Text);
            }
            else
            {
                errorValues[15] = -1000;
                errorValues[16] = -1000;
                errorValues[17] = -1000;
            }
            if (CTestRef.cb_XOR.Checked == true)
            {
                errorValues[18] = Convert.ToDouble(CTestRef.tb_XORR.Text);
                errorValues[19] = Convert.ToDouble(CTestRef.tb_XORG.Text);
                errorValues[20] = Convert.ToDouble(CTestRef.tb_XORB.Text);
            }
            else
            {
                errorValues[18] = -1000;
                errorValues[19] = -1000;
                errorValues[20] = -1000;
            }

            //Check if an error is present
            isError = false;
            for (int i = 0; i < errorValues.Length; i++)
            {
                if (errorValues[i] != -1000)
                    isError = true;
            }

            //Determine Error Measures
            if (CTestRef.cb_Average.Checked)
                avgStd[0] = true;
            else
                avgStd[0] = false;
            if (CTestRef.cb_StdDev.Checked)
                avgStd[1] = true;
            else
                avgStd[1] = false;

            //Determine Test Type
            if (CTestRef.rb_FullTest.Checked == true)
            {
                if (isError == true)
                    typeOfTest = 0; //Full Test
                else
                    typeOfTest = 1; //Only Test
            }
            else if (CTestRef.rb_Test.Checked == true)
                typeOfTest = 1; //Only Test
            else
            {
                typeOfTest = 2; //Only Compare
            }

        }
    }
}





