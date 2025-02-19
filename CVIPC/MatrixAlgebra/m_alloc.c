/***************************************************************************
======================================================================
Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
======================================================================
                                                                      
             File Name: m_alloc.c
           Description: Matrix memory management routines
         Related Files: Makefile, CVIPmatrix.h
   Initial Coding Date: 1/23/92
           Portability: Standard (ANSI) C
             Credit(s): Gregory Hance, E.E. Dept. SIUE

  Global Function List: new_Matrix - allocate a Matrix structure
			delete_Matrix - free a Matrix structure

			
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

$Log: m_alloc.c,v $
Revision 1.5  1998/02/18 02:18:56  achomai
1) Edited new_Matrix to perform memory allocation checking :
   - new_Matrix now checks the pointer returned by calloc before using it.
   - If allocation failed, new_Matrix will free all allocated memory
     blocks before returning.
   - Code for filling the pointer table has been re-written to make it
     easier to understand.
2) Error messages are now shown using error_CVIP instead of printf.
3) Input checking in delete_Matrix is now done in two steps :
   - The function will check to make sure that the pointer passed is
     not NULL.
   - It will then check the contents of the Matrix structure.

Revision 1.4  1997/03/08 00:55:23  yawei
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

Revision 1.3  1996/12/05 19:21:33  akjoele
Made function prototypes ANSI-C-like.

 * Revision 1.2  1995/02/02  03:25:50  luok
 * correct memory deletion in matrix_delete. There is no
 * need to delete iptr, because iptr is just a pointer to memory
 * allocated by rptr
 *
 * Revision 1.1  1995/02/02  02:48:03  luok
 * Initial revision
 *
 * Revision 1.2  1995/01/13  19:50:34  kjoelena
 * Checked in for version 1.2
 *
 * Revision 1.1  1993/05/04  02:30:57  hanceg
 * Initial revision
 *

*****************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include "CVIPmatrix.h"

/****************************************************************
                  Name: new_Matrix
         Expanded Name: Allocate a matrix
            Parameters: <rows> - number of rows for new matrix
			<cols> - nuber of cols for new matrix
			<data_type> - one of CVIP_BYTE, CVIP_SHORT, CVIP_INTEGER, CVIP_FLOAT or CVIP_DOUBLE
			<data_format> - one of REAL or IMAGINARY
               Returns: a pointer to the newly allocated Matrix structure
           Description: allocates a structure of type Matrix with
			<rows> x <cols> data elements of type <data_type>.
			The Matrix structure contains two members, **rptr
			and **iptr which are used to reference
			the real and imaginary data respectively. The matrix
			data is contiguous in the sense that a reference
			to the address of the first element may be used
			to dereference all others.
	   Diagnostics: returns NULL pointer w/ corresponding error message
			upon memory allocation failure
             Credit(s): Greg Hance
			
			
****************************************************************/
Matrix *new_Matrix(unsigned int rows, unsigned int cols, CVIP_TYPE data_type, FORMAT data_format)
{
	register int i;
	Matrix *A;
	const DF = data_format+1; /* DF - Data Format (i.e. REAL or COMPLEX) */
	char	*FuncName = "new_Matrix";

/*	allocate the matrix structure */
	A = (Matrix *) calloc(1,sizeof(Matrix));
	if(!A)
	{
		error_CVIP(FuncName,"ERROR in matrix structure allocate\n");
		return NULL;
	}

/*	set up the size as requested */
	A->rows = rows;
	A->cols = cols;
	A->data_format = data_format;
	A->data_type = data_type; 

/*	try to allocate the request */
	switch(data_type) {
	case CVIP_BYTE:
	{	/* byte matrix */
		byte	**byte_matrix;
		byte	*byte_data;
		byte_matrix = (byte **)calloc(rows*DF, sizeof(byte *));
		if(byte_matrix != NULL)
		{
			byte_data = (byte *)calloc(	rows*cols*DF,
							sizeof(byte));
			if(byte_data != NULL)
			{
			/*	remap the table of pointers in 
				making it a 2-d array */
				for(i = 0;i < rows*DF; i++)
				{
					byte_matrix[i] = byte_data;
					byte_data = (byte *)(byte_data + cols);
				}
				A->rptr = (char **)byte_matrix;
				break;
			}
			free(byte_matrix);
		}
		free(A);
		error_CVIP(	FuncName,
				"Error making pointers in %dx%d byte matrix\n",
				rows,cols);
		return NULL;
	}
	case CVIP_SHORT:
	{	/* short matrix */
		short	**short_matrix;
		short	*short_data;
		short_matrix = (short **)calloc(rows*DF, sizeof(short *));
		if(short_matrix != NULL)
		{
			short_data = (short *)calloc(	rows*cols*DF,
							sizeof(short));
			if(short_data != NULL)
			{
			/*	remap the table of pointers in 
				making it a 2-d array */
				for(i = 0;i < rows*DF; i++)
				{
					short_matrix[i] = short_data;
					short_data = (short *)(short_data+cols);
				}
				A->rptr = (char **)short_matrix;
				break;
			}
			free(short_matrix);
		}
		free(A);
		error_CVIP(	FuncName,
				"Error making pointers in %dx%d short matrix\n",
				rows,cols);
		return NULL;
	}
	case CVIP_INTEGER:
	{	/* integer matrix */
		int	**int_matrix;
		int	*int_data;
		int_matrix = (int **)calloc(rows*DF, sizeof(int *));
		if(int_matrix != NULL)
		{
			int_data = (int *)calloc(	rows*cols*DF,
							sizeof(int));
			if(int_data != NULL)
			{
			/*	remap the table of pointers in 
				making it a 2-d array */
				for(i = 0;i < rows*DF; i++)
				{
					int_matrix[i] = int_data;
					int_data = (int *)(int_data + cols);
				}
				A->rptr = (char **)int_matrix;
				break;
			}
			free(int_matrix);
		}
		free(A);
		error_CVIP(	FuncName,
				"Error making pointers in %dx%d int matrix\n",
				rows,cols);
		return NULL;
	}
	case CVIP_FLOAT:
	{	/* float matrix */
		float	**float_matrix;
		float	*float_data;
		float_matrix = (float **)calloc(rows*DF, sizeof(float *));
		if(float_matrix != NULL)
		{
			float_data = (float *)calloc(	rows*cols*DF,
							sizeof(float));
			if(float_data != NULL)
			{
			/*	remap the table of pointers in 
				making it a 2-d array */
				for(i = 0;i < rows*DF; i++)
				{
					float_matrix[i] = float_data;
					float_data = (float *)(float_data+cols);
				}
				A->rptr = (char **)float_matrix;
				break;
			}
			free(float_matrix);
		}
		free(A);
		error_CVIP(	FuncName,
				"Error making pointers in %dx%d float matrix\n",
				rows,cols);
		return NULL;
	}
	case CVIP_DOUBLE:
	{	/* double matrix */
		double	**double_matrix;
		double	*double_data;
		double_matrix = (double **)calloc(rows*DF, sizeof(double *));
		if(double_matrix != NULL)
		{
			double_data = (double *)calloc(	rows*cols*DF,
							sizeof(double));
			if(double_data != NULL)
			{
			/*	remap the table of pointers in 
				making it a 2-d array */
				for(i = 0;i < rows*DF; i++)
				{
					double_matrix[i] = double_data;
					double_data=(double *)(double_data+cols);
				}
				A->rptr = (char **)double_matrix;
				break;
			}
			free(double_matrix);
		}
		free(A);
		error_CVIP(	FuncName,
			"Error making pointers in %dx%d double matrix\n",
			rows,cols);
		return NULL;
	}
	default:
		error_CVIP(FuncName,"Unsupported data_type\n");
		free(A);
		return NULL;
	}
	if(data_format == COMPLEX)
	A->iptr = (char **)((A->rptr) + rows);
	else
	A->iptr = NULL;

	return(A);
}


/****************************************************************
                  Name: delete_Matrix
         Expanded Name: Matrix Free
            Parameters: <A> - pointer to a Matrix structure
               Returns: (Nada)
           Description: Frees all memory associated with a Matrix structure.
			NOTE: Matrix structure must be allocated be 
			new_Matrix
	   Diagnostics: returns with error message when invalid Matrix structure
			is passed
             Credit(s): Greg Hance
			
****************************************************************/

void delete_Matrix(Matrix *A)
{
	char **a;

/*	check for valid structure */
	if(A != NULL)
	{
		if(	((A->rptr != NULL) || (A->iptr != NULL)) &&
			(A->rows != 0) &&
			(A->cols != 0))
		{
		/*	a used for freeing */
			a = A->rptr;
		/*	free first level of indirection */
			free(*a);
		/*	free second level of indirection */
			free((char *)a);
		/*	free matrix structure */
			free((char *)A);
			return;
		}
	}
	error_CVIP(	"delete_Matrix",
			"Invalid structure passed to delete_Matrix\n");
}
