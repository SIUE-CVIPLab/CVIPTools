/*''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' ======================================================================
' Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
' ======================================================================
'
'             File Name: LaunchCameraForm.cs
'           Description: Contains the controls and code
'                        for LaunchCameraForm
'   Initial Coding Date: December 2009
'              Modified: November 2011
'       Delevoping tool: Visual Studio 2010-C#
'             Credit(s): Jhansi Lakshmi Akkineni
'                        Patrick Solt
'                        Southern Illinois University Edwardsville
'
' Copyright (C) 2013 Scott Umbaugh and SIUE
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
using System.Diagnostics;
using System.Drawing;
using System.IO;
using System.Text;
using System.Windows.Forms;

namespace CVIPGUI
{
    public partial class LaunchCameraForm : Form
    {
        public LaunchCameraForm()
        {
            InitializeComponent();
            this.MdiParent = MainForm.TheMainForm;
        }
        private void btnBrowse_Click(object sender, EventArgs e)
        {
            if (!string.IsNullOrEmpty(this.txtProgram.Text))
            {
                try
                {
                    string dir = Path.GetDirectoryName(this.txtProgram.Text);
                    string fname = Path.GetFileName(this.txtProgram.Text);
                    this.dlgFileOpen.InitialDirectory = dir;
                    this.dlgFileOpen.FileName = fname;
                }
                catch { }
            }
            if (this.dlgFileOpen.ShowDialog() == DialogResult.OK)
                this.txtProgram.Text = this.dlgFileOpen.FileName;
        }
        private void btnLaunch_Click(object sender, EventArgs e)
        {
            try
            {
                ProcessStartInfo psi = new ProcessStartInfo(this.txtProgram.Text, "");
                psi.RedirectStandardOutput = true;
                psi.UseShellExecute = false;
                Process p = Process.Start(psi);
                p.Start();
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }
        protected override void OnFormClosing(FormClosingEventArgs e)
        {
            base.OnFormClosing(e);
            MainForm.LaunchCameraForm = null;
        }
    }
}
