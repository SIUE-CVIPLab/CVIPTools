/***************************************************************************
* **********************************************************************
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* **********************************************************************
*
*             File Name: opjtocvip.c
*           Description: openjpeg image structure to cvip image structure conversion driver
*         Related Files: jp2_decode.c
*           Portability: Standard (ANSI) C
*             Author(s): Serkan Kefel
*                        Southern Illinois University @ Edwardsville
*
** Copyright (C) 1996 SIUE - by Scott Umbaugh and .
**
** Permission to use, copy, modify, and distribute this software and its
** documentation for any purpose and without fee is hereby granted, provided
** that the above copyright notice appear in all copies and that both that
** copyright notice and this permission notice appear in supporting
** documentation.  This software is provided "as is" without express or
** implied warranty.
****************************************************************************/

#include "CVIPtoolkit.h"
#include "CVIPconvert.h"
#include "CVIPdef.h"
#include "CVIPimage.h"

#include "openjpeg.h"

Image* opjtocvip(opj_image_t *image)
{
	Image **temp;
	Image *outputImage;
	byte **tempImage;

	int no_of_bands, no_of_rows, no_of_cols;
	int bands, r, c, pix_counter;

	temp = (Image *)malloc(image->numcomps*sizeof(Image));
	for(bands = 0; bands < image->numcomps; bands ++)
		temp[bands] = create_black(image->x1, image->y1);
	if(image->numcomps == 3)
		outputImage = assemble_bands(temp, 3);
	else
		outputImage = create_black(image->x1, image->y1);

	outputImage->bands = image->numcomps;
	
	if(image->color_space == 1)
		outputImage->color_space = RGB;
	else if(image->color_space == 2)
		outputImage->color_space = GRAY_SCALE;
	else
		exit(-1); //error
	outputImage->image_format = JP2;
	
	no_of_bands = outputImage->bands;
	no_of_rows = image->y1;
	no_of_cols = image->x1;

	for(bands=0; bands < no_of_bands; bands++) 
	{
		pix_counter = 0;
		tempImage = getData_Image(outputImage, bands);
		for(r=0; r < no_of_rows; r++) 
		{
			for(c=0; c < no_of_cols; c++)
			{
				tempImage[r][c] = image->comps[bands].data[pix_counter];
				pix_counter++;
			}
		}
	}
	return outputImage;
}

