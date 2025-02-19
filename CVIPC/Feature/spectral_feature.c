/******************************************************************************
    ======================================================================
    Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
    ======================================================================

                   Name: spectral_feature.c
          Expanded Name: spectral features

             Parameters: Pointer to the original image of type Image
                         Pointer to the labeled image of type Image
                         coordinates of the point on the labled image to
                         select the object of interest:
                         r -- row coordinate, c -- column coordinate

                Returns: pointer to a structure containing spectral features,
			 the structure is defined in newfeature.h.

                         If the original image is a color image, the first 
                         one, no_of_rings and no_of_sectors values pointed to by
			 dc, sector and band respectively in POWER are for band 0;
                         the following values are for band 1, and so on.

            Description: The original image can be of any data types: CVIP_BYTE,
                         CVIP_SHORT, CVIP_INTEGER, CVIP_FLOAT and CVIP_DOUBLE.
			 'no_of_bands' means 'number of rings' actually.

            Diagnostics: None

    Initial Coding Date: 6/16/96
Last Modifications Made: 7/15/96
             References: None

              Author(s): Wenxing Li


          Southern Illinois University @ Edwardsville

*******************************************************************************/


#include <math.h>
#include "CVIPimage.h"
#include "newfeature.h"
#include "CVIPtransform.h"

#define M_PI            3.14159265358979323846
#define M_PI_2          1.57079632679489661923


void init_power(Image * returnImage, int bands, int size, CVIP_TYPE dtype)
{
	int		   i, j, k;
	void		** newimage;

	for (k=0; k< bands; k++)	/* all assign 0 initially */
	{
		newimage = (void **) returnImage->image_ptr[k]->rptr;
		for (i=0; i < size; i++)
			for (j=0; j < size; j++)
				switch(dtype)
				{
					case CVIP_BYTE:  ((byte **)newimage)[i][j]  =  (byte)0;  break;
					case CVIP_SHORT: ((short **)newimage)[i][j] = (short)0;  break;
					case CVIP_INTEGER:((int **)newimage)[i][j]   =  (int)0;  break;
					case CVIP_FLOAT: ((float **)newimage)[i][j] = (float)0;  break;
					case CVIP_DOUBLE:((double **)newimage)[i][j]= (double)0; 
				}
	}
}


/* duplicate an object in a multiband real image */
Image * objectduplicate(Image * originalImage, Image * labeledImage, int label, int size, int xmin, int ymin)
{
	int		 ** labimage;
	void  		 ** origimage, ** newimage;
	int 	  	    i, j, k, m, n;
	CVIP_TYPE	  	    dtype;
	Image  	 *  returnImage;
	unsigned int 	    rows, cols;

	rows = originalImage->image_ptr[0]->rows;
	cols = originalImage->image_ptr[0]->cols;

	dtype = originalImage->image_ptr[0]->data_type;
	labimage = (int **)labeledImage->image_ptr[0]->rptr;
	returnImage = new_Image(originalImage->image_format, originalImage->color_space, 
	originalImage->bands, size, size, dtype, REAL);

	init_power(returnImage, originalImage->bands, size, dtype);

	for (k=0; k< originalImage->bands; k++)
	{
		newimage = (void **) returnImage->image_ptr[k]->rptr;
		origimage = (void **) originalImage->image_ptr[k]->rptr;
		for (i=xmin, m=0; i < rows && m < size; i++, m++)   /*according to the smaller one*/
			for (j=ymin, n=0; j < cols && n < size; j++, n++)
				if (labimage[i][j] == label) 
					switch(dtype)
					{
						case CVIP_BYTE:   ((byte **)newimage)[m][n] = ((byte **)origimage)[i][j];  break;
						case CVIP_SHORT: ((short **)newimage)[m][n] = ((short **)origimage)[i][j]; break;
						case CVIP_INTEGER: ((int **)newimage)[m][n] =   ((int **)origimage)[i][j]; break;
						case CVIP_FLOAT: ((float **)newimage)[m][n] = ((float **)origimage)[i][j]; break;
						case CVIP_DOUBLE:((double**)newimage)[m][n] = ((double**)origimage)[i][j]; 
					}
	}

	return (returnImage);
}

#define POWERPROCESS\
  {	register int	      i_, j_, ith_, jth_, xc_, yc_; \
	register double       power_, a_;\
	register unsigned int halfrows_, halfcols_;\
 	halfrows_ = rows/2; 	halfcols_ = cols/2;\
        for (i_=halfrows_+1; i_<rows; i_++)\
          for (j_=0; j_<cols; j_++)\
            { xc_ = i_ - halfrows_;\
              yc_ = j_ - halfcols_;\
	      power_ = rp[i_][j_]*rp[i_][j_] + ip[i_][j_]*ip[i_][j_];\
	      if (yc_ == 0) a_ = M_PI_2;	/* 90 degrees */ \
	      else 	    a_ = atan(xc_/yc_);\
	      if (a_ < 0)   a_ += M_PI;\
	      ith_ = a_ / angle;\
	      sector[k][ith_] += power_;\
	      jth_ = sqrt((xc_*xc_ + yc_*yc_)) / radius;\
	      band[k][jth_] += power_;\
            }\
        for (j_=halfcols_ + 1; j_<cols; j_++)\
          { power_ = rp[halfrows_][j_]*rp[halfrows_][j_] + ip[halfrows_][j_]*ip[halfrows_][j_];\
	    sector[k][0] += power_;\
	    jth_ = (j_- halfcols_) / radius;\
  	    band[k][jth_] += power_;\
          }\
  }


/* for fft only */
void power_compute(Image * fftImage, POWER * PP, int no_of_bands, int no_of_sectors, int size)
{
	int 	       	    i, k;
	float    	 ** rp, ** ip;
	double	    sector[10][100],  band[10][100];
	double	    angle, radius;
	unsigned int      rows, cols; 

	rows = fftImage->image_ptr[0]->rows;
	cols = fftImage->image_ptr[0]->cols;

	for (k=0; k<fftImage->bands; k++)
		for (i=0; i<100; i++) { sector[k][i] = 0; band[k][i] = 0; }

	angle  = M_PI / no_of_sectors;
	radius = (sqrt(rows*rows + cols*cols) / 2) / no_of_bands;
	for (k=0; k<fftImage->bands; k++)
	{
		rp = (float **)fftImage->image_ptr[k]->rptr;
		ip = (float **)fftImage->image_ptr[k]->iptr;
		(PP->dc)[k] = pow(rp[rows/2][cols/2], 2) + pow(ip[rows/2][cols/2], 2);
		POWERPROCESS
	}

	PP->no_of_bands = no_of_bands;
	PP->no_of_sectors = no_of_sectors;
	PP->imagebands  = fftImage->bands;
	for (k=0; k<fftImage->bands; k++)
	{
		for (i=0; i<no_of_sectors; i++)
		{
			if ((PP->dc)[k] >= 1) sector[k][i] /= (PP->dc)[k];
			(PP->sector)[k*no_of_sectors + i] = sector[k][i];
		}
		for (i=0; i<no_of_bands; i++)
		{
			if ((PP->dc)[k] >= 1) band[k][i] /= (PP->dc)[k];
			(PP->band)[k*no_of_bands + i] = band[k][i];
		}
		(PP->dc)[k] = (PP->dc)[k] / pow(size, 4); 
	}      
}


int preprocess_power(Image * labeledImage, int label, int * minx, int * miny)
{
	int 		xmin, xmax, ymin, ymax, i, j, k=0, size;
	int 	     ** image;
	unsigned int   rows, cols; 

	rows =  getNoOfRows_Image(labeledImage);
	cols =  getNoOfCols_Image(labeledImage);
	image = (int **)getData_Image(labeledImage, 0);

	xmin = rows; xmax = 0;
	ymin = cols; ymax = 0;

	for (i=0; i<rows; i++)
		for (j=0; j<cols; j++)
			if (image[i][j] == label)
			{
				if (xmin > i) xmin = i;
				if (xmax < i) xmax = i;
				if (ymin > j) ymin = j;
				if (ymax < j) ymax = j;
			}

	/* choose the longer side */
	if ( (xmax-xmin) > (ymax-ymin) ) size = xmax - xmin + 1;
	else				  size = ymax - ymin + 1;

	/* if the longer side is not power of 2, enlarge it to be power of 2*/
	for (i=0, j=2; i<9 && j<size; i++, j*=2) if (size % j != 0) k++;
	if (k != 0) 	size = j;

	*minx = xmin;    *miny = ymin;
	return (size);
}


POWER * spectral_feature(Image * originalImage, Image * labeledImage, int no_of_bands, int no_of_sectors, int r, int c)
{
	int     label, size, xmin, ymin;
	POWER * PP;
	Image * newobjectImage, * fftImage;

	label = ((int **)(labeledImage->image_ptr[0]->rptr))[r][c];

	PP = (POWER *)malloc((sizeof(POWER)+2));
	PP->dc	    = (double *)malloc(originalImage->bands*sizeof(double));
	PP->sector = (double *)malloc(originalImage->bands*no_of_sectors*sizeof(double));
	PP->band   = (double *)malloc(originalImage->bands*no_of_bands*sizeof(double));

	size  =  preprocess_power(labeledImage, label, &xmin, &ymin);
	newobjectImage = objectduplicate(originalImage, labeledImage, label, size, xmin, ymin);

	fftImage = (Image *)fft_transform(newobjectImage, size);

	printf("power computing...\n");
	power_compute(fftImage, PP, no_of_bands, no_of_sectors, size);

	delete_Image(fftImage); 
	return (PP);
}
