/***************************************************************************
* ======================================================================
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* ======================================================================
*
*             File Name: TrimList.h
*           Description: 
*         Related Files: 
*   Initial Coding Date: Sun Sep 19 18:48:16 CDT 1993
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
** $Log: TrimList.h,v $
 * Revision 1.2  1997/03/08  00:48:26  yawei
 * Name Changes:
 * 	BOOLEAN ==> CVIP_BOOLEAN
 * 	FALSE ==> CVIP_YES
 * 	TRUE ==> CVIP_NO
 * 	BYTE ==> CVIP_BYTE
 * 	SHORT ==> CVIP_SHORT
 * 	INTEGER ==> CVIP_INTEGER
 * 	FLOAT ==> CVIP_FLOAT
 * 	DOUBLE ==> CVIP_DOUBLE
 * 	TYPE ==> CVIP_TYPE
 *
** Revision 1.1  1994/10/30 22:43:06  hanceg
** Initial revision
**
*
****************************************************************************/
extern int trimList_Objects(ObjectList listP, unsigned width, unsigned height, float p_area_min, float p_area_max, float eig_r_min, float eig_r_max, float angle_min, float angle_max, float p_width, float p_height, CVIP_BOOLEAN no_edge );
