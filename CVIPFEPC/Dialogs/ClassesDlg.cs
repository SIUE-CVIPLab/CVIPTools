/*''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' ======================================================================
' Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
' ======================================================================
'
'             File Name: ClassesDlg.cs
'           Description: Contains the code for
'                        ClassesDlg dialog
'         Related Files: MainForm.cs
'                        AppConfiguration.cs
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

using CVIPFEPC.Configuration;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace CVIPFEPC.Dialogs
{
    public partial class ClassesDlg : Form
    {
        public ClassesDlg()
        {
            InitializeComponent();
        }
        private void btnAdd_Click(object sender, EventArgs e)
        {
            if (this.txtNewClass.Text.Contains(" "))
            {
                MessageBox.Show("Class Names Cannot Have Spaces.",
                    "Spaces in Class Name!", MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
            else if (!string.IsNullOrEmpty(this.txtNewClass.Text))
            {
                this.lstClasses.Items.Add(this.txtNewClass.Text);
                this.txtNewClass.Text = "";
                this.txtNewClass.Focus();
            }
            CheckDirty();
        }
        private void btnDelete_Click(object sender, EventArgs e)
        {
            if (this.lstClasses.SelectedItems.Count > 0)
            {
                object[] itms = new object[this.lstClasses.SelectedItems.Count];
                this.lstClasses.SelectedItems.CopyTo(itms, 0);
                foreach (object obj in itms)
                    this.lstClasses.Items.Remove(obj);
            }
            CheckDirty();
        }
        private void btnOK_Click(object sender, EventArgs e)
        {
            if (this.IsDirty)
            {
                string[] list = new string[this.lstClasses.Items.Count];
                this.lstClasses.Items.CopyTo(list, 0);
                AppConfiguration.ClassList = new List<string>(list);
            }
        }
        private void btnReset_Click(object sender, EventArgs e)
        {
            ResetControls();
        }
        private void CheckDirty()
        {
            this.btnAdd.Enabled = !string.IsNullOrEmpty(this.txtNewClass.Text);
            this.btnDelete.Enabled = (this.lstClasses.SelectedItems.Count > 0);
            this.btnReset.Enabled = this.IsDirty;
        }
        private void lstClasses_SelectedIndexChanged(object sender, EventArgs e)
        {
            this.btnDelete.Enabled = (this.lstClasses.SelectedItems.Count > 0);
        }
        protected override void OnLoad(EventArgs e)
        {
            base.OnLoad(e);
            ResetControls();
        }
        private void ResetControls()
        {
            this.lstClasses.Items.Clear();
            this.lstClasses.Items.AddRange(AppConfiguration.ClassList.ToArray());
            this.txtNewClass.Text = "";
            this.txtNewClass.Focus();
            CheckDirty();
        }
        private void txtNewClass_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (((int)e.KeyChar == 13) && !string.IsNullOrEmpty(this.txtNewClass.Text))
            {
                this.btnAdd.PerformClick();
                e.Handled = true;
            }
        }
        private void txtNewClass_TextChanged(object sender, EventArgs e)
        {
            this.btnAdd.Enabled = !string.IsNullOrEmpty(this.txtNewClass.Text);
        }

        private bool IsDirty
        {
            get
            {
                bool dirty = this.lstClasses.Items.Count != AppConfiguration.ClassList.Count;
                if (!dirty && (this.lstClasses.Items.Count > 0))
                {
                    for (int i = 0; i < this.lstClasses.Items.Count; i++)
                    {
                        if ((string)this.lstClasses.Items[i] != AppConfiguration.ClassList[i])
                        {
                            dirty = true;
                            break;
                        }
                    }
                }
                return dirty;
            }
        }

        private void ClassesDlg_Load(object sender, EventArgs e)
        {

        }
    }
    public class EnterTextBox : TextBox
    {
        protected override bool IsInputKey(Keys key)
        {
            if (key == Keys.Enter)
                return true;
            return base.IsInputKey(key);
        }
    }
}
