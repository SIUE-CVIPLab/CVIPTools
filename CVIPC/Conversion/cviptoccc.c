/***************************************************************************
======================================================================
Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
======================================================================
                                                                      
             File Name: cviptoccc.c
           Description: contains a routine to write the contents of a CVIPtools
			Image structure to a Color Cell Compression file.
         Related Files: CVIPimage.h, CVIPccc.h, Imakefile
   Initial Coding Date: 1/24/93
           Portability: Standard (ANSI) C
             Credit(s): Gregory Hance, E.E. Dept. SIUE

  Global Function List: cviptoccc
			
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

$Log: cviptoccc.c,v $
Revision 1.4  1997/05/21 03:25:56  yawei
added WIN32 fopen binary support
.,

Revision 1.3  1997/01/15 17:06:29  yawei
Global Change:  IMAGE ==> Image

 * Revision 1.2  1997/01/15  16:02:53  yawei
 * updated changes
 *
 * Revision 1.1  1993/05/31  07:10:11  hanceg
 * Initial revision
 *                                                         

*****************************************************************************/



#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "CVIPconutils.h"
#include "CVIPimage.h"
#define  RED    0
#define  GREEN  1
#define  BLUE   2
#define  NILL   0
#define  MAXCOLORS 254		/* use 245 for xwindows version */
#define  ABSMAXCOLORS 256
#define  MAX_XSIZE 768
#define  MAXDIST   3*256*256+1
#define  LOWER_BLACK_ROWS  64	/* MUST be a multiple of 4 */
#define  CCCFILE 0
#define  SIZE128x128 0
#define  SIZE256x256 1
#define  SIZE512x512 2
#define  SIZE768x768 3
#define  SIZE320x200 4
#define  SIZE640x400 5
#define  SIZE640x480 6
#define  SIZE64x64   7
#define  CELLSIZE 16	/* MUST be a power of 2 <= 32, >= 1  */
#define  MSIZE    4  	/* 8 - log(2, CELLSIZE) */
#define  DISTANCE2(x,y,z) ((x)*(x) + (y)*(y) + (z)*(z))
/* #define  DISTANCE2(x,y,z) (ABS(x) + ABS(y) + ABS(z)) */

struct rep_entry { long rep_no; long dist; };
struct cspace {long B[32];};

void cviptoccc(cvip_Image, ccc_name, cccfile, maxcolor,dermvis,verbose)
 Image *cvip_Image;
 char *ccc_name;
 FILE *cccfile;
 int maxcolor;
 int verbose;
 int dermvis;
{
 char     fnamestr[80], *str_ptr, *prog_name, function_name[] = {"cviptoccc"};
 FILE     *bitfile, *colfile;
 byte    *r_ptr, *g_ptr, *b_ptr;
 unsigned char bitmap[2], tempmin[3], tempmax[3], colortable[ABSMAXCOLORS][3];  
 unsigned int num0, color0[3], num1, color1[3],
	  splitspan, splitcolor;
 int      row, xsize, x, ysize, y, sizecode, cell, bitnum,
          r, g, b, color, i, blackrows,
          rM, gM, bM, j, k, row_size, col_size;
 long     splitcount, avgR, avgG, avgB, dist, dist2, closest;
 double   luminance[4][4], avglum;
 struct {unsigned char color[3];} pixel[4][MAX_XSIZE];  /* was 256 */
 struct {unsigned char color[3];} pixel_rgb[4][MAX_XSIZE];  /* was 256 */
 struct   cspace cspaceRG[32][32];
 struct   cblock {unsigned char min[3];
                  unsigned char max[3];
	          unsigned char span[3];
	          unsigned long count;
		  struct cblock *next;};
 struct   cblock *topblock, *lastblock,
		 *cblockptr, *splitblock;
 struct   rep_entry *ptlist;
 void     insort(), makelist();
 
 CVIPinit(function_name, verbose);

 /*-------------------------------------------------------------*/
 /* Test for specification of image filename prefix.            */
 /* verbose - must be passed as a value of 2                    */  
 /*-------------------------------------------------------------*/
   if(verbose == 2)
   {  fprintf(stderr,"Usage: %s ImageSize FilenamePrefix [Colors] [Quiet]\n",prog_name);
      fprintf(stderr,"Image sizes available:\n128x128\n256x256\n512x512\n");
      fprintf(stderr,"768x768\n320x200\n640x400\n640x480\n64x64\n");
      fprintf(stderr,"Max Colors = %d\n",ABSMAXCOLORS);
      CVIPerror("CVIP error: improper usage");
   }
   
  row_size = cvip_Image->image_ptr[0]->rows;
  col_size = cvip_Image->image_ptr[0]->cols;
  
  
 /*-------------------------------------------------------------*/
 /* Determine the size of the images to be compressed.          */
 /*-------------------------------------------------------------*/
 if ( (row_size == 128) && (col_size == 128) )
    {xsize = 128;  ysize = 128;  sizecode = SIZE128x128;}
 else if ( (row_size == 256) && (col_size == 256) )
    {xsize = 256;  ysize = 256;  sizecode = SIZE256x256;}
 else if ( (row_size == 512) && (col_size == 512) )
    {xsize = 512;  ysize = 512;  sizecode = SIZE512x512;}
 else if ( (row_size == 768) && (col_size == 768) )
    {xsize = 768;  ysize = 768;  sizecode = SIZE768x768;}
 else if ( (row_size == 200) && (col_size == 320) )
    {xsize = 320;  ysize = 200;  sizecode = SIZE320x200;}
 else if ( (row_size == 400) && (col_size == 640) )
    {xsize = 640;  ysize = 400;  sizecode = SIZE640x400;}
 else if ( (row_size == 480) && (col_size == 640) )
    {xsize = 640;  ysize = 480;  sizecode = SIZE640x480;}
 else if ( (row_size == 64) && (col_size == 64) )
    {xsize = 64;   ysize = 64;   sizecode = SIZE64x64;}
 else
    CVIPerror("Image Size %dx%d Is Not Supported.\n", row_size, col_size);

 if(dermvis)		             /* This is the fix for images that */
   blackrows = (LOWER_BLACK_ROWS >> 2) << 2;	/* come from the dervis */
 else					/* camera.  We ignore the bottom */
   blackrows = 0;			/* rows so that the color selection */
					/* is not biased toward the black. */
 /*-------------------------------------------------------------*/
 /* Check if fewer selected colors are desired.                 */
 /* Also, if the fourth argument is not a number, treat as the  */
 /* quiet option and turn informational messages off.           */
 /*-------------------------------------------------------------*/
 /* use 245 for xwindows version */
 if (maxcolor > ABSMAXCOLORS) 
    maxcolor = ABSMAXCOLORS;
 if (maxcolor < 2) 
    maxcolor = 2;

 if (verbose)
   {fprintf(stderr,"cviptoccc:   Color Cell Compression Utility\n");
    fprintf(stderr,"cviptoccc: ----------------------------------\n");
    fprintf(stderr,"cviptoccc: Processing Image File %s.\n", ccc_name);
    fprintf(stderr,"cviptoccc: Dimensions of Image: %dx%d.\n", xsize, ysize);
    fprintf(stderr,"cviptoccc: Color Table Size: %d.\n", maxcolor);
   }
 /*-------------------------------------------------------------*/
 /* Open image file for input into Phase 1.                     */
 /* Open .bit and .col files for Phase 1 output.                */
 /*-------------------------------------------------------------*/
 if ( (str_ptr = (char *) strchr(ccc_name, '.')) == NULL) {
    prog_name = (char *) malloc(strlen(ccc_name)+1);
    strncpy(prog_name, ccc_name, strlen(ccc_name)+1);
 }
 else {
    prog_name = (char *) malloc((str_ptr-ccc_name)+1);
    strncpy(prog_name, ccc_name, str_ptr-ccc_name);
    *(prog_name + (str_ptr-ccc_name)) = '\0';
 }

 strcpy(fnamestr, prog_name);
 strcat(fnamestr, ".bit");
 #ifndef WIN32
 bitfile = fopen(fnamestr, "w"); 
 #else
 bitfile = fopen(fnamestr, "wb"); 
 #endif
 if (bitfile == NULL)
    CVIPerror("cviptoccc: Unable to open %s for output.\n", fnamestr);
     
 strcpy(fnamestr, prog_name);
 strcat(fnamestr, ".col");
 #ifndef WIN32
 colfile = fopen(fnamestr, "w"); 
 #else
 colfile = fopen(fnamestr, "wb"); 
 #endif
 if (colfile == NULL)
    {CVIPerror("cviptoccc: Unable to open %s for output.\n", fnamestr);
     fclose(bitfile);
     }

 /*-------------------------------------------------------------*/
 /*  P h a s e   1  -  Luminance Quantization.                  */
 /*-------------------------------------------------------------*/
 if (verbose)
   {fprintf(stderr,"cviptoccc: Phase 1 - Luminance Quantization.\n");
    fprintf(stderr,"cviptoccc: Phase 1 - Processing Scanline   0.");
   }
   
 r_ptr = (byte *) *((byte **) cvip_Image->image_ptr[0]->rptr);
 g_ptr = (byte *) *((byte **) cvip_Image->image_ptr[1]->rptr);
 b_ptr = (byte *) *((byte **) cvip_Image->image_ptr[2]->rptr);

 for (row = 0; row < ysize-blackrows; row += 4)
     {if (verbose)
	{fprintf(stderr,"\b\b\b\b%3d.", row);
         fflush(stdout);
        }
	
      /*-------------------------------------------------------------*/
      /* Fetch four scanlines at a time from CVIP Image structure.   */
      /*-------------------------------------------------------------*/
      for (y=0; y<4; y++)
	  for (x=0; x<xsize; x++) {
	       pixel[y][x].color[RED]   = r_ptr[(row+y)*ysize + x];
	       pixel[y][x].color[GREEN] = g_ptr[(row+y)*ysize + x];
	       pixel[y][x].color[BLUE]  = b_ptr[(row+y)*ysize + x];
      }

      /*--------------------------------------------------------*/
      /* For each 4x4 cell, calculate the luminance for each    */
      /* pixel as well as the average luminance for the cell.   */
      /*--------------------------------------------------------*/
      for (cell=0; cell<xsize; cell+=4)
	  {avglum = 0.0;
	   for (y=0; y<4; y++)
	       for (x=0; x<4; x++)
		   {luminance[y][x] = (.30 * pixel[y][x+cell].color[RED])
				    + (.59 * pixel[y][x+cell].color[GREEN])
				    + (.11 * pixel[y][x+cell].color[BLUE]);
                    avglum += luminance[y][x];
                   }
           avglum /= 16.0;

           /*---------------------------------------------------*/
	   /* Generate a 4x4 bitmap representing the cell's     */
	   /* quantization based on the average luminance.      */
	   /* Accumulate the number of pixels quantized to each */
	   /* level.                                            */
           /*---------------------------------------------------*/
           num0 = 0;  num1 = 0;
	   color0[RED] = 0;   color0[GREEN] = 0;   color0[BLUE] = 0;
	   color1[RED] = 0;   color1[GREEN] = 0;   color1[BLUE] = 0;
	   bitmap[0] = 0;     bitmap[1] = 0;
           for (y=0; y<4; y++)
	       for (x=0; x<4; x++)
		   {if (luminance[y][x]>avglum)
                       {bitnum = (y<<2)+x;
                        if (bitnum<8)
                            bitmap[0] |= ((unsigned char)128)>>bitnum;
                        else
                           {bitnum-=8;
                            bitmap[1] |= ((unsigned char)128)>>bitnum;
                           }
	                num1++; 
			color1[RED]   += pixel[y][x+cell].color[RED];
			color1[GREEN] += pixel[y][x+cell].color[GREEN];
			color1[BLUE]  += pixel[y][x+cell].color[BLUE];
                       }
		    else 
	               {num0++; 
			color0[RED]   += pixel[y][x+cell].color[RED];
			color0[GREEN] += pixel[y][x+cell].color[GREEN];
			color0[BLUE]  += pixel[y][x+cell].color[BLUE];
                       }
                   }

           /*---------------------------------------------------*/
	   /* Calculate the average color for each quantization */
	   /* level. Output them to the *.col file, and the bit */
	   /* map of the cell to the *.bit file.                */
           /*---------------------------------------------------*/
	   if (num0>0)
              {color0[RED] /= num0;  color0[GREEN] /= num0;  color0[BLUE] /= num0;}
           if (num1>0)
              {color1[RED] /= num1;  color1[GREEN] /= num1;  color1[BLUE] /= num1;}
	   fwrite(bitmap, 2, 1, bitfile);
	   putc(color0[RED],   colfile);
	   putc(color0[GREEN], colfile);
	   putc(color0[BLUE],  colfile);
	   putc(color1[RED],   colfile);
	   putc(color1[GREEN], colfile);
	   putc(color1[BLUE],  colfile);
          }
     }

 if (verbose)
    fprintf(stderr,"\b\b\b\b%3d.\ncviptoccc: Phase 1 - Processing Complete.\n", ysize);
 fclose(colfile);  fclose(bitfile);

 /*-------------------------------------------------------------*/
 /*  P h a s e   2  -  Median Cut Sampling of Color Histogram   */
 /*-------------------------------------------------------------*/
 if (verbose)
   {fprintf(stderr,"cviptoccc: Phase 2 - Color Histogram Sampling.\n");
    fprintf(stderr,"cviptoccc: Phase 2 - Color Space Subdivision   0.");
   }

 /*-------------------------------------------------------------*/
 /* Initialize the color space histogram.                       */
 /*-------------------------------------------------------------*/
 for (r=0; r<32; r++)
    for (g=0; g<32; g++)
       for (b=0; b<32; b++)
	  cspaceRG[r][g].B[b] = 0;
            
 /*-------------------------------------------------------------*/
 /* Allocate top colorblock and initialize to full color space. */
 /* Populate histogram cells from contents of *.col file.       */
 /*-------------------------------------------------------------*/
 topblock  = (struct cblock *) malloc(sizeof(struct cblock));
 lastblock = topblock;
 topblock->min[RED] = 32;  topblock->min[GREEN] = 32;  topblock->min[BLUE] = 32;
 topblock->max[RED] = 0;   topblock->max[GREEN] = 0;   topblock->max[BLUE] = 0;
 topblock->count = 0;      topblock->next = NULL; 
 strcpy(fnamestr, prog_name);
 strcat(fnamestr, ".col");
 #ifndef WIN32
 colfile = fopen(fnamestr, "r"); 
 #else
 colfile = fopen(fnamestr, "rb"); 
 #endif
 while((r = getc(colfile)) != EOF)
       {r>>=3;
	g = (getc(colfile)>>3);
	b = (getc(colfile)>>3);
	cspaceRG[r][g].B[b]++;
	topblock->count++;
	if (r < topblock->min[RED])   topblock->min[RED]   = r;
	if (g < topblock->min[GREEN]) topblock->min[GREEN] = g;
	if (b < topblock->min[BLUE])  topblock->min[BLUE]  = b;
	if (r > topblock->max[RED])   topblock->max[RED]   = r;
	if (g > topblock->max[GREEN]) topblock->max[GREEN] = g;
	if (b > topblock->max[BLUE])  topblock->max[BLUE]  = b;
       }
 topblock->span[RED]   = 1 + topblock->max[RED]   - topblock->min[RED];
 topblock->span[GREEN] = 1 + topblock->max[GREEN] - topblock->min[GREEN];
 topblock->span[BLUE]  = 1 + topblock->max[BLUE]  - topblock->min[BLUE];
 fclose(colfile);

 /*-------------------------------------------------------------*/
 /* Perform one colorblock split for each color sample desired. */
 /*-------------------------------------------------------------*/
 for (color=1; color<maxcolor; color++)  {

     splitspan = 1;
     cblockptr = topblock;

      /*--------------------------------------------------------*/
      /* Determine colorblock with the greatest color span.     */
      /*--------------------------------------------------------*/
      while(cblockptr!=NULL)
	   {for (i=0; i<3; i++)
	       if (cblockptr->span[i] > splitspan)
                 {splitspan  = cblockptr->span[i];
	          splitcolor = i;
	          splitblock = cblockptr;
                 }
            cblockptr = cblockptr->next;
           }
      /*--------------------------------------------------------*/
      /* Break out early if there are too few unique colors.    */
      /*--------------------------------------------------------*/
      if (splitspan == 1) break;

      /*--------------------------------------------------------*/
      /* Split the color block in half based on the number of   */
      /* pixel samples it contains. Reuse the chosen colorblock */
      /* for one side of the split, and allocate a new one on   */
      /* the end for the other.                                 */
      /*--------------------------------------------------------*/
      splitcount = (splitblock->count)>>1;
      lastblock->next = (struct cblock *) malloc(sizeof(struct cblock));
      lastblock = lastblock->next;
      if (verbose) {
         fprintf(stderr,"\b\b\b\b%3d.", color);
         fflush(stdout);
      }
      lastblock->next = NULL;
      /*--------------------------------------------------------*/
      /* Split the red range between the two colorblocks.       */
      /*--------------------------------------------------------*/
      if (splitcolor == RED)
         {for (r=(splitblock->min[RED]); r<(splitblock->max[RED]-1); r++)
             {for (g=(splitblock->min[GREEN]); g<=(splitblock->max[GREEN]); g++)
                 for (b=(splitblock->min[BLUE]); b<=(splitblock->max[BLUE]); b++)
                     splitcount -= cspaceRG[r][g].B[b];
              if (splitcount<0) break;
             }
          lastblock->min[RED]   = r+1;
	  lastblock->max[RED]   = splitblock->max[RED];
	  splitblock->max[RED]  = r;
	  lastblock->min[GREEN] = splitblock->min[GREEN];
	  lastblock->max[GREEN] = splitblock->max[GREEN];
	  lastblock->min[BLUE]  = splitblock->min[BLUE];
	  lastblock->max[BLUE]  = splitblock->max[BLUE];
         }
      /*--------------------------------------------------------*/
      /* Split the green range between the two colorblocks.     */
      /*--------------------------------------------------------*/
      else if (splitcolor == GREEN)
         {for (g=(splitblock->min[GREEN]); g<(splitblock->max[GREEN]-1); g++)
             {for (b=(splitblock->min[BLUE]); b<=(splitblock->max[BLUE]); b++)
                 for (r=(splitblock->min[RED]); r<=(splitblock->max[RED]); r++)
                     splitcount -= cspaceRG[r][g].B[b];
              if (splitcount<0) break;
             }
	  lastblock->min[GREEN]  = g+1;
	  lastblock->max[GREEN]  = splitblock->max[GREEN];
	  splitblock->max[GREEN] = g;
	  lastblock->min[BLUE]   = splitblock->min[BLUE];
	  lastblock->max[BLUE]   = splitblock->max[BLUE];
	  lastblock->min[RED]    = splitblock->min[RED];
	  lastblock->max[RED]    = splitblock->max[RED];
         }
      /*--------------------------------------------------------*/
      /* Split the blue range between the two colorblocks.      */
      /*--------------------------------------------------------*/
      else 
         {for (b=(splitblock->min[BLUE]); b<(splitblock->max[BLUE]-1); b++)
             {for (r=(splitblock->min[RED]); r<=(splitblock->max[RED]); r++)
                 for (g=(splitblock->min[GREEN]); g<=(splitblock->max[GREEN]); g++)
                     splitcount -= cspaceRG[r][g].B[b];
              if (splitcount<0) break;
             }
          lastblock->min[BLUE]  = b+1;
          lastblock->max[BLUE]  = splitblock->max[BLUE];
	  splitblock->max[BLUE] = b;
	  lastblock->min[RED]   = splitblock->min[RED];
	  lastblock->max[RED]   = splitblock->max[RED];
	  lastblock->min[GREEN] = splitblock->min[GREEN];
	  lastblock->max[GREEN] = splitblock->max[GREEN];
         }

      /*--------------------------------------------------------*/
      /* Shrink the original colorblock around it's samples.    */
      /*--------------------------------------------------------*/
      splitblock->count = 0;
      tempmin[RED] = 32;  tempmin[GREEN] = 32;  tempmin[BLUE] = 32;
      tempmax[RED] = 0;   tempmax[GREEN] = 0;   tempmax[BLUE] = 0;
      for (r=(splitblock->min[RED]); r<=(splitblock->max[RED]); r++)
         for (g=(splitblock->min[GREEN]); g<=(splitblock->max[GREEN]); g++)
            for (b=(splitblock->min[BLUE]); b<=(splitblock->max[BLUE]); b++)
               	if (cspaceRG[r][g].B[b] > 0)
	          {splitblock->count += cspaceRG[r][g].B[b];
	           if (r < tempmin[RED])   tempmin[RED]   = r;
	           if (g < tempmin[GREEN]) tempmin[GREEN] = g;
	           if (b < tempmin[BLUE])  tempmin[BLUE]  = b;
	           if (r > tempmax[RED])   tempmax[RED]   = r;
                   if (g > tempmax[GREEN]) tempmax[GREEN] = g;
	           if (b > tempmax[BLUE])  tempmax[BLUE]  = b;
		  }
      splitblock->min[RED]   = tempmin[RED];
      splitblock->min[GREEN] = tempmin[GREEN];
      splitblock->min[BLUE]  = tempmin[BLUE];
      splitblock->max[RED]   = tempmax[RED];
      splitblock->max[GREEN] = tempmax[GREEN];
      splitblock->max[BLUE]  = tempmax[BLUE];
      splitblock->span[RED]   = 1 + splitblock->max[RED]   - splitblock->min[RED];
      splitblock->span[GREEN] = 1 + splitblock->max[GREEN] - splitblock->min[GREEN];
      splitblock->span[BLUE]  = 1 + splitblock->max[BLUE]  - splitblock->min[BLUE];
      /*--------------------------------------------------------*/
      /* Shrink the new colorblock around it's samples.         */
      /*--------------------------------------------------------*/
      lastblock->count=0;
      tempmin[RED] = 32;  tempmin[GREEN] = 32;  tempmin[BLUE] = 32;
      tempmax[RED] = 0;   tempmax[GREEN] = 0;   tempmax[BLUE] = 0;
      for (r=(lastblock->min[RED]); r<=(lastblock->max[RED]); r++)
          for (g=(lastblock->min[GREEN]); g<=(lastblock->max[GREEN]); g++)
             for (b=(lastblock->min[BLUE]); b<=(lastblock->max[BLUE]); b++)
		if (cspaceRG[r][g].B[b] > 0)
		  {lastblock->count += cspaceRG[r][g].B[b];
	           if (r < tempmin[RED])   tempmin[RED]   = r;
	           if (g < tempmin[GREEN]) tempmin[GREEN] = g;
	           if (b < tempmin[BLUE])  tempmin[BLUE]  = b;
	           if (r > tempmax[RED])   tempmax[RED]   = r;
                   if (g > tempmax[GREEN]) tempmax[GREEN] = g;
	           if (b > tempmax[BLUE])  tempmax[BLUE]  = b;
		  }
       lastblock->min[RED]   = tempmin[RED];
       lastblock->min[GREEN] = tempmin[GREEN];
       lastblock->min[BLUE]  = tempmin[BLUE];
       lastblock->max[RED]   = tempmax[RED];
       lastblock->max[GREEN] = tempmax[GREEN];
       lastblock->max[BLUE]  = tempmax[BLUE];
       lastblock->span[RED]   = 1 + lastblock->max[RED]   - lastblock->min[RED];
       lastblock->span[GREEN] = 1 + lastblock->max[GREEN] - lastblock->min[GREEN];
       lastblock->span[BLUE]  = 1 + lastblock->max[BLUE]  - lastblock->min[BLUE];
      }
 if (verbose)
    fprintf(stderr,"\b\b\b\b%3d.\ncviptoccc: Phase 2 - Processing Complete.\n", color);

 /*-------------------------------------------------------------*/
 /*  P h a s e   3  -  Color Table Generation.                  */
 /*-------------------------------------------------------------*/
 if (verbose)
   {fprintf(stderr,"cviptoccc: Phase 3 - Color Table Generation.\n");
    fprintf(stderr,"cviptoccc: Phase 3 - Calculating Entry   0.");
   }
 cblockptr = topblock;
 maxcolor  = color;
 color = 0;
 /*-------------------------------------------------------------*/
 /* Calculate the weighted average color for each colorblock.   */
 /* Deallocate each colorblock when calculations are complete.  */
 /*-------------------------------------------------------------*/
 while (cblockptr!=NULL)
      {avgR = 0;   avgG = 0;   avgB = 0;
       for (r=(cblockptr->min[RED]); r<=(cblockptr->max[RED]); r++)
          for (g=(cblockptr->min[GREEN]); g<=(cblockptr->max[GREEN]); g++)
             for (b=(cblockptr->min[BLUE]); b<=(cblockptr->max[BLUE]); b++)
		{avgR += (cspaceRG[r][g].B[b] * (r<<3));
		 avgG += (cspaceRG[r][g].B[b] * (g<<3));
		 avgB += (cspaceRG[r][g].B[b] * (b<<3));
                }
       colortable[color][RED]   = (unsigned char)(avgR / cblockptr->count);
       colortable[color][GREEN] = (unsigned char)(avgG / cblockptr->count);
       colortable[color][BLUE]  = (unsigned char)(avgB / cblockptr->count);
       topblock  = cblockptr;
       cblockptr = cblockptr->next;
       free(topblock);
       if (verbose)
       {  fprintf(stderr,"\b\b\b\b%3d.", color);
          fflush(stdout);
       }
       color++;
      }
 if (verbose) fprintf(stderr,"\b\b\b\b%3d.\ncviptoccc: Phase 3 - Processing Complete.\n", maxcolor);

 /*-------------------------------------------------------------*/
 /*  P h a s e   4  -  Color Table Mapping/Image File Creation. */
 /*-------------------------------------------------------------*/
 if (verbose)
   {fprintf(stderr,"cviptoccc: Phase 4 - Color Table Mapping.\n");
    fprintf(stderr,"cviptoccc: Phase 4 - Processing Scanline   0.");
   }

 strcpy(fnamestr, prog_name);
 strcat(fnamestr, ".ccc");
 strcpy(fnamestr, prog_name);
 strcat(fnamestr, ".bit");
 #ifndef WIN32
 bitfile = fopen(fnamestr, "r");
 #else
 bitfile = fopen(fnamestr, "rb");
 #endif

 strcpy(fnamestr, prog_name);
 strcat(fnamestr, ".col");
 #ifndef WIN32
 colfile = fopen(fnamestr, "r");
 #else
 colfile = fopen(fnamestr, "rb");
 #endif

 /*-------------------------------------------------------------*/
 /* Dump (colortable size-1) and color table to ccc file first. */
 /*-------------------------------------------------------------*/
 putc(CCCFILE,    cccfile);
 putc(sizecode,   cccfile);
 putc(maxcolor-1, cccfile);
 for (color=0; color<maxcolor; color++)
     {putc((int)colortable[color][RED],   cccfile); 
      putc((int)colortable[color][GREEN], cccfile); 
      putc((int)colortable[color][BLUE],  cccfile); 
     }

 /*-------------------------------------------------------------*/
 /* Next, put each of the 4x4 bitmaps with it associated pair   */
 /* color table pointers into the image file.  Mapping to the   */
 /* color table entries takes place here.  		        */
 /*-------------------------------------------------------------*/
 for(i=0; i<CELLSIZE; i++)		/* Here we are going to reuse the */
    for(j=0; j<CELLSIZE; j++)		/* colorspace array to hold the */
       for(k=0; k<CELLSIZE; k++)	/* pointers to the lists of */
	  cspaceRG[i][j].B[k] = NILL;	/* representatives (from colortable) */
 for (y=0; y<(ysize-blackrows)>>2; y++)
   {if (verbose)
      {fprintf(stderr,"\b\b\b\b%3d.", y<<2);
       fflush(stdout);
      }
    for (x=0; x<(xsize>>2); x++)
       {fread(bitmap, 2, 1, bitfile);
	fwrite(bitmap, 2, 1, cccfile);
	for (i=0; i<2; i++)
           {r = getc(colfile);   g = getc(colfile);   b = getc(colfile);
	    rM = r>>MSIZE;  gM = g>>MSIZE;  bM = b>>MSIZE;
	/* If the list doesn't exist for this color cell, create it. */
	    if(cspaceRG[rM][gM].B[bM] == NILL)
	       makelist(cspaceRG, maxcolor, colortable, rM, gM, bM);
            dist = MAXDIST;   /* Start with the maximum dist */
	    ptlist = (struct rep_entry *) cspaceRG[rM][gM].B[bM];
	    j = 0;
	    while(dist > ptlist[j].dist)
	    {  dist2 = DISTANCE2(r - colortable[ptlist[j].rep_no][RED],
				 g - colortable[ptlist[j].rep_no][GREEN],
				 b - colortable[ptlist[j].rep_no][BLUE]);
	       if(dist2 < dist)			/* Find the color from the */
	       {  closest = ptlist[j].rep_no;	/* list that minimizes dist2 */
		  dist = dist2;
	       }
	       j++;
	    }
            putc(closest, cccfile);		/* Put it in the file */
           }
       }
   }
 if (verbose)
    fprintf(stderr,"\b\b\b\b%3d.\ncviptoccc: Phase 4 - Processing Complete.\n", ysize);
 bitmap[0] = 0;
 bitmap[1] = 0;
 closest = 0;
 for(y=0; y<(blackrows >> 2); y++)	/* If blackrows is zero, this loop */
   for(x=0; x<(xsize >> 2); x++)	/* should not execute. */
   {  fwrite(bitmap, 2, 1, cccfile);
      putc(closest, cccfile);
      putc(closest, cccfile);
   }
 fclose(bitfile);  fclose(colfile);
 strcpy(fnamestr, prog_name);
 strcat(fnamestr, ".bit");
 unlink(fnamestr);
 strcpy(fnamestr, prog_name);
 strcat(fnamestr, ".col");
 unlink(fnamestr);
}

void makelist(ptcells, maxcolor, ct, rM, gM, bM)
   struct cspace ptcells[][32];
   int maxcolor, rM, gM, bM;
   unsigned char ct[][3];
{
   int color, r, g, b, countentry, radius2, tempdist, i,
       rdiff, gdiff, bdiff, rp1, gp1, bp1, mindist, mincolor, center[3], d2;
   struct rep_entry temp[ABSMAXCOLORS+1], *ptlist;
   void insort();
	/****************************************************************/
	/* Create a list of possible representatives (colortable	*/
	/* entries) that we should test for a given color from the	*/
	/* *.col file.  Hopefully, this list will be much shorter than	*/
	/* checking all 256 possible colortable entries.		*/
	/****************************************************************/
   mindist = MAXDIST;                	/* Start with biggest dist */
   mincolor = -1;			/* Safety precaution. See NOTE below */
   countentry = 0;			/* Count the entries in cell list */
   center[RED]   = (r = rM << MSIZE) + (1 << (MSIZE - 1)); /* Find center */
   center[GREEN] = (g = gM << MSIZE) + (1 << (MSIZE - 1)); /* of cell */
   center[BLUE]  = (b = bM << MSIZE) + (1 << (MSIZE - 1));
   rp1 = ((rM + 1) << MSIZE) - 1;	/* (r,g,b) is the lower corner */
   gp1 = ((gM + 1) << MSIZE) - 1;	/* of the cell.  (rp1,gp1,bp1) */
   bp1 = ((bM + 1) << MSIZE) - 1;	/* is the upper corner. */
	/****************************************************************/
	/* For each color in the colortable, check to see if it is in	*/
	/* the cell defined by (rM,gM,bM) (from *.col file).  If it is,	*/
	/* add it to the list with a distance of zero.			*/
	/* NOTE:  Theoretically, there SHOULD be at least one colortable*/
	/* entry that falls in a cell that has been specified by a point*/
	/* in the *.col file because the histogram was generated from	*/
	/* the *.col file and the entries are calculated from the hist. */
	/* Therefore it is inconceivable that the following loop could	*/
	/* terminate without finding a mincolor.  Isn't it?		*/
	/****************************************************************/
   for(color = 0; color < maxcolor; color++)
      if(ct[color][RED]  >> MSIZE == rM &&	/* Is this color in the cell */
	 ct[color][GREEN]>> MSIZE == gM &&	/* we are currently testing? */
         ct[color][BLUE] >> MSIZE == bM)
      {  temp[++countentry].rep_no = color;	/* If so, put it in the list */
	 temp[countentry].dist = 0;		/* and keep closest to center */
	 tempdist = DISTANCE2(ct[color][RED]   - center[RED],
			      ct[color][GREEN] - center[GREEN],
			      ct[color][BLUE]  - center[BLUE]);
	 if(tempdist < mindist)
	 {  mindist = tempdist;
	    mincolor = color;
	 }
      }
	/****************************************************************/
	/* Now find the maximum distance from the point closest to the	*/
	/* center to the edge of the cell.  This distance will be used	*/
	/* as a radius around the cell boundary.  All representatives	*/
	/* within this radius will be included in the list.		*/
	/****************************************************************/
   if(mincolor >= 0)	/* Added safety precaution here */
   {rdiff = (ct[mincolor][RED]   >= center[RED]   ? r : rp1)-ct[mincolor][RED];
   gdiff = (ct[mincolor][GREEN] >= center[GREEN] ? g : gp1)-ct[mincolor][GREEN];
   bdiff = (ct[mincolor][BLUE]  >= center[BLUE]  ? b : bp1)-ct[mincolor][BLUE];
   radius2 = DISTANCE2(rdiff, gdiff, bdiff);
   }
   else		/* If no colors were found in the box, make the radius the */
      radius2 = mindist;	/* maximum. (number left in mindist) */
	/****************************************************************/
	/* Next look at all colortable entries not in the cell but close*/
	/* enough that they may be the nearest neighbor to a given pixel*/
	/* within the cell.						*/
	/****************************************************************/
   for(color = 0; color < maxcolor; color++)
      if(!(ct[color][RED]  >> MSIZE == rM &&	/* Is this color NOT in the */
	   ct[color][GREEN]>> MSIZE == gM &&	/* cell we are testing? */
           ct[color][BLUE] >> MSIZE == bM))
      {  rdiff = (ct[color][RED]   < r ? r : rp1) - ct[color][RED];
	 gdiff = (ct[color][GREEN] < g ? g : gp1) - ct[color][GREEN];
	 bdiff = (ct[color][BLUE]  < b ? b : bp1) - ct[color][BLUE];
	 if(ct[color][RED]   >= r && ct[color][RED]   <= rp1) rdiff = 0;
	 if(ct[color][GREEN] >= g && ct[color][GREEN] <= gp1) gdiff = 0;
	 if(ct[color][BLUE]  >= b && ct[color][BLUE]  <= bp1) bdiff = 0;
	 if((d2 = DISTANCE2(rdiff, gdiff, bdiff)) < radius2)
	 {  temp[++countentry].rep_no = color;	/* Save it if within radius2 */
	    temp[countentry].dist = d2;		/* of the cell boundary */
	 }
      }				/* Sort the whole list for fast convergence */
   insort(temp, countentry);	/* to a nearest neighbor. (insertion sort) */
   ptlist = (struct rep_entry *)malloc((1+countentry) * sizeof(struct rep_entry));
   for(i=0; i<countentry; i++)	/* Allocate memory to hold list, copy list */
      ptlist[i] = temp[i+1];	/* into new memory, and save a pointer to it */
   ptlist[countentry].dist = MAXDIST;	/* Add a large distance to the end */
   ptlist[countentry].rep_no = 0;	/* so search will terminate. */
   ptcells[rM][gM].B[bM] = (long)ptlist;
}

void insort(list, count)
   struct rep_entry *list;
   int count;
{
   int j;			/* Insertion sort on the distance key */
   struct rep_entry temp;	/* for the list of representatives */
   void insert();

   list[0].dist = -1;		/* Make the first entry in the list the */
   for(j=2; j<=count; j++)	/* smallest.  Start with a two-member list */
   {  temp = list[j];		/* and insert the rest of the entries into */
      insert(list, &temp, j-1);	/* this list in ascending order. */
   }
}

void insert(list, temp, i)
   struct rep_entry *list, *temp;
   int i;
{
  while((*temp).dist < list[i].dist)	/* This subroutine inserts the given */
   {  list[i+1] = list[i]; i--; }	/* entry into the list in the proper */
   list[i+1] = *temp;			/* place.  Ascending order. */
}
