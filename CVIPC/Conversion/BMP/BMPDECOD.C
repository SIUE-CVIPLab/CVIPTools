/****************************************************************************\
**  Title:        BMPDECODE                                                 **
**  Purpose:      Display the data in a BMP image file header.              **
**  Version:      1.0                                                       **
**  Date:         September 1991                                            **
**  Author:       James D. Murray, Anaheim, CA, USA                         **
**  C Compilers:  Borland C++ v2.0, Microsoft C v6.00a                      **
**                                                                          **
**  This module contains the following function:                            **
**                                                                          **
**  Portions Copyright (C) 1994 by James D. Murray and William vanRyper     **
\****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "endianio.h"
#include "bmp.h"


SHORT
BmpDecodeScanLine(DecodedBuffer, LineLength, BufferSize, Method, FpBmp)
BYTE *DecodedBuffer;    /* Pointer to buffer to hold decoded data         */
WORD  BufferSize;       /* Size of buffer to hold decoded data in bytes   */
WORD  LineLength;       /* The length of a scan line in pixels            */
DWORD Method;           /* Data encoding method used on scan line data    */
FILE *FpBmp;            /* FILE pointer to the open input BMP image file  */
{
    BYTE    runCount;       /* Number of pixels in the run  */
    BYTE    runValue;       /* Value of pixels in the run   */
    BYTE    Value;          /* Temporary pixel value holder */
    BYTE    tempValue;      /* Temporary pixel value holder */
    WORD    bufIndex;       /* The index of DecodedBuffer   */

    /* Check that a proper compression method has been specified */
    if (Method != COMPRESS_RLE4 && Method != COMPRESS_RLE8)
        return(-1);

    bufIndex = 0;         /* Initialize the buffer index  */
    
    /*
    ** Subtract 2 bytes from the size of the buffer to save room for
    ** the end-of-scan-line marker.  The buffer should have two more
    ** bytes than it need to hold the scan line, of course.
    */
    BufferSize -= 2;

    /* Main decoding loop */
    while (bufIndex <= BufferSize)
    {
        runCount = GetByte(FpBmp);  /* Number of pixels in the run */
		if (ferror(FpBmp))
		{
			fputs("BMPHEAD: Error reading file!\n", stderr);
			return bufIndex;
		}

        runValue = GetByte(FpBmp);  /* Value of pixels in the run  */
		if (ferror(FpBmp))
		{
			fputs("BMPHEAD: Error reading file!\n", stderr);
			return bufIndex;
		}

		tempValue = runValue;

        switch(runCount)
        {
            case 0:        /* Literal Run or Escape Code */
                switch(runValue)
                {
                    case 0:             /* End of Scan Line Escape Code */
                        puts("End of scan line Code");
                    case 1:             /* End of Bitmap Escape Code */
                        puts("End of bit map Code");
                        return(bufIndex);
                    case 2:             /* Delta Escape Code (not supported) */
                        fputs("Delta Escape Codes not supported!", stderr);
                        return(-1);
                    default:            /* Literal Run */
                        /* Check for a possible buffer overflow */
                        if (bufIndex + runValue > BufferSize)
                            return(-2);

                        if (Method == COMPRESS_RLE8)
                        {
                            while (runValue--)
                                DecodedBuffer[bufIndex++] = GetByte(FpBmp);
							if (tempValue % 2) { /* padding? */
								GetByte(FpBmp);  /* get rid of the surplus byte*/
							}
                        }
                        else
                        if (Method == COMPRESS_RLE4)
                        {
                            /*
                            ** Alternate writing the most-significant and
                            ** Least-significant nibble to the buffer.  The
                            ** odd-length literal runs are a bit tricky.
                            */
                            while (runValue--)
                            {
                                Value = GetByte(FpBmp);
                                DecodedBuffer[bufIndex++] = (MSN(Value));
                                if (runValue--)
                                    DecodedBuffer[bufIndex++] |= (LSN(Value));
                            }
							if ((tempValue % 4) == 1 || (tempValue % 4) == 2) { /* padding? */
								GetByte(FpBmp);  /* get rid of the surplus byte*/
							}
                        }
                }
                break;
            default:    /* Encoded Run */
                if (Method == COMPRESS_RLE4)            /* Write a 4-bit value */
                {
                    /* Check for a possible buffer overflow */
                    if (bufIndex + (runCount / 2) > BufferSize)
                        return(-2);

                    /*
                    ** Alternate writing the most-significant and
                    ** Least-significant nibble to the buffer.
                    */
                    while (runCount--)
                    {
                        DecodedBuffer[bufIndex++] = LSN(runValue);
                    }
                }
                else    /* Write an 8-bit value */
                {
printf("bufIndex %d  runCount %d  BufferSize %d\n", bufIndex, runCount, BufferSize);
                    /* Check for a possible buffer overflow */
                    if (bufIndex + runCount > BufferSize)
                       return(bufIndex);

                    while (runCount--)
                        DecodedBuffer[bufIndex++] = runValue;
                }
                break;
        }
    }
    fputs("BMPDECOD: No End of Scan line code!\n", stderr);
    return(-3);     /* No End-of-Scan Line or End-of-Bitmap code! */
}
