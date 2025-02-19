
/***************************************************************************
======================================================================
Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
======================================================================
                                                                      
             File Name: cviptotiff.c
           Description: contains a routine to write the contents of a
			CVIPtools Image structure out to a tiff file.
         Related Files: CVIPimage.h, CVIPtiff.h, Imakefile
   Initial Coding Date: 1/24/93
           Portability: Standard (ANSI) C
             Credit(s): Gregory Hance, E.E. Dept. SIUE

  Global Function List: cviptotiff
			
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

$Log: cviptotiff.c,v $
Revision 1.6  1997/05/26 20:00:52  yawei
modified for new tiff version

Revision 1.5  1997/03/08 00:43:30  yawei
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

Revision 1.4  1997/01/15 17:08:04  yawei
Global Change:  IMAGE ==> Image

 * Revision 1.3  1995/02/21  03:04:09  luok
 * check file into RCS
 *
 * Revision 1.2  1995/02/21  02:40:51  luok
 * check file into RCS
 *
 * Revision 1.1  1993/05/31  07:10:13  hanceg
 * Initial revision
 *                                                         

*****************************************************************************/
/*
** Derived by Jef Poskanzer from ras2tif.c, which is:
**
** Copyright (c) 1990 by Sun Microsystems, Inc.
**
** Author: Patrick J. Naughton
** naughton@wind.sun.com
**
** Permission to use, copy, modify, and distribute this software and its
** documentation for any purpose and without fee is hereby granted,
** provided that the above copyright notice appear in all copies and that
** both that copyright notice and this permission notice appear in
** supporting documentation.
**
** This file is provided AS IS with no warranties of any kind.  The author
** shall have no liability with respect to the infringement of copyrights,
** trade secrets or any patents by this file or any part thereof.  In no
** event will the author be liable for any lost revenue or profits or
** other special, indirect and consequential damages.
*/

#include "pnm.h"
#include "tiff.h"
#include "tiffio.h"
#define NO_STD_INCLUDES
#include "CVIPimage.h"
#include "CVIPxel.h"

#include "ppmcmap.h"
#define MAXCOLORS 256

void cviptotiff( cvip_Image, tiff_name, compression,  fillorder, g3options, predictor, rowsperstrip, verbose)
    Image *cvip_Image;
    unsigned short compression;
    unsigned short fillorder;
    long g3options;
    unsigned short predictor;
    long rowsperstrip;
    char *tiff_name;
    int verbose;
    {
    char *prog_name[1] = {"cviptotiff"};
    byte *grayptr;
    int argn;
    char* inf = prog_name[0];
    xel** xels;
    register xel* xP;
    colorhist_vector chv;
    colorhash_table cht;
    unsigned short red[MAXCOLORS], grn[MAXCOLORS], blu[MAXCOLORS];
    int cols, rows, format, row, colors, i;
    register int col;
    xelval maxval = 255;
    int grayscale;
    TIFF* tif;
    short photometric;
    short samplesperpixel;
    short bitspersample;
    int bytesperrow;
    unsigned char* buf;
    unsigned char* tP;

    pnm_init( &verbose, prog_name );

    rows = cvip_Image->image_ptr[0]->rows;
    cols = cvip_Image->image_ptr[0]->cols;
    
    xels = pnm_allocarray(cols, rows);
    
    switch(cvip_Image->color_space) {
       case RGB:
          format = PPM_FORMAT;
	  CVIP_TO_PNM((pixel **) xels, cvip_Image->image_ptr[0]->rptr,cvip_Image->image_ptr[1]->rptr,cvip_Image->image_ptr[2]->rptr,rows,cols,byte);
	  break;
       case GRAY_SCALE:
          format = PGM_FORMAT;
	  CVIP_TO_PNM((pixel **) xels, NULL, NULL, cvip_Image->image_ptr[0]->rptr, rows, cols, byte);
	  grayptr = (byte *) *( (byte **) cvip_Image->image_ptr[0]->rptr);
	  maxval = 0;
	  for(i=0; i < (rows*cols); i++)
	     maxval = max(grayptr[i],maxval);
	  break;
       case BINARY:
          format = PBM_FORMAT;
	  CVIP_TO_PNM((pixel **) xels, NULL, NULL, cvip_Image->image_ptr[0]->rptr,rows,cols,byte);
	  break;
       default:
          pm_message("FREAKED OUT color space");
	  break;
    }

    /* Check for grayscale. */
    switch ( PNM_FORMAT_TYPE(format) )
	{
	case PPM_TYPE:
	pm_message( "computing colormap..." );
	chv = ppm_computecolorhist( xels, cols, rows, MAXCOLORS, &colors );
	if ( chv == (colorhist_vector) 0 )
	    {
	    pm_message(
		"Too many colors - proceeding to write a 24-bit %dx%d RGB TIFF file - %s.", rows, cols, tiff_name);
	    pm_message(
		"If you want an 8-bit palette file try quantizing the image to 256 colors first.\n");
	    grayscale = 0;
	    }
	else
	    {
	    pm_message( "%d colors found", colors );
	    grayscale = 1;
	    for ( i = 0; i < colors; ++i )
		{
		register xelval r, g, b;

		r = PPM_GETR( chv[i].color );
		g = PPM_GETG( chv[i].color );
		b = PPM_GETB( chv[i].color );
		if ( r != g || g != b )
		    {
		    grayscale = 0;
		    break;
		    }
		}
	    }
	break;

	default:
	chv = (colorhist_vector) 0;
	grayscale = 1;
	break;
	}

    /* Open output file. */
    if( !strcmp(tiff_name,"Standard Output") )
       tif = TIFFFdOpen( 1, "Standard Output", "w" );
    else
       tif = TIFFOpen(tiff_name, "w" );
    if ( tif == NULL )
	pm_error( "error opening TIFF file" );

    /* Figure out TIFF parameters. */
    switch ( PNM_FORMAT_TYPE(format) )
	{
	case PPM_TYPE:
	if ( chv == (colorhist_vector) 0 )
	    {
	    samplesperpixel = 3;
	    bitspersample = 8;
	    photometric = PHOTOMETRIC_RGB;
	    bytesperrow = cols * 3;
	    }
	else if ( grayscale )
	    {
	    pm_message("writing %dx%d gray scale TIFF file - %s.", rows, cols, tiff_name);
	    samplesperpixel = 1;
	    bitspersample = pm_maxvaltobits( maxval );
	    pm_message("%d bits per sample.", bitspersample);
	    pm_message("1 sample per pixel.\n");
	    photometric = PHOTOMETRIC_MINISBLACK;
	    bytesperrow = ( cols + i - 1 ) / i;
	    }
	else
	    {
	    pm_message("writing %dx%dx8 colormap TIFF file - %s.", rows, cols, tiff_name);
	    pm_message("8 bits per sample.");
	    pm_message("1 sample per pixel.\n");
	    samplesperpixel = 1;
	    bitspersample = 8;
	    photometric = PHOTOMETRIC_PALETTE;
	    bytesperrow = cols;
	    }
	break;

	case PGM_TYPE:
	pm_message("writing %dx%d gray scale TIFF file - %s.", rows, cols, tiff_name);
	samplesperpixel = 1;
	bitspersample = pm_maxvaltobits( maxval );
	pm_message("%d bits per sample.", bitspersample);
	pm_message("1 sample per pixel.\n");
	photometric = PHOTOMETRIC_MINISBLACK;
	i = 8 / bitspersample;
	bytesperrow = ( cols + i - 1 ) / i;
	break;

	default:
	pm_message("writing %dx%d binary TIFF file - %s.", rows, cols, tiff_name);
	pm_message("1 bit per sample.");
	pm_message("\" sample per pixel.\n");
	samplesperpixel = 1;
	bitspersample = 1;
	photometric = PHOTOMETRIC_MINISBLACK;
	bytesperrow = ( cols + 7 ) / 8;
	break;
	}

    if ( rowsperstrip == 0 )
	rowsperstrip = ( 8 * 1024 ) / bytesperrow;
    buf = (unsigned char*) malloc( bytesperrow );
    if ( buf == (unsigned char*) 0 )
	pm_error( "can't allocate memory for row buffer" );

    /* Set TIFF parameters. */
    TIFFSetField( tif, TIFFTAG_IMAGEWIDTH, cols );
    TIFFSetField( tif, TIFFTAG_IMAGELENGTH, rows );
    TIFFSetField( tif, TIFFTAG_BITSPERSAMPLE, bitspersample );
    TIFFSetField( tif, TIFFTAG_ORIENTATION, ORIENTATION_TOPLEFT );
    TIFFSetField( tif, TIFFTAG_COMPRESSION, compression );
    if ( compression == COMPRESSION_CCITTFAX3 && g3options != 0 )
	TIFFSetField( tif, TIFFTAG_GROUP3OPTIONS, g3options );
    if ( compression == COMPRESSION_LZW && predictor != 0 )
	TIFFSetField( tif, TIFFTAG_PREDICTOR, predictor );
    TIFFSetField( tif, TIFFTAG_PHOTOMETRIC, photometric );
    TIFFSetField( tif, TIFFTAG_FILLORDER, fillorder );
    TIFFSetField( tif, TIFFTAG_DOCUMENTNAME, inf );
    TIFFSetField( tif, TIFFTAG_IMAGEDESCRIPTION, "converted CVIP file" );
    TIFFSetField( tif, TIFFTAG_SAMPLESPERPIXEL, samplesperpixel );
    TIFFSetField( tif, TIFFTAG_ROWSPERSTRIP, rowsperstrip );
    /* TIFFSetField( tif, TIFFTAG_STRIPCVIP_BYTECOUNTS, rows / rowsperstrip ); */
    TIFFSetField( tif, TIFFTAG_PLANARCONFIG, PLANARCONFIG_CONTIG );

    if ( chv == (colorhist_vector) 0 )
	cht = (colorhash_table) 0;
    else
	{
	/* Make TIFF colormap. */
	for ( i = 0; i < colors; ++i )
	    {
	    red[i] = (long) PPM_GETR( chv[i].color ) * 65535L / maxval;
	    grn[i] = (long) PPM_GETG( chv[i].color ) * 65535L / maxval;
	    blu[i] = (long) PPM_GETB( chv[i].color ) * 65535L / maxval;
	    }
	TIFFSetField( tif, TIFFTAG_COLORMAP, red, grn, blu );

	/* Convert color vector to color hash table, for fast lookup. */
	cht = ppm_colorhisttocolorhash( chv, colors );
	ppm_freecolorhist( chv );
	}

    /* Now write the TIFF data. */
    for ( row = 0; row < rows; ++row )
	{
	if ( PNM_FORMAT_TYPE(format) == PPM_TYPE && ! grayscale )
	    {
	    if ( cht == (colorhash_table) 0 )
		{
		for ( col = 0, xP = xels[row], tP = buf;
		      col < cols; ++col, ++xP )
		    {
		    register unsigned char s;

		    s = PPM_GETR( *xP );
		    if ( maxval != 255 )
			s = (long) s * 255 / maxval;
		    *tP++ = s;
		    s = PPM_GETG( *xP );
		    if ( maxval != 255 )
			s = (long) s * 255 / maxval;
		    *tP++ = s;
		    s = PPM_GETB( *xP );
		    if ( maxval != 255 )
			s = (long) s * 255 / maxval;
		    *tP++ = s;
		    }
		}
	    else
		{
		for ( col = 0, xP = xels[row], tP = buf;
		      col < cols; ++col, ++xP )
		    {
		    register int s;

		    s = ppm_lookupcolor( cht, xP );
		    if ( s == -1 )
			pm_error(
			    "color not found?!?  row=%d col=%d  r=%d g=%d b=%d",
			    row, col, PPM_GETR( *xP ), PPM_GETG( *xP ),
			    PPM_GETB( *xP ) );
		    *tP++ = (unsigned char) s;
		    }
		}
	    }
	else
	    {
	    register xelval bigger_maxval;
	    register int bitshift;
	    register unsigned char byte;
	    register xelval s;

	    bigger_maxval = pm_bitstomaxval( bitspersample );
	    bitshift = 8 - bitspersample;
	    byte = 0;
	    for ( col = 0, xP = xels[row], tP = buf; col < cols; ++col, ++xP )
		{
		s = PNM_GET1( *xP );
		if ( maxval != bigger_maxval )
		    s = (long) s * bigger_maxval / maxval;
		byte |= s << bitshift;
		bitshift -= bitspersample;
		if ( bitshift < 0 )
		    {
		    *tP++ = byte;
		    bitshift = 8 - bitspersample;
		    byte = 0;
		    }
		}
	    if ( bitshift != 8 - bitspersample )
		*tP++ = byte;
	    }

	if ( TIFFWriteScanline( tif, buf, row, 0 ) < 0 )
	    pm_error( "failed a scanline write on row %d", row );
	}
    TIFFFlushData( tif );
    TIFFClose( tif );
    if(cht!=NULL)
	ppm_freecolorhash(cht);

    }
