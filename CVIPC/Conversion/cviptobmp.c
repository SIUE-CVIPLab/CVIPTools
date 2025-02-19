/***************************************************************************
======================================================================
Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
======================================================================
                                                                      
             File Name: cviptobmp.c
           Description: contains a routine to write a CVIPtools Image
			structure to a BMP data file.
			a CVIP Image structure.
         Related Files: CVIPimage.h, CVIPbin.h, Makefile
   Initial Coding Date: 09/10/2002
           Portability: Standard (ANSI) C
             Credit(s): Huashi Ding, E.E. Dept. SIUE

  Global Function List: cviptobmp
			
****************************************************************************

** Copyright (C) 1991, 1992, 1993 SIUE - by Scott Umbaugh, Greg Hance.
**
** Permission to use, copy, modify, and distribute this software and its
** documentation for any purpose and without fee is hereby granted, provided
** that the above copyright notice appear in all copies and that both that
** copyright notice and this permission notice appear in supporting
** documentation.  This software is provided "as is" without express or
** implied warranty.

*****************************************************************************/


#include <math.h>
#include <stdio.h>
#include "CVIPimage.h"
#include "CVIPconutils.h"
#include "endianio.h"
#include "bmp.h"

/****************************************************************
                  Name: cviptobmp
         Expanded Name: CVIPtools Image format to BMP format
            Parameters:   <raw_Image> - pointer to Image structure
                          <raw_image> - name of output file
                         <outputfile> - file pointer to open image file
			    <verbose> - wanna know what I do?
               Returns: nada.
           Description: writes the contents of a CVIPtools Image structure in
			raw data format to the file <raw_image>.
           Diagnostics: prints out info. pertaining to the specifications
			of the image being written if verbose is CVIP_YES.
             Credit(s): Huashi Ding
			
			
****************************************************************/

void cviptobmp(Image *raw_Image, char *raw_image, FILE *outputfile, CVIP_BOOLEAN verbose)
{
   char function_name[] = {"cviptobmp"};
   long bytes_in_image, bytes_in_palette;
   int  width, height, data_bands;
   byte *r_ptr, *g_ptr, *b_ptr;
   int	i, j, padding;
   WORD  NumColors;        /* Number of colors in color table */

   BMPHEADER    bmpHead;          /* BMP image file header structure   */
   
   CVIPinit(function_name, verbose);

   if (getDataType_Image(raw_Image) != CVIP_BYTE)
     raw_Image = (Image *)remap_Image(raw_Image, CVIP_BYTE, 0, 255);

   data_bands  = raw_Image->bands;
   height = raw_Image->image_ptr[0]->rows;
   width  = raw_Image->image_ptr[0]->cols;
   
   bytes_in_image = height*width*data_bands;

   bmpHead.WinColorTable = NULL;

   if (data_bands == 3) {
	   bytes_in_palette = 0;
   } else {
		NumColors = (WORD) (256);
	    bytes_in_palette = NumColors * sizeof(WINRGBQUAD);

		if (NumColors > 0) {
			bmpHead.WinColorTable = calloc(NumColors, sizeof(WINRGBQUAD));
			for (i = 0; i < NumColors; i++)
			{
				bmpHead.WinColorTable[i].rgbBlue =i;
				bmpHead.WinColorTable[i].rgbGreen=i;
				bmpHead.WinColorTable[i].rgbRed  =i;
			}
		}

   }

   bmpHead.Header.Type		= 0x4d42;
   bmpHead.Header.FileSize	= 14 + sizeof(WININFOHEAD) + bytes_in_image + bytes_in_palette;
   bmpHead.Header.Reserved1 = 0;
   bmpHead.Header.Reserved2 = 0;
   bmpHead.Header.Offset	= 14 + sizeof(WININFOHEAD) + bytes_in_palette;

   bmpHead.Pm2Info.Size			= 0;
   bmpHead.PmInfo.Size			= 0;
   
   bmpHead.WinInfo.Size			= sizeof(WININFOHEAD);
   bmpHead.WinInfo.Width		= width;       
   bmpHead.WinInfo.Height		= height;      
   bmpHead.WinInfo.Planes		= 1;      
   bmpHead.WinInfo.BitCount		= 8 * data_bands;    
   bmpHead.WinInfo.Compression	= 0; 
   bmpHead.WinInfo.SizeImage	= 0;   
   bmpHead.WinInfo.XPelsPerMeter= 2834;
   bmpHead.WinInfo.YPelsPerMeter= 2834;
   bmpHead.WinInfo.ClrUsed		= 0;     
   bmpHead.WinInfo.ClrImportant	= 0;


   WriteBmpHeader(&bmpHead, outputfile);

	switch(data_bands) {

	case 1:	
			padding = width % 4;
			padding = (4 - padding) % 4;

			CVIPmessage("writing %dx%d raw bytes of image data to file - %s.",width,height,raw_image);
			CVIPmessage("8 bits per sample. - GRAYSCALE");
			CVIPmessage("1 sample per pixel.\n");

			for(i = height - 1; i >= 0; i--) { 
				r_ptr = *((byte **)raw_Image->image_ptr[0]->rptr) + (i * width);
				for (j = 0; j < width; j++) {
				   PutByte(*r_ptr++, outputfile);
				}
				for (j = 0; j < padding; j++) {
				   PutByte(0, outputfile);
				}
			}
			break;
	case 3: 
			padding = (3*width) % 4;
			padding = (4 - padding) % 4;
			CVIPmessage("writing %dx%dx%d raw bytes of image data to file - %s.",width,height,data_bands,raw_image);
			CVIPmessage("8 bits per sample.");
			CVIPmessage("3 samples per pixel.\n");
			r_ptr = (byte *) *((byte **)raw_Image->image_ptr[0]->rptr);
			g_ptr = (byte *) *((byte **)raw_Image->image_ptr[1]->rptr);
			b_ptr = (byte *) *((byte **)raw_Image->image_ptr[2]->rptr);

			for(i = height - 1; i >= 0; i--) { 
				r_ptr = *((byte **)raw_Image->image_ptr[0]->rptr) + (i * width);
				g_ptr = *((byte **)raw_Image->image_ptr[1]->rptr) + (i * width);
				b_ptr = *((byte **)raw_Image->image_ptr[2]->rptr) + (i * width);
				for (j = 0; j < width; j++) {
				   PutByte(*b_ptr++, outputfile);
				   PutByte(*g_ptr++, outputfile);
				   PutByte(*r_ptr++, outputfile);
				}
				for (j = 0; j < padding; j++) {
				   PutByte(0, outputfile);
				}
			}
			break;
	}

	if (NULL != bmpHead.WinColorTable) 
	{
		free (bmpHead.WinColorTable);
		bmpHead.WinColorTable = NULL;
	}
}

