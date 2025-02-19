/*''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' ======================================================================
' Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
' ======================================================================
'
'             File Name: viewTable.cs
'           Description: Contains the controls and code
'                        for Compression->viewTable page
'         Related Files: CvipOp.cs
'                        CvipConstant.cs
'   Initial Coding Date: April 2007
'              Modified: November 2011
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
'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''*/

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Text;
using System.Windows.Forms;

namespace CVIPGUI
{
    public partial class viewTable : Form
    {
        TextBox[] arrText;

        string[] tableChrominanceDefault = new string[] {
                                                    "17", "18", "24", "47", "99", "99", "99", "99",
                                                    "18", "21", "26", "66", "99", "99", "99", "99",
                                                    "24", "26", "56", "99", "99", "99", "99", "99",
                                                    "47", "66", "99", "99", "99", "99", "99", "99",
                                                    "99", "99", "99", "99", "99", "99", "99", "99",
                                                    "99", "99", "99", "99", "99", "99", "99", "99",
                                                    "99", "99", "99", "99", "99", "99", "99", "99",
                                                    "99", "99", "99", "99", "99", "99", "99", "99" };

        string[] tableLuminanceDefault = new string[]   {
                                                    "16", "11", "10", "16", "24",  "15",  "1",   "61",
                                                    "12", "12", "14", "19", "26",  "58",  "60",  "55",
                                                    "14", "13", "16", "24", "40",  "57",  "69",  "56",
                                                    "14", "17", "22", "29", "51",  "81",  "80",  "62",
                                                    "18", "22", "37", "56", "68",  "109", "103", "77",
                                                    "24", "35", "55", "64", "81",  "104", "113", "92",
                                                    "49", "64", "78", "87", "103", "121", "120", "101",
                                                    "72", "92", "95", "98", "112", "100", "103", "99" };

        string[] tableNoneQuantDefault = new string[] {
                                                    "1", "1", "1", "1", "1", "1", "1", "1",
                                                    "1", "1", "1", "1", "1", "1", "1", "1",
                                                    "1", "1", "1", "1", "1", "1", "1", "1",
                                                    "1", "1", "1", "1", "1", "1", "1", "1",
                                                    "1", "1", "1", "1", "1", "1", "1", "1",
                                                    "1", "1", "1", "1", "1", "1", "1", "1",
                                                    "1", "1", "1", "1", "1", "1", "1", "1",
                                                    "1", "1", "1", "1", "1", "1", "1", "1"};

        public viewTable()
        {
            InitializeComponent();
            this.MdiParent = MainForm.TheMainForm;
        }
        private void btCancel_Click(object sender, EventArgs e)
        {
            if (this.Text == "JPEG Chrominance Table")
                MainForm.CompressionForm.pageLossy.tableChrom = null;
            if (this.Text == "JPEG Luminance Table")
                MainForm.CompressionForm.pageLossy.tableLumi = null;
            this.Dispose();
        }
        private void btDefault_Click(object sender, EventArgs e)
        {
            string[] tableDefault = tableNoneQuantDefault;
            if (MainForm.CompressionForm.pageLossy.comboBoxQuanTable.Text == "Default")
            {
                if (this.Text == "JPEG Chrominance Table")
                    tableDefault = tableChrominanceDefault;
                else
                    tableDefault = tableLuminanceDefault;
            }
            for (int i = 0; i < 64; i++)
                arrText[i].Text = tableDefault[i];
        }
        private void btSave_Click(object sender, EventArgs e)
        {
            if (this.Text == "JPEG Chrominance Table")
            {
                if (MainForm.CompressionForm.pageLossy.comboBoxQuanTable.Text == "Default")
                {
                    for (int i = 0; i < 64; i++)
                    {
                        MainForm.CompressionForm.pageLossy.tableChrominanceSave[i] = arrText[i].Text;
                        if (!MainForm.CompressionForm.pageLossy.bChrominanceTableSaved)
                            MainForm.CompressionForm.pageLossy.tableChrominanceNoneQuantSave[i] = tableNoneQuantDefault[i];
                    }
                }
                else
                {
                    for (int i = 0; i < 64; i++)
                    {
                        MainForm.CompressionForm.pageLossy.tableChrominanceNoneQuantSave[i] = arrText[i].Text;
                        if (!MainForm.CompressionForm.pageLossy.bChrominanceTableSaved)
                            MainForm.CompressionForm.pageLossy.tableChrominanceSave[i] = tableChrominanceDefault[i];
                    }
                }
                MainForm.CompressionForm.pageLossy.bChrominanceTableSaved = true;
            }
            else
            {
                if (MainForm.CompressionForm.pageLossy.comboBoxQuanTable.Text == "Default")
                {
                    for (int i = 0; i < 64; i++)
                    {
                        MainForm.CompressionForm.pageLossy.tableLuminanceSave[i] = arrText[i].Text;
                        if (!MainForm.CompressionForm.pageLossy.bLuminanceTableSaved)
                            MainForm.CompressionForm.pageLossy.tableLuminanceNoneQuantSave[i] = tableNoneQuantDefault[i];
                    }
                }
                else
                {
                    for (int i = 0; i < 64; i++)
                    {
                        MainForm.CompressionForm.pageLossy.tableLuminanceNoneQuantSave[i] = arrText[i].Text;
                        if (!MainForm.CompressionForm.pageLossy.bLuminanceTableSaved)
                            MainForm.CompressionForm.pageLossy.tableLuminanceSave[i] = tableLuminanceDefault[i];
                    }
                }
                MainForm.CompressionForm.pageLossy.bLuminanceTableSaved = true;
            }
            SaveJPEGQuantTable();
        }
        protected override void OnFormClosing(FormClosingEventArgs e)
        {
            base.OnFormClosing(e);
            if (this.Text == "JPEG Chrominance Table")
                MainForm.CompressionForm.pageLossy.tableChrom = null;
            if (this.Text == "JPEG Luminance Table")
                MainForm.CompressionForm.pageLossy.tableLumi = null;
        }
        protected override void OnLoad(EventArgs e)
        {
            base.OnLoad(e);
            arrText = new TextBox[] {
                textBox1,  textBox2,  textBox3,  textBox4,  textBox5,  textBox6,  textBox7,  textBox8,
                textBox9,  textBox10, textBox11, textBox12, textBox13, textBox14, textBox15, textBox16,
                textBox17, textBox18, textBox19, textBox20, textBox21, textBox22, textBox23, textBox24,
                textBox25, textBox26, textBox27, textBox28, textBox29, textBox30, textBox31, textBox32,
                textBox33, textBox34, textBox35, textBox36, textBox37, textBox38, textBox39, textBox40,
                textBox41, textBox42, textBox43, textBox44, textBox45, textBox46, textBox47, textBox48,
                textBox49, textBox50, textBox51, textBox52, textBox53, textBox54, textBox55, textBox56,
                textBox57, textBox58, textBox59, textBox60, textBox61, textBox62, textBox63, textBox64};

            LoadJPEGQuantTable();
        }
        public void LoadJPEGQuantTable()
        {
            string[] tableLoad;
            if (this.Text == "JPEG Chrominance Table")
            {
                if (MainForm.CompressionForm.pageLossy.comboBoxQuanTable.Text == "Default")
                {
                    if (MainForm.CompressionForm.pageLossy.bChrominanceTableSaved)
                        tableLoad = MainForm.CompressionForm.pageLossy.tableChrominanceSave;
                    else
                        tableLoad = tableChrominanceDefault;
                }
                else
                {
                    if (MainForm.CompressionForm.pageLossy.bChrominanceTableSaved)
                        tableLoad = MainForm.CompressionForm.pageLossy.tableChrominanceNoneQuantSave;
                    else
                        tableLoad = tableNoneQuantDefault;
                }
            }
            else
            {
                if (MainForm.CompressionForm.pageLossy.comboBoxQuanTable.Text == "Default")
                {
                    if (MainForm.CompressionForm.pageLossy.bLuminanceTableSaved)
                        tableLoad = MainForm.CompressionForm.pageLossy.tableLuminanceSave;
                    else
                        tableLoad = tableLuminanceDefault;
                }
                else
                {
                    if (MainForm.CompressionForm.pageLossy.bLuminanceTableSaved)
                        tableLoad = MainForm.CompressionForm.pageLossy.tableLuminanceNoneQuantSave;
                    else
                        tableLoad = tableNoneQuantDefault;
                }
            }
            for (int i = 0; i < 64; i++)
                arrText[i].Text = tableLoad[i];
        }
        public void SaveJPEGQuantTable()
        {
            string[] tableChrominance;
            string[] tableLuminance;
            if (MainForm.CompressionForm.pageLossy.comboBoxQuanTable.Text == "Default")
            {
                tableLuminance = tableLuminanceDefault;
                tableChrominance = tableChrominanceDefault;
                if (MainForm.CompressionForm.pageLossy.bLuminanceTableSaved &&
                    (MainForm.CompressionForm.pageLossy.tableLuminanceSave[0] != null))
                {
                    tableLuminance = MainForm.CompressionForm.pageLossy.tableLuminanceSave;
                }
                if (MainForm.CompressionForm.pageLossy.bChrominanceTableSaved &&
                    (MainForm.CompressionForm.pageLossy.tableChrominanceSave[0] != null))
                {
                    tableChrominance = MainForm.CompressionForm.pageLossy.tableChrominanceSave;
                }
            }
            else
            {
                tableLuminance = tableNoneQuantDefault;
                tableChrominance = tableNoneQuantDefault;
                if (MainForm.CompressionForm.pageLossy.bLuminanceTableSaved &&
                    (MainForm.CompressionForm.pageLossy.tableLuminanceNoneQuantSave[0] != null))
                {
                    tableLuminance = MainForm.CompressionForm.pageLossy.tableLuminanceNoneQuantSave;
                }
                if (MainForm.CompressionForm.pageLossy.bChrominanceTableSaved &&
                    (MainForm.CompressionForm.pageLossy.tableChrominanceNoneQuantSave[0] != null))
                {
                    tableChrominance = MainForm.CompressionForm.pageLossy.tableChrominanceNoneQuantSave;
                }
            }
            string fileName = Environment.GetEnvironmentVariable("TEMP") + @"\quant1.txt";
            if (File.Exists(fileName)) File.Delete(fileName);
            using (StreamWriter sw = File.CreateText(fileName))
            {
                for (int i = 0; i < 64; i++)
                    sw.Write(tableLuminance[i] + " ");
                sw.WriteLine("\n");
                for (int i = 0; i < 64; i++)
                    sw.Write(tableChrominance[i] + " ");
                sw.WriteLine();
            }
        }
    }
}
