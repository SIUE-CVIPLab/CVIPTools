/***************************************************************************
* =========================================================================
*
*   Computer Vision and Image Processing Lab - Dr. Scott Umbaugh SIUE 
* 
* =========================================================================
*
*             File Name: prewitt_filter.c 
*            Name: Hari Krishna Akkineni  
*            Portability: Standard (ANSI) C*                         
**      Copyright (c) 2009, SIUE - Scott Umbaugh
****************************************************************************/

/****************************************************************************/

/* Define Preprocessor statements */
#include "CVIPimage.h"
#include "CVIPdef.h"
#include "CVIPfs.h" 
#include <limits.h>
#include "CVIPmap.h"
#include <math.h>

static Image *prewitt_edge(Image *cvipImage2, Image *directionImage, int size);
static void threshold_image(Image *inputImage,int thres);
static MATRIX *get_mask(MASK_TYPE type, int dimension);

Image *prewitt_filter(Image *inputImage, Image *dirImage, int mask_choice, 
	int mask_size, int keep_dc, int threshold)
{
	MATRIX *KERNEL;
	MATRIX *temp_MATRIX;
	KIRSCH_MASK *masks;
	int dimension;
	int bias_choice = 0;
	int warning = 0;
	Image *cvipImage1, *direction_Image, *magImage;
	direction_Image = new_Image(inputImage->image_format, inputImage->color_space, inputImage->bands,
		getNoOfRows_Image(inputImage),getNoOfCols_Image(inputImage), CVIP_FLOAT, REAL);

	/*convole filter takes only short ot byte inputs*/
	
	if(inputImage->bandP[0]->data_type < CVIP_SHORT)
	{
		cast_Image(inputImage,CVIP_SHORT);
		fprintf(stderr,"Image is cast into CVIP_SHORT");
	}
	else if(inputImage->bandP[0]->data_type > CVIP_SHORT)
	{
		cvipImage1 = (Image*)remap_Image(inputImage,CVIP_SHORT,0,255);
		fprintf(stderr,"Image is remapped into CVIP_BYTE");
		delete_Image(inputImage);
		inputImage = cvipImage1;
	}
	cvipImage1 = NULL;

	if(mask_choice > 0 && mask_choice < 5)
	{
		if (mask_choice == 1)
			mask_choice = 4;
		else if (mask_choice == 4)
			mask_choice = 1;
		KERNEL = get_mask( (MASK_TYPE) (mask_choice-1), 3);
		fprintf(stderr,"\n                            Lowpass Mask:\n");
		fprintf(stderr,"                            ==============");
		matrix_print(KERNEL);

		if(inputImage->bands == 1){
			temp_MATRIX = inputImage->image_ptr[0]; 
			inputImage->image_ptr[0] = convolve(inputImage->image_ptr[0], KERNEL);
			delete_Matrix(temp_MATRIX);
		}
		else {
			temp_MATRIX = inputImage->image_ptr[0]; 
			inputImage->image_ptr[0] = convolve(inputImage->image_ptr[0], KERNEL);
			delete_Matrix(temp_MATRIX);
			temp_MATRIX = inputImage->image_ptr[1]; 
			inputImage->image_ptr[1] = convolve(inputImage->image_ptr[1], KERNEL);
			delete_Matrix(temp_MATRIX);
			temp_MATRIX = inputImage->image_ptr[2]; 
			inputImage->image_ptr[2] = convolve(inputImage->image_ptr[2], KERNEL);
			delete_Matrix(temp_MATRIX);
		}
		delete_Matrix(KERNEL);
	}
	
	/*if(mask_size >=7){
	mask_size = 7;
	warning = 1;
	}
	else if(mask_size >= 5){
	mask_size = 5;
	warning = 1;
	}
	else if(mask_size != 3){
	mask_size = 3;
	warning = 1;
	}*/


	//fprintf(fp,"Mask Size %d, Warning %d\n", mask_size,warning);
	/*if(warning)
	fprintf(stderr,"EDGE_Prewitt:kernel size is changed to %d",mask_size);*/
	magImage = prewitt_edge(inputImage,direction_Image, mask_size);	
	*dirImage = *(duplicate_Image(direction_Image));
	delete_Image(direction_Image);
	if(threshold >= 0){
		threshold_image(magImage,threshold);
	}
	//fclose(fp);
	return magImage;
}

static Image *prewitt_edge(Image *cvipImage, Image *directionImage, int size)
{
	Image *testImage,*magnitudeImage,*horizontalImage,*verticalImage;
	Matrix *horiz, *vert;
	int x, y, count;
	int rows, cols, no_of_bands, bands;
	int midpoint,direction,value;
	short  **image_h, **image_v;
	float  ** image_m,**image_d;

    IMAGE_FORMAT image_format1;

	COLOR_FORMAT color_space1;

	CVIP_TYPE data_type1;

	FORMAT data_format1;

	image_format1 = (cvipImage)->image_format;

	color_space1 = (cvipImage)->color_space;

	data_format1 = getDataFormat_Image(cvipImage);

	data_type1 = getDataType_Image(cvipImage);

	no_of_bands  = getNoOfBands_Image(cvipImage);   
	rows =  getNoOfRows_Image(cvipImage);   
	cols =  getNoOfCols_Image(cvipImage);

	/*convole filter takes only short ot byte inputs*/

	if(cvipImage->bandP[0]->data_type < CVIP_SHORT){
		cast_Image(cvipImage,CVIP_BYTE);
		fprintf(stderr,"Image is cast into CVIP_SHORT\n");
	}
	else if(cvipImage->bandP[0]->data_type > CVIP_SHORT){
		testImage = (Image*)remap_Image(cvipImage,CVIP_SHORT,SHRT_MIN, SHRT_MAX);
		fprintf(stderr,"Image is remapped into CVIP_SHORT\n");
		delete_Image(cvipImage);
		cvipImage = (Image*)duplicate_Image(testImage);
		(void)delete_Image(testImage);
		//testImage = NULL;
	}
	//testImage = NULL;
	horiz = new_Matrix(size, size, CVIP_FLOAT, REAL);
	midpoint = size/2;
	/* horizontal mask */
	for(y=0;y<size;y++)
	{
		for(x=0;x<size;x++)
		{
			if(y< midpoint)
				setRealVal_Matrix(horiz,float,y,x,-1);
			else if (y== midpoint)
				setRealVal_Matrix(horiz,float,y,x,0);
			else 
				setRealVal_Matrix(horiz,float,y,x,1);
		}
	}

	/* vertical mask */

	vert = transpose_Matrix(horiz);
	print_Matrix(horiz);
	print_Matrix(vert);
	testImage = (Image*)duplicate_Image(cvipImage);
	magnitudeImage = (Image*)new_Image(image_format1, color_space1, no_of_bands, rows,cols, CVIP_FLOAT, REAL);
	horizontalImage = (Image*)new_Image(image_format1, color_space1, no_of_bands, rows,cols, CVIP_FLOAT, REAL);
	verticalImage = (Image*)new_Image(image_format1, color_space1, no_of_bands, rows,cols, CVIP_FLOAT, REAL);

	horizontalImage = convolve_filter(cvipImage,horiz);
	verticalImage = convolve_filter(testImage,vert);
	for(bands = 0; bands< no_of_bands;bands++){
		image_h = getData_Image(horizontalImage,bands);
		image_v = getData_Image(verticalImage,bands);
		image_m = getData_Image(magnitudeImage,bands);
		image_d = getData_Image(directionImage,bands);
		for(y = 0; y< rows; y++){
			for(x = 0; x < cols; x++){
				image_d[y][x] = atan2(image_v[y][x], image_h[y][x]); 
				image_m[y][x] = sqrt((image_v[y][x])*(image_v[y][x])+(image_h[y][x])*(image_h[y][x]));

			}
		}
	}
	fprintf(stderr,"\n");

	(void)delete_Image(horizontalImage);
	(void)delete_Image(verticalImage);
	(void)delete_Image(testImage);
	//(void)delete_Image(cvipImage);
	(void)delete_Matrix(horiz);
	(void)delete_Matrix(vert);

	return magnitudeImage;
}
/****************************************************************
Format: void threshold_image(Image *,int)
Description: This function is done specifically for edge_detection only.
It assumed the input is short and is real image.

Credit: Kun Luo
*****************************************************************/



static void threshold_image(Image *inputImage,int thres){
	int x, y,row,col;
	float **real;
	int band;
	row= inputImage->bandP[0]->rows;
	col= inputImage->bandP[0]->cols;
	for(band=0;band<inputImage->bands;band++){
		real=getData_Image(inputImage,band);
		for(y=0;y<row;y++){
			for(x=0;x<col;x++){
				real[y][x]=(real[y][x]<thres)?0:255;
			}
		}
	}
}


/****************************************************************
Name: get_mask
Expanded Name: get mask
Parameters: <dimension> - dimension of mask kernel (e.g. 3 => 3x3)
<MASK_TYPE> - an enumerated data type indicating which
mask to fetch from masks.h
Returns: pointer to MATRIX structure
Description: creates a new instance of a MATRIX structure
containing a mask kernel from the kernels defined
above.
Diagnostics: none.
Credit(s): Gregory Hance
Southern Illinois University @ Edwardsville
****************************************************************/


static MATRIX *get_mask(MASK_TYPE type, int dimension)
{
	MATRIX *KERNEL;
	float **kernel;
	int x, y, count=0;

	KERNEL = matrix_allocate(dimension, dimension, CVIP_FLOAT, REAL);   
	kernel = (float **) KERNEL->rptr;

	if(dimension == 3) {
		for (y=0; y < KERNEL->rows; y++)
			for (x=0; x < KERNEL->cols; x++) {
				kernel[y][x] = MASK3x3[type].kernel[count];
				count++;
			}
	}
	else if(dimension == 5) {
		for (y=0; y < KERNEL->rows; y++)
			for (x=0; x < KERNEL->cols; x++) {
				kernel[y][x] = MASK5x5[type].kernel[count];
				count++;
			}
	}
	else {
		fprintf(stderr, "The mask size %d is not supported\n", dimension);
		return(NULL);
	}
	return(KERNEL);
}
