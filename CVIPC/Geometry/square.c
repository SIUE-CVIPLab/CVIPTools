/******************************************************************************
    ======================================================================
    Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
    ======================================================================
		   Name: create_squarewave_sep
          Expanded Name: create_squarewave_sep
             Parameters: Pointer to original image of type Image
                Returns: Image Pointer
            Description: Creates a square wave image for the given input image.                          
            Diagnostics: None as yet
             References: None
              Author(s): Srinivas Madiraju, Kun Luo
                         Southern Illinois University @ Edwardsville
______________________________________________________________________________

To this function square_image(), the original Image pointer is passed where is resultant square wave image is computed and the resultant Image pointer is passed back to the original calling function.

To user is prompted to choose between the horizontal square wave and the Vertical square wave.

For the horizontal square wave, the first half of the rows (or image) is filled with white pixels 
(pixel value 255) and the remainder of the row if filled with black pixels (pixel value 0)
This procedure is repeated for each and every row for the new resultant image.

For the vertical square wave, the first half of image is filled with white pixels (pixel value 255) and the remainder of the image if filled with black pixels (pixel value 0)


*******************************************************************************/

#include "CVIPtoolkit.h"
#include "waves.h"

Image *create_squarewave_sep(){ 
	int img_size, frequency, choice;
   	fprintf(stderr, " ENTER Image SIZE : ");
   	img_size = get_int(10, 1, 1000);
   	fprintf(stderr, "\n           1: Horizontal Sine Wave\n");
   	fprintf(stderr, "           2: Vertical Sine Wave\n");
   	fprintf(stderr, " ENTER CHOICE : ");
   	choice = get_int(10, 1, 2);
   	fprintf(stderr, " Enter the desired FREQUENCY : ");
   	frequency = get_int(10, 1, 256);
	return (Image*)create_squarewave(img_size, frequency, choice);
}

Image *create_squarewave(int img_size, int frequency, int choice)
{
   int i, j, gray_level = 127, semaphore = 0;
   unsigned int bands;
   byte  **new_image;
   IMAGE_FORMAT image;
   COLOR_FORMAT color;
   CVIP_TYPE         data_type;
   FORMAT       data_format;
   Image        *NewImage;
   float		step;

   data_type = CVIP_BYTE;
   data_format = REAL;
   image = PGM;
   color = GRAY_SCALE;
   bands = 1;

   if(img_size  <= 0)
	img_size = 1;
   if(frequency <= 0)
	frequency = 1;
   step = ((float)(img_size))/(frequency*(float)2.0);

   NewImage = image_allocate(image, color, bands, img_size, img_size, 
                             data_type, data_format);
   if (choice == 1)  semaphore = 1;
   if (choice == 2)  semaphore = 2;
   if(bands == 1)
    {
      if (semaphore==2)
        {
          new_image = (byte **) NewImage->image_ptr[0]->rptr;
            for (i = 0; i < img_size; i++) 
	            for (j = 0; j < img_size; j++)
				{
					if(0 == (((int)(((float)(i)) / step))) % 2 )
			          { new_image[i][j] = 255; }
					else 
				      { new_image[i][j] = 0; }
				}
		} 	      
	if(semaphore==1) 
        {
          new_image = (byte **) NewImage->image_ptr[0]->rptr;
            for (i = 0; i < img_size; i++) 
	            for (j = 0; j < img_size; j++)
				{
					if(0 == (((int)(((float)(j)) / step))) % 2 )
			          { new_image[i][j] = 255; }
					else 
				      { new_image[i][j] = 0; }
				}
		}
     }
   return (NewImage);
}
