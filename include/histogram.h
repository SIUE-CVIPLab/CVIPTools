/***************************************************************************
* **********************************************************************
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* **********************************************************************
*
*             File Name: histogram.h
*           Description: 
*         Related Files: 
*   Initial Coding Date: Mon Dec 30 22:08:02 CST 1996
*           Portability: Standard (ANSI) C
*            References:
*             Author(s): dlyons
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
 *RCS info
 *$Author: yawei $
 *$Id: histogram.h,v 1.6 1997/01/16 20:58:59 yawei Exp $
 *$Log: histogram.h,v $
 * Revision 1.6  1997/01/16  20:58:59  yawei
 * Global Change:  Image_FORMAT ==> IMAGE_FORMAT
 *
 * Revision 1.5  1997/01/15  17:13:24  yawei
 * Global Change:  IMAGE ==> Image
 *
 * Revision 1.4  1996/12/31  22:12:32  yawei
 * complete the function prototypes
 *
 * Revision 1.3  1996/12/31  22:01:11  yawei
 * Changed function names and prototypes.
 *
 * Revision 1.2  1996/12/30  19:39:46  yawei
 * removed histeq()
 *
 * Revision 1.1  1996/07/18  19:52:07  akjoele
 * Initial revision
 *
 * Revision 1.3  1995/06/17  15:11:29  dlyons
 * Redid RCS
**
****************************************************************************/

#ifndef __HISTOGRAM_H
#define __HISTOGRAM_H
#ifdef __cplusplus
extern "C"{
#endif 


/* extern void histeq(Image*); 
 * renamed and changed to local function
 */

extern Image *hist_spec(Image *imageP, int mode, char **input);
extern Image *spec_hist_images(Image *imageP, char **input);

extern Image *histogram_spec(Image* imageP, float **histogram);
extern Image *make_histogram(float **histogram, IMAGE_FORMAT image_format,
	COLOR_FORMAT color_format);
extern Image *get_histogram_Image(Image *imageP);
	extern float **get_histogram(Image *imageP);
extern void histogram_show(float **histogram);
extern void showMax_histogram(float **histogram, char *title);

extern float **define_histogram(int bands, int mode, char **eq);

/* setup functions, not encouraged to be used in CVIPtools */
extern void hist_spec_setup(Image*);
extern void histogram_setup(Image*);
extern void make_histogram_setup(Image*);
#ifdef __cplusplus
}
#endif 
#endif
