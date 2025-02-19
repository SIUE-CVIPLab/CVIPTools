/***************************************************************************
* =========================================================================
*
*			 CVIP_ATAT - Dr. Scott Umbaugh SIUE
* 
* =========================================================================
*
*             File Name: NewProject.cs 
*           Description: Used to create new project.
*   Initial Coding Date: June 6, 2006
*Last Modification Made: June 22, 2010
*  Programming Language: Visual Studio C#.NET 2008 
*             Credit(s): Wenjun(Evan) Bian, Pelin Guvenc
*                        Southern Illinois University at Edwardsville
*
*		  Copyright (c): 2010-2011 SIUE - Scott Umbaugh
****************************************************************************/

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Diagnostics;
using System.IO;

namespace CVIP_ATAT
{
    public partial class NewProject : Form
    {
        MDIMainForm MDIMainFormRef;

        public NewProject(MDIMainForm reference)
        {
            InitializeComponent();
            tbPName.Select();

            MDIMainFormRef = reference;
        }

        private void btBrowse_Click(object sender, EventArgs e)
        {
            if (folderBrowserDialog1.ShowDialog() != DialogResult.Cancel)
            { 
               tbLocation.Text =  folderBrowserDialog1.SelectedPath+"\\";
               labelPPath.Text  = tbLocation.Text + tbPName.Text;
                
            }
            
        }

        private void btCancel_Click(object sender, EventArgs e)
        {
            MDIMainFormRef.newProject.Dispose();
        }

        private void btOk_Click(object sender, EventArgs e)
        {
            labelPPath.Text = tbLocation.Text + tbPName.Text;
            if (Directory.Exists(labelPPath.Text) == true)
            {
                MessageBox.Show("The directory already exists. Please change the directory name.","Change directory",
                     MessageBoxButtons.OK, MessageBoxIcon.Warning);

            }
            else
            {
                DirectoryInfo createDirectory = new DirectoryInfo(labelPPath.Text.ToString ());
                createDirectory.Create();
                MDIMainFormRef.newProjectPath =createDirectory.FullName;
                this.Dispose();
            }
        }

        private void tbPName_KeyUp(object sender, KeyEventArgs e)
        {
            labelPPath.Text = tbLocation.Text + tbPName.Text;

        }

        private void NewProject_Load(object sender, EventArgs e)
        {

        }


    }
}