/***************************************************************************
======================================================================
Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
======================================================================
                                                                      
             File Name: CVIPband.h
           Description: function protoypes for functions in libband.a
         Related Files: Makefile, libband.a
   Initial Coding Date: 1/24/92
           Portability: Standard (ANSI) C
             Credit(s): Gregory Hance, E.E. Dept. SIUE
			
****************************************************************************

** Copyright (C) 1992, 1993 SIUE - by Scott Umbaugh, Greg Hance.
**
** Permission to use, copy, modify, and distribute this software and its
** documentation for any purpose and without fee is hereby granted, provided
** that the above copyright notice appear in all copies and that both that
** copyright notice and this permission notice appear in supporting
** documentation.  This software is provided "as is" without express or
** implied warranty.

RCS (Revision Control System) Information - Added automatically by RCS) 

$Log: CVIPband.h,v $
 * Revision 1.4  1997/03/08  00:45:17  yawei
 * Name Changes:
 * 	BOOLEAN ==> CVIP_BOOLEAN
 * 	FALSE ==> CVIP_YES
 * 	TRUE ==> CVIP_NO
 * 	BYTE ==> CVIP_BYTE
 * 	SHORT ==> CVIP_SHORT
 * 	INTEGER ==> CVIP_INTEGER
 * 	FLOAT ==> CVIP_FLOAT
 * 	DOUBLE ==> CVIP_DOUBLE
 * 	TYPE ==> CVIP_TYPE
 *
Revision 1.3  1996/08/09 17:49:19  akjoele
ajf

 * Revision 1.2  1996/08/09  15:49:20  akjoele
 * Added prototype for extract_band()
 *
 * Revision 1.1  1994/10/30  22:43:06  hanceg
 * Initial revision
 *
 * Revision 1.1  1993/05/03  05:53:15  hanceg
 * Initial revision
 *
 *                                                         

*****************************************************************************/
#if !defined( CVIPBAND_DEFINED )

   #define CVIPBAND_DEFINED

   #include "CVIPmatrix.h"
   #include "CVIPalloc.h"

   extern MATRIX **bandcast(MATRIX **, int, CVIP_TYPE);
   extern void bandcopy(MATRIX **, MATRIX **, int);
   extern void *band_minmax(MATRIX *const *bands, unsigned int no_of_bands, CVIP_TYPE data_type, int bstart, int bstop);
   
#endif
