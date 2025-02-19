/***************************************************************************
* ======================================================================
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* ======================================================================
*
*             File Name: errormsg.c
*           Description: contains routines for handling error messages
*                        and other forms of verbose output in CVIPtools
*         Related Files: libcli.c, CVIPerror.h
*   Initial Coding Date: Fri Apr  9 15:43:42 CDT 1993
*           Portability: Standard (ANSI) C
*             Credit(s): Gregory Hance
*                        Southern Illinois University @ Edwardsville
*
*  Global Function List: init_CVIP - parse global command line arguments
*			 quite_CVIP - turn off messages
*			 verbose_CVIP - turn on messages
*			 usage_CVIP - print program usage
*			 msg_CVIP - print informational message
*			 error_CVIP - print error message
*			 perror_CVIP - print system error message
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
* $Log: errormsg.c,v $
* Revision 1.2  1997/01/16 21:23:38  yawei
* updated changes
*
 * Revision 1.1  1993/05/03  22:37:20  hanceg
 * Initial revision
 *
*
****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <errno.h>
#include "CVIPerror.h"

#define CVIP_VERSION "1.1"

#define ERRWARN "error"

/* Initialization of global variables. */
static int showmessages = 1;


/****************************************************************
                   Name: init_CVIP
          Expanded Name: CVIPtools Initialize
             Parameters: <argcP> - pointer to the number of command line
			           arguments
			 <argv> - array of pointers to the command line
			 	  arguments
                Returns: nada
            Description: searches for global command line arguments such as --
			 "-quit" - do not print messages issued w/ msg_CVIP(...)
			 "-version" - print current version of CVIPtools and
			 then exit program.
	    Diagnostics: none.
              Credit(s): Gregory Hance
		         Southern Illinois University @ Edwardsville
****************************************************************/

void init_CVIP( int *argcP, char *argv[] )
    {
    int argn, i;
    const char *progname;

    /* Extract program name. */
    progname = strrchr( argv[0], '/');
    if ( progname == NULL )
	progname = argv[0];
    else
	++progname;

    /* Check for any global args. */
    for ( argn = 1; argn < *argcP; ++argn )
	{
	if ( !strcmp( argv[argn], "-quiet") )
	    {
	    showmessages = 0;
	    }
	else if ( !strcmp( argv[argn], "-version") )
	    {
	    msg_CVIP( progname, "Version of %s", CVIP_VERSION );
#ifdef BSD
	    msg_CVIP( progname, "BSD defined" );
#endif /*BSD*/
#ifdef SYSV
	    msg_CVIP( progname, "SYSV defined" );
#endif /*SYSV*/
#ifdef DEBUG
	    msg_CVIP( progname, "DEBUG defined" );
#endif /*DEBUG*/
	    exit( 0 );
	    }
	else
	    continue;
	for ( i = argn + 1; i <= *argcP; ++i )
	    argv[i - 1] = argv[i];
	--(*argcP);
	}
    }


/****************************************************************
                   Name: quite_CVIP
          Expanded Name: CVIPtools Quite
             Parameters: (void)
                Returns: nada
            Description: turns off messages displayed by msg_CVIP(...)
	    Diagnostics: none
              Credit(s): Gregory Hance
		         Southern Illinois University @ Edwardsville
****************************************************************/

void quite_CVIP(void)
{
   showmessages = 0;
}


/****************************************************************
                   Name: quite_CVIP
          Expanded Name: CVIPtools Verbose
             Parameters: (void)
                Returns: nada
            Description: turns on messages displayed by msg_CVIP(...)
	    Diagnostics: none
              Credit(s): Gregory Hance
		         Southern Illinois University @ Edwardsville
****************************************************************/

void verbose_CVIP(void)
{
   showmessages = 1;
}

/* Error handling. */

/****************************************************************
                   Name: usage_CVIP
          Expanded Name: CVIPtools Usage
             Parameters: <fn> - pointer to character string containing the
			 name of the program
			 <usage> - pointer to character string containing a
			 usage message for the current program.
                Returns: nada
            Description: prints a usage message out to stderr and then
			 exits the program
	    Diagnostics: none
              Credit(s): Gregory Hance
		         Southern Illinois University @ Edwardsville
****************************************************************/

void usage_CVIP( const char *fn, const char *usage )
    {
    fprintf( stderr, "usage:  %s %s\n", fn, usage );
    exit( 1 );
    }


/****************************************************************
                   Name: perror_CVIP
          Expanded Name: CVIPtools perror
             Parameters: <fn> - pointer to character string containing the
			 name of the program
			 <usage> - pointer to character string containing a
			 message about the reason of the error.
                Returns: nada
            Description: print a system error to stderr
	    Diagnostics: none
              Credit(s): Gregory Hance
		         Southern Illinois University @ Edwardsville
****************************************************************/

void perror_CVIP( const char *fn, const char *reason )
    {
    extern int errno;
    char* e;

    e = strerror(errno);

    if ( reason != 0 && reason[0] != '\0' )
	error_CVIP( fn, "%s - %s", reason, e );
    else
	error_CVIP( fn, "%s", e );
    }


/****************************************************************
                   Name: msg_CVIP
          Expanded Name: cvip message
             Parameters: <fn> - pointer to character string containing the
			 name of the program/function
			 <format> - pointer to a format control string in the
			 form of printf(...) (e.g. "x = %d").
			 <...> - list of variables, seperated by commas, to be
			 used by the format control string. (e.g.) -
			 error_CVIP("myfunc", "x = %d", 3) => "myfunc: x = 3"
                Returns: nada
            Description: print an informational message.
	    Diagnostics: none
              Credit(s): Gregory Hance
		         Southern Illinois University @ Edwardsville
****************************************************************/

void msg_CVIP( const char *fn, const char* format, ... )
    {
    va_list args;

    va_start( args, format );

    if ( showmessages )
	{
	fprintf( stderr, "%s: ", fn );
	(void) vfprintf( stderr, format, args );
	}
    va_end( args );
    }


void 
print_CVIP( 
	const char* format, 
	... 
)
{
    	va_list args;

    	va_start( args, format );

    	if ( showmessages )
		(void) vfprintf( stderr, format, args );

    	va_end( args );
}



/****************************************************************
                   Name: error_CVIP
          Expanded Name: cvip error
             Parameters: <fn> - pointer to character string containing the
			 name of the program/function
			 <format> - pointer to a format control string in the
			 form of printf(...) (e.g. "x != %d").
			 <...> - list of variables, seperated by commas, to be
			 used by the format control string.
                Returns: nada
            Description: print an error message prefixed by a standard
			 CVIPtools error tag. (e.g.) - error_CVIP("myfunc",
			 "x != %d", 3) => "<myfunc-error>: x != 3\n"
	    Diagnostics: none
              Credit(s): Gregory Hance
		         Southern Illinois University @ Edwardsville
****************************************************************/

void error_CVIP( const char* fn, const char* format, ... )
    {
    va_list args;

    va_start( args, format );

    fprintf( stderr, "<%s-%s>: ", fn , ERRWARN);
    (void) vfprintf( stderr, format, args );
    fputc( '\n', stderr );
    va_end( args );
    }

