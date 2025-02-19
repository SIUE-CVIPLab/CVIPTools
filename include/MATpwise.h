/***************************************************************************
======================================================================
Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
======================================================================
                                                                      
             File Name: MATpwise.h
           Description: Include file containing a macro for piece-wise
			(element by element) matrix operations. Such as
			addition, subtraction, multiplication, etc..
         Related Files: Makefile, m_arith_bin.c
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

$Log: MATpwise.h,v $
 * Revision 1.1  1994/10/30  22:43:06  hanceg
 * Initial revision
 *
 * Revision 1.1  1993/05/04  02:31:02  hanceg
 * Initial revision
 *

*****************************************************************************/

/****************************************************************
                  Name: PWISE_MAT
         Expanded Name: Piece-Wise Matrix Operations
            Parameters: a - pointer to first MATRIX structure.
    			b - pointer to second MATRIX structure.
    			c  - pointer to result MATRIX structure.
    			rowsa - number of rows in matrix a
   			colsa - number of columns in matrix a
			opera - any legal C binary operator
    			typea - legal C type describing the type of a
    			typeb - legal C type describing the type of b
    			typec - legal C type describing the type of c

                Return: (Nil)
           Description: Macro for piece-wise add, subtract, multiply fncs.
             Credit(s): Greg Hance (made minor ANSI modifications)
			Digital Signal Processing Algorithms in C
			
****************************************************************/
#if !defined( MATPWISE_DEFINED )

#define MATPWISE_DEFINED

#define PWISE_MAT(a,b,c,rowsa,colsa,oper,typea,typeb,typec) {  \
                 const typea **_AMX = (const typea **)a->rptr; \
		 const typeb **_BMX = (const typeb **)b->rptr; \
		 typec **_CMX = (typec **)c->rptr; \
		 register const typea *_PTA;  \
		 register const typeb *_PTB; \
		 register typec *_PTC; \
                 register int _IX,_JX; \
		 for(_IX = 0 ; _IX < rowsa ; _IX++) { \
		    _PTC = _CMX[_IX]; \
		    _PTB = _BMX[_IX]; \
		    _PTA = _AMX[_IX]; \
		    for(_JX = 0 ; _JX < colsa ; _JX++) \
		          *_PTC++ = (*_PTA++) oper (*_PTB++); \
		 } \
	}


/****************************************************************
                  Name: PWISE_MULT
         Expanded Name: Multiply Matrices
            Parameters: a - pointer to first MATRIX structure.
    			b - pointer to second MATRIX structure.
    			c  - pointer to result MATRIX structure.
    			rowsa - number of rows in matrix a
   			colsa - number of columns in matrix a
    			typea - legal C type describing the type of a
    			typeb - legal C type describing the type of b
    			typec - legal C type describing the type of c

                Return: (Nil)
           Description: Macro for element by element matrix multiplication.
			...WILL handle complex matrices
             Credit(s): Greg Hance
			
****************************************************************/
#define PWISE_MULT(a,b,c,rowsa,colsa,typea,typeb,typec) {  \
                 typea **_AMXR = (typea **)a->rptr; \
		 typeb **_BMXR = (typeb **)b->rptr; \
		 typec **_CMXR = (typec **)c->rptr; \
                 typea **_AMXI = (typea **)a->iptr; \
		 typeb **_BMXI = (typeb **)b->iptr; \
		 typec **_CMXI = (typec **)c->iptr; \
		 register typea *_PTAR;  \
		 register typeb *_PTBR; \
		 register typec *_PTCR; \
		 register typea *_PTAI;  \
		 register typeb *_PTBI; \
		 register typec *_PTCI; \
                 register int _IX,_JX; \
		 for(_IX = 0 ; _IX < rowsa ; _IX++) { \
		    _PTCR = _CMXR[_IX]; \
		    _PTBR = _BMXR[_IX]; \
		    _PTAR = _AMXR[_IX]; \
		    if(a->data_format==COMPLEX) { \
		       _PTCI = _CMXI[_IX]; \
		       _PTBI = _BMXI[_IX]; \
		       _PTAI = _AMXI[_IX]; \
		    } \
		    for(_JX = 0 ; _JX < colsa ; _JX++) {\
		          if(a->data_format==REAL) \
		             *_PTCR++ = (*_PTAR++) * (*_PTBR++); \
			  else {\
			     CMUL(typec,*_PTCR,*_PTCI,*_PTAR,*_PTAI,*_PTBR,*_PTBI); \
			     _PTCR++;_PTCI++;_PTAR++;_PTAI++;_PTBR++;_PTBI++; \
			  } \
		    } \
		 } \
	}

#endif /* MATPWISE_DEFINED */
