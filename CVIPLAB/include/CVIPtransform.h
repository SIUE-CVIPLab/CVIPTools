/***************************************************************************
* ======================================================================
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* ======================================================================
*
*             File Name: CVIPtransform.h
*           Description: 
*         Related Files: 
*   Initial Coding Date: Mon Sep 13 20:02:52 CDT 1993
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
** $Log: CVIPtransform.h,v $
** Revision 1.6  1997/04/11 21:42:12  yawei
** chnaged zero_pad to return void
**
** Revision 1.5  1997/03/28 22:46:45  yawei
** changed prototype of zero_pad()
**
** Revision 1.4  1997/03/08 00:48:42  yawei
** Name Changes:
** 	BOOLEAN ==> CVIP_BOOLEAN
** 	FALSE ==> CVIP_YES
** 	TRUE ==> CVIP_NO
** 	BYTE ==> CVIP_BYTE
** 	SHORT ==> CVIP_SHORT
** 	INTEGER ==> CVIP_INTEGER
** 	FLOAT ==> CVIP_FLOAT
** 	DOUBLE ==> CVIP_DOUBLE
** 	TYPE ==> CVIP_TYPE
**
** Revision 1.3  1997/01/15 17:12:01  yawei
** Global Change:  IMAGE ==> Image
**
 * Revision 1.2  1996/12/29  05:31:21  yawei
 * wht2d ==> walhad_transform
 *
 * Revision 1.1  1994/10/30  22:43:06  hanceg
 * Initial revision
 *
 * Revision 1.1  1994/01/27  16:19:56  kjoelena
 * Initial revision
 *
*
****************************************************************************/
#if !defined(CVIPTRANSFORM_DEFINED)

   #define CVIPTRANSFORM_DEFINED

#include "CVIPtoolkit.h"
#include "CVIPdef.h"
typedef enum {FORWARD, INVERSE } FFT_DIRECTION;

#ifdef __cplusplus
extern "C"{
#endif 

/* interactive functions used in setup */
extern CVIP_BOOLEAN get_zpad_dims(Image *image, int *n_rows, int *n_cols,
	int block_size);
extern int get_block_size(void); 

/* utility functions */
extern long calculate_size(int length, CVIP_TYPE data_type);
extern void shift_n_copy(Image *image, float *colordat, int number);
extern void manager(Image *image, float *colordat, FFT_DIRECTION direction,
	int plane, int block_size);
extern CVIP_BOOLEAN image_check(Image *image);
extern CVIP_BOOLEAN check_pow_two(int number);
extern void zero_pad(Image *image, unsigned int rows, unsigned int cols);

extern Image *fft_transform(Image *image, int blocksize);
extern Image *ifft_transform(Image *image, int blocksize);

extern Image *dct_transform( Image *input_Image, int size );
extern Image *idct_transform( Image *input_Image, int size );

extern Image *haar_transform(Image *image, int ibit, int block_size);
extern Image *walhad_transform(Image *image, int ibit, int block_size);

#include "wavelet.h"

/* setup functions for backward compatibility, not encouraged to use */
extern Image *fft_Setup(Image *image, CVIP_BOOLEAN *remap);
extern Image *dct_setup( Image *input_Image, CVIP_BOOLEAN *remap );
extern Image *xform_setup(Image *image, CVIP_BOOLEAN *remap, PROGRAMS transform);

#ifdef __cplusplus
}
#endif 

#endif /* CVIPTRANSFORM_DEFINED */
