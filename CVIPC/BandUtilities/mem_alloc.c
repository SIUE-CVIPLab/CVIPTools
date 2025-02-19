/***************************************************************************
* ======================================================================
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* ======================================================================
*
*             File Name: mem_manage.c
*           Description: generic vector and matrix memory management routines
*         Related Files: Imakefile, libband.a
*   Initial Coding Date: Sun Apr 11 20:56:06 CDT 1993
*           Portability: Standard (ANSI) C
*             Credit(s): Gregory Hance
*                        Southern Illinois University @ Edwardsville
*
*  Global Function List: vecalloc - allocate a vector
*			 matalloc - alocate a matrix
*		         vecfree - free a vector
*			 matfree - free a matrix
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
* $Log: mem_alloc.c,v $
* Revision 1.4  1998/03/31 03:39:38  achomai
* Cleaned the following functions :
* vecalloc :
* 1.  Fixed error in memory allocation.  Argument to calloc should be
*     size, not sizeof(size).
* 2.  Checked for allocation failure.  Partially allocated objects will
*     be freed before the function returns NULL.
* matalloc :
* 1.  Removed unused local variable, imgdim.
* 2.  Fixed error in memory allocation.  Argument to calloc should be
*     size, not sizeof(size).
* 3.  Checked for allocation failure.  Partially allocated objects will
*     be freed before the function returns NULL.
*
* Revision 1.3  1993/05/18 20:47:23  hanceg
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
#include "CVIPalloc.h"


/****************************************************************
                   Name: vecalloc
          Expanded Name: Vector Allocate
             Parameters: <no_of_vecs> - number of vectors to allocate
			 <vdim> - dimension of each vector
			 <size> - size of each vector element (e.g.
				  sizeof(float))
                Returns: double pointer to a new instance of an array of vectors
            Description: allocate an array of <no_of_vecs> vectors each of size
			 <vdim> with an element size of <size>.
			 NOTE: use vecfree(...) to free the vector
	    Diagnostics: returns NULL pointer w/ corresponding error message
			 upon memory allocation error
              Credit(s): Gregory Hance
		         Southern Illinois University @ Edwardsville
****************************************************************/

void *vecalloc( unsigned int no_of_vecs, unsigned int vdim, size_t size )
{
	byte **vecP;
	register int i = 0;

	vecP = (byte **)malloc(no_of_vecs*sizeof(byte *));
	if(vecP != NULL)
	{
		for(i = 0;i < no_of_vecs;i++)
		{
			vecP[i] = (byte *)calloc(vdim,size);
			if(vecP[i] == NULL)
			break;
		}
		if(i == no_of_vecs)
		return(vecP);
		if(i != 0)
		do{
			i--;
			free(vecP[i]);
		}while(i != 0);
		free(vecP);
	}
	return(NULL);
} /* End of function vecalloc(...) */


/****************************************************************
                   Name: matalloc
          Expanded Name: Matrix Allocate
             Parameters: <depth> - depth of matrix
			 <rows> - number of rows in matrix
			 <cols> - number of columns in matrix
			 <size> - size of each matrix element (e.g.
				  sizeof(float))
                Returns: triple pointer to a new instance of an array
			 of matrices
            Description: allocate an array of <depth> matrices each with <rows>
			 rows and <cols> cols with an element size of <size>.
			 NOTE: use matfree(...) to free the matrix
	    Diagnostics: returns NULL pointer w/ corresponding error message
			 upon memory allocation failure.
              Credit(s): Gregory Hance
		         Southern Illinois University @ Edwardsville
****************************************************************/

void *matalloc(unsigned int depth, unsigned int rows, unsigned int cols,
               size_t size)
{
	byte		***matP;
	register int	i,j;


	matP = (byte ***)malloc(depth*sizeof(byte **));
	if(matP != NULL)
	{
		for(i = 0;i < depth;i++)
		{
			matP[i] = (byte **)malloc(rows*sizeof(byte *));
			if(matP[i] == NULL)
			break;
			*matP[i] = (byte *)calloc(rows*cols,size);
			if(*matP[i] == NULL)
			{
				free(matP[i]);
				break;
			}
			for(j=1; j < rows; j++)
			matP[i][j] = (byte*) *matP[i] + j*cols*size;
		}
		if(i == depth)
		return(matP);
		if(i != 0)
		do{
			i--;
			free(matP[i]);
		}while(i != 0);
		free(matP);
	}
	return(NULL);
} /* End of function matalloc(...) */


/****************************************************************
                   Name: vecfree
          Expanded Name: Vector Free
             Parameters: <vecP> - pointer to vector allocated w/ vecalloc
			 <number_of_vecs> - number of vectors (number of
			 data bands)
                Returns: nada
            Description: free the memory associated with a vector allocated
			 by vecalloc
	    Diagnostics: none
              Credit(s): Gregory Hance
		         Southern Illinois University @ Edwardsville
****************************************************************/

void vecfree(void *vecP, unsigned int no_of_vecs)
{
	register int i;
	void **freevecP = (void **)vecP;

	for(i=0; i < no_of_vecs; i++)
	free(freevecP[i]);
	free(freevecP);
} /* End of function vecfree(...) */



/****************************************************************
                   Name: matfree
          Expanded Name: Matrix Free
             Parameters: <matP> - pointer to matrix allocated w/ matalloc
			 <number_of_planes> - depth of matrix (number of
			 data bands)
                Returns: nada
            Description: free the memory associated with a matrix allocated
			 by matalloc
	    Diagnostics: none
              Credit(s): Gregory Hance
		         Southern Illinois University @ Edwardsville
****************************************************************/

void matfree(void *matP, unsigned int no_of_planes)
{
	register int	i;
	void		***freematP = (void ***) matP;

	for(i=0; i < no_of_planes; i++) {
		free(*freematP[i]);
		free(freematP[i]);
	}
	free(freematP);
} /* End of function matfree(...) */
