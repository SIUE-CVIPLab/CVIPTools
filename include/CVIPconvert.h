/***************************************************************************
======================================================================
Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
======================================================================
                                                                      
             File Name: CVIPconvert.h
           Description: include file containing prototypes for libconverter.a
			functions. These are the primary functions used
			for converting to and from the CVIP Image structure
			and external file formats.
         Related Files: convert.c, Makefile
   Initial Coding Date: 1/24/92
           Portability: Standard (ANSI) C
             Credit(s): Gregory Hance, E.E. Dept. SIUE
			
****************************************************************************

** Copyright (C) 1991, 1992, 1993 SIUE - by Scott Umbaugh, Greg Hance.
**
** Permission to use, copy, modify, and distribute this software and its
** documentation for any purpose and without fee is hereby granted, provided
** that the above copyright notice appear in all copies and that both that
** copyright notice and this permission notice appear in supporting
** documentation.  This software is provided "as is" without express or
** implied warranty.

RCS (Revision Control System) Information - Added automatically by RCS) 

$Author: yawei $                                                         
$Date: 1997/05/16 23:41:51 $                                                        
$Source: /opt/cvipapps/CVIPtools3.6/include/RCS/CVIPconvert.h,v $                                                         
$Header: /opt/cvipapps/CVIPtools3.6/include/RCS/CVIPconvert.h,v 1.8 1997/05/16 23:41:51 yawei Exp $

*****************************************************************************/
#if !defined( CVIPCONVERT_DEFINED )
    #define CVIPCONVERT_DEFINED

    #include <stdlib.h>
    #include <string.h>
    #include <stdio.h>
    #ifndef WIN32
    #include <io.h>
    #endif
    #include "CVIPimage.h"
    #include "CVIPbin.h"
    #include "CVIPccc.h"
    #include "CVIPcompress.h"
    #include "CVIPconutils.h"
    #include "CVIPeps.h"
    #include "CVIPgif.h"
    #include "CVIPhalftone.h"
    #include "CVIPiris.h"
    #include "CVIPitex.h"
    #include "CVIPluminance.h"
    #include "CVIPmagic.h"
    #include "CVIPpng.h"
    #include "CVIPpnm.h"
    #include "CVIPps.h"
    #include "CVIPras.h"
    #include "CVIPtiff.h"
    #include "CVIPvip.h"
    #include "gray_binary.h"
    #include "pnm.h"

    #define CVIPgetformat(a) getFormat_CVIP(a)
    #define CVIPwriteimage(a,b,c,d,e,f) write_Image(a,b,c,d,e,f)
    #define CVIPreadimage(a,b,c) read_Image(a,c)

    #ifdef __cplusplus
        extern "C"{
    #endif 

    extern IMAGE_FORMAT getFormat_CVIP(char *);
    extern int  write_Image(Image *, char *, CVIP_BOOLEAN, CVIP_BOOLEAN, IMAGE_FORMAT, CVIP_BOOLEAN);
    extern int  write_JPEG_Image(Image *, char *, CVIP_BOOLEAN, CVIP_BOOLEAN, IMAGE_FORMAT, CVIP_BOOLEAN, int);
    extern Image *read_Image(char *, int);
    extern char *new_ext(const char *src, const char *ext);

    #ifdef __cplusplus
        }
    #endif 
#endif

