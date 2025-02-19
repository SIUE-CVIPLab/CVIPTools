/***************************************************************************
* =========================================================================
*   Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* =========================================================================
*
*             File Name: laws_texture.c
*           Description: contains the functions to calculate laws texture
*                        features
*   Initial Coding Date: January 27, 2015
*           Portability: Standard (ANSI) C
*             Credit(s): Christopher Daigle, Anthony Seganfredo,
*                        Patrick Solt, Heema kumari poudel.
*                        Southern Illinois University Edwardsville
*
*   Copyright (C) 2015 Scott Umbaugh and SIUE
*
****************************************************************************/

#define _LAWS_TEXTURE_C

// include header files
#include "CVIPimage.h"
#include "CVIPmap.h"
#include "laws_texture.h"
#include "CVIPconvert.h"

/* forward declarations */
double* hist_feature(Image* image, Image* labeled, int row, int col);
Image* label(const Image* image);
Image* laws_energy_map(Image* filtered);
Image* laws_filtered_image(Image* image, int vector1, int vector2);
Image* object_mask(Image* labeled, int row, int col, int windowsize, int* nRow, int* nCol); //nRow and cRow added to fix edge detection issue

/******************************************************************************
 *
 * laws_texture(image, labeled_image, row, col, window_size, vector1, vector2)
 *
 *   Description: Calculates and returns laws texture features for the object
 *                in input image located and coordinates row, col.
 *         image: Input image used to calculate statistics.
 * labeled_image: Labeled image used to identify specific object within
 *                input image.
 *      row, col: Identifies location of object in labeled image.
 *   window_size: Neighborhood size used in calculations.
 *       vector1: Laws vectors used to create laws filter mask used in
 *       vector2: calculations.
 *
 *****************************************************************************/
double* laws_texture(Image* image, Image* labeled_image, int row, int col, int window_size, int vector1, int vector2)
{
    double* features = NULL;
    Image *energy_map, *filtered, *mask;
	int nRow = 0;
	int nCol = 0;

    // Convolve image with laws_mask to produce filtered image
    filtered = laws_filtered_image(image, vector1, vector2);
	//write_Image(filtered, "C:\\Users\\cstacey\\Desktop\\Laws Images\\filtered.jpg", CVIP_YES, 0, VIP, 0);

    // Create energy mask image
    energy_map = laws_energy_map(filtered);
	//write_Image(energy_map, "C:\\Users\\cstacey\\Desktop\\Laws Images\\energy_map.jpg", CVIP_YES, 0, VIP, 0);

    // Create and label object mask image
	mask = object_mask(labeled_image, row, col, max(LAWS_SIZE, window_size), &nRow, &nCol);
	//write_Image(energy_map, "C:\\Users\\cstacey\\Desktop\\Laws Images\\energy_map.jpg", CVIP_YES, 0, VIP, 0);

    // Calculate histogram features on energy map image
	features = hist_feature(energy_map, mask, nRow, nCol);

    // Release memory allocated in this function
    delete_Image(energy_map);
    delete_Image(filtered);
    delete_Image(mask);

    return features;
}


/******************************************************************************
 *
 * laws_energy_map(Image* filtered)
 *
 *  Description: Creates laws energy map image from laws filtered image.
 *     filtered: Image to use to create energy map.
 *
 *****************************************************************************/
int neighborhood_sum(int** inptr, int r, int c)
{
    int i, j, sum = 0;
    for (i = -NEIGHBORHOOD_BOUND; i <= NEIGHBORHOOD_BOUND; i++)
    {
        for (j = -NEIGHBORHOOD_BOUND; j <= NEIGHBORHOOD_BOUND; j++)
        {
            sum += abs(inptr[r + i][c + j]);
        }
    }
    return sum;
}
Image* laws_energy_map(Image* filtered)
{
    int **inptr, **outptr;
    int band, bands = getNoOfBands_Image(filtered);
    int r, rows = getNoOfRows_Image(filtered);
    int c, cols = getNoOfCols_Image(filtered);
    Image* energy_map = new_Image(PPM, RGB, bands, rows, cols, CVIP_INTEGER, REAL);

    // Calculate energy for each pixel
    for (band = 0; band < bands; band++)
    {
        inptr = (int**)getData_Image(filtered, band);
        outptr = (int**)getData_Image(energy_map, band);
        for (r = NEIGHBORHOOD_BOUND; r < rows - NEIGHBORHOOD_BOUND; r++)
        {
            for (c = NEIGHBORHOOD_BOUND; c < cols - NEIGHBORHOOD_BOUND; c++)
            {
                outptr[r][c] = neighborhood_sum(inptr, r, c);
            }
        }
    }
    return energy_map;
}


/******************************************************************************
 *
 * laws_filtered_image(Image* image, int vector1, int vector2)
 *
 * Description: Convolves laws filter mask, determined by vectors vector1 and
 *              vector2, with input image and returns result.
 *       image: Image to be convolved with laws mask.
 *     vector1: Laws vectors used to create laws filter mask used for
 *     vector2: convolution.
 *
 *****************************************************************************/
int laws_convolve(byte** inptr, const int maskptr[][LAWS_SIZE], int r, int c)
{
    int i, j, val = 0;
    for (i = -LAWS_BOUND; i <= LAWS_BOUND; i++)
    {
        for (j = -LAWS_BOUND; j <= LAWS_BOUND; j++)
        {
            val += (inptr[r + i][c + j] * maskptr[i + LAWS_BOUND][j + LAWS_BOUND]);
        }
    }
    return val;
}
Image* laws_filtered_image(Image* image, int vector1, int vector2)
{
    const int (*mask)[LAWS_SIZE][LAWS_SIZE] = &laws_masks[vector1][vector2];

    byte** inptr;
    int** outptr;
    int band, bands = getNoOfBands_Image(image);
    int r, rows = getNoOfRows_Image(image);
    int c, cols = getNoOfCols_Image(image);
    Image* byte_img = image;
    Image* filtered = new_Image(PPM, RGB, bands, rows, cols, CVIP_INTEGER, REAL);

    // Convert input image to byte datatype, if needed
    if (getDataType_Image(image) != CVIP_BYTE)
    {
        byte_img = remap_Image(image, CVIP_BYTE, 0, 255);
    }

    // Convolve input image with laws filter mask
    for (band = 0; band < bands; band++)
    {
        inptr = (byte**)getData_Image(byte_img, band);
        outptr = (int**)getData_Image(filtered, band);
        for (r = LAWS_BOUND; r < rows - LAWS_BOUND; r++)
        {
            for (c = LAWS_BOUND; c < cols - LAWS_BOUND; c++)
            {
                outptr[r][c] = laws_convolve(inptr, *mask, r, c);
            }
        }
    }

    // Dispose of byte image, if it was created in this function.
    if (getDataType_Image(image) != CVIP_BYTE)
    {
        delete_Image(byte_img);
    }
    return filtered;
}


/******************************************************************************
 *
 * object_mask(labeled, row, col, window_size)
 *
 * Description: Creates mask image that isolates object located at row, col
 *              coordinates. Parameter 'window_size' is used to remove pixels
 *              from mask that are not to be used - pixel locations for
 *              which the mask doesn't fit entirely inside of the object
 *              are not to be used.
 *     labeled: Labeled image used to identify object to be masked.
 *    row, col: Identifies location of object in labeled image.
 * window_size: Neighborhood size used in calculations.
 *
 *****************************************************************************/
int mask_value(int** inptr, int r, int c, int greylevel, int bound)
{
    int i, j;
    int val = 1;
    for (i = -bound; i <= bound; i++)
    {
        if (val != 1) break;
        for (j = -bound; j <= bound; j++)
        {
            if (inptr[r + i][c + j] != greylevel)
            {
                val = 0;
                break;
            }
        }
    }
    return val;
}
Image* object_mask(Image* labeled, int row, int col, int window_size, int* nRow, int* nCol)
{
	int** maskptr;
	int** lblptr;
	int bound = window_size / 2;
	int greylevel = getPixel_Image(labeled, int, col, row, 0);
	int r, rows = getNoOfRows_Image(labeled);
	int c, cols = getNoOfCols_Image(labeled);
	Image* mask = new_Image(PGM, GRAY_SCALE, 1, rows, cols, CVIP_INTEGER, REAL);
	lblptr = (int**)getData_Image(labeled, 0);
	maskptr = (int**)getData_Image(mask, 0);

	int found = 0;
	for (r = bound; r < (rows - bound); r++)
	{
		for (c = bound; c < (cols - bound); c++)
		{
			maskptr[r][c] = mask_value(lblptr, r, c, greylevel, bound);
			if (found == 0)
			{
				if (maskptr[r][c] == 1)
				{
					found = 1;
					*nRow = r;
					*nCol = c;
				}
			}
		}
	}
	return mask;
}
