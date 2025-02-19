/***************************************************************************
======================================================================
Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
======================================================================
                                                                      
             File Name: m_mult.c
           Description: contains routine for performing the 
			matrix cross product of two matrices
         Related Files: Makefile, CVIPmatrix.h, CVIPcomplex.h, MATmult.h
   Initial Coding Date: 1/23/93
           Portability: Standard (ANSI) C
             Credit(s): Gregory Hance, E.E. Dept. SIUE
			Arve Kjoelen (ANSI C Portability)

  Global Function List: mult_Matrix - perform matrix multiplication

			
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
$Date: 1998/04/19 01:59:19 $                                                        
$Source: /home/cvip/cvipapps/CVIPtools3.7/MatrixAlgebra/RCS/m_mult.c,v $                                                         
$Header: /home/cvip/cvipapps/CVIPtools3.7/MatrixAlgebra/RCS/m_mult.c,v 1.5 1998/04/19 01:59:19 achomai Exp $

*****************************************************************************/
#include "stdlib.h"
#include "stdio.h"
#include "CVIPmatrix.h"
#include "CVIPcomplex.h"
#include "MATmult.h"

/****************************************************************
                  Name: mult_Matrix
         Expanded Name: Matrix Multiplication
            Parameters: <A> - pointer to first Matrix structure
			<B> - pointer to second Matrix structure
               Returns: pointer to Matrix structure containing the
			resulting vector multiplication, <A>x<B>
           Description: peforms Matrix cross product of <A> and <B>.
			Promotes result to most precise type of <A> and <B>.
			Uses MULT_MAT macro to do all 25 type combinations
			of matrices.
           Diagnostics: returns NULL pointer w/ error message when...
				...cols of <A> do not match the number
				   of rows in <B>
				...problems w/ Matrix structure
             Credit(s): Greg Hance
			C Language Algorithms in DSP
			Arve Kjoelen (ANSI C changes)
			
			
****************************************************************/
Matrix *mult_Matrix(const Matrix *A, const Matrix *B)
{
	Matrix	*C, *Am = (Matrix *) A, *Bm = (Matrix *) B;
	int	a_r,a_c,b_c,mustfree=0;
	char	*type[] = {	"CVIP_BYTE","CVIP_SHORT",
				"CVIP_INTEGER","CVIP_FLOAT",
				"CVIP_DOUBLE"};
	char	*format[] = {"REAL","COMPLEX"};
	char	*FuncName = "mult_Matrix";

	if(B->rows != A->cols) {
		error_CVIP(	FuncName,
				"Rows of B and columns of A must agree\n");
		error_CVIP(	FuncName,
				"A is %dx%d and B is %dx%d\n",
				A->rows,A->cols,B->rows,B->cols);
		return(NULL);
	}

	if(!A->rptr) {
		error_CVIP(	FuncName,
				"No A matrix allocated for mult_Matrix\n");
		return(NULL);
	}
	if(!B->rptr) {
		error_CVIP(	FuncName,
				"No B matrix allocated for mult_Matrix\n");
		return(NULL);
	}

/* simplify the row and col variables */
	a_r = A->rows;
	a_c = A->cols;
	b_c = B->cols;
    
/* tell user types and formats of matrices being operated on. */  
	msg_CVIP(	FuncName,"Multiplying %s %s and %s %s matrices.\n",
			format[A->data_format],type[A->data_type],
			format[B->data_format],type[B->data_type]);
/* Check to see if at least one of the matrices is complex 
	If this is true then both must be complex. */

	if(A->data_format == COMPLEX){
		if(B->data_format==REAL) {
			Bm = duplicate_Matrix(B,COMPLEX);
			if(Bm == NULL)
			return(NULL);
			mustfree=2;
		}
	}
	else 
	if(B->data_format==COMPLEX) {
		Am = duplicate_Matrix(A,COMPLEX);
		if(Am == NULL)
		return(NULL);
		mustfree=1;
	}

/* allocate C to be of the highest ranking type of A and B
   (largest element size gives the highest rank ) */

	if(A->data_type > B->data_type)
	C = new_Matrix(a_r,b_c,Am->data_type, Am->data_format);
	else
	C = new_Matrix(a_r,b_c,Bm->data_type, Bm->data_format);

	if(C == NULL)
	{
		if(mustfree)
			if(mustfree == 1)
			delete_Matrix(Am);
			else
			delete_Matrix(Bm);
		return(NULL);
	}

/* do the 25 type cases of A and B with 2 nested switch statements */

	switch(A->data_type) {
	case CVIP_BYTE:
		switch(B->data_type) {
		case CVIP_BYTE:    /* C byte, A byte, B byte */
			MULT_MAT(Am,Bm,C,a_r,a_c,b_c,byte,byte,byte)
			break;
		case CVIP_SHORT:    /* C short, A byte, B short */
			MULT_MAT(Am,Bm,C,a_r,a_c,b_c,byte,short,short)
			break;
		case CVIP_INTEGER:    /* C int, A byte, B int */
			MULT_MAT(Am,Bm,C,a_r,a_c,b_c,byte,int,int)
			break;
		case CVIP_FLOAT:    /* C float, A byte, B float */
			MULT_MAT(Am,Bm,C,a_r,a_c,b_c,byte,float,float)
			break;
		case CVIP_DOUBLE:    /* C double, A byte, B double */
			MULT_MAT(Am,Bm,C,a_r,a_c,b_c,byte,double,double)
		}
		break;
	case CVIP_SHORT:
		switch(B->data_type) {
		case CVIP_BYTE:    /* C short, A short, B byte */
			MULT_MAT(Am,Bm,C,a_r,a_c,b_c,short,byte,short)
			break;
		case CVIP_SHORT:    /* C short, A short, B short */
			MULT_MAT(Am,Bm,C,a_r,a_c,b_c,short,short,short)
			break;
		case CVIP_INTEGER:    /* C int, A short, B int */
			MULT_MAT(Am,Bm,C,a_r,a_c,b_c,short,int,int)
			break;
		case CVIP_FLOAT:    /* C float, A short, B float */
			MULT_MAT(Am,Bm,C,a_r,a_c,b_c,short,float,float)
			break;
		case CVIP_DOUBLE:    /* C double, A short, B double */
			MULT_MAT(Am,Bm,C,a_r,a_c,b_c,short,double,double)
		}
		break;
        case CVIP_INTEGER:
		switch(B->data_type) {
		case CVIP_BYTE:    /* C int, A int, B byte */
			MULT_MAT(Am,Bm,C,a_r,a_c,b_c,int,byte,int)
			break;
		case CVIP_SHORT:    /* C int, A int, B short */
			MULT_MAT(Am,Bm,C,a_r,a_c,b_c,int,short,int)
			break;
		case CVIP_INTEGER:    /* C int, A int, B int */
			MULT_MAT(Am,Bm,C,a_r,a_c,b_c,int,int,int)
			break;
		case CVIP_FLOAT:    /* C float, A int, B float */
			MULT_MAT(Am,Bm,C,a_r,a_c,b_c,int,float,float)
			break;
		case CVIP_DOUBLE:    /* C double, A int, B double */
			MULT_MAT(Am,Bm,C,a_r,a_c,b_c,int,double,double)
		}
		break;
	case CVIP_FLOAT:
		switch(B->data_type) {
		case CVIP_BYTE:    /* C float, A float, B byte */
			MULT_MAT(Am,Bm,C,a_r,a_c,b_c,float,byte,float)
			break;
		case CVIP_SHORT:    /* C float, A float, B short */
			MULT_MAT(Am,Bm,C,a_r,a_c,b_c,float,short,float)
			break;
		case CVIP_INTEGER:   /* C float, A float, B int */
			MULT_MAT(Am,Bm,C,a_r,a_c,b_c,float,int,float)
			break;
		case CVIP_FLOAT:    /* C float, A float, B float */
			MULT_MAT(Am,Bm,C,a_r,a_c,b_c,float,float,float)
			break;
		case CVIP_DOUBLE:    /* C double, A float, B double */
			MULT_MAT(Am,Bm,C,a_r,a_c,b_c,float,double,double)
		}
		break;
	case CVIP_DOUBLE:
		switch(B->data_type) {
		case CVIP_BYTE:    /* C double, A double, B byte */
			MULT_MAT(Am,Bm,C,a_r,a_c,b_c,double,byte,double)
			break;
		case CVIP_SHORT:    /* C double, A double, B short */
			MULT_MAT(Am,Bm,C,a_r,a_c,b_c,double,short,double)
			break;
		case CVIP_INTEGER:    /* C double, A double, B int */
			MULT_MAT(Am,Bm,C,a_r,a_c,b_c,double,int,double)
			break;
		case CVIP_FLOAT:    /* C double, A double, B float */
			MULT_MAT(Am,Bm,C,a_r,a_c,b_c,double,float,double)
			break;
		case CVIP_DOUBLE:    /* C double, A double, B double */
			MULT_MAT(Am,Bm,C,a_r,a_c,b_c,double,double,double)
		}
	}
    
	if(mustfree)
		if(mustfree==1)
		delete_Matrix(Am);
		else
		delete_Matrix(Bm);
   
	return(C);
}

