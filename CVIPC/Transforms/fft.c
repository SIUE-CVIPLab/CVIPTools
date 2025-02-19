/*****************************************************************************
 * ======================================================================    *
 * Image Processing/Computer Vision Tool Project - Dr. Scott Umbaugh SIUE    *
 * ======================================================================    *
 *                                                                           *
 * ROUTINE/FUNCTION: fft_transform()                                         *
 *                                                                           *
 *           DESCRIPTION:  Perform forward fast fourier transform.           *
 *                                                                           *
 *                   AUTHOR: Simon Low                                       *
 *                                                                           *
 *            RELATED FILES: fft_setup.c, util.c, inverse_fft.c              *
 *                                                                           *
 *              CODING DATE: Jan/92                                          *
 *  LAST MODIFICATIONS MADE: 11/16/94                                        *
 *                           revised by Kun Luo in November, 1994, to make   *
 *                           it accept input image which data type can be    *
 *                           of any .                                        *
 *                                                                           *
 *  VARIABLES PASSED TO FUNCTION:                                            *
 *        input_Image - An image structure with necessary info. about the    *
 *        image as well as a **ptr to the image data. (see image.h)          *
 *                                                                           *
 *        block_size - type int. The size of each block where fft is going   *
 *        to operate on.                                                     *
 *                                                                           *
 *                                                                           *
 *  RETURNED VARIABLES:                                                      *
 *        fft_transform() -  returns an image pointer with                   *
 *                           complex data (forward transformed )             *
 *                                                                           *
 *****************************************************************************
RCS (Revision Control System) Information - Added automatically by RCS)

$Author: yawei $
$Date: 1997/05/29 21:25:40 $
$Source: /opt/cvipapps/CVIPtools3.6/TRANSFORMS/RCS/fft.c,v $
$Header: /opt/cvipapps/CVIPtools3.6/TRANSFORMS/RCS/fft.c,v 1.17 1997/05/29 21:25:40 yawei Exp $

*******************************************************************************/
/* Define Preprocessor statements */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <CVIPtools.h>
#include <CVIPimage.h>
#include <CVIPtransform.h>

/* forward fft */
Image *fft_transform(Image *input_Image,int block_size)
{
  Image *xsform_Image;
  Image *temp_image;
  float *red_data, *green_data, *blue_data;

  int i, ww;
  int  w, h, old_w, old_h,band;
  int color = 0, cc, x, y, zeropad = 0;
  long row_size;

 /* zero-padding parameter setup */

  if(input_Image->bands == 3) color = 1;

  w = input_Image->image_ptr[0]->cols;
  h = input_Image->image_ptr[0]->rows;

  old_w = w;
  old_h = h;

  ww = w % block_size;

  if (ww != 0) {  /* if ==0 need no change */
     zeropad = 1;
     if ( (cc=((w+ww)%block_size)) != 0) {
        w = w + block_size - ww;
     }
     else
        w = w + ww;
  }

  ww = h % block_size;

  if (ww != 0) {  /* if ==0 need no change */
     zeropad = 1;
     if ( (cc=((h+ww)%block_size)) != 0) {
        h =  h + block_size - ww;
     }
     else
        h =  h + ww;
  }

   /* Allocate memory for return Image (only) : COMPLEX */

  xsform_Image=image_allocate(input_Image->image_format,
       input_Image->color_space,input_Image->bands,h,w,CVIP_FLOAT,COMPLEX);
  temp_image=input_Image;
  if ( zeropad ) {
      printf("\nZero padding... \n");
      temp_image=image_allocate(input_Image->image_format,
       input_Image->color_space,input_Image->bands,h,w,input_Image->image_ptr[0]->data_type,
           input_Image->image_ptr[0]->data_format);
     
      row_size=calculate_size(old_w,input_Image->bandP[0]->data_type);
      for(band=0;band<input_Image->bands;band++) {
         for(y=0;y<old_h;y++){
            memcpy((char *)temp_image->image_ptr[band]->rptr[y],
                  (char*)input_Image->image_ptr[band]->rptr[y],row_size);
            if(input_Image->image_ptr[0]->data_format==COMPLEX)
                memcpy((char *)temp_image->image_ptr[band]->iptr[y],
                   (char*)input_Image->image_ptr[band]->iptr[y],row_size);
         }
      }
      delete_Image(input_Image);
   } 

  /* allocate memory for array (float )to be sent into fft.c */

  red_data = (float *) calloc(h*w*2+1, sizeof(float));

  if( color) {

     green_data = (float *) calloc(h*w*2+1, sizeof(float));
     blue_data  = (float *) calloc(h*w*2+1, sizeof(float));

  }

  /* shift the whole image, not block by block */
  shift_n_copy(temp_image, red_data, 0);

  if(color) {
     shift_n_copy(temp_image, green_data, 1);
     shift_n_copy(temp_image, blue_data, 2);
  }

  manager(temp_image, red_data, FORWARD, 0, block_size);

 if(color) {
     manager(temp_image, blue_data,FORWARD, 1, block_size);
     manager(temp_image, green_data, FORWARD, 2, block_size);
  }

  i=1;
  
  for(y=0; y< h; y++) {
    for(x=0; x< w; x++) {

      /*  transfer transformed data to xsform_Image */

      ((float **)(xsform_Image->image_ptr[0]->rptr))[y][x] = red_data[i];
      ((float **)(xsform_Image->image_ptr[0]->iptr))[y][x] = red_data[i+1];

      if (color) {
        ((float **)(xsform_Image->image_ptr[1]->rptr))[y][x] = green_data[i];
        ((float **)(xsform_Image->image_ptr[1]->iptr))[y][x] = green_data[i+1];
        ((float **)(xsform_Image->image_ptr[2]->rptr))[y][x] = blue_data[i];
        ((float **)(xsform_Image->image_ptr[2]->iptr))[y][x] = blue_data[i+1];
      }
      i+= 2;
    }
  }
  delete_Image(temp_image);
  free(red_data);
  if(color){
	free(green_data);
	free(blue_data);
  }
  /* return the forward transformed image pointer */
 
  return xsform_Image;

}

long calculate_size(int length, CVIP_TYPE data_type){
   long value;
   switch(data_type){
     case CVIP_BYTE:
         value=sizeof(byte);
         break;
     case CVIP_SHORT:
         value=sizeof(short);
         break;
     case CVIP_INTEGER:
         value=sizeof(long);
         break;
     case CVIP_FLOAT:
         value=sizeof(float);
         break;
     case CVIP_DOUBLE:
         value=sizeof(double);
   }
   value*=length;
   return value;
}

