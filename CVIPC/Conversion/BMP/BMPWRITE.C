/****************************************************************************\
**  Title:        BMPWRITE                                                  **
**  Purpose:      Display the data in a BMP image file header.              **
**  Version:      1.0                                                       **
**  Date:         September 1991                                            **
**  Author:       James D. Murray, Anaheim, CA, USA                         **
**  C Compilers:  Borland C++ v2.0, Microsoft C v6.00a                      **
**                                                                          **
**  This module contains the following function:                            **
**                                                                          **
**      WriteBmpHeader - Write a BMP header to a FILE stream.               **
**                                                                          **
**  Portions Copyright (C) 1994 by James D. Murray and William vanRyper     **
\****************************************************************************/
#include <stdio.h>
#include "endianio.h"
#include "bmp.h"

/* External global variables */
VOID (*PutWord)(WORD, FILE *);
VOID (*PutDword)(DWORD, FILE *);

/*
**  Write a Windows or PM BMP header.
**
**  This function reads the information from a BMPHEADER structure
**  and writes it to a FILE stream in the form of a BMP header.
**
**  Returns: Nothing.
*/
VOID
WriteBmpHeader(BmpHead, FpBmp)
BMPHEADER *BmpHead;     /* Pointer to BMP header structure  */
FILE      *FpBmp;       /* BMP image file output FILE stream */
{
    register SHORT i;   /* Loop counter */
    WORD  NumColors;    /* Number of colors in color table */

    PutWord  = PutLittleWord;   /* Write using little-endian byte order */
    PutDword = PutLittleDword;  

    /* Write the bit map file header */
    PutWord(BmpHead->Header.Type,      FpBmp);
    PutDword(BmpHead->Header.FileSize, FpBmp);
    PutWord(BmpHead->Header.Reserved1, FpBmp);
    PutWord(BmpHead->Header.Reserved2, FpBmp);
    PutDword(BmpHead->Header.Offset,   FpBmp);

    /*
    ** Write the bit map information header.
    **
    ** The size if the information header indicates if the BMP file
    ** originated on an MS Windows or OS/2 Presentation Manager system.
    */
    if (BmpHead->PmInfo.Size)          /* OS/2 1.x */
    {
        PutWord(BmpHead->PmInfo.Size,     FpBmp);
        PutWord(BmpHead->PmInfo.Width,    FpBmp);
        PutWord(BmpHead->PmInfo.Height,   FpBmp);
        PutWord(BmpHead->PmInfo.Planes,   FpBmp);
        PutWord(BmpHead->PmInfo.BitCount, FpBmp);

        if (BmpHead->PmColorTable)
        {
            /* Determine number of entries in color table */
            NumColors = (WORD) (1U << (BmpHead->PmInfo.Planes *
              BmpHead->PmInfo.BitCount));

            /* Write the color table one color triple at a time */
            for (i = 0; i < NumColors; i++)
            {
                 PutByte(BmpHead->PmColorTable[i].rgbBlue,  FpBmp);
                 PutByte(BmpHead->PmColorTable[i].rgbGreen, FpBmp);
                 PutByte(BmpHead->PmColorTable[i].rgbRed,   FpBmp);
            }
        }
    }
    else                               /* Windows 3 */
    if (BmpHead->WinInfo.Size)
    {                              
        PutDword(BmpHead->WinInfo.Size,          FpBmp);
        PutDword(BmpHead->WinInfo.Width,         FpBmp);
        PutDword(BmpHead->WinInfo.Height,        FpBmp);
        PutWord(BmpHead->WinInfo.Planes,         FpBmp);
        PutWord(BmpHead->WinInfo.BitCount,       FpBmp);
        PutDword(BmpHead->WinInfo.Compression,   FpBmp);
        PutDword(BmpHead->WinInfo.SizeImage,     FpBmp);
        PutDword(BmpHead->WinInfo.XPelsPerMeter, FpBmp);
        PutDword(BmpHead->WinInfo.YPelsPerMeter, FpBmp);
        PutDword(BmpHead->WinInfo.ClrUsed,       FpBmp);
        PutDword(BmpHead->WinInfo.ClrImportant,  FpBmp);

        if (BmpHead->WinColorTable)
        {
            /* Determine number of entries in color table */
            if (BmpHead->WinInfo.ClrUsed)
                NumColors = BmpHead->WinInfo.ClrUsed;
            else
                NumColors = (WORD) (1U << (BmpHead->WinInfo.Planes *
                  BmpHead->WinInfo.BitCount));

            /* Write the color table one color quad at a time */
            for (i = 0; i < NumColors; i++)
            {
                PutByte(BmpHead->WinColorTable[i].rgbBlue,     FpBmp);
                PutByte(BmpHead->WinColorTable[i].rgbGreen,    FpBmp);
                PutByte(BmpHead->WinColorTable[i].rgbRed,      FpBmp);
                PutByte(BmpHead->WinColorTable[i].rgbReserved, FpBmp);
            }
        }
    }
    else                               /* OS/2 2.0 */
    if (BmpHead->Pm2Info.Size)
    {                              
        PutDword(BmpHead->Pm2Info.Size,          FpBmp);
        PutDword(BmpHead->Pm2Info.Width,         FpBmp);
        PutDword(BmpHead->Pm2Info.Height,        FpBmp);
        PutWord( BmpHead->Pm2Info.Planes,        FpBmp);
        PutWord( BmpHead->Pm2Info.BitCount,      FpBmp);
        PutDword(BmpHead->Pm2Info.Compression,   FpBmp);
        PutDword(BmpHead->Pm2Info.SizeImage,     FpBmp);
        PutDword(BmpHead->Pm2Info.XPelsPerMeter, FpBmp);
        PutDword(BmpHead->Pm2Info.YPelsPerMeter, FpBmp);
        PutDword(BmpHead->Pm2Info.ClrUsed,       FpBmp);
        PutDword(BmpHead->Pm2Info.ClrImportant,  FpBmp);
        PutWord( BmpHead->Pm2Info.Units,         FpBmp);
        PutWord( BmpHead->Pm2Info.Reserved,      FpBmp);
        PutWord( BmpHead->Pm2Info.Recording,     FpBmp);
        PutWord( BmpHead->Pm2Info.Rendering,     FpBmp);
        PutDword(BmpHead->Pm2Info.Size1,         FpBmp);
        PutDword(BmpHead->Pm2Info.Size2,         FpBmp);
        PutDword(BmpHead->Pm2Info.ColorEncoding, FpBmp);
        PutDword(BmpHead->Pm2Info.Identifier,    FpBmp);

        if (BmpHead->Pm2ColorTable)
        {
            /* Determine number of entries in color table */
            if (BmpHead->Pm2Info.ClrUsed)
                NumColors = BmpHead->Pm2Info.ClrUsed;
            else
                NumColors = (WORD) (1U << (BmpHead->Pm2Info.Planes *
                  BmpHead->Pm2Info.BitCount));

            /* Write the color table one color quad at a time */
            for (i = 0; i < NumColors; i++)
            {
                PutByte(BmpHead->Pm2ColorTable[i].rgbBlue,     FpBmp);
                PutByte(BmpHead->Pm2ColorTable[i].rgbGreen,    FpBmp);
                PutByte(BmpHead->Pm2ColorTable[i].rgbRed,      FpBmp);
                PutByte(BmpHead->Pm2ColorTable[i].rgbReserved, FpBmp);
            }
        }
    }
}

