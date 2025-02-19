/***************************************************************************
* ======================================================================
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* ======================================================================
*
*             File Name: pct.h
*           Description: contains function prototypes for functions related
*			 to the principal components transform.
*         Related Files: pct.c
*   Initial Coding Date: Sun May 30 14:27:42 CDT 1993
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
** $Log: m_CovEig.h,v $
** Revision 1.2  1997/03/26 03:42:11  yawei
** BOOLEAN ==> CVIP_BOOLEAN
**
** Revision 1.1  1994/10/30 22:43:06  hanceg
** Initial revision
**
 * Revision 1.1  1993/05/31  03:23:39  hanceg
 * Initial revision
 *
*
****************************************************************************/
#if !defined(EIG_DEFINED)

   #define EIG_DEFINED

   #define covariance(a,b,c) covariance_Matrix(a,b,c)
   #define eigensystem(a) eigenSystem_Matrix(a)

   extern Matrix *covariance_Matrix(float **bvecP, unsigned int no_of_bands,
	unsigned int vdim, CVIP_BOOLEAN is_mask, float mask_val);
   extern Matrix *eigenSystem_Matrix(Matrix *a_MATRIX);

#endif 
