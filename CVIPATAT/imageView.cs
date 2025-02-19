using System;
using System.Drawing;
using System.IO;
using System.Windows.Forms;

namespace CVIP_ATAT
{
    public partial class imageView : Form
    {        
        MDIMainForm viewMainRef;
        private string imageNamePath;
        private int inputImage, memoryDC, imageWidth, imageHeight, imageBands, datatype;

        public imageView(MDIMainForm mainRef, string imageName)
        {
            viewMainRef = mainRef;
            imageNamePath = imageName;
            this.ResizeRedraw = true;

            InitializeComponent();

            this.inputImage = viewMainRef.mainCVIPTool.Read_Image(ref this.imageNamePath);

            if (this.inputImage == 0)
                throw new ArgumentException(imageName + ": CVIPimage pointer not initialized.");

            double[] info = viewMainRef.mainCVIPTool.GetImageInfo(this.inputImage);
            this.datatype = (int)info[3];
            this.imageBands = (int)info[4];
            this.imageHeight = (int)info[5];
            this.imageWidth = (int)info[6];
        }

        private void imageView_FormClosed(object sender, FormClosedEventArgs e)
        {
            viewMainRef.mainCVIPTool.Delete_Image(ref inputImage);
            this.Dispose();
        }

        private void imageView_MouseMove(object sender, MouseEventArgs e)
        {
            int xMouse, yMouse;
            string[] rgb;

            Point pt = ScalePointWindowToImage(e.Location);
            xMouse = pt.X;
            yMouse = pt.Y;

            rgb = GetRGBString(pt.X, pt.Y);

            viewMainRef.tbColValue.Text = xMouse.ToString();
            viewMainRef.tbRowValue.Text = yMouse.ToString();
            viewMainRef.tbRValue.Text = rgb[0];
            viewMainRef.tbGValue.Text = rgb[1];
            viewMainRef.tbBValue.Text = rgb[2];
        }

        private void imageView_MouseLeave(object sender, EventArgs e)
        {
            viewMainRef.tbColValue.Text = "";
            viewMainRef.tbRowValue.Text = "";
            viewMainRef.tbRValue.Text = "";
            viewMainRef.tbGValue.Text = "";
            viewMainRef.tbBValue.Text = "";
        }

        Point ScalePointWindowToImage(Point ptWindow)
        {
            double scaleX = (double)this.imageWidth / this.ClientSize.Width;
            double scaleY = (double)this.imageHeight / this.ClientSize.Height;
            int X = (int)((double)ptWindow.X * scaleX);
            int Y = (int)((double)ptWindow.Y * scaleY);
            return new Point(X, Y);
        }

        private void imageView_Load(object sender, EventArgs e)
        {
            this.Text = Path.GetFileName(imageNamePath);
            this.ClientSize = new Size(this.imageWidth, this.imageHeight);
            if (this.imageHeight > 745)
            {
                this.ClientSize = new Size((int)(this.imageWidth * (745 / (double)this.imageHeight)), 745);
            }
            this.RenderDisplayImage();
        }

        private void imageView_Paint(object sender, PaintEventArgs e)
        {
            IntPtr hdc = e.Graphics.GetHdc();
            viewMainRef.mainCVIPTool.Show_DisplayImage(hdc.ToInt32(), memoryDC, this.ClientSize.Width, this.ClientSize.Height, this.imageWidth, this.imageHeight);
            e.Graphics.ReleaseHdc();
        }
        private void RenderDisplayImage()
        {
            if (this.memoryDC != 0)
            {
                viewMainRef.mainCVIPTool.Delete_DisplayImage(this.memoryDC);
                this.memoryDC = 0;
            }
            int img = this.inputImage;
            this.inputImage = viewMainRef.mainCVIPTool.CondRemap_Image(img, 0, 0, 255);
            viewMainRef.mainCVIPTool.Delete_Image(ref img);
            Bitmap bmp = new Bitmap(this.imageWidth, this.imageHeight);
            Graphics g = Graphics.FromImage(bmp);
            g.Clear(Color.Black);
            IntPtr hdc = g.GetHdc();
            memoryDC = viewMainRef.mainCVIPTool.Render_DisplayImage(hdc.ToInt32(), this.inputImage);
            g.ReleaseHdc(hdc);
            g.Dispose();
        }

        public string[] GetRGBString(int x, int y)
        {
            string[] rgb = null;
            if ((x >= 0) && (x < this.imageWidth) &&
                (y >= 0) && (y < this.imageHeight))
            {
                double[] pixel = (double[])viewMainRef.mainCVIPTool.GetPixel_Image(this.inputImage, y, x);
                string format = "";
                if ((this.datatype == 4) || (this.datatype == 3))
                {
                    format = "0.00000";
                }
                rgb = new string[3];
                rgb[0] = pixel[0].ToString(format);
                if (this.imageBands == 1)
                {
                    rgb[1] = rgb[0];
                    rgb[2] = rgb[0];
                }
                else
                {
                    rgb[1] = pixel[1].ToString(format);
                    rgb[2] = pixel[2].ToString(format);
                }
            }
            return rgb;
        }
    }
}