/***************************************************************************
======================================================================
Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
======================================================================
                                                                      
             File Name: CVIPras.h
           Description: include file containing prototypes as well as
			a few defines for libcolor.a functions.
         Related Files: cviptobin.c, bintocvip.c, Makefile
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
$Date: 1997/04/15 00:01:51 $                                                        
$Source: /opt/cvipapps/CVIPtools3.5/include/RCS/CVIPras.h,v $                                                         
$Header: /opt/cvipapps/CVIPtools3.5/include/RCS/CVIPras.h,v 1.4 1997/04/15 00:01:51 yawei Exp $

*****************************************************************************/
#ifndef CVIPRAS_H
#define CVIPRAS_H
#define RT_STANDARD	1	/* Raw pixrect image in 68000 byte order */
#define RT_CVIP_BYTE_ENCODED	2	/* Run-length compression of bytes */
#ifdef __cplusplus
extern "C"{
#endif 


void cviptoras( Image * , char *, FILE *, int, int);
extern Image *rastocvip(char *, FILE *, int);
#ifdef __cplusplus
}
#endif 
#endif
