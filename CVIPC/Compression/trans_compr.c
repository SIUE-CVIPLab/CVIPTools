/**************************************************************************
* **********************************************************************
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* **********************************************************************
*
*             File Name: trans_compr.c
*           Description: 
*         Related Files: 
*   Initial Coding Date: 1/1/2001
*           Portability: Standard (ANSI) C
*            References:
*             Author(s): Zhijian Lin
*                        Southern Illinois University @ Edwardsville
*
** Copyright (C) 1996 SIUE - by Scott Umbaugh
**
** Permission to use, copy, modify, and distribute this software and its
** documentation for any purpose and without fee is hereby granted, provided
** that the above copyright notice appear in all copies and that both that
** copyright notice and this permission notice appear in supporting
** documentation.  This software is provided "as is" without express or
** implied warranty.
**
** RCS (Revision Control System) Information
** ...Added automatically by RCS 
**
** $Log: trans_compr.c,v $
** Revision 1.3  2001/05/03 05:49:22  zlin
** final initiation
**
** Revision 1.1  2001/02/20 00:27:33  zlin
** Initial revision
**
****************************************************************************/



#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <math.h>
#include <string.h>
#include "CVIPtoolkit.h"
#include "CVIPdef.h"
#include "wavelet.h"
#include "CVIPobject.h"
#include "CVIPdrawimg.h"
#include "CVIPtransform.h"
#include "huffman.h"
#include "CVIPtools.h"
#include "vector_quant.h"
#include "vector_data.h"
#ifndef WIN32
#include <unistd.h>
#include <pwd.h>
#include <dirent.h>
#else
#include <io.h>
#include <direct.h>
#endif


static void band_remap(Image *image, Image *outputImage, int remap_type, int begin_rows, int end_rows, int begin_cols, int end_cols, float *min_max);
Image *log_remap(Image *imgP, int band);
static Image *inverse_log_remap(Image *imgP, int band);
static Image *inverse_band_remap(Image *temp_image, Image *outputImage, int remap_type, int begin_rows, int end_rows, int begin_cols, int end_cols, float min, float max, float minimum);
static float *min_max_Image(Image *image);


static Image *YCbCr(Image *image, int isign);
static void entropy(Image *image, int begin_row, int begin_col, int end_row, int end_col);
static Image* copy_Image_local(Image *inImage);



/*****************************************************************************************
**	Function Name: 	trans_compr							**
**	Description:	Do transform based compression					**
**	Parameters:	filename:	file to store the compressed data   		**
**			image: 		input image					**
**			color_space:	color space					**
**					0: RGB 1: PCT 2: YCbCr 				**
**			xform:		transform					**
**					1: DCT 2: WAVELET				**
**			WAVELET_basis:	WAVELET transform basic function		**
**					1: harr 2: baud4				**
**			subimage_size:  block size to do the transform			**
**					8, 16, 32, 64, 128, 256, 512			**
**			quant:		quantization					**
**					0: none 1: user specified			**
**			JEPG_Q_Table:	use JPEG quantization table			**
**					0: without using 1: using			**
**			coding:		use vector quantization or not			**
**					1: user specified VQ				**
**					2: Huffman coding				**
**			data_type:	data type to store				**
**					1: float 2: byte 3: short			**
**			remap_type:	remap type for float -> byte/short		**
**					1: linear remap 2: log remap			**
**			keep_DC:	quantize the DC of DCT or not			**
**					0. quantize it 1. keep it			**
**											**
**	Return:		result compressed image						**
**	Author:		Zhijian Lin							**
**	Initial Date:	11/15/00							**
*****************************************************************************************/

//tras_compr_step4 only performs huffman encoding/decoding
//xvq is removed from the transform compression
Image *tras_compr_step4 (char *filename, char* quantfile, Image *image, int color_space, int xform, int WAVELET_basis, int subimage_size, 
						int quant, int JPEG_Q_Table, int coding, int data_type, int remap_type, int keep_DC)
{
	int		maxsz, size, block_size, lowband;
   	HISTORY 	stuff;
	Image		*temp_image;
   	char		*code_book;
   	int  		**hptr=NULL;
   	float  	 	**hptr1=NULL;
	int		pct, ycbcr;
	int		scheme;
	long		size_original;
	long		size_compressed;
	struct  	stat s_buf;     
	float		comp_ratio;	
	
	/* add for the data_type and remap_type */
	float		*min_max=NULL, range[10][2], min=0, max=0;
	float		*datarange;
	Image 		*outputImage;
	IMAGE_FORMAT 	image_format;
	COLOR_FORMAT 	color_format;
   	FORMAT       	data_format;
	unsigned     	no_of_rows, no_of_cols, no_of_bands;
	int 		r, c, bands;
	float		**img_i, **img_o;
	float		**dc_value=NULL,
		sum[3];			/* temp value */ 
	
	/* add for doing the transform in small block */
	Image		*subimage; 		/* used to do tranform in small block size */
	int		i, j;			/* for loop index for subimage */
	int		qtable[3][10];		/* quantization table */
	FILE		*fp;			/* file pointer */
	byte		**img;
	
	no_of_rows =  getNoOfRows_Image(image);
	no_of_cols =  getNoOfCols_Image(image);		/* no_of_cols is the same as no_of_rows now */
	no_of_bands = getNoOfBands_Image(image);
	image_format = getFileFormat_Image(image);
	color_format = getColorSpace_Image(image);
	data_format = getDataFormat_Image(image);

//Remove xvq function from transform compression
#if 0
	/*
	** do vector quantization and vector dequantization
	*/
	if (coding == 1) {
		printf("begin to VQ... \n");
		
		/* do VQ compress */
		if (color_space==0)
			scheme = 9;
		else 
			scheme = 10;
		
		if (vq_compress(image,
			filename, 
			1,		/* cdbook is in file */
			0, 		/* not fixed cdbook */
			10, 		/* erro threshold */
			code_book,	/* useless */
			64,		/* # of entries, useless */
			4, 		/* rows_per_vector, useless */
			4, 		/* cols_per_vector, useless */
			scheme 		
			) != 1) 	
		{	
			return NULL;
		}
		
		
		/* calculate the compression ratio, the CVIP_BYTE ratio has been calculated and printed out in vector_quantization.c */
		if (stat(filename, &s_buf) == 0 && (data_type == 3 || data_type == 1))
		{
			size_original = no_of_rows * no_of_cols * no_of_bands;
			size_compressed = (long)s_buf.st_size;
			comp_ratio = (float)size_original /(float)size_compressed;
			printf("\n\tThe original raw data occupies %ld bytes", size_original);
			printf("\n\tThe compressed data occupies %ld bytes", size_compressed);
			printf("\n\tThe Compression Ratio : %.2f \n\n", comp_ratio);
		}
		
		
		/* do VQ decompress */
		if ( (temp_image = (Image *)vq_decompress(filename)) == (Image *) NULL) {
			return NULL;
		}
		else {
			outputImage = (Image *)vq_decompress(filename);	/* do it for the remap/inverse_remap function */
		}
		outputImage = xvq (image,
			1, //xform
			scheme,
			filename,
			2, //file_type
			1, //remap_type
			0, //dc
			);
		
		/*view_Image(outputImage, "VQed");*/
		
		/* cast the image to float */
		if(temp_image->image_ptr[0]->data_type != CVIP_FLOAT) {
			(void) cast_Image(temp_image, CVIP_FLOAT);
		}
		
		/* copy history form image without VQ or deVQ to temp_image with VQ and deVQ */
		history_copy(image, temp_image);
	}
#endif	  
	
	/* 
	** do Huffman coding 
	*/
	if (coding == 2) {
/*		
		outputImage = new_Image(image_format, color_format, no_of_bands, no_of_rows, no_of_cols, CVIP_BYTE, data_format);
		min = 0;

		for(bands = 0; bands < no_of_bands; bands++)
		{
            img = getData_Image(outputImage, bands);
            img_o = getData_Image(image, bands);
            for(r = 0; r < no_of_rows; r++)
				for(c = 0; c < no_of_cols; c++)
					img[r][c]= (byte)(img_o[r][c] - min);
		}
*/

		datarange = (float *)getDataRange_Image(image);
		if (data_format == COMPLEX) {
		min = datarange[no_of_bands*4];
		max = datarange[no_of_bands*4+1];
		} else {
		min = datarange[no_of_bands*2];
		max = datarange[no_of_bands*2+1];
		}
		if (datarange) free(datarange);

		outputImage = duplicate_Image(image);

		printf("remap to CVIP_BYTE...\n");
		outputImage = remap_Image(outputImage, CVIP_BYTE, 0, 255);


		printf("huffman coding...\n");
		if (huf_compress(outputImage, filename) != 0) {
			return NULL;
		}
		
		//delete_Image(outputImage);
		
		/* calculate the compression ratio, the CVIP_BYTE ratio has been calculated and printed out in vector_quantization.c */
		if (stat(filename, &s_buf) == 0 )
		{
			size_compressed = (long)s_buf.st_size;
			size_original = no_of_rows * no_of_cols * no_of_bands;
			comp_ratio = (float)size_original /(float)size_compressed;
			printf("\n\tThe original raw data occupies %ld bytes", size_original);
			printf("\n\tThe compressed data occupies %ld bytes", size_compressed);
			printf("\n\tThe Compression Ratio : %.2f \n\n", comp_ratio);
		}
		
		/* do huffman decompress */
/*
		if ( (temp_image = (Image *)huf_decompress(filename)) == (Image *) NULL) {
			return NULL;
		}
*/

		printf("huffman decoding...\n");
		outputImage = (Image *)huf_decompress(filename);	/* do it for the remap/inverse_remap function */
		printf("cast to CVIP_FLOAT...\n");
		(void) cast_Image(outputImage, CVIP_FLOAT);
		outputImage = remap_Image(outputImage, CVIP_FLOAT, min, max);
		history_copy(image, outputImage);
		delete_Image(image);
		image = outputImage; 
		outputImage = NULL;               
		return image;
		
		/* cast the image to float */
		if(temp_image->image_ptr[0]->data_type != CVIP_FLOAT) {
			(void) cast_Image(temp_image, CVIP_FLOAT);
		}
		
		/* shift the pixel value back */

		for(bands = 0; bands < no_of_bands; bands++)
		{
            img_i = getData_Image(temp_image, bands);
            for(r = 0; r < no_of_rows; r++)
				for(c = 0; c < no_of_cols; c++)
					img_i[r][c] += min;
		}
		
		/* copy history form image without VQ or deVQ to temp_image with VQ and deVQ */
//		history_copy(image, temp_image);
		
	}
	else {
		printf("coding selected error\n");
		return NULL;
	}
	/*view_Image(image, "2");*/
	
  		
	/*
	** inverse remap
	*/
	if (data_type == 2 || data_type == 3)	        /* CVIP_BYTE or CVIP_SHORT */
	{
		printf("inverse-remap...\n");
		
		temp_image = inverse_band_remap(temp_image, outputImage, remap_type, 0, (image->image_ptr[0]->rows)/8, 0, 
			(image->image_ptr[0]->cols)/8, range[0][0], range[0][1], min);
		
		temp_image = inverse_band_remap(temp_image, outputImage, remap_type, 0, (image->image_ptr[0]->rows)/8, 
			(image->image_ptr[0]->cols)/8, (image->image_ptr[0]->cols)/4, range[1][0], range[1][1], min);
		
		temp_image = inverse_band_remap(temp_image, outputImage, remap_type, (image->image_ptr[0]->rows)/8, 
			(image->image_ptr[0]->rows)/4, 0, (image->image_ptr[0]->cols)/8, range[2][0], range[2][1], min);
		
		temp_image = inverse_band_remap(temp_image, outputImage, remap_type, (image->image_ptr[0]->rows)/8, (image->image_ptr[0]->rows)/4, 
			(image->image_ptr[0]->cols)/8, (image->image_ptr[0]->cols)/4, range[3][0], range[3][1], min);
		
		temp_image = inverse_band_remap(temp_image, outputImage, remap_type, 0, (image->image_ptr[0]->rows)/4, 
			(image->image_ptr[0]->cols)/4, (image->image_ptr[0]->cols)/2, range[4][0], range[4][1], min);
		
		temp_image = inverse_band_remap(temp_image, outputImage, remap_type, (image->image_ptr[0]->rows)/4, 
			(image->image_ptr[0]->rows)/2, 0, (image->image_ptr[0]->cols)/4, range[5][0], range[5][1], min);
		
		temp_image = inverse_band_remap(temp_image, outputImage, remap_type, (image->image_ptr[0]->rows)/4, (image->image_ptr[0]->rows)/2,
			(image->image_ptr[0]->cols)/4, (image->image_ptr[0]->cols)/2, range[6][0], range[6][1], min);
		
		temp_image = inverse_band_remap(temp_image, outputImage, remap_type, 0, (image->image_ptr[0]->rows)/2, 
			(image->image_ptr[0]->cols)/2, (image->image_ptr[0]->cols), range[7][0], range[7][1], min);
		
		temp_image = inverse_band_remap(temp_image, outputImage, remap_type, (image->image_ptr[0]->rows)/2, 
			(image->image_ptr[0]->rows), 0, (image->image_ptr[0]->cols)/2, range[8][0], range[8][1], min);
		
		temp_image = inverse_band_remap(temp_image, outputImage, remap_type, (image->image_ptr[0]->rows)/2, (image->image_ptr[0]->rows),
			(image->image_ptr[0]->cols)/2, (image->image_ptr[0]->cols), range[9][0], range[9][1], min);
	}
	
	history_copy(image, temp_image);
	delete_Image(outputImage);
	delete_Image(image);
	image = temp_image;
	temp_image = NULL;
	/*view_Image(temp_image, "2.5");*/
	return image;
}

//tras_compr_step3 saves histroy information that will be used in 
//XVQ function which is removed from tranform compression.
//So currently tras_compr_step3 is NOT called by any function.
Image *tras_compr_step3 (char *filename, char* quantfile, Image *image, int color_space, int xform, int WAVELET_basis, int subimage_size, 
						int quant, int JPEG_Q_Table, int coding, int data_type, int remap_type, int keep_DC)
{
	int		maxsz, size, block_size, lowband;
   	HISTORY 	stuff, stuff1;
	Image		*temp_image;
   	char		*code_book;
   	int  		**hptr=NULL;
   	float  	 	**hptr1=NULL;
	int		pct, ycbcr;
	int		scheme;
	long		size_original;
	long		size_compressed;
	struct  	stat s_buf;     
	float		comp_ratio;	
	
	/* add for the data_type and remap_type */
	float		*min_max=NULL, range[10][2], min=0;
	Image 		*outputImage;
	IMAGE_FORMAT 	image_format;
	COLOR_FORMAT 	color_format;
   	FORMAT       	data_format;
	unsigned     	no_of_rows, no_of_cols, no_of_bands;
	int 		r, c, bands;
	float		**img_i, **img_o;
	float		**dc_value=NULL,
		sum[3];			/* temp value */ 
	
	/* add for doing the transform in small block */
	Image		*subimage; 		/* used to do tranform in small block size */
	int		i, j;			/* for loop index for subimage */
	int		qtable[3][10];		/* quantization table */
	FILE		*fp;			/* file pointer */
	byte		**img;

	no_of_rows =  getNoOfRows_Image(image);
	no_of_cols =  getNoOfCols_Image(image);		/* no_of_cols is the same as no_of_rows now */
	no_of_bands = getNoOfBands_Image(image);
	image_format = getFileFormat_Image(image);
	color_format = getColorSpace_Image(image);
	data_format = getDataFormat_Image(image);

	/* 
	** calculate the entropy of the image 
	*/
	if ( JPEG_Q_Table == 1 || quant == 1 ) {
		entropy(image, 0, 0, no_of_rows-1,  no_of_rows-1);
		min_max = min_max_Image(image);		
		printf("min = %f, max = %f \n", min_max[0], min_max[1]);
		min = min_max[0];
	}
	
	
	/*
	** remap and save history
	*/
	if(data_type == 1 || data_type ==0)	/* 1 - CVIP_FLOAT */ 	
   	{
 	  /***********************************************
	  ******* 				  ********
	  *******        save history here  	  ********    
	  *******				  ********
		***********************************************/
		printf("\nSaving history for CVIP_FLOAT\n");
		stuff=(HISTORY)NULL;
		stuff=(HISTORY)malloc(sizeof(struct history));
		stuff->packetP = (PACKET *)malloc(sizeof(PACKET));
		
		if (quant==1)
		{
			stuff->packetP->dsize=39;
			stuff->packetP->dtype=(CVIP_TYPE *)malloc(sizeof(CVIP_TYPE)*39);
			stuff->packetP->dptr=(void **)malloc(sizeof(void *)*39);
			for(i = 0; i < 39; i++)
				stuff->packetP->dtype[i]=CVIP_INTEGER;
			
			hptr=(int **)NULL;
			hptr=(int **)malloc(sizeof(int *)*30);
			for(i=0; i<30; i++)
				hptr[i]=(int *)malloc(sizeof(int));
			
			for (bands=0; bands<3; bands++)
				for (i=0; i<10; i++)
					hptr[10*bands+i][0] = qtable[bands][i];
				
				for (i=0; i<30; i++)
					stuff->packetP->dptr[i+9] = (void *)hptr[i];
				
		}
		else {
			stuff->packetP->dsize=9;
			stuff->packetP->dtype=(CVIP_TYPE *)malloc(sizeof(CVIP_TYPE)*9);
			stuff->packetP->dptr=(void **)malloc(sizeof(void *)*9);
			for(i = 0; i < 9; i++)
				stuff->packetP->dtype[i]=CVIP_INTEGER;
		}	  
		
		hptr=(int **)NULL;
		hptr=(int **)malloc(sizeof(int *)*9);
		for(i=0; i<9; i++)
			hptr[i]=(int *)malloc(sizeof(int));
		
		if (xform == 1)	/* DCT */
		{
			hptr[0][0] = color_space;	
			hptr[1][0] = JPEG_Q_Table; 
			hptr[2][0] = keep_DC; 
			hptr[3][0] = subimage_size;	
            hptr[4][0] = quant; 	
			hptr[5][0] = coding;	
			hptr[6][0] = data_type; 
			hptr[7][0] = remap_type;
			hptr[8][0] = min;
			for (i = 0; i < 9; i++)
				stuff->packetP->dptr[i]=(void *)hptr[i];
			stuff->next=(HISTORY)NULL;
			stuff->ftag=DCTXFORM;
		}
		else 	/* WAVELET */
		{
			hptr[0][0] = color_space;	
			hptr[1][0] = WAVELET_basis; 
			hptr[2][0] = lowband; 
			hptr[3][0] = subimage_size;	
            hptr[4][0] = quant; 
			hptr[5][0] = coding;	
			hptr[6][0] = data_type; 
			hptr[7][0] = remap_type;
			hptr[8][0] = min; 
			for (i = 0; i < 9; i++)
				stuff->packetP->dptr[i]=(void *)hptr[i];
			stuff->next=(HISTORY)NULL;
			stuff->ftag=WAVELET;
		}	
		
		/* end of save history */
   	}
	else if(data_type == 2 || data_type == 3)	/* 2 - CVIP_BYTE; 3 - CVIP_SHORT */
   	{
	/* 
	** get the maximum and minimum value of the image 
		*/
		min_max = min_max_Image(image);		/* min_max[0] is min, min_max[1] is max */
		min = min_max[0];
		
		/*
		** do the remapping for each sub bands 
		*/
		if(remap_type == 1) { 		/* linear remap */
			printf("Linear_Remap...\n");
		}
		else if(remap_type == 2) 		/* log remap */
		{
			printf("LOG_Remap...\n");
			for(bands = 0; bands < no_of_bands; bands++)
			{
				img_i = getData_Image(image, bands);
				/* shift the value for log */
				for(r = 0; r < no_of_rows; r++)
					for(c = 0; c < no_of_cols; c++)
						img_i[r][c] = img_i[r][c] + fabs(min);	/* shift for log */
			}
		}
		
		/* 
		** create new image according to the remap type 
		*/
		if (data_type == 2) {  
            outputImage = new_Image(image_format, color_format, no_of_bands, no_of_rows, no_of_cols, CVIP_BYTE, data_format);
		}
		else if (data_type == 3) {
			outputImage = new_Image(image_format, color_format, no_of_bands, no_of_rows, no_of_cols, CVIP_SHORT, data_format);
		}
		
		/* 
		** change the data type and remap sub bands
		*/
		band_remap(image, outputImage, remap_type, 0, (no_of_rows)/8, 0, (no_of_cols)/8, min_max);
		range[0][0] = min_max[0];
		range[0][1] = min_max[1];
		
		band_remap(image, outputImage, remap_type, 0, (no_of_rows)/8,	(no_of_cols)/8, (no_of_cols)/4, min_max);
		range[1][0] = min_max[0];
		range[1][1] = min_max[1];
		
		band_remap(image, outputImage, remap_type, (no_of_rows)/8, (no_of_rows)/4, 0, (no_of_cols)/8, min_max);
		range[2][0] = min_max[0];
		range[2][1] = min_max[1];
		
		band_remap(image, outputImage, remap_type, (no_of_rows)/8, (no_of_rows)/4, (no_of_cols)/8, (no_of_cols)/4, min_max);
		range[3][0] = min_max[0];
		range[3][1] = min_max[1];
		
		band_remap(image, outputImage, remap_type, 0, (no_of_rows)/4, (no_of_cols)/4, (no_of_cols)/2, min_max);
		range[4][0] = min_max[0];
		range[4][1] = min_max[1];
		
		band_remap(image, outputImage, remap_type, (no_of_rows)/4, (no_of_rows)/2, 0, (no_of_cols)/4, min_max);
		range[5][0] = min_max[0];
		range[5][1] = min_max[1];
		
		band_remap(image, outputImage, remap_type, (no_of_rows)/4, (no_of_rows)/2, (no_of_cols)/4, (no_of_cols)/2, min_max);
		range[6][0] = min_max[0];
		range[6][1] = min_max[1];
		
		band_remap(image, outputImage, remap_type, 0, (no_of_rows)/2, (no_of_cols)/2, (no_of_cols), min_max);
		range[7][0] = min_max[0];
		range[7][1] = min_max[1];
		
		band_remap(image, outputImage, remap_type, (no_of_rows)/2, (no_of_rows), 0, (no_of_cols)/2, min_max);
		range[8][0] = min_max[0];
		range[8][1] = min_max[1];
		
		band_remap(image, outputImage, remap_type, (no_of_rows)/2, (no_of_rows), (no_of_cols)/2, (no_of_cols), min_max);
		range[9][0] = min_max[0];
		range[9][1] = min_max[1];
		
		
		history_copy(image, outputImage);
		delete_Image(image);
		image = outputImage;
		outputImage = NULL;                
		
		
		/*************************************
		******* 			********
		*******   save history here  	********    
		*******			********
		**************************************/
		
		printf("Saving history for BYTE/SHORT\n");
		stuff=(HISTORY)NULL;
     	  stuff=(HISTORY)malloc(sizeof(struct history));
		  stuff->packetP = (PACKET *)malloc(sizeof(PACKET));
		  
		  if (quant==1 && xform==1 && keep_DC==1)
		  {
			  stuff->packetP->dsize=60+(no_of_rows/subimage_size)*(no_of_cols/subimage_size)*3;
			  stuff->packetP->dtype=(CVIP_TYPE *)malloc(sizeof(CVIP_TYPE)*(60+(no_of_rows/subimage_size)*(no_of_cols/subimage_size)*3));
			  stuff->packetP->dptr=(void **)malloc(sizeof(void *)*(60+(no_of_rows/subimage_size)*(no_of_cols/subimage_size)*3));
			  for(i = 0; i < 39; i++)
				  stuff->packetP->dtype[i]=CVIP_INTEGER;
			  for(i = 39; i < (60+(no_of_rows/subimage_size)*(no_of_cols/subimage_size)*3); i++)
				  stuff->packetP->dtype[i]=CVIP_FLOAT;
			  
			  hptr=(int **)NULL;
			  hptr=(int **)malloc(sizeof(int *)*30);
			  for(i=0; i<30; i++)
				  hptr[i]=(int *)malloc(sizeof(int));
			  
			  for (bands=0; bands<3; bands++)
				  for (i=0; i<10; i++)
					  hptr[10*bands+i][0] = qtable[bands][i];
				  
				  for (i=0; i<30; i++)
					  stuff->packetP->dptr[i+9] = (void *)hptr[i];
				  
				  
				  hptr1=(float **)NULL;
				  hptr1=(float **)malloc(sizeof(float *)*(21+(no_of_rows/subimage_size)*(no_of_cols/subimage_size)*3));
				  for(i=0; i<(21+(no_of_rows/subimage_size)*(no_of_cols/subimage_size)*3); i++)
					  hptr1[i]=(float *)malloc(sizeof(float));
				  
				  for (i = 0; i < 20; i++)
					  hptr1[i][0] = range[i/2][i%2];
				  
				  hptr1[20][0] = min;
				  
				  for (bands=0; bands<3; bands++)
					  for (i=0; i<((no_of_rows/subimage_size)*(no_of_cols/subimage_size)); i++)
						  hptr1[21+i][0] = dc_value[i/3][i%3];
					  
					  
					  for(i=0; i<(21+(no_of_rows/subimage_size)*(no_of_cols/subimage_size)*3); i++)
						  stuff->packetP->dptr[i+39] = (void *)hptr1[i];
					  
		  }
		  else if (quant==1)
		  {
			  stuff->packetP->dsize=60;
			  stuff->packetP->dtype=(CVIP_TYPE *)malloc(sizeof(CVIP_TYPE)*60);
			  stuff->packetP->dptr=(void **)malloc(sizeof(void *)*60);
			  for(i = 0; i < 39; i++)
				  stuff->packetP->dtype[i]=CVIP_INTEGER;
			  for(i=39; i<60; i++)
				  stuff->packetP->dtype[i]=CVIP_FLOAT;
              
			  hptr=(int **)NULL;
			  hptr=(int **)malloc(sizeof(int *)*30);
			  for(i=0; i<30; i++)
				  hptr[i]=(int *)malloc(sizeof(int));
			  
			  for (bands=0; bands<3; bands++)
				  for (i=0; i<10; i++)
					  hptr[10*bands+i][0] = qtable[bands][i];
				  
				  for (i=0; i<30; i++)
					  stuff->packetP->dptr[i+9] = (void *)hptr[i];
				  
				  hptr1=(float **)NULL;
				  hptr1=(float **)malloc(sizeof(float *)*21);
				  for(i=0; i<21; i++)
					  hptr1[i]=(float *)malloc(sizeof(float)*21);
				  
				  for(i = 0; i < 20; i++)
					  hptr1[i][0] = range[i/2][i%2];
				  
				  hptr1[20][0] = min;
				  
				  for(i=0; i<21; i++)
					  stuff->packetP->dptr[i+39]=(void *)hptr1[i];
				  
		  }
		  else if (xform==1 && keep_DC==1)
		  {
			  stuff->packetP->dsize=30+(no_of_rows/subimage_size)*(no_of_cols/subimage_size)*3;
			  stuff->packetP->dtype=(CVIP_TYPE *)malloc(sizeof(CVIP_TYPE)*(30+(no_of_rows/subimage_size)*(no_of_cols/subimage_size)*3));
			  stuff->packetP->dptr=(void **)malloc(sizeof(void *)*(30+(no_of_rows/subimage_size)*(no_of_cols/subimage_size)*3));
			  for(i = 0; i < 9; i++)
				  stuff->packetP->dtype[i]=CVIP_INTEGER;
			  for(i = 9; i < (30+(no_of_rows/subimage_size)*(no_of_cols/subimage_size)*3); i++)
				  stuff->packetP->dtype[i]=CVIP_FLOAT;
			  
			  hptr1=(float **)NULL;
			  hptr1=(float **)malloc(sizeof(float *)*(21+(no_of_rows/subimage_size)*(no_of_cols/subimage_size)*3));
			  for(i=0; i<(21+(no_of_rows/subimage_size)*(no_of_cols/subimage_size)*3); i++)
				  hptr1[i]=(float *)malloc(sizeof(float));
              
			  for (i = 0; i < 20; i++)
				  hptr1[i][0] = range[i/2][i%2];
			  
			  hptr1[20][0] = min;
			  
			  for (i=0; i<((no_of_rows/subimage_size)*(no_of_cols/subimage_size)*3); i++)
				  hptr1[21+i][0] = dc_value[i/3][i%3];
			  
			  
			  for(i=0; i<(21+(no_of_rows/subimage_size)*(no_of_cols/subimage_size)*3); i++)
				  stuff->packetP->dptr[i+9] = (void *)hptr1[i];
		  }
		  else
		  {
			  stuff->packetP->dsize=30;
			  stuff->packetP->dtype=(CVIP_TYPE *)malloc(sizeof(CVIP_TYPE)*30);
			  stuff->packetP->dptr=(void **)malloc(sizeof(void *)*30);
			  for(i = 0; i < 9; i++)
				  stuff->packetP->dtype[i]=CVIP_INTEGER;
			  for(i=9; i<30; i++)
				  stuff->packetP->dtype[i]=CVIP_FLOAT;
              
			  hptr1=(float **)NULL;
			  hptr1=(float **)malloc(sizeof(float *)*21);
			  for(i=0; i<21; i++)
				  hptr1[i]=(float *)malloc(sizeof(float)*21);
              
			  for(i = 0; i < 20; i++)
				  hptr1[i][0] = range[i/2][i%2];
			  
			  hptr1[20][0] = min;
			  
			  for(i=0; i<21; i++)
				  stuff->packetP->dptr[i+9]=(void *)hptr1[i];
			  
		  }
		  
		  /* common history */
		  hptr=(int **)NULL;
		  hptr=(int **)malloc(sizeof(int *)*9);
		  for(i=0; i<9; i++)
			  hptr[i]=(int *)malloc(sizeof(int));
		  
		  if (xform == 1)	/* DCT */
		  {
			  hptr[0][0] = color_space;	
			  hptr[1][0] = JPEG_Q_Table; 
			  hptr[2][0] = keep_DC; 
			  hptr[3][0] = subimage_size;	
			  hptr[4][0] = quant; 	
			  hptr[5][0] = coding;	
			  hptr[6][0] = data_type; 
			  hptr[7][0] = remap_type;
			  hptr[8][0] = min;
			  for (i = 0; i < 9; i++)
				  stuff->packetP->dptr[i]=(void *)hptr[i];
			  stuff->next=(HISTORY)NULL;
			  stuff->ftag=DCTXFORM;
		  }
		  else 	/* WAVELET */
		  {
			  hptr[0][0] = color_space;	
			  hptr[1][0] = WAVELET_basis; 
			  hptr[2][0] = lowband; 
			  hptr[3][0] = subimage_size;	
			  hptr[4][0] = quant; 
			  hptr[5][0] = coding;	
			  hptr[6][0] = data_type; 
			  hptr[7][0] = remap_type;
			  hptr[8][0] = min; 
			  for (i = 0; i < 9; i++)
				  stuff->packetP->dptr[i]=(void *)hptr[i];
			  stuff->next=(HISTORY)NULL;
			  stuff->ftag=WAVELET;
		  }	
		  /* end of save history */
   	}  	/* end of data_type if statement */
	
	
   	if (pct == 0)	/*no pct xform*/
   	{
		printf("save history for no pct\n");
		history_add(image, stuff);  
	}
	else 		/*PCTed*/
	{
		printf("save history for pct\n");
		stuff1 = history_get(image, PCT);
		stuff1->next = stuff;
	}
   	
}

Image *tras_compr_step2 (char *filename, char* quantfile, Image *image, int color_space, int xform, int WAVELET_basis, int subimage_size, 
						int quant, int JPEG_Q_Table, int coding, int data_type, int remap_type, int keep_DC)
{
	int		maxsz, size, block_size, lowband;
   	HISTORY 	stuff;
	Image		*temp_image;
   	char		*code_book;
   	int  		**hptr=NULL;
   	float  	 	**hptr1=NULL;
	int		pct, ycbcr;
	int		scheme;
	long		size_original;
	long		size_compressed;
	struct  	stat s_buf;     
	float		comp_ratio;	
	
	/* add for the data_type and remap_type */
	float		*min_max=NULL, range[10][2], min=0;
	Image 		*outputImage;
	IMAGE_FORMAT 	image_format;
	COLOR_FORMAT 	color_format;
   	FORMAT       	data_format;
	unsigned     	no_of_rows, no_of_cols, no_of_bands;
	int 		r, c, bands;
	float		**img_i, **img_o;
	float		**dc_value=NULL,
		sum[3];			/* temp value */ 
	
	/* add for doing the transform in small block */
	Image		*subimage; 		/* used to do tranform in small block size */
	int		i, j;			/* for loop index for subimage */
	int		qtable[3][10];		/* quantization table */
	FILE		*fp;			/* file pointer */
	byte		**img;

	no_of_rows =  getNoOfRows_Image(image);
	no_of_cols =  getNoOfCols_Image(image);		/* no_of_cols is the same as no_of_rows now */
	no_of_bands = getNoOfBands_Image(image);
	image_format = getFileFormat_Image(image);
	color_format = getColorSpace_Image(image);
	data_format = getDataFormat_Image(image);

	/*
	** do quantization with the user specified table onto the ten sub bands (sub images)
	*/  
	if (quant == 1) {
		printf("Do the quantization using the user specified table\n");
		
		fp = fopen(quantfile, "r");
		if (fp == NULL) {
			printf("Cannot open quantization table\n");
			return NULL;
		}
		
		for(bands = 0; bands < no_of_bands; bands++)
		{
            
            for (i = 0; i < 10; i++)
				fscanf(fp, "%d", &qtable[bands][i]); 
			img_i = getData_Image(image, bands);
			
            for(r = 0; r < no_of_rows/8; r++)
				for(c = 0; c < no_of_rows/8; c++)
					img_i[r][c] = ((img_i[r][c]/(float)qtable[bands][0])-floor(img_i[r][c]/(float)qtable[bands][0]))>=0.5 ? 
					(float)ceil(img_i[r][c]/(float)qtable[bands][0]) : (float)floor(img_i[r][c]/(float)qtable[bands][0]);
				
				for(r = 0; r < no_of_rows/8; r++)
					for(c = no_of_rows/8; c < no_of_rows/4; c++)
						img_i[r][c] = ((img_i[r][c]/(float)qtable[bands][1])-floor(img_i[r][c]/(float)qtable[bands][1]))>=0.5 ? 
						(float)ceil(img_i[r][c]/(float)qtable[bands][1]) : (float)floor(img_i[r][c]/(float)qtable[bands][1]);
					
					for(r = no_of_rows/8; r < no_of_rows/4; r++)
						for(c = 0; c < no_of_rows/8; c++)
							img_i[r][c] = ((img_i[r][c]/(float)qtable[bands][2])-floor(img_i[r][c]/(float)qtable[bands][2]))>=0.5 ? 
							(float)ceil(img_i[r][c]/(float)qtable[bands][2]) : (float)floor(img_i[r][c]/(float)qtable[bands][2]);
						
						for(r = no_of_rows/8; r < no_of_rows/4; r++)
							for(c = no_of_rows/8; c < no_of_rows/4; c++)
								img_i[r][c] = ((img_i[r][c]/(float)qtable[bands][3])-floor(img_i[r][c]/(float)qtable[bands][3]))>=0.5 ? 
								(float)ceil(img_i[r][c]/(float)qtable[bands][3]) : (float)floor(img_i[r][c]/(float)qtable[bands][3]);
							
							for(r = 0; r < no_of_rows/4; r++)
								for(c = no_of_rows/4; c < no_of_rows/2; c++)
									img_i[r][c] = ((img_i[r][c]/(float)qtable[bands][4])-floor(img_i[r][c]/(float)qtable[bands][4]))>=0.5 ? 
									(float)ceil(img_i[r][c]/(float)qtable[bands][4]) : (float)floor(img_i[r][c]/(float)qtable[bands][4]);
								
								for(r = no_of_rows/4; r < no_of_rows/2; r++)
									for(c = 0; c < no_of_rows/4; c++)
										img_i[r][c] = ((img_i[r][c]/(float)qtable[bands][5])-floor(img_i[r][c]/(float)qtable[bands][5]))>=0.5 ? 
										(float)ceil(img_i[r][c]/(float)qtable[bands][5]) : (float)floor(img_i[r][c]/(float)qtable[bands][5]);
									
									for(r = no_of_rows/4; r < no_of_rows/2; r++)
										for(c = no_of_rows/4; c < no_of_rows/2; c++)
											img_i[r][c] = ((img_i[r][c]/(float)qtable[bands][6])-floor(img_i[r][c]/(float)qtable[bands][6]))>=0.5 ? 
											(float)ceil(img_i[r][c]/(float)qtable[bands][6]) : (float)floor(img_i[r][c]/(float)qtable[bands][6]);
										
										for(r = 0; r < no_of_rows/2; r++)
											for(c = no_of_rows/2; c < no_of_rows; c++)
												img_i[r][c] = ((img_i[r][c]/(float)qtable[bands][7])-floor(img_i[r][c]/(float)qtable[bands][7]))>=0.5 ? 
												(float)ceil(img_i[r][c]/(float)qtable[bands][7]) : (float)floor(img_i[r][c]/(float)qtable[bands][7]);
											
											for(r = no_of_rows/2; r < no_of_rows; r++)
												for(c = 0; c < no_of_rows/2; c++)
													img_i[r][c] = ((img_i[r][c]/(float)qtable[bands][8])-floor(img_i[r][c]/(float)qtable[bands][8]))>=0.5 ? 
													(float)ceil(img_i[r][c]/(float)qtable[bands][8]) : (float)floor(img_i[r][c]/(float)qtable[bands][8]);
												
												for(r = no_of_rows/2; r < no_of_rows; r++)
													for(c = no_of_rows/2; c < no_of_rows; c++)
														img_i[r][c] = ((img_i[r][c]/(float)qtable[bands][9])-floor(img_i[r][c]/(float)qtable[bands][9]))>=0.5 ? 
														(float)ceil(img_i[r][c]/(float)qtable[bands][9]) : (float)floor(img_i[r][c]/(float)qtable[bands][9]);
		}	/* end of bands for loop */
		fclose(fp);
	}
	
//saving histroy (step3) is removed	
	image = tras_compr_step4 (filename, quantfile, image, color_space, xform, WAVELET_basis, subimage_size, 
				quant, JPEG_Q_Table, coding, data_type, remap_type, keep_DC);

	/*
	** do dequantization with the user specified table onto the ten sub bands (sub images)
	*/  
	if (quant == 1) {
		printf("Do the dequantization using the user specified table...\n");
		
		for(bands = 0; bands < no_of_bands; bands++)
		{
			img_i = getData_Image(image, bands);
			
            for(r = 0; r < no_of_rows/8; r++)
				for(c = 0; c < no_of_rows/8; c++)
					img_i[r][c] = img_i[r][c] * qtable[bands][0];
				
				for(r = 0; r < no_of_rows/8; r++)
					for(c = no_of_rows/8; c < no_of_rows/4; c++)
						img_i[r][c] = img_i[r][c] * qtable[bands][1];
					
					for(r = no_of_rows/8; r < no_of_rows/4; r++)
						for(c = 0; c < no_of_rows/8; c++)
							img_i[r][c] = img_i[r][c] * qtable[bands][2];
						
						for(r = no_of_rows/8; r < no_of_rows/4; r++)
							for(c = no_of_rows/8; c < no_of_rows/4; c++)
								img_i[r][c] = img_i[r][c] * qtable[bands][3];
							
							for(r = 0; r < no_of_rows/4; r++)
								for(c = no_of_rows/4; c < no_of_rows/2; c++)
									img_i[r][c] = img_i[r][c] * qtable[bands][4];
								
								for(r = no_of_rows/4; r < no_of_rows/2; r++)
									for(c = 0; c < no_of_rows/4; c++)
										img_i[r][c] = img_i[r][c] * qtable[bands][5];
									
									for(r = no_of_rows/4; r < no_of_rows/2; r++)
										for(c = no_of_rows/4; c < no_of_rows/2; c++)
											img_i[r][c] = img_i[r][c] * qtable[bands][6];
										
										for(r = 0; r < no_of_rows/2; r++)
											for(c = no_of_rows/2; c < no_of_rows; c++)
												img_i[r][c] = img_i[r][c] * qtable[bands][7];
											
											for(r = no_of_rows/2; r < no_of_rows; r++)
												for(c = 0; c < no_of_rows/2; c++)
													img_i[r][c] = img_i[r][c] * qtable[bands][8];
												
												for(r = no_of_rows/2; r < no_of_rows; r++)
													for(c = no_of_rows/2; c < no_of_rows; c++)
														img_i[r][c] = img_i[r][c] * qtable[bands][9];
		}	/* end of bands for loop */
		
	}

	return image;
}

Image *tras_compr_step1 (char *filename, char* quantfile, Image *image, int color_space, int xform, int WAVELET_basis, int subimage_size, 
						int quant, int JPEG_Q_Table, int coding, int data_type, int remap_type, int keep_DC)
{
	int		maxsz, size, block_size, lowband;
   	HISTORY 	stuff;
	Image		*temp_image;
   	char		*code_book;
   	int  		**hptr=NULL;
   	float  	 	**hptr1=NULL;
	int		pct, ycbcr;
	int		scheme;
	long		size_original;
	long		size_compressed;
	struct  	stat s_buf;     
	float		comp_ratio;	
	
	/* add for the data_type and remap_type */
	float		*min_max=NULL, range[10][2], min=0;
	Image 		*outputImage;
	IMAGE_FORMAT 	image_format;
	COLOR_FORMAT 	color_format;
   	FORMAT       	data_format;
	unsigned     	no_of_rows, no_of_cols, no_of_bands;
	int 		r, c, bands;
	float		**img_i, **img_o;
	float		**dc_value=NULL,
		sum[3];			/* temp value */ 
	
	/* add for doing the transform in small block */
	Image		*subimage; 		/* used to do tranform in small block size */
	int		i, j;			/* for loop index for subimage */
	int		qtable[3][10];		/* quantization table */
	FILE		*fp;			/* file pointer */
	byte		**img;
	
	/* Initialize JPEG Luminance and Chrominance tables */
	/* quantization table for jpeg */
	float Luminance[8][8] = {16,  11,  10,  16,  24,  40,  51,  61,
		12,  12,  14,  19,  26,  58,  60,  55,
		14,  13,  16,  24,  40,  57,  69,  56,
		14,  17,  22,  29,  51,  87,  80,  62,
		18,  22,  37,  56,  68,  109, 103, 77,
		24,  35,  55,  64,  81,  104, 113, 92,
		49,  64,  78,  87,  103, 121, 120,101,
		72,  92,  95,  98,  112, 100, 103, 99};
	
	float Chrominance[8][8] = {17,  18,  24,  47,  99,  99,  99,  99,
		18,  21,  26,  66,  99,  99,  99,  99,
		24,  26,  56,  99,  99,  99,  99,  99,
		47,  66,  99,  99,  99,  99,  99,  99,
		99,  99,  99,  99,  99,  99,  99,  99,
		99,  99,  99,  99,  99,  99,  99,  99,
		99,  99,  99,  99,  99,  99,  99,  99,
		99,  99,  99,  99,  99,  99,  99,  99};
	
        /* 
        ** modify the JPEG quantization table 
	*/
	for (r=0; r<8; r++)
		for (c=0; c<8; c++) {
			Luminance[r][c]/=4.0;
			Chrominance[r][c]/=4.0;
        }
        
		
		for(i=0; i<3; i++)
			for(j=0; j<10; j++)
				qtable[i][j] = 1;

	no_of_rows =  getNoOfRows_Image(image);
	no_of_cols =  getNoOfCols_Image(image);		/* no_of_cols is the same as no_of_rows now */
	no_of_bands = getNoOfBands_Image(image);
	image_format = getFileFormat_Image(image);
	color_format = getColorSpace_Image(image);
	data_format = getDataFormat_Image(image);
	/* 
	** make a new image to hold the small block size subimage and the packed transformed image
	*/
			subimage = new_Image(image_format, color_format, no_of_bands, subimage_size, subimage_size, CVIP_FLOAT, data_format);
			outputImage = new_Image(image_format, color_format, no_of_bands, no_of_rows, no_of_cols, CVIP_FLOAT, data_format);
			
			
			
			/*
			** allocate memory for dc_value array
			*/
			if (xform == 1 && (data_type == 2 || data_type == 3) && keep_DC == 1) 
			{
			/*dc_value = (float **)malloc(sizeof(float *)*3);
			for (i=0; i<3; i++)
				dc_value[i]=(float **)malloc(sizeof(float *)*((no_of_rows/subimage_size)*(no_of_rows/subimage_size)));*/
				dc_value = (float **)malloc(sizeof(float *)*((no_of_rows/subimage_size)*(no_of_rows/subimage_size)));
				for(i = 0; i < ((no_of_rows/subimage_size)*(no_of_rows/subimage_size)); i++)
					dc_value[i]=(float *)malloc(sizeof(float)*3);
			}  	    
			
			
			/* 
			** do the transform on the subimage and pack them to the tranformed image 
			*/
			printf("do the transform...\n");
			for(i = 0; i < no_of_rows/subimage_size; i++) {
				for(j = 0; j < no_of_cols/subimage_size; j++) {  
					
					/* get the appropriate subimage from the original image */
					for(bands = 0; bands < no_of_bands; bands++)
					{
						img_o = getData_Image(image, bands);
						img_i = getData_Image(subimage, bands);
						for(r = 0; r < subimage_size; r++)
							for(c = 0; c < subimage_size; c++)
								img_i[r][c] = img_o[i*subimage_size+r][j*subimage_size+c];
					}
					
					
					if (xform == 1)
					{
						subimage = dct_transform(subimage, subimage_size);
					}
					else if (xform == 2)
					{
						switch (WAVELET_basis) {
						case 1:
							lowband =(int)(subimage_size>>2);
							subimage = haar_transform(subimage, 1, lowband);
							break;
						case 2: 
							lowband =(int)(subimage_size>>2);
							subimage = wavdaub4_transform(subimage, 1, lowband);
							break;
						}
					}
					
					
					/* keep DC */
					if (xform == 1 && (data_type == 2 || data_type == 3) && keep_DC == 1)
					{
						for(bands = 0; bands < no_of_bands; bands++)
						{
							sum[bands] = 0;
							img_i = getData_Image(subimage, bands);
							
							for(r = 0; r < subimage_size; r++)
								for(c = 0; c < subimage_size; c++)
									if((r != 0) || (c != 0))
										sum[bands] = img_i[r][c] + sum[bands]; 
									
									dc_value[i*(no_of_rows/subimage_size)+j][bands] = img_i[0][0];
									img_i[0][0] = sum[bands] / (float)((getNoOfRows_Image(image)) * (getNoOfCols_Image(image)));
						}
						
					}
					
					
					
					/* involve jpeg quantization table */
					if (xform == 1 && subimage_size == 8 && JPEG_Q_Table == 1) {
						if (no_of_bands == 1) {
							img_i = getData_Image(subimage, 0);
							for(r = 0; r < subimage_size; r++)
								for(c = 0; c < subimage_size; c++) {
									img_i[r][c] = ((img_i[r][c]/Luminance[r][c])-floor(img_i[r][c]/Luminance[r][c]))>=0.5 ? 
										(float)ceil(img_i[r][c]/Luminance[r][c]) : (float)floor(img_i[r][c]/Luminance[r][c]);
								}
						}
						else {
							for(bands = 0; bands < no_of_bands; bands++) {
								img_i = getData_Image(subimage, bands);
								for(r = 0; r < subimage_size; r++) {
									for(c = 0; c < subimage_size; c++) {
										if (bands == 0) {
											img_i[r][c] = ((img_i[r][c]/Luminance[r][c])-floor(img_i[r][c]/Luminance[r][c]))>=0.5 ? 
												(float)ceil(img_i[r][c]/Luminance[r][c]) : (float)floor(img_i[r][c]/Luminance[r][c]);
										}
										else {
											img_i[r][c] = ((img_i[r][c]/Chrominance[r][c])-floor(img_i[r][c]/Chrominance[r][c]))>=0.5 ? 
												(float)ceil(img_i[r][c]/Chrominance[r][c]) : (float)floor(img_i[r][c]/Chrominance[r][c]);
										}
									}
								}
							}
						}
					}
					
					
					/* pack the subimage into the transformed image */
					for(bands = 0; bands < no_of_bands; bands++)
					{
						img_o = getData_Image(subimage, bands);
						img_i = getData_Image(outputImage, bands);
						
						
						for(r = 0; r < subimage_size/8; r++)
							for(c = 0; c < subimage_size/8; c++)
								img_i[i*subimage_size/8+r][j*subimage_size/8+c] = img_o[r][c];
							
							for(r = 0; r < subimage_size/8; r++)
								for(c = subimage_size/8; c < subimage_size/4; c++)
									img_i[i*subimage_size/8+r][no_of_cols/8+(j-1)*subimage_size/8+c] = img_o[r][c];
								
								for(r = subimage_size/8; r < subimage_size/4; r++)
									for(c = 0; c < subimage_size/8; c++)
										img_i[no_of_rows/8+(i-1)*subimage_size/8+r][j*subimage_size/8+c] = img_o[r][c];
									
									for(r = subimage_size/8; r < subimage_size/4; r++)
										for(c = subimage_size/8; c < subimage_size/4; c++)
											img_i[no_of_rows/8+(i-1)*subimage_size/8+r][no_of_cols/8+(j-1)*subimage_size/8+c] = img_o[r][c];
										
										for(r = 0; r < subimage_size/4; r++)
											for(c = subimage_size/4; c < subimage_size/2; c++)
												img_i[i*subimage_size/4+r][no_of_cols/4+(j-1)*subimage_size/4+c] = img_o[r][c];
											
											for(r = subimage_size/4; r < subimage_size/2; r++)
												for(c = 0; c < subimage_size/4; c++)
													img_i[no_of_rows/4+(i-1)*subimage_size/4+r][j*subimage_size/4+c] = img_o[r][c];
												
												for(r = subimage_size/4; r < subimage_size/2; r++)
													for(c = subimage_size/4; c < subimage_size/2; c++)
														img_i[no_of_rows/4+(i-1)*subimage_size/4+r][no_of_cols/4+(j-1)*subimage_size/4+c] = img_o[r][c];
													
													for(r = 0; r < subimage_size/2; r++)
														for(c = subimage_size/2; c < subimage_size; c++)
															img_i[i*subimage_size/2+r][no_of_cols/2+(j-1)*subimage_size/2+c] = img_o[r][c];
														
														for(r = subimage_size/2; r < subimage_size; r++)
															for(c = 0; c < subimage_size/2; c++)
																img_i[no_of_rows/2+(i-1)*subimage_size/2+r][j*subimage_size/2+c] = img_o[r][c];
															
															for(r = subimage_size/2; r < subimage_size; r++)
																for(c = subimage_size/2; c < subimage_size; c++)
																	img_i[no_of_rows/2+(i-1)*subimage_size/2+r][no_of_cols/2+(j-1)*subimage_size/2+c] = img_o[r][c];
					} 	
					
	  }	/* j for loop */
	}  	/* i for loop */
	
	history_copy(image, outputImage);
	delete_Image(image);
	image = outputImage; 
	outputImage = NULL;               
	//	view_Image(image, "1");
	
	image = tras_compr_step2 (filename, quantfile, image, color_space, xform, WAVELET_basis, subimage_size, 
				quant, JPEG_Q_Table, coding, data_type, remap_type, keep_DC);
	
	
	/* 
	** do the inverse transform on the subimage and 
	** pack them to the inverse tranformed image 
	*/
	printf("inverse transform...\n");
	outputImage = new_Image(image_format, color_format, no_of_bands, no_of_rows, no_of_cols, CVIP_FLOAT, data_format);
	
	for(i = 0; i < no_of_rows/subimage_size; i++) {
		for(j = 0; j < no_of_cols/subimage_size; j++) {  
			
            /* get the ten bands form image and put them back to the subimage */
            for(bands = 0; bands < no_of_bands; bands++)
            {
				img_i = getData_Image(subimage, bands);
				img_o = getData_Image(image, bands);
				
				for(r = 0; r < subimage_size/8; r++)
					for(c = 0; c < subimage_size/8; c++)
						img_i[r][c] = img_o[i*subimage_size/8+r][j*subimage_size/8+c];
					
					for(r = 0; r < subimage_size/8; r++)
						for(c = subimage_size/8; c < subimage_size/4; c++)
							img_i[r][c] = img_o[i*subimage_size/8+r][no_of_cols/8+(j-1)*subimage_size/8+c];
						
						for(r = subimage_size/8; r < subimage_size/4; r++)
							for(c = 0; c < subimage_size/8; c++)
								img_i[r][c] = img_o[no_of_rows/8+(i-1)*subimage_size/8+r][j*subimage_size/8+c];
							
							for(r = subimage_size/8; r < subimage_size/4; r++)
								for(c = subimage_size/8; c < subimage_size/4; c++)
									img_i[r][c] = img_o[no_of_rows/8+(i-1)*subimage_size/8+r][no_of_cols/8+(j-1)*subimage_size/8+c];
								
								for(r = 0; r < subimage_size/4; r++)
									for(c = subimage_size/4; c < subimage_size/2; c++)
										img_i[r][c] = img_o[i*subimage_size/4+r][no_of_cols/4+(j-1)*subimage_size/4+c];
									
									for(r = subimage_size/4; r < subimage_size/2; r++)
										for(c = 0; c < subimage_size/4; c++)
											img_i[r][c] = img_o[no_of_rows/4+(i-1)*subimage_size/4+r][j*subimage_size/4+c];
										
										for(r = subimage_size/4; r < subimage_size/2; r++)
											for(c = subimage_size/4; c < subimage_size/2; c++)
												img_i[r][c] = img_o[no_of_rows/4+(i-1)*subimage_size/4+r][no_of_cols/4+(j-1)*subimage_size/4+c];
											
											for(r = 0; r < subimage_size/2; r++)
												for(c = subimage_size/2; c < subimage_size; c++)
													img_i[r][c] = img_o[i*subimage_size/2+r][no_of_cols/2+(j-1)*subimage_size/2+c];
												
												for(r = subimage_size/2; r < subimage_size; r++)
													for(c = 0; c < subimage_size/2; c++)
														img_i[r][c] = img_o[no_of_rows/2+(i-1)*subimage_size/2+r][j*subimage_size/2+c];
													
													for(r = subimage_size/2; r < subimage_size; r++)
														for(c = subimage_size/2; c < subimage_size; c++)
															img_i[r][c] = img_o[no_of_rows/2+(i-1)*subimage_size/2+r][no_of_cols/2+(j-1)*subimage_size/2+c];
			} 	/* bands for loop */
			
			
            /* involve jpeg quantization table */
            if (xform == 1 && subimage_size == 8 && JPEG_Q_Table == 1) {
				if (no_of_bands == 1) {
					img_i = getData_Image(subimage, 0);
					for(r = 0; r < subimage_size; r++)
						for(c = 0; c < subimage_size; c++)
							img_i[r][c] = img_i[r][c]*Luminance[r][c];
				}
				else {
					for(bands = 0; bands < no_of_bands; bands++) {
						img_i = getData_Image(subimage, bands);
						for(r = 0; r < subimage_size; r++) {
							for(c = 0; c < subimage_size; c++) {
								if (bands == 0) {
									img_i[r][c] = img_i[r][c]*Luminance[r][c];
								}
								else {
									img_i[r][c] = img_i[r][c]*Chrominance[r][c];
								}
							}
						}
					}
				}
			}
			
			
			/* keep DC */
			if (xform == 1 && (data_type == 2 || data_type == 3) && keep_DC == 1)
			{
				/*printf("\n\t\tGet DC back\n");*/
				for(bands = 0; bands < no_of_bands; bands++)
				{
					img_i = getData_Image(subimage, bands);
					img_i[0][0] = dc_value[i*(no_of_rows/subimage_size)+j][bands];
				}
            }
			
            /* inverse transform */
            if (xform == 1) 	/* 1 - DCT */
            {
				subimage = idct_transform(subimage, subimage_size);
			}
			else if (xform == 2)
            {
				switch (WAVELET_basis) {
				case 1:
					lowband =(int)(subimage_size>>2);
					subimage = haar_transform(subimage, 0, lowband);
					break;
				case 2: 
					lowband =(int)(subimage_size>>2);
					
					subimage = wavdaub4_transform(subimage, -1, lowband);
					
					
					break;
				}
            }
			
            /* put the appropriate subimage into the output image */
            for(bands = 0; bands < no_of_bands; bands++)
            {
				img_i = getData_Image(outputImage, bands);
				img_o = getData_Image(subimage, bands);
				for(r = 0; r < subimage_size; r++)
					for(c = 0; c < subimage_size; c++)
						img_i[i*subimage_size+r][j*subimage_size+c] = img_o[r][c];
			}
			
	  }	/* i for loop */
	}	/* j for loop */
	/*view_Image(outputImage, "3");*/
	
	history_copy(image, outputImage);
	delete_Image(image);
	image = outputImage;
	outputImage = NULL;

	return image;
}

Image *trans_compr(char *filename, char* quantfile, Image *image, int color_space, int xform, int WAVELET_basis, int subimage_size, 
				   int quant, int JPEG_Q_Table, int coding, int data_type, int remap_type, int keep_DC)
{	
	/* import from xvq.c */
	int		maxsz, size, block_size, lowband;
   	HISTORY 	stuff;
	Image		*image1 = NULL;
	Image		*temp_image = NULL;
   	char		*code_book = NULL;
   	int  		**hptr=NULL;
   	float  	 	**hptr1=NULL;
	int		pct, ycbcr;
	int		scheme;
	long		size_original;
	long		size_compressed;
	struct  	stat s_buf;     
	float		comp_ratio;	
	
	/* add for the data_type and remap_type */
	float		*min_max=NULL, range[10][2], min=0;
	Image 		*outputImage = NULL;
	IMAGE_FORMAT 	image_format;
	COLOR_FORMAT 	color_format;
   	FORMAT       	data_format;
	unsigned     	no_of_rows, no_of_cols, no_of_bands;
	int 		r, c, bands;
	float		**img_i = NULL, **img_o = NULL;
	float		**dc_value=NULL,
		sum[3];			/* temp value */ 
	
	/* add for doing the transform in small block */
	Image		*subimage = NULL; 		/* used to do tranform in small block size */
	int		i, j;			/* for loop index for subimage */
	int		qtable[3][10];		/* quantization table */
	FILE		*fp = NULL;			/* file pointer */
	byte		**img = NULL;
	
			
				/*************************************************************************
				**	transform compression can be devided into 4 modules:		**
				**		1. color space transfrom				**
				**		2. spectral transform					**
				**		3. quantization						**
				**		4. vector quantization					**
			*************************************************************************/	
			//print input parameters
			printf("color_space=%d\n", color_space);
			printf("xform=%d\n", xform);
			printf("WAVELET_basis=%d\n", WAVELET_basis);
			printf("subimage_size=%d\n", subimage_size);
			printf("quant=%d\n", quant);
			printf("JPEG_Q_Table=%d\n", JPEG_Q_Table);
			printf("coding=%d\n", coding);
			printf("data_type=%d\n", data_type);
			printf("remap_type=%d\n", remap_type);
			printf("keep_DC=%d\n", keep_DC);
			
			
			/*
			** get the properties of the image 
			*/
			no_of_rows =  getNoOfRows_Image(image);
			no_of_cols =  getNoOfCols_Image(image);	
			no_of_bands = getNoOfBands_Image(image);
			
			/* 
			** assign the code book name for VQ 
			*/
			code_book = calloc(13, sizeof(char));
			strcpy(code_book, "temp_cdbook");
			
			/* 
			** set the color space option 
			*/
			pct = ((image->bands == 3) && (color_space == 1)) ? 1 : 0;
			ycbcr = ((image->bands == 3) && (color_space == 2)) ? 1 : 0;
			
			/* 
			** pad the image to a 2 power size 
			*/
			maxsz=MAX(no_of_rows, no_of_cols);
			maxsz=(int)pow(2,((int)(log(maxsz-1)/log(2))+1));
			printf("zero pad... \n");
			(void)zero_pad(image, maxsz, maxsz);
			if (subimage_size == 0)
				subimage_size = maxsz;
			
				/*
				** get the properties of the image 
			*/
			no_of_rows =  getNoOfRows_Image(image);
			no_of_cols =  getNoOfCols_Image(image);		/* no_of_cols is the same as no_of_rows now */
			no_of_bands = getNoOfBands_Image(image);
			image_format = getFileFormat_Image(image);
			color_format = getColorSpace_Image(image);
			data_format = getDataFormat_Image(image);
			
			
			/* 
			** calculate the entropy of the image 
			*/
//			entropy(image, 0, 0, no_of_rows-1,  no_of_rows-1);
			
			/* 
			** calculate the original file size 
			*/
			size_original = no_of_rows * no_of_cols * no_of_bands;
			
			/* 
			** cast image to CVIP_FLOAT 
			*/
			if(image->image_ptr[0]->data_type != CVIP_FLOAT) {
				printf("cast to float...\n");
				(void)cast_Image(image, CVIP_FLOAT);
			}
			
			/*
			** do the pct or ycbcr color transform 
			*/
			if (pct == 1) {
				printf("pct transform...\n");
				image = pct_color(image, CVIP_NO, NULL, 1);
			} 
			else if (ycbcr == 1) {
				printf("ycbcr transform...\n");
				image = YCbCr(image, 0);
			}
			/*view_Image(image, "0");*/
			
			image = tras_compr_step1 (filename, quantfile, image, color_space, xform, WAVELET_basis, subimage_size, 
						quant, JPEG_Q_Table, coding, data_type, remap_type, keep_DC);

			
			/* 
			** color inverse transform 
			*/
			if (pct == 1) {
				printf("\n\npct inverse tranformed");
				image = pct_color(image, CVIP_NO, NULL, 2);
			}
			else if (ycbcr == 1) {
				printf("\n\nYCbCr inverse tranformed");
				image = YCbCr(image, 1);
			}          
			
			
			/* save the image format, remap and view the image */
			printf("trans_compr: convert the resulting image to BYTE before return...\n");
			image->image_format = TRCM;
			image = remap_Image(image, CVIP_BYTE, 0, 255);
			/*view_Image( image ,"final");*/
			
			
			/* release the momery */
			if (min_max!=NULL)
			{
				free(min_max);
			}
			
			if (NULL != subimage) {
				delete_Image(subimage);
			}
			
			if (NULL != code_book) {
				free(code_book);
			}
			if (dc_value!=NULL)
				free(dc_value);
			
			return image;
			
}
/*
** end of trans_compr function
*/


/*********************************************************************************************************
**	Function Name: 	TRCM_read_decompression								**
**	Description:	This function is called by function xdr_compress() in file "cviptovip.c".	**
**			It is used for reading TRCM_compressed image files with VIP structure from 	**
**			disk. Because TRCM_compressed image files is saved as VIP structure, now	**
**			the pointer 'fp' points to the raw data in VIP structure. in fact,		**
** 			The raw data in VIP structure is the original TRCMP_compressed image files.	**
**			The useful part of imgP is its history. its history stores the 			**
**			necessary data for doing the inverse transform.					**
**	Parameters:	fp -- File pointer								**
**			imgP -- image contain the history						**
**	Return:		decompressed image								**
**	Author:		Zhijian Lin									**
**	Initial Date:	4/28/01										**
*********************************************************************************************************/
Image *TRCM_read_decompression(FILE *fp, Image *imgP) 
{
   	HISTORY 	stuff;
   	Image 		*image;
   	float		**img_i, **img_o;
   	float		**dc_value=NULL;
   	int		qtable[3][10];
   	float 		**hptr1; 
	int		**hptr;
	
   	int 		data;
   	int		pct, ycbcr;
   	int 		color_space,
		xform,
		WAVELET_basis,
		subimage_size,
		quant,
		JPEG_Q_Table,
		coding,
		data_type,
		remap_type,
		dc,
		lowband;
	
	FILE		*fptr;
	char		*filename;
	
   	Image 		*outputImage;
   	int 		r, c, i, j, bands;
   	float		range[10][2], min;
   	IMAGE_FORMAT 	image_format;
	COLOR_FORMAT 	color_format;
	FORMAT       	data_format;
   	unsigned     	no_of_rows, no_of_cols, no_of_bands;
	
   	Image		*subimage;		/* used to do tranform in small block size */	
	
#ifndef WIN32
	struct passwd *pwentry;
#endif
	
	/* quantization table for jpeg */
	float Luminance[8][8] = {16,  11,  10,  16,  24,  40,  51,  61,
		12,  12,  14,  19,  26,  58,  60,  55,
		14,  13,  16,  24,  40,  57,  69,  56,
		14,  17,  22,  29,  51,  87,  80,  62,
		18,  22,  37,  56,  68,  109, 103, 77,
		24,  35,  55,  64,  81,  104, 113, 92,
		49,  64,  78,  87,  103, 121, 120, 101,
		72,  92,  95,  98,  112, 100, 103, 99};
	
	float Chrominance[8][8] = {17,  18,  24,  47,  99,  99,  99,  99,
		18,  21,  26,  66,  99,  99,  99,  99,
		24,  26,  56,  99,  99,  99,  99,  99,
		47,  66,  99,  99,  99,  99,  99,  99,
		99,  99,  99,  99,  99,  99,  99,  99,
		99,  99,  99,  99,  99,  99,  99,  99,
		99,  99,  99,  99,  99,  99,  99,  99,
		99,  99,  99,  99,  99,  99,  99,  99};
	
	printf("trcm decompress...\n");
	/* 
	** modify the JPEG quantization table 
	*/
	for (r=0; r<8; r++)
		for (c=0; c<8; c++) {
			Luminance[r][c]/=4.0;
			Chrominance[r][c]/=4.0;
        }
		
		filename = (char *)malloc(sizeof(char) * 150);
		
#ifndef WIN32
     	  pwentry = getpwuid(getuid()); 	/*get home directory of the user*/
		  strcpy(filename, pwentry->pw_dir);
		  strcat(filename, "/.cvip_temp/"); 
		  strcat(filename, "temp_file");
#else
		  if(getenv("temp"))
		  {
			  strcpy(filename, getenv("temp"));
			  strcat(filename, "\\.cvip_temp");
			  strcat(filename, "\\temp_file");
		  }
		  else
          {
			  strcpy(filename, "\\temp\\.cvip_temp");
			  strcat(filename, "\\temp_file");
		  }
#endif
		  
		  /*error_CVIP("filename = %s", filename);*/
		  
		  if((fptr = fopen(filename, "w+")) == NULL)
		  {
			  error_CVIP("TRCM_read_decompression", "cannot open new file");
		  }
		  
		  data = getc(fp);
		  while(data != EOF)
		  {
			  fputc(data, fptr);
			  data = getc(fp);
		  }
		  fclose(fptr);
		  
		  
		  
		  /***************************************************************************
		  **	this part is to do DCT inverse xform;				  **
		  **	now the imgP is changed to temp_image				  **
		  ***************************************************************************/
		  if(history_check(DCTXFORM, imgP))
		  { 
			  printf("DCTXFORM\n");
			  
			  stuff=history_get(imgP, DCTXFORM);
			  xform = 1; 
			  hptr=(int **)malloc(sizeof(int *)*9);
			  for(i=0; i<9; i++)
				  hptr[i]=(int *)malloc(sizeof(int));
			  for(i=0; i<9; i++)
				  hptr[i]=(int *)stuff->packetP->dptr[i];
			  
			  color_space 	= hptr[0][0];	
			  JPEG_Q_Table 	= hptr[1][0]; 
			  dc 		= hptr[2][0]; 
			  subimage_size = hptr[3][0];	
			  quant 	= hptr[4][0]; 	
			  coding 	= hptr[5][0];	
			  data_type 	= hptr[6][0]; 
			  remap_type 	= hptr[7][0];
			  min		= hptr[8][0];
		  }  
		  else if(history_check(WAVELET, imgP))
		  {	
			  printf("WAVELET\n");
			  
			  stuff=history_get(imgP, WAVELET);
			  xform = 2;          
			  hptr=(int **)malloc(sizeof(int *)*9);
			  for(i=0; i<9; i++)
				  hptr[i]=(int *)malloc(sizeof(int));
			  for(i=0; i<9; i++)
				  hptr[i]=(int *)stuff->packetP->dptr[i];
			  
			  color_space 	= hptr[0][0];	
			  WAVELET_basis	= hptr[1][0]; 
			  lowband	= hptr[2][0]; 
			  subimage_size = hptr[3][0];	
			  quant 	= hptr[4][0]; 	
			  coding 	= hptr[5][0];	
			  data_type 	= hptr[6][0]; 
			  remap_type 	= hptr[7][0];
			  min		= hptr[8][0];
		  }
		  
		  
		  printf("color_space=%d\n", color_space);
		  printf("xform=%d\n", xform);
		  printf("WAVELET_basis=%d\n", WAVELET_basis);
		  printf("subimage_size=%d\n", subimage_size);
		  printf("quant=%d\n", quant);
		  printf("JPEG_Q_Table=%d\n", JPEG_Q_Table);
		  printf("coding=%d\n", coding);
		  printf("data_type=%d\n", data_type);
		  printf("remap_type=%d\n", remap_type);
		  printf("dc=%d\n", dc);
		  
		  
		  if (coding == 1) {
			  if ((image = (Image *)vq_decompress(filename)) == (Image *) NULL) {	
				  error_CVIP("TRCM decompression fail", " return NULL");
				  return NULL;
			  }
			  else
				  outputImage = (Image *)vq_decompress(filename);	/* do it for the remap/inverse_remap function */
		  } 
		  else {
			  /* do huffman decompress */
			  if ( (image = (Image *)huf_decompress(filename)) == (Image *) NULL) {
				  return NULL;
			  }
			  else {
				  /*view_Image(image,"huf");*/
				  outputImage = (Image *)huf_decompress(filename);	/* do it for the remap/inverse_remap function */
			  }
			  
			  /* cast the image to float */
			  if(image->image_ptr[0]->data_type != CVIP_FLOAT) {
				  (void) cast_Image(image, CVIP_FLOAT);
			  }
			  
			  no_of_rows =  getNoOfRows_Image(image);
			  no_of_cols =  getNoOfCols_Image(image);
			  no_of_bands = getNoOfBands_Image(image);
			  
			  /* shift the pixel value back */
			  for(bands = 0; bands < no_of_bands; bands++)
			  {
				  img_i = getData_Image(image, bands);
				  for(r = 0; r < no_of_rows; r++)
					  for(c = 0; c < no_of_cols; c++)
						  img_i[r][c] += min;
			  }
		  }
		  
		  
		  /************************************************************************
		  ** the history of imgP stores the necessary data for inverse transform. 
		  ************************************************************************/
		  history_copy(imgP, image);
		  
		  no_of_rows =  getNoOfRows_Image(image);
		  no_of_cols =  getNoOfCols_Image(image);
		  no_of_bands = getNoOfBands_Image(image);
		  image_format = getFileFormat_Image(image);
		  color_format = getColorSpace_Image(image);
		  data_format = getDataFormat_Image(image);
		  
		  
		  if(image->image_ptr[0]->data_type != CVIP_FLOAT) {
			  (void) cast_Image(image, CVIP_FLOAT);
		  }
		  
		  pct = ((image->bands == 3) && (color_space == 1)) ? 1 : 0;
		  ycbcr = ((image->bands == 3) && (color_space == 2)) ? 1 : 0;
		  
		  if (xform == 1 && (data_type == 2 || data_type == 3) && dc == 1) 
		  {
			  dc_value = (float **)malloc(sizeof(float *)*((no_of_rows/subimage_size)*(no_of_rows/subimage_size)));
			  for(i = 0; i < ((no_of_rows/subimage_size)*(no_of_rows/subimage_size)); i++)
				  dc_value[i]=(float *)malloc(sizeof(float)*3);
		  }  	    
		  
		  if(data_type == 2 || data_type == 3)
		  {
			  if (quant==1 && xform==1 && dc==1)
			  {
				  free(hptr);
				  hptr=(int **)malloc(sizeof(int *)*30);
				  for(i=0; i<30; i++)
					  hptr[i] = (int *)malloc(sizeof(int));
				  
				  for (i=0; i<30; i++)
					  hptr[i] = (int *)stuff->packetP->dptr[i+9];
				  
				  for (bands=0; bands<3; bands++)
					  for (i=0; i<10; i++)
						  qtable[bands][i] = hptr[10*bands+i][0];
					  
					  hptr1=(float **)malloc(sizeof(float *)*(21+(no_of_rows/subimage_size)*(no_of_cols/subimage_size)*3));
					  for(i=0; i<(21+(no_of_rows/subimage_size)*(no_of_cols/subimage_size)*3); i++)
						  hptr1[i]=(float *)malloc(sizeof(float));
					  
					  for(i=0; i<(21+(no_of_rows/subimage_size)*(no_of_cols/subimage_size)*3); i++)
						  hptr1[i] = (float *) stuff->packetP->dptr[i+39];
					  
					  for (i = 0; i < 20; i++)
						  range[i/2][i%2] = hptr1[i][0];
					  
					  min = hptr1[20][0];
					  
					  for (i=0; i<((no_of_rows/subimage_size)*(no_of_cols/subimage_size)*3); i++)
						  dc_value[i/3][i%3] = hptr1[21+i][0];
			  }
			  else if (quant==1)
			  {
				  free(hptr);
				  hptr=(int **)malloc(sizeof(int *)*30);
				  for(i=0; i<30; i++)
					  hptr[i]=(int *)malloc(sizeof(int));
				  
				  for (i=0; i<30; i++)
					  hptr[i] = (int *)stuff->packetP->dptr[i+9];
				  
				  for (bands=0; bands<3; bands++)
					  for (i=0; i<10; i++)
						  qtable[bands][i] = hptr[10*bands+i][0];
					  
					  hptr1=(float **)malloc(sizeof(float *)*21);
					  for(i=0; i<21; i++)
						  hptr1[i]=(float *)malloc(sizeof(float));
					  
					  for(i=0; i<21; i++)
						  hptr1[i] = (float *) stuff->packetP->dptr[i+39];
					  
					  for (i = 0; i < 20; i++)
						  range[i/2][i%2] = hptr1[i][0];
					  
					  min = hptr1[20][0];
			  }
			  else if (xform==1 && dc==1)
			  {
				  hptr1=(float **)malloc(sizeof(float *)*(21+(no_of_rows/subimage_size)*(no_of_cols/subimage_size)*3));
				  for(i=0; i<(21+(no_of_rows/subimage_size)*(no_of_cols/subimage_size)*3); i++)
					  hptr1[i]=(float *)malloc(sizeof(float));
				  
				  for(i=0; i<(21+(no_of_rows/subimage_size)*(no_of_cols/subimage_size)*3); i++)
					  hptr1[i] = (float *) stuff->packetP->dptr[i+9];
				  
				  for (i = 0; i < 20; i++)
					  range[i/2][i%2] = hptr1[i][0];
				  
				  min = hptr1[20][0];
				  
				  for (i=0; i<((no_of_rows/subimage_size)*(no_of_cols/subimage_size)*3); i++)
					  dc_value[i/3][i%3] = hptr1[21+i][0];
			  }
			  else
			  {
				  hptr1=(float **)malloc(sizeof(float *)*21);
				  for(i=0; i<21; i++)
					  hptr1[i]=(float *)malloc(sizeof(float));
				  
				  for(i=0; i<21; i++)
					  hptr1[i] = (float *) stuff->packetP->dptr[i+9];
				  
				  for (i = 0; i < 20; i++)
					  range[i/2][i%2] = hptr1[i][0];
				  
				  min = hptr1[20][0];
			  }
			  
			  
			  /*
			  ** inverse remap
			  */
			  printf("inverse-remap...\n");
			  
			  image = inverse_band_remap(image, outputImage, remap_type, 0, (image->image_ptr[0]->rows)/8, 0, 
				  (image->image_ptr[0]->cols)/8, range[0][0], range[0][1], min);
			  
			  image = inverse_band_remap(image, outputImage, remap_type, 0, (image->image_ptr[0]->rows)/8, 
				  (image->image_ptr[0]->cols)/8, (image->image_ptr[0]->cols)/4, range[1][0], range[1][1], min);
          				
			  image = inverse_band_remap(image, outputImage, remap_type, (image->image_ptr[0]->rows)/8, 
				  (image->image_ptr[0]->rows)/4, 0, (image->image_ptr[0]->cols)/8, range[2][0], range[2][1], min);
          				
			  image = inverse_band_remap(image, outputImage, remap_type, (image->image_ptr[0]->rows)/8, (image->image_ptr[0]->rows)/4, 
				  (image->image_ptr[0]->cols)/8, (image->image_ptr[0]->cols)/4, range[3][0], range[3][1], min);
          				
			  image = inverse_band_remap(image, outputImage, remap_type, 0, (image->image_ptr[0]->rows)/4, 
				  (image->image_ptr[0]->cols)/4, (image->image_ptr[0]->cols)/2, range[4][0], range[4][1], min);
			  
			  image = inverse_band_remap(image, outputImage, remap_type, (image->image_ptr[0]->rows)/4, 
				  (image->image_ptr[0]->rows)/2, 0, (image->image_ptr[0]->cols)/4, range[5][0], range[5][1], min);
          				
			  image = inverse_band_remap(image, outputImage, remap_type, (image->image_ptr[0]->rows)/4, (image->image_ptr[0]->rows)/2,
				  (image->image_ptr[0]->cols)/4, (image->image_ptr[0]->cols)/2, range[6][0], range[6][1], min);
          				
			  image = inverse_band_remap(image, outputImage, remap_type, 0, (image->image_ptr[0]->rows)/2, 
				  (image->image_ptr[0]->cols)/2, (image->image_ptr[0]->cols), range[7][0], range[7][1], min);
          				
			  image = inverse_band_remap(image, outputImage, remap_type, (image->image_ptr[0]->rows)/2, 
				  (image->image_ptr[0]->rows), 0, (image->image_ptr[0]->cols)/2, range[8][0], range[8][1], min);
          				
			  image = inverse_band_remap(image, outputImage, remap_type, (image->image_ptr[0]->rows)/2, (image->image_ptr[0]->rows),
				  (image->image_ptr[0]->cols)/2, (image->image_ptr[0]->cols), range[9][0], range[9][1], min);
			  
			  delete_Image(outputImage);
			  
	}	/* end of data_type if statement */
	else if (quant == 1)
	{
		free(hptr);
   	    hptr=(int **)malloc(sizeof(int *)*30);
   	    for(i=0; i<30; i++)
			hptr[i]=(int *)malloc(sizeof(int));
		
		for (i=0; i<30; i++)
			hptr[i] = (int *)stuff->packetP->dptr[i+9];
		
		for (bands=0; bands<3; bands++)
			for (i=0; i<10; i++)
				qtable[bands][i] = hptr[10*bands+i][0];
	}  
	
	/*
	** do dequantization with the user specified table onto the ten sub bands (sub images)
	*/  
	if (quant == 1) {
		printf("Do the dequantization using the user specified table...\n");
		
		for(bands = 0; bands < no_of_bands; bands++)
		{
			img_i = getData_Image(image, bands);
			
            for(r = 0; r < no_of_rows/8; r++)
				for(c = 0; c < no_of_rows/8; c++)
					img_i[r][c] = img_i[r][c] * qtable[bands][0];
				
				for(r = 0; r < no_of_rows/8; r++)
					for(c = no_of_rows/8; c < no_of_rows/4; c++)
						img_i[r][c] = img_i[r][c] * qtable[bands][1];
					
					for(r = no_of_rows/8; r < no_of_rows/4; r++)
						for(c = 0; c < no_of_rows/8; c++)
							img_i[r][c] = img_i[r][c] * qtable[bands][2];
						
						for(r = no_of_rows/8; r < no_of_rows/4; r++)
							for(c = no_of_rows/8; c < no_of_rows/4; c++)
								img_i[r][c] = img_i[r][c] * qtable[bands][3];
							
							for(r = 0; r < no_of_rows/4; r++)
								for(c = no_of_rows/4; c < no_of_rows/2; c++)
									img_i[r][c] = img_i[r][c] * qtable[bands][4];
								
								for(r = no_of_rows/4; r < no_of_rows/2; r++)
									for(c = 0; c < no_of_rows/4; c++)
										img_i[r][c] = img_i[r][c] * qtable[bands][5];
									
									for(r = no_of_rows/4; r < no_of_rows/2; r++)
										for(c = no_of_rows/4; c < no_of_rows/2; c++)
											img_i[r][c] = img_i[r][c] * qtable[bands][6];
										
										for(r = 0; r < no_of_rows/2; r++)
											for(c = no_of_rows/2; c < no_of_rows; c++)
												img_i[r][c] = img_i[r][c] * qtable[bands][7];
											
											for(r = no_of_rows/2; r < no_of_rows; r++)
												for(c = 0; c < no_of_rows/2; c++)
													img_i[r][c] = img_i[r][c] * qtable[bands][8];
												
												for(r = no_of_rows/2; r < no_of_rows; r++)
													for(c = no_of_rows/2; c < no_of_rows; c++)
														img_i[r][c] = img_i[r][c] * qtable[bands][9];
		}	/* end of bands for loop */
	}
	
	/* 
	** do the inverse transform on the subimage and 
	** pack them to the inverse tranformed image 
	*/
	subimage = new_Image(image_format, color_format, no_of_bands, subimage_size, subimage_size, CVIP_FLOAT, data_format);
	outputImage = new_Image(image_format, color_format, no_of_bands, no_of_rows, no_of_cols, CVIP_FLOAT, data_format);
	
	for(i = 0; i < no_of_rows/subimage_size; i++) {
		for(j = 0; j < no_of_cols/subimage_size; j++) {  
			
            /* get the ten bands form image and put them back to the subimage */
            for(bands = 0; bands < no_of_bands; bands++)
            {
				img_i = getData_Image(subimage, bands);
				img_o = getData_Image(image, bands);
				
				for(r = 0; r < subimage_size/8; r++)
					for(c = 0; c < subimage_size/8; c++)
						img_i[r][c] = img_o[i*subimage_size/8+r][j*subimage_size/8+c];
					
					for(r = 0; r < subimage_size/8; r++)
						for(c = subimage_size/8; c < subimage_size/4; c++)
							img_i[r][c] = img_o[i*subimage_size/8+r][no_of_cols/8+(j-1)*subimage_size/8+c];
						
						for(r = subimage_size/8; r < subimage_size/4; r++)
							for(c = 0; c < subimage_size/8; c++)
								img_i[r][c] = img_o[no_of_rows/8+(i-1)*subimage_size/8+r][j*subimage_size/8+c];
							
							for(r = subimage_size/8; r < subimage_size/4; r++)
								for(c = subimage_size/8; c < subimage_size/4; c++)
									img_i[r][c] = img_o[no_of_rows/8+(i-1)*subimage_size/8+r][no_of_cols/8+(j-1)*subimage_size/8+c];
								
								for(r = 0; r < subimage_size/4; r++)
									for(c = subimage_size/4; c < subimage_size/2; c++)
										img_i[r][c] = img_o[i*subimage_size/4+r][no_of_cols/4+(j-1)*subimage_size/4+c];
									
									for(r = subimage_size/4; r < subimage_size/2; r++)
										for(c = 0; c < subimage_size/4; c++)
											img_i[r][c] = img_o[no_of_rows/4+(i-1)*subimage_size/4+r][j*subimage_size/4+c];
										
										for(r = subimage_size/4; r < subimage_size/2; r++)
											for(c = subimage_size/4; c < subimage_size/2; c++)
												img_i[r][c] = img_o[no_of_rows/4+(i-1)*subimage_size/4+r][no_of_cols/4+(j-1)*subimage_size/4+c];
											
											for(r = 0; r < subimage_size/2; r++)
												for(c = subimage_size/2; c < subimage_size; c++)
													img_i[r][c] = img_o[i*subimage_size/2+r][no_of_cols/2+(j-1)*subimage_size/2+c];
												
												for(r = subimage_size/2; r < subimage_size; r++)
													for(c = 0; c < subimage_size/2; c++)
														img_i[r][c] = img_o[no_of_rows/2+(i-1)*subimage_size/2+r][j*subimage_size/2+c];
													
													for(r = subimage_size/2; r < subimage_size; r++)
														for(c = subimage_size/2; c < subimage_size; c++)
															img_i[r][c] = img_o[no_of_rows/2+(i-1)*subimage_size/2+r][no_of_cols/2+(j-1)*subimage_size/2+c];
			} 	/* bands for loop */
			
			
            /* involve jpeg quantization table */
            if (xform == 1 && subimage_size == 8 && JPEG_Q_Table == 1) {
				if (no_of_bands == 1) {
					img_i = getData_Image(subimage, 0);
					for(r = 0; r < subimage_size; r++)
						for(c = 0; c < subimage_size; c++)
							img_i[r][c] = img_i[r][c]*Luminance[r][c];
				}
				else {
					for(bands = 0; bands < no_of_bands; bands++) {
						img_i = getData_Image(subimage, bands);
						for(r = 0; r < subimage_size; r++) {
							for(c = 0; c < subimage_size; c++) {
								if (bands == 0) {
									img_i[r][c] = img_i[r][c]*Luminance[r][c];
								}
								else {
									img_i[r][c] = img_i[r][c]*Chrominance[r][c];
								}
							}
						}
					}
				}
			}
			
			
			/* keep DC */
			if (xform == 1 && (data_type == 2 || data_type == 3) && dc == 1)
			{
				/*printf("\n\t\tGet DC back\n");*/
				for(bands = 0; bands < no_of_bands; bands++)
				{
					img_i = getData_Image(subimage, bands);
					img_i[0][0] = dc_value[i*(no_of_rows/subimage_size)+j][bands];
				}
            }
			
            /* inverse transform */
            if (xform == 1) 	/* 1 - DCT */
            {
				subimage = idct_transform(subimage, subimage_size);
			}
			else if (xform == 2)
            {
				switch (WAVELET_basis) {
				case 1:
					lowband =(int)(subimage_size>>2);
					subimage = haar_transform(subimage, 0, lowband);
					break;
				case 2: 
					lowband =(int)(subimage_size>>2);
					subimage = wavdaub4_transform(subimage, -1, lowband);
					break;
				}
            }
			
            /* put the appropriate subimage into the output image */
            for(bands = 0; bands < no_of_bands; bands++)
            {
				img_i = getData_Image(outputImage, bands);
				img_o = getData_Image(subimage, bands);
				for(r = 0; r < subimage_size; r++)
					for(c = 0; c < subimage_size; c++)
						img_i[i*subimage_size+r][j*subimage_size+c] = img_o[r][c];
			}
			
	  }	/* i for loop */
	}	/* j for loop */
	/*view_Image(outputImage, "3");*/
	
	history_copy(image, outputImage);
	delete_Image(image);
	image = outputImage;
	outputImage = NULL;
	
	/* 
	** color inverse transform 
	*/
	if (pct == 1) {
		printf("\n\npct inverse tranformed");
		image = pct_color(image, CVIP_NO, NULL, 2);
	}
	else if (ycbcr == 1) {
		printf("\n\nYCbCr inverse tranformed");
		image = YCbCr(image, 1);
	}          
	
	
   	image = remap_Image(image, CVIP_BYTE, 0, 255);
	
   	free(dc_value);
   	free(hptr);
   	free(hptr1);
   	delete_Image(subimage);
	
	return image; 
}
/* 
** End of TRCM_read_decompression() function.
*/




/*************************************************************************
**	Function Name: 	log_remap					**
**	Description:	do the log remap				**
**	Parameters:	input image...					**
**	Return:		result image					**
**	Author:		Yue Cheng					**
**	Initial Date:	3/15/00						**
*************************************************************************/
Image *log_remap(Image 	*imgP, int band)
{
	Image  		*remP,*remP1;
	IMAGE_FORMAT 	format;
	HISTORY 	stuff;
	char 		bsize[6], *assign="spectrum",
		*strP = NULL;
	float		**rdataP, **idataP, N, **odataP;
	int 		h, w, x, y, color=0, bands, k, m, *hptr, block_size;
	double 		temp, temp1;
	char		*fn = "logMap_Image";
	
	if(getDataType_Image(imgP) != CVIP_FLOAT)
		(void) cast_Image(imgP, CVIP_FLOAT);
	
	bands	= getNoOfBands_Image(imgP);
	h 	= getNoOfRows_Image(imgP);
	w 	= getNoOfCols_Image(imgP);
	
	if(band > bands-1) {
		error_CVIP(fn,"The maximum band number is %d\n",bands-1);
		band = bands-1;
	}
	if(band==-1 && bands == 3)  
		remP = new_Image(PPM,RGB,bands,h,w,CVIP_FLOAT,REAL);
	else
		remP = new_Image(PGM,GRAY_SCALE,1,h,w,CVIP_FLOAT,REAL);
	
	if(remP == NULL)
	{
		delete_Image(imgP);
		return(NULL);
	}
	
	/* Not COMPLEX */
	for (k = 0; k < bands; k++) 
	{
		if(band != -1) k = band;
		rdataP = getRealData_Matrix(getBand_Image(imgP, k));
		if(band ==-1)
			odataP = getRealData_Matrix(getBand_Image(remP, k));
		else
			odataP = getRealData_Matrix(getBand_Image(remP, 0));
		
		/*fprintf(stdout, "\nlog remap");*/
		for(y = 0; y < h; y++) 
			for(x = 0; x < w; x++) {
			/*if(y == 0 && x ==0)
				fprintf(stdout, "\nI[%d][%d] = %f", y, x, rdataP[y][x]);*/
				
				temp = (double)(rdataP[y][x]);
				
				/*odataP[y][x] = (float)log10(1.0+temp);*/
				odataP[y][x] = (float)log10(1.0+temp) / log10(1.05);
				/*if(y == 0 && x ==0)
				fprintf(stdout, "\nI[%d][%d] = %f", y, x, odataP[y][x]);*/
				if(temp < 0.0)
					fprintf(stdout, "\nI[%d][%d] = %f", y, x, rdataP[y][x]);
			} 
			if(band !=-1)
				break;
	}
	
	
	if (imgP) delete_Image(imgP);
	
	return remP;
}
/*
** end of log_remap function 
*/



/*************************************************************************
**	Function Name: 	inverse_log_remap				**
**	Description:	do the inverse log remap			**
**	Parameters:	input image...					**
**	Return:		result image					**
**	Author:		Yue Cheng					**
**	Initial Date:	3/15/00						**
*************************************************************************/
Image *inverse_log_remap(Image *imgP, int band)
{
	Image  		*remP,*remP1;
	IMAGE_FORMAT 	format;
	HISTORY 	stuff;
	char 		bsize[6], *assign="spectrum",
		*strP = NULL;
	float		**rdataP, **idataP, N, **odataP;
	int 		h, w, x, y, color=0, bands, k, m, *hptr, block_size;
	double 		temp;
	char		*fn = "logMap_Image";
	
	if(getDataType_Image(imgP) != CVIP_FLOAT)
		(void) cast_Image(imgP, CVIP_FLOAT);
	
	bands	= getNoOfBands_Image(imgP);
	h 	= getNoOfRows_Image(imgP);
	w 	= getNoOfCols_Image(imgP);
	
	if(band > bands-1) {
		error_CVIP(fn,"The maximum band number is %d\n",bands-1);
		band = bands-1;
	}
	if(band==-1 && bands == 3)  
		remP = new_Image(PPM,RGB,bands,h,w,CVIP_FLOAT,REAL);
	else
		remP = new_Image(PGM,GRAY_SCALE,1,h,w,CVIP_FLOAT,REAL);
	
	if(remP == NULL)
	{
		delete_Image(imgP);
		return(NULL);
	}
	
	/* Not COMPLEX */
	for (k = 0; k < bands; k++) 
	{
		if(band != -1) k = band;
		rdataP = getRealData_Matrix(getBand_Image(imgP, k));
		if(band ==-1)
			odataP = getRealData_Matrix(getBand_Image(remP, k));
		else
			odataP = getRealData_Matrix(getBand_Image(remP, 0));
		
		/*fprintf(stdout, "\ninverse log remap\n");*/
		for(y = 0; y < h; y++) 
			for(x = 0; x < w; x++) {
			/*if(y == 0 && x ==0)
				fprintf(stdout, "\nI[%d][%d] = %f", y, x, rdataP[y][x]);*/
				/*temp = (double)pow(10, rdataP[y][x]);*/
				temp = (double)pow(1.05, rdataP[y][x]);
				odataP[y][x] = (float)(temp - 1.0);
				
			} 
			if(band !=-1)
				break;
	}
	
	
	if (imgP) delete_Image(imgP);
	
	return remP;
}
/*
** end of inverse_log_remap function 
*/


/*************************************************************************
**	Function Name: 	band_remap					**
**	Description:	do the remap					**
**	Parameters:	input image...					**
**	Author:		Yue Cheng					**
**	Initial Date:	3/15/00						**
*************************************************************************/
void band_remap(Image *image, Image *outputImage, int remap_type, int begin_rows, int end_rows, int begin_cols, int end_cols, float *min_max)
{
	Image	*sub_image;
	IMAGE_FORMAT image_format;
	COLOR_FORMAT color_space;
	CVIP_TYPE    data_type, data_type_o;
	FORMAT       data_format;
	float   	**img_i, **img_sub; 
	byte		**img_o, **img_sub1;
	short	**img_o_s, ** img_sub1_s;
	
	int		r, c, bands;
	unsigned 	no_of_rows, no_of_cols, no_of_bands;
	
	float 	*min_max_sub;
	
	no_of_rows =  end_rows - begin_rows;
	no_of_cols =  end_cols - begin_cols;
	
	no_of_bands = getNoOfBands_Image(image);
	image_format = getFileFormat_Image(image);
	color_space = getColorSpace_Image(image);
	data_format = getDataFormat_Image(image);
	data_type = getDataType_Image(image);
	data_type_o = getDataType_Image(outputImage);
	
	sub_image = new_Image(image_format, color_space, no_of_bands, no_of_rows, no_of_cols, data_type, data_format);
	
	for(bands = 0; bands < no_of_bands; bands++)
	{
		img_i = getData_Image(image, bands);
		img_sub = getData_Image(sub_image, bands);
		
		for(r = 0; r < no_of_rows; r++)
			for(c= 0; c < no_of_cols; c++)
			{
				img_sub[r][c] = img_i[begin_rows + r][begin_cols + c];
			}
	}
	
	min_max_sub = malloc(sizeof(float)*2);
	min_max_sub = min_max_Image(sub_image);
	/*fprintf(stdout, "\nsub_image before log_remap: min_sub = %f, max_sub = %f\n, min = %f, max = %f", min_max_sub[0], min_max_sub[1], min_max[0], min_max[1]);*/
	
	(void)history_copy(image, sub_image);
	
	if(remap_type == 2)
	{
		sub_image = log_remap(sub_image, -1);
	}
	min_max_sub = min_max_Image(sub_image);
	min_max[0] = min_max_sub[0];
	min_max[1] = min_max_sub[1];
	/*fprintf(stdout, "\n\nsub_image after log_remap: min_sub = %f, max_sub = %f\n, min = %f, max = %f", min_max_sub[0], min_max_sub[1], min_max[0], min_max[1]);*/
	
	if(data_type_o == CVIP_BYTE)
	{
		/*fprintf(stdout, "\nband_remap :CVIP_BYTE\n");*/
		sub_image = remap_Image(sub_image, CVIP_BYTE, 0, 255);
	}
	else if(data_type_o == CVIP_SHORT)
	{
		/*fprintf(stdout, "\nband_remap : CVIP_SHORT\n");*/
		sub_image = remap_Image(sub_image, CVIP_SHORT, 0, 32767);
		
	}
	data_type = getDataType_Image(sub_image);
	/*fprintf(stdout, "\nafter remap to float: data_type = %d", data_type);*/
	
	for(bands = 0; bands < no_of_bands; bands++)
	{
		if(data_type_o == CVIP_BYTE)
		{
			img_sub1 = getData_Image(sub_image, bands);
			img_o = getData_Image(outputImage, bands);
			
			for(r = 0; r < no_of_rows; r++)
				for(c= 0; c < no_of_cols; c++)
				{
					img_o[begin_rows + r][begin_cols + c] = img_sub1[r][c];
				}
		}
		else if(data_type_o == CVIP_SHORT)
		{
			img_sub1_s = getData_Image(sub_image, bands);
			img_o_s = getData_Image(outputImage, bands);
			
			for(r = 0; r < no_of_rows; r++)
				for(c= 0; c < no_of_cols; c++)
				{
					img_o_s[begin_rows + r][begin_cols + c] = img_sub1_s[r][c];
				}
		}
	}
	
	delete_Image(sub_image);
	free(min_max_sub);
	
}
/*
** end of band_remap function 
*/



/*************************************************************************
**	Function Name: 	inverse_band_remap				**
**	Description:	do the inverse remap				**
**			temp_image is out, outputImage is in		**
**	Parameters:	input image...					**
**	Return:		result image					**
**	Author:		Yue Cheng					**
**	Initial Date:	3/15/00						**
*************************************************************************/
Image* inverse_band_remap(Image *temp_image, Image *outputImage, int remap_type, int begin_rows, int end_rows, int begin_cols, int end_cols, float min, float max, float minimum)
{
	Image	*sub_image;
	IMAGE_FORMAT image_format;
	COLOR_FORMAT color_space;
	CVIP_TYPE    data_type;
	FORMAT       data_format;
	byte   	**img_i, **img_sub1;
	short   	**img_i_s, **img_sub1_s; 
	float	**img_o, **img_sub2;
	float	**img_R, **img_G, **img_B, **img_o_R, **img_o_G, **img_o_B;
	
	int		r, c, bands, count;
	unsigned 	no_of_rows, no_of_cols, no_of_bands;
	
	float	*min_max_sub, *min_max;
	
	float	temp1, temp2;
	
	int		pct = 0, count_R = 0, count_G = 0, count_B = 0;
	CVIP_BOOLEAN R = CVIP_NO, G = CVIP_NO, B = CVIP_NO;
	
	no_of_rows =  end_rows - begin_rows;
	no_of_cols =  end_cols - begin_cols;
	
	no_of_bands = getNoOfBands_Image(outputImage);
	image_format = getFileFormat_Image(outputImage);
	color_space = getColorSpace_Image(outputImage);
	data_format = getDataFormat_Image(outputImage);
	data_type = getDataType_Image(outputImage);
	
	/*fprintf(stdout, "\nenter band_remap");*/
	sub_image = new_Image(image_format, color_space, no_of_bands, no_of_rows, no_of_cols, data_type, data_format);
	/*fprintf(stdout, "\ndata_type = %d\n", data_type);*/
	
	for(bands = 0; bands < no_of_bands; bands++)
	{
		if(data_type == CVIP_BYTE)
		{
			img_i = getData_Image(outputImage, bands);
			img_sub1 = getData_Image(sub_image, bands);
			
			for(r = 0; r < no_of_rows; r++)
				for(c= 0; c < no_of_cols; c++)
				{
					img_sub1[r][c] = img_i[begin_rows + r][begin_cols + c];
					
				}
		}
		else if(data_type == CVIP_SHORT)
		{
			img_i_s = getData_Image(outputImage, bands);
			img_sub1_s = getData_Image(sub_image, bands);
			
			for(r = 0; r < no_of_rows; r++)
				for(c= 0; c < no_of_cols; c++)
				{
					img_sub1_s[r][c] = img_i_s[begin_rows + r][begin_cols + c];
					
				}
		}
	}
	(void) cast_Image(sub_image, CVIP_FLOAT);
	
	(void)history_copy(temp_image, sub_image);
	if(history_check(PCT, sub_image))
	{
		pct = 1;
	}
	
	min_max_sub = malloc(sizeof(float)*2);
	min_max_sub = min_max_Image(sub_image);
	/*fprintf(stdout, "\nsub_image before inverse_log_remap: min_sub = %f, max_sub = %f\n", min_max_sub[0], min_max_sub[1]);
	fprintf(stdout, "\n\t min = %f, max = %f\n", min, max);*/
	
	if((min_max_sub[0] == 0.0) && (min_max_sub[1] == 0.0))
	{
		/*fprintf(stdout, "\nenter ZERO!!!");*/
		for(bands = 0; bands < no_of_bands; bands++)
		{
			img_sub2 = getData_Image(sub_image, bands);
			img_o = getData_Image(temp_image, bands);
			
			for(r = 0; r < no_of_rows; r++)
				for(c= 0; c < no_of_cols; c++)
				{
					img_o[begin_rows + r][begin_cols + c] = 0.0;
				}
		}
	}
	else
	{
		if(pct == 0) /* no PCT has been performed */
		{
			for(bands = 0; bands < no_of_bands; bands++)
			{
				img_sub2 = getData_Image(sub_image, bands);
				
				for(r = 0; r < no_of_rows; r++)
					for(c= 0; c < no_of_cols; c++)
					{
						if(data_type == CVIP_BYTE)
						{ 
						/*if(bands == 0 && r == 0 && c == 0)
							fprintf(stdout, "\nCVIP_BYTE\n");*/
							img_sub2[r][c] = (img_sub2[r][c] - 0.0) * fabs(max -min) / (255.0 - 0.0) + min;
						}
						else if(data_type == CVIP_SHORT)
						{ 
						/*if(bands == 0 && r == 0 && c == 0)
							fprintf(stdout, "\nCVIP_SHORT\n");*/
							img_sub2[r][c] = (img_sub2[r][c] - 0.0) * fabs(max -min) / (32767.0 - 0.0) + min;
						}
					}
			}
			
			data_type = getDataType_Image(sub_image);
			/*fprintf(stdout, "\nafter remap to float: data_type = %d", data_type);*/
			min_max = malloc(sizeof(float)*2);
			min_max = min_max_Image(sub_image);
			/*fprintf(stdout, "\nafter float->float: [%f, %f]\n", min_max[0], min_max[1]);*/
			
			if(remap_type == 2 || remap_type == 3)
			{
				sub_image = inverse_log_remap(sub_image, -1);
			}
			min_max_sub = min_max_Image(sub_image);
			/* fprintf(stdout, "\nsub_image after inverse_log_remap: min_sub = %f, max_sub = %f\n", min_max_sub[0], min_max_sub[1]);*/
			
			for(bands = 0; bands < no_of_bands; bands++)
			{
				img_sub2 = getData_Image(sub_image, bands);
				img_o = getData_Image(temp_image, bands);
				
				for(r = 0; r < no_of_rows; r++)
					for(c= 0; c < no_of_cols; c++)
					{
						if(remap_type == 2)
							img_o[begin_rows + r][begin_cols + c] = img_sub2[r][c] - fabs(minimum);
						else if(remap_type == 1)
							img_o[begin_rows + r][begin_cols + c] = img_sub2[r][c];
					}
			}
		}
		else if(pct == 1)
		{
			img_R = getData_Image(sub_image, 0);
			img_G = getData_Image(sub_image, 1);
			img_B = getData_Image(sub_image, 2);
			
			for(r = 0; r < no_of_rows; r++)
				for(c= 0; c < no_of_cols; c++)
				{
					if(img_R[r][c] == 0.0)
					{
						count_R = count_R + 1;
					}
					if(img_G[r][c] == 0.0)
					{
						count_G = count_G + 1;
					}
					if(img_B[r][c] == 0.0)
					{
						count_B = count_B + 1;
					}
				}
				if(count_R == (no_of_rows * no_of_cols))
				{
					R = CVIP_YES;
				}
				if(count_G == (no_of_rows * no_of_cols))
				{
					G = CVIP_YES;
				}
				if(count_B == (no_of_rows * no_of_cols))
				{
					B = CVIP_YES;
				}
				
				
				for(bands = 0; bands < no_of_bands; bands++)
				{
					img_sub2 = getData_Image(sub_image, bands);
					
					for(r = 0; r < no_of_rows; r++)
						for(c= 0; c < no_of_cols; c++)
						{
							if(data_type == CVIP_BYTE)
							{ 
							/*if(bands == 0 && r == 0 && c == 0)
								fprintf(stdout, "\nCVIP_BYTE\n");*/
								img_sub2[r][c] = (img_sub2[r][c] - 0.0) * fabs(max -min) / (255.0 - 0.0) + min;
							}
							else if(data_type == CVIP_SHORT)
							{ 
							/*if(bands == 0 && r == 0 && c == 0)
								fprintf(stdout, "\nCVIP_SHORT\n");*/
								img_sub2[r][c] = (img_sub2[r][c] - 0.0) * fabs(max -min) / (32767.0 - 0.0) + min;
							}
						}
				}
				
				if(remap_type == 2)
				{
					sub_image = inverse_log_remap(sub_image, -1);
				}
				min_max_sub = min_max_Image(sub_image);
				/*fprintf(stdout, "\nsub_image after inverse_log_remap: min_sub = %f, max_sub = %f\n", min_max_sub[0], min_max_sub[1]);*/
				
				img_R = getData_Image(sub_image, 0);
				img_G = getData_Image(sub_image, 1);
				img_B = getData_Image(sub_image, 2);
				
				img_o_R = getData_Image(temp_image, 0);
				img_o_G = getData_Image(temp_image, 1);
				img_o_B = getData_Image(temp_image, 2);
				
				for(r = 0; r < no_of_rows; r++)
					for(c= 0; c < no_of_cols; c++)
					{	
						if(!R) 
						{ 
							if(remap_type == 2)
								img_o_R[begin_rows + r][begin_cols + c] = img_R[r][c] - fabs(minimum);
							else if(remap_type == 1)
								img_o_R[begin_rows + r][begin_cols + c] = img_R[r][c];
						}
						else
						{ 
							img_o_R[begin_rows + r][begin_cols + c] = 0.0;
						}
						
						if(!G)
						{
							if(remap_type == 2)
								img_o_G[begin_rows + r][begin_cols + c] = img_G[r][c] - fabs(minimum);
							else if(remap_type == 1)
								img_o_G[begin_rows + r][begin_cols + c] = img_G[r][c];
						}
						else
						{ 
							img_o_G[begin_rows + r][begin_cols + c] = 0.0;
						}
						
						if(!B)
						{
							if(remap_type == 2)
								img_o_B[begin_rows + r][begin_cols + c] = img_B[r][c] - fabs(minimum);
							else if(remap_type == 1)
								img_o_B[begin_rows + r][begin_cols + c] = img_B[r][c];
						}
						else
						{ 
							img_o_B[begin_rows + r][begin_cols + c] = 0.0;
						}
					}	  
   }
   
   }
   delete_Image(sub_image);
   free(min_max_sub);
   
   return temp_image;
   
}
/*
** end of inverse_band_remap function 
*/

/*************************************************************************
**	Function Name: 	min_max_Image					**
**	Description:	find the minimum and maximum value of a image	**
**	Parameters:	image -- input image				**
**	Return:		float pointer, ->[0]:min, ->[1]: max		**
**	Author:		Yue Cheng					**
**	Initial Date:	3/15/00						**
*************************************************************************/
float *min_max_Image(Image *image)
{
	int  	no_of_bands, imgsize, rows, cols;
	float   	*min_maxP = NULL;
	int		r, c, bands;
	float	**img;
	float 	min, max;
	
	/*(void)cast_Image(image, CVIP_FLOAT);*/
	
	no_of_bands = getNoOfBands_Image(image);
	rows = getNoOfRows_Image(image);
	cols = getNoOfCols_Image(image);
	
	min_maxP  = (float *) malloc(sizeof(float)*2);
	
	for(bands = 0; bands < no_of_bands; bands++)
	{
		img = getData_Image(image, bands);
		for(r = 0; r < rows; r++)
			for(c = 0; c < cols; c++)
			{
				if(bands == 0 && r == 0 && c == 0)
				{
					min = img[r][c];
					max = img[r][c];
				}
				else
				{
					if(min > img[r][c])
						min = img[r][c];
					if(max < img[r][c])
						max = img[r][c];
				}   
			}
	}
	
	min_maxP[0] = min;
	min_maxP[1] = max;
	
	return min_maxP;  
}
/*
** end of min_max_Image function 
*/



/*****************************************************************
**	Function Name: 	YCbCr					**
**	Description:	Do YCbCr color transform		**
**	Parameters:	image -- input image			**
**			isign -- 0: forward, 1: inverse 	**
**	Return:		result image				**
**	Author:		Zhijian Lin				**
**	Initial Date:	11/15/00				**
*****************************************************************/
Image *YCbCr(Image *image, int isign)
{
	Image		*outputImage; 	
	IMAGE_FORMAT 	image_format;
	COLOR_FORMAT 	color_space;
   	FORMAT       	data_format;
	unsigned     	no_of_rows, 
		no_of_cols, 
		no_of_bands;
	int 		r, c, bands;
	float		**img_R, **img_G, **img_B,
		**img_Y, **img_Cb, **img_Cr,
		**img_o, **img_i;
   	
	no_of_rows =  getNoOfRows_Image(image);
	no_of_cols =  getNoOfCols_Image(image);
	no_of_bands = getNoOfBands_Image(image);
	image_format = getFileFormat_Image(image);
	color_space = getColorSpace_Image(image);
	data_format = getDataFormat_Image(image);
	outputImage = new_Image(image_format, color_space, no_of_bands, no_of_rows, no_of_cols, CVIP_FLOAT, data_format);
	
	
	if(image->image_ptr[0]->data_type != CVIP_FLOAT)
		(void)cast_Image(image, CVIP_FLOAT);
	
	if (isign == 0) {
		if (no_of_bands == 1) {
			
		}
		else {
            img_R = getData_Image(image, 0);
            img_G = getData_Image(image, 1);
            img_B = getData_Image(image, 2);
            img_Y = getData_Image(outputImage, 0);
            img_Cb = getData_Image(outputImage, 1);
            img_Cr = getData_Image(outputImage, 2);
            for(r = 0; r < no_of_rows; r++)
				for(c = 0; c < no_of_cols; c++) {
					img_Y[r][c] = 0.299*img_R[r][c]+0.587*img_G[r][c]+0.114*img_B[r][c];
					img_Cb[r][c] = -0.1687*img_R[r][c]-0.3313*img_G[r][c]+0.5*img_B[r][c]+16;
					img_Cr[r][c] = 0.5*img_R[r][c]-0.4187*img_G[r][c]-0.0813*img_B[r][c]+16;
				}
		}
	}
	else if (isign == 1) {
		if (no_of_bands == 1) {
			
		}
		else {
            img_Y = getData_Image(image, 0);
            img_Cb = getData_Image(image, 1);
            img_Cr = getData_Image(image, 2);
            img_R = getData_Image(outputImage, 0);
            img_G = getData_Image(outputImage, 1);
            img_B = getData_Image(outputImage, 2);
            for(r = 0; r < no_of_rows; r++)
				for(c = 0; c < no_of_cols; c++) {
					img_R[r][c] = img_Y[r][c]+1.402*img_Cr[r][c];
					img_G[r][c] = img_Y[r][c]-0.34414*(img_Cb[r][c]-16)-0.71414*(img_Cr[r][c]-16);
					img_B[r][c] = img_Y[r][c]+1.722*(img_Cb[r][c]-16);
				}
		}
	}
	else {
		printf("\n\nError at YCbCr transform: no such isign.");
		return NULL;
	}
	
	for(bands = 0; bands < no_of_bands; bands++)
	{
		img_i = getData_Image(outputImage, bands);
		img_o = getData_Image(image, bands);
		for(r = 0; r < no_of_rows; r++)
            for(c = 0; c < no_of_cols; c++)
				img_o[r][c] = img_i[r][c];
	}
	
	delete_Image(outputImage);
	return image;
}
/*
** end of YCbCr function 
*/


/*************************************************************************
**	Function Name: 	entropy						**
**	Description:	Caculate the Entropy of partial or whole image	**
**	Parameters:	image 	-- input image				**
**			others 	-- coordinates 				**
**	Return:		void						**
**	Author:		Zhijian Lin					**
**	Initial Date:	2/23/01						**
*************************************************************************/
void entropy(Image *image, int begin_row, int begin_col, int end_row, int end_col)
{
/*
** structure to hold the number of pixels that have the same value;
   	*/
   	struct value_number		
   	{
		float value;
		int	number;
		int	flag;
   	} **value_number_ptr;
   	
	float	**img;	
	int	no_of_rows, no_of_cols, no_of_bands;
   	int	r, c, r1, c1, bands, i;
   	float	prob, entropy[3];
	
	/*
	** cast image to CVIP_FLOAT
	*/
	if (image->image_ptr[0]->data_type != CVIP_FLOAT) {
		cast_Image(image, CVIP_FLOAT);
	}
	
	/* 
	** get the rows, cols and bands
	*/
	no_of_rows =  getNoOfRows_Image(image);
	no_of_cols =  getNoOfCols_Image(image);
	no_of_bands = getNoOfBands_Image(image);
	if (begin_row<0 || begin_row>=no_of_rows || end_row<0 || end_row>=no_of_rows ||
		begin_col<0 || begin_col>=no_of_cols || end_col<0 || end_col>=no_of_cols ||
		end_row <= begin_row || end_col<= begin_col) {
		printf("\nError in entropy, specified coordinates out of range");
		return;
	}
	no_of_rows = end_row - begin_row + 1;
	no_of_cols = end_col - begin_col + 1;
	
	/*
	** assign memory to value_number array
	*/
	value_number_ptr = (struct value_number **)malloc(sizeof(struct value_number *)*(no_of_rows*no_of_cols));
	for (i = 0; i < no_of_rows*no_of_cols; i++) {
		value_number_ptr[i] = (struct value_number *)malloc(sizeof(struct value_number));
	}
	
	/* 
	** initialization 
	*/
	entropy[0] = 0;
	entropy[1] = 0;
	entropy[2] = 0;
	
	/*
	** calculate the entropy on each band
	*/
	for(bands = 0; bands < no_of_bands; bands++)
   	{
     	  /* initialization */
     	  value_number_ptr[0]->flag = 0;
		  
		  /* get the number of values and the number of pixels of one value */
		  img = getData_Image(image, bands);
		  for(r = begin_row; r < end_row+1; r++)
			  for(c = begin_col; c < end_col+1; c++)
			  {
				  for (i = 0; i < no_of_rows*no_of_cols; i++)
				  {
					  if (value_number_ptr[i]->flag == 0)
					  {
						  value_number_ptr[i]->flag = 1;
						  value_number_ptr[i+1]->flag = 0;
						  value_number_ptr[i]->value = img[r][c];
						  value_number_ptr[i]->number = 1;
						  break;
					  }
					  else if (img[r][c] == value_number_ptr[i]->value)
					  {
						  value_number_ptr[i]->number++;
						  break;
					  }
				  }
			  }
			  
			  
			  for (i = 0; i < no_of_rows*no_of_cols; i++)
			  {
				  if (value_number_ptr[i]->flag != 0) {
					  prob = (float)value_number_ptr[i]->number / (float)(no_of_rows*no_of_cols);
					  entropy[bands] += (-1) * prob * (log(prob)/log(2));
				  }
				  else {
					  break;
				  }
			  } 
			  
	} /* end of bands for loop */
	
	(void)free(value_number_ptr);
	
	printf("\nThe entropy is\n");
	printf("red: %f, green: %f, blue: %f\n", entropy[0], entropy[1], entropy[2]);
}
/*
** end of function entropy
*/


/*************************************************************************
**	Function Name: 	copy_Image_local				**
**	Description:	Caculate the Entropy of partial or whole image	**
**	Parameters:	image 	-- input image				**
**			others 	-- coordinates 				**
**	Return:		Entropy of each band				**
**			[0]: Red band, [1]: Green band, [2]: Blue band 	**
**	Author:		Zhijian Lin					**
**	Initial Date:	2/23/01						**
*************************************************************************/
Image* copy_Image_local(Image *inImage) 
{
	Image 		*outImage;
	IMAGE_FORMAT 	image_format;
	COLOR_FORMAT 	color_space;
   	FORMAT       	data_format;
	unsigned     	no_of_rows, 
		no_of_cols, 
		no_of_bands;
	int 		r, c, bands;
	float		**img_i, **img_o;
	
	
	/* 
	** cast input image to CVIP_FLOAT 
	*/
	if(inImage->image_ptr[0]->data_type != CVIP_FLOAT) {
		(void)cast_Image(inImage, CVIP_FLOAT);
	}
	
	/*
	** get the properties of the image 
	*/
   	no_of_rows =  getNoOfRows_Image(inImage);
	no_of_cols =  getNoOfCols_Image(inImage);
	no_of_bands = getNoOfBands_Image(inImage);
	image_format = getFileFormat_Image(inImage);
	color_space = getColorSpace_Image(inImage);
	data_format = getDataFormat_Image(inImage);
	
	outImage = new_Image(image_format, color_space, no_of_bands, no_of_rows, no_of_cols, CVIP_FLOAT, data_format);
	
	
	for(bands = 0; bands < no_of_bands; bands++)
	{
		img_i = getData_Image(inImage, bands);
		img_o = getData_Image(outImage, bands);
		for(r = 0; r < no_of_rows; r++)
            for(c = 0; c < no_of_cols; c++)
				img_o[r][c] = img_i[r][c];
	}
	
	history_copy(inImage, outImage);
	
	return outImage;
}
