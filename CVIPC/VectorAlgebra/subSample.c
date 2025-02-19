/***************************************************************************
* ======================================================================
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* ======================================================================
*
*             File Name: subSample.c
*           Description: subsample (decimate) a 1-D vector of data.
*         Related Files: subSample.h
*   Initial Coding Date: Thu Sep 23 19:00:15 CDT 1993
*           Portability: Standard (ANSI) C
*            References: none
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
** $Log: subSample.c,v $
** Revision 1.2  1997/03/08 01:02:41  yawei
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

#define SUBSAMPLE(veca_,dima_,vecb_,type_,skip_) { \
	register int i_; \
	register type_ *bP_ = vecb_; \
	type_ *aP_ = veca_; \
	for(i_ = 0; i_ < dima_; i_ += skip_, bP_++) \
		*bP_ = aP_[i_]; \
} \

void *
subSample_Vector(
	void *vecP,
	unsigned dim,
	CVIP_TYPE data_type,
	unsigned skip, 
	unsigned *new_dim
)
{
	void *outP;
	size_t ds[] = 	{sizeof(byte), sizeof(short), sizeof(int),
			sizeof(short), sizeof(float), sizeof(double)};

	/*
	 * make sure dimension is greater than 0
	 */
  	if (dim < 1 ) {
		error_CVIP("subSample_Vector", "vector dimension equals 0");
		return NULL;
	}

	/*
  	 * calculate new vector length of subsampled data
 	 */
  	*new_dim = ( (dim - 1)/(skip + 1) ) + 1;

	outP = malloc(ds[data_type]*(*new_dim));

	skip++;
	switch(data_type) {
		case CVIP_BYTE :
			SUBSAMPLE(vecP, dim, outP, byte, skip)
			break;
		case CVIP_SHORT :
			SUBSAMPLE(vecP, dim, outP, short, skip)
			break;
		case CVIP_INTEGER :
			SUBSAMPLE(vecP, dim, outP, int, skip)
			break;
		case CVIP_FLOAT :
			SUBSAMPLE(vecP, dim, outP, float, skip)
			break;
		case CVIP_DOUBLE :
			SUBSAMPLE(vecP, dim, outP, double, skip)
			break;
		default : 
			error_CVIP("subSample_Vector", "invalid data type!");
			return NULL;
	}

return outP;
}
			
	
