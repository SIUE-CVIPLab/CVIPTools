/*
 * wrcvip.c
 *
 * Copyright (C) 1991-1996, Thomas G. Lane.
 * This file is part of the Independent JPEG Group's software.
 * For conditions of distribution and use, see the accompanying README file.
 *
 * This file contains routines to write output images in CVIP/PGM format.
 * The extended 2-byte-per-sample raw CVIP/PGM formats are supported.
 * The PBMPLUS library is NOT required to compile this software
 * (but it is highly useful as a set of CVIP image manipulation programs).
 *
 * These routines may need modification for non-Unix environments or
 * specialized applications.  As they stand, they assume output to
 * an ordinary stdio stream.
 */

#include "cdjpeg.h"		/* Common decls for cjpeg/djpeg applications */
#include <CVIPimage.h>		/* Common decls for cjpeg/djpeg applications */


/*
 * For 12-bit JPEG data, we either downscale the values to 8 bits
 * (to write standard byte-per-sample CVIP/PGM files), or output
 * nonstandard word-per-sample CVIP/PGM files.  Downscaling is done
 * if CVIP_NORAWWORD is defined (this can be done in the Makefile
 * or in jconfig.h).
 * (When the core library supports data precision reduction, a cleaner
 * implementation will be to ask for that instead.)
 */

#if BITS_IN_JSAMPLE == 8
#define GET_JPG_SAMPLE(v)  (char) (v)
#define BYTESPERSAMPLE 1
#define CVIP_MAXVAL 255
#else
#ifdef CVIP_NORAWWORD
#define GET_JPG_SAMPLE(v)  (char) ((v) >> (BITS_IN_JSAMPLE-8))
#define BYTESPERSAMPLE 1
#define CVIP_MAXVAL 255
#else
/* The word-per-sample format always puts the LSB first. */
#define GET_JPG_SAMPLE(v) (int) (v)
#define BYTESPERSAMPLE 2
#define CVIP_MAXVAL ((1<<BITS_IN_JSAMPLE)-1)
#endif
#endif


/*
 * When JSAMPLE is the same size as char, we can just fwrite() the
 * decompressed data to the CVIP or PGM file.  On PCs, in order to make this
 * work the output buffer must be allocated in near data space, because we are
 * assuming small-data memory model wherein fwrite() can't reach far memory.
 * If you need to process very wide images on a PC, you might have to compile
 * in large-memory model, or else replace fwrite() with a putc() loop ---
 * which will be much slower.
 */


/* Private version of data destination object */

typedef struct {
  struct djpeg_dest_struct pub;	/* public fields */
  char *iobuffer;
  JSAMPROW pixrow;
  size_t buffer_width;
  JDIMENSION samples_per_row;
} cvip_dest_struct;

typedef cvip_dest_struct * cvip_dest_ptr;


/*
 * Write some pixel data.
 * In this module rows_supplied will always be 1.
 *
 * put_pixel_rows handles the "normal" 8-bit case where the decompressor
 * output buffer is physically the same as the fwrite buffer.
 */

METHODDEF(void)
put_pixel_rows (j_decompress_ptr cinfo, djpeg_dest_ptr dinfo,
		JDIMENSION rows_supplied)
{
  cvip_dest_ptr dest = (cvip_dest_ptr) dinfo;

  (void) JFWRITE(dest->pub.output_file, dest->iobuffer, dest->buffer_width);
}


/*
 * This code is used when we have to copy the data and apply a pixel
 * format translation.  Typically this only happens in 12-bit mode.
 */

METHODDEF(void)
copy_pixel_rows (j_decompress_ptr cinfo, djpeg_dest_ptr dinfo,
		 JDIMENSION rows_supplied)
{
  cvip_dest_ptr dest = (cvip_dest_ptr) dinfo;
  register JSAMPROW ptr;
  register JDIMENSION col;

  ptr = dest->pub.buffer[0];
#if BITS_IN_JSAMPLE == 8
  if (cinfo->out_color_space != JCS_GRAYSCALE ) {
    for (col = dest->samples_per_row; col > 0; col-=3) {
      setPixel_Image(cinfo->cvipImage,byte,
    	 	(dest->samples_per_row-col)/3,cinfo->output_scanline-1,
    		0, (byte)GET_JPG_SAMPLE(GETJSAMPLE(*ptr++)));
      setPixel_Image(cinfo->cvipImage, byte,
    	   (dest->samples_per_row-col)/3, cinfo->output_scanline-1, 
    	   1, (byte)GET_JPG_SAMPLE(GETJSAMPLE(*ptr++)));
      setPixel_Image(cinfo->cvipImage, byte,
    	   (dest->samples_per_row-col)/3,cinfo->output_scanline-1, 
    	   2, (byte)GET_JPG_SAMPLE(GETJSAMPLE(*ptr++)));
    }
  } else {
    for (col = dest->samples_per_row; col > 0; col--) {
      setPixel_Image(cinfo->cvipImage,byte,
  	 	  dest->samples_per_row-col,cinfo->output_scanline-1,
  		  0, (byte)GET_JPG_SAMPLE(GETJSAMPLE(*ptr++)));
    }
  }
#else
  if (cinfo->out_color_space != JCS_GRAYSCALE ) {
    for (col = dest->samples_per_row; col > 0; col-=3) {
      setPixel_Image(cinfo->cvipImage,int,
    	 	(dest->samples_per_row-col)/3,cinfo->output_scanline-1,
    		0, (int)GET_JPG_SAMPLE(GETJSAMPLE(*ptr++)));
      setPixel_Image(cinfo->cvipImage, int,
    	   (dest->samples_per_row-col)/3, cinfo->output_scanline-1, 
    	   1, (int)GET_JPG_SAMPLE(GETJSAMPLE(*ptr++)));
      setPixel_Image(cinfo->cvipImage, int,
    	   (dest->samples_per_row-col)/3,cinfo->output_scanline-1, 
    	   2, (int)GET_JPG_SAMPLE(GETJSAMPLE(*ptr++)));
    }
  } else {
    for (col = dest->samples_per_row; col > 0; col--) {
      setPixel_Image(cinfo->cvipImage,int,
  	 	  dest->samples_per_row-col,cinfo->output_scanline-1,
  		  0, (int)GET_JPG_SAMPLE(GETJSAMPLE(*ptr++)));
    }
  }
#endif
}


/*
 * Write some pixel data when color quantization is in effect.
 * We have to demap the color index values to straight data.
 */

METHODDEF(void)
put_demapped_rgb (j_decompress_ptr cinfo, djpeg_dest_ptr dinfo,
		  JDIMENSION rows_supplied)
{
  cvip_dest_ptr dest = (cvip_dest_ptr) dinfo;
  register char * bufferptr;
  register int pixval;
  register JSAMPROW ptr;
  register JSAMPROW color_map0 = cinfo->colormap[0];
  register JSAMPROW color_map1 = cinfo->colormap[1];
  register JSAMPROW color_map2 = cinfo->colormap[2];
  register JDIMENSION col;

  ptr = dest->pub.buffer[0];
  bufferptr = dest->iobuffer;
#if BITS_IN_JSAMPLE == 8
  for (col = cinfo->output_width; col > 0; col--) {
    pixval = GETJSAMPLE(*ptr++);
    setPixel_Image(cinfo->cvipImage, byte,
	   cinfo->output_width-col, cinfo->output_scanline-1,
      0, (byte)GET_JPG_SAMPLE(GETJSAMPLE(color_map0[pixval])));
    setPixel_Image(cinfo->cvipImage, byte,
	   cinfo->output_width-col, cinfo->output_scanline-1,
      1, (byte)GET_JPG_SAMPLE(GETJSAMPLE(color_map1[pixval])));
    setPixel_Image(cinfo->cvipImage, byte,
	   cinfo->output_width-col, cinfo->output_scanline-1,
      2, (byte)GET_JPG_SAMPLE(GETJSAMPLE(color_map2[pixval])));
  }
#else
  for (col = cinfo->output_width; col > 0; col--) {
    pixval = GETJSAMPLE(*ptr++);
    setPixel_Image(cinfo->cvipImage, int,
	   cinfo->output_width-col, cinfo->output_scanline-1,
      0, (int)GET_JPG_SAMPLE(GETJSAMPLE(color_map0[pixval])));
    setPixel_Image(cinfo->cvipImage, int,
	   cinfo->output_width-col, cinfo->output_scanline-1,
      1, (int)GET_JPG_SAMPLE(GETJSAMPLE(color_map1[pixval])));
    setPixel_Image(cinfo->cvipImage, int,
	   cinfo->output_width-col, cinfo->output_scanline-1,
      2, (int)GET_JPG_SAMPLE(GETJSAMPLE(color_map2[pixval])));
  }
#endif
}


METHODDEF(void)
put_demapped_gray (j_decompress_ptr cinfo, djpeg_dest_ptr dinfo,
		   JDIMENSION rows_supplied)
{
  cvip_dest_ptr dest = (cvip_dest_ptr) dinfo;
  register char * bufferptr;
  register JSAMPROW ptr;
  register JSAMPROW color_map = cinfo->colormap[0];
  register JDIMENSION col;

  ptr = dest->pub.buffer[0];
  bufferptr = dest->iobuffer;
#if BITS_IN_JSAMPLE == 8
  for (col = cinfo->output_width; col > 0; col--) {
    setPixel_Image(cinfo->cvipImage, byte, 
	   cinfo->output_width-col, cinfo->output_scanline-1,
      0, (byte)GET_JPG_SAMPLE(GETJSAMPLE(color_map[GETJSAMPLE(*ptr++)])));
  }
#else
    setPixel_Image(cinfo->cvipImage, int,
	   cinfo->output_width-col, cinfo->output_scanline-1, 0,
		(int)GET_JPG_SAMPLE(GETJSAMPLE(color_map[GETJSAMPLE(*ptr++)])));
#endif
}


/*
 * Startup: write the file header.
 */

METHODDEF(void)
start_output_cvip (j_decompress_ptr cinfo, djpeg_dest_ptr dinfo)
{
  cvip_dest_ptr dest = (cvip_dest_ptr) dinfo;

  /* Emit file header */
  switch (cinfo->out_color_space) {
  case JCS_GRAYSCALE:
#if BITS_IN_JSAMPLE == 8
	 cinfo->cvipImage = (Image *)new_Image(JPG, GRAY_SCALE, 1,
		 cinfo->image_height, cinfo->image_width, CVIP_BYTE, REAL);
#else
	 cinfo->cvipImage = (Image *)new_Image(JPG, GRAY_SCALE, 1,
		 cinfo->image_height, cinfo->image_width, CVIP_INTEGER, REAL);
#endif
    break;
  case JCS_RGB:
#if BITS_IN_JSAMPLE == 8
	 cinfo->cvipImage = (Image *)new_Image(JPG, RGB, 3,
		 cinfo->image_height, cinfo->image_width, CVIP_BYTE, REAL);
#else
	 cinfo->cvipImage = (Image *)new_Image(JPG, RGB, 3,
		 cinfo->image_height, cinfo->image_width, CVIP_INTEGER, REAL);
#endif
    break;
  default:
    ERREXIT(cinfo, JERR_CVIP_COLORSPACE);
  }
}


/*
 * Finish up at the end of the file.
 */

METHODDEF(void)
finish_output_cvip (j_decompress_ptr cinfo, djpeg_dest_ptr dinfo)
{
  /* Make sure we wrote the output file OK */
/*  fflush(dinfo->output_file);
  if (ferror(dinfo->output_file))
    ERREXIT(cinfo, JERR_FILE_WRITE); */
}


/*
 * The module selection routine for CVIP format output.
 */

GLOBAL(djpeg_dest_ptr)
jinit_write_cvip (j_decompress_ptr cinfo)
{
  cvip_dest_ptr dest;

  /* Create module interface object, fill in method pointers */
  dest = (cvip_dest_ptr)
      (*cinfo->mem->alloc_small) ((j_common_ptr) cinfo, JPOOL_IMAGE,
				  SIZEOF(cvip_dest_struct));
  dest->pub.start_output = start_output_cvip;
  dest->pub.finish_output = finish_output_cvip;

  /* Calculate output image dimensions so we can allocate space */
  jpeg_calc_output_dimensions(cinfo);

  /* Create physical I/O buffer.  Note we make this near on a PC. */
  dest->samples_per_row = cinfo->output_width * cinfo->out_color_components;
  dest->buffer_width = dest->samples_per_row * (BYTESPERSAMPLE * SIZEOF(char));
  dest->iobuffer = (char *) (*cinfo->mem->alloc_small)
    ((j_common_ptr) cinfo, JPOOL_IMAGE, dest->buffer_width); 

  dest->pub.buffer_height = 1;

    /* When quantizing, we need an output buffer for colormap indexes
     * that's separate from the physical I/O buffer.  We also need a
     * separate buffer if pixel format translation must take place.
     */
    dest->pub.buffer = (*cinfo->mem->alloc_sarray)
      ((j_common_ptr) cinfo, JPOOL_IMAGE,
       cinfo->output_width * cinfo->output_components, (JDIMENSION) 1);
    if (! cinfo->quantize_colors)
      dest->pub.put_pixel_rows = copy_pixel_rows;
    else if (cinfo->out_color_space == JCS_GRAYSCALE)
      dest->pub.put_pixel_rows = put_demapped_gray;
    else
      dest->pub.put_pixel_rows = put_demapped_rgb;
  return (djpeg_dest_ptr) dest;
}
