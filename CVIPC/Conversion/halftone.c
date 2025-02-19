/***************************************************************************
* ======================================================================
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* ======================================================================
*
*             File Name: halftone.c
*           Description: converts a grayscale image to a binary image
*         Related Files: CVIPhalftone.h, dithers.h, Imakefile
*   Initial Coding Date: Sun May 30 23:13:37 CDT 1993
*           Portability: Standard (ANSI) C
*             Credit(s): Gregory Hance
*                        Southern Illinois University @ Edwardsville
*
** Copyright (C) 1993 SIUE - by Gregory Hance.
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
** $Log: halftone.c,v $
** Revision 1.6  1998/10/22 20:05:44  lguo
** in the former version, the static model array for dither, cluster3,4,8 are changed during processing. Now the codes are changed to avoid changing those staic arrays so that dither and cluster3,4,8 can work repaetly.
**
** Revision 1.5  1997/03/08 17:00:19  yawei
** Swaped CVIP_YES and CVIP_NO
**
** Revision 1.4  1997/03/08 00:43:03  yawei
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
** Revision 1.3  1997/01/15 17:07:18  yawei
** Global Change:  IMAGE ==> Image
**
 * Revision 1.2  1997/01/15  16:05:54  yawei
 * updated changes
 *
 * Revision 1.1  1993/05/31  07:10:15  hanceg
 * Initial revision
 *
*
****************************************************************************/
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "CVIPimage.h"
#include "dithers.h"
#include "CVIPhalftone.h"

#define CVIP_WHITE 1
#define CVIP_BLACK 0

#define FS_SCALE 1024
#define HALF_FS_SCALE 512


/****************************************************************
                   Name: CVIPhalftone
          Expanded Name: CVIP half tone
             Parameters: <cvip_Image> - pointer to input image
			 <halftone> - indicates method used to convert from
			 grayscale to binary. (one of QT_FS, QT_THRESH,
			 QT_DITHER8, QT_CLUSTER3, QT_CLUSTER4, QT_CLUSTER8)
			 <maxval> - should normally be set to 255 (specifies
			 maximum range of input image)
			 <fthreshval> - threshold value between [0.0 ... 1.0].
			 Only needed if QT_THRESH is selected.
			 <retain_image> - CVIP_YES or CVIP_NO value indicating whether
			 the original Image structure should be freed or not.
			 <verbose> - CVIP_YES or CVIP_NO value indicating whether
			 the function should output standard messages.
                Returns: pointer to a binary image
            Description: quatizes a grayscale image to two levels (a binary 
			 image). Possible methods of quantization are: (1) 
			 QT_FS -- Floyd - Steinberg  error  diffusion, (2)
			 QT_THRESH -- simple thresholding, (3) QT_DITHER8 --
			 Bayer's ordered dither and (4) QT_CLUSTER3,
			 QT_CLUSTER4 and QT_CLUSTER8 -- three different sizes
			 of 45-degree  clustered-dot dither.
     			 Floyd-Steinberg will almost always  give  the  best
			 looking results.
	    Diagnostics: none
              Credit(s): Jef Poskanzer -- "PBMPLUS"
			 Gregory Hance
		         Southern Illinois University @ Edwardsville
****************************************************************/

Image *CVIPhalftone(Image *cvip_Image, int halftone, int maxval, float fthreshval, CVIP_BOOLEAN retain_image, CVIP_BOOLEAN verbose)
{
    byte* grayrow;
    register byte* gP;
    byte* bitrow;
    register byte* bP;
    int rows, cols, row;
    int col, limitcol, format;
    char function_name[] = {"CVIPhalftone"};
    long threshval, sum;
    long* thiserr;
    long* nexterr;
    long* temperr;
    int fs_direction;
    Image *bit_Image;
    
    cols = cvip_Image->image_ptr[0]->cols;
    rows = cvip_Image->image_ptr[0]->rows;
    
    bit_Image = (Image *) image_allocate(cvip_Image->image_format, BINARY, 1, rows, cols, CVIP_BYTE, REAL);
    
    format = cvip_Image->image_format;
    if( !(format==PBM || format==PGM || format==TIF || format==RAS || format==BIN || format==ITX) ) {
       if(verbose)
          fprintf(stderr, "\n%s: casting image to format that supports binary images - (PBM).\n",function_name);
       bit_Image->image_format = PBM;
    }

    /* Initialize. */
    switch ( halftone )
	{
	case QT_FS:
	if(verbose)
	   fprintf(stderr, "%s: performing boustrophedonic Floyd-Steinberg error diffusion.\n\n",function_name);
	/* Initialize Floyd-Steinberg error vectors. */
	thiserr = (long*) calloc( cols + 2, sizeof(long) );
	nexterr = (long*) calloc( cols + 2, sizeof(long) );
	srand( (int) ( time( 0 ) ^ getpid( ) ) );
	for ( col = 0; col < cols + 2; ++col )
	    thiserr[col] = ( rand( ) % FS_SCALE - HALF_FS_SCALE ) / 4;
	    /* (random errors in [-FS_SCALE/8 .. FS_SCALE/8]) */
	fs_direction = 1;
	threshval = fthreshval * FS_SCALE;
	break;

	case QT_THRESH:
	threshval = fthreshval * maxval + 0.999999;
	if(verbose) {
	   fprintf(stderr, "%s: performing simple thresholding operation.\n",function_name);
	   fprintf(stderr, "%s: threshold level - %ld.\n\n",function_name, threshval);
	}
	break;
	
	case QT_DITHER8:
	break;
	
	case QT_CLUSTER3:
	break;
	
	case QT_CLUSTER4:
	break;
	
	case QT_CLUSTER8:
	break;
	
	default:
	fprintf(stderr, "%s: can't happen... but apparently something did?!?\n" , function_name); break;
	}

    for ( row = 0; row < rows; ++row )
	{
	grayrow = (byte *) ((byte **) cvip_Image->image_ptr[0]->rptr)[row];
	bitrow  = (byte *) ((byte **) bit_Image->image_ptr[0]->rptr)[row];

	switch ( halftone )
	    {
	    case QT_FS:
	    for ( col = 0; col < cols + 2; ++col )
		nexterr[col] = 0;
	    if ( fs_direction )
		{
		col = 0;
		limitcol = cols;
		gP = grayrow;
		bP = bitrow;
		}
	    else
		{
		col = cols - 1;
		limitcol = -1;
		gP = &(grayrow[col]);
		bP = &(bitrow[col]);
		}
	    do
		{
		sum = ( (long) *gP * FS_SCALE ) / maxval + thiserr[col + 1];
		if ( sum >= threshval )
		    {
		    *bP = CVIP_WHITE;
		    sum = sum - threshval - HALF_FS_SCALE;
		    }
		else
		    *bP = CVIP_BLACK;

		if ( fs_direction )
		    {
		    thiserr[col + 2] += ( sum * 7 ) / 16;
		    nexterr[col    ] += ( sum * 3 ) / 16;
		    nexterr[col + 1] += ( sum * 5 ) / 16;
		    nexterr[col + 2] += ( sum     ) / 16;

		    ++col;
		    ++gP;
		    ++bP;
		    }
		else
		    {
		    thiserr[col    ] += ( sum * 7 ) / 16;
		    nexterr[col + 2] += ( sum * 3 ) / 16;
		    nexterr[col + 1] += ( sum * 5 ) / 16;
		    nexterr[col    ] += ( sum     ) / 16;

		    --col;
		    --gP;
		    --bP;
		    }
		}
	    while ( col != limitcol );
	    temperr = thiserr;
	    thiserr = nexterr;
	    nexterr = temperr;
	    fs_direction = ! fs_direction;
	    break;

	    case QT_THRESH:
	    for ( col = 0, gP = grayrow, bP = bitrow; col < cols; ++col, ++gP, ++bP )
		if ( *gP >= threshval )
		    *bP = CVIP_WHITE;
		else
		    *bP = CVIP_BLACK;
	    break;

	    case QT_DITHER8:
	    for ( col = 0, gP = grayrow, bP = bitrow; col < cols; ++col, ++gP, ++bP )
		if ( *gP >= dither8[row % 16][col % 16] * ( maxval + 1 ) / 256 )
		    *bP = CVIP_WHITE;
		else
		    *bP = CVIP_BLACK;
	    break;

	    case QT_CLUSTER3:
	    for ( col = 0, gP = grayrow, bP = bitrow; col < cols; ++col, ++gP, ++bP )
		if ( *gP >= cluster3[row %6][col %6 ] * ( maxval + 1 ) / 18 )
		    *bP = CVIP_WHITE;
		else
		    *bP = CVIP_BLACK;
	    break;

	    case QT_CLUSTER4:
	    for ( col = 0, gP = grayrow, bP = bitrow; col < cols; ++col, ++gP, ++bP )
		if ( *gP >= cluster4[row %8][col%8] * ( maxval + 1 ) / 32 )
		    *bP = CVIP_WHITE;
		else
		    *bP = CVIP_BLACK;
	    break;

	    case QT_CLUSTER8:
	    for ( col = 0, gP = grayrow, bP = bitrow; col < cols; ++col, ++gP, ++bP )
		if ( *gP >= cluster8[row %16][col %16] * ( maxval + 1 ) / 128 )
		    *bP = CVIP_WHITE;
		else
		    *bP = CVIP_BLACK;
	    break;

	    default:
	    fprintf(stderr, "%s: can't happen... but apparently something did?!?\n" , function_name); break;
	    }
	}

if(!retain_image)
   image_free(cvip_Image);
return bit_Image;
}
