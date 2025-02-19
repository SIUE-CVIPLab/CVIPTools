/***************************************************************************
======================================================================
Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
======================================================================
                                                                      
             File Name: cviptobin.c
           Description: contains a routine to write a CVIPtools Image
			structure to a raw data file.
			a CVIP Image structure.
         Related Files: CVIPimage.h, CVIPbin.h, Makefile
   Initial Coding Date: 1/24/93
           Portability: Standard (ANSI) C
             Credit(s): Gregory Hance, E.E. Dept. SIUE

  Global Function List: cviptobin
			
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

$Log: cviptobin.c,v $
Revision 1.4  1997/03/08 17:00:15  yawei
Swaped CVIP_YES and CVIP_NO

Revision 1.3  1997/03/08 00:43:00  yawei
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

Revision 1.2  1997/01/15 17:07:12  yawei
Global Change:  IMAGE ==> Image

 * Revision 1.1  1993/05/31  07:10:11  hanceg
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
                  Name: cviptobin
         Expanded Name: CVIPtools Image format to Raw (Binary) format
            Parameters:   <raw_Image> - pointer to Image structure
                          <raw_image> - name of output file
                         <outputfile> - file pointer to open image file
			<color_order> - color ordering. one of...
				      ORD_RGB, ORD_RBG, ORD_GRB, ORD_GBR, 
				      ORD_BRG, ORD_BGR
			<interleaved> - interleave scheme. one of...
				      INTERPLANE, INTERLINE, INTERPIXEL
			    <verbose> - wanna know what I do?
               Returns: nada.
           Description: writes the contents of a CVIPtools Image structure in
			raw data format to the file <raw_image>.
           Diagnostics: prints out info. pertaining to the specifications
			of the image being written if verbose is CVIP_YES.
             Credit(s): Greg Hance
			
			
****************************************************************/

void cviptobin(Image *raw_Image, char *raw_image, FILE *outputfile, COLOR_ORDER color_order, INTERLEAVE_SCHEME interleaved, CVIP_BOOLEAN verbose)
{
   char function_name[] = {"cviptobin"};
   char *color[6] = {"RGB","RBG","GRB", "GBR" ,"BRG", "BGR"};
   char *scheme[3] = {"INTERPLANE", "INTERLINE", "INTERPIXEL"};
   int i, width, height, data_bands;
   long bytes_in_image;
   byte *r_ptr, *g_ptr, *b_ptr;
   byte *buf1, *buf2, *buf3; 
   
   CVIPinit(function_name, verbose);
   
   data_bands  = raw_Image->bands;
   height = raw_Image->image_ptr[0]->rows;
   width  = raw_Image->image_ptr[0]->cols;
   
   bytes_in_image = height*width*data_bands;
                    
   switch(data_bands) {
      
      case 1:	CVIPmessage("writing %dx%d raw bytes of image data to file - %s.",width,height,raw_image);
		CVIPmessage("8 bits per sample. - GRAYSCALE");
		CVIPmessage("1 sample per pixel.\n");
		CVIPWriteBytes(outputfile,*((byte **)raw_Image->image_ptr[0]->rptr),width*height);
		break;
      case 3:   CVIPmessage("writing %dx%dx%d raw bytes of image data to file - %s.",width,height,data_bands,raw_image);
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
		   case INTERPLANE: CVIPWriteBytes(outputfile,buf1,width*height);
				    CVIPWriteBytes(outputfile,buf2,width*height);
		                    CVIPWriteBytes(outputfile,buf3,width*height);
				    break;
		   case INTERLINE:  for(i = 0; i < height; i++) {
				       CVIPWriteBytes(outputfile,(buf1+i*width),width);
				       CVIPWriteBytes(outputfile,(buf2+i*width),width);
		                       CVIPWriteBytes(outputfile,(buf3+i*width),width);
				    }
				    break;
		   case INTERPIXEL: for(i = 0; i < width*height; i++) { 
				       fputc(*buf1++,outputfile);
				       fputc(*buf2++,outputfile);
				       fputc(*buf3++,outputfile);
				    }
				    break;
		   default: CVIPerror("invalid interleave scheme: must be INTERPLANE, INTERLINE or INTERPIXEL\n"); break;
                }
		break;
      default:  CVIPerror("improper number of data bands (1 or 3 only).\n"); break;
   }
		
}

