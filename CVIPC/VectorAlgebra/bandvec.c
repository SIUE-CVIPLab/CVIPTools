/***************************************************************************
* ======================================================================
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* ======================================================================
*
*             File Name: bandvec.c
*           Description: contains vector manipulation routines
*         Related Files: Imakefile, libband.a
*   Initial Coding Date: Mon Apr 12 14:35:23 CDT 1993
*           Portability: Standard (ANSI) C
*             Credit(s): Gregory Hance
*                        Southern Illinois University @ Edwardsville
*
*  Global Function List: band2pixel_Vector(...) - band vector to pixel vector
*			 pixel2band_Vector(...) - pixel vector to band vector
*			 copy_Vector(...) - copy vector A to vector B
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
* $Log: bandvec.c,v $
* Revision 1.3  1997/03/08 01:02:32  yawei
* Name Changes:
* 	BOOLEAN ==> CVIP_BOOLEAN
* 	FALSE ==> CVIP_NO
* 	TRUE ==> CVIP_YES
* 	BYTE ==> CVIP_BYTE
* 	SHORT ==> CVIP_SHORT
* 	INTEGER ==> CVIP_INTEGER
* 	FLOAT ==> CVIP_FLOAT
* 	DOUBLE ==> CVIP_DOUBLE
* 	TYPE ==> CVIP_TYPE
*
* Revision 1.2  1996/08/19 12:26:39  akjoele
* *** empty log message ***
*
 * Revision 1.1  1994/10/30  17:59:04  hanceg
 * CVIPtools1.0 source file - G. Hance
 *
 * Revision 1.1  1993/05/03  05:53:16  hanceg
 * Initial revision
 *
*
*
****************************************************************************/
#include "CVIPtools.h"
#include "CVIPdef.h"
#include "limits.h"
#include "float.h"

/****************************************************************
                   Name: band2pixel_Vector
          Expanded Name: Band Vector to Pixel Vector
             Parameters: <bandP> - pointer to array of band vectors
			 <no_of_bands> - number of spectral bands in image
			 (number of band vectors)
			 <imgsize> - size of image (length of each band vector)
                Returns: pointer to array pixel vectors
            Description: converts a band vector array to a pixel
			 vector array
	    Diagnostics: none
              Credit(s): Gregory Hance
		         Southern Illinois University @ Edwardsville
****************************************************************/

byte **band2pixel_Vector(byte **bandP, unsigned int no_of_bands, unsigned int imgsize)
{
   register int i = 0, j;
   byte *pvP;
   byte **pixP;

   pixP = (byte **) malloc(imgsize*sizeof(byte *));
  *pixP = (byte *)  malloc(no_of_bands*imgsize*sizeof(byte));

   for(pvP = *pixP; i < imgsize; i++) {
      pixP[i] = pvP;
      for(j=0; j < no_of_bands; j++, pvP++)
         *pvP = *(bandP[j]+i);
   }
return pixP;
}

/****************************************************************
                   Name: pixel2band_Vector
          Expanded Name: Pixel Vector to Band Vector
             Parameters: <bandP> - pointer to array of pixel vectors
			 <no_of_bands> - number spectral bands in image
			 (length of each pixel vector)
			 <imgsize> - size of image (number of pixel vectors)
                Returns: pointer to array pixel vectors
            Description: converts a pixel vector array to a band
			 vector array
	    Diagnostics: none
              Credit(s): Gregory Hance
		         Southern Illinois University @ Edwardsville
****************************************************************/

byte **pixel2band_Vector(byte **pixP, unsigned int no_of_bands, unsigned int imgsize)
{
   register int i = 0, j;
   byte *bvP;
   byte **bandP;

   bandP = (byte **) malloc(no_of_bands*sizeof(byte *));
  *bandP = (byte *)  malloc(no_of_bands*imgsize*sizeof(byte));

   for(bvP = *bandP; i < no_of_bands; i++) {
      bandP[i] = bvP;
      for(j=0; j < imgsize; j++, bvP++)
         *bvP = *(pixP[j]+i);
   }
return bandP;
}




#define COPY_VEC(a,b,vdim,typea,typeb,dta,dtb,amin,amax) { \
                 register const typea *_PTA = (const typea *)a; \
                 register typeb *_PTB = (typeb *)b; \
		 register int _IAB; \
		 for(_IAB = 0 ; _IAB < vdim ; _IAB++, _PTA++, _PTB++) { \
		    if(dtb < CVIP_FLOAT) \
		       *_PTB = (typeb) ROUND(*_PTA); \
		    else \
		       *_PTB = (typeb)(*_PTA); \
		    if(dtb < dta) \
		       *_PTB = CLAMP(*_PTB, amin, amax); \
		} \
	}

/****************************************************************
                   Name: copy_Vector
          Expanded Name: Copy Vector
             Parameters: <avecP> - pointer to vector A
			 <bvecP> - pointer to vector B
			 <vdim> - dimension of each vector
			 <atype> - type of data pointed to by vector A
			 <btype> - type of data pointed to by vector B
                Returns: nada
            Description: copies the contents of vector A into vector B.
			 Handles all 25 different type combinations of
			 A and B. NOTE: this function simply copies one
			 vector into another; therefore copying a vector of
			 a more precise type to that of a less precise
			 type will work properly but may result in garbage
			 if the range of A is not inclusive of that of B.
	    Diagnostics: none
              Credit(s): Gregory Hance
		         Southern Illinois University @ Edwardsville
****************************************************************/

void copy_Vector(void *avecP, void *bvecP, unsigned int vdim, 
             CVIP_TYPE atype, CVIP_TYPE btype)
{

    /* do the 25 type cases of A and B with 2 nested switch statements */

    switch(atype) {
        case CVIP_BYTE:
            switch(btype) {
                case CVIP_BYTE:    /*  A byte, B byte */
                    (void) memcpy(bvecP,avecP, (size_t) sizeof(byte)*vdim);
                    break;
                case CVIP_SHORT:    /*  A byte, B short */
                    COPY_VEC(avecP,bvecP,vdim,byte,short,atype,btype, SHRT_MIN, SHRT_MAX)
                    break;
                case CVIP_INTEGER:    /*  A byte, B int */
                    COPY_VEC(avecP,bvecP,vdim,byte,int,atype,btype, INT_MIN, INT_MAX)
                    break;
                case CVIP_FLOAT:    /* A byte, B float */
                    COPY_VEC(avecP,bvecP,vdim,byte,float,atype,btype, FLT_MIN, FLT_MAX)
                    break;
                case CVIP_DOUBLE:    /*  A byte, B double */
                    COPY_VEC(avecP,bvecP,vdim,byte,double,atype,btype, DBL_MIN, DBL_MAX)
            }
            break;
        case CVIP_SHORT:
            switch(btype) {
                case CVIP_BYTE:    /*  A short, B byte */
                    COPY_VEC(avecP,bvecP,vdim,short,byte,atype,btype, 0, UCHAR_MAX)
                    break;
                case CVIP_SHORT:    /*  A short, B short */
                    (void) memcpy(bvecP, avecP, (size_t) sizeof(short)*vdim);
                    break;
                case CVIP_INTEGER:    /*  A short, B int */
                    COPY_VEC(avecP,bvecP,vdim,short,int,atype,btype, INT_MIN, INT_MAX)
                    break;
                case CVIP_FLOAT:    /*  A short, B float */
                    COPY_VEC(avecP,bvecP,vdim,short,float,atype,btype, FLT_MIN, FLT_MAX)
                    break;
                case CVIP_DOUBLE:    /*  A short, B double */
                    COPY_VEC(avecP,bvecP,vdim,short,double,atype,btype, DBL_MIN, DBL_MAX)
            }
            break;
        case CVIP_INTEGER:
            switch(btype) {
                case CVIP_BYTE:    /*  A int, B byte */
                    COPY_VEC(avecP,bvecP,vdim,int,byte,atype,btype, 0, UCHAR_MAX)
                    break;
                case CVIP_SHORT:    /*  A int, B short */
                    COPY_VEC(avecP,bvecP,vdim,int,short,atype,btype, SHRT_MIN, SHRT_MAX)
                    break;
                case CVIP_INTEGER:    /*  A int, B int */
                    (void) memcpy(bvecP, avecP, (size_t) sizeof(int)*vdim);
                    break;
                case CVIP_FLOAT:    /*  A int, B float */
                    COPY_VEC(avecP,bvecP,vdim,int,float,atype,btype, FLT_MIN, FLT_MAX)
                    break;
                case CVIP_DOUBLE:    /*  A int, B double */
                    COPY_VEC(avecP,bvecP,vdim,int,double,atype,btype, DBL_MIN, DBL_MAX)
            }
            break;
        case CVIP_FLOAT:
            switch(btype) {
                case CVIP_BYTE:    /*  A float, B byte */
                    COPY_VEC(avecP,bvecP,vdim,float,byte,atype,btype, 0, UCHAR_MAX)
                    break;
                case CVIP_SHORT:    /*  A float, B short */
                    COPY_VEC(avecP,bvecP,vdim,float,short,atype,btype, SHRT_MIN, SHRT_MAX)
                    break;
                case CVIP_INTEGER:    /*  A float, B int */
                    COPY_VEC(avecP,bvecP,vdim,float,int,atype,btype, INT_MIN, INT_MAX)
                    break;
                case CVIP_FLOAT:    /*  A float, B float */
                    (void) memcpy(bvecP, avecP, (size_t) sizeof(float)*vdim);
                    break;
                case CVIP_DOUBLE:    /*  A float, B double */
                    COPY_VEC(avecP,bvecP,vdim,float,double,atype,btype, DBL_MIN, DBL_MAX)
            }
            break;
        case CVIP_DOUBLE:
            switch(btype) {
                case CVIP_BYTE:    /*  A double, B byte */
                    COPY_VEC(avecP,bvecP,vdim,double,byte,atype,btype, 0, UCHAR_MAX)
                    break;
                case CVIP_SHORT:    /*  A double, B short */
                    COPY_VEC(avecP,bvecP,vdim,double,short,atype,btype, SHRT_MIN, SHRT_MAX)
                    break;
                case CVIP_INTEGER:   /*  A double, B int */
                    COPY_VEC(avecP,bvecP,vdim,double,int,atype,btype, INT_MIN, INT_MAX)
                    break;
                case CVIP_FLOAT:    /*  A double, B float */
                    COPY_VEC(avecP,bvecP,vdim,double,float,atype,btype, FLT_MIN, FLT_MAX)
                    break;
                case CVIP_DOUBLE:    /*  A double, B double */
                    (void) memcpy(bvecP, avecP, (size_t) sizeof(double)*vdim);
            }
            break;
    }

} /* End of function - copy_Vector(...) */


