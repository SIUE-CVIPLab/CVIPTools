/***************************************************************************
* ======================================================================
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* ======================================================================
*
*             File Name: subSample.h
*           Description: function header file
*         Related Files: subSample.c
*   Initial Coding Date: Thu Sep 23 20:29:08 CDT 1993
*           Portability: Standard (ANSI) C
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
** $Log: subSample.h,v $
** Revision 1.2  1997/03/08 00:50:38  yawei
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
** Revision 1.1  1994/10/30 22:43:06  hanceg
** Initial revision
**
*
****************************************************************************/
#if !defined ( SUBSAMPLE_DEFINED )

	#define SUBSAMPLE_DEFINED

	extern void *subSample_Vector(void *vecP, unsigned dim, CVIP_TYPE data_type,
unsigned skip, unsigned *new_dim);


#endif /* SUBSAMPLE_DEFINED */
