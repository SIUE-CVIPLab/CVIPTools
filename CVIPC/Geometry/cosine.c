/******************************************************************************
    ======================================================================
    Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
    ======================================================================
 		   Name: create_cosine_sep
          Expanded Name: create_cosine_sep
             Parameters: Pointer to original image of type Image
                Returns: Image Pointer
            Description: Creates a cosine wave image for the given input image.
	    Diagnostics: None as yet
             References: None
              Author(s): Srinivas Madiraju, Kun Luo
                         Southern Illinois University @ Edwardsville
______________________________________________________________________________
 

To this function, the original Image pointer is passed where is resultant sine wave image is computed and the resultant Image pointer is passed back to the original calling function.

To user is prompted to choose between the horizontal sine wave and the Vertical sine wave.
The user can also enter the frequency of the sine wave which should be in the range 1 ~ 256. 
For each pixel (in the row), the pixel values are calculated as  127 + 128*Sin2(PI)xf, where f is the frequency chosen by the user and x is the row value which ranges from 0~256, or 0~512 depending upon the image size. 
This procedure is repeated for each and every row for the new resultant image.
$Log: cosine.c,v $
Revision 1.7  1997/03/08 01:01:39  yawei
Name Changes:
	BOOLEAN ==> CVIP_BOOLEAN
	FALSE ==> CVIP_NO
	TRUE ==> CVIP_YES
	BYTE ==> CVIP_BYTE
	SHORT ==> CVIP_SHORT
	INTEGER ==> CVIP_INTEGER
	FLOAT ==> CVIP_FLOAT
	DOUBLE ==> CVIP_DOUBLE
	TYPE ==> CVIP_TYPE

Revision 1.6  1997/01/16 21:32:30  yawei
Global Change:  Image_FORMAT ==> IMAGE_FORMAT

 * Revision 1.5  1997/01/15  17:19:48  yawei
 * Global Change:  IMAGE ==> Image
 *
 * Revision 1.4  1996/12/16  23:08:40  yawei
 * Change function name:
 *  cosine_wave_sep          ==> create_cosine
 *
 * Revision 1.3  1996/03/26  19:55:09  zli
 * *** empty log message ***
 *
 * Revision 1.2  1996/03/26  19:18:38  zli
 * split create_cosine_sep() into two functions
 *
 * Revision 1.1  1996/01/06  20:10:38  kluo
 * Initial revision
 *

******************************************************************************/

#include "CVIPtoolkit.h"
#include "waves.h"

Image *create_cosine_sep(){ 
	int img_size, frequency, choice;
   	fprintf(stderr, " ENTER Image SIZE : ");
   	img_size = get_int(10, 1, 1000);
   	fprintf(stderr, "\n           1: Horizontal Sine Wave\n");
   	fprintf(stderr, "           2: Vertical Sine Wave\n");
   	fprintf(stderr, " ENTER CHOICE : ");
   	choice = get_int(10, 1, 2);
   	fprintf(stderr, " Enter the desired FREQUENCY : ");
   	frequency = get_int(10, 1, 256);
	return (Image*)create_cosine(img_size, frequency, choice);
}

Image *create_cosine(int img_size, int frequency, int choice)
{
   int   i, j, rounded_pixel, bands, co_ordinate = 127, semaphore = 0;
   byte  **new_red_plane, **new_green_plane, **new_blue_plane,
         **new_image; 
   float pixel;
   IMAGE_FORMAT image;
   COLOR_FORMAT color;
   CVIP_TYPE         data_type;
   FORMAT       data_format;
   Image        *NewImage;
    
   data_type = CVIP_BYTE;
   data_format = REAL;
   image = PGM;
   color = GRAY_SCALE;
   bands = 1;

   if (choice == 1)  semaphore = 1;

   NewImage = image_allocate(image, color, bands, img_size, img_size, 
                             data_type, data_format);
   if(bands == 1)
    {
      if (semaphore)
        {
          new_image = (byte **) NewImage->image_ptr[0]->rptr;
          for (i = 0; i < img_size; i++) 
            for (j = 0; j < img_size; j++)
              { 
                pixel = (float)co_ordinate + 128*cos(2*PI*frequency*j/img_size);
	        rounded_pixel = (int) (pixel + 0.5);
	        new_image[i][j] = rounded_pixel;
	      }
      	}
      else
        {
          new_image = (byte **) NewImage->image_ptr[0]->rptr;
          for (i = 0; i < img_size; i++) 
            for (j = 0; j < img_size; j++)
              { 
                pixel = (float)co_ordinate + 128*cos(2*PI*frequency*j/img_size);
	        rounded_pixel = (int) (pixel + 0.5);
	        new_image[j][i] = rounded_pixel;
	      }
      	}
     }
   else if (bands == 3)
    {
      new_red_plane   = (byte **) NewImage->image_ptr[0]->rptr;    
      new_green_plane = (byte **) NewImage->image_ptr[1]->rptr;    
      new_blue_plane  = (byte **) NewImage->image_ptr[2]->rptr; 
      if (semaphore)
        {  
          for (i = 0; i < img_size; i++) 
            for (j = 0; j < img_size; j++)
              { 
                pixel = (float)co_ordinate + 128*cos(2*PI*frequency*j/img_size);
	        rounded_pixel = (int) (pixel + 0.5);
	        new_red_plane[i][j] = rounded_pixel;
	        new_blue_plane[i][j] = rounded_pixel;
	        new_green_plane[i][j] = rounded_pixel;
	      }
        }
      else 
        {  
          for (i = 0; i < img_size; i++) 
            for (j = 0; j < img_size; j++)
              { 
                pixel = (float)co_ordinate + 128*cos(2*PI*frequency*j/img_size);
	        rounded_pixel = (int) (pixel + 0.5);
	        new_red_plane[j][i] = rounded_pixel;
	        new_blue_plane[j][i] = rounded_pixel;
	        new_green_plane[j][i] = rounded_pixel;
	      }
        }
    } /* end of else */
 return (NewImage);
 }
