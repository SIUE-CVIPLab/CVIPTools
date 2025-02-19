/***************************************************************************
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* **************************************************************************
*
*             File Name: watershed.c
*           Description: 
*         Related Files: 
*   Initial Coding Date: May. 4th 2003
*           Portability: Standard (ANSI) C
*            References:
*             Author(s): Xiaohe Chen
*                        Southern Illinois University
*
** Copyright (C) 2003 SIUE - by Scott Umbaugh and Xiaohe Chen.
**
** Permission to use, copy, modify, and distribute this software and its
** documentation for any purpose and without fee is hereby granted, provided
** that the above copyright notice appear in all copies and that both that
** copyright notice and this permission notice appear in supporting
** documentation.  This software is provided "as is" without express or
** implied warranty.
****************************************************************************/
#include "watershed.h"
#include "CVIPmap.h"

Image * watershed2(Image *inputImage, float threshold, int choice);
Image * watershed3(Image *inputImage, float threshold, int choice);
int Markpoint(int ** outImage, int r, int c, int * CurrentLabelNo, int no_of_rows, int no_of_cols);
int TraversePlateau(byte **ImageData, int **PlateauMatrix, int no_of_rows, int no_of_cols);
int Rainfall(Image * pGrayImage, int ** pLabelMatrix, int ** pPlateauMatrix, int CurrentLabel, int r, int c);
byte GetAverageColor(Image * pGrayImage, int ** pLabelMatrix, byte ** pCruiseMatrix, int r, int c, int no_of_pixels, double tmpColor);
int Merge(Image * pGrayImage, Image * labelImage, float threshold);
int MergeSegment(Image * pGrayImage, Image * labelImage, float threshold);
long GetObjectCount(Image * pGrayImage, int ** pLabelMatrix, byte ** pCruiseMatrix, int r, int c, int no_of_pixels, long tmpCount1);

/********************************************************************************
** Function --	watershed_segment
**
** In -- <inputImage> Pointer to image structure
**		 <threshold>  Threshold value
**		 <choice>	  CVIP_NO  (0) Do not merge result
**					  CVIP_YES (1) To merge result
**
*******************************************************************************/
Image *watershed_segment(Image *inputImage, float threshold, CVIP_BOOLEAN choice)
{
	IMAGE *outImage;
	 
	if (choice == CVIP_YES)
		outImage = watershed3(inputImage, threshold, 0);
	else
		outImage = watershed2(inputImage, threshold, 0);
	
	return outImage;
}
/********************************************************************************
**
**
**
**
**
**
**
**
********************************************************************************/
Image * watershed(Image *inputImage)
{

	byte ** pImageMatrix;
	int ** pLabelMatrix;
	Image * outImage;
	Image * tmpImage;
	int ** pTemp; /* array to store the max and min value of each band */
   
	int no_of_rows, no_of_cols, no_of_bands;
	int counter = 1;

	int bands = 0;
	int i, r, c;
	int * CurrentLabel;
	
	/****************************
	initialize
	****************************/
	no_of_rows =  getNoOfRows_Image(inputImage);
	no_of_cols =  getNoOfCols_Image(inputImage);
	no_of_bands = getNoOfBands_Image(inputImage);
	pTemp = (int **)calloc(no_of_bands, sizeof(int *));

	CurrentLabel = (int *)malloc(sizeof(int));
	* CurrentLabel = 1;

	for (i = 0; i < no_of_bands; i++)
	{
		pTemp[i] = (int *)calloc(2, sizeof(int));
		pTemp[i][0] = 255;	// min
		pTemp[i][1] = 0;	// max
	}
	
	/*
	** Label Image
	** band 1 is the label band
	** band 2 is the dam band
	** band 3 is reserved for future use
	*/
	tmpImage = new_Image(inputImage->image_format, RGB, 3, no_of_rows, no_of_cols, CVIP_BYTE, REAL);
	outImage = new_Image(inputImage->image_format, RGB, 1, no_of_rows, no_of_cols, CVIP_INTEGER, REAL);
	
	/*
	** Preprocess
	*/
	pLabelMatrix = getData_Image(tmpImage, 0);
	for (i = 0; i < no_of_bands; i++)
	{
		pImageMatrix = getData_Image(inputImage, i);
  		for(r = 0; r < no_of_rows; r++) 
			for(c = 0; c < no_of_cols; c++)
		{
			if (pTemp[i][0]	> pImageMatrix[r][c])
				pTemp[i][0] = pImageMatrix[r][c];
			if (pTemp[i][1]	< pImageMatrix[r][c])
				pTemp[i][1] = pImageMatrix[r][c];
		}
	}
	
	for (i = 0; i < no_of_bands; i++)
	{
		pLabelMatrix = getData_Image(outImage, i);
		pImageMatrix = getData_Image(inputImage, i);
  		for(r = 0; r < no_of_rows; r++) 
			for(c = 0; c < no_of_cols; c++)
		{
			pLabelMatrix[r][c] = 0;

			if (pTemp[i][0]	> pImageMatrix[r][c])
				pTemp[i][0] = pImageMatrix[r][c];
			// only for test
			// pTemp[i][0] = 200;
			if (pTemp[i][1]	< pImageMatrix[r][c])
				pTemp[i][1] = pImageMatrix[r][c];
		}
	}
	/*
	** main loop to label the pixels
	*/
	for (i = 0; i < no_of_bands; i++)
	{
		pLabelMatrix = getData_Image(outImage, i);
		pImageMatrix = getData_Image(inputImage, i);
		while (pTemp[i][0]	< pTemp[i][1])
		{
  			for(r = 0; r < no_of_rows; r++)
				for(c = 0; c < no_of_cols; c++)
			{
				if (pImageMatrix[r][c] == pTemp[i][0])
					Markpoint(pLabelMatrix, r, c, CurrentLabel, no_of_rows, no_of_cols);
			}
			pTemp[i][0] = pTemp[i][0] + 1;
		}
	}

	// append for experiment
	/*
	for (i = 0; i < no_of_bands; i++)
	{
		pLabelMatrix = getData_Image(outImage, i);
		pImageMatrix = getData_Image(inputImage, i);
		for(r = 0; r < no_of_rows; r++)
			for(c = 0; c < no_of_cols; c++)
		{
			if (pLabelMatrix[r][c] == 65535)
				pLabelMatrix[r][c] = 0;
			else
				pLabelMatrix[r][c] = pImageMatrix[r][c];
		}
	}
	*/
	delete_Image(tmpImage);
	return outImage;
}
/********************************************************************************
********************************************************************************/
int Markpoint(int ** pLabelMatrix, int r, int c, int * CurrentLabelNo, int no_of_rows, int no_of_cols)
{
	int no_of_labeled_pixel;
	int current_label, previous_label;
	int isDam;


	no_of_labeled_pixel = 0;
	isDam = 0;
	current_label = 0;
	previous_label = 0;

	if (r == 0)
	{
		/************************************************************/
		if (c == 0)
		{
			if (r < no_of_rows - 1)
				if (pLabelMatrix[r+1][c] != 0)
			{
				no_of_labeled_pixel = no_of_labeled_pixel + 1;
				if ((previous_label != 0) && (current_label != previous_label))
					previous_label = current_label;
				current_label = pLabelMatrix[r+1][c];
			}
			if (c < no_of_cols - 1)
				if (pLabelMatrix[r][c+1] != 0)
			{
				no_of_labeled_pixel = no_of_labeled_pixel + 1;
				if ((previous_label != 0) && (current_label != previous_label))
				{
					previous_label = current_label;
				}
				current_label = pLabelMatrix[r][c+1];
			}
			if ((r < no_of_rows - 1) && (c < no_of_cols - 1))
				if (pLabelMatrix[r+1][c+1] != 0)
			{
				no_of_labeled_pixel = no_of_labeled_pixel + 1;
				if ((previous_label != 0) && (current_label != previous_label))
				{
					previous_label = current_label;
				}
				current_label = pLabelMatrix[r+1][c+1];
			}
		}
		else
		{
			if (r < no_of_rows - 1)
				if (pLabelMatrix[r+1][c-1] != 0)
			{
				no_of_labeled_pixel = no_of_labeled_pixel + 1;
				if ((previous_label != 0) && (current_label != previous_label))
				{
					previous_label = current_label;
				}
				current_label = pLabelMatrix[r+1][c-1];
			}
			if (pLabelMatrix[r][c-1] != 0)
			{
				no_of_labeled_pixel = no_of_labeled_pixel + 1;
				if ((previous_label != 0) && (current_label != previous_label))
				{
					previous_label = current_label;
				}
				current_label = pLabelMatrix[r][c-1];
			}
		}
		/************************************************************/
	}
	else
	{
		if (pLabelMatrix[r-1][c] != 0)
		{
			no_of_labeled_pixel = no_of_labeled_pixel + 1;
			if ((previous_label != 0) && (current_label != previous_label))
			{
				previous_label = current_label;
			}
			current_label = pLabelMatrix[r-1][c];
		}
		if (c < no_of_cols - 1)
			if (pLabelMatrix[r-1][c+1] != 0)
		{
			no_of_labeled_pixel = no_of_labeled_pixel + 1;
			if ((previous_label != 0) && (current_label != previous_label))
			{
				previous_label = current_label;
			}
			current_label = pLabelMatrix[r-1][c+1];
		}
		/************************************************************/
		if (c == 0)
		{
			if (r < no_of_rows - 1)
				if (pLabelMatrix[r+1][c] != 0)
			{
				no_of_labeled_pixel = no_of_labeled_pixel + 1;
				if ((previous_label != 0) && (current_label != previous_label))
				{
					previous_label = current_label;
				}
				current_label = pLabelMatrix[r+1][c];
			}
			if (c < no_of_cols - 1)
				if (pLabelMatrix[r][c+1] != 0)
			{
				no_of_labeled_pixel = no_of_labeled_pixel + 1;
				if ((previous_label != 0) && (current_label != previous_label))
				{
					previous_label = current_label;
				}
				current_label = pLabelMatrix[r][c+1];
			}
			if ((r < no_of_rows - 1) && (c < no_of_cols - 1))
				if (pLabelMatrix[r+1][c+1] != 0)
			{
				no_of_labeled_pixel = no_of_labeled_pixel + 1;
				if ((previous_label != 0) && (current_label != previous_label))
				{
					previous_label = current_label;
				}
				current_label = pLabelMatrix[r+1][c+1];
			}
		}
		else
		{
			if (pLabelMatrix[r-1][c-1] != 0)
			{
				no_of_labeled_pixel = no_of_labeled_pixel + 1;
				if ((previous_label != 0) && (current_label != previous_label))
				{
					previous_label = current_label;

				}
				current_label = pLabelMatrix[r-1][c-1];
			}
			if (r < no_of_rows - 1)
				if (pLabelMatrix[r+1][c-1] != 0)
			{
				no_of_labeled_pixel = no_of_labeled_pixel + 1;
				if ((previous_label != 0) && (current_label != previous_label))
				{
					previous_label = current_label;
				}
				current_label = pLabelMatrix[r+1][c-1];
			}
			if (pLabelMatrix[r][c-1] != 0)
			{
				no_of_labeled_pixel = no_of_labeled_pixel + 1;
				if ((previous_label != 0) && (current_label != previous_label))
				{
					previous_label = current_label;
				}
				current_label = pLabelMatrix[r][c-1];
			}
		}
		/************************************************************/
	}
	/************************************************************/
	/* isDam 0: not a dam, 1: a dam. -1 new abyss
	/************************************************************/
	if (previous_label != 0)
		isDam = 1;
	else if (current_label == 0)
		isDam = -1;

	if (isDam > 0)
	{
		/* mark as dam */
		pLabelMatrix[r][c] = 65535;
	}
	else if (isDam == 0)
	{
		/* only one adjacent pixel was labeled, so label it as the other one */
		pLabelMatrix[r][c] = current_label;
	}
	else if (isDam < 0)
	{
		pLabelMatrix[r][c] = * CurrentLabelNo;
		* CurrentLabelNo = * CurrentLabelNo + 1;
	}

	return 1;
}
/***************************************************************************
** Steepest Step
***************************************************************************/
/*
int * Steepest(int **dataMatrix, int r, int c, int no_of_rows, int no_of_cols)
{
	int minimumX, minimumY;
	int * returnArray;
	int minimumAltitude;

	returnArray = (int *)malloc(2*sizeof(int));
	minimumAltitude = dataMatrix[r][c];
	if (r > 0)
		if (minimumAltitude > dataMatrix[r-1][c])
	{
		minimumAltitude = dataMatrix[r-1][c];
		minimumX = r - 1;
		minimumY = c;
	}
	if (c > 0)
		if (minimumAltitude > dataMatrix[r][c-1])
	{
		minimumAltitude = dataMatrix[r][c-1];
		minimumX = r;
		minimumY = c - 1;
	}
	if ((r > 0) && (c > 0))
		if (minimumAltitude > dataMatrix[r-1][c-1])
	{
		minimumAltitude = dataMatrix[r-1][c-1];
		minimumX = r - 1;
		minimumY = c - 1;
	}

	if (r < no_of_rows)
		if (minimumAltitude > dataMatrix[r+1][c])
	{
		minimumAltitude = dataMatrix[r+1][c];
		minimumX = r + 1;
		minimumY = c;
	}
	if (c < no_of_cols)
		if (minimumAltitude > dataMatrix[r][c+1])
	{
		minimumAltitude = dataMatrix[r][c+1];
		minimumX = r;
		minimumY = c + 1;
	}
	if ((r < no_of_rows) && (c < no_of_cols))
		if (minimumAltitude > dataMatrix[r+1][c+1])
	{
		minimumAltitude = dataMatrix[r+1][c+1];
		minimumX = r + 1;
		minimumY = c + 1;
	}
	if ((r > 0) && (c < no_of_cols))
		if (minimumAltitude > dataMatrix[r-1][c+1])
	{
		minimumAltitude = dataMatrix[r-11][c+1];
		minimumX = r - 1;
		minimumY = c + 1;
	}
	if ((r < no_of_rows) && (c > 0))
		if (minimumAltitude > dataMatrix[r+1][c-1])
	{
		minimumAltitude = dataMatrix[r+1][c-1];
		minimumX = r + 1;
		minimumY = c - 1;
	}

	//////////////////////////////////////////////////
	if ((minimumX == r) && (minimumY == c))
	{
		returnArray[0] = -1;
		returnArray[1] = -1;
	}
	else
	{
		returnArray[0] = minimumX;
		returnArray[1] = minimumY;
	}
	return returnArray;
}
*/
/***************************************************************************
** Steepest Step
** in this function, return value is and 10 bits integer which reflect the
** steepest routine of the certain pixel. each of 8 bits stands for one of the
** adjacent pixel. 0 for not a routine, 1 for a selection either plateau or deepest
** path.
** The highest bit was the determination whether the the point's outlet(s) is in the
** same plateau
** return value
** 0 : regional minimum not on a plateau
** 1 - 255 rainfall path with outlet(s) (possible a plateau pixel with lower outlet)
** 256 : not valid number
** > 256 and < 512 : plateaum with same altitude.
** > 512 is a pixel on plateau
** returnMask bit 0		: has outlet on position 0
			  bit 1     : has outlet on position 1
			  ...
			  bit 7     : has outlet on position 7
			  bit 8     : outlet has same altitude with original point
			  bit 9     : original point belong to a plateau
***************************************************************************/
int Steepest(byte **dataMatrix, int r, int c, int no_of_rows, int no_of_cols)
{
	//int minimumX, minimumY;
	int returnMask;
	int minimumAltitude;

	minimumAltitude = dataMatrix[r][c];
	returnMask = 0;
	/**********************************/
	/* calculate the minimum altitude */
	/* count the plateau              */
	/**********************************/
	if (r > 0)
	{
		if (minimumAltitude > dataMatrix[r-1][c])
			minimumAltitude = dataMatrix[r-1][c];
		if (dataMatrix[r][c] == dataMatrix[r-1][c])
			returnMask = returnMask | 512;
	}
	if (c > 0)
	{
		if (minimumAltitude > dataMatrix[r][c-1])
			minimumAltitude = dataMatrix[r][c-1];
		if (dataMatrix[r][c] == dataMatrix[r][c-1])
			returnMask = returnMask | 512;
	}
	if ((r > 0) && (c > 0))
	{
		if (minimumAltitude > dataMatrix[r-1][c-1])
			minimumAltitude = dataMatrix[r-1][c-1];
		if (dataMatrix[r][c] == dataMatrix[r-1][c-1])
			returnMask = returnMask | 512;
	}
	if (r < no_of_rows - 1)
	{
		if (minimumAltitude > dataMatrix[r+1][c])
			minimumAltitude = dataMatrix[r+1][c];
		if (dataMatrix[r][c] == dataMatrix[r+1][c])
			returnMask = returnMask | 512;
	}
	if (c < no_of_cols - 1)
	{
		if (minimumAltitude > dataMatrix[r][c+1])
			minimumAltitude = dataMatrix[r][c+1];
		if (dataMatrix[r][c] == dataMatrix[r][c+1])
			returnMask = returnMask | 512;
	}
	if ((r < no_of_rows - 1) && (c < no_of_cols - 1))
	{
		if (minimumAltitude > dataMatrix[r+1][c+1])
			minimumAltitude = dataMatrix[r+1][c+1];
		if (dataMatrix[r][c] == dataMatrix[r+1][c+1])
			returnMask = returnMask | 512;
	}
	if ((r > 0) && (c < no_of_cols - 1))
	{
		if (minimumAltitude > dataMatrix[r-1][c+1])
			minimumAltitude = dataMatrix[r-1][c+1];
		if (dataMatrix[r][c] == dataMatrix[r-1][c+1])
			returnMask = returnMask | 512;
	}
	if ((r < no_of_rows - 1) && (c > 0))
	{
		if (minimumAltitude > dataMatrix[r+1][c-1])
			minimumAltitude = dataMatrix[r+1][c-1];
		if (dataMatrix[r][c] == dataMatrix[r+1][c-1])
			returnMask = returnMask | 512;
	}
	/**********************************/
	/* decide the deepest path or     */
	/* create the mask by bitwise or  */
	/**********************************/
	if ((r > 0) && (c > 0))
		if (minimumAltitude == dataMatrix[r-1][c-1])
			returnMask = returnMask | 1;
	if (r > 0)
		if (minimumAltitude == dataMatrix[r-1][c])
			returnMask = returnMask | 2;
	if ((r > 0) && (c < no_of_cols - 1))
		if (minimumAltitude == dataMatrix[r-1][c+1])
			returnMask = returnMask | 4;
	if (c < no_of_cols - 1)
		if (minimumAltitude == dataMatrix[r][c+1])
			returnMask = returnMask | 8;
	if ((r < no_of_rows - 1) && (c < no_of_cols - 1))
		if (minimumAltitude == dataMatrix[r+1][c+1])
			returnMask = returnMask | 16;
	if (r < no_of_rows - 1)
		if (minimumAltitude == dataMatrix[r+1][c])
			returnMask = returnMask | 32;
	if ((r < no_of_rows - 1) && (c > 0))
		if (minimumAltitude == dataMatrix[r+1][c-1])
			returnMask = returnMask | 64;
	if (c > 0)
		if (minimumAltitude == dataMatrix[r][c-1])
				returnMask = returnMask | 128;
	/* Determine if the outlet has same altitude with orginal point */
	if ((minimumAltitude == dataMatrix[r][c]) && (returnMask != 0))
		returnMask = returnMask | 256;

	return returnMask;

}
/***************************************************************************
** Function Name : isPlateau
** Description   : determine if the pixel belong to a plateau and
                   if the pixel has lower or plat outlet
** return        : 0 not a pixel on plateau
                 : 1 not possible
				 : 2 a pixel on the plateau that has lower outlet(s)
				 : 3 a pixel on the plateau that has same altitude outlet(s)
***************************************************************************/
int isPlateau(int evaMask)
{
	//////////////////////////////////////////////////
	//int Plateau;	/* if the point belong to the plateau */
	div_t div_result;

	div_result = div(evaMask, 128);
	return div_result.quot;
}
/****************************************************************************/
/***************************************************************************/
int PositionIsOutlet(int nmMask, int positionNo)
{
	int MaskOut;
	MaskOut = nmMask & (int)pow(2, positionNo);
	if (MaskOut != 0)
		return 1;
	else
		return 0;
}
/***************************************************************************
***************************************************************************/
int getPlateauNeighbor(byte **dataMatrix, int r, int c, int no_of_rows, int no_of_cols)
{
	int returnMask;
	int minimumAltitude;

	minimumAltitude = dataMatrix[r][c];
	returnMask = 0;
	/**********************************/
	/* count the plateau              */
	/**********************************/
	if ((r > 0) && (c > 0))
		if (minimumAltitude == dataMatrix[r-1][c-1])
			returnMask = returnMask | 1;
	if (r > 0)
		if (minimumAltitude == dataMatrix[r-1][c])
			returnMask = returnMask | 2;
	if ((r > 0) && (c < no_of_cols))
		if (minimumAltitude == dataMatrix[r-1][c+1])
			returnMask = returnMask | 4;
	if (c < no_of_cols)
		if (minimumAltitude == dataMatrix[r][c+1])
			returnMask = returnMask | 8;
	if ((r < no_of_rows) && (c < no_of_cols))
		if (minimumAltitude == dataMatrix[r+1][c+1])
			returnMask = returnMask | 16;
	if (r < no_of_rows)
		if (minimumAltitude == dataMatrix[r+1][c])
			returnMask = returnMask | 32;
	if ((r < no_of_rows) && (c > 0))
		if (minimumAltitude == dataMatrix[r+1][c-1])
			returnMask = returnMask | 64;
	if (c > 0)
		if (minimumAltitude == dataMatrix[r][c-1])
				returnMask = returnMask | 128;

	return returnMask;

}
/***************************************************************************
return value : 0 - 65535 minimum neighbor plus 1
               65536 all neighbors haven't been marked.
***************************************************************************/
int minimumPath(int **dataMatrix, int r, int c, int nmMask)
{
	int minimumLabel;
	int i;
/* not finished */
	minimumLabel = 65535; /* maximum plat depth */
	for (i = 0; i < 8; i ++)
	{
		if (PositionIsOutlet(nmMask, i))
		switch (i)
		{
			case 0:
				minimumLabel = dataMatrix[r][c-1];
				break;
			case 1:
				minimumLabel = dataMatrix[r][c-1];
				break;
			case 2:
				minimumLabel = dataMatrix[r][c-1];
				break;
			case 3:
				minimumLabel = dataMatrix[r][c-1];
				break;
			case 4:
				minimumLabel = dataMatrix[r][c-1];
				break;
			case 5:
				minimumLabel = dataMatrix[r][c-1];
				break;
			case 6:
				minimumLabel = dataMatrix[r][c-1];
				break;
			case 7:
				minimumLabel = dataMatrix[r][c-1];
				break;
			default:
				break;
		}
	}
	/*
	if ((r > 0) && (c > 0) && (dataMatrix[r-1][c-1] != 0))
		if (minimumLabel > dataMatrix[r-1][c-1])
			minimumLabel = dataMatrix[r-1][c-1];
	if ((r > 0) && (dataMatrix[r-1][c] != 0))
		if (minimumLabel == dataMatrix[r-1][c])
			minimumLabel = dataMatrix[r-1][c];
	if ((r > 0) && (c < no_of_cols) && (dataMatrix[r-1][c+1] != 0))
		if (minimumLabel == dataMatrix[r-1][c+1])
			minimumLabel = dataMatrix[r-1][c+1];
	if ((c < no_of_cols) && (dataMatrix[r][c+1] != 0))
		if (minimumLabel == dataMatrix[r][c+1])
			minimumLabel = dataMatrix[r][c+1];
	if ((r < no_of_rows) && (c < no_of_cols) && (dataMatrix[r+1][c+1] != 0))
		if (minimumLabel == dataMatrix[r+1][c+1])
			minimumLabel = dataMatrix[r+1][c+1];
	if ((r < no_of_rows) && (dataMatrix[r+1][c] != 0))
		if (minimumLabel == dataMatrix[r+1][c])
			minimumLabel = dataMatrix[r+1][c];
	if ((r < no_of_rows) && (c > 0) && (dataMatrix[r+1][c-1] != 0))
		if (minimumLabel == dataMatrix[r+1][c-1])
			minimumLabel = dataMatrix[r+1][c-1];
	if ((c > 0) && (dataMatrix[r][c-1] != 0))
		if (minimumLabel == dataMatrix[r][c-1])
			minimumLabel = dataMatrix[r][c-1];
	*/
	return minimumLabel + 1;
	
}
/***************************************************************************
** Function Name   : MarkPlateau
** Description     : From outlet(s) of the plateau to mark the whole plaeau
**                 : according to rainfall simulation
***************************************************************************/
int MarkPlateau(byte **ImageData, int **PlateauMatrix, int r, int c, int no_of_rows, int no_of_cols, int Steps)
{
	int nmMask;
	//int nmPlateau;
	int i;

	nmMask = getPlateauNeighbor(ImageData, r, c, no_of_rows, no_of_cols);
	// if the marker should be lower then lower it.
	PlateauMatrix[r][c] = Steps;

	// Only the neighbor plateau pixel hasn't been marked or marked level > current level then
	// recurisvely mark plateau
	for (i = 0; i < 8; i ++)
	{
		if (PositionIsOutlet(nmMask, i))
		switch (i)
		{
			case 0:
				if (PlateauMatrix[r-1][c-1] <= Steps)
					MarkPlateau(ImageData, PlateauMatrix, r-1, c-1, no_of_rows, no_of_cols, Steps + 1);
			break;
			case 1:
				if (PlateauMatrix[r-1][c] <= Steps)
					MarkPlateau(ImageData, PlateauMatrix, r-1, c, no_of_rows, no_of_cols, Steps + 1);
			break;
			case 2:
				if (PlateauMatrix[r-1][c+1] <= Steps)
					MarkPlateau(ImageData, PlateauMatrix, r-1, c+1, no_of_rows, no_of_cols, Steps + 1);
			break;
			case 3:
				if (PlateauMatrix[r][c+1] <= Steps)
					MarkPlateau(ImageData, PlateauMatrix, r, c+1, no_of_rows, no_of_cols, Steps + 1);
			break;
			case 4:
				if (PlateauMatrix[r+1][c-1] <= Steps)
					MarkPlateau(ImageData, PlateauMatrix, r+1, c-1, no_of_rows, no_of_cols, Steps + 1);
			break;
			case 5:
				if (PlateauMatrix[r+1][c] <= Steps)
					MarkPlateau(ImageData, PlateauMatrix, r+1, c, no_of_rows, no_of_cols, Steps + 1);
			break;
			case 6:
				if (PlateauMatrix[r+1][c+1] <= Steps)
					MarkPlateau(ImageData, PlateauMatrix, r+1, c+1, no_of_rows, no_of_cols, Steps + 1);
			break;
			case 7:
				if (PlateauMatrix[r][c-1] <= Steps)
					MarkPlateau(ImageData, PlateauMatrix, r, c-1, no_of_rows, no_of_cols, Steps + 1);
			break;
			default:
			break;
		}
	}

	return 1;
}
/***************************************************************************
*** Procedure to traverse the plateau
***************************************************************************/
int TraversePlateau(byte **ImageData, int **PlateauMatrix, int no_of_rows, int no_of_cols)
{
	int nmPlateau;
	int nmMask;
	//int Steps;		/* an estimation that how faraway from the outlet of the plateau */
	//int minimumAltitude;
	int r, c;

	for (r = 0; r < no_of_rows; r++)
		for (c = 0; c < no_of_cols; c++)
	{
		nmMask = Steepest(ImageData, r, c, no_of_rows, no_of_cols);
		nmPlateau = isPlateau(nmMask);
		/*********************************************************/
		/* a pixel on the plateau that has lower outlet(s)       */
		/* mark it as the first level -- 1                       */
		/*********************************************************/
		if (nmPlateau == 2)
		{
			// recursively mark the points with the the plateau
			MarkPlateau(ImageData, PlateauMatrix, r, c, no_of_rows, no_of_cols, 1);
		}
	}

	//////////////////////////////////////////////////

	return nmPlateau;
}
/***************************************************************************
*** Procedure to traverse the plateau
***************************************************************************/
/*
int getRegionalMinimum(Matrix *ImageData, Matrix *PlateauMatrix, int r, int c)
{
	int nmPlateau;
	int nmMask;
	int LabelNo;   // try to get the label number
	//int minimumAltitude;
	//int r, c;

	LabelNo = 0;
	for (r = 0; r < no_of_rows; r++)
		for (c = 0; c < no_of_cols; c++)
	{
		nmMask = Steepest(ImageData, r, c, no_of_rows, no_of_cols);
		nmPlateau = isPlateau(nmMask);
		/*********************************************************/
		/* a pixel on the plateau that has lower outlet(s)       */
		/* mark it as the first level -- 1                       */
		/*********************************************************/
/*
		if (nmPlateau == 2)
			MarkPlateau(ImageData, PlateauMatrix, r, c, no_of_rows, no_of_cols, 1);
	}

	//////////////////////////////////////////////////

	return nmPlateau;
}
*/
/***************************************************************************
*** watershed function
***		rain fall simulation
***
***************************************************************************/
Image * watershed2(Image *inputImage, float threshold, int choice)
{
	
	byte ** pImageMatrix;
	int ** pLabelMatrix;
	int ** pPlateauMatrix;
	//int ** CommonLabelMatrix;
	Image * outImage;
	Image *tmpImage, *tmpImage1;
	Image * plateauImage;
	Image * tmpLabelImage;
	//Image * CommonLabelImage;
	//int nmMask;   /* integer to store the outlet of the pixel */
	  
	int no_of_rows, no_of_cols, no_of_bands;
	int counter = 1;

	int bands = 0;
	int r, c, i;
	int CurrentLabel, tmpLabel;
	
	/****************************
	initialize
	****************************/
	
	no_of_rows =  getNoOfRows_Image(inputImage);
	no_of_cols =  getNoOfCols_Image(inputImage);
	no_of_bands = getNoOfBands_Image(inputImage);

	outImage = duplicate_Image(inputImage);
	outImage = remap_Image(outImage, CVIP_BYTE, 0, 255);
	tmpImage1 = duplicate_Image(inputImage);
	// convert color image to gray
	// xxx lunminance image has weird performance, so create tmpImage1 for input
	//tmpImage = remap_Image(inputImage, CVIP_BYTE, 0, 255);
	if (no_of_bands != 1)
		tmpImage = luminance_Image(tmpImage1);
	else
	{
		tmpImage = duplicate_Image(tmpImage1);
		delete_Image(tmpImage1);
	}
	// create label image
	tmpLabelImage = new_Image(VIP, RGB, 1, no_of_rows, no_of_cols, CVIP_INTEGER, REAL);
	// create common label image from gray image
	//CommonLabelImage = labeling_Image(tmpImage);
	plateauImage = new_Image(VIP, RGB, 1, no_of_rows, no_of_cols, CVIP_INTEGER, REAL);
		
	/*
	** Preprocess
	*/
	pLabelMatrix = getData_Image(tmpLabelImage, 0);
	pImageMatrix = getData_Image(tmpImage, 0);
	// this is only for test purpose
	pImageMatrix[0][0] = 1;
	pImageMatrix[2][1] = 1;

	for(r = 0; r < no_of_rows; r++) 
		for(c = 0; c < no_of_cols; c++)
			pLabelMatrix[r][c] = 0;
	
	pPlateauMatrix = getData_Image(plateauImage, 0);
	//CommonLabelMatrix = getData_Image(CommonLabelImage, 0);

	TraversePlateau(pImageMatrix, pPlateauMatrix, no_of_rows, no_of_cols);

	CurrentLabel = 1;
	tmpLabel = 1;
	for(r = 0; r < no_of_rows; r++) 
		for(c = 0; c < no_of_cols; c++)
	{
		counter = 1;
		tmpLabel = Rainfall(tmpImage, pLabelMatrix, pPlateauMatrix, CurrentLabel, r, c, counter);
		if (tmpLabel == CurrentLabel)
			CurrentLabel ++;
	}

	Merge(tmpImage, tmpLabelImage, threshold);
	//tmpLabelImage = MorphClose(tmpLabelImage, 1, 3, 6, 6);
	//pLabelMatrix = getData_Image(tmpLabelImage, 0);

	// Mark the border in the original image (cloned)
	for (i = 0; i < no_of_bands; i++)
	{
		pImageMatrix = getData_Image(outImage, i);
		for(r = 0; r < no_of_rows - 1; r++) 
			for(c = 0; c < no_of_cols - 1; c++)
		{
			if ((pLabelMatrix[r][c] !=pLabelMatrix[r+1][c]) || (pLabelMatrix[r][c] !=pLabelMatrix[r][c+1]) || (pLabelMatrix[r][c] !=pLabelMatrix[r+1][c+1]))
				pImageMatrix[r][c] = 255;
		}
	}
	delete_Image(outImage);
	delete_Image(plateauImage);
	delete_Image(tmpLabelImage);
	//delete_Image(CommonLabelImage);
	return tmpImage;
	
	//return outImage;
}
/***************************************************************************
*** watershed function
***		rain fall simulation
***
***************************************************************************/
Image * watershed3(Image *inputImage, float threshold, int choice)
{
	
	byte ** pImageMatrix;
	int ** pLabelMatrix;
	int ** pPlateauMatrix;
	//int ** CommonLabelMatrix;
	Image * outImage;
	Image *tmpImage, *tmpImage1;
	Image * plateauImage;
	Image * tmpLabelImage;
	//Image * CommonLabelImage;
	//int nmMask;   /* integer to store the outlet of the pixel */
	  
	int no_of_rows, no_of_cols, no_of_bands;
	int counter = 1;

	int bands = 0;
	int r, c, i;
	int CurrentLabel, tmpLabel;
	
	/****************************
	initialize
	****************************/
	
	no_of_rows =  getNoOfRows_Image(inputImage);
	no_of_cols =  getNoOfCols_Image(inputImage);
	no_of_bands = getNoOfBands_Image(inputImage);

	outImage = duplicate_Image(inputImage);
	outImage = remap_Image(outImage, CVIP_BYTE, 0, 255);
	tmpImage1 = duplicate_Image(inputImage);
	// convert color image to gray
	// xxx lunminance image has weird performance, so create tmpImage1 for input
	//tmpImage = remap_Image(inputImage, CVIP_BYTE, 0, 255);
	if (no_of_bands != 1)
		tmpImage = luminance_Image(tmpImage1);
	else
	{
		tmpImage = duplicate_Image(tmpImage1);
		delete_Image(tmpImage1);
	}
	// create label image
	tmpLabelImage = new_Image(VIP, RGB, 1, no_of_rows, no_of_cols, CVIP_INTEGER, REAL);
	// create common label image from gray image
	//CommonLabelImage = labeling_Image(tmpImage);
	plateauImage = new_Image(VIP, RGB, 1, no_of_rows, no_of_cols, CVIP_INTEGER, REAL);
		
	/*
	** Preprocess
	*/
	pLabelMatrix = getData_Image(tmpLabelImage, 0);
	pImageMatrix = getData_Image(tmpImage, 0);
	// this is only for test purpose
	pImageMatrix[0][0] = 1;
	pImageMatrix[2][1] = 1;

	for(r = 0; r < no_of_rows; r++) 
		for(c = 0; c < no_of_cols; c++)
			pLabelMatrix[r][c] = 0;
	
	pPlateauMatrix = getData_Image(plateauImage, 0);
	//CommonLabelMatrix = getData_Image(CommonLabelImage, 0);

	TraversePlateau(pImageMatrix, pPlateauMatrix, no_of_rows, no_of_cols);

	CurrentLabel = 1;
	tmpLabel = 1;
	for(r = 0; r < no_of_rows; r++) 
		for(c = 0; c < no_of_cols; c++)
	{
		counter = 1;
		tmpLabel = Rainfall(tmpImage, pLabelMatrix, pPlateauMatrix, CurrentLabel, r, c, counter);
		if (tmpLabel == CurrentLabel)
			CurrentLabel ++;
	}

	Merge(tmpImage, tmpLabelImage, threshold);
	//tmpLabelImage = MorphClose(tmpLabelImage, 1, 3, 6, 6);
	//pLabelMatrix = getData_Image(tmpLabelImage, 0);

	// Mark the border in the original image (cloned)
	for (i = 0; i < no_of_bands; i++)
	{
		pImageMatrix = getData_Image(outImage, i);
		for(r = 0; r < no_of_rows - 1; r++) 
			for(c = 0; c < no_of_cols - 1; c++)
		{
			if ((pLabelMatrix[r][c] !=pLabelMatrix[r+1][c]) || (pLabelMatrix[r][c] !=pLabelMatrix[r][c+1]) || (pLabelMatrix[r][c] !=pLabelMatrix[r+1][c+1]))
				pImageMatrix[r][c] = 255;
		}
	}
	//delete_Image(outImage);
	delete_Image(tmpImage);
	delete_Image(plateauImage);
	delete_Image(tmpLabelImage);
	//delete_Image(CommonLabelImage);
	//return tmpImage;
	
	return outImage;
}
/***************************************************************************
* Function Description : Preorder scan Rainfall simulation
***************************************************************************/
int Rainfall(Image * pGrayImage, int ** pLabelMatrix, int ** pPlateauMatrix, int CurrentLabel, int r, int c, int counter)
{
	int tempLabel;
	int no_of_rows, no_of_cols;
	byte ** pImageMatrix;
	int nmMask, findOutlet, i;

	no_of_rows =  getNoOfRows_Image(pGrayImage);
	no_of_cols =  getNoOfCols_Image(pGrayImage);

	pImageMatrix = getData_Image(pGrayImage, 0);

	nmMask = Steepest(pImageMatrix, r, c, no_of_rows, no_of_cols);
	findOutlet = 0;
	i = 0;


	counter++;
	///////////////////////////////////////////////////////////////////
	// if point do not belong to plateau or point has lower outlets
	///////////////////////////////////////////////////////////////////
    //if ((isPlateau(nmMask) == 0) || (isPlateau(nmMask) == 2))
	//{
		// this loop guarrantee that only first outlet will be poped out
		// not necessary because regional minimum can be plateau
		//while ((findOutlet == 0) && (i < 8))
		//{
		//	if (PositionIsOutlet(nmMask, i))
		//		findOutlet = 1;
		//	else
		//		i = i + 1;
		//}
		// if position has no outlet (regional minimum) and is not labeled, give current label
		//if ((i == 8) && (pLabelMatrix[r][c] == 0))
		tempLabel = CurrentLabel;

		pLabelMatrix[r][c] = -1;

		if(counter > 500)
		{
			pLabelMatrix[r][c] = tempLabel;
			return tempLabel;
		}
		// if Labeled then route will be labeled as that label, else recursive
		if (PositionIsOutlet(nmMask, 0))
		{
			if (pLabelMatrix[r-1][c-1] == 0)
				tempLabel = Rainfall(pGrayImage, pLabelMatrix, pPlateauMatrix, CurrentLabel, r-1, c-1, counter);
			else if (pLabelMatrix[r-1][c-1] > 0)
				tempLabel = pLabelMatrix[r-1][c-1];
		}

		if (PositionIsOutlet(nmMask, 1))
		{
			if (pLabelMatrix[r-1][c] == 0)
				tempLabel = Rainfall(pGrayImage, pLabelMatrix, pPlateauMatrix, CurrentLabel, r-1, c, counter);
			else if (pLabelMatrix[r-1][c] > 0)
				tempLabel = pLabelMatrix[r-1][c];
		}

		if (PositionIsOutlet(nmMask, 2))
		{
			if (pLabelMatrix[r-1][c+1] == 0)
				tempLabel = Rainfall(pGrayImage, pLabelMatrix, pPlateauMatrix, CurrentLabel, r-1, c+1, counter);
			else if (pLabelMatrix[r-1][c+1] > 0)
				tempLabel = pLabelMatrix[r-1][c+1];
		}

		if (PositionIsOutlet(nmMask, 3))
		{
			if (pLabelMatrix[r][c+1] == 0)
				tempLabel = Rainfall(pGrayImage, pLabelMatrix, pPlateauMatrix, CurrentLabel, r, c+1, counter);
			else if (pLabelMatrix[r][c+1] > 0)
				tempLabel = pLabelMatrix[r][c+1];
		}

		if (PositionIsOutlet(nmMask, 4))
		{
			if (pLabelMatrix[r+1][c+1] == 0)
				tempLabel = Rainfall(pGrayImage, pLabelMatrix, pPlateauMatrix, CurrentLabel, r+1, c+1, counter);
			else if (pLabelMatrix[r+1][c+1] > 0)
				tempLabel = pLabelMatrix[r+1][c+1];
		}

		if (PositionIsOutlet(nmMask, 5))
		{
			if (pLabelMatrix[r+1][c] == 0)
				tempLabel = Rainfall(pGrayImage, pLabelMatrix, pPlateauMatrix, CurrentLabel, r+1, c, counter);
			else if (pLabelMatrix[r+1][c] > 0)
				tempLabel = pLabelMatrix[r+1][c];
		}

		if (PositionIsOutlet(nmMask, 6))
		{
			if (pLabelMatrix[r+1][c-1] == 0)
				tempLabel = Rainfall(pGrayImage, pLabelMatrix, pPlateauMatrix, CurrentLabel, r+1, c-1, counter);
			else if (pLabelMatrix[r+1][c-1] > 0)
				tempLabel = pLabelMatrix[r+1][c-1];
		}

		if (PositionIsOutlet(nmMask, 7))
		{
			if (pLabelMatrix[r][c-1] == 0)
				tempLabel = Rainfall(pGrayImage, pLabelMatrix, pPlateauMatrix, CurrentLabel, r, c-1, counter);
			else if (pLabelMatrix[r][c-1] > 0)
				tempLabel = pLabelMatrix[r][c-1];
		}
	//}
	/////////////////////////////////////////////////////////////////////
	// else if point has outlets with same altitude
	/////////////////////////////////////////////////////////////////////
	//else if (isPlateau(nmMask) == 3)
	//{

	//}

	pLabelMatrix[r][c] = tempLabel;
	return tempLabel;
}
/***************************************************************************
** Function Name : 
***************************************************************************/
int Merge(Image * pGrayImage, Image * labelImage, float threshold)
{
	byte ** pImageMatrix;
	int ** pLabelMatrix;
	Image * pCruiseImage;
	byte ** pCruiseMatrix;
	int ObjectHistogram[256];
	int i, r, c;
	int no_of_rows, no_of_cols;
	byte AverageColor;
	int TotalObjects;
	int MaxObjectColor;
	int MaxObjects;
	int ThresholdObjects;
	long tmpCount;
	byte upperlimit, lowerlimit;

	for (i = 0; i < 256; i ++)
		ObjectHistogram[i] = 0;
	TotalObjects = 0;
	MaxObjectColor = 0;
	MaxObjects = 0;
	upperlimit = 0;
	lowerlimit = 0;

	no_of_rows =  getNoOfRows_Image(pGrayImage);
	no_of_cols =  getNoOfCols_Image(pGrayImage);

	pCruiseImage = new_Image(pGrayImage->image_format, pGrayImage->color_space, 1, no_of_rows, no_of_cols, CVIP_BYTE, REAL);

	pCruiseMatrix = getData_Image(pCruiseImage, 0);
	pImageMatrix = getData_Image(pGrayImage, 0);
	pLabelMatrix = getData_Image(labelImage, 0);
	
	for (r = 0; r < no_of_rows - 1; r++) 
		for (c = 0; c < no_of_cols - 1; c++)
	{
		if (pCruiseMatrix[r][c] == 0)
		{
			AverageColor = GetAverageColor(pGrayImage, pLabelMatrix, pCruiseMatrix, r, c, 0, 0.0);
			ObjectHistogram[AverageColor] ++;
			TotalObjects ++;
		}
	}

	// calculate the location and max number of the object
	for (i = 0; i < 255; i++)
	{
		if (ObjectHistogram[i] > MaxObjects)
		{
			MaxObjects = ObjectHistogram[i];
			MaxObjectColor = i;
		}
	}
	upperlimit = MaxObjectColor;
	lowerlimit = MaxObjectColor;
	ThresholdObjects = MaxObjects;
	if (threshold == 0)
		threshold = 0.65;
	while (ThresholdObjects < threshold * TotalObjects)
	{
		upperlimit ++;
		lowerlimit --;
		ThresholdObjects = ThresholdObjects + ObjectHistogram[upperlimit] + ObjectHistogram[lowerlimit];
	}

	for (r = 0; r < no_of_rows - 1; r++) 
		for (c = 0; c < no_of_cols - 1; c++)
	{
		pCruiseMatrix[r][c] = 0;
	}

	for (r = 0; r < no_of_rows - 1; r++) 
		for (c = 0; c < no_of_cols - 1; c++)
	{
		AverageColor = GetAverageColor(pGrayImage, pLabelMatrix, pCruiseMatrix, r, c, 0, 0.0);
		if (AverageColor >= lowerlimit)// && (AverageColor <= upperlimit))
			pLabelMatrix[r][c] = 1;
		else
			pLabelMatrix[r][c] = 0;
	}
/*
	// merge the object that is less than 200
	for (r = 0; r < no_of_rows - 1; r++) 
		for (c = 0; c < no_of_cols - 1; c++)
	{
		pCruiseMatrix[r][c] = 0;
	}


	for (r = 0; r < no_of_rows - 1; r++) 
		for (c = 0; c < no_of_cols - 1; c++)
	{
		if (pCruiseMatrix[r][c] == 0)
			tmpCount = GetObjectCount(pGrayImage, pLabelMatrix, pCruiseMatrix, r, c, 0, 0);
		/*
		if (tmpCount <= 200)
		{
			if (pLabelMatrix[r][c] == 0)
				pLabelMatrix[r][c] = 1;
			else
			if (pLabelMatrix[r][c] == 1)
				pLabelMatrix[r][c] = 0;
		}

	}
*/
	delete_Image(pCruiseImage);
	//free(ObjectHistogram);
	pImageMatrix = NULL;
	pLabelMatrix = NULL;
	pCruiseMatrix = NULL;
	return 0;
}
/***************************************************************************
** Function Name : 
***************************************************************************/
int MergeSegment(Image * pGrayImage, Image * labelImage, float threshold)
{
	byte ** pImageMatrix;
	int ** pLabelMatrix;
	Image * pCruiseImage;
	byte ** pCruiseMatrix;
	int ObjectHistogram[256];
	int i, r, c;
	int no_of_rows, no_of_cols;
	byte AverageColor;
	int TotalObjects;
	int MaxObjectColor;
	int MaxObjects;
	int ThresholdObjects;
	long tmpCount;
	byte upperlimit, lowerlimit;

	for (i = 0; i < 256; i ++)
		ObjectHistogram[i] = 0;
	TotalObjects = 0;
	MaxObjectColor = 0;
	MaxObjects = 0;
	upperlimit = 0;
	lowerlimit = 0;

	no_of_rows =  getNoOfRows_Image(pGrayImage);
	no_of_cols =  getNoOfCols_Image(pGrayImage);

	pCruiseImage = new_Image(pGrayImage->image_format, pGrayImage->color_space, 1, no_of_rows, no_of_cols, CVIP_BYTE, REAL);

	pCruiseMatrix = getData_Image(pCruiseImage, 0);
	pImageMatrix = getData_Image(pGrayImage, 0);
	pLabelMatrix = getData_Image(labelImage, 0);
	
	for (r = 0; r < no_of_rows - 1; r++) 
		for (c = 0; c < no_of_cols - 1; c++)
	{
		if (pCruiseMatrix[r][c] == 0)
		{
			AverageColor = GetAverageColor(pGrayImage, pLabelMatrix, pCruiseMatrix, r, c, 0, 0.0);
			ObjectHistogram[AverageColor] ++;
			TotalObjects ++;
		}
	}

	// calculate the location and max number of the object
	for (i = 0; i < 255; i++)
	{
		if (ObjectHistogram[i] > MaxObjects)
		{
			MaxObjects = ObjectHistogram[i];
			MaxObjectColor = i;
		}
	}
	upperlimit = MaxObjectColor;
	lowerlimit = MaxObjectColor;
	ThresholdObjects = MaxObjects;

	while (ThresholdObjects < 0.65 * TotalObjects)
	{
		upperlimit ++;
		lowerlimit --;
		ThresholdObjects = ThresholdObjects + ObjectHistogram[upperlimit] + ObjectHistogram[lowerlimit];
	}

	for (r = 0; r < no_of_rows - 1; r++) 
		for (c = 0; c < no_of_cols - 1; c++)
	{
		pCruiseMatrix[r][c] = 0;
	}

	for (r = 0; r < no_of_rows - 1; r++) 
		for (c = 0; c < no_of_cols - 1; c++)
	{
		AverageColor = GetAverageColor(pGrayImage, pLabelMatrix, pCruiseMatrix, r, c, 0, 0.0);
		if (AverageColor >= lowerlimit)// && (AverageColor <= upperlimit))
			pLabelMatrix[r][c] = 1;
		else
			pLabelMatrix[r][c] = 0;
	}
/*
	for (r = 0; r < no_of_rows - 1; r++) 
		for (c = 0; c < no_of_cols - 1; c++)
	{
		AverageColor = GetAverageColor(pGrayImage, pLabelMatrix, pCruiseMatrix, r, c, 0, 0.0);
		pImageMatrix[r][c] = AverageColor;
		if (AverageColor >= lowerlimit)// && (AverageColor <= upperlimit))
			pLabelMatrix[r][c] = 1;
		else
			pLabelMatrix[r][c] = 0;

	}
		*/
/*
	// merge the object that is less than 200
	for (r = 0; r < no_of_rows - 1; r++) 
		for (c = 0; c < no_of_cols - 1; c++)
	{
		pCruiseMatrix[r][c] = 0;
	}


	for (r = 0; r < no_of_rows - 1; r++) 
		for (c = 0; c < no_of_cols - 1; c++)
	{
		if (pCruiseMatrix[r][c] == 0)
			tmpCount = GetObjectCount(pGrayImage, pLabelMatrix, pCruiseMatrix, r, c, 0, 0);
		/*
		if (tmpCount <= 200)
		{
			if (pLabelMatrix[r][c] == 0)
				pLabelMatrix[r][c] = 1;
			else
			if (pLabelMatrix[r][c] == 1)
				pLabelMatrix[r][c] = 0;
		}

	}
*/
	delete_Image(pCruiseImage);
	//free(ObjectHistogram);
	pImageMatrix = NULL;
	pLabelMatrix = NULL;
	pCruiseMatrix = NULL;
	return 0;
}
/***************************************************************************
***************************************************************************/
byte GetAverageColor(Image * pGrayImage, int ** pLabelMatrix, byte ** pCruiseMatrix, int r, int c, int no_of_pixels, double tmpColor)
{
	double tmpColor1;
	byte ** pImageMatrix;
	int no_of_rows, no_of_cols;

	no_of_rows =  getNoOfRows_Image(pGrayImage);
	no_of_cols =  getNoOfCols_Image(pGrayImage);
	pImageMatrix = getData_Image(pGrayImage, 0);

	pCruiseMatrix[r][c] = 1;
	tmpColor1 = (tmpColor * no_of_pixels + pImageMatrix[r][c]) / (no_of_pixels + 1);
	if ((r > 0) && (c > 0))
		if ((pLabelMatrix[r][c] == pLabelMatrix[r-1][c-1]) && (pCruiseMatrix[r-1][c-1] == 0))
			tmpColor1 = GetAverageColor(pGrayImage, pLabelMatrix, pCruiseMatrix, r-1, c-1, no_of_pixels + 1, tmpColor1);
	if (r > 0)
		if ((pLabelMatrix[r][c] == pLabelMatrix[r-1][c]) && (pCruiseMatrix[r-1][c] == 0))
			tmpColor1 = GetAverageColor(pGrayImage, pLabelMatrix, pCruiseMatrix, r-1, c, no_of_pixels + 1, tmpColor1);
	if ((r > 0) && (c < no_of_cols - 1))
		if ((pLabelMatrix[r][c] == pLabelMatrix[r-1][c+1]) && (pCruiseMatrix[r-1][c+1] == 0))
			tmpColor1 = GetAverageColor(pGrayImage, pLabelMatrix, pCruiseMatrix, r-1, c+1, no_of_pixels + 1, tmpColor1);
	if (c < no_of_cols - 1)
		if ((pLabelMatrix[r][c] == pLabelMatrix[r][c+1]) && (pCruiseMatrix[r][c+1] == 0))
			tmpColor1 = GetAverageColor(pGrayImage, pLabelMatrix, pCruiseMatrix, r, c+1, no_of_pixels + 1, tmpColor1);
	if ((r < no_of_rows - 1) && (c < no_of_cols - 1))
		if ((pLabelMatrix[r][c] == pLabelMatrix[r+1][c+1]) && (pCruiseMatrix[r+1][c+1] == 0))
			tmpColor1 = GetAverageColor(pGrayImage, pLabelMatrix, pCruiseMatrix, r+1, c+1, no_of_pixels + 1, tmpColor1);
	if (r < no_of_rows - 1)
		if ((pLabelMatrix[r][c] == pLabelMatrix[r+1][c]) && (pCruiseMatrix[r+1][c] == 0))
			tmpColor1 = GetAverageColor(pGrayImage, pLabelMatrix, pCruiseMatrix, r+1, c, no_of_pixels + 1, tmpColor1);
	if ((r < no_of_rows - 1) && (c > 0))
		if ((pLabelMatrix[r][c] == pLabelMatrix[r+1][c-1]) && (pCruiseMatrix[r+1][c-1] == 0))
			tmpColor1 = GetAverageColor(pGrayImage, pLabelMatrix, pCruiseMatrix, r+1, c-1, no_of_pixels + 1, tmpColor1);
	if (c > 0)
		if ((pLabelMatrix[r][c] == pLabelMatrix[r][c-1]) && (pCruiseMatrix[r][c-1] == 0))
			tmpColor1 = GetAverageColor(pGrayImage, pLabelMatrix, pCruiseMatrix, r, c-1, no_of_pixels + 1, tmpColor1);
	pImageMatrix[r][c] = (byte)tmpColor1;

	return (byte)tmpColor1;
}
/***************************************************************************
***************************************************************************/
long GetObjectCount(Image * pGrayImage, int ** pLabelMatrix, byte ** pCruiseMatrix, int r, int c, int no_of_pixels, long tmpCount1)
{
	long tmpCount;
	byte ** pImageMatrix;
	int no_of_rows, no_of_cols;

	no_of_rows =  getNoOfRows_Image(pGrayImage);
	no_of_cols =  getNoOfCols_Image(pGrayImage);
	pImageMatrix = getData_Image(pGrayImage, 0);

	//pCruiseMatrix[r][c] = 1;
	tmpCount = tmpCount1 + 1;
	if (tmpCount < 220)
	{
		/***********************************************************/
		if ((r > 0) && (c > 0))
		if ((pLabelMatrix[r][c] == pLabelMatrix[r-1][c-1]) && (pCruiseMatrix[r-1][c-1] == 0))
			tmpCount = GetObjectCount(pGrayImage, pLabelMatrix, pCruiseMatrix, r-1, c-1, no_of_pixels + 1, tmpCount);
		/***********************************************************/
		if (r > 0)
		if ((pLabelMatrix[r][c] == pLabelMatrix[r-1][c]) && (pCruiseMatrix[r-1][c] == 0))
			tmpCount = GetObjectCount(pGrayImage, pLabelMatrix, pCruiseMatrix, r-1, c, no_of_pixels + 1, tmpCount);
		/***********************************************************/
		if ((r > 0) && (c < no_of_cols - 1))
		if ((pLabelMatrix[r][c] == pLabelMatrix[r-1][c+1]) && (pCruiseMatrix[r-1][c+1] == 0))
			tmpCount = GetObjectCount(pGrayImage, pLabelMatrix, pCruiseMatrix, r-1, c+1, no_of_pixels + 1, tmpCount);
		/***********************************************************/
		if (c < no_of_cols - 1)
		if ((pLabelMatrix[r][c] == pLabelMatrix[r][c+1]) && (pCruiseMatrix[r][c+1] == 0))
			tmpCount = GetObjectCount(pGrayImage, pLabelMatrix, pCruiseMatrix, r, c+1, no_of_pixels + 1, tmpCount);
		/***********************************************************/
		if ((r < no_of_rows - 1) && (c < no_of_cols - 1))
		if ((pLabelMatrix[r][c] == pLabelMatrix[r+1][c+1]) && (pCruiseMatrix[r+1][c+1] == 0))
			tmpCount = GetObjectCount(pGrayImage, pLabelMatrix, pCruiseMatrix, r+1, c+1, no_of_pixels + 1, tmpCount);
		/***********************************************************/
		if (r < no_of_rows - 1)
		if ((pLabelMatrix[r][c] == pLabelMatrix[r+1][c]) && (pCruiseMatrix[r+1][c] == 0))
			tmpCount = GetObjectCount(pGrayImage, pLabelMatrix, pCruiseMatrix, r+1, c, no_of_pixels + 1, tmpCount);
		/***********************************************************/
		if ((r < no_of_rows - 1) && (c > 0))
		if ((pLabelMatrix[r][c] == pLabelMatrix[r+1][c-1]) && (pCruiseMatrix[r+1][c-1] == 0))
			tmpCount = GetObjectCount(pGrayImage, pLabelMatrix, pCruiseMatrix, r+1, c-1, no_of_pixels + 1, tmpCount);
		/***********************************************************/
		if (c > 0)
		if ((pLabelMatrix[r][c] == pLabelMatrix[r][c-1]) && (pCruiseMatrix[r][c-1] == 0))
			tmpCount = GetObjectCount(pGrayImage, pLabelMatrix, pCruiseMatrix, r, c-1, no_of_pixels + 1, tmpCount);
	}

	if (tmpCount <= 200)
	{
		if (pLabelMatrix[r][c] == 0)
			pLabelMatrix[r][c] = 1;
		else
		if (pLabelMatrix[r][c] == 1)
			pLabelMatrix[r][c] = 0;
	}
	return tmpCount;
}
/***************************************************************************
** under construction
***************************************************************************/
/*
int GetMajorNeighborLabel(Image * pGrayImage, int ** pLabelMatrix, byte ** pCruiseMatrix, int r, int c, int no_of_pixels, double tmpColor)
{
	byte tmpColor[8];
	byte ** pImageMatrix;
	int no_of_rows, no_of_cols;

	no_of_rows =  getNoOfRows_Image(pGrayImage);
	no_of_cols =  getNoOfCols_Image(pGrayImage);
	pImageMatrix = getData_Image(pGrayImage, 0);

	pCruiseMatrix[r][c] = 1;
	tmpCount ++;
	if ((r > 0) && (c > 0))
		if ((pLabelMatrix[r][c] == pLabelMatrix[r-1][c-1]) && (pCruiseMatrix[r-1][c-1] == 0))
			tmpColor1 = GetObjectCount(pGrayImage, pLabelMatrix, pCruiseMatrix, r-1, c-1, no_of_pixels + 1, tmpColor1);
	if (r > 0)
		if ((pLabelMatrix[r][c] == pLabelMatrix[r-1][c]) && (pCruiseMatrix[r-1][c] == 0))
			tmpColor1 = GetObjectCount(pGrayImage, pLabelMatrix, pCruiseMatrix, r-1, c, no_of_pixels + 1, tmpColor1);
	if ((r > 0) && (c < no_of_cols - 1))
		if ((pLabelMatrix[r][c] == pLabelMatrix[r-1][c+1]) && (pCruiseMatrix[r-1][c+1] == 0))
			tmpColor1 = GetObjectCount(pGrayImage, pLabelMatrix, pCruiseMatrix, r-1, c+1, no_of_pixels + 1, tmpColor1);
	if (c < no_of_cols - 1)
		if ((pLabelMatrix[r][c] == pLabelMatrix[r][c+1]) && (pCruiseMatrix[r][c+1] == 0))
			tmpColor1 = GetObjectCount(pGrayImage, pLabelMatrix, pCruiseMatrix, r, c+1, no_of_pixels + 1, tmpColor1);
	if ((r < no_of_rows - 1) && (c < no_of_cols - 1))
		if ((pLabelMatrix[r][c] == pLabelMatrix[r+1][c+1]) && (pCruiseMatrix[r+1][c+1] == 0))
			tmpColor1 = GetObjectCount(pGrayImage, pLabelMatrix, pCruiseMatrix, r+1, c+1, no_of_pixels + 1, tmpColor1);
	if (r < no_of_rows - 1)
		if ((pLabelMatrix[r][c] == pLabelMatrix[r+1][c]) && (pCruiseMatrix[r+1][c] == 0))
			tmpColor1 = GetObjectCount(pGrayImage, pLabelMatrix, pCruiseMatrix, r+1, c, no_of_pixels + 1, tmpColor1);
	if ((r < no_of_rows - 1) && (c > 0))
		if ((pLabelMatrix[r][c] == pLabelMatrix[r+1][c-1]) && (pCruiseMatrix[r+1][c-1] == 0))
			tmpColor1 = GetObjectCount(pGrayImage, pLabelMatrix, pCruiseMatrix, r+1, c-1, no_of_pixels + 1, tmpColor1);
	if (c > 0)
		if ((pLabelMatrix[r][c] == pLabelMatrix[r][c-1]) && (pCruiseMatrix[r][c-1] == 0))
			tmpColor1 = GetObjectCount(pGrayImage, pLabelMatrix, pCruiseMatrix, r, c-1, no_of_pixels + 1, tmpColor1);

	return tmpCount;
}
*/
/***************************************************************************
*** End of watershed.c
***************************************************************************/