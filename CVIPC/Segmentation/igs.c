/******************************************************************************
    ======================================================================
    Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
    ======================================================================

                   Name: igs.c
          Expanded Name: Improved Gray Scale Quantization

             Parameters: inputImage -- Pointer to the input image of type
                                       Image.

                         gray_level -- gray level of the output image
               
	        Returns: If succeeds, return the quantized image with 
			 specified gray levels; if errors happen, return NULL.

            Description: If the input image is not a CVIP_BYTE image, it will be 
			 remapped to be CVIP_BYTE first. It can be multi_band and
			 assumed to be real only.

            Diagnostics: None

    Initial Coding Date: 10/9/96
Last Modifications Made: 10/20/96
             References: None

                 Author: Wenxing Li


          Southern Illinois University @ Edwardsville


*******************************************************************************/



#include "CVIPtoolkit.h"
#include "CVIPdef.h"
#include "CVIPsegment.h"

static Image * IGS_prep(Image * inputImage, int gray_level)
{
  int		i,  j,  k=0;
  Image	      * returnImage;

  if ( (gray_level > 256) || (gray_level < 2))
    { fprintf(stderr, "The gray level should be within 2 -- 256.\n");
		delete_Image(inputImage);
      return NULL;
    }

  for (i=0, j=2; i<7 && j<gray_level; i++, j*=2)
    if (gray_level % j != 0) k++;
  if (k != 0)
     { fprintf(stderr, "gray level is not power of 2.\n");
		 delete_Image(inputImage);
       return NULL;
     }

  if (inputImage->image_ptr[0]->data_format != REAL)
     { fprintf(stderr, "IGS: input image should be a real image.\n");
		 delete_Image(inputImage);
       return NULL;
     }

  if (inputImage->image_ptr[0]->data_type != CVIP_BYTE)
     returnImage = remap_Image(inputImage, CVIP_BYTE, 0, 255);
  else 
     returnImage = duplicate_Image(inputImage);

  return returnImage;
}


/* if everything is OK, return a non-NULL pointer; 
   otherwise, return NULL */
/* a real multi_band image */
Image * igs_segment(Image * inputImage, int gray_level)
{
  byte 			mask,  complement, initial,  sum=0;
  int			i,  j,  k=0;
  byte	     	     ** image,  value;
  unsigned int 		rows, cols;
  Image		      * returnImage;

  returnImage = IGS_prep(inputImage, gray_level);
  if (!returnImage) return NULL; /* image has bee deleted */

  if (gray_level == 256) return returnImage;

  rows = returnImage->image_ptr[0]->rows;
  cols = returnImage->image_ptr[0]->cols;

  initial = 0x80;
  mask = initial;
  
  for (i=gray_level/2; i>1; i/=2)
    { initial /= 2;
      mask |= initial;
    }

  complement = 0xff - mask;

  for (k=0; k<returnImage->bands; k++)
    {
     image = (byte **)returnImage->image_ptr[k]->rptr;
     for (i=0; i<rows; i++)
       for (j=0; j<cols; j++)
	 { value = image[i][j];
	   if ( (value & mask) != mask)
	      sum = value + (sum & complement);
 	   else sum = value;
	   image[i][j] = sum & mask;
	 }
    }

  return returnImage;
}

