#include "CVIPtoolkit.h"
#include "CVIPconvert.h"
#include "CVIPdef.h"
#include "CVIPimage.h"

Image* CLAHE(Image* inputImage, int blocksize, float clipPercent, int bandSelect) {
	byte** imBand; //Array for Input Image
	float** imFirst; //Array for Chosen Output Band
	float** imSecond; //Array for Another Output Band
	float** imThird; //Array for Another Output Band
	float** tempImageArr; //Array to Hold DCT Symmetry Image
	Image* tempImage; //DCT Symmetry Image
	Image* outImage; //Output Image
	float tmp1; //Used in 3 Band Ratio Calculation
	unsigned int row, col, origBand, height, width; //Holds Input and DCT Symmetry Image Information
	int totalClipped, totalClippedBins, blockR, blockC; //Used to Calculate Clipping Limit

	float hist[256] = { 0 }; //Probability Density Function Storage
	float cdf[256] = { 0 }; //Cumulative Distribution Function Storage
	float regionSize = blocksize * blocksize; //Area of Block
	int clipLimit = regionSize * clipPercent; //Maximum Allowed Histogram Bin Number
	if (clipLimit < 1)
		clipLimit = 1;
	int halfSize = blocksize / 2;
	int lowerLimit = halfSize + (blocksize % 2);

	origBand = getNoOfBands_Image(inputImage); //Input Image Number of Bands
	row = getNoOfRows_Image(inputImage); //Input Image Number of Rows
	col = getNoOfCols_Image(inputImage); //Input Image Number of Columns

	//Error Check: Returns Original Image if Band Selection is Invalid.
	if (bandSelect < 0 || bandSelect >= origBand)
	{
		fprintf(stderr, "CLAHE: Selected Band Not Available\n");
		return(inputImage);
	}

	height = row + blocksize; //DCT Symmetry Image Number of Rows
	width = col + blocksize;  //DCT Symmetry Image Number of Rows

	//Create Images for DCT Symmetry and Output 
	tempImage = new_Image(BMP, RGB, 1, height, width, CVIP_FLOAT, REAL); //DCT Symmetry Image

	//Create Output Float Image:
	if (getDataType_Image(inputImage) < CVIP_FLOAT)
	{
		outImage = duplicate_Image(inputImage); //Create Duplicate of Input Image in Output Image
		cast_Image(outImage, CVIP_FLOAT); //Cast Image to Float to Avoid Error in condRemap_Image
		outImage = condRemap_Image(outImage, CVIP_FLOAT, 0, 255); // Output Image
	}
	else
	{
		outImage = condRemap_Image(inputImage, CVIP_FLOAT, 0, 255); // Output Image
	}

	//Get Original Image Array at the Selected Band
	imBand = getData_Image(inputImage, bandSelect); 

	//Assign Output Image Arrays
	if (origBand == 1)
	{
		imFirst = getData_Image(outImage, bandSelect); //Get Output Image Array at the Selected Band
	}
	else
	{
		imFirst = getData_Image(outImage, bandSelect); //Get Output Image Array at the Selected Band
		if (bandSelect == 0)
		{
			imSecond = getData_Image(outImage, 1); //Get Output Image Array at the Nonselected Band
			imThird = getData_Image(outImage, 2); //Get Output Image Array at the Nonselected Band
		}
		else if (bandSelect == 1)
		{
			imSecond = getData_Image(outImage, 0); //Get Output Image Array at the Nonselected Band
			imThird = getData_Image(outImage, 2); //Get Output Image Array at the Nonselected Band
		}
		else
		{
			imSecond = getData_Image(outImage, 0); //Get Output Image Array at the Nonselected Band
			imThird = getData_Image(outImage, 1); //Get Output Image Array at the Nonselected Band
		}
	}

	//Get DCT Symmetry Image Array
	tempImageArr = getData_Image(tempImage, 0);

	//Fill in the Middle of the DCT Symmetry Image with the Input Image
	for (int r = lowerLimit; r < height - halfSize - 1; r++)
	{
		for (int c = lowerLimit; c < width - halfSize - 1; c++)
		{
			tempImageArr[r][c] = (float)imBand[r - lowerLimit][c - lowerLimit];
		}
	}

	//Create DCT Symmetry Image by Mirroring the Edges
	for (int r = 0; r < height; r++)
	{
		for (int c = 0; c < width; c++)
		{
			//Top Left
			if (c < lowerLimit && r < lowerLimit)
				tempImageArr[r][c] = tempImageArr[lowerLimit + (lowerLimit - r - 1)][lowerLimit + (lowerLimit - c - 1)];
			//Top Right
			else if (c >= width - halfSize - 1 && r < lowerLimit)
				tempImageArr[r][c] = tempImageArr[lowerLimit + (lowerLimit - r - 1)][(width - halfSize - 1) - (c - (width - halfSize - 1) + 1)];
			//Bottom Left
			else if (c < lowerLimit && r >= height - halfSize - 1)
				tempImageArr[r][c] = tempImageArr[(height - halfSize - 1) - (r - (height - halfSize - 1) + 1)][lowerLimit + (lowerLimit - c - 1)];
			//Bottom Right
			else if (c >= width - halfSize - 1 && r >= height - halfSize - 1)
				tempImageArr[r][c] = tempImageArr[(height - halfSize - 1) - (r - (height - halfSize - 1) + 1)][(width - halfSize - 1) - (c - (width - halfSize - 1) + 1)];
			//Left
			else if (c < lowerLimit)
				tempImageArr[r][c] = tempImageArr[r][lowerLimit + (lowerLimit - c - 1)];
			//Right
			else if (c >= width - halfSize - 1)
				tempImageArr[r][c] = tempImageArr[r][(width - halfSize - 1) - (c - (width - halfSize - 1) + 1)];
			//Top
			else if (r < lowerLimit)
				tempImageArr[r][c] = tempImageArr[lowerLimit + (lowerLimit - r - 1)][c];
			//Bottom
			else if (r >= height - halfSize - 1)
				tempImageArr[r][c] = tempImageArr[(height - halfSize - 1) - (r - (height - halfSize - 1) + 1)][c];
			//Pixel is Part of the Original Size
			else
				tempImageArr[r][c] = tempImageArr[r][c];
		}
	}
	
	//Loop Through "Original Image" Within DCT Symettry Image
	for (int r = lowerLimit; r < height - halfSize; r++)
	{
		for (int c = lowerLimit; c < width - halfSize; c++)
		{
			//Initialize Clip Variables
			totalClipped = 0;
			totalClippedBins = 0;

			//Clear Histogram Arrays
			for (int h = 0; h < 256; h++)
			{
				hist[h] = 0.0;
				cdf[h] = 0.0;
			}
			//Get Histogram (Probability Density Function)
			int startR = r - lowerLimit;
			int endR = startR + blocksize;
			int startC = c - lowerLimit;
			int endC = startC + blocksize;
			for (blockR = startR; blockR < endR; blockR++)
			{
				for (blockC = startC; blockC < endC; blockC++)
				{
					hist[(int)tempImageArr[blockR][blockC]] += 1.0;
				}
			}
			//Clip Histogram:
			for (int h = 0; h < 256; h++)
			{
				if (hist[h] > clipLimit)
				{
					totalClipped += hist[h] - clipLimit;
					totalClippedBins += 1;
					hist[h] = clipLimit;
				}
			}
			//Redistribute Histogram:
			int place = 0;
			while (totalClipped > 0)
			{
				if (hist[place] > 0)
				{
					hist[place]++;
					totalClipped--;
				}
				place++;
				if (place == 256)
					place = 0;
			}
			//Calculate CDF:
			cdf[0] = hist[0] * (255.0 / regionSize);
			for (int h = 1; h < 256; h++)
			{
				if (hist[h] > 0.0) {
					cdf[h] = hist[h] * (255.0 / regionSize);
					cdf[h] += cdf[h - 1];
				}
				else {
					cdf[h] = cdf[h - 1];
				}
			}
			//Calculate Output Pixel Values
			if (origBand > 1)
			{
				if (tempImageArr[r][c] == 0)
					tmp1 = 1;
				else
					tmp1 = tempImageArr[r][c];
				imFirst[startR][startC] = cdf[(int)tempImageArr[r][c]];
				imSecond[startR][startC] = imSecond[startR][startC] * (cdf[(int)tmp1] / tmp1);
				imThird[startR][startC] = imThird[startR][startC] * (cdf[(int)tmp1] / tmp1);

			}
			else
			{
				imFirst[startR][startC] = cdf[(int)tempImageArr[r][c]];
			}
		}
	}

	//Delete Non-Returned Images
	delete_Image(tempImage);
	delete_Image(inputImage);

	//Return Result Image
	return outImage;
}

Image* CLAHE_Grid(Image* inputImage, int blocksize, float clipPercent, int bandSelect) {
	byte** imBand; //Array for Input Image
	float** imFirst; //Array for Chosen Output Band
	float** imSecond; //Array for Another Output Band 
	float** imThird; //Array for Another Output Band
	Image* outImage; //Output Image
	float tmp1; //Used in 3 Band Ratio Calculation
	unsigned int row, col, origBand, gridRows, gridCols; //Holds Input Image and Block Size Information
	int totalClipped = 0, totalClippedBins = 0; //Used to Calculate Clipping Limit

	float hist[256] = { 0 }; //Probability Density Function Storage
	float cdf[256] = { 0 }; //Cumulative Distribution Function Storage
	float regionSize = blocksize * blocksize; //Area of Block
	int clipLimit = regionSize * clipPercent; //Maximum Allowed Histogram Bin Number
	if (clipLimit < 1)
		clipLimit = 1;

	origBand = getNoOfBands_Image(inputImage); //Input Image Number of Bands
	row = getNoOfRows_Image(inputImage); //Input Image Number of Rows
	col = getNoOfCols_Image(inputImage); //Input Image Number of Columns

	//Check if bandSelect is Valid:
	if (bandSelect < 0 || bandSelect >= getNoOfBands_Image(inputImage))
	{
		fprintf(stderr, "CLAHE: Selected Band Not Available\n");
		return(inputImage);
	}

	//Create Grid Details:
	gridRows = row / blocksize; //Number of Grids Per Row
	gridCols = col / blocksize; //Number of Grids Per Col

	//Create Output Float Image:
	if (getDataType_Image(inputImage) < CVIP_FLOAT)
	{
		outImage = duplicate_Image(inputImage);
		cast_Image(outImage, CVIP_FLOAT);
		outImage = condRemap_Image(outImage, CVIP_FLOAT, 0, 255);
	}
	else
	{
		outImage = condRemap_Image(inputImage, CVIP_FLOAT, 0, 255);
	}

	//Get Original Image Array at the Selected Band:
	imBand = getData_Image(inputImage, bandSelect);

	//Assign Output Image Arrays:
	if (origBand == 1)
	{
		imFirst = getData_Image(outImage, bandSelect);
	}
	else
	{
		imFirst = getData_Image(outImage, bandSelect);
		if (bandSelect == 0)
		{
			imSecond = getData_Image(outImage, 1);
			imThird = getData_Image(outImage, 2);
		}
		else if (bandSelect == 1)
		{
			imSecond = getData_Image(outImage, 0);
			imThird = getData_Image(outImage, 2);
		}
		else
		{
			imSecond = getData_Image(outImage, 0);
			imThird = getData_Image(outImage, 1);
		}
	}

	//Loop Through Blocks:
	for (int gridR = 0; gridR < gridRows; gridR++)
	{
		for (int gridC = 0; gridC < gridCols; gridC++)
		{
			//Clear Histogram Arrays:
			for (int h = 0; h < 256; h++)
			{
				hist[h] = 0.0;
				cdf[h] = 0.0;
			}
			//Get Histogram (Probability Density Function):
			for (int blockR = gridR * blocksize; blockR < (gridR * blocksize) + blocksize; blockR++)
			{
				for (int blockC = gridC * blocksize; blockC < (gridC * blocksize) + blocksize; blockC++)
				{
					hist[imBand[blockR][blockC]] += 1.0;
				}
			}
			//Clip Histogram:
			for (int h = 0; h < 256; h++)
			{
				if (hist[h] > clipLimit)
				{
					totalClipped += hist[h] - clipLimit;
					totalClippedBins += 1;
					hist[h] = clipLimit;
				}
			}
			//Redistribute Histogram:
			int place = 0;
			while (totalClipped > 0)
			{
				if (hist[place] > 0)
				{
					hist[place]++;
					totalClipped--;
				}
				place++;
				if (place == 256)
					place = 0;
			}
			//Calculate CDF (Cumulative Distribution Function):
			cdf[0] = hist[0] * (255.0 / regionSize);
			for (int h = 1; h < 256; h++)
			{
				if (hist[h] > 0.0) {
					cdf[h] = hist[h] * (255.0 / regionSize);
					cdf[h] += cdf[h - 1];
				}
				else {
					cdf[h] = cdf[h - 1];
				}
			}
			//Get Newly Mapped Pixels:
			for (int blockR = gridR * blocksize; blockR < (gridR * blocksize) + blocksize; blockR++)
			{
				for (int blockC = gridC * blocksize; blockC < (gridC * blocksize) + blocksize; blockC++)
				{
					//Calculate Output Pixel Values
					if (origBand > 1)
					{
						if (imBand[blockR][blockC] == 0)
							tmp1 = 1;
						else
							tmp1 = imBand[blockR][blockC];
						imFirst[blockR][blockC] = cdf[imBand[blockR][blockC]];
						imSecond[blockR][blockC] = imSecond[blockR][blockC] * (cdf[(int)tmp1] / tmp1);
						imThird[blockR][blockC] = imThird[blockR][blockC] * (cdf[(int)tmp1] / tmp1);

					}
					else
					{
						imFirst[blockR][blockC] = cdf[imBand[blockR][blockC]];
					}
				}
			}
		}
	}

	//Delete Original Image:
	delete_Image(inputImage);

	//Return Result Image:
	return outImage;
}

