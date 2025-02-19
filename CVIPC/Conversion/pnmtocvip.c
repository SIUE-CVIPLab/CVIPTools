/***************************************************************************
======================================================================
Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
======================================================================
                                                                      
             File Name: pnmtocvip.c
           Description: contains a routine to load a PBM, PGM or PPM file into
			a CVIPtools Image structure.
         Related Files: CVIPimage.h, CVIPpnm.h, Makefile
   Initial Coding Date: 1/24/93
           Portability: Standard (ANSI) C
             Credit(s): Gregory Hance, E.E. Dept. SIUE

  Global Function List: pnmtocvip
			
****************************************************************************

** Copyright (C) 1991, 1992, 1993 SIUE - by Scott Umbaugh, Greg Hance.
** Copyright (C) 1988 by Jef Poskanzer.
**
** Permission to use, copy, modify, and distribute this software and its
** documentation for any purpose and without fee is hereby granted, provided
** that the above copyright notice appear in all copies and that both that
** copyright notice and this permission notice appear in supporting
** documentation.  This software is provided "as is" without express or
** implied warranty.

RCS (Revision Control System) Information - Added automatically by RCS) 

$Log: pnmtocvip.c,v $
Revision 1.7  1997/03/08 00:43:17  yawei
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

Revision 1.6  1997/01/15 17:07:43  yawei
Global Change:  IMAGE ==> Image

 * Revision 1.5  1995/05/09  22:31:08  luok
 * nothing changed
 *
 * Revision 1.4  1995/05/09  22:15:19  luok
 * check file into RCS
 *
 * Revision 1.3  1995/02/06  18:52:14  luok
 * fix memory leakl
 *
 * Revision 1.2  1995/02/06  17:50:02  luok
 * check file in.
 *
 * Revision 1.1  1993/05/31  07:10:16  hanceg
 * Initial revision
 *                                                         

*****************************************************************************/

#include "pnm.h"
#define NO_STD_INCLUDES
#include "CVIPimage.h"
#include "CVIPxel.h"

static xel **cvip_readpnm( FILE* file, int* colsP, int* rowsP, xelval* maxvalP, int* formatP );
static void cvip_readpnminit( FILE* file, int* colsP, int* rowsP, xelval* maxvalP, int* formatP );
   
Image *pnmtocvip(pnm_file, ifp, format, verbose)
    char* pnm_file;
    FILE *ifp;
    int format;
    int verbose;
    {
    Image *pnm_Image;
    byte **r_plane, **g_plane, **b_plane;
    char* prog_name[1] = {"pnmtocvip"};
    const char *fn = "pnmtocvip";
    int rows, cols, i;
    unsigned int image_dimension;
    xelval maxval;
    xel** xels;
    register xel* xP;
    register byte* gP;
    register byte* bP;
    byte *gray_ptr, *bit_ptr;

    
    pnm_init( &verbose, prog_name );

    xels = (xel **) cvip_readpnm( ifp, &cols, &rows, &maxval, &format );
    image_dimension = rows*cols;

	switch ( PNM_FORMAT_TYPE(format) ) {
	   case PPM_TYPE:
	      msg_CVIP(fn,"loading %dx%d Portable Pixmap(PPM) - %s.\n",rows, cols, pnm_file);
	      msg_CVIP(fn,"8 bits per sample.\n");
	      msg_CVIP(fn,"3 samples per pixel.\n");
	      pnm_Image = (Image *) image_allocate(PPM, RGB, 3, rows, cols, CVIP_BYTE, REAL); 
              r_plane = (byte **) pnm_Image->image_ptr[0]->rptr;
	      g_plane = (byte **) pnm_Image->image_ptr[1]->rptr;
	      b_plane = (byte **) pnm_Image->image_ptr[2]->rptr;
	      PNM_TO_CVIP((pixel **) xels, r_plane, g_plane, b_plane, rows, cols, byte);
	      break;
	   case PGM_TYPE:
	      msg_CVIP(fn,"loading %dx%d Portable Graymap(PGM) - %s.\n",rows, cols, pnm_file);
	      msg_CVIP(fn,"8 bits per sample.\n");
	      msg_CVIP(fn,"1 sample per pixel.\n");
	      pnm_Image = (Image *) image_allocate(PGM, GRAY_SCALE, 1, rows, cols, CVIP_BYTE, REAL);
	      gray_ptr   = (byte *) pnm_Image->image_ptr[0]->rptr[0];
	      for ( i = 0, gP = (byte *)gray_ptr, xP = *xels; i < image_dimension; ++i, ++gP, ++xP )
	         *gP = PNM_GET1( *xP );
	      break;
	   case PBM_TYPE:
	      msg_CVIP(fn,"loading %dx%d Portable Bitmap(PBM) - %s.\n",rows, cols, pnm_file);
	      msg_CVIP(fn,"1 bit per sample.\n");
	      msg_CVIP(fn,"1 sample per pixel.\n");
	      pnm_Image = (Image *) image_allocate(PBM, BINARY, 1, rows, cols, CVIP_BYTE, REAL);
	      bit_ptr   = (byte *) pnm_Image->image_ptr[0]->rptr[0];
	      for ( i = 0, bP = (byte *) bit_ptr, xP = *xels; i < image_dimension; ++i, ++bP, ++xP )
	         *bP = PNM_GET1( *xP ) == 0 ?  PBM_BLACK : PBM_WHITE;
	      break;
	   default:
	      pm_error( "can't happen" );
	}
    pm_freearray((char **)xels,rows);        
    return pnm_Image;   
    }


static xel**
cvip_readpnm( file, colsP, rowsP, maxvalP, formatP )
    FILE* file;
    int* colsP;
    int* rowsP;
    int* formatP;
    xelval* maxvalP;
    {
    xel** xels;
    int row;

    cvip_readpnminit( file, colsP, rowsP, maxvalP, formatP );

    xels = pnm_allocarray( *colsP, *rowsP );

    for ( row = 0; row < *rowsP; ++row )
	pnm_readpnmrow( file, xels[row], *colsP, *maxvalP, *formatP );
    return xels;
    }

static void
cvip_readpnminit( file, colsP, rowsP, maxvalP, formatP )
    FILE* file;
    int* colsP;
    int* rowsP;
    int* formatP;
    xelval* maxvalP;
    {
    gray gmaxval;

    /* Check magic number. */
    if( file != stdin )
       *formatP = pbm_readmagicnumber( file );
    switch ( PNM_FORMAT_TYPE(*formatP) )
	{
	case PPM_TYPE:
	ppm_readppminitrest( file, colsP, rowsP, (pixval*) maxvalP );
	break;

	case PGM_TYPE:
	pgm_readpgminitrest( file, colsP, rowsP, &gmaxval );
	*maxvalP = (xelval) gmaxval;
	break;

	case PBM_TYPE:
	pbm_readpbminitrest( file, colsP, rowsP );
	*maxvalP = pnm_pbmmaxval;
	break;

	default:
	pm_error( "bad magic number - not a ppm, pgm, or pbm file" );
	}
    }
