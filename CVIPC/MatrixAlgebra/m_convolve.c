/* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
======================================================================

             File Name: m_convolve.c
           Description: contains libmatrix.a routines for convolving
                        two matrices or perform filtering.
         Related Files: Makefile, CVIPmatrix.h
   Initial Coding Date: 12/5/96
           Portability: Standard (ANSI) C
             Credit(s): Arve Kjoelen, E.E. Dept. SIUE


****************************************************************************

** Copyright (C) 1996 SIUE - by Scott Umbaugh, Arve Kjoelen.
**
** Permission to use, copy, modify, and distribute this software and its
** documentation for any purpose and without fee is hereby granted, provided
** that the above copyright notice appear in all copies and that both that
** copyright notice and this permission notice appear in supporting
** documentation.  This software is provided "as is" without express or
** implied warranty.

*****************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "CVIPmatrix.h"

/*
 * Program name: convolve_Matrix()
 *
 * Description:
 *	Convolves two matrices with each other.  Returns
 *	a pointer to the result.  Supports all data types.
 * 	Does not support complex matrices.  Matrices passed are 
 *	freed, so that higher-level functions must make copies if
 *	they wish to reuse.
 *
 * Parameters passed:
 *	Matrix *mat1, Matrix *mat2 - pointers to the two matrices.
 *
 *	int handle - indicates which underlying assumptions should
 *	    be used in the filtering process:
 *	handle = 0 - Assume FFT symmetry (perform circular convolution).
 *	handle = 1 - Assume DCT symmetry (Matrix flipped along its edges).
 *	handle = 2 - Leave edge pixels intact (no filtering of edges).
 *	handle = 3 - Set edge pixels to zero (unfiltered pixels set to zero).
 *	handle = 4 - Set edge pixels equal to their closest non-edge neighbors.
 *		     (zero-order hold).
 *	handle = 5 - crop result, returning only filtered part.
 *	handle = 6 - zero-pad mat1, performing a true convolution/correlation.
 *
 *	int ctr - whether to "center" the filter mask before convolving.
 *	    ctr=0 -> don't center.  ctr=1-> center.  Centering moves
 *	    mat2 up and to the left before initial filtering.
 *
 * Author: Arve Kjoelen, SIUE (akjoele@ee.siue.edu)
 *
 * Initial Coding: Wed Dec 11 09:02:45 CST 1996
 *
 */
Matrix *convolve_Matrix(Matrix *mat1, Matrix *mat2, int handle, const int ctr) {
	Matrix		*res;					/* result */
	int		i,j,k,l;				/* counters */
	int		rows,cols,frows,fcols,nrows,ncols;	/* size of 
								matrices*/
	int		drows, dcols;		/* Number of "dead rows/cols", 
						or edge rows/cols */
	CVIP_TYPE	mintp, maxtp, newtp;
	short		ssum;
	int		isum;
	float		fsum;
	double		dsum;
	char		*FuncName = "convolve_Matrix";

	if(mat1->data_format==COMPLEX || mat2->data_format==COMPLEX) {
		error_CVIP(FuncName,"Complex data format not supported.\n");
		delete_Matrix(mat1);
		delete_Matrix(mat2);
		return(NULL);
	}

/*
 * The purpose of the following is to find the
 * proper data type for the output matrix.
 * The output data type will be the most precise
 * of the two input data types unless:
 * - the two data types are identical, and equal
 *   to CVIP_BYTE or CVIP_SHORT.
 * As a result, there is a small possibility of
 * overflow when:
 * - One image is CVIP_BYTE, the other CVIP_SHORT or CVIP_INTEGER.
 * - Both images are CVIP_INTEGER.
 */
   if(mat1->data_type <= mat2->data_type) {
      mintp=mat1->data_type;
      maxtp=mat2->data_type;
   }
   else {
      mintp=mat2->data_type;
      maxtp=mat1->data_type;
   }
   if(mintp==maxtp) { /* input matrices are of same type */
      if(mintp==CVIP_BYTE)
         newtp=CVIP_SHORT;
      else if(mintp==CVIP_SHORT)
         newtp=CVIP_INTEGER;
      else 
         newtp=mintp;
   } 
   else /* input matrices are not of same type */
      newtp=maxtp;

/*
 * Cast matrices to most precise data type.
 */
   	res=clone_Matrix(mat1, newtp);
	if(res == NULL)
	{
		delete_Matrix(mat1);
		delete_Matrix(mat2);
		return(NULL);
	}
	(void)copy_Matrix(mat1, res);
	delete_Matrix(mat1);
	mat1=res;

	res=clone_Matrix(mat2, newtp);
	if(res == NULL)
	{
		delete_Matrix(mat1);
		delete_Matrix(mat2);
		return(NULL);
	}
	(void)copy_Matrix(mat2, res);
	delete_Matrix(mat2);
	mat2=res;
	res=NULL; 

/*
 * You never know how this function will be called, so
 * let's make sure mat1 has the largest dimensions.  If not,
 * interchange mat1 and mat2. Also, look critically at
 * the matrix dimensions.  There is no sense in attempting
 * to filter a 640x480 image with a 512x512 filter.  The only
 * exception is when the filtering type is convolution.
 */
   if(mat1->rows <= mat2->rows && mat1->cols <= mat2->cols) {
      res=mat1;
      mat1=mat2;
      mat2=res;
   }
   else if (!(mat1->rows > mat2->rows && mat1->cols > mat2->cols)) {
      if(handle!=6) {
		error_CVIP(FuncName,"Unsupported matrix sizes.\n");
		delete_Matrix(mat1);
		delete_Matrix(mat2);
		return(NULL);
      }
   }
/*
 * drows and dcols are the number of "dead"  or edge rows and columns.
 */
   drows=(int)(mat2->rows)/2;
   dcols=(mat2->cols)/2;

/*
 * Determine size of output matrix and allocate.
 */
   if(handle < 5) {
      nrows=mat1->rows;
      ncols=mat1->cols;
   }
   else if(handle == 5) { /* cropping the image */
      nrows=mat1->rows - 2*drows;
      ncols=mat1->cols - 2*dcols;
   }
   else if(handle == 6) { /* true convolution */
      nrows=mat1->rows + mat2->rows -1;
      ncols=mat1->cols + mat2->cols -1;
   }
   else {
	error_CVIP(FuncName,"Unsupported value for 'handle'.\n");
	delete_Matrix(mat1);
	delete_Matrix(mat2);
	return(NULL);
   }
   res=new_Matrix(nrows, ncols, newtp, REAL);

/*
 * Figure out which type of convolution to do, and execute.
 */
   frows=mat2->rows;
   fcols=mat2->cols;
   rows=mat1->rows;
   cols=mat1->cols;

/*
 * In general, we're trying to optimize here:
 * instead of reinventing the wheel each time we move our convolution mask a step,
 * we will retain our sum and compute our new result by only considering the
 * difference introduced by moving the mask.  The larger the mask size,
 * the greater is our benefit from doing this.  Note that we're also
 * centering the convolution mask, if asked for.
 */
   if(handle==0) { /* FFT symmetry */
      switch(newtp) {
         case CVIP_SHORT:
         ssum=0;
         for(k=0; k<frows; k++) {
            for(l=0; l<fcols; l++) {
               ssum+=((short *)mat2->rptr[k])[l]*((short *)mat1->rptr[(rows+k-(ctr==0 ? 0 : drows))%(rows-1)])[(cols+l-(ctr==0 ? 0 : dcols))%(cols-1)];
            }
         }
         ((short *)res->rptr[0])[0]=ssum;
         for(i=0; i<nrows; i++) {
            if(i%2) { /* we are going right-to-left on this row. */
               for(j=ncols-1; j>=0; j--) {
                  if(j==(ncols-1)) { /* end of line, must do funky stuff */
                     for(l=0; l<fcols; l++) {
                        ssum+=((short *)mat2->rptr[0])[l]*((short *)mat1->rptr[(rows+i-(ctr==0 ? 0 : drows))%(rows-1)])[(cols+j+l-(ctr==0 ? 0 : dcols))%(cols-1)];
                        ssum-=((short *)mat2->rptr[frows-1])[l]*((short *)mat1->rptr[(rows+i+frows-1-(ctr==0 ? 0 : drows))%(rows-1)])[(cols+j+l-(ctr==0 ? 0 : dcols))%(cols-1)];
                     }
                  }
                  else { /* not end of line, this happens most of the time */
                     for(k=0; k<frows; k++) {
                        ssum-=((short *)mat2->rptr[k])[0]*((short *)mat1->rptr[(rows+i+k-(ctr==0 ? 0 : drows))%(rows-1)])[(cols+j-(ctr==0 ? 0 : dcols))%(cols-1)];
                        fsum+=((short *)mat2->rptr[k])[fcols-1]*((short *)mat1->rptr[(rows+i+k-(ctr==0 ? 0 : drows))%(rows-1)])[(cols+j+fcols-1-(ctr==0 ? 0 : dcols))%(cols-1)];
                     }
                  }
                  ((short *)res->rptr[i])[j]=ssum;
               }
            }
            else { /* we are going left-to-right on this row. */
               for(j=0; j<ncols; j++) {
                  if( i && j ) { /* not beginning of line; this happens most of the time */
                     for(k=0; k<frows; k++) {
                        ssum-=((short *)mat2->rptr[k])[0]*((short *)mat1->rptr[(rows+i+k-(ctr==0 ? 0 : drows))%(rows-1)])[(cols+j-(ctr==0 ? 0 : dcols))%(cols-1)];
                        ssum+=((short *)mat2->rptr[k])[fcols-1]*((short *)mat1->rptr[(rows+i+k-(ctr==0 ? 0 : drows))%(rows-1)])[(cols+j+fcols-1-(ctr==0 ? 0 : dcols))%(cols-1)];
                     }
                  }
                  else if ( i && !j) { /* beginning of line; */
                     for(l=0; l<fcols; l++) {
                        ssum-=((short *)mat2->rptr[0])[l]*((short *)mat1->rptr[(rows+i-(ctr==0 ? 0 : drows))%(rows-1)])[(cols+j+l-(ctr==0 ? 0 : dcols))%(cols-1)];
                        ssum+=((short *)mat2->rptr[fcols-1])[l]*((short *)mat1->rptr[(rows+i+frows-1-(ctr==0 ? 0 : drows))%(rows-1)])[(cols+j+l-(ctr==0 ? 0 : dcols))%(cols-1)];
                     }
                  }
                  ((short *)res->rptr[i])[j]=ssum;
               }
            }
         }
         break;
         case CVIP_INTEGER:
         isum=0;
         for(k=0; k<frows; k++) {
            for(l=0; l<fcols; l++) {
               isum+=((int *)mat2->rptr[k])[l]*((int *)mat1->rptr[(rows+k-(ctr==0 ? 0 : drows))%(rows-1)])[(cols+l-(ctr==0 ? 0 : dcols))%(cols-1)];
            }
         }
         ((int *)res->rptr[0])[0]=isum;
         for(i=0; i<nrows; i++) {
            if(i%2) { /* we are going right-to-left on this row. */
               for(j=ncols-1; j>=0; j--) {
                  if(j==(ncols-1)) { /* end of line, must do funky stuff */
                     for(l=0; l<fcols; l++) {
                        isum+=((int *)mat2->rptr[0])[l]*((int *)mat1->rptr[(rows+i-(ctr==0 ? 0 : drows))%(rows-1)])[(cols+j+l-(ctr==0 ? 0 : dcols))%(cols-1)];
                        isum-=((int *)mat2->rptr[frows-1])[l]*((int *)mat1->rptr[(rows+i+frows-1-(ctr==0 ? 0 : drows))%(rows-1)])[(cols+j+l-(ctr==0 ? 0 : dcols))%(cols-1)];
                     }
                  }
                  else { /* not end of line, this happens most of the time */
                     for(k=0; k<frows; k++) {
                        isum-=((int *)mat2->rptr[k])[0]*((int *)mat1->rptr[(rows+i+k-(ctr==0 ? 0 : drows))%(rows-1)])[(cols+j-(ctr==0 ? 0 : dcols))%(cols-1)];
                        fsum+=((int *)mat2->rptr[k])[fcols-1]*((int *)mat1->rptr[(rows+i+k-(ctr==0 ? 0 : drows))%(rows-1)])[(cols+j+fcols-1-(ctr==0 ? 0 : dcols))%(cols-1)];
                     }
                  }
                  ((int *)res->rptr[i])[j]=isum;
               }
            }
            else { /* we are going left-to-right on this row. */
               for(j=0; j<ncols; j++) {
                  if( i && j ) { /* not beginning of line; this happens most of the time */
                     for(k=0; k<frows; k++) {
                        isum-=((int *)mat2->rptr[k])[0]*((int *)mat1->rptr[(rows+i+k-(ctr==0 ? 0 : drows))%(rows-1)])[(cols+j-(ctr==0 ? 0 : dcols))%(cols-1)];
                        isum+=((int *)mat2->rptr[k])[fcols-1]*((int *)mat1->rptr[(rows+i+k-(ctr==0 ? 0 : drows))%(rows-1)])[(cols+j+fcols-1-(ctr==0 ? 0 : dcols))%(cols-1)];
                     }
                  }
                  else if ( i && !j) { /* beginning of line; */
                     for(l=0; l<fcols; l++) {
                        isum-=((int *)mat2->rptr[0])[l]*((int *)mat1->rptr[(rows+i-(ctr==0 ? 0 : drows))%(rows-1)])[(cols+j+l-(ctr==0 ? 0 : dcols))%(cols-1)];
                        isum+=((int *)mat2->rptr[fcols-1])[l]*((int *)mat1->rptr[(rows+i+frows-1-(ctr==0 ? 0 : drows))%(rows-1)])[(cols+j+l-(ctr==0 ? 0 : dcols))%(cols-1)];
                     }
                  }
                  ((int *)res->rptr[i])[j]=isum;
               }
            }
         }
         break;
         case CVIP_FLOAT:
         fsum=0.0;
         for(k=0; k<frows; k++) {
            for(l=0; l<fcols; l++) {
               fsum+=((float *)mat2->rptr[k])[l]*((float *)mat1->rptr[(rows+k-(ctr==0 ? 0 : drows))%(rows-1)])[(cols+l-(ctr==0 ? 0 : dcols))%(cols-1)];
            }
         }
         ((float *)res->rptr[0])[0]=fsum;
         for(i=0; i<nrows; i++) {
            if(i%2) { /* we are going right-to-left on this row. */
               for(j=ncols-1; j>=0; j--) {
                  if(j==(ncols-1)) { /* end of line, must do funky stuff */
                     for(l=0; l<fcols; l++) {
                        fsum+=((float *)mat2->rptr[0])[l]*((float *)mat1->rptr[(rows+i-(ctr==0 ? 0 : drows))%(rows-1)])[(cols+j+l-(ctr==0 ? 0 : dcols))%(cols-1)];
                        fsum-=((float *)mat2->rptr[frows-1])[l]*((float *)mat1->rptr[(rows+i+frows-1-(ctr==0 ? 0 : drows))%(rows-1)])[(cols+j+l-(ctr==0 ? 0 : dcols))%(cols-1)];
                     }
                  }
                  else { /* not end of line, this happens most of the time */
                     for(k=0; k<frows; k++) {
                        fsum-=((float *)mat2->rptr[k])[0]*((float *)mat1->rptr[(rows+i+k-(ctr==0 ? 0 : drows))%(rows-1)])[(cols+j-(ctr==0 ? 0 : dcols))%(cols-1)];
                        fsum+=((float *)mat2->rptr[k])[fcols-1]*((float *)mat1->rptr[(rows+i+k-(ctr==0 ? 0 : drows))%(rows-1)])[(cols+j+fcols-1-(ctr==0 ? 0 : dcols))%(cols-1)];
                     }
                  }
	       ((float *)res->rptr[i])[j]=fsum;
               }
            }
            else { /* we are going left-to-right on this row. */
               for(j=0; j<ncols; j++) {
                  if( i && j ) { /* not beginning of line; this happens most of the time */
                     for(k=0; k<frows; k++) {
                        fsum-=((float *)mat2->rptr[k])[0]*((float *)mat1->rptr[(rows+i+k-(ctr==0 ? 0 : drows))%(rows-1)])[(cols+j-(ctr==0 ? 0 : dcols))%(cols-1)];
                        fsum+=((float *)mat2->rptr[k])[fcols-1]*((float *)mat1->rptr[(rows+i+k-(ctr==0 ? 0 : drows))%(rows-1)])[(cols+j+fcols-1-(ctr==0 ? 0 : dcols))%(cols-1)];
                     }
                  }
                  else if ( i && !j) { /* beginning of line; */
                     for(l=0; l<fcols; l++) {
                        fsum-=((float *)mat2->rptr[0])[l]*((float *)mat1->rptr[(rows+i-(ctr==0 ? 0 : drows))%(rows-1)])[(cols+j+l-(ctr==0 ? 0 : dcols))%(cols-1)];
                        fsum+=((float *)mat2->rptr[fcols-1])[l]*((float *)mat1->rptr[(rows+i+frows-1-(ctr==0 ? 0 : drows))%(rows-1)])[(cols+j+l-(ctr==0 ? 0 : dcols))%(cols-1)];
                     }
                  }
	       ((float *)res->rptr[i])[j]=fsum;
               }
            }
         }
         break;
         case CVIP_DOUBLE:
         dsum=0;
         for(k=0; k<frows; k++) {
            for(l=0; l<fcols; l++) {
               dsum+=((double *)mat2->rptr[k])[l]*((double *)mat1->rptr[(rows+k-(ctr==0 ? 0 : drows))%(rows-1)])[(cols+l-(ctr==0 ? 0 : dcols))%(cols-1)];
            }
         }
         ((double *)res->rptr[0])[0]=dsum;
         for(i=0; i<nrows; i++) {
            if(i%2) { /* we are going right-to-left on this row. */
               for(j=ncols-1; j>=0; j--) {
                  if(j==(ncols-1)) { /* end of line, must do funky stuff */
                     for(l=0; l<fcols; l++) {
                        dsum+=((double *)mat2->rptr[0])[l]*((double *)mat1->rptr[(rows+i-(ctr==0 ? 0 : drows))%(rows-1)])[(cols+j+l-(ctr==0 ? 0 : dcols))%(cols-1)];
                        dsum-=((double *)mat2->rptr[frows-1])[l]*((double *)mat1->rptr[(rows+i+frows-1-(ctr==0 ? 0 : drows))%(rows-1)])[(cols+j+l-(ctr==0 ? 0 : dcols))%(cols-1)];
                     }
                  }
                  else { /* not end of line, this happens most of the time */
                     for(k=0; k<frows; k++) {
                        dsum-=((double *)mat2->rptr[k])[0]*((double *)mat1->rptr[(rows+i+k-(ctr==0 ? 0 : drows))%(rows-1)])[(cols+j-(ctr==0 ? 0 : dcols))%(cols-1)];
                        fsum+=((double *)mat2->rptr[k])[fcols-1]*((double *)mat1->rptr[(rows+i+k-(ctr==0 ? 0 : drows))%(rows-1)])[(cols+j+fcols-1-(ctr==0 ? 0 : dcols))%(cols-1)];
                     }
                  }
                  ((double *)res->rptr[i])[j]=dsum;
               }
            }
            else { /* we are going left-to-right on this row. */
               for(j=0; j<ncols; j++) {
                  if( i && j ) { /* not beginning of line; this happens most of the time */
                     for(k=0; k<frows; k++) {
                        dsum-=((double *)mat2->rptr[k])[0]*((double *)mat1->rptr[(rows+i+k-(ctr==0 ? 0 : drows))%(rows-1)])[(cols+j-(ctr==0 ? 0 : dcols))%(cols-1)];
                        dsum+=((double *)mat2->rptr[k])[fcols-1]*((double *)mat1->rptr[(rows+i+k-(ctr==0 ? 0 : drows))%(rows-1)])[(cols+j+fcols-1-(ctr==0 ? 0 : dcols))%(cols-1)];
                     }
                  }
                  else if ( i && !j) { /* beginning of line; */
                     for(l=0; l<fcols; l++) {
                        dsum-=((double *)mat2->rptr[0])[l]*((double *)mat1->rptr[(rows+i-(ctr==0 ? 0 : drows))%(rows-1)])[(cols+j+l-(ctr==0 ? 0 : dcols))%(cols-1)];
                        dsum+=((double *)mat2->rptr[fcols-1])[l]*((double *)mat1->rptr[(rows+i+frows-1-(ctr==0 ? 0 : drows))%(rows-1)])[(cols+j+l-(ctr==0 ? 0 : dcols))%(cols-1)];
                     }
                  }
                  ((double *)res->rptr[i])[j]=dsum;
               }
            }
         }
         break;
      }
   }
   delete_Matrix(mat1);
   delete_Matrix(mat2);
   return(res);
}
