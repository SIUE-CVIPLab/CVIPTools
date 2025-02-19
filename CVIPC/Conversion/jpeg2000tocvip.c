/***************************************************************************
* **********************************************************************
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* **********************************************************************
*
*             File Name: jpeg2000tocvip.c
*           Description: jpeg2000 conversion driver
*         Related Files: jp2_decode.c
*           Portability: Standard (ANSI) C
*             Author(s): Serkan Kefel
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
****************************************************************************/

#include "CVIPcompress.h"
#include "CVIPtyp.h"
#include "CVIPimage.h"
#include "CVIPjpeg2000.h"

#include "openjpeg.h"
#include "dirent.h"
#include "getopt.h"

Image *jp2tocvip(char *filename)
{
	return jp2_decoder(filename);
}