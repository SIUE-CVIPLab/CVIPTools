/***************************************************************************
======================================================================
Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
======================================================================
                                                                      
             File Name: m_logic_bin.c
           Description: contains several matrix piece-wise logical functions
         Related Files: Makefile, CVIPmatrix.h, CVIPpwise.h
   Initial Coding Date: 1/23/92
           Portability: Standard (ANSI) C
             Credit(s): Gregory Hance, E.E. Dept. SIUE

 Global Function List:  and_Matrix - and two matrices
			
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

$Log: m_logic_bin.c,v $
Revision 1.3  1998/04/19 01:52:36  achomai
Cleaned up and_Matrix :
1) Made the function check if new_Matrix or duplicate_Matrix
   returned NULL.
2) Made the function delete the temporary and output matrices
   if the function failed because of an unknown data type.
3) Removed the mixing of data type and data format when the
   function does comparison.

Revision 1.2  1997/03/08 00:55:17  yawei
Name Changes:
	BOOLEAN ==> CVIP_BOOLEAN
	FALSE ==> CVIP_NO
	TRUE ==> CVIP_YES
	BYTE ==> CVIP_BYTE
	SHORT ==> CVIP_SHORT
	INTEGER ==> CVIP_INTEGER
	FLOAT ==> CVIP_FLOAT
	DOUBLE ==> CVIP_DOUBLE
	TYPE ==> CVIP_TYPE

Revision 1.1  1994/10/30 17:58:41  hanceg
CVIPtools1.0 source file - G. Hance

 * Revision 1.1  1993/05/04  02:30:57  hanceg
 * Initial revision
 *                                                         


*****************************************************************************/

#include "stdlib.h"
#include "stdio.h"
#include "CVIPmatrix.h"
#include "CVIPcomplex.h"
#include "MATpwise.h"

/****************************************************************
                  Name: and_Matrix
         Expanded Name: Matrix And (logical)
            Parameters: <A> - pointer to first matrix
			<B> -pointer to second matrix
               Returns: pointer to resultant matrix containing, <A>&<B>
           Description: ands the contents of <A> to that of <B>. Uses the
			PWISE_MAT macro to do all 15 combinations of
			integer matrix types.  Promotes to most precise type
			of <A> and <B>. Supports complex matrices
           Diagnostics: returns NULL pointer w/ error message when matrix
			sizes do not agree.
             Credit(s): Greg Hance
			
****************************************************************/
Matrix *and_Matrix(
	const Matrix *A,
	const Matrix *B
)
{
	Matrix		*matC ,*matA = (Matrix*)A, *matB = (Matrix*)B;
    	int 		a_r, a_c, mustfree=0, df;
	CVIP_TYPE 	a_type, b_type;
	FORMAT		a_format, b_format;
	
	/* 
	** simplify some variables 
	*/
    	a_r = getNoOfRows_Matrix(A);
    	a_c = getNoOfCols_Matrix(A);
	a_type = getDataType_Matrix(A);
	b_type = getDataType_Matrix(B);
	a_format = getDataFormat_Matrix(A);
	b_format = getDataFormat_Matrix(B);

    	if(getNoOfRows_Matrix(B) != a_r || getNoOfCols_Matrix(B) != a_c) {
        	error_CVIP("and_Matrix", "B and A sizes must agree");
        	error_CVIP("and_Matrix", "A is %dx%d and B is %dx%d"
                ,a_r, a_c, getNoOfRows_Matrix(B), getNoOfCols_Matrix(B));
        	return NULL;
    	}

	if( (a_type > CVIP_INTEGER) || (b_type > CVIP_INTEGER) ) {
		error_CVIP("and_Matrix",
		"both matrices must be of integral type!");
		return NULL;
	}
    
	/* 
	** Check to see if at least one of the matrices is complex
	** If this is true then both must be complex.
	*/
   
   	if(a_format == COMPLEX){
      		if(b_format==REAL) {
			b_format = COMPLEX;
         		matB = duplicate_Matrix(B,b_format);
			if(matB == NULL)
			return(NULL);
	 		mustfree=2;
      		}
   	}
   	else 
      		if(b_format==COMPLEX) {
			a_format = COMPLEX;
         		matA = duplicate_Matrix(A,a_format);
			if(matA == NULL)
			return(NULL);
	 		mustfree=1;
      		}

	/* 
	** allocate C to be of the highest ranking type of A and B
   	** (largest element size gives the highest rank ) 
	*/

    	if(a_type > b_type)
        	matC = new_Matrix(a_r, a_c, a_type, a_format);
    	else
         	matC = new_Matrix(a_r, a_c, b_type, b_format);
	if(matC == NULL)
	{
	/*	If allocation for C failed, then the temporary
		matrix matA or matB must be deleted.
	*/
		if(mustfree)
		{
			if(mustfree==1)
			delete_Matrix(matA);
			else
			delete_Matrix(matB);
		}
		return(NULL);
	}
	/*
	** data format = 1 (REAL), 2 (COMPLEX)
	*/
    	df = getDataFormat_Matrix(matC);
	 	 
	/* 
	** do the 15 type cases of A and B with 2 nested switch statements 
	*/

    	switch(a_type) {
        case CVIP_BYTE:
            	switch(b_type) {
                case CVIP_BYTE:    /* C byte, A byte, B byte */
                    PWISE_MAT(matA,matB,matC,a_r<<df,a_c,&,byte,byte,byte)
                    break;
                case CVIP_SHORT:    /* C short, A byte, B short */
                    PWISE_MAT(matA,matB,matC,a_r<<df,a_c,&,byte,short,short)
                    break;
                case CVIP_INTEGER:    /* C int, A byte, B int */
                    PWISE_MAT(matA,matB,matC,a_r<<df,a_c,&,byte,int,int)
                    break;
		default: 
			error_CVIP("and_Matrix", 
			"invalid CVIPtools data type for matrix B!");
			delete_Matrix(matC);
			matC = NULL;
            	}
        break;
	case CVIP_SHORT:
            	switch(b_type) {
                case CVIP_BYTE:    /* C short, A short, B byte */
                    PWISE_MAT(matA,matB,matC,a_r<<df,a_c,&,short,byte,short)
                    break;
                case CVIP_SHORT:    /* C short, A short, B short */
                    PWISE_MAT(matA,matB,matC,a_r<<df,a_c,&,short,short,short)
                    break;
                case CVIP_INTEGER:    /* C int, A short, B int */
                    PWISE_MAT(matA,matB,matC,a_r<<df,a_c,&,short,int,int)
                    break;
		default: 
			error_CVIP("and_Matrix", 
			"invalid CVIPtools data type for matrix B!");
			delete_Matrix(matC);
			matC = NULL;
            	}
        break;
	case CVIP_INTEGER:
		switch(b_type) {
                case CVIP_BYTE:    /* C int, A int, B byte */
                	PWISE_MAT(matA,matB,matC,a_r<<df,a_c,&,int,byte,int)
                    	break;
                case CVIP_SHORT:    /* C int, A int, B short */
                    	PWISE_MAT(matA,matB,matC,a_r<<df,a_c,&,int,short,int)
                    	break;
                case CVIP_INTEGER:    /* C int, A int, B int */
                    	PWISE_MAT(matA,matB,matC,a_r<<df,a_c,&,int,int,int)
                    	break;
		default: 
			error_CVIP("and_Matrix", 
			"invalid CVIPtools data type for matrix B!");
			delete_Matrix(matC);
			matC = NULL;
            	}
	break;
	default:
		error_CVIP("and_Matrix",
		"invalid CVIPtools data type for matrix A!");
		delete_Matrix(matC);
		matC = NULL;
	}

	if(mustfree)
		if(mustfree==1)
			delete_Matrix(matA);
		else
			delete_Matrix(matB);

	return(matC);
}
