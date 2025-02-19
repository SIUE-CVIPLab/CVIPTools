/***************************************************************************
* ======================================================================
* Computer Vision/ImageFuzzy Processing Tool Project - Dr. Scott Umbaugh SIUE
* ======================================================================
*
*             File Name: fuzzyc.h
*           Description: 
*         Related Files: 
*   Initial Coding Date: Tue Jun  1 12:02:26 CDT 1993
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
** $Log: fuzzyc.h,v $
** Revision 1.6  2001/10/15 02:48:56  ycheng
** added variable 'bands' in _ImageFuzzy structure.
**
 * Revision 1.5  1997/01/15  17:11:29  yawei
 * Global Change:  IMAGE ==> Image
 *
 * Revision 1.4  1996/12/23  18:48:43  yawei
 * Changed filename: fuzzycMeans.h ==> fuzzyc.h
 *
 * Revision 1.3  1996/12/23  00:41:00  yawei
 * Changed (const Image) to (Image ) in the setup function
 *
 * Revision 1.2  1996/12/21  00:42:24  yawei
 *  int fuzzycMeans_Image(Image *srcImage, float variance)
 * 	==>Image *fuzzyc_segment(Image *srcImage, float variance)
 *
 * Revision 1.1  1994/10/30  22:43:06  hanceg
 * Initial revision
 *
 * Revision 1.1  1993/06/02  04:48:35  hanceg
 * Initial revision
 *
*
****************************************************************************/
/* this file consists the macro define and basic data struct */
#if !defined(_CVIP_FUZZYC_)
#define _CVIP_FUZZYC_
#define SQRT_2PI      2.506628275
#define PI_255        162.338042

typedef unsigned char Pixel[3];

struct  _ImageFuzzy {
   int    size;
   int    width;
   int    height;
   int    colors;
   int    bands;
   Pixel  **matrix;
};
typedef struct _ImageFuzzy ImageFuzzy;

struct  _Class {
   double mean[3];
   double std[3];
   int    count;
   double peak[3];
   Pixel  color;
};
typedef struct _Class Class;

struct  _Peak {
   double low;
   double peak;
   double up;
};
typedef struct _Peak Peak[3];


typedef double Histogram[3];

#ifdef __cplusplus
extern "C"{
#endif 

extern Image *fuzzyc_segment(Image *srcImage, float variance);
extern Image *fuzzyc_segment_setup(Image *imgP);

#ifdef __cplusplus
}
#endif 

#endif