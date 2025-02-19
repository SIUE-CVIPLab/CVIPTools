/*
* =========================================================================
*
*   Computer Vision and Image Processing Lab - Dr. Scott Umbaugh SIUE
* 
* =========================================================================
*             File Name: improved_mmse_filter.c
*           Description: Contains a function to improved mmse filter 
*   Initial Coding Date: June 22, 2009
*           Portability: Standard (ANSI) C
*             Credit(s): Hari Krishna Akkineni
*                        Southern Illinois University at Edwardsville
*
** Copyright (c) 1995, 1996, SIUE - Scott Umbaugh, Kun Luo, Yansheng Wei
****************************************************************************/

/*
** include header files
*/

#include "CVIPconvert.h"
#include "CVIPdef.h"
#include "CVIPimage.h"
#include "CVIPspfltr.h"
#include "float.h"


Image *improved_mmse_filter(Image *cvipImage, float threshval, int kernel_size, float nvar)
{

	Image       *cvipImage1;	/* declare image structure pointer*/

    unsigned int                 r,                /* row index */
                        c,           /* column index */
                        bands;                /* band index */
                        
    unsigned int         no_of_rows,        /* number of rows in image */
                        no_of_cols,        /* number of columns in image */
                        no_of_bands;        /* number of image bands */
        int p,
            k,
			Low,
			kLow,
			kHigh,flag;
        float lmean,
                lvar,
				kernelSize,
				varRatio,
                **image,
                **image1;
    /*
    ** Gets the number of image bands (planes)
    */
    no_of_bands = getNoOfBands_Image(cvipImage);

    /* 
    ** Gets the number of rows in the input image  
    */
    no_of_rows =  getNoOfRows_Image(cvipImage);

    /* 
    ** Gets the number of columns in the input image  
    */
    no_of_cols =  getNoOfCols_Image(cvipImage);
   
    
	//calculate new stretch values based on user input
    Low=(kernel_size-1)/2;
	

for(bands=0; bands < no_of_bands; bands++) 
{
        image = getData_Image(cvipImage, bands);
		cvipImage1 = duplicate_Image(cvipImage);
        image1 = getData_Image(cvipImage1, bands);

        for(r=Low; r < no_of_rows-Low; r++) 
		{
                 for(c=Low; c < no_of_cols-Low; c++) 
				 {

                    flag=0;
					kernelSize = kernel_size;

					  while (kernelSize>=3 && flag!=1)
					  {
/*                    calculate the  local mean */

						  kLow=(kernelSize-1)/2;
						  kHigh=(kernelSize+1)/2;

						  lmean=0;
						  for(k=r-kLow; k < r+kHigh; k++){
							  for(p=c-kLow; p < c+kHigh; p++){
								  lmean=(lmean+image[k][p]);
								  }
							 }
						  lmean=lmean/(kernelSize*kernelSize);

	/*                    Compute  local variance */                               
						  lvar=0;
						  for(k=r-kLow; k < r+kHigh; k++){
							  for(p=c-kLow; p < c+kHigh; p++){
								  lvar=(lvar+((image[k][p]-lmean)*(image[k][p]-lmean)));
								  }
							  }
						  lvar=lvar/(kernelSize*kernelSize - 1);

						  varRatio=nvar/lvar;

						  if(varRatio > threshval)
						  {
							  image1[r][c]=image[r][c]-(varRatio*(image[r][c]-lmean));
							  flag = 1;

						  }
						  else  /* gain is too small. try smaller kernel 
								to get smaller local variance and higher gain*/
						  
							  kernelSize = kernelSize - 2;
						  
					  }
				 }
			}
}
return cvipImage1;
}
/*
** end of function improved mmse filter
*/
