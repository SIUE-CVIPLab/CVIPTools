/***************************************************************************
======================================================================
Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
======================================================================
                                                                      
             File Name: CVIPcomplex.h
           Description: Contains macros useful in dealing with
			complex numbers. Also contains prototypes...
         Related Files: Makefile, CVIPmatrix.h
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

$Log: CVIPcomplex.h,v $
Revision 1.1  1994/10/30 22:43:06  hanceg
Initial revision

 * Revision 1.1  1993/05/04  02:31:01  hanceg
 * Initial revision
 *                                                         

*****************************************************************************/
#if !defined( CVIPCOMPLEX_DEFINED )

#define CVIPCOMPLEX_DEFINED

#define CASSIGN(matrix,type,row,col,r,i) (((type**)(matrix)->rptr)[row][col]=(r)); \
                                 (((type**)(matrix)->iptr)[row][col]=(i));
				 
/* Find phasor angle of a complex number. This macro also checks the (0,0) case since 
   the machine will give back a NaN or Inf!. Also... atan2() returns double precision
   and is declared in <math.h> */
#define CANG(r,i) ((r)==0.0 && (i)==0.0) ? (0.0) : atan2((double)i,(double)r)

/* Find magnitude of complex number. Also...sqrt() returns double precision and is 
   declared in <math.h> */
#define CMAG(r,i) sqrt((double)((r)*(r) + (i)*(i)))

/* the folowing macro will convert from the rectangular coordinate system 
   to the polar coordinate system, or convert polar to rectangular.
   The conversion assumes that the data is in radians for the polar
   to rectangular conversion. The conversion from rectangular to polar will
   result in angles measured in radians. */

#define REC2POL(type,m,p,r,i) (m)=((type)CMAG((r),(i)));(p)=((type)CANG((r),(i)))  
#define POL2REC(type,r,i,m,p) (r)=((type)(m*cos((double)p)));(i)=((type)(m*sin((double)p)))

#define CMUL(type,r3,i3,r1,i1,r2,i2) (r3) = ((type)((((r1)*(r2))-((i1)*(i2))))); (i3) = ((type)(((r1)*(i2))+((i1)*(r2))))


#define MAGSQ(r,i) ((double) ((r)*(r) + (i)*(i)))

#endif /* CVIPCOMPLEX_DEFINED */
