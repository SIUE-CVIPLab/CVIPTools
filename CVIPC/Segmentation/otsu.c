/***************************************************************************
* =========================================================================
*
*   Computer Vision and Image Processing Lab - Dr. Scott Umbaugh SIUE
* 
* =========================================================================
*
*             File Name: otsu_threshold.c 
*           Description: it contains the function to threshold BYTE images 
*   Initial Coding Date: October 15, 2008
*           Portability: Standard (ANSI) C
*             Credit(s): Jhansi Lakshmi Akkineni
*                        Southern Illinois University at Edwardsville
*
** Copyright (c) 1995, 1996, SIUE - Scott Umbaugh, Kun Luo, Yansheng Wei
****************************************************************************/

/*
** include header files
*/

#include "CVIPtoolkit.h"
#include "CVIPdef.h"
#include "CVIPimage.h"
#include "CVIPsegment.h"



#define 	WHITE_LAB	255
#define		BLACK_LAB	0

Image *otsu_segment(Image *inputImage){

    float 		**image; 	/* 2-d matrix data pointer */
    unsigned int 		r,		/* row index */
			c, 		/* column index */
			bands;		/* band index */
			
    unsigned int 	no_of_rows,	/* number of rows in image */
			no_of_cols,	/* number of columns in image */
			no_of_bands;	/* number of image bands */

	int t, g;
	Image* tempImage;

    no_of_bands = getNoOfBands_Image(inputImage);
    no_of_rows =  getNoOfRows_Image(inputImage);
    no_of_cols =  getNoOfCols_Image(inputImage);

	if (getDataType_Image(inputImage) < CVIP_FLOAT)
	{
		tempImage = duplicate_Image(inputImage);
		cast_Image(tempImage, CVIP_FLOAT);
		tempImage = condRemap_Image(tempImage, CVIP_FLOAT, 0, 255);
	}
	else
	{
		tempImage = condRemap_Image(inputImage, CVIP_FLOAT, 0, 255);
	}

    for(bands=0; bands < no_of_bands; bands++) {

		float p1[256] = {0}, p2[256] = {0}, mean1[256] = {0}, mean2[256] = {0}, sigma[256] = {0};
	    int threshval = 1;
	    float tmp=0.0, temp;
		float p[256] = {0};

		image = getData_Image(tempImage, bands);

		for(r=0;r<no_of_rows;r++)
		{
			for(c=0;c<no_of_cols;c++)
			{
				g=image[r][c];
				p[g] = p[g] + 1.0;
			}
		}
		for(t=1; t<256; t++)
		{
			for(g=1; g<t+1; g++)
			{
				//temp = p[g]/(no_of_rows*no_of_cols);
				p1[t] = p1[t] + p[g];
				mean1[t] = mean1[t] + (g * p[g]);
			}
			for(g=t+1; g<256; g++)
			{
				//temp = p[g]/(no_of_rows*no_of_cols);
				p2[t] = p2[t] + p[g];
				mean2[t] = mean2[t] + (g * p[g]);
			}
			mean1[t] = mean1[t] / p1[t];
			mean2[t] = mean2[t] / p2[t];
			p1[t] = p1[t] / (no_of_rows*no_of_cols);
			p2[t] = p2[t] / (no_of_rows*no_of_cols);
			sigma[t] = p1[t] * p2[t] *(mean1[t]-mean2[t])*(mean1[t]-mean2[t]);
			if(sigma[t] > tmp)
			{
				threshval = t;
				tmp = sigma[t];
			}
		}
		printf("Threshold value choosen for band %d is: %d\n", bands, threshval);
		for(r=0; r < no_of_rows; r++) 
		{
     	    for(c=0; c < no_of_cols; c++) 
			{
				if(image[r][c] > (byte) threshval)
            		image[r][c] = WHITE_LAB;
	  			else 
	     			image[r][c] = BLACK_LAB;
            }
     	}
	}
    inputImage = condRemap_Image(tempImage, CVIP_BYTE, 0, 255);
    return inputImage;
}

