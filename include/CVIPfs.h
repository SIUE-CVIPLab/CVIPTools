/***************************************************************************
* ======================================================================
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* ======================================================================
*
*             File Name: CVIPfs.h
*           Description: contains function prototypes, type names, etc. for
*			 the spatial filtering library.
*         Related Files: Imakefile, edge_detect.c, spatial_tools.c
*   Initial Coding Date: Mon Sep 13 18:12:45 CDT 1993
*           Portability: Standard (ANSI) C
*            References: Pratt book
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
** $Log: CVIPfs.h,v $
** Revision 1.10  1997/05/18 05:44:04  yawei
** changed name IN, FIL, conflict with WIN32
**
** Revision 1.9  1997/01/15 17:13:01  yawei
** Global Change:  IMAGE ==> Image
**
 * Revision 1.8  1996/12/30  22:01:08  yawei
 * changed get_mask(int, int) to get_mask(MASK_TYPE, int)
 *
 * Revision 1.7  1996/12/24  23:19:19  yawei
 * Added "hough" stuff
 *
 * Revision 1.6  1996/12/24  22:07:19  yawei
 * added convolve_Image;
 * renamed edgeDetect_Image ==> edge_detect_setup
 * added edge_detect_filter
 *
 * Revision 1.5  1996/11/04  18:47:07  akjoele
 * Added prototype for get_mask()
 *
 * Revision 1.4  1995/06/12  14:53:42  luok
 * change the defintion of get_default_matrix
 *
 * Revision 1.3  1995/06/01  02:37:57  luok
 * add kernel size option to blur.
 *
 * Revision 1.2  1995/05/31  00:45:07  luok
 * add spatial filter
 *
 * Revision 1.1  1994/10/30  22:43:06  hanceg
 * Initial revision
 *
*
****************************************************************************/
#if !defined( CVIPFS_DEFINED )
   #define CVIPFS_DEFINED

   #include "masks.h"
   #include "CVIPtools.h"

   #define LAPLACIAN 1
   #define ROBERTS 2
   #define SOBEL 3
   #define KIRSCH 4
   #define FREI 5

#ifdef __cplusplus
extern "C"{
#endif 


	/* convolve image */
   extern Image *convolve_filter(Image *imageP, Matrix *filP);
   extern Image *convolve_filter_non_normalization(Image *imageP, Matrix *filP);

	/* edge detect */
   extern Image *edge_detect_setup(Image *imageP, int program);
	extern Image *edge_detect_filter(Image *imageP, int program,
		int mask_choice, int mask_size, int keep_dc, int threhold,
		int threddfs, int thresh,int thr);

	/* hough */
   extern Image * hough_transform(Image* cvipImage,char *interpret,int num);
   extern Image * hough_inverse(Image *cvipImage,int height, int width,
			int threshold);
	extern char* parse_string(char *input);
	extern Image *hough_filter(Image *cvipImage, char *name, char *degree_string,
		int threshold, int connection, int interactive, int delta_length, int SegmentLength, int intermediate_result);
	extern Image* edge_link_filter(Image *cvipImage, int connection);

   extern Matrix *convolve(Matrix *inMatrix, Matrix *filMatrix);
   extern Matrix *convolve_non_normalization(Matrix *inMatrix, Matrix *filMatrix);
   extern Matrix * get_matrix_setup();
   extern Matrix * get_Input_Filter(int row, int col);
   extern Matrix * get_default_filter(PROGRAMS type,int dimension,int direct);
   extern MATRIX *get_mask(MASK_TYPE type,int dimension);


	extern Image *canny_filter (float low, float high, float var, Image *inputImage,
							Image *nonmax_mag, Image *nonmax_dir);

	extern Image *shen_castan_filter(Image *inputImage, Image *zerOut, float b, int window_size,float low_thresh,
						 float  high_thresh,int thinFactor);

	extern Image *boiecox_filter ( Image *inputImage, float var, unsigned int do_thresh, unsigned int do_hyst,
					   unsigned int thin,float high_thld, float low_thld, Image *Imagethld, Image *Imagehyst);

	extern Image* marr_hildreth_filter(Image* inputImage, float sigma, int threshold);
	extern float pratt_merit(Image *inputImage1, Image *inputImage2,  float a);
	extern Image *kirsch_filter(Image *imageP, Image * pdirImage, int mask_choice,int mask_size, int keep_dc, int threshold);
	extern Image *prewitt_filter(Image *inputImage, Image *pdirImage, int mask_choice,int mask_size, int keep_dc, int threshold);
	extern Image *robinson_filter(Image *imageP,Image *pdirimage, int mask_choice,int mask_size, int keep_dc, int threshold);
	extern Image *sobel_filter(Image *inputImage, Image *pdirImage, int mask_choice,int mask_size, int keep_dc, int threshold);

#ifdef __cplusplus
}
#endif 

#endif /* CVIPFS_DEFINED */
