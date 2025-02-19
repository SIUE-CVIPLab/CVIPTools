/***************************************************************************
* ======================================================================
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* ======================================================================
*
*             File Name: luminance.c
*           Description: core toolbox module containing a routine for
*			 fast RGB to luminance calculation.
*         Related Files: CVIPluminance.h, Imakefile
*   Initial Coding Date: Sun May 30 23:13:09 CDT 1993
*           Portability: Standard (ANSI) C
*             Credit(s): Gregory Hance
*                        Southern Illinois University @ Edwardsville
*
** Copyright (C) 1993 SIUE - by Gregory Hance.
** Copyright (C) 1989, 1991 by Jef Poskanzer
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
** $Log: luminance.c,v $
** Revision 1.6  1997/03/08 17:06:11  yawei
** Swaped CVIP_YES and CVIP_NO
**
** Revision 1.5  1997/03/08 00:59:04  yawei
** Name Changes:
** 	BOOLEAN ==> CVIP_BOOLEAN
** 	FALSE ==> CVIP_YES
** 	TRUE ==> CVIP_NO
** 	BYTE ==> CVIP_BYTE
** 	SHORT ==> CVIP_SHORT
** 	INTEGER ==> CVIP_INTEGER
** 	FLOAT ==> CVIP_FLOAT
** 	DOUBLE ==> CVIP_DOUBLE
** 	TYPE ==> CVIP_TYPE
**
** Revision 1.4  1997/01/15 17:17:30  yawei
** Global Change:  IMAGE ==> Image
**
 * Revision 1.3  1996/02/28  19:42:46  akjoele
 * *** empty log message ***
 *
 * Revision 1.2  1996/02/28  19:33:38  akjoele
 * Fixed memory leak so that the passed image is freed when
 * an error condition occurrs.
 *
 * Revision 1.1  1995/10/16  22:28:38  akjoele
 * Initial revision
 *
 * Revision 1.1  1993/05/31  07:10:15  hanceg
 * Initial revision
 *
*
****************************************************************************/
#include <math.h>
#include <stdio.h>
#include "CVIPimage.h"
#include "CVIPluminance.h"


/****************************************************************
                   Name: CVIPluminance
          Expanded Name: CVIP luminance
             Parameters: <cvip_Image> pointer to Image structure.
			 <maxval> - should be set to a value less than 255.
			 Specifies the maximum range of the input image.
			 <retain_image> - CVIP_YES or CVIP_NO value indicating whether
			 the original Image structure should be freed or not.
			 <verbose> - CVIP_YES or CVIP_NO value indicating whether
			 the function should output standard messages.
                Returns: pointer to luminance transformed image.
            Description: Performs an  RGB to luminance transform according to
			 P = 0.299 r + 0.587 g + 0.114 b.
	    Diagnostics: none
              Credit(s): Jef Poskanzer - "PBMPLUS"
			 Arve Kjoelen, Gregory Hance
		         Southern Illinois University @ Edwardsville
****************************************************************/

Image *luminance_Image(Image *inIm) {
    register int cnt=0;
    int npix, rows, cols;
    char function_name[] = {"CVIPluminance"};
    Image *grIm;
    byte *brptr, *bgptr, *bbptr, *boptr;
    short *srptr, *sgptr, *sbptr, *soptr;
    int *irptr, *igptr, *ibptr, *ioptr;
    float *frptr, *fgptr, *fbptr, *foptr;
    double *drptr, *dgptr, *dbptr, *doptr;
    
    rows = inIm->image_ptr[0]->rows;
    cols = inIm->image_ptr[0]->cols;
    npix = rows*cols;
    
    if(inIm->bands!=3) {
       fprintf(stderr, "Error: Your input image must have three color bands\n");
       delete_Image(inIm);
       return(NULL);
    }

    grIm = (Image *) new_Image(PGM, GRAY_SCALE, 1, rows, cols, inIm->image_ptr[0]->data_type, inIm->image_ptr[0]->data_format);
    
    fprintf(stdout, "%s: performing RGB -> luminance transform.\n",function_name);

    switch(inIm->image_ptr[0]->data_type) {
       case CVIP_BYTE:
      	  brptr=(byte *)inIm->image_ptr[0]->rptr[0];
	  bgptr=(byte *)inIm->image_ptr[1]->rptr[0];
	  bbptr=(byte *)inIm->image_ptr[2]->rptr[0];
	  boptr=(byte *)grIm->image_ptr[0]->rptr[0];
	  while(cnt++<npix) {
	     *boptr=CVIP_LUMIN(*brptr, *bgptr, *bbptr);
	     boptr++; brptr++; bgptr++; bbptr++;
	  }
	  break;

       case CVIP_SHORT:
          srptr=(short *)inIm->image_ptr[0]->rptr[0];
          sgptr=(short *)inIm->image_ptr[1]->rptr[0];
          sbptr=(short *)inIm->image_ptr[2]->rptr[0];
          soptr=(short *)grIm->image_ptr[0]->rptr[0];
          while(cnt++<npix) {
             *soptr=CVIP_LUMIN(*srptr, *sgptr, *sbptr);
             soptr++; srptr++; sgptr++; sbptr++;
          }
          break;

       case CVIP_INTEGER:
          irptr=(int *)inIm->image_ptr[0]->rptr[0];
          igptr=(int *)inIm->image_ptr[1]->rptr[0];
          ibptr=(int *)inIm->image_ptr[2]->rptr[0];
          ioptr=(int *)grIm->image_ptr[0]->rptr[0];
          while(cnt++<npix) {
             *ioptr=CVIP_LUMIN(*irptr, *igptr, *ibptr);
             ioptr++; irptr++; igptr++; ibptr++;
          }
          break;

       case CVIP_FLOAT:
          frptr=(float *)inIm->image_ptr[0]->rptr[0];
          fgptr=(float *)inIm->image_ptr[1]->rptr[0];
          fbptr=(float *)inIm->image_ptr[2]->rptr[0];
          foptr=(float *)grIm->image_ptr[0]->rptr[0];
          while(cnt++<npix) {
             *foptr=(float)CVIP_LUMIN(*frptr, *fgptr, *fbptr);
             foptr++; frptr++; fgptr++; fbptr++;
          }
          break;

       case CVIP_DOUBLE:
          drptr=(double *)inIm->image_ptr[0]->rptr[0];
          dgptr=(double *)inIm->image_ptr[1]->rptr[0];
          dbptr=(double *)inIm->image_ptr[2]->rptr[0];
          doptr=(double *)grIm->image_ptr[0]->rptr[0];
          while(cnt++<npix) {
             *doptr=CVIP_LUMIN(*drptr, *dgptr, *dbptr);
             doptr++; drptr++; dgptr++; dbptr++;
          }
          break;

	} /* switch */
   delete_Image(inIm);
   return(grIm);
}
