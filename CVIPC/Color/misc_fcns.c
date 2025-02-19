/***************************************************************************
* ======================================================================
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* ======================================================================
*
*             File Name: misc_fcns.c
*           Description: pixel replication utiltiy
*         Related Files: misc_fcns.c, Imakefile
*   Initial Coding Date: Sun May 30 14:48:09 CDT 1993
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
** $Log: misc_fcns.c,v $
** Revision 1.4  1997/03/08 00:58:57  yawei
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
** Revision 1.3  1997/01/15 17:17:21  yawei
** Global Change:  IMAGE ==> Image
**
 * Revision 1.2  1997/01/15  16:33:59  yawei
 * updated changes
 *
 * Revision 1.1  1993/05/31  03:23:40  hanceg
 * Initial revision
 *
*
****************************************************************************/
#include "CVIPtoolkit.h"
#include "CVIPdef.h"
#include "CVIPcolor.h"


/****************************************************************
                   Name: repzoom
          Expanded Name: replication zoom
             Parameters: <srcImage> - pointer to Image structure
			 <factor> - integer value to replicate by
			 <retain> - should the original image be freed.
                Returns: pointer to pixel replicated image
            Description: enlarge an image by pixel replication
	    Diagnostics: none
              Credit(s): Gregory Hance
		         Southern Illinois University @ Edwardsville
****************************************************************/

 Image *repzoom(Image *srcImage, unsigned int factor, CVIP_BOOLEAN retain)
 {
   byte *srcP, *zoomP;
   Image *zoomImage;
   register int i=0, j, k, x, y;
   unsigned int bands, rows, cols;

   /* Simplify some variables */
   bands = srcImage->bands;
   rows = srcImage->bandP[0]->rows;
   cols = srcImage->bandP[0]->cols;
 
   zoomImage = image_allocate(srcImage->image_format, srcImage->color_space, 
   bands, rows*factor, cols*factor, CVIP_BYTE, srcImage->bandP[0]->data_format);


   for(; i < bands; i++)            
      for(y=0; y < rows; y++) {
         srcP = (byte *) srcImage->bandP[i]->rptr[y];
            for(x=0; x < cols; x++, srcP++)
               for(j=y*factor; j < y*factor + factor; j++) {   
                  zoomP = (byte *) zoomImage->bandP[i]->rptr[j] + factor*x;
	          for(k=x*factor; k < x*factor + factor; k++, zoomP++)
	             *zoomP = *srcP;
	       }
      }

   if(!retain)
      image_free(srcImage);

return zoomImage;  
}


