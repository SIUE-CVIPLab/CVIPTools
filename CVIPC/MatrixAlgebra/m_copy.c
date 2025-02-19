/***************************************************************************
======================================================================
Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
======================================================================
                                                                      
             File Name: m_copy.c
           Description: contains functions to copy one matrix to another.
          Related Files: Makefile, MATcopy.h, CVIPmatrix.h
   Initial Coding Date: 1/23/93
           Portability: Standard (ANSI) C
             Credit(s): Gregory Hance, E.E. Dept. SIUE

 Global Function List: copy_Matrix - copy matrix A to B
		       fastCopy_Matrix - perform fast copy 
		       duplicate_Matrix - duplicate a matrix
		       clone_Matrix - create a new matrix of same
				       type and dimensions as a.
		       paste_Matrix - paste matrix 1 to matrix b
			
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

$Log: m_copy.c,v $
Revision 1.10  1998/04/19 02:33:21  achomai
Cleaned up copy_Matrix :
1) Made the function return CVIP_NO instead of 0 and CVIP_YES
   instead of 1.
Cleaned up fastCopy_Matrix :
1) Made the function return CVIP_NO instead of 0 and CVIP_YES
   instead of 1.
2) Made the function use error_CVIP to print error messages.
Cleaned up duplicate_Matrix :
1) Made the function check if new_Matrix returned NULL.

Revision 1.9  1997/03/08 17:04:36  yawei
Swaped CVIP_YES and CVIP_NO

Revision 1.8  1997/03/08 00:55:26  yawei
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

Revision 1.7  1996/12/22 17:56:34  akjoele
removed: char temp_dir[100]
include file termio.h
int be_in_CVIPtools=0.
All of which seemed to have no business being in this module.

 * Revision 1.6  1996/12/11  20:34:57  akjoele
 * Fixed old-style (non-ANSI C) function headers.
 * Added skeleton for paste_Matrix()
 *
 * Revision 1.5  1995/11/27  19:40:21  kluo
 * check file in, add be_in_CVIPtools variable
 *
 * Revision 1.4  1995/10/25  01:15:23  kluo
 * initialize temp_dir to NULL
 *
 * Revision 1.3  1995/08/23  23:51:18  kluo
 * move definition of temp_dir ere
 *
 * Revision 1.2  1995/08/23  23:47:25  kluo
 * check file into RCS
 *
 * Revision 1.1  1993/05/04  02:30:58  hanceg
 * Initial revision
 *

*****************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include "CVIPmatrix.h"
#include "MATcopy.h"


/****************************************************************
                  Name: copy_Matrix
         Expanded Name: Matrix Copy
            Parameters: <A> - pointer to source matrix
			<B> - pointer to destination matrix
		        <force> - force operation even if matrix
			<B> is of a less precise type than <A>.
               Returns: 1 upon success, 0 upon failure
           Description: Copy the contents of <A> into <B>. Uses the 
			macro MAT_COPY to support all 25 combinations
	                of matrix types.
	   Diagnostics: returns 1 upon success and 0 upon failure; matrix 
			sizes must agree and if <force> is CVIP_NO then
			copy_Matrix will not perform the copy if <B> is less
			precise than <A>.
             Credit(s): Greg Hance
						
****************************************************************/
CVIP_BOOLEAN 
copy_Matrix(
    	const Matrix 	*A,
    	Matrix 		*B
)
{
	unsigned	a_f, b_f, a_r, a_c;
	CVIP_TYPE	a_t, b_t;

    	if( 	(getNoOfRows_Matrix(B) != getNoOfRows_Matrix(A)) ||
		(getNoOfCols_Matrix(B) != getNoOfCols_Matrix(A)) ) {
        	error_CVIP("copy_Matrix","matrix dimensions do not agree");
        	return(CVIP_NO);
    	}
    
	/* 
	** simplify the row and col variables 
	*/
    	a_r 	= getNoOfRows_Matrix(A);
    	a_c 	= getNoOfCols_Matrix(A);
	a_t 	= getDataType_Matrix(A);
	b_t	= getDataType_Matrix(B);
	a_f	= (unsigned) getDataFormat_Matrix(A);
	b_f	= (unsigned) getDataFormat_Matrix(B);
    
	/* 
	** Check to see if at least one of the matrices is real 
   	** If this is true then both must be cast as real. 
	*/      

   	if( (FORMAT) a_f == COMPLEX ) {
      		if( (FORMAT) b_f == REAL )
         		a_f = 0;
   	}
   	else 
      		if( (FORMAT) b_f == COMPLEX ) 
         		a_f = 0;

 	copy_Vector(getRow_Matrix(A,0), getRow_Matrix(B,0), 
	(a_r*a_c) << a_f, a_t, b_t);

	return(CVIP_YES);
}



/****************************************************************
                  Name: fastCopy_Matrix
         Expanded Name: Matrix Fast Copy
            Parameters: <A> - pointer to source matrix
			<B> - pointer to destination matrix
               Returns: 1 upon success, 0 upon failure
           Description: Copy the contents of <A> into <B>. Uses a faster
			method of transfering data than in copy_Matrix
			for matrices of the same type.
	   Diagnostics: returns 1 upon success and 0 upon failure; matrix 
			sizes must agree and fastCopy_Matrix will not perform
			the copy if <B> is less precise than <A>.
             Credit(s): Greg Hance
						
****************************************************************/
CVIP_BOOLEAN	fastCopy_Matrix(const Matrix *A, Matrix *B)
{
	int		a_r,a_c;
	const char	fn[] = {"fastCopy_Matrix"};
	register void	*data_a, *data_b;
	const		DF = A->data_format+1; /* DF(Data Format) = 1 (REAL), 2 (COMPLEX) */

	if(B->rows != A->rows || B->cols != A->cols) {
		error_CVIP(fn,"B and A sizes must agree\n");
		error_CVIP(fn,"A is %dx%d and B is %dx%d\n",
			A->rows,A->cols,B->rows,B->cols);
		return(CVIP_NO);
	}
    
	if((B->data_format != A->data_format)||(B->data_type != A->data_type)) {
		error_CVIP(fn,"Data format and data type of both matrices must agree.\n");
		return(CVIP_NO);
	}
    
/* simplify the row and col and data variables */
	a_r = A->rows;
	a_c = A->cols;
	data_a = (void *) A->rptr[0];
	data_b = (void *) B->rptr[0];
    
/* do the 5 type cases of A and B  */

	switch(A->data_type) {
		case CVIP_BYTE:
			memcpy(data_b, data_a, a_r*a_c*DF);
			break;
		case CVIP_SHORT:
			memcpy(data_b, data_a, sizeof(short)*a_r*a_c*DF);
			break;
		case CVIP_INTEGER:
			memcpy(data_b, data_a, sizeof(int)*a_r*a_c*DF);
			break;
		case CVIP_FLOAT:
			memcpy(data_b, data_a, sizeof(float)*a_r*a_c*DF);
			break;
		case CVIP_DOUBLE:
			memcpy(data_b, data_a, sizeof(double)*a_r*a_c*DF);
			break;
	}
	return(CVIP_YES);
}


/****************************************************************
                  Name: duplicate_Matrix
         Expanded Name: Matrix Duplication
            Parameters: <A> - pointer to source matrix
			<df> - data format of new matrix (REAL or IMAGINARY)
               Returns: pointer to new instance of matrix <A>
           Description: Creates an exact duplicate of the original
			matrix <A>, with the exception that the format can be
			altered. If the format is specified to be
			less precise than that of A then the imaginary
			data is truncated.
           Diagnostics: none
             Credit(s): Greg Hance
						
****************************************************************/
Matrix *duplicate_Matrix(const Matrix *A, FORMAT df)
{
	Matrix		*B;
	register void	*data_b, *data_a;
	int		DF = df;
	const		a_r = A->rows, a_c = A->cols;
   
	B = new_Matrix(a_r, a_c, A->data_type, DF);
	if(B == NULL)
	return(NULL);
   
	if( (df == COMPLEX) && (A->data_format == REAL) ) DF = 1;
	else DF++;
   
	data_a = (void *) A->rptr[0];
	data_b = (void *) B->rptr[0];

	switch(A->data_type) {
		case CVIP_BYTE:
			memcpy(data_b, data_a, a_r*a_c*DF);
			break;
		case CVIP_SHORT:
			memcpy(data_b, data_a, sizeof(short)*a_r*a_c*DF);
			break;
		case CVIP_INTEGER:
			memcpy(data_b, data_a, sizeof(int)*a_r*a_c*DF);
			break;
		case CVIP_FLOAT:
			memcpy(data_b, data_a, sizeof(float)*a_r*a_c*DF);
			break;
		case CVIP_DOUBLE:
			memcpy(data_b, data_a, sizeof(double)*a_r*a_c*DF);
			break;
	}
	return B;
}

   

Matrix *
clone_Matrix(
	const Matrix	*matP,
	CVIP_TYPE	dt
)
{

	return new_Matrix(
		getNoOfRows_Matrix(matP), 
		getNoOfCols_Matrix(matP), 
		dt,
		getDataFormat_Matrix(matP)
	);

}

/*
 * Function Name: paste_Matrix 
 *
 * Description: paste Matrix A into Matrix B at a specified
 * row,col offset.  B values in the paset area are overwritten.
 * all other B values are left alone.  Returns a 1 if successful,
 * and a 0 otherwise.  Supports all matrix data types.  Also
 * supports COMPLEX data formats.
 *
 * Author: Arve Kjoelen, SIUE (akjoele@ee.siue.edu)
 *
 * Initial Coding: Wed Dec 11 10:17:04 CST 1996
 *
 */
int	paste_Matrix(	Matrix *from,	Matrix	*to,
			int	rfrom,	int	cfrom,
			int	rto,	int	cto,
			int	rdelta, int	cdelta) {
	CVIP_TYPE	dtype;
	char		*FuncName = "paste_Matrix";

	if(from->rows > to->rows || from->cols > to->cols) {
		error_CVIP(FuncName,"Can't paste into a smaller matrix.\n");
		return(0);
	}
	else
	if(	(rfrom+rdelta)>(MIN(to->rows,from->rows)) ||
		((cfrom+cdelta)>(MIN(to->cols,from->cols)))) {
		error_CVIP(FuncName,"Given offset is too big\n");
		return(0);
	}
}
