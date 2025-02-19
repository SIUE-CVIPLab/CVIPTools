/***************************************************************************
* ======================================================================
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* ======================================================================
*
*             File Name: bandcast.c
*           Description: cast image bands to a specified type
*         Related Files: Imakefile, libband.a, libmatrix.a
*   Initial Coding Date: 11/01/92
*           Portability: Standard (ANSI) C
*             Credit(s): Gregory Hance
*                        Southern Illinois University @ Edwardsville
*
** Copyright (C) 1993 SIUE - by Gregory Hance.
**
** Permission to use, copy, modify, and distribute this software and its
** documentation for any purpose and without fee is hereby granted, provided
** that the above copyright notice appear in all copies and that both that
** copyright notice and this permission notice appear in supporting
** documentation.  This software is provided "as is" without express or
** implied warranty.
**
* RCS (Revision Control System) Information
* ...Added automatically by RCS 
*
* $Log: bandcast.c,v $
* Revision 1.4  1998/03/31 04:37:21  achomai
* Cleaned bandcast :
* 1.  Changed MATRIX to Matrix.
* 2.  Changed matrix_allocate to new_Matrix.
* 3.  Used error_CVIP instead of fprintf for printing error messages.
* 4.  Removed an unused for-loop (probably an error from copying.)
* 5.  In case of allocation failure, partially allocated objects will
*     be freed before returning NULL.
*
* Revision 1.3  1997/03/08 00:58:27  yawei
* Name Changes:
* 	BOOLEAN ==> CVIP_BOOLEAN
* 	FALSE ==> CVIP_YES
* 	TRUE ==> CVIP_NO
* 	BYTE ==> CVIP_BYTE
* 	SHORT ==> CVIP_SHORT
* 	INTEGER ==> CVIP_INTEGER
* 	FLOAT ==> CVIP_FLOAT
* 	DOUBLE ==> CVIP_DOUBLE
* 	TYPE ==> CVIP_TYPE
*
* Revision 1.2  1996/08/09 15:11:05  akjoele
* Changed function prototype for ANSI C conformity.
*
 * Revision 1.1  1996/08/09  15:09:51  akjoele
 * Initial revision
 *
 * Revision 1.1  1996/08/09  15:08:51  akjoele
 * Initial revision
 *
 * Revision 1.1  1993/05/03  05:53:15  hanceg
 * Initial revision
 *
*
*
****************************************************************************/

#include "stdlib.h"
#include "stdio.h"
#include "CVIPmatrix.h"


/****************************************************************
                   Name: bandcast
          Expanded Name: Band Cast
             Parameters: <srcBANDS> - pointer to an array of Matrix pointers
			 <no_of_bands> - number of spectral data bands
			 <data_type> - data type to be promoted to
                Returns: pointer to new array of Matrix pointers cast into
			 the specified data type
            Description: cast the data of an image pointed to by <srcBANDS?
			 into a more precise type.
	    Diagnostics: returns with NULL pointer and error message when
			 cast cannot be performed.
              Credit(s): Greg Hance, Arve Kjoelen
****************************************************************/

Matrix **bandcast(Matrix **srcBANDS, int no_of_bands, CVIP_TYPE data_type)
{
	Matrix		**desBANDS;
	int		i,rows,cols;
	FORMAT		format;
	const char	fn[] = {"bandcast"};
   
	/* simplify variables */
	rows = srcBANDS[0]->rows;
	cols = srcBANDS[0]->cols;
	format = srcBANDS[0]->data_format;
   
	if (!(desBANDS = (Matrix **) malloc(no_of_bands*sizeof(Matrix *))) ) {
		error_CVIP(fn,"Could not allocate new data bands for image.\n");
		return NULL;
	}
   
	for(i = 0; i < no_of_bands; i++) {
		desBANDS[i] = new_Matrix(rows,cols,data_type,format);
		if(desBANDS[i] == NULL)
		break;
		(void) copy_Matrix(srcBANDS[i], desBANDS[i]);
	}
	if(i == no_of_bands)
	return(desBANDS);
	error_CVIP(fn,"Could not allocate new matrix for data band.\n");
	if(i != 0)
	do{
		i--;
		delete_Matrix(desBANDS[i]);
	}while(i != 0);
	free(desBANDS);
	return(NULL);
}
