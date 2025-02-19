/*****************************************************************************
 * ======================================================================    *
 * Image Processing/Computer Vision Tool Project - Dr. Scott Umbaugh SIUE    *
 * ======================================================================    *
 *                                                                           *
 * ROUTINE/PGM NAME: inverse_fft.c                                           *
 *                                                                           *
 *              DESCRIPTION: This function performs inverse fft and calculate*
 * the fourier spectrum(s) and return the inverse-transformed image pointer. *
 *                                                                           *
 *                                                                           *
 *                   AUTHOR: Simon Low                                       *
 *                                                                           *
 *            RELATED FILES: fourn.c, fft.c, util.c, fft_setup.c             *
 *                                                                           *
 *              CODING DATE: 1/15/92                                         *
 *  LAST MODIFICATIONS MADE: 11/16/94                                        *
 *                           revised by Kun Luo to make it not truncate      *
 *                           floating point data in order to keep precision  *
 *                                                                           *
 *****************************************************************************

RCS (Revision Control System) Information - Added automatically by RCS)

$Author: yawei $
$Date: 1997/05/02 22:06:18 $
$Source: /opt/cvipapps/CVIPtools3.5/TRANSFORMS/RCS/inverse_fft.c,v $
$Header: /opt/cvipapps/CVIPtools3.5/TRANSFORMS/RCS/inverse_fft.c,v 1.13 1997/05/02 22:06:18 yawei Exp $

*******************************************************************************/
/* Define Preprocessor statements */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "CVIPtools.h"
#include "CVIPimage.h"
#include "CVIPconvert.h"
#include "CVIPtransform.h"

Image *ifft_transform(Image *in_Image, int block_size) {
  int h, w, x, y, color=0;
  int i;
  float *red_data, *green_data, *blue_data;

  if(block_size > in_Image->image_ptr[0]->rows ||
 	  block_size > in_Image->image_ptr[0]->cols) {
     fprintf(stderr, "inverse_fft: blocksize larger than image!\n");
     return(Image *)NULL;
  }
  fprintf(stdout, "Performing the inverse FFT\n");
  if(in_Image->image_ptr[0]->data_format != COMPLEX) {
     for(i=0; i<in_Image->bands; i++) {
        if(!(makeComplex_Matrix(in_Image->image_ptr[i], CVIP_NO))) {
	   fprintf(stderr, "inverse_fft: makeComplex_Matrix failed!\n");
	   exit(1);
        }
     }
     in_Image->image_ptr[0]->data_format = COMPLEX;
  }
  if (getDataType_Image(in_Image) < CVIP_FLOAT) {
     cast_Image(in_Image, CVIP_FLOAT);
     print_CVIP("Input image boosted to FLOAT\n");
  }
  if(in_Image->bands == 3)
     color = 1;

  w = in_Image->image_ptr[0]->cols;
  h = in_Image->image_ptr[0]->rows;

  red_data = (float *) calloc(h*w*2+1, sizeof(float));

  if(color) {
     green_data = (float *) calloc(h*w*2+1, sizeof(float));
     blue_data  = (float *) calloc(h*w*2+1, sizeof(float));
  }

  i=1;  
 
  for(y=0; y<h; y++) {
    for(x=0; x<w; x++) {

      red_data[i]=((float **)(in_Image->image_ptr[0]->rptr))[y][x];
      red_data[i+1]=((float **)(in_Image->image_ptr[0]->iptr))[y][x];

      if (color) {
         green_data[i]=((float **)(in_Image->image_ptr[1]->rptr))[y][x];         green_data[i+1]=((float **)(in_Image->image_ptr[1]->iptr))[y][x];
         blue_data[i]=((float **)(in_Image->image_ptr[2]->rptr))[y][x];
         blue_data[i+1]=((float **)(in_Image->image_ptr[2]->iptr))[y][x];
      }
     i += 2;
    } /* end x */
 }   /* end y */

  x=0;

  /* inverse fft */

  manager(in_Image, red_data, INVERSE, 0, block_size);

  if (color) {
    manager(in_Image, green_data, INVERSE, 1, block_size);
    manager(in_Image, blue_data, INVERSE, 2, block_size);
  }

  free(red_data);
  if(color) {
     free(green_data);
     free(blue_data);
  }
  for(x=0; x<in_Image->bands; x++)
     (void)matrix_makereal(in_Image->image_ptr[x], CVIP_YES);
  return(in_Image);
}

