/***************************************************************************
* ======================================================================
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* ======================================================================
*    
*             File Name: .c
*           Description:  filter
*         Related Files: 
*   Initial Coding Date: Sun April 17, 15:54:12 CDT 1995
*           Portability: Standard (ANSI) C
*             Credit(s): Kun Luo
*                        Southern Illinois University @ Edwardsville
*
** Copyright (C) 1995 SIUE - by Kun Luo.
**
** Permission to use, copy, modify, and distribute this software and its
** documentation for any purpose and without fee is hereby granted, provided
** that the above copyright notice appear in all copies and that both that
** copyright notice and this permission notice appear in supporting
** documentation.  This software is provided "as is" without express or
** implied warranty.
**
** $Log: CVIPspfltr.h,v $
** Revision 1.13  1997/11/21 22:14:58  wzheng
** rename *new_lee=>*exp_ace_filter
** rename lee=>ace2_filter
** rename new_lee1=>log_ace_filter
**
** Revision 1.12  1997/10/14 22:30:22  wzheng
** add alpha and beta into lee
**
** Revision 1.11  1997/10/14 21:34:40  cvip
** *** empty log message ***
**
** Revision 1.10  1997/09/18 17:03:50  wzheng
** adapt_median_filter
**
** Revision 1.9  1997/01/15 17:13:05  yawei
** Global Change:  IMAGE ==> Image
**
 * Revision 1.8  1996/12/30  20:48:32  yawei
 * Added single_filter
 *
 * Revision 1.7  1996/12/30  20:28:01  yawei
 * added missing ")"
 *
 * Revision 1.6  1996/12/30  20:26:19  yawei
 * Added setup function declaration
 *
 * Revision 1.5  1996/12/30  20:22:04  yawei
 * added specify_filter
 *
 * Revision 1.4  1996/12/27  05:52:32  yawei
 * Added new functions
 *
 * Revision 1.3  1996/12/24  22:09:53  yawei
 * Changed function names.
 *
 * Revision 1.2  1996/12/12  21:39:17  akjoele
 * Added convolve_Image().
 *
 * Revision 1.1  1995/06/06  22:05:51  luok
 * Initial revision
 *
 * Revision 1.1  1995/04/17  21:23:27  luok
 * Initial revision
 *
****************************************************************************/
#ifndef  _CVIP_SPATFLTR
#define _CVIP_SPATFLTR

#include "CVIPtoolkit.h"      
#include <math.h>      
#include <limits.h>

#ifdef __cplusplus
extern "C"{
#endif 

extern Image *alpha_filter(Image *imageP, int mask_size, int p);
extern Image *minimum_filter(Image *imageP, int mask_size)  ;      
extern Image *mean_filter(Image *imageW, int mask_size);
extern Image *adapt_median_filter(Image *inputIMAGE,int wmax);
extern Image *exp_ace_filter(Image *inputIMAGE,int wsize,float alpha,float beta);
extern Image *ace2_filter(Image *inputIMAGE,int wsize,float alpha,float beta);
extern Image *log_ace_filter(Image *inputIMAGE,int wsize,float alpha,float beta);
extern Image *contra_filter(Image *imageW, int mask_size, int p);
extern Image *geometric_filter(Image *imageW, int mask_size);
extern Image *harmonic_filter(Image *imageW, int mask_size);
extern Image *Ypmean_filter(Image *imageW, int mask_size, int p) ;
extern Image *midpoint_filter(Image *imageW, int mask_size) ;
extern Image *maximum_filter(Image *imageW, int mask_size);
extern Image *median_filter(Image *inputImage, int size);
extern Image *adaptive_contrast_filter(Image * inputImage, float k1, float k2,
	unsigned int kernel_size, float min_gain,  float max_gain);
extern Image *raster_deblur_filter(Image *cvip_image);
extern Image *acuity_nightvision_filter(Image *cvipImage, char reason, 
	int threshold, int choice);
extern Image *unsharp_filter(Image *inputImage, int lower, int upper,
	float low_clip, float high_clip);
extern Image * mmse_filter(Image  *  inputImage,  float  noise_var,
	unsigned int kernel_size);
extern Matrix * specify_filter(int row, int col, float** temp);
extern Image *single_filter(Image *orig_image, float sx, float sy,
	int xcen, int ycen, float rot, float beta, int N, float *h, int choice);
extern Image *kuwahara_filter(Image *inputImage, int mask_size);
extern Image *improved_mmse_filter(Image *cvipImage, float threshval, int kernel_size, float nvar);
extern Image *cerchar_filter(Image *inputImage);
extern Image *harris_corner_filter(Image *inputImage, float alpha, int threshold, int border, float dmin);
extern Image *moravec_corner_filter ( Image *inputImage, float threshval);
extern Image *ad_filter(Image *imageW, int iteration_num, int speed, int edge_heigt) ;
extern Image *param_ad_filter(Image *imageW, int iteration_num, int speed, int edge_heigt, int block_size) ;
extern Image *canny_filter (float low, float high, float var, Image *inputImage, Image *nonmax_mag, Image *nonmax_dir);
extern void image_sharp(Image* image);

/*Image *convolve_Image(Image *im1, Image *im2, int handle, int center);*/

/* The following setup functions are for backward compatibility, new
 * applications shouldn't use them.
 */

extern Image *alpha_setup(Image *cvipImage);
extern Image *minimum_setup(Image *cvipImage);
extern Image *mean_setup(Image *cvipImage);
extern Image *contra_setup(Image *cvipImage);
extern Image *geometric_setup(Image *cvipImage);
extern Image *harmonic_setup(Image *cvipImage);
extern Image *Ypmean_setup(Image *cvipImage) ;
extern Image *midpoint_setup(Image *cvipImage);
extern Image *maximum_setup(Image *cvipImage);
extern Matrix * get_Input_Filter(int row, int col);
extern Matrix * get_matrix_setup();
extern Image *single_filter_setup (Image *orig_image);
extern Image *ad_setup(Image *cvipImage);
extern Image *adaptive_ad_setup(Image *cvipImage);

#ifdef __cplusplus
}
#endif 

#endif
