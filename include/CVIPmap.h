/***************************************************************************
* ======================================================================
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* ======================================================================
*
*             File Name: CVIPmap.h
*           Description: contains function prototypes, type names, constants,
*			 etc. related to libmap (Data Mapping Toolkit.)
*         Related Files: Imakefile, normalize.c, relremap.c
*   Initial Coding Date: Mon Apr 12 15:56:34 CDT 1993
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
* $Log: CVIPmap.h,v $
 * Revision 1.6  1997/03/08  00:51:17  yawei
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
* Revision 1.5  1996/12/30 17:17:23  yawei
* added trun_Image
*
 * Revision 1.4  1996/12/20  19:20:18  yawei
 * changed logMap_Image function prototype.
 *
 * Revision 1.3  1996/06/11  12:14:19  kluo
 * check in
 *
 * Revision 1.2  1995/03/07  22:59:40  luok
 * change declaration type of condRemap_Image
 *
 * Revision 1.1  1994/10/30  22:43:06  hanceg
 * Initial revision
 *
 * Revision 1.1  1993/05/11  00:35:30  hanceg
 * Initial revision
 *
*
****************************************************************************/
#if !defined(CVIPMAP_DEFINED)

   #define CVIPMAP_DEFINED

   #include "CVIPmanager.h"
   #include "CVIPdef.h"
#ifdef __cplusplus
extern "C"{
#endif 


   #define remapp(a,b,c) remap_Image(a,b,0,c)
   #define linxform(a,b,c,d) linearTrans_Image(a,b,c,d)

   extern Image *remap_Image(const Image *mapP, CVIP_TYPE dtype, long dmin,
		long dmax);
   extern void linearTrans_Image(float **cvecP, unsigned int no_of_vecs,
		unsigned int vdim, double **transmatrix);
   extern Image *logMap_Image(Image *imgP, int band);
   extern Image *condRemap_Image(const Image *imgP, CVIP_TYPE dtype,
		unsigned min, unsigned max);
   extern Image * trun_Image(const Image *imageP, CVIP_TYPE dtype, long dmin,
		long dmax);
   extern Image *remap_Image_C(const Image 	*imageP, CVIP_TYPE 	dtype, long	dmin, long	dmax);
#ifdef __cplusplus
}
#endif 

#endif
