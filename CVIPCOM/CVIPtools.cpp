/*''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
/*''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' ======================================================================
' Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
' ======================================================================
'
'             File Name: CVIPtools.cpp
'           Description: Contains controls and code
'                        for CCVIPtools class
'         Related Files: CVIPC Directory
'                        Include Directory
'   Initial Coding Date: July 2002
'              Modified: January 2013
'       Delevoping tool: Visual Studio 2010-C++
'             Credit(s): Patrick Solt,Hari Siva Kumar Reddy Bhogala
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

#include "stdafx.h"
#include "CVIPtools.h"

#include "CVIPconvert.h"
#include "CVIParithlogic.h"
#include "CVIPcolor.h"
#include "CVIPdisplay.h"
#include "CVIPdrawimg.h"
#include "CVIPfeatures.h"
#include "CVIPfs.h"
#include "CVIPgeometry.h"
#include "CVIPhisto.h"
#include "CVIPjpeg.h"
#include "CVIPmesh.h"
#include "CVIPmorph.h"
#include "CVIPnoise.h"
#include "CVIPpattern.h"
#include "CVIPsegment.h"
#include "CVIPspfltr.h"
#include "CVIPtexture.h"
#include "CVIPtransform.h"
#include "CVIPxformfilter.h"

// CCVIPtools

STDMETHODIMP CCVIPtools::superPixel(long* image, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* im = ::duplicate_Image((Image*)(*image));
    Image* ret = ::superPixel(im);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Ace2_Filter(long* image, long masksize, double local_mean, double local_gain, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* im = ::duplicate_Image((Image*)(*image));
    Image* ret = ::ace2_filter(im, masksize, local_mean, local_gain);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Acuity_Nightvision_Filter(long* image, long reason, long threshold, long acuity, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    char ch = (reason == 0) ? 'n' : 'y';
    Image* im = ::duplicate_Image((Image*)(*image));
    Image* ret = ::acuity_nightvision_filter(im, ch, (int)threshold, (int)acuity);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::AD_Filter(long* image, long iterations, long speed, long edge_height, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* im = ::duplicate_Image((Image*)(*image));
    Image* ret = ::ad_filter(im, (int)iterations, (int)speed, (int)edge_height);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Adapt_Median_Filter(long* image, long masksize, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* im = ::duplicate_Image((Image*)(*image));
    Image* ret = ::adapt_median_filter(im, (int)masksize);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Adaptive_Contrast_Filter(long* image, double k1, double k2, long kernel_size, double min_gain, double max_gain, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* im = ::duplicate_Image((Image*)(*image));
    Image* ret = ::adaptive_contrast_filter(im, (float)k1, (float)k2, (unsigned int)kernel_size, (float)min_gain, (float)max_gain);
    ::delete_Image(im);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Add_Image(long* image1, long* image2, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* im1 = ::duplicate_Image((Image*)(*image1));
    Image* im2 = ::duplicate_Image((Image*)(*image2));
    Image* ret = ::add_Image(im1, im2);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Alpha_Filter(long* image, long masksize, long p, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* im = ::duplicate_Image((Image*)(*image));
    Image* ret = ::alpha_filter(im, (int)masksize, (int)p);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::And_Image(long* image1, long* image2, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* im1 = ::duplicate_Image((Image*)(*image1));
    Image* im2 = ::duplicate_Image((Image*)(*image2));
    Image* ret = ::and_Image(im1, im2);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Area(long* labeled_image, int row, int col, long* area)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    *area = ::area((Image*)(*labeled_image), row, col);
    return S_OK;
}
STDMETHODIMP CCVIPtools::Aspect(long* labeled_image, int row, int col, double* aspect)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    *aspect = ::aspect((Image*)(*labeled_image), row, col);
    return S_OK;
}
STDMETHODIMP CCVIPtools::Assemble_Bands(long bands[3], long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* im[3];
    im[0] = ::duplicate_Image((Image*)bands[0]);
    im[1] = ::duplicate_Image((Image*)bands[1]);
    im[2] = ::duplicate_Image((Image*)bands[2]);
    Image* ret = ::assemble_bands(im, 3);
    ::delete_Image(im[0]);
    ::delete_Image(im[1]);
    ::delete_Image(im[2]);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Auto_Threshold_Segment(long* image, float limit, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* im = ::duplicate_Image((Image*)(*image));
    Image* ret = ::auto_threshold_segment(im, limit);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Bilinear_Interp(long* image, float factor, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* im = ::duplicate_Image((Image*)(*image));
    Image* ret = ::bilinear_interp(im, factor);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Bilinear_Interp1(long* image, float xfactor, float yfactor, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* im = ::duplicate_Image((Image*)(*image));
    Image* ret = ::bilinear_interp1(im, xfactor, yfactor);
    ::delete_Image(im);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Bintocvip(BSTR* filename, long bands, long color_order, long interleaved, int height, int width, long verbose, long* cvip_image)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    char buf[_MAX_PATH];
    ::WideCharToMultiByte(CP_ACP, 0, *filename, -1, buf, _MAX_PATH, NULL, NULL);
    FILE* inputfile = fopen(buf, "rwb");
    Image* ret = ::bintocvip(buf, inputfile, bands, (COLOR_ORDER)color_order, (INTERLEAVE_SCHEME)interleaved, height, width, (CVIP_BOOLEAN)verbose);
    fclose(inputfile);
    if (ret == NULL)
        return 0;
    *cvip_image = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Bit_Compress(BSTR* filename, long* image, long bitmask)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    char fname[_MAX_PATH];
    ::WideCharToMultiByte(CP_ACP, 0, *filename, -1, fname, _MAX_PATH, NULL, NULL);

    Image* im = NULL;
    if (getDataType_Image((Image*)(*image)) == CVIP_BYTE)
        im = ::duplicate_Image((Image*)(*image));
    else
        im = ::remap_Image((Image*)(*image), CVIP_BYTE, 0, 255);

    int result = ::bit_compress(im, fname, (byte)bitmask);
    if (result != 0)
        return -1;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Bit_Decompress(BSTR* filename, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    char fname[_MAX_PATH];
    ::WideCharToMultiByte(CP_ACP, 0, *filename, -1, fname, _MAX_PATH, NULL, NULL);
    Image* ret = ::bit_decompress(fname);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Boiecox_Filter(long* image, double variance, long do_threshold, long do_hyst, long do_thin, double high_threshold, double low_threshold, long* threshhold_image, long* hyst_image, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* im = ::duplicate_Image((Image*)(*image));
    Image* hyst = (Image*)calloc(1, sizeof(Image));
    Image* thresh = (Image*)calloc(1, sizeof(Image));
    Image* ret = ::boiecox_filter(im, (float)variance, (unsigned int)do_threshold, (unsigned int)do_hyst, (unsigned int)do_thin, (float)high_threshold, (float)low_threshold, thresh, hyst);
    ::delete_Image(im);
    if (ret == NULL)
        return 0;
    *hyst_image = (long)hyst;
    *threshhold_image = (long)thresh;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Btc_Compress(BSTR* filename, long* image, long blocksize)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    char fname[_MAX_PATH];
    ::WideCharToMultiByte(CP_ACP, 0, *filename, -1, fname, _MAX_PATH, NULL, NULL);

    Image* im = NULL;
    if (getDataType_Image((Image*)(*image)) == CVIP_BYTE)
        im = ::duplicate_Image((Image*)(*image));
    else
        im = ::remap_Image((Image*)(*image), CVIP_BYTE, 0, 255);

    int result = ::btc_compress(im, fname, blocksize);
    if (result != 0)
        return -1;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Btc_Decompression(BSTR* filename, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    char fname[_MAX_PATH];
    ::WideCharToMultiByte(CP_ACP, 0, *filename, -1, fname, _MAX_PATH, NULL, NULL);
    Image* ret = ::btc_decompress(fname);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Btc2_Compress(BSTR* filename, long* image, long blocksize)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    char fname[_MAX_PATH];
    ::WideCharToMultiByte(CP_ACP, 0, *filename, -1, fname, _MAX_PATH, NULL, NULL);

    Image* im = NULL;
    if (getDataType_Image((Image*)(*image)) == CVIP_BYTE)
        im = ::duplicate_Image((Image*)(*image));
    else
        im = ::remap_Image((Image*)(*image), CVIP_BYTE, 0, 255);

    int result = ::btc2_compress(im, fname, blocksize);
    if (result != 0)
        return -1;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Btc2_Decompress(BSTR* filename, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    char fname[_MAX_PATH];
    ::WideCharToMultiByte(CP_ACP, 0, *filename, -1, fname, _MAX_PATH, NULL, NULL);
    Image* ret = ::btc2_decompress(fname);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Btc3_Compress(BSTR* filename, long* image, long blocksize)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    char fname[_MAX_PATH];
    ::WideCharToMultiByte(CP_ACP, 0, *filename, -1, fname, _MAX_PATH, NULL, NULL);

    Image* im = NULL;
    if (getDataType_Image((Image*)(*image)) == CVIP_BYTE)
        im = ::duplicate_Image((Image*)(*image));
    else
        im = ::remap_Image((Image*)(*image), CVIP_BYTE, 0, 255);

    int result = ::btc3_compress(im, fname, blocksize);
    if (result != 0)
        return -1;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Btc3_Decompress(BSTR* filename, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    char fname[_MAX_PATH];
    ::WideCharToMultiByte(CP_ACP, 0, *filename, -1, fname, _MAX_PATH, NULL, NULL);
    Image* ret = ::btc3_decompress(fname);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Butterworth_Band_Pass(long* image, long blocksize, long keepdc, long inner_cutoff, long outer_cutoff, long filter_order, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* im = ::duplicate_Image((Image*)(*image));
    Image* ret = ::Butterworth_Band_Pass(im, (int)blocksize, (int)keepdc, (int)inner_cutoff, (int)outer_cutoff, (int)filter_order);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Butterworth_Band_Reject(long* image, long blocksize, long keepdc, long inner_cutoff, long outer_cutoff, long filter_order, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* im = ::duplicate_Image((Image*)(*image));
    Image* ret = ::Butterworth_Band_Reject(im, (int)blocksize, (int)keepdc, (int)inner_cutoff, (int)outer_cutoff, (int)filter_order);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Butterworth_High(long* image, long blocksize, long keepdc, long cutoff, long filter_order, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* im = ::duplicate_Image((Image*)(*image));
    Image* ret = ::Butterworth_High(im, (int)blocksize, (int)keepdc, (int)cutoff, (int)filter_order);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Butterworth_Low(long* image, long blocksize, long keepdc, long cutoff, long filter_order, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* im = ::duplicate_Image((Image*)(*image));
    Image* ret = ::Butterworth_Low(im, (int)blocksize, (int)keepdc, (int)cutoff, (int)filter_order);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Canny_Filter(long* image, double low_threshold, double high_threshold, double variance, long* mag_image, long* dir_image, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* im = ::duplicate_Image((Image*)(*image));
    Image* mag = (Image*)calloc(1, sizeof(Image));
    Image* dir = (Image*)calloc(1, sizeof(Image));
    Image* ret = ::canny_filter((float)low_threshold, (float)high_threshold, (float)variance, im, mag, dir);
    ::delete_Image(im);
    if (ret == NULL)
        return 0;
    *mag_image = (long)mag;
    *dir_image = (long)dir;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Cast_Image(long* image, long datatype)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    ::cast_Image((Image*)(*image), (CVIP_TYPE)datatype);
    return S_OK;
}
STDMETHODIMP CCVIPtools::CentroID(long* labeled_image, long row, long col, VARIANT* centroid)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* im = (Image*)(*labeled_image);
    int* result = ::centroid(im, row, col);
    if (result == NULL)
        return 0;

    // Create the safe-array...
    COleSafeArray saRet;
    DWORD numElements = 2;
    saRet.Create(VT_I4, 1, &numElements);

    for (long idx = 0; idx < numElements; idx++)
        saRet.PutElement(&idx, result + idx);
    free(result);
    *centroid = saRet.Detach();
    return S_OK;
}
STDMETHODIMP CCVIPtools::Cerchar_Filter(long* image, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* im = ::duplicate_Image((Image*)(*image));
    Image* ret = ::cerchar_filter(im);
    ::delete_Image(im);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Check_Bin(long* image, long* is_binary)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    *is_binary = chk_bin((Image*)(*image));
    return S_OK;
}
STDMETHODIMP CCVIPtools::Check_xform_history(long* image, int filter_type, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    ::check_xform_history((Image*)(*image), filter_type, (PROGRAMS*)result);
    return S_OK;
}
STDMETHODIMP CCVIPtools::CLAHE(long* image, int blocksize, double clippercent, int band, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* im = NULL;
    if (getDataType_Image((Image*)(*image)) == CVIP_BYTE)
        im = ::duplicate_Image((Image*)(*image));
    else
        im = ::remap_Image((Image*)(*image), CVIP_BYTE, 0, 255);

    Image* ret = NULL;
    if (im->bands == 1)
        ret = ::CLAHE(im, blocksize, clippercent, 0);
    else
    {
        if (band != 0)
            ret = ::CLAHE(im, blocksize, clippercent, band - 1);
        else
        {
            float norm[3] = { 255.0f, 255.0f, 255.0f };
            float ref[3] = { 1.0f, 1.0f, 1.0f };
            Image* fwd_xform = NULL, * remap = NULL, * eq = NULL, * eb1 = NULL, * eb2 = NULL, * eb3 = NULL, * ret1 = NULL;
            Image* temp, * temp2 = NULL;
            fwd_xform = ::colorxform(im, HSL, norm, ref, 1); //Do the HSL xform
            remap = ::remap_Image(fwd_xform, CVIP_BYTE, 0, 255);
            temp = ::duplicate_Image(remap);
            temp2 = ::duplicate_Image(remap);
            eb1 = ::extract_band(remap, 1);
            eb2 = ::extract_band(temp, 2);
            eb3 = ::extract_band(temp2, 3);
            eq = ::CLAHE(eb3, blocksize, clippercent, 0);
            Image* imm[3];
            imm[0] = eb1;
            imm[1] = eb2;
            imm[2] = eq;
            ret1 = ::assemble_bands(imm, 3);
            ::delete_Image(imm[0]);
            ::delete_Image(imm[1]);
            ::delete_Image(imm[2]);
            // eq = ::histeq(remap, 2); //Do the histogram equalization over the "Lightness" band
            ret = ::colorxform(ret1, HSL, norm, ref, -1); //Do the inverse HSL xform
            ::delete_Image(fwd_xform);
        }
    }
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::CLAHE_Grid(long* image, int blocksize, double clippercent, int band, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* im = NULL;
    if (getDataType_Image((Image*)(*image)) == CVIP_BYTE)
        im = ::duplicate_Image((Image*)(*image));
    else
        im = ::remap_Image((Image*)(*image), CVIP_BYTE, 0, 255);

    Image* ret = NULL;
    if (im->bands == 1)
        ret = ::CLAHE_Grid(im, blocksize, clippercent, 0);
    else
    {
        if (band != 0)
            ret = ::CLAHE_Grid(im, blocksize, clippercent, band - 1);
        else
        {
            float norm[3] = { 255.0f, 255.0f, 255.0f };
            float ref[3] = { 1.0f, 1.0f, 1.0f };
            Image* fwd_xform = NULL, * remap = NULL, * eq = NULL, * eb1 = NULL, * eb2 = NULL, * eb3 = NULL, * ret1 = NULL;
            Image* temp, * temp2 = NULL;
            fwd_xform = ::colorxform(im, HSL, norm, ref, 1); //Do the HSL xform
            remap = ::remap_Image(fwd_xform, CVIP_BYTE, 0, 255);
            temp = ::duplicate_Image(remap);
            temp2 = ::duplicate_Image(remap);
            eb1 = ::extract_band(remap, 1);
            eb2 = ::extract_band(temp, 2);
            eb3 = ::extract_band(temp2, 3);
            eq = ::CLAHE_Grid(eb3, blocksize, clippercent, 0);
            Image* imm[3];
            imm[0] = eb1;
            imm[1] = eb2;
            imm[2] = eq;
            ret1 = ::assemble_bands(imm, 3);
            ::delete_Image(imm[0]);
            ::delete_Image(imm[1]);
            ::delete_Image(imm[2]);
            // eq = ::histeq(remap, 2); //Do the histogram equalization over the "Lightness" band
            ret = ::colorxform(ret1, HSL, norm, ref, -1); //Do the inverse HSL xform
            ::delete_Image(fwd_xform);
        }
    }
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Close_Consol()
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    ::FreeConsole();
    return S_OK;
}
STDMETHODIMP CCVIPtools::Close_Console()
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    if (hStdout)
    {
        fclose(fpStdout);
        CloseHandle(hStdout);
        fpStdout = NULL;
        hStdout = NULL;
    }
    if (hStderr)
    {
        fclose(fpStderr);
        CloseHandle(hStderr);
        fpStderr = NULL;
        hStderr = NULL;
    }
    return S_OK;
}
STDMETHODIMP CCVIPtools::Color_Contrast_Enhance(long* image, long low_limit, long high_limit, float low_clip, float high_clip, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* im = ::duplicate_Image((Image*)(*image));
    Image* ret = ::color_contrast_enhance(im, low_limit, high_limit, low_clip, high_clip);
    ::delete_Image(im);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::ColorXform(long* image, long color_space, double* norm_vector, double* white_reference, long direction, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    float *pnorm = NULL, *pwhite = NULL;
    float norm[3], white[3];

    if ((norm_vector[0] != 0.0) ||
        (norm_vector[1] != 0.0) ||
        (norm_vector[2] != 0.0))
    {
        norm[0] = (float)norm_vector[0];
        norm[1] = (float)norm_vector[1];
        norm[2] = (float)norm_vector[2];
        pnorm = norm;
    }
    if ((white_reference[0] != 0.0) ||
        (white_reference[1] != 0.0) ||
        (white_reference[2] != 0.0))
    {
        white[0] = (float)white_reference[0];
        white[1] = (float)white_reference[1];
        white[2] = (float)white_reference[2];
        pwhite = white;
    }
    Image* im = ::duplicate_Image((Image*)(*image));
    Image* ret = ::colorxform(im, (COLOR_FORMAT)color_space, pnorm, pwhite, direction);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::CondRemap_Image(long* image, long datatype, int min, int max, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* im = ::duplicate_Image((Image*)(*image));
    Image* ret = ::condRemap_Image(im, (CVIP_TYPE)datatype, min, max);
    ::delete_Image(im);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Contra_Filter(long* image, long masksize, long p, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* im = ::duplicate_Image((Image*)(*image));
    Image* ret = ::contra_filter(im, (int)masksize, (int)p);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Copy_Paste(long* src_image, long* dest_image, int src_row, int src_col, int height, int width, int dest_row, int dest_col, long transparent, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* src = ::duplicate_Image((Image*)(*src_image));
    Image* dest = ::duplicate_Image((Image*)(*dest_image));
    Image* ret = ::copy_paste(src, dest, src_row, src_col, height, width, dest_row, dest_col, (CVIP_BOOLEAN)transparent);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Create_Black(int width, int height, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* ret = ::create_black(width, height);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Create_Checkboard(int width, int height, int start_col, int start_row, int blockx, int blocky, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* ret = ::create_checkboard(width, height, start_col, start_row, blockx, blocky);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Create_Circle(int width, int height, int centerx, int centery, int radius, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* ret = ::create_circle(width, height, centerx, centery, radius);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Create_Cosine(int img_size, int frequency, int direction, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* ret = ::create_cosine(img_size, frequency, direction);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Create_Degenerate_Circle(int width, int height, int centerx, int centery, int radius, int blur, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* ret = ::create_degenerate_circle(width, height, centerx, centery, radius, blur);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Create_Ellipse(int width, int height, int centerx, int centery, int shape_width, int shape_height, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* ret = ::create_ellipse(width, height, centery, centerx, shape_width, shape_height);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Create_Line(int width, int height, int tlx, int tly, int brx, int bry, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* ret = ::create_line(width, height, tlx, tly, brx, bry);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Create_Mask(long width, long height, double* values, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* mask = ::create_black(width, height);
    if (mask == NULL)
        return 0;
    byte** data = (byte**)getData_Image(mask, 0);
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
            data[row][col] = (byte)values[(row * width) + col];
    }
    *result = (long)mask;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Create_Mesh_Sine(int rows, int cols, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    int oldx = 0, oldy = 0, newx = 0, newy = 0;
    struct mesh* ret = (struct mesh*)malloc(sizeof(struct mesh));
    if (ret == NULL)
        return 0;

    ret->height = rows;
    ret->width = cols;
    ret->nodes = (struct mesh_node**)malloc(sizeof(struct mesh_node*) * cols);
    for (int col = 0; col < cols; col++)
        ret->nodes[col] = (struct mesh_node*)calloc(rows, sizeof(struct mesh_node));

    oldy = 0;
    for (int row = 0; row < rows; row++)
    {
        oldx = 0;
        newy = oldy + abs((int)((25 * cos((double)row)) + 0.5));
        newy = min(newy, 511);
        for (int col = 0; col < cols; col++)
        {
            newx = oldx + abs((int)((25 * sin((double)col)) + 0.5));
            newx = min(newx, 511);
            ret->nodes[col][row].x = newx;
            ret->nodes[col][row].y = newy;
            oldx = newx;
        }
        oldy = newy;
    }
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Create_Rectangle(int width, int height, int tlx, int tly, int shape_width, int shape_height, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* ret = ::create_rectangle(width, height, tlx, tly, shape_width, shape_height);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Create_Sine(int img_size, int frequency, int direction, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* ret = ::create_sine(img_size, frequency, direction);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Create_Squarewave(int img_size, int frequency, int direction, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* ret = ::create_squarewave(img_size, frequency, direction);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Crop(long* image, int start_row, int start_col, int rows, int cols, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* im = ::duplicate_Image((Image*)(*image));
    Image* ret = ::crop(im, start_row, start_col, rows, cols);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::CVIP_OUTPUT(BSTR* message)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    USES_CONVERSION;
    fflush(stdout); // necessary, or you could wait long time before seeing lines
    fflush(stderr);

    DWORD nStdout = 0, nStderr = 0;
    LPTSTR buffer = (LPTSTR)VirtualAlloc(NULL, CCVIPtools::nBufferSize, MEM_COMMIT, PAGE_READWRITE);

    // look first in the pipe to prevent ReadFile from blocking
    if (PeekNamedPipe(hStdout, buffer, CCVIPtools::nBufferSize - 1, &nStdout, NULL, NULL) &&
        (nStdout != 0))
    {
        ReadFile(hStdout, buffer, nStdout, &nStdout, NULL);
    }
    if (PeekNamedPipe(hStderr, buffer + nStdout, CCVIPtools::nBufferSize - nStdout - 1, &nStderr, NULL, NULL) &&
        (nStderr != 0))
    {
        ReadFile(hStderr, buffer + nStdout, nStderr, &nStderr, NULL);
    }
    buffer[nStdout + nStderr] = '\0';
    for (DWORD i = 0; i < nStdout + nStderr; i++)
    {
        if (buffer[i] == _T('\b'))
            buffer[i] = ' ';
    }
    CComBSTR bstr(buffer);
    *message = bstr.Detach();
    VirtualFree((LPVOID)buffer, 0, MEM_RELEASE);
    return S_OK;
}
STDMETHODIMP CCVIPtools::CVIPhalftone(long* image, int halftone_method, int maxval, float threshold, long retain_image, long verbose, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* im = ::duplicate_Image((Image*)(*image));
    Image* ret = ::CVIPhalftone(im, halftone_method, maxval, threshold, (CVIP_BOOLEAN)retain_image, (CVIP_BOOLEAN)verbose);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Cviptoccc(BSTR* filename, long maxcolor, long verbose, long dermvis, long* cvip_image)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    char fname[_MAX_PATH];
    ::WideCharToMultiByte(CP_ACP, 0, *filename, -1, fname, _MAX_PATH, NULL, NULL);
    FILE* inputfile = fopen(fname, "rwb");
    ::cviptoccc((Image*)(*cvip_image), fname, inputfile, maxcolor, dermvis, verbose);
    fclose(inputfile);
    return S_OK;
}
STDMETHODIMP CCVIPtools::Cviptoeps(BSTR* filename, long* cvip_image, double scale_x, double scale_y, long band, long verbose)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    char fname[_MAX_PATH];
    ::WideCharToMultiByte(CP_ACP, 0, *filename, -1, fname, _MAX_PATH, NULL, NULL);
    FILE* inputfile = fopen(fname, "rwb");
    ::cviptoeps((Image*)(*cvip_image), fname, inputfile, (float)scale_x, (float)scale_y, band, (CVIP_BOOLEAN)verbose);
    fclose(inputfile);
    return S_OK;
}
STDMETHODIMP CCVIPtools::Cviptogif(BSTR* filename, long* cvip_image, long interlace, long verbose)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    char fname[_MAX_PATH];
    ::WideCharToMultiByte(CP_ACP, 0, *filename, -1, fname, _MAX_PATH, NULL, NULL);
    FILE* inputfile = fopen(fname, "rwb");
    ::cviptogif((Image*)(*cvip_image), fname, inputfile, interlace, verbose);
    fclose(inputfile);
    return S_OK;
}
STDMETHODIMP CCVIPtools::Cviptoiris(BSTR* filename, long* cvip_image, long verbose, long prt_type)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    char fname[_MAX_PATH];
    ::WideCharToMultiByte(CP_ACP, 0, *filename, -1, fname, _MAX_PATH, NULL, NULL);
    FILE* inputfile = fopen(fname, "rwb");
    ::cviptoiris((Image*)(*cvip_image), fname, inputfile, prt_type, verbose);
    fclose(inputfile);
    return S_OK;
}
STDMETHODIMP CCVIPtools::Cviptoitex(BSTR* filename, long* cvip_image, BSTR* comment, long verbose)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    char fname[_MAX_PATH];
    char image_comment[64000];
    ::WideCharToMultiByte(CP_ACP, 0, *filename, -1, fname, _MAX_PATH, NULL, NULL);
    ::WideCharToMultiByte(CP_ACP, 0, *filename, -1, image_comment, 64000, NULL, NULL);
    FILE* inputfile = fopen(fname, "rwb");
    ::cviptoitex((Image*)(*cvip_image), fname, inputfile, image_comment, (CVIP_BOOLEAN)verbose);
    fclose(inputfile);
    return S_OK;
}
STDMETHODIMP CCVIPtools::Cviptojpg(BSTR* filename, long* cvip_image, int quality, long grayscale, long optimize, int smooth, long verbose, BSTR* qtablesFile)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    char fname[_MAX_PATH];
    char qtablesfname[_MAX_PATH];
    ::WideCharToMultiByte(CP_ACP, 0, *filename, -1, fname, _MAX_PATH, NULL, NULL);
    ::WideCharToMultiByte(CP_ACP, 0, *qtablesFile, -1, qtablesfname, _MAX_PATH, NULL, NULL);
    if (::jpg_compress((Image*)(*cvip_image), fname, quality, (CVIP_BOOLEAN)grayscale, (CVIP_BOOLEAN)optimize, smooth, (CVIP_BOOLEAN)verbose, qtablesfname) != 0)
        return -1;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Cviptopnm(BSTR* filename, long* cvip_image, long verbose)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    char fname[_MAX_PATH];
    ::WideCharToMultiByte(CP_ACP, 0, *filename, -1, fname, _MAX_PATH, NULL, NULL);
    FILE* inputfile = fopen(fname, "rwb");
    ::cviptopnm((Image*)(*cvip_image), fname, inputfile, verbose);
    fclose(inputfile);
    return S_OK;
}
STDMETHODIMP CCVIPtools::Cviptoras(BSTR* filename, long* cvip_image, long pr_type, long verbose)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    char fname[_MAX_PATH];
    ::WideCharToMultiByte(CP_ACP, 0, *filename, -1, fname, _MAX_PATH, NULL, NULL);
    FILE* inputfile = fopen(fname, "rwb");
    ::cviptoras((Image*)(*cvip_image), fname, inputfile, pr_type, verbose);
    fclose(inputfile);
    return S_OK;
}
STDMETHODIMP CCVIPtools::Cviptotiff(BSTR* filename, long* cvip_image, long compression, long fillorder, long g3options, long predictor, long rowsperstrip, long verbose)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    char fname[_MAX_PATH];
    ::WideCharToMultiByte(CP_ACP, 0, *filename, -1, fname, _MAX_PATH, NULL, NULL);
    FILE* inputfile = fopen(fname, "rwb");
    ::cviptotiff((Image*)(*cvip_image), fname, (unsigned short)compression, (unsigned short)fillorder, g3options, (unsigned short)predictor, rowsperstrip, verbose);
    fclose(inputfile);
    return S_OK;
}
STDMETHODIMP CCVIPtools::Cviptovip(BSTR* filename, long* cvip_image, long verbose, long save_history, long is_compressed)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    char fname[_MAX_PATH];
    ::WideCharToMultiByte(CP_ACP, 0, *filename, -1, fname, _MAX_PATH, NULL, NULL);
    FILE* inputfile = fopen(fname, "rwb");
    ::cviptovip((Image*)(*cvip_image), fname, inputfile, (CVIP_BOOLEAN)save_history, (CVIP_BOOLEAN)is_compressed, (CVIP_BOOLEAN)verbose);
    fclose(inputfile);
    return S_OK;
}
STDMETHODIMP CCVIPtools::Date_Range(long* image, VARIANT* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    DWORD numElements = 4 * getNoOfBands_Image((Image*)(*image));
    double* min_max = new double[numElements];

    Get_max_min_value(image, min_max);

    // Create the safe-array...
    COleSafeArray saRet;
    saRet.Create(VT_R8, 1, &numElements);
    for (long idx = 0; idx < numElements; idx++)
        saRet.PutElement(&idx, min_max + idx);
    delete [] min_max;
    *result = saRet.Detach();
    return S_OK;
}
STDMETHODIMP CCVIPtools::Dct_Transform(long* image, long blocksize, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* im = ::duplicate_Image((Image*)(*image));
    int rows, cols;
    if (get_zpad_dims(im, &rows, &cols, blocksize) == CVIP_YES)
        zero_pad(im, rows, cols);
    Image* ret = ::dct_transform(im, (int)blocksize);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Delete_DisplayImage(long memory_dc)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    ::DeleteDC((HDC)memory_dc);
    return S_OK;
}
STDMETHODIMP CCVIPtools::Delete_Image(long* image)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    ::delete_Image((Image*)(*image));
    return S_OK;
}
STDMETHODIMP CCVIPtools::Dice_Coef(long* image1, long* image2, VARIANT* error_values)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* im1 = (Image*)(*image1);
    Image* im2 = (Image*)(*image2);
    int bands = max(im1->bands, im2->bands);
    double* error = ::dice_coef(im1, im2);
    if (error == NULL)
        return 0;

    // Create the safe-array...
    COleSafeArray saRet;
    DWORD numElements = bands;
    saRet.Create(VT_R8, 1, &numElements);
    for (long idx = 0; idx < numElements; idx++)
        saRet.PutElement(&idx, error + idx);
    free(error);
    *error_values = saRet.Detach();
    return S_OK;
}
STDMETHODIMP CCVIPtools::Divide_Image(long* image1, long* image2, long zero2num, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* im1 = ::duplicate_Image((Image*)(*image1));
    Image* im2 = ::duplicate_Image((Image*)(*image2));
    Image* ret = ::divide_Image(im1, im2, (CVIP_BOOLEAN)zero2num);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Dpc_Compress(BSTR* filename, long* image, float ratio, int bit_length, int clipping, int direction, int origin, float deviation)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    char fname[_MAX_PATH];
    ::WideCharToMultiByte(CP_ACP, 0, *filename, -1, fname, _MAX_PATH, NULL, NULL);

    Image* im = NULL;
    if (getDataType_Image((Image*)(*image)) == CVIP_BYTE)
        im = ::duplicate_Image((Image*)(*image));
    else
        im = ::remap_Image((Image*)(*image), CVIP_BYTE, 0, 255);

    int result = ::dpc_compress(im, fname, ratio, bit_length, clipping, direction, origin, deviation);
    if (result != 0)
        return -1;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Dpc_Decompress(BSTR* filename, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    char fname[_MAX_PATH];
    ::WideCharToMultiByte(CP_ACP, 0, *filename, -1, fname, _MAX_PATH, NULL, NULL);
    Image* ret = ::dpc_decompress(fname);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Draw_mesh(long* image, long* mesh)
/*pmesh is free after this function*/
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* im = (Image*)(*image);
    struct mesh* pmesh= (struct mesh*)(*mesh);
    ::display_mesh(im, pmesh, NULL);
    for (int i = 0; i < pmesh->width; i++)
        free(pmesh->nodes[i]);
    free(pmesh->nodes);
    free(pmesh);
    return S_OK;
}
STDMETHODIMP CCVIPtools::Duplicate_Image(long* image, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* im = ::duplicate_Image((Image*)(*image));
    if (im == NULL)
        return 0;
    *result = (long)im;
    return S_OK;
}
STDMETHODIMP CCVIPtools::DynRLC_Compression(BSTR* filename, long* image, long window_size, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    char fname[_MAX_PATH];
    ::WideCharToMultiByte(CP_ACP, 0, *filename, -1, fname, _MAX_PATH, NULL, NULL);

    Image* im = NULL;
    if (getDataType_Image((Image*)(*image)) == CVIP_BYTE)
        im = ::duplicate_Image((Image*)(*image));
    else
        im = ::remap_Image((Image*)(*image), CVIP_BYTE, 0, 255);

    int ret = ::glr_compress(im, fname, window_size);
    if (ret != 0)
        return -1;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::DynRLC_deCompression(BSTR* filename, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    char fname[_MAX_PATH];
    ::WideCharToMultiByte(CP_ACP, 0, *filename, -1, fname, _MAX_PATH, NULL, NULL);
    Image* ret = ::glr_decompress(fname);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Edge_Detect_Filter(long* image, long edge_detector, long mask_type, long masksize, long keepdc, long threshold, long frei_projection, long frei_threshold, long frei_angle, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* im = ::duplicate_Image((Image*)(*image));
    Image* ret = ::edge_detect_filter(im, edge_detector, mask_type, masksize, keepdc, threshold, frei_projection, frei_threshold, frei_angle);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Edge_Link_Filter(long* binary_image, long connection_distance, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* im = ::duplicate_Image((Image*)(*binary_image));
    Image* ret = ::edge_link_filter(im, connection_distance);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Enlarge(long* image, int rows, int cols, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* im = ::duplicate_Image((Image*)(*image));
    Image* ret = ::enlarge(im, rows, cols);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Epstocvip(BSTR* filename, long verbose)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    char fname[_MAX_PATH];
    ::WideCharToMultiByte(CP_ACP, 0, *filename, -1, fname, _MAX_PATH, NULL, NULL);
    FILE* inputfile = fopen(fname, "rwb");
    ::epstocvip(fname, inputfile, (CVIP_BOOLEAN)verbose);
    fclose(inputfile);
    return S_OK;
}
STDMETHODIMP CCVIPtools::Euler(long* labeled_image, long row, long col, long* euler)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    *euler = ::euler((Image*)(*labeled_image), row, col);
    return S_OK;
}
STDMETHODIMP CCVIPtools::Exp_Ace_Filter(long* image, long masksize, double local_mean, double local_gain, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* im = ::duplicate_Image((Image*)(*image));
    Image* ret = ::exp_ace_filter(im, masksize, local_mean, local_gain);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Extract_Band(long* image, int band, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* im = ::duplicate_Image((Image*)(*image));
    Image* ret = ::extract_band(im, band);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Fft_Mag(long* image, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* im = ::duplicate_Image((Image*)(*image));
    Image* ret = ::fft_mag(im);
    ::delete_Image(im);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Fft_Phase(long* image, long remap_norm, double k, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* im = ::duplicate_Image((Image*)(*image));
    Image* ret = ::fft_phase(im, (int)remap_norm, (float)k);
    ::delete_Image(im);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Fft_Transform(long* image, long blocksize, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* im = ::duplicate_Image((Image*)(*image));
    int rows, cols;
    if (get_zpad_dims(im, &rows, &cols, blocksize) == CVIP_YES)
        zero_pad(im, rows, cols);
    Image* ret = ::fft_transform(im, (int)blocksize);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::File_To_Mesh(BSTR* filename, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    char fname[_MAX_PATH];
    ::WideCharToMultiByte(CP_ACP, 0, *filename, -1, fname, _MAX_PATH, NULL, NULL);
    struct mesh* pmesh = ::file_to_mesh(fname);
    if (pmesh == NULL)
        return 0;
    *result = (long)pmesh;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Fractal_Compression(long* image, BSTR* filename, double tolerance, long min_part, long max_part, long dom_type, long dom_step, long c1, long c2, long scalebits, long offsetbits, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    char fname[_MAX_PATH];
    ::WideCharToMultiByte(CP_ACP, 0, *filename, -1, fname, _MAX_PATH, NULL, NULL);

    Image* im = NULL;
    if (getDataType_Image((Image*)(*image)) == CVIP_BYTE)
        im = ::duplicate_Image((Image*)(*image));
    else
        im = ::remap_Image((Image*)(*image), CVIP_BYTE, 0, 255);

    int ret = ::frac_compress(im, fname, tolerance, min_part, max_part, dom_type, dom_step, (char)c1, (char)c2, scalebits, offsetbits);
    if (ret != 0)
        return -1;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Fractal_deCompression(BSTR* filename, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    char fname[_MAX_PATH];
    ::WideCharToMultiByte(CP_ACP, 0, *filename, -1, fname, _MAX_PATH, NULL, NULL);
    Image* ret = ::frac_decompress(fname);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Fuzzyc_Segment(long* image, double variance, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* im = NULL;
    if (getDataType_Image((Image*)(*image)) == CVIP_BYTE)
        im = ::duplicate_Image((Image*)(*image));
    else
        im = ::remap_Image((Image*)(*image), CVIP_BYTE, 0, 255);

    Image* ret = ::fuzzyc_segment(im, (float)variance);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Gamma_Noise(long* image, double variance, int alpha, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    float var = (float)variance;
    Image* im = ::duplicate_Image((Image*)(*image));
    Image* ret = ::gamma_noise(im, &var, &alpha);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Gaussian_Blur_Filter(long* image, long kernel_size, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Matrix* mask = (Matrix*)get_default_filter(BLUR_SPATIAL, (int)kernel_size, 0);
    if (mask == NULL)
        return 0;

    Image* im = NULL;
    if (getDataType_Image((Image*)(*image)) == CVIP_BYTE)
        im = ::duplicate_Image((Image*)(*image));
    else
        im = ::remap_Image((Image*)(*image), CVIP_BYTE, 0, 255);

    Image* ret = ::convolve_filter(im, mask);
    ::delete_Matrix(mask);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Gaussian_Noise(long* image, double variance, double mean, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    float var = (float)variance;
    float avg = (float)mean;
    Image* im = ::duplicate_Image((Image*)(*image));
    Image* ret = ::gaussian_noise(im, &var, &avg);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Geometric_Filter(long* image, long masksize, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* im = ::duplicate_Image((Image*)(*image));
    Image* ret = ::geometric_filter(im, (int)masksize);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Geometric_Mean(long* degr_image, long* degr_fn, long* psd_noise, long* psd_orig, double gamma, double alpha, long max_gain, long cutoff, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* im = ::duplicate_Image((Image*)(*degr_image));
    Image* fn = ::duplicate_Image((Image*)(*degr_fn));
    Image* noise = ::duplicate_Image((Image*)(*psd_noise));
    Image* orig = ::duplicate_Image((Image*)(*psd_orig));
    Image* ret = ::geometric_mean(im, fn, noise, orig, (float)gamma, (float)alpha, (int)max_gain, (int)cutoff);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::get_hist_real(long* image, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* im = NULL;
    if (getDataType_Image((Image*)(*image)) == CVIP_BYTE)
        im = ::duplicate_Image((Image*)(*image));
    else
        im = ::remap_Image_C((Image*)(*image), CVIP_BYTE, 0, 255);

    int bands = getNoOfBands_Image(im);
    int rows = getNoOfRows_Image(im);
    int cols = getNoOfCols_Image(im);
    float **map = (float**)malloc(bands * sizeof(float*));
    map[0] = (float*)calloc(bands * 256, sizeof(float));
    for (int band = 1; band < bands; band++)
        map[band] = map[band - 1] + 256;
    for (int band = 0; band < bands; band++)
    {
        byte** data = (byte**)getData_Image(im, band);
        for (int col = 0; col < cols; col++)
        {
            for (int row = 0; row < rows; row++)
                map[band][data[row][col]] += 1;
        }
    }
    ::scale_to_max(map, NULL, bands, 256);
    Image *ret = draw_picture(map, 256, 128, bands);
    ::delete_Image(im);
    free(map[0]);
    free(map);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Get_Histogram_Image(long* image, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* im = ::duplicate_Image((Image*)(*image));
    Image* ret = ::get_histogram_Image(im);
    ::delete_Image(im);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Get_max_min_value(long* image, double* min_max)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* im = (Image*)(*image);
    CVIP_TYPE dt = getDataType_Image(im);
    FORMAT format = getDataFormat_Image(im);
    unsigned bands = getNoOfBands_Image(im);
    unsigned rows = getNoOfRows_Image(im);
    unsigned cols = getNoOfCols_Image(im);
    unsigned imgsize = rows * cols;
    void **imgvecPi = NULL, **imgvecPr = (void **)malloc(sizeof(void*) * bands);

    getBandVector_Image(im, imgvecPr);
    if (format == COMPLEX)
    {
        imgvecPi = (void **)malloc(sizeof(void*) * bands);
        for (int i = 0; i < bands; i++)
            imgvecPi[i] = getImagRow_Image(im, 0, i);
    }
    for (int i = 0; i < bands; i++)
    {
        min_max[(i * 4) + 0] = findMinVal_Vector(imgvecPr[i], imgsize, dt);
        min_max[(i * 4) + 1] = findMaxVal_Vector(imgvecPr[i], imgsize, dt);
        if (format == COMPLEX)
        {
            min_max[(i * 4) + 2] = findMinVal_Vector(imgvecPi[i], imgsize, dt);
            min_max[(i * 4) + 3] = findMaxVal_Vector(imgvecPi[i], imgsize, dt);
        }
    }
    free(imgvecPr);
    if (format == COMPLEX)
        free(imgvecPi);
    return S_OK;
}
STDMETHODIMP CCVIPtools::Get_Mesh_Points(long* mesh, VARIANT* points)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    struct mesh* pmesh = (struct mesh*)(*mesh);

    // Create the safe-array...
    COleSafeArray saRet;
    DWORD numElements = (pmesh->width * pmesh->height * 2) + 2;
    saRet.Create(VT_I4, 1, &numElements);

    long idx = 0;
    long val = pmesh->width;
    saRet.PutElement(&idx, &val);

    idx++;
    val = pmesh->height;
    saRet.PutElement(&idx, &val);

    for (int row = 0; row < pmesh->height; row++)
    {
        for (int col = 0; col < pmesh->width; col++)
        {
            idx++;
            val = pmesh->nodes[col][row].x;
            saRet.PutElement(&idx, &val);

            idx++;
            val = pmesh->nodes[col][row].y;
            saRet.PutElement(&idx, &val);
        }
    }
    *points = saRet.Detach();
    return S_OK;
}
STDMETHODIMP CCVIPtools::GetDataFormat_Image(long* image, long* format)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    *format = getDataFormat_Image((Image*)(*image));
    return S_OK;
}
STDMETHODIMP CCVIPtools::GetDataType_Image(long* image, long* datatype)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    *datatype = getDataType_Image((Image*)(*image));
    return S_OK;
}
STDMETHODIMP CCVIPtools::GetImageInfo(long* image, VARIANT* info)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* im = (Image*)(*image);

    // Create the safe-array...
    COleSafeArray saRet;
    DWORD numElements = 9;
    saRet.Create(VT_R8, 1, &numElements);

    long idx = 0;
    double tmp = im->color_space;
    saRet.PutElement(&idx, &tmp);

    idx++;
    tmp = im->image_format;
    saRet.PutElement(&idx, &tmp);

    idx++;
    tmp = getDataFormat_Image(im);
    saRet.PutElement(&idx, &tmp);

    idx++;
    tmp = getDataType_Image(im);
    saRet.PutElement(&idx, &tmp);

    idx++;
    tmp = getNoOfBands_Image(im);
    saRet.PutElement(&idx, &tmp);

    idx++;
    tmp = getNoOfRows_Image(im);
    saRet.PutElement(&idx, &tmp);

    idx++;
    tmp = getNoOfCols_Image(im);
    saRet.PutElement(&idx, &tmp);

    *info = saRet.Detach();
    return S_OK;
}
STDMETHODIMP CCVIPtools::Getlast_Hist(long* image, long* programs, int num_programs, long* hist)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* im = (Image*)(*image);
    PROGRAMS* progs = (PROGRAMS*)malloc(sizeof(PROGRAMS) * num_programs);
    for (int i = 0; i < num_programs; i++)
        progs[i] = ((PROGRAMS*)programs)[i];
    PROGRAMS ret = ::getlast_Hist(im, progs, num_programs);
    free(progs);
    if (ret == (PROGRAMS)0)
        return 0;
    *hist = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::GetNoOfBands_Image(long* image, long* bands)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    *bands = getNoOfBands_Image((Image*)(*image));
    return S_OK;
}
STDMETHODIMP CCVIPtools::GetNoOfCols_Image(long* image, long* cols)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    *cols = getNoOfCols_Image((Image*)(*image));
    return S_OK;
}
STDMETHODIMP CCVIPtools::GetNoOfRows_Image(long* image, long* rows)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    *rows = getNoOfRows_Image((Image*)(*image));
    return S_OK;
}
STDMETHODIMP CCVIPtools::GetPixel_Image(long* image, long row, long col, VARIANT* pixel)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* im = (Image*)(*image);
    DWORD bands = getNoOfBands_Image(im);
    unsigned rows = getNoOfRows_Image(im);
    unsigned cols = getNoOfCols_Image(im);
    double val = -1.0;

    // Create a 1 dimension safe-array ...
    COleSafeArray saRet;
    saRet.Create(VT_R8, 1, &bands);

    if((row < 0) || (row >= rows) || (col < 0) || (col >= cols))
    {
        for (long band = 0; band < bands; band++)
            saRet.PutElement(&band, &val);
    }
    else
    {
        CVIP_TYPE dt = getDataType_Image(im);
        for (long band = 0; band < bands; band++)
        {
            switch (dt)
            {
            case CVIP_BYTE:
                val = (double)getPixel_Image(im, byte, col, row, band);
                break;
            case CVIP_SHORT:
                val = (double)getPixel_Image(im, short, col, row, band);
                break;
            case CVIP_INTEGER:
                val = (double)getPixel_Image(im, int, col, row, band);
                break;
            case CVIP_FLOAT:
                val = (double)getPixel_Image(im, float, col, row, band);
                break;
            case CVIP_DOUBLE:
                val = (double)getPixel_Image(im, double, col, row, band);
                break;
            default:
                val = -1.0;
                break;
            }
            saRet.PutElement(&band, &val);
        }
    }
    *pixel = saRet.Detach();
    return S_OK;
}
STDMETHODIMP CCVIPtools::giftocvip(BSTR* filename, long* unused, long image_number, long verbose)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    char fname[_MAX_PATH];
    ::WideCharToMultiByte(CP_ACP, 0, *filename, -1, fname, _MAX_PATH, NULL, NULL);
    FILE* inputfile = fopen(fname, "rwb");
    ::giftocvip(fname, inputfile, image_number, verbose);
    fclose(inputfile);
    return S_OK;
}
STDMETHODIMP CCVIPtools::Glr_Compress(BSTR* filename, long* image, long window_size)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    char fname[_MAX_PATH];
    ::WideCharToMultiByte(CP_ACP, 0, *filename, -1, fname, _MAX_PATH, NULL, NULL);
    Image* im = ::duplicate_Image((Image*)(*image));
    int result = ::glr_compress(im, fname, window_size);
    if (result != 0)
        return -1;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Glr_Decompress(BSTR* filename, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    char fname[_MAX_PATH];
    ::WideCharToMultiByte(CP_ACP, 0, *filename, -1, fname, _MAX_PATH, NULL, NULL);
    Image* ret = ::glr_decompress(fname);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Gray_Binary(long* image, int direction, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* im = ::duplicate_Image((Image*)(*image));
    Image* ret = ::gray_binary(im, direction);
    ::delete_Image(im);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Gray_Linear(long* image, double start, double end, double new_start, double slope, int oor_handling, int band, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* im = ::duplicate_Image((Image*)(*image));
    Image* ret = ::gray_linear(im, start, end, new_start, slope, oor_handling, band);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Gray_Multiplication(long* image, float ratio, long byte_clipping, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    if (byte_clipping != 0)
        return Gray_Multiply(image, ratio, result);
    else
        return Gray_Multiply2(image, ratio, result);
}
STDMETHODIMP CCVIPtools::Gray_Multiply(long* image, float ratio, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* im = NULL;
    if (getDataType_Image((Image*)(*image)) == CVIP_BYTE)
        im = ::duplicate_Image((Image*)(*image));
    else
        im = ::remap_Image((Image*)(*image), CVIP_BYTE, 0, 255);

    Image* ret = ::gray_multiply(im, ratio);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Gray_Multiply2(long* image, float ratio, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* im = ::duplicate_Image((Image*)(*image));
    Image* ret = ::gray_multiply2(im, ratio);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Gray_Quant_Segment(long* image, long gray_levels, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* im = ::duplicate_Image((Image*)(*image));
    Image* ret = ::gray_quant_segment(im, (int)gray_levels);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Graylevel_Quant(long* image, long gray_levels, long choice, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    if (choice == 1)
        return Igs_Segment(image, gray_levels, result);
    else
        return Gray_Quant_Segment(image, gray_levels, result);
    return S_OK;
}
STDMETHODIMP CCVIPtools::Graylevel_Remap(long* image, long r_selection, long g_selection, long b_selection, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* im = (Image*)(*image);
    if (getNoOfBands_Image(im) != 1)
        return 0;

    CVIP_TYPE dt = getDataType_Image(im);
    int selections[3] = {r_selection, g_selection, b_selection};
    Image* bands[3] = {NULL, NULL, NULL};
    for (int band = 0; band < 3; band++)
    {
        Image *a = NULL, *b = NULL, *c = NULL;
        switch (selections[band])
        {
        case 0:    /* "_/-\_" */
            a = gray_linear(::duplicate_Image(im), 0, 63, 0, 4, 0, -1);
            b = gray_linear(::duplicate_Image(im), 64, 191, 255, 0, 0, -1);
            c = gray_linear(::duplicate_Image(im), 192, 254, 255, -4, 0, -1);
            a = add_Image(a, b);
            bands[band] = add_Image(a, c);
            break;
        case 1:    /* "_/-" */
            a = gray_linear(::duplicate_Image(im), 0, 63, 0, 0, 0, -1);
            b = gray_linear(::duplicate_Image(im), 64, 127, 0, 0, 0, -1);
            c = gray_linear(::duplicate_Image(im), 127, 254, 255, 0, 0, -1);
            a = add_Image(a, b);
            bands[band] = add_Image(a, c);
            break;
        case 2:    /* "-\_" */
            a = gray_linear(::duplicate_Image(im), 0, 127, 255, 0, 0, -1);
            b = gray_linear(::duplicate_Image(im), 128, 191, 255, -4, 0, -1);
            c = gray_linear(::duplicate_Image(im), 192, 255, 0, 0, 0, -1);
            a = add_Image(a, b);
            bands[band] = add_Image(a, c);
            break;
        case 3:    /* slash "/" */
            bands[band] = gray_linear(::duplicate_Image(im), 0, 255, 0, 1, 0, -1);
            break;
        case 4: /* backslash "\" */
            bands[band] = gray_linear(::duplicate_Image(im), 0, 255, 255, -1, 0, -1);
            break;
        default:
            bands[band] = gray_linear(::duplicate_Image(im), 0, 255, 0, 1, 0, -1);
            break;
        }
        if (getDataType_Image(bands[band]) > dt)
        {
            Image* tmp = bands[band];
            switch (dt)
            {
            case CVIP_BYTE:
                bands[band] = ::remap_Image(tmp, CVIP_BYTE, 0, 255);
                break;
            case CVIP_SHORT:
                bands[band] = ::remap_Image(tmp, CVIP_SHORT, SHRT_MIN, SHRT_MAX);
                break;
            case CVIP_INTEGER:
                bands[band] = ::remap_Image(tmp, CVIP_INTEGER, LONG_MIN, LONG_MAX);
                break;
            }
            ::delete_Image(tmp);
        }
    }
    Image* ret = assemble_bands(bands, 3);
    ::delete_Image(bands[0]);
    ::delete_Image(bands[1]);
    ::delete_Image(bands[2]);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::GVFSnake_Segment(long* image, long* coordinates, long iterations, double alpha, double beta, double kappa, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    int* pts = (int*)malloc(sizeof(int) * coordinates[0]);
    for (int i = 0; i < coordinates[0]; i++)
        pts[i] = coordinates[i + 1];
    Image* im = ::duplicate_Image((Image*)(*image));
    Image* ret = ::snakeSetup(im, coordinates[0], pts, (int)iterations, alpha, beta, kappa);
    ::delete_Image(im);
    free(pts);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::H_image(long mask_type, long height, long width, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* ret = ::h_image((int)mask_type, (unsigned int)height, (unsigned int)width);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Haar_Transform(long* image, long direction, long blocksize, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    int rows, cols;
    Image* im = ::duplicate_Image((Image*)(*image));
    if (get_zpad_dims(im, &rows, &cols, blocksize) == CVIP_YES)
        zero_pad(im, rows, cols);
    Image* ret = ::haar_transform(im, (int)direction, (int)blocksize);
    if(ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Harmonic_Filter(long* image, long masksize, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* im = ::duplicate_Image((Image*)(*image));
    Image* ret = ::harmonic_filter(im, (int)masksize);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Harris_Corner_Filter(long* image, float alpha, long threshold, long border, float dmin, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* im = ::duplicate_Image((Image*)(*image));
    Image* ret = ::harris_corner_filter(im, alpha, threshold, border, dmin);
    ::delete_Image(im);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::High_Freq_Emphasis(long* image, long blocksize, long keepdc, long cutoff, double alpha, long filter_order, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* im = ::duplicate_Image((Image*)(*image));
    Image* ret = ::High_Freq_Emphasis(im, (int)blocksize, (int)keepdc, (int)cutoff, (float)alpha, (int)filter_order);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Highboost(long* image, long masksize, long center_value, long add2original, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    float** mask_values = (float**)calloc((int)masksize, sizeof(float*));
    mask_values[0] = (float*)calloc(masksize * masksize, sizeof(float));
    for (int i = 1; i < masksize; i++)
        mask_values[i] = mask_values[i - 1] + masksize;
    for (int row = 0; row < masksize; row++)
    {
        for (int col = 0; col < masksize; col++)
            mask_values[row][col] = -1;
    }
    mask_values[masksize / 2][masksize / 2] = center_value;
    Matrix* mask = specify_filter(masksize, masksize, mask_values);
    free(mask_values[0]);
    free(mask_values);
    if (mask == NULL)
        return 0;

    Image* im = NULL;
    if ((getDataType_Image((Image*)(*image)) == CVIP_BYTE) ||
        (getDataType_Image((Image*)(*image)) == CVIP_SHORT))
    {
        im = ::duplicate_Image((Image*)(*image));
    }
    else
    {
        im = ::remap_Image((Image*)(*image), CVIP_BYTE, 0, 255);
    }
    Image* ret = ::convolve_filter(im, mask);
    if (add2original != 0)
        ret = ::add_Image(ret, ::duplicate_Image((Image*)(*image)));
    ::delete_Matrix(mask);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::HighFreq_Emphasis(long* image, long xform, long cutoff, long filter_order, double offset, long keepdc, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image *im = ::duplicate_Image((Image*)(*image)), *fwd_xform = NULL;
    int dc_position = -1;
    int rows = getNoOfRows_Image(im);
    int cols = getNoOfCols_Image(im);
    int blocksize = (int)pow(2.0, ceil(log((double)max(rows, cols)) / log(2.0)));

    if (get_zpad_dims(im, &rows, &cols, blocksize) == CVIP_YES)
        zero_pad(im, rows, cols);

    switch (xform)
    {
    // perform fast Fourier xform
    case 0:
        fwd_xform = ::fft_transform(im, blocksize);
        dc_position = 1;
        break;
    // performs Discrete Cosine Transform
    case 1:
        fwd_xform = ::dct_transform(im, blocksize);
        dc_position = 2;
        break;
    // performs a fast Haar xform
    case 2:
        fwd_xform = ::haar_transform(im, 1, blocksize);
        dc_position = 2;
        break;
    // performs Walsh or Hadamard xform 1 is Walsh forward
    case 3:
        fwd_xform = ::walhad_transform(im, 1, blocksize);
        dc_position = 2;
        break;
    // performs Walsh or Hadamard xform 3 is Hadamard forward
    case 4:
        fwd_xform = ::walhad_transform(im, 3, blocksize);
        dc_position = 2;
        break;
    default:
        fwd_xform = ::fft_transform(im, blocksize);
        dc_position = 1;
        break;
    }
    Image *emphasis = NULL, *inv_xform = NULL;
    if (dc_position == 1)
        emphasis = ::High_Freq_Emphasis(fwd_xform, blocksize, keepdc, cutoff, offset, filter_order);
    else
        emphasis = ::nonfft_xformfilter(fwd_xform, blocksize, keepdc, HIGH_FREQ_EMPHASIS, cutoff, offset, filter_order);
    switch (xform)
    {
    // perform inverse fast Fourier xform
    case 0:
        inv_xform = ::ifft_transform(emphasis, blocksize);
        break;
    // performs inverse Discrete Cosine Transform
    case 1:
        inv_xform = ::idct_transform(emphasis, blocksize);
        break;
    // performs a inverse fast Haar xform
    case 2:
        inv_xform = ::haar_transform(emphasis, 0, blocksize);
        break;
    // performs inverse  Walsh or Hadamard xform 1 is Walsh forward
    case 3:
        inv_xform = ::walhad_transform(emphasis, 0, blocksize);
        break;
    // performs inverse Walsh or Hadamard xform 3 is Hadamard forward
    case 4:
        inv_xform = ::walhad_transform(emphasis, 2, blocksize);
        break;
    default:
        inv_xform = ::ifft_transform(emphasis, blocksize);
        break;
    }
    inv_xform = ::add_Image(inv_xform, ::duplicate_Image((Image*)(*image)));
    Image* ret = ::hist_stretch(inv_xform, 0, 255, 0.01, 0.01);
    ::delete_Image(inv_xform);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Highpass_Spatial(long* image, long add2original, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Matrix* mask = get_default_filter(HIGHPASS_SPATIAL, 3, 0);
    if (mask == NULL)
        return 0;

    Image* im = NULL;
    if ((getDataType_Image((Image*)(*image)) == CVIP_BYTE) ||
        (getDataType_Image((Image*)(*image)) == CVIP_SHORT))
    {
        im = ::duplicate_Image((Image*)(*image));
    }
    else
    {
        im = ::remap_Image((Image*)(*image), CVIP_BYTE, 0, 255);
    }
    Image* ret = ::convolve_filter(im, mask);
    if (add2original != 0)
        ret = ::add_Image(ret, ::duplicate_Image((Image*)(*image)));
    ::delete_Matrix(mask);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Hist_Feature(long* image, long* labeled_image, long row, long col, VARIANT* features)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* im = (Image*)(*image);
    Image* labeled = (Image*)(*labeled_image);
    double* hist = ::hist_feature(im, labeled, row, col);
    if (hist == NULL)
        return 0;

    // Create the safe-array...
    COleSafeArray saRet;
    DWORD numElements = getNoOfBands_Image(im) * 5;
    saRet.Create(VT_R8, 1, &numElements);
    for (long idx = 0; idx < numElements; idx++)
        saRet.PutElement(&idx, hist + idx);
    free(hist);
    *features = saRet.Detach();
    return S_OK;
}
STDMETHODIMP CCVIPtools::Hist_Slide(long* image, int slide, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* im = ::duplicate_Image((Image*)(*image));
    Image* ret = ::hist_slide(im, slide);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Hist_Spec(long* image, BSTR* r_histogram, BSTR* g_histogram, BSTR* b_histogram, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    char* fnames[3];
    BSTR* filenames[3] = {r_histogram, g_histogram, b_histogram};
    for (int i = 0; i < 3; i++)
    {
        fnames[i] = (char*)calloc(CVIP_MAX_PATH, sizeof(char));
        ::WideCharToMultiByte(CP_ACP, 0, *filenames[i], -1, fnames[i], _MAX_PATH, NULL, NULL);
    }
    Image* im = NULL;
    if (getDataType_Image((Image*)(*image)) == CVIP_BYTE)
        im = ::duplicate_Image((Image*)(*image));
    else
        im = ::remap_Image((Image*)(*image), CVIP_BYTE, 0, 255);

    Image* ret = ::hist_spec(im, 0, (char**)fnames);
    for (int i = 0; i < 3; i++)
        free(fnames[i]);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Hist_Stretch(long* image, int low_limit, int high_limit, float low_clip, float high_clip, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* im = ::duplicate_Image((Image*)(*image));
    Image* ret = ::hist_stretch(im, low_limit, high_limit, low_clip, high_clip);
    ::delete_Image(im);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Hist_Thresh_Gray(long* image, float tore, long* result)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	Image* im = NULL;
	if (getDataType_Image((Image*)(*image)) == CVIP_BYTE)
		im = ::duplicate_Image((Image*)(*image));
	else
		im = ::remap_Image((Image*)(*image), CVIP_BYTE, 0, 255);

	Image* ret = ::hist_thresh_gray(im, tore);
	if (ret == NULL)
		return 0;
	*result = (long)ret;
	return S_OK;
}
STDMETHODIMP CCVIPtools::Hist_Thresh_Segment(long* image, float tore, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* im = NULL;
    if (getDataType_Image((Image*)(*image)) == CVIP_BYTE)
        im = ::duplicate_Image((Image*)(*image));
    else
        im = ::remap_Image((Image*)(*image), CVIP_BYTE, 0, 255);

    Image* ret = ::hist_thresh_segment(im, tore);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}

//Hari Siva Kumar Reddy ( Fixed the bug in Histeq)
STDMETHODIMP CCVIPtools::Histeq(long* image, int band, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* im = NULL;
    if (getDataType_Image((Image*)(*image)) == CVIP_BYTE)
        im = ::duplicate_Image((Image*)(*image));
    else
        im = ::remap_Image((Image*)(*image), CVIP_BYTE, 0, 255);

    Image* ret = NULL;
    if (im->bands == 1)
        ret = ::histeq(im, 0);
    else
    {
        if (band != 0)
            ret = ::histeq(im, band - 1);
        else
        {
            float norm[3] = {255.0f, 255.0f, 255.0f};
            float ref[3] = {1.0f, 1.0f, 1.0f};
            Image *fwd_xform = NULL, *remap = NULL, *eq = NULL, *inv_xform = NULL,*eb1 = NULL,*eb2 = NULL,*eb3 = NULL,*ret1 = NULL;
			//eb1 = ::remap_Image((Image*)(*image), CVIP_BYTE, 0, 255);
			//eb2 =::remap_Image((Image*)(*image), CVIP_BYTE, 0, 255);
			//eb3 =::remap_Image((Image*)(*image), CVIP_BYTE, 0, 255);
			Image *temp,*temp2 = NULL;
            fwd_xform = ::colorxform(im, HSL, norm, ref, 1); //Do the HSL xform
            remap = ::remap_Image(fwd_xform, CVIP_BYTE, 0, 255);
			temp = ::duplicate_Image(remap);
			temp2 = ::duplicate_Image(remap);
			eb1 = ::extract_band(remap, 1);
			eb2 = ::extract_band(temp, 2);
			eb3 = ::extract_band(temp2, 3);
			eq = ::histeq(eb3, 0);
			Image* imm[3];
			imm[0] = eb1;
			imm[1] = eb2;
			imm[2] = eq;
			ret1 = ::assemble_bands(imm, 3);
			::delete_Image(imm[0]);
			::delete_Image(imm[1]);
			::delete_Image(imm[2]);
           // eq = ::histeq(remap, 2); //Do the histogram equalization over the "Lightness" band
            inv_xform = ::colorxform(ret1, HSL, norm, ref, -1); //Do the inverse HSL xform
            ret = ::remap_Image(inv_xform, CVIP_BYTE, 0, 255);
            ::delete_Image(fwd_xform);
            ::delete_Image(inv_xform);
        }
    }
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Histogram_Spec(long* image, double* histogram, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* im = ::duplicate_Image((Image*)(*image));
    float** hist_spec = new float*[im->bands];
    for (int i = 0; i < im->bands; i++)
    {
        hist_spec[i] = new float[256];
        for (int j = 0; j < 256; j++)
            hist_spec[i][j] = (float)histogram[(i * 256) + j];
    }
    Image* ret = ::histogram_spec(im, hist_spec);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::History_Add(long* image, long* history)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* im = (Image*)(*image);
    HISTORY hist= (HISTORY)(*history);
    ::history_add(im, hist);
    return S_OK;
}
STDMETHODIMP CCVIPtools::History_Check(long* image, int program, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    *result = ::history_check((PROGRAMS)program, (Image*)(*image));
    return S_OK;
}
STDMETHODIMP CCVIPtools::History_Copy(long* source, long* destination)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* src = (Image*)(*source);
    Image* dest = (Image*)(*destination);
    ::history_copy (src, dest);
    return S_OK;
}
STDMETHODIMP CCVIPtools::history_create(long prog, long type, float value, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    HISTORY hist = (HISTORY)malloc(sizeof(struct history));
    if (hist == NULL)
        return 0;

    int* hptr = (int*)malloc(sizeof(int));
    hptr[0] = (int)value;

    hist->packetP = (PACKET*)malloc(sizeof(PACKET));
    hist->packetP->dsize = 1;
    hist->packetP->dtype = (CVIP_TYPE*)malloc(sizeof(CVIP_TYPE));
    hist->packetP->dtype[0] = CVIP_INTEGER;
    hist->packetP->dptr = (void**)malloc(sizeof(void*));
    hist->packetP->dptr[0] = (int*)hptr;
    hist->packetP->dsize = 1;
    hist->next = NULL;
    hist->ftag = (PROGRAMS)prog;

    *result = (long)hist;
    return S_OK;
}
STDMETHODIMP CCVIPtools::history_create2(long prog, long type, int value1, int value2, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    HISTORY hist = (HISTORY)malloc(sizeof(struct history));
    if (hist == NULL)
        return 0;

    int** hptr = (int**)malloc(sizeof(int*) * 2);
    hptr[0] = (int*)malloc(sizeof(int));
    hptr[1] = (int*)malloc(sizeof(int));
    hptr[0][0] = (int)value1;
    hptr[1][0] = (int)value2;

    hist->packetP = (PACKET*)malloc(sizeof(PACKET));
    hist->packetP->dsize = 2;
    hist->packetP->dtype = (CVIP_TYPE*)malloc(sizeof(CVIP_TYPE) * 2);
    hist->packetP->dtype[0] = CVIP_INTEGER;
    hist->packetP->dtype[1] = CVIP_INTEGER;
    hist->packetP->dptr = (void**)hptr;
    hist->next = NULL;
    hist->ftag = (PROGRAMS)prog;

    *result = (long)hist;
    return S_OK;
}
STDMETHODIMP CCVIPtools::History_Delete_Program(long* image, int program, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    ::history_delete_program((Image*)(*image), (PROGRAMS)program);
    return S_OK;
}
STDMETHODIMP CCVIPtools::History_Get(long* image, int program, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* im = (Image*)(*image);
    HISTORY hist = ::history_get(im, (PROGRAMS)program);
    if(result == NULL)
        return 0;
    *result = (long)hist;
    return S_OK;
}
STDMETHODIMP CCVIPtools::History_get_data(long* history, int program, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    HISTORY hist = (HISTORY)(*history);
    *result = (long)*((int*)hist->packetP->dptr[0]);
    return S_OK;
}
STDMETHODIMP CCVIPtools::History_get_data2(long* history, int program, int index, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    HISTORY hist = (HISTORY)(*history);
    *result = (long)(((int**)hist->packetP->dptr)[index][0]);
    return S_OK;
}
STDMETHODIMP CCVIPtools::Homomorphic(long* image, double upper_limit, double lower_limit, long cutoff, long add2original, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* im = (Image*)(*image);
    Image* ret = ::homomorphic(::duplicate_Image(im), (float)upper_limit, (float)lower_limit, (int)cutoff);
    if (add2original != 0)
    {
        Image* tmp = ::add_Image(ret, ::duplicate_Image(im));
        ret = ::hist_stretch(tmp, 1, 254, 0.01, 0.01);
        ::delete_Image(tmp);
    }
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Horizontal_Flip(long* image, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* im = ::duplicate_Image((Image*)(*image));
    Image* ret = ::HorizontalFlip(im);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Hough_Filter(long* image, BSTR* image_name, BSTR* angles_of_interest, long threshold, long connection_distance, long interactive, long delta_length, long segment_length, long intermediate_result, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    char name[_MAX_PATH];
    char angles[_MAX_PATH];
    ::WideCharToMultiByte(CP_ACP, 0, *image_name, -1, name, _MAX_PATH, NULL, NULL);
    ::WideCharToMultiByte(CP_ACP, 0, *angles_of_interest, -1, angles, _MAX_PATH, NULL, NULL);

    Image* im = ::duplicate_Image((Image*)(*image));
    Image* ret = ::hough_filter(im, name, angles, (int)threshold, (int)connection_distance, (int)interactive, (int)delta_length, (int)segment_length, (int)intermediate_result);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Huf_Compress(BSTR* filename, long* image)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    char fname[_MAX_PATH];
    ::WideCharToMultiByte(CP_ACP, 0, *filename, -1, fname, _MAX_PATH, NULL, NULL);

    Image* im = NULL;
    if (getDataType_Image((Image*)(*image)) == CVIP_BYTE)
        im = ::duplicate_Image((Image*)(*image));
    else
        im = ::remap_Image((Image*)(*image), CVIP_BYTE, 0, 255);

    int result = ::huf_compress(im, fname);
    if (result != 0)
        return -1;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Huf_Decompress(BSTR* filename, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    char fname[_MAX_PATH];
    ::WideCharToMultiByte(CP_ACP, 0, *filename, -1, fname, _MAX_PATH, NULL, NULL);
    Image* ret = ::huf_decompress(fname);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Idct_Transform(long* image, long blocksize, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* im = ::duplicate_Image((Image*)(*image));
    Image* ret = ::idct_transform(im, (int)blocksize);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Ideal_Band_Pass(long* image, long blocksize, long keepdc, long inner_cutoff, long outer_cutoff, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* im = ::duplicate_Image((Image*)(*image));
    Image* ret = ::Ideal_Band_Pass(im, (int)blocksize, (int)keepdc, (int)inner_cutoff, (int)outer_cutoff);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Ideal_Band_Reject(long* image, long blocksize, long keepdc, long inner_cutoff, long outer_cutoff, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* im = ::duplicate_Image((Image*)(*image));
    Image* ret = ::Ideal_Band_Reject(im, (int)blocksize, (int)keepdc, (int)inner_cutoff, (int)outer_cutoff);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Ideal_High(long* image, long blocksize, long keepdc, long cutoff, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* im = ::duplicate_Image((Image*)(*image));
    Image* ret = ::Ideal_High(im, (int)blocksize, (int)keepdc, (int)cutoff);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Ideal_Low(long* image, long blocksize, long keepdc, long cutoff, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* im = ::duplicate_Image((Image*)(*image));
    Image* ret = ::Ideal_Low(im, (int)blocksize, (int)keepdc, (int)cutoff);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Ifft_Transform(long* image, long blocksize, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* im = ::duplicate_Image((Image*)(*image));
    Image* ret = ::ifft_transform(im, (int)blocksize);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Igs_Segment(long* image, long gray_levels, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* im = ::duplicate_Image((Image*)(*image));
    Image* ret = ::igs_segment(im, (int)gray_levels);
    ::delete_Image(im);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Improved_Mmse_Filter(long* image, float threshold, long kernel_size, float noise_variance, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* im = ::duplicate_Image((Image*)(*image));
    Image* ret = ::improved_mmse_filter(im, threshold, (int)kernel_size, noise_variance);
    ::delete_Image(im);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Input_Mesh(long* points, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    /*
        0:cols
        1:rows
        2:nodes[0][0].x
        3:nodes[0][0].y
        4:nodes[0][1].x
        5:nodes[0][1].y
    */
    struct mesh* mesh = (struct mesh*)malloc(sizeof(struct mesh));
    if (mesh == NULL)
        return 0;

    mesh->width = points[0];  /* number of cols */
    mesh->height = points[1]; /* number of rows */
    mesh->nodes = (struct mesh_node**)malloc(sizeof(struct mesh_node*) * mesh->width);
    for (int col = 0; col < mesh->width; col++)
        mesh->nodes[col] = (struct mesh_node*)calloc(mesh->height, sizeof(struct mesh_node));
    for (int row = 0; row < mesh->height; row++)
    {
        for (int col = 0; col < mesh->width; col++)
        {
            mesh->nodes[col][row].x = points[(2 * ((mesh->width * row) + col)) + 2];
            mesh->nodes[col][row].y = points[(2 * ((mesh->width * row) + col)) + 3];
        }
    }
    *result =(long)mesh;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Intensity_Slicing(long* image, long* lookup_table, long options, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* im = (Image*)(*image);
    if (getNoOfBands_Image(im) != 1)
        return 0;

    if ((lookup_table[0] < 0) || (lookup_table[7] > 255))
        return 0;

    for (int i = 0; i < 6; i++)
    {
        if (lookup_table[i] >= lookup_table[i + 1])
            return 0;
    }

    long* lut = lookup_table;
    Image* bands[3] = {NULL, NULL, NULL};
    Image *a, *b, *c, *d;
    for (int i = 0; i < 3; i++)
    {
        a = gray_linear(::duplicate_Image(im), lut[0], lut[1], lut[8 + i], 0, 0, -1);
        b = gray_linear(::duplicate_Image(im), lut[2], lut[3], lut[11 + i], 0, 0, -1);
        c = gray_linear(::duplicate_Image(im), lut[4], lut[5], lut[14 + i], 0, 0, -1);
        d = gray_linear(::duplicate_Image(im), lut[6], lut[7], lut[17 + i], 0, 0, -1);
        a = add_Image(a, b);
        a = add_Image(a, c);
        bands[i] = add_Image(a, d);
    }
    Image* ret = ::assemble_bands(bands, 3);
    ::delete_Image(bands[0]);
    ::delete_Image(bands[1]);
    ::delete_Image(bands[2]);
    if (options == 0)
    {
        im = ::duplicate_Image(im);
        cast_Image(im, CVIP_FLOAT);
        int cols = getNoOfCols_Image(ret);
        int rows = getNoOfRows_Image(ret);
        float** rr = (float**)getData_Image(ret, 0);
        float** gg = (float**)getData_Image(ret, 1);
        float** bb = (float**)getData_Image(ret, 2);
        float** mm = (float**)getData_Image(im, 0);
        for (int row = 0; row < rows; row++)
        {
            for (int col = 0; col < cols; col++)
            {
                if ((mm[row][col] < lut[0]) ||
                    ((mm[row][col] > lut[1]) && (mm[row][col] < lut[2])) ||
                    ((mm[row][col] > lut[3]) && (mm[row][col] < lut[4])) ||
                    ((mm[row][col] > lut[5]) && (mm[row][col] < lut[6])) ||
                    (mm[row][col] > lut[7]))
                {
                    rr[row][col] = mm[row][col];
                    gg[row][col] = mm[row][col];
                    bb[row][col] = mm[row][col];
                }
            }
        }
        ::delete_Image(im);
    }
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Inverse_Xformfilter(long* degr_image, long* degr_fn, long max_gain, double cutoff, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* im = ::duplicate_Image((Image*)(*degr_image));
    Image* fn = ::duplicate_Image((Image*)(*degr_fn));
    Image* ret = ::inverse_xformfilter(im, fn, (int)max_gain, (float)cutoff);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Ipct(long* image, long ignore_background, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* im = ::duplicate_Image((Image*)(*image));
    Image* ret = ::ipct(im, (CVIP_BOOLEAN)ignore_background, NULL);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Irregular(long* labeled_image, int row, int col, double* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    *result = ::irregular((Image*)(*labeled_image), row, col);
    return S_OK;
}
STDMETHODIMP CCVIPtools::Jp2_Decoder(BSTR* filename, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    char fname[_MAX_PATH];
    ::WideCharToMultiByte(CP_ACP, 0, *filename, -1, fname, _MAX_PATH, NULL, NULL);
    Image* ret = ::jp2_decoder(fname);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Jaccard_Index(long* image1, long* image2, VARIANT* error_values)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* im1 = (Image*)(*image1);
    Image* im2 = (Image*)(*image2);
    int bands = max(im1->bands, im2->bands);
    double* error = ::jaccard_index(im1, im2);
    if (error == NULL)
        return 0;

    // Create the safe-array...
    COleSafeArray saRet;
    DWORD numElements = bands;
    saRet.Create(VT_R8, 1, &numElements);
    for (long idx = 0; idx < numElements; idx++)
        saRet.PutElement(&idx, error + idx);
    free(error);
    *error_values = saRet.Detach();
    return S_OK;
}
STDMETHODIMP CCVIPtools::Jp2_Encoder(BSTR* filename, long* image, int rate, int quality, int layers, int blocksize)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    char fname[_MAX_PATH];
    ::WideCharToMultiByte(CP_ACP, 0, *filename, -1, fname, _MAX_PATH, NULL, NULL);

    Image* im = NULL;
    if (getDataType_Image((Image*)(*image)) == CVIP_BYTE)
        im = ::duplicate_Image((Image*)(*image));
    else
        im = ::remap_Image((Image*)(*image), CVIP_BYTE, 0, 255);

    int result = ::jp2_encoder(im, fname, rate, quality, layers, blocksize);
    ::delete_Image(im);
    if (result != 0)
        return -1;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Jpg_Compress(BSTR* filename, long* image, int quality, long grayscale, long optimize, int smooth, long verbose, BSTR* qtablesFile)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    char fname[_MAX_PATH];
    char qtablesfname[_MAX_PATH];
    ::WideCharToMultiByte(CP_ACP, 0, *filename, -1, fname, _MAX_PATH, NULL, NULL);
    ::WideCharToMultiByte(CP_ACP, 0, *qtablesFile, -1, qtablesfname, _MAX_PATH, NULL, NULL);

    Image* im = NULL;
    if (getDataType_Image((Image*)(*image)) == CVIP_BYTE)
        im = ::duplicate_Image((Image*)(*image));
    else
        im = ::remap_Image((Image*)(*image), CVIP_BYTE, 0, 255);

    int result = ::jpg_compress(im, fname, quality, (CVIP_BOOLEAN)grayscale, (CVIP_BOOLEAN)optimize, smooth, (CVIP_BOOLEAN)verbose, qtablesfname);
    if (result != 0)
        return -1;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Jpg_Decompress(BSTR* filename, int num_colors, long blocksmooth, long grayscale, long nodither, long verbose, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    char fname[_MAX_PATH];
    ::WideCharToMultiByte(CP_ACP, 0, *filename, -1, fname, _MAX_PATH, NULL, NULL);
    Image* ret = ::jpg_decompress(fname, num_colors, (CVIP_BOOLEAN)blocksmooth, (CVIP_BOOLEAN)grayscale, (CVIP_BOOLEAN)nodither, (CVIP_BOOLEAN)verbose);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Jpgtocvip(BSTR* filename, int num_colors, long blocksmooth, long grayscale, long nodither, long verbose, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    char fname[_MAX_PATH];
    ::WideCharToMultiByte(CP_ACP, 0, *filename, -1, fname, _MAX_PATH, NULL, NULL);
    Image* ret = ::jpgtocvip(fname, num_colors, (CVIP_BOOLEAN)blocksmooth, (CVIP_BOOLEAN)grayscale, (CVIP_BOOLEAN)nodither, (CVIP_BOOLEAN)verbose);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::K_Nearest_Neighbor(BSTR* test_set, BSTR* training_set, BSTR* outputfile, int normalization, int distance_measure, int k, float s_min, float s_max, float r_softmax, float r_minkowski, long* error)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    char testfile[_MAX_PATH];
    char trainingfile[_MAX_PATH];
    char outfile[_MAX_PATH];
    ::WideCharToMultiByte(CP_ACP, 0, *test_set, -1, testfile, _MAX_PATH, NULL, NULL);
    ::WideCharToMultiByte(CP_ACP, 0, *training_set, -1, trainingfile, _MAX_PATH, NULL, NULL);
    ::WideCharToMultiByte(CP_ACP, 0, *outputfile, -1, outfile, _MAX_PATH, NULL, NULL);
    *error = k_nearest_neighbor(testfile, trainingfile, outfile, normalization, distance_measure, k, s_min, s_max, r_softmax, r_minkowski);
    return S_OK;
}
STDMETHODIMP CCVIPtools::Krisch_Filter(long* image, long* dir_image, long filter_type, long kernel_size, long keepdc, long threshold, long* mag_image)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* im = ::duplicate_Image((Image*)(*image));
    Image* dir = (Image*)calloc(1, sizeof(Image));
    Image* ret = ::kirsch_filter(im, dir, (int)filter_type, (int)kernel_size, (int)keepdc, (int)threshold);
    ::delete_Image(im);
    if (ret == NULL)
        return 0;
    *mag_image = (long)ret;
    *dir_image = (long)dir;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Kuwahara_Filter(long* image, long masksize, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* im = ::duplicate_Image((Image*)(*image));
    Image* ret = ::kuwahara_filter(im, (int)masksize);
    ::delete_Image(im);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Label(long* image, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* im = NULL;
    if (getDataType_Image((Image*)(*image)) == CVIP_BYTE)
        im = ::duplicate_Image((Image*)(*image));
    else
        im = ::remap_Image((Image*)(*image), CVIP_BYTE, 0, 255);

    Image* ret = ::label(im);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Laws_Texture_Feature(long* image, long* labeled_image, int row, int col, int window_size, int vector1, int vector2, VARIANT* features)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    //Image* im = (Image*)(*image);
    //Image* labeled = (Image*)(*labeled_image);
    //double* laws = ::laws_texture(im, labeled, row, col,window_size, vector1, vector2);
	double* laws = ::laws_texture((Image*)(*image), (Image*)(*labeled_image), row, col, window_size, vector1, vector2);
    if (laws == NULL)
        return 0;

    // Create the safe-array...
    COleSafeArray saRet;
    //DWORD numElements = getNoOfBands_Image(im) * 5;
	DWORD numElements = getNoOfBands_Image((Image*)(*image)) * 5;
    saRet.Create(VT_R8, 1, &numElements);
    for (long idx = 0; idx < numElements; idx++)
        saRet.PutElement(&idx, laws + idx);
    free(laws);
    *features = saRet.Detach();
    return S_OK;
}
STDMETHODIMP CCVIPtools::Least_Squares(long* degr_image, long* degr_fn, long* smoothness_fn, double gamma, long max_gain, long cutoff, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* im = ::duplicate_Image((Image*)(*degr_image));
    Image* fn = ::duplicate_Image((Image*)(*degr_fn));
    Image* smoothness = ::duplicate_Image((Image*)(*smoothness_fn));
    Image* ret = ::least_squares(im, fn, smoothness, (float)gamma, (int)max_gain, (int)cutoff);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Local_Adaptive_Zoom(long* image, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* im = ::duplicate_Image((Image*)(*image));
    Image* ret = ::local_adaptive_zoom(im);
    ::delete_Image(im);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Local_Histeq(long* image, int blocksize, int band, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* im = NULL;
    if (getDataType_Image((Image*)(*image)) == CVIP_BYTE)
        im = ::duplicate_Image((Image*)(*image));
    else
        im = ::remap_Image((Image*)(*image), CVIP_BYTE, 0, 255);

    Image* ret = NULL;
    if (im->bands == 1)
        ret = ::local_histeq(im, blocksize, 0);
    else
    {
        if (band != 0)
            ret = ::local_histeq(im, blocksize, band - 1);
        else
        {
            float norm[3] = { 255.0f, 255.0f, 255.0f };
            float ref[3] = { 1.0f, 1.0f, 1.0f };
            Image* fwd_xform = NULL, * remap = NULL, * eq = NULL, * eb1 = NULL, * eb2 = NULL, * eb3 = NULL, * ret1 = NULL;
            Image* temp, * temp2 = NULL;
            fwd_xform = ::colorxform(im, HSL, norm, ref, 1); //Do the HSL xform
            remap = ::remap_Image(fwd_xform, CVIP_BYTE, 0, 255);
            temp = ::duplicate_Image(remap);
            temp2 = ::duplicate_Image(remap);
            eb1 = ::extract_band(remap, 1);
            eb2 = ::extract_band(temp, 2);
            eb3 = ::extract_band(temp2, 3);
            eq = ::local_histeq(eb3, blocksize, 0);
            Image* imm[3];
            imm[0] = eb1;
            imm[1] = eb2;
            imm[2] = eq;
            ret1 = ::assemble_bands(imm, 3);
            ::delete_Image(imm[0]);
            ::delete_Image(imm[1]);
            ::delete_Image(imm[2]);
            // eq = ::histeq(remap, 2); //Do the histogram equalization over the "Lightness" band
            ret = ::colorxform(ret1, HSL, norm, ref, -1); //Do the inverse HSL xform
            ::delete_Image(fwd_xform);
        }
    }
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Log_Ace_Filter(long* image, long masksize, double local_mean, double local_gain, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* im = ::duplicate_Image((Image*)(*image));
    Image* ret = ::log_ace_filter(im, masksize, local_mean, local_gain);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Log_Remap(long* image, long band, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    return LogMap_Image(image, band, result);
}
STDMETHODIMP CCVIPtools::LogMap_Image(long* image, int band, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* im = ::duplicate_Image((Image*)(*image));
    Image* ret = ::logMap_Image(im, band);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Lum_Average(long* image, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* im = ::duplicate_Image((Image*)(*image));
    Image* ret = ::lum_average(im);
    ::delete_Image(im);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Luminance_Image(long* image, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* im = ::duplicate_Image((Image*)(*image));
    Image* ret = ::luminance_Image(im);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Make_Histogram(double* histogram, long image_format, long color_format, long bands, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    float** hist = new float*[bands];
    hist[0] = new float[bands * 256];
    for (int band = 1; band < bands; band++)
        hist[band] = hist[band - 1] + 256;
    for (int band = 0; band < bands; band++)
    {
        for (int i = 0; i < 256; i++)
            hist[band][i] = (float)histogram[(band * 256) + i];
    }
    Image* ret = ::make_histogram(hist, (IMAGE_FORMAT)image_format, (COLOR_FORMAT)color_format);
    delete [] hist[0];
    delete [] hist;
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Marr_Hildreth_Filter(long* image, float sigma, int threshold, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* im = ::duplicate_Image((Image*)(*image));
    Image* ret = ::marr_hildreth_filter(im, sigma, threshold);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Maximum_Filter(long* image, long masksize, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* im = ::duplicate_Image((Image*)(*image));
    Image* ret = ::maximum_filter(im, (int)masksize);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Mean_Filter(long* image, long masksize, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* im = ::duplicate_Image((Image*)(*image));
    Image* ret = ::mean_filter(im, (int)masksize);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Median_Cut_Segment(long* image, long num_colors, long ignore_background, long r_background, long g_background, long b_background, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Color bg;
    bg.r = (unsigned char)r_background;
    bg.g = (unsigned char)g_background;
    bg.b = (unsigned char)b_background;

    Image* im = NULL;
    if (getDataType_Image((Image*)(*image)) == CVIP_BYTE)
        im = ::duplicate_Image((Image*)(*image));
    else
        im = ::remap_Image((Image*)(*image), CVIP_BYTE, 0, 255);

    Image* ret = ::median_cut_segment(im, num_colors, (CVIP_BOOLEAN)ignore_background, bg);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Median_Filter(long* image, long masksize, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* im = NULL;
    if (getDataType_Image((Image*)(*image)) == CVIP_BYTE)
        im = ::duplicate_Image((Image*)(*image));
    else
        im = ::remap_Image((Image*)(*image), CVIP_BYTE, 0, 255);

    Image* ret = ::median_filter(im, (int)masksize);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Mesh_To_File(BSTR* filename, long* mesh)
/*pmesh is free after this function*/
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    char fname[_MAX_PATH];
    ::WideCharToMultiByte(CP_ACP, 0, *filename, -1, fname, _MAX_PATH, NULL, NULL);
    struct mesh* pmesh= (struct mesh*)(*mesh);
    ::mesh_to_file(pmesh, fname);
    for (int i = 0; i < pmesh->width; i++)
        free(pmesh->nodes[i]);
    free(pmesh->nodes);
    free(pmesh);
    return S_OK;
}
STDMETHODIMP CCVIPtools::Mesh_Warping(long* image, long* mesh, long interpolation_method, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    int rows = getNoOfRows_Image((Image*)(*image));
    int cols = getNoOfCols_Image((Image*)(*image));
    struct mesh* pmesh= (struct mesh*)(*mesh);
    for (int row = 0; row < pmesh->height; row++)
    {
        for (int col = 0; col < pmesh->width; col++)
        {
            if ((pmesh->nodes[col][row].x >= cols) || (pmesh->nodes[col][row].y >= rows))
                return 0;
        }
    }
    Image* im = NULL;
    if (getDataType_Image((Image*)(*image)) == CVIP_BYTE)
        im = ::duplicate_Image((Image*)(*image));
    else
        im = ::remap_Image((Image*)(*image), CVIP_BYTE, 0, 255);

    Image* ret = ::mesh_warping(im, pmesh, (int)interpolation_method);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Mesh_WarpingRI(long* image, long* mesh, long interpolation_method, long zero_missing, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    int rows = getNoOfRows_Image((Image*)(*image));
    int cols = getNoOfCols_Image((Image*)(*image));
    struct mesh* pmesh= (struct mesh*)(*mesh);
    for (int row = 0; row < pmesh->height; row++)
    {
        for (int col = 0; col < pmesh->width; col++)
        {
            if ((pmesh->nodes[col][row].x >= cols) || (pmesh->nodes[col][row].y >= rows))
                return 0;
        }
    }
    Image* im = NULL;
    if (getDataType_Image((Image*)(*image)) == CVIP_BYTE)
        im = ::duplicate_Image((Image*)(*image));
    else
        im = ::remap_Image((Image*)(*image), CVIP_BYTE, 0, 255);

    Image* ret = ::mesh_warping_ri(im, pmesh, (int)interpolation_method, (CVIP_BOOLEAN)zero_missing);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Midpoint_Filter(long* image, long masksize, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* im = ::duplicate_Image((Image*)(*image));
    Image* ret = ::midpoint_filter(im, (int)masksize);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Minimum_Filter(long* image, long masksize, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* im = ::duplicate_Image((Image*)(*image));
    Image* ret = ::minimum_filter(im, (int)masksize);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Mmse_Filter(long* image, double noise_variance, long kernel_size, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* im = ::duplicate_Image((Image*)(*image));
    Image* ret = ::mmse_filter(im, (float)noise_variance, (unsigned int)kernel_size);
    ::delete_Image(im);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Moravec_Corner_Filter(long* image, float threshold, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* im = ::duplicate_Image((Image*)(*image));
    Image* ret = ::moravec_corner_filter(im, threshold);
    ::delete_Image(im);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Morph_Hitmiss(long* binary_image, long masksize, double* mask_values, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    char* mask = (char*)malloc(masksize * masksize * sizeof(char));
    for (int row = 0; row < masksize; row++)
    {
        for (int col = 0; col < masksize; col++)
        {
            if (mask_values[(row * masksize) + col] == 1.0)
                mask[(row * masksize) + col] = '1';
            else if (mask_values[(row * masksize) + col] == 0.0)
                mask[(row * masksize) + col] = '0';
            else
                mask[(row * masksize) + col] = 'x';
        }
    }
    Image* im = ::duplicate_Image((Image*)(*binary_image));
    Image* ret = ::morph_hitmiss(im, masksize, mask);
    free(mask);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Morph_Skeleton(long* binary_image, long masksize, double* mask_values, long iterations, long four_eight_mask, long method, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    char* mask = (char*)malloc(masksize * masksize * sizeof(char));
    for (int row = 0; row < masksize; row++)
    {
        for (int col = 0; col < masksize; col++)
        {
            if (mask_values[(row * masksize) + col] == 1.0)
                mask[(row * masksize) + col] = '1';
            else if (mask_values[(row * masksize) + col] == 0.0)
                mask[(row * masksize) + col] = '0';
            else
                mask[(row * masksize) + col] = 'x';
        }
    }
    Image* im = ::duplicate_Image((Image*)(*binary_image));
    Image* ret = ::morph_skeleton(im, masksize, mask, iterations, four_eight_mask, method);
    free(mask);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Morph_Thinning(long* binary_image, long masksize, double* mask_values, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    char* mask = (char*)malloc(masksize * masksize * sizeof(char));
    for (int row = 0; row < masksize; row++)
    {
        for (int col = 0; col < masksize; col++)
        {
            if (mask_values[(row * masksize) + col] == 1.0)
                mask[(row * masksize) + col] = '1';
            else if (mask_values[(row * masksize) + col] == 0.0)
                mask[(row * masksize) + col] = '0';
            else
                mask[(row * masksize) + col] = 'x';
        }
    }
    Image* im = ::duplicate_Image((Image*)(*binary_image));
    Image* ret = ::morph_thinning(im, masksize, mask);
    ::delete_Image(im);
    free(mask);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::MorphClose(long* image, int kernel_type, int kernel_size, int height, int width, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image *im = (Image*)(*image), *ret = NULL;
    if (getNoOfBands_Image(im) == 1)
    {
        im = ::duplicate_Image((Image*)(*image));
        ret = ::MorphClose(im, kernel_type, kernel_size, height, width);
    }
    else
    {
        Image* bands[3];
        for (int i = 0; i < 3; i++)
        {
            im = ::duplicate_Image((Image*)(*image));
            Image* band = ::extract_band(im, i + 1);
            bands[i] = ::MorphClose(band, kernel_type, kernel_size, height, width);
        }
        ret = ::assemble_bands(bands, 3);
        for (int i = 0; i < 3; i++)
            ::delete_Image(bands[i]);
    }
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::MorphClose_Image(long* image, long* matrix, int userOrg, int x, int y, int size, long* result)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	Image *im = (Image*)(*image), *ret = NULL;
	CVIP_BOOLEAN origin;
	Matrix* kernel = NULL;
	int** temp = new int*[size];
	for (int i = 0; i < size; ++i)
		temp[i] = new int[size];
	kernel = new_Matrix(size, size, CVIP_INTEGER, REAL);
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
		{
			temp[i][j] = *(matrix + ((i*size) + j));
		}
	kernel->rptr = (char**)temp;
	if (userOrg == 0)
		origin = CVIP_NO;
	else
		origin = CVIP_YES;
	if (getNoOfBands_Image(im) == 1)
	{
		im = ::duplicate_Image((Image*)(*image));
		ret = ::MorphClose_Image(im, kernel, origin, x, y);
	}
	else
	{
		Image* bands[3];
		for (int i = 0; i < 3; i++)
		{
			im = ::duplicate_Image((Image*)(*image));
			Image* band = ::extract_band(im, i + 1);
			bands[i] = ::MorphClose_Image(band, kernel, origin, x, y);
		}
		ret = ::assemble_bands(bands, 3);
		for (int i = 0; i < 3; i++)
			::delete_Image(bands[i]);
	}
	if (ret == NULL)
		return 0;
	*result = (long)ret;
	return S_OK;
}
STDMETHODIMP CCVIPtools::MorphDilate(long* image, int kernel_type, int kernel_size, int height, int width, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image *im = (Image*)(*image), *ret = NULL;
    if (getNoOfBands_Image(im) == 1)
    {
        im = ::duplicate_Image((Image*)(*image));
        ret = ::MorphDilate(im, kernel_type, kernel_size, height, width);
    }
    else
    {
        Image* bands[3];
        for (int i = 0; i < 3; i++)
        {
            im = ::duplicate_Image((Image*)(*image));
            Image* band = ::extract_band(im, i + 1);
            bands[i] = ::MorphDilate(band, kernel_type, kernel_size, height, width);
        }
        ret = ::assemble_bands(bands, 3);
        for (int i = 0; i < 3; i++)
            ::delete_Image(bands[i]);
    }
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::MorphDilate_Image(long* image, int* matrix, int userOrg, int x, int y, int size, long* result)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	Image *im = (Image*)(*image), *ret = NULL;
	CVIP_BOOLEAN origin;
	Matrix* kernel = NULL;
	int** temp = new int*[size];
	for (int i = 0; i < size; ++i)
		temp[i] = new int[size];
	kernel = new_Matrix(size, size, CVIP_INTEGER, REAL);
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
		{
			temp[i][j] = *(matrix + ((i*size)+j));
		}
	kernel->rptr = (char**)temp;
	if (userOrg == 0)
		origin = CVIP_NO;
	else
		origin = CVIP_YES;
	if (getNoOfBands_Image(im) == 1)
	{
		im = ::duplicate_Image((Image*)(*image));
		ret = ::MorphDilate_Image(im, kernel, origin, x, y);
	}
	else
	{
		Image* bands[3];
		for (int i = 0; i < 3; i++)
		{
			im = ::duplicate_Image((Image*)(*image));
			Image* band = ::extract_band(im, i + 1);
			bands[i] = ::MorphDilate_Image(band, kernel, origin, x, y);
		}
		ret = ::assemble_bands(bands, 3);
		for (int i = 0; i < 3; i++)
			::delete_Image(bands[i]);
	}
	if (ret == NULL)
		return 0;
	*result = (long)ret;
	return S_OK;
}
STDMETHODIMP CCVIPtools::MorphErode(long* image, int kernel_type, int kernel_size, int height, int width, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image *im = (Image*)(*image), *ret = NULL;
    if (getNoOfBands_Image(im) == 1)
    {
        im = ::duplicate_Image((Image*)(*image));
        ret = ::MorphErode(im, kernel_type, kernel_size, height, width);
    }
    else
    {
        Image* bands[3];
        for (int i = 0; i < 3; i++)
        {
            im = ::duplicate_Image((Image*)(*image));
            Image* band = ::extract_band(im, i + 1);
            bands[i] = ::MorphErode(band, kernel_type, kernel_size, height, width);
        }
        ret = ::assemble_bands(bands, 3);
        for (int i = 0; i < 3; i++)
            ::delete_Image(bands[i]);
    }
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::MorphErode_Image(long* image, long* matrix, int userOrg, int x, int y, int size, long* result)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	Image *im = (Image*)(*image), *ret = NULL;
	CVIP_BOOLEAN origin;
	Matrix* kernel = NULL;
	int** temp = new int*[size];
	for (int i = 0; i < size; ++i)
		temp[i] = new int[size];
	kernel = new_Matrix(size, size, CVIP_INTEGER, REAL);
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
		{
			temp[i][j] = *(matrix + ((i*size) + j));
		}
	kernel->rptr = (char**)temp;
	if (userOrg == 0)
		origin = CVIP_NO;
	else
		origin = CVIP_YES;
	if (getNoOfBands_Image(im) == 1)
	{
		im = ::duplicate_Image((Image*)(*image));
		ret = ::MorphErode_Image(im, kernel, origin, x, y);
	}
	else
	{
		Image* bands[3];
		for (int i = 0; i < 3; i++)
		{
			im = ::duplicate_Image((Image*)(*image));
			Image* band = ::extract_band(im, i + 1);
			bands[i] = ::MorphErode_Image(band, kernel, origin, x, y);
		}
		ret = ::assemble_bands(bands, 3);
		for (int i = 0; i < 3; i++)
			::delete_Image(bands[i]);
	}
	if (ret == NULL)
		return 0;
	*result = (long)ret;
	return S_OK;
}
STDMETHODIMP CCVIPtools::Morpho(long* image, BSTR* surrounds_string, long rotation, long boolfunc, long connectedness, long iterations, long fields, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    char surrounds[_MAX_PATH];
    ::WideCharToMultiByte(CP_ACP, 0, *surrounds_string, -1, surrounds, _MAX_PATH, NULL, NULL);
    Image* im = ::duplicate_Image((Image*)(*image));
    Image* ret = ::morpho(im, surrounds, (CVIP_BOOLEAN)rotation, (int)boolfunc, (int)connectedness, (unsigned int)iterations, (int)fields);
    ::delete_Image(im);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Morpho_com(long* image, BSTR* surrounds_string, long rotation, long boolfunc, long iterations, long subfields, long unused, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    char surrounds_buffer[_MAX_PATH];
    ::WideCharToMultiByte(CP_ACP, 0, *surrounds_string, -1, surrounds_buffer, _MAX_PATH, NULL, NULL);

    int additional_surrounds = 0, num_surrounds = 0;
    int* surrchoice = parse2ints(surrounds_buffer, " ,;:\n", &num_surrounds);
    if (rotation != 0)
    {
        for (int i = 0; i < num_surrounds; i++)
        {
            if (((surrchoice[i] > 1) && (surrchoice[i] < 7)) ||
                ((surrchoice[i] > 8) && (surrchoice[i] < 13)))
            {
                additional_surrounds += 5;
            }
            else if (surrchoice[i] == 8)
                additional_surrounds++;
            else if ((surrchoice[i] == 13) || (surrchoice[i] == 14))
                additional_surrounds += 2;
        }
    }
    Matrix** surrounds = (MATRIX**)calloc(num_surrounds + additional_surrounds, sizeof(MATRIX*));
    byte* surrP[] = {   (byte*)HEXLAT1, (byte*)HEXLAT2, (byte*)HEXLAT3,
                        (byte*)HEXLAT4, (byte*)HEXLAT5, (byte*)HEXLAT6,
                        (byte*)HEXLAT7, (byte*)HEXLAT8, (byte*)HEXLAT9,
                        (byte*)HEXLAT10, (byte*)HEXLAT11, (byte*)HEXLAT12,
                        (byte*)HEXLAT13, (byte*)HEXLAT14 };

    for (int i = 0, *p = surrchoice; i < num_surrounds; i++, p++)
        surrounds[i] = array2MATRIX(surrP[*p - 1], CVIP_BYTE, 3, 3);
    if (rotation != 0)
    {
        int k = num_surrounds;
        for (int i = 0; i < num_surrounds; i++)
        {
            if (((surrchoice[i] > 1) && (surrchoice[i] < 7)) ||
                ((surrchoice[i] > 8) && (surrchoice[i] < 13)))
            {
                for (int j = 0; j < 5; j++, k++)
                    surrounds[k] = hexrotate(surrounds[i], SIX_NWSE, (j + 1) * 60);
            }
            else if (surrchoice[i] == 8)
                surrounds[k++] = hexrotate(surrounds[i], SIX_NWSE, 60);
            else if ((surrchoice[i] == 13) || (surrchoice[i] == 14))
            {
                for (int j = 0; j < 2; j++, k++)
                    surrounds[k] = hexrotate(surrounds[i], SIX_NWSE, (j + 1) * 60);
            }
        }
    }
    CVIP_BOOLEAN(*bF)(CVIP_BOOLEAN a, CVIP_BOOLEAN b);
    switch (boolfunc)
    {
		case 1: bF = &zero; break;
		case 2: bF = &not_a; break;
		case 3: bF = &and; break;
		case 4: bF = &or; break;
		case 5: bF = &xor; break;
		case 6: bF = &not_and; break;
		default: bF = &or_not_and; break;
    }
    Image* im = ::duplicate_Image((Image*)(*image));
    Image* ret = ::morphIterMod_Image(im, surrounds, bF, num_surrounds + additional_surrounds, SIX_NWSE, iterations, (int)subfields);
    ::delete_Image(im);
    for (int i = 0; i < num_surrounds + additional_surrounds; i++)
        ::delete_Matrix(surrounds[i]);
    free(surrounds);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::MorphOpen(long* image, int kernel_type, int kernel_size, int height, int width, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image *im = (Image*)(*image), *ret = NULL;
    if (getNoOfBands_Image(im) == 1)
    {
        im = ::duplicate_Image((Image*)(*image));
        ret = ::MorphOpen(im, kernel_type, kernel_size, height, width);
    }
    else
    {
        Image* bands[3];
        for (int i = 0; i < 3; i++)
        {
            im = ::duplicate_Image((Image*)(*image));
            Image* band = ::extract_band(im, i + 1);
            bands[i] = ::MorphOpen(band, kernel_type, kernel_size, height, width);
        }
        ret = ::assemble_bands(bands, 3);
        for (int i = 0; i < 3; i++)
            ::delete_Image(bands[i]);
    }
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::MorphOpen_Image(long* image, long* matrix, int userOrg, int x, int y, int size, long* result)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	Image *im = (Image*)(*image), *ret = NULL;
	CVIP_BOOLEAN origin;
	Matrix* kernel = NULL;
	int** temp = new int*[size];
	for (int i = 0; i < size; ++i)
		temp[i] = new int[size];
	kernel = new_Matrix(size, size, CVIP_INTEGER, REAL);
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
		{
			temp[i][j] = *(matrix + ((i*size) + j));
		}
	kernel->rptr = (char**)temp;
	if (userOrg == 0)
		origin = CVIP_NO;
	else
		origin = CVIP_YES;
	if (getNoOfBands_Image(im) == 1)
	{
		im = ::duplicate_Image((Image*)(*image));
		ret = ::MorphOpen_Image(im, kernel, origin, x, y);
	}
	else
	{
		Image* bands[3];
		for (int i = 0; i < 3; i++)
		{
			im = ::duplicate_Image((Image*)(*image));
			Image* band = ::extract_band(im, i + 1);
			bands[i] = ::MorphOpen_Image(band, kernel, origin, x, y);
		}
		ret = ::assemble_bands(bands, 3);
		for (int i = 0; i < 3; i++)
			::delete_Image(bands[i]);
	}
	if (ret == NULL)
		return 0;
	*result = (long)ret;
	return S_OK;
}
STDMETHODIMP CCVIPtools::Multi_Resolution_Segment(long* image, long homogeneity_test, double param1, double param2, long run_PCT, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* im = NULL;
    if (getDataType_Image((Image*)(*image)) == CVIP_BYTE)
        im = ::duplicate_Image((Image*)(*image));
    else
        im = ::remap_Image((Image*)(*image), CVIP_BYTE, 0, 255);

    float parameters[2] = {(float)param1, (float)param2};
    Image* ret = ::multi_resolution_segment(im, homogeneity_test, parameters, (CVIP_BOOLEAN)run_PCT);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Multiply_Image(long* image1, long* image2, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* im1 = ::duplicate_Image((Image*)(*image1));
    Image* im2 = ::duplicate_Image((Image*)(*image2));
    Image* ret = ::multiply_Image(im1, im2);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Nearest_Centroid(BSTR* test_set, BSTR* training_set, BSTR* outputfile, int normalization, int distance_measure, float s_min, float s_max, float r_softmax, float r_minkowski, long* error)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    char testfile[_MAX_PATH];
    char trainingfile[_MAX_PATH];
    char outfile[_MAX_PATH];
    ::WideCharToMultiByte(CP_ACP, 0, *test_set, -1, testfile, _MAX_PATH, NULL, NULL);
    ::WideCharToMultiByte(CP_ACP, 0, *training_set, -1, trainingfile, _MAX_PATH, NULL, NULL);
    ::WideCharToMultiByte(CP_ACP, 0, *outputfile, -1, outfile, _MAX_PATH, NULL, NULL);
    *error = nearest_centroid(testfile, trainingfile, outfile, normalization, distance_measure, s_min, s_max, r_softmax, r_minkowski);
    return S_OK;
}
STDMETHODIMP CCVIPtools::Nearest_Neighbor(BSTR* test_set, BSTR* training_set, BSTR* outputfile, int normalization, int distance_measure, float s_min, float s_max, float r_softmax, float r_minkowski, long* error)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    char testfile[_MAX_PATH];
    char trainingfile[_MAX_PATH];
    char outfile[_MAX_PATH];
    ::WideCharToMultiByte(CP_ACP, 0, *test_set, -1, testfile, _MAX_PATH, NULL, NULL);
    ::WideCharToMultiByte(CP_ACP, 0, *training_set, -1, trainingfile, _MAX_PATH, NULL, NULL);
    ::WideCharToMultiByte(CP_ACP, 0, *outputfile, -1, outfile, _MAX_PATH, NULL, NULL);
    *error = nearest_neighbor(testfile, trainingfile, outfile, normalization, distance_measure, s_min, s_max, r_softmax, r_minkowski);
    return S_OK;
}
STDMETHODIMP CCVIPtools::Neg_Exp_Noise(long* image, double variance, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* im = ::duplicate_Image((Image*)(*image));
    float var = (float)variance;
    Image* ret = ::neg_exp_noise(im, &var);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::New_Image(long image_format, long color_space, int bands, int height, int width, long datatype, long data_format, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* ret = ::new_Image((IMAGE_FORMAT )image_format, (COLOR_FORMAT)color_space, bands, height, width, (CVIP_TYPE)datatype, (FORMAT)data_format);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Nonfft_Xformfilter(long* image, long blocksize, long keepdc, long filter_type, long p1, double p2, long filter_order, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* im = ::duplicate_Image((Image*)(*image));
    Image* ret = ::nonfft_xformfilter(im, (int)blocksize, (int)keepdc, (FILTER_TYPE)filter_type, (int)p1, (float)p2, (int)filter_order);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Not_Image(long* image, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* im = ::duplicate_Image((Image*)(*image));
    Image* ret = ::not_Image(im);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Notch(BSTR* filename, long* cols, long* rows, long* radius, long* image, long num_points, long interactive, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    char fname[_MAX_PATH];
    ::WideCharToMultiByte(CP_ACP, 0, *filename, -1, fname, _MAX_PATH, NULL, NULL);
    NOTCH_ZONE* zone = (NOTCH_ZONE*)calloc(num_points, sizeof(NOTCH_ZONE));
    for (int i = 0; i < num_points; i++)
    {
        zone[i].x = (int)cols[i];
        zone[i].y = (int)rows[i];
        zone[i].radius = (int)radius[i] / 2;
    }
    Image* im = ::duplicate_Image((Image*)(*image));
    Image* ret = ::notch(im, fname, zone, (int)num_points, (CVIP_BOOLEAN)interactive);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Object_Crop(long* image, long* coordinates, long format, long r_value, long g_value, long b_value, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    int* coords = (int*)malloc(coordinates[0] * sizeof(int));
    for (int i = 0; i < coordinates[0]; i++)
        coords[i] = (int)coordinates[i + 1];

    Image* im = NULL;
    if (getDataType_Image((Image*)(*image)) == CVIP_BYTE)
        im = ::duplicate_Image((Image*)(*image));
    else
        im = ::remap_Image((Image*)(*image), CVIP_BYTE, 0, 255);

    Image* ret = ::object_crop(im, coordinates[0], coords, (int)format, (int)r_value, (int)g_value, (int)b_value);
    free(coords);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Open_Consol_Redirect_Output()
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    if (!AllocConsole())
        return S_OK;

    int handle = _open_osfhandle((long)GetStdHandle(STD_OUTPUT_HANDLE), _O_TEXT);
    FILE* fp = _fdopen(handle, "w");
    *stdout = *fp;

    handle = _open_osfhandle((long)GetStdHandle(STD_ERROR_HANDLE), _O_TEXT);
    fp = _fdopen(handle, "w");
    *stderr = *fp;

    printf("****************************************************\n");
    printf("*       CVIPWin32 VB based on CVICOM               *\n");
    printf("*          Version: Interal release                *\n");
    printf("*               C Library         by               *\n");
    printf("*          Scott Umbaugh, Kun Luo, Zhen Li         *\n");
    printf("*       Arve Kjoelen, Mark Zuke, Yansheng Wei      *\n");
    printf("*            COM interface by                      *\n");
    printf("*          Dejun Zhang, Xiaohe Chen, Huashi Ding   *\n");
    printf("*            Visual Basic 6.0 Code by              *\n");
    printf("*          Dejun Zhang, Xiaohe Chen, Huashi Ding   *\n");
    printf("*                     COPYRIGHT                    *\n");
    printf("*         Electrical Engineering Department        *\n");
    printf("*   Southern Illinois University at Edwardsville   *\n");
    printf("****************************************************\n");

    return S_OK;
}
STDMETHODIMP CCVIPtools::Or_Image(long* image1, long* image2, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* im1 = ::duplicate_Image((Image*)(*image1));
    Image* im2 = ::duplicate_Image((Image*)(*image2));
    Image* ret = ::or_Image(im1, im2);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Orientation(long* labeled_image, int row, int col, long* orientation)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    *orientation = (long)::orientation((Image*)(*labeled_image), row, col);
    return S_OK;
}
STDMETHODIMP CCVIPtools::Otsu_Segment(long* image, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* im = ::duplicate_Image((Image*)(*image));
    Image* ret = ::otsu_segment(im);
    ::delete_Image(im);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Overlap_Coef(long* image1, long* image2, VARIANT* error_values)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* im1 = (Image*)(*image1);
    Image* im2 = (Image*)(*image2);
    int bands = max(im1->bands, im2->bands);
    double* error = ::overlap_coef(im1, im2);
    if (error == NULL)
        return 0;

    // Create the safe-array...
    COleSafeArray saRet;
    DWORD numElements = bands;
    saRet.Create(VT_R8, 1, &numElements);
    for (long idx = 0; idx < numElements; idx++)
        saRet.PutElement(&idx, error + idx);
    free(error);
    *error_values = saRet.Detach();
    return S_OK;
}
STDMETHODIMP CCVIPtools::Param_AD_Filter(long* image, long iterations, long speed, long edge_height, long blocksize, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* im = ::duplicate_Image((Image*)(*image));
    Image* ret = ::param_ad_filter(im, (int)iterations, (int)speed, (int)edge_height, (int)blocksize);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Parametric_Wiener(long* degr_image, long* degr_fn, long* psd_noise, long* psd_orig, double gamma, long max_gain, long cutoff, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* im = ::duplicate_Image((Image*)(*degr_image));
    Image* fn = ::duplicate_Image((Image*)(*degr_fn));
    Image* noise = ::duplicate_Image((Image*)(*psd_noise));
    Image* orig = ::duplicate_Image((Image*)(*psd_orig));
    Image* ret = ::parametric_wiener(im, fn, noise, orig, (float)gamma, (int)max_gain, (int)cutoff);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Pct(long* image, long ignore_background, double* background, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* im = ::duplicate_Image((Image*)(*image));
    float* mask = new float[im->bands];
    for (int i = 0; i < im->bands; i++)
        mask[i] = (float)background[i];
    Image* ret = ::pct(im, (CVIP_BOOLEAN)ignore_background, mask);
    delete [] mask;
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Pct_Color(long* image, long ignore_background, double* background, long choice, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* im = ::duplicate_Image((Image*)(*image));
    float* mask = new float[im->bands];
    for (int i = 0; i < im->bands; i++)
        mask[i] = (float)background[i];
    Image* ret = ::pct_color(im, (CVIP_BOOLEAN)ignore_background, mask, (int)choice);
    delete [] mask;
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Pct_Median_Segment(long* image, long num_colors, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* im = ::duplicate_Image((Image*)(*image));
    Image* ret = ::pct_median_segment(im, (int)num_colors);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Perimeter(long* labeled_image, int row, int col, long* perimeter)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    *perimeter = (long)::perimeter((Image*)(*labeled_image), row, col);
    return S_OK;
}
STDMETHODIMP CCVIPtools::Pngtocvip(BSTR* filename, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    char fname[_MAX_PATH];
    ::WideCharToMultiByte(CP_ACP, 0, *filename, -1, fname, _MAX_PATH, NULL, NULL);
    Image* ret = ::pngtocvip(fname);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Power_Spect_Eq(long* degr_image, long* degr_fn, long* psd_noise, long* psd_orig, long max_gain, long cutoff, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* im = ::duplicate_Image((Image*)(*degr_image));
    Image* fn = ::duplicate_Image((Image*)(*degr_fn));
    Image* noise = ::duplicate_Image((Image*)(*psd_noise));
    Image* orig = ::duplicate_Image((Image*)(*psd_orig));
    Image* ret = ::power_spect_eq(im, fn, noise, orig, (int)max_gain, (int)cutoff);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Pratt_Merit(long* image1, long* image2, double scale_factor, double* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* im1 = (Image*)(*image1);
    Image* im2 = (Image*)(*image2);
    *result = (double)::pratt_merit(im1, im2, scale_factor);
    return S_OK;
}
STDMETHODIMP CCVIPtools::Prewitt_Filter(long* image, long* dir_image, long filter_type, long kernel_size, long keepdc, long threshold, long* mag_image)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* im = ::duplicate_Image((Image*)(*image));
    Image* dir = (Image*)calloc(1, sizeof(Image));
    Image* ret = ::prewitt_filter(im, dir, (int)filter_type, (int)kernel_size, (int)keepdc, (int)threshold);
    if (ret == NULL)
        return 0;
    *dir_image = (long)dir;
    *mag_image = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Print_Image(int dc, long* image)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* im = (Image*)(*image);
    if (im == NULL)
        return S_OK;

    PRINTDLG PrtDlg;
    if (!AfxGetApp()->GetPrinterDeviceDefaults(&PrtDlg))
        return FALSE; //If no defaults then no printer!!

    CPrintDialog* pdlg = new CPrintDialog(FALSE, 0, NULL);
    if (pdlg->DoModal() == IDOK)
    {
        int rows = im->image_ptr[0]->rows;
        int cols = im->image_ptr[0]->cols;
        HDC dcPrinter = pdlg->GetPrinterDC();
        CDC* pDC = new CDC;
        pDC->Attach(dcPrinter);
        HDC hdc = (dc != 0) ? (HDC)dc : ::CreateCompatibleDC(dcPrinter);
        if (dc == 0)
        {
            HBITMAP hbmp = ::CreateCompatibleBitmap(dcPrinter, cols, rows);
            ::SelectObject(hdc, hbmp);
            for (int r = 0; r < rows; r++)
            {
                for (int c = 0; c < cols; c++)
                {
                    switch (im->bands)
                    {
                    case 1:
                        ::SetPixel(hdc, c, r,
                            RGB(im->image_ptr[0]->rptr[r][c],
                                im->image_ptr[0]->rptr[r][c],
                                im->image_ptr[0]->rptr[r][c])
                            );
                        break;

                    case 3:
                        ::SetPixel(hdc, c, r,
                            RGB(im->image_ptr[0]->rptr[r][c],
                                im->image_ptr[1]->rptr[r][c],
                                im->image_ptr[2]->rptr[r][c])
                            );
                        break;
                    }
                }
            }
            ::DeleteObject(hbmp);
        }
        ::BitBlt(pDC->GetSafeHdc(), 0, 0, cols, rows, hdc, 0, 0, SRCCOPY);
        ::DeleteDC(hdc);
    }
    return S_OK;
}
STDMETHODIMP CCVIPtools::Projection(long* labeled_image, int row, int col, int height, int width, VARIANT* projections)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* labeled = (Image*)(*labeled_image);
    int* proj = ::projection(labeled, row, col, height, width);
    if (proj == NULL)
        return 0;

    // Create the safe-array...
    COleSafeArray saRet;
    DWORD numElements = height + width;
    saRet.Create(VT_I4, 1, &numElements);
    for (long idx = 0; idx < numElements; idx++)
        saRet.PutElement(&idx, proj + idx);
    free(proj);
    *projections = saRet.Detach();
    return S_OK;
}
STDMETHODIMP CCVIPtools::Pseudo_Remap(long* image, long* lookup_table, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    byte** byte_table = (byte**)malloc(3 * sizeof(byte*));
    byte_table[0] = (byte*)malloc(3 * 256 * sizeof(byte));
    byte_table[1] = byte_table[0] + 256;
    byte_table[2] = byte_table[1] + 256;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 256; j++)
            byte_table[i][j] = (byte)lookup_table[(i * 256) + j];
    }
    Image* im = NULL;
    if (getDataType_Image((Image*)(*image)) == CVIP_BYTE)
        im = ::duplicate_Image((Image*)(*image));
    else
        im = ::remap_Image((Image*)(*image), CVIP_BYTE, 0, 255);

    Image* ret = ::pseudo_remap(im, byte_table);
    ::delete_Image(im);
    free(byte_table[0]);
    free(byte_table);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Pseudocol_Freq(long* image, int low_cutoff, int high_cutoff, int lowpass_band, int bandpass_band, int highpass_band, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    if ((low_cutoff >= high_cutoff) ||
        (lowpass_band == bandpass_band) ||
        (lowpass_band == highpass_band) ||
        (bandpass_band == highpass_band) ||
        (((Image*)*image)->bands != 1))
    {
        return 0;
    }
    Image* im = NULL;
    if (getDataType_Image((Image*)(*image)) != CVIP_FLOAT)
        im = ::duplicate_Image((Image*)(*image));
    else
        im = ::remap_Image((Image*)(*image), CVIP_INTEGER, INT_MIN, INT_MAX);

    Image* ret = ::pseudocol_freq(im, low_cutoff, high_cutoff, lowpass_band, bandpass_band, highpass_band);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Raster_Deblur_Filter(long* image, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* im = ::duplicate_Image((Image*)(*image));
    Image* ret = ::raster_deblur_filter(im);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Rayleigh_Noise(long* image, double variance, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* im = ::duplicate_Image((Image*)(*image));
    float var = (float)variance;
    Image* ret = ::rayleigh_noise(im, &var);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Read_Image(BSTR* filename, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    char fname[_MAX_PATH];
    ::WideCharToMultiByte(CP_ACP, 0, *filename, -1, fname, _MAX_PATH, NULL, NULL);
    Image* im = ::read_Image(fname, CVIP_YES);
    if (im == NULL)
        return 0;
    *result = (long)im;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Remap_Image(long* image, long datatype, long dmin, long dmax, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* ret = NULL;
    if (getDataType_Image((Image*)(*image)) == datatype)
        ret = ::duplicate_Image((Image*)(*image));
    else
        ret = ::remap_Image((Image*)(*image), (CVIP_TYPE)datatype, dmin, dmax);

    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::REMAPP(long* image, long datatype, long dmin, long dmax, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* ret = ::remap_Image((Image*)(*image), (CVIP_TYPE)datatype, dmin, dmax);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Render_DisplayImage(long window_dc, long* image, long* memory_dc)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    return __Render_DisplayImage(window_dc, image, memory_dc);
}
STDMETHODIMP CCVIPtools::Rms_Error(long* image1, long* image2, VARIANT* rms_values)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* im1 = (Image*)(*image1);
    Image* im2 = (Image*)(*image2);
    float* error = ::rms_error(im1, im2);
    if (error == NULL)
        return 0;

    // Create the safe-array...
    COleSafeArray saRet;
    DWORD numElements = im1->bands;
    saRet.Create(VT_R4, 1, &numElements);
    for (long idx = 0; idx < numElements; idx++)
        saRet.PutElement(&idx, error + idx);
    free(error);
    *rms_values = saRet.Detach();
    return S_OK;
}
STDMETHODIMP CCVIPtools::Robinson_Filter(long* image, long* dir_image, long mask_type, long masksize, long keepdc, long threshold, long* mag_image)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* im = ::duplicate_Image((Image*)(*image));
    Image* dir = (Image*)calloc(1, sizeof(Image));
    Image* ret = ::robinson_filter(im, dir, (int)mask_type, (int)masksize, (int)keepdc, (int)threshold);
    ::delete_Image(im);
    if (ret == NULL)
        return 0;
    *dir_image = (long)dir;
    *mag_image = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Rotate(long* image, float degrees, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* im = ::duplicate_Image((Image*)(*image));
    Image* ret = ::rotate(im, degrees);
    ::delete_Image(im);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Rst_invariant(long* labeled_image, long row, long col, VARIANT* features)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* im = (Image*)(*labeled_image);
    double* rst = ::rst_invariant(im, row, col);
    if (rst == NULL)
        return 0;

    // Create the safe-array...
    COleSafeArray saRet;
    DWORD numElements = 7;
    saRet.Create(VT_R8, 1, &numElements);
    for (long idx = 0; idx < numElements; idx++)
        saRet.PutElement(&idx, rst + idx);
    free(rst);
    *features = saRet.Detach();
    return S_OK;
}
STDMETHODIMP CCVIPtools::Save_Compressed_Data(long* image, BSTR* filename)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    char fname[_MAX_PATH];
    ::WideCharToMultiByte(CP_ACP, 0, *filename, -1, fname, _MAX_PATH, NULL, NULL);

    Image* im = NULL;
    IMAGE_FORMAT format = ((Image*)(*image))->image_format;
    if (((format == ZON) || (format == ZON2)) &&
        (getDataType_Image((Image*)(*image)) != CVIP_BYTE))
    {
        im = ::remap_Image((Image*)(*image), CVIP_BYTE, 0, 255);
    }
    else
    {
        im = ::duplicate_Image((Image*)(*image));
    }
    switch (format)
    {
    case JPG:
        ::write_Image(im, fname, CVIP_YES, CVIP_NO, JPG, CVIP_YES);
        break;
    case JP2:
        ::write_Image(im, fname, CVIP_YES, CVIP_NO, JP2, CVIP_YES);
        break;
    default:
        ::write_Image(im, fname, CVIP_YES, CVIP_NO, VIP, CVIP_YES);
        break;
    }
    ::delete_Image(im);
    return S_OK;
}
STDMETHODIMP CCVIPtools::Sct_Split_Segment(long* image, long A_split, long B_split, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* im = NULL;
    if (getDataType_Image((Image*)(*image)) == CVIP_BYTE)
        im = ::duplicate_Image((Image*)(*image));
    else
        im = ::remap_Image((Image*)(*image), CVIP_BYTE, 0, 255);

    Image* ret = ::sct_split_segment(im, (int)A_split, (int)B_split);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Set_Console(long unused)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    char pipenames[2][_MAX_PATH];
    for (int i = 0; i < 2; i++)
    {
        GUID guid;
        RPC_CSTR guidstr;
        char buf[37];

        CoCreateGuid(&guid);
        UuidToString(&guid, &guidstr);
        for (int j = 0; j < 36; j++)
            buf[j] = (char)guidstr[j];
        buf[36] = '\0';
        RpcStringFree(&guidstr);
        sprintf(pipenames[i], "\\\\.\\pipe\\%s", buf);
    }
    USES_CONVERSION;
    hStdout = CreateNamedPipe((LPCTSTR)pipenames[0],
                            PIPE_ACCESS_INBOUND,
                            0,
                            PIPE_NOWAIT,
                            CCVIPtools::nBufferSize,
                            CCVIPtools::nBufferSize,
                            500,
                            NULL);

    hStderr = CreateNamedPipe((LPCTSTR)pipenames[1],
                            PIPE_ACCESS_INBOUND,
                            0,
                            PIPE_NOWAIT,
                            CCVIPtools::nBufferSize,
                            CCVIPtools::nBufferSize,
                            500,
                            NULL);

    fpStdout = freopen(pipenames[0], "w", stdout);
    ConnectNamedPipe(hStdout, NULL);
    fpStderr = freopen(pipenames[1], "w", stderr);
    ConnectNamedPipe(hStderr, NULL);

    printf("****************************************************\n");
    printf("*         CVIPtools Function Information         *\n");
    printf("****************************************************\n");

    return S_OK;
}
STDMETHODIMP CCVIPtools::Sharpen_I(long* image, long remap, long mask_type, long masksize, float low_clip, float high_clip, long add2original, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
	
    Image* im = (Image*)(*image);
    // Laplacian Filter with keepDC
    Image* laplacian = ::edge_detect_filter(::duplicate_Image(im), EDGE_LAPLACIAN, -1, (int)mask_type, 0, -1, 0, 0, 0);
    // Sobel Filter
    //Image* sobel = ::edge_detect_filter(::duplicate_Image(im), EDGE_SOBEL, -1, (int)masksize, 0, -1, 0, 0, 0);
    Image* dir = (Image*)calloc(1, sizeof(Image));
    Image* sobel = ::sobel_filter(::duplicate_Image(im), dir, -1, (int)masksize, -1, -1);
    
	
	
	// multiply two image
    Image* multiply = ::multiply_Image(laplacian, sobel);
    // then remap if possible, remap create a new image
    if (remap)
    {
        Image* tmp = multiply;
        multiply = ::remap_Image(tmp, CVIP_BYTE, 0, 255);
        ::delete_Image(tmp);
    }
    // add to original image
    if (add2original != 0)
        multiply = ::add_Image(multiply, ::duplicate_Image(im));
    // histogram stretch
    Image* ret = ::hist_stretch(multiply, 0, 255, low_clip, high_clip);
    ::delete_Image(multiply);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Sharpen_II(long* image, long add2original, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* im = (Image*)(*image);
    // histogram shrink
    Image* shrink = remap_Image(im, CVIP_BYTE, 10, 100);
    // roberts edge detection
	shrink = ::edge_detect_filter(shrink,EDGE_ROBERTS,-1, 1, -1, -1, -1, -1, -1);
	Image* add = NULL;
	if (add2original != 0)
		add = ::add_Image(shrink, ::duplicate_Image(im));
	else
		add = shrink;
	add = remap_Image(add, CVIP_BYTE, 0, 255);
	Image* ret = NULL;
    if (im->bands == 1)
        ret = ::histeq(add, 0);
    else
    {
        float norm[3] = {255.0f, 255.0f, 255.0f};
        float ref[3] = {1.0f, 1.0f, 1.0f};
        Image *fwd_xform = NULL, *eq = NULL, *inv_xform = NULL;
        fwd_xform = ::colorxform(add, HSL, norm, ref, 1);
        eq = histeq(fwd_xform, 2);
        inv_xform = ::colorxform(eq, HSL, norm, ref, 0);
        ret = ::remap_Image(inv_xform, CVIP_BYTE, 0, 255);
        ::delete_Image(inv_xform);
    }
	if (ret == NULL)
		return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Sharpen_III(long* image, long add2original, long* result)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	Image* im = (Image*)(*image);
	// histogram shrink
	Image* shrink = remap_Image(im, CVIP_BYTE, 10, 100);
	// image sharp
	::image_sharp(shrink);
	Image* ret = NULL;
	if (im->bands == 1)
		ret = ::histeq(shrink, 0);
	else
	{
		float norm[3] = { 255.0f, 255.0f, 255.0f };
		float ref[3] = { 1.0f, 1.0f, 1.0f };
		Image *fwd_xform = NULL, *eq = NULL, *inv_xform = NULL;
		fwd_xform = ::colorxform(shrink, HSL, norm, ref, 1);
		eq = histeq(fwd_xform, 2);
		inv_xform = ::colorxform(eq, HSL, norm, ref, 0);
		ret = ::remap_Image(inv_xform, CVIP_BYTE, 0, 255);
		::delete_Image(inv_xform);
	}
	if (add2original != 0)
		ret = ::add_Image(ret, ::duplicate_Image(im));
	if (ret == NULL)
		return 0;
	*result = (long)ret;
	return S_OK;
}
STDMETHODIMP CCVIPtools::Shen_Castan_Filter(long* image, double smoothing_factor, long window_size, double low_threshold, double high_threshold, long thin_factor, long* intermediate_image, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* im = ::duplicate_Image((Image*)(*image));
    Image* intermediate = (Image*)calloc(1, sizeof(Image));
    Image* ret = ::shen_castan_filter(im, intermediate, (float)smoothing_factor, (int)window_size, (float)low_threshold, (float)high_threshold, (int)thin_factor);
    ::delete_Image(im);
    if (ret == NULL)
        return 0;
    *intermediate_image = (long)intermediate;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Show_DisplayImage(long window_dc, long memory_dc, long window_width, long window_height, long memory_width, long memory_height)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    return __Show_DisplayImage(window_dc, memory_dc, window_width, window_height, memory_width, memory_height);
}
STDMETHODIMP CCVIPtools::Show_Image(int dc, int x, int y, long* image)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* im = (Image*)(*image);
    if (im == NULL)
        return S_OK;

    int rows = im->image_ptr[0]->rows ;
    int cols = im->image_ptr[0]->cols ;
    HDC hdc1= (HDC)dc;
    HDC hdc = ::CreateCompatibleDC(hdc1);
    HBITMAP hb = ::CreateCompatibleBitmap(hdc1, cols, rows);
    ::SelectObject(hdc, hb);
    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < cols; c++)
        {
            switch (im->bands)
            {
            case 1:
                ::SetPixel(hdc, c, r,
                    RGB(im->image_ptr[0]->rptr[r][c],
                        im->image_ptr[0]->rptr[r][c],
                        im->image_ptr[0]->rptr[r][c])
                    );
                break;

            case 3:
                ::SetPixel(hdc, c, r,
                    RGB(im->image_ptr[0]->rptr[r][c],
                        im->image_ptr[1]->rptr[r][c],
                        im->image_ptr[2]->rptr[r][c])
                    );
                break;
            }
        }
    }
    ::DeleteObject(hb);
    ::BitBlt(hdc1, 0, 0, cols, rows, hdc, 0, 0, SRCCOPY);
    ::DeleteDC(hdc);
    return S_OK;
}
STDMETHODIMP CCVIPtools::Show_Image_Ex(int window_dc, long* memory_dc, int x, int y, long* image)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* im = (Image*)(*image);
    if (im == NULL)
        return S_OK;

    int rows = im->image_ptr[0]->rows;
    int cols = im->image_ptr[0]->cols;
    HDC dcWindow = (HDC)window_dc;
    HDC hdc = (*memory_dc != 0) ? (HDC)(*memory_dc) : ::CreateCompatibleDC (dcWindow);
    if (*memory_dc == 0)
    {
        HBITMAP  hb = ::CreateCompatibleBitmap(dcWindow, cols, rows);
        ::SelectObject(hdc, hb);
        for (int r = 0; r < rows; r++)
        {
            for (int c = 0; c < cols; c++)
            {
                switch (im->bands)
                {
                case 1:
                    ::SetPixel(hdc, c, r,
                        RGB(im->image_ptr[0]->rptr[r][c],
                            im->image_ptr[0]->rptr[r][c],
                            im->image_ptr[0]->rptr[r][c])
                        );
                    break;

                case 3:
                    ::SetPixel(hdc, c, r,
                        RGB(im->image_ptr[0]->rptr[r][c],
                            im->image_ptr[1]->rptr[r][c],
                            im->image_ptr[2]->rptr[r][c])
                        );
                    break;
                }
            }
        }
        ::DeleteObject(hb);
        *memory_dc = (long)hdc;
    }
    if (((x == cols) && (y == rows)) || ((x == 0) && (y == 0)))
    {
        ::BitBlt(dcWindow, 0, 0, cols, rows, hdc, 0, 0, SRCCOPY);
    }
    else
    {
        HDC hdcScaled = CreateCompatibleDC(dcWindow);
        HBITMAP hbmScaled = CreateCompatibleBitmap(dcWindow, x, y);
        if (hbmScaled == 0)
            return S_OK;

        if (!SelectObject(hdcScaled, hbmScaled))
            return S_OK;

        ::StretchBlt(hdcScaled, 0, 0, x, y, hdc, 0, 0, cols, rows, SRCCOPY);
        ::BitBlt(dcWindow, 0, 0, x, y, hdcScaled, 0, 0, SRCCOPY);
        ::DeleteObject(hbmScaled);
        ::DeleteDC(hdcScaled);
    }
    ::DeleteDC(hdc);
    return S_OK;
}
STDMETHODIMP CCVIPtools::Shrink(long* image, float factor, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* im = ::duplicate_Image((Image*)(*image));
    Image* ret = ::shrink(im, factor);
    ::delete_Image(im);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Simple_Wiener(long* degr_image, long* degr_fn, double k, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* im = ::duplicate_Image((Image*)(*degr_image));
    Image* fn = ::duplicate_Image((Image*)(*degr_fn));
    Image* ret = ::simple_wiener(im, fn, (float)k);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Single_Filter(long* image, double sizing_factor_x, double sizing_factor_y, long centerx, long centery, double rotation, double beta, long kernel_size, double* kernel_data, long choice, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    float* kernel = new float[kernel_size * kernel_size];
    for (int i = 0; i < kernel_size * kernel_size; i++)
        kernel[i] = (float)kernel_data[i];
    Image* im = ::duplicate_Image((Image*)(*image));
    Image* ret = ::single_filter(im, (float)sizing_factor_x, (float)sizing_factor_y, (int)centerx, (int)centery, (float)rotation, (float)beta, (int)kernel_size, kernel, (int)choice);
    delete [] kernel;
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Snr(long* image1, long* image2, VARIANT* snr_values)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* im1 = (Image*)(*image1);
    Image* im2 = (Image*)(*image2);
    float* error = ::snr(im1, im2);
    if (error == NULL)
        return 0;

    // Create the safe-array...
    COleSafeArray saRet;
    DWORD numElements = im1->bands;
    saRet.Create(VT_R4, 1, &numElements);
    for (long idx = 0; idx < numElements; idx++)
        saRet.PutElement(&idx, error + idx);
    free(error);
    *snr_values = saRet.Detach();
    return S_OK;
}
STDMETHODIMP CCVIPtools::Sobel_Filter(long* image, long* dir_image, long filter_type, long kernel_size, long keepdc, long threshold, long* mag_image)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* im = ::duplicate_Image((Image*)(*image));
    Image* dir = (Image*)calloc(1, sizeof(Image));
    Image* ret = ::sobel_filter(im, dir, (int)filter_type, (int)kernel_size, (int)keepdc, (int)threshold);
    if (ret == NULL)
        return 0;
    *dir_image = (long)dir;
    *mag_image = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Spatial_Quant(long* image, int rows, int cols, int method, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* im = ::duplicate_Image((Image*)(*image));
    Image* ret = ::spatial_quant(im, rows, cols, method);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Spec_Hist_Image(long* image, BSTR* r_histogram, BSTR* g_histogram, BSTR* b_histogram, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    char* histograms[3];
    for (int i = 0; i < 3; i++)
        histograms[i] = (char*)calloc(_MAX_PATH, sizeof(char));
    ::WideCharToMultiByte(CP_ACP, 0, *r_histogram, -1, histograms[0], _MAX_PATH, NULL, NULL);
    ::WideCharToMultiByte(CP_ACP, 0, *g_histogram, -1, histograms[1], _MAX_PATH, NULL, NULL);
    ::WideCharToMultiByte(CP_ACP, 0, *b_histogram, -1, histograms[2], _MAX_PATH, NULL, NULL);

    Image* im = NULL;
    if (getDataType_Image((Image*)(*image)) == CVIP_BYTE)
        im = ::duplicate_Image((Image*)(*image));
    else
        im = ::remap_Image((Image*)(*image), CVIP_BYTE, 0, 255);

    Image* ret = ::spec_hist_images(im, histograms);
    ::delete_Image(im);
    for (int i = 0; i < 3; i++)
        free(histograms[i]);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Specify_Filter(long* image, long mask_height, long mask_width, double* mask_values, int normalization, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    float** values = (float**)calloc(mask_height, sizeof(float*));
    values[0] = (float*)calloc(mask_height * mask_width, sizeof(float));
    for (int r = 1; r < mask_height; r++)
        values[r] = values[r - 1] + mask_width;
    for (int r = 0; r < mask_height; r++)
    {
        for (int c = 0; c < mask_width; c++)
            values[r][c] = (float)mask_values[(r * mask_width) + c];
    }
    Matrix* mask = ::specify_filter(mask_height, mask_width, values);
    free(values[0]);
    free(values);

    Image* im = NULL;
    if (getDataType_Image((Image*)(*image)) == CVIP_BYTE)
        im = ::duplicate_Image((Image*)(*image));
    else
        im = ::remap_Image((Image*)(*image), CVIP_BYTE, 0, 255);

    Image* ret = NULL;
    if (normalization != 0)
        ret = ::convolve_filter(im, mask);
    else
        ret = ::convolve_filter_non_normalization(im, mask);
    ::delete_Matrix(mask);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Speckle_Noise(long* image, double psalt, double ppepper, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* im = ::duplicate_Image((Image*)(*image));
    float salt = (float)psalt;
    float pepper = (float)ppepper;
    Image* ret = ::speckle_noise(im, &salt, &pepper);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Spectral_Feature(long* image, long* labeled_image, long rings, long sectors, long row, long col, VARIANT* features)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* im = (Image*)(*image);
    Image* labeled = (Image*)(*labeled_image);
    POWER* spectral = ::spectral_feature(im, labeled, rings, sectors, row, col);
    if (spectral == NULL)
        return 0;

    // Create the safe-array...
    COleSafeArray saRet;
    DWORD numElements = (im->bands * rings) + (im->bands * sectors) + im->bands + 3;
    saRet.Create(VT_R8, 1, &numElements);

    long idx = 0;
    double val = spectral->no_of_sectors;
    saRet.PutElement(&idx, &val);

    idx++;
    val = spectral->no_of_bands;
    saRet.PutElement(&idx, &val);

    idx++;
    val = spectral->imagebands;
    saRet.PutElement(&idx, &val);
    for (int band = 0; band < im->bands; band++)
    {
        idx++;
        val = spectral->dc[band];
        saRet.PutElement(&idx, &val);

        for (int ring = 0; ring < rings; ring++)
        {
            idx++;
            val = spectral->band[(band * rings) + ring];
            saRet.PutElement(&idx, &val);
        }
        for (int sector = 0; sector < sectors; sector++)
        {
            idx++;
            val = spectral->sector[(band * sectors) + sector];
            saRet.PutElement(&idx, &val);
        }
    }
    free(spectral);
    *features = saRet.Detach();
    return S_OK;
}
STDMETHODIMP CCVIPtools::Split_Merge_Segment(long* image, long level, long homogeneity_test, double param1, double param2, long run_PCT, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* im = NULL;
    if (getDataType_Image((Image*)(*image)) == CVIP_BYTE)
        im = ::duplicate_Image((Image*)(*image));
    else
        im = ::remap_Image((Image*)(*image), CVIP_BYTE, 0, 255);

    float parameters[2] = {(float)param1, (float)param2};
    Image* ret = ::split_merge_segment(im, (unsigned int)level, (unsigned int)homogeneity_test, parameters, (CVIP_BOOLEAN)run_PCT);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Subtract_Image(long* image1, long* image2, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* im1 = ::duplicate_Image((Image*)(*image1));
    Image* im2 = ::duplicate_Image((Image*)(*image2));
    Image* ret = ::subtract_Image(im1, im2);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::TextureFeature(long* image, long* labeled_image, long row, long col, long distance, long bitmask, VARIANT* features)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* im = (Image*)(*image);
    Image* labeled = (Image*)(*labeled_image);
    TEXTURE* tex = ::texture(im, labeled, 0, (int)row, (int)col, bitmask, (int)distance);
    if (tex == NULL)
        return 0;

    double average = -1.0, range = -1.0;
    switch (bitmask)
    {
    case 1:
        average = tex->ASM[4];
        range = tex->ASM[5];
        break;
    case 2:
        average = tex->contrast[4];
        range = tex->contrast[5];
        break;
    case 4:
        average = tex->correlation[4];
        range = tex->correlation[5];
        break;
    case 16:
        average = tex->IDM[4];
        range = tex->IDM[5];
        break;
    case 256:
        average = tex->entropy[4];
        range = tex->entropy[5];
        break;
    }
    // Create the safe-array...
    COleSafeArray saRet;
    DWORD numElements = 2;
    saRet.Create(VT_R8, 1, &numElements);

    long idx = 0;
    saRet.PutElement(&idx, &average);

    idx++;
    saRet.PutElement(&idx, &range);
    *features = saRet.Detach();
    return S_OK;
}
STDMETHODIMP CCVIPtools::TextureFeature2(long* image, long* labeled_image, long band, long row, long col, long distance, long energy, long inertia, long correlation, long inv_diff, long entropy, long include_zero_pairs, VARIANT* features)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* im = (Image*)(*image);
    Image* labeled = (Image*)(*labeled_image);
    TEXTURE2* tex2 = ::texture2(im, labeled, (int)band, (int)row, (int)col, (int)distance, (int)energy, (int)inertia, (int)correlation, (int)inv_diff, (int)entropy, (int)include_zero_pairs);
    if (tex2 == NULL)
        return 0;

    // Create the safe-array...
    COleSafeArray saRet;
    DWORD numElements = 30;
    saRet.Create(VT_R8, 1, &numElements);
    for (long idx = 0; idx < numElements; )
    {
        switch (idx / 6)
        {
        case 0:
            for (int i = 0; i < 6; i++, idx++)
            {
                double val = tex2->energy[i];
                saRet.PutElement(&idx, &val);
            }
            break;
        case 1:
            for (int i = 0; i < 6; i++, idx++)
            {
                double val = tex2->inertia[i];
                saRet.PutElement(&idx, &val);
            }
            break;
        case 2:
            for (int i = 0; i < 6; i++, idx++)
            {
                double val = tex2->correlation[i];
                saRet.PutElement(&idx, &val);
            }
            break;
        case 3:
            for (int i = 0; i < 6; i++, idx++)
            {
                double val = tex2->IDM[i];
                saRet.PutElement(&idx, &val);
            }
            break;
        case 4:
            for (int i = 0; i < 6; i++, idx++)
            {
                double val = tex2->entropy[i];
                saRet.PutElement(&idx, &val);
            }
            break;
        }
    }
    *features = saRet.Detach();
    return S_OK;
}
STDMETHODIMP CCVIPtools::Thinness(long* labeled_image, int row, int col, double* thinness)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    *thinness = ::thinness((Image*)(*labeled_image), row, col);
    return S_OK;
}
STDMETHODIMP CCVIPtools::Threshold_Segment(long* image, long threshold, long byte_remap, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* im = ::duplicate_Image((Image*)(*image));
    Image* ret = ::threshold_segment(im, (unsigned int)threshold, (CVIP_BOOLEAN)byte_remap);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Tifftocvip(BSTR* filename, int verbose, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    char fname[_MAX_PATH];
    ::WideCharToMultiByte(CP_ACP, 0, *filename, -1, fname, _MAX_PATH, NULL, NULL);
    Image* ret = ::tifftocvip(fname, verbose);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Tile_by_name(BSTR* filename)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    char basename[_MAX_PATH];
    ::WideCharToMultiByte(CP_ACP, 0, *filename, -1, basename, _MAX_PATH, NULL, NULL);

    Image* ret = ::create_black(76800, 1024);
    byte** retdata = (byte**)getData_Image(ret, 0);
    for (int i = 0; i < 60; i++)
    {
        char fname[_MAX_PATH];
        char idx[10];
        ::itoa(i, idx, 10);
        sprintf(fname, "%s%s.jpg", basename, idx);
        Image* im = ::read_Image(fname, NULL);
        int rows = getNoOfRows_Image(im);
        int cols = getNoOfCols_Image(im);
        byte** data = (byte**)getData_Image(im, 0);
        for (int row  = 0; row < rows; row++)
        {
            for (int col = 0; col < cols; col++)
                retdata[row][(i * 1280) + col] = data[row][col];
        }
        ::delete_Image(im);
    }
    ::write_Image(ret, "result.vip", CVIP_YES, CVIP_NO, VIP, CVIP_NO);
    Image* shrink = ::shrink(ret, 0.1);
    ::write_Image(shrink, "result1.vip", CVIP_YES, CVIP_NO, VIP, CVIP_NO);
    ::delete_Image(shrink);
    ::delete_Image(ret);
    return S_OK;
}
STDMETHODIMP CCVIPtools::Transform_Compression(long* image, BSTR* filename, BSTR* quantfile, long color_space, long xform, long basis, long blocksize, long quantization, long use_quant_table, long use_vector_quant, long datatype, long remap_type, long keepdc, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    char fname[_MAX_PATH];
    char quantfname[_MAX_PATH];
    ::WideCharToMultiByte(CP_ACP, 0, *filename, -1, fname, _MAX_PATH, NULL, NULL);
    ::WideCharToMultiByte(CP_ACP, 0, *quantfile, -1, quantfname, _MAX_PATH, NULL, NULL);
    Image* im = ::duplicate_Image((Image*)(*image));
    Image* ret = ::trans_compr(fname, quantfname, im, (int)color_space, (int)xform, (int) basis,
                                (int)blocksize, (int)quantization, (int)use_quant_table,
                                (int)use_vector_quant, (int)datatype, (int)remap_type, (int)keepdc);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Transform_Sharpen(long* image, long xform, long cutoff, long filter_type, long filter_order, long keepdc, long add2original, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image *im = ::duplicate_Image((Image*)(*image)), *fwd_xform = NULL;
    int rows = getNoOfRows_Image(im);
    int cols = getNoOfCols_Image(im);
    int blocksize = (int)pow(2.0, ceil(log((double)max(rows, cols)) / log(2.0)));

    if (get_zpad_dims(im, &rows, &cols, blocksize) == CVIP_YES)
        zero_pad(im, rows, cols);

    switch (xform)
    {
    // perform fast Fourier transform
    case 0:
        fwd_xform = ::fft_transform(im, blocksize);
        break;
    // performs Discrete Cosine Transform
    case 1:
        fwd_xform = ::dct_transform(im, blocksize);
        break;
    // performs a fast Haar transform
    case 2:
        fwd_xform = ::haar_transform(im, 1, blocksize);
        break;
    // performs Walsh or Hadamard transform 1 is Walsh forward
    case 3:
        fwd_xform = ::walhad_transform(im, 1, blocksize);
        break;
    // performs Walsh or Hadamard transform 3 is Hadamard forward
    case 4:
        fwd_xform = ::walhad_transform(im, 3, blocksize);
        break;
    default:
        fwd_xform = ::fft_transform(im, blocksize);
        break;
    }
    // High Pass Filter
    Image *highpass = NULL, *inv_xform = NULL;
    highpass = ::hpf_filter(fwd_xform, xform, blocksize, filter_type, filter_order, cutoff, keepdc);

    switch (xform)
    {
    // perform inverse fast Fourier transform
    case 0:
        inv_xform = ::ifft_transform(highpass, blocksize);
        break;
    // performs inverse Discrete Cosine Transform
    case 1:
        inv_xform = ::idct_transform(highpass, blocksize);
        break;
    // performs a inverse fast Haar transform
    case 2:
        inv_xform = ::haar_transform(highpass, 0, blocksize);
        break;
    // performs inverse  Walsh or Hadamard transform 1 is Walsh forward
    case 3:
        inv_xform = ::walhad_transform(highpass, 0, blocksize);
        break;
    // performs inverse Walsh or Hadamard transform 3 is Hadamard forward
    case 4:
        inv_xform = ::walhad_transform(highpass, 2, blocksize);
        break;
    default:
        inv_xform = ::ifft_transform(highpass, blocksize);
        break;
    }
    if (add2original != 0)
        inv_xform = ::add_Image(inv_xform, ::duplicate_Image((Image*)(*image)));
    Image* ret = ::hist_stretch(inv_xform, 0, 255, 0.01, 0.01);
    ::delete_Image(inv_xform);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Transform_Smoothing(long* image, long xform, long cutoff, long filter_type, long filter_order, long keepdc, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image *im = ::duplicate_Image((Image*)(*image)), *fwd_xform = NULL;
    int rows = getNoOfRows_Image(im);
    int cols = getNoOfCols_Image(im);
    int blocksize = (int)pow(2.0, ceil(log((double)max(rows, cols)) / log(2.0)));

    if (get_zpad_dims(im, &rows, &cols, blocksize) == CVIP_YES)
        zero_pad(im, rows, cols);

    switch (xform)
    {
    // perform fast Fourier transform
    case 0:
        fwd_xform = ::fft_transform(im, blocksize);
        break;
    // performs Discrete Cosine Transform
    case 1:
        fwd_xform = ::dct_transform(im, blocksize);
        break;
    // performs a fast Haar transform
    case 2:
        fwd_xform = ::haar_transform(im, 1, blocksize);
        break;
    // performs Walsh or Hadamard transform 1 is Walsh forward
    case 3:
        fwd_xform = ::walhad_transform(im, 1, blocksize);
        break;
    // performs Walsh or Hadamard transform 3 is Hadamard forward
    case 4:
        fwd_xform = ::walhad_transform(im, 3, blocksize);
        break;
    default:
        fwd_xform = ::fft_transform(im, blocksize);
        break;
    }
    // Low Pass Filter
    Image *lowpass = NULL, *inv_xform = NULL;
    lowpass = ::lpf_filter(fwd_xform, xform, blocksize, filter_type, filter_order, cutoff, keepdc);

    switch (xform)
    {
    // perform inverse fast Fourier transform
    case 0:
        inv_xform = ::ifft_transform(lowpass, blocksize);
        break;
    // performs inverse Discrete Cosine Transform
    case 1:
        inv_xform = ::idct_transform(lowpass, blocksize);
        break;
    // performs a inverse fast Haar transform
    case 2:
        inv_xform = ::haar_transform(lowpass, 0, blocksize);
        break;
    // performs inverse  Walsh or Hadamard transform 1 is Walsh forward
    case 3:
        inv_xform = ::walhad_transform(lowpass, 0, blocksize);
        break;
    // performs inverse Walsh or Hadamard transform 3 is Hadamard forward
    case 4:
        inv_xform = ::walhad_transform(lowpass, 2, blocksize);
        break;
    default:
        inv_xform = ::ifft_transform(lowpass, blocksize);
        break;
    }
    if (inv_xform == NULL)
        return 0;
    *result = (long)inv_xform;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Translate(long* image, long wrap, int row_offset, int col_offset, int rows, int cols, int row_slide, int col_slide, float fill_val, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* im = ::duplicate_Image((Image*)(*image));
    Image* ret = ::translate(im, (CVIP_BOOLEAN)wrap, row_offset, col_offset, rows, cols, row_slide, col_slide, fill_val);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Uniform_Noise(long* image, double variance, double mean, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* im = ::duplicate_Image((Image*)(*image));
    float fvar = (float)variance;
    float fmean = (float)mean;
    Image* ret = ::uniform_noise(im, &fvar, &fmean);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Unsharp_Filter(long* image, long lower_limit, long upper_limit, double low_clip, double high_clip, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* im = ::duplicate_Image((Image*)(*image));
    Image* ret = ::unsharp_filter(im, (int)lower_limit, (int)upper_limit, (float)low_clip, (float)high_clip);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Vertical_Flip(long* image, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* im = ::duplicate_Image((Image*)(*image));
    Image* ret = ::VerticalFlip(im);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Vq_Compress(long* image, BSTR* filename, long use_file_codebook, long use_fixed_codebook, double error_threshold, BSTR* codebook_filename, long num_entries, long vector_height, long vector_width, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    /***********************************************************************
    "Usage: cvip vector_quant<image, read_codebook, cdbook_infile, error_thres, no_of_entries, rows_per_vector, cols_per_vector, CodeFileName, Scheme number>");
                <image> color or gray;
                <read_codebook 0/1> 0: generate new codebook; 1: using existing codebook;
                <cdbook_infile 0/1> 0: save codebook in separate file; 1: save codebook in compressed file;
                <error_thres> typical value 5~10\n \t<no_of_entries> number of entries in the codebook, typical 8~128
                <rows_per_vector> vertical vector size;
                <cols_per_vector> horizontal vector size;
                <CodeFileName> file name for the codebook
                <Scheme number0/1/2> 0: REGULAR_FORMAT; 1: WVQ3; 2: WVQ2.
    ************************************************************************/
    char fname[_MAX_PATH];
    char cdbookfname[_MAX_PATH];
    cdbookfname[0] = '\0';
    ::WideCharToMultiByte(CP_ACP, 0, *filename, -1, fname, _MAX_PATH, NULL, NULL);
    ::WideCharToMultiByte(CP_ACP, 0, *codebook_filename, -1, cdbookfname, _MAX_PATH, NULL, NULL);
    Image* im = ::duplicate_Image((Image*)(*image));
    *result = ::vq_compress(im, fname, (int)use_file_codebook, (int)use_fixed_codebook, (float)error_threshold, cdbookfname, (int)num_entries, (int)vector_height, (int)vector_width, REGULAR_FORMAT);
    ::delete_Image(im);
    if (*result == 0)
        return 0;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Vq_Decompress(BSTR* filename, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    char fname[_MAX_PATH];
    ::WideCharToMultiByte(CP_ACP, 0, *filename, -1, fname, _MAX_PATH, NULL, NULL);
    Image* ret = ::vq_decompress(fname);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Walhad_Transform(long* image, long xform, long blocksize, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    int rows, cols;
    Image* im = ::duplicate_Image((Image*)(*image));
    if (get_zpad_dims(im, &rows, &cols, (int)blocksize) == CVIP_YES)
        zero_pad(im, rows, cols);
    Image* ret = ::walhad_transform(im, (int)xform, (int)blocksize);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Watershed_Segment(long* image, int merge_result, float threshold, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* im = NULL;
    if (getDataType_Image((Image*)(*image)) == CVIP_BYTE)
        im = ::duplicate_Image((Image*)(*image));
    else
        im = ::remap_Image((Image*)(*image), CVIP_BYTE, 0, 255);

    Image* ret = ::watershed_segment(im, threshold, (CVIP_BOOLEAN)merge_result);
    ::delete_Image(im);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Wavdaub4_Transform(long* image, long direction, long low_band, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* im = ::duplicate_Image((Image*)(*image));
    Image* ret = ::wavdaub4_transform(im, (int)direction, (int)low_band);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Wavhaar_Transform(long* image, long direction, long low_band, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* im = ::duplicate_Image((Image*)(*image));
    Image* ret = ::wavhaar_transform(im, (int)direction, (int)low_band);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Wiener(long* degr_image, long* degr_fn, long* psd_noise, long* psd_orig, long max_gain, long cutoff, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* im = ::duplicate_Image((Image*)(*degr_image));
    Image* fn = ::duplicate_Image((Image*)(*degr_fn));
    Image* noise = ::duplicate_Image((Image*)(*psd_noise));
    Image* orig = ::duplicate_Image((Image*)(*psd_orig));
    Image* ret = ::wiener(im, fn, noise, orig, (int)max_gain, (int)cutoff);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Write_Image(long* image, BSTR* filename, long retain_image, long run_setup, long image_format, long verbose)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    char fname[_MAX_PATH];
    ::WideCharToMultiByte(CP_ACP, 0, *filename, -1, fname, _MAX_PATH, NULL, NULL);
    Image* im = (Image*)(*image);
    ::write_Image(im, fname, (CVIP_BOOLEAN)retain_image, (CVIP_BOOLEAN)run_setup, (IMAGE_FORMAT)image_format, (CVIP_BOOLEAN)verbose);
    return S_OK;
}
STDMETHODIMP CCVIPtools::Write_JPEG_Image(long* image, BSTR* filename, long retain_image, long run_setup, long image_format, long verbose, int ratio)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    char fname[_MAX_PATH];
    ::WideCharToMultiByte(CP_ACP, 0, *filename, -1, fname, _MAX_PATH, NULL, NULL);
    Image* im = (Image*)(*image);
    ::write_JPEG_Image(im, fname, (CVIP_BOOLEAN)retain_image, (CVIP_BOOLEAN)run_setup, (IMAGE_FORMAT)image_format, (CVIP_BOOLEAN)verbose, ratio);
    return S_OK;
}
STDMETHODIMP CCVIPtools::Xor_Error(long* image1, long* image2, VARIANT* error_values)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* im1 = (Image*)(*image1);
    Image* im2 = (Image*)(*image2);
    int bands = max(im1->bands, im2->bands);
    double* error = ::xor_error(im1, im2);
    if (error == NULL)
        return 0;

    // Create the safe-array...
    COleSafeArray saRet;
    DWORD numElements = bands;
    saRet.Create(VT_R8, 1, &numElements);
    for (long idx = 0; idx < numElements; idx++)
        saRet.PutElement(&idx, error + idx);
    free(error);
    *error_values = saRet.Detach();
    return S_OK;
}
STDMETHODIMP CCVIPtools::Xor_Image(long* image1, long* image2, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* im1 = ::duplicate_Image((Image*)(*image1));
    Image* im2 = ::duplicate_Image((Image*)(*image2));
    Image* ret = ::xor_Image(im1, im2);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Xvq_Compress(long* image, long xform, long scheme, BSTR* filename, long output_data_type, long remap_type, long dc_term_handling, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    char fname[_MAX_PATH];
    ::WideCharToMultiByte(CP_ACP, 0, *filename, -1, fname, _MAX_PATH, NULL, NULL);
    Image* im = ::duplicate_Image((Image*)(*image));
    Image* ret = ::xvq(im, (int)xform, (int)scheme, fname, (int)output_data_type, (int)remap_type, (int)dc_term_handling);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Xvq_Decompress(BSTR* filename, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    char fname[_MAX_PATH];
    ::WideCharToMultiByte(CP_ACP, 0, *filename, -1, fname, _MAX_PATH, NULL, NULL);
    Image* ret = ::xvq_decompress(fname);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Ypmean_Filter(long* image, long masksize, long p, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* im = ::duplicate_Image((Image*)(*image));
    Image* ret = ::Ypmean_filter(im, (int)masksize, (int)p);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Zon_Compress(BSTR* filename, long* image, int blocksize, int xform, int mask_type, float compression_ratio)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    char fname[_MAX_PATH];
    ::WideCharToMultiByte(CP_ACP, 0, *filename, -1, fname, _MAX_PATH, NULL, NULL);
    Image* im = ::duplicate_Image((Image*)(*image));
    int ret = ::zon_compress(im, fname, blocksize, xform, mask_type, compression_ratio);
    ::delete_Image(im);
    if (ret != 0)
        return -1;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Zon_Decompress(BSTR* filename, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    char fname[_MAX_PATH];
    ::WideCharToMultiByte(CP_ACP, 0, *filename, -1, fname, _MAX_PATH, NULL, NULL);
    Image* im = ::zon_decompress(fname);
    Image* ret = ::remap_Image(im, CVIP_BYTE, 0, 255);
    ::delete_Image(im);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Zon2_Compress(BSTR* filename, long* image, int blocksize, int xform, int mask_type, float compression_ratio)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    char fname[_MAX_PATH];
    ::WideCharToMultiByte(CP_ACP, 0, *filename, -1, fname, _MAX_PATH, NULL, NULL);
    Image* im = ::duplicate_Image((Image*)(*image));
    int ret = ::zon2_compress(im, fname, blocksize, xform, mask_type, compression_ratio);
    ::delete_Image(im);
    if (ret != 0)
        return -1;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Zon2_Decompress(BSTR* filename, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    char fname[_MAX_PATH];
    ::WideCharToMultiByte(CP_ACP, 0, *filename, -1, fname, _MAX_PATH, NULL, NULL);
    Image* im = ::zon2_decompress(fname);
    Image* ret = ::remap_Image(im, CVIP_BYTE, 0, 255);
    ::delete_Image(im);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Zoom(long* image, int quadrant, int col, int row, int cols, int rows, float factor_requested, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    Image* im = NULL;
    if (getDataType_Image((Image*)(*image)) == CVIP_BYTE)
        im = ::duplicate_Image((Image*)(*image));
    else
        im = ::remap_Image((Image*)(*image), CVIP_BYTE, 0, 255);

    Image* ret = ::zoom(im, quadrant, col, row, cols, rows, factor_requested);
    ::delete_Image(im);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Zvl_Compress(BSTR* filename, long* image)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    char fname[_MAX_PATH];
    ::WideCharToMultiByte(CP_ACP, 0, *filename, -1, fname, _MAX_PATH, NULL, NULL);

    Image* im = NULL;
    if (getDataType_Image((Image*)(*image)) == CVIP_BYTE)
        im = ::duplicate_Image((Image*)(*image));
    else
        im = ::remap_Image((Image*)(*image), CVIP_BYTE, 0, 255);

    int ret = ::zvl_compress(im, fname);
    if (ret != 0)
        return -1;
    return S_OK;
}
STDMETHODIMP CCVIPtools::Zvl_Decompress(BSTR* filename, long* result)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    char fname[_MAX_PATH];
    ::WideCharToMultiByte(CP_ACP, 0, *filename, -1, fname, _MAX_PATH, NULL, NULL);
    Image* ret = ::zvl_decompress(fname);
    if (ret == NULL)
        return 0;
    *result = (long)ret;
    return S_OK;
}
