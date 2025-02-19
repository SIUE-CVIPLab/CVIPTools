/***************************************************************************
======================================================================
Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
======================================================================
                                                                      
             File Name: MATmult.h
           Description: Include file containing a macro for matrix
			multiplication.
         Related Files: Makefile, m_mult.c
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

$Log: MATmult.h,v $
 * Revision 1.1  1994/10/30  22:43:06  hanceg
 * Initial revision
 *
 * Revision 1.1  1993/05/04  02:31:02  hanceg
 * Initial revision
 *

*****************************************************************************/
/****************************************************************
                  Name: MULT_MAT
         Expanded Name: Multiply Matrices
            Parameters: a - pointer to first MATRIX structure.
    			b - pointer to second MATRIX structure.
    			c  - pointer to result MATRIX structure.
    			rowsa - number of rows in matrix a
   			colsa - number of columns in matrix a
   			colsb - number of columns in matrix b
    			typea - legal C type describing the type of a
    			typeb - legal C type describing the type of b
    			typec - legal C type describing the type of c

                Return: (Nil)
           Description: Macro for matrix multiplication.
			...will handle complex matrices
             Credit(s): Greg Hance (added support for Complex matrices
			as well as some others)
			Digital Signal Processing Algorithms in C
			
****************************************************************/
#if !defined( MATMULT_DEFINED )

#define MATMULT_DEFINED

#define MULT_MAT(a,b,c,rowsa,colsa,colsb,typea,typeb,typec) {  \
                const typea **_AMXR = (const typea **)a->rptr; \
                 const typeb **_BMXR = (const typeb **)b->rptr; \
                const typea **_AMXI = (const typea **)a->iptr; \
                 const typeb **_BMXI = (const typeb **)b->iptr; \
		 typec **_CMXR = (typec **)c->rptr; \
		 typec **_CMXI = (typec **)c->iptr; \
		 register const typea *_PTAR,*_PTAI; \
		 register const typeb *_PTBR,*_PTBI; \
		 register typec *_PTCR,*_PTCI,_CR,_CI; \
		 register int _IX,_JX,_KX; \
		 for(_IX = 0 ; _IX < rowsa ; _IX++) { \
		    _PTCR = _CMXR[_IX]; \
		    _PTBR = _BMXR[0]; \
		    if(c->data_format==COMPLEX) { \
		       _PTCI = _CMXI[_IX]; \
		       _PTBI = _BMXI[0]; \
                    } \
		    for(_JX = 0 ; _JX < colsb ; _JX++) { \
		       _PTAR = _AMXR[_IX]; \
		       if(C->data_format == REAL) \
		          *_PTCR = (*_PTAR++) * (*_PTBR++); \
		       else {\
		          _PTAI = _AMXI[_IX]; \
		          CMUL(typec,*_PTCR,*_PTCI,*_PTAR,*_PTAI,*_PTBR,*_PTBI); \
			  _PTAR++;_PTBR++;_PTAI++;_PTBI++; \
		       } \
		       for(_KX = 1 ; _KX < colsa ; _KX++) { \
		          if(C->data_format == REAL) \
		             *_PTCR += (*_PTAR++)* _BMXR[_KX][_JX]; \
		          else {\
		             CMUL(typec,_CR,_CI,*_PTAR,*_PTAI,_BMXR[_KX][_JX],_BMXI[_KX][_JX]); \
			     *_PTCR += (_CR);*_PTCI += (_CI);_PTAR++;_PTAI++; \
		          } \
		       } \
		       _PTCR++;\
		       if(c->data_format==COMPLEX) _PTCI++; \
		     } \
		  } \
         }

#endif /*MATMULT_DEFINED */
