/***************************************************************************
======================================================================
Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
======================================================================
                                                                      
             File Name: CVIPluminance.h
           Description: include file containing prototypes
			for libcolor.a functions.
         Related Files: CVIPluminance.c, Makefile
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
$Date: 1997/04/14 23:58:49 $                                                        
$Source: /opt/cvipapps/CVIPtools3.5/include/RCS/CVIPluminance.h,v $                                                         
$Header: /opt/cvipapps/CVIPtools3.5/include/RCS/CVIPluminance.h,v 1.5 1997/04/14 23:58:49 yawei Exp $

*****************************************************************************/
#ifndef CVIPLUMINANCE_H
#define CVIPLUMINANCE_H
#ifdef __cplusplus
extern "C"{
#endif 


#define CVIP_LUMIN(r,g,b) ( 0.299 * (r) + 0.587 * (g) + 0.114 * (b) )
extern Image *luminance_Image(Image *);
extern Image *lum_average(Image * input_Image);
#ifdef __cplusplus
}
#endif 
#endif
