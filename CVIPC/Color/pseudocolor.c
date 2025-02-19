/***************************************************************************
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* **************************************************************************
*
*             File Name: pseudocolor.c
*           Description: 
*         Related Files: 
*   Initial Coding Date: Nov. 4th 2002
*           Portability: Standard (ANSI) C
*            References:
*             Author(s): Xiaohe Chen
*                        Southern Illinois University at Edwardsville
*
** Copyright (C) 1996 SIUE - by Scott Umbaugh and Yansheng Wei.
**
** Permission to use, copy, modify, and distribute this software and its
** documentation for any purpose and without fee is hereby granted, provided
** that the above copyright notice appear in all copies and that both that
** copyright notice and this permission notice appear in supporting
** documentation.  This software is provided "as is" without express or
** implied warranty.
**
****************************************************************************
****************************************************************************/
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CVIPtools.h"
#include "CVIPimage.h"
#include "CVIPdef.h"
#include "CVIPmap.h"
#include "CVIPconvert.h"
/********************************************************************************
********************************************************************************/
Image * pseudo_remap( Image *inputImage, byte **lookupTable)
{

	byte ** pImageMatrix;
	byte **newImageMatrix;
	Image * outImage;

	int no_of_rows, no_of_cols, no_of_bands;
	int counter = 1;

	int bands = 0;
	int i, r, c;
	byte cc;


	
	
	/****************************
	Copy the old image to new image
	****************************/
	no_of_rows =  getNoOfRows_Image(inputImage);
	no_of_cols =  getNoOfCols_Image(inputImage);

	outImage = new_Image(inputImage->image_format, RGB, 3, no_of_rows, no_of_cols, CVIP_BYTE, REAL);

	
	no_of_bands = getNoOfBands_Image(inputImage);
	
	/*
	** Should be grayscale images
	*/
	pImageMatrix = getData_Image(inputImage, 0);
	for (i = 0; i < 3; i++)
	{
		newImageMatrix = getData_Image(outImage, i);
  		for(r = 0; r < no_of_rows; r++) 
			for(c = 0; c < no_of_cols; c++)
		{
			cc = pImageMatrix[r][c];
			//newImageMatrix[r][c] = pMatrix[i][cc];
			newImageMatrix[r][c] = lookupTable[i][cc];
			
		}
	}
	return outImage;
}
/***************************************************************************
*** End of pseudocolor.c
****************************************************************************/