/***************************************************************************
* ======================================================================
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* ======================================================================
*
*             File Name: findHisto.c
*           Description: find the histogram of a vector
*         Related Files: findHisto.h
*   Initial Coding Date: Thu Sep 30 16:09:30 CDT 1993
*           Portability: Standard (ANSI) C
*            References: yours truly
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
** $Log: findHisto.c,v $
** Revision 1.3  1997/03/08 17:07:52  yawei
** Swaped CVIP_YES and CVIP_NO
**
** Revision 1.2  1997/03/08 01:02:44  yawei
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
** Revision 1.1  1994/10/30 17:59:05  hanceg
** CVIPtools1.0 source file - G. Hance
**
*
****************************************************************************/
#include "CVIPvector.h"
#include "CVIPdef.h"

int findHisto_Vector(
	byte 	*vecP,	/* input vector */
	int 	vsize,	/* size of input vector */
	void 	*hP,	/* histogram vector */
	int 	l,	/* expected low value in input */
	int 	h,	/*    "     high        "      */
	CVIP_TYPE 	dtype	/* VIP data type of histogram */
)
{
	const char 	*fn = "findHisto";
	int 		size, *ihP;
	register int 	i;
	double 		*dhP;

	if(l < 0) {
		error_CVIP(fn, "l = %d, must be positive!\n", l);
		return 0;
	}

	size = h - l + 1;

	if(size < 2) {
		error_CVIP(fn,"h-l =%d, must atleast be 2 to be of any use!\n");
		return 0;
	}

	switch(dtype) {
		case CVIP_INTEGER :
			if(memset(hP, 0, sizeof(int)*size) != hP) {
				error_CVIP(fn, "could not init. histogram!\n");
				return 0;
			}
			ihP = hP;
			for(i=0; i < vsize; i++, vecP++)
				ihP[CLAMP((int) *vecP,l,h)]++;
		break;
		case CVIP_DOUBLE :
			if(memset(hP, 0, sizeof(double)*size) != hP) {
				error_CVIP(fn, "could not init. histogram!\n");
				return 0;
			}
			dhP = hP;
			for(i=0; i < vsize; i++, vecP++)
				dhP[CLAMP((int) *vecP,l,h)]++;
		break;
		default :
			error_CVIP(fn,"support CVIP_INTEGER and CVIP_DOUBLE types only!\n");
			return 0;
	}

return 1;
}		

int printHisto_Vector(
	const char *fname,
	void *hP,
	CVIP_TYPE dtype,
	int l,
	int h,
	int skipval
)
{
	FILE *fileP;
	register int 	i, *ihP, size;
	register double	*dhP;
	int temp;

	size = h - l + 1;

	fileP = openWrite_CVIP(fname, CVIP_NO);

	fprintf(fileP,"# histogram\n");
	fprintf(fileP,"# bin\tcount\n");
			
	switch(dtype) {
		case CVIP_INTEGER :
			ihP = hP;
			if((skipval >= 0) && (skipval <= h))
				ihP[skipval] = 0;
			for(i=0; i < size; i++, ihP++)
				if(*ihP)
					fprintf(fileP,"%5d\t%d\n",i, *ihP);
		break;
		case CVIP_DOUBLE :
			dhP = hP;
			if((skipval >= 0) && (skipval <= h))
				dhP[skipval] = 0;
			for(i=0; i < size; i++, dhP++)
				if(*dhP)
					fprintf(fileP,"%5d\t%.4f\n",i, *dhP);
				
		break;
		default :
			error_CVIP("printHisto","support CVIP_INTEGER and CVIP_DOUBLE types only!\n");
			return 0;
	}

	close_CVIP(fileP);

return(1);
}
