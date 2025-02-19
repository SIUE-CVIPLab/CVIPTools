/******************************************************************************
    ======================================================================
    Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
    ======================================================================

 		             Name: smooth.c
          Expanded Name: image smoothening
             Parameters: Pointer to original image of type Image
                Returns: Image Pointer
            Description: Smoothens (removes noise) the given image. 
			 (Kernel size is in the Range 2 ~ 10)
            Diagnostics: None as yet
             References: None
              Author(s): Srinivas Madiraju
                         Southern Illinois University @ Edwardsville
______________________________________________________________________________
** Copyright (C) 1995 SIUE - by Kun Luo, Mark Zuke and Scott Umbaugh.
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
** $Log: smooth.c,v $
** Revision 1.7  1997/01/15 17:20:57  yawei
** Global Change:  IMAGE ==> Image
**
 * Revision 1.6  1996/12/24  22:31:58  yawei
 * image_enhance.h ==> CVIPenhance.h
 *
 * Revision 1.5  1996/12/24  22:20:03  yawei
 * Changed filename:
 *   img_smooth.c ==> smooth.c
 *
 * Revision 1.4  1996/12/24  22:18:37  yawei
 * Changed function:
 *  void image_smooth_sep ==> Image *smooth_filter
 *
 * Revision 1.3  1996/12/24  22:02:32  yawei
 * (check in old version).
 *
 * Revision 1.2  1995/05/12  22:25:30  zook
 * Modified function to provide only
 * neighborhood averaging filter.
 *
 * Revision 1.1  1995/05/12  22:21:47  zook
 * Initial revision
 *

For Image Smoothening, the two algorithms used are Neighborhood Averaging and
Median Filtering. These algorithms are used for diminishing spurious effects
(noise) in a digital image.

To the function, image_smooth(), the pointer to the original image structure
is passed. The user is prompted to select either neighborhood averaging or
median filtering. In either case the Kernel size is limited in the range 2 and
10 inclusive of the two boundaries.

In Neighborhood Averaging, depending upon the kernel size (3X3, 4X4, and so
on...), the current pixel under consideration is replaced by the average sum
of all it's neighboring pixels. If the kernel size is too large say 8X8 or so,
then the output is slow, because every pixel under consideration is replaced
by the average of 8*8 pixels which involves 64 multiplications and 63
additions. In general, for a kernel size n, the number of multiplications is
n*n and the number of additions are (n*n - 1).  

For the Median filter,  the gray level of each pixel is replaced by the median
of the gray levels in the neighborhood of that pixel. The neighboring pixels
are sorted in ascending or descending order and the pixel under consideration
is replaced by the middle value of the sorted pixels. For example, for a kernel
size of 5X5, the pixel under consideration is replaced by the median or middle
pixel value (13th in this case) of all it's 25 neighboring pixels. Like
neighborhood averaging, for large kernel sizes, the output is slow due the
computations involved. 

After computing the resultant image, the Image pointer is returned to the
calling function.

*******************************************************************************/

#include "CVIPtoolkit.h"
#include "CVIPenhance.h"
#include <math.h>

Image *smooth_setup(Image *inputImage){
    int kernel;
   fprintf(stderr, " Enter the kernel size : ");
   kernel = get_int(10, 2, 10);
   return smooth_filter(inputImage,kernel);
}

Image *smooth_filter(Image *inputImage,int kernel)
{
   int i, j, rounded_pixel, cols, rows, threshold,
       x, y, bands, col_initial, row_initial, choice,
       median_array1[100], median_array2[100], temp, 
       median_array3[100], count = 0; 
   long sum1 = 0, sum2 = 0, sum3 = 0;
   byte **gray_plane, **red_plane, **blue_plane, **green_plane;
   float  pixel;
      
   rows = inputImage->image_ptr[0]->rows;
   cols = inputImage->image_ptr[0]->cols; 
   bands = getNoOfBands_Image(inputImage);
   for (i = 0; i < 100; i++) 
     {
      median_array1[i] = 0;
      median_array2[i] = 0;
      median_array3[i] = 0;
     }
   choice = 1;
   if (choice == 1) 
     {
       col_initial = (kernel/2 + 1);
       row_initial = (kernel/2 + 1);
       if ( (bands == 1) && (kernel > 1) )
         {
           gray_plane = (byte **) inputImage->image_ptr[0]->rptr;
           for (i = col_initial; i < (cols - col_initial - 1); i++) 
           for (j = row_initial; j < (rows - row_initial - 1); j++)
             {
               for (x = 0; x < kernel; x++) 
                 for (y = 0; y < kernel; y++)
                   sum1 += (long) gray_plane[x-1+j][y-1+i];
                 gray_plane[j][i] = (int) (sum1/(kernel*kernel));
               sum1 = 0;
	     }
         }
       else if ( (bands == 3) && (kernel > 1) )
         {
           red_plane = (byte **) inputImage->image_ptr[0]->rptr;
           blue_plane = (byte **) inputImage->image_ptr[1]->rptr;
           green_plane = (byte **) inputImage->image_ptr[2]->rptr;
   
           for (i = col_initial; i < (cols - col_initial - 1); i++) 
             for (j = row_initial; j < (rows - row_initial - 1); j++)
               {
                 for (x = 0; x < kernel; x++) 
                   for (y = 0; y < kernel; y++)
                     {
                       sum1 += (long) red_plane[x-1+j][y-1+i];
                       sum2 += (long) blue_plane[x-1+j][y-1+i];
                       sum3 += (long) green_plane[x-1+j][y-1+i];
                     }
                   red_plane[j][i] = (int) (sum1/(kernel*kernel));
                   blue_plane[j][i] = (int) (sum2/(kernel*kernel));
                   green_plane[j][i] = (int) (sum3/(kernel*kernel));
                 sum1 = sum2 = sum3 = 0;
	       }
         }
     }
   else if (choice == 2) 
     {
       col_initial = (kernel/2 + 1);
       row_initial = (kernel/2 + 1);
       if ( (bands == 1) && (kernel > 1) )
         {
           gray_plane = (byte **) inputImage->image_ptr[0]->rptr;
           for (i = col_initial; i < (cols - col_initial - 1); i++) 
             for (j = row_initial; j < (rows - row_initial - 1); j++)
               {
                 for (x = 0, count = 0; x < kernel; x++)
                   for (y = 0; y < kernel; y++)
                     median_array1[count++] = gray_plane[x-1+j][y-1+i];
	               	/* 
			** Perform sorting routine 
			*/
			do {
            			temp = median_array1[0];
            			for (y=1; y<kernel*kernel; y++)
               			if (median_array1[y-1] > median_array1[y]) {
                       			temp = median_array1[y-1];
                  			median_array1[y-1] = median_array1[y];
                    			median_array1[y] = temp;
               			}
         		}
         		while (temp != median_array1[0]);
            
                 	gray_plane[j][i] = median_array1[(kernel*kernel)>>1];
	       }
          }
       else if ( (bands == 3) && (kernel > 1) )
         {
           red_plane = (byte **) inputImage->image_ptr[0]->rptr;
           blue_plane = (byte **) inputImage->image_ptr[1]->rptr;
           green_plane = (byte **) inputImage->image_ptr[2]->rptr;
   
           for (i = col_initial; i < (cols - col_initial - 1); i++) 
             for (j = row_initial; j < (rows - row_initial - 1); j++)
               {
                 for (x = 0, count = 0; x < kernel; x++)
                   for (y = 0; y < kernel; y++)
                     {
                       median_array1[count] = red_plane[x-1+j][y-1+i];
                       median_array2[count] = blue_plane[x-1+j][y-1+i];
                       median_array3[count++] = green_plane[x-1+j][y-1+i];
                     }
                 for (x = 0; x < (kernel*kernel - 1); x++) 
                   for (y = x + 1; y < (kernel*kernel); y++)
                     {
                       if (median_array1[x] > median_array1[y])
                         {
                           temp = median_array1[x];
                           median_array1[x] = median_array1[y];
                           median_array1[y] = temp;
                         }
                       if (median_array2[x] > median_array2[y])
                         {
                           temp = median_array2[x];
                           median_array2[x] = median_array2[y];
                           median_array2[y] = temp;
                         }
                       if (median_array3[x] > median_array3[y])
                         {
                           temp = median_array3[x];
                           median_array3[x] = median_array3[y];
                           median_array3[y] = temp;
                         }
                     }
                 red_plane[j][i] = median_array1[kernel*kernel/2 + 1];
                 blue_plane[j][i] = median_array2[kernel*kernel/2 + 1];
                 green_plane[j][i] = median_array3[kernel*kernel/2 + 1];
	       }
          }
      }
		return inputImage;
 }
