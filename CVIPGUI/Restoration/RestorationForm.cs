/*''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' ======================================================================
' Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
' ======================================================================
'
'             File Name: RestorationForm.cs
'           Description: Contains the controls and code
'                        for Restoration Form
'         Related Files: Noise.cs
'                        SpatialFilter.cs
'                        FrequencyFilter.cs
'                        CvipOp.cs
'                        CvipConstant.cs
'   Initial Coding Date: April 2007
'              Modified: October 2009
'       Delevoping tool: Visual Studio 2010-C#
'             Credit(s): Wenjun(Evan) Bian
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
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace CVIPGUI
{
    public partial class RestorationForm : Form
    {
        public RestorationForm()
        {
            InitializeComponent();
            this.MdiParent = MainForm.TheMainForm;
        }
        protected override void OnFormClosing(FormClosingEventArgs e)
        {
            base.OnFormClosing(e);
            MainForm.RestorationForm = null;
        }
    }
}
