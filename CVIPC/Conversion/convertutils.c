/***************************************************************************
* ======================================================================
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* ======================================================================
*
*             File Name: convertutils.c
*           Description: contains utilities for standard I/O etc.
*			 NOTE: some of these routines overlap with those
*			 contained in libcli.a and should be changed.
*         Related Files: Imakefile, CVIPconutils.h
*   Initial Coding Date: Sun May 30 23:09:35 CDT 1993
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
** $Log: convertutils.c,v $
** Revision 1.7  1997/05/30 19:47:23  yawei
** undeclare err_list for LINUX
**
** Revision 1.6  1997/05/21 03:23:13  yawei
** added WIN32 fopen
**
** Revision 1.5  1997/05/19 00:33:42  yawei
** added errno.h
**
** Revision 1.4  1997/03/08 17:01:00  yawei
** Swaped CVIP_YES and CVIP_NO
**
** Revision 1.3  1997/03/08 00:43:52  yawei
** Name Changes:
** 	BOOLEAN ==> CVIP_BOOLEAN
** 	FALSE ==> CVIP_YES
** 	TRUE ==> CVIP_NO
** 	BYTE ==> CVIP_BYTE
** 	SHORT ==> CVIP_SHORT
** 	INTEGER ==> CVIP_INTEGER
** 	FLOAT ==> CVIP_FLOAT
** 	DOUBLE ==> CVIP_DOUBLE
** 	TYPE ==> CVIP_TYPE
**
** Revision 1.2  1997/03/07 23:55:09  yawei
** Prepared for changes
**
 * Revision 1.1  1993/05/31  07:10:10  hanceg
 * Initial revision
 *
*
****************************************************************************/
#include <stdio.h>
#include <errno.h>
#if __STDC__
#include <stdarg.h>
#else /*__STDC__*/
#include <varargs.h>
#endif /*__STDC__*/

typedef enum {CVIP_NO, CVIP_YES} CVIP_BOOLEAN;

/* Initialization. */

static char* progname;
static int verbose;

void CVIPinit(function_name, showmessages)
char *function_name;
int showmessages;
{
   progname = function_name;
   verbose = (showmessages) ? CVIP_YES : CVIP_NO;
}

#if __STDC__
void CVIPerror( char* format, ... )
{
   va_list args;

   va_start( args, format );
#else /*__STDC__*/
/*VARARGS1*/
void CVIPerror( va_alist )
va_dcl
{ 
   va_list args;
   char* format;

   va_start( args );
   format = va_arg( args, char* );
#endif /*__STDC__*/

   fprintf( stderr, "CVIP ERROR/%s: ", progname );
   (void) vfprintf( stderr, format, args );
   fputc( '\n', stderr );
   va_end( args );
}


void CVIPsyserror( reason )
char* reason;
{
#if ! (defined(i386BSD) || defined(linux))
   extern const char* sys_errlist[];
#endif
   char* e;

   e = (char *)sys_errlist[errno];

   if ( reason != 0 && reason[0] != '\0' )
      CVIPerror( "%s - %s", reason, e );
   else
      CVIPerror( "%s", e );
}

#if __STDC__
void CVIPmessage( char* format, ... )
{
   va_list args;

   va_start( args, format );
#else /*__STDC__*/
/*VARARGS1*/
void CVIPmessage( va_alist )
va_dcl
{ 
   va_list args;
   char* format;

   va_start( args );
   format = va_arg( args, char* );
#endif /*__STDC__*/

   if ( verbose ) {
      fprintf( stderr, "%s: ", progname );
      (void) vfprintf( stderr, format, args );
      fputc( '\n', stderr );
   }
   va_end( args );
}


/* 
Endian I/O.
*/

/* File open/close that handles "-" as stdin and checks errors. */

FILE *CVIPopenr( name )
char* name;
{
FILE* f;

if ( strcmp( name, "-" ) == 0 )
   f = stdin;
else {
	#ifndef WIN32
   f = fopen( name, "r" );
	#else
   f = fopen( name, "rb" );
	#endif
   if ( f == NULL ) {
      CVIPsyserror( name );
      return NULL;
   }
}
return f;
}

FILE* CVIPopenw( name )
char* name;
{
   FILE* f;

if ( strcmp( name, "-" ) == 0 )
   f = stdout;
else {
	#ifndef WIN32
   f = fopen( name, "w" );
	#else
   f = fopen( name, "wb" );
	#endif
   if ( f == NULL ) {
      CVIPsyserror( name );
      return NULL;
   }
}
return f;
}

void CVIPclose( f )
FILE* f;
{    
   fflush( f );
   if ( ferror( f ) )
      CVIPmessage( "a file read or write error occurred at some point" );
   if ( f != stdin )
      if ( fclose( f ) != 0 )
         CVIPsyserror( "fclose" );
}
