/***************************************************************************
======================================================================
Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
======================================================================
                                                                      
             File Name: CVIPbin.h
           Description: include file containing prototypes as well as
			a few type declarations for libcolor.a functions.
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
$Date: 1997/04/15 00:06:47 $                                                        
$Source: /home/cvip/cvipapps/CVIPtools3.6/include/RCS/CVIPbin.h,v $                                                         
$Header: /home/cvip/cvipapps/CVIPtools3.6/include/RCS/CVIPbin.h,v 1.4 1997/04/15 00:06:47 yawei Exp $

*****************************************************************************/
#ifndef CVIPBIN_H
#define CVIPBIN_H
typedef enum { ORD_RGB, ORD_RBG, ORD_GRB, ORD_GBR, ORD_BRG, ORD_BGR } COLOR_ORDER;
typedef enum {INTERPLANE, INTERLINE, INTERPIXEL} INTERLEAVE_SCHEME;

#ifdef __cplusplus
extern "C"{
#endif 
Image *bintocvip(char *, FILE *, int, COLOR_ORDER, INTERLEAVE_SCHEME, int, int, CVIP_BOOLEAN);
void cviptobin(Image *, char *, FILE *, COLOR_ORDER, INTERLEAVE_SCHEME, CVIP_BOOLEAN);
#ifdef __cplusplus
}
#endif 

#define SIZES    245760,      512,      480,   \
                 262144,      512,      512,   \
		  65536,      256,      256,   \
		  16384,      128,      128,   \
		   4096,       64,       64,   \
		 220020,      570,      386,   \
		 196608,      256,      768 

#endif
