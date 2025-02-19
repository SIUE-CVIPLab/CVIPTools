/***************************************************************************
======================================================================
Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
======================================================================
                                                                      
             File Name: cviptoeps.c
           Description: contains a routine to write the contents of a 
			CVIPtools Image structure to EPS file.
         Related Files: CVIPimage.h, CVIPeps.h, Imakefile
   Initial Coding Date: 1/24/93
           Portability: Standard (ANSI) C
             Credit(s): Gregory Hance, E.E. Dept. SIUE

  Global Function List: cviptoeps
			
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

$Log: cviptoeps.c,v $
Revision 1.5  1997/04/03 15:56:41  yawei
modified a little bit

Revision 1.4  1997/04/03 15:35:15  yawei
added band support

Revision 1.3  1997/03/08 00:42:57  yawei
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

Revision 1.2  1997/01/15 17:07:03  yawei
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
#include "CVIPluminance.h"

void cviptoeps(Image *cvip_Image, char *eps_name, FILE * outputfile,
	float scale_x, float scale_y, int  band, CVIP_BOOLEAN verbose)
{
   int x,y, bands;
   char function_name[] = {"cviptoeps"}; 
   long int i;
   int xlate=0,ylate=0, xscale, yscale;
   byte *image_data;
	CVIP_BOOLEAN duplicated = CVIP_NO;

   CVIPinit(function_name, verbose);

   x = cvip_Image->image_ptr[0]->cols;
   y = cvip_Image->image_ptr[0]->rows;
	bands = getNoOfBands_Image(cvip_Image);

	if (bands > 1) {
		if(band >= bands) {
			error_CVIP("cviptoeps", "the given band is not present");
			/*delete_Image(cvip_Image);*/
			return;
		} else if (band < 0 && bands == 3) {
			print_CVIP("convert to gray level image by luminance transform");
			cvip_Image = duplicate_Image(cvip_Image);
			if (!cvip_Image) {
				error_CVIP("duplicate_Image", "duplicate image failed");
				/*delete_Image(cvip_Image);*/
				return;
			}
			cvip_Image = luminance_Image(cvip_Image);
			band = 0;
			duplicated = CVIP_YES;
		}
	} else band = 0;
   xscale = x*scale_x + 0.5;
   yscale = y*scale_y + 0.5;
      
   CVIPmessage("opening Encapsulated PostScript(EPS) output file - %s.",eps_name);
   CVIPmessage("writing %dx%d gray scale image data.",x,y);
   CVIPmessage("8 bits per sample.");
   CVIPmessage("1 sample per pixel.\n");

   fputs("%!PS-Adobe-2.0 EPSF-1.2\n",outputfile);
   fputs("%%Creator:CVIP Image Converter - cviptoeps()\n", outputfile);

   fprintf(outputfile,"%%%%Title:%s\n",eps_name);

   fputs("%%CreationDate Fri Jul 08 12:59:00 1966\n", outputfile);
   fputs("%%Origin:0 720\n", outputfile);

   fprintf(outputfile,"%%%%BoundingBox: 0.000 0.000 %d.000 %d.000\n", xscale, yscale);

   fputs("%%EndComments\n",outputfile);

   fprintf(outputfile,"%%ImageData: %d %d 8 1 0 %d 0 \"beginimage\"\n",x,y,x);
   fprintf(outputfile,"/width %d def\n",x);
   fprintf(outputfile,"/height %d def\n",y);
   fprintf(outputfile,"/pixelwidth %d def\n",xscale);
   fprintf(outputfile,"/pixelheight %d def\n",yscale);
   fprintf(outputfile,"/xlate %d def\n",xlate);
   fprintf(outputfile,"/ylate %d def\n",ylate);

   fputs("/picstr width string def\n", outputfile);
   fputs("/dopic {\n", outputfile);
   fputs("	gsave\n", outputfile);
   fputs("	width height 8\n", outputfile);
   fputs("	[width 0 0 height neg 0 height]\n", outputfile);
   fputs("	{ currentfile picstr readhexstring pop }\n", outputfile);
   fputs("	image\n", outputfile);
   fputs("	grestore\n", outputfile);
   fputs("	} def\n", outputfile);

   fprintf(outputfile,"xlate ylate translate\n",xlate,ylate);

   fputs("pixelwidth pixelheight scale\n",outputfile);
   fputs("dopic\n", outputfile);

   /*image_data = (byte *) *((byte **) cvip_Image->image_ptr[0]->rptr);*/
   image_data = (byte *) *((byte **) getData_Image(cvip_Image, band));

   for (i=0;i<x*y;i++) {
      if(!((i+1)%65)) 
         fputc('\n',outputfile);
      fprintf(outputfile,"%02x",*image_data++);
   }

	fputs("\nshowpage\n", outputfile);
	if (duplicated == CVIP_YES) delete_Image(cvip_Image);
}
