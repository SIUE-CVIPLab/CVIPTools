/***************************************************************************
======================================================================
Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
======================================================================
                                                                      
             File Name: ccctocvip.c
           Description: contains a routine to load a CCC (Color Cell
			Compression) file into a CVIP Image structure.
         Related Files: CVIPimage.h, CVIPccc.h, Makefile
   Initial Coding Date: 1/24/92
           Portability: Standard (ANSI) C
             Credit(s): Gregory Hance, E.E. Dept. SIUE

  Global Function List: ccctocvip

			
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

$Log: ccctocvip.c,v $
Revision 1.3  1997/03/08 00:42:46  yawei
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

Revision 1.2  1997/01/15 17:06:35  yawei
Global Change:  IMAGE ==> Image

 * Revision 1.1  1993/05/31  07:10:09  hanceg
 * Initial revision
 *

*****************************************************************************/

#include <stdio.h>
#include "CVIPimage.h"
#define  RED     0
#define  GREEN   1
#define  BLUE    2
#define  MAX_X_RES  1024
#define  MAX_Y_RES   864 
#define  CCCFILE       0
#define  SIZE128x128   0
#define  SIZE256x256   1
#define  SIZE512x512   2
#define  SIZE768x768   3
#define  SIZE320x200   4
#define  SIZE640x400   5
#define  SIZE640x480   6
#define  SIZE64x64     7


/****************************************************************
                  Name: ccctocvip
         Expanded Name: Color Cell Compression to CVIP
            Parameters: prog_name - pointer to chracter string containing
				    the name of the image to be loaded
                          cccfile - pointer to open file descriptor
			  verbose - wanna know what I do?
               Returns: pointer to newly allocated Image structure with
			data from CCC image (uncompressed of course...)
           Description: loads an Image structure with data from a CCC
			image and initializes all parameters of the structure
			to the specifications of the image.
           Diagnostics: all sorts of interesting comments on what the program
			is up to ... cool huh. 
			Returns a NULL pointer w/ corresponding error
			message when...
				- file prog_name cannot be opened
				- file is not in CCC format
             Credit(s): University of Rolla, Missouri
			Greg Hance (added CVIP support)
			
			
****************************************************************/
Image *ccctocvip(prog_name, cccfile, verbose)
 char *prog_name;
 FILE *cccfile;
 int verbose;
{
 char   *char_buff, *str_ptr;
 Image *ccc_Image;
 unsigned char colorcell[3][256], scanline[4][MAX_X_RES];
 unsigned char bitmap[2], color0, color1, mask;
 byte *r_ptr, *g_ptr, *b_ptr;
 int      colortabsize, color, x, y, i, j;
 int      xres, yres, imagesize, filetype, mult;

 if(verbose){
 fprintf(stderr,"ccctocvip:  Color Cell Decompression Utility\n");
 fprintf(stderr,"ccctocvip: ----------------------------------\n");
 fprintf(stderr,"ccctocvip: Processing Image File %s.\n", prog_name);
 }

 /*-----------------------------------------------------------*/
 /* Open .ccc file for input and .pic file for output.        */
 /*-----------------------------------------------------------*/
 if (cccfile == NULL)
    {fprintf(stderr,"ccctocvip: Unable to open %s for input.\n", prog_name);
     return(NULL);}

 /*-----------------------------------------------------------*/
 /* Fetch colortable size-1 from first byte of .ccc file.     */
 /* Then retrieve that many color value from the subsequent   */
 /* bytes.                                                    */
 /*-----------------------------------------------------------*/
 if( cccfile != stdin )
    filetype=getc(cccfile);
 else
    filetype=0;
 if (filetype != CCCFILE)
    {fprintf(stderr,"CCCDISP: File %s is not in CCC format.\n", prog_name);
     return(NULL);}
 imagesize=getc(cccfile);
 if (imagesize == SIZE128x128)
    {xres=128; yres=128; mult=6;}
 else if (imagesize == SIZE256x256)
    {xres=256; yres=256; mult=3;}
 else if (imagesize == SIZE512x512)
    {xres=512; yres=512; mult=1;}
 else if (imagesize == SIZE768x768)
    {xres=768; yres=768; mult=1;}
 else if (imagesize == SIZE320x200)
    {xres=320; yres=200; mult=1;}
 else if (imagesize == SIZE640x400)
    {xres=640; yres=400; mult=1;}
 else if (imagesize == SIZE640x480)
    {xres=640; yres=480; mult=1;}
 else if (imagesize == SIZE64x64)
    {xres=64;  yres=64; mult=12;}
 else
    {fprintf(stderr,"CCCDISP: Unable to determine dimensions of %s.\n", prog_name);
     return(NULL);}
     
  ccc_Image = (Image *) image_allocate(CCC, RGB, 3, yres, xres, CVIP_BYTE, REAL); 
  r_ptr = (byte *) ccc_Image->image_ptr[0]->rptr[0];
  g_ptr = (byte *) ccc_Image->image_ptr[1]->rptr[0];
  b_ptr = (byte *) ccc_Image->image_ptr[2]->rptr[0];

/*******************************************************************/
/* This line added to remove the expansion feature which is only   */
/* needed when running under X-windows				   */
mult = 1;
/*******************************************************************/
 colortabsize = getc(cccfile)+1;
 for (color=0; color<colortabsize; color++)
    {colorcell[RED][color]   = (unsigned char)getc(cccfile); 
     colorcell[GREEN][color] = (unsigned char)getc(cccfile); 
     colorcell[BLUE][color]  = (unsigned char)getc(cccfile); 
    }
 /*-----------------------------------------------------------*/
 /* Process the 4x4 color cells left-to-right from the top of */
 /* the ccc file downward.  Build up 4 scanlines for dumping  */
 /* to the pic file when the end of the line is reached.      */
 /*-----------------------------------------------------------*/
 if(verbose)
    fprintf(stderr,"ccctocvip: Decompressing Scanline   0.");
 for (y=0; y<(yres*mult)>>2; y++)
    {if(verbose)
     {  fprintf(stderr,"\b\b\b\b%3d.", (y<<2));
     fflush(stdout);
     }
     for (x=0; x<xres; x+=4)
	{bitmap[0] = (unsigned char)getc(cccfile);
	 bitmap[1] = (unsigned char)getc(cccfile);
	 color0    = (unsigned char)getc(cccfile);
	 color1    = (unsigned char)getc(cccfile);
	 mask=128;
	 for (j=0; j<4; j++)
	    {for (i=0; i<4; i++)
		{if ((bitmap[j>>1] & mask) > 0)
		    scanline[j][x+i] = color1;
                 else
		    scanline[j][x+i] = color0;
                 if ((mask>>=1) == 0) mask=128;
                }
             }
        }
      for (i=0; i<4; i++)
         for (j=0; j<xres; j++)
            {*r_ptr++ = (byte) colorcell[RED][scanline[i][j]];
             *g_ptr++ = (byte) colorcell[GREEN][scanline[i][j]];;
             *b_ptr++ = (byte) colorcell[BLUE][scanline[i][j]];;
            }
     }
 if(verbose){
    fprintf(stderr,"\b\b\b\b%3d.", yres);
    fprintf(stderr,"\nccctocvip: Decompression Complete.\n\n");
 }
 
 return ccc_Image;
}
