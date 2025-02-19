/***************************************************************************
======================================================================
Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
======================================================================
                                                                      
             File Name: bintocvip.c
           Description: contains a routine to load an encapsulated postscript
			file into a CVIP Image structure.
         Related Files: CVIPimage.h, CVIPbin.h, Makefile
   Initial Coding Date: 1/24/93
           Portability: Standard (ANSI) C
             Credit(s): Gregory Hance, E.E. Dept. SIUE

  Global Function List: epstocvip
			
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

$Log: epstocvip.c,v $
Revision 1.6  1997/04/03 15:10:33  yawei
added support for gray XV eps format

Revision 1.5  1997/04/03 03:16:43  yawei
modified for reading

Revision 1.4  1997/03/08 17:00:03  yawei
Swaped CVIP_YES and CVIP_NO

Revision 1.3  1997/03/08 00:42:52  yawei
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

Revision 1.2  1997/01/15 17:06:49  yawei
Global Change:  IMAGE ==> Image

 * Revision 1.1  1993/05/31  07:10:14  hanceg
 * Initial revision
 *                                                         

*****************************************************************************/


#include <math.h>
#include <string.h>
#include <stdio.h>
#include "CVIPimage.h"
#include "CVIPconutils.h"
#define EPS_MAGIC1 'I'
#define EPS_MAGIC2 'm'
#define XV_GRAY_MAGIC "% dimensions of data"
#define EPS_FORMAT (((EPS_MAGIC1)<<8)|EPS_MAGIC2)
#define NEWLINE 0x0a
#define VALID_ASCIIHEX(hex)   ( ( (((0xF0)&(hex)) == 0x30) || (((0xF0)&(hex)) == 0x40) || (((0xF0)&(hex)) == 0x60) ) ?\
                              ( ( ((((0x0F)&(hex)) > 0x00) && (((0x0F)&(hex)) < 0x07)) || ((hex) == (0x30)) \
			       ||  ((hex) == (0x37)) || ((hex) == (0x38)) || ((hex) == (0x39)) ) ? 1 : 0 ) : 0 )
			          

Image *epstocvip(eps_image, inputfile, verbose)
char *eps_image;
FILE *inputfile;
CVIP_BOOLEAN verbose;
{
   Image *eps_Image;
   unsigned char c, d;
   int x=0,y;
   long int index;
   char xnum[5],ynum[5], function_name[] = {"epstocvip"};
   unsigned int length=0;
   CVIP_BOOLEAN data=CVIP_NO, valid_data=CVIP_YES;
   char buf[300];
   byte byte1, byte2, *data_buf;
   
   CVIPinit(function_name, verbose);

   if( inputfile != stdin )
      fgets(buf, 300, inputfile);
   else
      fgets(buf, 298, inputfile);
   while( !((CVIP2BytetoShort(buf[2],buf[1]) == EPS_FORMAT)
			   ||(CVIP2BytetoShort(buf[3],buf[2]) == EPS_FORMAT)
				||strstr(buf,XV_GRAY_MAGIC)) )  {
      fgets(buf, 300, inputfile);
	}
   
         
	if (strstr(buf,XV_GRAY_MAGIC)) {
		sscanf(buf, "%d %d", &x, &y);
      fgets(buf, 300, inputfile);
      fgets(buf, 300, inputfile);
      fgets(buf, 300, inputfile);
		if (strstr(buf,"false 3 colorimage")) {
			error_CVIP("function_name",
				"color EPS format not supported");
			return (Image *)NULL;
		} else if (!strcmp(buf, "image\n")) {
      	fgets(buf, 300, inputfile);
		} else {
			error_CVIP("function_name", "unrecognizable EPS format");
			return (Image *)NULL;
		}
	} else {
   	while(buf[x] != ' ') x++;

   	for(index=0, x++; buf[x] != ' '; x++, index++)
     	 xnum[index] = buf[x];
   	xnum[index] = '\0';
   
   	while(buf[x] == ' ') x++;
   
   	for(index=0; buf[x] != ' '; x++, index++)
      ynum[index] = buf[x];
	   ynum[index] = '\0';
   	x=atoi(xnum);
   	y=atoi(ynum);
	}

   
   CVIPmessage("loading %dx%d Encapsulated PostScript(EPS) image - %s",x,y,eps_image);
   CVIPmessage("8 bits per sample - gray scale.");
   CVIPmessage("1 sample per pixel.\n");
   
   if( (eps_Image = image_allocate(EPS, GRAY_SCALE, 1, y, x, CVIP_BYTE, REAL)) == NULL )
      CVIPerror("could not allocate Image structure");
      
   data_buf = (byte *) *((byte **)eps_Image->image_ptr[0]->rptr);

   while(data == CVIP_NO) {
      fgets(buf, 80, inputfile);
      if( !((buf[0]=='%') || (buf[0]=='/')) )
         if(  VALID_ASCIIHEX(buf[0]) &&
              VALID_ASCIIHEX(buf[1]) &&
	      VALID_ASCIIHEX(buf[2]) &&
	      VALID_ASCIIHEX(buf[3]) )
	        data = CVIP_YES;
   }
   
   while(valid_data) {
      byte1=ASCIIHEXtoDECIMAL(buf[length]);
      byte2=ASCIIHEXtoDECIMAL(buf[length+1]);
      if(VALID_ASCIIHEX(buf[length])) {
         *data_buf++ = (byte1<<4)|byte2;
         length+=2;
      }
      else
         valid_data = CVIP_NO;
   }

   length >>= 1;
   for(index=0; index < x*y-length; index++) {
      c=fgetc(inputfile);
         if(c!=NEWLINE) {
	    d=fgetc(inputfile);
	    byte1 = ASCIIHEXtoDECIMAL(c);
	    byte2 = ASCIIHEXtoDECIMAL(d);
	    *data_buf++ = (byte1<<4)|byte2;
	 }
	 else
	    index--;
   }

return eps_Image;

}
