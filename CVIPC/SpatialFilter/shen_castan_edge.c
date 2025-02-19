/*include header files*/
#include "CVIPtoolkit.h"
#include "CVIPconvert.h"
#include "CVIPdef.h"
#include "CVIPimage.h"
//#include "CVIPlab.h"
#include "CVIPgeometry.h"
#include "CVIPtoolkit.h"
#include "CVIPdrawimg.h"
#include "CVIPhisto.h"
#include "CVIPmap.h"
#include "CVIPview.h"
#include "CVIPobject.h"
#include "threshold.h"
#include "CVIPfs.h"
#include <CVIPmatrix.h>
#include <CVIPspfltr.h>
#include <limits.h>

#define OUTLINE 10
/* Function prototypes */

void ISEF_filter (Image *in, Image *out, float b);
void ISEF_vertical (Image *in,Image *out, float b);
void ISEF_horizontal (Image *in,Image *out, float b);
Image *compute_bli (Image *in, Image *smothed_image);
Image *locate_zero_crossings (Image *orig,  Image *smoothed, Image *bli, int window_size);
int is_candidate_edge (Image *buff, Image *orig, int row, int col, int bands);
float compute_adaptive_gradient (Image *BLI_buffer, Image *orig_buffer, int window_size,int row,
								 int col, int bands);
Image *locate_zero_crossings (Image *orig,  Image *smoothed, Image *bli, int window_size);
void threshold_edges (Image *in, Image *out, float low_thresh, float high_thresh, int thinFactor);
int mark_connected (Image *in, Image *out,int i, int j, int level,
					float low_thresh, int bands,int thinFactor );
void estimate_thresh ( Image *in, float *low, float *hi, int nr, int nc,int bands);

Image *debed (Image *im, int width);
Image *embed (Image *im, int width);

/*shen funcion*/
/*
	b: smoothing factor for the ISEF function. it's >0 and <1;
	window_size: 3, 5, or 7;
	low_thresh:range from 0 to 10, better use fraction between 0-1;if it's a noisy image, better go for low_thresh value>1;
	high_thresh:range from 0 to 10, better use fraction between 0-1;if it's a noisy image, better go for high_thresh value>1;
	thinFactor: it decides the width of the edge;

	Note: high_thresh should be greater than or equal to low_thresh;
	if low_thresh = 1, it uses the value estimated from the image for hysterisys threshold ;
	if high_thresh = 1, it uses the value estimated from the image for hysterisys threshold ;

	b= 0.5, 0.7, 0.9;
	window_size: 3, 5, 7;
	low_thresh = 0.5, 1, 2, 3, 5;
	high_thresh = 0.5, 1, 2, 3, 5;
	thinFactor = 1 or 3;

	for worf.ppm -- 0.9,5,1,1,1
	for cam.pgm -- 0,7, 7, 0.5, 1
*/
Image *shen_castan_filter(Image *inImage, Image *zeroInter, float b, int window_size,float low_thresh,
				   float high_thresh,int thinFactor)
{
	int i;
	Image *ISEF_image,*x,*y, **inputImage, *old, 
		  *zero_image;
	Image *bli_buffer;
   
/* Convert the input image to floating point*/

	i = cast_Image(inImage, CVIP_FLOAT);
	inputImage	=	embed (inImage, OUTLINE);

/* Smooth input image using recursively implemented ISEF filter */
	ISEF_image = duplicate_Image(inputImage);
	ISEF_filter(inputImage, ISEF_image, b);
      
/* Compute bli image band-limited laplacian image from smoothed image */

	x=duplicate_Image(inputImage);
 	y=duplicate_Image(ISEF_image);

	bli_buffer = compute_bli(x,y); 
//    view_Image(bli_buffer,"bli");

	//ISEF_image = remap_Image(ISEF_image,CVIP_FLOAT, 0, 255);

/* Perform edge detection using bli and gradient thresholding */
   zero_image = duplicate_Image(inputImage);
   zero_image = locate_zero_crossings (zero_image, ISEF_image, bli_buffer, window_size);

   *zeroInter = *(duplicate_Image(zero_image));

   printf("here after zero crossings");
//   view_Image(zero_image,"zero crossings");
   
	delete_Image(ISEF_image);
   ISEF_image = NULL;

   delete_Image(bli_buffer);
   bli_buffer = NULL;


/*Perform hysterisis thresholding*/
  threshold_edges (zero_image, inputImage,low_thresh, high_thresh,thinFactor);

// view_Image(inputImage, " thre output");


/*	for (i=0; i<im->info->nr; i++)
	  for (j=0; j<im->info->nc; j++)
	    if (res->data[i][j] > 0) res->data[i][j] = 0;
	     else res->data[i][j] = 255;
	
	free(buffer[0]); free(buffer);*/

old = debed (inputImage, OUTLINE);
old = remap_Image(old,CVIP_BYTE, 0, 255);
//view_Image(old, "output");

return old;

}

/*	Recursive filter realization of the ISEF*/
void ISEF_filter (Image *in, Image *out, float b)
{
	Image *temp;
	temp = duplicate_Image(in);

/* first apply the filter in the vertical direcion (to the rows) */
  ISEF_vertical (in,temp, b);

 // view_Image(temp,"bli");


/* now apply the filter in the horizontal direction (to the columns) and */
/* apply this filter to the results of the previous one */
  ISEF_horizontal (temp, out,b);

  delete_Image(temp);
  temp = NULL;

// view_Image(out,"ISEF smoothed");
 
}

void ISEF_vertical (Image *in,Image *out, float b)
{
	int		no_of_rows, 
			no_of_cols, 
			no_of_bands,
			bands, r, c;
	
	float b1, b2;
   
	float **image;

	Matrix *A, *B;
    
	b1 = (1.0 - b)/(1.0 + b);
	b2 = b*b1;
   	
	/*
    ** Gets the number of image bands (planes)
    */

    no_of_bands = getNoOfBands_Image(in);

	/* 
    ** Gets the number of rows in the input image  
    */
	no_of_rows =  getNoOfRows_Image(in);

    /* 
    ** Gets the number of columns in the input image  
    */
	no_of_cols =  getNoOfCols_Image(in);
    
	/*create two matrices to store causal and anti casual components*/
	A=new_Matrix(no_of_rows, no_of_cols ,CVIP_FLOAT,REAL);
      if(A==NULL)
             printf("NULL");

	B=new_Matrix(no_of_rows, no_of_cols,CVIP_FLOAT,REAL);
      if(B==NULL)
             printf("NULL");

	  
	/* compute boundary conditions */
	for(bands =0; bands < no_of_bands; bands++){
		image= getData_Image(in, bands);
	 for (c=0; c<no_of_cols; c++)
		{
      
/* boundary exists for 1st and last column */
	   (A->rptr)[0][c] = b1 * image[0][c];	
	   (B->rptr)[no_of_rows-1][c] = b2 * image[no_of_rows-1][c];
		}
	}

/* compute causal component */
	for(bands =0; bands < no_of_bands; bands++){
		image= getData_Image(in, bands);
	 for (r=1; r<no_of_rows; r++)
	  for (c=0; c<no_of_cols; c++)
	    (A->rptr)[r][c] = b1 * image[r][c] + b * (A->rptr)[r-1][c];
	}
/* compute anti-causal component */
	for(bands =0; bands < no_of_bands; bands++){
		image= getData_Image(in, bands);
	 for (r=no_of_rows-2; r>=0; r--)
	  for (c=0; c<no_of_cols; c++)
	    (B->rptr)[r][c] = b2 * image[r][c] + b * (B->rptr)[r+1][c];
	}
/* boundary case for computing output of first filter */
	for(bands =0; bands < no_of_bands; bands++){
		image= getData_Image(out, bands);
	 for (c=0; c<no_of_cols-1; c++)
	  image[no_of_rows-1][c] =  (A->rptr)[no_of_rows-1][c]; 
	}
/* now compute the output of the first filter and store in y */
/* this is the sum of the causal and anti-causal components */
	for(bands =0; bands < no_of_bands; bands++){
	 		image= getData_Image(out, bands);
		for (r=0; r<no_of_rows-2; r++)
	  for (c=0; c<no_of_cols-1; c++)
	    image[r][c] = (A->rptr)[r][c] + (B->rptr)[r+1][c];
	} 

	/*free necessary pointers*/

      delete_Matrix(A);
      delete_Matrix(B);

}


void ISEF_horizontal (Image *in,Image *out, float b)

{
	int		no_of_rows, 
			no_of_cols, 
			no_of_bands,
			bands, r, c;
	
	float b1, b2;
   
	float **image;

	Matrix *A, *B;
    
	b1 = (1.0 - b)/(1.0 + b);
	b2 = b*b1;
   	
	/*
    ** Gets the number of image bands (planes)
    */

    no_of_bands = getNoOfBands_Image(in);

	/* 
    ** Gets the number of rows in the input image  
    */
	no_of_rows =  getNoOfRows_Image(in);

    /* 
    ** Gets the number of columns in the input image  
    */
	no_of_cols =  getNoOfCols_Image(in);
    
	/*create two matrices to store causal and anti casual components*/
	A=new_Matrix(no_of_rows, no_of_cols ,CVIP_FLOAT,REAL);
      if(A==NULL)
             printf("NULL");

	B=new_Matrix(no_of_rows, no_of_cols,CVIP_FLOAT,REAL);
      if(B==NULL)
             printf("NULL");   
/* compute boundary conditions */
for(bands =0; bands < no_of_bands; bands++){
		image= getData_Image(in, bands);	
  for (r=0; r<no_of_rows; r++)
	{
	   (A->rptr)[r][0] = b1 * image[r][0];
	   (B->rptr)[r][no_of_cols-1] = b2 * image[r][no_of_cols-1];
	}
}
/* compute causal component */
for(bands =0; bands < no_of_bands; bands++){
		image= getData_Image(in, bands);
	for (c=1; c<no_of_cols; c++)
	  for (r=0; r<no_of_rows; r++)
	    (A->rptr)[r][c] = b1 * image[r][c] + b * (A->rptr)[r][c-1];
}
/* compute anti-causal component */
for(bands =0; bands < no_of_bands; bands++){
		image= getData_Image(in, bands);
	for (c=no_of_cols-2; c>=0; c--)
	  for (r=0; r<no_of_rows;r++)
	    (B->rptr)[r][c] = b2 * image[r][c] + b * (B->rptr)[r][c+1];
}

/* boundary case for computing output of first filter */  
for(bands =0; bands < no_of_bands; bands++){
		image= getData_Image(out, bands);
	for (r=0; r<no_of_rows; r++)
	  image[r][no_of_cols-1] = (A->rptr)[r][no_of_cols-1];
}
/* now compute the output of the second filter and store in y */
/* this is the sum of the causal and anti-causal components */
 for(bands =0; bands < no_of_bands; bands++){
		image= getData_Image(out, bands);
	for (r=0; r<no_of_rows; r++)
	  for (c=0; c<no_of_cols-1; c++)
	    image[r][c] = (A->rptr)[r][c] + (B->rptr)[r][c+1];
 
 } 

	/*free necessary pointers*/
	  delete_Matrix(A);
      delete_Matrix(B);

}



/* compute the band-limited laplacian of the input image */
Image *compute_bli (Image *in, Image *smoothed_image)
{
	
	int		no_of_rows, 
			no_of_cols, 
			no_of_bands,
			bands, r, c;
	
	byte  **image;  
	float **image1, 
		  **image2;

	Image *bliImage;
	/*
    ** Gets the number of image bands (planes)
    */

    no_of_bands = getNoOfBands_Image(in);

	/* 
    ** Gets the number of rows in the input image  
    */
	no_of_rows =  getNoOfRows_Image(in);

    /* 
    ** Gets the number of columns in the input image  
    */
	no_of_cols =  getNoOfCols_Image(in);
    
	bliImage = new_Image(PGM, GRAY_SCALE, no_of_bands,
                     no_of_rows,no_of_cols, CVIP_BYTE, REAL);

  for (bands =0; bands < no_of_bands; bands++){
		image = getData_Image(bliImage, bands);
	for (r=0; r<no_of_rows; r++)
	  for (c=0; c<no_of_cols; c++)
	     
		  image[r][c] = 0;

  }
   
  in = remap_Image(in,CVIP_FLOAT, 0, 255);
  smoothed_image = remap_Image(smoothed_image,CVIP_FLOAT, 0, 255);

/* The bli is computed by taking the difference between the smoothed image */
/* and the original image.  In Shen and Castan's paper this is shown to */
/* approximate the band-limited laplacian of the image.  The bli is then */
/* made by setting all values in the bli to 1 where the laplacian is */
/* positive and 0 otherwise. 						*/

	for (bands =0; bands < no_of_bands; bands++){
		image= getData_Image(bliImage, bands);	  
		image1= getData_Image(in, bands);	  
		image2= getData_Image(smoothed_image, bands);	  

		for (r=0; r<no_of_rows; r++){
			for (c=0; c<no_of_cols; c++){
				
				if (r<OUTLINE || r >= no_of_rows-OUTLINE ||
					c<OUTLINE || c >= no_of_cols-OUTLINE) continue;
	  
            image[r][c] = ((image2[r][c] - image1[r][c]) > 0.0);
			}
		}
	  	  
	}
	
		
	//bliImage = remap_Image(bliImage,CVIP_BYTE, 0, 255);
//	view_Image(bliImage,"bli in func");

	return bliImage;


}



 Image *locate_zero_crossings (Image *orig,  Image *smoothed, Image *bli, int window_size)
{
	int row, col, nrows, ncols, bands, nbands;
    
	float **image;
	float grad;
		
	/*
    ** Gets the number of image bands (planes)
    */

    nbands = getNoOfBands_Image(orig);

	/* 
    ** Gets the number of rows in the input image  
    */
	nrows =  getNoOfRows_Image(orig);


    /* 
    ** Gets the number of columns in the input image  
    */
	ncols =  getNoOfCols_Image(orig);
    
 for (bands =0; bands < nbands; bands++)
	{

    image  = getData_Image(orig, bands);

	for (row=0; row<nrows; row++)
	{
	   for (col=0; col<ncols; col++)
	   {

       /* ignore pixels around the boundary of the image */
	   if (row<OUTLINE || row >= nrows-OUTLINE || col<OUTLINE || col >= ncols-OUTLINE)
		{
	     image[row][col] = 0.0;
		}

       /* next check if pixel is a zero-crossing of the laplacian  */
	   else if (is_candidate_edge (bli, smoothed, row, col, bands))
		{

       /* now do gradient thresholding  */
	//	printf("going to compute");
		grad = compute_adaptive_gradient (bli, smoothed,window_size,row,col,bands);
	    image[row][col] = grad;

		}
	   
	   else  image[row][col] = 0.0;		    
	  }
	}

	
}


return orig;

}

/* finds zero-crossings in laplacian (buff)  orig is the smoothed image */
int is_candidate_edge (Image *buff, Image *orig, int row, int col, int bands)
{
/* test for zero-crossings of laplacian then make sure that zero-crossing */
/* sign correspondence principle is satisfied.  i.e. a positive z-c must */
/* have a positive 1st derivative where positive z-c means the 2nd deriv */
/* goes from positive to negative as we pass through the step edge */
   	
	float **image;
	byte  **image1;

//	view_Image(buff,"bli func");
//	view_Image(orig,"smooth func");


	
	image  = getData_Image(orig, bands);
	image1 = getData_Image(buff, bands);
	

		if (image1[row][col] == 1 && image1[row+1][col] == 0) /* positive z-c */
	{ 
	   
	 if ((image[row+1][col] - image[row-1][col]) > 0.0) return 1;
	   else return 0;
	}
	else if (image1[row][col] == 1 && image1[row][col+1] == 0 ) /* positive z-c */
	{
	   if ((image[row][col+1] - image[row][col-1])> 0.0) return 1;
	   else return 0;
	}
	else if ( image1[row][col] == 1 && image1[row-1][col] == 0) /* negative z-c */
	{
		//printf("value = %f", (image[row+1][col] - image[row-1][col]) );		

	   if ((image[row+1][col] - image[row-1][col]) < 0.0) return 1;
	   else return 0;
	}
	else if (image1[row][col] == 1 && image1[row][col-1] == 0 ) /* negative z-c */
	{
	   if ((image[row][col+1] - image[row][col-1] )< 0.0) return 1;
	   else return 0;
	}
	else														/* not a z-c */
	  return 0;


}


float compute_adaptive_gradient (Image *BLI_buffer, Image *orig_buffer, int window_size,
								 int row, int col, int bands)
{
	int i, j;
	float sum_on, sum_off;
	float avg_on, avg_off;
	int num_on, num_off;
	
	float **image;
	byte  **image1;
   
	sum_on = sum_off = 0.0;
	num_on = num_off = 0;
   
	image  = getData_Image(orig_buffer, bands);
	image1 = getData_Image(BLI_buffer, bands);
	
	
	for (i= (int)(-window_size/2); i<= (int) (window_size/2); i++)
	{
	   for (j= (int) (-window_size/2); j<= (int) (window_size/2); j++)
	   {
	     if (image1[row+i][col+j])
	     {
	        sum_on += image[row+i][col+j];
	        num_on++;
	     }
	     else
	     {
	        sum_off += image[row+i][col+j];
	        num_off++;
	     }
	   }
	}
   
	if (sum_off) avg_off = sum_off / num_off;
	else avg_off = 0;
   
	if (sum_on) avg_on = sum_on / num_on;
	else avg_on = 0;
   
	return (avg_off - avg_on);
}



void threshold_edges (Image *in, Image *out, float l, float h, int thinFactor)
{
	int i, j, bands, nbands, nrows, ncols, nr, nc, k;
   
	float high_thresh, low_thresh;
	
	float **image, **image1;
	
	/*
    ** Gets the number of image bands (planes)
    */

    nbands = getNoOfBands_Image(in);

	/* 
    ** Gets the number of rows in the input image  
    */
	nrows =  getNoOfRows_Image(in);

    /* 
    ** Gets the number of columns in the input image  
    */
	ncols =  getNoOfCols_Image(in);
    
	nr = nrows;
	nc = ncols;
   
 for (bands =0; bands < nbands; bands++)
 {
	
	 low_thresh  =l;
	 high_thresh =h;
	image  = getData_Image(in, bands);
	image1 = getData_Image(out, bands);

	estimate_thresh (in, &low_thresh, &high_thresh, nr, nc, bands);
	
	printf("bands= %d ,low = %f, HIGH = %f\n", bands ,low_thresh, high_thresh);
	
	for (i=0; i<nrows; i++)
	  for (j=0; j<ncols; j++)
	   image1[i][j] = 0;
  
	  for (i=0; i<nrows; i++){
	   for (j=0; j<ncols; j++){
            
		if (i<OUTLINE || i >= nrows-OUTLINE ||
            j<OUTLINE || j >= ncols-OUTLINE) continue;

		/* only check a contour if it is above high_thresh */
		/* mark all connected points above low thresh */

	   if ((image[i][j]) > high_thresh) 
		{
		mark_connected (in,out,i,j,0,low_thresh,bands,thinFactor);
		
		}
	  
	  }
	 }
	
	  for (i=0; i<nrows; i++)	/* erase all points which were 255 */
	 for (j=0; j<ncols; j++)
	  if (image1[i][j] == 255) image1[i][j] = 0;

	
 }	


}

/*	return true if it marked something */ 
int mark_connected (Image *in, Image *out,int i, int j, int level, float low_thresh,int bands, int thinFactor)
{
	int notChainEnd, nr, nc, nrows, ncols;

 	float **image, **image1;

	//printf("here in mark  %d  also %d",bands, b);
	/* 
    ** Gets the number of rows in the input image  
    */
	nrows =  getNoOfRows_Image(in);

    /* 
    ** Gets the number of columns in the input image  
    */
	ncols =  getNoOfCols_Image(in);
    
	nr = nrows;
	nc = ncols;

	//	printf("here in mark %d ", b);
	image  = getData_Image(in, bands);
	image1 = getData_Image(out,bands);

   /* stop if you go off the edge of the image */
	if (i >= nr || i < 0 || j >= nc || j < 0) return 0;
   
   /* stop if the point has already been visited */
	if (image1[i][j] != 0) return 0;	
   
   /* stop when you hit an image boundary */
	if (image[i][j] == 0.0) return 0;
   
	if ((image[i][j]) > low_thresh)
	{
	   image1[i][j] = 1;
	}
	else
	{
	   image1[i][j] = 255;
	}
   
	notChainEnd =0;
	notChainEnd |= mark_connected(in,out,i	,j+1	, level+1,low_thresh, bands, thinFactor);	
	notChainEnd |= mark_connected(in,out,i  ,j-1, level+1,low_thresh, bands, thinFactor);
	notChainEnd |= mark_connected(in,out,i+1,j+1, level+1,low_thresh, bands, thinFactor);
	notChainEnd |= mark_connected(in,out,i+1,j  , level+1,low_thresh, bands, thinFactor);
	notChainEnd |= mark_connected(in,out,i+1,j-1, level+1,low_thresh, bands, thinFactor);
	notChainEnd |= mark_connected(in,out,i-1,j-1, level+1,low_thresh, bands, thinFactor);
	notChainEnd |= mark_connected(in,out,i-1,j  , level+1,low_thresh, bands, thinFactor);
	notChainEnd |= mark_connected(in,out,i-1,j+1, level+1,low_thresh, bands, thinFactor);

	if (notChainEnd && ( level > 0 ) )
	{
	/* do some contour thinning */
	  if ( thinFactor > 0 )
	  if ( (level%thinFactor) != 0  )
	  {
	    /* delete this point */  
	    image1[i][j] = 255;
	  }
	}
    
	return 1;
}


void estimate_thresh ( Image *in, float *low, float *hi, int nr, int nc,int bands)
{
	float vmax, vmin, scale, x,z;
	int i,j,k, hist[256], count;

	float **image;
	image  = getData_Image(in, bands);


/* Build a histogram of the Laplacian image. */
	vmin = vmax = fabs((float)(image[20][20]));
	for (i=0; i<nr; i++)
	  for (j=0; j<nc; j++)
	  {
            if (i<OUTLINE || i >= nr-OUTLINE ||
                  j<OUTLINE || j >= nc-OUTLINE) continue;
	    x = image[i][j];
	    if (vmin > x) vmin = x;
	    if (vmax < x) vmax = x;
	  }


	  printf("here in est vmin = %f, vmax = %f", vmin, vmax);

	for (k=0; k<256; k++) hist[k] = 0;

	scale = 256.0/(vmax-vmin + 1);

	for (i=0; i<nr; i++)
	  for (j=0; j<nc; j++)
	  {
            if (i<OUTLINE || i >= nr-OUTLINE ||
                  j<OUTLINE || j >= nc-OUTLINE) continue;
	    x = image[i][j];
	    k = (int)((x - vmin)*scale);
	    hist[k] += 1;
	  }

/* The high threshold should be > 80 or 90% of the pixels */
	k = 255;
	j = (int)(.99*nr*nc);
	count = hist[255];
	while (count < j)
	{
	  k--;
	  if (k<0) break;
	  count += hist[k];
	}
	
	z= ((double)k/scale   + vmin );

	printf ("estimted high = %2f, estimated low = %2f", z, z/2);

	*hi = (*hi)  * z;
	*low = (*low) * z/2;

}


Image *embed (Image *im, int width)
{
	int i,j,I,J,k, K;

	Image *newim;

	float **image, **image1;

	unsigned int 	no_of_rows,nrows,	/* number of rows in image */
					no_of_cols,ncols,	/* number of columns in image */
					no_of_bands;	/* number of image bands */

	


	COLOR_FORMAT        color_space; 
    FORMAT              data_format;
    CVIP_TYPE           data_type;  
    IMAGE_FORMAT        image_format; 
	
	width += 2;


	/*
    ** Gets the number of image bands (planes)
    */
    no_of_bands = getNoOfBands_Image(im);

    /* 
    ** Gets the number of rows in the input image  
    */
    no_of_rows =  getNoOfRows_Image(im);

    /* 
    ** Gets the number of columns in the input image  
    */
    no_of_cols =  getNoOfCols_Image(im);
 
    /*
    ** Gets the ColorSpace ofimage bands (planes)
    */ 
    color_space   = getColorSpace_Image(im);       
       
   /*
   ** Gets the DataFormat of image bands (planes)
   */
    data_format   = getDataFormat_Image(im);   
    
   /*
   ** Gets the DataType of image bands (planes)
   */
   data_type    = getDataType_Image(im);    
    
   /*
   ** Gets the FileFormat of image bands (planes)
   */   
   image_format  = getFileFormat_Image(im); 
   
   newim = new_Image(image_format, color_space, no_of_bands, no_of_rows+width+width,
					no_of_cols+width +width, data_type, data_format);  

	//new = newimage (im->info->nr+width+width, im->info->nc+width+width);

	/* 
    ** Gets the number of rows in the input image  
    */
    nrows =  getNoOfRows_Image(newim);

    /* 
    ** Gets the number of columns in the input image  
    */
    ncols =  getNoOfCols_Image(newim);

  for(k=0;k<no_of_bands; k++){
  	image  = getData_Image(im, k);
	image1  = getData_Image(newim,k);

	  
	  for (i=0; i<nrows; i++)
	  for (j=0; j<ncols; j++)
	  {
	    I = (i-width+no_of_rows)%no_of_rows;
	    J = (j-width+no_of_cols)%no_of_cols;
	    image1[i][j] = image[I][J];
	  }
  }
/*	free (im->info);
	free(im->data[0]); free(im->data);
	im->info = new->info;
	im->data = new->data;*/

	return newim;	

}

Image *debed (Image *im, int width)
{
	int i,j,k;
	Image *old;

	unsigned int 	nrows,no_of_rows,	/* number of rows in image */
					ncols,no_of_cols,	/* number of columns in image */
					no_of_bands;	/* number of image bands */

	
	COLOR_FORMAT        color_space; 
    FORMAT              data_format;
    CVIP_TYPE           data_type;  
    IMAGE_FORMAT        image_format; 
	
	float **image, **image1;

	/*
    ** Gets the number of image bands (planes)
    */
    no_of_bands = getNoOfBands_Image(im);

	/* 
    ** Gets the number of rows in the input image  
    */
    no_of_rows =  getNoOfRows_Image(im);

    /* 
    ** Gets the number of columns in the input image  
    */
    no_of_cols =  getNoOfCols_Image(im);
 
    
    /*
    ** Gets the ColorSpace ofimage bands (planes)
    */ 
    color_space   = getColorSpace_Image(im);       
       
   /*
   ** Gets the DataFormat of image bands (planes)
   */
    data_format   = getDataFormat_Image(im);   
    
   /*
   ** Gets the DataType of image bands (planes)
   */
   data_type    = getDataType_Image(im);    
    
   /*
   ** Gets the FileFormat of image bands (planes)
   */   
   image_format  = getFileFormat_Image(im); 


	width +=2;
	old = new_Image(image_format, color_space, no_of_bands, no_of_rows-width-width,
					no_of_cols-width -width, data_type, data_format);  

	/* 
    ** Gets the number of rows in the input image  
    */
    nrows =  getNoOfRows_Image(old);

    /* 
    ** Gets the number of columns in the input image  
    */
    ncols =  getNoOfCols_Image(old);
	
	//	old = newimage (im->info->nr-width-width, im->info->nc-width-width);

	for(k=0; k<no_of_bands; k++){
	image  = getData_Image(im, k);
	image1 = getData_Image(old, k);

	for (i=0; i<nrows-1; i++)
	{
	  for (j=1; j<ncols-1; j++)
	  {
	    image1[i][j] = image[i+width][j+width];
	    image1[nrows-1][j] = 0;

	  }
	  image1[i][0] = 0;
      image1[i][ncols -1] = 0;

	}

	
	/*free (im->info);
	free(im->data[0]); free(im->data);
	im->info = old->info;
	im->data = old->data;*/
	
	}

	return old;

}
