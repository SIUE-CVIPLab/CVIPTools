/***************************************************************************
* ======================================================================
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* ======================================================================
*
*             File Name: Dice.c
*           Description: Finds the Jaccard Value of two images.
*         Related Files:
*   Initial Coding Date: September 22nd, 2020
*           Portability: Standard (ANSI) C
*             Credit(s): Charles Stacey
*                        Southern Illinois University @ Edwardsville
*
** Copyright (C) 2020 SIUE - by Scott Umbaugh.
**
** Permission to use, copy, modify, and distribute this software and its
** documentation for any purpose and without fee is hereby granted, provided
** that the above copyright notice appear in all copies and that both that
** copyright notice and this permission notice appear in supporting
** documentation.  This software is provided "as is" without express or
** implied warranty.
****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "CVIPtoolkit.h"
#include "CVIPconvert.h"
#include "CVIPdef.h"
#include "CVIPimage.h"
#include "CVIParithlogic.h"

double* jaccard_index(Image* pIdealImage, Image* pTestImage)
{
	Image* andImage, *orImage;
	byte** pIdealData, ** pTestData, ** andData, ** orData;
	double* fRatio;
	int nBand, nBands, nBandsIdeal, nBandsTest;
	int nRow, nRows, nCol, nCols;
	float idealArea, testArea, intersectArea, andArea, orArea;
	int binary, idealIndex = 0, testIndex = 0;
	int valuesIdeal[2], valuesTest[2];

	//Determine Bands:
	nBands = nBandsIdeal = getNoOfBands_Image(pIdealImage);
	nBandsTest = getNoOfBands_Image(pTestImage);
	if (nBandsTest != nBandsIdeal)
	{
		int i;
		Image* tmp[3];
		if (nBandsTest == 1)
		{
			for (i = 0; i < 3; i++)
				tmp[i] = pTestImage;
			pTestImage = assemble_bands(tmp, 3);
		}
		else
		{
			nBands = nBandsTest;
			for (i = 0; i < 3; i++)
				tmp[i] = pIdealImage;
			pIdealImage = assemble_bands(tmp, 3);
		}
	}

	if (getDataType_Image(pIdealImage) != CVIP_BYTE)
		pIdealImage = remap_Image(pIdealImage, CVIP_BYTE, 0, 255);

	if (getDataType_Image(pTestImage) != CVIP_BYTE)
		pTestImage = remap_Image(pTestImage, CVIP_BYTE, 0, 255);

	fRatio = malloc(nBands * sizeof(double));

	nRows = getNoOfRows_Image(pIdealImage);
	nCols = getNoOfCols_Image(pIdealImage);

	//Check if the image is binary
	binary = 1;
	
	for (nBand = 0; nBand < nBands; nBand++)
	{
		pIdealData = getData_Image(pIdealImage, nBand);
		pTestData = getData_Image(pTestImage, nBand);

		//Get First Values
		valuesIdeal[0] = (int)pIdealData[0][0];
		valuesTest[0] = (int)pTestData[0][0];
		for (nRow = 1; nRow < nRows; nRow++)
		{
			for (nCol = 1; nCol < nCols; nCol++)
			{
				//Check Ideal
				//Second Value Found
				if (pIdealData[nRow][nCol] != valuesIdeal[0] && idealIndex == 0)
				{
					valuesIdeal[1] = pIdealData[nRow][nCol];
					idealIndex = 1;
				}
				else if (pIdealData[nRow][nCol] != valuesIdeal[0] && pIdealData[nRow][nCol] != valuesIdeal[1] && idealIndex == 1)
				{
					binary = 0;
					goto notBinary;
				}
				//Check Ideal
				//Second Value Found
				if (pTestData[nRow][nCol] != valuesIdeal[0] && testIndex == 0)
				{
					valuesIdeal[1] = pTestData[nRow][nCol];
					testIndex = 1;
				}
				else if (pTestData[nRow][nCol] != valuesIdeal[0] && pTestData[nRow][nCol] != valuesIdeal[1] && testIndex == 1)
				{
					binary = 0;
					goto notBinary;
				}
			}
		}
	}

	notBinary:

	if (binary == 1)
	{
		for (nBand = 0; nBand < nBands; nBand++)
		{
			pIdealData = getData_Image(pIdealImage, nBand);
			pTestData = getData_Image(pTestImage, nBand);

			fRatio[nBand] = 0.0;
			idealArea = 0;
			testArea = 0;
			intersectArea = 0;

			for (nRow = 0; nRow < nRows; nRow++)
			{
				for (nCol = 0; nCol < nCols; nCol++)
				{
					if (pIdealData[nRow][nCol] != 0)
						idealArea++;
					if (pTestData[nRow][nCol] != 0)
						testArea++;
					if (pIdealData[nRow][nCol] != 0 && pTestData[nRow][nCol] != 0)
						intersectArea++;
				}
			}
			if (idealArea != 0)
				fRatio[nBand] = intersectArea / (idealArea + testArea - intersectArea);
		}
	}
	else
	{
		andImage = and_Image(duplicate_Image(pIdealImage), duplicate_Image(pTestImage));
		orImage = or_Image(duplicate_Image(pIdealImage), duplicate_Image(pTestImage));
		for (nBand = 0; nBand < nBands; nBand++)
		{
			andData = getData_Image(andImage, nBand);
			orData = getData_Image(orImage, nBand);

			fRatio[nBand] = 0.0;
			andArea = 0;
			orArea = 0;

			for (nRow = 0; nRow < nRows; nRow++)
			{
				for (nCol = 0; nCol < nCols; nCol++)
				{
					andArea += andData[nRow][nCol];
					orArea += orData[nRow][nCol];
				}
			}
			fRatio[nBand] = andArea / orArea;
		}
		delete_Image(andImage);
		delete_Image(orImage);
	}
	return fRatio;
}