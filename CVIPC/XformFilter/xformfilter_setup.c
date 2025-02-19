/***************************************************************************
*									   *
* ======================================================================== *
*  COMPUTER VISION/Image PROCESSING TOOL PROJECT - Dr. Scott Umbaugh, SIUE *
* ======================================================================== *
*									   *
*	FILE NAME: xformfilter_setup.c					   *
*									   *
*	DESCRIPTION: Contains setup function for transform_domain filtering*
*		     routines.						   *
*									   *
*	AUTHOR : Arve Kjoelen, SIUE					   *
*									   *
*	INITIAL CODING DATE: 01/11/94					   *
*									   *
*	RELATED FILES: filter.c lpf_setup.c hpf_setup.c bpf_setup.c        *
*		       brf_setup.c hfe_setup.c cn_setup.c		   *
*									   *
***************************************************************************/
#include "CVIPimage.h"
#include "CVIPdef.h"
#include "CVIPtools.h"
#include "CVIPxformfilter.h"
Image *
xformfilter_setup(
	Image 		*in_Image, 
	CVIP_BOOLEAN 	*remap, 
	unsigned 	filter
) 
{
   PROGRAMS i, *progs;
   char *answer;
   MATRIX **matrix;
   HISTORY h_story;
   int c;


   if((!history_check(WALSH, in_Image)) && (!history_check(FFT, in_Image)) && (!history_check(DCTXFORM, in_Image)) && (!history_check(WAVELET, in_Image))) {
      fprintf(stdout, "Warning: These filtering routines were written for use with\n");
      fprintf(stdout, "the FFT, Walsh and DCT transforms.  Since you have not performed\n");
      fprintf(stdout, "any of these transforms on the current image, it is possible that\n");
         fprintf(stdout, "this routine will not produce meaningful results.  Do you\n");
         fprintf(stdout, "still wish to continue? (y/n)\n");
         answer=(char *)malloc(32);
         (void)gets(answer);
         if(answer[0]!='y') {
            *remap=0;
            free(answer);
            return(Image*)NULL;
         }
         free(answer);
      }
      c=0;
      progs=(PROGRAMS *)malloc(sizeof(PROGRAMS)*4);
      progs[0]=DCTXFORM; progs[1]=FFT; progs[2]=WALSH; progs[3]=WAVELET;
      c=getlast_Hist(in_Image, progs, 4);
/*
      for(i=DCTXFORM; i<=WAVELET; i+=2) {
         if(history_check(i, in_Image)) {
            c=i;
            break;
         }
      }
*/
      i=c;
      if(in_Image->image_ptr[0]->data_type!=CVIP_FLOAT) { 
         matrix=(MATRIX **)in_Image->image_ptr;
         castImage(in_Image, CVIP_FLOAT);
         for(c=0; c<in_Image->bands; c++) delete_Matrix(matrix[c]);
         free(matrix);
      }

      /* Add information to image history */
      if(filter<6) {
         h_story=(HISTORY)malloc(sizeof(struct history));
         h_story->next=(HISTORY)NULL;
         h_story->packetP=(PACKET *)malloc(sizeof(PACKET));
	 h_story->packetP->dtype=(CVIP_TYPE*)malloc(sizeof(CVIP_TYPE));
	 *(h_story->packetP->dtype)=CVIP_INTEGER;
	 h_story->packetP->dsize=1;
	 h_story->packetP->dptr = (void **)malloc(sizeof(void*));
 	 h_story->packetP->dptr[0]=(int *)malloc(sizeof(int));
	 memcpy((void *)h_story->packetP->dptr[0], (void *)&filter, 
			sizeof(int));
         h_story->ftag=XFORMFILTER;
         history_add(in_Image, h_story);
      }
      switch(filter) {
         case 1: in_Image = (Image *)hpf_setup(in_Image, i); break;
         case 2: in_Image = (Image *)lpf_setup(in_Image, i); break;
         case 3: in_Image = (Image *)bpf_setup(in_Image, i); break;
         case 4: in_Image = (Image *)brf_setup(in_Image, i); break;
         case 5: in_Image = (Image *)hfe_setup(in_Image, i); break;
         default: fprintf(stdout, "xformfilter_setup: Unrecognized filter\n");
                  *remap=0;
                  return(Image *)NULL;
      }
   *remap=CVIP_NO;
   return(in_Image);         
}

