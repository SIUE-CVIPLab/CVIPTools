/***************************************************************************
* ======================================================================
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* ======================================================================
*
*             File Name: CVIPcmap.h
*           Description: header file for colormap routines in CVIPtools
*			 NOTE: these functions need to be altered to work
*			 more effeciently with CVIPtools -- they are currently
*			 adapted directly from libppm.
*         Related Files: cmap.c, Imakefile
*   Initial Coding Date: Sun May 30 13:54:44 CDT 1993
*           Portability: Standard (ANSI) C
*             Credit(s): Gregory Hance
*                        Southern Illinois University @ Edwardsville
*
** Copyright (C) 1993 SIUE - by Gregory Hance.
**
** Permission to use, copy, modify, and distribute this software and its
** documentation for any purpose and without fee is hereby granted, provided
** that the above copyright notice appear in all copies and that both that
** copyright notice and this permission notice appear in supporting
** documentation.  This software is provided "as is" without express or
** implied warranty.
**
* RCS (Revision Control System) Information
* ...Added automatically by RCS 
*
** $Log: CVIPcmap.h,v $
 * Revision 1.2  1997/01/15  17:09:50  yawei
 * Global Change:  IMAGE ==> Image
 *
 * Revision 1.1  1994/10/30  22:43:06  hanceg
 * Initial revision
 *
 * Revision 1.1  1993/05/31  03:23:37  hanceg
 * Initial revision
 *
*
****************************************************************************/
#if !defined(CVIPCMAP_DEFINED)

   #define CVIPCMAP_DEFINED

   #define ARGS(alist) alist

   typedef struct {
      byte r, g, b;
   } pixel;

   #define PPM_GETR(p) ((p).r)
   #define PPM_GETG(p) ((p).g)
   #define PPM_GETB(p) ((p).b)
   #define PPM_ASSIGN(p,red,grn,blu) do { (p).r = (red); (p).g = (grn); (p).b = (blu); } while ( 0 )
   #define PPM_EQUAL(p,q) ( (p).r == (q).r && (p).g == (q).g && (p).b == (q).b )
   #define PPM_LUMIN(p) ( 0.299 * PPM_GETR(p) + 0.587 * PPM_GETG(p) + 0.114 * PPM_GETB(p) )

   /* Color histogram stuff. */

   typedef struct colorhist_item* colorhist_vector;
   struct colorhist_item {
      pixel color;
      unsigned int value;
   };

   typedef struct colorhist_list_item* colorhist_list;
   struct colorhist_list_item {
      struct colorhist_item ch;
      colorhist_list next;
   };

   extern colorhist_vector ppm_computecolorhist ARGS(( pixel** pixels, int cols,  int rows, int maxcolors, int* colorsP ));
   /* Returns a colorhist *colorsP long (with space allocated for maxcolors. */

   extern void ppm_addtocolorhist ARGS(( colorhist_vector chv, int* colorsP, int  maxcolors, pixel* colorP, int value, int position ));

   extern void ppm_freecolorhist ARGS(( colorhist_vector chv ));


   /* Color hash table stuff. */

   typedef colorhist_list* colorhash_table;

   extern colorhash_table 
   ppm_computecolorhash ARGS(( pixel** pixels, int cols, int rows, int maxcolors, int* colorsP ));

   extern int ppm_lookupcolor ARGS(( colorhash_table cht, pixel* colorP ));

   extern colorhist_vector ppm_colorhashtocolorhist ARGS(( colorhash_table cht, int maxcolors ));

    extern colorhash_table ppm_colorhisttocolorhash ARGS(( colorhist_vector chv, int colors ));

    extern int ppm_addtocolorhash ARGS(( colorhash_table cht, pixel* colorP, int value ));
/* Returns -1 on failure. */

    extern colorhash_table ppm_alloccolorhash ARGS(( void ));

    extern void ppm_freecolorhash ARGS(( colorhash_table cht ));

    extern void printhist(colorhist_vector chv, unsigned int colors);

    extern colorhist_vector find_colorhist(const Image *srcImage, unsigned int *colors);

#endif /* CVIPCMAP_DEFINED */
