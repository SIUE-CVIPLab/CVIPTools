/***************************************************************************
======================================================================
Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
======================================================================
                                                                      
             File Name: MATscale.h
           Description: Include file containing a macro for scaling
			a matrix by a coefficient as well as obtaining
			a submatrix from that matrix.
         Related Files: Makefile, m_crop.c, m_scale.c
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

$Author: hanceg $                                                         
$Date: 1994/10/30 22:43:06 $                                                        
$Source: /opt/cvipapps/CVIPtools3.5/include/RCS/MATscale.h,v $                                                         
$Header: /opt/cvipapps/CVIPtools3.5/include/RCS/MATscale.h,v 1.1 1994/10/30 22:43:06 hanceg Exp $

*****************************************************************************/

/****************************************************************
                  Name: SCALE_MAT
         Expanded Name: Scale a Mtrix
            Parameters: a - pointer to input MATRIX structure.
    			b - pointer to resultant MATRIX structure.
    			s - scale factor variable to be multiplied.
    			rows - number of rows in matrix b
    			cols - number of columns in matrix b
    			rowoff - number of rows to offset matrix b
    			coloff - number of columns to offset matrix b
    			typea - legal C type describing the type of a
    			typeb - legal C type describing the type of b
                Return: (Nada)
           Description: This macro will scale matrix b by some factor
			s and store the resultant matrix in a. The macro
			may also be used to operate on only a subarea of
			the original b.
             Credit(s): Greg Hance
			
****************************************************************/
#if !defined( MATSCALE_DEFINED )

#define MATSCALE_DEFINED

#define SCALE_MAT(a,b,s,rows,cols,rowoff,coloff,typea,typeb) { \
                 typea **_ARMX = (typea **)a->rptr; \
                 typeb **_BRMX = (typeb **)b->rptr; \
                 typea **_AIMX = (typea **)a->iptr; \
                 typeb **_BIMX = (typeb **)b->iptr; \
		 register typea *_PTAR; \
		 register typeb *_PTBR; \
		 register typea *_PTAI; \
		 register typeb *_PTBI; \
		 register int _IX,_JX; \
		 for(_IX = 0 ; _IX < rows ; _IX++) { \
		    _PTBR = _BRMX[_IX]; \
		    _PTAR = _ARMX[_IX + rowoff] + coloff; \
		    if(a->data_format==COMPLEX) { \
		       _PTBI = _BIMX[_IX]; \
		       _PTAI = _AIMX[_IX + rowoff] + coloff; \
		    } \
		    for(_JX = 0 ; _JX < cols ; _JX++) { \
		       *_PTBR++ = (typeb)(s * (*_PTAR++)); \
		       if(a->data_format==COMPLEX) \
		          *_PTBI++ = (typeb)(s * (*_PTAI++)); \
		    } \
		 } \
	}

#endif /* MATSCALE_DEFINED */
