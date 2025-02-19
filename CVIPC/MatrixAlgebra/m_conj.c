/***************************************************************************
======================================================================
Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
======================================================================
                                                                      
             File Name: m_conj.c
           Description: contains function to compute the conjugate of a matrix.
          Related Files: Makefile, MATcopy.h, CVIPmatrix.h
   Initial Coding Date: 7/26/96
           Portability: Standard (ANSI) C
             Credit(s): Arve Kjoelen, E.E. Dept. SIUE

 Global Function List:  conj_matrix()
			
****************************************************************************

** Copyright (C) 1996 SIUE - by Scott Umbaugh, Arve Kjoelen.
**
** Permission to use, copy, modify, and distribute this software and its
** documentation for any purpose and without fee is hereby granted, provided
** that the above copyright notice appear in all copies and that both that
** copyright notice and this permission notice appear in supporting
** documentation.  This software is provided "as is" without express or
** implied warranty.
*****************************************************************************/
#include <stdlib.h>
#include "CVIPtyp.h"
#include "CVIPmatrix.h"

/****************************************************************
                  Name: conj_Matrix
            Parameters: <A> - pointer to source matrix
               Returns: 1 if successful, 0 otherwise.
           Description: Calculate the complex conjugate of a matrix.
	   Diagnostics: - If passed matrix is real, nothing happens.
			- All data types (CVIP_BYTE, CVIP_SHORT, CVIP_INTEGER, CVIP_FLOAT, CVIP_DOUBLE)
			  are supported.
			- The original data is NOT kept.  rationale:  If
			  you're messing with complex matrices and image
			  processing, you're probably doing FFT's, with CVIP_FLOAT
			  data types and large matrices.  Not creating a copy
			  of the passed matrix saves  lots of time and space.
			  If you want to keep the original, call 
			  duplicate_Matrix before calling this!
             Credit(s): Arve Kjoelen
						
****************************************************************/
CVIP_BOOLEAN 
conj_Matrix(
    	Matrix 	*A
)
{
	unsigned	r,c; /* # of rows and columns in matrix */
        unsigned	i,j; /* counter variables */
	CVIP_TYPE	t;
	char		*FuncName = "conj_Matrix";
	
	if(!A)
	{
		error_CVIP(FuncName,"NULL pointer passed.\n");
		return(CVIP_NO);
	}
	if(getDataFormat_Matrix(A)==REAL) return(CVIP_NO);

	t=getDataType_Matrix(A);
	r=getNoOfRows_Matrix(A);
	c=getNoOfCols_Matrix(A);

	for(i=0; i<r; i++) {
		switch(t) {
		case CVIP_BYTE:
			for(j=0; j<c; j++)
			((byte *)A->iptr[i])[j]=-((byte *)A->iptr[i])[j];
			break;
		case CVIP_SHORT:
			for(j=0; j<c; j++)
			((short *)A->iptr[i])[j]=-((short *)A->iptr[i])[j];
			break;
		case CVIP_INTEGER:
			for(j=0; j<c; j++)
			((int *)A->iptr[i])[j]=-((int *)A->iptr[i])[j];
			break;
		case CVIP_FLOAT:
			for(j=0; j<c; j++)
			((float *)A->iptr[i])[j]=-((float *)A->iptr[i])[j];
			break;
		case CVIP_DOUBLE:
			for(j=0; j<c; j++)
			((double *)A->iptr[i])[j]=-((double *)A->iptr[i])[j];
			break;
		default:
			error_CVIP(FuncName,"Invalid data type.\n");
			return(CVIP_NO);
		}
	}
	return(CVIP_YES);
}
