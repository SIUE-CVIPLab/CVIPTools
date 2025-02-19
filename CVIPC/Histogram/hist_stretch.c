/******************************************************************************
    ======================================================================
    Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
    ======================================================================

                   Name: hist_stretch.c
          Expanded Name: Histogram Stretch

             Parameters: inputImage -- Pointer to the input image of type
                                       Image.

			 low_limit -- low limit of the range into which the 
				      output image is remapped

			 high_limit -- high limit of the range into which the
				       output image is remapped

			 low_clip -- percentage of the low end of the input
				     image which will be clipped

			 high_clip -- percentage of the high end of the input
				      image which will be clipped

                Returns: Return the histogram stretched image.

            Description: If the input image is not a CVIP_BYTE image, it will be
                         remapped to be CVIP_BYTE first. It can be multi_band and
                         assumed to be real only.

            Diagnostics: None

    Initial Coding Date: 10/31/96
Last Modifications Made: 11/14/96
             References: None

                 Author: Wenxing Li


          Southern Illinois University @ Edwardsville


*******************************************************************************/


#include <math.h>
#include "CVIPimage.h"

Image * remap_Image(const Image *, CVIP_TYPE, long, long);

static long * get_hist(Image * inputImage)
{ int			i, j, k;
  long		      * P, n;
  byte 		     ** image;
  unsigned int		rows, cols;

  rows = inputImage->image_ptr[0]->rows;
  cols = inputImage->image_ptr[0]->cols;  

  P = (long *)calloc(256 * inputImage->bands, sizeof(long));

  for (n=0; n < 256*inputImage->bands; n++)
    P[n] = (long)0;

  for (k=0; k<inputImage->bands; k++)
    { image = (byte **)inputImage->image_ptr[k]->rptr;
      for (i=0; i<rows; i++)
        for (j=0; j<cols; j++)
 	  P[k*256 + image[i][j]]++;

    }

  return (P);
}

static int * clip_computing(Image * inputImage, long * P, float low, float high)
{ int			k, l, h;
  int		      * ptr;
  long			total, suml, sumh;

  total = inputImage->image_ptr[0]->rows * inputImage->image_ptr[0]->cols;
  ptr = (int *)malloc(inputImage->bands * 2 * sizeof(int));

  for (k=0; k<inputImage->bands; k++)
    { l = -1;
      h = 256;
      suml = 0;
      sumh = 0;
      while ((suml/(float)total) < low)
	{ l++;
	  suml += P[k*256 + l];
	}
      if ((suml/(float)total) >= (low + 0.01)) l--;
      while ((sumh/(float)total) < high)
	{ h--;
	  sumh += P[k*256 + h];
	}
      if ((sumh/(float)total) >= (high + 0.01)) h++;
      ptr[k*2] = l;
      ptr[k*2 + 1] = h;
    }

  free((char *)P);
  return (ptr);
}

/* CVIP_BYTE image, modify on the input image */
static void clip_hist(Image * inputImage, float low, float high)
{ int			i, j, k, l, h;
  byte 		     ** image;
  int 		      * ptr;
  unsigned int		rows, cols;

  rows = inputImage->image_ptr[0]->rows;
  cols = inputImage->image_ptr[0]->cols;  

  ptr = clip_computing(inputImage, get_hist(inputImage), low, high);

  for (k=0; k<inputImage->bands; k++)
    { image = (byte **)inputImage->image_ptr[k]->rptr;
      l = ptr[k*2];
      h = ptr[k*2 + 1];
      for (i=0; i<rows; i++)
        for (j=0; j<cols; j++)
	  { if ((int)image[i][j] <= l) image[i][j] = (byte)l+1;
            if ((int)image[i][j] >= h) image[i][j] = (byte)h-1;
          }
    }

  free((char *)ptr);
}


/* multi_band images, if not CVIP_BYTE, remap to be CVIP_BYTE before doing hist_stretch */
Image * hist_stretch(Image * inputImage, int low_limit, int high_limit,
		     float low_clip, float high_clip)
{ CVIP_TYPE		dtype;
  Image	      * tempImage, * returnImage;

  dtype = inputImage->image_ptr[0]->data_type;

  if (dtype == CVIP_BYTE)
       tempImage = duplicate_Image(inputImage);
  else tempImage = remap_Image(inputImage, CVIP_BYTE, 0, 255);
 
  clip_hist(tempImage, low_clip, high_clip);

  returnImage = remap_Image(tempImage, CVIP_BYTE, low_limit, high_limit);

  delete_Image(tempImage);

  return (returnImage);
}
  
