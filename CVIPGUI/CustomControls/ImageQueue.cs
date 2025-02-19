/*''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' ======================================================================
' Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
' ======================================================================
'
'             File Name: ImageQueue.cs
'           Description: Contains the controls and code
'                        for ImageQueue class
'         Related Files: ViewerForm.cs
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
using System.Collections;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Text;
using System.Windows.Forms;

namespace CVIPGUI
{
    public delegate void GenericStateChange();
    public delegate void ViewerChanged(ViewerForm viewer);

    public partial class ImageQueue : UserControl, IEnumerable<ViewerForm>
    {
        public ImageQueue()
        {
            InitializeComponent();
            this.SelectedViewerChanged += this.OnSelectedViewerChanged;
            this.ViewerCollectionChanged += this.OnViewerCollectionChanged;
        }
        private ViewerForm Add(ViewerForm viewer)
        {
            viewer.MdiParent = this.ParentForm;
            viewer.Show();
            this.lvViewers.Add(viewer);
            if (!this.chkLockInput.Checked)
                this.SelectedViewer = viewer;
            viewer.BringToFront();
            return viewer;
        }
        public ViewerForm Add(int image, string name)
        {
            return this.Add(new ViewerForm(image, name));
        }
        public ViewerForm Add(int image, string name, LogRemap remap)
        {
            return this.Add(new ViewerForm(image, name, remap));
        }
        public ViewerForm Add(int image, string name, int wParam, string compressedFileName)
        {
            return this.Add(new ViewerForm(image, name, wParam, compressedFileName));
        }
        public void AddFiles(string[] filenames)
        {
            this.Cursor = Cursors.WaitCursor;
            foreach (string name in filenames)
            {
                FileInfo fi = new FileInfo(name);
                ViewerForm viewer = this.lvViewers[fi.FullName];
                if (viewer == null)
                {
                    int img;
                    if (fi.Exists && ((img = CvipOp.Read_Image(fi.FullName)) != 0))
                    {
                        viewer = new ViewerForm(img, fi.Name);
                        viewer.Name = fi.FullName;
                        this.Add(viewer);
                    }
                }
                else
                {
                    if (!this.chkLockInput.Checked)
                        this.SelectedViewer = viewer;
                    viewer.BringToFront();
                }
            }
            this.Cursor = Cursors.Default;
        }
        private void btnDelete_Click(object sender, EventArgs e)
        {
            this.lvViewers.RemoveSelected();
        }
        private void btnDeleteAll_Click(object sender, EventArgs e)
        {
            this.RemoveAll();
        }
        IEnumerator IEnumerable.GetEnumerator()
        {
            return this.GetEnumerator();
        }
        public IEnumerator<ViewerForm> GetEnumerator()
        {
            return this.lvViewers.GetEnumerator();
        }
        public void OnKeyboardCommand(KeyPressEventArgs e)
        {
            switch (e.KeyChar)
            {
            case 'e':
            case 'E':
                this.lvViewers.HistEQSelected();
                e.Handled = true;
                break;

            case 'h':
            case 'H':
                this.lvViewers.FlipSelected(false);
                e.Handled = true;
                break;

            case 'q':
            case 'Q':
                this.lvViewers.HideSelected();
                e.Handled = true;
                break;

            case 'n':
                this.lvViewers.RestoreSelected();
                e.Handled = true;
                break;

            case 'N':
                this.lvViewers.RestoreResizeSelected();
                e.Handled = true;
                break;

            case 't':
                this.lvViewers.RotateSelected(false);
                e.Handled = true;
                break;

            case 'T':
                this.lvViewers.RotateSelected(true);
                e.Handled = true;
                break;

            case 'v':
            case 'V':
                this.lvViewers.FlipSelected(true);
                e.Handled = true;
                break;
            }
        }
        protected override void OnPaddingChanged(EventArgs e)
        {
            base.OnPaddingChanged(e);
            this.pnlSplitterTop.Height = this.Padding.Top;
            this.pnlSplitterBottom.Height = this.Padding.Bottom;
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
                this.splitter.ListViewCtrl = this.lvViewers;
                this.Tag = null;
            }
        }
        private void OnSelectedViewerChanged(ViewerForm viewer)
        {
            this.btnDelete.Enabled = (this.lvViewers.SelectedViewer != null);
              
        }
        private void OnViewerCollectionChanged()
        {
            this.btnDeleteAll.Enabled = (this.lvViewers.Count > 0);
        }
        public void Remove(ViewerForm viewer)
        {
            this.lvViewers.Remove(viewer);
        }
        public bool RemoveAll()
        {
            if (this.Count > 0)
            {
                string msg = "Images that have not been saved will be lost. Really Delete All?";
                string title = "Delete all Images";
                MessageBoxButtons btns = MessageBoxButtons.YesNo;
                MessageBoxIcon icon = MessageBoxIcon.Warning;
                if (MessageBox.Show(msg, title, btns, icon) == DialogResult.No)
                    return false;
            }
            this.lvViewers.RemoveAll();
            return true;
        }
        public void RemoveSelected()
        {
            this.lvViewers.RemoveSelected();
        }
        public ViewerForm this[int idx]
        {
            get { return this.lvViewers[idx]; }
        }
        public ViewerForm this[string name]
        {
            get { return this.lvViewers[name]; }
        }
        public int Count
        {
            get { return (this.lvViewers.Count); }
        }
        [Browsable(false), DesignerSerializationVisibility(DesignerSerializationVisibility.Hidden)]
        public ViewerForm SelectedViewer
        {
            get { return (this.lvViewers.SelectedViewer); }
            set { this.lvViewers.SelectedViewer = value; }
        }
        [Browsable(false)]
        public SelectedViewerCollection SelectedViewers
        {
            get { return this.lvViewers.SelectedViewers; }
        }
        public event ViewerChanged SelectedViewerChanged
        {
            add { this.lvViewers.SelectedViewers.SelectedViewerChanged += value; }
            remove { this.lvViewers.SelectedViewers.SelectedViewerChanged -= value; }
        }
        public event GenericStateChange ViewerCollectionChanged
        {
            add { this.lvViewers.Viewers.ViewerCollectionChanged += value; }
            remove { this.lvViewers.Viewers.ViewerCollectionChanged -= value; }
        }
    }
    public class ImageQueueListView : ListView, IEnumerable<ViewerForm>
    {
        private ImageQueue iqOwner;
        private SelectedViewerCollection collectSelectedViewers;
        private ViewerCollection collectViewers;
        private int counterUpdate = 0;

        public ImageQueueListView()
        {
            this.SetStyle(ControlStyles.AllPaintingInWmPaint | ControlStyles.OptimizedDoubleBuffer, true);
        }
        public void Add(ViewerForm viewer)
        {
            this.Viewers.Add(viewer);
            this.SelectViewer();
        }
        IEnumerator IEnumerable.GetEnumerator()
        {
            return this.GetEnumerator();
        }
        public IEnumerator<ViewerForm> GetEnumerator()
        {
            return this.Viewers.GetEnumerator();
        }
        public void FlipSelected(bool direction)
        {
            foreach (ViewerForm viewer in this.SelectedViewers)
            {
                viewer.FlipImage(direction);
            }
        }
        public void HideSelected()
        {
            foreach (ImageQueueListItem itm in this.SelectedItems)
            {
                itm.Selected = itm.Viewer.Visible = false;
            }
            this.SelectViewer();
        }
        public void HistEQSelected()
        {
            foreach (ViewerForm viewer in this.SelectedViewers)
            {
                viewer.HistEQImage();
            }
        }
        protected override void OnItemSelectionChanged(ListViewItemSelectionChangedEventArgs e)
        {
            base.OnItemSelectionChanged(e);
            ImageQueueListItem item = e.Item as ImageQueueListItem;
            ViewerForm viewer = item.Viewer;
            if (e.IsSelected)
            {
                item.BackColor = SystemColors.Highlight;
                item.ForeColor = Color.White;
                this.SelectedViewers.Add(viewer);
            }
            else
            {
                item.BackColor = Color.Transparent;
                item.ForeColor = Color.Black;
                this.SelectedViewers.Remove(viewer);
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
                    {
                        itm.Selected = true;
                    }
                }
                break;

            case Keys.Delete:
                this.RemoveSelected();
                break;
            }
            base.OnKeyDown(e);
        }
        protected override void OnKeyPress(KeyPressEventArgs e)
        {
            this.ImageQueue.OnKeyboardCommand(e);
            base.OnKeyPress(e);
        }
        public void Remove(ViewerForm viewer)
        {
            this.Viewers.Remove(viewer);
            this.SelectViewer();
        }
        public void RemoveAll()
        {
            this.Viewers.Clear();
        }
        public void RemoveSelected()
        {
            if (this.SelectedViewers.Count > 0)
            {
                ViewerForm[] viewers = new ViewerForm[this.SelectedViewers.Count];
                this.SelectedViewers.CopyTo(viewers, 0);
                this.SelectedViewers.Clear();
                this.Viewers.Remove(viewers);
                this.SelectViewer();
            }
        }
        public void RestoreSelected()
        {
            foreach (ViewerForm viewer in this.SelectedViewers)
            {
                viewer.RestoreImage();
            }
        }
        public void RestoreResizeSelected()
        {
            foreach (ViewerForm viewer in this.SelectedViewers)
            {
                viewer.RestoreResizeImage();
            }
        }
        public void RotateSelected(bool direction)
        {
            foreach (ViewerForm viewer in this.SelectedViewers)
            {
                viewer.RotateImage(direction);
            }
        }
        private void SelectViewer()
        {
            if ((this.SelectedViewer == null) && (this.Viewers.Count > 0))
            {
                ViewerForm viewer = this.MainForm.ActiveMdiChild as ViewerForm;
                if (viewer == null)
                {
                    foreach (ViewerForm v in this)
                    {
                        if (v.Visible)
                        {
                            viewer = v;
                            break;
                        }
                    }
                }
                if (viewer != null)
                    this.SelectedViewer = viewer;
            }
        }
        protected override void WndProc(ref Message m)
        {
            int x, y;
            switch ((WM)m.Msg)
            {
            case WM.ERASEBKGND:
                if (InUpdate)
                    return;
                break;

            case WM.MOUSEMOVE:
                if (this.Cursor != Cursors.WaitCursor)
                {
                    x = ((int)m.LParam & 0xffff);
                    y = (((int)m.LParam >> 0x10) & 0xffff);
                    this.Cursor = (GetItemAt(x, y) != null)
                        ? Cursors.Hand
                        : Cursors.Default;
                }

                break;

            case WM.LBUTTONDOWN:
            case WM.LBUTTONDBLCLK:
            case WM.RBUTTONDOWN:
            case WM.RBUTTONDBLCLK:
                x = ((int)m.LParam & 0xffff);
                y = (((int)m.LParam >> 0x10) & 0xffff);
                if (GetItemAt(x, y) == null)
                {
                    m.Msg = (int)WM.NULL;
                    this.Focus();
                }
                break;

            case WM.SIZE:
                x = ((int)m.LParam & 0xffff);
                if (this.Viewers.MaxLabelWidth > x)
                    x = this.Viewers.MaxLabelWidth;
                if (this.ColumnWidth != x)
                    this.ColumnWidth = x;
                break;
            }
            base.WndProc(ref m);
        }
        public ViewerForm this[int idx]
        {
            get { return this.Viewers[idx]; }
        }
        public ViewerForm this[string name]
        {
            get { return this.Viewers[name]; }
        }
        [DefaultValue(0), DesignerSerializationVisibility(DesignerSerializationVisibility.Hidden)]
        public int ColumnWidth
        {
            get { return (this.Columns[0].Width); }
            set { this.Columns[0].Width = value; }
        }
        public int Count
        {
            get { return (this.Viewers.Count); }
        }
        private ImageQueue ImageQueue
        {
            get
            {
                if (this.iqOwner == null)
                {
                    Control parent = this.Parent;
                    while (!(parent is ImageQueue))
                    {
                        parent = parent.Parent;
                    }
                    this.iqOwner = parent as ImageQueue;
                }
                return this.iqOwner;
            }
        }
        private MainForm MainForm
        {
            get { return this.ImageQueue.ParentForm as MainForm; }
        }
        [Browsable(false), DesignerSerializationVisibility(DesignerSerializationVisibility.Hidden)]
        public bool InUpdate
        {
            get { return (counterUpdate != 0); }
            set
            {
                if (value)
                {
                    if (counterUpdate++ == 0)
                    {
                        this.Cursor = Cursors.WaitCursor;
                        BeginUpdate();
                    }
                }
                else
                {
                    if (--counterUpdate == 0)
                    {
                        EndUpdate();
                        this.Cursor = Cursors.Default;
                    }
                }
            }
        }
        [Browsable(false), DefaultValue(null), DesignerSerializationVisibility(DesignerSerializationVisibility.Hidden)]
        public ViewerForm SelectedViewer
        {
            get { return this.SelectedViewers.SelectedViewer; }
            set { this.SelectedViewers.SelectedViewer = value; }
        }
        [Browsable(false), DefaultValue(null)]
        public SelectedViewerCollection SelectedViewers
        {
            get
            {
                if (this.collectSelectedViewers == null)
                {
                    this.collectSelectedViewers = new SelectedViewerCollection(this);
                }
                return this.collectSelectedViewers;
            }
        }
        [Browsable(false), DefaultValue(null)]
        public ViewerCollection Viewers
        {
            get
            {
                if (this.collectViewers == null)
                {
                    this.collectViewers = new ViewerCollection(this);
                }
                return this.collectViewers;
            }
        }
    }
    public class ImageQueueSplitter : System.Windows.Forms.Splitter
    {
        ImageQueueListView buddy = null;

        protected override void OnSplitterMoving(SplitterEventArgs sevent)
        {
            if ((buddy != null) && !buddy.InUpdate)
            {
                buddy.InUpdate = true;
                buddy.ColumnWidth = 0;
            }
            base.OnSplitterMoving(sevent);
        }
        protected override void OnSplitterMoved(SplitterEventArgs sevent)
        {
            if ((buddy != null) && buddy.InUpdate)
            {
                buddy.InUpdate = false;
            }
            base.OnSplitterMoved(sevent);
        }
        [Browsable(false), DefaultValue(null), DesignerSerializationVisibility(DesignerSerializationVisibility.Hidden)]
        public ImageQueueListView ListViewCtrl
        {
            get { return (this.buddy); }
            set { this.buddy = value; }
        }
    }
    public class ImageQueueListItem : ListViewItem
    {
        private int widthLabel = 0;

        public int LabelWidth
        {
            get
            {
                if ((this.widthLabel == 0) &&
                    !string.IsNullOrEmpty(this.Text) &&
                    (this.ListView != null))
                {
                    Graphics g = this.ListView.CreateGraphics();
                    this.widthLabel = (int)(g.MeasureString(this.Text, this.Font).Width + 5.5F);
                    g.Dispose();
                }

                return (this.widthLabel);
            }
        }
        [Browsable(false), DefaultValue(null), DesignerSerializationVisibility(DesignerSerializationVisibility.Hidden)]
        public ViewerForm Viewer
        {
            get { return (ViewerForm)this.Tag; }
            set
            {
                if ((this.Viewer != value) && ((this.Tag = value) != null))
                {
                    this.Viewer.ListItem = this;
                    this.Name = this.Viewer.Name;
                    this.Text = this.Viewer.Text;
                    if (System.IO.File.Exists(this.Name))
                    {
                        this.ToolTipText = this.Name;
                    }
                }
            }
        }
    }
    public class ViewerCollection : IList<ViewerForm>, ICollection<ViewerForm>, IEnumerable<ViewerForm>
    {
        private ImageQueueListView owner;
        private int widthMaxLabel = 0;
        public event GenericStateChange ViewerCollectionChanged;

        public ViewerCollection(ImageQueueListView owner)
        {
            this.owner = owner;
        }
        public void Add(ViewerForm viewer)
        {
            if (viewer == null)
            {
                throw new ArgumentException("Parameter cannot be null.");
            }
            if (this.Contains(viewer))
            {
                throw new ArgumentException(viewer.Name + " already exists in this collection.");
            }
            viewer.ListItem = new ImageQueueListItem();
            this.owner.Items.Add(viewer.ListItem);
            if (viewer.ListItem.LabelWidth > this.MaxLabelWidth)
            {
                this.widthMaxLabel = viewer.ListItem.LabelWidth;

                if (owner.ColumnWidth < this.MaxLabelWidth)
                {
                    owner.ColumnWidth = this.MaxLabelWidth;
                }
            }
            this.owner.Update();
            if (this.ViewerCollectionChanged != null)
            {
                this.ViewerCollectionChanged();
            }
        }
        public void Clear()
        {
            foreach (ImageQueueListItem itm in this.owner.Items)
            {
                itm.Viewer.ListItem = null;
                itm.Viewer.Close();
            }
            this.owner.SelectedItems.Clear();
            this.owner.Items.Clear();
            this.widthMaxLabel = 0;
            if (owner.ColumnWidth > owner.ClientSize.Width)
            {
                owner.ColumnWidth = owner.ClientSize.Width;
            }
            if (this.ViewerCollectionChanged != null)
            {
                this.ViewerCollectionChanged();
            }
        }
        public bool Contains(ViewerForm viewer)
        {
            return (this.IndexOf(viewer) != -1);
        }
        public void CopyTo(ViewerForm[] dest, int index)
        {
            foreach (ViewerForm viewer in this)
            {
                dest[index++] = viewer;
            }
        }
        IEnumerator IEnumerable.GetEnumerator()
        {
            return this.GetEnumerator();
        }
        public IEnumerator<ViewerForm> GetEnumerator()
        {
            foreach (ImageQueueListItem itm in this.owner.Items)
            {
                yield return itm.Viewer;
            }
        }
        public int IndexOf(ViewerForm viewer)
        {
            return this.owner.Items.IndexOf(viewer.ListItem);
        }
        public void Insert(int index, ViewerForm viewer)
        {
            viewer.ListItem = new ImageQueueListItem();
            this.owner.Items.Insert(index, viewer.ListItem);
            if (viewer.ListItem.LabelWidth > this.MaxLabelWidth)
            {
                this.widthMaxLabel = viewer.ListItem.LabelWidth;
                if (owner.ColumnWidth < this.MaxLabelWidth)
                {
                    owner.ColumnWidth = this.MaxLabelWidth;
                }
            }
            if (this.ViewerCollectionChanged != null)
            {
                this.ViewerCollectionChanged();
            }
        }
        public bool Remove(ViewerForm viewer)
        {
            ImageQueueListItem item = viewer.ListItem;
            viewer.ListItem = null;
            viewer.Close();
            this.owner.SelectedViewers.Remove(viewer);
            this.owner.Items.Remove(item);
            if (item.LabelWidth == this.MaxLabelWidth)
            {
                this.widthMaxLabel = 0;
                foreach (ImageQueueListItem li in owner.Items)
                {
                    if (li.LabelWidth > this.MaxLabelWidth)
                    {
                        this.widthMaxLabel = li.LabelWidth;
                    }
                }
                int width = this.owner.ClientSize.Width;
                if (this.MaxLabelWidth > width)
                {
                    width = this.MaxLabelWidth;
                }
                if (this.owner.ColumnWidth > width)
                {
                    this.owner.ColumnWidth = width;
                }
            }
            if (this.ViewerCollectionChanged != null)
            {
                this.ViewerCollectionChanged();
            }
            return (true);
        }
        public void Remove(ViewerForm[] viewers)
        {
            bool maxchanged = false;
            ImageQueueListItem item;

            this.owner.SelectedViewers.Remove(viewers);
            foreach (ViewerForm viewer in viewers)
            {
                item = viewer.ListItem;
                viewer.ListItem = null;
                viewer.Close();
                this.owner.Items.Remove(item);
                if (item.LabelWidth == this.MaxLabelWidth)
                {
                    maxchanged = true;
                }
            }
            if (maxchanged)
            {
                this.widthMaxLabel = 0;
                foreach (ImageQueueListItem li in owner.Items)
                {
                    if (li.LabelWidth > this.MaxLabelWidth)
                    {
                        this.widthMaxLabel = li.LabelWidth;
                    }
                }
                int width = this.owner.ClientSize.Width;
                if (this.MaxLabelWidth > width)
                {
                    width = this.MaxLabelWidth;
                }
                if (this.owner.ColumnWidth > width)
                {
                    this.owner.ColumnWidth = width;
                }
            }
            if (this.ViewerCollectionChanged != null)
            {
                this.ViewerCollectionChanged();
            }
        }
        public void RemoveAt(int index)
        {
            Remove(this[index]);
        }
        public ViewerForm this[int idx]
        {
            get
            {
                ImageQueueListItem item = this.owner.Items[idx] as ImageQueueListItem;
                ViewerForm viewer = null;

                if (item != null)
                {
                    viewer = item.Viewer;
                }
                return (viewer);
            }
            set
            {
                if ((idx >= 0) && (idx < this.owner.Items.Count))
                {
                    value.ListItem = new ImageQueueListItem();
                    this.owner.Items[idx] = value.ListItem;
                }
            }
        }
        public ViewerForm this[string name]
        {
            get
            {
                foreach (ViewerForm viewer in this)
                {
                    if (viewer.Name == name)
                    {
                        return viewer;
                    }
                }
                return null;
            }
        }
        public int Count
        {
            get { return this.owner.Items.Count; }
        }
        public bool IsReadOnly
        {
            get { return false; }
        }
        public int MaxLabelWidth
        {
            get { return (this.widthMaxLabel); }
        }
    }
    public class SelectedViewerCollection : IList<ViewerForm>, ICollection<ViewerForm>, IEnumerable<ViewerForm>
    {
        private ListView lvOwner;
        private Queue<ViewerForm> qViewers = new Queue<ViewerForm>();
        public event ViewerChanged SelectedViewerChanged;

        public SelectedViewerCollection(ListView owner)
        {
            this.lvOwner = owner;
        }
        public void Add(ViewerForm viewer)
        {
            if (viewer == null)
            {
                throw new ArgumentException("Parameter cannot be null.");
            }
            if (this.qViewers.Contains(viewer))
            {
                throw new ArgumentException(viewer.Name + " already exists in this collection.");
            }
            if (viewer.ListItem.Selected == false)
            {
                viewer.ListItem.Selected = true;
            }
            else
            {
                this.qViewers.Enqueue(viewer);
                if (this.qViewers.Count == 1)
                {
                    viewer.ListItem.EnsureVisible();
                    viewer.Visible = true;
                    viewer.BringToFront();
                    if (this.SelectedViewerChanged != null)
                    {
                        this.SelectedViewerChanged(viewer);
                    }
                }
            }
        }
        public void Clear()
        {
            if (this.Count > 0)
            {
                this.qViewers.Clear();
                this.lvOwner.SelectedItems.Clear();
                if (this.SelectedViewerChanged != null)
                {
                    this.SelectedViewerChanged(null);
                }
            }
        }
        public bool Contains(ViewerForm viewer)
        {
            return (this.IndexOf(viewer) != -1);
        }
        public void CopyTo(ViewerForm[] dest, int index)
        {
            foreach (ViewerForm viewer in this)
            {
                dest[index++] = viewer;
            }
        }
        IEnumerator IEnumerable.GetEnumerator()
        {
            return this.GetEnumerator();
        }
        public IEnumerator<ViewerForm> GetEnumerator()
        {
            foreach (ImageQueueListItem itm in this.lvOwner.SelectedItems)
            {
                yield return itm.Viewer;
            }
        }
        public int IndexOf(ViewerForm viewer)
        {
            return this.lvOwner.SelectedItems.IndexOf(viewer.ListItem);
        }
        public void Insert(int index, ViewerForm viewer)
        {
            throw new NotSupportedException();
        }
        public bool Remove(ViewerForm viewer)
        {
            if ((viewer.ListItem != null) && (viewer.ListItem.Selected == true))
            {
                viewer.ListItem.Selected = false;
            }
            else if (this.qViewers.Contains(viewer))
            {
                int count = this.qViewers.Count;
                ViewerForm current = null;
                ViewerForm previous = this.SelectedViewer;
                for (int i = 0; i < count; i++)
                {
                    current = this.qViewers.Dequeue();
                    if (current != viewer)
                    {
                        this.qViewers.Enqueue(current);
                    }
                }
                if ((current = this.SelectedViewer) != previous)
                {
                    if (current != null)
                    {
                        current.ListItem.EnsureVisible();
                        current.BringToFront();
                    }
                    if (this.SelectedViewerChanged != null)
                    {
                        this.SelectedViewerChanged(current);
                    }
                }
            }
            return (true);
        }
        public void Remove(ViewerForm[] viewers)
        {
            ViewerForm current = null;
            ViewerForm previous = this.SelectedViewer;
            foreach (ViewerForm viewer in viewers)
            {
                if ((viewer.ListItem != null) && (viewer.ListItem.Selected == true))
                {
                    viewer.ListItem.Selected = false;
                }
                else if (this.qViewers.Contains(viewer))
                {
                    int count = this.qViewers.Count;

                    for (int i = 0; i < count; i++)
                    {
                        current = this.qViewers.Dequeue();

                        if (current != viewer)
                        {
                            this.qViewers.Enqueue(current);
                        }
                    }
                }
            }
            if ((current = this.SelectedViewer) != previous)
            {
                if (current != null)
                {
                    current.ListItem.EnsureVisible();
                    current.BringToFront();
                }
                if (this.SelectedViewerChanged != null)
                {
                    this.SelectedViewerChanged(current);
                }
            }
        }
        public void RemoveAt(int index)
        {
            Remove(this[index]);
        }
        public ViewerForm this[int idx]
        {
            get
            {
                ImageQueueListItem item = this.lvOwner.SelectedItems[idx] as ImageQueueListItem;
                ViewerForm viewer = null;

                if (item != null)
                {
                    viewer = item.Viewer;
                }
                return (viewer);
            }
            set { throw new NotSupportedException(); }
        }
        public ViewerForm this[string name]
        {
            get
            {
                foreach (ViewerForm viewer in this)
                {
                    if (viewer.Name == name)
                    {
                        return viewer;
                    }
                }
                return null;
            }
        }
        public int Count
        {
            get { return this.lvOwner.SelectedItems.Count; }
        }
        public bool IsReadOnly
        {
            get { return true; }
        }
        public ViewerForm SelectedViewer
        {
            get
            {
                ViewerForm selected = null;
                if (this.qViewers.Count > 0)
                {
                    selected = this.qViewers.Peek();
                }
                return selected;
            }
            set
            {
                this.qViewers.Clear();
                this.lvOwner.SelectedItems.Clear();
                if (value != null)
                {
                    value.ListItem.Selected = true;
                }
                else
                {
                    if (this.SelectedViewerChanged != null)
                    {
                        this.SelectedViewerChanged(null);
                    }
                }
            }
        }
    }
}
