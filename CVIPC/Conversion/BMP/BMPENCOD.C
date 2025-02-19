/****************************************************************************\
**  Title:        BMPENCODE                                                 **
**  Purpose:      Display the data in a BMP image file header.              **
**  Version:      1.0                                                       **
**  Date:         September 1991                                            **
**  Author:       James D. Murray, Anaheim, CA, USA                         **
**  C Compilers:  Borland C++ v2.0, Microsoft C v6.00a                      **
**                                                                          **
**  This module contains the following function:                            **
**                                                                          **
**      BmpEncodeScanLine -   **
**                                                                          **
**  Portions Copyright (C) 1994 by James D. Murray and William vanRyper     **
\****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "endianio.h"
#include "bmp.h"

/*
Read encoded data from a FILE stream and write to a buffer.

Pixels are either 4-bits or 8-bits in size.  The Method parameter
indcates the size with a value of COMPRESS_RLE4 or COMPRESS_RLE8.

Note that this code only writes absolute runs of pixels that are the same
value.  Literal runs may just as easily represent a line of pixels with
different values.

For 4-bit pixels the MSN (Most Significant Nibble) is the first pixel
value and the LSN (Least Significant Nibble) is the second pixel value.
This particular algorithm encodes 4-bit per pixel data two nibbles at a time.
In other words, if you had the raw run "11 11 15" only first four nibbles
would be encoded in the run.  The fifth nibble would be treated part of
of the next run.  Not the most efficient scheme, but it
simplifies the algorithm by not needing to tear apart bytes into sparate
nibble values and add padding for odd-length pixel runs.  So there.

**  Method may have one of the following values:
**
**      0 - Unencoded
**      1 - Four bits per pixel
**      2 - Eight bits per pixel
**
**
*/
SHORT
BmpEncodeScanLine(EncodedBuffer, BufferSize, LineLength, Method, FpBmp)
BYTE  *EncodedBuffer;    /* Pointer to buffer to hold encodeded scan line   */
WORD   BufferSize;       /* Size of buffer holding unencoded data           */
WORD   LineLength;       /* The length of a scan line in pixels             */
DWORD  Method;           /* Encoding method to use                          */
FILE  *FpBmp;            /* FILE pointer to the open input BMP image file   */
{
    WORD    runCount;       /* The number of pixels in the current run      */
    WORD    pixelCount;     /* The number of pixels read from the scan line */
    SHORT   bufIndex;       /* The index of DecodedBuffer                   */
    BYTE    pixelValue1;    /* Pixel value read from the scan line (4-byte max) */
    BYTE    pixelValue2;    /* Pixel value read from the scan line          */

    /* Check that a proper compression method has been specified */
    if (Method != COMPRESS_RLE4 && Method != COMPRESS_RLE8)
        return(-1);

    bufIndex   = 0;
    runCount   = (Method == COMPRESS_RLE4 ? 2 : 1);
    pixelCount = (Method == COMPRESS_RLE4 ? 2 : 1);

    /* Read in first pixel value */
    pixelValue1 = GetByte(FpBmp);

    /* Main encoding loop */
    for (;;)
    {
        /* Read in another pixel value */
        pixelValue2 = GetByte(FpBmp);

        /* Count number of pixels read so far */
        pixelCount += (Method == COMPRESS_RLE4 ? 2 : 1);

        /* If the pixels are the same then start or continue a run */
        if (pixelValue1 == pixelValue2)   /* Compare pixels */
        {
            /* Advance the run count */
            runCount += (Method == COMPRESS_RLE4 ? 2 : 1);

            if (runCount < 256)     /* Maximum run-length is 256 pixels     */
            {
                if (pixelCount < LineLength)  /* Don't run past end of scan line */
                    continue;       /* Continue reading the run             */
            }
        }

        /*
        ** If we have gotten this far then we have either come to the end of
        ** a pixel run, have reached the maximum number of pixels encodable
        ** in a run, or read to the end of the scan line.  Now encode the
        ** current run.
        */

        /*
        ** Literal runs must have a runCount greater than 2 or the
        ** literal run indicator will be confused with an escape code.
        ** This scheme will also only encode even-length runs as literal
        ** runs.  This frees us from keeping track of left over nibbles
        ** from odd-length runs.
        */
#if 0
		if (runCount > 2 && runCount < 8 && !(runCount % 2))    /* Write a Literal Run 
*/
#endif
        if (runCount < 0)
		{
            /* Make sure writing this next run will not overflow the buffer */
            if (bufIndex + runCount >= BufferSize - 2)
                return(-1);

            EncodedBuffer[bufIndex++] = 0;          /* Literal Run indicator  */
            EncodedBuffer[bufIndex++] = runCount;   /* Number of pixels in run */

            if (Method == COMPRESS_RLE4)
                runCount /= 2;

            /* Write the pixel data run */
            while (runCount--)
                EncodedBuffer[bufIndex++] = pixelValue1;
        }
        else                /* Write an Encoded Run */
        {
printf("runCount: %d  value %d\n", runCount, pixelValue1);
            EncodedBuffer[bufIndex++] = runCount;    /* Number of pixels in run */
            EncodedBuffer[bufIndex++] = pixelValue1; /* Value of pixels in run */
        }

        /* If we've encoded the entire line then break out of the loop */
        if (pixelCount == LineLength)
            break;

        /* Start a new pixel run count  */
        runCount = (Method == COMPRESS_RLE4 ? 2 : 1);

        /* Store next pixel value run to match */
        pixelValue1 = pixelValue2;
    }
    /* Write an End of Scan Line Escape Code */
    EncodedBuffer[bufIndex++] = 0;          
    EncodedBuffer[bufIndex++] = 0;

    return(bufIndex);
}

