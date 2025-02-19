/***************************************************************************
* ======================================================================
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* ======================================================================
*
*             File Name: CVIPmem.h
*           Description: contains declarations for function prototypes
*			 in mem_alloc.c along with the new type name DATAFORM.
*         Related Files: mem_alloc.c
*   Initial Coding Date: Sun Apr 11 20:57:22 CDT 1993
*           Portability: Standard (ANSI) C
*             Credit(s): Gregory Hance
*                        Southern Illinois University @ Edwardsville
*
** Copyright (C) 1993 SIUE - by Gregory Hance and Dr. Scott Umbaugh.
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
* $Log: CVIPalloc.h,v $
 * Revision 1.1  1994/10/30  22:43:06  hanceg
 * Initial revision
 *
 * Revision 1.1  1993/05/03  05:53:14  hanceg
 * Initial revision
 *
*
*
****************************************************************************/
#if !defined( CVIPALLOC_DEFINED )

   #define CVIPALLOC_DEFINED

   typedef enum { MATRIXFORM, BANVECFORM, PIXVECFORM } DATAFORM;

   extern void *matalloc( unsigned int depth, unsigned int rows, unsigned int cols, size_t size );

   extern void *vecalloc( unsigned int no_of_vecs, unsigned int vdim, size_t size  );

   extern void vecfree(void *vecP, unsigned int no_of_vecs);

   extern void matfree(void *matP, unsigned int no_of_planes);

#endif
