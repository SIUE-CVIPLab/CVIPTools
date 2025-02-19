/***************************************************************************
* =========================================================================
*
*   Computer Vision and Image Processing Lab - Dr. Scott Umbaugh SIUE
* 
* =========================================================================
*
*             File Name: auto_threshold_segment.c 
*           Description: it contains the function to threshold BYTE images 
*   Initial Coding Date: Feb 20, 2009
*           Portability: Standard (ANSI) C
*             Credit(s): Mounika Mamidi
*                        Southern Illinois University at Edwardsville
*
** Copyright (c) 1995, 1996, SIUE - Scott Umbaugh, Mounika Mamidi
****************************************************************************/


/*
** include header files
*/

#include "CVIPtoolkit.h"
#include "CVIPconvert.h"
#include "CVIPsegment.h"
#include "CVIPdef.h"
#include "CVIPimage.h"
#include "CVIPtyp.h"
#define		WHITE_LAB	255
#define		BLACK_LAB	0
#define Value 255



	float thresholdfunction(Image *cvipImage, float oldthreshold , unsigned int band);

	Image *threshold_image(Image *cvipImage, float threshval, unsigned int band);

	Image *auto_threshold_segment(Image *inputImage, float limit)


	{
		float	**image; 

		Image  *outputImage ,*finalImage[3] ,*combinedImage;
		
		unsigned int 		r,	c, 	bands , iteration=0 ;
		
		unsigned int 	no_of_rows,	no_of_cols,	no_of_bands;

		float initialthreshold=0,autothreshold=0,threshold=0,mean1=0,mean2=0;

		float difference=0;

		cast_Image(inputImage, CVIP_FLOAT);
    
		no_of_bands = getNoOfBands_Image(inputImage);

		no_of_rows =  getNoOfRows_Image(inputImage);
  
	    no_of_cols =  getNoOfCols_Image(inputImage);



		for(bands=0; bands < no_of_bands; bands++) 
		
		{
			image = getData_Image(inputImage, bands);

			initialthreshold=0.0f;

			for(r=0; r < no_of_rows; r++) 
			
			{
				for(c=0; c < no_of_cols; c++) 
				
				{
					initialthreshold=initialthreshold+image[r][c];
				}
			}
		
			initialthreshold=initialthreshold/(r*c);

			printf("initial threshold value %f \n\n",initialthreshold);

			//thresholdimage =duplicate_Image(inputImage);

			threshold=thresholdfunction(inputImage,initialthreshold, bands);

			iteration=0;

			//checking the old and new threshold values

			while(!(abs(difference=initialthreshold-threshold)<=limit))
			{
				initialthreshold=threshold;

				iteration=iteration+1;

				printf("after %d iteration the threshold value is %f \n\n", iteration,threshold);

				threshold=thresholdfunction(inputImage,initialthreshold , bands);

			}

			outputImage = threshold_image(inputImage,threshold,bands);

			printf("threshold value %f \n\n", threshold);
		
		}
		
		return outputImage;
	
	}
 
	float thresholdfunction(Image *cvipImage, float oldthreshold, unsigned int band)
	{

		float	**image; 

		unsigned int 		r,	c ;	

		unsigned int 	no_of_rows,	no_of_cols;

		float mean1=0,mean2=0,threshold1,count=0,threshold=0;

		threshold1=oldthreshold;

		no_of_rows =  getNoOfRows_Image(cvipImage);

		no_of_cols =  getNoOfCols_Image(cvipImage);

		image = getData_Image(cvipImage, band);

		//calculating the total value at each pixel to find threshold

		for(r=0; r < no_of_rows; r++) 
		
		{

			for(c=0; c < no_of_cols; c++)
			{
				if(image[r][c] >= (byte) oldthreshold)
				{
					mean1=mean1+image[r][c];

					count=count+1;
				}

				else 
					mean2=mean2+image[r][c];
			}
		}

		//finding the mean of the image

		if(mean1==0)
		
 			mean2=2*mean2;

		else
			mean1=mean1/count;

		if(mean2==0)

			mean1=2*mean1;

		else
			mean2=mean2/(r*c-count);

		threshold=(mean1+mean2)/2;

		return(threshold);

	}

	//threshold function

	Image *threshold_image(Image *cvipImage, float threshval, unsigned int band)
	
	{
		float  **image; 
		
		unsigned int 	r=0,	c=0;	
		
		unsigned int 	no_of_rows,	no_of_cols,no_of_bands;

		no_of_rows =  getNoOfRows_Image(cvipImage);

		no_of_cols =  getNoOfCols_Image(cvipImage);

		no_of_bands = getNoOfBands_Image(cvipImage);

		image = getData_Image(cvipImage, band);

			for(r=0; r < no_of_rows; r++) 
		
			{
				for(c=0; c < no_of_cols; c++) 
			
				{
					if(image[r][c] >=  threshval)
            	    
						image[r][c] = WHITE_LAB;
	  	
					else 
	     	    
						image[r][c] = BLACK_LAB;
				}
			}
			
			return cvipImage;
	}