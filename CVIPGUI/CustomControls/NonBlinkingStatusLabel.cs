/*''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' ======================================================================
' Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
' ======================================================================
'
'             File Name: Win32Msgs.cs
'           Description: Contains the controls and code
'                        for CustomControls->NonBlinkingStatusLabel class
'   Initial Coding Date: June 2007
'              Modified: March 2010
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
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace CVIPGUI
{
    class NonBlinkingStatusLabel : System.Windows.Forms.ToolStripStatusLabel
    {
        Point pt = new Point();

        protected override void OnMouseEnter(EventArgs e)
        {
            pt = Cursor.Position;
            base.OnMouseEnter(e);
        }
        protected override void OnMouseLeave(EventArgs e)
        {
            if (!pt.IsEmpty && (pt == Cursor.Position))
            {
                return;
            }
            pt = Cursor.Position;
            base.OnMouseLeave(e);
        }
        protected override void OnMouseMove(MouseEventArgs mea)
        {
            if (!pt.IsEmpty && (pt == Cursor.Position))
            {
                return;
            }
            pt = Cursor.Position;
            base.OnMouseMove(mea);
        }
    }
}
