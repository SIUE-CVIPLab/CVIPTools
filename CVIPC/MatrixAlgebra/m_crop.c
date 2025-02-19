/***************************************************************************
======================================================================
Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
======================================================================
                                                                      
             File Name: m_crop.c
           Description: contains a function creating a sub-matrix
			from the original
         Related Files: Makefile, CVIPmatrix.h, MATscale.h
   Initial Coding Date: 1/23/93
           Portability: Standard (ANSI) C
             Credit(s): Gregory Hance, E.E. Dept. SIUE

  Global Function List: crop_Matrix - crop a matrix

			
****************************************************************************

** Copyright (C) 1991-1996 SIUE - by Scott Umbaugh, Greg Hance, Arve Kjoelen.
**
** Permission to use, copy, modify, and distribute this software and its
** documentation for any purpose and without fee is hereby granted, provided
** that the above copyright notice appear in all copies and that both that
** copyright notice and this permission notice appear in supporting
** documentation.  This software is provided "as is" without express or
** implied warranty.

*****************************************************************************/

#include "stdlib.h"
#include "stdio.h"
#include "CVIPmatrix.h"
#include "MATscale.h"

/****************************************************************
                  Name: crop_Matrix
         Expanded Name: Matrix Crop
            Parameters: <a> - pointer to source matrix
			<row_offset> - offset of row from 0
			<col_offset> - offset of column from 0
			<rows> - number of rows
			<cols> - number of columns
               Returns: Returns the new smaller matrix as a pointer to
			a new Matrix structure using the row and col offsets
			and number of <rows> and <cols> in the result matrix.
           Description: forms a sub-matrix of given size and location from
			original
	   Diagnostics: returns NULL ptr. w/ error msg. when submatrix
			size exceeds that of parent matrix
             Credit(s): Greg Hance
			C Language Algorithms in DSP
			Arve Kjoelen (ANSI C)
			
			
****************************************************************/

Matrix	*crop_Matrix(	const Matrix	*a,
			unsigned int	row_offset,
			unsigned int	col_offset,
			unsigned int	rows,
			unsigned int	cols)
{
	Matrix	*b;
	char	*FuncName = "crop_Matrix";

/* check the row and col variables */
	if((rows + row_offset) > a->rows || (cols + col_offset) > a->cols) {
		error_CVIP(FuncName,"sub-matrix exceeds matrix size\n");
		return NULL;
	}

/* allocate the output sub-matrix */
	b = new_Matrix(rows,cols,a->data_type, a->data_format);
	if(b == NULL)
	return(NULL);
/* do the different type cases with a switch statement */
	switch(a->data_type) {
		case CVIP_SHORT:
			SCALE_MAT(a,b,1,rows,cols,row_offset,col_offset,short,short)
			break;
		case CVIP_BYTE:
			SCALE_MAT(a,b,1,rows,cols,row_offset,col_offset,byte,byte)
			break;
		case CVIP_INTEGER:
			SCALE_MAT(a,b,1,rows,cols,row_offset,col_offset,int,int)
			break;
		case CVIP_FLOAT:
			SCALE_MAT(a,b,1,rows,cols,row_offset,col_offset,float,float)
			break;
		case CVIP_DOUBLE:
			SCALE_MAT(a,b,1,rows,cols,row_offset,col_offset,double,double)
	}
	return(b);
}
