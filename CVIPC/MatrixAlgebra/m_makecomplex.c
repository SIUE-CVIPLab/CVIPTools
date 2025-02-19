/***************************************************************************
======================================================================
Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
======================================================================
                                                                      
             File Name: m_makecomplex.c
           Description: contains routine for reallocating space to a 
			real MATRIX structure to make it complex
         Related Files: Makefile, CVIPmatrix.h
   Initial Coding Date: 1/24/93
           Portability: Standard (ANSI) C
             Credit(s): Gregory Hance, E.E. Dept. SIUE

  Global Function List: m_makecomplex

			
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
$Date: 1998/04/19 02:55:25 $                                                        
$Source: /home/cvip/cvipapps/CVIPtools3.7/MatrixAlgebra/RCS/m_makecomplex.c,v $                                                         
$Header: /home/cvip/cvipapps/CVIPtools3.7/MatrixAlgebra/RCS/m_makecomplex.c,v 1.5 1998/04/19 02:55:25 achomai Exp $

*****************************************************************************/
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "CVIPmatrix.h"


/****************************************************************
                  Name: matrix_makecomplex
         Expanded Name: Make a Complex Matrix
            Parameters: <real_MATRIX> - pointer to real matrix
			<verbose> - speak to me
               Returns: 1 - upon success, 0 - upon failure
           Description: reallocates twice the amount of memory
			already assigned to <real_MATRIX>  to make a complex.
			The new complex data can be referenced
			through **iptr of the MATRIX structure.
			realloc() is used to keep the new data address'
			contiguous with that of the real data...
			rather than allocate a new block of memory.
			This has potential advantages when peforming
			the same operation on both data sets (real & imag.)
           Diagnostics: returns a NULL pointer and warning message when...
			   ...matrix is already complex
			   ...memory cannot be successfully allocated
             Credit(s): Greg Hance
			
			
****************************************************************/
CVIP_BOOLEAN	matrix_makecomplex(	Matrix		*real_MATRIX,
					CVIP_BOOLEAN	verbose)
{
    int		i, j, rows, cols;
    CVIP_TYPE	data_type;
    char	**data;
    const char	function_name[] = {"matrix_makecomplex"};
    
/* check to make sure matrix is already not a complex MATRIX */
	if(real_MATRIX->data_format == COMPLEX) {
		error_CVIP(function_name,"Matrix is already complex.\n");
		return(CVIP_NO);
	}

/* simplify some commonly used variables */    
	rows = real_MATRIX->rows;
	cols = real_MATRIX->cols;
	data_type = real_MATRIX->data_type;
	data = real_MATRIX->rptr;
    
/* acknowledge complex allocation */
	if(verbose)
	msg_CVIP(function_name,"Extending Matrix to complex format.\n");

/* try to allocate the request */
	switch(data_type) {
	case CVIP_BYTE: {    /* byte matrix */
		byte		**byte_matrix;
		byte		*byte_data;
		if(!(byte_matrix = (byte **)realloc(data,
					(unsigned long)2*rows*sizeof(byte *))))
		{
			error_CVIP(function_name,
			"Could not reallocate first level of indirection.\n");
			return(CVIP_NO);
		}
		if(!(byte_data = (byte *)realloc(*data,
				(unsigned long)2*rows*cols*sizeof(byte))))
		{
			error_CVIP(function_name,
			"Could not reallocate second level of indirection.\n");
			return(CVIP_NO);
		}

		/* Remap the table of pointers in making it a 2-d complex
		   array.  Since a pointer to a (possibly new) memory region 
		   may be returned by realloc() we must remap the real data 
		   as well as the imaginary. */

		for(i = 0;i < rows*2;i++)
		{
			byte_matrix[i] = byte_data;
			byte_data += cols;
		}

		/* initialize all of the imaginary data elements to value 0 */
		(void) bzero(byte_matrix[rows],cols*rows);

		real_MATRIX->rptr = (char **)(byte_matrix);
		real_MATRIX->iptr = (char **)(byte_matrix + rows);
		break;
	}
        case CVIP_SHORT: {    /* short matrix */
		short		**short_matrix;
		short		*short_data;
		if(!(short_matrix = (short **)realloc(data,
					(unsigned long)2*rows*sizeof(short *))))
		{
			error_CVIP(function_name,
			"Could not reallocate first level of indirection.\n");
			return(CVIP_NO);
		}
		if(!(short_data = (short *)realloc(*data,
				(unsigned long)2*rows*cols*sizeof(short))))
		{
			error_CVIP(function_name,
			"Could not reallocate second level of indirection.\n");
			return(CVIP_NO);
		}

		/* Remap the table of pointers in making it a 2-d complex
		   array.  Since a pointer to a (possibly new) memory region 
		   may be returned by realloc() we must remap the real data 
		   as well as the imaginary. */

		for(i = 0;i < rows*2;i++)
		{
			short_matrix[i] = short_data;
			short_data += cols;
		}

		/* initialize all of the imaginary data elements to value 0 */
		(void) bzero(short_matrix[rows],cols*rows);

		real_MATRIX->rptr = (char **)(short_matrix);
		real_MATRIX->iptr = (char **)(short_matrix + rows);
		break;
	}
        case CVIP_INTEGER:{    /* int matrix */
		int		**int_matrix;
		int		*int_data;
		if(!(int_matrix = (int **)realloc(data,
					(unsigned long)2*rows*sizeof(int *))))
		{
			error_CVIP(function_name,
			"Could not reallocate first level of indirection.\n");
			return(CVIP_NO);
		}
		if(!(int_data = (int *)realloc(*data,
				(unsigned long)2*rows*cols*sizeof(int))))
		{
			error_CVIP(function_name,
			"Could not reallocate second level of indirection.\n");
			return(CVIP_NO);
		}

		/* Remap the table of pointers in making it a 2-d complex
		   array.  Since a pointer to a (possibly new) memory region 
		   may be returned by realloc() we must remap the real data 
		   as well as the imaginary. */

		for(i = 0;i < rows*2;i++)
		{
			int_matrix[i] = int_data;
			int_data += cols;
		}

		/* initialize all of the imaginary data elements to value 0 */
		(void) bzero(int_matrix[rows],cols*rows);

		real_MATRIX->rptr = (char **)(int_matrix);
		real_MATRIX->iptr = (char **)(int_matrix + rows);
		break;
	}
        case CVIP_FLOAT: {    /* float matrix */
		float		**float_matrix;
		float		*float_data;
		if(!(float_matrix = (float **)realloc(data,
					(unsigned long)2*rows*sizeof(float *))))
		{
			error_CVIP(function_name,
			"Could not reallocate first level of indirection.\n");
			return(CVIP_NO);
		}
		if(!(float_data = (float *)realloc(*data,
				(unsigned long)2*rows*cols*sizeof(float))))
		{
			error_CVIP(function_name,
			"Could not reallocate second level of indirection.\n");
			return(CVIP_NO);
		}

		/* Remap the table of pofloaters in making it a 2-d complex
		   array.  Since a pofloater to a (possibly new) memory region 
		   may be returned by realloc() we must remap the real data 
		   as well as the imaginary. */

		for(i = 0;i < rows*2;i++)
		{
			float_matrix[i] = float_data;
			float_data += cols;
		}

		/* initialize all of the imaginary data elements to value 0 */
		(void) bzero(float_matrix[rows],cols*rows);

		real_MATRIX->rptr = (char **)(float_matrix);
		real_MATRIX->iptr = (char **)(float_matrix + rows);
		break;
	}
        case CVIP_DOUBLE:{    /* double matrix */
		double		**double_matrix;
		double		*double_data;
		if(!(double_matrix = (double **)realloc(data,
					(unsigned long)2*rows*sizeof(double *))))
		{
			error_CVIP(function_name,
			"Could not reallocate first level of indirection.\n");
			return(CVIP_NO);
		}
		if(!(double_data = (double *)realloc(*data,
				(unsigned long)2*rows*cols*sizeof(double))))
		{
			error_CVIP(function_name,
			"Could not reallocate second level of indirection.\n");
			return(CVIP_NO);
		}

		/* Remap the table of podoubleers in making it a 2-d complex
		   array.  Since a podoubleer to a (possibly new) memory region 
		   may be returned by realloc() we must remap the real data 
		   as well as the imaginary. */

		for(i = 0;i < rows*2;i++)
		{
			double_matrix[i] = double_data;
			double_data += cols;
		}

		/* initialize all of the imaginary data elements to value 0 */
		(void) bzero(double_matrix[rows],cols*rows);

		real_MATRIX->rptr = (char **)(double_matrix);
		real_MATRIX->iptr = (char **)(double_matrix + rows);
		break;
	}
        default:
		error_CVIP(function_name,"Unsupported data type.\n");
		return(CVIP_NO);
	}
/* change matrix format to that of complex MATRIX */
	real_MATRIX->data_format = COMPLEX;
	return(CVIP_YES);
}
