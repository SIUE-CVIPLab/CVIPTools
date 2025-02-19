/***************************************************************************
* ======================================================================
* Computer Vision/ImageFuzzy Processing Tool Project - Dr. Scott Umbaugh SIUE
* ======================================================================
*
*             File Name: seg.h
*           Description: 
*         Related Files: 
*   Initial Coding Date: Tue Jun  1 12:02:31 CDT 1993
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
** $Log: seg.h,v $
** Revision 1.1  1994/10/30 22:43:06  hanceg
** Initial revision
**
 * Revision 1.1  1993/06/02  04:48:36  hanceg
 * Initial revision
 *
*
****************************************************************************/
extern void find_cluster();
extern void coarse_seg();

extern int     vn[3];     /* number of valleys in each space */
extern int     pn[3];     /* number of peaks in each space */

extern double  peak[64][3];
extern double  valley[64][3]; 
extern float   safe;
