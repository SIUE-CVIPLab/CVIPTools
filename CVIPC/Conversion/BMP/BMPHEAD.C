/****************************************************************************\
**  Title:        BMPHEAD                                                   **
**  Purpose:      Display the data in a BMP image file header.              **
**  Version:      1.0                                                       **
**  Date:         September 1991                                            **
**  Author:       James D. Murray, Anaheim, CA, USA                         **
**  C Compilers:  Borland C++ v2.0, Microsoft C v6.00a                      **
**                                                                          **
**  BMPHEAD displays all real information contained within the              **
**  header of a BMP image file including the array of color map             **
**  values.                                                                 **
**                                                                          **
**  Portions Copyright (C) 1994 by James D. Murray and William vanRyper     **
\****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "endianio.h"
#include "bmp.h"


int
main(argc, argv)
int argc;
char *argv[];
{
    register WORD i;                    /* Loop Counter */
    BMPHEADER  bmpHead;
    WORD       NumberColorTableEntries;
    CHAR       BmpFileName[80];         /* Holder for the BMP image file name */
    FILE      *fpBmpIn;                 /* File pointer to the BMP image file */

    puts("BMPHEAD - Display the header info within a BMP image file (v1.00)\n");

    /* Check for proper number of command line arguments */
    if (argc < 2)
    {
        fputs("Usage: BMPHEAD filename.bmp\n\n", stderr);
        exit(-1);
    }

    /* Add the .bmp extension to the file name if no extension exists */
    strcpy(BmpFileName, argv[1]);
    if (!strrchr(argv[1], '.'))
        strcat(BmpFileName, ".bmp");

    /* Open the BMP image file */
    if ((fpBmpIn = fopen(BmpFileName, "rb")) == NULL)
    {
        fprintf(stderr, "BMPHEAD: Cannot open file %s\n", BmpFileName);
        exit(-2);
    }

    /* Read the BMP image file header information */
    ReadBmpHeader(&bmpHead, fpBmpIn);

    /* Check for FILE stream error */
    if (ferror(fpBmpIn))
    {
        fputs("BMPHEAD: Error reading header information!\n", stderr);
        exit(-4);
    }

    /* Check the Identification Type */
    if (bmpHead.Header.Type != BMP_ID)
    {
        fprintf(stderr, "BMPHEAD: %s is not a BMP-format file!\n",
          BmpFileName);
        exit(-5);
    }

    /*
    ** Display the BMP file information.
    */
    printf("            File Type: %x\n",    bmpHead.Header.Type);
    printf("            File Size: %ld\n",   bmpHead.Header.FileSize);
    printf("            Reserved1: %d\n",    bmpHead.Header.Reserved1);
    printf("            Reserved2: %d\n",    bmpHead.Header.Reserved2);
    printf("    Image Data Offset: %ld\n\n", bmpHead.Header.Offset);

    if (bmpHead.PmInfo.Size)         /* OS/2 1.x bitmap */
    {
        printf("   Size of Header: %ld", bmpHead.PmInfo.Size);
        puts("\t(OS/2 1.x Bitmap)");

        printf("   Width of Image: %d",  bmpHead.PmInfo.Width);
        puts("\t(in Pixels)");

        printf("  Height of Image: %d",  bmpHead.PmInfo.Height);
        puts("\t(in Pixels)");

        printf(" Number of Planes: %d",  bmpHead.PmInfo.Planes);
        puts("\t(Must be 1)");

        printf("   Bits Per Pixel: %d",  bmpHead.PmInfo.BitCount);
        printf("\t(%ld Colors Total)\n", 1L << (bmpHead.PmInfo.Planes * 
bmpHead.PmInfo.BitCount));
    }
    else
    if (bmpHead.WinInfo.Size)           /* Windows 3.0 bitmap */
    {
        printf("       Size of Header: %ld", bmpHead.WinInfo.Size);
        puts("\t(Windows 3.0 Bitmap)");
        printf("       Width of Image: %ld", bmpHead.WinInfo.Width);
        puts("\t(in Pixels)");
        printf("      Height of Image: %ld", bmpHead.WinInfo.Height);
        puts("\t(in Pixels)");
        printf("     Number of Planes: %d",  bmpHead.WinInfo.Planes);
        puts("\t(Must be 1)");
        printf("       Bits Per Pixel: %d",  bmpHead.WinInfo.BitCount);
        printf("\t(%ld Colors Total)\n", 1L << (bmpHead.WinInfo.Planes * 
bmpHead.WinInfo.BitCount));
        printf("          Compression: %ld", bmpHead.WinInfo.Compression);
        switch (bmpHead.WinInfo.Compression)
        {
            case COMPRESS_RGB:
                puts("\t(No Compression)");
                break;
            case COMPRESS_RLE4:
                puts("\t(4-bits Per Pixel Encoding)");
                break;
            case COMPRESS_RLE8:
                puts("\t(8-bits Per Pixel Encoding)");
                break;
            default:
                puts("\t(Unknown Compression Format)");
                break;
        }
        printf("        Size of Image: %ld", bmpHead.WinInfo.SizeImage);
        puts("\t(in Bytes)");

        printf("Horizontal Resolution: %ld", bmpHead.WinInfo.XPelsPerMeter);
        puts("\t(in Pixels Per Meter)");

        printf("  Vertical Resolution: %ld", bmpHead.WinInfo.YPelsPerMeter);
        puts("\t(in Pixels Per Meter)");

        printf("   Color Indexes Used: %ld", bmpHead.WinInfo.ClrUsed);
        if (bmpHead.WinInfo.BitCount == 24)
            puts("\t(No Color Table)");
        else
        if (bmpHead.WinInfo.ClrUsed != 0)
            printf("\t(%lu Entries in Color Table)\n", bmpHead.WinInfo.ClrUsed);
        else
            printf("\t(%lu Entries in Color Table)\n",
              (DWORD) (1U << (bmpHead.WinInfo.Planes * bmpHead.WinInfo.BitCount)));

        printf("     Colors Important: %ld", bmpHead.WinInfo.ClrImportant);
        if (bmpHead.WinInfo.ClrImportant == 0)
            printf("\t(All Colors Are Important)");
        else
            printf("\t(%ld Colors Are Important)", bmpHead.WinInfo.ClrImportant);
        fputc('\n', stdout);
    }
    else
    if (bmpHead.PmInfo.Size)         /* OS/2 2.0 bitmap */
    {
        printf("       Size of Header: %ld", bmpHead.Pm2Info.Size);
        puts("\t(OS/2 2.0 Bitmap)");
        printf("       Width of Image: %ld", bmpHead.Pm2Info.Width);
        puts("\t(in Pixels)");
        printf("      Height of Image: %ld", bmpHead.Pm2Info.Height);
        puts("\t(in Pixels)");
        printf("     Number of Planes: %d",  bmpHead.Pm2Info.Planes);
        puts("\t(Must be 1)");
        printf("       Bits Per Pixel: %d",  bmpHead.Pm2Info.BitCount);
        printf("\t(%ld Colors Total)\n", 1L << (bmpHead.Pm2Info.Planes * 
bmpHead.Pm2Info.BitCount));
        printf("          Compression: %ld", bmpHead.Pm2Info.Compression);
        switch (bmpHead.Pm2Info.Compression)
        {
            case COMPRESS_RGB:
                puts("\t(No Compression)");
                break;
            case COMPRESS_RLE4:
                puts("\t(4-bits Per Pixel Encoding)");
                break;
            case COMPRESS_RLE8:
                puts("\t(8-bits Per Pixel Encoding)");
                break;
            default:
                puts("\t(Unknown Compression Format)");
                break;
        }
        printf("        Size of Image: %ld", bmpHead.Pm2Info.SizeImage);
        puts("\t(in Bytes)");

        printf("Horizontal Resolution: %ld", bmpHead.Pm2Info.XPelsPerMeter);
        puts("\t(in Pixels Per Meter)");

        printf("  Vertical Resolution: %ld", bmpHead.Pm2Info.YPelsPerMeter);
        puts("\t(in Pixels Per Meter)");

        printf("   Color Indexes Used: %ld", bmpHead.Pm2Info.ClrUsed);
        if (bmpHead.Pm2Info.BitCount == 24)
            puts("\t(No Color Table)");
        else
        if (bmpHead.Pm2Info.ClrUsed != 0)
            printf("\t(%lu Entries in Color Table)\n", bmpHead.Pm2Info.ClrUsed);
        else
            printf("\t(%lu Entries in Color Table)\n",
              (DWORD) (1U << (bmpHead.Pm2Info.Planes * bmpHead.Pm2Info.BitCount)));

        printf("     Colors Important: %ld", bmpHead.Pm2Info.ClrImportant);
        if (bmpHead.Pm2Info.ClrImportant == 0)
            printf("\t(All Colors Are Important)");
        else
            printf("\t(%ld Colors Are Important)", bmpHead.Pm2Info.ClrImportant);
        fputc('\n', stdout);
    }
    else
    {
        fputs("BMPHEAD: No BMP information read!\n", stderr);
        exit(-7);
    }


    /*
    ** Display the color table (if any).
    **
    ** Use ClrUsed to determine the number of entries in the
    ** color table.  If ClrUsed is 0, then the number of entries
    ** is calculated using BitCount.  Typically, bitmaps with
    ** 24-bits per pixel do not have color tables unless ClrUsed
    ** is non-zero.  All other types of bitmaps (1, 4, or 8-bits per
    ** pixel) do.
    */

    /* Display the color table */      /* OS/2 1.x */
    if (bmpHead.PmInfo.Size && bmpHead.PmInfo.BitCount != 24)
    {
        /* Determine the number of RGB entries in the color table */
        NumberColorTableEntries =
          (WORD) (1U << (bmpHead.PmInfo.Planes * bmpHead.PmInfo.BitCount));

        fputs("\nHit Enter for color table information...", stdout);
        getch();
        putchar('\n');

        printf("\nNumber of Color Table Entries: %u\n\n", NumberColorTableEntries);
        puts("Color\tRed\tGreen\tBlue");

        for (i = 0; i < NumberColorTableEntries; i++)
        {
            printf("%03u\t%03u\t%03u\t%03u\n",
              i,
              bmpHead.PmColorTable[i].rgbRed,
              bmpHead.PmColorTable[i].rgbGreen,
              bmpHead.PmColorTable[i].rgbBlue);

            if (i && i % 22 == 0)
            {
                fputs("Hit Enter for next page...", stdout);
                getch();        
                puts("\n\nColor\tRed\tGreen\tBlue\n");
            }
        }
    }
    else                               /* Windows 3.0 */
    if (bmpHead.WinInfo.Size && 
       (bmpHead.WinInfo.BitCount != 24 || bmpHead.WinInfo.ClrUsed != 0))
    {
        /* Determine the number of RGB entries in the color table */
        if (bmpHead.WinInfo.ClrUsed != 0)
            NumberColorTableEntries = (WORD) bmpHead.WinInfo.ClrUsed;
        else
            NumberColorTableEntries =
              (WORD) (1U << (bmpHead.WinInfo.Planes * bmpHead.WinInfo.BitCount));

        fputs("\nHit Enter for color table information...", stdout);
        getch();
        fputc('\n', stdout);

        printf("\nNumber of Color Table Entries: %u\n\n", NumberColorTableEntries);

        puts("Color\tRed\tGreen\tBlue\tReserved\n");
        for (i = 0; i < NumberColorTableEntries; i++)
        {
            printf("%03u\t%03u\t%03u\t%03u\t%03u\n",
              i,
              bmpHead.WinColorTable[i].rgbRed,
              bmpHead.WinColorTable[i].rgbGreen,
              bmpHead.WinColorTable[i].rgbBlue,
              bmpHead.WinColorTable[i].rgbReserved);

            if (i && i % 22 == 0)
            {
                fputs("Hit Enter for next page...", stdout);
                getch();        
                puts("\n\nColor\tRed\tGreen\tBlue\tReserved\n");
            }
         }
    }
    else                               /* OS/2 2.0 */
    if (bmpHead.Pm2Info.Size &&
       (bmpHead.Pm2Info.BitCount != 24 || bmpHead.Pm2Info.ClrUsed != 0))
    {
        /* Determine the number of RGB entries in the color table */
        if (bmpHead.Pm2Info.ClrUsed != 0)
            NumberColorTableEntries = (WORD) bmpHead.Pm2Info.ClrUsed;
        else
            NumberColorTableEntries =
              (WORD) (1U << (bmpHead.Pm2Info.Planes * bmpHead.Pm2Info.BitCount));

        fputs("\nHit Enter for color table information...", stdout);
        getch();
        fputc('\n', stdout);

        printf("\nNumber of Color Table Entries: %u\n\n", NumberColorTableEntries);

        puts("Color\tRed\tGreen\tBlue\tReserved\n");
        for (i = 0; i < NumberColorTableEntries; i++)
        {
            printf("%03u\t%03u\t%03u\t%03u\t%03u\n",
              i,
              bmpHead.Pm2ColorTable[i].rgbRed,
              bmpHead.Pm2ColorTable[i].rgbGreen,
              bmpHead.Pm2ColorTable[i].rgbBlue,
              bmpHead.Pm2ColorTable[i].rgbReserved);

            if (i && i % 22 == 0)
            {
                fputs("Hit Enter for next page...", stdout);
                getch();        
                puts("\n\nColor\tRed\tGreen\tBlue\tReserved\n");
            }
         }
    }

    fclose(fpBmpIn);
    return(0);
}
