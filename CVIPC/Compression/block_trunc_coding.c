/***************************************************************************
* **********************************************************************
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* **********************************************************************
*
*             File Name: btc.c
*           Description:
*         Related Files:
*   Initial Coding Date: Fri May 02, 1997
*           Portability: Standard (ANSI) C
*            References:
*             Author(s): kcai, Hong Niu, Zhen Li and Kun Luo
*                        Southern Illinois University @ Edwardsville
*
** Copyright (C) 1996 SIUE - by Scott Umbaugh, kcai, Kun Luo, H. Niu, Z. Li.
**
** Permission to use, copy, modify, and distribute this software and its
** documentation for any purpose and without fee is hereby granted, provided
** that the above copyright notice appear in all copies and that both that
** copyright notice and this permission notice appear in supporting
** documentation.  This software is provided "as is" without express or
** implied warranty.
**
*******************************************************************************/
#include <stdio.h>
#include <string.h>
#include <math.h>				
#include "CVIPdef.h"
#include "CVIPimage.h"
#include "CVIPconvert.h"
#include "block_trunc_coding.h"
#include <sys/types.h>
#include <sys/stat.h>
#ifndef WIN32
#include <unistd.h>
#endif


/*
** declaration of function prototypes
*/

static char* BTC_Image(Image *inputImage);

static int write_btc_file_header(Image* input, int blocksize, char* output);
static int read_btc_file_header(FILE *fp);

static int
encode_block(byte **image, int blockx, int blocky, int blocksize, int bands, FILE *fp);
static int
decode_block(byte **image, int blockx, int blocky, int blocksize, int bands, FILE *fp);


extern char temp_dir[100];
extern char *Cmpr_Name[];

Image * btc(Image *cvipImage)
{
	Image *decodeImage;
	char  *outputfile;

	outputfile = BTC_Image(cvipImage);
	if (outputfile == NULL)
		return NULL;
	decodeImage = btc_decompress(outputfile);
	free(outputfile);

	if (cvipImage) delete_Image(cvipImage);
	return decodeImage;
}


static char * BTC_Image(Image *inputImage) {
	int  blocksize;
	char *outputfile;	/* output file name */

	print_CVIP("\n\t\tEnter the block size:  ");
	blocksize = getInt_CVIP(10, 0, 64);

	outputfile = (char*)malloc(150);
	strcpy(outputfile, temp_dir);
	strcat(outputfile, "/__");
	strcat(outputfile, Cmpr_Name[Btc]);

	if (btc_compress(inputImage, outputfile, blocksize) < 0) {
		free(outputfile);
		return (char *)NULL;
	}
	else
		return outputfile;

}


int btc_compress(Image *inputImage, char *filename, int blocksize) {

	FILE 		*fp;
	struct stat	s_buf;
	long		counter;
	byte 		**image; 	/* 2-d matrix data pointer */

	int 		y,		/* row index */
		x, 		/* column index */
		bands,		/* band index */
		level[2] = { 0,0 },	/* quantization levels */
		blockx, blocky, xnum, ynum,	/* block number */
		l = 0, j;

	unsigned int 	rows, 		/* number of rows in image */
		cols,		/* number of columns in image */
		no_of_bands;	/* number of image bands */

	if (blocksize <3) {
		printf("The block size is too small. \n");
		if (inputImage) delete_Image(inputImage);
		return -1;
	}

	/*
	** Gets the number of image bands (planes)
	*/
	no_of_bands = getNoOfBands_Image(inputImage);

	/*
	** Gets the number of rows in the input image
	*/
	rows = getNoOfRows_Image(inputImage);

	/*
	** Gets the number of columns in the input image
	*/
	cols = getNoOfCols_Image(inputImage);

	/*
	** reference each band of image data in 2-d matrix form;
	** which is used for reading and writing the pixel values
	*/

	write_btc_file_header(inputImage, blocksize, filename);

#ifndef WIN32
	if ((fp = fopen(filename, "a")) == NULL) {
#else
	if ((fp = fopen(filename, "ab")) == NULL) {
#endif
		printf("cannot open file to write\n");
		if (inputImage) delete_Image(inputImage);
		return -1;
	}

	for (bands = 0; bands < no_of_bands; bands++) {
		image = getData_Image(inputImage, bands);
		xnum = cols / blocksize;
		ynum = rows / blocksize;
		for (blocky = 0; blocky<ynum; blocky++)
			for (blockx = 0; blockx<xnum; blockx++) {
				encode_block(image, blockx, blocky, blocksize, bands, fp);

			}
	}

	/*fsync(fileno(fp));*/
	fflush(fp);
	fclose(fp);
	if (stat(filename, &s_buf) == 0) {
		counter = (long)s_buf.st_size;
		printf("\nThe original raw data occupies %ld bytes", rows*cols*no_of_bands);
		printf("\nThe compressed data occupies %ld bytes", counter);
		printf(" \nCompression ratio 1 : %f\n", (rows*cols*bands) / (float)counter);
	}

	if (inputImage) delete_Image(inputImage);
	return 0;
	}
/*
** end of function BTC_Image
*/


/* compress the image to a data file */
static int write_btc_file_header(Image* input, int blocksize, char* output) {
	CVIP_TYPE      image_type;
	IMAGE_FORMAT   image_format;
	int            rows, cols, bands;
	FORMAT         data;
	COLOR_FORMAT   color;
	FILE           *fp;

	if ((fp = fopen(output, "wb")) == NULL) {
		printf("cannot open file to write\n");
		return -1;
	}

	putc((int)'b', fp);
	putc((int)'t', fp);
	putc((int)'c', fp);

	image_format = getFileFormat_Image(input);
	color = getColorSpace_Image(input);
	bands = getNoOfBands_Image(input);
	rows = getNoOfRows_Image(input);
	cols = getNoOfCols_Image(input);
	image_type = getDataType_Image(input);
	data = getDataFormat_Image(input);

	/* save Image format data */
	if (fwrite(&image_format, sizeof(image_format), 1, fp) != 1) {
		printf("cannot write1\n");
		exit(0);
	}
	if (fwrite(&color, sizeof(color), 1, fp) != 1) {
		printf("cannot write2\n");
		exit(0);
	}
	if (fwrite(&bands, sizeof(bands), 1, fp) != 1) {
		printf("cannot write3\n");
		exit(0);
	}
	if (fwrite(&rows, sizeof(rows), 1, fp) != 1) {
		printf("cannot write4\n");
		exit(0);
	}
	if (fwrite(&cols, sizeof(cols), 1, fp) != 1) {
		printf("cannot write5\n");
		exit(0);
	}
	if (fwrite(&image_type, sizeof(image_type), 1, fp) != 1) {
		printf("cannot write6\n");
		exit(0);
	}
	if (fwrite(&data, sizeof(data), 1, fp) != 1) {
		printf("cannot write7\n");
		exit(0);
	}
	if (fwrite(&blocksize, sizeof(blocksize), 1, fp) != 1) {
		printf("cannot write8\n");
		exit(0);
	}

	fclose(fp);
	return 1;

}
/* end of write_btc_file_header */


/* Calculat quantization levels */
static int
encode_block(byte **image, int blockx, int blocky, int blocksize, int bands, FILE *fp)
{
	/*	byte 		**image; 	 2-d matrix data pointer */
	byte		tempLevel1, tempLevel2, tempByte2;
	int 		y,		    	/* row index */
		x, 		    	/* column index */
		i,		    	/* byte index */
		y0, y1, x0, x1;


	double		blockSum1 = 0.0, blockSum2 = 0.0,     /* defined as double instead of int
													  to avoid overflow possibility */
		moment1, moment2,
		a, b, stdDev, numPixel = 0,               /* the number of pixels which have graylevel
												  higher than the first moment */
		temp1;

	int		counter = 0,
		level[2],
		tempByte;

	//short ;

	/*calculate the first moment and the second moment */
	x0 = blocksize*blockx;
	y0 = blocksize*blocky;
	x1 = blocksize*(blockx + 1);
	y1 = blocksize*(blocky + 1);
	for (y = y0; y<y1; y++) {
		for (x = x0; x<x1; x++) {
			blockSum1 += (double)image[y][x];
			blockSum2 += (double)image[y][x] * image[y][x];
		}
	}

	moment1 = blockSum1 / (blocksize*blocksize);
	moment2 = blockSum2 / (blocksize*blocksize);

	/*Got a netative value inside the sqrt */
	stdDev = abs(sqrt(moment2 - moment1*moment1));

	for (y = y0; y<y1; y++) {
		for (x = x0; x<x1; x++) {
			if ((double)image[y][x] >= moment1)
				numPixel++;
			/*         	if (y0>=132 && x0==52)
			printf("image[%d][%d] = %d,  ", y, x, (int)image[y][x]);
			*/
		}
	}

	if (numPixel != blocksize*blocksize) {
		temp1 = blocksize*blocksize - numPixel;

		level[0] = (round)(moment1 - stdDev*sqrt(numPixel / temp1));
		level[1] = (round)(moment1 + stdDev*sqrt(temp1 / numPixel));

	}
	else {
		level[0] = moment1;
		level[1] = moment1;
	}
	/*        if (y0>=132 && x0==52) {
	printf("\nblocky=%d, blockx=%d\n", blocky, blockx);
	printf("blockSum1 = %f,  blockSum2 = %f\n", blockSum1, blockSum2);
	printf("moment1 = %f,  moment2 = %f, stdDev = %f\n", moment1, moment2, stdDev);
	printf("numPixel = %d, temp1 = %d\n", numPixel, temp1);
	printf("level[0] = %d,  level[1] = %d\n\n", level[0], level[1]);
	}
	*/
	if (level[0] > 255)
		level[0] = 255;
	else if (level[0] < 0)
		level[0] = 0;

	if (level[1] > 255)
		level[1] = 255;
	else if (level[1] < 0)
		level[1] = 0;

	tempLevel1 = (byte)(level[0]);
	tempLevel2 = (byte)(level[1]);


	if (fwrite(&tempLevel1, sizeof(tempLevel1), 1, fp) != 1) {
		printf("cannot write level[0]\n");
		exit(0);
	}
	if (fwrite(&tempLevel2, sizeof(tempLevel2), 1, fp) != 1) {
		printf("cannot write level[1]\n");
		exit(0);
	}


	for (y = y0; y<y1; y++) {
		for (x = x0; x<x1; x++) {
			if ((int)image[y][x] >= moment1)
				tempByte = tempByte | 1;
			else
				tempByte = tempByte | 0;

			counter++;
			if ((counter % 8) != 0)
				tempByte = tempByte << 1;
			else {
				tempByte2 = (byte)tempByte;
				if (fwrite(&tempByte2, sizeof(tempByte2), 1, fp) != 1) {
					printf("cannot write tempByte2\n");
					exit(0);
				}

				tempByte = 0;
			}

		}
	}


	return 0;
}


/*
** end of encode_block() function
*/



Image* btc_decompress(char *filename) {
	FILE               *fp;
	Image *		decodeImage;

	if ((fp = fopen(filename, "rb")) == NULL) {
		printf("cannot open file to read\n");
		return NULL;
	}
	decodeImage = btc_decompression(fp);
	fclose(fp);

	return decodeImage;
}

Image *btc_decompression(FILE *fp) {

	Image              *inputImage;
	char	       b, t, c;
	int                blocksize, k, numOfBytes;
	byte               **image;
	CVIP_TYPE          image_type;
	IMAGE_FORMAT       image_format;
	FORMAT             dataFormat;
	COLOR_FORMAT       color;
	unsigned int       rows, cols, v, u, no_of_bands;

	int   		y,		/* row index */
		x, 		/* column index */
		bands,		/* band index */
		blockx, blocky;	/* block number */

						/*read Image Format Data*/

	b = (char)getc(fp);
	t = (char)getc(fp);
	c = (char)getc(fp);
	if (b != 'b' || t != 't' || c != 'c') {
		fprintf(stderr, "Wrong image format\n");
		return NULL;
	}
	if (fread(&image_format, sizeof(image_format), 1, fp) != 1) {
		printf("cannot read\n");
		return NULL;
	}
	if (fread(&color, sizeof(color), 1, fp) != 1) {
		printf("cannot read\n");
		return NULL;
	}
	if (fread(&no_of_bands, sizeof(no_of_bands), 1, fp) != 1) {
		printf("cannot read\n");
		return NULL;
	}

	if (fread(&rows, sizeof(rows), 1, fp) != 1) {
		printf("cannot read\n");
		return NULL;
	}

	if (fread(&cols, sizeof(cols), 1, fp) != 1) {
		printf("cannot read\n");
		return NULL;
	}

	if (fread(&image_type, sizeof(image_type), 1, fp) != 1) {
		printf("cannot read\n");
		return NULL;
	}
	if (fread(&dataFormat, sizeof(dataFormat), 1, fp) != 1) {
		printf("cannot read\n");
		return NULL;
	}
	if (fread(&blocksize, sizeof(blocksize), 1, fp) != 1) {
		printf("cannot read\n");
		return NULL;
	}

	inputImage = new_Image(image_format, color, no_of_bands, rows, cols, image_type, dataFormat);

	for (bands = 0; bands < no_of_bands; bands++) {
		image = getData_Image(inputImage, bands);
		for (blocky = 0; blocky<rows / blocksize; blocky++) {
			for (blockx = 0; blockx<cols / blocksize; blockx++) {
				decode_block(image, blockx, blocky, blocksize, bands, fp);
			}
		}
	}

	inputImage->image_format = BTC;
	return inputImage;
}
/* end of decode_file() */

/* Calculat quantization levels */
static int
decode_block(byte ** image, int blockx, int blocky, int blocksize, int bands, FILE *fp)
{

	int 		y,		    	/* row index */
		x, 		    	/* column index */
		k,		    	/* level index */
		y0, y1, x0, x1,
		level[2],
		tempByte, tempByte3,
		numOfBytes,
		i, u, v;

	byte		tempLevel, tempByte2;

	for (k = 0; k<2; k++) {
		if (fread(&tempLevel, sizeof(tempLevel), 1, fp) != 1) {
			printf("cannot read tempLevel\n");
			return 0;
		}
		else
			level[k] = (int)tempLevel;
	}


	/*calculat the first moment and the second moment */
	x0 = blocksize*blockx;
	y0 = blocksize*blocky;
	x1 = blocksize*(blockx + 1);
	y1 = blocksize*(blocky + 1);

	x = x0;
	y = y0;
	numOfBytes = blocksize*blocksize / 8;
	for (i = 0; i<numOfBytes; i++) {
		if (fread(&tempByte2, sizeof(tempByte2), 1, fp) != 1) {
			printf("cannot read tempByte2\n");
			return 0;
		}
		tempByte = (int)tempByte2;

		for (u = 0; u<8; u++) {
			tempByte3 = tempByte & 128;
			if (tempByte3 == 128)
				image[y][x] = level[1];
			else
				image[y][x] = level[0];

			tempByte = tempByte << 1;

			if (x < (x1 - 1))
				x++;
			else {
				x = x0;
				y++;
			}

		}
	}


}
/*
** end of decode_block() function
*/
