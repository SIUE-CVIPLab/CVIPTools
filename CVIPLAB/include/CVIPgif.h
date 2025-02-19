/***************************************************************************
======================================================================
Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
======================================================================
                                                                      
             File Name: CVIPgif.h
           Description: include file containing prototypes as well as
			a few type declarations for libcolor.a functions.
         Related Files: cviptogif.c, giftocvip.c, Makefile
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
$Date: 1997/04/15 00:00:44 $                                                        
$Source: /opt/cvipapps/CVIPtools3.5/include/RCS/CVIPgif.h,v $                                                         
$Header: /opt/cvipapps/CVIPtools3.5/include/RCS/CVIPgif.h,v 1.3 1997/04/15 00:00:44 yawei Exp $

*****************************************************************************/
#ifndef CVIPGIF_H
#define CVIPGIF_H

#ifdef __cplusplus
extern "C"{
#endif 

extern Image *giftocvip(char *, FILE *, int, int);
extern void cviptogif(Image *, char *, FILE *, int, int);
#ifdef __cplusplus
}
#endif 

#endif

