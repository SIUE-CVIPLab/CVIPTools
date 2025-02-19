/***************************************************************************
* ======================================================================
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* ======================================================================
*
*             File Name: findNonSkin.h
*           Description: public (client) function declaration file
*         Related Files: findNonSkin.c
*   Initial Coding Date: Fri Sep 24 15:23:07 CDT 1993
*           Portability: Standard (ANSI) C
*            References: UMR dermvis group, wvs[,rhm][,rpm]@ee.umr.edu
*             Author(s): Gregory Hance
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
** $Log: findNonSkin.h,v $
 * Revision 1.1  1994/10/30  22:43:06  hanceg
 * Initial revision
 *
*
****************************************************************************/
#if !defined ( FINDNONSKIN_DEFINED )

	#define FINDNONSKIN_DEFINED

	extern Image *findNonSkin_DVis(Image *imageP);


#endif /* FINDNONSKIN_DEFINED */
