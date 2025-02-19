/***************************************************************************
* **********************************************************************
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* **********************************************************************
*
*             File Name: CVIPview.h
*           Description: display related functions
*         Related Files: xview.c, view.c, display.c
*   Initial Coding Date: Sun Jan  5 15:30:06 CST 1997
*           Portability: Standard (ANSI) C
*            References:
*             Author(s): Yansheng Wei
*                        Southern Illinois University @ Edwardsville
*
** Copyright (C) 1996 SIUE - by Scott Umbaugh and Yansheng Wei.
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
** $Log: CVIPview.h,v $
** Revision 1.10  1997/06/02 19:30:13  yawei
** modified setDisplay_Image() prototype
**
** Revision 1.9  1997/05/30 00:26:36  yawei
** added varargs.h
**
** Revision 1.8  1997/05/29 22:29:46  yawei
** modified prototype for setDisplay_Image()
**
** Revision 1.7  1997/01/16 20:56:37  yawei
** Global Change:  Image_FORMAT ==> IMAGE_FORMAT
**
 * Revision 1.6  1997/01/15  17:11:25  yawei
 * Global Change:  IMAGE ==> Image
 *
 * Revision 1.5  1997/01/05  21:30:54  yawei
 * added header
 *
*
****************************************************************************/
#ifndef _CVIP_VIEW
#define _CVIP_VIEW


extern void setDisplay_Image(char *viewer, char *format);
extern char *getDisplay_Image(void);

extern void display_Image( const char *image_name , IMAGE_FORMAT format );
extern void display_RAMImage(Image *inputImage, char *name);
extern void view_Image(Image *inputImage, char *imagename); 

extern void cont_view(Image *inputImage, char *name);

#endif
