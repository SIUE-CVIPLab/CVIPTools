/***************************************************************************
======================================================================
Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
======================================================================
                                                                      
             File Name: m_det.c
           Description: contains routine for finding the determinant
			of a matrix
         Related Files: Makefile, MATcopy.h, CVIPmatrix.h
   Initial Coding Date: 1/23/93
           Portability: Standard (ANSI) C
             Credit(s): Gregory Hance, E.E. Dept. SIUE

  Global Function List: det_Matrix - find the determinant of a matrix

			
****************************************************************************

** Copyright (C) 1991-1996 SIUE - by Scott Umbaugh, Greg Hance, Arve Kjoelen.
**
** Permission to use, copy, modify, and distribute this software and its
** documentation for any purpose and without fee is hereby granted, provided
** that the above copyright notice appear in all copies and that both that
** copyright notice and this permission notice appear in supporting
** documentation.  This software is provided "as is" without express or
** implied warranty.

RCS (Revision Control System) Information - Added automatically by RCS) 

$Author: achomai $                                                         
$Date: 1998/04/19 01:22:08 $                                                        
$Source: /home/cvip/cvipapps/CVIPtools3.7/MatrixAlgebra/RCS/m_det.c,v $                                                         
$Header: /home/cvip/cvipapps/CVIPtools3.7/MatrixAlgebra/RCS/m_det.c,v 1.6 1998/04/19 01:22:08 achomai Exp $

*****************************************************************************/

#include "stdlib.h"
#include "stdio.h"
#include "CVIPmatrix.h"
#include "MATcopy.h"

/****************************************************************
                  Name: det_Matrix
         Expanded Name: Matrix Determinant
            Parameters: <A> - pointer to Matrix structure
               Returns: double value equal to the determinant of the matrix
           Description: Finds the determinant of the input matrix. Allocates
			and frees a matrix for the determinant calculation. 
			Exits and prints error message on invalid Matrix 
			structure.
	   Diagnostics: returns 0 w/ corresponding error message when matrix
			is not square. Can not handle a complex matrix.
             Credit(s): Greg Hance
			C Language Algorithms in DSP
			Arve Kjoelen (name changes & ANSI C compat.)
			
****************************************************************/

double det_Matrix(const Matrix *A)
{
	Matrix	*Adet;
	double	**a;
	double	*a_ptr;
	double	det,big,pivot_inverse,temp,abs_element;
	int	n,row,col,swap_row,pivot;
	char	*FuncName = "det_Matrix";

	if(A->data_format==COMPLEX) {
		error_CVIP(FuncName,"Does not support COMPLEX matrices.\n");
		return 0;
	}

	if(A->rows != A->cols) {
		error_CVIP(	FuncName,"Non-square, size = %dx%d",
				A->rows,A->cols);
		return 0;
	}

/* check pointer */
	if(!A->rptr) {
		error_CVIP(FuncName,"No matrix for det_Matrix\n");
		return 0;
	}

/* size of square matrix */
	n = A->rows;

/* allocate space for the determinant calculation matrix */
	Adet = new_Matrix(n,n,CVIP_DOUBLE, REAL);
	if(Adet == NULL)
	return(0);

/* copy to double matrix for calculations */
	switch(A->data_type) {
		case CVIP_BYTE:
			COPY_MAT(A,Adet,n,n,byte,double)
			break;
		case CVIP_SHORT:
			COPY_MAT(A,Adet,n,n,short,double)
			break;
		case CVIP_INTEGER:
			COPY_MAT(A,Adet,n,n,int,double)
			break;
		case CVIP_FLOAT:
			COPY_MAT(A,Adet,n,n,float,double)
			break;
		case CVIP_DOUBLE:
			COPY_MAT(A,Adet,n,n,double,double)
			break;
		default:
			error_CVIP(FuncName,"Unsupported data type.\n");
			delete_Matrix(Adet);
			return 0;
	}

	a = (double **)Adet->rptr;

/* initialize the answer */
	det = 1.0;

	for(pivot = 0 ; pivot < n-1 ; pivot++) {

/* find the biggest absolute pivot */
	big = fabs(a[pivot][pivot]);
	swap_row = 0;               /* initialize for no swap */
	for(row = pivot + 1; row < n ; row++) {
		abs_element = fabs(a[row][pivot]);
		if(abs_element > big) {
			swap_row = row;
			big = abs_element;
		}
	}

/* unless swap_row is still zero we must swap two rows */
	if(swap_row != 0) {
		a_ptr = a[pivot];
		a[pivot] = a[swap_row];
		a[swap_row] = a_ptr;
/* change the sign of determinant because of swap */
		det = -det*a[pivot][pivot];
	}
        else{
/* calculate the determinant by the product of the pivots */
		det = det*a[pivot][pivot];
	}

/* if almost singular matrix, give up now */
	if(fabs(det) < 1.0e-50) return(det);

	pivot_inverse = 1.0/a[pivot][pivot];
	for(col = pivot + 1 ; col < n ; col++) {
		a[pivot][col] = a[pivot][col]*pivot_inverse;
	}

	for(row = pivot + 1 ; row < n ; row++) {
		temp = a[row][pivot];
		for(col = pivot + 1 ; col < n ; col++) {
			a[row][col] = a[row][col] - a[pivot][col]*temp;
		}
	}
	}

/* last pivot, no reduction required */
	det = det*a[n-1][n-1];

/* free up the calculation matrix */
	delete_Matrix(Adet);

	return(det);
}
