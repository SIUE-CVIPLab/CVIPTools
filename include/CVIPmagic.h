/***************************************************************************
* ======================================================================
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* ======================================================================
*
*             File Name: CVIPmagic.h
*           Description: Contains "Magic" numbers that correspond to
*                        different image file formats such as...
*                        CCC, EPS, GIF, ITEX, RAS and TIFF
*         Related Files: libconverter.a, convert.c
*   Initial Coding Date: Tue Apr  6 21:44:24 CDT 1993
*           Portability: Standard (ANSI) C
*             Credit(s): Gregory Hance
*                        Southern Illinois University @ Edwardsville
*
** Copyright (C) 1993 SIUE - by Gregory Hance.
**
** Permission to use, copy, modify, and distribute this software and its
** documentation for any purpose and without fee is hereby granted, provided
** that the above copyright notice appear in all copies and that both that
** copyright notice and this permission notice appear in supporting
** documentation.  This software is provided "as is" without express or
** implied warranty.
**
* RCS (Revision Control System) Information
* ...Added automatically by RCS 
*
* $Log: CVIPmagic.h,v $
* Revision 1.3  1997/04/15 00:07:34  yawei
* added if-def
*
* Revision 1.2  1996/06/11 12:14:09  kluo
* check in
*
 * Revision 1.1  1994/10/30  22:43:06  hanceg
 * Initial revision
 *
 * Revision 1.1  1993/05/31  07:10:20  hanceg
 * Initial revision
 *
*
****************************************************************************/
#ifndef CVIPMAGIC_H
#define CVIPMAGIC_H
#define CCCMAGIC 0

#define GIF_MAGIC1 'G'
#define GIF_MAGIC2 'I'
#define GIF_MAGIC3 'F'
#define GIFMAGIC ((GIF_MAGIC1<<16)|(GIF_MAGIC2<<8)|GIF_MAGIC3)

#define ITEX_MAGIC1 'I' 
#define ITEX_MAGIC2 'M'
#define ITEXMAGIC (((ITEX_MAGIC1)<<8)|ITEX_MAGIC2)

#define CVIP_MAGIC1 'V'
#define CVIP_MAGIC2 'i'
#define CVIP_MAGIC3 'P'
#define CVIPMAGIC ((CVIP_MAGIC1<<16)|(CVIP_MAGIC2<<8)|CVIP_MAGIC3)

#define RASMAGIC       0x59a66a95

#define	TIFF_BIGENDIAN		0x4d4d
#define	TIFF_LITTLEENDIAN	0x4949

#define EPS_MAGIC1 '%'
#define EPS_MAGIC2 '!'
#define EPSMAGIC (((EPS_MAGIC1)<<8)|EPS_MAGIC2)

#endif
