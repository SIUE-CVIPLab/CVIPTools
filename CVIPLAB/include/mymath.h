/***************************************************************************
* ======================================================================
* Computer Vision/ImageFuzzy Processing Tool Project - Dr. Scott Umbaugh SIUE
* ======================================================================
*
*             File Name: mymath.h
*           Description: 
*         Related Files: 
*   Initial Coding Date: Tue Jun  1 12:02:30 CDT 1993
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
** $Log: mymath.h,v $
** Revision 1.1  1994/10/30 22:43:06  hanceg
** Initial revision
**
 * Revision 1.1  1993/06/02  04:48:35  hanceg
 * Initial revision
 *
*
****************************************************************************/
extern int     rgb_to_i123();
extern int     rgb_to_chr();
extern int     rgb_to_sph();
extern double  *gausian();
extern int     convolution();
extern int     convert();
extern int     low_pass();

extern float  tore;
extern int     t_len;  
