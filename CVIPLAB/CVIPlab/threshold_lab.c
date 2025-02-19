/***************************************************************************
* =========================================================================
*
*   Computer Vision and Image Processing Lab - Dr. Scott Umbaugh SIUE
*
* =========================================================================
*
*             File Name: threshold_lab.c
*           Description: it contains the function to threshold BYTE images
*   Initial Coding Date: April 23, 1996
*           Portability: Standard (ANSI) C
*             Credit(s): Zhen Li & Kun Luo
*                        Southern Illinois University at Edwardsville
*
** Copyright (c) 1995, 1996, SIUE - Scott Umbaugh, Kun Luo, Yansheng Wei
****************************************************************************/

/*
** include header files
*/

#include "CVIPtoolkit.h"
#include "CVIPconvert.h"
#include "CVIPdef.h"
#include "CVIPimage.h"
#include "CVIPlab.h"


/*
** The following function will compare the actual gray level of the input image
** with the threshold limit. If the gray-level value is greater than the
** threshold limit then the gray level is set to 255 (WHITE_LAB) else to
** 0 (BLACK_LAB). Note that the '_LAB' or '_lab' is appended to names used
** in CVIPlab to avoid naming conflicts with existing constant and function
** (e.g. threshold_lab) names.
*/

#define 	WHITE_LAB	255
#define		BLACK_LAB	0

Image *threshold_lab(Image *inputImage, unsigned int threshval) {
	byte 		**image; 	/* 2-d matrix data pointer */
	unsigned int 		r,		/* row index */
		c, 		/* column index */
		bands;		/* band index */

	unsigned int 	no_of_rows,	/* number of rows in image */
		no_of_cols,	/* number of columns in image */
		no_of_bands;	/* number of image bands */

						/*
						** Gets the number of image bands (planes)
						*/
	no_of_bands = getNoOfBands_Image(inputImage);

	/*
	** Gets the number of rows in the input image
	*/
	no_of_rows = getNoOfRows_Image(inputImage);

	/*
	** Gets the number of columns in the input image
	*/
	no_of_cols = getNoOfCols_Image(inputImage);

	/*
	** Compares the pixel value at the location (r,c)
	** with the threshold value. If it is greater than
	** the threshold value it writes 255 at the location
	** else it writes 0. Note thta this assumes the input
	** image is of data type BYTE.
	*/
	for (bands = 0; bands < no_of_bands; bands++) {
		/*
		** reference each band of image data in 2-d matrix form;
		** which is used for reading and writing the pixel values
		*/
		image = getData_Image(inputImage, bands);
		for (r = 0; r < no_of_rows; r++) {
			for (c = 0; c < no_of_cols; c++) {
				if (image[r][c] >(byte) threshval)
					image[r][c] = WHITE_LAB;
				else
					image[r][c] = BLACK_LAB;
			}
		}
	}

	return inputImage;
}
/*
** end of function threshold_lab
*/
