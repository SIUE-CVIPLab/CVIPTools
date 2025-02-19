/***************************************************************************
* **********************************************************************
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* **********************************************************************
*
*             File Name: cviptoopj.c
*           Description: cvip image structure to openjpeg image structure conversion driver
*         Related Files: jp2_encode.c
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
#include "opj_includes.h"

opj_image_t* cviptoopj(Image *inputImage)
{
	opj_image_t *temp = NULL;

	byte **tempImage;

	int no_of_bands, no_of_rows, no_of_cols;
	int bands, r, c, pix_counter;

	no_of_bands = getNoOfBands_Image(inputImage);
	no_of_rows =  getNoOfRows_Image(inputImage);
	no_of_cols =  getNoOfCols_Image(inputImage);

	temp = (opj_image_t*) opj_calloc(1, sizeof(opj_image_t));
	temp->numcomps = inputImage->bands;
	temp->comps = (opj_image_comp_t*)opj_malloc(temp->numcomps * sizeof(opj_image_comp_t));
	if(inputImage->color_space == RGB)
		temp->color_space = 1;
	else if(inputImage->color_space == GRAY_SCALE)
		temp->color_space = 2;

	temp->x0 = 0;
	temp->y0 = 0;
	temp->x1 = no_of_cols;
	temp->y1 = no_of_rows;

	for(bands = 0; bands < no_of_bands; bands++) 
	{
		opj_image_comp_t *comp = &temp->comps[bands];
		comp->w = no_of_cols;
		comp->h = no_of_rows;
		comp->dx = 1;
		comp->dy = 1;
		comp->prec = 8;
		comp->bpp = 8;
		comp->sgnd = 0;
		comp->data = (int*) opj_calloc(comp->w * comp->h, sizeof(int));
	}

	for(bands=0; bands < no_of_bands; bands++) 
	{
		tempImage = getData_Image(inputImage, bands);
		pix_counter = 0;
		for(r=0; r < no_of_rows; r++) 
		{
     		for(c=0; c < no_of_cols; c++)
			{
				temp->comps[bands].data[pix_counter] = tempImage[r][c];
				pix_counter ++;
			}
		}
	}

	return temp;
}