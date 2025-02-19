/***************************************************************************
* =========================================================================
*
*   Computer Vision and Image Processing Lab - Dr. Scott Umbaugh SIUE
* 
* =========================================================================
*
*             File Name: harris_corner_detector.c 
*           Description: Harris corner Edge Detector
*   Initial Coding Date: Apr 10th 2009
*           Portability: Standard (ANSI) C
*             Credit(s): Mounika Mamidi
*                        Southern Illinois University at Edwardsville
*
** Copyright (c) 1995, 2004, SIUE - Scott Umbaugh, Kun Luo, Yansheng Wei
****************************************************************************/
#include <CVIPspfltr.h>
#include "CVIPtoolkit.h"
#include "CVIPconvert.h"
#include "CVIPdef.h"
#include "CVIPimage.h"
#include "CVIPtransform.h"
#include "CVIParithlogic.h"



/*
** global variables
*/
Image *A = NULL, *B = NULL, *C = NULL, *Q = NULL;

/*
** nonmaxima_mask function declaration
*/
void nonmaxima_mask(float **pixImg, unsigned char **pixMask, int rows, int cols, int border, float dmin, int threshold);


/*
**  1-D Horizontal/Vertical convolution
**
**    - Input image must be CVIP_FLOAT datatype
**    - Input image will be deleted
**    - filt = 1-D float array
**    - sz   = size of float array. Must be odd.
*/
Image* convolve1h_float(Image *img, float *filt, unsigned int sz)
{
	Image *imgOut;
	int idx, offset;
	float **dataIn, **dataOut, val;
	unsigned int i, band, row, col;
	unsigned int bands, rows, cols;

	bands = getNoOfBands_Image(img);
	rows = getNoOfRows_Image(img);
	cols = getNoOfCols_Image(img);

	imgOut = new_Image(img->image_format, img->color_space, bands, rows, cols, CVIP_FLOAT, REAL);

	for(band=0; band<bands; band++)
	{
		dataIn = getData_Image(img, band);
		dataOut = getData_Image(imgOut, band);
		for(row=0; row<rows; row++)
		{
			offset = (int)row - (sz/2);
			for(col=0; col<cols; col++)
			{
				val = 0.0f;
				for(i=0; i<sz; i++)
				{
					idx = offset + i;
					if((idx>=0) && ((unsigned int)idx<rows)) val += (dataIn[idx][col] * filt[i]);
				}
				dataOut[row][col] = val;
			}
		}
	}

	delete_Image(img);
	return imgOut;
}

Image* convolve1v_float(Image *img, float *filt, unsigned int sz)
{
	Image *imgOut;
	int idx, offset;
	float **dataIn, **dataOut, val;
	unsigned int i, band, row, col;
	unsigned int bands, rows, cols;

	bands = getNoOfBands_Image(img);
	rows = getNoOfRows_Image(img);
	cols = getNoOfCols_Image(img);

	imgOut = new_Image(img->image_format, img->color_space, bands, rows, cols, CVIP_FLOAT, REAL);

	for(band=0; band<bands; band++)
	{
		dataIn = getData_Image(img, band);
		dataOut = getData_Image(imgOut, band);
		for(col=0; col<cols; col++)
		{
			offset = (int)col - (sz/2);
			for(row=0; row<rows; row++)
			{
				val = 0.0f;
				for(i=0; i<sz; i++)
				{
					idx = offset + i;
					if((idx>=0) && ((unsigned int)idx<cols)) val += (dataIn[row][idx] * filt[i]);
				}
				dataOut[row][col] = val;
			}
		}
	}

	delete_Image(img);
	return imgOut;
}

Image* convolve2_float(Image *img, float *filt, unsigned int sz)
{
	return convolve1v_float(convolve1h_float(img, filt, sz), filt, sz);
}

/* 
** create the derivative images
*/
void make_derivatives(Image *inputImage)
{
    // filter kernels (one-dim. part of separable 2D filters)
	const float pfilt[3] = {0.223755f, 0.552490f, 0.223755f};
	const float dfilt[3] = {0.453014f, 0.0f, -0.453014f};
	const float bfilt[7] = {0.01563f, 0.09375f, 0.234375f, 0.3125f, 0.234375f, 0.09375f, 0.01563f};

	Image *dup, *iX, *iY;

	// create Ix and Iy images
	// step 1: 1-d gaussian blur
	dup = duplicate_Image(inputImage);
	cast_Image(dup, CVIP_FLOAT);
	iX = convolve1h_float(duplicate_Image(dup), pfilt, 3);
	iY = convolve1v_float(dup, pfilt, 3);

	// step 2: 1-d edge detector
	iX = convolve1h_float(iX, dfilt, 3);
	iY = convolve1v_float(iY, dfilt, 3);

	// create A, B, and C images
	C = multiply_Image(duplicate_Image(iX), duplicate_Image(iY));
	A = multiply_Image(iX, duplicate_Image(iX));
	B = multiply_Image(iY, duplicate_Image(iY));

	// 2-d blur A, B, and C images
	A = convolve2_float(A, bfilt, 7);
	B = convolve2_float(B, bfilt, 7);
	C = convolve2_float(C, bfilt, 7);
}

/* 
** create crf image
*/
void make_crf(float alpha)
{
	float **pixA, **pixB, **pixC, **pixQ;
	float a, b, c, det, trace;
	unsigned int band, row, col;
	unsigned int bands, rows, cols;

	bands = getNoOfBands_Image(A);
	rows = getNoOfRows_Image(A);
	cols = getNoOfCols_Image(A);

	Q = new_Image(A->image_format, A->color_space, bands, rows, cols, CVIP_FLOAT, REAL);

	for(band=0; band<bands; band++)
	{
		pixA = getData_Image(A, band);
		pixB = getData_Image(B, band);
		pixC = getData_Image(C, band);
		pixQ = getData_Image(Q, band);

		for(row=0; row<rows; row++)
		{
			for(col=0; col<cols; col++)
			{
				a = pixA[row][col];
				b = pixB[row][col];
				c = pixC[row][col];
				det = (a * b) - (c * c);
				trace = a + b;
				pixQ[row][col] = det - alpha * (trace * trace);
			}
		}
	}
}


/* 
** harris corner detector
*/
Image* harris_corner_filter(Image *inputImage, float alpha, int threshold, int border, float dmin)
{
	float **pixQ;
	byte **pixMask;
	Image *imgMask;
	unsigned int band;
	unsigned int bands, rows, cols;

	make_derivatives(inputImage);
	make_crf(alpha);

	bands = getNoOfBands_Image(Q);
	rows = getNoOfRows_Image(Q);
	cols = getNoOfCols_Image(Q);

	imgMask = new_Image(Q->image_format, Q->color_space, bands, rows, cols, CVIP_BYTE, REAL);

	for(band=0; band<bands; band++)
	{
		pixQ = getData_Image(Q, band);
		pixMask = getData_Image(imgMask, band);
		nonmaxima_mask(pixQ, pixMask, rows, cols, border, dmin, threshold);
	}

	return imgMask;
}
