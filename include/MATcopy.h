/***************************************************************************
======================================================================
Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
======================================================================
                                                                      
             File Name: CVIPcopy.h
           Description: Include file for functions using the macro COPY_MAT.
         Related Files: Makefile, m_copy.c
   Initial Coding Date: 1/23/93
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
$Date: 1997/03/08 00:47:50 $                                                        
$Source: /opt/cvipapps/CVIPtools3.5/include/RCS/MATcopy.h,v $                                                         
$Header: /opt/cvipapps/CVIPtools3.5/include/RCS/MATcopy.h,v 1.2 1997/03/08 00:47:50 yawei Exp $

*****************************************************************************/
/****************************************************************
                  Name: COPY_MAT
         Expanded Name: Copy Matrix
            Parameters: a - pointer to MATRIX structure
                        b - pointer to MATRIX structure
                        rows - number of rows contained in each matrix
			cols - number of cols contained in each matrix
			typea - legal C type describing the type of a
			typeb - legal C type describing the type of b
                Return: (Nil)
           Description: Copies the contents of matrix a into matrix b.
			If a has a floating point type and b has an
			integer type the values will be rounded off
			as expressed by the macro ROUND.
             Credit(s): Greg Hance
			
			
****************************************************************/
#if !defined( MATCOPY_DEFINED )

#define MATCOPY_DEFINED

#ifndef CVIPDEF_DEFINED
#   include "CVIPdef.h"
#endif

#define COPY_MAT(a,b,rows,cols,typea,typeb) { \
                 const typea **_AMX = (const typea **)a->rptr; \
                 typeb **_BMX = (typeb **)b->rptr; \
		 register const typea *_PTA; \
		 register typeb *_PTB; \
		 register int _IX,_JX; \
		 for(_IX = 0 ; _IX < rows ; _IX++) { \
		    _PTB = _BMX[_IX]; \
		    _PTA = _AMX[_IX]; \
		    for(_JX = 0 ; _JX < cols ; _JX++) \
		       if(b->data_type<CVIP_FLOAT) { \
		          *_PTB++ = (typeb) ROUND(*_PTA); _PTA++; } \
		       else \
		          *_PTB++ = (typeb)(*_PTA++); \
		 } \
	}
#endif /* MATCOPY_DEFINED */
