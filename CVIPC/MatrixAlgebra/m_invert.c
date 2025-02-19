/***************************************************************************
======================================================================
Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
======================================================================
                                                                      
             File Name: m_invert.c
           Description: contains routine for finding the inverse of
			a matrix.
         Related Files: Makefile, MATcopy.c, CVIPmatrix.h
   Initial Coding Date: 1/24/93
           Portability: Standard (ANSI) C
             Credit(s): Gregory Hance, E.E. Dept. SIUE

  Global Function List: invert_Matrix - invert a matrix
			
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
$Date: 1998/04/19 02:22:54 $                                                        
$Source: /home/cvip/cvipapps/CVIPtools3.7/MatrixAlgebra/RCS/m_invert.c,v $                                                         
$Header: /home/cvip/cvipapps/CVIPtools3.7/MatrixAlgebra/RCS/m_invert.c,v 1.3 1998/04/19 02:22:54 achomai Exp $

*****************************************************************************/
#include "stdlib.h"
#include "stdio.h"
#include "CVIPmatrix.h"
#include "CVIPcomplex.h"
#include "MATcopy.h"

/****************************************************************
                  Name: invert_Matrix
         Expanded Name: Matrix Invert
            Parameters: <A> - pointer to matrix to be inverted
               Returns: pointer to inverted matrix (promoted to type double)
           Description: finds the inverse of matrix <A> using Gauss-Jordan
			elimination with full pivoting (not your usual
			half pivot I guess... ) ALSO... this routine will
			find the inverse of a complex matrix.
           Diagnostics: returns NULL pointer and issues error message
			with singular matrices, bad Matrix structures
             Credit(s): Greg Hance (Added complex support)
			C Language Algorithms in DSP
			
			
****************************************************************/
Matrix	*invert_Matrix(const Matrix	*A)
{
	Matrix	*Ai;
	double	**a, **b;
    	double	big,pivot_inverse,pivot_r,pivot_i;
	double	temp,abs_element,r_mult,i_mult,temp_i;
	int	*pivot_flag,*swap_col,*swap_row;
	int	i,n,row,col,swap,irow,icol;
	const DF = A->data_format+1; /* DF(Data Format)=1 (REAL), 2 (COMPLEX)*/
	char	*FuncName = "invert_Matrix";

/* check for square matrix */
	if(A->rows != A->cols) {
		error_CVIP(FuncName,"Non-square, size = %dx%d\n",
			A->rows,A->cols);
		return NULL;
	}

/* check pointer */
	if(!A->rptr) {
		error_CVIP(FuncName,"No matrix for invert_Matrix\n");
		return NULL;
	}

/* size of square matrix */
	n = A->rows;

/* allocate space for the inverse */
	Ai = new_Matrix(n,n,CVIP_DOUBLE, A->data_format);
	if(Ai == NULL)
	return(NULL);

/* copy to double matrix */
	switch(A->data_type) {
		case CVIP_BYTE:
			COPY_MAT(A,Ai,n*DF,n,byte,double)
			break;
		case CVIP_SHORT:
			COPY_MAT(A,Ai,n*DF,n,short,double)
			break;
		case CVIP_INTEGER:
			COPY_MAT(A,Ai,n*DF,n,int,double)
			break;
		case CVIP_FLOAT:
			COPY_MAT(A,Ai,n*DF,n,float,double)
			break;
		case CVIP_DOUBLE:
			COPY_MAT(A,Ai,n*DF,n,double,double)
			break;
		default:
			error_CVIP(FuncName,"Unsupported type.\n");
			return NULL;
	}
           
	a = (double **)Ai->rptr;
	if(Ai->data_format == COMPLEX)
	b = (double **)Ai->iptr;;

/* allocate index arrays and set to zero */
	pivot_flag = (int *) calloc(n,sizeof(int));
	swap_row = (int *) calloc(n,sizeof(int));
	swap_col = (int *) calloc(n,sizeof(int));

	if(!pivot_flag || !swap_row || !swap_col) {
		error_CVIP(FuncName,"Memory allocation error.\n");
		if(pivot_flag != NULL)
		free(pivot_flag);

		if(swap_row != NULL)
		free(swap_row);

		if(swap_col != NULL)
		free(swap_col);

		delete_Matrix(Ai);
		return NULL;
	}

	for(i = 0 ; i < n ; i++) {   /* n iterations of pivoting */

/* find the biggest pivot element */
        big = 0.0;
        for(row = 0 ; row < n ; row++) {
            if(!pivot_flag[row]) {       /* only unused pivots */
                for(col = 0 ; col < n ; col++) {
                    if(!pivot_flag[col]) {
		        if(Ai->data_format==REAL)
                           abs_element = fabs(a[row][col]);
			else
			   abs_element = MAGSQ(a[row][col],b[row][col]);
                        if(abs_element >= big) {
                            big = abs_element;
                            irow = row;
                            icol = col;
                        }
                    }
                }
            }
        }
        pivot_flag[icol]++;    /* mark this pivot as used */

/* swap rows to make this diagonal the biggest absolute pivot */
        if(irow != icol) {
            for(col = 0 ; col < n ; col++) {
                temp = a[irow][col];
                a[irow][col] = a[icol][col];
                a[icol][col] = temp;
		if(Ai->data_format == COMPLEX) {
                   temp = b[irow][col];
                   b[irow][col] = b[icol][col];
                   b[icol][col] = temp;
                }
            }
       }

/* store what we swaped */
       swap_row[i] = irow;
       swap_col[i] = icol;

/* bad news if the pivot is zero */
       if(a[icol][icol] == 0.0) {
//           error_CVIP(FuncName,"SINGULAR Matrix.\n");

           free((char *)pivot_flag);
           free((char *)swap_row);
           free((char *)swap_col);
           delete_Matrix(Ai);
           return(NULL);
       }

/* divide the row by the pivot */
       if(Ai->data_format==REAL)
          pivot_inverse = 1.0/a[icol][icol];
       else {
          pivot_r = a[icol][icol]/MAGSQ(a[icol][icol],b[icol][icol]);
	  pivot_i = (-1)*b[icol][icol]/MAGSQ(a[icol][icol],b[icol][icol]);
       }
       a[icol][icol] = 1.0;        /* pivot = 1 to avoid round off */
       if(Ai->data_format == COMPLEX)
          b[icol][icol] = 0.0;
       for(col = 0 ; col < n ; col++)
           if(Ai->data_format == REAL)
              a[icol][col] = a[icol][col]*pivot_inverse;
	   else {
              CMUL(double,r_mult,i_mult,a[icol][col],b[icol][col],pivot_r,pivot_i);
              a[icol][col] = r_mult;
	      b[icol][col] = i_mult;
	 }

/* fix the other rows by subtracting */
       for(row = 0 ; row < n ; row++) {
           if(row != icol) {
               temp = a[row][icol];
	       a[row][icol] = 0.0;
	       if(Ai->data_format==COMPLEX) {
	          temp_i = b[row][icol];
		  b[row][icol] = 0.0;
               }
               for(col = 0 ; col < n ; col++)
	           if(Ai->data_format==REAL)
                      a[row][col] = a[row][col]-a[icol][col]*temp;
		   else {
		      CMUL(double,r_mult,i_mult,a[icol][col],b[icol][col],temp,temp_i);
		      a[row][col] -= r_mult;
		      b[row][col] -= i_mult;
		   } 	       
        }
    }
  }

/* fix the affect of all the swaps for final answer */
	for(swap = n-1 ; swap >= 0 ; swap--) {
	if(swap_row[swap] != swap_col[swap]) {
		for(row = 0 ; row < n ; row++) {
			temp = a[row][swap_row[swap]];
			a[row][swap_row[swap]] = a[row][swap_col[swap]];
			a[row][swap_col[swap]] = temp;
			if(Ai->data_format==COMPLEX) {
				temp = b[row][swap_row[swap]];
				b[row][swap_row[swap]] = b[row][swap_col[swap]];
				b[row][swap_col[swap]] = temp;
			}
		}
	}
	}

/* free up all the index arrays */
	free((char *)pivot_flag);
	free((char *)swap_row);
	free((char *)swap_col);

	return(Ai);
}
