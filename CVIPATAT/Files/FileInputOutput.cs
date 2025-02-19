/***************************************************************************
* =========================================================================
*
*			 CVIP_ATAT - Dr. Scott Umbaugh SIUE
* 
* =========================================================================
*
*             File Name: FileInputOutput.cs 
*           Description: Used to get data from database and store data into data base.
*   Initial Coding Date: June 6,2006
*Last Modification Made: Feb 14, 2020
*  Programming Language: Visual Studio C#.NET 2008, 2017
*             Credit(s): Wenjun(Evan) Bian, Pelin Guvenc, Charles Stacey
*                        Southern Illinois University at Edwardsville
*
*		  Copyright (c): 2010-2011 SIUE - Scott Umbaugh
****************************************************************************/

using System;
using System.IO;
using System.Data;
using System.Data.OleDb;
using System.Windows.Forms;

namespace CVIP_ATAT.Files
{
    class FileInputOutput
    {
        MDIMainForm MDIMainFormRef;

        public FileInputOutput(MDIMainForm reference)  //Get MDIMainForm's reference
        {
            MDIMainFormRef = reference;
        }

        //Need to add a disconnect from the database, this function causes errors.
        public void createDate(string DirectoryName)
        {
            //The Jet Provider requires the path to exist in order to create the new database.
            //Attempting to create a database file in a directory that does not exist will result in 
            //an exception. This exception can be caught using a Try...Catch structure.

            ADOX.Catalog CVIP_ATAT_MDB = new ADOX.Catalog();


            //Delete the old imagelist database. Then create a new one.
            if (File.Exists(DirectoryName + "\\CVIPATAT_Database.mdb"))
                File.Delete(DirectoryName + "\\CVIPATAT_Database.mdb");

            //create database
            CVIP_ATAT_MDB.Create("Provider=Microsoft.Jet.OLEDB.4.0;" +
                       "Data Source=" + DirectoryName + "\\CVIPATAT_Database.mdb");

            //connect to database
            ADODB.Connection conADO = new ADODB.Connection();
            object obj = new object();

            //open database
            conADO.Open("Provider=Microsoft.Jet.OLEDB.4.0;" +
                     "Data Source=" + DirectoryName + "\\CVIPATAT_Database.mdb", null, null, 0);

            //Create Datatables
            //notes: some name can not be given to table, such as 'image'. maybe it conflict with the keywords
            string[] tableCreate ={
                                    "CREATE TABLE Images",
                                    "CREATE TABLE Processes",
                                    "CREATE TABLE TestResult"
                               };

            for (int i = 0; i < tableCreate.Length; i++)
            {
                conADO.Execute(tableCreate[i], out obj, 0);
            }


            // Add Columns for Images Table
            string[] columnImageListAdd = {
            "ALTER TABLE Images ADD COLUMN ImageName string;",
            "ALTER TABLE Images ADD COLUMN ImagePath string;",
            "ALTER TABLE Images ADD COLUMN IdealImageName string;",
            "ALTER TABLE Images ADD COLUMN IdealImagePath string;",
            "ALTER TABLE Images ADD COLUMN ImageCount string;"};

            for (int i = 0; i < columnImageListAdd.Length; i++)
            {
                conADO.Execute(columnImageListAdd[i], out obj, 0);
            }

            //Add columns for processes table
            string[] columnProcessesAdd ={
            "ALTER TABLE Processes ADD COLUMN Stages string;",
            "ALTER TABLE Processes ADD COLUMN Options string;",
            "ALTER TABLE Processes ADD COLUMN Processes string;",
            "ALTER TABLE Processes ADD COLUMN P1 string;",
            "ALTER TABLE Processes ADD COLUMN P2 string;",
            "ALTER TABLE Processes ADD COLUMN P3 string;",
            "ALTER TABLE Processes ADD COLUMN OneImageTotalOption string;"
        };

            for (int i = 0; i < columnProcessesAdd.Length; i++)
            {
                conADO.Execute(columnProcessesAdd[i], out obj, 0);
            }

            //Add columns for TestResult table
            string[] columnTestResultAdd ={
            "ALTER TABLE TestResult ADD COLUMN StageOption string;",
            "ALTER TABLE TestResult ADD COLUMN Algorithm string;",
            "ALTER TABLE TestResult ADD COLUMN ImageName string;",
            "ALTER TABLE TestResult ADD COLUMN ImagePath string;",
            "ALTER TABLE TestResult ADD COLUMN IdealImageName string;",
            "ALTER TABLE TestResult ADD COLUMN IdealImagePath string;",
            "ALTER TABLE TestResult ADD COLUMN OriginalImage string;" 
            };

            for (int i = 0; i < columnTestResultAdd.Length; i++)
            {
                conADO.Execute(columnTestResultAdd[i], out obj, 0);
            }

            conADO.Close();
        }

        public void saveImageList(string DirectoryName, CVIPATATForm CVIPATATRef)
        {
            string strAccessConn = "Provider=Microsoft.JET.OLEDB.4.0;" +
                                   "Data Source=" + DirectoryName + "\\CVIPATAT_Database.mdb";
            string strAccessSelect = "Select * from Images"; //select the table

            OleDbConnection mConnection = new OleDbConnection(strAccessConn);
            OleDbDataAdapter myDataAdapter = new OleDbDataAdapter();
            OleDbCommandBuilder myCommandBuild = new OleDbCommandBuilder(myDataAdapter);

            myDataAdapter.SelectCommand = new OleDbCommand(strAccessSelect, mConnection);
            mConnection.Open();

            //Create a DataTable with the name of the table in the database.
            //Create a DataSet including the DataTable.
            DataSet myDataSet = new DataSet();
            DataTable myDataTable = new DataTable();
            myDataSet.Tables.Add(myDataTable);

            //open the table ."Images" is the name of source table to map from; 
            //                "DataImages" is the name of  is dataset table to map to
            myDataAdapter.TableMappings.Add("Images", "dataImages");


            //load current data into the local table copy 
            myDataAdapter.Fill(myDataSet, "Images");


            //Add images into database.
            for (int i = 0; i < CVIPATATRef.lvImage.Items.Count; i++)
            {
                DataRow newRow = myDataSet.Tables["dataImages"].NewRow();

                if (i == 0)
                {
                    newRow["ImageName"] = CVIPATATRef.lvImage.Items[i].SubItems[0].Text;
                    newRow["ImagePath"] = CVIPATATRef.lvImage.Items[i].SubItems[1].Text;
                    newRow["IdealImageName"] = CVIPATATRef.lvImage.Items[i].SubItems[2].Text;
                    newRow["IdealImagePath"] = CVIPATATRef.lvImage.Items[i].SubItems[3].Text;
                    newRow["ImageCount"] = CVIPATATRef.tbImageCount.Text;
                }
                else
                {
                    newRow["ImageName"] = CVIPATATRef.lvImage.Items[i].SubItems[0].Text;
                    newRow["ImagePath"] = CVIPATATRef.lvImage.Items[i].SubItems[1].Text;
                    newRow["IdealImageName"] = CVIPATATRef.lvImage.Items[i].SubItems[2].Text;
                    newRow["IdealImagePath"] = CVIPATATRef.lvImage.Items[i].SubItems[3].Text;
                }

                myDataSet.Tables["dataImages"].Rows.Add(newRow);
            }
            //update one whole row, no matter whether all the colmuns has been given values. 
            myDataAdapter.Update(myDataSet.Tables["dataImages"]);

            //close database
            mConnection.Close();

            //dispose resource
            mConnection.Dispose();
            myDataAdapter.Dispose();
            myCommandBuild.Dispose();
            myDataTable.Dispose();
            myDataSet.Dispose();
            GC.Collect();
        }

        public void readImageList(string DirectoryName, CVIPATATForm CVIPATATRef)
        {
            ListViewItem objListView;

            string strAccessConn = "Provider=Microsoft.JET.OLEDB.4.0;" +
            "Data Source=" + DirectoryName + "\\CVIPATAT_Database.mdb";
            string strAccessSelect = "Select * from Images";

            OleDbConnection mConnection = new OleDbConnection(strAccessConn);
            OleDbDataAdapter myDataAdapter = new OleDbDataAdapter();
            OleDbCommandBuilder myCommandBuild = new OleDbCommandBuilder(myDataAdapter);

            myDataAdapter.SelectCommand = new OleDbCommand(strAccessSelect, mConnection);
            mConnection.Open();

            //Create a DataTable with the name of the table in the database.
            //Create a DataSet including the DataTable.
            DataSet myDataSet = new DataSet();
            DataTable myDataTable = new DataTable();
            myDataSet.Tables.Add(myDataTable);

            //open the table ."ImageList" is the name of source table to map from; 
            //                "DataImageList" is the name of  is dataset table to map to
            myDataAdapter.TableMappings.Add("Images", "dataImages");

            //load current data into the local table copy 
            myDataAdapter.Fill(myDataSet, "Images");

            // all of the data are in the computer memory, so we just deal with virtual table.
            //Count the row's number.
            int rowCount = myDataSet.Tables["dataImages"].Rows.Count;
            //read data from certain row and certain column. the first row is marked as 0.
            for (int i = 0; i < rowCount; i++)
            {
                if (i == 0)
                {
                    CVIPATATRef.tbImageCount.Text = myDataSet.Tables["dataImages"].Rows[i]["ImageCount"].ToString();
                }

                objListView = CVIPATATRef.lvImage.Items.Add(myDataSet.Tables["dataImages"].Rows[i]["ImageName"].ToString());
                objListView.SubItems.Add(myDataSet.Tables["dataImages"].Rows[i]["ImagePath"].ToString());
                objListView.SubItems.Add(myDataSet.Tables["dataImages"].Rows[i]["IdealImageName"].ToString());
                objListView.SubItems.Add(myDataSet.Tables["dataImages"].Rows[i]["IdealImagePath"].ToString());
            }

            //close database
            mConnection.Close();

            //dispose resource
            mConnection.Dispose();
            myDataAdapter.Dispose();
            myCommandBuild.Dispose();
            myDataTable.Dispose();
            myDataSet.Dispose();
            GC.Collect();
        }

        public void saveProcess(string DirectoryName, CVIPATATForm CVIPATATRef)
        {
            string strAccessConn = "Provider=Microsoft.JET.OLEDB.4.0;" +
                       "Data Source=" + DirectoryName + "\\CVIPATAT_Database.mdb";
            string strAccessSelect = "Select * from Processes"; //select the table

            OleDbConnection mConnection = new OleDbConnection(strAccessConn);
            OleDbDataAdapter myDataAdapter = new OleDbDataAdapter();
            OleDbCommandBuilder myCommandBuild = new OleDbCommandBuilder(myDataAdapter);

            myDataAdapter.SelectCommand = new OleDbCommand(strAccessSelect, mConnection);
            mConnection.Open();

            //Create a DataTable with the name of the table in the database.
            //Create a DataSet including the DataTable.
            DataSet myDataSet = new DataSet();
            DataTable myDataTable = new DataTable();
            myDataSet.Tables.Add(myDataTable);

            //open the table ."Processes" is the name of source table to map from; 
            //                "DataProcesses" is the name of  is dataset table to map to
            myDataAdapter.TableMappings.Add("Processes", "dataProcesses");


            //load current data into the local table copy 
            myDataAdapter.Fill(myDataSet, "Processes");


            //Add images into database.
            for (int i = 0; i < CVIPATATRef.lvProcess.Items.Count; i++)
            {
                DataRow newRow = myDataSet.Tables["dataProcesses"].NewRow();

                if (i == 0)
                {
                    newRow["Stages"] = CVIPATATRef.lvProcess.Items[i].SubItems[0].Text;
                    newRow["Options"] = CVIPATATRef.lvProcess.Items[i].SubItems[1].Text;
                    newRow["Processes"] = CVIPATATRef.lvProcess.Items[i].SubItems[2].Text;
                    newRow["P1"] = CVIPATATRef.lvProcess.Items[i].SubItems[3].Text;
                    newRow["P2"] = CVIPATATRef.lvProcess.Items[i].SubItems[4].Text;
                    newRow["P3"] = CVIPATATRef.lvProcess.Items[i].SubItems[5].Text;
                    newRow["OneImageTotalOption"] = CVIPATATRef.tbTotalOptionsImage.Text;
                }
                else
                {
                    newRow["Stages"] = CVIPATATRef.lvProcess.Items[i].SubItems[0].Text;
                    newRow["Options"] = CVIPATATRef.lvProcess.Items[i].SubItems[1].Text;
                    newRow["Processes"] = CVIPATATRef.lvProcess.Items[i].SubItems[2].Text;
                    newRow["P1"] = CVIPATATRef.lvProcess.Items[i].SubItems[3].Text;
                    newRow["P2"] = CVIPATATRef.lvProcess.Items[i].SubItems[4].Text;
                    newRow["P3"] = CVIPATATRef.lvProcess.Items[i].SubItems[5].Text;

                }

                myDataSet.Tables["dataProcesses"].Rows.Add(newRow);

            }

            //update one whole row, no matter whether all the colmuns has been given values. 
            myDataAdapter.Update(myDataSet.Tables["dataProcesses"]);

            //close database
            mConnection.Close();

            //dispose resource
            mConnection.Dispose();
            myDataAdapter.Dispose();
            myCommandBuild.Dispose();
            myDataTable.Dispose();
            myDataSet.Dispose();
            GC.Collect();
        }

        public void readProcess(string DirectoryName, CVIPATATForm CVIPATATRef)
        {
            ListViewItem objListView;

            string strAccessConn = "Provider=Microsoft.JET.OLEDB.4.0;" +
            "Data Source=" + DirectoryName + "\\CVIPATAT_Database.mdb";
            string strAccessSelect = "Select * from Processes";

            OleDbConnection mConnection = new OleDbConnection(strAccessConn);
            OleDbDataAdapter myDataAdapter = new OleDbDataAdapter();
            OleDbCommandBuilder myCommandBuild = new OleDbCommandBuilder(myDataAdapter);

            myDataAdapter.SelectCommand = new OleDbCommand(strAccessSelect, mConnection);
            mConnection.Open();

            //Create a DataTable with the name of the table in the database.
            //Create a DataSet including the DataTable.
            DataSet myDataSet = new DataSet();
            DataTable myDataTable = new DataTable();
            myDataSet.Tables.Add(myDataTable);

            //open the table ."Processes" is the name of source table to map from; 
            //                "DataProcesses" is the name of  is dataset table to map to
            myDataAdapter.TableMappings.Add("Processes", "dataProcesses");

            //load current data into the local table copy 
            myDataAdapter.Fill(myDataSet, "Processes");


            // all of the data are in the computer memory, so we just deal with virtual table.
            //Count the row's number.
            int rowCount = myDataSet.Tables["dataProcesses"].Rows.Count;
            //read data from certain row and certain column. the first row is marked as 0.
            for (int i = 0; i < rowCount; i++)
            {
                if (i == 0)
                {
                    CVIPATATRef.tbTotalOptionsImage.Text = myDataSet.Tables["dataProcesses"].Rows[i]["OneImageTotalOption"].ToString();
                }

                objListView = CVIPATATRef.lvProcess.Items.Add(myDataSet.Tables["dataProcesses"].Rows[i]["Stages"].ToString());
                objListView.SubItems.Add(myDataSet.Tables["dataProcesses"].Rows[i]["Options"].ToString());
                objListView.SubItems.Add(myDataSet.Tables["dataProcesses"].Rows[i]["Processes"].ToString());
                objListView.SubItems.Add(myDataSet.Tables["dataProcesses"].Rows[i]["P1"].ToString());
                objListView.SubItems.Add(myDataSet.Tables["dataProcesses"].Rows[i]["P2"].ToString());
                objListView.SubItems.Add(myDataSet.Tables["dataProcesses"].Rows[i]["P3"].ToString());
            }

            //close database
            mConnection.Close();

            //dispose resource
            mConnection.Dispose();
            myDataAdapter.Dispose();
            myCommandBuild.Dispose();
            myDataTable.Dispose();
            myDataSet.Dispose();
            GC.Collect();

            //calculate the option of every stage
            if (CVIPATATRef.lvProcess.Items.Count != 0)
            {
                int itemIndex;
                int stageMax = Convert.ToInt16(CVIPATATRef.lvProcess.Items[CVIPATATRef.lvProcess.Items.Count - 1].SubItems[0].Text);
                for (int i = 0; i < stageMax; i++)
                {
                    //get the index(initial address) of the selected stage 
                    itemIndex = -1;

                    for (int j = 0; j < CVIPATATRef.lvProcess.Items.Count; j++)
                    {
                        if (Convert.ToInt16(CVIPATATRef.lvProcess.Items[j].SubItems[0].Text) == (i + 1))
                        {
                            if (itemIndex == -1)
                            {
                                Processes.optionInOneStageCount[i] = 0;
                                itemIndex = CVIPATATRef.lvProcess.Items[j].Index;
                            }
                            //get the number of option within the same stage
                            Processes.optionInOneStageCount[i]++;

                        }
                    }

                }
            }
            else
            { }

        }

        public void saveTestResult(string DirectoryName, CVIPATATForm CVIPATATRef)
        {
            string strAccessConn = "Provider=Microsoft.JET.OLEDB.4.0;" +
           "Data Source=" + DirectoryName + "\\CVIPATAT_Database.mdb";
            string strAccessSelect = "Select * from TestResult"; //select the table

            OleDbConnection mConnection = new OleDbConnection(strAccessConn);
            OleDbDataAdapter myDataAdapter = new OleDbDataAdapter();
            OleDbCommandBuilder myCommandBuild = new OleDbCommandBuilder(myDataAdapter);

            myDataAdapter.SelectCommand = new OleDbCommand(strAccessSelect, mConnection);
            mConnection.Open();

            //Create a DataTable with the name of the table in the database.
            //Create a DataSet including the DataTable.
            DataSet myDataSet = new DataSet();
            DataTable myDataTable = new DataTable();
            myDataSet.Tables.Add(myDataTable);

            //open the table ."TestResult" is the name of source table to map from; 
            //                "DataTestResult" is the name of  is dataset table to map to
            myDataAdapter.TableMappings.Add("TestResult", "dataTestResult");


            //load current data into the local table copy 
            myDataAdapter.Fill(myDataSet, "TestResult");


            //Add images into database.
            for (int i = 0; i < CVIPATATRef.lvTestResult.Items.Count; i++)
            {
                DataRow newRow = myDataSet.Tables["dataTestResult"].NewRow();

                newRow["StageOption"] = CVIPATATRef.lvTestResult.Items[i].SubItems[0].Text;
                newRow["Algorithm"] = CVIPATATRef.lvTestResult.Items[i].SubItems[1].Text;
                newRow["ImageName"] = CVIPATATRef.lvTestResult.Items[i].SubItems[2].Text;
                newRow["ImagePath"] = CVIPATATRef.lvTestResult.Items[i].SubItems[3].Text;
                newRow["IdealImageName"] = CVIPATATRef.lvTestResult.Items[i].SubItems[4].Text;
                newRow["IdealImagePath"] = CVIPATATRef.lvTestResult.Items[i].SubItems[5].Text;
                newRow["OriginalImage"] = CVIPATATRef.lvTestResult.Items[i].SubItems[6].Text;

                myDataSet.Tables["dataTestResult"].Rows.Add(newRow);
            }

            //update one whole row, no matter whether all the colmuns has been given values. 
            myDataAdapter.Update(myDataSet.Tables["dataTestResult"]);

            //close database
            mConnection.Close();

            //dispose resource
            mConnection.Dispose();
            myDataAdapter.Dispose();
            myCommandBuild.Dispose();
            myDataTable.Dispose();
            myDataSet.Dispose();
            GC.Collect();

        }

        public void readTestResult(string DirectoryName, CVIPATATForm CVIPATATRef)
        {
            ListViewItem objListView;

            string strAccessConn = "Provider=Microsoft.JET.OLEDB.4.0;" +
            "Data Source=" + DirectoryName + "\\CVIPATAT_Database.mdb";
            string strAccessSelect = "Select * from TestResult";

            OleDbConnection mConnection = new OleDbConnection(strAccessConn);
            OleDbDataAdapter myDataAdapter = new OleDbDataAdapter();
            OleDbCommandBuilder myCommandBuild = new OleDbCommandBuilder(myDataAdapter);

            myDataAdapter.SelectCommand = new OleDbCommand(strAccessSelect, mConnection);
            mConnection.Open();

            //Create a DataTable with the name of the table in the database.
            //Create a DataSet including the DataTable.
            DataSet myDataSet = new DataSet();
            DataTable myDataTable = new DataTable();
            myDataSet.Tables.Add(myDataTable);

            //open the table ."TestResult" is the name of source table to map from; 
            //                "DataTestResult" is the name of  is dataset table to map to
            myDataAdapter.TableMappings.Add("TestResult", "dataTestResult");

            //load current data into the local table copy 
            myDataAdapter.Fill(myDataSet, "TestResult");


            // all of the data are in the computer memory, so we just deal with virtual table.
            //Count the row's number.
            int rowCount = myDataSet.Tables["dataTestResult"].Rows.Count;
            //read data from certain row and certain column. the first row is marked as 0.
            for (int i = 0; i < rowCount; i++)
            {
                objListView = CVIPATATRef.lvTestResult.Items.Add(myDataSet.Tables["dataTestResult"].Rows[i]["StageOption"].ToString());
                objListView.SubItems.Add(myDataSet.Tables["dataTestResult"].Rows[i]["Algorithm"].ToString());
                objListView.SubItems.Add(myDataSet.Tables["dataTestResult"].Rows[i]["ImageName"].ToString());
                objListView.SubItems.Add(myDataSet.Tables["dataTestResult"].Rows[i]["ImagePath"].ToString());
                objListView.SubItems.Add(myDataSet.Tables["dataTestResult"].Rows[i]["IdealImageName"].ToString());
                objListView.SubItems.Add(myDataSet.Tables["dataTestResult"].Rows[i]["IdealImagePath"].ToString());
                objListView.SubItems.Add(myDataSet.Tables["dataTestResult"].Rows[i]["OriginalImage"].ToString());
            }

            //close database
            mConnection.Close();

            //dispose resource
            mConnection.Dispose();
            myDataAdapter.Dispose();
            myCommandBuild.Dispose();
            myDataTable.Dispose();
            myDataSet.Dispose();
            GC.Collect();


        }

        public void saveUserSettings(string filename, CVIPATATForm CVIPATATRef)
        {
            StreamWriter sw = new StreamWriter(filename);
            string[] options = new string[38];

            //This part was added before and kept in. It determines if the user affirmed the save.
            sw.WriteLine("AskBeforeExit Sign");   //write a line and carriage return
            if (MDIMainFormRef.mnuAskBeforeExit.Checked == true)
                sw.WriteLine("1");                  //write a character with carriage return
            else
                sw.WriteLine("0");

            //Save Comparison Checkboxes
            options[0] = CVIPATATRef.cb_RMS.Checked ? "1" : "0";
            options[1] = CVIPATATRef.cb_SNR.Checked ? "1" : "0";
            options[2] = CVIPATATRef.cb_SubtractEnergy.Checked ? "1" : "0";
            options[3] = CVIPATATRef.cb_DICE.Checked ? "1" : "0";
            options[4] = CVIPATATRef.cb_Jaccard.Checked ? "1" : "0";
            options[5] = CVIPATATRef.cb_Over.Checked ? "1" : "0";
            options[6] = CVIPATATRef.cb_XOR.Checked ? "1" : "0";
            options[7] = CVIPATATRef.cb_Average.Checked ? "1" : "0";
            options[8] = CVIPATATRef.cb_StdDev.Checked ? "1" : "0";
            options[9] = CVIPATATRef.cbSelectAll.Checked ? "1" : "0";

            //Save Comparison Textboxes
            options[10] = CVIPATATRef.tb_RMSR.Text;
            options[11] = CVIPATATRef.tb_RMSG.Text;
            options[12] = CVIPATATRef.tb_RMSB.Text;
            options[13] = CVIPATATRef.tb_SNRR.Text;
            options[14] = CVIPATATRef.tb_SNRG.Text;
            options[15] = CVIPATATRef.tb_SNRB.Text;
            options[16] = CVIPATATRef.tb_SUBR.Text;
            options[17] = CVIPATATRef.tb_SUBG.Text;
            options[18] = CVIPATATRef.tb_SUBB.Text;
            options[19] = CVIPATATRef.tb_DICER.Text;
            options[20] = CVIPATATRef.tb_DICEG.Text;
            options[21] = CVIPATATRef.tb_DICEB.Text;
            options[22] = CVIPATATRef.tb_JaccR.Text;
            options[23] = CVIPATATRef.tb_JaccG.Text;
            options[24] = CVIPATATRef.tb_JaccB.Text;
            options[25] = CVIPATATRef.tb_OverR.Text;
            options[26] = CVIPATATRef.tb_OverG.Text;
            options[27] = CVIPATATRef.tb_OverB.Text;
            options[28] = CVIPATATRef.tb_XORR.Text;
            options[29] = CVIPATATRef.tb_XORG.Text;
            options[30] = CVIPATATRef.tb_XORB.Text;
            options[31] = CVIPATATRef.tb_Thresh.Text;

            //Save Testing RadioButtons
            options[32] = CVIPATATRef.rb_FullTest.Checked ? "1" : "0";
            options[33] = CVIPATATRef.rb_Test.Checked ? "1" : "0";
            options[34] = CVIPATATRef.rb_Compare.Checked ? "1" : "0";

            //Save Testing Textboxes
            options[35] = CVIPATATRef.tb_TestDir.Text;
            options[36] = CVIPATATRef.tb_IdealDir.Text;
            options[37] = CVIPATATRef.tbAlg.Text;

            //Write User Settings
            for (int settingNumber = 0; settingNumber < 38; settingNumber++)
            {
                sw.WriteLine(options[settingNumber]);
            }

            //Close File Writer
            sw.Close();
            sw.Dispose();
        }

        public void readUserSettings(string filename, CVIPATATForm CVIPATATRef)
        {
            StreamReader sr = new StreamReader(filename);
            string[] options = new string[38];

            sr.ReadLine();

            //read in character(in ASCII) and return a integral value.
            //      chr 0:  int value 48;  chr 1: int value 49;
            if (sr.ReadLine() == "0") MDIMainFormRef.mnuAskBeforeExit.Checked = false;
            else
                MDIMainFormRef.mnuAskBeforeExit.Checked = true;

            //Read User Settings
            for (int settingNumber = 0; settingNumber < 38; settingNumber++)
            {
                options[settingNumber] = sr.ReadLine();
            }

            //Read Comparison Checkboxes
            CVIPATATRef.cb_RMS.Checked = (options[0] == "1") ? true : false;
            CVIPATATRef.cb_SNR.Checked = (options[1] == "1") ? true : false;
            CVIPATATRef.cb_SubtractEnergy.Checked = (options[2] == "1") ? true : false;
            CVIPATATRef.cb_DICE.Checked = (options[3] == "1") ? true : false;
            CVIPATATRef.cb_Jaccard.Checked = (options[4] == "1") ? true : false;
            CVIPATATRef.cb_Over.Checked = (options[5] == "1") ? true : false;
            CVIPATATRef.cb_XOR.Checked = (options[6] == "1") ? true : false;
            CVIPATATRef.cb_Average.Checked = (options[7] == "1") ? true : false;
            CVIPATATRef.cb_StdDev.Checked = (options[8] == "1") ? true : false;
            CVIPATATRef.cbSelectAll.Checked = (options[9] == "1") ? true : false;


            //Read Comparison Textboxes
            CVIPATATRef.tb_RMSR.Text = options[10];
            CVIPATATRef.tb_RMSG.Text = options[11];
            CVIPATATRef.tb_RMSB.Text = options[12];
            CVIPATATRef.tb_SNRR.Text = options[13];
            CVIPATATRef.tb_SNRG.Text = options[14];
            CVIPATATRef.tb_SNRB.Text = options[15];
            CVIPATATRef.tb_SUBR.Text = options[16];
            CVIPATATRef.tb_SUBG.Text = options[17];
            CVIPATATRef.tb_SUBB.Text = options[18];
            CVIPATATRef.tb_DICER.Text = options[19];
            CVIPATATRef.tb_DICEG.Text = options[20];
            CVIPATATRef.tb_DICEB.Text = options[21];
            CVIPATATRef.tb_JaccR.Text = options[22];
            CVIPATATRef.tb_JaccG.Text = options[23];
            CVIPATATRef.tb_JaccB.Text = options[24];
            CVIPATATRef.tb_OverR.Text = options[25];
            CVIPATATRef.tb_OverG.Text = options[26];
            CVIPATATRef.tb_OverB.Text = options[27];
            CVIPATATRef.tb_XORR.Text = options[28];
            CVIPATATRef.tb_XORG.Text = options[29];
            CVIPATATRef.tb_XORB.Text = options[30];
            CVIPATATRef.tb_Thresh.Text = options[31];

            //Read Testing RadioButtons
            CVIPATATRef.rb_FullTest.Checked = (options[32] == "1") ? true : false;
            CVIPATATRef.rb_Test.Checked = (options[33] == "1") ? true : false;
            CVIPATATRef.rb_Compare.Checked = (options[34] == "1") ? true : false;

            //Read Testing Textboxes
            CVIPATATRef.tb_TestDir.Text = options[35];
            CVIPATATRef.tb_IdealDir.Text = options[36];
            CVIPATATRef.tbAlg.Text = options[37];

            //Close File Writer
            sr.Close();
            sr.Dispose();
        }
    }
}

//// Reference:   http://www.functionx.com/vcsharp/ado/Lesson02.htm