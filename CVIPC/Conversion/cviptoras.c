/***************************************************************************
======================================================================
Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
======================================================================
                                                                      
             File Name: cviptoras.c
           Description: contains a routine to write the contents of a
			CVIPtools Image structure to a SunRaster file..
         Related Files: CVIPimage.h, CVIPras.h, Imakefile
   Initial Coding Date: 1/24/93
           Portability: Standard (ANSI) C
             Credit(s): Gregory Hance, E.E. Dept. SIUE

  Global Function List: cviptoras
			
****************************************************************************

** Copyright (C) 1991, 1992, 1993 SIUE - by Scott Umbaugh, Greg Hance.
** Copyright (C) 1989, 1991 by Jef Poskanzer.
**
** Permission to use, copy, modify, and distribute this software and its
** documentation for any purpose and without fee is hereby granted, provided
** that the above copyright notice appear in all copies and that both that
** copyright notice and this permission notice appear in supporting
** documentation.  This software is provided "as is" without express or
** implied warranty.

RCS (Revision Control System) Information - Added automatically by RCS) 

$Log: cviptoras.c,v $
Revision 1.5  1997/01/15 17:07:48  yawei
Global Change:  IMAGE ==> Image

 * Revision 1.4  1995/02/06  20:20:13  luok
 * fix a memory leak
 *
 * Revision 1.3  1995/02/06  20:03:02  luok
 * check file in
 *
 * Revision 1.2  1994/12/21  08:06:32  luok
 * check the file into RCS
 *
 * Revision 1.1  1993/05/31  07:10:13  hanceg
 * Initial revision
 *                                                         

*****************************************************************************/

#include "pnm.h"
#include "rast.h"
#define NO_STD_INCLUDES
#include "CVIPimage.h"
#include "ppmcmap.h"
#include "CVIPxel.h"
#define MAXCOLORS 256
static colormap_t* make_pr_colormap ARGS(( colorhist_vector chv, int colors ));
static colormap_t* make_gray_pr_colormap ARGS(( void ));
static colormap_t* alloc_pr_colormap ARGS(( void ));

void
cviptoras( ras_Image, ras_name, outfp, pr_type, verbose)
    int pr_type;
    Image *ras_Image;
    int verbose;
    char *ras_name;
    FILE* outfp;
    {
    xel** xels;
    xel* xelrow;
    xel p;
    register xel* xP;
    colorhist_vector chv;
    colorhash_table cht;
    colormap_t* pr_colormapP;
    int argn, rows, cols, format, i;
    int depth, colors, linesize, row;
    register int col, bitcount; 
    xelval maxval = 255;
    struct pixrect* pr;
    unsigned char* data;
    register unsigned char* byteP;
    char *prog_name[1] = {"cviptoras"},*fn = "cviptoras";

    pnm_init( &verbose, prog_name );
    msg_CVIP(fn,"opening Sun Raster file %s for output.", ras_name);
    
    rows = ras_Image->image_ptr[0]->rows;
    cols = ras_Image->image_ptr[0]->cols;
    
    xels = pnm_allocarray(cols, rows);
    
    switch(ras_Image->color_space) {
       case RGB:
          format = PPM_FORMAT;
	  CVIP_TO_PNM((pixel **) xels,ras_Image->image_ptr[0]->rptr,ras_Image->image_ptr[1]->rptr,ras_Image->image_ptr[2]->rptr,rows,cols,byte);
	  break;
       case GRAY_SCALE:
          format = PGM_FORMAT;
	  CVIP_TO_PNM((pixel **) xels, NULL, NULL, ras_Image->image_ptr[0]->rptr, rows,cols,byte);
	  break;
       case BINARY:
          format = PBM_FORMAT;
	  CVIP_TO_PNM((pixel **) xels, NULL, NULL, ras_Image->image_ptr[0]->rptr, rows,cols,byte);
	  break;
       default:
          msg_CVIP(fn,"Freaked out color space");
	  break;
    }
          
    /* Figure out the proper depth and colormap. */
    switch (PNM_FORMAT_TYPE(format) )
	{
	case PPM_TYPE:
	msg_CVIP(fn, "computing colormap..." );
	chv = ppm_computecolorhist( xels, cols, rows, MAXCOLORS, &colors );
	if ( chv == (colorhist_vector) 0 )
	    {
	    msg_CVIP(fn,
		"Too many colors - proceeding to write a 24-bit non-mapped" );
	    msg_CVIP(fn,
		"rasterfile.  If you want 8 bits, try quantizing to %d colors.", MAXCOLORS );
	    msg_CVIP(fn, "%d colors found", colors );
	    msg_CVIP(fn,"writing %dx%d image data to Sun Raster file.", rows, cols); 
            msg_CVIP(fn,"8 bits per sample - RGB.");
	    msg_CVIP(fn,"3 samples per pixel.\n");
	    depth = 24;
	    pr_type = RT_STANDARD;
	    pr_colormapP = (colormap_t*) 0;
	    }
	else
	    {
	    msg_CVIP(fn, "%d colors found", colors );
	    msg_CVIP(fn,"writing %dx%d image data to Sun Raster file.", rows, cols); 
            msg_CVIP(fn,"8 bits per sample - RGB COLORMAPPED.");
	    msg_CVIP(fn,"1 sample per pixel (colormaps to 3).\n");

	    if ( maxval != 255 )
		for ( i = 0; i < colors; ++i )
		    PPM_DEPTH( chv[i].color, chv[i].color, maxval, 255 );

	    /* Force white to slot 0 and black to slot 1, if possible. */
	    PPM_ASSIGN( p, 255, 255, 255 );
	    ppm_addtocolorhist( chv, &colors, MAXCOLORS, &p, 0, 0 );
	    PPM_ASSIGN( p, 0, 0, 0 );
	    ppm_addtocolorhist( chv, &colors, MAXCOLORS, &p, 0, 1 );

	    if ( colors == 2 )
		{
		/* Monochrome. */
		depth = 1;
		pr_colormapP = (colormap_t*) 0;
		}
	    else
		{
		/* Turn the ppm colormap into the appropriate Sun colormap. */
		depth = 8;
		pr_colormapP = make_pr_colormap( chv, colors );
		}
	    cht = ppm_colorhisttocolorhash( chv, colors );
	    ppm_freecolorhist( chv );
	    }

	break;

	case PGM_TYPE:
	depth = 8;
	pr_colormapP = make_gray_pr_colormap( );
	msg_CVIP(fn,"writing %dx%d image data to Sun Raster file.", rows, cols); 
        msg_CVIP(fn,"8 bits per sample - GRAYSCALE.");
	msg_CVIP(fn,"1 sample per pixel.\n");
	break;

	default:
	depth = 1;
	pr_colormapP = (colormap_t*) 0;
	msg_CVIP(fn,"writing %dx%d image data to Sun Raster file.", rows, cols); 
        msg_CVIP(fn,"1 bit per sample - BINARY.");
	msg_CVIP(fn,"1 sample per pixel.\n");
	break;
	}

    if ( maxval > 255 && depth != 1 )
	msg_CVIP(fn,
	    "maxval is not 255 - automatically rescaling colors" );
    
    /* Allocate space for the Sun-format image. */
    if ( (pr = mem_create(cols, rows, depth)) == (struct pixrect*) 0 )
	pm_error( "unable to create new pixrect" );
    data = ( (struct mpr_data*) pr->pr_data )->md_image;
    linesize = ( (struct mpr_data*) pr->pr_data )->md_linebytes;

    /* And compute the Sun image.  The variables at this point are:
    **   cht is null or not
    **   depth is 1, 8, or 24
    */
    for ( row = 0; row < rows; ++row )
	{
	xelrow = xels[row];
	byteP = data;
	switch ( depth )
	    {
	    case 1:
	    *byteP = 0;
	    bitcount = 7;
	    for ( col = 0, xP = xelrow; col < cols; ++col, ++xP )
		{
		register int color;

                switch ( PNM_FORMAT_TYPE(format) )
                    {
                    case PPM_TYPE:
		    if ( maxval != 255 )
			PPM_DEPTH( *xP, *xP, maxval, 255 );
		    color = ppm_lookupcolor( cht, xP );
		    if ( color == -1 )
			pm_error(
			    "color not found?!?  row=%d col=%d  r=%d g=%d b=%d",
			    row, col, PPM_GETR(*xP), PPM_GETG(*xP),
			    PPM_GETB(*xP) );
		    if ( color )
			*byteP |= 1 << bitcount;
                    break;

		    default:
		    color = PNM_GET1( *xP );
		    if ( ! color )
			*byteP |= 1 << bitcount;
                    break;
                    }
		--bitcount;
		if ( bitcount < 0 )
		    {
		    ++byteP;
		    *byteP = 0;
		    bitcount = 7;
		    }
		}
	    break;

	    case 8:
	    for ( col = 0, xP = xelrow; col < cols; ++col, ++xP )
		{
		register int color;

                switch ( PNM_FORMAT_TYPE(format) )
                    {
                    case PPM_TYPE:
		    if ( maxval != 255 )
			PPM_DEPTH( *xP, *xP, maxval, 255 );
		    color = ppm_lookupcolor( cht, xP );
		    if ( color == -1 )
			pm_error(
			    "color not found?!?  row=%d col=%d  r=%d g=%d b=%d",
			    row, col, PPM_GETR(*xP), PPM_GETG(*xP),
			    PPM_GETB(*xP) );
                    break;

                    case PGM_TYPE:
		    color = PNM_GET1( *xP );
		    if ( maxval != 255 )
			color = color * 255 / maxval;
                    break;

		    default:
		    color = PNM_GET1( *xP );
                    }
		*byteP++ = color;
		}
	    break;

	    case 24:
	    /* If depth is 24, we do NOT have a valid cht. */
	    for ( col = 0, xP = xelrow; col < cols; ++col, ++xP )
		{
		if ( maxval != 255 )
		    PPM_DEPTH( *xP, *xP, maxval, 255 );
		*byteP++ = PPM_GETB( *xP );
		*byteP++ = PPM_GETG( *xP );
		*byteP++ = PPM_GETR( *xP );
		}
	    break;

	    default:
	    pm_error( "can't happen" );
	    }
	data += linesize;
	}
    pnm_freearray( xels, rows );

    /* Finally, write out. */
    if ( pr_dump( pr, outfp, pr_colormapP, pr_type, 0 ) == PIX_ERR )
	pm_error( "error writing rasterfile" );
    mem_free(pr);
}

static colormap_t*
make_pr_colormap( chv, colors )
    colorhist_vector chv;
    int colors;
    {
    colormap_t* pr_colormapP;
    int i;

    pr_colormapP = alloc_pr_colormap( );

    for ( i = 0; i < colors; ++i )
	{
	pr_colormapP->map[0][i] = PPM_GETR( chv[i].color );
	pr_colormapP->map[1][i] = PPM_GETG( chv[i].color );
	pr_colormapP->map[2][i] = PPM_GETB( chv[i].color );
	}
    for ( ; i < MAXCOLORS; ++i )
	pr_colormapP->map[0][i] = pr_colormapP->map[1][i] =
	    pr_colormapP->map[2][i] = 0;

    return pr_colormapP;
    }

static colormap_t*
make_gray_pr_colormap( )
    {
    colormap_t* pr_colormapP;
    int i;

    pr_colormapP = alloc_pr_colormap( );

    for ( i = 0; i < MAXCOLORS; ++i )
	{
	pr_colormapP->map[0][i] = i;
	pr_colormapP->map[1][i] = i;
	pr_colormapP->map[2][i] = i;
	}

    return pr_colormapP;
    }

static colormap_t*
alloc_pr_colormap( )
    {
    colormap_t* pr_colormapP;

    pr_colormapP = (colormap_t*) malloc( sizeof(colormap_t) );
    if ( pr_colormapP == (colormap_t*) 0 )
	pm_error( "out of memory" );
    pr_colormapP->type = RMT_EQUAL_RGB;
    pr_colormapP->length = MAXCOLORS;
    pr_colormapP->map[0] =
	(unsigned char*) malloc( MAXCOLORS * sizeof(unsigned char) );
    pr_colormapP->map[1] =
	(unsigned char*) malloc( MAXCOLORS * sizeof(unsigned char) );
    pr_colormapP->map[2] =
	(unsigned char*) malloc( MAXCOLORS * sizeof(unsigned char) );
    if ( pr_colormapP->map[0] == 0 || pr_colormapP->map[1] == 0 ||
	 pr_colormapP->map[2] == 0 )
	pm_error( "out of memory" );

    return pr_colormapP;
    }
