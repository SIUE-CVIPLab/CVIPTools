/***************************************************************************
* =========================================================================
*
*   Computer Vision and Image Processing Lab - Dr. Scott Umbaugh SIUE
* 
* =========================================================================
*
*             File Name: otsu_threshold.c 
*           Description: it contains the function to threshold BYTE images 
*   Initial Coding Date: June 15, 2009
*           Portability: Standard (ANSI) C
*             Credit(s): Hari Krishna Akkineni, Jhansi Lakshmi Akkineni
*                        Southern Illinois University at Edwardsville
*
** Copyright (c) 1995, 1996, SIUE - Scott Umbaugh, Kun Luo, Yansheng Wei
****************************************************************************/


/*
** include header files
*/

#include "CVIPtoolkit.h"
#include "CVIPconvert.h"
#include "CVIPdef.h"
#include "CVIPimage.h"
#include "math.h"


Image *fft_mag(Image *inputImage){
    Image	*outimage; 	/* 2-d matrix data pointer */
    unsigned int 		r,		/* row index */
			c, 		/* column index */
			bands;		/* band index */
			
    unsigned int 	no_of_rows,	/* number of rows in image */
			no_of_cols,	/* number of columns in image */
			no_of_bands;	/* number of image bands */

	float 	** rp,  ** ip, mag;


    /*
    ** Gets the number of image bands (planes)
    */
    no_of_bands = getNoOfBands_Image(inputImage);

    /* 
    ** Gets the number of rows in the input image  
    */
    no_of_rows =  getNoOfRows_Image(inputImage);

    /* 
    ** Gets the number of columns in the input image  
    */
    no_of_cols =  getNoOfCols_Image(inputImage);

    outimage = duplicate_Image(inputImage);

    for(bands=0; bands < no_of_bands; bands++) 
	{
	  rp = (float **)outimage->image_ptr[bands]->rptr;
      ip = (float **)outimage->image_ptr[bands]->iptr;
	  for(r=0; r < no_of_rows; r++) 
	  {
     	  for(c=0; c < no_of_cols; c++) 
		  {
			  mag = (float)sqrt(((rp[r][c]*rp[r][c])+(ip[r][c]*ip[r][c])));
			  rp[r][c] = mag;
			  ip[r][c] = 0;
          }
      }
    }

	return outimage;
}

