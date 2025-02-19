/*''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' ======================================================================
' Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
' ======================================================================
'
'             File Name: UtilitiesForm.cs
'           Description: Contains the controls and code
'                        for UtilitiesForm
'         Related Files: UtilArithLogic.cs
'                        UtilCompare.cs
'                        UtilConvert.cs
'                        UtilCreate.cs
'                        UtilEnhance.cs
'                        UtilFilter.cs
'                        UtilSize.cs
'                        UtilStats.cs
'                        CvipOp.cs
'                        CvipConstant.cs
'   Initial Coding Date: April 2007
'              Modified: July 2010
'       Delevoping tool: Visual Studio 2008-C#
'             Credit(s): Wenjun(Evan) Bian
'                        Patrick Solt
Hari Siva Kumar Reddy Bhogala
'                        Southern Illinois University Edwardsville
'
' Copyright (C) 2010 Scott Umbaugh and SIUE
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

namespace CVIPGUI
{
    public partial class UtilitiesForm : Form
    {
        private string mOpName;
        private string mUtilName;

        public UtilitiesForm()
        {
            InitializeComponent();
            this.MdiParent = MainForm.TheMainForm;
        }

        public void Init()
        {
            switch (this.mUtilName)
            {
            case "Arith/Logic":
                utilArithLogic1.Init(this.mOpName);
                utilArithLogic1.Visible = true;
                utilArithLogic1.BringToFront();
                break;

            case "Compare":
                utilCompare1.Init(this.mOpName);
                utilCompare1.Visible = true;
                utilCompare1.BringToFront();
                break;

            case "Convert":
                utilConvert1.Init(this.mOpName);
                utilConvert1.Visible = true;
                utilConvert1.BringToFront();
                break;

            case "Create":
                utilCreate1.Init(this.mOpName);
                utilCreate1.Visible = true;
                utilCreate1.BringToFront();
                break;

            case "Enhance":
                utilEnhance1.Init(this.mOpName);
                utilEnhance1.Visible = true;
                utilEnhance1.BringToFront();
                break;

            case "Filter":
                utilFilter1.Init(this.mOpName);
                utilFilter1.Visible = true;
                utilFilter1.BringToFront();
                break;

            case "Size":
                utilSize1.Init(this.mOpName);
                utilSize1.Visible = true;
                utilSize1.BringToFront();
                break;

            case "Stats":
                utilStats1.Init(this.mOpName);
                utilStats1.Visible = true;
                utilStats1.BringToFront();
                break;
            }
        }

        protected override void OnFormClosing(FormClosingEventArgs e)
        {
            base.OnFormClosing(e);
            MainForm.UtilitiesForm = null;
        }

        protected override void OnLoad(EventArgs e)
        {
            base.OnLoad(e);

            this.utilArithLogic1.Location = new Point(0, 0);
            this.utilCompare1.Location = new Point(0, 0);
            this.utilConvert1.Location = new Point(0, 0);
            this.utilCreate1.Location = new Point(0, 0);
            this.utilEnhance1.Location = new Point(0, 0);
            this.utilFilter1.Location = new Point(0, 0);
            this.utilSize1.Location = new Point(0, 0);
            this.utilStats1.Location = new Point(0, 0);
            if ((this.Height/4 > 185))
                this.Size = new Size(this.Width/2,this.Height/4);
            else
            this.Size = new Size(440, 185);
        }

        private void UpdateImageList(ViewerForm e)
        {
            UpdateImageList();
        }

        private void UpdateImageList()
        {
            if (MainForm.Viewers != null)
            {
                utilConvert1.UpdateImageList();
                utilEnhance1.UpdateImageList();
                utilStats1.UpdateImageList();
            }
        }

        protected override void WndProc(ref Message m)
        {
            base.WndProc(ref m);
            if (MainForm.Viewers != null)
            {
                switch ((WM)m.Msg)
                {
                case WM.CREATE:
                    MainForm.Viewers.SelectedViewerChanged += this.UpdateImageList;
                    MainForm.Viewers.ViewerCollectionChanged += this.UpdateImageList;
                    break;

                case WM.DESTROY:
                    MainForm.Viewers.SelectedViewerChanged -= this.UpdateImageList;
                    MainForm.Viewers.ViewerCollectionChanged -= this.UpdateImageList;
                    break;
                }
            }
        }

        public string OpName { set { mOpName = value; } }
        public string UtilName { set { mUtilName = value; } }

        private void UtilitiesForm_Load(object sender, EventArgs e)
        {

        }

        private void utilEnhance1_Load(object sender, EventArgs e)
        {

        }

        private void utilFilter1_Load(object sender, EventArgs e)
        {

        }

        private void utilConvert1_Load(object sender, EventArgs e)
        {

        }
    }
}
