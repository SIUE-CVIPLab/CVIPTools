/***************************************************************************
* ======================================================================
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* ======================================================================
*
*             File Name: CVIPerror.h
*           Description: This file contains standard routines for handling
*                        output messages in CVIPtools (diagnostic as well as
*                        regular informative messages.)
*         Related Files: libpbm1.a (pbmplus library), errormsg.c
*   Initial Coding Date: Fri Apr  9 11:03:01 CDT 1993
*           Portability: Standard (ANSI) C
*             Credit(s): Gregory Hance
*                        Southern Illinois University @ Edwardsville
*                        Jef Poskanzer - Many of these routines are highly
*                        correlated with those of "pbmplus" but are slightly
*                        modified in the sense that I wan't to use them in a
*                        larger program and can't have the program exiting
*                        just because an error popped up.... boiiinnnggg!
*
** Copyright (C) 1989 by Jef Poskanzer.
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
* $Log: CVIPerror.h,v $
* Revision 1.3  1997/05/30 19:30:45  yawei
* changed macro definition
*
* Revision 1.2  1997/05/09 15:35:06  yawei
* renamed quite_CVIP to quiet_CVIP
*
* Revision 1.1  1994/10/30 22:43:06  hanceg
* Initial revision
*
 * Revision 1.1  1993/05/03  22:37:21  hanceg
 * Initial revision
 *
*
****************************************************************************/

#if !defined(CVIPERROR_DEFINED)

   #define CVIPERROR_DEFINED

   #include <errno.h>

   /* message formatting and error handling definitions */

   #define cvip_msg msg_CVIP
   #define cvip_error error_CVIP
   #define cvip_perror(a,b) perror_CVIP(a,b)
   #define cvip_usage(a,b) usage_CVIP(a,b)
   #define cvip_quite()  quite_CVIP()
   #define quiet_CVIP()  quite_CVIP()
   #define cvip_verbose(a) verbose_CVIP(a)
   #define cvip_init(a,b) init_CVIP(a,b)


   extern void msg_CVIP( const char *fn, const char *msg, ... );
   extern void print_CVIP( const char* format, ... );
   extern void error_CVIP( const char *fn, const char *error, ... );
   extern void perror_CVIP( const char *fn, const char *reason );
   extern void usage_CVIP( const char *fn, const char *usage );
   extern void quite_CVIP(void);
   extern void verbose_CVIP(void);

   /* initialization routine for standalone modules
      with command line processing */

   extern void init_CVIP( int* argcP, char* argv[] );


#endif
