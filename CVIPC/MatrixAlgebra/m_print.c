/***************************************************************************
======================================================================
Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
======================================================================
                                                                      
             File Name: m_print.c
           Description: contains libmatrix.a module for printing
			the contents of a MATRIX structure.
         Related Files: Makefile, CVIPmatrix.h
   Initial Coding Date: 1/24/93
           Portability: Standard (ANSI) C
             Credit(s): Gregory Hance, E.E. Dept. SIUE

  Global Function List: matrix_print - print the contents of a matrix
			
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
$Date: 1998/04/19 03:00:51 $                                                        
$Source: /home/cvip/cvipapps/CVIPtools3.7/MatrixAlgebra/RCS/m_print.c,v $                                                         
$Header: /home/cvip/cvipapps/CVIPtools3.7/MatrixAlgebra/RCS/m_print.c,v 1.4 1998/04/19 03:00:51 achomai Exp $

*****************************************************************************/

#include "stdlib.h"
#include "stdio.h"
#include "CVIPmatrix.h"

/****************************************************************
                  Name: matrix_print
         Expanded Name: Matrix Print
            Parameters: <A> - pointer to venerable MATRIX structure
               Returns: None
           Description: Prints out the contents of a matrix structure
			in row - column format.
           Diagnostics: Row 1:  <col.1>  <col.2> ... <col.N>
			  .        .        .            .
			  .        .        .            .
			Row N:  <col.1> <col.3> ...  <col.N>
             Credit(s): Greg Hance
			
			
****************************************************************/
void matrix_print(const MATRIX *A)
{
    int i,j,cols_lin;
    
    if( (A->data_type == CVIP_SHORT) || (A->data_type == CVIP_INTEGER) || (A->data_type == CVIP_BYTE) )
        cols_lin = 10;       /* 10 per line for int */
    else
        cols_lin = 5;        /* 5 per line for float types */
    
    if(A->data_format == COMPLEX)
       cols_lin--;

    
       for(i = 0 ; i < A->rows ; i++) {
          for(j = 0 ; j < A->cols ; j++) {
             if(j%cols_lin == 0) {    /* newline every cols_lin */
                if(j == 0)           /* start of row */
                   fprintf(stderr,"\nRow%3d:",i);
                else
                   fprintf(stderr,"\n       ");
             }
             switch(A->data_type) {
	        case CVIP_BYTE:
                   fprintf(stderr,"%7d",((byte **)A->rptr)[i][j]);
		   if(A->data_format==COMPLEX)
		      fprintf(stderr," + %d I",((byte **)A->iptr)[i][j]);
                   break;
                case CVIP_INTEGER:
                   fprintf(stderr,"%7d",((int **)A->rptr)[i][j]);
		   if(A->data_format==COMPLEX)
		      fprintf(stderr," + %d I",((int **)A->iptr)[i][j]);
                   break;
                case CVIP_SHORT:
                   fprintf(stderr,"%7d",((short **)A->rptr)[i][j]);
		   if(A->data_format==COMPLEX)
		      fprintf(stderr," + %d I",((short **)A->iptr)[i][j]);
                   break;
                case CVIP_FLOAT:
                   fprintf(stderr,"%14.5g",((float **)A->rptr)[i][j]);
	           if(A->data_format==COMPLEX)
		      fprintf(stderr," + %g I",((float **)A->iptr)[i][j]);
                   break;
                case CVIP_DOUBLE:
                   fprintf(stderr,"%14.5lg",((double **)A->rptr)[i][j]);
		   if(A->data_format==COMPLEX)
	              fprintf(stderr," + %lg I",((double **)A->iptr)[i][j]);
		   break;
             }
         }
      }
fprintf(stderr,"\n");
}
