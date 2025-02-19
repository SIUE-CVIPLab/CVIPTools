/*''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' ======================================================================
' Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
' ======================================================================
'
'             File Name: InfoPanel.cs
'           Description: Contains the controls and code
'                        for InfoPanel class
'   Initial Coding Date: April 2007
'              Modified: December 2009
'       Delevoping tool: Visual Studio 2010-C#
'             Credit(s): Patrick Solt
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
'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''*/

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace CVIPGUI
{
    public partial class InfoPanel : UserControl
    {
        public InfoPanel()
        {
            InitializeComponent();
        }
        public void AppendLine(string line)
        {
            this.richTextInfo.AppendText(line + "\n");
        }
        public void Clear()
        {
            CvipOp.Close_Console();
            this.richTextInfo.Text = "";
            CvipOp.Set_Console();
        }
        protected override void OnParentChanged(EventArgs e)
        {
            base.OnParentChanged(e);
            if (this.Tag == null)
            {
                this.Tag = true;
                Form parent = this.ParentForm;
                parent.Controls.Remove(this);
                parent.Controls.Add(this.splitter);
                parent.Controls.Add(this);
                this.Tag = null;
            }
        }
        private void mnuInfoClear_Click(object sender, EventArgs e)
        {
            this.Clear();
        }
        private void mnuInfoCopy_Click(object sender, EventArgs e)
        {
            if (!string.IsNullOrEmpty(this.richTextInfo.SelectedText))
            {
                Clipboard.SetText(this.richTextInfo.SelectedText);
            }
        }
        private void mnuInfoHide_Click(object sender, EventArgs e)
        {
            this.Visible = false;
        }
        private void richTextInfo_SelectionChanged(object sender, EventArgs e)
        {
            this.mnuInfoCopy.Enabled = !string.IsNullOrEmpty(this.richTextInfo.SelectedText);
        }
        private void timer1_Tick(object sender, EventArgs e)
        {
            if (richTextInfo.Text.Length > CvipConstant.CvipMessageBufferSize)
            {
                richTextInfo.Text = "";
            }
            string tmp = CvipOp.CVIP_OUTPUT();
            if (tmp != "")
            {
                richTextInfo.Text = richTextInfo.Text + tmp + "\n";
                richTextInfo.SelectionStart = richTextInfo.Text.Length;
                richTextInfo.ScrollToCaret();
            }
        }
    }
}
