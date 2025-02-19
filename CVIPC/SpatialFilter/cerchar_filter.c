
/***************************************************************************
* =========================================================================
*
*   Computer Vision and Image Processing Lab - Dr. Scott Umbaugh SIUE
* 
* =========================================================================
*
*             File Name: cerchar_filter.c 
*           Description: Cervenka and Chrvat Multiband Edge Detector
*   Initial Coding Date: Apr 20th 2009
*           Portability: Standard (ANSI) C
*             Credit(s): Mounika Mamidi
*                        Southern Illinois University at Edwardsville
*
** Copyright (c) 1995, 2004, SIUE - Scott Umbaugh, Kun Luo, Yansheng Wei
****************************************************************************/

/*include Header files*/
#include <CVIPspfltr.h>
#include "CVIPtoolkit.h"
#include "CVIPconvert.h"
#include "CVIPdef.h"
#include "CVIPtyp.h"
#include "CVIPimage.h"
#include "CVIPtransform.h"
#include "CVIParithlogic.h"


#define CASE_MAX 10


Image *cerchar_filter(Image *inputImage)
{
	byte **input;
	float **output;
	Image *outputImage;
	float arithavg1=0,arithavg2=0,arithavg3=0,arithavg4=0;
	float a=0,b=0,c=0,a1=0,b1=0,c2=0,d=0,e=0;
	unsigned int bands,row,col,r1,c1,band=1;
	unsigned int noofbands,noofcols,noofrows;

	noofbands=getNoOfBands_Image(inputImage);

	noofcols=getNoOfCols_Image(inputImage);

	noofrows=getNoOfRows_Image(inputImage);

	outputImage=new_Image(inputImage->image_format,inputImage->color_space,band,noofrows,noofcols,CVIP_FLOAT,REAL);
		//calculating the arithmetic average in all the bands at each pixel location

		for(row=0;row<noofrows-1;row++)
		{
			for(col=0;col<noofcols-1;col++)
			{
				arithavg1=0;arithavg2=0;

				arithavg3=0;arithavg4=0;
				r1=row;
				c1=col;
				//for the last and first row and column
				if((r1==row)&&(c1==col))
				{
				for(bands=0;bands<noofbands;bands++)
				{
					input=getData_Image(inputImage,bands);
					arithavg1=arithavg1+input[row][col];
				}
				r1=row+1;
				c1=col+1;
				}
				bands=0;
				if((r1==row+1)&&(c1==col+1))
				{
				for(bands=0;bands<noofbands;bands++)
				{
					input=getData_Image(inputImage,bands);
					arithavg2=arithavg2+input[r1][c1];
				}
				r1=row+1;
				c1=col;
				}				
				if((r1==row+1)&&(c1==col))
				{
				for(bands=0;bands<noofbands;bands++)
				{
					input=getData_Image(inputImage,bands);
					arithavg3=arithavg3+input[r1][c1];
				}
				r1=row;
				c1=col+1;
				}
				if((r1==row)&&(c1==col+1))
				{
				for(bands=0;bands<noofbands;bands++)
				{
					input=getData_Image(inputImage,bands);
					arithavg4=arithavg4+input[r1][c1];
				}
				}
				//arithmetic average at each band
				arithavg1=arithavg1/noofbands;
				arithavg2=arithavg2/noofbands;
				arithavg3=arithavg3/noofbands;
				arithavg4=arithavg4/noofbands;

				for(bands=0;bands<noofbands;bands++)
				{
					input=getData_Image(inputImage,bands);

					output=getData_Image(outputImage,0);

						a=a+(input[row][col]-arithavg1)*(input[row+1][col+1]-arithavg2);

						b=b+(input[row][col]-arithavg1)*(input[row][col]-arithavg1);

						c=c+(input[row+1][col+1]-arithavg2)*(input[row+1][col+1]-arithavg2);

						b1=b1+(input[row+1][col]-arithavg3)*(input[row+1][col]-arithavg3);

						c2=c2+(input[row][col+1]-arithavg4)*(input[row][col+1]-arithavg4);

						a1=a1+(input[row+1][col]-arithavg3)*(input[row][col+1]-arithavg4);
					}

				if(b==0||c==0)
					d=0.0f;
				else
					d=a/sqrt(b*c);

				if(b1==0||c2==0)

					e=0.0f;		
				else
					e=a1/sqrt(b1*c2);
					if(d<=e)
						output[row][col]=d;
					else
						output[row][col]=e;
					a=0.0f;
					b=0.0f;
					c=0.0f;
					a1=0.0f;
					b1=0.0f;
					c2=0.0f;
			}
		}

	return outputImage;
}