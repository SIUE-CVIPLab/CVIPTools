/***************************************************************************
* **********************************************************************
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* **********************************************************************
*
*             File Name: pct_median.c
*           Description: 
*         Related Files: 
*   Initial Coding Date: Fri Jan  3 15:41:30 CST 1997
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
** $Log: pct_median.c,v $
**
** revision 1.4 2006/07/20  Wenjun(Evan) Bian
** the way invoking remap_Image() causes memory leakage.
**
** Revision 1.3  1997/03/08 17:01:32  yawei
** Swaped CVIP_YES and CVIP_NO
**
** Revision 1.2  1997/03/08 00:44:50  yawei
** Name Changes:
** 	BOOLEAN ==> CVIP_BOOLEAN
** 	FALSE ==> CVIP_YES
** 	TRUE ==> CVIP_NO
** 	BYTE ==> CVIP_BYTE
** 	SHORT ==> CVIP_SHORT
** 	INTEGER ==> CVIP_INTEGER
** 	FLOAT ==> CVIP_FLOAT
** 	DOUBLE ==> CVIP_DOUBLE
** 	TYPE ==> CVIP_TYPE
**
** Revision 1.1  1997/01/03 21:41:56  yawei
** Initial revision
**
*
****************************************************************************/
#include <CVIPtoolkit.h>
#include <CVIPconvert.h>
#include <CVIPmap.h>
#include <CVIPsegment.h>
#include <pct.h>

Image *pct_median_segment(Image *imageP, unsigned colors) {
	CVIP_TYPE     dt;
	FORMAT format;
	Image *tempImgP, *temmp;
	Color bg = {0, 0, 0};

	byte **byteData;
	float **floatData, factor;

	double min, max, temp;
	unsigned    no_of_bands, imgsize, rows, cols, r, c;
	void     **imgvecP = NULL;
	int i;

	format = getDataFormat_Image(imageP);

	if (format == COMPLEX) {
		perror_CVIP("pct_median_segment", "COMPLEX datatype not supported.");
		delete_Image (imageP);
		return (Image *)NULL;
	}

	no_of_bands = getNoOfBands_Image(imageP);
	rows = getNoOfRows_Image(imageP);
	cols = getNoOfCols_Image(imageP);
	imgsize = rows*cols;

	/* PCT */
	if ( (imageP = pct(imageP, CVIP_NO, (float *)NULL)) == (Image *) NULL)
		return (Image *)NULL; 
	dt = getDataType_Image(imageP);

	/* Fine the Min and Max of the PCT Image */
	imgvecP = (void **) malloc(sizeof(void *)*no_of_bands);
	getBandVector_Image((Image *)imageP, imgvecP);

	for (i = 0; i < no_of_bands; i++) {
		temp = findMinVal_Vector(imgvecP[i], imgsize, dt);
			if (!i) min = temp;
			else min = (min < temp) ? min : temp;
		temp  = findMaxVal_Vector(imgvecP[i], imgsize, dt);
			if (!i) max = temp;
			else max = (max < temp) ? temp : max;
	}
	free(imgvecP);
	factor = (max - min) / 255;
/*	printf("min=%f, max = %f\n", min, max); */

	/* make a copy */
	tempImgP = duplicate_Image(imageP);
	if (!tempImgP) {
		delete_Image(imageP);
		return (Image *)NULL;
	}
		
	/* remap to CVIP_BYTE */
	//old code 
	//imageP = remap_Image(imageP, CVIP_BYTE, 0, 255);   
	//new code for correcting memeory leak.
	temmp = remap_Image(imageP, CVIP_BYTE, 0, 255);
	delete_Image(imageP);
    imageP=temmp;
		
	if (!imageP) return (Image *)NULL;

	/* Median cut */
	imageP = median_cut_segment(imageP, colors, CVIP_NO, bg);
	if (!imageP) return (Image *)NULL;

	/* map back */
	for (i = 0; i < no_of_bands; i++) {
		byteData = getData_Image(imageP, i);
		floatData = getData_Image(tempImgP, i);
		for (r = 0; r < rows; r++)
			for (c = 0; c < cols; c++) 
				floatData[r][c] = (float) byteData[r][c] * factor + min;
	}

	/* delete the image */
	delete_Image(imageP);

	imageP = ipct(tempImgP, CVIP_NO, (float *)NULL);

	return imageP;

	
}
