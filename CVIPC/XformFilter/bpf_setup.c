/*****************************************************************************
 * ======================================================================    *
 * Image Processing/Computer Vision Tool Project - Dr. Scott Umbaugh SIUE    *
 * ======================================================================    *
 *                                                                           *
 * ROUTINE/PGM NAME: bpf_setup.c                                             *
 *                                                                           *
 *                    Band Pass filters setup                                *
 *              DESCRIPTION: This function is designed to setup both the     *
 * Ideal Band Pass and Butterworth Band Pass filter. It prompt the user to   *
 * see if the dc value is to be retained, for cut off frequencies, and for   *
 * filter order if butterworth filter is requested. It also determines       *
 * whether to call the filtering routine directly or to call another setup   *
 * routine called cn_setup().                                                *
 * These band pass filters can be called independently without using this    *
 * setup program.                                                            *
 *                                                                           *
 * Note: Any newly created transform need to be added to the                 *
 *       switch(transform) statement with dcpos=1 if the dc value is in      *
 *       center of the spectrum or dcpos=2 if the dc value is at the         *
 *       top left corner of the spectrum.                                    *
 *                                                                           *
 *                   AUTHOR: Simon Low                                       *
 *                                                                           *
 *            RELATED FILES: filter.c, cn_setup.c                            *
 *                                                                           *
 *              CODING DATE: 1/15/92                                         *
 *  LAST MODIFICATIONS MADE: 11/18/92                                        *
 *                                                                           *
 *****************************************************************************
RCS (Revision Control System) Information - Added automatically by RCS)

$Author: yawei $
$Date: 1997/01/15 17:14:00 $
$Source: /export/home_faculty/cvipapps/CVIPtools3.5/XFORMFILTER/RCS/bpf_setup.c,v $
$Header: /export/home_faculty/cvipapps/CVIPtools3.5/XFORMFILTER/RCS/bpf_setup.c,v 1.9 1997/01/15 17:14:00 yawei Exp $

*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "CVIPtools.h"
#include "CVIPimage.h"
#include "CVIPxformfilter.h"

Image *
bpf_setup(
	Image 		*in_Image, 
	PROGRAMS	transform
)
{
  int dc, dcpos;
  int block_size, choice, filtertype=0;
  char DC[2];
  HISTORY stuff;
  int order;
  int inner=0, outer=0, maxi=0;

  printf("\nRetain DC Value (Y/N) ?: ");
  scanf("%s", &DC);
  getchar();
  if (DC[0] == 'Y' || DC[0] == 'y')
    dc = 1;
  else
    dc = 0;

  switch(transform) {
    case WALSH:
       stuff=history_get(in_Image, WALSH);
       GET_HIST_DATA(stuff,0,block_size);
       dcpos = 2; /* corner */
       break;
    case HADAMARD:
       stuff=history_get(in_Image, HADAMARD);
       GET_HIST_DATA(stuff,0,block_size);
       dcpos = 2; 
       break;
    case FFT:
       stuff=history_get(in_Image, FFT);
       GET_HIST_DATA(stuff,0,block_size);
       dcpos=1;
       break;
    case DCTXFORM:
       stuff=history_get(in_Image, DCTXFORM);
       GET_HIST_DATA(stuff,0,block_size);
       dcpos=2;
       break; 
    case WAVELET:
       dcpos=2;
       block_size=in_Image->image_ptr[0]->rows;
       break;
    default: /* used for unsetup transform, assuming dc at canter */ 
       dcpos=1;
       fprintf(stdout, "Was your previous transform an FFT ? (y/n)\n");
       (void)gets(DC);
       if((DC[0]!='y') && (DC[0]!='Y')) dcpos=2;
       printf("\nEnter block size used for previous forward transform: ");
       scanf("%d", &block_size);
       getchar();
  }

 while(choice !=3) {

  printf("\n Band Pass Filters\n");
  printf("===================\n");
  printf("\n 1. Ideal Band Pass Filter\n");
  printf("\n 2. Butterworth Band Pass Filter\n");
  printf("\n 3. Go back to Previous menu\n");
  printf("\n Please enter your choice: ");
  scanf("%d", &choice);
  getchar();

  if (dcpos==1) maxi = block_size/2;
  else maxi=block_size;

  while(inner<1 || outer<1 || inner> maxi || outer>maxi || outer < inner) {
    printf("\nMin: 1 Max: %d \n",maxi);
    printf("Please Enter Lower Cutoff Frequency: ");
    scanf("%d", &inner);
    getchar(); 
    printf("\nPlease Enter Higher Cutoff Frequency: ");
    scanf("%d", &outer);
    getchar(); 
    if(outer < inner)
      printf("\nHigher cutoff (%d) can not < Lower cutoff(%d) !\n",outer,inner);
  }

  switch(choice) {
    case 1:  /* Ideal Band Pass */ 
      filtertype = 5;
      if ( dcpos == 1) { /* dc in center */
        in_Image=(Image *)Ideal_Band_Pass(in_Image,block_size,dc,inner,outer);
      }
      else { /* 0 filter order since this is not Butterworth */
        in_Image=(Image *)nonfft_xformfilter(in_Image,block_size,dc,filtertype,inner,outer,0);
      }
    return in_Image;
    case 2: /* Butterworth Band Pass */
        order = 0; 
        while ( order < 1 || order > 8) {
          printf("\nEnter filter order (1-8) : ");
          scanf("%d", &order);
          getchar();
        }
        filtertype = 6;
        if ( dcpos == 1) {
          in_Image=(Image *)Butterworth_Band_Pass(in_Image,block_size,dc,inner,outer,order);
        }
        else {
          in_Image =(Image *)nonfft_xformfilter(in_Image,block_size,dc,filtertype,inner, outer,order);
        }
        return in_Image;
    case 3:
        fprintf(stderr, "\nreturning unprocessed image.\n");
        return in_Image;
    default:
        printf("\nTry again !\n");
        break;
    }
 }
return(NULL);
}
