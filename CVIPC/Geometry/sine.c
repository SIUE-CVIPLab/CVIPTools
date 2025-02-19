/******************************************************************************
    ======================================================================
    Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
    ======================================================================
 		   Name: create_sine_sep
          Expanded Name: create_sine_sep
             Parameters: Pointer to original image of type Image
                Returns: Image Pointer
            Description: Creates a sine wave image for the given input image.
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

******************************************************************************/

#include "CVIPtoolkit.h"
#include "waves.h"

Image *create_sine_sep(){ 
	int img_size, frequency, choice;
   	fprintf(stderr, " ENTER Image SIZE : ");
   	img_size = get_int(10, 1, 1000);
   	fprintf(stderr, "\n           1: Horizontal Sine Wave\n");
   	fprintf(stderr, "           2: Vertical Sine Wave\n");
   	fprintf(stderr, " ENTER CHOICE : ");
   	choice = get_int(10, 1, 2);
   	fprintf(stderr, " Enter the desired FREQUENCY : ");
   	frequency = get_int(10, 1, 256);
	return (Image*)create_sine(img_size, frequency, choice);
}

Image *create_sine(int img_size, int frequency, int choice){

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
                pixel = (float)co_ordinate + 128*sin(2*PI*frequency*j/img_size);
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
                pixel = (float)co_ordinate + 128*sin(2*PI*frequency*j/img_size);
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
                pixel = (float)co_ordinate + 128*sin(2*PI*frequency*j/img_size);
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
                pixel = (float)co_ordinate + 128*sin(2*PI*frequency*j/img_size);
	        rounded_pixel = (int) (pixel + 0.5);
	        new_red_plane[j][i] = rounded_pixel;
	        new_blue_plane[j][i] = rounded_pixel;
	        new_green_plane[j][i] = rounded_pixel;
	      }
        }
    } /* end of else */
 return (NewImage);
}
