/***************************************************************************
* ======================================================================
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* ======================================================================
*
*             File Name: viptocvip.c
*           Description: read the contents of an Image structure from a
*                        CVIPtools "VIP - Visualization in Image Processing"
*                        format
*         Related Files: libconverter.a, CVIPvip.h, CVIPmagic.h
*   Initial Coding Date: Wed Apr  7 18:38:26 CDT 1993
*           Portability: Standard (ANSI) C
*             Credit(s): Gregory Hance, Arve Kjoelena
*                        Southern Illinois University @ Edwardsville
*
** Copyright (C) 1993 SIUE - by Gregory Hance and Arve Kjoelena.
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
* $Log: viptocvip.c,v $
* Revision 1.7  1997/03/08 17:00:51  yawei
* Swaped CVIP_YES and CVIP_NO
*
* Revision 1.6  1997/03/08 00:43:37  yawei
* Name Changes:
* 	BOOLEAN ==> CVIP_BOOLEAN
* 	FALSE ==> CVIP_NO
* 	TRUE ==> CVIP_YES
* 	BYTE ==> CVIP_BYTE
* 	SHORT ==> CVIP_SHORT
* 	INTEGER ==> CVIP_INTEGER
* 	FLOAT ==> CVIP_FLOAT
* 	DOUBLE ==> CVIP_DOUBLE
* 	TYPE ==> CVIP_TYPE
*
* Revision 1.5  1997/01/15 17:08:13  yawei
* Global Change:  IMAGE ==> Image
*
 * Revision 1.4  1997/01/15  16:12:13  yawei
 * updated changes
 *
 * Revision 1.3  1995/09/22  17:34:30  kluo
 * history is saved
 *
 * Revision 1.2  1995/09/18  20:50:43  kluo
 * check file in
 *
 * Revision 1.1  1993/05/31  07:10:16  hanceg
 * Initial revision
 *
*
****************************************************************************/
#include "CVIPimage.h"
#include "CVIPmagic.h"
#include "CVIPvip.h"

static long readMagic_VIP(FILE *file);

Image *viptocvip( char *filename, FILE *file, CVIP_BOOLEAN verbose )
{
	const char *fn = "viptocvip", *col[] = { "BINARY", "GRAY_SCALE", "RGB",
	"HSL", "HSV", "SCT", "CCT", "LUV", "LAB", "XYZ"}, *form[] = {"REAL",
	"COMPLEX" }, *typ[] = {"CVIP_BYTE", "CVIP_SHORT", "CVIP_INTEGER", "CVIP_FLOAT", "CVIP_DOUBLE"};
	Image 	*imageP;
	XDR 	xdri;

	if(verbose)
		msg_CVIP(fn, "reading CVIPtools \"VIP\" image from %s ...\n", filename);

	if( file != stdin )
		if(readMagic_VIP(file) != CVIPMAGIC ) {
        		error_CVIP(fn,"not a CVIPtools \"VIP\" file.");
         		return NULL;
      		} 

	xdrstdio_create(&xdri, file, XDR_DECODE);

	if(!(imageP = (Image *) calloc(1, sizeof(Image))) ) {
		error_CVIP(fn, "could not allocate image structure.");
		return NULL;
	}

	if(!xdr_image(&xdri, imageP,file,NULL,CVIP_NO,CVIP_NO)) {
		error_CVIP(fn,"XDR I/O failed.");
		error_CVIP(fn,"could not write image to %s.", filename);
		return NULL;
	}

	if(verbose) {
		msg_CVIP(fn,"listing image attributes ...\n");
		msg_CVIP(fn," color space -- %s.\n", col[getColorSpace_Image(imageP)]);
		msg_CVIP(fn,"   data type -- %s.\n", typ[getDataType_Image(imageP)]);
		msg_CVIP(fn,"      format -- %s.\n", form[getDataFormat_Image(imageP)]);
		msg_CVIP(fn,"       bands -- %u.\n", getNoOfBands_Image(imageP));
		msg_CVIP(fn,"        rows -- %d.\n", getNoOfRows_Image(imageP));
		msg_CVIP(fn,"        cols -- %d.\n", getNoOfCols_Image(imageP));

	}
   
return imageP;
}


static long readMagic_VIP(FILE *file)
{
long magic1, magic2, magic3;
const char *fn = "readMagic_VIP";

   magic1 = getc( file );
   if ( magic1 == EOF ) {
      error_CVIP(fn, "unexpected EOF while reading magic number" );
      return 0;
   }
   magic2 = getc( file );
   if ( magic2 == EOF ) {
      error_CVIP(fn, "unexpected EOF while reading magic number" );
      return 0;
   }
   magic3 = getc( file );
   if ( magic3 == EOF ) {
      error_CVIP(fn, "unexpected EOF while reading magic number" );
      return 0;
   }
   return (magic1<<16) | (magic2<<8) | magic3;
}
