/*''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' ======================================================================
' Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
' ======================================================================
'
'             File Name: UpDown.cs
'           Description: Contains the code for
'                        UpDown custom control
'         Related Files: MainForm.cs
'   Initial Coding Date: November 2006
'              Modified: December 2011
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
using System.Drawing;
using System.Data;
using System.Text;
using System.Windows.Forms;

namespace CVIPFEPC.CustomControls
{
    public partial class UpDown : UserControl
    {
        private int m_nMin = 0;
        private int m_nMax = 10;
        private int m_nIncrement = 1;
        private int m_nValue = 0;
        private bool m_bWrap = false;

        [Category("Action")]
        [Description("Fires when the up button is clicked.")]
        public event Action UpClick;

        [Category("Action")]
        [Description("Fires when the down button is clicked.")]
        public event Action DownClick;

        public UpDown()
        {
            InitializeComponent();
        }
        private void btnDown_Click(object sender, EventArgs e)
        {
            this.m_nValue -= this.m_nIncrement;
            UpdateState();

            // If an event has no subscribers registerd, it will
            // evaluate to null. The test checks that the value is not
            // null, ensuring that there are subscribers before
            // calling the event itself.
            if (DownClick != null)
                DownClick();  // Notify Subscribers
        }
        private void btnUp_Click(object sender, EventArgs e)
        {
            this.m_nValue += this.m_nIncrement;
            UpdateState();

            // If an event has no subscribers registerd, it will
            // evaluate to null. The test checks that the value is not
            // null, ensuring that there are subscribers before
            // calling the event itself.
            if (UpClick != null)
                UpClick();  // Notify Subscribers
        }
        protected override void OnResize(EventArgs e)
        {
            base.OnResize(e);

            int nMidPoint = this.Height / 2;

            this.btnUp.Top = 0;
            this.btnUp.Left = 0;
            this.btnUp.Width = this.Width;
            this.btnUp.Height = nMidPoint;

            this.btnDown.Top = nMidPoint;
            this.btnDown.Left = 0;
            this.btnDown.Width = this.Width;
            this.btnDown.Height = nMidPoint;
        }
        private void UpdateState()
        {
            if ((this.m_nIncrement == 0) ||
                (this.m_nMin == this.m_nMax))
            {
                if (this.m_nMin == this.m_nMax)
                    this.m_nValue = this.m_nMin;
                this.btnDown.Enabled = false;
                this.btnUp.Enabled = false;
            }
            else
            {
                if (this.m_bWrap)
                {
                    while (this.m_nValue > this.m_nMax)
                        this.m_nValue -= this.Range;
                    while (this.m_nValue < this.m_nMin)
                        this.m_nValue += this.Range;
                    this.btnDown.Enabled = true;
                    this.btnUp.Enabled = true;
                }
                else
                {
                    bool UpEnabled = true;
                    bool DownEnabled = true;
                    if (this.m_nValue >= this.m_nMax)
                    {
                        this.m_nValue = this.m_nMax;
                        UpEnabled = false;
                    }
                    else if (this.m_nValue <= this.m_nMin)
                    {
                        this.m_nValue = this.m_nMin;
                        DownEnabled = false;
                    }
                    if (this.m_nIncrement < 0)
                    {
                        bool swap = UpEnabled;
                        UpEnabled = DownEnabled;
                        DownEnabled = swap;
                    }
                    this.btnDown.Enabled = DownEnabled;
                    this.btnUp.Enabled = UpEnabled;
                }
            }
        }

        [Category("Misc")]
        [Description("Get/Set the amount by which the position changes on each click")]
        public int Increment
        {
            get { return this.m_nIncrement; }
            set
            {
                this.m_nIncrement = value;
                UpdateState();
            }
        }

        [Category("Misc")]
        [Description("Get/Set the lower bound of the scroll range")]
        public int Min
        {
            get { return this.m_nMin; }
            set
            {
                if (value > this.m_nMax)
                {
                    MessageBox.Show("Min cannot be greater than Max.",
                                    "Properties Window",
                                    MessageBoxButtons.OKCancel,
                                    MessageBoxIcon.Exclamation);
                    return;
                }
                this.m_nMin = value;
                if (this.m_nValue < this.m_nMin)
                    this.m_nValue = this.m_nMin;
                UpdateState();
            }
        }

        [Category("Misc")]
        [Description("Get/Set the upper bound of the scroll range")]
        public int Max
        {
            get { return this.m_nMax; }
            set
            {
                if (value < this.m_nMin)
                {
                    MessageBox.Show("Max cannot be less than Min.",
                                    "Properties Window",
                                    MessageBoxButtons.OKCancel,
                                    MessageBoxIcon.Exclamation);
                    return;
                }
                this.m_nMax = value;
                if (this.m_nValue > this.m_nMax)
                    this.m_nValue = this.m_nMax;
                UpdateState();
            }
        }

        [Category("Misc")]
        [Description("Get value of the scroll range")]
        public int Range
        {
            get { return this.m_nMax - this.m_nMin + 1; }
        }

        [Category("Misc")]
        [Description("Get/Set the current position in the scroll range")]
        public int Value
        {
            get { return this.m_nValue; }
            set
            {
                if ((value < this.m_nMin) || (value > this.m_nMax))
                {
                    MessageBox.Show("Value must be within scroll range.",
                                    "Properties Window",
                                    MessageBoxButtons.OKCancel,
                                    MessageBoxIcon.Exclamation);
                    return;
                }
                this.m_nValue = value;
                UpdateState();
            }
        }

        [Category("Behavior")]
        [Description("Get/Set whether the value (position) will wrap from max to min (or min to max)")]
        public bool Wrap
        {
            get { return this.m_bWrap; }
            set
            {
                this.m_bWrap = value;
                UpdateState();
            }
        }
    }
}
