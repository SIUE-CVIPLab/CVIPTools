/***************************************************************************
* ======================================================================
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* ======================================================================
*
*             File Name: m_file.h
*           Description: 
*         Related Files: 
*   Initial Coding Date: Mon Sep 20 20:49:36 CDT 1993
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
** $Log: m_file.h,v $
** Revision 1.1  1994/10/30 22:43:06  hanceg
** Initial revision
**
*
****************************************************************************/
#if !defined( M_FILE_DEFINED )

	#define M_FILE_DEFINED

	#define MAXROWS 32768U
	#define MAXELEMENTS 33554432U

	#if !defined( NO_STD_INCLUDES )
	#include <rpc/rpc.h>

	extern bool_t xdr_matrix(XDR *xdrs, Matrix *mP);
	extern int read_Matrix(Matrix *matP, const char *name);
	extern int write_Matrix(Matrix *matP, const char *name);
	#endif

#endif /* M_FILE_DEFINED */
