using System;
using System.Windows.Forms;

namespace CVIPFEPC.Dialogs
{
    public partial class AboutDlg : Form
    {
        public AboutDlg()
        {
            InitializeComponent();
        }
        private void btnOK_Click(object sender, EventArgs e)
        {
            this.Dispose();
        }

        private void lnkCvipWebSite_LinkClicked_1(object sender, LinkLabelLinkClickedEventArgs e)
        {
            try { System.Diagnostics.Process.Start("http://cviptools.siue.edu"); }
            catch { }
        }
    }
}
