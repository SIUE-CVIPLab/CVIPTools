/*''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' ======================================================================
' Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
' ======================================================================
'
'             File Name: FepcListView.cs
'           Description: Contains the code for
'                        FepcListView custom control
'         Related Files: MainForm.cs
'                        ImageObject.cs
'                        FeatureFile.cs
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
using CVIPFEPC.CvipFile;
using System;
using System.Collections;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace CVIPFEPC.CustomControls
{
    public delegate Tuple<FeatureFileSet, string> FeatureFileGet();

    public class FepcListView : ListView, IList<ImageObject>
    {
        private bool bLeave1OutChanged = false;
        private bool bTestTrainingChanged = false;
        private int nSortCol = 1;
        private IContainer components;
        private ColumnHeader columnHeader1;
        private ColumnHeader columnHeader2;
        private ContextMenuStrip popmnuClasses;
        private CheckedObjectEnumerator enumTestSet = null;
        private NotCheckedObjectEnumerator enumTrainingSet = null;
        private SelectedObjectList listSelectedObjects;
        private FeatureFileSet ffsLeave1Out = null;
        private FeatureFileSet ffsTestTraining = null;

        [Category("Action")]
        [Description("Fires when delete keypress message is received.")]
        public event Action DeleteKeyPressed;

        [Category("Action")]
        [Description("Fires when item is clicked on Classes context menu.")]
        public event ToolStripItemClickedEventHandler ClassSelectionChanged
        {
            add { this.popmnuClasses.ItemClicked += value; }
            remove { this.popmnuClasses.ItemClicked -= value; }
        }

        public FepcListView()
        {
            this.components = new System.ComponentModel.Container();
            this.columnHeader1 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.columnHeader2 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.popmnuClasses = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.SuspendLayout();
            // 
            // columnHeader1
            // 
            this.columnHeader1.Text = "Image File";
            this.columnHeader1.Width = 190;
            // 
            // columnHeader2
            // 
            this.columnHeader2.Text = "Class";
            this.columnHeader2.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.columnHeader2.Width = 69;
            // 
            // popmnuClasses
            // 
            this.popmnuClasses.Name = "popmnuClasses";
            this.popmnuClasses.Size = new System.Drawing.Size(110, 70);
            // 
            // FepcListView
            // 
            this.CheckBoxes = true;
            this.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.columnHeader1,
            this.columnHeader2});
            this.ContextMenuStrip = this.popmnuClasses;
            this.HideSelection = false;
            this.LabelWrap = false;
            this.View = System.Windows.Forms.View.Details;
            this.ResumeLayout(false);

            // Create FeatureFiles for experiments
            this.ffsLeave1Out = new FeatureFileSet(true);
            this.ffsTestTraining = new FeatureFileSet(false);
        }
        public void Add(ImageObject obj)
        {
            Add(obj, false);
        }
        public void Add(ImageObject obj, bool istestobject)
        {
            ListViewItem itm = this.Items.Add(obj.Name);
            itm.Checked = istestobject;
            itm.Name = obj.FileName;
            itm.SubItems.Add(obj.ClassName);
            itm.Tag = obj;
            this.bLeave1OutChanged = true;
            this.bTestTrainingChanged = true;
        }
        public bool Contains(ImageObject obj)
        {
            return this.Items.ContainsKey(obj.FileName);
        }
        public void CopyTo(ImageObject[] dest, int idx)
        {
            foreach (ImageObject obj in this)
                dest[idx++] = obj;
        }
        IEnumerator IEnumerable.GetEnumerator()
        {
            return this.GetEnumerator();
        }
        public IEnumerator<ImageObject> GetEnumerator()
        {
            foreach (ListViewItem itm in this.Items)
                yield return (ImageObject)itm.Tag;
        }
        public Tuple<FeatureFileSet, string> GetFeatureFile()
        {
            FeatureFileSet ffs = null;
            string msg = null;
            bool space = false;
            if (!this.CheckBoxes)
            {
                if (this.Items.Count == 0)
                    msg = "Feature file is empty. Please select some images.";
                else
                {
                    ffs = this.ffsLeave1Out;
                    if (this.bLeave1OutChanged)
                    {
                        this.ffsLeave1Out.Clear();
                        foreach (ImageObject obj in this)
                        {
                            if (obj.Name.Contains(" ") && space == false)
                                space = true;
                            this.ffsLeave1Out.Add(obj);
                        }
                        this.bLeave1OutChanged = false;
                    }
                }
            }
            else
            {
                if (this.TrainingSetObjects.Count == 0 || this.TestSetObjects.Count == 0)
                {
                    this.Randomize();
                    ffs = this.ffsTestTraining;
                    if (this.bTestTrainingChanged)
                    {
                        this.ffsTestTraining.Clear();
                        foreach (ImageObject obj in this.TrainingSetObjects)
                        {
                            if (obj.Name.Contains(" ") && space == false)
                                space = true;
                            this.ffsTestTraining.TrainingSet.Add(obj);
                        }
                        foreach (ImageObject obj in this.TestSetObjects)
                        {
                            if (obj.Name.Contains(" ") && space == false)
                                space = true;
                            this.ffsTestTraining.TestSet.Add(obj);
                        }
                        this.bTestTrainingChanged = false;
                    }
                }
                else
                {
                    ffs = this.ffsTestTraining;
                    if (this.bTestTrainingChanged)
                    {
                        this.ffsTestTraining.Clear();
                        foreach (ImageObject obj in this.TrainingSetObjects)
                        {
                            if (obj.Name.Contains(" ") && space == false)
                                space = true;
                            this.ffsTestTraining.TrainingSet.Add(obj);
                        }
                        foreach (ImageObject obj in this.TestSetObjects)
                        {
                            if (obj.Name.Contains(" ") && space == false)
                                space = true;
                            this.ffsTestTraining.TestSet.Add(obj);
                        }
                        this.bTestTrainingChanged = false;
                    }
                }
            }
            if (ffs != null)
            {
                ffs.Classifier = AppConfiguration.Classifier;
                ffs.FeatureHeader = AppConfiguration.FeatureHeader;
                ffs.TmpTrainingSetFile = null;
                ffs.TmpTestSetFile = null;
                ffs.WorkingDirectory = null;
            }
            if (space == true)
               MessageBox.Show("Filenames with spaces will have underscores in results files",
                    "Spaces in File Name!", MessageBoxButtons.OK, MessageBoxIcon.Information);
            return new Tuple<FeatureFileSet, string>(ffs, msg);
        }
        public int IndexOf(ImageObject obj)
        {
            return this.Items.IndexOfKey(obj.FileName);
        }
        public void Insert(int idx, ImageObject obj)
        {
            ListViewItem itm = this.Items.Insert(idx, obj.Name);
            itm.Name = obj.FileName;
            itm.SubItems.Add(obj.ClassName);
            itm.Tag = obj;
            this.bLeave1OutChanged = true;
            this.bTestTrainingChanged = true;
        }
        public void InvertChecked()
        {
            foreach (ListViewItem itm in this.Items)
                itm.Checked = !itm.Checked;
            this.bTestTrainingChanged = true;
        }
        private void OnClassListChanged()
        {
            this.popmnuClasses.Items.Clear();
            foreach (string s in AppConfiguration.ClassList)
                this.popmnuClasses.Items.Add(s);
        }
        protected override void OnItemCheck(ItemCheckEventArgs ice)
        {
            base.OnItemCheck(ice);
            this.bTestTrainingChanged = true;
        }
        protected override void OnItemSelectionChanged(ListViewItemSelectionChangedEventArgs e)
        {
            base.OnItemSelectionChanged(e);
            if (e.IsSelected)
            {
                e.Item.BackColor = SystemColors.Highlight;
                e.Item.ForeColor = Color.White;
            }
            else
            {
                e.Item.BackColor = Color.Transparent;
                e.Item.ForeColor = Color.Black;
            }
        }
        protected override void OnKeyDown(KeyEventArgs e)
        {
            switch (e.KeyCode)
            {
            case Keys.A:
                if (e.Control)
                {
                    e.Handled = true;
                    foreach (ListViewItem itm in this.Items)
                        itm.Selected = true;
                }
                break;
            case Keys.Delete:
                e.Handled = true;
                if (this.DeleteKeyPressed != null)
                    this.DeleteKeyPressed();
                break;
            }
            base.OnKeyDown(e);
        }
        public void Randomize()
        {
            Random rdm = new Random();
            while (this.CheckedItems.Count > 0)
                this.CheckedItems[0].Checked = false;
            while (this.CheckedItems.Count < (this.Items.Count / 2))
                this.Items[rdm.Next(this.Items.Count)].Checked = true;
            this.bTestTrainingChanged = true;
        }
        public bool Remove(ImageObject obj)
        {
            bool success = false;
            int idx = this.IndexOf(obj);
            if (idx != -1)
            {
                this.RemoveAt(idx);
                success = true;
            }
            return success;
        }
        public void RemoveAt(int idx)
        {
            if ((idx >= 0) && (idx < this.Count))
            {
                this.Items.RemoveAt(idx);
                this.bLeave1OutChanged = true;
                this.bTestTrainingChanged = true;
            }
        }
        public void RemoveSelected()
        {
            if (this.SelectedItems.Count > 0)
            {
                ListViewItem[] itms = new ListViewItem[this.SelectedItems.Count];
                this.SelectedItems.CopyTo(itms, 0);
                foreach (ListViewItem itm in itms)
                    this.Items.Remove(itm);
                this.bLeave1OutChanged = true;
                this.bTestTrainingChanged = true;
            }
        }
        public void ReSort()
        {
            this.ListViewItemSorter = new ListViewItemComparer(this.nSortCol);
        }
        protected override void WndProc(ref Message m)
        {
            switch (m.Msg)
            {
            case 0x0001: // WM_CREATE
                AppConfiguration.ClassListChanged += this.OnClassListChanged;
                OnClassListChanged();
                break;
            case 0x0002: // WM_DESTROY
                AppConfiguration.ClassListChanged -= this.OnClassListChanged;
                break;
            }
            base.WndProc(ref m);
        }

        public ImageObject this[int idx]
        {
            get
            {
                ImageObject obj = null;
                if ((idx >= 0) && (idx < this.Count))
                    obj = (ImageObject)this.Items[idx].Tag;
                return obj;
            }
            set { this.Insert(idx, value); }
        }
        public ImageObject this[string key]
        {
            get
            {
                ImageObject obj = null;
                int idx = this.Items.IndexOfKey(key);
                if (idx != -1)
                    obj = this[idx];
                return obj;
            }
        }
        [DefaultValue(1)]
        public int SortColumn
        {
            get { return this.nSortCol; }
            set
            {
                this.nSortCol = value;
                ReSort();
            }
        }
        [Browsable(false), DefaultValue(null)]
        public SelectedObjectList SelectedObjects
        {
            get
            {
                if (this.listSelectedObjects == null)
                    this.listSelectedObjects = new SelectedObjectList(this);
                return this.listSelectedObjects;
            }
        }
        [Browsable(false), DefaultValue(null)]
        public CheckedObjectEnumerator TestSetObjects
        {
            get
            {
                if (this.enumTestSet == null)
                    this.enumTestSet = new CheckedObjectEnumerator(this);
                return this.enumTestSet;
            }
        }
        [Browsable(false), DefaultValue(null)]
        public NotCheckedObjectEnumerator TrainingSetObjects
        {
            get
            {
                if (this.enumTrainingSet == null)
                    this.enumTrainingSet = new NotCheckedObjectEnumerator(this);
                return this.enumTrainingSet;
            }
        }
        public int Count { get { return this.Items.Count; } }
        public bool IsReadOnly { get { return false; } }
    }
    // Implements the manual sorting of items by columns.
    class ListViewItemComparer : IComparer
    {
        private int col;
        public ListViewItemComparer() { col = 0; }
        public ListViewItemComparer(int column) { col = column; }
        public int Compare(object x, object y)
        {
            ListViewItem itmX = (ListViewItem)x;
            ListViewItem itmY = (ListViewItem)y;
            if ((itmX.SubItems.Count > col) && (itmY.SubItems.Count > col))
            {
                return String.Compare(itmX.SubItems[col].Text, itmY.SubItems[col].Text);
            }
            return 0;
        }
    }
    public class CheckedObjectEnumerator : IEnumerable<ImageObject>
    {
        private FepcListView owner = null;
        public CheckedObjectEnumerator(FepcListView lv) { this.owner = lv; }
        IEnumerator IEnumerable.GetEnumerator()
        {
            return this.GetEnumerator();
        }
        public IEnumerator<ImageObject> GetEnumerator()
        {
            foreach (ListViewItem itm in this.owner.CheckedItems)
                yield return (ImageObject)itm.Tag;
        }
        public int Count { get { return this.owner.CheckedItems.Count; } }
    }
    public class NotCheckedObjectEnumerator : IEnumerable<ImageObject>
    {
        private FepcListView owner = null;
        public NotCheckedObjectEnumerator(FepcListView lv) { this.owner = lv; }
        IEnumerator IEnumerable.GetEnumerator()
        {
            return this.GetEnumerator();
        }
        public IEnumerator<ImageObject> GetEnumerator()
        {
            foreach (ListViewItem itm in this.owner.Items)
            {
                if (!itm.Checked)
                    yield return (ImageObject)itm.Tag;
            }
        }
        public int Count { get { return this.owner.Items.Count - this.owner.CheckedItems.Count; } }
    }
    public class SelectedObjectList : IList<ImageObject>
    {
        private FepcListView owner = null;
        public SelectedObjectList(FepcListView lv) { this.owner = lv; }
        public void Add(ImageObject obj)
        {
            int idx = this.owner.Items.IndexOfKey(obj.FileName);
            if (idx != -1)
                this.owner.Items[idx].Selected = true;
        }
        public void Clear()
        {
            this.owner.SelectedItems.Clear();
        }
        public bool Contains(ImageObject obj)
        {
            return this.owner.SelectedItems.ContainsKey(obj.FileName);
        }
        public void CopyTo(ImageObject[] dest, int idx)
        {
            foreach (ImageObject obj in this)
                dest[idx++] = obj;
        }
        IEnumerator IEnumerable.GetEnumerator()
        {
            return this.GetEnumerator();
        }
        public IEnumerator<ImageObject> GetEnumerator()
        {
            foreach (ListViewItem itm in this.owner.SelectedItems)
                yield return (ImageObject)itm.Tag;
        }
        public int IndexOf(ImageObject obj)
        {
            return this.owner.SelectedItems.IndexOfKey(obj.FileName);
        }
        public void Insert(int idx, ImageObject obj)
        {
            throw new NotSupportedException();
        }
        public bool Remove(ImageObject obj)
        {
            bool success = false;
            int idx = this.owner.SelectedItems.IndexOfKey(obj.FileName);
            if (idx != -1)
            {
                this.owner.SelectedItems[idx].Selected = false;
                success = true;
            }
            return success;
        }
        public void RemoveAt(int idx)
        {
            if ((idx >= 0) && (idx < this.Count))
                this.owner.SelectedItems[idx].Selected = false;
        }

        public ImageObject this[int idx]
        {
            get
            {
                ImageObject obj = null;
                if ((idx >= 0) && (idx < this.Count))
                    obj = (ImageObject)this.owner.SelectedItems[idx].Tag;
                return obj;
            }
            set { throw new NotSupportedException(); }
        }
        public ImageObject this[string key]
        {
            get
            {
                ImageObject obj = null;
                int idx = this.owner.SelectedItems.IndexOfKey(key);
                if (idx != -1)
                    obj = this[idx];
                return obj;
            }
        }
        public int Count { get { return this.owner.SelectedItems.Count; } }
        public bool IsReadOnly { get { return true; } }
    }
}
