/***************************************************************************
======================================================================
Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
======================================================================
                                                                      
             File Name: cviptoitex.c
           Description: contains a routine to write the contents of a
			CVIPtools Image structure to an ITEX file.
         Related Files: CVIPimage.h, CVIPitex.h, Makefile
   Initial Coding Date: 1/24/93
           Portability: Standard (ANSI) C
             Credit(s): Gregory Hance, E.E. Dept. SIUE

  Global Function List: cviptoitex
			
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

$Log: cviptoitex.c,v $
Revision 1.4  1997/03/08 17:00:07  yawei
Swaped CVIP_YES and CVIP_NO

Revision 1.3  1997/03/08 00:42:54  yawei
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

Revision 1.2  1997/01/15 17:06:58  yawei
Global Change:  IMAGE ==> Image

 * Revision 1.1  1993/05/31  07:10:12  hanceg
 * Initial revision
 *                                                         

*****************************************************************************/


#include <math.h>
#include <string.h>
#include <stdio.h>
#include "CVIPimage.h"
#include "CVIPconutils.h"
#define ITEX_COMPRESSION 0
#define ITEX_MAGIC1 'I'
#define ITEX_MAGIC2 'M'
#define ITEX_FORMAT (ITEX_MAGIC1 * 256 + ITEX_MAGIC2)

	
void cviptoitex(cvip_Image, cvip_name, outputfile, image_comment, verbose)
Image *cvip_Image;
char *cvip_name;
FILE *outputfile;
char *image_comment;
CVIP_BOOLEAN verbose;
{
   unsigned char c,d, buf[14];
   int image_width, image_height, x_origin=0, y_origin=0;
   char function_name[] = {"cviptoitex"};

   CVIPinit(function_name, CVIP_YES);

   CVIPmessage("opening binary ITEX output file as: %s", cvip_name);
   
   image_width  = cvip_Image->image_ptr[0]->cols;
   image_height = cvip_Image->image_ptr[0]->rows;
    
   CVIPShortto2Byte(ITEX_FORMAT,buf[0],buf[1]);
   CVIPShortto2Byte(strlen(image_comment) + 1,buf[3],buf[2]);
   CVIPShortto2Byte(image_width,buf[5],buf[4]);
   CVIPShortto2Byte(image_height,buf[7],buf[6]);
   CVIPShortto2Byte(x_origin,buf[9],buf[8]);
   CVIPShortto2Byte(y_origin,buf[12],buf[11]);
   CVIPShortto2Byte(ITEX_COMPRESSION,buf[13],buf[12]);
   
   CVIPWriteBytes(outputfile, buf, 14);   
   if(fseek(outputfile, 49, SEEK_CUR)) /* skip reserved section */
      CVIPerror("ITEX reserved section apparently is not!");
   CVIPWriteBytes(outputfile, image_comment, strlen(image_comment)+1);
   CVIPmessage("image comment: %s", image_comment);
   CVIPWriteBytes(outputfile, *((byte **)cvip_Image->image_ptr[0]->rptr), image_width*image_height);
   CVIPmessage("writing %dx%d 8-bit grayscale image", image_width, image_height);
   CVIPmessage("8 bits per sample.");
   CVIPmessage("1 sample per pixel.\n");

}
	
