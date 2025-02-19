/***************************************************************************
* **********************************************************************
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* **********************************************************************
*
*             File Name: writePNG.c
*           Description: PNG conversion driver
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

#include "png.h"

#define DEFAULT_BIT_DEPTH 8

int cviptopng(Image *cvipImage, char *filename)
{
	FILE *fp;
	byte **tempImage;

	png_structp png_ptr;
	png_infop info_ptr;
	png_bytep *row_ptrs;

	int bands;
	int rows;
	int cols;
	int colCounter;

	/* CVIP Image Info */
	int cvipWidth;
	int cvipHeight;
	int cvipBands;
	int cvipColorSpace;
	int cvipBitDepth;

	/* PNG Image Info */
	int width;
	int height;
	int bit_depth;
	int color_type;
	int channels;

	/* open file to write PNG */
	fp = fopen(filename, "wb");
	if (!fp)
	{
		fprintf(stderr, "Can't open file: %s for writing!\n", filename);
		return 1;
	}

	// allocate png_truct and png_info
	png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, (png_voidp)NULL, NULL, NULL);
	if (!png_ptr)
	{
		fprintf(stderr, "Mermory allocation for png_ptr failed!\n");
		return 1;
	}

	info_ptr = png_create_info_struct(png_ptr);
	if (!info_ptr)
	{
		fprintf(stderr, "Mermory allocation for info_ptr failed!\n");
		png_destroy_read_struct(&png_ptr, (png_infopp)NULL, (png_infopp)NULL);
		return 1;
	}

	png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, (png_voidp)NULL, NULL, NULL);

	if (setjmp(png_jmpbuf(png_ptr)))
	{
		png_destroy_write_struct(&png_ptr, &info_ptr);
		fclose(fp);
		return 1;
	}

	png_init_io(png_ptr, fp);

	/* Get CVIP Image Info */
	cvipBands = getNoOfBands_Image(cvipImage);
	cvipWidth = getNoOfCols_Image(cvipImage);
	cvipHeight = getNoOfRows_Image(cvipImage);
	cvipColorSpace = cvipImage->color_space;
	cvipBitDepth = DEFAULT_BIT_DEPTH;

	/* Set PNG Image Info */
	width = cvipWidth;
	height = cvipHeight;
	bit_depth = cvipBitDepth;
	if (cvipColorSpace == GRAY_SCALE)
		color_type = PNG_COLOR_TYPE_GRAY;
	else if (cvipColorSpace == RGB)
		color_type = PNG_COLOR_TYPE_RGB;
	channels = cvipBands;

	png_set_IHDR(png_ptr, info_ptr, width, height, bit_depth, color_type, PNG_INTERLACE_NONE, 
		PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);

	png_write_info(png_ptr, info_ptr);

	/* Get CVIP Image Data */
	row_ptrs = (png_bytep *)malloc(height * sizeof(png_bytep));
	for (rows = 0; rows < height; rows ++)
	{
		row_ptrs[rows] = (png_bytep)png_malloc(png_ptr, png_get_rowbytes(png_ptr, info_ptr));	
	}	
	
	for (bands = 0; bands < cvipBands; bands ++)
	{
		tempImage = getData_Image(cvipImage, bands);
		for (rows = 0; rows < height; rows ++)
		{
			colCounter = 0;
			for (cols = 0; cols < width * channels; cols ++)
			{
				if (bands == 0) //red or gray
				{
					if ((cols % channels) == 0)
					{
						row_ptrs[rows][cols] = tempImage[rows][colCounter];
						colCounter ++;
					}
				}
				else if (bands == 1) //green
				{
					if (((cols + 2) % channels) == 0)
					{
						row_ptrs[rows][cols] = tempImage[rows][colCounter];
						colCounter ++;
					}
				}
				else if (bands == 2) //blue
				{
					if (((cols + 1) % channels) == 0)
					{
						row_ptrs[rows][cols] = tempImage[rows][colCounter];
						colCounter ++;
					}
				}
			}
		}
	}

	png_write_image(png_ptr, row_ptrs);

	png_write_end(png_ptr, info_ptr);

	png_destroy_write_struct(&png_ptr, &info_ptr);

	for (rows = 0; rows < height; rows ++)
		free(row_ptrs[rows]);
	fclose(fp);

	return 0;
}