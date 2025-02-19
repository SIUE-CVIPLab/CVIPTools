/***************************************************************************
* **********************************************************************
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* **********************************************************************
*
*             File Name: arithlogic.c
*           Description: 
*         Related Files: 
*   Initial Coding Date: Wed Mar 26 14:02:49 CST 1997
*           Portability: Standard (ANSI) C
*            References:
*             Author(s): Yansheng Wei (not me)
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
** $Log: arithlogic.c,v $
** Revision 1.14  1998/04/21 22:44:14  achomai
** Made all functions use error_CVIP to print error messages.
** Made all functions delete the input image(s) if they failed.
** Made all functions check the result of the Matrix library functions.
**
** Revision 1.13  1997/06/03 02:26:07  yawei
** fixed image multiply bug
**
** Revision 1.12  1997/03/28 18:27:27  yawei
** added header
**
*
****************************************************************************/
#include "CVIPtoolkit.h"
#include "CVIPimage.h"
#include "CVIPmatrix.h"
#include "CVIParithlogic.h"
#include "CVIPdef.h"
#include "CVIPtransform.h"


void which_zero_pad(Image *, Image *);
 
Image	*divide_Image(	Image		*inputImage1,
			Image		*inputImage2, 
			CVIP_BOOLEAN 	zero2num){
	Matrix 		*image1,*image2,*outimage;/* 2-d matrix data pointer */
	int 		y,		/* row index */
			x, 		/* column index */
			bands;		/* band index */
			
	unsigned int 	rows1,rows2, 	/* number of rows in image */
			cols1,cols2,	/* number of columns in image */
			no_bands1,no_bands2;	/* number of image bands */
	char		*fn = "divide_Image";

	no_bands1 = getNoOfBands_Image(inputImage1);
	no_bands2 = getNoOfBands_Image(inputImage2);
	if(no_bands1 != no_bands2) {
		error_CVIP(fn,"Different number of bands.\n");
		delete_Image(inputImage1);
		delete_Image(inputImage2);
		return NULL;
	}
	if(	inputImage1->bandP[0]->data_format != 
		inputImage2->bandP[0]->data_format){
		error_CVIP(fn,"Different data format.\n");
		delete_Image(inputImage1);
		delete_Image(inputImage2);
		return NULL;
	}

	if(getDataType_Image(inputImage1)!=CVIP_FLOAT)
		cast_Image(inputImage1, CVIP_FLOAT);
	if(getDataType_Image(inputImage1)!=CVIP_FLOAT)
		error_CVIP(fn,"Unable to cast the image.\n");
	if(getDataType_Image(inputImage2)!=CVIP_FLOAT)
		cast_Image(inputImage2, CVIP_FLOAT);
	if(getDataType_Image(inputImage2)!=CVIP_FLOAT)
		error_CVIP(fn,"Unable to cast the image.\n");

	which_zero_pad(inputImage1, inputImage2);

	for(bands=0; bands < no_bands1; bands++) {
		/*
		** reference each band of image data in 2-d matrix form;
		** which is used for reading and writing the pixel values
		*/
		image1 = inputImage1->bandP[bands];
		image2 = inputImage2->bandP[bands];
		if (zero2num == CVIP_YES) 
			divide_Matrix(&outimage, image1,image2,image1);
		else
			divide_Matrix(&outimage, image1,image2,image2);
		if(outimage == NULL)
		break;
		inputImage1->bandP[bands] = outimage;
		delete_Matrix(image1);
	}
	if(bands != no_bands1)
	{
		delete_Image(inputImage1);
		inputImage1 = NULL;
	}
	delete_Image(inputImage2);
	return inputImage1;
}

Image	*multiply_Image(	Image	*inputImage1,
					Image	*inputImage2){
	Matrix		*image1,*image2; /* 2-d matrix data pointer */
	int 		y,		/* row index */
			x, 		/* column index */
			bands;		/* band index */
			
	unsigned int	no_bands1,no_bands2;	/* number of image bands */
	char		*fn = "multiply_Image";
	
	no_bands1 = getNoOfBands_Image(inputImage1);
	no_bands2 = getNoOfBands_Image(inputImage2);
	if(no_bands1 != no_bands2) {
		error_CVIP(fn,"Different number of bands.\n");
		delete_Image(inputImage1);
		delete_Image(inputImage2);
		return NULL;
	}

	if(getDataType_Image(inputImage1)!=CVIP_FLOAT)
		cast_Image(inputImage1, CVIP_FLOAT);
	if(getDataType_Image(inputImage1)!=CVIP_FLOAT)
		error_CVIP(fn,"Unable to cast the image.\n");
	if(getDataType_Image(inputImage2)!=CVIP_FLOAT)
		cast_Image(inputImage2, CVIP_FLOAT);
	if(getDataType_Image(inputImage2)!=CVIP_FLOAT)
		error_CVIP(fn,"Unable to cast the image.\n");
	which_zero_pad(inputImage1, inputImage2);

	for(bands=0; bands < no_bands1; bands++) {
		/*
		** reference each band of image data in 2-d matrix form;
		** which is used for reading and writing the pixel values
		*/
  		image1 = inputImage1->bandP[bands];
  		image2 = inputImage2->bandP[bands];
		inputImage1->bandP[bands] = multPWise_Matrix(image1,image2);
		if(inputImage1->bandP[bands] == NULL)
		{
			inputImage1->bandP[bands] = image1;
			break;
		}
		delete_Matrix(image1);
	}
	if(bands != no_bands1)
	{
		delete_Image(inputImage1);
		inputImage1 = NULL;
	}
	delete_Image(inputImage2);
	return inputImage1;
}

Image	*add_Image(	Image	*inputImage1,
			Image	*inputImage2){
	Matrix 		*image1,*image2; 	/* 2-d matrix data pointer */
	int		bands;		/* band index */
	unsigned int	no_bands1,no_bands2;	/* number of image bands */
	char		*fn = "add_Image";
	
	no_bands1 = getNoOfBands_Image(inputImage1);
	no_bands2 = getNoOfBands_Image(inputImage2);
	if(no_bands1 != no_bands2) {
		error_CVIP(fn,"Different number of bands.\n");
		delete_Image(inputImage1);
		delete_Image(inputImage2);
		return NULL;
	}


	if(getDataType_Image(inputImage1)!=CVIP_FLOAT)
		cast_Image(inputImage1, CVIP_FLOAT);
	if(getDataType_Image(inputImage1)!=CVIP_FLOAT)
		error_CVIP(fn,"Unable to cast the image.\n");
	if(getDataType_Image(inputImage2)!=CVIP_FLOAT)
		cast_Image(inputImage2, CVIP_FLOAT);
	if(getDataType_Image(inputImage2)!=CVIP_FLOAT)
		error_CVIP(fn,"Unable to cast the image.\n");
	which_zero_pad(inputImage1, inputImage2);

	for(bands=0; bands < no_bands1; bands++) {
		/*
		** reference each band of image data in 2-d matrix form;
		** which is used for reading and writing the pixel values
		*/
  		image1 = inputImage1->bandP[bands];
  		image2 = inputImage2->bandP[bands];
		inputImage1->bandP[bands] = add_Matrix(image1,image2);
		if(inputImage1->bandP[bands] == NULL)
		{
			inputImage1->bandP[bands] = image1;
			break;
		}
		delete_Matrix(image1);
	}
	if(bands != no_bands1)
	{
		delete_Image(inputImage1);
		inputImage1 = NULL;
	}
	delete_Image(inputImage2);
	return inputImage1;
}

Image	*subtract_Image(	Image	*inputImage1,
				Image	*inputImage2){
	Matrix 		*image1,*image2; 	/* 2-d matrix data pointer */
	int		bands;		/* band index */
	unsigned int	no_bands1,no_bands2;	/* number of image bands */
	char		*fn = "subtract_Image";

	no_bands1 = getNoOfBands_Image(inputImage1);
	no_bands2 = getNoOfBands_Image(inputImage2);
	if(no_bands1 != no_bands2) {
		error_CVIP(fn,"Different number of bands.\n");
		delete_Image(inputImage1);
		delete_Image(inputImage2);
		return NULL;
	}

	if(getDataType_Image(inputImage1)!=CVIP_FLOAT)
		cast_Image(inputImage1, CVIP_FLOAT);
	if(getDataType_Image(inputImage1)!=CVIP_FLOAT)
		error_CVIP(fn,"Unable to cast the image.\n");
	if(getDataType_Image(inputImage2)!=CVIP_FLOAT)
		cast_Image(inputImage2, CVIP_FLOAT);
	if(getDataType_Image(inputImage2)!=CVIP_FLOAT)
		error_CVIP(fn,"Unable to cast the image.\n");
	which_zero_pad(inputImage1, inputImage2);

	for(bands=0; bands < no_bands1; bands++) {
		/*
		** reference each band of image data in 2-d matrix form;
		** which is used for reading and writing the pixel values
		*/
  		image1 = inputImage1->bandP[bands];
  		image2 = inputImage2->bandP[bands];
		inputImage1->bandP[bands] = sub_Matrix(image1,image2);
		if(inputImage1->bandP[bands] == NULL)
		{
			inputImage1->bandP[bands] = image1;
			break;
		}
		delete_Matrix(image1);
	}
	if(bands != no_bands1)
	{
		delete_Image(inputImage1);
		inputImage1 = NULL;
	}
	delete_Image(inputImage2);
	return inputImage1;
}

Image	*and_Image(	Image	*inputImage1,
			Image	*inputImage2){
	byte 		**image1,**image2; 	/* 2-d matrix data pointer */
	int 		y,		/* row index */
			x, 		/* column index */
			bands;		/* band index */
			
	unsigned int 	rows1,rows2, 	/* number of rows in image */
			cols1,cols2,	/* number of columns in image */
			no_bands1,no_bands2;	/* number of image bands */
	char		*fn = "and_Image";

	rows1 = getNoOfRows_Image(inputImage1);
	rows2 = getNoOfRows_Image(inputImage2);
	cols1 = getNoOfCols_Image(inputImage1);
	cols2 = getNoOfCols_Image(inputImage2);
	no_bands1 = getNoOfBands_Image(inputImage1);
	no_bands2 = getNoOfBands_Image(inputImage2);
	if(no_bands1 != no_bands2) {
		error_CVIP(fn,"Different number of bands.\n");
		delete_Image(inputImage1);
		delete_Image(inputImage2);
		return NULL;
	}

	which_zero_pad(inputImage1, inputImage2);

        if(rows1<rows2) rows1=rows2;
        if(cols1<cols2) cols1=cols2;

	for(bands=0; bands < no_bands1; bands++) {
		/*
		** reference each band of image data in 2-d matrix form;
		** which is used for reading and writing the pixel values
		*/
  		image1 = getData_Image(inputImage1, bands);
  		image2 = getData_Image(inputImage2, bands);
  		for(y=0; y < rows1; y++) {
     			for(x=0; x < cols1; x++) {
            			image1[y][x] = image1[y][x]&image2[y][x];
         		}
     		}
	}
	delete_Image(inputImage2);
	return inputImage1;
}

Image	*or_Image(	Image	*inputImage1,
			Image	*inputImage2){
	byte 		**image1,**image2; 	/* 2-d matrix data pointer */
	int 		y,		/* row index */
			x, 		/* column index */
			bands;		/* band index */
			
	unsigned int 	rows1,rows2, 	/* number of rows in image */
			cols1,cols2,	/* number of columns in image */
			no_bands1,no_bands2;	/* number of image bands */
	char		*fn = "or_Image";

	rows1 = getNoOfRows_Image(inputImage1);
	rows2 = getNoOfRows_Image(inputImage2);
	cols1 = getNoOfCols_Image(inputImage1);
	cols2 = getNoOfCols_Image(inputImage2);
	no_bands1 = getNoOfBands_Image(inputImage1);
	no_bands2 = getNoOfBands_Image(inputImage2);
	if(no_bands1 != no_bands2) {
		error_CVIP(fn,"Different number of bands.\n");
		delete_Image(inputImage1);
		delete_Image(inputImage2);
		return NULL;
	}

	which_zero_pad(inputImage1, inputImage2);

        if(rows1<rows2) rows1=rows2;
        if(cols1<cols2) cols1=cols2;

	for(bands=0; bands < no_bands1; bands++) {
		/*
		** reference each band of image data in 2-d matrix form;
		** which is used for reading and writing the pixel values
		*/
  		image1 = getData_Image(inputImage1, bands);
  		image2 = getData_Image(inputImage2, bands);
  		for(y=0; y < rows1; y++) {
     			for(x=0; x < cols1; x++) {
            			image1[y][x] = image1[y][x]|image2[y][x];
         		}
     		}
	}
	delete_Image(inputImage2);
	return inputImage1;
}

Image	*xor_Image(	Image	*inputImage1,
			Image	*inputImage2){
	byte 		**image1,**image2; 	/* 2-d matrix data pointer */
	int 		y,		/* row index */
			x, 		/* column index */
			bands;		/* band index */
			
	unsigned int 	rows1,rows2, 	/* number of rows in image */
			cols1,cols2,	/* number of columns in image */
			no_bands1,no_bands2;	/* number of image bands */
	char		*fn = "xor_Image";
	
	rows1 = getNoOfRows_Image(inputImage1);
	rows2 = getNoOfRows_Image(inputImage2);
	cols1 = getNoOfCols_Image(inputImage1);
	cols2 = getNoOfCols_Image(inputImage2);
	no_bands1 = getNoOfBands_Image(inputImage1);
	no_bands2 = getNoOfBands_Image(inputImage2);
	if(no_bands1 != no_bands2) {
		error_CVIP(fn,"Different number of bands.\n");
		delete_Image(inputImage1);
		delete_Image(inputImage2);
		return NULL;
	}

	which_zero_pad(inputImage1, inputImage2);

        if(rows1<rows2) rows1=rows2;
        if(cols1<cols2) cols1=cols2;


	for(bands=0; bands < no_bands1; bands++) {
		/*
		** reference each band of image data in 2-d matrix form;
		** which is used for reading and writing the pixel values
		*/
  		image1 = getData_Image(inputImage1, bands);
  		image2 = getData_Image(inputImage2, bands);
  		for(y=0; y < rows1; y++) {
     			for(x=0; x < cols1; x++) {
            			image1[y][x] = image1[y][x]^image2[y][x];
         		}
     		}
	}
	delete_Image(inputImage2);
	return inputImage1;
}

Image	*not_Image(Image	*inputImage){
	byte 		**image; 	/* 2-d matrix data pointer */
	int 		y,		/* row index */
			x, 		/* column index */
			bands;		/* band index */
			
	unsigned int 	rows,	 	/* number of rows in image */
			cols,		/* number of columns in image */
			no_bands;	/* number of image bands */

	rows = getNoOfRows_Image(inputImage);

	cols = getNoOfCols_Image(inputImage);

	no_bands = getNoOfBands_Image(inputImage);

	for(bands=0; bands < no_bands; bands++) {
  		image = getData_Image(inputImage, bands);
  		for(y=0; y < rows; y++) {
     			for(x=0; x < cols; x++) {
            			image[y][x] = ~image[y][x];
         		}
     		}
	}
	return inputImage;
}
/* Compare the sizes of two images, then decide which one to zero-pad
 * and call the zero_pad function */
void	which_zero_pad(	Image	*Im1,
			Image	*Im2) {
	int row1,row2,col1,col2;
	int req=0,ceq=0;

	row1=Im1->image_ptr[0]->rows;
	row2=Im2->image_ptr[0]->rows;
	col1=Im1->image_ptr[0]->cols;
	col2=Im2->image_ptr[0]->cols;

	if(row1 == row2 && col1 == col2) return;

	if(row1==row2) {
		req=1;
	}
	if(col1==col2) {
		ceq=1;
	}
	if(!req && ceq) {
		if(row1<row2) zero_pad(Im1,row2,col1);
		else zero_pad(Im2,row1,col1);
	}
	else if(!ceq && req) {
		if(col1<col2) zero_pad(Im1,row2,col2);
		else zero_pad(Im2,row2,col1);
	}
	else { /* ceq && req */
		if(col1<col2) {
			if(row1<row2) zero_pad(Im1,row2,col2);
			else {
				zero_pad(Im1,row1,col2);
				zero_pad(Im2,row1,col2);
				return;
			}
		}
		else {
			if(row1<row2) {
				zero_pad(Im1,row2,col1);
				zero_pad(Im2,row2,col1);
			}
			else {
				zero_pad(Im2,row1,col1);
			}
		}
	}
	return;
}
