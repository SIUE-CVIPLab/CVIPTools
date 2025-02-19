/******************************************************************************
    ======================================================================
    Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
    ======================================================================

                   Name: mmse_filter.c

          Expanded Name: MMSE filter

             Parameters: inputImage -- Pointer to the original image of 
				       type Image.

			 noise_var -- Noise variance of the input image.

			 kernel_size -- Size of the kernel(should be an odd
				        number)  

                Returns: pointer to a new image.

            Description: The original image should be a real image, it can
			 be multi_band and of any data type: CVIP_BYTE, CVIP_SHORT,
                         CVIP_INTEGER, CVIP_FLOAT and CVIP_DOUBLE.

            Diagnostics: None

    Initial Coding Date: 9/26/96
Last Modifications Made: 10/16/96
             References: None

                 Author: Wenxing Li


          Southern Illinois University @ Edwardsville

*******************************************************************************/


#include <math.h>
#include "CVIPimage.h"

#define MAXCVIP_SHORT    pow(2, (sizeof(short)*8 - 1)) - 1
#define MINCVIP_SHORT   (pow(2, (sizeof(short)*8 - 1))*(-1))
#define MAXINT      pow(2, (sizeof(int)*8 - 1)) - 1
#define MININT     (pow(2, (sizeof(int)*8 - 1))*(-1))


#define MEAN_VAR(type_)\
 { register int		x_, y_;\
   type_  	     ** image_; \
   register type_	value_; \
   register float	sum_ave_, sum_var_; \
   float		ratio_, temp_; \
   image_ = (type_ **)image; \
   if (i>=(rows-offset) || i<offset || j>=(cols-offset) || j<offset) \
     ((type_ **)output)[i][j] = image_[i][j]; \
   else \
     { sum_ave_ = 0; \
       sum_var_ = 0; \
       for (x_=-offset; x_<=offset; x_++) \
         for (y_=-offset; y_<=offset; y_++) \
           { value_ = image_[i+x_][j+y_]; \
	     sum_ave_ += value_; \
	     sum_var_ += value_ * value_; \
      	   } \
       sum_ave_ /= (kernel_size*kernel_size); \
       sum_var_ /= (kernel_size*kernel_size); \
       sum_var_ -= sum_ave_ * sum_ave_; \
       ratio_ = noise_var/sum_var_; \
       temp_ = (1.0-ratio_)*image_[i][j] + ratio_*sum_ave_;\
       if (dtype < CVIP_FLOAT) \
         { if (temp_ > (float)dmax) temp_ = (float)dmax; \
           if (temp_ < (float)dmin) temp_ = (float)dmin; \
	 } \
       ((type_ **)output)[i][j] = (type_)temp_; \
     }\
 }


/* normal, return 0; otherwise return -1 */
static int mmse_prep(Image * inputImage, unsigned int kernel_size, int * dmin, int * dmax)
{ 
  CVIP_TYPE		dtype;

  if (kernel_size > inputImage->image_ptr[0]->rows ||
      kernel_size > inputImage->image_ptr[0]->cols)
    { fprintf(stderr, "kernel_size larger than image rows or cols\n");
      return -1;
    }

  if (!(kernel_size % 2)) 
    { fprintf(stderr, "kernel_size should be an odd number\n");
      return -1;
    }

  if (inputImage->image_ptr[0]->data_format != REAL)
    { fprintf(stderr, "mmse_filter only deals with real images\n");
      return -1;
    }

  dtype = inputImage->image_ptr[0]->data_type;
  switch(dtype)
    { case CVIP_BYTE:   *dmin = 0;        *dmax = 255;      break;
      case CVIP_SHORT:  *dmin = MINCVIP_SHORT; *dmax = MAXCVIP_SHORT; break;
      case CVIP_INTEGER:*dmin = MININT;   *dmax = MAXINT;   break;
      default:      break;
    }
  
  return 0;
}


/* a real multi_band image of any data type */ 
Image * mmse_filter(Image * inputImage, float noise_var, unsigned int kernel_size)
{
  unsigned int 		rows, cols;
  int			i, j, k, offset;
  void 		     ** image, ** output;
  CVIP_TYPE 			dtype; 
  Image		      * mmseImage;
  int		        dmin,  dmax;

  if (kernel_size == 1) return inputImage;

  if (mmse_prep(inputImage, kernel_size, &dmin, &dmax)) return NULL;

  rows = inputImage->image_ptr[0]->rows;
  cols = inputImage->image_ptr[0]->cols;

  dtype = inputImage->image_ptr[0]->data_type;
  mmseImage = new_Image(inputImage->image_format, inputImage->color_space, 
		        inputImage->bands, rows, cols, dtype, REAL);
  offset = kernel_size / 2;

  for (k=0; k<inputImage->bands; k++)
    {
     image = (void **)inputImage->image_ptr[k]->rptr;
     output = (void **)mmseImage->image_ptr[k]->rptr;
     for (i=0; i<rows; i++)
       for (j=0; j<cols; j++)
	 switch (dtype)
	   { case  CVIP_BYTE:    MEAN_VAR(byte) 	break;
	     case  CVIP_SHORT:   MEAN_VAR(short)	break;
	     case  CVIP_INTEGER: MEAN_VAR(int)   	break;
	     case  CVIP_FLOAT:   MEAN_VAR(float)	break;
	     case  CVIP_DOUBLE:  MEAN_VAR(double)
	   }
    }

  return mmseImage;
}
 
