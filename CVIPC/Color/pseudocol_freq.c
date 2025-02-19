/***************************************************************************
* **********************************************************************
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* **********************************************************************
*
*             File Name: pseudocol_freq.c
*           Description: The original image can be of any data types: CVIP_BYTE,
*                        CVIP_SHORT, CVIP_INTEGER, CVIP_FLOAT and CVIP_DOUBLE.
*         Related Files: 
*   Initial Coding Date: 7/5/96
*           Portability: Standard (ANSI) C
*            References:
*             Author(s): Wenxing Li
*                        Southern Illinois University @ Edwardsville
*
** Copyright (C) 1996 SIUE - by Scott Umbaugh and Yansheng Wei.
**
** Permission to use, copy, modify, and distribute this software and its
** documentation for any purpose and without fee is hereby granted, provided
** that the above copyright notice appear in all copies and that both that
** copyright notice and this permission notice appear in supporting
** documentation.  This software is provided "as is" without express or
** implied warranty.
**
* RCS (Revision Control System) Information
* ...Added automatically by RCS 
*
** $Log: pseudocol_freq.c,v $
** Revision 1.6  1997/03/08 00:59:12  yawei
** Name Changes:
** 	BOOLEAN ==> CVIP_BOOLEAN
** 	FALSE ==> CVIP_YES
** 	TRUE ==> CVIP_NO
** 	BYTE ==> CVIP_BYTE
** 	SHORT ==> CVIP_SHORT
** 	INTEGER ==> CVIP_INTEGER
** 	FLOAT ==> CVIP_FLOAT
** 	DOUBLE ==> CVIP_DOUBLE
** 	TYPE ==> CVIP_TYPE
**
** Revision 1.5  1997/01/16 21:28:32  yawei
** manual changes
**
 * Revision 1.4  1996/12/28  06:30:37  yawei
 * blockwise_fft ==> fft_transform
 * inverse_fft   ==> ifft_transform
 *
 * Revision 1.3  1996/12/23  21:05:52  yawei
 * Changed filename:
 *   frequency_pseudocolor.c ==> pseudocol_freq.c
 *
*
****************************************************************************/

#include <math.h>
#include "CVIPimage.h"
#include "CVIPcolor.h"
#include "CVIPtransform.h"

#define MAXCVIP_SHORT    pow(2, (sizeof(short)*8 - 1)) - 1
#define MINCVIP_SHORT   (pow(2, (sizeof(short)*8 - 1))*(-1))
#define MAXINT	    pow(2, (sizeof(int)*8 - 1)) - 1
#define MININT     (pow(2, (sizeof(int)*8 - 1))*(-1))

#define FREPSEUDO(type_)\
  lowImage = (Image *)remap_Image(lowImage, type_, dmin, dmax);\
  bandImage = (Image *)remap_Image(bandImage, type_, dmin, dmax);\
  highImage = (Image *)remap_Image(highImage, type_, dmin, dmax);

#define FRECVIP_DOUBLE\
  cast_Image(lowImage, CVIP_DOUBLE); \
  cast_Image(bandImage, CVIP_DOUBLE);\
  cast_Image(highImage, CVIP_DOUBLE);


static int prepro_frequency(Image * inputImage)
{
 int 		i, j, k=0, size;
 unsigned int   rows, cols; 

 rows =  getNoOfRows_Image(inputImage);
 cols =  getNoOfCols_Image(inputImage);

/* choose the longer side */
 if ( rows > cols ) size = rows;
 else		    size = cols;

/* if the longer side is not power of 2, enlarge it to be power of 2*/
 for (i=0, j=2; i<9 && j<size; i++, j*=2) if (size % j != 0) k++;
 if (k != 0) 	size = j;

 return (size);
}

static Image * combine_image(IMAGE_FORMAT image_format,
	COLOR_FORMAT color_space, int bands, int heigth, int width,
	CVIP_TYPE data_type, FORMAT data_format)
{int      i;
 Image  * A;
 Matrix * M;

 A = (Image *) malloc(sizeof(Image));
 if(!A) {printf("\nERROR in image structure allocate\n");
         exit(1);
    	 }

 A->image_format = image_format;
 A->color_space = color_space;
 A->bands = bands;
 A->story = NULL;

 A->image_ptr = (MATRIX **) malloc(bands*sizeof(MATRIX *));

 for(i = 0 ; i < bands ; i++)
   {M = (Matrix *) malloc(sizeof(Matrix));
    if(!M) {printf("\nERROR in matrix structure allocate\n");
            return NULL;
    	   }
    A->image_ptr[i] = M;
    M->rows = heigth;
    M->cols = width;
    M->data_format = data_format;
    M->data_type = data_type;
    M->iptr = NULL;
    }   

 return(A);
}

static void free_for_combine(Image *A)
{register int 	  i;
 const char 	* fn = "combine_image_free";
 HISTORY  	  head, previous;
   
 if( !A || !(A->bands) || (!A->image_ptr) ) 
   cvip_error(fn, "\ninvalid structure passed to image_free");
 
 if(A->story!=NULL)
   {head=A->story;
    while(head!=NULL)
      {previous=head;
       head=head->next;
       i = previous->packetP->dsize;
       while(i>0)
	 {i--;
          free(previous->packetP->dptr[i]);
          }      
       free(previous->packetP->dtype);
       free(previous->packetP->dptr);
       free(previous->packetP);
       free(previous);
      }
    }
 
 for(i=A->bands-1; i >= 0; i--)
   if(A->image_ptr[i]!=0) free((char *)(A->image_ptr[i]));
 
 free( A->image_ptr );
 
 free((char *)A);
}

static void frequency_process(Image * lowfftImage, Image * bandfftImage,
	Image * highfftImage, Image * outputImage, CVIP_TYPE dtype, int blocksize,
	int blow, int bband, int bhigh)
{Image * lowImage, * bandImage, * highImage;
 long 	 dmin, dmax;

 lowImage = (Image *)ifft_transform(lowfftImage, blocksize);
 bandImage = (Image *)ifft_transform(bandfftImage, blocksize);
 highImage = (Image *)ifft_transform(highfftImage, blocksize);

 switch(dtype)
   { case CVIP_BYTE:   dmin = 0;        dmax = 255;      FREPSEUDO(CVIP_BYTE)    break;
     case CVIP_SHORT:  dmin = MINCVIP_SHORT; dmax = MAXCVIP_SHORT; FREPSEUDO(CVIP_SHORT)   break;
     case CVIP_INTEGER:dmin = MININT;   dmax = MAXINT;   FREPSEUDO(CVIP_INTEGER) break;
     case CVIP_FLOAT:  break;
     case CVIP_DOUBLE: FRECVIP_DOUBLE        break;
   }

 outputImage->image_ptr[blow]->rptr = lowImage->image_ptr[0]->rptr;
 outputImage->image_ptr[bband]->rptr = bandImage->image_ptr[0]->rptr;
 outputImage->image_ptr[bhigh]->rptr = highImage->image_ptr[0]->rptr;

 free_for_combine(highImage);
 free_for_combine(bandImage);
 free_for_combine(lowImage);

 delete_Image(highfftImage);
 delete_Image(bandfftImage);
 delete_Image(lowfftImage);
}


/* passed parameters should guarantee that blow != bband != bhigh */
/* real image, various data types */
Image * pseudocol_freq(Image * grayImage, int inner, int outer, int blow,
			      int bband, int bhigh)
{Image * lowfftImage, * bandfftImage, * highfftImage,  *outputImage;
 int     blocksize;
 CVIP_TYPE    dtype;

 dtype = grayImage->image_ptr[0]->data_type;
 blocksize = prepro_frequency(grayImage);
 outputImage = combine_image(PPM, RGB, 3, blocksize, blocksize, dtype, REAL);

 lowfftImage = (Image *)fft_transform(grayImage, blocksize);
 bandfftImage = duplicate_Image(lowfftImage);
 highfftImage = duplicate_Image(lowfftImage);

 lowfftImage = (Image *)Ideal_Low(lowfftImage, blocksize, 1, inner);
 bandfftImage = (Image *)Ideal_Band_Pass(bandfftImage, blocksize, 0, inner, outer);
 highfftImage = (Image *)Ideal_High(highfftImage, blocksize, 0, outer);

 frequency_process(lowfftImage, bandfftImage, highfftImage, outputImage, 
		   dtype, blocksize, blow, bband, bhigh);

 return (outputImage);
}
