/***************************************************************************
======================================================================
Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
======================================================================
                                                                      
             File Name: m_scale.c
           Description: contains libmatrix.a routine for scaling a 
			matrix by some coefficient s.
         Related Files: Makefile, CVIPmatrix.h, MATscale.h
   Initial Coding Date: 1/24/92
           Portability: Standard (ANSI) C
             Credit(s): Gregory Hance, E.E. Dept. SIUE
			Arve Kjoelen, SIUE

  Global Function List: scale_Matrix - scale a matrix
			
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
$Date: 1998/04/19 02:31:13 $                                                        
$Source: /home/cvip/cvipapps/CVIPtools3.7/MatrixAlgebra/RCS/m_scale.c,v $                                                         
$Header: /home/cvip/cvipapps/CVIPtools3.7/MatrixAlgebra/RCS/m_scale.c,v 1.3 1998/04/19 02:31:13 achomai Exp $

*****************************************************************************/
#include "stdlib.h"
#include "stdio.h"
#include "CVIPmatrix.h"
#include "MATscale.h"


/****************************************************************
                  Name: scale_Matrix
         Expanded Name: Matrix Scale
            Parameters: <a> - pointer to Matrix structure
			<s> - coefficient to multiply by each element
			of matrix <a>
               Returns: pointer to Matrix structure containing 
			scaled matrix (type float or double)
           Description: Scales each element of the matrix <a> by some
			coefficient <s>. All data types less precise
			than CVIP_FLOAT or promoted. 
           Diagnostics: prints message of type of promotion being made
			Frees up old matrix.
             Credit(s): Greg Hance
			
			
****************************************************************/
Matrix *scale_Matrix(	const Matrix	*a,
			double		s)
{
	Matrix	*b;
	int	a_r,a_c;
	char	function_name[] = {"scale_Matrix"};

/* simplify the row and col variables */
	a_r = a->rows;
	a_c = a->cols;

/* do the different type cases with a switch statement */
	switch(a->data_type) {
		case CVIP_SHORT:	/* if a short, b is float */
			b = new_Matrix(a_r,a_c,CVIP_FLOAT,a->data_format);
			if(b == NULL)
			break;
			msg_CVIP(	function_name,
					"Promoting Matrix to type float.\n");
			SCALE_MAT(a,b,s,a_r,a_c,0,0,short,float)
			break;
		case CVIP_BYTE:		/* if a byte, b is float */
			b = new_Matrix(a_r,a_c,CVIP_FLOAT,a->data_format);
			if(b == NULL)
			break;
			msg_CVIP(	function_name,
					"Promoting Matrix to type float.\n");
			SCALE_MAT(a,b,s,a_r,a_c,0,0,byte,float)
			break;
		case CVIP_INTEGER:	/* if a integer, b is float */
			b = new_Matrix(a_r,a_c,CVIP_FLOAT,a->data_format);
			if(b == NULL)
			break;
			msg_CVIP(	function_name,
					"Promoting Matrix to type float.\n");
			SCALE_MAT(a,b,s,a_r,a_c,0,0,int,float)
			break;
		case CVIP_FLOAT:	/* a float, b float */
			b = new_Matrix(a_r,a_c,CVIP_FLOAT,a->data_format);
			if(b == NULL)
			break;
			SCALE_MAT(a,b,s,a_r,a_c,0,0,float,float)
			break;
		case CVIP_DOUBLE:	/* a double, b double */
			b = new_Matrix(a_r,a_c,CVIP_DOUBLE,a->data_format);
			if(b == NULL)
			break;
			SCALE_MAT(a,b,s,a_r,a_c,0,0,double,double)
	}
	delete_Matrix((Matrix *)a);
	return(b);
}
