/***************************************************************************
======================================================================
Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
======================================================================
                                                                      
             File Name: bintocvip.c
           Description: contains a routine to load a raw data file into
			a CVIP Image structure.
         Related Files: CVIPimage.h, CVIPbin.h, Makefile
   Initial Coding Date: 1/24/93
           Portability: Standard (ANSI) C
             Credit(s): Gregory Hance, E.E. Dept. SIUE

  Global Function List: bintocvip
			
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

$Log: bintocvip.c,v $
Revision 1.4  1997/03/08 17:00:29  yawei
Swaped CVIP_YES and CVIP_NO

Revision 1.3  1997/03/08 00:43:11  yawei
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

Revision 1.2  1997/01/15 17:07:33  yawei
Global Change:  IMAGE ==> Image

 * Revision 1.1  1993/05/31  07:10:09  hanceg
 * Initial revision
 *                                                         

*****************************************************************************/

#include <math.h>
#include <stdio.h>
#include "CVIPimage.h"
#include "CVIPconutils.h"

typedef enum { ORD_RGB, ORD_RBG, ORD_GRB, ORD_GBR, ORD_BRG, ORD_BGR } COLOR_ORDER;
typedef enum {INTERPLANE, INTERLINE, INTERPIXEL} INTERLEAVE_SCHEME;

/****************************************************************
                  Name: bintocvip
         Expanded Name: Binary (Raw) format to CVIP Image format
            Parameters:  inputfile - file pointer to open image file
			 data_bands - number of data bands in image (1-3)
			color_order - color ordering. one of...
				      ORD_RGB, ORD_RBG, ORD_GRB, ORD_GBR, 
				      ORD_BRG, ORD_BGR
			interleaved - interleave scheme. one of...
				      INTERPLANE, INTERLINE, INTERPIXEL
			     height - height of image (rows)
			      width - width of image (cols)
			    verbose - wanna know what I do?
               Returns: pointer to newly allocated Image structure with
			data from raw image.
           Description: loads an Image structure with data from a raw
			image and initializes all parameters of the structure
			to the specifications of the image.
           Diagnostics: prints out info. pertaining to the specifications
			of the image being loaded if verbose is CVIP_YES.
			returns with NULL pointer and error message when
			size of image being read from file raw_image does
			not correspond to height*width*data_bands
             Credit(s): Greg Hance
			
			
****************************************************************/

Image *bintocvip(char * raw_image, FILE *inputfile, int data_bands, COLOR_ORDER color_order, INTERLEAVE_SCHEME interleaved, int height, int width, CVIP_BOOLEAN verbose)
{
   char function_name[] = {"bintocvip"};
   char *color[6] = {"RGB","RBG","GRB", "GBR" ,"BRG", "BGR"};
   char *scheme[3] = {"INTERPLANE", "INTERLINE", "INTERPIXEL"};
   Image *raw_Image;
   int i;
   long bytes_in_image;
   byte *r_ptr, *g_ptr, *b_ptr;
   byte *buf1, *buf2, *buf3; 
   
   CVIPinit(function_name, verbose);
   
   fseek(inputfile,0,2);
   bytes_in_image = (long) ftell(inputfile);
   fseek(inputfile,0,0);
   
   if(bytes_in_image != (width*height*data_bands)) {
      CVIPerror("specified height and width does not correspond with");
      CVIPerror("the number of bytes found in the file.");
      CVIPerror("found %ld bytes, should be %ld bytes ... sorry!\n",bytes_in_image,width*height*data_bands);
      return NULL;
   }
      
        
   switch(data_bands) {
      
      case 1:   if( (raw_Image = image_allocate(BIN, GRAY_SCALE, 1, height, width, CVIP_BYTE, REAL)) == NULL )
	           CVIPerror("could not allocate Image structure");
		CVIPmessage("loading %dx%d raw bytes of image data from file - %s.",width,height,raw_image);
		CVIPmessage("8 bits per sample. - GRAYSCALE");
		CVIPmessage("1 sample per pixel.\n");
		CVIPReadBytes(inputfile,*((byte **)raw_Image->image_ptr[0]->rptr),width*height);
		break;
      case 3:   if( (raw_Image = image_allocate(BIN, RGB, 3, height, width, CVIP_BYTE, REAL)) == NULL )
	           CVIPerror("could not allocate Image structure");
		CVIPmessage("loading %dx%dx%d raw bytes of image data from file - %s.",width,height,data_bands,raw_image);
	        CVIPmessage("color order - %s.", color[color_order]);
		CVIPmessage("interleave scheme - %s.", scheme[interleaved]);
		CVIPmessage("8 bits per sample.");
		CVIPmessage("3 samples per pixel.\n");
		r_ptr = (byte *) *((byte **)raw_Image->image_ptr[0]->rptr);
		g_ptr = (byte *) *((byte **)raw_Image->image_ptr[1]->rptr);
		b_ptr = (byte *) *((byte **)raw_Image->image_ptr[2]->rptr);
		switch(color_order) { 
                   case 0: buf1 = r_ptr; 
                           buf2 = g_ptr; 
                           buf3 = b_ptr; 
                           break; 
                   case 1: buf1 = r_ptr; 
                           buf2 = b_ptr; 
              		   buf3 = g_ptr; 
              		   break; 
     	           case 2: buf1 = g_ptr; 
                           buf2 = r_ptr; 
                           buf3 = b_ptr; 
                           break; 
                   case 3: buf1 = g_ptr; 
                           buf2 = b_ptr; 
                           buf3 = r_ptr; 
                           break; 
                   case 4: buf1 = b_ptr; 
                           buf2 = r_ptr; 
                           buf3 = g_ptr; 
                           break; 
                   case 5: buf1 = b_ptr; 
                           buf2 = g_ptr; 
                           buf3 = r_ptr; 
                           break;
                   default: fprintf(stderr, "arrange_pointers: CVIP ERROR/invalid ordering of RGB pointers."); break;
                }
		switch(interleaved) {
		   case INTERPLANE: CVIPReadBytes(inputfile,buf1,width*height);
				    CVIPReadBytes(inputfile,buf2,width*height);
		                    CVIPReadBytes(inputfile,buf3,width*height);
				    break;
		   case INTERLINE:  for(i = 0; i < height; i++) {
				       CVIPReadBytes(inputfile,(buf1+i*width),width);
				       CVIPReadBytes(inputfile,(buf2+i*width),width);
		                       CVIPReadBytes(inputfile,(buf3+i*width),width);
				    }
				    break;
		   case INTERPIXEL: for(i = 0; i < width*height; i++) { 
				       *buf1++ = fgetc(inputfile);
				       *buf2++ = fgetc(inputfile);
				       *buf3++ = fgetc(inputfile);
				    }
				    break;
		   default: CVIPerror("invalid interleave scheme: must be INTERPLANE, INTERLINE or INTERPIXEL\n"); break;
                }
		break;
      default:  CVIPerror("improper number of data bands (1 or 3 only).\n"); break;
   }

return raw_Image;
}

