/*************************************************************************** ======================================================================
Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
======================================================================
                                                                      
             File Name: CVIPccc.h
           Description: include file containing prototypes as well as
			a define for libcolor.a functions.
         Related Files: cviptoccc.c, ccctocvip.c, Makefile
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
$Date: 1997/04/15 00:04:10 $                                                        
$Source: /opt/cvipapps/CVIPtools3.5/include/RCS/CVIPccc.h,v $                                                         
$Header: /opt/cvipapps/CVIPtools3.5/include/RCS/CVIPccc.h,v 1.3 1997/04/15 00:04:10 yawei Exp $

*****************************************************************************/
#ifndef CVIPCCC_H
#define CVIPCCC_H
#define  MAXCOLORS 254		/* use 245 for xwindows version */
#ifdef __cplusplus
extern "C"{
#endif 

extern Image *ccctocvip(char *, FILE *, int);
extern void cviptoccc(Image *, char *, FILE *, int, int, int);

#ifdef __cplusplus
}
#endif 

#endif
