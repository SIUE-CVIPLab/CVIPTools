

/***************************************************************************
* =========================================================================
*
*   Computer Vision and Image Processing Lab - Dr. Scott Umbaugh SIUE
*
* =========================================================================
*
*             File Name: marr_hildreth_edge.c
*           Description: Marr Hildreth's Edge Detector
*   Initial Coding Date: Feb 10th 2009
*           Portability: Standard (ANSI) C
*             Credit(s): Jhansi Lakshmi Akkineni
*                        Southern Illinois University at Edwardsville
*
** Copyright (c) 1995, 2004, SIUE - Scott Umbaugh, Kun Luo, Yansheng Wei
****************************************************************************/


#include "CVIPconvert.h"
#include "CVIPimage.h"
#include <CVIPspfltr.h>
#include "CVIPfs.h"


/* Function Prototypes*/
float distance(float x1, float y1, float x2, float y2);
float gauss_marr(float d, float sigma);
float LoG(float d, float sigma);
//extern Image* convolve_filter(Image* img, Matrix* mat);


Image* marr_hildreth_filter(Image* img, float sigma, int thresholdVal)
{
	float d;
	Image* imgLoG;
	Matrix* mat;
	float** dataImg;
	short** dataLoG;
	unsigned int band, row, col, n, width;
	unsigned int num_bands, num_rows, num_cols;
	CVIP_TYPE data_type;
	data_type = getDataType_Image(img);

	/* Create a Gaussian and a derivative of Gaussian filter mask */
	width = (unsigned int)((3.35 * sigma) + 0.33);
	n = (2 * width) + 1;
	printf("Smoothing with a Gaussian of size %dx%d\n", n, n);

	mat = new_Matrix(n, n, CVIP_FLOAT, REAL);
	for (row = 0; row < n; row++)
	{
		for (col = 0; col < n; col++)
		{
			d = distance((float)row, (float)col, (float)width, (float)width);
			((float**)(mat->rptr))[row][col] = LoG(d, sigma);
		}
	}

	/* Convolution of source image with a Gaussian in X and Y directions */
	imgLoG = duplicate_Image(img);
	if (data_type == CVIP_INTEGER || data_type == CVIP_FLOAT)
		imgLoG = remap_Image(imgLoG, CVIP_SHORT, 0, 255);
	printf("Convolution with LoG:\n");
	imgLoG = (Image*)convolve_filter(imgLoG, mat);

	/* Locate the zero crossings */
	printf("Zero crossings:\n");

	num_bands = getNoOfBands_Image(img);
	num_rows = getNoOfRows_Image(img);
	num_cols = getNoOfCols_Image(img);
	cast_Image(img, CVIP_FLOAT);

	for (band = 0; band < num_bands; band++)
	{
		dataImg = getData_Image(img, band);
		dataLoG = getData_Image(imgLoG, band);

		for (row = 0; row < num_rows; row++)
		{
			for (col = 0; col < num_cols; col++)
			{
				dataImg[row][col] = 0;

				if ((row <= width) || (row >= (num_rows - width - 1)) ||
					(col <= width) || (col >= (num_cols - width - 1)))
					continue;

				if (((dataLoG[row - 1][col] * dataLoG[row + 1][col]) < 0) && (abs(dataLoG[row - 1][col] - dataLoG[row + 1][col]) > thresholdVal))
				{
					dataImg[row][col] = 255;
					continue;
				}
				if (((dataLoG[row][col - 1] * dataLoG[row][col + 1]) < 0) && (abs(dataLoG[row][col - 1] - dataLoG[row][col + 1]) > thresholdVal))
				{
					dataImg[row][col] = 255;
					continue;
				}
				if (((dataLoG[row + 1][col - 1] * dataLoG[row - 1][col + 1]) < 0) && (abs(dataLoG[row + 1][col - 1] - dataLoG[row - 1][col + 1]) > thresholdVal))
				{
					dataImg[row][col] = 255;
					continue;
				}
				if (((dataLoG[row - 1][col - 1] * dataLoG[row + 1][col + 1]) < 0) && (abs(dataLoG[row - 1][col - 1] - dataLoG[row + 1][col + 1]) > thresholdVal))
				{
					dataImg[row][col] = 255;
					continue;
				}
			}
		}
	}

	delete_Image(imgLoG);
	delete_Matrix(mat);

	return img;
}

float distance(float x1, float y1, float x2, float y2)
{
	double x = (double)(x1 - x2);
	double y = (double)(y1 - y2);
	return (float)sqrt(x * x + y * y);
}

float gauss_marr(float d, float sigma)
{
	return (float)exp((double)((-d * d) / (2 * sigma * sigma)));
}

float LoG(float d, float sigma)
{
	float x1 = gauss_marr(d, sigma);
	return (d * d - 2 * sigma * sigma) / (sigma * sigma * sigma * sigma) * x1;
}