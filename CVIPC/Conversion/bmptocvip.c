/***************************************************************************
======================================================================
Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
======================================================================
                                                                      
             File Name: bmptocvip.c
           Description: contains a routine to load a BMP
			file into a CVIP Image structure.
         Related Files: CVIPimage.h, CVIPbin.h, Makefile
   Initial Coding Date: 09/09/2002
           Portability: Standard (ANSI) C
             Credit(s): Huashi Ding, E.E. Dept. SIUE

  Global Function List: bmptocvip
			
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

#include	"ppm.h" 
#define NO_STD_INCLUDES
#include        "CVIPimage.h"
#include        "CVIPxel.h"
#include "endianio.h"
#include "bmp.h"

#define	ReadOK(file,buffer,len)	(fread(buffer, len, 1, file) != 0)

Image *bmptocvip(char *name, FILE *in, int imageNumber, int showmessage)
{
    register int i, j, k;             /* Loop counters                     */
    FILE         *fpBmpIn = in;     /* BMP image file input FILE stream  */
    BYTE         *buffer;           /* Buffer to hold scan line data     */
    WORD          bufSize;          /* Size of the scan line buffer      */
    SHORT         byteCount;        /* Number of bytes in a buffer              */
    BMPHEADER     bmpHead;          /* BMP image file header structure   */
    WORD  NumColors;        /* Number of colors in color table */

	int isColor;
	BYTE		  temp;				/* Temporary byte to store pixels */
	int		xpos = 0, ypos;
	int		width, height, bitsPerPixel;

	Image           *bmp_Image;
	char            *prog_name[1] = {"bmptocvip"};
		
	byte **red_plane, **green_plane, **blue_plane;

    pm_init(&showmessage, prog_name);
	pm_message("opening Bitmap Image Format(BMP) file - %s.",name);

	bmpHead.Pm2ColorTable = NULL;
	bmpHead.PmColorTable  = NULL;
	bmpHead.WinColorTable = NULL;

    /* Read the BMP image file header information */
    ReadBmpHeader(&bmpHead, fpBmpIn);
    if (bmpHead.PmInfo.Size)         /* OS/2 1.x bitmap */
    {
        width			= bmpHead.PmInfo.Width;
        height			= bmpHead.PmInfo.Height;
        bitsPerPixel	= bmpHead.PmInfo.BitCount;
	} else if (bmpHead.WinInfo.Size)           /* Windows 3.0 bitmap */
	{
        width			= bmpHead.WinInfo.Width;
        height			= bmpHead.WinInfo.Height;
        bitsPerPixel	= bmpHead.WinInfo.BitCount;
	} else if (bmpHead.Pm2Info.Size)         /* OS/2 2.0 bitmap */
    {
        width			= bmpHead.Pm2Info.Width;
        height			= bmpHead.Pm2Info.Height;
        bitsPerPixel	= bmpHead.Pm2Info.BitCount;
	} else
    {
        fputs("BMPHEAD: No BMP information read!\n", stderr);
		return NULL;
	}

    /* Check for FILE stream error */
    if (ferror(fpBmpIn))
    {
        fputs("BMPHEAD: Error reading header information!\n", stderr);
        return NULL;
    }

    /* Check the Identification Type */
    if (bmpHead.Header.Type != BMP_ID)
    {
        fputs("Not a BMP-format file!\n", stderr);
        return NULL;
    }

    /* Seek to the bitmap data (we should already be at the data) */
    fseek(fpBmpIn, bmpHead.Header.Offset, SEEK_SET);

    if (bmpHead.WinInfo.Size)   /* Windows 3.x BMP file */
    {
        /* Determine number of entries in color table */
        if (bmpHead.WinInfo.ClrUsed)
            NumColors = bmpHead.WinInfo.ClrUsed;
        else
            NumColors = (WORD) (1U << (bmpHead.WinInfo.Planes *
              bmpHead.WinInfo.BitCount));

		isColor = 0;
        /* Read in the color table one color quad at a time */
        for (i = 0; i < NumColors; i++)
        {
            if (bmpHead.WinColorTable[i].rgbBlue != bmpHead.WinColorTable[i].rgbGreen ||
				bmpHead.WinColorTable[i].rgbGreen!= bmpHead.WinColorTable[i].rgbRed ||
				bmpHead.WinColorTable[i].rgbRed  != bmpHead.WinColorTable[i].rgbBlue)
			{
				isColor = 1;
				break;
			}
			
        }

		if (0 == isColor)
		{
			free (bmpHead.WinColorTable);
			bmpHead.WinColorTable = NULL;
		}

		if ((bmpHead.WinInfo.BitCount == 24 || NULL != bmpHead.WinColorTable)) {
			if ((bmp_Image = image_allocate(BMP, RGB, 3, height, width, CVIP_BYTE, REAL)) == NULL)
			{
					pm_error("couldn't alloc Image structure" );
					return NULL;
			}

			red_plane = (byte **) bmp_Image->image_ptr[0]->rptr;
			green_plane = (byte **) bmp_Image->image_ptr[1]->rptr;
			blue_plane = (byte **) bmp_Image->image_ptr[2]->rptr;	
		} else {
			if ((bmp_Image = image_allocate(BMP, GRAY_SCALE, 1, height, width, CVIP_BYTE, REAL)) == NULL)
			{
					pm_error("couldn't alloc Image structure" );
					return NULL;
			}

			red_plane = (byte **) bmp_Image->image_ptr[0]->rptr;
		}

		ypos = bmpHead.WinInfo.Height - 1;

        /* Calculate the size of the scan line buffer in bytes */
        bufSize = (bmpHead.WinInfo.Width * ((bmpHead.WinInfo.BitCount + 7) >> 3) + 2);

        /* Allocate scan line buffer memory */
        if ((buffer = (BYTE *) calloc(bufSize, sizeof(BYTE))) == (BYTE *) NULL)
        {
            fputs("BMPCODE: Error allocating memory.\n", stderr);
            return NULL;
        }

        /* If the BMP file contains compressed image data, then decode it */
        if ((bmpHead.WinInfo.Compression == COMPRESS_RLE4 && bmpHead.WinInfo.BitCount == 4) ||
            (bmpHead.WinInfo.Compression == COMPRESS_RLE8 && bmpHead.WinInfo.BitCount == 8))
        {
            /* Check that we are a the image data offset specified in the header before 
reading */
            if (ftell(fpBmpIn) != bmpHead.Header.Offset)
                printf("WARNING: At %ld, should be %ld\n", 
                    ftell(fpBmpIn), bmpHead.Header.Offset);

            for (i = 0; i < bmpHead.WinInfo.Height; i++)
            {
				xpos = 0;
				for (j = 0; j < bufSize; j++) {
					buffer[j] = 0; //reset scan line
				}
                /* Decode a scan line */
                if ((byteCount =
                    BmpDecodeScanLine(buffer, bmpHead.WinInfo.Width,
                      bufSize, bmpHead.WinInfo.Compression, fpBmpIn)) < 0)
                {
                    fputs("BMPCODE: Error decoding scan line.\n", stderr);
		            return NULL;
                }

                /* Write the decoded scan line to the output image */
				if (8 == bmpHead.WinInfo.BitCount) 
				{
					if (NULL != bmpHead.WinColorTable) {
						for (j = 0; j < bmpHead.WinInfo.Width; j++) {
							temp = buffer[j];
							red_plane[ypos][xpos]   = bmpHead.WinColorTable[temp].rgbRed;
							green_plane[ypos][xpos] = bmpHead.WinColorTable[temp].rgbGreen;
							blue_plane[ypos][xpos]  = bmpHead.WinColorTable[temp].rgbBlue; 
							xpos++;
						}
					} else {
						for (j = 0; j < bmpHead.WinInfo.Width; j++) {
							red_plane[ypos][xpos]   = buffer[j];
							xpos++;
						}
					}
				} else // (4 == bmpHead.WinInfo.BitCount)
				{
					if (NULL != bmpHead.WinColorTable) {
						for (j = 0; j < bmpHead.WinInfo.Width; j++) {
							temp = buffer[j];
							red_plane[ypos][xpos]   = bmpHead.WinColorTable[temp].rgbRed;
							green_plane[ypos][xpos] = bmpHead.WinColorTable[temp].rgbGreen;
							blue_plane[ypos][xpos]  = bmpHead.WinColorTable[temp].rgbBlue; 
							xpos++;
						}
					} else {
						for (j = 0; j < bmpHead.WinInfo.Width; j++) {
							red_plane[ypos][xpos]   = buffer[j];
							xpos++;
						}
					}
				} 
				
				ypos--;
            }
        }
        else    /* The BMP file contains uncompressed image data */    
        if (bmpHead.WinInfo.Compression == COMPRESS_RGB &&
           (bmpHead.WinInfo.BitCount == 1 ||
		    bmpHead.WinInfo.BitCount == 4 || 
		    bmpHead.WinInfo.BitCount == 8 || 
			bmpHead.WinInfo.BitCount == 24))
        {
            /* Check that we are a the image data offset specified in the header before 
reading */
            if (ftell(fpBmpIn) != bmpHead.Header.Offset)
                printf("WARNING: At %ld, should be %ld\n", 
                    ftell(fpBmpIn), bmpHead.Header.Offset);

            for (i = 0; i < bmpHead.WinInfo.Height; i++)
            {
				xpos = 0;
                /* Write the Encoded scan line to the output image*/
				if (8 == bmpHead.WinInfo.BitCount) 
				{
					for (j = 0; j < bmpHead.WinInfo.Width; j++)
						buffer[j] = GetByte(fpBmpIn);

					j = 4 - (j % 4);
					if (4 != j) {
						for (; j > 0; j--) {
							GetByte(fpBmpIn); //get rid of padding bytes
						}
					}
					if (NULL != bmpHead.WinColorTable) {
						for (j = 0; j < bmpHead.WinInfo.Width; j++) {
							temp = buffer[j];
							red_plane[ypos][xpos]   = bmpHead.WinColorTable[temp].rgbRed;
							green_plane[ypos][xpos] = bmpHead.WinColorTable[temp].rgbGreen;
							blue_plane[ypos][xpos]  = bmpHead.WinColorTable[temp].rgbBlue; 
							xpos++;
						}
					} else {
						for (j = 0; j < bmpHead.WinInfo.Width; j++) {
							red_plane[ypos][xpos]   = buffer[j];
							xpos++;
						}
					}
				} else if (24 == bmpHead.WinInfo.BitCount)
				{
					for (j = 0; j < bmpHead.WinInfo.Width * 3; j++)
						buffer[j] = GetByte(fpBmpIn);
					
					j = 4 - (j % 4);
					if (4 != j) {
						for (; j > 0; j--) {
							GetByte(fpBmpIn); //get rid of padding bytes
						}
					}

					for (j = 0; j < bmpHead.WinInfo.Width; j++) {
						red_plane[ypos][xpos]   = buffer[j * 3 + 2];
						green_plane[ypos][xpos] = buffer[j * 3 + 1];
						blue_plane[ypos][xpos]  = buffer[j * 3]; 
						xpos++;
					}
				} else if (4 == bmpHead.WinInfo.BitCount)
				{
					for (j = 0; j < ((bmpHead.WinInfo.Width + 1) / 2); j++)
						buffer[j] = GetByte(fpBmpIn);
					j = 4 - (j % 4);
					if (4 != j) {
						for (; j > 0; j--) {
							GetByte(fpBmpIn); //get rid of padding bytes
						}
					}
					for (j = 0; j < ((bmpHead.WinInfo.Width + 1) / 2); j++) {
						if (NULL != bmpHead.WinColorTable) {
							temp = 0x0f & (buffer[j] >> 4);
							red_plane[ypos][xpos]   = bmpHead.WinColorTable[temp].rgbRed;
							green_plane[ypos][xpos] = bmpHead.WinColorTable[temp].rgbGreen;
							blue_plane[ypos][xpos]  = bmpHead.WinColorTable[temp].rgbBlue; 
							xpos++;
							if (xpos >= bmpHead.WinInfo.Width) break;
							temp = 0x0f & buffer[j];
							red_plane[ypos][xpos]   = bmpHead.WinColorTable[temp].rgbRed;
							green_plane[ypos][xpos] = bmpHead.WinColorTable[temp].rgbGreen;
							blue_plane[ypos][xpos]  = bmpHead.WinColorTable[temp].rgbBlue; 
							xpos++;
							if (xpos >= bmpHead.WinInfo.Width) break;
						} else {
							temp = 0x0f & (buffer[j] >> 4);
							red_plane[ypos][xpos]   = bmpHead.WinColorTable[temp].rgbRed;
							xpos++;
							if (xpos >= bmpHead.WinInfo.Width) break;
							temp = 0x0f & buffer[j];
							red_plane[ypos][xpos]   = bmpHead.WinColorTable[temp].rgbRed;
							xpos++;
							if (xpos >= bmpHead.WinInfo.Width) break;
						}
					}
				} else if (1 == bmpHead.WinInfo.BitCount)
				{
					for (j = 0; j < ((bmpHead.WinInfo.Width + 7) / 8); j++)
						buffer[j] = GetByte(fpBmpIn);

					j = 4 - (j % 4);
					if (4 != j) {
						for (; j > 0; j--) {
							GetByte(fpBmpIn); //get rid of padding bytes
						}
					}
					for (j = 0; j < ((bmpHead.WinInfo.Width + 7)  / 8); j++) {
						temp = buffer[j];
						for (k = 0; k < 8; k++) {
							if (0x01 == (0x01 & (temp >> (7 - k)))) {
								if (NULL != bmpHead.WinColorTable) {
									blue_plane[ypos][xpos]  = 255; 
									green_plane[ypos][xpos] = 255;
								}
								red_plane[ypos][xpos]   = 255;
							} else {
								if (NULL != bmpHead.WinColorTable) {
									blue_plane[ypos][xpos]  = 0; 
									green_plane[ypos][xpos] = 0;
								}
								red_plane[ypos][xpos]   = 0;
							}
							xpos++;
							if (xpos >= bmpHead.WinInfo.Width) break;
						}
						if (xpos >= bmpHead.WinInfo.Width) break;
					}
				}
				ypos--;
            }
        }

		free(buffer);
    }                                       
    else
    if (bmpHead.PmInfo.Size)    /* OS/2 1.x BMP file */
    {
		bmp_Image = NULL;
    }
    else
    if (bmpHead.Pm2Info.Size)    /* OS/2 2.0 BMP file */
    {
		bmp_Image = NULL;
    }

	if (NULL == bmpHead.Pm2ColorTable) {
		free (bmpHead.Pm2ColorTable);
		bmpHead.Pm2ColorTable = NULL;
	}
	if (NULL == bmpHead.PmColorTable) {
		free (bmpHead.PmColorTable);
		bmpHead.PmColorTable = NULL;
	}
	if (NULL == bmpHead.WinColorTable) {
		free (bmpHead.WinColorTable);
		bmpHead.WinColorTable = NULL;
	}

	return bmp_Image;
}

