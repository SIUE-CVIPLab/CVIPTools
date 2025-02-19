/***************************************************************************
* ======================================================================
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* ======================================================================
*
*             File Name: median_cut.h
*           Description: 
*         Related Files: 
*   Initial Coding Date: Thu Oct  7 15:00:03 CDT 1993
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
** $Log: median_cut.h,v $
** Revision 1.5  1997/03/08 00:48:29  yawei
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
** Revision 1.4  1996/12/23 18:49:23  yawei
** Changed filename: MedianCut.h ==> median_cut.h
**
 * Revision 1.3  1996/12/23  00:44:13  yawei
 * Changed (const Image) to (Image ) in the setup function.
 *
 * Revision 1.2  1996/12/22  05:21:51  yawei
 * Changed:
 *    ColorHistogram *medianCut_Image ==> Image *median_cut_segment
 *    MCS_SetUp ==> median_cut_setup
 *
 * Revision 1.1  1994/10/30  22:43:06  hanceg
 * Initial revision
 *
*
****************************************************************************/
#if !defined(CVIP_MEDIAN_CUT__INCLUDED_)
#define CVIP_MEDIAN_CUT__INCLUDED_
#ifdef __cplusplus
extern "C"{
#endif 

extern Image *median_cut_segment(Image *imgP, int newcolors,
		CVIP_BOOLEAN is_bg, Color bg);
extern Image *median_cut_setup(Image *imgP);
#ifdef __cplusplus
}
#endif 


#endif