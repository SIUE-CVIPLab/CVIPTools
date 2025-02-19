
/***************************************************************************
* =========================================================================
*
*   Computer Vision and Image Processing Lab - Dr. Scott Umbaugh SIUE
* 
* =========================================================================
*
*             File Name: morph_thinning.c 
*           Description: Performs morphological operation
*   Initial Coding Date: Nov 30th 2009
*           Portability: Standard (ANSI) C
*             Credit(s): Mounika Mamidi
*                        Southern Illinois University at Edwardsville
*
** Copyright (c) 1995, 2004, SIUE - Scott Umbaugh, Mounika Mamidi
****************************************************************************/

/*
** include header files
*/
#include "CVIPtoolkit.h"
#include "CVIPconvert.h"
#include "CVIPdef.h"
#include "CVIPimage.h"
#include "CVIPtyp.h"
#include "CVIPmorph.h"

	/* 
	** Thinning transform
	*/
	Image* morph_thinning(Image *inputImage,int filterdimension,char *ThinningFilter)
	{
		Image *thinning_Image, *temp;
		float **thinningdata,**outputdata;
		Matrix	*OutputFilter, *ThinningValues;

		unsigned int rows,cols, bands;
		unsigned int r,c, b;
		int x=0,y=0,counter=0;
		
		int midpoint=filterdimension/2;

		bands = getNoOfBands_Image(inputImage);

		rows =  getNoOfRows_Image(inputImage);

		cols =  getNoOfCols_Image(inputImage);

		thinning_Image=new_Image(inputImage->image_format, inputImage->color_space,bands,rows,cols,CVIP_FLOAT,REAL);
		ThinningValues =new_Matrix(filterdimension,filterdimension,CVIP_FLOAT,REAL);

		cast_Image(inputImage, CVIP_FLOAT);

	    OutputFilter = new_Matrix(filterdimension,filterdimension,CVIP_FLOAT,REAL);

			for(b=0; b < bands; b++) {
			/*
			** reference each band of image data in 2-d matrix form;
			** which is used for reading and writing the pixel values
			*/
				thinningdata = getData_Image(inputImage, b);
				for(r=0; r < rows; r++) {
					for(c=0; c < cols; c++) {
						if(thinningdata[r][c]>0)
							thinningdata[r][c]=1.0f;
						else
							thinningdata[r][c]=0.0f;
					}
				}
			}
		for(r = 0; r < filterdimension; r++)
		{
			for( x = 0; x < filterdimension; x++)
			{
					if (ThinningFilter[r*filterdimension+x] == '1')
						((float **)(ThinningValues->rptr))[r][x] = 1.0;
					else if (ThinningFilter[r*filterdimension+x] == '0')
						((float **)(ThinningValues->rptr))[r][x] = 0;
					else
					   ((float **)(ThinningValues->rptr))[r][x] = 255.0;
			}
		}
			for(b=0; b < bands; b++) {
			/*
			** reference each band of image data in 2-d matrix form;
			** which is used for reading and writing the pixel values
			*/
				thinningdata = getData_Image(inputImage, b);
				outputdata = getData_Image(thinning_Image,b);
				for(r=0; r < rows-filterdimension+1; r++) {
					for(c=0; c < cols-filterdimension+1; c++) {

						if(thinningdata[r+midpoint][c+midpoint]!=(((float **)(ThinningValues->rptr))[midpoint][midpoint]))
						{
								outputdata[r+midpoint][c+midpoint]=0;
						}
							else
							{
								for(y=0;y<filterdimension;y++)
								{
									//x-column, y-row
									for(x=0;x<filterdimension;x++)
									{
								if(((float**)(ThinningValues->rptr))[y][x]==255.0f)
									((float **)(OutputFilter->rptr))[y][x]=thinningdata[r+y][c+x];
								else if(((float**)(ThinningValues->rptr))[y][x]== 0.0f)
									((float **)(OutputFilter->rptr))[y][x]=0.0f;
								else if(((float**)(ThinningValues->rptr))[y][x]==1.0f)
									((float **)(OutputFilter->rptr))[y][x]=1.0f;
									}

								}
								for(y=0;y<filterdimension;y++)
								{
									//x-column, y-row
									for(x=0;x<filterdimension;)
									{
										if(thinningdata[r+y][c+x]==((float **)(OutputFilter->rptr))[y][x])
										{
											x++;
											counter=counter+1;
										}
										else
										{
											outputdata[r+midpoint][c+midpoint]=0;
											break;
										}
									}
								}
								if(counter == (filterdimension*filterdimension))
								{
									outputdata[r+midpoint][c+midpoint]=255.0f;
									counter=0;
									
								}
								counter=0;
						}
					}
				}
			}


			for(b=0; b < bands; b++) {
				thinningdata = getData_Image(inputImage, b);
				outputdata = getData_Image(thinning_Image,b);
				for(r=0; r < rows; r++) {
					for(c=0; c < cols; c++) {	
						if(thinningdata[r][c]==1)
							thinningdata[r][c]=255;
							outputdata[r][c]=thinningdata[r][c]-outputdata[r][c];
						
					}
				}
			}
			delete_Matrix(OutputFilter);
			delete_Matrix(ThinningValues);
			temp=(Image *)remap_Image((const Image *)thinning_Image,CVIP_BYTE,0,255);
			delete_Image(thinning_Image);
			thinning_Image=temp;
			return thinning_Image;			
	}