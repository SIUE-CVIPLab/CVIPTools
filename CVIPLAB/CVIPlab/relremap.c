/***************************************************************************
* ======================================================================
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* ======================================================================
*
*             File Name: relremap.c
*           Description: perform relative remapping procedure from type float to
*			 type byte.
*         Related Files: Imakefile, CVIPmap.h
*   Initial Coding Date: Mon Apr 12 14:46:15 CDT 1993
*           Portability: Standard (ANSI) C
*             Credit(s): Gregory Hance
*                        Southern Illinois University @ Edwardsville
*
** Copyright (C) 1993,1996 SIUE - Scott Umbaugh, Gregory Hance.
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
* $Log: relremap.c,v $
* Revision 1.17  1998/05/16 17:44:56  smakam
* included the casting to Image * in delete_Image functions
*
* Revision 1.16  1998/04/22 00:18:58  achomai
* 1.  Made the functions check for memory allocation failure or errors
*     from lower level functions.  If an error occured, all memory
*     blocks and structures allocated before that point will be freed.
* 2.  Made the functions use error_CVIP for printing error messages.
*
* Revision 1.15  1997/03/08 01:01:14  yawei
* Name Changes:
* 	BOOLEAN ==> CVIP_BOOLEAN
* 	FALSE ==> CVIP_NO
* 	TRUE ==> CVIP_YES
* 	BYTE ==> CVIP_BYTE
* 	SHORT ==> CVIP_SHORT
* 	INTEGER ==> CVIP_INTEGER
* 	FLOAT ==> CVIP_FLOAT
* 	DOUBLE ==> CVIP_DOUBLE
* 	TYPE ==> CVIP_TYPE
*
* Revision 1.15 2003/12/02
* Xiaohe Chen add debug information for remap_Image
* Revision 1.14  1996/09/27 22:54:04  sumbaug
* this is actuallly version 1.12, with a modification
* to the copyright in the header, adding 1996 (version 1.13 caused
* the color histeq, with V option, and transform filtering to bomb)
*
* Revision 1.12  1996/05/03  03:00:31  kluo
* fix the bug in remap_Image_C, which affect the view histogram
* in cviptcl/cvipwish
*
* Revision 1.11  1996/05/03  02:32:52  akjoele
* check file into RCS. This is done by Kun Luo for Arve,
* When I found the solution for the rwsi-beta version histeq problem.
* It is 9:30pm and I don't want to wait till tomorrow to see the
* result. So  I checked this file into RCS for arve.
*
* Revision 1.10  1996/02/15  19:35:14  akjoele
* Changed condRemap_Image so that it does a complete remap when the image
* is with has values more than 0.499 outside the specified range.  Previously,
* this limit was 1.000 outside the specified remap range.
*
* Revision 1.9  1995/12/26  01:30:21  kluo
* add view complex image histogram
*
* Revision 1.8  1995/12/26  01:03:16  kluo
* temporary check in for comparision with old version
*
* Revision 1.7  1995/09/19  22:04:00  kluo
* change history dptr
*
* Revision 1.6  1995/07/18  01:19:58  kluo
* fix equation used with REMAP
*
* Revision 1.5  1995/07/17  21:29:57  kluo
* check file in
*
* Revision 1.4  1995/03/07  22:58:36  luok
* fix bugs on  condRemap_Image. arguments, comparision.
*
* Revision 1.3  1995/03/07  00:52:36  luok
* change the remap so that it do a uniform remap instead of one band
* by one band
*
* Revision 1.2  1995/02/01  15:24:15  luok
* check file back into RCS
*
* Revision 1.1  1993/05/11  00:35:17  hanceg
* Initial revision
*
*
****************************************************************************/
#include "CVIPtoolkit.h"
#include "CVIPdef.h"
#include "float.h"

/****************************************************************
Name: remap_Image
Expanded Name: remapping
Parameters: <imageP> - pointer to Image structure
<dtype> - type of the data to be mapped to (e.g. CVIP_BYTE).
must be either as precise or less precise
than that of the input image.
<dmin> - minimum value in range (e.g. 0 )
<dmax> - maximum value in range (e.g. 255 )
Returns: pointer to a new instance of the Image <imageP>
that has been mapped into the range [<dmin>...<dmax>].
Description: performs remapping procedure in which the relative
size of each data band is maintained.
Diagnostics: none
Credit(s): Gregory Hance
Southern Illinois University @ Edwardsville
****************************************************************/

#define REMAPP(imgP_,mapP_,atype_,btype_,bands_,size_,factor_,minP_,dmin) { \
	register atype_ *aP_; \
	register btype_ *bP_; \
	register long j_ , i_; \
	for(j_=0; j_ < bands_; j_++) { \
	 	aP_ = imgP_[j_]; \
		bP_ = mapP_[j_]; \
		for(i_= 0; i_ < size_; i_++, aP_++, bP_++) \
			*bP_ = dmin + factor_*( *aP_ - minP_[j_] ) + 0.5 ; \
	} \
} \


Image *
remap_Image(
	const Image 	*imageP,
	CVIP_TYPE 	dtype,
	long	 	dmin,
	long	 	dmax
	)
{
	Image 		*mapP;
	CVIP_TYPE 	dt = getDataType_Image(imageP);
	HISTORY 	h_story, old_story;
	PACKET 		*oldpacket;
	const char 	*fn = "remap_Image";
	register 	int i, j;
	unsigned 	no_of_bands, imgsize, rows, cols;
	double 		*minP, *maxP, *spreadP, maxspread = 0, factor;
	void 		**imgvecP, **mapvecP;
	double		temp_min, temp_max;


	if (dtype > dt) {
		error_CVIP(fn,
			"output image must be of a less precise type than input");
		return NULL;
	}
	switch (dtype)
	{
	case CVIP_BYTE:
		printf("CVIPtools.Remap_Image: Image is remapped into CVIP_BYTE\n");
		break;
	case CVIP_SHORT:
		printf("CVIPtools.Remap_Image: Image is remapped into CVIP_SHORT\n");
		break;
	case CVIP_INTEGER:
		printf("CVIPtools.Remap_Image: Image is remapped into CVIP_SHORT\n");
		break;
	case CVIP_FLOAT:
		printf("CVIPtools.Remap_Image: Image is remapped into CVIP_FLOAT\n");
		break;
	case CVIP_DOUBLE:
		printf("Image is remapped into CVIP_DOUBLE\n");
		break;
	default:
		break;
	}
	no_of_bands = getNoOfBands_Image(imageP);
	rows = getNoOfRows_Image(imageP);
	cols = getNoOfCols_Image(imageP);
	imgsize = rows*cols;


	if (getDataFormat_Image(imageP) == COMPLEX) {
		imageP = duplicate_Image(imageP);
		if (imageP == NULL)
			return(NULL);

		for (i = 0; i < no_of_bands; i++)
		{
			setBand_Image(
				imageP,
				rect2pol_Matrix(getBand_Image(imageP, i), 1),
				i);
			if (getBand_Image(imageP, i) == NULL)
				break;
		}
		if (i != no_of_bands)
		{
			delete_Image((Image *)imageP);
			return(NULL);
		}
	}

	mapP = new_Image(getFileFormat_Image(imageP),
		getColorSpace_Image(imageP),
		no_of_bands, rows, cols, dtype, REAL);
	if (mapP == NULL)
	{
		if (getDataFormat_Image(imageP) == COMPLEX)
			delete_Image((Image *)imageP);
		return(NULL);
	}

	spreadP = (double *)malloc(no_of_bands*sizeof(double));
	minP = (double *)malloc(sizeof(double)*no_of_bands);
	maxP = (double *)malloc(sizeof(double)*no_of_bands);
	imgvecP = (void **)malloc(sizeof(void *)*no_of_bands);
	mapvecP = (void **)malloc(sizeof(void *)*no_of_bands);

	if ((spreadP == NULL) ||
		(minP == NULL) ||
		(maxP == NULL) ||
		(imgvecP == NULL) ||
		(mapvecP == NULL))
	{
		error_CVIP(fn, "Unable to allocate memory.\n");

		if (spreadP != NULL) free(spreadP);
		if (minP != NULL) free(minP);
		if (maxP != NULL) free(maxP);
		if (imgvecP != NULL) free(imgvecP);
		if (mapvecP != NULL) free(mapvecP);

		delete_Image(mapP);
		if (getDataFormat_Image(imageP) == COMPLEX)
			delete_Image((Image *)imageP);
		return(NULL);
	}
	getBandVector_Image((Image *)imageP, imgvecP);
	getBandVector_Image((Image *)mapP, mapvecP);

	/*
	** Copy history information to new image
	*/
	history_copy((Image*)imageP, mapP);

	for (i = 0; i < no_of_bands; i++) {
		minP[i] = findMinVal_Vector(imgvecP[i], imgsize, dt);
		maxP[i] = findMaxVal_Vector(imgvecP[i], imgsize, dt);
		if (i == 0) {
			temp_min = minP[i];
			temp_max = maxP[i];
		}
		else {
			if (temp_min>minP[i])
				temp_min = minP[i];
			if (temp_max<maxP[i])
				temp_max = maxP[i];
		}
		spreadP[i] = maxP[i] - minP[i];
	}
	maxspread = temp_max - temp_min;

	for (i = 0; i < no_of_bands; i++)
		minP[i] = temp_min;
	if (maxspread == 0.0)
		maxspread = dmax - dmin;

	factor = ((double)dmax - dmin) / maxspread;

	switch (dtype) {
	case CVIP_BYTE:
		switch (dt) {
		case CVIP_BYTE:
			REMAPP(imgvecP, mapvecP, byte, byte, no_of_bands, imgsize, factor, minP, dmin)
				break;
		case CVIP_SHORT:
			REMAPP(imgvecP, mapvecP, short, byte, no_of_bands, imgsize, factor, minP, dmin)
				break;
		case CVIP_INTEGER:
			REMAPP(imgvecP, mapvecP, int, byte, no_of_bands, imgsize, factor, minP, dmin)
				break;
		case CVIP_FLOAT:
			REMAPP(imgvecP, mapvecP, float, byte, no_of_bands, imgsize, factor, minP, dmin)
				break;
		case CVIP_DOUBLE:
			REMAPP(imgvecP, mapvecP, double, byte, no_of_bands, imgsize, factor, minP, dmin)
		}
		break;
	case CVIP_SHORT:
		switch (dt) {
		case CVIP_SHORT:
			REMAPP(imgvecP, mapvecP, short, short, no_of_bands, imgsize, factor, minP, dmin)
				break;
		case CVIP_INTEGER:
			REMAPP(imgvecP, mapvecP, int, short, no_of_bands, imgsize, factor, minP, dmin)
				break;
		case CVIP_FLOAT:
			REMAPP(imgvecP, mapvecP, float, short, no_of_bands, imgsize, factor, minP, dmin)
				break;
		case CVIP_DOUBLE:
			REMAPP(imgvecP, mapvecP, double, short, no_of_bands, imgsize, factor, minP, dmin)
		}
		break;
	case CVIP_INTEGER:
		switch (dt) {
		case CVIP_INTEGER:
			REMAPP(imgvecP, mapvecP, int, int, no_of_bands, imgsize, factor, minP, dmin)
				break;
		case CVIP_FLOAT:
			REMAPP(imgvecP, mapvecP, float, int, no_of_bands, imgsize, factor, minP, dmin)
				break;
		case CVIP_DOUBLE:
			REMAPP(imgvecP, mapvecP, double, int, no_of_bands, imgsize, factor, minP, dmin)
		}
		break;
	case CVIP_FLOAT:
		switch (dt) {
		case CVIP_FLOAT:
			REMAPP(imgvecP, mapvecP, float, float, no_of_bands, imgsize, factor, minP, dmin)
				break;
		case CVIP_DOUBLE:
			REMAPP(imgvecP, mapvecP, double, float, no_of_bands, imgsize, factor, minP, dmin)
		}
		break;
	case CVIP_DOUBLE:
		REMAPP(imgvecP, mapvecP, double, double, no_of_bands, imgsize, factor, minP, dmin)
			break;
	default:
		error_CVIP(fn, "Invalid data type.");
		delete_Image(mapP);
		mapP = NULL;
	}

	free(spreadP);
	free(minP);
	free(maxP);
	free(mapvecP);
	free(imgvecP);

	if (getDataFormat_Image(imageP) == COMPLEX)
		delete_Image((Image *)imageP);

	return mapP;
}

Image *
remap_Image_C(
	const Image 	*imageP,
	CVIP_TYPE 	dtype,
	long	 	dmin,
	long	 	dmax
	)
{
	Image 		*mapP;
	CVIP_TYPE 	dt = getDataType_Image(imageP);
	HISTORY 	h_story, old_story;
	PACKET 		*oldpacket;
	const char 	*fn = "remap_Image_C";
	register int	i, j;
	unsigned 	no_of_bands, imgsize, rows, cols;
	double 		*minP, *maxP, *minP_i, *maxP_i,
		*spreadP, maxspread = 0, factor;
	void 		**imgvecP, **imgvecP_i, **mapvecP, **mapvecP_i;
	double		temp_min, temp_max;


	if (dtype > dt) {
		error_CVIP(fn,
			"output image must be of a less precise type than input");
		return NULL;
	}

	switch (dtype)
	{
	case CVIP_BYTE:
		fprintf(stderr, "Image is remapped into CVIP_BYTE\n");
		break;
	case CVIP_SHORT:
		fprintf(stderr, "Image is remapped into CVIP_SHORT\n");
		break;
	case CVIP_INTEGER:
		fprintf(stderr, "Image is remapped into CVIP_INTEGER\n");
		break;
	case CVIP_FLOAT:
		fprintf(stderr, "Image is remapped into CVIP_FLOAT\n");
		break;
	case CVIP_DOUBLE:
		fprintf(stderr, "Image is remapped into CVIP_DOUBLE\n");
		break;
	default:
		break;
	}
	no_of_bands = getNoOfBands_Image(imageP);
	rows = getNoOfRows_Image(imageP);
	cols = getNoOfCols_Image(imageP);
	imgsize = rows*cols;

	mapP = new_Image(getFileFormat_Image(imageP),
		getColorSpace_Image(imageP),
		no_of_bands, rows, cols, dtype,
		getDataFormat_Image(imageP));

	if (mapP == NULL)
		return(NULL);
	spreadP = (double *)malloc(no_of_bands*sizeof(double));
	minP = (double *)malloc(sizeof(double)*no_of_bands);
	maxP = (double *)malloc(sizeof(double)*no_of_bands);
	minP_i = (double *)malloc(sizeof(double)*no_of_bands);
	maxP_i = (double *)malloc(sizeof(double)*no_of_bands);
	imgvecP = (void **)malloc(sizeof(void *)*no_of_bands);
	mapvecP = (void **)malloc(sizeof(void *)*no_of_bands);
	imgvecP_i = (void **)malloc(sizeof(void *)*no_of_bands);
	mapvecP_i = (void **)malloc(sizeof(void *)*no_of_bands);

	if ((spreadP == NULL) ||
		(minP == NULL) ||
		(maxP == NULL) ||
		(minP_i == NULL) ||
		(maxP_i == NULL) ||
		(imgvecP == NULL) ||
		(mapvecP == NULL) ||
		(imgvecP_i == NULL) ||
		(mapvecP_i == NULL))
	{
		error_CVIP(fn, "Unable to allocate memory.\n");
		if (spreadP != NULL) free(spreadP);
		if (minP != NULL) free(minP);
		if (maxP != NULL) free(maxP);
		if (minP_i != NULL) free(minP_i);
		if (maxP_i != NULL) free(maxP_i);
		if (imgvecP != NULL) free(imgvecP);
		if (mapvecP != NULL) free(mapvecP);
		if (imgvecP_i != NULL) free(imgvecP_i);
		if (mapvecP_i != NULL) free(mapvecP_i);
		delete_Image(mapP);
	}

	getBandVector_Image((Image *)imageP, imgvecP);
	getBandVector_Image((Image *)mapP, mapvecP);

	if (getDataFormat_Image(imageP) == COMPLEX) {
		for (i = 0; i<no_of_bands; i++) {
			imgvecP_i[i] = getImagRow_Image(imageP, 0, i);
			mapvecP_i[i] = getImagRow_Image(mapP, 0, i);
		}

	}

	/*
	** Copy history information to new image
	*/
	history_copy((Image*)imageP, mapP);

	for (i = 0; i < no_of_bands; i++) {
		minP[i] = findMinVal_Vector(imgvecP[i], imgsize, dt);
		maxP[i] = findMaxVal_Vector(imgvecP[i], imgsize, dt);
		if (getDataFormat_Image(imageP) == COMPLEX) {
			minP_i[i] = findMinVal_Vector(imgvecP_i[i], imgsize, dt);
			maxP_i[i] = findMaxVal_Vector(imgvecP_i[i], imgsize, dt);
			if (minP[i] > minP_i[i])
				minP[i] = minP_i[i];
			if (maxP[i] < maxP_i[i])
				maxP[i] = maxP_i[i];
		}
	}

	temp_max = maxP[0];
	temp_min = minP[0];
	for (i = 1; i < no_of_bands; i++) {
		if (temp_max < maxP[i])
			temp_max = maxP[i];
		if (temp_min > minP[i])
			temp_min = minP[i];
	}

	maxspread = temp_max - temp_min;

	for (i = 0; i < no_of_bands; i++)
		minP[i] = temp_min;
	if (maxspread == 0.0)
		maxspread = dmax - dmin;

	factor = ((double)dmax - dmin) / maxspread;

	switch (dtype) {
	case CVIP_BYTE:
		switch (dt) {
		case CVIP_BYTE:
			REMAPP(imgvecP, mapvecP, byte, byte, no_of_bands, imgsize, factor, minP, dmin)
				break;
		case CVIP_SHORT:
			REMAPP(imgvecP, mapvecP, short, byte, no_of_bands, imgsize, factor, minP, dmin)
				break;
		case CVIP_INTEGER:
			REMAPP(imgvecP, mapvecP, int, byte, no_of_bands, imgsize, factor, minP, dmin)
				break;
		case CVIP_FLOAT:
			REMAPP(imgvecP, mapvecP, float, byte, no_of_bands, imgsize, factor, minP, dmin)
				break;
		case CVIP_DOUBLE:
			REMAPP(imgvecP, mapvecP, double, byte, no_of_bands, imgsize, factor, minP, dmin)
		}
		break;
	case CVIP_SHORT:
		switch (dt) {
		case CVIP_SHORT:
			REMAPP(imgvecP, mapvecP, short, short, no_of_bands, imgsize, factor, minP, dmin)
				break;
		case CVIP_INTEGER:
			REMAPP(imgvecP, mapvecP, int, short, no_of_bands, imgsize, factor, minP, dmin)
				break;
		case CVIP_FLOAT:
			REMAPP(imgvecP, mapvecP, float, short, no_of_bands, imgsize, factor, minP, dmin)
				break;
		case CVIP_DOUBLE:
			REMAPP(imgvecP, mapvecP, double, short, no_of_bands, imgsize, factor, minP, dmin)
		}
		break;
	case CVIP_INTEGER:
		switch (dt) {
		case CVIP_INTEGER:
			REMAPP(imgvecP, mapvecP, int, int, no_of_bands, imgsize, factor, minP, dmin)
				break;
		case CVIP_FLOAT:
			REMAPP(imgvecP, mapvecP, float, int, no_of_bands, imgsize, factor, minP, dmin)
				break;
		case CVIP_DOUBLE:
			REMAPP(imgvecP, mapvecP, double, int, no_of_bands, imgsize, factor, minP, dmin)
		}
		break;
	case CVIP_FLOAT:
		switch (dt) {
		case CVIP_FLOAT:
			REMAPP(imgvecP, mapvecP, float, float, no_of_bands, imgsize, factor, minP, dmin)
				break;
		case CVIP_DOUBLE:
			REMAPP(imgvecP, mapvecP, double, float, no_of_bands, imgsize, factor, minP, dmin)
		}
		break;
	case CVIP_DOUBLE:
		REMAPP(imgvecP, mapvecP, double, double, no_of_bands, imgsize, factor, minP, dmin)
			break;
	default:
		error_CVIP(fn, "Invalid data type.\n");
		free(spreadP);
		free(minP); free(minP_i);
		free(maxP); free(maxP_i);
		free(mapvecP); free(mapvecP_i);
		free(imgvecP); free(imgvecP_i);
		delete_Image(mapP);
		return(NULL);
	}

	if (getDataFormat_Image(imageP) == COMPLEX) {
		switch (dtype) {
		case CVIP_BYTE:
			switch (dt) {
			case CVIP_BYTE:
				REMAPP(imgvecP_i, mapvecP_i, byte, byte, no_of_bands, imgsize, factor, minP, dmin)
					break;
			case CVIP_SHORT:
				REMAPP(imgvecP_i, mapvecP_i, short, byte, no_of_bands, imgsize, factor, minP, dmin)
					break;
			case CVIP_INTEGER:
				REMAPP(imgvecP_i, mapvecP_i, int, byte, no_of_bands, imgsize, factor, minP, dmin)
					break;
			case CVIP_FLOAT:
				REMAPP(imgvecP_i, mapvecP_i, float, byte, no_of_bands, imgsize, factor, minP, dmin)
					break;
			case CVIP_DOUBLE:
				REMAPP(imgvecP_i, mapvecP_i, double, byte, no_of_bands, imgsize, factor, minP, dmin)
			}
			break;
		case CVIP_SHORT:
			switch (dt) {
			case CVIP_SHORT:
				REMAPP(imgvecP_i, mapvecP_i, short, short, no_of_bands, imgsize, factor, minP, dmin)
					break;
			case CVIP_INTEGER:
				REMAPP(imgvecP_i, mapvecP_i, int, short, no_of_bands, imgsize, factor, minP, dmin)
					break;
			case CVIP_FLOAT:
				REMAPP(imgvecP_i, mapvecP_i, float, short, no_of_bands, imgsize, factor, minP, dmin)
					break;
			case CVIP_DOUBLE:
				REMAPP(imgvecP_i, mapvecP_i, double, short, no_of_bands, imgsize, factor, minP, dmin)
			}
			break;
		case CVIP_INTEGER:
			switch (dt) {
			case CVIP_INTEGER:
				REMAPP(imgvecP_i, mapvecP_i, int, int, no_of_bands, imgsize, factor, minP, dmin)
					break;
			case CVIP_FLOAT:
				REMAPP(imgvecP_i, mapvecP_i, float, int, no_of_bands, imgsize, factor, minP, dmin)
					break;
			case CVIP_DOUBLE:
				REMAPP(imgvecP_i, mapvecP_i, double, int, no_of_bands, imgsize, factor, minP, dmin)
			}
			break;
		case CVIP_FLOAT:
			switch (dt) {
			case CVIP_FLOAT:
				REMAPP(imgvecP_i, mapvecP_i, float, float, no_of_bands, imgsize, factor, minP, dmin)
					break;
			case CVIP_DOUBLE:
				REMAPP(imgvecP_i, mapvecP_i, double, float, no_of_bands, imgsize, factor, minP, dmin)
			}
			break;
		case CVIP_DOUBLE:
			REMAPP(imgvecP_i, mapvecP_i, double, double, no_of_bands, imgsize, factor, minP, dmin)
				break;
		default:
			error_CVIP(fn, "Invalid data type.\n");
			delete_Image(mapP);
			mapP = NULL;
		}
	}

	free(spreadP);
	free(minP); free(minP_i);
	free(maxP); free(maxP_i);
	free(mapvecP); free(mapvecP_i);
	free(imgvecP); free(imgvecP_i);


	return mapP;
}

Image *
condRemap_Image(
	const Image	*imgP,
	CVIP_TYPE 	dtype,
	unsigned  	min,
	unsigned  	max
	)
{
	Image		*outP;
	register int	i;
	double		*minP, *maxP, dmax, dmin;
	unsigned	bands;
	char		*fn = "condRemap_Image";

	bands = getNoOfBands_Image(imgP);
	minP = (double *)malloc(bands*sizeof(double));
	maxP = (double *)malloc(bands*sizeof(double));
	if ((minP == NULL) || (maxP == NULL))
	{
		error_CVIP(fn, "Unable to allocate memory.\n");
		if (minP != NULL) free(minP);
		if (maxP != NULL) free(maxP);
		return(NULL);
	}

	(void)findMinVal_Image(imgP, minP);
	(void)findMaxVal_Image(imgP, maxP);

	dmin = minP[0];
	dmax = maxP[0];

	for (i = 0; i < bands; i++) {
		dmin = MIN(minP[i], dmin);
		dmax = MAX(maxP[i], dmax);
	}

	if (dmin < 0.0 || ((dmin < ((double)min - 0.499)) &&
		(dmax >((double)max + 0.499))))
		outP = remap_Image(imgP, dtype, min, max);
	else
		if ((dmin < ((double)min - 0.499)) &&
			(!(dmax>((double)max + 0.499))))
			outP = remap_Image(imgP, dtype, min, ROUND(dmax));
		else
			if (!(dmin < ((double)min - 0.499)) &&
				(dmax>((double)max + 0.499)))
				outP = remap_Image(imgP, dtype, ROUND(dmin), max);
			else
			{
				outP = clone_Image(imgP, dtype);
				if (outP != NULL)
					(void) copy_Image(imgP, outP);
			}

	free(minP);
	free(maxP);

	return outP;
}

/****************************************************************
Name: trun_Image
Expanded Name: remapping
Parameters: <imageP> - pointer to Image structure
<dtype> - type of the data to be mapped to (e.g. CVIP_BYTE).
must be either as precise or less precise
than that of the input image.
<dmin> - minimum value in range (e.g. 0 )
<dmax> - maximum value in range (e.g. 255 )
Returns: pointer to a new instance of the Image <imageP>
that has been mapped into the range [<dmin>...<dmax>].
Description: performs remapping procedure in which the relative
size of each data band is maintained.
Diagnostics: none
Credit(s): Kun Luo
Southern Illinois University @ Edwardsville
****************************************************************/

#define TRUNCATE_(imgP_,mapP_,atype_,btype_,bands_,size_,maxP_,minP_) { \
	register atype_ *aP_; \
	register btype_ *bP_; \
	register long j_ , i_; \
	for(j_= 0 ; j_ < bands_ ; j_++) { \
	 	aP_ = imgP_[j_]; \
		bP_ = mapP_[j_]; \
		for( i_ = 0 ; i_ < size_ ; i_++, aP_++, bP_++){ \
			if((long) *aP_ <  minP_)  \
			      *bP_ = minP_; \
			else if((long) *aP_ >  maxP_) \
			      *bP_ = maxP_; \
		        else \
			      *bP_ = *aP_; \
		}\
	} \
} \


Image *
trun_Image(
	const Image 	*imageP,
	CVIP_TYPE 	dtype,
	long     	dmin,
	long    	dmax
	)
{
	Image 		*mapP;
	CVIP_TYPE 	dt = getDataType_Image(imageP);
	HISTORY 	h_story, old_story;
	PACKET 		*oldpacket;
	const char 	*fn = "remap_Image";
	register 	int i, j;
	unsigned 	no_of_bands, imgsize, rows, cols;
	void 		**imgvecP, **mapvecP;


	if (dtype > dt) {
		error_CVIP(fn,
			"output image must be of a less precise type than input");
		return NULL;
	}

	no_of_bands = getNoOfBands_Image(imageP);
	rows = getNoOfRows_Image(imageP);
	cols = getNoOfCols_Image(imageP);
	imgsize = rows*cols;

	imgvecP = (void **)malloc(sizeof(void *)*no_of_bands);
	mapvecP = (void **)malloc(sizeof(void *)*no_of_bands);
	if ((imgvecP == NULL) || (mapvecP == NULL))
	{
		error_CVIP(fn, "Unable to allocate memory.\n");
		if (imgvecP != NULL) free(imgvecP);
		if (mapvecP != NULL) free(mapvecP);
		return(NULL);
	}

	if (getDataFormat_Image(imageP) == COMPLEX) {
		imageP = duplicate_Image(imageP);
		for (i = 0; i < no_of_bands; i++)
		{
			setBand_Image(
				imageP,
				rect2pol_Matrix(getBand_Image(imageP, i), 1),
				i);
			if (getBand_Image(imageP, i) == NULL)
				break;
		}
		if (i != no_of_bands)
		{
			delete_Image((Image *)imageP);
			free(imgvecP);
			free(mapvecP);
			return(NULL);
		}
	}

	mapP = new_Image(getFileFormat_Image(imageP),
		getColorSpace_Image(imageP),
		no_of_bands, rows, cols, dtype, REAL);
	if (mapP == NULL)
	{
		if (getDataFormat_Image(imageP) == COMPLEX)
			delete_Image((Image *)imageP);
		free(imgvecP);
		free(mapvecP);
		return(NULL);
	}

	getBandVector_Image((Image *)imageP, imgvecP);
	getBandVector_Image((Image *)mapP, mapvecP);

	/*
	** Copy history information to new image
	*/
	history_copy((Image*)imageP, mapP);

	switch (dtype) {
	case CVIP_BYTE:
		switch (dt) {
		case CVIP_BYTE:
			TRUNCATE_(imgvecP, mapvecP, byte, byte, no_of_bands, imgsize, dmax, dmin)
				break;
		case CVIP_SHORT:
			TRUNCATE_(imgvecP, mapvecP, short, byte, no_of_bands, imgsize, dmax, dmin)
				break;
		case CVIP_INTEGER:
			TRUNCATE_(imgvecP, mapvecP, int, byte, no_of_bands, imgsize, dmax, dmin)
				break;
		case CVIP_FLOAT:
			TRUNCATE_(imgvecP, mapvecP, float, byte, no_of_bands, imgsize, dmax, dmin)
				break;
		case CVIP_DOUBLE:
			TRUNCATE_(imgvecP, mapvecP, double, byte, no_of_bands, imgsize, dmax, dmin)
		}
		break;
	case CVIP_SHORT:
		switch (dt) {
		case CVIP_SHORT:
			TRUNCATE_(imgvecP, mapvecP, short, short, no_of_bands, imgsize, dmax, dmin)
				break;
		case CVIP_INTEGER:
			TRUNCATE_(imgvecP, mapvecP, int, short, no_of_bands, imgsize, dmax, dmin)
				break;
		case CVIP_FLOAT:
			TRUNCATE_(imgvecP, mapvecP, float, short, no_of_bands, imgsize, dmax, dmin)
				break;
		case CVIP_DOUBLE:
			TRUNCATE_(imgvecP, mapvecP, double, short, no_of_bands, imgsize, dmax, dmin)
		}
		break;
	case CVIP_INTEGER:
		switch (dt) {
		case CVIP_INTEGER:
			TRUNCATE_(imgvecP, mapvecP, int, int, no_of_bands, imgsize, dmax, dmin)
				break;
		case CVIP_FLOAT:
			TRUNCATE_(imgvecP, mapvecP, float, int, no_of_bands, imgsize, dmax, dmin)
				break;
		case CVIP_DOUBLE:
			TRUNCATE_(imgvecP, mapvecP, double, int, no_of_bands, imgsize, dmax, dmin)
		}
		break;
	case CVIP_FLOAT:
		switch (dt) {
		case CVIP_FLOAT:
			TRUNCATE_(imgvecP, mapvecP, float, float, no_of_bands, imgsize, dmax, dmin)
				break;
		case CVIP_DOUBLE:
			TRUNCATE_(imgvecP, mapvecP, double, float, no_of_bands, imgsize, dmax, dmin)
		}
		break;
	case CVIP_DOUBLE:
		TRUNCATE_(imgvecP, mapvecP, double, double, no_of_bands, imgsize, dmax, dmin)
			break;
	default:
		error_CVIP(fn, "Invalid data type.\n");
		delete_Image(mapP);
		mapP = NULL;
	}

	free(mapvecP);
	free(imgvecP);

	if (getDataFormat_Image(imageP) == COMPLEX)
		delete_Image((Image *)imageP);

	return mapP;
}

/*
* truncate_vals - Truncate image values to be between 0 and 255
*
* Description: This function takes any input image and truncates its
* image values so that any number below min is set to 0, and any number
* above max is set to max.
*/
/*
void truncate_vals(Image *img, float min, float max) {
int i, j, k;

for(i=0; i<img->bands; i++) {
switch(
}
}
*/

