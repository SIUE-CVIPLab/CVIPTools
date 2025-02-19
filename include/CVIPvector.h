/***************************************************************************
* ======================================================================
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* ======================================================================
*
*             File Name: CVIPvector.h
*           Description: Contains function prototypes, type names, etc. for
*			 vector library routines.
*         Related Files: VectorMinMax.c, bandvec.c, tvector.c
*   Initial Coding Date: Sun Aug 29 18:54:08 CDT 1993
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
** $Log: CVIPvector.h,v $
 * Revision 1.2  1997/03/08  00:47:16  yawei
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
** Revision 1.1  1994/10/30 22:43:06  hanceg
** Initial revision
**
*
****************************************************************************/
#if !defined(CVIPVECTOR_DEFINED)

   #define CVIPVECTOR_DEFINED

   #include "CVIPparse.h"
   #include "subSample.h"
   #include "findHisto.h"
   #include "filterVector.h"

#define copymat(amatP,bmatP,rows,cols,atype,btype) \
        copyvec(*(amatP),*(bmatP),(rows)*(cols),atype,btype)

#define banvec2pixvec(a,b,c) band2pixel_Vector(a,b,c)
#define pixvec2banvec(a,b,c) pixel2band_Vector(a,b,c)
#define copyvec(a,b,c,d,e) copy_Vector(a,b,c,d,e)
#define vecnorm(a,b,c,d,e) normalize_Vector(a,b,c,d,e)

#ifdef __cplusplus
extern "C"{
#endif 


extern byte **band2pixel_Vector(byte **bandP, unsigned int no_of_bands, unsigned int imgsize);
extern byte **pixel2band_Vector(byte **pixP, unsigned int no_of_bands, unsigned int imgsize);
extern void copy_Vector(void *avecP, void *bvecP, unsigned int vdim, CVIP_TYPE atype, CVIP_TYPE btype);
extern void *normalize_Vector(void *srcvecP, float *normP, CVIP_TYPE vecdtype, unsigned int no_of_vecs, unsigned int vdim);

double findMinVal_Vector(void *a, unsigned length, CVIP_TYPE data_type);
double findMaxVal_Vector(void *a, unsigned length, CVIP_TYPE data_type);

#ifdef __cplusplus
}
#endif 

#endif /* CVIPVECTOR_DEFINED */

