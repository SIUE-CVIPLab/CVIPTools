/***************************************************************************
* =========================================================================
*
*			 CVIPtools - Dr. Scott Umbaugh SIUE
*
* =========================================================================
*
*             File Name: superPixel.c
*		  Expanded Name: Super Pixel Declaration File
*			 Parameters: Pointers pointing to the file names of training and
*						 test set, error code
*				 Return: Number of entries in training set
*           Description: Runs SuperPixel Code
*   Initial Coding Date: May 2022
*Last Modification Made:  2022
*           Portability: Standard (ANSI) C
*             Credit(s): koop 
*			Southern Illinois University at Edwardsville
*
*		  Copyright (c): 1995-2005 SIUE - Scott Umbaugh
* 
* 
*			****INCOMPLETE FILE****
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


Image * superPixel(Image *cvipImage) {
    

	float norm[3] = { 255.0,255.0,255.0 };
	float ref[3] = { 1.0,1.0,1.0 };


    //Temporary Image Placeholder 
    unsigned int bandCount = getNoOfBands_Image(cvipImage); 
    unsigned int cols = getNoOfCols_Image(cvipImage); 
    unsigned int row = getNoOfRows_Image(cvipImage); 
    Image* outputImage;
    outputImage = new_Image(cvipImage->image_format, cvipImage->color_space, bandCount, row, cols, CVIP_FLOAT, REAL);
////////////////////////////////////////////////////////////////////////
    //Convert image into CieLAB Space 
////////////////////////////////////////////////////////////////////////
    //Start by pulling out the pixel data into array for algorithm
    byte** rawDataValue; 
    double** tempholding; 

    //outputImage = remap_Image(cvipImage, CVIP_DOUBLE); 

	//Convert RGB to HSV and extract value band
	cvipImage = colorxform(cvipImage, HSV, norm, ref, 1); 
    
	float** brightness = getData_Image(cvipImage, 2);


	//cvipImage = auto_threshold_segment1(brightness, 2); 


    return cvipImage; 
}



float thresholdfunction1(Image* cvipImage, float oldthreshold, unsigned int band);

Image* threshold_image1(Image* cvipImage, float threshval, unsigned int band);

Image* auto_threshold_segment1(Image* inputImage, float limit){
	//limit = 2; 

	float** image;

	Image* outputImage, * finalImage[3], * combinedImage;

	unsigned int 		r, c, bands, iteration = 0;

	unsigned int 	no_of_rows, no_of_cols, no_of_bands;

	float initialthreshold = 0, autothreshold = 0, threshold = 0, mean1 = 0, mean2 = 0;

	float difference = 0;

	cast_Image(inputImage, CVIP_FLOAT);

	no_of_bands = 1;

	no_of_rows = getNoOfRows_Image(inputImage);

	no_of_cols = getNoOfCols_Image(inputImage);



	for (bands = 0; bands < no_of_bands; bands++)

	{
		image = getData_Image(inputImage, bands);

		initialthreshold = 0.0f;

		for (r = 0; r < no_of_rows; r++)

		{
			for (c = 0; c < no_of_cols; c++)

			{
				initialthreshold = initialthreshold + image[r][c];
			}
		}

		initialthreshold = initialthreshold / (r * c);

		printf("initial threshold value %f \n\n", initialthreshold);

		//thresholdimage =duplicate_Image(inputImage);

		threshold = thresholdfunction1(inputImage, initialthreshold, bands);

		iteration = 0;

		//checking the old and new threshold values

		while (!(abs(difference = initialthreshold - threshold) <= limit))
		{
			initialthreshold = threshold;

			iteration = iteration + 1;

			printf("after %d iteration the threshold value is %f \n\n", iteration, threshold);

			threshold = thresholdfunction1(inputImage, initialthreshold, bands);

		}

		outputImage = threshold_image1(inputImage, threshold, bands);

		printf("threshold value %f \n\n", threshold);

	}

	return outputImage;

}

float thresholdfunction1(Image* cvipImage, float oldthreshold, unsigned int band)
{

	float** image;

	unsigned int 		r, c;

	unsigned int 	no_of_rows, no_of_cols;

	float mean1 = 0, mean2 = 0, threshold1, count = 0, threshold = 0;

	threshold1 = oldthreshold;

	no_of_rows = getNoOfRows_Image(cvipImage);

	no_of_cols = getNoOfCols_Image(cvipImage);

	image = getData_Image(cvipImage, band);

	//calculating the total value at each pixel to find threshold

	for (r = 0; r < no_of_rows; r++)

	{

		for (c = 0; c < no_of_cols; c++)
		{
			if (image[r][c] >= (byte)oldthreshold)
			{
				mean1 = mean1 + image[r][c];

				count = count + 1;
			}

			else
				mean2 = mean2 + image[r][c];
		}
	}

	//finding the mean of the image

	if (mean1 == 0)

		mean2 = 2 * mean2;

	else
		mean1 = mean1 / count;

	if (mean2 == 0)

		mean1 = 2 * mean1;

	else
		mean2 = mean2 / (r * c - count);

	threshold = (mean1 + mean2) / 2;

	return(threshold);

}

//threshold function

Image* threshold_image1(Image* cvipImage, float threshval, unsigned int band)

{
	float** image;

	unsigned int 	r = 0, c = 0;

	unsigned int 	no_of_rows, no_of_cols, no_of_bands;

	no_of_rows = getNoOfRows_Image(cvipImage);

	no_of_cols = getNoOfCols_Image(cvipImage);

	no_of_bands = getNoOfBands_Image(cvipImage);

	image = getData_Image(cvipImage, band);

	for (r = 0; r < no_of_rows; r++)

	{
		for (c = 0; c < no_of_cols; c++)

		{
			if (image[r][c] >= threshval)

				image[r][c] = WHITE_LAB;

			else

				image[r][c] = BLACK_LAB;
		}
	}

	return cvipImage;
}