/***************************************************************************
======================================================================
Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
======================================================================
                                                                      
             File Name: CVIPeps.h
           Description: include file containing prototypes as well as
			a few type declarations for libcolor.a functions.
         Related Files: cviptoeps.c, epstocvip.c, Makefile
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
$Date: 1997/04/15 00:06:08 $                                                        
$Source: /opt/cvipapps/CVIPtools3.5/include/RCS/CVIPeps.h,v $                                                         
$Header: /opt/cvipapps/CVIPtools3.5/include/RCS/CVIPeps.h,v 1.5 1997/04/15 00:06:08 yawei Exp $

*****************************************************************************/
#ifndef CVIPEPS_H
#define CVIPEPS_H
#ifdef __cplusplus
extern "C"{
#endif 
Image *epstocvip(char *, FILE *, CVIP_BOOLEAN);
void cviptoeps(Image *, char *, FILE *, float, float, int, CVIP_BOOLEAN);
#ifdef __cplusplus
}
#endif 

#endif

