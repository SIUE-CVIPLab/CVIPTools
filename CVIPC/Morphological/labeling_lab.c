/***************************************************************************
* =========================================================================
*
*   Computer Vision and Image Processing Lab - Dr. Scott Umbaugh SIUE
* 
* =========================================================================
*
*             File Name: labeling_lab.c 
*           Description: it contains the function to threshold BYTE images 
*   Initial Coding Date: April 23, 1996
*           Portability: Standard (ANSI) C
*             Credit(s): Xiaohe Chen
*                        Southern Illinois University at Edwardsville
*
** Copyright (c) 1995, 1996, SIUE - Scott Umbaugh, X Chen
****************************************************************************/
/*
** include header files
*/



#include "labeling.h"
void Mark_Obj(int rr, int cc, int counter)
{
	
	if ( pImageMatrix[rr][cc] != 0 )
	{
		pLabel[rr][cc] = counter;
		newImageMatrix[rr][cc] = counter;
		if (rr > 0)
			if ((pImageMatrix[rr][cc] == pImageMatrix[rr-1][cc]) && (pLabel[rr-1][cc] == 0))
				Mark_Obj(rr-1, cc, counter);
		if (cc > 0) 
			if ((pImageMatrix[rr][cc] == pImageMatrix[rr][cc-1]) && (pLabel[rr][cc-1] == 0))
				Mark_Obj(rr, cc-1, counter);
		if (rr < no_of_rows-1) 
			if ((pImageMatrix[rr][cc] == pImageMatrix[rr+1][cc]) && (pLabel[rr+1][cc] == 0))
				Mark_Obj(rr+1, cc, counter);
		if (cc < no_of_cols -1) 
			if ((pImageMatrix[rr][cc] == pImageMatrix[rr][cc+1]) && (pLabel[rr][cc+1] == 0))
				Mark_Obj(rr, cc+1, counter);
	}
	
}

Image *labeling_Image(Image *inputImage)
{
/*
	Matrix *pMLabel;
	byte ** pImageMatrix;
	byte **newImageMatrix;
	int **pLabel;
	int no_of_rows, no_of_cols, no_of_bands;
	int counter = 1;
*/
	int bands = 0;
	int r, c;
	CVIP_TYPE dt;
	
	dt = getFormat_CVIP(inputImage);
	outImage = clone_Image(inputImage, CVIP_BYTE);
	history_copy(inputImage, outImage);
	
	no_of_rows =  getNoOfRows_Image(inputImage);
	no_of_cols =  getNoOfCols_Image(inputImage);
	no_of_bands = getNoOfBands_Image(inputImage);
	

    pMLabel = new_Matrix(no_of_rows, no_of_cols, CVIP_INTEGER, REAL);
	pLabel = (int **)getData_Matrix(pMLabel);
    for (r = 0; r < no_of_rows; r++)
		for(c=0; c < no_of_cols; c++)
	{
		pLabel[r][c] = 0;
	}
	
	pImageMatrix = getData_Image(inputImage, bands);
	newImageMatrix = getData_Image(outImage, bands);
	printf("debug %d\n", no_of_rows);
  	for(r=0; r < no_of_rows; r++) 
		for(c = 0; c < no_of_cols; c++)
	{

		if ((pLabel[r][c] == 0) && (pImageMatrix[r][c] > (byte)0))
		{
			Mark_Obj(r, c, counter);
			counter ++;
		}
	}
	
	printf("\nTotal Object number : %d\n", counter -1);
	counter = 0;
	delete_Matrix(pMLabel);
	return outImage;
}

