/***************************************************************************
======================================================================
Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
======================================================================
                                                                      
             File Name: CVIPtiff.h
           Description: include file containing prototypes as well as
			a few defines for libcolor.a functions.
         Related Files: cviptotiff.c, tifftocvip.c, Makefile
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
$Date: 1997/04/15 00:04:59 $                                                        
$Source: /opt/cvipapps/CVIPtools3.5/include/RCS/CVIPtiff.h,v $                                                         
$Header: /opt/cvipapps/CVIPtools3.5/include/RCS/CVIPtiff.h,v 1.3 1997/04/15 00:04:59 yawei Exp $

*****************************************************************************/

/* Available tiff compression schemes: COMPRESSION_NONE, COMPRESSION_PACKBITS,  
                                       COMPRESSION_LZW, COMPRESSION_CCITTFAX3, 
				       COMPRESSION_CCITTFAX4 

                 Available fillorders: FILLORDER_MSB2LSB, FILLORDER_LSB2MSB
		 
		  Available g3options: GROUP3OPT_2DENCODING, GROUP3OPT_FILLBITS
*/
#ifndef CVIPTIFF_H          
#define CVIPTIFF_H          
#include "tiff.h"  
#ifdef __cplusplus
extern "C"{
#endif 


#define DEFAULT 0

void cviptotiff( Image *, char *, unsigned short,  unsigned short, long, unsigned short, long, int);
Image *tifftocvip(char *,  int );
#ifdef __cplusplus
}
#endif 

#endif

