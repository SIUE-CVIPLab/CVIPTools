/***************************************************************************
======================================================================
Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
======================================================================
                                                                      
             File Name: cviptopnm.c
           Description: contains a routine to write the contents of a CVIPtools
			Image structure out to a PBM, PGM or PPM file.
         Related Files: CVIPimage.h, CVIPpnm.h, Imakefile
   Initial Coding Date: 1/24/93
           Portability: Standard (ANSI) C
             Credit(s): Gregory Hance, E.E. Dept. SIUE

  Global Function List: cviptopnm
			
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

$Log: cviptopnm.c,v $
Revision 1.5  1997/01/15 17:07:54  yawei
Global Change:  IMAGE ==> Image

 * Revision 1.4  1997/01/15  16:10:46  yawei
 * updated changes
 *
 * Revision 1.3  1995/02/02  03:22:56  luok
 * get rid of memory leak
 *
 * Revision 1.2  1995/02/01  16:41:03  luok
 * check file into RCS
 *
 * Revision 1.1  1993/05/31  07:10:13  hanceg
 * Initial revision
 *                                                         

*****************************************************************************/

#include "ppm.h"
#define NO_STD_INCLUDES
#include "CVIPimage.h"
#include "CVIPxel.h"

void cviptopnm( cvip_Image ,pnm_name , outfp, verbose)
    Image* cvip_Image;
    char *pnm_name;
    FILE *outfp;
    int verbose;
    {
    byte **r_plane, **g_plane, **b_plane;
    char* prog_name[1] = {"cviptopnm"};
	const char *fn = "cviptopnm";
    int rows, cols;
    bit **binary_image;
    gray **gray_image;
    pixel **rgb_image;

    rows = cvip_Image->image_ptr[0]->rows;
    cols = cvip_Image->image_ptr[0]->cols;
    
    pm_init( &verbose, prog_name );

    switch(cvip_Image->color_space) {
       case BINARY:
	  if(verbose) {
	     msg_CVIP(fn,"writing %dx%d Portable Bitmap(PBM) - %s.\n",rows, cols, pnm_name);
	     msg_CVIP(fn,"1 bit per sample.\n");
	     msg_CVIP(fn,"1 sample per pixel.\n");
	  }
          binary_image = (bit **) cvip_Image->image_ptr[0]->rptr;
	  pbm_writepbm( outfp, binary_image, cols, rows, 0 );
	  break;
       case GRAY_SCALE:
	  if(verbose) {
	     msg_CVIP(fn,"writing %dx%d Portable Graymap(PGM) - %s.\n",rows, cols, pnm_name);
	     msg_CVIP(fn,"8 bits per sample.\n");
	     msg_CVIP(fn,"1 sample per pixel.\n");
	  }
          gray_image = (gray **) cvip_Image->image_ptr[0]->rptr;
	  pgm_writepgm( outfp, gray_image, cols, rows, 255, 0);
	  break;
       case RGB:
	  if(verbose) {
	     msg_CVIP(fn,"writing %dx%d Portable Pixmap(PPM) - %s.\n",rows, cols, pnm_name);
	     msg_CVIP(fn,"8 bits per sample.\n");
	     msg_CVIP(fn,"3 samples per pixel/RGB interleaved.\n");
	  }
          r_plane = (byte **) cvip_Image->image_ptr[0]->rptr;
	  g_plane = (byte **) cvip_Image->image_ptr[1]->rptr;
	  b_plane = (byte **) cvip_Image->image_ptr[2]->rptr;

	  rgb_image = ppm_allocarray( cols, rows );
	  CVIP_TO_PNM(rgb_image, r_plane, g_plane, b_plane, rows, cols, byte);
	  ppm_writeppm( outfp, rgb_image, cols, rows, 255, 0);
	  pm_freearray((char **)rgb_image,rows);
	  break;
       default:
          msg_CVIP(fn,"You've done it now!\n");
	  break;
    }

}
