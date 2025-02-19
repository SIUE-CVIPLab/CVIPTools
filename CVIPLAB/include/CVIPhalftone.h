/***************************************************************************
======================================================================
Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
======================================================================
                                                                      
             File Name: CVIPhalftone.h
           Description: include file containing prototypes as well as
			a few defines for libcolor.a functions.
         Related Files: halftone.c, Makefile
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
$Date: 1997/04/15 14:52:58 $                                                        
$Source: /opt/cvipapps/CVIPtools3.5/include/RCS/CVIPhalftone.h,v $                                                         
$Header: /opt/cvipapps/CVIPtools3.5/include/RCS/CVIPhalftone.h,v 1.5 1997/04/15 14:52:58 yawei Exp $

*****************************************************************************/

#ifndef CVIPHALFTONE_H
#define CVIPHALFTONE_H
#ifdef __cplusplus
extern "C"{
#endif 

#define QT_FS 1
#define QT_THRESH 2
#define QT_DITHER8 3
#define QT_CLUSTER3 4
#define QT_CLUSTER4 5
#define QT_CLUSTER8 6

extern Image *CVIPhalftone(Image *, int, int, float,
	CVIP_BOOLEAN, CVIP_BOOLEAN);
#ifdef __cplusplus
}
#endif 
#endif

