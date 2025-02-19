/***************************************************************************
======================================================================
Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
======================================================================
                                                                      
             File Name: m_sqrt.c
           Description: contains libmatrix.a routine for computing the
			square root of a matrix.
         Related Files: Makefile, CVIPmatrix.h, rec2pol
   Initial Coding Date: 12/5/96
           Portability: Standard (ANSI) C
             Credit(s): Arve Kjoelen, E.E. Dept. SIUE

			
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
#include <stdio.h>
#include <math.h>
#include "CVIPmatrix.h"
#include "CVIPdef.h"


/****************************************************************
                  Name: sqrt_Matrix
         Expanded Name: Matrix Square Root
            Parameters: <a> - pointer to Matrix structure
               Returns: pointer to Matrix structure containing 
			matrix square root.
           Description: Computes the square root of the passed matrix.
			All data types less precise than CVIP_FLOAT are promoted.
			Complex datatypes are supported.
           Diagnostics: Frees up old matrix.
             Credit(s): Arve Kjoelen
			
			
****************************************************************/
Matrix *sqrt_Matrix(Matrix *a)
{
	Matrix	*b, *tmp;
	int	i,j;
	char	function_name[] = {"sqrt_Matrix"};

	if(a->data_type<=CVIP_FLOAT) {
		b=clone_Matrix(a, CVIP_FLOAT);
	}
	else if(a->data_type==CVIP_DOUBLE) {
		b=clone_Matrix(a, CVIP_DOUBLE);
	}
	if(b == NULL)
	{
		delete_Matrix(a);
		return(NULL);
	}
	(void)copy_Matrix(a,b);
	delete_Matrix(a);

	if(b->data_format==REAL) {
		for(i=0; i<b->rows; i++) {
		switch(b->data_type) {
		case CVIP_FLOAT:
			for(j=0; j<b->cols; j++)
			((float **)(b->rptr))[i][j]=
			(float)sqrt((double)((float **)(b->rptr))[i][j]);
			break;
		case CVIP_DOUBLE:
			for(j=0; j<b->cols; j++)
			((double **)(b->rptr))[i][j]=
			sqrt(((double **)(b->rptr))[i][j]);
			break;
		}
		}
	}
	else { /* data_format COMPLEX */
		a=duplicate_Matrix(b, REAL);
		if(a == NULL)
		{
			delete_Matrix(b);
			return(NULL);
		}
		tmp=a;
		a=mag_Matrix(a);
		delete_Matrix(tmp);
		if(a == NULL)
		{
			delete_Matrix(b);
			return(NULL);
		}
		b=rect2pol_Matrix(b,1);
		if(b == NULL)
		return(NULL);
		for(i=0; i<b->rows; i++) {
			for(j=0; j<b->cols; j++) {
			if(b->data_type==CVIP_FLOAT) {
			((float **)(b->rptr))[i][j]=
			(float)sqrt((double)((float **)(a->rptr))[i][j]);
			((float **)(b->iptr))[i][j]/=2.0;
			}
			else { /* CVIP_DOUBLE */
			for(j=0; j<b->cols; j++)
			((double **)(b->rptr))[i][j]=
			sqrt(((double **)(a->rptr))[i][j]);
			((double **)(b->iptr))[i][j]/=2.0;
			}
			}
		}
		delete_Matrix(a);
		b=rect2pol_Matrix(b,0);
	}
	return(b);
}

/****************************************************************
                  Name: cbrt_Matrix
         Expanded Name: Matrix Cube Root
            Parameters: <a> - pointer to Matrix structure
               Returns: pointer to Matrix structure containing 
			matrix cube root.
           Description: Computes the cube root of the passed matrix.
			All data types less precise than CVIP_FLOAT are promoted.
			Complex datatypes are supported.
           Diagnostics: Frees up old matrix.
             Credit(s): Arve Kjoelen
			
			
****************************************************************/
Matrix *cbrt_Matrix(Matrix *a)
{
	Matrix	*b, *tmp;
	int	i,j;
	char	function_name[] = {"sqrt_Matrix"};

	if(a->data_type<=CVIP_FLOAT) {
		b=clone_Matrix(a, CVIP_FLOAT);
		(void)copy_Matrix(a,b);
	}
	else if(a->data_type==CVIP_DOUBLE) {
		b=clone_Matrix(a, CVIP_DOUBLE);
		(void)copy_Matrix(a,b);
	}
	delete_Matrix(a);

	if(b->data_format==REAL) {
		for(i=0; i<b->rows; i++) {
		switch(b->data_type) {
		case CVIP_FLOAT:
			for(j=0; j<b->cols; j++)
			((float **)(b->rptr))[i][j]=
			(float)cbrt((double)((float **)(b->rptr))[i][j]);
			break;
		case CVIP_DOUBLE:
			for(j=0; j<b->cols; j++)
			((double **)(b->rptr))[i][j]=
			cbrt(((double **)(b->rptr))[i][j]);
			break;
		}
		}
	}
	else { /* data_format COMPLEX */
		a=duplicate_Matrix(b, REAL);
		if(a == NULL)
		{
			delete_Matrix(b);
			return(NULL);
		}
		tmp=a;
		a=mag_Matrix(a);
		delete_Matrix(tmp);
		if(a == NULL)
		{
			delete_Matrix(b);
			return(NULL);
		}
		b=rect2pol_Matrix(b,1);
		if(b == NULL)
		return(NULL);
		for(i=0; i<b->rows; i++) {
			for(j=0; j<b->cols; j++) {
			if(b->data_type==CVIP_FLOAT) {
				((float **)(b->rptr))[i][j]=
				(float)cbrt((double)((float **)(a->rptr))[i][j]);
				((float **)(b->iptr))[i][j]/=3.0;
			}
			else { /* CVIP_DOUBLE */
				for(j=0; j<b->cols; j++)
				((double **)(b->rptr))[i][j]=
				cbrt(((double **)(a->rptr))[i][j]);
				((double **)(b->iptr))[i][j]/=3.0;
			}
		}
		}
		delete_Matrix(a);
		b=rect2pol_Matrix(b,0);
	}
	return(b);
}
