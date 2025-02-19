/***************************************************************************
* **********************************************************************
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* **********************************************************************
*
*             File Name: readPNG.c
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

#define READBYTE 8

Image* pngtocvip(char *filename)
{
	FILE *fp;
	char *header;

	Image *cvipImage;
	Image **temp;
	byte **tempImage;

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

	png_structp png_ptr;
	png_infop info_ptr, end_info;
	png_bytep *row_ptrs;

	// get file to be decoded
	fp = fopen(filename, "rb");
	if (!fp)
	{
		fprintf(stderr, "Can't read image: %s\n", filename);
		return 1;
	}
	
	// read header
	header = (char *)malloc(READBYTE*sizeof(char));
	fread(header, 1, READBYTE, fp);
	if (png_sig_cmp(header, 0, READBYTE))		
	{
		fprintf(stderr, "%s is not a PNG file!\n", filename);
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

	end_info = png_create_info_struct(png_ptr);
	if (!end_info)
	{
		fprintf(stderr, "Mermory allocation for end_ptr failed!\n");
		png_destroy_read_struct(&png_ptr, (png_infopp)NULL, (png_infopp)NULL);
		return 1;
	}

	if (setjmp(png_jmpbuf(png_ptr)))
	{
		png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
		fclose(fp);
		return 1;
	}

	png_set_sig_bytes(png_ptr, READBYTE);

	png_init_io(png_ptr, fp);

	png_read_info(png_ptr, info_ptr);
	/* Get PNG Image Info */
	width = png_get_image_width(png_ptr, info_ptr);
	height = png_get_image_height(png_ptr, info_ptr);
	bit_depth = png_get_bit_depth(png_ptr, info_ptr);
	color_type = png_get_color_type(png_ptr, info_ptr);
	channels = png_get_channels(png_ptr, info_ptr);

	/* Set CVIP Image Info */
	if (channels == 1 || channels == 2)
		cvipBands = 1;
	else if (channels == 3 || channels == 4)
		cvipBands = 3;
	cvipWidth = width;
	cvipHeight = height;
	cvipBitDepth = bit_depth;

	fprintf(stderr, "pngtocvip: loading %dx%d Portable Network Graphics(PNG) - %s.\n", cvipWidth, cvipHeight, filename);
	fprintf(stderr, "pngtocvip: %d bits per sample.\n", cvipBitDepth);
	fprintf(stderr, "pngtocvip: 1 sample per pixel.\n");

	if (color_type == PNG_COLOR_TYPE_GRAY || color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
		cvipColorSpace = GRAY_SCALE;
	else if (color_type == PNG_COLOR_TYPE_RGB || color_type == PNG_COLOR_TYPE_RGB_ALPHA)
		cvipColorSpace = RGB;

	temp = (Image *)malloc(cvipBands*sizeof(Image));
	for (bands = 0; bands < cvipBands; bands ++)
		temp[bands] = create_black(cvipWidth, cvipHeight);
	if(cvipBands == 3)
		cvipImage = assemble_bands(temp, 3);
	else
	{
		cvipImage = create_black(cvipWidth, cvipHeight);
		for (bands = 0; bands < cvipBands; bands ++)
			delete_Image(temp[bands]);
	}

	cvipImage->bands = cvipBands;
	cvipImage->color_space = cvipColorSpace;
	cvipImage->image_format = PNG;

	/* Read PNG Image */
	row_ptrs = (png_bytep *)malloc(height * sizeof(png_bytep));
	for (rows = 0; rows < height; rows ++)
	{
		row_ptrs[rows] = (png_bytep)png_malloc(png_ptr, png_get_rowbytes(png_ptr, info_ptr));	
	}

	png_read_image(png_ptr, row_ptrs);

	/* Write CVIP Image */
	for (bands = 0; bands < cvipBands; bands ++)
	{
		tempImage = getData_Image(cvipImage, bands);
		for (rows = 0; rows < height; rows ++)
		{
			colCounter = 0;
			for (cols = 0; cols < width*channels; cols ++)
			{
				if (bands == 0)
				{
					if ((cols % channels) == 0) //red
					{
						tempImage[rows][colCounter] = row_ptrs[rows][cols];
						colCounter ++;
					}
				}
				else if (bands == 1 && channels == 4)
				{
					if (((cols + 3) % channels) == 0) //green
					{
						tempImage[rows][colCounter] = row_ptrs[rows][cols];
						colCounter ++;
					}
				}
				else if (bands == 1 && channels == 3)
				{
					if (((cols + 2) % channels) == 0) //green
					{
						tempImage[rows][colCounter] = row_ptrs[rows][cols];
						colCounter ++;
					}
				}
				else if (bands == 2 && channels == 4)
				{
					if (((cols + 2) % channels) == 0) //blue
					{
							tempImage[rows][colCounter] = row_ptrs[rows][cols];
							colCounter ++;
					}
				}
				else if (bands == 2 && channels == 3)
				{
					if (((cols + 1) % channels) == 0) //blue
					{
							tempImage[rows][colCounter] = row_ptrs[rows][cols];
							colCounter ++;
					}
				}
			}
		}
	}

	png_read_end(png_ptr, info_ptr);

	for (rows = 0; rows < height; rows ++)
		free(row_ptrs[rows]);
	
	png_destroy_read_struct(&png_ptr, &info_ptr, png_infopp_NULL);

	fclose(fp);

	return cvipImage;
}