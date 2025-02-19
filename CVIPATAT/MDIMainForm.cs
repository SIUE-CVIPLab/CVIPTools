/***************************************************************************
* =========================================================================
*
*			 CVIP_ATAT - Dr. Scott Umbaugh SIUE
* 
* =========================================================================
*
*             File Name: MDIMainForm.cs 
*           Description: Parent Form for create, open, close and save project.
*   Initial Coding Date: June 6, 2006
*Last Modification Made: Feb 14, 2020
*  Programming Language: Visual Studio C#.NET 2008, 2017 
*             Credit(s): Wenjun(Evan) Bian, Pelin Guvenc, Charles Stacey
*                        Southern Illinois University at Edwardsville
*
*		  Copyright (c): 2010-2011 SIUE - Scott Umbaugh
****************************************************************************/
using Microsoft.Win32;
using System;
using System.Windows.Forms;
using CVIP_ATAT.Files;
using System.IO;
using SERVERLib;

namespace CVIP_ATAT
{
    public partial class MDIMainForm : Form
    {
        public CVIPTools mainCVIPTool = new CVIPTools();
        CVIPATATForm CVIPATATInUse, CVIPATA_Open,CVIPATA_New;
        public NewProject newProject;
        public FileInfo myOpenProject;
        FileInputOutput fileInOut;
        
        public int  CVIPATATFormCloseSign = 0; //a sign for MDIMainForm to close or not
        public int CVIPATA_Open_Sign = 0;
        public int CVIPATA_New_Sign = 0;
        public int runTestFinishSign = 0;
        public string newProjectPath="0";
        public string fileDialogCurrent;

        public MDIMainForm()
        {
            InitializeComponent();           
        }

        private void MDIMainForm_Load(object sender, EventArgs e)
        {
            fileInOut = new FileInputOutput(this);
        }

        private void MDIMainForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (mnuAskBeforeExit.Checked)
            {
                if (CVIPATATFormCloseSign == 1)
                    e.Cancel = true;     //we will not close CVIPATATForm, so we will not close MDIMainForm too.
                else
                {
                    if (MessageBox.Show("Are you sure you want to exit CVIPATAT?", "CVIPATAT Confirm Exit",
                        MessageBoxButtons.YesNo, MessageBoxIcon.Question) == DialogResult.No)
                        e.Cancel = true;
                    else e.Cancel = false;
                }
            }
        }

        private void exitToolStripMenuItem_Click(object sender, EventArgs e)
        {         
            if (mnuAskBeforeExit.Checked)
            {
                if (MessageBox.Show("Are you sure you want to exit CVIPATAT?", "CVIPATAT Confirm Exit",
                    MessageBoxButtons.YesNo, MessageBoxIcon.Question) == DialogResult.No)
                    return;      
            }
            this.Dispose();
            Application.Exit(); 
       }

        public void endProgram()
        {            
            this.Dispose();
            Application.Exit();
        }

        private void mnuAskBeforeExit_Click(object sender, EventArgs e)
        {
            mnuAskBeforeExit.Checked = (!mnuAskBeforeExit.Checked);
        }

        private void aboutCVIPATATToolStripMenuItem_Click(object sender, EventArgs e)
        {
            AboutCVIPATAT about_CVIPATAT = new AboutCVIPATAT();
            about_CVIPATAT.ShowDialog();
        }

        private void mnuNewProject_Click(object sender, EventArgs e)
        {
            newProject = new NewProject(this);
            newProject.ShowDialog ();
            if (newProjectPath=="0")
            { }
            else
            {
                CVIPATA_New_Sign = 1;
                CVIPATA_Open_Sign = 0;

                mnuCloseProject.Enabled = true;
                mnuSaveProject.Enabled = true;
                mnuOpenProject.Enabled = false;
                mnuNewProject.Enabled = false;

                CVIPATA_New = new CVIPATATForm(this, newProjectPath);
                CVIPATATInUse = CVIPATA_New; //Get the CVIPATAT reference
                CVIPATA_New.MdiParent = this;
                CVIPATA_New.Show();

                //Create database
                fileInOut.createDate(CVIPATA_New.CVIP_projectPath);
            }
        }

        private void mnuOpenProject_Click(object sender, EventArgs e)
        {
            CVIPATA_New_Sign = 0;
            CVIPATA_Open_Sign = 1;

            openProject.Title = "Open Project.";
            openProject.Filter = "CVIPATAT Config Files(*.cfg)|*.cfg"; 
            openProject.FilterIndex = 1;
            openProject.FileName = "CVIPConfig.cfg";

            if (openProject.ShowDialog() != DialogResult.Cancel)
            {

                myOpenProject = new FileInfo(openProject.FileName);
                string aa = myOpenProject.FullName;

                if (myOpenProject.FullName==myOpenProject.DirectoryName + "\\CVIPConfig.cfg")
                {
                    mnuCloseProject.Enabled = true;
                    mnuSaveProject.Enabled = true;
                    mnuOpenProject.Enabled = false;
                    mnuNewProject.Enabled = false;

                    //CVIPATATForm CVIPATA_Open = new CVIPATATForm(this);
                    CVIPATA_Open = new CVIPATATForm(this, myOpenProject.DirectoryName);
                    CVIPATATInUse = CVIPATA_Open; //Get the CVIPATAT reference
                    CVIPATA_Open.MdiParent = this;
                    CVIPATA_Open.Show();

                    //read tool config
                    //fileInOut.readToolConfig(openProject.FileName);
                    fileInOut.readUserSettings(openProject.FileName, CVIPATA_Open);
                    CVIPATA_Open.repairCompare();

                    //read images list
                    fileInOut.readImageList(myOpenProject.DirectoryName, CVIPATA_Open);

                    //read process list
                    fileInOut.readProcess(myOpenProject.DirectoryName, CVIPATA_Open);

                    //read test result
                    fileInOut.readTestResult(myOpenProject.DirectoryName, CVIPATA_Open);
                }
                else
                {
                    MessageBox.Show("We just can open CVIPConfig.cfg file. Please check the file and directory.", "Open file error",
                        MessageBoxButtons.OK , MessageBoxIcon.Warning );
                }
            }
            else
            {
                mnuCloseProject.Enabled = false;
                mnuSaveProject.Enabled = false;
                mnuOpenProject.Enabled = true;
                mnuNewProject.Enabled = true;
            }    
        }

        private void mnuSaveProject_Click(object sender, EventArgs e)
        {
            savenow();
        }

        public void savenow()
        {
            //create a new file to save tool's config
            //After a file is created, it is open. if we donot close it now, we may meet problem to open it next time.
            try
            {
                if (File.Exists(CVIPATATInUse.CVIP_projectPath + "\\CVIPConfig.cfg"))
                {
                    File.Delete(CVIPATATInUse.CVIP_projectPath + "\\CVIPConfig.cfg");
                }
                File.Create(CVIPATATInUse.CVIP_projectPath + "\\CVIPConfig.cfg").Close();

                //create a new database to save data
                fileInOut.createDate(CVIPATATInUse.CVIP_projectPath);

                //save Tool's config
                fileInOut.saveUserSettings(CVIPATATInUse.CVIP_projectPath + "\\CVIPConfig.cfg", CVIPATATInUse);

                //save images list
                fileInOut.saveImageList(CVIPATATInUse.CVIP_projectPath, CVIPATATInUse);

                //save processes list
                fileInOut.saveProcess(CVIPATATInUse.CVIP_projectPath, CVIPATATInUse);

                //save test result
                fileInOut.saveTestResult(CVIPATATInUse.CVIP_projectPath, CVIPATATInUse);
            }
            catch
            {
                MessageBox.Show("Project files unsuccessfully saved.", "Project Save Error!", MessageBoxButtons.OK, MessageBoxIcon.Warning);
            }
        }

        private void mnuClose_Click(object sender, EventArgs e)
        {   
            //this could cause an exception that can be caught using a Try...Catch structure.
            try
            {
                CVIPATATInUse.BringToFront();
                if (this.ActiveMdiChild.Name == "CVIPATATForm")
                {
                    //this will trigger event: CVIPATATForm_FormClosing(object sender, FormClosingEventArgs e)
                    CVIPATATForm CloseProject = (CVIPATATForm)this.ActiveMdiChild;
                    CloseProject.Close();
                }
            }
            catch
            { }
        }

        private void tbOpen_Click(object sender, EventArgs e)
        {
            imageView viewImage;
            fileDialog.Title = "Add Images";
            fileDialog.Filter =
                "All Image Files|*.vip; *.jpeg; *.jpg; *.gif; *.bmp; *.pbm; *.pgm; *.ppm; *tif" +
                "|Bitmap Files (*.bmp)|*.bmp" +
                "|CVIPtools VIP Format (*.vip)|*.vip|Graphic Interchange Format (*.gif)|*.gif" +
                "|JPEG File Interchange Format (*.jpg, *.jpeg)|*.jpg; *.jpeg" +
                "|Tagged Image File Format (*.tif, *.tiff)|*.tif; *.tiff" +
                "|Portable Image File Format (*.pbm, *.pgm, *.ppm)|*.pbm; *.pgm; *.ppm";
            fileDialog.FilterIndex = 1;
            fileDialog.Multiselect = true;
            //fileDialog.InitialDirectory = fileDialogCurrent;
            if (fileDialog.ShowDialog() == DialogResult.OK)
            {
                fileDialog.InitialDirectory = Path.GetDirectoryName(fileDialog.FileName);
                int imageCount = fileDialog.FileNames.Length;
                for (int i = 0; i < imageCount; i++)
                {
                    if (File.Exists(fileDialog.FileNames[i]))
                    {
                        viewImage = new imageView(this, fileDialog.FileNames[i]);
                        viewImage.MdiParent = this;
                        viewImage.Show();
                    }
                    else
                    {
                        MessageBox.Show("Image File Not Found.", "File Not Found.", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    }
                }
            }
        }

        static public string CVIPtoolsHOME
        {
            get
            {
                string envKey = @"HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Control\Session Manager\Environment";
                return (string)Registry.GetValue(envKey, "CVIPtoolsHOME", null);
            }
        }

        private void contenToolStripMenuItem_Click(object sender, EventArgs e)
        {
            string cvipHome = @"HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Control\Session Manager\Environment";
            cvipHome = (string)Registry.GetValue(cvipHome, "CVIPtoolsHOME", null);
            if (string.IsNullOrEmpty(cvipHome))
            {
                MessageBox.Show("Can't find the ATAT help file. The CVIPtoolsHOME environment variable is not set.",
                    "ATATHELP Not Found", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                return;
            }
            FileInfo fi = new FileInfo(cvipHome + @"HELP\ATATHELP.CHM");
            if (!fi.Exists)
            {
                MessageBox.Show("The file: " + fi.FullName + " is missing.", "ATATHELP Not Found",
                    MessageBoxButtons.OK, MessageBoxIcon.Warning);
                return;
            }
            System.Diagnostics.Process.Start(fi.FullName);

        }
    }
}