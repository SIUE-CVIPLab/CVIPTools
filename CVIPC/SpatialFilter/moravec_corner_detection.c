
/***************************************************************************
* =========================================================================
*
*   Computer Vision and Image Processing Lab - Dr. Scott Umbaugh SIUE
* 
* =========================================================================
*
*             File Name: moravec_corner_detection.c 
*           Description: function to detect edges in the image
*   Initial Coding Date: Feb 10th 2009
*           Portability: Standard (ANSI) C
*             Credit(s): Mounika Mamidi
*                        Southern Illinois University at Edwardsville
*
** Copyright (c) 1995, 2004, SIUE - Scott Umbaugh, Mounika Mamidi
****************************************************************************/


#include "CVIPconvert.h"
#include "CVIPimage.h"
#include <CVIPspfltr.h>
#include "CVIPtyp.h"
#include "float.h"
#include "CVIParithlogic.h"
#define		WHITE_LAB	255
#define		BLACK_LAB	0


Image *threshold_detect(Image *cvipImage, float threshval);

Image *moravec_corner_filter(Image *inputImage, float threshval)

{
		float   **inputdata;
			
		float  **outputdata; 

		Image  *outputImage;

		unsigned int 		r,	c, 	bands, i=0 ,j =0;
		
		unsigned int 	no_of_rows,	no_of_cols,	no_of_bands; 
			
		if(threshval>255)

			threshval=255;

		else if(threshval<0)
			
			threshval=0;

		cast_Image(inputImage, CVIP_FLOAT);

		no_of_bands = getNoOfBands_Image(inputImage);

		no_of_rows =  getNoOfRows_Image(inputImage);
  
	    no_of_cols =  getNoOfCols_Image(inputImage);

	    outputImage=new_Image(inputImage->image_format,inputImage->color_space,no_of_bands,no_of_rows,no_of_cols,CVIP_FLOAT,REAL);

				
		/*Calculating the average of the surrounding pixels*/
		
		for(bands=0; bands < no_of_bands; bands++) 
		
		{
			inputdata = getData_Image(inputImage, bands);

			outputdata=getData_Image(outputImage,bands);

			for(i=0;i<no_of_rows;i++)
			{
				for(j=0;j<no_of_cols;j++)
				{
					outputdata[i][j]=0.0f;

					if(i==0||j==0||i==no_of_rows-1||j==no_of_cols-1)
						
						outputdata[i][j]=0.0f;
					
					else
					
					{
						for(r=i-1; r <= i+1; r++) 
						
						{
							for(c=j-1; c <= j+1; c++) 
								
								outputdata[i][j]=outputdata[i][j]+abs(inputdata[i][j]-inputdata[r][c]);
						}
						
						outputdata[i][j]=(outputdata[i][j])/8;
					}
				}
			}
		}
		
		outputImage=threshold_detect(outputImage,threshval);
		
		return(outputImage);
	}
	
	/*Threshold Function*/
	
	Image *threshold_detect(Image *cvipImage, float threshold)
	
	{
		float		**inputdata; 	

		unsigned int 		r,	c, bands;	
		
		unsigned int 	no_of_rows,	no_of_cols, no_of_bands;

		no_of_rows =  getNoOfRows_Image(cvipImage);

		no_of_cols =  getNoOfCols_Image(cvipImage);

		no_of_bands = getNoOfBands_Image(cvipImage);

		for(bands=0;bands<no_of_bands;bands++)
		{
		inputdata = getData_Image(cvipImage, bands);

			for(r=0; r < no_of_rows; r++) 
		
			{
				for(c=0; c < no_of_cols; c++) 
			
				{
					if(inputdata[r][c] > threshold)
            	    
						inputdata[r][c] = WHITE_LAB;
	  	
					else 
	     	    
						inputdata[r][c] = BLACK_LAB;
				}
			}
		}
		return cvipImage;
	}