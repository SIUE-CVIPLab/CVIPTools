/*****************************************************************************
    ======================================================================
    Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
    ======================================================================
		   Name: image_sharp
          Expanded Name: image sharpening
             Parameters: Pointer to original image of type Image
                Returns: Image Pointer
            Description: Sharpens (brigthens the edges) the given image.
            Diagnostics: None as yet
             References: None
              Author(s): Srinivas Madiraju
                         Southern Illinois University @ Edwardsville
______________________________________________________________________________

For Image Sharpening, the roberts gradient algorithm is used. This algorithm brightens the edges of the image thus creating a high constrast background/foreground image thus increasing in the sharpness of the image. 

To the function, image_sharp(), the pointer to the original image structure is passed. For each pixel, it's gradient is calculated as the difference in gray levels betweem adjacent pixels. The gradient is added to the original pixel value, thus resulting in a crisp image. Since the gradient assumes large values for prominent edges in the image, and small values in the regions that are fairly smooth, being zero in regions of constant gray levels, the original pixel value is added to get a constrasted sharp image. 

After computing the resultant image, the Image pointer is returned to the calling function.

****************************************************************************/

#include "CVIPtoolkit.h"
#include "CVIPenhance.h"
#include <math.h>

void image_sharp( Image *inputImage)
{
   int  i, j, cols, rows, bands, col_initial = 0, row_initial = 0, temp1, temp2; 
   byte **gray_plane, **red_plane, **blue_plane, **green_plane;
      
   rows = inputImage->image_ptr[0]->rows;
   cols = inputImage->image_ptr[0]->cols; 
   bands = getNoOfBands_Image(inputImage);
   if (bands == 1) 
    {
      gray_plane = (byte **) inputImage->image_ptr[0]->rptr;
      for (i = col_initial; i < (cols - col_initial - 1); i++) 
         for (j = row_initial; j < (rows - row_initial - 1); j++)
           {
             temp1 = abs(gray_plane[j][i] - gray_plane[j+1][i]);
             temp2 = abs(gray_plane[j][i] - gray_plane[j][i+1]); 
             gray_plane[j][i] += abs(temp1 - temp2);
             if (gray_plane[j][i] > 255)  gray_plane[j][i] = 255;
	   }      	      
     }
   else if (bands == 3)
    {
      red_plane = (byte **) inputImage->image_ptr[0]->rptr;
      blue_plane = (byte **) inputImage->image_ptr[1]->rptr;
      green_plane = (byte **) inputImage->image_ptr[2]->rptr;
      for (i = col_initial; i < (cols - col_initial - 1); i++) 
         for (j = row_initial; j < (rows - row_initial - 1); j++)
           {
             temp1 = abs(red_plane[j][i] - red_plane[j+1][i+1]);
             temp2 = abs(red_plane[j+1][i] - red_plane[j][i+1]);
             red_plane[j][i] += (int) sqrt(temp1*temp1 + temp2*temp2);
             if (red_plane[j][i] > 255)  red_plane[j][i] = 255;
             temp1 = abs(blue_plane[j][i] - blue_plane[j+1][i+1]);
             temp2 = abs(blue_plane[j+1][i] - blue_plane[j][i+1]);
             blue_plane[j][i] += (int) sqrt(temp1*temp1 + temp2*temp2);
             if (blue_plane[j][i] > 255)  blue_plane[j][i] = 255;
             temp1 = abs(green_plane[j][i] - green_plane[j+1][i+1]);
             temp2 = abs(green_plane[j+1][i] - green_plane[j][i+1]);
             green_plane[j][i] += (int) sqrt(temp1*temp1 + temp2*temp2);
             if (green_plane[j][i] > 255)  green_plane[j][i] = 255;
	   }
    }
 }
