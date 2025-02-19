/***************************************************************************
* =========================================================================
*
*   Computer Vision and Image Processing Lab - Dr. Scott Umbaugh SIUE
* 
* =========================================================================
*
*             File Name: Pratts.c 
*           Description: it contains the function to threshold BYTE images 
*   Initial Coding Date: April 23, 1996
*           Portability: Standard (ANSI) C
*             Credit(s): Sushuma Gouravaram
*                        Southern Illinois University at Edwardsville
*
** Copyright (c) 1995, 2004, SIUE - Scott Umbaugh, Kun Luo, Yansheng Wei
****************************************************************************/

/*
** include header files
*/

#include "CVIPtoolkit.h"
#include "CVIPconvert.h"
#include "CVIPdef.h"
#include "CVIPimage.h"
//#include "CVIPlab.h"

/*
	a: a scaling constant that can be adjusted to adjust the penalty for offset edges; P71 in CVIPtools book;
	inputImage1: the ideal edge image;
	inputImage2: the output edge image from edge detection operation;

	a = 0.11; I don't want to give the big penalty for smeared edges;
*/
float pratt_merit(Image *inputImage1, Image *inputImage2,  float a){
    
	byte 		**image1; 	/* 2-d matrix data pointer */
	byte 		**image2; 	/* 2-d matrix data pointer */

    unsigned int 		r,r1,		/* row index */
						c,c1,		/* column index */
						bands;		/* band index */
			
    unsigned int 	no_of_rows,	/* number of rows in image */
					no_of_cols,	/* number of columns in image */
					no_of_bands;	/* number of image bands */

	unsigned int  IF=0, IA=0;

	float d, min, sum;

    /*
    ** Gets the number of image bands (planes)
    */
    no_of_bands = getNoOfBands_Image(inputImage1);

    /* 
    ** Gets the number of rows in the input image  
    */
    no_of_rows =  getNoOfRows_Image(inputImage1);

    /* 
    ** Gets the number of columns in the input image  
    */
    no_of_cols =  getNoOfCols_Image(inputImage1);

    /* 
    ** Compares the pixel value at the location (r,c)
    ** with the threshold value. If it is greater than 
    ** the threshold value it writes 255 at the location
    ** else it writes 0. Note thta this assumes the input
    ** image is of data type BYTE.
    */
    for(bands=0; bands < no_of_bands; bands++) {
	/*
	** reference each band of image data in 2-d matrix form;
	** which is used for reading and writing the pixel values
	*/
  	image1 = getData_Image(inputImage1, bands);
  	image2 = getData_Image(inputImage2, bands);

  	for(r=0; r < no_of_rows; r++) {
     	    for(c=0; c < no_of_cols; c++) {
	if(image1[r][c] > 0)
			IA++;
	if(image2[r][c] > 0)
			IF++;
			
           }
     	}
    }
	
	printf(" IA= %d", IA);


	if(IA>IF)
	IF =IA;
	printf("IF = %d",IF);

	sum =0.0;

	for(bands=0; bands < no_of_bands; bands++) {
	/*
	** reference each band of image data in 2-d matrix form;
	** which is used for reading and writing the pixel values
	*/
  	image1 = getData_Image(inputImage1, bands);
  	image2 = getData_Image(inputImage2, bands);

  	for(r=0; r < no_of_rows; r++) {
     	 for(c=0; c < no_of_cols; c++) {
			
		 if(image2[r][c]>0)
			{
			 min=1000;
			 for(r1=0; r1 < no_of_rows; r1++) {
     		  for(c1=0; c1 < no_of_cols; c1++) {
				if(image1[r1][c1]>0)
					{
					d=  (((r1-r)*(r1-r))+((c1-c)*(c1-c)));
					if (d<min)
					min = d;
					//printf("min  = %d", min);
					}
		 
			 }
			}
				
		    sum = sum + (1/(1+a*min));
			}

		}
	}
}

 printf("result = %f", sum/IF);
 printf("sum  = %f", sum);

  printf("IN = %d",IF);


 return sum/IF;

}//end of function

