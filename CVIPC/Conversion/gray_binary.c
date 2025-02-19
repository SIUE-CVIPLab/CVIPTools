/******************************************************************************
    ======================================================================
    Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
    ======================================================================

                   Name: gray_binary.c
          Expanded Name: Binary code to Gray code and inverse.

             Parameters: inputImage -- Pointer to input image of type Image

			 direction -- 1 or 0. 1 means from binary to Gray
			 code; 0 means from Gray code to binary code.

                Returns: pointer to an image whose pixels are encoded using
			 Gray code or binary code according to the value
			 of direction.

            Description: The input image should be a real image, it can be 
			 multi_band and of any data types: CVIP_BYTE, CVIP_SHORT, 
                         CVIP_INTEGER, CVIP_FLOAT and CVIP_DOUBLE.

            Diagnostics: None

    Initial Coding Date: 9/20/96
Last Modifications Made: 10/3/96
             References: None

                 Author: Wenxing Li


          Southern Illinois University @ Edwardsville

*******************************************************************************/



#include <math.h>
#include "CVIPimage.h" 

/*
   If check is zero or positive, return the Gray code of n;
   if check is negative, return the inverse Gray code of n.
*/
static byte Gray_code(byte n, int check)
{
 int            ish;
 byte           ans, idiv;
 
 if (check >=0) return (n ^ (n >> 1));
 
 ish = 1;
 ans = n;
 for (;;) { ans ^= (idiv = ans >> ish);
            if (idiv <= 1 || ish == 16) return (ans);
            ish <<= 1;
          }
}
 
 
/* multi-band real images */
Image * gray_binary(Image * inputImage, int direction)
{
 int             dd=1;
 Image         * newImage;
 unsigned int    i, j, k, rows, cols;
 byte         ** image;
 
 if (getDataFormat_Image(inputImage)==COMPLEX)
   { fprintf(stderr, "Input image should be real image\n");
     return NULL;
   }

 if (direction != 0 && direction != 1)
   { fprintf(stderr, "direction can only be 0 or 1\n");
     return NULL;
   }

 if (inputImage->image_ptr[0]->data_type == CVIP_BYTE)
      newImage = duplicate_Image(inputImage);
 else newImage = (Image *)remap_Image(inputImage, CVIP_BYTE, 0, 255);
 
 if (!direction) dd = -1;
 rows =  newImage->image_ptr[0]->rows;
 cols =  newImage->image_ptr[0]->cols;
 
 for (k=0; k<newImage->bands; k++)
  {image = (byte **)newImage->image_ptr[k]->rptr;
   for (i=0; i<rows; i++)
     for (j=0; j<cols; j++)
       image[i][j] = Gray_code(image[i][j], dd);
  }

 return newImage;
}

