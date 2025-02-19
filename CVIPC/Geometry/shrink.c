/***************************************************************************
* **********************************************************************
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* **********************************************************************
*
*             File Name: shrink.c
*           Description: 
*         Related Files: 
*   Initial Coding Date: Tue Dec 17 14:35:18 CST 1996
*           Portability: Standard (ANSI) C
*            References:
*             Author(s): Srinivas Madiraju, Yansheng Wei
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
** $Log: shrink.c,v $
** Revision 1.9  1997/03/08 01:01:53  yawei
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
** Revision 1.8  1997/01/16 21:32:40  yawei
** Global Change:  Image_FORMAT ==> IMAGE_FORMAT
**
 * Revision 1.7  1997/01/15  17:20:06  yawei
 * Global Change:  IMAGE ==> Image
 *
 * Revision 1.6  1996/12/17  22:07:02  yawei
 * Changed "image_geometry.h" to "CVIPgeometry.h"
 *
 * Revision 1.5  1996/12/17  20:47:17  yawei
 * Added header
 *
*
****************************************************************************
A pointer to the Image structure is passed to the function scale_image so that
the original image can be accessed. The user is prompted to enter the scaling
factor which should be in the range 0.1 to 1 (1 is the maximum scaling factor.
The function uses the first order scaling algorithm where, depending upon the
scaling factor the pixels from the original image are simple copied to the new
image.  The scaling factor is tested first to determine the size of the new
resultant image as well as the pixels to be removed in the original image.
If the inverse of the scaling factor is an integer (example scaling factor =
0.25, ==> 1/0.25 = 4), then every occurrence of that pixel is COPIED to the new
image who image size is determined by the scaling factor (In the above case,
every 4nd pixel is copied to the new image).

If the scaling factor is less than 0.5, then the scaling factor is apparently
modified so that the number of pixels COPIED to the new image is uniform thus
avoiding quantization in the resultant image.
For example, for a scaling factor 0.4 (0.4 ==> 1/0.4 = 2.5), every alternate
2nd and 3rd pixels are copied to the new image.

If the scaling factor is greater than 0.5, then depending upon the scaling
factor, those many pixels are SKIPPED while rest of the pixels are copied to
the new image. For example, for a scaling factor 0.6, every alternate 2nd and
3rd pixels are skipped while the rest is written to the new image. For a
scaling factor of 0.8, every 5th pixel is skipped, for 0.9 every 9th pixel is
skipped and so on.

After the scaling operation is performed, the pointer to the new resultant
image of type Image is returned to the calling function so that the new image
can be displayed.
*******************************************************************************/
 



#include "CVIPtoolkit.h"
#include "CVIPgeometry.h"
#define  COUNT 10

Image *shrink_sep( Image *input_Image ){
  float factor;

  fprintf(stderr, "\n\n ENTER SCALE FACTOR : ");
  factor = get_float(0.1, 1.0);

  return shrink(input_Image,factor);
}

Image *shrink( Image *input_Image, float factor )
{
  byte **red_plane, **green_plane, **blue_plane, **map_plane, 
       **new_red_plane, **new_green_plane, **new_blue_plane,
       **new_image, **image_array;
  int x_col, y_row, x, y, inv_factor = 0, temp_inv_factor, temp_dimensions,
      bands, rows, cols, new_cols, new_rows, semaphore = 0, count = 0,
      r_count = 0, c_count = 0, scale_step = 0, count1 = 0, temp_step2,
      temp_factor = 0, row_counter = 1, col_counter = 1, temp_step = 0,
      high_flag1 = 0, high_flag2 = 0, low_flag1 = 0, low_flag2 = 0, 
      div = 0, int_semaphore = 0, temp_swap, compare = 256;
  float test_dimensions = 0, test_inv_factor = 0;
  IMAGE_FORMAT image;
  COLOR_FORMAT color;
  CVIP_TYPE data_type;
  FORMAT data_format;
  Image *NewImage;

  if (factor<0.1 || factor>1.0) {printf("factor should be within (0.1-1.0)\n");
			         return NULL;
				}

  rows = getNoOfRows_Image(input_Image);
  cols = getNoOfCols_Image(input_Image);
  data_type = getDataType_Image(input_Image);
  data_format = getDataFormat_Image(input_Image);
  image = getFileFormat_Image(input_Image);
  color = getColorSpace_Image(input_Image);
  bands = getNoOfBands_Image(input_Image);

  temp_factor = (int) (factor * 10);
  factor = (float)temp_factor/10;
  inv_factor = (int) (1/factor);
  new_rows = (int) rows * factor;  
  new_cols = (int) cols * factor; 
  if (rows != cols)
    {
      temp_swap = rows;
      rows = cols;
      cols = temp_swap;
    } 
  if (!(factor > 0.5 && factor < 1.0))
    {
      test_inv_factor = (float) (1/factor);
      if ((test_inv_factor - inv_factor) > 0)
        {
          if ((int) (test_inv_factor + 0.5) > (int) (test_inv_factor))
            {  inv_factor = 2; low_flag2 = 1; }
          else 
            { inv_factor = (int) test_inv_factor; low_flag1 = 1; } 
        }
      else int_semaphore = 1;
     }
  else
    {
      semaphore = 1;
      temp_step = (factor * 10);
      temp_step2 = temp_step*(rows/compare);      
      div = (COUNT - temp_step);
      if (temp_step < 8)
        {
          scale_step = (temp_step/div) + 1;
          if (scale_step == 3)
            {
              high_flag2 = 1;
              new_rows -= (++temp_step2);
              new_cols -= (++temp_step2); 
             }
          else 
            {  scale_step = 2; high_flag1 = 1;  }
        }
      else 
        {
          if ((temp_step + 1) < COUNT)
            scale_step = temp_step/div + 1;
          else 
            scale_step = temp_step + 1;
        }
    }
  rows -= inv_factor;
  cols -= inv_factor;    
  NewImage = image_allocate(image, color, bands, new_rows, new_cols, 
                            data_type, data_format);
  if( input_Image->bands == 1)
    {
      image_array = (byte **) input_Image->image_ptr[0]->rptr;
      new_image = (byte **) NewImage->image_ptr[0]->rptr;
      if (!(semaphore))
        {  
          if (low_flag1)
            {     
              for(y_row = 0, y = 0; y_row < rows; y_row+=inv_factor, y++)
                {
                  r_count++;
                  for(x_col = 0, x = 0; x_col < cols; x_col+=inv_factor, x++)
                   {
                    c_count++;
                    new_image[x][y]= image_array[x_col][y_row];
                    if (c_count - inv_factor == 0) { x_col++; c_count = 0; }
                   }
                  if (r_count - inv_factor == 0)  { y_row++; r_count = 0; }
                }
            }
          else if (low_flag2)
            {     
              for(y_row = 0, y = 0; y_row < rows; y_row+=inv_factor, y++)
                {
                  r_count++;
                  for(x_col = 0, x = 0; x_col < cols; x_col+=inv_factor, x++)
                   {
                    c_count++;
                    new_image[x][y]= image_array[x_col][y_row];
                    if (!(c_count%2))  x_col++; 
                   }
                  if (!(r_count%2))   y_row++;
                }
            }
          else if (int_semaphore)
            {
              for(y_row = 0, y = 0; y_row < rows ; y_row+=inv_factor, y++)
                for(x_col = 0, x = 0; x_col < cols; x_col+=inv_factor, x++)
                  new_image[x][y]= image_array[x_col][y_row];
            }
        } /* end of !semaphore */

      else if (semaphore)
        {      
         if (high_flag1)
          { 
            for(y_row = 0,y = 0; y_row < rows; y_row++,y++)
              {
                r_count++;
                if (r_count%2 == 0) y_row++;
                else if (r_count%3 == 0)  y_row++;
                for(x_col = 0, x = 0; x_col < cols; x_col++, x++)
                  {
                    c_count++;
                    new_image[x][y]= image_array[x_col][y_row];
                    if (c_count%2 == 0) x_col++;
                    else if (c_count%3 == 0)  x_col++;
                  }
               }
           } /* end of if flag */
         else if (high_flag2)
          { 
            for(y_row = 0,y = 0; y_row < rows; y_row++,y++)
              {
                r_count++;
                if ((scale_step - r_count) == 1)  { y_row++; r_count = 0; }
                for(x_col = 0, x = 0; x_col < cols; x_col++, x++)
                  { 
                    c_count++;
                    if ((scale_step - c_count) == 1)  { x_col++; c_count = 0; }
                    new_image[x][y]= image_array[x_col][y_row];
                  }
               }
           } /* end of if flag */

         else 
          { 
            for(y_row = 0,y = 0; y_row < rows; y_row++,y++)
              {
                r_count++;
                if ((scale_step - r_count) == 1)  { y_row++; r_count = 0; }
                for(x_col = 0, x = 0; x_col < cols; x_col++, x++)
                  { 
                    c_count++;
                    if ((scale_step - c_count) == 1)  { x_col++; c_count = 0; }
                    new_image[x][y]= image_array[x_col][y_row];
                  }
               }
           } /* end of else */

        }  /* end of else semaphore */
    }

  else if (bands == 3)
    {
     red_plane   = (byte **) input_Image->image_ptr[0]->rptr;    
     green_plane = (byte **) input_Image->image_ptr[1]->rptr;    
     blue_plane  = (byte **) input_Image->image_ptr[2]->rptr;    
     new_red_plane   = (byte **) NewImage->image_ptr[0]->rptr;    
     new_green_plane = (byte **) NewImage->image_ptr[1]->rptr;    
     new_blue_plane  = (byte **) NewImage->image_ptr[2]->rptr;    
     if (!(semaphore))
       {  
         if (low_flag1)
           {     
             for(y_row = 0, y = 0; y_row < rows; y_row+=inv_factor, y++)
               {
                 r_count++;
                 for(x_col = 0, x = 0; x_col < cols; x_col+=inv_factor, x++)
                   {
                     c_count++;
                     new_red_plane[x][y]= red_plane[x_col][y_row];
                     new_blue_plane[x][y]= blue_plane[x_col][y_row];
                     new_green_plane[x][y]= green_plane[x_col][y_row];
                    if (c_count - inv_factor == 0) { x_col++; c_count = 0; }
                   }
                  if (r_count - inv_factor == 0)  { y_row++; r_count = 0; }
               }
            }
         else if (low_flag2)
           {     
             for(y_row = 0, y = 0; y_row < rows; y_row+=inv_factor, y++)
               {
                 r_count++;
                 for(x_col = 0, x = 0; x_col < cols; x_col+=inv_factor, x++)
                   {
                    c_count++;
                    new_red_plane[x][y]= red_plane[x_col][y_row];
                    new_blue_plane[x][y]= blue_plane[x_col][y_row];
                    new_green_plane[x][y]= green_plane[x_col][y_row];
                    if (!(c_count%2))  x_col++; 
                   }
                  if (!(r_count%2))   y_row++;
                }
            }
          else if (int_semaphore)
            {
              for(y_row = 0, y = 0; y_row < rows ; y_row+=inv_factor, y++)
                for(x_col = 0, x = 0; x_col < cols; x_col+=inv_factor, x++) {
                   new_red_plane[x][y]= red_plane[x_col][y_row];
                   new_blue_plane[x][y]= blue_plane[x_col][y_row];
                   new_green_plane[x][y]= green_plane[x_col][y_row];
                }
            }
        } /* end of !semaphore */
      else if (semaphore)
        {      
         if (high_flag1)
          { 
            for(y_row = 0,y = 0; y_row < rows; y_row++,y++)
              {
                r_count++;
                if (r_count%2 == 0) y_row++;
                else if (r_count%3 == 0)  y_row++;
                for(x_col = 0, x = 0; x_col < cols; x_col++, x++)
                  {
                    c_count++;
                    new_red_plane[x][y]= red_plane[x_col][y_row];
                    new_blue_plane[x][y]= blue_plane[x_col][y_row];
                    new_green_plane[x][y]= green_plane[x_col][y_row];
                    if (c_count%2 == 0) x_col++;
                    else if (c_count%3 == 0)  x_col++;
                  }
               }
           } /* end of if flag */
         else if (high_flag2)
          { 
            for(y_row = 0,y = 0; y_row < rows; y_row++,y++)
              {
                r_count++;
                if ((scale_step - r_count) == 1)  { y_row++; r_count = 0; }
                for(x_col = 0, x = 0; x_col < cols; x_col++, x++)
                  { 
                    c_count++;
                    if ((scale_step - c_count) == 1)  { x_col++; c_count = 0; }
                    new_red_plane[x][y]= red_plane[x_col][y_row];
                    new_blue_plane[x][y]= blue_plane[x_col][y_row];
                    new_green_plane[x][y]= green_plane[x_col][y_row];
                  }
               }
           } /* end of if flag */
         else 
          { 
            for(y_row = 0,y = 0; y_row < rows; y_row++,y++)
              {
                r_count++;
                if ((scale_step - r_count) == 1)  { y_row++; r_count = 0; }
                for(x_col = 0, x = 0; x_col < cols; x_col++, x++)
                  { 
                    c_count++;
                    if ((scale_step - c_count) == 1)  { x_col++; c_count = 0; }
                    new_red_plane[x][y]= red_plane[x_col][y_row];
                    new_blue_plane[x][y]= blue_plane[x_col][y_row];
                    new_green_plane[x][y]= green_plane[x_col][y_row];
                  }
               }
           } /* end of else */
        }  /* end of else semaphore */
   }  /* end of else  */
 return (NewImage);
}
