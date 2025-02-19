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


#define EDGE_X 252
#define EDGE_Y 253
#define EDGE_45 254
#define EDGE_135 255

#define diag_scale 1.414 

#define image_zc_x(r,c, detx, bands) \
(((image_locx(c,r,detx, bands)>0) != (image_locx(c+1,r,detx, bands)>0)) ?EDGE_X:0)

#define image_zc_y(r,c, dety, bands) \
(((image_locy(c,r+1,dety, bands)>0) != (image_locy(c,r,dety, bands)>0)) ?EDGE_Y:0)

#define image_zc_135(r,c, det135, bands) \
(((image_loc135(c+1,r+1,det135, bands)>0) != (image_loc135(c,r,det135, bands)>0)) ?EDGE_135:0)

#define image_zc_45(r,c,det45, bands) \
(((image_loc45(c-1,r+1,det45, bands)>0) != (image_loc45(c,r,det45, bands)>0)) ?EDGE_45:0)


/*function prototypes */
float gaussboie(float x, float sigma);
Image *image_detx (Image *gauImage);
Image *image_dety (Image *gauImage);
Image *image_det45 (Image *gauImage);
Image *image_det135 (Image *gauImage);

/*loc*/
int image_locx ( int iy,  int ix,  Image *image, int bands);
int image_locy ( int iy,  int ix,  Image *image, int bands);
int image_loc45 ( int iy,  int ix,  Image *image, int bands);
int image_loc135 ( int iy,  int ix,  Image *image, int bands);


int image_threshold (Image * detx,int Bands);
Image *image_hysteresis (Image *detx,Image *dety,Image *det45,Image *det135,
				  Image *ImageEdge,int lo_thld);

void image_neighbor_fwd (Image *detx,Image *dety,Image *det45,Image *det135, Image *ImageHyst,
					unsigned int iy, unsigned int ix,unsigned int bands, int lo_thld);

void image_neighbor_bwd (Image *detx,Image *dety,Image *det45,Image *det135,  Image *ImageHyst,
					unsigned int iy, unsigned int ix,unsigned int bands, int lo_thld);

int Bcontour (Image *detx,Image *dety,Image *det45,Image *det135, Image *ImageHyst,
		  unsigned int iy, unsigned int ix,unsigned int bands,int lo_thld);

int Fcontour (Image *detx,Image *dety,Image *det45,Image *det135, Image *ImageHyst,
		  unsigned int iy, unsigned int ix,unsigned int bands,int lo_thld);

byte image_edge_map_lo (Image *detx,Image *dety,Image *det45,Image *det135,
				   unsigned int ix, unsigned int iy, unsigned int bands,int lo_thld);

Image *image_thin ( Image *InputImage);

/*main******************************************
var - variance of gaussian for smoothing (0.5-5)

if (do_threshold  == 1){
then get threshold factor for ordianry thresholding 
0 < threshold factor < 10
if factor  =1 then mean absolute value of the image is used as threshold. 'high_thld' 
is the variable used to store this threshold value. low_thld in this case will be 0.

if factor !=1 the threshold = factor * mean absolute value of image
  do not show hyst threshold factor options
}
else if (do_hysterisis == 1){
then get low threshold factor and high threshold factor such that high > low always
and

 the high threshold = high factor * mean absolute value
 the low threshold = low factor * high threshold * 0.5

 therefore range for high factor 0-10.
 but range for low factor = 0-1.
 
 do not show odinary threshold factor options 
 
}

do_thin  - 0 or 1 
        0- no thinning, 1- thinning is done which means the thickness of 
        edges is reduced

***************************************/

Image *boiecox_filter ( Image *inputImage, float var, unsigned int do_thresh, unsigned int do_hyst,
					   unsigned int thin,float high_thld, float low_thld, Image *Imagethld, Image *Imagehyst)

{
	Image		*Image_x, *Imagedetx, 
				*Imagedety, *Imagedet45, 
				*Imagedet135, *ImageEdge;
	
	unsigned int r, c, bands,
				 half, size, count=0;	
	
	int				u1=0, u2=0;
	Matrix			*gau;

	int threshold, l_threshold;	
	CVIP_TYPE    data_type;
	COLOR_FORMAT color_space;
	IMAGE_FORMAT image_format;

	short		**imagex, **imagey,**image45, **image135; 
	byte		**imageE;
	
	unsigned int 	no_of_rows,		/* number of rows in image */
					no_of_cols,		/* number of columns in image */
					no_of_bands;	/* number of image bands */
	
	color_space	 = getColorSpace_Image(inputImage);
	image_format = getFileFormat_Image(inputImage); 
	data_type	 = getDataType_Image(inputImage);        

	/*conovolve filter accepts only short or byte data types*/

	if(data_type== CVIP_INTEGER || data_type == CVIP_FLOAT)
	inputImage =  remap_Image(inputImage,CVIP_SHORT, 0, 255);
 

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

	for(r=0; r < size; r++){
		for(c=0; c < size; c++)
		{    
		u1= c+1-(size+1)/2; u2 = r+1-(size+1)/2;
			((float**)(gau->rptr))[r][c]=   gaussboie((float)u1, var) * 
				gaussboie ((float)u2, var);
			//	printf (" u1 = %d, u2 = %d, value = %2f) ...\n",u1, u2,((float**)(gau->rptr))[r][c]);
		}
	}	

	matrix_print(gau);
	
	/*blur with gussian*/
	Image_x = duplicate_Image(inputImage);

	Image_x = convolve_filter(Image_x,gau);
		
	Imagedetx = duplicate_Image(Image_x);
	Imagedetx = image_detx (Image_x);

	Imagedety = duplicate_Image(Image_x);
	Imagedety = image_dety (Image_x);

	Imagedet45 = duplicate_Image(Image_x);
	Imagedet45 = image_det45 (Image_x);

	Imagedet135 = duplicate_Image(Image_x);
	Imagedet135 = image_det135 (Image_x);
   
	ImageEdge=new_Image(image_format, color_space, no_of_bands,
                            no_of_rows,no_of_cols, CVIP_BYTE, REAL);

	for(bands=0; bands< no_of_bands; bands++){	
					
			imagex= getData_Image(Imagedetx, bands);
			imagey= getData_Image(Imagedety, bands);
			image45= getData_Image(Imagedet45, bands);
			image135= getData_Image(Imagedet135, bands);
			imageE= getData_Image(ImageEdge, bands);

			threshold = image_threshold (Imagedetx, bands);
			if(do_thresh ==1 || do_hyst ==1)
			threshold = high_thld * threshold;

			printf(" \n\nThreshold in %d  = %d", bands, threshold);

		for (r = 0; r < no_of_rows; r++) {
			for (c = 0; c < no_of_cols; c++) {    
						
			int sx, sy, s45, s135, orient_flag;
			int big;
			sx = abs (imagex[r][c]);					
			sy = abs (imagey[r][c]);		
			s45 = (int) ((float) (abs (image45[r][c])) / diag_scale);		
			s135 = (int) ((float) (abs (image135[r][c])) / diag_scale);
				
			big = sx;
			orient_flag = EDGE_X;

			if (sy > big) {
				big = sy;
			orient_flag = EDGE_Y;
			}
			if (s45 > big) {
			big = s45;
			orient_flag = EDGE_45;
			}
			if (s135 > big) {
			big = s135;
			orient_flag = EDGE_135;
			}

			if (big > threshold) {
				
				switch (orient_flag) {
				case EDGE_X:
					imageE[r][c] = image_zc_x (r, c, Imagedetx, bands);
					break;
				case EDGE_Y:
					imageE[r][c] = image_zc_y (r, c, Imagedety, bands);
					break;
				case EDGE_45:
					imageE[r][c] = image_zc_45 (r, c, Imagedet45, bands);
					break;
				case EDGE_135:
					imageE[r][c] = image_zc_135 (r, c, Imagedet135, bands);
					break;
				default:
					fprintf (stderr, "error in case statements\n");
					exit (1);
					break;
				}
			}
			else {
			imageE[r][c] = 0;
			}
		
		
			}
			
			//printf("I ma here %d", count);
			//count ++;
			
		}

	}

	*Imagethld = *(duplicate_Image(ImageEdge));

	if (do_hyst == 1){
			l_threshold = threshold * low_thld *0.5;

	ImageEdge = image_hysteresis (Imagedetx,Imagedety,Imagedet45,Imagedet135,
									ImageEdge, l_threshold);
	}
	*Imagehyst = *(duplicate_Image(ImageEdge));

	if (thin ==1)
	ImageEdge = image_thin(ImageEdge);
	
	printf("\n\n returning from boiecox");

	return(ImageEdge);

}


/*      Gaussian        */
float gaussboie(float x, float sigma)
{
	float z;
    if (sigma == 0) return 0.0;
		z = (float)  (exp((double) ((-x*x)/(2*sigma*sigma))) ) / (sigma * sqrt(2*PI));
	return z;
}



/*compute detx*/
Image *image_detx (Image *gauImage)
{
  
	unsigned int r,c,bands;

	Image		*detxImage;
	short		**image1, **image2;


	unsigned int 	no_of_rows,		/* number of rows in image */
					no_of_cols,		/* number of columns in image */
					no_of_bands;	/* number of image bands */

	/*
    ** Gets the number of image bands (planes)
    */

    no_of_bands = getNoOfBands_Image(gauImage);

    /* 
    ** Gets the number of rows in the input image  
    */
    no_of_rows =  getNoOfRows_Image(gauImage);

    /* 
    ** Gets the number of columns in the input image  
    */
    no_of_cols =  getNoOfCols_Image(gauImage);

  	detxImage  = duplicate_Image(gauImage);

	for (bands =0; bands< no_of_bands; bands++){

		/*
		* Left Col/side
		*/
	
		image1= getData_Image(detxImage, bands);
		image2= getData_Image(gauImage, bands);
 
		for (r = 0; r < no_of_rows; r++) {
	
			image1[r][0] = image2[r][1]- image2[r][0];
    
		}
		/*
		*  Middle Cols
		*/
		for (r = 0; r < no_of_rows; r++) {
			for (c = 1; c <no_of_cols-1 ; c++) {

			image1[r][c] = image2[r][c+1]- image2[r][c-1];

			}
		}

		/*
		* Right Col/Side
		*/
		for (r = 0; r < no_of_rows; r++) {
				image1[r][no_of_cols-1] = image2[r][no_of_cols-1]- image2[r][no_of_cols-2];
    		}
	}


printf("\n\n returning from image_detx");
return (detxImage);


}


Image *image_dety (Image *gauImage)
{
  
	unsigned int r,c,bands;

	Image		*detyImage;
	short		**image1, **image2;


	unsigned int 	no_of_rows,		/* number of rows in image */
					no_of_cols,		/* number of columns in image */
					no_of_bands;	/* number of image bands */

	/*
    ** Gets the number of image bands (planes)
    */

    no_of_bands = getNoOfBands_Image(gauImage);

    /* 
    ** Gets the number of rows in the input image  
    */
    no_of_rows =  getNoOfRows_Image(gauImage);

    /* 
    ** Gets the number of columns in the input image  
    */
    no_of_cols =  getNoOfCols_Image(gauImage);
  	
	detyImage  = duplicate_Image(gauImage);

	for (bands =0; bands< no_of_bands; bands++){
		/*
		* Top Row
		*/
	
		image1= getData_Image(detyImage, bands);
		image2= getData_Image(gauImage, bands);
 
		for (c = 0; c < no_of_cols; c++) {
			image1[0][c] = image2[1][c]- image2[0][c];
    
		}
		/*
		* Middle Rows
		*/
		for (r = 1; r < no_of_rows-1; r++) {
			for (c = 0; c <no_of_cols ; c++) {

			image1[r][c] = image2[r+1][c]- image2[r-1][c];

			}
		}

		/*
		* Bottom row
		*/
		for (c = 0; c < no_of_cols; c++) {
				image1[no_of_rows-1][c] = image2[no_of_rows-1][c]- image2[no_of_rows-2][c];
    		}
	}

	printf("\n\n returning from image_dety");

	return (detyImage);
}




Image *image_det45 (Image *gauImage)
{
  
	unsigned int r,c,bands;

	Image *det45Image;
	short **image1, **image2;


	unsigned int 	no_of_rows,		/* number of rows in image */
					no_of_cols,		/* number of columns in image */
					no_of_bands;	/* number of image bands */

	/*
    ** Gets the number of image bands (planes)
    */

    no_of_bands = getNoOfBands_Image(gauImage);

    /* 
    ** Gets the number of rows in the input image  
    */
    no_of_rows =  getNoOfRows_Image(gauImage);

    /* 
    ** Gets the number of columns in the input image  
    */
    no_of_cols =  getNoOfCols_Image(gauImage);
  	
	det45Image  = duplicate_Image(gauImage);

	for (bands =0; bands< no_of_bands; bands++){
	
		/*
		* Top row WITHOUT CORNER PIXCELS
		*/
	
		image1= getData_Image(det45Image, bands);
		image2= getData_Image(gauImage, bands);
 
		for (c = 1; c < no_of_cols-1; c++) {
			image1[0][c] = image2[1][c-1]- image2[0][c+1];
		}

		 /*
		* Diagonal
		*/
		for (r = 1; r < no_of_rows-1; r++) {
				for (c = 1; c < no_of_cols-1; c++) {
				image1[r][c] = image2[r+1][c-1]- image2[r-1][c+1];
				}
			}
  
		/*
		* Left Col
		*/
		for (r = 1; r < no_of_rows-1; r++) {
			image1[r][0] = image2[r+1][0]- image2[r-1][1];
		}
		
		/*
		* Right Col
		*/
		for (r = 1; r < no_of_rows-1; r++) {
			image1[r][no_of_cols-1] = image2[r+1][no_of_cols-2]- image2[r-1][no_of_cols-1];
		}
 
		/*
		 * Bottom Row WITHOUT CORNER PIXCELS
		 */
		for (c = 1; c < no_of_cols-1; c++) {
			image1[no_of_rows-1][c] = image2[no_of_rows-1][c-1]- image2[no_of_rows-2][c+1];
		}
  
		/*
		* Now the top left Corner
		*/
		image1[0][0] = image2[1][0]- image2[0][1];
		
		/*
		* Now th bottom left corner
		*/
		image1[no_of_rows-1][0] = image2[no_of_rows-1][0]- image2[no_of_rows-2][1];
		
		/*
		 * Now the bottom right corner
		 */
		image1[no_of_rows-1][no_of_cols-1] = image2[no_of_rows-1][no_of_cols-2]
											- image2[no_of_rows-2][no_of_cols-1];
		/*
		* Now the top right Corner
		*/
		image1[0][no_of_cols-1] = image2[1][no_of_cols-2]
											- image2[0][no_of_cols-1];
		
	}
printf("\n\n returning from image_det45");

	return (det45Image);
}

/*Determie Image 135*/
Image *image_det135 (Image *gauImage)
{
  
	unsigned int	r,c,bands;

	Image			*det135Image;
	short			**image1, **image2;


	unsigned int 	no_of_rows,		/* number of rows in image */
					no_of_cols,		/* number of columns in image */
					no_of_bands;	/* number of image bands */

	/*
    ** Gets the number of image bands (planes)
    */

    no_of_bands = getNoOfBands_Image(gauImage);

    /* 
    ** Gets the number of rows in the input image  
    */
    no_of_rows =  getNoOfRows_Image(gauImage);

    /* 
    ** Gets the number of columns in the input image  
    */
    no_of_cols =  getNoOfCols_Image(gauImage);
  	
	det135Image  = duplicate_Image(gauImage);
	
	for (bands =0; bands< no_of_bands; bands++){
	
		image1= getData_Image(det135Image, bands);
		image2= getData_Image(gauImage, bands);
		/*
		* Top row WITHOUT CORNER PIXCELS
		*/
		for (c = 1; c < no_of_cols-1; c++) {
			image1[0][c] = image2[1][c+1]- image2[0][c-1];
		}

		/*
		* Diagonal
		*/

			for (r = 1; r < no_of_rows-1; r++) {
				for (c = 1; c < no_of_cols-1; c++) {
				image1[r][c] = image2[r+1][c+1]- image2[r-1][c-1];
				}
			}

  		/*
		* Left Col
		*/

		for (r = 1; r < no_of_rows-1; r++) {
			image1[r][0] = image2[r+1][1]- image2[r-1][0];
		}
		
		/*
		* Right Col
		*/
		for (r = 1; r < no_of_rows-1; r++) {
			image1[r][no_of_cols-1] = image2[r+1][no_of_cols-1]- image2[r-1][no_of_cols-2];
		}
 
		/*
		 * Bottom Row WITHOUT CORNER PIXCELS
		 */
		for (c = 1; c < no_of_cols-1; c++) {
			image1[no_of_rows-1][c] = image2[no_of_rows-1][c+1]- image2[no_of_rows-2][c-1];
		}
  
		/*
		* Now the top left Corner
		*/
		image1[0][0] = image2[1][1]- image2[0][0];
		
		/*
		* Now th bottom left corner
		*/
		image1[no_of_rows-1][0] = image2[no_of_rows-1][1]- image2[no_of_rows-2][0];
		
		/*
		 * Now the bottom right corner
		 */
		image1[no_of_rows-1][no_of_cols-1] = image2[no_of_rows-1][no_of_cols-1]
											- image2[no_of_rows-2][no_of_cols-2];

		/*
		* Now the top right Corner
		*/
		image1[0][no_of_cols-1] = image2[1][no_of_cols-1]
											- image2[0][no_of_cols-2];
		
	}
printf("\n\n returning from image_det135");

	return (det135Image);
}

/*Locx*/
int image_locx ( int iy,  int ix, Image *detx, int bands)
{                               
	
	short **image;
   	unsigned int 	nx,		/* number of rows in image */
					ny;		/* number of columns in image */
	/*
	** Gets the number of rows in the input image  
    */
    nx =  getNoOfRows_Image(detx);
    /* 
    ** Gets the number of columns in the input image  
    */
    ny =  getNoOfCols_Image(detx);
  	
	if (ix < 2 || ix > nx - 2 || iy < 2 || iy >ny - 1)
		return (0);
	
  	image= getData_Image(detx, bands);
	return( image[ix][iy] - image[ix][iy-1]);
}

int
image_locy ( int iy,  int ix,  Image *dety, int bands)
{  
   short **image;
   unsigned int 	nx,		/* number of rows in image */
					ny;		/* number of columns in image */
	/*
	** Gets the number of rows in the input image  
    */
    nx =  getNoOfRows_Image(dety);

    /* 
    ** Gets the number of columns in the input image  
    */
    ny =  getNoOfCols_Image(dety);
  	
	if (ix < 2 || ix > nx - 1 || iy < 2 || iy > ny - 2)
    return (0);

	image= getData_Image(dety, bands);
	return( image[ix][iy] - image[ix-1][iy]);
}

int
image_loc45 ( int iy,  int ix, Image *det45, int bands)
{                               
   short			**image;
   unsigned int 	nx,		/* number of rows in image */
					ny;		/* number of columns in image */
	/*
	** Gets the number of rows in the input image  
    */
    nx =  getNoOfRows_Image(det45);

    /* 
    ** Gets the number of columns in the input image  
    */
    ny =  getNoOfCols_Image(det45);

	if (ix < 2 || ix > nx - 2 || iy < 2 || iy > ny - 2)
    return (0);

	image= getData_Image(det45, bands);
	return( image[ix][iy] - image[ix-1][iy+1]);
}

int
image_loc135 ( int iy,  int ix,Image *det135, int bands)
{                              
   short **image;
   unsigned int 	nx,		/* number of rows in image */
					ny;	/* number of columns in image */
	/*
	** Gets the number of rows in the input image  
    */
    nx =  getNoOfRows_Image(det135);

    /* 
    ** Gets the number of columns in the input image  
    */
    ny =  getNoOfCols_Image(det135);

	if (ix < 2 || ix > nx - 2 || iy < 2 || iy > ny - 2)
    return (0);

	image= getData_Image(det135, bands);
	return( image[ix][iy] - image[ix-1][iy-1]);
}

int image_threshold (Image * detx, int  bands)
{
  int r,c;
  int tmp;
  float mad = (float) 0;        /* calculate mean absolute deviation */

  short **image;
  unsigned int 	nx,		/* number of rows in image */
					ny;		/* number of columns in image */
	/*
	** Gets the number of rows in the input image  
    */
    nx =  getNoOfRows_Image(detx);

    /* 
    ** Gets the number of columns in the input image  
    */
    ny =  getNoOfCols_Image(detx);
   	image= getData_Image(detx, bands);
 
	for (c = 0; c < ny; c++) {
		for (r = 0; r < nx; r++) {

		tmp =image[r][c] ;
        mad += abs (tmp);
		}
	}
	printf("\n\n returning from image_threshold");
  return ((int) ((float) (3 * mad / nx / ny) / 0.8));
}


Image *image_hysteresis (Image *detx,Image *dety,Image *det45,Image *det135,
				  Image *ImageEdge, int lo_thld)
{
  	unsigned int r,c,bands;

	Image		*ImageHyst;
	byte		**imageE, **imageH;
	unsigned int 	no_of_rows,		/* number of rows in image */
					no_of_cols,		/* number of columns in image */
					no_of_bands;	/* number of image bands */

	/*
    ** Gets the number of image bands (planes)
    */

    no_of_bands = getNoOfBands_Image(ImageEdge);

    /* 
    ** Gets the number of rows in the input image  
    */
    no_of_rows =  getNoOfRows_Image(ImageEdge);

    /* 
    ** Gets the number of columns in the input image  
    */
    no_of_cols =  getNoOfCols_Image(ImageEdge);	
	
	ImageHyst  = duplicate_Image(ImageEdge);
 	for(bands=0; bands< no_of_bands; bands++){
		imageH = getData_Image(ImageHyst, bands);
		for (c= 0; c< no_of_cols; c++) {
			for (r = 0; r < no_of_rows; r++) {
				imageH[r][c] =0;
			}
		}
	}
	
	for(bands=0; bands< no_of_bands; bands++){	
		imageE = getData_Image(ImageEdge, bands);
		imageH = getData_Image(ImageHyst, bands);	
			for (c = 0; c< no_of_cols; c++) {
				for (r = 0; r < no_of_rows; r++) {

		if (imageE[r][c] != 0) {
			imageH[r][c] = imageE[r][c];        
			//*mapP = lmap_hiP[ix];
			image_neighbor_fwd (detx,dety,det45,det135,ImageHyst,
							c, r, bands,lo_thld);
			image_neighbor_bwd (detx,dety,det45,det135,ImageHyst,
							c, r, bands,lo_thld);
			}
			}
		  }
	}
	printf("\n\nreturning from hysteresis threshold");
  return (ImageHyst);
}

void image_neighbor_fwd (Image *detx, Image *dety, Image *det45, Image *det135,
						 Image *ImageHyst,unsigned int iy, unsigned int ix, unsigned int bands, int lo_thld)
{

	 unsigned int 	nx,				/* number of rows in image */
					ny;				/* number of columns in image */
	 byte		**imageH;
	/*
	** Gets the number of rows in the input image  
    */
    nx =  getNoOfRows_Image(detx);

    /* 
    ** Gets the number of columns in the input image  
    */
    ny =  getNoOfCols_Image(detx);
	
	imageH= getData_Image(ImageHyst, bands);

	//printf("\n\nIn FWD");
	
	switch (imageH[ix][iy]) {
  case 5:
    return;
  
  case EDGE_Y:                 /*0 */
    if (!Fcontour (detx,dety,det45,det135, ImageHyst,iy, ix + 1, bands, lo_thld)
		&& Fcontour (detx,dety,det45,det135, ImageHyst,iy, ix + 2, bands, lo_thld))
      goto L_EDGE_Y;
    else if (!(Fcontour (detx,dety,det45,det135, ImageHyst,iy - 1, ix + 1, bands, lo_thld)
			|| Fcontour (detx,dety,det45,det135, ImageHyst,iy + 1, ix + 1, bands, lo_thld)) 
			&&
             (Fcontour (detx,dety,det45,det135, ImageHyst,iy - 1, ix + 2, bands, lo_thld)
			 || Fcontour (detx,dety,det45,det135, ImageHyst,iy + 1, ix + 2, bands, lo_thld))) {
    L_EDGE_Y:if ((ix + 1 < nx) && (imageH[ix][iy+1] == 0))
        imageH[ix][iy+1] = 5;
    }
    break;
  
  case EDGE_135:               /*45 */
    if (!Fcontour (detx,dety,det45,det135, ImageHyst, iy - 1, ix + 1, bands, lo_thld) 
		&& Fcontour (detx,dety,det45,det135,ImageHyst, iy - 2, ix + 2, bands, lo_thld))
      goto L_EDGE_135;
    else if (!(Fcontour (detx,dety,det45,det135, ImageHyst, iy, ix + 1, bands, lo_thld) 
			|| Fcontour (detx,dety,det45,det135, ImageHyst,iy - 1, ix, bands, lo_thld)) &&
             (Fcontour (detx,dety,det45,det135, ImageHyst,iy - 2, ix + 1,bands, lo_thld) 
			 || Fcontour (detx,dety,det45,det135, ImageHyst,iy - 1, ix + 2,bands, lo_thld))) {
    L_EDGE_135:if ((iy - 1 >= 0) && (ix + 1 < nx) && (imageH[ix-1][iy+1] == 0))
        imageH[ix-1][iy+1] = 5;
    }
    break;  

  case EDGE_X:                 /*90 */
    if (!Fcontour (detx,dety,det45,det135, ImageHyst,iy - 1, ix, bands, lo_thld) 
		&& Fcontour (detx,dety,det45,det135, ImageHyst,iy - 2, ix, bands, lo_thld))
      goto L_EDGE_X;
    else if (!(Fcontour (detx,dety,det45,det135, ImageHyst,iy - 1, ix - 1, bands, lo_thld)
			|| Fcontour (detx,dety,det45,det135, ImageHyst,iy - 1, ix + 1, bands, lo_thld)) 
			&&
             (Fcontour (detx,dety,det45,det135, ImageHyst,iy - 2, ix - 1, bands, lo_thld) 
			 || Fcontour (detx,dety,det45,det135, ImageHyst,iy - 2, ix + 1, bands, lo_thld))) {
    L_EDGE_X:if ((iy - 1 >= 0) && (imageH[ix-1][iy]== 0))
        imageH[ix-1][iy] = 5;
    }
    break;
  
  case EDGE_45:                /*135 */
    if (!Fcontour (detx,dety,det45,det135, ImageHyst,iy + 1, ix + 1, bands, lo_thld)
		&& Fcontour (detx,dety,det45,det135, ImageHyst,iy + 2, ix + 2, bands, lo_thld))
      goto L_EDGE_45;
    else if (!(Fcontour (detx,dety,det45,det135, ImageHyst,iy, ix + 1, bands, lo_thld) 
			|| Fcontour (detx,dety,det45,det135, ImageHyst,iy + 1, ix, bands, lo_thld)) 
			&&
             (Fcontour (detx,dety,det45,det135, ImageHyst,iy + 1, ix + 2, bands, lo_thld)
			 || Fcontour (detx,dety,det45,det135, ImageHyst,iy + 2, ix + 1, bands, lo_thld))) {
    L_EDGE_45:if ((iy + 1 < ny) && (ix + 1 < nx) && (imageH[ix+1][iy+1] ==0))
        (imageH[ix+1][iy+1]) = 5;
    }
    break;
  
  default:
    fprintf (stderr, "error in case statements fwd\n");
    fprintf (stderr, "x=%d y=%d\n", ix, iy);
    exit (1);
    break;
  }
}

void
image_neighbor_bwd (Image *detx, Image *dety, Image *det45, Image *det135, Image *ImageHyst,
					unsigned int iy, unsigned int ix, unsigned int bands,int lo_thld)
{
	unsigned int 	nx,		/* number of rows in image */
				ny;	/* number of columns in image */
	byte  **imageH;
	/*
	** Gets the number of rows in the input image  
    */
    nx =  getNoOfRows_Image(detx);

    /* 
    ** Gets the number of columns in the input image  
    */
    ny =  getNoOfCols_Image(detx);
	imageH= getData_Image(ImageHyst, bands);
	
	
	switch (imageH[ix][iy]) {
  case 5:
    return;

  case EDGE_Y:                 /*0 */
    if (!Bcontour (detx,dety,det45,det135, ImageHyst,iy, ix - 1, bands, lo_thld) 
		&& Bcontour (detx,dety,det45,det135, ImageHyst,iy, ix - 2, bands, lo_thld))
      goto L_EDGE_Y;
    else if (!(Bcontour (detx,dety,det45,det135, ImageHyst,iy - 1, ix - 1, bands, lo_thld)
			|| Bcontour (detx,dety,det45,det135, ImageHyst,iy + 1, ix - 1, bands, lo_thld)) 
			&&
             (Bcontour (detx,dety,det45,det135, ImageHyst,iy - 1, ix - 2, bands, lo_thld)
			 || Bcontour (detx,dety,det45,det135, ImageHyst,iy + 1, ix - 2, bands, lo_thld))) {
    L_EDGE_Y:if ((ix - 1 >= 0) && (imageH[ix][iy-1]== 0))
        (imageH[ix][iy-1]) = 5;
    }
    break;
  case EDGE_135:               /*45 */
    if (!Bcontour (detx,dety,det45,det135, ImageHyst,iy + 1, ix - 1, bands, lo_thld) 
		&& Bcontour (detx,dety,det45,det135, ImageHyst,iy + 2, ix - 2, bands, lo_thld))
      goto L_EDGE_135;
    else if (!(Bcontour (detx,dety,det45,det135,ImageHyst,iy, ix - 1, bands, lo_thld) 
			|| Bcontour (detx,dety,det45,det135, ImageHyst,iy + 1, ix, bands, lo_thld)) 
			&&
             (Bcontour (detx,dety,det45,det135, ImageHyst,iy + 1, ix - 2, bands, lo_thld) 
			 || Bcontour (detx,dety,det45,det135, ImageHyst,iy + 2, ix - 1, bands, lo_thld))) {
    L_EDGE_135:if ((iy + 1 < ny) && (ix - 1 >= 0) && (imageH[ix+1][iy-1]==0))
        (imageH[ix+1][iy-1]) = 5;
    }
    break;
  case EDGE_X:                 /*90 */
    if (!Bcontour (detx,dety,det45,det135, ImageHyst,iy + 1, ix, bands, lo_thld) 
		&& Bcontour (detx,dety,det45,det135, ImageHyst,iy + 2, ix, bands, lo_thld))
      goto L_EDGE_X;
    else if (!(Bcontour (detx,dety,det45,det135, ImageHyst,iy + 1, ix - 1, bands, lo_thld) 
			|| Bcontour (detx,dety,det45,det135, ImageHyst,iy + 1, ix + 1, bands, lo_thld)) 
			&&
             (Bcontour (detx,dety,det45,det135,ImageHyst,iy + 2, ix - 1, bands, lo_thld) 
			 || Bcontour (detx,dety,det45,det135, ImageHyst,iy + 2, ix + 1, bands, lo_thld))) {
    L_EDGE_X:if ((iy + 1 < ny) && (imageH[ix+1][iy] == 0))
        (imageH[ix+1][iy]) = 5;
    }
    break;
  case EDGE_45:                /*135 */
    if (!Bcontour (detx,dety,det45,det135, ImageHyst,iy - 1, ix - 1, bands, lo_thld) 
		&& Bcontour (detx,dety,det45,det135, ImageHyst,iy - 2, ix - 2, bands, lo_thld))
      goto L_EDGE_45;
    else if (!(Bcontour (detx,dety,det45,det135, ImageHyst,iy, ix - 1, bands, lo_thld) 
			|| Bcontour (detx,dety,det45,det135, ImageHyst,iy - 1, ix, bands, lo_thld))
			&&
             (Bcontour (detx,dety,det45,det135, ImageHyst,iy - 1, ix - 2, bands, lo_thld) 
			 || Bcontour (detx,dety,det45,det135, ImageHyst,iy - 2, ix - 1, bands, lo_thld))) {
    L_EDGE_45:if ((iy - 1 >= 0) && (ix - 1 >= 0) && (imageH[ix-1][iy-1] == 0))
        (imageH[ix-1][iy-1]) = 5;
    }
    break;
  default:
    fprintf (stderr, "error in case statements bwd \n");
    fprintf (stderr, "x=%d y=%d\n", ix, iy);
    exit (1);
    break;
  }
}

int
Fcontour (Image *detx,Image *dety,Image *det45,Image *det135,Image *ImageHyst,
		  int iy, int ix,unsigned int bands,int lo_thld)
{
    unsigned int nx, ny;
	byte **imageH;
	byte edge_pt;
	/*
	** Gets the number of rows in the input image  
    */
    nx =  getNoOfRows_Image(detx);

    /* 
    ** Gets the number of columns in the input image  
    */
    ny =  getNoOfCols_Image(detx);
	if(ix<0||ix>=nx||iy<0||iy>=ny) return(0);

    imageH= getData_Image(ImageHyst, bands);
   	if (imageH[ix][iy] != 0)
		return (1);
	else if ((edge_pt = image_edge_map_lo (detx,dety,det45,det135,ix, iy,bands,lo_thld )) != 0)
	{
    imageH[ix][iy] = edge_pt;
    image_neighbor_fwd (detx,dety,det45,det135, ImageHyst,iy, ix,bands,lo_thld);
    return (1);
  }
  else
    return (0);
}

int Bcontour (Image *detx,Image *dety,Image *det45,Image *det135 ,Image *ImageHyst,
		  unsigned int iy, unsigned int ix,unsigned int bands,int lo_thld)
{
 unsigned int nx, ny;
	byte **imageH;
	byte  edge_pt;
	/*
	** Gets the number of rows in the input image  
    */
    nx =  getNoOfRows_Image(detx);

    /* 
    ** Gets the number of columns in the input image  
    */
    ny =  getNoOfCols_Image(detx);

	if(ix<0||ix>=nx||iy<0||iy>=ny) return(0);    
	imageH= getData_Image(ImageHyst, bands); 

	if (imageH[ix][iy] != 0)
		return (1);
	else if ((edge_pt = image_edge_map_lo (detx,dety,det45,det135,ix, iy,bands,lo_thld )) != 0) {
    imageH[ix][iy] = edge_pt;
	image_neighbor_bwd (detx,dety,det45,det135,ImageHyst,iy,ix,bands,lo_thld);
    return (1);
	}
  else
    return (0);
  
}


byte image_edge_map_lo (Image *detx,Image *dety,Image *det45,Image *det135,
				   unsigned int ix, unsigned int iy, unsigned int bands,int lo_thld)
{
	short	  **imagex, **imagey, 
			  **image45, **image135; 
  	int big, sx, sy, s45, s135,orient_flag;
	
	imagex= getData_Image(detx, bands);
	imagey= getData_Image(dety, bands);
	image45= getData_Image(det45, bands);
	image135= getData_Image(det135, bands);
	
	sx = abs (imagex[ix][iy]);					
	sy = abs (imagey[ix][iy]);		
	s45 = (int) ((float) (abs (image45[ix][iy])) / diag_scale);		
	s135 = (int) ((float) (abs (image135[ix][iy])) / diag_scale);
	
	big = sx;
	orient_flag = EDGE_X;
  
	if (sy > big) {
    big = sy;
   orient_flag = EDGE_Y;
  }
  if (s45 > big) {
    big = s45;
    orient_flag = EDGE_45;
  }
  if (s135 > big) {
    big = s135;
    orient_flag = EDGE_135;
  }

  if (big > lo_thld) {
    switch (orient_flag) {
    case EDGE_X:
      return (image_zc_x (ix, iy, detx, bands));
    case EDGE_Y:
      return (image_zc_y (ix, iy, dety, bands));
    case EDGE_45:
      return (image_zc_45 (ix, iy, det45, bands));
    case EDGE_135:
      return (image_zc_135 (ix, iy, det135, bands));
    default:
      fprintf (stderr, "error in case statements\n");
      exit (1);
      break;
    }
  }
  else
    return (0);
}



Image *image_thin ( Image *InputImage)
{
  
  register int ix; 
  register int iy, nlinks, npieces;
 
  register int b01, b12, b21, b10;
  register int p1, p2, p3, p4;
  register int b00, b02, b20, b22;


  	unsigned int 	bands,no_of_rows,		/* number of rows in image */
					no_of_cols,		/* number of columns in image */
					no_of_bands;	/* number of image bands */

	byte **image;
	/*
    ** Gets the number of image bands (planes)
    */

    no_of_bands = getNoOfBands_Image(InputImage);

    /* 
    ** Gets the number of rows in the input image  
    */
    no_of_rows =  getNoOfRows_Image(InputImage);

    /* 
    ** Gets the number of columns in the input image  
    */
    no_of_cols =  getNoOfCols_Image(InputImage);
  
   // emPiy = 0;
  for(bands=0; bands< no_of_bands; bands++){	
			image= getData_Image(InputImage, bands);
	for (iy = 1; iy < no_of_cols-1; iy++) {
			//emPiy += no_of_rows;
		for (ix = 1; ix < no_of_rows-1; ix++) {
      //emP = emPiy + ix;
    //  b01 = *(emP - nx) > 0;
	  b01 = image[ix-1][iy] > 0;
    //  b12 = *(emP + 1) > 0;
	  b12 = image[ix][iy+1] > 0;
   //   b21 = *(emP + nx) > 0;
	  b21 = image[ix+1][iy] > 0;
   //   b10 = *(emP - 1) > 0;
	  b10 = image[ix][iy-1]> 0;
      
	  if ((b01 + b12 + b21 + b10) > 1) {
        //b00 = *(emP - nxP1) > 0;
		 b00 = image[ix-1][iy-1] > 0;
        //b02 = *(emP - nxM1) > 0;
		 b02 = image[ix-1][iy+1] > 0;
        //b20 = *(emP + nxM1) > 0;
		 b20 = image[ix+1][iy-1] > 0;
        //b22 = *(emP + nxP1) > 0;
			b22 = image[ix+1][iy+1] > 0;

        p1 = b00 | b01;
        p2 = b02 | b12;
        p3 = b22 | b21;
        p4 = b20 | b10;

        nlinks = b01 & p2;
        nlinks += b12 & p3;
        nlinks += b21 & p4;
        nlinks += b10 & p1;

        npieces = p1 + p2 + p3 + p4;

        if ((npieces - nlinks) < 2)
          image[ix][iy] = 0;             /*edge_map[iy*nx+ix]=0; */
      }
    }
  }
 }
  printf("\n\nReturning from thinning");
  return (InputImage);
}




