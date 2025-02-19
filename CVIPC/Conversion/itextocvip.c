/***************************************************************************
======================================================================
Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
======================================================================
                                                                      
             File Name: itextocvip.c
           Description: contains a routine to load an ITEX file into
			a CVIP Image structure.
         Related Files: CVIPimage.h, CVIPitex.h, Makefile
   Initial Coding Date: 1/24/93
           Portability: Standard (ANSI) C
             Credit(s): Gregory Hance, E.E. Dept. SIUE

  Global Function List: itextocvip
			
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

$Log: itextocvip.c,v $
Revision 1.3  1997/03/08 00:42:49  yawei
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

Revision 1.2  1997/01/15 17:06:40  yawei
Global Change:  IMAGE ==> Image

 * Revision 1.1  1993/05/31  07:10:15  hanceg
 * Initial revision
 *                                                         

*****************************************************************************/


#include <math.h>
#include <stdio.h>
#include "CVIPimage.h"
#include "CVIPconutils.h"
#define ITEX_MAGIC1 'I'
#define ITEX_MAGIC2 'M'
#define ITEX_FORMAT (((ITEX_MAGIC1)<<8)|ITEX_MAGIC2)


Image *itextocvip(char *itex_image, FILE *inputfile, CVIP_BOOLEAN verbose)
{
	unsigned char c,d, buf[13];
	char comstring[256], function_name[] = {"itextocvip"};
	unsigned short comment, x, y, xorig, yorig;
	int count, bc = 2;
	Image *itex_Image;

        CVIPinit(function_name, verbose);
	
        if( inputfile != stdin ) bc=0;

        CVIPReadBytes(inputfile,buf,13-bc);

        if( inputfile != stdin )
	   if( CVIP2BytetoShort(buf[1],buf[0]) != ITEX_FORMAT )
	      CVIPerror("Attempted to Read Non ITEX Image File");
	
        comment=CVIP2BytetoShort(buf[2-bc],buf[3-bc]);
	          
	    x = CVIP2BytetoShort(buf[4-bc],buf[5-bc]);
            y = CVIP2BytetoShort(buf[6-bc],buf[7-bc]);
	xorig = CVIP2BytetoShort(buf[8-bc],buf[9-bc]);
        yorig = CVIP2BytetoShort(buf[10-bc],buf[11-bc]);

	CVIPmessage("loading %dx%d ITEX image data - %s",x,y,itex_image);
	CVIPmessage("8 bits per sample.");
	CVIPmessage("1 sample per pixel.");
	
	if( (itex_Image = image_allocate(ITX, GRAY_SCALE, 1, y, x, CVIP_BYTE, REAL)) == NULL )
	   CVIPerror("could not allocate Image structure");

	if(buf[12-bc])
	   CVIPerror("ITEX format appears to be compressed - can not handle this!");

        if(fseek(inputfile, 50, SEEK_CUR)) /* skip reserved section */
	   CVIPerror("ITEX reserved section apparently is not!");
	
	if( !CVIPReadBytes(inputfile, comstring, comment) )
	   CVIPerror("could not read ITEX comment");

	if(comment) {
	   comstring[comment] = '\0';
	   CVIPmessage("the comment contained in the ITEX image file is: \n            %s\n",comstring);
	}
	else
	   CVIPmessage("ITEX image file contains no comment\n");
		
        CVIPReadBytes(inputfile, *((byte **)itex_Image->image_ptr[0]->rptr), x*y);

return itex_Image;
}

