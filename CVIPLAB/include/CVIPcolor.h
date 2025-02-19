/***************************************************************************
* ======================================================================
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* ======================================================================
*
*             File Name: CVIPcolor.h
*           Description: contains function prototypes for public access
*			 color transform utilities.
*         Related Files: cxform.c, Imakefile
*   Initial Coding Date: Sun May 30 13:59:41 CDT 1993
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
** $Log: CVIPcolor.h,v $
 * Revision 1.9  1997/03/08  00:45:29  yawei
 * Name Changes:
 * 	BOOLEAN ==> CVIP_BOOLEAN
 * 	FALSE ==> CVIP_YES
 * 	TRUE ==> CVIP_NO
 * 	BYTE ==> CVIP_BYTE
 * 	SHORT ==> CVIP_SHORT
 * 	INTEGER ==> CVIP_INTEGER
 * 	FLOAT ==> CVIP_FLOAT
 * 	DOUBLE ==> CVIP_DOUBLE
 * 	TYPE ==> CVIP_TYPE
 *
** Revision 1.8  1997/01/15 17:09:55  yawei
** Global Change:  IMAGE ==> Image
**
 * Revision 1.7  1996/12/24  17:17:19  yawei
 * added "CVIPluminance.h"
 *
 * Revision 1.6  1996/12/24  16:45:52  yawei
 * Added linxform
 *
 * Revision 1.5  1996/12/24  15:41:54  yawei
 * Changed function names.
 *
 * Revision 1.4  1996/12/04  19:56:25  wli
 * change the type of dim from int to long.
 *
 * Revision 1.3  1996/07/22  16:29:00  akjoele
 * *** empty log message ***
 *
 * Revision 1.2  1996/02/29  14:46:28  akjoele
 * Made rgb2hsv and hsv2rgb prototype definitions so they can be accessed
 * from other modules.
 *
 * Revision 1.1  1994/10/30  22:43:06  hanceg
 * Initial revision
 *
 * Revision 1.1  1993/05/31  03:23:37  hanceg
 * Initial revision
 *
*
****************************************************************************/
#if !defined( CVIPCOLOR_DEFINED )

   #define CVIPCOLOR_DEFINED


   #include "CVIPmap.h"
   #include "ColorMap.h"
   #include "pct.h"
   #include "CVIPluminance.h"

#ifdef __cplusplus
extern "C"{
#endif 

   extern Image * cxform_dispatch(Image *srcImage, unsigned int choice,
		CVIP_BOOLEAN *remapg);
   extern Image * colorxform(const Image *rgbImage, COLOR_FORMAT newcspace,
		float *norm, float *refwhite, int dir);
	extern Image * pseudocol_freq(Image * grayImage, int inner, int outer,
		int blow, int bband, int bhigh);

   extern void rgb2hsv(float **vecP, unsigned long dim);
   extern void hsv2rgb(float **vecP, unsigned long dim);
   extern void rgb2yiq(Image *in, int inv);

	/* This function appears in the old CVIPcolor.h file, and may be used in old
	 * applications; keep it here for safety.
	 */
	extern void linxform(float **cvecP, unsigned int no_of_vecs,
		unsigned int vdim, double **transmatrix);
#ifdef __cplusplus
}
#endif 

#endif /* CVIPCOLOR_DEFINED */
