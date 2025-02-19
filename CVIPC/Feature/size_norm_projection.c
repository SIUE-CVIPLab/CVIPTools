/******************************************************************************
    ======================================================================
    Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
    ======================================================================

                   Name: size_norm_projection.c
          Expanded Name: size normalized projections

             Parameters: Pointer to the labeled image of type Image
                         coordinates of the point on the labled image to
                         select the object of interest:
                         r -- row coordinate, c -- column coordinate
			 normalized height
			 normalized width

                Returns: pointer to an array containing horizontal and vertical
			 projections.

            Description: None

            Diagnostics: None

    Initial Coding Date: 7/24/96
Last Modifications Made: 
             References: None

              Author(s): Wenxing Li


          Southern Illinois University @ Edwardsville

*******************************************************************************/


#include <math.h>
#include "CVIPimage.h"
#include "CVIPgeometry.h"


float prep_projection(Image * labeledImage, int label, int * minx, int * miny,
		    int height, int width)
{
 int 		xmin, xmax, ymin, ymax, i, j, k=0;
 int 	     ** image;
 unsigned int   rows, cols; 
 float		ratio, wr, hr;

 rows =  getNoOfRows_Image(labeledImage);
 cols =  getNoOfCols_Image(labeledImage);
 image = (int **)getData_Image(labeledImage, 0);

 xmin = rows; xmax = 0;
 ymin = cols; ymax = 0;

 for (i=0; i<rows; i++)
   for (j=0; j<cols; j++)
      if (image[i][j] == label)
	{ if (xmin > i) xmin = i;
	  if (xmax < i) xmax = i;
	  if (ymin > j) ymin = j;
	  if (ymax < j) ymax = j;
	 }

 wr = (float)width / (ymax-ymin+1);
 hr = (float)height/ (xmax-xmin+1);

/* choose the smaller one */
 if ( wr < hr ) ratio = wr;
 else		ratio = hr;

 *minx = xmin;    *miny = ymin;
 return (ratio);
}


/* duplicate an object for size-normalized projections */
Image * objdup_projection(Image * labeledImage, int label, int height, int width,
		          float ratio, int xmin, int ymin)
{int		 ** labimage, ** newimage;
 int 	  	    i, j, m, n;
 Image  	 *  returnImage;
 int		    nrow, ncol;
 unsigned int 	    rows, cols;

 rows = labeledImage->image_ptr[0]->rows;
 cols = labeledImage->image_ptr[0]->cols;

 labimage = (int **)labeledImage->image_ptr[0]->rptr;
 nrow = (int)(height/ratio);
 if ((height/ratio - nrow) > 0.9) nrow++;
 ncol = (int)(width/ratio);
 if ((width/ratio - ncol) > 0.9) ncol++;

 returnImage = new_Image(labeledImage->image_format, labeledImage->color_space,
			 1, nrow, ncol, CVIP_INTEGER, REAL);

 newimage = (int **) returnImage->image_ptr[0]->rptr;
 for (i=0; i < nrow; i++)
   for (j=0; j < ncol; j++) newimage[i][j] = 0;

 for (i=xmin, m=0; i < rows; i++, m++)   
   for (j=ymin, n=0; j < cols; j++, n++)
     if (labimage[i][j] == label)  newimage[m][n] = labimage[i][j];

 return (returnImage);
}


int * get_projection(Image * inputImage, int height, int width)
{int            i, j;
 int         ** image;
 unsigned int   rows, cols;
 int          * ptr;

 rows = inputImage->image_ptr[0]->rows;
 cols = inputImage->image_ptr[0]->cols;
 image = (int **)inputImage->image_ptr[0]->rptr;
 
 ptr = (int *)malloc((height+width)*sizeof(int));
 for (i=0; i<(height+width); i++) ptr[i] = 0;

 for (i=0; i<rows; i++)
   for (j=0; j<cols; j++)
     if (image[i][j] != 0 ) { ptr[i]++; ptr[height+j]++;}

 return (ptr);
}

/* return NULL if error happens */
int * projection(Image * labeledImage, int r, int c, int height, int width)
{int 		label, minx, miny;
 float		ratio;
 int	      * ptr;
 Image	      * objectImage, * normImage;
 unsigned int   rows, cols;

 label = ((int **)labeledImage->image_ptr[0]->rptr)[r][c];

 ratio = prep_projection(labeledImage, label, &minx, &miny, height, width);

 objectImage = objdup_projection(labeledImage, label, height, width, ratio, minx, miny);
 rows = objectImage->image_ptr[0]->rows;
 cols = objectImage->image_ptr[0]->cols;

 if (height > rows && width > cols) 
   normImage = (Image *)enlarge(objectImage, height, width);

 if (height < rows && width < cols)
   normImage = (Image *)spatial_quant(objectImage, height, width, 3);

 if (height == rows || width == cols) 
   { if (height == rows && width < cols) return NULL;
     if (width == cols && height < rows) return NULL;   
     normImage = objectImage;
   }

 ptr = get_projection(normImage, height, width);

 delete_Image(normImage);	/* only this */

 return (ptr);
}
