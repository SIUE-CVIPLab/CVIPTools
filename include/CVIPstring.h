/***************************************************************************
* ======================================================================
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* ======================================================================
*
*             File Name: CVIPstring.h
*           Description: contains function prototypes, type names, constants
*			 etc., related to string functions in -- libcli.a
*         Related Files: Imakefile, libpbm1.c
*   Initial Coding Date: Sun Apr 11 14:32:40 CDT 1993
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
* $Log: CVIPstring.h,v $
 * Revision 1.1  1994/10/30  22:43:06  hanceg
 * Initial revision
 *
 * Revision 1.1  1993/05/03  22:37:22  hanceg
 * Initial revision
 *
*
****************************************************************************/
#if !defined(CVIPSTRING_DEFINED)

   #define CVIPSTRING_DEFINED

   extern int pm_keymatch( char* str, char* keyword, int minchars );
   #define cvip_keymatch( str, keyword, minchars ) pm_keymatch( str, keyword, minchars )
   #define keyMatch_CVIP( str, keyword, minchars ) pm_keymatch( str, keyword, minchars )

#endif
