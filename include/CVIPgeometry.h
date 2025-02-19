/***************************************************************************
* ======================================================================
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* ======================================================================
*
*             File Name: CVIPgeometry.h
*           Description: contains function prototypes, constants and types
*			 defined in threshold.c
*         Related Files: compliment.c
*   Initial Coding Date: Tue Apr 27 21:49:42 CDT 1993
*           Portability: Standard (ANSI) C
*             Credit(s): Srini
*                        Southern Illinois University @ Edwardsville
*
* RCS (Revision Control System) Information
* ...Added automatically by RCS 
*
** $Log: CVIPgeometry.h,v $
** Revision 1.14  2001/11/10 18:37:05  ycheng
** ycheng checked in this file at cpohl's request.
**
** Revision 1.13  2000/05/24 22:02:57  cpohl
** *** empty log message ***
**
** Revision 1.12  1997/07/23 21:31:45  wzheng
** translate do_warp -> do_wrap
**
** Revision 1.11  1997/03/21 01:13:59  yawei
** added copy_paste
**
** Revision 1.10  1997/03/08 00:52:42  yawei
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
** Revision 1.9  1997/01/15 17:13:36  yawei
** Global Change:  IMAGE ==> Image
**
 * Revision 1.8  1996/12/31  04:07:03  yawei
 * added enlarge()
 *
 * Revision 1.7  1996/12/31  00:15:21  yawei
 * Added crop()
 *
 * Revision 1.6  1996/12/17  22:52:09  yawei
 * Changed and added function prototypes
 *
 * Revision 1.5  1996/12/17  21:56:58  yawei
 * Changed file name from "image_geometry.h" to "CVIPgeometry.h"
 *
 * Revision 1.4  1996/12/17  21:50:45  yawei
 * added spatial_quant
 *
 * Revision 1.3  1996/12/17  20:07:52  akjoele
 * Added crop_Image; removed extraneous
 * crop_inerr, etc.
 *
 * Revision 1.2  1996/11/26  18:09:35  yawei
 * Added funciton prototype for rotate_image_sep
 *
 * Revision 1.1  1994/10/30  22:43:06  hanceg
 * Initial revision
 *
 * Revision 1.1  1993/04/29  06:54:22  hanceg
 * Initial revision
 *
*
****************************************************************************/

#include "bilinear.h"

#ifndef  _CVIP_GEOMETRY
#define  _CVIP_GEOMETRY

#ifdef __cplusplus
extern "C"{
#endif 

#define AVERAGE   1
#define MEDIAN    2
#define METHOD    3

extern Image *HorizontalFlip(Image *inputImage);
extern Image *VerticalFlip(Image *inputImage);
extern Image *rotate( Image *input_Image, float degree);
extern Image *shrink( Image *input_Image, float factor );
extern Image *spatial_quant(Image *cvipImage,int row,int col,int method);
extern Image *translate(Image *cvipImage, CVIP_BOOLEAN do_wrap, int y_off,
					int x_off, int y_mount,int x_mount,int y_slide,
					int x_slide, float fill_out);
extern Image *zoom(Image *input_Image, int quadrant, int X, int Y, int dx,
					int dy, float temp_factor);
extern Image *crop(Image *imgP, unsigned row_offset, unsigned col_offset,
					unsigned rows, unsigned cols);
extern Image *object_crop(Image *imgP, int no_of_coords, int *coordinates, int format, int R, int G, int B);
extern Image *enlarge(Image *cvipImage, int row, int col);
extern Image *copy_paste( Image *srcImg, Image *destImg, 
	unsigned start_r, unsigned start_c, unsigned height, unsigned width,
	unsigned dest_r, unsigned dest_c, CVIP_BOOLEAN transparent);
extern Image *local_adaptive_zoom(Image *inputImage);

/* the setup functions are for backword compatibility, new applications are not
 * encouraged to use them 
 */
extern Image *rotate_sep( Image *input_Image );
extern Image *shrink_sep( Image *input_Image );
extern Image *spatial_quant_sep(Image *cvipImage);
extern Image *translate_setup(Image *cvipImage);
extern Image * CutPaste_Setup(Image *cvipImage);
extern Image *zoom_sep( Image *input_Image );
extern Image * enlarge_setup(Image *cvipImage);
#ifdef __cplusplus
}
#endif 
#endif
