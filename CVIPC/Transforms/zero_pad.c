/************************************************************************
*									*
* ===================================================================== *
*    Computer Vision/Image Processing Tool - Dr. Scott Umbaugh, SIUE	*
* ===================================================================== *
*									*
*	PGM/FILE NAME: zero_pad.c					*
*									*
*	  DESCRIPTION: Contains algorithms that zero-pad an image.	*
*									*
*	       AUTHOR: Arve Kjoelen, SIUE 				*
*									*
*   PARAMETERS PASSED: Image *image - a pointer to an image structure	*
*		       to be zero-padded.				*
*									*
*		       int n_rows, n_cols - Dimensions of new image	*
*		       after zero-padding.				*
*									*
*	      RETURNS: nothing (the zero-padded image is contained in 	*
*		       the passed Image pointer).			*
*									*
* INITIAL CODING DATE: 05/03/94						*
*									*
************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <CVIPmatrix.h>
#include <CVIPimage.h>
#include <CVIPtransform.h>
#include <CVIPtools.h>

void 
zero_pad(
	Image 	*image, 
	unsigned int 	n_rows, 
	unsigned int 	n_cols
) 
{
   	MATRIX 	*t_matrix, *temp;
	FORMAT format;
   	int 	i, j, k, rows, cols, *h_ptr;
   	byte 	**brptr, **biptr, *bptr, **btrptr, **btiptr, *btptr;
   	float 	**rptr, **iptr, *ptr, **trptr, **tiptr, *tptr;
   	HISTORY story;

   	fprintf(stdout,
	"Zero-padding image to %d rows by %d cols...\n", n_rows, n_cols);

      	rows=getNoOfRows_Image(image);
      	cols=getNoOfCols_Image(image);
	format = getDataFormat_Image(image);

   	for(k=0; k<image->bands; k++) {
      		if(image->image_ptr[0]->data_type==CVIP_FLOAT) {
			if (format == REAL)
         			t_matrix=new_Matrix(n_rows, n_cols, CVIP_FLOAT, REAL);
			else 
         			t_matrix=new_Matrix(n_rows, n_cols, CVIP_FLOAT, COMPLEX);
         		rptr=(float **)getRealData_Image(image,k);
         		trptr=(float **)getRealData_Matrix(t_matrix);
         		for(i=0; i<rows; i++) {
            			ptr=(float *)rptr[i];
            			tptr=(float *)trptr[i];
            			for(j=0; j<cols; j++) {
               				tptr[j]=ptr[j];
            			}
         		}
			if (format == COMPLEX) {
	         		iptr=(float **)getImagData_Image(image,k);
       	  			tiptr=(float **)getImagData_Matrix(t_matrix);
       	  			for(i=0; i<rows; i++) {
       	     				ptr=(float *)iptr[i]; tptr=(float *)tiptr[i];
       	     				for(j=0; j<cols; j++) tptr[j]=ptr[j];
       	  			}
			}
         		temp=(MATRIX *)image->image_ptr[k];
         		delete_Matrix(temp);
         		image->image_ptr[k]=(MATRIX *)t_matrix;
         		t_matrix=NULL;
      		}
      		else if(image->image_ptr[0]->data_type==CVIP_BYTE) {
			if (format == REAL)
         			t_matrix=new_Matrix(n_rows, n_cols, CVIP_BYTE, REAL);  
			else
         			t_matrix=new_Matrix(n_rows, n_cols, CVIP_BYTE, COMPLEX);
			brptr=(byte **)getRealData_Image(image,k);
         		btrptr=(byte **)getRealData_Matrix(t_matrix);
         		for(i=0; i<rows; i++) {
            			bptr=(byte *)brptr[i];
            			btptr=(byte *)btrptr[i];
            			for(j=0; j<cols; j++) {
               				btptr[j]=bptr[j];
            			}
         		}
			if (format == COMPLEX) {
				biptr=(byte **)getImagData_Image(image,k);
         			btiptr=(byte **)getImagData_Matrix(t_matrix);
         			for(i=0; i<rows; i++) {
            				bptr=(byte *)biptr[i]; btptr=(byte *)btiptr[i];
            				for(j=0; j<cols; j++) btptr[j]=bptr[j];
         			}
			}
         		temp=(MATRIX *)image->image_ptr[k];
         		delete_Matrix(temp);
         		image->image_ptr[k]=(MATRIX *)t_matrix;
         		t_matrix=NULL;
      		}
      		else {
         		fprintf(stderr, "zero_pad data type: only CVIP_FLOAT and CVIP_BYTE supported\n");
         		exit(0);
      		}
	}
	
   	/*story=(HISTORY)malloc(sizeof(struct history));
   	story->packetP = (PACKET *)malloc(sizeof(PACKET));
   	story->packetP->dsize=4;
   	h_ptr=(int *)malloc(sizeof(int)*4);
   	h_ptr[0]=rows;
   	h_ptr[1]=cols;
   	h_ptr[2]=n_rows;
   	h_ptr[3]=n_cols;
   	story->packetP->dptr = (void**)malloc(sizeof(void*)*4);
   	story->packetP->dptr[0]=(int *)h_ptr;
	story->packetP->dptr[1]=(int *)h_ptr + 1;
	story->packetP->dptr[2]=(int *)h_ptr + 2;
	story->packetP->dptr[3]=(int *)h_ptr + 3;
	story->packetP->dtype = (CVIP_TYPE *)malloc(sizeof(CVIP_TYPE)*4);
	for(k =0; k < 4; k++)
	    story->packetP->dtype[k] = CVIP_INTEGER;
   	story->next=(HISTORY)NULL;
   	story->ftag=ZERO_PAD;
   	history_add(image, story);  */

   	return;
}

