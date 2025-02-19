/***************************************************************************
* ======================================================================
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* ======================================================================
*
*             File Name: spatial_tools.c
*           Description: This is a series of modules designed for
*			 temporal/spatial processing of an image. So far only
*			 one function exists - convolve().
*         Related Files: Imakefile
*   Initial Coding Date: 1/15/92
*           Portability: Standard (ANSI) C
*             Credit(s): Kun Luo, Gregory Hance
*                        Southern Illinois University @ Edwardsville
*
** Copyright (C) 1993 SIUE - by Kun Luo, Gregory Hance.
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
** $Log: spatial_tools.c,v $
** Revision 1.14  1997/05/18 05:46:49  yawei
** 1) changed (const int) to floats, to eliminate warning on WIN32
** 2) renamed IN, and FIL to avoid name conflict with WIN32
**
** Revision 1.13  1997/03/08 01:02:59  yawei
** Name Changes:
** 	BOOLEAN ==> CVIP_BOOLEAN
** 	FALSE ==> CVIP_YES
** 	TRUE ==> CVIP_NO
** 	BYTE ==> CVIP_BYTE
** 	SHORT ==> CVIP_SHORT
** 	inMatrixTEGER ==> CVIP_inMatrixTEGER
** 	FLOAT ==> CVIP_FLOAT
** 	DOUBLE ==> CVIP_DOUBLE
** 	TYPE ==> CVIP_TYPE
**
** Revision 1.12  1997/01/15 17:20:42  yawei
** Global Change:  IMAGE ==> Image
**
 * Revision 1.11  1996/12/30  20:30:32  yawei
 * get_Input_Filter_sep -> specify_filter
 *
 * Revision 1.10  1996/12/24  20:43:31  yawei
 * Changed function name
 *   convolve_Image == > convolve_filter
 *
 * Revision 1.9  1996/06/10  20:25:48  akjoele
 * Changed convolve() to assume DCT symmetry about the edges.  This eliminates
 * black edges.
 *
 * Revision 1.8  1996/06/03  16:14:05  akjoele
 * Checked out by Zhen Li, in by akjoele.  zli added a setup function
 * for cviptcl.
 *
 * Revision 1.7  1995/11/02  14:22:57  akjoele
 * Changed error message to indicate which function os reporting the error.
 * Also removed exit statements and replaces them with return(NULL).
 *
 * Revision 1.6  1995/07/31  17:34:58  kluo
 * add header.
 *
 * Revision 1.5  1995/06/30  22:02:22  kluo
 * add header
 *
 * Revision 1.4  1995/06/12  14:56:19  luok
 * add difference filter
 *
 * Revision 1.3  1995/06/01  02:39:08  luok
 * add 5,7, kernel blur to it.
 *
 * Revision 1.2  1995/05/31  00:46:44  luok
 * add spatial filters.
 *
 * Revision 1.1  1995/05/30  21:54:42  luok
 * Initial revision
 *
 * Revision 1.1  1995/05/18  19:21:48  kjoelena
 * Initial revision
 *
 * Revision 1.1  1993/06/02  07:54:17  hanceg
 * Initial revision
 *
*
****************************************************************************/
#include "CVIPtools.h"
#include "CVIPimage.h"
#include "CVIPdef.h"              /* header files */
#include "CVIPfs.h"
#include "CVIPmatrix.h"
#include "CVIPspfltr.h"

/****************************************************************
                   Name: convolve_filter
          Expanded Name:    "
             Parameters: <imageP> - pointer to an Image structure
			 <filP> - pointer to Matrix containing the kernel to be
			 convolved with <imageP>.
                Returns: Returns pointer to output image.
            Description: Requires pointer to input Image, pointer to filter
			 kernel. Returns with error message if unable to
			 allocate output image.
	    Diagnostics: none
              Author(s): Kun Luo
		         Southern Illinois University @ Edwardsville
****************************************************************/

Image *convolve_filter(Image *imageP, Matrix *filP)
{
   Image *outP = (Image *) malloc(sizeof(Image));
   unsigned bands = getNoOfBands_Image(imageP);
   register int i;

   outP->bandP = (Matrix **) malloc(sizeof(Matrix*)*imageP->bands);
   outP->image_format = imageP->image_format;
   outP->color_space = imageP->color_space;
   outP->bands = imageP->bands;
   outP->story = NULL;

   if((imageP->bandP[0]->data_type<CVIP_SHORT)&&(!castImage((Image*)imageP,CVIP_SHORT))){
   /*this is for convolve, I really think sometime in the future I will change
     it (by luok May 30, 1995) */
	fprintf(stderr,"cast failed\n");
	return NULL;
   }
  
   if(filP == NULL)
	return NULL;

   for(i=0; i < bands; i++)
      outP->bandP[i] = convolve(getBand_Image(imageP,i),filP);
   
   delete_Image(imageP);
   
   return outP;
}

Image *convolve_filter_non_normalization(Image *imageP, Matrix *filP)
{
   Image *outP = (Image *) malloc(sizeof(Image));
   unsigned bands = getNoOfBands_Image(imageP);
   register int i;

   outP->bandP = (Matrix **) malloc(sizeof(Matrix*)*imageP->bands);
   outP->image_format = imageP->image_format;
   outP->color_space = imageP->color_space;
   outP->bands = imageP->bands;
   outP->story = NULL;

   if((imageP->bandP[0]->data_type<CVIP_SHORT)&&(!castImage((Image*)imageP,CVIP_SHORT))){
   /*this is for convolve, I really think sometime in the future I will change
     it (by luok May 30, 1995) */
	fprintf(stderr,"cast failed\n");
	return NULL;
   }
  
   if(filP == NULL)
	return NULL;

   for(i=0; i < bands; i++)
      outP->bandP[i] = convolve_non_normalization(getBand_Image(imageP,i),filP);
   
   delete_Image(imageP);
   
   return outP;
}


Matrix * specify_filter(int row, int col, float** temp){
    Matrix *outM;
    int x, y;
    outM = new_Matrix(row,col,CVIP_FLOAT,REAL);
    printf("\n");
    for(y = 0; y < row; y++){
	for(x = 0; x < col; x++){
	    setRealVal_Matrix(outM,float,x,y,temp[y][x]);
	}
    }
    return outM;
}



Matrix * get_default_filter(PROGRAMS type, int dimension,int direction){
    Matrix *outM;
    outM = new_Matrix(dimension,dimension,CVIP_FLOAT,REAL);
    switch(type){
	case BLUR_SPATIAL: 
	    switch(dimension){
		case 3:
	    	   setRealVal_Matrix(outM,float,0,0,1.0/16);
	    	   setRealVal_Matrix(outM,float,0,1,1.0/8);
		   setRealVal_Matrix(outM,float,0,2,1.0/16);

		   setRealVal_Matrix(outM,float,1,0,1.0/8);
		   setRealVal_Matrix(outM,float,1,1,1.0/4);
		   setRealVal_Matrix(outM,float,1,2,1.0/8);

		   setRealVal_Matrix(outM,float,2,0,1.0/16);
	 	   setRealVal_Matrix(outM,float,2,1,1.0/8);
	   	   setRealVal_Matrix(outM,float,2,2,1.0/16);
		   break;
		case 5:
	    	   setRealVal_Matrix(outM,float,0,0,0.0039);
	    	   setRealVal_Matrix(outM,float,0,1,0.0156);
		   setRealVal_Matrix(outM,float,0,2,0.0234);
		   setRealVal_Matrix(outM,float,0,3,0.0156);
		   setRealVal_Matrix(outM,float,0,4,0.0039);

		   setRealVal_Matrix(outM,float,1,0,0.0156);
		   setRealVal_Matrix(outM,float,1,1,0.0625);
		   setRealVal_Matrix(outM,float,1,2,0.0938);
		   setRealVal_Matrix(outM,float,1,3,0.0625);
		   setRealVal_Matrix(outM,float,1,4,0.0156);

		   setRealVal_Matrix(outM,float,2,0,0.0234);
	 	   setRealVal_Matrix(outM,float,2,1,0.0938);
	   	   setRealVal_Matrix(outM,float,2,2,0.1406);
		   setRealVal_Matrix(outM,float,2,3,0.0938);
		   setRealVal_Matrix(outM,float,2,4,0.0234);

		   setRealVal_Matrix(outM,float,3,0,0.0156);
		   setRealVal_Matrix(outM,float,3,1,0.0625);
		   setRealVal_Matrix(outM,float,3,2,0.0938);
		   setRealVal_Matrix(outM,float,3,3,0.0625);
		   setRealVal_Matrix(outM,float,3,4,0.0156);

		   setRealVal_Matrix(outM,float,4,0,0.0039);
		   setRealVal_Matrix(outM,float,4,1,0.0156);
		   setRealVal_Matrix(outM,float,4,2,0.0234);
		   setRealVal_Matrix(outM,float,4,3,0.0156);
		   setRealVal_Matrix(outM,float,4,4,0.0039);
		   break;
		case 7:
		   setRealVal_Matrix(outM,float,0,0,0.0002);
		   setRealVal_Matrix(outM,float,0,1,0.0015);
		   setRealVal_Matrix(outM,float,0,2,0.0037);
		   setRealVal_Matrix(outM,float,0,3,0.0049);
		   setRealVal_Matrix(outM,float,0,4,0.0037);
		   setRealVal_Matrix(outM,float,0,5,0.0015);
		   setRealVal_Matrix(outM,float,0,6,0.0002);

		   setRealVal_Matrix(outM,float,1,0,0.0015);
		   setRealVal_Matrix(outM,float,1,1,0.0088);
		   setRealVal_Matrix(outM,float,1,2,0.0220);
		   setRealVal_Matrix(outM,float,1,3,0.0293);
		   setRealVal_Matrix(outM,float,1,4,0.0220);
		   setRealVal_Matrix(outM,float,1,5,0.0088);
		   setRealVal_Matrix(outM,float,1,6,0.0015);


		   setRealVal_Matrix(outM,float,2,0,0.0037);
		   setRealVal_Matrix(outM,float,2,1,0.0220);
		   setRealVal_Matrix(outM,float,2,2,0.0549);
		   setRealVal_Matrix(outM,float,2,3,0.0732);
		   setRealVal_Matrix(outM,float,2,4,0.0549);
		   setRealVal_Matrix(outM,float,2,5,0.0220);
		   setRealVal_Matrix(outM,float,2,6,0.0037);

		   setRealVal_Matrix(outM,float,3,0,0.0049);
		   setRealVal_Matrix(outM,float,3,1,0.0293);
		   setRealVal_Matrix(outM,float,3,2,0.0732);
		   setRealVal_Matrix(outM,float,3,3,0.0977);
		   setRealVal_Matrix(outM,float,3,4,0.0732);
		   setRealVal_Matrix(outM,float,3,5,0.0293);
		   setRealVal_Matrix(outM,float,3,6,0.0049);

		   setRealVal_Matrix(outM,float,4,0,0.0037);
    		   setRealVal_Matrix(outM,float,4,1,0.0220);    
		   setRealVal_Matrix(outM,float,4,2,0.0549);
    		   setRealVal_Matrix(outM,float,4,3,0.0732);
   		   setRealVal_Matrix(outM,float,4,4,0.0549);    
		   setRealVal_Matrix(outM,float,4,5,0.0220);    
		   setRealVal_Matrix(outM,float,4,6,0.0037);

		   setRealVal_Matrix(outM,float,5,0,0.0015);
    		   setRealVal_Matrix(outM,float,5,1,0.0088);    
		   setRealVal_Matrix(outM,float,5,2,0.0220);    
		   setRealVal_Matrix(outM,float,5,3,0.0293);    
		   setRealVal_Matrix(outM,float,5,4,0.0220);
    		   setRealVal_Matrix(outM,float,5,5,0.0088);
    		   setRealVal_Matrix(outM,float,5,6,0.0015);

		   setRealVal_Matrix(outM,float,6,0,0.0002);    
		   setRealVal_Matrix(outM,float,6,1,0.0015);    
		   setRealVal_Matrix(outM,float,6,2,0.0037);    
		   setRealVal_Matrix(outM,float,6,3,0.0049);    
		   setRealVal_Matrix(outM,float,6,4,0.0037);
		   setRealVal_Matrix(outM,float,6,5,0.0015);
		   setRealVal_Matrix(outM,float,6,6,0.0002);
  	    }
	    break;
	case DIFFERENCE_SPATIAL:
	    if(direction == 0){/*horizontal*/
	    	   setRealVal_Matrix(outM,float,0,0,0.0);
	    	   setRealVal_Matrix(outM,float,0,1,1.0);
		   setRealVal_Matrix(outM,float,0,2,0.0);

		   setRealVal_Matrix(outM,float,1,0,0.0);
		   setRealVal_Matrix(outM,float,1,1,0.0);
		   setRealVal_Matrix(outM,float,1,2,0.0);

		   setRealVal_Matrix(outM,float,2,0,0.0);
	 	   setRealVal_Matrix(outM,float,2,1,-1.0);
	   	   setRealVal_Matrix(outM,float,2,2,0.0);
	    }
	    else if(direction == 1){/*vertical*/
	    	   setRealVal_Matrix(outM,float,0,0,0.0);
	    	   setRealVal_Matrix(outM,float,0,1,0.0);
		   setRealVal_Matrix(outM,float,0,2,0.0);

		   setRealVal_Matrix(outM,float,1,0,1.0);
		   setRealVal_Matrix(outM,float,1,1,0.0);
		   setRealVal_Matrix(outM,float,1,2,-1.0);

		   setRealVal_Matrix(outM,float,2,0,0.0);
	 	   setRealVal_Matrix(outM,float,2,1,0.0);
	   	   setRealVal_Matrix(outM,float,2,2,0.0);
	    }
	    break;
	case LOWPASS_SPATIAL:
	    setRealVal_Matrix(outM,float,0,0,0.1);
	    setRealVal_Matrix(outM,float,0,1,0.1);
	    setRealVal_Matrix(outM,float,0,2,0.1);

	    setRealVal_Matrix(outM,float,1,0,0.1);
	    setRealVal_Matrix(outM,float,1,1,0.2);
	    setRealVal_Matrix(outM,float,1,2,0.1);

	    setRealVal_Matrix(outM,float,2,0,0.1);
	    setRealVal_Matrix(outM,float,2,1,0.1);
	    setRealVal_Matrix(outM,float,2,2,0.1);
	    break;
	case LAPLACIAN_SPATIAL:
	    setRealVal_Matrix(outM,float,0,0,1.0);
	    setRealVal_Matrix(outM,float,0,1,-2.0);
	    setRealVal_Matrix(outM,float,0,2,1.0);

	    setRealVal_Matrix(outM,float,1,0,-2.0);
	    setRealVal_Matrix(outM,float,1,1,4.0);
	    setRealVal_Matrix(outM,float,1,2,-2.0);

	    setRealVal_Matrix(outM,float,2,0,1.0);
	    setRealVal_Matrix(outM,float,2,1,-2.0);
	    setRealVal_Matrix(outM,float,2,2,1.0);
	    break;
	case HIGHPASS_SPATIAL:
	    setRealVal_Matrix(outM,float,0,0,0.0);
	    setRealVal_Matrix(outM,float,0,1,-1.0);
	    setRealVal_Matrix(outM,float,0,2,0.0);

	    setRealVal_Matrix(outM,float,1,0,-1.0);
	    setRealVal_Matrix(outM,float,1,1,4.0);
	    setRealVal_Matrix(outM,float,1,2,-1.0);

	    setRealVal_Matrix(outM,float,2,0,0.0);
	    setRealVal_Matrix(outM,float,2,1,-1.0);
	    setRealVal_Matrix(outM,float,2,2,0.0);
	    break;	
	default:
	    fprintf(stderr,"Contact your CVIP administrator\n");
	    return NULL;
    }
    return outM;
}



 /****************************************************************
                   Name: convolve
          Expanded Name:    "
             Parameters: <inMatrix> - pointer to a MATRIX structure
			 <filMatrix> - pointer to MATRIX containing the kernel to be
			 convolved with <inMatrix>.
                Returns: Returns pointer to output matrix.
            Description: Requires pointer to input MATRIX, pointer to filter
			 kernel. Returns with error message if unable to
			 allocate output matrix.
	    Diagnostics: none
              Author(s): Gregory Hance
		         Southern Illinois University @ Edwardsville
****************************************************************/


MATRIX * convolve(Matrix * inMatrix, Matrix * filMatrix) { 
  MATRIX   * OutMatrix;

  int       row, column, i, j, normal_factor;
  int       kernel_rows, kernel_cols, dead_rows, dead_cols;
  short int *outptr, *inptr;
  float  *filptr, sumval;

/* Both matrices must be integer type */

  if (inMatrix->data_type != CVIP_SHORT){
    fprintf(stderr, "\nError: Input matrix in convolve is not CVIP_SHORT type\n");
    return(NULL);
  }

/* Allocate memory for the output matrix */

  OutMatrix = matrix_allocate(inMatrix->rows, inMatrix->cols, inMatrix->data_type, REAL);  

/* Set the size of the kernel rows and columns */ 
  kernel_rows = filMatrix->rows;
  kernel_cols = filMatrix->cols;

  dead_rows = kernel_rows/2;
  dead_cols = kernel_cols/2;
  
/* Calculate the normalization factor for the kernel matrix */
  normal_factor = 0;
  for (row=0; row<kernel_rows; row++){
    filptr = (float *) filMatrix->rptr[row];
    for (column=0; column<kernel_cols; column++)
      normal_factor += (filptr[column]);
  }

  normal_factor = abs(normal_factor);
/* Make sure the normalization factor is not 0 */
  if(!normal_factor) normal_factor = 1;

  fprintf(stderr, "\n\n");
  fprintf(stderr, "Convolving image with normal factor %d\n Row: ", normal_factor);
  for (row=0; row<(inMatrix->rows)-kernel_rows+1; row++){

    if(row%16 == 0) fprintf(stderr,"\b\b\b\b%4d",row);

    outptr = (short int *) OutMatrix->rptr[row+dead_rows];
    /*
     * primary loop - handle all but image edge pixels
     */
    for (column=0; column<(inMatrix->cols)-kernel_cols+1; column++){
      sumval = 0;
      for (i=0; i<kernel_rows; i++){
        inptr = (short int *) inMatrix->rptr[i+row];     /* row offset */
        inptr += column;             /* col offset */
        filptr = (float *) filMatrix->rptr[i];
        for (j=0; j<kernel_cols; j++)                     
           sumval += (*inptr++) * (*filptr++);
      }
      outptr[column+dead_cols] = ROUND( sumval/normal_factor );
    } /* end primary loop */

    /*
     * secondary loop1 - handle left side of image
     */
    for(column=0; column<dead_cols; column++) {
       sumval=0;
       for(i=0; i<kernel_rows; i++) {
          inptr = (short int *) inMatrix->rptr[i+row];
          filptr = (float *)filMatrix->rptr[i];
	  for(j=0; j<kernel_cols; j++)
	     sumval+= inptr[(abs)(j-dead_cols)] * (*filptr++);
       }
       outptr[column] = ROUND( sumval/normal_factor );
    } /* end secondary loop 1 */

    /*   
     * secondary loop2 - handle right side of image
     * XXX This loop doesn't look 100% OK, but the result looks good.
     */  
    for(column=inMatrix->cols-kernel_cols; column<inMatrix->cols; column++) {
       sumval=0; 
       for(i=0; i<kernel_rows; i++) {
          inptr = (short int *) inMatrix->rptr[i+row]; 
          filptr = (float *)filMatrix->rptr[i];
          for(j=0; j<kernel_cols; j++)
			sumval+=inptr[column-abs(dead_cols-j)]*(*filptr++);
//fix by Dejun Zhang, logical error in original code
//             sumval+=inptr[column+1-abs(dead_cols-j)]*(*filptr++);
       }  
       outptr[column] = ROUND( sumval/normal_factor );
    } /* end secondary loop 2 */
  }
  /*
   * loop for top part of image.
   */
   for(row=0; row<dead_rows; row++) {
      outptr=(short int *) OutMatrix->rptr[row];  
      for(column=0; column<(inMatrix->cols)-kernel_cols+1; column++) {
         sumval=0;
	 for(i=0; i<kernel_rows; i++) {
	    inptr = (short int *) inMatrix->rptr[abs(i-row)];
	    inptr+=column;
	    filptr = (float *)filMatrix->rptr[i];
            for(j=0; j<kernel_cols; j++) {
               sumval+= (*inptr++) * (*filptr++);
	    }
         }
	 outptr[column+dead_cols] = ROUND(sumval/normal_factor);
      }
   } /* end loop for top part of image */
  /*
   * loop for bottom part of image.
   */
   for(row=inMatrix->rows-kernel_rows+1; row<inMatrix->rows; row++) {
      outptr=(short int *) OutMatrix->rptr[row];
      for(column=0; column<(inMatrix->cols)-kernel_cols+1; column++) {
         sumval=0;  
         for(i=0; i<kernel_rows; i++) {
            inptr = (short int *) inMatrix->rptr[row-abs(dead_rows-i)];
            inptr+=column;
            filptr = (float *)filMatrix->rptr[i];
            for(j=0; j<kernel_cols; j++) {
               sumval+= (*inptr++) * (*filptr++);
            }
         }  
         outptr[column+dead_cols] = ROUND(sumval/normal_factor);
      }
   } /* end loop for bottom part of image */
  /*
   * corners.
   */
   for(i=0; i<dead_rows; i++) {
      outptr=(short int *)OutMatrix->rptr[i];
      for(j=0; j<dead_cols; j++)
         outptr[j]=(outptr[dead_cols]+outptr[dead_cols+1])/2;
      for(j=inMatrix->cols-dead_cols; j<inMatrix->cols; j++)
	 outptr[j]=(outptr[j-dead_cols]+outptr[j-dead_cols-1])/2;
   }
   for(i=inMatrix->rows-dead_rows; i<inMatrix->rows; i++) {
      outptr=(short int *)OutMatrix->rptr[i];
      for(j=0; j<dead_cols; j++)
         outptr[j]=(outptr[dead_cols]+outptr[dead_cols+1])/2;
      for(j=inMatrix->cols-dead_cols; j<inMatrix->cols; j++)
	 outptr[j]=(outptr[j-dead_cols]+outptr[j-dead_cols-1])/2;
   }
   fprintf(stderr, "\n");
   return(OutMatrix);  
}

MATRIX * convolve_non_normalization(Matrix * inMatrix, Matrix * filMatrix) { 
  MATRIX   * OutMatrix;

  int       row, column, i, j, normal_factor;
  int       kernel_rows, kernel_cols, dead_rows, dead_cols;
  short int *outptr, *inptr;
  float  *filptr, sumval;

/* Both matrices must be integer type */

  if (inMatrix->data_type != CVIP_SHORT){
    fprintf(stderr, "\nError: Input matrix in convolve is not CVIP_SHORT type\n");
    return(NULL);
  }

/* Allocate memory for the output matrix */

  OutMatrix = matrix_allocate(inMatrix->rows, inMatrix->cols, inMatrix->data_type, REAL);  

/* Set the size of the kernel rows and columns */ 
  kernel_rows = filMatrix->rows;
  kernel_cols = filMatrix->cols;

  dead_rows = kernel_rows/2;
  dead_cols = kernel_cols/2;
  
  normal_factor = 1;

  fprintf(stderr, "\n\n");
  fprintf(stderr, "Convolving image with normal factor %d\n Row: ", normal_factor);
  for (row=0; row<(inMatrix->rows)-kernel_rows+1; row++){

    if(row%16 == 0) fprintf(stderr,"\b\b\b\b%4d",row);

    outptr = (short int *) OutMatrix->rptr[row+dead_rows];
    /*
     * primary loop - handle all but image edge pixels
     */
    for (column=0; column<(inMatrix->cols)-kernel_cols+1; column++){
      sumval = 0;
      for (i=0; i<kernel_rows; i++){
        inptr = (short int *) inMatrix->rptr[i+row];     /* row offset */
        inptr += column;             /* col offset */
        filptr = (float *) filMatrix->rptr[i];
        for (j=0; j<kernel_cols; j++)                     
           sumval += (*inptr++) * (*filptr++);
      }
      outptr[column+dead_cols] = ROUND( sumval/normal_factor );
    } /* end primary loop */

    /*
     * secondary loop1 - handle left side of image
     */
    for(column=0; column<dead_cols; column++) {
       sumval=0;
       for(i=0; i<kernel_rows; i++) {
          inptr = (short int *) inMatrix->rptr[i+row];
          filptr = (float *)filMatrix->rptr[i];
	  for(j=0; j<kernel_cols; j++)
	     sumval+= inptr[(abs)(j-dead_cols)] * (*filptr++);
       }
       outptr[column] = ROUND( sumval/normal_factor );
    } /* end secondary loop 1 */

    /*   
     * secondary loop2 - handle right side of image
     * XXX This loop doesn't look 100% OK, but the result looks good.
     */  
    for(column=inMatrix->cols-kernel_cols; column<inMatrix->cols; column++) {
       sumval=0; 
       for(i=0; i<kernel_rows; i++) {
          inptr = (short int *) inMatrix->rptr[i+row]; 
          filptr = (float *)filMatrix->rptr[i];
          for(j=0; j<kernel_cols; j++)
			sumval+=inptr[column-abs(dead_cols-j)]*(*filptr++);
//fix by Dejun Zhang, logical error in original code
//             sumval+=inptr[column+1-abs(dead_cols-j)]*(*filptr++);
       }  
       outptr[column] = ROUND( sumval/normal_factor );
    } /* end secondary loop 2 */
  }
  /*
   * loop for top part of image.
   */
   for(row=0; row<dead_rows; row++) {
      outptr=(short int *) OutMatrix->rptr[row];  
      for(column=0; column<(inMatrix->cols)-kernel_cols+1; column++) {
         sumval=0;
	 for(i=0; i<kernel_rows; i++) {
	    inptr = (short int *) inMatrix->rptr[abs(i-row)];
	    inptr+=column;
	    filptr = (float *)filMatrix->rptr[i];
            for(j=0; j<kernel_cols; j++) {
               sumval+= (*inptr++) * (*filptr++);
	    }
         }
	 outptr[column+dead_cols] = ROUND(sumval/normal_factor);
      }
   } /* end loop for top part of image */
  /*
   * loop for bottom part of image.
   */
   for(row=inMatrix->rows-kernel_rows+1; row<inMatrix->rows; row++) {
      outptr=(short int *) OutMatrix->rptr[row];
      for(column=0; column<(inMatrix->cols)-kernel_cols+1; column++) {
         sumval=0;  
         for(i=0; i<kernel_rows; i++) {
            inptr = (short int *) inMatrix->rptr[row-abs(dead_rows-i)];
            inptr+=column;
            filptr = (float *)filMatrix->rptr[i];
            for(j=0; j<kernel_cols; j++) {
               sumval+= (*inptr++) * (*filptr++);
            }
         }  
         outptr[column+dead_cols] = ROUND(sumval/normal_factor);
      }
   } /* end loop for bottom part of image */
  /*
   * corners.
   */
   for(i=0; i<dead_rows; i++) {
      outptr=(short int *)OutMatrix->rptr[i];
      for(j=0; j<dead_cols; j++)
         outptr[j]=(outptr[dead_cols]+outptr[dead_cols+1])/2;
      for(j=inMatrix->cols-dead_cols; j<inMatrix->cols; j++)
	 outptr[j]=(outptr[j-dead_cols]+outptr[j-dead_cols-1])/2;
   }
   for(i=inMatrix->rows-dead_rows; i<inMatrix->rows; i++) {
      outptr=(short int *)OutMatrix->rptr[i];
      for(j=0; j<dead_cols; j++)
         outptr[j]=(outptr[dead_cols]+outptr[dead_cols+1])/2;
      for(j=inMatrix->cols-dead_cols; j<inMatrix->cols; j++)
	 outptr[j]=(outptr[j-dead_cols]+outptr[j-dead_cols-1])/2;
   }
   fprintf(stderr, "\n");
   return(OutMatrix);  
}

Matrix * get_matrix_setup(){
    int row, col;
    int getout = 0;
    while(!getout){
        fflush(stdin);
    	printf("Number of rows for the Matrix Filter:");
    	scanf("%d",&row);
    	printf("Number of columns for the Matrix Filter:");
    	scanf("%d",&col);
    	if(col < 7 && row < 7)
	    getout = 1;
	else{
	    fflush(stdin);
	    printf("Are you sure you want to input %d different values?(y/n)",
			(int)col*row);
	    if(getchar() == 'y')
	         getout = 1;
	}
    }
    return get_Input_Filter(row,col);
}
    
Matrix * get_Input_Filter(int row, int col){
    Matrix * new_m;
    int x, y, i;
    float **temp;
    temp = (float**)calloc(row, sizeof(float*));
    temp[0] = (float*)calloc(row*col, sizeof(float));
    for (i=1; i<row; i++)
	temp[i]=temp[0]+i*col;
    printf("\n");
    fflush(stdin);
    for(y = 0; y < row; y++){
	for(x = 0; x < col; x++){
	    printf("Matrix[%d,%d] = ",y,x);
	    scanf("%f", temp[y]+x);
	}
    }
    new_m = (Matrix*)specify_filter(row, col,(float**)temp);
    free(temp[0]);
    free(temp);
    return new_m;
}

