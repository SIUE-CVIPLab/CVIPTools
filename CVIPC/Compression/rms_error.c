/***************************************************************************
* **********************************************************************
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* **********************************************************************
*
*             File Name: rms_error.c
*           Description: This file contain a routines that compute the  
*                        total error, the root mean squared error, and the
*			 signal to noise ratio between two images.   
*       	         The error is computed in each band, and the
*	                 total ms error is also calculated. 
*         Related Files: 
*   Initial Coding Date: 10/7/93
*           Portability: Standard (ANSI) C
*            References: Arve Kjoelen MS Thesis, SIUE 1994
*             Author(s): Arve Kjoelen, Scott Umbaugh
*                        Southern Illinois University @ Edwardsville
*          							
*	DIAGNOSTICS: Both Images must have the same size and number of	
*		     color bands. RMS error requires BYTE images since it is 
*                    based on relative magnitudes. Any data type will work
*                    but the range needs to be ~about 0-255 for a
*                    meaningful result.
*
** Copyright (C) 1996 SIUE - by Scott Umbaugh and Arve Kjoelen.
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
** $Log: rms_error.c,v $
** Revision 1.8  1998/03/10 04:44:34  smakam
** included functionality to display a error message when trying to find snr for images of different sizes
**
** Revision 1.7  1997/08/06 17:02:19  wzheng
** avoid delete image before out of function
**
** Revision 1.6  1997/06/20 16:04:10  wzheng
** *** empty log message ***
**
** Revision 1.5  1997/05/16 02:34:18  yawei
** check back changes
**
*
****************************************************************************/						
#include <math.h>
#include "CVIPimage.h"
#include "CVIPmap.h"
#include "CVIPdef.h"

/* Root mean square error function */

float *rms_error(Image *image1, Image *image2) {
   float *error, temperr;
   int i, j, k, rows, cols;
   CVIP_TYPE dtype=CVIP_BYTE;

   if(image1->bands!=image2->bands) {
      fprintf(stderr, "Your images must have the same # of spectral bands!\n");
      if (image1) delete_Image(image1);
      if (image2) delete_Image(image2);
      return((float *)NULL);
   }
   if(image1->bandP[0]->rows!=image2->bandP[0]->rows || image1->bandP[0]->cols!=image2->bandP[0]->cols) {
      fprintf(stderr, "rms_error: images must be os same size\n");
      if (image1) delete_Image(image1);
      if (image2) delete_Image(image2);
      return(NULL);
   }
   dtype=MAX(image1->bandP[0]->data_type,image2->bandP[0]->data_type);

   if((image1->image_ptr[0]->data_type<dtype))
      (void)cast_Image(image1, dtype);
   if((image2->image_ptr[0]->data_type<dtype))
      (void)cast_Image(image2, dtype);


   error = (float *)(calloc((image1->bands+1), sizeof(float)));

   for(k=0; k<image1->bands; k++) {
      rows = (int)image1->image_ptr[k]->rows;
      cols = (int)image1->image_ptr[k]->cols;
      temperr=0.0;
      for(i=0; i<rows; i++) {
         for(j=0; j<cols; j++) {
            switch(dtype) {
               case CVIP_BYTE:
               temperr+=(float)SQR(((byte *)image1->bandP[k]->rptr[i])[j]-((byte *)image2->bandP[k]->rptr[i])[j]);
               break;
               case CVIP_SHORT:
               temperr+=(float)SQR(((short *)image1->bandP[k]->rptr[i])[j]-((short *)image2->bandP[k]->rptr[i])[j]);
               break;
               case CVIP_INTEGER:
               temperr+=(float)SQR(((int *)image1->bandP[k]->rptr[i])[j]-((int *)image2->bandP[k]->rptr[i])[j]);
               break;
               case CVIP_FLOAT:
               temperr+=(float)SQR(((float *)image1->bandP[k]->rptr[i])[j]-((float *)image2->bandP[k]->rptr[i])[j]);
               break;
               case CVIP_DOUBLE:
               temperr+=(float)SQR(((double *)image1->bandP[k]->rptr[i])[j]-((double *)image2->bandP[k]->rptr[i])[j]);
               break;
            }
         }
      }
      error[k]=temperr;
      error[k]= sqrt (error[k]/(float)(rows*cols));
      error[image1->bands]+=temperr;
   }
/*
   if (image1) delete_Image(image1);
   if (image2) delete_Image(image2); 
*/
   return(error);
}

/* Total error function */

float *tot_error(Image *image1, Image *image2) {
   float *error, temperr;
   int i, j, k, rows, cols;
   CVIP_TYPE dtype=CVIP_BYTE;

   if(image1->bands!=image2->bands) {
      fprintf(stderr, "Your images must have the same # of spectral bands!\n");
      return((float *)NULL);
   }
   if(image1->bandP[0]->rows!=image2->bandP[0]->rows || image1->bandP[0]->cols!=image2->bandP[0]->cols) {
      fprintf(stderr, "rms_error: images must be os same size\n");
      return(NULL);
   }
   dtype=MAX(image1->bandP[0]->data_type,image2->bandP[0]->data_type);

   if((image1->image_ptr[0]->data_type<dtype))
      (void)cast_Image(image1, dtype);
   if((image2->image_ptr[0]->data_type<dtype))
      (void)cast_Image(image2, dtype);


   error = (float *)(calloc((image1->bands+1), sizeof(float)));

   for(k=0; k<image1->bands; k++) {
      rows = (int)image1->image_ptr[k]->rows;
      cols = (int)image1->image_ptr[k]->cols;
      temperr=0.0;
      for(i=0; i<rows; i++) {
         for(j=0; j<cols; j++) {
            switch(dtype) {
               case CVIP_BYTE:
               temperr+=(float)SQR(((byte *)image1->bandP[k]->rptr[i])[j]-((byte *)image2->bandP[k]->rptr[i])[j]);
               break;
               case CVIP_SHORT:
               temperr+=(float)SQR(((short *)image1->bandP[k]->rptr[i])[j]-((short *)image2->bandP[k]->rptr[i])[j]);
               break;
               case CVIP_INTEGER:
               temperr+=(float)SQR(((int *)image1->bandP[k]->rptr[i])[j]-((int *)image2->bandP[k]->rptr[i])[j]);
               break;
               case CVIP_FLOAT:
               temperr+=(float)SQR(((float *)image1->bandP[k]->rptr[i])[j]-((float *)image2->bandP[k]->rptr[i])[j]);
               break;
               case CVIP_DOUBLE:
               temperr+=(float)SQR(((double *)image1->bandP[k]->rptr[i])[j]-((double *)image2->bandP[k]->rptr[i])[j]);
               break;
            }
         }
      }
      error[k]=temperr;
      error[image1->bands]+=temperr;
   }
   return(error);
}


/************************************************************************
*									*
*		MASTER'S THESIS - ARVE KJOELEN				*
*		==============================				*
*									*
*	ROUTINE/PGM NAME: snr()						*
*									*
*	DESCRIPTION:  This routine calculates the SNR for a 		*
*	reconstructed image when passed the total squared errors.	*
*	As such, a call to this function must be preceded by a call to	*
*	the function tot_error.						*
*									*
*	AUTHOR: Arve Kjoelen						*
*									*
*	DIAGNOSTICS:							*
*	- This function works only on CVIP_BYTE images, since the SNR 	*
*	requires that we take into account the accuracy/range of	*
*	the data.							*
*	- This function does not free the float pointer passed to it.	*
*	INITIAL CODING DATE: 10/7/93					*
*									*
*	LAST MODIFICATIONS MADE: 10/7/93, 5/6/97-Scott Umbaugh		*
*									*
************************************************************************/
float *snr(Image *img1, Image *img2) {
   float *snr, *error, temp;
   int k, rows, cols;

   if(img1->bandP[0]->data_type != CVIP_BYTE || (img2->bandP[0]->data_type!=CVIP_BYTE)) {
      fprintf(stderr, "Only byte images supported for SNR\n");
   }
   if(img1->bandP[0]->rows!=img2->bandP[0]->rows || img1->bandP[0]->cols!=img2->bandP[0]->cols) {
      fprintf(stderr, "snr error: images must be os same size\n");
      if (img1) delete_Image(img1);
      if (img2) delete_Image(img2);
      return(NULL);
   }
   snr =  (float *)calloc(((img1->bands)+1), sizeof(float));

   error=tot_error(img1, img2);
   
   for(k=0; k<img1->bands; k++) {
      rows = (int)img1->image_ptr[k]->rows;
      cols = (int)img1->image_ptr[k]->cols;

      if(error[k]<1.0) {
      	snr[k] = -1.0;
	fprintf(stderr, "No error!\n");
      } else snr[k] = 10*log10( (float) (rows*cols*65025.0)/error[k]);
   }
   if(img1->bands==1)
      snr[img1->bands]=snr[0];
   else
      snr[img1->bands]=10*log10(img1->bands* (float)(rows*cols*65025.0)/ error[img1->bands]);

   free(error);
/*
   if (img1) delete_Image(img1);
   if (img2) delete_Image(img2); 
*/
   return(snr);
}
