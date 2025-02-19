/***************************************************************************
* ======================================================================
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* ======================================================================
*
*             File Name: CVIPhisto.h
*           Description: contains function prototypes, type names and constants
*			 for functions contained in libhisto.a.
*         Related Files: Imakefile, histeq.c
*   Initial Coding Date: Wed Jun  2 03:01:47 CDT 1993
*           Portability: Standard (ANSI) C
*             Credit(s): Gregory Hance
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
** $Log: CVIPhisto.h,v $
** Revision 1.11  1997/04/15 22:30:45  yawei
** added band parameter to gray_linear
**
** Revision 1.10  1997/01/15 17:10:30  yawei
** Global Change:  IMAGE ==> Image
**
* Revision 1.9  1996/12/30  19:39:30  yawei
* changed function anmes, and added new functions.
*
* Revision 1.8  1996/12/24  22:26:58  yawei
* image_enhance.h ==> CVIPenhance.h
*
* Revision 1.7  1996/12/24  00:44:14  yawei
* *** empty log message ***
*
* Revision 1.6  1996/12/24  00:43:27  yawei
* Changed include file
*
* Revision 1.5  1996/11/13  23:46:05  yawei
* Added hist_stretch function prototype
*
* Revision 1.4  1996/11/13  23:36:35  yawei
* Added gray_multiply2, gray_multiply, gray_multiply_Setup functions there
*
* Revision 1.3  1996/03/01  19:49:16  akjoele
* Changed prototypes for histeq, since histeq has been rewritten to
* return Image *.
*
* Revision 1.2  1996/02/29  20:29:55  akjoele
* Added prototype for local_heq.
*
* Revision 1.1  1994/10/30  22:43:06  hanceg
* Initial revision
*
*
****************************************************************************/
#if !defined(CVIPHISTO_DEFINED)
    #define CVIPHISTO_DEFINED

#include "CVIPenhance.h"
#include "CVIPgeometry.h"
#include "histogram.h"
#include "waves.h"

#ifdef __cplusplus
    extern "C"{
#endif 

extern Image *histeq(Image *in, int mb);
extern Image *gray_multiply(Image *input,float ratio);
extern Image *gray_multiply2(Image *input,float ratio);
extern Image * hist_stretch(Image * inputImage, int low_limit,
int high_limit, float low_clip, float high_clip);
extern Image * gray_linear(Image * inputImage, double start, double end,
double s_gray, double slope, int change, int band);
extern Image *hist_slide(Image *input,int slide);
extern Image *local_histeq(Image *in, int size, int mb);
extern Image* CLAHE(Image* inputImage, int blocksize, float clipPercent, int bandSelect);
extern Image* CLAHE_Grid(Image* inputImage, int blocksize, float clipPercent, int bandSelect);
extern Image* draw_picture(float** map, int width, int height, int dim);
extern void scale_to_max(float** vec1, float** vec2, int dim, int len);

/* setup function for backward compatibility and for using in CVIPlab, not
* encouraged to be used in CVIPtools
*/
extern Image *histeq_setup(Image *in);
extern Image *local_heq_setup(Image *);
extern Image *gray_multiply_Setup(Image *input);
extern Image* HistSlide_Setup(Image *input);
extern Image* HistMan_Setup(Image *input);
#ifdef __cplusplus
    }
#endif 
#endif /* CVIPHISTO_DEFINED */
