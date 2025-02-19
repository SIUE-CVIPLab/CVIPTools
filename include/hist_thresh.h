/***************************************************************************
* ======================================================================
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* ======================================================================
*
*             File Name: hist_thresh.h
*           Description: 
*         Related Files: 
*   Initial Coding Date: Thu Dec  2 15:52:57 CST 1993
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
** $Log: hist_thresh.h $
** Revision 1.3  1996/12/21 00:58:36  yawei
** Changed file name to "hist_thresh.h"
**
 * Revision 1.2  1996/12/20  23:43:15  yawei
 *    Image *ATS_SetUp(const Image *imgP)
 * ==>Image *hist_thresh_segment(const Image *imgP)
 *
 *    int adaptThresh_Image( Image *imgP, unsigned nom )
 * ==>Image *hist_thresh_gray(Image *imgP)
 *    (This function is not currently in the Book, it works on single band image,
 *     the original nom doesn't do anything)
 *
 * Revision 1.1  1994/10/30  22:43:06  hanceg
 * Initial revision
 *
*
****************************************************************************/
#ifdef __cplusplus
extern "C"{
#endif 
extern Image *hist_thresh_gray(Image *imgP, float tore);
extern Image *hist_thresh_segment(Image *imgP, float tore);
#ifdef __cplusplus
}
#endif 
