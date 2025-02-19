/***************************************************************************
   ======================================================================
   Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
   ======================================================================
 		   Name: zoom_image
          Expanded Name: zoom_image
             Parameters: Pointer to original image of type Image
                Returns: Image Pointer
            Description: Zooms the given image by a factor specified by
                         the user (Range 1 ~ 10)
            Diagnostics: None as yet
             References: None
              Author(s): Srinivas Madiraju
                         Southern Illinois University @ Edwardsville
 _____________________________________________________________________________
 

To the function zoom_image, a pointer to the original image is passed as a parameter. A menu appears for the user to zoom the original image as the user wishes. After performing the zooming operation the pointer to the resultant image is returned to the calling function to display the resultant image.
As the menu implies, the user can zoom the entire image, the first quadrant, the second and so on as well as specifying the co-ordinates and their respective distances to be zoomed.
The maximum zoom factor allowed is 10.
The zoom factor entered by the user is rounded before performing the actual zooming. If the zoom factor is 3/4th or above the closest integer value, the zooming factor is rounded to the nearest integer value. Like wise if the zoom factor is 1/4th or below the closest integer value, the zooming factor is rounded to the nearest integer value. 
If the zoom factor is between 1/4th or 3/4th an integer value, then depending upon the zooming factor, selected pixels are skipped in a uniform pattern and the zooming factor is rounded to the nearest integer. In this case, if the zooming factor is close or above 1/2 the integer value, the zooming factor is rounded to the nearest high integer value, else it is rounded to the nearest lower integer value.

The zooming is performed as a first order zooming algorithmn. For example, a zooming factor n implies n*n pixels are replicated in the neighborhood of any given original pixel.

Depending upon the menu chosen by the user, the oppropriate regions in the original image are chosen and zoomed accordingly. A new image of the appropriate size is created where the zoomed pixels of the original image are written. The pointer to this newly created zoomed image is returned to the calling function.	

*******************************************************************************/


#include "CVIPtoolkit.h"
#include <CVIPgeometry.h>
#define IMG_MANIP 6
#define HALF      0.5
#define QUARTER   0.25

Image *zoom_sep( Image *input_Image )
{
  int quadrant, X, Y, dx, dy;
  float temp_factor;

 fprintf(stderr, "\n SPECIFY the QUADRANT of image to be ZOOMED\n");
  fprintf(stderr, " Usage ==> 1: 1st Quadrant\n");
  fprintf(stderr, "           2: 2nd Quadrant\n");
  fprintf(stderr, "           3: 3rd Quadrant\n");
  fprintf(stderr, "           4: 4th Quadrant\n");
  fprintf(stderr, "           5: Whole of Image\n");
  fprintf(stderr, "           6: Specify (x, y) & dx, dy\n");
  fprintf(stderr, "\n\n ENTER CHOICE : ");
  quadrant = get_int(10, 1, 6);
  if (quadrant == 6)
   { 
     fprintf(stderr, "\n\n ENTER X-Coordinate : ");
     X = get_int(10, 0, 512);
     fprintf(stderr, " ENTER Y-Coordinate : ");
     Y = get_int(10, 0, 512);
     fprintf(stderr, " ENTER dx           : ");
     dx = get_int(10, 0, 512);
     fprintf(stderr, " ENTER dy           : ");
     dy = get_int(10, 0, 512);
    }
  fprintf(stderr, "\n\n ENTER ZOOM FACTOR : ");
  temp_factor = get_float(1.0, 10.0);
  
  return zoom(input_Image, quadrant, X, Y, dx, dy, temp_factor);
}

Image *zoom(Image *input_Image, int quadrant, int X, int Y, int dx,
		int dy, float temp_factor){
  byte **red_plane, **green_plane, **blue_plane, **map_plane, 
       **new_red_plane, **new_green_plane, **new_blue_plane,
       **new_image, **image_array;
  int x_col, x_org, y_row, copy, x, y, count = 1, semaphore = 0, skip,
      x_cor, y_cor,  temp, factor, test_factor, 
      row_count = 0, col_count = 0, flag = 0,
      bands, rows, cols, new_cols, new_rows, col_value, row_value,
      test_quarter;
  float quarter, half;
  IMAGE_FORMAT image;
  COLOR_FORMAT color;
  CVIP_TYPE data_type;
  FORMAT data_format;
  Image *NewImage;

  rows = getNoOfRows_Image(input_Image);
  cols = getNoOfCols_Image(input_Image);
  data_type = getDataType_Image(input_Image);
  data_format = getDataFormat_Image(input_Image);
  image = getFileFormat_Image(input_Image);
  color = getColorSpace_Image(input_Image);
  bands = getNoOfBands_Image(input_Image);

  if (quadrant == 6)
   { 
     row_value = Y;  rows = Y + dy; 
     col_value = X;  cols = X + dx;
    }
  test_factor = (int) temp_factor;
  half = test_factor + HALF;
  quarter = test_factor + QUARTER;
  if (quarter <= temp_factor)
   {
     if ( (test_factor + HALF + QUARTER) > temp_factor)
       {
         semaphore = 1;
         factor = (((int) + temp_factor) + 1);
         temp_factor = (((int) + temp_factor) + HALF);
         if ( ((int) (temp_factor + 0.5) <= 5) )
           skip = 2 * ( (int) (temp_factor + 0.5));
         else if ( ((int) (temp_factor + 0.5)) > 6 )
           skip = ((2 * temp_factor) + 1);
         else skip = 2 * temp_factor;
         if ( ((int) temp_factor >= 5) && ((int) temp_factor != 7) )
           flag = 1;        /* to remove blank pixels (at edges) in image */
       }
      else
        {  
          factor = ((int) temp_factor) + 1;  /* for 3/4th & higher  */
          temp_factor  = ((int) temp_factor) + 1;
        }
    }
  else 
    {
      factor = (int) temp_factor;  /* for int values */
      temp_factor = (int) temp_factor;  
    }
  if (quadrant == 5) 
    { new_rows = rows*temp_factor;  new_cols = cols*temp_factor;  }
  else if (quadrant == 6) 
    { new_rows = (rows - Y)*temp_factor;  new_cols = (cols - X)*temp_factor;  }
  else 
    { new_rows = rows*temp_factor/2; new_cols = cols*temp_factor/2;  }   
  if (flag) { new_rows -= IMG_MANIP; new_cols -= IMG_MANIP; }

  NewImage = image_allocate(image, color, bands, new_rows, new_cols, 
                            data_type, data_format);
  if ( quadrant == 1)
    {  rows /= 2;   cols /= 2;   col_value = row_value = 0; }
  else if ( quadrant == 2)
    {  row_value = 0 ; col_value = cols/2;  rows /= 2;  }
  else if ( quadrant == 3)
    {  row_value = rows/2; col_value = 0; cols /= 2;  }
  else if ( quadrant == 4)
    {  row_value = rows/2 ; col_value = cols/2;  }
  else if ( quadrant == 5)
    { row_value = col_value = 0;  }
  if( input_Image->bands == 1)
    { 
      image_array = (byte **) input_Image->image_ptr[0]->rptr;
      new_image = (byte **) NewImage->image_ptr[0]->rptr;
      if (semaphore)
        {      
          for(y_row = row_value,y = 0; y_row < (rows - 1); y_row++, y += factor)
            {   
              row_count++;
              if (((skip - row_count) == 1) )
                {  y_row++; row_count = 0; }
              for(x_col = col_value, x = 0; x_col < (cols - 1); x_col++)
                {
                  col_count++;
                  if (((skip - col_count) == 1) )
                    {  x_col++; col_count = 0; }
                  for (copy=x_cor=y_cor=0; copy < (factor * factor); copy++ )
                    {  
                      new_image[y+y_cor][x+x_cor++]= image_array[y_row][x_col];
	              if (x_cor == factor) 
	                {  y_cor++;x_cor=0;  }
	    	    } /* Inner for loop  */       
                  x += factor;
                }
            }
        }  /* end of if semaphore */

      else if (!semaphore)
        {      
          for(y_row = row_value,y = 0; y_row < rows; y_row++, y += factor)
            for(x_col = col_value,  x = 0; x_col < cols; x_col++, x += factor)
              for (copy=0, x_cor=0, y_cor=0; copy < (factor * factor); copy++)
                {  
                  new_image[y+y_cor][x+x_cor++]= image_array[y_row][x_col];
	          if (x_cor == factor) 
	            {  y_cor++;x_cor=0;  }
	        } /* Inner for loop  */       
        }  /* end if !semaphore */
   }  /* end of if (bands == 1)  */

  else if (bands == 3)
    {
     red_plane   = (byte **) input_Image->image_ptr[0]->rptr;    
     green_plane = (byte **) input_Image->image_ptr[1]->rptr;    
     blue_plane  = (byte **) input_Image->image_ptr[2]->rptr;    
     new_red_plane   = (byte **) NewImage->image_ptr[0]->rptr;    
     new_green_plane = (byte **) NewImage->image_ptr[1]->rptr;    
     new_blue_plane  = (byte **) NewImage->image_ptr[2]->rptr;    

     if (semaphore)
       {      
        for(y_row = row_value,y = 0; y_row < (rows - 1); y_row++, y += factor)
           {   
            row_count++;
            if (((skip - row_count) == 1) )
              {  y_row++; row_count = 0; }
            for(x_col = col_value, x = 0; x_col < (cols - 1); x_col++)
              {
               col_count++;
               if (((skip - col_count) == 1) )
                 {  x_col++; col_count = 0; }
               for (copy=x_cor=y_cor=0; copy < (factor * factor); copy++ )
                 {  
                  new_red_plane[y+y_cor][x+x_cor] = red_plane[y_row][x_col];
                  new_green_plane[y+y_cor][x+x_cor]=green_plane[y_row][x_col];
                  new_blue_plane[y+y_cor][x+x_cor++] = blue_plane[y_row][x_col]; 
                   if (x_cor == factor) 
                       {  y_cor++;x_cor=0;  }
	    	  } /* Inner for loop  */       
                x += factor;
               }
            }
        }  /* end of if semaphore */

     else if (!semaphore)
       {      
         for(y_row = row_value,y = 0; y_row < rows; y_row++, y += factor)
           for(x_col = col_value,  x = 0; x_col < cols; x_col++, x += factor)
             for (copy=0, x_cor=0, y_cor=0; copy < (factor * factor); copy++)
               {  
                 new_red_plane[y+y_cor][x+x_cor]  = red_plane[y_row][x_col]; 
                 new_green_plane[y+y_cor][x+x_cor]= green_plane[y_row][x_col];
                 new_blue_plane[y+y_cor][x+x_cor++] = blue_plane[y_row][x_col];   
                 if (x_cor == factor) 
                   {  y_cor++;x_cor=0;  }
               } /* Inner for loop  */       
       }  /* end of if else  */
   }  /* end of if (bands == 3)  */
 return (NewImage);
}
