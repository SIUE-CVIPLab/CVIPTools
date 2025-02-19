/***************************************************************************
* ======================================================================
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* ======================================================================
*
*             File Name: file.h
*           Description: 
*         Related Files: 
*   Initial Coding Date: Fri Sep 17 16:21:56 CDT 1993
*           Portability: Standard (ANSI) C
*            References:
*             Author(s): Gregory Hance
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
** $Log: CVIPfile.h,v $
 * Revision 1.4  1997/03/08  00:45:59  yawei
 * Name Changes:
 * 	BOOLEAN ==> CVIP_BOOLEAN
 * 	FALSE ==> CVIP_YES
 * 	TRUE ==> CVIP_NO
 * 	BYTE ==> CVIP_BYTE
 * 	SHORT ==> CVIP_SHORT
 * 	INTEGER ==> CVIP_INTEGER
 * 	FLOAT ==> CVIP_FLOAT
 * 	DOUBLE ==> CVIP_DOUBLE
 * 	TYPE ==> CVIP_TYPE
 *
** Revision 1.3  1997/03/07 04:18:06  yawei
** removed the file.h related stuff, not necessary
**
** Revision 1.2  1997/03/07 03:46:37  yawei
** combined contents from file.h
**
** Revision 1.1  1994/10/30 22:43:06  hanceg
** Initial revision
**
*
****************************************************************************/
#if !defined( FILE_DEFINED )

	#define FILE_DEFINED

	#include "ctype.h"

	extern FILE *openRead_CVIP(const char *name);
	extern FILE *openWrite_CVIP(const char *name, CVIP_BOOLEAN nice);
	extern void close_CVIP(FILE* f);
	extern int fSkipLines_CVIP(FILE *fileP, unsigned no_of_lines);
	extern int fGetLine_CVIP(FILE *fileP, char *strP);
	extern int fGetString_CVIP(FILE *fileP, char *strP, int field_no, const char *sep);
	extern int strToken_CVIP(const char *strP, const char *setP, char **tokP, int no_of_tokens);
	extern double fGetFloat_CVIP(FILE *fileP, int *status, int field_no, const char *sep);
	extern long fGetInt_CVIP(FILE *fileP, int *status, int field_no, const char *sep);
	extern double strGetFloat_CVIP(const char *strP, int *status, int field_no, const char *sep);
	extern long strGetInt_CVIP(const char *strP, int *status, int field_no, const char *sep);
	extern int getPathFileName(const char *strP, char *pnP, char *fnP);
	extern char **seperateStrings_CVIP(const char *strP, int c, int *n);

#endif /* FILE_DEFINED */

