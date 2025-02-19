/***************************************************************************
======================================================================
Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
======================================================================
                                                                      
             File Name: rec2pol.c
           Description: contains libmatrix.a routine for converting
			from rectangular to polar coordinates
         Related Files: Makefile, CVIPmatrix.h, CVIPcomplex.h
   Initial Coding Date: 1/24/92
           Portability: Standard (ANSI) C
             Credit(s): Gregory Hance, E.E. Dept. SIUE

  Global Function List: rec2pol - rectangular to polar coordinates
   Local Function List: cdiv, dcdiv - not used currently

			
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
$Date: 1998/04/19 03:02:23 $                                                        
$Source: /home/cvip/cvipapps/CVIPtools3.7/MatrixAlgebra/RCS/rec2pol.c,v $                                                         
$Header: /home/cvip/cvipapps/CVIPtools3.7/MatrixAlgebra/RCS/rec2pol.c,v 1.5 1998/04/19 03:02:23 achomai Exp $

*****************************************************************************/

#include <math.h>      /* header files */
#include <stdlib.h>
#include <stdio.h>
#include "CVIPmatrix.h"
#include "CVIPcomplex.h"

static void cdiv(float *r3,float *i3,float r1,float i1,float r2,float i2);
static void dcdiv(double *r3,double *i3,double r1,double i1,double r2,double i2);


/****************************************************************
                  Name: rec2pol
         Expanded Name: Rectangular to Polar
            Parameters: <A> - pointer to Matrix structure
			<dir> - type of transformation
		           (1) - rectangular to polar
			   (anything else) - polar to rectangular
               Returns: pointer to Matrix structure containing the
			desired transformation (type float or double)
           Description: Performs transformation from rectangular to
			polar coordinates or from polar to rectangular
			coordinates depending upon the value of <dir>.
			Values less than type CVIP_FLOAT are promoted. If
			a matrix of type double is passed the result will
			be double.
           Diagnostics: returns with NULL pointer and message when...
				- matrix is not complex
		        also informs user when a promotion takes place.
             Credit(s): Greg Hance
			
			
****************************************************************/

Matrix	*rect2pol_Matrix(Matrix *A,int dir)
{
	float		fmag, fphase, xf, yf;
	double		dmag, dphase, xd, yd;
	register float	*rfP, *ifP;
	register double	*rdP, *idP;
	register int	i;
	Matrix		*B;
	short free_matrix = CVIP_NO;
	char		*fn = "rect2pol_Matrix";
   
	if(A->data_format == REAL) {
		error_CVIP(fn,"Matrix structure must be complex.\n");
		error_CVIP(fn,"Try calling makeComplex_Matrix() first.\n");
		delete_Matrix(A);
		return(NULL);
	}

	if(A->data_type < CVIP_FLOAT) {
		B = (Matrix *) new_Matrix(A->rows,A->cols,CVIP_FLOAT,COMPLEX);
		if(B == NULL)
		{
			delete_Matrix(A);
			return(NULL);
		}
		msg_CVIP(fn,"Casting resultant Matrix to floating pt. complex.\n");
		copy_Matrix(A, B);
		free_matrix = CVIP_YES;
	}
	else
	B = A;
       
	if(B->data_type == CVIP_FLOAT) {
		rfP = *((float **) B->rptr);
		ifP = *((float **) B->iptr);
	}
	else {
		rdP = *((double **) B->rptr);
		idP = *((double **) B->iptr);
	}    

	if(dir == 1) {
		for(i=0; i < B->rows*B->cols; i++) 
		if(B->data_type==CVIP_FLOAT) {
			REC2POL(float, fmag, fphase, *rfP, *ifP);
			*rfP++ = fmag;
			*ifP++ = fphase;
		}
		else {
			REC2POL(double, dmag, dphase, *rdP, *idP);
			*rdP++ = dmag;
			*idP++ = dphase;
		}
	}
	else {  
		for(i=0; i < B->rows*B->cols; i++) 
		if(A->data_type==CVIP_FLOAT) {
			POL2REC(float, xf, yf, *rfP, *ifP);
			*rfP++ = xf;
			*ifP++ = yf;
		}
		else {
			POL2REC(double, xd, yd, *rdP, *idP);
			*rdP++ = xd;
			*idP++ = yd;
		}
	}

	if(free_matrix)
	delete_Matrix(A);

	return B;
}



/****************************************************************
                  Name: cdiv
         Expanded Name: Complex Divide
            Parameters: r3 - pointer to real component of result
			i3 - pointer to complex component of result
			r1 - real component of data object 1
			i1 - imaginary component of data object 1
			r2 - real component of data object 2
			i2 - imaginary component of data object 2
               Returns: (Nada)
           Description: performs float complex quotient from
			(r1,i1)/(r2,i2) and put the result in (r3,i3)
           Diagnostics: (Nada)
             Credit(s): Greg Hance
			
			
****************************************************************/
static void cdiv(float *r3,float *i3,float r1,float i1,float r2,float i2)
{

	float f;

	f = r2*r2+i2*i2;
	*r3 = (r1*r2+i1*i2)/f;
	*i3 = (i1*r2-r1*i2)/f;
}


/****************************************************************
                  Name: dcdiv
         Expanded Name: Double Complex Divide
            Parameters: r3 - pointer to real component of result
			i3 - pointer to complex component of result
			r1 - real component of data object 1
			i1 - imaginary component of data object 1
			r2 - real component of data object 2
			i2 - imaginary component of data object 2
               Returns: (Nada)
           Description: performs double complex quotient from
			(r1,i1)/(r2,i2) and put the result in (r3,i3)
           Diagnostics: (Nada)
             Credit(s): Greg Hance
			
			
****************************************************************/
static void dcdiv(	double	*r3,
			double	*i3,
			double	r1,
			double	i1,
			double	r2,
			double	i2)
{
	double f;

	f = r2*r2+i2*i2;
	*r3 = (r1*r2+i1*i2)/f;
	*i3 = (i1*r2-r1*i2)/f;
}


int
abs_Matrix(
	Matrix		*matP
)
{
	void		*vP;
	unsigned	n_r, n_c;
	FORMAT		f;
	CVIP_TYPE		t;

	vP	= getRealRow_Matrix(matP, 0);
	n_r	= getNoOfRows_Matrix(matP);
	n_c	= getNoOfCols_Matrix(matP);
	f	= getDataFormat_Matrix(matP);
	t	= getDataType_Matrix(matP);

	return absVector(vP, t, (n_r*n_c) << f);
}
