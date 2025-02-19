/**************************************************************************
*	COMPUTER VISION / Image PROCESSING TOOL - Dr. Scott Umbaugh, SIUE *
*									  *
*	FILE NAME: color_adjust.c				  	  *
*									  *
*     DESCRIPTION: This file contains algorithms that adjust the	  *
*	relative colors of a color image, including routines for	  *
*	automated color balancing, adjustment of hue, and adjustment	  *
*	of saturation.  Current functions are:				  *
*		Image *balance_RGB_Setup()				  *
*									  *
*  	   AUTHOR: Arve Kjoelen, SIUE					  *
*									  *
*     CODING DATE: 10/12/95						  *
*									  *
*   LAST MODIFIED: Thu Oct 12 10:05:18 CDT 1995				  *
*									  *
*       1)  The input image is left in its original precision, so  	  *
*	that some rounding will take place when a CVIP_BYTE image is passed.   *
*	If higher precision is desired, the input image should be cast	  *
*	to a more precise type, such as CVIP_INTEGER or CVIP_FLOAT.		  *
*	2) The program will refuse to operate on images in other	  *
*	formats than RGB.  If it is desired to operate on color mages in  *
*	other color formats, they should be converted to RGB before 	  *
*	calling any of the following routines, then converted back from   *
*	RGB.								  *
*									  *
**************************************************************************/	
#include <stdio.h>
#include <string.h>
#include <CVIPtools.h>
#include <CVIPimage.h>
#include <color_adjust.h>
Image *balance_RGB_Setup(Image *inIm) {
   char *string;
   const char tokens[]=", \0";
   int xin=-1, yin=-1, xfin=-1, yfin=-1;
   float *averages;

   if(inIm->color_space != RGB || inIm->bands != 3) {
      fprintf(stderr, "Your image must be in the RGB color space\n");
      return((Image *)NULL);
   }
   string=(char *)malloc(sizeof(char)*32);
   fprintf(stdout, "Automated Color balancing:\n");
   fprintf(stdout, "==========================\n\n");
   fprintf(stdout, "This technique is based on your being able to\n");
   fprintf(stdout, "Specify a point (or region, for better results) in\n");
   fprintf(stdout, "the image where the primary colors should be of\n");
   fprintf(stderr, "of equal value.  Normally, this will be an are that\n");
   fprintf(stderr, "SHOULD appear white, but now appears tinted.\n\n");
   while(xin<0 || yin<0 || (xin > (inIm->image_ptr[0]->rows - 1)) || (yin > (inIm->image_ptr[0]->cols-1))) {
      fprintf(stderr, "Please specify the (row,column) position of the\n");
      fprintf(stderr, "Upper left-hand corner of the region: \n");
      gets(string);
      xin=atoi(strtok(string, &tokens[0]));
      yin=atoi(strtok(NULL, &tokens[0]));
   }
   string[0]='\0';
      while(xfin<xin || yfin<yin || (xfin>inIm->image_ptr[0]->rows-1) || (yfin>inIm->image_ptr[0]->cols-1)) {
      fprintf(stderr, "Please specify the (row,column) position of the\n");
      fprintf(stderr, "Lower right-hand corner of the region: \n");
      gets(string);
      xfin=atoi(strtok(string, &tokens[0]));
      yfin=atoi(strtok(NULL, &tokens[0]));
   }

   /* Find the average values of each color in the region */
   averages = (float *)aver_region(inIm, xin, yin, xfin, yfin);

   /*
    * Balance the colors by scaling Green and Blue to match 
    * the Red intensity in the region, thus obtaining 'white balance'
    */
   balance_RGB_Image(inIm, averages);
   return(inIm); 
}

float *aver_region(Image *inIm, int xin, int yin, int xfin, int yfin) {
   int cnt, k;		/* Counter variables */
   byte *bptr;		/* Pointer to image if of type CVIP_BYTE */
   short *sptr;		/* Pointer if of type CVIP_SHORT */
   int *iptr;
   float *fptr;
   double *dptr;
   float *avgs, *sums;
   int numpix;
   
   avgs=(float *)malloc(sizeof(float)*(size_t)inIm->bands);
   sums=(float *)malloc(sizeof(float)*(size_t)inIm->bands);
   numpix=(xfin-xin+1)*(yfin-yin+1);

   for(k=0; k<inIm->bands; k++) {
      sums[k]=0.0;
      cnt=0;
      switch(inIm->image_ptr[0]->data_type) {
         case CVIP_BYTE:
	    bptr=(byte *)inIm->image_ptr[k]->rptr[0]; 
	    while (cnt++ < numpix) sums[k]+= (float)*bptr++; 
         break;

         case CVIP_SHORT:
            sptr=(short *)inIm->image_ptr[k]->rptr[0];
            while (cnt++ < numpix) sums[k]+= (float)*sptr++;
         break;

         case CVIP_INTEGER:
            iptr=(int *)inIm->image_ptr[k]->rptr[0];
            while (cnt++ < numpix) sums[k]+= (float)*iptr++;
         break;

         case CVIP_FLOAT:
            fptr=(float *)inIm->image_ptr[k]->rptr[0];
            while (cnt++ < numpix) sums[k]+= (float)*fptr++;
         break;

         case CVIP_DOUBLE:
            dptr=(double *)inIm->image_ptr[k]->rptr[0];
            while (cnt++ < numpix) sums[k]+= (float)*dptr++;
         break;
      } /* switch */
   avgs[k]=(float)sums[k]/(float)numpix;
   } /* for k */
   free(sums);
   return(avgs);
}

void balance_RGB_Image(Image *inIm, float *averages) {
   int k, cnt;
   float *ptr;
   float temp;
   int numpix;

  /*
   * Normalize averages
   */ 
   (void)cast_Image(inIm, CVIP_FLOAT);
   averages[1]=averages[0]/averages[1];
   averages[2]=averages[0]/averages[2];
   numpix=(inIm->image_ptr[0]->rows)*(inIm->image_ptr[0]->cols);

   for(k=1; k<inIm->bands; k++) {
      cnt=0;
      while (cnt++ < numpix) *ptr++ *= averages[k];
   } /* for k */
}
