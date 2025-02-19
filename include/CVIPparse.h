/***************************************************************************
* ======================================================================
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* ======================================================================
*
*             File Name: CVIPparse.h
*           Description: includes all prototypes for external functions defined
*                        in libcli.a
*         Related Files: libpbm1.c, errormsg.c, getvalue.c as well as the
*                        include files mentioned below.
*   Initial Coding Date: Sun Apr 11 14:23:48 CDT 1993
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
* $Log: CVIPparse.h,v $
 * Revision 1.1  1994/10/30  22:43:06  hanceg
 * Initial revision
 *
 * Revision 1.1  1993/05/03  22:37:22  hanceg
 * Initial revision
 *
*
****************************************************************************/
#if !defined(CVIPPARSE_DEFINED)
  
   #define CVIPPARSE_DEFINED

 
   /* include prototypes for many of the common ANSI C library facilities */
   #if !defined( NO_STD_INCLUDES )
      #include <stdio.h>
      #include <stdlib.h>
      #include <math.h>
      #include <string.h>
   #endif

   #include "CVIPtyp.h"

   #include "CVIPerror.h"
   #include "CVIPget.h"
   #include "CVIPstring.h"
   #include "CVIPfile.h"

  /*
   * memory allocation stuff
   */

   extern void *allocMatrix3D_CVIP(unsigned int depth, unsigned int rows, unsigned int cols, size_t size);
   extern void *allocMatrix_CVIP(unsigned int rows, unsigned int cols, size_t size);
   extern void freeMatrix_CVIP(void *matP);
   extern void freeMatrix3D_CVIP(void *matP);

#endif
