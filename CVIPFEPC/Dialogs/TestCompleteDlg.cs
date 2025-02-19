/*''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' ======================================================================
' Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
' ======================================================================
'
'             File Name: TestCompleteDlg.cs
'           Description: Contains the code for TestCompleteDlg
'                        dialog, a customized MessageBox look-a-like.
'         Related Files: MainForm.cs
'   Initial Coding Date: January 2012
'       Delevoping tool: Visual Studio 2010-C#
'             Credit(s): Patrick Solt
'                        Southern Illinois University Edwardsville
'
' Copyright (C) 2012 Scott Umbaugh and SIUE
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
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace CVIPFEPC.Dialogs
{
    public partial class TestCompleteDlg : Form
    {
        public TestCompleteDlg()
        {
            InitializeComponent();
            this.Font = SystemFonts.MessageBoxFont;
        }
        public TestCompleteDlg(string sResultsLocation)
            : this()
        {
            this.ResultsLink = sResultsLocation;
        }
        private void lblResult_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
        {
            try { System.Diagnostics.Process.Start(this.ResultsLink); }
            catch { }
        }
        protected override void WndProc(ref Message m)
        {
            switch (m.Msg)
            {
            case 0x0001: // WM_CREATE
                Icon info = SystemIcons.Information;
                Bitmap bmp = new Bitmap(info.Width, info.Height);
                using (Graphics g = Graphics.FromImage(bmp))
                {
                    g.Clear(SystemColors.Window);
                    g.DrawIcon(info, 0, 0);
                }
                this.picIcon.Image = bmp;
                break;
            }
            base.WndProc(ref m);
        }

        public string ResultsLink
        {
            get
            {
                string link = null;
                if (this.lblSmallResult.Visible)
                    link = this.lblSmallResult.Text;
                else if (this.lblLargeResult.Visible)
                    link = this.lblLargeResult.Text;
                return link;
            }
            set
            {
                using (Graphics graphics = this.CreateGraphics())
                {
                    int proposedWidth = this.ClientSize.Width;
                    int proposedHeight = this.ClientSize.Height;
                    SizeF sz = graphics.MeasureString(value, this.lblSmallResult.Font);
                    if ((int)sz.Width <= this.lblSmallResult.Width)
                    {
                        this.lblSmallResult.Text = value;
                        this.lblSmallResult.Visible = true;
                        this.lblLargeResult.Visible = false;
                        this.pnlMessage.Anchor = AnchorStyles.Left;
                        this.pnlMessage.Height = this.lblDoneMessage.Height;
                        this.pnlMessage.Width = this.lblSmallResult.Left + (int)sz.Width;
                    }
                    else
                    {
                        if ((int)sz.Width > this.lblLargeResult.Width)
                        {
                            sz = graphics.MeasureString(value, this.lblLargeResult.Font, this.lblLargeResult.Width);
                            int rows = (int)sz.Height / this.lblLargeResult.Height;
                            this.lblLargeResult.Height = rows * this.lblLargeResult.Height;
                        }
                        this.lblLargeResult.Text = value;
                        this.lblLargeResult.Visible = true;
                        this.lblSmallResult.Visible = false;
                        this.pnlMessage.Anchor = AnchorStyles.Top | AnchorStyles.Left;
                        this.pnlMessage.Height = this.lblDoneMessage.Height + this.lblLargeResult.Height;
                        this.pnlMessage.Width = this.lblLargeResult.Left + (int)sz.Width;
                    }
                }
            }
        }
    }
}
