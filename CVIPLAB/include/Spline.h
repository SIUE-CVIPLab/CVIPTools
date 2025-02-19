/***************************************************************************
* ======================================================================
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* ======================================================================
*
*             File Name: drawpoints.h
*           Description: 
*         Related Files: 
*   Initial Coding Date: Mon Jul 12 19:50:03 CDT 1993
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
** $Log: Spline.h,v $
 * Revision 1.1  1994/10/30  22:43:06  hanceg
 * Initial revision
 *
*
****************************************************************************/
#if !defined(SPLINE_DEFINED)

   #define SPLINE_DEFINED

   struct BorderPointsType {

	unsigned no_of_points;
	unsigned h_span; 	/* UMR data -- 512 */
	unsigned v_span;	/* UMR data -- 512 */
	unsigned *xP;
	unsigned *yP;

   };

   typedef struct BorderPointsType BorderPoints;

   extern void drawPnts_Border(Border imageP, unsigned number_of_points, unsigned *xP, unsigned *yP );

   extern void readPntFile_Border(const char *pnt_file, unsigned *no_of_points,
unsigned **xP, unsigned **yP);

   extern void drawSpline_Border( Border imageP, unsigned number_of_points, unsigned *xP, unsigned *yP );

#endif /* SPLINE_DEFINED */


