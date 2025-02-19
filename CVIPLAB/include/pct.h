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
** $Log: pct.h,v $
** Revision 1.8  2000/02/24 07:48:48  ycheng
** added '#include ""CVIPmatrix.h"' and '#include ""m_CovEig.h"' again although acturelly they were
** in the version 1.15.
**
** Revision 1.7  2000/01/12 06:23:23  cvip
** *** empty log message ***
**
** Revision 1.6  2000/01/12 04:26:14  cvip
** *** empty log message ***
**
** Revision 1.5  2000/01/12 03:41:29  cvip
** *** empty log message ***
**
** Revision 1.4  1997/03/08 17:02:46  yawei
** Swaped CVIP_YES and CVIP_NO
**
** Revision 1.3  1997/03/08 00:50:10  yawei
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
** Revision 1.2  1996/12/23 20:37:47  yawei
** Changed function names.
**
 * Revision 1.1  1994/10/30  22:43:06  hanceg
 * Initial revision
 *
 * Revision 1.1  1993/05/31  03:23:39  hanceg
 * Initial revision
 *
*
****************************************************************************/
#if !defined(PCT_DEFINED)

   #define PCT_DEFINED
   #include "CVIPmatrix.h"
   #include "m_CovEig.h"

#ifdef __cplusplus
extern "C"{
#endif 
  
   extern Image *pct( Image *imgP, CVIP_BOOLEAN is_mask, float *maskP);
   extern Image *ipct(Image *imgP, CVIP_BOOLEAN is_mask, float *maskP);
   extern Image *pct_color(Image *imgP, CVIP_BOOLEAN is_mask, float *maskP, int choice);

	/* The setup function is for backword compatibility, new applications
	 * are not encouraged to use it
	 */
	extern Image *pct_setup(Image *imgP, CVIP_BOOLEAN is_mask, float *maskP);
#ifdef __cplusplus
}
#endif 
/* macro removed
	#define pct(a) PCT_Image(a, CVIP_NO, NULL) */

#endif /* PCT_DEFINED */
