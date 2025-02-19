/******************************************************************************
    ======================================================================
    Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
    ======================================================================

                   Name: xor_error.c

          Expanded Name: Computing comparison ratio of two images by XOR  

             Parameters: A pointer to an ideal image and a pointer to a test 
			             image

                Returns: a pointer to double values

            Description: This file contains a routine that computes the  
                         XOR error. The error is computed in each band.

            Diagnostics: None

    Initial Coding Date: 11/04/11
             References: None

              Author(s): Maryam Amini

 
              Southern Illinois University Edwardsville


*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "CVIPtoolkit.h"
#include "CVIPconvert.h"
#include "CVIPdef.h"
#include "CVIPimage.h"

double *xor_error(Image *pIdealImage, Image *pTestImage)
{
	byte **pIdealData, **pXORData;
	double *fRatio;
	int nBand, nBands, nBandsIdeal, nBandsTest;
	int nRow, nRows, nCol, nCols;
	unsigned int nIdealArea[3], nXORArea[3];
	Image *pXORImage = NULL;

	nBands = nBandsIdeal = getNoOfBands_Image(pIdealImage);
	nBandsTest = getNoOfBands_Image(pTestImage);
	if(nBandsTest != nBandsIdeal)
	{
		int i;
		Image *tmp[3];
		if(nBandsTest == 1)
		{
			for(i=0; i<3; i++)
				tmp[i] = pTestImage;
			pTestImage = assemble_bands(tmp, 3);
		}
		else
		{
			nBands = nBandsTest;
			for(i=0; i<3; i++)
				tmp[i] = pIdealImage;
			pIdealImage = assemble_bands(tmp, 3);
		}
	}

	if(getDataType_Image(pIdealImage) != CVIP_BYTE)
		pIdealImage = remap_Image(pIdealImage, CVIP_BYTE, 0, 255);

	if(getDataType_Image(pTestImage) != CVIP_BYTE)
		pTestImage = remap_Image(pTestImage, CVIP_BYTE, 0, 255);

	pXORImage = xor_Image(duplicate_Image(pIdealImage), pTestImage);

	fRatio = malloc(nBands * sizeof(double));

	nRows = getNoOfRows_Image(pIdealImage);
	nCols = getNoOfCols_Image(pIdealImage);

	for(nBand = 0; nBand < nBands; nBand++)
	{
		pIdealData = getData_Image(pIdealImage, nBand);
		pXORData = getData_Image(pXORImage, nBand);

		fRatio[nBand] = 0.0;
		nIdealArea[nBand] = 0;
		nXORArea[nBand] = 0;

		for(nRow = 0; nRow < nRows; nRow++)
		{
			for(nCol = 0; nCol < nCols; nCol++)
			{
				if(pIdealData[nRow][nCol] != 0)
					nIdealArea[nBand]++;

				if(pXORData[nRow][nCol] != 0)
					nXORArea[nBand]++;
			}
		}

		if(nIdealArea[nBand] != 0)
			fRatio[nBand] = (float)nXORArea[nBand] / (float)nIdealArea[nBand];
	}
	delete_Image(pXORImage);
	return fRatio;
}
