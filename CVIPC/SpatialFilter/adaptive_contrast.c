/******************************************************************************
    ======================================================================
    Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
    ======================================================================

                   Name: adaptive_contrast.c
          Expanded Name: adaptive contrast filter

             Parameters: inputImage -- Pointer to the input image of type
				       Image.

			 k1 -- A constant between 0 and 1.
 			 k2 -- Another constant between 0 and 1.

			 kernel_size -- size of the kernel(should be an
					odd number).

			 min_gain -- the minimum gain factor
			 max_gain -- the maximum gain factor

                Returns: pointer to an image that is the filtering result
			 of the input image using adaptive contrast filter.

            Description: The input image is a real image, it can be 
			 multi_band and of any data type: CVIP_BYTE, CVIP_SHORT, 
                         CVIP_INTEGER, CVIP_FLOAT and CVIP_DOUBLE.

            Diagnostics: None

    Initial Coding Date: 10/3/96
Last Modifications Made: 10/16/96
             References: None

                 Author: Wenxing Li


          Southern Illinois University @ Edwardsville

*******************************************************************************/



#include <math.h>
#include "CVIPimage.h"
#include "CVIPmap.h"

#define MAXCVIP_SHORT    pow(2, (sizeof(short)*8 - 1)) - 1
#define MINCVIP_SHORT   (pow(2, (sizeof(short)*8 - 1))*(-1))
#define MAXINT      pow(2, (sizeof(int)*8 - 1)) - 1
#define MININT     (pow(2, (sizeof(int)*8 - 1))*(-1))


#define MEAN_ADP(type_)\
{	register int  i_, j_; \
	int		  k_; \
	register double     sum_; \
	register type_   ** image_; \
	for (k_=0; k_<inputImage->bands; k_++) \
        { image_ = (type_ **)inputImage->image_ptr[k_]->rptr; \
	  sum_ = 0; \
	  for (i_=0; i_<rows; i_++) \
	    for (j_=0; j_<cols; j_++) \
	      sum_ += image_[i_][j_]; \
	  mean[k_] = sum_ / (rows*cols); \
	} \
}


static double * get_mean(Image * inputImage)
{
  unsigned int		rows, cols;
  CVIP_TYPE			dtype;
  double	      * mean;

  mean = (double *)calloc(inputImage->bands, sizeof(double));

  rows = inputImage->image_ptr[0]->rows;
  cols = inputImage->image_ptr[0]->cols;

  dtype = inputImage->image_ptr[0]->data_type;

  switch (dtype)
    { case  CVIP_BYTE:    MEAN_ADP(byte) 	break;
      case  CVIP_SHORT:   MEAN_ADP(short)	break;
      case  CVIP_INTEGER: MEAN_ADP(int)   	break;
      case  CVIP_FLOAT:   MEAN_ADP(float)	break;
      case  CVIP_DOUBLE:  MEAN_ADP(double)
    }

  return mean;
}


#define ADAP_MEAN_VAR(type_)\
 { register int		x_, y_;\
   type_  	     ** image_; \
   register type_	value_; \
   register float	sum_ave_, sum_var_; \
   float		factor_; \
   image_ = (type_ **)image; \
   if (i>=(rows-offset) || i<offset || j>=(cols-offset) || j<offset) \
     output[i][j] = (float)image_[i][j]; \
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
       if (sum_var_ != 0) \
            factor_ = k1 * (mean[k] / sum_var_); \
       else factor_ = max_gain; \
       if (factor_ > max_gain) factor_ = max_gain; \
       if (factor_ < min_gain) factor_ = min_gain; \
       output[i][j] = factor_*(image_[i][j] - sum_ave_) + k2*sum_ave_;\
     }\
 }


/* normal, return 0; otherwise return -1 */
static int adap_prep(Image * inputImage, unsigned int kernel_size)
{
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
  
  return 0;
}


static Image * adap_post(Image * adapImage, CVIP_TYPE dtype)
{
  Image 	     * returnImage;
  long		       dmin, dmax;

  switch (dtype)
    { case   CVIP_BYTE:  dmin = 0;        dmax = 255;        break;
      case   CVIP_SHORT: dmin = MINCVIP_SHORT; dmax = MAXCVIP_SHORT;   break;
      case CVIP_INTEGER: dmin = MININT;   dmax = MAXINT;     break;
      case   CVIP_FLOAT: break;
      case  CVIP_DOUBLE: (void)cast_Image(adapImage, CVIP_DOUBLE);
    }

  if (dtype < CVIP_FLOAT)
    { returnImage = remap_Image(adapImage, dtype, dmin, dmax);
      delete_Image(adapImage);
      return returnImage;
    }
 
  return adapImage;
}


/* a real multi_band image of any data type */ 

Image *adaptive_contrast_filter(Image * inputImage, float k1, float k2,
	unsigned int kernel_size, float min_gain,  float max_gain)
{
  unsigned int 		rows, cols;
  int			i, j, k, offset;
  void 		     ** image;
  float		     ** output;
  CVIP_TYPE 			dtype; 
  Image		      * adapImage, * returnImage;
  double	      * mean;

  if (kernel_size == 1) return inputImage;

  if (adap_prep(inputImage, kernel_size)) return NULL;

  mean = get_mean(inputImage);

  rows = inputImage->image_ptr[0]->rows;
  cols = inputImage->image_ptr[0]->cols;

  dtype = inputImage->image_ptr[0]->data_type;
  adapImage = new_Image(inputImage->image_format, inputImage->color_space, 
		        inputImage->bands, rows, cols, CVIP_FLOAT, REAL);
  offset = kernel_size / 2;

  for (k=0; k<inputImage->bands; k++)
    {
     image = (void **)inputImage->image_ptr[k]->rptr;
     output = (float **)adapImage->image_ptr[k]->rptr;
     for (i=0; i<rows; i++)
       for (j=0; j<cols; j++)
	 switch (dtype)
	   { case  CVIP_BYTE:    ADAP_MEAN_VAR(byte) 	break;
	     case  CVIP_SHORT:   ADAP_MEAN_VAR(short)	break;
	     case  CVIP_INTEGER: ADAP_MEAN_VAR(int)   	break;
	     case  CVIP_FLOAT:   ADAP_MEAN_VAR(float)	break;
	     case  CVIP_DOUBLE:  ADAP_MEAN_VAR(double)
	   }
    }

  returnImage = adap_post(adapImage, dtype);

  return returnImage;
}

