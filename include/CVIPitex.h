/***************************************************************************
======================================================================
Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
======================================================================
                                                                      
             File Name: CVIPbin.h
           Description: include file containing prototypes
			for libcolor.a functions.
         Related Files: cviptoitex.c, itextocvip.c, Makefile
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
$Date: 1997/04/15 00:05:34 $                                                        
$Source: /opt/cvipapps/CVIPtools3.5/include/RCS/CVIPitex.h,v $                                                         
$Header: /opt/cvipapps/CVIPtools3.5/include/RCS/CVIPitex.h,v 1.4 1997/04/15 00:05:34 yawei Exp $

*****************************************************************************/

#ifndef CVIPITEX_H
#define CVIPITEX_H
#ifdef __cplusplus
extern "C"{
#endif 

extern Image *itextocvip(char *, FILE *, CVIP_BOOLEAN);
extern void cviptoitex(Image *, char *, FILE *, char *, CVIP_BOOLEAN);
#ifdef __cplusplus
}
#endif 

#endif

