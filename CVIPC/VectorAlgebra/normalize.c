/***************************************************************************
* ======================================================================
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* ======================================================================
*
*             File Name: normalize.c
*           Description: Data Mapping routine for normalizing a vector
*         Related Files: Imakefile, CVIPmap.h
*   Initial Coding Date: Mon Apr 12 14:27:30 CDT 1993
*           Portability: Standard (ANSI) C
*             Credit(s): Gregory Hance
*                        Southern Illinois University @ Edwardsville
*
*  Global Function List: normalize_Vector - normalize a vector
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
* $Log: normalize.c,v $
* Revision 1.2  1997/03/08 01:02:38  yawei
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
* Revision 1.1  1994/10/30 17:59:05  hanceg
* CVIPtools1.0 source file - G. Hance
*
 * Revision 1.1  1993/05/11  00:35:17  hanceg
 * Initial revision
 *
*
****************************************************************************/
#include "CVIPtoolkit.h"


/****************************************************************
                   Name: normalize_Vector
          Expanded Name: normalize vector
             Parameters: <srcvecP> - pointer to array of vectors
			 <normP> - normalization vector
			 <vecdtype> - valid CVIPtools data type of vector
			 <no_of_vecs> - number of vectors
                Returns: pointer to a normalized array of vectors.
            Description: This function will normalize an array of vectors
			 with respect to the normalization vector <normP>.
			 (i.e. srcvecP[0]([0],[1],...,[vdim-1])/normP[0], 
			 srcvecP[1]([0],[1],...,[vdim-1])/normP[1].
			 If the data type of the vectors is less precise than
			 "float" or equal to "float" then the result will be
			 type "float". If the arrays are of type "double"
			 then the result will be an array of normalized vectors
			 of type "double".
	    Diagnostics: none
              Credit(s): Gregory Hance
		         Southern Illinois University @ Edwardsville
****************************************************************/

void *normalize_Vector(void *srcvecP, float *normP, CVIP_TYPE vecdtype,
                unsigned int no_of_vecs, unsigned int vdim)
{
register unsigned int i=0, j;
void **nvecP, **vecP;
register byte *bP;
register short *sP;
register int *iP;
register float *fP, *vfP;
register double *dP, *vdP;
 
vecP = (void **) srcvecP;

if(vecdtype < CVIP_FLOAT) nvecP = allocMatrix_CVIP(no_of_vecs, vdim, sizeof(float));
else nvecP = vecP;

	
for(; i < no_of_vecs; i++, normP++) {
   
   switch(vecdtype) {
      case CVIP_BYTE :
         bP = (byte *) vecP[i];
         vfP = (float *) nvecP[i];
         for(j=0; j < vdim; j++, bP++, vfP++)
            *vfP = (float) *bP / *normP;
		
      break;
      case CVIP_SHORT :
         sP = (short *) vecP[i];
         vfP = (float *) nvecP[i];
         for(j=0; j < vdim; j++, sP++, vfP++)
            *vfP = *sP / *normP;
		
      break;
      case CVIP_INTEGER :
         iP = (int *) vecP[i];
         vfP = (float *) nvecP[i];
         for(j=0; j < vdim; j++, iP++, vfP++)
            *vfP = *iP / *normP;
		 
      break;
      case CVIP_FLOAT :
         fP = (float *) vecP[i];
         vfP = (float *) nvecP[i];
         for(j=0; j < vdim; j++, fP++, vfP++)
            *vfP = *fP / *normP;
		  
      break;
      case CVIP_DOUBLE :
         dP = (double *) vecP[i];
         vdP = (double *) nvecP[i];
         for(j=0; j < vdim; j++, dP++, vdP++)
            *vdP = *dP / *normP;
		 
      break;
   }
}

return nvecP;

} /* End of function vecnorm(...) */
 

#define fabsVector(a, ctype, size) { \
	register ctype	*_AP = (ctype *) (a); \
	register int	_IX; \
	for(_IX=0; _IX < size; _IX++, _AP++) \
		*_AP = (ctype) fabs((double) *_AP); \
} \

int
absVector(
	void		*vecP,
	CVIP_TYPE		type,
	unsigned	size
)
{


	switch(type) {
		case CVIP_BYTE :
			fabsVector(vecP, byte, size)
			break;
		case CVIP_SHORT:
			fabsVector(vecP, short, size)
			break;
		case CVIP_INTEGER :
			fabsVector(vecP, int, size)
			break;
		case CVIP_FLOAT :
			fabsVector(vecP, float, size)
			break;
		case CVIP_DOUBLE :
			fabsVector(vecP, double, size)
			break;
		default:
			error_CVIP("absVector", "unknown data type!");
			return 0;
	}

	return 1;
}

#define printVec(a, ctype, size, format, fileP) {\
	register ctype	*_AP = (ctype *) (a); \
	register int	_IX; \
	for(_IX=0; _IX < size; _IX++, _AP++) \
		fprintf(fileP, "vec[%d] = " #format "\n", _IX, *_AP); \
} \


int
printVector(
	void		*vecP,
	CVIP_TYPE		type,
	unsigned	size,
	FILE		*fileP
)
{

	switch(type) {
		case CVIP_BYTE :
			printVec(vecP, byte, size, %d, fileP)
			break;
		case CVIP_SHORT:
			printVec(vecP, short, size, %hd, fileP)
			break;
		case CVIP_INTEGER :
			printVec(vecP, int, size, %d, fileP)
			break;
		case CVIP_FLOAT :
			printVec(vecP, float, size, %f, fileP)
			break;
		case CVIP_DOUBLE :
			printVec(vecP, double, size, %f, fileP)
			break;
		default:
			error_CVIP("absVector", "unknown data type!");
			return 0;
	}

	return 1;
}
