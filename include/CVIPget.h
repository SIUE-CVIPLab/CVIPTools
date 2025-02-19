/***************************************************************************
* ======================================================================
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* ======================================================================
*
*             File Name: CVIPget.h
*           Description: contains prototypes for functions in getvalue.c
*         Related Files: libcli.a, getvalue.c
*   Initial Coding Date: Sat Apr 10 18:30:34 CDT 1993
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
* $Log: CVIPget.h,v $
 * Revision 1.1  1994/10/30  22:43:06  hanceg
 * Initial revision
 *
 * Revision 1.1  1993/05/03  22:37:22  hanceg
 * Initial revision
 *
*
****************************************************************************/
#if !defined(CVIPGET_DEFINED)

   #define CVIPGET_DEFINED
   
   #define get_string(a) getString_CVIP(a)
   #define get_int(a,b,c) getInt_CVIP(a,b,c)
   #define get_uint(a,b,c) getUInt_CVIP(a,b,c)
   #define get_float(a,b) getFloat_CVIP(a,b)

   extern char *getString_CVIP(void);
   extern long getInt_CVIP(int base, long low_limit, long up_limit);
   extern unsigned long getUInt_CVIP(int base, unsigned long low_limit, unsigned long up_limit);
   extern double getFloat_CVIP(double low_limit, double up_limit);
   extern char *getEnv_CVIP(const char *name);

#endif

