/***************************************************************************
======================================================================
Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
======================================================================
                                                                      
             File Name: rastocvip.c
           Description: contains a routine to load a SunRaster file into
			a CVIP Image structure.
         Related Files: CVIPimage.h, CVIPras.h, Imakefile
   Initial Coding Date: 1/24/93
           Portability: Standard (ANSI) C
             Credit(s): Gregory Hance, E.E. Dept. SIUE

  Global Function List: rastocvip
			
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

$Log: rastocvip.c,v $
Revision 1.8  1997/03/08 00:43:14  yawei
Name Changes:
	BOOLEAN ==> CVIP_BOOLEAN
	FALSE ==> CVIP_NO
	TRUE ==> CVIP_YES
	BYTE ==> CVIP_BYTE
	SHORT ==> CVIP_SHORT
	INTEGER ==> CVIP_INTEGER
	FLOAT ==> CVIP_FLOAT
	DOUBLE ==> CVIP_DOUBLE
	TYPE ==> CVIP_TYPE

Revision 1.7  1997/01/15 17:07:38  yawei
Global Change:  IMAGE ==> Image

 * Revision 1.6  1995/05/09  20:55:34  luok
 * fix the rle problem
 *
 * Revision 1.5  1995/05/09  20:19:16  luok
 * check file into RCS
 *
 * Revision 1.4  1995/02/06  18:52:34  luok
 * fix memory leak
 *
 * Revision 1.3  1995/02/02  03:23:23  luok
 * get rid of memory leak
 *
 * Revision 1.2  1995/02/02  03:10:06  luok
 * check file into RCS
 *
 * Revision 1.1  1993/05/31  07:10:16  hanceg
 * Initial revision
 *                                                         

*****************************************************************************/

#include "pnm.h"
#include "rast.h"
#define NO_STD_INCLUDES
#include "CVIPimage.h"

static int ras_load_header( FILE *in, struct rasterfile* hP );

Image *rastocvip(rasterfile, ifp, verbose)
char *rasterfile;
FILE* ifp;
int verbose;
{
    char* prog_name[2] = {"rastocvip"};
    Image *ras_Image;
    struct rasterfile header;
    colormap_t pr_colormap;
    int grayscale;
    struct pixrect* pr;
    xel* xelrow;
    register xel* xP;
    register gray* gP;
    register bit* bP;
    int rows, cols, format, depth, i, row, mask;
    register int col, j;
    xelval maxval = 255;
    xel zero, one;
    int linesize;
    unsigned char* data;
    unsigned char* byteP;
    byte *gray_ptr, *bit_ptr, *red_ptr, *blue_ptr, *green_ptr;

    pnm_init( &verbose, prog_name );

    /* Read in the rasterfile.  First the header. */
    if ( ras_load_header( ifp, &header ) != 0 )
	pm_error( "unable to read in rasterfile header" );

    cols = header.ras_width;
    rows = header.ras_height;
    depth = header.ras_depth;

    if ( cols <= 0 )
	pm_error( "invalid cols: %d", cols );
    if ( rows <= 0 )
	pm_error( "invalid rows: %d", rows );

    /* If there is a color map, read it. */
    grayscale = 1;
    if ( header.ras_maplength != 0 )
	{
	pm_message("reading Sun Raster colormap.");
	if ( pr_load_colormap( ifp, &header, &pr_colormap ) != 0 )
	    pm_error( "unable to skip colormap data" );
	for ( i = 0; i < header.ras_maplength / 3; ++i )
	    if ( pr_colormap.map[0][i] != pr_colormap.map[1][i] ||
		 pr_colormap.map[1][i] != pr_colormap.map[2][i] )
		{
		grayscale = 0;
		break;
		}
	if(!grayscale)
	   pm_message("%d colors found.", header.ras_maplength / 3);
	}

    /* Check the depth and color map. */
    switch ( depth )
	{
	case 1:
	if ( header.ras_maptype == RMT_NONE && header.ras_maplength == 0 )
	    {
	    maxval = pnm_pbmmaxval;
	    format = PBM_TYPE;
	    PNM_ASSIGN1( zero, maxval );
	    PNM_ASSIGN1( one, 0 );
	    }
	else if ( header.ras_maptype == RMT_EQUAL_RGB &&
		  header.ras_maplength == 6 )
	    {
	    if ( grayscale )
		{
		maxval = 255;
		format = PGM_TYPE;
		PNM_ASSIGN1( zero, pr_colormap.map[0][0] );
		PNM_ASSIGN1( one, pr_colormap.map[0][1] );
		}
	    else
		{
		maxval = 255;
		format = PPM_TYPE;
		PPM_ASSIGN(
		    zero, pr_colormap.map[0][0], pr_colormap.map[1][0],
		    pr_colormap.map[2][0] );
		PPM_ASSIGN(
		    one, pr_colormap.map[0][1], pr_colormap.map[1][1],
		    pr_colormap.map[2][1] );
		}
	    }
	else
	    pm_error(
      "this depth-1 rasterfile has a non-standard colormap - type %d length %d",
		header.ras_maptype, header.ras_maplength );
	break;

	case 8:
	if ( grayscale )
	    {
	    maxval = 255;
	    format = PGM_TYPE;
	    }
	else if ( header.ras_maptype == RMT_EQUAL_RGB )
	    {
	    maxval = 255;
	    format = PPM_TYPE;
	    }
	else
	    pm_error(
      "this depth-8 rasterfile has a non-standard colormap - type %d length %d",
		header.ras_maptype, header.ras_maplength );
	break;

	case 24:
	case 32:
	if ( header.ras_maptype == RMT_NONE && header.ras_maplength == 0 )
	    ;
	else if ( header.ras_maptype == RMT_RAW || header.ras_maplength == 768 )
	    ;
	else
	    pm_error(
     "this depth-%d rasterfile has a non-standard colormap - type %d length %d",
		depth, header.ras_maptype, header.ras_maplength );
	maxval = 255;
	format = PPM_TYPE;
	break;

	default:
	pm_error(
	    "invalid depth: %d.  Can only handle depth 1, 8, 24, or 32.",
	    depth );
	}

    /* Now load the data.  The pixrect returned is a memory pixrect. */
    if ( ( pr = pr_load_image( ifp, &header, NULL ) ) == NULL )
	pm_error(
	    "unable to read in the image from the rasterfile" );

    linesize = ( (struct mpr_data*) pr->pr_data )->md_linebytes;
    data = ( (struct mpr_data*) pr->pr_data )->md_image;

    /* Now write out the anymap. */
    xelrow = pnm_allocrow( cols );
    switch ( PNM_FORMAT_TYPE(format) )
        {
        case PBM_TYPE:
        pm_message( "loading %dx%d Sun Raster file image data - %s.", rows, cols, rasterfile );
	pm_message("1 bit per sample - BINARY.");
	pm_message("1 sample per pixel.\n");
	if ((ras_Image = image_allocate(RAS, BINARY, 1, rows, cols, CVIP_BYTE, REAL)) == NULL)
	   pm_error("couldn't alloc Image structure" );
        break;

        case PGM_TYPE:
        pm_message( "loading %dx%d Sun Raster file image data - %s.", rows, cols, rasterfile);
	pm_message("8 bits per sample - GRAYSCALE.");
	pm_message("1 sample per pixel.\n");
	if ((ras_Image = image_allocate(RAS, GRAY_SCALE, 1, rows, cols, CVIP_BYTE, REAL)) == NULL)
	   pm_error("couldn't alloc Image structure" );
        break;

        case PPM_TYPE:
        pm_message( "loading %dx%d Sun Raster file image data - %s.", rows, cols, rasterfile);
	if( header.ras_maptype == RMT_NONE && header.ras_maplength == 0 ) {
	   pm_message("8 bits per sample - RGB.");
	   pm_message("3 samples per pixel.\n");
	}
	else {
	   pm_message("8 bits per sample - RGB COLORMAPPED.");
	   pm_message("1 sample per pixel (colormapped to 3).\n");
	}
	if ((ras_Image = image_allocate(RAS, RGB, 3, rows, cols, CVIP_BYTE, REAL)) == NULL)
	   pm_error("couldn't alloc Image structure" );
        break;

        default:
        pm_error( "shouldn't happen" );
        }

    for ( row = 0; row < rows; ++row )
	{
	byteP = data;
	switch ( depth )
	    {
	    case 1:
	    mask = 0x80;
	    for ( col = 0, xP = xelrow; col < cols; ++col, ++xP )
		{
		if ( mask == 0 )
		    {
		    ++byteP;
		    mask = 0x80;
		    }
		*xP = ( *byteP & mask ) ? one : zero;
		mask = mask >> 1;
		}
	    break;

	    case 8:
	    for ( col = 0, xP = xelrow; col < cols; ++col, ++xP )
		{
		if ( header.ras_maplength == 0 )
		    PNM_ASSIGN1( *xP, *byteP );
		else if ( grayscale )
		    PNM_ASSIGN1( *xP, pr_colormap.map[0][*byteP] );
		else
		    PPM_ASSIGN(
			*xP, pr_colormap.map[0][*byteP],
			pr_colormap.map[1][*byteP],
			pr_colormap.map[2][*byteP] );
		++byteP;
		}
	    break;

	    case 24:
	    case 32:
	    for ( col = 0, xP = xelrow; col < cols; ++col, ++xP )
		{
		register xelval r, g, b;

		if ( depth == 32 )
		    ++byteP;
		if ( header.ras_type == RT_FORMAT_RGB )
		    {
		    r = *byteP++;
		    g = *byteP++;
		    b = *byteP++;
		    }
		else
		    {
		    b = *byteP++;
		    g = *byteP++;
		    r = *byteP++;
		    }
		if ( header.ras_maplength == 0 )
		    PPM_ASSIGN( *xP, r, g, b );
		else
		    PPM_ASSIGN(
			*xP, pr_colormap.map[0][r], pr_colormap.map[1][g],
			pr_colormap.map[2][b] );
		}
	    break;

	    default:
	    pm_error( "can't happen" );
	    }
	data += linesize;
	switch ( PNM_FORMAT_TYPE(format) ) {
	   case PPM_TYPE:
	      red_ptr   = (byte *) ras_Image->image_ptr[0]->rptr[row];
	      green_ptr = (byte *) ras_Image->image_ptr[1]->rptr[row];
	      blue_ptr  = (byte *) ras_Image->image_ptr[2]->rptr[row];
	      for (j = 0, xP = xelrow; j < cols; ++j, ++xP) {
	         *red_ptr++ = xP->r;
		 *green_ptr++ = xP->g;
		 *blue_ptr++ = xP->b;
	      }      
	      break;
	   case PGM_TYPE:
	      gray_ptr   = (byte *) ras_Image->image_ptr[0]->rptr[row];
	      for ( j = 0, gP = (gray *)gray_ptr, xP = xelrow; j < cols; ++j, ++gP, ++xP )
	         *gP = PNM_GET1( *xP );
	      break;
	   case PBM_TYPE:
	      bit_ptr   = (byte *) ras_Image->image_ptr[0]->rptr[row];
	      for ( j = 0, bP = (bit *) bit_ptr, xP = xelrow; j < cols; ++j, ++bP, ++xP )
	         *bP = PNM_GET1( *xP ) == 0 ? PBM_BLACK : PBM_WHITE;
	      break;
	   default:
	      pm_error( "can't happen" );
	}
   }

pm_freerow((char *)xelrow);
if(pr!=NULL)
   mem_free(pr);
/*The following is a fix to RLE*/
/*if(header.ras_type == 0002){
   int rows, cols, bands, im_row, im_col, im_band;
   byte **data;
   im_band = ras_Image->bands;
   im_row = ras_Image->bandP[0]->rows;
   im_col = ras_Image->bandP[0]->cols;
   for(bands = 0; bands < im_band; bands++){
	data = (byte**)ras_Image->bandP[bands]->rptr;
	for(rows = 0; rows < im_row; rows++){
	    for(cols = 0; cols < im_col; cols++){
		if(data[rows][cols] == 0)
		     data[rows][cols] = 255;
		else if( data[rows][cols] == 1)
		     data[rows][cols] = 0;
	    }
        }
   }
}*/
return ras_Image;
}


static int
ras_load_header( in, hP )
    FILE* in;
    struct rasterfile* hP;
    {
    if ( in != stdin ) {
       if ( pm_readbiglong( in, &(hP->ras_magic) ) == -1 )
          return PIX_ERR;
       if ( hP->ras_magic != RAS_MAGIC )
          return PIX_ERR;
    }
    if ( pm_readbiglong( in, &(hP->ras_width) ) == -1 )
	return PIX_ERR;
    if ( pm_readbiglong( in, &(hP->ras_height) ) == -1 )
	return PIX_ERR;
    if ( pm_readbiglong( in, &(hP->ras_depth) ) == -1 )
	return PIX_ERR;
    if ( pm_readbiglong( in, &(hP->ras_length) ) == -1 )
	return PIX_ERR;
    if ( pm_readbiglong( in, &(hP->ras_type) ) == -1 )
	return PIX_ERR;
    if ( pm_readbiglong( in, &(hP->ras_maptype) ) == -1 )
	return PIX_ERR;
    if ( pm_readbiglong( in, &(hP->ras_maplength) ) == -1 )
	return PIX_ERR;
    return 0;
    }
