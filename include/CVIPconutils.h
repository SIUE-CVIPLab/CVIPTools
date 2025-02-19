/***************************************************************************
======================================================================
Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
======================================================================
                                                                      
             File Name: CVIPconutils.h
           Description: include file containing several useful macros
			used in the conversion library as well as some
			prototypes of functions used locally as utilities
			in the conversion library but that never quite made
			it to the big time.
         Related Files: libconverter.a, Makefile
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
$Date: 1997/04/14 23:59:52 $                                                        
$Source: /opt/cvipapps/CVIPtools3.5/include/RCS/CVIPconutils.h,v $                                                         
$Header: /opt/cvipapps/CVIPtools3.5/include/RCS/CVIPconutils.h,v 1.4 1997/04/14 23:59:52 yawei Exp $

*****************************************************************************/
#ifndef CVIPCONUTILS_H
#define  CVIPCONUTILS_H
#include "CVIPimage.h"
#define	CVIPReadBytes(file,buffer,len)	(fread(buffer, 1, len, file) != 0)
#define CVIPWriteBytes(file,buffer,len) (fwrite(buffer, 1, len, file) != 0)
#define CVIP2BytetoShort(a,b)   (((b)<<8)|(a))
#define CVIPShortto2Byte(intval,byte1,byte2) (byte1=((intval)>>8));(byte2=((intval)&0xFF))       
#define ASCIIHEXtoDECIMAL(hex) ((((0xF0)&(hex)) == (0x30)) ? ((hex)-48) : (((0x0F)&(hex))+9))

extern void CVIPinit(char *, int);
extern void CVIPsyserror( char * );
extern void CVIPclose( FILE * );
extern FILE *CVIPopenr( char * );
extern FILE *CVIPopenw( char * );
extern void CVIPmessage( char* , ... );
extern void CVIPerror( char* , ... );
extern Image *safvrtocvip(char *, FILE *, int);
#endif
