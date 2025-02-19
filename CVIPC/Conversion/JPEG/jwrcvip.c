/*
 * rdppm.c
 *
 * Copyright (C) 1991-1996, Thomas G. Lane.
 * This file is part of the Independent JPEG Group's software.
 * For conditions of distribution and use, see the accompanying README file.
 *
 * This file contains routines to read input images in PPM/PGM format.
 * The extended 2-byte-per-sample raw PPM/PGM formats are supported.
 * The PBMPLUS library is NOT required to compile this software
 * (but it is highly useful as a set of PPM image manipulation programs).
 *
 * These routines may need modification for non-Unix environments or
 * specialized applications.  As they stand, they assume input from
 * an ordinary stdio stream.  They further assume that reading begins
 * at the start of the file; start_input may need work if the
 * user interface has already read some data (e.g., to determine that
 * the file is indeed PPM format).
 */

#include "cdjpeg.h"		/* Common decls for cjpeg/djpeg applications */
#include <CVIPimage.h>

/* Portions of this code are based on the PBMPLUS library, which is:
**
** Copyright (C) 1988 by Jef Poskanzer.
**
** Permission to use, copy, modify, and distribute this software and its
** documentation for any purpose and without fee is hereby granted, provided
** that the above copyright notice appear in all copies and that both that
** copyright notice and this permission notice appear in supporting
** documentation.  This software is provided "as is" without express or
** implied warranty.
*/

#ifdef HAVE_UNSIGNED_CHAR
typedef unsigned char U_CHAR;
#define UCH(x)	((int) (x))
#else /* !HAVE_UNSIGNED_CHAR */
#ifdef CHAR_IS_UNSIGNED
typedef char U_CHAR;
#define UCH(x)	((int) (x))
#else
typedef char U_CHAR;
#define UCH(x)	((int) (x) & 0xFF)
#endif
#endif /* HAVE_UNSIGNED_CHAR */

/* Private version of data source object */

typedef struct {
  struct cjpeg_source_struct pub; /* public fields */

  U_CHAR *iobuffer; 
  JSAMPROW pixrow;
  size_t buffer_width;
  JSAMPLE *rescale;
} cvip_source_struct;

typedef cvip_source_struct * cvip_source_ptr;


/*
 * Read one row of pixels.
 *
 * We provide several different versions depending on input file format.
 * In all cases, input is scaled to the size of JSAMPLE.
 *
 * A really fast path is provided for reading byte/sample raw files with
 * maxval = MAXJSAMPLE, which is the normal case for 8-bit data.
 */


METHODDEF(JDIMENSION)
get_text_gray_row (j_compress_ptr cinfo, cjpeg_source_ptr sinfo)
/* This version is for reading text-format PGM files with any maxval */
{
  cvip_source_ptr source = (cvip_source_ptr) sinfo;
  FILE * infile = source->pub.input_file;
  register JSAMPROW ptr;
  register JSAMPLE *rescale = source->rescale;
  JDIMENSION col;
  unsigned row = cinfo->next_row;

  ptr = source->pub.buffer[0];
  for (col = cinfo->image_width; col > 0; col--) {
    *ptr++ = rescale[(unsigned int) getRealPixel_Image(cinfo->cvipImage,
	 	byte, cinfo->image_width-col,row,0)];
  }
  cinfo->next_row++;
  return 1;
}


METHODDEF(JDIMENSION)
get_text_rgb_row (j_compress_ptr cinfo, cjpeg_source_ptr sinfo)
/* This version is for reading text-format PPM files with any maxval */
{
  cvip_source_ptr source = (cvip_source_ptr) sinfo;
  FILE * infile = source->pub.input_file;
  register JSAMPROW ptr;
  register JSAMPLE *rescale = source->rescale;
  JDIMENSION col;
  unsigned row = cinfo->next_row;
  unsigned int val;

  ptr = source->pub.buffer[0];
  for (col = cinfo->image_width; col > 0; col--) {
	 val = (unsigned) getRealPixel_Image(cinfo->cvipImage, byte,
                     cinfo->image_width-col, row,0); *ptr++ = rescale[val]; 
	 val = (unsigned) getRealPixel_Image(cinfo->cvipImage, byte,
                     cinfo->image_width-col, row,1); *ptr++ = rescale[val]; 
	 val = (unsigned) getRealPixel_Image(cinfo->cvipImage, byte,
                     cinfo->image_width-col, row,2); *ptr++ = rescale[val]; 
  }
  cinfo->next_row++;
  return 1;
}



/*
 * Read the file header; return image size and component count.
 */

METHODDEF(void)
start_input_cvip (j_compress_ptr cinfo, cjpeg_source_ptr sinfo)
{
  cvip_source_ptr source = (cvip_source_ptr) sinfo;
  int c;
  CVIP_BOOLEAN need_iobuffer, use_raw_buffer, need_rescale;
  unsigned int w, h, maxval, bands;
  Image * inputImage = cinfo->cvipImage;

  bands = getNoOfBands_Image(inputImage);
  h =  getNoOfRows_Image(inputImage);
  w =  getNoOfCols_Image(inputImage);

  maxval = 255;

  cinfo->data_precision = BITS_IN_JSAMPLE; /* we always rescale data to this */
  cinfo->image_width = (JDIMENSION) w;
  cinfo->image_height = (JDIMENSION) h;

  /* initialize flags to most common settings */
  need_iobuffer = CVIP_YES;		/* do we need an I/O buffer? */
  use_raw_buffer = CVIP_NO;	/* do we map input buffer onto I/O buffer? */
  need_rescale = CVIP_YES;		/* do we need a rescale array? */

  if(bands==1)
  {
    cinfo->input_components = bands;
    cinfo->in_color_space = JCS_GRAYSCALE;
    TRACEMS2(cinfo, 1, JTRC_CVIP_TEXT, w, h);
    source->pub.get_pixel_rows = get_text_gray_row;
    need_iobuffer = CVIP_NO;
  } else {
    cinfo->input_components = bands;
    cinfo->in_color_space = JCS_RGB;
    TRACEMS2(cinfo, 1, JTRC_CVIP_TEXT, w, h);
    source->pub.get_pixel_rows = get_text_rgb_row;
    need_iobuffer = CVIP_NO;
  }

  /* Create compressor input buffer. */
  if (use_raw_buffer) {
    /* For unscaled raw-input case, we can just map it onto the I/O buffer. */
    /* Synthesize a JSAMPARRAY pointer structure */
    /* Cast here implies near->far pointer conversion on PCs */
    source->pixrow = (JSAMPROW) source->iobuffer;
    source->pub.buffer = & source->pixrow;
    source->pub.buffer_height = 1;
  } else {
    /* Need to translate anyway, so make a separate sample buffer. */
    source->pub.buffer = (*cinfo->mem->alloc_sarray)
      ((j_common_ptr) cinfo, JPOOL_IMAGE,
       (JDIMENSION) w * cinfo->input_components, (JDIMENSION) 1);
    source->pub.buffer_height = 1;
  }

  /* Compute the rescaling array if required. */
  if (need_rescale) {
    INT32 val, half_maxval;

    /* On 16-bit-int machines we have to be careful of maxval = 65535 */
    source->rescale = (JSAMPLE *)
      (*cinfo->mem->alloc_small) ((j_common_ptr) cinfo, JPOOL_IMAGE,
				  (size_t) (((long) maxval + 1L) * SIZEOF(JSAMPLE)));
    half_maxval = maxval / 2;
    for (val = 0; val <= (INT32) maxval; val++) {
      /* The multiplication here must be done in 32 bits to avoid overflow */
      source->rescale[val] = (JSAMPLE) ((val*MAXJSAMPLE + half_maxval)/maxval);
    }
  }
}


/*
 * Finish up at the end of the file.
 */

METHODDEF(void)
finish_input_cvip (j_compress_ptr cinfo, cjpeg_source_ptr sinfo)
{
  /* no work */
}


/*
 * The module selection routine for PPM format input.
 */

GLOBAL(cjpeg_source_ptr)
jinit_read_cvip (j_compress_ptr cinfo)
{
  cvip_source_ptr source;
  /* Create module interface object */
  source = (cvip_source_ptr)
      (*cinfo->mem->alloc_small) ((j_common_ptr) cinfo, JPOOL_IMAGE,
				  SIZEOF(cvip_source_struct));
  /* Fill in method ptrs, except get_pixel_rows which start_input sets */
  source->pub.start_input = start_input_cvip;
  source->pub.finish_input = finish_input_cvip;
  return (cjpeg_source_ptr) source;
}
