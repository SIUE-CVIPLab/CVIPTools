/***************************************************************************
======================================================================
Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
======================================================================
                                                                      
             File Name: giftocvip.c
           Description: contains a routine to load a GIF
			file into a CVIP Image structure.
         Related Files: CVIPimage.h, CVIPbin.h, Makefile
   Initial Coding Date: 1/24/93
           Portability: Standard (ANSI) C
             Credit(s): Gregory Hance, E.E. Dept. SIUE

  Global Function List: giftocvip
			
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

$Log: giftocvip.c,v $
Revision 1.5  1997/03/08 16:59:51  yawei
Swaped CVIP_YES and CVIP_NO

Revision 1.4  1997/03/08 00:42:40  yawei
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

Revision 1.3  1997/01/15 17:06:24  yawei
Global Change:  IMAGE ==> Image

 * Revision 1.2  1997/01/15  16:01:35  yawei
 * updated changes
 *
 * Revision 1.1  1993/05/31  07:10:14  hanceg
 * Initial revision
 *                                                         

*****************************************************************************/


#include	"ppm.h" 
#define NO_STD_INCLUDES
#include        "CVIPimage.h"
#include        "CVIPxel.h"

#define	MAXCOLORMAPSIZE		256

#define CM_RED		0
#define CM_GREEN	1
#define CM_BLUE		2

#define	MAX_LWZ_BITS		12

#define INTERLACE       0x40    /* 0100 0000 (Dec. 64)  */
#define LOCALCOLORMAP	0x80    /* 1000 0000 (Dec. 128) */      
#define BitSet(byte, bit)	(((byte) & (bit)) == (bit)) /* Check to see if a certain bit is set */

#define	ReadOK(file,buffer,len)	(fread(buffer, len, 1, file) != 0)

#define LM_to_uint(a,b)			(((b)<<8)|(a))

struct {
	unsigned int	Width;
	unsigned int	Height;
	unsigned char	ColorMap[3][MAXCOLORMAPSIZE];
	unsigned int	BitPixel;
	unsigned int	ColorResolution;
	unsigned int	Background;
	unsigned int	AspectRatio;
} GifScreen;

struct {
	int	transparent;
	int	delayTime;
	int	inputFlag;
	int	disposal;
} Gif89 = { -1, -1, -1, 0 };

#define CVIP_YES 1
#define CVIP_NO 0

static Image *ReadGIF ARGS(( FILE *fd, int imageNumber ));
static int ReadColorMap ARGS(( FILE *fd, int number, unsigned char buffer[3][MAXCOLORMAPSIZE] ));
static int DoExtension ARGS(( FILE *fd, int label ));
static int GetDataBlock ARGS(( FILE *fd, unsigned char  *buf ));
static int GetCode ARGS(( FILE *fd, int code_size, int flag ));
static int LWZReadByte ARGS(( FILE *fd, int flag, int input_code_size ));
static Image *ReadImage ARGS(( FILE *fd, int len, int height, unsigned char cmap[3][MAXCOLORMAPSIZE], int interlace, int ignore ));

int verbose = CVIP_NO; 
int showComment = CVIP_NO;

Image *giftocvip(char *name, FILE *in, int imageNumber, int showmessage)
{
	Image           *gif_Image;
	char            *prog_name[1] = {"giftocvip"};
		
	Image *ReadGIF(FILE *, int);

	verbose = showmessage;
	showComment = showmessage;

        pm_init(&verbose, prog_name);
	pm_message("opening Graphics Interchange Format(GIF) file - %s.",name);

	gif_Image = (Image *) ReadGIF(in, imageNumber);

	return gif_Image;
}

static Image *ReadGIF(fd, imageNumber)
FILE	*fd;
int	imageNumber;
{
	unsigned char	buf[16];
	unsigned char	c;
	unsigned char	localColorMap[3][MAXCOLORMAPSIZE];
	int		useGlobalColormap;
	int		bitPixel;
	int		imageCount = 0, bufcount = 0;
	char		version[4];
	Image *gif_Image;
	
	Image *ReadImage ARGS(( FILE *fd, int len, int height, unsigned char cmap[3][MAXCOLORMAPSIZE], int interlace, int ignore ));

        if( fd != stdin )
           bufcount = 3;
	if (! ReadOK(fd,buf,3+bufcount)) /* Read in 1 - 6 byte data element */ 
           pm_error("error reading magic number" );
        
        if( bufcount )
	   if (strncmp((char *) buf,"GIF",3) != 0) /* Compare first 3 bytes of .gif */
              pm_error("not a GIF file" ); /* file with "GIF" */
       
	strncpy(version, (char *) buf + bufcount, 3); /* Compare next 3 bytes for version */
	version[3] = '\0';            /* Note: NULL char. is skipped (buf+3)*/

	if ((strcmp(version, "87a") != 0) && (strcmp(version, "89a") != 0))
		pm_error("bad version number, not '87a' or '89a'" );

	if (! ReadOK(fd,buf,7))
		pm_error("failed to read screen descriptor" );

	GifScreen.Width           = LM_to_uint(buf[0],buf[1]); /* 2 bytes => unsigned int */
	GifScreen.Height          = LM_to_uint(buf[2],buf[3]); /* 2 bytes => unsigned int */
	GifScreen.BitPixel        = 2<<(buf[4]&0x07); /* # of bits per pixel (2, 4, 8) */
	GifScreen.ColorResolution = (((buf[4]&0x70)>>3)+1); 
	GifScreen.Background      = buf[5];
	GifScreen.AspectRatio     = buf[6];

	if (BitSet(buf[4], LOCALCOLORMAP)) {	/* Global Colormap if 1000 0000 bit is set */
		if (ReadColorMap(fd,GifScreen.BitPixel,GifScreen.ColorMap))
			pm_error("error reading global colormap" );
	}

	if (GifScreen.AspectRatio != 0 && GifScreen.AspectRatio != 49) {
		float	r;
		r = ( (float) GifScreen.AspectRatio + 15.0 ) / 64.0;
		pm_message("warning - non-square pixels; to fix do a 'pnmscale -%cscale %g'",
		    r < 1.0 ? 'x' : 'y',
		    r < 1.0 ? 1.0 / r : r );
	}

	for (;;) {
		if (! ReadOK(fd,&c,1))
			pm_error("EOF / read error on image data" );

		if (c == ';') {		/* GIF terminator */
			if (imageCount < imageNumber)
				pm_error("only %d image%s found in file",
					 imageCount, imageCount>1?"s":"" );
			return;
		}

		if (c == '!') { 	/* Extension */
			if (! ReadOK(fd,&c,1))
				pm_error("OF / read error on extention function code");
			DoExtension(fd, c);
			continue;
		}

		if (c != ',') {		/* Not a valid start character */
			pm_message("bogus character 0x%02x, ignoring", (int) c );
			continue;
		}

		++imageCount;

		if (! ReadOK(fd,buf,9))
			pm_error("couldn't read left/top/width/height");

		useGlobalColormap = ! BitSet(buf[8], LOCALCOLORMAP);

		bitPixel = 1<<((buf[8]&0x07)+1);

		if (! useGlobalColormap) {
			if (ReadColorMap(fd, bitPixel, localColorMap))
				pm_error("error reading local colormap" );
			gif_Image = (Image *) ReadImage(fd, LM_to_uint(buf[4],buf[5]),
				  LM_to_uint(buf[6],buf[7]), localColorMap,
				  BitSet(buf[8], INTERLACE), imageCount != imageNumber);
                        return gif_Image;
		} else {
			gif_Image = (Image *) ReadImage(fd, LM_to_uint(buf[4],buf[5]),
				  LM_to_uint(buf[6],buf[7]), GifScreen.ColorMap,
				  BitSet(buf[8], INTERLACE), imageCount != imageNumber);
                        return gif_Image;
		}

	}
}

static int
ReadColorMap(fd,number,buffer)
FILE		*fd;
int		number;
unsigned char	buffer[3][MAXCOLORMAPSIZE];
{
	int		i;
	unsigned char	rgb[3];

	for (i = 0; i < number; ++i) {
		if (! ReadOK(fd, rgb, sizeof(rgb))) /* Read in one 3 byte data element */
			pm_error("bad colormap" );

		buffer[CM_RED][i] = rgb[0] ;
		buffer[CM_GREEN][i] = rgb[1] ;
		buffer[CM_BLUE][i] = rgb[2] ;
	}
	return CVIP_NO;
}

static int
DoExtension(fd, label)
FILE	*fd;
int	label;
{
	static char	buf[256];
	char		*str;

	switch (label) {
	case 0x01:		/* Plain Text Extension */
		str = "Plain Text Extension";
#ifdef notdef
		if (GetDataBlock(fd, (unsigned char*) buf) == 0)
			;

		lpos   = LM_to_uint(buf[0], buf[1]);
		tpos   = LM_to_uint(buf[2], buf[3]);
		width  = LM_to_uint(buf[4], buf[5]);
		height = LM_to_uint(buf[6], buf[7]);
		cellw  = buf[8];
		cellh  = buf[9];
		foreground = buf[10];
		background = buf[11];

		while (GetDataBlock(fd, (unsigned char*) buf) != 0) {
			PPM_ASSIGN(image[ypos][xpos],
					cmap[CM_RED][v],
					cmap[CM_GREEN][v],
					cmap[CM_BLUE][v]);
			++index;
		}

		return CVIP_NO;
#else
		break;
#endif
	case 0xff:		/* Application Extension */
		str = "Application Extension";
		break;
	case 0xfe:		/* Comment Extension */
		str = "Comment Extension";
		while (GetDataBlock(fd, (unsigned char*) buf) != 0) {
			if (showComment)
				pm_message("gif comment: %s", buf );
		}
		return CVIP_NO;
	case 0xf9:		/* Graphic Control Extension */
		str = "Graphic Control Extension";
		(void) GetDataBlock(fd, (unsigned char*) buf);
		Gif89.disposal    = (buf[0] >> 2) & 0x7;
		Gif89.inputFlag   = (buf[0] >> 1) & 0x1;
		Gif89.delayTime   = LM_to_uint(buf[1],buf[2]);
		if ((buf[0] & 0x1) != 0)
			Gif89.transparent = buf[3];

		while (GetDataBlock(fd, (unsigned char*) buf) != 0)
			;
		return CVIP_NO;
	default:
		str = buf;
		sprintf(buf, "UNKNOWN (0x%02x)", label);
		break;
	}

	pm_message("got a '%s' extension", str );

	while (GetDataBlock(fd, (unsigned char*) buf) != 0)
		;

	return CVIP_NO;
}

int	ZeroDataBlock = CVIP_NO;

static int
GetDataBlock(fd, buf)
FILE		*fd;
unsigned char 	*buf;
{
	unsigned char	count;

	if (! ReadOK(fd,&count,1)) {
		pm_message("error in getting DataBlock size" );
		return -1;
	}

	ZeroDataBlock = count == 0;

	if ((count != 0) && (! ReadOK(fd, buf, count))) {
		pm_message("error in reading DataBlock" );
		return -1;
	}

	return count;
}

static int
GetCode(fd, code_size, flag)
FILE	*fd;
int	code_size;
int	flag;
{
	static unsigned char	buf[280];
	static int		curbit, lastbit, done, last_byte;
	int			i, j, ret;
	unsigned char		count;

	if (flag) {
		curbit = 0;
		lastbit = 0;
		done = CVIP_NO;
		return 0;
	}

	if ( (curbit+code_size) >= lastbit) {
		if (done) {
			if (curbit >= lastbit)
				pm_error("ran off the end of my bits" );
			return -1;
		}
		buf[0] = buf[last_byte-2];
		buf[1] = buf[last_byte-1];

		if ((count = GetDataBlock(fd, &buf[2])) == 0)
			done = CVIP_YES;

		last_byte = 2 + count;
		curbit = (curbit - lastbit) + 16;
		lastbit = (2+count)*8 ;
	}

	ret = 0;
	for (i = curbit, j = 0; j < code_size; ++i, ++j)
		ret |= ((buf[ i / 8 ] & (1 << (i % 8))) != 0) << j;

	curbit += code_size;

	return ret;
}

static int
LWZReadByte(fd, flag, input_code_size)
FILE	*fd;
int	flag;
int	input_code_size;
{
	static int	fresh = CVIP_NO;
	int		code, incode;
	static int	code_size, set_code_size;
	static int	max_code, max_code_size;
	static int	firstcode, oldcode;
	static int	clear_code, end_code;
	static int	table[2][(1<< MAX_LWZ_BITS)];
	static int	stack[(1<<(MAX_LWZ_BITS))*2], *sp;
	register int	i;

	if (flag) {
		set_code_size = input_code_size;
		code_size = set_code_size+1;
		clear_code = 1 << set_code_size ;
		end_code = clear_code + 1;
		max_code_size = 2*clear_code;
		max_code = clear_code+2;

		GetCode(fd, 0, CVIP_YES);
		
		fresh = CVIP_YES;

		for (i = 0; i < clear_code; ++i) {
			table[0][i] = 0;
			table[1][i] = i;
		}
		for (; i < (1<<MAX_LWZ_BITS); ++i)
			table[0][i] = table[1][0] = 0;

		sp = stack;

		return 0;
	} else if (fresh) {
		fresh = CVIP_NO;
		do {
			firstcode = oldcode =
				GetCode(fd, code_size, CVIP_NO);
		} while (firstcode == clear_code);
		return firstcode;
	}

	if (sp > stack)
		return *--sp;

	while ((code = GetCode(fd, code_size, CVIP_NO)) >= 0) {
		if (code == clear_code) {
			for (i = 0; i < clear_code; ++i) {
				table[0][i] = 0;
				table[1][i] = i;
			}
			for (; i < (1<<MAX_LWZ_BITS); ++i)
				table[0][i] = table[1][i] = 0;
			code_size = set_code_size+1;
			max_code_size = 2*clear_code;
			max_code = clear_code+2;
			sp = stack;
			firstcode = oldcode =
					GetCode(fd, code_size, CVIP_NO);
			return firstcode;
		} else if (code == end_code) {
			int		count;
			unsigned char	buf[260];

			if (ZeroDataBlock)
				return -2;

			while ((count = GetDataBlock(fd, buf)) > 0)
				;

			if (count != 0)
				pm_message("missing EOD in data stream (common occurence)");
			return -2;
		}

		incode = code;

		if (code >= max_code) {
			*sp++ = firstcode;
			code = oldcode;
		}

		while (code >= clear_code) {
			*sp++ = table[1][code];
			if (code == table[0][code])
				pm_error("circular table entry BIG ERROR");
			code = table[0][code];
		}

		*sp++ = firstcode = table[1][code];

		if ((code = max_code) <(1<<MAX_LWZ_BITS)) {
			table[0][code] = oldcode;
			table[1][code] = firstcode;
			++max_code;
			if ((max_code >= max_code_size) &&
				(max_code_size < (1<<MAX_LWZ_BITS))) {
				max_code_size *= 2;
				++code_size;
			}
		}

		oldcode = incode;

		if (sp > stack)
			return *--sp;
	}
	return code;
}

static Image *ReadImage(fd, len, height, cmap, interlace, ignore)
FILE	*fd;
int	len, height;
unsigned char	cmap[3][MAXCOLORMAPSIZE];
int	interlace, ignore;
{
	unsigned char	c, i;	
	int		v;
	int		xpos = 0, ypos = 0, pass = 0;
	pixel		**image;
	Image *gif_Image;
	byte **red_plane, **green_plane, **blue_plane;

	/*
	**  Initialize the Compression routines
	*/
	if (! ReadOK(fd,&c,1))
		pm_error("EOF / read error on image data" );

	if (LWZReadByte(fd, CVIP_YES, c) < 0)
		pm_error("error reading image" );

	/*
	**  If this is an "uninteresting picture" ignore it.
	*/
	if (ignore) {
		if (verbose)
			pm_message("skipping image..." );

		while (LWZReadByte(fd, CVIP_NO, c) >= 0)
			;
		return;
	}

	if ((gif_Image = image_allocate(GIF, RGB, 3, height, len, CVIP_BYTE, REAL)) == NULL)
		pm_error("couldn't alloc Image structure" );
		
	red_plane = (byte **) gif_Image->image_ptr[0]->rptr;
	green_plane = (byte **) gif_Image->image_ptr[1]->rptr;
	blue_plane = (byte **) gif_Image->image_ptr[2]->rptr;	
	
	if (verbose)
		pm_message("reading %d by %d%s GIF image",
			len, height, interlace ? " interlaced" : "" );

	while ((v = LWZReadByte(fd,CVIP_NO,c)) >= 0 ) {

		red_plane[ypos][xpos]   = cmap[CM_RED][v];
		green_plane[ypos][xpos] = cmap[CM_GREEN][v];
		blue_plane[ypos][xpos]  = cmap[CM_BLUE][v]; 

		++xpos;
		if (xpos == len) {
			xpos = 0;
			if (interlace) {
				switch (pass) {
				case 0:
				case 1:
					ypos += 8; break;
				case 2:
					ypos += 4; break;
				case 3:
					ypos += 2; break;
				}

				if (ypos >= height) {
					++pass;
					switch (pass) {
					case 1:
						ypos = 4; break;
					case 2:
						ypos = 2; break;
					case 3:
						ypos = 1; break;
					default:
						goto fini;
					}
				}
			} else {
				++ypos;
			}
		}
		if (ypos >= height)
			break;
	}

fini:
	if (LWZReadByte(fd,CVIP_NO,c)>=0)
		pm_message("too much input data, ignoring extra...");

	if (verbose) {
		pm_message("8 bits per sample.");
		pm_message("colormapped to 3 samples per pixel.\n");
	}
			  	
return gif_Image;
}
