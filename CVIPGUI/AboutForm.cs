/*''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' ======================================================================
' Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
' ======================================================================
'
'             File Name: AboutForm.cs
'           Description: Contains the controls and code
'                        for AboutForm
'   Initial Coding Date: February 2007
'              Modified: March 2013
'       Delevoping tool: Visual Studio 2010-C#
'             Credit(s): Wenjun(Evan) Bian
'                        Patrick Solt
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
using System.Windows.Forms;

namespace CVIPGUI
{
    public partial class AboutForm : Form
    {
        public AboutForm()
        {
            InitializeComponent();
        }
        private void chkAboutCvip_Click(object sender, EventArgs e)
        {
            this.txtAboutCvip.Visible = this.chkAboutCvip.Checked;
            this.pnlAboutCvip.Visible = !this.chkAboutCvip.Checked;
        }
        private void lnkCvipWebSite_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
        {
            try { System.Diagnostics.Process.Start("http://cviptools.siue.edu"); }
            catch { }
        }

        private void btnOK_Click(object sender, EventArgs e)
        {

        }   
    }
}
