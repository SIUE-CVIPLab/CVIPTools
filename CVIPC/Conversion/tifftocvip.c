/***************************************************************************
======================================================================
Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
======================================================================
                                                                      
             File Name: tifftocvip.c
           Description: contains a routine to load a TIFF file into
			a CVIP Image structure.
         Related Files: CVIPimage.h, CVIPtiff.h, Imakefile
   Initial Coding Date: 1/24/93
           Portability: Standard (ANSI) C
             Credit(s): Gregory Hance, E.E. Dept. SIUE

  Global Function List: tifftocvip
			
****************************************************************************

** Copyright (C) 1991, 1992, 1993 SIUE - by Scott Umbaugh, Greg Hance.
**
** Permission to use, copy, modify, and distribute this software and its
** documentation for any purpose and without fee is hereby granted, provided
** that the above copyright notice appear in all copies and that both that
** copyright notice and this permission notice appear in supporting
** documentation.  This software is provided "as is" without express or
** implied warranty.

RCS (Revision Control System) Information - Added automatically by RCS) 

$Log: tifftocvip.c,v $
Revision 1.6  1997/05/26 20:01:04  yawei
 modified for new tiff version

Revision 1.5  1997/05/15 19:44:04  kcai
No change

Revision 1.4  1997/03/08 00:43:49  yawei
Name Changes:
	BOOLEAN ==> CVIP_BOOLEAN
	FALSE ==> CVIP_YES
	TRUE ==> CVIP_NO
	BYTE ==> CVIP_BYTE
	SHORT ==> CVIP_SHORT
	INTEGER ==> CVIP_INTEGER
	FLOAT ==> CVIP_FLOAT
	DOUBLE ==> CVIP_DOUBLE
	TYPE ==> CVIP_TYPE

Revision 1.3  1997/01/15 17:08:33  yawei
Global Change:  IMAGE ==> Image

 * Revision 1.2  1997/01/15  16:03:48  yawei
 * updated changes
 *
 * Revision 1.1  1993/05/31  07:10:16  hanceg
 * Initial revision
 *                                                         

*****************************************************************************/

#include "pnm.h"
#include "tiff.h"
#include "tiffio.h"
#include "tiffcomp.h"
#define NO_STD_INCLUDES
#include "CVIPimage.h"

#define MAXCOLORS 1024

Image *tifftocvip(tiff_file, verbose)
    char *tiff_file;
    int verbose;
    {
    char* prog_name[1] = {"tifftocvip"};
    int argn, cols, rows, grayscale;
    int numcolors, headerdump;
    register TIFF* tif;
    int row, i;
    register int col;
    u_char* buf;
    register u_char* inP;
    int maxval;
    register xel* xP;
    xel colormap[MAXCOLORS];
    register u_char sample;
    register int bitsleft;
    unsigned short bps, spp, photomet;
    unsigned short* redcolormap;
    unsigned short* greencolormap;
    unsigned short* bluecolormap;
    Image *tiff_Image;
    byte *gray_ptr, *r_ptr, *g_ptr, *b_ptr;

    headerdump = verbose;
    pnm_init( &verbose, prog_name );

    if( !strcmp(tiff_file, "Standard Input") ) {
	tif = TIFFFdOpen( 0, tiff_file, "r" );
	if ( tif == NULL )
	    pm_error( "error opening standard input as TIFF file" );
    }
    else {
       tif = TIFFOpen( tiff_file, "r" );
       if ( tif == NULL )
          pm_error( "error opening TIFF file %s", prog_name );
    }

    if ( headerdump )
	TIFFPrintDirectory( tif, stderr, TIFFPRINT_NONE );

    if ( ! TIFFGetField( tif, TIFFTAG_BITSPERSAMPLE, &bps ) )
	bps = 1;
    if ( ! TIFFGetField( tif, TIFFTAG_SAMPLESPERPIXEL, &spp ) )
	spp = 1;
    if ( ! TIFFGetField( tif, TIFFTAG_PHOTOMETRIC, &photomet ) )
	pm_error( "error getting photometric" );

    switch ( spp )
	{
	case 1:
	case 3:
	case 4:
	break;

	default:
	pm_error(
	    "can only handle 1-channel gray scale or 1- or 3-channel color" );
	}

    (void) TIFFGetField( tif, TIFFTAG_IMAGEWIDTH, &cols );
    (void) TIFFGetField( tif, TIFFTAG_IMAGELENGTH, &rows );

    if ( headerdump )
	{
	pm_message( "%dx%dx%d image", cols, rows, bps * spp );
	pm_message( "%d bits/sample, %d samples/pixel", bps, spp );
	}

    maxval = ( 1 << bps ) - 1;
    if ( maxval == 1 && spp == 1 )
	{
	if ( headerdump )
	    pm_message("monochrome" );
	grayscale = 1;
	}
    else
	{
	switch ( photomet )
	    {
	    case PHOTOMETRIC_MINISBLACK:
	    if ( headerdump )
		pm_message( "%d graylevels (min=black)", maxval + 1 );
	    grayscale = 1;
	    break;

	    case PHOTOMETRIC_MINISWHITE:
	    if ( headerdump )
		pm_message( "%d graylevels (min=white)", maxval + 1 );
	    grayscale = 1;
	    break;

	    case PHOTOMETRIC_PALETTE:
	    if ( headerdump )
		pm_message( "colormapped" );
	    if ( ! TIFFGetField( tif, TIFFTAG_COLORMAP, &redcolormap, &greencolormap, &bluecolormap ) )
		pm_error( "error getting colormaps" );
	    numcolors = maxval + 1;
	    if ( numcolors > MAXCOLORS )
		pm_error( "too many colors" );
	    maxval = PNM_MAXMAXVAL;
	    grayscale = 0;
	    for ( i = 0; i < numcolors; ++i )
		{
		register xelval r, g, b;
		r = (long) redcolormap[i] * PNM_MAXMAXVAL / 65535L;
		g = (long) greencolormap[i] * PNM_MAXMAXVAL / 65535L;
		b = (long) bluecolormap[i] * PNM_MAXMAXVAL / 65535L;
		PPM_ASSIGN( colormap[i], r, g, b );
		}
	    break;

	    case PHOTOMETRIC_RGB:
	    if ( headerdump )
		pm_message( "truecolor" );
	    grayscale = 0;
	    break;

	    case PHOTOMETRIC_MASK:
	    pm_error( "don't know how to handle PHOTOMETRIC_MASK" );

	    default:
	    pm_error( "unknown photometric: %d", photomet );
	    }
	}
    if ( maxval > PNM_MAXMAXVAL )
	pm_error(
"bits/sample is too large - try reconfiguring with PGM_BIGGRAYS\n    or without PPM_PACKCOLORS" );


    if ( grayscale )
	{
	if ( maxval == 1 )
	    {
	    pm_message( "loading BINARY TIFF image data from %s.\n", tiff_file );
	    if ((tiff_Image = image_allocate(TIF, BINARY, 1, rows, cols, CVIP_BYTE, REAL)) == NULL)
	       pm_error("couldn't alloc Image structure" );
	    }
	else
	    {
	    pm_message( "loading GRAYSCALE TIFF image data from %s.\n" ,tiff_file);
	    if ((tiff_Image = image_allocate(TIF, GRAY_SCALE, 1, rows, cols, CVIP_BYTE, REAL)) == NULL)
	       pm_error("couldn't alloc Image structure" );
	    }
	}
    else
	{
	pm_message( "loading RGB TIFF image data from %s.\n", tiff_file );
	if ((tiff_Image = image_allocate(TIF, RGB, 3, rows, cols, CVIP_BYTE, REAL)) == NULL)
	   pm_error("couldn't alloc Image structure" );
	}

    buf = (u_char*) malloc(TIFFScanlineSize(tif));
    if ( buf == NULL )
	pm_error( "can't allocate memory for scanline buffer" );

#define NEXTSAMPLE \
    { \
    if ( bitsleft == 0 ) \
	{ \
	++inP; \
	bitsleft = 8; \
	} \
    bitsleft -= bps; \
    sample = ( *inP >> bitsleft ) & maxval; \
    }

    for ( row = 0; row < rows; ++row )
	{
	if ( TIFFReadScanline( tif, buf, row, 0 ) < 0 )
	    pm_error( "bad data read on line %d", row );
	inP = buf;
	bitsleft = 8;

	switch ( photomet )
	    {
	    case PHOTOMETRIC_MINISBLACK:
	    gray_ptr   = (byte *) tiff_Image->image_ptr[0]->rptr[row];
	    for ( col = 0; col < cols; ++col, ++gray_ptr )
		{
		NEXTSAMPLE
		*gray_ptr = sample;
		}
	    break;

	    case PHOTOMETRIC_MINISWHITE:
	    gray_ptr   = (byte *) tiff_Image->image_ptr[0]->rptr[row];
	    for ( col = 0; col < cols; ++col, ++gray_ptr )
		{
		NEXTSAMPLE
		*gray_ptr = maxval - sample;
		}
	    break;

	    case PHOTOMETRIC_PALETTE:
	    r_ptr = (byte *) tiff_Image->image_ptr[0]->rptr[row];
	    g_ptr = (byte *) tiff_Image->image_ptr[1]->rptr[row];
	    b_ptr = (byte *) tiff_Image->image_ptr[2]->rptr[row];

	    for ( col = 0; col < cols; ++col, ++r_ptr, ++g_ptr, ++b_ptr )
		{
		NEXTSAMPLE
		*r_ptr = colormap[sample].r;
		*g_ptr = colormap[sample].g;
		*b_ptr = colormap[sample].b;
		}
	    break;

	    case PHOTOMETRIC_RGB:
	    r_ptr  = (byte *) tiff_Image->image_ptr[0]->rptr[row];
	    g_ptr  = (byte *) tiff_Image->image_ptr[1]->rptr[row];
	    b_ptr  = (byte *) tiff_Image->image_ptr[2]->rptr[row];

	    for ( col = 0; col < cols; ++col, ++r_ptr, ++g_ptr, ++b_ptr )
		{
		register xelval r, g, b;

		NEXTSAMPLE
		*r_ptr = sample;
		NEXTSAMPLE
		*g_ptr = sample;
		NEXTSAMPLE
		*b_ptr = sample;
		if ( spp == 4 )
		    NEXTSAMPLE		/* skip alpha channel */
		}
	    break;

	    default:
	    pm_error( "unknown photometric: %d", photomet );
	    }
	}

    return tiff_Image;
    }
