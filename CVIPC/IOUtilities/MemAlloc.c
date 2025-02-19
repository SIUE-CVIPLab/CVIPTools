/***************************************************************************
* ======================================================================
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* ======================================================================
*
*             File Name: MemAlloc.c
*           Description: generic vector and matrix memory management routines
*         Related Files: Imakefile, libband.a
*   Initial Coding Date: Sun Apr 11 20:56:06 CDT 1993
*           Portability: Standard (ANSI) C
*             Credit(s): Gregory Hance
*                        Southern Illinois University @ Edwardsville
*
*  Global Function List: allocMatrix3D_CVIP - allocate 3-dimensional matrix
*			 allocMatrix_CVIP - alocate 2-dimensional matrix
*		         freeMatrix_CVIP - free a matrix (2-D)
*			 allocMatrix3D_CVIP - free a matrix (3-D)
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
* $Log: MemAlloc.c,v $
* Revision 1.1  1994/10/30 17:59:00  hanceg
* CVIPtools1.0 source file - G. Hance
*
 * Revision 1.3  1993/05/18  20:47:23  hanceg
 * fixed rows/cols problem with mem_alloc.c
 *
 * Revision 1.2  1993/05/04  17:00:47  hanceg
 * fixed bug with vecalloc
 *
 * Revision 1.1  1993/05/03  05:53:16  hanceg
 * Initial revision
 *
*
*
****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "CVIPtyp.h"
#include "CVIPparse.h"
#include "CVIPmatrix.h"


/****************************************************************
                   Name: allocMatrix3D_CVIP
          Expanded Name: allocate matrix 3-Dimensional CVIP
             Parameters: <depth> - depth of matrix
			 <rows> - number of rows in matrix
			 <cols> - number of columns in matrix
			 <size> - size of each matrix element (e.g.
				  sizeof(float))
                Returns: triple pointer to a new instance of an array
			 of matrices
            Description: allocate an array of <depth> matrices each with <rows>
			 rows and <cols> cols with an element size of <size>.
			 NOTE: use freeMatrix3D_CVIP(...) to free the matrix
	    Diagnostics: returns NULL pointer w/ corresponding error message
			 upon memory allocation failure.
              Author(s): Gregory Hance
		         Southern Illinois University @ Edwardsville
****************************************************************/

void *allocMatrix3D_CVIP(unsigned int depth, unsigned int rows, unsigned int cols, size_t size)
{
byte ***matP;
register int i, j;

matP = (byte ***) malloc(depth*sizeof(byte **));
*matP = (byte **) malloc(rows*depth*sizeof(byte *));
**matP = (byte *) malloc(rows*cols*depth*size);


for(i=0; i < depth; i++) {
   matP[i] = (byte **) *matP + i*rows*sizeof(byte *);
   *matP[i] = (byte *) **matP + i*rows*cols*size;
   for(j=1; j < rows; j++)
      matP[i][j] = (byte *) *matP[i] + j*cols*size;
}

return matP;
}
/* End of function allocMatrix3D_CVIP(...) */


/****************************************************************
                   Name: allocMatrix_CVIP
          Expanded Name: allocate matrix CVIP
             Parameters: <rows> - number of rows in matrix
			 <cols> - number of columns in matrix
			 <size> - size of each matrix element (e.g.
				  sizeof(float))
                Returns: double pointer to a new instance of a matrix.
            Description: allocate an array of <rows> rows and <cols> cols with
			 an element size of <size>.
			 NOTE: use freeMatrix_CVIP(...) to free the matrix.
	    Diagnostics: returns NULL pointer w/ corresponding error message
			 upon memory allocation failure.
              Author(s): Gregory Hance
		         Southern Illinois University @ Edwardsville
****************************************************************/


void *allocMatrix_CVIP(unsigned int rows, unsigned int cols, size_t size)
{
byte **matP;
register int i;

matP = (byte **) malloc(rows*sizeof(byte *));
*matP = (byte *) malloc(rows*cols*size);

for(i=1; i < rows; i++)
   matP[i] = (byte *) *matP + i*cols*size;

return matP;
} 
/* End of function allocMatrix_CVIP(...) */


/****************************************************************
                   Name: freeMatrix_CVIP
          Expanded Name: free matrix CVIP
             Parameters: <matP> - pointer to matrix allocated w/ matalloc
			 <number_of_planes> - depth of matrix (number of
			 data bands)
                Returns: nada
            Description: free the memory associated with a matrix allocated
			 by allocMatrix_CVIP
	    Diagnostics: none
              Author(s): Gregory Hance
		         Southern Illinois University @ Edwardsville
****************************************************************/

void freeMatrix_CVIP(void *matP)
{

free(*((void**)matP));
free(matP);

} /* End of function freeMatrix_CVIP(...) */


/****************************************************************
                   Name: freeMatrix3D_CVIP
          Expanded Name: free matrix 3-Dimensional CVIP
             Parameters: <matP> - pointer to matrix allocated w/ matalloc
			 <number_of_planes> - depth of matrix (number of
			 data bands)
                Returns: nada
            Description: free the memory associated with a matrix allocated
			 by allocMatrix3D_CVIP
	    Diagnostics: none
              Author(s): Gregory Hance
		         Southern Illinois University @ Edwardsville
****************************************************************/

void freeMatrix3D_CVIP(void *matP)
{

free(**((void***)matP));
free(*((void***)matP));
free(matP);

} /* End of function freeMatrix3D_CVIP(...) */

