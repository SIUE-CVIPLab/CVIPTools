/***************************************************************************
======================================================================
Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
======================================================================
                                                                      
             File Name: m_arith_bin.c
           Description: contains several matrix piece-wise arithmetic functions
         Related Files: Makefile, CVIPmatrix.h, CVIPpwise.h
   Initial Coding Date: 1/23/92
           Portability: Standard (ANSI) C
             Credit(s): Gregory Hance, E.E. Dept. SIUE

 Global Function List:  add_Matrix - add two matrices
			sub_Matrix - subtract two matrices
			multPWise_Matrix - multiply two matrices

			
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

$Log: m_arith_bin.c,v $
Revision 1.7  1998/04/19 01:38:08  achomai
Cleaned up :
1) Changed the function definition to ANSI-C style.
2) Made the functions check if duplicate_Matrix or new_Matrix returned
   NULL.
3) Made the functions use error_CVIP and msg_CVIP for printing
   error messages and information.
4) Previously, recip_Matrix prints "hello 2!" if the data type is
   CVIP_INTEGER.  This has been removed.

Revision 1.6  1997/07/16 18:51:30  smakam
changed free to delete_Matrix in divide_Matrix function

Revision 1.5  1997/03/08 17:04:15  yawei
Swaped CVIP_YES and CVIP_NO

Revision 1.4  1997/03/08 00:54:56  yawei
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

Revision 1.3  1996/03/04 15:47:50  akjoele
*** empty log message ***

 * Revision 1.2  1996/03/04  15:39:41  akjoele
 * Added divode_const_Matrix() function, which divides a matrix by
 * a constant.
 *
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
                  Name: add_Matrix
         Expanded Name: Matrix Add
            Parameters: <A> - pointer to first matrix
			<B> -pointer to second matrix
               Returns: pointer to resultant matrix containing, <A>+<B>
           Description: adds the contents of <A> to that of <B>. Uses the
			PWISE_MAT macro to do all 25 combinations of
			matrix types.  Promotes to most precise type
			of <A> and <B>. Supports complex matrices
           Diagnostics: returns NULL pointer w/ error message when matrix
			sizes do not agree.
             Credit(s): Greg Hance
			
****************************************************************/
Matrix	*add_Matrix(	const Matrix	*A,
			const Matrix	*B)
{
	Matrix	*C ,*Aa = (Matrix*)A, *Ba = (Matrix*)B;
	int	a_r,a_c,mustfree=0, DF;
	char	*type[] = {	"CVIP_BYTE","CVIP_SHORT",
				"CVIP_INTEGER","CVIP_FLOAT","CVIP_DOUBLE"};
	char	*format[] = {"REAL","COMPLEX"};
	char	*FuncName = "add_Matrix";

	if(B->rows != A->rows || B->cols != A->cols) {
		error_CVIP(FuncName,"Sizes of B and A must agree.\n");
		error_CVIP(FuncName,"A is %dx%d and B is %dx%d.\n",
			A->rows,A->cols,B->rows,B->cols);
		return(NULL);
	}
    
/* simplify the row and col variables */
	a_r = A->rows;
	a_c = A->cols;
    
/* tell user types and formats of matrices being operated on. */  
	msg_CVIP(FuncName,"Adding %s %s matrix to %s %s matrix.\n",
		format[A->data_format],type[A->data_type],
		format[B->data_format],type[B->data_type]); 
/* Check to see if at least one of the matrices is complex 
   If this is true then both must be complex. */
   
	if(A->data_format == COMPLEX){
		if(B->data_format==REAL) {
			Ba = duplicate_Matrix(B,COMPLEX);
			if(Ba == NULL)
			return(NULL);
			mustfree=2;
		}
	}
	else 
	if(B->data_format==COMPLEX) {
		Aa = duplicate_Matrix(A,COMPLEX);
		if(Aa == NULL)
		return(NULL);
		mustfree=1;
	}

/* allocate C to be of the highest ranking type of A and B
   (largest element size gives the highest rank ) */

	if(A->data_type > B->data_type)
	C = new_Matrix(a_r,a_c,Aa->data_type, Aa->data_format);
	else
	C = new_Matrix(a_r,a_c, Ba->data_type, Ba->data_format);
	if(C == NULL)
	{
		if(mustfree)
			if(mustfree==1)
			delete_Matrix(Aa);
			else
			delete_Matrix(Ba);
		return(NULL);
	}
	DF = C->data_format+1; /* DF(Data Format) = 1 (REAL), 2 (COMPLEX)*/
	 
/* inform user of type and format of resultant matrix */
	msg_CVIP(FuncName,"Resultant matrix is %s %s.\n",
		format[C->data_format],type[C->data_type]);
	 
/* do the 25 type cases of A and B with 2 nested switch statements */

	switch(A->data_type) {
	case CVIP_BYTE:
		switch(B->data_type) {
		case CVIP_BYTE:    /* C byte, A byte, B byte */
			PWISE_MAT(Aa,Ba,C,a_r*DF,a_c,+,byte,byte,byte)
			break;
		case CVIP_SHORT:    /* C short, A byte, B short */
			PWISE_MAT(Aa,Ba,C,a_r*DF,a_c,+,byte,short,short)
			break;
		case CVIP_INTEGER:    /* C int, A byte, B int */
			PWISE_MAT(Aa,Ba,C,a_r*DF,a_c,+,byte,int,int)
			break;
		case CVIP_FLOAT:    /* C float, A byte, B float */
			PWISE_MAT(Aa,Ba,C,a_r*DF,a_c,+,byte,float,float)
			break;
		case CVIP_DOUBLE:    /* C double, A byte, B double */
			PWISE_MAT(Aa,Ba,C,a_r*DF,a_c,+,byte,double,double)
		}
		break;
	case CVIP_SHORT:
		switch(B->data_type) {
		case CVIP_BYTE:    /* C short, A short, B byte */
			PWISE_MAT(Aa,Ba,C,a_r*DF,a_c,+,short,byte,short)
			break;
		case CVIP_SHORT:    /* C short, A short, B short */
			PWISE_MAT(Aa,Ba,C,a_r*DF,a_c,+,short,short,short)
			break;
		case CVIP_INTEGER:    /* C int, A short, B int */
			PWISE_MAT(Aa,Ba,C,a_r*DF,a_c,+,short,int,int)
			break;
		case CVIP_FLOAT:    /* C float, A short, B float */
			PWISE_MAT(Aa,Ba,C,a_r*DF,a_c,+,short,float,float)
			break;
		case CVIP_DOUBLE:    /* C double, A short, B double */
			PWISE_MAT(Aa,Ba,C,a_r*DF,a_c,+,short,double,double)
		}
		break;
	case CVIP_INTEGER:
		switch(B->data_type) {
		case CVIP_BYTE:    /* C int, A int, B byte */
			PWISE_MAT(Aa,Ba,C,a_r*DF,a_c,+,int,byte,int)
			break;
		case CVIP_SHORT:    /* C int, A int, B short */
			PWISE_MAT(Aa,Ba,C,a_r*DF,a_c,+,int,short,int)
			break;
		case CVIP_INTEGER:    /* C int, A int, B int */
			PWISE_MAT(Aa,Ba,C,a_r*DF,a_c,+,int,int,int)
			break;
		case CVIP_FLOAT:    /* C float, A int, B float */
			PWISE_MAT(Aa,Ba,C,a_r*DF,a_c,+,int,float,float)
			break;
		case CVIP_DOUBLE:    /* C double, A int, B double */
			PWISE_MAT(Aa,Ba,C,a_r*DF,a_c,+,int,double,double)
		}
		break;
	case CVIP_FLOAT:
		switch(B->data_type) {
		case CVIP_BYTE:    /* C float, A float, B byte */
			PWISE_MAT(Aa,Ba,C,a_r*DF,a_c,+,float,byte,float)
			break;
		case CVIP_SHORT:    /* C float, A float, B short */
			PWISE_MAT(Aa,Ba,C,a_r*DF,a_c,+,float,short,float)
			break;
		case CVIP_INTEGER:    /* C float, A float, B int */
			PWISE_MAT(Aa,Ba,C,a_r*DF,a_c,+,float,int,float)
			break;
		case CVIP_FLOAT:    /* C float, A float, B float */
			PWISE_MAT(Aa,Ba,C,a_r*DF,a_c,+,float,float,float)
			break;
		case CVIP_DOUBLE:    /* C double, A float, B double */
			PWISE_MAT(Aa,Ba,C,a_r*DF,a_c,+,float,double,double)
		}
		break;
	case CVIP_DOUBLE:
		switch(B->data_type) {
		case CVIP_BYTE:    /* C double, A double, B byte */
			PWISE_MAT(Aa,Ba,C,a_r*DF,a_c,+,double,byte,double)
			break;
                case CVIP_SHORT:    /* C double, A double, B short */
			PWISE_MAT(Aa,Ba,C,a_r*DF,a_c,+,double,short,double)
			break;
		case CVIP_INTEGER:    /* C double, A double, B int */
			PWISE_MAT(Aa,Ba,C,a_r*DF,a_c,+,double,int,double)
			break;
		case CVIP_FLOAT:    /* C double, A double, B float */
			PWISE_MAT(Aa,Ba,C,a_r*DF,a_c,+,double,float,double)
			break;
		case CVIP_DOUBLE:    /* C double, A double, B double */
			PWISE_MAT(Aa,Ba,C,a_r*DF,a_c,+,double,double,double)
		}
		break;
	}

	if(mustfree)
		if(mustfree==1)
			delete_Matrix(Aa);
		else
			delete_Matrix(Ba);
	return(C);
}

/****************************************************************
                  Name: sub_Matrix
         Expanded Name: Matrix Subtract
            Parameters: <A> - pointer to first matrix
			<B> -pointer to second matrix
               Returns: pointer to resultant matrix containing, <A>-<B>
           Description: subtracts the contents of <B> from that of <A>. Uses the
			PWISE_MAT macro to do all 25 combinations of
			matrix types.  Promotes to most precise type
			of <A> and <B>. Supports complex matrices
 	   Diagnostics: returns NULL pointer w/ error message when matrix
			sizes do not agree.
             Credit(s): Greg Hance
			
****************************************************************/
Matrix	*sub_Matrix(	const Matrix	*A,
			const Matrix	*B)
{
	Matrix	*C, *As = (Matrix*)A, *Bs = (Matrix*)B;
	int	a_r,a_c,mustfree=0, DF;
	char	*type[] = {	"CVIP_BYTE","CVIP_SHORT","CVIP_INTEGER",
				"CVIP_FLOAT","CVIP_DOUBLE"};
	char	*format[] = {"REAL","COMPLEX"};
	char	*FuncName = "sub_Matrix";

	if(B->rows != A->rows || B->cols != A->cols) {
		error_CVIP(FuncName,"Sizes of B and A must agree.\n");
		error_CVIP(FuncName,"A is %dx%d and B is %dx%d.\n",
			A->rows,A->cols,B->rows,B->cols);
		return(NULL);
	}
    
/* simplify the row and col variables */
	a_r = A->rows;
	a_c = A->cols;
    
/* tell user types and formats of matrices being operated on. */
	msg_CVIP(FuncName,"Subtracting %s %s matrix from %s %s matrix.\n",
		format[A->data_format],type[A->data_type],
		format[B->data_format],type[B->data_type]); 
    
/* Check to see if at least one of the matrices is complex 
   If this is true then both must be complex. */
	if(A->data_format == COMPLEX){
		if(B->data_format==REAL) {
			Bs = duplicate_Matrix(B,COMPLEX);
			if(Bs == NULL)
			return(NULL);
			mustfree=2;
		}
	}
	else 
	if(B->data_format==COMPLEX) {
		As = duplicate_Matrix(A,COMPLEX);
		if(As == NULL)
		return(NULL);
		mustfree=1;
	}
   
/* allocate C to be of the highest ranking type of A and B
   (largest element size gives the highest rank ) */

	if(A->data_type > B->data_type)
		C = new_Matrix(a_r,a_c,As->data_type, As->data_format);
	else
		C = new_Matrix(a_r,a_c, Bs->data_type, Bs->data_format);
	if(C == NULL)
	{
		if(mustfree)
			if(mustfree==1)
			delete_Matrix(As);
			else
			delete_Matrix(Bs);
		return(NULL);
	}
	DF = C->data_format+1; /* DF(Data Format) = 1 (REAL), 2 (COMPLEX)*/
	 
/* inform user of type and format of resultant matrix */
	msg_CVIP(FuncName,"Resultant matrix is %s %s.\n",
		format[C->data_format],type[C->data_type]);
	 
/* do the 25 type cases of A and B with 2 nested switch statements */

    switch(A->data_type) {
        case CVIP_BYTE:
            switch(B->data_type) {
                case CVIP_BYTE:    /* C byte, A byte, B byte */
                    PWISE_MAT(As,Bs,C,a_r*DF,a_c,-,byte,byte,byte)
                    break;
                case CVIP_SHORT:    /* C short, A byte, B short */
                    PWISE_MAT(As,Bs,C,a_r*DF,a_c,-,byte,short,short)
                    break;
                case CVIP_INTEGER:    /* C int, A byte, B int */
                    PWISE_MAT(As,Bs,C,a_r*DF,a_c,-,byte,int,int)
                    break;
                case CVIP_FLOAT:    /* C float, A byte, B float */
                    PWISE_MAT(As,Bs,C,a_r*DF,a_c,-,byte,float,float)
                    break;
                case CVIP_DOUBLE:    /* C double, A byte, B double */
                    PWISE_MAT(As,Bs,C,a_r*DF,a_c,-,byte,double,double)
            }
            break;
        case CVIP_SHORT:
            switch(B->data_type) {
                case CVIP_BYTE:    /* C short, A short, B byte */
                    PWISE_MAT(As,Bs,C,a_r*DF,a_c,-,short,byte,short)
                    break;
                case CVIP_SHORT:    /* C short, A short, B short */
                    PWISE_MAT(As,Bs,C,a_r*DF,a_c,-,short,short,short)
                    break;
                case CVIP_INTEGER:    /* C int, A short, B int */
                    PWISE_MAT(As,Bs,C,a_r*DF,a_c,-,short,int,int)
                    break;
                case CVIP_FLOAT:    /* C float, A short, B float */
                    PWISE_MAT(As,Bs,C,a_r*DF,a_c,-,short,float,float)
                    break;
                case CVIP_DOUBLE:    /* C double, A short, B double */
                    PWISE_MAT(As,Bs,C,a_r*DF,a_c,-,short,double,double)
            }
            break;
        case CVIP_INTEGER:
            switch(B->data_type) {
                case CVIP_BYTE:    /* C int, A int, B byte */
                    PWISE_MAT(As,Bs,C,a_r*DF,a_c,-,int,byte,int)
                    break;
                case CVIP_SHORT:    /* C int, A int, B short */
                    PWISE_MAT(As,Bs,C,a_r*DF,a_c,-,int,short,int)
                    break;
                case CVIP_INTEGER:    /* C int, A int, B int */
                    PWISE_MAT(As,Bs,C,a_r*DF,a_c,-,int,int,int)
                    break;
                case CVIP_FLOAT:    /* C float, A int, B float */
                    PWISE_MAT(As,Bs,C,a_r*DF,a_c,-,int,float,float)
                    break;
                case CVIP_DOUBLE:    /* C double, A int, B double */
                    PWISE_MAT(As,Bs,C,a_r*DF,a_c,-,int,double,double)
            }
            break;
        case CVIP_FLOAT:
            switch(B->data_type) {
                case CVIP_BYTE:    /* C float, A float, B byte */
                    PWISE_MAT(As,Bs,C,a_r*DF,a_c,-,float,byte,float)
                    break;
                case CVIP_SHORT:    /* C float, A float, B short */
                    PWISE_MAT(As,Bs,C,a_r*DF,a_c,-,float,short,float)
                    break;
                case CVIP_INTEGER:    /* C float, A float, B int */
                    PWISE_MAT(As,Bs,C,a_r*DF,a_c,-,float,int,float)
                    break;
                case CVIP_FLOAT:    /* C float, A float, B float */
                    PWISE_MAT(As,Bs,C,a_r*DF,a_c,-,float,float,float)
                    break;
                case CVIP_DOUBLE:    /* C double, A float, B double */
                    PWISE_MAT(As,Bs,C,a_r*DF,a_c,-,float,double,double)
            }
            break;
        case CVIP_DOUBLE:
            switch(B->data_type) {
                case CVIP_BYTE:    /* C double, A double, B byte */
                    PWISE_MAT(As,Bs,C,a_r*DF,a_c,-,double,byte,double)
                    break;
                case CVIP_SHORT:    /* C double, A double, B short */
                    PWISE_MAT(As,Bs,C,a_r*DF,a_c,-,double,short,double)
                    break;
                case CVIP_INTEGER:    /* C double, A double, B int */
                    PWISE_MAT(As,Bs,C,a_r*DF,a_c,-,double,int,double)
                    break;
                case CVIP_FLOAT:    /* C double, A double, B float */
                    PWISE_MAT(As,Bs,C,a_r*DF,a_c,-,double,float,double)
                    break;
                case CVIP_DOUBLE:    /* C double, A double, B double */
                    PWISE_MAT(As,Bs,C,a_r*DF,a_c,-,double,double,double)
            }
            break;
    }

	if(mustfree)
		if(mustfree==1)
			delete_Matrix(As);
		else
			delete_Matrix(Bs);

    return(C);
}


/****************************************************************
                  Name: multPWise_Matrix
         Expanded Name: Matrix Piece-wise Multiplication
            Parameters: <A> - pointer to first matrix
			<B> -pointer to second matrix
               Returns: pointer to resultant matrix containing, <A>*<B>
           Description: multiplies the contents of <B> from that of <A>.
			Uses the PWISE_MULT macro to do all 25 combinations of
			matrix types.  Promotes to most precise type
			of <A> and <B>. Supports complex matrices
 	   Diagnostics: returns NULL pointer w/ error message when matrix
			sizes do not agree.
             Credit(s): Greg Hance
			
****************************************************************/
Matrix *multPWise_Matrix(	const Matrix	*A,
				const Matrix	*B)
{
	Matrix	*C, *Am = (Matrix*)A, *Bm = (Matrix*)B;
	int	a_r,a_c,mustfree=0;
	char	*type[] = {	"CVIP_BYTE","CVIP_SHORT","CVIP_INTEGER",
				"CVIP_FLOAT","CVIP_DOUBLE"};
	char	*format[] = {"REAL","COMPLEX"};
	char	*FuncName = "multPWise_Matrix";

	if(B->rows != A->rows || B->cols != A->cols) {
		error_CVIP(FuncName,"Sizes of B and A must agree.\n");
		error_CVIP(FuncName,"A is %dx%d and B is %dx%d.\n",
			A->rows,A->cols,B->rows,B->cols);
		return(NULL);
	}
    
/* simplify the row and col variables */
	a_r = A->rows;
	a_c = A->cols;
    
/* tell user types and formats of matrices being operated on. */
	msg_CVIP(FuncName,"Multiplying %s %s matrix and %s %s matrix.\n",
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
         C = new_Matrix(a_r,a_c,Am->data_type, Am->data_format);
    else
         C = new_Matrix(a_r,a_c, Bm->data_type, Bm->data_format);
	if(C == NULL)
	{
		if(mustfree)
			if(mustfree==1)
			delete_Matrix(Am);
			else
			delete_Matrix(Bm);
		return(NULL);
	}
/* inform user of type and format of resultant matrix */
	msg_CVIP(FuncName,"Resultant matrix is %s %s.\n",
		format[C->data_format],type[C->data_type]);

/* do the 25 type cases of A and B with 2 nested switch statements */

    switch(A->data_type) {
        case CVIP_BYTE:
            switch(B->data_type) {
                case CVIP_BYTE:    /* C byte, A byte, B byte */
                    PWISE_MULT(Am,Bm,C,a_r,a_c,byte,byte,byte)
                    break;
                case CVIP_SHORT:    /* C short, A byte, B short */
                    PWISE_MULT(Am,Bm,C,a_r,a_c,byte,short,short)
                    break;
                case CVIP_INTEGER:    /* C int, A byte, B int */
                    PWISE_MULT(Am,Bm,C,a_r,a_c,byte,int,int)
                    break;
                case CVIP_FLOAT:    /* C float, A byte, B float */
                    PWISE_MULT(Am,Bm,C,a_r,a_c,byte,float,float)
                    break;
                case CVIP_DOUBLE:    /* C double, A byte, B double */
                    PWISE_MULT(Am,Bm,C,a_r,a_c,byte,double,double)
            }
            break;
        case CVIP_SHORT:
            switch(B->data_type) {
                case CVIP_BYTE:    /* C short, A short, B byte */
                    PWISE_MULT(Am,Bm,C,a_r,a_c,short,byte,short)
                    break;
                case CVIP_SHORT:    /* C short, A short, B short */
                    PWISE_MULT(Am,Bm,C,a_r,a_c,short,short,short)
                    break;
                case CVIP_INTEGER:    /* C int, A short, B int */
                    PWISE_MULT(Am,Bm,C,a_r,a_c,short,int,int)
                    break;
                case CVIP_FLOAT:    /* C float, A short, B float */
                    PWISE_MULT(Am,Bm,C,a_r,a_c,short,float,float)
                    break;
                case CVIP_DOUBLE:    /* C double, A short, B double */
                    PWISE_MULT(Am,Bm,C,a_r,a_c,short,double,double)
            }
            break;
        case CVIP_INTEGER:
            switch(B->data_type) {
                case CVIP_BYTE:    /* C int, A int, B byte */
                    PWISE_MULT(Am,Bm,C,a_r,a_c,int,byte,int)
                    break;
                case CVIP_SHORT:    /* C int, A int, B short */
                    PWISE_MULT(Am,Bm,C,a_r,a_c,int,short,int)
                    break;
                case CVIP_INTEGER:    /* C int, A int, B int */
                    PWISE_MULT(Am,Bm,C,a_r,a_c,int,int,int)
                    break;
                case CVIP_FLOAT:    /* C float, A int, B float */
                    PWISE_MULT(Am,Bm,C,a_r,a_c,int,float,float)
                    break;
                case CVIP_DOUBLE:    /* C double, A int, B double */
                    PWISE_MULT(Am,Bm,C,a_r,a_c,int,double,double)
            }
            break;
        case CVIP_FLOAT:
            switch(B->data_type) {
                case CVIP_BYTE:    /* C float, A float, B byte */
                    PWISE_MULT(Am,Bm,C,a_r,a_c,float,byte,float)
                    break;
                case CVIP_SHORT:    /* C float, A float, B short */
                    PWISE_MULT(Am,Bm,C,a_r,a_c,float,short,float)
                    break;
                case CVIP_INTEGER:    /* C float, A float, B int */
                    PWISE_MULT(Am,Bm,C,a_r,a_c,float,int,float)
                    break;
                case CVIP_FLOAT:    /* C float, A float, B float */
                    PWISE_MULT(Am,Bm,C,a_r,a_c,float,float,float)
                    break;
                case CVIP_DOUBLE:    /* C double, A float, B double */
                    PWISE_MULT(Am,Bm,C,a_r,a_c,float,double,double)
            }
            break;
        case CVIP_DOUBLE:
            switch(B->data_type) {
                case CVIP_BYTE:    /* C double, A double, B byte */
                    PWISE_MULT(Am,Bm,C,a_r,a_c,double,byte,double)
                    break;
                case CVIP_SHORT:    /* C double, A double, B short */
                    PWISE_MULT(Am,Bm,C,a_r,a_c,double,short,double)
                    break;
                case CVIP_INTEGER:    /* C double, A double, B int */
                    PWISE_MULT(Am,Bm,C,a_r,a_c,double,int,double)
                    break;
                case CVIP_FLOAT:    /* C double, A double, B float */
                    PWISE_MULT(Am,Bm,C,a_r,a_c,double,float,double)
                    break;
                case CVIP_DOUBLE:    /* C double, A double, B double */
                    PWISE_MULT(Am,Bm,C,a_r,a_c,double,double,double)
            }
            break;
    }

	if(mustfree)
		if(mustfree==1)
			delete_Matrix(Am);
		else
			delete_Matrix(Bm);

	return(C);
}

#define RINV(type,r2,r1,check) do { \
	if(r1) { \
		r2 = 1.0/(r1); \
		check = CVIP_YES; \
	} \
	else 	check = CVIP_NO; \
} while(0)

#define CINV(type,r2,i2,r1,i1,check) do { \
	type r3, i3; \
	CMUL(type,r3,i3,r1,i1,r1,-i1); \
	if(r3) { \
		r2 = (r1)/r3; \
		i2 = -(i1)/r3; \
		check = CVIP_YES; \
	} \
	else 	check = CVIP_NO; \
} while(0)

#define PWISE_RECIP(a,b,c,rowsa,colsa,typea,typeb,typec) {  \
	typea 		**_AMXR = (typea **)(a)->rptr; \
	typeb 		**_BMXR = (typeb **)(b)->rptr; \
	typec 		**_CMXR = (typec **)(c)->rptr; \
	typea 		**_AMXI = (typea **)(a)->iptr; \
	typeb 		**_BMXI = (typeb **)(b)->iptr; \
	typec 		**_CMXI = (typec **)(c)->iptr; \
	register typea 	*_PTAR;  \
	register typeb 	*_PTBR; \
	register typec 	*_PTCR; \
	register typea 	*_PTAI;  \
	register typeb 	*_PTBI; \
	register typec 	*_PTCI; \
	register int 	_IX,_JX; \
	CVIP_BOOLEAN 	check; \
	for(_IX = 0 ; _IX < rowsa ; _IX++) { \
		_PTCR = _CMXR[_IX]; \
		_PTBR = _BMXR[_IX]; \
		_PTAR = _AMXR[_IX]; \
		if(getDataFormat_Matrix(a)==COMPLEX) { \
			_PTCI = _CMXI[_IX]; \
		        _PTBI = _BMXI[_IX]; \
		        _PTAI = _AMXI[_IX]; \
		} \
		for(_JX = 0 ; _JX < colsa ; _JX++) {\
			if(getDataFormat_Matrix(a)==REAL) { \
			 	RINV(typeb,*_PTBR,*_PTAR,check); \
				if(!check) \
					*_PTBR = *_PTCR; \
				_PTCR++;_PTAR++;_PTBR++; \
			} \
			else {\
				CINV(typeb,*_PTBR,*_PTBI,*_PTAR,*_PTAI,check); \
				if(!check) { \
					*_PTBR = *_PTCR; \
					*_PTBI = *_PTCI; \
				} \
				_PTCR++;_PTCI++;_PTAR++;_PTAI++;_PTBR++;_PTBI++; \
			} \
		} \
	} \
}

int
divide_Matrix(
	Matrix		**dP, 
	const Matrix	*aP,
	const Matrix	*bP,
	const Matrix	*cP

)
{
	Matrix		*denP, *numP;

	numP = (Matrix *)aP;
	recip_Matrix(&denP, bP, cP);
	if(denP != NULL)
	{
		*dP = multPWise_Matrix(numP, denP);
		delete_Matrix(denP);
		return 1;
	}
	*dP = NULL;
	return(0);
}

int
recip_Matrix(
	Matrix		**rP, 
	const Matrix	*aP,
	const Matrix	*bP
)
{

    	int 		a_r, a_c;
    	const char 	*fn = {"recip_Matrix"};

	/* 
	** simplify the row and col variables 
	*/
   	a_r = getNoOfRows_Matrix(aP);
    	a_c = getNoOfCols_Matrix(aP);

	/* 
	** do the different type cases with a switch statement 
	*/
    	switch(getDataType_Matrix(aP)) {
        case CVIP_SHORT:    
		/* 
		** if a short, b is float 
		*/
	    	*rP = new_Matrix(a_r,a_c,CVIP_FLOAT,getDataFormat_Matrix(aP));
		if(*rP == NULL)
		break;
		PWISE_RECIP(aP,*rP,bP,a_r,a_c,short,float,short)
            	break;
	case CVIP_BYTE:   
		/*
		** if a byte, b is float 
		*/
	    	*rP = new_Matrix(a_r,a_c,CVIP_FLOAT,getDataFormat_Matrix(aP));
		if(*rP == NULL)
		break;
		PWISE_RECIP(aP,*rP,bP,a_r,a_c,byte,float,byte)
            	break;
        case CVIP_INTEGER:    
		/* 
		** if a integer, b is float 
		*/
	    	*rP = new_Matrix(a_r,a_c,CVIP_FLOAT,getDataFormat_Matrix(aP));
		if(*rP == NULL)
		break;
		PWISE_RECIP(aP,*rP,bP,a_r,a_c,int,float,int)
            	break;
        case CVIP_FLOAT:    
		/* 
		** a float, b float 
		*/
	    	*rP = new_Matrix(a_r,a_c,CVIP_FLOAT,getDataFormat_Matrix(aP));
		if(*rP == NULL)
		break;
		PWISE_RECIP(aP,*rP,bP,a_r,a_c,float,float,float)
            	break;
        case CVIP_DOUBLE:    
		/* 
		** a double, b double 
		*/
	    	*rP = new_Matrix(a_r,a_c,CVIP_DOUBLE,getDataFormat_Matrix(aP));
		if(*rP == NULL)
		break;
		PWISE_RECIP(aP,*rP,bP,a_r,a_c,double,double,double)
		break;
	default:
		return 0;
	}

    	return 1;
}
