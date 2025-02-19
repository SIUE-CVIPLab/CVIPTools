/******************************************************************************
    ======================================================================
    Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
    ======================================================================

                   Name: binary_feature.c
          Expanded Name: features of the binary object(Area)

             Parameters: Pointer to the labeled image of type Image and 
			 coordinates of the point on the labled image

                Returns: a feature value or pointer to values

            Description: Computes eight features of the binary object:
			 area, perimeter, centroid, axis of least second moment,
			 thinness ratio, aspect ratio, euler number and 
			 horizontal & vertical projections

            Diagnostics: None

    Initial Coding Date: 6/22/96
Last Modifications Made: 7/1/96
             References: None

              Author(s): Wenxing Li

 
          Southern Illinois University @ Edwardsville


*******************************************************************************/

#include <math.h>
#include "ObjectContour.h"


extern short build_ChainCode(ChainCode *, Image *, int, int, int, int);
extern ChainCode * new_ChainCode(int, int, int);
extern void delete_ChainCode(ChainCode *);

#define M_PI            3.14159265358979323846
#define M_PI_2          1.57079632679489661923

int perimeter(Image * labeledImage, int r, int c)
{
 int 		xmin, xmax, ymin, ymax, label;
 int 		i, j, check=1, xstart=0, ystart=0;
 int 		pvalue;
 int 	     ** image;
 unsigned int   rows, cols; 
 ChainCode    * ccP;

 rows =  getNoOfRows_Image(labeledImage);
 cols =  getNoOfCols_Image(labeledImage);
 image = (int **)getData_Image(labeledImage, 0);

 xmin = rows;  xmax = 0;
 ymin = cols;  ymax = 0;
 label = image[r][c];

 for (i=0; i<rows; i++)
   for (j=0; j<cols; j++)
      if (image[i][j] == label)
	{ if (xmin > i) xmin = i;
	  if (xmax < i) xmax = i;
	  if (ymin > j) ymin = j;
	  if (ymax < j) ymax = j;
	  if (check) { xstart = i; ystart = j; check = 0;}
	}

 ccP = new_ChainCode(xstart, ystart, label);
 build_ChainCode(ccP, labeledImage, ymin, xmin, ymax, xmax);

 pvalue = ccP->no_of_vectors;
 delete_ChainCode(ccP);
 return (pvalue);
}

long area(Image * labeledImage, int r, int c)
{int 	i, j, label;
 int ** image;
 unsigned int rows, cols; 
 long   aarea=0;

 rows = labeledImage->image_ptr[0]->rows;
 cols = labeledImage->image_ptr[0]->cols;
 image = (int **)labeledImage->image_ptr[0]->rptr;
 label = image[r][c];

 for (i=0; i<rows; i++)
   for (j=0; j<cols; j++)
      if (image[i][j] == label) aarea++;

 return (aarea);
}

int * centroid(Image * labeledImage, int r, int c)
{
	int		i, j, label;
	int		**image,*ptr;
	unsigned	rows,cols; 
	long		aarea=0, ri=0, ci=0;

	ptr = (int *)malloc(2 * sizeof(int));
	if(ptr == NULL)
	{
		error_CVIP("centroid","Unable to allocate memory.\n");
		return(NULL);
	}
	
	rows = labeledImage->image_ptr[0]->rows;
	cols = labeledImage->image_ptr[0]->cols;
	image = (int **)labeledImage->image_ptr[0]->rptr;
	label = image[r][c];

	for (i=0; i<rows; i++)
	for (j=0; j<cols; j++)
	if (image[i][j] == label) { aarea++; ri += i; ci += j;}

	ptr[0] = (int)(ri / aarea);
	ptr[1] = (int)(ci / aarea);

	if (((float)ri/aarea - ptr[0]) > 0.5) ptr[0]++;
	if (((float)ci/aarea - ptr[1]) > 0.5) ptr[1]++;

	return(ptr);
}

double orientation(Image * labeledImage, int r, int c)
{
	int		i, j, label;
	int		**image;
	unsigned	rows,cols; 
	long		rc=0, rr=0, cc=0;
	double		theta;
	int		*cen;

	cen = centroid(labeledImage,r,c);
	if(cen == NULL)
	return(HUGE_VAL);

	rows = labeledImage->image_ptr[0]->rows;
	cols = labeledImage->image_ptr[0]->cols;
	image = (int **)labeledImage->image_ptr[0]->rptr;
	label = image[r][c];

	for (i=0; i<rows; i++)
	for (j=0; j<cols; j++)
	if (image[i][j] == label)
	{
		rc += (i-cen[0])*(j-cen[1]);
		rr += (i-cen[0])*(i-cen[0]);
		cc += (j-cen[1])*(j-cen[1]);
	}

/*	theta = 0.5 * atan(2.0*(double)rc/((double)(rr-cc)));*/
	theta = 0.5 * atan2(2.0*(double)rc,(double)(rr-cc));
	theta *= 180.0/M_PI;

	free(cen);
	return(theta);
}

double thinness(Image * labeledImage, int r, int c)
{
 int	pl;
 long   aarea;

 pl = perimeter(labeledImage, r, c);
 aarea = area(labeledImage, r, c);

 return((4.0*M_PI*aarea)/(pl*pl));
}

double irregular(Image * labeledImage, int r, int c)
{
 int    pl;
 long   aarea;

 pl = perimeter(labeledImage, r, c);
 aarea = area(labeledImage, r, c);

 return((pl*pl)/(4.0*M_PI*aarea));
}

double aspect(Image * labeledImage, int r, int c)
{
 int 		xmin, xmax, ymin, ymax, label;
 int 		i, j;
 int 	     ** image;
 unsigned int   rows, cols; 

 rows =  getNoOfRows_Image(labeledImage);
 cols =  getNoOfCols_Image(labeledImage);
 image = (int **)getData_Image(labeledImage, 0);

 xmin = rows;  xmax = 0;
 ymin = cols;  ymax = 0;
 label = image[r][c];

 for (i=0; i<rows; i++)
   for (j=0; j<cols; j++)
     if (image[i][j] == label)
	{ if (xmin > i) xmin = i;
	  if (xmax < i) xmax = i;
	  if (ymin > j) ymin = j;
	  if (ymax < j) ymax = j;
	}

 return ( (double)(ymax-ymin+1) / (xmax-xmin+1));
}

int euler(Image * labeledImage, int r, int c)
{int 		i, j, label;
 int 	     ** image;
 unsigned int   rows, cols; 
 long		convex=0, concav=0;

 rows = labeledImage->image_ptr[0]->rows;
 cols = labeledImage->image_ptr[0]->cols;
 image = (int **)labeledImage->image_ptr[0]->rptr;
 label = image[r][c];

 for (i=1; i<rows; i++)
   for (j=1; j<cols; j++)
     if (image[i][j] == label)
       { if (image[i-1][j-1] != label && image[i-1][j] != label
	     && image[i][j-1] != label) convex++;
	 if (image[i-1][j-1] != label && image[i-1][j] == label
	     && image[i][j-1] == label) concav++;
       }

 return ((int)(convex-concav));
}

int * t_projection(Image * labeledImage, int r, int c)
{int 		i, j, label;
 int 	     ** image;
 unsigned int   rows, cols; 
 int	      * ptr, *p , a[2048];

 rows = labeledImage->image_ptr[0]->rows;
 cols = labeledImage->image_ptr[0]->cols;
 image = (int **)labeledImage->image_ptr[0]->rptr;
 label = image[r][c];

 ptr = (int *)malloc((rows+cols)*sizeof(int));
 for (i=0; i<2048; i++) a[i] = 0;

 for (i=0; i<rows; i++)
   for (j=0; j<cols; j++)
     if (image[i][j] == label) { a[i]++; a[rows+j]++;}

 p = ptr + 2;
 for (i=0, j=0; i<rows; i++) 
   if (a[i]!=0) { *p=a[i]; j++; p++;}

 ptr[0] = j;
 for (i=0, j=0; j<cols; j++)
   if (a[rows+j]!=0) { *p=a[rows+j]; i++; p++;}

 ptr[1] = i;
 return (ptr);
}

