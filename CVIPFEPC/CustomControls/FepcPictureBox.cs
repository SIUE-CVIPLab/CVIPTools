/*''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' ======================================================================
' Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
' ======================================================================
'
'             File Name: FepcPictureBox.cs
'           Description: Contains the code for
'                        FepcPictureBox custom control
'         Related Files: MainForm.cs
'                        ImageObject.cs
'   Initial Coding Date: November 2006
'              Modified: March 2012
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

using CVIPFEPC.CvipFile;
using SERVERLib;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace CVIPFEPC.CustomControls
{
    public class FepcPictureBox : PictureBox
    {
        static private CVIPTools CvipOp = new CVIPTools();

        private ImageObject pObject = null;
        private int nCurrentView = 0;
        private int pImage = 0;
        private int pMask = 0;
        private int pMemDC = 0;

        int Make1Band(int img)
        {
            return CvipOp.Extract_Band(ref img, 1);
        }
        int Make3Band(int img)
        {
            int[] bands = { img, img, img };
            return CvipOp.Assemble_Bands(bands);
        }
        protected override void OnPaint(PaintEventArgs pe)
        {
            base.OnPaint(pe);
            if (this.pMemDC != 0)
            {
                IntPtr hdc = pe.Graphics.GetHdc();
                CvipOp.Show_DisplayImage(hdc.ToInt32(), this.pMemDC,
                    this.pObject.Width, this.pObject.Height,
                    this.pObject.Width, this.pObject.Height);
                pe.Graphics.ReleaseHdc();
            }
        }
        public void ShowImage()
        {
            this.nCurrentView = 0;
            if (this.pMemDC != 0)
            {
                CvipOp.Delete_DisplayImage(this.pMemDC);
                this.pMemDC = 0;
            }
            if (this.CvipImage != 0)
            {
                int img = CvipOp.CondRemap_Image(ref this.pImage, 0, 0, 255);
                Bitmap bmp = new Bitmap(this.pObject.Width, this.pObject.Height);
                Graphics g = Graphics.FromImage(bmp);
                g.Clear(Color.Black);
                IntPtr hdc = g.GetHdc();
                this.pMemDC = CvipOp.Render_DisplayImage(hdc.ToInt32(), ref img);
                g.ReleaseHdc(hdc);
                g.Dispose();
                CvipOp.Delete_Image(ref img);
            }
            Refresh();
        }
        public void ShowMask()
        {
            this.nCurrentView = 1;
            if (this.pMemDC != 0)
            {
                CvipOp.Delete_DisplayImage(this.pMemDC);
                this.pMemDC = 0;
            }
            if (this.CvipMask != 0)
            {
                int img = CvipOp.Duplicate_Image(ref this.pMask);
                Bitmap bmp = new Bitmap(this.pObject.Width, this.pObject.Height);
                Graphics g = Graphics.FromImage(bmp);
                g.Clear(Color.Black);
                IntPtr hdc = g.GetHdc();
                this.pMemDC = CvipOp.Render_DisplayImage(hdc.ToInt32(), ref img);
                g.ReleaseHdc(hdc);
                g.Dispose();
                CvipOp.Delete_Image(ref img);
            }
            Refresh();
        }
        public void ShowMaskedImage()
        {
            this.nCurrentView = 2;
            if (this.pMemDC != 0)
            {
                CvipOp.Delete_DisplayImage(this.pMemDC);
                this.pMemDC = 0;
            }
            if ((this.CvipImage != 0) && (this.CvipMask != 0))
            {
                int img = CvipOp.Duplicate_Image(ref this.pImage);
                int mask = CvipOp.Duplicate_Image(ref this.pMask);

                if (CvipOp.GetDataType_Image(ref img) != 0)
                    img = CvipOp.Remap_Image(ref img, 0, 0, 255);

                if (CvipOp.GetDataType_Image(ref mask) != 0)
                    mask = CvipOp.Remap_Image(ref mask, 0, 0, 255);

                img = CvipOp.And_Image(ref img, ref mask);
                CvipOp.Delete_Image(ref mask);

                Bitmap bmp = new Bitmap(this.pObject.Width, this.pObject.Height);
                Graphics g = Graphics.FromImage(bmp);
                g.Clear(Color.Black);
                IntPtr hdc = g.GetHdc();
                this.pMemDC = CvipOp.Render_DisplayImage(hdc.ToInt32(), ref img);
                g.ReleaseHdc(hdc);
                g.Dispose();
                CvipOp.Delete_Image(ref img);
            }
            Refresh();
        }

        [DefaultValue(null)]
        public ImageObject CurrentObject
        {
            get { return this.pObject; }
            set
            {
                if (this.pMemDC != 0)
                {
                    CvipOp.Delete_DisplayImage(this.pMemDC);
                    this.pMemDC = 0;
                }
                if (this.pImage != 0)
                {
                    CvipOp.Delete_Image(ref this.pImage);
                    this.pImage = 0;
                }
                if (this.pMask != 0)
                {
                    CvipOp.Delete_Image(ref this.pMask);
                    this.pMask = 0;
                }
                this.pObject = value;
                switch (this.nCurrentView)
                {
                case 0:
                    ShowImage();
                    break;
                case 1:
                    ShowMask();
                    break;
                case 2:
                    ShowMaskedImage();
                    break;
                }
            }
        }
        private int CvipImage
        {
            get
            {
                if ((this.pImage == 0) && (this.pObject != null))
                    this.pImage = this.pObject.Image;
                return this.pImage;
            }
        }
        private int CvipMask
        {
            get
            {
                if ((this.pMask == 0) && (this.CvipImage != 0))
                {
                    this.pMask = this.pObject.Mask;
                    int bandsImg = CvipOp.GetNoOfBands_Image(ref this.pImage);
                    int bandsMask = CvipOp.GetNoOfBands_Image(ref this.pMask);
                    if (bandsMask != bandsImg)
                    {
                        if (bandsImg == 1)
                            this.pMask = Make1Band(this.pMask);
                        else
                            this.pMask = Make3Band(this.pMask);
                    }
                }
                return this.pMask;
            }
        }
    }
}
