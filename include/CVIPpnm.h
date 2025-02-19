/***************************************************************************
======================================================================
Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
======================================================================
                                                                      
             File Name: CVIPpnm.h
           Description: include file containing prototypes
			for libcolor.a functions.
         Related Files: cviptopnm.c, pnmtocvip.c, Makefile
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
$Date: 1997/04/15 00:03:35 $                                                        
$Source: /opt/cvipapps/CVIPtools3.5/include/RCS/CVIPpnm.h,v $                                                         
$Header: /opt/cvipapps/CVIPtools3.5/include/RCS/CVIPpnm.h,v 1.3 1997/04/15 00:03:35 yawei Exp $

*****************************************************************************/
#ifndef CVIPPNM_H
#define CVIPPNM_H
#ifdef __cplusplus
extern "C"{
#endif 


extern Image *pnmtocvip(char *, FILE *, int, int);
extern void cviptopnm(Image *, char *, FILE *, int);
#ifdef __cplusplus
}
#endif 
#endif

