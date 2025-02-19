/***************************************************************************
* **********************************************************************
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* **********************************************************************
*
*             File Name: h_image.c
*           Description: 
*         Related Files: 
*   Initial Coding Date: Tue Nov  5 15:54:47 CST 1996
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
** $Log: h_image.c,v $
** Revision 1.6  1997/03/08 00:53:42  yawei
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
** Revision 1.5  1997/01/02 16:48:58  akjoele
** Eliminated unneeded variables after lint check.
**
 * Revision 1.4  1996/11/08  00:02:11  yawei
 * data normalized to N*N for gaussian mask
 *
 * Revision 1.3  1996/11/07  03:50:42  yawei
 * commented out the data_remaping, so the output of h_image is float.
 *
 * Revision 1.2  1996/11/06  05:01:48  yawei
 * set the value of constant mask to 255, so it will be remapped to 255 on return.
 *
 * Revision 1.1  1996/11/05  21:55:00  yawei
 * Initial revision
 *
*
****************************************************************************/
#include "CVIPtoolkit.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


Image *
h_image(int type, unsigned int height, unsigned int width){
			
	/* type = 1, Constant
	 * type = 2, Fixed mask
	 * type = 3, Gaussian
	 */

	unsigned int r, c, hf_w = width/2, hf_h = height/2;
	Image *outimage;
	float **outdata, sum = 0.0, sigma, tmp1, tmp2, tmp;

	if (height < 3 || width < 3) {
		fprintf(stderr, "Masksize too small, at least 3x3\n");
		return (Image *)NULL;
	}

	outimage = new_Image(PGM, GRAY_SCALE, 1, height, width, CVIP_FLOAT, REAL);
	outdata = (float **)getData_Image(outimage, 0);

	switch (type) {
		case 1:
			for (r = 0; r < height; r++) 
				for (c = 0; c < width; c++) {
					outdata[r][c] = 1.0;
					sum += outdata[r][c];
				}
			break;
		case 2:
			for (r = 0; r < height; r++) 
				for (c = 0; c < width; c++) {
					outdata[r][c] = 1.0;
					sum += outdata[r][c];
				}
			outdata[height/2][width/2] = height * width;
			sum = sum - 1.0 + outdata[height/2][width/2];
			break;
		case 3:
			c = (width + height) /4;
			r = (width + height) /2;
			sigma = sqrt(c*c / (2 * log(2) + (r - 3) * log(3)));
			sigma = 1.0 / 2.0 /sigma/sigma;
			tmp = width * height;
			for (r = 0; r < height; r++) 
				for (c = 0; c < width; c++) {
					tmp1 = (r-hf_h)*(r-hf_h); tmp2 = (c-hf_w)*(c-hf_w);
					outdata[r][c] = tmp*exp(- (tmp1 + tmp2) * sigma);
					sum += outdata[r][c];
				}
			break;
		default:
			fprintf(stderr, "Incorrect mask type number: %d\n", type);
			return (Image *)NULL;
	}

	return outimage;
}
