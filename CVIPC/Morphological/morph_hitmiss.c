

/***************************************************************************
* =========================================================================
*
*   Computer Vision and Image Processing Lab - Dr. Scott Umbaugh SIUE
* 
* =========================================================================
*
*             File Name: morph_hitmiss.c 
*           Description: Performs morphological operation
*   Initial Coding Date: Nov 10th 2009
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
	** hit or miss transform
	*/
	Image* morph_hitmiss(Image *inputImage,int filterdimension,char *HitmissFilter)
	{
		Image *hitmiss_Image, *temp;
		float **hitmissdata,**outputdata;
		Matrix	*OutputFilter, *HitormissFiilter;

		unsigned int rows,cols, bands;
		unsigned int r,c, b;
		int x=0,y=0,counter=0;
		
		int midpoint=(filterdimension/2);

		bands = getNoOfBands_Image(inputImage);

		rows =  getNoOfRows_Image(inputImage);

		cols =  getNoOfCols_Image(inputImage);

		hitmiss_Image=new_Image(inputImage->image_format, inputImage->color_space,bands,rows,cols,CVIP_FLOAT,REAL);

		cast_Image(inputImage, CVIP_FLOAT);

	    OutputFilter = new_Matrix(filterdimension,filterdimension,CVIP_FLOAT,REAL);
		HitormissFiilter=new_Matrix(filterdimension,filterdimension,CVIP_FLOAT,REAL);

			for(b=0; b < bands; b++) {
			/*
			** reference each band of image data in 2-d matrix form;
			** which is used for reading and writing the pixel values
			*/
				hitmissdata = getData_Image(inputImage, b);
				for(r=0; r < rows; r++) {
					for(c=0; c < cols; c++) {
						if(hitmissdata[r][c]>0)
							hitmissdata[r][c]=1.0f;
						else
							hitmissdata[r][c]=0.0f;
					}
				}
			}
		for(y = 0; y< filterdimension; y++)
		{
			for(x = 0; x< filterdimension; x++)
			{
					if (HitmissFilter[y*filterdimension+x] == '1')
						((float **)(HitormissFiilter->rptr))[y][x] = 1.0;
					else if (HitmissFilter[y*filterdimension+x] == '0')
						((float **)(HitormissFiilter->rptr))[y][x] = 0;
					else
						((float **)(HitormissFiilter->rptr))[y][x] = 255.0;
			}
		}
			for(b=0; b < bands; b++) {
			/*
			** reference each band of image data in 2-d matrix form;
			** which is used for reading and writing the pixel values
			*/
				hitmissdata = getData_Image(inputImage, b);
				outputdata = getData_Image(hitmiss_Image,b);
				for(r=0; r < rows-filterdimension+1; r++) {
					for(c=0; c < cols-filterdimension+1; c++) {

						if(hitmissdata[r+midpoint][c+midpoint]!=(((float **)(HitormissFiilter->rptr))[midpoint][midpoint]))
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
								if(((float**)(HitormissFiilter->rptr))[y][x]==255.0f)
									((float **)(OutputFilter->rptr))[y][x]=hitmissdata[r+y][c+x];
								else if(((float**)(HitormissFiilter->rptr))[y][x]== 0.0f)
									((float **)(OutputFilter->rptr))[y][x]=0.0f;
								else if(((float**)(HitormissFiilter->rptr))[y][x]==1.0f)
									((float **)(OutputFilter->rptr))[y][x]=1.0f;
									}

								}
								for(y=0;y<filterdimension;y++)
								{
									//x-column, y-row
									for(x=0;x<filterdimension;)
									{
										if(hitmissdata[r+y][c+x]==((float **)(OutputFilter->rptr))[y][x])
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
			delete_Matrix(OutputFilter);
			delete_Matrix(HitormissFiilter);
			delete_Image(inputImage);
			temp=(Image *)remap_Image((const Image *)hitmiss_Image,CVIP_BYTE,0,255);
			delete_Image(hitmiss_Image);
			hitmiss_Image=temp;
			return hitmiss_Image;			
	}