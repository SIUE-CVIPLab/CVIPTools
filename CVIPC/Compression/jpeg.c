/***************************************************************************
* RCS (Revision Control System) Information
* ...Added automatically by RCS 
*
** $Log: jpeg.c,v $
** Revision 1.4  1997/06/20 16:11:55  wzheng
** *** empty log message ***
**
** Revision 1.3  1997/06/06 16:21:05  wzheng
** add grayscale convert function
**
** Revision 1.2  1997/06/04 14:46:04  wzheng
** memory leak
**
** Revision 1.1  1997/05/26 22:35:23  yawei
** Initial revision
**
*
****************************************************************************/
/*
 * cjpeg.c
 *
 * Copyright (C) 1991-1998, Thomas G. Lane.
 * This file is part of the Independent JPEG Group's software.
 * For conditions of distribution and use, see the accompanying README file.
 *
 * This file contains a command-line user interface for the JPEG compressor.
 * It should work on any system with Unix- or MS-DOS-style command lines.
 *
 * Two different command line styles are permitted, depending on the
 * compile-time switch TWO_FILE_COMMANDLINE:
 *	cjpeg [options]  inputfile outputfile
 *	cjpeg [options]  [inputfile]
 * In the second style, output is always to standard output, which you'd
 * normally redirect to a file or pipe to some other program.  Input is
 * either from a named file or from standard input (typically redirected).
 * The second style is convenient on Unix but is unhelpful on systems that
 * don't support pipes.  Also, you MUST use the first style if your system
 * doesn't do binary I/O to stdin/stdout.
 * To simplify script writing, the "-outfile" switch is provided.  The syntax
 *	cjpeg [options]  -outfile outputfile  inputfile
 * works regardless of which command line style is used.
 */

#include <sys/stat.h>
#include <sys/types.h>
#include "cdjpeg.h"		/* Common decls for cjpeg/djpeg applications */
#include "jversion.h"		/* for version message */
#include <CVIPtoolkit.h>		/* for version message */

#include <ctype.h>		/* to declare isprint() */
#ifdef USE_CCOMMAND		/* command-line reader for Macintosh */
#ifdef __MWERKS__
#include <SIOUX.h>              /* Metrowerks needs this */
#include <console.h>		/* ... and this */
#endif
#ifdef THINK_C
#include <console.h>		/* Think declares it here */
#endif
#endif


/* Create the add-on message string table. */

#define JMESSAGE(code,string)	string ,

static const char * const cdjpeg_message_table[] = {
#include "cderror.h"
  NULL
};



/*
 * Argument-parsing code.
 * The switch parser is designed to be useful with DOS-style command line
 * syntax, ie, intermixed switches and file names, where only the switches
 * to the left of a given file name affect processing of that file.
 * The main program in this file doesn't actually use this capability...
 */

LOCAL(int)
parse_switches (j_compress_ptr cinfo, int quality, char *qtablesFile, 
	CVIP_BOOLEAN grayscale, CVIP_BOOLEAN optimize)
/* Parse optional switches.
 * modified for CVIP only
 */
{
  int q_scale_factor = 100;		/* scaling percentage for -qtables */
  CVIP_BOOLEAN force_baseline = CVIP_NO;

  cinfo->err->trace_level = 0;

  if (grayscale == CVIP_YES) jpeg_set_colorspace(cinfo, JCS_GRAYSCALE);
  cinfo->optimize_coding = optimize;
  
  /* Set quantization tables for selected quality. */
  /* Some or all may be overridden if -qtables is present. */

  quality = (quality == -1) ? 75 : quality;
  jpeg_set_quality(cinfo, quality, force_baseline);
  /* Change scale factor in case -qtables is present. */
  q_scale_factor = jpeg_quality_scaling(quality);

  if (qtablesFile != NULL)	/* process -qtables if it was present */
      read_quant_tables(cinfo, qtablesFile, q_scale_factor, force_baseline);

  return 1;

}

static const char * funcname;	/* program name for error messages */

int jpg_compress(Image *cvipImage, char *filename, int quality, 
	CVIP_BOOLEAN grayscale, CVIP_BOOLEAN optimize, int smooth, 
	CVIP_BOOLEAN verbose, char *qtablesFile)
{
  struct jpeg_compress_struct cinfo;
  struct jpeg_error_mgr jerr;
#ifdef PROGRESS_REPORT
  struct cdjpeg_progress_mgr progress;
#endif
  int file_index;
  cjpeg_source_ptr src_mgr;
  FILE * output_file;
  JDIMENSION num_scanlines;

  struct stat s_buf;        /*structure used to contain file info */
  int rows=0, cols=0, bands=0;
  long counter;

  /* get the original image info */
  rows = getNoOfRows_Image(cvipImage);
  cols = getNoOfCols_Image(cvipImage);
  bands = getNoOfBands_Image(cvipImage);


  /* On Mac, fetch a command line. */
#ifdef USE_CCOMMAND
  argc = ccommand(&argv);
#endif

  funcname = "jpg_compress";
/*  qtablesFile = "quant.txt";	*/

  /* Initialize the JPEG compression object with default error handling. */
  cinfo.err = jpeg_std_error(&jerr);
  jpeg_create_compress(&cinfo);
  /* Add some application-specific error messages (from cderror.h) */
  jerr.addon_message_table = cdjpeg_message_table;
  jerr.first_addon_message = JMSG_FIRSTADDONCODE;
  jerr.last_addon_message = JMSG_LASTADDONCODE;

  /* Now safe to enable signal catcher. */
#ifdef NEED_SIGNAL_CATCHER
  enable_signal_catcher((j_common_ptr) &cinfo);
#endif

  /* Initialize JPEG parameters.
   * Much of this may be overridden later.
   * In particular, we don't yet know the input file's color space,
   * but we need to provide some value for jpeg_set_defaults() to work.
   */

  cinfo.in_color_space = JCS_RGB; /* arbitrary guess */
  jpeg_set_defaults(&cinfo);
  cinfo.cvipImage = cvipImage;
  cinfo.next_row = 0; /* first row to read */


  /* Open the output file. */
  if ((output_file = fopen(filename, WRITE_BINARY)) == NULL) {
    fprintf(stderr, "%s: can't open %s\n", funcname, filename);
    /*exit(EXIT_FAILURE); */
  if (cvipImage) delete_Image(cvipImage);
	 return -1;
  }

#ifdef PROGRESS_REPORT
  start_progress_monitor((j_common_ptr) &cinfo, &progress);
#endif

  /* Figure out the input file format, and set up to read it. */
  src_mgr = jinit_read_cvip(&cinfo);
  src_mgr->input_file = (FILE *)NULL;

  /* Adjust default compression parameters by re-parsing the options */
  /* parse_switches (&cinfo, quality, qtablesFile, grayscale, optimize); */
  /* cinfo.smoothing_factor = smooth; */

  /* Read the input file header to obtain file size & colorspace. */
  (*src_mgr->start_input) (&cinfo, src_mgr);

  /* Now that we know input colorspace, fix colorspace-dependent defaults */
  jpeg_default_colorspace(&cinfo);

  /* Adjust default compression parameters by re-parsing the options */
  parse_switches (&cinfo, quality, qtablesFile,grayscale, optimize);
  cinfo.smoothing_factor = smooth;

  if (verbose == CVIP_YES) {
      /* Enable debug printouts. */
      /* On first -d, print version identification */
      /*
       *if (cinfo.emethods->trace_level == 0)
       *  fprintf(stderr, "Independent JPEG Group's CJPEG, version
       *  %s\n%s\n",
       *  JVERSION, JCOPYRIGHT);
       *cinfo.emethods->trace_level++;
       */
  }

  /* Specify data destination for compression */
  jpeg_stdio_dest(&cinfo, output_file);

  /* Start compressor */
  jpeg_start_compress(&cinfo, CVIP_YES);

  /* Process data */
  while (cinfo.next_scanline < cinfo.image_height) {
    num_scanlines = (*src_mgr->get_pixel_rows) (&cinfo, src_mgr);
    (void) jpeg_write_scanlines(&cinfo, src_mgr->buffer, num_scanlines);
  }

  /* Finish compression and release memory */
  (*src_mgr->finish_input) (&cinfo, src_mgr);
  jpeg_finish_compress(&cinfo);
  jpeg_destroy_compress(&cinfo);

  /* Close files, if we opened them */
  if (output_file != stdout)
    fclose(output_file);

#ifdef PROGRESS_REPORT
  end_progress_monitor((j_common_ptr) &cinfo);
#endif

  /* All done. */
  /*exit(jerr.num_warnings ? EXIT_WARNING : EXIT_SUCCESS); */
  /* calculate and print the compression ratio */
  if (stat(filename, &s_buf)==0){
    counter = (long)s_buf.st_size;
    printf("\n\tThe original raw data occupies %ld bytes",rows*cols*bands);
    printf("\n\tThe compressed data occupies %ld bytes",counter);
    printf("\n\tCompression ratio : %.2f\n\n",(rows*cols*bands)/(float)counter);
  }

  if (cvipImage) delete_Image(cvipImage);

  return 0;			/* suppress no-return-value warnings */
}

/************************ decompress *************************************/
/*
 * djpeg.c
 *
 * Copyright (C) 1991-1997, Thomas G. Lane.
 * This file is part of the Independent JPEG Group's software.
 * For conditions of distribution and use, see the accompanying README file.
 *
 * This file contains a command-line user interface for the JPEG decompressor.
 * It should work on any system with Unix- or MS-DOS-style command lines.
 *
 * Two different command line styles are permitted, depending on the
 * compile-time switch TWO_FILE_COMMANDLINE:
 *	djpeg [options]  inputfile outputfile
 *	djpeg [options]  [inputfile]
 * In the second style, output is always to standard output, which you'd
 * normally redirect to a file or pipe to some other program.  Input is
 * either from a named file or from standard input (typically redirected).
 * The second style is convenient on Unix but is unhelpful on systems that
 * don't support pipes.  Also, you MUST use the first style if your system
 * doesn't do binary I/O to stdin/stdout.
 * To simplify script writing, the "-outfile" switch is provided.  The syntax
 *	djpeg [options]  -outfile outputfile  inputfile
 * works regardless of which command line style is used.
 */

/*
 * This list defines the known output image formats
 * (not all of which need be supported by a given version).
 */

typedef enum {
	FMT_BMP,		/* BMP format (Windows flavor) */
	FMT_GIF,		/* GIF format */
	FMT_OS2,		/* BMP format (OS/2 flavor) */
	FMT_PPM,		/* PPM/PGM (PBMPLUS formats) */
	FMT_RLE,		/* RLE format */
   FMT_CVIP,   /* CVIP format */
	FMT_TARGA,		/* Targa format */
	FMT_TIFF		/* TIFF format */
} IMAGE_FORMATS;


static IMAGE_FORMATS requested_fmt;

/*
 * Argument-parsing code.
 * The switch parser is designed to be useful with DOS-style command line
 * syntax, ie, intermixed switches and file names, where only the switches
 * to the left of a given file name affect processing of that file.
 * The main program in this file doesn't actually use this capability...
 */


LOCAL(int)
parse_switches_decom (j_decompress_ptr cinfo, int colors,
	CVIP_BOOLEAN nodither, CVIP_BOOLEAN grayscale, CVIP_BOOLEAN blocksmooth)
/* Parse optional switches.
 * Returns argv[] index of first file-name argument (== argc if none).
 * Any file names with indexes <= last_file_arg_seen are ignored;
 * they have presumably been processed in a previous iteration.
 * (Pass 0 for last_file_arg_seen on the first or only iteration.)
 * for_real is CVIP_NO on the first (dummy) pass; we may skip any expensive
 * processing.
 */
{

  /* Set up default JPEG parameters. */
  cinfo->err->trace_level = 0;

  /* Scan command line options, adjust parameters */

  if (colors > 0) {
		cinfo->desired_number_of_colors = colors;
		cinfo->quantize_colors = CVIP_YES;
  }
  if (nodither == CVIP_YES) {
		cinfo->dither_mode = JDITHER_NONE;
  } else {
		cinfo->dither_mode = JDITHER_FS;
  }
  if (grayscale == CVIP_YES) {
		cinfo->out_color_space = JCS_GRAYSCALE;
  } else if (colors > 0) {
		cinfo->desired_number_of_colors = colors;
		cinfo->quantize_colors = CVIP_YES;
  }

  cinfo->do_block_smoothing = blocksmooth;
  return 1;
}


/*
 * Marker processor for COM and interesting APPn markers.
 * This replaces the library's built-in processor, which just skips the marker.
 * We want to print out the marker as text, to the extent possible.
 * Note this code relies on a non-suspending data source.
 */

LOCAL(unsigned int)
jpeg_getc (j_decompress_ptr cinfo)
/* Read next byte */
{
  struct jpeg_source_mgr * datasrc = cinfo->src;

  if (datasrc->bytes_in_buffer == 0) {
    if (! (*datasrc->fill_input_buffer) (cinfo))
      ERREXIT(cinfo, JERR_CANT_SUSPEND);
  }
  datasrc->bytes_in_buffer--;
  return GETJOCTET(*datasrc->next_input_byte++);
}


METHODDEF(CVIP_BOOLEAN)
COM_handler (j_decompress_ptr cinfo)
{
  CVIP_BOOLEAN traceit = (cinfo->err->trace_level >= 1);
  INT32 length;
  unsigned int ch;
  unsigned int lastch = 0;

  length = jpeg_getc(cinfo) << 8;
  length += jpeg_getc(cinfo);
  length -= 2;			/* discount the length word itself */

  if (traceit)
    fprintf(stderr, "Comment, length %ld:\n", (long) length);

  while (--length >= 0) {
    ch = jpeg_getc(cinfo);
    if (traceit) {
      /* Emit the character in a readable form.
       * Nonprintables are converted to \nnn form,
       * while \ is converted to \\.
       * Newlines in CR, CR/LF, or LF form will be printed as one newline.
       */
      if (ch == '\r') {
	fprintf(stderr, "\n");
      } else if (ch == '\n') {
	if (lastch != '\r')
	  fprintf(stderr, "\n");
      } else if (ch == '\\') {
	fprintf(stderr, "\\\\");
      } else if (isprint(ch)) {
	putc(ch, stderr);
      } else {
	fprintf(stderr, "\\%03o", ch);
      }
      lastch = ch;
    }
  }

  if (traceit)
    fprintf(stderr, "\n");

  return CVIP_YES;
}


Image *jpg_decompression(FILE *fp, int colors, CVIP_BOOLEAN blocksmooth,
      CVIP_BOOLEAN grayscale, CVIP_BOOLEAN nodither, CVIP_BOOLEAN verbose)
{
  struct jpeg_decompress_struct cinfo;
  struct jpeg_error_mgr jerr;
#ifdef PROGRESS_REPORT
  struct cdjpeg_progress_mgr progress;
#endif
  int file_index;
  djpeg_dest_ptr dest_mgr = NULL;
  FILE * input_file = fp;
  FILE * output_file = (FILE *)NULL;
  JDIMENSION num_scanlines;

  /* On Mac, fetch a command line. */
#ifdef USE_CCOMMAND
  argc = ccommand(&argv);
#endif

  funcname = "jpg_decompression";

  /* Initialize the JPEG decompression object with default error handling. */
  cinfo.err = jpeg_std_error(&jerr);
  jpeg_create_decompress(&cinfo);
  /* Add some application-specific error messages (from cderror.h) */
  jerr.addon_message_table = cdjpeg_message_table;
  jerr.first_addon_message = JMSG_FIRSTADDONCODE;
  jerr.last_addon_message = JMSG_LASTADDONCODE;

  /* Insert custom marker processor for COM and APP12.
   * APP12 is used by some digital camera makers for textual info,
   * so we provide the ability to display it as text.
   * If you like, additional APPn marker types can be selected for display,
   * but don't try to override APP0 or APP14 this way (see libjpeg.doc).
   */
  jpeg_set_marker_processor(&cinfo, JPEG_COM, COM_handler);
  jpeg_set_marker_processor(&cinfo, JPEG_APP0+12, COM_handler);

  /* Now safe to enable signal catcher. */
#ifdef NEED_SIGNAL_CATCHER
  enable_signal_catcher((j_common_ptr) &cinfo);
#endif

  /* no need to open any files */

#ifdef PROGRESS_REPORT
  start_progress_monitor((j_common_ptr) &cinfo, &progress);
#endif

  /* Specify data source for decompression */
  jpeg_stdio_src(&cinfo, input_file);

  /* Read file header, set default decompression parameters */
  (void) jpeg_read_header(&cinfo, CVIP_YES);

  /* Adjust default decompression parameters by re-parsing the options */
  parse_switches_decom(&cinfo, colors, nodither, grayscale, blocksmooth);

  /* Initialize the output module now to let it override any crucial
   * option settings (for instance, GIF wants to force color quantization).
   */
  dest_mgr = jinit_write_cvip(&cinfo);

  dest_mgr->output_file = output_file;

  /* Start decompressor */
  (void) jpeg_start_decompress(&cinfo);

  /* Write output file header */
  (*dest_mgr->start_output) (&cinfo, dest_mgr);

  /* Process data */
  while (cinfo.output_scanline < cinfo.output_height) {
    num_scanlines = jpeg_read_scanlines(&cinfo, dest_mgr->buffer,
					dest_mgr->buffer_height);
    (*dest_mgr->put_pixel_rows) (&cinfo, dest_mgr, num_scanlines);
  }

#ifdef PROGRESS_REPORT
  /* Hack: count final pass as done in case finish_output does an extra pass.
   * The library won't have updated completed_passes.
   */
  progress.pub.completed_passes = progress.pub.total_passes;
#endif

  /* Finish decompression and release memory.
   * I must do it in this order because output module has allocated memory
   * of lifespan JPOOL_IMAGE; it needs to finish before releasing memory.
   */
  (*dest_mgr->finish_output) (&cinfo, dest_mgr);
  (void) jpeg_finish_decompress(&cinfo);
  jpeg_destroy_decompress(&cinfo);

  /* Close files not needed, done at upper level */
  

#ifdef PROGRESS_REPORT
  end_progress_monitor((j_common_ptr) &cinfo);
#endif

  /* All done. */
  /*exit(jerr.num_warnings ? EXIT_WARNING : EXIT_SUCCESS); */
  return cinfo.cvipImage;			/* suppress no-return-value warnings */

}

Image* jpg_decompress(char *filename, int colors, CVIP_BOOLEAN blocksmooth,
       CVIP_BOOLEAN grayscale, CVIP_BOOLEAN nodither, CVIP_BOOLEAN verbose) {
    FILE               *fp;
    Image *    cvipImage;
 
    if((fp=fopen(filename,"rb"))==NULL){
       printf("cannot open %s file to read\n", filename);
       return NULL;
    }
    cvipImage = jpg_decompression(fp, colors, blocksmooth, grayscale,
					 nodither, verbose);
    fclose(fp);
    return cvipImage;
}

