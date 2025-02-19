
/***************************************************************************
======================================================================
Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
======================================================================
                                                                      
             File Name: m_makereal.c
           Description: contains routine to truncate an imaginary
			matrix into a real
         Related Files: Makefile, CVIPmatrix.h
   Initial Coding Date: 1/24/93
           Portability: Standard (ANSI) C
             Credit(s): Gregory Hance, E.E. Dept. SIUE

  Global Function List: makeReal_Matrix - make a real matrix
			
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
$Date: 1998/04/19 03:14:26 $                                                        
$Source: /home/cvip/cvipapps/CVIPtools3.7/MatrixAlgebra/RCS/m_makereal.c,v $                                                         
$Header: /home/cvip/cvipapps/CVIPtools3.7/MatrixAlgebra/RCS/m_makereal.c,v 1.4 1998/04/19 03:14:26 achomai Exp $

*****************************************************************************/
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "CVIPmatrix.h"

/****************************************************************
                  Name: makeReal_Matrix
         Expanded Name: Matrix Make Real
            Parameters: complex_Matrix - pointer to matrix structure
			verbose - should i speak?
               Returns: 1 - upon success, 0 - upon failure
           Description: reallocates the amount of memory associated 
			with complex_Matrix to that of a real matrix
           Diagnostics: returns NULL pointer and error message when...
				...matrix is already real
				...memory cannot be reallocated by realloc()
             Credit(s): Greg Hance
			
			
****************************************************************/
CVIP_BOOLEAN makeReal_Matrix(	Matrix		*complex_Matrix,
				CVIP_BOOLEAN	verbose)
{
	int		i, j, rows, cols;
	CVIP_TYPE	data_type;
	char		**data;
	const char	function_name[] = {"makeReal_Matrix"};

/* check to make sure matrix is already not a real Matrix */
	if(complex_Matrix->data_format == REAL) {
		error_CVIP(function_name,"Matrix is already real.\n");
		return(CVIP_NO);
	}

    
/* simplify some commonly used variables */    
	rows = complex_Matrix->rows;
	cols = complex_Matrix->cols;
	data_type = complex_Matrix->data_type;
	data = complex_Matrix->rptr;
      
/* acknowledge complex allocation */
	if(verbose)
	msg_CVIP(
		function_name,
		"Cropping complex part of Matrix to form real matrix.\n");

/* try to allocate the request */
	switch(data_type){
	case CVIP_BYTE:{	/* byte matrix */
		byte	**byte_matrix;
		byte	*byte_data;

		if(!(byte_matrix = (byte **)realloc(data,rows*sizeof(byte *))))
		{
			error_CVIP(function_name,
			"Could not reallocate first level of indirection.\n");
			return(CVIP_NO);
		}
		if(!(byte_data = (byte *)realloc(*data,
				rows*cols*sizeof(byte))))
		{
			error_CVIP(function_name,
			"Could not reallocate second level of indirection.\n");
			return(CVIP_NO);
		}
		/* Since a pointer to a (possibly new) memory region may be 
		   returned by realloc() we may need to remap the real data. */
		if((char *)byte_data != *data)
		for(i = 0;i < rows;i++)
		{
			byte_matrix[i] = byte_data;
			byte_data += cols;
		}
		complex_Matrix->rptr = (char **)byte_matrix;
		break;
	}
	case CVIP_SHORT:{	/* short matrix */
		short	**short_matrix;
		short	*short_data;

		if(!(short_matrix=(short **)realloc(data,rows*sizeof(short *))))
		{
			error_CVIP(function_name,
			"Could not reallocate first level of indirection.\n");
			return(CVIP_NO);
		}
		if(!(short_data = (short *)realloc(*data,
				rows*cols*sizeof(short))))
		{
			error_CVIP(function_name,
			"Could not reallocate second level of indirection.\n");
			return(CVIP_NO);
		}
		/* Since a pointer to a (possibly new) memory region may be 
		   returned by realloc() we may need to remap the real data. */
		if((char *)short_data != *data)
		for(i = 0;i < rows;i++)
		{
			short_matrix[i] = short_data;
			short_data += cols;
		}
		complex_Matrix->rptr = (char **)short_matrix;
		break;
	}
	case CVIP_INTEGER:{	/* int matrix */
		int	**int_matrix;
		int	*int_data;

		if(!(int_matrix=(int **)realloc(data,rows*sizeof(int *))))
		{
			error_CVIP(function_name,
			"Could not reallocate first level of indirection.\n");
			return(CVIP_NO);
		}
		if(!(int_data = (int *)realloc(*data,
				rows*cols*sizeof(int))))
		{
			error_CVIP(function_name,
			"Could not reallocate second level of indirection.\n");
			return(CVIP_NO);
		}
		/* Since a pointer to a (possibly new) memory region may be 
		   returned by realloc() we may need to remap the real data. */
		if((char *)int_data != *data)
		for(i = 0;i < rows;i++)
		{
			int_matrix[i] = int_data;
			int_data += cols;
		}
		complex_Matrix->rptr = (char **)int_matrix;
		break;
	}
        case CVIP_FLOAT:{	/* float matrix */
		float	**float_matrix;
		float	*float_data;

		if(!(float_matrix=(float **)realloc(data,rows*sizeof(float *))))
		{
			error_CVIP(function_name,
			"Could not reallocate first level of indirection.\n");
			return(CVIP_NO);
		}
		if(!(float_data = (float *)realloc(*data,
				rows*cols*sizeof(float))))
		{
			error_CVIP(function_name,
			"Could not reallocate second level of indirection.\n");
			return(CVIP_NO);
		}
		/* Since a pofloater to a (possibly new) memory region may be 
		   returned by realloc() we may need to remap the real data. */
		if((char *)float_data != *data)
		for(i = 0;i < rows;i++)
		{
			float_matrix[i] = float_data;
			float_data += cols;
		}
		complex_Matrix->rptr = (char **)float_matrix;
		break;
	}
        case CVIP_DOUBLE:{	/* double matrix */
		double	**double_matrix;
		double	*double_data;

		if(!(double_matrix=(double **)realloc(data,rows*sizeof(double *))))
		{
			error_CVIP(function_name,
			"Could not reallocate first level of indirection.\n");
			return(CVIP_NO);
		}
		if(!(double_data = (double *)realloc(*data,
				rows*cols*sizeof(double))))
		{
			error_CVIP(function_name,
			"Could not reallocate second level of indirection.\n");
			return(CVIP_NO);
		}
		/* Since a podoubleer to a (possibly new) memory region may be 
		   returned by realloc() we may need to remap the real data. */
		if((char *)double_data != *data)
		for(i = 0;i < rows;i++)
		{
			double_matrix[i] = double_data;
			double_data += cols;
		}
		complex_Matrix->rptr = (char **)double_matrix;
		break;
	}
        default:
		error_CVIP(function_name,"Unsupported data type.\n");
		return(CVIP_NO);
	}
/* change matrix format to that of complex Matrix */
	complex_Matrix->data_format = REAL;
	complex_Matrix->iptr = NULL;
	return(CVIP_YES);
}
