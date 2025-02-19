/***************************************************************************
* =========================================================================
*
*			 CVIP_ATAT - Dr. Scott Umbaugh SIUE
* 
* =========================================================================
*
*             File Name: Image.cs 
*           Description: Gathers images into the images tab list view.
*   Initial Coding Date: June 6, 2006
*Last Modification Made: June 16, 2021
*  Programming Language: Visual Studio C#.NET 2019
*             Credit(s): Wenjun(Evan) Bian, Pelin Guvenc, Charles Stacey
*                        Southern Illinois University at Edwardsville
*
*		  Copyright (c): 2010-2021 SIUE - Scott Umbaugh
****************************************************************************/

using System;
using System.Collections;
using System.Windows.Forms;
using System.IO;

namespace CVIP_ATAT.Files
{
    class Images
    {
        CVIPATATForm CImageRef;

        ListViewItem objListView;
        int imageCount;

        public Images(CVIPATATForm reference)
        {
            CImageRef = reference;
        }

        public void image_btAddImage_Click()
        {
            try
            {
                CImageRef.AddImage.Title = "Add Images";
                CImageRef.AddImage.Filter =
                    "All Image Files|*.vip; *.jpeg; *.jpg; *.gif; *.bmp; *.pbm; *.pgm; *.ppm; *tif" +
                    "|Bitmap Files (*.bmp)|*.bmp" +
                    "|CVIPtools VIP Format (*.vip)|*.vip|Graphic Interchange Format (*.gif)|*.gif" +
                    "|JPEG File Interchange Format (*.jpg, *.jpeg)|*.jpg; *.jpeg" +
                    "|Tagged Image File Format (*.tif, *.tiff)|*.tif; *.tiff" +
                    "|Portable Network Graphics (*.png)| *.png" +
                    "|Portable Image File Format (*.pbm, *.pgm, *.ppm)|*.pbm; *.pgm; *.ppm";
                CImageRef.AddImage.FilterIndex = 1;
                CImageRef.AddImage.Multiselect = true;

                if (CImageRef.AddImage.ShowDialog() != DialogResult.Cancel)
                {
                    imageCount = CImageRef.AddImage.FileNames.Length;

                    for (int i = 0; i < imageCount; i++)
                    {
                        FileInfo imageinfo = new FileInfo(CImageRef.AddImage.FileNames[i]);
                        String fname = Path.GetFileName(imageinfo.ToString());
                        objListView = CImageRef.lvImage.Items.Add(imageinfo.Name);
                        objListView.Name = fname;
                        objListView.SubItems.Add(CImageRef.AddImage.FileNames[i]);
                        objListView.SubItems.Add("Null");
                        objListView.SubItems.Add("Null");
                    }
                }
                CImageRef.tbImageCount.Text = CImageRef.lvImage.Items.Count.ToString();
            }
            catch
            {
                MessageBox.Show("Crash detected while adding test images.", "Crash Detected.",
                  MessageBoxButtons.OK, MessageBoxIcon.Warning);
            }
        }

        public void image_btAddIdealImage_Click()
        {
            try
            {
                FolderBrowserDialog fbIdealImage = new FolderBrowserDialog();
                if (CImageRef.lvImage.Items.Count == 0)
                {
                    MessageBox.Show("First you have to add test images!", "Please add test images.",
                      MessageBoxButtons.OK, MessageBoxIcon.Warning);
                }
                else
                {
                    if (fbIdealImage.ShowDialog() == DialogResult.OK)
                    {
                        string selectedPath = fbIdealImage.SelectedPath;
                        string[] filepaths = Directory.GetFiles(selectedPath);
                        string imageName, idealImageName;
                        string fName = "";
                        bool missingIdealFlag = true;
                        ArrayList missingIdeals = new ArrayList();
                        int missingIdealCounter = 0;

                        for (int i = 0; i < CImageRef.lvImage.Items.Count; i++)
                        {
                            missingIdealFlag = true;
                            imageName = CImageRef.lvImage.Items[i].SubItems[1].Text;
                            fName = Path.GetFileName(imageName);
                            foreach (string filename in filepaths)
                            {
                                idealImageName = Path.GetFileNameWithoutExtension(filename);
                                imageName = Path.GetFileNameWithoutExtension(imageName);
                                if (idealImageName == imageName)
                                {
                                    //FileInfo imageinfo = new FileInfo(CImageRef.lvImage.Items[i].SubItems[1].Text);
                                    FileInfo idealimageinfo = new FileInfo(filename);
                                    CImageRef.lvImage.Items[i].SubItems[2].Text = idealimageinfo.Name;
                                    CImageRef.lvImage.Items[i].SubItems[3].Text = filename;
                                    missingIdealFlag = false;
                                    break;
                                }
                            }
                            if (missingIdealFlag && CImageRef.lvImage.Items[i].SubItems[2].Text == "Null")
                            {
                                missingIdeals.Add(Path.GetFileName(fName));
                                missingIdealCounter++;
                            }
                        }
                        if (missingIdealCounter != 0)
                        {
                            string missingIdealFiles = "";
                            MessageBox.Show("The Following Ideal Images Couldn't Be Found!", "Missing Ideal Images.", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                            for (int j = 0; j < missingIdealCounter; j++)
                            {
                                missingIdealFiles += missingIdeals[j].ToString() + "  ";
                            }
                            if (MessageBox.Show(missingIdealFiles + "\nWould you like to remove images from list?", "Missing Ideal Image.", MessageBoxButtons.YesNo, MessageBoxIcon.Exclamation) == DialogResult.Yes)
                            {
                                for (int j = missingIdealCounter - 1; j >= 0; j--)
                                {
                                    CImageRef.lvImage.Items.RemoveByKey(missingIdeals[j].ToString());
                                }
                                CImageRef.tbImageCount.Text = CImageRef.lvImage.Items.Count.ToString();
                            }
                        }
                    }
                }
            }
            catch
            {
                MessageBox.Show("Crash detected while adding ideal images.", "Crash Detected.",
                  MessageBoxButtons.OK, MessageBoxIcon.Warning);
            }
        }

        public void btDelAllIdealImage_Click()
        {
            if(CImageRef.lvImage.Items.Count == 0)
                MessageBox.Show("No ideal images added.", "Please add ideal images.", MessageBoxButtons.OK, MessageBoxIcon.Warning);
            else if (MessageBox.Show("Delete All Ideal Images?","Delete all ideal images", MessageBoxButtons.OKCancel, MessageBoxIcon.Exclamation)== DialogResult.OK)
            {
                for (int i = 0; i < CImageRef.lvImage.Items.Count; i++)
                {
                    CImageRef.lvImage.Items[i].SubItems[2].Text = "Null";
                    CImageRef.lvImage.Items[i].SubItems[3].Text = "Null";
                }
            }
        }

        public void btDelSelectedIdImage_Click()
        {
            if (CImageRef.lvImage.SelectedItems.Count == 0)
            {
                MessageBox.Show("No ideal images selected.", "Please Select ideal images.",MessageBoxButtons.OK, MessageBoxIcon.Warning);
            }
            else
            {
                ListView.SelectedIndexCollection indexes = CImageRef.lvImage.SelectedIndices;
                foreach (int index in indexes)
                {
                    CImageRef.lvImage.Items[index].SubItems[2].Text = "Null";
                    CImageRef.lvImage.Items[index].SubItems[3].Text = "Null";
                }
            }
        }

        public void image_btDeleteSelectedImage_Click()
        {
            if (CImageRef.lvImage.SelectedItems.Count == 0)
            {
                MessageBox.Show("No images selected.", "Please Select ideal images.",MessageBoxButtons.OK, MessageBoxIcon.Warning);
            }
            else
            {
                ListView.SelectedIndexCollection indexes = CImageRef.lvImage.SelectedIndices;
                for (int i = indexes.Count - 1; i >= 0; i--)
                {
                    CImageRef.lvImage.Items.Remove(CImageRef.lvImage.Items[indexes[i]]);
                }
            }
            CImageRef.tbImageCount.Text = CImageRef.lvImage.Items.Count.ToString();
        }

        public void image_btDeleteAllImage_Click()
        {
            if (CImageRef.lvImage.Items.Count == 0)
            {
                MessageBox.Show("No images added.", "Empty List",
                                  MessageBoxButtons.OK, MessageBoxIcon.Question);
            }
            else
            {
                if (MessageBox.Show("Do you really want to delete all the images in ListView?",
                        "Delete all images", MessageBoxButtons.OKCancel, MessageBoxIcon.Exclamation)
                         == DialogResult.OK)
                {
                    CImageRef.lvImage.Items.Clear();
                }
            }
            CImageRef.tbImageCount.Text = "0";
        }

        public void image_btAddFolder_Click()
        {
            string[] testFiles = null;
            string[] idealFiles = null;
            string[] extensions = { ".vip", ".jpeg", ".jpg", ".gif", ".bmp", ".pbm", ".pgm", ".ppm", ".tif", ".png" };
            bool imageFile, idealExists;
            string[] iNames = { "\\mask", "\\masks" };
            int i, e, t, error = 0;
            int iCheck; 

            try
            {
                if (CImageRef.folderBrowser.ShowDialog() == DialogResult.OK)
                {
                    //Clear Image Table
                    if (CImageRef.lvImage.Items.Count == 0)
                    { }
                    else
                        CImageRef.lvImage.Items.Clear();

                    //Get Test Directory
                    if (Directory.Exists(CImageRef.folderBrowser.SelectedPath))
                        testFiles = Directory.GetFiles(CImageRef.folderBrowser.SelectedPath);
                    else
                        error = 1;

                    iCheck = 0;
                    for(i = 0; i < 2; i++)
                    {
                        if (Directory.Exists(CImageRef.folderBrowser.SelectedPath + iNames[i]))
                        {
                            if (iCheck == 0)
                            {
                                idealFiles = Directory.GetFiles(CImageRef.folderBrowser.SelectedPath + iNames[i]);
                                iCheck++;
                            }
                            else if(iCheck == 1)
                            {
                                MessageBox.Show("Multiple subdirectories found with title mask, masks, Mask, and/or Masks. Only the first ideal folder identified will be used",
                                    "Multiple Ideal SubDirectories Found", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                                break;
                            }
                        }
                    }
                    if (iCheck == 0)
                        error = 2;

                    if (error == 0)
                    {
                        for (t = 0; t < testFiles.Length; t++)
                        {
                            //Check Extension
                            imageFile = false;
                            for (e = 0; e < extensions.Length; e++)
                            {
                                if (Path.GetExtension(testFiles[t]) == extensions[e])
                                {
                                    imageFile = true;
                                    break;
                                }
                            }

                            //Check Ideal Folder for Test Match
                            idealExists = false;
                            for (i = 0; i < idealFiles.Length; i++)
                            {
                                if (Path.GetFileNameWithoutExtension(testFiles[t]) == Path.GetFileNameWithoutExtension(idealFiles[i]))
                                {
                                    idealExists = true;
                                    break;
                                }
                            }

                            //Create new row if criteria is met.
                            if (imageFile == true && idealExists == true)
                            {
                                objListView = CImageRef.lvImage.Items.Add(Path.GetFileName(testFiles[t]));
                                objListView.SubItems.Add((testFiles[t]));
                                objListView.SubItems.Add(Path.GetFileName(idealFiles[i]));
                                objListView.SubItems.Add((idealFiles[i]));
                            }
                        }
                    }
                    else
                    {
                        if (error == 1)
                            MessageBox.Show("Directory does not exist.", "Choose another directory.", MessageBoxButtons.OK, MessageBoxIcon.Question);
                        else if (error == 2)
                            MessageBox.Show("Mask directory not included. Please add a directory titled \"Masks\" inside main directory", "Include a mask directory.", MessageBoxButtons.OK, MessageBoxIcon.Question);
                        else
                            MessageBox.Show("Unknown Error", "Unknown Error", MessageBoxButtons.OK, MessageBoxIcon.Question);
                    }
                }
                CImageRef.tbImageCount.Text = CImageRef.lvImage.Items.Count.ToString();
            }
            catch
            {
                MessageBox.Show("Crash detected while adding batch folder.", "Crash Detected.",
                  MessageBoxButtons.OK, MessageBoxIcon.Warning);
            }
        }
    }
}
