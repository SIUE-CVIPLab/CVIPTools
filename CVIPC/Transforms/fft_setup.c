/*****************************************************************************
 * ======================================================================    *
 * Image Processing/Computer Vision Tool Project - Dr. Scott Umbaugh SIUE    *
 * ======================================================================    *
 *                                                                           *
 * ROUTINE/PGM NAME: fft_setup.c                                             *
 *                                                                           *
 *              DESCRIPTION: This function is designed to setup the fft      *
 * operation and it is called by the main program with an image pointer.     *
 * From here forward fft or inverse fft can be called. fft and inverse fft   *
 * can also be called independently with correct parameters.                 *
 *                                                                           *
 *                   AUTHOR: Simon Low                                       *
 *                                                                           *
 *            RELATED FILES: ifft_transform.c, fourn.c, filter.c, util.c        *
 *                                                                           *
 *              CODING DATE: 1/15/92                                         *
 *  LAST MODIFICATIONS MADE: 11/18/92                                        *
 *                                                                           *
 *****************************************************************************
RCS (Revision Control System) Information - Added automatically by RCS)

$Author: yawei $
$Date: 1997/03/08 17:05:39 $
$Source: /export/home_faculty/cvipapps/CVIPtools3.5/TRANSFORMS/RCS/fft_setup.c,v $
$Header: /export/home_faculty/cvipapps/CVIPtools3.5/TRANSFORMS/RCS/fft_setup.c,v 1.9 1997/03/08 17:05:39 yawei Exp $

*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "CVIPtools.h"
#include "CVIPdef.h" 
#include "CVIPtoolkit.h"
#include "CVIPimage.h"
#include "CVIPtransform.h"


Image *fft_setup(Image *in_Image, CVIP_BOOLEAN *remap)
{
  int n, block_size, choice=0, *hptr;
  HISTORY stuff=NULL;

  *remap=CVIP_YES;

  while (choice != 3) {

    printf("\n Fast Fourier Transform \n");
    printf(" =======================\n");
    printf("\n 1. Forward Transform\n");
    printf("\n 2. Inverse Transform\n");
    printf("\n 3. Previous Menu\n"); 
    printf("\n Please enter your choice: ");
    scanf("%d", &choice);
    getchar();

  switch(choice) {

     case 1:
       printf("\nPossible block size are: 16,32,64,128,256 etc\n");
       printf("\nEnter Square Block Size (power of 2): ");
       scanf("%d", &n);
       getchar();
       while(n!=2 && n!=4 && n!=8 && n!=16 && n!=32 && n!=64 && n!=128 && n!=256 && n!=512 && n!=1024) {
         fprintf(stderr,"\nBlock size not power of 2 !");
         printf("\nEnter Square Block Size(power of 2): ");
         scanf("%d", &n);
         getchar();
       }
       block_size = n;
       in_Image = (Image *) fft_transform(in_Image, block_size);
       stuff=(HISTORY)malloc(sizeof(struct history));
       stuff->packetP = (PACKET *)malloc(sizeof(PACKET));
       stuff->packetP->dsize=1;
       stuff->packetP->dtype=(CVIP_TYPE *)malloc(sizeof(CVIP_TYPE));
       stuff->packetP->dtype[0]=CVIP_INTEGER;
       hptr=(int *)malloc(sizeof(int));
       hptr[0]=block_size;
       stuff->packetP->dptr = (void**)malloc(sizeof(void*));
       stuff->packetP->dptr[0]=(int *)hptr;
       stuff->packetP->dsize = 1;
       stuff->next=(HISTORY)NULL;
       stuff->ftag=FFT;
       history_add(in_Image, stuff);       
       return in_Image;

     case 2:
       if(!history_check(FFT, in_Image)) {
          printf("\nEnter the block size used for forward fft: ");
          scanf("%d", &block_size);
          getchar();
       }
       else {
          stuff=history_get(in_Image, FFT);
          GET_HIST_DATA(stuff,0,block_size);
       }
       if(in_Image->image_ptr[0]->data_format!=COMPLEX) {
	  fprintf(stderr, "Warning:  The input image is REAL.\n");
	  fprintf(stderr, "Creating all-zero complex part...\n");
	  for(choice=0; choice<in_Image->bands; choice++) (void)makeComplex_Matrix(in_Image->image_ptr[choice],CVIP_YES);
       }
       in_Image = (Image *)ifft_transform(in_Image, block_size);
       stuff=NULL;
       stuff=(HISTORY)malloc(sizeof(struct history));
       stuff->packetP = (PACKET *)malloc(sizeof(PACKET));
       stuff->packetP->dsize=1;
       stuff->packetP->dtype=(CVIP_TYPE *)malloc(sizeof(CVIP_TYPE));
       stuff->packetP->dtype[0]=CVIP_INTEGER;
       hptr=(int *)malloc(sizeof(int));
       hptr[0]=block_size;
       stuff->packetP->dptr = (void**)malloc(sizeof(void*));
       stuff->packetP->dptr[0]=(int *)hptr;
       stuff->packetP->dsize = 1;
       stuff->next=(HISTORY)NULL;
       stuff->ftag=I_FFT;
       history_add(in_Image, stuff);           
       return in_Image;
    case 3:
       *remap=CVIP_NO;
       return in_Image;
    default:
       break;
   }  
 }  
  return in_Image;
}
