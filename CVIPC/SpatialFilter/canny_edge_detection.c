/***************************************************************************
* =========================================================================
*
*   Computer Vision and Image Processing Lab - Dr. Scott Umbaugh SIUE
* 
* =========================================================================
*
*             File Name: canny_edge_detection.c 
*           Description: Canny's Edge Detector
*   Initial Coding Date: May 1st 2004
*           Portability: Standard (ANSI) C
*             Credit(s): Sushuma Gouravaram
*                        Southern Illinois University at Edwardsville
*
** Copyright (c) 1995, 2004, SIUE - Scott Umbaugh, Kun Luo, Yansheng Wei
****************************************************************************/


#include "CVIPtoolkit.h"
#include "CVIPconvert.h"
#include "CVIPdef.h"
#include "CVIPimage.h"
#include "CVIPgeometry.h"
#include <stdio.h>
#include "CVIPtoolkit.h"
#include "CVIPdrawimg.h"
#include "CVIPhisto.h"
#include "CVIPmap.h"
#include "CVIPview.h"
#include "math.h"
#include "CVIPobject.h"
#include "threshold.h"
#include "CVIPfs.h"
#include <CVIPmatrix.h>
#include <CVIPspfltr.h>
#include <limits.h>
#include <CVIPspfltr.h>



/*function prototypes */
float gauss_function(float x, float sigma);
float dGauss (float x, float sigma);
float meanGauss (float x, float sigma);
float norm ( int x, int y);
Image *convolution (Image *inputimage, Matrix *gau, int width, int which);
Image *diff_convolution (Image*inputimage, Matrix *dgau, int width,  int which);
void nonmax_suppress (Image *Image_dx, Image *Image_dy, Image *mag, Image *ori);
void hysteresis (float high, float low,Image *cvipImage, Image *mag, Image *dir);
int trace (int i, int j, float low, Image *cvipImage,Image *mag, Image *dir, int bands);
int range (Image *im, int i, int j);
void estimate_threshold (Image *mag, float *hi, float *low, int bands);
void canny(float var, Image *inputImage, Image *cvipImage, Image *cvipImage1);
void estimate_threshold1 ( Image *in, float *low, float *hi,int bands);


/* 
	low: range from 0 to 10, better use fraction between 0-1;if it's a noisy image, better go for low value>1;
	high: range from 0 to 10, better use fraction between 0-1;if it's a noisy image, better go for high value>1;
	var: has to be equal to or greater than 0.5 AND equal to or less than 5;
	
	note: low & high are not real threshold, they are a fraction of the estimated threshold that you would like to use;
	if low_thresh = 1, it uses the value estimated from the image for hysterisys threshold ;
	if high_thresh = 1, it uses the value estimated from the image for hysterisys threshold ;

	low = 0.2, 0.5, 1, 2, 5;
	high = 0.2, 0.5, 1, 2, 5;
	var = 0.5, 1, 1.5, 3;

    cam.pgm - 1,0.5,0.5
	worf.ppm - 1,1,1
*/

Image *canny_filter (float low, float high, float var, Image *inputImage, 
					 Image *nonmax_mag, Image *nonmax_dir)
{
	
    Image		*magImage;	/*magnitude of edges Image*/
	Image		*dirImage;	/*direction of edges Image*/
	Image       *cvipImage, 
				*cvipImage1;
    
  
	unsigned int 	no_of_rows,		/* number of rows in image */
					no_of_cols,		/* number of columns in image */
					no_of_bands;	/* number of image bands */

	COLOR_FORMAT	color_space;
	CVIP_TYPE		data_type;
	IMAGE_FORMAT        image_format; 
	
	/*get image properties*/
	data_type  =	getDataType_Image(inputImage);        
	image_format =   getFileFormat_Image(inputImage);
	color_space = getColorSpace_Image(inputImage);

	/*
    ** Gets the number of image bands (planes)
    */

    no_of_bands = getNoOfBands_Image(inputImage);

    /* 
    ** Gets the number of rows in the input image  
    */
    no_of_rows =  getNoOfRows_Image(inputImage);

    /* 
    ** Gets the number of columns in the input image  
    */
    no_of_cols =  getNoOfCols_Image(inputImage);
 
	/*convole filter takes only short ot byte inputs*/

	if(data_type== CVIP_INTEGER || data_type == CVIP_FLOAT)
	inputImage =  remap_Image(inputImage,CVIP_SHORT, 0, 255);
 
	magImage = new_Image(image_format, color_space, no_of_bands,
                            no_of_rows,no_of_cols, CVIP_FLOAT, REAL);

	dirImage = new_Image(image_format, color_space, no_of_bands,
                            no_of_rows,no_of_cols, CVIP_FLOAT, REAL);

	cvipImage1 = new_Image(image_format, color_space, no_of_bands,
                            no_of_rows,no_of_cols, CVIP_BYTE, REAL);
    	  
   /* Apply the gaussian mask and non max suppression*/
	cvipImage = duplicate_Image(inputImage);
	
	canny(var, cvipImage, magImage, dirImage);

	*nonmax_mag = *(duplicate_Image(magImage));
	*nonmax_dir = *(duplicate_Image(dirImage));
   
	/*perform hysteresis thresholding*/
	hysteresis (high, low, cvipImage1, magImage, dirImage);
	
  	return cvipImage1;

}


void canny(float var, Image *inputImage, Image *cvipImage, Image *cvipImage1)
{
	
	Image   *Image_x;
	Image	*Image_dx;
	Image	*Image_dy;

	unsigned int r,c,bands,half,size;
	
	Matrix *gau, *dgau;
	int u1=0, u2=0;
	float  max=0.0, min=10000.0;

	short **image1, **image2;
	float **image, **imageO;
	
	unsigned int 	no_of_rows,		/* number of rows in image */
					no_of_cols,		/* number of columns in image */
					no_of_bands;	/* number of image bands */

	/*
    ** Gets the number of image bands (planes)
    */

    no_of_bands = getNoOfBands_Image(inputImage);

    /* 
    ** Gets the number of rows in the input image  
    */
    no_of_rows =  getNoOfRows_Image(inputImage);

    /* 
    ** Gets the number of columns in the input image  
    */
    no_of_cols =  getNoOfCols_Image(inputImage);
 
   
   /* Create a Gaussian and a derivative of Gaussian filter mask */
  
	half = (int)(sqrt(-log(0.05) * 2 * var*var));
	size = 2*half + 1;
	
	printf ("size = %d",size);

	gau=new_Matrix(size, size ,CVIP_FLOAT,REAL);
      if(gau==NULL)
             printf("NULL");

	dgau=new_Matrix(size , size,CVIP_FLOAT,REAL);
      if(dgau==NULL)
             printf("NULL");

	 
	for(r=0; r < size; r++){

		for(c=0; c < size; c++)
		{
    
		u1= c+1-(size+1)/2; u2 = r+1-(size+1)/2;
	
		((float**)(gau->rptr))[r][c]=   gauss_function((float)u1, var) * gauss_function ((float)u2, var);
		
	//	printf (" u1 = %d, u2 = %d, value = %2f) ...\n",u1, u2,((float**)(gau->rptr))[r][c]);

		((float**)(dgau->rptr))[r][c] = gauss_function((float)u1, var) * dGauss ((float)u2, var);
	
	//	printf ("value  d = %2f) ...\n",((float**)(dgau->rptr))[r][c]);


		}

	}	

	printf ("The matrices are formed");

//	matrix_print(gau);
	
 	/*blur with gussian*/
	Image_x = duplicate_Image(inputImage);
	Image_x = convolve_filter(Image_x,gau);
   
	//view_Image(Image_x,"Image_x");
 
	Image_dx = duplicate_Image(Image_x);
	Image_dy = duplicate_Image(Image_x);
	
	/*convolve with deritavive masks in X and Y directions*/
//	matrix_print(dgau);
	Image_dx = convolve_filter(Image_dx,dgau);
//    view_Image(Image_dx,"Image_dx");
 
	dgau = transpose_Matrix(dgau);
//	matrix_print(dgau);

	Image_dy = convolve_filter(Image_dy,dgau);
//	view_Image(Image_dy,"Image_dy");


	delete_Matrix(gau);
    delete_Matrix(dgau);

	/* Create an image of the norm of dx,dy */

	for (bands =0; bands< no_of_bands; bands++){
	
		 image = getData_Image(cvipImage, bands);
		 imageO= getData_Image(cvipImage1, bands);
		 image1= getData_Image(Image_dx, bands);
		 image2= getData_Image(Image_dy, bands);
	  
	  for (r=0; r < no_of_rows; r++){
		for (c=0; c < no_of_cols; c++){
	     
			/* u1 = image1[r][c]*image1[r][c];
		   u2 = (image2[r][c]*image2[r][c]);
		   image[r][c] = sqrt (u1 + u2 );*/
		   
		   u1 = image1[r][c];
		   u2 = image2[r][c];
		   image[r][c] = norm (u1,u2);

		   if (image[r][c] > max) max = image[r][c];
		   if (image[r][c] <min) min = image[r][c];
		   imageO[r][c] = atan2(u2,u1);



		}
	  }
	}


	nonmax_suppress (Image_dx, Image_dy, cvipImage,cvipImage1);
	
	delete_Image(Image_x);
	Image_x = NULL;
	delete_Image(Image_dx);
	Image_dx = NULL;
  
	delete_Image(Image_dy);
	Image_dy = NULL;
	
}



/*      Gaussian        */
float gauss_function(float x, float sigma)
{
	float z;
    if (sigma == 0) return 0.0;
		z = (float)  (exp((double) ((-x*x)/(2*sigma*sigma))) ) / (sigma * sqrt(2*PI));
	return z;
}



/*      First derivative of Gaussian    */
float dGauss (float x, float sigma)
{
	return -x/(sigma*sigma) * gauss_function(x, sigma);
}


/*norm function*/
float norm ( int x, int y)
{
	return sqrt(x*x + y*y);
}

/*non maximum supress*/
void nonmax_suppress (Image *Image_dx, Image *Image_dy, Image *mag, Image *ori)
{
	int i,j,bands;
	unsigned int 	no_of_rows,		/* number of rows in image */
					no_of_cols,		/* number of columns in image */
					no_of_bands;	/* number of image bands */
	
	short			**image3, **image4;
	float			**image1, **image2, **image5;
	
	int				xc,yc,dx,dy;	
	float			aGx, aGy,m01, m11, m_01, m_11, m1, m2, mag1;

	Image  *temp;

	temp = duplicate_Image(mag);	
    /*
    ** Gets the number of image bands (planes)
    */

    no_of_bands = getNoOfBands_Image(Image_dx);

    /* 
    ** Gets the number of rows in the input image  
    */
    no_of_rows =  getNoOfRows_Image(Image_dx);

    /* 
    ** Gets the number of columns in the input image  
    */
    no_of_cols =  getNoOfCols_Image(Image_dx);
 
  
	for (bands=0; bands<no_of_bands; bands++){
		 
		 image1= getData_Image(temp, bands);
		 image2= getData_Image(ori, bands);
		 image3= getData_Image(Image_dy, bands);
		 image4= getData_Image(Image_dx, bands);
		 image5= getData_Image(mag, bands);
	  
	for (i=1; i<no_of_rows-1; i++)	{
	  for (j=1; j<no_of_cols-1; j++) {
	   
	  image5[i][j] = 0.0;
	  aGx = abs(image3[i][j]);
	  aGy = abs(image4[i][j]);

	  xc = image3[i][j];
	  yc = image4[i][j];

		//find direction
  	 if (image3[i][j]>0)
              dx = -1;
           else 
              dx = 1;
     if (image4[i][j]>0 )
              dy = 1;
           else
	      dy = -1;
         

     if(aGx>aGy) // x is dominant direction
		{ 
		   m01 = image1[i][j+dx];
           m11 = image1[i-dy][j+dx];
           m_01 = image1[i][j-dx];
           m_11 = image1[i+dy][j-dx];
          
		   m1 = (aGx-aGy)*m01 + aGy*m11;
           m2 = (aGx-aGy)*m_01 + aGy*m_11;
           mag1 = image1[i][j]*aGx;
           
		}
	else 	// y is dominant direction

		{
	       m01 = image1[i-dy][j];
           m11 = image1[i-dy][j+dx];
           m_01 = image1[i+dy][j];
           m_11 = image1[i+dy][j-dx];
          
	       m1 = (aGy-aGx)*m01 + aGx*m11;
           m2 = (aGy-aGx)*m_01 + aGx*m_11;
           mag1 = image1[i][j]*aGy;
         }

		if ((mag1>m2) && (mag1>=m1) ){
		image5[i][j] = image1[i][j];
		image2[i][j] = atan2(yc, xc);
		}
		else{
		image5[i][j] = 0;
		image2[i][j] = 0;
		}
  

	 }
	}
   }


return;
}




/*hysteresis***************************/

void hysteresis (float h, float l, Image *cvipImage, Image *mag, Image *dir)
{
	int i,j,bands;

	unsigned int 	no_of_rows,		/* number of rows in image */
					no_of_cols,		/* number of columns in image */
					no_of_bands;	/* number of image bands */

	float			**image2;
	byte			**image1;
 
	float high,low;
 	/*
    ** Gets the number of image bands (planes)
    */

    no_of_bands = getNoOfBands_Image(mag);

    /* 
    ** Gets the number of rows in the input image  
    */
    no_of_rows =  getNoOfRows_Image(mag);

    /* 
    ** Gets the number of columns in the input image  
    */
    no_of_cols =  getNoOfCols_Image(mag);


	for (bands=0;bands<no_of_bands; bands++){
		 
		low =l;
		high =h;
			
		image1= getData_Image(cvipImage, bands);
		image2= getData_Image(mag, bands);
		printf ("Beginning hysteresis thresholding in band %d \n", bands);
	
		for (i=0; i<no_of_rows; i++)
			for (j=0; j<no_of_cols; j++)
			image1[i][j] = 0;

		
		printf(" estimating the threshold for hysterisis");
		estimate_threshold (mag, &high, &low, bands);
		printf ("FinalHysteresis thresholds : HI %f LOW %f \n",high, low);


			/* For each edge with a magnitude above the high threshold, begin
		tracing edge pixels that are above the low threshold.                */

		for (i=0; i<no_of_rows; i++)
			for (j=0; j<no_of_cols; j++){
				if (image2[i][j] >= high)
				trace (i, j, low, cvipImage, mag, dir,bands);

			}		
				
				
				
//				printf("hello");
	
	}
	

}


/*  TRACE - recursively trace edge pixels that have a threshold > the low
	edge threshold, continuing from the pixel at (i,j).                     */

int trace (int i, int j, float low, Image *cvipImage,Image *mag, Image *dir, int bands)
{
	int n,m;
	char flag = 0;

	byte			**image3;

	float			**image1, **image2;

		 image1= getData_Image(mag, bands);
		 image2= getData_Image(dir, bands);
		 image3= getData_Image(cvipImage, bands);
		
	if (image3[i][j] == 0)
	{
	  image3[i][j] = 255;
	  flag=0;
	  
	  for (n= -1; n<=1; n++)
	  {
	    for(m= -1; m<=1; m++)
	    {
	     if (i==0 && m==0) continue;
	      if (range(mag, i+n, j+m) && image1[i+n][j+m] >=low)
	       if (trace(i+n, j+m, low, cvipImage,mag,dir,bands))
			{
		    flag=1;
		    break;
			}
	    }
	  if (flag) break;
		}
    return(1);
	}
  return(0);

}

/*range*/
int range (Image *im, int i, int j)
{
unsigned int 	no_of_rows,	/* number of rows in image */
				no_of_cols;	/* number of columns in image */
	
	/*Gets the number of rows in the input image */
    no_of_rows =  getNoOfRows_Image(im);

    /*  Gets the number of columns in the input image*/
    no_of_cols =  getNoOfCols_Image(im);
	
	if ((i<0) || (i>=no_of_rows)) return 0;
	if ((j<0) || (j>=no_of_cols)) return 0;
	return 1;
}


/*estimate the threshold limits for the image*/
void estimate_threshold (Image *mag, float *hi, float *low, int bands)
{
	int i,j,k, hist[256], count, nrows, ncols;

	float **image;

	float vmin, vmax, x, est_high, est_low;
	/* 
    ** Gets the number of rows in the input image  
    */
    nrows =  getNoOfRows_Image(mag);

    /* 
    ** Gets the number of columns in the input image  
    */
    ncols =  getNoOfCols_Image(mag);

    printf("In estimate threshold");

	image= getData_Image(mag, bands);


	vmin = vmax = fabs((float)(image[20][20]));
	for (i=0; i<nrows; i++)
	  for (j=0; j<ncols; j++)
	  {
            x = image[i][j];
	    if (vmin > x) vmin = x;
	    if (vmax < x) vmax = x;
	  }
	printf("here in est vmin = %f, vmax = %f", vmin, vmax);


	/* Build a histogram of the magnitude image. */
	for (k=0; k<256; k++) hist[k] = 0;

	for (i=0; i<nrows; i++)
	  for (j=0; j<ncols; j++)
	    hist[(int)image[i][j]] ++;

	/* The high threshold should be > 80 or 90% of the pixels 
	j = (int)(ratio*mag->info->nr*mag->info->nc);
	*/
	j = nrows;
	if (j<ncols) j = ncols;
	j = (int)(.05*nrows*ncols);
	k = 255;

	printf(" j = %d", j);

	count = hist[255];
	while (count < j)
	{
	  k--;
	  if (k<0) break;
	  count += hist[k];
	}


	printf(" k = %d", k);

	est_high = k;
	*hi = (*hi) * k;
	 if(*hi ==0)
		 *hi =1;
	printf(" estimated high thresh = %f", est_high);
	//*hi = k+vmin;
	i=0;
	while (hist[i]==0) i++;

	
	est_low	= (k+i)/2.0;
	printf(" estimated low thresh = %f", est_low);


	*low = (*low) * (k+i)/2.0;

	if(*low ==0)
		*low =1;

}

