/***************************************************************************
* =========================================================================
*
*			 CVIP_ATAT - Dr. Scott Umbaugh SIUE
* 
* =========================================================================
*
*             File Name: AboutCVIPATAT.cs 
*           Description: About CVIPATAT.
*   Initial Coding Date: June 6, 2006
*Last Modification Made: June 22, 2010
*  Programming Language: Visual Studio C#.NET 2008 
*             Credit(s): Wenjun(Evan) Bian, Pelin Guvenc
*                        Southern Illinois University at Edwardsville
*
*		  Copyright (c): 2010-2011 SIUE - Scott Umbaugh
****************************************************************************/

using System;
using System.Windows.Forms;

namespace CVIP_ATAT
{
    public partial class AboutCVIPATAT : Form
    {
        public AboutCVIPATAT()
        {
            InitializeComponent();
        }

        private void AboutCVIPATATExit_Click(object sender, EventArgs e)
        {
            this.Dispose();
        }

        private void linkLabel1_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
        {
            System.Diagnostics.Process.Start("http://cviptools.siue.edu");

        }
    }
}