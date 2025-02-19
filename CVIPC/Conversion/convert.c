/***************************************************************************
======================================================================
Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
======================================================================
                                                                      
             File Name: convert.c
           Description: contains routines found in libcolor.a. The functions
			specified below are particularly useful as end user
			functions for loading different file formats into
			the CVIP Image structure. At present the following
			file formats are supported...
                            PBM - Portable Bit Map
		            PGM - Portable Gray Map
			    PPM - Portable Pix Map
			    EPS - Encapsulated Post Script
			   TIFF - Tagged Image File Format
			    GIF - Graphical Interchange Format
			    RAS - Sun Raster File Format
		           ITEX - ITEX Image Format
			   IRIS - Silicon Graphics Image Format
			    CCC - Color Cell Compression Format
			    BIN - Binary (Raw) Image Format
                            VIP - Visualization and Image Processing Format
                            GLR - Gray Level Runlength Coding Format 
                            BTC - Block Truncation Coding Format
                            BRC - Bitplane Runlength Coding
         Related Files: CVIPconvert.h, Makefile and 
			all Includes listed below
   Initial Coding Date: 1/24/92
           Portability: Standard (ANSI) C
             Credit(s): Gregory Hance, E.E. Dept. SIUE

Global Function List: CVIPgetformat
			CVIPreadimage
			CVIPwriteimage
			new_ext
   Local Function List: pnm_setup
			eps_setup
			itex_setup
			ras_setup
			gif_setup
			ccc_setup
			tiff_setup
			bin_wsetup
			bin_rsetup
			guess_bin_dim
			
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

$Log: convert.c,v $
Revision 1.42  2001/05/22 20:12:21  rswamis
Added PostScript Format in the write_Image and getImage_Format functions

Revision 1.41  2001/05/02 14:47:11  zlin
add transform compression TRCM stuff

Revision 1.40  2000/03/08 18:07:54  rswamis
Added XVQ in getFormat_CVIP function , in write_Image function.

Revision 1.39  1999/11/17 00:53:27  ycheng
added case XVQ in write_image().

Revision 1.38  1999/10/03 22:27:17  lguo
cheked out by wzheng, do not know what was changed.

Revision 1.37  1998/03/10 04:26:27  smakam
made changes corresponding to including a new compression method fractal

Revision 1.36  1998/02/12 20:25:47  smakam
changed DPCM -DPC

Revision 1.35  1997/09/12 20:18:45  smakam
removed the unwanted messages for invalid image formats

Revision 1.34  1997/06/16 19:25:57  yawei
added type cast for SGI

Revision 1.33  1997/05/30 19:52:49  yawei
modified for JPG/TIF?

Revision 1.32  1997/05/21 03:21:49  yawei
added WIN32 fopen

Revision 1.31  1997/05/19 20:04:48  yawei
added WIN32 STDC support

Revision 1.30  1997/05/15 19:55:05  kcai
Added WIN32 for Windows95 porting

Revision 1.29  1997/05/09 16:08:33  yawei
fixed the seg fault error on failure of reading images

Revision 1.28  1997/05/05 18:06:33  yawei
added ZVL support for get image format

Revision 1.27  1997/05/02 17:02:35  yawei
modified BIN read setup

Revision 1.26  1997/04/29 15:27:43  yawei
added GIF support

Revision 1.25  1997/04/25 22:39:06  yawei
checked in for kui,

Revision 1.24  1997/04/18 22:45:30  yawei
modified read_Image and write_Image to fix problem of Image format.

Revision 1.23  1997/04/18 19:40:26  yawei
changed a little

Revision 1.22  1997/04/14 22:09:26  yawei
removed the second parameter for read_Image

Revision 1.21  1997/04/07 22:10:47  yawei
droppend GIF write support

Revision 1.20  1997/04/03 15:35:00  yawei
modified eps

Revision 1.19  1997/03/08 17:00:39  yawei
Swaped CVIP_YES and CVIP_NO

Revision 1.18  1997/03/08 00:43:27  yawei
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

Revision 1.17  1997/01/16 20:48:43  yawei
Global Change:  Image_FORMAT ==> IMAGE_FORMAT

 * Revision 1.16  1997/01/15  17:07:59  yawei
 * Global Change:  IMAGE ==> Image
 *
 * Revision 1.15  1996/12/14  03:33:26  yawei
 * 1) Added support for ZON, and ZON2 in the getFormat_CVIP() function
 * 2) Added support in the cviptovip() and viptocvip().
 *
 * Revision 1.14  1996/11/20  16:34:42  yawei
 * Changed hardcoded compress file name flag to global array
 *
 * Revision 1.13  1996/04/04  00:28:56  mzuke
 * commented out message about 'decision loop'
 *
 * Revision 1.12  1996/02/02  22:02:00  akjoele
 * Added SAFVR format and fixed bug.
 *
 * Revision 1.11  1996/02/02  22:01:29  akjoele
 * *** empty log message ***
 *
 * Revision 1.10  1996/01/19  22:13:54  kluo
 * change read_Image so that format argument is not necessarily needed.
 *
 * Revision 1.9  1996/01/19  22:06:50  mzuke
 * Change the prompt, add (g/c) in the prompt.
 * This log message was written by kluo on Friday afternoon.
 * I couldn't find mark and I really need to use convert.c
 * so I checked it in for Mark.
 *
 * Revision 1.8  1995/11/03  22:44:58  kluo
 * add dpcm.
 *
 * Revision 1.7  1995/10/16  22:29:20  akjoele
 * Changed call to CVIP_luminance to become call to luminance_Image()
 * because of changes in the luminance transform function.
 *
 * Revision 1.6  1995/10/16  17:53:27  kluo
 * add various compression
 *
 * Revision 1.5  1995/08/25  01:43:07  kluo
 * change read image so that image format doesn't depend on extension for standard
 * image formats.
 *
 * Revision 1.4  1995/06/19  20:59:33  kluo
 * change so that .bw .sgi and .rgb are regarded as iris
 *
 * Revision 1.3  1995/06/16  05:04:41  luok
 * add iris file format
 *
 * Revision 1.2  1994/12/21  07:21:58  luok
 * check file into RCS
 *
 * Revision 1.1  1993/05/31  07:10:10  hanceg
 * Initial revision
 *

*****************************************************************************/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#ifndef WIN32
#include <unistd.h>
#else
#define R_OK 4
#define W_OK 2
#endif
#include "CVIPimage.h"
#include "CVIPhalftone.h"
#include "CVIPluminance.h"
#include "CVIPconutils.h"
#include "CVIPgif.h"
#include "CVIPras.h"
#include "CVIPpnm.h"
#include "CVIPccc.h"
#include "CVIPtiff.h"
#include "CVIPitex.h"
#include "CVIPeps.h"
#include "CVIPps.h"
#include "CVIPbin.h"
#include "CVIPmagic.h"
#include "CVIPvip.h"
#include "pnm.h"
#include "CVIPcompress.h"

extern char temp_dir[100];
extern char *Cmpr_Name[];
extern char *image_format_string[];


/******************************************************************
   MAKE_LOWER_CASE - a little macro to force the ascii character
		     (x) into lower case. This was written before
		     I discovered the ANSI function tolower(); which
		     will do the same thing... and I thought I was 
		     special.
*******************************************************************/
#define MAKE_LOWER_CASE(x) (((x)&0xF0)==0x40) ? (((x)&0x0F)|0x60) : ((((x)&0xF0)==0x50) ? (((x)&0x0F)|0x70) : (x))

/******************************************************************
    grayOK - macro to specify if the image format supports gray level
             formats... where (tag) is one of the Format tags specified
	     in the the function CVIPwriteimage below
*******************************************************************/
#define grayOK(tag) (((tag)&0x03) != 0)

static IMAGE_FORMAT CVIPgetmagic(const char *filename, unsigned long* magic, FILE *fd);
static void pnm_setup(Image *, char *, FILE *, CVIP_BOOLEAN);
static void eps_setup(Image *, char *, FILE *, int, CVIP_BOOLEAN);
static void itex_setup(Image *, char *, FILE *, CVIP_BOOLEAN);
static void iris_setup(Image *, char *, FILE *, CVIP_BOOLEAN);
static void ras_setup(Image *, char *, FILE *, CVIP_BOOLEAN);
static void gif_setup(Image *, char *, FILE *, CVIP_BOOLEAN);
static void ccc_setup(Image *, char *, FILE *, CVIP_BOOLEAN);
static void tiff_setup(Image *, char *, CVIP_BOOLEAN);
static void bin_wsetup(Image *, char *, FILE *, CVIP_BOOLEAN);
static Image *bin_rsetup(char *, FILE *, CVIP_BOOLEAN);
static int guess_bin_dim(FILE *,int*);


/****************************************************************
                  Name: getFormat_CVIP
         Expanded Name: Get Format CVIPtools
            Parameters: filename - pointer to character string containing
				   the name of the file name.
               Returns: The FORMAT of the image. One of... PBM, PGM, PPM, EPS,
			TIF, GIF, RAS, ITX, CCC, BIN, VIP, GLR, BTC or BRC.
           Description: This function will read the name of filename passed
			to it and and return the enumerated type name of the
			function based on the filename extension. The function
			is case insensitive.
			There is no extension requirement with file now(Kun Luo)
           Diagnostics: returns (-1) w/ corresponding error message when...
				- filename has no extension (obviously)
				- the extension is not recognizable. 
				  acceptable extensions are ...
					.ccc - Color Cell Compression Format
					.bin or .pic - Raw Image File Format
                                        .glr - Gray Level Runlength Coding Format
                                        .btc - Block Truncation Coding Format
                                        .brc - Bitplane Runlength Coding Format
					.huf - Huffman Coding Format
             Credit(s): Kun Luo, Greg Hance
			
****************************************************************/
int getFormat_CVIP(char *filename)
{
    char *strptr, ext[4], function_name[] = {"CVIPgetformat"};
    IMAGE_FORMAT format;
    FILE * fptr;
    byte magic[21];
    int pos, psize;	/* psize=potential size of the image (SAVFR format) */
	 #ifndef WIN32
    struct stat *buf;	/* info about the file */
	 #else
    struct _stat *buf;	/* info about the file */
	 #endif

	 #ifndef WIN32
    fptr = fopen(filename,"r");
	 #else
    fptr = fopen(filename,"rb");
	 #endif
    if(fptr == NULL)
	return -1;
    fread(magic,20,1, fptr);
    fclose(fptr);
    if(strncmp((char*)magic,"BM",2) == 0)
	return BMP;
    if(strncmp((char*)magic,"P1",2) == 0 || strncmp((char*)magic,"P4",2) == 0)
	return PBM;
    if(strncmp((char*)magic,"P2",2) == 0 || strncmp((char*)magic,"P5",2) == 0)
	return PGM;
    if(strncmp((char*)magic,"P3",2) == 0 || strncmp((char*)magic,"P6",2) == 0)
	return PPM;
    if(strncmp((char*)magic,"%!",2) == 0)
	return EPS;
    if(strncmp((char*)magic,"%!PS",4) == 0)
	return PS;
    if(strncmp((char*)magic,"MM",2)==0 || strncmp((char*)magic,"II",2)==0 )
	return TIF;
    if(strncmp((char*)magic,"vq",2) == 0)
	return VQ;
    if(strncmp((char*)magic,"xvq",2) == 0)
	return XVQ;
    if(strncmp((char*)magic,"GIF87a",6) == 0 || 
	strncmp((char*)magic,"GIF89a",6) == 0)
	return GIF;
    if(magic[0] == (byte)0x59 && magic[1] == (byte) 0xa6 &&
	   magic[2] == (byte)0x6a && magic[3] == (byte)0x95) 
	return RAS;
    if(strncmp((char*)magic,"IM",2) == 0)
	return ITX;
    if ((magic[0] == (byte)0x01 && magic[1] == (byte)0xda) ||
	   (magic[0] == (byte)0xda && magic[1] == (byte)0x01))
	return IRIS;
    if(strncmp((char*)magic,"ViP",3) == 0)
	return VIP;
    if(strncmp((char*)magic,"btc",3) == 0)
	return BTC;
    if(strncmp((char*)magic,"glr",3) == 0)
	return GLR;
    if(strncmp((char*)magic,"huf",3) == 0)
	return HUF;
    if(strncmp((char*)magic,"fra",3) == 0)
	return FRA;
    if(strncmp((char*)magic,"brc",3) == 0)
	return BRC;
    if(strncmp((char*)magic,"b2tc",4) == 0)
	return BTC2;
    if(strncmp((char*)magic,"b3tc",4) == 0)
	return BTC3;
    if(strncmp((char*)magic,"dpcm",4) == 0)
	return DPC;
    if(strncmp((char*)magic,"ZON",3) == 0)
	return ZON;
    if(strncmp((char*)magic,"ZON2",4) == 0)
	return ZON2;
    if (magic[0] == (byte)0xff && magic[1] == (byte)0xd8)
	return JPG;
    if(strncmp((char*)magic,"ZVL",3) == 0)
	return ZVL;
	if (magic[4] == 'j' && magic[5] == 'P')
		return JP2;
	if (magic[1] == 80 && magic[2] == 78 && magic[3] == 71)
		return PNG;

   if(!(strcmp(filename, "-")))			
         return 0;
/* 
 * The following is a major hack designed to
 * detect the presence of a SAFVR image format.  This format
 * uses 32-bit values to represent image parameters.  What we'll
 * do is read in the image height and width from the place in
 * the file where they should be, calculate the image size
 * based on these values, and check the resulting size against
 * the size of the file. You'd think the navy people would have
 * included a magic number in their file format.
 *
 * Arve Kjoelen - Thu Feb  1 13:24:02 CST 1996
 */
   psize=0;
   if(!(int)(magic[12]) && !(int)(magic[16]) && !(int)magic[13] && !(int)magic[17] && !(int)(magic[4]) && !(int)magic[5] && !(int)magic[6] ) { 
						 /* if these aren't 0, we're
						 dealing with images with
						 dimensions greater than
						 2^^15 - not likely */
      psize+=(int)(magic[14])<<8;
      psize+=(int)magic[15];
      pos=psize;	/* store number of rows here. */
      psize=(int)(magic[18])<<8;
      psize+=(int)magic[19];
      psize*=pos;
      if((int)(magic[7])==1) psize*=3; /* color */ 
      else if(!(int)(magic[7])) psize=psize*1;  
      else psize=0;
   
   }
   if(psize!=0) { /* psize should be set here if we think there's
		     an SAVFR image lurking. */
		#ifndef WIN32
      buf=(struct stat *)malloc(sizeof(struct stat));
      if (stat(filename, buf)==-1) {
		#else
      buf=(struct _stat *)malloc(sizeof(struct _stat));
      if (_stat(filename, buf)==-1) {
		#endif
         fprintf(stderr, "getFormat_CVIP: error: stat(%s) failed!\n", filename);
	 return(-1);
      }
      if((int)(buf->st_size)==psize+24) {
         fprintf(stderr, "Found SAFVR Image\n");
	 return(SAFVR);
      }
   }
/*   fprintf(stderr, "Done with decision loop - dodn't mess abything up\n"); */

   if ( (strptr = (char *) strrchr(filename, '.'))==NULL ) {
      /*fprintf(stderr,"%s: image file must have extension.\n",function_name);
      fprintf(stderr,"%s: (e.g.) .ccc .bin .et cetera\n",function_name);*/
      return(-1);
   }
   else {
      strptr++;
      ext[0] = MAKE_LOWER_CASE(strptr[0]); 
      ext[1] = MAKE_LOWER_CASE(strptr[1]);
      ext[2] = MAKE_LOWER_CASE(strptr[2]);
      ext[3] = '\0';
      if(!(strcmp(ext, "ccc")))
         return CCC;
      else if(!(strcmp(ext, "eps")))
         return EPS;
      else if(!(strcmp(ext, "ps")))
         return PS;
      else if(!(strcmp(ext, "bin")) || !(strcmp(ext, "pic")) )
         return BIN;
      else if(!(strcmp(ext, "glr")))
         return GLR;
      else if(!(strcmp(ext, "brc")))
         return BRC;
      else if(!(strcmp(ext, "huf")))
         return HUF;
      else {
         /*fprintf(stderr,"%s: Image file extension .%s is not recognized.\n", function_name, ext);
	 fprintf(stderr,"%s: formats supported...\n", function_name);
	 fprintf(stderr,"%s: Filetype  Description                          Operations\n", function_name);
	 fprintf(stderr,"%s: ========  ===========                          ===========\n", function_name);
         fprintf(stderr,"%s: gif	Graphics Interchange Format	     read  write\n", function_name);
         fprintf(stderr,"%s: itx	ITEX Framegrabber Files	             read  write\n", function_name);
         fprintf(stderr,"%s: pbm	Jef Poskanzer's Portable Bitmaps     read  write\n", function_name);
         fprintf(stderr,"%s: pgm	Jef Poskanzer's Portable Graymaps    read  write\n", function_name);
         fprintf(stderr,"%s: ppm	Jef Poskanzer's Portable Pixmaps     read  write\n", function_name);
         fprintf(stderr,"%s: eps	PostScript Encapsulated Files	     read  write\n", function_name);
         fprintf(stderr,"%s: ps		PostScript  Files		     read  write\n", function_name);
         fprintf(stderr,"%s: ras	Sun Rasterfiles	                     read  write\n", function_name);
         fprintf(stderr,"%s: tiff	Tagged Image File Format	     read  write\n", function_name);
	 fprintf(stderr,"%s: ccc	Color Cell Compression Utility	     read  write\n", function_name);
	 fprintf(stderr,"%s: bin	Raw Binary Image Data	             read  write\n", function_name);
	 fprintf(stderr,"%s: glr	Gray-Level Runlength Coding          read  write\n", function_name);
	 fprintf(stderr,"%s: btc	Block Truncation Coding	             read  write\n", function_name);
	 fprintf(stderr,"%s: brc	Bitplane Runlength Coding	     read  write\n", function_name);
	 fprintf(stderr,"%s: huf	Huffman (entropy) Coding	     read  write\n", function_name);
	 fprintf(stderr,"%s: jpg	Joint Photographic Experts Group     read  write\n", function_name);*/
	 return(-1);
      }
   }
}

/****************************************************************
                  Name: read_Image
         Expanded Name: Read Image
            Parameters: filename - pointer to a character string
				   containing the file name of the image
				   to be loaded
			showmessages - shall I be verbose?
               Returns: pointer to newly allocated Image structure loaded with
			data from image <filename>.
           Description: loads an Image structure with data from the
			specified image file <filename> with format <format>. 
			All data members of the structure are initialized to
			the specifications of the image file read in.
           Diagnostics: returns a NULL pointer w/ corresponding error message
			when...
				- format is not recognized
				- the image file specified does not
				  conform to the standards of the format
				  specified
             Credit(s): Greg Hance
			
****************************************************************/
Image *read_Image(char *filename, int showmessages)
{
   Image *cvip_Image;
   FILE *fd;
   const char *fn = "read_Image";
   unsigned long magic = 0;
	IMAGE_FORMAT format, r_format;

   format = (IMAGE_FORMAT)getFormat_CVIP(filename);
	CVIPinit("read_Image", 1);

   if( format != TIF )
      fd = CVIPopenr( filename );
 
   if(!(strcmp(filename, "-")))
      if( (format = CVIPgetmagic(filename, &magic, fd)) == -1 ) {
         error_CVIP(fn, "ERROR reading stdin ...\n");
         error_CVIP(fn, "can't determine file type from magic number.\n");
         CVIPclose ( fd );
         return NULL;
      }

   if( !strcmp(filename,"-") )
      filename = "Standard Input";


   switch(format) {
      case BMP: cvip_Image = (Image *) bmptocvip(filename, fd, (int) magic, showmessages); break;
      case PBM:
      case PGM:
      case PPM: cvip_Image = (Image *) pnmtocvip(filename, fd, (int) magic, showmessages); break;
      case EPS: cvip_Image = (Image *) epstocvip(filename, fd, showmessages); break;
      case TIF: cvip_Image = (Image *) tifftocvip(filename, showmessages); break;
      case GIF: cvip_Image = (Image *) giftocvip(filename, fd, 1, showmessages); break;
      case RAS: cvip_Image = (Image *) rastocvip(filename, fd, showmessages); break;
      case IRIS: cvip_Image = (Image *) iristocvip(filename,fd,showmessages); break;
      case ITX: cvip_Image = (Image *) itextocvip(filename, fd, showmessages); break;
      case CCC: cvip_Image = (Image *) ccctocvip(filename, fd, showmessages); break;
      case VIP: cvip_Image = (Image *) viptocvip(filename, fd, showmessages); break;
      case BIN: cvip_Image = (Image *) bin_rsetup(filename, fd, showmessages); break;
      case JPG: cvip_Image = (Image *)jpgtocvip(filename, 256, CVIP_NO, CVIP_NO, CVIP_NO, 
					(CVIP_BOOLEAN)showmessages); break;
	  case JP2: cvip_Image = (Image *) jp2tocvip(filename); break;
	  case PNG: cvip_Image = (Image *) pngtocvip(filename); break;
      case SAFVR: cvip_Image = (Image *) safvrtocvip(filename, fd, showmessages); break;
      default:  error_CVIP(fn, "not a valid CVIP image format\n"); return NULL;
   }

   if (NULL == cvip_Image) return NULL;

   if( format != TIF && format != IRIS)
      CVIPclose( fd );
	r_format = cvip_Image->image_format;
	if (format == VIP    && r_format != GLR &&
		 r_format != BTC  && r_format != BRC &&
		 r_format != HUF  && r_format != ZVL &&
		 r_format != BTC2 && r_format != BTC2 &&
		 r_format != BTC3 && r_format != DPC &&
		 r_format != ZON  && r_format != ZON2 &&
		 r_format != FRA && r_format != VQ && 
		 r_format != XVQ && r_format != TRCM) cvip_Image->image_format = VIP;
   return cvip_Image;
}
 

/****************************************************************
                  Name: write_Image
         Expanded Name: Write Image
            Parameters:   cvip_Image - pointer to valid CVIP Image structure
		            filename - pointer to a character string
				       containing the file name of the image
				       to be loaded
		        retain_image - should the image be retained after
				       writing it out to disk or can I go ahead 
				       and free it's memory. (CVIP_YES or CVIP_NO)?
			      set_up - do you want a set-up routine to
				       be run for the image (CVIP_YES or CVIP_NO)?
			  new_format - enumeration constant specifying the
				       format of the file to be read in.
				       One of... PBM, PGM, PPM, EPS, TIF, GIF,
				       RAS, ITX, CCC, BIN or VIP.
			showmessages - shall I be verbose (CVIP_YES or CVIP_NO)?
               Returns: pointer to newly allocated Image structure loaded with
			data from image <filename>.
           Description: writes the contents of a CVIP Image structure out
			to disk in the specified format <new_format>. Many
			of the formats offer variations on the way a 
			file can be presented to disk. (e.g. compression
			schemes, byte ordering, etc..) To take full 
			advantage of this a set-up routine can be run
			by setting <set-up> equal to CVIP_YES; otherwise, 
			default options will be used. Set-up routines
			vary for each format.
           Diagnostics: Varies for each format. Can be suppressed
			considerably by setting showmessages equal to CVIP_NO
             Credit(s): Greg Hance
			
****************************************************************/
int  write_Image(Image *cvip_Image, char *filename, CVIP_BOOLEAN retain_image, CVIP_BOOLEAN set_up, IMAGE_FORMAT new_format, CVIP_BOOLEAN showmessages)
{
	
	 
   byte ftag[12] =   {0x01, 0x02,  0x04,  0x02,  0x07,  0x04,  0x07,  0x02,  0x07,0x04,  0x07, 0x07};
   char *color[] = {"BINARY", "GRAYSCALE", "RGB"}, function_name[] = {"write_Image"};
   IMAGE_FORMAT cvip_format;
   COLOR_FORMAT cvip_color;
   FILE *fd;
   Image *copy;
   int i;

   //xchen add this so the code is only compatible with COM interface.
   for (i = 0; i < 17; i++)
		Cmpr_Name[i] = "";

   if(new_format != TIF)
      	if(!(fd = openWrite_CVIP(filename, CVIP_NO))) {
		error_CVIP("write_Image", "could not open file %s for writing.\n", filename);
		return 0;
	}

   if( !strcmp(filename,"-") )
      filename = "Standard Output";

   cvip_format = cvip_Image->image_format;
   cvip_color = cvip_Image->color_space;
   
 /*  if(set_up == CVIP_NO) 
      new_format = cvip_format;*/
   
   if(set_up != CVIP_NO) 
      if( cvip_color==BINARY || cvip_color==GRAY_SCALE)    
         if(!grayOK(ftag[new_format])) {
            fprintf(stderr, "\n%s: conversion from %s %s to %s is not supported.\n",function_name, color[cvip_color],image_format_string[cvip_format],image_format_string[new_format]);
	    fprintf(stderr, "%s: must do pseudo color mapping first.\n\n",function_name);
	    return(0);
         }	 
    
	 
   switch(new_format) {
//switch(cvip_Image->image_format ) {    
 case BTC2:
      case DPC:
      case BTC3:
      case ZON:
      case ZON2:
      case BTC:
      case GLR:
      case BRC:
      case ZVL:
      case FRA:
      case VQ:
      case XVQ:
      case TRCM:
      case HUF:
		  printf("File is transfered to PNM format\n");
      case PBM:   
      case PGM:
      case PPM:   if(set_up == CVIP_NO) 
                     cviptopnm(cvip_Image, filename, fd, showmessages); 
		  else
		     pnm_setup(cvip_Image, filename, fd, showmessages);
		  break;
      case EPS:   if(set_up == CVIP_NO)
                     cviptoeps(cvip_Image, filename, fd, 1.0, 1.0, -1, showmessages); 
		  else
		     eps_setup(cvip_Image, filename, fd, -1, showmessages);
		  break;
      case PS:    cviptops(cvip_Image, filename); 
		  break;
      case TIF:   if(set_up == CVIP_NO)
                     cviptotiff(cvip_Image, filename, COMPRESSION_LZW, FILLORDER_MSB2LSB, CVIP_NO, CVIP_NO, CVIP_NO, showmessages); 
		  else
		     tiff_setup(cvip_Image, filename, showmessages);
		  break;		     
      case GIF:   
      		  if(set_up == CVIP_NO)
                     cviptogif(cvip_Image, filename, fd, CVIP_NO, showmessages); 
		  else
		     gif_setup(cvip_Image, filename, fd, showmessages); 
		  break;
      case BMP:   
              cviptobmp(cvip_Image, filename, fd, showmessages); 
		  break;
      case RAS:   if(set_up == CVIP_NO)
                     cviptoras(cvip_Image, filename, fd, RT_CVIP_BYTE_ENCODED, showmessages); 
                  else
		     ras_setup(cvip_Image, filename, fd, showmessages);
                  break;
      case ITX:   if(set_up == CVIP_NO)
                     cviptoitex(cvip_Image, filename, fd, "CVIP: Converter Utility by Greg Hance", showmessages);
		  else
		     itex_setup(cvip_Image, filename, fd, showmessages);
		  break;
      case IRIS:
  		 if(set_up == CVIP_NO)
                     cviptoiris(cvip_Image, filename, fd, "CVIP: Converter Utility by Kun Luo", showmessages);
		  else
		     iris_setup(cvip_Image, filename, fd, showmessages);
		  break;

      case CCC:   if(set_up == CVIP_NO)
                     cviptoccc(cvip_Image, filename, fd, MAXCOLORS, CVIP_NO, showmessages);
		  else
		     ccc_setup(cvip_Image, filename, fd, showmessages);	     
		  break;
      case JPG:   
		copy = (Image *)duplicate_Image(cvip_Image);
      		if(set_up == CVIP_NO)
                     cviptojpg(copy, filename, 75, CVIP_NO, CVIP_NO, 0,  showmessages, NULL);
		  else
		     printf("cvip_setup has not to be written");
		     /* cvip_setup(cvip_Image, filename, fd, showmessages); */	     
		  break;
	  case JP2:
		  copy = (Image *)duplicate_Image(cvip_Image);
      		if(set_up == CVIP_NO)
				cviptojp2(copy, filename, 1, -1, 1, 64);
		  else
		     printf("cvip_setup has not to be written");
		     /* cvip_setup(cvip_Image, filename, fd, showmessages); */
			break;
	  case PNG:
			copy = (Image *)duplicate_Image(cvip_Image);
      		if(set_up == CVIP_NO)
				cviptopng(copy, filename);
			else
		     printf("cvip_setup has not to be written");
		     /* cvip_setup(cvip_Image, filename, fd, showmessages); */
			break;
	  case VIP:  {
		 char file_name[150];
		 strcpy(file_name,temp_dir);
		 //xchen comment this out
		 //strcat(file_name,"/");
		 strcat(file_name,filename);
		
	 
		 switch(cvip_Image->image_format){
			case BTC:
				strcat(file_name,"__"); strcat(file_name, Cmpr_Name[Btc]);
				if(access(file_name,R_OK)== -1){
		 		     cviptovip(cvip_Image, filename, fd,CVIP_YES,CVIP_NO, showmessages);
				}
				else
				     cviptovip(cvip_Image,file_name,fd,CVIP_YES,CVIP_YES,showmessages);
				break;
			case BTC2:
				strcat(file_name,"__"); strcat(file_name, Cmpr_Name[Btc2]);
				if(access(file_name,R_OK)== -1){
		 		     cviptovip(cvip_Image, filename, fd,CVIP_YES,CVIP_NO, showmessages);
				}
				else
				     cviptovip(cvip_Image,file_name,fd,CVIP_YES,CVIP_YES,showmessages);
				break;
			case BTC3:
				strcat(file_name,"__"); strcat(file_name, Cmpr_Name[Btc3]);
				if(access(file_name,R_OK)== -1){
		 		     cviptovip(cvip_Image, filename, fd,CVIP_YES,CVIP_NO, showmessages);
				}
				else
				     cviptovip(cvip_Image,file_name,fd,CVIP_YES,CVIP_YES,showmessages);
				break;
			case DPC:
				strcat(file_name,"__"); strcat(file_name, Cmpr_Name[Dpcm]);
				if(access(file_name,R_OK)== -1){
		 		     cviptovip(cvip_Image, filename, fd,CVIP_YES,CVIP_NO, showmessages);
				}
				else
				     cviptovip(cvip_Image,file_name,fd,CVIP_YES,CVIP_YES,showmessages);
				break;
			case GLR:
				strcat(file_name,"__"); strcat(file_name, Cmpr_Name[Glr]);
				if(access(file_name,R_OK)== -1){
		 		     cviptovip(cvip_Image, filename, fd,CVIP_YES,CVIP_NO, showmessages);
				}
				else
				     cviptovip(cvip_Image,file_name,fd,CVIP_YES,CVIP_YES,showmessages);
				break;
			case HUF:
				strcat(file_name,"__"); strcat(file_name, Cmpr_Name[Huf]);
				if(access(file_name,R_OK)== -1){
		 		     cviptovip(cvip_Image, filename, fd,CVIP_YES,CVIP_NO, showmessages);
				}
				else
				     cviptovip(cvip_Image,file_name,fd,CVIP_YES,CVIP_YES,showmessages);
				break;
			case FRA:
				strcat(file_name,"__"); strcat(file_name, Cmpr_Name[Fra]);
				if(access(file_name,R_OK)== -1){
		 		     cviptovip(cvip_Image, filename, fd,CVIP_YES,CVIP_NO, showmessages);
				}
				else
				     cviptovip(cvip_Image,file_name,fd,CVIP_YES,CVIP_YES,showmessages);
				break;
			case VQ:
				strcat(file_name,"__"); strcat(file_name, Cmpr_Name[Vq]);
				if(access(file_name,R_OK)== -1){
		 		     cviptovip(cvip_Image, filename, fd,CVIP_YES,CVIP_NO, showmessages);
				}
				else
				     cviptovip(cvip_Image,file_name,fd,CVIP_YES,CVIP_YES,showmessages);
				break;
			case XVQ:  
			        strcat(file_name,"__"); strcat(file_name, Cmpr_Name[Xvq]);
				if(access(file_name,R_OK)== -1){
		 		     cviptovip(cvip_Image, filename, fd,CVIP_YES,CVIP_NO, showmessages);
				}
				else
				     cviptovip(cvip_Image,file_name,fd,CVIP_YES,CVIP_YES,showmessages);
                                break;
			case TRCM:  
			        strcat(file_name,"__"); strcat(file_name, Cmpr_Name[Trcm]);
				if(access(file_name,R_OK)== -1){
		 		     cviptovip(cvip_Image, filename, fd,CVIP_YES,CVIP_NO, showmessages);
				}
				else
				     cviptovip(cvip_Image,file_name,fd,CVIP_YES,CVIP_YES,showmessages);
                                break;
			case BRC:
				strcat(file_name,"__"); strcat(file_name, Cmpr_Name[Brc]);
				if(access(file_name,R_OK)== -1){
		 		     cviptovip(cvip_Image, filename, fd,CVIP_YES,CVIP_NO, showmessages);
				}
				else
				     cviptovip(cvip_Image,file_name,fd,CVIP_YES,CVIP_YES,showmessages);
				break;
			case ZVL:
				strcat(file_name,"__"); strcat(file_name, Cmpr_Name[Zvl]);
				if(access(file_name,R_OK)== -1){
		 		     cviptovip(cvip_Image, filename, fd,CVIP_YES,CVIP_NO, showmessages);
				}
				else
				     cviptovip(cvip_Image,file_name,fd,CVIP_YES,CVIP_YES,showmessages);
				break;
			case ZON:
				strcat(file_name,"__"); strcat(file_name, Cmpr_Name[Zon]);
				if(access(file_name,R_OK)== -1){
		 		     cviptovip(cvip_Image, filename, fd,CVIP_YES,CVIP_NO, showmessages);
				}
				else
				     cviptovip(cvip_Image,file_name,fd,CVIP_YES,CVIP_YES,showmessages);
				break;
			case ZON2:
				strcat(file_name,"__"); strcat(file_name, Cmpr_Name[Zon2]);
				if(access(file_name,R_OK)== -1){
		 		     cviptovip(cvip_Image, filename, fd,CVIP_YES,CVIP_NO, showmessages);
				}
				else
				     cviptovip(cvip_Image,file_name,fd,CVIP_YES,CVIP_YES,showmessages);
				break;
			default:	
		 		cviptovip(cvip_Image, filename, fd,CVIP_YES,CVIP_NO, showmessages);    
		 }
		 } 
		  break;

      case BIN:   if(set_up == CVIP_NO)
                     cviptobin(cvip_Image, filename, fd, ORD_RGB, INTERPIXEL, showmessages); 
		  else
		     bin_wsetup(cvip_Image, filename, fd, showmessages);
		  break;
      default:  fprintf(stderr, "CVIPwriteimage: not a valid CVIP image format\n"); return 0;
   }
   
if(!retain_image) {
   image_free(cvip_Image);
   if(showmessages)
      msg_CVIP(function_name, "freeing image structure.\n");
}

if( new_format != TIF && new_format != JPG)
   CVIPclose( fd );

return 1;
}

/****************************************************************
                  Name: write_JPEG_Image
         Expanded Name: Write JPEG Image
            Parameters:   cvip_Image - pointer to valid CVIP Image structure
		            filename - pointer to a character string
				       containing the file name of the image
				       to be loaded
		        retain_image - should the image be retained after
				       writing it out to disk or can I go ahead 
				       and free it's memory. (CVIP_YES or CVIP_NO)?
			      set_up - do you want a set-up routine to
				       be run for the image (CVIP_YES or CVIP_NO)?
			  new_format - enumeration constant specifying the
				       format of the file to be read in.
				       One of... PBM, PGM, PPM, EPS, TIF, GIF,
				       RAS, ITX, CCC, BIN or VIP.
			showmessages - shall I be verbose (CVIP_YES or CVIP_NO)?
				   ratio - specifies compression ratio
               Returns: 1 on success
           Description: writes the contents of a CVIP Image structure out
			to disk in the specified format <new_format>. Many
			of the formats offer variations on the way a 
			file can be presented to disk. (e.g. compression
			schemes, byte ordering, etc..) To take full 
			advantage of this a set-up routine can be run
			by setting <set-up> equal to CVIP_YES; otherwise, 
			default options will be used. Set-up routines
			vary for each format.
           Diagnostics: Varies for each format. Can be suppressed
			considerably by setting showmessages equal to CVIP_NO
             Credit(s): Greg Hance, Serkan Kefel
			
****************************************************************/

int  write_JPEG_Image(Image *cvip_Image, char *filename, CVIP_BOOLEAN retain_image, CVIP_BOOLEAN set_up, IMAGE_FORMAT new_format, CVIP_BOOLEAN showmessages, int ratio)
{
   byte ftag[12] =   {0x01, 0x02,  0x04,  0x02,  0x07,  0x04,  0x07,  0x02,  0x07,0x04,  0x07, 0x07};
   char *color[] = {"BINARY", "GRAYSCALE", "RGB"}, function_name[] = {"write_JPEG_Image"};
   IMAGE_FORMAT cvip_format;
   COLOR_FORMAT cvip_color;
   FILE *fd;
   Image *copy;
   int i;

   //xchen add this so the code is only compatible with COM interface.
   for (i = 0; i < 17; i++)
		Cmpr_Name[i] = "";

   if(new_format != TIF)
      	if(!(fd = openWrite_CVIP(filename, CVIP_NO))) {
		error_CVIP("write_JPEG_Image", "could not open file %s for writing.\n", filename);
		return 0;
	}

   if( !strcmp(filename,"-") )
      filename = "Standard Output";

   cvip_format = cvip_Image->image_format;
   cvip_color = cvip_Image->color_space;
   
 /*  if(set_up == CVIP_NO) 
      new_format = cvip_format;*/

   if(set_up != CVIP_NO) 
      if( cvip_color==BINARY || cvip_color==GRAY_SCALE)    
         if(!grayOK(ftag[new_format])) {
            fprintf(stderr, "\n%s: conversion from %s %s to %s is not supported.\n",function_name, color[cvip_color],image_format_string[cvip_format],image_format_string[new_format]);
	    fprintf(stderr, "%s: must do pseudo color mapping first.\n\n",function_name);
	    return(0);
         }	 
   
   switch(new_format) {
      case BTC2:
      case DPC:
      case BTC3:
      case ZON:
      case ZON2:
      case BTC:
      case GLR:
      case BRC:
      case ZVL:
      case FRA:
      case VQ:
      case XVQ:
      case TRCM:
      case HUF:
		  printf("File is transfered to PNM format\n");
      case PBM:   
      case PGM:
      case PPM:   if(set_up == CVIP_NO) 
                     cviptopnm(cvip_Image, filename, fd, showmessages); 
		  else
		     pnm_setup(cvip_Image, filename, fd, showmessages);
		  break;
      case EPS:   if(set_up == CVIP_NO)
                     cviptoeps(cvip_Image, filename, fd, 1.0, 1.0, -1, showmessages); 
		  else
		     eps_setup(cvip_Image, filename, fd, -1, showmessages);
		  break;
      case PS:    cviptops(cvip_Image, filename); 
		  break;
      case TIF:   if(set_up == CVIP_NO)
                     cviptotiff(cvip_Image, filename, COMPRESSION_LZW, FILLORDER_MSB2LSB, CVIP_NO, CVIP_NO, CVIP_NO, showmessages); 
		  else
		     tiff_setup(cvip_Image, filename, showmessages);
		  break;		     
      case GIF:   
      		  if(set_up == CVIP_NO)
                     cviptogif(cvip_Image, filename, fd, CVIP_NO, showmessages); 
		  else
		     gif_setup(cvip_Image, filename, fd, showmessages); 
		  break;
      case BMP:   
              cviptobmp(cvip_Image, filename, fd, showmessages); 
		  break;
      case RAS:   if(set_up == CVIP_NO)
                     cviptoras(cvip_Image, filename, fd, RT_CVIP_BYTE_ENCODED, showmessages); 
                  else
		     ras_setup(cvip_Image, filename, fd, showmessages);
                  break;
      case ITX:   if(set_up == CVIP_NO)
                     cviptoitex(cvip_Image, filename, fd, "CVIP: Converter Utility by Greg Hance", showmessages);
		  else
		     itex_setup(cvip_Image, filename, fd, showmessages);
		  break;
      case IRIS:
  		 if(set_up == CVIP_NO)
                     cviptoiris(cvip_Image, filename, fd, "CVIP: Converter Utility by Kun Luo", showmessages);
		  else
		     iris_setup(cvip_Image, filename, fd, showmessages);
		  break;

      case CCC:   if(set_up == CVIP_NO)
                     cviptoccc(cvip_Image, filename, fd, MAXCOLORS, CVIP_NO, showmessages);
		  else
		     ccc_setup(cvip_Image, filename, fd, showmessages);	     
		  break;
      case JPG:   
		copy = (Image *)duplicate_Image(cvip_Image);
      		if(set_up == CVIP_NO)
                     cviptojpg(copy, filename, ratio, CVIP_NO, CVIP_NO, 0,  showmessages, NULL);
		  else
		     printf("cvip_setup has not to be written");
		     /* cvip_setup(cvip_Image, filename, fd, showmessages); */	     
		  break;
	  case JP2:
		  copy = (Image *)duplicate_Image(cvip_Image);
      		if(set_up == CVIP_NO)
				cviptojp2(copy, filename, ratio, -1, 1, 64);
		  else
		     printf("cvip_setup has not to be written");
		     /* cvip_setup(cvip_Image, filename, fd, showmessages); */
			break;
	  case PNG:
			copy = (Image *)duplicate_Image(cvip_Image);
      		if(set_up == CVIP_NO)
				cviptopng(copy, filename);
			else
		     printf("cvip_setup has not to be written");
		     /* cvip_setup(cvip_Image, filename, fd, showmessages); */
			break;
	  case VIP:  {
		 char file_name[150];
		 strcpy(file_name,temp_dir);
		 //xchen comment this out
		 //strcat(file_name,"/");
		 strcat(file_name,filename);
		 switch(cvip_Image->image_format){
			case BTC:
				strcat(file_name,"__"); strcat(file_name, Cmpr_Name[Btc]);
				if(access(file_name,R_OK)== -1){
		 		     cviptovip(cvip_Image, filename, fd,CVIP_YES,CVIP_NO, showmessages);
				}
				else
				     cviptovip(cvip_Image,file_name,fd,CVIP_YES,CVIP_YES,showmessages);
				break;
			case BTC2:
				strcat(file_name,"__"); strcat(file_name, Cmpr_Name[Btc2]);
				if(access(file_name,R_OK)== -1){
		 		     cviptovip(cvip_Image, filename, fd,CVIP_YES,CVIP_NO, showmessages);
				}
				else
				     cviptovip(cvip_Image,file_name,fd,CVIP_YES,CVIP_YES,showmessages);
				break;
			case BTC3:
				strcat(file_name,"__"); strcat(file_name, Cmpr_Name[Btc3]);
				if(access(file_name,R_OK)== -1){
		 		     cviptovip(cvip_Image, filename, fd,CVIP_YES,CVIP_NO, showmessages);
				}
				else
				     cviptovip(cvip_Image,file_name,fd,CVIP_YES,CVIP_YES,showmessages);
				break;
			case DPC:
				strcat(file_name,"__"); strcat(file_name, Cmpr_Name[Dpcm]);
				if(access(file_name,R_OK)== -1){
		 		     cviptovip(cvip_Image, filename, fd,CVIP_YES,CVIP_NO, showmessages);
				}
				else
				     cviptovip(cvip_Image,file_name,fd,CVIP_YES,CVIP_YES,showmessages);
				break;
			case GLR:
				strcat(file_name,"__"); strcat(file_name, Cmpr_Name[Glr]);
				if(access(file_name,R_OK)== -1){
		 		     cviptovip(cvip_Image, filename, fd,CVIP_YES,CVIP_NO, showmessages);
				}
				else
				     cviptovip(cvip_Image,file_name,fd,CVIP_YES,CVIP_YES,showmessages);
				break;
			case HUF:
				strcat(file_name,"__"); strcat(file_name, Cmpr_Name[Huf]);
				if(access(file_name,R_OK)== -1){
		 		     cviptovip(cvip_Image, filename, fd,CVIP_YES,CVIP_NO, showmessages);
				}
				else
				     cviptovip(cvip_Image,file_name,fd,CVIP_YES,CVIP_YES,showmessages);
				break;
			case FRA:
				strcat(file_name,"__"); strcat(file_name, Cmpr_Name[Fra]);
				if(access(file_name,R_OK)== -1){
		 		     cviptovip(cvip_Image, filename, fd,CVIP_YES,CVIP_NO, showmessages);
				}
				else
				     cviptovip(cvip_Image,file_name,fd,CVIP_YES,CVIP_YES,showmessages);
				break;
			case VQ:
				strcat(file_name,"__"); strcat(file_name, Cmpr_Name[Vq]);
				if(access(file_name,R_OK)== -1){
		 		     cviptovip(cvip_Image, filename, fd,CVIP_YES,CVIP_NO, showmessages);
				}
				else
				     cviptovip(cvip_Image,file_name,fd,CVIP_YES,CVIP_YES,showmessages);
				break;
			case XVQ:  
			        strcat(file_name,"__"); strcat(file_name, Cmpr_Name[Xvq]);
				if(access(file_name,R_OK)== -1){
		 		     cviptovip(cvip_Image, filename, fd,CVIP_YES,CVIP_NO, showmessages);
				}
				else
				     cviptovip(cvip_Image,file_name,fd,CVIP_YES,CVIP_YES,showmessages);
                                break;
			case TRCM:  
			        strcat(file_name,"__"); strcat(file_name, Cmpr_Name[Trcm]);
				if(access(file_name,R_OK)== -1){
		 		     cviptovip(cvip_Image, filename, fd,CVIP_YES,CVIP_NO, showmessages);
				}
				else
				     cviptovip(cvip_Image,file_name,fd,CVIP_YES,CVIP_YES,showmessages);
                                break;
			case BRC:
				strcat(file_name,"__"); strcat(file_name, Cmpr_Name[Brc]);
				if(access(file_name,R_OK)== -1){
		 		     cviptovip(cvip_Image, filename, fd,CVIP_YES,CVIP_NO, showmessages);
				}
				else
				     cviptovip(cvip_Image,file_name,fd,CVIP_YES,CVIP_YES,showmessages);
				break;
			case ZVL:
				strcat(file_name,"__"); strcat(file_name, Cmpr_Name[Zvl]);
				if(access(file_name,R_OK)== -1){
		 		     cviptovip(cvip_Image, filename, fd,CVIP_YES,CVIP_NO, showmessages);
				}
				else
				     cviptovip(cvip_Image,file_name,fd,CVIP_YES,CVIP_YES,showmessages);
				break;
			case ZON:
				strcat(file_name,"__"); strcat(file_name, Cmpr_Name[Zon]);
				if(access(file_name,R_OK)== -1){
		 		     cviptovip(cvip_Image, filename, fd,CVIP_YES,CVIP_NO, showmessages);
				}
				else
				     cviptovip(cvip_Image,file_name,fd,CVIP_YES,CVIP_YES,showmessages);
				break;
			case ZON2:
				strcat(file_name,"__"); strcat(file_name, Cmpr_Name[Zon2]);
				if(access(file_name,R_OK)== -1){
		 		     cviptovip(cvip_Image, filename, fd,CVIP_YES,CVIP_NO, showmessages);
				}
				else
				     cviptovip(cvip_Image,file_name,fd,CVIP_YES,CVIP_YES,showmessages);
				break;
			default:	
		 		cviptovip(cvip_Image, filename, fd,CVIP_YES,CVIP_NO, showmessages);    
		 }
		 } 
		  break;

      case BIN:   if(set_up == CVIP_NO)
                     cviptobin(cvip_Image, filename, fd, ORD_RGB, INTERPIXEL, showmessages); 
		  else
		     bin_wsetup(cvip_Image, filename, fd, showmessages);
		  break;
      default:  fprintf(stderr, "CVIPwriteimage: not a valid CVIP image format\n"); return 0;
   }
   
if(!retain_image) {
   image_free(cvip_Image);
   if(showmessages)
      msg_CVIP(function_name, "freeing image structure.\n");
}

if( new_format != TIF && new_format != JPG)
   CVIPclose( fd );

return 1;
}

/****************************************************************
                  Name: pnm_setup
         Expanded Name: Portable Any Map Set-Up Routine
            Parameters: cvip_Image - pointer to Image structure
			  filename - pointer to char. string containing
				     the image file name.
			   verbose - wanna know what I do? (CVIP_YES or CVIP_NO)
               Returns: None
           Description: This function will ask the user a set of questions
			regarding how the data should be presented to disk.
			The function will then save the content of the
			CVIP Image structure to disk based on the customized
			parameters.
           Diagnostics: a series of questions regarding how the image
			should be saved.
			if the function has trouble writing the image
			to disk for any reason an appropriate error
			message will be displayed.
             Credit(s): Greg Hance
			
			
****************************************************************/
static void pnm_setup(Image *cvip_Image, char *filename, FILE *fd, CVIP_BOOLEAN verbose)
{
/*   char *format[] = {"PBM", "PGM", "PPM", "EPS", "TIF", "GIF", "RAS", "ITX", "IRIS","CCC", "BIN", "VIP"};*/
   char *color[] = {"BINARY", "GRAYSCALE", "RGB"}, function_name[] = {"pnm_setup"};
   char *ext[] = {".pbm",".pgm",".ppm"}, *pnmfile;
   COLOR_FORMAT old_color;
   IMAGE_FORMAT old_format;
   int count, choice = 2;
   char *new_ext(const char *src, const char *ext);
   
   old_color  = cvip_Image->color_space;
   old_format = cvip_Image->image_format;

   do {
      count = 1;
      fprintf(stderr, "\n%s: converting from %s %s format to PNM format.\n",function_name,color[old_color],image_format_string[old_format]);
      fprintf(stderr, "%s: available PNM image formats for this type of conversion:\n",function_name);
      fprintf(stderr, "%s: (%d) PBM.\n",function_name,count++);
      fprintf(stderr, "%s: (%d) PGM.\n",function_name,count++);
      if(old_color == RGB)  
         fprintf(stderr, "%s: (%d) PPM.\n",function_name,count++);
      fprintf(stderr,"%s: convert to which format (1 <-> %d)?",function_name, count-1);
      scanf("%d", &choice);
   } while(choice<1 || choice>3);
   choice--;

   cvip_Image->image_format = choice;
   cvip_Image->color_space = choice;
   
   if(old_color == RGB) 
      if(choice == PGM || choice == PBM) 
         cvip_Image = luminance_Image(cvip_Image);
   if(old_color == RGB || old_color == GRAY_SCALE)
      if(choice == PBM) 
         cvip_Image = CVIPhalftone(cvip_Image, QT_FS, 255, 0.5, CVIP_NO, CVIP_YES);

   pnmfile = (char *) new_ext(filename, ext[choice]);
	if(!(fd = openWrite_CVIP(pnmfile, CVIP_NO))) {
			error_CVIP("pnm_setup", "could not open file %s for 		writing.\n", pnmfile);
			return;
	}

   cviptopnm(cvip_Image, pnmfile, fd, verbose);
	close_CVIP(fd);
	free(pnmfile);
}
   

/****************************************************************
                  Name: eps_setup
         Expanded Name: Encapsulated PostScript Set-Up Routine
            Parameters: cvip_Image - pointer to Image structure
			  filename - pointer to char. string containing
				     the image file name.
			   verbose - wanna know what I do? (CVIP_YES or CVIP_NO)
               Returns: (None)
           Description: This function will ask the user a set of questions
			regarding how the data should be presented to disk.
			The function will then save the content of the
			CVIP Image structure to disk based on the customized
			parameters.
           Diagnostics: a series of questions regarding how the image
			should be saved.
			if the function has trouble writing the image
			to disk for any reason an appropriate error
			message will be displayed.
             Credit(s): Greg Hance
			
			
****************************************************************/

static void eps_setup(Image *cvip_Image, char *filename, FILE *fd, int band, CVIP_BOOLEAN verbose)
{
   char *color[] = {"BINARY", "GRAYSCALE", "RGB"}, function_name[] = {"eps_setup"};
   COLOR_FORMAT old_color;
   IMAGE_FORMAT old_format;
   float xscale, yscale;
   
   old_color  = cvip_Image->color_space;
   old_format = cvip_Image->image_format;

   do {
      fprintf(stderr, "\n%s: converting from %s %s format to EPS format.\n",function_name,color[old_color],image_format_string[old_format]);
      fprintf(stderr, "%s: it is possible to rescale the postscipt image for display.\n",function_name);
      fprintf(stderr,"%s: (factor < 1) => shrink.\n",function_name);
      fprintf(stderr,"%s: (factor > 1) => enlarge.\n",function_name);
      fprintf(stderr,"%s: (factor = 1) => no change.\n",function_name);
      fprintf(stderr,"%s: enter horizontal scaling factor?",function_name);
      scanf("%f", &xscale);
      fprintf(stderr,"%s: enter vertical scaling factor?",function_name);
      scanf("%f", &yscale);
   } while(!xscale || !yscale);
   
   cviptoeps(cvip_Image, filename, fd, xscale, yscale, band, verbose); 
}


/****************************************************************
                  Name: itex_setup
         Expanded Name: ITEX Set-Up Routine
            Parameters: cvip_Image - pointer to Image structure
			  filename - pointer to char. string containing
				     the image file name.
			   verbose - wanna know what I do? (CVIP_YES or CVIP_NO)
               Returns: (Not a damn thing... but probably should)
           Description: This function will ask the user a set of questions
			regarding how the data should be presented to disk.
			The function will then save the content of the
			CVIP Image structure to disk based on the customized
			parameters.
           Diagnostics: a series of questions regarding how the image
			should be saved.
			if the function has trouble writing the image
			to disk for any reason an appropriate error
			message will be displayed.
             Credit(s): Greg Hance
			
			
****************************************************************/

static void itex_setup(Image *cvip_Image, char *filename, FILE *fd, CVIP_BOOLEAN verbose)
{
  /* char *format[] = {"PBM", "PGM", "PPM", "EPS", "TIF", "GIF", "RAS", "ITX", "IRIS","CCC", "BIN", "VIP"};*/
   char *color[] = {"BINARY", "GRAYSCALE", "RGB"}, function_name[] = {"itex_setup"}, comment[80];
   COLOR_FORMAT old_color;
   IMAGE_FORMAT old_format;
   float xscale, yscale;
   
   old_color  = cvip_Image->color_space;
   old_format = cvip_Image->image_format;

      fprintf(stderr, "\n%s: converting from %s %s format to EPS format.\n",function_name,color[old_color],image_format_string[old_format]);
      fprintf(stderr, "%s: enter a comment to be placed in ITEX header.\n",function_name);
      fprintf(stderr, "%s: comment: ",function_name);
      fflush(stdin);
      fgets(comment, 80, stdin);
      fprintf(stderr,"\n");
   
   cvip_Image->image_format = ITX;
   cvip_Image->color_space = GRAY_SCALE;
   
   if(old_color == RGB) 
      cvip_Image = luminance_Image(cvip_Image);
   
   cviptoitex(cvip_Image, filename, fd, comment, verbose); 
}
/****************************************************************
                  Name: iris_setup
         Expanded Name: IRIS Set-Up Routine
            Parameters: cvip_Image - pointer to Image structure
			  filename - pointer to char. string containing
				     the image file name.
			   verbose - wanna know what I do? (CVIP_YES or CVIP_NO)
               Returns: nothing
           Description: This function will ask the user a set of questions
			regarding how the data should be presented to disk.
			The function will then save the content of the
			CVIP Image structure to disk based on the customized
			parameters.
           Diagnostics: a series of questions regarding how the image
			should be saved.
			if the function has trouble writing the image
			to disk for any reason an appropriate error
			message will be displayed.
             Credit(s): Kun Luo
			
			
****************************************************************/

static void iris_setup(Image *cvip_Image, char *filename, FILE *fd, CVIP_BOOLEAN verbose)
{
/*  char *format[] = {"PBM", "PGM", "PPM", "EPS", "TIF", "GIF", "RAS", "ITX", "IRIS","CCC", "BIN", "VIP"};*/
   char *color[] = {"BINARY", "GRAYSCALE", "RGB"}, function_name[] = {"itex_setup"}, comment[80];
   COLOR_FORMAT old_color;
   IMAGE_FORMAT old_format;
   float xscale, yscale;
   
   old_color  = cvip_Image->color_space;
   old_format = cvip_Image->image_format;

      fprintf(stderr, "\n%s: converting from %s %s format to IRIS format.\n",function_name,color[old_color],image_format_string[old_format]);
      fprintf(stderr, "%s: enter a comment to be placed in IRIS header.\n",function_name);
      fprintf(stderr, "%s: comment: ",function_name);
      fflush(stdin);
      fgets(comment, 80, stdin);
      fprintf(stderr,"\n");
   
   cvip_Image->image_format = IRIS;
   cviptoiris(cvip_Image, filename, fd, comment, verbose); 
}



/****************************************************************
                  Name: ras_setup
         Expanded Name: Sun Raster Set-Up Routine
            Parameters: cvip_Image - pointer to Image structure
			  filename - pointer to char. string containing
				     the image file name.
			   verbose - wanna know what I do? (CVIP_YES or CVIP_NO)
               Returns: (None)
           Description: This function will ask the user a set of questions
			regarding how the data should be presented to disk.
			The function will then save the content of the
			CVIP Image structure to disk based on the customized
			parameters.
           Diagnostics: a series of questions regarding how the image
			should be saved.
			if the function has trouble writing the image
			to disk for any reason an appropriate error
			message will be displayed.
             Credit(s): Greg Hance
			
			
****************************************************************/

static void ras_setup(Image *cvip_Image, char *filename, FILE *fd, CVIP_BOOLEAN verbose)
{
 /*  char *format[] = {"PBM", "PGM", "PPM", "EPS", "TIF", "GIF", "RAS", "ITX", "IRIS","CCC", "BIN", "VIP"};*/
   char *color[] = {"BINARY", "GRAYSCALE", "RGB"}, function_name[] = {"ras_setup"};
   COLOR_FORMAT old_color;
   IMAGE_FORMAT old_format;
   int count, choice, encode;
   
   old_color  = cvip_Image->color_space;
   old_format = cvip_Image->image_format;

   do {
      count = 1;
      fprintf(stderr, "\n%s: converting from %s %s format to Sun rasterfile format.\n",function_name,color[old_color],image_format_string[old_format]);
      fprintf(stderr, "%s: available Sun raster color formats for this type of conversion:\n",function_name);
      fprintf(stderr, "%s: (%d) BINARY          - (black and white pixels only).\n",function_name,count++);
      fprintf(stderr, "%s: (%d) GRAYSCALE       - (256 graylevels).\n",function_name,count++);
      if(old_color == RGB)  
      fprintf(stderr, "%s: (%d) RGB/COLORMAPPED - (colormapped if less than 256 colors).\n",function_name,count++);
      fprintf(stderr,"%s: convert to which color format (1 <-> %d)?",function_name, count-1);
      scanf("%d", &choice);
   } while(choice<1 || choice>3);
   choice--;

   do {
      fprintf(stderr,"%s: =========================================\n",function_name);
      fprintf(stderr,"%s: choose one of the following:\n",function_name);   
      fprintf(stderr,"%s: (1) Sun raster STANDARD format.\n",function_name);
      fprintf(stderr,"%s: (2) Sun raster CVIP_BYTE ENCODED format (smaller but less standard).\n",function_name);
      fprintf(stderr,"%s: choose (1 or 2)?",function_name);
      scanf("%d", &encode);
   } while(encode<1 || encode>2);

   fprintf(stderr,"\n\n");
   
   cvip_Image->image_format = RAS;
   cvip_Image->color_space = choice;
   
   if(old_color == RGB) 
      if(choice == GRAY_SCALE || choice == BINARY) 
         cvip_Image = luminance_Image(cvip_Image);
   if(old_color == RGB || old_color == GRAY_SCALE)
      if(choice == BINARY) 
         cvip_Image = CVIPhalftone(cvip_Image, QT_FS, 255, 0.5, CVIP_NO, CVIP_YES);
   
   cviptoras(cvip_Image, filename, fd, encode, verbose); 
}


/****************************************************************
                  Name: gif_setup
         Expanded Name: Graphical Interchange Format Set-Up Routine
            Parameters: cvip_Image - pointer to Image structure
			  filename - pointer to char. string containing
				     the image file name.
			   verbose - wanna know what I do? (CVIP_YES or CVIP_NO)
               Returns: (None)
           Description: This function will ask the user a set of questions
			regarding how the data should be presented to disk.
			The function will then save the content of the
			CVIP Image structure to disk based on the customized
			parameters.
           Diagnostics: a series of questions regarding how the image
			should be saved.
			if the function has trouble writing the image
			to disk for any reason an appropriate error
			message will be displayed.
             Credit(s): Greg Hance
			
			
****************************************************************/

static void gif_setup(Image *cvip_Image, char *filename, FILE *fd, CVIP_BOOLEAN verbose)
{
  /* char *format[] = {"PBM", "PGM", "PPM", "EPS", "TIF", "GIF", "RAS", "ITX", "IRIS","CCC", "BIN", "VIP"};*/
   char *color[] = {"BINARY", "GRAYSCALE", "RGB"}, function_name[] = {"gif_setup"};
   COLOR_FORMAT old_color;
   IMAGE_FORMAT old_format;
   int interlace;
   char ask;
   
   old_color  = cvip_Image->color_space;
   old_format = cvip_Image->image_format;

      fprintf(stderr, "\n%s: converting from %s %s format to Graphics Interchange Format (GIF).\n",function_name,color[old_color],image_format_string[old_format]);
      fprintf(stderr, "%s: NOTE: generally GIF files are not interlaced!\n",function_name);
      fprintf(stderr, "%s: do you want an interlaced GIF file?",function_name);
      fflush(stdin);
      ask = getchar();
      if(ask=='y' || ask=='Y') 
         interlace = CVIP_YES;
      else
         interlace = CVIP_NO;
      fprintf(stderr,"\n");
   
   cvip_Image->image_format = GIF;
   cvip_Image->color_space = RGB;
      
   cviptogif(cvip_Image, filename, fd, interlace, verbose); 
}

/****************************************************************
                  Name: ccc_setup
         Expanded Name: Color Cell Compression Set-Up Routine
            Parameters: cvip_Image - pointer to Image structure
			  filename - pointer to char. string containing
				     the image file name.
			   verbose - wanna know what I do? (CVIP_YES or CVIP_NO)
               Returns: (None)
           Description: This function will ask the user a set of questions
			regarding how the data should be presented to disk.
			The function will then save the content of the
			CVIP Image structure to disk based on the customized
			parameters.
           Diagnostics: a series of questions regarding how the image
			should be saved.
			if the function has trouble writing the image
			to disk for any reason an appropriate error
			message will be displayed.
             Credit(s): Greg Hance
			
			
****************************************************************/

static void ccc_setup(Image *cvip_Image, char *filename, FILE *fd, CVIP_BOOLEAN verbose)
{
 /*  char *format[] = {"PBM", "PGM", "PPM", "EPS", "TIF", "GIF", "RAS", "ITX", "IRIS","CCC", "BIN", "VIP"};*/
   char *color[] = {"BINARY", "GRAYSCALE", "RGB"}, function_name[] = {"ccc_setup"};
   COLOR_FORMAT old_color;
   IMAGE_FORMAT old_format;
   int no_colors, dermvis;
   char ask;
   
   old_color  = cvip_Image->color_space;
   old_format = cvip_Image->image_format;

      fprintf(stderr, "\n%s: converting from %s %s format to Color Cell Compression format (CCC).\n",function_name,color[old_color],image_format_string[old_format]);
      fprintf(stderr, "%s: NOTE: images taken with the dermvis camera have lower rows that are\n",function_name);
      fprintf(stderr, "%s: not used; it is better to suppress these rows as not to bias the\n", function_name);
      fprintf(stderr, "%s: color selection.\n",function_name);
      fprintf(stderr, "%s: Is the image from the dermvis archive of skin tumor images?",function_name);
      fflush(stdin);
      ask = getchar();
      if(ask=='y' || ask=='Y') 
         dermvis = CVIP_YES;
      else
         dermvis = CVIP_NO;
      fprintf(stderr, "%s: ===========================================================\n",function_name);
      fprintf(stderr, "%s: quantize to how many colors (2 <-> 256)?",function_name);
      scanf("%d", &no_colors);
      fprintf(stderr,"\n");
   
   cvip_Image->image_format = CCC;
   cvip_Image->color_space = RGB;
      
   cviptoccc(cvip_Image, filename, fd, no_colors, dermvis, verbose); 
}


/****************************************************************
                  Name: tiff_setup
         Expanded Name: Tagged Image File Format Set-Up Routine
            Parameters: cvip_Image - pointer to Image structure
			  filename - pointer to char. string containing
				     the image file name.
			   verbose - wanna know what I do? (CVIP_YES or CVIP_NO)
               Returns: (None)
           Description: This function will ask the user a set of questions
			regarding how the data should be presented to disk.
			The function will then save the content of the
			CVIP Image structure to disk based on the customized
			parameters.
           Diagnostics: a series of questions regarding how the image
			should be saved.
			if the function has trouble writing the image
			to disk for any reason an appropriate error
			message will be displayed.
             Credit(s): Greg Hance
			
			
****************************************************************/

static void tiff_setup(Image *cvip_Image, char *filename, CVIP_BOOLEAN verbose)
{
 /*  char *format[] = {"PBM", "PGM", "PPM", "EPS", "TIF", "GIF", "RAS", "ITX", "IRIS","CCC", "BIN", "VIP"};*/
   char *color[] = {"BINARY", "GRAYSCALE", "RGB"}, function_name[] = {"tiff_setup"}, ask;
   COLOR_FORMAT old_color;
   IMAGE_FORMAT old_format;
   int count, choice;
   unsigned short encode;
   unsigned short fill;
   long group3;
   unsigned short predictor;
   long rowsperstrip;

   old_color  = cvip_Image->color_space;
   old_format = cvip_Image->image_format;

   do {
      count = 1;
      fprintf(stderr, "\n%s: converting from %s %s format to Tagged Image File format (TIF).\n",function_name,color[old_color],image_format_string[old_format]);
      fprintf(stderr, "%s: available TIFF color formats for this type of conversion:\n",function_name);
      fprintf(stderr, "%s: (%d) BINARY          - (black and white pixels only).\n",function_name,count++);
      fprintf(stderr, "%s: (%d) GRAYSCALE       - (256 graylevels maximum).\n",function_name,count++);
      if(old_color == RGB)  
      fprintf(stderr, "%s: (%d) RGB/COLORMAPPED - (colormapped if less than 256 colors).\n",function_name,count++);
      fprintf(stderr,"%s: convert to which color format (1 <-> %d)?",function_name, count-1);
      scanf("%d", &choice);
   } while(choice<1 || choice>3);
   choice--;

   if(old_color == RGB) 
      if(choice == GRAY_SCALE || choice == BINARY) 
         cvip_Image = luminance_Image(cvip_Image);
   if(old_color == RGB || old_color == GRAY_SCALE)
      if(choice == BINARY) 
         cvip_Image = CVIPhalftone(cvip_Image, QT_FS, 255, 0.5, CVIP_NO, CVIP_YES);

   do {
      fprintf(stderr,"%s: ============================\n",function_name);
      fprintf(stderr,"%s: choose a compression scheme:\n",function_name);   
      fprintf(stderr,"%s: (1) Lempel-Ziv  & Welch (usually best bet).\n",function_name);
      fprintf(stderr,"%s: (2) Macintosh RLE.\n",function_name);
      fprintf(stderr,"%s: (3) CCITT Group 3 fax encoding (bilevel data).\n",function_name);
      fprintf(stderr,"%s: (4) CCITT Group 4 fax encoding (bilevel data).\n",function_name);
      fprintf(stderr,"%s: (5) none.\n",function_name);
      fprintf(stderr,"%s: choose (1 <-> 5)?",function_name);
      scanf("%hd", &encode);
   } while(encode<1 || encode>5);
   
   
   if(encode == 1) {
      fprintf(stderr,"%s: ==========\n",function_name);
      fprintf(stderr,"%s: ZVL option:\n",function_name);
      fprintf(stderr,"%s: Do you wish for each scanline of the output image\n",function_name);
      fprintf(stderr,"%s: to undergo horizontal differencing before it is encoded (n)?",function_name);
      getchar(); /*fflush(stdin);*/
      ask = getchar();
      if(ask=='y' || ask=='Y')
         predictor = 2;
      else
         predictor = CVIP_NO;       
   } 

   
   if(encode == 4) 
      do {
         fprintf(stderr,"%s: ===============\n",function_name);
         fprintf(stderr,"%s: Group 3 Options:\n",function_name);
         fprintf(stderr,"%s: (1) 2-dimensional  encoding.\n",function_name);
         fprintf(stderr,"%s: (2) encoded scanline by zero-filling to a byte boundry.\n",function_name);
         fprintf(stderr,"%s: choose (1 or 2)?",function_name);
         scanf("%ld", &group3);
   } while(group3<1 || group3>2);
   
   if(group3==1)
      group3 = GROUP3OPT_2DENCODING;
   else if(group3==2)
      group3 = GROUP3OPT_FILLBITS;
   else
      group3 = CVIP_NO;
   
   do {
      fprintf(stderr,"%s: =========================================\n",function_name);
      fprintf(stderr,"%s: choose a fill order/byte ordering scheme:\n",function_name);   
      fprintf(stderr,"%s: (1) MSB to LSB (most common).\n",function_name);
      fprintf(stderr,"%s: (2) LSB to MSB.\n",function_name);
      fprintf(stderr,"%s: choose (1 or 2)?",function_name);
      scanf("%hd", &fill);
   } while(fill<1 || fill>2);
   
   
   fprintf(stderr,"%s: ====================================================\n",function_name);
   fprintf(stderr,"%s: CVIP_NO: assures no more than 8 kilobytes per strip:\n",function_name);
   fprintf(stderr,"%s: Do you wish to set the number of rows (scanlines)\n",function_name);
   fprintf(stderr,"%s: in each strip of data in the output file. (n)?",function_name);
   getchar();/*fflush(stdin);*/
   ask = getchar();
   if(ask=='y' || ask=='Y') {
      fprintf(stderr,"%s: how many scanlines/rows?",function_name);
      scanf("%ld", &rowsperstrip);
   }
   else
      rowsperstrip = CVIP_NO;      
  
   fprintf(stderr,"\n\n");
   
   cvip_Image->image_format = RAS;
   cvip_Image->color_space = choice;
   
   switch(encode) {
      case 1: encode = COMPRESSION_LZW;break;
      case 2: encode = COMPRESSION_PACKBITS;break;
      case 3: encode = COMPRESSION_CCITTFAX3;break;
      case 4: encode = COMPRESSION_CCITTFAX4;break;
      case 5: encode = COMPRESSION_NONE;break;
      default: fprintf(stderr, "%s: can't happen!\n",function_name);break;
   }
    
   cviptotiff(cvip_Image, filename, encode, fill, group3, predictor, rowsperstrip, verbose); 
}

/****************************************************************
                  Name: guess_bin_dim
         Expanded Name: Guess Binary Dimension
            Parameters:  infp - pointer to open file descriptor
		        color - pointer to integer data object
               Returns: index to an array where the width and height
			of the image are specified.
           Description: attempts to guess the dimensions of a
			raw image file based on a predetermined set
			of values contained in the include file CVIPimage.h
           Diagnostics: returns -1 if no match can be found
             Credit(s): Greg Hance
			
			
****************************************************************/
static int guess_bin_dim(infp,color)
FILE *infp;
int *color;
{
   int i, format;   
   long dimension;
   
   static struct image_dimension {
       long size;
       int width;
       int heigth;
   } Image_DIMENSION[] = {SIZES};

   fseek(infp,0,2);
   dimension = (long) ftell(infp);
   fseek(infp,0,0);
   
   for(i=0; i <= 6 ; i++)
      if(dimension == Image_DIMENSION[i].size) {
         *color = CVIP_NO;
	 return i;
      }
      else if((dimension/3) == Image_DIMENSION[i].size) {
	 *color = CVIP_YES;
	 return i;
      }

return(-1);
}


/****************************************************************
                  Name: bin_rsetup
         Expanded Name: Binary Read Set-Up
            Parameters: filename - pointer to a character string
				   containing the name of the file name
			 verbose - wanna know what I do(CVIP_YES or CVIP_NO)?
               Returns: pointer to Image structure loaded with data
			from the file <filename> and initialized to the
			specifications of the format.
           Description: will load a raw data image into a CVIP Image 
			structure. The function will first make an
			educated guess at the image format based on size
			alone and if it misses the mark the user can
			manually specify the width, height, no. of
			data bands, etc..
           Diagnostics: questions the user if guess is correct (regarding
			width ,height and no. of bands.)
			if not... prompts the user for more input.
			returns NULL pointer w/ corresponding error msg.
			if things don't match up (e.g. user specified
			width and height may not match up with the
			amount of data contained in the file.)
             Credit(s): Greg Hance
			
			
****************************************************************/
static Image *bin_rsetup(char *filename, FILE *fd, CVIP_BOOLEAN verbose)
{
   FILE *fptr;
   Image *rawImage;
   int guess_size,gcolor, rows, cols, color_order, interleave, bands;
   char *color[6] = {"RGB","RBG","GRB", "GBR" ,"BRG", "BGR"};
   char *scheme[3] = {"INTERPLANE", "INTERLINE", "INTERPIXEL"};
   char *guess_color[] = {"GRAYSCALE", "RGB"};
   char function_name[] = {"bin_rsetup"}, ask;
   static struct image_dimension {
      long size;
      int width;
      int heigth;
   } Image_DIMENSION[] = {SIZES};
   
   fptr = CVIPopenr(filename);
   
   guess_size = guess_bin_dim(fptr,&gcolor);
   
/*   if(guess_size != -1) {
      fprintf(stderr,"%s: is the raw image a %d x %d %s image?",function_name, Image_DIMENSION[guess_size].width, Image_DIMENSION[guess_size].heigth, guess_color[gcolor]);
      fflush(stdin);
      ask = getchar(); 
   }
   if(guess_size<0 || ask=='n' || ask=='N') {
      fprintf(stderr, "%s: is the image grayscale or color (g/c)? ", function_name);
      fflush(stdin);
      ask = getchar();
      if( ask=='c' || ask=='C')
         bands = 3;
      else
         bands = 1;
      fprintf(stderr,"%s: what is the image height?", function_name);
      scanf("%d", &rows);
      fprintf(stderr,"%s: what is the image width?", function_name);
      scanf("%d", &cols);
   } */
	if (guess_size < 0) {
      fprintf(stderr,"%s: can't determine the image size?",function_name);
      fflush(stdin);
		return (Image*)NULL;
	} else {
      rows = Image_DIMENSION[guess_size].heigth;
      cols = Image_DIMENSION[guess_size].width;
      if(gcolor)
         bands = 3;
      else
         bands = 1;
   }
   
   if(bands == 3) {
/*      do {
         fprintf(stderr,"%s: ========================================\n",function_name);
         fprintf(stderr,"%s: what is the color ordering of the image:\n",function_name);   
	 fprintf(stderr,"%s: (1) RGB, (2) RBG, (3) GRB, (4) GBR, (5) BRG, (6) BGR.\n",function_name);
         fprintf(stderr,"%s: choose (1 <-> 6)?",function_name);
         scanf("%d", &color_order);
      } while(color_order<1 || color_order>6);
      color_order--;
      do {
         fprintf(stderr,"%s: ==============================================\n",function_name);
         fprintf(stderr,"%s: what is the interleave scheme of the %s image:\n",function_name,color[color_order]);   
         fprintf(stderr,"%s: (1) INTERPLANE, (2) INTERLINE, (3) INTERPIXEL\n",function_name);
         fprintf(stderr,"%s: choose (1 <-> 3)?",function_name);
         scanf("%d", &interleave);
      } while(interleave<1 || interleave>3);
      interleave--;
*/
		color_order = ORD_RGB;
		interleave = INTERPIXEL;
      rawImage = bintocvip(filename, fd, bands, color_order, interleave, rows, cols, verbose);
   }
   else
      rawImage = bintocvip(filename, fd, bands, CVIP_NO, CVIP_NO, rows, cols, verbose);
return rawImage;
}
   

/****************************************************************
                  Name: bin_wsetup
         Expanded Name: Binary Write Set-Up
            Parameters:  cvip_Image - pointer to an Image structure
			   filename - pointer to a character string
				      containing the name of the file name
			    verbose - wanna know what I do(CVIP_YES or CVIP_NO)?
               Returns: (None)
           Description: will save the data pointed to by an Image
			structure out to disk in raw image format.
			No header ...no  nothin' just RAW PRIMAL data!
           Diagnostics: ...informs user of operations taking place
			...if image is color will prompt user for
			desired interlace scheme, and color sequencing.
             Credit(s): Greg Hance
			
****************************************************************/
      
static void bin_wsetup(Image *cvip_Image, char *filename, FILE *fd, CVIP_BOOLEAN verbose)
{
  /* char *format[] = {"PBM", "PGM", "PPM", "EPS", "TIF", "GIF", "RAS", "ITX", "IRIS","CCC", "BIN", "VIP"};*/
   char *color_type[] = {"BINARY", "GRAYSCALE", "RGB"};
   COLOR_FORMAT old_color;
   IMAGE_FORMAT old_format;
   int rows, cols, color_order, interleave, bands, choice;
   char *color[6] = {"RGB","RBG","GRB", "GBR" ,"BRG", "BGR"};
   char *scheme[3] = {"INTERPLANE", "INTERLINE", "INTERPIXEL"};
   char function_name[] = {"bin_wsetup"};
   
   old_color  = cvip_Image->color_space;
   old_format = cvip_Image->image_format;
   bands = cvip_Image->bands;
   rows = cvip_Image->image_ptr[0]->rows;
   cols = cvip_Image->image_ptr[0]->cols;

   do {
      fprintf(stderr, "\n%s: converting from %s %s format to Binary raw data format (BIN.)\n",function_name,color_type[old_color],image_format_string[old_format]);
      fprintf(stderr, "%s: available BIN color formats for this type of conversion:\n",function_name);
      fprintf(stderr, "%s: (1) GRAYSCALE  - (256 graylevels maximum).\n",function_name);
      if(old_color == RGB) { 
      fprintf(stderr, "%s: (2) COLOR      - (true 24 bit color).\n",function_name);
         fprintf(stderr,"%s: convert to which color format (1 or 2)?",function_name);
         scanf("%d", &choice);
      }
      else
        choice = 1;
   } while(choice<1 || choice>2);

   if(old_color == RGB && choice == GRAY_SCALE) 
      cvip_Image = luminance_Image(cvip_Image);

   
   if(choice==RGB) {
      do {
         fprintf(stderr,"%s: ========================================\n",function_name);
         fprintf(stderr,"%s: what is the color ordering of the image:\n",function_name);   
	 fprintf(stderr,"%s: (1) RGB, (2) RBG, (3) GRB, (4) GBR, (5) BRG, (6) BGR.\n",function_name);
         fprintf(stderr,"%s: choose (1 <-> 6)?",function_name);
         scanf("%d", &color_order);
      } while(color_order<1 || color_order>6);
      color_order--;
      do {
         fprintf(stderr,"%s: ==============================================\n",function_name);
         fprintf(stderr,"%s: what is the interleave scheme of the %s image:\n",function_name,color[color_order]);   
         fprintf(stderr,"%s: (1) INTERPLANE, (2) INTERLINE, (3) INTERPIXEL\n",function_name);
         fprintf(stderr,"%s: choose (1 <-> 3)?",function_name);
         scanf("%d", &interleave);
      } while(interleave<1 || interleave>3);
      interleave--;
      cviptobin(cvip_Image, filename, fd, color_order, interleave, verbose);
   }
   else
      cviptobin(cvip_Image, filename, fd, CVIP_NO, CVIP_NO, verbose);
}


/****************************************************************
                  Name: new_ext
         Expanded Name: New Extension
            Parameters: src - pointer to a character string
			ext - pointer to a character string in the
			      form of an extension (e.g. .ppm )
               Returns: pointer to newly allocated character string
			src.ext
           Description: replace the last occuring extension of
			src with des.
           Diagnostics: this function is quit...
             Credit(s): Greg Hance
			
****************************************************************/
char *new_ext(const char *src, const char *ext)
{
   char *sptr, *des;
   unsigned int baselen;

   if ( (sptr = (char *) strrchr(src, '.')) == NULL) {
      des = (char *) malloc(strlen(src)+strlen(ext)+1);
      strcpy(des, src);
      strcat(des, ext);
   }
   else {
      baselen = abs(sptr-src);
      des = (char *) malloc(baselen + strlen(ext) + 1);
      (void) strncpy(des, src, baselen);
      *(des + baselen) = '\0';
      (void) strcat(des, ext);
   }

return des;
}


static IMAGE_FORMAT CVIPgetmagic(const char *filename, unsigned long *magic, FILE *fd)
{
   register int count=1;
   const char *fn = "CVIPgetmagic";

   *magic = 0;

   while(count < 5) {
      *magic <<= 8;
      *magic |= (0xff&getc( fd ));
      if( *magic == RASMAGIC )
         return RAS;
      else if( *magic == GIFMAGIC )
         return GIF;
      else if( *magic == CVIPMAGIC )
         return VIP;
      else if( *magic == ITEXMAGIC )
         return ITX;
      else if( (*magic ==TIFF_BIGENDIAN) ||  (*magic ==TIFF_LITTLEENDIAN) ) {
         fprintf(stderr, "%s: can not read TIFF file from \"stdin\"... sorry.\n",fn);
         return -1;
      }
      else if( *magic == EPSMAGIC )
         return EPS;
      else if( PNM_FORMAT_TYPE(*magic) == PPM_TYPE )
         return PPM;
      else if( PNM_FORMAT_TYPE(*magic) == PGM_TYPE )
         return PGM;
      else if( PNM_FORMAT_TYPE(*magic) == PBM_TYPE )
         return PBM;
      else if( !*magic )
         return CCC;
     
   }
   return -1;
}
 
