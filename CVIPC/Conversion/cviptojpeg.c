/***************************************************************************
* **********************************************************************
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* **********************************************************************
*
*             File Name: cviptojpeg.c
*           Description: jpeg conversion driver
*         Related Files: jpeg.c
*   Initial Coding Date: Fri Jul 18 07:24:50 CDT 1997
*           Portability: Standard (ANSI) C
*            References:
*             Author(s): 
*                        Southern Illinois University @ Edwardsville
*
** Copyright (C) 1996 SIUE - by Scott Umbaugh and .
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
** $Log: cviptojpeg.c,v $
** Revision 1.1  1997/07/18 12:25:39  yawei
** Initial revision
**
*
****************************************************************************/
#include "CVIPjpeg.h"
#include "CVIPcompress.h"
#include "CVIPtyp.h"
#include "CVIPimage.h"


int cviptojpg(Image *cvipImage, char *filename, int quality, 
    CVIP_BOOLEAN grayscale, CVIP_BOOLEAN optimize, int smooth, 
    CVIP_BOOLEAN verbose, char *qtablesFile){

    return jpg_compress(cvipImage, filename, quality, grayscale, 
		optimize, smooth, verbose, qtablesFile);

}
