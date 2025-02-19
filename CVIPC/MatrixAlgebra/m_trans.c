/***************************************************************************
======================================================================
Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
======================================================================
                                                                      
             File Name: m_trans.c
           Description: contains libmatrix.a routine to transpose a matrix.
         Related Files: Makefile, CVIPmatrix.h
   Initial Coding Date: 1/24/93
           Portability: Standard (ANSI) C
             Credit(s): Gregory Hance, E.E. Dept. SIUE

  Global Function List: transpose_Matrix - transpose a Matrix

			
****************************************************************************

** Copyright (C) 1991, 1992, 1993 SIUE - by Scott Umbaugh, Greg Hance.
**
** Permission to use, copy, modify, and distribute this software and its
** documentation for any purpose and without fee is hereby granted, provided
** that the above copyright notice appear in all copies and that both that
** copyright notice and this permission notice appear in supporting
** documentation.  This software is provided "as is" without express or
** implied warranty.

RCS (Revision Control System) Information - Added automatically by RCS) 

$Author: achomai $                                                         
$Date: 1998/04/19 02:29:07 $                                                        
$Source: /home/cvip/cvipapps/CVIPtools3.7/MatrixAlgebra/RCS/m_trans.c,v $                                                         
$Header: /home/cvip/cvipapps/CVIPtools3.7/MatrixAlgebra/RCS/m_trans.c,v 1.4 1998/04/19 02:29:07 achomai Exp $

*****************************************************************************/

#include "stdlib.h"
#include "stdio.h"
#include "CVIPmatrix.h"

/****************************************************************
                  Name: transpose_Matrix
         Expanded Name: Matrix Transpose
            Parameters: <A> - pointer to Matrix structure
               Returns: pointer to new matrix structure of same type
			containing the transposed matrix
           Description: transposes the matrix <A> by copying to a new
			matrix. In case you didn't now that means
			interchange the rows w/ the columns.
           Diagnostics: (Nada)
             Credit(s): Greg Hance
			
			
****************************************************************/
Matrix	*transpose_Matrix(const Matrix	*A)
{
	Matrix	*At;
	short	**as,**ast;
	byte	**ab, **abt;
	int	**ai, **ait;
	float	**af,**aft;
	double	**ad,**adt;
	int	i,j;

/* allocate transposed output space of same type */
	At = new_Matrix(A->cols,A->rows, A->data_type, A->data_format);
	if(At == NULL)
	return(NULL);

	switch(A->data_type) {
		case CVIP_SHORT:
			as = (short **)(A->rptr);
			ast = (short **)(At->rptr);
			for(i = 0 ; i < A->rows ; i++)
				for(j = 0 ; j < A->cols ; j++)
				ast[j][i] = as[i][j];
			break;
		case CVIP_BYTE:
			ab = (byte **)(A->rptr);
			abt = (byte **)(At->rptr);
			for(i = 0 ; i < A->rows ; i++)
				for(j = 0 ; j < A->cols ; j++)
				abt[j][i] = ab[i][j];
			break;
		case CVIP_INTEGER:
			ai = (int **)(A->rptr);
			ait = (int **)(At->rptr);
			for(i = 0 ; i < A->rows ; i++)
				for(j = 0 ; j < A->cols ; j++)
				ait[j][i] = ai[i][j];
			break;
		case CVIP_FLOAT:
			af = (float **)(A->rptr);
			aft = (float **)(At->rptr);
			for(i = 0 ; i < A->rows ; i++)
				for(j = 0 ; j < A->cols ; j++)
				aft[j][i] = af[i][j];
			break;
		case CVIP_DOUBLE:
			ad = (double **)(A->rptr);
			adt = (double **)(At->rptr);
			for(i = 0 ; i < A->rows ; i++)
				for(j = 0 ; j < A->cols ; j++)
				adt[j][i] = ad[i][j];
	}
	if(A->data_format==COMPLEX) {
	switch(A->data_type) {
		case CVIP_SHORT:
			as = (short **)(A->iptr);
			ast = (short **)(At->iptr);
			for(i = 0 ; i < A->rows ; i++)
				for(j = 0 ; j < A->cols ; j++)
				ast[j][i] = as[i][j];
			break;
		case CVIP_BYTE:
			ab = (byte **)(A->iptr);
			abt = (byte **)(At->iptr);
			for(i = 0 ; i < A->rows ; i++)
				for(j = 0 ; j < A->cols ; j++)
				abt[j][i] = ab[i][j];
			break;
		case CVIP_INTEGER:
			ai = (int **)(A->iptr);
			ait = (int **)(At->iptr);
			for(i = 0 ; i < A->rows ; i++)
				for(j = 0 ; j < A->cols ; j++)
				ait[j][i] = ai[i][j];
			break;
		case CVIP_FLOAT:
			af = (float **)(A->iptr);
			aft = (float **)(At->iptr);
			for(i = 0 ; i < A->rows ; i++)
				for(j = 0 ; j < A->cols ; j++)
				aft[j][i] = af[i][j];
			break;
		case CVIP_DOUBLE:
			ad = (double **)(A->iptr);
			adt = (double **)(At->iptr);
			for(i = 0 ; i < A->rows ; i++)
				for(j = 0 ; j < A->cols ; j++)
				adt[j][i] = ad[i][j];
			break;
	}
	}
	return(At);
}
