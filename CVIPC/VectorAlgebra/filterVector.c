/***************************************************************************
* ======================================================================
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* ======================================================================
*
*             File Name: filterVector.c
*           Description: 
*         Related Files: 
*   Initial Coding Date: Thu Sep 30 22:22:55 CDT 1993
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
** $Log: filterVector.c,v $
** Revision 1.1  1994/10/30 17:59:06  hanceg
** CVIPtools1.0 source file - G. Hance
**
*
****************************************************************************/
#include "CVIPvector.h"
#include "CVIPdef.h"

int convolve_Vector(
	double 	*xvecP,	/* input sequence vector */
	double 	*hvecP,	/* impulse sequence vector */
	int 	xlen,	/* length of input vector */
	int 	hlen	/* length of impulse vector */
)
{
	double 		*yvecP, *yP;
	register double *xP, *hP;
	register int 	i, j;
	unsigned 	ylen, len;

	ylen = xlen + hlen - 1;

	if(!(yvecP = (double *) calloc(ylen, sizeof(double)))) {
		error_CVIP("convolve", "memory allocation failure!");
		return 0;
	}
	yP = yvecP;

	len = hlen-1;
	for(i=0, xP=xvecP; i < xlen; i++, xP++)
		for(j=0, hP=hvecP; j < hlen; j++, hP++)
			yP[len+i-j] += (*hP)*(*xP);

	len = hlen >> 1;
	yP += len;
	if( ((void *)memcpy((void *)xvecP, (void *)yP, sizeof(double)*xlen)) != xvecP ) {
		error_CVIP("convolve", "memcpy failed!");
		return 0;
	}

	free(yvecP);

return(1);
}
			

	


