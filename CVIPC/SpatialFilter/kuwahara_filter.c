/***************************************************************************
* =========================================================================
*
*   Computer Vision and Image Processing Lab - Dr. Scott Umbaugh SIUE 
* 
* =========================================================================
*
*             File Name: kuwahara.c 
*            Name: Jhansi Lakshmi Akkineni  
*            Portability: Standard (ANSI) C*                         
**      Copyright (c) 1995, 1996, SIUE - Scott Umbaugh
****************************************************************************/


#include "CVIPconvert.h"
#include "CVIPimage.h"
#include "float.h"
#include "CVIPspfltr.h" 
#include "CVIPmap.h"  

//float* mean_and_variance(unsigned int x0, int y0, int x1, int y1, float **image);

Image *kuwahara_filter(Image *inputImage, int mask_size)
{
	float **image, **outImage;
	Image *outputImage;
	unsigned int    nofrows,  nofcols, nofbands, bands;
	unsigned int d = 0, r, c, i, j;
	float localMean, localVariance, bestMean, bestVariance, mean[2], sum=0, count=0,temp;

	cast_Image(inputImage, CVIP_FLOAT);
	nofbands = getNoOfBands_Image(inputImage);
    nofrows =  getNoOfRows_Image(inputImage);
    nofcols =  getNoOfCols_Image(inputImage);

	outputImage = new_Image(inputImage->image_format,inputImage->color_space,nofbands,nofrows, nofcols,CVIP_FLOAT,REAL);
	d=(mask_size-1)/2;
        
      for(bands=0; bands < nofbands; bands++) {
		  image = getData_Image(inputImage, bands);
		  outImage = getData_Image(outputImage, bands);
		  for(r=d; r < nofrows-d; r++){
              for(c=d; c < nofcols-d; c++){
				  sum=0;count=0;
				  for(i=(r-d); i<=r; i++)
				  {
					for(j=(c-d); j<=c; j++)
					{
						//v = image1[i][j];
						sum = sum + image[i][j];
						count = count + 1;
					}
				  }
	              mean[0] = (float)(sum/count);
				  sum =0;
				  for(i=(r-d); i<=r; i++)
				  {
					for(j=(c-d); j<=c; j++)
					{
						temp = mean[0] - image[i][j];
						sum = sum + (temp * temp);
					}
				  }
				  mean[1] = (float)(sum/count);
				  localMean = (float)mean[0];
                  localVariance = (float)mean[1];
				  bestMean = localMean;
				  bestVariance = localVariance;
				  if (localVariance < bestVariance)
				  {
					  bestMean     = localMean;
                      bestVariance = localVariance;
				  }
				  sum=0;count=0;

				  //mean = (float*)mean_and_variance (r, (c-d), (r+d), c, image);
				  for(i=r; i<=(r+d); i++)
				  {
					for(j=(c-d); j<=c; j++)
					{
						//v = image1[i][j];
						sum = sum + image[i][j];
						count = count + 1;
					}
				  }
	              mean[0] = (float)(sum/count);
				  sum =0;
				  for(i=r; i<=(r+d); i++)
				  {
					for(j=(c-d); j<=c; j++)
					{
						temp = mean[0] - image[i][j];
						sum = sum + (temp * temp);
					}
				  }
				  mean[1] = (float)(sum/count);
				  localMean = (float)mean[0];
                  localVariance = (float)mean[1];
				  if (localVariance < bestVariance)
				  {
					  bestMean     = localMean;
                      bestVariance = localVariance;
				  }
				  sum=0;count=0;
				  //mean = (float*)mean_and_variance ((r-d), c, r, (c+d), image);
				  for(i=(r-d); i<=r; i++)
				  {
					for(j=c; j<=(c+d); j++)
					{
						//v = image1[i][j];
						sum = sum + image[i][j];
						count = count + 1;
					}
				  }
	              mean[0] = (float)(sum/count);
				  sum =0;
				  for(i=(r-d); i<=r; i++)
				  {
					for(j=c; j<=(c+d); j++)
					{
						temp = mean[0] - image[i][j];
						sum = sum + (temp * temp);
					}
				  }
				  mean[1] = (float)(sum/count);
				  localMean = (float)mean[0];
                  localVariance = (float)mean[1];
				  if (localVariance < bestVariance)
				  {
					  bestMean     = localMean;
                      bestVariance = localVariance;
				  }
				  sum=0;count=0;
				  //mean = (float*)mean_and_variance (r, c, (r+d), (c+d), image);
				  for(i=r; i<=(r+d); i++)
				  {
					for(j=c; j<=(c+d); j++)
					{
						//v = image1[i][j];
						sum = sum + image[i][j];
						count = count + 1;
					}
				  }
	              mean[0] = (float)(sum/count);
				  sum =0;
				  for(i=r; i<=(r+d); i++)
				  {
					for(j=c; j<=(c+d); j++)
					{
						temp = mean[0] - image[i][j];
						sum = sum + (temp * temp);
					}
				  }
				  mean[1] = (float)(sum/count);
				  localMean = (float)mean[0];
                  localVariance = (float)mean[1];
				  if (localVariance < bestVariance)
				  {
					  bestMean     = localMean;
                      bestVariance = localVariance;
				  }
				  outImage[r][c] = (float)bestMean;
			  }
		  }
	  }
	  outputImage = condRemap_Image(outputImage, CVIP_BYTE, 0, 255);
	return outputImage;
}
       
/*float* mean_and_variance(int x0, int y0, int x1, int y1, float **image1)
{
	float sum = 0.0, mean[2], temp, v;
	int count =0, i, j;

	for(i=x0; i<=x1; i++)
	{
		for(j=y0; j<=y1; j++)
		{
			v = image1[i][j];
			sum = sum + v;
			count = count + 1;
		}
	}

	mean[0] = (float)(sum/count);

    sum =0;
	for(i=x0; i<=x1; i++)
	{
		for(j=y0; j<=y1; j++)
		{
			temp = mean[0] - image1[i][j];
			sum = sum + (temp * temp);
		}
	}
	mean[1] = (float)(sum/count);
	return mean;
}*/
