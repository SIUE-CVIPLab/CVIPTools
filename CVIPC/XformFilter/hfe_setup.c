/*****************************************************************************
 * ======================================================================    *
 * Image Processing/Computer Vision Tool Project - Dr. Scott Umbaugh SIUE    *
 * ======================================================================    *
 *                                                                           *
 * ROUTINE/PGM NAME: hfe_setup.c                                             *
 *                                                                           *
 *                   High Freq Emphasis Filter setup                         *
 *              DESCRIPTION: This function is designed to setup the          *
 * High Frequency Emphasis  filter. It prompt the user to see dc is to       *
 *  be retained and high freq boost factor and                               *
 * for cut off frequency. It also determines (By type of transform) whether  * 
 * to call the filtering routine directly or to call another setup routine   *
 * called cn_setup().                                                        *
 * This filter can also be called independently without using this setup     *
 *  It uses a BUtterworth filter program.                                    *
 *                                                                           *
 * Note: Any newly created transform need to be added to the                 *
 *       switch(transform) statement with dcpos=1 if the dc is in the        *
 *       center of the spectrum or dcpos=2 if it is at the top left corner   *
 *       of the spectrum.                                                    *  
 *                                                                           *
 *                   AUTHOR: Simon Low                                       *
 *                                                                           *
 *            RELATED FILES: filter.c, cn_setup.c                            *
 *                                                                           *
 *              CODING DATE: 1/15/92                                         *
 *  LAST MODIFICATIONS MADE: 6/21/94   seu                                   *
 *                                                                           *
 *****************************************************************************
RCS (Revision Control System) Information - Added automatically by RCS)

$Author: yawei $
$Date: 1997/01/15 17:14:07 $
$Source: /export/home_faculty/cvipapps/CVIPtools3.5/XFORMFILTER/RCS/hfe_setup.c,v $
$Header: /export/home_faculty/cvipapps/CVIPtools3.5/XFORMFILTER/RCS/hfe_setup.c,v 1.7 1997/01/15 17:14:07 yawei Exp $

*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "CVIPtools.h"
#include "CVIPimage.h"
#include "CVIPxformfilter.h"

Image *
hfe_setup(
	Image 		*in_Image, 
	PROGRAMS	transform
)
{
  int dc, dcpos;
  float alfa;
  int block_size, filtertype=0;
  char DC[2];
  HISTORY stuff;
  int order;
  int cut=0, maxi=0;

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
    default: /* used for unsetup transform, assuming dc at center*/ 
       dcpos=1;
       fprintf(stdout, "Was your previous transform an FFT ? (y/n)\n");
       (void)gets(DC);
       if((DC[0]!='y') && (DC[0]!='Y')) dcpos=2;
       printf("\nEnter block size used for previous forward transform: ");
       scanf("%d", &block_size);
       getchar();
  }

  if (dcpos==1) maxi = block_size/2;
  else maxi=block_size;

  while(cut <= 0 || cut > maxi){
    printf("\nMin: 1 Max: %d \n",maxi);
    printf("\nPlease Enter Cutoff Frequency: ");
    scanf("%d",&cut);
    getchar(); 
  }
  while(order < 1 || order > 8){
    printf("\nPlease Enter Butterworth Filter Order: ");
    scanf("%d",&order);
    getchar(); 
    printf("Order = %d",order);
  }

  filtertype = 9;
  if ( dcpos == 1) { /* dc in center */
        printf("\n Enter Emphasis Offset Value: ");
        scanf("%f",&alfa);
        getchar();
    in_Image=(Image *)High_Freq_Emphasis(in_Image,block_size,dc,cut,alfa,order);
    return in_Image;
  }
  else { 
    in_Image=(Image *)nonfft_xformfilter(in_Image,block_size,dc,filtertype,cut,alfa,order);
    return in_Image;
  }
}
