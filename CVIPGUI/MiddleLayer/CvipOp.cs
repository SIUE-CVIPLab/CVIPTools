/*'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' ======================================================================
' Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
' ======================================================================
'
'             File Name: CvipOp.cs
'           Description: Wrapper functions for CVIPCOM control
'   Initial Coding Date: April 2007
'              Modified: February 2013
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

using SERVERLib;
using System;
using System.Collections.Generic;
using System.Drawing;
using System.IO;
using System.Text;
using System.Windows.Forms;

namespace CVIPGUI
{
    public struct NotchZone
    {
        public int Col;
        public int Row;
        public int Radius;
        public NotchZone(int r, int c, int rad)
        {
            this.Col = c;
            this.Row = r;
            this.Radius = rad;
        }
    }

    static class CvipOp
    {
        static CVIPTools CVIPCOM = null;

        static string errCodebook = "The image to be compressed must be the same size as the image from which the codebook is generated.";
        static string errColorBands = "Please use different colors for different bands.";
        static string errCropParams = "Please check parameters.";
        static string errCutoff = "The Low Cutoff should be less than the High Cutoff.";
        static string errFileOpen = "Cannot open the specified image.";
        static string errHistoryIn = "Invalid input history.";
        static string errHistoryOut = "Invalid output history.";
        static string errImageBands = "Image band(s) incompatible.";
        static string errImageBinary = "This operation requires binary image(s). You can get a binary image by thresholding an image.";
        static string errImageColor = "This operation requires a color image.";
        static string errImageGray = "This operation requires a gray image.";
        static string errImageInput = "Invalid input image.";
        static string errImageOutput = "Invalid output image.";
        static string errImageSize = "Image size(s) incompatible.";
        static string errResizeParams = "New size same as current size.";

        static CvipOp()
        {
            CVIPCOM = new CVIPTools();
            Set_Console();
        }


        static public int superPixel(int image)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                ret = CVIPCOM.superPixel(ref dup);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Vertical_Flip", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }


        static public int AD_Filter(int image, int iterations, int speed, int edge_height)
        {
            int dup = 0, ret = 0;
            try
            {

                
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                ret = CVIPCOM.AD_Filter(ref dup, iterations, speed, edge_height);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("AD_Filter", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public int Adapt_Median_Filter(int image, int masksize)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                ret = CVIPCOM.Adapt_Median_Filter(ref dup, masksize);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Adapt_Median_Filter", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public int Adaptive_Contrast_Filter(int image, double k1, double k2, int kernel_size, double min_gain, double max_gain)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                
                dup = CVIPCOM.Duplicate_Image(ref image);
                ret = CVIPCOM.Adaptive_Contrast_Filter(ref dup, k1, k2, kernel_size, min_gain, max_gain);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Adaptive_Contrast_Filter", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public int Add_Image(int image1, int image2)
        {
            int dup1 = 0, dup2 = 0, ret = 0;
            try
            {
                if (image1 == 0) throw new Exception(errImageInput);
                if (image2 == 0) throw new Exception(errImageInput);
                dup1 = CVIPCOM.Duplicate_Image(ref image1);
                dup2 = CVIPCOM.Duplicate_Image(ref image2);

                int band1 = CVIPCOM.GetNoOfBands_Image(ref dup1);
                int band2 = CVIPCOM.GetNoOfBands_Image(ref dup2);
                if (band1 != band2)
                {
                    int tmp = 0;
                    int[] bands = new int[3];
                    if (band1 == 1)
                    {
                        tmp = dup1;
                        for (int i = 0; i < 3; i++)
                            bands[i] = tmp;
                        dup1 = CVIPCOM.Assemble_Bands(bands);
                    }
                    else if (band2 == 1)
                    {
                        tmp = dup2;
                        for (int i = 0; i < 3; i++)
                            bands[i] = tmp;
                        dup2 = CVIPCOM.Assemble_Bands(bands);
                    }
                    else
                        throw new Exception(errImageBands);
                    CVIPCOM.Delete_Image(ref tmp);
                }
                CVIPCOM.Cast_Image(ref dup1, (int)dataType.CVIP_FLOAT);
                CVIPCOM.Cast_Image(ref dup2, (int)dataType.CVIP_FLOAT);
                ret = CVIPCOM.Add_Image(ref dup1, ref dup2);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Add_Image", e);
                ret = 0;
            }
            finally
            {
                if (dup1 != 0) CVIPCOM.Delete_Image(ref dup1);
                if (dup2 != 0) CVIPCOM.Delete_Image(ref dup2);
            }
            return ret;
        }
        static public int Alpha_Filter(int image, int masksize, int p)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                ret = CVIPCOM.Alpha_Filter(ref dup, masksize, p);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Alpha_Filter", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public int And_Image(int image1, int image2)
        {
            int dup1 = 0, dup2 = 0, ret = 0;
            try
            {
                if (image1 == 0) throw new Exception(errImageInput);
                if (image2 == 0) throw new Exception(errImageInput);

                if ((dataType)CVIPCOM.GetDataType_Image(ref image1) == dataType.CVIP_BYTE)
                    dup1 = CVIPCOM.Duplicate_Image(ref image1);
                else
                    dup1 = CVIPCOM.Remap_Image(ref image1, (int)dataType.CVIP_BYTE, 0, 255);

                if ((dataType)CVIPCOM.GetDataType_Image(ref image2) == dataType.CVIP_BYTE)
                    dup2 = CVIPCOM.Duplicate_Image(ref image2);
                else
                    dup2 = CVIPCOM.Remap_Image(ref image2, (int)dataType.CVIP_BYTE, 0, 255);

                int band1 = CVIPCOM.GetNoOfBands_Image(ref dup1);
                int band2 = CVIPCOM.GetNoOfBands_Image(ref dup2);
                if (band1 != band2)
                {
                    int tmp = 0;
                    int[] bands = new int[3];
                    if (band1 == 1)
                    {
                        tmp = dup1;
                        for (int i = 0; i < 3; i++)
                            bands[i] = tmp;
                        dup1 = CVIPCOM.Assemble_Bands(bands);
                    }
                    else if (band2 == 1)
                    {
                        tmp = dup2;
                        for (int i = 0; i < 3; i++)
                            bands[i] = tmp;
                        dup2 = CVIPCOM.Assemble_Bands(bands);
                    }
                    else
                        throw new Exception(errImageBands);
                    CVIPCOM.Delete_Image(ref tmp);
                }
                ret = CVIPCOM.And_Image(ref dup1, ref dup2);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("And_Image", e);
                ret = 0;
            }
            finally
            {
                if (dup1 != 0) CVIPCOM.Delete_Image(ref dup1);
                if (dup2 != 0) CVIPCOM.Delete_Image(ref dup2);
            }
            return ret;
        }
        static public int Area(int labeledImage, int row, int col)
        {
            int area = -1;
            try
            {
                if (labeledImage == 0) throw new Exception(errImageInput);
                area = CVIPCOM.Area(ref labeledImage, row, col);
            }
            catch (Exception e)
            {
                ReportError("Area", e);
                area = -1;
            }
            return area;
        }
        static public double Aspect(int labeledImage, int row, int col)
        {
            double aspect = 0;
            try
            {
                if (labeledImage == 0) throw new Exception(errImageInput);
                aspect = CVIPCOM.Aspect(ref labeledImage, row, col);
            }
            catch (Exception e)
            {
                ReportError("Aspect", e);
                aspect = 0;
            }
            return aspect;
        }
        static public int Assemble_Bands(int[] bands)
        {
            int ret = 0;
            try
            {
                if (bands[0] == 0) throw new Exception(errImageInput);
                if (bands[1] == 0) throw new Exception(errImageInput);
                if (bands[2] == 0) throw new Exception(errImageInput);
                int rows = CVIPCOM.GetNoOfRows_Image(ref bands[0]);
                int cols = CVIPCOM.GetNoOfCols_Image(ref bands[0]);
                for (int i = 1; i < 3; i++)
                {
                    if ((CVIPCOM.GetNoOfRows_Image(ref bands[i]) != rows) ||
                        (CVIPCOM.GetNoOfCols_Image(ref bands[i]) != cols))
                        throw new Exception(errImageSize);
                }
                ret = CVIPCOM.Assemble_Bands(bands);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Assemble_Bands", e);
                ret = 0;
            }
            return ret;
        }
        static public int Auto_Threshold_Segment(int inputImage, float limit)
        {
            int dup = 0, ret = 0;
            try
            {
                if (inputImage == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref inputImage);
                ret = CVIPCOM.Auto_Threshold_Segment(ref dup, limit);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("auto_threshold_segment", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public int Bilinear_Interp1(int image, float xfactor, float yfactor)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                ret = CVIPCOM.Bilinear_Interp1(ref dup, xfactor, yfactor);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Bilinear_Interp1", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public int BinaryToGray(int image)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                ret = CVIPCOM.Gray_Binary(ref dup, 1);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("BinaryToGray", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public int Boiecox_Filter(int image, double variance, bool do_threshold, bool do_hyst, bool do_thin, double high_threshold, double low_threshold, ref int threshold_image, ref int hyst_image)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                ret = CVIPCOM.Boiecox_Filter(ref dup, variance, do_threshold ? 1 : 0, do_hyst ? 1 : 0, do_thin ? 1 : 0, high_threshold, low_threshold, ref threshold_image, ref hyst_image);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Boiecox_Filter", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public int BRLC_Compression(int image, string filename, int bitmask)
        {
            int dup = 0, success = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                CVIPCOM.Bit_Compress(ref filename, ref dup, bitmask);
            }
            catch (Exception e)
            {
                ReportError("BRLC_Compression", e);
                success = -1;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return success;
        }
        static public int BRLC_Compression_Image(int image, string filename, int bitmask)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                CVIPCOM.Bit_Compress(ref filename, ref dup, bitmask);
                ret = CVIPCOM.Bit_Decompress(ref filename);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("BRLC_Compression_Image", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public int BRLC_deCompression(string filename)
        {
            int ret = 0;
            try
            {
                ret = CVIPCOM.Bit_Decompress(ref filename);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("BRLC_deCompression", e);
                ret = 0;
            }
            return ret;
        }
        static public int BTC_Compression(int image, string filename, int blocksize)
        {
            int dup = 0, success = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                CVIPCOM.Btc_Compress(ref filename, ref dup, blocksize);
            }
            catch (Exception e)
            {
                ReportError("BTC_Compression", e);
                success = -1;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return success;
        }
        static public int BTC_Compression_Image(int image, string filename, int blocksize)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                CVIPCOM.Btc_Compress(ref filename, ref dup, blocksize);
                ret = CVIPCOM.Btc_Decompression(ref filename);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("BTC_Compression_Image", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public int BTC_deCompression(string filename)
        {
            int ret = 0;
            try
            {
                ret = CVIPCOM.Btc_Decompression(ref filename);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("BTC_deCompression", e);
                ret = 0;
            }
            return ret;
        }
        static public int Butterworth_Band_Pass(int image, int blocksize, int keepdc, int inner_cutoff, int outer_cutoff, int filter_order)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                ret = CVIPCOM.Butterworth_Band_Pass(ref dup, blocksize, keepdc, inner_cutoff, outer_cutoff, filter_order);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Butterworth_Band_Pass", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public int Butterworth_Band_Reject(int image, int blocksize, int keepdc, int inner_cutoff, int outer_cutoff, int filter_order)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                ret = CVIPCOM.Butterworth_Band_Reject(ref dup, blocksize, keepdc, inner_cutoff, outer_cutoff, filter_order);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Butterworth_Band_Reject", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public int Butterworth_High(int image, int blocksize, int keepdc, int cutoff, int filter_order)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                ret = CVIPCOM.Butterworth_High(ref dup, blocksize, keepdc, cutoff, filter_order);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Butterworth_High", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public int Butterworth_Low(int image, int blocksize, int keepdc, int cutoff, int filter_order)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                ret = CVIPCOM.Butterworth_Low(ref dup, blocksize, keepdc, cutoff, filter_order);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Butterworth_Low", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public int Canny_Filter(int image, double low_threshold, double high_threshold, double variance, ref int mag_image, ref int dir_image)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                ret = CVIPCOM.Canny_Filter(ref dup, low_threshold, high_threshold, variance, ref mag_image, ref dir_image);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Canny_Filter", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public void Cast_Image(int image, dataType dt)
        {
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                CVIPCOM.Cast_Image(ref image, (int)dt);
            }
            catch (Exception e)
            {
                ReportError("Cast_Image", e);
            }
        }
        static public int[] CentroID(int labeledImage, int row, int col)
        {
            object centroid = null;
            try
            {
                if (labeledImage == 0) throw new Exception(errImageInput);
                centroid = CVIPCOM.CentroID(ref labeledImage, row, col);
            }
            catch (Exception e)
            {
                ReportError("CentroID", e);
                centroid = null;
            }
            return (int[])centroid;
        }
        static public int Cerchar_Filter(int image)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                ret = CVIPCOM.Cerchar_Filter(ref dup);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Cerchar_Filter", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public bool Check_Bin(int image)
        {
            bool result = false;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                result = (CVIPCOM.Check_Bin(ref image) != 0);
            }
            catch (Exception e)
            {
                ReportError("Check_Bin", e);
                result = false;
            }
            return result;
        }
        static public int Check_xform_history(int image, int filter_type)
        {
            int hist = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                hist = CVIPCOM.Check_xform_history(ref image, filter_type);
            }
            catch (Exception e)
            {
                ReportError("Check_xform_history", e);
                hist = 0;
            }
            return hist;
        }
        static public int CLAHE(int image, int blocksize, double clippercent, int band)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                ret = CVIPCOM.CLAHE(ref dup, blocksize, clippercent, band);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("CLAHE", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }

        static public int CLAHE_Grid(int image, int blocksize, double clippercent, int band)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                ret = CVIPCOM.CLAHE_Grid(ref dup, blocksize, clippercent, band);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("CLAHE", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }

        static public void Close_Console()
        {
            try { CVIPCOM.Close_Console(); }
            catch { }
        }
        static public int Color_Contrast_Enhance(int image, int low_limit, int high_limit, float low_clip, float high_clip)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                ret = CVIPCOM.Color_Contrast_Enhance(ref dup, low_limit, high_limit, low_clip, high_clip);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Color_Contrast_Enhance", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public int ColorXform(int image, colorFormat cf, ref double norm_vector, ref double white_reference, int direction)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                if (GetNoOfBands_Image(image) != 3) throw new Exception(errImageColor);
                dup = CVIPCOM.Duplicate_Image(ref image);
                ret = CVIPCOM.ColorXform(ref dup, (int)cf, ref norm_vector, ref white_reference, direction);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("ColorXform", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public int CondRemap_Image(int image, dataType dt, int min, int max)
        {
            int remap = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                remap = CVIPCOM.CondRemap_Image(ref image, (int)dt, min, max);
                if (remap == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("CondRemap_Image", e);
                remap = 0;
            }
            return remap;
        }
        static public int Contra_Filter(int image, int masksize, int p)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                ret = CVIPCOM.Contra_Filter(ref dup, masksize, p);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Contra_Filter", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public int Copy_Paste(int src_image, int dest_image, int src_row, int src_col, int rows, int cols, int dest_row, int dest_col, int transparent)
        {
            int ret = 0, dupCopy = 0, dupPaste = 0;
            try
            {
                if (src_image == 0) throw new Exception(errImageInput);
                if (dest_image == 0) throw new Exception(errImageInput);
                int src_width = CVIPCOM.GetNoOfCols_Image(ref src_image);
                int src_height = CVIPCOM.GetNoOfRows_Image(ref src_image);
                int dest_width = CVIPCOM.GetNoOfCols_Image(ref dest_image);
                int dest_height = CVIPCOM.GetNoOfRows_Image(ref dest_image);
                if ((src_row < 0) || (src_row >= src_height) ||
                    (src_col < 0) || (src_col >= src_width) ||
                    (rows <= 0) || ((src_row + rows) > src_height) ||
                    (cols <= 0) || ((src_col + cols) > src_width) ||
                    (dest_row < 0) || (dest_row >= dest_height) ||
                    (dest_col < 0) || (dest_col >= dest_width))
                    throw new Exception(errCropParams);
                dupCopy = CVIPCOM.Duplicate_Image(ref src_image);
                dupPaste = CVIPCOM.Duplicate_Image(ref dest_image);
                ret = CVIPCOM.Copy_Paste(ref dupCopy, ref dupPaste, src_row, src_col, rows, cols, dest_row, dest_col, transparent);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Copy_Paste", e);
                ret = 0;
            }
            finally
            {
                if (dupCopy != 0) CVIPCOM.Delete_Image(ref dupCopy);
                if (dupPaste != 0) CVIPCOM.Delete_Image(ref dupPaste);
            }
            return ret;
        }
        static public int Create_Black(int width, int height)
        {
            int ret = 0;
            try
            {
                ret = CVIPCOM.Create_Black(width, height);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Create_Black", e);
                ret = 0;
            }
            return ret;
        }
        static public int Create_Checkboard(int width, int height, int start_col, int start_row, int sqwidth, int sqheight)
        {
            int ret = 0;
            try
            {
                ret = CVIPCOM.Create_Checkboard(width, height, start_col, start_row, sqwidth, sqheight);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Create_Checkboard", e);
                ret = 0;
            }
            return ret;
        }
        static public int Create_Circle(int width, int height, int centerx, int centery, int radius)
        {
            int ret = 0;
            try
            {
                ret = CVIPCOM.Create_Circle(width, height, centerx, centery, radius);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Create_Circle", e);
                ret = 0;
            }
            return ret;
        }
        static public int Create_Cosine(int size, int frequency, int direction)
        {
            int ret = 0;
            try
            {
                ret = CVIPCOM.Create_Cosine(size, frequency, direction);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Create_Cosine", e);
                ret = 0;
            }
            return ret;
        }
        static public int Create_Degenerate_Circle(int width, int height, int centerx, int centery, int radius, int blur)
        {
            int ret = 0;
            try
            {
                ret = CVIPCOM.Create_Degenerate_Circle(width, height, centerx, centery, radius, blur);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Create_Degenerate_Circle", e);
                ret = 0;
            }
            return ret;
        }
        static public int Create_Ellipse(int width, int height, int centerx, int centery, int ellipse_width, int ellipse_height)
        {
            int ret = 0;
            try
            {
                ret = CVIPCOM.Create_Ellipse(width, height, centerx, centery, ellipse_width, ellipse_height);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Create_Ellipse", e);
                ret = 0;
            }
            return ret;
        }
        static public int Create_Line(int width, int height, int tlx, int tly, int brx, int bry)
        {
            int ret = 0;
            try
            {
                ret = CVIPCOM.Create_Line(width, height, tlx, tly, brx, bry);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Create_Line", e);
                ret = 0;
            }
            return ret;
        }
        static public int Create_Mask(double[,] mask_values)
        {
            int ret = 0;
            try
            {
                int height = mask_values.GetLength(0);
                int width = mask_values.GetLength(1);
                double[] mask_1d = new double[width * height];

                for (int r = 0; r < height; r++)
                {
                    for (int c = 0; c < width; c++)
                    {
                        mask_1d[r * width + c] = mask_values[r, c];
                    }
                }
                ret = CVIPCOM.Create_Mask(width, height, ref mask_1d[0]);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Create_Mask", e);
                ret = 0;
            }
            return ret;
        }
        static public Point[,] Create_Mesh_Sine(int rows, int cols)
        {
            Point[,] points = null;
            try
            {
                int pmesh = CVIPCOM.Create_Mesh_Sine(rows, cols);
                if (pmesh == 0) throw new Exception(errImageOutput);
                points = Get_Mesh_Points(pmesh);
            }
            catch (Exception e)
            {
                ReportError("Create_Mesh_Sine", e);
                points = null;
            }
            return points;
        }
        static public int Create_Rectangle(int width, int height, int tlx, int tly, int rect_width, int rect_height)
        {
            int ret = 0;
            try
            {
                ret = CVIPCOM.Create_Rectangle(width, height, tlx, tly, rect_width, rect_height);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Create_Rectangle", e);
                ret = 0;
            }
            return ret;
        }
        static public int Create_Sine(int size, int frequency, int direction)
        {
            int ret = 0;
            try
            {
                ret = CVIPCOM.Create_Sine(size, frequency, direction);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Create_Sine", e);
                ret = 0;
            }
            return ret;
        }
        static public int Create_Squarewave(int size, int frequency, int direction)
        {
            int ret = 0;
            try
            {
                ret = CVIPCOM.Create_Squarewave(size, frequency, direction);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Create_Squarewave", e);
                ret = 0;
            }
            return ret;
        }
        static public int Crop(int image, int start_row, int start_col, int rows, int cols)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                int width = CVIPCOM.GetNoOfCols_Image(ref image);
                int height = CVIPCOM.GetNoOfRows_Image(ref image);
                if ((start_row < 0) || (start_row >= height) ||
                    (start_col < 0) || (start_col >= width) ||
                    (rows <= 0) || ((start_row + rows) > height) ||
                    (cols <= 0) || ((start_col + cols) > width))
                    throw new Exception(errCropParams);
                dup = CVIPCOM.Duplicate_Image(ref image);
                ret = CVIPCOM.Crop(ref dup, start_row, start_col, rows, cols);
                if (ret == 0) throw new Exception(errImageOutput);
            }
           
            catch (Exception e)
            {
                ReportError("Crop", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public string CVIP_OUTPUT()
        {
            return CVIPCOM.CVIP_OUTPUT();
        }
        static public int CVIPhalftone(int image, int halftone_method, int maxval, float threshold, int retain_image, int verbose)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                ret = CVIPCOM.CVIPhalftone(ref dup, halftone_method, maxval, threshold, retain_image, verbose);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("CVIPhalftone", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public Bitmap CvipToBitmap(int image)
        {
            Bitmap bmp = null;
            Graphics g = null;
            IntPtr hdc = IntPtr.Zero;
            int memDC = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                int width = CVIPCOM.GetNoOfCols_Image(ref image);
                int height = CVIPCOM.GetNoOfRows_Image(ref image);
                bmp = new Bitmap(width, height);
                g = Graphics.FromImage(bmp);
                g.Clear(Color.Black);
                hdc = g.GetHdc();
                memDC = CVIPCOM.Render_DisplayImage(hdc.ToInt32(), ref image);
                CVIPCOM.Show_DisplayImage(hdc.ToInt32(), memDC, width, height, width, height);
            }
            catch (Exception e)
            {
                ReportError("CvipToBitmap", e);
                bmp = null;
            }
            finally
            {
                if (memDC != 0) CVIPCOM.Delete_DisplayImage(memDC);
                if (g != null)
                {
                    if (hdc != IntPtr.Zero) g.ReleaseHdc(hdc);
                    g.Dispose();
                }
            }
            return bmp;
        }
        static public int Dct_Transform(int image, int blocksize)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                CVIPCOM.Cast_Image(ref dup, (int)dataType.CVIP_FLOAT);
                ret = CVIPCOM.Dct_Transform(ref dup, blocksize);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Dct_Transform", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public int DCTSharpening(int image, int cutoff, int filter_order, int add2original)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                ret = CVIPCOM.Transform_Sharpen(ref dup, 1, cutoff, 1, filter_order, 1, add2original);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("DCTSharpening", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public int DCTSmoothing(int image, int cutoff, int filter_order)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                ret = CVIPCOM.Transform_Smoothing(ref dup, 1, cutoff, 1, filter_order, 1);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("DCTSmoothing", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public void Delete_DisplayImage(int memDC)
        {
            try
            {
                if (memDC == 0) throw new Exception(errImageInput);
                CVIPCOM.Delete_DisplayImage(memDC);
            }
            catch (Exception e)
            {
                ReportError("Delete_DisplayImage", e);
            }
        }
        static public void Delete_Image(ref int image)
        {
            if (image == 0) return;
            try { CVIPCOM.Delete_Image(ref image); }
            catch { }
            image = 0;
        }
        static public double[] Dice_Coef(int idealImage, int testImage)
        {
            double[] dice;
            try
            {
                if (idealImage == 0) throw new Exception(errImageInput);
                if (testImage == 0) throw new Exception(errImageInput);
                dice = CVIPCOM.Dice_Coef(ref idealImage, ref testImage);
            }
            catch (Exception e)
            {
                ReportError("Dice", e);
                dice = null;
            }
            return dice;
        }
        static public int Divide_Image(int image1, int image2, int zero2num)
        {
            int ret, dup1 = 0, dup2 = 0;
            try
            {
                if (image1 == 0) throw new Exception(errImageInput);
                if (image2 == 0) throw new Exception(errImageInput);
                dup1 = CVIPCOM.Duplicate_Image(ref image1);
                dup2 = CVIPCOM.Duplicate_Image(ref image2);

                int band1 = CVIPCOM.GetNoOfBands_Image(ref dup1);
                int band2 = CVIPCOM.GetNoOfBands_Image(ref dup2);
                if (band1 != band2)
                {
                    int tmp = 0;
                    int[] bands = new int[3];
                    if (band1 == 1)
                    {
                        tmp = dup1;
                        for (int i = 0; i < 3; i++)
                            bands[i] = tmp;
                        dup1 = CVIPCOM.Assemble_Bands(bands);
                    }
                    else if (band2 == 1)
                    {
                        tmp = dup2;
                        for (int i = 0; i < 3; i++)
                            bands[i] = tmp;
                        dup2 = CVIPCOM.Assemble_Bands(bands);
                    }
                    else
                        throw new Exception(errImageBands);
                    CVIPCOM.Delete_Image(ref tmp);
                }
                CVIPCOM.Cast_Image(ref dup1, (int)dataType.CVIP_FLOAT);
                CVIPCOM.Cast_Image(ref dup2, (int)dataType.CVIP_FLOAT);
                ret = CVIPCOM.Divide_Image(ref dup1, ref dup2, zero2num);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Divide_Image", e);
                ret = 0;
            }
            finally
            {
                if (dup1 != 0) CVIPCOM.Delete_Image(ref dup1);
                if (dup2 != 0) CVIPCOM.Delete_Image(ref dup2);
            }
            return ret;
        }
        static public int DPC_Compression(int image, string filename, float ratio, int bit_length, int clipping, int direction, int origin, float deviation)
        {
            int dup = 0, success = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                CVIPCOM.Dpc_Compress(ref filename, ref dup, ratio, bit_length, clipping, direction, origin, deviation);
            }
            catch (Exception e)
            {
                ReportError("DPC_Compression", e);
                success = -1;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return success;
        }
        static public int DPC_Compression_Image(int image, string filename, float ratio, int bit_length, int clipping, int direction, int origin, float deviation)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                CVIPCOM.Dpc_Compress(ref filename, ref dup, ratio, bit_length, clipping, direction, origin, deviation);
                ret = CVIPCOM.Dpc_Decompress(ref filename);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("DPC_Compression_Image", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public int DPC_deCompression(string filename)
        {
            int ret = 0;
            try
            {
                ret = CVIPCOM.Dpc_Decompress(ref filename);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("DPC_deCompression", e);
                ret = 0;
            }
            return ret;
        }
        static public int Duplicate_Image(int image)
        {
            int dup = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                if (dup == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Duplicate_Image", e);
                dup = 0;
            }
            return dup;
        }
        static public int DynRLC_Compression(int image, string filename, int blocksize)
        {
            int dup = 0, success = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                CVIPCOM.DynRLC_Compression(ref filename, ref dup, blocksize);
            }
            catch (Exception e)
            {
                ReportError("DynRLC_Compression", e);
                success = -1;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return success;
        }
        static public int DynRLC_Compression_Image(int image, string filename, int blocksize)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                CVIPCOM.DynRLC_Compression(ref filename, ref dup, blocksize);
                ret = CVIPCOM.DynRLC_deCompression(ref filename);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("DynRLC_Compression_Image", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public int DynRLC_deCompression(string filename)
        {
            int ret = 0;
            try
            {
                ret = CVIPCOM.DynRLC_deCompression(ref filename);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("DynRLC_deCompression", e);
                ret = 0;
            }
            return ret;
        }
        static public int Edge_Detect_Filter(int image, int edge_detector, int mask_type, int masksize, bool keepdc, int threshold, int frei_projection, int frei_threshold, int frei_angle)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                ret = CVIPCOM.Edge_Detect_Filter(ref dup, edge_detector, mask_type, masksize, keepdc ? 1 : 0, threshold, frei_projection, frei_threshold, frei_angle);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Edge_Detect_Filter", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public int Edge_Link_Filter(int image, int connection_distance)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                ret = CVIPCOM.Edge_Link_Filter(ref dup, connection_distance);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Edge_Link_Filter", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public int Enlarge(int image, int height, int width)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                if ((height == CVIPCOM.GetNoOfRows_Image(ref image)) &&
                    (width == CVIPCOM.GetNoOfCols_Image(ref image)))
                    throw new Exception(errResizeParams);
                dup = CVIPCOM.Duplicate_Image(ref image);
                ret = CVIPCOM.Enlarge(ref dup, height, width);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Enlarge", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public int Euler(int labeledImage, int row, int col)
        {
            int euler = -1;
            try
            {
                if (labeledImage == 0) throw new Exception(errImageInput);
                euler = CVIPCOM.Euler(ref labeledImage, row, col);
            }
            catch (Exception e)
            {
                ReportError("Euler", e);
                euler = -1;
            }
            return euler;
        }
        static public int Extract_Band(int image, int band)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                if (CVIPCOM.GetNoOfBands_Image(ref image) != 3) throw new Exception(errImageColor);
                dup = CVIPCOM.Duplicate_Image(ref image);
                ret = CVIPCOM.Extract_Band(ref dup, band);
                CVIPCOM.Delete_Image(ref dup);
                dup = 0;
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Extract_Band", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public int Fft_Mag(int image)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                ret = CVIPCOM.Fft_Mag(ref dup);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Fft_Mag", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public int Fft_Phase(int image, int remap_norm, double k)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                ret = CVIPCOM.Fft_Phase(ref dup, remap_norm, k);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Fft_Phase", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public int Fft_Transform(int image, int blocksize)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                ret = CVIPCOM.Fft_Transform(ref dup, blocksize);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Fft_Transform", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public int FFTSharpening(int image, int cutoff, int filter_order, int add2original)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                ret = CVIPCOM.Transform_Sharpen(ref dup, 0, cutoff, 1, filter_order, 1, add2original);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("FFTSharpening", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public int FFTSmoothing(int image, int cutoff, int filter_order)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                ret = CVIPCOM.Transform_Smoothing(ref dup, 0, cutoff, 1, filter_order, 1);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("FFTSmoothing", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public Point[,] File_To_Mesh(string filename)
        {
            Point[,] points = null;
            try
            {
                using (BinaryReader br = new BinaryReader(File.OpenRead(filename)))
                {
                    int cols = br.ReadInt32();
                    int rows = br.ReadInt32();
                    points = new Point[rows, cols];
                    for (int i = 0; i < rows; i++)
                    {
                        for (int j = 0; j < cols; j++)
                        {
                            points[i, j].X = br.ReadInt32();
                            points[i, j].Y = br.ReadInt32();
                        }
                    }
                }
            }
            catch (Exception e)
            {
                ReportError("File_To_Mesh", e);
                points = null;
            }
            return points;
        }
        static public int Fractal_Compression(int image, string filename, int tolerance, int min, int max, int domtype, int domstep, int slowenc, int scalebits, int offsetbits)
        {
            int dup = 0, success = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                byte ch = (slowenc != 0) ? (byte)'y' : (byte)'n';
                success = CVIPCOM.Fractal_Compression(ref dup, ref filename, tolerance, min, max, domtype, domstep, ch, ch, scalebits, offsetbits);
            }
            catch (Exception e)
            {
                ReportError("Fractal_Compression", e);
                success = -1;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return success;
        }
        static public int Fractal_Compression_Image(int image, string filename, int tolerance, int min, int max, int domtype, int slowenc)
        {
            int dup = 0, ret = 0;
            try
            {
                // For CVIPtools
                // Domain Step is default set to 1
                // Scaling Bits is default 5
                // Offset Bits is default 7
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                byte ch = (slowenc != 0) ? (byte)'y' : (byte)'n';
                CVIPCOM.Fractal_Compression(ref dup, ref filename, tolerance, min, max, domtype, 1, ch, ch, 5, 7);
                ret = CVIPCOM.Fractal_deCompression(ref filename);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Fractal_Compression_Image", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public int Fractal_deCompression(string filename)
        {
            int ret = 0;
            try
            {
                ret = CVIPCOM.Fractal_deCompression(ref filename);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Fractal_deCompression", e);
                ret = 0;
            }
            return ret;
        }
        static public int Fuzzyc_Segment(int image, double variance)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                int numbands = CVIPCOM.GetNoOfBands_Image(ref dup);
                if (numbands == 1)
                {
                    int tmp = dup;
                    int[] bands = new int[3];
                    for (int i = 0; i < 3; i++)
                        bands[i] = tmp;
                    dup = CVIPCOM.Assemble_Bands(bands);
                    CVIPCOM.Delete_Image(ref tmp);
                }
                ret = CVIPCOM.Fuzzyc_Segment(ref dup, variance);
                if (numbands == 1)
                {
                    int tmp = ret;
                    ret = CVIPCOM.Extract_Band(ref tmp, 1);
                    CVIPCOM.Delete_Image(ref tmp);
                }
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Fuzzyc_Segment", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public int Gamma_Noise(int image, double variance, int alpha)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                ret = CVIPCOM.Gamma_Noise(ref dup, variance, alpha);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Gamma_Noise", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public int Gaussian_Blur_Filter(int image, int masksize)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                ret = CVIPCOM.Gaussian_Blur_Filter(ref dup, masksize);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Gaussian_Blur_Filter", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public int Gaussian_Noise(int image, double variance, double mean)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                ret = CVIPCOM.Gaussian_Noise(ref dup, variance, mean);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Gaussian_Noise", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public int Geometric_Filter(int image, int masksize)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                ret = CVIPCOM.Geometric_Filter(ref dup, masksize);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Geometric_Filter", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public int Geometric_Mean(int degr_image, int degr_fn, int psd_noise, int psd_orig, double gamma, double alpha, int max_gain, int cutoff)
        {
            int dup_im = 0, dup_fn = 0, dup_noise = 0, dup_orig = 0, ret = 0;
            try
            {
                if (degr_image == 0) throw new Exception(errImageInput);
                if (degr_fn == 0) throw new Exception(errImageInput);
                if (psd_noise == 0) throw new Exception(errImageInput);
                if (psd_orig == 0) throw new Exception(errImageInput);
                dup_im = CVIPCOM.Duplicate_Image(ref degr_image);
                dup_fn = CVIPCOM.Duplicate_Image(ref degr_fn);
                dup_noise = CVIPCOM.Duplicate_Image(ref psd_noise);
                dup_orig = CVIPCOM.Duplicate_Image(ref psd_orig);
                ret = CVIPCOM.Geometric_Mean(ref dup_im, ref dup_fn, ref dup_noise, ref dup_orig, gamma, alpha, max_gain, cutoff);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Geometric_Mean", e);
                ret = 0;
            }
            finally
            {
                if (dup_im != 0) CVIPCOM.Delete_Image(ref dup_im);
                if (dup_fn != 0) CVIPCOM.Delete_Image(ref dup_fn);
                if (dup_noise != 0) CVIPCOM.Delete_Image(ref dup_noise);
                if (dup_orig != 0) CVIPCOM.Delete_Image(ref dup_orig);
            }
            return ret;
        }
        static public int get_hist_real(int image)
        {
            int ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                ret = CVIPCOM.get_hist_real(ref image);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("get_hist_real", e);
                ret = 0;
            }
            return ret;
        }
        static public int Get_Histogram_Image(int image)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                ret = CVIPCOM.Get_Histogram_Image(ref dup);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Get_Histogram_Image", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public double[] Get_max_min_value(int image)
        {
            double[] result = new double[12];
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                CVIPCOM.Get_max_min_value(ref image, ref result[0]);
            }
            catch (Exception e)
            {
                ReportError("Get_max_min_value", e);
                result = null;
            }
            return result;
        }
        static public Point[,] Get_Mesh_Points(int mesh)
        {
            Point[,] points = null;
            try
            {
                int[] arr = CVIPCOM.Get_Mesh_Points(ref mesh) as int[];
                if (arr == null) throw new Exception(errImageOutput);
                int width = arr[0];
                int height = arr[1];
                points = new Point[height, width];
                int k = 2;
                for (int i = 0; i < height; i++)
                {
                    for (int j = 0; j < width; j++)
                    {
                        points[i, j].X = arr[k++];
                        points[i, j].Y = arr[k++];
                    }
                }
            }
            catch (Exception e)
            {
                ReportError("Get_Mesh_Points", e);
                points = null;
            }
            return points;
        }
        static public dataFormat GetDataFormat_Image(int image)
        {
            dataFormat df = (dataFormat)(-1);
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                df = (dataFormat)CVIPCOM.GetDataFormat_Image(ref image);
            }
            catch (Exception e)
            {
                ReportError("GetDataFormat_Image", e);
                df = (dataFormat)(-1);
            }
            return df;
        }
        static public dataType GetDataType_Image(int image)
        {
            dataType dt = (dataType)(-1);
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dt = (dataType)CVIPCOM.GetDataType_Image(ref image);
            }
            catch (Exception e)
            {
                ReportError("GetDataType_Image", e);
                dt = (dataType)(-1);
            }
            return dt;
        }
        static public double[] GetImageInfo(int image)
        {
            object info = null;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                info = CVIPCOM.GetImageInfo(ref image);
            }
            catch (Exception e)
            {
                ReportError("GetImageInfo", e);
                info = null;
            }
            return (double[])info;
        }
        static public int GetNoOfBands_Image(int image)
        {
            int bands = -1;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                bands = CVIPCOM.GetNoOfBands_Image(ref image);
            }
            catch (Exception e)
            {
                ReportError("GetNoOfBands_Image", e);
                bands = -1;
            }
            return bands;
        }
        static public int GetNoOfCols_Image(int image)
        {
            int cols = -1;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                cols = CVIPCOM.GetNoOfCols_Image(ref image);
            }
            catch (Exception e)
            {
                ReportError("GetNoOfCols_Image", e);
                cols = -1;
            }
            return cols;
        }
        static public int GetNoOfRows_Image(int image)
        {
            int rows = -1;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                rows = CVIPCOM.GetNoOfRows_Image(ref image);
            }
            catch (Exception e)
            {
                ReportError("GetNoOfRows_Image", e);
                rows = -1;
            }
            return rows;
        }
        static public double[] GetPixel_Image(int image, int row, int col)
        {
            object pixel = null;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                pixel = CVIPCOM.GetPixel_Image(ref image, row, col);
            }
            catch (Exception e)
            {
                ReportError("GetPixel_Image", e);
                pixel = null;
            }
            return (double[])pixel;
        }
        static public int Gray_Binary(int image, int direction)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                ret = CVIPCOM.Gray_Binary(ref dup, direction);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Gray_Binary", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public int Gray_Level_Multiplication(int image, float mult, int choice)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                ret = CVIPCOM.Gray_Multiplication(ref dup, mult, choice);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Gray_Level_Multiplication", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public int Gray_Multiply(int image, float ratio)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                ret = CVIPCOM.Gray_Multiply(ref dup, ratio);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Gray_Multiply", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public int Gray_Multiply2(int image, float ratio)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                ret = CVIPCOM.Gray_Multiply2(ref dup, ratio);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Gray_Multiply2", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public int Gray_Quant_Segment(int image, int gray_levels)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                ret = CVIPCOM.Gray_Quant_Segment(ref dup, gray_levels);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Gray_Quant_Segment", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public int Graylevel_Quant(int image, int gray_levels, int choice)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                ret = CVIPCOM.Graylevel_Quant(ref dup, gray_levels, choice);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Graylevel_Quant", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public int Graylevel_Remap(int image, int r_selection, int g_selection, int b_selection)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                if (CVIPCOM.GetNoOfBands_Image(ref image) != 1) throw new Exception(errImageGray);
                dup = CVIPCOM.Duplicate_Image(ref image);
                ret = CVIPCOM.Graylevel_Remap(ref dup, r_selection, g_selection, b_selection);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Graylevel_Remap", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public int GrayToBinary(int image)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                ret = Gray_Binary(dup, 0);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("GrayToBinary", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public int GVFSnake_Segment(int image, int[] area, int iterations, double alpha, double beta, double kappa)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                ret = CVIPCOM.GVFSnake_Segment(ref dup, ref area[0], iterations, alpha, beta, kappa);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("GVFSnake_Segment", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public int H_image(int mask_type, int height, int width)
        {
            int ret = 0;
            try
            {
                ret = CVIPCOM.H_image(mask_type, height, width);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("H_image", e);
                ret = 0;
            }
            return ret;
        }
        static public int Haar_Transform(int image, int direction, int blocksize)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                ret = CVIPCOM.Haar_Transform(ref dup, direction, blocksize);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Haar_Transform", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public int Harmonic_Filter(int image, int masksize)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                ret = CVIPCOM.Harmonic_Filter(ref dup, masksize);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Harmonic_Filter", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public int Harris_Corner_Filter(int image, float alpha, int threshold, int border, float dmin)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                ret = CVIPCOM.Harris_Corner_Filter(ref dup, alpha, threshold, border, dmin);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Harris_Corner_Filter", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public int High_Freq_Emphasis(int image, int blocksize, int keepdc, int cutoff, double alpha, int filter_order)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                ret = CVIPCOM.High_Freq_Emphasis(ref dup, blocksize, keepdc, cutoff, alpha, filter_order);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("High_Freq_Emphasis", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public int HighBoost(int image, int masksize, int center_value, int add2original)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                ret = CVIPCOM.Highboost(ref dup, masksize, center_value, add2original);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("HighBoost", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public int HighFreq_Emphasize(int image, int xform, int cutoff, int filter_order, double offset, int keepdc)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                ret = CVIPCOM.HighFreq_Emphasis(ref dup, xform, cutoff, filter_order, offset, keepdc);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("HighFreq_Emphasize", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public int Highpass_Spatial_Filter(int image, int add2original)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                ret = CVIPCOM.Highpass_Spatial(ref dup, add2original);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Highpass_Spatial_Filter", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public double[] Hist_Feature(int image, int labledImage, int row, int col)
        {
            object result = null;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                if (labledImage == 0) throw new Exception(errImageInput);
                result = CVIPCOM.Hist_Feature(ref image, ref labledImage, row, col);
            }
            catch (Exception e)
            {
                ReportError("Hist_Feature", e);
                result = null;
            }
            return (double[])result;
        }
        static public int Hist_Thresh_Gray(int image, float tore)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                ret = CVIPCOM.Hist_Thresh_Gray(ref dup, tore);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Hist_Thresh_Gray", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public int Hist_Thresh_Segment(int image, float tore)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                ret = CVIPCOM.Hist_Thresh_Segment(ref dup, tore);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Hist_Thresh_Segment", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public int Histogram_ACE2(int image, double local_mean, double local_gain, int masksize)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                ret = CVIPCOM.Ace2_Filter(ref dup, masksize, local_mean, local_gain);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Histogram_ACE2", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public int Histogram_Equalization(int image, int band)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
             
                ret = CVIPCOM.Histeq(ref dup, band);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Histogram_Equalization", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public int Histogram_expACE(int image, double local_mean, double local_gain, int masksize)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                ret = CVIPCOM.Exp_Ace_Filter(ref dup, masksize, local_mean, local_gain);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Histogram_expACE", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public int Histogram_Local_Equalization(int image, int blocksize, int band)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                ret = CVIPCOM.Local_Histeq(ref dup, blocksize, band);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Histogram_Local_Equalization", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public int Histogram_logACE(int image, double local_mean, double local_gain, int masksize)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                ret = CVIPCOM.Log_Ace_Filter(ref dup, masksize, local_mean, local_gain);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Histogram_logACE", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public int Histogram_Slide(int image, int slide)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                ret = CVIPCOM.Hist_Slide(ref dup, slide);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Histogram_Slide", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public int Histogram_Specification(int image, string r_histogram, string g_histogram, string b_histogram)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                ret = CVIPCOM.Hist_Spec(ref dup, ref r_histogram, ref g_histogram, ref b_histogram);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Histogram_Specification", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public int Histogram_Stretch(int image, int low_limit, int high_limit, float low_clip, float high_clip)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                ret = CVIPCOM.Hist_Stretch(ref dup, low_limit, high_limit, low_clip, high_clip);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Histogram_Stretch", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public void History_Add(int image, int history)
        {
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                if (history == 0) throw new Exception(errHistoryIn);
                CVIPCOM.History_Add(ref image, ref history);
            }
            catch (Exception e)
            {
                ReportError("History_Add", e);
            }
        }
        static public int History_Check(int image, int program)
        {
            int hist = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                hist = CVIPCOM.History_Check(ref image, program);
            }
            catch (Exception e)
            {
                ReportError("History_Check", e);
                hist = 0;
            }
            return hist;
        }
        static public int history_create(int prog, int type, float value)
        {
            int hist = 0;
            try
            {
                hist = CVIPCOM.history_create(prog, type, value);
                if (hist == 0) throw new Exception(errHistoryOut);
            }
            catch (Exception e)
            {
                ReportError("history_create", e);
                hist = 0;
            }
            return hist;
        }
        static public int history_create2(int prog, int type, int value1, int value2)
        {
            int hist = 0;
            try
            {
                hist = CVIPCOM.history_create2(prog, type, value1, value2);
                if (hist == 0) throw new Exception(errHistoryOut);
            }
            catch (Exception e)
            {
                ReportError("history_create2", e);
                hist = 0;
            }
            return hist;
        }
        static public int History_Delete_Program(int image, int program)
        {
            int hist = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                hist = CVIPCOM.History_Delete_Program(ref image, program);
            }
            catch (Exception e)
            {
                ReportError("History_Delete_Program", e);
                hist = 0;
            }
            return hist;
        }
        static public int History_Get(int image, int program)
        {
            int hist = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                hist = CVIPCOM.History_Get(ref image, program);
                if (hist == 0) throw new Exception(errHistoryOut);
            }
            catch (Exception e)
            {
                ReportError("History_Get", e);
                hist = 0;
            }
            return hist;
        }
        static public int History_get_data(int history, int program)
        {
            int data = 0;
            try
            {
                if (history == 0) throw new Exception(errHistoryIn);
                data = CVIPCOM.History_get_data(ref history, program);
                if (data == 0) throw new Exception(errHistoryOut);
            }
            catch (Exception e)
            {
                ReportError("History_get_data", e);
                data = 0;
            }
            return data;
        }
        static public int History_get_data2(int history, int program, int index)
        {
            int data = 0;
            try
            {
                if (history == 0) throw new Exception(errHistoryIn);
                data = CVIPCOM.History_get_data2(ref history, program, index);
                if (data == 0) throw new Exception(errHistoryOut);
            }
            catch (Exception e)
            {
                ReportError("History_get_data2", e);
                data = 0;
            }
            return data;
        }
        static public int Homomorphic_Sharpen(int image, int cutoff, double lower_limit, double upper_limit, int add2original)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                ret = CVIPCOM.Homomorphic(ref dup, upper_limit, lower_limit, cutoff, add2original);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Homomorphic_Sharpen", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public int Horizontal_Flip(int image)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                ret = CVIPCOM.Horizontal_Flip(ref dup);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Horizontal_Flip", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public int Hough_Filter(int image, string image_name, string angles_of_interest, int threshold, int connection_distance, int interactive, int delta_length, int segment_length, int intermediate_result)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                ret = CVIPCOM.Hough_Filter(ref dup, ref image_name, ref angles_of_interest, threshold, connection_distance, interactive, delta_length, segment_length, intermediate_result);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Hough_Filter", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public int Huffman_Compression(int image, string filename)
        {
            int dup = 0, success = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                CVIPCOM.Huf_Compress(ref filename, ref dup);
            }
            catch (Exception e)
            {
                ReportError("Huffman_Compression", e);
                success = -1;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return success;
        }
        static public int Huffman_Compression_Image(int image, string filename)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                CVIPCOM.Huf_Compress(ref filename, ref dup);
                ret = CVIPCOM.Huf_Decompress(ref filename);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Huffman_Compression_Image", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public int Huffman_deCompression(string filename)
        {
            int ret = 0;
            try
            {
                ret = CVIPCOM.Huf_Decompress(ref filename);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Huffman_deCompression", e);
                ret = 0;
            }
            return ret;
        }
        static public int Idct_Transform(int image, int blocksize)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                ret = CVIPCOM.Idct_Transform(ref dup, blocksize);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Idct_Transform", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public int Ideal_Band_Pass(int image, int blocksize, int keepdc, int inner_cutoff, int outer_cutoff)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                ret = CVIPCOM.Ideal_Band_Pass(ref dup, blocksize, keepdc, inner_cutoff, outer_cutoff);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Ideal_Band_Pass", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public int Ideal_Band_Reject(int image, int blocksize, int keepdc, int inner_cutoff, int outer_cutoff)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                ret = CVIPCOM.Ideal_Band_Reject(ref dup, blocksize, keepdc, inner_cutoff, outer_cutoff);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Ideal_Band_Reject", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public int Ideal_High(int image, int blocksize, int keepdc, int cutoff)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                ret = CVIPCOM.Ideal_High(ref dup, blocksize, keepdc, cutoff);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Ideal_High", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public int Ideal_Low(int image, int blocksize, int keepdc, int cutoff)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                ret = CVIPCOM.Ideal_Low(ref dup, blocksize, keepdc, cutoff);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Ideal_Low", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public int Ifft_Transform(int image, int blocksize)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                ret = CVIPCOM.Ifft_Transform(ref dup, blocksize);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Ifft_Transform", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public int Igs_Segment(int image, int gray_levels)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                ret = CVIPCOM.Igs_Segment(ref dup, gray_levels);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Igs_Segment", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public int Improved_Mmse_Filter(int image, float threshold, int kernel_size, float noise_variance)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                ret = CVIPCOM.Improved_Mmse_Filter(ref dup, threshold, kernel_size, noise_variance);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Improved_Mmse_Filter", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public int Input_Mesh(Point[,] points)
        {
            int mesh = 0;
            try
            {
                int[] arr = new int[(points.Length + 1) * 2];
                int width = points.GetLength(1);
                int height = points.GetLength(0);
                int k = 0;
                arr[k++] = width;
                arr[k++] = height;
                for (int i = 0; i < height; i++)
                {
                    for (int j = 0; j < width; j++)
                    {
                        arr[k++] = points[i, j].X;
                        arr[k++] = points[i, j].Y;
                    }
                }
                mesh = CVIPCOM.Input_Mesh(ref arr[0]);
                if (mesh == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Input_Mesh", e);
                mesh = 0;
            }
            return mesh;
        }
        static public int Intensity_Slicing(int image, ref int lookup_table, int options)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                ret = CVIPCOM.Intensity_Slicing(ref dup, ref lookup_table, options);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Intensity_Slicing", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public int Inverse_Xformfilter(int degr_image, int degr_fn, int max_gain, double cutoff)
        {
            int dup_im = 0, dup_fn = 0, ret = 0;
            try
            {
                if (degr_image == 0) throw new Exception(errImageInput);
                if (degr_fn == 0) throw new Exception(errImageInput);
                dup_im = CVIPCOM.Duplicate_Image(ref degr_image);
                dup_fn = CVIPCOM.Duplicate_Image(ref degr_fn);
                ret = CVIPCOM.Inverse_Xformfilter(ref dup_im, ref dup_fn, max_gain, cutoff);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Inverse_Xformfilter", e);
                ret = 0;
            }
            finally
            {
                if (dup_im != 0) CVIPCOM.Delete_Image(ref dup_im);
                if (dup_fn != 0) CVIPCOM.Delete_Image(ref dup_fn);
            }
            return ret;
        }

        static public double[] Jaccard_Index(int idealImage, int testImage)
        {
            double[] dice;
            try
            {
                if (idealImage == 0) throw new Exception(errImageInput);
                if (testImage == 0) throw new Exception(errImageInput);
                dice = CVIPCOM.Jaccard_Index(ref idealImage, ref testImage);
            }
            catch (Exception e)
            {
                ReportError("Dice", e);
                dice = null;
            }
            return dice;
        }

        static public int JPEG_Compression(int image, string filename, int quality, int grayscale, int optimize, int smooth)
        {
            int dup = 0, success = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                string quant_file = Environment.GetEnvironmentVariable("TEMP") + @"\quant1.txt";
                CVIPCOM.Jpg_Compress(ref filename, ref dup, quality, grayscale, optimize, smooth, 0, ref quant_file);
            }
            catch (Exception e)
            {
                ReportError("JPEG_Compression", e);
                success = -1;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return success;
        }
        static public int JPEG_Compression_Image(int image, string filename, int quality, int grayscale, int optimize, int smooth)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                string quant_file = Environment.GetEnvironmentVariable("TEMP") + @"\quant1.txt";
                CVIPCOM.Jpg_Compress(ref filename, ref dup, quality, grayscale, optimize, smooth, 0, ref quant_file);
                ret = CVIPCOM.Jpg_Decompress(ref filename, 256, smooth, grayscale, 0, 0);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("JPEG_Compression_Image", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public int JPEG_deCompression(string filename, int smooth, int grayscale)
        {
            int ret = 0;
            try
            {
                ret = CVIPCOM.Jpg_Decompress(ref filename, 256, smooth, grayscale, 0, 0);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("JPEG_deCompression", e);
                ret = 0;
            }
            return ret;
        }
        static public int JPEG2000_Compression(int image, string filename, int rate, int quality, int layers, int blocksize)
        {
            int dup = 0, success = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                CVIPCOM.Jp2_Encoder(ref filename, ref dup, rate, quality, layers, blocksize);
            }
            catch (Exception e)
            {
                ReportError("JPEG2000_Compression", e);
                success = -1;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return success;
        }
        static public int JPEG2000_Compression_Image(int image, string filename, int rate, int quality, int layers, int blocksize)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                CVIPCOM.Jp2_Encoder(ref filename, ref dup, rate, quality, layers, blocksize);
                ret = CVIPCOM.Jp2_Decoder(ref filename);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("JPEG2000_Compression_Image", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public int JPEG2000_deCompression(string filename)
        {
            int ret = 0;
            try
            {
                ret = CVIPCOM.Jp2_Decoder(ref filename);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("JPEG2000_deCompression", e);
                ret = 0;
            }
            return ret;
        }
        static public int K_Nearest_Neighbor(string testset, string trainset, string outputfile, int normalization, int distance_measure, int k, int s_min, int s_max, int r_softmax, int r_minkowski)
        {
            int error = -1;
            try
            {
                error = CVIPCOM.K_Nearest_Neighbor(ref testset, ref trainset, ref outputfile, normalization, distance_measure, k, s_min, s_max, r_softmax, r_minkowski);
            }
            catch (Exception e)
            {
                ReportError("K_Nearest_Neighbor", e);
            }
            return error;
        }
        static public int Kirsch_Filter(int image, ref int dirImage, int filter_type, int kernel_size, bool keepdc, int threshold)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                ret = CVIPCOM.Krisch_Filter(ref dup, ref dirImage, filter_type, kernel_size, keepdc ? 1 : 0, threshold);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Kirsch_Filter", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public int Kuwahara_Filter(int image, int masksize)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                ret = CVIPCOM.Kuwahara_Filter(ref dup, masksize);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("kuwahara", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public int Label(int image)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                ret = CVIPCOM.Label(ref dup);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Label", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public double[] Laws_Texture_Feature(int image, int labledImage, int row, int col, int window_size, int vector1, int vector2)
        {
        object result = null;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                if (labledImage == 0) throw new Exception(errImageInput);
               
                try { result = CVIPCOM.Laws_Texture_Feature(ref image, ref  labledImage, row, col, window_size, vector1, vector2); }
                 
                catch { throw new NotSupportedException(); }
                              
            }
            catch (Exception e)
            {
                ReportError("Laws_Texture_Feature", e);
                result = null;
            }
            return (double[])result;
        }
        static public int Least_Squares(int degr_image, int degr_fn, int smoothness_fn, double gamma, int max_gain, int cutoff)
        {
            int dup_im = 0, dup_fn = 0, dup_smoothness = 0, ret = 0;
            try
            {
                if (degr_image == 0) throw new Exception(errImageInput);
                if (degr_fn == 0) throw new Exception(errImageInput);
                if (smoothness_fn == 0) throw new Exception(errImageInput);
                dup_im = CVIPCOM.Duplicate_Image(ref degr_image);
                dup_fn = CVIPCOM.Duplicate_Image(ref degr_fn);
                dup_smoothness = CVIPCOM.Duplicate_Image(ref smoothness_fn);
                ret = CVIPCOM.Least_Squares(ref dup_im, ref dup_fn, ref dup_smoothness, gamma, max_gain, cutoff);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Least_Squares", e);
                ret = 0;
            }
            finally
            {
                if (dup_im != 0) CVIPCOM.Delete_Image(ref dup_im);
                if (dup_fn != 0) CVIPCOM.Delete_Image(ref dup_fn);
                if (dup_smoothness != 0) CVIPCOM.Delete_Image(ref dup_smoothness);
            }
            return ret;
        }
        static public int Linear_Modify_Range(int image, double start, double end, double new_start, double slope, int oor_handling, int band)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                ret = CVIPCOM.Gray_Linear(ref dup, start, end, new_start, slope, oor_handling, band);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Linear_Modify_Range", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public int Local_Adaptive_Zoom(int image)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                ret = CVIPCOM.Local_Adaptive_Zoom(ref dup);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Local_Adaptive_Zoom", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public int Log_Remap(int image, LogRemap band)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                ret = CVIPCOM.Log_Remap(ref dup, (int)band);
                if (ret == 0) throw new Exception(errImageOutput);
            }
           catch (Exception e)
            {
                ReportError("Log_Remap", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public int Lum_Average(int image)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                if (CVIPCOM.GetNoOfBands_Image(ref image) == 1) throw new Exception(errImageColor);
                dup = CVIPCOM.Duplicate_Image(ref image);
                ret = CVIPCOM.Lum_Average(ref dup);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Lum_Average", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public int Luminance_Image(int image)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                if (CVIPCOM.GetNoOfBands_Image(ref image) == 1) throw new Exception(errImageColor);
                dup = CVIPCOM.Duplicate_Image(ref image);
                ret = CVIPCOM.Luminance_Image(ref dup);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Luminance_Image", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public int Marr_Hildreth_Filter(int inputImage, float sigma, int thresholdVal)
        {
            int dup = 0, ret = 0;
            try
            {
                if (inputImage == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref inputImage);
                ret = CVIPCOM.Marr_Hildreth_Filter(ref dup, sigma, thresholdVal);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Marr_Hildreth_Filter", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public int Maximum_Filter(int image, int masksize)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                ret = CVIPCOM.Maximum_Filter(ref dup, masksize);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Maximum_Filter", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public int MBTC_Compression(int image, string filename, int blocksize)
        {
            int dup = 0, success = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                CVIPCOM.Btc2_Compress(ref filename, ref dup, blocksize);
            }
            catch (Exception e)
            {
                ReportError("MBTC_Compression", e);
                success = -1;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return success;
        }
        static public int MBTC_Compression_Image(int image, string filename, int blocksize)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                CVIPCOM.Btc2_Compress(ref filename, ref dup, blocksize);
                ret = CVIPCOM.Btc2_Decompress(ref filename);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("MBTC_Compression_Image", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public int MBTC_deCompression(string filename)
        {
            int ret = 0;
            try
            {
                ret = CVIPCOM.Btc2_Decompress(ref filename);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("MBTC_deCompression", e);
                ret = 0;
            }
            return ret;
        }
        static public int Mean_Filter(int image, int masksize)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                

                ret = CVIPCOM.Mean_Filter(ref dup, masksize);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Mean_Filter", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public int Median_Cut_Segment(int image, int num_colors, int ignore_background, int r_background, int g_background, int b_background)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                int numbands = CVIPCOM.GetNoOfBands_Image(ref dup);
                if (numbands == 1)
                {
                    int tmp = dup;
                    int[] bands = new int[3];
                    for (int i = 0; i < 3; i++)
                        bands[i] = tmp;
                    dup = CVIPCOM.Assemble_Bands(bands);
                    CVIPCOM.Delete_Image(ref tmp);
                }
                ret = CVIPCOM.Median_Cut_Segment(ref dup, num_colors, ignore_background, r_background, g_background, b_background);
                if (numbands == 1)
                {
                    int tmp = ret;
                    ret = CVIPCOM.Extract_Band(ref tmp, 1);
                    CVIPCOM.Delete_Image(ref tmp);
                }
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Median_Cut_Segment", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public int Median_Filter(int image, int masksize)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                ret = CVIPCOM.Median_Filter(ref dup, masksize);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Median_Filter", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public void Mesh_To_File(string filename, Point[,] points)
        {
            try
            {
                int mesh = Input_Mesh(points);
                CVIPCOM.Mesh_To_File(ref filename, ref mesh);
            }
            catch (Exception e)
            {
                ReportError("Mesh_To_File", e);
            }
        }
        static public int Mesh_Warping(int image, Point[,] points, int interpolation_method)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                int mesh = Input_Mesh(points);
                ret = CVIPCOM.Mesh_Warping(ref dup, ref mesh, interpolation_method);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Mesh_Warping", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public int Mesh_WarpingRI(int image, Point[,] points, int interpolation_method, int zero_missing)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                int mesh = Input_Mesh(points);
                ret = CVIPCOM.Mesh_WarpingRI(ref dup, ref mesh, interpolation_method, zero_missing);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Mesh_WarpingRI", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public int Midpoint_Filter(int image, int masksize)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                ret = CVIPCOM.Midpoint_Filter(ref dup, masksize);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Midpoint_Filter", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public int Minimum_Filter(int image, int masksize)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                ret = CVIPCOM.Minimum_Filter(ref dup, masksize);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Minimum_Filter", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public int Mmse_Filter(int image, double noise_variance, int kernel_size)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                ret = CVIPCOM.Mmse_Filter(ref dup, noise_variance, kernel_size);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Mmse_Filter", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public int Moravec_Corner_Filter(int image, float threshold)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                ret = CVIPCOM.Moravec_Corner_Filter(ref dup, threshold);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Moravec_Corner_Filter", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public int Morph_Hitmiss(int image, int masksize, double[] mask_values)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                ret = CVIPCOM.Morph_Hitmiss(ref dup, masksize, ref mask_values[0]);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Morph_Hitmiss", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public int Morph_Skeleton(int binary_image, int masksize, double[] mask_values, int iterations, int four_eight_mask, int method)
        {
            int dup = 0, ret = 0;
            try
            {
                if (binary_image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref binary_image);
                if(four_eight_mask == 0 || four_eight_mask == 1)
                ret = CVIPCOM.Morph_Skeleton(ref dup, masksize, ref mask_values[0], iterations, 0 , method);
                else
                    ret = CVIPCOM.Morph_Skeleton(ref dup, masksize, ref mask_values[0], iterations, 1, method);
                
                    if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Morph_Skeleton", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public int Morph_Thinning(int image, int masksize, double[] mask_values)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                ret = CVIPCOM.Morph_Thinning(ref dup, masksize, ref mask_values[0]);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Morph_Thinning", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public int MorphClose(int image, int kernel_type, int kernel_size, int height, int width)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                if (kernel_type == 2)
                    height = width;
                ret = CVIPCOM.MorphClose(ref dup, kernel_type, kernel_size, height, width);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("MorphClose", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public int MorphClose_Image(int image, int[] matrix, int userOrg, int x, int y, int size)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                ret = CVIPCOM.MorphClose_Image(ref dup, ref matrix[0], userOrg, x, y, size);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("MorphDilate", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public int MorphDilate(int image, int kernel_type, int kernel_size, int height, int width)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                if (kernel_type == 2)
                    height = width;
                ret = CVIPCOM.MorphDilate(ref dup, kernel_type, kernel_size, height, width);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("MorphDilate", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public int MorphDilate_Image(int image, int[] matrix, int userOrg, int x, int y, int size)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                ret = CVIPCOM.MorphDilate_Image(ref dup, ref matrix[0], userOrg, x, y, size);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("MorphDilate", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public int MorphErode(int image, int kernel_type, int kernel_size, int height, int width)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                if (kernel_type == 2)
                    height = width;
                ret = CVIPCOM.MorphErode(ref dup, kernel_type, kernel_size, height, width);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("MorphErode", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public int MorphErode_Image(int image, int[] matrix, int userOrg, int x, int y, int size)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                ret = CVIPCOM.MorphErode_Image(ref dup, ref matrix[0], userOrg, x, y, size);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("MorphDilate", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public int Morpho_com(int image, string surrounds_string, bool rotation, int boolfunc, int iterations, int subfields)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                ret = CVIPCOM.Morpho_com(ref dup, ref surrounds_string, rotation ? 1 : 0, boolfunc, iterations, subfields, 0);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Morpho_com", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public int MorphOpen(int image, int kernel_type, int kernel_size, int height, int width)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                if (kernel_type == 2)
                    height = width;
                ret = CVIPCOM.MorphOpen(ref dup, kernel_type, kernel_size, height, width);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("MorphOpen", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public int MorphOpen_Image(int image, int[] matrix, int userOrg, int x, int y, int size)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                ret = CVIPCOM.MorphOpen_Image(ref dup, ref matrix[0], userOrg, x, y, size);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("MorphDilate", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public int Multi_Resolution_Segment(int image, int homogeneity_test, double param1, double param2, bool run_PCT)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                ret = CVIPCOM.Multi_Resolution_Segment(ref dup, homogeneity_test, param1, param2, run_PCT ? 1 : 0);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Multi_Resolution_Segment", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public int Multiply_Image(int image1, int image2)
        {
            int dup1 = 0, dup2 = 0, ret = 0;
            try
            {
                if (image1 == 0) throw new Exception(errImageInput);
                if (image2 == 0) throw new Exception(errImageInput);
                dup1 = CVIPCOM.Duplicate_Image(ref image1);
                dup2 = CVIPCOM.Duplicate_Image(ref image2);

                int band1 = CVIPCOM.GetNoOfBands_Image(ref dup1);
                int band2 = CVIPCOM.GetNoOfBands_Image(ref dup2);
                if (band1 != band2)
                {
                    int tmp = 0;
                    int[] bands = new int[3];
                    if (band1 == 1)
                    {
                        tmp = dup1;
                        for (int i = 0; i < 3; i++)
                            bands[i] = tmp;
                        dup1 = CVIPCOM.Assemble_Bands(bands);
                    }
                    else if (band2 == 1)
                    {
                        tmp = dup2;
                        for (int i = 0; i < 3; i++)
                            bands[i] = tmp;
                        dup2 = CVIPCOM.Assemble_Bands(bands);
                    }
                    else
                        throw new Exception(errImageBands);
                    CVIPCOM.Delete_Image(ref tmp);
                }
                CVIPCOM.Cast_Image(ref dup1, (int)dataType.CVIP_FLOAT);
                CVIPCOM.Cast_Image(ref dup2, (int)dataType.CVIP_FLOAT);
                ret = CVIPCOM.Multiply_Image(ref dup1, ref dup2);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Multiply_Image", e);
                ret = 0;
            }
            finally
            {
                if (dup1 != 0) CVIPCOM.Delete_Image(ref dup1);
                if (dup2 != 0) CVIPCOM.Delete_Image(ref dup2);
            }
            return ret;
        }
        static public int Nearest_Centroid(string testset, string trainset, string outputfile, int normalization, int distance_measure, int s_min, int s_max, int r_softmax, int r_minkowski)
        {
            int error = -1;
            try
            {
                error = CVIPCOM.Nearest_Centroid(ref testset, ref trainset, ref outputfile, normalization, distance_measure, s_min, s_max, r_softmax, r_minkowski);
            }
            catch (Exception e)
            {
                ReportError("Nearest_Centroid", e);
            }
            return error;
        }
        static public int Nearest_Neighbor(string testset, string trainset, string outputfile, int normalization, int distance_measure, int s_min, int s_max, int r_softmax, int r_minkowski)
        {
            int error = -1;
            try
            {
                error = CVIPCOM.Nearest_Neighbor(ref testset, ref trainset, ref outputfile, normalization, distance_measure, s_min, s_max, r_softmax, r_minkowski);
            }
            catch (Exception e)
            {
                ReportError("Nearest_Neighbor", e);
            }
            return error;
        }
        static public int Neg_Exp_Noise(int image, double variance)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                ret = CVIPCOM.Neg_Exp_Noise(ref dup, variance);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Neg_Exp_Noise", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public int New_Image(imageFormat imf, colorFormat cf, int bands, int height, int width, dataType dt, dataFormat df)
        {
            int ret = 0;
            try
            {
                ret = CVIPCOM.New_Image((int)imf, (int)cf, bands, height, width, (int)dt, (int)df);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("New_Image", e);
                ret = 0;
            }
            return ret;
        }
        static public int Nonfft_Xformfilter(int image, int blocksize, int keepdc, int filter_type, int p1, double p2, int filter_order)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                ret = CVIPCOM.Nonfft_Xformfilter(ref dup, blocksize, keepdc, filter_type, p1, p2, filter_order);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Nonfft_Xformfilter", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public int Not_Image(int image)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                if ((dataType)CVIPCOM.GetDataType_Image(ref image) == dataType.CVIP_BYTE)
                    dup = CVIPCOM.Duplicate_Image(ref image);
                else
                    dup = CVIPCOM.Remap_Image(ref image, (int)dataType.CVIP_BYTE, 0, 255);
                ret = CVIPCOM.Not_Image(ref dup);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Not_Image", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public int Notch(int image, NotchZone[] notches)
        {
            int ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                string fname = "";
                int[] x = new int[notches.Length];
                int[] y = new int[notches.Length];
                int[] r = new int[notches.Length];
                for (int i = 0; i < notches.Length; i++)
                {
                    x[i] = notches[i].Col;
                    y[i] = notches[i].Row;
                    r[i] = notches[i].Radius;
                }
                ret = CVIPCOM.Notch(ref fname, ref x[0], ref y[0], ref r[0], ref image, notches.Length, 0);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Notch", e);
                ret = 0;
            }
            return ret;
        }
        static public int Object_Crop(int image, int[] area, int format, int r_value, int g_value, int b_value)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                ret = CVIPCOM.Object_Crop(ref dup, ref area[0], format, r_value, g_value, b_value);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Object_Crop", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public int Or_Image(int image1, int image2)
        {
            int dup1 = 0, dup2 = 0, ret = 0;
            try
            {
                if (image1 == 0) throw new Exception(errImageInput);
                if (image2 == 0) throw new Exception(errImageInput);

                if ((dataType)CVIPCOM.GetDataType_Image(ref image1) == dataType.CVIP_BYTE)
                    dup1 = CVIPCOM.Duplicate_Image(ref image1);
                else
                    dup1 = CVIPCOM.Remap_Image(ref image1, (int)dataType.CVIP_BYTE, 0, 255);

                if ((dataType)CVIPCOM.GetDataType_Image(ref image2) == dataType.CVIP_BYTE)
                    dup2 = CVIPCOM.Duplicate_Image(ref image2);
                else
                    dup2 = CVIPCOM.Remap_Image(ref image2, (int)dataType.CVIP_BYTE, 0, 255);

                int band1 = CVIPCOM.GetNoOfBands_Image(ref dup1);
                int band2 = CVIPCOM.GetNoOfBands_Image(ref dup2);
                if (band1 != band2)
                {
                    int tmp = 0;
                    int[] bands = new int[3];
                    if (band1 == 1)
                    {
                        tmp = dup1;
                        for (int i = 0; i < 3; i++)
                            bands[i] = tmp;
                        dup1 = CVIPCOM.Assemble_Bands(bands);
                    }
                    else if (band2 == 1)
                    {
                        tmp = dup2;
                        for (int i = 0; i < 3; i++)
                            bands[i] = tmp;
                        dup2 = CVIPCOM.Assemble_Bands(bands);
                    }
                    else
                        throw new Exception(errImageBands);
                    CVIPCOM.Delete_Image(ref tmp);
                }
                ret = CVIPCOM.Or_Image(ref dup1, ref dup2);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Or_Image", e);
                ret = 0;
            }
            finally
            {
                if (dup1 != 0) CVIPCOM.Delete_Image(ref dup1);
                if (dup2 != 0) CVIPCOM.Delete_Image(ref dup2);
            }
            return ret;
        }
        static public int Orientation(int labeledImage, int row, int col)
        {
            int orientation = 0;
            try
            {
                if (labeledImage == 0) throw new Exception(errImageInput);
                orientation = CVIPCOM.Orientation(ref labeledImage, row, col);
            }
            catch (Exception e)
            {
                ReportError("Orientation", e);
                orientation = 0;
            }
            return orientation;
        }
        static public int Otsu_Segment(int image)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                ret = CVIPCOM.Otsu_Segment(ref dup);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Otsu_Segment", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }

        static public double[] Overlap_Coef(int idealImage, int testImage)
        {
            double[] dice;
            try
            {
                if (idealImage == 0) throw new Exception(errImageInput);
                if (testImage == 0) throw new Exception(errImageInput);
                dice = CVIPCOM.Overlap_Coef(ref idealImage, ref testImage);
            }
            catch (Exception e)
            {
                ReportError("Dice", e);
                dice = null;
            }
            return dice;
        }

        static public int P_Remap(int image, int[] lookup_table)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                ret = CVIPCOM.Pseudo_Remap(ref dup, ref lookup_table[0]);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("P_Remap", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public int Param_AD_Filter(int image, int iterations, int speed, int edge_height, int blocksize)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                ret = CVIPCOM.Param_AD_Filter(ref dup, iterations, speed, edge_height, blocksize);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Param_AD_Filter", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public int Parametric_Wiener(int degr_image, int degr_fn, int psd_noise, int psd_orig, double gamma, int max_gain, int cutoff)
        {
            int dup_im = 0, dup_fn = 0, dup_noise = 0, dup_orig = 0, ret = 0;
            try
            {
                if (degr_image == 0) throw new Exception(errImageInput);
                if (degr_fn == 0) throw new Exception(errImageInput);
                if (psd_noise == 0) throw new Exception(errImageInput);
                if (psd_orig == 0) throw new Exception(errImageInput);
                dup_im = CVIPCOM.Duplicate_Image(ref degr_image);
                dup_fn = CVIPCOM.Duplicate_Image(ref degr_fn);
                dup_noise = CVIPCOM.Duplicate_Image(ref psd_noise);
                dup_orig = CVIPCOM.Duplicate_Image(ref psd_orig);
                ret = CVIPCOM.Parametric_Wiener(ref dup_im, ref dup_fn, ref dup_noise, ref dup_orig, gamma, max_gain, cutoff);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Parametric_Wiener", e);
                ret = 0;
            }
            finally
            {
                if (dup_im != 0) CVIPCOM.Delete_Image(ref dup_im);
                if (dup_fn != 0) CVIPCOM.Delete_Image(ref dup_fn);
                if (dup_noise != 0) CVIPCOM.Delete_Image(ref dup_noise);
                if (dup_orig != 0) CVIPCOM.Delete_Image(ref dup_orig);
            }
            return ret;
        }
        static public int Pct_Color(int image, bool ignore_background, ref double background, int choice)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                if (CVIPCOM.GetNoOfBands_Image(ref image) != 3) throw new Exception(errImageColor);
                dup = CVIPCOM.Duplicate_Image(ref image);
                ret = CVIPCOM.Pct_Color(ref dup, Convert.ToInt32(ignore_background), ref background, choice);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Pct_Color", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public int Pct_Median_Segment(int image, int num_colors)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                int numbands = CVIPCOM.GetNoOfBands_Image(ref dup);
                if (numbands == 1)
                {
                    int tmp = dup;
                    int[] bands = new int[3];
                    for (int i = 0; i < 3; i++)
                        bands[i] = tmp;
                    dup = CVIPCOM.Assemble_Bands(bands);
                    CVIPCOM.Delete_Image(ref tmp);
                }
                ret = CVIPCOM.Pct_Median_Segment(ref dup, num_colors);
                if (numbands == 1)
                {
                    int tmp = ret;
                    ret = CVIPCOM.Extract_Band(ref tmp, 1);
                    CVIPCOM.Delete_Image(ref tmp);
                }
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Pct_Median_Segment", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public int Perimeter(int labeledImage, int row, int col)
        {
            int perimeter = 0;
            try
            {
                if (labeledImage == 0) throw new Exception(errImageInput);
                perimeter = CVIPCOM.Perimeter(ref labeledImage, row, col);
            }
            catch (Exception e)
            {
                ReportError("Perimeter", e);
                perimeter = 0;
            }
            return perimeter;
        }
        static public int PMBTC_Compression(int image, string filename, int blocksize)
        {
            int dup = 0, success = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                CVIPCOM.Btc3_Compress(ref filename, ref dup, blocksize);
            }
            catch (Exception e)
            {
                ReportError("PMBTC_Compression", e);
                success = -1;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return success;
        }
        static public int PMBTC_Compression_Image(int image, string filename, int blocksize)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                CVIPCOM.Btc3_Compress(ref filename, ref dup, blocksize);
                ret = CVIPCOM.Btc3_Decompress(ref filename);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("PMBTC_Compression_Image", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public int PMBTC_deCompression(string filename)
        {
            int ret = 0;
            try
            {
                ret = CVIPCOM.Btc3_Decompress(ref filename);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("PMBTC_deCompression", e);
                ret = 0;
            }
            return ret;
        }
        static public int Power_Spect_Eq(int degr_image, int degr_fn, int psd_noise, int psd_orig, int max_gain, int cutoff)
        {
            int dup_im = 0, dup_fn = 0, dup_noise = 0, dup_orig = 0, ret = 0;
            try
            {
                if (degr_image == 0) throw new Exception(errImageInput);
                if (degr_fn == 0) throw new Exception(errImageInput);
                if (psd_noise == 0) throw new Exception(errImageInput);
                if (psd_orig == 0) throw new Exception(errImageInput);
                dup_im = CVIPCOM.Duplicate_Image(ref degr_image);
                dup_fn = CVIPCOM.Duplicate_Image(ref degr_fn);
                dup_noise = CVIPCOM.Duplicate_Image(ref psd_noise);
                dup_orig = CVIPCOM.Duplicate_Image(ref psd_orig);
                ret = CVIPCOM.Power_Spect_Eq(ref dup_im, ref dup_fn, ref dup_noise, ref dup_orig, max_gain, cutoff);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Power_Spect_Eq", e);
                ret = 0;
            }
            finally
            {
                if (dup_im != 0) CVIPCOM.Delete_Image(ref dup_im);
                if (dup_fn != 0) CVIPCOM.Delete_Image(ref dup_fn);
                if (dup_noise != 0) CVIPCOM.Delete_Image(ref dup_noise);
                if (dup_orig != 0) CVIPCOM.Delete_Image(ref dup_orig);
            }
            return ret;
        }
        static public double[] Pratt_Merit(int image1, int image2, double scale_factor)
        {
            double[] result = null;
            try
            {
                if (image1 == 0) throw new Exception(errImageInput);
                if (image2 == 0) throw new Exception(errImageInput);
                int numbands = CVIPCOM.GetNoOfBands_Image(ref image1);
                if (CVIPCOM.GetNoOfBands_Image(ref image2) != numbands)
                    throw new Exception(errImageBands);
                if ((CVIPCOM.GetNoOfCols_Image(ref image1) != CVIPCOM.GetNoOfCols_Image(ref image2)) ||
                    (CVIPCOM.GetNoOfRows_Image(ref image1) != CVIPCOM.GetNoOfRows_Image(ref image2)))
                    throw new Exception(errImageSize);
                if ((CVIPCOM.Check_Bin(ref image1) == 0) || (CVIPCOM.Check_Bin(ref image2) == 0))
                    throw new Exception(errImageBinary);
                result = new double[numbands];
                for (int band = 0; band < numbands; band++)
                {
                    int band1 = CVIPCOM.Extract_Band(ref image1, band + 1);
                    int band2 = CVIPCOM.Extract_Band(ref image2, band + 1);
                   // MessageBox.Show(scale_factor.ToString());

                    result[band] = CVIPCOM.Pratt_Merit(ref band1, ref band2, scale_factor);
                    CVIPCOM.Delete_Image(ref band1);
                    CVIPCOM.Delete_Image(ref band2);
                }
            }
            catch (Exception e)
            {
                ReportError("Pratt_Merit", e);
                result = null;
            }
            return result;
        }
        static public int Sobel_Filter(int image, ref int dirImage, int filter_type, int kernel_size, bool keepdc, int threshold)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                //MessageBox.Show(keepdc.ToString());
                ret = CVIPCOM.Sobel_Filter(ref dup, ref dirImage, filter_type, kernel_size, keepdc ? 1 : 0, threshold);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Sobel_Filter", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public int Prewitt_Filter(int image, ref int dirImage, int filter_type, int kernel_size, bool keepdc, int threshold)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                //MessageBox.Show(keepdc.ToString());
                ret = CVIPCOM.Prewitt_Filter(ref dup, ref dirImage, filter_type, kernel_size, keepdc ? 1 : 0, threshold);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Prewitt_Filter", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public int[] Projection(int labeledImage, int row, int col, int height, int width)
        {
            object ret = null;
            try
            {
                if (labeledImage == 0) throw new Exception(errImageInput);
                ret = CVIPCOM.Projection(ref labeledImage, row, col, height, width);
            }
            catch (Exception e)
            {
                ReportError("Projection", e);
                ret = null;
            }
            return (int[])ret;
        }
        static public int Pseudocol_Freq(int image, int lowcutoff, int highcutoff, int lowpass_band, int bandpass_band, int highpass_band)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                if (CVIPCOM.GetNoOfBands_Image(ref image) != 1) throw new Exception(errImageGray);
                if (lowcutoff >= highcutoff) throw new Exception(errCutoff);
                if ((lowpass_band == bandpass_band) ||
                    (lowpass_band == highpass_band) ||
                    (bandpass_band == highpass_band))
                    throw new Exception(errColorBands);
                dup = CVIPCOM.Duplicate_Image(ref image);
                ret = CVIPCOM.Pseudocol_Freq(ref dup, lowcutoff, highcutoff, lowpass_band, bandpass_band, highpass_band);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Pseudocol_Freq", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public int Rayleigh_Noise(int image, double variance)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                ret = CVIPCOM.Rayleigh_Noise(ref dup, variance);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Rayleigh_Noise", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public int Read_Image(string filename)
        {
            int ret = 0;
            try
            {
                ret = CVIPCOM.Read_Image(ref filename);
                if (ret == 0) throw new Exception(errFileOpen);
            }
            catch (Exception e)
            {
                ReportError("Read_Image", e);
                ret = 0;
            }
            return ret;
        }
        static public int Remap_Image(int image, dataType dt, int dmin, int dmax)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                ret = CVIPCOM.Remap_Image(ref dup, (int)dt, dmin, dmax);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Remap_Image", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public int REMAPP(int image, dataType dt, int dmin, int dmax)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                ret = CVIPCOM.REMAPP(ref dup, (int)dt, dmin, dmax);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("REMAPP", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public int Render_DisplayImage(int window_dc, int image)
        {
            int mem_dc = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                mem_dc = CVIPCOM.Render_DisplayImage(window_dc, ref image);
                if (mem_dc == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Render_DisplayImage", e);
                mem_dc = 0;
            }
            return mem_dc;
        }
        static private void ReportError(string function, Exception e)
        {
            string msg = function + "() exception: " + e.Message;
            MessageBox.Show(msg, "CvipOp Error", MessageBoxButtons.OK, MessageBoxIcon.Warning);
        }
        static public float[] Rms_Error(int image1, int image2)
        {
            int tmp1 = 0, tmp2 = 0;
            float[] result = null;
            try
            {
                if (image1 == 0) throw new Exception(errImageInput);
                if (image2 == 0) throw new Exception(errImageInput);
                if (GetNoOfBands_Image(image1) != GetNoOfBands_Image(image2))
                    throw new Exception(errImageBands);
                if ((GetNoOfCols_Image(image1) != GetNoOfCols_Image(image2)) ||
                    (GetNoOfRows_Image(image1) != GetNoOfRows_Image(image2)))
                    throw new Exception(errImageSize);
                tmp1 = Duplicate_Image(image1);
                tmp2 = Duplicate_Image(image2);
                result = CVIPCOM.Rms_Error(ref tmp1, ref tmp2);
            }
            catch (Exception e)
            {
                ReportError("Rms_Error", e);
                result = null;
            }
            if (tmp1 != 0) Delete_Image(ref tmp1);
            if (tmp2 != 0) Delete_Image(ref tmp2);
            return result;
        }
        static public int Robinson_Filter(int image, ref int dirImage, int mask_type, int masksize, bool keepdc, int threshold)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                ret = CVIPCOM.Robinson_Filter(ref dup, ref dirImage, mask_type, masksize, keepdc ? 1 : 0, threshold);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Robinson_Filter", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public int Rotate(int image, float degrees)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                ret = CVIPCOM.Rotate(ref dup, degrees);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Rotate", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public double[] Rst_invariant(int labeledImage, int row, int col)
        {
            object rst = null;
            try
            {
                if (labeledImage == 0) throw new Exception(errImageInput);
                rst = CVIPCOM.Rst_invariant(ref labeledImage, row, col);
            }
            catch (Exception e)
            {
                ReportError("Rst_invariant", e);
                rst = null;
            }
            return (double[])rst;
        }
        static public void Save_Compressed_Data(int image, string filename)
        {
            int dup = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                CVIPCOM.Save_Compressed_Data(ref dup, ref filename);
            }
            catch (Exception e)
            {
                ReportError("Save_Compressed_Data", e);
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
        }
        static public int Sct_Split_Segment(int image, int A_split, int B_split)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                int numbands = CVIPCOM.GetNoOfBands_Image(ref dup);
                if (numbands == 1)
                {
                    int tmp = dup;
                    int[] bands = new int[3];
                    for (int i = 0; i < 3; i++)
                        bands[i] = tmp;
                    dup = CVIPCOM.Assemble_Bands(bands);
                    CVIPCOM.Delete_Image(ref tmp);
                }
                ret = CVIPCOM.Sct_Split_Segment(ref dup, A_split, B_split);
                if (numbands == 1)
                {
                    int tmp = ret;
                    ret = CVIPCOM.Extract_Band(ref tmp, 1);
                    CVIPCOM.Delete_Image(ref tmp);
                }
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Sct_Split_Segment", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public void Set_Console()
        {
            int unused = 0;
            CVIPCOM.Set_Console(unused);
        }
        static public int Sharpening_AlgorithmI(int image, int remap, int mask_type, int masksize, float lowclip, float highclip, int add2original)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                ret = CVIPCOM.Sharpen_I(ref dup, remap, mask_type, masksize, lowclip, highclip, add2original);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Sharpening_AlgorithmI", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public int Sharpening_AlgorithmII(int image, int add2original)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                ret = CVIPCOM.Sharpen_II(ref dup, add2original);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Sharpening_AlgorithmII", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public int Sharpening_AlgorithmIII(int image, int add2original)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                ret = CVIPCOM.Sharpen_III(ref dup, add2original);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Sharpening_AlgorithmIII", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public int Shen_Castan_Filter(int image, double smoothing_factor, int window_size, double low_threshold, double high_threshold, int thin_factor, ref int intermediate_image)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                ret = CVIPCOM.Shen_Castan_Filter(ref dup, smoothing_factor, window_size, low_threshold, high_threshold, thin_factor, ref  intermediate_image);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Shen_Castan_Filter", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public void Show_DisplayImage(int winDC, int memDC, int winWidth, int winHeight, int memWidth, int memHeight)
        {
            try
            {
                CVIPCOM.Show_DisplayImage(winDC, memDC, winWidth, winHeight, memWidth, memHeight);
            }
            catch (Exception e)
            {
                ReportError("Show_DisplayImage", e);
            }
        }
        static public int Simple_Wiener(int degr_image, int degr_fn, double k)
        {
            int dup_im = 0, dup_fn = 0, ret = 0;
            try
            {
                if (degr_image == 0) throw new Exception(errImageInput);
                if (degr_fn == 0) throw new Exception(errImageInput);
                dup_im = CVIPCOM.Duplicate_Image(ref degr_image);
                dup_fn = CVIPCOM.Duplicate_Image(ref degr_fn);
                ret = CVIPCOM.Simple_Wiener(ref dup_im, ref dup_fn, k);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Simple_Wiener", e);
                ret = 0;
            }
            finally
            {
                if (dup_im != 0) CVIPCOM.Delete_Image(ref dup_im);
                if (dup_fn != 0) CVIPCOM.Delete_Image(ref dup_fn);
            }
            return ret;
        }
        static public float[] Snr(int image1, int image2)
        {
            int tmp1 = 0, tmp2 = 0;
            float[] result = null;
            try
            {
                if (image1 == 0) throw new Exception(errImageInput);
                if (image2 == 0) throw new Exception(errImageInput);
                if (GetNoOfBands_Image(image1) != GetNoOfBands_Image(image2))
                    throw new Exception(errImageBands);
                if ((GetNoOfCols_Image(image1) != GetNoOfCols_Image(image2)) ||
                    (GetNoOfRows_Image(image1) != GetNoOfRows_Image(image2)))
                    throw new Exception(errImageSize);
                tmp1 = Duplicate_Image(image1);
                tmp2 = Duplicate_Image(image2);
                result = CVIPCOM.Snr(ref tmp1, ref tmp2);
            }
            catch (Exception e)
            {
                ReportError("Snr", e);
                result = null;
            }
            if (tmp1 != 0) Delete_Image(ref tmp1);
            if (tmp2 != 0) Delete_Image(ref tmp2);
            return result;
        }
        
        static public int Spatial_Quant(int image, int rows, int cols, int method)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                int width = CVIPCOM.GetNoOfCols_Image(ref dup);
                int height = CVIPCOM.GetNoOfRows_Image(ref dup);
                if (width < cols) cols = width;
                if (height < rows) rows = height;
                ret = CVIPCOM.Spatial_Quant(ref dup, rows, cols, method);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Spatial_Quant", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public int Spec_Hist_Image(int image, string r_histogram, string g_histogram, string b_histogram)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                ret = CVIPCOM.Spec_Hist_Image(ref dup, ref r_histogram, ref g_histogram, ref b_histogram);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Spec_Hist_Image", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public int Specify_Filter(int image, int mask_height, int mask_width, double[] mask_values, int normalization)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
               // MessageBox.Show(mask_values[0].ToString());
                ret = CVIPCOM.Specify_Filter(ref dup, mask_height, mask_width, ref mask_values[0], normalization);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Specify_Filter", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public int Speckle_Noise(int image, double psalt, double ppepper)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                ret = CVIPCOM.Speckle_Noise(ref dup, psalt, ppepper);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Speckle_Noise", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public double[] Spectral_Feature(int image, int labeledImage, int rings, int sectors, int row, int col)
        {
            object spectral = null;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                if (labeledImage == 0) throw new Exception(errImageInput);
                spectral = CVIPCOM.Spectral_Feature(ref image, ref labeledImage, rings, sectors, row, col);
            }
            catch (Exception e)
            {
                ReportError("Spectral_Feature", e);
                spectral = null;
            }
            return (double[])spectral;
        }
        static public int Split_Merge_Segment(int image, int level, int homogeneity_test, double param1, double param2, bool runPCT)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                ret = CVIPCOM.Split_Merge_Segment(ref dup, level, homogeneity_test, param1, param2, runPCT ? 1 : 0);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Split_Merge_Segment", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public int Subtract_Image(int image1, int image2)
        {
            int dup1 = 0, dup2 = 0, ret = 0;
            try
            {
                if (image1 == 0) throw new Exception(errImageInput);
                if (image2 == 0) throw new Exception(errImageInput);
                dup1 = CVIPCOM.Duplicate_Image(ref image1);
                dup2 = CVIPCOM.Duplicate_Image(ref image2);

                int band1 = CVIPCOM.GetNoOfBands_Image(ref dup1);
                int band2 = CVIPCOM.GetNoOfBands_Image(ref dup2);
                if (band1 != band2)
                {
                    int tmp = 0;
                    int[] bands = new int[3];
                    if (band1 == 1)
                    {
                        tmp = dup1;
                        for (int i = 0; i < 3; i++)
                            bands[i] = tmp;
                        dup1 = CVIPCOM.Assemble_Bands(bands);
                    }
                    else if (band2 == 1)
                    {
                        tmp = dup2;
                        for (int i = 0; i < 3; i++)
                            bands[i] = tmp;
                        dup2 = CVIPCOM.Assemble_Bands(bands);
                    }
                    else
                        throw new Exception(errImageBands);
                    CVIPCOM.Delete_Image(ref tmp);
                }
                CVIPCOM.Cast_Image(ref dup1, (int)dataType.CVIP_FLOAT);
                CVIPCOM.Cast_Image(ref dup2, (int)dataType.CVIP_FLOAT);
                ret = CVIPCOM.Subtract_Image(ref dup1, ref dup2);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Subtract_Image", e);
                ret = 0;
            }
            finally
            {
                if (dup1 != 0) CVIPCOM.Delete_Image(ref dup1);
                if (dup2 != 0) CVIPCOM.Delete_Image(ref dup2);
            }
            return ret;
        }
        static public double[] TextureFeature(int image, int labeledImage, int row, int col, int distance, int bitmask)
        {
            object texture = null;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                if (labeledImage == 0) throw new Exception(errImageInput);
                texture = CVIPCOM.TextureFeature(ref image, ref labeledImage, row, col, distance, bitmask);
            }
            catch (Exception e)
            {
                ReportError("TextureFeature", e);
                texture = null;
            }
            return (double[])texture;
        }
        static public double[] Texture2_Feature(int image, int labeledimage, int band, int row, int col, int distance, bool energy, bool inertia, bool invDiff, bool entropy, bool correlation, bool include_zero_pairs)
        {
            double[] texture = null;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                if (labeledimage == 0) throw new Exception(errImageInput);
                texture = (double[])CVIPCOM.TextureFeature2(ref image, ref labeledimage, band, row, col, distance, energy ? 1 : 0, inertia ? 1 : 0, invDiff ? 1 : 0, entropy ? 1 : 0, correlation ? 1 : 0, include_zero_pairs ? 1 : 0);
            }
            catch (Exception e)
            {
                ReportError("TextureFeature2", e);
                texture = null;
            }
            return texture;
        }
        static public double Thinness(int labeledImage, int row, int col)
        {
            double thinness = 0;
            try
            {
                if (labeledImage == 0) throw new Exception(errImageInput);
                thinness = CVIPCOM.Thinness(ref labeledImage, row, col);
            }
            catch (Exception e)
            {
                ReportError("Thinness", e);
                thinness = 0;
            }
            return thinness;
        }
        static public int Threshold_Segment(int image, int threshold, bool byte_remap)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                ret = CVIPCOM.Threshold_Segment(ref dup, threshold, Convert.ToInt32(byte_remap));
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Threshold_Segment", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public int Transform_compression(int image, string filename, string quantfile, int color_space, int xform, int blocksize, int quantization, int use_quant_table, int use_vector_quant, int datatype, int remap_type, int keepdc)
        {
            int basis = 0, dup = 0, ret = 0;
            switch (xform)
            {
            case 0:
                xform = 1;
                basis = 0;
                break;
            case 1:
                xform = 2;
                basis = 1;
                break;
            case 2:
                xform = 2;
                basis = 2;
                break;
            default:
                xform = 1;
                basis = 0;
                break;
            }
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                ret = CVIPCOM.Transform_Compression(ref dup, ref filename, ref quantfile, color_space, xform, basis, blocksize, quantization, use_quant_table, use_vector_quant, datatype, remap_type, keepdc);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Transform_compression", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public int Translate(int image, int wrap, int row_offset, int col_offset, int rows, int cols, int row_slide, int col_slide, float fill_val)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
               // MessageBox.Show(fill_val.ToString());
                ret = CVIPCOM.Translate(ref dup, wrap, row_offset, col_offset, rows, cols, row_slide, col_slide, fill_val);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Translate", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public int Uniform_Noise(int image, double variance, double mean)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                ret = CVIPCOM.Uniform_Noise(ref dup, variance, mean);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Uniform_Noise", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public int Unsharp_Masking(int image, int lowlimit, int highlimit, double lowclip, double highclip)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                ret = CVIPCOM.Unsharp_Filter(ref dup, lowlimit, highlimit, lowclip, highclip);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Unsharp_Masking", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public int Vertical_Flip(int image)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                ret = CVIPCOM.Vertical_Flip(ref dup);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Vertical_Flip", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public int Vq_Compression(int image, string filename, int vector_height, int vector_width, int num_entries, double error_threshold, string codebook_filename, int use_file_codebook, int use_fixed_codebook)
        {
            int dup = 0, success = -1;
            try
            {
                // Read codebook from file; don't save codebook                use_file_codebook : 0 use_fixed_codebook : 1
                // Read codebook from file; save codebook with coding result   use_file_codebook : 1 use_fixed_codebook : 1
                // Generate codebook; save codebook with coding result         use_file_codebook : 1 use_fixed_codebook : 0
                // Generate codebook; save codebook into separate file         use_file_codebook : 0 use_fixed_codebook : 0
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                success = CVIPCOM.Vq_Compress(ref dup, ref filename, use_file_codebook, use_fixed_codebook, error_threshold, ref codebook_filename, num_entries, vector_height, vector_width);
            }
            catch (Exception e)
            {
                ReportError("Vq_Compression", e);
                success = -1;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return success;
        }
        static public int Vq_Compression_Image(int image, string filename, int vector_height, int vector_width, int num_entries, double error_threshold, string codebook_filename, int use_file_codebook, int use_fixed_codebook)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                CVIPCOM.Vq_Compress(ref dup, ref filename, use_file_codebook, use_fixed_codebook, error_threshold, ref codebook_filename, num_entries, vector_height, vector_width);
                ret = CVIPCOM.Vq_Decompress(ref filename);
                if (ret == 0) throw new Exception(errCodebook);
            }
            catch (Exception e)
            {
                ReportError("Vq_Compression_Image", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public int Vq_deCompression(string filename)
        {
            int ret = 0;
            try
            {
                ret = CVIPCOM.Vq_Decompress(ref filename);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Vq_deCompression", e);
                ret = 0;
            }
            return ret;
        }
        static public int Walhad_Transform(int image, int xform, int blocksize)
        {
            int dup = 0, ret = 0;
            try
            {
                
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                ret = CVIPCOM.Walhad_Transform(ref dup, xform, blocksize);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Walhad_Transform", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public int Watershed_Segment(int image, bool merge_result, double threshold)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                ret = CVIPCOM.Watershed_Segment(ref dup,merge_result ? 1 : 0, (float)threshold);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Watershed_Segment", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public int Wavdaub4_Transform(int image, int direction, int low_band)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                ret = CVIPCOM.Wavdaub4_Transform(ref dup, direction, low_band);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Wavdaub4_Transform", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public int Wavhaar_Transform(int image, int direction, int low_band)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                CVIPCOM.Cast_Image(ref dup, (int)dataType.CVIP_FLOAT);
                ret = CVIPCOM.Wavhaar_Transform(ref dup, direction, low_band);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Wavhaar_Transform", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public int Wiener(int degr_image, int degr_fn, int psd_noise, int psd_orig, int max_gain, int cutoff)
        {
            int dup_im = 0, dup_fn = 0, dup_noise = 0, dup_orig = 0, ret = 0;
            try
            {
                if (degr_image == 0) throw new Exception(errImageInput);
                if (degr_fn == 0) throw new Exception(errImageInput);
                if (psd_noise == 0) throw new Exception(errImageInput);
                if (psd_orig == 0) throw new Exception(errImageInput);
                dup_im = CVIPCOM.Duplicate_Image(ref degr_image);
                dup_fn = CVIPCOM.Duplicate_Image(ref degr_fn);
                dup_noise = CVIPCOM.Duplicate_Image(ref psd_noise);
                dup_orig = CVIPCOM.Duplicate_Image(ref psd_orig);
                ret = CVIPCOM.Wiener(ref dup_im, ref dup_fn, ref dup_noise, ref dup_orig, max_gain, cutoff);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Wiener", e);
                ret = 0;
            }
            finally
            {
                if (dup_im != 0) CVIPCOM.Delete_Image(ref dup_im);
                if (dup_fn != 0) CVIPCOM.Delete_Image(ref dup_fn);
                if (dup_noise != 0) CVIPCOM.Delete_Image(ref dup_noise);
                if (dup_orig != 0) CVIPCOM.Delete_Image(ref dup_orig);
            }
            return ret;
        }
        static public void Write_Image(int image, string filename, int retain_image, int run_setup, imageFormat imf, int verbose)
        {
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                CVIPCOM.Write_Image(ref image, ref filename, retain_image, run_setup, (int)imf, verbose);
            }
            catch (Exception e)
            {
                ReportError("Write_Image", e);
            }
        }
        static public void Write_JPEG_Image(int image, string filename, int retain_image, int run_setup, imageFormat imf, int verbose, int ratio)
        {
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                CVIPCOM.Write_JPEG_Image(ref image, ref filename, retain_image, run_setup, (int)imf, verbose, ratio);
            }
            catch (Exception e)
            {
                ReportError("Write_JPEG_Image", e);
            }
        }

        static public double[] XOR_Error(int idealImage, int testImage)
        {
            double[] dice;
            try
            {
                if (idealImage == 0) throw new Exception(errImageInput);
                if (testImage == 0) throw new Exception(errImageInput);
                dice = CVIPCOM.Xor_Error(ref idealImage, ref testImage);
            }
            catch (Exception e)
            {
                ReportError("Dice", e);
                dice = null;
            }
            return dice;
        }

        static public int Xor_Image(int image1, int image2)
        {
            int dup1 = 0, dup2 = 0, ret = 0;
            try
            {
                if (image1 == 0) throw new Exception(errImageInput);
                if (image2 == 0) throw new Exception(errImageInput);

                if ((dataType)CVIPCOM.GetDataType_Image(ref image1) == dataType.CVIP_BYTE)
                    dup1 = CVIPCOM.Duplicate_Image(ref image1);
                else
                    dup1 = CVIPCOM.Remap_Image(ref image1, (int)dataType.CVIP_BYTE, 0, 255);

                if ((dataType)CVIPCOM.GetDataType_Image(ref image2) == dataType.CVIP_BYTE)
                    dup2 = CVIPCOM.Duplicate_Image(ref image2);
                else
                    dup2 = CVIPCOM.Remap_Image(ref image2, (int)dataType.CVIP_BYTE, 0, 255);

                int band1 = CVIPCOM.GetNoOfBands_Image(ref dup1);
                int band2 = CVIPCOM.GetNoOfBands_Image(ref dup2);
                if (band1 != band2)
                {
                    int tmp = 0;
                    int[] bands = new int[3];
                    if (band1 == 1)
                    {
                        tmp = dup1;
                        for (int i = 0; i < 3; i++)
                            bands[i] = tmp;
                        dup1 = CVIPCOM.Assemble_Bands(bands);
                    }
                    else if (band2 == 1)
                    {
                        tmp = dup2;
                        for (int i = 0; i < 3; i++)
                            bands[i] = tmp;
                        dup2 = CVIPCOM.Assemble_Bands(bands);
                    }
                    else
                        throw new Exception(errImageBands);
                    CVIPCOM.Delete_Image(ref tmp);
                }
                ret = CVIPCOM.Xor_Image(ref dup1, ref dup2);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Xor_Image", e);
                ret = 0;
            }
            finally
            {
                if (dup1 != 0) CVIPCOM.Delete_Image(ref dup1);
                if (dup2 != 0) CVIPCOM.Delete_Image(ref dup2);
            }
            return ret;
        }
        static public int XVQ_Compression(int image, int xform, int scheme, string filename, int output_data_type, int remap_type, int keepdc)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                ret = CVIPCOM.Xvq_Compress(ref dup, xform, scheme, ref filename, output_data_type, remap_type, keepdc);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("XVQ_Compression", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public int Ypmean_Filter(int image, int masksize, int p)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                ret = CVIPCOM.Ypmean_Filter(ref dup, masksize, p);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Ypmean_Filter", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public int Zonal_Compression(int image, string filename, int blocksize, int xform, int mask_type, float compression_ratio, int keepdc)
        {
            int dup = 0, success = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                if (keepdc != 0)
                    CVIPCOM.Zon_Compress(ref filename, ref dup, blocksize, xform, mask_type, compression_ratio);
                else
                    CVIPCOM.Zon2_Compress(ref filename, ref dup, blocksize, xform, mask_type, compression_ratio);
            }
            catch (Exception e)
            {
                ReportError("Zonal_Compression", e);
                success = -1;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return success;
        }
        static public int Zonal_Compression_Image(int image, string filename, int blocksize, int xform, int mask_type, double compression_ratio, int keepdc)
        {
            int ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                if (keepdc != 0)
                    ret = Zonal1_Compression_Image(image, filename, blocksize, xform, mask_type, (float)compression_ratio);
                else
                    ret = Zonal2_Compression_Image(image, filename, blocksize, xform, mask_type, (float)compression_ratio);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Zonal_Compression_Image", e);
                ret = 0;
            }
            return ret;
        }
        static public int Zonal1_Compression(int image, string filename, int blocksize, int xform, int mask_type, float compression_ratio)
        {
            int dup = 0, success = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                CVIPCOM.Zon_Compress(ref filename, ref dup, blocksize, xform, mask_type, compression_ratio);
            }
            catch (Exception e)
            {
                ReportError("Zonal1_Compression", e);
                success = -1;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return success;
        }
        static public int Zonal1_Compression_Image(int image, string filename, int blocksize, int xform, int mask_type, float compression_ratio)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                CVIPCOM.Zon_Compress(ref filename, ref dup, blocksize, xform, mask_type, compression_ratio);
                ret = CVIPCOM.Zon_Decompress(ref filename);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Zonal1_Compression_Image", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public int Zonal1_deCompression(string filename)
        {
            int ret = 0;
            try
            {
                ret = CVIPCOM.Zon_Decompress(ref filename);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Zonal1_deCompression", e);
                ret = 0;
            }
            return ret;
        }
        static public int Zonal2_Compression(int image, string filename, int blocksize, int xform, int mask_type, float compression_ratio)
        {
            int dup = 0, success = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                CVIPCOM.Zon2_Compress(ref filename, ref dup, blocksize, xform, mask_type, compression_ratio);
            }
            catch (Exception e)
            {
                ReportError("Zonal2_Compression", e);
                success = -1;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return success;
        }
        static public int Zonal2_Compression_Image(int image, string filename, int blocksize, int xform, int mask_type, float compression_ratio)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                
                CVIPCOM.Zon2_Compress(ref filename, ref dup, blocksize, xform, mask_type, compression_ratio);
                ret = CVIPCOM.Zon2_Decompress(ref filename);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Zonal2_Compression_Image", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public int Zonal2_deCompression(string filename)
        {
            int ret = 0;
            try
            {
                ret = CVIPCOM.Zon2_Decompress(ref filename);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Zonal2_deCompression", e);
                ret = 0;
            }
            return ret;
        }
        static public int Zoom(int image, int quadrant, int col, int row, int cols, int rows, float factor_requested)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                ret = CVIPCOM.Zoom(ref dup, quadrant, col, row, cols, rows, factor_requested);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("Zoom", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public int ZVL_Compression(int image, string filename)
        {
            int dup = 0, success = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                CVIPCOM.Zvl_Compress(ref filename, ref dup);
            }
            catch (Exception e)
            {
                ReportError("ZVL_Compression", e);
                success = -1;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return success;
        }
        static public int ZVL_Compression_Image(int image, string filename)
        {
            int dup = 0, ret = 0;
            try
            {
                if (image == 0) throw new Exception(errImageInput);
                dup = CVIPCOM.Duplicate_Image(ref image);
                CVIPCOM.Zvl_Compress(ref filename, ref dup);
                ret = CVIPCOM.Zvl_Decompress(ref filename);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("ZVL_Compression_Image", e);
                ret = 0;
            }
            finally
            {
                if (dup != 0) CVIPCOM.Delete_Image(ref dup);
            }
            return ret;
        }
        static public int ZVL_deCompression(string filename)
        {
            int ret = 0;
            try
            {
                ret = CVIPCOM.Zvl_Decompress(ref filename);
                if (ret == 0) throw new Exception(errImageOutput);
            }
            catch (Exception e)
            {
                ReportError("ZVL_deCompression", e);
                ret = 0;
            }
            return ret;
        }
    }
}
