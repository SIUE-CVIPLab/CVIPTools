/***************************************************************************
* **********************************************************************
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* **********************************************************************
*
*             File Name: DigitalLine.c
*           Description: 
*         Related Files: 
*   Initial Coding Date: Fri Nov 22 14:56:00 CST 1996
*           Portability: Standard (ANSI) C
*            References:
*             Author(s): Paul Heckbert, Greg Hance 
*                        Southern Illinois University @ Edwardsville
*
** Copyright (C) 1996 SIUE - by Scott Umbaugh and Greg Hance.
**
** Permission to use, copy, modify, and distribute this software and its
** documentation for any purpose and without fee is hereby granted, provided
** that the above copyright notice appear in all copies and that both that
** copyright notice and this permission notice appear in supporting
** documentation.  This software is provided "as is" without express or
** implied warranty.
**
****************************************************************************/
/*
 * Digital Line Drawing
 * by Paul Heckbert -- original author, modified by Greg Hance
 * from "Graphics Gems", Academic Press, 1990
 */
/*
 * digline: draw digital line from (x1,y1) to (x2,y2),
 * calling a user-supplied procedure at each pixel.
 * Does no clipping.  Uses Bresenham's algorithm.
 *
 * Paul Heckbert	3 Sep 85
 */

#include "CVIPtoolkit.h"
#include "CVIPdef.h"

void digLine_GP( ROI *roiP, int x1, int y1, int x2, int y2)
{
    int d, x, y, ax, ay, sx, sy, dx, dy;
    register int i;

    dx = x2-x1;  ax = ABS(dx)<<1;  sx = SGN(dx);
    dy = y2-y1;  ay = ABS(dy)<<1;  sy = SGN(dy);

    x = x1;
    y = y1;
    if (ax>ay) {		/* x dominant */
	d = ay-(ax>>1);
	for (;;) {
	    for(i=0; i < getNoOfBands_ROI(roiP); i++)
	       setPixel_ROI(roiP, byte, x, y, i, 255);
	    if (x==x2) return;
	    if (d>=0) {
		y += sy;
		d -= ax;
	    }
	    x += sx;
	    d += ay;
	}
    }
    else {			/* y dominant */
	d = ax-(ay>>1);
	for (;;) {
	    for(i=0; i < getNoOfBands_ROI(roiP); i++) 
	       setPixel_ROI(roiP, byte, x, y, i, 255);
	    if (y==y2) return;
	    if (d>=0) {
		x += sx;
		d -= ay;
	    }
	    y += sy;
	    d += ax;
	}
    }
}

void drawBox_GP( ROI *roiP )
{

   int x_l = 0;
   int x_r = getHorSize_ROI(roiP) - 1;
   int y_t = 0;
   int y_b = getVerSize_ROI(roiP) - 1;;

   digLine_GP( roiP, x_l, y_t, x_r, y_t);
   digLine_GP( roiP, x_r, y_t, x_r, y_b);
   digLine_GP( roiP, x_r, y_b, x_l, y_b);
   digLine_GP( roiP, x_l, y_b, x_l, y_t);

}
