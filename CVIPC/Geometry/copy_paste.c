/***************************************************************************
* **********************************************************************
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* **********************************************************************
*
*             File Name: copy_paste.c
*           Description: cross image copy_paste function
*         Related Files: 
*   Initial Coding Date: Thu Mar 20 19:09:35 CST 1997
*           Portability: Standard (ANSI) C
*            References:
*             Author(s): Yansheng Wei
*                        Southern Illinois University @ Edwardsville
*
** Copyright (C) 1996 SIUE - by Scott Umbaugh and Yansheng Wei.
**
** Permission to use, copy, modify, and distribute this software and its
** documentation for any purpose and without fee is hereby granted, provided
** that the above copyright notice appear in all copies and that both that
** copyright notice and this permission notice appear in supporting
** documentation.  This software is provided "as is" without express or
** implied warranty.
**
* RCS (Revision Control System) Information
* ...Added automatically by RCS 
*
** $Log: copy_paste.c,v $
** Revision 1.3  1997/04/14 19:12:23  yawei
** adjusted boundary check
**
** Revision 1.2  1997/03/21 23:46:59  yawei
** fixed size error
**
** Revision 1.1  1997/03/21 01:10:23  yawei
** Initial revision
**
*
****************************************************************************/

#include <limits.h>
#include <CVIPmatrix.h>
#include <CVIPimage.h>
#include <CVIPgeometry.h>
#include <CVIPmap.h>

Image *copy_paste(
	Image *srcImg, Image *destImg, 
	unsigned start_r, unsigned start_c, unsigned height, unsigned width,
	unsigned dest_r, unsigned dest_c, CVIP_BOOLEAN transparent)
{
	Image *cropImg, *resultImg = destImg, *tempImg;
	int rows, cols, bands, no_of_bands,
		 rows1, cols1, bands1, band, r, c;
	FORMAT format, format1;
	float **data_real, **data1_real,
			**data_comp, **data1_comp;
	CVIP_TYPE dt, dt1;

	rows =  getNoOfRows_Image(srcImg);
	cols =  getNoOfCols_Image(srcImg);
	bands = getNoOfBands_Image(srcImg);
	format = getDataFormat_Image(srcImg);
	dt = getDataType_Image(srcImg);

	rows1 =  getNoOfRows_Image(destImg);
	cols1 =  getNoOfCols_Image(destImg);
	bands1 = getNoOfBands_Image(destImg);
	format1 = getDataFormat_Image(destImg);
	dt1 = getDataType_Image(destImg);

	if (destImg == srcImg) resultImg = duplicate_Image(srcImg);

	/* size check */
	if (height * width <= 0) {
		perror_CVIP("copy_paste",
			"positive values required for the subimage size");	
		delete_Image(srcImg);
		delete_Image(resultImg);
	}

	if (start_r + height > rows || dest_r + height > rows1) {
		perror_CVIP("copy_paste", "required subimage too big, clipped.");	
		height = (rows - start_r > rows1 - dest_r) ? rows1-dest_r:rows-start_r;
		height--;
	}
	if (start_c + width > cols || dest_c + width > cols1) {
		perror_CVIP("copy_paste", "required subimage too big, clipped.");	
		width = (cols - start_c > cols1 - dest_c) ? cols1-dest_c:cols-start_c;
		width--;
	}

	/* crop image */
	cropImg = crop(srcImg, start_r, start_c, height, width);
	if (cropImg == (Image *)NULL) {
		perror_CVIP("copy_paste", "cut image failed.");	
		delete_Image(resultImg);
		return (Image *)NULL;
	}
	/*delete_Image(srcImg);  */

	/* cast to float */
	if (dt < CVIP_FLOAT) cast_Image(cropImg, CVIP_FLOAT);
	if (dt1 < CVIP_FLOAT) cast_Image(resultImg, CVIP_FLOAT);

	/* pasting */
	for (band = 0; band < bands1; band++) {
		data_real = (float **)getRealData_Image(cropImg, band*bands/bands1);
		data1_real = (float **)getRealData_Image(resultImg, band);
		if (transparent == CVIP_YES)  {
			for (r = 0; r < height; r++) 
				for (c = 0; c < width; c++) 
					data1_real[r+dest_r][c+dest_c] += data_real[r][c];
		} else {
			for (r = 0; r < height; r++) 
				for (c = 0; c < width; c++) 
					data1_real[r+dest_r][c+dest_c] = data_real[r][c];
		}
			
		if (format1 == COMPLEX) {
			data1_comp = (float **)getImagData_Image(resultImg, band);
			if (format == COMPLEX) 
				data_comp = (float **)getImagData_Image(cropImg, band*bands/bands1);
			else 
				data_comp = (float **)getRealData_Image(cropImg, band*bands/bands1);

			if (transparent == CVIP_YES)  {
				for (r = 0; r < height; r++) 
					for (c = 0; c < width; c++) 
						data1_comp[r+dest_r][c+dest_c] += data_comp[r][c];
			} else {
				for (r = 0; r < height; r++) 
					for (c = 0; c < width; c++) 
						data1_comp[r+dest_r][c+dest_c] = data_comp[r][c];
			}
		}
		
	}
	delete_Image(cropImg);

	/* mapping back */
	if (dt1 != CVIP_FLOAT)  {
		tempImg = resultImg;
		switch (dt1) {
			case CVIP_BYTE: 
				resultImg = remap_Image((const Image*) tempImg,
					CVIP_BYTE, 0, 255);
				break;
			case CVIP_SHORT: 
				resultImg = remap_Image((const Image*) tempImg,
					CVIP_SHORT, SHRT_MIN,SHRT_MAX);
				break;
			case CVIP_INTEGER: 
				resultImg = remap_Image((const Image*) tempImg,
					CVIP_INTEGER, LONG_MIN,LONG_MAX);
				break;
			default: 
				perror_CVIP("copy_paste", "image datatype mismatch.");
				delete_Image(resultImg);
				return (Image *)NULL;
		}
		delete_Image(tempImg);
	}
	return  resultImg;
}

