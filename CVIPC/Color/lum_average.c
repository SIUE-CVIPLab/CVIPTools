/******************************************************************************
    ======================================================================
    Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
    ======================================================================

              File Name: lum_average.c
             Parameters: Pointer to original image of type Image
                Returns: Image Pointer
            Description: Color to gray_scale by average of all bands
            Diagnostics: None as of yet
             References: None
              Author(s): Wenxing Li
                         Southern Illinois University @ Edwardsville
    Initial Coding Date: 6/1/96

                   This file contains the functions necessary to let
        the user get the gray_scale image by average of all image bands.
	The input image can be multi-band image (i.e. from 1 to n bands)
	with any data type(CVIP_BYTE, CVIP_SHORT, CVIP_INTEGER, CVIP_FLOAT & CVIP_DOUBLE), but it
	should be a real image. The resulting image after averaging will
	be of the same data type as the original image.




*******************************************************************************/
#include "CVIPimage.h"

#define maxband 20

#define LUMCOMPUTE(type_,bands_,size_,bandp_) \
  {	register long	   i_,  j_;     \
	register type_	 * out_;	\
	register double    sum_;	\
	out_ = (type_ *)bandp_[0];	\
	for (j_=0; j_<size_; j_++) 	\
	{ sum_ = 0;			\
	  for (i_=1; i_<=bands_; i_++)  sum_ += (double)(*((type_ *)bandp_[i_]));\
	  *out_ = (type_) (sum_/(double)bands_);	\
 	  for (i_=1; i_<=bands_; i_++) ((type_ *)bandp_[i_])++;	\
	  out_++; \
	}\
  }

/* for multi_bands & real images */
Image * lum_average(Image * input_Image)
{
 Image 		* output_Image;
 unsigned int 	  bands,  rows,  cols;
 CVIP_TYPE		  data_type;
 void 		* bandp[maxband+1];	/* *band[0] for result */
 int		  i;
 long		  size;

 bands = input_Image->bands;
 if (bands < 2)   return (input_Image);

 rows = input_Image->image_ptr[0]->rows;
 cols = input_Image->image_ptr[0]->cols;
 size = rows * cols;
 data_type = input_Image->image_ptr[0]->data_type;
 output_Image = new_Image(PGM, GRAY_SCALE, 1, rows, cols, data_type,REAL);

 bandp[0] = (void *)output_Image->image_ptr[0]->rptr[0];
 for (i=0; i<bands; i++) bandp[i+1] = (void *)input_Image->image_ptr[i]->rptr[0];

 data_type = input_Image->image_ptr[0]->data_type;
 switch(data_type)
  { case CVIP_BYTE:    LUMCOMPUTE(byte,bands,size,bandp)   break;
    case CVIP_SHORT:   LUMCOMPUTE(short,bands,size,bandp)  break;
    case CVIP_INTEGER: LUMCOMPUTE(int,bands,size,bandp)    break;
    case CVIP_FLOAT:   LUMCOMPUTE(float,bands,size,bandp)  break;
    case CVIP_DOUBLE:  LUMCOMPUTE(double,bands,size,bandp) break;
  }

 return output_Image;
}
