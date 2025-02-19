/***************************************************************************
* ======================================================================
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* ======================================================================
*
*             File Name: CVIPsegment.h
*           Description: 
*         Related Files: 
*   Initial Coding Date: Mon Sep 13 20:13:39 CDT 1993
*           Portability: Standard (ANSI) C
*            References:
*             Author(s): Gregory Hance
*                        Southern Illinois University @ Edwardsville
*
** Copyright (C) 1993 SIUE - by Gregory Hance.
**
** Permission to use, copy, modify, and distribute this software and its
** documentation for any purpose and without fee is hereby granted, provided
** that the above copyright notice appear in all copies and that both that
** copyright notice and this permission notice appear in supporting
** documentation.  This software is provided "as is" without express or
** implied warranty.
**
* RCS (Revision Control System) Information
* ...Added automatically by RCS 
*
** $Log: CVIPsegment.h,v $
 * Revision 1.7  1997/01/15  17:10:58  yawei
 * Global Change:  IMAGE ==> Image
 *
 * Revision 1.6  1997/01/03  21:43:36  yawei
 * added pct_median_segment
 *
 * Revision 1.5  1996/12/23  18:51:51  yawei
 * Changed file names:
 *   MedianCut.h ==> median_cut.h
 *   fuzzycMeans.h ==> fuzzyc.h
 *
 * Revision 1.4  1996/12/23  18:39:35  yawei
 * Changed file names.
 *
 * Revision 1.3  1996/12/21  01:23:53  yawei
 * Changed include header file
 *
 * Revision 1.2  1996/12/17  21:50:26  yawei
 * Added "gray level quantization"
 *
 * Revision 1.1  1994/10/30  22:43:06  hanceg
 * Initial revision
 *
*
****************************************************************************/
#if !defined(CVIPSEGMENT_DEFINED)
 #define CVIPSEGMENT_DEFINED

#include "fuzzyc.h"
#include "split_merge.h"
#include "hist_thresh.h"
#include "median_cut.h"
#include "sct_split.h"
#include "threshold.h"
#include "watershed.h"


#ifdef __cplusplus
extern "C"{
#endif 

 extern Image *MRS_SetUp(const Image *imgP);

extern Image *gray_quant_setup(Image *cvipImage);
extern Image *gray_quant_segment(Image *cvipImage, int num_bits);

extern Image *igs_segment(Image * inputImage, int gray_level);
extern Image *pct_median_segment(Image *imageP, unsigned colors);
extern Image *otsu_segment(Image *inputImage);
extern Image *auto_threshold_segment(Image *inputImage, float limit);
extern Image *snakeSetup(Image *inputImage, int no_of_coords, int *rclist, int iteration_num, double alpha, double beta, double kappa);
extern double *xor_error(Image *inputImage1,Image *inputImage2);
extern double* dice_coef(Image* inputImage1, Image* inputImage2);
extern double* jaccard_index(Image* inputImage1, Image* inputImage2);
extern double* overlap_coef(Image* inputImage1, Image* inputImage2);
extern Image *superPixel(Image* inputImage);

#ifdef __cplusplus
}
#endif 
#endif /* CVIPSEGMENT_DEFINED */
